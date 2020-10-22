//
// Created by rajashekhar on 21/10/20.
//

#include "../test/munit.h"
#include "../parser/xml.h"
#include "connector.h"



/*
 * @brief Unit testing of
 * int insert_to_esb_request(char *sender_id, char *dest_id, \
                          char *message_type, char *reference_id, char *message_id,\
                          char *data_location, char *status, char *status_details, char *received_on);
 */

/* setup function */
static void*
test_insert_into_esb_request_setup(const MunitParameter params[],void* user_data) {
    char *file = (char *)user_data;
    (void)params;
    bmd_envelope *envl = extract_envelope(file);
    return envl;
}

/* Test function */

static MunitResult
test_insert_into_esb_request(const MunitParameter params[] , void *fixture) {
    (void )params;
    bmd_envelope *envl = (bmd_envelope *) fixture;
    /* check the return value from insert_into_esb_request */
    int r_value = insert_into_esb_request(envl->Sender, envl->Destination, envl->MessageType, \
                                        envl->ReferenceID, envl->MessageID, "Routes", \
                                        "available", "received successfully", envl->CreationDateTime);
    munit_assert_int(r_value, ==, 1);
    return MUNIT_OK;
}

/* tear_down function */
static void
test_insert_into_esb_request_tear_down(void *fixture) {
    bmd_envelope *envl = (bmd_envelope *)fixture;
    free(envl);
}




static MunitTest database_tests[] = {
        {
                /* name */
                (char *) "/test_insert_into_esb_request/insert_into_esb_request",
                /* test */
                test_insert_into_esb_request,
                /* setup */
                test_insert_into_esb_request_setup,
                /* tear_down */
                test_insert_into_esb_request_tear_down,
                /* options */
                MUNIT_TEST_OPTION_NONE,
                /* parameters */
                NULL
        },
        /* Mark the end of the array with an entry where the test
         * function is NULL */
        {
            NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL
        }



};

static const  MunitSuite suite = {
        /* name */
        "/database_tests",
        /* array of tests */
        database_tests,
        /* suites */
        NULL,
        /* iterations */
        1,
        /* options */
        MUNIT_SUITE_OPTION_NONE
};


#include <stdlib.h>

int main(int argc,const char* argv[]) {
    char *user_data = "file.xml";
    return munit_suite_main(&suite, (void *)user_data, argc, (char *const *) argv);
}