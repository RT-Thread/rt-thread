/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 * 
 * Change Logs:
 * Date        Author       Notes
 * 2022-12-10  liqiaozhong  first commit 
 *
 */
#include "rtconfig.h"
#ifdef BSP_USING_GPIO
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "fparameters.h"
#include "ftypes.h"
#include "board.h"
#include <rtdbg.h>

#include "fgpio.h"
/**************************** Type Definitions *******************************/
/************************** Variable Definitions *****************************/
#if defined(FIREFLY_DEMO_BOARD)
static rt_base_t input_pin_index = FGPIO_ID(FGPIO_CTRL_2, FGPIO_PIN_10);
static rt_base_t output_pin_index = FGPIO_ID(FGPIO_CTRL_3, FGPIO_PIN_1);
#elif defined(E2000D_DEMO_BOARD) || defined(E2000Q_DEMO_BOARD)
static rt_base_t input_pin_index = FGPIO_ID(FGPIO_CTRL_4, FGPIO_PIN_11);
static rt_base_t output_pin_index = FGPIO_ID(FGPIO_CTRL_4, FGPIO_PIN_12);
#endif
/***************** Macros (Inline Functions) Definitions *********************/
#define FGPIO_OPS_PIN_PORT_A           0U
#define FGPIO_OPS_PIN_PORT_B           1U
#define FGPIO_OPS_LEVEL_LOW            0U
#define FGPIO_OPS_LEVEL_HIGH           1U
/***************************** main function *********************************/
static void gpio_irq_test(void *param)
{
    // rt_kprintf("GPIO-%d, Interrupt Asserted!!! \r\n",input_pin_index);
}
/* this function will toggle output pin and test intr of input pin */
static void gpio_thread(uint8_t argc, char **argv)
{
    int ret = 0;
    static u32 set_level = FGPIO_OPS_LEVEL_LOW;
    u32 get_level;
    
    /* pin init */
    rt_pin_mode(input_pin_index, PIN_MODE_INPUT);
    rt_pin_attach_irq(input_pin_index, PIN_IRQ_MODE_RISING, gpio_irq_test, RT_NULL);
    rt_pin_mode(output_pin_index, PIN_MODE_OUTPUT);
while (1)
{
    /* toggle operation */
    rt_pin_write(output_pin_index, set_level);
    set_level = (FGPIO_OPS_LEVEL_LOW == set_level) ? FGPIO_OPS_LEVEL_HIGH : FGPIO_OPS_LEVEL_LOW;
    rt_pin_irq_enable(input_pin_index, PIN_IRQ_ENABLE);
    rt_pin_write(output_pin_index, set_level);
    get_level = rt_pin_read(input_pin_index);
    if (set_level != get_level)
    {
        rt_kprintf(" input level not equals to output level!!!\r\n");
        RT_ASSERT(0);
        return -1;
    }
    else
    {
        // rt_kprintf(" ==> Set GPIO-%d to %s \r\n", output_pin_index, (set_level == FGPIO_PIN_LOW) ? "low" : "high");
        // rt_kprintf(" <== Get GPIO-%d as %s \r\n", input_pin_index, (get_level == FGPIO_PIN_LOW) ? "low" : "high");
    }
    FDriverMdelay(100);
}
}

int gpio_sample(int argc, char *argv[])
{
    rt_thread_t thread;
    rt_err_t res;
    thread = rt_thread_create("gpio_thread", gpio_thread, RT_NULL, 4096, 25, 10);
    res = rt_thread_startup(thread);
    RT_ASSERT(res == RT_EOK);
}

MSH_CMD_EXPORT(gpio_sample, FT GPIO toggle sample.);
#endif