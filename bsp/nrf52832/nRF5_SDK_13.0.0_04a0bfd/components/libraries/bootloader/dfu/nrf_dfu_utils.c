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
#include "nrf_dfu_utils.h"

#include <string.h>
#include "nrf_dfu_settings.h"
#include "nrf_dfu_mbr.h"
#include "nrf_bootloader_app_start.h"
#include "nrf_bootloader_info.h"
#include "crc32.h"
#include "nrf_log.h"
#include "app_timer.h"


static app_timer_t nrf_dfu_utils_reset_delay_timer_data = { {0} };
const app_timer_id_t nrf_dfu_utils_reset_delay_timer = &nrf_dfu_utils_reset_delay_timer_data;

/**
 * Round up val to the next page boundry
 */
static uint32_t align_to_page(uint32_t val, uint32_t page_size)
{
    return ((val + page_size - 1 ) &~ (page_size - 1));
}


static void nrf_dfu_invalidate_bank(nrf_dfu_bank_t * p_bank)
{
    // Set the bank-code to invalid, and reset size/CRC
    memset(p_bank, 0, sizeof(nrf_dfu_bank_t));

    // Reset write pointer after completed operation
    s_dfu_settings.write_offset = 0;

    // Reset SD size
    s_dfu_settings.sd_size = 0;

    // Promote dual bank layout
    s_dfu_settings.bank_layout = NRF_DFU_BANK_LAYOUT_DUAL;

    // Signify that bank 0 is empty
    s_dfu_settings.bank_current = NRF_DFU_CURRENT_BANK_0;
}


/** @brief Function to continue App update
 *
 * @details This function will be called after reset if there is a valid application in Bank1
 *          required to be copied down to bank0.
 *
 * @param[in]       src_addr            Source address of the application to copy from Bank1 to Bank0.
 *
 * @retval  NRF_SUCCESS                 Continuation was successful.
 * @retval  NRF_ERROR_NULL              Invalid data during compare.
 * @retval  FS_ERR_UNALIGNED_ADDR       A call to fstorage was not aligned to a page boundary or the address was not word aliged.
 * @retval  FS_ERR_INVALID_ADDR         The destination of a call to fstorage does not point to
 *                                      the start of a flash page or the operation would
 *                                      go beyond the flash memory boundary.
 * @retval  FS_ERR_NOT_INITIALIZED      The fstorage module is not initialized.
 * @retval  FS_ERR_INVALID_CFG          The initialization of the fstorage module is invalid.
 * @retval  FS_ERR_NULL_ARG             A call to fstorage had an invalid NULL argument.
 * @retval  FS_ERR_INVALID_ARG          A call to fstorage had invalid arguments.
 * @retval  FS_ERR_QUEUE_FULL           If the internal operation queue of the fstorage module is full.
 * @retval  FS_ERR_FAILURE_SINCE_LAST   If an error occurred in another transaction and fstorage cannot continue before
 *                                      the event has been dealt with.
 */
