/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety       first version
 */

#include <rtthread.h>
#include "at91sam9g45.h"

static rt_list_t clocks;

struct clk {
    char name[32];
    rt_uint32_t rate_hz;
    struct clk *parent;
    rt_list_t  node;
};

static struct clk clk32k = {
    "clk32k",
    AT91C_SLOW_CLOCK,
    RT_NULL,
    {RT_NULL, RT_NULL},
};

static struct clk main_clk = {
    "main",
    0,
    RT_NULL,
    {RT_NULL, RT_NULL},
};

static struct clk plla = {
    "plla",
    0,
    &main_clk,
    {RT_NULL, RT_NULL},
};

static struct clk mck = {
    "mck",
    0,
    RT_NULL,
    {RT_NULL, RT_NULL},
};

static struct clk upllck = {
    "upllck",
    480*1000*1000,
    &main_clk,
    {RT_NULL, RT_NULL},
};

static struct clk *const standard_pmc_clocks[] = {
    /* four primary clocks */
    &clk32k,
    &main_clk,
    &plla,

    /* MCK */
    &mck
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
    rt_uint32_t rate;

    for (;;) {
        rate = clk->rate_hz;
        if (rate || !clk->parent)
            break;
        clk = clk->parent;
    }
    return rate;
}

static void at91_upllck_init(rt_uint32_t main_clock)
{
    // EHCI USB use fixed 480MHz clock
}

static struct clk *at91_css_to_clk(unsigned long css)
{
    switch (css) {
        case AT91C_PMC_CSS_SLOW_CLK:
            return &clk32k;
        case AT91C_PMC_CSS_MAIN_CLK:
            return &main_clk;
        case AT91C_PMC_CSS_PLLA_CLK:
            return &plla;
        case AT91C_PMC_CSS_UPLL_CLK:
            return &upllck;
    }

    return RT_NULL;
}

// TODO: how to auto-set register value by OSC and MCK
/* Settings at 400/133MHz */
// In datasheet, ATMEL says 12MHz main crystal startup time less than 2ms, so we
// configure OSC startup timeout to 64*8/32768=15.6ms, should enough
#define BOARD_OSCOUNT           (AT91C_CKGR_OSCOUNT & (64 << 8))
// MAINCK => Divider(DIVA) => PLLA(MULA, OUTA) => /1/2 Divider(PLLADIV2) => PLLACK
// pls. refer to doc6438G figure 24-6 on pg294.     ICPLLA in reg PMC_PLLICPR
// 12MHz / 3 * (199 + 1) = 800MHz
// OUTA/ICPLLA can as ICPLLA:OUTA[1]:OUTA[0] = (800-PLLAOUT(MHz))/50
// PLLACOUNT field occupy bit[13:8], max value is 0x3F, then about 19.2ms
#define BOARD_CKGR_PLLA         (AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT         (0x3F << 8)
#define BOARD_MULA              (AT91C_CKGR_MULA & (199 << 16))
#define BOARD_DIVA              (AT91C_CKGR_DIVA & 3)
// Clock Source => select(CCS) => Prescaler(PRES) => Master Clock Divider(MDIV) => MCK
//                                                => Processor Clock Divider => PCK
// Master clock can refer to doc6438G figure 25-2 on pg298
// PLLADIV2=1(div 2, 400MHz), PRES=0(no div, 400MHz),
// MDIV=3(Master Clock divided by 3, 133MHz), CSS=0(still Slow Clock)
#define BOARD_PRESCALER         (0x00001300) //400/133MHz

#define MHz(n)      ((n) * 1000 * 1000)
#define OSC_FREQ    MHz(12)
#define PLLA_FREQ   MHz(800)

