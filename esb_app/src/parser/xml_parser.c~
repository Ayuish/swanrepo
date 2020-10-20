/*
BMD XML document parsing
navigate through XML document and stroe the content in it .
Parse a XML to a tree , use xmlDocGetRootElement() to get the root element
then walk through the document and store all element name in a bmd_message struct
*/

#include<stdio.h>
#include<libxml/parser.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include "xml.h"

char * attributes[7]={
    "MessageID",
    "MessageType",
    "Sender",
    "Destination",
    "CreationDateTime",
    "Signature",
    "ReferenceID"
};

//checking whether is a leaf node generated or not

int is_leaf(xmlNode *node)
{
    xmlNode * child=node->children;
    while(child)
    {
        if(child->type==XML_ELEMENT_NODE){
            return 0;
        }
        child=child->next;
    }
    return 1;
}

/*extracting contents from a XML document and stroing
and if node type id element it is leaf
*/

void extract_envelope_utils(xmlNode * node,bmd_envelope* bm)
{
    int n;
    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
            if(is_leaf(node))
            {
                n=strlen((char*)xmlNodeGetContent(node));
                //MessageId
                if((strcmp(((char *)node->name),attributes[0]))==0)
                {
                    bm->MessageID=malloc((n+1)*sizeof(char));
                    strcpy(bm->MessageID,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm->MessageID,"")==0)
                    {
                        bm->MessageID=NULL;
                    }
                }

                //MessageType
                else if((strcmp(((char *)node->name),attributes[1]))==0)
                {
                    bm->MessageType=(char *)malloc((n+1)*sizeof(char));
                    strcpy(bm->MessageType,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm->MessageType,"")==0)
                    {
                        bm->MessageType=NULL;
                    }
                }

                //Sender
                else if((strcmp(((char *)node->name),attributes[2]))==0)
                {
                    bm->Sender =(char *)malloc((n+1)*sizeof(char));
                    strcpy(bm->Sender,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm->Sender,"")==0)
                    {
                        bm->Sender=NULL;
                    }
                }
                
                //Destination
                else if((strcmp(((char *)node->name),attributes[3]))==0)
                {
                    bm->Destination=(char *)malloc((n+1)*sizeof(char));
                    strcpy(bm->Destination,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm->Destination,"")==0)
                    {
                        bm->Destination=NULL;
                    }
                }

                //CreationDateTime
                else if((strcmp(((char *)node->name),attributes[3]))==0)
                {
                    bm->CreationDateTime=(char *)malloc((n+1)*sizeof(char));
                    strcpy(bm->CreationDateTime,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm->CreationDateTime,"")==0)
                    {
                        bm->CreationDateTime=NULL;
                    }

                }

                //Signature
                else if((strcmp(((char *)node->name),attributes[6]))==0)
                {
                    bm->Signature=(char *)malloc((n+1)*sizeof(char));
                    strcpy(bm->Signature,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm->Signature,"")==0)
                    {
                        bm->Signature=NULL;
                    }
                }

                //ReferenceID
                else if((strcmp(((char *)node->name),attributes[7]))==0)
                {
                    bm->ReferenceID=(char *)malloc((n+1)*sizeof(char));
                    strcpy(bm->ReferenceID,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm->ReferenceID,"")==0)
                    {
                        bm->ReferenceID=NULL;
                    }
                }

            }
        }
        extract_envelope_utils(node->children,bm);
        node=node->next;
    }
}


//extarcting bmd_envelope

bmd_envelope * extract_envelope(char * filepath)
{
    xmlDoc *doc=NULL;
    xmlNode *root_element = NULL;

    //parse the file
    doc=xmlReadFile(filepath,NULL,0);

    if(doc==NULL)
    {
        printf("Could not parse the XML file \n");
    }
    
    //getting root element node
    bmd_envelope * bm=(bmd_envelope *)malloc(sizeof(bmd_envelope));
    root_element=xmlDocGetRootElement(doc);

    extract_envelope_utils(root_element,bm);

    //free the document
    xmlFreeDoc(doc);

    //free the variables which were defined globally
    xmlCleanupParser();
    return bm;
}

/* extracting payload from xml file */
bmd * parse_bmd_xml(char * filepath)
{
    printf("XML Parsing\n");
    bmd * bd=(bmd *)malloc(sizeof(bmd));
    bd->envelope=extract_payload(filepath);
    bd->payload=extract_payload(filepath);
    printf("Payload is working fine\n");
    return bd;
}

char * extract_payload(char * filepath)
{
    xmlDoc *doc=NULL;
    xmlNode *root_element=NULL;
    char * Payload;
    //parse tgge file
    doc=xmlReadFile(filepath,NULL,0);

    if(doc==NULL)
    {
        printf("Could not parse the XML file\n");
    }
    root_element=xmlDocGetRootElement(doc);
    int n;
    xmlNode * node=root_element->children;
    while(node)
    {
        if(node->type==XML_ELEMENT_NODE)
        {
            if(is_leaf(node))
            {
                if((strcmp(((char *)node->name),"Payload"))==0)
                {
                    n=strlen((char*)xmlNodeGetContent(node));
                    printf("Payload length is %d\n",n);
                    Payload=(char *)malloc((n+2)*sizeof(char));
                    printf("%s\n",(char *)xmlNodeGetContent(node));
                    strcpy(Payload,(char *)xmlNodeGetContent(node));
                    printf("Payload is %s\n",Payload);
                    if(n==0)
                    {
                        Payload=NULL;
                    }
                    return Payload;
                }
            }
        }
        node=node->next;
    }

    //free the doc
    xmlFreeDoc(doc);

    xmlCleanupParser();
    printf("Completed\n");
    return NULL;
    }


    int main()
    {
        char filepath[100]="home/vinay/Desktop/recieved.xml";
        bmd *bd=(bmd *)malloc(sizeof(bmd));
        bd=parse_bmd_xml(filepath);
        printf("\n");
        return 0;
    }
