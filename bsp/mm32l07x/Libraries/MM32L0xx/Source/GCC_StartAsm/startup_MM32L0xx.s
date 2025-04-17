/* ******************** (C) COPYRIGHT 2017 MindMotion ******************** */
/* File Name          : startup_mm32L0xx.s                                */
/* Author             : AE Team                                           */
/* Version            : V2.0.0                                            */
/* Date               : 22/08/2017                                        */
/* Description        : MM32L0xx Medium-density devices vector table for  */
/*                      GCC toolchain.                                    */
/*                      This module performs:                             */
/*                      - Set the initial SP                              */
/*                      - Set the initial PC == __iar_program_start,       */
/*                      - Set the vector table entries with the exceptions*/
/*                        ISR address                                     */
/*                      - Configure the system clock                      */
/*                      - Branches to main in the C library (which        */
/*                        eventually calls main()).                       */
/*                      After Reset the Cortex-M0 processor is in Thread  */
/*                      mode, priority is Privileged, and the Stack is set*/
/*                      to Main.                                          */
/* ************************************************************************/

/* The vector table is normally located at address 0. When debugging in RAM, it can be located in RAM, aligned to at least 2^6. The name "__vector_table" has special meaning for C-SPY: it is where the SP start value is found, and the NVIC vector table register (VTOR) is initialized to this address if != 0. */

/* Cortex-M version */

    .syntax unified
    .cpu cortex-m0
    .fpu softvfp
    .thumb

.global __vector_table

.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss

    .section .text.Reset_Handler
    .weak Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:
    ldr r0, =_estack
    msr msp, r0

    /*Check if boot space corresponds to test memory*/
    ldr r0, =0x00000004
    ldr r1, [r0]
    lsrs r1, r1, #24
    ldr r2, =0x1F
    cmp r1, r2
    bne ApplicationStart  

    /*SYSCFG clock enable*/
    ldr r0, =0x40021018 
    ldr r1, =0x00000001
    str r1, [r0]

    /* Set CFGR1 register with flash memory remap at address 0 */
    ldr r0, =0x40010000 
    ldr r1, =0x00000000
    str r1, [r0]
ApplicationStart:
    /* Copy the data segment initializers from flash to SRAM */
    movs r1, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r3, =_sidata
    ldr r3, [r3, r1]
    str r3, [r0, r1]
    adds r1, r1, #4

LoopCopyDataInit:
    ldr r0, =_sdata
    ldr r3, =_edata
    adds r2, r0, r1
    cmp r2, r3
    bcc CopyDataInit
    ldr r2, =_sbss
    b LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
    movs r3, #0
    str  r3, [r2]
    adds r2, r2, #4


LoopFillZerobss:
    ldr r3, = _ebss
    cmp r2, r3
    bcc FillZerobss

/* Call the clock system intitialization function.*/
    bl  SystemInit
    
/* Call the application's entry point.*/
    bl main
  
LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/* Vector Table Mapped to Address 0 at Reset */
    .section .isr_vector, "a", %progbits
    .type __vector_table, %object
    .size __vector_table, .-__vector_table

__vector_table:
    .word _estack
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word 0
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler

    /* External Interrupts */
    .word WWDG_IRQHandler
    .word PVD_IRQHandler
    .word RTC_IRQHandler
    .word FLASH_IRQHandler
    .word RCC_CRS_IRQHandler
    .word EXTI0_1_IRQHandler
    .word EXTI2_3_IRQHandler
    .word EXTI4_15_IRQHandler
    .word 0
    .word DMA1_Channel1_IRQHandler
    .word DMA1_Channel2_3_IRQHandler
    .word DMA1_Channel4_5_IRQHandler
    .word ADC_COMP_IRQHandler
    .word TIM1_BRK_UP_TRG_COM_IRQHandler
    .word TIM1_CC_IRQHandler
    .word TIM2_IRQHandler
    .word TIM3_IRQHandler
    .word 0
    .word 0
    .word TIM14_IRQHandler
    .word 0
    .word TIM16_IRQHandler
    .word TIM17_IRQHandler
    .word I2C1_IRQHandler
    .word 0
    .word SPI1_IRQHandler
    .word SPI2_IRQHandler
    .word UART1_IRQHandler
    .word UART2_IRQHandler
    .word AES_IRQHandler
    .word CAN_IRQHandler
    .word USB_IRQHandler

/* Dummy Exception Handlers (infinite loops which can be modified) */
    .section .text.NMI_Handler
    .weak NMI_Handler
    .type NMI_Handler, %function
NMI_Handler:
    b NMI_Handler

    .section .text.HardFault_Handler
    .weak HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    b HardFault_Handler

    .section .text.SVC_Handler
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    b SVC_Handler

    .section .text.PendSV_Handler
    .weak PendSV_Handler
    .type PendSV_Handler, %function
PendSV_Handler:
    b PendSV_Handler

    .section .text.SysTick_Handler
    .weak SysTick_Handler
    .type SysTick_Handler, %function
SysTick_Handler:
    b SysTick_Handler

    .section .text.WWDG_IRQHandler
    .weak WWDG_IRQHandler
    .type WWDG_IRQHandler, %function
WWDG_IRQHandler:
    b WWDG_IRQHandler

    .section .text.PVD_IRQHandler
    .weak PVD_IRQHandler
    .type PVD_IRQHandler, %function
PVD_IRQHandler:
    b PVD_IRQHandler

    .section .text.RTC_IRQHandler
    .weak RTC_IRQHandler
    .type RTC_IRQHandler, %function
