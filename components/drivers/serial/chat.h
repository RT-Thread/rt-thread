#ifndef __modem_chat_h__
#define __modem_chat_h__

#include <rtthread.h>
#include <rtdevice.h>

#define MODEM_CHAT_RESP_LIST(F) \
    F(MODEM_CHAT_RESP_OK,         "OK"), \
    F(MODEM_CHAT_RESP_READY,      "READY"), \
    F(MODEM_CHAT_RESP_CONNECT,    "CONNECT"), \
    F(MODEM_CHAT_RESP_BUSY,       "BUSY"), \
    F(MODEM_CHAT_RESP_NO_CARRIER, "NO CARRIER"), \
    F(MODEM_CHAT_RESP_ERROR,      "ERROR") \

#define DEFINE_MODEM_RESP_ID_TABLE(id, s) id

enum {
    MODEM_CHAT_RESP_LIST(DEFINE_MODEM_RESP_ID_TABLE),
    MODEM_CHAT_RESP_MAX,
    MODEM_CHAT_RESP_NOT_NEED = MODEM_CHAT_RESP_MAX,
};

struct rt_modem_chat_data {
    const char* transmit;
    rt_uint8_t expect;      // use CHAT_RESP_xxx
    rt_uint8_t retries;
    rt_uint8_t timeout;     // second
};


rt_err_t rt_modem_chat(struct rt_serial_device *serial, const struct rt_modem_chat_data *data, rt_size_t len);

#endif
