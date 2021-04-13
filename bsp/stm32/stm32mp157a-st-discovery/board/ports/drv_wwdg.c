/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-18     thread-liu        the first version
 */

#include <board.h>

#if defined(BSP_USING_WWDG)
#include "drv_config.h"
#include <string.h>
#include <stdlib.h>

//#define DRV_DEBUG
#define LOG_TAG             "drv.wwg"
#include <drv_log.h>

#define LED5_PIN  GET_PIN(A, 14)

static rt_uint8_t feed_flag = 0;
static WWDG_HandleTypeDef hwwdg1;

void WWDG1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_WWDG_IRQHandler(&hwwdg1);

    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* hwwdg)
{
    if(hwwdg->Instance==WWDG1)
    {
        if (feed_flag)
        {
            HAL_WWDG_Refresh(&hwwdg1);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_14);
        }
    }
}

static void wwdg_init()
{
    rt_pin_mode(LED5_PIN, PIN_MODE_OUTPUT);

    hwwdg1.Instance       = WWDG1;
    hwwdg1.Init.Prescaler = WWDG_PRESCALER_8;
    hwwdg1.Init.Window    = 0X5F;
    hwwdg1.Init.Counter   = 0x7F;
    hwwdg1.Init.EWIMode   = WWDG_EWI_ENABLE;

    if (HAL_WWDG_Init(&hwwdg1) != HAL_OK)
    {
        Error_Handler();
    }

    feed_flag = 1;
}

static void wwdg_control(uint8_t pre_value)
{
    if(pre_value > 7)
    {
       pre_value = 7;
    }
    hwwdg1.Instance->CFR &= ~(7 << 11);     /* clear WDGTB[2:0] */
    hwwdg1.Instance->CFR |= pre_value << 11; /* set WDGTB[2:0] */
}

static void wwdg_stop(void)
{
    feed_flag = 0;
}

static int wwdg_sample(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "run"))
        {
            wwdg_init();
        }
        else if (!strcmp(argv[1], "set"))
        {
            if (argc > 2)
            {
                wwdg_control(atoi(argv[2]));
            }
        }
        else if (!strcmp(argv[1], "stop"))
        {
            wwdg_stop();
        }
    }
    else
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("wwdg_sample run            - open wwdg, when feed wwdg in wwdg irq, the LD5 will blink\n");
        rt_kprintf("wwdg_sample stop           - stop to feed wwdg, system will reset\n");
        rt_kprintf("wwdg_sample set            - set the wwdg prescaler, wwdg_sample set [0 - 7]\n");
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(wwdg_sample, window watch dog sample);

#endif
