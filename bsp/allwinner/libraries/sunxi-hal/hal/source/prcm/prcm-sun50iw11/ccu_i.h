/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                         clock control unit module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : ccu_i.h
* By      : Sunny
* Version : v1.0
* Date    : 2012-5-7
* Descript: clock control unit internal header.
* Update  : date                auther      ver     notes
*           2012-5-7 8:40:42    Sunny       1.0     Create this file.
*********************************************************************************************************
*/

#ifndef __CCU_I_H__
#define __CCU_I_H__

#include "platform.h"
#include "ccu_regs.h"

#define R_PRCM_REG_BASE SUNXI_R_PRCM_PBASE
#define CCU_REG_BASE    SUNXI_CCU_REG_PBASE
// prcm regs
#define CCU_PLL_CTRL1   (R_PRCM_REG_BASE + 0x244)

// name by pll order
#define CCU_PLLx_REG(n) (R_PRCM_REG_BASE + 0x1000 + (0x8 * (n - 1)))

//name by pll function
#define CCU_PLL_C0_REG              (CCU_PLLx_REG(1))
#define CCU_PLL_DDR0_REG            (CCU_REG_BASE + 0x800)
/* #define CCU_PLL_DDR1_REG            (CCU_PLLx_REG(4)) */
#define CCU_PLL_PERIPH0_REG         (CCU_PLLx_REG(3))
/* #define CCU_PLL_PERIPH1_REG         (CCU_PLLx_REG(6)) */
#define CCU_PLL_VIDEO0_REG          (CCU_PLLx_REG(9))
#define CCU_PLL_VIDEO1_REG          (CCU_PLLx_REG(10))
#define CCU_PLL_VE_REG              (CCU_PLLx_REG(12))
#define CCU_PLL_DE_REG              (CCU_PLLx_REG(13))
#define CCU_PLL_HSIC_REG            (CCU_PLLx_REG(15))
#define CCU_PLL_AUDIO_REG           (CCU_PLLx_REG(16))
#define CCU_CPU_AXI_CFG_REG         (CCU_REG_BASE + 0x500)
#define CCU_PSI_AHB1_AHB2_CFG_REG   (CCU_REG_BASE + 0x510)
#define CCU_APB1_CFG_REG            (CCU_REG_BASE + 0x520)
#define CCU_APB2_CFG_REG            (CCU_REG_BASE + 0x524)
#define CCU_CCI_CFG_REG             (CCU_REG_BASE + 0x530)
#define CCU_MBUS_CLK_REG            (CCU_REG_BASE + 0x540)
#define CCU_MBUS_MASTER_CLK_REG     (CCU_REG_BASE + 0x804)
#define CCU_MSGBOX_BGR_REG          (CCU_REG_BASE + 0x71c)
#define CCU_SPINLOCK_BGR_REG        (CCU_REG_BASE + 0x72c)
#define CCU_DRAM_CLOCK_REG          (CCU_REG_BASE + 0x800)

#define CCU_R_AHBS_CFG_REG          (R_PRCM_REG_BASE + 0x0)
#define CCU_R_APBS0_CFG_REG         (R_PRCM_REG_BASE + 0xc)
#define CCU_R_APBS1_CFG_REG         (R_PRCM_REG_BASE + 0x10)

