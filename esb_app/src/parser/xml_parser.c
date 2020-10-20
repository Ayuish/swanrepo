#include<stdio.h>
#include<stdlib.h>
//gcc -Wall -I/usr/include/libxml2 -o parsing parsing.c -lxml2
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "xml.h"


bmd parse_bmd_xml(char * bmd_file_path) 
{

    xmlDoc         *document;
    xmlNode        *root, *first_child, *node,*temp;
    char           *filename;
    
   
    filename = bmd_file_path;

    document = xmlReadFile(filename, NULL, 0);
    temp = xmlDocGetRootElement(document);
    root=xmlFirstElementChild(temp);
  
       
    char* arrayValue[8];
    int i=0;
    first_child = root->children;
    for (node = first_child; node; node = node->next) 
    {
            
      if(node->type==1)
        {
            arrayValue[i]=(char*)xmlNodeGetContent(node);
            i++;
        }
    }

    root=xmlLastElementChild(temp);
    first_child = root;
    for (node = first_child; node; node = node->next)
     {
        if(node->type==1)
        {
            arrayValue[i]=(char*)xmlNodeGetContent(node);
            i++;
        }
     }
    
   bmd_envelope envl;
   envl->MessageID = arrayValue[0];
   envl->MessageType = arrayValue[1];
   envl->Sender = arrayValue[2];
   envl->Destination = arrayValue[3];
   envl->CreationDateTime = arrayValue[4];
   envl->Signature = arrayValue[5];
   envl->ReferenceID =arrayValue[6];
  // envl.user_properties = arrayValue[7];
   
   bmd b;
   b.envelop = envl;
   b.payload = arrayValue[7];

 return b;
}

int main() {
 
 bmd b;
// bmd_envelop envl;
 b = parse_bmd_xml("/home/vinay/Desktop/try.xml");
 printf("%s\n",b.envl->MessageID);
// printf("%s",envl.message_id);
 printf("%s\n",b.payload);
}
