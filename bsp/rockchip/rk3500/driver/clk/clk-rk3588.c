#include "clk-rk3588.h"
#define DBG_TAG "clk.rk3588"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include <mm_aspace.h>
#include "rk3588-cru.h"
#define raw_to_rk_clk(raw) rt_container_of(raw, struct rk3588_clk, parent)
#define MHz     1000000
#define KHz     1000

#define CPU_PVTPLL_HZ   (1008 * MHz)
#define LPLL_HZ     (816 * MHz)
#define GPLL_HZ     (1188 * MHz)
#define CPLL_HZ     (1500 * MHz)
#define NPLL_HZ         (850 * MHz)
#define PPLL_HZ     (1100 * MHz)

/* RK3588 pll id */
enum rk3588_pll_id {
    B0PLL,
    B1PLL,
    LPLL,
    CPLL,
    GPLL,
    NPLL,
    V0PLL,
    AUPLL,
    PPLL,
    PLL_COUNT,
};

struct rk3588_clk_info {
    unsigned long id;
    char *name;
    rt_bool_t is_cru;
};

struct rk3588_pll {
    unsigned int con0;
    unsigned int con1;
    unsigned int con2;
    unsigned int con3;
    unsigned int con4;
    unsigned int reserved0[3];
};
struct rk3588_cru {
    struct rk3588_pll pll[18];                                                                          /*144*/
    unsigned int reserved0[16];/* Address Offset: 0x0240 */                                             /*160*/
    unsigned int mode_con00;/* Address Offset: 0x0280 */                                                /*161*/
    unsigned int reserved1[31];/* Address Offset: 0x0284 */                                             /*192*/
    unsigned int clksel_con[178]; /* Address Offset: 0x0300 */                                          /*370*/
    unsigned int reserved2[142];/* Address Offset: 0x05c8 */                                            /*512*/
    unsigned int clkgate_con[78];/* Address Offset: 0x0800 */                                           /*590*/
    unsigned int reserved3[50];/* Address Offset: 0x0938 */                                             /*640*/
    unsigned int softrst_con[78];/* Address Offset: 0xa00 */ /* for convenient of softrst register      //718*/
    unsigned int reserved4[50];/* Address Offset: 0x0b38 */                                             /*768*/
    unsigned int glb_cnt_th;/* Address Offset: 0x0c00 */
    unsigned int glb_rst_st;/* Address Offset: 0x0c04 */
    unsigned int glb_srst_fst;/* Address Offset: 0x0c08 */
    unsigned int glb_srsr_snd; /* Address Offset: 0x0c0c */
    unsigned int glb_rst_con;/* Address Offset: 0x0c10 */
    unsigned int reserved5[4];/* Address Offset: 0x0c14 */
    unsigned int sdio_con[2];/* Address Offset: 0x0c24 */
    unsigned int reserved7;/* Address Offset: 0x0c2c */
    unsigned int sdmmc_con[2];/* Address Offset: 0x0c30 */
    unsigned int reserved8[48562];/* Address Offset: 0x0c38 */
    unsigned int pmuclksel_con[21]; /* Address Offset: 0x0100 */
    unsigned int reserved9[299];/* Address Offset: 0x0c38 */
    unsigned int pmuclkgate_con[9]; /* Address Offset: 0x0100 */
};

struct rk3588_clk_priv {
    struct rk3588_cru *cru;

    rt_ubase_t ppll_hz;
    rt_ubase_t gpll_hz;
    rt_ubase_t cpll_hz;
    rt_ubase_t npll_hz;
    rt_ubase_t v0pll_hz;
    rt_ubase_t aupll_hz;
    rt_ubase_t armclk_hz;
    rt_ubase_t armclk_enter_hz;
    rt_ubase_t armclk_init_hz;
    rt_bool_t sync_kernel;
    rt_bool_t set_armclk_rate;
};
struct rk3588_clk_platform_data
{
    rt_uint32_t id;
    void *base;
};
struct rt_reset_controller_clk_node
{
    struct rt_clk_node parent;

    struct rt_reset_controller rstcer;
};
struct rk3588_clk
{
    struct rt_reset_controller_clk_node parent;

    void *base;

    struct rk3588_clk_priv clk_info;

    struct rk3588_clk_platform_data pdata[];
};
struct pll_rate_table {
    unsigned long rate;
    unsigned int m;
    unsigned int p;
    unsigned int s;
    unsigned int k;
};

#define RK3588_PLL_CON(x)       ((x) * 0x4)
#define RK3588_MODE_CON         0x280

#define RK3588_PHP_CRU_BASE     0x8000
#define RK3588_PMU_CRU_BASE     0x30000
#define RK3588_BIGCORE0_CRU_BASE    0x50000
#define RK3588_BIGCORE1_CRU_BASE    0x52000
#define RK3588_DSU_CRU_BASE     0x58000

#define RK3588_PLL_CON(x)       ((x) * 0x4)
#define RK3588_MODE_CON0        0x280
#define RK3588_CLKSEL_CON(x)        ((x) * 0x4 + 0x300)
#define RK3588_CLKGATE_CON(x)       ((x) * 0x4 + 0x800)
#define RK3588_SOFTRST_CON(x)       ((x) * 0x4 + 0xa00)
#define RK3588_GLB_CNT_TH       0xc00
#define RK3588_GLB_SRST_FST     0xc08
#define RK3588_GLB_SRST_SND     0xc0c
#define RK3588_GLB_RST_CON      0xc10
#define RK3588_GLB_RST_ST       0xc04
#define RK3588_SDIO_CON0        0xC24
#define RK3588_SDIO_CON1        0xC28
#define RK3588_SDMMC_CON0       0xC30
#define RK3588_SDMMC_CON1       0xC34

#define RK3588_PHP_CLKGATE_CON(x)   ((x) * 0x4 + RK3588_PHP_CRU_BASE + 0x800)
#define RK3588_PHP_SOFTRST_CON(x)   ((x) * 0x4 + RK3588_PHP_CRU_BASE + 0xa00)

#define RK3588_PMU_PLL_CON(x)       ((x) * 0x4 + RK3588_PHP_CRU_BASE)
#define RK3588_PMU_CLKSEL_CON(x)    ((x) * 0x4 + RK3588_PMU_CRU_BASE + 0x300)
#define RK3588_PMU_CLKGATE_CON(x)   ((x) * 0x4 + RK3588_PMU_CRU_BASE + 0x800)
#define RK3588_PMU_SOFTRST_CON(x)   ((x) * 0x4 + RK3588_PMU_CRU_BASE + 0xa00)

#define RK3588_B0_PLL_CON(x)        ((x) * 0x4 + RK3588_BIGCORE0_CRU_BASE)
#define RK3588_B0_PLL_MODE_CON      (RK3588_BIGCORE0_CRU_BASE + 0x280)
#define RK3588_BIGCORE0_CLKSEL_CON(x)   ((x) * 0x4 + RK3588_BIGCORE0_CRU_BASE + 0x300)
#define RK3588_BIGCORE0_CLKGATE_CON(x)  ((x) * 0x4 + RK3588_BIGCORE0_CRU_BASE + 0x800)
#define RK3588_BIGCORE0_SOFTRST_CON(x)  ((x) * 0x4 + RK3588_BIGCORE0_CRU_BASE + 0xa00)
#define RK3588_B1_PLL_CON(x)        ((x) * 0x4 + RK3588_BIGCORE1_CRU_BASE)
#define RK3588_B1_PLL_MODE_CON      (RK3588_BIGCORE1_CRU_BASE + 0x280)
#define RK3588_BIGCORE1_CLKSEL_CON(x)   ((x) * 0x4 + RK3588_BIGCORE1_CRU_BASE + 0x300)
#define RK3588_BIGCORE1_CLKGATE_CON(x)  ((x) * 0x4 + RK3588_BIGCORE1_CRU_BASE + 0x800)
#define RK3588_BIGCORE1_SOFTRST_CON(x)  ((x) * 0x4 + RK3588_BIGCORE1_CRU_BASE + 0xa00)
#define RK3588_LPLL_CON(x)      ((x) * 0x4 + RK3588_DSU_CRU_BASE)
#define RK3588_LPLL_MODE_CON        (RK3588_DSU_CRU_BASE + 0x280)
#define RK3588_DSU_CLKSEL_CON(x)    ((x) * 0x4 + RK3588_DSU_CRU_BASE + 0x300)
#define RK3588_DSU_CLKGATE_CON(x)   ((x) * 0x4 + RK3588_DSU_CRU_BASE + 0x800)
#define RK3588_DSU_SOFTRST_CON(x)   ((x) * 0x4 + RK3588_DSU_CRU_BASE + 0xa00)

enum {
    /* CRU_CLK_SEL8_CON */
    ACLK_LOW_TOP_ROOT_SRC_SEL_SHIFT     = 14,
    ACLK_LOW_TOP_ROOT_SRC_SEL_MASK      = 1 << ACLK_LOW_TOP_ROOT_SRC_SEL_SHIFT,
    ACLK_LOW_TOP_ROOT_SRC_SEL_GPLL      = 0,
    ACLK_LOW_TOP_ROOT_SRC_SEL_CPLL,
    ACLK_LOW_TOP_ROOT_DIV_SHIFT     = 9,
    ACLK_LOW_TOP_ROOT_DIV_MASK      = 0x1f << ACLK_LOW_TOP_ROOT_DIV_SHIFT,
    PCLK_TOP_ROOT_SEL_SHIFT         = 7,
    PCLK_TOP_ROOT_SEL_MASK          = 3 << PCLK_TOP_ROOT_SEL_SHIFT,
    PCLK_TOP_ROOT_SEL_100M          = 0,
    PCLK_TOP_ROOT_SEL_50M,
    PCLK_TOP_ROOT_SEL_24M,
    ACLK_TOP_ROOT_SRC_SEL_SHIFT     = 5,
    ACLK_TOP_ROOT_SRC_SEL_MASK      = 3 << ACLK_TOP_ROOT_SRC_SEL_SHIFT,
    ACLK_TOP_ROOT_SRC_SEL_GPLL      = 0,
    ACLK_TOP_ROOT_SRC_SEL_CPLL,
    ACLK_TOP_ROOT_SRC_SEL_AUPLL,
    ACLK_TOP_ROOT_DIV_SHIFT         = 0,
    ACLK_TOP_ROOT_DIV_MASK          = 0x1f << ACLK_TOP_ROOT_DIV_SHIFT,

    /* CRU_CLK_SEL9_CON */
    ACLK_TOP_S400_SEL_SHIFT         = 8,
    ACLK_TOP_S400_SEL_MASK          = 3 << ACLK_TOP_S400_SEL_SHIFT,
    ACLK_TOP_S400_SEL_400M          = 0,
    ACLK_TOP_S400_SEL_200M,
    ACLK_TOP_S200_SEL_SHIFT         = 6,
    ACLK_TOP_S200_SEL_MASK          = 3 << ACLK_TOP_S200_SEL_SHIFT,
    ACLK_TOP_S200_SEL_200M          = 0,
    ACLK_TOP_S200_SEL_100M,

    /* CRU_CLK_SEL38_CON */
    CLK_I2C8_SEL_SHIFT          = 13,
    CLK_I2C8_SEL_MASK           = 1 << CLK_I2C8_SEL_SHIFT,
    CLK_I2C7_SEL_SHIFT          = 12,
    CLK_I2C7_SEL_MASK           = 1 << CLK_I2C7_SEL_SHIFT,
    CLK_I2C6_SEL_SHIFT          = 11,
    CLK_I2C6_SEL_MASK           = 1 << CLK_I2C6_SEL_SHIFT,
    CLK_I2C5_SEL_SHIFT          = 10,
    CLK_I2C5_SEL_MASK           = 1 << CLK_I2C5_SEL_SHIFT,
    CLK_I2C4_SEL_SHIFT          = 9,
    CLK_I2C4_SEL_MASK           = 1 << CLK_I2C4_SEL_SHIFT,
    CLK_I2C3_SEL_SHIFT          = 8,
    CLK_I2C3_SEL_MASK           = 1 << CLK_I2C3_SEL_SHIFT,
    CLK_I2C2_SEL_SHIFT          = 7,
    CLK_I2C2_SEL_MASK           = 1 << CLK_I2C2_SEL_SHIFT,
    CLK_I2C1_SEL_SHIFT          = 6,
    CLK_I2C1_SEL_MASK           = 1 << CLK_I2C1_SEL_SHIFT,
    ACLK_BUS_ROOT_SEL_SHIFT         = 5,
    ACLK_BUS_ROOT_SEL_MASK          = 3 << ACLK_BUS_ROOT_SEL_SHIFT,
    ACLK_BUS_ROOT_SEL_GPLL          = 0,
    ACLK_BUS_ROOT_SEL_CPLL,
    ACLK_BUS_ROOT_DIV_SHIFT         = 0,
    ACLK_BUS_ROOT_DIV_MASK          = 0x1f << ACLK_BUS_ROOT_DIV_SHIFT,

    /* CRU_CLK_SEL40_CON */
    CLK_SARADC_SEL_SHIFT            = 14,
    CLK_SARADC_SEL_MASK         = 0x1 << CLK_SARADC_SEL_SHIFT,
    CLK_SARADC_SEL_GPLL         = 0,
    CLK_SARADC_SEL_24M,
    CLK_SARADC_DIV_SHIFT            = 6,
    CLK_SARADC_DIV_MASK         = 0xff << CLK_SARADC_DIV_SHIFT,

    /* CRU_CLK_SEL41_CON */
    CLK_UART_SRC_SEL_SHIFT          = 14,
    CLK_UART_SRC_SEL_MASK           = 0x1 << CLK_UART_SRC_SEL_SHIFT,
    CLK_UART_SRC_SEL_GPLL           = 0,
    CLK_UART_SRC_SEL_CPLL,
    CLK_UART_SRC_DIV_SHIFT          = 9,
    CLK_UART_SRC_DIV_MASK           = 0x1f << CLK_UART_SRC_DIV_SHIFT,
    CLK_TSADC_SEL_SHIFT         = 8,
    CLK_TSADC_SEL_MASK          = 0x1 << CLK_TSADC_SEL_SHIFT,
    CLK_TSADC_SEL_GPLL          = 0,
    CLK_TSADC_SEL_24M,
    CLK_TSADC_DIV_SHIFT         = 0,
    CLK_TSADC_DIV_MASK          = 0xff << CLK_TSADC_DIV_SHIFT,

    /* CRU_CLK_SEL42_CON */
    CLK_UART_FRAC_NUMERATOR_SHIFT       = 16,
    CLK_UART_FRAC_NUMERATOR_MASK        = 0xffff << 16,
    CLK_UART_FRAC_DENOMINATOR_SHIFT     = 0,
    CLK_UART_FRAC_DENOMINATOR_MASK      = 0xffff,

    /* CRU_CLK_SEL43_CON */
    CLK_UART_SEL_SHIFT          = 0,
    CLK_UART_SEL_MASK           = 0x3 << CLK_UART_SEL_SHIFT,
    CLK_UART_SEL_SRC            = 0,
    CLK_UART_SEL_FRAC,
    CLK_UART_SEL_XIN24M,

    /* CRU_CLK_SEL59_CON */
    CLK_PWM2_SEL_SHIFT          = 14,
    CLK_PWM2_SEL_MASK           = 3 << CLK_PWM2_SEL_SHIFT,
    CLK_PWM1_SEL_SHIFT          = 12,
    CLK_PWM1_SEL_MASK           = 3 << CLK_PWM1_SEL_SHIFT,
    CLK_SPI4_SEL_SHIFT          = 10,
    CLK_SPI4_SEL_MASK           = 3 << CLK_SPI4_SEL_SHIFT,
    CLK_SPI3_SEL_SHIFT          = 8,
    CLK_SPI3_SEL_MASK           = 3 << CLK_SPI3_SEL_SHIFT,
    CLK_SPI2_SEL_SHIFT          = 6,
    CLK_SPI2_SEL_MASK           = 3 << CLK_SPI2_SEL_SHIFT,
    CLK_SPI1_SEL_SHIFT          = 4,
    CLK_SPI1_SEL_MASK           = 3 << CLK_SPI1_SEL_SHIFT,
    CLK_SPI0_SEL_SHIFT          = 2,
    CLK_SPI0_SEL_MASK           = 3 << CLK_SPI0_SEL_SHIFT,
    CLK_SPI_SEL_200M            = 0,
    CLK_SPI_SEL_150M,
    CLK_SPI_SEL_24M,

    /* CRU_CLK_SEL60_CON */
    CLK_PWM3_SEL_SHIFT          = 0,
    CLK_PWM3_SEL_MASK           = 3 << CLK_PWM3_SEL_SHIFT,
    CLK_PWM_SEL_100M            = 0,
    CLK_PWM_SEL_50M,
    CLK_PWM_SEL_24M,

    /* CRU_CLK_SEL62_CON */
    DCLK_DECOM_SEL_SHIFT            = 5,
    DCLK_DECOM_SEL_MASK         = 1 << DCLK_DECOM_SEL_SHIFT,
    DCLK_DECOM_SEL_GPLL         = 0,
    DCLK_DECOM_SEL_SPLL,
    DCLK_DECOM_DIV_SHIFT            = 0,
    DCLK_DECOM_DIV_MASK         = 0x1F << DCLK_DECOM_DIV_SHIFT,

    /* CRU_CLK_SEL77_CON */
    CCLK_EMMC_SEL_SHIFT         = 14,
    CCLK_EMMC_SEL_MASK          = 3 << CCLK_EMMC_SEL_SHIFT,
    CCLK_EMMC_SEL_GPLL          = 0,
    CCLK_EMMC_SEL_CPLL,
    CCLK_EMMC_SEL_24M,
    CCLK_EMMC_DIV_SHIFT         = 8,
    CCLK_EMMC_DIV_MASK          = 0x3f << CCLK_EMMC_DIV_SHIFT,

    /* CRU_CLK_SEL78_CON */
    SCLK_SFC_SEL_SHIFT          = 12,
    SCLK_SFC_SEL_MASK           = 3 << SCLK_SFC_SEL_SHIFT,
    SCLK_SFC_SEL_GPLL           = 0,
    SCLK_SFC_SEL_CPLL,
    SCLK_SFC_SEL_24M,
    SCLK_SFC_DIV_SHIFT          = 6,
    SCLK_SFC_DIV_MASK           = 0x3f << SCLK_SFC_DIV_SHIFT,
    BCLK_EMMC_SEL_SHIFT         = 5,
    BCLK_EMMC_SEL_MASK          = 1 << BCLK_EMMC_SEL_SHIFT,
    BCLK_EMMC_SEL_GPLL          = 0,
    BCLK_EMMC_SEL_CPLL,
    BCLK_EMMC_DIV_SHIFT         = 0,
    BCLK_EMMC_DIV_MASK          = 0x1f << BCLK_EMMC_DIV_SHIFT,

    /* CRU_CLK_SEL81_CON */
    CLK_GMAC1_PTP_SEL_SHIFT         = 13,
    CLK_GMAC1_PTP_SEL_MASK          = 1 << CLK_GMAC1_PTP_SEL_SHIFT,
    CLK_GMAC1_PTP_SEL_CPLL          = 0,
    CLK_GMAC1_PTP_DIV_SHIFT         = 7,
    CLK_GMAC1_PTP_DIV_MASK          = 0x3f << CLK_GMAC1_PTP_DIV_SHIFT,
    CLK_GMAC0_PTP_SEL_SHIFT         = 6,
    CLK_GMAC0_PTP_SEL_MASK          = 1 << CLK_GMAC0_PTP_SEL_SHIFT,
    CLK_GMAC0_PTP_SEL_CPLL          = 0,
    CLK_GMAC0_PTP_DIV_SHIFT         = 0,
    CLK_GMAC0_PTP_DIV_MASK          = 0x3f << CLK_GMAC0_PTP_DIV_SHIFT,

    /* CRU_CLK_SEL83_CON */
    CLK_GMAC_125M_SEL_SHIFT         = 15,
    CLK_GMAC_125M_SEL_MASK          = 1 << CLK_GMAC_125M_SEL_SHIFT,
    CLK_GMAC_125M_SEL_GPLL          = 0,
    CLK_GMAC_125M_SEL_CPLL,
    CLK_GMAC_125M_DIV_SHIFT         = 8,
    CLK_GMAC_125M_DIV_MASK          = 0x7f << CLK_GMAC_125M_DIV_SHIFT,

    /* CRU_CLK_SEL84_CON */
    CLK_GMAC_50M_SEL_SHIFT          = 7,
    CLK_GMAC_50M_SEL_MASK           = 1 << CLK_GMAC_50M_SEL_SHIFT,
    CLK_GMAC_50M_SEL_GPLL           = 0,
    CLK_GMAC_50M_SEL_CPLL,
    CLK_GMAC_50M_DIV_SHIFT          = 0,
    CLK_GMAC_50M_DIV_MASK           = 0x7f << CLK_GMAC_50M_DIV_SHIFT,

    /* CRU_CLK_SEL110_CON */
    HCLK_VOP_ROOT_SEL_SHIFT         = 10,
    HCLK_VOP_ROOT_SEL_MASK          = 3 << HCLK_VOP_ROOT_SEL_SHIFT,
    HCLK_VOP_ROOT_SEL_200M          = 0,
    HCLK_VOP_ROOT_SEL_100M,
    HCLK_VOP_ROOT_SEL_50M,
    HCLK_VOP_ROOT_SEL_24M,
    ACLK_VOP_LOW_ROOT_SEL_SHIFT     = 8,
    ACLK_VOP_LOW_ROOT_SEL_MASK      = 3 << ACLK_VOP_LOW_ROOT_SEL_SHIFT,
    ACLK_VOP_LOW_ROOT_SEL_400M      = 0,
    ACLK_VOP_LOW_ROOT_SEL_200M,
    ACLK_VOP_LOW_ROOT_SEL_100M,
    ACLK_VOP_LOW_ROOT_SEL_24M,
    ACLK_VOP_ROOT_SEL_SHIFT         = 5,
    ACLK_VOP_ROOT_SEL_MASK          = 7 << ACLK_VOP_ROOT_SEL_SHIFT,
    ACLK_VOP_ROOT_SEL_GPLL          = 0,
    ACLK_VOP_ROOT_SEL_CPLL,
    ACLK_VOP_ROOT_SEL_AUPLL,
    ACLK_VOP_ROOT_SEL_NPLL,
    ACLK_VOP_ROOT_SEL_SPLL,
    ACLK_VOP_ROOT_DIV_SHIFT         = 0,
    ACLK_VOP_ROOT_DIV_MASK          = 0x1f << ACLK_VOP_ROOT_DIV_SHIFT,

