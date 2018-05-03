;*****************************************************************************
;* @file     start_cmem7.h
;*
;* @brief    CMEM7 startup file
;*
;*
;* @version  V1.0
;* @date     3. September 2013
;*
;* @note               
;*           
;*****************************************************************************
;* @attention
;*
;* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
;* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
;* TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT, 
;* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
;* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
;* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;*
;* <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
;*****************************************************************************

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

__Vectors       DCD     __initial_sp               ; Top of Stack
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
				DCD     ETH_IRQHandler             ; ETH
				DCD     USB_IRQHandler             ; USB
				DCD     DMAC_IRQHandler            ; DMAC
				DCD     CAN0_IRQHandler            ; CAN0
				DCD     CAN1_IRQHandler            ; CAN1
				DCD     FP0_IRQHandler             ; FP[0:15]
				DCD     FP1_IRQHandler
				DCD     FP2_IRQHandler
				DCD     FP3_IRQHandler
				DCD     FP4_IRQHandler
				DCD     FP5_IRQHandler
				DCD     FP6_IRQHandler
				DCD     FP7_IRQHandler
				DCD     FP8_IRQHandler
				DCD     FP9_IRQHandler
				DCD     FP10_IRQHandler
				DCD     FP11_IRQHandler
				DCD     FP12_IRQHandler
				DCD     FP13_IRQHandler
				DCD     FP14_IRQHandler
				DCD     FP15_IRQHandler			   ; 21
				DCD     UART0_IRQHandler           ; UART0
                DCD     UART1_IRQHandler           ; UART1
				DCD     ADC_IRQHandler             ; ADC
				DCD     GPIO_IRQHandler            ; GPIO
				DCD     SPI1_IRQHandler            ; SPI1
				DCD     I2C1_IRQHandler            ; I2C1
				DCD     SPI0_IRQHandler            ; SPI0
				DCD     I2C0_IRQHandler            ; I2C0
				DCD     RTC_1S_IRQHandler          ; RTC 1S
				DCD     RTC_1MS_IRQHandler         ; RTC 1MS
				DCD     WDG_IRQHandler             ; Watchdog
				DCD     TIMER_IRQHandler           ; Timer 0 || 1 || 2 || 3
                DCD     DDRC_SW_PROC_IRQHandler    ; DDRC sw proc       				
				DCD     ETH_PMT_IRQHandler         ; ETH pmt
				DCD     PAD_IRQHandler             ; PAD
				DCD     DDRC_LANE_SYNC_IRQHandler  ; DDRC lane sync
				DCD     UART2_IRQHandler           ; UART2

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]
        IMPORT  SystemInit
        IMPORT  __main
                 LDR     R0, =SystemInit
                 BLX     R0
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
				EXPORT  ETH_IRQHandler             [WEAK]
                EXPORT  USB_IRQHandler             [WEAK]
				EXPORT  DMAC_IRQHandler            [WEAK]
				EXPORT  CAN0_IRQHandler            [WEAK]
				EXPORT  CAN1_IRQHandler            [WEAK]
				EXPORT  FP0_IRQHandler             [WEAK]
				EXPORT  FP1_IRQHandler             [WEAK]
				EXPORT  FP2_IRQHandler             [WEAK]
				EXPORT  FP3_IRQHandler             [WEAK]
				EXPORT  FP4_IRQHandler             [WEAK]
				EXPORT  FP5_IRQHandler             [WEAK]
				EXPORT  FP6_IRQHandler             [WEAK]
				EXPORT  FP7_IRQHandler             [WEAK]
				EXPORT  FP8_IRQHandler             [WEAK]
				EXPORT  FP9_IRQHandler             [WEAK]
				EXPORT  FP10_IRQHandler            [WEAK]
				EXPORT  FP11_IRQHandler            [WEAK]
				EXPORT  FP12_IRQHandler            [WEAK]
				EXPORT  FP13_IRQHandler            [WEAK]
				EXPORT  FP14_IRQHandler            [WEAK]
				EXPORT  FP15_IRQHandler            [WEAK]
				EXPORT  UART0_IRQHandler           [WEAK]
                EXPORT  UART1_IRQHandler           [WEAK]
                EXPORT  ADC_IRQHandler             [WEAK]
				EXPORT  GPIO_IRQHandler            [WEAK]
                EXPORT  SPI1_IRQHandler            [WEAK]
				EXPORT  I2C1_IRQHandler            [WEAK]
                EXPORT  SPI0_IRQHandler            [WEAK]
                EXPORT  I2C0_IRQHandler            [WEAK]
				EXPORT  RTC_1S_IRQHandler          [WEAK]
				EXPORT  RTC_1MS_IRQHandler         [WEAK]
                EXPORT  WDG_IRQHandler             [WEAK]				
                EXPORT  TIMER_IRQHandler           [WEAK] 
                EXPORT  DDRC_SW_PROC_IRQHandler    [WEAK]           				
				EXPORT  ETH_PMT_IRQHandler         [WEAK]           				
				EXPORT  PAD_IRQHandler             [WEAK]           				
				EXPORT  DDRC_LANE_SYNC_IRQHandler  [WEAK]           				
				EXPORT  UART2_IRQHandler           [WEAK]           				         				
ETH_IRQHandler
USB_IRQHandler
DMAC_IRQHandler
CAN0_IRQHandler
CAN1_IRQHandler
FP0_IRQHandler
FP1_IRQHandler
FP2_IRQHandler
FP3_IRQHandler
FP4_IRQHandler
FP5_IRQHandler
FP6_IRQHandler
FP7_IRQHandler
FP8_IRQHandler
FP9_IRQHandler
FP10_IRQHandler
FP11_IRQHandler
FP12_IRQHandler
FP13_IRQHandler
FP14_IRQHandler
FP15_IRQHandler
UART0_IRQHandler
UART1_IRQHandler          
ADC_IRQHandler 
GPIO_IRQHandler
SPI1_IRQHandler          
I2C1_IRQHandler         
SPI0_IRQHandler          
I2C0_IRQHandler  
RTC_1S_IRQHandler
RTC_1MS_IRQHandler
WDG_IRQHandler            
TIMER_IRQHandler 
DDRC_SW_PROC_IRQHandler    				
ETH_PMT_IRQHandler               				
PAD_IRQHandler                  				
DDRC_LANE_SYNC_IRQHandler     				
UART2_IRQHandler          
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

;******************* (C) COPYRIGHT 2011 Capital Micro *****END OF FILE*****
