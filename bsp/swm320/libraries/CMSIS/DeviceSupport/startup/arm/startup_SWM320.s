;******************************************************************************************************************************************
; 文件名称:	startup_SWM320.s
; 功能说明:	SWM2400单片机的启动文件
; 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
; 注意事项:
; 版本日期: V1.1.0		2017年10月25日
; 升级记录:
;
;
;******************************************************************************************************************************************
; @attention
;
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
; REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
; FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
; OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
; -ECTION WITH THEIR PRODUCTS.
;
; COPYRIGHT 2012 Synwit Technology
;******************************************************************************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

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
                DCD     GPIOA0_Handler
                DCD     GPIOA1_Handler
                DCD     GPIOA2_Handler
                DCD     GPIOA3_Handler
                DCD     GPIOA4_Handler
                DCD     GPIOA5_Handler
                DCD     GPIOA6_Handler
                DCD     GPIOA7_Handler
				DCD     GPIOB0_Handler
                DCD     GPIOB1_Handler
                DCD     GPIOB2_Handler
                DCD     GPIOB3_Handler
                DCD     GPIOB4_Handler
                DCD     GPIOB5_Handler
                DCD     GPIOB6_Handler
                DCD     GPIOB7_Handler
                DCD     GPIOC0_Handler
                DCD     GPIOC1_Handler
                DCD     GPIOC2_Handler
                DCD     GPIOC3_Handler
                DCD     GPIOC4_Handler
                DCD     GPIOC5_Handler
                DCD     GPIOC6_Handler
                DCD     GPIOC7_Handler
                DCD     GPIOM0_Handler
                DCD     GPIOM1_Handler
                DCD     GPIOM2_Handler
                DCD     GPIOM3_Handler
                DCD     GPIOM4_Handler
                DCD     GPIOM5_Handler
                DCD     GPIOM6_Handler
                DCD     GPIOM7_Handler
				DCD     DMA_Handler
                DCD     LCD_Handler
                DCD     NORFLC_Handler
				DCD		CAN_Handler
                DCD     PULSE_Handler
                DCD     WDT_Handler
                DCD     PWM_Handler
                DCD     UART0_Handler
				DCD     UART1_Handler
				DCD     UART2_Handler
				DCD     UART3_Handler
				DCD     0
				DCD     I2C0_Handler
                DCD     I2C1_Handler
                DCD     SPI0_Handler
                DCD     ADC0_Handler
                DCD     RTC_Handler
                DCD     BOD_Handler
                DCD     SDIO_Handler
                DCD     GPIOA_Handler
                DCD     GPIOB_Handler
                DCD     GPIOC_Handler
                DCD     GPIOM_Handler
                DCD     GPION_Handler
                DCD     GPIOP_Handler
                DCD     ADC1_Handler
                DCD     FPU_Handler
				DCD     SPI1_Handler
				DCD     TIMR0_Handler
				DCD     TIMR1_Handler
				DCD     TIMR2_Handler
				DCD     TIMR3_Handler
				DCD     TIMR4_Handler
				DCD     TIMR5_Handler
                         
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors



                AREA    |.text|, CODE, READONLY


Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]
        IMPORT  __main
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP

HardFault_Handler PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP

MemManage_Handler PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP

BusFault_Handler PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP

UsageFault_Handler PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP

SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP

DebugMon_Handler PROC
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

GPIOA0_Handler PROC
                EXPORT  GPIOA0_Handler            [WEAK]
                B       .
                ENDP

GPIOA1_Handler PROC
                EXPORT  GPIOA1_Handler            [WEAK]
                B       .
                ENDP

GPIOA2_Handler PROC
                EXPORT  GPIOA2_Handler            [WEAK]
                B       .
                ENDP

GPIOA3_Handler PROC
                EXPORT  GPIOA3_Handler            [WEAK]
                B       .
                ENDP

GPIOA4_Handler PROC
                EXPORT  GPIOA4_Handler            [WEAK]
                B       .
                ENDP

GPIOA5_Handler PROC
                EXPORT  GPIOA5_Handler            [WEAK]
                B       .
                ENDP

GPIOA6_Handler PROC
                EXPORT  GPIOA6_Handler            [WEAK]
                B       .
                ENDP

GPIOA7_Handler PROC
                EXPORT  GPIOA7_Handler            [WEAK]
                B       .
                ENDP

GPIOB0_Handler PROC
                EXPORT  GPIOB0_Handler            [WEAK]
                B       .
                ENDP

GPIOB1_Handler PROC
                EXPORT  GPIOB1_Handler            [WEAK]
                B       .
                ENDP

GPIOB2_Handler PROC
                EXPORT  GPIOB2_Handler            [WEAK]
                B       .
                ENDP

GPIOB3_Handler PROC
                EXPORT  GPIOB3_Handler            [WEAK]
                B       .
                ENDP

GPIOB4_Handler PROC
                EXPORT  GPIOB4_Handler            [WEAK]
                B       .
                ENDP

GPIOB5_Handler PROC
                EXPORT  GPIOB5_Handler            [WEAK]
                B       .
                ENDP

GPIOB6_Handler PROC
                EXPORT  GPIOB6_Handler            [WEAK]
                B       .
                ENDP

GPIOB7_Handler PROC
                EXPORT  GPIOB7_Handler            [WEAK]
                B       .
                ENDP

GPIOC0_Handler PROC
                EXPORT  GPIOC0_Handler            [WEAK]
                B       .
                ENDP

GPIOC1_Handler PROC
                EXPORT  GPIOC1_Handler            [WEAK]
                B       .
                ENDP

