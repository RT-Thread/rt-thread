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
/**@file
 *
 * @defgroup nrf_bootloader_app Application start
 * @{
 * @ingroup nrf_bootloader
 */

#ifndef NRF_BOOTLOADER_APP_START_H__
#define NRF_BOOTLOADER_APP_START_H__

#include <stdint.h>
#include <stdbool.h>
#include "sdk_errors.h"


/**@brief Function for using hardware to protect flash from writing and reading.
 *
 * @details This function will apply write/erase protection to a specific area. Read
 *          protection is optional, decided by \p read_protect. This function uses
 *          the BPROT or ACL peripheral, depending on which is available.
 *
 * @param[in]  address       The start address of the area to protect. Must be a flash page
 *                           boundary.
 * @param[in]  size          The size of the area to protect, in bytes. Must be a multiple
 *                           of flash page size.
 * @param[in]  read_protect  Whether to protect the area from reading/executing as well.
 *                           This is not available on chips with the BPROT peripheral
 *                           (e.g. nrf52832, nrf52810).
 *
 * @retval  NRF_SUCCESS              Flash protection applied successfully.
 * @retval  NRF_ERROR_NO_MEM         No more ACL instances to use for flash protection.
 * @retval  NRF_ERROR_INVALID_PARAM  Address was out of range or size was not a multiple
 *                                   of flash page size.
 */
ret_code_t nrf_bootloader_flash_protect(uint32_t address, uint32_t size, bool read_protect);

/**@brief Function for starting another application (and aborting the current one).
 *
 * @details This function uses the provided address to swap the stack pointer and then load
 *          the address of the reset handler to be executed. It checks the current system mode
 *          (thread/handler). If in thread mode, it resets into the other application.
 *          If in handler mode, isr_abort is executed to ensure that handler mode is left correctly.
 *          It then jumps into the reset handler of the other application.
 *
 * @note This function assumes the SoftDevice has not previously been initialized.
 *
 * @note This function will never return, but issues a reset into the provided application.
 */
void nrf_bootloader_app_start(void);

#endif // NRF_BOOTLOADER_APP_START_H__

/** @} */
