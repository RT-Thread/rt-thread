/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#include "nrf_dfu_flash.h"
#include "nrf_bootloader_info.h"
#include "pb.h"
#include "pb_common.h"
#include "pb_decode.h"
#include "dfu-cc.pb.h"
#include "crc32.h"
#include "nrf_crypto.h"
#include "nrf_crypto_shared.h"
#include "nrf_assert.h"
#include "nrf_dfu_validation.h"
#include "nrf_dfu_ver_validation.h"
#include "nrf_strerror.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_validation
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
NRF_LOG_MODULE_REGISTER();

#ifndef DFU_REQUIRES_SOFTDEVICE
#if !defined(BLE_STACK_SUPPORT_REQD) && !defined(ANT_STACK_SUPPORT_REQD)
#define DFU_REQUIRES_SOFTDEVICE 0
#else
#define DFU_REQUIRES_SOFTDEVICE 1
#endif
#endif

#define EXT_ERR(err) (nrf_dfu_result_t)((uint32_t)NRF_DFU_RES_CODE_EXT_ERROR + (uint32_t)err)

/* Whether a complete init command has been received and prevalidated, but the firmware
 * is not yet fully transferred. This value will also be correct after reset.
 */
static bool               m_valid_init_cmd_present = false;
static dfu_packet_t       m_packet                 = DFU_PACKET_INIT_DEFAULT;
static uint8_t*           m_init_packet_data_ptr   = 0;
static uint32_t           m_init_packet_data_len   = 0;
static pb_istream_t       m_pb_stream;

static dfu_init_command_t const * mp_init = NULL;

__ALIGN(4) extern const uint8_t pk[64];

/** @brief Value length structure holding the public key.
 *
 * @details The pk value pointed to is the public key present in dfu_public_key.c
 */
static nrf_crypto_ecc_public_key_t                  m_public_key;

/** @brief Structure to hold a signature
 */
static nrf_crypto_ecdsa_secp256r1_signature_t       m_signature;

/** @brief Structure to hold the hash for signature verification
 */
static nrf_crypto_hash_sha256_digest_t              m_sig_hash;

/** @brief Structure to hold the hash for the firmware image
 */
static nrf_crypto_hash_sha256_digest_t              m_fw_hash;

/** @brief Whether nrf_crypto and local keys have been initialized.
 */
static bool                                         m_crypto_initialized = false;

/** @brief Flag used by parser code to indicate that the init command has been found to be invalid.
 */
static bool                                         m_init_packet_valid = false;

static void pb_decoding_callback(pb_istream_t *str,
                                 uint32_t tag,
                                 pb_wire_type_t wire_type,
                                 void *iter)
{
    pb_field_iter_t* p_iter = (pb_field_iter_t *) iter;

    // Match the beginning of the init command.
    if (p_iter->pos->ptr == &dfu_init_command_fields[0])
    {
        uint8_t  * ptr  = (uint8_t *)str->state;
        uint32_t   size = str->bytes_left;

        if (m_init_packet_data_ptr != NULL || m_init_packet_data_len != 0)
        {
            m_init_packet_valid = false;
            return;
        }

        // Remove tag.
        while (*ptr & 0x80)
        {
            ptr++;
            size--;
        }
        ptr++;
        size--;

        // Store the info in init_packet_data.
        m_init_packet_data_ptr = ptr;
        m_init_packet_data_len = size;
        m_init_packet_valid    = true;

        NRF_LOG_DEBUG("PB: Init packet data len: %d", size);
    }
}

/** @brief Function for decoding byte stream into variable.
 *
 *  @retval true   If the stored init command was successfully decoded.
 *  @retval false  If there was no stored init command, or the decoding failed.
 */
static bool stored_init_cmd_decode(void)
{
    m_pb_stream = pb_istream_from_buffer(s_dfu_settings.init_command,
                                         s_dfu_settings.progress.command_size);

    dfu_init_command_t * p_init;

    // Attach our callback to follow the field decoding.
    m_pb_stream.decoding_callback = pb_decoding_callback;

    m_init_packet_valid    = false;
    m_init_packet_data_ptr = NULL;
    m_init_packet_data_len = 0;
    memset(&m_packet, 0, sizeof(m_packet));

    if (!pb_decode(&m_pb_stream, dfu_packet_fields, &m_packet))
    {
        NRF_LOG_ERROR("Handler: Invalid protocol buffer m_pb_stream");
        return false;
    }

    if (!m_init_packet_valid || (m_packet.has_signed_command && m_packet.has_command))
    {
        NRF_LOG_ERROR("Handler: Invalid init command.");
        return false;
    }
    else if (m_packet.has_signed_command && m_packet.signed_command.command.has_init)
    {
        p_init = &m_packet.signed_command.command.init;

        m_pb_stream = pb_istream_from_buffer(m_init_packet_data_ptr, m_init_packet_data_len);
        memset(p_init, 0, sizeof(dfu_init_command_t));

        if (!pb_decode(&m_pb_stream, dfu_init_command_fields, p_init))
        {
            NRF_LOG_ERROR("Handler: Invalid protocol buffer m_pb_stream (init command)");
            return false;
        }
    }
    else if (m_packet.has_command && m_packet.command.has_init)
    {
        p_init = &m_packet.command.init;
    }
    else
    {
        return false;
    }

    mp_init = p_init;

    return true;
}


