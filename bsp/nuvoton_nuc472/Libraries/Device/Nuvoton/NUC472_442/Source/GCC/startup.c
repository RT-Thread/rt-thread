/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "string.h"

void __attribute__((weak))
Default_Handler(void);

// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions

void __attribute__ ((weak)) HardFault_Handler(void);
void __attribute__ ((weak)) PendSV_Handler(void);
void __attribute__ ((weak)) NMI_Handler(void);
void __attribute__ ((weak)) MemManage_Handler(void);
void __attribute__ ((weak)) BusFault_Handler(void);
void __attribute__ ((weak)) UsageFault_Handler(void);
void __attribute__ ((weak)) SVC_Handler(void);
void __attribute__ ((weak)) DebugMon_Handler(void);
void __attribute__ ((weak)) SysTick_Handler(void);
void __attribute__ ((weak)) BOD_IRQHandler(void);
void __attribute__ ((weak)) IRC_IRQHandler(void);
void __attribute__ ((weak)) PWRWU_IRQHandler(void);
void __attribute__ ((weak)) CLKF_IRQHandler(void);
void __attribute__ ((weak)) RTC_IRQHandler(void);
void __attribute__ ((weak)) TAMPER_IRQHandler(void);
void __attribute__ ((weak)) EINT0_IRQHandler(void);
void __attribute__ ((weak)) EINT1_IRQHandler(void);
void __attribute__ ((weak)) EINT2_IRQHandler(void);
void __attribute__ ((weak)) EINT3_IRQHandler(void);
void __attribute__ ((weak)) EINT4_IRQHandler(void);
void __attribute__ ((weak)) EINT5_IRQHandler(void);
void __attribute__ ((weak)) EINT6_IRQHandler(void);
void __attribute__ ((weak)) EINT7_IRQHandler(void);
void __attribute__ ((weak)) GPA_IRQHandler(void);
void __attribute__ ((weak)) GPB_IRQHandler(void);
void __attribute__ ((weak)) GPC_IRQHandler(void);
void __attribute__ ((weak)) GPD_IRQHandler(void);
void __attribute__ ((weak)) GPE_IRQHandler(void);
void __attribute__ ((weak)) GPF_IRQHandler(void);
void __attribute__ ((weak)) GPG_IRQHandler(void);
void __attribute__ ((weak)) GPH_IRQHandler(void);
void __attribute__ ((weak)) GPI_IRQHandler(void);
void __attribute__ ((weak)) TMR0_IRQHandler(void);
void __attribute__ ((weak)) TMR1_IRQHandler(void);
void __attribute__ ((weak)) TMR2_IRQHandler(void);
void __attribute__ ((weak)) TMR3_IRQHandler(void);
void __attribute__ ((weak)) PDMA_IRQHandler(void);
void __attribute__ ((weak)) ADC_IRQHandler(void);
void __attribute__ ((weak)) WDT_IRQHandler(void);
void __attribute__ ((weak)) WWDT_IRQHandler(void);
void __attribute__ ((weak)) EADC0_IRQHandler(void);
void __attribute__ ((weak)) EADC1_IRQHandler(void);
void __attribute__ ((weak)) EADC2_IRQHandler(void);
void __attribute__ ((weak)) EADC3_IRQHandler(void);
void __attribute__ ((weak)) ACMP_IRQHandler(void);
void __attribute__ ((weak)) OPA0_IRQHandler(void);
void __attribute__ ((weak)) OPA1_IRQHandler(void);
void __attribute__ ((weak)) ICAP0_IRQHandler(void);
void __attribute__ ((weak)) ICAP1_IRQHandler(void);
void __attribute__ ((weak)) PWM0CH0_IRQHandler(void);
void __attribute__ ((weak)) PWM0CH1_IRQHandler(void);
void __attribute__ ((weak)) PWM0CH2_IRQHandler(void);
void __attribute__ ((weak)) PWM0CH3_IRQHandler(void);
void __attribute__ ((weak)) PWM0CH4_IRQHandler(void);
void __attribute__ ((weak)) PWM0CH5_IRQHandler(void);
void __attribute__ ((weak)) PWM0_BRK_IRQHandler(void);
void __attribute__ ((weak)) QEI0_IRQHandler(void);
void __attribute__ ((weak)) PWM1CH0_IRQHandler(void);
void __attribute__ ((weak)) PWM1CH1_IRQHandler(void);
void __attribute__ ((weak)) PWM1CH2_IRQHandler(void);
void __attribute__ ((weak)) PWM1CH3_IRQHandler(void);
void __attribute__ ((weak)) PWM1CH4_IRQHandler(void);
void __attribute__ ((weak)) PWM1CH5_IRQHandler(void);
void __attribute__ ((weak)) PWM1_BRK_IRQHandler(void);
void __attribute__ ((weak)) QEI1_IRQHandler(void);
void __attribute__ ((weak)) EPWM0_IRQHandler(void);
void __attribute__ ((weak)) EPWM0BRK_IRQHandler(void);
void __attribute__ ((weak)) EPWM1_IRQHandler(void);
void __attribute__ ((weak)) EPWM1BRK_IRQHandler(void);
void __attribute__ ((weak)) USBD_IRQHandler(void);
void __attribute__ ((weak)) USBH_IRQHandler(void);
void __attribute__ ((weak)) USB_OTG_IRQHandler(void);
void __attribute__ ((weak)) EMAC_TX_IRQHandler(void);
void __attribute__ ((weak)) EMAC_RX_IRQHandler(void);
void __attribute__ ((weak)) SPI0_IRQHandler(void);
void __attribute__ ((weak)) SPI1_IRQHandler(void);
void __attribute__ ((weak)) SPI2_IRQHandler(void);
void __attribute__ ((weak)) SPI3_IRQHandler(void);
void __attribute__ ((weak)) UART0_IRQHandler(void);
void __attribute__ ((weak)) UART1_IRQHandler(void);
void __attribute__ ((weak)) UART2_IRQHandler(void);
void __attribute__ ((weak)) UART3_IRQHandler(void);
void __attribute__ ((weak)) UART4_IRQHandler(void);
void __attribute__ ((weak)) UART5_IRQHandler(void);
void __attribute__ ((weak)) I2C0_IRQHandler(void);
void __attribute__ ((weak)) I2C1_IRQHandler(void);
void __attribute__ ((weak)) I2C2_IRQHandler(void);
void __attribute__ ((weak)) I2C3_IRQHandler(void);
void __attribute__ ((weak)) I2C4_IRQHandler(void);
void __attribute__ ((weak)) SC0_IRQHandler(void);
void __attribute__ ((weak)) SC1_IRQHandler(void);
void __attribute__ ((weak)) SC2_IRQHandler(void);
void __attribute__ ((weak)) SC3_IRQHandler(void);
void __attribute__ ((weak)) SC4_IRQHandler(void);
void __attribute__ ((weak)) SC5_IRQHandler(void);
void __attribute__ ((weak)) CAN0_IRQHandler(void);
void __attribute__ ((weak)) CAN1_IRQHandler(void);
void __attribute__ ((weak)) I2S0_IRQHandler(void);
void __attribute__ ((weak)) I2S1_IRQHandler(void);
void __attribute__ ((weak)) SD_IRQHandler(void);
void __attribute__ ((weak)) PS2D_IRQHandler(void);
void __attribute__ ((weak)) CAP_IRQHandler(void);
void __attribute__ ((weak)) CRYPTO_IRQHandler(void);
void __attribute__ ((weak)) CRC_IRQHandler(void);

