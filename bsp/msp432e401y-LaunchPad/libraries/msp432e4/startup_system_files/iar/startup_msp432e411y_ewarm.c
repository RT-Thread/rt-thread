//*****************************************************************************
//
// Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  Redistributions of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the
//  documentation and/or other materials provided with the
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// MSP432 Startup Code and interrupt vectors for IAR Embedded Workbench for ARM
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// Enable the IAR extensions for this source file.
//
//*****************************************************************************
#pragma language=extended
#pragma segment="CSTACK"

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
extern void Reset_Handler(void);
static void Default_Handler(void);

extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

/* device specific interrupt handler */
extern void GPIOA_IRQHandler(void);
extern void GPIOB_IRQHandler(void);
extern void GPIOC_IRQHandler(void);
extern void GPIOD_IRQHandler(void);
extern void GPIOE_IRQHandler(void);
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void SSI0_IRQHandler(void);
extern void I2C0_IRQHandler(void);
extern void PWM0_FAULT_IRQHandler(void);
extern void PWM0_0_IRQHandler(void);
extern void PWM0_1_IRQHandler(void);
extern void PWM0_2_IRQHandler(void);
extern void QEI0_IRQHandler(void);
extern void ADC0SS0_IRQHandler(void);
extern void ADC0SS1_IRQHandler(void);
extern void ADC0SS2_IRQHandler(void);
extern void ADC0SS3_IRQHandler(void);
extern void WATCHDOG_IRQHandler(void);
extern void TIMER0A_IRQHandler(void);
extern void TIMER0B_IRQHandler(void);
extern void TIMER1A_IRQHandler(void);
extern void TIMER1B_IRQHandler(void);
extern void TIMER2A_IRQHandler(void);
extern void TIMER2B_IRQHandler(void);
extern void COMP0_IRQHandler(void);
extern void COMP1_IRQHandler(void);
extern void COMP2_IRQHandler(void);
extern void SYSCTL_IRQHandler(void);
extern void FLASH_IRQHandler(void);
extern void GPIOF_IRQHandler(void);
extern void GPIOG_IRQHandler(void);
extern void GPIOH_IRQHandler(void);
extern void UART2_IRQHandler(void);
extern void SSI1_IRQHandler(void);
extern void TIMER3A_IRQHandler(void);
extern void TIMER3B_IRQHandler(void);
extern void I2C1_IRQHandler(void);
extern void CAN0_IRQHandler(void);
extern void CAN1_IRQHandler(void);
extern void EMAC0_IRQHandler(void);
extern void HIBERNATE_IRQHandler(void);
extern void USB0_IRQHandler(void);
extern void PWM0_3_IRQHandler(void);
extern void UDMA_IRQHandler(void);
extern void UDMAERR_IRQHandler(void);
extern void ADC1SS0_IRQHandler(void);
extern void ADC1SS1_IRQHandler(void);
extern void ADC1SS2_IRQHandler(void);
extern void ADC1SS3_IRQHandler(void);
extern void EPI0_IRQHandler(void);
extern void GPIOJ_IRQHandler(void);
extern void GPIOK_IRQHandler(void);
extern void GPIOL_IRQHandler(void);
extern void SSI2_IRQHandler(void);
extern void SSI3_IRQHandler(void);
extern void UART3_IRQHandler(void);
extern void UART4_IRQHandler(void);
extern void UART5_IRQHandler(void);
extern void UART6_IRQHandler(void);
extern void UART7_IRQHandler(void);
extern void I2C2_IRQHandler(void);
extern void I2C3_IRQHandler(void);
extern void TIMER4A_IRQHandler(void);
extern void TIMER4B_IRQHandler(void);
extern void TIMER5A_IRQHandler(void);
extern void TIMER5B_IRQHandler(void);
extern void SYSEXC_IRQHandler(void);
extern void I2C4_IRQHandler(void);
extern void I2C5_IRQHandler(void);
extern void GPIOM_IRQHandler(void);
extern void GPION_IRQHandler(void);
extern void TAMPER0_IRQHandler(void);
extern void GPIOP0_IRQHandler(void);
extern void GPIOP1_IRQHandler(void);
extern void GPIOP2_IRQHandler(void);
extern void GPIOP3_IRQHandler(void);
extern void GPIOP4_IRQHandler(void);
extern void GPIOP5_IRQHandler(void);
extern void GPIOP6_IRQHandler(void);
extern void GPIOP7_IRQHandler(void);
extern void GPIOQ0_IRQHandler(void);
extern void GPIOQ1_IRQHandler(void);
extern void GPIOQ2_IRQHandler(void);
extern void GPIOQ3_IRQHandler(void);
extern void GPIOQ4_IRQHandler(void);
extern void GPIOQ5_IRQHandler(void);
extern void GPIOQ6_IRQHandler(void);
extern void GPIOQ7_IRQHandler(void);
extern void GPIOR_IRQHandler(void);
extern void GPIOS_IRQHandler(void);
extern void SHA0_IRQHandler(void);
extern void AES0_IRQHandler(void);
extern void DES0_IRQHandler(void);
extern void LCD0_IRQHandler(void);
extern void TIMER6A_IRQHandler(void);
extern void TIMER6B_IRQHandler(void);
extern void TIMER7A_IRQHandler(void);
extern void TIMER7B_IRQHandler(void);
extern void I2C6_IRQHandler(void);
extern void I2C7_IRQHandler(void);
extern void ONEWIRE0_IRQHandler(void);
extern void I2C8_IRQHandler(void);
extern void I2C9_IRQHandler(void);
extern void GPIOT_IRQHandler(void);

