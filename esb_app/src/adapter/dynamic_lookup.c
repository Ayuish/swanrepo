/* Created By Vinay Prabhakar on 29/10/20
    @Brief : Under this module we will be creating a pre requisite 
    which we can use later while calling functions dyanmically
    and you may need to add more functions as project proceeds
    */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<curl/curl.h>
#include "adapter.h"

void* remove_file(void* ptr, void* ptr1)
{
    remove(((char *)ptr));
    return "Yes Successfully removed the file";
}

//esb would have this table

const static struct {
    const char* name;
    void* (*func)(void*, void*);
}

function_map[]={
    {"APIURL",transport_to_ifsc_razorpay},
    {"email",send_mail},
    {"convert_to_json",convert_to_json},
    {"remove",remove_file},
    {"sftp",sftp_upload},
};

//following is the description that how esb can invoke the service adapter functions

char* call_function(const char* name,void* data,void* data1)
{
    for(int i=0;i<(sizeof(function_map)/sizeof(function_map[0]));i++)
    {
        if(!strcmp(function_map[i].name,name)&& function_map[i].func)
        {
            return function_map[i].func(data,data1);
        }
    }
    return "NO Dynamic Calling Failed";
}
