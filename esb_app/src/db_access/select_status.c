/*
Created By Vinay Prabhakar on 26/10/20
Under this : we will be accessing database to get the details of the
id where status has some particular value (e.g Processing or done or error)
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<mysql/mysql.h>
#include "connector.h"
#include<time.h>

#define STRING_SIZE 1000

#define SELECT_SAMPLE "select * from esb_request where status= ?"

int select_status(char* status)
{
    MYSQL_STMT      *stmt;
    MYSQL_RES       *prepare_meta_result;
    MYSQL_TIME       ts;
    MYSQL_BIND       input_bind[1];
    unsigned long    input_length;
    char             input_data[STRING_SIZE];
    MYSQL_BIND       bind[10];
    int              param_count,column_count,row_count;
    int              id;
    char             int_data[8][STRING_SIZE];
    unsigned long    str_length[10];
    bool             is_null[2];

    MYSQL *mysql=mysql_init(NULL);
    if(mysql==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        return -1;
    }

    if(mysql_real_connect(mysql,HOST,USER,PASS,DB_NAME,PORT,UNIX_SOCKET,FLAG)==NULL)
    {
    fprintf(stderr,"Error [%d] : %s\n",mysql_errno(mysql),mysql_error(mysql));
    return -1;
    }
    stmt=mysql_stmt_init(mysql);
    if(!stmt)
    {
        fprintf(stderr,"mysql_stmt_init() failed\n");
        return -1;
    }

    //prepare select query
    if(mysql_stmt_prepare(stmt,SELECT_SAMPLE,strlen(SELECT_SAMPLE)))
    {
        fprintf(stderr,"mysql_stmt_prepare() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }
    fprintf(stdout,"SELECT query successful\n");

    //get parameter count
    param_count=mysql_stmt_param_count(stmt);
    fprintf(stdout,"total parameters in SELECT: %d\n",param_count);

    if(param_count!=1)
    {
        fprintf(stderr,"invalid parameter count\n");
        return -1;
    }

    //fetch result set
    prepare_meta_result=mysql_stmt_result_metadata(stmt);
    if(!prepare_meta_result)
    {
        fprintf(stderr,"mysql_stmt_result_metadata() gave no information\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }

    //get total columns
    column_count=mysql_num_fields(prepare_meta_result);
    fprintf(stdout,"total columns in SELECT sample: %d\n",column_count);
    if(column_count!=10)
    {
        fprintf(stderr,"invalid column count returned by MYSQL\n");
        return -1;
    }

    memset(input_bind,0,sizeof(input_bind));

    //string column
    input_bind[0].buffer_type=MYSQL_TYPE_STRING;
    input_bind[0].buffer=(char *)input_data;
    input_bind[0].buffer_length=STRING_SIZE;
    input_bind[0].length=&input_length;

    //bind the buffers

    if(mysql_stmt_bind_param(stmt,input_bind))
    {
        fprintf(stderr,"mysql_stmt_bind_param() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }

    strncpy(input_data,status,STRING_SIZE);
    input_length=strlen(input_data);

    if(mysql_stmt_execute(stmt))
    {
        fprintf(stderr,"mysql_stmt_execute , failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }

    //bind the result buffers for aa columns

    memset(bind,0,sizeof(bind));

    //integer param for id
    bind[0].buffer_type=MYSQL_TYPE_LONG;
    bind[0].buffer=(char *)&id;
    bind[0].is_null;
    bind[0].length=&str_length[0];

     /* STRING PARAM */
     bind[1].buffer_type= MYSQL_TYPE_STRING;
     bind[1].buffer= (char *)&int_data[0];
     bind[1].is_null= 0;
     bind[1].length= &str_length[1];
     bind[1].buffer_length= STRING_SIZE;


     /* STRING PARAM */
     bind[2].buffer_type= MYSQL_TYPE_STRING;
     bind[2].buffer= (char *)&int_data[1];
     bind[2].is_null= 0;
     bind[2].length= &str_length[2];
     bind[2].buffer_length= STRING_SIZE;


     /* STRING PARAM */
     bind[3].buffer_type= MYSQL_TYPE_STRING;
     bind[3].buffer= (char *)&int_data[2];
     bind[3].is_null= 0;
     bind[3].length= &str_length[3];
     bind[3].buffer_length= STRING_SIZE;


     /* STRING PARAM */
     bind[4].buffer_type= MYSQL_TYPE_STRING;
     bind[4].buffer= (char *)&int_data[3];
     bind[4].is_null= 0;
     bind[4].length= &str_length[4];
