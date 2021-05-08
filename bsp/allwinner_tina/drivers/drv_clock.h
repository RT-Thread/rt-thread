/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */
#ifndef __DRV_CLOCK_H__
#define __DRV_CLOCK_H__

/* PLL state */
#define PLL_ENBALE              (0x1)
#define PLL_STABLE              (0x2)

/* Clock source selection */
#define CLK_LOSC_SRC            (0x00)
#define CLK_OSC24M_SRC          (0x01)
#define CLK_PLL_SRC             (0x02)
#define PRE_DIV_SRC             (0x03)


/*  */
#define TCON_PLL_VIDEO_X1       (0x000)
#define TCON_PLL_VIDEO_X2       (0x002)


#define PLL_CPU_ENABLE_STATE            (0x1<<31)
#define PLL_CPU_HAS_BEEN_STABLE         (0x1<<28)
#define PLL_CPU_DIV_P(reg)              ((reg>>16)&0x3)
#define PLL_CPU_FACTOR_N(reg)           ((reg>>8)&0x1f)
#define PLL_CPU_FACTOR_K(reg)           ((reg>>4)&0x3)
#define PLL_CPU_FACTOR_M(reg)           ((reg)&0x3)

#define PLL_AUDIO_ENABLE_STATE          (0x1<<31)
#define PLL_AUDIO_HAS_BEEN_STABLE       (0x1<<28)
#define PLL_AUDIO_FACTOR_N(reg)         ((reg>>8)&0x7f)
#define PLL_AUDIO_PREDIV_M(reg)         ((reg)&0x1f)

#define PLL_VIDEO_ENABLE_STATE          (0x1<<31)
#define PLL_VIDEO_MODE                  (0x1<<30)
#define PLL_VIDEO_HAS_BEEN_STABLE       (0x1<<28)
#define PLL_VIDEO_FRAC_CLK_OUT          (0x1<<25)
#define PLL_VIDEO_MODE_SEL              (0x1<<24)
#define PLL_VIDEO_SDM_EN                (0x1<<20)
#define PLL_VIDEO_FACTOR_N(reg)         ((reg>>8)&0x7f)
#define PLL_VIDEO_PREDIV_M(reg)         (reg&0xf)

#define PLL_VE_ENABLE_STATE             (0x1<<31)
#define PLL_VE_HAS_BEEN_STABLE          (0x1<<28)
#define PLL_VE_FRAC_CLK_OUT             (0x1<<25)
#define PLL_VE_MODE_SEL                 (0x1<<24)
#define PLL_VE_FACTOR_N(reg)            ((reg>>8)&0x7f)
#define PLL_VE_PREDIV_M(reg)            (reg&0xf)

#define PLL_DDR_ENABLE_STATE            (0x1<<31)
#define PLL_DDR_HAS_BEEN_STABLE         (0x1<<28)
#define SDRAM_SIGMA_DELTA_EN            (0x1<<24)
#define PLL_DDR_CFG_UPDATE              (0x1<<20)
#define PLL_DDR_FACTOR_N(reg)           ((reg>>8)&0x1f)
#define PLL_DDR_FACTOR_K(reg)           ((reg>>4)&0x3)
#define PLL_DDR_FACTOR_M(reg)           ((reg)&0x3)

#define PLL_PERIPH_ENABLE_STATE         (0x1<<31)
#define PLL_PERIPH_HAS_BEEN_STABLE      (0x1<<28)
#define PLL_PERIPH_24M_OUT_EN           (0x1<<18)
#define PLL_PERIPH_24M_POST_DIV(reg)    ((reg>>16)&0x3)
#define PLL_PERIPH_FACTOR_N(reg)        ((reg>>8)&0x1f)
#define PLL_PERIPH_FACTOR_K(reg)        ((reg>>4)&0x3)
#define PLL_PERIPH_FACTOR_M(reg)        (reg&0x3)

#define HCLKC_DIV(reg)                  ((reg>>16)&0x3)
#define AHB_SRC_SEL(reg)                ((reg>>12)&0x3)
#define AHB_CLK_DIV(reg)                ((reg>>4)&0x3)
#define AHB_PRE_DIV(reg)                ((reg>>6)&0x3)
#define APH_CLK_PATIO(reg)              ((reg>>8)&0x3)


#define CCM_MMC_CTRL_OSCM24             (0x00)
#define CCM_MMC_CTRL_PLL_PERIPH         (0x01)

#define CCU_BASE_ADDR      (0x01C20000)

#define _24MHZ_     (24000000U)
#define _32KHZ_     (32000U)

/* GATE */

#define BUS_GATE_OFFSET_BIT    (12)

