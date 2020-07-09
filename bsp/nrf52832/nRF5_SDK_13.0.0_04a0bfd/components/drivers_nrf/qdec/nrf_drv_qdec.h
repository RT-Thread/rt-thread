/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#ifndef NRF_DRV_QDEC_H__
#define NRF_DRV_QDEC_H__

#include "nrf_qdec.h"
#include "sdk_config.h"
#include "sdk_errors.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup nrf_qdec QDEC HAL and driver
 * @ingroup nrf_drivers
 * @brief Quadrature decoder (QDEC) APIs.
 * @details The QDEC HAL provides basic APIs for accessing the registers of the QDEC.
 * The QDEC driver provides APIs on a higher level.
 *
 * @defgroup nrf_drv_qdec QDEC driver
 * @{
 * @ingroup nrf_qdec
 * @brief Quadrature decoder (QDEC) driver.
 */

/**@brief QDEC configuration structure.*/
typedef struct
{
    nrf_qdec_reportper_t   reportper;          /**< Report period in samples. */
    nrf_qdec_sampleper_t   sampleper;          /**< Sampling period in microseconds. */
    uint32_t               psela;              /**< Pin number for A input. */
    uint32_t               pselb;              /**< Pin number for B input. */
    uint32_t               pselled;            /**< Pin number for LED output. */
    uint32_t               ledpre;             /**< Time (in microseconds) how long LED is switched on before sampling. */
    nrf_qdec_ledpol_t      ledpol;             /**< Active LED polarity. */
    bool                   dbfen;              /**< State of debouncing filter. */
    bool                   sample_inten;       /**< Enabling sample ready interrupt. */
    uint8_t                interrupt_priority; /**< QDEC interrupt priority. */
} nrf_drv_qdec_config_t;

/**@brief QDEC default configuration. */
#define NRF_DRV_QDEC_DEFAULT_CONFIG                                         \
    {                                                                       \
        .reportper          = (nrf_qdec_reportper_t)QDEC_CONFIG_REPORTPER,  \
        .sampleper          = (nrf_qdec_sampleper_t)QDEC_CONFIG_SAMPLEPER,  \
        .psela              = QDEC_CONFIG_PIO_A,                            \
        .pselb              = QDEC_CONFIG_PIO_B,                            \
        .pselled            = QDEC_CONFIG_PIO_LED,                          \
        .ledpre             = QDEC_CONFIG_LEDPRE,                           \
        .ledpol             = (nrf_qdec_ledpol_t)QDEC_CONFIG_LEDPOL,        \
        .interrupt_priority = QDEC_CONFIG_IRQ_PRIORITY,                     \
        .dbfen              = QDEC_CONFIG_DBFEN,                            \
        .sample_inten       = QDEC_CONFIG_SAMPLE_INTEN                      \
    }

/**@brief QDEC sample event data.*/
typedef struct
{
    int8_t value; /**< Sample value. */
} nrf_drv_qdec_sample_data_evt_t;

/**@brief QDEC report event data.*/
typedef struct
{
    int16_t acc;     /**< Accumulated transitions. */
    uint16_t accdbl;  /**< Accumulated double transitions. */
} nrf_drv_qdec_report_data_evt_t;

/**@brief QDEC event handler structure. */
typedef struct
{
    nrf_qdec_event_t  type;
    union
    {
        nrf_drv_qdec_sample_data_evt_t sample; /**< Sample event data. */
        nrf_drv_qdec_report_data_evt_t report; /**< Report event data. */
    } data;
} nrf_drv_qdec_event_t;

/**@brief QDEC event handler.
 * @param[in] event  QDEC event structure.
 */
typedef void (*qdec_event_handler_t)(nrf_drv_qdec_event_t event);

/**@brief Function for initializing QDEC.
 *
 * @param[in] p_config            Pointer to configuration parameters.
 * @param[in] event_handler  Event handler function.
 *
 * @retval NRF_SUCCESS If initialization was successful.
 * @retval NRF_ERROR_INVALID_PARAM If invalid parameters were supplied.
 * @retval NRF_ERROR_INVALID_STATE If QDEC was already initialized.
 */
ret_code_t nrf_drv_qdec_init(nrf_drv_qdec_config_t const * p_config,
                             qdec_event_handler_t event_handler);

/**@brief Function for uninitializing QDEC.
 * @note  Function asserts if module is uninitialized.
 */
void nrf_drv_qdec_uninit(void);

/**@brief Function for enabling QDEC.
 * @note  Function asserts if module is uninitialized or enabled.
 */
void nrf_drv_qdec_enable(void);

/**@brief Function for disabling QDEC.
 * @note  Function asserts if module is uninitialized or disabled.
 */
void nrf_drv_qdec_disable(void);

/**@brief Function for reading accumulated transitions QDEC.
 * @note  Function asserts if module is not enabled.
 * @note  Accumulators are cleared after reading.
 *
 * @param[out] p_acc      Pointer to store accumulated transitions.
 * @param[out] p_accdbl   Pointer to store accumulated double transitions.
 */
void nrf_drv_qdec_accumulators_read(int16_t * p_acc, int16_t * p_accdbl);

/**
 * @brief Function for returning the address of a specific timer task.
 *
 * @param[in]  task       QDEC task.
 * @param[out] p_task     Task address.
 */
void nrf_drv_qdec_task_address_get(nrf_qdec_task_t task, uint32_t * p_task);

/**
 * @brief Function for returning the address of a specific timer event.
 *
 * @param[in]  event       QDEC event.
 * @param[out] p_event     Event address.
 */
void nrf_drv_qdec_event_address_get(nrf_qdec_event_t event, uint32_t * p_event);

/**
   *@}
 **/

#ifdef __cplusplus
}
#endif

#endif /* NRF_DRV_QDEC_H__ */
