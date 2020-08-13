/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2020-06-19     thread-liu      first version
 */

#include <board.h>

#ifdef BSP_USING_LPTIM
#include "drv_config.h"
#include <string.h>
#include <stdlib.h>

//#define DRV_DEBUG
#define LOG_TAG             "drv.lptimer"
#include <drv_log.h>

LPTIM_HandleTypeDef hlptim1;

void LPTIM1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    
    HAL_LPTIM_IRQHandler(&hlptim1);
    
    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
    if(hlptim->Instance == LPTIM1)
    {
        rt_kprintf("hello rt-thread!\n");
    }
}

static int lptim_control(uint8_t pre_value)
{
    if(pre_value > 7)
    {
       pre_value = 7; 
    }
    hlptim1.Instance->CFGR &= ~(7 << 9);      /* clear PRESC[2:0] */
    hlptim1.Instance->CFGR |= pre_value << 9; /* set PRESC[2:0]  */

    return RT_EOK;
}

/**
 * This function initialize the lptim
 */
static int lptim_init(void)
{
    hlptim1.Instance = LPTIM1;
    hlptim1.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
    hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV1;
    hlptim1.Init.UltraLowPowerClock.Polarity = LPTIM_CLOCKPOLARITY_RISING;
    hlptim1.Init.UltraLowPowerClock.SampleTime = LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION;
    hlptim1.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
    hlptim1.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
    hlptim1.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
    hlptim1.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
    hlptim1.Init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
    hlptim1.Init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;
    if (HAL_LPTIM_Init(&hlptim1) != HAL_OK)
    {
        LOG_D("LPTIM Init Error!\n");
        return -RT_ERROR;
    }
  /* ### Start counting in interrupt mode ############################# */
    if (HAL_LPTIM_Counter_Start_IT(&hlptim1, 5000) != HAL_OK)
    {
        LOG_D("LPTIM Start Counting Error!\n");
        return -RT_ERROR;
    }
    
    return RT_EOK;
}

static int lptim_deinit()
{
   if (HAL_LPTIM_DeInit(&hlptim1) != HAL_OK)
   {
        LOG_D("LPTIM Deinit Error!\n");
        return -RT_ERROR;
   }
    
    return RT_EOK;
}

static int lptim_sample(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "run"))
        { 
           lptim_init(); 
        }
        else if (!strcmp(argv[1], "stop"))
        {
            lptim_deinit();
        }
        else if (!strcmp(argv[1], "set"))
        {
            if (argc > 2)
            {
               lptim_control(atoi(argv[2]));
            }     
        }
    }
    else
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("lptim_sample run            - open lptim, shell will printf 'hello rt-thread'\n");
        rt_kprintf("lptim_sample set            - set the lptim prescaler, lptim_sample set [0 - 7]\n");
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(lptim_sample, low power timer sample);

#endif
