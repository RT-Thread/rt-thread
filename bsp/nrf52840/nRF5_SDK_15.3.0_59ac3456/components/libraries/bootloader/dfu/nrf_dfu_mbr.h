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
/**@file
 *
 * @defgroup sdk_nrf_dfu_mbr MBR functions
 * @{
 * @ingroup  nrf_dfu
 */

#ifndef NRF_DFU_MBR_H__
#define NRF_DFU_MBR_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Function for copying the bootloader using an MBR command.
 *
 * @param[in] p_src         Source address of the bootloader data to copy.
 * @param[in] len           Length of the data to copy in bytes.
 *
 * @return  This function will return only if the command request could not be run.
 *          See @ref sd_mbr_command_copy_bl_t for possible return values.
 */
uint32_t nrf_dfu_mbr_copy_bl(uint32_t * p_src, uint32_t len);


/** @brief Function for initializing the SoftDevice using an MBR command.
 *
 * @retval  NRF_SUCCESS     If the SoftDevice was initialized successfully.
 *                          Any other return value indicates that the SoftDevice
 *                          could not be initialized.
 */
uint32_t nrf_dfu_mbr_init_sd(void);


/** @brief Function for setting the address of the IRQ table to the app's using an MBR command.
 *
 * @retval  NRF_SUCCESS  If the address of the new irq table was set. Any other
 *                       return value indicates that the address could not be set.
 */
uint32_t nrf_dfu_mbr_irq_forward_address_set(void);


#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_MBR_H__

/** @} */
