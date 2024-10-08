/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */
#include "board.h"
#include "drv_common.h"
#include "drv_gpio.h"
#include "drv_usart_v2.h"

uint32_t SystemCoreClock;
extern const uint32_t __isr_start_address;


const uint32_t __attribute__((section (".app_info")))
    g_CAppInfo[256] =
{
    __APP_START_MAGIC__,
    sizeof(g_CAppInfo),
    0,
    0,
};

void SystemInit(void)
{
#ifdef __USE_XTL__
    SYSCTRL->FREQ_SEL = 0x20000000 | SYSCTRL_FREQ_SEL_HCLK_DIV_1_2 | (1 << 13) | SYSCTRL_FREQ_SEL_CLOCK_SOURCE_EXT | SYSCTRL_FREQ_SEL_XTAL_192Mhz;
#else
    SYSCTRL->FREQ_SEL = 0x20000000 | SYSCTRL_FREQ_SEL_HCLK_DIV_1_2 | (1 << 13) | SYSCTRL_FREQ_SEL_CLOCK_SOURCE_INC | SYSCTRL_FREQ_SEL_XTAL_192Mhz;
#endif
    SCB->VTOR = (uint32_t)(&__isr_start_address);
    SYSCTRL->CG_CTRL1 = SYSCTRL_APBPeriph_ALL;
    SYSCTRL->SOFT_RST1 = SYSCTRL_APBPeriph_ALL;
    SYSCTRL->PHER_CTRL &= ~(1 << 20);
    SYSCTRL->SOFT_RST2 &= ~SYSCTRL_USB_RESET;
    SYSCTRL->LOCK_R |= SYSCTRL_USB_RESET;
    __enable_irq();
}

void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency */
{
    SystemCoreClock = HSE_VALUE * (((SYSCTRL->FREQ_SEL & SYSCTRL_FREQ_SEL_XTAL_Mask) >> SYSCTRL_FREQ_SEL_XTAL_Pos) + 1);
}

void rt_hw_board_init(void)
{
    GPIO_Config(GPIOC_03, 0, 0);
    GPIO_Config(GPIOD_14, 0, 0);
    GPIO_Config(GPIOD_15, 0, 0);
    __NVIC_SetPriorityGrouping(7 - __NVIC_PRIO_BITS);
    SystemCoreClockUpdate();
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
    rt_hw_systick_init();
    DMA_GlobalInit();
    Uart_GlobalInit();
    DMA_TakeStream(DMA1_STREAM_1);/* for qspi */
    CoreTick_Init();
#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif

    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

}


