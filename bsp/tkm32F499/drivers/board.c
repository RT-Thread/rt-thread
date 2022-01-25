/*
 * Copyright (c) 2017-2019, MindMotion AE Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-02     spaceman           first version
 */
#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#include <drv_uart.h>
// extern uint32_t SystemCoreClock;
// extern void SystemInit(void);

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */

static void bsp_clock_config(void)
{
    RemapVtorTable();
    SystemClk_HSEInit(RCC_PLLMul_20);//启动PLL时钟，12MHz*20=240MHz
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2：2，全局性函数，仅需设置一次

    uint32_t sysclk = 0;
    getSystemClock(&sysclk);

    SysTick_Config(sysclk / RT_TICK_PER_SECOND);
    SysTick->CTRL |= 0x00000004UL;
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

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

void rt_hw_board_init()
{
    bsp_clock_config();
#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
    // volatile uint16_t i=0;
    // rt_hw_uart_init();
    // i = UINT16_MAX;
    // while(i--);     //wait for a while after uart initiated.
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
