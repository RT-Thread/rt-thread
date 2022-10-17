/**************************************************************************//**
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>
#include <rtdevice.h>
#include <drv_gpio.h>

/* defined the LEDR pin: PH4 */
#define LEDR   NU_GET_PININDEX(NU_PH, 4)

/* defined the LEDG pin: PH6 */
#define LEDG   NU_GET_PININDEX(NU_PH, 6)

int main(int argc, char **argv)
{
#if defined(RT_USING_PIN)

    int counter = 0;

    /* set pin mode to output */
    rt_pin_mode(LEDR, PIN_MODE_OUTPUT);
    rt_pin_mode(LEDG, PIN_MODE_OUTPUT);

    while (counter++ < 10)
    {
        rt_pin_write(LEDR, PIN_HIGH);
        rt_pin_write(LEDG, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(LEDR, PIN_LOW);
        rt_pin_write(LEDG, PIN_HIGH);
        rt_thread_mdelay(500);
    }

#endif
    return 0;
}
