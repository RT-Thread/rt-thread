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

#define LED7_PIN  GET_PIN(H, 7)
LPTIM_HandleTypeDef hlptim1;

extern int lptim_stop(void);

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
        HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_7);
    }
    
    /* All level of ITs can interrupt */
    __set_BASEPRI(0U); 

    lptim_stop();
    rt_kprintf("system returns to normal!\n");
}

static int lptim_control(uint8_t pre_value)
{
    if(pre_value > 7)
    {
       pre_value = 7; 
    }
    hlptim1.Instance->CFGR &= ~(7 << 9);      /* clear PRESC[2:0] */
    hlptim1.Instance->CFGR |= pre_value << 9; /* set PRESC[2:0]  */
    rt_kprintf("set lptim pre value [0x%x] success!\n", pre_value);
    
    return RT_EOK;
}

int lptim_start(void)
{
  /* ### Start counting in interrupt mode ############################# */
    if (HAL_LPTIM_Counter_Start_IT(&hlptim1, 32767) != HAL_OK)
    {
        LOG_D("lptim1 start counting failed!\n");
        return -RT_ERROR;
    }
    
    LOG_D("lptim1 start counting success!\n");
        
    return RT_EOK;
}

int lptim_stop(void)
{
   if (HAL_LPTIM_Counter_Stop_IT(&hlptim1) != HAL_OK)
   {
        LOG_D("lptim1 stop failed!\n");
        return -RT_ERROR;
   }
   
   LOG_D("lptim1 stop counting success!\n"); 
   
   return RT_EOK;
}

int lptim_init(void)
{
    rt_pin_mode(LED7_PIN, PIN_MODE_OUTPUT);
        
    hlptim1.Instance = LPTIM1;
    hlptim1.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
    hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV8;
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
        LOG_D("lptim init failed!\n");
        return -RT_ERROR;
    }
    LOG_D("lptim init success!\n");
    
    return RT_EOK;
}
INIT_DEVICE_EXPORT(lptim_init);

static int lptim_sample(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "start"))
        { 
           lptim_start();
           return RT_EOK;
        }
        else if (!strcmp(argv[1], "stop"))
        {
            lptim_stop();
            return RT_EOK;
        }
        else if (!strcmp(argv[1], "set"))
        {
            if (argc > 2)
            {
               lptim_control(atoi(argv[2]));
               return RT_EOK;
            }
            else
            {
                goto _exit;
            }
        }
        else
        {
            goto _exit;
        }
    }
_exit:
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("lptim_sample start    - start lptim, the LED7 will start blink\n");
        rt_kprintf("lptim_sample stop     - stop lptim, the LED7 will stop blink\n");
        rt_kprintf("lptim_sample set      - set the lptim prescaler to change LED7 blink frquency, lptim_sample set [0 - 7]\n");
    }

    return -RT_ERROR;
}
MSH_CMD_EXPORT(lptim_sample, low power timer sample);

#endif
