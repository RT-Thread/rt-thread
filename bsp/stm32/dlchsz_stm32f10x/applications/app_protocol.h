#ifndef __APP_PROTOCOL_H__
#define __APP_PROTOCOL_H__

#include <board.h>

struct app_protocol {
    struct rt_messagequeue rtu_slave;
};

extern struct app_protocol g_app_protocol;

#endif
