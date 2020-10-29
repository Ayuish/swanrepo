//
// Created by rajashekhar on 21/10/20.
//

#include "../test/munit.h"
#include "../bmd_extract/xml.h"
#include "connector.h"
#include <stdio.h>
#include <stdlib.h>



/*
 * @brief Unit testing of
 * int insert_to_esb_request(char *sender_id, char *dest_id, \
                          char *message_type, char *reference_id, char *message_id,\
                          char *data_location, char *status, char *status_details, char *received_on);
 */

/* setup function of insert_into_esb_request*/
static void*
test_insert_into_esb_request_setup(const MunitParameter params[],void* user_data) {
    char *file = (char *)user_data;
    (void)params;
    bmd_envelope *envelope = extract_envelope(file);
    return envelope;
}

/* Test function of insert_into_esb_request */

static MunitResult
test_insert_into_esb_request(const MunitParameter params[] , void *fixture) {
    (void )params;
    bmd_envelope *envelope = (bmd_envelope *) fixture;
    /* Generating random MessageId because it is Unique */
    munit_uint32_t Message_id = munit_rand_uint32();
    /* Converting uint_32_t to a string */
    sprintf(envelope->MessageID, "%lu", (unsigned long)Message_id);
    /* Check the return value  */
    int r_value = insert_into_esb_request(envelope->Sender, envelope->Destination, envelope->MessageType, \
                                        envelope->ReferenceID, envelope->MessageID, "Routes", \
                                        "available", "received successfully", envelope->CreationDateTime);

     /* We entered the data with new envelope->MessageID , r_value = 1 */
    munit_assert_int(r_value, ==, 1);
     /* Check the return value again */
    r_value = insert_into_esb_request(envelope->Sender, envelope->Destination, envelope->MessageType, \
                                        envelope->ReferenceID, envelope->MessageID, "Routes", \
                                        "available", "received successfully", envelope->CreationDateTime);

    /* We are entering the data with same envelope->MessageID so r_value = -1 */
     munit_assert_int(r_value, ==, -1);
    return MUNIT_OK;
}

/* tear_down function of insert_into_esb_request */
static void
test_insert_into_esb_request_tear_down(void *fixture) {
    bmd_envelope *envelope = (bmd_envelope *)fixture;
    free(envelope);
}


/*
 * @brief Unit testing of
 * int get_active_route_id(char *sender_id,char *destination_id, char *message_type);
 */

/* setup function of get_active route_id*/
static void *
get_active_route_id_setup(const MunitParameter params[], void *user_data)
{
    char *file = (char *)user_data;
    (void)params;
    bmd_envelope *envelope = extract_envelope(file);
    return envelope;
}

/* Test function of get_active_route_id */
static MunitResult
test_get_active_route_id(const MunitParameter params[], void *fixture)
{
    bmd_envelope *envelope= (bmd_envelope *)fixture;
    (void)params;
    /* checking return value for data already present in routes table */
    int r_value = get_active_route_id(envelope->Sender, envelope->Destination, envelope->MessageType);
    munit_assert_int(r_value,  !=, -1);
    /* Genarating random Sender_id */
    munit_uint32_t Sender_id = munit_rand_uint32();
    /* Converting uint_32_t to a string */
    sprintf(envelope->Sender, "%lu", (unsigned long)Sender_id);
    /* checking return value for data not present in routes table */
    r_value = get_active_route_id(envelope->Sender, envelope->Destination, envelope->MessageType);
    munit_assert_int(r_value, ==, -1);

    return MUNIT_OK;
}

/* tear_down function of get_active_route_id */
static void
get_active_route_id_tear_down(void *fixture)
{
    bmd_envelope *envelope = (bmd_envelope *)fixture;
    free(envelope);
}

/*
 * @brief Unit testing of
 * int check_id_in_transform_config(int route_id);
 */


/* test function for check_id_in_transform_config*/
static MunitResult
test_check_id_in_transform_config(const MunitParameter params[],void *user_data ) {
    (void)params;
    (void)user_data;
    /* check return value for the route_id present in transform_config table */
    int r_value = check_id_in_transform_config(1);
    munit_assert_int(r_value, ==, 1);

    int random_int = munit_rand_int_range(1000,5000);
    /* check return value for the route_id not present in transform_config table */
    r_value = check_id_in_transform_config(random_int);
    munit_assert_int(r_value, ==, -1);

    return MUNIT_OK;
}

/*
 * @brief Unit testing of
 * int check_id_in_transport_config(int route_id);
 */


/* test function for check_id_in_transport_config*/
static MunitResult
test_check_id_in_transport_config(const MunitParameter params[],void *user_data ) {
    (void)params;
    (void)user_data;
    /* check return value for the route_id present in transform_config table */
    int r_value = check_id_in_transport_config(1);
    munit_assert_int(r_value, ==, 1);

    int random_int = munit_rand_int_range(1000,5000);
    /* check return value for the route_id not present in transform_config table */
    r_value = check_id_in_transport_config(random_int);
    munit_assert_int(r_value, ==, -1);

    return MUNIT_OK;
}


