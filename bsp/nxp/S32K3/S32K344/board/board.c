/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-16     Pillar       first version
 */

#include "board.h"

static inline uint32_t SysTick_Config(uint32_t ticks)
{
    if ((ticks - 1UL) > S32_SysTick_RVR_RELOAD_MASK)
    {
        return 1;
    }

    S32_SysTick->RVR  = (uint32_t)(ticks - 1UL);
    S32_SysTick->CVR  = 0UL;
    S32_SysTick->CSRr = S32_SysTick_CSR_ENABLE(1)   |
                        S32_SysTick_CSR_TICKINT(1)  |
                        S32_SysTick_CSR_CLKSOURCE(1);
    return 0;
}

#define UART_CONSOLE_CHANNEL 0
#define UART_TIMEOUT    ((uint32)0xFFFFFFFF)

void rt_hw_console_output(const char *str)
{
    rt_enter_critical();

    while (*str != '\0')
    {
        if (*str == '\n')
        {
            Uart_SyncSend(UART_CONSOLE_CHANNEL, (const uint8 *)"\r", 1, UART_TIMEOUT);
        }
        Uart_SyncSend(UART_CONSOLE_CHANNEL, str++, 1, UART_TIMEOUT);
    }

    rt_exit_critical();
}

char rt_hw_console_getchar(void)
{
    char ch = -1;
    uint32 remaining;

    if (Uart_AsyncReceive(UART_CONSOLE_CHANNEL, (uint8 *)&ch, 1) != E_OK)
    {
        ch = -1;
    }
    rt_thread_mdelay(5);
    return ch;
}

#define SYSCLK 48000000

void rt_hw_board_init(void)
{
    SysTick_Config(SYSCLK / RT_TICK_PER_SECOND);

#if defined(RT_USING_HEAP)
    /* Heap initialization */
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* Initialize the Mcu driver */
    Mcu_Init(NULL_PTR);

    Mcu_InitClock(0);
#if (MCU_NO_PLL == STD_OFF)
    while (MCU_PLL_LOCKED != Mcu_GetPllStatus());
    Mcu_DistributePllClock();
#endif
    Mcu_SetMode(0);

    /* Initialize all pins using the Port driver */
    Port_Init(NULL_PTR);

    /* Initialize IRQs */
    Platform_Init(NULL_PTR);

    /* Initializes an UART driver*/
    Uart_Init(NULL_PTR);
}