static uint32_t nrf_dfu_app_continue(uint32_t               src_addr)
{
    // This function only in use when new app is present in bank 1
    uint32_t const image_size  = s_dfu_settings.bank_1.image_size;
    uint32_t const split_size  = CODE_PAGE_SIZE; // Arbitrary number that must be page aligned

    uint32_t ret_val            = NRF_SUCCESS;
    uint32_t target_addr        = MAIN_APPLICATION_START_ADDR + s_dfu_settings.write_offset;
    uint32_t length_left        = (image_size - s_dfu_settings.write_offset);
    uint32_t cur_len;
    uint32_t crc;

    NRF_LOG_DEBUG("Enter nrf_dfu_app_continue\r\n");

    // Copy the application down safely
    do
    {
        cur_len = (length_left > split_size) ? split_size : length_left;

        // Erase the target page
        ret_val = nrf_dfu_flash_erase((uint32_t*) target_addr, split_size / CODE_PAGE_SIZE, NULL);
        if (ret_val != NRF_SUCCESS)
        {
            return ret_val;
        }

        // Flash one page
        ret_val = nrf_dfu_flash_store((uint32_t*)target_addr, (uint32_t*)src_addr, cur_len, NULL);
        if (ret_val != NRF_SUCCESS)
        {
            return ret_val;
        }

        ret_val = nrf_dfu_mbr_compare((uint32_t*)target_addr, (uint32_t*)src_addr, cur_len);
        if (ret_val != NRF_SUCCESS)
        {
            // We will not retry the copy
            NRF_LOG_ERROR("Invalid data during compare: target: 0x%08x, src: 0x%08x\r\n", target_addr, src_addr);
            return ret_val;
        }

        // Erase the head (to handle growing bank 0)
        ret_val = nrf_dfu_flash_erase((uint32_t*) src_addr, split_size / CODE_PAGE_SIZE, NULL);
        if (ret_val != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("App update: Failure erasing page at addr: 0x%08x\r\n", src_addr);
            return ret_val;
        }

        s_dfu_settings.write_offset += cur_len;
        ret_val = nrf_dfu_settings_write(NULL);

        target_addr += cur_len;
        src_addr += cur_len;

        length_left -= cur_len;
    }
    while(length_left > 0);

    // Check the crc of the copied data. Enable if so.
    crc = crc32_compute((uint8_t*)MAIN_APPLICATION_START_ADDR, image_size, NULL);

    if (crc == s_dfu_settings.bank_1.image_crc)
    {
        NRF_LOG_DEBUG("Setting app as valid\r\n");
        s_dfu_settings.bank_0.bank_code = NRF_DFU_BANK_VALID_APP;
        s_dfu_settings.bank_0.image_crc = crc;
        s_dfu_settings.bank_0.image_size = image_size;
    }
    else
    {
        NRF_LOG_ERROR("CRC computation failed for copied app: "
                      "src crc: 0x%08x, res crc: 0x%08x\r\n",
                      s_dfu_settings.bank_1.image_crc,
                      crc);
    }

    nrf_dfu_invalidate_bank(&s_dfu_settings.bank_1);
    ret_val = nrf_dfu_settings_write(NULL);

    return ret_val;
}

/** @brief Function to execute the continuation of a SoftDevice update.
 *
 * @param[in]       src_addr            Source address of the SoftDevice to copy from.
 * @param[in]       p_bank              Pointer to the bank where the SoftDevice resides.
 *
 * @retval NRF_SUCCESS Continuation was successful.
 * @retval NRF_ERROR_INVALID_LENGTH Invalid len
 * @retval NRF_ERROR_NO_MEM if UICR.NRFFW[1] is not set (i.e. is 0xFFFFFFFF).
 * @retval NRF_ERROR_INVALID_PARAM if an invalid command is given.
 * @retval NRF_ERROR_INTERNAL indicates that the contents of the memory blocks where not verified correctly after copying.
 * @retval NRF_ERROR_NULL If the content of the memory blocks differs after copying.
 */
