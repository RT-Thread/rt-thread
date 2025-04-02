/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <rtthread.h>
#include <stdlib.h>
#include <math.h>
#include "sysctl_boot.h"
#include "sysctl_clk.h"
#include "ioremap.h"
#include "board.h"

/* created by yangfan */
/* please refer to the sysctl_clk.h file for API description */

#define OSC_CLOCK_FREQ_24M (24000000)
#define TIMER_PULSE_IN (50000000)

extern volatile sysctl_boot_t *sysctl_boot;
volatile sysctl_clk_t* sysctl_clk = (volatile sysctl_clk_t*)CMU_BASE_ADDR;
/* volatile sysctl_clk_attr_t *sysctl_attr; */

/* Determine the properties of clk. */
int sysctl_clk_attribute(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        /*--------------------------- ROOT CLOCK: OSC24M, PLL0-3 ------------------------------------*/
        case SYSCTL_CLK_ROOT_OSC_IN:
        case SYSCTL_CLK_ROOT_TIMERX_PULSE_IN:
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- CPU0 CLOCK ------------------------------------*/
        case SYSCTL_CLK_CPU0_SRC:
        case SYSCTL_CLK_CPU0_PLIC:
        case SYSCTL_CLK_CPU0_ACLK:
        case SYSCTL_CLK_CPU0_NOC_DDRCP4:
        case SYSCTL_CLK_CPU0_PCLK:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- PMU CLOCK ------------------------------------*/
        case SYSCTL_CLK_PMU_PCLK:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- HS CLOCK ------------------------------------*/
        case SYSCTL_CLK_HS_HCLK_HIGH_SRC:
        case SYSCTL_CLK_HS_HCLK_HIGH_GATE:
        case SYSCTL_CLK_HS_HCLK_SRC:
        case SYSCTL_CLK_SD0_AHB_GATE:
        case SYSCTL_CLK_SD1_AHB_GATE:
        case SYSCTL_CLK_USB0_AHB_GATE:
        case SYSCTL_CLK_USB1_AHB_GATE:
        case SYSCTL_CLK_SSI1_AHB_GATE:
        case SYSCTL_CLK_SSI2_AHB_GATE:

        case SYSCTL_CLK_SSI0_AXI:
        case SYSCTL_CLK_SSI1:
        case SYSCTL_CLK_SSI2:
        case SYSCTL_CLK_QSPI_AXI_SRC:
        case SYSCTL_CLK_SSI1_ACLK_GATE:
        case SYSCTL_CLK_SSI2_ACLK_GATE:

        case SYSCTL_CLK_SSI0:

        case SYSCTL_CLK_SD_AXI_SRC:
        case SYSCTL_CLK_SD0_AXI_GATE:
        case SYSCTL_CLK_SD1_AXI_GATE:
        case SYSCTL_CLK_SD0_BASE_GATE:
        case SYSCTL_CLK_SD1_BASE_GATE:

        case SYSCTL_CLK_SD_CARD_SRC:
        case SYSCTL_CLK_SD0_CARD_GATE:
        case SYSCTL_CLK_SD1_CARD_GATE:

        case SYSCTL_CLK_PLL0_DIV16:
        case SYSCTL_CLK_USB_REF_50M:
        case SYSCTL_CLK_USB0_REF_GATE:
        case SYSCTL_CLK_USB1_REF_GATE:

        case SYSCTL_CLK_SD_TIMER_SRC:
        case SYSCTL_CLK_SD0_TIMER_GATE:
        case SYSCTL_CLK_SD1_TIMER_GATE:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- LS CLOCK ------------------------------------*/
        case SYSCTL_CLK_LS_APB_SRC:
        case SYSCTL_CLK_UART0_APB_GATE:
        case SYSCTL_CLK_UART1_APB_GATE:
        case SYSCTL_CLK_UART2_APB_GATE:
        case SYSCTL_CLK_UART3_APB_GATE:
        case SYSCTL_CLK_UART4_APB_GATE:
        case SYSCTL_CLK_I2C0_APB_GATE:
        case SYSCTL_CLK_I2C1_APB_GATE:
        case SYSCTL_CLK_I2C2_APB_GATE:
        case SYSCTL_CLK_I2C3_APB_GATE:
        case SYSCTL_CLK_I2C4_APB_GATE:
        case SYSCTL_CLK_GPIO_APB_GATE:
        case SYSCTL_CLK_PWM_APB_GATE:
        case SYSCTL_CLK_JAMLINK0_APB_GATE:
        case SYSCTL_CLK_JAMLINK1_APB_GATE:
        case SYSCTL_CLK_JAMLINK2_APB_GATE:
        case SYSCTL_CLK_JAMLINK3_APB_GATE:
        case SYSCTL_CLK_ADC_APB_GATE:

        case SYSCTL_CLK_UART0_CORE:
        case SYSCTL_CLK_UART1_CORE:
        case SYSCTL_CLK_UART2_CORE:
        case SYSCTL_CLK_UART3_CORE:
        case SYSCTL_CLK_UART4_CORE:

        case SYSCTL_CLK_JAMLINK_CO_DIV:
        case SYSCTL_CLK_JAMLINK0_CO_GATE:
        case SYSCTL_CLK_JAMLINK1_CO_GATE:
        case SYSCTL_CLK_JAMLINK2_CO_GATE:
        case SYSCTL_CLK_JAMLINK3_CO_GATE:

        case SYSCTL_CLK_I2C0_CORE:
        case SYSCTL_CLK_I2C1_CORE:
        case SYSCTL_CLK_I2C2_CORE:
        case SYSCTL_CLK_I2C3_CORE:
        case SYSCTL_CLK_I2C4_CORE:

        case SYSCTL_CLK_ADC:
        case SYSCTL_CLK_GOIP_DEBOUNCE:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- SYSCTL CLOCK ------------------------------------*/
        case SYSCTL_CLK_SYSCTRL_APB_SRC:
        case SYSCTL_CLK_WDT0_APB_GATE:
        case SYSCTL_CLK_WDT1_APB_GATE:
        case SYSCTL_CLK_TIMER_APB_GATE:
        case SYSCTL_CLK_IOMUX_APB_GATE:
        case SYSCTL_CLK_MAILBOX_APB_GATE:

        case SYSCTL_CLK_HDI_CORE:

        case SYSCTL_CLK_TIMESTAMP:

        case SYSCTL_CLK_TEMP_SENSOR:

        case SYSCTL_CLK_WDT0:
        case SYSCTL_CLK_WDT1:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- TIMER CLOCK ------------------------------------*/
        case SYSCTL_CLK_TIMERX_PULSE_IN:
        case SYSCTL_CLK_TIMER0_SRC:
        case SYSCTL_CLK_TIMER0:
        case SYSCTL_CLK_TIMER1_SRC:
        case SYSCTL_CLK_TIMER1:
        case SYSCTL_CLK_TIMER2_SRC:
        case SYSCTL_CLK_TIMER2:
        case SYSCTL_CLK_TIMER3_SRC:
        case SYSCTL_CLK_TIMER3:
        case SYSCTL_CLK_TIMER4_SRC:
        case SYSCTL_CLK_TIMER4:
        case SYSCTL_CLK_TIMER5_SRC:
        case SYSCTL_CLK_TIMER5:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- SHRM CLOCK ------------------------------------*/
        case SYSCTL_CLK_SHRM_SRC:
        case SYSCTL_CLK_SHRM_DIV2:
        case SYSCTL_CLK_SHRM_AXIS_SLAVE:
        case SYSCTL_CLK_DECOMPRESS_AXI:

        case SYSCTL_CLK_SHRM_APB:

        case SYSCTL_CLK_SHRM_AXI_SRC:
        case SYSCTL_CLK_NONAI2D_AXI_GATE:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- SEC CLOCK ------------------------------------*/
        case SYSCTL_CLK_SEC_APB:
        case SYSCTL_CLK_SEC_FIX:

        case SYSCTL_CLK_SEC_AXI:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- USB TEST MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_USB_480M:
        case SYSCTL_CLK_USB_100M:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- DPHY DFT MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_DPHY_DFT_MODE:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        /*--------------------------- SPI2AXI CLOCK ------------------------------------*/
        case SYSCTL_CLK_SPI2AXI_AXI:
        {
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
        }

        default:
            return SYSCTL_READ_ENABLE | SYSCTL_WRITE_ENABLE;
    }
}

/*
 * API of root node
 * If PLL bypass, the output clock is 24m clock.
 * If there is no bypass, the clock comes from PLL
 */
bool sysctl_boot_get_root_clk_bypass(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            return ((sysctl_boot->pll[0].cfg1 >> 19) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            return ((sysctl_boot->pll[1].cfg1 >> 19) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            return ((sysctl_boot->pll[2].cfg1 >> 19) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            return ((sysctl_boot->pll[3].cfg1 >> 19) & 0x1) ? true:false;

        default:
            return false;
    }
}

/* if PLL bypass, the output clock is 24m clock. If there is no bypass, the clock comes from PLL */
void sysctl_boot_set_root_clk_bypass(sysctl_clk_node_e clk, bool enable)
{
    volatile uint32_t ret;

    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            if(true == enable)  /* enable bypass */
            {
                sysctl_boot->pll[0].cfg1 |= (1 << 19);
            }
            else
            {
                sysctl_boot->pll[0].cfg1 &= ~(1 << 19);
            }
            return;

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            if(true == enable)  /* enable bypass */
            {
                sysctl_boot->pll[1].cfg1 |= (1 << 19);
            }
            else
            {
                sysctl_boot->pll[1].cfg1 &= ~(1 << 19);
            }
            return;

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            if(true == enable)  /* enable bypass */
            {
                sysctl_boot->pll[2].cfg1 |= (1 << 19);
            }
            else
            {
                sysctl_boot->pll[2].cfg1 &= ~(1 << 19);
            }
            return;

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            if(true == enable)  /* enable bypass */
            {
                sysctl_boot->pll[3].cfg1 |= (1 << 19);
            }
            else
            {
                sysctl_boot->pll[3].cfg1 &= ~(1 << 19);
            }
            return;

        default:
            return;
    }
}

/* Get enable/disable state of PLL output clock */
bool sysctl_boot_get_root_clk_en(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            return ((sysctl_boot->pll[0].ctl >> 2) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            return ((sysctl_boot->pll[1].ctl >> 2) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            return ((sysctl_boot->pll[2].ctl >> 2) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            return ((sysctl_boot->pll[3].ctl >> 2) & 0x1) ? true:false;

        default:
            return false;
    }
}

/* Enable PLL output clock */
void sysctl_boot_set_root_clk_en(sysctl_clk_node_e clk, bool enable)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            if(true == enable)
            {
                sysctl_boot->pll[0].ctl |= (1 << 2) | (1 << 18);     /* enable pll */
            }

            return;

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            if(true == enable)
            {
                sysctl_boot->pll[1].ctl |= (1 << 2) | (1 << 18);     /* enable pll */
            }

            return;

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            if(true == enable)
            {
                sysctl_boot->pll[2].ctl |= (1 << 2) | (1 << 18);     /* enable pll */
            }

            return;

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            if(true == enable)
            {
                sysctl_boot->pll[3].ctl |= (1 << 2) | (1 << 18);     /* enable pll */
            }

            return;

        default:
            return;
    }
}

/* PLL power supply */
bool sysctl_boot_set_root_clk_pwroff(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            sysctl_boot->pll[0].ctl |= (1 << 0)|(1 << 16);
            return true;

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            sysctl_boot->pll[1].ctl |= (1 << 0)|(1 << 16);
            return true;

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            sysctl_boot->pll[2].ctl |= (1 << 0)|(1 << 16);
            return true;

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            sysctl_boot->pll[3].ctl |= (1 << 0)|(1 << 16);
            return true;

        default:
            return false;
    }
}

