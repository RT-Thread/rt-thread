/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#include <stdint.h>
#include <stdbool.h>
#include "nordic_common.h"
#include "sdk_common.h"
#include "sdk_config.h"
#include "ipv6_utils.h"

void ipv6_checksum_calculate(const uint8_t * p_data, uint16_t len, uint16_t * p_checksum, bool flip_flag)
{
    uint16_t checksum_even = (((*p_checksum) & 0xFF00) >> 8);
    uint16_t checksum_odd  = ((*p_checksum) & 0x00FF);

    while (len)
    {
        if ( len == 1 )
        {
          checksum_even += (*p_data);
          len           -= 1;
        }
        else
        {
          checksum_even += *p_data++;
          checksum_odd  += *p_data++;
          len           -= 2;
        }

        if (checksum_odd & 0xFF00)
        {
            checksum_even += ((checksum_odd & 0xFF00) >> 8);
            checksum_odd   = (checksum_odd & 0x00FF);
        }

        if (checksum_even & 0xFF00)
        {
            checksum_odd += ((checksum_even & 0xFF00) >> 8);
            checksum_even = (checksum_even & 0x00FF);
        }
    }

    checksum_even = (checksum_even << 8) + (checksum_odd & 0xFFFF);

    if (flip_flag)
    {
        // We use 0xFFFF instead of 0x0000 because of not operator.
        if (checksum_even == 0xFFFF)
        {
            checksum_even = 0x0000;
        }
    }

    (*p_checksum) = (uint16_t)(checksum_even);
}

void ipv6_header_init(ipv6_header_t * p_ip_header)
{
    p_ip_header->version_traffic_class   = IPV6_DEFAULT_VER_TC;
    p_ip_header->traffic_class_flowlabel = IPV6_DEFAULT_TC_FL;
    p_ip_header->flowlabel               = IPV6_DEFAULT_FL;
    p_ip_header->next_header             = IPV6_NEXT_HEADER_RESERVED;
    p_ip_header->hoplimit                = IPV6_DEFAULT_HOP_LIMIT;
    p_ip_header->length                  = 0;
}
