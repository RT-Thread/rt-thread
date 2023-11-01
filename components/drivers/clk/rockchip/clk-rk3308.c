/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk.h"

#define DBG_TAG "clk.rk3308"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <dt-bindings/clock/rk3308-cru.h>

#define APLL_HZ         (816 * MHZ)

#define CORE_ACLK_HZ    408000000
#define CORE_DBG_HZ     204000000

#define BUS_ACLK_HZ     200000000
#define BUS_HCLK_HZ     100000000
#define BUS_PCLK_HZ     100000000

#define PERI_ACLK_HZ    200000000
#define PERI_HCLK_HZ    100000000
#define PERI_PCLK_HZ    100000000

#define AUDIO_HCLK_HZ   100000000
#define AUDIO_PCLK_HZ   100000000

struct rk_pll
{
    rt_uint32_t con0;
    rt_uint32_t con1;
    rt_uint32_t con2;
    rt_uint32_t con3;
    rt_uint32_t con4;
    rt_uint32_t reserved0[3];
};

struct rk_cru
{
    struct rk_pll pll[4];
    rt_uint32_t reserved1[8];
    rt_uint32_t mode;
    rt_uint32_t misc;
    rt_uint32_t reserved2[2];
    rt_uint32_t glb_cnt_th;
    rt_uint32_t glb_rst_st;
    rt_uint32_t glb_srst_fst;
    rt_uint32_t glb_srst_snd;
    rt_uint32_t glb_rst_con;
    rt_uint32_t pll_lock;
    rt_uint32_t reserved3[6];
    rt_uint32_t hwffc_con0;
    rt_uint32_t reserved4;
    rt_uint32_t hwffc_th;
    rt_uint32_t hwffc_intst;
    rt_uint32_t apll_con0_s;
    rt_uint32_t apll_con1_s;
    rt_uint32_t clksel_con0_s;
    rt_uint32_t reserved5;
    rt_uint32_t clksel_con[74];
    rt_uint32_t reserved6[54];
    rt_uint32_t clkgate_con[15];
    rt_uint32_t reserved7[(0x380 - 0x338) / 4 - 1];
    rt_uint32_t ssgtbl[32];
    rt_uint32_t softrst_con[10];
    rt_uint32_t reserved8[(0x480 - 0x424) / 4 - 1];
    rt_uint32_t sdmmc_con[2];
    rt_uint32_t sdio_con[2];
    rt_uint32_t emmc_con[2];
};

/* Private data for the clock driver - used by rk_get_cru() */
struct rk_clk_priv
{
    struct rk_cru *cru;
    rt_ubase_t armclk_hz;
    rt_ubase_t dpll_hz;
    rt_ubase_t vpll0_hz;
    rt_ubase_t vpll1_hz;
};

struct rk_clk_platform_data
{
    rt_uint32_t id;
    void *base;
};

struct rk_clk
{
    struct rt_reset_controller_clk_node parent;

    void *base;
    struct rk_clk_priv clk_info;
    struct rk_clk_platform_data pdata[CLK_NR_CLKS];
};

#define raw_to_rk_clk(raw) rt_container_of(raw, struct rk_clk, parent)

#define PLL_CON(x)  ((x) * 0x4)
#define MODE_CON    0xa0

enum plls
{
    apll, dpll, vpll0, vpll1,
};

enum
{
    /* PLLCON0*/
    PLL_BP_SHIFT                    = 15,
    PLL_POSTDIV1_SHIFT              = 12,
    PLL_POSTDIV1_MASK               = 7 << PLL_POSTDIV1_SHIFT,
    PLL_FBDIV_SHIFT                 = 0,
    PLL_FBDIV_MASK                  = 0xfff,

    /* PLLCON1 */
    PLL_PDSEL_SHIFT                 = 15,
    PLL_PD1_SHIFT                   = 14,
    PLL_PD_SHIFT                    = 13,
    PLL_PD_MASK                     = 1 << PLL_PD_SHIFT,
    PLL_DSMPD_SHIFT                 = 12,
    PLL_DSMPD_MASK                  = 1 << PLL_DSMPD_SHIFT,
    PLL_LOCK_STATUS_SHIFT           = 10,
    PLL_LOCK_STATUS_MASK            = 1 << PLL_LOCK_STATUS_SHIFT,
    PLL_POSTDIV2_SHIFT              = 6,
    PLL_POSTDIV2_MASK               = 7 << PLL_POSTDIV2_SHIFT,
    PLL_REFDIV_SHIFT                = 0,
    PLL_REFDIV_MASK                 = 0x3f,

    /* PLLCON2 */
    PLL_FOUT4PHASEPD_SHIFT          = 27,
    PLL_FOUTVCOPD_SHIFT             = 26,
    PLL_FOUTPOSTDIVPD_SHIFT         = 25,
    PLL_DACPD_SHIFT                 = 24,
    PLL_FRAC_DIV                    = 0xffffff,

    /* CRU_MODE */
    PLLMUX_FROM_XIN24M              = 0,
    PLLMUX_FROM_PLL,
    PLLMUX_FROM_RTC32K,
    USBPHY480M_MODE_SHIFT           = 8,
    USBPHY480M_MODE_MASK            = 3 << USBPHY480M_MODE_SHIFT,
    VPLL1_MODE_SHIFT                        = 6,
    VPLL1_MODE_MASK                 = 3 << VPLL1_MODE_SHIFT,
    VPLL0_MODE_SHIFT                        = 4,
    VPLL0_MODE_MASK                 = 3 << VPLL0_MODE_SHIFT,
    DPLL_MODE_SHIFT                 = 2,
    DPLL_MODE_MASK                  = 3 << DPLL_MODE_SHIFT,
    APLL_MODE_SHIFT                 = 0,
    APLL_MODE_MASK                  = 3 << APLL_MODE_SHIFT,

    /* CRU_CLK_SEL0_CON */
    CORE_ACLK_DIV_SHIFT             = 12,
    CORE_ACLK_DIV_MASK              = 0x7 << CORE_ACLK_DIV_SHIFT,
    CORE_DBG_DIV_SHIFT              = 8,
    CORE_DBG_DIV_MASK               = 0xf << CORE_DBG_DIV_SHIFT,
    CORE_CLK_PLL_SEL_SHIFT          = 6,
    CORE_CLK_PLL_SEL_MASK           = 0x3 << CORE_CLK_PLL_SEL_SHIFT,
    CORE_CLK_PLL_SEL_APLL           = 0,
    CORE_CLK_PLL_SEL_VPLL0,
    CORE_CLK_PLL_SEL_VPLL1,
    CORE_DIV_CON_SHIFT              = 0,
    CORE_DIV_CON_MASK               = 0x0f << CORE_DIV_CON_SHIFT,

    /* CRU_CLK_SEL5_CON */
    BUS_PLL_SEL_SHIFT               = 6,
    BUS_PLL_SEL_MASK                = 0x3 << BUS_PLL_SEL_SHIFT,
    BUS_PLL_SEL_DPLL                = 0,
    BUS_PLL_SEL_VPLL0,
    BUS_PLL_SEL_VPLL1,
    BUS_ACLK_DIV_SHIFT              = 0,
    BUS_ACLK_DIV_MASK               = 0x1f << BUS_ACLK_DIV_SHIFT,

    /* CRU_CLK_SEL6_CON */
    BUS_PCLK_DIV_SHIFT              = 8,
    BUS_PCLK_DIV_MASK               = 0x1f << BUS_PCLK_DIV_SHIFT,
    BUS_HCLK_DIV_SHIFT              = 0,
    BUS_HCLK_DIV_MASK               = 0x1f << BUS_HCLK_DIV_SHIFT,

    /* CRU_CLK_SEL7_CON */
    CRYPTO_APK_SEL_SHIFT            = 14,
    CRYPTO_APK_PLL_SEL_MASK         = 3 << CRYPTO_APK_SEL_SHIFT,
    CRYPTO_PLL_SEL_DPLL             = 0,
    CRYPTO_PLL_SEL_VPLL0,
    CRYPTO_PLL_SEL_VPLL1            = 0,
    CRYPTO_APK_DIV_SHIFT            = 8,
    CRYPTO_APK_DIV_MASK             = 0x1f << CRYPTO_APK_DIV_SHIFT,
    CRYPTO_PLL_SEL_SHIFT            = 6,
    CRYPTO_PLL_SEL_MASK             = 3 << CRYPTO_PLL_SEL_SHIFT,
    CRYPTO_DIV_SHIFT                = 0,
    CRYPTO_DIV_MASK                 = 0x1f << CRYPTO_DIV_SHIFT,

    /* CRU_CLK_SEL8_CON */
    DCLK_VOP_SEL_SHIFT              = 14,
    DCLK_VOP_SEL_MASK               = 0x3 << DCLK_VOP_SEL_SHIFT,
    DCLK_VOP_SEL_DIVOUT             = 0,
    DCLK_VOP_SEL_FRACOUT,
    DCLK_VOP_SEL_24M,
    DCLK_VOP_PLL_SEL_SHIFT          = 10,
    DCLK_VOP_PLL_SEL_MASK           = 0x3 << DCLK_VOP_PLL_SEL_SHIFT,
    DCLK_VOP_PLL_SEL_DPLL           = 0,
    DCLK_VOP_PLL_SEL_VPLL0,
    DCLK_VOP_PLL_SEL_VPLL1,
    DCLK_VOP_DIV_SHIFT              = 0,
    DCLK_VOP_DIV_MASK               = 0xff,

    /* CRU_CLK_SEL10_CON */
    CLK_UART_SRC_SEL_SHIFT          = 13,
    CLK_UART_SRC_SEL_MASK           = 0x7 << CLK_UART_SRC_SEL_SHIFT,
    CLK_UART_SRC_SEL_DPLL           = 0,
    CLK_UART_SRC_SEL_VPLL0,
    CLK_UART_SRC_SEL_VPLL1,
    CLK_UART_SRC_SEL_480M,
    CLK_UART_SRC_SEL_XIN_OSC0,
    CLK_UART_SRC_DIV_SHIFT          = 0,
    CLK_UART_SRC_DIV_MASK           = 0x3f << CLK_UART_SRC_DIV_SHIFT,

