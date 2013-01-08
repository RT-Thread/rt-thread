/*
 * File      : s3c45b0.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-06     XuXinming    first version
 * 2006-09-16     Bernard      modify according to code style
 */

#ifndef __S3C44B0_H__
#define __S3C44B0_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup S3C44B0
 */
/*@{*/

/*------------------------------------------------------------------------
 *	  ASIC Address Definition
 *----------------------------------------------------------------------*/
#define S3C_REG		*(volatile unsigned int *)
#define S3C_REGW	*(volatile unsigned short *)
#define S3C_REGB	*(volatile unsigned char *)

/* System */
#define SYSCFG		(S3C_REG(0x1c00000))

/* Cache */
#define NCACHBE0	(S3C_REG(0x1c00004))
#define NCACHBE1	(S3C_REG(0x1c00008))

/* Bus control */
#define SBUSCON		(S3C_REG(0x1c40000))

/* Memory control */
#define BWSCON		(S3C_REG(0x1c80000))
#define BANKCON0	(S3C_REG(0x1c80004))
#define BANKCON1	(S3C_REG(0x1c80008))
#define BANKCON2	(S3C_REG(0x1c8000c))
#define BANKCON3	(S3C_REG(0x1c80010))
#define BANKCON4	(S3C_REG(0x1c80014))
#define BANKCON5	(S3C_REG(0x1c80018))
#define BANKCON6	(S3C_REG(0x1c8001c))
#define BANKCON7	(S3C_REG(0x1c80020))
#define REFRESH		(S3C_REG(0x1c80024))
#define BANKSIZE	(S3C_REG(0x1c80028))
#define MRSRB6		(S3C_REG(0x1c8002c))
#define MRSRB7		(S3C_REG(0x1c80030))

/* UART */
#define ULCON0		(S3C_REG(0x1d00000))
#define ULCON1		(S3C_REG(0x1d04000))
#define UCON0		(S3C_REG(0x1d00004))
#define UCON1		(S3C_REG(0x1d04004))
#define UFCON0		(S3C_REG(0x1d00008))
#define UFCON1		(S3C_REG(0x1d04008))
#define UMCON0		(S3C_REG(0x1d0000c))
#define UMCON1		(S3C_REG(0x1d0400c))
#define UTRSTAT0	(S3C_REG(0x1d00010))
#define UTRSTAT1	(S3C_REG(0x1d04010))
#define UERSTAT0	(S3C_REG(0x1d00014))
#define UERSTAT1	(S3C_REG(0x1d04014))
#define UFSTAT0		(S3C_REG(0x1d00018))
#define UFSTAT1		(S3C_REG(0x1d04018))
#define UMSTAT0		(S3C_REG(0x1d0001c))
#define UMSTAT1		(S3C_REG(0x1d0401c))
#define UBRDIV0		(S3C_REG(0x1d00028))
#define UBRDIV1		(S3C_REG(0x1d04028))

#define UTXH0		(S3C_REGB(0x1d00020))
#define UTXH1		(S3C_REGB(0x1d04020))
#define URXH0		(S3C_REGB(0x1d00024))
#define URXH1		(S3C_REGB(0x1d04024))

/* SIO */
#define SIOCON		(S3C_REG(0x1d14000))
#define SIODAT		(S3C_REG(0x1d14004))
#define SBRDR		(S3C_REG(0x1d14008))
#define IVTCNT		(S3C_REG(0x1d1400c))
#define DCNTZ		(S3C_REG(0x1d14010))

/* IIS */
#define IISCON		(S3C_REG(0x1d18000))
#define IISMOD		(S3C_REG(0x1d18004))
#define IISPSR		(S3C_REG(0x1d18008))
#define IISFCON		(S3C_REG(0x1d1800c))

#define IISFIF		(S3C_REQW(0x1d18010))

/* I/O Port */
#define PCONA		(S3C_REG(0x1d20000))
#define PDATA		(S3C_REG(0x1d20004))

#define PCONB		(S3C_REG(0x1d20008))
#define PDATB		(S3C_REG(0x1d2000c))

#define PCONC		(S3C_REG(0x1d20010))
#define PDATC		(S3C_REG(0x1d20014))
#define PUPC		(S3C_REG(0x1d20018))

#define PCOND		(S3C_REG(0x1d2001c))
#define PDATD		(S3C_REG(0x1d20020))
#define PUPD		(S3C_REG(0x1d20024))

#define PCONE		(S3C_REG(0x1d20028))
#define PDATE		(S3C_REG(0x1d2002c))
#define PUPE		(S3C_REG(0x1d20030))

#define PCONF		(S3C_REG(0x1d20034))
#define PDATF		(S3C_REG(0x1d20038))
#define PUPF		(S3C_REG(0x1d2003c))

