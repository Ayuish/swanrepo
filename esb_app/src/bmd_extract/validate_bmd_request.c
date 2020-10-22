/* created by Vinay Prabhakar on 22/10/2020
@ brief : validating bmd request
validating bmd request under 4 conditions
1 The mandatory value (Sender , Destination, Message Type etc.) must be present
in the received bmd.
2. For the received record there must be an active route
3. For the selected route record there should be corresponding records present in
 transport_config and transform_config tables
4. We also need to check the payload size for e.g
file larger than 5 MB should not be allowed or are allowed for
certain senders and message types etc.

*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "xml.h"
#include<string.h>
#include "../db_access/connector.h"

int is_bmd_valid(bmd * bd)
{
    printf("%s\n%s\n%s\n",bd->envelope->Sender,bd->envelope->Destination,bd->envelope->MessageType);
    if(validate_xml_file(bd))
    {
        int id=active_routes_from_source(bd->envelope->Sender,bd->envelope->Destination,bd->envelope->MessageType);
        printf("id is %d\n",id);
        if(id>0)
        {
            if(check_id_in_transform_config(id)>=0&& check_id_in_transport_config(id)>=0)
            {
                if(strlen(bd->payload)<=5242880)
                return 1;
            }
        }
    }
    return 0;
    }

    int validate_xml_file(bmd * bmd_file)
    {
        //MessageID
        if(bmd_file->envelope->MessageID==NULL)
        {
            fprintf(stderr,"Message ID does not exist in BMD\n");
            return 0;
        }

        //MessageType
        if(bmd_file->envelope->MessageType ==NULL)
        {
            fprintf(stderr,"MessageType does not exist\n");
            return 0;
        }

        //Sender
        if(bmd_file->envelope->Sender == NULL)
        {
            fprintf(stderr,"Sender does not exist\n");
            return 0;
        }

        //Destination
        if(bmd_file->envelope->Destination == NULL)
        {
            fprintf(stderr,"Destination does not exist\n");
            return 0;
        }

        //CreationDateTime
        if(bmd_file->envelope->CreationDateTime == NULL)
        {
            fprintf(stderr,"CreationDateTime does not exist\n");
            return 0;
        }

        //Signature

        if(bmd_file->envelope->Signature == NULL)
        {
            fprintf(stderr,"Signature does not exist\n");
            return 0;
        }

        //ReferenceID
        if(bmd_file->envelope->ReferenceID == NULL)
        {
            fprintf(stderr,"ReferenceID does not exist\n");
            return 0;
        }

        //payload
        if(bmd_file->payload == NULL)
        {
            fprintf(stderr,"Payload does not exist\n");
            return 0;
        }
        return 1;
    }
