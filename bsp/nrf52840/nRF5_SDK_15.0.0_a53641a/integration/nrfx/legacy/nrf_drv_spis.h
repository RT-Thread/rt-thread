/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_SPIS_H__
#define NRF_DRV_SPIS_H__

#include <nrfx_spis.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_spis SPIS driver - legacy layer
 * @{
 * @ingroup  nrf_spis
 *
 * @brief    Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_spis_t         nrf_drv_spis_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_spis_config_t  nrf_drv_spis_config_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_spis_evt_t     nrf_drv_spis_event_t;

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SPIS_INSTANCE               NRFX_SPIS_INSTANCE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SPIS_DEFAULT_CONFIG         NRFX_SPIS_DEFAULT_CONFIG
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SPIS_DEFAULT_CSN_PULLUP     NRFX_SPIS_DEFAULT_CSN_PULLUP
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SPIS_DEFAULT_MISO_DRIVE     NRFX_SPIS_DEFAULT_MISO_DRIVE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SPIS_PIN_NOT_USED           NRFX_SPIS_PIN_NOT_USED

/** @brief Macro for providing API backward compatibility. */
#define NRF_DRV_SPIS_BIT_ORDER_LSB_FIRST    NRF_SPIS_BIT_ORDER_LSB_FIRST
/** @brief Macro for providing API backward compatibility. */
#define NRF_DRV_SPIS_BIT_ORDER_MSB_FIRST    NRF_SPIS_BIT_ORDER_MSB_FIRST
/** @brief Macro for providing API backward compatibility. */
#define nrf_drv_spis_endian_t               nrf_spis_bit_order_t
/** @brief Macro for providing API backward compatibility. */
#define NRF_DRV_SPIS_MODE_0                 NRF_SPIS_MODE_0
/** @brief Macro for providing API backward compatibility. */
#define NRF_DRV_SPIS_MODE_1                 NRF_SPIS_MODE_1
/** @brief Macro for providing API backward compatibility. */
#define NRF_DRV_SPIS_MODE_2                 NRF_SPIS_MODE_2
/** @brief Macro for providing API backward compatibility. */
#define NRF_DRV_SPIS_MODE_3                 NRF_SPIS_MODE_3
/** @brief Macro for providing API backward compatibility. */
#define nrf_drv_spis_mode_t                 nrf_spis_mode_t
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SPIS_BUFFERS_SET_DONE       NRFX_SPIS_BUFFERS_SET_DONE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SPIS_XFER_DONE              NRFX_SPIS_XFER_DONE
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_SPIS_EVT_TYPE_MAX           NRFX_SPIS_EVT_TYPE_MAX
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_spis_event_type_t           nrfx_spis_evt_type_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_spis_uninit                 nrfx_spis_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_spis_buffers_set            nrfx_spis_buffers_set

/** @brief SPI slave event callback function type.
 *
 * @param[in] event                 SPI slave driver event.
 */
typedef void (*nrf_drv_spis_event_handler_t)(nrf_drv_spis_event_t event);

/** @brief Function for initializing the SPI slave driver instance.
 *
 * @note When the nRF52 Anomaly 109 workaround for SPIS is enabled, this function
 *       initializes the GPIOTE driver as well, and uses one of GPIOTE channels
 *       to detect falling edges on CSN pin.
 *
 * @param[in] p_instance    Pointer to the driver instance structure.
 * @param[in] p_config      Pointer to the structure with the initial configuration.
 *                          If NULL, the default configuration will be used.
 * @param[in] event_handler Function to be called by the SPI slave driver upon event.
 *
 * @retval NRF_SUCCESS             If the initialization was successful.
 * @retval NRF_ERROR_INVALID_PARAM If an invalid parameter is supplied.
 * @retval NRFX_ERROR_INVALID_STATE If the instance is already initialized.
 * @retval NRF_ERROR_BUSY          If some other peripheral with the same
 *                                 instance ID is already in use. This is
 *                                 possible only if PERIPHERAL_RESOURCE_SHARING_ENABLED
 *                                 is set to a value other than zero.
 * @retval NRF_ERROR_INTERNAL      GPIOTE channel for detecting falling edges
 *                                 on CSN pin cannot be initialized. Possible
 *                                 only when using nRF52 Anomaly 109 workaround.
 */
ret_code_t nrf_drv_spis_init(nrf_drv_spis_t const * const  p_instance,
                             nrf_drv_spis_config_t const * p_config,
                             nrf_drv_spis_event_handler_t  event_handler);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_SPIS_H__
