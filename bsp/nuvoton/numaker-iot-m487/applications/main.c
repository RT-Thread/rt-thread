/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>

/* defined the LEDR pin: PH0 */
#define LEDR   NU_GET_PININDEX(NU_PH, 0)

int main(int argc, char **argv)
{
    int counter = 0;

    /* set LEDR1 pin mode to output */
    rt_pin_mode(LEDR, PIN_MODE_OUTPUT);

    while (counter++ < 10)
    {
        rt_pin_write(LEDR, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LEDR, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return 0;
}
