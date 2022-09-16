#include "qe_touch_config.h"
#include <rtthread.h>
#include <rtdevice.h>
#define TOUCH_SCAN_INTERVAL_EXAMPLE (20)    /* milliseconds */

uint64_t button_status;
#if (TOUCH_CFG_NUM_SLIDERS != 0)
    uint16_t slider_position[TOUCH_CFG_NUM_SLIDERS];
#endif
#if (TOUCH_CFG_NUM_WHEELS != 0)
    uint16_t wheel_position[TOUCH_CFG_NUM_WHEELS];
#endif

void qe_touch_main(void *parameter)
{
    fsp_err_t err;
    rt_uint32_t led_blu = rt_pin_get("P501");

    /* Open Touch middleware */
    rt_kprintf("TOUCH Open\n");
    err = RM_TOUCH_Open(g_qe_touch_instance_config01.p_ctrl, g_qe_touch_instance_config01.p_cfg);
    if (FSP_SUCCESS != err)
    {
        rt_kprintf("RM_TOUCH_Open fail\n");
        return;
    }

    rt_kprintf("TOUCH ScanStart\n");
    /* Main loop */
    while (true)
    {
        /* for [CONFIG01] configuration */
        err = RM_TOUCH_ScanStart(g_qe_touch_instance_config01.p_ctrl);
        if (FSP_SUCCESS != err)
        {
            rt_kprintf("RM_TOUCH_Open fail\n");
            return;
        }
        while (0 == g_qe_touch_flag) {}
        g_qe_touch_flag = 0;

        err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &button_status, NULL, NULL);
        if (FSP_SUCCESS == err)
        {
            if (button_status)
            {
                rt_pin_write(led_blu, PIN_HIGH);
            }
            else
            {
                rt_pin_write(led_blu, PIN_LOW);
            }
        }

        /* FIXME: Since this is a temporary process, so re-create a waiting process yourself. */
        rt_thread_mdelay(TOUCH_SCAN_INTERVAL_EXAMPLE);
    }
}

int touch_init(void)
{
    rt_thread_t tid = rt_thread_create("touch", qe_touch_main, RT_NULL, 512, 10, 50);
    if (tid)
    {
        rt_thread_startup(tid);
    }
    return 0;
}
INIT_APP_EXPORT(touch_init);
//MSH_CMD_EXPORT(touch_init, touch_init);
