#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/un.h>
#include <stddef.h>

// next 2 defines are for sftp server so that we can store data locally on it . See sftp.c if still confused .
#define UPLOAD_FILE_AS  "output_to_transfer.json"
#define REMOTE_URL "sftp://127.0.0.1/sftpuser/sftp-test/"

/* required header files */
#include "../adapter/adapter.h"
#include "../bmd_extract/xml.h"
#include "../db_access/connector.h"
#define threshold 50

bool create_worker_thread(int fd);

/**
 * This code is adapted from the samples available at:
 * https://opensource.com/article/19/4/interprocess-communication-linux-networking and
 * https://www.gnu.org/software/libc/manual/html_node/Local-Socket-Example.html
 *
 * Compile it using: gcc local_socket_client_server.c -lpthread -o ipc_demo
 
 * Needless to say, this code is not perfect and may have some subtle bugs. A purpose
 * if this code is to show how to write a socket based client server program that
 * off-loads the client connection to a new thread for processing.
 */

//freeing the memory allocated throughout the code

void freeing_the_memory(transform_config *tf,transport_config *tp,bmd *bd){
    free(tf->config_value);
    free(tf->config_key);
    free(tf);
    free(tp->config_value);
    free(tp->config_key);
    free(tp);
    free(bd->envelope);
    free(bd->payload);
    free(bd);
}
void log_msg(const char *msg, bool terminate) {
    printf("%s\n", msg);
    if (terminate) exit(-1); /* failure */
}

/**
 * Create a named (AF_LOCAL) socket at a given file path.
 * @param socket_file
 * @param is_client whether to create a client socket or server socket
 * @return Socket descriptor
 */
int make_named_socket(const char *socket_file, bool is_client) {
    printf("Creating AF_LOCAL socket at path %s\n", socket_file);
    if (!is_client && access(socket_file, F_OK) != -1) {
        log_msg("An old socket file exists, removing it.", false);
        if (unlink(socket_file) != 0) {
            log_msg("Failed to remove the existing socket file.", true);
        }
    }
    struct sockaddr_un name;
    /* Create the socket. */
    int sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        log_msg("Failed to create socket.", true);
    }

    /* Bind a name to the socket. */
    name.sun_family = AF_LOCAL;
    strncpy (name.sun_path, socket_file, sizeof(name.sun_path));
    name.sun_path[sizeof(name.sun_path) - 1] = '\0';

    /* The size of the address is
       the offset of the start of the socket_file,
       plus its length (not including the terminating null byte).
       Alternatively you can just do:
       size = SUN_LEN (&name);
   */
    size_t size = (offsetof(struct sockaddr_un, sun_path) +
                   strlen(name.sun_path));
    if (is_client) {
        if (connect(sock_fd, (struct sockaddr *) &name, size) < 0) {
            log_msg("connect failed", 1);
        }
    } else {
        if (bind(sock_fd, (struct sockaddr *) &name, size) < 0) {
            log_msg("bind failed", 1);
        }
    }
    return sock_fd;
}

/**
 * Starts a server socket that waits for incoming client connections.
 * @param socket_file
 * @param max_connects
 */
_Noreturn void start_server_socket(char *socket_file, int max_connects) {
    int sock_fd = make_named_socket(socket_file, false);

    /* listen for clients, up to MaxConnects */
    if (listen(sock_fd, max_connects) < 0) {
        log_msg("Listen call on the socket failed. Terminating.", true); /* terminate */
    }
    log_msg("Listening for client connections...\n", false);
    /* Listens indefinitely */
    while (1) {
        struct sockaddr_in caddr; /* client address */
        int len = sizeof(caddr);  /* address length could change */

        printf("Waiting for incoming connections...\n");
        int client_fd = accept(sock_fd, (struct sockaddr *) &caddr, &len);  /* accept blocks */

        if (client_fd < 0) {
            log_msg("accept() failed. Continuing to next.", 0); /* don't terminate, though there's a problem */
            continue;
        }
        /* Start a worker thread to handle the received connection. */
        if (!create_worker_thread(client_fd)) {
            log_msg("Failed to create worker thread. Continuing to next.", 0);
            continue;
        }

    }
    /* while(1) */
}


/**
 * This functions is executed in a separate thread.
 * @param sock_fd
 */
