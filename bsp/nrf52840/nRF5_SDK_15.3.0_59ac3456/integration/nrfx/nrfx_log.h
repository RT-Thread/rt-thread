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

#ifndef NRFX_LOG_H__
#define NRFX_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NRFX_LOG_MODULE)
#define NRF_LOG_MODULE_NAME     NRFX_LOG_MODULE

#define NRFX_CONFIG_ENTRY(x)    CONCAT_3(NRFX_, NRFX_LOG_MODULE, x)

#if NRFX_CHECK(NRFX_CONFIG_ENTRY(_CONFIG_LOG_ENABLED))
#define NRF_LOG_LEVEL           NRFX_CONFIG_ENTRY(_CONFIG_LOG_LEVEL)
#define NRF_LOG_INFO_COLOR      NRFX_CONFIG_ENTRY(_CONFIG_INFO_COLOR)
#define NRF_LOG_DEBUG_COLOR     NRFX_CONFIG_ENTRY(_CONFIG_DEBUG_COLOR)
#else
#define NRF_LOG_LEVEL           0
#endif
#endif // defined(NRFX_LOG_MODULE)

#include <nrf_log.h>

#if defined(NRFX_LOG_MODULE)
NRF_LOG_MODULE_REGISTER();
#endif

#define TEST_MACRO_INFO(...)  NRF_LOG_INFO(__VA_ARGS__)
/**
 * @defgroup nrfx_log nrfx_log.h
 * @{
 * @ingroup nrfx
 *
 * @brief This file contains macros that should be implemented according to
 *        the needs of the host environment into which @em nrfx is integrated.
 */

/**
 * @brief Macro for logging a message with the severity level ERROR.
 */
#define NRFX_LOG_ERROR(...)     NRF_LOG_ERROR(__VA_ARGS__)

/**
 * @brief Macro for logging a message with the severity level WARNING.
 */
#define NRFX_LOG_WARNING(...)   NRF_LOG_WARNING(__VA_ARGS__)

/**
 * @brief Macro for logging a message with the severity level INFO.
 */
#define NRFX_LOG_INFO(...)      TEST_MACRO_INFO(__VA_ARGS__)

/**
 * @brief Macro for logging a message with the severity level DEBUG.
 */
#define NRFX_LOG_DEBUG(...)     NRF_LOG_DEBUG(__VA_ARGS__)


/**
 * @brief Macro for logging a memory dump with the severity level ERROR.
 *
 * @param[in] p_memory  Pointer to the memory region to be dumped.
 * @param[in] length    Length of the memory region in bytes.
 */
#define NRFX_LOG_HEXDUMP_ERROR(p_memory, length) \
    NRF_LOG_HEXDUMP_ERROR(p_memory, length)

/**
 * @brief Macro for logging a memory dump with the severity level WARNING.
 *
 * @param[in] p_memory  Pointer to the memory region to be dumped.
 * @param[in] length    Length of the memory region in bytes.
 */
#define NRFX_LOG_HEXDUMP_WARNING(p_memory, length) \
    NRF_LOG_HEXDUMP_WARNING(p_memory, length)

/**
 * @brief Macro for logging a memory dump with the severity level INFO.
 *
 * @param[in] p_memory  Pointer to the memory region to be dumped.
 * @param[in] length    Length of the memory region in bytes.
 */
#define NRFX_LOG_HEXDUMP_INFO(p_memory, length) \
    NRF_LOG_HEXDUMP_INFO(p_memory, length)

/**
 * @brief Macro for logging a memory dump with the severity level DEBUG.
 *
 * @param[in] p_memory  Pointer to the memory region to be dumped.
 * @param[in] length    Length of the memory region in bytes.
 */
#define NRFX_LOG_HEXDUMP_DEBUG(p_memory, length) \
    NRF_LOG_HEXDUMP_DEBUG(p_memory, length)


/**
 * @brief Macro for getting the textual representation of a given error code.
 *
 * @param[in] error_code  Error code.
 *
 * @return String containing the textual representation of the error code.
 */
#define NRFX_LOG_ERROR_STRING_GET(error_code) \
    NRF_LOG_ERROR_STRING_GET(error_code)

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRFX_LOG_H__
