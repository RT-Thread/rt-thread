/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#include "drv_common.h"
#include <board.h>

#ifdef RT_USING_PIN
#include <drv_gpio.h>
#endif

#ifdef RT_USING_SERIAL
#ifdef RT_USING_SERIAL_V2
#include <drv_usart_v2.h>
#else
#include <drv_uart.h>
#endif /* RT_USING_SERIAL */
#endif /* RT_USING_SERIAL_V2 */

#define DBG_TAG "drv_common"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */

/* SysTick configuration */
void rt_hw_systick_init(void)
{
    /* update the system core clock value */
    SystemCoreClockUpdate();
    /* initialize systick(base time) */
    SysTick_Config(SystemCoreClock / SYSTICK_TIME_UNIT);
    /* systick interrupt control */
    Systick_setInterrupt(ENABLE);

    NVIC_SetPriority(SysTick_IRQn, 0x0F);
}

/**
 * This is the timer interrupt service routine.
 *
 */
volatile rt_tick_t g_tick_test;

void SysTick_Handler(void)
{
    rt_interrupt_enter();

    rt_tick_increase();
    g_tick_test = rt_tick_get();

    rt_interrupt_leave();
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char *s, int num)
{
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    LOG_E("Error_Handler at file:%s num:%d", s, num);
    while (1)
    {
    }
    /* USER CODE END Error_Handler */
}

/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint64_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * (reload / (1000000 / RT_TICK_PER_SECOND));
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

#define BSP_SCB_ENABLE_I_CACHE
#define BSP_SCB_ENABLE_D_CACHE
/**
 * This function will initial NS800 board.
 */
rt_weak void rt_hw_board_init(void)
{
#ifdef BSP_SCB_ENABLE_I_CACHE
    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();
#endif

#ifdef BSP_SCB_ENABLE_D_CACHE
    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();
#endif

    /* Initialize device clock and peripherals */
    Device_init();
    /* Disable peripheral register locks */
    Device_unlockPeriphReg();
    /* Interrupt initialization. Disable global interrupts. */
    Interrupt_initModule();
    Interrupt_initVectorTable();

    rt_hw_systick_init();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif

#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* Set the shell console output device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_NANO)
    extern void rt_hw_console_init(void);
    rt_hw_console_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* Board underlying hardware initialization */
    rt_components_board_init();
#endif
}
#ifdef RT_USING_CONSOLE

void rt_hw_console_output(const char *str)
{
#if defined(__ICCARM__)
    rt_size_t size = rt_strlen(str);

    __write(0, str, size);
#else
    rt_size_t i = 0, size = 0;
    char a = '\r';
    FILE f;

    size = rt_strlen(str);

    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            fputc(a, &f);
        }
        fputc(str[i], &f);
    }
#endif
}
#endif

#ifdef RT_USING_FINSH
char rt_hw_console_getchar(void)
{
    /* Note: the initial value of ch must < 0 */
    int ch = -1;

    if (UART1->STAT.BIT.RDRF)
    {
        ch = (uint8_t)UART1->DATA.WORDVAL;
    }
    else
    {
        rt_thread_mdelay(10);
    }
    return ch;
}
#endif

