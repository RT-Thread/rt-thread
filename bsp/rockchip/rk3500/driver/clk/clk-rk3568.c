/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk3568.h"

#define DBG_TAG "clk.rk3568"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rk3568-cru.h"

#define APLL_HZ (816 * MHZ)
#define GPLL_HZ (1188 * MHZ)
#define CPLL_HZ (1000 * MHZ)
#define PPLL_HZ (100 * MHZ)

struct rk_pll
{
    rt_uint32_t con0;
    rt_uint32_t con1;
    rt_uint32_t con2;
    rt_uint32_t con3;
    rt_uint32_t con4;
    rt_uint32_t reserved0[3];
};

struct rk_pmucru
{
    struct rk_pll pll[2];
    rt_uint32_t reserved0[16];
    rt_uint32_t mode_con00;
    rt_uint32_t reserved1[31];
    rt_uint32_t pmu_clksel_con[10];
    rt_uint32_t reserved2[22];
    rt_uint32_t pmu_clkgate_con[3];
    rt_uint32_t reserved3[29];
    rt_uint32_t pmu_softrst_con[1];
};

struct rk_cru
{
    struct rk_pll pll[6];
    rt_uint32_t mode_con00;
    rt_uint32_t misc_con[3];
    rt_uint32_t glb_cnt_th;
    rt_uint32_t glb_srst_fst;
    rt_uint32_t glb_srsr_snd;
    rt_uint32_t glb_rst_con;
    rt_uint32_t glb_rst_st;
    rt_uint32_t reserved0[7];
    rt_uint32_t clksel_con[85];
    rt_uint32_t reserved1[43];
    rt_uint32_t clkgate_con[36];
    rt_uint32_t reserved2[28];
    rt_uint32_t softrst_con[30];
    rt_uint32_t reserved3[2];
    rt_uint32_t ssgtbl[32];
    rt_uint32_t reserved4[32];
    rt_uint32_t sdmmc0_con[2];
    rt_uint32_t sdmmc1_con[2];
    rt_uint32_t sdmmc2_con[2];
    rt_uint32_t emmc_con[2];
};

struct rk_pmuclk_priv
{
    struct rk_pmucru *pmucru;
    rt_ubase_t ppll_hz;
    rt_ubase_t hpll_hz;
};

struct rk_clk_priv
{
    struct rk_cru *cru;
    rt_ubase_t ppll_hz;
    rt_ubase_t hpll_hz;
    rt_ubase_t gpll_hz;
    rt_ubase_t cpll_hz;
    rt_ubase_t npll_hz;
    rt_ubase_t vpll_hz;
    rt_ubase_t armclk_hz;
    rt_ubase_t armclk_enter_hz;
    rt_ubase_t armclk_init_hz;
    rt_bool_t sync_kernel;
    rt_bool_t set_armclk_rate;
};

struct rk_clk_platform_data
{
    rt_uint32_t id;
    void *base;
};

enum rk_clk_type
{
    rk_clk_type_clk,
    rk_clk_type_pmuclk,
};

struct rt_reset_controller_clk_node
{
    struct rt_clk_node parent;

    struct rt_reset_controller rstcer;
};

struct rk_clk
{
    struct rt_reset_controller_clk_node parent;

    void *base;
    enum rk_clk_type type;

    union
    {
        struct rk_clk_priv clk_info;
        struct rk_pmuclk_priv pmuclk_info;
    };

    struct rk_clk_platform_data pdata[];
};

#define raw_to_rk_clk(raw) rt_container_of(raw, struct rk_clk, parent)

#define PMU_MODE                0x80
#define PMU_PLL_CON(x)          ((x) * 0x4)
#define PLL_CON(x)              ((x) * 0x4)
#define MODE_CON                0xc0

enum pmu_plls
{
    ppll, hpll,
};

enum plls
{
    apll, dpll, gpll, cpll, npll, vpll,
};

enum
{
    /* CRU_PMU_CLK_SEL0_CON */
    RTC32K_SEL_SHIFT                = 6,
    RTC32K_SEL_MASK                 = 0x3 << RTC32K_SEL_SHIFT,
    RTC32K_SEL_PMUPVTM              = 0,
    RTC32K_SEL_OSC1_32K,
    RTC32K_SEL_OSC0_DIV32K,

    /* CRU_PMU_CLK_SEL1_CON */
    RTC32K_FRAC_NUMERATOR_SHIFT     = 16,
    RTC32K_FRAC_NUMERATOR_MASK      = 0xffff << 16,
    RTC32K_FRAC_DENOMINATOR_SHIFT   = 0,
    RTC32K_FRAC_DENOMINATOR_MASK    = 0xffff,

    /* CRU_PMU_CLK_SEL2_CON */
    PCLK_PDPMU_SEL_SHIFT            = 15,
    PCLK_PDPMU_SEL_MASK             = 1 << PCLK_PDPMU_SEL_SHIFT,
    PCLK_PDPMU_SEL_PPLL             = 0,
    PCLK_PDPMU_SEL_GPLL,
    PCLK_PDPMU_DIV_SHIFT            = 0,
    PCLK_PDPMU_DIV_MASK             = 0x1f,

    /* CRU_PMU_CLK_SEL3_CON */
    CLK_I2C0_DIV_SHIFT              = 0,
    CLK_I2C0_DIV_MASK               = 0x7f,

    /* PMUCRU_PMUCLKSEL_CON04 */
    CLK_UART0_SEL_SHIFT             = 10,
    CLK_UART0_SEL_MASK              = 0x3 << CLK_UART0_SEL_SHIFT,
    CLK_UART0_SEL_DIV               = 0,
    CLK_UART0_SEL_FRACDIV,
    CLK_UART0_SEL_XIN24M,
    CLK_UART0_DIV_SEL_SHIFT         = 8,
    CLK_UART0_DIV_SEL_MASK          = 0x3 << CLK_UART0_DIV_SEL_SHIFT,
    CLK_UART0_SRC_SEL_PPLL          = 0,
    CLK_UART0_SRC_SEL_480M,
    CLK_UART0_SRC_SEL_CPLL,
    CLK_UART0_SRC_SEL_GPLL,
    CLK_UART0_DIV_DIV_SHIFT         = 0,
    CLK_UART0_DIV_DIV_MASK          = 0x3f << CLK_UART0_DIV_DIV_SHIFT,

    /* PMUCRU_PMUCLKSEL_CON05 */
    CLK_UART0_FRAC_NUMERATOR_SHIFT  = 16,
    CLK_UART0_FRAC_NUMERATOR_MASK   = 0xffff << 16,
    CLK_UART0_FRAC_DENOMINATOR_SHIFT= 0,
    CLK_UART0_FRAC_DENOMINATOR_MASK = 0xffff,

    /* PMUCRU_PMUCLKSEL_CON09 */
    CLK_PCIE_PHY2_REF_SEL_SHIFT     = 11,
    CLK_PCIE_PHY2_REF_SEL_MASK      = 1 << CLK_PCIE_PHY2_REF_SEL_SHIFT,
    CLK_PCIE_PHY1_REF_SEL_SHIFT     = 7,
    CLK_PCIE_PHY1_REF_SEL_MASK      = 1 << CLK_PCIE_PHY1_REF_SEL_SHIFT,
    CLK_PCIE_PHY0_REF_SEL_SHIFT     = 3,
    CLK_PCIE_PHY0_REF_SEL_MASK      = 1 << CLK_PCIE_PHY0_REF_SEL_SHIFT,
    CLK_PCIE_PHY_REF_SEL_24M        = 0,
    CLK_PCIE_PHY_REF_SEL_PPLL,
    CLK_PCIE_PHY2_PLL_DIV_SHIFT     = 8,
    CLK_PCIE_PHY2_PLL_DIV_MASK      = 7 << CLK_PCIE_PHY2_PLL_DIV_SHIFT,
    CLK_PCIE_PHY1_PLL_DIV_SHIFT     = 4,
    CLK_PCIE_PHY1_PLL_DIV_MASK      = 7 << CLK_PCIE_PHY1_PLL_DIV_SHIFT,
    CLK_PCIE_PHY0_PLL_DIV_SHIFT     = 0,
    CLK_PCIE_PHY0_PLL_DIV_MASK      = 7 << CLK_PCIE_PHY0_PLL_DIV_SHIFT,

    /* CRU_PMU_CLK_SEL6_CON */
    CLK_PWM0_SEL_SHIFT              = 7,
    CLK_PWM0_SEL_MASK               = 1 << CLK_PWM0_SEL_SHIFT,
    CLK_PWM0_SEL_XIN24M             = 0,
    CLK_PWM0_SEL_PPLL,
    CLK_PWM0_DIV_SHIFT              = 0,
    CLK_PWM0_DIV_MASK               = 0x7f,

    /* CRU_CLK_SEL0_CON */
    CLK_CORE_PRE_SEL_SHIFT          = 7,
    CLK_CORE_PRE_SEL_MASK           = 1 << CLK_CORE_PRE_SEL_SHIFT,
    CLK_CORE_PRE_SEL_SRC            = 0,
    CLK_CORE_PRE_SEL_APLL,

    /* CRU_CLK_SEL2_CON */
    SCLK_CORE_PRE_SEL_SHIFT         = 15,
    SCLK_CORE_PRE_SEL_MASK          = 1 << SCLK_CORE_PRE_SEL_SHIFT,
    SCLK_CORE_PRE_SEL_SRC           = 0,
    SCLK_CORE_PRE_SEL_NPLL,
    SCLK_CORE_SRC_SEL_SHIFT         = 8,
    SCLK_CORE_SRC_SEL_MASK          = 3 << SCLK_CORE_SRC_SEL_SHIFT,
    SCLK_CORE_SRC_SEL_APLL          = 0,
    SCLK_CORE_SRC_SEL_GPLL,
    SCLK_CORE_SRC_SEL_NPLL,
    SCLK_CORE_SRC_DIV_SHIFT         = 0,
    SCLK_CORE_SRC_DIV_MASK          = 0x1f << SCLK_CORE_SRC_DIV_SHIFT,

    /* CRU_CLK_SEL3_CON */
    GICCLK_CORE_DIV_SHIFT           = 8,
    GICCLK_CORE_DIV_MASK            = 0x1f << GICCLK_CORE_DIV_SHIFT,
    ATCLK_CORE_DIV_SHIFT            = 0,
    ATCLK_CORE_DIV_MASK             = 0x1f << ATCLK_CORE_DIV_SHIFT,

    /* CRU_CLK_SEL4_CON */
    PERIPHCLK_CORE_PRE_DIV_SHIFT    = 8,
    PERIPHCLK_CORE_PRE_DIV_MASK     = 0x1f << PERIPHCLK_CORE_PRE_DIV_SHIFT,
    PCLK_CORE_PRE_DIV_SHIFT         = 0,
    PCLK_CORE_PRE_DIV_MASK          = 0x1f << PCLK_CORE_PRE_DIV_SHIFT,

    /* CRU_CLK_SEL5_CON */
    ACLK_CORE_NIU2BUS_SEL_SHIFT     = 14,
    ACLK_CORE_NIU2BUS_SEL_MASK      = 0x3 << ACLK_CORE_NIU2BUS_SEL_SHIFT,
    ACLK_CORE_NDFT_DIV_SHIFT        = 8,
    ACLK_CORE_NDFT_DIV_MASK         = 0x1f << ACLK_CORE_NDFT_DIV_SHIFT,

    /* CRU_CLK_SEL10_CON */
    HCLK_PERIMID_SEL_SHIFT          = 6,
    HCLK_PERIMID_SEL_MASK           = 3 << HCLK_PERIMID_SEL_SHIFT,
    HCLK_PERIMID_SEL_150M           = 0,
    HCLK_PERIMID_SEL_100M,
    HCLK_PERIMID_SEL_75M,
    HCLK_PERIMID_SEL_24M,
    ACLK_PERIMID_SEL_SHIFT          = 4,
    ACLK_PERIMID_SEL_MASK           = 3 << ACLK_PERIMID_SEL_SHIFT,
    ACLK_PERIMID_SEL_300M           = 0,
    ACLK_PERIMID_SEL_200M,
    ACLK_PERIMID_SEL_100M,
    ACLK_PERIMID_SEL_24M,

    /* CRU_CLK_SEL27_CON */
    CLK_CRYPTO_PKA_SEL_SHIFT        = 6,
    CLK_CRYPTO_PKA_SEL_MASK         = 3 << CLK_CRYPTO_PKA_SEL_SHIFT,
    CLK_CRYPTO_PKA_SEL_300M         = 0,
    CLK_CRYPTO_PKA_SEL_200M,
    CLK_CRYPTO_PKA_SEL_100M,
    CLK_CRYPTO_CORE_SEL_SHIFT       = 4,
    CLK_CRYPTO_CORE_SEL_MASK        = 3 << CLK_CRYPTO_CORE_SEL_SHIFT,
    CLK_CRYPTO_CORE_SEL_200M        = 0,
    CLK_CRYPTO_CORE_SEL_150M,
    CLK_CRYPTO_CORE_SEL_100M,
    HCLK_SECURE_FLASH_SEL_SHIFT     = 2,
    HCLK_SECURE_FLASH_SEL_MASK      = 3 << HCLK_SECURE_FLASH_SEL_SHIFT,
    HCLK_SECURE_FLASH_SEL_150M      = 0,
    HCLK_SECURE_FLASH_SEL_100M,
    HCLK_SECURE_FLASH_SEL_75M,
    HCLK_SECURE_FLASH_SEL_24M,
    ACLK_SECURE_FLASH_SEL_SHIFT     = 0,
    ACLK_SECURE_FLASH_SEL_MASK      = 3 << ACLK_SECURE_FLASH_SEL_SHIFT,
    ACLK_SECURE_FLASH_SEL_200M      = 0,
    ACLK_SECURE_FLASH_SEL_150M,
    ACLK_SECURE_FLASH_SEL_100M,
    ACLK_SECURE_FLASH_SEL_24M,

    /* CRU_CLK_SEL28_CON */
    CCLK_EMMC_SEL_SHIFT             = 12,
    CCLK_EMMC_SEL_MASK              = 7 << CCLK_EMMC_SEL_SHIFT,
    CCLK_EMMC_SEL_24M               = 0,
    CCLK_EMMC_SEL_200M,
    CCLK_EMMC_SEL_150M,
    CCLK_EMMC_SEL_100M,
    CCLK_EMMC_SEL_50M,
    CCLK_EMMC_SEL_375K,
    BCLK_EMMC_SEL_SHIFT             = 8,
    BCLK_EMMC_SEL_MASK              = 3 << BCLK_EMMC_SEL_SHIFT,
    BCLK_EMMC_SEL_200M              = 0,
    BCLK_EMMC_SEL_150M,
    BCLK_EMMC_SEL_125M,
    SCLK_SFC_SEL_SHIFT              = 4,
    SCLK_SFC_SEL_MASK               = 7 << SCLK_SFC_SEL_SHIFT,
    SCLK_SFC_SEL_24M                = 0,
    SCLK_SFC_SEL_50M,
    SCLK_SFC_SEL_75M,
    SCLK_SFC_SEL_100M,
    SCLK_SFC_SEL_125M,
    SCLK_SFC_SEL_150M,
    NCLK_NANDC_SEL_SHIFT            = 0,
    NCLK_NANDC_SEL_MASK             = 3 << NCLK_NANDC_SEL_SHIFT,
    NCLK_NANDC_SEL_200M             = 0,
    NCLK_NANDC_SEL_150M,
    NCLK_NANDC_SEL_100M,
    NCLK_NANDC_SEL_24M,

    /* CRU_CLK_SEL30_CON */
    CLK_SDMMC1_SEL_SHIFT            = 12,
    CLK_SDMMC1_SEL_MASK             = 7 << CLK_SDMMC1_SEL_SHIFT,
    CLK_SDMMC0_SEL_SHIFT            = 8,
    CLK_SDMMC0_SEL_MASK             = 7 << CLK_SDMMC0_SEL_SHIFT,
    CLK_SDMMC_SEL_24M               = 0,
    CLK_SDMMC_SEL_400M,
    CLK_SDMMC_SEL_300M,
    CLK_SDMMC_SEL_100M,
    CLK_SDMMC_SEL_50M,
    CLK_SDMMC_SEL_750K,

    /* CRU_CLK_SEL31_CON */
    CLK_MAC0_OUT_SEL_SHIFT          = 14,
    CLK_MAC0_OUT_SEL_MASK           = 3 << CLK_MAC0_OUT_SEL_SHIFT,
    CLK_MAC0_OUT_SEL_125M           = 0,
    CLK_MAC0_OUT_SEL_50M,
    CLK_MAC0_OUT_SEL_25M,
    CLK_MAC0_OUT_SEL_24M,
    CLK_GMAC0_PTP_REF_SEL_SHIFT     = 12,
    CLK_GMAC0_PTP_REF_SEL_MASK      = 3 << CLK_GMAC0_PTP_REF_SEL_SHIFT,
    CLK_GMAC0_PTP_REF_SEL_62_5M     = 0,
    CLK_GMAC0_PTP_REF_SEL_100M,
    CLK_GMAC0_PTP_REF_SEL_50M,
    CLK_GMAC0_PTP_REF_SEL_24M,
    CLK_MAC0_2TOP_SEL_SHIFT         = 8,
    CLK_MAC0_2TOP_SEL_MASK          = 3 << CLK_MAC0_2TOP_SEL_SHIFT,
    CLK_MAC0_2TOP_SEL_125M          = 0,
    CLK_MAC0_2TOP_SEL_50M,
    CLK_MAC0_2TOP_SEL_25M,
    CLK_MAC0_2TOP_SEL_PPLL,
    RGMII0_CLK_SEL_SHIFT            = 4,
    RGMII0_CLK_SEL_MASK             = 3 << RGMII0_CLK_SEL_SHIFT,
    RGMII0_CLK_SEL_125M             = 0,
    RGMII0_CLK_SEL_125M_1,
    RGMII0_CLK_SEL_2_5M,
    RGMII0_CLK_SEL_25M,
    RMII0_CLK_SEL_SHIFT             = 3,
    RMII0_CLK_SEL_MASK              = 1 << RMII0_CLK_SEL_SHIFT,
    RMII0_CLK_SEL_2_5M              = 0,
    RMII0_CLK_SEL_25M,
    RMII0_EXTCLK_SEL_SHIFT          = 2,
    RMII0_EXTCLK_SEL_MASK           = 1 << RMII0_EXTCLK_SEL_SHIFT,
    RMII0_EXTCLK_SEL_MAC0_TOP       = 0,
    RMII0_EXTCLK_SEL_IO,
    RMII0_MODE_SHIFT                = 0,
    RMII0_MODE_MASK                 = 3 << RMII0_MODE_SHIFT,
    RMII0_MODE_SEL_RGMII            = 0,
    RMII0_MODE_SEL_RMII,
    RMII0_MODE_SEL_GMII,

    /* CRU_CLK_SEL32_CON */
    CLK_SDMMC2_SEL_SHIFT            = 8,
    CLK_SDMMC2_SEL_MASK             = 7 << CLK_SDMMC2_SEL_SHIFT,

    /* CRU_CLK_SEL38_CON */
    ACLK_VOP_PRE_SEL_SHIFT          = 6,
    ACLK_VOP_PRE_SEL_MASK           = 3 << ACLK_VOP_PRE_SEL_SHIFT,
    ACLK_VOP_PRE_SEL_CPLL           = 0,
    ACLK_VOP_PRE_SEL_GPLL,
    ACLK_VOP_PRE_SEL_HPLL,
    ACLK_VOP_PRE_SEL_VPLL,
    ACLK_VOP_PRE_DIV_SHIFT          = 0,
    ACLK_VOP_PRE_DIV_MASK           = 0x1f << ACLK_VOP_PRE_DIV_SHIFT,

    /* CRU_CLK_SEL39_CON */
    DCLK0_VOP_SEL_SHIFT             = 10,
    DCLK0_VOP_SEL_MASK              = 3 << DCLK0_VOP_SEL_SHIFT,
    DCLK_VOP_SEL_HPLL               = 0,
    DCLK_VOP_SEL_VPLL,
    DCLK_VOP_SEL_GPLL,
    DCLK_VOP_SEL_CPLL,
    DCLK0_VOP_DIV_SHIFT             = 0,
    DCLK0_VOP_DIV_MASK              = 0xff << DCLK0_VOP_DIV_SHIFT,

    /* CRU_CLK_SEL40_CON */
    DCLK1_VOP_SEL_SHIFT             = 10,
    DCLK1_VOP_SEL_MASK              = 3 << DCLK1_VOP_SEL_SHIFT,
    DCLK1_VOP_DIV_SHIFT             = 0,
    DCLK1_VOP_DIV_MASK              = 0xff << DCLK1_VOP_DIV_SHIFT,

    /* CRU_CLK_SEL41_CON */
    DCLK2_VOP_SEL_SHIFT             = 10,
    DCLK2_VOP_SEL_MASK              = 3 << DCLK2_VOP_SEL_SHIFT,
    DCLK2_VOP_DIV_SHIFT             = 0,
    DCLK2_VOP_DIV_MASK              = 0xff << DCLK2_VOP_DIV_SHIFT,

    /* CRU_CLK_SEL43_CON */
    DCLK_EBC_SEL_SHIFT              = 6,
    DCLK_EBC_SEL_MASK               = 3 << DCLK_EBC_SEL_SHIFT,
    DCLK_EBC_SEL_GPLL_400M          = 0,
    DCLK_EBC_SEL_CPLL_333M,
    DCLK_EBC_SEL_GPLL_200M,

    /* CRU_CLK_SEL47_CON */
    ACLK_RKVDEC_SEL_SHIFT           = 7,
    ACLK_RKVDEC_SEL_MASK            = 1 << ACLK_RKVDEC_SEL_SHIFT,
    ACLK_RKVDEC_SEL_GPLL            = 0,
    ACLK_RKVDEC_SEL_CPLL,
    ACLK_RKVDEC_DIV_SHIFT           = 0,
    ACLK_RKVDEC_DIV_MASK            = 0x1f << ACLK_RKVDEC_DIV_SHIFT,

    /* CRU_CLK_SEL49_CON */
    CLK_RKVDEC_CORE_SEL_SHIFT       = 14,
    CLK_RKVDEC_CORE_SEL_MASK        = 0x3 << CLK_RKVDEC_CORE_SEL_SHIFT,
    CLK_RKVDEC_CORE_SEL_GPLL        = 0,
    CLK_RKVDEC_CORE_SEL_CPLL,
    CLK_RKVDEC_CORE_SEL_NPLL,
    CLK_RKVDEC_CORE_SEL_VPLL,
    CLK_RKVDEC_CORE_DIV_SHIFT       = 8,
    CLK_RKVDEC_CORE_DIV_MASK        = 0x1f << CLK_RKVDEC_CORE_DIV_SHIFT,

    /* CRU_CLK_SEL50_CON */
    PCLK_BUS_SEL_SHIFT              = 4,
    PCLK_BUS_SEL_MASK               = 3 << PCLK_BUS_SEL_SHIFT,
    PCLK_BUS_SEL_100M               = 0,
    PCLK_BUS_SEL_75M,
    PCLK_BUS_SEL_50M,
    PCLK_BUS_SEL_24M,
    ACLK_BUS_SEL_SHIFT              = 0,
    ACLK_BUS_SEL_MASK               = 3 << ACLK_BUS_SEL_SHIFT,
    ACLK_BUS_SEL_200M               = 0,
    ACLK_BUS_SEL_150M,
    ACLK_BUS_SEL_100M,
    ACLK_BUS_SEL_24M,

    /* CRU_CLK_SEL51_CON */
    CLK_TSADC_DIV_SHIFT             = 8,
    CLK_TSADC_DIV_MASK              = 0x7f << CLK_TSADC_DIV_SHIFT,
    CLK_TSADC_TSEN_SEL_SHIFT        = 4,
    CLK_TSADC_TSEN_SEL_MASK         = 0x3 << CLK_TSADC_TSEN_SEL_SHIFT,
    CLK_TSADC_TSEN_SEL_24M          = 0,
    CLK_TSADC_TSEN_SEL_100M,
    CLK_TSADC_TSEN_SEL_CPLL_100M,
    CLK_TSADC_TSEN_DIV_SHIFT        = 0,
    CLK_TSADC_TSEN_DIV_MASK         = 0x7 << CLK_TSADC_TSEN_DIV_SHIFT,

