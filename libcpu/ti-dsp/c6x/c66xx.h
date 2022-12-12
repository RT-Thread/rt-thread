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

extern __cregister volatile unsigned int IERR;    /* Internal Exception Report Register */
extern __cregister volatile unsigned int ECR;     /* Exception Clear Register */
extern __cregister volatile unsigned int EFR;     /* Exception Flag Register */
extern __cregister volatile unsigned int TSR;     /* Task State Register */
extern __cregister volatile unsigned int ITSR;    /* Interrupt Task State Register */
extern __cregister volatile unsigned int NTSR;    /* NMI/exception Task State Register */
extern __cregister volatile unsigned int TSCL;    /* Time Stamp Counter Register - Low Half  */
extern __cregister volatile unsigned int TSCH;    /* Time Stamp Counter Register - High Half */
extern __cregister volatile unsigned int DNUM;    /* Core number */

extern __cregister volatile unsigned int AMR;
extern __cregister volatile unsigned int CSR;
extern __cregister volatile unsigned int IFR;
extern __cregister volatile unsigned int ISR;
extern __cregister volatile unsigned int ICR;
extern __cregister volatile unsigned int IER;
extern __cregister volatile unsigned int ISTP;
extern __cregister volatile unsigned int IRP;
extern __cregister volatile unsigned int NRP;

#ifdef _BIG_ENDIAN
#define RT_REG_PAIR(odd, even) unsigned long odd; unsigned long even
#else
#define RT_REG_PAIR(odd, even) unsigned long even; unsigned long odd
#endif

struct rt_hw_register
{
    RT_REG_PAIR(b17, b16);
    RT_REG_PAIR(b19, b18);
    RT_REG_PAIR(b21, b20);
    RT_REG_PAIR(b23, b22);
    RT_REG_PAIR(b25, b24);
    RT_REG_PAIR(b27, b26);
    RT_REG_PAIR(b29, b28);
    RT_REG_PAIR(b31, b30);

    RT_REG_PAIR(b1, b0);
    RT_REG_PAIR(b3, b2);
    RT_REG_PAIR(b5, b4);
    RT_REG_PAIR(b7, b6);
    RT_REG_PAIR(b9, b8);
    RT_REG_PAIR(b11, b10);
    RT_REG_PAIR(b13, b12);

    RT_REG_PAIR(a17, a16);
    RT_REG_PAIR(a19, a18);
    RT_REG_PAIR(a21, a20);
    RT_REG_PAIR(a23, a22);
    RT_REG_PAIR(a25, a24);
    RT_REG_PAIR(a27, a26);
    RT_REG_PAIR(a29, a28);
    RT_REG_PAIR(a31, a30);

    RT_REG_PAIR(a1, a0);
    RT_REG_PAIR(a3, a2);
    RT_REG_PAIR(a5, a4);
    RT_REG_PAIR(a7, a6);
    RT_REG_PAIR(a9, a8);
    RT_REG_PAIR(a11, a10);
    RT_REG_PAIR(a13, a12);

    RT_REG_PAIR(a15, a14);
    RT_REG_PAIR(sp, dp);
};

typedef struct rt_hw_exp_stack_register
{
    RT_REG_PAIR(tsr, orig_a4);
    RT_REG_PAIR(rilc, ilc);
    RT_REG_PAIR(pc, csr);
    struct rt_hw_register hw_register;
} rt_hw_thread_stack_register;

#define __dint()                asm(" DINT")
#define __rint()                asm(" RINT")
#define __system_call()         asm(" SWE")
#define __enter_idle()          asm(" IDLE")
#define __nop()                 asm(" NOP")
#define __mfence()              asm(" MFENCE")

#define __SYSREG(ADDR, TYPE)    (*(volatile TYPE*)(ADDR))
#define __SYSREGA(ADDR, TYPE)   ((volatile TYPE*)(ADDR))

#endif /* __C66XX_H__ */