static void crypto_init(void)
{
    ret_code_t err_code;
    uint8_t    pk_copy[sizeof(pk)];

    if (m_crypto_initialized)
    {
        return;
    }

    err_code = nrf_crypto_init();
    ASSERT(err_code == NRF_SUCCESS);
    UNUSED_PARAMETER(err_code);

    // Convert public key to big-endian format for use in nrf_crypto.
    nrf_crypto_internal_double_swap_endian(pk_copy, pk, sizeof(pk) / 2);

    err_code = nrf_crypto_ecc_public_key_from_raw(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                  &m_public_key,
                                                  pk_copy,
                                                  sizeof(pk));
    ASSERT(err_code == NRF_SUCCESS);
    UNUSED_PARAMETER(err_code);

    m_crypto_initialized = true;
}


void nrf_dfu_validation_init(void)
{
    // If the command is stored to flash, init command was valid.
    if ((s_dfu_settings.progress.command_size != 0) &&
         stored_init_cmd_decode())
    {
        m_valid_init_cmd_present = true;
    }
    else
    {
        m_valid_init_cmd_present = false;
    }
}


static void dfu_progress_reset(void)
{
    memset(s_dfu_settings.init_command, 0xFF, INIT_COMMAND_MAX_SIZE); // Remove the last init command
    memset(&s_dfu_settings.progress, 0, sizeof(dfu_progress_t));
    s_dfu_settings.write_offset = 0;
}


nrf_dfu_result_t nrf_dfu_validation_init_cmd_create(uint32_t size)
{
    nrf_dfu_result_t ret_val = NRF_DFU_RES_CODE_SUCCESS;
    if (size == 0)
    {
        ret_val = NRF_DFU_RES_CODE_INVALID_PARAMETER;
    }
    else if (size > INIT_COMMAND_MAX_SIZE)
    {
        ret_val = NRF_DFU_RES_CODE_INSUFFICIENT_RESOURCES;
    }
    else
    {
        // Set DFU to uninitialized.
        m_valid_init_cmd_present = false;

        // Reset all progress.
        dfu_progress_reset();

        // Set the init command size.
        s_dfu_settings.progress.command_size = size;
    }
    return ret_val;
}


nrf_dfu_result_t nrf_dfu_validation_init_cmd_append(uint8_t const * p_data, uint32_t length)
{
    nrf_dfu_result_t ret_val = NRF_DFU_RES_CODE_SUCCESS;
    if ((length + s_dfu_settings.progress.command_offset) > s_dfu_settings.progress.command_size)
    {
        NRF_LOG_ERROR("Init command larger than expected.");
        ret_val = NRF_DFU_RES_CODE_INVALID_PARAMETER;
    }
    else
    {
        // Copy the received data to RAM, update offset and calculate CRC.
        memcpy(&s_dfu_settings.init_command[s_dfu_settings.progress.command_offset],
                p_data,
                length);

        s_dfu_settings.progress.command_offset += length;
        s_dfu_settings.progress.command_crc = crc32_compute(p_data,
                                                            length,
                                                            &s_dfu_settings.progress.command_crc);
    }
    return ret_val;
}


void nrf_dfu_validation_init_cmd_status_get(uint32_t * p_offset,
                                            uint32_t * p_crc,
                                            uint32_t * p_max_size)
{
    *p_offset   = s_dfu_settings.progress.command_offset;
    *p_crc      = s_dfu_settings.progress.command_crc;
    *p_max_size = INIT_COMMAND_MAX_SIZE;
}


bool nrf_dfu_validation_init_cmd_present(void)
{
    return m_valid_init_cmd_present;
}


