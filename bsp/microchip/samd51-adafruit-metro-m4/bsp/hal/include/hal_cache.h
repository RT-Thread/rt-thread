/**
 * \file
 *
 * \brief HAL cache functionality implementation.
 *
 * Copyright (c)2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef HAL_CACHE_H_
#define HAL_CACHE_H_

#include <hpl_cmcc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Enable cache module
 *
 * \param[in] pointer pointing to the starting address of cache module
 *
 * \return status of operation
 */
int32_t cache_enable(const void *hw);

/**
 * \brief Disable cache module
 *
 * \param[in] pointer pointing to the starting address of cache module
 *
 * \return status of operation
 */
int32_t cache_disable(const void *hw);

/**
 * \brief Initialize cache module
 *
 * This function initialize cache module configuration.
 *
 * \return status of operation
 */
int32_t cache_init(void);

/**
 * \brief Configure cache module
 *
 * \param[in] pointer pointing to the starting address of cache module
 * \param[in] cache configuration structure pointer
 *
 * \return status of operation
 */
int32_t cache_configure(const void *hw, struct _cache_cfg *cache);

/**
 * \brief Invalidate entire cache entries
 *
 * \param[in] pointer pointing to the starting address of cache module
 *
 * \return status of operation
 */
int32_t cache_invalidate_all(const void *hw);

#ifdef __cplusplus
}
#endif

#endif /* HAL_CACHE_H_ */
