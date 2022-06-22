/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-27     thread-liu        first version
 */

#include "board.h"
//#define DRV_DEBUG
#define LOG_TAG             "drv.pwr"
#include <drv_log.h>

extern int lptim_start(void);
extern int lptim_stop(void);

static RCC_ClkInitTypeDef  RCC_ClkInit = {0};

#define __WAIT_EVENT_TIMEOUT(__CONDITION__, __TIMEOUT_VAL__)                 \
  do {                                                                       \
    __IO uint32_t count = __TIMEOUT_VAL__ * (SystemCoreClock / 20U / 1000U); \
    do                                                                       \
    {                                                                        \
      if (count-- == 0U)                                                     \
      {                                                                      \
        return  HAL_TIMEOUT;                                                 \
      }                                                                      \
    }                                                                        \
    while (__CONDITION__ == 0U);                                             \
  } while(0)

/* Back up clock tree */
static void backup_cm4_clocks(void)
{
    rt_uint32_t *pFLatency = NULL;

    /* Back up MCU clock configuration */
    HAL_RCC_GetClockConfig(&RCC_ClkInit, pFLatency);
}

/* Restore the CM4 clock source muxer and the CM4 prescaler. */
rt_err_t restore_cm4_clock(void)
{
    /* Update SystemCoreClock variable */
    SystemCoreClock = HAL_RCC_GetSystemCoreClockFreq();

    /* Enable PLL3 if needed */
    if (RCC_ClkInit.MCUInit.MCU_Clock == RCC_MCUSSOURCE_PLL3)
    {
    /* Enable PLL3 */
    __HAL_RCC_PLL3_ENABLE();

    /* Wait till PLL3 is ready */
    __WAIT_EVENT_TIMEOUT(__HAL_RCC_GET_FLAG(RCC_FLAG_PLL3RDY), CLOCKSWITCH_TIMEOUT_VALUE);

    /* Enable PLL3 outputs */
    __HAL_RCC_PLL3CLKOUT_ENABLE(RCC_PLL3_DIVP | RCC_PLL3_DIVQ | RCC_PLL3_DIVR);
    }

    /* Configure MCU clock only */
    __HAL_RCC_MCU_SOURCE(RCC_ClkInit.MCUInit.MCU_Clock);

    /* Wait till MCU is ready */
    __WAIT_EVENT_TIMEOUT(__HAL_RCC_GET_FLAG(RCC_FLAG_MCUSSRCRDY),
                       CLOCKSWITCH_TIMEOUT_VALUE);

    /* Update SystemCoreClock variable */
    SystemCoreClock = HAL_RCC_GetSystemCoreClockFreq();

    /* Reconfigure Systick */
    if (HAL_InitTick(uwTickPrio) != HAL_OK)
    {
        return RT_ERROR;
    }

    /* Set MCU division factor */
    __HAL_RCC_MCU_DIV(RCC_ClkInit.MCUInit.MCU_Div);

    /* Wait till MCUDIV is ready */
    __WAIT_EVENT_TIMEOUT(__HAL_RCC_GET_FLAG(RCC_FLAG_MCUDIVRDY),
                       CLOCKSWITCH_TIMEOUT_VALUE);

    /* Update SystemCoreClock variable */
    SystemCoreClock = HAL_RCC_GetSystemCoreClockFreq();

    /* Reconfigure Systick */
    if (HAL_InitTick(uwTickPrio) != HAL_OK)
    {
        return RT_ERROR;
    }

    return RT_EOK;
}

void RCC_WAKEUP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_RCC_WAKEUP_IRQHandler();

    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_RCC_WAKEUP_Callback()
{
    if (__HAL_PWR_GET_FLAG(PWR_FLAG_STOP) == 1U)
    {
        __HAL_PWR_CLEAR_FLAG(PWR_FLAG_STOP);
    }

    restore_cm4_clock();
    /* All level of ITs can interrupt */
    __set_BASEPRI(0U);

    rt_kprintf("system exit stop mode success!\n");
}

static void enter_sleep_mode(void)
{
    __set_BASEPRI((1) << (8 - __NVIC_PRIO_BITS));

    lptim_start();

    HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

static void enter_stop_mode(void)
{
    /*
     * Only the IT with the highest priority (0 value) can interrupt.
     * RCC_WAKEUP_IRQn IT is intended to have the highest priority and to be the
     * only one IT having this value
     * RCC_WAKEUP_IRQn is generated only when RCC is completely resumed from
     * CSTOP (protection mechanism)
     */
    __set_BASEPRI((1) << (8 - __NVIC_PRIO_BITS));

    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_STOP);
    backup_cm4_clocks();
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}

static void pm_wackup_key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI13_IRQn, 0x01, 0);
    HAL_NVIC_EnableIRQ(EXTI13_IRQn);
}

int drv_pm_hw_init(void)
{
    pm_wackup_key_init();

    return RT_EOK;
}
INIT_BOARD_EXPORT(drv_pm_hw_init);

static int pwr_sample(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (!rt_strcmp(argv[1], "stop"))
        {
           rt_kprintf("system will enter stop mode! you can press USER2 button to exit this mode\n");
           enter_stop_mode();
           return RT_EOK;

        }
        else if (!rt_strcmp(argv[1], "sleep"))
        {
           rt_kprintf("system will enter sleep mode! lptim1 will wake up the system\n");
           enter_sleep_mode();
           return RT_EOK;
        }
        else
        {
            goto _exit;
        }
    }
_exit:
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("pwr_sample stop      - system enter stop mode\n");
        rt_kprintf("pwr_sample sleep     - system enter sleep mode\n");
    }

    return -RT_ERROR;
}
MSH_CMD_EXPORT(pwr_sample, enter low power mode sample);