// Function determines if init command signature is obligatory.
static bool signature_required(dfu_fw_type_t fw_type_to_be_updated)
{
    bool result = true;

    // DFU_FW_TYPE_EXTERNAL_APPLICATION and bootloader updates always require
    // signature check
    if ((!DFU_REQUIRES_SOFTDEVICE && (fw_type_to_be_updated == DFU_FW_TYPE_SOFTDEVICE)) ||
            (fw_type_to_be_updated == DFU_FW_TYPE_APPLICATION))
    {
        result = NRF_DFU_REQUIRE_SIGNED_APP_UPDATE;
    }
    return result;
}


// Function to perform signature check if required.
static nrf_dfu_result_t nrf_dfu_validation_signature_check(dfu_signature_type_t signature_type,
                                                           uint8_t      const * p_signature,
                                                           uint32_t             signature_len,
                                                           uint8_t      const * p_data,
                                                           uint32_t             data_len)
{
    ret_code_t err_code;
    size_t     hash_len = NRF_CRYPTO_HASH_SIZE_SHA256;

    nrf_crypto_hash_context_t         hash_context   = {0};
    nrf_crypto_ecdsa_verify_context_t verify_context = {0};

    crypto_init();

    NRF_LOG_INFO("Signature required. Checking signature.")
    if (p_signature == NULL)
    {
        NRF_LOG_WARNING("No signature found.");
        return EXT_ERR(NRF_DFU_EXT_ERROR_SIGNATURE_MISSING);
    }

    if (signature_type != DFU_SIGNATURE_TYPE_ECDSA_P256_SHA256)
    {
        NRF_LOG_INFO("Invalid signature type");
        return EXT_ERR(NRF_DFU_EXT_ERROR_WRONG_SIGNATURE_TYPE);
    }

    NRF_LOG_INFO("Calculating hash (len: %d)", data_len);
    err_code = nrf_crypto_hash_calculate(&hash_context,
                                         &g_nrf_crypto_hash_sha256_info,
                                         p_data,
                                         data_len,
                                         m_sig_hash,
                                         &hash_len);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_DFU_RES_CODE_OPERATION_FAILED;
    }

    if (sizeof(m_signature) != signature_len)
    {
        return NRF_DFU_RES_CODE_OPERATION_FAILED;
    }

    // Prepare the signature received over the air.
    memcpy(m_signature, p_signature, signature_len);

    // Calculate the signature.
    NRF_LOG_INFO("Verify signature");

    // The signature is in little-endian format. Change it to big-endian format for nrf_crypto use.
    nrf_crypto_internal_double_swap_endian_in_place(m_signature, sizeof(m_signature) / 2);

    err_code = nrf_crypto_ecdsa_verify(&verify_context,
                                       &m_public_key,
                                       m_sig_hash,
                                       hash_len,
                                       m_signature,
                                       sizeof(m_signature));
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Signature failed (err_code: 0x%x)", err_code);
        NRF_LOG_DEBUG("Signature:");
        NRF_LOG_HEXDUMP_DEBUG(m_signature, sizeof(m_signature));
        NRF_LOG_DEBUG("Hash:");
        NRF_LOG_HEXDUMP_DEBUG(m_sig_hash, hash_len);
        NRF_LOG_DEBUG("Public Key:");
        NRF_LOG_HEXDUMP_DEBUG(pk, sizeof(pk));
        NRF_LOG_FLUSH();

        return NRF_DFU_RES_CODE_INVALID_OBJECT;
    }

    NRF_LOG_INFO("Image verified");
    return NRF_DFU_RES_CODE_SUCCESS;
}


// Function to calculate the total size of the firmware(s) in the update.
static nrf_dfu_result_t update_data_size_get(dfu_init_command_t const * p_init, uint32_t * p_size)
{
    nrf_dfu_result_t ret_val = EXT_ERR(NRF_DFU_EXT_ERROR_INIT_COMMAND_INVALID);
    uint32_t         fw_sz   = 0;

    if ((p_init->type == DFU_FW_TYPE_APPLICATION ||
         p_init->type == DFU_FW_TYPE_EXTERNAL_APPLICATION) &&
         (p_init->has_app_size == true))
    {
        fw_sz = p_init->app_size;
    }
    else
    {
        if ((p_init->type & DFU_FW_TYPE_SOFTDEVICE) && (p_init->has_sd_size == true))
        {
            fw_sz = p_init->sd_size;
        }

        if ((p_init->type & DFU_FW_TYPE_BOOTLOADER) && (p_init->has_bl_size == true))
        {
            if (p_init->bl_size <= BOOTLOADER_SIZE)
            {
                fw_sz += p_init->bl_size;
            }
            else
            {
                NRF_LOG_ERROR("BL size (%d) over limit (%d)", p_init->bl_size, BOOTLOADER_SIZE);
                fw_sz   = 0;
                ret_val = NRF_DFU_RES_CODE_INSUFFICIENT_RESOURCES;
            }
        }
    }

    if (fw_sz)
    {
        *p_size = fw_sz;
        ret_val = NRF_DFU_RES_CODE_SUCCESS;
    }
    else
    {
        NRF_LOG_ERROR("Init packet does not contain valid firmware size");
    }

    return ret_val;
}


