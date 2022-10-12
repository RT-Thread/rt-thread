/**
 * \file
 *
 * \brief Generic Clock Controller.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
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

#ifndef _HPL_GCLK_H_INCLUDED
#define _HPL_GCLK_H_INCLUDED

#include <compiler.h>
#ifdef _UNIT_TEST_
#include <hri_gclk1_v210_mock.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup gclk_group GCLK Hardware Proxy Layer
 *
 * \section gclk_hpl_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

/**
 * \name HPL functions
 */
//@{
/**
 * \brief Enable clock on the given channel with the given clock source
 *
 * This function maps the given clock source to the given clock channel
 * and enables channel.
 *
 * \param[in] channel The channel to enable clock for
 * \param[in] source The clock source for the given channel
 */
static inline void _gclk_enable_channel(const uint8_t channel, const uint8_t source)
{

	hri_gclk_write_PCHCTRL_reg(GCLK, channel, source | GCLK_PCHCTRL_CHEN);
}

/**
 * \brief Initialize GCLK generators by function references
 * \param[in] bm Bit mapping for referenced generators,
 *               a bit 1 in position triggers generator initialization.
 */
void _gclk_init_generators_by_fref(uint32_t bm);

//@}
/**@}*/
#ifdef __cplusplus
}
#endif

#endif /* _HPL_GCLK_H_INCLUDED */