enum bus_gate
{
    USB_OTG_GATING     = (0x18 | (0x0 << BUS_GATE_OFFSET_BIT)),
    SPI1_GATING        = (0x15 | (0x0 << BUS_GATE_OFFSET_BIT)),
    SPI0_GATING        = (0x14 | (0x0 << BUS_GATE_OFFSET_BIT)),
    SDRAM_GATING       = (0x0E | (0x0 << BUS_GATE_OFFSET_BIT)),
    SD1_GATING         = (0x09 | (0x0 << BUS_GATE_OFFSET_BIT)),
    SD0_GATING         = (0x08 | (0x0 << BUS_GATE_OFFSET_BIT)),
    DMA_GATING         = (0x06 | (0x0 << BUS_GATE_OFFSET_BIT)),

    DEFE_GATING        = (0x0E | (0x1 << BUS_GATE_OFFSET_BIT)),
    DEBE_GATING        = (0x0C | (0x1 << BUS_GATE_OFFSET_BIT)),
    TVE_GATING         = (0x0A | (0x1 << BUS_GATE_OFFSET_BIT)),
    TVD_GATING         = (0x09 | (0x1 << BUS_GATE_OFFSET_BIT)),
    CSI_GATING         = (0x08 | (0x1 << BUS_GATE_OFFSET_BIT)),
    DEINTERLACE_GATING = (0x05 | (0x1 << BUS_GATE_OFFSET_BIT)),
    LCD_GATING         = (0x04 | (0x1 << BUS_GATE_OFFSET_BIT)),
    VE_GATING          = (0x00 | (0x1 << BUS_GATE_OFFSET_BIT)),

    UART2_GATING       = (0x16 | (0x2 << BUS_GATE_OFFSET_BIT)),
    UART1_GATING       = (0x15 | (0x2 << BUS_GATE_OFFSET_BIT)),
    UART0_GATING       = (0x14 | (0x2 << BUS_GATE_OFFSET_BIT)),
    TWI2_GATING        = (0x12 | (0x2 << BUS_GATE_OFFSET_BIT)),
    TWI1_GATING        = (0x11 | (0x2 << BUS_GATE_OFFSET_BIT)),
    TWI0_GATING        = (0x10 | (0x2 << BUS_GATE_OFFSET_BIT)),
    DAUDIO_GATING      = (0x0C | (0x2 << BUS_GATE_OFFSET_BIT)),
    RSB_GATING         = (0x03 | (0x2 << BUS_GATE_OFFSET_BIT)),
    CIR_GATING         = (0x02 | (0x2 << BUS_GATE_OFFSET_BIT)),
    OWA_GATING         = (0x01 | (0x2 << BUS_GATE_OFFSET_BIT)),
    AUDIO_CODEC_GATING = (0x00 | (0x2 << BUS_GATE_OFFSET_BIT)),
};

enum dram_gate
{
    BE_GATING_DRAM          = 26,
    FE_GATING_DRAM          = 24,
    TVD_GATING_DRAM         = 3,
    DEINTERLACE_GATING_DRAM = 2,
    CSI_GATING_DRAM         = 1,
    VE_GATING_DRAM          = 0
};
enum mmc_clk_id
{
    SDMMC0,
    SDMMC1,
};

