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

#include "nrf_dfu_settings.h"
#include <stddef.h>
#include <string.h>
#include "nrf_dfu_flash.h"
#include "nrf_soc.h"
#include "crc32.h"
#include "nrf_nvmc.h"
#include "sdk_config.h"


#define DFU_SETTINGS_VERSION_OFFSET             (offsetof(nrf_dfu_settings_t, settings_version))                         //<! Offset in the settings struct where the settings version is located.
#define DFU_SETTINGS_INIT_COMMAND_OFFSET        (offsetof(nrf_dfu_settings_t, init_command))                             //<! Offset in the settings struct where the InitCommand is located.
#define DFU_SETTINGS_BOOT_VALIDATION_OFFSET     (offsetof(nrf_dfu_settings_t, boot_validation_crc))                      //<! Offset in the settings struct where the boot validation info is located.
#define DFU_SETTINGS_BOOT_VALIDATION_SIZE       ((3 * sizeof(boot_validation_t)) + 4)
#define DFU_SETTINGS_BOND_DATA_OFFSET_V1        (offsetof(nrf_dfu_settings_t, init_command) + INIT_COMMAND_MAX_SIZE_v1)  //<! Offset in the settings struct where the bond data was located in settings version 1.
#define DFU_SETTINGS_ADV_NAME_OFFSET_V1         (offsetof(nrf_dfu_settings_t, init_command) + INIT_COMMAND_MAX_SIZE_v1 + NRF_DFU_PEER_DATA_LEN)  //<! Offset in the settings struct where the bond data was located in settings version 1.

#define NRF_LOG_MODULE_NAME nrf_dfu_settings
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


/**@brief   This variable reserves a page in flash for bootloader settings
 *          to ensure the linker doesn't place any code or variables at this location.
 */
#if defined (__CC_ARM )

    uint8_t m_dfu_settings_buffer[BOOTLOADER_SETTINGS_PAGE_SIZE]
        __attribute__((at(BOOTLOADER_SETTINGS_ADDRESS)))
        __attribute__((used));

#elif defined ( __GNUC__ ) || defined ( __SES_ARM )

    uint8_t m_dfu_settings_buffer[BOOTLOADER_SETTINGS_PAGE_SIZE]
        __attribute__((section(".bootloader_settings_page")))
        __attribute__((used));

#elif defined ( __ICCARM__ )

    __no_init __root uint8_t m_dfu_settings_buffer[BOOTLOADER_SETTINGS_PAGE_SIZE]
        @ BOOTLOADER_SETTINGS_ADDRESS;

#else

    #error Not a valid compiler/linker for m_dfu_settings placement.

#endif // Compiler specific

#if defined(NRF52_SERIES)

/**@brief   This variable reserves a page in flash for MBR parameters
 *          to ensure the linker doesn't place any code or variables at this location.
 */
#if defined ( __CC_ARM )

    uint8_t m_mbr_params_page[NRF_MBR_PARAMS_PAGE_SIZE]
        __attribute__((at(NRF_MBR_PARAMS_PAGE_ADDRESS)))
        __attribute__((used));

#elif defined ( __GNUC__ ) || defined ( __SES_ARM )

    uint8_t m_mbr_params_page[NRF_MBR_PARAMS_PAGE_SIZE]
        __attribute__((section(".mbr_params_page")))
        __attribute__((used));

#elif defined ( __ICCARM__ )

    __no_init uint8_t m_mbr_params_page[NRF_MBR_PARAMS_PAGE_SIZE]
        @ NRF_MBR_PARAMS_PAGE_ADDRESS;

#else

    #error Not a valid compiler/linker for m_mbr_params_page placement.

#endif // Compiler specific

uint8_t * mp_dfu_settings_backup_buffer = &m_mbr_params_page[0];


#ifndef NRF_DFU_IN_APP
#define NRF_DFU_IN_APP 0
#endif

