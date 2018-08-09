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

#ifndef __NRF_MPU_H
#define __NRF_MPU_H

/**
* @defgroup nrf_mpu MPU (Memory Protection Unit) driver
* @{
* @ingroup app_common
* @brief Functions for controlling MPU
*/
#include <stdint.h>
#include <stdlib.h>
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief MPU region handle. */
typedef uint8_t nrf_mpu_region_t;

/**@brief Initialize MPU and driver.
 *
 * @return NRF_SUCCESS on success, otherwise error code.
 */
ret_code_t nrf_mpu_init(void);

/**@brief Create new MPU region.
 *
 * @param[out]  p_region    Region handle.
 * @param[in]   address     Region base address.
 * @param[in]   size        Region size,
 * @param[in]   attributes  Region attributes.
 *
 * @return NRF_SUCCESS on success, otherwise error code.
 */
ret_code_t nrf_mpu_region_create(nrf_mpu_region_t *p_region,
                                 void *address,
                                 size_t size,
                                 uint32_t attributes);

/**@brief Destroy MPU region.
 *
 * @param[in]  region    Region handle.
 *
 * @return NRF_SUCCESS on success, otherwise error code.
 */
ret_code_t nrf_mpu_region_destroy(nrf_mpu_region_t region);

#ifdef __cplusplus
}
#endif

#endif /* __NRF_MPU_H */
/** @} */