GPIOC2_Handler PROC
                EXPORT  GPIOC2_Handler            [WEAK]
                B       .
                ENDP

GPIOC3_Handler PROC
                EXPORT  GPIOC3_Handler            [WEAK]
                B       .
                ENDP

GPIOC4_Handler PROC
                EXPORT  GPIOC4_Handler            [WEAK]
                B       .
                ENDP

GPIOC5_Handler PROC
                EXPORT  GPIOC5_Handler            [WEAK]
                B       .
                ENDP

GPIOC6_Handler PROC
                EXPORT  GPIOC6_Handler            [WEAK]
                B       .
                ENDP

GPIOC7_Handler PROC
                EXPORT  GPIOC7_Handler            [WEAK]
                B       .
                ENDP

GPIOM0_Handler PROC
                EXPORT  GPIOM0_Handler            [WEAK]
                B       .
                ENDP

GPIOM1_Handler PROC
                EXPORT  GPIOM1_Handler            [WEAK]
                B       .
                ENDP

GPIOM2_Handler PROC
                EXPORT  GPIOM2_Handler            [WEAK]
                B       .
                ENDP

GPIOM3_Handler PROC
                EXPORT  GPIOM3_Handler            [WEAK]
                B       .
                ENDP

GPIOM4_Handler PROC
                EXPORT  GPIOM4_Handler            [WEAK]
                B       .
                ENDP

GPIOM5_Handler PROC
                EXPORT  GPIOM5_Handler            [WEAK]
                B       .
                ENDP

GPIOM6_Handler PROC
                EXPORT  GPIOM6_Handler            [WEAK]
                B       .
                ENDP

GPIOM7_Handler PROC
                EXPORT  GPIOM7_Handler            [WEAK]
                B       .
                ENDP

DMA_Handler PROC
                EXPORT  DMA_Handler            [WEAK]
                B       .
                ENDP

LCD_Handler PROC
                EXPORT  LCD_Handler            [WEAK]
                B       .
                ENDP

NORFLC_Handler PROC
                EXPORT  NORFLC_Handler            [WEAK]
                B       .
                ENDP

CAN_Handler PROC
                EXPORT  CAN_Handler            [WEAK]
                B       .
                ENDP

PULSE_Handler PROC
                EXPORT  PULSE_Handler          [WEAK]
                B       .
                ENDP

WDT_Handler PROC
                EXPORT  WDT_Handler            [WEAK]
                B       .
                ENDP

PWM_Handler PROC
                EXPORT  PWM_Handler            [WEAK]
                B       .
                ENDP

UART0_Handler PROC
                EXPORT  UART0_Handler            [WEAK]
                B       .
                ENDP

UART1_Handler PROC
                EXPORT  UART1_Handler            [WEAK]
                B       .
                ENDP

UART2_Handler PROC
                EXPORT  UART2_Handler            [WEAK]
                B       .
                ENDP

UART3_Handler PROC
                EXPORT  UART3_Handler            [WEAK]
                B       .
                ENDP

I2C0_Handler PROC
                EXPORT  I2C0_Handler            [WEAK]
                B       .
                ENDP

I2C1_Handler PROC
                EXPORT  I2C1_Handler            [WEAK]
                B       .
                ENDP

SPI0_Handler PROC
                EXPORT  SPI0_Handler            [WEAK]
                B       .
                ENDP

ADC0_Handler PROC
                EXPORT  ADC0_Handler            [WEAK]
                B       .
                ENDP

RTC_Handler PROC
                EXPORT  RTC_Handler            [WEAK]
                B       .
                ENDP

BOD_Handler PROC
                EXPORT  BOD_Handler            [WEAK]
                B       .
                ENDP

SDIO_Handler PROC
                EXPORT  SDIO_Handler            [WEAK]
                B       .
                ENDP

GPIOA_Handler PROC
                EXPORT  GPIOA_Handler            [WEAK]
                B       .
                ENDP

GPIOB_Handler PROC
                EXPORT  GPIOB_Handler            [WEAK]
                B       .
                ENDP

GPIOC_Handler PROC
                EXPORT  GPIOC_Handler            [WEAK]
                B       .
                ENDP

GPIOM_Handler PROC
                EXPORT  GPIOM_Handler            [WEAK]
                B       .
                ENDP

GPION_Handler PROC
                EXPORT  GPION_Handler            [WEAK]
                B       .
                ENDP

GPIOP_Handler PROC
                EXPORT  GPIOP_Handler            [WEAK]
                B       .
                ENDP

ADC1_Handler PROC
                EXPORT  ADC1_Handler            [WEAK]
                B       .
                ENDP

FPU_Handler PROC
                EXPORT  FPU_Handler            [WEAK]
                B       .
                ENDP

SPI1_Handler PROC
                EXPORT  SPI1_Handler            [WEAK]
                B       .
                ENDP

TIMR0_Handler PROC
                EXPORT  TIMR0_Handler           [WEAK]
                B       .
                ENDP

TIMR1_Handler PROC
                EXPORT  TIMR1_Handler           [WEAK]
                B       .
                ENDP
				
TIMR2_Handler PROC
                EXPORT  TIMR2_Handler           [WEAK]
                B       .
                ENDP

TIMR3_Handler PROC
                EXPORT  TIMR3_Handler           [WEAK]
                B       .
                ENDP
				
TIMR4_Handler PROC
                EXPORT  TIMR4_Handler           [WEAK]
                B       .
                ENDP

TIMR5_Handler PROC
                EXPORT  TIMR5_Handler           [WEAK]
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
