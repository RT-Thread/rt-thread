/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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
 * @defgroup nrf_bootloader_fw_activation Firmware activation
 * @{
 * @ingroup  nrf_bootloader
 */

#ifndef NRF_BOOTLOADER_FW_ACTIVATION_H__
#define NRF_BOOTLOADER_FW_ACTIVATION_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    ACTIVATION_NONE,                             //!< No new update was found.
    ACTIVATION_SUCCESS,                          //!< Update was successfully activated.
    ACTIVATION_SUCCESS_EXPECT_ADDITIONAL_UPDATE, //!< Update was successfully activated, but there might be additional update(s) to be transferred.
    ACTIVATION_ERROR,                            //!< Activation of an update failed.
} nrf_bootloader_fw_activation_result_t;

/** @brief Function for activating a firmware received during DFU.
 *
 * @details     This function initiates or continues the DFU copy-back
 *              routines. These routines are fail-safe operations to activate
 *              either a new SoftDevice, bootloader, combination of SoftDevice and
 *              bootloader, or a new application.
 *
 * @details     This function relies on accessing MBR commands through supervisor calls.
 *              It does not rely on the SoftDevice for flash operations.
 *
 * @note        When updating the bootloader or both bootloader and SoftDevice in combination,
 *              this function does not return, but rather initiates a reboot to activate
 *              the new bootloader.
 *
 * @retval  ACTIVATION_NONE                              If no update was found.
 * @retval  ACTIVATION_SUCCESS                           If the firmware update was successfully activated.
 * @retval  ACTIVATION_SUCCESS_EXPECT_ADDITIONAL_UPDATE  If the firmware update was successfully activated,
 *                                                       but there are likely more updates to be transferred.
 * @retval  ACTIVATION_ERROR                             If the firmware update could not be activated.
 */
nrf_bootloader_fw_activation_result_t nrf_bootloader_fw_activate(void);



#ifdef __cplusplus
}
#endif

#endif // NRF_BOOTLOADER_FW_ACTIVATION_H__

/** @} */
