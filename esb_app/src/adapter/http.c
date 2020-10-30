/* Created By Vinay Prabhakar on 29/10/20
    @Brief: Under this module we will be invoking a public api by passing its key 
    and will be getting response back from it as in callback function
    */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curl/curl.h>
#include "adapter.h"

struct memory{
    char* memory;
    size_t size;
};

static size_t writecallback(void* contents,size_t size, size_t nmemb, void* userp)
{
    size_t realsize=size*nmemb;
    struct memory* mem=(struct memory *)userp;

    char* ptr=realloc(mem->memory,mem->size + realsize+1);
    if(ptr==NULL)
    {
        //out of memory
        printf("not enough memory\n");
        return 0;
    }

    mem->memory=ptr;
    memcpy(&(mem->memory[mem->size]),contents,realsize);

    mem->size+=realsize;
    mem->memory[mem->size]=0;

    return realsize;


}

void* transport_to_ifsc_razorpay(void* ptr,void* ptr1)
{
    char* s=(char *)malloc((strlen(ptr)+strlen(ptr1)+1)*sizeof(char));
    sprintf(s,"%s%s",((char *)ptr),((char *)ptr1));
    printf("Transformation for PO service: %s : %s : %s \n",((char* )ptr),((char *)ptr1),s);

    //curl handle
    CURL *curl;
    CURLcode res;
    struct memory chunk;

    //will grow as needed by realloc above
    chunk.memory=NULL;

    //no data at this point 
    chunk.size=0;

    curl_global_init(CURL_GLOBAL_ALL);

    //curl session
    curl=curl_easy_init();

    //specif url to get 
    curl_easy_setopt(curl,CURLOPT_URL,s);
    //s is url see above

    //send all data to this fucntion
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writecallback);

    //pass chunk struct to callback fucntion
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&chunk);

    //get the result
    res=curl_easy_perform(curl);

    //error handling
    if(res!=CURLE_OK)
    {
        fprintf(stderr,"curl_easy_perform() failed - %s\n",curl_easy_strerror(res));
        return NULL;
    }

    printf("%s\n",chunk.memory);

    //cleanup curl
    curl_easy_cleanup(curl);

    curl_global_cleanup();

    return chunk.memory;
    
}
