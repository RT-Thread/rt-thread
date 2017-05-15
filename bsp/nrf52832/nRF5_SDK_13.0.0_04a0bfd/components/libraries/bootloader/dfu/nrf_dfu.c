/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "nrf_dfu.h"

#include "nrf_dfu_transport.h"
#include "nrf_dfu_utils.h"
#include "nrf_bootloader_app_start.h"
#include "nrf_dfu_settings.h"
#include "nrf_gpio.h"
#include "app_scheduler.h"
#include "app_timer.h"
#include "nrf_log.h"
#include "boards.h"
#include "nrf_bootloader_info.h"
#include "nrf_dfu_req_handler.h"
#ifdef NRF_DFU_DEBUG_VERSION
#include "nrf_delay.h"
#endif //NRF_DFU_DEBUG_VERSION
#ifndef SOFTDEVICE_PRESENT
#include "nrf_soc.h"
#endif

#define SCHED_MAX_EVENT_DATA_SIZE       MAX(APP_TIMER_SCHED_EVENT_DATA_SIZE, 0)                 /**< Maximum size of scheduler events. */
#define BOOTLOADER_DFU_START            0xB1                                                    /**< Magic value written to retention register when starting DFU buttonless. */
#define SCHED_QUEUE_SIZE                20                                                      /**< Maximum number of events in the scheduler queue. */


// Weak function implementation

/** @brief Weak implemenation of nrf_dfu_check_enter.
 *
 * @note    This function must be overridden to enable entering DFU mode at will.
 *          Default behaviour is to enter DFU when BOOTLOADER_BUTTON is pressed.
 */
__WEAK bool nrf_dfu_enter_check(void)
{
    if (nrf_gpio_pin_read(BOOTLOADER_BUTTON) == 0)
    {
        return true;
    }

    if(NRF_POWER->GPREGRET == BOOTLOADER_DFU_START)
    {
        return true;
    }

    if (s_dfu_settings.enter_buttonless_dfu == 1)
    {
        s_dfu_settings.enter_buttonless_dfu = 0;
        APP_ERROR_CHECK(nrf_dfu_settings_write(NULL));
        return true;
    }
    return false;
}


// Internal Functions
static void reset_delay_timer_handler(void * p_context)
{
    NRF_LOG_DEBUG("Reset delay timer expired, resetting.\r\n");
#ifdef NRF_DFU_DEBUG_VERSION
    nrf_delay_ms(100);
#endif
    NVIC_SystemReset();
}

/**@brief Function for initializing the timer handler module (app_timer).
 */
static void timers_init(void)
{
    APP_ERROR_CHECK(app_timer_init());
    APP_ERROR_CHECK( app_timer_create(&nrf_dfu_utils_reset_delay_timer, APP_TIMER_MODE_SINGLE_SHOT, reset_delay_timer_handler) );
}


/** @brief Function for event scheduler initialization.
 */
static void scheduler_init(void)
{
    APP_SCHED_INIT(SCHED_MAX_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
}


static void wait_for_event()
{
    // Transport is waiting for event?
    while(true)
    {
        // Can't be emptied like this because of lack of static variables
#ifdef BLE_STACK_SUPPORT_REQD
        (void)sd_app_evt_wait();
#else
        __WFI();
#endif
        app_sched_execute();
    }
}


void nrf_dfu_wait()
{
#ifdef BLE_STACK_SUPPORT_REQD
        (void)sd_app_evt_wait();
#else
        __WFI();
#endif
    app_sched_execute();
}


uint32_t nrf_dfu_init()
{
    uint32_t ret_val = NRF_SUCCESS;
    uint32_t enter_bootloader_mode = 0;

    NRF_LOG_DEBUG("In real nrf_dfu_init\r\n");

    nrf_dfu_settings_init();
    timers_init();

    // Continue ongoing DFU operations
    // Note that this part does not rely on SoftDevice interaction
    ret_val = nrf_dfu_continue(&enter_bootloader_mode);
    if(ret_val != NRF_SUCCESS)
    {
        NRF_LOG_DEBUG("Could not continue DFU operation: 0x%08x\r\n", ret_val);
        enter_bootloader_mode = 1;
    }

    // Check if there is a reason to enter DFU mode
    // besides the effect of the continuation
    if (nrf_dfu_enter_check())
    {
        NRF_LOG_DEBUG("Application sent bootloader request\n");
        enter_bootloader_mode = 1;
    }

    NRF_POWER->GPREGRET = 0;

    if(enter_bootloader_mode != 0 || !nrf_dfu_app_is_valid())
    {
        scheduler_init();

        // Initializing transports
        ret_val = nrf_dfu_transports_init();
        if (ret_val != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Could not initalize DFU transport: 0x%08x\r\n", ret_val);
            return ret_val;
        }

        (void)nrf_dfu_req_handler_init();

        // This function will never return
        NRF_LOG_DEBUG("Waiting for events\r\n");
        wait_for_event();
        NRF_LOG_DEBUG("After waiting for events\r\n");
    }

    if (nrf_dfu_app_is_valid())
    {
        NRF_LOG_DEBUG("Jumping to: 0x%08x\r\n", MAIN_APPLICATION_START_ADDR);
        nrf_bootloader_app_start(MAIN_APPLICATION_START_ADDR);
    }

    // Should not be reached!
    NRF_LOG_INFO("After real nrf_dfu_init\r\n");
    return NRF_SUCCESS;
}
