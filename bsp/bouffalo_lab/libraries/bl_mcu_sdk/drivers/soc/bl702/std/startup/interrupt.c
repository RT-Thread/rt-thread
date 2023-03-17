/**
 * @file interrupt.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "bflb_core.h"

typedef void (*pFunc)(void);

struct bflb_irq_info_s g_irqvector[CONFIG_IRQ_NUM];

extern void default_trap_handler(void);
extern void default_interrupt_handler(void);

const pFunc __Vectors[] __attribute__((section(".vector"), aligned(64))) = {
    default_interrupt_handler, /*         */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /* 3       */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /* 7       */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /* 11      */
    default_interrupt_handler, /* 12      */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /*         */
    default_interrupt_handler, /* 16 +  0 */
    default_interrupt_handler, /* 16 +  1 */
    default_interrupt_handler, /* 16 +  2 */
    default_interrupt_handler, /* 16 +  3 */
    default_interrupt_handler, /* 16 +  4 */
    default_interrupt_handler, /* 16 +  5 */
    default_interrupt_handler, /* 16 +  6 */
    default_interrupt_handler, /* 16 +  7 */
    default_interrupt_handler, /* 16 +  8 */
    default_interrupt_handler, /* 16 +  9 */
    default_interrupt_handler, /* 16 + 10 */
    default_interrupt_handler, /* 16 + 11 */
    default_interrupt_handler, /* 16 + 12 */
    default_interrupt_handler, /* 16 + 13 */
    default_interrupt_handler, /* 16 + 14 */
    default_interrupt_handler, /* 16 + 15 */
    default_interrupt_handler, /* 16 + 16 */
    default_interrupt_handler, /* 16 + 17 */
    default_interrupt_handler, /* 16 + 18 */
    default_interrupt_handler, /* 16 + 19 */
    default_interrupt_handler, /* 16 + 20 */
    default_interrupt_handler, /* 16 + 21 */
    default_interrupt_handler, /* 16 + 22 */
    default_interrupt_handler, /* 16 + 23 */
    default_interrupt_handler, /* 16 + 24 */
    default_interrupt_handler, /* 16 + 25 */
    default_interrupt_handler, /* 16 + 26 */
    default_interrupt_handler, /* 16 + 27 */
    default_interrupt_handler, /* 16 + 28 */
    default_interrupt_handler, /* 16 + 29 */
    default_interrupt_handler, /* 16 + 30 */
    default_interrupt_handler, /* 16 + 31 */
    default_interrupt_handler, /* 16 + 32 */
    default_interrupt_handler, /* 16 + 33 */
    default_interrupt_handler, /* 16 + 34 */
    default_interrupt_handler, /* 16 + 35 */
    default_interrupt_handler, /* 16 + 36 */
    default_interrupt_handler, /* 16 + 37 */
    default_interrupt_handler, /* 16 + 38 */
    default_interrupt_handler, /* 16 + 39 */
    default_interrupt_handler, /* 16 + 40 */
    default_interrupt_handler, /* 16 + 41 */
    default_interrupt_handler, /* 16 + 42 */
    default_interrupt_handler, /* 16 + 43 */
    default_interrupt_handler, /* 16 + 44 */
    default_interrupt_handler, /* 16 + 45 */
    default_interrupt_handler, /* 16 + 46 */
    default_interrupt_handler, /* 16 + 47 */
    default_interrupt_handler, /* 16 + 48 */
    default_interrupt_handler, /* 16 + 49 */
    default_interrupt_handler, /* 16 + 50 */
    default_interrupt_handler, /* 16 + 51 */
    default_interrupt_handler, /* 16 + 52 */
    default_interrupt_handler, /* 16 + 53 */
    default_interrupt_handler, /* 16 + 54 */
    default_interrupt_handler, /* 16 + 55 */
    default_interrupt_handler, /* 16 + 56 */
    default_interrupt_handler, /* 16 + 57 */
    default_interrupt_handler, /* 16 + 58 */
    default_interrupt_handler, /* 16 + 59 */
    default_interrupt_handler, /* 16 + 60 */
    default_interrupt_handler, /* 16 + 61 */
    default_interrupt_handler, /* 16 + 62 */
    default_interrupt_handler, /* 16 + 63 */
};

void exception_entry(void)
{
    unsigned long cause;
    unsigned long epc;
    unsigned long tval;

    printf("exception_entry\r\n");

    cause = READ_CSR(CSR_MCAUSE);
    printf("mcause=%08x\r\n", (int)cause);
    epc = READ_CSR(CSR_MEPC);
    printf("mepc:%08x\r\n", (int)epc);
    tval = READ_CSR(CSR_MTVAL);
    printf("mtval:%08x\r\n", (int)tval);

    cause = (cause & 0x3ff);

#ifndef CONFIG_TRAP_DUMP_DISABLE
    const char *mcause_str[] = {
        "Instruction address misaligned",
        "Instruction access fault",
        "Illegal instruction",
        "Breakpoint",
        "Load address misaligned",
        "Load access fault",
        "Store/AMO address misaligned",
        "Store/AMO access fault",
        "Environment call from U-mode",
        "Environment call from S-mode",
        "RSVD",
        "Environment call from M-mode",
        "Instruction page fault",
        "Load page fault",
        "RSVD",
        "Store/AMO page fault"
    };

    printf("%s\r\n", mcause_str[cause & 0xf]);
#endif
    if ((cause == 8) || (cause == 11)) {
        epc += 4;
        WRITE_CSR(CSR_MEPC, epc);
    } else {
        while (1) {
        }
    }
}

void interrupt_entry(void)
{
    irq_callback handler;
    void *arg;
    volatile uint32_t mcause = 0UL;
    uint32_t irq_num;

    mcause = READ_CSR(CSR_MCAUSE);
    irq_num = mcause & 0x3FF;

    if (irq_num < CONFIG_IRQ_NUM) {
        handler = g_irqvector[irq_num].handler;
        arg = g_irqvector[irq_num].arg;
        if (handler) {
            handler(irq_num, arg);
        } else {
        }
    } else {
    }
}

__attribute__((interrupt, aligned(64))) void default_trap_handler(void)
{
    exception_entry();
}

__attribute__((interrupt)) __attribute__((weak)) void default_interrupt_handler(void)
{
    __asm volatile("addi sp,sp,-8");
    __asm volatile("csrr a0,mcause");
    __asm volatile("csrr a1,mepc");
    __asm volatile("sw a0,4(sp)");
    __asm volatile("sw a1,0(sp)");
    __asm volatile("csrsi mstatus,8");
    interrupt_entry();
    __asm volatile("csrci mstatus,8");
    __asm volatile("lw a1,0(sp)");
    __asm volatile("lw a0,4(sp)");
    __asm volatile("csrw mepc,a1");
    __asm volatile("csrw mcause,a0");
    __asm volatile("addi sp,sp,8");
}