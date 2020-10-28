/* Created By Vinay Prabhakar on 28/10/20
 @Brief: Under this module we create a json file containing
 payload data and returns the path of the file.
 */

 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include "adapter.h"

 void* convert_to_json(void* payload, void* name)
 {
    printf("Payload to json ...\n");
    char bmd_name[50];

    //create file name
    char file[50];
    sprintf(file,"output_%s.json",(char *)name);

    FILE* fp;
    //open file in oreder to write
    fp=fopen(file,"w");
    if(fp==NULL)
    {
        printf("File opening failed\n");
        return NULL;
    }

    //write into json file
    fprintf(fp,"%s\n",(char *)payload);

    //close the file
    fclose(fp);

    //return json file
    return strdup(file);
 }

 int main()
 {
    convert_to_json("001-01-1234","First ");
    return 0;
 }