    /* CRU_CLK_SEL11_CON */
    CLK_UART_SEL_SHIFT              = 14,
    CLK_UART_SEL_MASK               = 0x3 << CLK_UART_SEL_SHIFT,
    CLK_UART_SEL_SRC                = 0,
    CLK_UART_SEL_NP5,
    CLK_UART_SEL_FRAC_OUT,
    CLK_UART_NP5_DIV_SHIFT          = 0,
    CLK_UART_NP5_DIV_MASK           = 0x3f << CLK_UART_NP5_DIV_SHIFT,

    /* CRU_CLKSEL12_CON */
    CLK_UART_FRAC_NUMERATOR_SHIFT   = 16,
    CLK_UART_FRAC_NUMERATOR_MASK    = 0xffff << 16,
    CLK_UART_FRAC_DENOMINATOR_SHIFT = 0,
    CLK_UART_FRAC_DENOMINATOR_MASK  = 0xffff,

    /* CRU_CLK_SEL25_CON */
    /* CRU_CLK_SEL26_CON */
    /* CRU_CLK_SEL27_CON */
    /* CRU_CLK_SEL28_CON */
    CLK_I2C_PLL_SEL_SHIFT           = 14,
    CLK_I2C_PLL_SEL_MASK            = 0x3 << CLK_I2C_PLL_SEL_SHIFT,
    CLK_I2C_PLL_SEL_DPLL            = 0,
    CLK_I2C_PLL_SEL_VPLL0,
    CLK_I2C_PLL_SEL_24M,
    CLK_I2C_DIV_CON_SHIFT           = 0,
    CLK_I2C_DIV_CON_MASK            = 0x7f << CLK_I2C_DIV_CON_SHIFT,

    /* CRU_CLK_SEL29_CON */
    CLK_PWM_PLL_SEL_SHIFT           = 14,
    CLK_PWM_PLL_SEL_MASK            = 0x3 << CLK_PWM_PLL_SEL_SHIFT,
    CLK_PWM_PLL_SEL_DPLL            = 0,
    CLK_PWM_PLL_SEL_VPLL0,
    CLK_PWM_PLL_SEL_24M,
    CLK_PWM_DIV_CON_SHIFT           = 0,
    CLK_PWM_DIV_CON_MASK            = 0x7f << CLK_PWM_DIV_CON_SHIFT,

    /* CRU_CLK_SEL30_CON */
    /* CRU_CLK_SEL31_CON */
    /* CRU_CLK_SEL32_CON */
    CLK_SPI_PLL_SEL_SHIFT           = 14,
    CLK_SPI_PLL_SEL_MASK            = 0x3 << CLK_SPI_PLL_SEL_SHIFT,
    CLK_SPI_PLL_SEL_DPLL            = 0,
    CLK_SPI_PLL_SEL_VPLL0,
    CLK_SPI_PLL_SEL_24M,
    CLK_SPI_DIV_CON_SHIFT           = 0,
    CLK_SPI_DIV_CON_MASK            = 0x7f << CLK_SPI_DIV_CON_SHIFT,

    /* CRU_CLK_SEL34_CON */
    CLK_SARADC_DIV_CON_SHIFT        = 0,
    CLK_SARADC_DIV_CON_MASK         = 0x7ff << CLK_SARADC_DIV_CON_SHIFT,

    /* CRU_CLK_SEL36_CON */
    PERI_PLL_SEL_SHIFT              = 6,
    PERI_PLL_SEL_MASK               = 0x3 << PERI_PLL_SEL_SHIFT,
    PERI_PLL_DPLL                   = 0,
    PERI_PLL_VPLL0,
    PERI_PLL_VPLL1,
    PERI_ACLK_DIV_SHIFT             = 0,
    PERI_ACLK_DIV_MASK              = 0x1f << PERI_ACLK_DIV_SHIFT,

    /* CRU_CLK_SEL37_CON */
    PERI_PCLK_DIV_SHIFT             = 8,
    PERI_PCLK_DIV_MASK              = 0x1f << PERI_PCLK_DIV_SHIFT,
    PERI_HCLK_DIV_SHIFT             = 0,
    PERI_HCLK_DIV_MASK              = 0x1f << PERI_HCLK_DIV_SHIFT,

    /* CRU_CLKSEL41_CON */
    EMMC_CLK_SEL_SHIFT              = 15,
    EMMC_CLK_SEL_MASK               = 1 << EMMC_CLK_SEL_SHIFT,
    EMMC_CLK_SEL_EMMC               = 0,
    EMMC_CLK_SEL_EMMC_DIV50,
    EMMC_PLL_SHIFT                  = 8,
    EMMC_PLL_MASK                   = 0x3 << EMMC_PLL_SHIFT,
    EMMC_SEL_DPLL                   = 0,
    EMMC_SEL_VPLL0,
    EMMC_SEL_VPLL1,
    EMMC_SEL_24M,
    EMMC_DIV_SHIFT                  = 0,
    EMMC_DIV_MASK                   = 0xff << EMMC_DIV_SHIFT,

    /* CRU_CLKSEL43_CON */
    MAC_CLK_SPEED_SEL_SHIFT         = 15,
    MAC_CLK_SPEED_SEL_MASK          = 1 << MAC_CLK_SPEED_SEL_SHIFT,
    MAC_CLK_SPEED_SEL_10M           = 0,
    MAC_CLK_SPEED_SEL_100M,
    MAC_CLK_SOURCE_SEL_SHIFT        = 14,
    MAC_CLK_SOURCE_SEL_MASK         = 1 << MAC_CLK_SOURCE_SEL_SHIFT,
    MAC_CLK_SOURCE_SEL_INTERNAL     = 0,
    MAC_CLK_SOURCE_SEL_EXTERNAL,
    MAC_PLL_SHIFT                   = 6,
    MAC_PLL_MASK                    = 0x3 << MAC_PLL_SHIFT,
    MAC_SEL_DPLL                    = 0,
    MAC_SEL_VPLL0,
    MAC_SEL_VPLL1,
    MAC_DIV_SHIFT                   = 0,
    MAC_DIV_MASK                    = 0x1f << MAC_DIV_SHIFT,

    /* CRU_CLK_SEL45_CON */
    AUDIO_PCLK_DIV_SHIFT            = 8,
    AUDIO_PCLK_DIV_MASK             = 0x1f << AUDIO_PCLK_DIV_SHIFT,
    AUDIO_PLL_SEL_SHIFT             = 6,
    AUDIO_PLL_SEL_MASK              = 0x3 << AUDIO_PLL_SEL_SHIFT,
    AUDIO_PLL_VPLL0                 = 0,
    AUDIO_PLL_VPLL1,
    AUDIO_PLL_24M,
    AUDIO_HCLK_DIV_SHIFT            = 0,
    AUDIO_HCLK_DIV_MASK             = 0x1f << AUDIO_HCLK_DIV_SHIFT,
};

enum
{
    VCO_MAX_HZ = 3200U * 1000000,
    VCO_MIN_HZ = 800 * 1000000,
    OUTPUT_MAX_HZ = 3200U * 1000000,
    OUTPUT_MIN_HZ = 24 * 1000000,
};

