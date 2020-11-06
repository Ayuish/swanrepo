/* Created By Vinay Prabhakar on 6/11/20
    @Brief: Writing test cases for adapter function
*/

#include<stdio.h>
#include<stdlib.h>
#include "../test/munit.h"
#include "adapter.h"


static void* 
send_mail_setup(const MunitParameter params[], void* user_data)
{
    (void )user_data;
    (void)params;
    char* toptr = "2016eeb1081@iitrpr.ac.in";
    char* file_path_ptr="output_first.json";
    char* res=send_mail("2016eeb1081@iitrpr.ac.in","output_first.json");
    return res;
}

static MunitResult
test_send_mail(const MunitParameter params[], void* fixture)
{
    char* res=(char *) fixture;
    (void)params;
    //char* ans=send_mail("vinayprabhakar91@gmail.com","output.json");
    munit_assert_string_equal(res,"Yes email sent");
    return MUNIT_OK;
}

static void 
send_mail_tear_down(void* fixture)
{
    char* res=(char *)fixture;
    free(res);
}

static MunitTest adapter_tests[]={

    {

    //name
    (char *) "/test_email.c/send_mail",
    //test
    test_send_mail,
    //setup
    send_mail_setup,
    //tera down
    send_mail_tear_down,
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


int main(int argc,const char* argv[])
{
    char* user_data= NULL;
    return munit_suite_main(&suite,(void *)user_data, argc,(char* const *)argv);


}
