/* Created By Vinay Prabhakar on 29/10/20
@Brief : This is the point where we invoke various destinations services
by dynamically calling them
*/

int main()
{
    char* d1=998;
    char*s="Working Fine";
    int d=998;
    char* s1="https://ifsc.razorpay.com/";
    char* s2="IDIB000V086";
    char* file_name=(char *) call_function("APIURL",s1,s2);
    printf("%s\n",file_name);
    char* file=(char *) call_function("convert_to_json",file_name,s2);
    printf("%s\n",file);
    printf("%s\n",(char *) call_function("email","testmail1@gmail.com",file));
    printf("%s\n",(char *) call_function("sftp","test",file));
    printf("%s\n",(char *) call_function("remove",file,NULL));
    

    remove(file);
    free(file_name);
    return 0;
}