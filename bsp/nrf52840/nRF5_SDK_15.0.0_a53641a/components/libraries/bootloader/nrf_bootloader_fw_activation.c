/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#include "nrf_bootloader_fw_activation.h"
#include "nrf_dfu_settings.h"
#include "nrf_dfu_mbr.h"
#include "nrf_bootloader_info.h"
#include "crc32.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_dfu_utils.h"
#include "nrf_bootloader_wdt.h"


static volatile bool m_flash_write_done;


/**
 * @brief Function for copying image. Image is copied in chunks. Frequency of storing progress
 *        in flash is configured by input parameter.
 *
 * @param[in] dst_addr             Destination address. Must be page aligned.
 * @param[in] src_addr             Source address. Must be higher value than dst_addr.
 * @param[in] size                 Image size.
 * @param[in] progress_update_step Number of copied pages that triggers saving progress to non-volatile memory.
 *                                 Note that step can be decreased if there is a risk of corruption caused by source
 *                                 and destination overlapping.
 *
 * @return NRF_SUCCESS or error code in case of failure.
 */
static uint32_t image_copy(uint32_t dst_addr,
                           uint32_t src_addr,
                           uint32_t size,
                           uint32_t progress_update_step)
{
    if (src_addr == dst_addr)
    {
        NRF_LOG_DEBUG("No copy needed src_addr: 0x%x, dst_addr: 0x%x", src_addr, dst_addr);
        return NRF_SUCCESS;
    }

    ASSERT(src_addr >= dst_addr);
    ASSERT(progress_update_step > 0);
    ASSERT((dst_addr % CODE_PAGE_SIZE) == 0);

    uint32_t max_safe_progress_upd_step = (src_addr - dst_addr)/CODE_PAGE_SIZE;
    ASSERT(max_safe_progress_upd_step > 0);

    uint32_t ret_val = NRF_SUCCESS;
    uint32_t pages_left = CEIL_DIV(size, CODE_PAGE_SIZE);

    //Firmware copying is time consuming operation thus watchdog handling is started
    nrf_bootloader_wdt_init();

    progress_update_step = MIN(progress_update_step, max_safe_progress_upd_step);

    while (size > 0)
    {
        uint32_t pages;
        uint32_t bytes;
        if (pages_left <= progress_update_step)
        {
            pages = pages_left;
            bytes = size;
        }
        else
        {
            pages = progress_update_step;
            bytes = progress_update_step * CODE_PAGE_SIZE;
        }
        // Erase the target pages
        ret_val = nrf_dfu_flash_erase(dst_addr, pages, NULL);
        if (ret_val != NRF_SUCCESS)
        {
            return ret_val;
        }

        // Flash one page
        NRF_LOG_DEBUG("Copying 0x%x to 0x%x, size: 0x%x", src_addr, dst_addr, bytes);
        ret_val = nrf_dfu_flash_store(dst_addr,
                                      (uint32_t *)src_addr,
                                      ALIGN_NUM(sizeof(uint32_t), bytes),
                                      NULL);
        if (ret_val != NRF_SUCCESS)
        {
            return ret_val;
        }

        pages_left  -= pages;
        size        -= bytes;
        dst_addr    += bytes;
        src_addr    += bytes;
        s_dfu_settings.write_offset += bytes;

        //store progress in flash on every successful chunk write
        ret_val = nrf_dfu_settings_write(NULL);
        if (ret_val != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Failed to write image copying progress to settings page.");
            return ret_val;
        }
    }

    return ret_val;
}

/** @brief Function to continue application update.
 *
 * @details This function will be called after reset if there is a valid application in Bank1
 *          required to be copied down to Bank 0.
 *
 * @return NRF_SUCCESS if continuation was successful, NRF_ERROR_INTERNAL if new firmware does not
 *         contain softdevice or other error coming from modules used by this function.
 */
static uint32_t app_activate(void)
{
    // This function is only in use when new app is present in Bank 1
    uint32_t const image_size  = s_dfu_settings.bank_1.image_size;

    uint32_t src_addr    = s_dfu_settings.progress.update_start_address;
    uint32_t ret_val     = NRF_SUCCESS;
    uint32_t target_addr = nrf_dfu_bank0_start_addr() + s_dfu_settings.write_offset;
    uint32_t length_left = (image_size - s_dfu_settings.write_offset);
    uint32_t crc;

    NRF_LOG_DEBUG("Enter nrf_dfu_app_continue");

    src_addr += s_dfu_settings.write_offset;

    if (src_addr == target_addr)
    {
        length_left = 0;
    }

    ret_val = image_copy(target_addr, src_addr, length_left, NRF_BL_FW_COPY_PROGRESS_STORE_STEP);
    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed to copy firmware.");
        return ret_val;
    }

    // Check the CRC of the copied data. Enable if so.
    crc = crc32_compute((uint8_t*)nrf_dfu_bank0_start_addr(), image_size, NULL);

    if (crc == s_dfu_settings.bank_1.image_crc)
    {
        NRF_LOG_DEBUG("Setting app as valid");
        s_dfu_settings.bank_0.bank_code = NRF_DFU_BANK_VALID_APP;
        s_dfu_settings.bank_0.image_crc = crc;
        s_dfu_settings.bank_0.image_size = image_size;
    }
    else
    {
        NRF_LOG_ERROR("CRC computation failed for copied app: "
                      "src crc: 0x%08x, res crc: 0x%08x",
                      s_dfu_settings.bank_1.image_crc,
                      crc);
    }

    return ret_val;
}


