/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: _cpu_asm.S
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-17 17:57:55
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "sdkconfig.h"

#ifdef CONFIG_TARGET_ARMV8_AARCH64
// ------------------------------------------------------------
  .global GetAffinity
  //uint32_t GetAffinity(void);
  .type GetAffinity, @function
GetAffinity:
  MRS      x0, MPIDR_EL1
  RET

 
.global ArchSpinLock;
.text;             
ArchSpinLock:                      
    mov     w2, #1
    sevl
1:
    wfe
    ldaxr   w1, [x0]
    cbnz    w1, 1b
    stxr    w1, w2, [x0]
    cbnz    w1, 1b
    ret


.global ArchSpinUnlock;
.text;           
ArchSpinUnlock:
    stlr    xzr, [x0]
    ret

#else

.globl GetAffinity
GetAffinity:
    mrc     p15, #0, r0, c0, c0, #5         @ read multiprocessor affinity register
    bx      lr

#endif