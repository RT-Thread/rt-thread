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
#ifndef ANT_COMMON_PAGE_81_H__
#define ANT_COMMON_PAGE_81_H__

/** @file
 *
 * @defgroup ant_common_page_81 ANT+ common page 81
 * @{
 * @ingroup ant_sdk_common_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ANT_COMMON_PAGE_81 (81) ///< @brief ID value of common page 81.

/**@brief Data structure for ANT+ common data page 81.
 *
 * @note This structure implements only page 81 specific data.
 */
typedef struct
{
    uint8_t  sw_revision_minor;  ///< Supplemental, fill by 0xFF if unused.
    uint8_t  sw_revision_major;  ///< Main software version.
    uint32_t serial_number;      ///< Lowest 32 b of serial number, fill by 0xFFFFFFFFF if unused.
} ant_common_page81_data_t;

/**@brief Initialize page 81.
 */
#define DEFAULT_ANT_COMMON_page81()                                     \
    (ant_common_page81_data_t)                                          \
    {                                                                   \
        .sw_revision_minor = UINT8_MAX,                                 \
        .sw_revision_major = UINT8_MAX,                                 \
        .serial_number     = UINT32_MAX,                                \
    }

/**@brief Initialize page 81.
 */
#define ANT_COMMON_page81(sw_major_rev, sw_minor_rev, seril_no)         \
    (ant_common_page81_data_t)                                          \
    {                                                                   \
        .sw_revision_minor = (sw_minor_rev),                            \
        .sw_revision_major = (sw_major_rev),                            \
        .serial_number     = (seril_no),                                \
    }

/**@brief Function for encoding page 81.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_common_page_81_encode(uint8_t * p_page_buffer,
                               volatile ant_common_page81_data_t const * p_page_data);

/**@brief Function for decoding page 81.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_common_page_81_decode(uint8_t const * p_page_buffer,
                               volatile ant_common_page81_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_COMMON_PAGE_81_H__
/** @} */
