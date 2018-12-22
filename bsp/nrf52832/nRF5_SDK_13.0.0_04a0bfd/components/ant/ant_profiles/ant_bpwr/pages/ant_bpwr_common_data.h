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
#ifndef ANT_BPWR_COMMON_DATA_H__
#define ANT_BPWR_COMMON_DATA_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_bpwr_common_data_page Stride Based Speed and Distance Monitor profile common data
 * @{
 * @ingroup ant_sdk_profiles_bpwr_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Data structure for BPWR common data.
 *
 * @details This structure stores data that is not associated with a particular page.
 */
typedef struct
{
    uint8_t  instantaneous_cadence; ///< Crank cadence (rpm, 0 - 254, 255-> invalid).
} ant_bpwr_common_data_t;

/**@brief Initialize common data.
 */
#define DEFAULT_ANT_BPWR_COMMON_DATA()  \
    (ant_bpwr_common_data_t)            \
    {                                   \
        .instantaneous_cadence  = 0,    \
    }

/**@brief Function for encoding speed.
 *
 * This function can be used for pages 16, 17, and 18.
 *
 * @param[in]  p_common_data    Pointer to the common data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_bpwr_cadence_encode(uint8_t                     * p_page_buffer,
                            ant_bpwr_common_data_t const * p_common_data);

/**@brief Function for decoding speed.
 *
 * This function can be used for pages 16, 17, and 18.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_common_data    Pointer to the common data.
 */
void ant_bpwr_cadence_decode(uint8_t const         * p_page_buffer,
                            ant_bpwr_common_data_t * p_common_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_BPWR_COMMON_DATA_H__
/** @} */
