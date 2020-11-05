//
// Created by rajashekhar on 30/10/20.
//


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
#define SELECT_QUERY "SELECT status                               \
FROM esb_request WHERE data_location = ?"

int check_status(char *status, char *data_location) {

    printf("check the status ... \n");
    MYSQL_STMT *stmt; /* store statement */
    MYSQL_BIND input_bind[1]; /* to bind input */
    char data_location_data[STRING_SIZE];
    unsigned long input_length[1];
    MYSQL_BIND bind[1];
    //my_ulonglong affected_rows;
    MYSQL_RES *prepare_meta_result;
    unsigned long param_count,column_count;
    char status_data[STRING_SIZE];
    unsigned long length[1];
    bool is_null[1];


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
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)&status_data;
    bind[0].buffer_length = STRING_SIZE;
    bind[0].is_null = &is_null[0];
    bind[0].length = &length[0] ;

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

    if(!mysql_stmt_fetch(stmt)) {
        if(is_null[0]) {
            fprintf(stdout, "status is not matched\n");
        }else {
            if (strcmp(status_data, status) == 0) {
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
                return 1;
            }
        }
    }else {
        printf("status is not matched \n");
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
    int id = check_status("DONE","/home/rajashekhar/nho2020b2/swan/esb_app/src/test_files/dum2.xml");
    printf("id = %d",id);
    return 0;
}
*/