void thread_function(int sock_fd) {
    log_msg("SERVER: thread_function: starting", false);
    transform_config *tf = NULL;
    transport_config *tp = NULL;
    bmd *bd;
    int id;
    char buffer[5000];
    memset(buffer, '\0', sizeof(buffer));
    int count = read(sock_fd, buffer, sizeof(buffer));
    if (count > 0) {
        printf("SERVER: Received from client i.e path of the xml file: %s\n", buffer);

        /* Extracting the data from the bmd xml file*/
        bd = parse_bmd_xml(buffer);

        /*
         * check if theere is an existing record present in esb_request table
         * for which the BMD XML file location is same as this one
         */

         /*
         If the existing record found for the received BMD XML file location
          check_data_location() function return -1 if no record present else
          id > 0 of the rom which has data_location as buffer
         */
          id = check_data_location(buffer);
         if(id > 0) {
             /*check whether the status is processing or not"

             /* get processing_attempts of data of given file
              * also check that the status is not "PROCESSING"
              */
             int processing_attempts = get_processing_attempts(buffer);
             if(processing_attempts < threshold && (check_status("PROCESSING",buffer) == -1) ){
                 processing_attempts++;
                 //increase processing attempts by 1
                 change_processing_attempts(processing_attempts,buffer);

                 /*
                  *look up the records routes,transform_config and transport_config tables
                  */
                 int route_id = get_active_route_id(bd->envelope->Sender,bd->envelope->Destination,
                                                    bd->envelope->MessageType);
                 if(route_id < 0) {
                     close(sock_fd) ;/*break connection */
                     log_msg("There is no active route_id present /n",false);
                     pthread_exit(NULL);
                 }
                 tf = fetch_transform_config_key_and_value(route_id);
                 tp = fetch_transport_config_key_and_value(route_id);
             }else {
                     update_esb_request("ERROR",id);
                     /**
                      * IMPLEMENT CLEANUP STEP
                      */
                 close(sock_fd); /*break connection */
                 log_msg("Number of processing attempts is more than threshold or it is already processing/n",false);
                 pthread_exit(NULL);

             }

         } else {
             /* This else loop is executed when data of given bmd xml file is absent */

             /* performing validation */
             if(!is_bmd_valid(bd)) {
                 close(sock_fd); /*break connection */
                 log_msg("bmd is not valid ",false);
                 pthread_exit(NULL);
             }
             int rc = insert_into_esb_request(bd->envelope->Sender,bd->envelope->Destination,
                                              bd->envelope->MessageType,bd->envelope->ReferenceID,
                                              bd->envelope->MessageID, buffer,"AVAILABLE",
                                              "It is available",bd->envelope->CreationDateTime);
             if(rc != 1) {
                 close(sock_fd);/* break connection */
                 log_msg("Insertion data into the esb_request failed",false);
                 pthread_exit(NULL);
             }

             /*
              * change the status from available to processing so that other thread won't pick it
              */
               update_esb_request("PROCESSING",id);
                  /*
                  *look up the records routes,transform_config and transport_config tables
                  */
             int route_id = get_active_route_id(bd->envelope->Sender,bd->envelope->Destination,
                                                bd->envelope->MessageType);
             if(route_id < 0) {
                 close(sock_fd); /*break connection */
                 log_msg("There is no active route_id present /n",false);
                 pthread_exit(NULL);
             }
             tf = fetch_transform_config_key_and_value(route_id);
             tp = fetch_transport_config_key_and_value(route_id);

        }

        write(sock_fd, buffer, sizeof(buffer)); /* echo as confirmation */
    }
    
    
    //email as destination service ends at line 247
     char* payload=extract_payload(buffer);
   //  printf("========> This is the paylaod to transfer %s\n",payload);
     
     convert_to_json(payload,"to_transfer");
     
     char* send=send_mail("vinayprabhakar91@gmail.com","output_to_transfer.json");
     printf("%s\n",send);
     
     //sftp as destination service
     sftp_upload(UPLOAD_FILE_AS,"output_to_transfer.json");
     
     
    /**
     * IMPLEMENT vii step here
     */
     // if vii step is works successfully
     if(true) {
         update_esb_request("DONE",id);
     }else{
         update_esb_request("ERROR",id);
     }
     
         
    //free the allocated memory 
    freeing_the_memory(tf,tp,bd);
    close(sock_fd); /* break connection */
    log_msg("SERVER: thread_function: Done. Worker thread terminating.", false);
    pthread_exit(NULL); // Must be the last statement
}

/**
 * This function launches a new worker thread.
 * @param sock_fd
 * @return Return true if thread is successfully created, otherwise false.
 */
bool create_worker_thread(int sock_fd) {
    log_msg("SERVER: Creating a worker thread.", false);
    pthread_t thr_id;
    int rc;
    rc = pthread_create(&thr_id,
            /* Attributes of the new thread, if any. */
                        NULL,
            /* Pointer to the function which will be
             * executed in new thread. */
                        thread_function,
            /* Argument to be passed to the above
             * thread function. */
                        (void *) sock_fd);
    if (rc) {
        log_msg("SERVER: Failed to create thread.", false);
        return false;
    }
    return true;
}

/**
 * Sends a message to the server socket.
 * @param msg Message to send
 * @param socket_file Path of the server socket on localhost.
 */
void send_message_to_socket(char *msg, char *socket_file) {
    int sockfd = make_named_socket(socket_file, true);

    /* Write some stuff and read the echoes. */
    log_msg("CLIENT: Connect to server, about to write some stuff...", false);
    if (write(sockfd, msg, strlen(msg)) > 0) {
        /* get confirmation echoed from server and print */
        char buffer[5000];
        memset(buffer, '\0', sizeof(buffer));
        if (read(sockfd, buffer, sizeof(buffer)) > 0) {
            printf("CLIENT: Received from server:: %s\n", buffer);
        }
    }
    log_msg("CLIENT: Processing done, about to exit...", false);
    close(sockfd); /* close the connection */
}


/**
 * This is the driver function you can use to test client-server
 * communication using sockets.
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [server|client] [Local socket file path] [Message to send (needed only in case of client)]\n",
               argv[0]);
        exit(-1);
    }
    if (0 == strcmp("server", argv[1])) {
        start_server_socket(argv[2], 10);
    } else {
        send_message_to_socket(argv[3], argv[2]);
    }
}