RTC_IRQHandler:
    b RTC_IRQHandler

    .section .text.FLASH_IRQHandler
    .weak FLASH_IRQHandler
    .type FLASH_IRQHandler, %function
FLASH_IRQHandler:
    b FLASH_IRQHandler

    .section .text.RCC_CRS_IRQHandler
    .weak RCC_CRS_IRQHandler
    .type RCC_CRS_IRQHandler, %function
RCC_CRS_IRQHandler:
    b RCC_CRS_IRQHandler

    .section .text.EXTI0_1_IRQHandler
    .weak EXTI0_1_IRQHandler
    .type EXTI0_1_IRQHandler, %function
EXTI0_1_IRQHandler:
    b EXTI0_1_IRQHandler

    .section .text.EXTI2_3_IRQHandler
    .weak EXTI2_3_IRQHandler
    .type EXTI2_3_IRQHandler, %function
EXTI2_3_IRQHandler:
    b EXTI2_3_IRQHandler

    .section .text.EXTI4_15_IRQHandler
    .weak EXTI4_15_IRQHandler
    .type EXTI4_15_IRQHandler, %function
EXTI4_15_IRQHandler:
    b EXTI4_15_IRQHandler

    .section .text.DMA1_Channel1_IRQHandler
    .weak DMA1_Channel1_IRQHandler
    .type DMA1_Channel1_IRQHandler, %function
DMA1_Channel1_IRQHandler:
    b DMA1_Channel1_IRQHandler

    .section .text.DMA1_Channel2_3_IRQHandler
    .weak DMA1_Channel2_3_IRQHandler
    .type DMA1_Channel2_3_IRQHandler, %function
DMA1_Channel2_3_IRQHandler:
    b DMA1_Channel2_3_IRQHandler

    .section .text.DMA1_Channel4_5_IRQHandler
    .weak DMA1_Channel4_5_IRQHandler
    .type DMA1_Channel4_5_IRQHandler, %function
DMA1_Channel4_5_IRQHandler:
    b DMA1_Channel4_5_IRQHandler

    .section .text.ADC_COMP_IRQHandler
    .weak ADC_COMP_IRQHandler
    .type ADC_COMP_IRQHandler, %function
ADC_COMP_IRQHandler:
    b ADC_COMP_IRQHandler

    .section .text.TIM1_BRK_UP_TRG_COM_IRQHandler
    .weak TIM1_BRK_UP_TRG_COM_IRQHandler
    .type TIM1_BRK_UP_TRG_COM_IRQHandler, %function
TIM1_BRK_UP_TRG_COM_IRQHandler:
    b TIM1_BRK_UP_TRG_COM_IRQHandler

    .section .text.TIM1_CC_IRQHandler
    .weak TIM1_CC_IRQHandler
    .type TIM1_CC_IRQHandler, %function
TIM1_CC_IRQHandler:
    b TIM1_CC_IRQHandler

    .section .text.TIM2_IRQHandler
    .weak TIM2_IRQHandler
    .type TIM2_IRQHandler, %function
TIM2_IRQHandler:
    b TIM2_IRQHandler

    .section .text.TIM3_IRQHandler
    .weak TIM3_IRQHandler
    .type TIM3_IRQHandler, %function
TIM3_IRQHandler:
    b TIM3_IRQHandler

    .section .text.TIM14_IRQHandler
    .weak TIM14_IRQHandler
    .type TIM14_IRQHandler, %function
TIM14_IRQHandler:
    b TIM14_IRQHandler

    .section .text.TIM16_IRQHandler
    .weak TIM16_IRQHandler
    .type TIM16_IRQHandler, %function
TIM16_IRQHandler:
    b TIM16_IRQHandler

    .section .text.TIM17_IRQHandler
    .weak TIM17_IRQHandler
    .type TIM17_IRQHandler, %function
TIM17_IRQHandler:
    b TIM17_IRQHandler

    .section .text.I2C1_IRQHandler
    .weak I2C1_IRQHandler
    .type I2C1_IRQHandler, %function
I2C1_IRQHandler:
    b I2C1_IRQHandler

    .section .text.SPI1_IRQHandler
    .weak SPI1_IRQHandler
    .type SPI1_IRQHandler, %function
SPI1_IRQHandler:
    b SPI1_IRQHandler

    .section .text.SPI2_IRQHandler
    .weak SPI2_IRQHandler
    .type SPI2_IRQHandler, %function
SPI2_IRQHandler:
    b SPI2_IRQHandler

    .section .text.UART1_IRQHandler
    .weak UART1_IRQHandler
    .type UART1_IRQHandler, %function
UART1_IRQHandler:
    b UART1_IRQHandler

    .section .text.UART2_IRQHandler
    .weak UART2_IRQHandler
    .type UART2_IRQHandler, %function
UART2_IRQHandler:
    b UART2_IRQHandler

    .section .text.AES_IRQHandler
    .weak AES_IRQHandler
    .type AES_IRQHandler, %function
AES_IRQHandler:
    b AES_IRQHandler

    .section .text.CAN_IRQHandler
    .weak CAN_IRQHandler
    .type CAN_IRQHandler, %function
CAN_IRQHandler:
    b CAN_IRQHandler

    .section .text.USB_IRQHandler
    .weak USB_IRQHandler
    .type USB_IRQHandler, %function
USB_IRQHandler:
    b USB_IRQHandler

/* ******************** (C) COPYRIGHT 2017 MindMotion ******************** */
