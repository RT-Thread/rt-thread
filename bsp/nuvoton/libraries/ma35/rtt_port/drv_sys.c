/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-11-11      Wayne            First version
*
******************************************************************************/

#include <rthw.h>
#include <rtthread.h>
#include "drv_sys.h"
#include <stdio.h>

#define DEF_RAISING_CPU_FREQUENCY
//Dont enable #define DEF_RAISING_CPU_VOLTAGE

void machine_shutdown(void)
{
    rt_kprintf("machine_shutdown...\n");
    rt_hw_interrupt_disable();

    /* Unlock */
    SYS_UnlockReg();

    while (1);
}

void machine_reset(void)
{
    rt_kprintf("machine_reset...\n");
    rt_hw_interrupt_disable();

    /* Unlock */
    SYS_UnlockReg();

    SYS->IPRST0 = SYS_IPRST0_CHIPRST_Msk;
    SYS->IPRST0 = 0;
    while (1);
}

int reboot(int argc, char **argv)
{
    machine_reset();
    return 0;
}
MSH_CMD_EXPORT(reboot, Reboot System);


void nu_sys_ip_reset(uint32_t u32ModuleIndex)
{
    SYS_ResetModule(u32ModuleIndex);
}

E_SYS_USB0_ID nu_sys_usb0_role(void)
{
#if 0
    /* Check Role on USB0 dual-role port. */
    /*
        [17] USB0_IDS
           USB0_ID Status
           0 = USB port 0 used as a USB device port.
           1 = USB port 0 used as a USB host port.
      */
    return ((inpw(REG_SYS_MISCISR) & (1 << 17)) > 0) ? USB0_ID_HOST : USB0_ID_DEVICE;
#else
    return USB0_ID_DEVICE;
#endif
}

void nu_sys_check_register(S_NU_REG *psNuReg)
{
    if (psNuReg == RT_NULL)
        return;

    while (psNuReg->vu32RegAddr != 0)
    {
        vu32 vc32RegValue = *((vu32 *)psNuReg->vu32RegAddr);
        vu32 vc32BMValue = vc32RegValue & psNuReg->vu32BitMask;
        rt_kprintf("[%3s] %32s(0x%08x) %24s(0x%08x): 0x%08x(AndBitMask:0x%08x)\n",
                   (psNuReg->vu32Value == vc32BMValue) ? "Ok" : "!OK",
                   psNuReg->szVName,
                   psNuReg->vu32Value,
                   psNuReg->szRegName,
                   psNuReg->vu32RegAddr,
                   vc32RegValue,
                   vc32BMValue);
        psNuReg++;
    }
}

static int nu_tempsen_init()
{
    SYS->TSENSRFCR &= ~SYS_TSENSRFCR_PD_Msk; // Disable power down, don't wait, takes double conv time (350ms * 2)
    return 0;
}

static int nu_tempsen_get_value()
{
    char sztmp[32];
    double temp;
    static rt_tick_t _old_tick = 0;
    static int32_t count = 0;

    _old_tick = rt_tick_get();

    // Wait valid bit set
    while ((SYS->TSENSRFCR & SYS_TSENSRFCR_DATAVALID_Msk) == 0)
    {
        // 700 ms after clear pd bit. other conversion takes 350 ms
        if (rt_tick_get() > (500 + _old_tick))
        {
            return -1;
        }
    }

    if (++count == 8)
    {
        count = 0;
        temp = (double)((SYS->TSENSRFCR & 0x0FFF0000) >> 16) * 274.3531 / 4096.0 - 93.3332;
        snprintf(sztmp, sizeof(sztmp), "Temperature: %.1f\n", temp);
        rt_kprintf("%s", sztmp);
    }

    // Clear Valid bit
    SYS->TSENSRFCR = SYS_TSENSRFCR_DATAVALID_Msk;

    return 0;
}

void nu_tempsen_hook(void)
{
    nu_tempsen_get_value();
}

static int nu_tempsen_go(void)
{
    rt_err_t err = rt_thread_idle_sethook(nu_tempsen_hook);

    if (err != RT_EOK)
    {
        rt_kprintf("set %s idle hook failed!\n", __func__);
        return -1;
    }

    nu_tempsen_init();

    return 0;
}
//INIT_APP_EXPORT(nu_tempsen_go);
MSH_CMD_EXPORT(nu_tempsen_go, go tempsen);

