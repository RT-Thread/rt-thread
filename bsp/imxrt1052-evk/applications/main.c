/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        first version
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_file.h>
#endif

#ifdef RT_USING_DEVICE
#include <rtdevice.h>
#endif

#include <board.h>

void dump_clock(void)
{
    rt_kprintf("OSC clock : %d\n",                  CLOCK_GetFreq(kCLOCK_OscClk));
    rt_kprintf("RTC clock : %d\n",                  CLOCK_GetFreq(kCLOCK_RtcClk));
    rt_kprintf("CPU clock: %d\n",                   CLOCK_GetFreq(kCLOCK_CpuClk)); 
    rt_kprintf("AHB clock : %d\n",                  CLOCK_GetFreq(kCLOCK_AhbClk)); 
    rt_kprintf("SEMC clock : %d\n",                 CLOCK_GetFreq(kCLOCK_SemcClk)); 
    rt_kprintf("IPG clock : %d\n",                  CLOCK_GetFreq(kCLOCK_IpgClk));
    rt_kprintf("ARMPLLCLK(PLL1) : %d\n",            CLOCK_GetFreq(kCLOCK_ArmPllClk));
    rt_kprintf("SYSPLLCLK(PLL2/528_PLL) : %d\n",    CLOCK_GetFreq(kCLOCK_SysPllClk));
    rt_kprintf("SYSPLLPDF0CLK : %d\n",              CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
    rt_kprintf("SYSPLLPFD1CLK : %d\n",              CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
    rt_kprintf("SYSPLLPFD2CLK : %d\n",              CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
    rt_kprintf("SYSPLLPFD3CLK : %d\n",              CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));
    rt_kprintf("USB1PLLCLK(PLL3) : %d\n",           CLOCK_GetFreq(kCLOCK_Usb1PllClk));
    rt_kprintf("USB1PLLPDF0CLK : %d\n",             CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk));
    rt_kprintf("USB1PLLPFD1CLK : %d\n",             CLOCK_GetFreq(kCLOCK_Usb1PllPfd1Clk));
    rt_kprintf("USB1PLLPFD2CLK : %d\n",             CLOCK_GetFreq(kCLOCK_Usb1PllPfd2Clk));
    rt_kprintf("USB1PLLPFD3CLK : %d\n",             CLOCK_GetFreq(kCLOCK_Usb1PllPfd3Clk));
    rt_kprintf("Audio PLLCLK(PLL4) : %d\n",         CLOCK_GetFreq(kCLOCK_AudioPllClk));
    rt_kprintf("Video PLLCLK(PLL5) : %d\n",         CLOCK_GetFreq(kCLOCK_VideoPllClk));
    rt_kprintf("Enet PLLCLK ref_enetpll0 : %d\n",   CLOCK_GetFreq(kCLOCK_EnetPll0Clk));
    rt_kprintf("Enet PLLCLK ref_enetpll1 : %d\n",   CLOCK_GetFreq(kCLOCK_EnetPll1Clk));
    rt_kprintf("Enet PLLCLK ref_enetpll2 : %d\n",   CLOCK_GetFreq(kCLOCK_EnetPll2Clk));
    rt_kprintf("USB2PLLCLK(PLL7) : %d\n",           CLOCK_GetFreq(kCLOCK_Usb2PllClk));
}

void dump_cc_info(void)
{
#if defined(__CC_ARM)
    rt_kprintf("using armcc, version: %d\n", __ARMCC_VERSION);
#elif defined(__ICCARM__)
    rt_kprintf("using iccarm, version: %d\n", __VER__);
#elif defined(__GNUC__)
    rt_kprintf("using gcc, version: %d.%d\n", __GNUC__, __GNUC_MINOR__);
#endif
}

void dump_link_info(void)
{
#if defined(__CC_ARM)

#elif defined(__ICCARM__)

#elif defined(__GNUC__)
    #define DUMP_SYMBOL(__SYM)                  \
        extern int __SYM;                       \
        rt_kprintf("%s: %p\n", #__SYM, &__SYM)

    DUMP_SYMBOL(__fsymtab_start);
    DUMP_SYMBOL(__fsymtab_end);
    DUMP_SYMBOL(__vsymtab_start);
    DUMP_SYMBOL(__vsymtab_end);
    DUMP_SYMBOL(__rt_init_start);
    DUMP_SYMBOL(__rt_init_end);

    DUMP_SYMBOL(__exidx_start);
    DUMP_SYMBOL(__exidx_end);

    DUMP_SYMBOL(__etext);

    DUMP_SYMBOL(__data_start__);
    DUMP_SYMBOL(__data_end__);

    DUMP_SYMBOL(__noncachedata_start__);
    DUMP_SYMBOL(__noncachedata_init_end__);

    DUMP_SYMBOL(__noncachedata_end__);

    DUMP_SYMBOL(__bss_start__);
    DUMP_SYMBOL(__bss_end__);

    DUMP_SYMBOL(stack_start);
    DUMP_SYMBOL(stack_end);

    DUMP_SYMBOL(heap_start);
#endif
}

int main(void)
{
    rt_uint32_t result;
    //dump_clock();
    dump_cc_info();
    dump_link_info();

    rt_kprintf("build time: %s %s\n", __DATE__, __TIME__);

#if defined(RT_USING_DFS) && defined(RT_USING_SDIO)
    result = mmcsd_wait_cd_changed(RT_TICK_PER_SECOND);
    if (result == MMCSD_HOST_PLUGED)
    {
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
    }
    else
    {
        rt_kprintf("sdcard init fail or timeout: %d!\n", result);
    }
#endif

    while (1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}



/*@}*/
