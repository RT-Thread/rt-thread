/*
 * @brief Power Management Controller registers and control functions
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

#ifndef __PMC_001_H_
#define __PMC_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_PMC_001 IP: PMC register block and driver
 * @ingroup IP_Drivers
 * Power Management Controller
 * @{
 */

/**
 * @brief Power Management Controller register block structure
 */
typedef struct {						/*!< PMC Structure          */
	__IO uint32_t  PD0_SLEEP0_HW_ENA;	/*!< Hardware sleep event enable register */
	__I  uint32_t  RESERVED0[6];
	__IO uint32_t  PD0_SLEEP0_MODE;		/*!< Sleep power mode register */
} IP_PMC_001_Type;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __PMC_001_H_ */