/**
 * @brief Function to check if single bank update should be used.
 *
 * @param new_fw_type Firmware type.
 */
static bool use_single_bank(dfu_fw_type_t new_fw_type)
{
    bool result = false;

    // DFU_FW_TYPE_EXTERNAL_APPLICATION never uses single bank
    if (((new_fw_type == DFU_FW_TYPE_APPLICATION) ||
         (new_fw_type == DFU_FW_TYPE_SOFTDEVICE)) &&
        NRF_DFU_SINGLE_BANK_APP_UPDATES)
    {
        result = true;
    }

    return result;
}


// Function to determine whether the new firmware needs a SoftDevice to be present.
static bool update_requires_softdevice(dfu_init_command_t const * p_init)
{
    return ((p_init->sd_req_count > 0) && (p_init->sd_req[0] != SD_REQ_APP_OVERWRITES_SD));
}


// Function to determine whether the SoftDevice can be removed during the update or not.
static bool keep_softdevice(dfu_init_command_t const * p_init)
{
    UNUSED_PARAMETER(p_init); // It's unused when DFU_REQUIRES_SOFTDEVICE is true.
    return DFU_REQUIRES_SOFTDEVICE || update_requires_softdevice(p_init);
}


/**@brief Function to determine where to temporarily store the incoming firmware.
 *        This also checks whether the update will fit, and deletes existing
 *        firmware to make room for the new firmware.
 *
 * @param[in]  p_init   Init command.
 * @param[in]  fw_size  The size of the incoming firmware.
 * @param[out] p_addr   The address at which to initially store the firmware.
 *
 * @retval NRF_DFU_RES_CODE_SUCCESS                 If the size check passed and
 *                                                  an address was found.
 * @retval NRF_DFU_RES_CODE_INSUFFICIENT_RESOURCES  If the size check failed.
 */
static nrf_dfu_result_t update_data_addr_get(dfu_init_command_t const * p_init,
                                             uint32_t                   fw_size,
                                             uint32_t                 * p_addr)
{
    nrf_dfu_result_t ret_val = NRF_DFU_RES_CODE_SUCCESS;
    ret_code_t err_code = nrf_dfu_cache_prepare(fw_size,
                                                use_single_bank(p_init->type),
                                                NRF_DFU_FORCE_DUAL_BANK_APP_UPDATES,
                                                keep_softdevice(p_init));
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Can't find room for update");
        ret_val = NRF_DFU_RES_CODE_INSUFFICIENT_RESOURCES;
    }
    else
    {
        *p_addr = nrf_dfu_bank1_start_addr();
        NRF_LOG_DEBUG("Write address set to 0x%08x", *p_addr);
    }
    return ret_val;
}


nrf_dfu_result_t nrf_dfu_validation_prevalidate(void)
{
    nrf_dfu_result_t                 ret_val        = NRF_DFU_RES_CODE_SUCCESS;
    dfu_command_t            const * p_command      = &m_packet.command;
    dfu_signature_type_t             signature_type = DFU_SIGNATURE_TYPE_MIN;
    uint8_t                  const * p_signature    = NULL;
    uint32_t                         signature_len  = 0;

    if (m_packet.has_signed_command)
    {
        p_command      = &m_packet.signed_command.command;
        signature_type =  m_packet.signed_command.signature_type;
        p_signature    =  m_packet.signed_command.signature.bytes;
        signature_len  =  m_packet.signed_command.signature.size;
    }

    // Validate signature.
    if (signature_required(p_command->init.type))
    {
        ret_val = nrf_dfu_validation_signature_check(signature_type,
                                                     p_signature,
                                                     signature_len,
                                                     m_init_packet_data_ptr,
                                                     m_init_packet_data_len);
    }

    // Validate versions.
    if (ret_val == NRF_DFU_RES_CODE_SUCCESS)
    {
        ret_val = nrf_dfu_ver_validation_check(&p_command->init);
    }

    if (ret_val != NRF_DFU_RES_CODE_SUCCESS)
    {
        NRF_LOG_WARNING("Prevalidation failed.");
        NRF_LOG_DEBUG("Init command:");
        NRF_LOG_HEXDUMP_DEBUG(m_init_packet_data_ptr, m_init_packet_data_len);
    }

    return ret_val;
}


