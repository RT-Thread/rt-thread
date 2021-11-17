/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#ifndef __C66XX_H__
#define __C66XX_H__

#include <c6x.h>

#ifdef _BIG_ENDIAN
#define REG_PAIR(odd, even) unsigned long odd; unsigned long even
#else
#define REG_PAIR(odd, even) unsigned long even; unsigned long odd
#endif

/*
 * this struct defines the way the registers are stored on the
 * stack during a system call. fields defined with REG_PAIR
 * are saved and restored using double-word memory operations
 * which means the word ordering of the pair depends on endianess.
 */

struct rt_hw_register
{
	REG_PAIR(b17, b16);
	REG_PAIR(b19, b18);
	REG_PAIR(b21, b20);
	REG_PAIR(b23, b22);
	REG_PAIR(b25, b24);
	REG_PAIR(b27, b26);
	REG_PAIR(b29, b28);
	REG_PAIR(b31, b30);

	REG_PAIR(b1, b0);
	REG_PAIR(b3, b2);
	REG_PAIR(b5, b4);
	REG_PAIR(b7, b6);
	REG_PAIR(b9, b8);
	REG_PAIR(b11, b10);
	REG_PAIR(b13, b12);

	REG_PAIR(a17, a16);
	REG_PAIR(a19, a18);
	REG_PAIR(a21, a20);
	REG_PAIR(a23, a22);
	REG_PAIR(a25, a24);
	REG_PAIR(a27, a26);
	REG_PAIR(a29, a28);
	REG_PAIR(a31, a30);

	REG_PAIR(a1, a0);
	REG_PAIR(a3, a2);
	REG_PAIR(a5, a4);
	REG_PAIR(a7, a6);
	REG_PAIR(a9, a8);
	REG_PAIR(a11, a10);
	REG_PAIR(a13, a12);

	REG_PAIR(a15, a14);
	REG_PAIR(sp, dp);
};

struct rt_hw_exp_stack_register
{
	REG_PAIR(tsr, orig_a4);
	REG_PAIR(rilc, ilc);
	REG_PAIR(pc, csr);
    struct rt_hw_register hw_register;
};

#define __dint()				asm(" DINT")
#define __rint()				asm(" RINT")
#define __system_call()			asm(" SWE")
#define __enter_idle()			asm(" IDLE")
#define __nop()					asm(" NOP")
#define __mfence()				asm(" MFENCE")

#define __SYSREG(ADDR, TYPE)	(*(volatile TYPE*)(ADDR))
#define __SYSREGA(ADDR, TYPE)	((volatile TYPE*)(ADDR))

#endif /* __C66XX_H__ */
