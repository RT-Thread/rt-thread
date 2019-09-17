#ifndef __chat_at_h__
#define __chat_at_h__

#include <rtthread.h>

#define CHAT_RESP_LIST(F) \
    F(CHAT_RESP_OK,         "OK"), \
    F(CHAT_RESP_READY,      "READY"), \
    F(CHAT_RESP_CONNECT,    "CONNECT"), \
    F(CHAT_RESP_BUSY,       "BUSY"), \
    F(CHAT_RESP_NO_CARRIER, "NO CARRIER"), \
    F(CHAT_RESP_ERROR,      "ERROR") \

#define DEFINE_RESP_ID_TABLE(id, s) id

enum {
    CHAT_RESP_LIST(DEFINE_RESP_ID_TABLE),
    CHAT_RESP_MAX,
    CHAT_RESP_NOT_NEED = CHAT_RESP_MAX,
};

struct chat_data {
    const char* transmit;
    rt_uint8_t expect;      // use CHAT_RESP_xxx
    rt_uint8_t retries;
    rt_uint8_t timeout;     // second
};


rt_err_t chat_run(const struct chat_data *data, rt_size_t len);

#endif
