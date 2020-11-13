//
// Created by rajashekhar on 20/10/20.
//

#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <stdio.h>
#include <mysql/mysql.h>


#define HOST "localhost"   /*hostname*/
#define USER  "newuser"       /*username*/
#define PASS    "Parrot_2020"         /* Left blank for Code portability */
#define DB_NAME "esb_db"   /*name of the database*/
#define PORT  3306         /*port number*/
#define UNIX_SOCKET NULL   /*unix socket*/
#define FLAG 0            /*last parameter to mysql_real_connect */





typedef struct transport_config_data
{
    char * config_key;
    char * config_value;
}transport_config;

typedef struct transform_config_data
{
    char * config_key;
    char * config_value;
}transform_config;


int connect_to_db(void);;
int finish_with_error(MYSQL *con);
int insert_into_esb_request(char *sender_id, char *dest_id,
                          char *message_type, char *reference_id, char *message_id,
                          char *data_location, char *status, char *status_details, char *received_on);
int get_active_route_id(char *sender_id,char *destination_id, char *message_type);
int update_esb_request(char * status,int id);
int check_id_in_transform_config(int route_id);
int check_id_in_transport_config(int route_id);
 
int select_status(char * status);

transform_config *  fetch_transform_config_key_and_value(int route_id);

transport_config *  fetch_transport_config_key_and_value(int route_id);

int check_data_location(char *data_location);
int get_processing_attempts(char *data_location);
int change_processing_attempts(int processing_attempts,char *data_location);
int check_status(char *status, char *data_location);

#endif //DATABASE_CONNECTOR_H
