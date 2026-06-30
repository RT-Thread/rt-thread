/**************************************************************************//**
*
* @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
******************************************************************************/

#include <rtconfig.h>
#include <rtdevice.h>
#include "drv_gpio.h"

/* defined the LEDR pin: PC14 */
#define LEDR   NU_GET_PININDEX(NU_PC, 14)

int main(int argc, char **argv)
{
#if defined(RT_USING_PIN)
    /* set LEDR pin mode to output */
    rt_pin_mode(LEDR, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LEDR, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LEDR, PIN_LOW);
        rt_thread_mdelay(500);
    }
#endif

    return 0;
}
