#ifndef __APP_MSG_QUE_H__
#define __APP_MSG_QUE_H__

#include <board.h>

struct app_msg_que {
    struct rt_messagequeue rtu_slave;
};

extern struct app_msg_que g_app_msg_que;

#endif
