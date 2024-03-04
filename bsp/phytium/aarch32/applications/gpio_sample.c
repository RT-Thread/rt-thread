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

#include "ftypes.h"
#include "fkernel.h"
#include "board.h"

#include "fgpio.h"
/**************************** Type Definitions *******************************/
/************************** Variable Definitions *****************************/
static rt_base_t input_pin_index = 0U;
static rt_base_t output_pin_index = 0U;
/***************** Macros (Inline Functions) Definitions *********************/
#define FGPIO_OPS_PIN_PORT_A           0U
#define FGPIO_OPS_PIN_PORT_B           1U
#define FGPIO_OPS_LEVEL_LOW            0U
#define FGPIO_OPS_LEVEL_HIGH           1U
/***************************** main function *********************************/
static void gpio_irq_test(void *param)
{
    rt_kprintf("GPIO-%d-%c-%d, Interrupt Asserted!!! \r\n",
               FGPIO_OPS_PIN_CTRL_ID(input_pin_index),
               (FGPIO_OPS_PIN_PORT_A == FGPIO_OPS_PIN_PORT_ID(input_pin_index)) ? 'a' : 'b',
               FGPIO_OPS_PIN_ID(input_pin_index));
}
/* this function will toggle output pin and test intr of input pin */
static int gpio_toggle_sample(uint8_t argc, char **argv)
{
    int ret = 0;
    static u32 set_level = FGPIO_OPS_LEVEL_LOW;
    u32 get_level;
    
#if defined(FIREFLY_DEMO_BOARD)
    /* pin init */
    input_pin_index = FGPIO_OPS_PIN_INDEX(3, 0, 1);
    rt_pin_mode(input_pin_index, PIN_MODE_INPUT);
    rt_pin_attach_irq(input_pin_index, PIN_IRQ_MODE_RISING, gpio_irq_test, RT_NULL);
    
    output_pin_index = FGPIO_OPS_PIN_INDEX(3, 0, 2);
    rt_pin_mode(output_pin_index, PIN_MODE_OUTPUT);
#endif

#if defined(E2000D_DEMO_BOARD)||defined(E2000Q_DEMO_BOARD)
    /* pin init */
    input_pin_index = FGPIO_OPS_PIN_INDEX(4, 0, 11);
    rt_pin_mode(input_pin_index, PIN_MODE_INPUT);
    rt_pin_attach_irq(input_pin_index, PIN_IRQ_MODE_RISING, gpio_irq_test, RT_NULL);
    
    output_pin_index = FGPIO_OPS_PIN_INDEX(4, 0, 12);
    rt_pin_mode(output_pin_index, PIN_MODE_OUTPUT);
#endif
    
    /* toggle operation */
    rt_pin_write(output_pin_index, set_level);
    set_level = (FGPIO_OPS_LEVEL_LOW == set_level) ? FGPIO_OPS_LEVEL_HIGH : FGPIO_OPS_LEVEL_LOW;
    rt_pin_irq_enable(input_pin_index, PIN_IRQ_ENABLE);
    rt_pin_write(output_pin_index, set_level);
    get_level = rt_pin_read(input_pin_index);
    if (set_level != get_level)
    {
        rt_kprintf(" input level not equals to output level!!!\r\n");
        return -1;
    }
    else
    {
        rt_kprintf(" ==> Set GPIO-%d-%c-%d to %s \r\n",
                FGPIO_OPS_PIN_CTRL_ID(output_pin_index), 
                (FGPIO_OPS_PIN_PORT_A == FGPIO_OPS_PIN_PORT_ID(output_pin_index)) ? 'a' : 'b', 
                FGPIO_OPS_PIN_ID(output_pin_index), 
                (set_level == FGPIO_PIN_LOW) ? "low" : "high");
        rt_kprintf(" <== Get GPIO-%d-%c-%d as %s \r\n",
                FGPIO_OPS_PIN_CTRL_ID(input_pin_index), 
                (FGPIO_OPS_PIN_PORT_A == FGPIO_OPS_PIN_PORT_ID(input_pin_index)) ? 'a' : 'b', 
                FGPIO_OPS_PIN_ID(input_pin_index), 
                (get_level == FGPIO_PIN_LOW) ? "low" : "high");
    }
    
    return ret;
}

MSH_CMD_EXPORT(gpio_toggle_sample, FT GPIO toggle sample.);
#endif