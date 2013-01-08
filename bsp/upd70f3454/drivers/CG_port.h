/*
*******************************************************************************
* Copyright(C) NEC Electronics Corporation 2010
* All rights reserved by NEC Electronics Corporation.
* This program should be used on your own responsibility.
* NEC Electronics Corporation assumes no responsibility for any losses
* incurred by customers or third parties arising from the use of this file.
*
* This device driver was created by Applilet3 for V850ES/Jx3
* 32-Bit Single-Chip Microcontrollers
* Filename:	CG_port.h
* Abstract:	This file implements device driver for PORT module.
* APIlib:	Applilet3 for V850ES/Jx3 V2.01 [20 Apr 2010]
* Device:	uPD70F3746
* Compiler:	IAR Systems ICCV850
* Creation date:	6/26/2010
*******************************************************************************
*/

#ifndef _MDPORT_
#define _MDPORT_
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/* Port mode control register (PMCn.7 - PMCn.0) */
#define	_00_PMCn0_OPER_PORT		0x00U	/* Pn0 as port mode */
#define	_00_PMCn1_OPER_PORT		0x00U	/* Pn1 as port mode */
#define	_00_PMCn2_OPER_PORT		0x00U	/* Pn2 as port mode */
#define	_00_PMCn3_OPER_PORT		0x00U	/* Pn3 as port mode */
#define	_00_PMCn4_OPER_PORT		0x00U	/* Pn4 as port mode */
#define	_00_PMCn5_OPER_PORT		0x00U	/* Pn5 as port mode */
#define	_00_PMCn6_OPER_PORT		0x00U	/* Pn6 as port mode */
#define	_00_PMCn7_OPER_PORT		0x00U	/* Pn7 as port mode */
#define	_01_PMCn0_OPER_ALTER		0x01U	/* Pn0 as alternative mode */
#define	_02_PMCn1_OPER_ALTER		0x02U	/* Pn1 as alternative mode */
#define	_04_PMCn2_OPER_ALTER		0x04U	/* Pn2 as alternative mode */
#define	_08_PMCn3_OPER_ALTER		0x08U	/* Pn3 as alternative mode */
#define	_10_PMCn4_OPER_ALTER		0x10U	/* Pn4 as alternative mode */
#define	_20_PMCn5_OPER_ALTER		0x20U	/* Pn5 as alternative mode */
#define	_40_PMCn6_OPER_ALTER		0x40U	/* Pn6 as alternative mode */
#define	_80_PMCn7_OPER_ALTER		0x80U	/* Pn7 as alternative mode */
#define	_00_PMCn0_OPER_OCD		0x00U	/* PMC0 for MINI2 */

/* Port mode register (PMn.7 - PMn.0) */
#define	_01_PMn0_MODE_INPUT		0x01U	/* Pn0 as input mode */
#define	_02_PMn1_MODE_INPUT		0x02U	/* Pn1 as input mode */
#define	_04_PMn2_MODE_INPUT		0x04U	/* Pn2 as input mode */
#define	_08_PMn3_MODE_INPUT		0x08U	/* Pn3 as input mode */
#define	_10_PMn4_MODE_INPUT		0x10U	/* Pn4 as input mode */
#define	_20_PMn5_MODE_INPUT		0x20U	/* Pn5 as input mode */
#define	_40_PMn6_MODE_INPUT		0x40U	/* Pn6 as input mode */
#define	_80_PMn7_MODE_INPUT		0x80U	/* Pn7 as input mode */
#define	_00_PMn0_MODE_OUTPUT		0x00U	/* Pn0 as output mode */
#define	_00_PMn1_MODE_OUTPUT		0x00U	/* Pn1 as output mode */
#define	_00_PMn2_MODE_OUTPUT		0x00U	/* Pn2 as output mode */
#define	_00_PMn3_MODE_OUTPUT		0x00U	/* Pn3 as output mode */
#define	_00_PMn4_MODE_OUTPUT		0x00U	/* Pn4 as output mode */
#define	_00_PMn5_MODE_OUTPUT		0x00U	/* Pn5 as output mode */
#define	_00_PMn6_MODE_OUTPUT		0x00U	/* Pn6 as output mode */
#define	_00_PMn7_MODE_OUTPUT		0x00U	/* Pn7 as output mode */
#define	_01_PMn0_MODE_UNUSED		0x01U	/* Pn0 as default mode */
#define	_02_PMn1_MODE_UNUSED		0x02U	/* Pn1 as default mode */
#define	_04_PMn2_MODE_UNUSED		0x04U	/* Pn2 as default mode */
#define	_08_PMn3_MODE_UNUSED		0x08U	/* Pn3 as default mode */
#define	_10_PMn4_MODE_UNUSED		0x10U	/* Pn4 as default mode */
#define	_20_PMn5_MODE_UNUSED		0x20U	/* Pn5 as default mode */
#define	_40_PMn6_MODE_UNUSED		0x40U	/* Pn6 as default mode */
#define	_80_PMn7_MODE_UNUSED		0x80U	/* Pn7 as default mode */
#define	_00_PMn0_MODE_OCD		0x00U	/* PMC0 for MINI2 */

