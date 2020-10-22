//
// Created by rajashekhar on 20/10/20.
//

#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <stdio.h>
#include <mysql/mysql.h>


#define HOST "localhost"   /*hostname*/
#define USER  "raja"       /*username*/
#define PASS    "Kucharla@1"         /* Left blank for Code portability */
#define DB_NAME "esb_db"   /*name of the database*/
#define PORT  3306         /*port number*/
#define UNIX_SOCKET NULL   /*unix socket*/
#define FLAG 0            /*last parameter to mysql_real_connect */


int connect_to_db(void);;
int finish_with_error(MYSQL *con);
int insert_into_esb_request(char *sender_id, char *dest_id,
                          char *message_type, char *reference_id, char *message_id,
                          char *data_location, char *status, char *status_details, char *received_on);

#endif //DATABASE_CONNECTOR_H
