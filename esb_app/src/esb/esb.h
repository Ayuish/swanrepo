#include<stdio.h>
#include "../bmd_extract/xml.h"
#include "../db_access/connector.h"



#ifndef ESB_H
#define ESB_H
int process_esb_request(char* bmd_file_path);

//task_node_info* fetch_new_request_from_db();
/*
typedef struct {
    char* sender_id;
    char* destination_id;
    char* message_type;
    // TODO: Other fields
} bmd_envelop;

typedef struct {
    bmd_envelop envelop;
    char* payload;
} bmd;
*/

#endif
