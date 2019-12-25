/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#ifndef ANT_SEARCH_CONFIG_H__
#define ANT_SEARCH_CONFIG_H__

/** @file
 *
 * @defgroup ant_search_config ANT search configuration
 * @{
 * @ingroup ant_sdk_utils
 * @brief ANT channel search configuration module.
 */

#include <stdint.h>
#include "ant_parameters.h"
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ANT_SEARCH_SHARING_CYCLES_DISABLE   0x00    ///< Disable search sharing.

#define ANT_LOW_PRIORITY_SEARCH_DISABLE     0x00    ///< Disable low priority search.
#define ANT_LOW_PRIORITY_TIMEOUT_DISABLE    0xFF    ///< Disable low priority search time-out.

#define ANT_HIGH_PRIORITY_SEARCH_DISABLE    0x00    ///< Disable high priority search.
#define ANT_HIGH_PRIORITY_TIMEOUT_DISABLE   0xFF    ///< Disable high priority search time-out.

/**@brief Search priority. */
typedef enum
{
    ANT_SEARCH_PRIORITY_DEFAULT = 0,                                ///< Default search priority level.
    ANT_SEARCH_PRIORITY_LOWEST  = ANT_SEARCH_PRIORITY_DEFAULT,      ///< Lowest search priority level.
    ANT_SEARCH_PRIORITY_0       = ANT_SEARCH_PRIORITY_LOWEST,
    ANT_SEARCH_PRIORITY_1       = 1,
    ANT_SEARCH_PRIORITY_2       = 2,
    ANT_SEARCH_PRIORITY_3       = 3,
    ANT_SEARCH_PRIORITY_4       = 4,
    ANT_SEARCH_PRIORITY_5       = 5,
    ANT_SEARCH_PRIORITY_6       = 6,
    ANT_SEARCH_PRIORITY_7       = 7,
    ANT_SEARCH_PRIORITY_HIGHEST = ANT_SEARCH_PRIORITY_7,            ///< Highest search priority level.
} ant_search_priority_t;

/**@brief ANT search waveform. */
typedef enum
{
    ANT_WAVEFORM_DEFAULT    = 316,  ///< Standard search waveform value.
    ANT_WAVEFORM_FAST       = 97,   ///< Accelerated search waveform value.
} ant_waveform_t;

/**@brief ANT search configuration structure. */
typedef struct
{
    uint8_t                 channel_number;         ///< Assigned channel number.
    uint8_t                 low_priority_timeout;   ///< Low priority time-out (in 2.5 second increments).
    uint8_t                 high_priority_timeout;  ///< High priority time-out (in 2.5 second increments).
    uint8_t                 search_sharing_cycles;  ///< Number of search cycles to run before alternating searches. Search sharing can be disabled by @ref ANT_SEARCH_SHARING_CYCLES_DISABLE.
    ant_search_priority_t   search_priority;        ///< Search priority.
    ant_waveform_t          waveform;               ///< Search waveform. Do not use custom values.
} ant_search_config_t;

/**@brief Initializes the default ANT search configuration structure.
 *
 * @param[in]  CHANNEL_NUMBER       Number of the channel.
 */
#define DEFAULT_ANT_SEARCH_CONFIG(CHANNEL_NUMBER)                   \
{                                                                   \
    .channel_number         = CHANNEL_NUMBER,                       \
    .low_priority_timeout   = ANT_DEFAULT_LOW_PRIORITY_TIMEOUT,     \
    .high_priority_timeout  = ANT_DEFAULT_HIGH_PRIORITY_TIMEOUT,    \
    .search_sharing_cycles  = ANT_SEARCH_SHARING_CYCLES_DISABLE,    \
    .search_priority        = ANT_SEARCH_PRIORITY_DEFAULT,          \
    .waveform               = ANT_WAVEFORM_DEFAULT,                 \
}

/**@brief Function for configuring the ANT channel search.
 *
 * @param[in]  p_config        Pointer to the search configuration structure.
 *
 * @retval     NRF_SUCCESS     If the channel was successfully configured. Otherwise, an error code is returned.
 */
uint32_t ant_search_init(ant_search_config_t const * p_config);


#ifdef __cplusplus
}
#endif

#endif // ANT_SEARCH_CONFIG_H__
/** @} */
