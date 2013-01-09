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
* Filename:	CG_timer.h
* Abstract:	This file implements device driver for Timer module.
* APIlib:	Applilet3 for V850ES/Jx3 V2.01 [20 Apr 2010]
* Device:	uPD70F3746
* Compiler:	IAR Systems ICCV850
* Creation date:	6/26/2010
*******************************************************************************
*/

#ifndef _MDTIMER_
#define _MDTIMER_
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/* 
	TMP control register 0 (TPnCTL0)
*/
/* TMP operation control (TPnCE) */
#define	_00_TMP_OPERATION_DISABLE		0x00U	/* disable internal operating clock operation (asynchronously reset TMPn) */
#define	_80_TMP_OPERATION_ENABLE		0x80U	/* enable internal operating clock operation */
/* Internal count clock selection (TPnCKS2 - TPnCKS0) */
#define	_00_TMP_INTERNAL_CLOCK0			0x00U	/* fXX */
#define	_01_TMP_INTERNAL_CLOCK1			0x01U	/* fXX/2 */
#define	_02_TMP_INTERNAL_CLOCK2			0x02U	/* fXX/2^2 */
#define	_03_TMP_INTERNAL_CLOCK3			0x03U	/* fXX/2^3 */
#define	_04_TMP_INTERNAL_CLOCK4			0x04U	/* fXX/2^4 */
#define	_05_TMP_INTERNAL_CLOCK5			0x05U	/* fXX/2^5 */
#define	_06_TMP_INTERNAL_CLOCK6			0x06U	/* fXX/2^6 or fXX/2^8 */
#define	_07_TMP_INTERNAL_CLOCK7			0x07U	/* fXX/2^7 or fXX/2^9 */

/* 
	TMP control register 1 (TPnCTL1)
*/
/* Software trigger control (TPnEST) */
#define	_00_TMP_SOFTTRIGGER_OFF			0x00U	/* no operation */
#define	_40_TMP_SOFTTRIGGER_ON			0x40U	/* in one-shot pulse mode: One-shot pulse software trigger */
											/* in external trigger pulse output mode: Pulse output software trigger */
/* Count clock selection (TPnEEE) */
#define	_00_TMP_INTERNAL_CLOCK			0x00U	/* use the internal clock (clock selected with bits TPnCKS2 to TPnCKS0) */
#define	_20_TMP_EXTERNAL_CLOCK			0x20U	/* use the external clock from the TIPn0 input pin */ 
/* Timer mode selection (TPnMD2 - TPnMD0) */
#define	_00_TMP_MODE_INTERVAL			0x00U	/* interval timer mode */
#define	_01_TMP_MODE_EXTERNALCOUNT		0x01U	/* external event counter mode */
#define	_02_TMP_MODE_EXTERNALTRG		0x02U	/* external trigger pulse output mode */
#define	_03_TMP_MODE_ONESHOT			0x03U	/* one-shot pulse mode */
#define	_04_TMP_MODE_PWM			0x04U	/* PWM mode */
#define	_05_TMP_MODE_FREERUNNING		0x05U	/* free-running mode */
#define	_06_TMP_MODE_PULSEMEASURE		0x06U	/* pulse width measurement mode */

/* 
	TMP I/O control register 0 (TPnIOC0)
*/
/* TOPn0 pin output level setting (TPnOL0) */
#define	_00_TMP_OUTPUT0_NORMAL			0x00U	/* normal output */
#define	_02_TMP_OUTPUT0_INVERTED		0x02U	/* inverted output */
/* TOPn0 pin output setting (TPnOE0) */
#define	_00_TMP_OUTPUT0_DISABLE			0x00U	/* disable timer output */
#define	_01_TMP_OUTPUT0_ENABLE			0x01U	/* enable timer output (TOPn0 pin outputs pulses) */
/* TOPn1 pin output level setting (TPnOL1) */
#define	_00_TMP_OUTPUT1_NORMAL			0x00U	/* normal output */
#define	_08_TMP_OUTPUT1_INVERTED		0x08U	/* inverted output */
/* TOPn1 pin output setting (TPnOE1) */
#define	_00_TMP_OUTPUT1_DISABLE			0x00U	/* disable timer output */
#define	_04_TMP_OUTPUT1_ENABLE			0x04U	/* enable timer output (TOPn1 pin outputs pulses) */

