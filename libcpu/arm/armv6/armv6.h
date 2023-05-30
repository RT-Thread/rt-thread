/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __ARMV6_H__
#define __ARMV6_H__


/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE        0x10
#define FIQMODE         0x11
#define IRQMODE         0x12
#define SVCMODE         0x13
#define ABORTMODE       0x17
#define UNDEFMODE       0x1b
#define MODEMASK        0x1f
#define NOINT           0xc0

#ifndef __ASSEMBLY__
struct rt_hw_register
{
    rt_uint32_t cpsr;
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t fp;
    rt_uint32_t ip;
    rt_uint32_t sp;
    rt_uint32_t lr;
    rt_uint32_t pc;
};
#if(0)
struct rt_hw_register{
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t fp;
    rt_uint32_t ip;
    rt_uint32_t sp;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t cpsr;
    rt_uint32_t ORIG_r0;
};
#endif
#endif

/* rt_hw_register offset */
#define S_FRAME_SIZE        68

#define S_PC                64
#define S_LR                60
#define S_SP                56
#define S_IP                52
#define S_FP                48
#define S_R10               44
#define S_R9                40
#define S_R8                36
#define S_R7                32
#define S_R6                28
#define S_R5                24
#define S_R4                20
#define S_R3                16
#define S_R2                12
#define S_R1                8
#define S_R0                4
#define S_CPSR              0


#endif
