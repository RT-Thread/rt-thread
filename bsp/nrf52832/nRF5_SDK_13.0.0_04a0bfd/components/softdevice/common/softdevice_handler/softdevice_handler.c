/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
#include "softdevice_handler.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_assert.h"
#include "nrf_soc.h"
#include "nrf_nvic.h"
#include "sdk_common.h"

#if NRF_MODULE_ENABLED(CLOCK)
#include "nrf_drv_clock.h"
#endif // NRF_MODULE_ENABLED(CLOCK)
#if NRF_MODULE_ENABLED(POWER)
#include "nrf_drv_power.h"
#endif // NRF_MODULE_ENABLED(POWER)
#include "app_error.h"

#if NRF_MODULE_ENABLED(RNG)
#include "nrf_drv_rng.h"
#endif // NRF_MODULE_ENABLED(RNG)

#define NRF_LOG_MODULE_NAME "SDH"
#include "nrf_log.h"
#if defined(ANT_STACK_SUPPORT_REQD) && defined(BLE_STACK_SUPPORT_REQD)
    #include "ant_interface.h"
#elif defined(ANT_STACK_SUPPORT_REQD)
    #include "ant_interface.h"
#elif defined(BLE_STACK_SUPPORT_REQD)
    #include "ble.h"
#endif


#define RAM_START_ADDRESS             0x20000000
#define SOFTDEVICE_EVT_IRQ            SD_EVT_IRQn                       /**< SoftDevice Event IRQ number. Used for both protocol events and SoC events. */
#define SOFTDEVICE_EVT_IRQHandler     SD_EVT_IRQHandler
#define RAM_TOTAL_SIZE                ((NRF_FICR->INFO.RAM) * 1024)
#define RAM_END_ADDRESS               (RAM_START_ADDRESS + RAM_TOTAL_SIZE)


static softdevice_evt_schedule_func_t m_evt_schedule_func;              /**< Pointer to function for propagating SoftDevice events to the scheduler. */
static sys_evt_handler_t              m_sys_evt_handler;                /**< Application event handler for handling System (SOC) events.  */

static volatile bool                  m_softdevice_enabled = false;     /**< Variable to indicate whether the SoftDevice is enabled. */
static volatile bool                  m_suspended;                      /**< Current state of the event handler. */

// The following three definitions is needed only if BLE events are needed to be pulled from the stack.
#ifdef BLE_STACK_SUPPORT_REQD
static uint8_t                      * mp_ble_evt_buffer;                /**< Buffer for receiving BLE events from the SoftDevice. */
static uint16_t                       m_ble_evt_buffer_size;            /**< Size of BLE event buffer. */
static ble_evt_handler_t              m_ble_evt_handler;                /**< Application event handler for handling BLE events. */
#endif

#ifdef ANT_STACK_SUPPORT_REQD
// The following two definitions are needed only if ANT events are needed to be pulled from the stack.
static ant_evt_t                      m_ant_evt_buffer;                 /**< Buffer for receiving ANT events from the SoftDevice. */
static ant_evt_handler_t              m_ant_evt_handler;                /**< Application event handler for handling ANT events.  */
#endif


#if defined(S1XX)
/**@brief       Callback function for asserts in the SoftDevice.
 *
 * @details     A pointer to this function will be passed to the SoftDevice. This function will be
 *              called if an ASSERT statement in the SoftDevice fails.
 *
 * @param[in]   pc         The value of the program counter when the ASSERT call failed.
 * @param[in]   line_num   Line number of the failing ASSERT call.
 * @param[in]   file_name  File name of the failing ASSERT call.
 */
