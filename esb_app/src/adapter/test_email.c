/* Created By Vinay Prabhakar on 6/11/20
    @Brief: Writing test cases for adapter function
    to run : gcc test_email.c email.c ../test/munit.c -lcurl -o out

*/

#include<stdio.h>
//#include<stdlib.h>
#include "../test/munit.h"
#include "adapter.h"


static MunitResult
test_send_mail(const MunitParameter params[], void* fixture)
{
    (void)fixture;
    (void)params;
    /* checking the return string for correct sender's email address */
    char* res = send_mail("2016eeb1081@iitrpr.ac.in","output.json");
    munit_assert_string_equal(res,"Yes email sent");
    /* checking the return string for another sender's email address */
    res = send_mail("vinayprabhakar91@gmail.com","output.json");
    munit_assert_string_equal(res,"Yes email sent");
    return MUNIT_OK;
}

static MunitTest adapter_tests[]={

    {

    //name
    (char *) "/test_email.c/send_mail",
    //test
    test_send_mail,
    //setup
    NULL,
    //tera down
    NULL,
    //options
    MUNIT_TEST_OPTION_NONE,
    //parameters
    NULL
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