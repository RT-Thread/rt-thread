/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */

#include <edma.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static rt_uint32_t commonrate;
static rt_uint32_t div_by_four;
static rt_uint32_t div_by_six;
static rt_uint32_t armrate;
static rt_uint32_t fixedrate;
static rt_uint32_t ddrrate;
static rt_uint32_t voicerate;
static rt_uint32_t mmcsdrate;
static rt_uint32_t vpssrate, vencrate_sd, vencrate_hd;


/* Four Transfer Controllers on DM365 */
static const rt_int8_t
dm365_queue_tc_mapping[][2] = {
    /* {event queue no, TC no} */
    {0, 0},
    {1, 1},
    {2, 2},
    {3, 3},
    {-1, -1},
};

static const rt_int8_t
dm365_queue_priority_mapping[][2] = {
    /* {event queue no, Priority} */
    {0, 7},
    {1, 7},
    {2, 7},
    {3, 0},
    {-1, -1},
};

static struct edma_soc_info edma_cc0_info = {
    .n_channel      = 64,
    .n_region       = 4,
    .n_slot         = 256,
    .n_tc           = 4,
    .n_cc           = 1,
    .queue_tc_mapping   = dm365_queue_tc_mapping,
    .queue_priority_mapping = dm365_queue_priority_mapping,
    .default_queue      = EVENTQ_3,
};

static struct edma_soc_info *dm365_edma_info[EDMA_MAX_CC] = {
    &edma_cc0_info,
};

static rt_list_t clocks;

struct clk {
    char name[32];
    rt_uint32_t *rate_hz;
    struct clk *parent;
    rt_list_t  node;
};

static struct clk davinci_dm365_clks[] = {
    {
        .name = "ARMCLK",
        .rate_hz = &armrate,
    },
    {
        .name = "UART0",
        .rate_hz = &fixedrate,
    },
    {
        .name = "UART1",
        .rate_hz = &commonrate,
    },
    {
        .name = "HPI",
        .rate_hz = &commonrate,
    },
    {
        .name = "EMACCLK",
        .rate_hz = &commonrate,
    },
    {
        .name = "I2CCLK",
        .rate_hz = &fixedrate,
    },
    {
        .name = "McBSPCLK",
        .rate_hz = &commonrate,
    },
    {
        .name = "MMCSDCLK0",
        .rate_hz = &mmcsdrate,
    },
    {
        .name = "MMCSDCLK1",
        .rate_hz = &mmcsdrate,
    },
    {
        .name = "SPICLK",
        .rate_hz = &commonrate,
    },
    {
        .name = "gpio",
        .rate_hz = &commonrate,
    },
    {
        .name = "AEMIFCLK",
        .rate_hz = &commonrate,
    },
    {
        .name = "PWM0_CLK",
        .rate_hz = &fixedrate,
    },
    {
        .name = "PWM1_CLK",
        .rate_hz = &fixedrate,
    },
    {
        .name = "PWM2_CLK",
        .rate_hz = &fixedrate,
    },
    {
        .name = "PWM3_CLK",
        .rate_hz = &fixedrate,
    },
    {
        .name = "USBCLK",
        .rate_hz = &fixedrate,
    },
    {
        .name = "VOICECODEC_CLK",
        .rate_hz = &voicerate,
    },
    {
        .name = "RTC_CLK",
        .rate_hz = &fixedrate,
    },
    {
        .name = "KEYSCAN_CLK",
        .rate_hz = &fixedrate,
    },
    {
        .name = "ADCIF_CLK",
        .rate_hz = &fixedrate,
    },
};

/* clocks cannot be de-registered no refcounting necessary */
struct clk *clk_get(const char *id)
{
    struct clk *clk;
    rt_list_t *list;

    for (list = (&clocks)->next; list != &clocks; list = list->next)
    {
        clk = (struct clk *)rt_list_entry(list, struct clk, node);
        if (rt_strcmp(id, clk->name) == 0)
            return clk;
    }

