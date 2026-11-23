/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtdevice.h>
#include "board.h"

#ifdef RT_USING_FINSH
#include <finsh.h>

static volatile rt_uint32_t sw2_irq_count;
static volatile rt_uint32_t sw3_irq_count;

static void button_irq(void *args)
{
    (*(volatile rt_uint32_t *)args)++;
}

static int button_irq_test(void)
{
    rt_err_t result;
    rt_uint32_t sw2_count;
    rt_uint32_t sw3_count;

    sw2_irq_count = 0;
    sw3_irq_count = 0;
    rt_pin_mode(SW2_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(SW3_PIN, PIN_MODE_INPUT_PULLUP);

    result = rt_pin_attach_irq(SW2_PIN, PIN_IRQ_MODE_FALLING,
                               button_irq, (void *)&sw2_irq_count);
    if (result != RT_EOK)
    {
        return result;
    }

    result = rt_pin_attach_irq(SW3_PIN, PIN_IRQ_MODE_FALLING,
                               button_irq, (void *)&sw3_irq_count);
    if (result != RT_EOK)
    {
        rt_pin_detach_irq(SW2_PIN);
        return result;
    }

    rt_pin_irq_enable(SW2_PIN, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(SW3_PIN, PIN_IRQ_ENABLE);
    rt_kprintf("Press SW2 and SW3 within 10 seconds\n");
    rt_thread_mdelay(10000);
    rt_pin_irq_enable(SW2_PIN, PIN_IRQ_DISABLE);
    rt_pin_irq_enable(SW3_PIN, PIN_IRQ_DISABLE);
    rt_pin_detach_irq(SW2_PIN);
    rt_pin_detach_irq(SW3_PIN);
    sw2_count = sw2_irq_count;
    sw3_count = sw3_irq_count;

    rt_kprintf("%s: SW2=%u, SW3=%u interrupt(s)\n",
               sw2_count != 0U && sw3_count != 0U ? "PASS" : "FAIL",
               (unsigned int)sw2_count, (unsigned int)sw3_count);

    return sw2_count != 0U && sw3_count != 0U ? RT_EOK : -RT_ERROR;
}
MSH_CMD_EXPORT(button_irq_test, count SW2 and SW3 falling-edge interrupts for 10 seconds);

static void reboot(void)
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, reset the MCU);
#endif

int main(void)
{
    rt_pin_write(LED_RED_PIN, PIN_HIGH);
    rt_pin_mode(LED_RED_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_RED_PIN, !rt_pin_read(LED_RED_PIN));
        rt_thread_mdelay(500);
    }
}