static struct rk_pll_rate_table pll_rates[] =
{
    /* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
    PLL_RATE(1608000000, 1,   67, 1, 1, 1, 0),
    PLL_RATE(1584000000, 1,   66, 1, 1, 1, 0),
    PLL_RATE(1560000000, 1,   65, 1, 1, 1, 0),
    PLL_RATE(1536000000, 1,   64, 1, 1, 1, 0),
    PLL_RATE(1512000000, 1,   63, 1, 1, 1, 0),
    PLL_RATE(1488000000, 1,   62, 1, 1, 1, 0),
    PLL_RATE(1464000000, 1,   61, 1, 1, 1, 0),
    PLL_RATE(1440000000, 1,   60, 1, 1, 1, 0),
    PLL_RATE(1416000000, 1,   59, 1, 1, 1, 0),
    PLL_RATE(1392000000, 1,   58, 1, 1, 1, 0),
    PLL_RATE(1368000000, 1,   57, 1, 1, 1, 0),
    PLL_RATE(1344000000, 1,   56, 1, 1, 1, 0),
    PLL_RATE(1320000000, 1,   55, 1, 1, 1, 0),
    PLL_RATE(1296000000, 1,   54, 1, 1, 1, 0),
    PLL_RATE(1272000000, 1,   53, 1, 1, 1, 0),
    PLL_RATE(1248000000, 1,   52, 1, 1, 1, 0),
    PLL_RATE(1200000000, 1,   50, 1, 1, 1, 0),
    PLL_RATE(1188000000, 2,   99, 1, 1, 1, 0),
    PLL_RATE(1104000000, 1,   46, 1, 1, 1, 0),
    PLL_RATE(1100000000, 12, 550, 1, 1, 1, 0),
    PLL_RATE(1008000000, 1,   84, 2, 1, 1, 0),
    PLL_RATE(1000000000, 6,  500, 2, 1, 1, 0),
    PLL_RATE(984000000,  1,   82, 2, 1, 1, 0),
    PLL_RATE(960000000,  1,   80, 2, 1, 1, 0),
    PLL_RATE(936000000,  1,   78, 2, 1, 1, 0),
    PLL_RATE(912000000,  1,   76, 2, 1, 1, 0),
    PLL_RATE(900000000,  4,  300, 2, 1, 1, 0),
    PLL_RATE(888000000,  1,   74, 2, 1, 1, 0),
    PLL_RATE(864000000,  1,   72, 2, 1, 1, 0),
    PLL_RATE(840000000,  1,   70, 2, 1, 1, 0),
    PLL_RATE(816000000,  1,   68, 2, 1, 1, 0),
    PLL_RATE(800000000,  6,  400, 2, 1, 1, 0),
    PLL_RATE(700000000,  6,  350, 2, 1, 1, 0),
    PLL_RATE(696000000,  1,   58, 2, 1, 1, 0),
    PLL_RATE(624000000,  1,   52, 2, 1, 1, 0),
    PLL_RATE(600000000,  1,   75, 3, 1, 1, 0),
    PLL_RATE(594000000,  2,   99, 2, 1, 1, 0),
    PLL_RATE(504000000,  1,   63, 3, 1, 1, 0),
    PLL_RATE(500000000,  6,  250, 2, 1, 1, 0),
    PLL_RATE(408000000,  1,   68, 2, 2, 1, 0),
    PLL_RATE(312000000,  1,   52, 2, 2, 1, 0),
    PLL_RATE(216000000,  1,   72, 4, 2, 1, 0),
    PLL_RATE(96000000,   1,   64, 4, 4, 1, 0),
};

static struct rk_cpu_rate_table cpu_rates[] =
{
    CPUCLK_RATE(1608000000, 1, 7),
    CPUCLK_RATE(1512000000, 1, 7),
    CPUCLK_RATE(1488000000, 1, 5),
    CPUCLK_RATE(1416000000, 1, 5),
    CPUCLK_RATE(1392000000, 1, 5),
    CPUCLK_RATE(1296000000, 1, 5),
    CPUCLK_RATE(1200000000, 1, 5),
    CPUCLK_RATE(1104000000, 1, 5),
    CPUCLK_RATE(1008000000, 1, 5),
    CPUCLK_RATE(912000000,  1, 5),
    CPUCLK_RATE(816000000,  1, 3),
    CPUCLK_RATE(696000000,  1, 3),
    CPUCLK_RATE(600000000,  1, 3),
    CPUCLK_RATE(408000000,  1, 1),
    CPUCLK_RATE(312000000,  1, 1),
    CPUCLK_RATE(216000000,  1, 1),
    CPUCLK_RATE(96000000,   1, 1),
};

static struct rk_pll_clock pll_clks[] =
{
    [apll]  = PLL(PLL_APLL,  PLL_CON(0),  MODE_CON, 0, 10, 0, pll_rates),
    [dpll]  = PLL(PLL_DPLL,  PLL_CON(8),  MODE_CON, 2, 10, 0, RT_NULL),
    [vpll0] = PLL(PLL_VPLL0, PLL_CON(16), MODE_CON, 4, 10, 0, RT_NULL),
    [vpll1] = PLL(PLL_VPLL1, PLL_CON(24), MODE_CON, 6, 10, 0, RT_NULL),
};

static struct rk_clk_gate clk_gates[] =
{
    GATE(SCLK_PVTM_CORE, "clk_pvtm_core", "xin24m", 0, 4),
    GATE(ACLK_BUS_SRC, "clk_bus_src", RT_NULL, 1, 0),
    GATE(PCLK_BUS, "pclk_bus", "clk_bus_src", 1, 3),
    GATE(PCLK_DDR, "pclk_ddr", "pclk_bus", 4, 15),
    GATE(HCLK_BUS, "hclk_bus", "clk_bus_src", 1, 2),
    GATE(ACLK_BUS, "aclk_bus", "clk_bus_src", 1, 1),
    GATE(SCLK_UART0, "clk_uart0", "clk_uart0_mux", 1, 12),
    GATE(SCLK_UART1, "clk_uart1", "clk_uart1_mux", 2, 0),
    GATE(SCLK_UART2, "clk_uart2", "clk_uart2_mux", 2, 4),
    GATE(SCLK_UART3, "clk_uart3", "clk_uart3_mux", 2, 8),
    GATE(SCLK_UART4, "clk_uart4", "clk_uart4_mux", 2, 12),
    GATE(SCLK_I2C0, "clk_i2c0", RT_NULL, 2, 13),
    GATE(SCLK_I2C1, "clk_i2c1", RT_NULL, 2, 14),
    GATE(SCLK_I2C2, "clk_i2c2", RT_NULL, 2, 15),
    GATE(SCLK_I2C3, "clk_i2c3", RT_NULL, 3, 0),
    GATE(SCLK_PWM0, "clk_pwm0", RT_NULL, 3, 1),
    GATE(SCLK_PWM1, "clk_pwm1", RT_NULL, 15, 0),
    GATE(SCLK_PWM2, "clk_pwm2", RT_NULL, 15, 1),
    GATE(SCLK_SPI0, "clk_spi0", RT_NULL, 3, 2),
    GATE(SCLK_SPI1, "clk_spi1", RT_NULL, 3, 3),
    GATE(SCLK_SPI2, "clk_spi2", RT_NULL, 3, 4),
    GATE(SCLK_TIMER0, "sclk_timer0", "xin24m", 3, 10),
    GATE(SCLK_TIMER1, "sclk_timer1", "xin24m", 3, 11),
    GATE(SCLK_TIMER2, "sclk_timer2", "xin24m", 3, 12),
    GATE(SCLK_TIMER3, "sclk_timer3", "xin24m", 3, 13),
    GATE(SCLK_TIMER4, "sclk_timer4", "xin24m", 3, 14),
    GATE(SCLK_TIMER5, "sclk_timer5", "xin24m", 3, 15),
    GATE(SCLK_TSADC, "clk_tsadc", "xin24m", 3, 5),
    GATE(SCLK_SARADC, "clk_saradc", "xin24m", 3, 6),
    GATE(SCLK_OTP, "clk_otp", "xin24m", 3, 7),
    GATE(SCLK_OTP_USR, "clk_otp_usr", "clk_otp", 3, 8),
    GATE(SCLK_CPU_BOOST, "clk_cpu_boost", "xin24m", 3, 9),
    GATE(SCLK_CRYPTO, "clk_crypto", RT_NULL, 1, 4),
    GATE(SCLK_CRYPTO_APK, "clk_crypto_apk", RT_NULL, 1, 5),
    GATE(DCLK_VOP, "dclk_vop", "dclk_vop_mux", 1, 8),
    GATE(ACLK_PERI_SRC, "clk_peri_src", RT_NULL, 8, 0),
    GATE(ACLK_PERI, "aclk_peri", "clk_peri_src", 8, 1),
    GATE(HCLK_PERI, "hclk_peri", "clk_peri_src", 8, 2),
    GATE(PCLK_PERI, "pclk_peri", "clk_peri_src", 8, 3),
    GATE(SCLK_NANDC_DIV, "clk_nandc_div", RT_NULL, 8, 4),
    GATE(SCLK_NANDC_DIV50, "clk_nandc_div50", RT_NULL, 8, 4),
    GATE(SCLK_NANDC, "clk_nandc", RT_NULL, 8, 5),
    GATE(SCLK_SDMMC_DIV, "clk_sdmmc_div", RT_NULL, 8, 6),
    GATE(SCLK_SDMMC_DIV50, "clk_sdmmc_div50", RT_NULL, 8, 6),
    GATE(SCLK_SDMMC, "clk_sdmmc", RT_NULL, 8, 7),
    GATE(SCLK_SDIO_DIV, "clk_sdio_div", RT_NULL, 8, 8),
    GATE(SCLK_SDIO_DIV50, "clk_sdio_div50", RT_NULL, 8, 8),
    GATE(SCLK_SDIO, "clk_sdio", RT_NULL, 8, 9),
    GATE(SCLK_EMMC_DIV, "clk_emmc_div", RT_NULL, 8, 10),
    GATE(SCLK_EMMC_DIV50, "clk_emmc_div50", RT_NULL, 8, 10),
    GATE(SCLK_EMMC, "clk_emmc", RT_NULL, 8, 11),
    GATE(SCLK_SFC, "clk_sfc", RT_NULL, 8, 12),
    GATE(SCLK_OTG_ADP, "clk_otg_adp", "clk_rtc32k", 8, 13),
    GATE(SCLK_MAC_SRC, "clk_mac_src", RT_NULL, 8, 14),
    GATE(SCLK_MAC_REF, "clk_mac_ref", "clk_mac", 9, 1),
    GATE(SCLK_MAC_RX_TX, "clk_mac_rx_tx", "clk_mac", 9, 0),
    GATE(SCLK_OWIRE, "clk_owire", RT_NULL, 8, 15),
    GATE(SCLK_DDRCLK, "clk_ddrphy4x_src", RT_NULL, 0, 10),
    GATE(PCLK_PMU, "pclk_pmu", "pclk_bus", 4, 5),
    GATE(SCLK_PMU, "clk_pmu", "pclk_bus", 4, 6),
    GATE(SCLK_USBPHY_REF, "clk_usbphy_ref", RT_NULL, 4, 8),
    GATE(SCLK_WIFI, "clk_wifi", RT_NULL, 4, 1),
    GATE(SCLK_PVTM_PMU, "clk_pvtm_pmu", "xin24m", 4, 4),
    GATE(HCLK_AUDIO, "hclk_audio", "clk_audio_src", 10, 1),
    GATE(PCLK_AUDIO, "pclk_audio", "clk_audio_src", 10, 2),
    GATE(SCLK_PDM, "clk_pdm", "clk_pdm_mux", 10, 5),
    GATE(SCLK_I2S0_8CH_TX_SRC, "clk_i2s0_8ch_tx_src", RT_NULL, 10, 12),
    GATE(SCLK_I2S0_8CH_TX, "clk_i2s0_8ch_tx", RT_NULL, 10, 14),
    GATE(SCLK_I2S0_8CH_TX_OUT, "clk_i2s0_8ch_tx_out", RT_NULL, 10, 15),
    GATE(SCLK_I2S0_8CH_RX_SRC, "clk_i2s0_8ch_rx_src", RT_NULL, 11, 0),
    GATE(SCLK_I2S0_8CH_RX, "clk_i2s0_8ch_rx", RT_NULL, 11, 2),
    GATE(SCLK_I2S0_8CH_RX_OUT, "clk_i2s0_8ch_rx_out", "clk_i2s0_8ch_rx", 11, 3),
    GATE(SCLK_I2S1_8CH_TX_SRC, "clk_i2s1_8ch_tx_src", RT_NULL, 11, 4),
    GATE(SCLK_I2S1_8CH_TX, "clk_i2s1_8ch_tx", RT_NULL, 11, 6),
    GATE(SCLK_I2S1_8CH_TX_OUT, "clk_i2s1_8ch_tx_out", RT_NULL, 11, 7),
    GATE(SCLK_I2S1_8CH_RX_SRC, "clk_i2s1_8ch_rx_src", RT_NULL, 11, 8),
    GATE(SCLK_I2S1_8CH_RX, "clk_i2s1_8ch_rx", RT_NULL, 11, 10),
    GATE(SCLK_I2S1_8CH_RX_OUT, "clk_i2s1_8ch_rx_out", "clk_i2s1_8ch_rx", 11, 11),
    GATE(SCLK_I2S2_8CH_TX_SRC, "clk_i2s2_8ch_tx_src", RT_NULL, 11, 12),
    GATE(SCLK_I2S2_8CH_TX, "clk_i2s2_8ch_tx", RT_NULL, 11, 14),
    GATE(SCLK_I2S2_8CH_TX_OUT, "clk_i2s2_8ch_tx_out", RT_NULL, 11, 15),
    GATE(SCLK_I2S2_8CH_RX_SRC, "clk_i2s2_8ch_rx_src", RT_NULL, 12, 0),
    GATE(SCLK_I2S2_8CH_RX, "clk_i2s2_8ch_rx", RT_NULL, 12, 2),
    GATE(SCLK_I2S2_8CH_RX_OUT, "clk_i2s2_8ch_rx_out", "clk_i2s2_8ch_rx", 12, 3),
    GATE(SCLK_I2S3_8CH_TX_SRC, "clk_i2s3_8ch_tx_src", RT_NULL, 12, 4),
    GATE(SCLK_I2S3_8CH_TX, "clk_i2s3_8ch_tx", RT_NULL, 12, 6),
    GATE(SCLK_I2S3_8CH_TX_OUT, "clk_i2s3_8ch_tx_out", RT_NULL, 12, 7),
    GATE(SCLK_I2S3_8CH_RX_SRC, "clk_i2s3_8ch_rx_src", RT_NULL, 12, 8),
    GATE(SCLK_I2S3_8CH_RX, "clk_i2s3_8ch_rx", RT_NULL, 12, 10),
    GATE(SCLK_I2S3_8CH_RX_OUT, "clk_i2s3_8ch_rx_out", "clk_i2s3_8ch_rx", 12, 11),
    GATE(SCLK_I2S0_2CH_SRC, "clk_i2s0_2ch_src", RT_NULL, 12, 12),
    GATE(SCLK_I2S0_2CH, "clk_i2s0_2ch", "clk_i2s0_2ch_mux", 12, 14),
    GATE(SCLK_I2S0_2CH_OUT, "clk_i2s0_2ch_out", RT_NULL, 12, 15),
    GATE(SCLK_I2S1_2CH_SRC, "clk_i2s1_2ch_src", RT_NULL, 13, 0),
    GATE(SCLK_I2S1_2CH, "clk_i2s1_2ch", "clk_i2s1_2ch_mux", 13, 2),
    GATE(SCLK_I2S1_2CH_OUT, "clk_i2s1_2ch_out", RT_NULL, 13, 3),
    GATE(SCLK_SPDIF_TX_DIV, "clk_spdif_tx_div", RT_NULL, 10, 6),
    GATE(SCLK_SPDIF_TX_DIV50, "clk_spdif_tx_div50", RT_NULL, 10, 6),
    GATE(SCLK_SPDIF_TX, "clk_spdif_tx", "clk_spdif_tx_mux", 10, 8),
    GATE(SCLK_SPDIF_RX_DIV, "clk_spdif_rx_div", RT_NULL, 10, 9),
    GATE(SCLK_SPDIF_RX_DIV50, "clk_spdif_rx_div50", RT_NULL, 10, 9),
    GATE(SCLK_SPDIF_RX, "clk_spdif_rx", "clk_spdif_rx_mux", 10, 11),
    GATE(ACLK_MAC, "aclk_mac", "aclk_peri", 9, 4),
    GATE(HCLK_NANDC, "hclk_nandc", "hclk_peri", 9, 6),
    GATE(HCLK_SDMMC, "hclk_sdmmc", "hclk_peri", 9, 7),
    GATE(HCLK_SDIO, "hclk_sdio", "hclk_peri", 9, 8),
    GATE(HCLK_EMMC, "hclk_emmc", "hclk_peri", 9, 9),
    GATE(HCLK_SFC, "hclk_sfc", "hclk_peri", 9, 10),
    GATE(HCLK_OTG, "hclk_otg", "hclk_peri", 9, 11),
    GATE(HCLK_HOST, "hclk_host", "hclk_peri", 9, 12),
    GATE(HCLK_HOST_ARB, "hclk_host_arb", "hclk_peri", 9, 13),
    GATE(PCLK_MAC, "pclk_mac", "pclk_peri", 9, 15),
    GATE(HCLK_PDM, "hclk_pdm", "hclk_audio", 14, 1),
    GATE(HCLK_SPDIFTX, "hclk_spdiftx", "hclk_audio", 14, 2),
    GATE(HCLK_SPDIFRX, "hclk_spdifrx", "hclk_audio", 14, 3),
    GATE(HCLK_I2S0_8CH, "hclk_i2s0_8ch", "hclk_audio", 14, 4),
    GATE(HCLK_I2S1_8CH, "hclk_i2s1_8ch", "hclk_audio", 14, 5),
    GATE(HCLK_I2S2_8CH, "hclk_i2s2_8ch", "hclk_audio", 14, 6),
    GATE(HCLK_I2S3_8CH, "hclk_i2s3_8ch", "hclk_audio", 14, 7),
    GATE(HCLK_I2S0_2CH, "hclk_i2s0_2ch", "hclk_audio", 14, 8),
    GATE(HCLK_I2S1_2CH, "hclk_i2s1_2ch", "hclk_audio", 14, 9),
    GATE(HCLK_VAD, "hclk_vad", "hclk_audio", 14, 10),
    GATE(PCLK_ACODEC, "pclk_acodec", "pclk_audio", 14, 12),
    GATE(ACLK_CRYPTO, "aclk_crypto", "aclk_bus", 5, 2),
    GATE(ACLK_VOP, "aclk_vop", "aclk_bus", 5, 3),
    GATE(HCLK_CRYPTO, "hclk_crypto", "hclk_bus", 5, 7),
    GATE(HCLK_VOP, "hclk_vop", "hclk_bus", 5, 8),
    GATE(PCLK_UART0, "pclk_uart0", "pclk_bus", 5, 10),
    GATE(PCLK_UART1, "pclk_uart1", "pclk_bus", 5, 11),
    GATE(PCLK_UART2, "pclk_uart2", "pclk_bus", 5, 12),
    GATE(PCLK_UART3, "pclk_uart3", "pclk_bus", 5, 13),
    GATE(PCLK_UART4, "pclk_uart4", "pclk_bus", 5, 14),
    GATE(PCLK_I2C0, "pclk_i2c0", "pclk_bus", 5, 15),
    GATE(PCLK_I2C1, "pclk_i2c1", "pclk_bus", 6, 0),
    GATE(PCLK_I2C2, "pclk_i2c2", "pclk_bus", 6, 1),
    GATE(PCLK_I2C3, "pclk_i2c3", "pclk_bus", 6, 2),
    GATE(PCLK_PWM0, "pclk_pwm0", "pclk_bus", 6, 3),
    GATE(PCLK_SPI0, "pclk_spi0", "pclk_bus", 6, 4),
    GATE(PCLK_SPI1, "pclk_spi1", "pclk_bus", 6, 5),
    GATE(PCLK_SPI2, "pclk_spi2", "pclk_bus", 6, 6),
    GATE(PCLK_SARADC, "pclk_saradc", "pclk_bus", 6, 7),
    GATE(PCLK_TSADC, "pclk_tsadc", "pclk_bus", 6, 8),
    GATE(PCLK_TIMER, "pclk_timer", "pclk_bus", 6, 9),
    GATE(PCLK_OTP_NS, "pclk_otp_ns", "pclk_bus", 6, 10),
    GATE(PCLK_GPIO0, "pclk_gpio0", "pclk_bus", 6, 12),
    GATE(PCLK_GPIO1, "pclk_gpio1", "pclk_bus", 6, 13),
    GATE(PCLK_GPIO2, "pclk_gpio2", "pclk_bus", 6, 14),
    GATE(PCLK_GPIO3, "pclk_gpio3", "pclk_bus", 6, 15),
    GATE(PCLK_GPIO4, "pclk_gpio4", "pclk_bus", 7, 0),
    GATE(PCLK_SGRF, "pclk_sgrf", "pclk_bus", 7, 1),
    GATE(PCLK_GRF, "pclk_grf", "pclk_bus", 7, 2),
    GATE(PCLK_USBSD_DET, "pclk_usbsd_det", "pclk_bus", 7, 3),
    GATE(PCLK_DDR_UPCTL, "pclk_ddr_upctl", "pclk_bus", 7, 4),
    GATE(PCLK_DDR_MON, "pclk_ddr_mon", "pclk_bus", 7, 5),
    GATE(PCLK_DDRPHY, "pclk_ddrphy", "pclk_bus", 7, 6),
    GATE(PCLK_DDR_STDBY, "pclk_ddr_stdby", "pclk_bus", 7, 7),
    GATE(PCLK_USB_GRF, "pclk_usb_grf", "pclk_bus", 7, 8),
    GATE(PCLK_CRU, "pclk_cru", "pclk_bus", 7, 9),
    GATE(PCLK_OTP_PHY, "pclk_otp_phy", "pclk_bus", 7, 10),
    GATE(PCLK_CPU_BOOST, "pclk_cpu_boost", "pclk_bus", 7, 11),
    GATE(PCLK_PWM1, "pclk_pwm1", "pclk_bus", 7, 12),
    GATE(PCLK_PWM2, "pclk_pwm2", "pclk_bus", 7, 13),
    GATE(PCLK_CAN, "pclk_can", "pclk_bus", 7, 14),
    GATE(PCLK_OWIRE, "pclk_owire", "pclk_bus", 7, 15),
};

#define PLL_MODE_MASK   0x1
#include "clk-pll.c"
#include "softrst.c"

static rt_base_t armclk_set_clk(struct rk_clk_priv *priv, rt_ubase_t hz)
{
    struct rk_cru *cru = priv->cru;
    const struct rk_cpu_rate_table *rate;
    rt_ubase_t old_rate;

    rate = rk_get_cpu_settings(cpu_rates, hz);
    if (!rate)
    {
        LOG_E("Unsupport rate %u", hz);

        return -RT_ENOSYS;
    }

    /*
     * select apll as cpu/core clock pll source and
     * set up dependent divisors for PERI and ACLK clocks.
     * core hz : apll = 1:1
     */
    old_rate = rk_pll_get_rate(&pll_clks[apll], priv->cru);
    if (old_rate > hz)
    {
        if (rk_pll_set_rate(&pll_clks[apll], priv->cru, hz))
        {
            return -RT_EINVAL;
        }

        rk_clrsetreg(&cru->clksel_con[0],
                CORE_CLK_PLL_SEL_MASK | CORE_DIV_CON_MASK |
                CORE_ACLK_DIV_MASK | CORE_DBG_DIV_MASK,
                rate->aclk_div << CORE_ACLK_DIV_SHIFT |
                rate->pclk_div << CORE_DBG_DIV_SHIFT |
                CORE_CLK_PLL_SEL_APLL << CORE_CLK_PLL_SEL_SHIFT |
                0 << CORE_DIV_CON_SHIFT);
    }
    else if (old_rate < hz)
    {
        rk_clrsetreg(&cru->clksel_con[0],
                CORE_CLK_PLL_SEL_MASK | CORE_DIV_CON_MASK |
                CORE_ACLK_DIV_MASK | CORE_DBG_DIV_MASK,
                rate->aclk_div << CORE_ACLK_DIV_SHIFT |
                rate->pclk_div << CORE_DBG_DIV_SHIFT |
                CORE_CLK_PLL_SEL_APLL << CORE_CLK_PLL_SEL_SHIFT |
                0 << CORE_DIV_CON_SHIFT);

        if (rk_pll_set_rate(&pll_clks[apll], priv->cru, hz))
        {
            return -RT_EINVAL;
        }
    }

