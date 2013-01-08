/*
 * @brief Global Input Multiplexer Array control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __GIMA_001_H_
#define __GIMA_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_GIMA_001 IP: GIMA register block and driver
 * @ingroup IP_Drivers
 * Global Input Multiplexer Array
 * @{
 */

/**
 * @brief Global Input Multiplexer Array (GIMA) register block structure
 */
typedef struct {						/*!< GIMA Structure */
	__IO uint32_t  CAP0_IN[4][4];		/*!< Timer x CAP0_y capture input multiplexer (GIMA output ((x*4)+y)) */
	__IO uint32_t  CTIN_IN[8];			/*!< SCT CTIN_x capture input multiplexer (GIMA output (16+x)) */
	__IO uint32_t  VADC_TRIGGER_IN;		/*!< VADC trigger input multiplexer (GIMA output 24) */
	__IO uint32_t  EVENTROUTER_13_IN;	/*!< Event router input 13 multiplexer (GIMA output 25) */
	__IO uint32_t  EVENTROUTER_14_IN;	/*!< Event router input 14 multiplexer (GIMA output 26) */
	__IO uint32_t  EVENTROUTER_16_IN;	/*!< Event router input 16 multiplexer (GIMA output 27) */
	__IO uint32_t  ADCSTART0_IN;		/*!< ADC start0 input multiplexer (GIMA output 28) */
	__IO uint32_t  ADCSTART1_IN;		/*!< ADC start1 input multiplexer (GIMA output 29) */
} IP_GIMA_001_Type;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GIMA_001_H_ */