    /* CRU_CLK_SEL52_CON */
    CLK_UART_SEL_SHIFT              = 12,
    CLK_UART_SEL_MASK               = 0x3 << CLK_UART_SEL_SHIFT,
    CLK_UART_SEL_SRC                = 0,
    CLK_UART_SEL_FRAC,
    CLK_UART_SEL_XIN24M,
    CLK_UART_SRC_SEL_SHIFT          = 8,
    CLK_UART_SRC_SEL_MASK           = 0x3 << CLK_UART_SRC_SEL_SHIFT,
    CLK_UART_SRC_SEL_GPLL           = 0,
    CLK_UART_SRC_SEL_CPLL,
    CLK_UART_SRC_SEL_480M,
    CLK_UART_SRC_DIV_SHIFT          = 0,
    CLK_UART_SRC_DIV_MASK           = 0x3f << CLK_UART_SRC_DIV_SHIFT,

    /* CRU_CLK_SEL53_CON */
    CLK_UART_FRAC_NUMERATOR_SHIFT   = 16,
    CLK_UART_FRAC_NUMERATOR_MASK    = 0xffff << 16,
    CLK_UART_FRAC_DENOMINATOR_SHIFT = 0,
    CLK_UART_FRAC_DENOMINATOR_MASK  = 0xffff,

    /* CRU_CLK_SEL71_CON */
    CLK_I2C_SEL_SHIFT               = 8,
    CLK_I2C_SEL_MASK                = 3 << CLK_I2C_SEL_SHIFT,
    CLK_I2C_SEL_200M                = 0,
    CLK_I2C_SEL_100M,
    CLK_I2C_SEL_24M,
    CLK_I2C_SEL_CPLL_100M,

    /* CRU_CLK_SEL72_CON */
    CLK_PWM3_SEL_SHIFT              = 12,
    CLK_PWM3_SEL_MASK               = 3 << CLK_PWM3_SEL_SHIFT,
    CLK_PWM2_SEL_SHIFT              = 10,
    CLK_PWM2_SEL_MASK               = 3 << CLK_PWM2_SEL_SHIFT,
    CLK_PWM1_SEL_SHIFT              = 8,
    CLK_PWM1_SEL_MASK               = 3 << CLK_PWM1_SEL_SHIFT,
    CLK_PWM_SEL_100M                = 0,
    CLK_PWM_SEL_24M,
    CLK_PWM_SEL_CPLL_100M,
    CLK_SPI3_SEL_SHIFT              = 6,
    CLK_SPI3_SEL_MASK               = 3 << CLK_SPI3_SEL_SHIFT,
    CLK_SPI2_SEL_SHIFT              = 4,
    CLK_SPI2_SEL_MASK               = 3 << CLK_SPI2_SEL_SHIFT,
    CLK_SPI1_SEL_SHIFT              = 2,
    CLK_SPI1_SEL_MASK               = 3 << CLK_SPI1_SEL_SHIFT,
    CLK_SPI0_SEL_SHIFT              = 0,
    CLK_SPI0_SEL_MASK               = 3 << CLK_SPI0_SEL_SHIFT,
    CLK_SPI_SEL_200M                = 0,
    CLK_SPI_SEL_24M,
    CLK_SPI_SEL_CPLL_100M,

    /* CRU_CLK_SEL73_CON */
    PCLK_TOP_SEL_SHIFT              = 12,
    PCLK_TOP_SEL_MASK               = 3 << PCLK_TOP_SEL_SHIFT,
    PCLK_TOP_SEL_100M               = 0,
    PCLK_TOP_SEL_75M,
    PCLK_TOP_SEL_50M,
    PCLK_TOP_SEL_24M,
    HCLK_TOP_SEL_SHIFT              = 8,
    HCLK_TOP_SEL_MASK               = 3 << HCLK_TOP_SEL_SHIFT,
    HCLK_TOP_SEL_150M               = 0,
    HCLK_TOP_SEL_100M,
    HCLK_TOP_SEL_75M,
    HCLK_TOP_SEL_24M,
    ACLK_TOP_LOW_SEL_SHIFT          = 4,
    ACLK_TOP_LOW_SEL_MASK           = 3 << ACLK_TOP_LOW_SEL_SHIFT,
    ACLK_TOP_LOW_SEL_400M           = 0,
    ACLK_TOP_LOW_SEL_300M,
    ACLK_TOP_LOW_SEL_200M,
    ACLK_TOP_LOW_SEL_24M,
    ACLK_TOP_HIGH_SEL_SHIFT         = 0,
    ACLK_TOP_HIGH_SEL_MASK          = 3 << ACLK_TOP_HIGH_SEL_SHIFT,
    ACLK_TOP_HIGH_SEL_500M          = 0,
    ACLK_TOP_HIGH_SEL_400M,
    ACLK_TOP_HIGH_SEL_300M,
    ACLK_TOP_HIGH_SEL_24M,

    /* CRU_CLK_SEL78_CON */
    CPLL_500M_DIV_SHIFT             = 8,
    CPLL_500M_DIV_MASK              = 0x1f << CPLL_500M_DIV_SHIFT,

    /* CRU_CLK_SEL79_CON */
    CPLL_250M_DIV_SHIFT             = 8,
    CPLL_250M_DIV_MASK              = 0x1f << CPLL_250M_DIV_SHIFT,
    CPLL_333M_DIV_SHIFT             = 0,
    CPLL_333M_DIV_MASK              = 0x1f << CPLL_333M_DIV_SHIFT,

    /* CRU_CLK_SEL80_CON */
    CPLL_62P5M_DIV_SHIFT            = 8,
    CPLL_62P5M_DIV_MASK             = 0x1f << CPLL_62P5M_DIV_SHIFT,
    CPLL_125M_DIV_SHIFT             = 0,
    CPLL_125M_DIV_MASK              = 0x1f << CPLL_125M_DIV_SHIFT,

    /* CRU_CLK_SEL81_CON */
    CPLL_25M_DIV_SHIFT              = 8,
    CPLL_25M_DIV_MASK               = 0x1f << CPLL_25M_DIV_SHIFT,
    CPLL_50M_DIV_SHIFT              = 0,
    CPLL_50M_DIV_MASK               = 0x1f << CPLL_50M_DIV_SHIFT,

    /* CRU_CLK_SEL82_CON */
    CPLL_100M_DIV_SHIFT             = 0,
    CPLL_100M_DIV_MASK              = 0x1f << CPLL_100M_DIV_SHIFT,
};

static struct rk_cpu_rate_table cpu_rates[] =
{
    CPUCLK_RATE(1800000000, 1, 7),
    CPUCLK_RATE(1704000000, 1, 7),
    CPUCLK_RATE(1608000000, 1, 5),
    CPUCLK_RATE(1584000000, 1, 5),
    CPUCLK_RATE(1560000000, 1, 5),
    CPUCLK_RATE(1536000000, 1, 5),
    CPUCLK_RATE(1512000000, 1, 5),
    CPUCLK_RATE(1488000000, 1, 5),
    CPUCLK_RATE(1464000000, 1, 5),
    CPUCLK_RATE(1440000000, 1, 5),
    CPUCLK_RATE(1416000000, 1, 5),
    CPUCLK_RATE(1392000000, 1, 5),
    CPUCLK_RATE(1368000000, 1, 5),
    CPUCLK_RATE(1344000000, 1, 5),
    CPUCLK_RATE(1320000000, 1, 5),
    CPUCLK_RATE(1296000000, 1, 5),
    CPUCLK_RATE(1272000000, 1, 5),
    CPUCLK_RATE(1248000000, 1, 5),
    CPUCLK_RATE(1224000000, 1, 5),
    CPUCLK_RATE(1200000000, 1, 3),
    CPUCLK_RATE(1104000000, 1, 3),
    CPUCLK_RATE(1008000000, 1, 3),
    CPUCLK_RATE(912000000,  1, 3),
    CPUCLK_RATE(816000000,  1, 3),
    CPUCLK_RATE(696000000,  1, 3),
    CPUCLK_RATE(600000000,  1, 3),
    CPUCLK_RATE(408000000,  1, 3),
    CPUCLK_RATE(312000000,  1, 3),
    CPUCLK_RATE(216000000,  1, 3),
    CPUCLK_RATE(96000000,   1, 3),
    { /* sentinel */ },
};

static struct rk_pll_rate_table pll_rates[] =
{
    /* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
    PLL_RATE(2208000000, 1,  92, 1, 1, 1, 0),
    PLL_RATE(2184000000, 1,  91, 1, 1, 1, 0),
    PLL_RATE(2160000000, 1,  90, 1, 1, 1, 0),
    PLL_RATE(2088000000, 1,  87, 1, 1, 1, 0),
    PLL_RATE(2064000000, 1,  86, 1, 1, 1, 0),
    PLL_RATE(2040000000, 1,  85, 1, 1, 1, 0),
    PLL_RATE(2016000000, 1,  84, 1, 1, 1, 0),
    PLL_RATE(1992000000, 1,  83, 1, 1, 1, 0),
    PLL_RATE(1920000000, 1,  80, 1, 1, 1, 0),
    PLL_RATE(1896000000, 1,  79, 1, 1, 1, 0),
    PLL_RATE(1800000000, 1,  75, 1, 1, 1, 0),
    PLL_RATE(1704000000, 1,  71, 1, 1, 1, 0),
    PLL_RATE(1608000000, 1,  67, 1, 1, 1, 0),
    PLL_RATE(1600000000, 3, 200, 1, 1, 1, 0),
    PLL_RATE(1584000000, 1, 132, 2, 1, 1, 0),
    PLL_RATE(1560000000, 1, 130, 2, 1, 1, 0),
    PLL_RATE(1536000000, 1, 128, 2, 1, 1, 0),
    PLL_RATE(1512000000, 1, 126, 2, 1, 1, 0),
    PLL_RATE(1488000000, 1, 124, 2, 1, 1, 0),
    PLL_RATE(1464000000, 1, 122, 2, 1, 1, 0),
    PLL_RATE(1440000000, 1, 120, 2, 1, 1, 0),
    PLL_RATE(1416000000, 1, 118, 2, 1, 1, 0),
    PLL_RATE(1400000000, 3, 350, 2, 1, 1, 0),
    PLL_RATE(1392000000, 1, 116, 2, 1, 1, 0),
    PLL_RATE(1368000000, 1, 114, 2, 1, 1, 0),
    PLL_RATE(1344000000, 1, 112, 2, 1, 1, 0),
    PLL_RATE(1320000000, 1, 110, 2, 1, 1, 0),
    PLL_RATE(1296000000, 1, 108, 2, 1, 1, 0),
    PLL_RATE(1272000000, 1, 106, 2, 1, 1, 0),
    PLL_RATE(1248000000, 1, 104, 2, 1, 1, 0),
    PLL_RATE(1200000000, 1, 100, 2, 1, 1, 0),
    PLL_RATE(1188000000, 1,  99, 2, 1, 1, 0),
    PLL_RATE(1104000000, 1,  92, 2, 1, 1, 0),
    PLL_RATE(1100000000, 3, 275, 2, 1, 1, 0),
    PLL_RATE(1008000000, 1,  84, 2, 1, 1, 0),
    PLL_RATE(1000000000, 3, 250, 2, 1, 1, 0),
    PLL_RATE(912000000,  1,  76, 2, 1, 1, 0),
    PLL_RATE(816000000,  1,  68, 2, 1, 1, 0),
    PLL_RATE(800000000,  3, 200, 2, 1, 1, 0),
    PLL_RATE(700000000,  3, 350, 4, 1, 1, 0),
    PLL_RATE(696000000,  1, 116, 4, 1, 1, 0),
    PLL_RATE(600000000,  1, 100, 4, 1, 1, 0),
    PLL_RATE(594000000,  1,  99, 4, 1, 1, 0),
    PLL_RATE(500000000,  1, 125, 6, 1, 1, 0),
    PLL_RATE(408000000,  1,  68, 2, 2, 1, 0),
    PLL_RATE(312000000,  1,  78, 6, 1, 1, 0),
    PLL_RATE(297000000,  2,  99, 4, 1, 1, 0),
    PLL_RATE(241500000,  2, 161, 4, 2, 1, 0),
    PLL_RATE(216000000,  1,  72, 4, 2, 1, 0),
    PLL_RATE(200000000,  1, 100, 3, 4, 1, 0),
    PLL_RATE(148500000,  1,  99, 4, 4, 1, 0),
    PLL_RATE(135000000,  2,  45, 4, 1, 1, 0),
    PLL_RATE(119000000,  3, 119, 4, 2, 1, 0),
    PLL_RATE(108000000,  2,  45, 5, 1, 1, 0),
    PLL_RATE(100000000,  1, 150, 6, 6, 1, 0),
    PLL_RATE(96000000,   1,  96, 6, 4, 1, 0),
    PLL_RATE(78750000,   1,  96, 6, 4, 1, 0),
    PLL_RATE(74250000,   2,  99, 4, 4, 1, 0),
    { /* sentinel */ },
};

static struct rk_pll_clock pmu_pll_clks[] =
{
    [ppll] = PLL(PLL_PPLL, PMU_PLL_CON(0), PMU_MODE, 0, 10, 0, pll_rates),
    [hpll] = PLL(PLL_HPLL, PMU_PLL_CON(16), PMU_MODE, 2, 10, 0, pll_rates),
};

static struct rk_pll_clock pll_clks[] =
{
    [apll] = PLL(PLL_APLL, PLL_CON(0),  MODE_CON,  0, 10, 0, pll_rates),
    [dpll] = PLL(PLL_DPLL, PLL_CON(8),  MODE_CON,  2, 10, 0, RT_NULL),
    [gpll] = PLL(PLL_HPLL, PLL_CON(16), MODE_CON,  6, 10, 0, pll_rates),
    [cpll] = PLL(PLL_CPLL, PLL_CON(24), MODE_CON,  4, 10, 0, pll_rates),
    [npll] = PLL(PLL_NPLL, PLL_CON(32), MODE_CON, 10, 10, 0, pll_rates),
    [vpll] = PLL(PLL_VPLL, PLL_CON(40), MODE_CON, 12, 10, 0, pll_rates),
};

