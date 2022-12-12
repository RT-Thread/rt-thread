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

/*
static rt_list_t clocks;

struct clk {
    char name[32];
    rt_uint32_t rate_hz;
    struct clk *parent;
    rt_list_t  node;
};

static struct clk clk32k = {
    "clk32k",
    AT91_SLOW_CLOCK,
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
    RT_NULL,
    {RT_NULL, RT_NULL},
};

static struct clk mck = {
    "mck",
    0,
    RT_NULL,
    {RT_NULL, RT_NULL},
};

static struct clk uhpck = {
    "uhpck",
    0,
    RT_NULL,
    {RT_NULL, RT_NULL},
};

static struct clk pllb = {
    "pllb",
    0,
    &main_clk,
    {RT_NULL, RT_NULL},
};

static struct clk udpck = {
    "udpck",
    0,
    &pllb,
    {RT_NULL, RT_NULL},
};

static struct clk *const standard_pmc_clocks[] = {
    // four primary clocks
    &clk32k,
    &main_clk,
    &plla,

    // MCK
    &mck
};

// clocks cannot be de-registered no refcounting necessary
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

static rt_uint32_t at91_pll_rate(struct clk *pll, rt_uint32_t freq, rt_uint32_t reg)
{
    unsigned mul, div;

    div = reg & 0xff;
    mul = (reg >> 16) & 0x7ff;
    if (div && mul) {
        freq /= div;
        freq *= mul + 1;
    } else
        freq = 0;

    return freq;
}

static unsigned at91_pll_calc(unsigned main_freq, unsigned out_freq)
{
    unsigned i, div = 0, mul = 0, diff = 1 << 30;
    unsigned ret = (out_freq > 155000000) ? 0xbe00 : 0x3e00;

    //PLL output max 240 MHz (or 180 MHz per errata)
    if (out_freq > 240000000)
        goto fail;

    for (i = 1; i < 256; i++) {
        int diff1;
        unsigned input, mul1;

        //
        // PLL input between 1MHz and 32MHz per spec, but lower
        // frequences seem necessary in some cases so allow 100K.
        // Warning: some newer products need 2MHz min.
        //
        input = main_freq / i;
        if (input < 100000)
            continue;
        if (input > 32000000)
            continue;

        mul1 = out_freq / input;
        if (mul1 > 2048)
            continue;
        if (mul1 < 2)
            goto fail;

        diff1 = out_freq - input * mul1;
        if (diff1 < 0)
            diff1 = -diff1;
        if (diff > diff1) {
            diff = diff1;
            div = i;
            mul = mul1;
            if (diff == 0)
                break;
        }
    }
    if (i == 256 && diff > (out_freq >> 5))
        goto fail;
    return ret | ((mul - 1) << 16) | div;
fail:
    return 0;
}

static rt_uint32_t at91_usb_rate(struct clk *pll, rt_uint32_t freq, rt_uint32_t reg)
{
    if (pll == &pllb && (reg & AT91_PMC_USB96M))
        return freq / 2;
    else
        return freq;
}


// PLLB generated USB full speed clock init
static void at91_pllb_usbfs_clock_init(rt_uint32_t main_clock)
{
    rt_uint32_t at91_pllb_usb_init;
    //
    // USB clock init:  choose 48 MHz PLLB value,
    // disable 48MHz clock during usb peripheral suspend.
    //
    // REVISIT:  assumes MCK doesn't derive from PLLB!
    //
    uhpck.parent = &pllb;

    at91_pllb_usb_init = at91_pll_calc(main_clock, 48000000 * 2) | AT91_PMC_USB96M;
    pllb.rate_hz = at91_pll_rate(&pllb, main_clock, at91_pllb_usb_init);

    at91_sys_write(AT91_CKGR_PLLBR, 0);

    udpck.rate_hz = at91_usb_rate(&pllb, pllb.rate_hz, at91_pllb_usb_init);
    uhpck.rate_hz = at91_usb_rate(&pllb, pllb.rate_hz, at91_pllb_usb_init);
}

static struct clk *at91_css_to_clk(unsigned long css)
{
    switch (css) {
        case AT91_PMC_CSS_SLOW:
            return &clk32k;
        case AT91_PMC_CSS_MAIN:
            return &main_clk;
        case AT91_PMC_CSS_PLLA:
            return &plla;
        case AT91_PMC_CSS_PLLB:
            return &pllb;
    }

    return RT_NULL;
}

#define false 0
#define true  1
int at91_clock_init(rt_uint32_t main_clock)
{
    unsigned tmp, freq, mckr;
    int i;
    int pll_overclock = false;

    //
    // When the bootloader initialized the main oscillator correctly,
    // there's no problem using the cycle counter.  But if it didn't,
    // or when using oscillator bypass mode, we must be told the speed
     // of the main clock.
    //
    if (!main_clock) {
        do {
            tmp = at91_sys_read(AT91_CKGR_MCFR);
        } while (!(tmp & AT91_PMC_MAINRDY));
        main_clock = (tmp & AT91_PMC_MAINF) * (AT91_SLOW_CLOCK / 16);
    }
    main_clk.rate_hz = main_clock;

    // report if PLLA is more than mildly overclocked
    plla.rate_hz = at91_pll_rate(&plla, main_clock, at91_sys_read(AT91_CKGR_PLLAR));
    if (plla.rate_hz > 209000000)
        pll_overclock = true;
    if (pll_overclock)
        ;//rt_kprintf("Clocks: PLLA overclocked, %ld MHz\n", plla.rate_hz / 1000000);

    at91_pllb_usbfs_clock_init(main_clock);

    //
     // MCK and CPU derive from one of those primary clocks.
     // For now, assume this parentage won't change.
     //
    mckr = at91_sys_read(AT91_PMC_MCKR);
    mck.parent = at91_css_to_clk(mckr & AT91_PMC_CSS);
    freq = mck.parent->rate_hz;
    freq /= (1 << ((mckr & AT91_PMC_PRES) >> 2));               // prescale

    mck.rate_hz = freq / (1 << ((mckr & AT91_PMC_MDIV) >> 8));      // mdiv

    // Register the PMC's standard clocks
    rt_list_init(&clocks);
    for (i = 0; i < ARRAY_SIZE(standard_pmc_clocks); i++)
        rt_list_insert_after(&clocks, &standard_pmc_clocks[i]->node);

    rt_list_insert_after(&clocks, &pllb.node);
    rt_list_insert_after(&clocks, &uhpck.node);
    rt_list_insert_after(&clocks, &udpck.node);

    // MCK and CPU clock are "always on"
    //clk_enable(&mck);

    //rt_kprintf("Clocks: CPU %u MHz, master %u MHz, main %u.%03u MHz\n",
    //  freq / 1000000, (unsigned) mck.rate_hz / 1000000,
    //  (unsigned) main_clock / 1000000,
    //  ((unsigned) main_clock % 1000000) / 1000); //cause blocked

    return 0;
}
*/

 // @brief System Clock Configuration

void rt_hw_clock_init(void)
{
    //at91_clock_init(18432000);
}

