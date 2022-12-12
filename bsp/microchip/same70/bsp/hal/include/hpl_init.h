/**
 * \file
 *
 * \brief Init related functionality declaration.
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

#ifndef _HPL_INIT_H_INCLUDED
#define _HPL_INIT_H_INCLUDED

/**
 * \addtogroup HPL Init
 *
 * \section hpl_init_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name HPL functions
 */
//@{
/**
 * \brief Initializes clock sources
 */
void _sysctrl_init_sources(void);

/**
 * \brief Initializes Power Manager
 */
void _pm_init(void);

/**
 * \brief Initialize generators
 */
void _gclk_init_generators(void);

/**
 * \brief Initialize 32 kHz clock sources
 */
void _osc32kctrl_init_sources(void);

/**
 * \brief Initialize clock sources
 */
void _oscctrl_init_sources(void);

/**
 * \brief Initialize clock sources that need input reference clocks
 */
void _sysctrl_init_referenced_generators(void);

/**
 * \brief Initialize clock sources that need input reference clocks
 */
void _oscctrl_init_referenced_generators(void);

/**
 * \brief Initialize master clock generator
 */
void _mclk_init(void);

/**
 * \brief Initialize clock generator
 */
void _lpmcu_misc_regs_init(void);

/**
 * \brief Initialize clock generator
 */
void _pmc_init(void);

/**
 * \brief Set performance level
 *
 * \param[in] level The performance level to set
 */
void _set_performance_level(const uint8_t level);

/**
 * \brief Initialize the chip
 */
void _init_chip(void);

//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_INIT_H_INCLUDED */
