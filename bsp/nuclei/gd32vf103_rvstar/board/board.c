/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-02     hqfang       first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#define SYSTICK_TICK_CONST                      (SOC_TIMER_FREQ / RT_TICK_PER_SECOND)
#define RT_KERNEL_INTERRUPT_LEVEL               1

#ifdef RT_USING_SERIAL
    #include <drv_usart.h>
#endif

/** _end symbol defined in linker script of Nuclei SDK */
extern void *_end;

/** _heap_end symbol defined in linker script of Nuclei SDK */
extern void *_heap_end;
#define HEAP_BEGIN  &_end
#define HEAP_END    &_heap_end

/*
 * - Implemented and defined in Nuclei SDK system_<Device>.c file
 * - Required macro NUCLEI_BANNER set to 0
 */
extern void _init(void);

/*
 * - Check MCU pin assignment here https://doc.nucleisys.com/nuclei_board_labs/hw/hw.html
 * - If you changed menuconfig to use different peripherals such as SPI, ADC, GPIO,
 *   HWTIMER, I2C, PWM, UART, WDT, RTC, please add or change related pinmux configuration
 *   code in functions(rt_hw_*_drvinit) below
 */

void rt_hw_spi_drvinit(void)
{

}

void rt_hw_adc_drvinit(void)
{

}

void rt_hw_gpio_drvinit(void)
{
    // Clock on all the GPIOs and AF
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_AF);
}

void rt_hw_hwtimer_drvinit(void)
{

}

void rt_hw_i2c_drvinit(void)
{

}

void rt_hw_pwm_drvinit(void)
{

}

void rt_hw_rtc_drvinit(void)
{

}

void rt_hw_uart_drvinit(void)
{
    /* Notice: Debug UART4 GPIO pins are already initialized in nuclei_sdk */

}

void rt_hw_wdt_drvinit(void)
{

}

void rt_hw_drivers_init(void)
{
#ifdef RT_USING_PIN
    rt_hw_gpio_drvinit();
#endif
#ifdef BSP_USING_UART
    rt_hw_uart_drvinit();
#endif
#ifdef BSP_USING_SPI
    rt_hw_spi_drvinit();
#endif
#ifdef BSP_USING_I2C
    rt_hw_i2c_drvinit();
#endif
#ifdef BSP_USING_ADC
    rt_hw_adc_drvinit();
#endif
#ifdef BSP_USING_WDT
    rt_hw_wdt_drvinit();
#endif
#ifdef BSP_USING_RTC
    rt_hw_rtc_drvinit();
#endif
#ifdef BSP_USING_HWTIMER
    rt_hw_hwtimer_drvinit();
#endif
#ifdef BSP_USING_PWM
    rt_hw_pwm_drvinit();
#endif
}

rt_weak void rt_hw_ticksetup(void)
{
    uint64_t ticks = SYSTICK_TICK_CONST;

    /* Make SWI and SysTick the lowest priority interrupts. */
    /* Stop and clear the SysTimer. SysTimer as Non-Vector Interrupt */
    SysTick_Config(ticks);
    ECLIC_DisableIRQ(SysTimer_IRQn);
    ECLIC_SetLevelIRQ(SysTimer_IRQn, RT_KERNEL_INTERRUPT_LEVEL);
    ECLIC_SetShvIRQ(SysTimer_IRQn, ECLIC_NON_VECTOR_INTERRUPT);
    ECLIC_EnableIRQ(SysTimer_IRQn);

    /* Set SWI interrupt level to lowest level/priority, SysTimerSW as Vector Interrupt */
    ECLIC_SetShvIRQ(SysTimerSW_IRQn, ECLIC_VECTOR_INTERRUPT);
    ECLIC_SetLevelIRQ(SysTimerSW_IRQn, RT_KERNEL_INTERRUPT_LEVEL);
    ECLIC_EnableIRQ(SysTimerSW_IRQn);
}

#define SysTick_Handler     eclic_mtip_handler

/**
 * @brief This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* Reload systimer */
    SysTick_Reload(SYSTICK_TICK_CONST);

    /* enter interrupt */
    rt_interrupt_enter();

    /* tick increase */
    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * @brief Setup hardware board for rt-thread
 *
 */
void rt_hw_board_init(void)
{
    /* OS Tick Configuration */
    rt_hw_ticksetup();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *) HEAP_BEGIN, (void *) HEAP_END);
#endif

    _init(); // __libc_init_array is not used in RT-Thread

    /* Board hardware drivers initialization */
    rt_hw_drivers_init();

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

/******************** end of file *******************/