    /* CRU_CLK_SEL111_CON */
    DCLK1_VOP_SRC_SEL_SHIFT         = 14,
    DCLK1_VOP_SRC_SEL_MASK          = 3 << DCLK1_VOP_SRC_SEL_SHIFT,
    DCLK1_VOP_SRC_DIV_SHIFT         = 9,
    DCLK1_VOP_SRC_DIV_MASK          = 0x1f << DCLK1_VOP_SRC_DIV_SHIFT,
    DCLK0_VOP_SRC_SEL_SHIFT         = 7,
    DCLK0_VOP_SRC_SEL_MASK          = 3 << DCLK0_VOP_SRC_SEL_SHIFT,
    DCLK_VOP_SRC_SEL_GPLL           = 0,
    DCLK_VOP_SRC_SEL_CPLL,
    DCLK_VOP_SRC_SEL_V0PLL,
    DCLK_VOP_SRC_SEL_AUPLL,
    DCLK0_VOP_SRC_DIV_SHIFT         = 0,
    DCLK0_VOP_SRC_DIV_MASK          = 0x7f << DCLK0_VOP_SRC_DIV_SHIFT,

    /* CRU_CLK_SEL112_CON */
    DCLK2_VOP_SEL_SHIFT         = 11,
    DCLK2_VOP_SEL_MASK          = 3 << DCLK2_VOP_SEL_SHIFT,
    DCLK1_VOP_SEL_SHIFT         = 9,
    DCLK1_VOP_SEL_MASK          = 3 << DCLK1_VOP_SEL_SHIFT,
    DCLK0_VOP_SEL_SHIFT         = 7,
    DCLK0_VOP_SEL_MASK          = 3 << DCLK0_VOP_SEL_SHIFT,
    DCLK2_VOP_SRC_SEL_SHIFT         = 5,
    DCLK2_VOP_SRC_SEL_MASK          = 3 << DCLK2_VOP_SRC_SEL_SHIFT,
    DCLK2_VOP_SRC_DIV_SHIFT         = 0,
    DCLK2_VOP_SRC_DIV_MASK          = 0x1f << DCLK2_VOP_SRC_DIV_SHIFT,

    /* CRU_CLK_SEL113_CON */
    DCLK3_VOP_SRC_SEL_SHIFT         = 7,
    DCLK3_VOP_SRC_SEL_MASK          = 3 << DCLK3_VOP_SRC_SEL_SHIFT,
    DCLK3_VOP_SRC_DIV_SHIFT         = 0,
    DCLK3_VOP_SRC_DIV_MASK          = 0x7f << DCLK3_VOP_SRC_DIV_SHIFT,

    /* CRU_CLK_SEL117_CON */
    CLK_AUX16MHZ_1_DIV_SHIFT        = 8,
    CLK_AUX16MHZ_1_DIV_MASK         = 0xff << CLK_AUX16MHZ_1_DIV_SHIFT,
    CLK_AUX16MHZ_0_DIV_SHIFT        = 0,
    CLK_AUX16MHZ_0_DIV_MASK         = 0xff << CLK_AUX16MHZ_0_DIV_SHIFT,

    /* CRU_CLK_SEL165_CON */
    PCLK_CENTER_ROOT_SEL_SHIFT      = 6,
    PCLK_CENTER_ROOT_SEL_MASK       = 3 << PCLK_CENTER_ROOT_SEL_SHIFT,
    PCLK_CENTER_ROOT_SEL_200M       = 0,
    PCLK_CENTER_ROOT_SEL_100M,
    PCLK_CENTER_ROOT_SEL_50M,
    PCLK_CENTER_ROOT_SEL_24M,
    HCLK_CENTER_ROOT_SEL_SHIFT      = 4,
    HCLK_CENTER_ROOT_SEL_MASK       = 3 << HCLK_CENTER_ROOT_SEL_SHIFT,
    HCLK_CENTER_ROOT_SEL_400M       = 0,
    HCLK_CENTER_ROOT_SEL_200M,
    HCLK_CENTER_ROOT_SEL_100M,
    HCLK_CENTER_ROOT_SEL_24M,
    ACLK_CENTER_LOW_ROOT_SEL_SHIFT      = 2,
    ACLK_CENTER_LOW_ROOT_SEL_MASK       = 3 << ACLK_CENTER_LOW_ROOT_SEL_SHIFT,
    ACLK_CENTER_LOW_ROOT_SEL_500M       = 0,
    ACLK_CENTER_LOW_ROOT_SEL_250M,
    ACLK_CENTER_LOW_ROOT_SEL_100M,
    ACLK_CENTER_LOW_ROOT_SEL_24M,
    ACLK_CENTER_ROOT_SEL_SHIFT      = 0,
    ACLK_CENTER_ROOT_SEL_MASK       = 3 << ACLK_CENTER_ROOT_SEL_SHIFT,
    ACLK_CENTER_ROOT_SEL_700M       = 0,
    ACLK_CENTER_ROOT_SEL_400M,
    ACLK_CENTER_ROOT_SEL_200M,
    ACLK_CENTER_ROOT_SEL_24M,

    /* CRU_CLK_SEL172_CON */
    CCLK_SDIO_SRC_SEL_SHIFT         = 8,
    CCLK_SDIO_SRC_SEL_MASK          = 3 << CCLK_SDIO_SRC_SEL_SHIFT,
    CCLK_SDIO_SRC_SEL_GPLL          = 0,
    CCLK_SDIO_SRC_SEL_CPLL,
    CCLK_SDIO_SRC_SEL_24M,
    CCLK_SDIO_SRC_DIV_SHIFT         = 2,
    CCLK_SDIO_SRC_DIV_MASK          = 0x3f << CCLK_SDIO_SRC_DIV_SHIFT,

    /* CRU_CLK_SEL176_CON */
    CLK_PCIE_PHY1_PLL_DIV_SHIFT     = 6,
    CLK_PCIE_PHY1_PLL_DIV_MASK      = 0x3f << CLK_PCIE_PHY1_PLL_DIV_SHIFT,
    CLK_PCIE_PHY0_PLL_DIV_SHIFT     = 0,
    CLK_PCIE_PHY0_PLL_DIV_MASK      = 0x3f << CLK_PCIE_PHY0_PLL_DIV_SHIFT,

    /* CRU_CLK_SEL177_CON */
    CLK_PCIE_PHY2_REF_SEL_SHIFT     = 8,
    CLK_PCIE_PHY2_REF_SEL_MASK      = 1 << CLK_PCIE_PHY2_REF_SEL_SHIFT,
    CLK_PCIE_PHY1_REF_SEL_SHIFT     = 7,
    CLK_PCIE_PHY1_REF_SEL_MASK      = 1 << CLK_PCIE_PHY1_REF_SEL_SHIFT,
    CLK_PCIE_PHY0_REF_SEL_SHIFT     = 6,
    CLK_PCIE_PHY0_REF_SEL_MASK      = 1 << CLK_PCIE_PHY0_REF_SEL_SHIFT,
    CLK_PCIE_PHY_REF_SEL_24M        = 0,
    CLK_PCIE_PHY_REF_SEL_PPLL,
    CLK_PCIE_PHY2_PLL_DIV_SHIFT     = 0,
    CLK_PCIE_PHY2_PLL_DIV_MASK      = 0x3f << CLK_PCIE_PHY2_PLL_DIV_SHIFT,

    /* PMUCRU_CLK_SEL2_CON */
    CLK_PMU1PWM_SEL_SHIFT           = 9,
    CLK_PMU1PWM_SEL_MASK            = 3 << CLK_PMU1PWM_SEL_SHIFT,

    /* PMUCRU_CLK_SEL3_CON */
    CLK_I2C0_SEL_SHIFT          = 6,
    CLK_I2C0_SEL_MASK           = 1 << CLK_I2C0_SEL_SHIFT,
    CLK_I2C_SEL_200M            = 0,
    CLK_I2C_SEL_100M,
};

static struct rk_pll_rate_table rk3588_pll_rates[] = {
    /* _mhz, _p, _m, _s, _k */
    RK3588_PLL_RATE(1500000000, 2, 250, 1, 0),
    RK3588_PLL_RATE(1200000000, 2, 200, 1, 0),
    RK3588_PLL_RATE(1188000000, 2, 198, 1, 0),
    RK3588_PLL_RATE(1100000000, 3, 550, 2, 0),
    RK3588_PLL_RATE(1008000000, 2, 336, 2, 0),
    RK3588_PLL_RATE(1000000000, 3, 500, 2, 0),
    RK3588_PLL_RATE(900000000, 2, 300, 2, 0),
    RK3588_PLL_RATE(850000000, 3, 425, 2, 0),
    RK3588_PLL_RATE(816000000, 2, 272, 2, 0),
    RK3588_PLL_RATE(786432000, 2, 262, 2, 9437),
    RK3588_PLL_RATE(786000000, 1, 131, 2, 0),
    RK3588_PLL_RATE(742500000, 4, 495, 2, 0),
    RK3588_PLL_RATE(722534400, 8, 963, 2, 24850),
    RK3588_PLL_RATE(600000000, 2, 200, 2, 0),
    RK3588_PLL_RATE(594000000, 2, 198, 2, 0),
    RK3588_PLL_RATE(200000000, 3, 400, 4, 0),
    RK3588_PLL_RATE(100000000, 3, 400, 5, 0),
    { /* sentinel */ },
};

static struct rk_pll_clock rk3588_pll_clks[] = {
    [B0PLL] = PLL(pll_rk3588, PLL_B0PLL, RK3588_B0_PLL_CON(0),
              RK3588_B0_PLL_MODE_CON, 0, 15, 0,
              rk3588_pll_rates),
    [B1PLL] = PLL(pll_rk3588, PLL_B1PLL, RK3588_B1_PLL_CON(8),
              RK3588_B1_PLL_MODE_CON, 0, 15, 0,
              rk3588_pll_rates),
    [LPLL] = PLL(pll_rk3588, PLL_LPLL, RK3588_LPLL_CON(16),
             RK3588_LPLL_MODE_CON, 0, 15, 0, rk3588_pll_rates),
    [V0PLL] = PLL(pll_rk3588, PLL_V0PLL, RK3588_PLL_CON(88),
              RK3588_MODE_CON0, 4, 15, 0, rk3588_pll_rates),
    [AUPLL] = PLL(pll_rk3588, PLL_AUPLL, RK3588_PLL_CON(96),
              RK3588_MODE_CON0, 6, 15, 0, rk3588_pll_rates),
    [CPLL] = PLL(pll_rk3588, PLL_CPLL, RK3588_PLL_CON(104),
             RK3588_MODE_CON0, 8, 15, 0, rk3588_pll_rates),
    [GPLL] = PLL(pll_rk3588, PLL_GPLL, RK3588_PLL_CON(112),
             RK3588_MODE_CON0, 2, 15, 0, rk3588_pll_rates),
    [NPLL] = PLL(pll_rk3588, PLL_NPLL, RK3588_PLL_CON(120),
             RK3588_MODE_CON0, 0, 15, 0, rk3588_pll_rates),
    [PPLL] = PLL(pll_rk3588, PLL_PPLL, RK3588_PMU_PLL_CON(128),
             RK3588_MODE_CON0, 10, 15, 0, rk3588_pll_rates),
};
struct rk3588_clk_gate
{
    const char *name;
    const char *parent_name;

    int offset;
    int con_bit;
};
#undef GATE
#define GATE(_id, _name,    \
_pname, _offset, _con_bit) \
[_id] =                     \
{                           \
    .name = _name,          \
    .parent_name = _pname,  \
    .offset = _offset,    \
    .con_bit = _con_bit,    \
}
static struct rk3588_clk_gate clk_gates[] =
{
    /*
     * CRU Clock-Architecture
     */
    /* fixed */

    /* top */
    GATE(PCLK_MIPI_DCPHY0, "pclk_mipi_dcphy0", "pclk_top_root", RK3588_CLKGATE_CON(3), 14),
    GATE(PCLK_MIPI_DCPHY1, "pclk_mipi_dcphy1", "pclk_top_root", RK3588_CLKGATE_CON(4), 3),
    GATE(PCLK_CSIPHY0, "pclk_csiphy0", "pclk_top_root", RK3588_CLKGATE_CON(1), 6),
    GATE(PCLK_CSIPHY1, "pclk_csiphy1", "pclk_top_root", RK3588_CLKGATE_CON(1), 8),
    GATE(PCLK_CRU, "pclk_cru", "pclk_top_root", RK3588_CLKGATE_CON(5), 0),

    /* bigcore0 */
    GATE(PCLK_BIGCORE0_PVTM, "pclk_bigcore0_pvtm", "pclk_bigcore0_root", RK3588_BIGCORE0_CLKGATE_CON(1), 0),
    GATE(CLK_BIGCORE0_PVTM, "clk_bigcore0_pvtm", "xin24m", RK3588_BIGCORE0_CLKGATE_CON(0), 12),
    GATE(CLK_CORE_BIGCORE0_PVTM, "clk_core_bigcore0_pvtm", "armclk_b01", RK3588_BIGCORE0_CLKGATE_CON(0), 13),

    /* bigcore1 */
    GATE(PCLK_BIGCORE1_PVTM, "pclk_bigcore1_pvtm", "pclk_bigcore1_root", RK3588_BIGCORE1_CLKGATE_CON(1), 0),
    GATE(CLK_BIGCORE1_PVTM, "clk_bigcore1_pvtm", "xin24m", RK3588_BIGCORE1_CLKGATE_CON(0), 12),
    GATE(CLK_CORE_BIGCORE1_PVTM, "clk_core_bigcore1_pvtm", "armclk_b23", RK3588_BIGCORE1_CLKGATE_CON(0), 13),

    /* dsu */
    GATE(PCLK_LITCORE_PVTM, "pclk_litcore_pvtm", "pclk_dsu_ns_root", RK3588_DSU_CLKGATE_CON(2), 6),
    GATE(PCLK_DBG, "pclk_dbg", "pclk_dsu_root", RK3588_DSU_CLKGATE_CON(1), 7),
    GATE(PCLK_DSU, "pclk_dsu", "pclk_dsu_root", RK3588_DSU_CLKGATE_CON(1), 6),
    GATE(PCLK_S_DAPLITE, "pclk_s_daplite", "pclk_dsu_ns_root", RK3588_DSU_CLKGATE_CON(1), 8),
    GATE(PCLK_M_DAPLITE, "pclk_m_daplite", "pclk_dsu_root", RK3588_DSU_CLKGATE_CON(1), 9),
    GATE(CLK_LITCORE_PVTM, "clk_litcore_pvtm", "xin24m", RK3588_DSU_CLKGATE_CON(2), 0),
    GATE(CLK_CORE_LITCORE_PVTM, "clk_core_litcore_pvtm", "armclk_l", RK3588_DSU_CLKGATE_CON(2), 1),

    /* audio */
    GATE(HCLK_I2S2_2CH, "hclk_i2s2_2ch", "hclk_audio_root", RK3588_CLKGATE_CON(7), 12),
    GATE(HCLK_I2S3_2CH, "hclk_i2s3_2ch", "hclk_audio_root", RK3588_CLKGATE_CON(7), 13),
    GATE(MCLK_I2S2_2CH, "mclk_i2s2_2ch", "clk_i2s2_2ch", RK3588_CLKGATE_CON(8), 0),
    GATE(MCLK_I2S3_2CH, "mclk_i2s3_2ch", "clk_i2s3_2ch", RK3588_CLKGATE_CON(8), 3),
    GATE(CLK_DAC_ACDCDIG, "clk_dac_acdcdig", "mclk_i2s3_2ch", RK3588_CLKGATE_CON(8), 4),
    GATE(PCLK_ACDCDIG, "pclk_acdcdig", "pclk_audio_root", RK3588_CLKGATE_CON(7), 11),
    GATE(HCLK_I2S0_8CH, "hclk_i2s0_8ch", "hclk_audio_root", RK3588_CLKGATE_CON(7), 4),

    GATE(MCLK_I2S0_8CH_TX, "mclk_i2s0_8ch_tx", "clk_i2s0_8ch_tx", RK3588_CLKGATE_CON(7), 7),

    GATE(MCLK_I2S0_8CH_RX, "mclk_i2s0_8ch_rx", "clk_i2s0_8ch_rx", RK3588_CLKGATE_CON(7), 10),

    GATE(HCLK_PDM1, "hclk_pdm1", "hclk_audio_root", RK3588_CLKGATE_CON(9), 6),

    GATE(HCLK_SPDIF0, "hclk_spdif0", "hclk_audio_root", RK3588_CLKGATE_CON(8), 14),
    GATE(MCLK_SPDIF0, "mclk_spdif0", "clk_spdif0", RK3588_CLKGATE_CON(9), 1),

    GATE(HCLK_SPDIF1, "hclk_spdif1", "hclk_audio_root", RK3588_CLKGATE_CON(9), 2),
    GATE(MCLK_SPDIF1, "mclk_spdif1", "clk_spdif1", RK3588_CLKGATE_CON(9), 5),

    /* bus */
    GATE(PCLK_MAILBOX0, "pclk_mailbox0", "pclk_top_root", RK3588_CLKGATE_CON(16), 11),
    GATE(PCLK_MAILBOX1, "pclk_mailbox1", "pclk_top_root", RK3588_CLKGATE_CON(16), 12),
    GATE(PCLK_MAILBOX2, "pclk_mailbox2", "pclk_top_root", RK3588_CLKGATE_CON(16), 13),
    GATE(PCLK_PMU2, "pclk_pmu2", "pclk_top_root", RK3588_CLKGATE_CON(19), 3),
    GATE(PCLK_PMUCM0_INTMUX, "pclk_pmucm0_intmux", "pclk_top_root", RK3588_CLKGATE_CON(19), 4),
    GATE(PCLK_DDRCM0_INTMUX, "pclk_ddrcm0_intmux", "pclk_top_root", RK3588_CLKGATE_CON(19), 5),

    GATE(PCLK_PWM1, "pclk_pwm1", "pclk_top_root", RK3588_CLKGATE_CON(15), 3),
    GATE(CLK_PWM1_CAPTURE, "clk_pwm1_capture", "xin24m", RK3588_CLKGATE_CON(15), 5),
    GATE(PCLK_PWM2, "pclk_pwm2", "pclk_top_root", RK3588_CLKGATE_CON(15), 6),
    GATE(CLK_PWM2_CAPTURE, "clk_pwm2_capture", "xin24m", RK3588_CLKGATE_CON(15), 8),
    GATE(PCLK_PWM3, "pclk_pwm3", "pclk_top_root", RK3588_CLKGATE_CON(15), 9),
    GATE(CLK_PWM3_CAPTURE, "clk_pwm3_capture", "xin24m", RK3588_CLKGATE_CON(15), 11),

    GATE(PCLK_BUSTIMER0, "pclk_bustimer0", "pclk_top_root", RK3588_CLKGATE_CON(15), 12),
    GATE(PCLK_BUSTIMER1, "pclk_bustimer1", "pclk_top_root", RK3588_CLKGATE_CON(15), 13),
    GATE(CLK_BUSTIMER0, "clk_bustimer0", "clk_bus_timer_root", RK3588_CLKGATE_CON(15), 15),
    GATE(CLK_BUSTIMER1, "clk_bustimer1", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 0),
    GATE(CLK_BUSTIMER2, "clk_bustimer2", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 1),
    GATE(CLK_BUSTIMER3, "clk_bustimer3", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 2),
    GATE(CLK_BUSTIMER4, "clk_bustimer4", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 3),
    GATE(CLK_BUSTIMER5, "clk_bustimer5", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 4),
    GATE(CLK_BUSTIMER6, "clk_bustimer6", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 5),
    GATE(CLK_BUSTIMER7, "clk_bustimer7", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 6),
    GATE(CLK_BUSTIMER8, "clk_bustimer8", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 7),
    GATE(CLK_BUSTIMER9, "clk_bustimer9", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 8),
    GATE(CLK_BUSTIMER10, "clk_bustimer10", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 9),
    GATE(CLK_BUSTIMER11, "clk_bustimer11", "clk_bus_timer_root", RK3588_CLKGATE_CON(16), 10),

    GATE(PCLK_WDT0, "pclk_wdt0", "pclk_top_root", RK3588_CLKGATE_CON(15), 0),
    GATE(TCLK_WDT0, "tclk_wdt0", "xin24m", RK3588_CLKGATE_CON(15), 1),

    GATE(PCLK_CAN0, "pclk_can0", "pclk_top_root", RK3588_CLKGATE_CON(11), 8),
    GATE(CLK_CAN0, "clk_can0", "gpll_cpll_p", RK3588_CLKGATE_CON(11), 9),
    GATE(PCLK_CAN1, "pclk_can1", "pclk_top_root", RK3588_CLKGATE_CON(11), 10),
    GATE(CLK_CAN1, "clk_can1", "gpll_cpll_p", RK3588_CLKGATE_CON(11), 11),
    GATE(PCLK_CAN2, "pclk_can2", "pclk_top_root", RK3588_CLKGATE_CON(11), 12),
    GATE(CLK_CAN2, "clk_can2", "gpll_cpll_p", RK3588_CLKGATE_CON(11), 13),

    GATE(ACLK_DECOM, "aclk_decom", "aclk_bus_root", RK3588_CLKGATE_CON(17), 6),
    GATE(PCLK_DECOM, "pclk_decom", "pclk_top_root", RK3588_CLKGATE_CON(17), 7),
    GATE(DCLK_DECOM, "dclk_decom", "gpll_spll_p", RK3588_CLKGATE_CON(17), 8),
    GATE(ACLK_DMAC0, "aclk_dmac0", "aclk_bus_root", RK3588_CLKGATE_CON(10), 5),
    GATE(ACLK_DMAC1, "aclk_dmac1", "aclk_bus_root", RK3588_CLKGATE_CON(10), 6),
    GATE(ACLK_DMAC2, "aclk_dmac2", "aclk_bus_root", RK3588_CLKGATE_CON(10), 7),
    GATE(ACLK_GIC, "aclk_gic", "aclk_bus_root", RK3588_CLKGATE_CON(10), 3),

