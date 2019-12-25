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
 * @defgroup nrf_dfu_rescodes DFU result codes
 * @{
 * @ingroup  sdk_nrf_dfu_transport
 * @brief When the DFU controller sends requests to the DFU bootloader on
 * the DFU target, the DFU bootloader answers with any of these result codes.
 */


#ifndef DFU_HANDLING_ERROR_H__
#define DFU_HANDLING_ERROR_H__

#include "nrf_dfu_types.h"
#include "nrf_dfu_req_handler.h"

#ifdef __cplusplus
extern "C" {
#endif



/**@brief DFU request extended result codes.
 *
 * @details When an event returns @ref NRF_DFU_RES_CODE_EXT_ERROR, it also stores an extended error code.
 *          The transport layer can then send the extended error code together with the error code to give
 *          the controller additional information about the cause of the error.
 */
typedef enum
{
    NRF_DFU_EXT_ERROR_NO_ERROR                  = 0x00, /**< No extended error code has been set. This error indicates an implementation problem. */
    NRF_DFU_EXT_ERROR_INVALID_ERROR_CODE        = 0x01, /**< Invalid error code. This error code should never be used outside of development. */
    NRF_DFU_EXT_ERROR_WRONG_COMMAND_FORMAT      = 0x02, /**< The format of the command was incorrect. This error code is not used in the
                                                             current implementation, because @ref NRF_DFU_RES_CODE_OP_CODE_NOT_SUPPORTED
                                                             and @ref NRF_DFU_RES_CODE_INVALID_PARAMETER cover all
                                                             possible format errors. */
    NRF_DFU_EXT_ERROR_UNKNOWN_COMMAND           = 0x03, /**< The command was successfully parsed, but it is not supported or unknown. */
    NRF_DFU_EXT_ERROR_INIT_COMMAND_INVALID      = 0x04, /**< The init command is invalid. The init packet either has
                                                             an invalid update type or it is missing required fields for the update type
                                                             (for example, the init packet for a SoftDevice update is missing the SoftDevice size field). */
    NRF_DFU_EXT_ERROR_FW_VERSION_FAILURE        = 0x05, /**< The firmware version is too low. For an application or SoftDevice, the version must be greater than
                                                             or equal to the current version. For a bootloader, it must be greater than the current version.
                                                             to the current version. This requirement prevents downgrade attacks.*/
    NRF_DFU_EXT_ERROR_HW_VERSION_FAILURE        = 0x06, /**< The hardware version of the device does not match the required
                                                             hardware version for the update. */
    NRF_DFU_EXT_ERROR_SD_VERSION_FAILURE        = 0x07, /**< The array of supported SoftDevices for the update does not contain
                                                             the FWID of the current SoftDevice or the first FWID is '0' on a
                                                             bootloader which requires the SoftDevice to be present. */
    NRF_DFU_EXT_ERROR_SIGNATURE_MISSING         = 0x08, /**< The init packet does not contain a signature. This error code is not used in the
                                                             current implementation, because init packets without a signature
                                                             are regarded as invalid. */
    NRF_DFU_EXT_ERROR_WRONG_HASH_TYPE           = 0x09, /**< The hash type that is specified by the init packet is not supported by the DFU bootloader. */
    NRF_DFU_EXT_ERROR_HASH_FAILED               = 0x0A, /**< The hash of the firmware image cannot be calculated. */
    NRF_DFU_EXT_ERROR_WRONG_SIGNATURE_TYPE      = 0x0B, /**< The type of the signature is unknown or not supported by the DFU bootloader. */
    NRF_DFU_EXT_ERROR_VERIFICATION_FAILED       = 0x0C, /**< The hash of the received firmware image does not match the hash in the init packet. */
    NRF_DFU_EXT_ERROR_INSUFFICIENT_SPACE        = 0x0D, /**< The available space on the device is insufficient to hold the firmware. */
} nrf_dfu_ext_error_code_t;


/**@brief Function for setting an extended error code that can be retrieved later.
 *
 * @details When an extended error occurs in the DFU process, this function can be used to store the error.
 *
 * @param error_code The error code to store.
 *
 * @retval NRF_DFU_RES_CODE_EXT_ERROR
 */
nrf_dfu_result_t ext_error_set(nrf_dfu_ext_error_code_t error_code);

/**@brief Function for getting the most recent extended error code.
 *
 * @details This function is used by the transport layer to fetch the most recent extended error code.
 *
 * @return The most recent error code. If the function is called again before a new error occurs, @ref NRF_DFU_EXT_ERROR_NO_ERROR is returned.
 */
nrf_dfu_ext_error_code_t ext_error_get( void );


#ifdef __cplusplus
}
#endif

#endif // DFU_HANDLING_ERROR_H__

/** @} */
