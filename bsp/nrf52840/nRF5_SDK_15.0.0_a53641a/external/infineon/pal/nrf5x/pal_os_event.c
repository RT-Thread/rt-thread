/**
* \copyright
* Copyright(c) 2018, Infineon Technologies AG
* All rights reserved.
*
* This software is provided with terms and conditions as specified in OPTIGA(TM) Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author Infineon AG
*
* \file
*
* \brief This file implements the platform abstraction layer APIs for os event/scheduler.
*
* \addtogroup  grPAL
* @{
*/

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include "pal_os_event.h"
#include "nrf_rtc.h"
#include "nrf_drv_rtc.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/
/// @cond hidden 
/// Callback function when timer elapses
static volatile register_callback callback_registered = NULL;
/// Pointer to store upper layer callback context (For example: Ifx i2c context)
static void * callback_ctx;

const nrf_drv_rtc_t rtc2 = NRF_DRV_RTC_INSTANCE(2);
static nrf_drv_rtc_config_t m_rtc2_config = NRF_DRV_RTC_DEFAULT_CONFIG;

// Tick count for pal_os_timer
volatile uint32_t g_tick_count = 0;

/**
*  Timer callback handler. 
*
*  This get called from the TIMER elapse event.<br>
*  Once the timer expires, the registered callback funtion gets called from the timer event handler, if
*  the call back is not NULL.<br>
*
*\param[in] args Callback argument
*
*/
static void ifx_rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
    volatile register_callback callback;

    if (int_type == NRF_DRV_RTC_INT_TICK)
    {
        g_tick_count++;
    }

    if (int_type == NRF_DRV_RTC_INT_COMPARE0)
    {
        nrf_drv_rtc_cc_disable(&rtc2, 0);

        if (callback_registered != NULL)
        {
            callback = callback_registered;
            callback_registered = NULL;
            callback(callback_ctx);
        }
    }
}

/// @endcond

void pal_os_event_init()
{
    // Initialize the RTC2 driver instance
    APP_ERROR_CHECK(nrf_drv_rtc_init(&rtc2, &m_rtc2_config, ifx_rtc_handler));

    // Set the prescaler to approximately get 1 ms intervals
    m_rtc2_config.prescaler = 31;

    // Enable tick event and interrupt
    nrf_drv_rtc_tick_enable(&rtc2, true);

    // Power on RTC instance
    nrf_drv_rtc_enable(&rtc2);
}

/**
* Platform specific event call back registration function to trigger once when timer expires.
* <br>
*
* <b>API Details:</b>
*         This function registers the callback function supplied by the caller.<br>
*         It triggers a timer with the supplied time interval in microseconds.<br>
*         Once the timer expires, the registered callback function gets called.<br>
* 
* \param[in] callback              Callback function pointer
* \param[in] callback_args         Callback arguments
* \param[in] time_us               time in micro seconds to trigger the call back
*
*/
void pal_os_event_register_callback_oneshot(register_callback callback, 
                                            void* callback_args, 
                                            uint32_t time_us)
{
    callback_registered = callback;
    callback_ctx = callback_args;

    // Clear the counter
    nrf_drv_rtc_counter_clear(&rtc2);

    // Set the compare register to trigger approximately at time_us
    APP_ERROR_CHECK(nrf_drv_rtc_cc_set(&rtc2, 0, (time_us / 1024) + 1 , true));
}

/**
* @}
*/