/* Cortex-M4 Processor Exceptions */
#pragma weak NMI_Handler=Default_Handler
#pragma weak HardFault_Handler=Default_Handler
#pragma weak MemManage_Handler=Default_Handler
#pragma weak BusFault_Handler=Default_Handler
#pragma weak UsageFault_Handler=Default_Handler
#pragma weak SVC_Handler=Default_Handler
#pragma weak DebugMon_Handler=Default_Handler
#pragma weak PendSV_Handler=Default_Handler
#pragma weak SysTick_Handler=Default_Handler

/* device specific interrupt handler */
#pragma weak GPIOA_IRQHandler=Default_Handler
#pragma weak GPIOB_IRQHandler=Default_Handler
#pragma weak GPIOC_IRQHandler=Default_Handler
#pragma weak GPIOD_IRQHandler=Default_Handler
#pragma weak GPIOE_IRQHandler=Default_Handler
#pragma weak UART0_IRQHandler=Default_Handler
#pragma weak UART1_IRQHandler=Default_Handler
#pragma weak SSI0_IRQHandler=Default_Handler
#pragma weak I2C0_IRQHandler=Default_Handler
#pragma weak PWM0_FAULT_IRQHandler=Default_Handler
#pragma weak PWM0_0_IRQHandler=Default_Handler
#pragma weak PWM0_1_IRQHandler=Default_Handler
#pragma weak PWM0_2_IRQHandler=Default_Handler
#pragma weak QEI0_IRQHandler=Default_Handler
#pragma weak ADC0SS0_IRQHandler=Default_Handler
#pragma weak ADC0SS1_IRQHandler=Default_Handler
#pragma weak ADC0SS2_IRQHandler=Default_Handler
#pragma weak ADC0SS3_IRQHandler=Default_Handler
#pragma weak WATCHDOG_IRQHandler=Default_Handler
#pragma weak TIMER0A_IRQHandler=Default_Handler
#pragma weak TIMER0B_IRQHandler=Default_Handler
#pragma weak TIMER1A_IRQHandler=Default_Handler
#pragma weak TIMER1B_IRQHandler=Default_Handler
#pragma weak TIMER2A_IRQHandler=Default_Handler
#pragma weak TIMER2B_IRQHandler=Default_Handler
#pragma weak COMP0_IRQHandler=Default_Handler
#pragma weak COMP1_IRQHandler=Default_Handler
#pragma weak COMP2_IRQHandler=Default_Handler
#pragma weak SYSCTL_IRQHandler=Default_Handler
#pragma weak FLASH_IRQHandler=Default_Handler
#pragma weak GPIOF_IRQHandler=Default_Handler
#pragma weak GPIOG_IRQHandler=Default_Handler
#pragma weak GPIOH_IRQHandler=Default_Handler
#pragma weak UART2_IRQHandler=Default_Handler
#pragma weak SSI1_IRQHandler=Default_Handler
#pragma weak TIMER3A_IRQHandler=Default_Handler
#pragma weak TIMER3B_IRQHandler=Default_Handler
#pragma weak I2C1_IRQHandler=Default_Handler
#pragma weak CAN0_IRQHandler=Default_Handler
#pragma weak CAN1_IRQHandler=Default_Handler
#pragma weak EMAC0_IRQHandler=Default_Handler
#pragma weak HIBERNATE_IRQHandler=Default_Handler
#pragma weak USB0_IRQHandler=Default_Handler
#pragma weak PWM0_3_IRQHandler=Default_Handler
#pragma weak UDMA_IRQHandler=Default_Handler
#pragma weak UDMAERR_IRQHandler=Default_Handler
#pragma weak ADC1SS0_IRQHandler=Default_Handler
#pragma weak ADC1SS1_IRQHandler=Default_Handler
#pragma weak ADC1SS2_IRQHandler=Default_Handler
#pragma weak ADC1SS3_IRQHandler=Default_Handler
#pragma weak EPI0_IRQHandler=Default_Handler
#pragma weak GPIOJ_IRQHandler=Default_Handler
#pragma weak GPIOK_IRQHandler=Default_Handler
#pragma weak GPIOL_IRQHandler=Default_Handler
#pragma weak SSI2_IRQHandler=Default_Handler
#pragma weak SSI3_IRQHandler=Default_Handler
#pragma weak UART3_IRQHandler=Default_Handler
#pragma weak UART4_IRQHandler=Default_Handler
#pragma weak UART5_IRQHandler=Default_Handler
#pragma weak UART6_IRQHandler=Default_Handler
#pragma weak UART7_IRQHandler=Default_Handler
#pragma weak I2C2_IRQHandler=Default_Handler
#pragma weak I2C3_IRQHandler=Default_Handler
#pragma weak TIMER4A_IRQHandler=Default_Handler
#pragma weak TIMER4B_IRQHandler=Default_Handler
#pragma weak TIMER5A_IRQHandler=Default_Handler
#pragma weak TIMER5B_IRQHandler=Default_Handler
#pragma weak SYSEXC_IRQHandler=Default_Handler
#pragma weak I2C4_IRQHandler=Default_Handler
#pragma weak I2C5_IRQHandler=Default_Handler
#pragma weak GPIOM_IRQHandler=Default_Handler
#pragma weak GPION_IRQHandler=Default_Handler
#pragma weak TAMPER0_IRQHandler=Default_Handler
#pragma weak GPIOP0_IRQHandler=Default_Handler
#pragma weak GPIOP1_IRQHandler=Default_Handler
#pragma weak GPIOP2_IRQHandler=Default_Handler
#pragma weak GPIOP3_IRQHandler=Default_Handler
#pragma weak GPIOP4_IRQHandler=Default_Handler
#pragma weak GPIOP5_IRQHandler=Default_Handler
#pragma weak GPIOP6_IRQHandler=Default_Handler
#pragma weak GPIOP7_IRQHandler=Default_Handler
#pragma weak GPIOQ0_IRQHandler=Default_Handler
#pragma weak GPIOQ1_IRQHandler=Default_Handler
#pragma weak GPIOQ2_IRQHandler=Default_Handler
#pragma weak GPIOQ3_IRQHandler=Default_Handler
#pragma weak GPIOQ4_IRQHandler=Default_Handler
#pragma weak GPIOQ5_IRQHandler=Default_Handler
#pragma weak GPIOQ6_IRQHandler=Default_Handler
#pragma weak GPIOQ7_IRQHandler=Default_Handler
#pragma weak GPIOR_IRQHandler=Default_Handler
#pragma weak GPIOS_IRQHandler=Default_Handler
#pragma weak SHA0_IRQHandler=Default_Handler
#pragma weak AES0_IRQHandler=Default_Handler
#pragma weak DES0_IRQHandler=Default_Handler
#pragma weak LCD0_IRQHandler=Default_Handler
#pragma weak TIMER6A_IRQHandler=Default_Handler
#pragma weak TIMER6B_IRQHandler=Default_Handler
#pragma weak TIMER7A_IRQHandler=Default_Handler
#pragma weak TIMER7B_IRQHandler=Default_Handler
#pragma weak I2C6_IRQHandler=Default_Handler
#pragma weak I2C7_IRQHandler=Default_Handler
#pragma weak ONEWIRE0_IRQHandler=Default_Handler
#pragma weak I2C8_IRQHandler=Default_Handler
#pragma weak I2C9_IRQHandler=Default_Handler
#pragma weak GPIOT_IRQHandler=Default_Handler