/* Check the lock state of PLL. */
bool sysctl_boot_get_root_clk_lock(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            return ((sysctl_boot->pll[0].state >> 0) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            return ((sysctl_boot->pll[1].state >> 0) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            return ((sysctl_boot->pll[2].state >> 0) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            return ((sysctl_boot->pll[3].state >> 0) & 0x1) ? true:false;

        default:
            return true;
    }
}

/*
 * Get PLL output frequency.
 * freq = (double)OSC_CLOCK_FREQ_24M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1)
 */
uint32_t sysctl_boot_get_root_clk_freq(sysctl_clk_node_e clk)
{
    uint32_t refdiv;    /* reference clock divide */
    uint32_t outdiv;    /* output clock divide */
    uint32_t fbdiv;     /* feedback clock divide */
    uint32_t freq;

    switch(clk)
    {
        case SYSCTL_CLK_ROOT_OSC_IN:
            return OSC_CLOCK_FREQ_24M;  /* 24MHz */

        case SYSCTL_CLK_ROOT_TIMERX_PULSE_IN:
            return TIMER_PULSE_IN;      /* 50MHz */

        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
        {
            if(true == sysctl_boot_get_root_clk_bypass(clk))
            {
                freq = OSC_CLOCK_FREQ_24M;
            }
            else
            {
                refdiv = (sysctl_boot->pll[0].cfg0 >> 16) & 0x3F;    /* bit 16~21 */
                outdiv = (sysctl_boot->pll[0].cfg0 >> 24) & 0xF;     /* bit 24~27 */
                fbdiv  = (sysctl_boot->pll[0].cfg0 >> 0)  & 0x1FFF;   /* bit 0~12 */
                freq = (double)OSC_CLOCK_FREQ_24M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1);
            }
            switch(clk)
            {
                case SYSCTL_CLK_ROOT_PLL0:
                    return freq;
                case SYSCTL_CLK_ROOT_PLL0_DIV_2:
                    return freq/2;
                case SYSCTL_CLK_ROOT_PLL0_DIV_3:
                    return freq/3;
                default:
                    return freq/4;
            }
        }

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
        {
            if(true == sysctl_boot_get_root_clk_bypass(clk))
            {
                freq = OSC_CLOCK_FREQ_24M;
            }
            else
            {
                refdiv = (sysctl_boot->pll[1].cfg0 >> 16) & 0x3F;    /* bit 16~21 */
                outdiv = (sysctl_boot->pll[1].cfg0 >> 24) & 0xF;     /* bit 24~27 */
                fbdiv  = (sysctl_boot->pll[1].cfg0 >> 0)  & 0x1FFF;   /* bit 0~12 */
                freq = (double)OSC_CLOCK_FREQ_24M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1);
            }
            switch(clk)
            {
                case SYSCTL_CLK_ROOT_PLL1:
                    return freq;
                case SYSCTL_CLK_ROOT_PLL1_DIV_2:
                    return freq/2;
                case SYSCTL_CLK_ROOT_PLL1_DIV_3:
                    return freq/3;
                default:
                    return freq/4;
            }
        }

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
        {
            if(true == sysctl_boot_get_root_clk_bypass(clk))
            {
                freq = OSC_CLOCK_FREQ_24M;
            }
            else
            {
                refdiv = (sysctl_boot->pll[2].cfg0 >> 16) & 0x3F;    /* bit 16~21 */
                outdiv = (sysctl_boot->pll[2].cfg0 >> 24) & 0xF;     /* bit 24~27 */
                fbdiv  = (sysctl_boot->pll[2].cfg0 >> 0)  & 0x1FFF;   /* bit 0~12 */
                freq = (double)OSC_CLOCK_FREQ_24M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1);
            }
            switch(clk)
            {
                case SYSCTL_CLK_ROOT_PLL2:
                    return freq;
                case SYSCTL_CLK_ROOT_PLL2_DIV_2:
                    return freq/2;
                case SYSCTL_CLK_ROOT_PLL2_DIV_3:
                    return freq/3;
                default:
                    return freq/4;
            }
        }

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
        {
            if(true == sysctl_boot_get_root_clk_bypass(clk))
            {
                freq = OSC_CLOCK_FREQ_24M;
            }
            else
            {
                refdiv = (sysctl_boot->pll[3].cfg0 >> 16) & 0x3F;    /* bit 16~21 */
                outdiv = (sysctl_boot->pll[3].cfg0 >> 24) & 0xF;     /* bit 24~27 */
                fbdiv  = (sysctl_boot->pll[3].cfg0 >> 0)  & 0x1FFF;   /* bit 0~12 */
                freq = (double)OSC_CLOCK_FREQ_24M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1);
            }
            switch(clk)
            {
                case SYSCTL_CLK_ROOT_PLL3:
                    return freq;
                case SYSCTL_CLK_ROOT_PLL3_DIV_2:
                    return freq/2;
                case SYSCTL_CLK_ROOT_PLL3_DIV_3:
                    return freq/3;
                default:
                    return freq/4;
            }
        }

        default:
            return 0;
    }
}

/*
 * Set the frequency of the PLL.
 * Please configure the PLL frequency according to the above frequency division coefficient.
 * Note: when configuring, you can't configure yourself. For example, the PLL
 * attached to CPU can't stop before configuring the PLL of CPU, switch the
 * clock first and then configure it. After configuration, switch it back.
 */
bool sysctl_boot_set_root_clk_freq(sysctl_clk_node_e clk, uint32_t fbdiv, uint32_t refdiv, uint32_t outdiv, uint32_t bwadj)
{
    uint32_t id;
    uint32_t wait_us = 100;
    volatile uint32_t ret;

    if(SYSCTL_CLK_ROOT_PLL0 == clk)
        id = 0;
    else if(SYSCTL_CLK_ROOT_PLL1 == clk)
        id = 1;
    else if(SYSCTL_CLK_ROOT_PLL2 == clk)
        id = 2;
    else if(SYSCTL_CLK_ROOT_PLL3 == clk)
        id = 3;
    else
        return false;

    /*
     * According to the k230 TRM manual, the configuration steps of PLL are
     * as follows:
     * 1. Configure PLLx_CTL.pllx_pwrdwn=1，close PLL output；
     * 2. Configure PLL param PLLx_CFG0 and PLLx_CFG1;
     * 3. Configure PLLx_CTL.pllx_init，The hardware will wait for the PLL to
     *    automatically lock and turn on the PLL output.
     */

    /* 1. poweroff pll */
    (void)sysctl_boot_set_root_clk_pwroff(clk);

    /* 2. config divide */
    sysctl_boot->pll[id].cfg0 = ((fbdiv &  0x1FFF) << 0) | ((refdiv &  0x3F) << 16) | ((outdiv & 0xF) << 24);
    ret = sysctl_boot->pll[id].cfg1;
    ret &= 0xfffff000;
    sysctl_boot->pll[id].cfg1 = ret | ((bwadj & 0xfff) << 0);

    /* 3. init pll. init will pwrup pll */
    sysctl_boot->pll[id].ctl |= (1 << 1)|(1 << 17);

    /* 4. check lock status */
    while(1)
    {
        if(false == sysctl_boot_get_root_clk_lock(clk))
        {
            wait_us --;
            if(wait_us == 0)
                return false;
        }
        else
            return true;
    }
}


/*
 * API of trunk and leaf node
 */