/* 
	TMP I/O control register 1 (TPnIOC1)
*/
/* Capture trigger input signal (TIPn1 pin) valid edge setting (TPnIS3,TPnIS2) */
#define	_00_TMP_INPUT1_EDGE_NONE		0x00U	/* detect no edge (capture operation is invalid) */
#define	_04_TMP_INPUT1_EDGE_RISING		0x04U	/* detection of rising edge */
#define	_08_TMP_INPUT1_EDGE_FALLING		0x08U	/* detection of falling edge */
#define	_0C_TMP_INPUT1_EDGE_BOTH		0x0CU	/* detection of both edges */
/* Capture trigger input signal (TIPn0 pin) valid edge setting (TPnIS1,TPnIS0) */
#define	_00_TMP_INPUT0_EDGE_NONE		0x00U	/* detect no edge (capture operation is invalid) */
#define	_01_TMP_INPUT0_EDGE_RISING		0x01U	/* detection of rising edge */
#define	_02_TMP_INPUT0_EDGE_FALLING		0x02U	/* detection of falling edge */
#define	_03_TMP_INPUT0_EDGE_BOTH		0x03U	/* detection of both edges */

/* 
	TMP I/O control register 2 (TPnIOC2)
*/
/* External event count input signal (TIPn0 pin) valid edge setting (TPnEES1,TPnEES0) */
#define	_00_TMP_EXTCOUNT_EDGE_NONE		0x00U	/* detect no edge (external event count is invalid) */
#define	_04_TMP_EXTCOUNT_EDGE_RISING		0x04U	/* detection of rising edge */
#define	_08_TMP_EXTCOUNT_EDGE_FALLING		0x08U	/* detection of falling edge */
#define	_0C_TMP_EXTCOUNT_EDGE_BOTH		0x0CU	/* detection of both edges */
/* External trigger input signal (TIPn0 pin) valid edge setting (TPnETS1,TPnETS0) */
#define	_00_TMP_EXTTRIGGER_EDGE_NONE		0x00U	/* detect no edge (external trigger is invalid) */
#define	_01_TMP_EXTTRIGGER_EDGE_RISING		0x01U	/* detection of rising edge */
#define	_02_TMP_EXTTRIGGER_EDGE_FALLING		0x02U	/* detection of falling edge */
#define	_03_TMP_EXTTRIGGER_EDGE_BOTH		0x03U	/* detection of both edges */

/* 
	TMP option register 0 (TPnOPT0)
*/
/* TPnCCR1 register capture/compare selection (TPnCCS1) */
#define	_00_TMP_CCR1_COMPARE			0x00U	/* compare register */
#define	_20_TMP_CCR1_CAPTURE			0x20U	/* capture register */
/* TPnCCR0 register capture/compare selection (TPnCCS0) */
#define	_00_TMP_CCR0_COMPARE			0x00U	/* compare register */
#define	_10_TMP_CCR0_CAPTURE			0x10U	/* capture register */
/* TMPn overflow detection flag (TPnOVF) */
#define _01_TMP_OVERFLOW_OCCUR			0x01U	/* overflow occurred */
#define _00_TMP_OVERFLOW_CLEAR			0x00U	/* clear overflow */

/* 
	TMQ0 control register 0 (TQ0CTL0)
*/
/* TMQ operation control (TQ0CE) */
#define	_00_TMQ_OPERATION_DISABLE		0x00U	/* disable internal operating clock operation (asynchronously reset TMQ0) */
#define	_80_TMQ_OPERATION_ENABLE		0x80U	/* enable internal operating clock operation */
/* Internal count clock selection (TQ0CKS2 - TQ0CKS0) */
#define	_00_TMQ_INTERNAL_CLOCK0			0x00U	/* fXX */
#define	_01_TMQ_INTERNAL_CLOCK1			0x01U	/* fXX/2 */
#define	_02_TMQ_INTERNAL_CLOCK2			0x02U	/* fXX/2^2 */
#define	_03_TMQ_INTERNAL_CLOCK3			0x03U	/* fXX/2^3 */
#define	_04_TMQ_INTERNAL_CLOCK4			0x04U	/* fXX/2^4 */
#define	_05_TMQ_INTERNAL_CLOCK5			0x05U	/* fXX/2^5 */
#define	_06_TMQ_INTERNAL_CLOCK6			0x06U	/* fXX/2^6 */
#define	_07_TMQ_INTERNAL_CLOCK7			0x07U	/* fXX/2^7 */

/* 
	TMQ0 control register 1 (TQ0CTL1)
*/
/* Software trigger control (TQ0EST) */
#define	_00_TMQ_SOFTTRIGGER_OFF			0x00U	/* no operation */
#define	_40_TMQ_SOFTTRIGGER_ON			0x40U	/* in one-shot pulse mode: One-shot pulse software trigger */
											/* in external trigger pulse output mode: Pulse output software trigger */
