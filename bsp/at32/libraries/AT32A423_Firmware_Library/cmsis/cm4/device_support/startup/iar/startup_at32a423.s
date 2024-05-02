;**************************************************************************
;* @file     startup_at32a423.s
;* @brief    at32a423 startup file for IAR Systems
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
        DCD     Reset_Handler                       ; Reset Handler
        DCD     NMI_Handler                         ; NMI Handler
        DCD     HardFault_Handler                   ; Hard Fault Handler
        DCD     MemManage_Handler                   ; MPU Fault Handler
        DCD     BusFault_Handler                    ; Bus Fault Handler
        DCD     UsageFault_Handler                  ; Usage Fault Handler
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     SVC_Handler                         ; SVCall Handler
        DCD     DebugMon_Handler                    ; Debug Monitor Handler
        DCD     0                                   ; Reserved
        DCD     PendSV_Handler                      ; PendSV Handler
        DCD     SysTick_Handler                     ; SysTick Handler

        ; External Interrupts
        DCD     WWDT_IRQHandler                     ; Window Watchdog Timer
        DCD     PVM_IRQHandler                      ; PVM through EXINT Line detect
        DCD     TAMP_STAMP_IRQHandler               ; Tamper and TimeStamps through the EXINT line
        DCD     ERTC_WKUP_IRQHandler                ; ERTC Wakeup through the EXINT line
        DCD     FLASH_IRQHandler                    ; Flash
        DCD     CRM_IRQHandler                      ; CRM
        DCD     EXINT0_IRQHandler                   ; EXINT Line 0
        DCD     EXINT1_IRQHandler                   ; EXINT Line 1
        DCD     EXINT2_IRQHandler                   ; EXINT Line 2
        DCD     EXINT3_IRQHandler                   ; EXINT Line 3
        DCD     EXINT4_IRQHandler                   ; EXINT Line 4
        DCD     DMA1_Channel1_IRQHandler            ; DMA1 Channel 1
        DCD     DMA1_Channel2_IRQHandler            ; DMA1 Channel 2
        DCD     DMA1_Channel3_IRQHandler            ; DMA1 Channel 3
        DCD     DMA1_Channel4_IRQHandler            ; DMA1 Channel 4
        DCD     DMA1_Channel5_IRQHandler            ; DMA1 Channel 5
        DCD     DMA1_Channel6_IRQHandler            ; DMA1 Channel 6
        DCD     DMA1_Channel7_IRQHandler            ; DMA1 Channel 7
        DCD     ADC1_IRQHandler                     ; ADC1
        DCD     CAN1_TX_IRQHandler                  ; CAN1 TX
        DCD     CAN1_RX0_IRQHandler                 ; CAN1 RX0
        DCD     CAN1_RX1_IRQHandler                 ; CAN1 RX1
        DCD     CAN1_SE_IRQHandler                  ; CAN1 SE
        DCD     EXINT9_5_IRQHandler                 ; EXINT Line [9:5]
        DCD     TMR1_BRK_TMR9_IRQHandler            ; TMR1 Brake and TMR9
        DCD     TMR1_OVF_TMR10_IRQHandler           ; TMR1 Overflow and TMR10
        DCD     TMR1_TRG_HALL_TMR11_IRQHandler      ; TMR1 Trigger and hall and TMR11
        DCD     TMR1_CH_IRQHandler                  ; TMR1 Channel
        DCD     TMR2_GLOBAL_IRQHandler              ; TMR2
        DCD     TMR3_GLOBAL_IRQHandler              ; TMR3
        DCD     TMR4_GLOBAL_IRQHandler              ; TMR4
        DCD     I2C1_EVT_IRQHandler                 ; I2C1 Event
        DCD     I2C1_ERR_IRQHandler                 ; I2C1 Error
        DCD     I2C2_EVT_IRQHandler                 ; I2C2 Event
        DCD     I2C2_ERR_IRQHandler                 ; I2C2 Error
        DCD     SPI1_IRQHandler                     ; SPI1
        DCD     SPI2_IRQHandler                     ; SPI2
        DCD     USART1_IRQHandler                   ; USART1
        DCD     USART2_IRQHandler                   ; USART2
        DCD     USART3_IRQHandler                   ; USART3
        DCD     EXINT15_10_IRQHandler               ; EXINT Line [15:10]
        DCD     ERTCAlarm_IRQHandler                ; RTC Alarm through EXINT Line
        DCD     OTGFS1_WKUP_IRQHandler              ; OTGFS1 Wakeup from suspend
        DCD     TMR12_GLOBAL_IRQHandler             ; TMR12
        DCD     TMR13_GLOBAL_IRQHandler             ; TMR13
        DCD     TMR14_GLOBAL_IRQHandler             ; TMR14
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     SPI3_IRQHandler                     ; SPI3
        DCD     USART4_IRQHandler                   ; USART4
        DCD     USART5_IRQHandler                   ; USART5
        DCD     TMR6_DAC_GLOBAL_IRQHandler          ; TMR6 & DAC
        DCD     TMR7_GLOBAL_IRQHandler              ; TMR7
        DCD     DMA2_Channel1_IRQHandler            ; DMA2 Channel 1
        DCD     DMA2_Channel2_IRQHandler            ; DMA2 Channel 2
        DCD     DMA2_Channel3_IRQHandler            ; DMA2 Channel 3
        DCD     DMA2_Channel4_IRQHandler            ; DMA2 Channel 4
        DCD     DMA2_Channel5_IRQHandler            ; DMA2 Channel 5
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     CAN2_TX_IRQHandler                  ; CAN2 TX
        DCD     CAN2_RX0_IRQHandler                 ; CAN2 RX0
        DCD     CAN2_RX1_IRQHandler                 ; CAN2 RX1
        DCD     CAN2_SE_IRQHandler                  ; CAN2 SE
        DCD     OTGFS1_IRQHandler                   ; OTGFS1
        DCD     DMA2_Channel6_IRQHandler            ; DMA2 Channel 6
        DCD     DMA2_Channel7_IRQHandler            ; DMA2 Channel 7
        DCD     0                                   ; Reserved
        DCD     USART6_IRQHandler                   ; USART6
        DCD     I2C3_EVT_IRQHandler                 ; I2C3 Event
        DCD     I2C3_ERR_IRQHandler                 ; I2C3 Error
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     FPU_IRQHandler                      ; FPU
        DCD     USART7_IRQHandler                   ; USART7
        DCD     USART8_IRQHandler                   ; USART8
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     DMAMUX_IRQHandler                   ; DMAMUX
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     ACC_IRQHandler                      ; ACC

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

        PUBWEAK WWDT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDT_IRQHandler
        B WWDT_IRQHandler

        PUBWEAK PVM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PVM_IRQHandler
        B PVM_IRQHandler

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

        PUBWEAK CRM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CRM_IRQHandler
        B CRM_IRQHandler

        PUBWEAK EXINT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXINT0_IRQHandler
        B EXINT0_IRQHandler

        PUBWEAK EXINT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXINT1_IRQHandler
        B EXINT1_IRQHandler

        PUBWEAK EXINT2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXINT2_IRQHandler
        B EXINT2_IRQHandler

        PUBWEAK EXINT3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXINT3_IRQHandler
        B EXINT3_IRQHandler

        PUBWEAK EXINT4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXINT4_IRQHandler
        B EXINT4_IRQHandler

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

        PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_IRQHandler
        B ADC1_IRQHandler

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

        PUBWEAK CAN1_SE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_SE_IRQHandler
        B CAN1_SE_IRQHandler

        PUBWEAK EXINT9_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXINT9_5_IRQHandler
        B EXINT9_5_IRQHandler

        PUBWEAK TMR1_BRK_TMR9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_BRK_TMR9_IRQHandler
        B TMR1_BRK_TMR9_IRQHandler

        PUBWEAK TMR1_OVF_TMR10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_OVF_TMR10_IRQHandler
        B TMR1_OVF_TMR10_IRQHandler

        PUBWEAK TMR1_TRG_HALL_TMR11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_TRG_HALL_TMR11_IRQHandler
        B TMR1_TRG_HALL_TMR11_IRQHandler

        PUBWEAK TMR1_CH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_CH_IRQHandler
        B TMR1_CH_IRQHandler

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

        PUBWEAK I2C1_EVT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_EVT_IRQHandler
        B I2C1_EVT_IRQHandler

        PUBWEAK I2C1_ERR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_ERR_IRQHandler
        B I2C1_ERR_IRQHandler

        PUBWEAK I2C2_EVT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_EVT_IRQHandler
        B I2C2_EVT_IRQHandler

        PUBWEAK I2C2_ERR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_ERR_IRQHandler
        B I2C2_ERR_IRQHandler

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

        PUBWEAK EXINT15_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXINT15_10_IRQHandler
        B EXINT15_10_IRQHandler

        PUBWEAK ERTCAlarm_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ERTCAlarm_IRQHandler
        B ERTCAlarm_IRQHandler

        PUBWEAK OTGFS1_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTGFS1_WKUP_IRQHandler
        B OTGFS1_WKUP_IRQHandler

        PUBWEAK TMR12_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR12_GLOBAL_IRQHandler
        B TMR12_GLOBAL_IRQHandler

        PUBWEAK TMR13_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR13_GLOBAL_IRQHandler
        B TMR13_GLOBAL_IRQHandler

        PUBWEAK TMR14_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR14_GLOBAL_IRQHandler
        B TMR14_GLOBAL_IRQHandler

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI3_IRQHandler
        B SPI3_IRQHandler

        PUBWEAK USART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART4_IRQHandler
        B USART4_IRQHandler

        PUBWEAK USART5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART5_IRQHandler
        B USART5_IRQHandler

        PUBWEAK TMR6_DAC_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR6_DAC_GLOBAL_IRQHandler
        B TMR6_DAC_GLOBAL_IRQHandler

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

        PUBWEAK DMA2_Channel4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel4_IRQHandler
        B DMA2_Channel4_IRQHandler

        PUBWEAK DMA2_Channel5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel5_IRQHandler
        B DMA2_Channel5_IRQHandler

        PUBWEAK CAN2_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_TX_IRQHandler
        B CAN2_TX_IRQHandler

        PUBWEAK CAN2_RX0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_RX0_IRQHandler
        B CAN2_RX0_IRQHandler

        PUBWEAK CAN2_RX1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_RX1_IRQHandler
        B CAN2_RX1_IRQHandler

        PUBWEAK CAN2_SE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_SE_IRQHandler
        B CAN2_SE_IRQHandler

        PUBWEAK OTGFS1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTGFS1_IRQHandler
        B OTGFS1_IRQHandler

        PUBWEAK DMA2_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel6_IRQHandler
        B DMA2_Channel6_IRQHandler

        PUBWEAK DMA2_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel7_IRQHandler
        B DMA2_Channel7_IRQHandler

        PUBWEAK USART6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART6_IRQHandler
        B USART6_IRQHandler

        PUBWEAK I2C3_EVT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_EVT_IRQHandler
        B I2C3_EVT_IRQHandler

        PUBWEAK I2C3_ERR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_ERR_IRQHandler
        B I2C3_ERR_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK USART7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART7_IRQHandler
        B USART7_IRQHandler

        PUBWEAK USART8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART8_IRQHandler
        B USART8_IRQHandler

        PUBWEAK DMAMUX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMAMUX_IRQHandler
        B DMAMUX_IRQHandler

        PUBWEAK ACC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ACC_IRQHandler
        B ACC_IRQHandler

        END
