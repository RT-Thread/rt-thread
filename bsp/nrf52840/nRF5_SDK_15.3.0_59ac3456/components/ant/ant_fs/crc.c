/**
 * This software is subject to the ANT+ Shared Source License
 * www.thisisant.com/swlicenses
 * Copyright (c) Garmin Canada Inc. 2012
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 *    1) Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *
 *    2) Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 *    3) Neither the name of Garmin nor the names of its
 *       contributors may be used to endorse or promote products
 *       derived from this software without specific prior
 *       written permission.
 *
 * The following actions are prohibited:
 *
 *    1) Redistribution of source code containing the ANT+ Network
 *       Key. The ANT+ Network Key is available to ANT+ Adopters.
 *       Please refer to http://thisisant.com to become an ANT+
 *       Adopter and access the key. 
 *
 *    2) Reverse engineering, decompilation, and/or disassembly of
 *       software provided in binary form under this license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE HEREBY
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; DAMAGE TO ANY DEVICE, LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE. SOME STATES DO NOT ALLOW 
 * THE EXCLUSION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO THE
 * ABOVE LIMITATIONS MAY NOT APPLY TO YOU.
 *
 */
#include "crc.h"
#include "compiler_abstraction.h"


/**@brief Function for updating the current CRC-16 value for a single byte input.
 *
 * @param[in] current_crc The current calculated CRC-16 value.
 * @param[in] byte        The input data byte for the computation.
 *
 * @return The updated CRC-16 value, based on the input supplied.
 */
static __INLINE uint16_t crc16_get(uint16_t current_crc, uint8_t byte)
{
    static const uint16_t crc16_table[16] =
    {
        0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
        0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400
    };

    uint16_t temp;

    // Compute checksum of lower four bits of a byte.
    temp         = crc16_table[current_crc & 0xF];
    current_crc  = (current_crc >> 4u) & 0x0FFFu;
    current_crc  = current_crc ^ temp ^ crc16_table[byte & 0xF];

    // Now compute checksum of upper four bits of a byte.
    temp         = crc16_table[current_crc & 0xF];
    current_crc  = (current_crc >> 4u) & 0x0FFFu;
    current_crc  = current_crc ^ temp ^ crc16_table[(byte >> 4u) & 0xF];

    return current_crc;
}


uint16_t crc_crc16_update(uint16_t current_crc, const volatile void * p_data, uint32_t size)
{
    uint8_t * p_block = (uint8_t *)p_data;

    while (size != 0)
    {
        current_crc = crc16_get(current_crc, *p_block);
        p_block++;
        size--;
    }

   return current_crc;
}
