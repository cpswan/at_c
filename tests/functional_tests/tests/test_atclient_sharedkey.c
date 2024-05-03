#include <atclient/atclient.h>
#include <atclient/constants.h>
#include <atlogger/atlogger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functional_tests/config.h"
#include "functional_tests/helpers.h"

#define TAG "test_atclient_sharedkey"

#define ATKEY_KEY "test_atclient_sharedkey"
#define ATKEY_NAMESPACE "functional_tests"
#define ATKEY_SHAREDBY FIRST_ATSIGN
#define ATKEY_SHAREDWITH SECOND_ATSIGN
#define ATKEY_VALUE "Hello World! :D\n"
#define ATKEY_TTL 60*1000*5 // 5 minutes
#define ATKEY_TTR -1 // DO NOT CACHE

static int test_1_put(atclient *atclient);
static int test_2_get_as_sharedby(atclient *atclient);
static int test_3_get_as_sharedwith(atclient *atclient);
static int test_4_delete(atclient *atclient);
static int test_5_should_not_exist_as_sharedby(atclient *atclient);
static int tear_down_sharedenckeys(atclient *atclient);

int main(int argc, char *argv[])
{
    int ret = 1;

    atlogger_set_logging_level(ATLOGGER_LOGGING_LEVEL_DEBUG);

    char *atsign1 = FIRST_ATSIGN;
    const size_t atsign1len = strlen(atsign1);

    char *atsign2 = SECOND_ATSIGN;
    const size_t atsign2len = strlen(atsign2);

    atclient atclient1;
    atclient_init(&atclient1);

    atclient atclient2;
    atclient_init(&atclient2);

    if((ret = functional_tests_pkam_auth(&atclient1, atsign1)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "set_up: %d\n", ret);
        goto exit;
    }

    if((ret = test_1_put(&atclient1)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "test_1_put: %d\n", ret);
        goto exit;
    }

    if((ret = test_2_get_as_sharedby(&atclient1)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "test_2_get_as_sharedby: %d\n", ret);
        goto exit;
    }

    if((ret = functional_tests_pkam_auth(&atclient2, atsign2)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "set_up: %d\n", ret);
        goto exit;
    }

    if((ret = test_3_get_as_sharedwith(&atclient2)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "test_3_get_as_sharedwith: %d\n", ret);
        goto exit;
    }

    if((ret = test_4_delete(&atclient1)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "test_4_delete: %d\n", ret);
        goto exit;
    }

    if((ret = test_5_should_not_exist_as_sharedby(&atclient1)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "test_5_should_not_exist: %d\n", ret);
        goto exit;
    }

    goto exit;

exit: {
    if(tear_down_sharedenckeys(&atclient1) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "tear_down: %d\n", ret);
        ret = 1;
    }
    atclient_free(&atclient1);
    atclient_free(&atclient2);
    return ret;
}
}

