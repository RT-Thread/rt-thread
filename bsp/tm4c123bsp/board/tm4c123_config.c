#include "stdbool.h"
#include "stdint.h"
#include "hw_memmap.h"
#include "pin_map.h"
#include "sysctl.h"
#include "pwm.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "ssi.h"

#include "tm4c123_config.h"




void uart_hw_config(void)
{
	  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	  GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
	  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	  GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	  
}



void pwm_hw_config(void)
{
	SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
   //GPIO port D needs to be enabled so these pins can be used.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

     // Configure the GPIO pin muxing to select PWM functions for these pins.
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);

     // Configure the GPIO pad for PWM function on pins PF2 and PF3
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3);	
	 
}


void adc_hw_config(void)
{
    // The ADC0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    // GPIO port D needs to be enabled
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Select the analog ADC function for these pins.
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); 
}


void  spi_hw_config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    //GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_2);

}