#if defined(SOFTDEVICE_PRESENT)
static uint32_t nrf_dfu_sd_continue_impl(uint32_t             src_addr,
                                         nrf_dfu_bank_t     * p_bank)
{
    uint32_t   ret_val      = NRF_SUCCESS;
    uint32_t   target_addr  = SOFTDEVICE_REGION_START + s_dfu_settings.write_offset;
    uint32_t   length_left  = align_to_page(s_dfu_settings.sd_size - s_dfu_settings.write_offset, CODE_PAGE_SIZE);
    uint32_t   split_size   = align_to_page(length_left / 4, CODE_PAGE_SIZE);

    NRF_LOG_DEBUG("Enter nrf_bootloader_dfu_sd_continue\r\n");

    // This can be a continuation due to a power failure
    src_addr += s_dfu_settings.write_offset;

    if (s_dfu_settings.sd_size != 0 && s_dfu_settings.write_offset == s_dfu_settings.sd_size)
    {
        NRF_LOG_DEBUG("SD already copied\r\n");
        return NRF_SUCCESS;
    }

    if (s_dfu_settings.write_offset == 0)
    {
        NRF_LOG_DEBUG("Updating SD. Old SD ver: %d, New ver: %d\r\n", SD_VERSION_GET(MBR_SIZE) / 100000, SD_VERSION_GET(src_addr) / 100000);
    }

    do
    {
        // If less than split size remain, reduce split size to avoid overwriting bank 0.
        if (split_size > length_left)
        {
            split_size = align_to_page(length_left, CODE_PAGE_SIZE);
        }

        NRF_LOG_DEBUG("Copying [0x%08x-0x%08x] to [0x%08x-0x%08x]: Len: 0x%08x\r\n", src_addr, src_addr + split_size, target_addr, target_addr + split_size, split_size);

        // Copy a chunk of the SD. Size in words
        ret_val = nrf_dfu_mbr_copy_sd((uint32_t*)target_addr, (uint32_t*)src_addr, split_size);
        if (ret_val != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Failed to copy SD: target: 0x%08x, src: 0x%08x, len: 0x%08x\r\n", target_addr, src_addr, split_size);
            return ret_val;
        }

        NRF_LOG_DEBUG("Finished copying [0x%08x-0x%08x] to [0x%08x-0x%08x]: Len: 0x%08x\r\n", src_addr, src_addr + split_size, target_addr, target_addr + split_size, split_size);

        // Validate copy. Size in words
        ret_val = nrf_dfu_mbr_compare((uint32_t*)target_addr, (uint32_t*)src_addr, split_size);
        if (ret_val != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Failed to Compare SD: target: 0x%08x, src: 0x%08x, len: 0x%08x\r\n", target_addr, src_addr, split_size);
            return ret_val;
        }

        NRF_LOG_DEBUG("Validated 0x%08x-0x%08x to 0x%08x-0x%08x: Size: 0x%08x\r\n", src_addr, src_addr + split_size, target_addr, target_addr + split_size, split_size);

        target_addr += split_size;
        src_addr += split_size;

        if (split_size > length_left)
        {
            length_left = 0;
        }
        else
        {
            length_left -= split_size;
        }

        NRF_LOG_DEBUG("Finished with the SD update.\r\n");

        // Save the updated point of writes in case of power loss
        s_dfu_settings.write_offset = s_dfu_settings.sd_size - length_left;
        ret_val = nrf_dfu_settings_write(NULL);
    }
    while (length_left > 0);

    return ret_val;
}

/**
 * @brief Flash storage callback used to reset the device if no new DFU is initiated within the timers expiration.
 *
 * After the completion of a SD, BL or SD + BL update, the controller might want to update the
 * application as well. Because of this, the DFU target will stay in bootloader mode for some
 * time after completion. However, if no such update is received the device should reset to
 * to look for a valid app and resume regular operation.
 */
static void reset_device_callback( fs_evt_t const * const evt, fs_ret_t result )
{
    // Verify that the current application is valid.
    if (nrf_dfu_app_is_valid())
    {
        // Start a timer which resets the device on expiration.
        NRF_LOG_DEBUG("Starting reset delay timer\r\n");
        uint32_t err_code = app_timer_start(nrf_dfu_utils_reset_delay_timer, APP_TIMER_TICKS(RESET_DELAY_LENGTH_MS), NULL);
        APP_ERROR_CHECK(err_code);
    }
}


/** @brief Function to continue SoftDevice update
 *
 * @details     This function will be called after reset if there is a valid SoftDevice in Bank0 or Bank1
 *          required to be relocated and activated through MBR commands.
 *
 * @param[in]       src_addr            Source address of the SoftDevice to copy from.
 * @param[in]       p_bank              Pointer to the bank where the SoftDevice resides.
 *
 * @retval NRF_SUCCESS Continuation was successful.
 * @retval NRF_ERROR_INVALID_LENGTH Invalid len
 * @retval NRF_ERROR_NO_MEM if UICR.NRFFW[1] is not set (i.e. is 0xFFFFFFFF).
 * @retval NRF_ERROR_INVALID_PARAM if an invalid command is given.
 * @retval NRF_ERROR_INTERNAL indicates that the contents of the memory blocks where not verified correctly after copying.
 * @retval NRF_ERROR_NULL If the content of the memory blocks differs after copying.
 */
static uint32_t nrf_dfu_sd_continue(uint32_t             src_addr,
                                    nrf_dfu_bank_t     * p_bank)
{
    uint32_t ret_val;

    ret_val = nrf_dfu_sd_continue_impl(src_addr, p_bank);
    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("SD update continuation failed\r\n");
        return ret_val;
    }

    nrf_dfu_invalidate_bank(p_bank);

    // Upon successful completion, the callback function will be called and reset the device. If a valid app i present, it will launch.
    NRF_LOG_DEBUG("Writing settings and reseting device.\r\n");
    ret_val = nrf_dfu_settings_write(reset_device_callback);

    return ret_val;
}
#endif