    return rk_pll_get_rate(&pll_clks[apll], priv->cru);
}

static void clk_get_pll_rate(struct rk_clk_priv *priv)
{
    if (!priv->dpll_hz)
    {
        priv->dpll_hz = rk_pll_get_rate(&pll_clks[dpll], priv->cru);
    }

    if (!priv->vpll0_hz)
    {
        priv->vpll0_hz = rk_pll_get_rate(&pll_clks[vpll0], priv->cru);
    }

    if (!priv->vpll1_hz)
    {
        priv->vpll1_hz = rk_pll_get_rate(&pll_clks[vpll1], priv->cru);
    }
}

static rt_base_t i2c_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con, con_id;

    switch (clk_id)
    {
    case SCLK_I2C0:
        con_id = 25;
        break;
    case SCLK_I2C1:
        con_id = 26;
        break;
    case SCLK_I2C2:
        con_id = 27;
        break;
    case SCLK_I2C3:
        con_id = 28;
        break;
    default:
        return -RT_EINVAL;
    }

    con = HWREG32(&cru->clksel_con[con_id]);
    div = con >> CLK_I2C_DIV_CON_SHIFT & CLK_I2C_DIV_CON_MASK;

    return DIV_TO_RATE(priv->dpll_hz, div);
}

static rt_base_t i2c_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t src_clk_div, con_id;

    src_clk_div = RT_DIV_ROUND_UP(priv->dpll_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 127);

    switch (clk_id)
    {
    case SCLK_I2C0:
        con_id = 25;
        break;
    case SCLK_I2C1:
        con_id = 26;
        break;
    case SCLK_I2C2:
        con_id = 27;
        break;
    case SCLK_I2C3:
        con_id = 28;
        break;
    default:
        return -RT_EINVAL;
    }

    rk_clrsetreg(&cru->clksel_con[con_id],
            CLK_I2C_PLL_SEL_MASK | CLK_I2C_DIV_CON_MASK,
            CLK_I2C_PLL_SEL_DPLL << CLK_I2C_PLL_SEL_SHIFT |
            (src_clk_div - 1) << CLK_I2C_DIV_CON_SHIFT);

    return i2c_get_clk(priv, clk_id);
}

