;********************************************************************************
;* File Name          : Startup_ACM32F4.s
;* Description        : This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == _iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR
;*                        address.
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M33 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;********************************************************************************
;*
;* <h2><center>&copy; Copyright (c) 2021 Aisinochip.
;* All rights reserved.</center></h2>
;*
;*******************************************************************************


        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler              ; Reset Handler
        DCD     NMI_Handler                ; NMI Handler
        DCD     HardFault_Handler          ; Hard Fault Handler
        DCD     MemManage_Handler          ; MPU Fault Handler
        DCD     BusFault_Handler           ; Bus Fault Handler
        DCD     UsageFault_Handler         ; Usage Fault Handler
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     SVC_Handler                ; SVCall Handler
        DCD     DebugMon_Handler           ; Debug Monitor Handler
        DCD     0                          ; Reserved
        DCD     PendSV_Handler             ; PendSV Handler
        DCD     SysTick_Handler            ; SysTick Handler

         ; External Interrupts
        DCD     WDT_IRQHandler                    ; WDT_IRQHandle
        DCD     RTC_IRQHandler                    ; RTC_IRQHandler
        DCD     EFC_IRQHandler                    ; EFC_IRQHandler
        DCD     GPIOAB_IRQHandler                 ; GPIOAB_IRQHandler
        DCD     GPIOCD_IRQHandler                 ; GPIOCD_IRQHandler
        DCD     EXTI_IRQHandler                   ; EXTI_IRQHandler
        DCD     SRAM_PARITY_IRQHandler            ; SRAM_PARITY_IRQHandler
        DCD     CLKRDY_IRQHandler                 ; CLKRDY_IRQHandler
        DCD     UART4_IRQHandler                  ; UART4_IRQHandler
        DCD     DMA_IRQHandler                    ; DMA_IRQHandler
        DCD     UART3_IRQHandler                  ; UART3_IRQHandler
        DCD     RSV_IRQHandler                    ; RSV_IRQHandler
        DCD     ADC_IRQHandler                    ; ADC_IRQHandler
        DCD     TIM1_BRK_UP_TRG_COM_IRQHandler    ; TIM1_BRK_UP_TRG_COM_IRQHandler
        DCD     TIM1_CC_IRQHandler                ; TIM1_CC_IRQHandler
        DCD     TIM2_IRQHandler                   ; TIM2_IRQHandler
        DCD     TIM3_IRQHandler                   ; TIM3_IRQHandler
        DCD     TIM6_IRQHandler                   ; TIM6_IRQHandler
        DCD     TIM7_IRQHandler                   ; TIM7_IRQHandler
        DCD     TIM14_IRQHandler                  ; TIM14_IRQHandler
        DCD     TIM15_IRQHandler                  ; TIM15_IRQHandler
        DCD     TIM16_IRQHandler                  ; TIM16_IRQHandler
        DCD     TIM17_IRQHandler                  ; TIM17_IRQHandler
        DCD     I2C1_IRQHandler                   ; I2C1_IRQHandler
        DCD     I2C2_IRQHandler                   ; I2C2_IRQHandler
        DCD     SPI1_IRQHandler                   ; SPI1_IRQHandler
        DCD     SPI2_IRQHandler                   ; SPI2_IRQHandler
        DCD     UART1_IRQHandler                  ; UART1_IRQHandler
        DCD     UART2_IRQHandler                  ; UART2_IRQHandler
        DCD     LPUART_IRQHandler                 ; LPUART_IRQHandler
        DCD     SPI3_IRQHandler                   ; SPI3_IRQHandler
        DCD     AES_IRQHandler                    ; AES_IRQHandler
        DCD     USB_IRQHandler                    ; USB_IRQHandler
        DCD     DAC_IRQHandler                    ; DAC_IRQHandler
        DCD     I2S_IRQHandler                    ; I2S_IRQHandler
        DCD     GPIOEF_IRQHandler                 ; GPIOEF_IRQHandler
        DCD     CAN1_IRQHandler                   ; CAN1_IRQHandler
        DCD     CAN2_IRQHandler                   ; CAN2_IRQHandler
        DCD     FPU_IRQHandler                    ; FPU_IRQHandler
        DCD     TIM4_IRQHandler                   ; TIM4_IRQHandler
        DCD     SPI4_IRQHandler                   ; SPI4_IRQHandler
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WDT_IRQHandler
        B WDT_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK EFC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EFC_IRQHandler
        B EFC_IRQHandler

        PUBWEAK GPIOAB_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIOAB_IRQHandler
        B GPIOAB_IRQHandler

        PUBWEAK GPIOCD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIOCD_IRQHandler
        B GPIOCD_IRQHandler

        PUBWEAK EXTI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI_IRQHandler
        B EXTI_IRQHandler

        PUBWEAK SRAM_PARITY_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SRAM_PARITY_IRQHandler
        B SRAM_PARITY_IRQHandler

        PUBWEAK CLKRDY_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CLKRDY_IRQHandler
        B CLKRDY_IRQHandler

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_IRQHandler
        B UART4_IRQHandler

        PUBWEAK DMA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_IRQHandler
        B DMA_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK RSV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RSV_IRQHandler
        B RSV_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK TIM1_BRK_UP_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_BRK_UP_TRG_COM_IRQHandler
        B TIM1_BRK_UP_TRG_COM_IRQHandler

        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_CC_IRQHandler
        B TIM1_CC_IRQHandler

        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
        B TIM3_IRQHandler

        PUBWEAK TIM6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM6_IRQHandler
        B TIM6_IRQHandler

        PUBWEAK TIM7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM7_IRQHandler
        B TIM7_IRQHandler

        PUBWEAK TIM14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM14_IRQHandler
        B TIM14_IRQHandler

        PUBWEAK TIM15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM15_IRQHandler
        B TIM15_IRQHandler

        PUBWEAK TIM16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM16_IRQHandler
        B TIM16_IRQHandler

        PUBWEAK TIM17_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM17_IRQHandler
        B TIM17_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK I2C2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_IRQHandler
        B I2C2_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART2_IRQHandler
        B UART2_IRQHandler

        PUBWEAK LPUART_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPUART_IRQHandler
        B LPUART_IRQHandler

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI3_IRQHandler
        B SPI3_IRQHandler

        PUBWEAK AES_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AES_IRQHandler
        B AES_IRQHandler

        PUBWEAK USB_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_IRQHandler
        B USB_IRQHandler

        PUBWEAK DAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC_IRQHandler
        B DAC_IRQHandler

        PUBWEAK I2S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2S_IRQHandler
        B I2S_IRQHandler

        PUBWEAK GPIOEF_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIOEF_IRQHandler
        B GPIOEF_IRQHandler

        PUBWEAK CAN1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_IRQHandler
        B CAN1_IRQHandler

        PUBWEAK CAN2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_IRQHandler
        B CAN2_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK TIM4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM4_IRQHandler
        B TIM4_IRQHandler

        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI4_IRQHandler
        B SPI4_IRQHandler


        END
/************************ (C) COPYRIGHT Aisinochip *****END OF FILE****/
