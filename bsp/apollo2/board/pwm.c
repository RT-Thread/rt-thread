/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "am_mcu_apollo.h"
#include "board.h"

#ifdef RT_USING_PWM

// LED3 is pin 19
#define AM_BSP_GPIO_PWM_LED                 19
#define AM_BSP_GPIO_CFG_PWM_LED             AM_HAL_PIN_19_TCTB1

#define AM_BSP_PWM_LED_TIMER                1
#define AM_BSP_PWM_LED_TIMER_SEG            AM_HAL_CTIMER_TIMERB
#define AM_BSP_PWM_LED_TIMER_INT            AM_HAL_CTIMER_INT_TIMERB1

/**
 * @brief LED brightness profile
 *
 * This function define LED brightness profile
 *
 * @return None.
 */
volatile uint32_t g_ui32Index = 0;
const uint32_t g_pui32Brightness[64] =
{
    1, 1, 1, 2, 3, 4, 6, 8,
    10, 12, 14, 17, 20, 23, 25, 28,
    31, 35, 38, 40, 43, 46, 49, 51,
    53, 55, 57, 59, 60, 61, 62, 62,
    63, 62, 62, 61, 60, 59, 57, 55,
    53, 51, 49, 46, 43, 40, 38, 35,
    32, 28, 25, 23, 20, 17, 14, 12,
    10, 8, 6, 4, 3, 2, 1, 1
};

/**
 * @brief Interrupt handler for the Timer
 *
 * This function is Interrupt handler for the Timer
 *
 * @return None.
 */
void am_ctimer_isr(void)
{
    /* Clear the interrupt that got us here */
    am_hal_ctimer_int_clear(AM_BSP_PWM_LED_TIMER_INT);

    /* Now set new PWM half-period for the LED */
    am_hal_ctimer_period_set(AM_BSP_PWM_LED_TIMER, AM_BSP_PWM_LED_TIMER_SEG,
                             64, g_pui32Brightness[g_ui32Index]);

    /* Set up the LED duty cycle for the next pulse */
    g_ui32Index = (g_ui32Index + 1) % 64;
}

/**
 * @brief Initialize the PWM
 *
 * This function initialize the PWM
 *
 * @return 0.
 */
int rt_hw_pwm_init(void)
{
    /* init pwm gpio */
    am_hal_gpio_pin_config(AM_BSP_GPIO_PWM_LED, AM_BSP_GPIO_CFG_PWM_LED);

    /* Configure a timer to drive the LED */
    am_hal_ctimer_config_single(AM_BSP_PWM_LED_TIMER, AM_BSP_PWM_LED_TIMER_SEG,
                                (AM_HAL_CTIMER_FN_PWM_REPEAT |
                                 AM_HAL_CTIMER_XT_2_048KHZ |
                                 AM_HAL_CTIMER_INT_ENABLE |
                                 AM_HAL_CTIMER_PIN_ENABLE));

    /* Set up initial timer period */
    am_hal_ctimer_period_set(AM_BSP_PWM_LED_TIMER, AM_BSP_PWM_LED_TIMER_SEG,
                             64, 32);

    /* Enable interrupts for the Timer we are using on this board */
    am_hal_ctimer_int_enable(AM_BSP_PWM_LED_TIMER_INT);
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_CTIMER);

    /* Start the timer */
    am_hal_ctimer_start(AM_BSP_PWM_LED_TIMER, AM_BSP_PWM_LED_TIMER_SEG);

    rt_kprintf("pwm_init!\n");

    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_BOARD_EXPORT(rt_hw_pwm_init);
#endif

#endif

/*@}*/