static rt_base_t mac_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con = HWREG32(&cru->clksel_con[43]);
    rt_ubase_t pll_rate;
    rt_uint8_t div;

    if ((con >> MAC_PLL_SHIFT) & MAC_SEL_VPLL0)
    {
        pll_rate = rk_pll_get_rate(&pll_clks[vpll0], priv->cru);
    }
    else if ((con >> MAC_PLL_SHIFT) & MAC_SEL_VPLL1)
    {
        pll_rate = rk_pll_get_rate(&pll_clks[vpll1], priv->cru);
    }
    else
    {
        pll_rate = rk_pll_get_rate(&pll_clks[dpll], priv->cru);
    }

    /* default set 50MHZ for gmac */
    if (!rate)
    {
        rate = 50000000;
    }

    div = RT_DIV_ROUND_UP(pll_rate, rate) - 1;
    RT_ASSERT(div < 32);

    rk_clrsetreg(&cru->clksel_con[43], MAC_DIV_MASK, div << MAC_DIV_SHIFT);

    return DIV_TO_RATE(pll_rate, div);
}

static rt_base_t mac_set_speed_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;

    if (rate != 2500000 && rate != 25000000)
    {
        LOG_E("Unsupported mac speed: %u", rate);

        return -RT_EINVAL;
    }

    rk_clrsetreg(&cru->clksel_con[43], MAC_CLK_SPEED_SEL_MASK,
            ((rate == 2500000) ? 0 : 1) << MAC_CLK_SPEED_SEL_SHIFT);

    return 0;
}

static rt_base_t mmc_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con, con_id;

    switch (clk_id)
    {
    case HCLK_SDMMC:
    case SCLK_SDMMC:
        con_id = 39;
        break;
    case HCLK_EMMC:
    case SCLK_EMMC:
    case SCLK_EMMC_SAMPLE:
        con_id = 41;
        break;
    default:
        return -RT_EINVAL;
    }

    con = HWREG32(&cru->clksel_con[con_id]);
    div = (con & EMMC_DIV_MASK) >> EMMC_DIV_SHIFT;

    if ((con & EMMC_PLL_MASK) >> EMMC_PLL_SHIFT == EMMC_SEL_24M)
    {
        return DIV_TO_RATE(OSC_HZ, div) / 2;
    }
    else
    {
        return DIV_TO_RATE(priv->vpll0_hz, div) / 2;
    }
}

static rt_base_t mmc_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;
    rt_uint32_t con_id;

    switch (clk_id)
    {
    case HCLK_SDMMC:
    case SCLK_SDMMC:
        con_id = 39;
        break;
    case HCLK_EMMC:
    case SCLK_EMMC:
        con_id = 41;
        break;
    default:
        return -RT_EINVAL;
    }
    /* Select clk_sdmmc/emmc source from VPLL0 by default */
    /* mmc clock defaulg div 2 internal, need provide double in cru */
    src_clk_div = RT_DIV_ROUND_UP(priv->vpll0_hz / 2, rate);

    if (src_clk_div > 127)
    {
        /* use 24MHz source for 400KHz clock */
        src_clk_div = RT_DIV_ROUND_UP(OSC_HZ / 2, rate);
        rk_clrsetreg(&cru->clksel_con[con_id],
                EMMC_PLL_MASK | EMMC_DIV_MASK | EMMC_CLK_SEL_MASK,
                EMMC_CLK_SEL_EMMC << EMMC_CLK_SEL_SHIFT |
                EMMC_SEL_24M << EMMC_PLL_SHIFT |
                (src_clk_div - 1) << EMMC_DIV_SHIFT);
    }
    else
    {
        rk_clrsetreg(&cru->clksel_con[con_id],
                EMMC_PLL_MASK | EMMC_DIV_MASK | EMMC_CLK_SEL_MASK,
                EMMC_CLK_SEL_EMMC << EMMC_CLK_SEL_SHIFT |
                EMMC_SEL_VPLL0 << EMMC_PLL_SHIFT |
                (src_clk_div - 1) << EMMC_DIV_SHIFT);
    }

    return mmc_get_clk(priv, clk_id);
}

static rt_base_t saradc_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con;

    con = HWREG32(&cru->clksel_con[34]);
    div = con >> CLK_SARADC_DIV_CON_SHIFT & CLK_SARADC_DIV_CON_MASK;

    return DIV_TO_RATE(OSC_HZ, div);
}

static rt_base_t saradc_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(OSC_HZ, rate);
    RT_ASSERT(src_clk_div - 1 <= 2047);

    rk_clrsetreg(&cru->clksel_con[34], CLK_SARADC_DIV_CON_MASK,
            (src_clk_div - 1) << CLK_SARADC_DIV_CON_SHIFT);

    return saradc_get_clk(priv, clk_id);
}

static rt_base_t tsadc_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con;

    con = HWREG32(&cru->clksel_con[33]);
    div = con >> CLK_SARADC_DIV_CON_SHIFT & CLK_SARADC_DIV_CON_MASK;

    return DIV_TO_RATE(OSC_HZ, div);
}

static rt_base_t tsadc_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(OSC_HZ, rate);
    RT_ASSERT(src_clk_div - 1 <= 2047);

    rk_clrsetreg(&cru->clksel_con[33], CLK_SARADC_DIV_CON_MASK,
            (src_clk_div - 1) << CLK_SARADC_DIV_CON_SHIFT);

    return tsadc_get_clk(priv, clk_id);
}

static rt_base_t spi_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con, con_id;

    switch (clk_id)
    {
    case SCLK_SPI0:
        con_id = 30;
        break;
    case SCLK_SPI1:
        con_id = 31;
        break;
    case SCLK_SPI2:
        con_id = 32;
        break;
    default:
        return -RT_EINVAL;
    }

    con = HWREG32(&cru->clksel_con[con_id]);
    div = con >> CLK_SPI_DIV_CON_SHIFT & CLK_SPI_DIV_CON_MASK;

    return DIV_TO_RATE(priv->dpll_hz, div);
}

