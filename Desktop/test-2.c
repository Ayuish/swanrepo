#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* parse (char* xml_string, char* start, char* end){
	
    char* p; 
  
    p = strstr(xml_string, start); 
    int index1=strlen(xml_string)-strlen(p)+strlen(start);
	
	p = strstr(xml_string, end); 
    int index2=strlen(xml_string)-strlen(p);
	
    int len = index2 - index1;

	char *dest = (char*)malloc(sizeof(char) * (len + 1));

	strncpy(dest, (xml_string + index1), len);

	return dest;

	
}
int main() {
    char  var[100];
	char xml[1000];

	strcpy(xml, " ");
    FILE *file;
    file = fopen("bmd.xml","r");
    while(fgets(var, sizeof(var), file)!=NULL){
        strcat(xml,var);
	}
	fclose(file);

    char *list[] = {"<MessageID>","</MessageID>", "<MessageType>", "</MessageType>",
                            "<Sender>", "</Sender>", "<Destination>", "</Destination>",
                            "<CreationDateTime>", "</CreationDateTime>", "<Signature>", "</Signature>",
                            "<ReferenceID>", "</ReferenceID>", "<Payload>", "</Payload>"};

    char *display[] = {"MessageID", "MessageType", "Sender", "Destination", "CreationDateTime",
                    "Signature", "ReferenceID", "Payload"};
    
    int j=0;

    for(int i=0;i<8;i++)
    {
        char *text = parse(xml, list[j], list[j+1]);
        printf("%s = %s",display[i],text);
        printf("\n");
        j = j+2;
    }
    
    return 0;
}
