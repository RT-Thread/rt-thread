;**************************************************************************
;* File Name    : startup_at32f415c8t7.s
;* Description  : at32f4xx startup file for IAR Systems
;* Date         : 2019-05-30
;* Version      : V1.0.0
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
        DCD     TAMP_STAMP_IRQHandler           ; Tamper and TimeStamps through the EXTI line
        DCD     ERTC_WKUP_IRQHandler            ; ERTC Wakeup through the EXTI line
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
        DCD     CAN1_TX_IRQHandler              ; CAN1 TX
        DCD     CAN1_RX0_IRQHandler             ; CAN1 RX0
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
        DCD     ERTCAlarm_IRQHandler            ; ERTC Alarm through EXTI Line
        DCD     USBWakeUp_IRQHandler            ; USB Wakeup from suspend
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                  				; Reserved
        DCD     0                  				; Reserved
        DCD     SDIO_IRQHandler                 ; SDIO
        DCD     TMR5_GLOBAL_IRQHandler          ; TMR5
        DCD     0                  				; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                  				; Reserved
        DCD     0                  				; Reserved
        DCD     DMA2_Channel1_IRQHandler        ; DMA2 Channel1
        DCD     DMA2_Channel2_IRQHandler        ; DMA2 Channel2
        DCD     DMA2_Channel3_IRQHandler        ; DMA2 Channel3
        DCD     DMA2_Channel4_5_IRQHandler      ; DMA2 Channel4 & Channel5
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     USBOTG_IRQHandler               ; USBOTG
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     COMP1_IRQHandler                ; COMP1
        DCD     COMP2_IRQHandler                ; COMP2
        DCD     ACC_IRQHandler                  ; ACC
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     DMA2_Channel6_7_IRQHandler      ; DMA2 Channel6 & Channel7
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

        PUBWEAK TAMP_STAMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TAMP_STAMP_IRQHandler
        B TAMP_STAMP_IRQHandler

        PUBWEAK ERTC_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ERTC_WKUP_IRQHandler
        B ERTC_WKUP_IRQHandler

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

        PUBWEAK CAN1_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_TX_IRQHandler
        B CAN1_TX_IRQHandler

        PUBWEAK CAN1_RX0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_RX0_IRQHandler
        B CAN1_RX0_IRQHandler

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

        PUBWEAK ERTCAlarm_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ERTCAlarm_IRQHandler
        B ERTCAlarm_IRQHandler

        PUBWEAK USBWakeUp_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USBWakeUp_IRQHandler
        B USBWakeUp_IRQHandler

        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO_IRQHandler
        B SDIO_IRQHandler

        PUBWEAK TMR5_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR5_GLOBAL_IRQHandler
        B TMR5_GLOBAL_IRQHandler

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

        PUBWEAK USBOTG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USBOTG_IRQHandler
        B USBOTG_IRQHandler

        PUBWEAK COMP1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
COMP1_IRQHandler
        B COMP1_IRQHandler
        
        PUBWEAK COMP2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
COMP2_IRQHandler
        B COMP2_IRQHandler

        PUBWEAK ACC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ACC_IRQHandler
        B ACC_IRQHandler

        PUBWEAK DMA2_Channel6_7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel6_7_IRQHandler
        B DMA2_Channel6_7_IRQHandler
		
        END
