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
#ifndef ANT_COMMON_PAGE_70_H__
#define ANT_COMMON_PAGE_70_H__

/** @file
 *
 * @defgroup ant_common_page_70 ANT+ common page 70
 * @{
 * @ingroup ant_sdk_common_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ANT_COMMON_PAGE_70              (70)        ///< @brief ID value of common page 70.
#define ANT_PAGE70_INVALID_DESCRIPTOR   UINT16_MAX  ///< Invalid descriptor.

/**@brief Command type.
 */
typedef enum
{
    ANT_PAGE70_COMMAND_PAGE_DATA_REQUEST        = 0x01,         ///< Page request.
    ANT_PAGE70_COMMAND_ANT_FS_SESSION_REQUEST   = 0x02,         ///< ANT FS session request.
} ant_page70_command_t;


/**@brief Data structure for ANT+ common data page 70.
 */
typedef struct
{
    uint8_t                             page_number;                ///< Requested page number.
    uint16_t                            descriptor;                 ///< Descriptor.
    ant_page70_command_t                command_type;               ///< Command type.
    union
    {
        enum
        {
            ANT_PAGE70_RESPONSE_INVALID                 = 0x00, ///< Invalid response type.
            ANT_PAGE70_RESPONSE_TRANSMIT_UNTIL_SUCCESS  = 0x80, ///< Transmit until a successful acknowledge is received.
        } specyfic;
        struct
        {
            uint8_t     transmit_count     :7;  ///< Number of re-transmissions.
            uint8_t     ack_resposne       :1;  ///< Acknowledge transmission is required.
        } items;
        uint8_t byte;
    } transmission_response;
} ant_common_page70_data_t;

/**@brief Initialize page 70 with default values.
 */
#define DEFAULT_ANT_COMMON_PAGE70()                                             \
    (ant_common_page70_data_t)                                                  \
    {                                                                           \
        .page_number                        = 0x00,                             \
        .command_type                       = (ant_page70_command_t)0x00,       \
        .transmission_response.specyfic     = ANT_PAGE70_RESPONSE_INVALID,      \
        .descriptor                         = ANT_PAGE70_INVALID_DESCRIPTOR,    \
    }

/**@brief Initialize page 70 with the page request.
 */
#define ANT_COMMON_PAGE_DATA_REQUEST(PAGE_NUMBER)                                           \
    (ant_common_page70_data_t)                                                              \
    {                                                                                       \
        .page_number                        = (PAGE_NUMBER),                                \
        .command_type                       = ANT_PAGE70_COMMAND_PAGE_DATA_REQUEST,         \
        .transmission_response.specyfic     = ANT_PAGE70_RESPONSE_TRANSMIT_UNTIL_SUCCESS,   \
        .descriptor                         = ANT_PAGE70_INVALID_DESCRIPTOR,                \
    }

/**@brief Function for encoding page 70.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_common_page_70_encode(uint8_t                                 * p_page_buffer,
                               volatile ant_common_page70_data_t const * p_page_data);

/**@brief Function for decoding page 70.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_common_page_70_decode(uint8_t const                     * p_page_buffer,
                               volatile ant_common_page70_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_COMMON_PAGE_70_H__
/** @} */