static struct rk_clk_gate clk_gates[] =
{
    /* CRU_GATE_CON00 */
    /* CRU_GATE_CON01 */
    GATE(PCLK_CORE_PVTM, "pclk_core_pvtm", "pclk_core_pre", 1, 9),
    GATE(CLK_CORE_PVTM, "clk_core_pvtm", "xin24m", 1, 10),
    GATE(CLK_CORE_PVTM_CORE, "clk_core_pvtm_core", "armclk", 1, 11),
    GATE(CLK_CORE_PVTPLL, "clk_core_pvtpll", "armclk", 1, 12),
    /* CRU_GATE_CON02 */
    GATE(CLK_GPU_SRC, "clk_gpu_src", "clk_gpu_pre_c", 2, 0),
    GATE(PCLK_GPU_PRE, "pclk_gpu_pre", "pclk_gpu_pre_div", 2, 2),
    GATE(CLK_GPU, "clk_gpu", "clk_gpu_pre_c", 2, 3),
    GATE(PCLK_GPU_PVTM, "pclk_gpu_pvtm", "pclk_gpu_pre", 2, 6),
    GATE(CLK_GPU_PVTM, "clk_gpu_pvtm", "xin24m", 2, 7),
    GATE(CLK_GPU_PVTM_CORE, "clk_gpu_pvtm_core", "clk_gpu_src", 2, 8),
    GATE(CLK_GPU_PVTPLL, "clk_gpu_pvtpll", "clk_gpu_src", 2, 9),
    GATE(ACLK_GPU_PRE, "aclk_gpu_pre", "aclk_gpu_pre_div", 2, 11),
    /* CRU_GATE_CON03 */
    GATE(CLK_NPU_SRC, "clk_npu_src", "clk_npu_src_c", 3, 0),
    GATE(CLK_NPU_NP5, "clk_npu_np5", "clk_npu_np5_c", 3, 1),
    GATE(HCLK_NPU_PRE, "hclk_npu_pre", "hclk_npu_pre_div", 3, 2),
    GATE(PCLK_NPU_PRE, "pclk_npu_pre", "pclk_npu_pre_div", 3, 3),
    GATE(ACLK_NPU_PRE, "aclk_npu_pre", "clk_npu", 3, 4),
    GATE(ACLK_NPU, "aclk_npu", "aclk_npu_pre", 3, 7),
    GATE(HCLK_NPU, "hclk_npu", "hclk_npu_pre", 3, 8),
    GATE(PCLK_NPU_PVTM, "pclk_npu_pvtm", "pclk_npu_pre", 3, 9),
    GATE(CLK_NPU_PVTM, "clk_npu_pvtm", "xin24m", 3, 10),
    GATE(CLK_NPU_PVTM_CORE, "clk_npu_pvtm_core", "clk_npu_pre_ndft", 3, 11),
    GATE(CLK_NPU_PVTPLL, "clk_npu_pvtpll", "clk_npu_pre_ndft", 3, 12),
    /* CRU_GATE_CON04 */
    GATE(CLK_DDRPHY1X_SRC, "clk_ddrphy1x_src", "clk_ddrphy1x_src_c", 4, 0),
    GATE(CLK_MSCH, "clk_msch", "clk_msch_div", 4, 2),
    GATE(CLK24_DDRMON, "clk24_ddrmon", "xin24m", 4, 15),
    /* CRU_GATE_CON05 */
    GATE(ACLK_GIC_AUDIO, "aclk_gic_audio", "aclk_gic_audio_sel", 5, 0),
    GATE(HCLK_GIC_AUDIO, "hclk_gic_audio", "hclk_gic_audio_sel", 5, 1),
    GATE(ACLK_GIC600, "aclk_gic600", "aclk_gic_audio", 5, 4),
    GATE(ACLK_SPINLOCK, "aclk_spinlock", "aclk_gic_audio", 5, 7),
    GATE(HCLK_SDMMC_BUFFER, "hclk_sdmmc_buffer", "hclk_gic_audio", 5, 8),
    GATE(DCLK_SDMMC_BUFFER, "dclk_sdmmc_buffer", "dclk_sdmmc_buffer_sel", 5, 9),
    GATE(HCLK_I2S0_8CH, "hclk_i2s0_8ch", "hclk_gic_audio", 5, 10),
    GATE(HCLK_I2S1_8CH, "hclk_i2s1_8ch", "hclk_gic_audio", 5, 11),
    GATE(HCLK_I2S2_2CH, "hclk_i2s2_2ch", "hclk_gic_audio", 5, 12),
    GATE(HCLK_I2S3_2CH, "hclk_i2s3_2ch", "hclk_gic_audio", 5, 13),
    GATE(HCLK_PDM, "hclk_pdm", "hclk_gic_audio", 5, 14),
    GATE(MCLK_PDM, "mclk_pdm", "mclk_pdm_sel", 5, 15),
    /* CRU_GATE_CON06 */
    GATE(CLK_I2S0_8CH_TX_SRC, "clk_i2s0_8ch_tx_src", "clk_i2s0_8ch_tx_src_c", 6, 0),
    GATE(CLK_I2S0_8CH_TX_FRAC, "clk_i2s0_8ch_tx_frac", "clk_i2s0_8ch_tx_frac_div", 6, 1),
    GATE(MCLK_I2S0_8CH_TX, "mclk_i2s0_8ch_tx", "clk_i2s0_8ch_tx", 6, 2),
    GATE(I2S0_MCLKOUT_TX, "i2s0_mclkout_tx", "i2s0_mclkout_tx_sel", 6, 3),
    GATE(CLK_I2S0_8CH_RX_SRC, "clk_i2s0_8ch_rx_src", "clk_i2s0_8ch_rx_src_c", 6, 4),
    GATE(CLK_I2S0_8CH_RX_FRAC, "clk_i2s0_8ch_rx_frac", "clk_i2s0_8ch_rx_frac_div", 6, 5),
    GATE(MCLK_I2S0_8CH_RX, "mclk_i2s0_8ch_rx", "clk_i2s0_8ch_rx", 6, 6),
    GATE(I2S0_MCLKOUT_RX, "i2s0_mclkout_rx", "i2s0_mclkout_rx_sel", 6, 7),
    GATE(CLK_I2S1_8CH_TX_SRC, "clk_i2s1_8ch_tx_src", "clk_i2s1_8ch_tx_src_c", 6, 8),
    GATE(CLK_I2S1_8CH_TX_FRAC, "clk_i2s1_8ch_tx_frac", "clk_i2s1_8ch_tx_frac_div", 6, 9),
    GATE(MCLK_I2S1_8CH_TX, "mclk_i2s1_8ch_tx", "clk_i2s1_8ch_tx", 6, 10),
    GATE(I2S1_MCLKOUT_TX, "i2s1_mclkout_tx", "i2s1_mclkout_tx_sel", 6, 11),
    GATE(CLK_I2S1_8CH_RX_SRC, "clk_i2s1_8ch_rx_src", "clk_i2s1_8ch_rx_src_c", 6, 12),
    GATE(CLK_I2S1_8CH_RX_FRAC, "clk_i2s1_8ch_rx_frac", "clk_i2s1_8ch_rx_frac_div", 6, 13),
    GATE(MCLK_I2S1_8CH_RX, "mclk_i2s1_8ch_rx", "clk_i2s1_8ch_rx", 6, 14),
    GATE(I2S1_MCLKOUT_RX, "i2s1_mclkout_rx", "i2s1_mclkout_rx_sel", 6, 15),
    /* CRU_GATE_CON07 */
    GATE(CLK_I2S2_2CH_SRC, "clk_i2s2_2ch_src", "clk_i2s2_2ch_src_c", 7, 0),
    GATE(CLK_I2S2_2CH_FRAC, "clk_i2s2_2ch_frac", "clk_i2s2_2ch_frac_div", 7, 1),
    GATE(MCLK_I2S2_2CH, "mclk_i2s2_2ch", "clk_i2s2_2ch", 7, 2),
    GATE(I2S2_MCLKOUT, "i2s2_mclkout", "i2s2_mclkout_sel", 7, 3),
    GATE(CLK_I2S3_2CH_TX, "clk_i2s3_2ch_tx_src", "clk_i2s3_2ch_tx_src_c", 7, 4),
    GATE(CLK_I2S3_2CH_TX_FRAC, "clk_i2s3_2ch_tx_frac", "clk_i2s3_2ch_tx_frac_div", 7, 5),
    GATE(MCLK_I2S3_2CH_TX, "mclk_i2s3_2ch_tx", "clk_i2s3_2ch_tx", 7, 6),
    GATE(I2S3_MCLKOUT_TX, "i2s3_mclkout_tx", "i2s3_mclkout_tx_sel", 7, 7),
    GATE(CLK_I2S3_2CH_RX, "clk_i2s3_2ch_rx_src", "clk_i2s3_2ch_rx_src_div", 7, 8),
    GATE(CLK_I2S3_2CH_RX_FRAC, "clk_i2s3_2ch_rx_frac", "clk_i2s3_2ch_rx_frac_div", 7, 9),
    GATE(MCLK_I2S3_2CH_RX, "mclk_i2s3_2ch_rx", "clk_i2s3_2ch_rx", 7, 10),
    GATE(I2S3_MCLKOUT_RX, "i2s3_mclkout_rx", "i2s3_mclkout_rx_sel", 7, 11),
    GATE(HCLK_VAD, "hclk_vad", "hclk_gic_audio", 7, 12),
    GATE(HCLK_SPDIF_8CH, "hclk_spdif_8ch", "hclk_gic_audio", 7, 13),
    GATE(MCLK_SPDIF_8CH_SRC, "mclk_spdif_8ch_src", "mclk_spdif_8ch_src_c", 7, 14),
    GATE(MCLK_SPDIF_8CH_FRAC, "mclk_spdif_8ch_frac", "mclk_spdif_8ch_frac_div", 7, 15),
    /* CRU_GATE_CON08 */
    GATE(HCLK_AUDPWM, "hclk_audpwm", "hclk_gic_audio", 8, 0),
    GATE(SCLK_AUDPWM_SRC, "sclk_audpwm_src", "sclk_audpwm_src_c", 8, 1),
    GATE(SCLK_AUDPWM_FRAC, "sclk_audpwm_frac", "sclk_audpwm_frac_frac", 8, 2),
    GATE(HCLK_ACDCDIG, "hclk_acdcdig", "hclk_gic_audio", 8, 3),
    GATE(CLK_ACDCDIG_I2C, "clk_acdcdig_i2c", "clk_acdcdig_i2c_sel", 8, 4),
    GATE(CLK_ACDCDIG_DAC, "clk_acdcdig_dac", "mclk_i2s3_2ch_tx", 8, 5),
    GATE(CLK_ACDCDIG_ADC, "clk_acdcdig_adc", "mclk_i2s3_2ch_rx", 8, 6),
    GATE(ACLK_SECURE_FLASH, "aclk_secure_flash", "aclk_secure_flash_sel", 8, 7),
    GATE(HCLK_SECURE_FLASH, "hclk_secure_flash", "hclk_secure_flash_sel", 8, 8),
    GATE(ACLK_CRYPTO_NS, "aclk_crypto_ns", "aclk_secure_flash", 8, 11),
    GATE(HCLK_CRYPTO_NS, "hclk_crypto_ns", "hclk_secure_flash", 8, 12),
    GATE(CLK_CRYPTO_NS_CORE, "clk_crypto_ns_core", "clk_crypto_ns_core_sel", 8, 13),
    GATE(CLK_CRYPTO_NS_PKA, "clk_crypto_ns_pka", "clk_crypto_ns_pka_sel", 8, 14),
    GATE(CLK_CRYPTO_NS_RNG, "clk_crypto_ns_rng", "hclk_secure_flash", 8, 15),
    /* CRU_GATE_CON09 */
    GATE(HCLK_NANDC, "hclk_nandc", "hclk_secure_flash", 9, 0),
    GATE(NCLK_NANDC, "nclk_nandc", "nclk_nandc_sel", 9, 1),
    GATE(HCLK_SFC, "hclk_sfc", "hclk_secure_flash", 9, 2),
    GATE(HCLK_SFC_XIP, "hclk_sfc_xip", "hclk_secure_flash", 9, 3),
    GATE(SCLK_SFC, "sclk_sfc", "sclk_sfc_sel", 9, 4),
    GATE(ACLK_EMMC, "aclk_emmc", "aclk_secure_flash", 9, 5),
    GATE(HCLK_EMMC, "hclk_emmc", "hclk_secure_flash", 9, 6),
    GATE(BCLK_EMMC, "bclk_emmc", "bclk_emmc_sel", 9, 7),
    GATE(CCLK_EMMC, "cclk_emmc", "cclk_emmc_sel", 9, 8),
    GATE(TCLK_EMMC, "tclk_emmc", "xin24m", 9, 9),
    GATE(HCLK_TRNG_NS, "hclk_trng_ns", "hclk_secure_flash", 9, 10),
    GATE(CLK_TRNG_NS, "clk_trng_ns", "hclk_secure_flash", 9, 11),
    /* CRU_GATE_CON10 */
    GATE(ACLK_PIPE, "aclk_pipe", "aclk_pipe_sel", 10, 0),
    GATE(PCLK_PIPE, "pclk_pipe", "pclk_pipe_div", 10, 1),
    GATE(CLK_XPCS_EEE, "clk_xpcs_eee", "clk_xpcs_eee_sel", 10, 4),
    GATE(ACLK_USB3OTG0, "aclk_usb3otg0", "aclk_pipe", 10, 8),
    GATE(CLK_USB3OTG0_REF, "clk_usb3otg0_ref", "xin24m", 10, 9),
    GATE(CLK_USB3OTG0_SUSPEND, "clk_usb3otg0_suspend", "clk_usb3otg0_suspend_sel", 10, 10),
    GATE(ACLK_USB3OTG1, "aclk_usb3otg1", "aclk_pipe", 10, 12),
    GATE(CLK_USB3OTG1_REF, "clk_usb3otg1_ref", "xin24m", 10, 13),
    GATE(CLK_USB3OTG1_SUSPEND, "clk_usb3otg1_suspend", "clk_usb3otg1_suspend_sel", 10, 14),
    /* CRU_GATE_CON11 */
    GATE(ACLK_SATA0, "aclk_sata0", "aclk_pipe", 11, 0),
    GATE(CLK_SATA0_PMALIVE, "clk_sata0_pmalive", "clk_gpll_div_20m", 11, 1),
    GATE(CLK_SATA0_RXOOB, "clk_sata0_rxoob", "clk_cpll_div_50m", 11, 2),
    GATE(ACLK_SATA1, "aclk_sata1", "aclk_pipe", 11, 4),
    GATE(CLK_SATA1_PMALIVE, "clk_sata1_pmalive", "clk_gpll_div_20m", 11, 5),
    GATE(CLK_SATA1_RXOOB, "clk_sata1_rxoob", "clk_cpll_div_50m", 11, 6),
    GATE(ACLK_SATA2, "aclk_sata2", "aclk_pipe", 11, 8),
    GATE(CLK_SATA2_PMALIVE, "clk_sata2_pmalive", "clk_gpll_div_20m", 11, 9),
    GATE(CLK_SATA2_RXOOB, "clk_sata2_rxoob", "clk_cpll_div_50m", 11, 10),
    /* CRU_GATE_CON12 */
    GATE(ACLK_PCIE20_MST, "aclk_pcie20_mst", "aclk_pipe", 12, 0),
    GATE(ACLK_PCIE20_SLV, "aclk_pcie20_slv", "aclk_pipe", 12, 1),
    GATE(ACLK_PCIE20_DBI, "aclk_pcie20_dbi", "aclk_pipe", 12, 2),
    GATE(PCLK_PCIE20, "pclk_pcie20", "pclk_pipe", 12, 3),
    GATE(CLK_PCIE20_AUX_NDFT, "clk_pcie20_aux_ndft", "xin24m", 12, 4),
    GATE(ACLK_PCIE30X1_MST, "aclk_pcie30x1_mst", "aclk_pipe", 12, 8),
    GATE(ACLK_PCIE30X1_SLV, "aclk_pcie30x1_slv", "aclk_pipe", 12, 9),
    GATE(ACLK_PCIE30X1_DBI, "aclk_pcie30x1_dbi", "aclk_pipe", 12, 10),
    GATE(PCLK_PCIE30X1, "pclk_pcie30x1", "pclk_pipe", 12, 11),
    GATE(CLK_PCIE30X1_AUX_NDFT, "clk_pcie30x1_aux_ndft", "xin24m", 12, 12),
    /* CRU_GATE_CON13 */
    GATE(ACLK_PCIE30X2_MST, "aclk_pcie30x2_mst", "aclk_pipe", 13, 0),
    GATE(ACLK_PCIE30X2_SLV, "aclk_pcie30x2_slv", "aclk_pipe", 13, 1),
    GATE(ACLK_PCIE30X2_DBI, "aclk_pcie30x2_dbi", "aclk_pipe", 13, 2),
    GATE(PCLK_PCIE30X2, "pclk_pcie30x2", "pclk_pipe", 13, 3),
    GATE(CLK_PCIE30X2_AUX_NDFT, "clk_pcie30x2_aux_ndft", "xin24m", 13, 4),
    GATE(PCLK_XPCS, "pclk_xpcs", "pclk_pipe", 13, 6),
    /* CRU_GATE_CON14 */
    GATE(ACLK_PERIMID, "aclk_perimid", "aclk_perimid_sel", 14, 0),
    GATE(HCLK_PERIMID, "hclk_perimid", "hclk_perimid_sel", 14, 1),
    GATE(ACLK_PHP, "aclk_php", "aclk_php_sel", 14, 8),
    GATE(HCLK_PHP, "hclk_php", "hclk_php_sel", 14, 9),
    GATE(PCLK_PHP, "pclk_php", "pclk_php_div", 14, 10),
    /* CRU_GATE_CON15 */
    GATE(HCLK_SDMMC0, "hclk_sdmmc0", "hclk_php", 15, 0),
    GATE(CLK_SDMMC0, "clk_sdmmc0", "clk_sdmmc0_sel", 15, 1),
    GATE(HCLK_SDMMC1, "hclk_sdmmc1", "hclk_php", 15, 2),
    GATE(CLK_SDMMC1, "clk_sdmmc1", "clk_sdmmc1_sel", 15, 3),
    GATE(CLK_GMAC0_PTP_REF, "clk_gmac0_ptp_ref", "clk_gmac0_ptp_ref_sel", 15, 4),
    GATE(ACLK_GMAC0, "aclk_gmac0", "aclk_php", 15, 5),
    GATE(PCLK_GMAC0, "pclk_gmac0", "pclk_php", 15, 6),
    GATE(CLK_MAC0_2TOP, "clk_mac0_2top", "clk_mac0_2top_sel", 15, 7),
    GATE(CLK_MAC0_OUT, "clk_mac0_out", "clk_mac0_out_sel", 15, 8),
    GATE(CLK_MAC0_REFOUT, "clk_mac0_refout", "clk_mac0_2top", 15, 12),
    /* CRU_GATE_CON16 */
    GATE(ACLK_USB, "aclk_usb", "aclk_usb_sel", 16, 0),
    GATE(HCLK_USB, "hclk_usb", "hclk_usb_sel", 16, 1),
    GATE(PCLK_USB, "pclk_usb", "pclk_usb_div", 16, 2),
    GATE(HCLK_USB2HOST0, "hclk_usb2host0", "hclk_usb", 16, 12),
    GATE(HCLK_USB2HOST0_ARB, "hclk_usb2host0_arb", "hclk_usb", 16, 13),
    GATE(HCLK_USB2HOST1, "hclk_usb2host1", "hclk_usb", 16, 14),
    GATE(HCLK_USB2HOST1_ARB, "hclk_usb2host1_arb", "hclk_usb", 16, 15),
    /* CRU_GATE_CON17 */
    GATE(HCLK_SDMMC2, "hclk_sdmmc2", "hclk_usb", 17, 0),
    GATE(CLK_SDMMC2, "clk_sdmmc2", "clk_sdmmc2_sel", 17, 1),
    GATE(CLK_GMAC1_PTP_REF, "clK_gmac1_ptp_ref", "clk_gmac1_ptp_ref_sel", 17, 2),
    GATE(ACLK_GMAC1, "aclk_gmac1", "aclk_usb", 17, 3),
    GATE(PCLK_GMAC1, "pclk_gmac1", "pclk_usb", 17, 4),
    GATE(CLK_MAC1_2TOP, "clk_mac1_2top", "clk_mac1_2top_sel", 17, 5),
    GATE(CLK_MAC1_OUT, "clk_mac1_out", "clk_mac1_out_sel", 17, 6),
    GATE(CLK_MAC1_REFOUT, "clk_mac1_refout", "clk_mac1_2top", 17, 10),
    /* CRU_GATE_CON18 */
    GATE(ACLK_VI, "aclk_vi", "aclk_vi_sel", 18, 0),
    GATE(HCLK_VI, "hclk_vi", "hclk_vi_div", 18, 1),
    GATE(PCLK_VI, "pclk_vi", "pclk_vi_div", 18, 2),
    GATE(ACLK_VICAP, "aclk_vicap", "aclk_vi", 18, 9),
    GATE(HCLK_VICAP, "hclk_vicap", "hclk_vi", 18, 10),
    GATE(DCLK_VICAP, "dclk_vicap", "dclk_vicap1_sel", 18, 11),
    /* CRU_GATE_CON19 */
    GATE(ACLK_ISP, "aclk_isp", "aclk_vi", 19, 0),
    GATE(HCLK_ISP, "hclk_isp", "hclk_vi", 19, 1),
    GATE(CLK_ISP, "clk_isp", "clk_isp_c", 19, 2),
    GATE(PCLK_CSI2HOST1, "pclk_csi2host1", "pclk_vi", 19, 4),
    GATE(CLK_CIF_OUT, "clk_cif_out", "clk_cif_out_c", 19, 8),
    GATE(CLK_CAM0_OUT, "clk_cam0_out", "clk_cam0_out_c", 19, 9),
    GATE(CLK_CAM1_OUT, "clk_cam1_out", "clk_cam1_out_c", 19, 9),
    /* CRU_GATE_CON20 */
    GATE(ACLK_VO, "aclk_vo", "aclk_vo_sel", 20, 0),
    GATE(HCLK_VO, "hclk_vo", "hclk_vo_div", 20, 1),
    GATE(PCLK_VO, "pclk_vo", "pclk_vo_div", 20, 2),
    GATE(ACLK_VOP_PRE, "aclk_vop_pre", "aclk_vop_pre_c", 20, 6),
    GATE(ACLK_VOP, "aclk_vop", "aclk_vop_pre", 20, 8),
    GATE(HCLK_VOP, "hclk_vop", "hclk_vo", 20, 9),
    GATE(DCLK_VOP0, "dclk_vop0", "dclk_vop0_c", 20, 10),
    GATE(DCLK_VOP1, "dclk_vop1", "dclk_vop1_c", 20, 11),
    GATE(DCLK_VOP2, "dclk_vop2", "dclk_vop2_c", 20, 12),
    GATE(CLK_VOP_PWM, "clk_vop_pwm", "xin24m", 20, 13),
    /* CRU_GATE_CON21 */
    GATE(ACLK_HDCP, "aclk_hdcp", "aclk_vo", 21, 0),
    GATE(HCLK_HDCP, "hclk_hdcp", "hclk_vo", 21, 1),
    GATE(PCLK_HDCP, "pclk_hdcp", "pclk_vo", 21, 2),
    GATE(PCLK_HDMI_HOST, "pclk_hdmi_host", "pclk_vo", 21, 3),
    GATE(CLK_HDMI_SFR, "clk_hdmi_sfr", "xin24m", 21, 4),
    GATE(CLK_HDMI_CEC, "clk_hdmi_cec", "clk_rtc_32k", 21, 5),
    GATE(PCLK_DSITX_0, "pclk_dsitx_0", "pclk_vo", 21, 6),
    GATE(PCLK_DSITX_1, "pclk_dsitx_1", "pclk_vo", 21, 7),
    GATE(PCLK_EDP_CTRL, "pclk_edp_ctrl", "pclk_vo", 21, 8),
    GATE(CLK_EDP_200M, "clk_edp_200m", "clk_edp_200m_sel", 21, 9),
    /* CRU_GATE_CON22 */
    GATE(ACLK_VPU_PRE, "aclk_vpu_pre", "aclk_vpu_pre_c", 22, 0),
    GATE(HCLK_VPU_PRE, "hclk_vpu_pre", "aclk_vpu_pre_c", 22, 1),
    GATE(ACLK_VPU, "aclk_vpu", "aclk_vpu_pre", 22, 4),
    GATE(HCLK_VPU, "hclk_vpu", "hclk_vpu_pre", 22, 5),
    GATE(PCLK_RGA_PRE, "pclk_rga_pre", "pclk_rga_pre_div", 22, 12),
    GATE(PCLK_EINK, "pclk_eink", "pclk_rga_pre", 22, 14),
    GATE(HCLK_EINK, "hclk_eink", "hclk_rga_pre", 22, 15),
    /* CRU_GATE_CON23 */
    GATE(ACLK_RGA_PRE, "aclk_rga_pre", "aclk_rga_pre_sel", 23, 0),
    GATE(HCLK_RGA_PRE, "hclk_rga_pre", "hclk_rga_pre_div", 23, 1),
    GATE(ACLK_RGA, "aclk_rga", "aclk_rga_pre", 23, 4),
    GATE(HCLK_RGA, "hclk_rga", "hclk_rga_pre", 23, 5),
    GATE(CLK_RGA_CORE, "clk_rga_core", "clk_rga_core_sel", 23, 6),
    GATE(ACLK_IEP, "aclk_iep", "aclk_rga_pre", 23, 7),
    GATE(HCLK_IEP, "hclk_iep", "hclk_rga_pre", 23, 8),
    GATE(CLK_IEP_CORE, "clk_iep_core", "clk_iep_core_sel", 23, 9),
    GATE(HCLK_EBC, "hclk_ebc", "hclk_rga_pre", 23, 10),
    GATE(DCLK_EBC, "dclk_ebc", "dclk_ebc_sel", 23, 11),
    GATE(ACLK_JDEC, "aclk_jdec", "aclk_rga_pre", 23, 12),
    GATE(HCLK_JDEC, "hclk_jdec", "hclk_rga_pre", 23, 13),
    GATE(ACLK_JENC, "aclk_jenc", "aclk_rga_pre", 23, 14),
    GATE(HCLK_JENC, "hclk_jenc", "hclk_rga_pre", 23, 15),
    /* CRU_GATE_CON24 */
    GATE(ACLK_RKVENC_PRE, "aclk_rkvenc_pre", "aclk_rkvenc_pre_c", 24, 0),
    GATE(HCLK_RKVENC_PRE, "hclk_rkvenc_pre", "hclk_rkvenc_pre_div", 24, 1),
    GATE(ACLK_RKVENC, "aclk_rkvenc", "aclk_rkvenc_pre", 24, 6),
    GATE(HCLK_RKVENC, "hclk_rkvenc", "hclk_rkvenc_pre", 24, 7),
    GATE(CLK_RKVENC_CORE, "clk_rkvenc_core", "clk_rkvenc_core_c", 24, 8),
    GATE(ACLK_RKVDEC_PRE, "aclk_rkvdec_pre", "aclk_rkvdec_pre_c", 25, 0),
    /* CRU_GATE_CON25 */
    GATE(HCLK_RKVDEC_PRE, "hclk_rkvdec_pre", "hclk_rkvdec_pre_div", 25, 1),
    GATE(ACLK_RKVDEC, "aclk_rkvdec", "aclk_rkvdec_pre", 25, 4),
    GATE(HCLK_RKVDEC, "hclk_rkvdec", "hclk_rkvdec_pre", 25, 5),
    GATE(CLK_RKVDEC_CA, "clk_rkvdec_ca", "clk_rkvdec_ca_c", 25, 6),
    GATE(CLK_RKVDEC_CORE, "clk_rkvdec_core", "clk_rkvdec_core_c", 25, 7),
    GATE(CLK_RKVDEC_HEVC_CA, "clk_rkvdec_hevc_ca", "clk_rkvdec_hevc_ca_c", 25, 8),
    /* CRU_GATE_CON26 */
    GATE(ACLK_BUS, "aclk_bus", "aclk_bus_sel", 26, 0),
    GATE(PCLK_BUS, "pclk_bus", "pclk_bus_sel", 26, 1),
    GATE(PCLK_TSADC, "pclk_tsadc", "pclk_bus", 26, 4),
    GATE(CLK_TSADC_TSEN, "clk_tsadc_tsen", "clk_tsadc_tsen_c", 26, 5),
    GATE(CLK_TSADC, "clk_tsadc", "clk_tsadc_div", 26, 6),
    GATE(PCLK_SARADC, "pclk_saradc", "pclk_bus", 26, 7),
    GATE(CLK_SARADC, "clk_saradc", "xin24m", 26, 8),
    GATE(PCLK_OTPC_NS, "pclk_otpc_ns", "hclk_secure_flash", 26, 9),
    GATE(CLK_OTPC_NS_SBPI, "clk_otpc_ns_sbpi", "xin24m", 26, 10),
    GATE(CLK_OTPC_NS_USR, "clk_otpc_ns_usr", "xin_osc0_half", 26, 11),
    GATE(PCLK_SCR, "pclk_scr", "pclk_bus", 26, 12),
    GATE(PCLK_WDT_NS, "pclk_wdt_ns", "pclk_bus", 26, 13),
    GATE(TCLK_WDT_NS, "tclk_wdt_ns", "xin24m", 26, 14),
    /* CRU_GATE_CON27 */
    GATE(PCLK_CAN0, "pclk_can0", "pclk_bus", 27, 5),
    GATE(CLK_CAN0, "clk_can0", "clk_can0_c", 27, 6),
    GATE(PCLK_CAN1, "pclk_can1", "pclk_bus", 27, 7),
    GATE(CLK_CAN1, "clk_can1", "clk_can1_c", 27, 8),
    GATE(PCLK_CAN2, "pclk_can2", "pclk_bus", 27, 9),
    GATE(CLK_CAN2, "clk_can2", "clk_can2_c", 27, 10),
    GATE(PCLK_UART1, "pclk_uart1", "pclk_bus", 27, 12),
    GATE(CLK_UART1_SRC, "clk_uart1_src", "clk_uart1_src_c", 27, 13),
    GATE(CLK_UART1_FRAC, "clk_uart1_frac", "clk_uart1_frac_frac", 27, 14),
    GATE(SCLK_UART1, "sclk_uart1", "sclk_uart1_sel", 27, 15),
    /* CRU_GATE_CON28 */
    GATE(PCLK_UART2, "pclk_uart2", "pclk_bus", 28, 0),
    GATE(CLK_UART2_SRC, "clk_uart2_src", "clk_uart2_src_c", 28, 1),
    GATE(CLK_UART2_FRAC, "clk_uart2_frac", "clk_uart2_frac_frac", 28, 2),
    GATE(SCLK_UART2, "sclk_uart2", "sclk_uart2_sel", 28, 3),
    GATE(PCLK_UART3, "pclk_uart3", "pclk_bus", 28, 4),
    GATE(CLK_UART3_SRC, "clk_uart3_src", "clk_uart3_src_c", 28, 5),
    GATE(CLK_UART3_FRAC, "clk_uart3_frac", "clk_uart3_frac_frac", 28, 6),
    GATE(SCLK_UART3, "sclk_uart3", "sclk_uart3_sel", 28, 7),
    GATE(PCLK_UART4, "pclk_uart4", "pclk_bus", 28, 8),
    GATE(CLK_UART4_SRC, "clk_uart4_src", "clk_uart4_src_c", 28, 9),
    GATE(CLK_UART4_FRAC, "clk_uart4_frac", "clk_uart4_frac_frac", 28, 10),
    GATE(SCLK_UART4, "sclk_uart4", "sclk_uart4_sel", 28, 11),
    GATE(PCLK_UART5, "pclk_uart5", "pclk_bus", 28, 12),
    GATE(CLK_UART5_SRC, "clk_uart5_src", "clk_uart5_src_c", 28, 13),
    GATE(CLK_UART5_FRAC, "clk_uart5_frac", "clk_uart5_frac_frac", 28, 14),
    GATE(SCLK_UART5, "sclk_uart5", "sclk_uart5_sel", 28, 15),
    /* CRU_GATE_CON29 */
    GATE(PCLK_UART6, "pclk_uart6", "pclk_bus", 29, 0),
    GATE(CLK_UART6_SRC, "clk_uart6_src", "clk_uart6_src_c", 29, 1),
    GATE(CLK_UART6_FRAC, "clk_uart6_frac", "clk_uart6_frac_frac", 29, 2),
    GATE(SCLK_UART6, "sclk_uart6", "sclk_uart6_sel", 29, 3),
    GATE(PCLK_UART7, "pclk_uart7", "pclk_bus", 29, 4),
    GATE(CLK_UART7_SRC, "clk_uart7_src", "clk_uart7_src_c", 29, 5),
    GATE(CLK_UART7_FRAC, "clk_uart7_frac", "clk_uart7_frac_frac", 29, 6),
    GATE(SCLK_UART7, "sclk_uart7", "sclk_uart7_sel", 29, 7),
    GATE(PCLK_UART8, "pclk_uart8", "pclk_bus", 29, 8),
    GATE(CLK_UART8_SRC, "clk_uart8_src", "clk_uart8_src_c", 29, 9),
    GATE(CLK_UART8_FRAC, "clk_uart8_frac", "clk_uart8_frac_frac", 29, 10),
    GATE(SCLK_UART8, "sclk_uart8", "sclk_uart8_sel", 29, 11),
    GATE(PCLK_UART9, "pclk_uart9", "pclk_bus", 29, 12),
    GATE(CLK_UART9_SRC, "clk_uart9_src", "clk_uart9_src_c", 29, 13),
    GATE(CLK_UART9_FRAC, "clk_uart9_frac", "clk_uart9_frac_frac", 29, 14),
    GATE(SCLK_UART9, "sclk_uart9", "sclk_uart9_sel", 29, 15),
    /* CRU_GATE_CON30 */
    GATE(PCLK_I2C1, "pclk_i2c1", "pclk_bus", 30, 0),
    GATE(CLK_I2C1, "clk_i2c1", "clk_i2c", 30, 1),
    GATE(PCLK_I2C2, "pclk_i2c2", "pclk_bus", 30, 2),
    GATE(CLK_I2C2, "clk_i2c2", "clk_i2c", 30, 3),
    GATE(PCLK_I2C3, "pclk_i2c3", "pclk_bus", 30, 4),
    GATE(CLK_I2C3, "clk_i2c3", "clk_i2c", 30, 5),
    GATE(PCLK_I2C4, "pclk_i2c4", "pclk_bus", 30, 6),
    GATE(CLK_I2C4, "clk_i2c4", "clk_i2c", 30, 7),
    GATE(PCLK_I2C5, "pclk_i2c5", "pclk_bus", 30, 8),
    GATE(CLK_I2C5, "clk_i2c5", "clk_i2c", 30, 9),
    GATE(PCLK_SPI0, "pclk_spi0", "pclk_bus", 30, 10),
    GATE(CLK_SPI0, "clk_spi0", "clk_spi0_sel", 30, 11),
    GATE(PCLK_SPI1, "pclk_spi1", "pclk_bus", 30, 12),
    GATE(CLK_SPI1, "clk_spi1", "clk_spi1_sel", 30, 13),
    GATE(PCLK_SPI2, "pclk_spi2", "pclk_bus", 30, 14),
    GATE(CLK_SPI2, "clk_spi2", "clk_spi2_sel", 30, 15),
    /* CRU_GATE_CON31 */
    GATE(PCLK_SPI3, "pclk_spi3", "pclk_bus", 31, 0),
    GATE(CLK_SPI3, "clk_spi3", "clk_spi3_sel", 31, 1),
    GATE(PCLK_GPIO1, "pclk_gpio1", "pclk_bus", 31, 2),
    GATE(DBCLK_GPIO1, "dbclk_gpio1", "dbclk_gpio", 31, 3),
    GATE(PCLK_GPIO2, "pclk_gpio2", "pclk_bus", 31, 4),
    GATE(DBCLK_GPIO2, "dbclk_gpio2", "dbclk_gpio", 31, 5),
    GATE(PCLK_GPIO3, "pclk_gpio3", "pclk_bus", 31, 6),
    GATE(DBCLK_GPIO3, "dbclk_gpio3", "dbclk_gpio", 31, 7),
    GATE(PCLK_GPIO4, "pclk_gpio4", "pclk_bus", 31, 8),
    GATE(DBCLK_GPIO4, "dbclk_gpio4", "dbclk_gpio", 31, 9),
    GATE(PCLK_PWM1, "pclk_pwm1", "pclk_bus", 31, 10),
    GATE(CLK_PWM1, "clk_pwm1", "clk_pwm1_sel", 31, 11),
    GATE(CLK_PWM1_CAPTURE, "clk_pwm1_capture", "xin24m", 31, 12),
    GATE(PCLK_PWM2, "pclk_pwm2", "pclk_bus", 31, 13),
    GATE(CLK_PWM2, "clk_pwm2", "clk_pwm2_sel", 31, 14),
    GATE(CLK_PWM2_CAPTURE, "clk_pwm2_capture", "xin24m", 31, 15),
    /* CRU_GATE_CON32 */
    GATE(PCLK_PWM3, "pclk_pwm3", "pclk_bus", 32, 0),
    GATE(CLK_PWM3, "clk_pwm3", "clk_pwm3_sel", 32, 1),
    GATE(CLK_PWM3_CAPTURE, "clk_pwm3_capture", "xin24m", 32, 2),
    GATE(PCLK_TIMER, "pclk_timer", "pclk_bus", 32, 3),
    GATE(CLK_TIMER0, "clk_timer0", "xin24m", 32, 4),
    GATE(CLK_TIMER1, "clk_timer1", "xin24m", 32, 5),
    GATE(CLK_TIMER2, "clk_timer2", "xin24m", 32, 6),
    GATE(CLK_TIMER3, "clk_timer3", "xin24m", 32, 7),
    GATE(CLK_TIMER4, "clk_timer4", "xin24m", 32, 8),
    GATE(CLK_TIMER5, "clk_timer5", "xin24m", 32, 9),
    GATE(CLK_I2C, "clk_i2c", "clk_i2c_sel", 32, 10),
    GATE(DBCLK_GPIO, "dbclk_gpio", "dbclk_gpio_sel", 32, 11),
    GATE(ACLK_MCU, "aclk_mcu", "aclk_bus", 32, 13),
    GATE(PCLK_INTMUX, "pclk_intmux", "pclk_bus", 32, 14),
    GATE(PCLK_MAILBOX, "pclk_mailbox", "pclk_bus", 32, 15),
    /* CRU_GATE_CON33 */
    GATE(ACLK_TOP_HIGH, "aclk_top_high", "aclk_top_high_sel", 33, 0),
    GATE(ACLK_TOP_LOW, "aclk_top_low", "aclk_top_low_sel", 33, 1),
    GATE(HCLK_TOP, "hclk_top", "hclk_top_sel", 33, 2),
    GATE(PCLK_TOP, "pclk_top", "pclk_top_sel", 33, 3),
    GATE(PCLK_PCIE30PHY, "pclk_pcie30phy", "pclk_top", 33, 8),
    GATE(CLK_OPTC_ARB, "clk_optc_arb", "clk_optc_arb_sel", 33, 9),
    GATE(PCLK_MIPICSIPHY, "pclk_mipicsiphy", "pclk_top", 33, 13),
    GATE(PCLK_MIPIDSIPHY0, "pclk_mipidsiphy0", "pclk_top", 33, 14),
    GATE(PCLK_MIPIDSIPHY1, "pclk_mipidsiphy1", "pclk_top", 33, 15),
    /* CRU_GATE_CON34 */
    GATE(PCLK_PIPEPHY0, "pclk_pipephy0", "pclk_top", 34, 4),
    GATE(PCLK_PIPEPHY1, "pclk_pipephy1", "pclk_top", 34, 5),
    GATE(PCLK_PIPEPHY2, "pclk_pipephy2", "pclk_top", 34, 6),
    GATE(PCLK_CPU_BOOST, "pclk_cpu_boost", "pclk_top", 34, 11),
    GATE(CLK_CPU_BOOST, "clk_cpu_boost", "xin24m", 34, 12),
    GATE(PCLK_OTPPHY, "pclk_otpphy", "pclk_top", 34, 13),
    GATE(PCLK_EDPPHY_GRF, "pclk_edpphy_grf", "pclk_top", 34, 14),
    /* CRU_GATE_CON35 */
    GATE(CPLL_500M, "clk_cpll_div_500m", "clk_cpll_div_500m_div", 35, 7),
    GATE(CPLL_333M, "clk_cpll_div_333m", "clk_cpll_div_333m_div", 35, 8),
    GATE(CPLL_250M, "clk_cpll_div_250m", "clk_cpll_div_250m_div", 35, 9),
    GATE(CPLL_125M, "clk_cpll_div_125m", "clk_cpll_div_125m_div", 35, 10),
    GATE(CPLL_100M, "clk_cpll_div_100m", "clk_cpll_div_100m_div", 35, 11),
    GATE(CPLL_62P5M, "clk_cpll_div_62P5m", "clk_cpll_div_62P5m_div", 35, 12),
    GATE(CPLL_50M, "clk_cpll_div_50m", "clk_cpll_div_50m_div", 35, 13),
    GATE(CPLL_25M, "clk_cpll_div_25m", "clk_cpll_div_25m_div", 35, 14),
};

