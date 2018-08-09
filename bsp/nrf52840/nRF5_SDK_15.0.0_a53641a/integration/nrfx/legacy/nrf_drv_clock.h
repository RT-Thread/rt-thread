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
#ifndef NRF_DRV_CLOCK_H__
#define NRF_DRV_CLOCK_H__

#include <nrfx_clock.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_clock Clock driver - legacy layer
 * @{
 * @ingroup nrf_clock
 *
 * @brief Layer providing compatibility with the former API.
 */

/**
 * @brief Clock events.
 */
typedef enum
{
    NRF_DRV_CLOCK_EVT_HFCLK_STARTED, ///< HFCLK has been started.
    NRF_DRV_CLOCK_EVT_LFCLK_STARTED, ///< LFCLK has been started.
    NRF_DRV_CLOCK_EVT_CAL_DONE,      ///< Calibration is done.
    NRF_DRV_CLOCK_EVT_CAL_ABORTED,   ///< Calibration has been aborted.
} nrf_drv_clock_evt_type_t;

/**
 * @brief Clock event handler.
 *
 * @param[in] event  Event.
 */
typedef void (*nrf_drv_clock_event_handler_t)(nrf_drv_clock_evt_type_t event);

// Forward declaration of the nrf_drv_clock_handler_item_t type.
typedef struct nrf_drv_clock_handler_item_s nrf_drv_clock_handler_item_t;

struct nrf_drv_clock_handler_item_s
{
    nrf_drv_clock_handler_item_t * p_next;        ///< A pointer to the next handler that should be called when the clock is started.
    nrf_drv_clock_event_handler_t  event_handler; ///< Function to be called when the clock is started.
};

/**
 * @brief Function for checking if driver is already initialized
 *
 * @retval true  Driver is initialized
 * @retval false Driver is uninitialized
 */
bool nrf_drv_clock_init_check(void);

/**
 * @brief Function for initializing the nrf_drv_clock module.
 *
 * After initialization, the module is in power off state (clocks are not requested).
 *
 * @retval NRF_SUCCESS                          If the procedure was successful.
 * @retval NRF_ERROR_MODULE_ALREADY_INITIALIZED If the driver was already initialized.
 */
ret_code_t nrf_drv_clock_init(void);

/**
 * @brief Function for uninitializing the clock module.
 *
 */
void nrf_drv_clock_uninit(void);

/**
 * @brief Function for requesting the LFCLK.
 *
 * The low-frequency clock can be requested by different modules
 * or contexts. The driver ensures that the clock will be started only when it is requested
 * the first time. If the clock is not ready but it was already started, the handler item that is
 * provided as an input parameter is added to the list of handlers that will be notified
 * when the clock is started. If the clock is already enabled, user callback is called from the
 * current context.
 *
 * The first request will start the selected LFCLK source. If an event handler is
 * provided, it will be called once the LFCLK is started. If the LFCLK was already started at this
 * time, the event handler will be called from the context of this function. Additionally,
 * the @ref nrf_drv_clock_lfclk_is_running function can be polled to check if the clock has started.
 *
 * @note When a SoftDevice is enabled, the LFCLK is always running and the driver cannot control it.
 *
 * @note The handler item provided by the user cannot be an automatic variable.
 *
 * @param[in] p_handler_item A pointer to the event handler structure.
 */
void nrf_drv_clock_lfclk_request(nrf_drv_clock_handler_item_t * p_handler_item);

/**
 * @brief Function for releasing the LFCLK.
 *
 * If there are no more requests, the LFCLK source will be stopped.
 *
 * @note When a SoftDevice is enabled, the LFCLK is always running.
 */
void nrf_drv_clock_lfclk_release(void);

/**
 * @brief Function for checking the LFCLK state.
 *
 * @retval true  If the LFCLK is running.
 * @retval false If the LFCLK is not running.
 */
bool nrf_drv_clock_lfclk_is_running(void);

/**
 * @brief Function for requesting the high-accuracy source HFCLK.
 *
 * The high-accuracy source
 * can be requested by different modules or contexts. The driver ensures that the high-accuracy
 * clock will be started only when it is requested the first time. If the clock is not ready
 * but it was already started, the handler item that is provided as an input parameter is added
 * to the list of handlers that will be notified when the clock is started.
 *
 * If an event handler is provided, it will be called once the clock is started. If the clock was already
 * started at this time, the event handler will be called from the context of this function. Additionally,
 * the @ref nrf_drv_clock_hfclk_is_running function can be polled to check if the clock has started.
 *
 * @note If a SoftDevice is running, the clock is managed by the SoftDevice and all requests are handled by
 *       the SoftDevice. This function cannot be called from all interrupt priority levels in that case.
 * @note The handler item provided by the user cannot be an automatic variable.
 *
 * @param[in] p_handler_item A pointer to the event handler structure.
 */
void nrf_drv_clock_hfclk_request(nrf_drv_clock_handler_item_t * p_handler_item);

/**
 * @brief Function for releasing the high-accuracy source HFCLK.
 *
 * If there are no more requests, the high-accuracy source will be released.
 */
void nrf_drv_clock_hfclk_release(void);

/**
 * @brief Function for checking the HFCLK state.
 *
 * @retval true If the HFCLK is running (for \nRFXX XTAL source).
 * @retval false If the HFCLK is not running.
 */
bool nrf_drv_clock_hfclk_is_running(void);

/**
 * @brief Function for starting a single calibration process.
 *
 * This function can also delay the start of calibration by a user-specified value. The delay will use
 * a low-power timer that is part of the CLOCK module. @ref nrf_drv_clock_is_calibrating can be called to
 * check if calibration is still in progress. If a handler is provided, the user can be notified when
 * calibration is completed. The ext calibration can be started from the handler context.
 *
 * The calibration process consists of three phases:
 * - Delay (optional)
 * - Requesting the high-accuracy HFCLK
 * - Hardware-supported calibration
 *
 * @param[in] delay   Time after which the calibration will be started (in 0.25 s units).
 * @param[in] handler NULL or user function to be called when calibration is completed or aborted.
 *
 * @retval NRF_SUCCESS             If the procedure was successful.
 * @retval NRF_ERROR_FORBIDDEN     If a SoftDevice is present or the selected LFCLK source is not an RC oscillator.
 * @retval NRF_ERROR_INVALID_STATE If the low-frequency clock is off.
 * @retval NRF_ERROR_BUSY          If calibration is in progress.
 */
ret_code_t nrf_drv_clock_calibration_start(uint8_t delay, nrf_drv_clock_event_handler_t handler);

/**
 * @brief Function for aborting calibration.
 *
 * This function aborts on-going calibration. If calibration was started, it cannot be stopped. If a handler
 * was provided by @ref nrf_drv_clock_calibration_start, this handler will be called once
 * aborted calibration is completed. @ref nrf_drv_clock_is_calibrating can also be used to check
 * if the system is calibrating.
 *
 * @retval NRF_SUCCESS         If the procedure was successful.
 * @retval NRF_ERROR_FORBIDDEN If a SoftDevice is present or the selected LFCLK source is not an RC oscillator.
 */
ret_code_t nrf_drv_clock_calibration_abort(void);

/**
 * @brief Function for checking if calibration is in progress.
 *
 * This function indicates that the system is
 * in calibration if it is in any of the calibration process phases (see @ref nrf_drv_clock_calibration_start).
 *
 * @param[out] p_is_calibrating True if calibration is in progress, false if not.
 *
 * @retval NRF_SUCCESS         If the procedure was successful.
 * @retval NRF_ERROR_FORBIDDEN If a SoftDevice is present or the selected LFCLK source is not an RC oscillator.
 */
ret_code_t nrf_drv_clock_is_calibrating(bool * p_is_calibrating);

/**@brief Function for returning a requested task address for the clock driver module.
 *
 * @param[in] task One of the peripheral tasks.
 *
 * @return Task address.
 */
__STATIC_INLINE uint32_t nrf_drv_clock_ppi_task_addr(nrf_clock_task_t task);

/**@brief Function for returning a requested event address for the clock driver module.
 *
 * @param[in] event One of the peripheral events.
 *
 * @return Event address.
 */
__STATIC_INLINE uint32_t nrf_drv_clock_ppi_event_addr(nrf_clock_event_t event);


#ifdef SOFTDEVICE_PRESENT
/**
 * @brief Function called by the SoftDevice handler if an @ref NRF_SOC_EVTS event is received from the SoftDevice.
 *
 * @param[in] evt_id One of NRF_SOC_EVTS values.
 */
void nrf_drv_clock_on_soc_event(uint32_t evt_id);

/**
 * @brief Function called by the SoftDevice handler when the SoftDevice has been enabled.
 *
 * This function is called just after the SoftDevice has been properly enabled.
 * Its main purpose is to mark that LFCLK has been requested by SD.
 */
void nrf_drv_clock_on_sd_enable(void);

/**
 * @brief Function called by the SoftDevice handler when the SoftDevice has been disabled.
 *
 * This function is called just after the SoftDevice has been properly disabled.
 * It has two purposes:
 * 1. Releases the LFCLK from the SD.
 * 2. Reinitializes an interrupt after the SD releases POWER_CLOCK_IRQ.
 */
void nrf_drv_clock_on_sd_disable(void);

#endif
/**
 *@}
 **/

#ifndef SUPPRESS_INLINE_IMPLEMENTATION
__STATIC_INLINE uint32_t nrf_drv_clock_ppi_task_addr(nrf_clock_task_t task)
{
    return nrf_clock_task_address_get(task);
}

__STATIC_INLINE uint32_t nrf_drv_clock_ppi_event_addr(nrf_clock_event_t event)
{
    return nrf_clock_event_address_get(event);
}
#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_CLOCK_H__