/* Port register (Pn.7 - Pn.0) */
#define	_00_Pn0_OUTPUT_0		0x00U	/* Pn0 output 0 */
#define	_00_Pn1_OUTPUT_0		0x00U	/* Pn1 output 0 */
#define	_00_Pn2_OUTPUT_0		0x00U	/* Pn2 output 0 */
#define	_00_Pn3_OUTPUT_0		0x00U	/* Pn3 output 0 */
#define	_00_Pn4_OUTPUT_0		0x00U	/* Pn4 output 0 */
#define	_00_Pn5_OUTPUT_0		0x00U	/* Pn5 output 0 */
#define	_00_Pn6_OUTPUT_0		0x00U	/* Pn6 output 0 */
#define	_00_Pn7_OUTPUT_0		0x00U	/* Pn7 output 0 */
#define	_01_Pn0_OUTPUT_1		0x01U	/* Pn0 output 1 */
#define	_02_Pn1_OUTPUT_1		0x02U	/* Pn1 output 1 */
#define	_04_Pn2_OUTPUT_1		0x04U	/* Pn2 output 1 */
#define	_08_Pn3_OUTPUT_1		0x08U	/* Pn3 output 1 */
#define	_10_Pn4_OUTPUT_1		0x10U	/* Pn4 output 1 */
#define	_20_Pn5_OUTPUT_1		0x20U	/* Pn5 output 1 */
#define	_40_Pn6_OUTPUT_1		0x40U	/* Pn6 output 1 */
#define	_80_Pn7_OUTPUT_1		0x80U	/* Pn7 output 1 */

/* Function register resistor (PFn.7 - PFn.0) */
#define	_00_PFn0_FUN_NORMAL		0x00U	/* Pn0 normal output */
#define	_00_PFn1_FUN_NORMAL		0x00U	/* Pn1 normal output */
#define	_00_PFn2_FUN_NORMAL		0x00U	/* Pn2 normal output */
#define	_00_PFn3_FUN_NORMAL		0x00U	/* Pn3 normal output */
#define	_00_PFn4_FUN_NORMAL		0x00U	/* Pn4 normal output */
#define	_00_PFn5_FUN_NORMAL		0x00U	/* Pn5 normal output */
#define	_00_PFn6_FUN_NORMAL		0x00U	/* Pn6 normal output */
#define	_00_PFn7_FUN_NORMAL		0x00U	/* Pn7 normal output */
#define	_01_PFn0_FUN_OPEN		0x01U	/* Pn0 open-drain output */
#define	_02_PFn1_FUN_OPEN		0x02U	/* Pn1 open-drain output */
#define	_04_PFn2_FUN_OPEN		0x04U	/* Pn2 open-drain output */
#define	_08_PFn3_FUN_OPEN		0x08U	/* Pn3 open-drain output */
#define	_10_PFn4_FUN_OPEN		0x10U	/* Pn4 open-drain output */
#define	_20_PFn5_FUN_OPEN		0x20U	/* Pn5 open-drain output */
#define	_40_PFn6_FUN_OPEN		0x40U	/* Pn6 open-drain output */
#define	_80_PFn7_FUN_OPEN		0x80U	/* Pn7 open-drain output */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define	_80_PM0_DEFAULT			0x80U	/* PM0 default value */
#define	_FC_PM1_DEFAULT			0xFCU	/* PM1 default value */
#define	_FC_PM3H_DEFAULT		0xFCU	/* PM3H default value */
#define	_F8_PM4_DEFAULT			0xF8U	/* PM4 default value */
#define	_C0_PM5_DEFAULT			0xC0U	/* PM5 default value */
#define	_FC_PM8_DEFAULT			0xFCU	/* PM8 default value */
#define	_F0_PMCD_DEFAULT		0xF0U	/* PMCD default value */
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void PORT_Init(void);
void led_on(void);
void led_off(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