static struct rk_clk_gate pmu_clk_gates[] =
{
    /* PMUCRU_PMUGATE_CON00 */
    GATE(XIN_OSC0_DIV, "xin_osc0_div", "xin_osc0_div_div", 0, 0),
    GATE(CLK_RTC_32K, "clk_rtc_32k", "clk_rtc_32k_mux", 0, 1),
    GATE(PCLK_PDPMU, "pclk_pdpmu", "pclk_pdpmu_pre", 0, 2),
    GATE(PCLK_PMU, "pclk_pmu", "pclk_pdpmu", 0, 6),
    GATE(CLK_PMU, "clk_pmu", "xin24m", 0, 7),
    /* PMUCRU_PMUGATE_CON01 */
    GATE(PCLK_I2C0, "pclk_i2c0", "pclk_pdpmu", 1, 0),
    GATE(CLK_I2C0, "clk_i2c0", "clk_i2c0_div", 1, 1),
    GATE(PCLK_UART0, "pclk_uart0", "pclk_pdpmu", 1, 2),
    GATE(CLK_UART0_DIV, "sclk_uart0_div", "sclk_uart0_div_div", 1, 3),
    GATE(CLK_UART0_FRAC, "sclk_uart0_frac", "sclk_uart0_frac_div", 1, 4),
    GATE(SCLK_UART0, "sclk_uart0", "sclk_uart0_mux", 1, 5),
    GATE(PCLK_PWM0, "pclk_pwm0", "pclk_pdpmu", 1, 6),
    GATE(CLK_PWM0, "clk_pwm0", "clk_pwm0_div", 1, 7),
    GATE(CLK_CAPTURE_PWM0_NDFT, "clk_capture_pwm0_ndft", "xin24m", 1, 8),
    GATE(PCLK_GPIO0, "pclk_gpio0", "pclk_pdpmu", 1, 9),
    GATE(DBCLK_GPIO0, "dbclk_gpio0", "dbclk_gpio0_sel", 1, 10),
    GATE(PCLK_PMUPVTM, "pclk_pmupvtm", "pclk_pdpmu", 1, 11),
    GATE(CLK_PMUPVTM, "clk_pmupvtm", "xin24m", 1, 12),
    GATE(CLK_CORE_PMUPVTM, "clk_core_pmupvtm", "xin24m", 1, 13),
    /* PMUCRU_PMUGATE_CON02 */
    GATE(CLK_REF24M, "clk_ref24m", "clk_ref24m_div", 2, 0),
    GATE(XIN_OSC0_USBPHY0_G, "xin_osc0_usbphy0_g", "xin24m", 2, 1),
    GATE(XIN_OSC0_USBPHY1_G, "xin_osc0_usbphy1_g", "xin24m", 2, 2),
    GATE(XIN_OSC0_MIPIDSIPHY0_G, "xin_osc0_mipidsiphy0_g", "xin24m", 2, 3),
    GATE(XIN_OSC0_MIPIDSIPHY1_G, "xin_osc0_mipidsiphy1_g", "xin24m", 2, 4),
    GATE(CLK_WIFI_DIV, "clk_wifi_div", "clk_wifi_div_div", 2, 5),
    GATE(CLK_WIFI_OSC0, "clk_wifi_osc0", "xin24m", 2, 6),
    GATE(CLK_PCIEPHY0_DIV, "clk_pciephy0_div", "clk_pciephy0_div_div", 2, 7),
    GATE(CLK_PCIEPHY0_OSC0, "clk_pciephy0_osc0", "xin24m", 2, 8),
    GATE(CLK_PCIEPHY1_DIV, "clk_pciephy1_div", "clk_pciephy1_div_div", 2, 9),
    GATE(CLK_PCIEPHY1_OSC0, "clk_pciephy1_osc0", "xin24m", 2, 10),
    GATE(CLK_PCIEPHY2_DIV, "clk_pciephy2_div", "clk_pciephy2_div_div", 2, 11),
    GATE(CLK_PCIEPHY2_OSC0, "clk_pciephy2_osc0", "xin24m", 2, 12),
    GATE(CLK_PCIE30PHY_REF_M, "clk_pcie30phy_ref_m", "ppll_ph0", 2, 13),
    GATE(CLK_PCIE30PHY_REF_N, "clk_pcie30phy_ref_n", "ppll_ph180", 2, 14),
    GATE(XIN_OSC0_EDPPHY_G, "xin_osc0_edpphy_g", "xin24m", 2, 15),
};

#define PLL_MODE_MASK   0x1
#include "clk-pll-rk3568.c"
#include "clk-mmc-phase.c"
#include "softrst.c"

static struct rk_pmuclk_priv *find_pmu(void)
{
    struct rk_pmuclk_priv *pmu_priv = RT_NULL;
    const char *compatible = "rockchip,rk3568-pmucru";
    struct rt_ofw_node *np = rt_ofw_find_node_by_compatible(RT_NULL, compatible);

    if (np)
    {
        struct rk_clk *rk_clk = rt_ofw_data(np);

        pmu_priv = &rk_clk->pmuclk_info;
        rt_ofw_node_put(np);
    }
    else
    {
        LOG_E("Find pmucru %s fail", compatible);
    }

    return pmu_priv;
}

static rt_ubase_t pmu_pll_set_rate(rt_ubase_t pll_id, rt_ubase_t rate)
{
    struct rk_pmuclk_priv *pmu_priv = find_pmu();

    if (pmu_priv)
    {
        rk_pll_set_rate(&pmu_pll_clks[pll_id], pmu_priv->pmucru, rate);
    }

    return 0;
}

static rt_ubase_t pmu_pll_get_rate(rt_ubase_t pll_id)
{
    struct rk_pmuclk_priv *pmu_priv = find_pmu();

    if (pmu_priv)
    {
        return rk_pll_get_rate(&pmu_pll_clks[pll_id], &pmu_priv->pmucru);
    }

    return 0;
}

static rt_ubase_t rtc32k_get_pmuclk(struct rk_pmuclk_priv *priv)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    rt_ubase_t m, n;
    rt_uint32_t fracdiv;

    fracdiv = HWREG32(&pmucru->pmu_clksel_con[1]);
    m = fracdiv & RTC32K_FRAC_NUMERATOR_MASK;
    m >>= RTC32K_FRAC_NUMERATOR_SHIFT;
    n = fracdiv & RTC32K_FRAC_DENOMINATOR_MASK;
    n >>= RTC32K_FRAC_DENOMINATOR_SHIFT;

    return OSC_HZ * m / n;
}

static rt_ubase_t rtc32k_set_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t rate)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    rt_ubase_t m, n, val;

    rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK, RTC32K_SEL_OSC0_DIV32K << RTC32K_SEL_SHIFT);

    rational_best_approximation(rate, OSC_HZ, RT_GENMASK(16 - 1, 0), RT_GENMASK(16 - 1, 0), &m, &n);
    val = m << RTC32K_FRAC_NUMERATOR_SHIFT | n;
    HWREG32(&pmucru->pmu_clksel_con[1]) = val;

    return rtc32k_get_pmuclk(priv);
}

static rt_ubase_t uart_get_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    rt_uint32_t reg, con, fracdiv, div, src, p_src, p_rate;
    rt_ubase_t m, n;

    switch (clk_id)
    {
    case SCLK_UART0:
        reg = 4;
        break;
    default:
        return -RT_ERROR;
    }

    con = HWREG32(&pmucru->pmu_clksel_con[reg]);
    src = (con & CLK_UART0_SEL_MASK) >> CLK_UART0_SEL_SHIFT;
    div = (con & CLK_UART0_DIV_DIV_MASK) >> CLK_UART0_DIV_DIV_SHIFT;
    p_src = (con & CLK_UART0_DIV_SEL_MASK) >> CLK_UART0_DIV_SEL_SHIFT;

    if (p_src == CLK_UART0_SRC_SEL_PPLL)
    {
        p_rate = priv->ppll_hz;
    }
    else if (p_src == CLK_UART0_SRC_SEL_GPLL)
    {
        p_rate = priv->hpll_hz;
    }
    else
    {
        p_rate = 480000000;
    }
    if (src == CLK_UART0_SEL_DIV)
    {
        return DIV_TO_RATE(p_rate, div);
    }
    else if (src == CLK_UART0_SEL_FRACDIV)
    {
        fracdiv = HWREG32(&pmucru->pmu_clksel_con[reg + 1]);
        n = fracdiv & CLK_UART0_FRAC_NUMERATOR_MASK;
        n >>= CLK_UART0_FRAC_NUMERATOR_SHIFT;
        m = fracdiv & CLK_UART0_FRAC_DENOMINATOR_MASK;
        m >>= CLK_UART0_FRAC_DENOMINATOR_SHIFT;
        return DIV_TO_RATE(p_rate, div) * n / m;
    }
    else
    {
        return OSC_HZ;
    }
}

static rt_ubase_t uart_set_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    rt_uint32_t reg, clk_src, uart_src, div;
    rt_ubase_t m = 0, n = 0, val;

    if (priv->ppll_hz % rate == 0)
    {
        clk_src = CLK_UART0_SRC_SEL_PPLL;
        uart_src = CLK_UART0_SEL_DIV;
        div = RT_DIV_ROUND_UP(priv->ppll_hz, rate);
    }
    else if (priv->hpll_hz % rate == 0)
    {
        clk_src = CLK_UART0_SRC_SEL_GPLL;
        uart_src = CLK_UART0_SEL_DIV;
        div = RT_DIV_ROUND_UP(priv->hpll_hz, rate);
    }
    else if (rate == OSC_HZ)
    {
        clk_src = CLK_UART0_SRC_SEL_GPLL;
        uart_src = CLK_UART0_SEL_XIN24M;
        div = 2;
    }

    switch (clk_id)
    {
    case SCLK_UART0:
        reg = 4;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&pmucru->pmu_clksel_con[reg], CLK_UART0_SEL_MASK | CLK_UART0_DIV_SEL_MASK | CLK_UART0_DIV_DIV_MASK,
            (clk_src << CLK_UART0_DIV_SEL_SHIFT) | (uart_src << CLK_UART0_SEL_SHIFT) |
            ((div - 1) << CLK_UART0_DIV_DIV_SHIFT));
    if (m && n)
    {
        val = m << CLK_UART0_FRAC_NUMERATOR_SHIFT | n;
        HWREG32(&pmucru->pmu_clksel_con[reg + 1]) = val;
    }

    return uart_get_pmuclk(priv, clk_id);
}

static rt_ubase_t i2c_get_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    rt_uint32_t div, con;

    switch (clk_id)
    {
    case CLK_I2C0:
        con = HWREG32(&pmucru->pmu_clksel_con[3]);
        div = (con & CLK_I2C0_DIV_MASK) >> CLK_I2C0_DIV_SHIFT;
        break;
    default:
        return -RT_ERROR;
    }

    return DIV_TO_RATE(priv->ppll_hz, div);
}

static rt_ubase_t i2c_set_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(priv->ppll_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 127);

    switch (clk_id)
    {
    case CLK_I2C0:
        rk_clrsetreg(&pmucru->pmu_clksel_con[3], CLK_I2C0_DIV_MASK, (src_clk_div - 1) << CLK_I2C0_DIV_SHIFT);
        break;
    default:
        return -RT_ERROR;
    }

    return i2c_get_pmuclk(priv, clk_id);
}

static rt_ubase_t pwm_get_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    rt_uint32_t div, sel, con, parent;

    switch (clk_id)
    {
    case CLK_PWM0:
        con = HWREG32(&pmucru->pmu_clksel_con[6]);
        sel = (con & CLK_PWM0_SEL_MASK) >> CLK_PWM0_SEL_SHIFT;
        div = (con & CLK_PWM0_DIV_MASK) >> CLK_PWM0_DIV_SHIFT;
        if (sel == CLK_PWM0_SEL_XIN24M)
        {
            parent = OSC_HZ;
        }
        else
        {
            parent = priv->ppll_hz;
        }
        break;
    default:
        return -RT_ERROR;
    }

    return DIV_TO_RATE(parent, div);
}

static rt_ubase_t pwm_set_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    int src_clk_div;

    switch (clk_id)
    {
    case CLK_PWM0:
        if (rate == OSC_HZ)
        {
            rk_clrsetreg(&pmucru->pmu_clksel_con[6], CLK_PWM0_SEL_MASK | CLK_PWM0_DIV_MASK,
                    (CLK_PWM0_SEL_XIN24M << CLK_PWM0_SEL_SHIFT) | 0 << CLK_PWM0_SEL_SHIFT);
        }
        else
        {
            src_clk_div = RT_DIV_ROUND_UP(priv->ppll_hz, rate);
            RT_ASSERT(src_clk_div - 1 <= 127);
            rk_clrsetreg(&pmucru->pmu_clksel_con[6], CLK_PWM0_DIV_MASK | CLK_PWM0_DIV_MASK,
                    (CLK_PWM0_SEL_PPLL << CLK_PWM0_SEL_SHIFT) | (src_clk_div - 1) << CLK_PWM0_DIV_SHIFT);
        }
        break;
    default:
        return -RT_ERROR;
    }

    return pwm_get_pmuclk(priv, clk_id);
}

static int armclk_set_clk(struct rk_clk_priv *priv, rt_ubase_t hz)
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

    LOG_I("set cpu_freq to %lu", hz);

    rk_clrsetreg(&cru->clksel_con[0], CLK_CORE_PRE_SEL_MASK, (CLK_CORE_PRE_SEL_SRC << CLK_CORE_PRE_SEL_SHIFT));
    rk_clrsetreg(&cru->clksel_con[2],
            SCLK_CORE_PRE_SEL_MASK | SCLK_CORE_SRC_SEL_MASK | SCLK_CORE_SRC_DIV_MASK,
            (SCLK_CORE_PRE_SEL_SRC << SCLK_CORE_PRE_SEL_SHIFT) |
            (SCLK_CORE_SRC_SEL_APLL <<SCLK_CORE_SRC_SEL_SHIFT) |
            (1 << SCLK_CORE_SRC_DIV_SHIFT));

    /*
     * set up dependent divisors for DBG and ACLK clocks.
     */
    old_rate = rk_pll_get_rate(&pll_clks[apll], &priv->cru);
    if (old_rate > hz)
    {
        if (rk_pll_set_rate(&pll_clks[apll], priv->cru, hz))
        {
            LOG_E("cpu_rate adjust error");
            return -RT_ENOSYS;
        }
        rk_clrsetreg(&cru->clksel_con[3], GICCLK_CORE_DIV_MASK | ATCLK_CORE_DIV_MASK,
                rate->pclk_div << GICCLK_CORE_DIV_SHIFT | rate->pclk_div << ATCLK_CORE_DIV_SHIFT);
        rk_clrsetreg(&cru->clksel_con[4], PERIPHCLK_CORE_PRE_DIV_MASK | PCLK_CORE_PRE_DIV_MASK,
                rate->pclk_div << PCLK_CORE_PRE_DIV_SHIFT | rate->pclk_div << PERIPHCLK_CORE_PRE_DIV_SHIFT);
        rk_clrsetreg(&cru->clksel_con[5], ACLK_CORE_NDFT_DIV_MASK, rate->aclk_div << ACLK_CORE_NDFT_DIV_SHIFT);
    }
    else if (old_rate < hz)
    {
        rk_clrsetreg(&cru->clksel_con[3], GICCLK_CORE_DIV_MASK | ATCLK_CORE_DIV_MASK,
                rate->pclk_div << GICCLK_CORE_DIV_SHIFT | rate->pclk_div << ATCLK_CORE_DIV_SHIFT);
        rk_clrsetreg(&cru->clksel_con[4], PERIPHCLK_CORE_PRE_DIV_MASK | PCLK_CORE_PRE_DIV_MASK,
                rate->pclk_div << PCLK_CORE_PRE_DIV_SHIFT | rate->pclk_div << PERIPHCLK_CORE_PRE_DIV_SHIFT);
        rk_clrsetreg(&cru->clksel_con[5], ACLK_CORE_NDFT_DIV_MASK, rate->aclk_div << ACLK_CORE_NDFT_DIV_SHIFT);

        if (rk_pll_set_rate(&pll_clks[apll], priv->cru, hz))
        {
            LOG_E("cpu_rate adjust error");
            return -RT_ENOSYS;
        }
    }

    return 0;
}

static rt_ubase_t cpll_div_get_rate(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    int div, mask, shift, con;

    switch (clk_id)
    {
    case CPLL_500M:
        con = 78;
        mask = CPLL_500M_DIV_MASK;
        shift = CPLL_500M_DIV_SHIFT;
        break;
    case CPLL_333M:
        con = 79;
        mask = CPLL_333M_DIV_MASK;
        shift = CPLL_333M_DIV_SHIFT;
        break;
    case CPLL_250M:
        con = 79;
        mask = CPLL_250M_DIV_MASK;
        shift = CPLL_250M_DIV_SHIFT;
        break;
    case CPLL_125M:
        con = 80;
        mask = CPLL_125M_DIV_MASK;
        shift = CPLL_125M_DIV_SHIFT;
        break;
    case CPLL_100M:
        con = 82;
        mask = CPLL_100M_DIV_MASK;
        shift = CPLL_100M_DIV_SHIFT;
        break;
    case CPLL_62P5M:
        con = 80;
        mask = CPLL_62P5M_DIV_MASK;
        shift = CPLL_62P5M_DIV_SHIFT;
        break;
    case CPLL_50M:
        con = 81;
        mask = CPLL_50M_DIV_MASK;
        shift = CPLL_50M_DIV_SHIFT;
        break;
    case CPLL_25M:
        con = 81;
        mask = CPLL_25M_DIV_MASK;
        shift = CPLL_25M_DIV_SHIFT;
        break;
    default:
        return -RT_ERROR;
    }

    div = (HWREG32(&cru->clksel_con[con]) & mask) >> shift;
    return DIV_TO_RATE(priv->cpll_hz, div);
}

