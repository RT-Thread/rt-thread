/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting implementation
 * 2018/12/27     Jesven       Add SMP support
 * 2021/02/02     lizhirui     Add userspace support
 * 2022/10/22     Shell        Support User mode RVV;
 *                             Trimming process switch context
 * 2024/09/01     Shell        Separated vector ctx from the generic
 */

#include "cpuport.h"
#include "stackframe.h"

/**
 * @param a0 pointer to frame bottom
 */
.global rt_hw_vector_ctx_save
rt_hw_vector_ctx_save:
    SAVE_VECTOR a0
    ret

/**
 * @param a0 pointer to frame bottom
 */
.global rt_hw_vector_ctx_restore
rt_hw_vector_ctx_restore:
    RESTORE_VECTOR a0
    ret

.global rt_hw_disable_vector
rt_hw_disable_vector:
    li t0, SSTATUS_VS
    csrc sstatus, t0
    ret

.global rt_hw_enable_vector
rt_hw_enable_vector:
    li t0, SSTATUS_VS
    csrs sstatus, t0
    ret