    GATE(PCLK_GPIO1, "pclk_gpio1", "pclk_top_root", RK3588_CLKGATE_CON(16), 14),
    GATE(DBCLK_GPIO1, "dbclk_gpio1", "mux_24m_32k_p", RK3588_CLKGATE_CON(16), 15),
    GATE(PCLK_GPIO2, "pclk_gpio2", "pclk_top_root", RK3588_CLKGATE_CON(17), 0),
    GATE(DBCLK_GPIO2, "dbclk_gpio2", "mux_24m_32k_p", RK3588_CLKGATE_CON(17), 1),
    GATE(PCLK_GPIO3, "pclk_gpio3", "pclk_top_root", RK3588_CLKGATE_CON(17), 2),
    GATE(DBCLK_GPIO3, "dbclk_gpio3", "mux_24m_32k_p", RK3588_CLKGATE_CON(17), 3),
    GATE(PCLK_GPIO4, "pclk_gpio4", "pclk_top_root", RK3588_CLKGATE_CON(17), 4),
    GATE(DBCLK_GPIO4, "dbclk_gpio4", "mux_24m_32k_p", RK3588_CLKGATE_CON(17), 5),

    GATE(PCLK_I2C1, "pclk_i2c1", "pclk_top_root", RK3588_CLKGATE_CON(10), 8),
    GATE(PCLK_I2C2, "pclk_i2c2", "pclk_top_root", RK3588_CLKGATE_CON(10), 9),
    GATE(PCLK_I2C3, "pclk_i2c3", "pclk_top_root", RK3588_CLKGATE_CON(10), 10),
    GATE(PCLK_I2C4, "pclk_i2c4", "pclk_top_root", RK3588_CLKGATE_CON(10), 11),
    GATE(PCLK_I2C5, "pclk_i2c5", "pclk_top_root", RK3588_CLKGATE_CON(10), 12),
    GATE(PCLK_I2C6, "pclk_i2c6", "pclk_top_root", RK3588_CLKGATE_CON(10), 13),
    GATE(PCLK_I2C7, "pclk_i2c7", "pclk_top_root", RK3588_CLKGATE_CON(10), 14),
    GATE(PCLK_I2C8, "pclk_i2c8", "pclk_top_root", RK3588_CLKGATE_CON(10), 15),
    GATE(CLK_I2C1, "clk_i2c1", "mux_200m_100m_p", RK3588_CLKGATE_CON(11), 0),
    GATE(CLK_I2C2, "clk_i2c2", "mux_200m_100m_p", RK3588_CLKGATE_CON(11), 1),
    GATE(CLK_I2C3, "clk_i2c3", "mux_200m_100m_p", RK3588_CLKGATE_CON(11), 2),
    GATE(CLK_I2C4, "clk_i2c4", "mux_200m_100m_p", RK3588_CLKGATE_CON(11), 3),
    GATE(CLK_I2C5, "clk_i2c5", "mux_200m_100m_p", RK3588_CLKGATE_CON(11), 4),
    GATE(CLK_I2C6, "clk_i2c6", "mux_200m_100m_p", RK3588_CLKGATE_CON(11), 5),
    GATE(CLK_I2C7, "clk_i2c7", "mux_200m_100m_p", RK3588_CLKGATE_CON(11), 6),
    GATE(CLK_I2C8, "clk_i2c8", "mux_200m_100m_p", RK3588_CLKGATE_CON(11), 7),

    GATE(PCLK_OTPC_NS, "pclk_otpc_ns", "pclk_top_root", RK3588_CLKGATE_CON(18), 9),
    GATE(CLK_OTPC_NS, "clk_otpc_ns", "xin24m", RK3588_CLKGATE_CON(18), 10),
    GATE(CLK_OTPC_ARB, "clk_otpc_arb", "xin24m", RK3588_CLKGATE_CON(18), 11),
    GATE(CLK_OTP_PHY_G, "clk_otp_phy_g", "xin24m", RK3588_CLKGATE_CON(18), 13),
    GATE(CLK_OTPC_AUTO_RD_G, "clk_otpc_auto_rd_g", "xin24m", RK3588_CLKGATE_CON(18), 12),

    GATE(PCLK_SARADC, "pclk_saradc", "pclk_top_root", RK3588_CLKGATE_CON(11), 14),
    GATE(CLK_SARADC, "clk_saradc", "gpll_24m_p", RK3588_CLKGATE_CON(11), 15),

    GATE(PCLK_SPI0, "pclk_spi0", "pclk_top_root", RK3588_CLKGATE_CON(14), 6),
    GATE(PCLK_SPI1, "pclk_spi1", "pclk_top_root", RK3588_CLKGATE_CON(14), 7),
    GATE(PCLK_SPI2, "pclk_spi2", "pclk_top_root", RK3588_CLKGATE_CON(14), 8),
    GATE(PCLK_SPI3, "pclk_spi3", "pclk_top_root", RK3588_CLKGATE_CON(14), 9),
    GATE(PCLK_SPI4, "pclk_spi4", "pclk_top_root", RK3588_CLKGATE_CON(14), 10),
    GATE(CLK_SPI0, "clk_spi0", "mux_200m_150m_24m_p", RK3588_CLKGATE_CON(14), 11),
    GATE(CLK_SPI1, "clk_spi1", "mux_200m_150m_24m_p", RK3588_CLKGATE_CON(14), 12),
    GATE(CLK_SPI2, "clk_spi2", "mux_200m_150m_24m_p", RK3588_CLKGATE_CON(14), 13),
    GATE(CLK_SPI3, "clk_spi3", "mux_200m_150m_24m_p", RK3588_CLKGATE_CON(14), 14),
    GATE(CLK_SPI4, "clk_spi4", "mux_200m_150m_24m_p", RK3588_CLKGATE_CON(14), 15),

    GATE(ACLK_SPINLOCK, "aclk_spinlock", "aclk_bus_root", RK3588_CLKGATE_CON(18), 6),
    GATE(PCLK_TSADC, "pclk_tsadc", "pclk_top_root", RK3588_CLKGATE_CON(12), 0),
    GATE(CLK_TSADC, "clk_tsadc", "gpll_24m_p", RK3588_CLKGATE_CON(12), 1),

    GATE(PCLK_UART1, "pclk_uart1", "pclk_top_root", RK3588_CLKGATE_CON(12), 2),
    GATE(PCLK_UART2, "pclk_uart2", "pclk_top_root", RK3588_CLKGATE_CON(12), 3),
    GATE(PCLK_UART3, "pclk_uart3", "pclk_top_root", RK3588_CLKGATE_CON(12), 4),
    GATE(PCLK_UART4, "pclk_uart4", "pclk_top_root", RK3588_CLKGATE_CON(12), 5),
    GATE(PCLK_UART5, "pclk_uart5", "pclk_top_root", RK3588_CLKGATE_CON(12), 6),
    GATE(PCLK_UART6, "pclk_uart6", "pclk_top_root", RK3588_CLKGATE_CON(12), 7),
    GATE(PCLK_UART7, "pclk_uart7", "pclk_top_root", RK3588_CLKGATE_CON(12), 8),
    GATE(PCLK_UART8, "pclk_uart8", "pclk_top_root", RK3588_CLKGATE_CON(12), 9),
    GATE(PCLK_UART9, "pclk_uart9", "pclk_top_root", RK3588_CLKGATE_CON(12), 10),

    GATE(CLK_UART1_SRC, "clk_uart1_src", "gpll_cpll_p", RK3588_CLKGATE_CON(12), 11),
    GATE(CLK_UART1_FRAC, "clk_uart1_frac", "clk_uart1_src", RK3588_CLKGATE_CON(12), 12),
    GATE(SCLK_UART1, "sclk_uart1", "clk_uart1", RK3588_CLKGATE_CON(12), 13),
    GATE(CLK_UART2_SRC, "clk_uart2_src", "gpll_cpll_p", RK3588_CLKGATE_CON(12), 14),
    GATE(CLK_UART2_FRAC, "clk_uart2_frac", "clk_uart2_src", RK3588_CLKGATE_CON(12), 15),
    GATE(SCLK_UART2, "sclk_uart2", "clk_uart2", RK3588_CLKGATE_CON(13), 0),
    GATE(CLK_UART3_SRC, "clk_uart3_src", "gpll_cpll_p", RK3588_CLKGATE_CON(13), 1),
    GATE(CLK_UART3_FRAC, "clk_uart3_frac", "clk_uart3_src", RK3588_CLKGATE_CON(13), 2),
    GATE(SCLK_UART3, "sclk_uart3", "clk_uart3", RK3588_CLKGATE_CON(13), 3),
    GATE(CLK_UART4_SRC, "clk_uart4_src", "gpll_cpll_p", RK3588_CLKGATE_CON(13), 4),
    GATE(CLK_UART4_FRAC, "clk_uart4_frac", "clk_uart4_src", RK3588_CLKGATE_CON(13), 5),
    GATE(SCLK_UART4, "sclk_uart4", "clk_uart4", RK3588_CLKGATE_CON(13), 6),
    GATE(CLK_UART5_SRC, "clk_uart5_src", "gpll_cpll_p", RK3588_CLKGATE_CON(13), 7),
    GATE(CLK_UART5_FRAC, "clk_uart5_frac", "clk_uart5_src", RK3588_CLKGATE_CON(13), 8),
    GATE(SCLK_UART5, "sclk_uart5", "clk_uart5", RK3588_CLKGATE_CON(13), 9),
    GATE(CLK_UART6_SRC, "clk_uart6_src", "gpll_cpll_p", RK3588_CLKGATE_CON(13), 10),
    GATE(CLK_UART6_FRAC, "clk_uart6_frac", "clk_uart6_src", RK3588_CLKGATE_CON(13), 11),
    GATE(SCLK_UART6, "sclk_uart6", "clk_uart6", RK3588_CLKGATE_CON(13), 12),
    GATE(CLK_UART7_SRC, "clk_uart7_src", "gpll_cpll_p", RK3588_CLKGATE_CON(13), 13),
    GATE(CLK_UART7_FRAC, "clk_uart7_frac", "clk_uart7_src", RK3588_CLKGATE_CON(13), 14),
    GATE(SCLK_UART7, "sclk_uart7", "clk_uart7", RK3588_CLKGATE_CON(13), 15),
    GATE(CLK_UART8_SRC, "clk_uart8_src", "gpll_cpll_p", RK3588_CLKGATE_CON(14), 0),
    GATE(CLK_UART8_FRAC, "clk_uart8_frac", "clk_uart8_src", RK3588_CLKGATE_CON(14), 1),
    GATE(SCLK_UART8, "sclk_uart8", "clk_uart8", RK3588_CLKGATE_CON(14), 2),
    GATE(CLK_UART9_SRC, "clk_uart9_src", "gpll_cpll_p", RK3588_CLKGATE_CON(14), 3),
    GATE(CLK_UART9_FRAC, "clk_uart9_frac", "clk_uart9_src", RK3588_CLKGATE_CON(14), 4),
    GATE(SCLK_UART9, "sclk_uart9", "clk_uart9", RK3588_CLKGATE_CON(14), 5),

    /* center */
    GATE(ACLK_DMA2DDR, "aclk_dma2ddr", "aclk_center_root", RK3588_CLKGATE_CON(69), 5),
    GATE(ACLK_DDR_SHAREMEM, "aclk_ddr_sharemem", "aclk_center_low_root", RK3588_CLKGATE_CON(69), 6),
    GATE(FCLK_DDR_CM0_CORE, "fclk_ddr_cm0_core", "hclk_center_root", RK3588_CLKGATE_CON(69), 14),
    GATE(CLK_DDR_TIMER0, "clk_ddr_timer0", "clk_ddr_timer_root", RK3588_CLKGATE_CON(70), 0),
    GATE(CLK_DDR_TIMER1, "clk_ddr_timer1", "clk_ddr_timer_root", RK3588_CLKGATE_CON(70), 1),
    GATE(TCLK_WDT_DDR, "tclk_wdt_ddr", "xin24m", RK3588_CLKGATE_CON(70), 2),
    GATE(PCLK_WDT, "pclk_wdt", "pclk_center_root", RK3588_CLKGATE_CON(70), 7),
    GATE(PCLK_TIMER, "pclk_timer", "pclk_center_root", RK3588_CLKGATE_CON(70), 8),
    GATE(PCLK_DMA2DDR, "pclk_dma2ddr", "pclk_center_root", RK3588_CLKGATE_CON(70), 9),
    GATE(PCLK_SHAREMEM, "pclk_sharemem", "pclk_center_root", RK3588_CLKGATE_CON(70), 10),

    /* gpu */
    GATE(CLK_GPU, "clk_gpu", "clk_gpu_src", RK3588_CLKGATE_CON(66), 4),
    GATE(CLK_GPU_COREGROUP, "clk_gpu_coregroup", "clk_gpu_src", RK3588_CLKGATE_CON(66), 6),
    GATE(CLK_GPU_PVTM, "clk_gpu_pvtm", "xin24m", RK3588_CLKGATE_CON(67), 0),
    GATE(CLK_CORE_GPU_PVTM, "clk_core_gpu_pvtm", "clk_gpu_src", RK3588_CLKGATE_CON(67), 1),

    /* isp1 */
    GATE(CLK_ISP1_CORE_MARVIN, "clk_isp1_core_marvin", "clk_isp1_core", RK3588_CLKGATE_CON(26), 3),
    GATE(CLK_ISP1_CORE_VICAP, "clk_isp1_core_vicap", "clk_isp1_core", RK3588_CLKGATE_CON(26), 4),

    /* npu */
    GATE(ACLK_NPU1, "aclk_npu1", "clk_npu_dsu0", RK3588_CLKGATE_CON(27), 0),
    GATE(HCLK_NPU1, "hclk_npu1", "hclk_npu_root", RK3588_CLKGATE_CON(27), 2),
    GATE(ACLK_NPU2, "aclk_npu2", "clk_npu_dsu0", RK3588_CLKGATE_CON(28), 0),
    GATE(HCLK_NPU2, "hclk_npu2", "hclk_npu_root", RK3588_CLKGATE_CON(28), 2),
    GATE(FCLK_NPU_CM0_CORE, "fclk_npu_cm0_core", "hclk_npu_cm0_root", RK3588_CLKGATE_CON(30), 3),
    GATE(PCLK_NPU_PVTM, "pclk_npu_pvtm", "pclk_npu_root", RK3588_CLKGATE_CON(29), 12),
    GATE(PCLK_NPU_GRF, "pclk_npu_grf", "pclk_npu_root", RK3588_CLKGATE_CON(29), 13),
    GATE(CLK_NPU_PVTM, "clk_npu_pvtm", "xin24m", RK3588_CLKGATE_CON(29), 14),
    GATE(CLK_CORE_NPU_PVTM, "clk_core_npu_pvtm", "clk_npu_dsu0", RK3588_CLKGATE_CON(29), 15),
    GATE(ACLK_NPU0, "aclk_npu0", "clk_npu_dsu0", RK3588_CLKGATE_CON(30), 6),
    GATE(HCLK_NPU0, "hclk_npu0", "hclk_npu_root", RK3588_CLKGATE_CON(30), 8),
    GATE(PCLK_NPU_TIMER, "pclk_npu_timer", "pclk_npu_root", RK3588_CLKGATE_CON(29), 6),
    GATE(CLK_NPUTIMER0, "clk_nputimer0", "clk_nputimer_root", RK3588_CLKGATE_CON(29), 8),
    GATE(CLK_NPUTIMER1, "clk_nputimer1", "clk_nputimer_root", RK3588_CLKGATE_CON(29), 9),
    GATE(PCLK_NPU_WDT, "pclk_npu_wdt", "pclk_npu_root", RK3588_CLKGATE_CON(29), 10),
    GATE(TCLK_NPU_WDT, "tclk_npu_wdt", "xin24m", RK3588_CLKGATE_CON(29), 11),

    /* nvm */
    GATE(ACLK_EMMC, "aclk_emmc", "aclk_nvm_root", RK3588_CLKGATE_CON(31), 5),
    GATE(TMCLK_EMMC, "tmclk_emmc", "xin24m", RK3588_CLKGATE_CON(31), 8),


    /* php */
    GATE(ACLK_PHP_GIC_ITS, "aclk_php_gic_its", "aclk_pcie_root", RK3588_CLKGATE_CON(34), 6),
    GATE(ACLK_PCIE_BRIDGE, "aclk_pcie_bridge", "aclk_pcie_root", RK3588_CLKGATE_CON(32), 8),
    GATE(ACLK_MMU_PCIE, "aclk_mmu_pcie", "aclk_pcie_bridge", RK3588_CLKGATE_CON(34), 7),
    GATE(ACLK_MMU_PHP, "aclk_mmu_php", "aclk_php_root", RK3588_CLKGATE_CON(34), 8),
    GATE(ACLK_PCIE_4L_DBI, "aclk_pcie_4l_dbi", "aclk_php_root", RK3588_CLKGATE_CON(32), 13),
    GATE(ACLK_PCIE_2L_DBI, "aclk_pcie_2l_dbi", "aclk_php_root", RK3588_CLKGATE_CON(32), 14),
    GATE(ACLK_PCIE_1L0_DBI, "aclk_pcie_1l0_dbi", "aclk_php_root", RK3588_CLKGATE_CON(32), 15),
    GATE(ACLK_PCIE_1L1_DBI, "aclk_pcie_1l1_dbi", "aclk_php_root", RK3588_CLKGATE_CON(33), 0),
    GATE(ACLK_PCIE_1L2_DBI, "aclk_pcie_1l2_dbi", "aclk_php_root", RK3588_CLKGATE_CON(33), 1),
    GATE(ACLK_PCIE_4L_MSTR, "aclk_pcie_4l_mstr", "aclk_mmu_pcie", RK3588_CLKGATE_CON(33), 2),
    GATE(ACLK_PCIE_2L_MSTR, "aclk_pcie_2l_mstr", "aclk_mmu_pcie", RK3588_CLKGATE_CON(33), 3),
    GATE(ACLK_PCIE_1L0_MSTR, "aclk_pcie_1l0_mstr", "aclk_mmu_pcie", RK3588_CLKGATE_CON(33), 4),
    GATE(ACLK_PCIE_1L1_MSTR, "aclk_pcie_1l1_mstr", "aclk_mmu_pcie", RK3588_CLKGATE_CON(33), 5),
    GATE(ACLK_PCIE_1L2_MSTR, "aclk_pcie_1l2_mstr", "aclk_mmu_pcie", RK3588_CLKGATE_CON(33), 6),
    GATE(ACLK_PCIE_4L_SLV, "aclk_pcie_4l_slv", "aclk_php_root", RK3588_CLKGATE_CON(33), 7),
    GATE(ACLK_PCIE_2L_SLV, "aclk_pcie_2l_slv", "aclk_php_root", RK3588_CLKGATE_CON(33), 8),
    GATE(ACLK_PCIE_1L0_SLV, "aclk_pcie_1l0_slv", "aclk_php_root", RK3588_CLKGATE_CON(33), 9),
    GATE(ACLK_PCIE_1L1_SLV, "aclk_pcie_1l1_slv", "aclk_php_root", RK3588_CLKGATE_CON(33), 10),
    GATE(ACLK_PCIE_1L2_SLV, "aclk_pcie_1l2_slv", "aclk_php_root", RK3588_CLKGATE_CON(33), 11),
    GATE(PCLK_PCIE_4L, "pclk_pcie_4l", "pclk_php_root", RK3588_CLKGATE_CON(33), 12),
    GATE(PCLK_PCIE_2L, "pclk_pcie_2l", "pclk_php_root", RK3588_CLKGATE_CON(33), 13),
    GATE(PCLK_PCIE_1L0, "pclk_pcie_1l0", "pclk_php_root", RK3588_CLKGATE_CON(33), 14),
    GATE(PCLK_PCIE_1L1, "pclk_pcie_1l1", "pclk_php_root", RK3588_CLKGATE_CON(33), 15),
    GATE(PCLK_PCIE_1L2, "pclk_pcie_1l2", "pclk_php_root", RK3588_CLKGATE_CON(34), 0),
    GATE(CLK_PCIE_AUX0, "clk_pcie_aux0", "xin24m", RK3588_CLKGATE_CON(34), 1),
    GATE(CLK_PCIE_AUX1, "clk_pcie_aux1", "xin24m", RK3588_CLKGATE_CON(34), 2),
    GATE(CLK_PCIE_AUX2, "clk_pcie_aux2", "xin24m", RK3588_CLKGATE_CON(34), 3),
    GATE(CLK_PCIE_AUX3, "clk_pcie_aux3", "xin24m", RK3588_CLKGATE_CON(34), 4),
    GATE(CLK_PCIE_AUX4, "clk_pcie_aux4", "xin24m", RK3588_CLKGATE_CON(34), 5),
    GATE(CLK_PIPEPHY0_REF, "clk_pipephy0_ref", "xin24m", RK3588_CLKGATE_CON(37), 0),
    GATE(CLK_PIPEPHY1_REF, "clk_pipephy1_ref", "xin24m", RK3588_CLKGATE_CON(37), 1),
    GATE(CLK_PIPEPHY2_REF, "clk_pipephy2_ref", "xin24m", RK3588_CLKGATE_CON(37), 2),
    GATE(PCLK_GMAC0, "pclk_gmac0", "pclk_php_root", RK3588_CLKGATE_CON(32), 3),
    GATE(PCLK_GMAC1, "pclk_gmac1", "pclk_php_root", RK3588_CLKGATE_CON(32), 4),
    GATE(ACLK_GMAC0, "aclk_gmac0", "aclk_mmu_php", RK3588_CLKGATE_CON(32), 10),
    GATE(ACLK_GMAC1, "aclk_gmac1", "aclk_mmu_php", RK3588_CLKGATE_CON(32), 11),
    GATE(CLK_PMALIVE0, "clk_pmalive0", "xin24m", RK3588_CLKGATE_CON(37), 4),
    GATE(CLK_PMALIVE1, "clk_pmalive1", "xin24m", RK3588_CLKGATE_CON(37), 5),
    GATE(CLK_PMALIVE2, "clk_pmalive2", "xin24m", RK3588_CLKGATE_CON(37), 6),
    GATE(ACLK_SATA0, "aclk_sata0", "aclk_mmu_php", RK3588_CLKGATE_CON(37), 7),
    GATE(ACLK_SATA1, "aclk_sata1", "aclk_mmu_php", RK3588_CLKGATE_CON(37), 8),
    GATE(ACLK_SATA2, "aclk_sata2", "aclk_mmu_php", RK3588_CLKGATE_CON(37), 9),
    GATE(ACLK_USB3OTG2, "aclk_usb3otg2", "aclk_mmu_php", RK3588_CLKGATE_CON(35), 7),
    GATE(SUSPEND_CLK_USB3OTG2, "suspend_clk_usb3otg2", "xin24m", RK3588_CLKGATE_CON(35), 8),
    GATE(REF_CLK_USB3OTG2, "ref_clk_usb3otg2", "xin24m", RK3588_CLKGATE_CON(35), 9),
    GATE(PCLK_PCIE_COMBO_PIPE_PHY0, "pclk_pcie_combo_pipe_phy0", "pclk_top_root", RK3588_PHP_CLKGATE_CON(0), 5),
    GATE(PCLK_PCIE_COMBO_PIPE_PHY1, "pclk_pcie_combo_pipe_phy1", "pclk_top_root", RK3588_PHP_CLKGATE_CON(0), 6),
    GATE(PCLK_PCIE_COMBO_PIPE_PHY2, "pclk_pcie_combo_pipe_phy2", "pclk_top_root", RK3588_PHP_CLKGATE_CON(0), 7),
    GATE(PCLK_PCIE_COMBO_PIPE_PHY, "pclk_pcie_combo_pipe_phy", "pclk_top_root", RK3588_PHP_CLKGATE_CON(0), 8),

