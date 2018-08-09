/*
 * FreeRTOS Kernel V10.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the ARM CM0 port.
 * CMSIS compatible layer to menage SysTick ticking source.
 *----------------------------------------------------------*/

#if configTICK_SOURCE == FREERTOS_USE_SYSTICK

#error NRF51 does not support SysTick module

/*-----------------------------------------------------------*/

#elif configTICK_SOURCE == FREERTOS_USE_RTC

#if configUSE_16_BIT_TICKS == 1
#error This port does not support 16 bit ticks.
#endif

#include "nrf_rtc.h"
#include "nrf_drv_clock.h"

/*-----------------------------------------------------------*/

void xPortSysTickHandler( void )
{
#if configUSE_TICKLESS_IDLE == 1
    nrf_rtc_event_clear(portNRF_RTC_REG, NRF_RTC_EVENT_COMPARE_0);
#endif

    BaseType_t switch_req = pdFALSE;
    uint32_t isrstate = portSET_INTERRUPT_MASK_FROM_ISR();

    uint32_t systick_counter = nrf_rtc_counter_get(portNRF_RTC_REG);
    nrf_rtc_event_clear(portNRF_RTC_REG, NRF_RTC_EVENT_TICK);

    if (configUSE_DISABLE_TICK_AUTO_CORRECTION_DEBUG == 0)
    {
        /* check FreeRTOSConfig.h file for more details on configUSE_DISABLE_TICK_AUTO_CORRECTION_DEBUG */
        TickType_t diff;
        diff = (systick_counter - xTaskGetTickCount()) & portNRF_RTC_MAXTICKS;

        /* At most 1 step if scheduler is suspended - the xTaskIncrementTick
         * would return the tick state from the moment when suspend function was called. */
        if ((diff > 1) && (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING))
        {
            diff = 1;
        }
        while ((diff--) > 0)
        {
            switch_req |= xTaskIncrementTick();
        }
    }
    else
    {
        switch_req = xTaskIncrementTick();
    }

    /* Increment the RTOS tick as usual which checks if there is a need for rescheduling */
    if ( switch_req != pdFALSE )
    {
        /* A context switch is required.  Context switching is performed in
        the PendSV interrupt.  Pend the PendSV interrupt. */
        SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
        __SEV();
    }

    portCLEAR_INTERRUPT_MASK_FROM_ISR( isrstate );
}

/*
 * Setup the RTC time to generate the tick interrupts at the required
 * frequency.
 */
