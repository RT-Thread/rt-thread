/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-05     qinweizhong  add support for tae32
 */
#include "board.h"

#define _SCB_BASE       (0xE000E010UL)
#define _SYSTICK_CTRL   (*(rt_uint32_t *)(_SCB_BASE + 0x0))
#define _SYSTICK_LOAD   (*(rt_uint32_t *)(_SCB_BASE + 0x4))
#define _SYSTICK_VAL    (*(rt_uint32_t *)(_SCB_BASE + 0x8))
#define _SYSTICK_CALIB  (*(rt_uint32_t *)(_SCB_BASE + 0xC))
#define _SYSTICK_PRI    (*(rt_uint8_t  *)(0xE000ED23UL))

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    if ((ticks - 1) > 0xFFFFFF)
    {
        return 1;
    }

    _SYSTICK_LOAD = ticks - 1;
    _SYSTICK_PRI = 0x01;
    _SYSTICK_VAL  = 0;
    _SYSTICK_CTRL = 0x07;

    return 0;
}

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 2048
static uint32_t rt_heap[RT_HEAP_SIZE];/* heap default size: 4K(1024 * 4)*/
rt_weak void *rt_heap_begin_get(void)
{
    return rt_heap;
}

rt_weak void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    /* System Clock Update */
    SystemClock_Config();
    /* System Tick Configuration */
    LL_Init();
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            /*Wait TXFIFO to be no full*/
            while (!__LL_UART_IsTxFIFONotFull(UART0)) {};

            /*Send data to UART*/
            __LL_UART_TxBuf9bits_Write(UART0, (uint16_t)a);
        }
        while (!__LL_UART_IsTxFIFONotFull(UART0)) {};

        /*Send data to UART*/
        __LL_UART_TxBuf9bits_Write(UART0, (uint16_t)(*(str + i)));
    }
}

char rt_hw_console_getchar(void)
{
    /* note: ch default value < 0 */
    int ch = -1;
    if (__LL_UART_IsDatReady(UART0))
    {
        /* receive data */
        ch = __LL_UART_RxBuf9bits_Read(UART0);
    }
    else
    {
        rt_thread_mdelay(10);
    }
    return ch;
}

void SystemClock_Config(void)
{
    LL_StatusETypeDef ret;
    SYSCTRL_SysclkUserCfgTypeDef sysclk_cfg;

    /*FPLL0 Init*/
    LL_FPLL_Init(FPLL0);

    /*SYSCLK Clock Config*/
    sysclk_cfg.sysclk_src = SYSCLK_SRC_PLL0DivClk;
    sysclk_cfg.sysclk_freq = 90000000UL;
    sysclk_cfg.pll0clk_src = PLLCLK_SRC_XOSC;
    sysclk_cfg.pll0clk_src_freq = HSE_VALUE;
    sysclk_cfg.apb0_clk_div = SYSCTRL_CLK_DIV_1;
    sysclk_cfg.apb1_clk_div = SYSCTRL_CLK_DIV_1;
    ret = LL_SYSCTRL_SysclkInit(SYSCTRL, &sysclk_cfg);

    if (ret == LL_OK)
    {
        SystemCoreClockUpdate(sysclk_cfg.sysclk_freq);
    }

    /*eFlash Memory CLK Source and Div Config*/
    LL_SYSCTRL_EFLASH_ClkCfg(EFLASH_CLK_SRC_PLL0DivClk, SYSCTRL_CLK_DIV_9);
}
