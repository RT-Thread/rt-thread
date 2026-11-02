/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-21     seteiro      CH32V203C8T6-EVT-R0: linker heap like ch32v307v-r1
 */

#include "board.h"
#include <stdint.h>
#include "drv_usart.h"
#include "drv_gpio.h"
#include <rthw.h>
#include <rtthread.h>

extern uint32_t SystemCoreClock;

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    NVIC_SetPriority(SysTicK_IRQn, 0xf0);
    NVIC_SetPriority(Software_IRQn, 0xf0);
    NVIC_EnableIRQ(SysTicK_IRQn);
    NVIC_EnableIRQ(Software_IRQn);
    SysTick->CTLR = 0;
    SysTick->SR = 0;
    SysTick->CNT = 0;
    SysTick->CMP = ticks - 1;
    SysTick->CTLR = 0xF;
    return 0;
}

void rt_hw_board_init()
{
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init((void *) HEAP_BEGIN, (void *) HEAP_END);
#endif
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

#ifdef BSP_USING_USBD
#include "ch32v20x_usb.h"
extern int rt_hw_usbd_init(void);

static int board_usbd_init(void)
{
    RCC_ClocksTypeDef clocks;
    volatile int wait;

    RCC_GetClocksFreq(&clocks);
    if (clocks.SYSCLK_Frequency == 144000000)
        RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div3);
    else if (clocks.SYSCLK_Frequency == 96000000)
        RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div2);
    else if (clocks.SYSCLK_Frequency == 48000000)
        RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBFS, ENABLE);

    /* Same SIE reset the WCH USBFS device example does before enabling. */
    USBFSH->BASE_CTRL = USBFS_UC_RESET_SIE | USBFS_UC_CLR_ALL;
    for (wait = 0; wait < 200; wait++)
        ;
    USBFSH->BASE_CTRL = 0x00;

    return rt_hw_usbd_init();
}
INIT_DEVICE_EXPORT(board_usbd_init);
#endif

#if defined(BSP_USING_ADC1) && (defined(ADC_CHANNEL_16) || defined(ADC_CHANNEL_17))
static int board_adc_internal_on(void)
{
    /* Channels 16 and 17 stay near zero until this switch is on. */
    ADC_TempSensorVrefintCmd(ENABLE);
    return 0;
}
INIT_APP_EXPORT(board_adc_internal_on);
#endif

void SysTick_Handler(void) __attribute__((interrupt()));
void SysTick_Handler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    SysTick->SR = 0;
    rt_tick_increase();
    rt_interrupt_leave();
    FREE_INT_SP();
}