void vPortSetupTimerInterrupt( void )
{
    /* Request LF clock */
    nrf_drv_clock_lfclk_request(NULL);

    /* Configure SysTick to interrupt at the requested rate. */
    nrf_rtc_prescaler_set(portNRF_RTC_REG, portNRF_RTC_PRESCALER);
    nrf_rtc_int_enable   (portNRF_RTC_REG, RTC_INTENSET_TICK_Msk);
    nrf_rtc_task_trigger (portNRF_RTC_REG, NRF_RTC_TASK_CLEAR);
    nrf_rtc_task_trigger (portNRF_RTC_REG, NRF_RTC_TASK_START);
    nrf_rtc_event_enable(portNRF_RTC_REG, RTC_EVTEN_OVRFLW_Msk);

    NVIC_SetPriority(portNRF_RTC_IRQn, configKERNEL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(portNRF_RTC_IRQn);
}

#if configUSE_TICKLESS_IDLE == 1

void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
{
    /*
     * Implementation note:
     *
     * To help debugging the option configUSE_TICKLESS_IDLE_SIMPLE_DEBUG was presented.
     * This option would make sure that even if program execution was stopped inside
     * this function no more than expected number of ticks would be skipped.
     *
     * Normally RTC works all the time even if firmware execution was stopped
     * and that may lead to skipping too much of ticks.
     */
    TickType_t enterTime;

    /* Make sure the SysTick reload value does not overflow the counter. */
    if ( xExpectedIdleTime > portNRF_RTC_MAXTICKS - configEXPECTED_IDLE_TIME_BEFORE_SLEEP )
    {
        xExpectedIdleTime = portNRF_RTC_MAXTICKS - configEXPECTED_IDLE_TIME_BEFORE_SLEEP;
    }
    /* Block all the interrupts globally */
#ifdef SOFTDEVICE_PRESENT
    do{
        uint8_t dummy = 0;
        uint32_t err_code = sd_nvic_critical_region_enter(&dummy);
        APP_ERROR_CHECK(err_code);
    }while (0);
#else
    __disable_irq();
#endif

    /* Configure CTC interrupt */
    enterTime = nrf_rtc_counter_get(portNRF_RTC_REG);

    if ( eTaskConfirmSleepModeStatus() != eAbortSleep )
    {
        TickType_t xModifiableIdleTime;
        TickType_t wakeupTime = (enterTime + xExpectedIdleTime) & portNRF_RTC_MAXTICKS;

        /* Stop tick events */
        nrf_rtc_int_disable(portNRF_RTC_REG, NRF_RTC_INT_TICK_MASK);

        /* Configure CTC interrupt */
        nrf_rtc_cc_set(portNRF_RTC_REG, 0, wakeupTime);
        nrf_rtc_event_clear(portNRF_RTC_REG, NRF_RTC_EVENT_COMPARE_0);
        nrf_rtc_int_enable(portNRF_RTC_REG, NRF_RTC_INT_COMPARE0_MASK);

        __DSB();

        /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
         * set its parameter to 0 to indicate that its implementation contains
         * its own wait for interrupt or wait for event instruction, and so wfi
         * should not be executed again.  However, the original expected idle
         * time variable must remain unmodified, so a copy is taken. */
        xModifiableIdleTime = xExpectedIdleTime;
        configPRE_SLEEP_PROCESSING( xModifiableIdleTime );
        if ( xModifiableIdleTime > 0 )
        {
#ifdef SOFTDEVICE_PRESENT

        uint32_t err_code = sd_app_evt_wait();
        APP_ERROR_CHECK(err_code);
#else
        /* No SD -  we would just block interrupts globally.
         * BASEPRI cannot be used for that because it would prevent WFE from wake up.
         */
         do{
            __WFE();
        } while (0 == (NVIC->ISPR[0]));
#endif
        }
        configPOST_SLEEP_PROCESSING( xExpectedIdleTime );
        nrf_rtc_int_disable(portNRF_RTC_REG, NRF_RTC_INT_COMPARE0_MASK);
        nrf_rtc_event_clear(portNRF_RTC_REG, NRF_RTC_EVENT_COMPARE_0);

        /* Correct the system ticks */
        {
            TickType_t diff;
            TickType_t exitTime;

            nrf_rtc_event_clear(portNRF_RTC_REG, NRF_RTC_EVENT_TICK);
            nrf_rtc_int_enable (portNRF_RTC_REG, NRF_RTC_INT_TICK_MASK);

            exitTime = nrf_rtc_counter_get(portNRF_RTC_REG);
            diff =  (exitTime - enterTime) & portNRF_RTC_MAXTICKS;

            /* It is important that we clear pending here so that our corrections are latest and in sync with tick_interrupt handler */
            NVIC_ClearPendingIRQ(portNRF_RTC_IRQn);

            if ((configUSE_TICKLESS_IDLE_SIMPLE_DEBUG) && (diff > xExpectedIdleTime))
            {
                diff = xExpectedIdleTime;
            }
            if (diff > 0)
            {
                vTaskStepTick(diff);
            }
        }
    }
#ifdef SOFTDEVICE_PRESENT
    uint32_t err_code = sd_nvic_critical_region_exit(0);
    APP_ERROR_CHECK(err_code);
#else
    __enable_irq();
#endif
}

#endif // configUSE_TICKLESS_IDLE

#else // configTICK_SOURCE
    #error  Unsupported configTICK_SOURCE value
#endif // configTICK_SOURCE == FREERTOS_USE_SYSTICK
