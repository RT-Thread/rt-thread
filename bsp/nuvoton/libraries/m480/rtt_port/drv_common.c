/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>
#include <rtthread.h>
#include "NuMicro.h"
#include "drv_uart.h"
#include "board.h"
#include "nutool_pincfg.h"
#include "nutool_modclkcfg.h"


/**
 * This function will initial.
 */
RT_WEAK void rt_hw_board_init(void)
{
    /* Init System/modules clock */
    nutool_modclkcfg_init();

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init all pin function setting */
    nutool_pincfg_init();

    /* Configure SysTick */
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

#if defined(BSP_USING_EADC)
    /* Vref connect to internal */
    SYS->VREFCTL = (SYS->VREFCTL & ~SYS_VREFCTL_VREFCTL_Msk) | SYS_VREFCTL_VREF_3_0V;
#endif

    /* Lock protected registers */
    SYS_LockReg();

#ifdef RT_USING_HEAP
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif /* RT_USING_HEAP */

#if defined(BSP_USING_UART)
    rt_hw_uart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    NVIC_SetPriorityGrouping(7);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/**
 * The time delay function.
 *
 * @param microseconds.
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
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

void rt_hw_cpu_reset(void)
{
    SYS_UnlockReg();

    SYS->IPRST0 |= SYS_IPRST0_CHIPRST_Msk;
}

int reboot(int argc, char **argv)
{
    rt_hw_cpu_reset();
    return 0;
}
MSH_CMD_EXPORT(reboot, Reboot System);
