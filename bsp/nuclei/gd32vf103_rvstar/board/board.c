/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
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
#include "cpuport.h"

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

// Check pin assignment here https://doc.nucleisys.com/nuclei_board_labs/hw/hw.html

void rt_hw_spi_drvinit(void)
{
    /* Comments below are sample configuration code for 
     * Configure PA5 PA6 PA7 (SPI0 SCK MISO MOSI) as alternate function
     * gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_7);
     * gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
     */
}

void rt_hw_adc_drvinit(void)
{
    /* Comments below are sample configuration code for 
     * Configure PA0, PA3 as analog mode
     * gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_3);
     */
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
    /* Comments below are sample configuration code for 
     * Configure PB10 PB11 (I2C1 SCL SDA) as alternate function
     * gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10 | GPIO_PIN_11);
     */
}

void rt_hw_pwm_drvinit(void)
{
    /* Comments below are sample configuration code for 
     * Configure PA6 PA7 PB0 PB1(TIMER2 CH0 CH1 CH2 CH3) as alternate function
     * gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
     * gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
     */
}

void rt_hw_rtc_drvinit(void)
{

}

void rt_hw_uart_drvinit(void)
{
    // Debug UART4 GPIO pins are already initialized in nuclei_sdk

    /* Comments below are sample configuration code for 
     * Configure PC10 PC11(UART3 TX RX) as alternate function
     * gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
     * gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
     */
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
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

}

/******************** end of file *******************/

