;**************************************************************************
;* @file     startup_at32f425.s
;* @brief    startup_at32f425 startup file for keil
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
                DCD     ERTC_IRQHandler                     ; ERTC
                DCD     FLASH_IRQHandler                    ; Flash
                DCD     CRM_IRQHandler                      ; CRM
                DCD     EXINT1_0_IRQHandler                 ; EXINT Line 1 & 0
                DCD     EXINT3_2_IRQHandler                 ; EXINT Line 3 & 2
                DCD     EXINT15_4_IRQHandler                ; EXINT Line 15 ~ 4
                DCD     ACC_IRQHandler                      ; ACC
                DCD     DMA1_Channel1_IRQHandler            ; DMA1 Channel 1
                DCD     DMA1_Channel3_2_IRQHandler          ; DMA1 Channel 3 & 2
                DCD     DMA1_Channel7_4_IRQHandler          ; DMA1 Channel 7 & 4
                DCD     ADC1_IRQHandler                     ; ADC1
                DCD     TMR1_BRK_OVF_TRG_HALL_IRQHandler    ; TMR1 brake overflow trigger and hall
                DCD     TMR1_CH_IRQHandler                  ; TMR1 channel
                DCD     TMR2_GLOBAL_IRQHandler              ; TMR2
                DCD     TMR3_GLOBAL_IRQHandler              ; TMR3
                DCD     TMR6_GLOBAL_IRQHandler              ; TMR6
                DCD     TMR7_GLOBAL_IRQHandler              ; TMR7
                DCD     TMR14_GLOBAL_IRQHandler             ; TMR14
                DCD     TMR15_GLOBAL_IRQHandler             ; TMR15
                DCD     TMR16_GLOBAL_IRQHandler             ; TMR16
                DCD     TMR17_GLOBAL_IRQHandler             ; TMR17
                DCD     I2C1_EVT_IRQHandler                 ; I2C1 Event
                DCD     I2C2_EVT_IRQHandler                 ; I2C2 Event
                DCD     SPI1_IRQHandler                     ; SPI1
                DCD     SPI2_IRQHandler                     ; SPI2
                DCD     USART1_IRQHandler                   ; USART1
                DCD     USART2_IRQHandler                   ; USART2
                DCD     USART4_3_IRQHandler                 ; USART3 & USART4
                DCD     CAN1_IRQHandler                     ; CAN1
                DCD     OTGFS1_IRQHandler                   ; OTGFS1
                DCD     I2C1_ERR_IRQHandler                 ; I2C1 Error
                DCD     SPI3_IRQHandler                     ; SPI3
                DCD     I2C2_ERR_IRQHandler                 ; I2C2 Error
                DCD     TMR13_GLOBAL_IRQHandler             ; TMR13
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
                EXPORT  ERTC_IRQHandler                     [WEAK]
                EXPORT  FLASH_IRQHandler                    [WEAK]
                EXPORT  CRM_IRQHandler                      [WEAK]
                EXPORT  EXINT1_0_IRQHandler                 [WEAK]
                EXPORT  EXINT3_2_IRQHandler                 [WEAK]
                EXPORT  EXINT15_4_IRQHandler                [WEAK]
                EXPORT  ACC_IRQHandler                      [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel3_2_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel7_4_IRQHandler          [WEAK]
                EXPORT  ADC1_IRQHandler                     [WEAK]
                EXPORT  TMR1_BRK_OVF_TRG_HALL_IRQHandler    [WEAK]
                EXPORT  TMR1_CH_IRQHandler                  [WEAK]
                EXPORT  TMR2_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR3_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR6_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR7_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR14_GLOBAL_IRQHandler             [WEAK]
                EXPORT  TMR15_GLOBAL_IRQHandler             [WEAK]
                EXPORT  TMR16_GLOBAL_IRQHandler             [WEAK]
                EXPORT  TMR17_GLOBAL_IRQHandler             [WEAK]
                EXPORT  I2C1_EVT_IRQHandler                 [WEAK]
                EXPORT  I2C2_EVT_IRQHandler                 [WEAK]
                EXPORT  SPI1_IRQHandler                     [WEAK]
                EXPORT  SPI2_IRQHandler                     [WEAK]
                EXPORT  USART1_IRQHandler                   [WEAK]
                EXPORT  USART2_IRQHandler                   [WEAK]
                EXPORT  USART4_3_IRQHandler                 [WEAK]
                EXPORT  CAN1_IRQHandler                     [WEAK]
                EXPORT  OTGFS1_IRQHandler                   [WEAK]
                EXPORT  I2C1_ERR_IRQHandler                 [WEAK]
                EXPORT  SPI3_IRQHandler                     [WEAK]
                EXPORT  I2C2_ERR_IRQHandler                 [WEAK]
                EXPORT  TMR13_GLOBAL_IRQHandler             [WEAK]
WWDT_IRQHandler
PVM_IRQHandler
ERTC_IRQHandler
FLASH_IRQHandler
CRM_IRQHandler
EXINT1_0_IRQHandler
EXINT3_2_IRQHandler
EXINT15_4_IRQHandler
ACC_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel3_2_IRQHandler
DMA1_Channel7_4_IRQHandler
ADC1_IRQHandler
TMR1_BRK_OVF_TRG_HALL_IRQHandler
TMR1_CH_IRQHandler
TMR2_GLOBAL_IRQHandler
TMR3_GLOBAL_IRQHandler
TMR6_GLOBAL_IRQHandler
TMR7_GLOBAL_IRQHandler
TMR14_GLOBAL_IRQHandler
TMR15_GLOBAL_IRQHandler
TMR16_GLOBAL_IRQHandler
TMR17_GLOBAL_IRQHandler
I2C1_EVT_IRQHandler
I2C2_EVT_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART4_3_IRQHandler
CAN1_IRQHandler
OTGFS1_IRQHandler
I2C1_ERR_IRQHandler
SPI3_IRQHandler
I2C2_ERR_IRQHandler
TMR13_GLOBAL_IRQHandler
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
