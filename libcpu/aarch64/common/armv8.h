/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 */

#ifndef __ARMV8_H__
#define __ARMV8_H__

/* the exception stack without VFP registers */
struct rt_hw_exp_stack
{
	unsigned long pc;
	unsigned long cpsr;
	unsigned long sp_el0;
	unsigned long x30;
    unsigned long fpcr;
    unsigned long fpsr;
	unsigned long x28;
	unsigned long x29;
	unsigned long x26;
	unsigned long x27;
	unsigned long x24;
	unsigned long x25;
	unsigned long x22;
	unsigned long x23;
	unsigned long x20;
	unsigned long x21;
	unsigned long x18;	
	unsigned long x19;
	unsigned long x16;
	unsigned long x17;
	unsigned long x14;
	unsigned long x15;
	unsigned long x12;
	unsigned long x13;
	unsigned long x10;
	unsigned long x11;
	unsigned long x8;
	unsigned long x9;
	unsigned long x6;
	unsigned long x7;
	unsigned long x4;
	unsigned long x5;
	unsigned long x2;
	unsigned long x3;
	unsigned long x0;
	unsigned long x1;

    unsigned long long fpu[16];
};

#define SP_ELx						( ( unsigned long ) 0x01 )
#define SP_EL0						( ( unsigned long ) 0x00 )
#define PSTATE_EL1					( ( unsigned long ) 0x04 )
#define PSTATE_EL2					( ( unsigned long ) 0x08 )
#define PSTATE_EL3					( ( unsigned long ) 0x0c )

rt_ubase_t rt_hw_get_current_el(void);
void rt_hw_set_elx_env(void);
void rt_hw_set_current_vbar(rt_ubase_t addr);

#endif
