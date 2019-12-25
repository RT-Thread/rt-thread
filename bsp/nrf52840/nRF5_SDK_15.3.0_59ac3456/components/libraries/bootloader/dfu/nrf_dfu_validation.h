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
/**@file
 *
 * @defgroup nrf_dfu_validation Validation
 * @{
 * @ingroup  nrf_dfu
 */

#ifndef __NRF_DFU_VALIDATION_H
#define __NRF_DFU_VALIDATION_H

#include "stdint.h"
#include "sdk_errors.h"
#include "dfu-cc.pb.h"
#include "nrf_dfu_handling_error.h"

/**
 * @brief Function for module initialization.
 *
 * Function checks if there is a valid init packet in DFU settings written in flash.
 */
void nrf_dfu_validation_init(void);

/**
 * @brief Function called on reception of init command creation request.
 *
 * @param[in] size Size of incoming init packet.
 *
 * @return       Operation result. See @ref nrf_dfu_result_t
 */
nrf_dfu_result_t nrf_dfu_validation_init_cmd_create(uint32_t size);

/**
 * @brief Function called on reception of fragment of init command.
 *
 * @param[in] p_data Init command fragment.
 * @param[in] length Init command fragment size.
 *
 * @return       Operation result. See @ref nrf_dfu_result_t
 */
nrf_dfu_result_t nrf_dfu_validation_init_cmd_append(uint8_t const * p_data, uint32_t length);

/**
 * @brief Function for getting init command status.
 *
 * @param[out] p_offset   Current offset.
 * @param[out] p_crc      Current CRC.
 * @param[out] p_max_size Maximum size of init command.
 */
void nrf_dfu_validation_init_cmd_status_get(uint32_t * p_offset,
                                            uint32_t * p_crc,
                                            uint32_t * p_max_size);

/**
 * @brief Function for inquiring whether a valid init command has been received.
 *
 * @return true  if there is a valid init command. This can be true at boot time
 *               if the device was reset during a DFU operation.
 */
bool nrf_dfu_validation_init_cmd_present(void);

/**
 * @brief Function for validating init command and retrieving the address and length of the firmware.
 *
 * If init command is successfully validated Bank 1 details are written to out parameters.
 *
 * Until @ref nrf_dfu_validation_init_cmd_create is called, this function can be called
 * again after the first time without side effects to retrieve address and length.
 *
 * @param[out] p_dst_data_addr  Start address of received data, if validation is successful.
 * @param[out] p_data_len       Expected length of received data, if validation is successful.
 *
 * @return       Operation result. See @ref nrf_dfu_result_t
 */
nrf_dfu_result_t nrf_dfu_validation_init_cmd_execute(uint32_t * p_dst_data_addr,
                                                     uint32_t * p_data_len);

/**
 * @brief Function for validating the init command.
 *
 * @return       Operation result. See @ref nrf_dfu_result_t.
 */
nrf_dfu_result_t nrf_dfu_validation_prevalidate(void);

/**
 * @brief Function for validating the firmware for booting.
 *
 * @param[in] p_validation  Validation parameters.
 * @param[in] data_addr     Start address of the firmware.
 * @param[in] data_len      Length of the firmware.
 *
 * @return       Whether the firmware is valid for booting.
 */
bool nrf_dfu_validation_boot_validate(boot_validation_t const * p_validation, uint32_t data_addr, uint32_t data_len);

/**
 * @brief Function for postvalidating the update after all data is received.
 *
 * @param[in] data_addr  Start address of the received data.
 * @param[in] data_len   Length of the received data.
 *
 * @return       Operation result. See @ref nrf_dfu_result_t.
 */
nrf_dfu_result_t nrf_dfu_validation_post_data_execute(uint32_t data_addr, uint32_t data_len);

/**
 * @brief Function for preparing the update for activation.
 *
 * This function is called after a reset, after all data is received. This function also runs
 * @ref nrf_dfu_validation_post_data_execute internally. If this succeeds, the update is
 * activated by the activation machinery in the bootloader the next time it runs.
 *
 * @note The caller must have permissions to edit the relevant entries in the settings.
 *
 * @param[in] data_addr  Start address of the received data.
 * @param[in] data_len   Length of the received data.
 *
 * @return       Operation result. See @ref nrf_dfu_result_t
 */
nrf_dfu_result_t nrf_dfu_validation_activation_prepare(uint32_t data_addr, uint32_t data_len);

/**
 * @brief Function to execute on a validated external app.
 *
 * @details This function is called once all data is received with the parameter
 *          @p is_boot set to false. The function is called during bootup with the parameter
 *          set to true.
 *
 *
 *
 * @note This function requires that @ref NRF_DFU_SUPPORTS_EXTERNAL_APP is set to 1.
 *       It is up to the user to implement this function.
 *
 * @warning Parameter @p is_trusted must be used to ensure that no loss of security of process can happen.
 *          This parameter should only be set if the function is called after a root-of-trust
 *          reset on the device.
 *
 *          Parameter @p is_trusted can be used for the following:
 *          - Ensuring that an external application is run only once (after root-of-trust).
 *          - Ensuring that a bank flag or any other flash access can only happen after root-of-trust.
 *          - Ensuring that the device reaches the correct state after a power failure on the device.
 *
 * @param[in] p_init        Init command for the firmware upgrade.
 * @param[in] is_trusted    Must be set to true if this is called after root-of-trust boot.
 *                          Must be set to false if this is called from DFU mode or background
 *                          DFU operation.
 *
 * @return      Operation result. see @ref nrf_dfu_result_t.
 */
nrf_dfu_result_t nrf_dfu_validation_post_external_app_execute(dfu_init_command_t const * p_init, bool is_trusted);

/**
* @brief Function to check if there is a valid external app in Bank 1.
*
* @returns True if valid external app, otherwise false.
*/
bool nrf_dfu_validation_valid_external_app(void);

#endif //__NRF_DFU_VALIDATION_H

/** @} */