nrf_dfu_result_t nrf_dfu_validation_init_cmd_execute(uint32_t * p_dst_data_addr,
                                                     uint32_t * p_data_len)
{
    nrf_dfu_result_t ret_val = NRF_DFU_RES_CODE_SUCCESS;

    if (s_dfu_settings.progress.command_offset != s_dfu_settings.progress.command_size)
    {
        // The object wasn't the right (requested) size.
        NRF_LOG_ERROR("Execute with faulty offset");
        ret_val = NRF_DFU_RES_CODE_OPERATION_NOT_PERMITTED;
    }
    else if (m_valid_init_cmd_present)
    {
        *p_dst_data_addr = nrf_dfu_bank1_start_addr();
        ret_val          = update_data_size_get(mp_init, p_data_len);
    }
    else if (stored_init_cmd_decode())
    {
        // Will only get here if init command was received since last reset.
        // An init command should not be written to flash until after it's been checked here.
        ret_val = nrf_dfu_validation_prevalidate();

        *p_dst_data_addr = 0;
        *p_data_len      = 0;

        // Get size of binary.
        if (ret_val == NRF_DFU_RES_CODE_SUCCESS)
        {
            ret_val = update_data_size_get(mp_init, p_data_len);
        }

        // Get address where to flash the binary.
        if (ret_val == NRF_DFU_RES_CODE_SUCCESS)
        {
            ret_val = update_data_addr_get(mp_init, *p_data_len, p_dst_data_addr);
        }

        // Set flag validating the init command.
        if (ret_val == NRF_DFU_RES_CODE_SUCCESS)
        {
            m_valid_init_cmd_present = true;
        }
        else
        {
            dfu_progress_reset();
        }
    }
    else
    {
        NRF_LOG_ERROR("Failed to decode init packet");
        ret_val = NRF_DFU_RES_CODE_INVALID_OBJECT;
    }

    return ret_val;
}


// Function to check the hash received in the init command against the received firmware.
// little_endian specifies the endianness of @p p_hash.
static bool nrf_dfu_validation_hash_ok(uint8_t const * p_hash, uint32_t src_addr, uint32_t data_len, bool little_endian)
{
    ret_code_t err_code;
    bool       result   = true;
    uint8_t    hash_be[NRF_CRYPTO_HASH_SIZE_SHA256];
    size_t     hash_len = NRF_CRYPTO_HASH_SIZE_SHA256;

    nrf_crypto_hash_context_t hash_context = {0};

    crypto_init();

    if (little_endian)
    {
        // Convert to hash to big-endian format for use in nrf_crypto.
        nrf_crypto_internal_swap_endian(hash_be,
                                        p_hash,
                                        NRF_CRYPTO_HASH_SIZE_SHA256);
        p_hash = hash_be;
    }

    NRF_LOG_DEBUG("Hash verification. start address: 0x%x, size: 0x%x",
                  src_addr,
                  data_len);

    err_code = nrf_crypto_hash_calculate(&hash_context,
                                         &g_nrf_crypto_hash_sha256_info,
                                         (uint8_t*)src_addr,
                                         data_len,
                                         m_fw_hash,
                                         &hash_len);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Could not run hash verification (err_code 0x%x).", err_code);
        result = false;
    }
    else if (memcmp(m_fw_hash, p_hash, NRF_CRYPTO_HASH_SIZE_SHA256) != 0)
    {
        NRF_LOG_WARNING("Hash verification failed.");
        NRF_LOG_DEBUG("Expected FW hash:")
        NRF_LOG_HEXDUMP_DEBUG(p_hash, NRF_CRYPTO_HASH_SIZE_SHA256);
        NRF_LOG_DEBUG("Actual FW hash:")
        NRF_LOG_HEXDUMP_DEBUG(m_fw_hash, NRF_CRYPTO_HASH_SIZE_SHA256);
        NRF_LOG_FLUSH();

        result = false;
    }

    return result;
}


// Function to check the hash received in the init command against the received firmware.
bool fw_hash_ok(dfu_init_command_t const * p_init, uint32_t fw_start_addr, uint32_t fw_size)
{
    ASSERT(p_init != NULL);
    return nrf_dfu_validation_hash_ok((uint8_t *)p_init->hash.hash.bytes, fw_start_addr, fw_size, true);
}