    /* rga */
    GATE(HCLK_RGA3_1, "hclk_rga3_1", "hclk_rga3_root", RK3588_CLKGATE_CON(76), 4),
    GATE(ACLK_RGA3_1, "aclk_rga3_1", "aclk_rga3_root", RK3588_CLKGATE_CON(76), 5),

    /* vdec */
    GATE(SUSPEND_CLK_USB3OTG0, "suspend_clk_usb3otg0", "xin24m", RK3588_CLKGATE_CON(42), 5),
    GATE(REF_CLK_USB3OTG0, "ref_clk_usb3otg0", "xin24m", RK3588_CLKGATE_CON(42), 6),
    GATE(SUSPEND_CLK_USB3OTG1, "suspend_clk_usb3otg1", "xin24m", RK3588_CLKGATE_CON(42), 8),
    GATE(REF_CLK_USB3OTG1, "ref_clk_usb3otg1", "xin24m", RK3588_CLKGATE_CON(42), 9),

    /* vdpu */
    GATE(HCLK_IEP2P0, "hclk_iep2p0", "hclk_vdpu_root", RK3588_CLKGATE_CON(45), 4),
    GATE(HCLK_JPEG_ENCODER0, "hclk_jpeg_encoder0", "hclk_vdpu_root", RK3588_CLKGATE_CON(44), 11),
    GATE(HCLK_JPEG_ENCODER1, "hclk_jpeg_encoder1", "hclk_vdpu_root", RK3588_CLKGATE_CON(44), 13),
    GATE(HCLK_JPEG_ENCODER2, "hclk_jpeg_encoder2", "hclk_vdpu_root", RK3588_CLKGATE_CON(44), 15),
    GATE(HCLK_JPEG_ENCODER3, "hclk_jpeg_encoder3", "hclk_vdpu_root", RK3588_CLKGATE_CON(45), 1),
    GATE(HCLK_JPEG_DECODER, "hclk_jpeg_decoder", "hclk_vdpu_root", RK3588_CLKGATE_CON(45), 3),
    GATE(HCLK_RGA2, "hclk_rga2", "hclk_vdpu_root", RK3588_CLKGATE_CON(45), 7),
    GATE(ACLK_RGA2, "aclk_rga2", "aclk_vdpu_root", RK3588_CLKGATE_CON(45), 8),
    GATE(HCLK_RGA3_0, "hclk_rga3_0", "hclk_vdpu_root", RK3588_CLKGATE_CON(45), 10),
    GATE(ACLK_RGA3_0, "aclk_rga3_0", "aclk_vdpu_root", RK3588_CLKGATE_CON(45), 11),
    GATE(HCLK_VPU, "hclk_vpu", "hclk_vdpu_root", RK3588_CLKGATE_CON(44), 9),

    /* venc */
    GATE(HCLK_RKVENC0, "hclk_rkvenc0", "hclk_rkvenc0_root", RK3588_CLKGATE_CON(47), 4),
    GATE(ACLK_RKVENC0, "aclk_rkvenc0", "aclk_rkvenc0_root", RK3588_CLKGATE_CON(47), 5),

    /* vi */
    GATE(ICLK_CSIHOST0, "iclk_csihost0", "iclk_csihost01", RK3588_CLKGATE_CON(51), 11),
    GATE(ICLK_CSIHOST1, "iclk_csihost1", "iclk_csihost01", RK3588_CLKGATE_CON(51), 12),
    GATE(PCLK_CSI_HOST_0, "pclk_csi_host_0", "pclk_vi_root", RK3588_CLKGATE_CON(50), 4),
    GATE(PCLK_CSI_HOST_1, "pclk_csi_host_1", "pclk_vi_root", RK3588_CLKGATE_CON(50), 5),
    GATE(PCLK_CSI_HOST_2, "pclk_csi_host_2", "pclk_vi_root", RK3588_CLKGATE_CON(50), 6),
    GATE(PCLK_CSI_HOST_3, "pclk_csi_host_3", "pclk_vi_root", RK3588_CLKGATE_CON(50), 7),
    GATE(PCLK_CSI_HOST_4, "pclk_csi_host_4", "pclk_vi_root", RK3588_CLKGATE_CON(50), 8),
    GATE(PCLK_CSI_HOST_5, "pclk_csi_host_5", "pclk_vi_root", RK3588_CLKGATE_CON(50), 9),
    GATE(ACLK_FISHEYE0, "aclk_fisheye0", "aclk_vi_root", RK3588_CLKGATE_CON(49), 14),
    GATE(HCLK_FISHEYE0, "hclk_fisheye0", "hclk_vi_root", RK3588_CLKGATE_CON(49), 15),
    GATE(ACLK_FISHEYE1, "aclk_fisheye1", "aclk_vi_root", RK3588_CLKGATE_CON(50), 1),
    GATE(HCLK_FISHEYE1, "hclk_fisheye1", "hclk_vi_root", RK3588_CLKGATE_CON(50), 2),
    GATE(CLK_ISP0_CORE_MARVIN, "clk_isp0_core_marvin", "clk_isp0_core", RK3588_CLKGATE_CON(49), 10),
    GATE(CLK_ISP0_CORE_VICAP, "clk_isp0_core_vicap", "clk_isp0_core", RK3588_CLKGATE_CON(49), 11),
    GATE(ACLK_ISP0, "aclk_isp0", "aclk_vi_root", RK3588_CLKGATE_CON(49), 12),
    GATE(HCLK_ISP0, "hclk_isp0", "hclk_vi_root", RK3588_CLKGATE_CON(49), 13),
    GATE(ACLK_VICAP, "aclk_vicap", "aclk_vi_root", RK3588_CLKGATE_CON(49), 7),
    GATE(HCLK_VICAP, "hclk_vicap", "hclk_vi_root", RK3588_CLKGATE_CON(49), 8),

    /* vo0 */
    GATE(PCLK_DP0, "pclk_dp0", "pclk_vo0_root", RK3588_CLKGATE_CON(56), 4),
    GATE(PCLK_DP1, "pclk_dp1", "pclk_vo0_root", RK3588_CLKGATE_CON(56), 5),
    GATE(PCLK_S_DP0, "pclk_s_dp0", "pclk_vo0_s_root", RK3588_CLKGATE_CON(56), 6),
    GATE(PCLK_S_DP1, "pclk_s_dp1", "pclk_vo0_s_root", RK3588_CLKGATE_CON(56), 7),
    GATE(CLK_DP0, "clk_dp0", "aclk_vo0_root", RK3588_CLKGATE_CON(56), 8),
    GATE(CLK_DP1, "clk_dp1", "aclk_vo0_root", RK3588_CLKGATE_CON(56), 9),
    GATE(HCLK_HDCP_KEY0, "hclk_hdcp_key0", "hclk_vo0_s_root", RK3588_CLKGATE_CON(55), 11),
    GATE(PCLK_HDCP0, "pclk_hdcp0", "pclk_vo0_root", RK3588_CLKGATE_CON(55), 14),
    GATE(ACLK_TRNG0, "aclk_trng0", "aclk_vo0_root", RK3588_CLKGATE_CON(56), 0),
    GATE(PCLK_TRNG0, "pclk_trng0", "pclk_vo0_root", RK3588_CLKGATE_CON(56), 1),
    GATE(PCLK_VO0GRF, "pclk_vo0grf", "pclk_vo0_root", RK3588_CLKGATE_CON(55), 10),
    GATE(MCLK_I2S4_8CH_TX, "mclk_i2s4_8ch_tx", "clk_i2s4_8ch_tx", RK3588_CLKGATE_CON(56), 13),
    GATE(MCLK_I2S8_8CH_TX, "mclk_i2s8_8ch_tx", "clk_i2s8_8ch_tx", RK3588_CLKGATE_CON(57), 1),
    GATE(MCLK_SPDIF2_DP0, "mclk_spdif2_dp0", "clk_spdif2_dp0", RK3588_CLKGATE_CON(57), 5),
    GATE(MCLK_SPDIF2, "mclk_spdif2", "clk_spdif2_dp0", RK3588_CLKGATE_CON(57), 6),
    GATE(MCLK_SPDIF5_DP1, "mclk_spdif5_dp1", "clk_spdif5_dp1", RK3588_CLKGATE_CON(57), 10),
    GATE(MCLK_SPDIF5, "mclk_spdif5", "clk_spdif5_dp1", RK3588_CLKGATE_CON(57), 11),

    /* vo1 */
    GATE(PCLK_EDP0, "pclk_edp0", "pclk_vo1_root", RK3588_CLKGATE_CON(62), 0),
    GATE(CLK_EDP0_24M, "clk_edp0_24m", "xin24m", RK3588_CLKGATE_CON(62), 1),
    GATE(PCLK_EDP1, "pclk_edp1", "pclk_vo1_root", RK3588_CLKGATE_CON(62), 3),
    GATE(CLK_EDP1_24M, "clk_edp1_24m", "xin24m", RK3588_CLKGATE_CON(62), 4),
    GATE(HCLK_HDCP_KEY1, "hclk_hdcp_key1", "hclk_vo1_s_root", RK3588_CLKGATE_CON(60), 4),
    GATE(PCLK_HDCP1, "pclk_hdcp1", "pclk_vo1_root", RK3588_CLKGATE_CON(60), 7),
    GATE(ACLK_HDMIRX, "aclk_hdmirx", "aclk_hdmirx_root", RK3588_CLKGATE_CON(61), 9),
    GATE(PCLK_HDMIRX, "pclk_hdmirx", "pclk_vo1_root", RK3588_CLKGATE_CON(61), 10),
    GATE(CLK_HDMIRX_REF, "clk_hdmirx_ref", "aclk_hdcp1_root", RK3588_CLKGATE_CON(61), 11),
    GATE(CLK_HDMIRX_AUD, "clk_hdmirx_aud", "clk_hdmirx_aud_mux", RK3588_CLKGATE_CON(61), 14),
    GATE(PCLK_HDMITX0, "pclk_hdmitx0", "pclk_vo1_root", RK3588_CLKGATE_CON(60), 11),
    GATE(CLK_HDMITX0_REF, "clk_hdmitx0_ref", "aclk_hdcp1_root", RK3588_CLKGATE_CON(61), 0),
    GATE(PCLK_HDMITX1, "pclk_hdmitx1", "pclk_vo1_root", RK3588_CLKGATE_CON(61), 2),
    GATE(CLK_HDMITX1_REF, "clk_hdmitx1_ref", "aclk_hdcp1_root", RK3588_CLKGATE_CON(61), 7),
    GATE(ACLK_TRNG1, "aclk_trng1", "aclk_hdcp1_root", RK3588_CLKGATE_CON(60), 9),
    GATE(PCLK_TRNG1, "pclk_trng1", "pclk_vo1_root", RK3588_CLKGATE_CON(60), 10),
    GATE(0, "pclk_vo1grf", "pclk_vo1_root", RK3588_CLKGATE_CON(59), 12),
    GATE(PCLK_S_EDP0, "pclk_s_edp0", "pclk_vo1_s_root", RK3588_CLKGATE_CON(59), 14),
    GATE(PCLK_S_EDP1, "pclk_s_edp1", "pclk_vo1_s_root", RK3588_CLKGATE_CON(59), 15),
    GATE(PCLK_S_HDMIRX, "pclk_s_hdmirx", "pclk_vo1_s_root", RK3588_CLKGATE_CON(65), 8),
    GATE(MCLK_I2S10_8CH_RX, "mclk_i2s10_8ch_rx", "clk_i2s10_8ch_rx", RK3588_CLKGATE_CON(65), 7),
    GATE(MCLK_I2S7_8CH_RX, "mclk_i2s7_8ch_rx", "clk_i2s7_8ch_rx", RK3588_CLKGATE_CON(60), 3),
    GATE(MCLK_I2S9_8CH_RX, "mclk_i2s9_8ch_rx", "clk_i2s9_8ch_rx", RK3588_CLKGATE_CON(65), 3),
    GATE(MCLK_I2S5_8CH_TX, "mclk_i2s5_8ch_tx", "clk_i2s5_8ch_tx", RK3588_CLKGATE_CON(62), 8),
    GATE(MCLK_I2S6_8CH_TX, "mclk_i2s6_8ch_tx", "clk_i2s6_8ch_tx", RK3588_CLKGATE_CON(62), 15),
    GATE(MCLK_I2S6_8CH_RX, "mclk_i2s6_8ch_rx", "clk_i2s6_8ch_rx", RK3588_CLKGATE_CON(63), 2),
    GATE(MCLK_SPDIF3, "mclk_spdif3", "clk_spdif3", RK3588_CLKGATE_CON(63), 7),
    GATE(MCLK_SPDIF4, "mclk_spdif4", "clk_spdif4", RK3588_CLKGATE_CON(63), 11),
    GATE(CLK_HDMIHDP0, "clk_hdmihdp0", "xin24m", RK3588_CLKGATE_CON(73), 12),
    GATE(CLK_HDMIHDP1, "clk_hdmihdp1", "xin24m", RK3588_CLKGATE_CON(73), 13),
    GATE(PCLK_HDPTX0, "pclk_hdptx0", "pclk_top_root", RK3588_CLKGATE_CON(72), 5),
    GATE(PCLK_HDPTX1, "pclk_hdptx1", "pclk_top_root", RK3588_CLKGATE_CON(72), 6),
    GATE(PCLK_USBDPPHY0, "pclk_usbdpphy0", "pclk_top_root", RK3588_CLKGATE_CON(72), 2),
    GATE(PCLK_USBDPPHY1, "pclk_usbdpphy1", "pclk_top_root", RK3588_CLKGATE_CON(72), 4),
    GATE(HCLK_VOP, "hclk_vop", "hclk_vop_root", RK3588_CLKGATE_CON(52), 8),
    GATE(ACLK_VOP, "aclk_vop", "aclk_vop_sub_src", RK3588_CLKGATE_CON(52), 9),
    GATE(PCLK_DSIHOST0, "pclk_dsihost0", "pclk_vop_root", RK3588_CLKGATE_CON(53), 4),
    GATE(PCLK_DSIHOST1, "pclk_dsihost1", "pclk_vop_root", RK3588_CLKGATE_CON(53), 5),
    GATE(CLK_VOP_PMU, "clk_vop_pmu", "xin24m", RK3588_CLKGATE_CON(53), 8),
    GATE(ACLK_VOP_DOBY, "aclk_vop_doby", "aclk_vop_root", RK3588_CLKGATE_CON(53), 10),
    GATE(CLK_USBDP_PHY0_IMMORTAL, "clk_usbdp_phy0_immortal", "xin24m", RK3588_CLKGATE_CON(2), 8),
    GATE(CLK_USBDP_PHY1_IMMORTAL, "clk_usbdp_phy1_immortal", "xin24m", RK3588_CLKGATE_CON(2), 15),

    GATE(CLK_REF_PIPE_PHY0_OSC_SRC, "clk_ref_pipe_phy0_osc_src", "xin24m", RK3588_CLKGATE_CON(77), 0),
    GATE(CLK_REF_PIPE_PHY1_OSC_SRC, "clk_ref_pipe_phy1_osc_src", "xin24m", RK3588_CLKGATE_CON(77), 1),
    GATE(CLK_REF_PIPE_PHY2_OSC_SRC, "clk_ref_pipe_phy2_osc_src", "xin24m", RK3588_CLKGATE_CON(77), 2),

    /* pmu */
    GATE(PCLK_PMU0_ROOT, "pclk_pmu0_root", "pclk_pmu1_root", RK3588_PMU_CLKGATE_CON(5), 0),
    GATE(CLK_PMU0, "clk_pmu0", "xin24m", RK3588_PMU_CLKGATE_CON(5), 1),
    GATE(PCLK_PMU0, "pclk_pmu0", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(5), 2),
    GATE(PCLK_PMU0IOC, "pclk_pmu0ioc", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(5), 4),
    GATE(PCLK_GPIO0, "pclk_gpio0", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(5), 5),
    GATE(PCLK_I2C0, "pclk_i2c0", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(2), 1),
    GATE(HCLK_I2S1_8CH, "hclk_i2s1_8ch", "hclk_pmu1_root", RK3588_PMU_CLKGATE_CON(2), 7),
    GATE(MCLK_I2S1_8CH_TX, "mclk_i2s1_8ch_tx", "clk_i2s1_8ch_tx", RK3588_PMU_CLKGATE_CON(2), 10),
    GATE(MCLK_I2S1_8CH_RX, "mclk_i2s1_8ch_rx", "clk_i2s1_8ch_rx", RK3588_PMU_CLKGATE_CON(2), 13),
    GATE(PCLK_PMU1, "pclk_pmu1", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(1), 0),
    GATE(CLK_DDR_FAIL_SAFE, "clk_ddr_fail_safe", "clk_pmu0", RK3588_PMU_CLKGATE_CON(1), 1),
    GATE(CLK_PMU1, "clk_pmu1", "clk_pmu0", RK3588_PMU_CLKGATE_CON(1), 3),
    GATE(HCLK_PDM0, "hclk_pdm0", "hclk_pmu1_root", RK3588_PMU_CLKGATE_CON(2), 14),
    GATE(HCLK_VAD, "hclk_vad", "hclk_pmu1_root", RK3588_PMU_CLKGATE_CON(3), 0),
    GATE(FCLK_PMU_CM0_CORE, "fclk_pmu_cm0_core", "hclk_pmu_cm0_root", RK3588_PMU_CLKGATE_CON(0), 13),
    GATE(PCLK_PMU1_IOC, "pclk_pmu1_ioc", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(1), 5),
    GATE(PCLK_PMU1PWM, "pclk_pmu1pwm", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(1), 12),
    GATE(CLK_PMU1PWM_CAPTURE, "clk_pmu1pwm_capture", "xin24m", RK3588_PMU_CLKGATE_CON(1), 14),
    GATE(PCLK_PMU1TIMER, "pclk_pmu1timer", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(1), 8),
    GATE(CLK_PMU1TIMER0, "clk_pmu1timer0", "clk_pmu1timer_root", RK3588_PMU_CLKGATE_CON(1), 10),
    GATE(CLK_PMU1TIMER1, "clk_pmu1timer1", "clk_pmu1timer_root", RK3588_PMU_CLKGATE_CON(1), 11),
    GATE(SCLK_UART0, "sclk_uart0", "clk_uart0", RK3588_PMU_CLKGATE_CON(2), 5),
    GATE(PCLK_UART0, "pclk_uart0", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(2), 6),
    GATE(PCLK_PMU1WDT, "pclk_pmu1wdt", "pclk_pmu0_root", RK3588_PMU_CLKGATE_CON(1), 6),
#define RK3588_PHYREF_ALT_GATE      0xc38
    GATE(CLK_PHY0_REF_ALT_P, "clk_phy0_ref_alt_p", "ppll", RK3588_PHYREF_ALT_GATE, 0),
    GATE(CLK_PHY0_REF_ALT_M, "clk_phy0_ref_alt_m", "ppll", RK3588_PHYREF_ALT_GATE, 1),
    GATE(CLK_PHY1_REF_ALT_P, "clk_phy1_ref_alt_p", "ppll", RK3588_PHYREF_ALT_GATE, 2),
    GATE(CLK_PHY1_REF_ALT_M, "clk_phy1_ref_alt_m", "ppll", RK3588_PHYREF_ALT_GATE, 3),