/* Count clock selection (TQ0EEE) */
#define	_00_TMQ_INTERNAL_CLOCK			0x00U	/* use the internal clock (clock selected with bits TQ0CKS2 to TQ0CKS0) */
#define	_20_TMQ_EXTERNAL_CLOCK			0x20U	/* use the external clock from the TIQ00 input pin */ 
/* Timer mode selection (TQ0MD2 - TQ0MD0) */
#define	_00_TMQ_MODE_INTERVAL			0x00U	/* interval timer mode */
#define	_01_TMQ_MODE_EXTERNALCOUNT		0x01U	/* external event counter mode */
#define	_02_TMQ_MODE_EXTERNALTRG		0x02U	/* external trigger pulse output mode */
#define	_03_TMQ_MODE_ONESHOT			0x03U	/* one-shot pulse mode */
#define	_04_TMQ_MODE_PWM			0x04U	/* PWM mode */
#define	_05_TMQ_MODE_FREERUNNING		0x05U	/* free-running mode */
#define	_06_TMQ_MODE_PULSEMEASURE		0x06U	/* pulse width measurement mode */

/* 
	TMQ0 I/O control register 0 (TQ0IOC0)
*/
/* TOQ00 pin output level setting (TQ0OL0) */
#define	_00_TMQ_OUTPUT0_NORMAL			0x00U	/* normal output */
#define	_02_TMQ_OUTPUT0_INVERTED		0x02U	/* inverted output */
/* TOQ00 pin output setting (TQ0OE0) */
#define	_00_TMQ_OUTPUT0_DISABLE			0x00U	/* disable timer output */
#define	_01_TMQ_OUTPUT0_ENABLE			0x01U	/* enable timer output (TOQ00 pin outputs pulses) */
/* TOQ01 pin output level setting (TQ0OL1) */
#define	_00_TMQ_OUTPUT1_NORMAL			0x00U	/* normal output */
#define	_08_TMQ_OUTPUT1_INVERTED		0x08U	/* inverted output */
/* TOQ01 pin output setting (TQ0OE1) */
#define	_00_TMQ_OUTPUT1_DISABLE			0x00U	/* disable timer output */
#define	_04_TMQ_OUTPUT1_ENABLE			0x04U	/* enable timer output (TOQ01 pin outputs pulses) */
/* TOQ02 pin output level setting (TQ0OL2) */
#define	_00_TMQ_OUTPUT2_NORMAL			0x00U	/* normal output */
#define	_20_TMQ_OUTPUT2_INVERTED		0x20U	/* inverted output */
/* TOQ02 pin output setting (TQ0OE2) */
#define	_00_TMQ_OUTPUT2_DISABLE			0x00U	/* disable timer output */
#define	_10_TMQ_OUTPUT2_ENABLE			0x10U	/* enable timer output (TOQ02 pin outputs pulses) */
/* TOQ03 pin output level setting (TQ0OL3) */
#define	_00_TMQ_OUTPUT3_NORMAL			0x00U	/* normal output */
#define	_80_TMQ_OUTPUT3_INVERTED		0x80U	/* inverted output */
/* TOQ03 pin output setting (TQ0OE3) */
#define	_00_TMQ_OUTPUT3_DISABLE			0x00U	/* disable timer output */
#define	_40_TMQ_OUTPUT3_ENABLE			0x40U	/* enable timer output (TOQ03 pin outputs pulses) */

/* 
	TMQ0 I/O control register 1 (TQ0IOC1)
*/
/* Capture trigger input signal (TIQ00 pin) valid edge setting (TQ0IS1,TQ0IS0) */
#define	_00_TMQ_INPUT0_EDGE_NONE		0x00U	/* detect no edge (capture operation is invalid) */
#define	_01_TMQ_INPUT0_EDGE_RISING		0x01U	/* detection of rising edge */
#define	_02_TMQ_INPUT0_EDGE_FALLING		0x02U	/* detection of falling edge */
#define	_03_TMQ_INPUT0_EDGE_BOTH		0x03U	/* detection of both edges */
/* Capture trigger input signal (TIQ01 pin) valid edge setting (TQ0IS3,TQ0IS2) */
#define	_00_TMQ_INPUT1_EDGE_NONE		0x00U	/* detect no edge (capture operation is invalid) */
#define	_04_TMQ_INPUT1_EDGE_RISING		0x04U	/* detection of rising edge */
#define	_08_TMQ_INPUT1_EDGE_FALLING		0x08U	/* detection of falling edge */
#define	_0C_TMQ_INPUT1_EDGE_BOTH		0x0CU	/* detection of both edges */
/* Capture trigger input signal (TIQ02 pin) valid edge setting (TQ0IS5,TQ0IS4) */
#define	_00_TMQ_INPUT2_EDGE_NONE		0x00U	/* detect no edge (capture operation is invalid) */
#define	_10_TMQ_INPUT2_EDGE_RISING		0x10U	/* detection of rising edge */
#define	_20_TMQ_INPUT2_EDGE_FALLING		0x20U	/* detection of falling edge */
#define	_30_TMQ_INPUT2_EDGE_BOTH		0x30U	/* detection of both edges */
/* Capture trigger input signal (TIQ03 pin) valid edge setting (TQ0IS7,TQ0IS6) */
#define	_00_TMQ_INPUT3_EDGE_NONE		0x00U	/* detect no edge (capture operation is invalid) */
#define	_40_TMQ_INPUT3_EDGE_RISING		0x40U	/* detection of rising edge */
#define	_80_TMQ_INPUT3_EDGE_FALLING		0x80U	/* detection of falling edge */
#define	_C0_TMQ_INPUT3_EDGE_BOTH		0xC0U	/* detection of both edges */

