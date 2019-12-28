#include "app_status_led.h"

#include <agile_led.h>

#define DBG_SECTION_NAME    "app_status_led"
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

static void __status_led_init(void);
static void __status_led_thread(void *para);

static void __status_led_init(void) {
    rt_thread_t tid;
    
    tid = rt_thread_create("status_led_thread",
                           __status_led_thread,
                           RT_NULL,
                           512,
                           30,
                           10);
    
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    else
        LOG_E("create status_led_thread thread failed.");
}
INIT_APP_EXPORT(__status_led_init);

static void __status_led_thread(void *para) {
    agile_led_t *sys_run = RT_NULL;

    sys_run = agile_led_create(GET_PIN(C, 13), PIN_LOW, "1000,1000", -1);
    agile_led_start(sys_run);
    
    while(1) {
        rt_thread_mdelay(1000);
    }
}