bool sysctl_clk_set_leaf_parent(sysctl_clk_node_e leaf, sysctl_clk_node_e parent)
{
    volatile uint32_t ret;

    switch(sysctl_clk_attribute(leaf))
    {
        case 0:
        case 1:
            return false;
        case 3:
            break;
    }

    switch(leaf)
    {
        /*--------------------------- CPU0 CLOCK ------------------------------------*/
        case SYSCTL_CLK_CPU0_SRC:
        case SYSCTL_CLK_CPU0_PLIC:
        case SYSCTL_CLK_CPU0_ACLK:
        case SYSCTL_CLK_CPU0_NOC_DDRCP4:
            return false;       /* always pll0_div2 */
        case SYSCTL_CLK_CPU0_PCLK:
            return false;       /* always pll0_div4 */

        /*--------------------------- PMU CLOCK ------------------------------------*/
        case SYSCTL_CLK_PMU_PCLK:
            return false;       /* always osc24m */

        /*--------------------------- HS CLOCK ------------------------------------*/
        case SYSCTL_CLK_HS_HCLK_HIGH_SRC:
        case SYSCTL_CLK_HS_HCLK_HIGH_GATE:
        case SYSCTL_CLK_HS_HCLK_SRC:
        case SYSCTL_CLK_SD0_AHB_GATE:
        case SYSCTL_CLK_SD1_AHB_GATE:
        case SYSCTL_CLK_USB0_AHB_GATE:
        case SYSCTL_CLK_USB1_AHB_GATE:
        case SYSCTL_CLK_SSI1_AHB_GATE:
        case SYSCTL_CLK_SSI2_AHB_GATE:
            return false;       /* always pll0_div4 */

        case SYSCTL_CLK_SSI0_AXI:
        case SYSCTL_CLK_SSI1:
        case SYSCTL_CLK_SSI2:
        case SYSCTL_CLK_QSPI_AXI_SRC:
        case SYSCTL_CLK_SSI1_ACLK_GATE:
        case SYSCTL_CLK_SSI2_ACLK_GATE:
            return false;       /* always pll0_div4 */

        case SYSCTL_CLK_SSI0:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_2 == parent)
            {
                ret = sysctl_clk->hs_spi_cfg;
                ret &= 0xfffbffff;
                sysctl_clk->hs_spi_cfg = ret | (0 << 18);
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL2_DIV_4 == parent)
            {
                ret = sysctl_clk->hs_spi_cfg;
                ret &= 0xfffbffff;
                sysctl_clk->hs_spi_cfg = ret | (1 << 18);
                return true;
            }
            else
            {
                return false;
            }
        }

        case SYSCTL_CLK_SD_AXI_SRC:
        case SYSCTL_CLK_SD0_AXI_GATE:
        case SYSCTL_CLK_SD1_AXI_GATE:
        case SYSCTL_CLK_SD0_BASE_GATE:
        case SYSCTL_CLK_SD1_BASE_GATE:
            return false;

        case SYSCTL_CLK_SD_CARD_SRC:
        case SYSCTL_CLK_SD0_CARD_GATE:
        case SYSCTL_CLK_SD1_CARD_GATE:
            return false;

        case SYSCTL_CLK_PLL0_DIV16:
            return false;
        case SYSCTL_CLK_USB_REF_50M:
            return false;
        case SYSCTL_CLK_USB0_REF_GATE:
        case SYSCTL_CLK_USB1_REF_GATE:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN == parent)
            {
                ret = sysctl_clk->hs_clken_cfg;
                ret &= 0xff7fffff;
                sysctl_clk->hs_clken_cfg = ret | (0 << 23);
                return true;
            }
            else if(SYSCTL_CLK_USB_REF_50M == parent)
            {
                ret = sysctl_clk->hs_clken_cfg;
                ret &= 0xff7fffff;
                sysctl_clk->hs_clken_cfg = ret | (1 << 23);
                return true;
            }
            else
            {
                return false;
            }
        }

        case SYSCTL_CLK_SD_TIMER_SRC:
        case SYSCTL_CLK_SD0_TIMER_GATE:
        case SYSCTL_CLK_SD1_TIMER_GATE:
            return false;

        /*--------------------------- LS CLOCK ------------------------------------*/
        case SYSCTL_CLK_LS_APB_SRC:
        case SYSCTL_CLK_UART0_APB_GATE:
        case SYSCTL_CLK_UART1_APB_GATE:
        case SYSCTL_CLK_UART2_APB_GATE:
        case SYSCTL_CLK_UART3_APB_GATE:
        case SYSCTL_CLK_UART4_APB_GATE:
        case SYSCTL_CLK_I2C0_APB_GATE:
        case SYSCTL_CLK_I2C1_APB_GATE:
        case SYSCTL_CLK_I2C2_APB_GATE:
        case SYSCTL_CLK_I2C3_APB_GATE:
        case SYSCTL_CLK_I2C4_APB_GATE:
        case SYSCTL_CLK_GPIO_APB_GATE:
        case SYSCTL_CLK_PWM_APB_GATE:
        case SYSCTL_CLK_JAMLINK0_APB_GATE:
        case SYSCTL_CLK_JAMLINK1_APB_GATE:
        case SYSCTL_CLK_JAMLINK2_APB_GATE:
        case SYSCTL_CLK_JAMLINK3_APB_GATE:
        case SYSCTL_CLK_ADC_APB_GATE:
            return false;

        case SYSCTL_CLK_UART0_CORE:
        case SYSCTL_CLK_UART1_CORE:
        case SYSCTL_CLK_UART2_CORE:
        case SYSCTL_CLK_UART3_CORE:
        case SYSCTL_CLK_UART4_CORE:
            return false;

        case SYSCTL_CLK_JAMLINK_CO_DIV:
        case SYSCTL_CLK_JAMLINK0_CO_GATE:
        case SYSCTL_CLK_JAMLINK1_CO_GATE:
        case SYSCTL_CLK_JAMLINK2_CO_GATE:
        case SYSCTL_CLK_JAMLINK3_CO_GATE:
            return false;

        case SYSCTL_CLK_I2C0_CORE:
        case SYSCTL_CLK_I2C1_CORE:
        case SYSCTL_CLK_I2C2_CORE:
        case SYSCTL_CLK_I2C3_CORE:
        case SYSCTL_CLK_I2C4_CORE:
            return false;

        case SYSCTL_CLK_ADC:
            return false;

        case SYSCTL_CLK_GOIP_DEBOUNCE:
            return false;

        /*--------------------------- SYSCTL CLOCK ------------------------------------*/
        case SYSCTL_CLK_SYSCTRL_APB_SRC:
        case SYSCTL_CLK_WDT0_APB_GATE:
        case SYSCTL_CLK_WDT1_APB_GATE:
        case SYSCTL_CLK_TIMER_APB_GATE:
        case SYSCTL_CLK_IOMUX_APB_GATE:
        case SYSCTL_CLK_MAILBOX_APB_GATE:
            return false;

        case SYSCTL_CLK_HDI_CORE:
            return false;

        case SYSCTL_CLK_TIMESTAMP:
            return false;

        case SYSCTL_CLK_TEMP_SENSOR:
        case SYSCTL_CLK_WDT0:
        case SYSCTL_CLK_WDT1:
            return false;

        /*--------------------------- TIMER CLOCK ------------------------------------*/
        case SYSCTL_CLK_TIMERX_PULSE_IN:
            return false;
        case SYSCTL_CLK_TIMER0_SRC:
            return false;
        case SYSCTL_CLK_TIMER0:
        {
            if(SYSCTL_CLK_TIMER0_SRC == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xffffff7f;
                sysctl_clk->sysctl_clken_cfg = ret | (0 << 7);
                return true;
            }
            else if(SYSCTL_CLK_TIMERX_PULSE_IN == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xffffff7f;
                sysctl_clk->sysctl_clken_cfg = ret | (1 << 7);
                return true;
            }
            else
            {
                return false;
            }
        }

        case SYSCTL_CLK_TIMER1_SRC:
            return false;
        case SYSCTL_CLK_TIMER1:
        {
            if(SYSCTL_CLK_TIMER1_SRC == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xfffffeff;
                sysctl_clk->sysctl_clken_cfg = ret | (0 << 8);
                return true;
            }
            else if(SYSCTL_CLK_TIMERX_PULSE_IN == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xfffffeff;
                sysctl_clk->sysctl_clken_cfg = ret | (1 << 8);
                return true;
            }
            else
            {
                return false;
            }
        }

        case SYSCTL_CLK_TIMER2_SRC:
            return false;
        case SYSCTL_CLK_TIMER2:
        {
            if(SYSCTL_CLK_TIMER2_SRC == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xfffffdff;
                sysctl_clk->sysctl_clken_cfg = ret | (0 << 9);
                return true;
            }
            else if(SYSCTL_CLK_TIMERX_PULSE_IN == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xfffffdff;
                sysctl_clk->sysctl_clken_cfg = ret | (1 << 9);
                return true;
            }
            else
            {
                return false;
            }
        }

        case SYSCTL_CLK_TIMER3_SRC:
            return false;
        case SYSCTL_CLK_TIMER3:
        {
            if(SYSCTL_CLK_TIMER3_SRC == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xfffffbff;
                sysctl_clk->sysctl_clken_cfg = ret | (0 << 10);
                return true;
            }
            else if(SYSCTL_CLK_TIMERX_PULSE_IN == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xfffffbff;
                sysctl_clk->sysctl_clken_cfg = ret | (1 << 10);
                return true;
            }
            else
            {
                return false;
            }
        }

        case SYSCTL_CLK_TIMER4_SRC:
            return false;
        case SYSCTL_CLK_TIMER4:
        {
            if(SYSCTL_CLK_TIMER4_SRC == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xfffff7ff;
                sysctl_clk->sysctl_clken_cfg = ret | (0 << 11);
                return true;
            }
            else if(SYSCTL_CLK_TIMERX_PULSE_IN == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xfffff7ff;
                sysctl_clk->sysctl_clken_cfg = ret | (1 << 11);
                return true;
            }
            else
            {
                return false;
            }
        }

        case SYSCTL_CLK_TIMER5_SRC:
            return false;
        case SYSCTL_CLK_TIMER5:
        {
            if(SYSCTL_CLK_TIMER5_SRC == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xffffefff;
                sysctl_clk->sysctl_clken_cfg = ret | (0 << 12);
                return true;
            }
            else if(SYSCTL_CLK_TIMERX_PULSE_IN == parent)
            {
                ret = sysctl_clk->sysctl_clken_cfg;
                ret &= 0xffffefff;
                sysctl_clk->sysctl_clken_cfg = ret | (1 << 12);
                return true;
            }
            else
            {
                return false;
            }
        }

        /*--------------------------- SHRM CLOCK ------------------------------------*/
        case SYSCTL_CLK_SHRM_SRC:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_2 == parent)
            {
                ret = sysctl_clk->shrm_clk_cfg;
                ret &= 0xffffbfff;
                sysctl_clk->shrm_clk_cfg = ret | (0 << 14);
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL3_DIV_2 == parent)
            {
                ret = sysctl_clk->shrm_clk_cfg;
                ret &= 0xffffbfff;
                sysctl_clk->shrm_clk_cfg = ret | (1 << 14);
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_SHRM_DIV2:
        case SYSCTL_CLK_SHRM_AXIS_SLAVE:
        case SYSCTL_CLK_DECOMPRESS_AXI:
            return false;

        case SYSCTL_CLK_SHRM_APB:
            return false;

        case SYSCTL_CLK_SHRM_AXI_SRC:
        case SYSCTL_CLK_NONAI2D_AXI_GATE:
            return false;

        /*--------------------------- SEC CLOCK ------------------------------------*/
        case SYSCTL_CLK_SEC_APB:
        case SYSCTL_CLK_SEC_FIX:
            return false;

        case SYSCTL_CLK_SEC_AXI:
            return false;

        /*--------------------------- USB TEST MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_USB_480M:
        case SYSCTL_CLK_USB_100M:
            return false;

        /*--------------------------- DPHY DFT MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_DPHY_DFT_MODE:
            return false;

        /*--------------------------- SPI2AXI CLOCK ------------------------------------*/
        case SYSCTL_CLK_SPI2AXI_AXI:
            return false;

        default:
            return false;
    }
}

/*
 * Get the clock source of the leaf node on the clock tree, that is, read the
 * value of the register corresponding to MUX;
 * SYSCTL_CLK_ROOT_MAX is returned by default.
 */