static rt_base_t spi_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t src_clk_div, con_id;

    src_clk_div = RT_DIV_ROUND_UP(priv->dpll_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 127);

    switch (clk_id)
    {
    case SCLK_SPI0:
        con_id = 30;
        break;
    case SCLK_SPI1:
        con_id = 31;
        break;
    case SCLK_SPI2:
        con_id = 32;
        break;
    default:
        return -RT_EINVAL;
    }

    rk_clrsetreg(&cru->clksel_con[con_id],
            CLK_SPI_PLL_SEL_MASK | CLK_SPI_DIV_CON_MASK,
            CLK_SPI_PLL_SEL_DPLL << CLK_SPI_PLL_SEL_SHIFT |
            (src_clk_div - 1) << CLK_SPI_DIV_CON_SHIFT);

    return spi_get_clk(priv, clk_id);
}

static rt_base_t pwm_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con;

    con = HWREG32(&cru->clksel_con[29]);
    div = con >> CLK_PWM_DIV_CON_SHIFT & CLK_PWM_DIV_CON_MASK;

    return DIV_TO_RATE(priv->dpll_hz, div);
}

static rt_base_t pwm_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(priv->dpll_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 127);

    rk_clrsetreg(&cru->clksel_con[29],
            CLK_PWM_PLL_SEL_MASK | CLK_PWM_DIV_CON_MASK,
            CLK_PWM_PLL_SEL_DPLL << CLK_PWM_PLL_SEL_SHIFT |
            (src_clk_div - 1) << CLK_PWM_DIV_CON_SHIFT);

    return pwm_get_clk(priv, clk_id);
}

static rt_base_t vop_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, pll_sel, vol_sel, con, parent;

    con = HWREG32(&cru->clksel_con[8]);
    vol_sel = (con & DCLK_VOP_SEL_MASK) >> DCLK_VOP_SEL_SHIFT;
    pll_sel = (con & DCLK_VOP_PLL_SEL_MASK) >> DCLK_VOP_PLL_SEL_SHIFT;
    div = con & DCLK_VOP_DIV_MASK;

    if (vol_sel == DCLK_VOP_SEL_24M)
    {
        parent = OSC_HZ;
    }
    else if (vol_sel == DCLK_VOP_SEL_DIVOUT)
    {
        switch (pll_sel)
        {
        case DCLK_VOP_PLL_SEL_DPLL:
            parent = priv->dpll_hz;
            break;
        case DCLK_VOP_PLL_SEL_VPLL0:
            parent = priv->vpll0_hz;
            break;
        case DCLK_VOP_PLL_SEL_VPLL1:
            parent = priv->vpll0_hz;
            break;
        default:
            return -RT_EINVAL;
        }
    } else {
        return -RT_EINVAL;
    }

    return DIV_TO_RATE(parent, div);
}

static rt_base_t vop_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    rt_ubase_t pll_rate, now, best_rate = 0;
    rt_uint32_t div, best_div = 0, best_sel = 0;

    for (int i = 0; i <= DCLK_VOP_PLL_SEL_VPLL1; i++)
    {
        switch (i)
        {
        case DCLK_VOP_PLL_SEL_DPLL:
            pll_rate = priv->dpll_hz;
            break;
        case DCLK_VOP_PLL_SEL_VPLL0:
            pll_rate = priv->vpll0_hz;
            break;
        case DCLK_VOP_PLL_SEL_VPLL1:
            pll_rate = priv->vpll1_hz;
            break;
        default:
            return -RT_EINVAL;
        }

        div = RT_DIV_ROUND_UP(pll_rate, rate);

        if (div > 255)
        {
            continue;
        }
        now = pll_rate / div;

        if (rt_abs(rate - now) < rt_abs(rate - best_rate))
        {
            best_rate = now;
            best_div = div;
            best_sel = i;
        }
    }

    if (best_rate != rate && rate == OSC_HZ)
    {
        rk_clrsetreg(&cru->clksel_con[8],
                DCLK_VOP_SEL_MASK,
                DCLK_VOP_SEL_24M << DCLK_VOP_SEL_SHIFT);
    }
    else if (best_rate)
    {
        rk_clrsetreg(&cru->clksel_con[8],
                DCLK_VOP_SEL_MASK | DCLK_VOP_PLL_SEL_MASK |
                DCLK_VOP_DIV_MASK,
                DCLK_VOP_SEL_DIVOUT << DCLK_VOP_SEL_SHIFT |
                best_sel << DCLK_VOP_PLL_SEL_SHIFT |
                (best_div - 1) << DCLK_VOP_DIV_SHIFT);
    }
    else
    {
        return -RT_EINVAL;
    }

    return vop_get_clk(priv, clk_id);
}

static rt_base_t bus_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con, parent = priv->dpll_hz;

    switch (clk_id)
    {
    case ACLK_BUS:
        con = HWREG32(&cru->clksel_con[5]);
        div = (con & BUS_ACLK_DIV_MASK) >> BUS_ACLK_DIV_SHIFT;
        break;
    case HCLK_BUS:
        con = HWREG32(&cru->clksel_con[6]);
        div = (con & BUS_HCLK_DIV_MASK) >> BUS_HCLK_DIV_SHIFT;
        break;
    case PCLK_BUS:
    case PCLK_WDT:
        con = HWREG32(&cru->clksel_con[6]);
        div = (con & BUS_PCLK_DIV_MASK) >> BUS_PCLK_DIV_SHIFT;
        break;
    default:
        return -RT_EINVAL;
    }

    return DIV_TO_RATE(parent, div);
}

static rt_base_t bus_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(priv->dpll_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 31);

    /*
     * select dpll as pd_bus bus clock source and
     * set up dependent divisors for PCLK/HCLK and ACLK clocks.
     */
    switch (clk_id)
    {
    case ACLK_BUS:
        rk_clrsetreg(&cru->clksel_con[5], BUS_PLL_SEL_MASK | BUS_ACLK_DIV_MASK,
                BUS_PLL_SEL_DPLL << BUS_PLL_SEL_SHIFT |
                (src_clk_div - 1) << BUS_ACLK_DIV_SHIFT);
        break;
    case HCLK_BUS:
        rk_clrsetreg(&cru->clksel_con[6], BUS_HCLK_DIV_MASK,
                (src_clk_div - 1) << BUS_HCLK_DIV_SHIFT);
        break;
    case PCLK_BUS:
        rk_clrsetreg(&cru->clksel_con[6], BUS_PCLK_DIV_MASK,
                (src_clk_div - 1) << BUS_PCLK_DIV_SHIFT);
        break;
    default:
        return -RT_EINVAL;
    }

    return bus_get_clk(priv, clk_id);
}

static rt_base_t peri_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con, parent = priv->dpll_hz;

    switch (clk_id)
    {
    case ACLK_PERI:
        con = HWREG32(&cru->clksel_con[36]);
        div = (con & PERI_ACLK_DIV_MASK) >> PERI_ACLK_DIV_SHIFT;
        break;
    case HCLK_PERI:
        con = HWREG32(&cru->clksel_con[37]);
        div = (con & PERI_HCLK_DIV_MASK) >> PERI_HCLK_DIV_SHIFT;
        break;
    case PCLK_PERI:
        con = HWREG32(&cru->clksel_con[37]);
        div = (con & PERI_PCLK_DIV_MASK) >> PERI_PCLK_DIV_SHIFT;
        break;
    default:
        return -RT_EINVAL;
    }

    return DIV_TO_RATE(parent, div);
}

static rt_base_t peri_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(priv->dpll_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 31);

    /*
     * select dpll as pd_peri bus clock source and
     * set up dependent divisors for PCLK/HCLK and ACLK clocks.
     */
    switch (clk_id)
    {
    case ACLK_PERI:
        rk_clrsetreg(&cru->clksel_con[36], PERI_PLL_SEL_MASK | PERI_ACLK_DIV_MASK,
                PERI_PLL_DPLL << PERI_PLL_SEL_SHIFT |
                (src_clk_div - 1) << PERI_ACLK_DIV_SHIFT);
        break;
    case HCLK_PERI:
        rk_clrsetreg(&cru->clksel_con[37], PERI_HCLK_DIV_MASK,
                (src_clk_div - 1) << PERI_HCLK_DIV_SHIFT);
        break;
    case PCLK_PERI:
        rk_clrsetreg(&cru->clksel_con[37], PERI_PCLK_DIV_MASK,
                (src_clk_div - 1) << PERI_PCLK_DIV_SHIFT);
        break;
    default:
        return -RT_EINVAL;
    }

    return peri_get_clk(priv, clk_id);
}

static rt_base_t audio_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con, parent = priv->vpll0_hz;

    switch (clk_id)
    {
    case HCLK_AUDIO:
        con = HWREG32(&cru->clksel_con[45]);
        div = (con & AUDIO_HCLK_DIV_MASK) >> AUDIO_HCLK_DIV_SHIFT;
        break;
    case PCLK_AUDIO:
        con = HWREG32(&cru->clksel_con[45]);
        div = (con & AUDIO_PCLK_DIV_MASK) >> AUDIO_PCLK_DIV_SHIFT;
        break;
    default:
        return -RT_EINVAL;
    }

    return DIV_TO_RATE(parent, div);
}

static rt_base_t audio_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(priv->vpll0_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 31);

    /*
     * select vpll0 as audio bus clock source and
     * set up dependent divisors for HCLK and PCLK clocks.
     */
    switch (clk_id)
    {
    case HCLK_AUDIO:
        rk_clrsetreg(&cru->clksel_con[45], AUDIO_PLL_SEL_MASK | AUDIO_HCLK_DIV_MASK,
                AUDIO_PLL_VPLL0 << AUDIO_PLL_SEL_SHIFT |
                (src_clk_div - 1) << AUDIO_HCLK_DIV_SHIFT);
        break;
    case PCLK_AUDIO:
        rk_clrsetreg(&cru->clksel_con[45], AUDIO_PLL_SEL_MASK | AUDIO_PCLK_DIV_MASK,
                AUDIO_PLL_VPLL0 << AUDIO_PLL_SEL_SHIFT |
                (src_clk_div - 1) << AUDIO_PCLK_DIV_SHIFT);
        break;
    default:
        return -RT_EINVAL;
    }

    return peri_get_clk(priv, clk_id);
}