/** @brief Function to execute the continuation of a SoftDevice update.
 *
 * @return NRF_SUCCESS if continuation was successful, NRF_ERROR_INTERNAL if new firmware does not
 *         contain softdevice or other error coming from modules used by this function.
 */
static uint32_t sd_activate(void)
{
    uint32_t   ret_val      = NRF_SUCCESS;
    uint32_t   target_addr  = nrf_dfu_softdevice_start_address() + s_dfu_settings.write_offset;
    uint32_t   src_addr     = s_dfu_settings.progress.update_start_address;
    uint32_t   sd_size      = s_dfu_settings.sd_size;
    uint32_t   length_left  = ALIGN_TO_PAGE(sd_size - s_dfu_settings.write_offset);

    NRF_LOG_DEBUG("Enter nrf_bootloader_dfu_sd_continue");

    if (SD_MAGIC_NUMBER_GET(src_addr) != SD_MAGIC_NUMBER)
    {
        NRF_LOG_ERROR("Source address does not contain a valid SoftDevice.")
        return NRF_ERROR_INTERNAL;
    }

    // This can be a continuation due to a power failure
    src_addr += s_dfu_settings.write_offset;

    if (s_dfu_settings.write_offset == sd_size)
    {
        NRF_LOG_DEBUG("SD already copied");
        return NRF_SUCCESS;
    }

    if (s_dfu_settings.write_offset == 0)
    {
        NRF_LOG_DEBUG("Updating SD. Old SD ver: %d, New ver: %d",
            SD_VERSION_GET(MBR_SIZE) / 1000000, SD_VERSION_GET(src_addr) / 1000000);
    }

    ret_val = image_copy(target_addr, src_addr, length_left, NRF_BL_FW_COPY_PROGRESS_STORE_STEP);
    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed to copy firmware.");
        return ret_val;
    }

    ret_val = nrf_dfu_settings_write(NULL);

    return ret_val;
}


/** @brief Function to continue bootloader update.
 *
 * @details     This function will be called after reset if there is a valid bootloader in Bank 0 or Bank 1
 *              required to be relocated and activated through MBR commands.
 *
 * @return This function will not return if the bootloader is copied successfully.
 *         After the copy is verified, the device will reset and start the new bootloader.
 *
 * @retval NRF_SUCCESS Continuation was successful.
 * @retval NRF_ERROR_INVALID_LENGTH Invalid length of flash operation.
 * @retval NRF_ERROR_NO_MEM If no parameter page is provided (see sds for more info).
 * @retval NRF_ERROR_INVALID_PARAM If an invalid command is given.
 * @retval NRF_ERROR_INTERNAL Internal error that should not happen.
 * @retval NRF_ERROR_FORBIDDEN If NRF_UICR->BOOTADDR is not set.
 */
static uint32_t bl_activate(void)
{
    uint32_t         ret_val  = NRF_ERROR_INVALID_DATA;
    nrf_dfu_bank_t * p_bank   = &s_dfu_settings.bank_1;
    uint32_t         len      = p_bank->image_size;
    uint32_t         src_addr = s_dfu_settings.progress.update_start_address;

    if (p_bank->bank_code == NRF_DFU_BANK_VALID_SD_BL)
    {
        src_addr += s_dfu_settings.sd_size;
        len      -= s_dfu_settings.sd_size;
    }

    NRF_LOG_DEBUG("Verifying BL: Addr: 0x%08x, Src: 0x%08x, Len: 0x%08x", BOOTLOADER_START_ADDR, src_addr, len);

    // This code is a configurable workaround for updating SD+BL from SDK 12.x.y - 14.1.0
    // SoftDevice size increase would lead to unaligned source address when comparing new BL in SD+BL updates.
    // This workaround is not required once BL is successfully installed with a version that is compiled SDK 14.1.0
#if defined(NRF52832_XXAA) && defined(BLE_STACK_SUPPORT_REQD)
    if ((p_bank->bank_code == NRF_DFU_BANK_VALID_SD_BL) &&
        (memcmp((void *)BOOTLOADER_START_ADDR, (void *)(src_addr - 0x4000), len) == 0))
    {
        ret_val = NRF_SUCCESS;
    }
#endif // defined(NRF52832_XXAA)

    // Check if the BL has already been copied.
    if ((ret_val != NRF_SUCCESS) &&
        (memcmp((void *)BOOTLOADER_START_ADDR, (void *)src_addr, len) == 0))
    {
        ret_val =  NRF_SUCCESS;
    }

    // If the bootloader is the same as the banked version, the copy is finished
    if (ret_val == NRF_SUCCESS)
    {
        NRF_LOG_DEBUG("No bootloader copy needed, bootloader update complete.");
    }
    else
    {
        NRF_LOG_DEBUG("Copying bootloader: Src: 0x%08x, Len: 0x%08x", src_addr, len);
        NRF_LOG_FLUSH();

        nrf_bootloader_wdt_feed();

        // Bootloader is different than the banked version. Continue copy
        // Note that if the SD and BL was combined, then the split point between them is in s_dfu_settings.sd_size
        // On success this function won't return.
        ret_val = nrf_dfu_mbr_copy_bl((uint32_t*)src_addr, len);
        if (ret_val != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Request to copy BL failed");
        }
    }

    return ret_val;
}


