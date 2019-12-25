/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#include "nrf_bootloader_info.h"

#define MBR_IRQ_FORWARD_ADDRESS_ADDRESS (0x20000000) //!< The address of the variable that decides where the MBR forwards interrupts

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


uint32_t nrf_dfu_mbr_irq_forward_address_set(void)
{
    uint32_t ret_val = NRF_ERROR_INVALID_PARAM;
    uint32_t address = MBR_SIZE;

#if !defined(BLE_STACK_SUPPORT_REQD) && !defined(ANT_STACK_SUPPORT_REQD)
    sd_mbr_command_t command =
    {
        .command = SD_MBR_COMMAND_IRQ_FORWARD_ADDRESS_SET,
        .params.irq_forward_address_set.address = address,
    };

    ret_val = sd_mbr_command(&command);
#endif

    if (ret_val == NRF_ERROR_INVALID_PARAM)
    {
        // Manually set the forward address if this MBR doesn't have the command.
        *(uint32_t *)(MBR_IRQ_FORWARD_ADDRESS_ADDRESS) = address;

        ret_val = NRF_SUCCESS;
    }

    return ret_val;
}