    GATE(HCLK_SPDIFRX0, "hclk_spdifrx0", "hclk_vo1", RK3588_CLKGATE_CON(63), 12),
    GATE(HCLK_SPDIFRX1, "hclk_spdifrx1", "hclk_vo1", RK3588_CLKGATE_CON(63), 14),
    GATE(HCLK_SPDIFRX2, "hclk_spdifrx2", "hclk_vo1", RK3588_CLKGATE_CON(64), 0),
    GATE(HCLK_SPDIF4, "hclk_spdif4", "hclk_vo1", RK3588_CLKGATE_CON(63), 8),
    GATE(HCLK_SPDIF3, "hclk_spdif3", "hclk_vo1", RK3588_CLKGATE_CON(63), 4),
    GATE(HCLK_I2S6_8CH, "hclk_i2s6_8ch", "hclk_vo1", RK3588_CLKGATE_CON(63), 3),
    GATE(HCLK_I2S5_8CH, "hclk_i2s5_8ch", "hclk_vo1", RK3588_CLKGATE_CON(62), 12),
    GATE(HCLK_I2S9_8CH, "hclk_i2s9_8ch", "hclk_vo1", RK3588_CLKGATE_CON(65), 0),
    GATE(HCLK_I2S7_8CH, "hclk_i2s7_8ch", "hclk_vo1", RK3588_CLKGATE_CON(60), 0),
    GATE(HCLK_I2S10_8CH, "hclk_i2s10_8ch", "hclk_vo1", RK3588_CLKGATE_CON(65), 4),
    GATE(ACLK_HDCP1, "aclk_hdcp1", "aclk_hdcp1_pre", RK3588_CLKGATE_CON(60), 5),
    GATE(HCLK_HDCP1, "hclk_hdcp1", "hclk_vo1", RK3588_CLKGATE_CON(60), 6),
    GATE(HCLK_SPDIF5_DP1, "hclk_spdif5_dp1", "hclk_vo0", RK3588_CLKGATE_CON(57), 7),
    GATE(HCLK_SPDIF2_DP0, "hclk_spdif2_dp0", "hclk_vo0", RK3588_CLKGATE_CON(57), 2),
    GATE(HCLK_I2S8_8CH, "hclk_i2s8_8ch", "hclk_vo0", RK3588_CLKGATE_CON(56), 14),
    GATE(HCLK_I2S4_8CH, "hclk_i2s4_8ch", "hclk_vo0", RK3588_CLKGATE_CON(56), 10),
    GATE(ACLK_HDCP0, "aclk_hdcp0", "aclk_hdcp0_pre", RK3588_CLKGATE_CON(55), 12),
    GATE(HCLK_HDCP0, "hclk_hdcp0", "hclk_vo0", RK3588_CLKGATE_CON(55), 13),
    GATE(HCLK_RKVENC1, "hclk_rkvenc1", "hclk_rkvenc1_pre", RK3588_CLKGATE_CON(48), 4),
    GATE(ACLK_RKVENC1, "aclk_rkvenc1", "aclk_rkvenc1_pre", RK3588_CLKGATE_CON(48), 5),
    GATE(ACLK_VPU, "aclk_vpu", "aclk_vdpu_low_pre", RK3588_CLKGATE_CON(44), 8),
    GATE(ACLK_IEP2P0, "aclk_iep2p0", "aclk_vdpu_low_pre", RK3588_CLKGATE_CON(45), 5),
    GATE(ACLK_JPEG_ENCODER0, "aclk_jpeg_encoder0", "aclk_vdpu_low_pre", RK3588_CLKGATE_CON(44), 10),
    GATE(ACLK_JPEG_ENCODER1, "aclk_jpeg_encoder1", "aclk_vdpu_low_pre", RK3588_CLKGATE_CON(44), 12),
    GATE(ACLK_JPEG_ENCODER2, "aclk_jpeg_encoder2", "aclk_vdpu_low_pre", RK3588_CLKGATE_CON(44), 14),
    GATE(ACLK_JPEG_ENCODER3, "aclk_jpeg_encoder3", "aclk_vdpu_low_pre", RK3588_CLKGATE_CON(45), 0),
    GATE(ACLK_JPEG_DECODER, "aclk_jpeg_decoder", "aclk_jpeg_decoder_pre", RK3588_CLKGATE_CON(45), 2),
    GATE(ACLK_USB3OTG1, "aclk_usb3otg1", "aclk_usb", RK3588_CLKGATE_CON(42), 7),
    GATE(HCLK_HOST0, "hclk_host0", "hclk_usb", RK3588_CLKGATE_CON(42), 10),
    GATE(HCLK_HOST_ARB0, "hclk_host_arb0", "hclk_usb", RK3588_CLKGATE_CON(42), 11),
    GATE(HCLK_HOST1, "hclk_host1", "hclk_usb", RK3588_CLKGATE_CON(42), 12),
    GATE(HCLK_HOST_ARB1, "hclk_host_arb1", "hclk_usb", RK3588_CLKGATE_CON(42), 13),
    GATE(ACLK_USB3OTG0, "aclk_usb3otg0", "aclk_usb", RK3588_CLKGATE_CON(42), 4),
    GATE(HCLK_SDIO, "hclk_sdio", "hclk_sdio_pre", RK3588_CLKGATE_CON(75), 2),
    GATE(HCLK_RKVDEC1, "hclk_rkvdec1", "hclk_rkvdec1_pre", RK3588_CLKGATE_CON(41), 2),
    GATE(ACLK_RKVDEC1, "aclk_rkvdec1", "aclk_rkvdec1_pre", RK3588_CLKGATE_CON(41), 3),
    GATE(HCLK_RKVDEC0, "hclk_rkvdec0", "hclk_rkvdec0_pre", RK3588_CLKGATE_CON(40), 3),
    GATE(ACLK_RKVDEC0, "aclk_rkvdec0", "aclk_rkvdec0_pre", RK3588_CLKGATE_CON(40), 4),
    GATE(CLK_PCIE4L_PIPE, "clk_pcie4l_pipe", "clk_pipe30phy_pipe0_i", RK3588_CLKGATE_CON(39), 0),
    GATE(CLK_PCIE2L_PIPE, "clk_pcie2l_pipe", "clk_pipe30phy_pipe2_i", RK3588_CLKGATE_CON(39), 1),
    GATE(CLK_PIPEPHY0_PIPE_G, "clk_pipephy0_pipe_g", "clk_pipephy0_pipe_i", RK3588_CLKGATE_CON(38), 3),
    GATE(CLK_PIPEPHY1_PIPE_G, "clk_pipephy1_pipe_g", "clk_pipephy1_pipe_i", RK3588_CLKGATE_CON(38), 4),
    GATE(CLK_PIPEPHY2_PIPE_G, "clk_pipephy2_pipe_g", "clk_pipephy2_pipe_i", RK3588_CLKGATE_CON(38), 5),
    GATE(CLK_PIPEPHY0_PIPE_ASIC_G, "clk_pipephy0_pipe_asic_g", "clk_pipephy0_pipe_i", RK3588_CLKGATE_CON(38), 6),
    GATE(CLK_PIPEPHY1_PIPE_ASIC_G, "clk_pipephy1_pipe_asic_g", "clk_pipephy1_pipe_i", RK3588_CLKGATE_CON(38), 7),
    GATE(CLK_PIPEPHY2_PIPE_ASIC_G, "clk_pipephy2_pipe_asic_g", "clk_pipephy2_pipe_i", RK3588_CLKGATE_CON(38), 8),
    GATE(CLK_PIPEPHY2_PIPE_U3_G, "clk_pipephy2_pipe_u3_g", "clk_pipephy2_pipe_i", RK3588_CLKGATE_CON(38), 9),
    GATE(CLK_PCIE1L2_PIPE, "clk_pcie1l2_pipe", "clk_pipephy0_pipe_g", RK3588_CLKGATE_CON(38), 13),
    GATE(CLK_PCIE1L0_PIPE, "clk_pcie1l0_pipe", "clk_pipephy1_pipe_g", RK3588_CLKGATE_CON(38), 14),
    GATE(CLK_PCIE1L1_PIPE, "clk_pcie1l1_pipe", "clk_pipephy2_pipe_g", RK3588_CLKGATE_CON(38), 15),
    GATE(HCLK_SFC, "hclk_sfc", "hclk_nvm", RK3588_CLKGATE_CON(31), 10),
    GATE(HCLK_SFC_XIP, "hclk_sfc_xip", "hclk_nvm", RK3588_CLKGATE_CON(31), 11),
    GATE(HCLK_EMMC, "hclk_emmc", "hclk_nvm", RK3588_CLKGATE_CON(31), 4),
    GATE(ACLK_ISP1, "aclk_isp1", "aclk_isp1_pre", RK3588_CLKGATE_CON(26), 5),
    GATE(HCLK_ISP1, "hclk_isp1", "hclk_isp1_pre", RK3588_CLKGATE_CON(26), 7),
    GATE(PCLK_AV1, "pclk_av1", "pclk_av1_pre", RK3588_CLKGATE_CON(68), 5),
    GATE(ACLK_AV1, "aclk_av1", "aclk_av1_pre", RK3588_CLKGATE_CON(68), 2),
/*
    GATE(ACLK_ISP1_PRE, "aclk_isp1_pre", "aclk_isp1_root", RK3588_CLKGATE_CON(26), 6),
    GATE(HCLK_ISP1_PRE, "hclk_isp1_pre", "hclk_isp1_root", RK3588_CLKGATE_CON(26), 8),
    GATE(HCLK_NVM, "hclk_nvm", "hclk_nvm_root", RK3588_CLKGATE_CON(31), 2),
    GATE(ACLK_USB, "aclk_usb", "aclk_usb_root", RK3588_CLKGATE_CON(42), 2),
    GATE(HCLK_USB, "hclk_usb", "hclk_usb_root", RK3588_CLKGATE_CON(42), 3),
    GATE(ACLK_JPEG_DECODER_PRE, "aclk_jpeg_decoder_pre", "aclk_jpeg_decoder_root", RK3588_CLKGATE_CON(44), 7),
    GATE(ACLK_VDPU_LOW_PRE, "aclk_vdpu_low_pre", "aclk_vdpu_low_root", RK3588_CLKGATE_CON(44), 5),
    GATE(ACLK_RKVENC1_PRE, "aclk_rkvenc1_pre", "aclk_rkvenc1_root", RK3588_CLKGATE_CON(48), 3),
    GATE(HCLK_RKVENC1_PRE, "hclk_rkvenc1_pre", "hclk_rkvenc1_root", RK3588_CLKGATE_CON(48), 2),
    GATE(HCLK_RKVDEC0_PRE, "hclk_rkvdec0_pre", "hclk_rkvdec0_root", RK3588_CLKGATE_CON(40), 5),
    GATE(ACLK_RKVDEC0_PRE, "aclk_rkvdec0_pre", "aclk_rkvdec0_root", RK3588_CLKGATE_CON(40), 6),
    GATE(HCLK_RKVDEC1_PRE, "hclk_rkvdec1_pre", "hclk_rkvdec1_root", RK3588_CLKGATE_CON(41), 4),
    GATE(ACLK_RKVDEC1_PRE, "aclk_rkvdec1_pre", "aclk_rkvdec1_root", RK3588_CLKGATE_CON(41), 5),
    GATE(ACLK_HDCP0_PRE, "aclk_hdcp0_pre", "aclk_vo0_root", RK3588_CLKGATE_CON(55), 9),
    GATE(HCLK_VO0, "hclk_vo0", "hclk_vo0_root", RK3588_CLKGATE_CON(55), 5),
    GATE(ACLK_HDCP1_PRE, "aclk_hdcp1_pre", "aclk_hdcp1_root", RK3588_CLKGATE_CON(59), 6),
    GATE(HCLK_VO1, "hclk_vo1", "hclk_vo1_root", RK3588_CLKGATE_CON(59), 9),
    GATE(ACLK_AV1_PRE, "aclk_av1_pre", "aclk_av1_root", RK3588_CLKGATE_CON(68), 1),
    GATE(PCLK_AV1_PRE, "pclk_av1_pre", "pclk_av1_root", RK3588_CLKGATE_CON(68), 4),
    GATE(HCLK_SDIO_PRE, "hclk_sdio_pre", "hclk_sdio_root", RK3588_CLKGATE_CON(75), 1),
*/
};

#include "clk-pll-rk3588.c"
#include "clk-mmc-phase.c"
#include "softrst.c"

static rt_ubase_t rk3588_center_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t con, sel, rate;

    switch (clk_id)
    {
    case ACLK_CENTER_ROOT:
        con = HWREG32(&cru->clksel_con[165]);
        sel = (con & ACLK_CENTER_ROOT_SEL_MASK) >>
              ACLK_CENTER_ROOT_SEL_SHIFT;
        if (sel == ACLK_CENTER_ROOT_SEL_700M)
            rate = 702 * MHz;
        else if (sel == ACLK_CENTER_ROOT_SEL_400M)
            rate = 396 * MHz;
        else if (sel == ACLK_CENTER_ROOT_SEL_200M)
            rate = 200 * MHz;
        else
            rate = OSC_HZ;
        break;
    case ACLK_CENTER_LOW_ROOT:
        con = HWREG32(&cru->clksel_con[165]);
        sel = (con & ACLK_CENTER_LOW_ROOT_SEL_MASK) >>
              ACLK_CENTER_LOW_ROOT_SEL_SHIFT;
        if (sel == ACLK_CENTER_LOW_ROOT_SEL_500M)
            rate = 500 * MHz;
        else if (sel == ACLK_CENTER_LOW_ROOT_SEL_250M)
            rate = 250 * MHz;
        else if (sel == ACLK_CENTER_LOW_ROOT_SEL_100M)
            rate = 100 * MHz;
        else
            rate = OSC_HZ;
        break;
    case HCLK_CENTER_ROOT:
        con = HWREG32(&cru->clksel_con[165]);
        sel = (con & HCLK_CENTER_ROOT_SEL_MASK) >>
              HCLK_CENTER_ROOT_SEL_SHIFT;
        if (sel == HCLK_CENTER_ROOT_SEL_400M)
            rate = 396 * MHz;
        else if (sel == HCLK_CENTER_ROOT_SEL_200M)
            rate = 200 * MHz;
        else if (sel == HCLK_CENTER_ROOT_SEL_100M)
            rate = 100 * MHz;
        else
            rate = OSC_HZ;
        break;
    case PCLK_CENTER_ROOT:
        con = HWREG32(&cru->clksel_con[165]);
        sel = (con & PCLK_CENTER_ROOT_SEL_MASK) >>
              PCLK_CENTER_ROOT_SEL_SHIFT;
        if (sel == PCLK_CENTER_ROOT_SEL_200M)
            rate = 200 * MHz;
        else if (sel == PCLK_CENTER_ROOT_SEL_100M)
            rate = 100 * MHz;
        else if (sel == PCLK_CENTER_ROOT_SEL_50M)
            rate = 50 * MHz;
        else
            rate = OSC_HZ;
        break;
    default:
        return -RT_ENOENT;
    }

    return rate;
}

static rt_ubase_t rk3588_center_set_clk(struct rk3588_clk_priv *priv,
                   rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int src_clk;

    switch (clk_id)
    {
    case ACLK_CENTER_ROOT:
        if (rate >= 700 * MHz)
            src_clk = ACLK_CENTER_ROOT_SEL_700M;
        else if (rate >= 396 * MHz)
            src_clk = ACLK_CENTER_ROOT_SEL_400M;
        else if (rate >= 200 * MHz)
            src_clk = ACLK_CENTER_ROOT_SEL_200M;
        else
            src_clk = ACLK_CENTER_ROOT_SEL_24M;
        rk_clrsetreg(&cru->clksel_con[165],
                 ACLK_CENTER_ROOT_SEL_MASK,
                 src_clk << ACLK_CENTER_ROOT_SEL_SHIFT);
        break;
    case ACLK_CENTER_LOW_ROOT:
        if (rate >= 500 * MHz)
            src_clk = ACLK_CENTER_LOW_ROOT_SEL_500M;
        else if (rate >= 250 * MHz)
            src_clk = ACLK_CENTER_LOW_ROOT_SEL_250M;
        else if (rate >= 99 * MHz)
            src_clk = ACLK_CENTER_LOW_ROOT_SEL_100M;
        else
            src_clk = ACLK_CENTER_LOW_ROOT_SEL_24M;
        rk_clrsetreg(&cru->clksel_con[165],
                 ACLK_CENTER_LOW_ROOT_SEL_MASK,
                 src_clk << ACLK_CENTER_LOW_ROOT_SEL_SHIFT);
        break;
    case HCLK_CENTER_ROOT:
        if (rate >= 396 * MHz)
            src_clk = HCLK_CENTER_ROOT_SEL_400M;
        else if (rate >= 198 * MHz)
            src_clk = HCLK_CENTER_ROOT_SEL_200M;
        else if (rate >= 99 * MHz)
            src_clk = HCLK_CENTER_ROOT_SEL_100M;
        else
            src_clk = HCLK_CENTER_ROOT_SEL_24M;
        rk_clrsetreg(&cru->clksel_con[165],
                 HCLK_CENTER_ROOT_SEL_MASK,
                 src_clk << HCLK_CENTER_ROOT_SEL_SHIFT);
        break;
    case PCLK_CENTER_ROOT:
        if (rate >= 198 * MHz)
            src_clk = PCLK_CENTER_ROOT_SEL_200M;
        else if (rate >= 99 * MHz)
            src_clk = PCLK_CENTER_ROOT_SEL_100M;
        else if (rate >= 50 * MHz)
            src_clk = PCLK_CENTER_ROOT_SEL_50M;
        else
            src_clk = PCLK_CENTER_ROOT_SEL_24M;
        rk_clrsetreg(&cru->clksel_con[165],
                 PCLK_CENTER_ROOT_SEL_MASK,
                 src_clk << PCLK_CENTER_ROOT_SEL_SHIFT);
        break;
    default:
        LOG_D("do not support this center freq\n");
        return -RT_EINVAL;
    }

    return rk3588_center_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_top_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t con, sel, div, rate, prate;

    switch (clk_id)
    {
    case ACLK_TOP_ROOT:
        con = HWREG32(&cru->clksel_con[8]);
        div = (con & ACLK_TOP_ROOT_DIV_MASK) >>
              ACLK_TOP_ROOT_DIV_SHIFT;
        sel = (con & ACLK_TOP_ROOT_SRC_SEL_MASK) >>
              ACLK_TOP_ROOT_SRC_SEL_SHIFT;
        if (sel == ACLK_TOP_ROOT_SRC_SEL_CPLL)
            prate = priv->cpll_hz;
        else
            prate = priv->gpll_hz;
        return DIV_TO_RATE(prate, div);
    case ACLK_LOW_TOP_ROOT:
        con = HWREG32(&cru->clksel_con[8]);
        div = (con & ACLK_LOW_TOP_ROOT_DIV_MASK) >>
              ACLK_LOW_TOP_ROOT_DIV_SHIFT;
        sel = (con & ACLK_LOW_TOP_ROOT_SRC_SEL_MASK) >>
              ACLK_LOW_TOP_ROOT_SRC_SEL_SHIFT;
        if (sel == ACLK_LOW_TOP_ROOT_SRC_SEL_CPLL)
            prate = priv->cpll_hz;
        else
            prate = priv->gpll_hz;
        return DIV_TO_RATE(prate, div);
    case PCLK_TOP_ROOT:
        con = HWREG32(&cru->clksel_con[8]);
        sel = (con & PCLK_TOP_ROOT_SEL_MASK) >> PCLK_TOP_ROOT_SEL_SHIFT;
        if (sel == PCLK_TOP_ROOT_SEL_100M)
            rate = 100 * MHz;
        else if (sel == PCLK_TOP_ROOT_SEL_50M)
            rate = 50 * MHz;
        else
            rate = OSC_HZ;
        break;
    default:
        return -RT_ENOENT;
    }

    return rate;
}

static rt_ubase_t rk3588_top_set_clk(struct rk3588_clk_priv *priv,
                rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int src_clk, src_clk_div;

    switch (clk_id)
    {
    case ACLK_TOP_ROOT:
        if (!(priv->cpll_hz % rate))
        {
            src_clk = ACLK_TOP_ROOT_SRC_SEL_CPLL;
            src_clk_div = RT_DIV_ROUND_UP(priv->cpll_hz, rate);
        } else {
            src_clk = ACLK_TOP_ROOT_SRC_SEL_GPLL;
            src_clk_div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
        }
        RT_ASSERT(src_clk_div - 1 <= 31);
        rk_clrsetreg(&cru->clksel_con[8],
                 ACLK_TOP_ROOT_DIV_MASK |
                 ACLK_TOP_ROOT_SRC_SEL_MASK,
                 (src_clk <<
                  ACLK_TOP_ROOT_SRC_SEL_SHIFT) |
                 (src_clk_div - 1) << ACLK_TOP_ROOT_DIV_SHIFT);
        break;
    case ACLK_LOW_TOP_ROOT:
        src_clk_div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
        RT_ASSERT(src_clk_div - 1 <= 31);
        rk_clrsetreg(&cru->clksel_con[8],
                 ACLK_LOW_TOP_ROOT_DIV_MASK |
                 ACLK_LOW_TOP_ROOT_SRC_SEL_MASK,
                 (ACLK_LOW_TOP_ROOT_SRC_SEL_GPLL <<
                  ACLK_LOW_TOP_ROOT_SRC_SEL_SHIFT) |
                 (src_clk_div - 1) << ACLK_LOW_TOP_ROOT_DIV_SHIFT);
        break;
    case PCLK_TOP_ROOT:
        if (rate == 100 * MHz)
            src_clk = PCLK_TOP_ROOT_SEL_100M;
        else if (rate == 50 * MHz)
            src_clk = PCLK_TOP_ROOT_SEL_50M;
        else
            src_clk = PCLK_TOP_ROOT_SEL_24M;
        rk_clrsetreg(&cru->clksel_con[8],
                 PCLK_TOP_ROOT_SEL_MASK,
                 src_clk << PCLK_TOP_ROOT_SEL_SHIFT);
        break;
    default:
        LOG_D("do not support this top freq\n");
        return -RT_EINVAL;
    }

    return rk3588_top_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_i2c_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t sel, con;
    rt_ubase_t rate;

    switch (clk_id)
    {
    case CLK_I2C0:
        con = HWREG32(&cru->pmuclksel_con[3]);
        sel = (con & CLK_I2C0_SEL_MASK) >> CLK_I2C0_SEL_SHIFT;
        break;
    case CLK_I2C1:
        con = HWREG32(&cru->clksel_con[38]);
        sel = (con & CLK_I2C1_SEL_MASK) >> CLK_I2C1_SEL_SHIFT;
        break;
    case CLK_I2C2:
        con = HWREG32(&cru->clksel_con[38]);
        sel = (con & CLK_I2C2_SEL_MASK) >> CLK_I2C2_SEL_SHIFT;
        break;
    case CLK_I2C3:
        con = HWREG32(&cru->clksel_con[38]);
        sel = (con & CLK_I2C3_SEL_MASK) >> CLK_I2C3_SEL_SHIFT;
        break;
    case CLK_I2C4:
        con = HWREG32(&cru->clksel_con[38]);
        sel = (con & CLK_I2C4_SEL_MASK) >> CLK_I2C4_SEL_SHIFT;
        break;
    case CLK_I2C5:
        con = HWREG32(&cru->clksel_con[38]);
        sel = (con & CLK_I2C5_SEL_MASK) >> CLK_I2C5_SEL_SHIFT;
        break;
    case CLK_I2C6:
        con = HWREG32(&cru->clksel_con[38]);
        sel = (con & CLK_I2C6_SEL_MASK) >> CLK_I2C6_SEL_SHIFT;
        break;
    case CLK_I2C7:
        con = HWREG32(&cru->clksel_con[38]);
        sel = (con & CLK_I2C7_SEL_MASK) >> CLK_I2C7_SEL_SHIFT;
        break;
    case CLK_I2C8:
        con = HWREG32(&cru->clksel_con[38]);
        sel = (con & CLK_I2C8_SEL_MASK) >> CLK_I2C8_SEL_SHIFT;
        break;
    default:
        return -RT_ENOENT;
    }
    if (sel == CLK_I2C_SEL_200M)
        rate = 200 * MHz;
    else
        rate = 100 * MHz;

    return rate;
}

