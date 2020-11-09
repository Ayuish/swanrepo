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

#define FROM_ADDR "kucharlar@gmail.com"
#define TO_ADDR   "2016eeb1081@iitrpr.ac.in"
//#define CC_ADDR   "vinayprabhakar91@gmail.com"



void* send_mail(void* toptr, void* file_path_ptr)
{
   char* to =(char *)toptr;
   //printf("%s\n",to);

   char ans[50];
   int i = 0;
   while(FROM_ADDR[i] != '@') {
      ans[i] =  FROM_ADDR[i];
      i++;
   }
   for(;i<50;i++) {
   ans[i] = '\0';
   }
   printf("%s\n",ans);

  // printf("%s\n",ans);
   char* file_path=(char *)file_path_ptr;
   printf("===>Sending to %s\n",to);
   printf("File is %s\n",file_path);

   CURL* curl;
   CURLcode res=CURLE_OK;
   struct curl_slist *recipients=NULL;
   
  

   curl=curl_easy_init();
   if(curl)
   {

      //set username and password
      curl_easy_setopt(curl,CURLOPT_USERNAME, ans);// put username of sender's email
      curl_easy_setopt(curl,CURLOPT_PASSWORD,"Kucharla@1");
      //url for mail server
      curl_easy_setopt(curl,CURLOPT_URL,"smtps://smtp.gmail.com:465");

      curl_easy_setopt(curl,CURLOPT_USE_SSL,CURLUSESSL_ALL);

      //from
      curl_easy_setopt(curl,CURLOPT_MAIL_FROM,FROM_ADDR);

      //recipients
      recipients=curl_slist_append(recipients,to);
      
     // recipients=curl_slist_append(recipients,CC_ADDR);
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
         return "Sending failed\n";
      }

      //free the list of recipients
      curl_slist_free_all(recipients);

      //cleanup
      curl_easy_cleanup(curl);

   }
   else
   {
   	printf("Could not send the mail\n");
   }
   //printf("DONE\n");
   return "Yes email sent";
}

/*
int main()
{
      char* t=send_mail("2016eeb1081@iitrpr.ac.in","output.json");
      printf("%s\n",t);
      return 0;
}
*/
