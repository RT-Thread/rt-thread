/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-07-14      Wayne            First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(USE_MA35D1_SUBM)

#include <rthw.h>
#include <stdio.h>

#include "drv_common.h"
#include "board.h"
#include "drv_uart.h"

#define LOG_TAG    "drv.common"
#undef  DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL      LOG_LVL_DBG
#define DBG_COLOR
#include <rtdbg.h>

extern void nu_clock_init(void);

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

int rt_hw_systick_init(void)
{
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Configure SysTick */
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);


    return 0;
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

void idle_wfi(void)
{
    __WFI();
}

rt_weak void nutool_pincfg_init(void)
{

}

/**
 * This function will initial board.
 */
rt_weak void rt_hw_board_init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* initialize base clock */
    nu_clock_init();

    /* initialize peripheral pin function */
    nutool_pincfg_init();

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)BOARD_HEAP_START, (void *)BOARD_HEAP_END);
#endif

    /* initialize uart */
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#if defined(RT_USING_HEAP)
    /* Dump heap information */
    rt_kprintf("Heap: Begin@%08x, END@%08x, SIZE: %d KiB\n", BOARD_HEAP_START, BOARD_HEAP_END, ((rt_uint32_t)BOARD_HEAP_END - (rt_uint32_t)BOARD_HEAP_START) / 1024);
#endif

    /* initialize systick */
    rt_hw_systick_init();
    rt_thread_idle_sethook(idle_wfi);

#if defined(RT_USING_COMPONENTS_INIT)
    rt_components_board_init();
#endif

}

#endif
