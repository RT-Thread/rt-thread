/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#ifndef __CH56X_PFIC_H__
#define __CH56X_PFIC_H__

#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* IREG: IENR/IRER/IRSR/IPRR, make sure irqn be 12~59
*/
#define PFIC_IREG1_MASK     0xfffff000
#define PFIC_IREG2_MASK     0x0fffffff
#define PFIC_MAX_IREG_BITS  60

#define _pfic_ireg_bit_get(pfic, IREG, irqn) \
        ((pfic->IREG[(irqn) >> 5] >> ((irqn) & 0x1f)) & 1)

#define _pfic_ireg_bit_set(pfic, IREG, irqn) \
        do pfic->IREG[(irqn) >> 5] = 1 << ((irqn) & 0x1f); while(0)

#define _pfic_irqn_enable(pfic, irqn)  _pfic_ireg_bit_set(pfic, IENR, irqn)
#define _pfic_irqn_disable(pfic, irqn) _pfic_ireg_bit_set(pfic, IRER, irqn)

/* Note: `union _pfic_cfgr` is not used directly in the reg structure */
union _pfic_cfgr
{
    uint32_t reg;
    struct
    {
        uint32_t hwstkctrl  : 1;    // RW, hw stack push/pop control (0:enable)
        uint32_t nestctrl   : 1;    // RW, nested intr enable control (0:enable)
        uint32_t nmiset     : 1;    // WO, write 1 to set NMI pending
        uint32_t nmireset   : 1;    // WO, write 1 to reset NMI pending
        uint32_t excset     : 1;    // WO, write 1 to set exception pending
        uint32_t excreset   : 1;    // WO, write 1 to reset exception pending
        uint32_t pficreset  : 1;    // WO, write 1 to reset PFIC module, auto clear
        uint32_t sysreset   : 1;    // WO, write 1 for a system reset, auto clear
        uint32_t resv_8     : 8;
        uint32_t keycode    : 16;   // WO, write protection keycode
    };
};
#define PFIC_CFGR_KEY1      0xfa05  // for hwstkctrl & nestctrl
#define PFIC_CFGR_KEY2      0xbcaf  // for nmi & exc set/reset
#define PFIC_CFGR_KEY3      0xbeef  // for sysreset

#define PFIC_CFGR_NMISET            (PFIC_CFGR_KEY2 << 16 | 1 << 2)
#define PFIC_CFGR_NMIRESET          (PFIC_CFGR_KEY2 << 16 | 1 << 3)
#define PFIC_CFGR_EXCSET            (PFIC_CFGR_KEY2 << 16 | 1 << 4)
#define PFIC_CFGR_EXCRESET          (PFIC_CFGR_KEY2 << 16 | 1 << 5)
#define PFIC_CFGR_PFICRESET         (1 << 6)
#define PFIC_CFGR_SYSRESET          (PFIC_CFGR_KEY3 << 16 | 1 << 7)

#define CFGR_HWSTKCTRL_ENABLE       (0 << 0)
#define CFGR_HWSTKCTRL_DISABLE      (1 << 0)
#define CFGR_HWSTKCTRL_MASK         (1 << 0)
#define CFGR_NESTCTRL_ENABLE        (0 << 1)
#define CFGR_NESTCTRL_DISABLE       (1 << 1)
#define CFGR_NESTCTRL_MASK          (1 << 1)
#define cfgr_nest_hwstk(v)          (PFIC_CFGR_KEY1 << 16 | (v))

union _pfic_gisr
{
    uint32_t reg;
    struct
    {
        uint32_t neststa    : 8;    // RO, nested interrupt state (0/1/2)
        uint32_t gactsta    : 1;    // RO, global interrupt active status
        uint32_t gpendsta   : 1;    // RO, global interrupt pending status
        uint32_t resv_10    : 22;
    };
};
#define PFIC_NESTSTA_NONE   0
#define PFIC_NESTSTA_L1     1
#define PFIC_NESTSTA_L2     2

union _pfic_fiofaddrr
{
    uint32_t reg;
    struct
    {
        uint32_t offaddr    : 24;   // RW
        uint32_t irqid      : 8;    // RW
    };
};

union _pfic_sctlr
{
    uint32_t reg;
    struct
    {
        uint32_t resv_0         : 1;
        uint32_t sleeponexit    : 1;  // enter (deep) sleep mode on isr exiting
        uint32_t sleepdeep      : 1;  // RW, 0/1 for sleep/deep-sleep mode
        uint32_t wfitowfe       : 1;  // RW, treat WFI as WFE
        uint32_t sevonpend      : 1;  // RW
        uint32_t setevent       : 1;  // WO, set event for WFE
        uint32_t resv_6         : 26;
    };
};