static rt_ubase_t rk3588_i2c_set_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id,
                rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int src_clk;

    if (rate >= 198 * MHz)
        src_clk = CLK_I2C_SEL_200M;
    else
        src_clk = CLK_I2C_SEL_100M;

    switch (clk_id)
    {
    case CLK_I2C0:
        rk_clrsetreg(&cru->pmuclksel_con[3], CLK_I2C0_SEL_MASK,
                 src_clk << CLK_I2C0_SEL_SHIFT);
        break;
    case CLK_I2C1:
        rk_clrsetreg(&cru->clksel_con[38], CLK_I2C1_SEL_MASK,
                 src_clk << CLK_I2C1_SEL_SHIFT);
        break;
    case CLK_I2C2:
        rk_clrsetreg(&cru->clksel_con[38], CLK_I2C2_SEL_MASK,
                 src_clk << CLK_I2C2_SEL_SHIFT);
        break;
    case CLK_I2C3:
        rk_clrsetreg(&cru->clksel_con[38], CLK_I2C3_SEL_MASK,
                 src_clk << CLK_I2C3_SEL_SHIFT);
        break;
    case CLK_I2C4:
        rk_clrsetreg(&cru->clksel_con[38], CLK_I2C4_SEL_MASK,
                 src_clk << CLK_I2C4_SEL_SHIFT);
        break;
    case CLK_I2C5:
        rk_clrsetreg(&cru->clksel_con[38], CLK_I2C5_SEL_MASK,
                 src_clk << CLK_I2C5_SEL_SHIFT);
        break;
    case CLK_I2C6:
        rk_clrsetreg(&cru->clksel_con[38], CLK_I2C6_SEL_MASK,
                 src_clk << CLK_I2C6_SEL_SHIFT);
        break;
    case CLK_I2C7:
        rk_clrsetreg(&cru->clksel_con[38], CLK_I2C7_SEL_MASK,
                 src_clk << CLK_I2C7_SEL_SHIFT);
        break;
    case CLK_I2C8:
        rk_clrsetreg(&cru->clksel_con[38], CLK_I2C8_SEL_MASK,
                 src_clk << CLK_I2C8_SEL_SHIFT);
        break;
    default:
        return -RT_ENOENT;
    }

    return rk3588_i2c_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_spi_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    con = HWREG32(&cru->clksel_con[59]);

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
    case CLK_SPI4:
        sel = (con & CLK_SPI4_SEL_MASK) >> CLK_SPI4_SEL_SHIFT;
        break;
    default:
        return -RT_ENOENT;
    }

    switch (sel)
    {
    case CLK_SPI_SEL_200M:
        return 200 * MHz;
    case CLK_SPI_SEL_150M:
        return 150 * MHz;
    case CLK_SPI_SEL_24M:
        return OSC_HZ;
    default:
        return -RT_ENOENT;
    }
}

static rt_ubase_t rk3588_spi_set_clk(struct rk3588_clk_priv *priv,
                rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int src_clk;

    if (rate >= 198 * MHz)
        src_clk = CLK_SPI_SEL_200M;
    else if (rate >= 140 * MHz)
        src_clk = CLK_SPI_SEL_150M;
    else
        src_clk = CLK_SPI_SEL_24M;

    switch (clk_id)
    {
    case CLK_SPI0:
        rk_clrsetreg(&cru->clksel_con[59],
                 CLK_SPI0_SEL_MASK,
                 src_clk << CLK_SPI0_SEL_SHIFT);
        break;
    case CLK_SPI1:
        rk_clrsetreg(&cru->clksel_con[59],
                 CLK_SPI1_SEL_MASK,
                 src_clk << CLK_SPI1_SEL_SHIFT);
        break;
    case CLK_SPI2:
        rk_clrsetreg(&cru->clksel_con[59],
                 CLK_SPI2_SEL_MASK,
                 src_clk << CLK_SPI2_SEL_SHIFT);
        break;
    case CLK_SPI3:
        rk_clrsetreg(&cru->clksel_con[59],
                 CLK_SPI3_SEL_MASK,
                 src_clk << CLK_SPI3_SEL_SHIFT);
        break;
    case CLK_SPI4:
        rk_clrsetreg(&cru->clksel_con[59],
                 CLK_SPI4_SEL_MASK,
                 src_clk << CLK_SPI4_SEL_SHIFT);
        break;
    default:
        return -RT_ENOENT;
    }

    return rk3588_spi_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_pwm_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t sel, con;

    switch (clk_id)
    {
    case CLK_PWM1:
        con = HWREG32(&cru->clksel_con[59]);
        sel = (con & CLK_PWM1_SEL_MASK) >> CLK_PWM1_SEL_SHIFT;
        break;
    case CLK_PWM2:
        con = HWREG32(&cru->clksel_con[59]);
        sel = (con & CLK_PWM2_SEL_MASK) >> CLK_PWM2_SEL_SHIFT;
        break;
    case CLK_PWM3:
        con = HWREG32(&cru->clksel_con[60]);
        sel = (con & CLK_PWM3_SEL_MASK) >> CLK_PWM3_SEL_SHIFT;
        break;
    case CLK_PMU1PWM:
        con = HWREG32(&cru->pmuclksel_con[2]);
        sel = (con & CLK_PMU1PWM_SEL_MASK) >> CLK_PMU1PWM_SEL_SHIFT;
        break;
    default:
        return -RT_ENOENT;
    }

    switch (sel)
    {
    case CLK_PWM_SEL_100M:
        return 100 * MHz;
    case CLK_PWM_SEL_50M:
        return 50 * MHz;
    case CLK_PWM_SEL_24M:
        return OSC_HZ;
    default:
        return -RT_ENOENT;
    }
}

static rt_ubase_t rk3588_pwm_set_clk(struct rk3588_clk_priv *priv,
                rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int src_clk;

    if (rate >= 99 * MHz)
        src_clk = CLK_PWM_SEL_100M;
    else if (rate >= 50 * MHz)
        src_clk = CLK_PWM_SEL_50M;
    else
        src_clk = CLK_PWM_SEL_24M;

    switch (clk_id)
    {
    case CLK_PWM1:
        rk_clrsetreg(&cru->clksel_con[59],
                 CLK_PWM1_SEL_MASK,
                 src_clk << CLK_PWM1_SEL_SHIFT);
        break;
    case CLK_PWM2:
        rk_clrsetreg(&cru->clksel_con[59],
                 CLK_PWM2_SEL_MASK,
                 src_clk << CLK_PWM2_SEL_SHIFT);
        break;
    case CLK_PWM3:
        rk_clrsetreg(&cru->clksel_con[60],
                 CLK_PWM3_SEL_MASK,
                 src_clk << CLK_PWM3_SEL_SHIFT);
        break;
    case CLK_PMU1PWM:
        rk_clrsetreg(&cru->pmuclksel_con[2],
                 CLK_PMU1PWM_SEL_MASK,
                 src_clk << CLK_PMU1PWM_SEL_SHIFT);
        break;
    default:
        return -RT_ENOENT;
    }

    return rk3588_pwm_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_adc_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t div, sel, con, prate;

    switch (clk_id)
    {
    case CLK_SARADC:
        con = HWREG32(&cru->clksel_con[40]);
        div = (con & CLK_SARADC_DIV_MASK) >> CLK_SARADC_DIV_SHIFT;
        sel = (con & CLK_SARADC_SEL_MASK) >>
              CLK_SARADC_SEL_SHIFT;
        if (sel == CLK_SARADC_SEL_24M)
            prate = OSC_HZ;
        else
            prate = priv->gpll_hz;
        return DIV_TO_RATE(prate, div);
    case CLK_TSADC:
        con = HWREG32(&cru->clksel_con[41]);
        div = (con & CLK_TSADC_DIV_MASK) >>
              CLK_TSADC_DIV_SHIFT;
        sel = (con & CLK_TSADC_SEL_MASK) >>
              CLK_TSADC_SEL_SHIFT;
        if (sel == CLK_TSADC_SEL_24M)
            prate = OSC_HZ;
        else
            prate = 100 * MHz;
        return DIV_TO_RATE(prate, div);
    default:
        return -RT_ENOENT;
    }
}

static rt_ubase_t rk3588_adc_set_clk(struct rk3588_clk_priv *priv,
                rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int src_clk_div;

    switch (clk_id)
    {
    case CLK_SARADC:
        if (!(OSC_HZ % rate))
        {
            src_clk_div = RT_DIV_ROUND_UP(OSC_HZ, rate);
            RT_ASSERT(src_clk_div - 1 <= 255);
            rk_clrsetreg(&cru->clksel_con[40],
                     CLK_SARADC_SEL_MASK |
                     CLK_SARADC_DIV_MASK,
                     (CLK_SARADC_SEL_24M <<
                      CLK_SARADC_SEL_SHIFT) |
                     (src_clk_div - 1) <<
                     CLK_SARADC_DIV_SHIFT);
        } else {
            src_clk_div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
            RT_ASSERT(src_clk_div - 1 <= 255);
            rk_clrsetreg(&cru->clksel_con[40],
                     CLK_SARADC_SEL_MASK |
                     CLK_SARADC_DIV_MASK,
                     (CLK_SARADC_SEL_GPLL <<
                      CLK_SARADC_SEL_SHIFT) |
                     (src_clk_div - 1) <<
                     CLK_SARADC_DIV_SHIFT);
        }
        break;
    case CLK_TSADC:
        if (!(OSC_HZ % rate))
        {
            src_clk_div = RT_DIV_ROUND_UP(OSC_HZ, rate);
            RT_ASSERT(src_clk_div - 1 <= 255);
            rk_clrsetreg(&cru->clksel_con[41],
                     CLK_TSADC_SEL_MASK |
                     CLK_TSADC_DIV_MASK,
                     (CLK_TSADC_SEL_24M <<
                      CLK_TSADC_SEL_SHIFT) |
                     (src_clk_div - 1) <<
                     CLK_TSADC_DIV_SHIFT);
        } else {
            src_clk_div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
            RT_ASSERT(src_clk_div - 1 <= 7);
            rk_clrsetreg(&cru->clksel_con[41],
                     CLK_TSADC_SEL_MASK |
                     CLK_TSADC_DIV_MASK,
                     (CLK_TSADC_SEL_GPLL <<
                      CLK_TSADC_SEL_SHIFT) |
                     (src_clk_div - 1) <<
                     CLK_TSADC_DIV_SHIFT);
        }
        break;
    default:
        return -RT_ENOENT;
    }
    return rk3588_adc_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_mmc_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t sel, con, div, prate;

    switch (clk_id)
    {
    case CCLK_SRC_SDIO:
        con = HWREG32(&cru->clksel_con[172]);
        div = (con & CCLK_SDIO_SRC_DIV_MASK) >> CCLK_SDIO_SRC_DIV_SHIFT;
        sel = (con & CCLK_SDIO_SRC_SEL_MASK) >>
              CCLK_SDIO_SRC_SEL_SHIFT;
        if (sel == CCLK_SDIO_SRC_SEL_GPLL)
            prate = priv->gpll_hz;
        else if (sel == CCLK_SDIO_SRC_SEL_CPLL)
            prate = priv->cpll_hz;
        else
            prate = OSC_HZ;
        return DIV_TO_RATE(prate, div);
    case CCLK_EMMC:
        con = HWREG32(&cru->clksel_con[77]);
        div = (con & CCLK_EMMC_DIV_MASK) >> CCLK_EMMC_DIV_SHIFT;
        sel = (con & CCLK_EMMC_SEL_MASK) >>
              CCLK_EMMC_SEL_SHIFT;
        if (sel == CCLK_EMMC_SEL_GPLL)
            prate = priv->gpll_hz;
        else if (sel == CCLK_EMMC_SEL_CPLL)
            prate = priv->cpll_hz;
        else
            prate = OSC_HZ;
        return DIV_TO_RATE(prate, div);
    case BCLK_EMMC:
        con = HWREG32(&cru->clksel_con[78]);
        div = (con & BCLK_EMMC_DIV_MASK) >> BCLK_EMMC_DIV_SHIFT;
        sel = (con & BCLK_EMMC_SEL_MASK) >>
              BCLK_EMMC_SEL_SHIFT;
        if (sel == CCLK_EMMC_SEL_CPLL)
            prate = priv->cpll_hz;
        else
            prate = priv->gpll_hz;
        return DIV_TO_RATE(prate, div);
    case SCLK_SFC:
        con = HWREG32(&cru->clksel_con[78]);
        div = (con & SCLK_SFC_DIV_MASK) >> SCLK_SFC_DIV_SHIFT;
        sel = (con & SCLK_SFC_SEL_MASK) >>
              SCLK_SFC_SEL_SHIFT;
        if (sel == SCLK_SFC_SEL_GPLL)
            prate = priv->gpll_hz;
        else if (sel == SCLK_SFC_SEL_CPLL)
            prate = priv->cpll_hz;
        else
            prate = OSC_HZ;
        return DIV_TO_RATE(prate, div);
    case DCLK_DECOM:
        con = HWREG32(&cru->clksel_con[62]);
        div = (con & DCLK_DECOM_DIV_MASK) >> DCLK_DECOM_DIV_SHIFT;
        sel = (con & DCLK_DECOM_SEL_MASK) >>
              DCLK_DECOM_SEL_SHIFT;
        if (sel == DCLK_DECOM_SEL_SPLL)
            prate = 702 * MHz;
        else
            prate = priv->gpll_hz;
        return DIV_TO_RATE(prate, div);
    default:
        return -RT_ENOENT;
    }
}

static rt_ubase_t rk3588_mmc_set_clk(struct rk3588_clk_priv *priv,
                rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int src_clk, div;
    /*rt_min_t(rt_ubase_t, 48 * MHZ, rate);*/
    switch (clk_id)
    {
    case CCLK_SRC_SDIO:
    case CCLK_EMMC:
    case SCLK_SFC:
        if (!(OSC_HZ % rate))
        {
            src_clk = SCLK_SFC_SEL_24M;
            div = RT_DIV_ROUND_UP(OSC_HZ, rate);
        } else if (!(priv->cpll_hz % rate))
        {
            src_clk = SCLK_SFC_SEL_CPLL;
            div = RT_DIV_ROUND_UP(priv->cpll_hz, rate);
        } else {
            src_clk = SCLK_SFC_SEL_GPLL;
            div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
        }
        break;
    case BCLK_EMMC:
        if (!(priv->cpll_hz % rate))
        {
            src_clk = CCLK_EMMC_SEL_CPLL;
            div = RT_DIV_ROUND_UP(priv->cpll_hz, rate);
        } else {
            src_clk = CCLK_EMMC_SEL_GPLL;
            div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
        }
        break;
    case DCLK_DECOM:
        if (!(702 * MHz % rate))
        {
            src_clk = DCLK_DECOM_SEL_SPLL;
            div = RT_DIV_ROUND_UP(702 * MHz, rate);
        } else {
            src_clk = DCLK_DECOM_SEL_GPLL;
            div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
        }
        break;
    default:
        return -RT_ENOENT;
    }

    switch (clk_id)
    {
    case CCLK_SRC_SDIO:
        rk_clrsetreg(&cru->clksel_con[172],
                 CCLK_SDIO_SRC_SEL_MASK |
                 CCLK_SDIO_SRC_DIV_MASK,
                 (src_clk << CCLK_SDIO_SRC_SEL_SHIFT) |
                 (div - 1) << CCLK_SDIO_SRC_DIV_SHIFT);
        break;
    case CCLK_EMMC:
        rk_clrsetreg(&cru->clksel_con[77],
                 CCLK_EMMC_SEL_MASK |
                 CCLK_EMMC_DIV_MASK,
                 (src_clk << CCLK_EMMC_SEL_SHIFT) |
                 (div - 1) << CCLK_EMMC_DIV_SHIFT);
        break;
    case BCLK_EMMC:
        rk_clrsetreg(&cru->clksel_con[78],
                 BCLK_EMMC_DIV_MASK |
                 BCLK_EMMC_SEL_MASK,
                 (src_clk << BCLK_EMMC_SEL_SHIFT) |
                 (div - 1) << BCLK_EMMC_DIV_SHIFT);
        break;
    case SCLK_SFC:
        rk_clrsetreg(&cru->clksel_con[78],
                 SCLK_SFC_DIV_MASK |
                 SCLK_SFC_SEL_MASK,
                 (src_clk << SCLK_SFC_SEL_SHIFT) |
                 (div - 1) << SCLK_SFC_DIV_SHIFT);
        break;
    case DCLK_DECOM:
        rk_clrsetreg(&cru->clksel_con[62],
                 DCLK_DECOM_DIV_MASK |
                 DCLK_DECOM_SEL_MASK,
                 (src_clk << DCLK_DECOM_SEL_SHIFT) |
                 (div - 1) << DCLK_DECOM_DIV_SHIFT);
        break;
    default:
        return -RT_ENOENT;
    }

    return rk3588_mmc_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_aux16m_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t div, con, parent;

    parent = priv->gpll_hz;
    con = HWREG32(&cru->clksel_con[117]);

    switch (clk_id)
    {
    case CLK_AUX16M_0:
        div = (con & CLK_AUX16MHZ_0_DIV_MASK) >> CLK_AUX16MHZ_0_DIV_SHIFT;
        return DIV_TO_RATE(parent, div);
    case CLK_AUX16M_1:
        div = (con & CLK_AUX16MHZ_1_DIV_MASK) >> CLK_AUX16MHZ_1_DIV_SHIFT;
        return DIV_TO_RATE(parent, div);
    default:
        return -RT_ENOENT;
    }
}

static rt_ubase_t rk3588_aux16m_set_clk(struct rk3588_clk_priv *priv,
                   rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t div;

    if (!priv->gpll_hz)
    {
        LOG_D("%s gpll=%lu\n", __func__, priv->gpll_hz);
        return -RT_ENOENT;
    }

    div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);

    switch (clk_id)
    {
    case CLK_AUX16M_0:
        rk_clrsetreg(&cru->clksel_con[117], CLK_AUX16MHZ_0_DIV_MASK,
                 (div - 1) << CLK_AUX16MHZ_0_DIV_SHIFT);
        break;
    case CLK_AUX16M_1:
        rk_clrsetreg(&cru->clksel_con[117], CLK_AUX16MHZ_1_DIV_MASK,
                 (div - 1) << CLK_AUX16MHZ_1_DIV_SHIFT);
        break;
    default:
        return -RT_ENOENT;
    }

    return rk3588_aux16m_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_aclk_vop_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t div, sel, con, parent;

    switch (clk_id)
    {
    case ACLK_VOP_ROOT:
    case ACLK_VOP:
        con = HWREG32(&cru->clksel_con[110]);
        div = (con & ACLK_VOP_ROOT_DIV_MASK) >> ACLK_VOP_ROOT_DIV_SHIFT;
        sel = (con & ACLK_VOP_ROOT_SEL_MASK) >> ACLK_VOP_ROOT_SEL_SHIFT;
        if (sel == ACLK_VOP_ROOT_SEL_GPLL)
            parent = priv->gpll_hz;
        else if (sel == ACLK_VOP_ROOT_SEL_CPLL)
            parent = priv->cpll_hz;
        else if (sel == ACLK_VOP_ROOT_SEL_AUPLL)
            parent = priv->aupll_hz;
        else if (sel == ACLK_VOP_ROOT_SEL_NPLL)
            parent = priv->npll_hz;
        else
            parent = 702 * MHz;
        return DIV_TO_RATE(parent, div);
    case ACLK_VOP_LOW_ROOT:
        con = HWREG32(&cru->clksel_con[110]);
        sel = (con & ACLK_VOP_LOW_ROOT_SEL_MASK) >>
              ACLK_VOP_LOW_ROOT_SEL_SHIFT;
        if (sel == ACLK_VOP_LOW_ROOT_SEL_400M)
            return 396 * MHz;
        else if (sel == ACLK_VOP_LOW_ROOT_SEL_200M)
            return 200 * MHz;
        else if (sel == ACLK_VOP_LOW_ROOT_SEL_100M)
            return 100 * MHz;
        else
            return OSC_HZ;
    case HCLK_VOP_ROOT:
        con = HWREG32(&cru->clksel_con[110]);
        sel = (con & HCLK_VOP_ROOT_SEL_MASK) >> HCLK_VOP_ROOT_SEL_SHIFT;
        if (sel == HCLK_VOP_ROOT_SEL_200M)
            return 200 * MHz;
        else if (sel == HCLK_VOP_ROOT_SEL_100M)
            return 100 * MHz;
        else if (sel == HCLK_VOP_ROOT_SEL_50M)
            return 50 * MHz;
        else
            return OSC_HZ;
    default:
        return -RT_ENOENT;
    }
}

static rt_ubase_t rk3588_aclk_vop_set_clk(struct rk3588_clk_priv *priv,
                     rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int src_clk, div;

    switch (clk_id)
    {
    case ACLK_VOP_ROOT:
    case ACLK_VOP:
        if (rate >= 850 * MHz)
        {
            src_clk = ACLK_VOP_ROOT_SEL_NPLL;
            div = 1;
        } else if (rate >= 750 * MHz)
        {
            src_clk = ACLK_VOP_ROOT_SEL_CPLL;
            div = 2;
        } else if (rate >= 700 * MHz)
        {
            src_clk = ACLK_VOP_ROOT_SEL_SPLL;
            div = 1;
        } else if (!(priv->cpll_hz % rate))
        {
            src_clk = ACLK_VOP_ROOT_SEL_CPLL;
            div = RT_DIV_ROUND_UP(priv->cpll_hz, rate);
        } else {
            src_clk = ACLK_VOP_ROOT_SEL_GPLL;
            div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
        }
        rk_clrsetreg(&cru->clksel_con[110],
                 ACLK_VOP_ROOT_DIV_MASK |
                 ACLK_VOP_ROOT_SEL_MASK,
                 (src_clk << ACLK_VOP_ROOT_SEL_SHIFT) |
                 (div - 1) << ACLK_VOP_ROOT_DIV_SHIFT);
        break;
    case ACLK_VOP_LOW_ROOT:
        if (rate == 400 * MHz || rate == 396 * MHz)
            src_clk = ACLK_VOP_LOW_ROOT_SEL_400M;
        else if (rate == 200 * MHz)
            src_clk = ACLK_VOP_LOW_ROOT_SEL_200M;
        else if (rate == 100 * MHz)
            src_clk = ACLK_VOP_LOW_ROOT_SEL_100M;
        else
            src_clk = ACLK_VOP_LOW_ROOT_SEL_24M;
        rk_clrsetreg(&cru->clksel_con[110],
                 ACLK_VOP_LOW_ROOT_SEL_MASK,
                 src_clk << ACLK_VOP_LOW_ROOT_SEL_SHIFT);
        break;
    case HCLK_VOP_ROOT:
        if (rate == 200 * MHz)
            src_clk = HCLK_VOP_ROOT_SEL_200M;
        else if (rate == 100 * MHz)
            src_clk = HCLK_VOP_ROOT_SEL_100M;
        else if (rate == 50 * MHz)
            src_clk = HCLK_VOP_ROOT_SEL_50M;
        else
            src_clk = HCLK_VOP_ROOT_SEL_24M;
        rk_clrsetreg(&cru->clksel_con[110],
                 HCLK_VOP_ROOT_SEL_MASK,
                 src_clk << HCLK_VOP_ROOT_SEL_SHIFT);
        break;
    default:
        return -RT_ENOENT;
    }

    return rk3588_aclk_vop_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_dclk_vop_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t div, sel, con, parent;

    switch (clk_id)
    {
    case DCLK_VOP0:
    case DCLK_VOP0_SRC:
        con = HWREG32(&cru->clksel_con[111]);
        div = (con & DCLK0_VOP_SRC_DIV_MASK) >> DCLK0_VOP_SRC_DIV_SHIFT;
        sel = (con & DCLK0_VOP_SRC_SEL_MASK) >> DCLK0_VOP_SRC_SEL_SHIFT;
        break;
    case DCLK_VOP1:
    case DCLK_VOP1_SRC:
        con = HWREG32(&cru->clksel_con[111]);
        div = (con & DCLK1_VOP_SRC_DIV_MASK) >> DCLK1_VOP_SRC_DIV_SHIFT;
        sel = (con & DCLK1_VOP_SRC_SEL_MASK) >> DCLK1_VOP_SRC_SEL_SHIFT;
        break;
    case DCLK_VOP2:
    case DCLK_VOP2_SRC:
        con = HWREG32(&cru->clksel_con[112]);
        div = (con & DCLK2_VOP_SRC_DIV_MASK) >> DCLK2_VOP_SRC_DIV_SHIFT;
        sel = (con & DCLK2_VOP_SRC_SEL_MASK) >> DCLK2_VOP_SRC_SEL_SHIFT;
        break;
    case DCLK_VOP3:
        con = HWREG32(&cru->clksel_con[113]);
        div = (con & DCLK3_VOP_SRC_DIV_MASK) >> DCLK3_VOP_SRC_DIV_SHIFT;
        sel = (con & DCLK3_VOP_SRC_SEL_MASK) >> DCLK3_VOP_SRC_SEL_SHIFT;
        break;
    default:
        return -RT_ENOENT;
    }

    if (sel == DCLK_VOP_SRC_SEL_AUPLL)
        parent = priv->aupll_hz;
    else if (sel == DCLK_VOP_SRC_SEL_V0PLL)
        parent = rk_pll_get_rate(&rk3588_pll_clks[V0PLL],
                           priv->cru, V0PLL);
    else if (sel == DCLK_VOP_SRC_SEL_GPLL)
        parent = priv->gpll_hz;
    else
        parent = priv->cpll_hz;

    return DIV_TO_RATE(parent, div);
}

