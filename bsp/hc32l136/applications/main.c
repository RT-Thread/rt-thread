/*
 * Copyright (C) 2021, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-07     PJQ          first version
 */


/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "board.h"

#include <rtthread.h>
#include <rtdevice.h>

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* defined the LED pin: PC9 */
#define LED_PIN                 GET_PIN(D, 5)
#define KEY_PIN                 GET_PIN(B, 9)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
 uint8_t flag;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
void key_handler(void *param)
{
    flag = ~flag;
}

/**
 *******************************************************************************
 ** \brief  Main function of GPIO output
 **
 ** \param  None
 **
 ** \retval int32_t Return value, if needed
 **
 ******************************************************************************/
int main(void)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    rt_pin_attach_irq(KEY_PIN, PIN_IRQ_MODE_FALLING, key_handler, RT_NULL);
    rt_pin_irq_enable(KEY_PIN, PIN_IRQ_ENABLE);
    
    while(1)
    {
        if (flag == 0)
        {
            rt_pin_write(LED_PIN, PIN_HIGH);
            rt_thread_delay(500);
            rt_pin_write(LED_PIN, PIN_LOW);
            rt_thread_delay(500);
        }
        else
        {
            rt_pin_write(LED_PIN, PIN_HIGH);
            rt_thread_delay(2000);
            rt_pin_write(LED_PIN, PIN_LOW);
            rt_thread_delay(2000);
        }
     }
}

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
