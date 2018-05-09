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
 * @defgroup sdk_nrf_bootloader Bootloader modules
 * @ingroup app_common
 * @brief Modules for creating a bootloader.
 *
 * @defgroup sdk_bootloader Bootloader
 * @{
 * @ingroup sdk_nrf_bootloader
 * @brief Basic bootloader.
 *
 * The bootloader module can be used to implement a basic bootloader that
 * can be extended with, for example, Device Firmware Update (DFU) support
 * or custom functionality.
  */

#ifndef NRF_BOOTLOADER_H__
#define NRF_BOOTLOADER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Function for initializing the bootloader.
 *
 * @details This function is the entry point of all bootloader operations.
 *          If DFU functionality is compiled in, the DFU process is initialized
 *          when running this function.
 *
 * @retval  NRF_SUCCESS     If the bootloader was successfully initialized.
 *                          Any other return code indicates that the operation failed.
 */
uint32_t nrf_bootloader_init(void);


/** @brief Function for customizing the bootloader initialization.
 *
 * @details This function is called during the initialization of the bootloader.
 *          It is implemented as weak function that can be overridden in the main file of the application.
 *
 * @retval  NRF_SUCCESS     If the user initialization was run successfully.
 */
uint32_t nrf_bootloader_user_init(void);


#ifdef __cplusplus
}
#endif

#endif // NRF_BOOTLOADER_H__
/** @} */