// Function to check whether the update contains a SoftDevice and, if so, if it is of a different
// major version than the existing SoftDevice.
static bool is_major_softdevice_update(uint32_t new_sd_addr)
{
    // True if there is no SD right now, but there is a new one coming. This counts as a major update.
    bool result = !SD_PRESENT && (SD_MAGIC_NUMBER_GET(new_sd_addr) == SD_MAGIC_NUMBER);

    if (SD_PRESENT && (SD_MAGIC_NUMBER_GET(new_sd_addr) == SD_MAGIC_NUMBER))
    {
        // Both SoftDevices are present.
        uint32_t current_SD_major = SD_MAJOR_VERSION_EXTRACT(SD_VERSION_GET(MBR_SIZE));
        uint32_t new_SD_major     = SD_MAJOR_VERSION_EXTRACT(SD_VERSION_GET(new_sd_addr));

        result = (current_SD_major != new_SD_major);

        NRF_LOG_INFO("SoftDevice update is a %s version update. Current: %d. New: %d.",
                     result ? "major" : "minor",
                     current_SD_major,
                     new_SD_major);
    }

    return result;
}


/**@brief Validate the SoftDevice size and magic number in structure found at 0x2000 in received SoftDevice.
 *
 * @param[in]  sd_start_addr  Start address of received SoftDevice.
 * @param[in]  sd_size        Size of received SoftDevice in bytes.
 */
static bool softdevice_info_ok(uint32_t sd_start_addr, uint32_t sd_size)
{
    bool result = true;

    if (SD_MAGIC_NUMBER_GET(sd_start_addr) != SD_MAGIC_NUMBER)
    {
        NRF_LOG_ERROR("The SoftDevice does not contain the magic number identifying it as a SoftDevice.");
        result = false;
    }
    else if (SD_SIZE_GET(sd_start_addr) < ALIGN_TO_PAGE(sd_size + MBR_SIZE))
    {
        // The size in the info struct should be rounded up to a page boundary
        // and be larger than the actual size + the size of the MBR.
        NRF_LOG_ERROR("The SoftDevice size in the info struct is too small compared with the size reported in the init command.");
        result = false;
    }

    return result;
}


static bool boot_validation_extract(boot_validation_t * p_boot_validation,
                                    dfu_init_command_t const * p_init,
                                    uint32_t index,
                                    uint32_t start_addr,
                                    uint32_t data_len,
                                    boot_validation_type_t default_type)
{
    ret_code_t err_code;
    size_t     hash_len = NRF_CRYPTO_HASH_SIZE_SHA256;

    nrf_crypto_hash_context_t hash_context = {0};

    memset(p_boot_validation, 0, sizeof(boot_validation_t));
    p_boot_validation->type = (p_init->boot_validation_count > index)
                              ? (boot_validation_type_t)p_init->boot_validation[index].type
                              : default_type; // default

    switch(p_boot_validation->type)
    {
        case NO_VALIDATION:
            break;

        case VALIDATE_CRC:
            *(uint32_t *)&p_boot_validation->bytes[0] = crc32_compute((uint8_t *)start_addr, data_len, NULL);
            break;

        case VALIDATE_SHA256:
            err_code = nrf_crypto_hash_calculate(&hash_context,
                                                 &g_nrf_crypto_hash_sha256_info,
                                                 (uint8_t*)start_addr,
                                                 data_len,
                                                 p_boot_validation->bytes,
                                                 &hash_len);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("nrf_crypto_hash_calculate() failed with error %s", nrf_strerror_get(err_code));
                return false;
            }
            break;

        case VALIDATE_ECDSA_P256_SHA256:
            memcpy(p_boot_validation->bytes, p_init->boot_validation[index].bytes.bytes, p_init->boot_validation[index].bytes.size);
            break;

        default:
            NRF_LOG_ERROR("Invalid boot validation type: %d", p_boot_validation->type);
            return false;
    }

    return nrf_dfu_validation_boot_validate(p_boot_validation, start_addr, data_len);
}


