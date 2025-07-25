 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <soc.h>
#include <csi_core.h>
#include <drv/tick.h>
#include <drv/porting.h>
#include <drv/irq.h>
#include "riscv_csr.h"

#if (defined(CONFIG_KERNEL_RHINO) || defined(CONFIG_KERNEL_FREERTOS) || defined(CONFIG_KERNEL_RTTHREAD)) && defined(CONFIG_KERNEL_NONE)
#error "Please check the current system is baremetal or not!!!"
#endif

#if !defined(CONFIG_SMP) || (defined(CONFIG_SMP) && !CONFIG_SMP)
#if CONFIG_NR_CPUS > 1
#error "Please define CONFIG_NR_CPUS as 1 or do not need define."
#endif
#endif

#if !CONFIG_INTC_CLIC_PLIC && CONFIG_SUPPORT_IRQ_NESTED
#error "Please disable CONFIG_SUPPORT_IRQ_NESTED in package.yaml when use PLIC."
#endif

#if CONFIG_ECC_L2_ENABLE
static csi_dev_t ecc_l2_dev;
#endif

extern void section_data_copy(void);
extern void section_ram_code_copy(void);
extern void section_bss_clear(void);

#ifdef CONFIG_RISCV_SMODE
extern unsigned long __Vectors;
unsigned long page_table_l2[512] __attribute__ ((aligned(4096)));
unsigned long page_table_l1[512] __attribute__ ((aligned(4096)));
unsigned long page_table_l0[512] __attribute__ ((aligned(4096)));