// ----------------------------------------------------------------------------

extern unsigned int  _estack;
// defined in linker script
extern unsigned char  _sidata;
// Begin address for the .data section// defined in linker script
extern unsigned char  _sdata;
// End address for the .data section// defined in linker script
extern unsigned char  _edata;
// Begin address for the .bss section// defined in linker script
extern unsigned char  __bss_start;
// End address for the .bss section// defined in linker script
extern unsigned char  __bss_end;

extern int entry(void);

typedef void (* const pHandler)(void);

// ----------------------------------------------------------------------------
static void Reset_Handler(void);

// The vector table.
// This relies on the linker script to place at correct location in memory.

__attribute__ ((section(".isr_vector"),used))
pHandler g_pfnVectors[] =
{
    (pHandler) &_estack,         //   0 The initial stack pointer
    Reset_Handler,               //   1 The reset handler
    NMI_Handler,                 //   2 The NMI handler
    HardFault_Handler,           //   3 The hard fault handler
    MemManage_Handler,           //   4 Reserved
    BusFault_Handler,            //   5 Reserved
    UsageFault_Handler,          //   6 Reserved
    0,                           //   7 Reserved
    0,                           //   8 Reserved
    0,                           //   9 Reserved
    0,                           //  10 Reserved
    SVC_Handler,                 //  11 SVCall handler
    DebugMon_Handler,            //  12 Reserved
    0,                           //  13 Reserved
    PendSV_Handler,              //  14 The PendSV handler
    SysTick_Handler,             //  15 The SysTick handler

	// ----------------------------------------------------------------------

    BOD_IRQHandler,              //  16 Brown Out detection
    IRC_IRQHandler,              //  17 Internal RC
    PWRWU_IRQHandler,            //  18 Power Down Wake Up
    Default_Handler,             //  19 Reserved.
    CLKF_IRQHandler,             //  20 CLKF
    Default_Handler,             //  21 Reserved.
    RTC_IRQHandler,              //  22 Real Time Clock
    TAMPER_IRQHandler,           //  23 Tamper detection
    EINT0_IRQHandler,            //  24 External Input 0
    EINT1_IRQHandler,            //  25 External Input 1
    EINT2_IRQHandler,            //  26 External Input 2
    EINT3_IRQHandler,            //  27 External Input 3
    EINT4_IRQHandler,            //  28 External Input 4
    EINT5_IRQHandler,            //  29 External Input 5
    EINT6_IRQHandler,            //  30 External Input 6
    EINT7_IRQHandler,            //  31 External Input 7
    GPA_IRQHandler,              //  32 GPIO Port A
    GPB_IRQHandler,              //  33 GPIO Port B
    GPC_IRQHandler,              //  34 GPIO Port C
    GPD_IRQHandler,              //  35 GPIO Port D
    GPE_IRQHandler,              //  36 GPIO Port E
    GPF_IRQHandler,              //  37 GPIO Port F
    GPG_IRQHandler,              //  38 GPIO Port G
    GPH_IRQHandler,              //  39 GPIO Port H
    GPI_IRQHandler,              //  40 GPIO Port I
    Default_Handler,             //  41 Reserved.
    Default_Handler,             //  42 Reserved.
    Default_Handler,             //  43 Reserved.
    Default_Handler,             //  44 Reserved.
    Default_Handler,             //  45 Reserved.
    Default_Handler,             //  46 Reserved.
    Default_Handler,             //  47 Reserved.
    TMR0_IRQHandler,             //  48 Timer 0
    TMR1_IRQHandler,             //  49 Timer 1
    TMR2_IRQHandler,             //  50 Timer 2
    TMR3_IRQHandler,             //  51 Timer 3
    Default_Handler,             //  52 Reserved.
    Default_Handler,             //  53 Reserved.
    Default_Handler,             //  54 Reserved.
    Default_Handler,             //  55 Reserved.
    PDMA_IRQHandler,             //  56 Peripheral DMA
    Default_Handler,             //  57 Reserved.
    ADC_IRQHandler,              //  58 ADC
    Default_Handler,             //  59 Reserved.
    Default_Handler,             //  60 Reserved.
    Default_Handler,             //  61 Reserved.
    WDT_IRQHandler,              //  62 Watch Dog Timer
    WWDT_IRQHandler,             //  63 Window Watch Dog Timer
    EADC0_IRQHandler,            //  64 EADC 0
    EADC1_IRQHandler,            //  65 EADC 1
    EADC2_IRQHandler,            //  66 EADC 2
    EADC3_IRQHandler,            //  67 EADC 3
    Default_Handler,             //  68 Reserved.
    Default_Handler,             //  69 Reserved.
    Default_Handler,             //  70 Reserved.
    Default_Handler,             //  71 Reserved.
    ACMP_IRQHandler,             //  72 Analog Comparator
    Default_Handler,             //  73 Reserved.
    Default_Handler,             //  74 Reserved.
    Default_Handler,             //  75 Reserved.
    OPA0_IRQHandler,             //  76 OPA 0
    OPA1_IRQHandler,             //  77 OPA 1
    ICAP0_IRQHandler,            //  78 ICAP 0
    ICAP1_IRQHandler,            //  79 ICAP 1
    PWM0CH0_IRQHandler,          //  80 PWMA CH0
    PWM0CH1_IRQHandler,          //  81 PWMA CH1
    PWM0CH2_IRQHandler,          //  82 PWMA CH2
    PWM0CH3_IRQHandler,          //  83 PWMA CH3
    PWM0CH4_IRQHandler,          //  84 PWMA CH4
    PWM0CH5_IRQHandler,          //  85 PWMA CH5
    PWM0_BRK_IRQHandler,         //  86 PWMA Brake
    QEI0_IRQHandler,             //  87 QEI 0
    PWM1CH0_IRQHandler,          //  88 PWM1 CH0
    PWM1CH1_IRQHandler,          //  89 PWM1 CH1
    PWM1CH2_IRQHandler,          //  90 PWM1 CH2
    PWM1CH3_IRQHandler,          //  91 PWM1 CH3
    PWM1CH4_IRQHandler,          //  92 PWM1 CH4
    PWM1CH5_IRQHandler,          //  93 PWM1 CH5
    PWM1_BRK_IRQHandler,         //  94 PWM1 Brake
    QEI1_IRQHandler,             //  95 QEI 1
    EPWM0_IRQHandler,            //  96 EPWM0
    EPWM0BRK_IRQHandler,         //  97 EPWM0 Brake
    EPWM1_IRQHandler,            //  98 EPWM1
    EPWM1BRK_IRQHandler,         //  99 EPWM1 Brake
    Default_Handler,             // 100 Reserved.
    Default_Handler,             // 101 Reserved.
    Default_Handler,             // 102 Reserved.
    Default_Handler,             // 103 Reserved.
    USBD_IRQHandler,             // 104 USB Device
    USBH_IRQHandler,             // 105 USB Host
    USB_OTG_IRQHandler,          // 106 USB OTG
    Default_Handler,             // 107 Reserved.
    EMAC_TX_IRQHandler,          // 108 Ethernet MAC TX
    EMAC_RX_IRQHandler,          // 109 Ethernet MAC RX
    Default_Handler,             // 110 Reserved.
    Default_Handler,             // 111 Reserved.
    SPI0_IRQHandler,             // 112 SPI 0
    SPI1_IRQHandler,             // 113 SPI 1
    SPI2_IRQHandler,             // 114 SPI 2
    SPI3_IRQHandler,             // 115 SPI 3
    Default_Handler,             // 116 Reserved.
    Default_Handler,             // 117 Reserved.
    Default_Handler,             // 118 Reserved.
    Default_Handler,             // 119 Reserved.
    UART0_IRQHandler,            // 120 UART 0
    UART1_IRQHandler,            // 121 UART 1
    UART2_IRQHandler,            // 122 UART 2
    UART3_IRQHandler,            // 123 UART 3
    UART4_IRQHandler,            // 124 UART 4
    UART5_IRQHandler,            // 125 UART 5
    Default_Handler,             // 126 Reserved.
    Default_Handler,             // 127 Reserved.
    I2C0_IRQHandler,             // 128 I2C 0
    I2C1_IRQHandler,             // 129 I2C 1
    I2C2_IRQHandler,             // 130 I2C 2
    I2C3_IRQHandler,             // 131 I2C 3
    I2C4_IRQHandler,             // 132 I2C 4
    Default_Handler,             // 133 Reserved.
    Default_Handler,             // 134 Reserved.
    Default_Handler,             // 135 Reserved.
    SC0_IRQHandler,              // 136 Smart Card 0
    SC1_IRQHandler,               // 137 Smart Card 1
    SC2_IRQHandler,              // 138 Smart Card 2
    SC3_IRQHandler,              // 139 Smart Card 3
    SC4_IRQHandler,              // 140 Smart Card 4
    SC5_IRQHandler,              // 141 Smart Card 5
    Default_Handler,             // 142 Reserved.
    Default_Handler,             // 143 Reserved.
    CAN0_IRQHandler,             // 144 CAN 0
    CAN1_IRQHandler,             // 145 CAN 1
    Default_Handler,             // 146 Reserved.
    Default_Handler,             // 147 Reserved.
    I2S0_IRQHandler,             // 148 I2S 0
    I2S1_IRQHandler,             // 149 I2S 1
    Default_Handler,             // 150 Reserved.
    Default_Handler,             // 151 Reserved.
    SD_IRQHandler,               // 152 SD card
    Default_Handler,             // 153 Reserved.
    PS2D_IRQHandler,             // 154 PS/2 device
    CAP_IRQHandler,              // 155 CAP
    CRYPTO_IRQHandler,           // 156 CRYPTO
    CRC_IRQHandler,              // 157 CRC
};

void _start()
{
    memcpy(&_sdata, &_sidata, &_edata - &_sdata);
    memset(&__bss_start, 0, &__bss_end - &__bss_start);
}

static void Reset_Handler(void)
{
	_start();
	entry();
}

// ----------------------------------------------------------------------------

void __attribute__ ((section(".after_vectors")))
Default_Handler(void)
{
  while (1)
    {
    }
}

// ----------------------------------------------------------------------------
