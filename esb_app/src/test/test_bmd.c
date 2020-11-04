/* Created By Vinay Prabhakar on 4/11/20 
    @Brief : Under this module we will be creating test cases for 
    is_bmd_valid() function and parse_bmd_xml() function.
It is highly recommended to have some prior knowledge to munit framework 
before going into testing
*/


#include<stdio.h>
#include "munit.h"
#include <stdlib.h>
#include "../bmd_extract/xml.h"
#include "../esb/esb.h"

//disabling MSCV warning about conditional expressions being constant
//like assert that 0!=1 for testing purposes

#if defined(_MS_VER)
#pragma warning(disable: 4127)
#endif

static MunitResult
test_xml_values(const MunitParameter params[], void* user_data)
{
    const char* foo;
    (void) user_data;
    
    /*foo paramter is specified as one of following
    one , two , three
    */
   foo=munit_parameters_get(params,"foo");

   //bar is one of the given : four , ,five , six
   //bar=munit_parameters_get(params,"bar");

   /* Notice that we're returning MUNIT_FAIL instead of writing an
   * error message.  Error messages are generally preferable, since
   * they make it easier to diagnose the issue, but this is an
   * option.
   *
   * Possible values are:
   *  - MUNIT_OK: Sucess
   *  - MUNIT_FAIL: Failure
   *  - MUNIT_SKIP: The test was skipped; usually this happens when a
   *    particular feature isn't in use.  For example, if you're
   *    writing a test which uses a Wayland-only feature, but your
   *    application is running on X11.
   *  - MUNIT_ERROR: The test failed, but not because of anything you
   *    wanted to test.  For example, maybe your test downloads a
   *    remote resource and tries to parse it, but the network was
   *    down.
   */

  printf("%s\n",(char* )foo);

  bmd* test_bmd=parse_bmd_xml(foo);

  printf("Testing parse_bmd_xml() function\n");

  printf("%s\n",test_bmd->envelope->MessageID);

  if(strcmp(foo,"../test_files/dum1.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }
  
  if(strcmp(foo,"../test_files/dum2.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"B9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DB");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:19:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"HDFC0CAGSBK");
  }

 if(strcmp(foo,"../test_files/dum3.xml")==0)
 {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"C9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DC");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:19:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1239");
 }

 if(strcmp(foo,"../test_files/test_xml_handle/dum.xml")==0)
 {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
 }

 if(strcmp(foo,"../test_files/test_xml_handle/dum1.xml")==0)
 {
    munit_assert_null(test_bmd->envelope->MessageID);
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
 }

  if(strcmp(foo,"../test_files/test_xml_handle/dum2.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_null(test_bmd->envelope->MessageType);
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }

  if(strcmp(foo,"../test_files/test_xml_handle/dum3.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_null(test_bmd->envelope->Sender);
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }

   if(strcmp(foo,"../test_files/test_xml_handle/dum4.xml")==0)
   {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_null(test_bmd->envelope->Destination);
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
   }

   if(strcmp(foo,"../test_files/test_xml_handle/dum5.xml")==0)
   {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_null(test_bmd->envelope->CreationDateTime);
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
   }

   if(strcmp(foo,"../test_files/test_xml_handle/dum6.xml")==0)
   {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_null(test_bmd->envelope->Signature);
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
   }

   if(strcmp(foo,"../test_files/test_xml_handle/dum7.xml")==0)
   {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_null(test_bmd->envelope->ReferenceID);
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
   }

   if(strcmp(foo,"../test_files/test_xml_handle/dum8.xml")==0)
   {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_null(test_bmd->payload);
   }

   // if evrything above goes fine then it will return OK in the console
   return MUNIT_OK;
}

static MunitResult
test_xml_valid(const MunitParameter params[], void* user_data)
{
    const char* foo;
    (void) user_data;

    //again foo paramter is specified as one of the xml files
    foo=munit_parameters_get(params,"foo");

/* Notice that we're returning MUNIT_FAIL instead of writing an
   * error message.  Error messages are generally preferable, since
   * they make it easier to diagnose the issue, but this is an
   * option.
   *
   * Possible values are:
   *  - MUNIT_OK: Sucess
   *  - MUNIT_FAIL: Failure
   *  - MUNIT_SKIP: The test was skipped; usually this happens when a
   *    particular feature isn't in use.  For example, if you're
   *    writing a test which uses a Wayland-only feature, but your
   *    application is running on X11.
   *  - MUNIT_ERROR: The test failed, but not because of anything you
   *    wanted to test.  For example, maybe your test downloads a
   *    remote resource and tries to parse it, but the network was
   *    down.
   */

    printf("%s\n",(char* )foo);

    bmd* test_bmd=parse_bmd_xml(foo);

    printf("Testing parse_bmd_xml() function\n");
    printf("%s\n",test_bmd->envelope->MessageID);

    if(strcmp(foo,"../test_files/dum1.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,1);
    }

    if(strcmp(foo,"../test_files/dum2.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,1);

    }

    if(strcmp(foo,"../test_files/dum3.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,1);
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,1);        
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum1.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,0);        
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum2.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,0);        
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum3.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,0);        
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum4.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,0);        
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum5.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,0);        
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum6.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,0);        
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum7.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,0);        
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum8.xml")==0)
    {
        munit_assert_int(validate_xml_file(test_bmd),==,0);        
    }

    return MUNIT_OK;

}