void _mmu_init(void) __attribute__((noinline));
void _mmu_init(void)
{
#if CONFIG_CPU_XUANTIE_C906 || CONFIG_CPU_XUANTIE_C906FD || CONFIG_CPU_XUANTIE_C906FDV \
    || CONFIG_CPU_XUANTIE_C908 || CONFIG_CPU_XUANTIE_C908V || CONFIG_CPU_XUANTIE_C908I \
    || CONFIG_CPU_XUANTIE_R910 || CONFIG_CPU_XUANTIE_R920
    unsigned long status = __get_MXSTATUS();
    /* open MAEE for thead-mmu extension */
    status |= (1 << 21);
    __set_MXSTATUS(status);

    page_table_l2[0] = 0x1 | ((unsigned long)page_table_l1 >> 12) << 10;
    page_table_l1[0] = 0x1 | ((unsigned long)page_table_l0 >> 12) << 10;
    /* setup mmu VA(0M ~ 1M-1) <==>  PA(0M ~ 1M-1) */
    for (unsigned long i = 0; i < 256; i++) {
        page_table_l0[i] = (UPPER_ATTRS(ATTR_CA | ATTR_SH) | i << 10 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
    }

    /* setup mmu VA(2M ~ 1G-1) <==>  PA(2M ~ 1G-1) */
    for (unsigned long i = 1; i < 512; i++) {
        page_table_l1[i] = (UPPER_ATTRS(ATTR_SO | ATTR_SH) | i << 19 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
    }

    /* setup mmu VA(1G ~ 2G-1) <==>  PA(1G ~ 2G-1) */
    page_table_l2[1] = (UPPER_ATTRS(ATTR_CA | ATTR_SH) | (1) << 28 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
#elif CONFIG_CPU_XUANTIE_C907_RV32 || CONFIG_CPU_XUANTIE_C907FD_RV32 || CONFIG_CPU_XUANTIE_C907FDV_RV32 || CONFIG_CPU_XUANTIE_C907FDVM_RV32
    unsigned long envcfgh = __get_MENVCFGH();
    /* enable svpbmt */
    envcfgh |= (1 << 30);
    __set_MENVCFGH(envcfgh);

    page_table_l1[0] = 0x1 | ((unsigned long)page_table_l0 >> 12) << 10;
    /* setup mmu VA(0M ~ 1M-1) <==>  PA(0M ~ 1M-1) */
    for (unsigned long i = 0; i < 256; i++) {
        page_table_l0[i] = (SVPBMT_PMA | (i) << 10 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
    }

    /* setup mmu VA(4M ~ 1G-1) <==>  PA(4M ~ 1G-1) */
    for (unsigned long i = 1; i < 256; i++) {
        page_table_l1[i] = (SVPBMT_IO | (i) << 20 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
    }

    /* setup mmu VA(1G ~ 2G-1) <==>  PA(1G ~ 2G-1) */
    for (unsigned long i = 256; i < 512; i++) {
        page_table_l1[i] = (SVPBMT_PMA | (i) << 20 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
    }
#else
    unsigned long envcfg = __get_MENVCFG();
    /* enable svpbmt */
    envcfg |= (1ull << 62);
    __set_MENVCFG(envcfg);

    page_table_l2[0] = 0x1 | ((unsigned long)page_table_l1 >> 12) << 10;
    page_table_l1[0] = 0x1 | ((unsigned long)page_table_l0 >> 12) << 10;
    /* setup mmu VA(0M ~ 1M-1) <==>  PA(0M ~ 1M-1) */
    for (unsigned long i = 0; i < 256; i++) {
        page_table_l0[i] = (SVPBMT_PMA | (i) << 10 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
    }

    /* setup mmu VA(2M ~ 1G-1) <==>  PA(2M ~ 1G-1) */
    for (unsigned long i = 1; i < 512; i++) {
        page_table_l1[i] = (SVPBMT_IO | (i) << 19 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
    }

    /* setup mmu VA(1G ~ 2G-1) <==>  PA(1G ~ 2G-1) */
    page_table_l2[1] = (SVPBMT_PMA | (1) << 28 | LOWER_ATTRS(DIRTY_FLAG | ACCESS_FLAG | AP_X | AP_W | AP_R | GLOBAL_FLAG)) | 0x1;
#endif

#if __riscv_xlen == 64
    csi_dcache_clean_range((unsigned long *)&page_table_l2, sizeof(page_table_l2));
#endif
    csi_dcache_clean_range((unsigned long *)&page_table_l1, sizeof(page_table_l1));
    csi_dcache_clean_range((unsigned long *)&page_table_l0, sizeof(page_table_l0));
    csi_mmu_invalid_tlb_all();
#if __riscv_xlen == 64
    __set_SATP(((unsigned long)&page_table_l2 >> 12));
    csi_mmu_set_mode(MMU_MODE_39);
    csi_mmu_enable();
#else
    __set_SATP(((unsigned long)&page_table_l1 >> 12));
    csi_mmu_set_mode(MMU_MODE_32);
    csi_mmu_enable();
#endif
}

void _system_switchto_smode(void)
{
    unsigned long m_status = __get_MSTATUS();
    m_status &= ~MSTATUS_TVM_MASK;
    m_status &= ~MSTATUS_MPP_MASK;
    m_status |= MSTATUS_MPP_S;
    __set_MSTATUS(m_status);

    /* setup S-Mode csr regs */
    __set_STVEC((unsigned long)(&__Vectors) | 0x1);
    //FIXME:
    __ASM("auipc a0, 0");
    __ASM("addi  a0, a0, 14");
    __ASM("csrw  mepc, a0");
    __ASM("mret");
}

void _system_init_for_smode(void)
{
    _system_switchto_smode();
}

void smode_init(void)
{
    /* may be not clear after reset on FPGA */
    csi_mmu_disable();
    _mmu_init();
    _system_init_for_smode();
}
#endif

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

static void fpp_init(void)
{
#if CONFIG_FPP_ENABLE
    csi_fpp_set_base_addr(0x19000000);
    csi_fpp_enable();
#endif
}

#if CONFIG_INTC_CLIC_PLIC
static void clic_init(void)
{
    int i;

    /* get interrupt level from info */
    CLIC->CLICCFG = (((CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos) << CLIC_CLICCFG_NLBIT_Pos);

    for (i = 0; i < 64; i++) {
        uint8_t nlbits = (CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
        CLIC->CLICINT[i].CTL = (CLIC->CLICINT[i].CTL & (~CLIC_INTCFG_PRIO_Msk)) | (0x1 << (8 - nlbits));
        CLIC->CLICINT[i].IP = 0;
        CLIC->CLICINT[i].ATTR = 1; /* use vector interrupt */
    }

    /* tspend use positive interrupt */
    CLIC->CLICINT[Machine_Software_IRQn].ATTR = 0x3;
    csi_irq_enable(Machine_Software_IRQn);

    /* enable external plic interrupt */
    csi_irq_enable(Machine_External_IRQn);

#if CONFIG_ECC_L1_ENABLE || CONFIG_ECC_ITCM_ENABLE || CONFIG_ECC_DTCM_ENABLE
    CLIC->CLICINT[L1_CACHE_ECC_IRQn].ATTR = 0x3;
    csi_irq_enable(L1_CACHE_ECC_IRQn);
#endif
}
#endif

static void interrupt_init(void)
{
    int i;

#if CONFIG_INTC_CLIC_PLIC
    clic_init();
    for (i = 0; i < CONFIG_IRQ_NUM - PLIC_IRQ_OFFSET; i++) {
        PLIC->PLIC_PRIO[i] = 31;
    }

    for (i = 0; i < (CONFIG_IRQ_NUM - PLIC_IRQ_OFFSET + 32) / 32; i++) {
        PLIC->PLIC_IP[i] = 0;
    }

    for (i = 0; i < (CONFIG_IRQ_NUM - PLIC_IRQ_OFFSET + 32) / 32; i++) {
        PLIC->PLIC_H0_MIE[i] = 0;
        PLIC->PLIC_H0_SIE[i] = 0;
    }

    /* set hart threshold 0, enable all interrupt */
    PLIC->PLIC_H0_MTH = 0;
    PLIC->PLIC_H0_STH = 0;

    for (i = 0; i < CONFIG_IRQ_NUM - PLIC_IRQ_OFFSET; i++) {
        PLIC->PLIC_H0_MCLAIM = i;
        PLIC->PLIC_H0_SCLAIM = i;
    }

    /* set PLIC_PER */
    PLIC->PLIC_PER = 0x1;
#else
    for (i = 0; i < CONFIG_IRQ_NUM; i++) {
        PLIC->PLIC_PRIO[i] = 31;
    }

    for (i = 0; i < (CONFIG_IRQ_NUM + 32) / 32; i++) {
        PLIC->PLIC_IP[i] = 0;
    }

    for (i = 0; i < (CONFIG_IRQ_NUM + 32) / 32; i++) {
        PLIC->PLIC_H0_MIE[i] = 0;
        PLIC->PLIC_H0_SIE[i] = 0;
    }

    /* set hart threshold 0, enable all interrupt */
    PLIC->PLIC_H0_MTH = 0;
    PLIC->PLIC_H0_STH = 0;

    for (i = 0; i < CONFIG_IRQ_NUM; i++) {
        PLIC->PLIC_H0_MCLAIM = i;
        PLIC->PLIC_H0_SCLAIM = i;
    }

    /* set PLIC_PER */
    PLIC->PLIC_PER = 0x1;

    /* enable MEIE & MTIE & MSIE */
    uint32_t mie = __get_MIE();
    mie |= (1 << 11 | 1 << 7 | 1 << 3);
#if CONFIG_ECC_L1_ENABLE || CONFIG_ECC_ITCM_ENABLE || CONFIG_ECC_DTCM_ENABLE
    mie |= (1 << 16);
#endif
    __set_MIE(mie);
#endif
}

static void section_init(void)
{
#if CONFIG_XIP
    section_data_copy();
    section_ram_code_copy();
    csi_dcache_clean();
    csi_icache_invalid();
#endif

    section_bss_clear();
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
#if CONFIG_CPU_XUANTIE_R908_CP || CONFIG_CPU_XUANTIE_R908FD_CP || CONFIG_CPU_XUANTIE_R908FDV_CP
    /* enable theadisaee & MM */
    unsigned long status = __get_MXSTATUS();
    status &= ~(1 << 22);
    status |= (1 << 24 | 1 << 15);
    __set_MXSTATUS(status);
#else
    /* enable theadisaee & MM */
    unsigned long status = __get_MXSTATUS();
    status |= (1 << 22 | 1 << 15);
    __set_MXSTATUS(status);
#endif

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

#if CONFIG_ECC_ITCM_ENABLE
    uint64_t mitcmcr = __get_MITCMCR();
    mitcmcr |= MITCMCR_ECC_EN_Msk;
    __set_MITCMCR(mitcmcr);
#endif

#if CONFIG_ECC_DTCM_ENABLE
    uint64_t mdtcmcr = __get_MDTCMCR();
    mdtcmcr |= MDTCMCR_ECC_EN_Msk;
    __set_MDTCMCR(mdtcmcr);
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
    section_init();
    pmp_init();
    fpp_init();

    interrupt_init();
    soc_set_sys_freq(20000000);
    csi_tick_init();

#if CONFIG_ECC_L2_ENABLE
    extern void ecc_l2_irqhandler(void *arg);
    /* l2 cache ecc interrupt register */
    ecc_l2_dev.irq_num = L2_CACHE_ECC_IRQn;
    csi_irq_attach(ecc_l2_dev.irq_num, ecc_l2_irqhandler, &ecc_l2_dev);
    csi_irq_enable(ecc_l2_dev.irq_num);
#endif
}