/** @brief Function to continue Bootloader update
 *
 * @details     This function will be called after reset if there is a valid Bootloader in Bank0 or Bank1
 *              required to be relocated and activated through MBR commands.
 *
 * @param[in]       src_addr            Source address of the BL to copy from.
 * @param[in]       p_bank              Pointer to the bank where the SoftDevice resides.
 *
 * @return This fucntion will not return if the bootloader is copied succesfully.
 *         After the copy is verified the device will reset and start the new bootloader.
 *
 * @retval NRF_SUCCESS Continuation was successful.
 * @retval NRF_ERROR_INVALID_LENGTH Invalid length of flash operation.
 * @retval NRF_ERROR_NO_MEM if no parameter page is provided (see sds for more info).
 * @retval NRF_ERROR_INVALID_PARAM if an invalid command is given.
 * @retval NRF_ERROR_INTERNAL internal error that should not happen.
 * @retval NRF_ERROR_FORBIDDEN if NRF_UICR->BOOTADDR is not set.
 */
static uint32_t nrf_dfu_bl_continue(uint32_t src_addr, nrf_dfu_bank_t * p_bank)
{
    uint32_t        ret_val     = NRF_SUCCESS;
    uint32_t const  len         = (p_bank->image_size - s_dfu_settings.sd_size);

    // if the update is a combination of BL + SD, offset with SD size to get BL start address
    src_addr += s_dfu_settings.sd_size;

    NRF_LOG_DEBUG("Verifying BL: Addr: 0x%08x, Src: 0x%08x, Len: 0x%08x\r\n", MAIN_APPLICATION_START_ADDR, src_addr, len);


    // If the bootloader is the same as the banked version, the copy is finished
    ret_val = nrf_dfu_mbr_compare((uint32_t*)BOOTLOADER_START_ADDR, (uint32_t*)src_addr, len);
    if (ret_val == NRF_SUCCESS)
    {
        NRF_LOG_DEBUG("Bootloader was verified\r\n");

        // Invalidate bank, marking completion
        nrf_dfu_invalidate_bank(p_bank);

        // Upon successful completion, the callback function will be called and reset the device. If a valid app i present, it will launch.
        NRF_LOG_DEBUG("Writing settings and reseting device.\r\n");
        ret_val = nrf_dfu_settings_write(reset_device_callback);
    }
    else
    {
        NRF_LOG_DEBUG("Bootloader not verified, copying: Src: 0x%08x, Len: 0x%08x\r\n", src_addr, len);
        // Bootloader is different than the banked version. Continue copy
        // Note that if the SD and BL was combined, then the split point between them is in s_dfu_settings.sd_size
        ret_val = nrf_dfu_mbr_copy_bl((uint32_t*)src_addr, len);
        if(ret_val != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Request to copy BL failed\r\n");
        }
    }

    return ret_val;
}


/** @brief Function to continue combined Bootloader and SoftDevice update
 *
 * @details     This function will be called after reset if there is a valid Bootloader and SoftDevice in Bank0 or Bank1
 *              required to be relocated and activated through MBR commands.
 *
 * @param[in]       src_addr            Source address of the combined Bootloader and SoftDevice to copy from.
 * @param[in]       p_bank              Pointer to the bank where the SoftDevice resides.
 *
 * @retval NRF_SUCCESS Continuation was successful.
 * @retval NRF_ERROR_INVALID_LENGTH Invalid len
 * @retval NRF_ERROR_NO_MEM if UICR.NRFFW[1] is not set (i.e. is 0xFFFFFFFF).
 * @retval NRF_ERROR_INVALID_PARAM if an invalid command is given.
 * @retval NRF_ERROR_INTERNAL indicates that the contents of the memory blocks where not verified correctly after copying.
 * @retval NRF_ERROR_NULL If the content of the memory blocks differs after copying.
 * @retval NRF_ERROR_FORBIDDEN if NRF_UICR->BOOTADDR is not set.
 */
