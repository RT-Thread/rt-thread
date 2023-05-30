/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-04-25     Yi.qiu       first version
 */

#include <rtthread.h>
#include "s3c24x0.h"

#define CONFIG_SYS_CLK_FREQ 12000000    // Fin = 12.00MHz

#if CONFIG_SYS_CLK_FREQ == 12000000
    /* MPLL=2*12*100/6=400MHz   */
    #define     MPL_MIDV    92      /* m=MPL_MDIV+8=100 */
    #define     MPL_PDIV    4       /* p=MPL_PDIV+2=6   */
    #define     MPL_SDIV    0       /* s=MPL_SDIV=0 */
    /* UPLL=12*64/8=96MHz */
    #define     UPL_MDIV    56      /* m=UPL_MDIV+8=64 */
    #define     UPL_PDIV    2       /* p=UPL_PDIV+2=4   */
    #define     UPL_SDIV    1       /* s=UPL_SDIV=1 */
    /* System clock divider FCLK:HCLK:PCLK=1:4:8 */
    #define     DIVN_UPLL       0x1     /* UCLK = UPLL clock / 2 */
    #define     HDIVN           0x2     /* HCLK = FCLK / 4 */
    #define     PDIVN           0x1     /* PCLK = HCLK / 2 */
#endif

rt_uint32_t PCLK;
rt_uint32_t FCLK;
rt_uint32_t HCLK;
rt_uint32_t UCLK;

void rt_hw_get_clock(void)
{
    rt_uint32_t val;
    rt_uint8_t m, p, s;

    val = MPLLCON;
    m = (val>>12)&0xff;
    p = (val>>4)&0x3f;
    s = val&3;

    FCLK = ((m+8)*(CONFIG_SYS_CLK_FREQ/100)*2)/((p+2)*(1<<s))*100;

    val = CLKDIVN;
    m = (val>>1)&3;
    p = val&1;

    switch (m) {
    case 0:
        HCLK = FCLK;
        break;
    case 1:
        HCLK = FCLK>>1;
        break;
    case 2:
        if(s&2)
            HCLK = FCLK>>3;
        else
            HCLK = FCLK>>2;
        break;
    case 3:
        if(s&1)
            HCLK = FCLK/6;
        else
            HCLK = FCLK/3;
        break;
}

    if(p)
        PCLK = HCLK>>1;
    else
        PCLK = HCLK;
}

void rt_hw_set_mpll_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv)
{
    MPLLCON = sdiv | (pdiv<<4) | (mdiv<<12);
}

void rt_hw_set_upll_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv)
{
    UPLLCON = (mdiv<<12) | (pdiv<<4) | sdiv;
}

void rt_hw_set_divider(rt_uint8_t hdivn, rt_uint8_t pdivn)
{
    CLKDIVN = (hdivn<<1) | pdivn;
}

/**
 * @brief System Clock Configuration
 */
void rt_hw_clock_init(void)
{
    LOCKTIME = 0xFFFFFFFF;
    rt_hw_set_mpll_clock(MPL_SDIV, MPL_PDIV, MPL_MIDV);
    rt_hw_set_upll_clock(UPL_SDIV, UPL_PDIV, UPL_MDIV);
    rt_hw_set_divider(HDIVN, PDIVN);
}

