/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-23     Wangshun     first version
 */

#include <board.h>
#include <rthw.h>
#include <rtthread.h>
#include <drv_usart.h>

extern unsigned long __heap_start;
extern unsigned long __heap_end;

/**
 * This function will initialize your board.
 */
void rt_hw_board_init()
{
    rt_hw_interrupt_init();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)&__heap_start, (void *)&__heap_end);
#endif

#ifdef BSP_USING_UART
    rt_hw_usart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

#ifdef RT_USING_SMP
#include <csi_core.h>

extern void Reset_Handler(void);

static struct c9xx_regs_struct {
    uint64_t pmpaddr0;
    uint64_t pmpaddr1;
    uint64_t pmpaddr2;
    uint64_t pmpaddr3;
    uint64_t pmpaddr4;
    uint64_t pmpaddr5;
    uint64_t pmpaddr6;
    uint64_t pmpaddr7;
    uint64_t pmpcfg0;
    uint64_t mcor;
    uint64_t mhcr;
    uint64_t mccr2;
    uint64_t mhint;
    uint64_t msmpr;
    uint64_t mie;
    uint64_t mxstatus;
    uint64_t mtvec;
    uint64_t plic_base_addr;
    uint64_t clint_base_addr;
} c9xx_regs;

#define C9xx_PLIC_CLINT_OFFSET     0x04000000  /* 64M */
#define C9xx_PLIC_DELEG_OFFSET     0x001ffffc
#define C9xx_PLIC_DELEG_ENABLE     0x1

#define XIAOHUI_SRESET_BASE                 0x18030000
#define XIAOHUI_SRESET_ADDR_OFFSET          0x10
#define PRIMARY_STARTUP_CORE_ID                0

static void c9xx_csr_copy(void)
{
    if (PRIMARY_STARTUP_CORE_ID == csi_get_cpu_id()) {
        /* Load from boot core */
        c9xx_regs.pmpaddr0 = rv_csr_read(CSR_PMPADDR0);
        c9xx_regs.pmpaddr1 = rv_csr_read(CSR_PMPADDR1);
        c9xx_regs.pmpaddr2 = rv_csr_read(CSR_PMPADDR2);
        c9xx_regs.pmpaddr3 = rv_csr_read(CSR_PMPADDR3);
        c9xx_regs.pmpaddr4 = rv_csr_read(CSR_PMPADDR4);
        c9xx_regs.pmpaddr5 = rv_csr_read(CSR_PMPADDR5);
        c9xx_regs.pmpaddr6 = rv_csr_read(CSR_PMPADDR6);
        c9xx_regs.pmpaddr7 = rv_csr_read(CSR_PMPADDR7);
        c9xx_regs.pmpcfg0  = rv_csr_read(CSR_PMPCFG0);
        c9xx_regs.mcor     = rv_csr_read(CSR_MCOR);
        c9xx_regs.msmpr    = rv_csr_read(CSR_MSMPR);
        c9xx_regs.mhcr     = rv_csr_read(CSR_MHCR);
        c9xx_regs.mccr2    = rv_csr_read(CSR_MCCR2);
        c9xx_regs.mhint    = rv_csr_read(CSR_MHINT);
        c9xx_regs.mtvec    = rv_csr_read(CSR_MTVEC);
        c9xx_regs.mie      = rv_csr_read(CSR_MIE);
        c9xx_regs.mxstatus = rv_csr_read(CSR_MXSTATUS);

        c9xx_regs.plic_base_addr = rv_csr_read(CSR_MAPBADDR);
        c9xx_regs.clint_base_addr = c9xx_regs.plic_base_addr + C9xx_PLIC_CLINT_OFFSET;
    } else {
        /* Store to other core */
        // rv_csr_write(CSR_PMPADDR0, c9xx_regs.pmpaddr0);
        // rv_csr_write(CSR_PMPADDR1, c9xx_regs.pmpaddr1);
        // rv_csr_write(CSR_PMPADDR2, c9xx_regs.pmpaddr2);
        // rv_csr_write(CSR_PMPADDR3, c9xx_regs.pmpaddr3);
        // rv_csr_write(CSR_PMPADDR4, c9xx_regs.pmpaddr4);
        // rv_csr_write(CSR_PMPADDR5, c9xx_regs.pmpaddr5);
        // rv_csr_write(CSR_PMPADDR6, c9xx_regs.pmpaddr6);
        // rv_csr_write(CSR_PMPADDR7, c9xx_regs.pmpaddr7);
        // rv_csr_write(CSR_PMPCFG0,  c9xx_regs.pmpcfg0);
        rv_csr_write(CSR_MCOR,     c9xx_regs.mcor);
        rv_csr_write(CSR_MSMPR,    c9xx_regs.msmpr);
        rv_csr_write(CSR_MHCR,     c9xx_regs.mhcr);
        rv_csr_write(CSR_MHINT,    c9xx_regs.mhint);
        // rv_csr_write(CSR_MTVEC,    c9xx_regs.mtvec);
        // rv_csr_write(CSR_MIE,      c9xx_regs.mie);
        rv_csr_write(CSR_MXSTATUS, c9xx_regs.mxstatus);
    }
}

void riscv_soc_start_cpu(int cpu_num)
{
    if (cpu_num < 1) {
        return;
    }

    c9xx_csr_copy();

    *(unsigned long *)((unsigned long)XIAOHUI_SRESET_BASE + XIAOHUI_SRESET_ADDR_OFFSET + ((cpu_num - 1) << 3)) = (unsigned long)Reset_Handler;
#if __riscv_xtheadsync
    __ASM("sync");
#endif

    /* Release secondary cpus, Determined by the xiaohui FPGA platform */
    *(uint32_t *)(XIAOHUI_SRESET_BASE) = 0x7f;
    // uint32_t mrmr = *(uint32_t *)(XIAOHUI_SRESET_BASE);
    // *(uint32_t *)(XIAOHUI_SRESET_BASE) = mrmr | (0x1 << (cpu_num - 1));
#if __riscv_xtheadsync
    __ASM("sync");
#endif
}
#endif /* RT_USING_SMP */