void softdevice_assertion_handler(uint32_t pc, uint16_t line_num, const uint8_t * file_name)
{
    UNUSED_PARAMETER(pc);
    assert_nrf_callback(line_num, file_name);
}
#else
/**@brief       Callback function for asserts in the SoftDevice.
 *
 * @details     A pointer to this function will be passed to the SoftDevice. This function will be
 *              called by the SoftDevice if certain unrecoverable errors occur within the
 *              application or SoftDevice.
 *
 *              See @ref nrf_fault_handler_t for more details.
 *
 * @param[in] id    Fault identifier. See @ref NRF_FAULT_IDS.
 * @param[in] pc    The program counter of the instruction that triggered the fault.
 * @param[in] info  Optional additional information regarding the fault. Refer to each fault
 *                  identifier for details.
 */
void softdevice_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    app_error_fault_handler(id, pc, info);
}
#endif


void intern_softdevice_events_execute(void)
{
    if (!m_softdevice_enabled)
    {
        // SoftDevice not enabled. This can be possible if the SoftDevice was enabled by the
        // application without using this module's API (i.e softdevice_handler_init)

        return;
    }
#if NRF_MODULE_ENABLED(CLOCK)
    bool no_more_soc_evts = false;
#else
    bool no_more_soc_evts = (m_sys_evt_handler == NULL);
#endif
#ifdef BLE_STACK_SUPPORT_REQD
    bool no_more_ble_evts = (m_ble_evt_handler == NULL);
#endif
#ifdef ANT_STACK_SUPPORT_REQD
    bool no_more_ant_evts = (m_ant_evt_handler == NULL);
#endif

    for (;;)
    {
        uint32_t err_code;

        if (!no_more_soc_evts)
        {
            if (m_suspended)
            {
                // Cancel pulling next event if event handler was suspended by user.
                return;
            }

            uint32_t evt_id;

            // Pull event from SOC.
            err_code = sd_evt_get(&evt_id);

            if (err_code == NRF_ERROR_NOT_FOUND)
            {
                no_more_soc_evts = true;
            }
            else if (err_code != NRF_SUCCESS)
            {
                APP_ERROR_HANDLER(err_code);
            }
            else
            {
#ifdef SOFTDEVICE_PRESENT
                // Call application's SOC event handler.
#if NRF_MODULE_ENABLED(POWER)
                nrf_drv_power_on_soc_event(evt_id);
#endif
#if NRF_MODULE_ENABLED(CLOCK)
                nrf_drv_clock_on_soc_event(evt_id);
#endif
#endif /* SOFTDEVICE_PRESENT */
                if (m_sys_evt_handler)
                {
                    m_sys_evt_handler(evt_id);
                }
            }
        }

#ifdef BLE_STACK_SUPPORT_REQD
        // Fetch BLE Events.
        if (!no_more_ble_evts)
        {
            if (m_suspended)
            {
                // Cancel pulling next event if event handler was suspended by user.
                return;
            }

            // Pull event from stack
            uint16_t evt_len = m_ble_evt_buffer_size;

            err_code = sd_ble_evt_get(mp_ble_evt_buffer, &evt_len);
            if (err_code == NRF_ERROR_NOT_FOUND)
            {
                no_more_ble_evts = true;
            }
            else if (err_code != NRF_SUCCESS)
            {
                APP_ERROR_HANDLER(err_code);
            }
            else
            {
                // Call application's BLE stack event handler.
                m_ble_evt_handler((ble_evt_t *)mp_ble_evt_buffer);
            }
        }
#endif

#ifdef ANT_STACK_SUPPORT_REQD
        // Fetch ANT Events.
        if (!no_more_ant_evts)
        {
            if (m_suspended)
            {
                // Cancel pulling next event if event handler was suspended by user.
                return;
            }

            // Pull event from stack
            err_code = sd_ant_event_get(&m_ant_evt_buffer.channel,
                                        &m_ant_evt_buffer.event,
                                        m_ant_evt_buffer.msg.evt_buffer);
            if (err_code == NRF_ERROR_NOT_FOUND)
            {
                no_more_ant_evts = true;
            }
            else if (err_code != NRF_SUCCESS)
            {
                APP_ERROR_HANDLER(err_code);
            }
            else
            {
                // Call application's ANT stack event handler.
                m_ant_evt_handler(&m_ant_evt_buffer);
            }
        }
#endif

        if (no_more_soc_evts)
        {
            // There are no remaining System (SOC) events to be fetched from the SoftDevice.
#if defined(ANT_STACK_SUPPORT_REQD) && defined(BLE_STACK_SUPPORT_REQD)
            // Check if there are any remaining BLE and ANT events.
            if (no_more_ble_evts && no_more_ant_evts)
            {
                break;
            }
#elif defined(BLE_STACK_SUPPORT_REQD)
            // Check if there are any remaining BLE events.
            if (no_more_ble_evts)
            {
                break;
            }
#elif defined(ANT_STACK_SUPPORT_REQD)
            // Check if there are any remaining ANT events.
            if (no_more_ant_evts)
            {
                break;
            }
#else
            // No need to check for BLE or ANT events since there is no support for BLE and ANT
            // required.
            break;
#endif
        }
    }
}