#define RK3588_VOP_PLL_LIMIT_FREQ 600000000

static rt_ubase_t rk3588_dclk_vop_set_clk(struct rk3588_clk_priv *priv,
                     rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    rt_ubase_t pll_rate, now, best_rate = 0;
    rt_uint32_t i, conid, con, sel, div, best_div = 0, best_sel = 0;
    rt_uint32_t mask, div_shift, sel_shift;

    switch (clk_id)
    {
    case DCLK_VOP0:
    case DCLK_VOP0_SRC:
        conid = 111;
        con = HWREG32(&cru->clksel_con[111]);
        sel = (con & DCLK0_VOP_SRC_SEL_MASK) >> DCLK0_VOP_SRC_SEL_SHIFT;
        mask = DCLK0_VOP_SRC_SEL_MASK | DCLK0_VOP_SRC_DIV_MASK;
        div_shift = DCLK0_VOP_SRC_DIV_SHIFT;
        sel_shift = DCLK0_VOP_SRC_SEL_SHIFT;
        break;
    case DCLK_VOP1:
    case DCLK_VOP1_SRC:
        conid = 111;
        con = HWREG32(&cru->clksel_con[111]);
        sel = (con & DCLK1_VOP_SRC_SEL_MASK) >> DCLK1_VOP_SRC_SEL_SHIFT;
        mask = DCLK1_VOP_SRC_SEL_MASK | DCLK1_VOP_SRC_DIV_MASK;
        div_shift = DCLK1_VOP_SRC_DIV_SHIFT;
        sel_shift = DCLK1_VOP_SRC_SEL_SHIFT;
        break;
    case DCLK_VOP2:
    case DCLK_VOP2_SRC:
        conid = 112;
        con = HWREG32(&cru->clksel_con[112]);
        sel = (con & DCLK2_VOP_SRC_SEL_MASK) >> DCLK2_VOP_SRC_SEL_SHIFT;
        mask = DCLK2_VOP_SRC_SEL_MASK | DCLK2_VOP_SRC_DIV_MASK;
        div_shift = DCLK2_VOP_SRC_DIV_SHIFT;
        sel_shift = DCLK2_VOP_SRC_SEL_SHIFT;
        break;
    case DCLK_VOP3:
        conid = 113;
        con = HWREG32(&cru->clksel_con[113]);
        sel = (con & DCLK3_VOP_SRC_SEL_MASK) >> DCLK3_VOP_SRC_SEL_SHIFT;
        mask = DCLK3_VOP_SRC_SEL_MASK | DCLK3_VOP_SRC_DIV_MASK;
        div_shift = DCLK3_VOP_SRC_DIV_SHIFT;
        sel_shift = DCLK3_VOP_SRC_SEL_SHIFT;
        break;
    default:
        return -RT_ENOENT;
    }

    if (sel == DCLK_VOP_SRC_SEL_V0PLL)
    {
        pll_rate = rk_pll_get_rate(&rk3588_pll_clks[V0PLL],
                         priv->cru, V0PLL);
        if (pll_rate >= RK3588_VOP_PLL_LIMIT_FREQ && pll_rate % rate == 0)
        {
            div = RT_DIV_ROUND_UP(pll_rate, rate);
            rk_clrsetreg(&cru->clksel_con[conid],
                     mask,
                     DCLK_VOP_SRC_SEL_V0PLL << sel_shift |
                     ((div - 1) << div_shift));
        } else {
            div = RT_DIV_ROUND_UP(RK3588_VOP_PLL_LIMIT_FREQ, rate);
            rk_clrsetreg(&cru->clksel_con[conid],
                     mask,
                     DCLK_VOP_SRC_SEL_V0PLL << sel_shift |
                     ((div - 1) << div_shift));
            rk_pll_set_rate(&rk3588_pll_clks[V0PLL],
                          priv->cru, V0PLL, div * rate);
        }
    } else {
        for (i = 0; i <= DCLK_VOP_SRC_SEL_AUPLL; i++)
        {
            switch (i)
            {
            case DCLK_VOP_SRC_SEL_GPLL:
                pll_rate = priv->gpll_hz;
                break;
            case DCLK_VOP_SRC_SEL_CPLL:
                pll_rate = priv->cpll_hz;
                break;
            case DCLK_VOP_SRC_SEL_AUPLL:
                pll_rate = priv->aupll_hz;
                break;
            case DCLK_VOP_SRC_SEL_V0PLL:
                pll_rate = 0;
                break;
            default:
                LOG_D("do not support this vop pll sel\n");
                return -RT_EINVAL;
            }

            div = RT_DIV_ROUND_UP(pll_rate, rate);
            if (div > 255)
                continue;
            now = pll_rate / div;
            if (abs(rate - now) < abs(rate - best_rate))
            {
                best_rate = now;
                best_div = div;
                best_sel = i;
            }
            LOG_D("p_rate=%lu, best_rate=%lu, div=%u, sel=%u\n",
                  pll_rate, best_rate, best_div, best_sel);
        }

        if (best_rate)
        {
            rk_clrsetreg(&cru->clksel_con[conid],
                     mask,
                     best_sel << sel_shift |
                     (best_div - 1) << div_shift);
        } else {
            LOG_D("do not support this vop freq %lu\n", rate);
            return -RT_EINVAL;
        }
    }
    return rk3588_dclk_vop_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_gmac_get_clk(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t con, div;

    switch (clk_id)
    {
    case CLK_GMAC0_PTP_REF:
        con = HWREG32(&cru->clksel_con[81]);
        div = (con & CLK_GMAC0_PTP_DIV_MASK) >> CLK_GMAC0_PTP_DIV_SHIFT;
        return DIV_TO_RATE(priv->cpll_hz, div);
    case CLK_GMAC1_PTP_REF:
        con = HWREG32(&cru->clksel_con[81]);
        div = (con & CLK_GMAC1_PTP_DIV_MASK) >> CLK_GMAC1_PTP_DIV_SHIFT;
        return DIV_TO_RATE(priv->cpll_hz, div);
    case CLK_GMAC_125M:
        con = HWREG32(&cru->clksel_con[83]);
        div = (con & CLK_GMAC_125M_DIV_MASK) >> CLK_GMAC_125M_DIV_SHIFT;
        return DIV_TO_RATE(priv->cpll_hz, div);
    case CLK_GMAC_50M:
        con = HWREG32(&cru->clksel_con[84]);
        div = (con & CLK_GMAC_50M_DIV_MASK) >> CLK_GMAC_50M_DIV_SHIFT;
        return DIV_TO_RATE(priv->cpll_hz, div);
    default:
        return -RT_ENOENT;
    }
}

static rt_ubase_t rk3588_gmac_set_clk(struct rk3588_clk_priv *priv,
                 rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    int div;

    div = RT_DIV_ROUND_UP(priv->cpll_hz, rate);

    switch (clk_id)
    {
    case CLK_GMAC0_PTP_REF:
        rk_clrsetreg(&cru->clksel_con[81],
                 CLK_GMAC0_PTP_DIV_MASK | CLK_GMAC0_PTP_SEL_MASK,
                 CLK_GMAC0_PTP_SEL_CPLL << CLK_GMAC0_PTP_SEL_SHIFT |
                 (div - 1) << CLK_GMAC0_PTP_DIV_SHIFT);
        break;
    case CLK_GMAC1_PTP_REF:
        rk_clrsetreg(&cru->clksel_con[81],
                 CLK_GMAC1_PTP_DIV_MASK | CLK_GMAC1_PTP_SEL_MASK,
                 CLK_GMAC1_PTP_SEL_CPLL << CLK_GMAC1_PTP_SEL_SHIFT |
                 (div - 1) << CLK_GMAC1_PTP_DIV_SHIFT);
        break;

    case CLK_GMAC_125M:
        rk_clrsetreg(&cru->clksel_con[83],
                 CLK_GMAC_125M_DIV_MASK | CLK_GMAC_125M_SEL_MASK,
                 CLK_GMAC_125M_SEL_CPLL << CLK_GMAC_125M_SEL_SHIFT |
                 (div - 1) << CLK_GMAC_125M_DIV_SHIFT);
        break;
    case CLK_GMAC_50M:
        rk_clrsetreg(&cru->clksel_con[84],
                 CLK_GMAC_50M_DIV_MASK | CLK_GMAC_50M_SEL_MASK,
                 CLK_GMAC_50M_SEL_CPLL << CLK_GMAC_50M_SEL_SHIFT |
                 (div - 1) << CLK_GMAC_50M_DIV_SHIFT);
        break;
    default:
        return -RT_ENOENT;
    }

    return rk3588_gmac_get_clk(priv, clk_id);
}

static rt_ubase_t rk3588_uart_get_rate(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t reg, con, fracdiv, div, src, p_src, p_rate;
    unsigned long m, n;

    switch (clk_id)
    {
    case SCLK_UART1:
        reg = 41;
        break;
    case SCLK_UART2:
        reg = 43;
        break;
    case SCLK_UART3:
        reg = 45;
        break;
    case SCLK_UART4:
        reg = 47;
        break;
    case SCLK_UART5:
        reg = 49;
        break;
    case SCLK_UART6:
        reg = 51;
        break;
    case SCLK_UART7:
        reg = 53;
        break;
    case SCLK_UART8:
        reg = 55;
        break;
    case SCLK_UART9:
        reg = 57;
        break;
    default:
        return -RT_ENOENT;
    }
    con = HWREG32(&cru->clksel_con[reg + 2]);
    src = (con & CLK_UART_SEL_MASK) >> CLK_UART_SEL_SHIFT;
    con = HWREG32(&cru->clksel_con[reg]);
    div = (con & CLK_UART_SRC_DIV_MASK) >> CLK_UART_SRC_DIV_SHIFT;
    p_src = (con & CLK_UART_SRC_SEL_MASK) >> CLK_UART_SRC_SEL_SHIFT;
    if (p_src == CLK_UART_SRC_SEL_GPLL)
        p_rate = priv->gpll_hz;
    else
        p_rate = priv->cpll_hz;

    if (src == CLK_UART_SEL_SRC)
    {
        return DIV_TO_RATE(p_rate, div);
    } else if (src == CLK_UART_SEL_FRAC)
    {
        fracdiv = HWREG32(&cru->clksel_con[reg + 1]);
        n = fracdiv & CLK_UART_FRAC_NUMERATOR_MASK;
        n >>= CLK_UART_FRAC_NUMERATOR_SHIFT;
        m = fracdiv & CLK_UART_FRAC_DENOMINATOR_MASK;
        m >>= CLK_UART_FRAC_DENOMINATOR_SHIFT;
        return DIV_TO_RATE(p_rate, div) * n / m;
    } else {
        return OSC_HZ;
    }
}

static rt_ubase_t rk3588_uart_set_rate(struct rk3588_clk_priv *priv,
                  rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t reg, clk_src, uart_src, div;
    unsigned long m = 0, n = 0, val;

    if (priv->gpll_hz % rate == 0)
    {
        clk_src = CLK_UART_SRC_SEL_GPLL;
        uart_src = CLK_UART_SEL_SRC;
        div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
    } else if (priv->cpll_hz % rate == 0)
    {
        clk_src = CLK_UART_SRC_SEL_CPLL;
        uart_src = CLK_UART_SEL_SRC;
        div = RT_DIV_ROUND_UP(priv->gpll_hz, rate);
    } else if (rate == OSC_HZ)
    {
        clk_src = CLK_UART_SRC_SEL_GPLL;
        uart_src = CLK_UART_SEL_XIN24M;
        div = 2;
    } else {
        clk_src = CLK_UART_SRC_SEL_GPLL;
        uart_src = CLK_UART_SEL_FRAC;
        div = 2;
        rational_best_approximation(rate, priv->gpll_hz / div,
                        RT_GENMASK(16 - 1, 0),
                        RT_GENMASK(16 - 1, 0),
                        &m, &n);
    }

    switch (clk_id)
    {
    case SCLK_UART1:
        reg = 41;
        break;
    case SCLK_UART2:
        reg = 43;
        break;
    case SCLK_UART3:
        reg = 45;
        break;
    case SCLK_UART4:
        reg = 47;
        break;
    case SCLK_UART5:
        reg = 49;
        break;
    case SCLK_UART6:
        reg = 51;
        break;
    case SCLK_UART7:
        reg = 53;
        break;
    case SCLK_UART8:
        reg = 55;
        break;
    case SCLK_UART9:
        reg = 57;
        break;
    default:
        return -RT_ENOENT;
    }
    rk_clrsetreg(&cru->clksel_con[reg],
             CLK_UART_SRC_SEL_MASK |
             CLK_UART_SRC_DIV_MASK,
             (clk_src << CLK_UART_SRC_SEL_SHIFT) |
             ((div - 1) << CLK_UART_SRC_DIV_SHIFT));
    rk_clrsetreg(&cru->clksel_con[reg + 2],
             CLK_UART_SEL_MASK,
             (uart_src << CLK_UART_SEL_SHIFT));
    if (m && n)
    {
        val = m << CLK_UART_FRAC_NUMERATOR_SHIFT | n;
        HWREG32(&cru->clksel_con[reg + 1]) = val;
    }

    return rk3588_uart_get_rate(priv, clk_id);
}

static rt_ubase_t rk3588_pciephy_get_rate(struct rk3588_clk_priv *priv, rt_ubase_t clk_id)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t con, div, src;

    switch (clk_id)
    {
    case CLK_REF_PIPE_PHY0:
        con = HWREG32(&cru->clksel_con[177]);
        src = (con & CLK_PCIE_PHY0_REF_SEL_MASK) >> CLK_PCIE_PHY0_REF_SEL_SHIFT;
        con = HWREG32(&cru->clksel_con[176]);
        div = (con & CLK_PCIE_PHY0_PLL_DIV_MASK) >> CLK_PCIE_PHY0_PLL_DIV_SHIFT;
        break;
    case CLK_REF_PIPE_PHY1:
        con = HWREG32(&cru->clksel_con[177]);
        src = (con & CLK_PCIE_PHY1_REF_SEL_MASK) >> CLK_PCIE_PHY1_REF_SEL_SHIFT;
        con = HWREG32(&cru->clksel_con[176]);
        div = (con & CLK_PCIE_PHY1_PLL_DIV_MASK) >> CLK_PCIE_PHY1_PLL_DIV_SHIFT;
        break;
    case CLK_REF_PIPE_PHY2:
        con = HWREG32(&cru->clksel_con[177]);
        src = (con & CLK_PCIE_PHY2_REF_SEL_MASK) >> CLK_PCIE_PHY2_REF_SEL_SHIFT;
        div = (con & CLK_PCIE_PHY2_PLL_DIV_MASK) >> CLK_PCIE_PHY2_PLL_DIV_SHIFT;
        break;
    default:
        return -RT_ENOENT;
    }

    if (src == CLK_PCIE_PHY_REF_SEL_PPLL)
    {
        return DIV_TO_RATE(priv->ppll_hz, div);
    } else {
        return OSC_HZ;
    }
}

static rt_ubase_t rk3588_pciephy_set_rate(struct rk3588_clk_priv *priv,
                  rt_ubase_t clk_id, rt_ubase_t rate)
{
    struct rk3588_cru *cru = priv->cru;
    rt_uint32_t clk_src, div;

    if (rate == OSC_HZ)
    {
        clk_src = CLK_PCIE_PHY_REF_SEL_24M;
        div = 1;
    } else {
        clk_src = CLK_PCIE_PHY_REF_SEL_PPLL;
        div = RT_DIV_ROUND_UP(priv->ppll_hz, rate);
    }

    switch (clk_id)
    {
    case CLK_REF_PIPE_PHY0:
        rk_clrsetreg(&cru->clksel_con[177],
             CLK_PCIE_PHY0_REF_SEL_MASK,
             (clk_src << CLK_PCIE_PHY0_REF_SEL_SHIFT));
        rk_clrsetreg(&cru->clksel_con[176],
             CLK_PCIE_PHY0_PLL_DIV_MASK,
             ((div - 1) << CLK_PCIE_PHY0_PLL_DIV_SHIFT));
        break;
    case CLK_REF_PIPE_PHY1:
        rk_clrsetreg(&cru->clksel_con[177],
             CLK_PCIE_PHY1_REF_SEL_MASK,
             (clk_src << CLK_PCIE_PHY1_REF_SEL_SHIFT));
        rk_clrsetreg(&cru->clksel_con[176],
             CLK_PCIE_PHY1_PLL_DIV_MASK,
             ((div - 1) << CLK_PCIE_PHY1_PLL_DIV_SHIFT));
        break;
    case CLK_REF_PIPE_PHY2:
        rk_clrsetreg(&cru->clksel_con[177],
             CLK_PCIE_PHY2_REF_SEL_MASK |
             CLK_PCIE_PHY2_PLL_DIV_MASK,
             (clk_src << CLK_PCIE_PHY2_REF_SEL_SHIFT) |
             ((div - 1) << CLK_PCIE_PHY2_PLL_DIV_SHIFT));
        break;
    default:
        return -RT_ENOENT;
    }

    return rk3588_pciephy_get_rate(priv, clk_id);
}

static rt_ubase_t rk_clk_get_rate(struct rk3588_clk_platform_data *pdata,
        struct rk3588_clk *rk_clk)
{
    struct rk3588_clk_priv *priv = &rk_clk->clk_info;
    rt_ubase_t rate = 0;

    if (!priv->gpll_hz)
    {
        return -RT_ERROR;
    }
    if (!priv->ppll_hz)
    {
        priv->ppll_hz = rk_pll_get_rate(&rk3588_pll_clks[PPLL],
                              priv->cru, PPLL);
    }
    switch (pdata->id)
    {
    case PLL_B0PLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[B0PLL], &priv->cru, B0PLL);
        break;
    case PLL_B1PLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[B1PLL], &priv->cru, B1PLL);
        break;
    case PLL_LPLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[LPLL], &priv->cru, LPLL);
        break;
    case PLL_V0PLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[V0PLL], &priv->cru, V0PLL);
        break;
    case PLL_AUPLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[AUPLL], &priv->cru, AUPLL);
        break;
    case PLL_CPLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[CPLL], &priv->cru, CPLL);
        break;
    case PLL_GPLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[GPLL], &priv->cru, GPLL);
        break;
    case PLL_NPLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[NPLL], &priv->cru, NPLL);
        break;
    case PLL_PPLL:
        rate = rk_pll_get_rate(&rk3588_pll_clks[PPLL], &priv->cru, PPLL);
        break;
    case ACLK_CENTER_ROOT:
    case PCLK_CENTER_ROOT:
    case HCLK_CENTER_ROOT:
    case ACLK_CENTER_LOW_ROOT:
        rate = rk3588_center_get_clk(priv, pdata->id);
        break;
    case ACLK_TOP_ROOT:
    case PCLK_TOP_ROOT:
    case ACLK_LOW_TOP_ROOT:
        rate = rk3588_top_get_clk(priv, pdata->id);
        break;
    case CLK_I2C0:
    case CLK_I2C1:
    case CLK_I2C2:
    case CLK_I2C3:
    case CLK_I2C4:
    case CLK_I2C5:
    case CLK_I2C6:
    case CLK_I2C7:
    case CLK_I2C8:
        rate = rk3588_i2c_get_clk(priv, pdata->id);
        break;
    case CLK_SPI0:
    case CLK_SPI1:
    case CLK_SPI2:
    case CLK_SPI3:
    case CLK_SPI4:
        rate = rk3588_spi_get_clk(priv, pdata->id);
        break;
    case CLK_PWM1:
    case CLK_PWM2:
    case CLK_PWM3:
    case CLK_PMU1PWM:
        rate = rk3588_pwm_get_clk(priv, pdata->id);
        break;
    case CLK_SARADC:
    case CLK_TSADC:
        rate = rk3588_adc_get_clk(priv, pdata->id);
        break;
    case CCLK_SRC_SDIO:
    case CCLK_EMMC:
    case BCLK_EMMC:
    case SCLK_SFC:
    case DCLK_DECOM:
        rate = rk3588_mmc_get_clk(priv, pdata->id);
        break;
    case TCLK_WDT0:
        rate = OSC_HZ;
        break;
