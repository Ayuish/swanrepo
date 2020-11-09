/* Created By Vinay Prabhakar on 9/11/20
    @Brief: Under this module we will be cretaing test case
    for sftp as destination service
*/

#include<stdio.h>
#include<stdlib.h>
#include "../test/munit.h"
#include "adapter.h"

#define UPLOAD_FILE_AS  "output_first.json"
#define REMOTE_URL "sftp://127.0.0.1/sftpuser/sftp-test/"



static void*
sftp_upload_setup(const MunitParameter params[], void* user_data)
{
    (void) user_data;
    (void) params;
    char* res=sftp_upload(UPLOAD_FILE_AS,"output_first.json");
    return res;
}

static MunitResult
test_sftp_upload(const MunitParameter params[], void* fixture)
{
    char* res=(char *) fixture;
    (void) params;
    munit_assert_string_equal(res,"YES file sent to sftp server");
    return MUNIT_OK;
}

static void*
sftp_upload_tear_down(void* fixture)
{
    char* res=(char *) fixture;

}


static void*
sftp_upload2_setup(const MunitParameter params[], void* user_data)
{
    (void) user_data;
    (void) params;
    char* res=sftp_upload(UPLOAD_FILE_AS,"output_last.json");
    return res;
}

static MunitResult
test_sftp_upload2(const MunitParameter params[], void* fixture)
{
    char* res=(char *) fixture;
    (void) params;
    munit_assert_string_not_equal(res,"Yes file sent to sftp server");
    return MUNIT_OK;
}

static void*
sftp_upload2_tear_down(void* fixture)
{
    char* res=(char *) fixture;

}





static MunitTest adapter_tests[]={

    {

    //name
    (char *) "/test_sftp.c/sftp_upload",
    //test
    test_sftp_upload,
    //setup
    sftp_upload_setup,
    //tera down
    sftp_upload_tear_down,
    //options
    MUNIT_TEST_OPTION_NONE,
    //paramters
    //NULL
    },

    {

    //name
    (char *) "/test_sftp.c/sftp_upload2",
    //test
    test_sftp_upload2,
    //setup
    sftp_upload2_setup,
    //tera down
    sftp_upload2_tear_down,
    //options
    MUNIT_TEST_OPTION_NONE,
    //paramters
    //NULL
    },


    


    //mark the end of array with an entry where the test function is nul
    {
        NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL
    }

};


static const MunitSuite suite={

    //name
    "/adapter_tests",

    //array of test
    adapter_tests,

    //suites
    NULL,

    //iterations
    1,

    //options
    MUNIT_SUITE_OPTION_NONE

};


/*
int main(int argc,const char* argv[])
{
    char* user_data= NULL;
    return munit_suite_main(&suite,(void *)user_data, argc,(char* const *)argv);


}
*/