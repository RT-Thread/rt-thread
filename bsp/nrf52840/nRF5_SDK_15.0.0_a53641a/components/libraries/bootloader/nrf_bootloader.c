/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#include "nrf_bootloader.h"

#include "compiler_abstraction.h"
#include "nrf.h"
#include "boards.h"
#include "sdk_config.h"
#include "nrf_power.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_dfu.h"
#include "nrf_error.h"
#include "nrf_dfu_settings.h"
#include "nrf_dfu_utils.h"
#include "nrf_bootloader_wdt.h"
#include "nrf_bootloader_info.h"
#include "nrf_bootloader_app_start.h"
#include "nrf_bootloader_fw_activation.h"
#include "nrf_bootloader_dfu_timers.h"
#include "app_scheduler.h"
#include "app_timer.h"

static nrf_dfu_observer_t m_user_observer; //<! Observer callback set by the user.

#define SCHED_QUEUE_SIZE      32          /**< Maximum number of events in the scheduler queue. */
#define SCHED_EVENT_DATA_SIZE MAX(NRF_DFU_SCHED_EVENT_DATA_SIZE, APP_TIMER_SCHED_EVENT_DATA_SIZE) /**< Maximum app_scheduler event size. */

#if !(defined(NRF_BL_DFU_ENTER_METHOD_BUTTON)    && \
      defined(NRF_BL_DFU_ENTER_METHOD_PINRESET)  && \
      defined(NRF_BL_DFU_ENTER_METHOD_GPREGRET)  && \
      defined(NRF_BL_DFU_ENTER_METHOD_BUTTONLESS))
    #error Configuration file is missing flags. Update sdk_config.h.
#endif

STATIC_ASSERT((NRF_BL_DFU_INACTIVITY_TIMEOUT_MS >= 100) || (NRF_BL_DFU_INACTIVITY_TIMEOUT_MS == 0),
             "NRF_BL_DFU_INACTIVITY_TIMEOUT_MS must be 100 ms or more, or 0 to indicate that it is disabled.");

#if defined(NRF_LOG_BACKEND_FLASH_START_PAGE)
STATIC_ASSERT(NRF_LOG_BACKEND_FLASH_START_PAGE != 0, 
    "If nrf_log flash backend is used it cannot use space after code because it would collide with settings page.");
#endif

/**@brief Weak implemenation of nrf_dfu_init
 *
 * @note   This function will be overridden if nrf_dfu.c is
 *         compiled and linked with the project
 */
 #if (__LINT__ != 1)
__WEAK uint32_t nrf_dfu_init(nrf_dfu_observer_t observer)
{
    NRF_LOG_DEBUG("in weak nrf_dfu_init");
    return NRF_SUCCESS;
}
#endif


/**@brief Weak implementation of nrf_dfu_init
 *
 * @note    This function must be overridden in application if
 *          user-specific initialization is needed.
 */
__WEAK uint32_t nrf_dfu_init_user(void)
{
    NRF_LOG_DEBUG("in weak nrf_dfu_init_user");
    return NRF_SUCCESS;
}


static void bootloader_reset(void)
{
    NRF_LOG_DEBUG("Resetting bootloader.");

    NRF_LOG_FINAL_FLUSH();

#if NRF_MODULE_ENABLED(NRF_LOG_BACKEND_RTT)
    // To allow the buffer to be flushed by the host.
    nrf_delay_ms(100);
#endif

    NVIC_SystemReset();
}


static void inactivity_timeout(void)
{
    NRF_LOG_INFO("Inactivity timeout.");
    bootloader_reset();
}


/**@brief Function for handling DFU events.
 */
static void dfu_observer(nrf_dfu_evt_type_t evt_type)
{
    switch (evt_type)
    {
        case NRF_DFU_EVT_DFU_STARTED:
        case NRF_DFU_EVT_OBJECT_RECEIVED:
            nrf_bootloader_dfu_inactivity_timer_restart(NRF_BL_DFU_INACTIVITY_TIMEOUT_MS, inactivity_timeout);
            break;
        case NRF_DFU_EVT_DFU_COMPLETED:
        case NRF_DFU_EVT_DFU_ABORTED:
            bootloader_reset();
            break;
        default:
            break;
    }

    if (m_user_observer)
    {
        m_user_observer(evt_type);
    }
}


/**@brief Function for initializing the event scheduler.
 */
