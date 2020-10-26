/*
Created By Vinay Prabhakar on 26/10/20
@Brief : Under this module we will be accessing database
in order to extract config keyy and value from transport table in
order to apply transportation steps for a suitable destination
service

Command to run is gcc fetch_transport_config_key_and_value.c -L/usr/local/mysql/lib -lmysqlclient -o out

*/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<mysql/mysql.h>
#include "connector.h"

#define STRING_SIZE 500

#define SELECT_SAMPLE "select config_key,config_value from transport_config where id=?"

transport_config* fetch_transport_config_key_and_value(int route_id)
{
    MYSQL           *stmt;
    MYSQL_BIND      input_bind[1];
    unsigned long   input_length;
    int             id;
    MYSQL_BIND      bind[2];
    MYSQL_RES       *prepare_meta_result;
    unsigned long   length[2];
    int             param_count,column_count,row_count;
    short           small_data;
    int             int_data;
    char            str_data[2][STRING_SIZE];
    bool            is_null[2];

    MYSQL*  mysql;
    mysql=mysql_init(NULL);
    if(mysql==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        return NULL;
    }
    if(mysql_real_connect(mysql,HOST,USER,PASS,DB_NAME,PORT,UNIX_SOCKET,FLAG)==NULL)
    {
        fprintf(stderr,"Error [%d] : %s\n",mysql_errno(mysql),mysql_error(mysql));
        return NULL;
    }

    //prepare select query
    stmt=mysql_stmt_init(mysql);
    if(!stmt)
    {
        fprintf(stderr,"mysql_stmt_init() failed\n");
        return NULL;
    }

    if(mysql_stmt_prepare(stmt,SELECT_SAMPLE,strlen(SELECT_SAMPLE)))
    {
        fprintf(stderr,"mysql_stmt_prepare() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return NULL;
    }
    fprintf(stdout,"Prepare SELECT successful\n");

    //get parameters count
    param_count=mysql_stmt_param_count(stmt);
    fprintf(stdout,"total parameters in SELECT :%d\n",param_count);

    if(param_count!=1)
    {
        fprintf(stderr,"invalid param_count returned by fucntion\n");
        return NULL;
    }

    //fetch result set
    prepare_meta_result=mysql_stmt_result_metadata(stmt);
    if(!prepare_meta_result)
    {
        fprintf(stderr,"mysql_stmt_result_metadata(stmt) gave no information\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return NULL;

    }

    //get total columns
    column_count=mysql_num_fields(prepare_meta_result);
    fprintf(stdout,"total columns in select statement: %d\n",column_count);

    if(column_count!=2)
    {
        fprintf(stderr,"incorrect  number of columns returned\n");
        return NULL;
    }

    memset(input_bind,0,sizeof(input_bind));

    //string column
    input_bind[0].buffer_type=MYSQL_TYPE_LONG;
    input_bind[0].buffer=(char *)&id;
    input_bind[0].is_null=0;
    input_bind[0].length=&input_length;

    //bind the buffers
    if(mysql_stmt_bind_param(stmt,input_bind))
    {
        fprintf(stderr,"mysql_stmt_bind_param() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return NULL;
    }
    id=route_id;

    //execute the query
    if(mysql_stmt_execute(stmt))
    {
        fprintf(stderr,"mysql_stmt_execute() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return NULL;
    }

    //bind the result buffer

    memset(bind,0,sizeof(bind));

    //config key column
    bind[0].buffer_type=MYSQL_TYPE_STRING;
    bind[0].buffer=(char *)str_data[0];
    bind[0].buffer_length=STRING_SIZE;
    bind[0].is_null=&is_null[0];
    bind[0].length=&length[0];

    //config value column
    bind[1].buffer_type=MYSQL_TYPE_STRING;
    bind[1].buffer=(char *)str_data[1];
    bind[1].buffer_length=STRING_SIZE;
    bind[1].is_null=&is_null[1];
    bind[1].length=&length[1];

    //bindt the rsult buffer
    if(mysql_stmt_bind_result(stmt,bind))
    {
        fprintf(stderr,"mysql_stmt_bind_result() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return NULL;
    }

    //buffer all results
    if(mysql_stmt_store_result(stmt))
    {
        fprintf(stderr,"mysql_stmt_store_result() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return NULL;
    }

    //fetch all rows
    row_count=0;
    fprintf(stdout,"fetching results ...\n");
    transport_config* tp=(transport_config* )malloc(sizeof(transport_config));
    if(!mysql_stmt_fetch(stmt))
    {
        row_count++;
        fprintf(stdout,"row %d\n",row_count);

        //column1
        fprintf(stdout,"column1 (config_key) : ");
        if(is_null[0])
        {
            fprintf(stdout,"NULL\n");

        }
        else{
            fprintf(stdout,"%s\n",str_data[0]);
            tp->config_key=strdup(str_data[0]);

        }

        //column 2
        fprintf(stdout,"column2 (config_value) : ");
                if(is_null[1])
                {
                    fprintf(stdout,"NULL\n");

                }
                else{
                    fprintf(stdout,"%s\n",str_data[1]);
                    tp->config_key=strdup(str_data[1]);

                }
        ///free the prepared result
        mysql_free_result(prepare_meta_result);

        //close  the statement
        if(mysql_stmt_close(stmt))
        {
            fprintf(stderr,"failed while closing\n");
            fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
            return NULL;
        }
        return tp;
    }

    //validate rows fetched

    //free the metadata
    mysql_free_result(prepare_meta_result);

    //close the statement
    if(mysql_stmt_close(stmt))
    {
        fprintf(stderr,"mysql_stmt_close() failed\n");
        fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
        return NULL;
    }

    return NULL;

}

/*
int main(int argc,char** argv)
{
    int id=1;
    transport_config* tp=fetch_transport_config_key_and_value(id);
    if(tp!=NULL)
    {
        printf("%s \n %s\n", tp->config_key , tp->config_value);
    }
    else{
        printf("No such record found\n");
    }
    return 0;
}
*/