#define CCU_R_LPSD_CLK_REG          (R_PRCM_REG_BASE + 0x0D0)
#define CCU_R_MAD_BGR_REG           (R_PRCM_REG_BASE + 0x0DC)
#define CCU_R_DMA_BGR_REG           (R_PRCM_REG_BASE + 0x10c)
#define CCU_R_AUDIOCODEC_ADC_CLK_REG (R_PRCM_REG_BASE + 0x140)
#define CCU_R_AUDIOCODEC_DAC_CLK_REG (R_PRCM_REG_BASE + 0x144)
#define CCU_R_AUDIOCODEC_BGR_REG    (R_PRCM_REG_BASE + 0x14C)
#define CCU_R_DMIC_CLK_REG          (R_PRCM_REG_BASE + 0x150)
#define CCU_R_DMIC_BGR_REG          (R_PRCM_REG_BASE + 0x15C)
#define CCU_R_I2S0_CLK_REG          (R_PRCM_REG_BASE + 0x170)
#define CCU_R_I2S0_ASRC_CLK_REG     (R_PRCM_REG_BASE + 0x174)
#define CCU_R_I2S1_CLK_REG          (R_PRCM_REG_BASE + 0x178)
#define CCU_R_I2S_BGR_REG           (R_PRCM_REG_BASE + 0x17C)
#define CCU_R_MSGBOX_BGR_REG        (R_PRCM_REG_BASE + 0x1dc)
#define R_DSP_BUS_GATING_RESET      (R_PRCM_REG_BASE + 0x1bc)
#define VDD_SYS_PWROFF_GATING_REG   (R_PRCM_REG_BASE + 0x250)
#define ANALOG_PWROFF_GATING_REG    (R_PRCM_REG_BASE + 0x254)
#define DSP_POWER_CONTROL_REG       (R_PRCM_REG_BASE + 0x258)
#define VDD_SYS_PWR_RST_REG         (R_PRCM_REG_BASE + 0x260)
#define VDD_SYS_DOM_PWR_CTRL_REG    (R_PRCM_REG_BASE + 0x264)
#define RES_CAL_CTRL_REG            (R_PRCM_REG_BASE + 0x310)
#define BUS_AUTO_CLOCK_GATING_REG   (R_PRCM_REG_BASE + 0x33c)
#define MSRAMOC_CTRL_REG            (R_PRCM_REG_BASE + 0x360)

#define CCU_PLL_AUDIO0_REG          (R_PRCM_REG_BASE + 0x1020)
#define CCU_PLL_AUDIO1_REG          (R_PRCM_REG_BASE + 0x1030)
#define CCU_PLL_AUDIO0_PAT0_REG     (R_PRCM_REG_BASE + 0x1120)
#define CCU_PLL_AUDIO1_PAT0_REG     (R_PRCM_REG_BASE + 0x1130)

#define R_DSP1_DBG_RST_MASK         (1 << 21)
#define R_DSP1_DBG_RST(x)           (x << 21)
#define R_DSP1_CFG_RST_MASK         (1 << 20)
#define R_DSP1_CFG_RST(x)           (x << 20)
#define R_DSP1_RST_MASK             (1 << 19)
#define R_DSP1_RST(x)               (x << 19)
#define R_DSP1_CFG_GATING_MASK      (1 << 3)
#define R_DSP1_CFG_GATING(x)        (x << 3)
#define R_DSP1_GATING_MASK          (1 << 2)
#define R_DSP1_GATING(x)            (x << 2)

#define DSP1_POWER_ISOLATION_MASK   (1 << 16)
#define DSP1_POWER_ISOLATION(x)     (x << 16)
#define DSP1_POWER_SWT_CTL_MASK     (0xff << 8)
#define DSP1_POWER_SWT_CTL(x)       (x << 8)
#define DSP1_POWER_PWR_STA_MASK     (0xff << 0)

#define PLL_NUM     (14)
#define BUS_NUM     (10)
#define IO_NUM      (2)

/* for sun50iw11 pll define */
#define CCU_SYS_CLK_CPUX    CCU_SYS_CLK_PLL1
#define CCU_SYS_CLK_PERI_1X CCU_SYS_CLK_PLL2
#define CCU_SYS_CLK_PERI_2X CCU_SYS_CLK_PLL3
#define CCU_SYS_CLK_PERI_800M   CCU_SYS_CLK_PLL4
#define CCU_SYS_CLK_AUDIO0_DIV2 CCU_SYS_CLK_PLL5
#define CCU_SYS_CLK_AUDIO0_DIV5 CCU_SYS_CLK_PLL6
#define CCU_SYS_CLK_AUDIO1_4X   CCU_SYS_CLK_PLL7
#define CCU_SYS_CLK_AUDIO1_2X   CCU_SYS_CLK_PLL8
#define CCU_SYS_CLK_AUDIO1_1X   CCU_SYS_CLK_AUDIO1