/*
 * 0x000  R32_PFIC_ISR1:        PFIC interrupt enable status (# 12-31)
 * 0x004  R32_PFIC_ISR2:        PFIC interrupt enable status (# 32-59)
 * 0x020  R32_PFIC_IPR1:        PFIC interrupt pending status (# 12-31)
 * 0x024  R32_PFIC_IPR2:        PFIC interrupt pending status (# 32-59)
 * 0x040  R32_PFIC_ITHRESDR:    PFIC interrupt priority threshold (B.7-4)
 * 0x044  R32_PFIC_FIBADDRR:    PFIC fast intr base address (B.31-28)
 * 0x048  R32_PFIC_CFGR:        PFIC interrupt configuration register
 * 0x04c  R32_PFIC_GISR:        PFIC global interrupt status register
 * 0x060  R32_PFIC_FIOFADDRR0:  PFIC fast intr 0 offset address (B.23-0)
 * 0x064  R32_PFIC_FIOFADDRR1:  PFIC fast intr 1 offset address (B.23-0)
 * 0x068  R32_PFIC_FIOFADDRR2:  PFIC fast intr 2 offset address (B.23-0)
 * 0x06c  R32_PFIC_FIOFADDRR3:  PFIC fast intr 3 offset address (B.23-0)
 * 0x100  R32_PFIC_IENR1:       PFIC interrupt enable register (# 12-31)
 * 0x104  R32_PFIC_IENR2:       PFIC interrupt enable register (# 32-59)
 * 0x180  R32_PFIC_IRER1:       PFIC interrupt reset register (# 12-31)
 * 0x184  R32_PFIC_IRER2:       PFIC interrupt reset register (# 32-59)
 * 0x200  R32_PFIC_IPSR1:       PFIC interrupt pending set register (# 12-31)
 * 0x204  R32_PFIC_IPSR2:       PFIC interrupt pending set register (# 32-59)
 * 0x280  R32_PFIC_IPRR1:       PFIC interrupt pending reset register (# 12-31)
 * 0x284  R32_PFIC_IPRR2:       PFIC interrupt pending reset register (# 32-59)
 * 0x300  R32_PFIC_IACTR1:      PFIC interrupt active status register (# 12-31)
 * 0x304  R32_PFIC_IACTR2:      PFIC interrupt active status register (# 32-59)
 * 0x400  R32_PFIC_IPRIORx:     PFIC interrupt priority registers
 * 0xd10  R32_PFIC_SCTLR:       PFIC system control register
 *
 * CAVEAT: gcc (as of 8.2.0) tends to read 32-bit word for bit field test.
 * Be careful for those with side effect for read.
 */
struct pfic_registers
{
    uint32_t              ISR[2];
    uint32_t              resv_08[6];
    uint32_t              IPR[2];
    uint32_t              resv_28[6];
    uint32_t              ITHRESDR;
    uint32_t              FIBADDRR;
    uint32_t              CFGR;
    union _pfic_gisr      GISR;
    uint32_t              resv_50[4];
    union _pfic_fiofaddrr FIOFADDRR[4];
    uint32_t              resv_70[36];
    uint32_t              IENR[2];
    uint32_t              resv_108[30];
    uint32_t              IRER[2];
    uint32_t              resv_188[30];
    uint32_t              IPSR[2];
    uint32_t              resv_208[30];
    uint32_t              IPRR[2];
    uint32_t              resv_288[30];
    uint32_t              IACTR[2];
    uint32_t              resv_308[62];
    uint8_t               IPRIOR[256];
    uint32_t              resv_500[516];
    union _pfic_sctlr     SCTLR;
} __packed;

CHECK_STRUCT_SIZE(struct pfic_registers, 0xd14);

union _systick_ctlr
{
    uint32_t reg;
    struct
    {
        uint32_t ste        : 1;  // RW, systick enable
        uint32_t stie       : 1;  // RW, systick interrupt enable
        uint32_t stclk      : 1;  // RW, systick clock source select
        uint32_t resv_3     : 5;
        uint32_t streload   : 1;  // W1, write 1 to reload systick
        uint32_t resv_9     : 23;
    };
};
#define RB_STKCTL_STE       0x001
#define RB_STKCTL_STIE      0x002
#define RB_STKCTL_STCLK     0x004
#define RB_STKCTL_STRELOAD  0x100

#define SYSTICK_SRC_HCLK_8  0
#define SYSTICK_SRC_HCLK    1

union _systick_cntfg
{
    uint32_t reg;
    struct
    {
        uint32_t swie       : 1;  // RW, software interrupt enable
        uint32_t cntif      : 1;  // RW0, counter dec to 0 (write 0 to clear)
        uint32_t resv_2     : 30;
    };
};
#define RB_CNTFG_SWIE       0X01
#define RB_CNTFG_CNTIF      0X02

/*
 * 0x00  R32_STK_CTLR:   SysTick control register
 * 0x04  R32_STK_CNTL:   SysTick counter, Lo.32
 * 0x08  R32_STK_CNTH:   SysTick counter, Hi.32
 * 0x0c  R32_STK_CMPLR:  SysTick compare-reload register, Lo.32
 * 0x10  R32_STK_CMPHR:  SysTick compare-reload register, Hi.32
 * 0x14  R32_STK_CNTFG:  SysTick counter flags
 *
 * CAVEAT: gcc (as of 8.2.0) tends to read 32-bit word for bit field test.
 * Be careful for those with side effect for read.
 */
struct systick_registers
{
    union _systick_ctlr   CTLR;
    uint32_t              CNTL;
    uint32_t              CNTH;
    uint32_t              CMPLR;
    uint32_t              CMPHR;
    union _systick_cntfg  CNTFG;
} __packed;

CHECK_STRUCT_SIZE(struct systick_registers, 0x18);

rt_inline void pfic_interrupt_umask(uint8_t irqn)
{
    volatile struct pfic_registers *pfic;

    if (irqn < PFIC_MAX_IREG_BITS)
    {
        pfic = (void *)PFIC_REG_BASE;
        _pfic_ireg_bit_set(pfic, IENR, irqn);
    }
}

rt_inline void pfic_interrupt_mask(uint8_t irqn)
{
    volatile struct pfic_registers *pfic;

    if (irqn < PFIC_MAX_IREG_BITS)
    {
        pfic = (void *)PFIC_REG_BASE;
        _pfic_ireg_bit_set(pfic, IRER, irqn);
    }
}

void pfic_swi_pendset(void);
void pfic_swi_pendreset(void);
void pfic_cfgr_set(uint32_t key_bit);
void systick_init(uint32_t count);

#ifdef __cplusplus
}
#endif

#endif