static void scheduler_init(void)
{
    APP_SCHED_INIT(SCHED_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
}


/**@brief Suspend the CPU until an interrupt occurs.
 */
static void wait_for_event(void)
{
#ifdef BLE_STACK_SUPPORT_REQD
    (void)sd_app_evt_wait();
#else
    // Wait for an event.
    __WFE();
    // Clear the internal event register.
    __SEV();
    __WFE();
#endif
}


/**@brief Continually sleep and process tasks whenever woken.
 */
static void loop_forever(void)
{
    while (true)
    {
        //feed the watchdog if enabled.
        nrf_bootloader_wdt_feed();

        app_sched_execute();

        if (!NRF_LOG_PROCESS())
        {
            wait_for_event();
        }
    }
}

/**@brief Function for initializing button used to enter DFU mode.
 */
static void dfu_enter_button_init(void)
{
    nrf_gpio_cfg_sense_input(NRF_BL_DFU_ENTER_METHOD_BUTTON_PIN,
                             BUTTON_PULL,
                             NRF_GPIO_PIN_SENSE_LOW);
}


static bool crc_on_valid_app_required(void)
{
    bool ret = true;
    if (NRF_BL_APP_CRC_CHECK_SKIPPED_ON_SYSTEMOFF_RESET &&
        (nrf_power_resetreas_get() & NRF_POWER_RESETREAS_OFF_MASK))
    {
        nrf_power_resetreas_clear(NRF_POWER_RESETREAS_OFF_MASK);
        ret = false;
    }
    else if (NRF_BL_APP_CRC_CHECK_SKIPPED_ON_GPREGRET2 &&
            (nrf_power_gpregret2_get() & BOOTLOADER_DFU_SKIP_CRC))
    {
        nrf_power_gpregret2_set(nrf_power_gpregret2_get() & ~BOOTLOADER_DFU_SKIP_CRC);
        ret = false;
    }
    else
    {
    }

    return ret;
}


/**@brief Function for clearing all DFU enter flags that
 *        preserve state during reset.
 *
 * @details This is used to make sure that each of these flags
 *          is checked only once after reset.
 */
static void dfu_enter_flags_clear(void)
{
    if (NRF_BL_DFU_ENTER_METHOD_PINRESET &&
       (NRF_POWER->RESETREAS & POWER_RESETREAS_RESETPIN_Msk))
    {
        // Clear RESETPIN flag.
        NRF_POWER->RESETREAS |= POWER_RESETREAS_RESETPIN_Msk;
    }

    if (NRF_BL_DFU_ENTER_METHOD_GPREGRET &&
       (nrf_power_gpregret_get() & BOOTLOADER_DFU_START))
    {
        // Clear DFU mark in GPREGRET register.
        nrf_power_gpregret_set(nrf_power_gpregret_get() & ~BOOTLOADER_DFU_START);
    }

    if (NRF_BL_DFU_ENTER_METHOD_BUTTONLESS &&
       (s_dfu_settings.enter_buttonless_dfu == 1))
    {
        // Clear DFU flag in flash settings.
        s_dfu_settings.enter_buttonless_dfu = 0;
        APP_ERROR_CHECK(nrf_dfu_settings_write(NULL));
    }
}


/**@brief Function for checking whether to enter DFU mode or not.
 */
static bool dfu_enter_check(void)
{
    if (!nrf_dfu_app_is_valid(crc_on_valid_app_required()))
    {
        NRF_LOG_DEBUG("DFU mode because app is not valid.");
        return true;
    }

    if (NRF_BL_DFU_ENTER_METHOD_BUTTON &&
       (nrf_gpio_pin_read(NRF_BL_DFU_ENTER_METHOD_BUTTON_PIN) == 0))
    {
        NRF_LOG_DEBUG("DFU mode requested via button.");
        return true;
    }

    if (NRF_BL_DFU_ENTER_METHOD_PINRESET &&
       (NRF_POWER->RESETREAS & POWER_RESETREAS_RESETPIN_Msk))
    {
        NRF_LOG_DEBUG("DFU mode requested via pin-reset.");
        return true;
    }

    if (NRF_BL_DFU_ENTER_METHOD_GPREGRET &&
       (nrf_power_gpregret_get() & BOOTLOADER_DFU_START))
    {
        NRF_LOG_DEBUG("DFU mode requested via GPREGRET.");
        return true;
    }

    if (NRF_BL_DFU_ENTER_METHOD_BUTTONLESS &&
       (s_dfu_settings.enter_buttonless_dfu == 1))
    {
        NRF_LOG_DEBUG("DFU mode requested via bootloader settings.");
        return true;
    }

    return false;
}


ret_code_t nrf_bootloader_init(nrf_dfu_observer_t observer)
{
    NRF_LOG_DEBUG("In nrf_bootloader_init");

    uint32_t                              ret_val;
    nrf_bootloader_fw_activation_result_t activation_result;
    uint32_t                              initial_timeout;
    bool                                  dfu_enter = false;

    m_user_observer = observer;

    if (NRF_BL_DFU_ENTER_METHOD_BUTTON)
    {
        dfu_enter_button_init();
    }

    ret_val = nrf_dfu_settings_init(false);
    if (ret_val != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    // Check if an update needs to be activated and activate it.
    activation_result = nrf_bootloader_fw_activate();

    switch (activation_result)
    {
        case ACTIVATION_NONE:
            initial_timeout = NRF_BL_DFU_INACTIVITY_TIMEOUT_MS;
            dfu_enter       = dfu_enter_check();
            break;

        case ACTIVATION_SUCCESS_EXPECT_ADDITIONAL_UPDATE:
            initial_timeout = NRF_BL_DFU_CONTINUATION_TIMEOUT_MS;
            dfu_enter       = true;
            break;

        case ACTIVATION_SUCCESS:
            bootloader_reset();
            NRF_LOG_ERROR("Should never come here: After bootloader_reset()");
            return NRF_ERROR_INTERNAL; // Should not reach this.

        case ACTIVATION_ERROR:
        default:
            return NRF_ERROR_INTERNAL;
    }

    if (dfu_enter)
    {
        nrf_bootloader_wdt_init();

        scheduler_init();

        // Clear all DFU stop flags.
        dfu_enter_flags_clear();

        // Call user-defined init function if implemented
        ret_val = nrf_dfu_init_user();
        if (ret_val != NRF_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }

        nrf_bootloader_dfu_inactivity_timer_restart(initial_timeout, inactivity_timeout);

        ret_val = nrf_dfu_init(dfu_observer);
        if (ret_val != NRF_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }

        NRF_LOG_DEBUG("Enter main loop");
        loop_forever(); // This function will never return.
        NRF_LOG_ERROR("Should never come here: After looping forever.");
    }
    else
    {
        // Erase additional data like peer data or advertisement name
        ret_val = nrf_dfu_settings_additional_erase();
        if (ret_val != NRF_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }

        nrf_bootloader_app_start();
        NRF_LOG_ERROR("Should never come here: After nrf_bootloader_app_start()");
    }

    // Should not be reached.
    return NRF_ERROR_INTERNAL;
}
