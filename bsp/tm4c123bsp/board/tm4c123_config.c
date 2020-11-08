/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#include <rtthread.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "tm4c123_config.h"

#ifdef RT_USING_SERIAL
    #include "driverlib/uart.h"
#endif /* RT_USING_SERIAL */
#ifdef RT_USING_ADC
    #include "driverlib/adc.h"
#endif /* RT_USING_ADC */
#ifdef RT_USING_PWM
    #include "driverlib/pwm.h"
#endif /* RT_USING_PWM */
#ifdef RT_USING_SPI
    #include "driverlib/ssi.h"
#endif /* RT_USING_SPI */


#ifdef RT_USING_SERIAL
void uart_hw_config(void)
{
    /* UART0 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    /* UART1 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
}
#endif /* RT_USING_SERIAL */

#ifdef RT_USING_ADC
void adc_hw_config(void)
{
    /* ADC0 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
}
#endif /* RT_USING_ADC */

#ifdef RT_USING_PWM
void pwm_hw_config(void)
{
    /* PWM7 (PWM1 module,M1PWM6 and M1PWM7) */
    SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);
}
#endif /* RT_USING_PWM */

#ifdef RT_USING_SPI
void  spi_hw_config(void)
{
    /* SPI0 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_2);
}
#endif /* RT_USING_SPI */

/************************** end of file ******************/