static int test_1_put(atclient *atclient)
{
    int ret = 1;

    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_1_put Begin\n");

    atclient_atkey atkey;
    atclient_atkey_init(&atkey);

    if ((ret = atclient_atkey_create_sharedkey(&atkey, ATKEY_KEY, strlen(ATKEY_KEY), ATKEY_SHAREDBY, strlen(ATKEY_SHAREDBY), ATKEY_SHAREDWITH, strlen(ATKEY_SHAREDWITH), ATKEY_NAMESPACE, strlen(ATKEY_NAMESPACE))) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atkey_create_sharedkey: %d\n", ret);
        goto exit;
    }

    atclient_atkey_metadata_set_ttl(&atkey.metadata, ATKEY_TTL);
    atclient_atkey_metadata_set_ttr(&atkey.metadata, ATKEY_TTR);

    if((ret = atclient_put(atclient, &atkey, ATKEY_VALUE, strlen(ATKEY_VALUE), NULL)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_put: %d\n", ret);
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "put done\n");

    goto exit;
exit: {
    atclient_atkey_free(&atkey);
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_1_put End (%d)\n", ret);
    return ret;
}
}

static int test_2_get_as_sharedby(atclient *atclient)
{
    int ret = 1;

    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_2_get_as_sharedby Begin\n");

    atclient_atkey atkey;
    atclient_atkey_init(&atkey);

    const size_t valuesize = 1024;
    char value[valuesize];
    memset(value, 0, sizeof(char) * valuesize);
    size_t valuelen = 0;

    if ((ret = atclient_atkey_create_sharedkey(&atkey, ATKEY_KEY, strlen(ATKEY_KEY), ATKEY_SHAREDBY, strlen(ATKEY_SHAREDBY), ATKEY_SHAREDWITH, strlen(ATKEY_SHAREDWITH), ATKEY_NAMESPACE, strlen(ATKEY_NAMESPACE))) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atkey_create_sharedkey: %d\n", ret);
        goto exit;
    }

    if((ret = atclient_get_sharedkey(atclient, &atkey, value, valuesize, &valuelen, NULL, false)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_get: %d\n", ret);
        goto exit;
    }

    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "value: \"%s\"\n", value);

    if((ret = strcmp(value, ATKEY_VALUE)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "value mismatch\n");
        goto exit;
    }

    // check ttl, should be 5 minutes
    if(atkey.metadata.ttl != ATKEY_TTL)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "ttl mismatch. Expected %d, got %d\n", ATKEY_TTL, atkey.metadata.ttl);
        ret = 1;
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "ttl matched: %d\n", atkey.metadata.ttl);

    if(atkey.metadata.ttr != ATKEY_TTR)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "ttr mismatch. Expected %d, got %d\n", ATKEY_TTR, atkey.metadata.ttr);
        ret = 1;
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "ttr matched: %d\n", atkey.metadata.ttr);

    goto exit;
exit: {
    atclient_atkey_free(&atkey);
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_2_get_as_sharedby End (%d)\n", ret);
    return ret;
}
}

static int test_3_get_as_sharedwith(atclient *atclient2)
{
    int ret = 1;

    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_3_get_as_sharedwith Begin\n");

    const size_t valuesize = 1024;
    char value[valuesize];
    memset(value, 0, sizeof(char) * valuesize);
    size_t valuelen = 0;
    
    atclient_atkey atkey;
    atclient_atkey_init(&atkey);

    if((ret = atclient_atkey_create_sharedkey(&atkey, ATKEY_KEY, strlen(ATKEY_KEY), ATKEY_SHAREDBY, strlen(ATKEY_SHAREDBY), ATKEY_SHAREDWITH, strlen(ATKEY_SHAREDWITH), ATKEY_NAMESPACE, strlen(ATKEY_NAMESPACE))) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atkey_create_sharedkey: %d\n", ret);
        goto exit;
    }


    if((ret = atclient_get_sharedkey(atclient2, &atkey, value, valuesize, &valuelen, NULL, false)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_get: %d\n", ret);
        goto exit;
    }

    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "value: \"%s\"\n", value);

    if((ret = strcmp(value, ATKEY_VALUE)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "value mismatch\n");
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "value matched: %s == %s\n", value, ATKEY_VALUE);

    if(atkey.metadata.ttl != ATKEY_TTL)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "ttl mismatch. Expected %d, got %d\n", ATKEY_TTL, atkey.metadata.ttl);
        ret = 1;
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "ttl matched: %d\n", atkey.metadata.ttl);

    if(atkey.metadata.ttr != ATKEY_TTR)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "ttr mismatch. Expected %d, got %d\n", ATKEY_TTR, atkey.metadata.ttr);
        ret = 1;
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "ttr matched: %d\n", atkey.metadata.ttr);

    goto exit;
exit: {
    atclient_atkey_free(&atkey);
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_3_get_as_sharedwith End (%d)\n", ret);
    return ret;
}
}

