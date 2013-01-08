/*
 * File      : at91sam7s.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      first version
 */

#ifndef __AT91SAM7S_H__
#define __AT91SAM7S_H__

#ifdef __cplusplus
extern "C" {
#endif

#define AT91_REG *(volatile unsigned int *)		/* Hardware register definition */

/* ========== Register definition for TC0 peripheral ==========  */
#define AT91C_TC0_SR		(AT91_REG(0xFFFA0020)) /* TC0 Status Register */
#define AT91C_TC0_RC		(AT91_REG(0xFFFA001C)) /* TC0 Register C */
#define AT91C_TC0_RB		(AT91_REG(0xFFFA0018)) /* TC0 Register B */
#define AT91C_TC0_CCR		(AT91_REG(0xFFFA0000)) /* TC0 Channel Control Register */
#define AT91C_TC0_CMR		(AT91_REG(0xFFFA0004)) /* TC0 Channel Mode Register (Capture Mode / Waveform Mode) */
#define AT91C_TC0_IER		(AT91_REG(0xFFFA0024)) /* TC0 Interrupt Enable Register */
#define AT91C_TC0_RA		(AT91_REG(0xFFFA0014)) /* TC0 Register A */
#define AT91C_TC0_IDR		(AT91_REG(0xFFFA0028)) /* TC0 Interrupt Disable Register */
#define AT91C_TC0_CV		(AT91_REG(0xFFFA0010)) /* TC0 Counter Value */
#define AT91C_TC0_IMR		(AT91_REG(0xFFFA002C)) /* TC0 Interrupt Mask Register */

/* ========== Register definition for TC1 peripheral ========== */
#define AT91C_TC1_RB		(AT91_REG(0xFFFA0058)) /* TC1 Register B */
#define AT91C_TC1_CCR		(AT91_REG(0xFFFA0040)) /* TC1 Channel Control Register */
#define AT91C_TC1_IER		(AT91_REG(0xFFFA0064)) /* TC1 Interrupt Enable Register */
#define AT91C_TC1_IDR		(AT91_REG(0xFFFA0068)) /* TC1 Interrupt Disable Register */
#define AT91C_TC1_SR		(AT91_REG(0xFFFA0060)) /* TC1 Status Register */
#define AT91C_TC1_CMR		(AT91_REG(0xFFFA0044)) /* TC1 Channel Mode Register (Capture Mode / Waveform Mode) */
#define AT91C_TC1_RA		(AT91_REG(0xFFFA0054)) /* TC1 Register A */
#define AT91C_TC1_RC		(AT91_REG(0xFFFA005C)) /* TC1 Register C */
#define AT91C_TC1_IMR		(AT91_REG(0xFFFA006C)) /* TC1 Interrupt Mask Register */
#define AT91C_TC1_CV		(AT91_REG(0xFFFA0050)) /* TC1 Counter Value */

/* ========== Register definition for TC2 peripheral ========== */
#define AT91C_TC2_CMR		(AT91_REG(0xFFFA0084)) /* TC2 Channel Mode Register (Capture Mode / Waveform Mode) */
#define AT91C_TC2_CCR		(AT91_REG(0xFFFA0080)) /* TC2 Channel Control Register */
#define AT91C_TC2_CV		(AT91_REG(0xFFFA0090)) /* TC2 Counter Value */
#define AT91C_TC2_RA		(AT91_REG(0xFFFA0094)) /* TC2 Register A */
#define AT91C_TC2_RB		(AT91_REG(0xFFFA0098)) /* TC2 Register B */
#define AT91C_TC2_IDR		(AT91_REG(0xFFFA00A8)) /* TC2 Interrupt Disable Register */
#define AT91C_TC2_IMR		(AT91_REG(0xFFFA00AC)) /* TC2 Interrupt Mask Register */
#define AT91C_TC2_RC		(AT91_REG(0xFFFA009C)) /* TC2 Register C */
#define AT91C_TC2_IER		(AT91_REG(0xFFFA00A4)) /* TC2 Interrupt Enable Register */
#define AT91C_TC2_SR		(AT91_REG(0xFFFA00A0)) /* TC2 Status Register */

/* ========== Register definition for PITC peripheral ========== */
#define AT91C_PITC_PIVR		(AT91_REG(0xFFFFFD38)) /* PITC Period Interval Value Register */
#define AT91C_PITC_PISR		(AT91_REG(0xFFFFFD34)) /* PITC Period Interval Status Register */
#define AT91C_PITC_PIIR		(AT91_REG(0xFFFFFD3C)) /* PITC Period Interval Image Register */
#define AT91C_PITC_PIMR		(AT91_REG(0xFFFFFD30)) /* PITC Period Interval Mode Register */

/* ========== Register definition for UDP peripheral ==========  */
#define AT91C_UDP_NUM		(AT91_REG(0xFFFB0000)) /* UDP Frame Number Register */
#define AT91C_UDP_STAT		(AT91_REG(0xFFFB0004)) /* UDP Global State Register */
#define AT91C_UDP_FADDR		(AT91_REG(0xFFFB0008)) /* UDP Function Address Register */
#define AT91C_UDP_IER		(AT91_REG(0xFFFB0010)) /* UDP Interrupt Enable Register */
#define AT91C_UDP_IDR		(AT91_REG(0xFFFB0014)) /* UDP Interrupt Disable Register */
#define AT91C_UDP_IMR		(AT91_REG(0xFFFB0018)) /* UDP Interrupt Mask Register */
#define AT91C_UDP_ISR		(AT91_REG(0xFFFB001C)) /* UDP Interrupt Status Register */
#define AT91C_UDP_ICR		(AT91_REG(0xFFFB0020)) /* UDP Interrupt Clear Register */
#define AT91C_UDP_RSTEP		(AT91_REG(0xFFFB0028)) /* UDP Reset Endpoint Register */
#define AT91C_UDP_CSR0		(AT91_REG(0xFFFB0030)) /* UDP Endpoint Control and Status Register */
#define AT91C_UDP_CSR(n)	(*(&AT91C_UDP_CSR0 + n))
#define AT91C_UDP_FDR0		(AT91_REG(0xFFFB0050)) /* UDP Endpoint FIFO Data Register */
#define AT91C_UDP_FDR(n)	(*(&AT91C_UDP_FDR0 + n))
#define AT91C_UDP_TXVC		(AT91_REG(0xFFFB0074)) /* UDP Transceiver Control Register */

/* ========== Register definition for US0 peripheral ========== */
#define AT91C_US0_CR		(AT91_REG(0xFFFC0000)) /* US0 Control Register */
#define AT91C_US0_MR		(AT91_REG(0xFFFC0004)) /* US0 Mode Register */
#define AT91C_US0_IER		(AT91_REG(0xFFFC0008)) /* US0 Interrupt Enable Register */
#define AT91C_US0_IDR		(AT91_REG(0xFFFC000C)) /* US0 Interrupt Disable Register */
#define AT91C_US0_IMR		(AT91_REG(0xFFFC0010)) /* US0 Interrupt Mask Register */
#define AT91C_US0_CSR		(AT91_REG(0xFFFC0014)) /* US0 Channel Status Register */
#define AT91C_US0_RHR		(AT91_REG(0xFFFC0018)) /* US0 Receiver Holding Register */
#define AT91C_US0_THR		(AT91_REG(0xFFFC001C)) /* US0 Transmitter Holding Register */
#define AT91C_US0_BRGR		(AT91_REG(0xFFFC0020)) /* US0 Baud Rate Generator Register */
#define AT91C_US0_RTOR		(AT91_REG(0xFFFC0024)) /* US0 Receiver Time-out Register */
#define AT91C_US0_TTGR		(AT91_REG(0xFFFC0028)) /* US0 Transmitter Time-guard Register */
#define AT91C_US0_NER		(AT91_REG(0xFFFC0044)) /* US0 Nb Errors Register */
#define AT91C_US0_FIDI		(AT91_REG(0xFFFC0040)) /* US0 FI_DI_Ratio Register */
#define AT91C_US0_IF		(AT91_REG(0xFFFC004C)) /* US0 IRDA_FILTER Register */

/* ========== Register definition for AIC peripheral ==========  */
#define AT91C_AIC_SMR0		(AT91_REG(0xFFFFF000)) /* AIC Source Mode Register */
#define AT91C_AIC_SMR(n)	(*(&AT91C_AIC_SMR0 + n))
#define AT91C_AIC_SVR0		(AT91_REG(0xFFFFF080)) /* AIC Source Vector Register */
#define AT91C_AIC_SVR(n)	(*(&AT91C_AIC_SVR0 + n))
#define AT91C_AIC_IVR		(AT91_REG(0xFFFFF100)) /* AIC Interrupt Vector Register */
#define AT91C_AIC_FVR		(AT91_REG(0xFFFFF104)) /* AIC FIQ Vector Register */
#define AT91C_AIC_ISR		(AT91_REG(0xFFFFF108)) /* AIC Interrupt Status Register */
#define AT91C_AIC_IPR		(AT91_REG(0xFFFFF10C)) /* AIC Interrupt Pending Register */
#define AT91C_AIC_IMR		(AT91_REG(0xFFFFF110)) /* AIC Interrupt Mask Register */
#define AT91C_AIC_CISR		(AT91_REG(0xFFFFF114)) /* AIC Core Interrupt Status Register */
#define AT91C_AIC_IECR		(AT91_REG(0xFFFFF120)) /* AIC Interrupt Enable Command Register */
#define AT91C_AIC_IDCR		(AT91_REG(0xFFFFF124)) /* AIC Interrupt Disable Command Register */
#define AT91C_AIC_ICCR		(AT91_REG(0xFFFFF128)) /* AIC Interrupt Clear Command Register */
#define AT91C_AIC_ISCR		(AT91_REG(0xFFFFF12C)) /* AIC Interrupt Set Command Register */
#define AT91C_AIC_EOICR		(AT91_REG(0xFFFFF130)) /* AIC End of Interrupt Command Register */
#define AT91C_AIC_SPU		(AT91_REG(0xFFFFF134)) /* AIC Spurious Vector Register */
#define AT91C_AIC_DCR		(AT91_REG(0xFFFFF138)) /* AIC Debug Control Register (Protect) */
#define AT91C_AIC_FFER		(AT91_REG(0xFFFFF140)) /* AIC Fast Forcing Enable Register */
#define AT91C_AIC_FFDR		(AT91_REG(0xFFFFF144)) /* AIC Fast Forcing Disable Register */
#define AT91C_AIC_FFSR		(AT91_REG(0xFFFFF148)) /* AIC Fast Forcing Status Register */


/* ========== Register definition for DBGU peripheral ==========  */
#define AT91C_DBGU_EXID		(AT91_REG(0xFFFFF244)) /* DBGU Chip ID Extension Register */
#define AT91C_DBGU_BRGR		(AT91_REG(0xFFFFF220)) /* DBGU Baud Rate Generator Register */
#define AT91C_DBGU_IDR		(AT91_REG(0xFFFFF20C)) /* DBGU Interrupt Disable Register */
#define AT91C_DBGU_CSR		(AT91_REG(0xFFFFF214)) /* DBGU Channel Status Register */
#define AT91C_DBGU_CIDR		(AT91_REG(0xFFFFF240)) /* DBGU Chip ID Register */
#define AT91C_DBGU_MR		(AT91_REG(0xFFFFF204)) /* DBGU Mode Register */
#define AT91C_DBGU_IMR		(AT91_REG(0xFFFFF210)) /* DBGU Interrupt Mask Register */
#define AT91C_DBGU_CR		(AT91_REG(0xFFFFF200)) /* DBGU Control Register */
#define AT91C_DBGU_FNTR		(AT91_REG(0xFFFFF248)) /* DBGU Force NTRST Register */
#define AT91C_DBGU_THR		(AT91_REG(0xFFFFF21C)) /* DBGU Transmitter Holding Register */
#define AT91C_DBGU_RHR		(AT91_REG(0xFFFFF218)) /* DBGU Receiver Holding Register */
#define AT91C_DBGU_IER		(AT91_REG(0xFFFFF208)) /* DBGU Interrupt Enable Register */

/* ========== Register definition for PIO peripheral ========== */
#define AT91C_PIO_ODR		(AT91_REG(0xFFFFF414)) /* PIOA Output Disable Registerr */
#define AT91C_PIO_SODR		(AT91_REG(0xFFFFF430)) /* PIOA Set Output Data Register */
#define AT91C_PIO_ISR		(AT91_REG(0xFFFFF44C)) /* PIOA Interrupt Status Register */
#define AT91C_PIO_ABSR		(AT91_REG(0xFFFFF478)) /* PIOA AB Select Status Register */
#define AT91C_PIO_IER		(AT91_REG(0xFFFFF440)) /* PIOA Interrupt Enable Register */
#define AT91C_PIO_PPUDR		(AT91_REG(0xFFFFF460)) /* PIOA Pull-up Disable Register */
#define AT91C_PIO_IMR		(AT91_REG(0xFFFFF448)) /* PIOA Interrupt Mask Register */
#define AT91C_PIO_PER		(AT91_REG(0xFFFFF400)) /* PIOA PIO Enable Register */
#define AT91C_PIO_IFDR		(AT91_REG(0xFFFFF424)) /* PIOA Input Filter Disable Register */
#define AT91C_PIO_OWDR		(AT91_REG(0xFFFFF4A4)) /* PIOA Output Write Disable Register */
#define AT91C_PIO_MDSR		(AT91_REG(0xFFFFF458)) /* PIOA Multi-driver Status Register */
#define AT91C_PIO_IDR		(AT91_REG(0xFFFFF444)) /* PIOA Interrupt Disable Register */
#define AT91C_PIO_ODSR		(AT91_REG(0xFFFFF438)) /* PIOA Output Data Status Register */
#define AT91C_PIO_PPUSR		(AT91_REG(0xFFFFF468)) /* PIOA Pull-up Status Register */
#define AT91C_PIO_OWSR		(AT91_REG(0xFFFFF4A8)) /* PIOA Output Write Status Register */
#define AT91C_PIO_BSR		(AT91_REG(0xFFFFF474)) /* PIOA Select B Register */
#define AT91C_PIO_OWER		(AT91_REG(0xFFFFF4A0)) /* PIOA Output Write Enable Register */
#define AT91C_PIO_IFER		(AT91_REG(0xFFFFF420)) /* PIOA Input Filter Enable Register */
#define AT91C_PIO_PDSR		(AT91_REG(0xFFFFF43C)) /* PIOA Pin Data Status Register */
#define AT91C_PIO_PPUER		(AT91_REG(0xFFFFF464)) /* PIOA Pull-up Enable Register */
#define AT91C_PIO_OSR		(AT91_REG(0xFFFFF418)) /* PIOA Output Status Register */
#define AT91C_PIO_ASR		(AT91_REG(0xFFFFF470)) /* PIOA Select A Register */
#define AT91C_PIO_MDDR		(AT91_REG(0xFFFFF454)) /* PIOA Multi-driver Disable Register */
#define AT91C_PIO_CODR		(AT91_REG(0xFFFFF434)) /* PIOA Clear Output Data Register */
#define AT91C_PIO_MDER		(AT91_REG(0xFFFFF450)) /* PIOA Multi-driver Enable Register */
#define AT91C_PIO_PDR		(AT91_REG(0xFFFFF404)) /* PIOA PIO Disable Register */
#define AT91C_PIO_IFSR		(AT91_REG(0xFFFFF428)) /* PIOA Input Filter Status Register */
#define AT91C_PIO_OER		(AT91_REG(0xFFFFF410)) /* PIOA Output Enable Register */
#define AT91C_PIO_PSR		(AT91_REG(0xFFFFF408)) /* PIOA PIO Status Register */

// ========== Register definition for PIOA peripheral ==========
#define AT91C_PIOA_IMR  	(AT91_REG(0xFFFFF448)) // (PIOA) Interrupt Mask Register
#define AT91C_PIOA_IER  	(AT91_REG(0xFFFFF440)) // (PIOA) Interrupt Enable Register
#define AT91C_PIOA_OWDR 	(AT91_REG(0xFFFFF4A4)) // (PIOA) Output Write Disable Register
#define AT91C_PIOA_ISR  	(AT91_REG(0xFFFFF44C)) // (PIOA) Interrupt Status Register
#define AT91C_PIOA_PPUDR 	(AT91_REG(0xFFFFF460)) // (PIOA) Pull-up Disable Register
#define AT91C_PIOA_MDSR 	(AT91_REG(0xFFFFF458)) // (PIOA) Multi-driver Status Register
#define AT91C_PIOA_MDER 	(AT91_REG(0xFFFFF450)) // (PIOA) Multi-driver Enable Register
#define AT91C_PIOA_PER  	(AT91_REG(0xFFFFF400)) // (PIOA) PIO Enable Register
#define AT91C_PIOA_PSR  	(AT91_REG(0xFFFFF408)) // (PIOA) PIO Status Register
#define AT91C_PIOA_OER  	(AT91_REG(0xFFFFF410)) // (PIOA) Output Enable Register
#define AT91C_PIOA_BSR  	(AT91_REG(0xFFFFF474)) // (PIOA) Select B Register
#define AT91C_PIOA_PPUER 	(AT91_REG(0xFFFFF464)) // (PIOA) Pull-up Enable Register
#define AT91C_PIOA_MDDR 	(AT91_REG(0xFFFFF454)) // (PIOA) Multi-driver Disable Register
#define AT91C_PIOA_PDR  	(AT91_REG(0xFFFFF404)) // (PIOA) PIO Disable Register
#define AT91C_PIOA_ODR  	(AT91_REG(0xFFFFF414)) // (PIOA) Output Disable Registerr
#define AT91C_PIOA_IFDR 	(AT91_REG(0xFFFFF424)) // (PIOA) Input Filter Disable Register
#define AT91C_PIOA_ABSR 	(AT91_REG(0xFFFFF478)) // (PIOA) AB Select Status Register
#define AT91C_PIOA_ASR  	(AT91_REG(0xFFFFF470)) // (PIOA) Select A Register
#define AT91C_PIOA_PPUSR 	(AT91_REG(0xFFFFF468)) // (PIOA) Pull-up Status Register
#define AT91C_PIOA_ODSR 	(AT91_REG(0xFFFFF438)) // (PIOA) Output Data Status Register
#define AT91C_PIOA_SODR 	(AT91_REG(0xFFFFF430)) // (PIOA) Set Output Data Register
#define AT91C_PIOA_IFSR 	(AT91_REG(0xFFFFF428)) // (PIOA) Input Filter Status Register
#define AT91C_PIOA_IFER 	(AT91_REG(0xFFFFF420)) // (PIOA) Input Filter Enable Register
#define AT91C_PIOA_OSR  	(AT91_REG(0xFFFFF418)) // (PIOA) Output Status Register
#define AT91C_PIOA_IDR  	(AT91_REG(0xFFFFF444)) // (PIOA) Interrupt Disable Register
#define AT91C_PIOA_PDSR 	(AT91_REG(0xFFFFF43C)) // (PIOA) Pin Data Status Register
#define AT91C_PIOA_CODR 	(AT91_REG(0xFFFFF434)) // (PIOA) Clear Output Data Register
#define AT91C_PIOA_OWSR 	(AT91_REG(0xFFFFF4A8)) // (PIOA) Output Write Status Register
#define AT91C_PIOA_OWER 	(AT91_REG(0xFFFFF4A0)) // (PIOA) Output Write Enable Register
// ========== Register definition for PIOB peripheral ==========
#define AT91C_PIOB_OWSR 	(AT91_REG(0xFFFFF6A8)) // (PIOB) Output Write Status Register
#define AT91C_PIOB_PPUSR 	(AT91_REG(0xFFFFF668)) // (PIOB) Pull-up Status Register
#define AT91C_PIOB_PPUDR 	(AT91_REG(0xFFFFF660)) // (PIOB) Pull-up Disable Register
#define AT91C_PIOB_MDSR 	(AT91_REG(0xFFFFF658)) // (PIOB) Multi-driver Status Register
#define AT91C_PIOB_MDER 	(AT91_REG(0xFFFFF650)) // (PIOB) Multi-driver Enable Register
#define AT91C_PIOB_IMR  	(AT91_REG(0xFFFFF648)) // (PIOB) Interrupt Mask Register
#define AT91C_PIOB_OSR  	(AT91_REG(0xFFFFF618)) // (PIOB) Output Status Register
#define AT91C_PIOB_OER  	(AT91_REG(0xFFFFF610)) // (PIOB) Output Enable Register
#define AT91C_PIOB_PSR  	(AT91_REG(0xFFFFF608)) // (PIOB) PIO Status Register
#define AT91C_PIOB_PER  	(AT91_REG(0xFFFFF600)) // (PIOB) PIO Enable Register
#define AT91C_PIOB_BSR  	(AT91_REG(0xFFFFF674)) // (PIOB) Select B Register
#define AT91C_PIOB_PPUER 	(AT91_REG(0xFFFFF664)) // (PIOB) Pull-up Enable Register
#define AT91C_PIOB_IFDR 	(AT91_REG(0xFFFFF624)) // (PIOB) Input Filter Disable Register
#define AT91C_PIOB_ODR  	(AT91_REG(0xFFFFF614)) // (PIOB) Output Disable Registerr
#define AT91C_PIOB_ABSR 	(AT91_REG(0xFFFFF678)) // (PIOB) AB Select Status Register
#define AT91C_PIOB_ASR  	(AT91_REG(0xFFFFF670)) // (PIOB) Select A Register
#define AT91C_PIOB_IFER 	(AT91_REG(0xFFFFF620)) // (PIOB) Input Filter Enable Register
#define AT91C_PIOB_IFSR 	(AT91_REG(0xFFFFF628)) // (PIOB) Input Filter Status Register
#define AT91C_PIOB_SODR 	(AT91_REG(0xFFFFF630)) // (PIOB) Set Output Data Register
#define AT91C_PIOB_ODSR 	(AT91_REG(0xFFFFF638)) // (PIOB) Output Data Status Register
#define AT91C_PIOB_CODR 	(AT91_REG(0xFFFFF634)) // (PIOB) Clear Output Data Register
#define AT91C_PIOB_PDSR 	(AT91_REG(0xFFFFF63C)) // (PIOB) Pin Data Status Register
#define AT91C_PIOB_OWER 	(AT91_REG(0xFFFFF6A0)) // (PIOB) Output Write Enable Register
#define AT91C_PIOB_IER  	(AT91_REG(0xFFFFF640)) // (PIOB) Interrupt Enable Register
#define AT91C_PIOB_OWDR 	(AT91_REG(0xFFFFF6A4)) // (PIOB) Output Write Disable Register
#define AT91C_PIOB_MDDR 	(AT91_REG(0xFFFFF654)) // (PIOB) Multi-driver Disable Register
#define AT91C_PIOB_ISR  	(AT91_REG(0xFFFFF64C)) // (PIOB) Interrupt Status Register
#define AT91C_PIOB_IDR  	(AT91_REG(0xFFFFF644)) // (PIOB) Interrupt Disable Register
#define AT91C_PIOB_PDR  	(AT91_REG(0xFFFFF604)) // (PIOB) PIO Disable Register

/* ========== Register definition for PMC peripheral ========== */
#define AT91C_PMC_SCER		(AT91_REG(0xFFFFFC00)) /* PMC System Clock Enable Register */
#define AT91C_PMC_SCDR		(AT91_REG(0xFFFFFC04)) /* PMC System Clock Disable Register */
#define AT91C_PMC_SCSR		(AT91_REG(0xFFFFFC08)) /* PMC System Clock Status Register */
#define AT91C_PMC_PCER		(AT91_REG(0xFFFFFC10)) /* PMC Peripheral Clock Enable Register */
#define AT91C_PMC_PCDR		(AT91_REG(0xFFFFFC14)) /* PMC Peripheral Clock Disable Register */
#define AT91C_PMC_PCSR		(AT91_REG(0xFFFFFC18)) /* PMC Peripheral Clock Status Register */
#define AT91C_PMC_MOR		(AT91_REG(0xFFFFFC20)) /* PMC Main Oscillator Register */
#define AT91C_PMC_MCFR		(AT91_REG(0xFFFFFC24)) /* PMC Main Clock  Frequency Register */
#define AT91C_PMC_PLLR		(AT91_REG(0xFFFFFC2C)) /* PMC PLL Register */
#define AT91C_PMC_MCKR		(AT91_REG(0xFFFFFC30)) /* PMC Master Clock Register */
#define AT91C_PMC_PCKR		(AT91_REG(0xFFFFFC40)) /* PMC Programmable Clock Register */
#define AT91C_PMC_IER		(AT91_REG(0xFFFFFC60)) /* PMC Interrupt Enable Register */
#define AT91C_PMC_IDR		(AT91_REG(0xFFFFFC64)) /* PMC Interrupt Disable Register */
#define AT91C_PMC_SR		(AT91_REG(0xFFFFFC68)) /* PMC Status Register */
#define AT91C_PMC_IMR		(AT91_REG(0xFFFFFC6C)) /* PMC Interrupt Mask Register */

/******************************************************************************/
/*               PERIPHERAL ID DEFINITIONS FOR AT91SAM7S64                    */
/******************************************************************************/
#define AT91C_ID_FIQ    	0 	/* Advanced Interrupt Controller (FIQ) */
#define AT91C_ID_SYS    	1 	/* System Peripheral */
#define AT91C_ID_PIOA   	2 	/* Parallel IO Controller A */
#define AT91C_ID_PIOB   	3 	/* Parallel IO Controller B */
#define AT91C_ID_ADC    	4 	/* Analog-to-Digital Converter */
#define AT91C_ID_SPI    	5	/* Serial Peripheral Interface */
#define AT91C_ID_US0    	6	/* USART 0 */
#define AT91C_ID_US1    	7	/* USART 1 */
#define AT91C_ID_SSC    	8	/* Serial Synchronous Controller */
#define AT91C_ID_TWI    	9 	/* Two-Wire Interface */
#define AT91C_ID_PWMC   	10	/* PWM Controller */
#define AT91C_ID_UDP    	11 	/* USB Device Port */
#define AT91C_ID_TC0    	12 	/* Timer Counter 0 */
#define AT91C_ID_TC1    	13 	/* Timer Counter 1 */
#define AT91C_ID_TC2    	14 	/* Timer Counter 2 */
#define AT91C_ID_15			15	/* Reserved */
#define AT91C_ID_16 		16 	/* Reserved */
#define AT91C_ID_17 		17 	/* Reserved */
#define AT91C_ID_18 		18 	/* Reserved */
#define AT91C_ID_19 		19 	/* Reserved */
#define AT91C_ID_20 		20 	/* Reserved */
#define AT91C_ID_21 		21 	/* Reserved */
#define AT91C_ID_22 		22 	/* Reserved */
#define AT91C_ID_23 		23 	/* Reserved */
#define AT91C_ID_24 		24 	/* Reserved */
#define AT91C_ID_25 		25 	/* Reserved */
#define AT91C_ID_26 		26 	/* Reserved */
#define AT91C_ID_27 		27 	/* Reserved */
#define AT91C_ID_28 		28 	/* Reserved */
#define AT91C_ID_29 		29 	/* Reserved */
#define AT91C_ID_IRQ0		30 	/* Advanced Interrupt Controller (IRQ0) */
#define AT91C_ID_IRQ1		31 	/* Advanced Interrupt Controller (IRQ1) */
#define AT91C_ALL_INT		0xC0007FF7	/* ALL VALID INTERRUPTS */

/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE			0x10
#define FIQMODE				0x11
#define IRQMODE				0x12
#define SVCMODE				0x13
#define ABORTMODE			0x17
#define UNDEFMODE			0x1b
#define MODEMASK			0x1f
#define NOINT				0xc0

#ifdef __cplusplus
}
#endif

#endif
