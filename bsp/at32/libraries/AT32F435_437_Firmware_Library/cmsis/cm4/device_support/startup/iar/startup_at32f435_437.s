;**************************************************************************
;* @file     startup_at32f435_437.s
;* @version  v2.0.8
;* @date     2022-04-25
;* @brief    at32f435_437 startup file for IAR Systems
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
        DCD     EDMA_Stream1_IRQHandler             ; EDMA Stream 1
        DCD     EDMA_Stream2_IRQHandler             ; EDMA Stream 2
        DCD     EDMA_Stream3_IRQHandler             ; EDMA Stream 3
        DCD     EDMA_Stream4_IRQHandler             ; EDMA Stream 4
        DCD     EDMA_Stream5_IRQHandler             ; EDMA Stream 5
        DCD     EDMA_Stream6_IRQHandler             ; EDMA Stream 6
        DCD     EDMA_Stream7_IRQHandler             ; EDMA Stream 7
        DCD     ADC1_2_3_IRQHandler                 ; ADC1 & ADC2 & ADC3
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
        DCD     SPI2_I2S2EXT_IRQHandler             ; SPI2
        DCD     USART1_IRQHandler                   ; USART1
        DCD     USART2_IRQHandler                   ; USART2
        DCD     USART3_IRQHandler                   ; USART3
        DCD     EXINT15_10_IRQHandler               ; EXINT Line [15:10]
        DCD     ERTCAlarm_IRQHandler                ; RTC Alarm through EXINT Line
        DCD     OTGFS1_WKUP_IRQHandler              ; OTGFS1 Wakeup from suspend
        DCD     TMR8_BRK_TMR12_IRQHandler           ; TMR8 Brake and TMR12
        DCD     TMR8_OVF_TMR13_IRQHandler           ; TMR8 Overflow and TMR13
        DCD     TMR8_TRG_HALL_TMR14_IRQHandler      ; TMR8 Trigger and hall and TMR14
        DCD     TMR8_CH_IRQHandler                  ; TMR8 Channel
        DCD     EDMA_Stream8_IRQHandler             ; EDMA Stream 8
        DCD     XMC_IRQHandler                      ; XMC
        DCD     SDIO1_IRQHandler                    ; SDIO1
        DCD     TMR5_GLOBAL_IRQHandler              ; TMR5
        DCD     SPI3_I2S3EXT_IRQHandler             ; SPI3
        DCD     UART4_IRQHandler                    ; UART4
        DCD     UART5_IRQHandler                    ; UART5
        DCD     TMR6_DAC_GLOBAL_IRQHandler          ; TMR6 & DAC
        DCD     TMR7_GLOBAL_IRQHandler              ; TMR7
        DCD     DMA1_Channel1_IRQHandler            ; DMA1 Channel 1
        DCD     DMA1_Channel2_IRQHandler            ; DMA1 Channel 2
        DCD     DMA1_Channel3_IRQHandler            ; DMA1 Channel 3
        DCD     DMA1_Channel4_IRQHandler            ; DMA1 Channel 4
        DCD     DMA1_Channel5_IRQHandler            ; DMA1 Channel 5
        DCD     EMAC_IRQHandler                     ; EMAC
        DCD     EMAC_WKUP_IRQHandler                ; EMAC Wakeup
        DCD     CAN2_TX_IRQHandler                  ; CAN2 TX
        DCD     CAN2_RX0_IRQHandler                 ; CAN2 RX0
        DCD     CAN2_RX1_IRQHandler                 ; CAN2 RX1
        DCD     CAN2_SE_IRQHandler                  ; CAN2 SE
        DCD     OTGFS1_IRQHandler                   ; OTGFS1
        DCD     DMA1_Channel6_IRQHandler            ; DMA1 Channel 6
        DCD     DMA1_Channel7_IRQHandler            ; DMA1 Channel 7
        DCD     0                                   ; Reserved
        DCD     USART6_IRQHandler                   ; USART6
        DCD     I2C3_EVT_IRQHandler                 ; I2C3 Event
        DCD     I2C3_ERR_IRQHandler                 ; I2C3 Error
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     OTGFS2_WKUP_IRQHandler              ; OTGFS2 Wakeup from suspend
        DCD     OTGFS2_IRQHandler                   ; OTGFS2
        DCD     DVP_IRQHandler                      ; DVP
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     FPU_IRQHandler                      ; FPU
        DCD     UART7_IRQHandler                    ; UART7
        DCD     UART8_IRQHandler                    ; UART8
        DCD     SPI4_IRQHandler                     ; SPI4
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     QSPI2_IRQHandler                    ; QSPI2
        DCD     QSPI1_IRQHandler                    ; QSPI1
        DCD     0                                   ; Reserved
        DCD     DMAMUX_IRQHandler                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     SDIO2_IRQHandler                    ; SDIO2
        DCD     ACC_IRQHandler                      ; ACC
        DCD     TMR20_BRK_IRQHandler                ; TMR20 Brake
        DCD     TMR20_OVF_IRQHandler                ; TMR20 Overflow
        DCD     TMR20_TRG_HALL_IRQHandler           ; TMR20 Trigger and hall
        DCD     TMR20_CH_IRQHandler                 ; TMR20 Channel
        DCD     DMA2_Channel1_IRQHandler            ; DMA2 Channel 1
        DCD     DMA2_Channel2_IRQHandler            ; DMA2 Channel 2
        DCD     DMA2_Channel3_IRQHandler            ; DMA2 Channel 3
        DCD     DMA2_Channel4_IRQHandler            ; DMA2 Channel 4
        DCD     DMA2_Channel5_IRQHandler            ; DMA2 Channel 5
        DCD     DMA2_Channel6_IRQHandler            ; DMA2 Channel 6
        DCD     DMA2_Channel7_IRQHandler            ; DMA2 Channel 7

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

        PUBWEAK EDMA_Stream1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EDMA_Stream1_IRQHandler
        B EDMA_Stream1_IRQHandler

        PUBWEAK EDMA_Stream2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EDMA_Stream2_IRQHandler
        B EDMA_Stream2_IRQHandler

        PUBWEAK EDMA_Stream3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EDMA_Stream3_IRQHandler
        B EDMA_Stream3_IRQHandler

        PUBWEAK EDMA_Stream4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EDMA_Stream4_IRQHandler
        B EDMA_Stream4_IRQHandler

        PUBWEAK EDMA_Stream5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EDMA_Stream5_IRQHandler
        B EDMA_Stream5_IRQHandler

        PUBWEAK EDMA_Stream6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EDMA_Stream6_IRQHandler
        B EDMA_Stream6_IRQHandler

        PUBWEAK EDMA_Stream7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EDMA_Stream7_IRQHandler
        B EDMA_Stream7_IRQHandler

        PUBWEAK ADC1_2_3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_2_3_IRQHandler
        B ADC1_2_3_IRQHandler

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

        PUBWEAK SPI2_I2S2EXT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_I2S2EXT_IRQHandler
        B SPI2_I2S2EXT_IRQHandler

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

        PUBWEAK TMR8_BRK_TMR12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_BRK_TMR12_IRQHandler
        B TMR8_BRK_TMR12_IRQHandler

        PUBWEAK TMR8_OVF_TMR13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_OVF_TMR13_IRQHandler
        B TMR8_OVF_TMR13_IRQHandler

        PUBWEAK TMR8_TRG_HALL_TMR14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_TRG_HALL_TMR14_IRQHandler
        B TMR8_TRG_HALL_TMR14_IRQHandler

        PUBWEAK TMR8_CH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_CH_IRQHandler
        B TMR8_CH_IRQHandler

        PUBWEAK EDMA_Stream8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EDMA_Stream8_IRQHandler
        B EDMA_Stream8_IRQHandler

        PUBWEAK XMC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
