/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-6-1        Wayne        First version
*
******************************************************************************/

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#if defined(RT_USING_PIN)
#include "drv_gpio.h"

/* defined the LED_0 pin: PJ14 */
#define LED_0   NU_GET_PININDEX(NU_PJ, 14)

int main(int argc, char **argv)
{
    int counter = 10000;

    /* set LED_0 pin mode to output */
    rt_pin_mode(LED_0, PIN_MODE_OUTPUT);

    while (counter--)
    {
        rt_pin_write(LED_0, PIN_HIGH);
        rt_thread_mdelay(100);
        rt_pin_write(LED_0, PIN_LOW);
        rt_thread_mdelay(100);
    }

    return 0;
}

#else

int main(int argc, char **argv)
{
    rt_kprintf("cpu-%d %d\r\n", rt_hw_cpu_id(), nu_cpu_dcache_line_size());
    return 0;
}

#endif

void happy_counter(void *pdata)
{
    uint32_t counter = 0;
    while (1)
    {
        rt_kprintf("cpu-%d %d\r\n", rt_hw_cpu_id(), counter++);
        rt_thread_mdelay(1000);
    }
}

void go_happy_counter(void)
{
    rt_thread_t tid = rt_thread_create("cpu-1", happy_counter, RT_NULL,  2048, 10, 20);
    RT_ASSERT(tid != RT_NULL);

    rt_thread_control(tid, RT_THREAD_CTRL_BIND_CPU, (void *)1);

    rt_thread_startup(tid);
}
MSH_CMD_EXPORT(go_happy_counter, go happy counter);