static MunitResult
test_bmd_valid(const MunitParameter params[],void* user_data)
{
    const char* foo;
    (void) user_data;

    //foo is specified as one of the xml files
    foo=munit_parameters_get(params,"foo");

    /* Notice that we're returning MUNIT_FAIL instead of writing an
   * error message.  Error messages are generally preferable, since
   * they make it easier to diagnose the issue, but this is an
   * option.
   *
   * Possible values are:
   *  - MUNIT_OK: Sucess
   *  - MUNIT_FAIL: Failure
   *  - MUNIT_SKIP: The test was skipped; usually this happens when a
   *    particular feature isn't in use.  For example, if you're
   *    writing a test which uses a Wayland-only feature, but your
   *    application is running on X11.
   *  - MUNIT_ERROR: The test failed, but not because of anything you
   *    wanted to test.  For example, maybe your test downloads a
   *    remote resource and tries to parse it, but the network was
   *    down.
   */

        printf("%s\n",(char*) foo);
    
        printf("Testing test_bmd_valid()\n");


        if(strcmp(foo,"../test_files/dum2.xml")==0)
        {
            munit_assert_int(process_esb_request(foo),==,1);
        }

        if(strcmp(foo,"../test_files/test_xml_handle/dum.xml")==0)
        {
            munit_assert_int(process_esb_request(foo),==,1);
        }

        if(strcmp(foo,"../test_files/test_xml_handle/dum1.xml")==0)
        {
            munit_assert_int(process_esb_request(foo),==,1);
        }

        return MUNIT_OK;
    }

static char* foo_params[]={

    (char*) "../test_files/dum1.xml",
    (char*) "../test_files/dum2.xml",
    (char*) "../test_files/dum3.xml",
    (char*) "../test_files/test_xml_handle/dum.xml",
    (char*) "../test_files/test_xml_handle/dum1.xml",
    (char*) "../test_files/test_xml_handle/dum2.xml",
    (char*) "../test_files/test_xml_handle/dum3.xml",
    (char*) "../test_files/test_xml_handle/dum4.xml",
    (char*) "../test_files/test_xml_handle/dum5.xml",
    (char*) "../test_files/test_xml_handle/dum6.xml",
    (char*) "../test_files/test_xml_handle/dum7.xml",
    (char*) "../test_files/test_xml_handle/dum8.xml",
    NULL
};

static char* bar_params[]={
    (char*) "red",
    (char*) "green",
    (char*) "blue",
    NULL
};

static MunitParameterEnum test_params[] = {
  { (char*) "foo", foo_params },
};

//Now creating a test suite by creating an array
static MunitTest test_suite_tests[] = {
    { (char*) "../example/xml_values",test_xml_values,NULL,NULL, MUNIT_TEST_OPTION_NONE, test_params},
    { (char*) "../exampple/bmd_valid" , test_xml_valid,NULL,NULL,MUNIT_TEST_OPTION_NONE,test_params},
    { (char*) "../example/bmd_validation", test_bmd_valid,NULL,NULL,MUNIT_TEST_OPTION_NONE,test_params},

    {NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL }
};

//Now we declare the test suite 

static const MunitSuite test_suite ={
    //this string will be prepended to all est names in this suite
    //for e.g. "/example/rand" will become "/unit/example/rand"


    //an empty string
    (char*) "",

    //first parameter in array of test suites
    test_suite_tests,

    /* In addition to containing test cases, suites can contain other
   * test suites.  This isn't necessary in this example, but it can be
   * a great help to projects with lots of tests by making it easier
   * to spread the tests across many files.  This is where you would
   * put "other_suites" (which is commented out above). */
    NULL,

    /* An interesting feature of µnit is that it supports automatically
   * running multiple iterations of the tests.  This is usually only
   * interesting if you make use of the PRNG to randomize your tests
   * cases a bit, or if you are doing performance testing and want to
   * average multiple runs.  0 is an alias for 1. */
   1,
  /* Just like MUNIT_TEST_OPTION_NONE, you can provide
   * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
   MUNIT_SUITE_OPTION_NONE


};

//below implementation is necessary for EXIT_SUCCESSS and EXIT_FAILURE
#include<stdlib.h>

//#if 1
int main(int argc,char** argv)
{
    //now we run our test suite

    return munit_suite_main(&test_suite,NULL,argc,NULL);
}

//#endif