static void at91_plla_init(void)
{
    rt_uint32_t pllar, mckr;

    // Code refer to doc6438G, 25.10 Programming Sequence
    /* Initialize main oscillator
     ****************************/
    // enable main OSC and wait OSC startup time timeout.
    AT91C_BASE_PMC->PMC_MOR = BOARD_OSCOUNT | AT91C_CKGR_MOSCEN;
    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCS));

    /* Initialize PLLA, Set PLL to 800MHz and wait PLL stable */
    pllar = (MHz(800) - PLLA_FREQ) / MHz(50);       // please refer to Table 46-15 of doc 6438G
    AT91C_BASE_PMC->PMC_PLLICPR = (pllar >> 2) & 1; // ICPLLA
    pllar = (pllar & 3) << 14;  // OUTA
    pllar |= BOARD_DIVA;        // PLLA input clock as 4MHz
    pllar |= BOARD_MULA;        // PLLA output clock as 800MHz
    pllar |= BOARD_PLLACOUNT;
    pllar |= AT91C_CKGR_SRCA;   // I don't known what means, but seems must set it
    AT91C_BASE_PMC->PMC_PLLAR = pllar;

    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKA));

    /* Wait for the master clock if it was already initialized */
    // make sure Master clock in READY status before operate it
    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));

    /* Switch to fast clock
     **********************/
    /* setup main clock divisor and prescaler, 400MHz/133MHz, but don't switch */
    mckr = AT91C_BASE_PMC->PMC_MCKR;
    if ((mckr & AT91C_PMC_MDIV) != (BOARD_PRESCALER & AT91C_PMC_MDIV))
    {
        mckr = (mckr & ~(unsigned int)AT91C_PMC_MDIV) | (BOARD_PRESCALER & AT91C_PMC_MDIV);
        AT91C_BASE_PMC->PMC_MCKR = mckr;
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));
    }

    /* Switch to PLL + prescaler, now Switch to PLLA as source, run on the fly */
    if ((mckr & AT91C_PMC_CSS) != AT91C_PMC_CSS_PLLA_CLK)
    {
        mckr = (mckr & ~(unsigned int)AT91C_PMC_CSS) | AT91C_PMC_CSS_PLLA_CLK;
        AT91C_BASE_PMC->PMC_MCKR = mckr;
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));
    }

    plla.rate_hz = PLLA_FREQ;
}

#define false 0
#define true  1
int at91_clock_init(rt_uint32_t main_clock)
{
    unsigned tmp, freq, mckr, mdiv;
    int i;

    /*
     * When the bootloader initialized the main oscillator correctly,
     * there's no problem using the cycle counter.  But if it didn't,
     * or when using oscillator bypass mode, we must be told the speed
     * of the main clock.
     */
    if (!main_clock) {
        do {
            tmp = readl(AT91C_CKGR_MCFR);
        } while (!(tmp & AT91C_CKGR_MAINRDY));
        main_clock = (tmp & AT91C_CKGR_MAINF) * (AT91C_SLOW_CLOCK / 16);
    }
    main_clk.rate_hz = main_clock;

    at91_plla_init();

    at91_upllck_init(main_clock);

    /*
     * MCK and CPU derive from one of those primary clocks.
     * For now, assume this parentage won't change.
     */
    mckr = readl(AT91C_PMC_MCKR);
    mck.parent = at91_css_to_clk(mckr & AT91C_PMC_CSS);
    freq = mck.parent->rate_hz;
    freq /= (1 << ((mckr & AT91C_PMC_PRES) >> 2));  /* prescale */
    mdiv = 1 << ((mckr & AT91C_PMC_MDIV) >> 8);
    if (mdiv == 8) mdiv = 3;
    freq /= mdiv;           /* mdiv */
    if (mckr & AT91C_PMC_PLLADIV2) freq /= 2;   /* plla_div2 */
    mck.rate_hz = freq;

    /* Register the PMC's standard clocks */
    rt_list_init(&clocks);
    for (i = 0; i < ARRAY_SIZE(standard_pmc_clocks); i++)
        rt_list_insert_after(&clocks, &standard_pmc_clocks[i]->node);

    rt_list_insert_after(&clocks, &upllck.node);

    /* MCK and CPU clock are "always on" */
    //clk_enable(&mck);

    /*rt_kprintf("Clocks: CPU %u MHz, master %u MHz, main %u.%03u MHz\n",
        freq / 1000000, (unsigned) mck.rate_hz / 1000000,
        (unsigned) main_clock / 1000000,
        ((unsigned) main_clock % 1000000) / 1000);*///cause blocked

    return 0;
}

/**
 * @brief System Clock Configuration
 */
void rt_hw_clock_init(void)
{
    at91_clock_init(MHz(12));
}