static rt_ubase_t cpll_div_set_rate(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int div, mask, shift, con;

    switch (clk_id)
    {
    case CPLL_500M:
        con = 78;
        mask = CPLL_500M_DIV_MASK;
        shift = CPLL_500M_DIV_SHIFT;
        break;
    case CPLL_333M:
        con = 79;
        mask = CPLL_333M_DIV_MASK;
        shift = CPLL_333M_DIV_SHIFT;
        break;
    case CPLL_250M:
        con = 79;
        mask = CPLL_250M_DIV_MASK;
        shift = CPLL_250M_DIV_SHIFT;
        break;
    case CPLL_125M:
        con = 80;
        mask = CPLL_125M_DIV_MASK;
        shift = CPLL_125M_DIV_SHIFT;
        break;
    case CPLL_100M:
        con = 82;
        mask = CPLL_100M_DIV_MASK;
        shift = CPLL_100M_DIV_SHIFT;
        break;
    case CPLL_62P5M:
        con = 80;
        mask = CPLL_62P5M_DIV_MASK;
        shift = CPLL_62P5M_DIV_SHIFT;
        break;
    case CPLL_50M:
        con = 81;
        mask = CPLL_50M_DIV_MASK;
        shift = CPLL_50M_DIV_SHIFT;
        break;
    case CPLL_25M:
        con = 81;
        mask = CPLL_25M_DIV_MASK;
        shift = CPLL_25M_DIV_SHIFT;
        break;
    default:
        return -RT_ERROR;
    }

    div = RT_DIV_ROUND_UP(priv->cpll_hz, rate);
    RT_ASSERT(div - 1 <= 31);
    rk_clrsetreg(&cru->clksel_con[con], mask, (div - 1) << shift);

    return cpll_div_get_rate(priv, clk_id);
}

static rt_ubase_t bus_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con, sel, rate;

    switch (clk_id)
    {
    case ACLK_BUS:
        con = HWREG32(&cru->clksel_con[50]);
        sel = (con & ACLK_BUS_SEL_MASK) >> ACLK_BUS_SEL_SHIFT;

        if (sel == ACLK_BUS_SEL_200M)
        {
            rate = 200 * MHZ;
        }
        else if (sel == ACLK_BUS_SEL_150M)
        {
            rate = 150 * MHZ;
        }
        else if (sel == ACLK_BUS_SEL_100M)
        {
            rate = 100 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    case PCLK_BUS:
    case PCLK_WDT_NS:
        con = HWREG32(&cru->clksel_con[50]);
        sel = (con & PCLK_BUS_SEL_MASK) >> PCLK_BUS_SEL_SHIFT;
        if (sel == PCLK_BUS_SEL_100M)
        {
            rate = 100 * MHZ;
        }
        else if (sel == PCLK_BUS_SEL_75M)
        {
            rate = 75 * MHZ;
        }
        else if (sel == PCLK_BUS_SEL_50M)
        {
            rate = 50 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    default:
        return -RT_ERROR;
    }

    return rate;
}

static rt_ubase_t bus_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (clk_id)
    {
    case ACLK_BUS:
        if (rate == 200 * MHZ)
        {
            src_clk = ACLK_BUS_SEL_200M;
        }
        else if (rate == 150 * MHZ)
        {
            src_clk = ACLK_BUS_SEL_150M;
        }
        else if (rate == 100 * MHZ)
        {
            src_clk = ACLK_BUS_SEL_100M;
        }
        else
        {
            src_clk = ACLK_BUS_SEL_24M;
        }
        rk_clrsetreg(&cru->clksel_con[50], ACLK_BUS_SEL_MASK, src_clk << ACLK_BUS_SEL_SHIFT);
        break;
    case PCLK_BUS:
    case PCLK_WDT_NS:
        if (rate == 100 * MHZ)
        {
            src_clk = PCLK_BUS_SEL_100M;
        }
        else if (rate == 75 * MHZ)
        {
            src_clk = PCLK_BUS_SEL_75M;
        }
        else if (rate == 50 * MHZ)
        {
            src_clk = PCLK_BUS_SEL_50M;
        }
        else
        {
            src_clk = PCLK_BUS_SEL_24M;
        }
        rk_clrsetreg(&cru->clksel_con[50], PCLK_BUS_SEL_MASK, src_clk << PCLK_BUS_SEL_SHIFT);
        break;

    default:
        return -RT_ENOSYS;
    }

    return bus_get_clk(priv, clk_id);
}

static rt_ubase_t perimid_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con, sel, rate;

    switch (clk_id)
    {
    case ACLK_PERIMID:
        con = HWREG32(&cru->clksel_con[10]);
        sel = (con & ACLK_PERIMID_SEL_MASK) >> ACLK_PERIMID_SEL_SHIFT;
        if (sel == ACLK_PERIMID_SEL_300M)
        {
            rate = 300 * MHZ;
        }
        else if (sel == ACLK_PERIMID_SEL_200M)
        {
            rate = 200 * MHZ;
        }
        else if (sel == ACLK_PERIMID_SEL_100M)
        {
            rate = 100 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    case HCLK_PERIMID:
        con = HWREG32(&cru->clksel_con[10]);
        sel = (con & HCLK_PERIMID_SEL_MASK) >> HCLK_PERIMID_SEL_SHIFT;
        if (sel == HCLK_PERIMID_SEL_150M)
        {
            rate = 150 * MHZ;
        }
        else if (sel == HCLK_PERIMID_SEL_100M)
        {
            rate = 100 * MHZ;
        }
        else if (sel == HCLK_PERIMID_SEL_75M)
        {
            rate = 75 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    default:
        return -RT_ERROR;
    }

    return rate;
}

static rt_ubase_t perimid_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (clk_id)
    {
    case ACLK_PERIMID:
        if (rate == 300 * MHZ)
        {
            src_clk = ACLK_PERIMID_SEL_300M;
        }
        else if (rate == 200 * MHZ)
        {
            src_clk = ACLK_PERIMID_SEL_200M;
        }
        else if (rate == 100 * MHZ)
        {
            src_clk = ACLK_PERIMID_SEL_100M;
        }
        else
        {
            src_clk = ACLK_PERIMID_SEL_24M;
        }
        rk_clrsetreg(&cru->clksel_con[10], ACLK_PERIMID_SEL_MASK, src_clk << ACLK_PERIMID_SEL_SHIFT);
        break;
    case HCLK_PERIMID:
        if (rate == 150 * MHZ)
        {
            src_clk = HCLK_PERIMID_SEL_150M;
        }
        else if (rate == 100 * MHZ)
        {
            src_clk = HCLK_PERIMID_SEL_100M;
        }
        else if (rate == 75 * MHZ)
        {
            src_clk = HCLK_PERIMID_SEL_75M;
        }
        else
        {
            src_clk = HCLK_PERIMID_SEL_24M;
        }
        rk_clrsetreg(&cru->clksel_con[10], HCLK_PERIMID_SEL_MASK, src_clk << HCLK_PERIMID_SEL_SHIFT);
        break;

    default:
        return -RT_ENOSYS;
    }

    return perimid_get_clk(priv, clk_id);
}

static rt_ubase_t top_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con, sel, rate;

    switch (clk_id)
    {
    case ACLK_TOP_HIGH:
        con = HWREG32(&cru->clksel_con[73]);
        sel = (con & ACLK_TOP_HIGH_SEL_MASK) >> ACLK_TOP_HIGH_SEL_SHIFT;
        if (sel == ACLK_TOP_HIGH_SEL_500M)
        {
            rate = 500 * MHZ;
        }
        else if (sel == ACLK_TOP_HIGH_SEL_400M)
        {
            rate = 400 * MHZ;
        }
        else if (sel == ACLK_TOP_HIGH_SEL_300M)
        {
            rate = 300 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    case ACLK_TOP_LOW:
        con = HWREG32(&cru->clksel_con[73]);
        sel = (con & ACLK_TOP_LOW_SEL_MASK) >> ACLK_TOP_LOW_SEL_SHIFT;
        if (sel == ACLK_TOP_LOW_SEL_400M)
        {
            rate = 400 * MHZ;
        }
        else if (sel == ACLK_TOP_LOW_SEL_300M)
        {
            rate = 300 * MHZ;
        }
        else if (sel == ACLK_TOP_LOW_SEL_200M)
        {
            rate = 200 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    case HCLK_TOP:
        con = HWREG32(&cru->clksel_con[73]);
        sel = (con & HCLK_TOP_SEL_MASK) >> HCLK_TOP_SEL_SHIFT;
        if (sel == HCLK_TOP_SEL_150M)
        {
            rate = 150 * MHZ;
        }
        else if (sel == HCLK_TOP_SEL_100M)
        {
            rate = 100 * MHZ;
        }
        else if (sel == HCLK_TOP_SEL_75M)
        {
            rate = 75 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    case PCLK_TOP:
        con = HWREG32(&cru->clksel_con[73]);
        sel = (con & PCLK_TOP_SEL_MASK) >> PCLK_TOP_SEL_SHIFT;
        if (sel == PCLK_TOP_SEL_100M)
        {
            rate = 100 * MHZ;
        }
        else if (sel == PCLK_TOP_SEL_75M)
        {
            rate = 75 * MHZ;
        }
        else if (sel == PCLK_TOP_SEL_50M)
        {
            rate = 50 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    default:
        return -RT_ERROR;
    }

    return rate;
}

static rt_ubase_t top_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (clk_id)
    {
    case ACLK_TOP_HIGH:
        if (rate == 500 * MHZ)
        {
            src_clk = ACLK_TOP_HIGH_SEL_500M;
        }
        else if (rate == 400 * MHZ)
        {
            src_clk = ACLK_TOP_HIGH_SEL_400M;
        }
        else if (rate == 300 * MHZ)
        {
            src_clk = ACLK_TOP_HIGH_SEL_300M;
        }
        else
        {
            src_clk = ACLK_TOP_HIGH_SEL_24M;
        }
        rk_clrsetreg(&cru->clksel_con[73], ACLK_TOP_HIGH_SEL_MASK, src_clk << ACLK_TOP_HIGH_SEL_SHIFT);
        break;
    case ACLK_TOP_LOW:
        if (rate == 400 * MHZ)
        {
            src_clk = ACLK_TOP_LOW_SEL_400M;
        }
        else if (rate == 300 * MHZ)
        {
            src_clk = ACLK_TOP_LOW_SEL_300M;
        }
        else if (rate == 200 * MHZ)
        {
            src_clk = ACLK_TOP_LOW_SEL_200M;
        }
        else
        {
            src_clk = ACLK_TOP_LOW_SEL_24M;
        }
        rk_clrsetreg(&cru->clksel_con[73], ACLK_TOP_LOW_SEL_MASK, src_clk << ACLK_TOP_LOW_SEL_SHIFT);
        break;
    case HCLK_TOP:
        if (rate == 150 * MHZ)
        {
            src_clk = HCLK_TOP_SEL_150M;
        }
        else if (rate == 100 * MHZ)
        {
            src_clk = HCLK_TOP_SEL_100M;
        }
        else if (rate == 75 * MHZ)
        {
            src_clk = HCLK_TOP_SEL_75M;
        }
        else
        {
            src_clk = HCLK_TOP_SEL_24M;
        }
        rk_clrsetreg(&cru->clksel_con[73], HCLK_TOP_SEL_MASK, src_clk << HCLK_TOP_SEL_SHIFT);
        break;
    case PCLK_TOP:
        if (rate == 100 * MHZ)
        {
            src_clk = PCLK_TOP_SEL_100M;
        }
        else if (rate == 75 * MHZ)
        {
            src_clk = PCLK_TOP_SEL_75M;
        }
        else if (rate == 50 * MHZ)
        {
            src_clk = PCLK_TOP_SEL_50M;
        }
        else
        {
            src_clk = PCLK_TOP_SEL_24M;
        }
        rk_clrsetreg(&cru->clksel_con[73], PCLK_TOP_SEL_MASK, src_clk << PCLK_TOP_SEL_SHIFT);
        break;

    default:
        return -RT_ENOSYS;
    }

    return top_get_clk(priv, clk_id);
}

static rt_ubase_t i2c_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;
    rt_ubase_t rate;

    switch (clk_id)
    {
    case CLK_I2C1:
    case CLK_I2C2:
    case CLK_I2C3:
    case CLK_I2C4:
    case CLK_I2C5:
        con = HWREG32(&cru->clksel_con[71]);
        sel = (con & CLK_I2C_SEL_MASK) >> CLK_I2C_SEL_SHIFT;
        if (sel == CLK_I2C_SEL_200M)
        {
            rate = 200 * MHZ;
        }
        else if (sel == CLK_I2C_SEL_100M)
        {
            rate = 100 * MHZ;
        }
        else if (sel == CLK_I2C_SEL_CPLL_100M)
        {
            rate = 100 * MHZ;
        }
        else
        {
            rate = OSC_HZ;
        }
        break;
    default:
        return -RT_ERROR;
    }

    return rate;
}

static rt_ubase_t i2c_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    if (rate == 200 * MHZ)
    {
        src_clk = CLK_I2C_SEL_200M;
    }
    else if (rate == 100 * MHZ)
    {
        src_clk = CLK_I2C_SEL_100M;
    }
    else
    {
        src_clk = CLK_I2C_SEL_24M;
    }

    switch (clk_id)
    {
    case CLK_I2C1:
    case CLK_I2C2:
    case CLK_I2C3:
    case CLK_I2C4:
    case CLK_I2C5:
        rk_clrsetreg(&cru->clksel_con[71], CLK_I2C_SEL_MASK, src_clk << CLK_I2C_SEL_SHIFT);
        break;
    default:
        return -RT_ERROR;
    }

    return i2c_get_clk(priv, clk_id);
}

static rt_ubase_t spi_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[72]);

    switch (clk_id)
    {
    case CLK_SPI0:
        sel = (con & CLK_SPI0_SEL_MASK) >> CLK_SPI0_SEL_SHIFT;
        break;
    case CLK_SPI1:
        sel = (con & CLK_SPI1_SEL_MASK) >> CLK_SPI1_SEL_SHIFT;
        break;
    case CLK_SPI2:
        sel = (con & CLK_SPI2_SEL_MASK) >> CLK_SPI2_SEL_SHIFT;
        break;
    case CLK_SPI3:
        sel = (con & CLK_SPI3_SEL_MASK) >> CLK_SPI3_SEL_SHIFT;
        break;
    default:
        return -RT_ERROR;
    }

    switch (sel)
    {
    case CLK_SPI_SEL_200M:
        return 200 * MHZ;
    case CLK_SPI_SEL_24M:
        return OSC_HZ;
    case CLK_SPI_SEL_CPLL_100M:
        return 100 * MHZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t spi_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    if (rate == 200 * MHZ)
    {
        src_clk = CLK_SPI_SEL_200M;
    }
    else if (rate == 100 * MHZ)
    {
        src_clk = CLK_SPI_SEL_CPLL_100M;
    }
    else
    {
        src_clk = CLK_SPI_SEL_24M;
    }

    switch (clk_id)
    {
    case CLK_SPI0:
        rk_clrsetreg(&cru->clksel_con[72], CLK_SPI0_SEL_MASK, src_clk << CLK_SPI0_SEL_SHIFT);
        break;
    case CLK_SPI1:
        rk_clrsetreg(&cru->clksel_con[72], CLK_SPI1_SEL_MASK, src_clk << CLK_SPI1_SEL_SHIFT);
        break;
    case CLK_SPI2:
        rk_clrsetreg(&cru->clksel_con[72], CLK_SPI2_SEL_MASK, src_clk << CLK_SPI2_SEL_SHIFT);
        break;
    case CLK_SPI3:
        rk_clrsetreg(&cru->clksel_con[72], CLK_SPI3_SEL_MASK, src_clk << CLK_SPI3_SEL_SHIFT);
        break;
    default:
        return -RT_ERROR;
    }

    return spi_get_clk(priv, clk_id);
}

static rt_ubase_t pwm_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[72]);

    switch (clk_id)
    {
    case CLK_PWM1:
        sel = (con & CLK_PWM1_SEL_MASK) >> CLK_PWM3_SEL_SHIFT;
        break;
    case CLK_PWM2:
        sel = (con & CLK_PWM2_SEL_MASK) >> CLK_PWM2_SEL_SHIFT;
        break;
    case CLK_PWM3:
        sel = (con & CLK_PWM3_SEL_MASK) >> CLK_PWM3_SEL_SHIFT;
        break;
    default:
        return -RT_ERROR;
    }

    switch (sel)
    {
    case CLK_PWM_SEL_100M:
        return 100 * MHZ;
    case CLK_PWM_SEL_24M:
        return OSC_HZ;
    case CLK_PWM_SEL_CPLL_100M:
        return 100 * MHZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t pwm_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    if (rate == 100 * MHZ)
    {
        src_clk = CLK_PWM_SEL_100M;
    }
    else
    {
        src_clk = CLK_PWM_SEL_24M;
    }

    switch (clk_id)
    {
    case CLK_PWM1:
        rk_clrsetreg(&cru->clksel_con[72], CLK_PWM1_SEL_MASK, src_clk << CLK_PWM1_SEL_SHIFT);
        break;
    case CLK_PWM2:
        rk_clrsetreg(&cru->clksel_con[72], CLK_PWM2_SEL_MASK, src_clk << CLK_PWM2_SEL_SHIFT);
        break;
    case CLK_PWM3:
        rk_clrsetreg(&cru->clksel_con[72], CLK_PWM3_SEL_MASK, src_clk << CLK_PWM3_SEL_SHIFT);
        break;
    default:
        return -RT_ERROR;
    }

    return pwm_get_clk(priv, clk_id);
}

static rt_ubase_t adc_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, sel, con, prate;

    switch (clk_id)
    {
    case CLK_SARADC:
        return OSC_HZ;
    case CLK_TSADC_TSEN:
        con = HWREG32(&cru->clksel_con[51]);
        div = (con & CLK_TSADC_TSEN_DIV_MASK) >> CLK_TSADC_TSEN_DIV_SHIFT;
        sel = (con & CLK_TSADC_TSEN_SEL_MASK) >> CLK_TSADC_TSEN_SEL_SHIFT;
        if (sel == CLK_TSADC_TSEN_SEL_24M)
        {
            prate = OSC_HZ;
        }
        else
        {
            prate = 100 * MHZ;
        }
        return DIV_TO_RATE(prate, div);
    case CLK_TSADC:
        con = HWREG32(&cru->clksel_con[51]);
        div = (con & CLK_TSADC_DIV_MASK) >> CLK_TSADC_DIV_SHIFT;
        prate = adc_get_clk(priv, CLK_TSADC_TSEN);
        return DIV_TO_RATE(prate, div);
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t adc_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;
    rt_ubase_t prate = 0;

    switch (clk_id)
    {
    case CLK_SARADC:
        return OSC_HZ;
    case CLK_TSADC_TSEN:
        if (!(OSC_HZ % rate))
        {
            src_clk_div = RT_DIV_ROUND_UP(OSC_HZ, rate);
            RT_ASSERT(src_clk_div - 1 <= 7);
            rk_clrsetreg(&cru->clksel_con[51], CLK_TSADC_TSEN_SEL_MASK | CLK_TSADC_TSEN_DIV_MASK,
                    (CLK_TSADC_TSEN_SEL_24M << CLK_TSADC_TSEN_SEL_SHIFT) |
                    (src_clk_div - 1) << CLK_TSADC_TSEN_DIV_SHIFT);
        }
        else
        {
            src_clk_div = RT_DIV_ROUND_UP(100 * MHZ, rate);
            RT_ASSERT(src_clk_div - 1 <= 7);
            rk_clrsetreg(&cru->clksel_con[51], CLK_TSADC_TSEN_SEL_MASK | CLK_TSADC_TSEN_DIV_MASK,
                    (CLK_TSADC_TSEN_SEL_100M << CLK_TSADC_TSEN_SEL_SHIFT) |
                    (src_clk_div - 1) << CLK_TSADC_TSEN_DIV_SHIFT);
        }
        break;
    case CLK_TSADC:
            prate = adc_get_clk(priv, CLK_TSADC_TSEN);
            src_clk_div = RT_DIV_ROUND_UP(prate, rate);
            RT_ASSERT(src_clk_div - 1 <= 128);
            rk_clrsetreg(&cru->clksel_con[51], CLK_TSADC_DIV_MASK, (src_clk_div - 1) << CLK_TSADC_DIV_SHIFT);
        break;
    default:
        return -RT_ERROR;
    }
    return adc_get_clk(priv, clk_id);
}

