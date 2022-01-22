/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     DongBowen    first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "hc32l196_sysctrl.h"
#include "hc32l196_flash.h"

/**
 * @brief  BSP clock initialize.
 *         Set board system clock to PLL@48MHz by RCH
 * @param  None
 * @retval None
 */
void rt_hw_board_clock_init(void)
{
    stc_sysctrl_pll_cfg_t stcPLLCfg;

    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);

    /* switch clock to RCL before changing RCH */
    Sysctrl_SetRCLTrim(SysctrlRclFreq32768);
    Sysctrl_SetRCLStableTime(SysctrlRclStableCycle64);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
    Sysctrl_SysClkSwitch(SysctrlClkRCL);

    /* set RCH to 4MHz */
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);

    stcPLLCfg.enInFreq    = SysctrlPllInFreq4_6MHz;
    stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;
    stcPLLCfg.enPllClkSrc = SysctrlPllRch;              /* input clock: RCH  */
    stcPLLCfg.enPllMul    = SysctrlPllMul12;            /* 4MHz x 12 = 48MHz */
    Sysctrl_SetPLLFreq(&stcPLLCfg);

    /*
     * When the used clock source HCLK is greater than 24M,
     * set the FLASH read wait cycle to 1 cycle.
     */
    Flash_WaitCycle(FlashWaitCycle1);

    /* enable PLL */
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);
    /* switch clock to PLL */
    Sysctrl_SysClkSwitch(SysctrlClkPLL);
}

/*******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SysTick_Configuration(void)
{
    rt_uint32_t cnts;

    cnts = Sysctrl_GetHClkFreq() / RT_TICK_PER_SECOND;

    SysTick_Config(cnts);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initialize HC32 board.
 */
void rt_hw_board_init()
{
    /* Configure the System clock */
    rt_hw_board_clock_init();

    /* Configure the SysTick */
    SysTick_Configuration();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

}

void rt_hw_us_delay(rt_uint32_t us)
{
    uint32_t start, now, delta, reload, us_tick;
    start = SysTick->VAL;
    reload = SysTick->LOAD;
    us_tick = SystemCoreClock / 1000000UL;

    do
    {
        now = SysTick->VAL;
        delta = start > now ?  start - now : reload + start - now;
    }
    while (delta < us_tick * us);
}
