/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PB2 */
#define LED0_PIN    GET_PIN(B, 2)

int main(void)
{
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);

    rt_kprintf("SYSCLK: %dMhz, \nHCLK: %dMhz, \nPCLK1: %dMhz, \nPCLK2: %dMhz, \nADCCLK: %dMhz\n",
               clocks.SYSCLK_Frequency / 1000000, clocks.HCLK_Frequency / 1000000,
               clocks.PCLK1_Frequency / 1000000, clocks.PCLK2_Frequency / 1000000, clocks.ADCCLK_Frequency / 1000000);

    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

