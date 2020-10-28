/* Created By Vinay Prabhakar on 28/10/20
@Brief : Under this module we will be accessing a public api using its
key and will be posting on that api use key value pair by POST method

Command to run is : gcc http.c -lcurl -o o
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<curl/curl.h>


int main(void)
{
    CURL* curl;
    CURLcode res;
     curl_global_init(CURL_GLOBAL_ALL);

     //curl handle
     curl=curl_easy_init();
     if(curl)
     {
        //set the url which will be receiving our POST.
        curl_easy_setopt(curl,CURLOPT_URL,"https://reqres.in/api/users");

        //specify data to post at above url
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"name=vinay&job=employed");

        //this command will be giving you internal working of curl
       curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);

        //perform the request
        res=curl_easy_perform(curl);

        //error checking
        if(res!=CURLE_OK)
        {
            fprintf(stderr,"curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

            //cleanup
            curl_easy_cleanup(curl);
        }

       curl_global_cleanup();
       return 0;
     }

}