static int test_4_delete(atclient *atclient)
{
    int ret = 1;

    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_4_delete Begin\n");

    atclient_atkey atkey;
    atclient_atkey_init(&atkey);

    if((ret = atclient_atkey_create_sharedkey(&atkey, ATKEY_KEY, strlen(ATKEY_KEY), ATKEY_SHAREDBY, strlen(ATKEY_SHAREDBY), ATKEY_SHAREDWITH, strlen(ATKEY_SHAREDWITH), ATKEY_NAMESPACE, strlen(ATKEY_NAMESPACE))) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atkey_create_sharedkey: %d\n", ret);
        goto exit;
    }

    if((ret = atclient_delete(atclient, &atkey)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_delete: %d\n", ret);
        goto exit;
    }

    goto exit;
exit: {
    atclient_atkey_free(&atkey);
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_4_delete End (%d)\n", ret);
    return ret;
}
}

static int test_5_should_not_exist_as_sharedby(atclient *atclient)
{
    int ret = 1;

    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_5_should_not_exist Begin\n");

    if((ret = functional_tests_selfkey_exists(atclient, ATKEY_KEY, ATKEY_SHAREDBY, ATKEY_NAMESPACE)) != false)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "functional_tests_selfkey_exists is 0 but should be 1: %d\n", ret);
        goto exit;
    }

    ret = 0;
    goto exit;
exit : {
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "test_5_should_not_exist End (%d)\n", ret);
    return ret;
}
}

static int tear_down_sharedenckeys(atclient *atclient1)
{
    int ret = 1;

    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "tear_down Begin\n");

    char atkeystrtemp[ATCLIENT_ATKEY_FULL_LEN];

    atclient_atkey atkey;
    atclient_atkey_init(&atkey);

    atclient_atkey atkeyforme;
    atclient_atkey_init(&atkeyforme);

    atclient_atkey atkeyforthem;
    atclient_atkey_init(&atkeyforthem);

    if((ret = atclient_atkey_create_sharedkey(&atkey, ATKEY_KEY, strlen(ATKEY_KEY), ATKEY_SHAREDBY, strlen(ATKEY_SHAREDBY), ATKEY_SHAREDWITH, strlen(ATKEY_SHAREDWITH), ATKEY_NAMESPACE, ATKEY_NAMESPACE == NULL ? 0 : strlen(ATKEY_NAMESPACE))) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atkey_create_sharedkey: %d\n", ret);
        goto exit;
    }

    if((ret = atclient_delete(atclient1, &atkey)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_delete: %d\n", ret);
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "deleted main shared atkey\n");

    memset(atkeystrtemp, 0, sizeof(char) * ATCLIENT_ATKEY_FULL_LEN);
    snprintf(atkeystrtemp, ATCLIENT_ATKEY_FULL_LEN, "shared_key.%s%s", ATKEY_SHAREDWITH+1, ATKEY_SHAREDBY);
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "atkeystrtemp: \"%s\"\n", atkeystrtemp);
    if((ret = atclient_atkey_from_string(&atkeyforme, atkeystrtemp, strlen(atkeystrtemp))) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atkey_from_string: %d\n", ret);
        goto exit;
    }

    memset(atkeystrtemp, 0, sizeof(char) * ATCLIENT_ATKEY_FULL_LEN);
    snprintf(atkeystrtemp, ATCLIENT_ATKEY_FULL_LEN, "%s:shared_key%s", ATKEY_SHAREDWITH, ATKEY_SHAREDBY);
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "atkeystrtemp: \"%s\"\n", atkeystrtemp);
    if((ret = atclient_atkey_from_string(&atkeyforthem, atkeystrtemp, strlen(atkeystrtemp))) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atkey_from_string: %d\n", ret);
        goto exit;
    }

    if((ret = atclient_delete(atclient1, &atkeyforme)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_delete: %d\n", ret);
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "deleted shared enc key for me\n");

    if((ret = atclient_delete(atclient1, &atkeyforthem)) != 0)
    {
        atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_delete: %d\n", ret);
        goto exit;
    }
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "deleted shared enc key for them\n");

    ret = 0;
    goto exit;

exit: {
    atclient_atkey_free(&atkey);
    atclient_atkey_free(&atkeyforme);
    atclient_atkey_free(&atkeyforthem);
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_INFO, "tear_down End (%d)\n", ret);
    return ret;
}
}