static rt_base_t crypto_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, con, parent;

    switch (clk_id)
    {
    case SCLK_CRYPTO:
        con = HWREG32(&cru->clksel_con[7]);
        div = (con & CRYPTO_DIV_MASK) >> CRYPTO_DIV_SHIFT;
        parent = priv->vpll0_hz;
        break;
    case SCLK_CRYPTO_APK:
        con = HWREG32(&cru->clksel_con[7]);
        div = (con & CRYPTO_APK_DIV_MASK) >> CRYPTO_APK_DIV_SHIFT;
        parent = priv->vpll0_hz;
        break;
    default:
        return -RT_EINVAL;
    }

    return DIV_TO_RATE(parent, div);
}

static rt_base_t crypto_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(priv->vpll0_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 31);

    /*
     * select gpll as crypto clock source and
     * set up dependent divisors for crypto clocks.
     */
    switch (clk_id)
    {
    case SCLK_CRYPTO:
        rk_clrsetreg(&cru->clksel_con[7], CRYPTO_PLL_SEL_MASK | CRYPTO_DIV_MASK,
                CRYPTO_PLL_SEL_VPLL0 << CRYPTO_PLL_SEL_SHIFT |
                (src_clk_div - 1) << CRYPTO_DIV_SHIFT);
        break;
    case SCLK_CRYPTO_APK:
        rk_clrsetreg(&cru->clksel_con[7], CRYPTO_APK_PLL_SEL_MASK | CRYPTO_APK_DIV_MASK,
                CRYPTO_PLL_SEL_VPLL0 << CRYPTO_APK_SEL_SHIFT |
                (src_clk_div - 1) << CRYPTO_APK_DIV_SHIFT);
        break;
    default:
        return -RT_EINVAL;
    }

    return crypto_get_clk(priv, clk_id);
}

static rt_ubase_t uart_get_rate(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t reg, con, fracdiv, div, src, p_src, p_rate;
    rt_ubase_t m, n;

    switch (clk_id)
    {
    case SCLK_UART0:
        reg = 10;
        break;
    case SCLK_UART1:
        reg = 13;
        break;
    case SCLK_UART2:
        reg = 16;
        break;
    case SCLK_UART3:
        reg = 19;
        break;
    case SCLK_UART4:
        reg = 22;
        break;
    default:
        return -RT_ERROR;
    }

    con = HWREG32(&cru->clksel_con[reg]);
    p_src = (con & CLK_UART_SRC_SEL_MASK) >> CLK_UART_SRC_SEL_SHIFT;
    div = (con & CLK_UART_SRC_DIV_MASK) >> CLK_UART_SRC_DIV_SHIFT;

    if (p_src == CLK_UART_SRC_SEL_DPLL)
    {
        p_rate = priv->dpll_hz;
    }
    else if (p_src == CLK_UART_SRC_SEL_VPLL0)
    {
        p_rate = priv->vpll0_hz;
    }
    else if (p_src == CLK_UART_SRC_SEL_VPLL1)
    {
        p_rate = priv->vpll1_hz;
    }
    else if (p_src == CLK_UART_SRC_SEL_480M)
    {
        p_rate = 480000000;
    }
    else
    {
        p_rate = OSC_HZ;
    }

    con = HWREG32(&cru->clksel_con[reg + 1]);
    src = (con & CLK_UART_SEL_MASK) >> CLK_UART_SEL_SHIFT;

    if (src == CLK_UART_SEL_SRC)
    {
        return DIV_TO_RATE(p_rate, div);
    }
    else if (src == CLK_UART_SEL_NP5)
    {
        div = (con & CLK_UART_NP5_DIV_MASK) >> CLK_UART_NP5_DIV_SHIFT;
        return DIV_TO_RATE(p_rate, div);
    }
    else if (src == CLK_UART_SEL_FRAC_OUT)
    {
        fracdiv = HWREG32(&cru->clksel_con[reg + 2]);
        n = fracdiv & CLK_UART_FRAC_NUMERATOR_MASK;
        n >>= CLK_UART_FRAC_NUMERATOR_SHIFT;
        m = fracdiv & CLK_UART_FRAC_DENOMINATOR_MASK;
        m >>= CLK_UART_FRAC_DENOMINATOR_SHIFT;
        return DIV_TO_RATE(p_rate, div) * n / m;
    }
    else
    {
        return OSC_HZ;
    }
}

static rt_ubase_t uart_set_rate(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t reg, clk_src, uart_src, src_div, np5_div;
    rt_ubase_t m = 0, n = 0, val;

    if (priv->dpll_hz % rate == 0)
    {
        clk_src = CLK_UART_SRC_SEL_DPLL;
        uart_src = CLK_UART_SEL_SRC;
        src_div = RT_DIV_ROUND_UP(priv->dpll_hz, rate);
        np5_div = 2;
    }
    else if (priv->vpll0_hz % rate == 0)
    {
        clk_src = CLK_UART_SRC_SEL_VPLL0;
        uart_src = CLK_UART_SEL_SRC;
        src_div = RT_DIV_ROUND_UP(priv->dpll_hz, rate);
        np5_div = 2;
    }
    else if (priv->vpll1_hz % rate == 0)
    {
        clk_src = CLK_UART_SRC_SEL_VPLL1;
        uart_src = CLK_UART_SEL_SRC;
        src_div = RT_DIV_ROUND_UP(priv->dpll_hz, rate);
        np5_div = 2;
    }
    else if (rate == OSC_HZ)
    {
        clk_src = CLK_UART_SRC_SEL_DPLL;
        uart_src = CLK_UART_SRC_SEL_XIN_OSC0;
        np5_div = 2;
        src_div = 2;
    }
    else
    {
        clk_src = CLK_UART_SRC_SEL_DPLL;
        uart_src = CLK_UART_SEL_FRAC_OUT;
        src_div = 2;
        np5_div = 2;
        rational_best_approximation(rate, priv->dpll_hz / src_div, RT_GENMASK(16 - 1, 0), RT_GENMASK(16 - 1, 0), &m, &n);
    }

    switch (clk_id)
    {
    case SCLK_UART0:
        reg = 10;
        break;
    case SCLK_UART1:
        reg = 13;
        break;
    case SCLK_UART2:
        reg = 16;
        break;
    case SCLK_UART3:
        reg = 19;
        break;
    case SCLK_UART4:
        reg = 22;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[reg], CLK_UART_SRC_SEL_MASK | CLK_UART_SRC_DIV_MASK,
            (clk_src << CLK_UART_SRC_SEL_SHIFT) | ((src_div - 1) << CLK_UART_SRC_DIV_SHIFT));
    rk_clrsetreg(&cru->clksel_con[reg + 1], CLK_UART_SEL_MASK | CLK_UART_NP5_DIV_MASK,
            (uart_src << CLK_UART_SEL_SHIFT) | ((np5_div - 1) << CLK_UART_NP5_DIV_SHIFT));

    if (m && n)
    {
        val = m << CLK_UART_FRAC_NUMERATOR_SHIFT | n;
        HWREG32(&cru->clksel_con[reg + 2]) = val;
    }

    return uart_get_rate(priv, clk_id);
}

static rt_base_t rk_clk_get_rate(struct rk_clk_platform_data *pdata,
        struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    rt_ubase_t rate = 0;

    switch (pdata->id)
    {
    case PLL_APLL:
    case ARMCLK:
        rate = rk_pll_get_rate(&pll_clks[apll], priv->cru);
        break;
    case PLL_DPLL:
        rate = rk_pll_get_rate(&pll_clks[dpll], priv->cru);
        break;
    case PLL_VPLL0:
        rate = rk_pll_get_rate(&pll_clks[vpll0], priv->cru);
        break;
    case PLL_VPLL1:
        rate = rk_pll_get_rate(&pll_clks[vpll1], priv->cru);
        break;
    case HCLK_SDMMC:
    case HCLK_EMMC:
    case SCLK_SDMMC:
    case SCLK_EMMC:
    case SCLK_EMMC_SAMPLE:
        rate = mmc_get_clk(priv, pdata->id);
        break;
    case SCLK_I2C0:
    case SCLK_I2C1:
    case SCLK_I2C2:
    case SCLK_I2C3:
        rate = i2c_get_clk(priv, pdata->id);
        break;
    case SCLK_SARADC:
        rate = saradc_get_clk(priv, pdata->id);
        break;
    case SCLK_TSADC:
        rate = tsadc_get_clk(priv, pdata->id);
        break;
    case SCLK_SPI0:
    case SCLK_SPI1:
        rate = spi_get_clk(priv, pdata->id);
        break;
    case SCLK_PWM0:
        rate = pwm_get_clk(priv, pdata->id);
        break;
    case DCLK_VOP:
        rate = vop_get_clk(priv, pdata->id);
        break;
    case ACLK_BUS:
    case HCLK_BUS:
    case PCLK_BUS:
    case PCLK_WDT:
        rate = bus_get_clk(priv, pdata->id);
        break;
    case ACLK_PERI:
    case HCLK_PERI:
    case PCLK_PERI:
        rate = peri_get_clk(priv, pdata->id);
        break;
    case HCLK_AUDIO:
    case PCLK_AUDIO:
        rate = audio_get_clk(priv, pdata->id);
        break;
    case SCLK_CRYPTO:
    case SCLK_CRYPTO_APK:
        rate = crypto_get_clk(priv, pdata->id);
        break;
    case SCLK_UART0:
    case SCLK_UART1:
    case SCLK_UART2:
    case SCLK_UART3:
    case SCLK_UART4:
        rate = uart_get_rate(priv, pdata->id);
        break;
    case SCLK_TIMER0:
    case SCLK_TIMER1:
    case SCLK_TIMER2:
    case SCLK_TIMER3:
    case SCLK_TIMER4:
    case SCLK_TIMER5:
        rate = OSC_HZ;
        break;
    default:
        return -RT_EINVAL;
    }

    return rate;
}