sysctl_clk_node_e sysctl_clk_get_leaf_parent(sysctl_clk_node_e leaf)
{
    switch(sysctl_clk_attribute(leaf))
    {
        case 0:
            return SYSCTL_CLK_ROOT_MAX;
        case 1:
        case 3:
            break;
    }

    switch(leaf)
    {
        /*--------------------------- CPU0 CLOCK ------------------------------------*/
        case SYSCTL_CLK_CPU0_SRC:
            return SYSCTL_CLK_ROOT_PLL0_DIV_2;
        case SYSCTL_CLK_CPU0_PLIC:
        case SYSCTL_CLK_CPU0_ACLK:
            return SYSCTL_CLK_CPU0_SRC;
        case SYSCTL_CLK_CPU0_NOC_DDRCP4:
            return SYSCTL_CLK_CPU0_ACLK;
        case SYSCTL_CLK_CPU0_PCLK:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;

        /*--------------------------- PMU CLOCK ------------------------------------*/
        case SYSCTL_CLK_PMU_PCLK:
            return SYSCTL_CLK_ROOT_OSC_IN;

        /*--------------------------- HS CLOCK ------------------------------------*/
        case SYSCTL_CLK_HS_HCLK_HIGH_SRC:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        case SYSCTL_CLK_HS_HCLK_HIGH_GATE:
            return SYSCTL_CLK_HS_HCLK_HIGH_SRC;
        case SYSCTL_CLK_HS_HCLK_SRC:
            return SYSCTL_CLK_HS_HCLK_HIGH_SRC;
        case SYSCTL_CLK_SD0_AHB_GATE:
        case SYSCTL_CLK_SD1_AHB_GATE:
        case SYSCTL_CLK_USB0_AHB_GATE:
        case SYSCTL_CLK_USB1_AHB_GATE:
        case SYSCTL_CLK_SSI1_AHB_GATE:
        case SYSCTL_CLK_SSI2_AHB_GATE:
            return SYSCTL_CLK_HS_HCLK_SRC;

        case SYSCTL_CLK_SSI0_AXI:
        case SYSCTL_CLK_SSI1:
        case SYSCTL_CLK_SSI2:
        case SYSCTL_CLK_QSPI_AXI_SRC:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        case SYSCTL_CLK_SSI1_ACLK_GATE:
        case SYSCTL_CLK_SSI2_ACLK_GATE:
            return SYSCTL_CLK_QSPI_AXI_SRC;

        case SYSCTL_CLK_SSI0:
        {
            if(0 == ((sysctl_clk->hs_spi_cfg >> 18) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_2;
            else
                return SYSCTL_CLK_ROOT_PLL2_DIV_4;
        }

        case SYSCTL_CLK_SD_AXI_SRC:
            return SYSCTL_CLK_ROOT_PLL2_DIV_4;
        case SYSCTL_CLK_SD0_AXI_GATE:
        case SYSCTL_CLK_SD1_AXI_GATE:
        case SYSCTL_CLK_SD0_BASE_GATE:
        case SYSCTL_CLK_SD1_BASE_GATE:
            return SYSCTL_CLK_SD_AXI_SRC;

        case SYSCTL_CLK_SD_CARD_SRC:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        case SYSCTL_CLK_SD0_CARD_GATE:
        case SYSCTL_CLK_SD1_CARD_GATE:
            return SYSCTL_CLK_SD_CARD_SRC;

        case SYSCTL_CLK_PLL0_DIV16:
            return SYSCTL_CLK_ROOT_PLL0;
        case SYSCTL_CLK_USB_REF_50M:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_USB0_REF_GATE:
        case SYSCTL_CLK_USB1_REF_GATE:
        {
            if(0 == ((sysctl_clk->hs_clken_cfg >> 23) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN;
            else
                return SYSCTL_CLK_USB_REF_50M;
        }

        case SYSCTL_CLK_SD_TIMER_SRC:
            return SYSCTL_CLK_ROOT_OSC_IN;
        case SYSCTL_CLK_SD0_TIMER_GATE:
        case SYSCTL_CLK_SD1_TIMER_GATE:
            return SYSCTL_CLK_SD_TIMER_SRC;

        /*--------------------------- LS CLOCK ------------------------------------*/
        case SYSCTL_CLK_LS_APB_SRC:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        case SYSCTL_CLK_UART0_APB_GATE:
        case SYSCTL_CLK_UART1_APB_GATE:
        case SYSCTL_CLK_UART2_APB_GATE:
        case SYSCTL_CLK_UART3_APB_GATE:
        case SYSCTL_CLK_UART4_APB_GATE:
        case SYSCTL_CLK_I2C0_APB_GATE:
        case SYSCTL_CLK_I2C1_APB_GATE:
        case SYSCTL_CLK_I2C2_APB_GATE:
        case SYSCTL_CLK_I2C3_APB_GATE:
        case SYSCTL_CLK_I2C4_APB_GATE:
        case SYSCTL_CLK_GPIO_APB_GATE:
        case SYSCTL_CLK_PWM_APB_GATE:
        case SYSCTL_CLK_JAMLINK0_APB_GATE:
        case SYSCTL_CLK_JAMLINK1_APB_GATE:
        case SYSCTL_CLK_JAMLINK2_APB_GATE:
        case SYSCTL_CLK_JAMLINK3_APB_GATE:
        case SYSCTL_CLK_ADC_APB_GATE:
            return SYSCTL_CLK_LS_APB_SRC;

        case SYSCTL_CLK_UART0_CORE:
        case SYSCTL_CLK_UART1_CORE:
        case SYSCTL_CLK_UART2_CORE:
        case SYSCTL_CLK_UART3_CORE:
        case SYSCTL_CLK_UART4_CORE:
            return SYSCTL_CLK_PLL0_DIV16;

        case SYSCTL_CLK_JAMLINK_CO_DIV:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_JAMLINK0_CO_GATE:
        case SYSCTL_CLK_JAMLINK1_CO_GATE:
        case SYSCTL_CLK_JAMLINK2_CO_GATE:
        case SYSCTL_CLK_JAMLINK3_CO_GATE:
            return SYSCTL_CLK_JAMLINK_CO_DIV;

        case SYSCTL_CLK_I2C0_CORE:
        case SYSCTL_CLK_I2C1_CORE:
        case SYSCTL_CLK_I2C2_CORE:
        case SYSCTL_CLK_I2C3_CORE:
        case SYSCTL_CLK_I2C4_CORE:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;

        case SYSCTL_CLK_ADC:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;

        case SYSCTL_CLK_GOIP_DEBOUNCE:
            return SYSCTL_CLK_ROOT_OSC_IN;

        /*--------------------------- SYSCTL CLOCK ------------------------------------*/
        case SYSCTL_CLK_SYSCTRL_APB_SRC:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_WDT0_APB_GATE:
        case SYSCTL_CLK_WDT1_APB_GATE:
        case SYSCTL_CLK_TIMER_APB_GATE:
        case SYSCTL_CLK_IOMUX_APB_GATE:
        case SYSCTL_CLK_MAILBOX_APB_GATE:
            return SYSCTL_CLK_SYSCTRL_APB_SRC;

        case SYSCTL_CLK_HDI_CORE:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;

        case SYSCTL_CLK_TIMESTAMP:
            return SYSCTL_CLK_ROOT_PLL1_DIV_4;

        case SYSCTL_CLK_TEMP_SENSOR:
        case SYSCTL_CLK_WDT0:
        case SYSCTL_CLK_WDT1:
            return SYSCTL_CLK_ROOT_OSC_IN;

        /*--------------------------- TIMER CLOCK ------------------------------------*/
        case SYSCTL_CLK_TIMERX_PULSE_IN:
            return SYSCTL_CLK_ROOT_TIMERX_PULSE_IN;     /* 注意，此处需要review。因为pulse是外部输入信号，这里如何定义其父时钟？ */
        case SYSCTL_CLK_TIMER0_SRC:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_TIMER0:
        {
            if(0 == ((sysctl_clk->sysctl_clken_cfg >> 7) & 0x1))
                return SYSCTL_CLK_TIMER0_SRC;
            else
                return SYSCTL_CLK_TIMERX_PULSE_IN;
        }
        case SYSCTL_CLK_TIMER1_SRC:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_TIMER1:
        {
            if(0 == ((sysctl_clk->sysctl_clken_cfg >> 8) & 0x1))
                return SYSCTL_CLK_TIMER1_SRC;
            else
                return SYSCTL_CLK_TIMERX_PULSE_IN;
        }
        case SYSCTL_CLK_TIMER2_SRC:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_TIMER2:
        {
            if(0 == ((sysctl_clk->sysctl_clken_cfg >> 9) & 0x1))
                return SYSCTL_CLK_TIMER2_SRC;
            else
                return SYSCTL_CLK_TIMERX_PULSE_IN;
        }
        case SYSCTL_CLK_TIMER3_SRC:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_TIMER3:
        {
            if(0 == ((sysctl_clk->sysctl_clken_cfg >> 10) & 0x1))
                return SYSCTL_CLK_TIMER3_SRC;
            else
                return SYSCTL_CLK_TIMERX_PULSE_IN;
        }
        case SYSCTL_CLK_TIMER4_SRC:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_TIMER4:
        {
            if(0 == ((sysctl_clk->sysctl_clken_cfg >> 11) & 0x1))
                return SYSCTL_CLK_TIMER4_SRC;
            else
                return SYSCTL_CLK_TIMERX_PULSE_IN;
        }
        case SYSCTL_CLK_TIMER5_SRC:
            return SYSCTL_CLK_PLL0_DIV16;
        case SYSCTL_CLK_TIMER5:
        {
            if(0 == ((sysctl_clk->sysctl_clken_cfg >> 12) & 0x1))
                return SYSCTL_CLK_TIMER5_SRC;
            else
                return SYSCTL_CLK_TIMERX_PULSE_IN;
        }

        /*--------------------------- SHRM CLOCK ------------------------------------*/
        case SYSCTL_CLK_SHRM_SRC:
        {
            if(0 == ((sysctl_clk->shrm_clk_cfg >> 14) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_2;
            else
                return SYSCTL_CLK_ROOT_PLL3_DIV_2;
        }
        case SYSCTL_CLK_SHRM_DIV2:
            return SYSCTL_CLK_SHRM_SRC;
        case SYSCTL_CLK_SHRM_AXIS_SLAVE:
            return SYSCTL_CLK_SHRM_DIV2;
        case SYSCTL_CLK_DECOMPRESS_AXI:
            return SYSCTL_CLK_SHRM_SRC;

        case SYSCTL_CLK_SHRM_APB:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;

        case SYSCTL_CLK_SHRM_AXI_SRC:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        case SYSCTL_CLK_NONAI2D_AXI_GATE:
            return SYSCTL_CLK_SHRM_AXI_SRC;

        /*--------------------------- SEC CLOCK ------------------------------------*/
        case SYSCTL_CLK_SEC_APB:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;

        case SYSCTL_CLK_SEC_FIX:
        case SYSCTL_CLK_SEC_AXI:
            return SYSCTL_CLK_ROOT_PLL1_DIV_4;

        /*--------------------------- USB TEST MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_USB_480M:
            return SYSCTL_CLK_ROOT_PLL1;
        case SYSCTL_CLK_USB_100M:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;

        /*--------------------------- DPHY DFT MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_DPHY_DFT_MODE:
            return SYSCTL_CLK_ROOT_PLL0;

        /*--------------------------- SPI2AXI CLOCK ------------------------------------*/
        case SYSCTL_CLK_SPI2AXI_AXI:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;

        default:
            return SYSCTL_CLK_ROOT_MAX;
    }
}

/*
 * Set the clock node enable.
 * Note: only set the enable of this clock node, and do not set the enable of
 * the upstream clock.
 */
void sysctl_clk_set_leaf_en(sysctl_clk_node_e leaf, bool enable)
{
    volatile uint32_t ret;
    switch(sysctl_clk_attribute(leaf))
    {
        case 0:
        case 1:
            return;
        case 3:
            break;
    }

    switch(leaf)
    {
        /*--------------------------- CPU0 CLOCK ------------------------------------*/
        case SYSCTL_CLK_CPU0_SRC:
            if(enable == true)
                sysctl_clk->cpu0_clk_cfg |= (1 << 0);
            else
                sysctl_clk->cpu0_clk_cfg &= ~(1 << 0);
            break;
        case SYSCTL_CLK_CPU0_PLIC:
            if(enable == true)
                sysctl_clk->cpu0_clk_cfg |= (1 << 9);
            else
                sysctl_clk->cpu0_clk_cfg &= ~(1 << 9);
            break;
        case SYSCTL_CLK_CPU0_ACLK:
            break;
        case SYSCTL_CLK_CPU0_NOC_DDRCP4:
            if(enable == true)
                sysctl_clk->ddr_clk_cfg |= (1 << 7);
            else
                sysctl_clk->ddr_clk_cfg &= ~(1 << 7);
            break;
        case SYSCTL_CLK_CPU0_PCLK:
            if(enable == true)
                sysctl_clk->cpu0_clk_cfg |= (1 << 13);
            else
                sysctl_clk->cpu0_clk_cfg &= ~(1 << 13);
            break;

        /*--------------------------- PMU CLOCK ------------------------------------*/
        case SYSCTL_CLK_PMU_PCLK:
            if(enable == true)
                sysctl_clk->pmu_clk_cfg |= (1 << 0);
            else
                sysctl_clk->pmu_clk_cfg &= ~(1 << 0);
            break;

        /*--------------------------- HS CLOCK ------------------------------------*/
        case SYSCTL_CLK_HS_HCLK_HIGH_SRC:
            break;
        case SYSCTL_CLK_HS_HCLK_HIGH_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 1);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 1);
            break;

        case SYSCTL_CLK_HS_HCLK_SRC:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 0);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 0);
            break;

        case SYSCTL_CLK_SD0_AHB_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 2);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 2);
            break;

        case SYSCTL_CLK_SD1_AHB_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 3);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 3);
            break;

        case SYSCTL_CLK_USB0_AHB_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 4);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 4);
            break;

        case SYSCTL_CLK_USB1_AHB_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 5);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 5);
            break;

        case SYSCTL_CLK_SSI1_AHB_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 7);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 7);
            break;

        case SYSCTL_CLK_SSI2_AHB_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 8);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 8);
            break;

        case SYSCTL_CLK_SSI0_AXI:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 27);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 27);
            break;

        case SYSCTL_CLK_SSI1:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 25);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 25);
            break;

        case SYSCTL_CLK_SSI2:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 26);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 26);
            break;

        case SYSCTL_CLK_QSPI_AXI_SRC:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 28);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 28);
            break;

        case SYSCTL_CLK_SSI1_ACLK_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 29);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 29);
            break;

        case SYSCTL_CLK_SSI2_ACLK_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 30);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 30);
            break;

        case SYSCTL_CLK_SSI0:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 24);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 24);
            break;

        case SYSCTL_CLK_SD_AXI_SRC:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 9);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 9);
            break;

        case SYSCTL_CLK_SD0_AXI_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 13);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 13);
            break;

        case SYSCTL_CLK_SD1_AXI_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 17);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 17);
            break;

        case SYSCTL_CLK_SD0_BASE_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 14);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 14);
            break;

        case SYSCTL_CLK_SD1_BASE_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 18);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 18);
            break;

        case SYSCTL_CLK_SD_CARD_SRC:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 11);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 11);
            break;

        case SYSCTL_CLK_SD0_CARD_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 15);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 15);
            break;

        case SYSCTL_CLK_SD1_CARD_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 19);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 19);
            break;

        case SYSCTL_CLK_PLL0_DIV16:
            break;
        case SYSCTL_CLK_USB_REF_50M:
            break;

        case SYSCTL_CLK_USB0_REF_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 21);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 21);
            break;

        case SYSCTL_CLK_USB1_REF_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 22);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 22);
            break;

        case SYSCTL_CLK_SD_TIMER_SRC:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 12);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 12);
            break;

        case SYSCTL_CLK_SD0_TIMER_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 16);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 16);
            break;

        case SYSCTL_CLK_SD1_TIMER_GATE:
            if(enable == true)
                sysctl_clk->hs_clken_cfg |= (1 << 20);
            else
                sysctl_clk->hs_clken_cfg &= ~(1 << 20);
            break;

        /*--------------------------- LS CLOCK ------------------------------------*/
        case SYSCTL_CLK_LS_APB_SRC:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 0);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 0);
            break;

        case SYSCTL_CLK_UART0_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 1);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 1);
            break;

        case SYSCTL_CLK_UART1_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 2);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 2);
            break;

        case SYSCTL_CLK_UART2_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 3);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 3);
            break;

        case SYSCTL_CLK_UART3_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 4);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 4);
            break;

        case SYSCTL_CLK_UART4_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 5);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 5);
            break;

        case SYSCTL_CLK_I2C0_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 6);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 6);
            break;

        case SYSCTL_CLK_I2C1_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 7);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 7);
            break;

        case SYSCTL_CLK_I2C2_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 8);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 8);
            break;

        case SYSCTL_CLK_I2C3_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 9);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 9);
            break;

        case SYSCTL_CLK_I2C4_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 10);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 10);
            break;

        case SYSCTL_CLK_GPIO_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 11);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 11);
            break;

        case SYSCTL_CLK_PWM_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 12);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 12);
            break;

        case SYSCTL_CLK_JAMLINK0_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg1 |= (1 << 4);
            else
                sysctl_clk->ls_clken_cfg1 &= ~(1 << 4);
            break;

        case SYSCTL_CLK_JAMLINK1_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg1 |= (1 << 5);
            else
                sysctl_clk->ls_clken_cfg1 &= ~(1 << 5);
            break;

        case SYSCTL_CLK_JAMLINK2_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg1 |= (1 << 6);
            else
                sysctl_clk->ls_clken_cfg1 &= ~(1 << 6);
            break;

        case SYSCTL_CLK_JAMLINK3_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg1 |= (1 << 7);
            else
                sysctl_clk->ls_clken_cfg1 &= ~(1 << 7);
            break;

        case SYSCTL_CLK_ADC_APB_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 15);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 15);
            break;

        case SYSCTL_CLK_UART0_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 16);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 16);
            break;

        case SYSCTL_CLK_UART1_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 17);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 17);
            break;

        case SYSCTL_CLK_UART2_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 18);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 18);
            break;

        case SYSCTL_CLK_UART3_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 19);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 19);
            break;

        case SYSCTL_CLK_UART4_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 20);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 20);
            break;

        case SYSCTL_CLK_JAMLINK_CO_DIV:
            break;
        case SYSCTL_CLK_JAMLINK0_CO_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg1 |= (1 << 0);
            else
                sysctl_clk->ls_clken_cfg1 &= ~(1 << 0);
            break;

        case SYSCTL_CLK_JAMLINK1_CO_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg1 |= (1 << 1);
            else
                sysctl_clk->ls_clken_cfg1 &= ~(1 << 1);
            break;

        case SYSCTL_CLK_JAMLINK2_CO_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg1 |= (1 << 2);
            else
                sysctl_clk->ls_clken_cfg1 &= ~(1 << 2);
            break;

        case SYSCTL_CLK_JAMLINK3_CO_GATE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg1 |= (1 << 3);
            else
                sysctl_clk->ls_clken_cfg1 &= ~(1 << 3);
            break;

        case SYSCTL_CLK_I2C0_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 21);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 21);
            break;

        case SYSCTL_CLK_I2C1_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 22);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 22);
            break;

        case SYSCTL_CLK_I2C2_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 23);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 23);
            break;

        case SYSCTL_CLK_I2C3_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 24);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 24);
            break;

        case SYSCTL_CLK_I2C4_CORE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 25);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 25);
            break;

        case SYSCTL_CLK_ADC:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 26);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 26);
            break;

        case SYSCTL_CLK_GOIP_DEBOUNCE:
            if(enable == true)
                sysctl_clk->ls_clken_cfg0 |= (1 << 27);
            else
                sysctl_clk->ls_clken_cfg0 &= ~(1 << 27);
            break;

        /*--------------------------- SYSCTL CLOCK ------------------------------------*/
        case SYSCTL_CLK_SYSCTRL_APB_SRC:
            break;
        case SYSCTL_CLK_WDT0_APB_GATE:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 1);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 1);
            break;

        case SYSCTL_CLK_WDT1_APB_GATE:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 2);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 2);
            break;

        case SYSCTL_CLK_TIMER_APB_GATE:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 3);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 3);
            break;

        case SYSCTL_CLK_IOMUX_APB_GATE:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 20);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 20);
            break;

        case SYSCTL_CLK_MAILBOX_APB_GATE:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 4);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 4);
            break;

        case SYSCTL_CLK_HDI_CORE:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 21);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 21);
            break;

        case SYSCTL_CLK_TIMESTAMP:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 19);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 19);
            break;

        case SYSCTL_CLK_TEMP_SENSOR:
            break;

        case SYSCTL_CLK_WDT0:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 5);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 5);

        case SYSCTL_CLK_WDT1:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 6);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 6);

        /*--------------------------- TIMER CLOCK ------------------------------------*/
        case SYSCTL_CLK_TIMERX_PULSE_IN:
            break;
        case SYSCTL_CLK_TIMER0_SRC:
            break;
        case SYSCTL_CLK_TIMER0:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 13);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 13);
            break;

        case SYSCTL_CLK_TIMER1_SRC:
            break;
        case SYSCTL_CLK_TIMER1:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 14);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 14);
            break;

        case SYSCTL_CLK_TIMER2_SRC:
            break;
        case SYSCTL_CLK_TIMER2:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 15);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 15);
            break;

        case SYSCTL_CLK_TIMER3_SRC:
            break;
        case SYSCTL_CLK_TIMER3:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 16);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 16);
            break;

        case SYSCTL_CLK_TIMER4_SRC:
            break;
        case SYSCTL_CLK_TIMER4:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 17);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 17);
            break;

        case SYSCTL_CLK_TIMER5_SRC:
            break;
        case SYSCTL_CLK_TIMER5:
            if(enable == true)
                sysctl_clk->sysctl_clken_cfg |= (1 << 18);
            else
                sysctl_clk->sysctl_clken_cfg &= ~(1 << 18);
            break;

        /*--------------------------- SHRM CLOCK ------------------------------------*/
        case SYSCTL_CLK_SHRM_SRC:
            if(enable == true)
                sysctl_clk->shrm_clk_cfg |= (1 << 10);
            else
                sysctl_clk->shrm_clk_cfg &= ~(1 << 10);
            break;

        case SYSCTL_CLK_SHRM_DIV2:
            break;
        case SYSCTL_CLK_SHRM_AXIS_SLAVE:
            if(enable == true)
                sysctl_clk->shrm_clk_cfg |= (1 << 11);
            else
                sysctl_clk->shrm_clk_cfg &= ~(1 << 11);
            break;

        case SYSCTL_CLK_DECOMPRESS_AXI:
            if(enable == true)
                sysctl_clk->shrm_clk_cfg |= (1 << 7);
            else
                sysctl_clk->shrm_clk_cfg &= ~(1 << 7);
            break;

        case SYSCTL_CLK_SHRM_APB:
            if(enable == true)
                sysctl_clk->shrm_clk_cfg |= (1 << 0);
            else
                sysctl_clk->shrm_clk_cfg &= ~(1 << 0);
            break;

        case SYSCTL_CLK_SHRM_AXI_SRC:
            if(enable == true)
                sysctl_clk->shrm_clk_cfg |= (1 << 12);
            else
                sysctl_clk->shrm_clk_cfg &= ~(1 << 12);
            break;

        case SYSCTL_CLK_NONAI2D_AXI_GATE:
            if(enable == true)
                sysctl_clk->shrm_clk_cfg |= (1 << 9);
            else
                sysctl_clk->shrm_clk_cfg &= ~(1 << 9);
            break;

        /*--------------------------- SEC CLOCK ------------------------------------*/
        case SYSCTL_CLK_SEC_APB:
            if(enable == true)
                sysctl_clk->sec_clk_div |= (1 << 0);
            else
                sysctl_clk->sec_clk_div &= ~(1 << 0);
            break;

        case SYSCTL_CLK_SEC_FIX:
            if(enable == true)
                sysctl_clk->sec_clk_div |= (1 << 5);
            else
                sysctl_clk->sec_clk_div &= ~(1 << 5);
            break;

        case SYSCTL_CLK_SEC_AXI:
            if(enable == true)
                sysctl_clk->sec_clk_div |= (1 << 4);
            else
                sysctl_clk->sec_clk_div &= ~(1 << 4);
            break;

        /*--------------------------- USB TEST MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_USB_480M:
            if(enable == true)
                sysctl_clk->usb_test_clk_div |= (1 << 0);
            else
                sysctl_clk->usb_test_clk_div &= ~(1 << 0);
            break;

        case SYSCTL_CLK_USB_100M:
            if(enable == true)
                sysctl_clk->usb_test_clk_div |= (1 << 0);
            else
                sysctl_clk->usb_test_clk_div &= ~(1 << 0);
            break;

        /*--------------------------- DPHY DFT MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_DPHY_DFT_MODE:
            if(enable == true)
                sysctl_clk->dphy_test_clk_div |= (1 << 0);
            else
                sysctl_clk->dphy_test_clk_div &= ~(1 << 0);
            break;

        /*--------------------------- SPI2AXI CLOCK ------------------------------------*/
        case SYSCTL_CLK_SPI2AXI_AXI:
            if(enable == true)
                sysctl_clk->spi2axi_clk_div |= (1 << 0);
            else
                sysctl_clk->spi2axi_clk_div &= ~(1 << 0);
            break;

        default:
            break;
    }
}

