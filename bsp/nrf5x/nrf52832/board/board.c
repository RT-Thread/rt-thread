/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-29     supperthomas first version
 *
 */
#include <rtthread.h>
#include <rthw.h>
#include <nrfx_systick.h>

#include "board.h"
#include "drv_uart.h"
#ifdef BSP_USING_SOFTDEVICE
#include <nrfx_rtc.h>
#include <nrfx_clock.h>
#include "app_error.h"
#include "nrf_drv_clock.h"
const nrfx_rtc_t rtc = NRFX_RTC_INSTANCE(1); /**< Declaring an instance of nrf_drv_rtc for RTC0. */

static void rtc_handler(nrfx_rtc_int_type_t int_type)
{
    if (int_type == NRFX_RTC_INT_TICK)
    {
        rt_interrupt_enter();

        rt_tick_increase();

        rt_interrupt_leave();
    }
}
#else
/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
void SysTick_Configuration(void)
{
#ifdef BSP_USING_SOFTDEVICE
    nrf_drv_clock_init();
    nrf_drv_clock_lfclk_request(NULL);

    uint32_t err_code;
#define TICK_RATE_HZ  RT_TICK_PER_SECOND
#define SYSTICK_CLOCK_HZ  ( 32768UL )

#define NRF_RTC_REG        NRF_RTC1
    /* IRQn used by the selected RTC */
#define NRF_RTC_IRQn       RTC1_IRQn
    /* Constants required to manipulate the NVIC. */
#define NRF_RTC_PRESCALER  ( (uint32_t) (NRFX_ROUNDED_DIV(SYSTICK_CLOCK_HZ, TICK_RATE_HZ) - 1) )
    nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;
    config.prescaler = NRF_RTC_PRESCALER;

    err_code = nrfx_rtc_init(&rtc, &config, rtc_handler);
    // APP_ERROR_CHECK(err_code);
    nrfx_rtc_tick_enable(&rtc, true);
#define COMPARE_COUNTERTIME  (3UL)                                        /**< Get Compare event COMPARE_TIME seconds after the counter starts from 0. */
    //Set compare channel to trigger interrupt after COMPARE_COUNTERTIME seconds
    err_code = nrfx_rtc_cc_set(&rtc, 0, COMPARE_COUNTERTIME * 8, true);
    // APP_ERROR_CHECK(err_code);

    //Power on RTC instance
    nrfx_rtc_enable(&rtc);
#else
    /* Set interrupt priority */
    NVIC_SetPriority(SysTick_IRQn, 0xf);

    /* Configure SysTick to interrupt at the requested rate. */
    nrf_systick_load_set(SystemCoreClock / RT_TICK_PER_SECOND);
    nrf_systick_val_clear();
    nrf_systick_csr_set(NRF_SYSTICK_CSR_CLKSOURCE_CPU | NRF_SYSTICK_CSR_TICKINT_ENABLE
                        | NRF_SYSTICK_CSR_ENABLE);
#endif
}


void rt_hw_board_init(void)
{
    rt_hw_interrupt_enable(0);
    // sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);
    /* Activate deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    SysTick_Configuration();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef BSP_USING_SOFTDEVICE
    extern uint32_t  Image$$RW_IRAM1$$Base;
    uint32_t const *const m_ram_start  = &Image$$RW_IRAM1$$Base;
    if ((uint32_t)m_ram_start == 0x20000000)
    {
        rt_kprintf("\r\n using softdevice the RAM couldn't be %p,please use the templete from package\r\n", m_ram_start);
        while (1);
    }
    else
    {
        rt_kprintf("\r\n using softdevice the RAM at %p\r\n", m_ram_start);
    }
#endif

}

