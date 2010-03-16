/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-16     Gary Lee     the first version
 */

#define BWSCON	        0x48000000

/* BWSCON */
#define DW8				(0x0)
#define DW16			(0x1)
#define DW32			(0x2)
#define WAIT			(0x1<<2)
#define UBLB			(0x1<<3)

#define B1_BWSCON		(DW16)
#define B2_BWSCON		(DW16)
#define B3_BWSCON		(DW16 + WAIT + UBLB)
#define B4_BWSCON		(DW16)
#define B5_BWSCON		(DW16)
#define B6_BWSCON		(DW32)
#define B7_BWSCON		(DW32)

#define B0_Tacs			0x0
#define B0_Tcos			0x0
#define B0_Tacc			0x7
#define B0_Tcoh			0x0
#define B0_Tah			0x0
#define B0_Tacp			0x0
#define B0_PMC			0x0

#define B1_Tacs			0x0
#define B1_Tcos			0x0
#define B1_Tacc			0x7
#define B1_Tcoh			0x0
#define B1_Tah			0x0
#define B1_Tacp			0x0
#define B1_PMC			0x0

#define B2_Tacs			0x0
#define B2_Tcos			0x0
#define B2_Tacc			0x7
#define B2_Tcoh			0x0
#define B2_Tah			0x0
#define B2_Tacp			0x0
#define B2_PMC			0x0

#define B3_Tacs			0xc
#define B3_Tcos			0x7
#define B3_Tacc			0xf
#define B3_Tcoh			0x1
#define B3_Tah			0x0
#define B3_Tacp			0x0
#define B3_PMC			0x0

#define B4_Tacs			0x0
#define B4_Tcos			0x0
#define B4_Tacc			0x7
#define B4_Tcoh			0x0
#define B4_Tah			0x0
#define B4_Tacp			0x0
#define B4_PMC			0x0

#define B5_Tacs			0xc
#define B5_Tcos			0x7
#define B5_Tacc			0xf
#define B5_Tcoh			0x1
#define B5_Tah			0x0
#define B5_Tacp			0x0
#define B5_PMC			0x0

#define B6_MT			0x3				/* SDRAM 											*/
#define B6_Trcd			0x1
#define B6_SCAN			0x1				/* 9bit 											*/

#define B7_MT			0x3				/* SDRAM 											*/
#define B7_Trcd			0x1				/* 3clk 											*/
#define B7_SCAN			0x1				/* 9bit 											*/

/* REFRESH parameter 					*/
#define REFEN			0x1				/* Refresh enable 									*/
#define TREFMD			0x0				/* CBR(CAS before RAS)/Auto refresh 				*/
#define Trc				0x3				/* 7clk 											*/
#define Tchr			0x2				/* 3clk 											*/

#define Trp				0x2				/* 4clk 											*/
#define REFCNT			1012

/**************************************/

.globl lowlevel_init
lowlevel_init:
	/* memory control configuration 	*/
	/* make r0 relative the current location so that it 									*/
	/* reads SMRDATA out of FLASH rather than memory ! 										*/
	ldr     r0, =SMRDATA
	ldr	    r1, =lowlevel_init
	sub	    r0, r0, r1
	adr	    r3, lowlevel_init			/* r3 <- current position of code   				*/
	add     r0, r0, r3
	ldr	    r1, =BWSCON					/* Bus Width Status Controller 						*/
	add     r2, r0, #13*4
0:
	ldr     r3, [r0], #4
	str     r3, [r1], #4
	cmp     r2, r0
	bne     0b

	/* everything is fine now 			*/
	mov	    pc, lr

	.ltorg
/* the literal pools origin 			*/

SMRDATA:
    .word (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
    .word ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))
    .word ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))
    .word ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))
    .word ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))
    .word ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))
    .word ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))
    .word ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))
    .word ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))
    .word ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Trc<<18)+(Tchr<<16)+REFCNT)
    .word 0xb2
    .word 0x30
    .word 0x30
    
