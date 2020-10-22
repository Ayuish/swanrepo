/* created by vinay prabhakar on 22/10/20
Brief :- Creating a test function for the xml_parser.c created before
*/

#include<stdio.h>
#include "munit.h"
#include <stdlib.h>
#include "../parser/xml.h"
#include "../esb/esb.h"

//to disable an MSCV warning about conditional expreesions before constatnt

#id defined(_MS_VER)
#pragma warning(disable : 4127)
##endif

static MunitResult
test_xml_values(const MUnitParameter params[], void * user_data)
{
    const char* foo;
    (void) user_data;
    /* the foo can be specified as one of following
    one,two or three */
    foo=munit_parameter_get(params,"foo");

  /* Similarly, "bar" is one of "four", "five", or "six". */
 //  bar = munit_parameters_get(params, "bar");
   /* "bar" is a bit more complicated.  We don't actually specify a
    * list of valid values, so by default NULL is passed.  However, the
    * CLI will accept any value.  This is a good way to have a value
    * that is usually selected randomly by the test, but can be
    * overridden on the command line if desired. */
   /* const char* baz = munit_parameters_get(params, "baz"); */

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

    printf("%s\n",(char *)foo);

    bmd *test_bmd=parse_bmd_xml(foo);
    printf("tetsing\n");
    printf("%S\n",test_bmd->envelop->MessageID);

    if(strcmp(foo,"../testing/xml_testing/dum1.xml")==0){
    munit_assert_string_equal(test_bmd->envelop->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"KARB0000001");
    }

    if(strcmp(foo,"../testing/xml_tetsing/dum2.xml")==0){
    munit_assert_string_equal(test_bmd->envelop->MessageID,"B9ECAEF2-107A-4452-9553-043B6D25386E");
        munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
        munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
        munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
        munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
        munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
        munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
        munit_assert_string_equal(test_bmd->payload,"HDFC0CAGSBK");
    }

    if(strcmp(foo,"../tetsing/xml_testing/dum3.xml")==0){
m   munit_assert_string_equal(test_bmd->envelop->MessageID,"C9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DC");
    munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:19:00+0000");
    munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1239");
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum1.xml")==0)
    {
        munit_assert_null(test_bmd->envelop->MessageID);
        munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
        munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
        munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
        munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
        munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
        munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
        munit_assert_string_equal(test_bmd->payload,"001-01-1234");
    }

    if(strcmp(foo,"../test_files/test_xml_handle/dum2.xml")==0)
      {
        munit_assert_string_equal(test_bmd->envelop->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
        munit_assert_null(test_bmd->envelop->MessageType);
        munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
        munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
        munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
        munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
        munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
        munit_assert_string_equal(test_bmd->payload,"001-01-1234");
      }

      if(strcmp(foo,"../test_files/test_xml_handle/dum3.xml")==0)
      {
        munit_assert_string_equal(test_bmd->envelop->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
        munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
        munit_assert_null(test_bmd->envelop->Sender);
        munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
        munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
        munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
        munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
        munit_assert_string_equal(test_bmd->payload,"001-01-1234");
      }

      if(strcmp(foo,"../test_files/test_xml_handle/dum4.xml")==0)
      {
        munit_assert_string_equal(test_bmd->envelop->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
        munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
        munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
        munit_assert_null(test_bmd->envelop->Destination);
        munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
        munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
        munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
        munit_assert_string_equal(test_bmd->payload,"001-01-1234");
      }

      if(strcmp(foo,"../test_files/test_xml_handle/dum5.xml")==0)
      {
        munit_assert_string_equal(test_bmd->envelop->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
        munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
        munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
        munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
        munit_assert_null(test_bmd->envelop->CreationDateTime);
        munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
        munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
        munit_assert_string_equal(test_bmd->payload,"001-01-1234");
      }

      if(strcmp(foo,"../test_files/test_xml_handle/dum6.xml")==0)
      {
        munit_assert_string_equal(test_bmd->envelop->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
        munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
        munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
        munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
        munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
        munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
        munit_assert_null(test_bmd->envelop->Signature);
        munit_assert_string_equal(test_bmd->payload,"001-01-1234");
      }

      if(strcmp(foo,"../test_files/test_xml_handle/dum7.xml")==0)
      {
        munit_assert_string_equal(test_bmd->envelop->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
        munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
        munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
        munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
        munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
        munit_assert_null(test_bmd->envelop->ReferenceID);
        munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
        munit_assert_string_equal(test_bmd->payload,"001-01-1234");
      }

      if(strcmp(foo,"../test_files/test_xml_handle/dum8.xml")==0)
      {
        munit_assert_string_equal(test_bmd->envelop->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
        munit_assert_string_equal(test_bmd->envelop->MessageType,"CreditReport");
        munit_assert_string_equal(test_bmd->envelop->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
        munit_assert_string_equal(test_bmd->envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
        munit_assert_string_equal(test_bmd->envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
        munit_assert_string_equal(test_bmd->envelop->ReferenceID,"INV-PROFILE-889712");
        munit_assert_string_equal(test_bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
        munit_assert_null(test_bmd->payload);
      }


      return MUNIT_OK;
    }

    static MunitResult
    test_xml_valid(const MunitParameter params[], void * user_data)
    {
        const char* foo;
        (void) user_data;
        //the foo parameter is defined as one of the xml files
        foo=munit_parameters_get(params,"foo");

        /* we will be using MUNIT_FAIL instead of error message
        as they are generally preferale
        it is easier to diagnose the issue
        possible values are
         MUNIT_OK: Sucess
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

           printf("%s\n",(char *)foo);
           bmd *test_bmd=parse_bmd_xml(foo);

           printf("Testing\n");
           printf("%s\n",test_bmd->envelop->MessageID);

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
           munit_assert_int(validate_xml_file(test_bmd),==,-1);
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
    test_bmd_valid(const MunitParameter params[], void* user_data)
    {
        const char* foo;
        (void) user_data;
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

          printf("%s\n",(char *) foo);

         // bmd *test_bmd= parse_bmd_xml(foo);

          printf("testing namxnmsandm\n");
          //printf("%s\n" ,test_bmd->envelop->MessageID);

          if(strcmp(foo,"../test_files/dum2.xml")==0)
          {
             munit_assert_int(process_esb_request(foo),==,1);
          }

          if(strcmp(foo,"../test_files/test_xml_handle/dum.xml")==0)
          {
             munit_assert_int(process_esb_request(foo),==,-1);
          }

          if(strcmp(foo,"../test_files/test_xml_handle/dum1.xml")==0)
          {
             munit_assert_int(process_esb_request(foo),==,-1);
          }



          return MUNIT_OK;
        }




        static char* foo_params[] = {
          (char*) "../test_files/dum1.xml" , (char*) "../test_files/dum2.xml", (char*) "../test_files/dum3.xml",
          (char*) "../test_files/test_xml_handle/dum.xml",   (char*) "../test_files/test_xml_handle/dum.xml",
          (char*) "../test_files/test_xml_handle/dum2.xml",  (char*) "../test_files/test_xml_handle/dum3.xml",
          (char*) "../test_files/test_xml_handle/dum4.xml",   (char*) "../test_files/test_xml_handle/dum5.xml",
          (char*) "../test_files/test_xml_handle/dum6.xml",  (char*) "../test_files/test_xml_handle/dum7.xml",
          (char*) "../test_files/test_xml_handle/dum8.xml",  NULL
        };

        static char* bar_params[] = {
          (char*) "red", (char*) "green", (char*) "blue", NULL
        };

        static MunitParameterEnum test_params[] = {
          { (char*) "foo", foo_params },
        };

        /* Creating a test suite is pretty simple.  First, you'll need an
         * array of tests: */
        static MunitTest test_suite_tests[] = {

          { (char*) "/example/xml_values", test_xml_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params },
          { (char*) "/example/bmd_valid", test_xml_valid, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params },
          { (char*) "/example/bmd-validation", test_bmd_valid, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params },


          { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
        };



        /* Now we'll actually declare the test suite.  You could do this in
         * the main function, or on the heap, or whatever you want. */
        static const MunitSuite test_suite = {
          /* This string will be prepended to all test names in this suite;
           * for example, "/example/rand" will become "/µnit/example/rand".
           * Note that, while it doesn't really matter for the top-level
           * suite, NULL signal the end of an array of tests; you should use
           * an empty string ("") instead. */
          (char*) "",
          /* The first parameter is the array of test suites. */
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

        /* This is only necessary for EXIT_SUCCESS and EXIT_FAILURE, which you
         * *should* be using but probably aren't (no, zero and non-zero don't
         * always mean success and failure).  I guess my point is that nothing
         * about µnit requires it. */
        #include <stdlib.h>
        #if 1
        int main(int argc, char** argv) {
          /* Finally, we'll actually run our test suite!  That second argument
           * is the user_data parameter which will be passed either to the
           * test or (if provided) the fixture setup function. */
          return munit_suite_main(&test_suite, NULL, argc, NULL);
        }
        #endif