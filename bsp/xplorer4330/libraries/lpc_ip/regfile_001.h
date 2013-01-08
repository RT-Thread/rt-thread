/*
 * @brief Register File registers and control functions
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

#ifndef __REGFILE_001_H_
#define __REGFILE_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_REGFILE_001 IP: REGFILE register block and driver
 * @ingroup IP_Drivers
 * Register File
 * @{
 */

/**
 * @brief Register File register block structure
 */
typedef struct {
	__IO uint32_t REGFILE[64];	/*!< General purpose storage register */
} IP_REGFILE_001_T;

/**
 * @brief	Write value to General purpose registers
 * @param	pREG	: Pointer to regfile block
 * @param	index	: General purpose register index
 * @param	value	: Value to write
 * @return	None
 * Note: These General purpose registers can be used to store important
 * information when the main power supply is off. The value in these
 * registers is not affected by chip reset. These registers are usually
 * powered in the RTC power domain.
 */
STATIC INLINE void IP_REGFILE_Write(IP_REGFILE_001_T *pREG, int index, uint32_t value)
{
	pREG->REGFILE[index] = value;
}

/**
 * @brief	Read value from General purpose registers
 * @param	pREG	: Pointer to regfile block
 * @param	index	: General purpose register index
 * @return	Read value
 * These General purpose registers can be used to store important
 * information when the main power supply is off. The value in these
 * registers is not affected by chip reset. These registers are usually
 * powered in the RTC power domain.
 */
STATIC INLINE uint32_t IP_REGFILE_Read(IP_REGFILE_001_T *pREG, int index)
{
	return pREG->REGFILE[index];
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __REGFILE_001_H_ */