    return RT_NULL;
}

rt_uint32_t clk_get_rate(struct clk *clk)
{
    rt_uint32_t flags;
    rt_uint32_t *rate;

    for (;;) {
        rate = clk->rate_hz;
        if (rate || !clk->parent)
            break;
        clk = clk->parent;
    }
    return *rate;
}

void clk_register(struct clk *clk)
{
    rt_list_insert_after(&clocks, &clk->node);
}

int davinci_register_clks(struct clk *clk_list, int num_clks)
{
    struct clk *clkp;
    int i;

    for (i = 0, clkp = clk_list; i < num_clks; i++, clkp++)
    {
        //rt_kprintf("1:%s\n", clkp->name);
        clk_register(clkp);
        //rt_kprintf("2:%s\n", clkp->name);
    }

    return 0;
}

/* PLL/Reset register offsets */
#define PLLM        0x110
#define PREDIV      0x114
#define PLLDIV2     0x11C
#define POSTDIV     0x128
#define PLLDIV4     0x160
#define PLLDIV5     0x164
#define PLLDIV6     0x168
#define PLLDIV7     0x16C
#define PLLDIV8     0x170


int davinci_clk_init(void)
{
    struct clk *clk_list;
    int num_clks;
    rt_uint32_t pll0_mult, pll1_mult;

    unsigned long prediv, postdiv;
    unsigned long pll_rate;
    unsigned long pll_div2, pll_div4, pll_div5,
        pll_div6, pll_div7, pll_div8;

    rt_list_init(&clocks);

    //davinci_psc_register(davinci_psc_base, 1);

    pll0_mult = davinci_readl(DAVINCI_PLL_CNTRL0_BASE + PLLM);
    pll1_mult = davinci_readl(DAVINCI_PLL_CNTRL1_BASE + PLLM);

    commonrate = ((pll0_mult + 1) * 27000000) / 6;
    armrate = ((pll0_mult + 1) * 27000000) / 2;

    fixedrate = 24000000;

    /* Read PLL0 configuration */
    prediv = (davinci_readl(DAVINCI_PLL_CNTRL0_BASE + PREDIV) &
            0x1f) + 1;
    postdiv = (davinci_readl(DAVINCI_PLL_CNTRL0_BASE + POSTDIV) &
            0x1f) + 1;

    /* PLL0 dividers */
    pll_div4 = (davinci_readl(DAVINCI_PLL_CNTRL0_BASE + PLLDIV4) &
            0x1f) + 1; /* EDMA, EMAC, config, common */
    pll_div5 = (davinci_readl(DAVINCI_PLL_CNTRL0_BASE + PLLDIV5) &
            0x1f) + 1; /* VPSS */
    pll_div6 = (davinci_readl(DAVINCI_PLL_CNTRL0_BASE + PLLDIV6) &
            0x1f) + 1; /* VENC */
    pll_div7 = (davinci_readl(DAVINCI_PLL_CNTRL0_BASE + PLLDIV7) &
            0x1f) + 1; /* DDR */
    pll_div8 = (davinci_readl(DAVINCI_PLL_CNTRL0_BASE + PLLDIV8) &
            0x1f) + 1; /* MMC/SD */

    pll_rate = ((fixedrate / prediv) * (2 * pll0_mult)) / postdiv;

    commonrate = pll_rate / pll_div4; /* 486/4 = 121.5MHz */
    vpssrate = pll_rate / pll_div5; /* 486/2 = 243MHz */
    vencrate_sd = pll_rate / pll_div6; /* 486/18 =  27MHz */
    ddrrate = pll_rate / pll_div7; /* 486/2 = 243MHz */
    mmcsdrate = pll_rate / pll_div8; /* 486/4 =  121.5MHz */

    rt_kprintf(
        "PLL0: fixedrate: %d, commonrate: %d, vpssrate: %d\n",
        fixedrate, commonrate, vpssrate);
    rt_kprintf(
        "PLL0: vencrate_sd: %d, ddrrate: %d mmcsdrate: %d\n",
        vencrate_sd, (ddrrate/2), mmcsdrate);

    /* Read PLL1 configuration */
    prediv = (davinci_readl(DAVINCI_PLL_CNTRL1_BASE + PREDIV) &
            0x1f) + 1;
    postdiv = (davinci_readl(DAVINCI_PLL_CNTRL1_BASE + POSTDIV) &
            0x1f) + 1;
    pll_rate = ((fixedrate / prediv) * (2 * pll1_mult)) / postdiv;

    /* PLL1 dividers */
    pll_div2 = (davinci_readl(DAVINCI_PLL_CNTRL1_BASE + PLLDIV2) &
            0x1f) + 1; /* ARM */
    pll_div4 = (davinci_readl(DAVINCI_PLL_CNTRL1_BASE + PLLDIV4) &
            0x1f) + 1; /* VOICE */
    pll_div5 = (davinci_readl(DAVINCI_PLL_CNTRL1_BASE + PLLDIV5) &
            0x1f) + 1; /* VENC */

    armrate = pll_rate / pll_div2; /* 594/2 = 297MHz */
    voicerate = pll_rate / pll_div4; /* 594/6 = 99MHz */
    vencrate_hd = pll_rate / pll_div5; /* 594/8 = 74.25MHz */

    rt_kprintf(
        "PLL1: armrate: %d, voicerate: %d, vencrate_hd: %d\n",
        armrate, voicerate, vencrate_hd);

    clk_list = davinci_dm365_clks;
    num_clks = ARRAY_SIZE(davinci_dm365_clks);

    return davinci_register_clks(clk_list, num_clks);
}

