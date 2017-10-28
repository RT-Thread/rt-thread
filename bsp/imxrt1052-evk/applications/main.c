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

#include <board.h>

RT_USED MPU_Type *mpu = MPU;
RT_USED IOMUXC_GPR_Type *iomuxc_gpr = IOMUXC_GPR;


static void dump_clock(void)
{
    rt_kprintf("CPU clock: %d\n",                   CLOCK_GetFreq(kCLOCK_CpuClk));
	rt_kprintf("AHB clock : %d\n",                  CLOCK_GetFreq(kCLOCK_AhbClk));
	rt_kprintf("SEMC clock : %d\n",                 CLOCK_GetFreq(kCLOCK_SemcClk));
	rt_kprintf("IPG clock : %d\n",                  CLOCK_GetFreq(kCLOCK_IpgClk));               
	rt_kprintf("OSC clock selected : %d\n",         CLOCK_GetFreq(kCLOCK_OscClk));               
	rt_kprintf("RTC clock: %d\n",                   CLOCK_GetFreq(kCLOCK_RtcClk));               
	rt_kprintf("ARMPLLCLK : %d\n",                  CLOCK_GetFreq(kCLOCK_ArmPllClk));            
	rt_kprintf("USB1PLLCLK : %d\n",                 CLOCK_GetFreq(kCLOCK_Usb1PllClk));           
	rt_kprintf("USB1PLLPDF0CLK : %d\n",             CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk));       
	rt_kprintf("USB1PLLPFD1CLK : %d\n",             CLOCK_GetFreq(kCLOCK_Usb1PllPfd1Clk));       
	rt_kprintf("USB1PLLPFD2CLK : %d\n",             CLOCK_GetFreq(kCLOCK_Usb1PllPfd2Clk));       
	rt_kprintf("USB1PLLPFD3CLK : %d\n",             CLOCK_GetFreq(kCLOCK_Usb1PllPfd3Clk));       
	rt_kprintf("USB2PLLCLK : %d\n",                 CLOCK_GetFreq(kCLOCK_Usb2PllClk));           
	rt_kprintf("SYSPLLCLK : %d\n",                  CLOCK_GetFreq(kCLOCK_SysPllClk));            
	rt_kprintf("SYSPLLPDF0CLK : %d\n",              CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));        
	rt_kprintf("SYSPLLPFD1CLK : %d\n",              CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));        
	rt_kprintf("SYSPLLPFD2CLK : %d\n",              CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));        
	rt_kprintf("SYSPLLPFD3CLK : %d\n",              CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));        
	rt_kprintf("Enet PLLCLK ref_enetpll0 : %d\n",   CLOCK_GetFreq(kCLOCK_EnetPll0Clk));          
	rt_kprintf("Enet PLLCLK ref_enetpll1 : %d\n",   CLOCK_GetFreq(kCLOCK_EnetPll1Clk));          
	rt_kprintf("Enet PLLCLK ref_enetpll2 : %d\n",   CLOCK_GetFreq(kCLOCK_EnetPll2Clk));          
	rt_kprintf("Audio PLLCLK : %d\n",               CLOCK_GetFreq(kCLOCK_AudioPllClk));          
	rt_kprintf("Video PLLCLK : %d\n",               CLOCK_GetFreq(kCLOCK_VideoPllClk));          
}

void dump_tcm(void)
{
    #define DUMP_REG(__REG)   \
        rt_kprintf("%s(%08p): %08x\n", #__REG, &(__REG), __REG)
            
    DUMP_REG(IOMUXC_GPR->GPR14);
    DUMP_REG(IOMUXC_GPR->GPR16);
    DUMP_REG(IOMUXC_GPR->GPR17);
}

int main(void)
{
    //dump_clock();
    //dump_tcm();
    
    rt_thread_delay(RT_TICK_PER_SECOND * 2);
    
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        rt_kprintf("File System initialized!\n");
    else
        rt_kprintf("File System init failed!\n");
    
    
    while (1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}



/*@}*/
