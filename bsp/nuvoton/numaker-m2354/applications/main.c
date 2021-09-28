/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-8-26       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>
#include <rtdevice.h>
#include <drv_gpio.h>

/* defined the LEDR pin: PD3 */
#define LEDR   NU_GET_PININDEX(NU_PD, 3)

int main(int argc, char **argv)
{
#if defined(RT_USING_PIN)
    int counter = 100;
    /* set LEDR pin mode to output */
    rt_pin_mode(LEDR, PIN_MODE_OUTPUT);

    while (counter--)
    {
        rt_pin_write(LEDR, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LEDR, PIN_LOW);
        rt_thread_mdelay(500);
    }
#endif
    return 0;
}
