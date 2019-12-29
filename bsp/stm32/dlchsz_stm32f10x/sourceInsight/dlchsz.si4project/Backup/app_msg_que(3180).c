#include "app_msg_que.h"

#define DBG_SECTION_NAME    "app_msg_que"
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

struct app_msg_que g_app_msg_que;
static rt_uint8_t __g_data_buf[512];

static void __msg_que_init(void) {
    rt_err_t res;
    
    res = rt_mq_init(&g_app_msg_que.rtu_slave, "rtu_slave", &__g_data_buf[0],
                     256, sizeof(__g_data_buf), RT_IPC_FLAG_FIFO);
    if (res != RT_EOK) {
        LOG_E("create rtu_slave message queue failed.");
        return;
    }
}
INIT_PREV_EXPORT(__msg_que_init);
