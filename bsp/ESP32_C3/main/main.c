/*
 * Copyright (c) 2021-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-04-24     supperthomas  first version
 * 2022-06-02     supperthomas  fix version
 * 2023-10-20     WCX1024979076 add wifi application
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_BLE
void app_main()
{
    while(1)
    {

    }
}
#endif /* BSP_USING_BLE */

int main(void)
{
    rt_kprintf("Hello!RT-THREAD!\r\n");
    rt_pin_mode(RT_BSP_LED_PIN, PIN_MODE_OUTPUT);

#ifdef BSP_USING_BLE
    extern void app_main(void);
    esp_timer_init();
    app_main(); //该函数为nimble样例程序入口
#endif /* BSP_USING_BLE */

#ifdef RT_USING_WIFI
    /* set wifi work mode */
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);
#endif /* RT_USING_WIFI */

    while (1)
    {
        rt_pin_write(RT_BSP_LED_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(RT_BSP_LED_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}