/** @brief Function to continue combined bootloader and SoftDevice update.
 *
 * @details     This function will be called after reset if there is a valid bootloader and SoftDevice in Bank 0 or Bank 1
 *              required to be relocated and activated through MBR commands.
 *
 * @retval NRF_SUCCESS Continuation was successful.
 * @retval NRF_ERROR_INVALID_LENGTH Invalid length.
 * @retval NRF_ERROR_NO_MEM If UICR.NRFFW[1] is not set (i.e. is 0xFFFFFFFF).
 * @retval NRF_ERROR_INVALID_PARAM If an invalid command is given.
 * @retval NRF_ERROR_INTERNAL Indicates that the contents of the memory blocks where not verified correctly after copying.
 * @retval NRF_ERROR_NULL If the content of the memory blocks differs after copying.
 * @retval NRF_ERROR_FORBIDDEN If NRF_UICR->BOOTADDR is not set.
 */
static uint32_t sd_bl_activate()
{
    uint32_t ret_val = NRF_SUCCESS;

    NRF_LOG_DEBUG("Enter nrf_dfu_sd_bl_continue");

    ret_val = sd_activate();
    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("SD+BL: SD copy failed");
        return ret_val;
    }

    ret_val = bl_activate();
    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("SD+BL: BL copy failed");
        return ret_val;
    }

    return ret_val;
}


static void flash_write_callback(void * p_context)
{
    UNUSED_PARAMETER(p_context);
    m_flash_write_done = true;
}


nrf_bootloader_fw_activation_result_t nrf_bootloader_fw_activate(void)
{
    nrf_bootloader_fw_activation_result_t result;
    uint32_t                              ret_val   = NRF_SUCCESS;
    nrf_dfu_bank_t                      * p_bank    = &s_dfu_settings.bank_1;
    bool                                  sd_update = false;


    NRF_LOG_DEBUG("Enter nrf_bootloader_fw_activate");

    switch (p_bank->bank_code)
    {
       case NRF_DFU_BANK_VALID_APP:
            NRF_LOG_DEBUG("Valid App");
            ret_val = app_activate();
            break;
       case NRF_DFU_BANK_VALID_SD:
            NRF_LOG_DEBUG("Valid SD");
            ret_val = sd_activate();
            sd_update = true;
            break;
        case NRF_DFU_BANK_VALID_BL:
            NRF_LOG_DEBUG("Valid BL");
            ret_val = bl_activate();
            break;
        case NRF_DFU_BANK_VALID_SD_BL:
            NRF_LOG_DEBUG("Valid SD + BL");
            ret_val = sd_bl_activate();
            sd_update = true;
            break;
        case NRF_DFU_BANK_INVALID:
        default:
            NRF_LOG_INFO("No firmware to activate.");
            return ACTIVATION_NONE;
    }

    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Activation failed with error %d (bank code: 0x%x)", ret_val, p_bank->bank_code);
        result = ACTIVATION_ERROR;
    }

    // Invalidate bank, marking completion.
    nrf_dfu_bank_invalidate(p_bank);

    m_flash_write_done = false;
    ret_val = nrf_dfu_settings_write(flash_write_callback);
    ASSERT(m_flash_write_done);

    /* At this point flash module is performing blocking operation. It is expected that operation is already performed. */
    if (ret_val == NRF_SUCCESS)
    {
        result = ACTIVATION_SUCCESS;
        if (sd_update && nrf_dfu_app_is_valid(true))
        {
            //If SD was updated and application is valid we want to stay in DFU to receive application.
            NRF_LOG_DEBUG("A SoftDevice has just been activated. It's likely that an application will come immediately");
            result = ACTIVATION_SUCCESS_EXPECT_ADDITIONAL_UPDATE;
        }
    }
    else
    {
        NRF_LOG_ERROR("Could not write settings.");
        result = ACTIVATION_ERROR;
    }

    return result;
}

