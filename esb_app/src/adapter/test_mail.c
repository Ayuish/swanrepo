/* Created By Vinay Prabhakar on 9/11/20
    @Brief : Under this module we will be creating test cases for adapter functions 
    which include destination services
*/

#include<stdio.h>
#include<stdlib.h>
#include "../test/munit.h"
#include "adapter.h"


#if defined(_MS_VER)
#pragma warning(disable: 4127)
#endif

static MunitResult
test_send_mail(const MunitParameter params[], void* user_data)
{
    void* foo;
    void* bar;
    (void) user_data;


    //foo paramter is one of following : one,two,three
    foo=munit_parameters_get(params,"foo");
    bar=munit_parameters_get(params,"bar");

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
  printf("%s\n",(char *)bar);

  char* res=send_mail(foo,bar);
  
  printf("Testing Email as destination service\n");

  if(strcmp(foo,"vinayprabhakar91@gmail.com")==0 && strcmp(bar,"output.json")==0)
  {
      munit_assert_string_equal(res,"Yes email sent");

  }
  return MUNIT_OK;


}

static char* foo_params={

    (void*) "vinayprabhakar91@gmail.com",
};

static char* bar_params={

    (void *) "output.json",
};




static MunitParamterEnum test_params[2]={

    { (char*) "foo", foo_params },
    { (char*) "bar", bar_params },
};

static MunitTest test_suite_tests[]={

    { (char *) "../example/send_mail",test_send_mail,NULL,NULL,MUNIT_TEST_OPTION_NONE,test_params},

    { NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL}
};

static const MunitSuite test_suite={

    (char *) "",

    //first paramter in array of test suites
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

#include<stdlib.h>

int main(int argc,char** argv)
{
    return munit_suite_main(&test_suite,NULL,argc,NULL);
}