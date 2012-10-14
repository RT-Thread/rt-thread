/*
 * (C) Copyright 2001
 * Erik Theisen, Wave 7 Optics, etheisen@mindspring.com
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <asm/ppc4xx.h>

/*****************************************************************************
 *
 *  XXX - DANGER
 *        These routines make use of self modifying code.  DO NOT CALL THEM
 *	  UNTIL THEY ARE RELOCATED TO RAM.  Additionally, I do not
 *	  recommend them for use in anything other than an interactive
 *        debugging environment.  This is mainly due to performance reasons.
 *
 ****************************************************************************/

/*
 * static void _create_MFDCR(unsigned short dcrn)
 *
 * Builds a 'mfdcr' instruction for get_dcr
 * function.
 */
		.section ".text"
		.align 2
		.type	 _create_MFDCR,@function
_create_MFDCR:
		/*
		 * Build up a 'mfdcr' instruction formatted as follows:
		 *
		 *  OPCD |   RT   |    DCRF      |     XO       | CR |
		 * ---------------|--------------|--------------|----|
		 * 0   5 | 6   10 | 11        20 | 21        30 | 31 |
		 *       |        |    DCRN      |              |    |
		 *   31  |  %r3   | (5..9|0..4)  |      323     |  0 |
		 *
		 * Where:
		 *	OPCD = opcode - 31
		 *	RT   = destination register - %r3 return register
		 *	DCRF = DCRN # with upper and lower halves swapped
		 *	XO   = extended opcode - 323
		 *	CR   = CR[CR0] NOT undefined - 0
		 */
		rlwinm	r0, r3, 27, 27, 31	/* OPCD = 31 */
		rlwinm	r3, r3, 5, 22, 26
		or	r3, r3, r0
		slwi	r3, r3, 10
		oris	r3, r3, 0x3e30		/* RT = %r3 */
		ori	r3, r3, 323		/* XO = 323 */
		slwi	r3, r3, 1		/* CR = 0 */

		mflr	r4
		stw	r3, 0(r4)		/* Store instr in get_dcr() */
		dcbst	r0, r4			/* Make sure val is written out */
		sync				/* Wait for write to complete */
		icbi	r0, r4			/* Make sure old instr is dumped */
		isync				/* Wait for icbi to complete */

		blr
.Lfe1:		.size	 _create_MFDCR,.Lfe1-_create_MFDCR
/* end _create_MFDCR() */

/*
 * static void _create_MTDCR(unsigned short dcrn, unsigned long value)
 *
 * Builds a 'mtdcr' instruction for set_dcr
 * function.
 */
		.section ".text"
		.align 2
		.type	 _create_MTDCR,@function
_create_MTDCR:
		/*
		 * Build up a 'mtdcr' instruction formatted as follows:
		 *
		 *  OPCD |   RS   |    DCRF      |     XO       | CR |
		 * ---------------|--------------|--------------|----|
		 * 0   5 | 6   10 | 11        20 | 21        30 | 31 |
		 *       |        |    DCRN      |              |    |
		 *   31  |  %r3   | (5..9|0..4)  |      451     |  0 |
		 *
		 * Where:
		 *	OPCD = opcode - 31
		 *	RS   = source register - %r4
		 *	DCRF = dest. DCRN # with upper and lower halves swapped
		 *	XO   = extended opcode - 451
		 *	CR   = CR[CR0] NOT undefined - 0
		 */
		rlwinm	r0, r3, 27, 27, 31	/* OPCD = 31 */
		rlwinm	r3, r3, 5, 22, 26
		or	r3, r3, r0
		slwi	r3, r3, 10
		oris	r3, r3, 0x3e40		/* RS = %r4 */
		ori	r3, r3, 451		/* XO = 451 */
		slwi	r3, r3, 1		/* CR = 0 */

		mflr	r5
		stw	r3, 0(r5)		/* Store instr in set_dcr() */
		dcbst	r0, r5			/* Make sure val is written out */
		sync				/* Wait for write to complete */
		icbi	r0, r5			/* Make sure old instr is dumped */
		isync				/* Wait for icbi to complete */

		blr
.Lfe2:		.size	 _create_MTDCR,.Lfe2-_create_MTDCR
/* end _create_MTDCR() */


/*
 * unsigned long get_dcr(unsigned short dcrn)
 *
 * Return a given DCR's value.
 */
		/* */
		/* XXX - This is self modifying code, hence */
		/* it is in the data section. */
		/* */
		.section ".text"
		.align	2
		.globl	get_dcr
		.type	get_dcr,@function
get_dcr:
		mflr	r0			/* Get link register */
		stwu	r1, -32(r1)		/* Save back chain and move SP */
		stw	r0, +36(r1)		/* Save link register */

		bl	_create_MFDCR		/* Build following instruction */
		/* XXX - we build this instuction up on the fly. */
		.long	0			/* Get DCR's value */

		lwz	r0, +36(r1)		/* Get saved link register */
		mtlr	r0			/* Restore link register */
		addi	r1, r1, +32		/* Remove frame from stack */
		blr				/* Return to calling function */
.Lfe3:		.size	get_dcr,.Lfe3-get_dcr
/* end get_dcr() */


/*
 * unsigned void set_dcr(unsigned short dcrn, unsigned long value)
 *
 * Return a given DCR's value.
 */
		/*
		 * XXX - This is self modifying code, hence
		 * it is in the data section.
		 */
		.section ".text"
		.align	2
		.globl	set_dcr
		.type	set_dcr,@function
set_dcr:
		mflr	r0			/* Get link register */
		stwu	r1, -32(r1)		/* Save back chain and move SP */
		stw	r0, +36(r1)		/* Save link register */

		bl	_create_MTDCR		/* Build following instruction */
		/* XXX - we build this instuction up on the fly. */
		.long	0			/* Set DCR's value */

		lwz	r0, +36(r1)		/* Get saved link register */
		mtlr	r0			/* Restore link register */
		addi	r1, r1, +32		/* Remove frame from stack */
		blr				/* Return to calling function */
.Lfe4:		.size	set_dcr,.Lfe4-set_dcr
/* end set_dcr() */

