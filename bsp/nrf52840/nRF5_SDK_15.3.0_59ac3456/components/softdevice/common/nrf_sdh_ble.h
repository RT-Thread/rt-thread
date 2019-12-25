/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

/**@file
 *
 * @defgroup nrf_sdh_ble BLE support in SoftDevice Handler
 * @{
 * @ingroup  nrf_sdh
 * @brief    This file contains the declarations of types and functions required for BLE stack
 * support.
 */

#ifndef NRF_SDH_BLE_H__
#define NRF_SDH_BLE_H__

#include "app_util.h"
#include "ble.h"
#include "nrf_section_iter.h"
#include "sdk_config.h"
#include "sdk_errors.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief  Size of the buffer for a BLE event. */
#define NRF_SDH_BLE_EVT_BUF_SIZE BLE_EVT_LEN_MAX(NRF_SDH_BLE_GATT_MAX_MTU_SIZE)


#if !(defined(__LINT__))
/**@brief   Macro for registering @ref nrf_sdh_soc_evt_observer_t. Modules that want to be
 *          notified about SoC events must register the handler using this macro.
 *
 * @details This macro places the observer in a section named "sdh_soc_observers".
 *
 * @param[in]   _name       Observer name.
 * @param[in]   _prio       Priority of the observer event handler.
 *                          The smaller the number, the higher the priority.
 * @param[in]   _handler    BLE event handler.
 * @param[in]   _context    Parameter to the event handler.
 * @hideinitializer
 */
#define NRF_SDH_BLE_OBSERVER(_name, _prio, _handler, _context)                                      \
STATIC_ASSERT(NRF_SDH_BLE_ENABLED, "NRF_SDH_BLE_ENABLED not set!");                                 \
STATIC_ASSERT(_prio < NRF_SDH_BLE_OBSERVER_PRIO_LEVELS, "Priority level unavailable.");             \
NRF_SECTION_SET_ITEM_REGISTER(sdh_ble_observers, _prio, static nrf_sdh_ble_evt_observer_t _name) =  \
{                                                                                                   \
    .handler   = _handler,                                                                          \
    .p_context = _context                                                                           \
}

/**@brief   Macro for registering an array of @ref nrf_sdh_ble_evt_observer_t.
 *          Modules that want to be notified about SoC events must register the handler using
 *          this macro.
 *
 * Each observer's handler will be dispatched an event with its relative context from @p _context.
 * This macro places the observer in a section named "sdh_ble_observers".
 *
 * @param[in]   _name       Observer name.
 * @param[in]   _prio       Priority of the observer event handler.
 *                          The smaller the number, the higher the priority.
 * @param[in]   _handler    BLE event handler.
 * @param[in]   _context    An array of parameters to the event handler.
 * @param[in]   _cnt        Number of observers to register.
 * @hideinitializer
 */
#define NRF_SDH_BLE_OBSERVERS(_name, _prio, _handler, _context, _cnt)                                    \
STATIC_ASSERT(NRF_SDH_BLE_ENABLED, "NRF_SDH_BLE_ENABLED not set!");                                      \
STATIC_ASSERT(_prio < NRF_SDH_BLE_OBSERVER_PRIO_LEVELS, "Priority level unavailable.");                  \
NRF_SECTION_SET_ITEM_REGISTER(sdh_ble_observers, _prio, static nrf_sdh_ble_evt_observer_t _name[_cnt]) = \
{                                                                                                        \
    MACRO_REPEAT_FOR(_cnt, HANDLER_SET, _handler, _context)                                              \
}

#if !(defined(DOXYGEN))
#define HANDLER_SET(_idx, _handler, _context)                                                       \
{                                                                                                   \
    .handler   = _handler,                                                                          \
    .p_context = _context[_idx],                                                                    \
},
#endif

#else // __LINT__

/* Swallow semicolons */
/*lint -save -esym(528, *) -esym(529, *) : Symbol not referenced. */
#define NRF_SDH_BLE_OBSERVER(A, B, C, D)     static int semicolon_swallow_##A
#define NRF_SDH_BLE_OBSERVERS(A, B, C, D, E) static int semicolon_swallow_##A
/*lint -restore */

#endif


/**@brief   BLE stack event handler. */
typedef void (*nrf_sdh_ble_evt_handler_t)(ble_evt_t const * p_ble_evt, void * p_context);

/**@brief   BLE event observer. */
typedef struct
{
    nrf_sdh_ble_evt_handler_t handler;      //!< BLE event handler.
    void *                    p_context;    //!< A parameter to the event handler.
} const nrf_sdh_ble_evt_observer_t;


/**@brief   Function for retrieving the address of the start of application's RAM.
 *
 * @param[out]  p_app_ram_start     Address of the start of application's RAM.
 *
 * @retval  NRF_SUCCESS     If the address was successfully retrieved.
 * @retval  NRF_ERROR_NULL  If @p p_app_ram_start was @c NULL.
 */
ret_code_t nrf_sdh_ble_app_ram_start_get(uint32_t * p_app_ram_start);


/**@brief   Set the default BLE stack configuration.
 *
 * This function configures the BLE stack with the settings specified in the
 * SoftDevice handler BLE configuration. The following configurations will be set:
 * - Number of peripheral links
 * - Number of central links
 * - ATT MTU size (for the given connection)
 * - Vendor specific UUID count
 * - GATTS Attribute table size
 * - Service changed
 *
 * @param[in]   conn_cfg_tag    The connection to configure.
 * @param[out]  p_ram_start     Application RAM start address.
 */
ret_code_t nrf_sdh_ble_default_cfg_set(uint8_t conn_cfg_tag, uint32_t * p_ram_start);


/**@brief   Function for configuring and enabling the BLE stack.
 *
 * @param[in]   p_app_ram_start     Address of the start of application's RAM.
 */
ret_code_t nrf_sdh_ble_enable(uint32_t * p_app_ram_start);


#ifdef __cplusplus
}
#endif

#endif // NRF_SDH_BLE_H__

/** @} */
