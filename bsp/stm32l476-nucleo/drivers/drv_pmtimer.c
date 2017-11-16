/*
 * File      : drv_pmtimer.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author          Notes
 * 2017-08-01     tanek           the first version
 */
 
#include "drv_pmtimer.h"
#include "board.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

#ifdef RT_USING_PM
#include <drivers/pm.h>

//#define PMTIMER_DEBUG_LED

static rt_uint32_t _count_freq = 0;

static LPTIM_HandleTypeDef LptimHandle;

void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef* hlptim)
{

    if(hlptim->Instance==LPTIM1)
    {
        /* Peripheral clock enable */
        __HAL_RCC_LPTIM1_CLK_ENABLE();
    }
}

void LPTIM1_IRQHandler(void)
{
    HAL_LPTIM_IRQHandler(&LptimHandle); 
}

void HAL_LPTIM_CompareMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
    rt_pm_exit();
}

/**
 * This function get current count value of LPTIM
 *
 * @return the count vlaue
 */
rt_uint32_t stm32l4_lptim_get_tick(void)
{
    return HAL_LPTIM_ReadCounter(&LptimHandle);
}

/**
 * This function get the max value that LPTIM can count
 *
 * @return the max count
 */
rt_uint32_t stm32l4_lptim_tick_max(void)
{
    return (0xFFFF);
}

/**
 * This function start LPTIM with reload value
 *
 * @param reload The value that LPTIM count down from
 *
 * @return RT_EOK 
 */
rt_err_t stm32l4_lptim_start(rt_uint32_t reload)
{  
    HAL_LPTIM_TimeOut_Start_IT(&LptimHandle, 0xFFFF, reload);
    
    return (RT_EOK);
}

/**
 * This function stop LPTIM
 */
void stm32l4_lptim_stop(void)
{
    HAL_LPTIM_TimeOut_Stop_IT(&LptimHandle);
}

/**
 * This function get the count clock of LPTIM
 *
 * @return the count clock frequency in Hz
 */
rt_uint32_t stm32l4_lptim_get_countfreq(void)
{
    return (_count_freq);
}

/**
 * This function initialize the lptim
 */
int stm32l4_hw_lptim_init(void)
{
    LptimHandle.Instance = LPTIM1;
    LptimHandle.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
    LptimHandle.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV128;
    LptimHandle.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
    LptimHandle.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
    LptimHandle.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
    LptimHandle.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
    if (HAL_LPTIM_Init(&LptimHandle) != HAL_OK)
    {
        return -1;
    }
    
    _count_freq = 32768 / 128;

    NVIC_ClearPendingIRQ(LPTIM1_IRQn);
    NVIC_SetPriority(LPTIM1_IRQn, 0);
    NVIC_EnableIRQ(LPTIM1_IRQn);
    
    //stm32l4_lptim_start(400);
    
    return 0;
}
INIT_BOARD_EXPORT(stm32l4_hw_lptim_init);

#endif /* RT_USING_PM */