#if defined(SOFTDEVICE_PRESENT)
static uint32_t nrf_dfu_sd_bl_continue(uint32_t src_addr, nrf_dfu_bank_t * p_bank)
{
    uint32_t ret_val = NRF_SUCCESS;

    NRF_LOG_DEBUG("Enter nrf_dfu_sd_bl_continue\r\n");

    ret_val = nrf_dfu_sd_continue_impl(src_addr, p_bank);
    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("SD+BL: SD copy failed\r\n");
        return ret_val;
    }

    ret_val = nrf_dfu_bl_continue(src_addr, p_bank);
    if (ret_val != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("SD+BL: BL copy failed\r\n");
        return ret_val;
    }

    return ret_val;
}
#endif

static uint32_t nrf_dfu_continue_bank(nrf_dfu_bank_t * p_bank, uint32_t src_addr, uint32_t * p_enter_dfu_mode)
{
    uint32_t ret_val = NRF_SUCCESS;

    switch (p_bank->bank_code)
    {
       case NRF_DFU_BANK_VALID_APP:
            NRF_LOG_DEBUG("Valid App\r\n");
            if(s_dfu_settings.bank_current == NRF_DFU_CURRENT_BANK_1)
            {
                // Only continue copying if valid app in bank1
                ret_val = nrf_dfu_app_continue(src_addr);
            }
            break;
#if defined(SOFTDEVICE_PRESENT)
       case NRF_DFU_BANK_VALID_SD:
            NRF_LOG_DEBUG("Valid SD\r\n");
            // There is a valid SD that needs to be copied (or continued)
            ret_val = nrf_dfu_sd_continue(src_addr, p_bank);
            (*p_enter_dfu_mode) = 1;
            break;
#endif

        case NRF_DFU_BANK_VALID_BL:
            NRF_LOG_DEBUG("Valid BL\r\n");
            // There is a valid BL that must be copied (or continued)
            ret_val = nrf_dfu_bl_continue(src_addr, p_bank);
            break;

#if defined(SOFTDEVICE_PRESENT)
        case NRF_DFU_BANK_VALID_SD_BL:
            NRF_LOG_DEBUG("Valid SD + BL\r\n");
            // There is a valid SD + BL that must be copied (or continued)
            ret_val = nrf_dfu_sd_bl_continue(src_addr, p_bank);
            // Set the bank-code to invalid, and reset size/CRC
            (*p_enter_dfu_mode) = 1;
            break;
#endif

        case NRF_DFU_BANK_INVALID:
        default:
            NRF_LOG_ERROR("Single: Invalid bank\r\n");
            break;
    }

    return ret_val;
}

uint32_t nrf_dfu_continue(uint32_t * p_enter_dfu_mode)
{
    uint32_t            ret_val;
    nrf_dfu_bank_t    * p_bank;
    uint32_t            src_addr = CODE_REGION_1_START;

    NRF_LOG_DEBUG("Enter nrf_dfu_continue\r\n");

    if (s_dfu_settings.bank_layout == NRF_DFU_BANK_LAYOUT_SINGLE )
    {
        p_bank = &s_dfu_settings.bank_0;
    }
    else if(s_dfu_settings.bank_current == NRF_DFU_CURRENT_BANK_0)
    {
        p_bank = &s_dfu_settings.bank_0;
    }
    else
    {
        p_bank = &s_dfu_settings.bank_1;
        src_addr += align_to_page(s_dfu_settings.bank_0.image_size, CODE_PAGE_SIZE);
    }

    ret_val = nrf_dfu_continue_bank(p_bank, src_addr, p_enter_dfu_mode);
    return ret_val;
}


bool nrf_dfu_app_is_valid(void)
{
    NRF_LOG_DEBUG("Enter nrf_dfu_app_is_valid\r\n");
    if (s_dfu_settings.bank_0.bank_code != NRF_DFU_BANK_VALID_APP)
    {
       // Bank 0 has no valid app. Nothing to boot
       NRF_LOG_DEBUG("Return false in valid app check\r\n");
       return false;
    }

    // If CRC == 0, this means CRC check is skipped.
    if (s_dfu_settings.bank_0.image_crc != 0)
    {
        uint32_t crc = crc32_compute((uint8_t*) CODE_REGION_1_START,
                                     s_dfu_settings.bank_0.image_size,
                                     NULL);

        if (crc != s_dfu_settings.bank_0.image_crc)
        {
            // CRC does not match with what is stored.
            NRF_LOG_DEBUG("Return false in CRC\r\n");
            return  false;
        }
    }

    NRF_LOG_DEBUG("Return true. App was valid\r\n");
    return true;
}