/* 
	TMQ0 I/O control register 2 (TQ0IOC2)
*/
/* External event count input signal (TIQ00 pin) valid edge setting (TQ0EES1,TQ0EES0) */
#define	_00_TMQ_EXTCOUNT_EDGE_NONE		0x00U	/* detect no edge (external event count is invalid) */
#define	_04_TMQ_EXTCOUNT_EDGE_RISING		0x04U	/* detection of rising edge */
#define	_08_TMQ_EXTCOUNT_EDGE_FALLING		0x08U	/* detection of falling edge */
#define	_0C_TMQ_EXTCOUNT_EDGE_BOTH		0x0CU	/* detection of both edges */
/* External trigger input signal (TIQ00 pin) valid edge setting (TQ0ETS1,TQ0ETS0) */
#define	_00_TMQ_EXTTRIGGER_EDGE_NONE		0x00U	/* detect no edge (external trigger is invalid) */
#define	_01_TMQ_EXTTRIGGER_EDGE_RISING		0x01U	/* detection of rising edge */
#define	_02_TMQ_EXTTRIGGER_EDGE_FALLING		0x02U	/* detection of falling edge */
#define	_03_TMQ_EXTTRIGGER_EDGE_BOTH		0x03U	/* detection of both edges */

/* 
	TMQ0 option register 0 (TQ0OPT0)
*/
/* TQ0CCR3 register capture/compare selection (TQ0CCS3) */
#define	_00_TMQ_CCR3_COMPARE			0x00U	/* compare register */
#define	_80_TMQ_CCR3_CAPTURE			0x80U	/* capture register */
/* TQ0CCR2 register capture/compare selection (TQ0CCS2) */
#define	_00_TMQ_CCR2_COMPARE			0x00U	/* compare register */
#define	_40_TMQ_CCR2_CAPTURE			0x40U	/* capture register */
/* TQ0CCR1 register capture/compare selection (TQ0CCS1) */
#define	_00_TMQ_CCR1_COMPARE			0x00U	/* compare register */
#define	_20_TMQ_CCR1_CAPTURE			0x20U	/* capture register */
/* TQ0CCR0 register capture/compare selection (TQ0CCS0) */
#define	_00_TMQ_CCR0_COMPARE			0x00U	/* compare register */
#define	_10_TMQ_CCR0_CAPTURE			0x10U	/* capture register */
/* TMQ0 overflow detection flag (TQ0OVF) */
#define _01_TMQ_OVERFLOW_OCCUR			0x01U	/* overflow occurred */
#define _00_TMQ_OVERFLOW_CLEAR			0x00U	/* clear overflow */

/* 
	TMM0 control register 0 (TM0CTL0)
*/
/* TMM0 operation control (TM0CE) */
#define	_00_TMM_OPERATION_DISABLE		0x00U	/* disable internal operating clock operation (asynchronously reset TMM0) */
#define	_80_TMM_OPERATION_ENABLE		0x80U	/* enable internal operating clock operation */
/* Internal count clock selection (TM0CKS2 - TM0CKS0) */
#define	_00_TMM_INTERNAL_CLOCK0			0x00U	/* fXX */
#define	_01_TMM_INTERNAL_CLOCK1			0x01U	/* fXX/2 */
#define	_02_TMM_INTERNAL_CLOCK2			0x02U	/* fXX/4 */
#define	_03_TMM_INTERNAL_CLOCK3			0x03U	/* fXX/64 */
#define	_04_TMM_INTERNAL_CLOCK4			0x04U	/* fXX/512 */
#define	_05_TMM_INTERNAL_CLOCK5			0x05U	/* INTWT */
#define	_06_TMM_INTERNAL_CLOCK6			0x06U	/* fR/8 */
#define	_07_TMM_INTERNAL_CLOCK7			0x07U	/* fXT */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
/* TMP0 compare register 0 (TP0CCR0)*/
#define _9C3F_TMP0_CCR0_VALUE			0x9C3FU
enum TMChannel
{
	TMCHANNEL0, TMCHANNEL1, TMCHANNEL2, TMCHANNEL3
};
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void TAB0_Init(void);
void TAB0_Start(void);
void TAB0_Stop(void);
MD_STATUS TAB0_ChangeTimerCondition(USHORT *array_reg, UCHAR array_num);
__interrupt void MD_INTTP0CC0(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
