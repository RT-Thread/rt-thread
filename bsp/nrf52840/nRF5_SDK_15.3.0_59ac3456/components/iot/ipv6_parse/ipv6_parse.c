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
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ipv6_parse.h"
#include "nrf_error.h"

static uint16_t ascii_to_hex(char * p_str)
{
    uint16_t res = 0;
    sscanf(p_str, "%hx", &res);
    return res;
}

static void reverse_string(char * p_str)
{
    uint32_t str_len = strlen(p_str);
    for (uint32_t i = 0, j = str_len - 1; i < j; i++, j--)
    {
        char tmp = p_str[i];
        p_str[i] = p_str[j];
        p_str[j] = tmp;
    }
}

uint32_t ipv6_parse_addr(uint8_t * p_addr, const char * p_uri, uint8_t uri_len)
{
    bool    is_compressed       = false;
    uint8_t block_1_len         = uri_len;

    const char  * compressed_position = strstr(&p_uri[0], "::");
    if (compressed_position != NULL)
    {
        is_compressed = true;
        block_1_len = compressed_position - &p_uri[0];
    }
    // Parse block 1.
    uint8_t block_1_end            = block_1_len;
    char    sub_addr_buf[5]        = {'\0',};

    uint8_t char_pos               = 0;
    uint8_t sub_addr_count_block_1 = 0;

    for (uint8_t i = 0; i < block_1_end; i++)
    {
        if (p_uri[i] != ':')
        {
            sub_addr_buf[char_pos++] = p_uri[i];
        }
        else
        {
            // we have read all number bytes and hit a delimiter. Save the sub address.
            uint16_t value = ascii_to_hex(sub_addr_buf);
            p_addr[sub_addr_count_block_1++] = ((value & 0xFF00) >> 8);
            p_addr[sub_addr_count_block_1++] = ((value & 0x00FF));

            char_pos = 0;
            memset(sub_addr_buf, '\0', 5);

        }

        // if we are at the end of block 1, save the last sub address.
        if ((i + 1) == block_1_end)
        {
            uint16_t value = ascii_to_hex(sub_addr_buf);
            p_addr[sub_addr_count_block_1++] = ((value & 0xFF00) >> 8);
            p_addr[sub_addr_count_block_1++] = ((value & 0x00FF));


            char_pos = 0;
            memset(sub_addr_buf, '\0', 5);
        }
    }

    if (is_compressed == true)
    {
        // NOTE: sub_addr_buf must be cleared in previous loop.

        // lets parse backwards for second block.
        uint8_t block_2_start = block_1_end + 2; // skip the '::' delimiter.
        uint8_t block_2_len   = uri_len - (block_1_len + 2);
        uint8_t block_2_end   = block_2_start + block_2_len;

        uint8_t sub_addr_count_block_2 = 0;
        uint8_t sub_addr_index         = 15;

        for (uint8_t i = block_2_end - 1; i > block_2_start - 1; i--)
        {
            if (p_uri[i] != ':')
            {
                sub_addr_buf[char_pos++] = p_uri[i];
            }
            else
            {
                // we have read all number bytes and hit a delimiter. Save the sub address.
                reverse_string(sub_addr_buf);

                uint16_t value = ascii_to_hex(sub_addr_buf);
                p_addr[sub_addr_index--] = ((value & 0x00FF));
                p_addr[sub_addr_index--] = ((value & 0xFF00) >> 8);
                sub_addr_count_block_2 += 2;
                char_pos = 0;
                memset(sub_addr_buf, '\0', 5);

            }

            // if we are at the end of block 1, save the last sub address.
            if (i == block_2_start)
            {
                reverse_string(sub_addr_buf);

                uint16_t value = ascii_to_hex(sub_addr_buf);
                p_addr[sub_addr_index--] = ((value & 0x00FF));
                p_addr[sub_addr_index--] = ((value & 0xFF00) >> 8);
                sub_addr_count_block_2 += 2;
                char_pos = 0;
                memset(sub_addr_buf, '\0', 5);
            }
        }

        for (uint8_t i = sub_addr_count_block_1; i < (16 - sub_addr_count_block_2); i++)
        {
            p_addr[i] = 0x00;
        }
    }
    return NRF_SUCCESS;
}
