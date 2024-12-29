/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/12/11     flyingcys    The first version
 */

#include <csi_core.h>
#include "riscv_csr.h"

/**
  * @brief  initialize pmp
  * @param  None
  * @return None
  */
static void pmp_init(void)
{
    long addr;

    addr = 0x90000000UL >> 2;
    __set_PMPADDR0(addr);
    __set_PMPxCFG(0, 0x8f);
}

static void cache_init(void)
{
    /* enable cache */
    csi_dcache_enable();
    csi_icache_enable();
}

/**
  * @brief  initialize the system
  *         Initialize the psr and vbr.
  * @param  None
  * @return None
  */
void SystemInit(void)
{
    /* enable theadisaee & MM */
    unsigned long status = __get_MXSTATUS();
    status |= (1 << 22 | 1 << 15);
    __set_MXSTATUS(status);

#if __riscv_flen == 64
    /* enable float ISA */
    status = __get_MSTATUS();
    status |= (1 << MSTATUS_FS_SHIFT);
    __set_MSTATUS(status);
#endif
#ifdef __riscv_vector
    /* enable vector ISA */
    status = __get_MSTATUS();
    status |= (1 << MSTATUS_VS_SHIFT);
    __set_MSTATUS(status);
#endif

#if CONFIG_ECC_L1_ENABLE
    /* enable L1 cache ecc */
    uint64_t mhint = __get_MHINT();
    mhint |= (0x1 << 19);
    __set_MHINT(mhint);
#endif

#if CONFIG_ECC_L2_ENABLE
    /* enable L2 cache ecc */
    uint64_t mccr2 = __get_MCCR2();
    mccr2 |= (0x1 << 1);
    __set_MCCR2(mccr2);
#endif

#ifdef CONFIG_RISCV_SMODE
    /* enable ecall delegate */
    unsigned long medeleg = __get_MEDELEG();
    medeleg |= (1 << 9);
    __set_MEDELEG(medeleg);

    /* enable interrupt delegate */
    unsigned long mideleg = __get_MIDELEG();
    mideleg |= 0x222;
    __set_MIDELEG(mideleg);
#endif

#ifdef CONFIG_RISCV_SMODE
    /* enable mcounteren for s-mode */
    __set_MCOUNTEREN(0xffffffff);

#if CBO_INSN_SUPPORT
    unsigned long envcfg = __get_MENVCFG();
    /* enable CBIE & CBCFE & CBZE on lower priviledge */
    envcfg |= (3 << 4 | 1 << 6 | 1 << 7);
    __set_MENVCFG(envcfg);
#endif
#endif

    cache_init();
    section_bss_clear();
    pmp_init();

#if CONFIG_ECC_L2_ENABLE
    extern void ecc_l2_irqhandler(void *arg);
    /* l2 cache ecc interrupt register */
    ecc_l2_dev.irq_num = L2_CACHE_ECC_IRQn;
    csi_irq_attach(ecc_l2_dev.irq_num, ecc_l2_irqhandler, &ecc_l2_dev);
    csi_irq_enable(ecc_l2_dev.irq_num);
#endif
}