/******************************************************************************
*
* Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*  Redistributions of source code must retain the above copyright
*  notice, this list of conditions and the following disclaimer.
*
*  Redistributions in binary form must reproduce the above copyright
*  notice, this list of conditions and the following disclaimer in the
*  documentation and/or other materials provided with the
*  distribution.
*
*  Neither the name of Texas Instruments Incorporated nor the names of
*  its contributors may be used to endorse or promote products derived
*  from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
 *****************************************************************************/

#include <stdint.h>


/* External declaration for the reset handler that is to be called when the */
/* processor is started                                                     */
extern void _c_int00(void);

/* External declaration for system initialization function                  */
extern void SystemInit(void);

/* Linker variable that marks the top of the stack. */
extern uint32_t __STACK_TOP;

/* Forward declaration of the default fault handlers. */
void Default_Handler(void) __attribute__((weak));
extern void Reset_Handler(void) __attribute__((weak));

/* Cortex-M4 Processor Exceptions */
extern void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

/* device specific interrupt handler */
extern void GPIOA_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOB_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UART0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void SSI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void PWM0_FAULT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void PWM0_0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void PWM0_1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void PWM0_2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void QEI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void ADC0SS0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void ADC0SS1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void ADC0SS2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void ADC0SS3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void WATCHDOG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER0A_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER0B_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER1A_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER1B_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER2A_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER2B_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void COMP0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void COMP1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void COMP2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void SYSCTL_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOF_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void SSI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER3A_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER3B_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void CAN0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void CAN1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void EMAC0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void HIBERNATE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void USB0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void PWM0_3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UDMA_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UDMAERR_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void ADC1SS0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void ADC1SS1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void ADC1SS2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void ADC1SS3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void EPI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOJ_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOK_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOL_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void SSI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void SSI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UART4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UART5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UART6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void UART7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER4A_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER4B_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER5A_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER5B_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void SYSEXC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPION_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TAMPER0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOP0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOP1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOP2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOP3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOP4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOP5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOP6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOP7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOQ0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOQ1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOQ2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOQ3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOQ4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOQ5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOQ6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void GPIOQ7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void SHA0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void AES0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void DES0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER6A_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER6B_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER7A_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMER7B_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C8_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void I2C9_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

/* Interrupt vector table.  Note that the proper constructs must be placed on this to */
/* ensure that it ends up at physical address 0x0000.0000 or at the start of          */
/* the program if located at a start address other than 0.                            */
#pragma RETAIN(interruptVectors)
#pragma DATA_SECTION(interruptVectors, ".intvecs")
void (* const interruptVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP),
    /* The initial stack pointer */
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
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    SHA0_IRQHandler,                        /* SHA/MD5 0                 */
    AES0_IRQHandler,                        /* AES 0                     */
    DES0_IRQHandler,                        /* DES3DES 0                 */
    0,                                      /* Reserved                  */
    TIMER6A_IRQHandler,                     /* Timer 6 subtimer A        */
    TIMER6B_IRQHandler,                     /* Timer 6 subtimer B        */
    TIMER7A_IRQHandler,                     /* Timer 7 subtimer A        */
    TIMER7B_IRQHandler,                     /* Timer 7 subtimer B        */
    I2C6_IRQHandler,                        /* I2C6 Master and Slave     */
    I2C7_IRQHandler,                        /* I2C7 Master and Slave     */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    I2C8_IRQHandler,                        /* I2C8 Master and Slave     */
    I2C9_IRQHandler,                        /* I2C9 Master and Slave     */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
};

/* Forward declaration of the default fault handlers. */
/* This is the code that gets called when the processor first starts execution */
/* following a reset event.  Only the absolutely necessary set is performed,   */
/* after which the application supplied entry() routine is called.  Any fancy  */
/* actions (such as making decisions based on the reset cause register, and    */
/* resetting the bits in that register) are left solely in the hands of the    */
/* application.                                                                */
void Reset_Handler(void)
{
    SystemInit();

    /* Jump to the CCS C Initialization Routine. */
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

/* This is the code that gets called when the processor receives an unexpected  */
/* interrupt.  This simply enters an infinite loop, preserving the system state */
/* for examination by a debugger.                                               */
void Default_Handler(void)
{
    /* Fault trap exempt from ULP advisor */
#pragma diag_push
#pragma CHECK_ULP("-2.1")

    /* Enter an infinite loop. */
    while (1)
    {
    }

#pragma diag_pop
}
