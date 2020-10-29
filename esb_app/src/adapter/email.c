/* Created By Vinay Prabhakar on 29/10/20
   @Brief: Under this module we will be trying to send 
   .json file(can be some other type) to an email via smtp taking email as 
   our destination service for ESB
   Command to run is : gcc email.c -lcurl -o o
   */

#include<stdio.h>
#include<string.h>
#include<curl/curl.h>
#include "adapter.h"

#define FROM_ADDR "<testmail1@gmail.com>"
#define TO_ADDR   "<testmail2@gmail.com>"
#define CC_ADDR   "<testmail3@gmail.com>"

void* send_mail(void* toptr, void* file_path_ptr)
{
   char* to =(char *)toptr;
   char* file_path=(char *)file_path_ptr;
   printf("===>Sending to %s\n",to);

   CURL* curl;
   CURLcode res=CURLE_OK;
   struct curl_slist *recipients=NULL;
   
   //uplaod_ctx.lines_read=0;

   curl=curl_easy_init();
   if(curl)
   {

      //set username and password
      curl_easy_setopt(curl,CURLOPT_USERNAME,"testmail1");
      curl_easy_setopt(curl,CURLOPT_PASSWORD,"enter_password");
      //url for mail server
      curl_easy_setopt(curl,CURLOPT_URL,"smtps://smtp.gmail.com:465");

      curl_easy_setopt(curl,CURLOPT_USE_SSL,CURLUSESSL_ALL);

      //from
      curl_easy_setopt(curl,CURLOPT_MAIL_FROM,FROM_ADDR);

      //recipients
      recipients=curl_slist_append(recipients,TO_ADDR);
      recipients=curl_slist_append(recipients,CC_ADDR);
      curl_easy_setopt(curl,CURLOPT_MAIL_RCPT,recipients);

      //callback function
      FILE* fp=fopen(file_path,"r");
      curl_easy_setopt(curl,CURLOPT_READDATA,fp);
      curl_easy_setopt(curl,CURLOPT_UPLOAD,1L);

      //send the message
      //res=0 means everything is fine
      res=curl_easy_perform(curl);

      if(res!=CURLE_OK)
      {
         fprintf(stderr,"curl_easy_perform() failed : %s\n", curl_easy_strerror(res));
      }

      //free the list of recipients
      curl_slist_free_all(recipients);

      //cleanup
      curl_easy_cleanup(curl);

   }
   //printf("DONE\n");
   return NULL;
}
/*
int main()
{
      int t=send_mail("testmail1@gmail.com","payload.json");
      printf("%d\n",t);
      return 0;
}
*/