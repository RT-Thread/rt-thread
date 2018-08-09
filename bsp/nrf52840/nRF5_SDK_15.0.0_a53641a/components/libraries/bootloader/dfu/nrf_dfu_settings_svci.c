/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#include <string.h>
#include "app_error.h"
#include "sdk_macros.h"
#include "nrf_dfu_settings.h"
#include "nrf_nvmc.h"
#include "crc32.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_settings_svci
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define DFU_SETTINGS_PEER_DATA_OFFSET           offsetof(nrf_dfu_settings_t, peer_data)             //<! Offset in the settings struct where the additional peer data is located.
#define DFU_SETTINGS_ADV_NAME_OFFSET            offsetof(nrf_dfu_settings_t, adv_name)              //<! Offset in the settings struct where the additional advertisement name is located.

extern nrf_dfu_settings_t s_dfu_settings;
extern uint8_t m_dfu_settings_buffer[CODE_PAGE_SIZE];

#if defined(NRF_DFU_BLE_REQUIRES_BONDS) && (NRF_DFU_BLE_REQUIRES_BONDS == 1)

ret_code_t nrf_dfu_settings_peer_data_write(nrf_dfu_peer_data_t * p_data)
{
    uint32_t        ret_val;

    uint32_t *      p_peer_data_settings =
        (uint32_t*) &m_dfu_settings_buffer[DFU_SETTINGS_PEER_DATA_OFFSET];

    uint32_t crc = (uint32_t)*p_peer_data_settings;

    VERIFY_PARAM_NOT_NULL(p_data);

    if (crc != 0xFFFFFFFF)
    {
        // Already written to, must be cleared out
        // Reset required.
        return NRF_ERROR_INVALID_STATE;
    }

    // Calculate the CRC for the structure excluding the CRC value itself.
    p_data->crc = crc32_compute((uint8_t*)p_data + 4, sizeof(nrf_dfu_peer_data_t) - 4, NULL);

    // Using SoftDevice call since this function cannot use static memory.
    ret_val = sd_flash_write(p_peer_data_settings,
                             (uint32_t*)p_data,
                             sizeof(nrf_dfu_peer_data_t)/4);

    return ret_val;
}


ret_code_t nrf_dfu_settings_peer_data_copy(nrf_dfu_peer_data_t * p_data)
{
    VERIFY_PARAM_NOT_NULL(p_data);

    memcpy(p_data, &m_dfu_settings_buffer[DFU_SETTINGS_PEER_DATA_OFFSET], sizeof(nrf_dfu_peer_data_t));

    return NRF_SUCCESS;
}


bool nrf_dfu_settings_peer_data_is_valid(void)
{
    nrf_dfu_peer_data_t * p_peer_data =
        (nrf_dfu_peer_data_t*) &m_dfu_settings_buffer[DFU_SETTINGS_PEER_DATA_OFFSET];

    // Calculate the CRC for the structure excluding the CRC value itself.
    uint32_t crc = crc32_compute((uint8_t*)p_peer_data + 4, sizeof(nrf_dfu_peer_data_t) - 4, NULL);

    return (p_peer_data->crc == crc);
}

#else // not NRF_DFU_BLE_REQUIRES_BONDS

ret_code_t nrf_dfu_settings_adv_name_write(nrf_dfu_adv_name_t * p_adv_name)
{
    uint32_t        ret_val;

    uint32_t * p_adv_name_settings =
        (uint32_t*) &m_dfu_settings_buffer[DFU_SETTINGS_ADV_NAME_OFFSET];

    uint32_t crc = (uint32_t)*p_adv_name_settings;

    VERIFY_PARAM_NOT_NULL(p_adv_name);

    if (crc != 0xFFFFFFFF)
    {
        // Already written to, must be cleared out.
        // Reset required
        return NRF_ERROR_INVALID_STATE;
    }

    // Calculate the CRC for the structure excluding the CRC value itself.
    p_adv_name->crc = crc32_compute((uint8_t *)p_adv_name + 4, sizeof(nrf_dfu_adv_name_t) - 4, NULL);

    // Using SoftDevice call since this function cannot use static memory.
    ret_val = sd_flash_write(p_adv_name_settings,
                             (uint32_t*) p_adv_name,
                             sizeof(nrf_dfu_adv_name_t)/4);
    return ret_val;
}


ret_code_t nrf_dfu_settings_adv_name_copy(nrf_dfu_adv_name_t * p_adv_name)
{
    VERIFY_PARAM_NOT_NULL(p_adv_name);
    memcpy(p_adv_name, &m_dfu_settings_buffer[DFU_SETTINGS_ADV_NAME_OFFSET], sizeof(nrf_dfu_adv_name_t));

    return NRF_SUCCESS;
}


bool nrf_dfu_settings_adv_name_is_valid(void)
{
    nrf_dfu_adv_name_t * p_adv_name =
        (nrf_dfu_adv_name_t*)&m_dfu_settings_buffer[DFU_SETTINGS_ADV_NAME_OFFSET];

    // Calculate the CRC for the structure excluding the CRC value itself.
    uint32_t crc = crc32_compute((uint8_t*)p_adv_name + 4, sizeof(nrf_dfu_adv_name_t) - 4, NULL);

    return (p_adv_name->crc == crc);
}

#endif


//lint -save -e(14)
ret_code_t nrf_dfu_settings_additional_erase(void)
{
    ret_code_t ret_code = NRF_SUCCESS;
    
    // Check CRC for both types.
    if (   (s_dfu_settings.peer_data.crc != 0xFFFFFFFF)
        || (s_dfu_settings.adv_name.crc  != 0xFFFFFFFF))
    {
        NRF_LOG_DEBUG("Erasing settings page additional data.");

        // Erasing and resetting the settings page without the peer data/adv data
        nrf_nvmc_page_erase(BOOTLOADER_SETTINGS_ADDRESS);
        nrf_nvmc_write_words(BOOTLOADER_SETTINGS_ADDRESS, (uint32_t const *)&s_dfu_settings, DFU_SETTINGS_PEER_DATA_OFFSET / 4);
    }

    return ret_code;
}
//lint -restore

