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
#ifndef ANT_COMMON_PAGE_80_H__
#define ANT_COMMON_PAGE_80_H__

/** @file
 *
 * @defgroup ant_sdk_common_pages ANT+ common pages
 * @{
 * @ingroup ant_sdk_profiles
 * @brief This module implements functions for the ANT+ common pages.
 * @details  ANT+ common data pages define common data formats that can be used by any device on any ANT network. The ability to send and receive these common pages is defined by the transmission type of the ANT channel parameter.
 *
 * Note that all unused pages in this section are not defined and therefore cannot be used.
 * @}
 *
 * @defgroup ant_common_page_80 ANT+ common page 80
 * @{
 * @ingroup ant_sdk_common_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ANT_COMMON_PAGE_80 (80) ///< @brief ID value of common page 80.

/**@brief Data structure for ANT+ common data page 80.
 *
 * @note This structure implements only page 80 specific data.
 */
typedef struct
{
    uint8_t  hw_revision;      ///< Hardware revision.
    uint16_t manufacturer_id;  ///< Manufacturer ID.
    uint16_t model_number;     ///< Model number.
} ant_common_page80_data_t;

/**@brief Initialize page 80.
 */
#define DEFAULT_ANT_COMMON_page80()     \
    (ant_common_page80_data_t)          \
    {                                   \
        .hw_revision     = 0x00,        \
        .manufacturer_id = UINT8_MAX,   \
        .model_number    = 0x00,        \
    }

/**@brief Initialize page 80.
 */
#define ANT_COMMON_page80(hw_rev, man_id, mod_num)  \
    (ant_common_page80_data_t)                      \
    {                                               \
        .hw_revision     = (hw_rev),                \
        .manufacturer_id = (man_id),                \
        .model_number    = (mod_num),               \
    }

/**@brief Function for encoding page 80.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_common_page_80_encode(uint8_t * p_page_buffer,
                               volatile ant_common_page80_data_t const * p_page_data);

/**@brief Function for decoding page 80.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_common_page_80_decode(uint8_t const * p_page_buffer,
                               volatile ant_common_page80_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_COMMON_PAGE_80_H__
/** @} */