static rt_ubase_t crypto_get_rate(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    switch (clk_id)
    {
    case ACLK_SECURE_FLASH:
    case ACLK_CRYPTO_NS:
        con = HWREG32(&cru->clksel_con[27]);
        sel = (con & ACLK_SECURE_FLASH_SEL_MASK) >> ACLK_SECURE_FLASH_SEL_SHIFT;
        if (sel == ACLK_SECURE_FLASH_SEL_200M)
        {
            return 200 * MHZ;
        }
        else if (sel == ACLK_SECURE_FLASH_SEL_150M)
        {
            return 150 * MHZ;
        }
        else if (sel == ACLK_SECURE_FLASH_SEL_100M)
        {
            return 100 * MHZ;
        }
        else
        {
            return 24 * MHZ;
        }
    case HCLK_SECURE_FLASH:
    case HCLK_CRYPTO_NS:
    case CLK_CRYPTO_NS_RNG:
        con = HWREG32(&cru->clksel_con[27]);
        sel = (con & HCLK_SECURE_FLASH_SEL_MASK) >> HCLK_SECURE_FLASH_SEL_SHIFT;
        if (sel == HCLK_SECURE_FLASH_SEL_150M)
        {
            return 150 * MHZ;
        }
        else if (sel == HCLK_SECURE_FLASH_SEL_100M)
        {
            return 100 * MHZ;
        }
        else if (sel == HCLK_SECURE_FLASH_SEL_75M)
        {
            return 75 * MHZ;
        }
        else
        {
            return 24 * MHZ;
        }
    case CLK_CRYPTO_NS_CORE:
        con = HWREG32(&cru->clksel_con[27]);
        sel = (con & CLK_CRYPTO_CORE_SEL_MASK) >> CLK_CRYPTO_CORE_SEL_SHIFT;
        if (sel == CLK_CRYPTO_CORE_SEL_200M)
        {
            return 200 * MHZ;
        }
        else if (sel == CLK_CRYPTO_CORE_SEL_150M)
        {
            return 150 * MHZ;
        }
        else
        {
            return 100 * MHZ;
        }
    case CLK_CRYPTO_NS_PKA:
        con = HWREG32(&cru->clksel_con[27]);
        sel = (con & CLK_CRYPTO_PKA_SEL_MASK) >> CLK_CRYPTO_PKA_SEL_SHIFT;
        if (sel == CLK_CRYPTO_PKA_SEL_300M)
        {
            return 300 * MHZ;
        }
        else if (sel == CLK_CRYPTO_PKA_SEL_200M)
        {
            return 200 * MHZ;
        }
        else
        {
            return 100 * MHZ;
        }
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t crypto_set_rate(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t src_clk, mask, shift;

    switch (clk_id)
    {
    case ACLK_SECURE_FLASH:
    case ACLK_CRYPTO_NS:
        mask = ACLK_SECURE_FLASH_SEL_MASK;
        shift = ACLK_SECURE_FLASH_SEL_SHIFT;
        if (rate == 200 * MHZ)
        {
            src_clk = ACLK_SECURE_FLASH_SEL_200M;
        }
        else if (rate == 150 * MHZ)
        {
            src_clk = ACLK_SECURE_FLASH_SEL_150M;
        }
        else if (rate == 100 * MHZ)
        {
            src_clk = ACLK_SECURE_FLASH_SEL_100M;
        }
        else
        {
            src_clk = ACLK_SECURE_FLASH_SEL_24M;
        }
        break;
    case HCLK_SECURE_FLASH:
    case HCLK_CRYPTO_NS:
    case CLK_CRYPTO_NS_RNG:
        mask = HCLK_SECURE_FLASH_SEL_MASK;
        shift = HCLK_SECURE_FLASH_SEL_SHIFT;
        if (rate == 150 * MHZ)
        {
            src_clk = HCLK_SECURE_FLASH_SEL_150M;
        }
        else if (rate == 100 * MHZ)
        {
            src_clk = HCLK_SECURE_FLASH_SEL_100M;
        }
        else if (rate == 75 * MHZ)
        {
            src_clk = HCLK_SECURE_FLASH_SEL_75M;
        }
        else
        {
            src_clk = HCLK_SECURE_FLASH_SEL_24M;
        }
        break;
    case CLK_CRYPTO_NS_CORE:
        mask = CLK_CRYPTO_CORE_SEL_MASK;
        shift = CLK_CRYPTO_CORE_SEL_SHIFT;
        if (rate == 200 * MHZ)
        {
            src_clk = CLK_CRYPTO_CORE_SEL_200M;
        }
        else if (rate == 150 * MHZ)
        {
            src_clk = CLK_CRYPTO_CORE_SEL_150M;
        }
        else
        {
            src_clk = CLK_CRYPTO_CORE_SEL_100M;
        }
        break;
    case CLK_CRYPTO_NS_PKA:
        mask = CLK_CRYPTO_PKA_SEL_MASK;
        shift = CLK_CRYPTO_PKA_SEL_SHIFT;
        if (rate == 300 * MHZ)
        {
            src_clk = CLK_CRYPTO_PKA_SEL_300M;
        }
        else if (rate == 200 * MHZ)
        {
            src_clk = CLK_CRYPTO_PKA_SEL_200M;
        }
        else
        {
            src_clk = CLK_CRYPTO_PKA_SEL_100M;
        }
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[27], mask, src_clk << shift);

    return crypto_get_rate(priv, clk_id);
}

static rt_ubase_t sdmmc_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    switch (clk_id)
    {
    case HCLK_SDMMC0:
    case CLK_SDMMC0:
        con = HWREG32(&cru->clksel_con[30]);
        sel = (con & CLK_SDMMC0_SEL_MASK) >> CLK_SDMMC0_SEL_SHIFT;
        break;
    case CLK_SDMMC1:
        con = HWREG32(&cru->clksel_con[30]);
        sel = (con & CLK_SDMMC1_SEL_MASK) >> CLK_SDMMC1_SEL_SHIFT;
        break;
    case CLK_SDMMC2:
        con = HWREG32(&cru->clksel_con[32]);
        sel = (con & CLK_SDMMC2_SEL_MASK) >> CLK_SDMMC2_SEL_SHIFT;
        break;
    default:
        return -RT_ERROR;
    }

    switch (sel)
    {
    case CLK_SDMMC_SEL_24M:
        return OSC_HZ;
    case CLK_SDMMC_SEL_400M:
        return 400 * MHZ;
    case CLK_SDMMC_SEL_300M:
        return 300 * MHZ;
    case CLK_SDMMC_SEL_100M:
        return 100 * MHZ;
    case CLK_SDMMC_SEL_50M:
        return 50 * MHZ;
    case CLK_SDMMC_SEL_750K:
        return 750 * KHZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t sdmmc_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (rate)
    {
    case OSC_HZ:
        src_clk = CLK_SDMMC_SEL_24M;
        break;
    case 400 * MHZ:
        src_clk = CLK_SDMMC_SEL_400M;
        break;
    case 300 * MHZ:
        src_clk = CLK_SDMMC_SEL_300M;
        break;
    case 100 * MHZ:
        src_clk = CLK_SDMMC_SEL_100M;
        break;
    case 52 * MHZ:
    case 50 * MHZ:
        src_clk = CLK_SDMMC_SEL_50M;
        break;
    case 750 * KHZ:
    case 400 * KHZ:
        src_clk = CLK_SDMMC_SEL_750K;
        break;
    default:
        return -RT_ERROR;
    }

    switch (clk_id)
    {
    case HCLK_SDMMC0:
    case CLK_SDMMC0:
        rk_clrsetreg(&cru->clksel_con[30], CLK_SDMMC0_SEL_MASK, src_clk << CLK_SDMMC0_SEL_SHIFT);
        break;
    case CLK_SDMMC1:
        rk_clrsetreg(&cru->clksel_con[30], CLK_SDMMC1_SEL_MASK, src_clk << CLK_SDMMC1_SEL_SHIFT);
        break;
    case CLK_SDMMC2:
        rk_clrsetreg(&cru->clksel_con[32], CLK_SDMMC2_SEL_MASK, src_clk << CLK_SDMMC2_SEL_SHIFT);
        break;
    default:
        return -RT_ERROR;
    }

    return sdmmc_get_clk(priv, clk_id);
}

static rt_ubase_t sfc_get_clk(struct rk_clk_priv *priv)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[28]);
    sel = (con & SCLK_SFC_SEL_MASK) >> SCLK_SFC_SEL_SHIFT;

    switch (sel)
    {
    case SCLK_SFC_SEL_24M:
        return OSC_HZ;
    case SCLK_SFC_SEL_50M:
        return 50 * MHZ;
    case SCLK_SFC_SEL_75M:
        return 75 * MHZ;
    case SCLK_SFC_SEL_100M:
        return 100 * MHZ;
    case SCLK_SFC_SEL_125M:
        return 125 * MHZ;
    case SCLK_SFC_SEL_150M:
        return 150 * KHZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t sfc_set_clk(struct rk_clk_priv *priv, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (rate)
    {
    case OSC_HZ:
        src_clk = SCLK_SFC_SEL_24M;
        break;
    case 50 * MHZ:
        src_clk = SCLK_SFC_SEL_50M;
        break;
    case 75 * MHZ:
        src_clk = SCLK_SFC_SEL_75M;
        break;
    case 100 * MHZ:
        src_clk = SCLK_SFC_SEL_100M;
        break;
    case 125 * MHZ:
        src_clk = SCLK_SFC_SEL_125M;
        break;
    case 150 * KHZ:
        src_clk = SCLK_SFC_SEL_150M;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[28], SCLK_SFC_SEL_MASK, src_clk << SCLK_SFC_SEL_SHIFT);

    return sfc_get_clk(priv);
}

static rt_ubase_t nand_get_clk(struct rk_clk_priv *priv)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[28]);
    sel = (con & NCLK_NANDC_SEL_MASK) >> NCLK_NANDC_SEL_SHIFT;

    switch (sel)
    {
    case NCLK_NANDC_SEL_200M:
        return 200 * MHZ;
    case NCLK_NANDC_SEL_150M:
        return 150 * MHZ;
    case NCLK_NANDC_SEL_100M:
        return 100 * MHZ;
    case NCLK_NANDC_SEL_24M:
        return OSC_HZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t nand_set_clk(struct rk_clk_priv *priv, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (rate)
    {
    case OSC_HZ:
        src_clk = NCLK_NANDC_SEL_24M;
        break;
    case 100 * MHZ:
        src_clk = NCLK_NANDC_SEL_100M;
        break;
    case 150 * MHZ:
        src_clk = NCLK_NANDC_SEL_150M;
        break;
    case 200 * MHZ:
        src_clk = NCLK_NANDC_SEL_200M;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[28], NCLK_NANDC_SEL_MASK, src_clk << NCLK_NANDC_SEL_SHIFT);

    return nand_get_clk(priv);
}

static rt_ubase_t emmc_get_clk(struct rk_clk_priv *priv)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[28]);
    sel = (con & CCLK_EMMC_SEL_MASK) >> CCLK_EMMC_SEL_SHIFT;

    switch (sel)
    {
    case CCLK_EMMC_SEL_200M:
        return 200 * MHZ;
    case CCLK_EMMC_SEL_150M:
        return 150 * MHZ;
    case CCLK_EMMC_SEL_100M:
        return 100 * MHZ;
    case CCLK_EMMC_SEL_50M:
        return 50 * MHZ;
    case CCLK_EMMC_SEL_375K:
        return 375 * KHZ;
    case CCLK_EMMC_SEL_24M:
        return OSC_HZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t emmc_set_clk(struct rk_clk_priv *priv, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (rate)
    {
    case OSC_HZ:
        src_clk = CCLK_EMMC_SEL_24M;
        break;
    case 52 * MHZ:
    case 50 * MHZ:
        src_clk = CCLK_EMMC_SEL_50M;
        break;
    case 100 * MHZ:
        src_clk = CCLK_EMMC_SEL_100M;
        break;
    case 150 * MHZ:
        src_clk = CCLK_EMMC_SEL_150M;
        break;
    case 200 * MHZ:
        src_clk = CCLK_EMMC_SEL_200M;
        break;
    case 400 * KHZ:
    case 375 * KHZ:
        src_clk = CCLK_EMMC_SEL_375K;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[28], CCLK_EMMC_SEL_MASK, src_clk << CCLK_EMMC_SEL_SHIFT);

    return emmc_get_clk(priv);
}

static rt_ubase_t emmc_get_bclk(struct rk_clk_priv *priv)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[28]);
    sel = (con & BCLK_EMMC_SEL_MASK) >> BCLK_EMMC_SEL_SHIFT;

    switch (sel)
    {
    case BCLK_EMMC_SEL_200M:
        return 200 * MHZ;
    case BCLK_EMMC_SEL_150M:
        return 150 * MHZ;
    case BCLK_EMMC_SEL_125M:
        return 125 * MHZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t emmc_set_bclk(struct rk_clk_priv *priv, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (rate)
    {
    case 200 * MHZ:
        src_clk = BCLK_EMMC_SEL_200M;
        break;
    case 150 * MHZ:
        src_clk = BCLK_EMMC_SEL_150M;
        break;
    case 125 * MHZ:
        src_clk = BCLK_EMMC_SEL_125M;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[28], BCLK_EMMC_SEL_MASK, src_clk << BCLK_EMMC_SEL_SHIFT);

    return emmc_get_bclk(priv);
}

static rt_ubase_t aclk_vop_get_clk(struct rk_clk_priv *priv)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t div, sel, con, parent;

    con = HWREG32(&cru->clksel_con[38]);
    div = (con & ACLK_VOP_PRE_DIV_MASK) >> ACLK_VOP_PRE_DIV_SHIFT;
    sel = (con & ACLK_VOP_PRE_SEL_MASK) >> ACLK_VOP_PRE_SEL_SHIFT;

    if (sel == ACLK_VOP_PRE_SEL_GPLL)
    {
        parent = priv->gpll_hz;
    }
    else if (sel == ACLK_VOP_PRE_SEL_CPLL)
    {
        parent = priv->cpll_hz;
    }
    else if (sel == ACLK_VOP_PRE_SEL_VPLL)
    {
        parent = priv->vpll_hz;
    }
    else
    {
        parent = priv->hpll_hz;
    }

    return DIV_TO_RATE(parent, div);
}

static rt_ubase_t aclk_vop_set_clk(struct rk_clk_priv *priv, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div, src_clk_mux;

    if ((priv->cpll_hz % rate) == 0)
    {
        src_clk_div = RT_DIV_ROUND_UP(priv->cpll_hz, rate);
        src_clk_mux = ACLK_VOP_PRE_SEL_CPLL;
    }
    else
    {
        src_clk_div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
        src_clk_mux = ACLK_VOP_PRE_SEL_GPLL;
    }

    RT_ASSERT(src_clk_div - 1 <= 31);
    rk_clrsetreg(&cru->clksel_con[38], ACLK_VOP_PRE_SEL_MASK | ACLK_VOP_PRE_DIV_MASK,
            src_clk_mux << ACLK_VOP_PRE_SEL_SHIFT | (src_clk_div - 1) << ACLK_VOP_PRE_DIV_SHIFT);

    return aclk_vop_get_clk(priv);
}

static rt_ubase_t dclk_vop_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t conid, div, sel, con, parent;

    switch (clk_id)
    {
    case DCLK_VOP0:
        conid = 39;
        break;
    case DCLK_VOP1:
        conid = 40;
        break;
    case DCLK_VOP2:
        conid = 41;
        break;
    default:
        return -RT_ERROR;
    }

    con = HWREG32(&cru->clksel_con[conid]);
    div = (con & DCLK0_VOP_DIV_MASK) >> DCLK0_VOP_DIV_SHIFT;
    sel = (con & DCLK0_VOP_SEL_MASK) >> DCLK0_VOP_SEL_SHIFT;

    if (sel == DCLK_VOP_SEL_HPLL)
    {
        parent = pmu_pll_get_rate(hpll);
    }
    else if (sel == DCLK_VOP_SEL_VPLL)
    {
        parent = rk_pll_get_rate(&pll_clks[vpll], &priv->cru);
    }
    else if (sel == DCLK_VOP_SEL_GPLL)
    {
        parent = priv->gpll_hz;
    }
    else if (sel == DCLK_VOP_SEL_CPLL)
    {
        parent = priv->cpll_hz;
    }
    else
    {
        return -RT_ERROR;
    }

    return DIV_TO_RATE(parent, div);
}

#define VOP_PLL_LIMIT_FREQ 600000000

static rt_ubase_t dclk_vop_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    rt_ubase_t pll_rate, now, best_rate = 0;
    rt_uint32_t i, conid, con, sel, div, best_div = 0, best_sel = 0;

    switch (clk_id)
    {
    case DCLK_VOP0:
        conid = 39;
        break;
    case DCLK_VOP1:
        conid = 40;
        break;
    case DCLK_VOP2:
        conid = 41;
        break;
    default:
        return -RT_ERROR;
    }

    con = HWREG32(&cru->clksel_con[conid]);
    sel = (con & DCLK0_VOP_SEL_MASK) >> DCLK0_VOP_SEL_SHIFT;

    if (sel == DCLK_VOP_SEL_HPLL)
    {
        div = 1;
        rk_clrsetreg(&cru->clksel_con[conid], DCLK0_VOP_DIV_MASK | DCLK0_VOP_SEL_MASK,
                (DCLK_VOP_SEL_HPLL << DCLK0_VOP_SEL_SHIFT) | ((div - 1) << DCLK0_VOP_DIV_SHIFT));
        pmu_pll_set_rate(hpll, div * rate);
    }
    else if (sel == DCLK_VOP_SEL_VPLL)
    {
        div = RT_DIV_ROUND_UP(VOP_PLL_LIMIT_FREQ, rate);
        rk_clrsetreg(&cru->clksel_con[conid], DCLK0_VOP_DIV_MASK | DCLK0_VOP_SEL_MASK,
                (DCLK_VOP_SEL_VPLL << DCLK0_VOP_SEL_SHIFT) | ((div - 1) << DCLK0_VOP_DIV_SHIFT));
        rk_pll_set_rate(&pll_clks[vpll], priv->cru, div * rate);
    }
    else
    {
        for (i = 0; i <= DCLK_VOP_SEL_CPLL; i++)
        {
            switch (i)
            {
            case DCLK_VOP_SEL_GPLL:
                pll_rate = priv->gpll_hz;
                break;
            case DCLK_VOP_SEL_CPLL:
                pll_rate = priv->cpll_hz;
                break;
            default:
                return -RT_ENOSYS;
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

        if (best_rate)
        {
            rk_clrsetreg(&cru->clksel_con[conid], DCLK0_VOP_DIV_MASK | DCLK0_VOP_SEL_MASK,
                    best_sel << DCLK0_VOP_SEL_SHIFT | (best_div - 1) << DCLK0_VOP_DIV_SHIFT);
        }
        else
        {
            return -RT_ENOSYS;
        }
    }
    return dclk_vop_get_clk(priv, clk_id);
}

static rt_ubase_t gmac_src_get_clk(struct rk_clk_priv *priv, rt_ubase_t mac_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[31 + mac_id * 2]);
    sel = (con & CLK_MAC0_2TOP_SEL_MASK) >> CLK_MAC0_2TOP_SEL_SHIFT;

    switch (sel)
    {
    case CLK_MAC0_2TOP_SEL_125M:
        return 125 * MHZ;
    case CLK_MAC0_2TOP_SEL_50M:
        return 50 * MHZ;
    case CLK_MAC0_2TOP_SEL_25M:
        return 25 * MHZ;
    case CLK_MAC0_2TOP_SEL_PPLL:
        return pmu_pll_get_rate(hpll);
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t gmac_src_set_clk(struct rk_clk_priv *priv, rt_ubase_t mac_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (rate)
    {
    case 125 * MHZ:
        src_clk = CLK_MAC0_2TOP_SEL_125M;
        break;
    case 50 * MHZ:
        src_clk = CLK_MAC0_2TOP_SEL_50M;
        break;
    case 25 * MHZ:
        src_clk = CLK_MAC0_2TOP_SEL_25M;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2], CLK_MAC0_2TOP_SEL_MASK, src_clk << CLK_MAC0_2TOP_SEL_SHIFT);

    return gmac_src_get_clk(priv, mac_id);
}

static rt_ubase_t gmac_out_get_clk(struct rk_clk_priv *priv, rt_ubase_t mac_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[31 + mac_id * 2]);
    sel = (con & CLK_MAC0_OUT_SEL_MASK) >> CLK_MAC0_OUT_SEL_SHIFT;

    switch (sel)
    {
    case CLK_MAC0_OUT_SEL_125M:
        return 125 * MHZ;
    case CLK_MAC0_OUT_SEL_50M:
        return 50 * MHZ;
    case CLK_MAC0_OUT_SEL_25M:
        return 25 * MHZ;
    case CLK_MAC0_OUT_SEL_24M:
        return OSC_HZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t gmac_out_set_clk(struct rk_clk_priv *priv, rt_ubase_t mac_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (rate)
    {
    case 125 * MHZ:
        src_clk = CLK_MAC0_OUT_SEL_125M;
        break;
    case 50 * MHZ:
        src_clk = CLK_MAC0_OUT_SEL_50M;
        break;
    case 25 * MHZ:
        src_clk = CLK_MAC0_OUT_SEL_25M;
        break;
    case 24 * MHZ:
        src_clk = CLK_MAC0_OUT_SEL_24M;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2], CLK_MAC0_OUT_SEL_MASK, src_clk << CLK_MAC0_OUT_SEL_SHIFT);

    return gmac_out_get_clk(priv, mac_id);
}

static rt_ubase_t gmac_ptp_ref_get_clk(struct rk_clk_priv *priv, rt_ubase_t mac_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[31 + mac_id * 2]);
    sel = (con & CLK_GMAC0_PTP_REF_SEL_MASK) >> CLK_GMAC0_PTP_REF_SEL_SHIFT;

    switch (sel)
    {
    case CLK_GMAC0_PTP_REF_SEL_62_5M:
        return 62500 * KHZ;
    case CLK_GMAC0_PTP_REF_SEL_100M:
        return 100 * MHZ;
    case CLK_GMAC0_PTP_REF_SEL_50M:
        return 50 * MHZ;
    case CLK_GMAC0_PTP_REF_SEL_24M:
        return OSC_HZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t gmac_ptp_ref_set_clk(struct rk_clk_priv *priv, rt_ubase_t mac_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk;

    switch (rate)
    {
    case 62500 * KHZ:
        src_clk = CLK_GMAC0_PTP_REF_SEL_62_5M;
        break;
    case 100 * MHZ:
        src_clk = CLK_GMAC0_PTP_REF_SEL_100M;
        break;
    case 50 * MHZ:
        src_clk = CLK_GMAC0_PTP_REF_SEL_50M;
        break;
    case 24 * MHZ:
        src_clk = CLK_GMAC0_PTP_REF_SEL_24M;
        break;
    default:
        return -RT_ERROR;
    }

    rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2], CLK_GMAC0_PTP_REF_SEL_MASK, src_clk << CLK_GMAC0_PTP_REF_SEL_SHIFT);

    return gmac_ptp_ref_get_clk(priv, mac_id);
}

static rt_ubase_t gmac_tx_rx_set_clk(struct rk_clk_priv *priv, rt_ubase_t mac_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con, sel, div_sel;

    con = HWREG32(&cru->clksel_con[31 + mac_id * 2]);
    sel = (con & RMII0_MODE_MASK) >> RMII0_MODE_SHIFT;

    if (sel == RMII0_MODE_SEL_RGMII)
    {
        if (rate == 2500000)
        {
            div_sel = RGMII0_CLK_SEL_2_5M;
        }
        else if (rate == 25000000)
        {
            div_sel = RGMII0_CLK_SEL_25M;
        }
        else
        {
            div_sel = RGMII0_CLK_SEL_125M;
        }
        rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2], RGMII0_CLK_SEL_MASK, div_sel << RGMII0_CLK_SEL_SHIFT);
    }
    else if (sel == RMII0_MODE_SEL_RMII)
    {
        if (rate == 2500000)
        {
            div_sel = RMII0_CLK_SEL_2_5M;
        }
        else
        {
            div_sel = RMII0_CLK_SEL_25M;
        }
        rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2], RMII0_CLK_SEL_MASK, div_sel << RMII0_CLK_SEL_SHIFT);
    }

    return 0;
}

static rt_ubase_t ebc_get_clk(struct rk_clk_priv *priv)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con, div, p_rate;

    con = HWREG32(&cru->clksel_con[79]);
    div = (con & CPLL_333M_DIV_MASK) >> CPLL_333M_DIV_SHIFT;
    p_rate = DIV_TO_RATE(priv->cpll_hz, div);

    con = HWREG32(&cru->clksel_con[43]);
    div = (con & DCLK_EBC_SEL_MASK) >> DCLK_EBC_SEL_SHIFT;

    switch (div)
    {
    case DCLK_EBC_SEL_GPLL_400M:
        return 400 * MHZ;
    case DCLK_EBC_SEL_CPLL_333M:
        return p_rate;
    case DCLK_EBC_SEL_GPLL_200M:
        return 200 * MHZ;
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t ebc_set_clk(struct rk_clk_priv *priv, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(priv->cpll_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 31);
    rk_clrsetreg(&cru->clksel_con[79], CPLL_333M_DIV_MASK, (src_clk_div - 1) << CPLL_333M_DIV_SHIFT);
    rk_clrsetreg(&cru->clksel_con[43], DCLK_EBC_SEL_MASK, DCLK_EBC_SEL_CPLL_333M << DCLK_EBC_SEL_SHIFT);

    return ebc_get_clk(priv);
}

static rt_ubase_t rkvdec_get_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con, div, src, p_rate;

    switch (clk_id)
    {
    case ACLK_RKVDEC_PRE:
    case ACLK_RKVDEC:
        con = HWREG32(&cru->clksel_con[47]);
        src = (con & ACLK_RKVDEC_SEL_MASK) >> ACLK_RKVDEC_SEL_SHIFT;
        div = (con & ACLK_RKVDEC_DIV_MASK) >> ACLK_RKVDEC_DIV_SHIFT;

        if (src == ACLK_RKVDEC_SEL_CPLL)
        {
            p_rate = priv->cpll_hz;
        }
        else
        {
            p_rate = priv->gpll_hz;
        }
        return DIV_TO_RATE(p_rate, div);
    case CLK_RKVDEC_CORE:
        con = HWREG32(&cru->clksel_con[49]);
        src = (con & CLK_RKVDEC_CORE_SEL_MASK) >> CLK_RKVDEC_CORE_SEL_SHIFT;
        div = (con & CLK_RKVDEC_CORE_DIV_MASK) >> CLK_RKVDEC_CORE_DIV_SHIFT;

        if (src == CLK_RKVDEC_CORE_SEL_CPLL)
        {
            p_rate = priv->cpll_hz;
        }
        else if (src == CLK_RKVDEC_CORE_SEL_NPLL)
        {
            p_rate = priv->npll_hz;
        }
        else if (src == CLK_RKVDEC_CORE_SEL_VPLL)
        {
            p_rate = priv->vpll_hz;
        }
        else
        {
            p_rate = priv->gpll_hz;
        }
        return DIV_TO_RATE(p_rate, div);
    default:
        return -RT_ERROR;
    }
}

