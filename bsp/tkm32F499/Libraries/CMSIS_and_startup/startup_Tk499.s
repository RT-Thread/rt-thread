;******************** (C) COPYRIGHT 2016 HOLOCENE ********************
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
;//============== 版本 EK V1.0  20190801  ==============//

Stack_Size      EQU     0x00002000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

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

__Vectors       DCD     __initial_sp                  ; Top of Stack
                DCD     Reset_Handler                 ; Reset Handler
                DCD     NMI_Handler                   ; NMI Handler
                DCD     HardFault_Handler             ; Hard Fault Handler
                DCD     MemManage_Handler             ; MPU Fault Handler
                DCD     BusFault_Handler              ; Bus Fault Handler
                DCD     UsageFault_Handler            ; Usage Fault Handler
                DCD     0                             ; Reserved
                DCD     0                             ; Reserved
                DCD     0                             ; Reserved
                DCD     0                             ; Reserved
                DCD     SVC_Handler                   ; SVCall Handler
                DCD     DebugMon_Handler              ; Debug Monitor Handler
                DCD     0                             ; Reserved
                DCD     PendSV_Handler                ; PendSV Handler
                DCD     SysTick_Handler               ; SysTick Handler

                ; External Interrupts
                DCD  WWDG_IRQHandler                  ;WWDG
                DCD  0                                ;
                DCD  TAMPER_IRQHandler                ;TAMPER
                DCD  RTC_IRQHandler                   ;RTC
                DCD  0                                ;
                DCD  RCC_IRQHandler                   ;RCC
                DCD  EXTI0_IRQHandler                 ;EXTI0
                DCD  EXTI1_IRQHandler                 ;EXTI1
                DCD  EXTI2_IRQHandler                 ;EXTI2
                DCD  EXTI3_IRQHandler                 ;EXTI3
                DCD  EXTI4_IRQHandler                 ;EXTI4
                DCD  DMA1_Channel1_IRQHandler         ;DMA1 Channel 1
                DCD  DMA1_Channel2_IRQHandler         ;DMA1 Channel 2
                DCD  DMA1_Channel3_IRQHandler         ;DMA1 Channel 3
                DCD  DMA1_Channel4_IRQHandler         ;DMA1 Channel 4
                DCD  DMA1_Channel5_IRQHandler         ;DMA1 Channel 5
                DCD  DMA1_Channel6_IRQHandler         ;DMA1 Channel 6
                DCD  DMA1_Channel7_IRQHandler         ;DMA1 Channel 7
                DCD  ADC1_IRQHandler                  ;ADC1
                DCD  CAN1_IRQHandler         	      ;CAN1
                DCD   0                               ;
                DCD   0                               ;
                DCD   0                               ;
                DCD  EXTI9_5_IRQHandler               ;EXTI9_5
                DCD  TIM1_BRK_IRQHandler              ;TIM1_BRK
                DCD  TIM1_UP_IRQHandler               ;TIM1_UP
                DCD  TIM1_TRG_COM_IRQHandler          ;TIM1_TRG_COM
                DCD  TIM1_CC_IRQHandler               ;TIM1_CC
                DCD  TIM3_IRQHandler                  ;TIM3
                DCD  TIM4_IRQHandler                  ;TIM4
                DCD  TIM5_IRQHandler                  ;TIM5
                DCD  TIM6_IRQHandler                  ;TIM6
                DCD  TIM7_IRQHandler                  ;TIM7
                DCD  I2C1_IRQHandler                  ;I2C1
                DCD  I2C2_IRQHandler                  ;I2C2
                DCD  SPI1_IRQHandler                  ;SPI1
                DCD  SPI2_IRQHandler                  ;SPI2
                DCD  UART1_IRQHandler                 ;UART1
                DCD  UART2_IRQHandler                 ;UART2
                DCD  UART3_IRQHandler                 ;UART3
                DCD  EXTI15_10_IRQHandler             ;EXTI15_10
                DCD  RTCAlarm_IRQHandler              ;RTC_ALARM
                DCD  USBAwake_IRQHandler              ;USBAwake
                DCD  TIM2_BRK_IRQHandler              ;TIM2_BRK
                DCD  TIM2_UP_IRQHandler               ;TIM2_UP
                DCD  TIM2_TRG_COM_IRQHandler          ;TIM2_TRG_COM
                DCD  TIM2_CC_IRQHandler               ;TIM2_CC
                DCD  DMA1_Channel8_IRQHandler         ;DMA1
                DCD  TK80_IRQHandler                  ;TK80
                DCD  SDIO1_IRQHandler                 ;SDIO1
                DCD  SDIO2_IRQHandler                 ;SDIO2
                DCD  SPI3_IRQHandler                  ;SPI3
                DCD  UART4_IRQHandler                 ;UART4
                DCD  UART5_IRQHandler                 ;UART5
                DCD  0                                ;
                DCD  TIM8_IRQHandler                  ;TIM8
                DCD  DMA2_Channel1_IRQHandler         ;DMA2 Channel 1
                DCD  DMA2_Channel2_IRQHandler         ;DMA2 Channel 2
                DCD  DMA2_Channel3_IRQHandler         ;DMA2 Channel 3
                DCD  DMA2_Channel4_IRQHandler         ;DMA2 Channel 4
                DCD  DMA2_Channel5_IRQHandler         ;DMA2 Channel 5
                DCD  TIM9_IRQHandler                  ;TIM9
                DCD  TIM10_IRQHandler                 ;TIM10
                DCD  CAN2_IRQHandler                  ;CAN2
                DCD  0                                ;
                DCD  0                                ;
                DCD  0                                ;
                DCD  USB_IRQHandler                   ;USB
                DCD  DMA2_Channel6_IRQHandler         ;DMA2 Channel 6
                DCD  DMA2_Channel7_IRQHandler         ;DMA2 Channel 7
                DCD  DMA2_Channel8_IRQHandler         ;DMA2 Channel 8
                DCD   0                               ;
                DCD  I2C3_IRQHandler                  ;I2C3
                DCD  I2C4_IRQHandler                  ;I2C4
                DCD  0                                ;
                DCD  0                                ;
                DCD  0                                ;
                DCD  0                                ;
                DCD  0                                ;
                DCD  0                                ;
                DCD  0                          	  ;
                DCD  FPU_IRQHandler                   ;FPU
                DCD  0                                ;
                DCD  0                                ;
                DCD  SPI4_IRQHandler                  ;SPI4
                DCD  0                                ;
                DCD  TOUCHPAD_IRQHandler                ;TCHPAD
                DCD  QSPI_IRQHandler                  ;QSPI
                DCD  LTDC_IRQHandler               ;LCD-TFT
                DCD  0                                ;
                DCD  I2S1_IRQHandler                  ;I2S1
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler    PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                LDR     R0, =0xE000ED88    ; 使能浮点运算 CP10,CP11
                LDR     R1,[R0]
                ORR     R1,R1,#(0xF << 20)
                STR     R1,[R0]
                ;IMPORT  SystemInit
                ; LDR     R0, =SystemInit
                ;BLX     R0

                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                   [WEAK]
                EXPORT  TAMPER_IRQHandler                 [WEAK]
                EXPORT  RTC_IRQHandler                    [WEAK]
                EXPORT  RCC_IRQHandler                    [WEAK]
                EXPORT  EXTI0_IRQHandler                  [WEAK]
                EXPORT  EXTI1_IRQHandler                  [WEAK]
                EXPORT  EXTI2_IRQHandler                  [WEAK]
                EXPORT  EXTI3_IRQHandler                  [WEAK]
                EXPORT  EXTI4_IRQHandler                  [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler          [WEAK]
                EXPORT  ADC1_IRQHandler                   [WEAK]
                EXPORT  CAN1_IRQHandler         	        [WEAK]
                EXPORT  EXTI9_5_IRQHandler               [WEAK]
                EXPORT  TIM1_BRK_IRQHandler              [WEAK]
                EXPORT  TIM1_UP_IRQHandler               [WEAK]
                EXPORT  TIM1_TRG_COM_IRQHandler          [WEAK]
                EXPORT  TIM1_CC_IRQHandler               [WEAK]
                EXPORT  TIM3_IRQHandler                  [WEAK]
                EXPORT  TIM4_IRQHandler                  [WEAK]
                EXPORT  TIM5_IRQHandler                  [WEAK]
                EXPORT  TIM6_IRQHandler                  [WEAK]
                EXPORT  TIM7_IRQHandler                  [WEAK]
                EXPORT  I2C1_IRQHandler                  [WEAK]
                EXPORT  I2C2_IRQHandler                  [WEAK]
                EXPORT  SPI1_IRQHandler                  [WEAK]
                EXPORT  SPI2_IRQHandler                  [WEAK]
                EXPORT  UART1_IRQHandler                 [WEAK]
                EXPORT  UART2_IRQHandler                 [WEAK]
                EXPORT  UART3_IRQHandler                 [WEAK]
                EXPORT  EXTI15_10_IRQHandler             [WEAK]
                EXPORT  RTCAlarm_IRQHandler              [WEAK]
                EXPORT  USBAwake_IRQHandler              [WEAK]
                EXPORT  TIM2_BRK_IRQHandler              [WEAK]
                EXPORT  TIM2_UP_IRQHandler               [WEAK]
                EXPORT  TIM2_TRG_COM_IRQHandler          [WEAK]
                EXPORT  TIM2_CC_IRQHandler               [WEAK]
                EXPORT  DMA1_Channel8_IRQHandler         [WEAK]
                EXPORT  TK80_IRQHandler                  [WEAK]
                EXPORT  SDIO1_IRQHandler                 [WEAK]
                EXPORT  SDIO2_IRQHandler                 [WEAK]
                EXPORT  SPI3_IRQHandler                  [WEAK]
                EXPORT  UART4_IRQHandler                 [WEAK]
                EXPORT  UART5_IRQHandler                 [WEAK]
                EXPORT  TIM8_IRQHandler                   [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA2_Channel4_IRQHandler          [WEAK]
                EXPORT  DMA2_Channel5_IRQHandler          [WEAK]
                EXPORT  TIM9_IRQHandler                   [WEAK]
                EXPORT  TIM10_IRQHandler                  [WEAK]
                EXPORT  CAN2_IRQHandler                   [WEAK]
                EXPORT  USB_IRQHandler                   [WEAK]
                EXPORT  DMA2_Channel6_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel7_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel8_IRQHandler         [WEAK]
                EXPORT  I2C3_IRQHandler                   [WEAK]
                EXPORT  I2C4_IRQHandler                   [WEAK]
                EXPORT  TOUCHPAD_IRQHandler                    [WEAK]
                EXPORT  SPI4_IRQHandler                   [WEAK]
                EXPORT  QSPI_IRQHandler                  [WEAK]
                EXPORT  LTDC_IRQHandler                [WEAK]
                EXPORT  I2S1_IRQHandler                  [WEAK]

WWDG_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_IRQHandler
CAN1_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
TIM5_IRQHandler
TIM6_IRQHandler
TIM7_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
EXTI15_10_IRQHandler
RTCAlarm_IRQHandler
USBAwake_IRQHandler
TIM2_BRK_IRQHandler
TIM2_UP_IRQHandler
TIM2_TRG_COM_IRQHandler
TIM2_CC_IRQHandler
DMA1_Channel8_IRQHandler
TK80_IRQHandler
SDIO1_IRQHandler
SDIO2_IRQHandler
SPI3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
TIM8_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_IRQHandler
DMA2_Channel5_IRQHandler
TIM9_IRQHandler
TIM10_IRQHandler
CAN2_IRQHandler
USB_IRQHandler
DMA2_Channel6_IRQHandler
DMA2_Channel7_IRQHandler
DMA2_Channel8_IRQHandler
I2C3_IRQHandler
I2C4_IRQHandler
FPU_IRQHandler
SPI4_IRQHandler
QSPI_IRQHandler
TOUCHPAD_IRQHandler
LTDC_IRQHandler
I2S1_IRQHandler

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

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;******************** (C) COPYRIGHT 2016 HOLOCENE ********************
