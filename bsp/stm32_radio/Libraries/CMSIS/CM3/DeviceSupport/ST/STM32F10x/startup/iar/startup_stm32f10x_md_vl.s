;/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
;* File Name          : startup_stm32f10x_md_vl.s
;* Author             : MCD Application Team
;* Version            : V3.2.0
;* Date               : 03/01/2010
;* Description        : STM32F10x Medium Density Value Line Devices vector table 
;*                      for EWARM5.x toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Configure the clock system
;*                      - Set the initial PC == __iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR 
;*                        address.
;*                      After Reset the Cortex-M3 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;********************************************************************************
;* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
;* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
;* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
;* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
;* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
;* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;*******************************************************************************/
;
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit        
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler             ; Reset Handler
        DCD     NMI_Handler               ; NMI Handler
        DCD     HardFault_Handler         ; Hard Fault Handler
        DCD     MemManage_Handler         ; MPU Fault Handler
        DCD     BusFault_Handler          ; Bus Fault Handler
        DCD     UsageFault_Handler        ; Usage Fault Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     SVC_Handler               ; SVCall Handler
        DCD     DebugMon_Handler          ; Debug Monitor Handler
        DCD     0                         ; Reserved
        DCD     PendSV_Handler            ; PendSV Handler
        DCD     SysTick_Handler           ; SysTick Handler

         ; External Interrupts
        DCD     WWDG_IRQHandler               ; Window Watchdog
        DCD     PVD_IRQHandler                ; PVD through EXTI Line detect
        DCD     TAMPER_IRQHandler             ; Tamper
        DCD     RTC_IRQHandler                ; RTC
        DCD     FLASH_IRQHandler              ; Flash
        DCD     RCC_IRQHandler                ; RCC
        DCD     EXTI0_IRQHandler              ; EXTI Line 0
        DCD     EXTI1_IRQHandler              ; EXTI Line 1
        DCD     EXTI2_IRQHandler              ; EXTI Line 2
        DCD     EXTI3_IRQHandler              ; EXTI Line 3
        DCD     EXTI4_IRQHandler              ; EXTI Line 4
        DCD     DMA1_Channel1_IRQHandler      ; DMA1 Channel 1
        DCD     DMA1_Channel2_IRQHandler      ; DMA1 Channel 2
        DCD     DMA1_Channel3_IRQHandler      ; DMA1 Channel 3
        DCD     DMA1_Channel4_IRQHandler      ; DMA1 Channel 4
        DCD     DMA1_Channel5_IRQHandler      ; DMA1 Channel 5
        DCD     DMA1_Channel6_IRQHandler      ; DMA1 Channel 6
        DCD     DMA1_Channel7_IRQHandler      ; DMA1 Channel 7
        DCD     ADC1_IRQHandler               ; ADC1
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     EXTI9_5_IRQHandler            ; EXTI Line 9..5
        DCD     TIM1_BRK_TIM15_IRQHandler     ; TIM1 Break and TIM15
        DCD     TIM1_UP_TIM16_IRQHandler      ; TIM1 Update and TIM16
        DCD     TIM1_TRG_COM_TIM17_IRQHandler ; TIM1 Trigger and Commutation and TIM17
        DCD     TIM1_CC_IRQHandler            ; TIM1 Capture Compare
        DCD     TIM2_IRQHandler               ; TIM2
        DCD     TIM3_IRQHandler               ; TIM3
        DCD     TIM4_IRQHandler               ; TIM4
        DCD     I2C1_EV_IRQHandler            ; I2C1 Event
        DCD     I2C1_ER_IRQHandler            ; I2C1 Error
        DCD     I2C2_EV_IRQHandler            ; I2C2 Event
        DCD     I2C2_ER_IRQHandler            ; I2C2 Error
        DCD     SPI1_IRQHandler               ; SPI1
        DCD     SPI2_IRQHandler               ; SPI2
        DCD     USART1_IRQHandler             ; USART1
        DCD     USART2_IRQHandler             ; USART2
        DCD     USART3_IRQHandler             ; USART3
        DCD     EXTI15_10_IRQHandler          ; EXTI Line 15..10
        DCD     RTCAlarm_IRQHandler           ; RTC Alarm through EXTI Line
        DCD     CEC_IRQHandler                ; HDMI-CEC
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved
        DCD     0                             ; Reserved                        
        DCD     TIM6_DAC_IRQHandler           ; TIM6 and DAC underrun
        DCD     TIM7_IRQHandler               ; TIM7                

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:REORDER(1)
WWDG_IRQHandler
        B WWDG_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:REORDER(1)
PVD_IRQHandler
        B PVD_IRQHandler

        PUBWEAK TAMPER_IRQHandler
        SECTION .text:CODE:REORDER(1)
TAMPER_IRQHandler
        B TAMPER_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:REORDER(1)
RCC_IRQHandler
        B RCC_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA1_Channel2_IRQHandler
        B DMA1_Channel2_IRQHandler

        PUBWEAK DMA1_Channel3_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA1_Channel3_IRQHandler
        B DMA1_Channel3_IRQHandler

        PUBWEAK DMA1_Channel4_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA1_Channel4_IRQHandler
        B DMA1_Channel4_IRQHandler

        PUBWEAK DMA1_Channel5_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA1_Channel5_IRQHandler
        B DMA1_Channel5_IRQHandler

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK DMA1_Channel7_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA1_Channel7_IRQHandler
        B DMA1_Channel7_IRQHandler

        PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:REORDER(1)
ADC1_IRQHandler
        B ADC1_IRQHandler

        PUBWEAK EXTI9_5_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI9_5_IRQHandler
        B EXTI9_5_IRQHandler

        PUBWEAK TIM1_BRK_TIM15_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM1_BRK_TIM15_IRQHandler
        B TIM1_BRK_TIM15_IRQHandler

        PUBWEAK TIM1_UP_TIM16_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM1_UP_TIM16_IRQHandler
        B TIM1_UP_TIM16_IRQHandler

        PUBWEAK TIM1_TRG_COM_TIM17_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM1_TRG_COM_TIM17_IRQHandler
        B TIM1_TRG_COM_TIM17_IRQHandler

        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM1_CC_IRQHandler
        B TIM1_CC_IRQHandler

        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM3_IRQHandler
        B TIM3_IRQHandler

        PUBWEAK TIM4_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM4_IRQHandler
        B TIM4_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler

        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C2_EV_IRQHandler
        B I2C2_EV_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:REORDER(1)
USART3_IRQHandler
        B USART3_IRQHandler

        PUBWEAK EXTI15_10_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI15_10_IRQHandler
        B EXTI15_10_IRQHandler

        PUBWEAK RTCAlarm_IRQHandler
        SECTION .text:CODE:REORDER(1)
RTCAlarm_IRQHandler
        B RTCAlarm_IRQHandler

        PUBWEAK CEC_IRQHandler
        SECTION .text:CODE:REORDER(1)
CEC_IRQHandler
        B CEC_IRQHandler

        PUBWEAK TIM6_DAC_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM6_DAC_IRQHandler
        B TIM6_DAC_IRQHandler

        PUBWEAK TIM7_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIM7_IRQHandler
        B TIM7_IRQHandler                

        END
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