static rt_ubase_t rkvdec_set_clk(struct rk_clk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk_cru *cru = priv->cru;
    int src_clk_div, src, p_rate;

    switch (clk_id)
    {
    case ACLK_RKVDEC_PRE:
    case ACLK_RKVDEC:
        src = (HWREG32(&cru->clksel_con[47]) & ACLK_RKVDEC_SEL_MASK) >> ACLK_RKVDEC_SEL_SHIFT;
        if (src == ACLK_RKVDEC_SEL_CPLL)
        {
            p_rate = priv->cpll_hz;
        }
        else
        {
            p_rate = priv->gpll_hz;
        }
        src_clk_div = RT_DIV_ROUND_UP(p_rate, rate);
        RT_ASSERT(src_clk_div - 1 <= 31);
        rk_clrsetreg(&cru->clksel_con[47], ACLK_RKVDEC_SEL_MASK | ACLK_RKVDEC_DIV_MASK,
                (src << ACLK_RKVDEC_SEL_SHIFT) | (src_clk_div - 1) << ACLK_RKVDEC_DIV_SHIFT);
        break;
    case CLK_RKVDEC_CORE:
        src = (HWREG32(&cru->clksel_con[49]) & CLK_RKVDEC_CORE_SEL_MASK) >> CLK_RKVDEC_CORE_SEL_SHIFT;
        if (src == CLK_RKVDEC_CORE_SEL_CPLL)
        {
            p_rate = priv->cpll_hz;
        }
        else if (src == CLK_RKVDEC_CORE_SEL_NPLL)
        {
            p_rate = priv->npll_hz;
        }
        else if (src == CLK_RKVDEC_CORE_SEL_VPLL)
        {
            p_rate = priv->vpll_hz;
        }
        else
        {
            p_rate = priv->gpll_hz;
        }
        src_clk_div = RT_DIV_ROUND_UP(p_rate, rate);
        RT_ASSERT(src_clk_div - 1 <= 31);
        rk_clrsetreg(&cru->clksel_con[49], CLK_RKVDEC_CORE_SEL_MASK | CLK_RKVDEC_CORE_DIV_MASK,
                (src << CLK_RKVDEC_CORE_SEL_SHIFT) | (src_clk_div - 1) << CLK_RKVDEC_CORE_DIV_SHIFT);
        break;
    default:
        return -RT_ERROR;
    }

    return rkvdec_get_clk(priv, clk_id);
}

static rt_ubase_t uart_get_rate(struct rk_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk_cru *cru = priv->cru;
    rt_uint32_t reg, con, fracdiv, div, src, p_src, p_rate;
    rt_ubase_t m, n;

    switch (clk_id)
    {
    case SCLK_UART1:
        reg = 52;
        break;
    case SCLK_UART2:
        reg = 54;
        break;
    case SCLK_UART3:
        reg = 56;
        break;
    case SCLK_UART4:
        reg = 58;
        break;
    case SCLK_UART5:
        reg = 60;
        break;
    case SCLK_UART6:
        reg = 62;
        break;
    case SCLK_UART7:
        reg = 64;
        break;
    case SCLK_UART8:
        reg = 66;
        break;
    case SCLK_UART9:
        reg = 68;
        break;
    default:
        return -RT_ERROR;
    }

    con = HWREG32(&cru->clksel_con[reg]);
    src = (con & CLK_UART_SEL_MASK) >> CLK_UART_SEL_SHIFT;
    div = (con & CLK_UART_SRC_DIV_MASK) >> CLK_UART_SRC_DIV_SHIFT;
    p_src = (con & CLK_UART_SRC_SEL_MASK) >> CLK_UART_SRC_SEL_SHIFT;

    if (p_src == CLK_UART_SRC_SEL_GPLL)
    {
        p_rate = priv->gpll_hz;
    }
    else if (p_src == CLK_UART_SRC_SEL_CPLL)
    {
        p_rate = priv->cpll_hz;
    }
    else
    {
        p_rate = 480000000;
    }
    if (src == CLK_UART_SEL_SRC)
    {
        return DIV_TO_RATE(p_rate, div);
    }
    else if (src == CLK_UART_SEL_FRAC)
    {
        fracdiv = HWREG32(&cru->clksel_con[reg + 1]);
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
    rt_uint32_t reg, clk_src, uart_src, div;
    rt_ubase_t m = 0, n = 0, val;

    if (priv->gpll_hz % rate == 0)
    {
        clk_src = CLK_UART_SRC_SEL_GPLL;
        uart_src = CLK_UART_SEL_SRC;
        div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
    }
    else if (priv->cpll_hz % rate == 0)
    {
        clk_src = CLK_UART_SRC_SEL_CPLL;
        uart_src = CLK_UART_SEL_SRC;
        div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
    }
    else if (rate == OSC_HZ)
    {
        clk_src = CLK_UART_SRC_SEL_GPLL;
        uart_src = CLK_UART_SEL_XIN24M;
        div = 2;
    }
    else
    {
        clk_src = CLK_UART_SRC_SEL_GPLL;
        uart_src = CLK_UART_SEL_FRAC;
        div = 2;
        rational_best_approximation(rate, priv->gpll_hz / div, RT_GENMASK(16 - 1, 0), RT_GENMASK(16 - 1, 0), &m, &n);
    }

    switch (clk_id)
    {
    case SCLK_UART1:
        reg = 52;
        break;
    case SCLK_UART2:
        reg = 54;
        break;
    case SCLK_UART3:
        reg = 56;
        break;
    case SCLK_UART4:
        reg = 58;
        break;
    case SCLK_UART5:
        reg = 60;
        break;
    case SCLK_UART6:
        reg = 62;
        break;
    case SCLK_UART7:
        reg = 64;
        break;
    case SCLK_UART8:
        reg = 66;
        break;
    case SCLK_UART9:
        reg = 68;
        break;
    default:
        return -RT_ERROR;
    }
    rk_clrsetreg(&cru->clksel_con[reg], CLK_UART_SEL_MASK | CLK_UART_SRC_SEL_MASK | CLK_UART_SRC_DIV_MASK,
            (clk_src << CLK_UART_SRC_SEL_SHIFT) | (uart_src << CLK_UART_SEL_SHIFT) |
            ((div - 1) << CLK_UART_SRC_DIV_SHIFT));
    if (m && n)
    {
        val = m << CLK_UART_FRAC_NUMERATOR_SHIFT | n;
        HWREG32(&cru->clksel_con[reg + 1]) = val;
    }

    return uart_get_rate(priv, clk_id);
}

static rt_ubase_t pmu_get_pmuclk(struct rk_pmuclk_priv *priv)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    rt_uint32_t div, con, sel, parent;

    con = HWREG32(&pmucru->pmu_clksel_con[2]);
    sel = (con & PCLK_PDPMU_SEL_MASK) >> PCLK_PDPMU_SEL_SHIFT;
    div = (con & PCLK_PDPMU_DIV_MASK) >> PCLK_PDPMU_DIV_SHIFT;

    if (sel)
    {
        parent = GPLL_HZ;
    }
    else
    {
        parent = priv->ppll_hz;
    }

    return DIV_TO_RATE(parent, div);
}

static rt_ubase_t pmu_set_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t rate)
{
    struct rk_pmucru *pmucru = priv->pmucru;
    int src_clk_div;

    src_clk_div = RT_DIV_ROUND_UP(priv->ppll_hz, rate);
    RT_ASSERT(src_clk_div - 1 <= 31);

    rk_clrsetreg(&pmucru->pmu_clksel_con[2], PCLK_PDPMU_DIV_MASK | PCLK_PDPMU_SEL_MASK,
            (PCLK_PDPMU_SEL_PPLL << PCLK_PDPMU_SEL_SHIFT) | ((src_clk_div - 1) << PCLK_PDPMU_DIV_SHIFT));

    return pmu_get_pmuclk(priv);
}

static rt_ubase_t pciephy_ref_get_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t clk_id)
{
    rt_uint32_t con, div, src;
    struct rk_pmucru *pmucru = priv->pmucru;

    switch (clk_id)
    {
    case CLK_PCIEPHY0_REF:
        con = HWREG32(&pmucru->pmu_clksel_con[9]);
        src = (con & CLK_PCIE_PHY0_REF_SEL_MASK) >> CLK_PCIE_PHY0_REF_SEL_SHIFT;
        con = HWREG32(&pmucru->pmu_clksel_con[9]);
        div = (con & CLK_PCIE_PHY0_PLL_DIV_MASK) >> CLK_PCIE_PHY0_PLL_DIV_SHIFT;
        break;
    case CLK_PCIEPHY1_REF:
        con = HWREG32(&pmucru->pmu_clksel_con[9]);
        src = (con & CLK_PCIE_PHY1_REF_SEL_MASK) >> CLK_PCIE_PHY1_REF_SEL_SHIFT;
        con = HWREG32(&pmucru->pmu_clksel_con[9]);
        div = (con & CLK_PCIE_PHY1_PLL_DIV_MASK) >> CLK_PCIE_PHY1_PLL_DIV_SHIFT;
        break;
    case CLK_PCIEPHY2_REF:
        con = HWREG32(&pmucru->pmu_clksel_con[9]);
        src = (con & CLK_PCIE_PHY2_REF_SEL_MASK) >> CLK_PCIE_PHY2_REF_SEL_SHIFT;
        con = HWREG32(&pmucru->pmu_clksel_con[9]);
        div = (con & CLK_PCIE_PHY2_PLL_DIV_MASK) >> CLK_PCIE_PHY2_PLL_DIV_SHIFT;
        break;
    }

    if (src == CLK_PCIE_PHY_REF_SEL_PPLL)
    {
        return DIV_TO_RATE(priv->ppll_hz, div);
    }
    else
    {
        return OSC_HZ;
    }
}

static rt_ubase_t pciephy_ref_set_pmuclk(struct rk_pmuclk_priv *priv, rt_ubase_t clk_id, rt_ubase_t rate)
{
    rt_uint32_t clk_src, div;
    struct rk_pmucru *pmucru = priv->pmucru;

    if (rate == OSC_HZ)
    {
        clk_src = CLK_PCIE_PHY_REF_SEL_24M;
        div = 1;
    }
    else
    {
        clk_src = CLK_PCIE_PHY_REF_SEL_PPLL;
        div = RT_DIV_ROUND_UP(priv->ppll_hz, rate);
    }

    switch (clk_id)
    {
    case CLK_PCIEPHY0_REF:
        rk_clrsetreg(&pmucru->pmu_clksel_con[9], CLK_PCIE_PHY0_REF_SEL_MASK,
                (clk_src << CLK_PCIE_PHY0_REF_SEL_SHIFT));
        rk_clrsetreg(&pmucru->pmu_clksel_con[9], CLK_PCIE_PHY0_PLL_DIV_MASK,
                ((div - 1) << CLK_PCIE_PHY0_PLL_DIV_SHIFT));
        break;
    case CLK_PCIEPHY1_REF:
        rk_clrsetreg(&pmucru->pmu_clksel_con[9], CLK_PCIE_PHY1_REF_SEL_MASK,
                (clk_src << CLK_PCIE_PHY1_REF_SEL_SHIFT));
        rk_clrsetreg(&pmucru->pmu_clksel_con[9], CLK_PCIE_PHY1_PLL_DIV_MASK,
                ((div - 1) << CLK_PCIE_PHY1_PLL_DIV_SHIFT));
        break;
    case CLK_PCIEPHY2_REF:
        rk_clrsetreg(&pmucru->pmu_clksel_con[9], CLK_PCIE_PHY2_REF_SEL_MASK,
                (clk_src << CLK_PCIE_PHY2_REF_SEL_SHIFT));
        rk_clrsetreg(&pmucru->pmu_clksel_con[9], CLK_PCIE_PHY2_PLL_DIV_MASK,
                ((div - 1) << CLK_PCIE_PHY2_PLL_DIV_SHIFT));
        break;
    default:
        return -RT_EINVAL;
    }

    return pciephy_ref_get_pmuclk(priv, clk_id);
}

static rt_ubase_t rk_pmuclk_type_get_rate(struct rk_clk_platform_data *pdata,
        struct rk_clk *rk_clk)
{
    struct rk_pmuclk_priv *priv = &rk_clk->pmuclk_info;
    rt_ubase_t rate = 0;

    if (!priv->ppll_hz)
    {
        return -RT_ERROR;
    }

    switch (pdata->id)
    {
    case PLL_PPLL:
        rate = rk_pll_get_rate(&pmu_pll_clks[ppll], &priv->pmucru);
        break;
    case PLL_HPLL:
        rate = rk_pll_get_rate(&pmu_pll_clks[hpll], &priv->pmucru);
        break;
    case CLK_RTC_32K:
    case CLK_RTC32K_FRAC:
        rate = rtc32k_get_pmuclk(priv);
        break;
    case SCLK_UART0:
        rate = uart_get_pmuclk(priv, pdata->id);
        break;
    case CLK_I2C0:
        rate = i2c_get_pmuclk(priv, pdata->id);
        break;
    case CLK_PWM0:
        rate = pwm_get_pmuclk(priv, pdata->id);
        break;
    case PCLK_PMU:
        rate = pmu_get_pmuclk(priv);
        break;
    case CLK_PCIEPHY0_REF:
    case CLK_PCIEPHY1_REF:
    case CLK_PCIEPHY2_REF:
        rate = pciephy_ref_get_pmuclk(priv, pdata->id);
        break;
    default:
        return -RT_ERROR;
    }

    return rate;
}

static rt_ubase_t rk_pmuclk_set_rate(struct rk_clk_platform_data *pdata,
        struct rk_clk *rk_clk, rt_ubase_t rate)
{
    struct rk_pmuclk_priv *priv = &rk_clk->pmuclk_info;
    rt_ubase_t res = 0;

    if (!priv->ppll_hz)
    {
        return -RT_ERROR;
    }

    switch (pdata->id)
    {
    case PLL_PPLL:
        res = rk_pll_set_rate(&pmu_pll_clks[ppll], priv->pmucru, rate);
        priv->ppll_hz = rk_pll_get_rate(&pmu_pll_clks[ppll], &priv->pmucru);
        break;
    case PLL_HPLL:
        res = rk_pll_set_rate(&pmu_pll_clks[hpll], priv->pmucru, rate);
        priv->hpll_hz = rk_pll_get_rate(&pmu_pll_clks[hpll], &priv->pmucru);
        break;
    case CLK_RTC_32K:
    case CLK_RTC32K_FRAC:
        res = rtc32k_set_pmuclk(priv, rate);
        break;
    case SCLK_UART0:
        res = uart_set_pmuclk(priv, pdata->id, rate);
        break;
    case CLK_I2C0:
        res = i2c_set_pmuclk(priv, pdata->id, rate);
        break;
    case CLK_PWM0:
        res = pwm_set_pmuclk(priv, pdata->id, rate);
        break;
    case PCLK_PMU:
        res = pmu_set_pmuclk(priv, rate);
        break;
    case CLK_PCIEPHY0_REF:
    case CLK_PCIEPHY1_REF:
    case CLK_PCIEPHY2_REF:
        res = pciephy_ref_set_pmuclk(priv, pdata->id, rate);
        break;
    default:
        return -RT_ERROR;
    }

    return res;
}

static rt_ubase_t rk_clk_type_get_rate(struct rk_clk_platform_data *pdata,
        struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    rt_ubase_t rate = 0;

    if (!priv->gpll_hz)
    {
        return -RT_ERROR;
    }

    switch (pdata->id)
    {
    case PLL_APLL:
    case ARMCLK:
        rate = rk_pll_get_rate(&pll_clks[apll], &priv->cru);
        break;
    case PLL_CPLL:
        rate = rk_pll_get_rate(&pll_clks[cpll], &priv->cru);
        break;
    case PLL_GPLL:
        rate = rk_pll_get_rate(&pll_clks[gpll], &priv->cru);
        break;
    case PLL_NPLL:
        rate = rk_pll_get_rate(&pll_clks[npll], &priv->cru);
        break;
    case PLL_VPLL:
        rate = rk_pll_get_rate(&pll_clks[vpll], &priv->cru);
        break;
    case PLL_DPLL:
        rate = rk_pll_get_rate(&pll_clks[dpll], &priv->cru);
        break;
    case ACLK_BUS:
    case PCLK_BUS:
    case PCLK_WDT_NS:
        rate = bus_get_clk(priv, pdata->id);
        break;
    case ACLK_PERIMID:
    case HCLK_PERIMID:
        rate = perimid_get_clk(priv, pdata->id);
        break;
    case ACLK_TOP_HIGH:
    case ACLK_TOP_LOW:
    case HCLK_TOP:
    case PCLK_TOP:
        rate = top_get_clk(priv, pdata->id);
        break;
    case CLK_I2C1:
    case CLK_I2C2:
    case CLK_I2C3:
    case CLK_I2C4:
    case CLK_I2C5:
        rate = i2c_get_clk(priv, pdata->id);
        break;
    case CLK_SPI0:
    case CLK_SPI1:
    case CLK_SPI2:
    case CLK_SPI3:
        rate = spi_get_clk(priv, pdata->id);
        break;
    case CLK_PWM1:
    case CLK_PWM2:
    case CLK_PWM3:
        rate = pwm_get_clk(priv, pdata->id);
        break;
    case CLK_SARADC:
    case CLK_TSADC_TSEN:
    case CLK_TSADC:
        rate = adc_get_clk(priv, pdata->id);
        break;
    case HCLK_SDMMC0:
    case CLK_SDMMC0:
    case CLK_SDMMC1:
    case CLK_SDMMC2:
        rate = sdmmc_get_clk(priv, pdata->id);
        break;
    case SCLK_SFC:
        rate = sfc_get_clk(priv);
        break;
    case NCLK_NANDC:
        rate = nand_get_clk(priv);
        break;
    case CCLK_EMMC:
        rate = emmc_get_clk(priv);
        break;
    case BCLK_EMMC:
        rate = emmc_get_bclk(priv);
        break;
    case ACLK_VOP:
        rate = aclk_vop_get_clk(priv);
        break;
    case DCLK_VOP0:
    case DCLK_VOP1:
    case DCLK_VOP2:
        rate = dclk_vop_get_clk(priv, pdata->id);
        break;
    case SCLK_GMAC0:
    case CLK_MAC0_2TOP:
    case CLK_MAC0_REFOUT:
        rate = gmac_src_get_clk(priv, 0);
        break;
    case CLK_MAC0_OUT:
        rate = gmac_out_get_clk(priv, 0);
        break;
    case CLK_GMAC0_PTP_REF:
        rate = gmac_ptp_ref_get_clk(priv, 0);
        break;
    case SCLK_GMAC1:
    case CLK_MAC1_2TOP:
    case CLK_MAC1_REFOUT:
        rate = gmac_src_get_clk(priv, 1);
        break;
    case CLK_MAC1_OUT:
        rate = gmac_out_get_clk(priv, 1);
        break;
    case CLK_GMAC1_PTP_REF:
        rate = gmac_ptp_ref_get_clk(priv, 1);
        break;
    case DCLK_EBC:
        rate = ebc_get_clk(priv);
        break;
    case ACLK_RKVDEC_PRE:
    case ACLK_RKVDEC:
    case CLK_RKVDEC_CORE:
        rate = rkvdec_get_clk(priv, pdata->id);
        break;
    case TCLK_WDT_NS:
        rate = OSC_HZ;
        break;
    case SCLK_UART1:
    case SCLK_UART2:
    case SCLK_UART3:
    case SCLK_UART4:
    case SCLK_UART5:
    case SCLK_UART6:
    case SCLK_UART7:
    case SCLK_UART8:
    case SCLK_UART9:
        rate = uart_get_rate(priv, pdata->id);
        break;
    case ACLK_SECURE_FLASH:
    case ACLK_CRYPTO_NS:
    case HCLK_SECURE_FLASH:
    case HCLK_CRYPTO_NS:
    case CLK_CRYPTO_NS_RNG:
    case CLK_CRYPTO_NS_CORE:
    case CLK_CRYPTO_NS_PKA:
        rate = crypto_get_rate(priv, pdata->id);
        break;
    case CPLL_500M:
    case CPLL_333M:
    case CPLL_250M:
    case CPLL_125M:
    case CPLL_100M:
    case CPLL_62P5M:
    case CPLL_50M:
    case CPLL_25M:
        rate = cpll_div_get_rate(priv, pdata->id);
        break;
    case CLK_TIMER0:
    case CLK_TIMER1:
    case CLK_TIMER2:
    case CLK_TIMER3:
    case CLK_TIMER4:
    case CLK_TIMER5:
        rate = OSC_HZ;
        break;
    default:
        return -RT_ERROR;
    }

    return rate;
};

static rt_ubase_t rk_clk_set_rate(struct rk_clk_platform_data *pdata,
        struct rk_clk *rk_clk, rt_ubase_t rate)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    rt_ubase_t res = 0;

    if (!priv->gpll_hz)
    {
        return -RT_ERROR;
    }

    switch (pdata->id)
    {
    case PLL_APLL:
    case ARMCLK:
        if (priv->armclk_hz)
        {
            armclk_set_clk(priv, rate);
        }
        priv->armclk_hz = rate;
        break;
    case PLL_CPLL:
        res = rk_pll_set_rate(&pll_clks[cpll], priv->cru, rate);
        priv->cpll_hz = rk_pll_get_rate(&pll_clks[cpll], &priv->cru);
        break;
    case PLL_GPLL:
        res = rk_pll_set_rate(&pll_clks[gpll], priv->cru, rate);
        priv->gpll_hz = rk_pll_get_rate(&pll_clks[gpll], &priv->cru);
        break;
    case PLL_NPLL:
        res = rk_pll_set_rate(&pll_clks[npll], priv->cru, rate);
        break;
    case PLL_VPLL:
        res = rk_pll_set_rate(&pll_clks[vpll], priv->cru, rate);
        priv->vpll_hz = rk_pll_get_rate(&pll_clks[vpll], &priv->cru);
        break;
    case ACLK_BUS:
    case PCLK_BUS:
    case PCLK_WDT_NS:
        res = bus_set_clk(priv, pdata->id, rate);
        break;
    case ACLK_PERIMID:
    case HCLK_PERIMID:
        res = perimid_set_clk(priv, pdata->id, rate);
        break;
    case ACLK_TOP_HIGH:
    case ACLK_TOP_LOW:
    case HCLK_TOP:
    case PCLK_TOP:
        res = top_set_clk(priv, pdata->id, rate);
        break;
    case CLK_I2C1:
    case CLK_I2C2:
    case CLK_I2C3:
    case CLK_I2C4:
    case CLK_I2C5:
        res = i2c_set_clk(priv, pdata->id, rate);
        break;
    case CLK_SPI0:
    case CLK_SPI1:
    case CLK_SPI2:
    case CLK_SPI3:
        res = spi_set_clk(priv, pdata->id, rate);
        break;
    case CLK_PWM1:
    case CLK_PWM2:
    case CLK_PWM3:
        res = pwm_set_clk(priv, pdata->id, rate);
        break;
    case CLK_SARADC:
    case CLK_TSADC_TSEN:
    case CLK_TSADC:
        res = adc_set_clk(priv, pdata->id, rate);
        break;
    case HCLK_SDMMC0:
    case CLK_SDMMC0:
    case CLK_SDMMC1:
    case CLK_SDMMC2:
        res = sdmmc_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_SFC:
        res = sfc_set_clk(priv, rate);
        break;
    case NCLK_NANDC:
        res = nand_set_clk(priv, rate);
        break;
    case CCLK_EMMC:
        res = emmc_set_clk(priv, rate);
        break;
    case BCLK_EMMC:
        res = emmc_set_bclk(priv, rate);
        break;
    case ACLK_VOP:
        res = aclk_vop_set_clk(priv, rate);
        break;
    case DCLK_VOP0:
    case DCLK_VOP1:
    case DCLK_VOP2:
        res = dclk_vop_set_clk(priv, pdata->id, rate);
        break;
    case SCLK_GMAC0:
    case CLK_MAC0_2TOP:
    case CLK_MAC0_REFOUT:
        res = gmac_src_set_clk(priv, 0, rate);
        break;
    case CLK_MAC0_OUT:
        res = gmac_out_set_clk(priv, 0, rate);
        break;
    case SCLK_GMAC0_RX_TX:
        res = gmac_tx_rx_set_clk(priv, 0, rate);
        break;
    case CLK_GMAC0_PTP_REF:
        res = gmac_ptp_ref_set_clk(priv, 0, rate);
        break;
    case SCLK_GMAC1:
    case CLK_MAC1_2TOP:
    case CLK_MAC1_REFOUT:
        res = gmac_src_set_clk(priv, 1, rate);
        break;
    case CLK_MAC1_OUT:
        res = gmac_out_set_clk(priv, 1, rate);
        break;
    case SCLK_GMAC1_RX_TX:
        res = gmac_tx_rx_set_clk(priv, 1, rate);
        break;
    case CLK_GMAC1_PTP_REF:
        res = gmac_ptp_ref_set_clk(priv, 1, rate);
        break;
    case DCLK_EBC:
        res = ebc_set_clk(priv, rate);
        break;
    case ACLK_RKVDEC_PRE:
    case ACLK_RKVDEC:
    case CLK_RKVDEC_CORE:
        res = rkvdec_set_clk(priv, pdata->id, rate);
        break;
    case TCLK_WDT_NS:
        res = OSC_HZ;
        break;
    case SCLK_UART1:
    case SCLK_UART2:
    case SCLK_UART3:
    case SCLK_UART4:
    case SCLK_UART5:
    case SCLK_UART6:
    case SCLK_UART7:
    case SCLK_UART8:
    case SCLK_UART9:
        res = uart_set_rate(priv, pdata->id, rate);
        break;
    case ACLK_SECURE_FLASH:
    case ACLK_CRYPTO_NS:
    case HCLK_SECURE_FLASH:
    case HCLK_CRYPTO_NS:
    case CLK_CRYPTO_NS_RNG:
    case CLK_CRYPTO_NS_CORE:
    case CLK_CRYPTO_NS_PKA:
        res = crypto_set_rate(priv, pdata->id, rate);
        break;
    case CPLL_500M:
    case CPLL_333M:
    case CPLL_250M:
    case CPLL_125M:
    case CPLL_100M:
    case CPLL_62P5M:
    case CPLL_50M:
    case CPLL_25M:
        res = cpll_div_set_rate(priv, pdata->id, rate);
        break;
    default:
        return -RT_ERROR;
    }

    return res;
};

