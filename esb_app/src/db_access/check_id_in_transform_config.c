/*
Created BY Vinay Prabhakar on 23/10/20
Under this : We will be checking whether for a particular route_id
is there a record present in the transformation_config table
so as to apply transformation steps as required by destination service


Command to run is gcc check_id_in_transform_config.c -L/usr/local/mysql/lib -lmysqlclient -o out
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<mysql/mysql.h>
#include "connector.h"

#define SELECT_SAMPLE "select id,route_id,config_key,config_value from transform_config where route_id=?"

#define STRING_SIZE 200

int check_id_in_transform_config(int route_id)
{
    MYSQL_STMT      *stmt;
    MYSQL_BIND      input_bind[1];
    unsigned long   input_length[3];
    MYSQL_BIND      bind[4];
    MYSQL_RES       *prepare_meta_result;
    int id;
    unsigned long   length[4];
    int             param_count, column_count,row_count;
    int             small_data[2];
    char            str_data[2][STRING_SIZE];
    bool            is_null[4];

    MYSQL* mysql=mysql_init(NULL);

    if(mysql==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        return -1;
    }

    //check if connection is established
    if(mysql_real_connect(mysql,HOST,USER,PASS,DB_NAME,PORT,UNIX_SOCKET,FLAG)==NULL)
    {
        fprintf(stderr, "Error [%d]: %s\n",mysql_errno(mysql),mysql_error(mysql));
        //close the connection
        mysql_close(mysql);
        return -1;
    }

    stmt=mysql_stmt_init(mysql);
    if(!stmt){
        fprintf(stderr,"mysql_stmt_init() failed \n");
        exit(0);
    }

    //prepare a select query to extract data from routes_table
    if(mysql_stmt_prepare(stmt,SELECT_SAMPLE,strlen(SELECT_SAMPLE)))
    {
        fprintf(stderr,"mysql_stmt_prepare(),Query failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;

    }

    //get parameter count from the statement
    param_count=mysql_stmt_param_count(stmt);

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

    //get total count
    column_count=mysql_num_fields(prepare_meta_result);

    if(column_count!=4)
    {
        fprintf(stderr,"mysql_nul_fileds() returned wrong count\n");
        return -1;
    }

    memset(input_bind,0,sizeof(input_bind));

    //string column
    input_bind[0].buffer_type=MYSQL_TYPE_LONG;
    input_bind[0].buffer=(char *)&id;
    input_bind[0].is_null=0;
    input_bind[0].length=&input_length[0];

    //binding the buffereds
    if(mysql_stmt_bind_param(stmt,input_bind))
    {
        fprintf(stderr,"mysql_stmt_bind_param() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }

    id=route_id;

    if(mysql_stmt_execute(stmt))
    {
        fprintf(stderr,"mysql_stmt_execute() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }

    //bind the result buffer bofre extracting
         memset(bind,0,sizeof(bind));
    //sender column
         bind[0].buffer_type= MYSQL_TYPE_LONG;
    	 bind[0].buffer= (char *)&small_data[0];
    	 bind[0].is_null= &is_null[0];
    	 bind[0].length= &length[0];

    	 bind[1].buffer_type= MYSQL_TYPE_LONG;
    	 bind[1].buffer= (char *)&small_data[1];
    	 bind[1].is_null= &is_null[1];
    	 bind[1].length= &length[1];

    	 bind[2].buffer_type= MYSQL_TYPE_STRING;
    	 bind[2].buffer= (char *)str_data[0];
    	 bind[2].buffer_length= STRING_SIZE;
    	 bind[2].is_null= &is_null[2];
    	 bind[2].length= &length[2];

    	 bind[3].buffer_type= MYSQL_TYPE_STRING;
    	 bind[3].buffer= (char *)str_data[1];
    	 bind[3].buffer_length= STRING_SIZE;
    	 bind[3].is_null= &is_null[3];
    	 bind[3].length= &length[3];


    //bind the result buffer
    if(mysql_stmt_bind_result(stmt,bind))
    {
        fprintf(stderr,"mysql_stmt_bind_result() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        exit(0);
    }

    //stor the results
    if(mysql_stmt_store_result(stmt))
    {
        fprintf(stderr,"mysql_stmt_store_result(stmt) failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        exit(0);
    }

    //getch rows
    row_count=0;
    while(!mysql_stmt_fetch(stmt))
    {
        row_count++;

        printf("%d\n",small_data[0]);
        printf("%d\n",small_data[1]);
        fprintf(stdout,"%s\t",str_data[0]);
        fprintf(stdout,"%s\t",str_data[1]);

        mysql_free_result(prepare_meta_result);

        //close
        if(mysql_stmt_close(stmt))
        {
            fprintf(stderr,"failed while closing connection\n");
            fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
            return -1;
        }
        return 1;
    }

    //free the rsult metadata
    mysql_free_result(prepare_meta_result);

    //close the statement
    if(mysql_stmt_close(stmt))
    {
        fprintf(stderr,"failed while closing the statement\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return -1;
    }
    mysql_close(mysql);

    return -1;
    }
/*
    int main(int argc ,char **argv)
    {
        int route_id=1;
        int valid_id= check_id_in_transform_config(route_id);
        if(valid_id==1)
        {
            printf("\nYes there is a record present in the transform_config table\n");
        }
        else{
            printf("No record present in transform_config table\n");
        }

        return 0;
}
*/