#include <stdio.h>
#include <string.h>

/* Contains necessary C functions of mysql */
#include <mysql/mysql.h>
/**
 * Holds the info to connect to DB and
 * error specifying function for
 * database connection handle
 */
#include "connector.h"

#define STRING_SIZE 100
#define SELECT_QUERY "SELECT processing_attempts                                 \
FROM esb_request WHERE data_location = ?"

int get_processing_attempts(char *data_location) {

    printf("getting the number of processing attempts\n");
    MYSQL_STMT *stmt; /* store statement */
    MYSQL_BIND input_bind[1]; /* to bind input */
    char data_location_data[STRING_SIZE];
    unsigned long input_length[1];
    MYSQL_BIND bind[1];
    //my_ulonglong affected_rows;
    MYSQL_RES *prepare_meta_result;
    unsigned long param_count,column_count;
    int int_data;
    unsigned long length[1];
    bool is_null[1];
    bool error[1];


    MYSQL *con; /*database connection handle*/
    /**
   * @brief Allocates or initialises a MYSQL object
   * suitable for mysql_real_connect() function
   *
   */
    con = mysql_init(NULL);

    /**
   * @brief Prints error message incase
   * initialisation of con fails.
   */
    if (con == NULL) {

        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    /**
   * @brief Checks if connection is
   * properly established.
   *
   */
    if (mysql_real_connect(con, HOST, USER, PASS,DB_NAME,
                           PORT, UNIX_SOCKET, FLAG) == NULL) {
        printf("Failed to connect to database");
    }

    stmt = mysql_stmt_init(con);
    if (!stmt) {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        return -1;
    }

    if (mysql_stmt_prepare(stmt, SELECT_QUERY, strlen(SELECT_QUERY))) {
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Get the parameter count from the statement */
    param_count = mysql_stmt_param_count(stmt);

    /* validate parameter count */
    if (param_count != 1) {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        return -1;
    }

    /* Fetch result set meta information */
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result) {
        fprintf(stderr,"mysql_stmt_result_metadata(),           \
        returned no meta information\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }


    memset(input_bind, 0, sizeof(input_bind));

    /* data_location data*/
    input_bind[0].buffer_type = MYSQL_TYPE_STRING;
    input_bind[0].buffer = (char *)data_location_data;
    input_bind[0].buffer_length = STRING_SIZE;
    input_bind[0].is_null = 0;
    input_bind[0].length = &input_length[0];


    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, input_bind))  {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Copy input data from function parameters */
    strncpy(data_location_data, data_location, STRING_SIZE);
    input_length[0] = strlen(data_location_data);

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }


    /*Get total coulumns in the query */
    column_count = mysql_num_fields(prepare_meta_result);
    fprintf(stdout, "total columns in SELECT statement : %lu \n",column_count);

    /* validate column count */
    if(column_count != 1) {
        fprintf(stderr,"invalid column count returned by MySQL\n");
        return -1;
    }

    /* Bind the result buffers for all 1 columns before fetching them */

    memset(bind, 0, sizeof(bind));

    /*  route_id */
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char *)&int_data;
    bind[0].is_null = &is_null[0];
    bind[0].length = &length[0] ;
    bind[0].error = &error[0];

    /* Bind the result buffers */
    if (mysql_stmt_bind_result(stmt, bind)) {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Now buffer all results to client */
    if (mysql_stmt_store_result(stmt))  {
        fprintf(stderr, " mysql_stmt_store_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    int processing_attempts;

    if(!mysql_stmt_fetch(stmt)) {
        if(!is_null[0]) {
            processing_attempts = int_data;
        }else {
            fprintf(stdout, "route_id is NULL\n");
        }
        /* Free the result */
        mysql_free_result(prepare_meta_result);

        /* Close the statement */
        if (mysql_stmt_close(stmt)) {
            fprintf(stderr, " failed while closing the statement\n");
            fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
            return -1;
        }
        /*closes the database connection*/
        mysql_close(con);

        return processing_attempts;
    }else{
        printf("No routes found..\n");
    }

    /* Free the prepared result metadata */
    mysql_free_result(prepare_meta_result);

    /* Close the statement */
    if (mysql_stmt_close(stmt)) {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /*closes the database connection*/
    mysql_close(con);
    /* returns number of rows in result */
    return -1;
}
/*
int main(int argc, char **argv) {
    int id = get_processing_attempts("bmd.xml");
    printf("id = %d",id);
    return 0;
}
*/


     bind[4].buffer_length= STRING_SIZE;


     /* STRING PARAM */
     bind[5].buffer_type= MYSQL_TYPE_STRING;
     bind[5].buffer= (char *)&int_data[4];
     bind[5].is_null= 0;
     bind[5].length= &str_length[5];
     bind[5].buffer_length= STRING_SIZE;


     /* DATETIME PARAM */
     bind[6].buffer_type= MYSQL_TYPE_DATETIME;
     bind[6].buffer= (char *)&ts;
     bind[6].is_null= 0;
     bind[6].length= &str_length[6];



     /* STRING PARAM */
     bind[7].buffer_type= MYSQL_TYPE_STRING;
     bind[7].buffer= (char *)&int_data[5];
     bind[7].is_null= &is_null[0];
     bind[7].length= &str_length[7];
     bind[7].buffer_length= STRING_SIZE;


     /* STRING PARAM */
     bind[8].buffer_type= MYSQL_TYPE_STRING;
     bind[8].buffer= (char *)&int_data[6];
     bind[8].is_null= 0;
     bind[8].length= &str_length[8];
     bind[8].buffer_length= STRING_SIZE;

     /* STRING PARAM */
     bind[9].buffer_type= MYSQL_TYPE_STRING;
     bind[9].buffer= (char *)&int_data[7];
     bind[9].is_null= &is_null[1];
     bind[9].length= &str_length[9];
     bind[9].buffer_length= STRING_SIZE;

     //bind the result buffers
     if(mysql_stmt_bind_result(stmt,bind))
     {
        fprintf(stderr,"mysql_stmt_bind_result() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
     }

     //now buffer all results
     if(mysql_stmt_store_result(stmt))
     {
        fprintf(stderr,"mysql_stmt_store_result() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
     }

     //fetch all rows
     row_count=0;
     fprintf(stdout,"Fetching Results...\n");
     printf("Header --> id sender_id dest_id message_type reference_id message_id received_on\t data_location status status_details\n");
     int row_id;
     while(!mysql_stmt_fetch(stmt))
     {
        row_count++;
        row_id=id;
        fprintf(stdout,"row %d : -->", row_count);

        //column1
        fprintf(stdout,"%d\t",id);

        //column2
        fprintf(stdout,"%s\t",int_data[0]);

        //cloumn3
        fprintf(stdout,"%s\t",int_data[1]);

        //column4
        fprintf(stdout,"%s\t",int_data[2]);

        //column5
        fprintf(stdout,"%s\t",int_data[3]);

        //column6
        fprintf(stdout,"%s\t",int_data[4]);

        //column7
        fprintf(stdout, " %04d-%02d-%02d %02d:%02d:%02d \t",ts.year, ts.month, ts.day,
        							   ts.hour, ts.minute, ts.second);

        //column8
        if(is_null[0])
        {
            fprintf(stdout,"NULL\t");
        }
        else{
            fprintf(stdout,"%s\t",int_data[5]);
        }
        //column9
        fprintf(stdout,"%s\t",int_data[6]);

        //column10
        if(is_null[1])
        {
            fprintf(stdout,"NULL\t");
        }
        else{
            fprintf(stdout,"%s\t",int_data[7]);
        }

        printf("\n");
     }

     //validate rows fetched

     fprintf(stdout,"total rows fetched are : %d\n",row_count);

     //free metadata
     mysql_free_result(prepare_meta_result);

     //close
     if(mysql_stmt_close(stmt))
     {
        fprintf(stderr,"failed while closing  the statement\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
     }

     mysql_close(mysql);
     if(row_count>0)
     {
        return row_id;

     }
     return -1;
}
/*
int main(int argc, char** argv)
{
    char* status="PROCESSING";
    select_status(status);
    return 0;
}
 */
