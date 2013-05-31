/** @file reg_efc.h
*   @brief EFC Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_EFC_H__
#define __REG_EFC_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Efc Register Frame Definition */
/** @struct efcBase
*   @brief Efc Register Frame Definition
*
*   This type is used to access the Efc Registers.
*/
/** @typedef efcBASE_t
*   @brief Efc Register Frame Type Definition
*
*   This type is used to access the Efc Registers.
*/
typedef volatile struct efcBase
{
	uint32 INSTRUCTION;    			/* 0x0	INSTRUCTION AN DUMPWORD REGISTER	*/
	uint32 ADDRESS;			    	/* 0x4 ADDRESS REGISTER    					*/
	uint32 DATA_UPPER;			    /* 0x8 DATA UPPER REGISTER    				*/
	uint32 DATA_LOWER;				/* 0xc DATA LOWER REGISTER    				*/
	uint32 SYSTEM_CONFIG;				/* 0x10 SYSTEM CONFIG REGISTER    			*/
	uint32 SYSTEM_STATUS;				/* 0x14 SYSTEM STATUS REGISTER    			*/
	uint32 ACCUMULATOR;				/* 0x18 ACCUMULATOR REGISTER    			*/
	uint32 BOUNDARY;			    	/* 0x1C BOUNDARY REGISTER 					*/
	uint32 KEY_FLAG;			    	/* 0x20 KEY FLAG REGISTER    				*/
	uint32 KEY;			        	/* 0x24	KEY REGISTER 						*/
	uint32   rsvd1;			        /* 0x28	RESERVED 							*/
	uint32 PINS;				        /* 0x2C  PINS REGISTER						*/
	uint32 CRA;				        /* 0x30  CRA								*/
	uint32 READ;				        /* 0x34 READ REGISTER						*/
	uint32 PROGRAMME;				    /* 0x38 PROGRAMME REGISTER					*/
	uint32 ERROR;				        /* 0x3C	ERROR STATUS REGISTER				*/
	uint32 SINGLE_BIT;				/* 0x40	SINGLE BIT ERROR 					*/
	uint32 TWO_BIT_ERROR;				/* 0x44	DOUBLE BIT ERROR 					*/
	uint32 SELF_TEST_CYCLES;			/* 0x48	SELF TEST CYCLEX					*/
	uint32 SELF_TEST_SIGN;			/* 0x4C SELF TEST SIGNATURE					*/
} efcBASE_t;

#define efcREG   ((efcBASE_t *)0xFFF8C000U)
/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
