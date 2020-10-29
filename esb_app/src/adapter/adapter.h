
#ifndef ADAPTER_H
#define ADAPTER_H


void*  convert_to_json(void* payload, void * name);
void*  ftp_upload(void *asptr, void *fileptr);
void* remove_file(void* ptr,void * ptr1) ;
void* send_mail(void* toptr,void* file_path_ptr);


#endif