#define CCU_AHB1_AHB2_SEL_MASK  (3 << 24)
#define CCU_AHB1_AHB2_M_MASK    (3 << 0)
#define CCU_AHB1_AHB2_N_MASK    (3 << 8)
#define CCU_AHB1_AHB2_SEL_RTC32 (1 << 24)
#define CCU_AHB1_AHB2_SEL_24M   (0 << 24)
#define CCU_APB1_SEL_MASK       (3 << 24)
#define CCU_APB1_SEL_RTC32      (1 << 24)
#define CCU_APB1_SEL_24M        (0 << 24)
#define CCU_APB1_FACTORN_MASK   (3 << 8)
#define CCU_APB1_FACTORM_MASK   (3 << 0)
#define CCU_APB2_M_MASK         (3 << 0)
#define CCU_APB2_N_MASK         (3 << 8)
#define CCU_APB2_SEL_MASK       (3 << 24)
#define CCU_APB2_SEL_RTC32      (1 << 24)
#define CCU_APB2_SEL_24M        (0 << 24)
#define CCU_AXI_SEL_MASK        (7 << 24)
#define CCU_AXI_SEL_24M         (0 << 24)
#define CCU_AXI_SEL_RTC32       (1 << 24)
#define CCU_AXI_FACTOR_M_MASK   (3 << 0)
#define CCU_AXI_APB_N_MASK      (3 << 8)
#define CCU_AXI_SRC_SEL_MASK    (7 << 24)

#define CPUX_PLL_ENABLE_MASK    (1 << 31)
#define CPUX_PLL_ENABLE         (1 << 31)
#define CPUX_PLL_DISABLE        (0 << 31)
#define CPUX_PLL_LOCK_MASK      (1 << 29)
#define CPUX_PLL_LOCK_ENABLE    (1 << 29)
#define CPUX_PLL_LOCK_DISABLE   (1 << 29)
#define CPUX_PLL_LOCK_STATUS    (1 << 28)

#define VDD_SYS_GATING_MASK (3 << 0)
#define VDD_SYS_GATING      (3 << 0)
#define VDD_SYS_NOT_GATING  (0 << 0)

#define ANALOG_PWROFF_GATING_MASK (1 << 0)
#define ANALOG_PWROFF_GATING      (1 << 0)
#define ANALOG_PWROFF_NOT_GATING  (0 << 0)

#define VDD_SYS_PWR_RST_MASK      (1 << 0)
#define VDD_SYS_PWR_RST_ASSERT    (0 << 0)
#define VDD_SYS_PWR_RST_DEASSERT  (1 << 0)

#define MSRAMOC_PORT_HOLD_EN      (1 << 1)
#define MSRAMOC_ACG_EN            (1 << 0)
#define AHBS_AUTO_CLK_GATE_EN     (1 << 24)
#define BM_ACG_MODE_EN            (1 << 0)


#define CCU_R_APBSx_SEL_MASK    (0x7<<24)
#define CCU_R_APBSx_SEL_DCXO24M          (0x0<<24)
#define CCU_R_APBSx_SEL_RTC32K           (0x1<<24)
#define CCU_R_APBSx_SEL_RC16M            (0x2<<24)
#define CCU_R_APBSx_SEL_PLL_PERI2X       (0x3<<24)
#define CCU_R_APBSx_SEL_PLL_AUDIO0DIV2   (0x4<<24)

typedef struct ccu_pll1_factor {
    u8 factor_n;
    u8 factor_k;
    u8 factor_m;
    u8 factor_p;
    u32 freq;
} ccu_pll1_factor_t;

/* local functions */
s32 ccu_set_cpus_src(u32 sclk);

/* ccu module registers address */
extern struct ccu_reg_list *ccu_reg_addr;
extern struct ccu_pll_c0_cpux_reg0000 *ccu_pll_c0_cpux_reg_addr;
extern struct ccu_pll_ddr0_reg0010 *ccu_pll_ddr0_reg_addr;
extern struct ccu_pll_periph_reg0010 *ccu_pll_periph0_reg_addr;
extern struct ccu_pll_audio0_reg0020 *ccu_pll_audio0_reg_addr;
extern struct ccu_pll_periph1_reg0028 *ccu_pll_periph1_reg_addr;

/* apb notifier list */
extern struct notifier *apbs2_notifier_head;

#endif /* __CCU_I_H__ */
