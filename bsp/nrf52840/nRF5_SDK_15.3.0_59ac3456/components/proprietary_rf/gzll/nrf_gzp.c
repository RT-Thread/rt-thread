/**
 * Copyright (c) 2009 - 2019, Nordic Semiconductor ASA
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
/**
 * @file
 * @brief Implementation of Gazell Pairing Library (gzp), Common functions.
 * @defgroup gzp_source_common Gazell Pairing common functions implementation
 * @{
 * @ingroup gzp_04_source
 */


#include "nrf_gzp.h"
#include "nrf_gzll.h"
#include "nrf_ecb.h"
#include <string.h>


#define SOURCE_FILE NRF_SOURCE_FILE_GZP    ///< File identifer for asserts.


/******************************************************************************/
/** @name Global variables
 *  @{ */
/******************************************************************************/

/**
 * Constant holding base address part of the pairing address.
 */
static const uint8_t pairing_base_address[4] = { GZP_ADDRESS };

/**
 * Constant holding prefix byte of the pairing address.
 */
static const uint8_t pairing_address_prefix_byte = 0;

/**
 * Constant holding pre-defined "validation ID".
 */
static const uint8_t gzp_validation_id[GZP_VALIDATION_ID_LENGTH] = GZP_VALIDATION_ID;

/**
 * Constant holding pre-defined "secret key".
 */
static const uint8_t gzp_secret_key[16] = GZP_SECRET_KEY;

/**
 * Variable used for AES key selection
 */
static gzp_key_select_t gzp_key_select;


/** @} */


/******************************************************************************/
/** @name Misc. external variables.
 *  @{ */
/******************************************************************************/
static uint8_t gzp_session_token[GZP_SESSION_TOKEN_LENGTH];
static uint8_t gzp_dyn_key[GZP_DYN_KEY_LENGTH];

/** @} */

/******************************************************************************/
/** @name Implementation common internal GZP functions
 *  @{ */
/******************************************************************************/
bool gzp_update_radio_params(const uint8_t* system_address)
{
    uint8_t i;
    uint8_t channels[NRF_GZLL_CONST_MAX_CHANNEL_TABLE_SIZE];
    uint32_t channel_table_size;
    uint32_t pairing_base_address_32, system_address_32;
    bool update_ok = true;
    bool gzll_enabled_state;

    gzll_enabled_state = nrf_gzll_is_enabled();

    // Configure "global" pairing address
    pairing_base_address_32 = (pairing_base_address[0])       +
    ((uint32_t)pairing_base_address[1] <<  8) +
    ((uint32_t)pairing_base_address[2] << 16) +
    ((uint32_t)pairing_base_address[3] << 24) ;
    if (system_address != NULL)
    {
        system_address_32 = (system_address[0])       +
        ((uint32_t)system_address[1] <<  8) +
        ((uint32_t)system_address[2] << 16) +
        ((uint32_t)system_address[3] << 24) ;
    }
    else
    {
        return false;
    }

    nrf_gzp_disable_gzll();
    update_ok = update_ok && nrf_gzll_set_base_address_0(pairing_base_address_32);
    update_ok = update_ok && nrf_gzll_set_address_prefix_byte(GZP_PAIRING_PIPE, pairing_address_prefix_byte);
    update_ok = update_ok && nrf_gzll_set_base_address_1(system_address_32);

    // Configure address for pipe 1 - 5. Address byte set to equal pipe number.
    for (i = 1; i < NRF_GZLL_CONST_PIPE_COUNT; i++)
    {
        update_ok = update_ok && nrf_gzll_set_address_prefix_byte(i,i);
    }

    channel_table_size = nrf_gzll_get_channel_table_size();
    gzp_generate_channels(&channels[0], system_address, channel_table_size);

    // Write generated channel subset to Gazell Link Layer
    update_ok = update_ok && nrf_gzll_set_channel_table(&channels[0], channel_table_size);
    if (gzll_enabled_state)
    {
        update_ok = update_ok && nrf_gzll_enable();
    }
    return update_ok;
}

void gzp_generate_channels(uint8_t* ch_dst, const uint8_t* system_address, uint8_t channel_tab_size)
{
    uint8_t binsize, spacing, i;

    binsize = (GZP_CHANNEL_MAX - GZP_CHANNEL_MIN) / channel_tab_size;

    ch_dst[0] = GZP_CHANNEL_LOW;
    ch_dst[channel_tab_size - 1] = GZP_CHANNEL_HIGH;

    if (system_address != NULL)
    {
        for (i = 1; i < (channel_tab_size - 1); i++)
        {
            ch_dst[i] = (binsize * i) + (system_address[i % 4] % binsize);
        }
    }

    // If channels are too close, shift them to better positions
    for (i = 1; i < channel_tab_size; i++)
    {
        spacing = (ch_dst[i] - ch_dst[i - 1]);
        if (spacing < GZP_CHANNEL_SPACING_MIN)
        {
            ch_dst[i] += (GZP_CHANNEL_SPACING_MIN - spacing);
        }
    }
}

