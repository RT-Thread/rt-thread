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

/* defined the LED_0 pin: PN6 */
#define LED_0   NU_GET_PININDEX(NU_PN, 6)

/* defined the LED_1 pin: PN7 */
#define LED_1   NU_GET_PININDEX(NU_PN, 7)

/* defined the LED_2 pin: PN10 */
#define LED_2   NU_GET_PININDEX(NU_PN, 10)

/* defined the KEY_0 pin: PN2 */
#define KEY_0   NU_GET_PININDEX(NU_PN, 2)

/* defined the KEY_1 pin: PN3 */
#define KEY_1   NU_GET_PININDEX(NU_PN, 3)

/* defined the KEY_2 pin: PN12 */
#define KEY_2   NU_GET_PININDEX(NU_PN, 12)

/* defined the KEY_3 pin: PN13 */
#define KEY_3   NU_GET_PININDEX(NU_PN, 13)

void nu_button_cb(void *args)
{
    uint32_t u32Key = (uint32_t)args;

    switch (u32Key)
    {
    case KEY_0:
        rt_kprintf("KEY_0 pressed\n");
        rt_pin_write(LED_1, PIN_HIGH);
        break;
    case KEY_1:
        rt_kprintf("KEY_1 pressed\n");
        rt_pin_write(LED_1, PIN_LOW);
        break;
    case KEY_2:
        rt_kprintf("KEY_2 pressed\n");
        rt_pin_write(LED_2, PIN_HIGH);
        break;
    case KEY_3:
        rt_kprintf("KEY_3 pressed\n");
        rt_pin_write(LED_2, PIN_LOW);
        break;
    }
}

static void nu_button_init(void)
{
    /* set KEY_0 pin mode to input, pull-up, falling edge and enable interrupt. */
    rt_pin_mode(KEY_0, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_0, PIN_IRQ_MODE_FALLING, nu_button_cb, (void *)KEY_0);
    rt_pin_irq_enable(KEY_0, PIN_IRQ_ENABLE);

    /* set KEY_1 pin mode to input, pull-up, falling edge and enable interrupt. */
    rt_pin_mode(KEY_1, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_1, PIN_IRQ_MODE_FALLING, nu_button_cb, (void *)KEY_1);
    rt_pin_irq_enable(KEY_1, PIN_IRQ_ENABLE);

    /* set KEY_2 pin mode to input, pull-up, falling edge and enable interrupt. */
    rt_pin_mode(KEY_2, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_2, PIN_IRQ_MODE_FALLING, nu_button_cb, (void *)KEY_2);
    rt_pin_irq_enable(KEY_2, PIN_IRQ_ENABLE);

    /* set KEY_3 pin mode to input, pull-up, falling edge and enable interrupt. */
    rt_pin_mode(KEY_3, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_3, PIN_IRQ_MODE_FALLING, nu_button_cb, (void *)KEY_3);
    rt_pin_irq_enable(KEY_3, PIN_IRQ_ENABLE);
}


int main(int argc, char **argv)
{
    int counter = 100000;

    /* set on-board buttons */
    nu_button_init();

    /* set LED_0, LED_1 and LED_2 pin mode to output */
    rt_pin_mode(LED_0, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_1, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_2, PIN_MODE_OUTPUT);

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
