/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_POWER_H__
#define NRF_DRV_POWER_H__

#include <nrfx_power.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_power POWER driver - legacy layer
 * @{
 * @ingroup  nrf_power
 *
 * @brief    Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_power_config_t             nrf_drv_power_config_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_power_pofwarn_config_t     nrf_drv_power_pofwarn_config_t;
#if NRF_POWER_HAS_SLEEPEVT || defined(__SDK_DOXYGEN__)
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_power_sleepevt_config_t    nrf_drv_power_sleepevt_config_t;
#endif
#if NRF_POWER_HAS_USBREG || defined(__SDK_DOXYGEN__)
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_power_usbevt_config_t      nrf_drv_power_usbevt_config_t;
#endif

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_MODE_CONSTLAT            NRFX_POWER_MODE_CONSTLAT
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_MODE_LOWPWR              NRFX_POWER_MODE_LOWPWR
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_power_mode_t                   nrfx_power_mode_t
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_SLEEP_EVT_ENTER          NRFX_POWER_SLEEP_EVT_ENTER
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_SLEEP_EVT_EXIT           NRFX_POWER_SLEEP_EVT_EXIT
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_power_sleep_evt_t              nrfx_power_sleep_evt_t
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_USB_EVT_DETECTED         NRFX_POWER_USB_EVT_DETECTED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_USB_EVT_REMOVED          NRFX_POWER_USB_EVT_REMOVED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_USB_EVT_READY            NRFX_POWER_USB_EVT_READY
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_power_usb_evt_t                nrfx_power_usb_evt_t
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_USB_STATE_DISCONNECTED   NRFX_POWER_USB_STATE_DISCONNECTED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_USB_STATE_CONNECTED      NRFX_POWER_USB_STATE_CONNECTED
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_POWER_USB_STATE_READY          NRFX_POWER_USB_STATE_READY
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_power_usb_state_t              nrfx_power_usb_state_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_power_pofwarn_event_handler_t  nrfx_power_pofwarn_event_handler_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_power_sleep_event_handler_t    nrfx_power_sleep_event_handler_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_power_usb_event_handler_t      nrfx_power_usb_event_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_power_usbstatus_get            nrfx_power_usbstatus_get

/**
 * @brief Function for checking if driver is already initialized
 *
 * This function is used to check whether common POWER_CLOCK interrupt
 * should be disabled or not if @ref nrf_drv_clock tries to disable the interrupt.
 *
 * @retval true  Driver is initialized
 * @retval false Driver is uninitialized
 *
 * @sa nrf_drv_power_uninit
 */
bool nrf_drv_power_init_check(void);

/**
 * @brief Initialize power module driver
 *
 * Enabled power module driver would process all the interrupts from power system.
 *
 * @param[in] p_config Driver configuration. Can be NULL - the default configuration
 *                     from @em sdk_config.h file would be used then.
 *
 * @retval NRF_ERROR_INVALID_STATE              Power driver has to be enabled
 *                                              before SoftDevice.
 * @retval NRF_ERROR_MODULE_ALREADY_INITIALIZED Module is initialized already.
 * @retval NRF_SUCCESS                          Successfully initialized.
 */
ret_code_t nrf_drv_power_init(nrf_drv_power_config_t const * p_config);

/**
 * @brief Unintialize power module driver
 *
 * Disables all the interrupt handling in the module.
 *
 * @sa nrf_drv_power_init
 */
void nrf_drv_power_uninit(void);

/**
 * @brief Initialize power failure comparator
 *
 * Configures and setups the power failure comparator and enables it.
 *
 * @param[in] p_config Configuration with values and event handler.
 *                     If event handler is set to NULL, interrupt would be disabled.
 *
 * @retval NRF_ERROR_INVALID_STATE POF is initialized when SD is enabled and
 *                                 the configuration differs from the old one and
 *                                 is not possible to be set using SD interface.
 * @retval NRF_SUCCESS             Successfully initialized and configured.
 */
ret_code_t nrf_drv_power_pof_init(nrf_drv_power_pofwarn_config_t const * p_config);

/**
 * @brief Turn off the power failure comparator
 *
 * Disables and clears the settings of the power failure comparator.
 */
void nrf_drv_power_pof_uninit(void);

#if NRF_POWER_HAS_SLEEPEVT || defined(__SDK_DOXYGEN__)

/**
 * @brief Initialize sleep entering and exiting events processing
 *
 * Configures and setups the sleep event processing.
 *
 * @param[in] p_config Configuration with values and event handler.
 *
 * @sa nrf_drv_power_sleepevt_uninit
 *
 * @note Sleep events are not available when SoftDevice is enabled.
 * @note If sleep event is enabled when SoftDevice is initialized, sleep events
 *       would be automatically disabled - it is the limitation of the
 *       SoftDevice itself.
 *
 * @retval NRF_ERROR_INVALID_STATE This event cannot be initialized
 *                                 when SD is enabled.
 * @retval NRF_SUCCESS             Successfully initialized and configured.
 */
ret_code_t nrf_drv_power_sleepevt_init(nrf_drv_power_sleepevt_config_t const * p_config);

/**
 * @brief Uninitialize sleep entering and exiting events processing
 *
 * @sa nrf_drv_power_sleepevt_init
 */
void nrf_drv_power_sleepevt_uninit(void);

#endif // NRF_POWER_HAS_SLEEPEVT || defined(__SDK_DOXYGEN__)

#if NRF_POWER_HAS_USBREG || defined(__SDK_DOXYGEN__)

/**
 * @brief Initialize USB power event processing
 *
 * Configures and setups the USB power event processing.
 *
 * @param[in] p_config Configuration with values and event handler.
 *
 * @sa nrf_drv_power_usbevt_uninit
 *
 * @retval NRF_ERROR_INVALID_STATE This event cannot be initialized
 *                                 when SD is enabled and SD does not support
 *                                 USB power events.
 * @retval NRF_SUCCESS             Successfully initialized and configured.
 */
ret_code_t nrf_drv_power_usbevt_init(nrf_drv_power_usbevt_config_t const * p_config);

/**
 * @brief Uninitalize USB power event processing
 *
 * @sa nrf_drv_power_usbevt_init
 */
void nrf_drv_power_usbevt_uninit(void);

#endif // NRF_POWER_HAS_USBREG || defined(__SDK_DOXYGEN__)

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_POWER_H__
