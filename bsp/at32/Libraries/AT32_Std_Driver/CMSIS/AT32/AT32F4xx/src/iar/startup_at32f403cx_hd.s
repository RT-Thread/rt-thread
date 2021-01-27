;**************************************************************************
;* File Name    : startup_at32f403cx_hd.s
;* Description  : at32f4xx startup file for IAR Systems
;* Date         : 2018-02-26
;* Version      : V1.0.4
;**************************************************************************
;

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
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
        DCD     Reset_Handler                   ; Reset Handler
        DCD     NMI_Handler                     ; NMI Handler
        DCD     HardFault_Handler               ; Hard Fault Handler
        DCD     MemManage_Handler               ; MPU Fault Handler
        DCD     BusFault_Handler                ; Bus Fault Handler
        DCD     UsageFault_Handler              ; Usage Fault Handler
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     SVC_Handler                     ; SVCall Handler
        DCD     DebugMon_Handler                ; Debug Monitor Handler
        DCD     0                               ; Reserved
        DCD     PendSV_Handler                  ; PendSV Handler
        DCD     SysTick_Handler                 ; SysTick Handler

        ; External Interrupts
        DCD     WWDG_IRQHandler                 ; Window Watchdog
        DCD     PVD_IRQHandler                  ; PVD through EXTI Line detect
        DCD     TAMPER_IRQHandler               ; Tamper
        DCD     RTC_IRQHandler                  ; RTC
        DCD     FLASH_IRQHandler                ; Flash
        DCD     RCC_IRQHandler                  ; RCC
        DCD     EXTI0_IRQHandler                ; EXTI Line 0
        DCD     EXTI1_IRQHandler                ; EXTI Line 1
        DCD     EXTI2_IRQHandler                ; EXTI Line 2
        DCD     EXTI3_IRQHandler                ; EXTI Line 3
        DCD     EXTI4_IRQHandler                ; EXTI Line 4
        DCD     DMA1_Channel1_IRQHandler        ; DMA1 Channel 1
        DCD     DMA1_Channel2_IRQHandler        ; DMA1 Channel 2
        DCD     DMA1_Channel3_IRQHandler        ; DMA1 Channel 3
        DCD     DMA1_Channel4_IRQHandler        ; DMA1 Channel 4
        DCD     DMA1_Channel5_IRQHandler        ; DMA1 Channel 5
        DCD     DMA1_Channel6_IRQHandler        ; DMA1 Channel 6
        DCD     DMA1_Channel7_IRQHandler        ; DMA1 Channel 7
        DCD     ADC1_2_IRQHandler               ; ADC1 & ADC2
        DCD     USB_HP_CAN1_TX_IRQHandler       ; USB High Priority or CAN1 TX
        DCD     USB_LP_CAN1_RX0_IRQHandler      ; USB Low  Priority or CAN1 RX0
        DCD     CAN1_RX1_IRQHandler             ; CAN1 RX1
        DCD     CAN1_SCE_IRQHandler             ; CAN1 SCE
        DCD     EXTI9_5_IRQHandler              ; EXTI Line [9:5]
        DCD     TMR1_BRK_TMR9_IRQHandler        ; TMR1 Break and TMR9
        DCD     TMR1_OV_TMR10_IRQHandler        ; TMR1 Update and TMR10
        DCD     TMR1_TRG_HALL_TMR11_IRQHandler  ; TMR1 Trigger and Commutation and TMR11
        DCD     TMR1_CC_IRQHandler              ; TMR1 Capture Compare
        DCD     TMR2_GLOBAL_IRQHandler          ; TMR2
        DCD     TMR3_GLOBAL_IRQHandler          ; TMR3
        DCD     TMR4_GLOBAL_IRQHandler          ; TMR4
        DCD     I2C1_EV_IRQHandler              ; I2C1 Event
        DCD     I2C1_ER_IRQHandler              ; I2C1 Error
        DCD     I2C2_EV_IRQHandler              ; I2C2 Event
        DCD     I2C2_ER_IRQHandler              ; I2C2 Error
        DCD     SPI1_IRQHandler                 ; SPI1
        DCD     SPI2_IRQHandler                 ; SPI2
        DCD     USART1_IRQHandler               ; USART1
        DCD     USART2_IRQHandler               ; USART2
        DCD     USART3_IRQHandler               ; USART3
        DCD     EXTI15_10_IRQHandler            ; EXTI Line [15:10]
        DCD     RTCAlarm_IRQHandler             ; RTC Alarm through EXTI Line
        DCD     USBWakeUp_IRQHandler            ; USB Wakeup from suspend
        DCD     TMR8_BRK_TMR12_IRQHandler       ; TMR8 Break and TMR12
        DCD     TMR8_OV_TMR13_IRQHandler        ; TMR8 Update and TMR13
        DCD     TMR8_TRG_HALL_TMR14_IRQHandler  ; TMR8 Trigger and Commutation and TMR14
        DCD     TMR8_CC_IRQHandler              ; TMR8 Capture Compare
        DCD     ADC3_IRQHandler                 ; ADC3
        DCD     0                               ; Reserved
        DCD     0                				; Reserved
        DCD     TMR5_GLOBAL_IRQHandler          ; TMR5
        DCD     SPI3_IRQHandler                 ; SPI3
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
		DCD		TMR6_GLOBAL_IRQHandler			; TMR6
		DCD		TMR7_GLOBAL_IRQHandler			; TMR7
        DCD     DMA2_Channel1_IRQHandler        ; DMA2 Channel1
        DCD     DMA2_Channel2_IRQHandler        ; DMA2 Channel2
        DCD     DMA2_Channel3_IRQHandler        ; DMA2 Channel3
        DCD     DMA2_Channel4_5_IRQHandler      ; DMA2 Channel4 & Channel5
        DCD     SDIO2_IRQHandler                ; SDIO2
        DCD     I2C3_EV_IRQHandler              ; I2C3 Event
        DCD     I2C3_ER_IRQHandler              ; I2C3 Error
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDG_IRQHandler
        B WWDG_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PVD_IRQHandler
        B PVD_IRQHandler

        PUBWEAK TAMPER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TAMPER_IRQHandler
        B TAMPER_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RCC_IRQHandler
        B RCC_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel2_IRQHandler
        B DMA1_Channel2_IRQHandler

        PUBWEAK DMA1_Channel3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel3_IRQHandler
        B DMA1_Channel3_IRQHandler

        PUBWEAK DMA1_Channel4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel4_IRQHandler
        B DMA1_Channel4_IRQHandler

        PUBWEAK DMA1_Channel5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel5_IRQHandler
        B DMA1_Channel5_IRQHandler

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK DMA1_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel7_IRQHandler
        B DMA1_Channel7_IRQHandler

        PUBWEAK ADC1_2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_2_IRQHandler
        B ADC1_2_IRQHandler

        PUBWEAK USB_HP_CAN1_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_HP_CAN1_TX_IRQHandler
        B USB_HP_CAN1_TX_IRQHandler

        PUBWEAK USB_LP_CAN1_RX0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_LP_CAN1_RX0_IRQHandler
        B USB_LP_CAN1_RX0_IRQHandler

        PUBWEAK CAN1_RX1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_RX1_IRQHandler
        B CAN1_RX1_IRQHandler

        PUBWEAK CAN1_SCE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_SCE_IRQHandler
        B CAN1_SCE_IRQHandler

        PUBWEAK EXTI9_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI9_5_IRQHandler
        B EXTI9_5_IRQHandler

        PUBWEAK TMR1_BRK_TMR9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_BRK_TMR9_IRQHandler
        B TMR1_BRK_TMR9_IRQHandler

        PUBWEAK TMR1_OV_TMR10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_OV_TMR10_IRQHandler
        B TMR1_OV_TMR10_IRQHandler

        PUBWEAK TMR1_TRG_HALL_TMR11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_TRG_HALL_TMR11_IRQHandler
        B TMR1_TRG_HALL_TMR11_IRQHandler

        PUBWEAK TMR1_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_CC_IRQHandler
        B TMR1_CC_IRQHandler

        PUBWEAK TMR2_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR2_GLOBAL_IRQHandler
        B TMR2_GLOBAL_IRQHandler

        PUBWEAK TMR3_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR3_GLOBAL_IRQHandler
        B TMR3_GLOBAL_IRQHandler

        PUBWEAK TMR4_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR4_GLOBAL_IRQHandler
        B TMR4_GLOBAL_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler

        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_EV_IRQHandler
        B I2C2_EV_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_IRQHandler
        B USART3_IRQHandler

        PUBWEAK EXTI15_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI15_10_IRQHandler
        B EXTI15_10_IRQHandler

        PUBWEAK RTCAlarm_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTCAlarm_IRQHandler
        B RTCAlarm_IRQHandler

        PUBWEAK USBWakeUp_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USBWakeUp_IRQHandler
        B USBWakeUp_IRQHandler

        PUBWEAK TMR8_BRK_TMR12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_BRK_TMR12_IRQHandler
        B TMR8_BRK_TMR12_IRQHandler

        PUBWEAK TMR8_OV_TMR13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_OV_TMR13_IRQHandler
        B TMR8_OV_TMR13_IRQHandler

        PUBWEAK TMR8_TRG_HALL_TMR14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_TRG_HALL_TMR14_IRQHandler
        B TMR8_TRG_HALL_TMR14_IRQHandler

        PUBWEAK TMR8_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_CC_IRQHandler
        B TMR8_CC_IRQHandler

        PUBWEAK ADC3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC3_IRQHandler
        B ADC3_IRQHandler
		
        PUBWEAK TMR5_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR5_GLOBAL_IRQHandler
        B TMR5_GLOBAL_IRQHandler

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI3_IRQHandler
        B SPI3_IRQHandler
		PUBWEAK TMR6_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR6_GLOBAL_IRQHandler
        B TMR6_GLOBAL_IRQHandler

		PUBWEAK TMR7_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR7_GLOBAL_IRQHandler
        B TMR7_GLOBAL_IRQHandler

        PUBWEAK DMA2_Channel1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel1_IRQHandler
        B DMA2_Channel1_IRQHandler

        PUBWEAK DMA2_Channel2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel2_IRQHandler
        B DMA2_Channel2_IRQHandler

        PUBWEAK DMA2_Channel3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel3_IRQHandler
        B DMA2_Channel3_IRQHandler

        PUBWEAK DMA2_Channel4_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel4_5_IRQHandler
        B DMA2_Channel4_5_IRQHandler

        PUBWEAK SDIO2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO2_IRQHandler
        B SDIO2_IRQHandler
		
        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_EV_IRQHandler
        B I2C3_EV_IRQHandler
		
        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler
		
        END
