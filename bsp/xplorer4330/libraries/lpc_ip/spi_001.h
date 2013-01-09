/*
 * @brief SPI registers and control functions
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

#ifndef __SPI_001_H_
#define __SPI_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_SPI_001 IP: SPI register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief SPI register block structure
 */
typedef struct {					/*!< SPI Structure          */
	__IO uint32_t  CR;				/*!< SPI Control Register. This register controls the operation of the SPI. */
	__I  uint32_t  SR;				/*!< SPI Status Register. This register shows the status of the SPI. */
	__IO uint32_t  DR;				/*!< SPI Data Register. This bi-directional register provides the transmit and receive data for the SPI. Transmit data is provided to the SPI0 by writing to this register. Data received by the SPI0 can be read from this register. */
	__IO uint32_t  CCR;				/*!< SPI Clock Counter Register. This register controls the frequency of a master's SCK0. */
	__I  uint32_t  RESERVED0[3];
	__IO uint32_t  INT;				/*!< SPI Interrupt Flag. This register contains the interrupt flag for the SPI interface. */
} IP_SPI_001_Type;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_001_H_ */