XMC_IRQHandler
        B XMC_IRQHandler

        PUBWEAK SDIO1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO1_IRQHandler
        B SDIO1_IRQHandler

        PUBWEAK TMR5_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR5_GLOBAL_IRQHandler
        B TMR5_GLOBAL_IRQHandler

        PUBWEAK SPI3_I2S3EXT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI3_I2S3EXT_IRQHandler
        B SPI3_I2S3EXT_IRQHandler

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART4_IRQHandler
        B UART4_IRQHandler

        PUBWEAK UART5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART5_IRQHandler
        B UART5_IRQHandler

        PUBWEAK TMR6_DAC_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR6_DAC_GLOBAL_IRQHandler
        B TMR6_DAC_GLOBAL_IRQHandler

        PUBWEAK TMR7_GLOBAL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR7_GLOBAL_IRQHandler
        B TMR7_GLOBAL_IRQHandler

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

        PUBWEAK EMAC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EMAC_IRQHandler
        B EMAC_IRQHandler

        PUBWEAK EMAC_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EMAC_WKUP_IRQHandler
        B EMAC_WKUP_IRQHandler

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

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK DMA1_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel7_IRQHandler
        B DMA1_Channel7_IRQHandler

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

        PUBWEAK OTGFS2_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTGFS2_WKUP_IRQHandler
        B OTGFS2_WKUP_IRQHandler

        PUBWEAK OTGFS2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTGFS2_IRQHandler
        B OTGFS2_IRQHandler

        PUBWEAK DVP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DVP_IRQHandler
        B DVP_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK UART7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART7_IRQHandler
        B UART7_IRQHandler

        PUBWEAK UART8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART8_IRQHandler
        B UART8_IRQHandler

        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI4_IRQHandler
        B SPI4_IRQHandler

        PUBWEAK QSPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QSPI2_IRQHandler
        B QSPI2_IRQHandler

        PUBWEAK QSPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QSPI1_IRQHandler
        B QSPI1_IRQHandler

        PUBWEAK DMAMUX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMAMUX_IRQHandler
        B DMAMUX_IRQHandler

        PUBWEAK SDIO2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO2_IRQHandler
        B SDIO2_IRQHandler

        PUBWEAK ACC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ACC_IRQHandler
        B ACC_IRQHandler

        PUBWEAK TMR20_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR20_BRK_IRQHandler
        B TMR20_BRK_IRQHandler

        PUBWEAK TMR20_OVF_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR20_OVF_IRQHandler
        B TMR20_OVF_IRQHandler

        PUBWEAK TMR20_TRG_HALL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR20_TRG_HALL_IRQHandler
        B TMR20_TRG_HALL_IRQHandler

        PUBWEAK TMR20_CH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR20_CH_IRQHandler
        B TMR20_CH_IRQHandler

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

        PUBWEAK DMA2_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel6_IRQHandler
        B DMA2_Channel6_IRQHandler

        PUBWEAK DMA2_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel7_IRQHandler
        B DMA2_Channel7_IRQHandler

        END
