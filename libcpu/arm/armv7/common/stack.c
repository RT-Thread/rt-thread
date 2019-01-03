/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <rtthread.h>
#include "armv7.h"
#include <cp15.h>

extern uint32_t rt_hw_get_vfp_neon_qreg_nums(void);

// This function will initialize thread stack
// @param tentry the entry of thread
// @param parameter the parameter of entry
// @param stack_addr the beginning stack address
// @param texit the function will be called when thread exit
// @return stack address
uint8_t *rt_hw_stack_init(void *tentry, void *parameter, uint8_t *stack_addr, void *texit)
{
    uint32_t *stk;

    stack_addr += sizeof(uint32_t);
    stack_addr = (uint8_t *)RT_ALIGN_DOWN((uint32_t)stack_addr, 8);
    stk = (uint32_t *)stack_addr;

    // thread stack
    //              offset  words           note
    // |  pc  |     0       1(4bytes)
    // |  lr  |     -4      1
    // |  r12 |     -8      1
    // |  ... |
    // |  r1  |     -52     1
    // |  r0  |     -56     1
    // | cpsr |     -60     1
    // | fpscr|     -64     1
    // |   0  |     -68     1               Make the number of registers pushed in even
    // |  q15 |             4               RT_USING_VFP_NEON_Q16
    // |  ... |             4               RT_USING_VFP_NEON_Q16
    // |  q8  |             4               RT_USING_VFP_NEON_Q16
    // |  q7  |             4
    // |  ... |             4
    // |  q0  |             4
    // --------SP
    *(--stk) = (uint32_t)tentry;            // entry point
    *(--stk) = (uint32_t)texit;             // lr
    *(--stk) = 0xdeadbeef;                  // r12
    *(--stk) = 0xdeadbeef;                  // r11
    *(--stk) = 0xdeadbeef;                  // r10
    *(--stk) = 0xdeadbeef;                  // r9
    *(--stk) = 0xdeadbeef;                  // r8
    *(--stk) = 0xdeadbeef;                  // r7
    *(--stk) = 0xdeadbeef;                  // r6
    *(--stk) = 0xdeadbeef;                  // r5
    *(--stk) = 0xdeadbeef;                  // r4
    *(--stk) = 0xdeadbeef;                  // r3
    *(--stk) = 0xdeadbeef;                  // r2
    *(--stk) = 0xdeadbeef;                  // r1
    *(--stk) = (uint32_t)parameter;         // r0 : argument

    if ((uint32_t)tentry & 0x01)
        *(--stk) = Mode_SVC | T_Bit;        // cpsr(thumb mode)
    else
        *(--stk) = Mode_SVC;                // cpsr(arm mode)

    uint32_t regNums = rt_hw_get_vfp_neon_qreg_nums();
    if (regNums != 0) {
        *(--stk) = rt_cpu_fpscr_get_default();  // fpscr
        *(--stk) = 0;
        
        if (regNums > 8) {
            // q8-q15
            for (uint32_t i = 0; i < 8 * 4; i++) {
                *(--stk) = 0;
            }
        }
        // q0-q7
        for (uint32_t i = 0; i < 8 * 4; i++) {
            *(--stk) = 0;
        }
    }

    // return task's current stack address
    return (uint8_t *)stk;
}
