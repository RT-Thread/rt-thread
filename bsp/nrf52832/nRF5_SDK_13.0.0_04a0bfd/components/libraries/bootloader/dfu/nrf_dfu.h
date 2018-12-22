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
/**@file
 *
 * @defgroup sdk_nrf_dfu DFU bootloader
 * @{
 * @ingroup  sdk_nrf_bootloader
 * @brief Bootloader with Device Firmware Update (DFU) functionality.
 *
 * The DFU bootloader module, in combination with the @ref sdk_bootloader module,
 * can be used to implement a bootloader that supports Device Firmware Updates.
 */


#ifndef NRF_DFU_H__
#define NRF_DFU_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BOOTLOADER_BUTTON                       (BSP_BUTTON_3)                      /**< Button for entering DFU mode. */

/** @brief Function for initializing a DFU operation.
 *
 * This function initializes a DFU operation and any transports that are registered
 * in the system.
 *
 * @retval  NRF_SUCCESS     If the DFU operation was successfully initialized.
 */
uint32_t nrf_dfu_init(void);


/** @brief Function for checking if DFU mode should be entered.
 *
 * This function checks whether DFU mode is required.
 *
 * @retval  true    If DFU mode must be entered.
 * @retval  false   If there is no need to enter DFU mode.
 */
bool nrf_dfu_enter_check(void);


/** @brief Function for checking if DFU should be reset (failsafe).
 *
 * This function will check if DFU should be reset (failsafe).
 *
 * If this returns true, DFU mode will be entered and DFU will be reset.
 *
 * @retval  true    If DFU must be reset (failsafe).
 * @retval  false   If there is no need to reset DFU.
 */
bool nrf_dfu_check_failsafe_reset(void);


/** @brief Function for blocking until an event (i.e. incoming BLE packet) arrives.
 */
void nrf_dfu_wait(void);

#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_H__

/** @} */