void nu_clock_dump(void)
{
    rt_kprintf("HXT: %d Hz\n", CLK_GetHXTFreq());
    rt_kprintf("LXT: %d Hz\n", CLK_GetLXTFreq());
    rt_kprintf("CAPLL: %d Hz(OpMode=%d)\n", CLK_GetPLLClockFreq(CAPLL),   CLK_GetPLLOpMode(CAPLL));
    rt_kprintf("DDRPLL: %d Hz(OpMode=%d)\n", CLK_GetPLLClockFreq(DDRPLL), CLK_GetPLLOpMode(DDRPLL));
    rt_kprintf("APLL: %d Hz(OpMode=%d)\n", CLK_GetPLLClockFreq(APLL),     CLK_GetPLLOpMode(APLL));
    rt_kprintf("EPLL: %d Hz(OpMode=%d)\n", CLK_GetPLLClockFreq(EPLL),     CLK_GetPLLOpMode(EPLL));
    rt_kprintf("VPLL: %d Hz(OpMode=%d)\n", CLK_GetPLLClockFreq(VPLL),     CLK_GetPLLOpMode(VPLL));

    rt_kprintf("M4-CPU: %d Hz\n", CLK_GetCPUFreq());

    rt_kprintf("SYSCLK0: %d Hz\n", CLK_GetSYSCLK0Freq());
    rt_kprintf("SYSCLK1: %d Hz\n", CLK_GetSYSCLK1Freq());
    rt_kprintf("HCLK0: %d Hz\n", CLK_GetHCLK0Freq());
    rt_kprintf("HCLK1: %d Hz\n", CLK_GetHCLK1Freq());
    rt_kprintf("HCLK2: %d Hz\n", CLK_GetHCLK2Freq());
    rt_kprintf("HCLK3: %d Hz\n", CLK_GetHCLK3Freq());
    rt_kprintf("PCLK0: %d Hz\n", CLK_GetPCLK0Freq());
    rt_kprintf("PCLK1: %d Hz\n", CLK_GetPCLK1Freq());
    rt_kprintf("PCLK2: %d Hz\n", CLK_GetPCLK2Freq());
    rt_kprintf("PCLK3: %d Hz\n", CLK_GetPCLK3Freq());
    rt_kprintf("PCLK4: %d Hz\n", CLK_GetPCLK4Freq());
}

const char *szClockName [] =
{
    "HXT",
    "LXT",
    "N/A",
    "LIRC",
    "HIRC",
    "N/A",
    "CAPLL",
    "N/A",
    "DDRPLL",
    "EPLL",
    "APLL",
    "VPLL"
};
#define CLOCKNAME_SIZE    (sizeof(szClockName)/sizeof(char*))

void nu_clock_isready(void)
{
    uint32_t u32IsReady, i;
    for (i = 0; i < CLOCKNAME_SIZE; i++)
    {
        if (i == 5 || i == 7 || i == 2) continue;
        u32IsReady = CLK_WaitClockReady(1 << i);
        rt_kprintf("%s: %s\n", szClockName[i], (u32IsReady == 1) ? "[Stable]" : "[Unstable]");
    }
}

extern uint32_t ma35d1_set_cpu_voltage(uint32_t sys_clk, uint32_t u32Vol);
void nu_clock_raise(void)
{
    uint32_t u32PllRefClk;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable HXT, LXT */
    CLK->PWRCTL |= (CLK_PWRCTL_HXTEN_Msk | CLK_PWRCTL_HIRCEN_Msk);
    if (CLK->STATUS & CLK_STATUS_HXTSTB_Msk)     // Check Ready
    {
        u32PllRefClk = __HXT;
    }
    else if (CLK->STATUS & CLK_STATUS_HIRCSTB_Msk)      // Check Ready
    {
        u32PllRefClk = __HIRC;  // HXT_CHECK_FAIL
    }
    else
    {
        return;
    }

    CLK_SetPLLFreq(VPLL, PLL_OPMODE_INTEGER, u32PllRefClk, 102000000ul);
    CLK_SetPLLFreq(APLL, PLL_OPMODE_INTEGER, u32PllRefClk, 160000000ul);
    CLK_SetPLLFreq(EPLL, PLL_OPMODE_INTEGER, u32PllRefClk, 500000000ul);

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_VPLLSTB_Msk | CLK_STATUS_APLLSTB_Msk | CLK_STATUS_EPLLSTB_Msk);

#if defined(DEF_RAISING_CPU_FREQUENCY)
    /* Switch clock source of CA35 to DDRPLL before raising CA-PLL */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_CA35CKSEL_Msk)) | CLK_CLKSEL0_CA35CKSEL_DDRPLL;
#if defined(DEF_RAISING_CPU_VOLTAGE)
    if (ma35d1_set_cpu_voltage(CLK_GetPLLClockFreq(SYSPLL), 0x68))
    {
        CLK_SetPLLFreq(CAPLL, PLL_OPMODE_INTEGER, u32PllRefClk, 1000000000ul);
    }
    else
#endif
    {
        ma35d1_set_cpu_voltage(CLK_GetPLLClockFreq(SYSPLL), 0x5F);
        CLK_SetPLLFreq(CAPLL, PLL_OPMODE_INTEGER, u32PllRefClk, 800000000ul);
    }

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_CAPLLSTB_Msk);

    /* Switch clock source of CA35 to CA-PLL after raising */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_CA35CKSEL_Msk)) | CLK_CLKSEL0_CA35CKSEL_CAPLL;
#endif

}

#ifdef FINSH_USING_MSH
    MSH_CMD_EXPORT(nu_clock_dump, Dump all clocks);
    MSH_CMD_EXPORT(nu_clock_raise, Raise clock);
    MSH_CMD_EXPORT(nu_clock_isready, Check PLL clocks);
#endif


