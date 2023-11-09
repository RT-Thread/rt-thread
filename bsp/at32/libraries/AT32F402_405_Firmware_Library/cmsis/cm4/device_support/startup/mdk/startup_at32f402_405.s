;**************************************************************************
;* @file     startup_at32f402_405.s
;* @brief    at32f402_405 startup file for keil
;* <<< Use Configuration Wizard in Context Menu >>>
;**************************************************************************
;

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                        ; Top of Stack
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
                DCD     ERTCAlarm_IRQHandler                ; ERTC Alarm through EXINT Line
                DCD     OTGFS1_WKUP_IRQHandler              ; OTGFS1 Wakeup from suspend
                DCD     0                                   ; Reserved
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
                DCD     TMR6_GLOBAL_IRQHandler              ; TMR6
                DCD     TMR7_GLOBAL_IRQHandler              ; TMR7
                DCD     DMA2_Channel1_IRQHandler            ; DMA1 Channel 1
                DCD     DMA2_Channel2_IRQHandler            ; DMA1 Channel 2
                DCD     DMA2_Channel3_IRQHandler            ; DMA1 Channel 3
                DCD     DMA2_Channel4_IRQHandler            ; DMA1 Channel 4
                DCD     DMA2_Channel5_IRQHandler            ; DMA1 Channel 5
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     OTGFS1_IRQHandler                   ; OTGFS1
                DCD     DMA2_Channel6_IRQHandler            ; DMA2 Channel 6
                DCD     DMA2_Channel7_IRQHandler            ; DMA2 Channel 7
                DCD     0                                   ; Reserved
                DCD     USART6_IRQHandler                   ; USART6
                DCD     I2C3_EVT_IRQHandler                 ; I2C3 Event
                DCD     I2C3_ERR_IRQHandler                 ; I2C3 Error
                DCD     OTGHS_EP1_OUT_IRQHandler            ; OTGHS endpoint1 out
                DCD     OTGHS_EP1_IN_IRQHandler             ; OTGHS endpoint1 in
                DCD     OTGHS_WKUP_IRQHandler               ; OTGHS Wakeup from suspend
                DCD     OTGHS_IRQHandler                    ; OTGHS
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     FPU_IRQHandler                      ; FPU
                DCD     UART7_IRQHandler                    ; UART7
                DCD     UART8_IRQHandler                    ; UART8
                DCD     0                                   ; Reserved
                DCD     I2SF5_IRQHandler                    ; I2SF5
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     QSPI1_IRQHandler                    ; QSPI1
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
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler                       [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                         [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                   [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                   [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                    [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler                  [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                         [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                      [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                     [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  WWDT_IRQHandler                     [WEAK]
                EXPORT  PVM_IRQHandler                      [WEAK]
                EXPORT  TAMP_STAMP_IRQHandler               [WEAK]
                EXPORT  ERTC_WKUP_IRQHandler                [WEAK]
                EXPORT  FLASH_IRQHandler                    [WEAK]
                EXPORT  CRM_IRQHandler                      [WEAK]
                EXPORT  EXINT0_IRQHandler                   [WEAK]
                EXPORT  EXINT1_IRQHandler                   [WEAK]
                EXPORT  EXINT2_IRQHandler                   [WEAK]
                EXPORT  EXINT3_IRQHandler                   [WEAK]
                EXPORT  EXINT4_IRQHandler                   [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler            [WEAK]
                EXPORT  ADC1_IRQHandler                     [WEAK]
                EXPORT  CAN1_TX_IRQHandler                  [WEAK]
                EXPORT  CAN1_RX0_IRQHandler                 [WEAK]
                EXPORT  CAN1_RX1_IRQHandler                 [WEAK]
                EXPORT  CAN1_SE_IRQHandler                  [WEAK]
                EXPORT  EXINT9_5_IRQHandler                 [WEAK]
                EXPORT  TMR1_BRK_TMR9_IRQHandler            [WEAK]
                EXPORT  TMR1_OVF_TMR10_IRQHandler           [WEAK]
                EXPORT  TMR1_TRG_HALL_TMR11_IRQHandler      [WEAK]
                EXPORT  TMR1_CH_IRQHandler                  [WEAK]
                EXPORT  TMR2_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR3_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR4_GLOBAL_IRQHandler              [WEAK]
                EXPORT  I2C1_EVT_IRQHandler                 [WEAK]
                EXPORT  I2C1_ERR_IRQHandler                 [WEAK]
                EXPORT  I2C2_EVT_IRQHandler                 [WEAK]
                EXPORT  I2C2_ERR_IRQHandler                 [WEAK]
                EXPORT  SPI1_IRQHandler                     [WEAK]
                EXPORT  SPI2_IRQHandler                     [WEAK]
                EXPORT  USART1_IRQHandler                   [WEAK]
                EXPORT  USART2_IRQHandler                   [WEAK]
                EXPORT  USART3_IRQHandler                   [WEAK]
                EXPORT  EXINT15_10_IRQHandler               [WEAK]
                EXPORT  ERTCAlarm_IRQHandler                [WEAK]
                EXPORT  OTGFS1_WKUP_IRQHandler              [WEAK]
                EXPORT  TMR13_GLOBAL_IRQHandler             [WEAK]
                EXPORT  TMR14_GLOBAL_IRQHandler             [WEAK]
                EXPORT  SPI3_IRQHandler                     [WEAK]
                EXPORT  USART4_IRQHandler                   [WEAK]
                EXPORT  USART5_IRQHandler                   [WEAK]
                EXPORT  TMR6_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR7_GLOBAL_IRQHandler              [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel4_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel5_IRQHandler            [WEAK]
                EXPORT  OTGFS1_IRQHandler                   [WEAK]
                EXPORT  DMA2_Channel6_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel7_IRQHandler            [WEAK]
                EXPORT  USART6_IRQHandler                   [WEAK]
                EXPORT  I2C3_EVT_IRQHandler                 [WEAK]
                EXPORT  I2C3_ERR_IRQHandler                 [WEAK]
                EXPORT  OTGHS_EP1_OUT_IRQHandler            [WEAK]
                EXPORT  OTGHS_EP1_IN_IRQHandler             [WEAK]
                EXPORT  OTGHS_WKUP_IRQHandler               [WEAK]
                EXPORT  OTGHS_IRQHandler                    [WEAK]
                EXPORT  FPU_IRQHandler                      [WEAK]
                EXPORT  UART7_IRQHandler                    [WEAK]
                EXPORT  UART8_IRQHandler                    [WEAK]
                EXPORT  I2SF5_IRQHandler                    [WEAK]
                EXPORT  QSPI1_IRQHandler                    [WEAK]
                EXPORT  DMAMUX_IRQHandler                   [WEAK]
                EXPORT  ACC_IRQHandler                      [WEAK]
WWDT_IRQHandler
PVM_IRQHandler
TAMP_STAMP_IRQHandler
ERTC_WKUP_IRQHandler
FLASH_IRQHandler
CRM_IRQHandler
EXINT0_IRQHandler
EXINT1_IRQHandler
EXINT2_IRQHandler
EXINT3_IRQHandler
EXINT4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_IRQHandler
CAN1_TX_IRQHandler
CAN1_RX0_IRQHandler
CAN1_RX1_IRQHandler
CAN1_SE_IRQHandler
EXINT9_5_IRQHandler
TMR1_BRK_TMR9_IRQHandler
TMR1_OVF_TMR10_IRQHandler
TMR1_TRG_HALL_TMR11_IRQHandler
TMR1_CH_IRQHandler
TMR2_GLOBAL_IRQHandler
TMR3_GLOBAL_IRQHandler
TMR4_GLOBAL_IRQHandler
I2C1_EVT_IRQHandler
I2C1_ERR_IRQHandler
I2C2_EVT_IRQHandler
I2C2_ERR_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXINT15_10_IRQHandler
ERTCAlarm_IRQHandler
OTGFS1_WKUP_IRQHandler
TMR13_GLOBAL_IRQHandler
TMR14_GLOBAL_IRQHandler
SPI3_IRQHandler
USART4_IRQHandler
USART5_IRQHandler
TMR6_GLOBAL_IRQHandler
TMR7_GLOBAL_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_IRQHandler
DMA2_Channel5_IRQHandler
OTGFS1_IRQHandler
DMA2_Channel6_IRQHandler
DMA2_Channel7_IRQHandler
USART6_IRQHandler
I2C3_EVT_IRQHandler
I2C3_ERR_IRQHandler
OTGHS_EP1_OUT_IRQHandler
OTGHS_EP1_IN_IRQHandler
OTGHS_WKUP_IRQHandler
OTGHS_IRQHandler
FPU_IRQHandler
UART7_IRQHandler
UART8_IRQHandler
I2SF5_IRQHandler
QSPI1_IRQHandler
DMAMUX_IRQHandler
ACC_IRQHandler
                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB

                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit

                 ELSE

                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap

__user_initial_stackheap

                 LDR     R0, = Heap_Mem
                 LDR     R1, = (Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END
