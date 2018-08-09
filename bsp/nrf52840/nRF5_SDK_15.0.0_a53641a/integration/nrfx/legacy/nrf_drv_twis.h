/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_TWIS_H__
#define NRF_DRV_TWIS_H__

#include <nrfx_twis.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_twis TWIS driver - legacy layer
 * @{
 * @ingroup  nrf_twis
 *
 * @brief    Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_twis_t         nrf_drv_twis_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_twis_config_t  nrf_drv_twis_config_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_twis_evt_t     nrf_drv_twis_evt_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_TWIS_INSTANCE               NRFX_TWIS_INSTANCE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_TWIS_DEFAULT_CONFIG         NRFX_TWIS_DEFAULT_CONFIG

/** @brief Macro for forwarding the new implementation. */
#define TWIS_EVT_READ_REQ                   NRFX_TWIS_EVT_READ_REQ
/** @brief Macro for forwarding the new implementation. */
#define TWIS_EVT_READ_DONE                  NRFX_TWIS_EVT_READ_DONE
/** @brief Macro for forwarding the new implementation. */
#define TWIS_EVT_READ_ERROR                 NRFX_TWIS_EVT_READ_ERROR
/** @brief Macro for forwarding the new implementation. */
#define TWIS_EVT_WRITE_REQ                  NRFX_TWIS_EVT_WRITE_REQ
/** @brief Macro for forwarding the new implementation. */
#define TWIS_EVT_WRITE_DONE                 NRFX_TWIS_EVT_WRITE_DONE
/** @brief Macro for forwarding the new implementation. */
#define TWIS_EVT_WRITE_ERROR                NRFX_TWIS_EVT_WRITE_ERROR
/** @brief Macro for forwarding the new implementation. */
#define TWIS_EVT_GENERAL_ERROR              NRFX_TWIS_EVT_GENERAL_ERROR
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_evt_type_t             nrfx_twis_evt_type_t
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_TWIS_ERROR_OVERFLOW         NRFX_TWIS_ERROR_OVERFLOW
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_TWIS_ERROR_DATA_NACK        NRFX_TWIS_ERROR_DATA_NACK
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_TWIS_ERROR_OVERREAD         NRFX_TWIS_ERROR_OVERREAD
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_TWIS_ERROR_UNEXPECTED_EVENT NRFX_TWIS_ERROR_UNEXPECTED_EVENT
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_error_t                nrfx_twis_error_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_event_handler_t        nrfx_twis_event_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_init                   nrfx_twis_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_uninit                 nrfx_twis_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_enable                 nrfx_twis_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_disable                nrfx_twis_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_error_get_and_clear    nrfx_twis_error_get_and_clear
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_tx_prepare             nrfx_twis_tx_prepare
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_tx_amount              nrfx_twis_tx_amount
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_rx_prepare             nrfx_twis_rx_prepare
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_rx_amount              nrfx_twis_rx_amount
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_is_busy                nrfx_twis_is_busy
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_is_waiting_tx_buff     nrfx_twis_is_waiting_tx_buff
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_is_waiting_rx_buff     nrfx_twis_is_waiting_rx_buff
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_is_pending_tx          nrfx_twis_is_pending_tx
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_twis_is_pending_rx          nrfx_twis_is_pending_rx

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_TWIS_H__
