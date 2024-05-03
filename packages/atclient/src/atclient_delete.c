#include "atclient/atclient.h"
#include "atclient/atkey.h"
#include <stdlib.h>
#include <string.h>
#include "atclient/atstr.h"
#include "atclient/constants.h"
#include "atclient/stringutils.h"
#include "atlogger/atlogger.h"

#define TAG "atclient_delete"

int atclient_delete(atclient *atclient, const atclient_atkey *atkey) {
  int ret = 1;

  atclient_atstr cmdbuffer;
  atclient_atstr_init_literal(&cmdbuffer, ATCLIENT_ATKEY_FULL_LEN + strlen("delete:"), "delete:");

  char atkeystr[ATCLIENT_ATKEY_FULL_LEN];
  memset(atkeystr, 0, sizeof(char) * ATCLIENT_ATKEY_FULL_LEN);
  size_t atkeystrlen = 0;

  const size_t recvsize = 4096;
  unsigned char recv[4096];
  memset(recv, 0, sizeof(unsigned char) * recvsize);
  size_t recvlen = 0;

  ret = atclient_atkey_to_string(atkey, atkeystr, ATCLIENT_ATKEY_FULL_LEN, &atkeystrlen);
  if (ret != 0) {
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atkey_to_string: %d\n", ret);
    goto exit;
  }

  ret = atclient_atstr_append(&cmdbuffer, "%.*s\n", (int)atkeystrlen, atkeystr);
  if (ret != 0) {
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_atstr_append: %d\n", ret);
    goto exit;
  }

  ret = atclient_connection_send(&(atclient->secondary_connection), (unsigned char *)cmdbuffer.str, cmdbuffer.len,
                                 recv, 4096, &recvlen);
  if (ret != 0) {
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "atclient_connection_send: %d\n", ret);
    goto exit;
  }

  if (!atclient_stringutils_starts_with((char *)recv, recvlen, "data:", 5)) {
    ret = 1;
    atlogger_log(TAG, ATLOGGER_LOGGING_LEVEL_ERROR, "recv was \"%.*s\" and did not have prefix \"data:\"\n",
                          (int)recvlen, recv);
    goto exit;
  }

  ret = 0;
  goto exit;
exit: {
  atclient_atstr_free(&cmdbuffer);
  return ret;
}
}