/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
#include "ble_flash.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "nrf_soc.h"
#include "nordic_common.h"
#include "nrf_error.h"
#include "nrf.h"
#include "app_util.h"


static volatile bool m_radio_active = false;  /**< TRUE if radio is active (or about to become active), FALSE otherwise. */


uint16_t ble_flash_crc16_compute(uint8_t * p_data, uint16_t size, uint16_t * p_crc)
{
    uint16_t i;
    uint16_t crc = (p_crc == NULL) ? 0xffff : *p_crc;

    for (i = 0; i < size; i++)
    {
        crc  = (unsigned char)(crc >> 8) | (crc << 8);
        crc ^= p_data[i];
        crc ^= (unsigned char)(crc & 0xff) >> 4;
        crc ^= (crc << 8) << 4;
        crc ^= ((crc & 0xff) << 4) << 1;
    }
    return crc;
}


/**@brief Function for erasing a page in flash.
 *
 * @param[in]  p_page  Pointer to first word in page to be erased.
 */
static void flash_page_erase(uint32_t * p_page)
{
    // Turn on flash erase enable and wait until the NVMC is ready.
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos);
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Erase page.
    NRF_NVMC->ERASEPAGE = (uint32_t)p_page;
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Turn off flash erase enable and wait until the NVMC is ready.
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing
    }
}


/**@brief Function for writing one word to flash. Unprotected write, which can interfere with radio communication.
 *
 * @details This function DOES NOT use the m_radio_active variable, but will force the write even
 *          when the radio is active. To be used only from @ref ble_flash_page_write.
 *
 * @note Flash location to be written must have been erased previously.
 *
 * @param[in]  p_address   Pointer to flash location to be written.
 * @param[in]  value       Value to write to flash.
 */
static void flash_word_unprotected_write(uint32_t * p_address, uint32_t value)
{
    // Turn on flash write enable and wait until the NVMC is ready.
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos);
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }
    *p_address = value;

    // Wait flash write to finish
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Turn off flash write enable and wait until the NVMC is ready.
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }
}


/**@brief Function for writing one word to flash.
 *
 * @note Flash location to be written must have been erased previously.
 *
 * @param[in]  p_address   Pointer to flash location to be written.
 * @param[in]  value       Value to write to flash.
 */
static void flash_word_write(uint32_t * p_address, uint32_t value)
{
    // If radio is active, wait for it to become inactive.
    while (m_radio_active)
    {
        // Do nothing (just wait for radio to become inactive).
        (void) sd_app_evt_wait();
    }

    // Turn on flash write enable and wait until the NVMC is ready.
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos);
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    *p_address = value;
    // Wait flash write to finish
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }
    // Turn off flash write enable and wait until the NVMC is ready.
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing
    }
}


uint32_t ble_flash_word_write(uint32_t * p_address, uint32_t value)
{
    flash_word_write(p_address, value);
    return NRF_SUCCESS;
}


uint32_t ble_flash_block_write(uint32_t * p_address, uint32_t * p_in_array, uint16_t word_count)
{
    uint16_t i;

    for (i = 0; i < word_count; i++)
    {
        flash_word_write(p_address, p_in_array[i]);
        p_address++;
    }

    return NRF_SUCCESS;
}


uint32_t ble_flash_page_erase(uint8_t page_num)
{
    uint32_t * p_page = (uint32_t *)(BLE_FLASH_PAGE_SIZE * page_num);
    flash_page_erase(p_page);

    return NRF_SUCCESS;
}


uint32_t ble_flash_page_write(uint8_t page_num, uint32_t * p_in_array, uint8_t word_count)
{
    int        i;
    uint32_t * p_page;
    uint32_t * p_curr_addr;
    uint16_t   in_data_crc;
    uint16_t   flash_crc;
    uint32_t   flash_header;

    p_page      = (uint32_t *)(BLE_FLASH_PAGE_SIZE * page_num);
    p_curr_addr = p_page;

    // Calculate CRC of the data to write.
    in_data_crc = ble_flash_crc16_compute((uint8_t *)p_in_array,
                                          word_count * sizeof(uint32_t),
                                          NULL);

    // Compare the calculated to the one in flash.
    flash_header = *p_curr_addr;
    flash_crc    = (uint16_t)flash_header;

    if (flash_crc == in_data_crc)
    {
        // Data is the same as the data already stored in flash, return without modifying flash.
        return NRF_SUCCESS;
    }

    // Erase flash page
    flash_page_erase(p_page);

    // Reserve space for magic number (for detecting if flash content is valid).
    p_curr_addr++;

    // Reserve space for saving word_count.
    p_curr_addr++;

    // Write data
    for (i = 0; i < word_count; i++)
    {
        flash_word_unprotected_write(p_curr_addr, p_in_array[i]);
        p_curr_addr++;
    }

    // Write number of elements.
    flash_word_write(p_page + 1, (uint32_t)(word_count));

    // Write magic number and CRC to indicate that flash content is valid.
    flash_header = BLE_FLASH_MAGIC_NUMBER | (uint32_t)in_data_crc;
    flash_word_write(p_page, flash_header);

    return NRF_SUCCESS;
}


uint32_t ble_flash_page_read(uint8_t page_num, uint32_t * p_out_array, uint8_t * p_word_count)
{
    int        byte_count;
    uint32_t * p_page;
    uint32_t * p_curr_addr;
    uint32_t   flash_header;
    uint32_t   calc_header;
    uint16_t   calc_crc;
    uint32_t   tmp;

    p_page      = (uint32_t *)(BLE_FLASH_PAGE_SIZE * page_num);
    p_curr_addr = p_page;

    // Check if block is valid
    flash_header = *p_curr_addr;
    tmp = flash_header & 0xFFFF0000;
    if (tmp != BLE_FLASH_MAGIC_NUMBER)
    {
        *p_word_count = 0;
        return NRF_ERROR_NOT_FOUND;
    }
    p_curr_addr++;

    // Read number of elements
    *p_word_count = (uint8_t)(*(p_curr_addr));
    p_curr_addr++;

    // Read data
    byte_count = (*p_word_count) * sizeof(uint32_t);
    memcpy(p_out_array, p_curr_addr, byte_count);

    // Check CRC
    calc_crc = ble_flash_crc16_compute((uint8_t *)p_out_array,
                                       (*p_word_count) * sizeof(uint32_t),
                                       NULL);
    calc_header = BLE_FLASH_MAGIC_NUMBER | (uint32_t)calc_crc;

    if (calc_header != flash_header)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    return NRF_SUCCESS;
}


uint32_t ble_flash_page_addr(uint8_t page_num, uint32_t ** pp_page_addr)
{
    *pp_page_addr = (uint32_t *)(BLE_FLASH_PAGE_SIZE * page_num);
    return NRF_SUCCESS;
}


void ble_flash_on_radio_active_evt(bool radio_active)
{
    m_radio_active = radio_active;
}