//*****************************************************************************
//
// The reference for the device initialization.
//
//*****************************************************************************
extern void SystemInit(void);

//*****************************************************************************
//
// The entry point for the application startup code.
//
//*****************************************************************************
extern void __iar_program_start(void);

//*****************************************************************************
//
// A union that describes the entries of the vector table.  The union is needed
// since the first entry is the stack pointer and the remainder are function
// pointers.
//
//*****************************************************************************
typedef union
{
    void (*handler)(void);
    uint32_t ptr;
}
uVectorEntry;

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
__root const uVectorEntry __vector_table[] @ ".intvec" =
{
    { .ptr = (uint32_t)__sfe("CSTACK") },   /* The initial stack pointer */
    Reset_Handler,                          /* The reset handler         */
    NMI_Handler,                            /* The NMI handler           */
    HardFault_Handler,                      /* The hard fault handler    */
    MemManage_Handler,                      /* The MPU fault handler     */
    BusFault_Handler,                       /* The bus fault handler     */
    UsageFault_Handler,                     /* The usage fault handler   */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    SVC_Handler,                            /* SVCall handler            */
    DebugMon_Handler,                       /* Debug monitor handler     */
    0,                                      /* Reserved                  */
    PendSV_Handler,                         /* The PendSV handler        */
    SysTick_Handler,                        /* The SysTick handler       */
    GPIOA_IRQHandler,                       /* GPIO Port A               */
    GPIOB_IRQHandler,                       /* GPIO Port B               */
    GPIOC_IRQHandler,                       /* GPIO Port C               */
    GPIOD_IRQHandler,                       /* GPIO Port D               */
    GPIOE_IRQHandler,                       /* GPIO Port E               */
    UART0_IRQHandler,                       /* UART0 Rx and Tx           */
    UART1_IRQHandler,                       /* UART1 Rx and Tx           */
    SSI0_IRQHandler,                        /* SSI0 Rx and Tx            */
    I2C0_IRQHandler,                        /* I2C0 Master and Slave     */
    PWM0_FAULT_IRQHandler,                  /* PWM Fault                 */
    PWM0_0_IRQHandler,                      /* PWM Generator 0           */
    PWM0_1_IRQHandler,                      /* PWM Generator 1           */
    PWM0_2_IRQHandler,                      /* PWM Generator 2           */
    QEI0_IRQHandler,                        /* Quadrature Encoder 0      */
    ADC0SS0_IRQHandler,                     /* ADC Sequence 0            */
    ADC0SS1_IRQHandler,                     /* ADC Sequence 1            */
    ADC0SS2_IRQHandler,                     /* ADC Sequence 2            */
    ADC0SS3_IRQHandler,                     /* ADC Sequence 3            */
    WATCHDOG_IRQHandler,                    /* Watchdog timer            */
    TIMER0A_IRQHandler,                     /* Timer 0 subtimer A        */
    TIMER0B_IRQHandler,                     /* Timer 0 subtimer B        */
    TIMER1A_IRQHandler,                     /* Timer 1 subtimer A        */
    TIMER1B_IRQHandler,                     /* Timer 1 subtimer B        */
    TIMER2A_IRQHandler,                     /* Timer 2 subtimer A        */
    TIMER2B_IRQHandler,                     /* Timer 2 subtimer B        */
    COMP0_IRQHandler,                       /* Analog Comparator 0       */
    COMP1_IRQHandler,                       /* Analog Comparator 1       */
    COMP2_IRQHandler,                       /* Analog Comparator 2       */
    SYSCTL_IRQHandler,                      /* System Control            */
    FLASH_IRQHandler,                       /* FLASH Control             */
    GPIOF_IRQHandler,                       /* GPIO Port F               */
    GPIOG_IRQHandler,                       /* GPIO Port G               */
    GPIOH_IRQHandler,                       /* GPIO Port H               */
    UART2_IRQHandler,                       /* UART2 Rx and Tx           */
    SSI1_IRQHandler,                        /* SSI1 Rx and Tx            */
    TIMER3A_IRQHandler,                     /* Timer 3 subtimer A        */
    TIMER3B_IRQHandler,                     /* Timer 3 subtimer B        */
    I2C1_IRQHandler,                        /* I2C1 Master and Slave     */
    CAN0_IRQHandler,                        /* CAN0                      */
    CAN1_IRQHandler,                        /* CAN1                      */
    EMAC0_IRQHandler,                       /* Ethernet                  */
    HIBERNATE_IRQHandler,                   /* Hibernate                 */
    USB0_IRQHandler,                        /* USB0                      */
    PWM0_3_IRQHandler,                      /* PWM Generator 3           */
    UDMA_IRQHandler,                        /* uDMA Software Transfer    */
    UDMAERR_IRQHandler,                     /* uDMA Error                */
    ADC1SS0_IRQHandler,                     /* ADC1 Sequence 0           */
    ADC1SS1_IRQHandler,                     /* ADC1 Sequence 1           */
    ADC1SS2_IRQHandler,                     /* ADC1 Sequence 2           */
    ADC1SS3_IRQHandler,                     /* ADC1 Sequence 3           */
    EPI0_IRQHandler,                        /* External Bus Interface 0  */
    GPIOJ_IRQHandler,                       /* GPIO Port J               */
    GPIOK_IRQHandler,                       /* GPIO Port K               */
    GPIOL_IRQHandler,                       /* GPIO Port L               */
    SSI2_IRQHandler,                        /* SSI2 Rx and Tx            */
    SSI3_IRQHandler,                        /* SSI3 Rx and Tx            */
    UART3_IRQHandler,                       /* UART3 Rx and Tx           */
    UART4_IRQHandler,                       /* UART4 Rx and Tx           */
    UART5_IRQHandler,                       /* UART5 Rx and Tx           */
    UART6_IRQHandler,                       /* UART6 Rx and Tx           */
    UART7_IRQHandler,                       /* UART7 Rx and Tx           */
    I2C2_IRQHandler,                        /* I2C2 Master and Slave     */
    I2C3_IRQHandler,                        /* I2C3 Master and Slave     */
    TIMER4A_IRQHandler,                     /* Timer 4 subtimer A        */
    TIMER4B_IRQHandler,                     /* Timer 4 subtimer B        */
    TIMER5A_IRQHandler,                     /* Timer 5 subtimer A        */
    TIMER5B_IRQHandler,                     /* Timer 5 subtimer B        */
    SYSEXC_IRQHandler,                      /* FPU                       */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    I2C4_IRQHandler,                        /* I2C4 Master and Slave     */
    I2C5_IRQHandler,                        /* I2C5 Master and Slave     */
    GPIOM_IRQHandler,                       /* GPIO Port M               */
    GPION_IRQHandler,                       /* GPIO Port N               */
    0,                                      /* Reserved                  */
    TAMPER0_IRQHandler,                     /* Tamper                    */
    GPIOP0_IRQHandler,                      /* GPIO Port P(Summary or P0)*/
    GPIOP1_IRQHandler,                      /* GPIO Port P1              */
    GPIOP2_IRQHandler,                      /* GPIO Port P2              */
    GPIOP3_IRQHandler,                      /* GPIO Port P3              */
    GPIOP4_IRQHandler,                      /* GPIO Port P4              */
    GPIOP5_IRQHandler,                      /* GPIO Port P5              */
    GPIOP6_IRQHandler,                      /* GPIO Port P6              */
    GPIOP7_IRQHandler,                      /* GPIO Port P7              */
    GPIOQ0_IRQHandler,                      /* GPIO Port Q(Summary or Q0)*/
    GPIOQ1_IRQHandler,                      /* GPIO Port Q1              */
    GPIOQ2_IRQHandler,                      /* GPIO Port Q2              */
    GPIOQ3_IRQHandler,                      /* GPIO Port Q3              */
    GPIOQ4_IRQHandler,                      /* GPIO Port Q4              */
    GPIOQ5_IRQHandler,                      /* GPIO Port Q5              */
    GPIOQ6_IRQHandler,                      /* GPIO Port Q6              */
    GPIOQ7_IRQHandler,                      /* GPIO Port Q7              */
    GPIOR_IRQHandler,                       /* GPIO Port R               */
    GPIOS_IRQHandler,                       /* GPIO Port S               */
    SHA0_IRQHandler,                        /* SHA/MD5 0                 */
    AES0_IRQHandler,                        /* AES 0                     */
    DES0_IRQHandler,                        /* DES3DES 0                 */
    LCD0_IRQHandler,                        /* LCD Controller 0          */
    TIMER6A_IRQHandler,                     /* Timer 6 subtimer A        */
    TIMER6B_IRQHandler,                     /* Timer 6 subtimer B        */
    TIMER7A_IRQHandler,                     /* Timer 7 subtimer A        */
    TIMER7B_IRQHandler,                     /* Timer 7 subtimer B        */
    I2C6_IRQHandler,                        /* I2C6 Master and Slave     */
    I2C7_IRQHandler,                        /* I2C7 Master and Slave     */
    0,                                      /* Reserved                  */
    ONEWIRE0_IRQHandler,                    /* One Wire 0                */
    0,                                      /* HIM PS/2 0                */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    I2C8_IRQHandler,                        /* I2C8 Master and Slave     */
    I2C9_IRQHandler,                        /* I2C9 Master and Slave     */
    GPIOT_IRQHandler,                       /* GPIO Port T               */
    0,                                      /* Reserved                  */
    0                                       /* Reserved                  */
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
__weak void Reset_Handler(void)
{
    //
    // Initialize the device
    //
    SystemInit();

    //
    // Call the application's entry point.
    //
    __iar_program_start();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void Default_Handler(void)
{
    //
    // Go into an infinite loop.
    //
    while (1)
    {
    }
}

