#include "app_modbus_rtu_slave.h"
#include "app_msg_que.h"

#include <modbus.h>

#define DBG_SECTION_NAME    "app_modbus_rtu_slave"
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

static void __modbus_rtu_slave_init(void);
static void __modbus_rtu_slave_thread(void *para);

static void __modbus_rtu_slave_init(void) {
    rt_thread_t tid;
    
    tid = rt_thread_create("modbus_rtu_slace",
                           __modbus_rtu_slave_thread,
                           RT_NULL,
                           2048,
                           1,
                           10);
    
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    else
        LOG_E("create modbus_rtu_slace thread failed.");
}
INIT_APP_EXPORT(__modbus_rtu_slave_init);

static void __modbus_rtu_slave_thread(void *para) {
    modbus_t *ctx = NULL;
    modbus_mapping_t *mb_mapping = NULL;
    int rc;
    
    ctx = modbus_new_rtu("/dev/uart3", 115200, 'N', 8, 1);
    modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS232);
//    modbus_set_debug(ctx, 1);
    modbus_set_slave(ctx, 1);
    modbus_connect(ctx);
    mb_mapping = modbus_mapping_new(0, 0, MODBUS_MAX_READ_REGISTERS, MODBUS_MAX_WRITE_REGISTERS);
    if (NULL == mb_mapping) {
        LOG_E("failed to allocate the mapping: %s", modbus_strerror(errno));
        modbus_free(ctx);
        return;
    }
    
    while (1){
        uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
        
        rc = modbus_receive(ctx, query);
        if (rc > 0) {
            rt_mq_send(&g_app_msg_que.rtu_slave, query, rc);
            modbus_reply(ctx, query, rc, mb_mapping);
        } else if (-1 == rc) {
            LOG_E("failed to modbus rtu data receive: %s", modbus_strerror(errno));
        }
    }
}