static rt_base_t rk_clk_set_rate(struct rk_clk_platform_data *pdata,
        struct rk_clk *rk_clk, rt_ubase_t rate)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    rt_ubase_t res = 0;

    switch (pdata->id)
    {
    case PLL_DPLL:
        res = rk_pll_set_rate(&pll_clks[dpll], priv->cru, rate);
        priv->dpll_hz = rk_pll_get_rate(&pll_clks[dpll], priv->cru);
        break;
    case ARMCLK:
        if (priv->armclk_hz)
        {
            armclk_set_clk(priv, rate);
        }
        priv->armclk_hz = rate;
        break;
    case HCLK_SDMMC:
    case HCLK_EMMC:
    case SCLK_SDMMC:
    case SCLK_EMMC:
        res = mmc_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_I2C0:
    case SCLK_I2C1:
    case SCLK_I2C2:
    case SCLK_I2C3:
        res = i2c_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_MAC:
        res = mac_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_MAC_RMII:
        res = mac_set_speed_clk(priv, pdata->id, rate);
        break;
    case SCLK_SARADC:
        res = saradc_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_TSADC:
        res = tsadc_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_SPI0:
    case SCLK_SPI1:
        res = spi_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_PWM0:
        res = pwm_set_clk(priv, pdata->id, rate);
        break;
    case DCLK_VOP:
        res = vop_set_clk(priv, pdata->id, rate);
        break;
    case ACLK_BUS:
    case HCLK_BUS:
    case PCLK_BUS:
        res = bus_set_clk(priv, pdata->id, rate);
        break;
    case ACLK_PERI:
    case HCLK_PERI:
    case PCLK_PERI:
        res = peri_set_clk(priv, pdata->id, rate);
        break;
    case HCLK_AUDIO:
    case PCLK_AUDIO:
        res = audio_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_CRYPTO:
    case SCLK_CRYPTO_APK:
        res = crypto_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_UART0:
    case SCLK_UART1:
    case SCLK_UART2:
    case SCLK_UART3:
    case SCLK_UART4:
        rate = uart_set_rate(priv, pdata->id, rate);
    default:
        return -RT_EINVAL;
    }

    return res;
}

static rt_err_t rk_clk_wait_lock(struct rk_clk_platform_data *pdata)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t count = 0, pllcon;

    /*
     * Lock time typical 250, max 500 input clock cycles @24MHz, So define a
     * very safe maximum of 1000us, meaning 24000 cycles.
     */
    do {
        pllcon = HWREG32(pdata->base + PLL_CON(1));
        rt_hw_us_delay(100);
        ++count;
    } while (pllcon & PLLCON1_LOCK_STATUS && count < 10);

    if (count >= 10)
    {
        err = -RT_ETIMEOUT;
    }

    return err;
}

static rt_err_t mac_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;

    /*
     * If the requested parent is in the same clock-controller and
     * the id is SCLK_MAC_SRC, switch to the internal clock.
     */
    if (ppdata->id == SCLK_MAC_SRC)
    {
        LOG_D("MAC switching RMII to %s", "SCLK_MAC");
        rk_clrreg(&cru->clksel_con[43], RT_BIT(14));
    }
    else
    {
        LOG_D("MAC switching RMII to %s", "CLKIN");
        rk_setreg(&cru->clksel_con[43], RT_BIT(14));
    }

    return 0;
}

static rt_err_t rk3308_clk_init(struct rt_clk *clk, void *fw_data)
{
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rt_ofw_cell_args *args = fw_data;
    struct rk_clk_platform_data *pdata;
    rt_uint32_t clk_id = args->args[0];
    rt_ubase_t reg_base;

    pdata = &rk_clk->pdata[clk_id];
    reg_base = (rt_ubase_t)rk_clk->clk_info.cru;

    switch (clk_id)
    {
    case PLL_APLL:
    case ARMCLK:
        reg_base += pll_clks[apll].con_offset;
        break;
    case PLL_DPLL:
        reg_base += pll_clks[dpll].con_offset;
        break;
    case PLL_VPLL0:
        reg_base += pll_clks[vpll0].con_offset;
        break;
    case PLL_VPLL1:
        reg_base += pll_clks[vpll1].con_offset;
        break;
    default:
        reg_base = RT_NULL;
        break;
    }

    pdata->id = clk_id;
    pdata->base = (void *)reg_base;

    clk->rate = rk_clk_get_rate(pdata, rk_clk);
    clk->sysdata = pdata;

    rk_clk_set_default_rates(clk, clk->clk_np->ops->set_rate, clk_id);

    return RT_EOK;
}

static rt_err_t rk3308_clk_enable(struct rt_clk *clk)
{
    struct rk_clk_platform_data *pdata = clk->sysdata;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rk_cru *cru = rk_clk->clk_info.cru;

    if (pdata->base)
    {
        HWREG32(pdata->base + PLL_CON(1)) = HIWORD_UPDATE(0, PLLCON1_PWRDOWN, 0);

        rk_clk_wait_lock(pdata);
    }
    else
    {
        struct rk_clk_gate *gate = &clk_gates[pdata->id];

        rk_clrreg(&cru->clkgate_con[gate->con_idx], RT_BIT(gate->con_bit));
    }

    return RT_EOK;
}

static void rk3308_clk_disable(struct rt_clk *clk)
{
    struct rk_clk_platform_data *pdata = clk->sysdata;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rk_cru *cru = rk_clk->clk_info.cru;

    if (pdata->base)
    {
        HWREG32(pdata->base + PLL_CON(1)) = HIWORD_UPDATE(PLLCON1_PWRDOWN, PLLCON1_PWRDOWN, 0);
    }
    else
    {
        struct rk_clk_gate *gate = &clk_gates[pdata->id];

        rk_setreg(&cru->clkgate_con[gate->con_idx], RT_BIT(gate->con_bit));
    }
}

static rt_bool_t rk3308_clk_is_enabled(struct rt_clk *clk)
{
    struct rk_clk_platform_data *pdata = clk->sysdata;

    if (pdata->base)
    {
        rt_uint32_t pllcon = HWREG32(pdata->base + PLL_CON(1));

        return !(pllcon & PLLCON1_PWRDOWN);
    }

    return RT_TRUE;
}

static rt_err_t rk3308_clk_set_rate(struct rt_clk *clk, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_ubase_t res_rate;
    struct rk_clk_platform_data *pdata = clk->sysdata;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);

    res_rate = rk_clk_set_rate(pdata, rk_clk, rate);

    if ((rt_base_t)res_rate > 0)
    {
        clk->rate = res_rate;
    }

    return (rt_ubase_t)res_rate > 0 ? RT_EOK : (rt_err_t)res_rate;
}

static rt_err_t rk3308_clk_set_parent(struct rt_clk *clk, struct rt_clk *parent)
{
    struct rk_clk_platform_data *pdata = clk->sysdata, *ppdata = parent->sysdata;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);

    switch (pdata->id)
    {
    case SCLK_MAC:
        return mac_set_parent(pdata, ppdata, rk_clk);

    default:
        break;
    }

    return -RT_EINVAL;
}

static const struct rt_clk_ops rk3308_clk_ops =
{
    .init = rk3308_clk_init,
    .enable = rk3308_clk_enable,
    .disable = rk3308_clk_disable,
    .is_enabled = rk3308_clk_is_enabled,
    .set_rate = rk3308_clk_set_rate,
    .set_parent = rk3308_clk_set_parent,
};

static void rk3308_clk_type_init(struct rk_clk *rk_clk, struct rt_ofw_node *np)
{
    rt_ubase_t cpu_freq = APLL_HZ;
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    const char *rockchip_cpu_freq = rt_ofw_bootargs_select("rockchip.cpu_freq=", 0);

    priv->cru = (struct rk_cru *)rk_clk->base;

    if (rockchip_cpu_freq)
    {
        cpu_freq = atol(rockchip_cpu_freq);
    }

    if (rk_pll_get_rate(&pll_clks[apll], priv->cru) != cpu_freq)
    {
        if (armclk_set_clk(priv, cpu_freq) < 0)
        {
            LOG_E("Failed to set armclk rate to %u, error = %s", cpu_freq);
        }
    }

    clk_get_pll_rate(priv);

    bus_set_clk(priv, ACLK_BUS, BUS_ACLK_HZ);
    bus_set_clk(priv, HCLK_BUS, BUS_HCLK_HZ);
    bus_set_clk(priv, PCLK_BUS, BUS_PCLK_HZ);

    peri_set_clk(priv, ACLK_PERI, PERI_ACLK_HZ);
    peri_set_clk(priv, HCLK_PERI, PERI_HCLK_HZ);
    peri_set_clk(priv, PCLK_PERI, PERI_PCLK_HZ);

    audio_set_clk(priv, HCLK_AUDIO, AUDIO_HCLK_HZ);
    audio_set_clk(priv, PCLK_AUDIO, AUDIO_PCLK_HZ);
}

static rt_err_t clk_rk3308_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    void *softrst_regs;
    struct rt_ofw_node *np = pdev->parent.ofw_node;
    struct rk_clk *rk_clk = rt_calloc(1, sizeof(*rk_clk));

    if (!rk_clk)
    {
        return -RT_ENOMEM;
    }

    rk_clk->base = rt_ofw_iomap(np, 0);

    if (!rk_clk->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk3308_clk_type_init(rk_clk, np);
    softrst_regs = &rk_clk->clk_info.cru->softrst_con;

    rk_clk->parent.parent.ops = &rk3308_clk_ops;

    if ((err = rt_clk_register(&rk_clk->parent.parent, RT_NULL)))
    {
        goto _fail;
    }

    if ((err = rk_register_softrst(&rk_clk->parent.rstcer, np,
            softrst_regs, ROCKCHIP_SOFTRST_HIWORD_MASK)))
    {
        goto _fail;
    }

    rt_ofw_data(np) = &rk_clk->parent;

    return RT_EOK;

_fail:
    if (rk_clk->base)
    {
        rt_iounmap(rk_clk->base);
    }

    rt_free(rk_clk);

    return err;
}

static const struct rt_ofw_node_id clk_rk3308_ofw_ids[] =
{
    { .compatible = "rockchip,rk3308-cru", },
    { /* sentinel */ }
};

static struct rt_platform_driver clk_rk3308_driver =
{
    .name = "clk-rk3308",
    .ids = clk_rk3308_ofw_ids,

    .probe = clk_rk3308_probe,
};

static int clk_rk3308_register(void)
{
    rt_platform_driver_register(&clk_rk3308_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(clk_rk3308_register);