#define PCONG		(S3C_REG(0x1d20040))
#define PDATG		(S3C_REG(0x1d20044))
#define PUPG		(S3C_REG(0x1d20048))

#define SPUCR		(S3C_REG(0x1d2004c))
#define EXTINT		(S3C_REG(0x1d20050))
#define EXTINTPND	(S3C_REG(0x1d20054))

/* Watchdog */
#define WTCON		(S3C_REG(0x1d30000))
#define WTDAT		(S3C_REG(0x1d30004))
#define WTCNT		(S3C_REG(0x1d30008))

/* ADC */
#define ADCCON		(S3C_REG(0x1d40000))
#define ADCPSR		(S3C_REG(0x1d40004))
#define ADCDAT		(S3C_REG(0x1d40008))

/* Timer */
#define TCFG0		(S3C_REG(0x1d50000))
#define TCFG1		(S3C_REG(0x1d50004))
#define TCON		(S3C_REG(0x1d50008))

#define TCNTB0		(S3C_REG(0x1d5000c))
#define TCMPB0		(S3C_REG(0x1d50010))
#define TCNTO0		(S3C_REG(0x1d50014))

#define TCNTB1		(S3C_REG(0x1d50018))
#define TCMPB1		(S3C_REG(0x1d5001c))
#define TCNTO1		(S3C_REG(0x1d50020))

#define TCNTB2		(S3C_REG(0x1d50024))
#define TCMPB2		(S3C_REG(0x1d50028))
#define TCNTO2		(S3C_REG(0x1d5002c))

#define TCNTB3		(S3C_REG(0x1d50030))
#define TCMPB3		(S3C_REG(0x1d50034))
#define TCNTO3		(S3C_REG(0x1d50038))

#define TCNTB4		(S3C_REG(0x1d5003c))
#define TCMPB4		(S3C_REG(0x1d50040))
#define TCNTO4		(S3C_REG(0x1d50044))

#define TCNTB5		(S3C_REG(0x1d50048))
#define TCNTO5		(S3C_REG(0x1d5004c))

/* IIC */
#define IICCON		(S3C_REG(0x1d60000))
#define IICSTAT    	(S3C_REG(0x1d60004))
#define IICADD     	(S3C_REG(0x1d60008))
#define IICDS		(S3C_REG(0x1d6000c))

/* RTC */
#define RTCCON		(S3C_REGB(0x1d70040)
#define RTCALM		(S3C_REGB(0x1d70050)
#define ALMSEC		(S3C_REGB(0x1d70054)
#define ALMMIN		(S3C_REGB(0x1d70058)
#define ALMHOUR		(S3C_REGB(0x1d7005c)
#define ALMDAY		(S3C_REGB(0x1d70060)
#define ALMMON		(S3C_REGB(0x1d70064)
#define ALMYEAR		(S3C_REGB(0x1d70068)
#define RTCRST		(S3C_REGB(0x1d7006c)
#define BCDSEC		(S3C_REGB(0x1d70070)
#define BCDMIN		(S3C_REGB(0x1d70074)
#define BCDHOUR		(S3C_REGB(0x1d70078)
#define BCDDAY		(S3C_REGB(0x1d7007c)
#define BCDDATE		(S3C_REGB(0x1d70080)
#define BCDMON		(S3C_REGB(0x1d70084)
#define BCDYEAR		(S3C_REGB(0x1d70088)
#define TICINT		(S3C_REGB(0x1d7008c)

/* Clock & Power management */
#define PLLCON		(S3C_REG(0x1d80000))
#define CLKCON		(S3C_REG(0x1d80004))
#define CLKSLOW		(S3C_REG(0x1d80008))
#define LOCKTIME	(S3C_REG(0x1d8000c))

/* Interrupt */
#define INTCON		(S3C_REG(0x1e00000))
#define INTPND		(S3C_REG(0x1e00004))
#define INTMOD		(S3C_REG(0x1e00008))
#define INTMSK		(S3C_REG(0x1e0000c))

#define I_PSLV		(S3C_REG(0x1e00010))
#define I_PMST		(S3C_REG(0x1e00014))
#define I_CSLV		(S3C_REG(0x1e00018))
#define I_CMST		(S3C_REG(0x1e0001c))
#define I_ISPR		(S3C_REG(0x1e00020))
#define I_ISPC		(S3C_REG(0x1e00024))

#define F_ISPR		(S3C_REG(0x1e00038))
#define F_ISPC		(S3C_REG(0x1e0003c))

