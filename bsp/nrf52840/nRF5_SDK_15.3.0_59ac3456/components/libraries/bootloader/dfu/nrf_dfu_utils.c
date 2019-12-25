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
#include "nrf_dfu_utils.h"

#include "nrf_dfu_settings.h"
#include "nrf_bootloader_info.h"
#include "crc32.h"
#include "nrf_log.h"
#include "nrf_dfu_validation.h"

void nrf_dfu_bank_invalidate(nrf_dfu_bank_t * const p_bank)
{
    // Set the bank-code to invalid, and reset size/CRC
    memset(p_bank, 0, sizeof(nrf_dfu_bank_t));

    // Reset write pointer after completed operation
    s_dfu_settings.write_offset = 0;
}


#if !defined(BLE_STACK_SUPPORT_REQD) && !defined(ANT_STACK_SUPPORT_REQD)
void nrf_dfu_softdevice_invalidate(void)
{
    static const uint32_t all_zero = 0UL;

    if (SD_PRESENT && !NRF_DFU_IN_APP)
    {
        ret_code_t err_code = nrf_dfu_flash_store(SD_MAGIC_NUMBER_ABS_OFFSET_GET(MBR_SIZE), &all_zero, 4, NULL);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Could not invalidate SoftDevice.")
        }
        else
        {
            // If there is an app it must be invalidated since its start address can no longer be resolved.
            if (s_dfu_settings.bank_0.bank_code == NRF_DFU_BANK_VALID_APP)
            {
                s_dfu_settings.bank_0.bank_code  = NRF_DFU_BANK_INVALID;
            }
            // Since the start of bank 0 has now implicitly been moved to the start
            // of the invalidated SoftDevice, its image size must be increased by the
            // same amount so the start of bank 1 will be correctly calculated.
            s_dfu_settings.bank_0.image_size += SD_SIZE_GET(MBR_SIZE) - MBR_SIZE;
        }
    }
}
#endif


uint32_t nrf_dfu_bank0_start_addr(void)
{
    if (SD_PRESENT)
    {
        return ALIGN_TO_PAGE(SD_SIZE_GET(MBR_SIZE));
    }
    else
    {
        return MBR_SIZE;
    }
}


uint32_t nrf_dfu_bank1_start_addr(void)
{
    uint32_t bank0_addr = nrf_dfu_bank0_start_addr();
    return ALIGN_TO_PAGE(bank0_addr + s_dfu_settings.bank_0.image_size);
}


uint32_t nrf_dfu_app_start_address(void)
{
    return nrf_dfu_bank0_start_addr();
}


uint32_t nrf_dfu_softdevice_start_address(void)
{
    return MBR_SIZE;
}


uint32_t nrf_dfu_cache_prepare(const uint32_t required_size, bool single_bank, bool keep_app, bool keep_softdevice)
{
    ret_code_t err_code;
    bool       cache_too_small;
    enum
    {
        INITIAL_DELETE_APP            = 0,
        APP_DELETED_DELETE_SOFTDEVICE = 1,
        SOFTDEVICE_DELETED            = 2
    } pass;

    NRF_LOG_DEBUG("Enter nrf_dfu_cache_prepare()");
    NRF_LOG_DEBUG("required_size: 0x%x.", required_size);
    NRF_LOG_DEBUG("single_bank: %s.",     single_bank     ? "true" : "false");
    NRF_LOG_DEBUG("keep_app: %s.",        keep_app        ? "true" : "false");
    NRF_LOG_DEBUG("keep_softdevice: %s.", keep_softdevice ? "true" : "false");
    NRF_LOG_DEBUG("SD_PRESENT: %s.",      SD_PRESENT      ? "true" : "false");
    NRF_LOG_DEBUG("Bank contents:");
    NRF_LOG_DEBUG("Bank 0 code: 0x%02x: Size: 0x%x", s_dfu_settings.bank_0.bank_code, s_dfu_settings.bank_0.image_size);
    NRF_LOG_DEBUG("Bank 1 code: 0x%02x: Size: 0x%x", s_dfu_settings.bank_1.bank_code, s_dfu_settings.bank_1.image_size);

    // Pass 0 deletes the app if necessary or requested, and if so, proceeds to pass 1.
    // Pass 1 deletes the SoftDevice if necessary or requested, and if so, proceeds to pass 2.
    // Pass 2 does a last size check.
    for (pass = INITIAL_DELETE_APP; pass <= SOFTDEVICE_DELETED; pass++)
    {
        uint32_t       cache_address;
        const uint32_t bootloader_start_addr = BOOTLOADER_START_ADDR; // Assign to a variable to prevent warning in Keil 4.
        bool           keep_firmware = true;
        bool           delete_more;

        switch (pass)
        {
            case INITIAL_DELETE_APP:
                cache_address = nrf_dfu_bank1_start_addr();

                // If there is no app, keep_app should be assumed false, so we can free up more space.
                keep_firmware = keep_app && (s_dfu_settings.bank_0.bank_code == NRF_DFU_BANK_VALID_APP);
                break;

            case APP_DELETED_DELETE_SOFTDEVICE:
                cache_address = nrf_dfu_bank0_start_addr();

                // If there is no SoftDevice, keep_SoftDevice should be assumed true, because there is
                // no point to continuing since the SoftDevice is the last firmware that can be deleted.
                keep_firmware = keep_softdevice || !SD_PRESENT;
                break;

            case SOFTDEVICE_DELETED:
                cache_address = nrf_dfu_softdevice_start_address();
                break;

            default:
                ASSERT(false);
                cache_address = 0;
                break;
        }

        ASSERT(cache_address <= DFU_REGION_END(bootloader_start_addr));
        cache_too_small = required_size > (DFU_REGION_END(bootloader_start_addr) - cache_address);
        delete_more     = cache_too_small || single_bank; // Delete app or SoftDevice only if we need more room, or if single bank is requested.

        NRF_LOG_DEBUG("pass: %d.", pass);
        NRF_LOG_DEBUG("cache_address: 0x%x.", cache_address);
        NRF_LOG_DEBUG("cache_too_small: %s.", cache_too_small ? "true" : "false");
        NRF_LOG_DEBUG("keep_firmware: %s.",   keep_firmware   ? "true" : "false");
        NRF_LOG_DEBUG("delete_more: %s.",     delete_more     ? "true" : "false");

        if (!delete_more || keep_firmware || (pass >= SOFTDEVICE_DELETED))
        {
            // Stop, done.
            break;
        }
    }

    if (cache_too_small)
    {
        NRF_LOG_WARNING("Aborting. Cannot fit new firmware on device");
        err_code = NRF_ERROR_NO_MEM;
    }
    else
    {
        // Room was found. Make the necessary preparations for receiving update.

#if !defined(BLE_STACK_SUPPORT_REQD) && !defined(ANT_STACK_SUPPORT_REQD)
        if (pass >= SOFTDEVICE_DELETED)
        {
            NRF_LOG_DEBUG("Invalidating SoftDevice.");
            nrf_dfu_softdevice_invalidate();
        }
#endif
        if (pass >= APP_DELETED_DELETE_SOFTDEVICE)
        {
            NRF_LOG_DEBUG("Invalidating app.");
            nrf_dfu_bank_invalidate(&s_dfu_settings.bank_0);
        }

        err_code = NRF_SUCCESS;
    }

    return err_code;
}
