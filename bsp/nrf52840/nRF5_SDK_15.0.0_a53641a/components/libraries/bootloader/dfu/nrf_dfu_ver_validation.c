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
#include <stdbool.h>
#include "nrf_dfu_types.h"
#include "nrf_dfu_settings.h"
#include "nrf_dfu_utils.h"
#include "nrf_bootloader_info.h"
#include "nrf_crypto.h"
#include "nrf_assert.h"
#include "dfu-cc.pb.h"
#include "nrf_dfu_ver_validation.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_ver_validation
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


#ifndef NRF_DFU_DEBUG
#ifdef NRF_DFU_DEBUG_VERSION
#define NRF_DFU_DEBUG 1
#else
#define NRF_DFU_DEBUG 0
#endif
#endif

/** @brief Macro for reading the Firmware ID of a SoftDevice at a given base address.
 */
#ifndef _SD_FWID_GET
#define _SD_FWID_GET(baseaddr)         SD_OFFSET_GET_UINT16(baseaddr, 0x0C)
#endif

#define EXT_ERR(err) (nrf_dfu_result_t)((uint32_t)NRF_DFU_RES_CODE_EXT_ERROR + (uint32_t)err)

static bool sd_req_check(uint32_t const * p_sd_req, uint8_t sd_req_cnt)
{
    bool result = false;
    for (uint8_t i = 0; i < sd_req_cnt; i++)
    {
        if (p_sd_req[i] == _SD_FWID_GET(MBR_SIZE))
        {
            // Found a matching sd_req field. sd_req is ok.
            result = true;
            break;
        }
    }
    return result;
}

static bool sd_req_ok(dfu_init_command_t const * p_init)
{
    ASSERT(p_init != NULL);
    bool result;
#ifdef BLE_STACK_SUPPORT_REQD
    // The bootloader needs the SoftDevice, so disabling NRF_DFU_APP_DOWNGRADE_PREVENTION
    // should not be applied to SoftDevice updates.
    const bool prevent_downgrade = NRF_DFU_APP_DOWNGRADE_PREVENTION || (p_init->type == DFU_FW_TYPE_SOFTDEVICE);
#else
    const bool prevent_downgrade = NRF_DFU_APP_DOWNGRADE_PREVENTION;
#endif

    if (SD_PRESENT)
    {
        if (p_init->sd_req_count && (p_init->sd_req[0] != SD_REQ_APP_OVERWRITES_SD))
        {
            result = sd_req_check(p_init->sd_req, p_init->sd_req_count);
        }
        else if (p_init->type == DFU_FW_TYPE_APPLICATION)
        {
            // The application wants to overwrite the SoftDevice.
            if (prevent_downgrade && (p_init->sd_req_count > 1) && (p_init->sd_req[0] == SD_REQ_APP_OVERWRITES_SD))
            {
                // The application can overwrite the SD if sd_req[0] == 0 and table has the fwid of the current SD.
                result = sd_req_check(p_init->sd_req, p_init->sd_req_count);
            }
            else
            {
                result = true;
            }
        }
        else
        {
            // Don't allow SoftDevice updates which assume no SD is present already.
            result = !prevent_downgrade || (p_init->type != DFU_FW_TYPE_SOFTDEVICE);
        }
    }
    else
    {
        if (p_init->sd_req_count && (p_init->sd_req[0] != SD_REQ_APP_OVERWRITES_SD))
        {
            // Fail if there is no SD and the update requires SD.
            result = false;
        }
        else
        {
            // If there is no SD and update has SD it is accepted only if it has a fw_version.
            result = !prevent_downgrade || p_init->has_fw_version;
        }
    }
    return result;
}

static bool fw_hash_type_ok(dfu_init_command_t const * p_init)
{
    ASSERT(p_init != NULL);

    return (p_init->hash.hash_type == DFU_HASH_TYPE_SHA256);
}

static bool fw_version_required(dfu_fw_type_t new_fw_type)
{
    bool result = true;

    if (new_fw_type == DFU_FW_TYPE_SOFTDEVICE)
    {
        result = false; // fw_version is optional in SoftDevice updates. If present, it will be checked against the app version.
    }
    else if (new_fw_type == DFU_FW_TYPE_APPLICATION)
    {
        result = NRF_DFU_APP_DOWNGRADE_PREVENTION; // fw_version is configurable in app updates.
    }

    return result;
}


static bool fw_type_ok(dfu_init_command_t const * p_init)
{
    ASSERT(p_init != NULL);

    return ((p_init->has_type)
            && (  (p_init->type == DFU_FW_TYPE_APPLICATION)
               || (p_init->type == DFU_FW_TYPE_SOFTDEVICE)
               || (p_init->type == DFU_FW_TYPE_BOOTLOADER)
               || (p_init->type == DFU_FW_TYPE_SOFTDEVICE_BOOTLOADER)));
}


// This function assumes p_init->has_fw_version.
static bool fw_version_ok(dfu_init_command_t const * p_init)
{
    ASSERT(p_init != NULL);
    ASSERT(p_init->has_fw_version);

    if (  (p_init->type == DFU_FW_TYPE_APPLICATION)
       || (p_init->type == DFU_FW_TYPE_SOFTDEVICE))
    {
        return ((p_init->fw_version >= s_dfu_settings.app_version) || !NRF_DFU_APP_DOWNGRADE_PREVENTION);
    }
    else
    {
        return  (p_init->fw_version > s_dfu_settings.bootloader_version);
    }
}

nrf_dfu_result_t nrf_dfu_ver_validation_check(dfu_init_command_t const * p_init)
{
    nrf_dfu_result_t ret_val = NRF_DFU_RES_CODE_SUCCESS;
    if (!fw_type_ok(p_init))
    {
        NRF_LOG_ERROR("Invalid firmware type.");
        ret_val = EXT_ERR(NRF_DFU_EXT_ERROR_INIT_COMMAND_INVALID);
    }
    else if (!fw_hash_type_ok(p_init))
    {
        NRF_LOG_ERROR("Invalid hash type.");
        ret_val = EXT_ERR(NRF_DFU_EXT_ERROR_WRONG_HASH_TYPE);
    }
    else if (!NRF_DFU_DEBUG ||
            (NRF_DFU_DEBUG && ((p_init->has_is_debug == false) || (p_init->is_debug == false))))
    {
        if (p_init->has_hw_version == false)
        {
            NRF_LOG_ERROR("No HW version.");
            ret_val = EXT_ERR(NRF_DFU_EXT_ERROR_INIT_COMMAND_INVALID);
        }
        else if (p_init->hw_version != NRF_DFU_HW_VERSION)
        {
            NRF_LOG_WARNING("Faulty HW version.");
            ret_val = EXT_ERR( NRF_DFU_EXT_ERROR_HW_VERSION_FAILURE);
        }
        else if (!sd_req_ok(p_init))
        {
            NRF_LOG_WARNING("SD req not met.");
            ret_val = EXT_ERR(NRF_DFU_EXT_ERROR_SD_VERSION_FAILURE);
        }
        else if (p_init->has_fw_version)
        {
            if (!fw_version_ok(p_init))
            {
                NRF_LOG_WARNING("FW version too low.");
                ret_val = EXT_ERR(NRF_DFU_EXT_ERROR_FW_VERSION_FAILURE);
            }
        }
        else
        {
            if (fw_version_required(p_init->type))
            {
                NRF_LOG_ERROR("FW version missing.");
                ret_val = EXT_ERR(NRF_DFU_EXT_ERROR_INIT_COMMAND_INVALID);
            }
        }
    }
    return ret_val;
}