/********************************/
/* LCD Controller Registers     */
/********************************/
#define LCDCON1		(S3C_REG(0x300000))
#define LCDCON2		(S3C_REG(0x300004))
#define LCDSADDR1	(S3C_REG(0x300008))
#define LCDSADDR2	(S3C_REG(0x30000c))
#define LCDSADDR3	(S3C_REG(0x300010))
#define REDLUT		(S3C_REG(0x300014))
#define GREENLUT	(S3C_REG(0x300018))
#define BLUELUT		(S3C_REG(0x30001c))
#define DP1_2		(S3C_REG(0x300020))
#define DP4_7		(S3C_REG(0x300024))
#define DP3_5		(S3C_REG(0x300028))
#define DP2_3		(S3C_REG(0x30002c))
#define DP5_7		(S3C_REG(0x300030))
#define DP3_4		(S3C_REG(0x300034))
#define DP4_5		(S3C_REG(0x300038))
#define DP6_7		(S3C_REG(0x30003c))
#define LCDCON3		(S3C_REG(0x300040))
#define DITHMODE	(S3C_REG(0x300044))

/* ZDMA0 */
#define ZDCON0		(S3C_REG(0x1e80000))
#define ZDISRC0		(S3C_REG(0x1e80004))
#define ZDIDES0		(S3C_REG(0x1e80008))
#define ZDICNT0		(S3C_REG(0x1e8000c))
#define ZDCSRC0		(S3C_REG(0x1e80010))
#define ZDCDES0		(S3C_REG(0x1e80014))
#define ZDCCNT0		(S3C_REG(0x1e80018))

/* ZDMA1 */
#define ZDCON1		(S3C_REG(0x1e80020))
#define ZDISRC1		(S3C_REG(0x1e80024))
#define ZDIDES1		(S3C_REG(0x1e80028))
#define ZDICNT1		(S3C_REG(0x1e8002c))
#define ZDCSRC1		(S3C_REG(0x1e80030))
#define ZDCDES1		(S3C_REG(0x1e80034))
#define ZDCCNT1		(S3C_REG(0x1e80038))

/* BDMA0 */
#define BDCON0		(S3C_REG(0x1f80000))
#define BDISRC0		(S3C_REG(0x1f80004))
#define BDIDES0		(S3C_REG(0x1f80008))
#define BDICNT0		(S3C_REG(0x1f8000c))
#define BDCSRC0		(S3C_REG(0x1f80010))
#define BDCDES0		(S3C_REG(0x1f80014))
#define BDCCNT0		(S3C_REG(0x1f80018))

/* BDMA1 */
#define BDCON1		(S3C_REG(0x1f80020))
#define BDISRC1		(S3C_REG(0x1f80024))
#define BDIDES1		(S3C_REG(0x1f80028))
#define BDICNT1		(S3C_REG(0x1f8002c))
#define BDCSRC1		(S3C_REG(0x1f80030))
#define BDCDES1		(S3C_REG(0x1f80034))
#define BDCCNT1		(S3C_REG(0x1f80038))

/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE	0x10		/* User Mode(USR) */
#define FIQMODE		0x11		/* Fast Interrupt Mode (FIQ) */
#define IRQMODE		0x12		/* Interrupt Mode (IRQ) */
#define SVCMODE		0x13		/* Supervisor Mode (SVC) */
#define ABORTMODE	0x17		/* Abort Mode(ABT) */
#define UNDEFMODE	0x1b		/* Undefine Mode(UDF) */
#define MODEMASK	0x1f		/* Processor Mode Mask */
#define NOINT		0xc0

/*****************************/
/* INT Define                */
/*****************************/
#define INT_ADC		0x00
#define INT_RTC		0x01
#define INT_UTXD1	0x02
#define INT_UTXD0	0x03
#define INT_SIO		0x04
#define INT_IIC		0x05
#define INT_URXD1	0x06
#define INT_URXD0	0x07
#define INT_TIMER5	0x08
#define INT_TIMER4	0x09
#define INT_TIMER3	0x0A
#define INT_TIMER2	0x0B
#define INT_TIMER1	0x0C
#define INT_TIMER0	0x0D
#define INT_UERR01	0x0E
#define INT_WDT		0x1F
#define INT_BDMA1	0x10
#define INT_BDMA0	0x11
#define INT_ZDMA1	0x12
#define INT_ZDMA0	0x13
#define INT_TICK	0x14
#define INT_EINT4567	0x15
#define INT_EINT3	0x16
#define INT_EINT2	0x17
#define INT_EINT1	0x18
#define INT_EINT0	0x19

#define INT_GLOBAL	26

struct rt_hw_register
{
	unsigned long r0;
	unsigned long r1;
	unsigned long r2;
	unsigned long r3;
	unsigned long r4;
	unsigned long r5;
	unsigned long r6;
	unsigned long r7;
	unsigned long r8;
	unsigned long r9;
	unsigned long r10;
	unsigned long fp;
	unsigned long ip;
	unsigned long sp;
	unsigned long lr;
	unsigned long pc;
	unsigned long cpsr;
	unsigned long ORIG_r0;
};

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
