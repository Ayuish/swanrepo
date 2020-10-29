//
// Created by rajashekhar on 29/10/20.
//


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* Contains necessary C functions of mysql */
#include <mysql/mysql.h>

#include "connector.h"
/**
 * Holds the info to connect to DB and
 * error specifying function for
 * databse connection handle
 */

#define STRING_SIZE 1000
#define UPDATE "UPDATE esb_request SET processing_attempts = ? WHERE data_location = ?"

int change_processing_attempts(int processing_attempts,char *data_location) {

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_ulonglong affected_rows;
    unsigned long param_count;
    int processing_attempts_data;
    char data_location_data[STRING_SIZE];
    unsigned long str_length[2];
    bool is_null;

    MYSQL *con; /*database connection handle*/
    /**
     * @brief Allocates and initialises a MYSQL object
     * suitable for mysql_real_connect() function
     *
     */
    con = mysql_init(NULL);

    /**
     * @brief Prints error message incase
     * initialisation of con fails.
     */
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    /**
     * @brief Checks if connection is
     * properly established.
     *
     */
    if (mysql_real_connect(con, HOST, USER, PASS,
                           DB_NAME, PORT, UNIX_SOCKET, FLAG) == NULL)
    {
        printf("Failed to connect to database ");
    }
    /* Prepare an UPDATE query with 9 parameters */
    stmt = mysql_stmt_init(con);
    if (!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        return -1;
    }

    if (mysql_stmt_prepare(stmt, UPDATE, strlen(UPDATE)))
    {
        fprintf(stderr, " mysql_stmt_prepare(), UPDATE failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Get the parameter count from the statement */
    param_count = mysql_stmt_param_count(stmt);
    /*fprintf(stdout, " total parameters in UPDATE: %d\n", param_count);*/

    /* validate parameter count */
    if (param_count != 2)
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        return -1;
    }

    /* Bind the data for all 2 parameters */
    memset(bind, 0, sizeof(bind));

    /* processing_attempts */
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char *)&processing_attempts_data;
    bind[0].is_null = 0;
    bind[0].length = &str_length[0];

    /* data_location */
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)&data_location_data;
    bind[1].buffer_length = STRING_SIZE;
    bind[1].is_null = 0;
    bind[1].length = &str_length[1];

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    processing_attempts_data = processing_attempts;

    strncpy(data_location_data, data_location, STRING_SIZE);
    str_length[1] = strlen(data_location_data);

    /* Execute the UPDATE statement*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute, failed\n");
        fprintf(stderr, " [%d]%s\n", mysql_stmt_errno(stmt),
                mysql_stmt_error(stmt));
        return -1;
    }

    /* Get the total rows affected */
    affected_rows = mysql_stmt_affected_rows(stmt);
    fprintf(stdout, "Total affected rows(UPDATE): %lu\n",
            (unsigned long)affected_rows);

    /* validate affected rows */
    if (affected_rows != 1)
    {
        fprintf(stderr, " invalid affected rows by MySQL\n");
        return -1;
    }

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }


    /*No error occurred and UPDATE is successful*/
    mysql_close(con);
    return 1;

}


/*
int main(int argc, char **argv) {
    int id = change_processing_attempts(0,"bmd.xml");
    printf("id = %d",id);
    return 0;
}
 */
