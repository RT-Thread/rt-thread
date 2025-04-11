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
 * 2025-04-08  liqiaozhong
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

/* Extract the index number from input_pin_index */
#define FGPIO_GET_CTRL(index) (((index) - FGPIO_GET_PIN(index) - (FGPIO_PORT_A * FGPIO_PIN_NUM)) / (FGPIO_PORT_NUM * FGPIO_PIN_NUM))

/* Extract the pin number from input_pin_index */
#define FGPIO_GET_PIN(index) ((index) % FGPIO_PIN_NUM)
/***************************** main function *********************************/
static void gpio_irq_test(s32 vector, void *param)
{
    FGpio *gpio_instance = (FGpio *)param;
    rt_kprintf("GPIO-%d-%d, PIN_IRQ_MODE_RISING Interrupt Asserted!!! \r\n",
                gpio_instance->config.ctrl,
                gpio_instance->config.pin);
}
/* this function will toggle output pin and test intr of input pin */
static int gpio_toggle_sample(uint8_t argc, char **argv)
{
    int res = 0;
    static u32 set_level = FGPIO_OPS_LEVEL_LOW;
    u32 get_level;

#if defined(FIREFLY_DEMO_BOARD)
    /* pin init */
    input_pin_index = FGPIO_ID(FGPIO_CTRL_0, FGPIO_PIN_0);
    rt_pin_mode(input_pin_index, PIN_MODE_INPUT);
    rt_pin_attach_irq(input_pin_index, PIN_IRQ_MODE_RISING, gpio_irq_test, RT_NULL);
    output_pin_index = FGPIO_ID(FGPIO_CTRL_4, FGPIO_PIN_13);
    rt_pin_mode(output_pin_index, PIN_MODE_OUTPUT);
#endif

#if defined(E2000D_DEMO_BOARD)||defined(E2000Q_DEMO_BOARD)
    /* pin init */
    input_pin_index = FGPIO_ID(FGPIO_CTRL_4, FGPIO_PIN_13);
    rt_pin_mode(input_pin_index, PIN_MODE_INPUT);
    rt_pin_attach_irq(input_pin_index, PIN_IRQ_MODE_RISING, gpio_irq_test, RT_NULL);
    output_pin_index = FGPIO_ID(FGPIO_CTRL_4, FGPIO_PIN_10);
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
        res = -1;
        goto exit;
    }
    else
    {
        rt_kprintf(" ==> Set GPIO-%d-%d to %s \r\n",
                FGPIO_GET_CTRL(output_pin_index),
                FGPIO_GET_PIN(output_pin_index),
                (set_level == FGPIO_PIN_LOW) ? "low" : "high");
        rt_kprintf(" <== Get GPIO-%d-%d as %s \r\n",
                FGPIO_GET_CTRL(input_pin_index),
                FGPIO_GET_PIN(input_pin_index),
                (get_level == FGPIO_PIN_LOW) ? "low" : "high");
    }
exit:
    /* print message on example run result */
    if (res == 0)
    {
        rt_kprintf("%s@%d:rtthread gpio test example [success].\r\n", __func__, __LINE__);
    }
    else
    {
        rt_kprintf("%s@%d:rtthread gpio test example [failure], res = %d\r\n", __func__, __LINE__, res);
    }

    return res;
}

MSH_CMD_EXPORT(gpio_toggle_sample, FT GPIO toggle sample.);
#endif