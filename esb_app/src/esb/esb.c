#include<stdio.h>
#include "../adapter/email.h"
#include "esb.h"
//#include "../bmd_extract/xml.h"
#include <libxml/parser.h>
#include <libxml/xpath.h>
/**
 * TODO: This is to be implemented separately.
 */
 
bmd parse_bmd_xml(char* bmd_file_path) {


//
bmd b;
  
  xmlDocPtr load_xml_doc(char *xml_file_path) {
    xmlDocPtr doc = xmlParseFile(xml_file_path);
    if (doc == NULL) {
        fprintf(stderr, "ERROR: Document not parsed successfully. \n");
        return NULL;
    }
    return doc;
  }

/**
 * Extract the nodes matching the given xpath from the supplied
 * XML document object.
 */
xmlXPathObjectPtr get_nodes_at_xpath(xmlDocPtr doc, xmlChar *xpath) {

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        printf("ERROR: Failed to create xpath context from the XML document.\n");
        return NULL;
    }
    xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
    xmlXPathFreeContext(context);
    if (result == NULL) {
        printf("ERROR: Failed to evaluate xpath expression.\n");
        return NULL;
    }
    if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        xmlXPathFreeObject(result);
        printf("No matching nodes found at the xpath.\n");
        return NULL;
    }
    return result;
 }

/**
 * Returns the text value of an XML element. It is expected that
 * there is only one XML element at the given xpath in the XML.
 */
 xmlChar* get_element_text(char *node_xpath, xmlDocPtr doc) {
    xmlChar *node_text;
    xmlXPathObjectPtr result = get_nodes_at_xpath(doc, 
        (xmlChar*)node_xpath);
    if (result) {
        xmlNodeSetPtr nodeset = result->nodesetval;
        if (nodeset->nodeNr == 1) {
            node_text = xmlNodeListGetString(doc,
                nodeset->nodeTab[0]->xmlChildrenNode, 1);
        } else {
            printf("ERROR: Expected one %s node, found %d\n", node_xpath, nodeset->nodeNr);
        }
        xmlXPathFreeObject(result);
    } else {
        printf("ERROR: Node not found at xpath %s\n", node_xpath);
    }
    return node_text;
 }

  
   
   /*
    bmd_envelop envl;
    envl.sender_id = "TEST-GUID-1";
    envl.destination_id = "TEST-GUID-2";
    envl.message_type = "TEST-GUID-3";

    b.envelop = envl;
    b.payload = "Some data here";
    */
    return b;
}
/*
int is_bmd_valid(bmd b)
{
    int valid = 1; // 1 => vaild, -1 => invalid
    // TODO: Implement the validation logic here

    return valid;
}
*/
int queue_the_request(bmd b)
{
    int success = 1; // 1 => OK, -1 => Error cases
    /** 
     * TODO: Insert the envelop data into esb_requests table,
     * and implement other logic for enqueueing the request
     * as specified in Theory of Operation.
     */
    return success;
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* bmd_file_path) {
    int status = 1; // 1 => OK, -ve => Errors
    printf("Handling the BMD %s\n", bmd_file_path);
    /** TODO: 
     * Perform the steps outlined in the Theory of Operation section of
     * the ESB specs document. Each major step should be implemented in
     * a separate module. Suitable unit tests should be created for all
     * the modules, including this one.
     */
    // Step 1:
    bmd b = parse_bmd_xml(bmd_file_path);

    // Step 2:
    if (is_bmd_valid(b)!=1)
    {
        //TODO: Process the error case
        printf("BMD is invalid!\n");
        status = -2;
    }
    else
    {
        // Step 3:
        status = queue_the_request(b);
    }
    
    return status;
}