#if !defined(BL_SETTINGS_ACCESS_ONLY) && !NRF_DFU_IN_APP
/**@brief   This variable has the linker write the MBR parameters page address to the
 *          UICR register. This value will be written in the HEX file and thus to the
 *          UICR when the bootloader is flashed into the chip.
 */
#if defined ( __CC_ARM )

    uint32_t const m_uicr_mbr_params_page_address
        __attribute__((at(NRF_UICR_MBR_PARAMS_PAGE_ADDRESS))) = NRF_MBR_PARAMS_PAGE_ADDRESS;

#elif defined ( __GNUC__ ) || defined ( __SES_ARM )

    uint32_t const m_uicr_mbr_params_page_address
        __attribute__ ((section(".uicr_mbr_params_page")))
        __attribute__ ((used)) = NRF_MBR_PARAMS_PAGE_ADDRESS;

#elif defined ( __ICCARM__ )

    __root uint32_t const m_uicr_mbr_params_page_address
        @ NRF_UICR_MBR_PARAMS_PAGE_ADDRESS = NRF_MBR_PARAMS_PAGE_ADDRESS;

#else

    #error Not a valid compiler/linker for m_mbr_params_page placement.

#endif // Compiler specific
#endif // #ifndef BL_SETTINGS_ACCESS_ONLY
#endif // #if defined( NRF52_SERIES )

nrf_dfu_settings_t s_dfu_settings;

static uint32_t settings_crc_get(nrf_dfu_settings_t const * p_settings)
{
    ASSERT(offsetof(nrf_dfu_settings_t, crc) == 0);

    // The crc is calculated from the s_dfu_settings struct, except the crc itself, the init command, bond data, and boot validation.
    return crc32_compute((uint8_t*)(p_settings) + 4, DFU_SETTINGS_INIT_COMMAND_OFFSET - 4, NULL);
}


static bool crc_ok(nrf_dfu_settings_t const * p_settings)
{
    if (p_settings->crc != 0xFFFFFFFF)
    {
        // CRC is set. Content must be valid
        uint32_t crc = settings_crc_get(p_settings);
        if (crc == p_settings->crc)
        {
            return true;
        }
    }
    return false;
}


static uint32_t boot_validation_crc(nrf_dfu_settings_t const * p_settings)
{
    return crc32_compute((const uint8_t *)&p_settings->boot_validation_softdevice,
                          DFU_SETTINGS_BOOT_VALIDATION_SIZE - 4,
                          NULL);
}


static bool boot_validation_crc_ok(nrf_dfu_settings_t const * p_settings)
{
    return (boot_validation_crc(p_settings) == p_settings->boot_validation_crc);
}


static bool settings_crc_ok(void)
{
    nrf_dfu_settings_t const * p_settings = (nrf_dfu_settings_t const *)m_dfu_settings_buffer;
    return crc_ok(p_settings);
}


static bool settings_backup_crc_ok(void)
{
    nrf_dfu_settings_t const * p_settings = (nrf_dfu_settings_t const *)mp_dfu_settings_backup_buffer;
    return crc_ok(p_settings) && ((p_settings->settings_version == 1) || boot_validation_crc_ok(p_settings));
}

#define REGION_COPY_BY_MEMBER(start_member, end_member, p_dst_addr)        \
    memcpy(p_dst_addr                    + offsetof(nrf_dfu_settings_t, start_member), \
           mp_dfu_settings_backup_buffer + offsetof(nrf_dfu_settings_t, start_member), \
           offsetof(nrf_dfu_settings_t, end_member) - offsetof(nrf_dfu_settings_t, start_member))