/*
 * @brief unit testing of
 * transform_config *  fetch_transform_config_key_and_value(int route_id);
 */

/* setup function for fetch_transform_config_key_and_value */
static void *
fetch_transform_config_key_and_value_setup(const MunitParameter params[], void *user_data)
{
    (void )params;
    (void )user_data;
    transform_config *tf = fetch_transform_config_key_and_value(1);
    return tf;
}


/* Test function for fetch_transform_config_key_and_value */
static MunitResult
test_fetch_transform_config_key_and_value(const MunitParameter params[], void *fixture)
{
    transform_config *tf = (transform_config *)fixture;
    (void )params;
    /*  checking config_key */
    munit_assert_string_equal(tf->config_key,"raja");
    /* checking config_value */
    munit_assert_string_equal(tf->config_value,"shekhar");
    return MUNIT_OK;
}


/* tear_down function for fetch_transform_config_key_and_value*/
static void
fetch_transform_config_key_and_value_tear_down(void *fixture)
{
    /* free the memory allocated to tf */
    transform_config * tf = (transform_config *)fixture;
    free(tf->config_key);
    free(tf->config_value);
    free(tf);
}


/*
 * @brief unit testing of
 * transport_config *  fetch_transport_config_key_and_value(int route_id);
 */

/* setup function for fetch_transport_config_key_and_value */
static void *
fetch_transport_config_key_and_value_setup(const MunitParameter params[], void *user_data)
{
    (void )params;
    (void )user_data;
    transport_config *tf = fetch_transport_config_key_and_value(1);
    return tf;
}


/* Test function for fetch_transport_config_key_and_value */
static MunitResult
test_fetch_transport_config_key_and_value(const MunitParameter params[], void *fixture)
{
    transport_config *tf = (transport_config *)fixture;
    (void )params;
    /*  checking config_key */
    munit_assert_string_equal(tf->config_key,"raja");
    /* checking config_value */
    munit_assert_string_equal(tf->config_value,"shekhar");
    return MUNIT_OK;
}


/* tear_down function for fetch_transport_config_key_and_value*/
static void
fetch_transport_config_key_and_value_tear_down(void *fixture)
{
    /* free the memory allocated to tf */
    transport_config * tf = (transport_config *)fixture;
    free(tf->config_key);
    free(tf->config_value);
    free(tf);
}


/*
 * @brief unit testing of
 * int update_esb_request(char * status,int id);
 */

static MunitResult
test_update_esb_request(const MunitParameter params[], void *fixture)
{
    int random_int = munit_rand_int_range(1,5000);
    /* Check the return value */
    int r_value = update_esb_request("available",random_int);
    munit_assert_int(r_value, ==, 1);
    return MUNIT_OK;
}


static MunitTest database_tests[] = {
        {
                /* name */
                (char *) "/test_db_access/insert_into_esb_request",
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
        {
                /* name */
                (char *) "/test_db_access/get_active_route_id",
                /* test */
                test_get_active_route_id,
                /* setup */
                get_active_route_id_setup,
                /* tear_down */
                get_active_route_id_tear_down,
                /* options */
                MUNIT_TEST_OPTION_NONE,
                /* parameters */
                NULL

        },
        {
                /* name */
                (char *) "/test_db_access/check_id_in_transform_config",
                /* test */
                test_check_id_in_transform_config,
                /* setup */
                NULL,
                /* tear_down */
                NULL,
                /* options */
                MUNIT_TEST_OPTION_NONE,
                /* parameters */
                NULL
        },
        {
                /* name */
                (char *) "/test_db_access/check_id_in_transform_config",
                /* test */
                test_check_id_in_transport_config,
                /* setup */
                NULL,
                /* tear_down */
                NULL,
                /* options */
                MUNIT_TEST_OPTION_NONE,
                /* parameters */
                NULL
        },
        {
                /* name */
                (char *) "/test_db_access/fetch_transform_key_and_value",
                /* test */
                test_fetch_transform_config_key_and_value,
                /* setup */
                fetch_transform_config_key_and_value_setup,
                /* tear_down */
                fetch_transform_config_key_and_value_tear_down,
                /* options */
                MUNIT_TEST_OPTION_NONE,
                /* parameters */
                NULL
        },
        {
                /* name */
                (char *) "/test_db_access/fetch_transport_key_and_value",
                /* test */
                test_fetch_transport_config_key_and_value,
                /* setup */
                fetch_transport_config_key_and_value_setup,
                /* tear_down */
                fetch_transport_config_key_and_value_tear_down,
                /* options */
                MUNIT_TEST_OPTION_NONE,
                /* parameters */
                NULL
        },
        {
                /* name */
                (char *) "/test_db_access/update_esb_request",
                /* test */
                test_update_esb_request,
                /* setup */
                NULL,
                /* tear_down */
                NULL,
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


/*
int main(int argc,const char* argv[]) {
    char *user_data = "/home/rajashekhar/nho2020b2/swan/esb_app/src/test_files/dum1.xml";
    return munit_suite_main(&suite, (void *)user_data, argc, (char *const *) argv);
}

*/