uint32_t nrf_dfu_find_cache(uint32_t size_req, bool dual_bank_only, uint32_t * p_address)
{
    uint32_t free_size =  DFU_REGION_TOTAL_SIZE - DFU_APP_DATA_RESERVED;
    nrf_dfu_bank_t * p_bank;

    NRF_LOG_DEBUG("Enter nrf_dfu_find_cache\r\n");

    if (p_address == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    
    // Simple check if size requirement can me met
    if(free_size < size_req)
    {
        NRF_LOG_DEBUG("No way to fit the new firmware on device\r\n");
        return NRF_ERROR_NO_MEM;
    }

    NRF_LOG_DEBUG("Bank content\r\n");
    NRF_LOG_DEBUG("Bank type: %d\r\n", s_dfu_settings.bank_layout);
    NRF_LOG_DEBUG("Bank 0 code: 0x%02x: Size: %d\r\n", s_dfu_settings.bank_0.bank_code, s_dfu_settings.bank_0.image_size);
    NRF_LOG_DEBUG("Bank 1 code: 0x%02x: Size: %d\r\n", s_dfu_settings.bank_1.bank_code, s_dfu_settings.bank_1.image_size);

    // Setting bank_0 as candidate
    p_bank = &s_dfu_settings.bank_0;

    // Setting candidate address
    (*p_address) = MAIN_APPLICATION_START_ADDR;

    // Calculate free size
    if (s_dfu_settings.bank_0.bank_code == NRF_DFU_BANK_VALID_APP)
    {
        // Valid app present.

        NRF_LOG_DEBUG("free_size before bank select: %d\r\n", free_size);

        free_size -= align_to_page(p_bank->image_size, CODE_PAGE_SIZE);

        NRF_LOG_DEBUG("free_size: %d, size_req: %d\r\n", free_size, size_req);

        // Check if we can fit the new in the free space or if removal of old app is required.
        if(size_req > free_size)
        {
            // Not enough room in free space (bank_1)
            if ((dual_bank_only))
            {
                NRF_LOG_ERROR("Failure: dual bank restriction\r\n");
                return NRF_ERROR_NO_MEM;
            }

            // Can only support single bank update, clearing old app.
            s_dfu_settings.bank_layout = NRF_DFU_BANK_LAYOUT_SINGLE;
            s_dfu_settings.bank_current = NRF_DFU_CURRENT_BANK_0;
            p_bank = &s_dfu_settings.bank_0;
            NRF_LOG_DEBUG("Enforcing single bank\r\n");
        }
        else
        {
            // Room in bank_1 for update
            // Ensure we are using dual bank layout
            s_dfu_settings.bank_layout = NRF_DFU_BANK_LAYOUT_DUAL;
            s_dfu_settings.bank_current = NRF_DFU_CURRENT_BANK_1;
            p_bank = &s_dfu_settings.bank_1;
            // Set to first free page boundry after previous app
            (*p_address) += align_to_page(s_dfu_settings.bank_0.image_size, CODE_PAGE_SIZE);
            NRF_LOG_DEBUG("Using second bank\r\n");
        }
    }
    else
    {
        // No valid app present. Promoting dual bank.
        s_dfu_settings.bank_layout  = NRF_DFU_BANK_LAYOUT_DUAL;
        s_dfu_settings.bank_current = NRF_DFU_CURRENT_BANK_0;

        p_bank = &s_dfu_settings.bank_0;
        NRF_LOG_DEBUG("No previous, using bank 0\r\n");
    }

    // Set the bank-code to invalid, and reset size/CRC
    memset(p_bank, 0, sizeof(nrf_dfu_bank_t));

    // Store the Firmware size in the bank for continuations
    p_bank->image_size = size_req;
    return NRF_SUCCESS;
}