struct tina_ccu
{
    volatile rt_uint32_t pll_cpu_ctrl;         /* 0x000 */
    volatile rt_uint32_t reserved0;
    volatile rt_uint32_t pll_audio_ctrl;       /* 0x008 */
    volatile rt_uint32_t reserved1;
    volatile rt_uint32_t pll_video_ctrl;       /* 0x010 */
    volatile rt_uint32_t reserved2;
    volatile rt_uint32_t pll_ve_ctrl;          /* 0x018 */
    volatile rt_uint32_t reserved3;
    volatile rt_uint32_t pll_ddr_ctrl;         /* 0x020 */
    volatile rt_uint32_t reserved4;
    volatile rt_uint32_t pll_periph_ctrl;      /* 0x028 */
    volatile rt_uint32_t reserved5[9];
    volatile rt_uint32_t cpu_clk_src;          /* 0x050 */
    volatile rt_uint32_t ahb_apb_hclkc_cfg;    /* 0x054 */
    volatile rt_uint32_t reserved6[2];
    volatile rt_uint32_t bus_clk_gating0;      /* 0x060 */
    volatile rt_uint32_t bus_clk_gating1;      /* 0x064 */
    volatile rt_uint32_t bus_clk_gating2;      /* 0x068 */
    volatile rt_uint32_t reserved7[7];
    volatile rt_uint32_t sdmmc0_clk;           /* 0x088 */
    volatile rt_uint32_t sdmmc1_clk;           /* 0x08C */
    volatile rt_uint32_t reserved8[8];
    volatile rt_uint32_t daudio_clk;           /* 0x0B0 */
    volatile rt_uint32_t owa_clk;              /* 0x0B4 */
    volatile rt_uint32_t cir_clk;              /* 0x0B8 */
    volatile rt_uint32_t reserved9[4];
    volatile rt_uint32_t usbphy_clk;           /* 0x0CC */
    volatile rt_uint32_t reserved10[12];
    volatile rt_uint32_t dram_gating;          /* 0x100 */
    volatile rt_uint32_t be_clk;               /* 0x104 */
    volatile rt_uint32_t reserved11;
    volatile rt_uint32_t fe_clk;               /* 0x10C */
    volatile rt_uint32_t reserved12[2];
    volatile rt_uint32_t tcon_clk;             /* 0x118*/
    volatile rt_uint32_t di_clk;               /* 0x11C */
    volatile rt_uint32_t tve_clk;              /* 0x120 */
    volatile rt_uint32_t tvd_clk;              /* 0x124 */
    volatile rt_uint32_t reserved13[3];
    volatile rt_uint32_t csi_clk;              /* 0x134 */
    volatile rt_uint32_t reserved14;
    volatile rt_uint32_t ve_clk;               /* 0x13C */
    volatile rt_uint32_t audio_codec_clk;      /* 0x140 */
    volatile rt_uint32_t avs_clk;              /* 0x144 */
    volatile rt_uint32_t reserved15[46];
    volatile rt_uint32_t pll_stable_time0;     /* 0x200 */
    volatile rt_uint32_t pll_stable_time1;     /* 0x204 */
    volatile rt_uint32_t reserved16[6];
    volatile rt_uint32_t pll_cpu_bias;         /* 0x220 */
    volatile rt_uint32_t pll_audio_bias;       /* 0x224 */
    volatile rt_uint32_t pll_video_bias;       /* 0x228 */
    volatile rt_uint32_t pll_ve_bias;          /* 0x22C */
    volatile rt_uint32_t pll_ddr_bias;         /* 0x230 */
    volatile rt_uint32_t pll_periph_bias;      /* 0x234 */
    volatile rt_uint32_t reserved17[6];
    volatile rt_uint32_t pll_cpu_tun;          /* 0x250 */
    volatile rt_uint32_t reserved18[3];
    volatile rt_uint32_t pll_ddr_tun;          /* 0x260 */
    volatile rt_uint32_t reserved19[8];
    volatile rt_uint32_t pll_audio_pat_ctrl;   /* 0x284 */
    volatile rt_uint32_t pll_video_pat_ctrl;   /* 0x288 */
    volatile rt_uint32_t reserved20;
    volatile rt_uint32_t pll_ddr_pat_ctrl;     /* 0x290 */
    volatile rt_uint32_t reserved21[11];
    volatile rt_uint32_t bus_soft_rst0;        /* 0x2C0 */
    volatile rt_uint32_t bus_soft_rst1;        /* 0x2C4 */
    volatile rt_uint32_t reserved22[2];
    volatile rt_uint32_t bus_soft_rst2;        /* 0x2D0 */
};

typedef struct tina_ccu *tina_ccu_t;

#define CCU ((tina_ccu_t) CCU_BASE_ADDR)

int cpu_get_pll_clk(void);
int audio_get_pll_clk(void);
int video_get_pll_clk(void);
int ve_get_pll_clk(void);
int ddr_get_pll_clk(void);
int periph_get_pll_clk(void);
int cpu_get_clk(void);
int ahb_get_clk(void);
int apb_get_clk(void);

rt_err_t cpu_set_pll_clk(int clk);
rt_err_t audio_set_pll_clk(int clk);
rt_err_t video_set_pll_clk(int clk);
rt_err_t ve_set_pll_clk(int clk);
rt_err_t periph_set_pll_clk(int clk);

rt_err_t cpu_set_clk(int clk);

rt_err_t bus_gate_clk_enalbe(enum bus_gate bus);
rt_err_t bus_gate_clk_disalbe(enum bus_gate bus);
rt_err_t bus_software_reset_enalbe(enum bus_gate bus);
rt_err_t bus_software_reset_disalbe(enum bus_gate bus);

rt_err_t dram_gate_clk_enable(enum dram_gate dram_gate);
rt_err_t dram_gate_clk_disable(enum dram_gate dram_gate);

rt_err_t mmc_set_clk(enum mmc_clk_id clk_id, int hz);
#endif
