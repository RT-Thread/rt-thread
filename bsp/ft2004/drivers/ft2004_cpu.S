/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-29     Carl    the first version
 *
 */

#include "rtconfig.h"

.globl rt_hw_cpu_id 
rt_hw_cpu_id:
    mrc p15, 0, r0, c0, c0, 5
    ubfx r0, r0, #0, #12
    cmp r0, #0
    beq core0
    cmp r0, #1
    beq core1 
    cmp r0, #256 
    beq core2  
    ldr r1,= #257
    cmp r0, r1
    beq core3
    b default
core0:
    mov r0, #0
    b return 
core1: 
    mov r0, #1
    b return 
core2: 
    mov r0, #2
    b return 
core3: 
    mov r0, #3
    b return 
default: 
    and r0, r0, #15
return: 
    bx lr 

