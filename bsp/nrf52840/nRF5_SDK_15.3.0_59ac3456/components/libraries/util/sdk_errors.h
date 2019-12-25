/**
 * Copyright (c) 2013 - 2019, Nordic Semiconductor ASA
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
 * @defgroup sdk_error SDK Error codes
 * @{
 * @ingroup app_common
 * @{
 * @details Error codes are 32-bit unsigned integers with the most significant 16-bit reserved for
 *          identifying the module where the error occurred while the least least significant LSB
 *          are used to provide the cause or nature of error. Each module is assigned a 16-bit
 *          unsigned integer. Which it will use to identify all errors that occurred in it. 16-bit
 *          LSB range is with module id as the MSB in the 32-bit error code is reserved for the
 *          module. As an example, if 0x8800 identifies a certain SDK module, all values from
 *          0x88000000 - 0x8800FFFF are reserved for this module.
 *          It should be noted that common error reasons have been assigned values to make it
 *          possible to decode error reason easily. As an example, lets module uninitialized has
 *          been assigned an error code 0x000A0. Then, if application encounters an error code
 *          0xZZZZ00A0, it knows that it accessing a certain module without initializing it.
 *          Apart from this, each module is allowed to define error codes that are not covered by
 *          the common ones, however, these values are defined in a range that does not conflict
 *          with common error values. For module, specific error however, it is possible that the
 *          same error value is used by two different modules to indicated errors of very different
 *          nature. If error is already defined by the NRF common error codes, these are reused.
 *          A range is reserved for application as well, it can use this range for defining
 *          application specific errors.
 *
 * @note Success code, NRF_SUCCESS, does not include any module identifier.

 */

#ifndef SDK_ERRORS_H__
#define SDK_ERRORS_H__

#include <stdint.h>
#include "nrf_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup sdk_err_base Base defined for SDK Modules
 * @{
 */
#define NRF_ERROR_SDK_ERROR_BASE         (NRF_ERROR_BASE_NUM + 0x8000)   /**< Base value defined for SDK module identifiers. */
#define NRF_ERROR_SDK_COMMON_ERROR_BASE  (NRF_ERROR_BASE_NUM + 0x0080)   /**< Base error value to be used for SDK error values. */
/** @} */

/**
 * @defgroup sdk_module_codes Codes reserved as identification for module where the error occurred.
 * @{
 */
#define NRF_ERROR_MEMORY_MANAGER_ERR_BASE   (0x8100)    /**< Base address for Memory Manager related errors. */
#define NRF_ERROR_PERIPH_DRIVERS_ERR_BASE   (0x8200)    /**< Base address for Peripheral drivers related errors. */
#define NRF_ERROR_GAZELLE_ERR_BASE          (0x8300)    /**< Base address for Gazelle related errors. */
#define NRF_ERROR_BLE_IPSP_ERR_BASE         (0x8400)    /**< Base address for BLE IPSP related errors. */
#define NRF_ERROR_CRYPTO_ERR_BASE           (0x8500)    /**< Base address for crypto related errors. */
/** @} */


/**
 * @defgroup sdk_iot_errors Codes reserved as identification for IoT errors.
 * @{
 */
#define NRF_ERROR_IOT_ERR_BASE_START        (0xA000)
#define NRF_ERROR_IOT_ERR_BASE_STOP         (0xAFFF)
/** @} */


/**
 * @defgroup sdk_common_errors Codes reserved as identification for common errors.
 * @{
 */
#define NRF_ERROR_MODULE_NOT_INITIALIZED     (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0000) ///< Module not initialized
#define NRF_ERROR_MUTEX_INIT_FAILED          (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0001) ///< Mutex initialization failed
#define NRF_ERROR_MUTEX_LOCK_FAILED          (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0002) ///< Mutex lock failed
#define NRF_ERROR_MUTEX_UNLOCK_FAILED        (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0003) ///< Mutex unlock failed
#define NRF_ERROR_MUTEX_COND_INIT_FAILED     (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0004) ///< Mutex conditional initialization failed
#define NRF_ERROR_MODULE_ALREADY_INITIALIZED (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0005) ///< Module already initialized
#define NRF_ERROR_STORAGE_FULL               (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0006) ///< Storage full
#define NRF_ERROR_API_NOT_IMPLEMENTED        (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0010) ///< API not implemented
#define NRF_ERROR_FEATURE_NOT_ENABLED        (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0011) ///< Feature not enabled
#define NRF_ERROR_IO_PENDING                 (NRF_ERROR_SDK_COMMON_ERROR_BASE + 0x0012) ///< Input/Output pending
/** @} */


/**
 * @defgroup drv_specific_errors Error / status codes specific to drivers.
 * @{
 */
#define NRF_ERROR_DRV_TWI_ERR_OVERRUN        (NRF_ERROR_PERIPH_DRIVERS_ERR_BASE + 0x0000)
#define NRF_ERROR_DRV_TWI_ERR_ANACK          (NRF_ERROR_PERIPH_DRIVERS_ERR_BASE + 0x0001)
#define NRF_ERROR_DRV_TWI_ERR_DNACK          (NRF_ERROR_PERIPH_DRIVERS_ERR_BASE + 0x0002)
/** @} */


/**
 * @defgroup ble_ipsp_errors IPSP codes
 * @brief Error and status codes specific to IPSP.
 * @{
 */
#define NRF_ERROR_BLE_IPSP_RX_PKT_TRUNCATED       (NRF_ERROR_BLE_IPSP_ERR_BASE + 0x0000)
#define NRF_ERROR_BLE_IPSP_CHANNEL_ALREADY_EXISTS (NRF_ERROR_BLE_IPSP_ERR_BASE + 0x0001)
#define NRF_ERROR_BLE_IPSP_LINK_DISCONNECTED      (NRF_ERROR_BLE_IPSP_ERR_BASE + 0x0002)
#define NRF_ERROR_BLE_IPSP_PEER_REJECTED          (NRF_ERROR_BLE_IPSP_ERR_BASE + 0x0003)
/* @} */


/**
 * @brief API Result.
 *
 * @details Indicates success or failure of an API procedure. In case of failure, a comprehensive
 *          error code indicating cause or reason for failure is provided.
 *
 *          Though called an API result, it could used in Asynchronous notifications callback along
 *          with asynchronous callback as event result. This mechanism is employed when an event
 *          marks the end of procedure initiated using API. API result, in this case, will only be
 *          an indicative of whether the procedure has been requested successfully.
 */
typedef uint32_t ret_code_t;

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif // SDK_ERRORS_H__
