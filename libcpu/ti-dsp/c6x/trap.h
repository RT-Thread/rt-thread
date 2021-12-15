/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#ifndef __TRAP_H__
#define __TRAP_H__

#include "c66xx.h"

/*
 * exception operation macro
 */
#define disable_exception()
#define get_except_type()       EFR
#define ack_exception(type)     ECR = 1ul << (type)
#define get_iexcept()           IERR
#define set_iexcept(mask)       IERR = (mask)

/*
 * exception types
 */
#define EXCEPT_TYPE_NXF   31       /* NMI */
#define EXCEPT_TYPE_EXC   30       /* external exception */
#define EXCEPT_TYPE_IXF   1        /* internal exception */
#define EXCEPT_TYPE_SXF   0        /* software exception */

#define EXCEPT_CAUSE_LBX  (1 << 7) /* loop buffer exception */
#define EXCEPT_CAUSE_PRX  (1 << 6) /* privilege exception */
#define EXCEPT_CAUSE_RAX  (1 << 5) /* resource access exception */
#define EXCEPT_CAUSE_RCX  (1 << 4) /* resource conflict exception */
#define EXCEPT_CAUSE_OPX  (1 << 3) /* opcode exception */
#define EXCEPT_CAUSE_EPX  (1 << 2) /* execute packet exception */
#define EXCEPT_CAUSE_FPX  (1 << 1) /* fetch packet exception */
#define EXCEPT_CAUSE_IFX  (1 << 0) /* instruction fetch exception */

enum SYSTEM_TRAP_CODE
{
    ABORT_BUS_ADDRERR = 0,  // bus address error
    ABORT_BUS_ACCERR,       // bus access permission error
    ABORT_OPCODE_ILL,       // illegal opcode
    ABORT_PRVREG_ILL,       // privilege register
    ABORT_PRVOPC_ILL,       // privileged opcode
    ABORT_ILLTRP_ILL,       // illegal trap
    ABORT_BRKPT_ILL,        // handling breakpoints
};

/*
 * abort types
 */
#define ABORT_TYPE_BUS        0           // bus access abnormal
#define ABORT_TYPE_MAP        1           // page table mapping error
#define ABORT_TYPE_UNDDEF     0xff        // undefined exception
#define ABORT_TYPE_FATAL      0xffffffff  // fatal error

struct rt_exception_info {
    char *kernel_str;
    int type;
    int code;
};

#define BKPT_OPCODE        0x56454314    /* illegal opcode */
#define INTC_MEXPMASK    __SYSREGA(0x018000e0, unsigned int)

extern void rt_trap_init(void);
extern void rt_hw_enable_exception(void);
extern int __fls(int val);
extern int __ffs(int val);

/*
 * ffz - find first zero in word.
 * @word: The word to search
 *
 * Undefined if no zero exists, so code should check against ~0UL first.
 */
#define ffz(x) __ffs(~(x))

/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
static inline int fls(int x)
{
    if (!x)
    {
        return 0;
    }
    return 32 - __fls(x);
}

/**
 * ffs - find first bit set
 * @x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 * Note ffs(0) = 0, ffs(1) = 1, ffs(0x80000000) = 32.
 */
static inline int ffs(int x)
{
    if (!x)
    {
        return 0;
    }
    return __ffs(x) + 1;
}

#endif /* __TRAP_H__ */