static void settings_forbidden_parts_copy_from_backup(uint8_t * p_dst_addr)
{
#if NRF_DFU_IN_APP || NRF_BL_DFU_ALLOW_UPDATE_FROM_APP
    REGION_COPY_BY_MEMBER(settings_version, bank_current, p_dst_addr);
    REGION_COPY_BY_MEMBER(bank_0, write_offset, p_dst_addr);
    REGION_COPY_BY_MEMBER(sd_size, progress, p_dst_addr);
    REGION_COPY_BY_MEMBER(boot_validation_crc, peer_data, p_dst_addr);
#else
    REGION_COPY_BY_MEMBER(settings_version, enter_buttonless_dfu, p_dst_addr);
    REGION_COPY_BY_MEMBER(init_command, peer_data, p_dst_addr);
#endif
}


ret_code_t nrf_dfu_settings_init(bool sd_irq_initialized)
{
    NRF_LOG_DEBUG("Calling nrf_dfu_settings_init()...");

    ret_code_t err_code = nrf_dfu_flash_init(sd_irq_initialized);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_dfu_flash_init() failed with error: %x", err_code);
        return NRF_ERROR_INTERNAL;
    }

    bool settings_valid        = settings_crc_ok();
    bool settings_backup_valid = settings_backup_crc_ok();

    if (settings_valid)
    {
        NRF_LOG_DEBUG("Using settings page.");
        memcpy(&s_dfu_settings, m_dfu_settings_buffer, sizeof(nrf_dfu_settings_t));
        if (settings_backup_valid)
        {
            NRF_LOG_DEBUG("Copying forbidden parts from backup page.");
            settings_forbidden_parts_copy_from_backup((uint8_t *)&s_dfu_settings);
        }
    }
    else if (settings_backup_valid)
    {
        NRF_LOG_INFO("Restoring settings from backup since the settings page contents are "
                     "invalid (CRC error).");
        memcpy(&s_dfu_settings,
               mp_dfu_settings_backup_buffer,
               sizeof(nrf_dfu_settings_t));
    }
    else
    {
        NRF_LOG_WARNING("Resetting bootloader settings since neither the settings page nor the "
                        "backup are valid (CRC error).");
        memset(&s_dfu_settings, 0x00, sizeof(nrf_dfu_settings_t));
        s_dfu_settings.settings_version = NRF_DFU_SETTINGS_VERSION;
    }

    if (NRF_DFU_SETTINGS_COMPATIBILITY_MODE && !NRF_DFU_IN_APP && (s_dfu_settings.settings_version == 1))
    {
        NRF_LOG_INFO("Old settings page detected. Upgrading info.");

        // Old version. Translate.
        memcpy(&s_dfu_settings.peer_data, (uint8_t *)&s_dfu_settings + DFU_SETTINGS_BOND_DATA_OFFSET_V1, NRF_DFU_PEER_DATA_LEN);
        memcpy(&s_dfu_settings.adv_name,  (uint8_t *)&s_dfu_settings + DFU_SETTINGS_ADV_NAME_OFFSET_V1,  NRF_DFU_ADV_NAME_LEN);

        // Initialize with defaults.
        s_dfu_settings.boot_validation_softdevice.type = NO_VALIDATION;
        s_dfu_settings.boot_validation_app.type        = VALIDATE_CRC;
        s_dfu_settings.boot_validation_bootloader.type = NO_VALIDATION;
        memcpy(s_dfu_settings.boot_validation_app.bytes, &s_dfu_settings.bank_0.image_crc, sizeof(uint32_t));

        s_dfu_settings.settings_version = NRF_DFU_SETTINGS_VERSION;
    }

    err_code = nrf_dfu_settings_write_and_backup(NULL);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_dfu_settings_write_and_backup() failed with error: %x", err_code);
        return NRF_ERROR_INTERNAL;
    }

    return NRF_SUCCESS;
}


static bool settings_forbidden_parts_equal_to_backup(uint8_t * p_compare_addr)
{
    nrf_dfu_settings_t temp_settings;
    memcpy(&temp_settings, p_compare_addr, sizeof(nrf_dfu_settings_t));
    settings_forbidden_parts_copy_from_backup((uint8_t *)&temp_settings);
    return memcmp(&temp_settings, p_compare_addr, sizeof(nrf_dfu_settings_t)) == 0;
}


