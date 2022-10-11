/**************************************************************************//**
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-7-20       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#if defined(RT_USING_PIN)

    #include "drv_gpio.h"
    /* defined the LED_1 pin: PJ15 */
    #define LED_1   NU_GET_PININDEX(NU_PJ, 15)

#endif

int main(int argc, char **argv)
{
    int counter = 10000;

#if defined(RT_USING_PIN)
    /* set LED_1 pin mode to output */
    rt_pin_mode(LED_1, PIN_MODE_OUTPUT);
#endif

    while (counter--)
    {
        rt_kprintf("Hello! MA35-RTP.\n");

#if defined(RT_USING_PIN)
        rt_pin_write(LED_1, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED_1, PIN_LOW);
        rt_thread_mdelay(1000);
#else
        rt_thread_mdelay(1000);
#endif
    }
    return 0;
}
