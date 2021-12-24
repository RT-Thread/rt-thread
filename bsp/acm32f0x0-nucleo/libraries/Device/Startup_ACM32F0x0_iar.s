;* File Name          : Startup_ACM32F0x0.s
;* Version            : V1.0.0
;* Date               : 2020
;* Description        : ACM32F0x0 Devices vector table for MDK-ARM toolchain. 
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == __iar_program_start
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the SC000 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                  ; Reset Handler

        DCD     NMI_Handler                    ; NMI Handler
        DCD     HardFault_Handler              ; Hard Fault Handler
        DCD     MemManage_Handler              ; MemManage_Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_Handler                    ; SVCall Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     PendSV_Handler                 ; PendSV Handler
        DCD     SysTick_Handler                ; SysTick Handler

        ; External Interrupts
        DCD     WDT_IRQHandler                  ; 0:  WDT_IRQHandler
        DCD     RTC_IRQHandler                  ; 1:  RTC_IRQHandler
        DCD     EFC_IRQHandler                  ; 2:  EFC_IRQHandler
        DCD     GPIOAB_IRQHandler               ; 3:  GPIOAB_IRQHandler
        DCD     GPIOCD_IRQHandler               ; 4:  GPIOCD_IRQHandler
        DCD     EXTI_IRQHandler                 ; 5:  EXTI_IRQHandler
        DCD     SRAM_PARITY_IRQHandler          ; 6:  SRAM_PARITY_IRQHandler
        DCD     CLKRDY_IRQHandler               ; 7:  CLKRDY_IRQHandler
        DCD     LCD_IRQHandler                  ; 8:  LCD_IRQHandler
        DCD     DMA_IRQHandler                  ; 9:  DMA_IRQHandler
        DCD     UART3_IRQHandler                ; 10: UART3_IRQHandler
        DCD     TKEY_IRQHandler                 ; 11: TKEY_IRQHandler
        DCD     ADC_IRQHandler                  ; 12: ADC_IRQHandler
        DCD     TIM1_BRK_UP_TRG_COM_IRQHandler  ; 13: TIM1_BRK_UP_TRG_COM_IRQHandler
        DCD     TIM1_CC_IRQHandler              ; 14: TIM1_CC_IRQHandler
        DCD     RSV_IRQHandler                  ; 15: Reserved
        DCD     TIM3_IRQHandler                 ; 16: TIM3_IRQHandler
        DCD     TIM6_IRQHandler                 ; 17: TIM6_IRQHandler
        DCD     RSV_IRQHandler                  ; 18: Reserved
        DCD     TIM14_IRQHandler                ; 19: TIM14_IRQHandler
        DCD     TIM15_IRQHandler                ; 20: TIM15_IRQHandler
        DCD     TIM16_IRQHandler                ; 21: TIM16_IRQHandler
        DCD     TIM17_IRQHandler                ; 22: TIM17_IRQHandler
        DCD     I2C1_IRQHandler                 ; 23: I2C1_IRQHandler
        DCD     I2C2_IRQHandler                 ; 24: I2C2_IRQHandler
        DCD     SPI1_IRQHandler                 ; 25: SPI1_IRQHandler
        DCD     SPI2_IRQHandler                 ; 26: SPI2_IRQHandler
        DCD     UART1_IRQHandler                ; 27: UART1_IRQHandler
        DCD     UART2_IRQHandler                ; 28: UART2_IRQHandler
        DCD     LPUART_IRQHandler               ; 29: LPUART_IRQHandler
        DCD     CAN1_IRQHandler                 ; 30: CAN1_IRQHandler
        DCD     AES_IRQHandler                  ; 31: AES_IRQHandler

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

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

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

        PUBWEAK LCD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LCD_IRQHandler
        B LCD_IRQHandler

        PUBWEAK DMA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_IRQHandler
        B DMA_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK TKEY_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TKEY_IRQHandler
        B TKEY_IRQHandler

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

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
        B TIM3_IRQHandler

        PUBWEAK TIM6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM6_IRQHandler
        B TIM6_IRQHandler

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

        PUBWEAK CAN1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_IRQHandler
        B CAN1_IRQHandler

        PUBWEAK AES_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AES_IRQHandler
        B AES_IRQHandler

        PUBWEAK RSV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RSV_IRQHandler
        B RSV_IRQHandler

        END
;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
