/* Created By Vinay Prabhakar on 22/10/20
@Brief :- Under this we will be updating the esb_request table after that request
has been completed and we need to update the status in that table to "Error
or "Done" as per our requirement
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "connector.h"

#define STRING_SIZE 100

#define UPDATE_QUERY "update esb_request set status= ? where id =?"

int update_esb_request(char * status,int id)
{
    printf("Updating esb_request table ...\n");

    MYSQL_STMT      *stmt;
    MYSQL_BIND      bind[2];
    my_ulonglong    affected_rows;
    int             param_count;
    int             id_data;
    char            status_data[STRING_SIZE];
    unsigned long   str_length;

    //databse connection handle
    MYSQL *con;

    //initialize mysql object for mysql_real_connect() function
    con=mysql_init(NULL);

    if(con==NULL){
    fprintf(stderr,"mysql_init() failed\n");
    exit(1);
    }
    //check if connection is properly established or not
    if(mysql_real_connect(con,HOST,USER,PASS,DB_NAME,PORT,UNIX_SOCKET,FLAG)==NULL)
    {
        fprintf(stderr,"Error [%s]:%s\n",mysql_error(con),mysql_error(con));
        mysql_close(con); //close the connection
        return -1;
    }
    //Prepare an update statement with 3 parameters;
    stmt=mysql_stmt_init(con);
    if(!stmt)
    {
        fprintf(stderr,"mysql_stmt_init() failed, out of the memory\n");
        return -1;

    }

    if(mysql_stmt_prepare(stmt,UPDATE_QUERY,strlen(UPDATE_QUERY)))
    {
        fprintf(stderr,"mysql_stmt_prepare(), UPDATE failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }

    //Get the parameter count from the statement
    param_count=mysql_stmt_param_count(stmt);
    fprintf(stdout,"Total parameters in UPDATE - %d\n",param_count);

    //validate parameter count
    if(param_count!=2)
    {
        fprintf(stderr,"invalid parameter count returned\n");
        return -1;
    }

    //Bind the data for 2 parameters
    memset(bind,0,sizeof(bind));

    //String param
    bind[0].buffer_type=MYSQL_TYPE_STRING;
    bind[0].buffer=(char *)&status_data;
    bind[0].is_null=0;
    bind[0].length=&str_length;
    bind[0].buffer_length=STRING_SIZE;

    //integer id parameter
    bind[1].buffer_type=MYSQL_TYPE_LONG;
    bind[1].buffer=(char *)&id_data;
    bind[1].is_null=0;
    bind[1].length=0;

    //bind the buffers

    if(mysql_stmt_bind_param(stmt,bind))
    {
        fprintf(stderr,"mysql_stmt_bind_param() failed...\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
    }

    id_data=id;
    strncpy(status_data,status,STRING_SIZE);
    str_length=strlen(status_data);

    //Executing the update statement
    if(mysql_stmt_execute(stmt))
    {
        fprintf(stderr,"mysql_stmt_execute() failed\n");
        fprintf(stderr,"[%d]%s\n",mysql_stmt_errno(stmt),mysql_stmt_error(stmt));
        return -1;
    }

    //clsoe the statement
    if(mysql_stmt_close(stmt))
    {
        fprintf(stderr,"mysql_stmt_close() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }

    //getting connection id
    printf("connection id is %ld\n",mysql_thread_id(con));
    printf("Update was successful now closing the connection...\n");
    sleep(2);
    //closing
    mysql_close(con);
    return 1;
   }

// commenting  the main
/*
 int main(int argc ,char ** argv)
 {
    char *status="PROCESSING";
    int id=1;
    update_esb_request(status,id);
    return 0;
 }
*/