// The is_trusted argument specifies whether the function should have side effects.
static bool postvalidate_app(dfu_init_command_t const * p_init, uint32_t src_addr, uint32_t data_len, bool is_trusted)
{
    boot_validation_t boot_validation;

    ASSERT(p_init->type == DFU_FW_TYPE_APPLICATION);

    if (!boot_validation_extract(&boot_validation, p_init, 0, src_addr, data_len, VALIDATE_CRC))
    {
        return false;
    }
#if !NRF_DFU_IN_APP
    else if (NRF_BL_APP_SIGNATURE_CHECK_REQUIRED &&
             (boot_validation.type != VALIDATE_ECDSA_P256_SHA256))
    {
        NRF_LOG_WARNING("The boot validation of the app must be a signature check.");
        return false;
    }
#endif

    if (!is_trusted)
    {
        return true;
    }

    memcpy(&s_dfu_settings.boot_validation_app, &boot_validation, sizeof(boot_validation));

    s_dfu_settings.bank_1.bank_code = NRF_DFU_BANK_VALID_APP;

    NRF_LOG_DEBUG("Invalidating old application in bank 0.");
    s_dfu_settings.bank_0.bank_code = NRF_DFU_BANK_INVALID;

    if (!DFU_REQUIRES_SOFTDEVICE && !update_requires_softdevice(p_init))
    {
         // App does not need SD, so it should be placed where SD is.
         nrf_dfu_softdevice_invalidate();
    }

    if (!NRF_DFU_DEBUG ||
                (NRF_DFU_DEBUG && (p_init->has_is_debug == false || p_init->is_debug == false)))
    {
        s_dfu_settings.app_version = p_init->fw_version;
    }

    return true;
}


// Function to check a received SoftDevice or Bootloader firmware, or both,
// before it is copied into place.
// The is_trusted argument specifies whether the function should have side effects.
static bool postvalidate_sd_bl(dfu_init_command_t const  * p_init,
                               bool                        with_sd,
                               bool                        with_bl,
                               uint32_t                    start_addr,
                               uint32_t                    data_len,
                               bool                        is_trusted)
{
    boot_validation_t boot_validation_sd = {NO_VALIDATION};
    boot_validation_t boot_validation_bl = {NO_VALIDATION};
    uint32_t bl_start = start_addr;
    uint32_t bl_size = data_len;

    ASSERT(with_sd || with_bl);

    if (with_sd)
    {
        if (!softdevice_info_ok(start_addr, p_init->sd_size))
        {
            return false;
        }

        if (is_major_softdevice_update(start_addr))
        {
            NRF_LOG_WARNING("Invalidating app because it is incompatible with the SoftDevice.");
            if (DFU_REQUIRES_SOFTDEVICE && !with_bl)
            {
                NRF_LOG_ERROR("Major SD update but no BL. Abort to avoid incapacitating the BL.");
                return false;
            }
        }

        if (!boot_validation_extract(&boot_validation_sd, p_init, 0, start_addr, p_init->sd_size, VALIDATE_CRC))
        {
            return false;
        }

        bl_start += p_init->sd_size;
        bl_size -= p_init->sd_size;
    }
    if (with_bl)
    {
        if (!boot_validation_extract(&boot_validation_bl, p_init, 0, bl_start, bl_size, NO_VALIDATION))
        {
            return false;
        }
        else if (boot_validation_bl.type != NO_VALIDATION)
        {
            NRF_LOG_WARNING("Boot validation of bootloader is not supported and will be ignored.");
        }
    }

    if (!is_trusted)
    {
        return true;
    }

    if (with_sd)
    {
        if (is_major_softdevice_update(start_addr))
        {
            // Invalidate app since it may not be compatible with new SD.
            nrf_dfu_bank_invalidate(&s_dfu_settings.bank_0);
        }

        memcpy(&s_dfu_settings.boot_validation_softdevice, &boot_validation_sd, sizeof(boot_validation_sd));

        // Mark the update as valid.
        s_dfu_settings.bank_1.bank_code = with_bl ? NRF_DFU_BANK_VALID_SD_BL
                                                  : NRF_DFU_BANK_VALID_SD;

        s_dfu_settings.sd_size = p_init->sd_size;
    }
    else
    {
        s_dfu_settings.bank_1.bank_code = NRF_DFU_BANK_VALID_BL;
    }


    if (with_bl)
    {
        memcpy(&s_dfu_settings.boot_validation_bootloader, &boot_validation_bl, sizeof(boot_validation_bl));

        if (!NRF_DFU_DEBUG ||
            (NRF_DFU_DEBUG && (p_init->has_is_debug == false || p_init->is_debug == false)))
        {
            // If the update contains a bootloader, update the version.
            // Unless the update is a debug packet.
            s_dfu_settings.bootloader_version = p_init->fw_version;
        }
    }

    return true;
}