bool softdevice_handler_is_enabled(void)
{
    return m_softdevice_enabled;
}

#if defined(S1XX)
uint32_t softdevice_handler_init(nrf_clock_lfclksrc_t              clock_source,
                                 void *                            p_ble_evt_buffer,
                                 uint16_t                          ble_evt_buffer_size,
                                 softdevice_evt_schedule_func_t    evt_schedule_func)
#else
uint32_t softdevice_handler_init(nrf_clock_lf_cfg_t *           p_clock_lf_cfg,
                                 void *                         p_ble_evt_buffer,
                                 uint16_t                       ble_evt_buffer_size,
                                 softdevice_evt_schedule_func_t evt_schedule_func)
#endif
{
    uint32_t err_code;

    // Save configuration.
#if defined (BLE_STACK_SUPPORT_REQD)
    // Check that buffer is not NULL.
    if (p_ble_evt_buffer == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    // Check that buffer is correctly aligned.
    if (!is_word_aligned(p_ble_evt_buffer))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    mp_ble_evt_buffer     = (uint8_t *)p_ble_evt_buffer;
    m_ble_evt_buffer_size = ble_evt_buffer_size;
#else
    // The variables p_ble_evt_buffer and ble_evt_buffer_size is not needed if BLE Stack support
    // is not required.
    UNUSED_PARAMETER(p_ble_evt_buffer);
    UNUSED_PARAMETER(ble_evt_buffer_size);
#endif

    m_evt_schedule_func = evt_schedule_func;

    // Initialize SoftDevice.
#if ((NRF_MODULE_ENABLED(CLOCK) || NRF_MODULE_ENABLED(POWER)) && defined(SOFTDEVICE_PRESENT))
    bool power_clock_isr_enabled = nrf_drv_common_irq_enable_check(POWER_CLOCK_IRQn);
    if (power_clock_isr_enabled)
    {
        NVIC_DisableIRQ(POWER_CLOCK_IRQn);
    }
#endif

#if (NRF_MODULE_ENABLED(RNG) && defined(SOFTDEVICE_PRESENT))
    bool rng_isr_enabled = nrf_drv_common_irq_enable_check(RNG_IRQn);
    if (rng_isr_enabled)
    {
        NVIC_DisableIRQ(RNG_IRQn);
    }
#endif
#if defined(S212) || defined(S332)
    err_code = sd_softdevice_enable(p_clock_lf_cfg, softdevice_fault_handler, ANT_LICENSE_KEY);
#elif defined(S1XX)
    err_code = sd_softdevice_enable(clock_source, softdevice_assertion_handler);
#else
    err_code = sd_softdevice_enable(p_clock_lf_cfg, softdevice_fault_handler);
#endif

    if (err_code != NRF_SUCCESS)
    {
#if (NRF_MODULE_ENABLED(RNG) && defined(SOFTDEVICE_PRESENT))
        if (rng_isr_enabled)
        {
            NVIC_EnableIRQ(RNG_IRQn);
        }
#endif
#if ((NRF_MODULE_ENABLED(CLOCK) || NRF_MODULE_ENABLED(POWER)) && defined(SOFTDEVICE_PRESENT))
        if (power_clock_isr_enabled)
        {
            NVIC_EnableIRQ(POWER_CLOCK_IRQn);
        }
#endif
        return err_code;
    }

    m_softdevice_enabled = true;
#ifdef SOFTDEVICE_PRESENT
#if NRF_MODULE_ENABLED(POWER)
    nrf_drv_power_on_sd_enable();
#endif
#if NRF_MODULE_ENABLED(CLOCK)
    nrf_drv_clock_on_sd_enable();
#endif
#endif /* SOFTDEVICE_PRESENT */

    // Enable BLE event interrupt (interrupt priority has already been set by the stack).
#ifdef SOFTDEVICE_PRESENT
    err_code = sd_nvic_EnableIRQ((IRQn_Type)SOFTDEVICE_EVT_IRQ);
    return err_code;

#else
    //In case of Serialization NVIC must be accessed directly.
    NVIC_EnableIRQ(SOFTDEVICE_EVT_IRQ);
    return NRF_SUCCESS;
#endif
}


uint32_t softdevice_handler_sd_disable(void)
{
    uint32_t err_code = sd_softdevice_disable();
    if (err_code == NRF_SUCCESS)
    {
        m_softdevice_enabled = false;
#ifdef SOFTDEVICE_PRESENT
#if NRF_MODULE_ENABLED(POWER)
        nrf_drv_power_on_sd_disable();
#endif
#if NRF_MODULE_ENABLED(CLOCK)
        nrf_drv_clock_on_sd_disable();
#endif
#if NRF_MODULE_ENABLED(RNG)
        nrf_drv_rng_on_sd_disable();
#endif
#endif /* SOFTDEVICE_PRESENT */
    }
    return err_code;
}


#ifdef BLE_STACK_SUPPORT_REQD
uint32_t softdevice_ble_evt_handler_set(ble_evt_handler_t ble_evt_handler)
{
    VERIFY_PARAM_NOT_NULL(ble_evt_handler);

    m_ble_evt_handler = ble_evt_handler;

    return NRF_SUCCESS;
}
#endif


#ifdef ANT_STACK_SUPPORT_REQD
uint32_t softdevice_ant_evt_handler_set(ant_evt_handler_t ant_evt_handler)
{
    VERIFY_PARAM_NOT_NULL(ant_evt_handler);

    m_ant_evt_handler = ant_evt_handler;

    return NRF_SUCCESS;
}
#endif


uint32_t softdevice_sys_evt_handler_set(sys_evt_handler_t sys_evt_handler)
{
    VERIFY_PARAM_NOT_NULL(sys_evt_handler);

    m_sys_evt_handler = sys_evt_handler;

    return NRF_SUCCESS;
}


/**@brief   Function for handling the Application's BLE Stack events interrupt.
 *
 * @details This function is called whenever an event is ready to be pulled.
 */
void SOFTDEVICE_EVT_IRQHandler(void)
{
    if (m_evt_schedule_func != NULL)
    {
        uint32_t err_code = m_evt_schedule_func();
        APP_ERROR_CHECK(err_code);
    }
    else
    {
        intern_softdevice_events_execute();
    }
}


void softdevice_handler_suspend()
{
#ifdef SOFTDEVICE_PRESENT
    ret_code_t err_code = sd_nvic_DisableIRQ((IRQn_Type)SOFTDEVICE_EVT_IRQ);
    APP_ERROR_CHECK(err_code);
#else
    NVIC_DisableIRQ(SOFTDEVICE_EVT_IRQ);
#endif
    m_suspended = true;
    return;
}


void softdevice_handler_resume()
{
    if (!m_suspended)
    {
        return;
    }
    m_suspended = false;

#ifdef SOFTDEVICE_PRESENT
    ret_code_t err_code;

    // Force calling ISR again to make sure that events not pulled previously
    // has been processed.
    err_code = sd_nvic_SetPendingIRQ((IRQn_Type)SOFTDEVICE_EVT_IRQ);
    APP_ERROR_CHECK(err_code);
    err_code = sd_nvic_EnableIRQ((IRQn_Type)SOFTDEVICE_EVT_IRQ);
    APP_ERROR_CHECK(err_code);
#else
    NVIC_SetPendingIRQ((IRQn_Type)SOFTDEVICE_EVT_IRQ);
    NVIC_EnableIRQ(SOFTDEVICE_EVT_IRQ);
#endif

    return;
}


bool softdevice_handler_is_suspended()
{
    return m_suspended;
}

#if defined(BLE_STACK_SUPPORT_REQD) && !defined(S1XX)

static inline uint32_t ram_total_size_get(void)
{
#ifdef NRF51
    uint32_t size_ram_blocks = (uint32_t)NRF_FICR->SIZERAMBLOCKS;
    uint32_t total_ram_size = size_ram_blocks;
    total_ram_size = total_ram_size * (NRF_FICR->NUMRAMBLOCK);
    return total_ram_size;
#elif (defined (NRF52) || defined(NRF52840_XXAA))
    return RAM_TOTAL_SIZE;
#endif /* NRF51 */
}


/*lint --e{528} -save suppress 528: symbol not referenced */
/**@brief   Function for finding the end address of the RAM.
 *
 * @retval  ram_end_address  Address of the end of the RAM.
 */
static inline uint32_t ram_end_address_get(void)
{
    uint32_t ram_end_address = (uint32_t)RAM_START_ADDRESS;
    ram_end_address         += ram_total_size_get();
    return ram_end_address;
}
/*lint -restore*/


/*lint --e{10} --e{27} --e{40} --e{529} -save */
ret_code_t softdevice_app_ram_start_get(uint32_t * app_ram_base)
{
    ret_code_t ret = NRF_SUCCESS;
#if   defined ( __CC_ARM )
    extern uint32_t Image$$RW_IRAM1$$Base;
    const volatile uint32_t ram_start = (uint32_t) &Image$$RW_IRAM1$$Base;
#elif defined ( __ICCARM__ )
    extern uint32_t __ICFEDIT_region_RAM_start__;
    volatile uint32_t ram_start = (uint32_t) &__ICFEDIT_region_RAM_start__;
#elif defined ( __GNUC__ )
    extern uint32_t __data_start__;
    volatile uint32_t ram_start = (uint32_t) &__data_start__;
#else
  ret = NRF_ERROR_NOT_FOUND;
  return ret;
#endif
    *app_ram_base = ram_start;
    return ret;
}
/*lint -restore*/


/*lint --e{10} --e{27} --e{40} --e{529} -save */
uint32_t softdevice_enable(uint32_t * ram_start)
{
#if (defined(S130) || defined(S132) || defined(S332) || defined(S140))
    uint32_t err_code;
    uint32_t app_ram_base = *ram_start;

    NRF_LOG_DEBUG("RAM start at 0x%x.\r\n", app_ram_base);
    err_code = sd_ble_enable(&app_ram_base);

    if (app_ram_base != *ram_start)
    {
        NRF_LOG_WARNING("RAM start should be adjusted to 0x%x.\r\n", app_ram_base);
        NRF_LOG_WARNING("RAM size should be adjusted to 0x%x.\r\n",
                        ram_end_address_get() - app_ram_base);
    }
    else if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("sd_ble_enable() returned unexpected value: 0x%x.\r\n", err_code);
    }
    return err_code;
#else
    return NRF_SUCCESS;
#endif   //defined(S130) || defined(S132) || defined(S332) || defined(S140)
}
/*lint -restore*/

#endif //BLE_STACK_SUPPORT_REQD