/* Get the enable status of this clock node */
bool sysctl_clk_get_leaf_en(sysctl_clk_node_e leaf)
{
    switch(sysctl_clk_attribute(leaf))
    {
        case 0:
            return false;
        case 1:
        case 3:
            break;
    }

    switch(leaf)
    {
        /*--------------------------- CPU0 CLOCK ------------------------------------*/
        case SYSCTL_CLK_CPU0_SRC:
            return (0 == ((sysctl_clk->cpu0_clk_cfg >> 0) & 0x1)) ? false : true;
        case SYSCTL_CLK_CPU0_PLIC:
            return (0 == ((sysctl_clk->cpu0_clk_cfg >> 9) & 0x1)) ? false : true;
        case SYSCTL_CLK_CPU0_ACLK:
            return true;
        case SYSCTL_CLK_CPU0_NOC_DDRCP4:
            return (0 == ((sysctl_clk->ddr_clk_cfg >> 7) & 0x1)) ? false : true;
        case SYSCTL_CLK_CPU0_PCLK:
            return (0 == ((sysctl_clk->cpu0_clk_cfg >> 7) & 0x1)) ? false : true;

        /*--------------------------- PMU CLOCK ------------------------------------*/
        case SYSCTL_CLK_PMU_PCLK:
            return (0 == ((sysctl_clk->pmu_clk_cfg >> 0) & 0x1)) ? false : true;

        /*--------------------------- HS CLOCK ------------------------------------*/
        case SYSCTL_CLK_HS_HCLK_HIGH_SRC:
            return true;
        case SYSCTL_CLK_HS_HCLK_HIGH_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 1) & 0x1)) ? false : true;
        case SYSCTL_CLK_HS_HCLK_SRC:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 0) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD0_AHB_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 2) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD1_AHB_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 3) & 0x1)) ? false : true;
        case SYSCTL_CLK_USB0_AHB_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 4) & 0x1)) ? false : true;
        case SYSCTL_CLK_USB1_AHB_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 5) & 0x1)) ? false : true;
        case SYSCTL_CLK_SSI1_AHB_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 7) & 0x1)) ? false : true;
        case SYSCTL_CLK_SSI2_AHB_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 8) & 0x1)) ? false : true;

        case SYSCTL_CLK_SSI0_AXI:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 27) & 0x1)) ? false : true;
        case SYSCTL_CLK_SSI1:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 25) & 0x1)) ? false : true;
        case SYSCTL_CLK_SSI2:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 26) & 0x1)) ? false : true;
        case SYSCTL_CLK_QSPI_AXI_SRC:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 28) & 0x1)) ? false : true;
        case SYSCTL_CLK_SSI1_ACLK_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 29) & 0x1)) ? false : true;
        case SYSCTL_CLK_SSI2_ACLK_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 30) & 0x1)) ? false : true;

        case SYSCTL_CLK_SSI0:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 24) & 0x1)) ? false : true;

        case SYSCTL_CLK_SD_AXI_SRC:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 9) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD0_AXI_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 13) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD1_AXI_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 17) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD0_BASE_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 14) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD1_BASE_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 18) & 0x1)) ? false : true;

        case SYSCTL_CLK_SD_CARD_SRC:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 11) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD0_CARD_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 15) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD1_CARD_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 19) & 0x1)) ? false : true;

        case SYSCTL_CLK_PLL0_DIV16:
            return true;
        case SYSCTL_CLK_USB_REF_50M:
            return true;
        case SYSCTL_CLK_USB0_REF_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 21) & 0x1)) ? false : true;
        case SYSCTL_CLK_USB1_REF_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 22) & 0x1)) ? false : true;

        case SYSCTL_CLK_SD_TIMER_SRC:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 12) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD0_TIMER_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 16) & 0x1)) ? false : true;
        case SYSCTL_CLK_SD1_TIMER_GATE:
            return (0 == ((sysctl_clk->hs_clken_cfg >> 20) & 0x1)) ? false : true;


        /*--------------------------- LS CLOCK ------------------------------------*/
        case SYSCTL_CLK_LS_APB_SRC:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 0) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART0_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 1) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART1_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 2) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART2_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 3) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART3_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 4) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART4_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 5) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C0_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 6) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C1_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 7) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C2_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 8) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C3_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 9) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C4_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 10) & 0x1)) ? false : true;
        case SYSCTL_CLK_GPIO_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 11) & 0x1)) ? false : true;
        case SYSCTL_CLK_PWM_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 12) & 0x1)) ? false : true;
        case SYSCTL_CLK_JAMLINK0_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg1 >> 4) & 0x1)) ? false : true;
        case SYSCTL_CLK_JAMLINK1_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg1 >> 5) & 0x1)) ? false : true;
        case SYSCTL_CLK_JAMLINK2_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg1 >> 6) & 0x1)) ? false : true;
        case SYSCTL_CLK_JAMLINK3_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg1 >> 7) & 0x1)) ? false : true;
        case SYSCTL_CLK_ADC_APB_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 15) & 0x1)) ? false : true;

        case SYSCTL_CLK_UART0_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 16) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART1_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 17) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART2_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 18) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART3_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 19) & 0x1)) ? false : true;
        case SYSCTL_CLK_UART4_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 20) & 0x1)) ? false : true;

        case SYSCTL_CLK_JAMLINK_CO_DIV:
            return true;
        case SYSCTL_CLK_JAMLINK0_CO_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg1 >> 0) & 0x1)) ? false : true;
        case SYSCTL_CLK_JAMLINK1_CO_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg1 >> 1) & 0x1)) ? false : true;
        case SYSCTL_CLK_JAMLINK2_CO_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg1 >> 2) & 0x1)) ? false : true;
        case SYSCTL_CLK_JAMLINK3_CO_GATE:
            return (0 == ((sysctl_clk->ls_clken_cfg1 >> 3) & 0x1)) ? false : true;

        case SYSCTL_CLK_I2C0_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 21) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C1_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 22) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C2_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 23) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C3_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 24) & 0x1)) ? false : true;
        case SYSCTL_CLK_I2C4_CORE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 25) & 0x1)) ? false : true;

        case SYSCTL_CLK_ADC:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 26) & 0x1)) ? false : true;

        case SYSCTL_CLK_GOIP_DEBOUNCE:
            return (0 == ((sysctl_clk->ls_clken_cfg0 >> 27) & 0x1)) ? false : true;

        /*--------------------------- SYSCTL CLOCK ------------------------------------*/
        case SYSCTL_CLK_SYSCTRL_APB_SRC:
            return true;
        case SYSCTL_CLK_WDT0_APB_GATE:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 1) & 0x1)) ? false : true;
        case SYSCTL_CLK_WDT1_APB_GATE:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 2) & 0x1)) ? false : true;
        case SYSCTL_CLK_TIMER_APB_GATE:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 3) & 0x1)) ? false : true;
        case SYSCTL_CLK_IOMUX_APB_GATE:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 20) & 0x1)) ? false : true;
        case SYSCTL_CLK_MAILBOX_APB_GATE:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 4) & 0x1)) ? false : true;

        case SYSCTL_CLK_HDI_CORE:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 21) & 0x1)) ? false : true;

        case SYSCTL_CLK_TIMESTAMP:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 19) & 0x1)) ? false : true;

        case SYSCTL_CLK_TEMP_SENSOR:
            return true;

        case SYSCTL_CLK_WDT0:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 5) & 0x1)) ? false : true;
        case SYSCTL_CLK_WDT1:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 6) & 0x1)) ? false : true;

        /*--------------------------- TIMER CLOCK ------------------------------------*/
        case SYSCTL_CLK_TIMERX_PULSE_IN:
            return true;
        case SYSCTL_CLK_TIMER0_SRC:
            return true;
        case SYSCTL_CLK_TIMER0:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 13) & 0x1)) ? false : true;
        case SYSCTL_CLK_TIMER1_SRC:
            return true;
        case SYSCTL_CLK_TIMER1:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 14) & 0x1)) ? false : true;
        case SYSCTL_CLK_TIMER2_SRC:
            return true;
        case SYSCTL_CLK_TIMER2:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 15) & 0x1)) ? false : true;
        case SYSCTL_CLK_TIMER3_SRC:
            return true;
        case SYSCTL_CLK_TIMER3:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 16) & 0x1)) ? false : true;
        case SYSCTL_CLK_TIMER4_SRC:
            return true;
        case SYSCTL_CLK_TIMER4:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 17) & 0x1)) ? false : true;
        case SYSCTL_CLK_TIMER5_SRC:
            return true;
        case SYSCTL_CLK_TIMER5:
            return (0 == ((sysctl_clk->sysctl_clken_cfg >> 18) & 0x1)) ? false : true;

        /*--------------------------- SHRM CLOCK ------------------------------------*/
        case SYSCTL_CLK_SHRM_SRC:
            return (0 == ((sysctl_clk->shrm_clk_cfg >> 10) & 0x1)) ? false : true;
        case SYSCTL_CLK_SHRM_DIV2:
            return true;
        case SYSCTL_CLK_SHRM_AXIS_SLAVE:
            return (0 == ((sysctl_clk->shrm_clk_cfg >> 11) & 0x1)) ? false : true;
        case SYSCTL_CLK_DECOMPRESS_AXI:
            return (0 == ((sysctl_clk->shrm_clk_cfg >> 7) & 0x1)) ? false : true;

        case SYSCTL_CLK_SHRM_APB:
            return (0 == ((sysctl_clk->shrm_clk_cfg >> 0) & 0x1)) ? false : true;

        case SYSCTL_CLK_SHRM_AXI_SRC:
            return (0 == ((sysctl_clk->shrm_clk_cfg >> 12) & 0x1)) ? false : true;

        /*--------------------------- SEC CLOCK ------------------------------------*/
        case SYSCTL_CLK_SEC_APB:
            return (0 == ((sysctl_clk->sec_clk_div >> 0) & 0x1)) ? false : true;
        case SYSCTL_CLK_SEC_FIX:
            return (0 == ((sysctl_clk->sec_clk_div >> 5) & 0x1)) ? false : true;

        case SYSCTL_CLK_SEC_AXI:
            return (0 == ((sysctl_clk->sec_clk_div >> 4) & 0x1)) ? false : true;

        /*--------------------------- USB TEST MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_USB_480M:
            return (0 == ((sysctl_clk->usb_test_clk_div >> 0) & 0x1)) ? false : true;
        case SYSCTL_CLK_USB_100M:
            return (0 == ((sysctl_clk->usb_test_clk_div >> 0) & 0x1)) ? false : true;

        /*--------------------------- DPHY DFT MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_DPHY_DFT_MODE:
            return (0 == ((sysctl_clk->dphy_test_clk_div >> 0) & 0x1)) ? false : true;

        /*--------------------------- SPI2AXI CLOCK ------------------------------------*/
        case SYSCTL_CLK_SPI2AXI_AXI:
            return (0 == ((sysctl_clk->spi2axi_clk_div >> 0) & 0x1)) ? false : true;

        default:
            return true;
    }
}