bool nrf_dfu_validation_boot_validate(boot_validation_t const * p_validation, uint32_t data_addr, uint32_t data_len)
{
    uint8_t const * p_data = (uint8_t*) data_addr;
    switch(p_validation->type)
    {
        case NO_VALIDATION:
            return true;

        case VALIDATE_CRC:
        {
            uint32_t current_crc = *(uint32_t *)p_validation->bytes;
            uint32_t crc = crc32_compute(p_data, data_len, NULL);

            if (crc != current_crc)
            {
                // CRC does not match with what is stored.
                NRF_LOG_DEBUG("CRC check of app failed. Return %d", NRF_DFU_DEBUG);
                return NRF_DFU_DEBUG;
            }
            return true;
        }

        case VALIDATE_SHA256:
            return nrf_dfu_validation_hash_ok(p_validation->bytes, data_addr, data_len, false);

        case VALIDATE_ECDSA_P256_SHA256:
        {
            nrf_dfu_result_t res_code = nrf_dfu_validation_signature_check(
                                            DFU_SIGNATURE_TYPE_ECDSA_P256_SHA256,
                                            p_validation->bytes,
                                            NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE,
                                            p_data,
                                            data_len);
            return (res_code == NRF_DFU_RES_CODE_SUCCESS);
        }

        default:
            ASSERT(false);
            return false;
    }
}


nrf_dfu_result_t postvalidate(uint32_t data_addr, uint32_t data_len, bool is_trusted)
{
    nrf_dfu_result_t           ret_val = NRF_DFU_RES_CODE_SUCCESS;
    dfu_init_command_t const * p_init  = mp_init;

    if (!fw_hash_ok(p_init, data_addr, data_len))
    {
        ret_val = EXT_ERR(NRF_DFU_EXT_ERROR_VERIFICATION_FAILED);
    }
    else
    {
        if (p_init->type == DFU_FW_TYPE_APPLICATION)
        {
            if (!postvalidate_app(p_init, data_addr, data_len, is_trusted))
            {
                ret_val = NRF_DFU_RES_CODE_INVALID_OBJECT;
            }
        }
#if NRF_DFU_SUPPORTS_EXTERNAL_APP
        else if (p_init->type == DFU_FW_TYPE_EXTERNAL_APPLICATION)
        {
            if (!is_trusted)
            {
                // This function must be implemented externally
                ret_val = nrf_dfu_validation_post_external_app_execute(p_init, is_trusted);
            }
            else
            {
                s_dfu_settings.bank_1.bank_code = NRF_DFU_BANK_VALID_EXT_APP;
            }
        }
#endif // NRF_DFU_SUPPORTS_EXTERNAL_APP
        else
        {
            bool with_sd = p_init->type & DFU_FW_TYPE_SOFTDEVICE;
            bool with_bl = p_init->type & DFU_FW_TYPE_BOOTLOADER;

            if (!postvalidate_sd_bl(p_init, with_sd, with_bl, data_addr, data_len, is_trusted))
            {
                ret_val = NRF_DFU_RES_CODE_INVALID_OBJECT;
                if (is_trusted && with_sd && !DFU_REQUIRES_SOFTDEVICE &&
                    (data_addr == nrf_dfu_softdevice_start_address()))
                {
                    nrf_dfu_softdevice_invalidate();
                }
            }
        }
    }

    if (!is_trusted)
    {
        if (ret_val == NRF_DFU_RES_CODE_SUCCESS)
        {
            s_dfu_settings.bank_current = NRF_DFU_CURRENT_BANK_1;
        }
        else
        {
            dfu_progress_reset();
        }
    }
    else
    {
        if (ret_val == NRF_DFU_RES_CODE_SUCCESS)
        {
            // Mark the update as complete and valid.
            s_dfu_settings.bank_1.image_crc  = crc32_compute((uint8_t *)data_addr, data_len, NULL);
            s_dfu_settings.bank_1.image_size = data_len;
        }
        else
        {
            nrf_dfu_bank_invalidate(&s_dfu_settings.bank_1);
        }

        dfu_progress_reset();
        s_dfu_settings.progress.update_start_address = data_addr;
    }

    return ret_val;
}


nrf_dfu_result_t nrf_dfu_validation_post_data_execute(uint32_t data_addr, uint32_t data_len)
{
    return postvalidate(data_addr, data_len, false);
}


nrf_dfu_result_t nrf_dfu_validation_activation_prepare(uint32_t data_addr, uint32_t data_len)
{
    return postvalidate(data_addr, data_len, true);
}


bool nrf_dfu_validation_valid_external_app(void)
{
    return s_dfu_settings.bank_1.bank_code == NRF_DFU_BANK_VALID_EXT_APP;
}