int platform_init(void)
{
    edma_init(dm365_edma_info);
}

INIT_BOARD_EXPORT(platform_init);

/* Reset board using the watchdog timer */
void reset_system(void)
{
    rt_uint32_t tgcr, wdtcr;
    rt_uint32_t base = DAVINCI_WDOG_BASE;

    /* Disable, internal clock source */
    davinci_writel(0, base + TCR);

    /* Reset timer, set mode to 64-bit watchdog, and unreset */
    davinci_writel(0, base + TGCR);
    tgcr =  (TGCR_TIMMODE_64BIT_WDOG << TGCR_TIMMODE_SHIFT) |
        (TGCR_UNRESET << TGCR_TIM12RS_SHIFT) |
        (TGCR_UNRESET << TGCR_TIM34RS_SHIFT);
    davinci_writel(tgcr, base + TGCR);

    /* Clear counter and period regs */
    davinci_writel(0, base + TIM12);
    davinci_writel(0, base + TIM34);
    davinci_writel(0, base + PRD12);
    davinci_writel(0, base + PRD34);

    /* Enable periodic mode */
    davinci_writel(TCR_ENAMODE_PERIODIC << ENAMODE12_SHIFT, base + TCR);

    /* Put watchdog in pre-active state */
    wdtcr = (WDTCR_WDKEY_SEQ0 << WDTCR_WDKEY_SHIFT) |
        (WDTCR_WDEN_ENABLE << WDTCR_WDEN_SHIFT);
    davinci_writel(wdtcr, base + WDTCR);

    /* Put watchdog in active state */
    wdtcr = (WDTCR_WDKEY_SEQ1 << WDTCR_WDKEY_SHIFT) |
        (WDTCR_WDEN_ENABLE << WDTCR_WDEN_SHIFT);
    davinci_writel(wdtcr, base + WDTCR);

    /*
     * Write an invalid value to the WDKEY field to trigger
     * a watchdog reset.
     */
    wdtcr = 0xDEADBEEF;
    davinci_writel(wdtcr, base + WDTCR);
}