#ifndef CONFIG_SPL_BUILD
    case CLK_AUX16M_0:
    case CLK_AUX16M_1:
        rk3588_aux16m_get_clk(priv, pdata->id);
        break;
    case ACLK_VOP_ROOT:
    case ACLK_VOP:
    case ACLK_VOP_LOW_ROOT:
    case HCLK_VOP_ROOT:
        rate = rk3588_aclk_vop_get_clk(priv, pdata->id);
        break;
    case DCLK_VOP0:
    case DCLK_VOP0_SRC:
    case DCLK_VOP1:
    case DCLK_VOP1_SRC:
    case DCLK_VOP2:
    case DCLK_VOP2_SRC:
    case DCLK_VOP3:
        rate = rk3588_dclk_vop_get_clk(priv, pdata->id);
        break;
    case CLK_GMAC0_PTP_REF:
    case CLK_GMAC1_PTP_REF:
    case CLK_GMAC_125M:
    case CLK_GMAC_50M:
        rate = rk3588_gmac_get_clk(priv, pdata->id);
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
        rate = rk3588_uart_get_rate(priv, pdata->id);
        break;
    case CLK_REF_PIPE_PHY0:
    case CLK_REF_PIPE_PHY1:
    case CLK_REF_PIPE_PHY2:
        rate = rk3588_pciephy_get_rate(priv, pdata->id);
        break;
#endif
    default:
        return -RT_ENOENT;
    }

    return rate;
};

static rt_err_t mmc_set_phase(struct rk3588_clk_platform_data *pdata,
        struct rk3588_clk *rk_clk, rt_uint32_t degrees)
{
    void *reg;
    rt_ubase_t rate;
    struct rk3588_clk_priv *priv = &rk_clk->clk_info;
    struct rk3588_cru *cru = priv->cru;

    rate = rk_clk_get_rate(pdata, rk_clk);

    switch (pdata->id)
    {
    case SCLK_SDIO_DRV:
        reg = &cru->sdio_con[0];
        break;

    case SCLK_SDIO_SAMPLE:
        reg = &cru->sdio_con[1];
        break;

    case SCLK_SDMMC_DRV:
        reg = &cru->sdmmc_con[0];
        break;

    case SCLK_SDMMC_SAMPLE:
        reg = &cru->sdmmc_con[1];
        break;
    }

    return rk_clk_mmc_set_phase(rate, reg, 1, degrees);
}

static rt_base_t mmc_get_phase(struct rk3588_clk_platform_data *pdata,
        struct rk3588_clk *rk_clk)
{
    void *reg;
    rt_ubase_t rate;
    struct rk3588_clk_priv *priv = &rk_clk->clk_info;
    struct rk3588_cru *cru = priv->cru;

    rate = rk_clk_get_rate(pdata, rk_clk);

    switch (pdata->id)
    {
    case SCLK_SDIO_DRV:
        reg = &cru->sdio_con[0];
        break;

    case SCLK_SDIO_SAMPLE:
        reg = &cru->sdio_con[1];
        break;

    case SCLK_SDMMC_DRV:
        reg = &cru->sdmmc_con[0];
        break;

    case SCLK_SDMMC_SAMPLE:
        reg = &cru->sdmmc_con[1];
        break;
    }

    return rk_clk_mmc_get_phase(rate, reg, 1);
}

static rt_err_t rk3588_clk_init(struct rt_clk *clk, void *fw_data)
{
    struct rk3588_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rt_ofw_cell_args *args = fw_data;
    struct rk3588_clk_platform_data *pdata;
    rt_uint32_t clk_id = args->args[0];
    rt_ubase_t reg_base;

    pdata = &rk_clk->pdata[clk_id];

    reg_base = (rt_ubase_t)rk_clk->clk_info.cru;

    switch (clk_id)
    {
    case PLL_B0PLL:
        reg_base += rk3588_pll_clks[B0PLL].con_offset;
        break;
    case PLL_B1PLL:
        reg_base += rk3588_pll_clks[B1PLL].con_offset;
        break;
    case PLL_LPLL:
        reg_base += rk3588_pll_clks[LPLL].con_offset;
        break;
    case PLL_V0PLL:
        reg_base += rk3588_pll_clks[V0PLL].con_offset;
        break;
    case PLL_AUPLL:
        reg_base += rk3588_pll_clks[AUPLL].con_offset;
        break;
    case PLL_CPLL:
        reg_base += rk3588_pll_clks[CPLL].con_offset;
        break;
    case PLL_GPLL:
        reg_base += rk3588_pll_clks[GPLL].con_offset;
        break;
    case PLL_NPLL:
        reg_base += rk3588_pll_clks[NPLL].con_offset;
        break;
    case PLL_PPLL:
        reg_base += rk3588_pll_clks[PPLL].con_offset;
        break;
    default:
        reg_base = RT_NULL;
        break;
    }

    pdata->id = clk_id;
    pdata->base = (void *)reg_base;

    clk->rate = rk_clk_get_rate(pdata, rk_clk);
    clk->priv = pdata;

    rk_clk_set_default_rates(clk, clk->clk_np->ops->set_rate, clk_id);

    return RT_EOK;
}

static rt_err_t rk_clk_wait_lock(struct rk3588_clk_platform_data *pdata)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t count = 0, pllcon;

    /*
     * Lock time typical 250, max 500 input clock cycles @24MHz, So define a
     * very safe maximum of 1000us, meaning 24000 cycles.
     */
    do {
        pllcon = HWREG32(pdata->base + 6*4);
        ++count;
    } while (pllcon & RK3588_PLLCON6_LOCK_STATUS && count < 10);

    if (count >= 10)
    {
        err = -RT_ETIMEOUT;
    }

    return err;
}

static rt_err_t rk3588_clk_enable(struct rt_clk *clk)
{
    struct rk3588_clk_platform_data *pdata = clk->priv;
    struct rk3588_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rk3588_cru *cru = rk_clk->clk_info.cru;

    if (pdata->base)
    {
        #define PLL_CON(x)              ((x) * 0x4)
        HWREG32(pdata->base + PLL_CON(6)) = HIWORD_UPDATE(0, RK3588_PLLCON1_PWRDOWN, 0);

        rk_clk_wait_lock(pdata);
    }
    else
    {
        void *con_regs;
        struct rk3588_clk_gate *gate;

            gate = &clk_gates[pdata->id];
            con_regs = (void*)cru + gate->offset;

        rk_clrreg(con_regs, RT_BIT(gate->con_bit));
    }

    return RT_EOK;
}


static void rk3588_clk_disable(struct rt_clk *clk)
{
    struct rk3588_clk_platform_data *pdata = clk->priv;
    struct rk3588_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rk3588_cru *cru = rk_clk->clk_info.cru;

    if (pdata->base)
    {
        HWREG32(pdata->base + PLL_CON(1)) = HIWORD_UPDATE(RK3588_PLLCON1_PWRDOWN, RK3588_PLLCON1_PWRDOWN, 0);
    }
    else
    {
        void *con_regs;
        struct rk3588_clk_gate *gate;

            gate = &clk_gates[pdata->id];
            con_regs = (void*)cru + gate->offset;

        rk_setreg(con_regs, RT_BIT(gate->con_bit));
    }

}

static rt_bool_t rk3588_clk_is_enabled(struct rt_clk *clk)
{
    struct rk3588_clk_platform_data *pdata = clk->priv;

    if (pdata->base)
    {
        rt_uint32_t pllcon = HWREG32(pdata->base + PLL_CON(1));

        return !(pllcon & RK3588_PLLCON1_PWRDOWN);
    }

    return RT_TRUE;
}

static rt_err_t rk3588_clk_set_rate(struct rt_clk *clk, rt_ubase_t rate, rt_ubase_t prate)
{
    rt_ubase_t ret = 0;
    rt_ubase_t res_rate;
    struct rk3588_clk_platform_data *pdata = clk->priv;
    struct rk3588_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    struct rk3588_clk_priv *priv = &rk_clk->clk_info;

    if (!priv->gpll_hz)
    {
        LOG_D("%s gpll=%lu\n", __func__, priv->gpll_hz);
        return -RT_ENOENT;
    }

    if (!priv->ppll_hz)
    {
        priv->ppll_hz = rk_pll_get_rate(&rk3588_pll_clks[PPLL],
                              priv->cru, PPLL);
    }

    switch (pdata->id)
    {
    case PLL_CPLL:
        res_rate = rk_pll_set_rate(&rk3588_pll_clks[CPLL], priv->cru,
                        CPLL, rate);
        priv->cpll_hz = rk_pll_get_rate(&rk3588_pll_clks[CPLL],
                              priv->cru, CPLL);
        break;
    case PLL_GPLL:
        res_rate = rk_pll_set_rate(&rk3588_pll_clks[GPLL], priv->cru,
                        GPLL, rate);
        priv->gpll_hz = rk_pll_get_rate(&rk3588_pll_clks[GPLL],
                              priv->cru, GPLL);
        break;
    case PLL_NPLL:
        res_rate = rk_pll_set_rate(&rk3588_pll_clks[NPLL], priv->cru,
                        NPLL, rate);
        break;
    case PLL_V0PLL:
        res_rate = rk_pll_set_rate(&rk3588_pll_clks[V0PLL], priv->cru,
                        V0PLL, rate);
        priv->v0pll_hz = rk_pll_get_rate(&rk3588_pll_clks[V0PLL],
                               priv->cru, V0PLL);
        break;
    case PLL_AUPLL:
        res_rate = rk_pll_set_rate(&rk3588_pll_clks[AUPLL], priv->cru,
                        AUPLL, rate);
        priv->aupll_hz = rk_pll_get_rate(&rk3588_pll_clks[AUPLL],
                               priv->cru, AUPLL);
        break;
    case PLL_PPLL:
        res_rate = rk_pll_set_rate(&rk3588_pll_clks[PPLL], priv->cru,
                        PPLL, rate);
        priv->ppll_hz = rk_pll_get_rate(&rk3588_pll_clks[PPLL],
                              priv->cru, PPLL);
        break;
    case ACLK_CENTER_ROOT:
    case PCLK_CENTER_ROOT:
    case HCLK_CENTER_ROOT:
    case ACLK_CENTER_LOW_ROOT:
        res_rate = rk3588_center_set_clk(priv, pdata->id, rate);
        break;
    case ACLK_TOP_ROOT:
    case PCLK_TOP_ROOT:
    case ACLK_LOW_TOP_ROOT:
        res_rate = rk3588_top_set_clk(priv, pdata->id, rate);
        break;
    case CLK_I2C0:
    case CLK_I2C1:
    case CLK_I2C2:
    case CLK_I2C3:
    case CLK_I2C4:
    case CLK_I2C5:
    case CLK_I2C6:
    case CLK_I2C7:
    case CLK_I2C8:
        res_rate = rk3588_i2c_set_clk(priv, pdata->id, rate);
        break;
    case CLK_SPI0:
    case CLK_SPI1:
    case CLK_SPI2:
    case CLK_SPI3:
    case CLK_SPI4:
        res_rate = rk3588_spi_set_clk(priv, pdata->id, rate);
        break;
    case CLK_PWM1:
    case CLK_PWM2:
    case CLK_PWM3:
    case CLK_PMU1PWM:
        res_rate = rk3588_pwm_set_clk(priv, pdata->id, rate);
        break;
    case CLK_SARADC:
    case CLK_TSADC:
        res_rate = rk3588_adc_set_clk(priv, pdata->id, rate);
        break;
    case CCLK_SRC_SDIO:
    case CCLK_EMMC:
    case BCLK_EMMC:
    case SCLK_SFC:
    case DCLK_DECOM:
        res_rate = rk3588_mmc_set_clk(priv, pdata->id, rate);
        break;
    case TCLK_WDT0:
        res_rate = OSC_HZ;
        break;
#ifndef CONFIG_SPL_BUILD
    case CLK_AUX16M_0:
    case CLK_AUX16M_1:
        rk3588_aux16m_set_clk(priv, pdata->id, rate);
        break;
    case ACLK_VOP_ROOT:
    case ACLK_VOP:
    case ACLK_VOP_LOW_ROOT:
    case HCLK_VOP_ROOT:
        res_rate = rk3588_aclk_vop_set_clk(priv, pdata->id, rate);
        break;
    case DCLK_VOP0:
    case DCLK_VOP0_SRC:
    case DCLK_VOP1:
    case DCLK_VOP1_SRC:
    case DCLK_VOP2:
    case DCLK_VOP2_SRC:
    case DCLK_VOP3:
        res_rate = rk3588_dclk_vop_set_clk(priv, pdata->id, rate);
        break;
    case CLK_GMAC0_PTP_REF:
    case CLK_GMAC1_PTP_REF:
    case CLK_GMAC_125M:
    case CLK_GMAC_50M:
        res_rate = rk3588_gmac_set_clk(priv, pdata->id, rate);
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
        res_rate = rk3588_uart_set_rate(priv, pdata->id, rate);
        break;
    case CLK_REF_PIPE_PHY0:
    case CLK_REF_PIPE_PHY1:
    case CLK_REF_PIPE_PHY2:
        res_rate = rk3588_pciephy_set_rate(priv, pdata->id, rate);
        break;
#endif
    default:
        return -RT_ENOENT;
    }

    if ((rt_base_t)res_rate > 0)
    {
        clk->rate = res_rate;
    }
    else
    {
        ret = (rt_ubase_t)res_rate > 0 ? RT_EOK : (rt_err_t)res_rate;
    }

    return ret;
};

static int  rk3588_dclk_vop_set_parent(struct rt_clk *clk,
                             struct rt_clk *parent)
{
    struct rk3588_clk_platform_data *pdata = clk->priv;
    struct rk3588_clk_platform_data *ppdata = parent->priv;
    struct rk3588_clk *rk_clk = raw_to_rk_clk(clk->clk_np);
    /*struct rk3588_clk_priv *priv = &rk_clk->clk_info;*/
    struct rk3588_cru *cru = rk_clk->clk_info.cru;

    rt_uint32_t sel;
    const char *clock_dev_name = parent->dev_id;

    if (ppdata->id == PLL_V0PLL)
        sel = 2;
    else if (ppdata->id == PLL_GPLL)
        sel = 0;
    else if (ppdata->id == PLL_CPLL)
        sel = 1;
    else
        sel = 3;

    switch (pdata->id)
    {
    case DCLK_VOP0_SRC:
        rk_clrsetreg(&cru->clksel_con[111], DCLK0_VOP_SRC_SEL_MASK,
                 sel << DCLK0_VOP_SRC_SEL_SHIFT);
        break;
    case DCLK_VOP1_SRC:
        rk_clrsetreg(&cru->clksel_con[111], DCLK1_VOP_SRC_SEL_MASK,
                 sel << DCLK1_VOP_SRC_SEL_SHIFT);
        break;
    case DCLK_VOP2_SRC:
        rk_clrsetreg(&cru->clksel_con[112], DCLK2_VOP_SRC_SEL_MASK,
                 sel << DCLK2_VOP_SRC_SEL_SHIFT);
        break;
    case DCLK_VOP3:
        rk_clrsetreg(&cru->clksel_con[113], DCLK3_VOP_SRC_SEL_MASK,
                 sel << DCLK3_VOP_SRC_SEL_SHIFT);
        break;
    case DCLK_VOP0:
        if (!rt_strcmp(clock_dev_name, "hdmiphypll_clk0"))
            sel = 1;
        else if (!rt_strcmp(clock_dev_name, "hdmiphypll_clk1"))
            sel = 2;
        else
            sel = 0;
        rk_clrsetreg(&cru->clksel_con[112], DCLK0_VOP_SEL_MASK,
                 sel << DCLK0_VOP_SEL_SHIFT);
        break;
    case DCLK_VOP1:
        if (!rt_strcmp(clock_dev_name, "hdmiphypll_clk0"))
            sel = 1;
        else if (!rt_strcmp(clock_dev_name, "hdmiphypll_clk1"))
            sel = 2;
        else
            sel = 0;
        rk_clrsetreg(&cru->clksel_con[112], DCLK1_VOP_SEL_MASK,
                 sel << DCLK1_VOP_SEL_SHIFT);
        break;
    case DCLK_VOP2:
        if (!rt_strcmp(clock_dev_name, "hdmiphypll_clk0"))
            sel = 1;
        else if (!rt_strcmp(clock_dev_name, "hdmiphypll_clk1"))
            sel = 2;
        else
            sel = 0;
        rk_clrsetreg(&cru->clksel_con[112], DCLK2_VOP_SEL_MASK,
                 sel << DCLK2_VOP_SEL_SHIFT);
        break;
    default:
        return -RT_EINVAL;
    }
    return 0;
}

static rt_err_t rk3588_clk_set_parent(struct rt_clk *clk, struct rt_clk *parent)
{
    struct rk3588_clk_platform_data *pdata = clk->priv;
    switch (pdata->id)
    {
    case DCLK_VOP0_SRC:
    case DCLK_VOP1_SRC:
    case DCLK_VOP2_SRC:
    case DCLK_VOP0:
    case DCLK_VOP1:
    case DCLK_VOP2:
    case DCLK_VOP3:
        return rk3588_dclk_vop_set_parent(clk, parent);
    default:
        return -RT_ENOENT;
    }

    return 0;
}

static rt_err_t rk3588_clk_set_phase(struct rt_clk *clk, int degrees)
{
    rt_err_t res;
    struct rk3588_clk_platform_data *pdata = clk->priv;
    struct rk3588_clk *rk_clk = raw_to_rk_clk(clk->clk_np);

    switch (pdata->id)
    {
    case SCLK_SDIO_DRV:
    case SCLK_SDIO_SAMPLE:
    case SCLK_SDMMC_DRV:
    case SCLK_SDMMC_SAMPLE:
        res = mmc_set_phase(pdata, rk_clk, degrees);
        break;

    default:
        return -RT_EINVAL;
    }

    return res;
}

static rt_base_t rk3588_clk_get_phase(struct rt_clk *clk)
{
    rt_base_t res;
    struct rk3588_clk_platform_data *pdata = clk->priv;
    struct rk3588_clk *rk_clk = raw_to_rk_clk(clk->clk_np);

    switch (pdata->id)
    {
    case SCLK_SDIO_DRV:
    case SCLK_SDIO_SAMPLE:
    case SCLK_SDMMC_DRV:
    case SCLK_SDMMC_SAMPLE:
        res = mmc_get_phase(pdata, rk_clk);
        break;

    default:
        return -RT_EINVAL;
    }

    return res;
}

static rt_base_t rk3588_clk_round_rate(struct rt_clk *clk, rt_ubase_t drate,
        rt_ubase_t *prate)
{
    return rk_clk_pll_round_rate(rk3588_pll_rates, RT_ARRAY_SIZE(rk3588_pll_rates), drate, prate);
}

static const struct rt_clk_ops rk3588_clk_ops =
{
    .init = rk3588_clk_init,
    .enable = rk3588_clk_enable,
    .disable = rk3588_clk_disable,
    .is_enabled = rk3588_clk_is_enabled,
    .set_rate = rk3588_clk_set_rate,
    .set_parent = rk3588_clk_set_parent,
    .set_phase = rk3588_clk_set_phase,
    .get_phase = rk3588_clk_get_phase,
    .round_rate = rk3588_clk_round_rate,
};















































static void rk3588_cru_init(struct rk3588_clk *rk_clk, struct rt_ofw_node *np)
{
    rt_int32_t ret, div;

    struct rk3588_clk_priv *priv = &rk_clk->clk_info;

div = RT_DIV_ROUND_UP(GPLL_HZ, 300 * MHz);
priv->cru = (struct rk3588_cru *)rk_clk->base;
    rk_clrsetreg(&priv->cru->clksel_con[38],
             ACLK_BUS_ROOT_SEL_MASK |
             ACLK_BUS_ROOT_DIV_MASK,
             div << ACLK_BUS_ROOT_DIV_SHIFT);


    if (priv->cpll_hz != CPLL_HZ)
    {
        ret = rk_pll_set_rate(&rk3588_pll_clks[CPLL], priv->cru,
                        CPLL, CPLL_HZ);
        if (!ret)
            priv->cpll_hz = CPLL_HZ;
    }
    if (priv->gpll_hz != GPLL_HZ)
    {
        ret = rk_pll_set_rate(&rk3588_pll_clks[GPLL], priv->cru,
                        GPLL, GPLL_HZ);
        if (!ret)
            priv->gpll_hz = GPLL_HZ;
    }

    if (priv->ppll_hz != PPLL_HZ)
    {
        ret = rk_pll_set_rate(&rk3588_pll_clks[PPLL], priv->cru,
                        PPLL, PPLL_HZ);
        priv->ppll_hz = rk_pll_get_rate(&rk3588_pll_clks[PPLL],
                              priv->cru, PPLL);
    }
    rk_clrsetreg(&priv->cru->clksel_con[9],
             ACLK_TOP_S400_SEL_MASK |
             ACLK_TOP_S200_SEL_MASK,
             (ACLK_TOP_S400_SEL_400M << ACLK_TOP_S400_SEL_SHIFT) |
             (ACLK_TOP_S200_SEL_200M << ACLK_TOP_S200_SEL_SHIFT));
}
static rt_err_t clk_rk3588_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_size_t data_size = CLK_NR_CLKS * sizeof(struct rk3588_clk_platform_data);
    struct rk3588_clk *rk_clk;
    struct rt_ofw_node *np = pdev->parent.ofw_node;

    rk_clk = rt_malloc(sizeof(*rk_clk) + data_size);

    if (rk_clk)
    {
        void *softrst_regs = RT_NULL;
        rt_memset(&rk_clk->parent, 0, sizeof(rk_clk->parent));

        rk_clk->base = rt_ofw_iomap(np, 0);
/*rt_kprintf("base %p\n", rk_clk->base);*/
        if (!rk_clk->base)
        {
            err = -RT_EIO;
            goto _fail;
        }


            rk3588_cru_init(rk_clk, np);
            softrst_regs = &rk_clk->clk_info.cru->softrst_con;


        rk_clk->parent.parent.ops = &rk3588_clk_ops;

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

static const struct rt_ofw_node_id clk_rk3588_ofw_ids[] =
{
    { .compatible = "rockchip,rk3588-cru" },
    { /* sentinel */ }
};

static struct rt_platform_driver clk_rk3588_driver =
{
    .name = "clk-rk3588",
    .ids = clk_rk3588_ofw_ids,

    .probe = clk_rk3588_probe,
};

static int clk_rk3588_register(void)
{
    rt_platform_driver_register(&clk_rk3588_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(clk_rk3588_register);
