/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_QSPI_H__
#define NRF_DRV_QSPI_H__

#include <nrfx_qspi.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup   nrf_drv_qspi QSPI driver - legacy layer
 * @{
 * @ingroup    nrf_qspi
 *
 * @brief      @tagAPI52840 Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_qspi_config_t nrf_drv_qspi_config_t;

#if QSPI_PIN_SCK == NRF_QSPI_PIN_NOT_CONNECTED
    #undef QSPI_PIN_SCK
    #define QSPI_PIN_SCK  BSP_QSPI_SCK_PIN
#endif
#if QSPI_PIN_CSN == NRF_QSPI_PIN_NOT_CONNECTED
    #undef QSPI_PIN_CSN
    #define QSPI_PIN_CSN  BSP_QSPI_CSN_PIN
#endif
#if QSPI_PIN_IO0 == NRF_QSPI_PIN_NOT_CONNECTED
    #undef QSPI_PIN_IO0
    #define QSPI_PIN_IO0  BSP_QSPI_IO0_PIN
#endif
#if QSPI_PIN_IO1 == NRF_QSPI_PIN_NOT_CONNECTED
    #undef QSPI_PIN_IO1
    #define QSPI_PIN_IO1  BSP_QSPI_IO1_PIN
#endif
#if QSPI_PIN_IO2 == NRF_QSPI_PIN_NOT_CONNECTED
    #undef QSPI_PIN_IO2
    #define QSPI_PIN_IO2  BSP_QSPI_IO2_PIN
#endif
#if QSPI_PIN_IO3 == NRF_QSPI_PIN_NOT_CONNECTED
    #undef QSPI_PIN_IO3
    #define QSPI_PIN_IO3  BSP_QSPI_IO3_PIN
#endif

/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_QSPI_DEFAULT_CONFIG     NRFX_QSPI_DEFAULT_CONFIG
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_QSPI_DEFAULT_CINSTR     NRFX_QSPI_DEFAULT_CINSTR
/** @brief Macro for forwarding the new implementation. */
#define NRF_DRV_QSPI_EVENT_DONE         NRFX_QSPI_EVENT_DONE
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_evt_t              nrfx_qspi_evt_t
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_handler_t          nrfx_qspi_handler_t

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_init               nrfx_qspi_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_uninit             nrfx_qspi_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_read               nrfx_qspi_read
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_write              nrfx_qspi_write
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_erase              nrfx_qspi_erase
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_chip_erase         nrfx_qspi_chip_erase
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_mem_busy_check     nrfx_qspi_mem_busy_check
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_cinstr_xfer        nrfx_qspi_cinstr_xfer
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_qspi_cinstr_quick_send  nrfx_qspi_cinstr_quick_send

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_QSPI_H__