static rt_uint32_t rk_clk_get_rate(struct rk_clk_platform_data *pdata,
    struct rk_clk *rk_clk)
{
    rt_uint32_t rate = 0;

    if (rk_clk->type == rk_clk_type_clk)
    {
        rate = rk_clk_type_get_rate(pdata, rk_clk);
    }
    else if (rk_clk->type == rk_clk_type_pmuclk)
    {
        rate = rk_pmuclk_type_get_rate(pdata, rk_clk);
    }

    return rate;
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

static rt_err_t rtc32k_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    struct rk_pmuclk_priv *priv = &rk_clk->pmuclk_info;
    struct rk_pmucru *pmucru = priv->pmucru;

    if (ppdata->id == CLK_RTC32K_FRAC)
    {
        rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK,
                RTC32K_SEL_OSC0_DIV32K << RTC32K_SEL_SHIFT);
    }
    else
    {
        rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK,
                RTC32K_SEL_OSC1_32K << RTC32K_SEL_SHIFT);
    }

    return RT_EOK;
}

static rt_err_t rk_pmuclk_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    switch (pdata->id)
    {
    case CLK_RTC_32K:
        return rtc32k_set_parent(pdata, ppdata, rk_clk);

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t gmac0_src_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;

    if (ppdata->id == CLK_MAC0_2TOP)
    {
        rk_clrsetreg(&cru->clksel_con[31], RMII0_EXTCLK_SEL_MASK,
                RMII0_EXTCLK_SEL_MAC0_TOP << RMII0_EXTCLK_SEL_SHIFT);
    }
    else
    {
        rk_clrsetreg(&cru->clksel_con[31], RMII0_EXTCLK_SEL_MASK,
                RMII0_EXTCLK_SEL_IO << RMII0_EXTCLK_SEL_SHIFT);
    }

    return RT_EOK;
}

static rt_err_t gmac1_src_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;

    if (ppdata->id == CLK_MAC1_2TOP)
    {
        rk_clrsetreg(&cru->clksel_con[33], RMII0_EXTCLK_SEL_MASK,
                RMII0_EXTCLK_SEL_MAC0_TOP << RMII0_EXTCLK_SEL_SHIFT);
    }
    else
    {
        rk_clrsetreg(&cru->clksel_con[33], RMII0_EXTCLK_SEL_MASK,
                RMII0_EXTCLK_SEL_IO << RMII0_EXTCLK_SEL_SHIFT);
    }

    return RT_EOK;
}

static rt_err_t gmac0_tx_rx_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;

    if (ppdata->id == SCLK_GMAC0_RGMII_SPEED)
    {
        rk_clrsetreg(&cru->clksel_con[31], RMII0_MODE_MASK,
                RMII0_MODE_SEL_RGMII << RMII0_MODE_SHIFT);
    }
    else if (ppdata->id == SCLK_GMAC0_RMII_SPEED)
    {
        rk_clrsetreg(&cru->clksel_con[31], RMII0_MODE_MASK,
                RMII0_MODE_SEL_RMII << RMII0_MODE_SHIFT);
    }
    else
    {
        rk_clrsetreg(&cru->clksel_con[31], RMII0_MODE_MASK,
                RMII0_MODE_SEL_GMII << RMII0_MODE_SHIFT);
    }

    return RT_EOK;
}

static rt_err_t gmac1_tx_rx_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;

    if (ppdata->id == SCLK_GMAC1_RGMII_SPEED)
    {
        rk_clrsetreg(&cru->clksel_con[33], RMII0_MODE_MASK,
                RMII0_MODE_SEL_RGMII << RMII0_MODE_SHIFT);
    }
    else if (ppdata->id == SCLK_GMAC1_RMII_SPEED)
    {
        rk_clrsetreg(&cru->clksel_con[33], RMII0_MODE_MASK,
                RMII0_MODE_SEL_RMII << RMII0_MODE_SHIFT);
    }
    else
    {
        rk_clrsetreg(&cru->clksel_con[33], RMII0_MODE_MASK,
                RMII0_MODE_SEL_GMII << RMII0_MODE_SHIFT);
    }

    return RT_EOK;
}

static rt_err_t dclk_vop_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con_id;

    switch (pdata->id)
    {
    case DCLK_VOP0:
        con_id = 39;
        break;

    case DCLK_VOP1:
        con_id = 40;
        break;

    case DCLK_VOP2:
        con_id = 41;
        break;

    default:
        return -RT_EINVAL;
    }

    if (ppdata->id == PLL_VPLL)
    {
        rk_clrsetreg(&cru->clksel_con[con_id], DCLK0_VOP_SEL_MASK,
                DCLK_VOP_SEL_VPLL << DCLK0_VOP_SEL_SHIFT);
    }
    else
    {
        rk_clrsetreg(&cru->clksel_con[con_id], DCLK0_VOP_SEL_MASK,
                DCLK_VOP_SEL_HPLL << DCLK0_VOP_SEL_SHIFT);
    }

    return RT_EOK;
}

static rt_err_t rkvdec_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;
    rt_uint32_t con_id, mask, shift;

    switch (pdata->id)
    {
    case ACLK_RKVDEC_PRE:
        con_id = 47;
        mask = ACLK_RKVDEC_SEL_MASK;
        shift = ACLK_RKVDEC_SEL_SHIFT;
        break;

    case CLK_RKVDEC_CORE:
        con_id = 49;
        mask = CLK_RKVDEC_CORE_SEL_MASK;
        shift = CLK_RKVDEC_CORE_SEL_SHIFT;
        break;

    default:
        return -RT_EINVAL;
    }

    if (ppdata->id == PLL_CPLL)
    {
        rk_clrsetreg(&cru->clksel_con[con_id], mask,
                ACLK_RKVDEC_SEL_CPLL << shift);
    }
    else
    {
        rk_clrsetreg(&cru->clksel_con[con_id], mask,
                ACLK_RKVDEC_SEL_GPLL << shift);
    }

    return RT_EOK;
}

static int rk_clk_set_parent(struct rk_clk_platform_data *pdata,
        struct rk_clk_platform_data *ppdata, struct rk_clk *rk_clk)
{
    switch (pdata->id)
    {
    case SCLK_GMAC0:
        return gmac0_src_set_parent(pdata, ppdata, rk_clk);

    case SCLK_GMAC1:
        return gmac1_src_set_parent(pdata, ppdata, rk_clk);

    case SCLK_GMAC0_RX_TX:
        return gmac0_tx_rx_set_parent(pdata, ppdata, rk_clk);

    case SCLK_GMAC1_RX_TX:
        return gmac1_tx_rx_set_parent(pdata, ppdata, rk_clk);

    case DCLK_VOP0:
    case DCLK_VOP1:
    case DCLK_VOP2:
        return dclk_vop_set_parent(pdata, ppdata, rk_clk);

    case ACLK_RKVDEC_PRE:
    case CLK_RKVDEC_CORE:
        return rkvdec_set_parent(pdata, ppdata, rk_clk);

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t mmc_set_phase(struct rk_clk_platform_data *pdata,
        struct rk_clk *rk_clk, rt_uint32_t degrees)
{
    void *reg;
    rt_ubase_t rate;
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;

    rate = rk_clk_get_rate(pdata, rk_clk);

    switch (pdata->id)
    {
    case SCLK_SDMMC0_DRV:
        reg = &cru->emmc_con[0];
        break;

    case SCLK_SDMMC0_SAMPLE:
        reg = &cru->emmc_con[1];
        break;

    case SCLK_SDMMC1_DRV:
        reg = &cru->emmc_con[0];
        break;

    case SCLK_SDMMC1_SAMPLE:
        reg = &cru->emmc_con[1];
        break;

    case SCLK_SDMMC2_DRV:
        reg = &cru->emmc_con[0];
        break;

    case SCLK_SDMMC2_SAMPLE:
        reg = &cru->emmc_con[1];
        break;

    case SCLK_EMMC_DRV:
        reg = &cru->emmc_con[0];
        break;

    case SCLK_EMMC_SAMPLE:
        reg = &cru->emmc_con[1];
        break;
    }

    return rk_clk_mmc_set_phase(rate, reg, 1, degrees);
}

static rt_base_t mmc_get_phase(struct rk_clk_platform_data *pdata,
        struct rk_clk *rk_clk)
{
    void *reg;
    rt_ubase_t rate;
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    struct rk_cru *cru = priv->cru;

    rate = rk_clk_get_rate(pdata, rk_clk);

    switch (pdata->id)
    {
    case SCLK_SDMMC0_DRV:
        reg = &cru->emmc_con[0];
        break;

    case SCLK_SDMMC0_SAMPLE:
        reg = &cru->emmc_con[1];
        break;

    case SCLK_SDMMC1_DRV:
        reg = &cru->emmc_con[0];
        break;

    case SCLK_SDMMC1_SAMPLE:
        reg = &cru->emmc_con[1];
        break;

    case SCLK_SDMMC2_DRV:
        reg = &cru->emmc_con[0];
        break;

    case SCLK_SDMMC2_SAMPLE:
        reg = &cru->emmc_con[1];
        break;

    case SCLK_EMMC_DRV:
        reg = &cru->emmc_con[0];
        break;

    case SCLK_EMMC_SAMPLE:
        reg = &cru->emmc_con[1];
        break;
    }

    return rk_clk_mmc_get_phase(rate, reg, 1);
}

static rt_err_t rk3568_clk_init(struct rt_clk *clk, void *fw_data)
{
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rt_ofw_cell_args *args = fw_data;
    struct rk_clk_platform_data *pdata;
    rt_uint32_t clk_id = args->args[0];
    rt_ubase_t reg_base;

    pdata = &rk_clk->pdata[clk_id];

    if (rk_clk->type == rk_clk_type_pmuclk)
    {
        reg_base = (rt_ubase_t)rk_clk->pmuclk_info.pmucru;

        switch (clk_id)
        {
        case PLL_PPLL:
            reg_base += pmu_pll_clks[ppll].con_offset;
            break;
        case PLL_HPLL:
            reg_base += pmu_pll_clks[hpll].con_offset;
            break;
        default:
            reg_base = RT_NULL;
            break;
        }
    }
    else if (rk_clk->type == rk_clk_type_clk)
    {
        reg_base = (rt_ubase_t)rk_clk->clk_info.cru;

        switch (clk_id)
        {
        case PLL_APLL:
        case ARMCLK:
            reg_base += pll_clks[apll].con_offset;
            break;
        case PLL_CPLL:
            reg_base += pll_clks[cpll].con_offset;
            break;
        case PLL_GPLL:
            reg_base += pll_clks[gpll].con_offset;
            break;
        case PLL_NPLL:
            reg_base += pll_clks[npll].con_offset;
            break;
        case PLL_VPLL:
            reg_base += pll_clks[vpll].con_offset;
            break;
        case PLL_DPLL:
            reg_base += pll_clks[dpll].con_offset;
            break;
        default:
            reg_base = RT_NULL;
            break;
        }
    }
    else
    {
        LOG_E("Unknow type of rk clk = %d", rk_clk->type);
        RT_ASSERT(0);
    }

    pdata->id = clk_id;
    pdata->base = (void *)reg_base;

    clk->rate = rk_clk_get_rate(pdata, rk_clk);
    clk->priv = pdata;

    rk_clk_set_default_rates(clk, clk->clk_np->ops->set_rate, clk_id);

    return RT_EOK;
}

static rt_err_t rk3568_clk_enable(struct rt_clk *clk)
{
    struct rk_clk_platform_data *pdata = clk->priv;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rk_cru *cru = rk_clk->clk_info.cru;
    struct rk_pmucru *pmucru = rk_clk->pmuclk_info.pmucru;

    if (pdata->base)
    {
        HWREG32(pdata->base + PLL_CON(1)) = HIWORD_UPDATE(0, PLLCON1_PWRDOWN, 0);

        rk_clk_wait_lock(pdata);
    }
    else
    {
        void *con_regs;
        struct rk_clk_gate *gate;

        if (rk_clk->type == rk_clk_type_clk)
        {
            gate = &clk_gates[pdata->id];
            con_regs = &cru->clkgate_con[gate->con_idx];
        }
        else if (rk_clk->type == rk_clk_type_pmuclk)
        {
            gate = &pmu_clk_gates[pdata->id];
            con_regs = &pmucru->pmu_clkgate_con[gate->con_idx];
        }
        else
        {
            return -RT_EINVAL;
        }

        rk_clrreg(con_regs, RT_BIT(gate->con_bit));
    }

    return RT_EOK;
}

static void rk3568_clk_disable(struct rt_clk *clk)
{
    struct rk_clk_platform_data *pdata = clk->priv;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rk_cru *cru = rk_clk->clk_info.cru;
    struct rk_pmucru *pmucru = rk_clk->pmuclk_info.pmucru;

    if (pdata->base)
    {
        HWREG32(pdata->base + PLL_CON(1)) = HIWORD_UPDATE(PLLCON1_PWRDOWN, PLLCON1_PWRDOWN, 0);
    }
    else
    {
        void *con_regs;
        struct rk_clk_gate *gate;

        if (rk_clk->type == rk_clk_type_clk)
        {
            gate = &clk_gates[pdata->id];
            con_regs = &cru->clkgate_con[gate->con_idx];
        }
        else if (rk_clk->type == rk_clk_type_pmuclk)
        {
            gate = &pmu_clk_gates[pdata->id];
            con_regs = &pmucru->pmu_clkgate_con[gate->con_idx];
        }
        else
        {
            return;
        }

        rk_setreg(con_regs, RT_BIT(gate->con_bit));
    }
}

static rt_bool_t rk3568_clk_is_enabled(struct rt_clk *clk)
{
    struct rk_clk_platform_data *pdata = clk->priv;

    if (pdata->base)
    {
        rt_uint32_t pllcon = HWREG32(pdata->base + PLL_CON(1));

        return !(pllcon & PLLCON1_PWRDOWN);
    }

    return RT_TRUE;
}

static rt_err_t rk3568_clk_set_rate(struct rt_clk *clk, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_ubase_t res_rate;
    struct rk_clk_platform_data *pdata = clk->priv;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);

    if (rk_clk->type == rk_clk_type_clk)
    {
        res_rate = rk_clk_set_rate(pdata, rk_clk, rate);

        if ((rt_base_t)res_rate > 0)
        {
            clk->rate = res_rate;
        }
    }
    else if (rk_clk->type == rk_clk_type_pmuclk)
    {
        res_rate = rk_pmuclk_set_rate(pdata, rk_clk, rate);

        if ((rt_base_t)res_rate > 0)
        {
            clk->rate = res_rate;
        }
    }
    else
    {
        return -RT_EINVAL;
    }

    return (rt_ubase_t)res_rate > 0 ? RT_EOK : (rt_err_t)res_rate;
}

static rt_err_t rk3568_clk_set_parent(struct rt_clk *clk, struct rt_clk *parent)
{
    rt_err_t err;
    struct rk_clk_platform_data *pdata = clk->priv, *ppdata = parent->priv;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rk_clk *rk_clk_parent = raw_to_rk_clk(clk->clk_np);

    if (rk_clk->type != rk_clk_parent->type)
    {
        return -RT_EINVAL;
    }

    if (rk_clk->type == rk_clk_type_clk)
    {
        err = rk_clk_set_parent(pdata, ppdata, rk_clk);
    }
    else if (rk_clk->type == rk_clk_type_pmuclk)
    {
        err = rk_pmuclk_set_parent(pdata, ppdata, rk_clk);
    }
    else
    {
        return -RT_EINVAL;
    }

    return err;
}

static rt_err_t rk3568_clk_set_phase(struct rt_clk *clk, int degrees)
{
    rt_err_t res;
    struct rk_clk_platform_data *pdata = clk->priv;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);

    switch (pdata->id)
    {
    case SCLK_SDMMC0_DRV:
    case SCLK_SDMMC0_SAMPLE:
    case SCLK_SDMMC1_DRV:
    case SCLK_SDMMC1_SAMPLE:
    case SCLK_SDMMC2_DRV:
    case SCLK_SDMMC2_SAMPLE:
    case SCLK_EMMC_DRV:
    case SCLK_EMMC_SAMPLE:
        res = mmc_set_phase(pdata, rk_clk, degrees);
        break;

    default:
        return -RT_EINVAL;
    }

    return res;
}

static rt_base_t rk3568_clk_get_phase(struct rt_clk *clk)
{
    rt_base_t res;
    struct rk_clk_platform_data *pdata = clk->priv;
    struct rk_clk *rk_clk = raw_to_rk_clk(clk->clk_np);

    switch (pdata->id)
    {
    case SCLK_SDMMC0_DRV:
    case SCLK_SDMMC0_SAMPLE:
    case SCLK_SDMMC1_DRV:
    case SCLK_SDMMC1_SAMPLE:
    case SCLK_SDMMC2_DRV:
    case SCLK_SDMMC2_SAMPLE:
    case SCLK_EMMC_DRV:
    case SCLK_EMMC_SAMPLE:
        res = mmc_get_phase(pdata, rk_clk);
        break;

    default:
        return -RT_EINVAL;
    }

    return res;
}

static rt_base_t rk3568_clk_round_rate(struct rt_clk *clk, rt_ubase_t drate,
        rt_ubase_t *prate)
{
    return rk_clk_pll_round_rate(pll_rates, RT_ARRAY_SIZE(pll_rates), drate, prate);
}

static const struct rt_clk_ops rk3568_clk_ops =
{
    .init = rk3568_clk_init,
    .enable = rk3568_clk_enable,
    .disable = rk3568_clk_disable,
    .is_enabled = rk3568_clk_is_enabled,
    .set_rate = rk3568_clk_set_rate,
    .set_parent = rk3568_clk_set_parent,
    .set_phase = rk3568_clk_set_phase,
    .get_phase = rk3568_clk_get_phase,
    .round_rate = rk3568_clk_round_rate,
};

static void rk3568_clk_type_init(struct rk_clk *rk_clk, struct rt_ofw_node *np)
{
    rt_ubase_t cpu_freq = APLL_HZ;
    struct rk_clk_priv *priv = &rk_clk->clk_info;
    const char *rockchip_cpu_freq = rt_ofw_bootargs_select("rockchip.cpu_freq=", 0);

    priv->cru = (struct rk_cru *)rk_clk->base;

    if (!priv->armclk_enter_hz)
    {
        priv->armclk_enter_hz = rk_pll_get_rate(&pll_clks[apll], &priv->cru);
        priv->armclk_init_hz = priv->armclk_enter_hz;
    }

    if (rockchip_cpu_freq)
    {
        cpu_freq = atol(rockchip_cpu_freq);
    }
    else
    {
        cpu_freq = 1800000000;
    }

    if (!armclk_set_clk(priv, cpu_freq))
    {
        priv->armclk_init_hz = cpu_freq;
    }

    if (priv->cpll_hz != CPLL_HZ)
    {
        if (!rk_pll_set_rate(&pll_clks[cpll], priv->cru, CPLL_HZ))
        {
            priv->cpll_hz = CPLL_HZ;
        }
    }

    if (priv->gpll_hz != GPLL_HZ)
    {
        if (!rk_pll_set_rate(&pll_clks[gpll], priv->cru, GPLL_HZ))
        {
            priv->gpll_hz = GPLL_HZ;
        }
    }

    priv->ppll_hz = pmu_pll_get_rate(ppll);
    priv->hpll_hz = pmu_pll_get_rate(hpll);
}

static void rk3568_pmu_clk_type_init(struct rk_clk *rk_clk, struct rt_ofw_node *np)
{
    struct rk_pmuclk_priv *priv = &rk_clk->pmuclk_info;
    priv->pmucru = (struct rk_pmucru *)rk_clk->base;

    if (priv->ppll_hz != PPLL_HZ)
    {
        if (!rk_pll_set_rate(&pmu_pll_clks[ppll], priv->pmucru, PPLL_HZ))
        {
            priv->ppll_hz = PPLL_HZ;
        }
    }

    /* Ungate PCIe30phy refclk_m and refclk_n */
    rk_clrsetreg(&priv->pmucru->pmu_clkgate_con[2], 0x3 << 13, 0 << 13);
}

static rt_err_t clk_rk3568_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_size_t data_size = 0;
    struct rk_clk *rk_clk;
    struct rt_ofw_node *np = pdev->parent.ofw_node;
    enum rk_clk_type type = (rt_ubase_t)pdev->id->data;

    if (type == rk_clk_type_clk)
    {
        data_size = CLK_NR_CLKS;
    }
    else if (type == rk_clk_type_pmuclk)
    {
        data_size = CLKPMU_NR_CLKS;
    }

    data_size *= sizeof(struct rk_clk_platform_data);
    rk_clk = rt_malloc(sizeof(*rk_clk) + data_size);

    if (rk_clk)
    {
        void *softrst_regs = RT_NULL;
        rt_memset(&rk_clk->parent, 0, sizeof(rk_clk->parent));

        rk_clk->base = rt_ofw_iomap(np, 0);

        if (!rk_clk->base)
        {
            err = -RT_EIO;
            goto _fail;
        }

        if (type == rk_clk_type_clk)
        {
            rk_clk->type = rk_clk_type_clk;

            rk3568_clk_type_init(rk_clk, np);
            softrst_regs = &rk_clk->clk_info.cru->softrst_con;
        }
        else if (type == rk_clk_type_pmuclk)
        {
            rk_clk->type = rk_clk_type_pmuclk;

            rk3568_pmu_clk_type_init(rk_clk, np);
            softrst_regs = &rk_clk->pmuclk_info.pmucru->pmu_softrst_con;
        }

        rk_clk->parent.parent.ops = &rk3568_clk_ops;

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
    }
    else
    {
        err = -RT_ENOMEM;
    }

    return err;

_fail:
    if (rk_clk->base)
    {
        rt_iounmap(rk_clk->base);
    }

    rt_free(rk_clk);

    return err;
}

static const struct rt_ofw_node_id clk_rk3568_ofw_ids[] =
{
    { .compatible = "rockchip,rk3568-cru", .data = (void *)rk_clk_type_clk },
    { .compatible = "rockchip,rk3568-pmucru", .data = (void *)rk_clk_type_pmuclk },
    { /* sentinel */ }
};

static struct rt_platform_driver clk_rk3568_driver =
{
    .name = "clk-rk3568",
    .ids = clk_rk3568_ofw_ids,

    .probe = clk_rk3568_probe,
};

static int clk_rk3568_register(void)
{
    rt_platform_driver_register(&clk_rk3568_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(clk_rk3568_register);