/*
 * Set the frequency division factor of this clock node.
 * freq = root_freq * numerator / denominator
 */
bool sysctl_clk_set_leaf_div(sysctl_clk_node_e leaf, uint32_t numerator, uint32_t denominator)
{
    volatile uint32_t ret;

    if(denominator == 0)
        return false;

    switch(sysctl_clk_attribute(leaf))
    {
        case 0:
        case 1:
            return false;
        case 3:
            break;
    }

    switch(leaf)
    {
        /*--------------------------- CPU0 CLOCK ------------------------------------*/
        case SYSCTL_CLK_CPU0_SRC:
        {
            if((numerator > 16) || (numerator < 1) || (denominator != 16))
                return false;
            else
            {
                /* 1/16 --- 16/16 */
                ret = sysctl_clk->cpu0_clk_cfg;
                ret &= 0xffffffe1;
                sysctl_clk->cpu0_clk_cfg = ret | (((numerator - 1) << 1) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_CPU0_PLIC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->cpu0_clk_cfg;
                ret &= 0xffffe3ff;
                sysctl_clk->cpu0_clk_cfg = ret | (((denominator - 1) << 10) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_CPU0_ACLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->cpu0_clk_cfg;
                ret &= 0xfffffe3f;
                sysctl_clk->cpu0_clk_cfg = ret | (((denominator - 1) << 6) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_CPU0_NOC_DDRCP4:
            return false;
        case SYSCTL_CLK_CPU0_PCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->cpu0_clk_cfg;
                ret &= 0xffffc7ff;
                sysctl_clk->cpu0_clk_cfg = ret | (((denominator - 1) << 15) | (1 << 31));
                return true;
            }
        }

        /*--------------------------- PMU CLOCK ------------------------------------*/
        case SYSCTL_CLK_PMU_PCLK:
            return false;

        /*--------------------------- HS CLOCK ------------------------------------*/
        case SYSCTL_CLK_HS_HCLK_HIGH_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_sdclk_cfg;
                ret &= 0xfffffff8;
                sysctl_clk->hs_sdclk_cfg = ret | (((denominator - 1) << 0) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_HS_HCLK_HIGH_GATE:
            return false;

        case SYSCTL_CLK_HS_HCLK_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_sdclk_cfg;
                ret &= 0xffffffc7;
                sysctl_clk->hs_sdclk_cfg = ret | (((denominator - 1) << 3) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_SD0_AHB_GATE:
        case SYSCTL_CLK_SD1_AHB_GATE:
        case SYSCTL_CLK_USB0_AHB_GATE:
        case SYSCTL_CLK_USB1_AHB_GATE:
        case SYSCTL_CLK_SSI1_AHB_GATE:
        case SYSCTL_CLK_SSI2_AHB_GATE:
            return false;

        case SYSCTL_CLK_SSI0_AXI:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_spi_cfg;
                ret &= 0xfffff1ff;
                sysctl_clk->hs_spi_cfg = ret | (((denominator - 1) << 9) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_SSI1:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_spi_cfg;
                ret &= 0xffffffc7;
                sysctl_clk->hs_spi_cfg = ret | (((denominator - 1) << 3) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_SSI2:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_spi_cfg;
                ret &= 0xfffffe3f;
                sysctl_clk->hs_spi_cfg = ret | (((denominator - 1) << 6) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_QSPI_AXI_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_spi_cfg;
                ret &= 0xffff8fff;
                sysctl_clk->hs_spi_cfg = ret | (((denominator - 1) << 12) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_SSI1_ACLK_GATE:
        case SYSCTL_CLK_SSI2_ACLK_GATE:
            return false;

        case SYSCTL_CLK_SSI0:
            return false;

        case SYSCTL_CLK_SD_AXI_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_sdclk_cfg;
                ret &= 0xfffffe3f;
                sysctl_clk->hs_sdclk_cfg = ret | (((denominator - 1) << 6) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_SD0_AXI_GATE:
        case SYSCTL_CLK_SD1_AXI_GATE:
        case SYSCTL_CLK_SD0_BASE_GATE:
        case SYSCTL_CLK_SD1_BASE_GATE:
            return false;

        case SYSCTL_CLK_SD_CARD_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_sdclk_cfg;
                ret &= 0xffff8fff;
                sysctl_clk->hs_sdclk_cfg = ret | (((denominator - 1) << 12) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_SD0_CARD_GATE:
        case SYSCTL_CLK_SD1_CARD_GATE:
            return false;

        case SYSCTL_CLK_PLL0_DIV16:
            return false;
        case SYSCTL_CLK_USB_REF_50M:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->hs_spi_cfg;
                ret &= 0xfffc7fff;
                sysctl_clk->hs_spi_cfg = ret | (((denominator - 1) << 15) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_USB0_REF_GATE:
        case SYSCTL_CLK_USB1_REF_GATE:
            return false;

        case SYSCTL_CLK_SD_TIMER_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/32 */
                ret = sysctl_clk->hs_sdclk_cfg;
                ret &= 0xfff07fff;
                sysctl_clk->hs_sdclk_cfg = ret | (((denominator - 1) << 15) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_SD0_TIMER_GATE:
        case SYSCTL_CLK_SD1_TIMER_GATE:
            return false;

        /*--------------------------- LS CLOCK ------------------------------------*/
        case SYSCTL_CLK_LS_APB_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/4, 1/8 --- 1/8 */
                ret = sysctl_clk->ls_clkdiv_cfg;
                ret &= 0xfffffff8;
                sysctl_clk->ls_clkdiv_cfg = ret | (((denominator - 1) << 0) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_UART0_APB_GATE:
        case SYSCTL_CLK_UART1_APB_GATE:
        case SYSCTL_CLK_UART2_APB_GATE:
        case SYSCTL_CLK_UART3_APB_GATE:
        case SYSCTL_CLK_UART4_APB_GATE:
        case SYSCTL_CLK_I2C0_APB_GATE:
        case SYSCTL_CLK_I2C1_APB_GATE:
        case SYSCTL_CLK_I2C2_APB_GATE:
        case SYSCTL_CLK_I2C3_APB_GATE:
        case SYSCTL_CLK_I2C4_APB_GATE:
        case SYSCTL_CLK_GPIO_APB_GATE:
        case SYSCTL_CLK_PWM_APB_GATE:
        case SYSCTL_CLK_JAMLINK0_APB_GATE:
        case SYSCTL_CLK_JAMLINK1_APB_GATE:
        case SYSCTL_CLK_JAMLINK2_APB_GATE:
        case SYSCTL_CLK_JAMLINK3_APB_GATE:
        case SYSCTL_CLK_ADC_APB_GATE:
            return false;

        case SYSCTL_CLK_UART0_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xfffffff8;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 0) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_UART1_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xffffffc7;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 3) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_UART2_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xfffffe3f;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 6) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_UART3_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xfffff1ff;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 9) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_UART4_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xffff8fff;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 12) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_JAMLINK_CO_DIV:
        {
            if((numerator != 1) || (denominator < 2) || (denominator > 512) || (denominator % 2 != 0))
                return false;
            else
            {
                /* 1/2, 1/4, 1/8 --- 1/512 */
                ret = sysctl_clk->ls_clkdiv_cfg;
                ret &= 0x807fffff;
                sysctl_clk->ls_clkdiv_cfg = ret | (((denominator/2 - 1) << 23) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_JAMLINK0_CO_GATE:
        case SYSCTL_CLK_JAMLINK1_CO_GATE:
        case SYSCTL_CLK_JAMLINK2_CO_GATE:
        case SYSCTL_CLK_JAMLINK3_CO_GATE:
            return false;

        case SYSCTL_CLK_I2C0_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xfffc7fff;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 15) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_I2C1_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xffe3ffff;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 18) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_I2C2_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xff1fffff;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 21) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_I2C3_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xf8ffffff;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 24) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_I2C4_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->uart_i2c_clkdiv_cfg;
                ret &= 0xc7ffffff;
                sysctl_clk->uart_i2c_clkdiv_cfg = ret | (((denominator - 1) << 27) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_ADC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 1024))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/1024 */
                ret = sysctl_clk->ls_clkdiv_cfg;
                ret &= 0xffffe007;
                sysctl_clk->ls_clkdiv_cfg = ret | (((denominator - 1) << 3) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_GOIP_DEBOUNCE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 1024))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/1024 */
                ret = sysctl_clk->ls_clkdiv_cfg;
                ret &= 0xff801fff;
                sysctl_clk->ls_clkdiv_cfg = ret | (((denominator - 1) << 13) | (1 << 31));
                return true;
            }
        }

        /*--------------------------- SYSCTL CLOCK ------------------------------------*/
        case SYSCTL_CLK_SYSCTRL_APB_SRC:
            return false;
        case SYSCTL_CLK_WDT0_APB_GATE:
        case SYSCTL_CLK_WDT1_APB_GATE:
        case SYSCTL_CLK_TIMER_APB_GATE:
        case SYSCTL_CLK_IOMUX_APB_GATE:
        case SYSCTL_CLK_MAILBOX_APB_GATE:
            return false;

        case SYSCTL_CLK_HDI_CORE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->sysctl_clk_div_cfg;
                ret &= 0x8fffffff;
                sysctl_clk->sysctl_clk_div_cfg = ret | (((denominator - 1) << 28) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_TIMESTAMP:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/32 */
                ret = sysctl_clk->sysctl_clk_div_cfg;
                ret &= 0xfff07fff;
                sysctl_clk->sysctl_clk_div_cfg = ret | (((denominator - 1) << 15) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_TEMP_SENSOR:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 256))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/256 */
                ret = sysctl_clk->sysctl_clk_div_cfg;
                ret &= 0xf00fffff;
                sysctl_clk->sysctl_clk_div_cfg = ret | (((denominator - 1) << 20) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_WDT0:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/64 */
                ret = sysctl_clk->sysctl_clk_div_cfg;
                ret &= 0xfffffe07;
                sysctl_clk->sysctl_clk_div_cfg = ret | (((denominator - 1) << 3) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_WDT1:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/64 */
                ret = sysctl_clk->sysctl_clk_div_cfg;
                ret &= 0xffff81ff;
                sysctl_clk->sysctl_clk_div_cfg = ret | (((denominator - 1) << 9) | (1 << 31));
                return true;
            }
        }

        /*--------------------------- TIMER CLOCK ------------------------------------*/
        case SYSCTL_CLK_TIMERX_PULSE_IN:
            return false;
        case SYSCTL_CLK_TIMER0_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->timer_clk_cfg;
                ret &= 0xfffffff8;
                sysctl_clk->timer_clk_cfg = ret | (((denominator - 1) << 0) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER0:
            return false;

        case SYSCTL_CLK_TIMER1_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->timer_clk_cfg;
                ret &= 0xffffffc7;
                sysctl_clk->timer_clk_cfg = ret | (((denominator - 1) << 3) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER1:
            return false;

        case SYSCTL_CLK_TIMER2_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->timer_clk_cfg;
                ret &= 0xfffffe3f;
                sysctl_clk->timer_clk_cfg = ret | (((denominator - 1) << 6) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER2:
            return false;

        case SYSCTL_CLK_TIMER3_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->timer_clk_cfg;
                ret &= 0xfffff1ff;
                sysctl_clk->timer_clk_cfg = ret | (((denominator - 1) << 9) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER3:
            return false;

        case SYSCTL_CLK_TIMER4_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->timer_clk_cfg;
                ret &= 0xffff8fff;
                sysctl_clk->timer_clk_cfg = ret | (((denominator - 1) << 12) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER4:
            return false;

        case SYSCTL_CLK_TIMER5_SRC:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->timer_clk_cfg;
                ret &= 0xfffc7fff;
                sysctl_clk->timer_clk_cfg = ret | (((denominator - 1) << 15) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER5:
            return false;

        /*--------------------------- SHRM CLOCK ------------------------------------*/
        case SYSCTL_CLK_SHRM_SRC:
            return false;
        case SYSCTL_CLK_SHRM_DIV2:
            return false;
        case SYSCTL_CLK_SHRM_AXIS_SLAVE:
        case SYSCTL_CLK_DECOMPRESS_AXI:
            return false;

        case SYSCTL_CLK_SHRM_APB:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->shrm_clk_cfg;
                ret &= 0xffe3ffff;
                sysctl_clk->shrm_clk_cfg = ret | (((denominator - 1) << 18) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_SHRM_AXI_SRC:
        case SYSCTL_CLK_NONAI2D_AXI_GATE:
            return false;

        /*--------------------------- SEC CLOCK ------------------------------------*/
        case SYSCTL_CLK_SEC_APB:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->sec_clk_div;
                ret &= 0xfffffff1;
                sysctl_clk->sec_clk_div = ret | (((denominator - 1) << 1) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_SEC_FIX:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/32 */
                ret = sysctl_clk->sec_clk_div;
                ret &= 0xfffff83f;
                sysctl_clk->sec_clk_div = ret | (((denominator - 1) << 6) | (1 << 31));
                return true;
            }
        }

        case SYSCTL_CLK_SEC_AXI:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->sec_clk_div;
                ret &= 0xffffc7ff;
                sysctl_clk->sec_clk_div = ret | (((denominator - 1) << 11) | (1 << 31));
                return true;
            }
        }

        /*--------------------------- USB TEST MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_USB_480M:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->usb_test_clk_div;
                ret &= 0xfffffff1;
                sysctl_clk->usb_test_clk_div = ret | (((denominator - 1) << 1) | (1 << 31));
                return true;
            }
        }
        case SYSCTL_CLK_USB_100M:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->usb_test_clk_div;
                ret &= 0xffffff8f;
                sysctl_clk->usb_test_clk_div = ret | (((denominator - 1) << 4) | (1 << 31));
                return true;
            }
        }

        /*--------------------------- DPHY DFT MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_DPHY_DFT_MODE:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/16 */
                ret = sysctl_clk->dphy_test_clk_div;
                ret &= 0xffffffe1;
                sysctl_clk->dphy_test_clk_div = ret | (((denominator - 1) << 1) | (1 << 31));
                return true;
            }
        }

        /*--------------------------- SPI2AXI CLOCK ------------------------------------*/
        case SYSCTL_CLK_SPI2AXI_AXI:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 8))
                return false;
            else
            {
                /* 1/1, 1/2, 1/3 --- 1/8 */
                ret = sysctl_clk->spi2axi_clk_div;
                ret &= 0xfffffff1;
                sysctl_clk->spi2axi_clk_div = ret | (((denominator - 1) << 1) | (1 << 31));
                return true;
            }
        }

        default:
            return false;
    }
}

/* Get the frequency division coefficient of this clock node */
double sysctl_clk_get_leaf_div(sysctl_clk_node_e leaf)
{
    switch(sysctl_clk_attribute(leaf))
    {
        case 0:
            return -1;
        case 1:
        case 3:
            break;
    }

    switch(leaf)
    {
        /*--------------------------- CPU0 CLOCK ------------------------------------*/
        case SYSCTL_CLK_CPU0_SRC:
            return (double)(((sysctl_clk->cpu0_clk_cfg >> 1) & 0xF) + 1) / 16.0;    /* 1/16 --- 16/16 */
        case SYSCTL_CLK_CPU0_PLIC:
            return 1.0/(double)(((sysctl_clk->cpu0_clk_cfg >> 10) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_CPU0_ACLK:
            return 1.0/(double)(((sysctl_clk->cpu0_clk_cfg >> 6) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_CPU0_NOC_DDRCP4:
            return 1;
        case SYSCTL_CLK_CPU0_PCLK:
            return 1.0/(double)(((sysctl_clk->cpu0_clk_cfg >> 15) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        /*--------------------------- PMU CLOCK ------------------------------------*/
        case SYSCTL_CLK_PMU_PCLK:
            return 1;

        /*--------------------------- HS CLOCK ------------------------------------*/
        case SYSCTL_CLK_HS_HCLK_HIGH_SRC:
            return 1.0/(double)(((sysctl_clk->hs_sdclk_cfg >> 0) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_HS_HCLK_HIGH_GATE:
            return 1;
        case SYSCTL_CLK_HS_HCLK_SRC:
            return 1.0/(double)(((sysctl_clk->hs_sdclk_cfg >> 3) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_SD0_AHB_GATE:
        case SYSCTL_CLK_SD1_AHB_GATE:
        case SYSCTL_CLK_USB0_AHB_GATE:
        case SYSCTL_CLK_USB1_AHB_GATE:
        case SYSCTL_CLK_SSI1_AHB_GATE:
        case SYSCTL_CLK_SSI2_AHB_GATE:
            return 1;

        case SYSCTL_CLK_SSI0_AXI:
            return 1.0/(double)(((sysctl_clk->hs_spi_cfg >> 9) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_SSI1:
            return 1.0/(double)(((sysctl_clk->hs_spi_cfg >> 3) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_SSI2:
            return 1.0/(double)(((sysctl_clk->hs_spi_cfg >> 6) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_QSPI_AXI_SRC:
            return 1.0/(double)(((sysctl_clk->hs_spi_cfg >> 12) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_SSI1_ACLK_GATE:
        case SYSCTL_CLK_SSI2_ACLK_GATE:
            return 1;

        case SYSCTL_CLK_SSI0:
            return 1;

        case SYSCTL_CLK_SD_AXI_SRC:
            return 1.0/(double)(((sysctl_clk->hs_sdclk_cfg >> 6) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_SD0_AXI_GATE:
        case SYSCTL_CLK_SD1_AXI_GATE:
        case SYSCTL_CLK_SD0_BASE_GATE:
        case SYSCTL_CLK_SD1_BASE_GATE:
            return 1;

        case SYSCTL_CLK_SD_CARD_SRC:
            return 1.0/(double)(((sysctl_clk->hs_sdclk_cfg >> 6) & 0x7) + 1);      /* maxinum = 1/2, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_SD0_CARD_GATE:
        case SYSCTL_CLK_SD1_CARD_GATE:
            return 1;

        case SYSCTL_CLK_PLL0_DIV16:
            return 1.0/16;
        case SYSCTL_CLK_USB_REF_50M:
            return 1.0/(double)(((sysctl_clk->hs_spi_cfg >> 15) & 0x7) + 1);        /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_USB0_REF_GATE:
        case SYSCTL_CLK_USB1_REF_GATE:
            return 1;

        case SYSCTL_CLK_SD_TIMER_SRC:
            return 1.0/(double)(((sysctl_clk->hs_sdclk_cfg >> 15) & 0x1F) + 1);      /* maxinum = 1/24, 1/24 --- 1/32 */
        case SYSCTL_CLK_SD0_TIMER_GATE:
        case SYSCTL_CLK_SD1_TIMER_GATE:
            return 1;

        /*--------------------------- LS CLOCK ------------------------------------*/
        case SYSCTL_CLK_LS_APB_SRC:
            return 1.0/(double)(((sysctl_clk->ls_clkdiv_cfg >> 0) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_UART0_APB_GATE:
        case SYSCTL_CLK_UART1_APB_GATE:
        case SYSCTL_CLK_UART2_APB_GATE:
        case SYSCTL_CLK_UART3_APB_GATE:
        case SYSCTL_CLK_UART4_APB_GATE:
        case SYSCTL_CLK_I2C0_APB_GATE:
        case SYSCTL_CLK_I2C1_APB_GATE:
        case SYSCTL_CLK_I2C2_APB_GATE:
        case SYSCTL_CLK_I2C3_APB_GATE:
        case SYSCTL_CLK_I2C4_APB_GATE:
        case SYSCTL_CLK_GPIO_APB_GATE:
        case SYSCTL_CLK_PWM_APB_GATE:
        case SYSCTL_CLK_JAMLINK0_APB_GATE:
        case SYSCTL_CLK_JAMLINK1_APB_GATE:
        case SYSCTL_CLK_JAMLINK2_APB_GATE:
        case SYSCTL_CLK_JAMLINK3_APB_GATE:
        case SYSCTL_CLK_ADC_APB_GATE:
            return 1;

        case SYSCTL_CLK_UART0_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 0) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_UART1_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 3) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_UART2_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 6) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_UART3_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 9) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_UART4_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 12) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        case SYSCTL_CLK_JAMLINK_CO_DIV:
            return 1.0/(double)(2 * (((sysctl_clk->ls_clkdiv_cfg >> 23) & 0xFF) + 1));      /* 1/2, 1/4, 1/8 --- 1/512 */
        case SYSCTL_CLK_JAMLINK0_CO_GATE:
        case SYSCTL_CLK_JAMLINK1_CO_GATE:
        case SYSCTL_CLK_JAMLINK2_CO_GATE:
        case SYSCTL_CLK_JAMLINK3_CO_GATE:
            return 1;

        case SYSCTL_CLK_I2C0_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 15) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_I2C1_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 18) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_I2C2_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 21) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_I2C3_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 24) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_I2C4_CORE:
            return 1.0/(double)(((sysctl_clk->uart_i2c_clkdiv_cfg >> 27) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        case SYSCTL_CLK_ADC:
            return 1.0/(double)(((sysctl_clk->ls_clkdiv_cfg >> 3) & 0x3FF) + 1);      /* 1/1, 1/2, 1/3 --- 1/1024 */

        case SYSCTL_CLK_GOIP_DEBOUNCE:
            return 1.0/(double)(((sysctl_clk->ls_clkdiv_cfg >> 13) & 0x3FF) + 1);      /* 1/1, 1/2, 1/3 --- 1/1024 */

        /*--------------------------- SYSCTL CLOCK ------------------------------------*/
        case SYSCTL_CLK_SYSCTRL_APB_SRC:
            /* return 1.0/(double)(((sysctl_clk->sysctl_clk_div_cfg >> 0) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8  */
            return 1;
        case SYSCTL_CLK_WDT0_APB_GATE:
        case SYSCTL_CLK_WDT1_APB_GATE:
        case SYSCTL_CLK_TIMER_APB_GATE:
        case SYSCTL_CLK_IOMUX_APB_GATE:
        case SYSCTL_CLK_MAILBOX_APB_GATE:
            return 1;

        case SYSCTL_CLK_HDI_CORE:
            return 1.0/(double)(((sysctl_clk->sysctl_clk_div_cfg >> 28) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        case SYSCTL_CLK_TIMESTAMP:
            return 1.0/(double)(((sysctl_clk->sysctl_clk_div_cfg >> 15) & 0x1F) + 1);      /* 1/1, 1/2, 1/3 --- 1/32 */

        case SYSCTL_CLK_TEMP_SENSOR:
            return 1.0/(double)(((sysctl_clk->sysctl_clk_div_cfg >> 20) & 0xFF) + 1);      /* 1/1, 1/2, 1/3 --- 1/256 */

        case SYSCTL_CLK_WDT0:
            return 1.0/(double)(((sysctl_clk->sysctl_clk_div_cfg >> 3) & 0x3F) + 1);      /* 1/1, 1/2, 1/3 --- 1/64 */

        case SYSCTL_CLK_WDT1:
            return 1.0/(double)(((sysctl_clk->sysctl_clk_div_cfg >> 9) & 0x3F) + 1);      /* 1/1, 1/2, 1/3 --- 1/64 */

        /*--------------------------- TIMER CLOCK ------------------------------------*/
        case SYSCTL_CLK_TIMERX_PULSE_IN:
            return 1;
        case SYSCTL_CLK_TIMER0_SRC:
            return 1.0/(double)(((sysctl_clk->timer_clk_cfg >> 0) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_TIMER0:
            return 1;

        case SYSCTL_CLK_TIMER1_SRC:
            return 1.0/(double)(((sysctl_clk->timer_clk_cfg >> 3) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_TIMER1:
            return 1;

        case SYSCTL_CLK_TIMER2_SRC:
            return 1.0/(double)(((sysctl_clk->timer_clk_cfg >> 6) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_TIMER2:
            return 1;

        case SYSCTL_CLK_TIMER3_SRC:
            return 1.0/(double)(((sysctl_clk->timer_clk_cfg >> 9) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_TIMER3:
            return 1;

        case SYSCTL_CLK_TIMER4_SRC:
            return 1.0/(double)(((sysctl_clk->timer_clk_cfg >> 12) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_TIMER4:
            return 1;

        case SYSCTL_CLK_TIMER5_SRC:
            return 1.0/(double)(((sysctl_clk->timer_clk_cfg >> 15) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_TIMER5:
            return 1;


        /*--------------------------- SHRM CLOCK ------------------------------------*/
        case SYSCTL_CLK_SHRM_SRC:
            return 1;
        case SYSCTL_CLK_SHRM_DIV2:
            return 1.0/2;
        case SYSCTL_CLK_SHRM_AXIS_SLAVE:
        case SYSCTL_CLK_DECOMPRESS_AXI:
            return 1;

        case SYSCTL_CLK_SHRM_APB:
            return 1.0/(double)(((sysctl_clk->shrm_clk_cfg >> 18) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        case SYSCTL_CLK_SHRM_AXI_SRC:
        case SYSCTL_CLK_NONAI2D_AXI_GATE:
            return 1;

        /*--------------------------- SEC CLOCK ------------------------------------*/
        case SYSCTL_CLK_SEC_APB:
            return 1.0/(double)(((sysctl_clk->sec_clk_div >> 1) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_SEC_FIX:
            return 1.0/(double)(((sysctl_clk->sec_clk_div >> 6) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        case SYSCTL_CLK_SEC_AXI:
            return 1.0/(double)(((sysctl_clk->sec_clk_div >> 11) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        /*--------------------------- USB TEST MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_USB_480M:
            return 1.0/(double)(((sysctl_clk->usb_test_clk_div >> 1) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */
        case SYSCTL_CLK_USB_100M:
            return 1.0/(double)(((sysctl_clk->usb_test_clk_div >> 4) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        /*--------------------------- DPHY DFT MODE CLOCK ------------------------------------*/
        case SYSCTL_CLK_DPHY_DFT_MODE:
            return 1.0/(double)(((sysctl_clk->dphy_test_clk_div >> 1) & 0xF) + 1);      /* 1/1, 1/2, 1/3 --- 1/16 */

        /*--------------------------- SPI2AXI CLOCK ------------------------------------*/
        case SYSCTL_CLK_SPI2AXI_AXI:
            return 1.0/(double)(((sysctl_clk->spi2axi_clk_div >> 1) & 0x7) + 1);      /* 1/1, 1/2, 1/3 --- 1/8 */

        default:
            return 1;
    }
}

/*
 * Calculate the frequency of this clock node.
 * It searches the entire clock path, calculates the frequency division of each
 * level starting from the clock source, and finally obtains the frequency of
 * the current clock node.
 * 1. For the clock of the root node, use sysctl_boot_get_root_clk_freq(node)
 *    to get the clock frequency (the frequency division coefficient div=1 at
 *    this time);
 * 2. For the clock of the leaf node, use the while loop to search the root
 *    node of the leaf node and calculate the div on the entire path. After
 *    finding the root node, use sysctl_boot_get_root_clk_freq(node) * div to
 *    calculate the frequency of the leaf node.
 */
uint32_t sysctl_clk_get_leaf_freq(sysctl_clk_node_e leaf)
{
    double div = 1.0;
    sysctl_clk_node_e node;

    node = leaf;

    if(node == SYSCTL_CLK_TIMERX_PULSE_IN)
    {
        return (uint32_t)(50000000 * div);
    }

    /* calc leaf chain div */
    while(node > SYSCTL_CLK_ROOT_MAX)
    {
        div *= sysctl_clk_get_leaf_div(node);
        node = sysctl_clk_get_leaf_parent(node);
    }

    /* get root freq and calc leaf freq */
    return (uint32_t)(sysctl_boot_get_root_clk_freq(node) * div);
}

int rt_hw_sysctl_clk_init(void)
{
    sysctl_clk = rt_ioremap((void*)CMU_BASE_ADDR, CMU_IO_SIZE);
    if(!sysctl_clk)
    {
        rt_kprintf("sysctl_clk ioremap error\n");
        return -1;
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_sysctl_clk_init);