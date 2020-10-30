/* Created By Vinay Prabhakar on 28/10/20
 @Brief: Under this module we will be creating a local sftp user on local host
 as a destination service to upload our .json file for further integration
 Command to run on terminal is : gcc sftp.c -lcurl -o o
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<curl/curl.h>
#include<sys/types.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#ifdef WIN32
#include<io.h>
#else
#include<unistd.h>
#endif

#define UPLOAD_FILE_AS  "payload.json"
#define REMOTE_URL "sftp://127.0.0.1/sftpuser/sftp-test/"

#define STRING_SIZE 100

static size_t read_callback(void* ptr, size_t size,size_t nmemb,void* stream)
{
    //For any given platform/compiler curl_off_t must be typedef'ed to a 64-bit wide signed integral data type
    curl_off_t nread;

    size_t retcode=fread(ptr,size,nmemb,stream);

    nread=(curl_off_t)retcode;

    fprintf(stderr,"++++ We read (this many bytes) % " CURL_FORMAT_CURL_OFF_T"bytes from the file\n",nread);
    return retcode;

}

void* sftp_upload(void* asptr,void* fileptr)
{
    //it should be unique in order to identify
    char* as=(char *)asptr;
    char* file=(char *)fileptr;
    CURL *curl;
    CURLcode res;
    FILE* fp;
    struct stat file_info;
    curl_off_t fsize;

    struct curl_slist *headerlist=NULL;

    //getting the size of the local file
    if(stat(file,&file_info))
    {
        printf("Could not open '%s': %s\n",file,strerror(errno));
        return strdup("Failed to open the file\n");
    }

    //size
    fsize=(curl_off_t)file_info.st_size;

    printf("Local file size: % " CURL_FORMAT_CURL_OFF_T "bytes .\n", fsize);

    //getting the file for reading only
    fp=fopen(file,"rb");

    curl_global_init(CURL_GLOBAL_ALL);

    //get curl
    curl=curl_easy_init();
    if(curl)
    {
        //make a list of the command to pass to libcurl for smooth execution
        curl_easy_setopt(curl,CURLOPT_READFUNCTION,read_callback);

        //enable uploading of the file
        curl_easy_setopt(curl,CURLOPT_UPLOAD,1L);

        //creating the target
        char url[STRING_SIZE];
        strcpy(url,REMOTE_URL);
        strcat(url,as);

        //specify the target
        curl_easy_setopt(curl,CURLOPT_URL,url);

        //now specifying the file to upload
        curl_easy_setopt(curl,CURLOPT_READDATA,fp);

        //set size of file to upload in case of large make sure argument passed to CURLOPT_INFILESIZE to be large
        curl_easy_setopt(curl,CURLOPT_INFILESIZE_LARGE,(curl_off_t)fsize);

        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0L);
        curl_easy_setopt(curl,CURLOPT_USERPWD,"sftpuser:prabhakars 589b");
	//this command us shows the internal working of curl step by step
        //curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);

        //initating the start for curl
        res=curl_easy_perform(curl);

        //check for errors
        if(res!=CURLE_OK)
        {
            fprintf(stderr,"curl_easy_perform() failed - %s\n",curl_easy_strerror(res));
            return "NO";
        }

        //cleaning sftp commands
        curl_slist_free_all(headerlist);

        //cleanup
        curl_easy_cleanup(curl);
    }
    //close the file
    fclose(fp);
    curl_global_cleanup();
    return "YES file sent to sftp server";
}

//commenting the main
/*
int main()
{
    sftp_upload(UPLOAD_FILE_AS,"output_first.json");
    return 0;
}
*/