static ret_code_t settings_write(void                   * p_dst,
                                 void const             * p_src,
                                 nrf_dfu_flash_callback_t callback,
                                 nrf_dfu_settings_t     * p_dfu_settings_buffer)
{
    ret_code_t err_code;

    if (memcmp(p_dst, p_src, sizeof(nrf_dfu_settings_t)) == 0)
    {
        NRF_LOG_DEBUG("Destination settings are identical to source, write not needed. Skipping.");
        if (callback != NULL)
        {
            callback(NULL);
        }
        return NRF_SUCCESS;
    }

    if (NRF_DFU_IN_APP && !settings_forbidden_parts_equal_to_backup((uint8_t *)&s_dfu_settings))
    {
        NRF_LOG_WARNING("Settings write aborted since it tries writing to forbidden settings.");
        return NRF_ERROR_FORBIDDEN;
    }

    NRF_LOG_DEBUG("Writing settings...");
    NRF_LOG_DEBUG("Erasing old settings at: 0x%08x", p_dst);

    // Not setting the callback function because ERASE is required before STORE
    // Only report completion on successful STORE.
    err_code = nrf_dfu_flash_erase((uint32_t)p_dst, 1, NULL);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Could not erase the settings page!");
        return NRF_ERROR_INTERNAL;
    }

    ASSERT(p_dfu_settings_buffer != NULL);
    memcpy(p_dfu_settings_buffer, p_src, sizeof(nrf_dfu_settings_t));

    err_code = nrf_dfu_flash_store((uint32_t)p_dst,
                                   p_dfu_settings_buffer,
                                   sizeof(nrf_dfu_settings_t),
                                   callback);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Could not write the DFU settings page!");
        return NRF_ERROR_INTERNAL;
    }

    return NRF_SUCCESS;
}


ret_code_t nrf_dfu_settings_write(nrf_dfu_flash_callback_t callback)
{
    static nrf_dfu_settings_t dfu_settings_buffer;
    s_dfu_settings.crc = settings_crc_get(&s_dfu_settings);
    s_dfu_settings.boot_validation_crc = boot_validation_crc(&s_dfu_settings);
    return settings_write(m_dfu_settings_buffer,
                          &s_dfu_settings,
                          callback,
                          &dfu_settings_buffer);
}


void settings_backup(nrf_dfu_flash_callback_t callback, void * p_src)
{
#if NRF_DFU_IN_APP
    NRF_LOG_INFO("Settings backup not available from app.");
#else
    static nrf_dfu_settings_t dfu_settings_buffer;
    NRF_LOG_INFO("Backing up settings page to address 0x%x.", mp_dfu_settings_backup_buffer);
    ASSERT(crc_ok(p_src));
    ret_code_t err_code = settings_write(mp_dfu_settings_backup_buffer,
                                         p_src,
                                         callback,
                                         &dfu_settings_buffer);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Could not perform backup of bootloader settings! Error: 0x%x", err_code);
    }
#endif
}


void nrf_dfu_settings_backup(nrf_dfu_flash_callback_t callback)
{
    settings_backup(callback, m_dfu_settings_buffer);
}


ret_code_t nrf_dfu_settings_write_and_backup(nrf_dfu_flash_callback_t callback)
{
#if NRF_DFU_IN_APP
    ret_code_t err_code = nrf_dfu_settings_write(callback);
#else
    ret_code_t err_code = nrf_dfu_settings_write(NULL);
    if (err_code == NRF_SUCCESS)
    {
        settings_backup(callback, &s_dfu_settings);
    }
#endif
    return err_code;
}


__WEAK ret_code_t nrf_dfu_settings_additional_erase(void)
{
    NRF_LOG_WARNING("No additional data erased");
    return NRF_SUCCESS;
}
