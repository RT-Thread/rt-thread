/*
 * @brief CCAN registers and control functions
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

#ifndef __CCAN_001_H_
#define __CCAN_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_CCAN_001 IP: CCAN register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief CCAN Controller Area Network register block structure
 */
typedef struct {						/*!< C_CAN Structure       */
	__IO uint32_t CNTL;					/*!< CAN control            */
	__IO uint32_t STAT;					/*!< Status register        */
	__I  uint32_t EC;					/*!< Error counter          */
	__IO uint32_t BT;					/*!< Bit timing register    */
	__I  uint32_t INT;					/*!< Interrupt register     */
	__IO uint32_t TEST;					/*!< Test register          */
	__IO uint32_t BRPE;					/*!< Baud rate prescaler extension register */
	__I  uint32_t  RESERVED0;
	__IO uint32_t IF1_CMDREQ;			/*!< Message interface command request  */
	union {
		__IO uint32_t IF1_CMDMSK_R;		/*!< Message interface command mask (read direction) */
		__IO uint32_t IF1_CMDMSK_W;		/*!< Message interface command mask (write direction) */
	};

	__IO uint32_t IF1_MSK1;				/*!< Message interface mask 1 */
	__IO uint32_t IF1_MSK2;				/*!< Message interface 1 mask 2 */
	__IO uint32_t IF1_ARB1;				/*!< Message interface 1 arbitration 1 */
	__IO uint32_t IF1_ARB2;				/*!< Message interface 1 arbitration 2 */
	__IO uint32_t IF1_MCTRL;			/*!< Message interface 1 message control */
	__IO uint32_t IF1_DA1;				/*!< Message interface data A1 */
	__IO uint32_t IF1_DA2;				/*!< Message interface 1 data A2 */
	__IO uint32_t IF1_DB1;				/*!< Message interface 1 data B1 */
	__IO uint32_t IF1_DB2;				/*!< Message interface 1 data B2 */
	__I  uint32_t  RESERVED1[13];
	__IO uint32_t IF2_CMDREQ;			/*!< Message interface command request  */
	union {
		__IO uint32_t IF2_CMDMSK_R;		/*!< Message interface command mask (read direction) */
		__IO uint32_t IF2_CMDMSK_W;		/*!< Message interface command mask (write direction) */
	};

	__IO uint32_t IF2_MSK1;				/*!< Message interface mask 1 */
	__IO uint32_t IF2_MSK2;				/*!< Message interface 1 mask 2 */
	__IO uint32_t IF2_ARB1;				/*!< Message interface 1 arbitration 1 */
	__IO uint32_t IF2_ARB2;				/*!< Message interface 1 arbitration 2 */
	__IO uint32_t IF2_MCTRL;			/*!< Message interface 1 message control */
	__IO uint32_t IF2_DA1;				/*!< Message interface data A1 */
	__IO uint32_t IF2_DA2;				/*!< Message interface 1 data A2 */
	__IO uint32_t IF2_DB1;				/*!< Message interface 1 data B1 */
	__IO uint32_t IF2_DB2;				/*!< Message interface 1 data B2 */
	__I  uint32_t  RESERVED2[21];
	__I  uint32_t TXREQ1;				/*!< Transmission request 1 */
	__I  uint32_t TXREQ2;				/*!< Transmission request 2 */
	__I  uint32_t  RESERVED3[6];
	__I  uint32_t ND1;					/*!< New data 1             */
	__I  uint32_t ND2;					/*!< New data 2             */
	__I  uint32_t  RESERVED4[6];
	__I  uint32_t IR1;					/*!< Interrupt pending 1    */
	__I  uint32_t IR2;					/*!< Interrupt pending 2    */
	__I  uint32_t  RESERVED5[6];
	__I  uint32_t MSGV1;				/*!< Message valid 1        */
	__I  uint32_t MSGV2;				/*!< Message valid 2        */
	__I  uint32_t  RESERVED6[6];
	__IO uint32_t CLKDIV;				/*!< CAN clock divider register */
} IP_CCAN_001_Type;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CCAN_001_H_ */
