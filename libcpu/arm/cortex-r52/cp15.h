/*
 * Copyright (c) 2011-2024, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-29     RT-Thread    first version
 */

#ifndef __CP15_H__
#define __CP15_H__

#define __get_cp(cp, op1, Rt, CRn, CRm, op2) \
    __asm volatile("MRC p" # cp ", " # op1 ", %0, c" # CRn ", c" # CRm ", " # op2 : "=r" (Rt) : : "memory" )
#define __set_cp(cp, op1, Rt, CRn, CRm, op2) \
    __asm volatile("MCR p" # cp ", " # op1 ", %0, c" # CRn ", c" # CRm ", " # op2 : : "r" (Rt) : "memory" )
#define __get_cp64(cp, op1, Rt, CRm) \
    __asm volatile("MRRC p" # cp ", " # op1 ", %Q0, %R0, c" # CRm  : "=r" (Rt) : : "memory" )
#define __set_cp64(cp, op1, Rt, CRm) \
    __asm volatile("MCRR p" # cp ", " # op1 ", %Q0, %R0, c" # CRm  : : "r" (Rt) : "memory" )

#endif
