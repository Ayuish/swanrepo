#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

#define PORT 20000 
#define BACKLOG 5
#define LENGTH 512 



 
void* thread_function(char* args)
{
	int i=0;
    while(i<2)
    {
        printf("I am thread_function and path of the file recieved from clien end is %s \n",args);
		i=i+2;
    }
}

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main ()
{
	/* Defining Variables */
	int sockfd; 
	int nsockfd; 
	int num;
	int sin_size; 
	struct sockaddr_in addr_local; /* client addr */
	struct sockaddr_in addr_remote; /* server addr */
	char revbuf[LENGTH]; // Receiver buffer

	/* Get the Socket file descriptor */
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
	    error("ERROR: Failed to obtain Socket Descriptor.\n");
	}
	else 
		printf("[Server] Obtaining socket descriptor successfully.\n");

	/* Fill the client socket address struct */
	addr_local.sin_family = AF_INET; // Protocol Family
	addr_local.sin_port = htons(PORT); // Port number
	addr_local.sin_addr.s_addr = INADDR_ANY; // AutoFill local address
	bzero(&(addr_local.sin_zero), 8); // Flush the rest of struct

	/* Bind a special Port */
	if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
	{
	    error("ERROR: Failed to bind Port.\n");
	}
	else 
		printf("[Server] Binded tcp port %d in addr 127.0.0.1 sucessfully.\n",PORT);

	/* Listen remote connect/calling */
	if(listen(sockfd,BACKLOG) == -1)
	{
	    error("ERROR: Failed to listen Port.\n");
	}
	else
		printf ("[Server] Listening the port %d successfully.\n", PORT);

	int success = 0;
	while(success == 0)
	{
	    sin_size = sizeof(struct sockaddr_in);

	    /* Wait a connection, and obtain a new socket file despriptor for single connection */
	    if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) == -1) 
		{
	        error("ERROR: Obtaining new Socket Despcritor.\n");
		}
	    else 
			printf("[Server] Server has got connected from %s.\n", inet_ntoa(addr_remote.sin_addr));

		/*Receive File from Client */
		char* fr_name = "/home/vinay/Desktop/swan/esb_app/src/parser/recieved_bmd.xml";
		pthread_t thread_id;
		int ret;
		ret=pthread_create(&thread_id,NULL,&thread_function,fr_name);
		if(ret==0)
		{
			printf("Thread cretaed successfully \n");

		}
		else
		{
			printf("Thread creation failed\n");
		}
		
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
			printf("File %s Cannot be opened file on server.\n", fr_name);
		else
		{
			bzero(revbuf, LENGTH); 
			int fr_block_sz = 0;
			//int success = 0;
			//while(success == 0)
			//{
			    while(fr_block_sz = recv(nsockfd, revbuf, LENGTH, 0)) 
			    {
			        if(fr_block_sz == 0)
			        {
			            break;
			        }
			        int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
			        if(write_sz < fr_block_sz)
			        {
			            error("File write failed on server.\n");
			        }
					if(fr_block_sz<0)
					{
						error("Error receiving file form client to server .\n");
					}
			        bzero(revbuf, LENGTH);
			    }
			    printf("Ok received from client!\n");
			    fclose(fr);
			//}
		}

	
	        success = 1;
	        close(nsockfd);
	        printf("[Server] Connection with Client closed. Server will wait now...\n");
	        while(waitpid(-1, NULL, WNOHANG) > 0);
	    //}
	}
}
