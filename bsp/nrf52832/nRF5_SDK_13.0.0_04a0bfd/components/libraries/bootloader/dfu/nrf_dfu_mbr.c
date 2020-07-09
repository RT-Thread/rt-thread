/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#include "nrf_dfu_mbr.h"
#include "nrf_mbr.h"
#include "nrf_dfu_types.h"
#include "nrf_log.h"

uint32_t nrf_dfu_mbr_copy_bl(uint32_t * p_src, uint32_t len)
{
    uint32_t ret_val;
    uint32_t const len_words = len / sizeof(uint32_t);

    sd_mbr_command_t command =
    {
        .command = SD_MBR_COMMAND_COPY_BL,
        .params.copy_bl.bl_src = p_src,
        .params.copy_bl.bl_len = len_words
    };

    ret_val = sd_mbr_command(&command);

    return ret_val;
}


uint32_t nrf_dfu_mbr_copy_sd(uint32_t * p_dst, uint32_t * p_src, uint32_t len)
{
    uint32_t ret_val;
    uint32_t const len_words = len / sizeof(uint32_t);

    if((len_words & (CODE_PAGE_SIZE / sizeof(uint32_t) - 1)) != 0)
        return NRF_ERROR_INVALID_LENGTH;

    sd_mbr_command_t command =
    {
        .command = SD_MBR_COMMAND_COPY_SD,
        .params.copy_sd.src = p_src,
        .params.copy_sd.dst = p_dst,
        .params.copy_sd.len = len_words
    };

    ret_val = sd_mbr_command(&command);

    return ret_val;
}


uint32_t nrf_dfu_mbr_init_sd(void)
{
    uint32_t ret_val;

    sd_mbr_command_t command =
    {
        .command = SD_MBR_COMMAND_INIT_SD
    };

    ret_val = sd_mbr_command(&command);

    return ret_val;
}


uint32_t nrf_dfu_mbr_compare(uint32_t * p_ptr1, uint32_t * p_ptr2, uint32_t len)
{
    uint32_t ret_val;
    uint32_t const len_words = len / sizeof(uint32_t);

    sd_mbr_command_t command =
    {
        .command = SD_MBR_COMMAND_COMPARE,
        .params.compare.ptr1 = p_ptr1,
        .params.compare.ptr2 = p_ptr2,
        .params.compare.len = len_words
    };

    ret_val = sd_mbr_command(&command);

    return ret_val;
}


uint32_t nrf_dfu_mbr_vector_table_set(uint32_t address, uint8_t is_temporary)
{
    uint32_t ret_val;

    NRF_LOG_DEBUG("running vector table set\r\n");
    sd_mbr_command_t command =
    {
        .command = SD_MBR_COMMAND_VECTOR_TABLE_BASE_SET,
        .params.base_set.address = address,
#ifndef SOFTDEVICE_PRESENT
        .params.base_set.temporary = is_temporary,
#endif
    };

    ret_val = sd_mbr_command(&command);
    NRF_LOG_DEBUG("After running vector table set\r\n");

    return ret_val;
}