__INLINE void nrf_gzp_disable_gzll(void)
{
    if (nrf_gzll_is_enabled())
    {
        nrf_gzll_disable();
        __WFI();
        while (nrf_gzll_is_enabled())
        {
        }
    }
}

#ifndef GZP_CRYPT_DISABLE

void gzp_xor_cipher(uint8_t* dst, const uint8_t* src, const uint8_t* pad, uint8_t length)
{
    uint8_t i;

    for (i = 0; i < length; i++)
    {
        *dst = *src ^ *pad;
        dst++;
        src++;
        pad++;
    }
}

bool gzp_validate_id(const uint8_t* id)
{
    return (memcmp(id, (void*)gzp_validation_id, GZP_VALIDATION_ID_LENGTH) == 0);
}

void gzp_add_validation_id(uint8_t* dst)
{
    memcpy(dst, (void const*)gzp_validation_id, GZP_VALIDATION_ID_LENGTH);
}

void gzp_crypt_set_session_token(const uint8_t * token)
{
    memcpy(gzp_session_token, (void const*)token, GZP_SESSION_TOKEN_LENGTH);
}

void gzp_crypt_set_dyn_key(const uint8_t* key)
{
    memcpy(gzp_dyn_key, (void const*)key, GZP_DYN_KEY_LENGTH);
}

void gzp_crypt_get_session_token(uint8_t * dst_token)
{
    memcpy(dst_token, (void const*)gzp_session_token, GZP_SESSION_TOKEN_LENGTH);
}

void gzp_crypt_get_dyn_key(uint8_t* dst_key)
{
    memcpy(dst_key, (void const*)gzp_dyn_key, GZP_DYN_KEY_LENGTH);
}

void gzp_crypt_select_key(gzp_key_select_t key_select)
{
    gzp_key_select = key_select;
}

void gzp_crypt(uint8_t* dst, const uint8_t* src, uint8_t length)
{
    uint8_t i;
    uint8_t key[16];
    uint8_t iv[16];

    // Build AES key based on "gzp_key_select"

    switch (gzp_key_select)
    {
    case GZP_ID_EXCHANGE:
        memcpy(key, (void const*)gzp_secret_key, 16);
        break;
    case GZP_KEY_EXCHANGE:
        memcpy(key, (void const*)gzp_secret_key, 16);
        gzp_get_host_id(key);
        break;
    case GZP_DATA_EXCHANGE:
        memcpy(key, (void const*)gzp_secret_key, 16);
        memcpy(key, (void const*)gzp_dyn_key, GZP_DYN_KEY_LENGTH);
        break;
    default:
        return;
    }

    // Build init vector from "gzp_session_token"
    for (i = 0; i < 16; i++)
    {
        if (i < GZP_SESSION_TOKEN_LENGTH)
        {
            iv[i] = gzp_session_token[i];
        }
        else
        {
            iv[i] = 0;
        }
    }

    // Set up hal_aes using new key and init vector
    (void)nrf_ecb_init();
    nrf_ecb_set_key(key);
    //hal_aes_setup(false, ECB, key, NULL); // Note, here we skip the IV as we use ECB mode

    // Encrypt IV using ECB mode
    (void)nrf_ecb_crypt(iv, iv);

    // Encrypt data by XOR'ing with AES output
    gzp_xor_cipher(dst, src, iv, length);

}

void gzp_random_numbers_generate(uint8_t * dst, uint8_t n)
{
    uint8_t i;

    NRF_RNG->EVENTS_VALRDY=0;
    NRF_RNG->TASKS_START = 1;
    for (i = 0; i < n; i++)
    {
        while (NRF_RNG->EVENTS_VALRDY==0)
        {}
        dst[i] = (uint8_t)NRF_RNG->VALUE;
        NRF_RNG->EVENTS_VALRDY=0;
    }
    NRF_RNG->TASKS_STOP = 1;
}


/******************************************************************************/
/** @name Implementation of nRF51 specific GZP functions
 *  @{ */
/******************************************************************************/

/**
* @brief Function for setting the Primask variable. Only necessary if ARMCC
* compiler skips __set_PRIMASK at high optimization levels.
*
* @param primask The primask value. 1 to disable interrupts, 0 otherwise.
*/
static void nrf_gzp_set_primask(uint32_t primask)
{
    #if defined(__CC_ARM)
    //lint -save -e10 -e618 -e438 -e550 -e526 -e628 -e526
    volatile register uint32_t __regPriMask         __ASM("primask");
    __regPriMask = (primask);
    #else
    __set_PRIMASK(primask);
    #endif
    //lint -restore
}

void nrf_gzp_flush_rx_fifo(uint32_t pipe)
{
    static uint8_t dummy_packet[NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH];
    uint32_t length;

    nrf_gzp_set_primask(1);
    while (nrf_gzll_get_rx_fifo_packet_count(pipe) >0)
    {
        length = NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH;
        (void)nrf_gzll_fetch_packet_from_rx_fifo(pipe,dummy_packet,&length);
    }
    nrf_gzp_set_primask(0);
}
/** @} */



/******************************************************************************/
/** @name Implementation of debug functions
 *  @{ */
/******************************************************************************/


/** @} */

/** @} */
#endif
