;******************************************************************************************************************************************
; 文件名称:	startup_SWM341.s
; 功能说明:	SWM341单片机的启动文件
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

Stack_Size      EQU     0x00004000

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
                DCD     UART0_Handler
                DCD     UART1_Handler
                DCD     TIMR0_Handler
                DCD     TIMR1_Handler
                DCD     DMA_Handler
                DCD     SPI0_Handler
                DCD     PWM0_Handler
                DCD     WDT_Handler
				DCD     UART2_Handler
                DCD     PWM1_Handler
                DCD     ADC0_Handler
                DCD     BTIMR0_Handler
                DCD     HALL0_Handler
                DCD     PWM2_Handler
                DCD     PWMBRK_Handler
                DCD     I2C0_Handler
                DCD     CAN0_Handler
                DCD     SPI1_Handler
                DCD     RTC_Handler
                DCD     PWM3_Handler
                DCD     TIMR2_Handler
                DCD     UART3_Handler
                DCD     TIMR3_Handler
                DCD     ADC1_Handler                                 
                DCD     BOD_Handler
                DCD     CORDIC_Handler
                DCD     BTIMR1_Handler
                DCD     PWM4_Handler
                DCD     HALL3_Handler
                DCD     BTIMR2_Handler
                DCD     I2C1_Handler
                DCD     BTIMR3_Handler                                            
				DCD     ACMP_Handler
                DCD     XTALSTOP_Handler
                DCD     FSPI_Handler
				DCD		GPIOA_Handler
                DCD     GPIOB_Handler
                DCD     GPIOC_Handler
                DCD     GPIOD_Handler
                DCD     GPIOM_Handler
				DCD     GPION_Handler
				DCD     GPIOA0_Handler
				DCD     GPIOA1_Handler
				DCD     GPIOA5_Handler
				DCD     GPIOA6_Handler
                DCD     GPIOA10_Handler
                DCD     GPIOA11_Handler
                DCD     GPIOA12_Handler
                DCD     GPIOA13_Handler
                DCD     GPIOB0_Handler
                DCD     GPIOB1_Handler
                DCD     GPIOB2_Handler
                DCD     GPIOC0_Handler
                DCD     GPIOC1_Handler
                DCD     GPIOC2_Handler
                DCD     GPIOC3_Handler
                DCD     GPIOC4_Handler
                DCD     GPIOD3_Handler
                DCD     GPIOD4_Handler
				DCD     GPIOD5_Handler
				DCD     GPIOD6_Handler
				DCD     GPIOD7_Handler
				DCD     GPIOD8_Handler
				DCD     GPIOC9_Handler
				DCD     GPIOC10_Handler
				DCD     GPIOC11_Handler
				DCD     GPIOC12_Handler
				DCD     GPIOM0_Handler
				DCD     GPIOM1_Handler
				DCD     GPIOM2_Handler
				DCD     GPIOM3_Handler
				DCD     GPIOM4_Handler
				DCD     DIV_Handler
				DCD     LCD_Handler
				DCD		GPIOE_Handler
				DCD		JPEG_Handler
				DCD		SDIO_Handler
				DCD		USB_Handler
				DCD		CAN1_Handler
				DCD		TIMR4_Handler
				DCD     BTIMR4_Handler
                DCD     BTIMR5_Handler
                DCD     BTIMR6_Handler
                DCD     BTIMR7_Handler
                DCD     BTIMR8_Handler
                DCD     BTIMR9_Handler
                DCD     BTIMR10_Handler
                DCD     BTIMR11_Handler
				DCD		DMA2D_Handler
				DCD		QEI_Handler

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors



                AREA    |.text|, CODE, READONLY


Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]
				 IMPORT  __main
				 IMPORT FPU_Enable
				 LDR     R0, =FPU_Enable
				 BLX     R0
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

UART0_Handler PROC
                EXPORT  UART0_Handler              [WEAK]
                B       .
                ENDP

UART1_Handler PROC
                EXPORT  UART1_Handler              [WEAK]
                B       .
                ENDP

TIMR0_Handler PROC
                EXPORT  TIMR0_Handler              [WEAK]
                B       .
                ENDP

TIMR1_Handler PROC
                EXPORT  TIMR1_Handler              [WEAK]
                B       .
                ENDP

DMA_Handler PROC
                EXPORT  DMA_Handler                [WEAK]
                B       .
                ENDP

SPI0_Handler PROC
                EXPORT  SPI0_Handler               [WEAK]
                B       .
                ENDP

PWM0_Handler PROC
                EXPORT  PWM0_Handler               [WEAK]
                B       .
                ENDP

WDT_Handler PROC
                EXPORT  WDT_Handler                [WEAK]
                B       .
                ENDP

UART2_Handler PROC
                EXPORT  UART2_Handler              [WEAK]
                B       .
                ENDP

PWM1_Handler PROC
                EXPORT  PWM1_Handler               [WEAK]
                B       .
                ENDP

ADC0_Handler PROC
                EXPORT  ADC0_Handler               [WEAK]
                B       .
                ENDP

BTIMR0_Handler PROC
                EXPORT  BTIMR0_Handler             [WEAK]
                B       .
                ENDP

HALL0_Handler PROC
                EXPORT  HALL0_Handler              [WEAK]
                B       .
                ENDP

PWM2_Handler PROC
                EXPORT  PWM2_Handler               [WEAK]
                B       .
                ENDP

PWMBRK_Handler PROC
                EXPORT  PWMBRK_Handler             [WEAK]
                B       .
                ENDP

I2C0_Handler PROC
                EXPORT  I2C0_Handler               [WEAK]
                B       .
                ENDP

CAN0_Handler PROC
                EXPORT  CAN0_Handler               [WEAK]
                B       .
                ENDP

SPI1_Handler PROC
                EXPORT  SPI1_Handler               [WEAK]
                B       .
                ENDP

RTC_Handler PROC
                EXPORT  RTC_Handler                [WEAK]
                B       .
                ENDP

PWM3_Handler PROC
                EXPORT  PWM3_Handler               [WEAK]
                B       .
                ENDP

TIMR2_Handler PROC
                EXPORT  TIMR2_Handler              [WEAK]
                B       .
                ENDP

UART3_Handler PROC
                EXPORT  UART3_Handler              [WEAK]
                B       .
                ENDP

TIMR3_Handler PROC
                EXPORT  TIMR3_Handler              [WEAK]
                B       .
                ENDP

ADC1_Handler PROC
                EXPORT  ADC1_Handler               [WEAK]
                B       .
                ENDP

BOD_Handler PROC
                EXPORT  BOD_Handler                [WEAK]
                B       .
                ENDP

CORDIC_Handler PROC
                EXPORT  CORDIC_Handler             [WEAK]
                B       .
                ENDP

BTIMR1_Handler PROC
                EXPORT  BTIMR1_Handler             [WEAK]
                B       .
                ENDP

PWM4_Handler PROC
                EXPORT  PWM4_Handler               [WEAK]
                B       .
                ENDP

HALL3_Handler PROC
                EXPORT  HALL3_Handler             [WEAK]
                B       .
                ENDP

BTIMR2_Handler PROC
                EXPORT  BTIMR2_Handler             [WEAK]
                B       .
                ENDP

I2C1_Handler PROC
                EXPORT  I2C1_Handler               [WEAK]
                B       .
                ENDP

BTIMR3_Handler PROC
                EXPORT  BTIMR3_Handler             [WEAK]
                B       .
                ENDP

ACMP_Handler PROC
                EXPORT  ACMP_Handler               [WEAK]
                B       .
                ENDP

XTALSTOP_Handler PROC
                EXPORT  XTALSTOP_Handler           [WEAK]
                B       .
                ENDP

FSPI_Handler PROC
                EXPORT  FSPI_Handler               [WEAK]
                B       .
                ENDP

GPIOA_Handler PROC
                EXPORT  GPIOA_Handler              [WEAK]
                B       .
                ENDP

GPIOB_Handler PROC
                EXPORT  GPIOB_Handler              [WEAK]
                B       .
                ENDP

GPIOC_Handler PROC
                EXPORT  GPIOC_Handler              [WEAK]
                B       .
                ENDP

GPIOD_Handler PROC
                EXPORT  GPIOD_Handler              [WEAK]
                B       .
                ENDP

GPIOM_Handler PROC
                EXPORT  GPIOM_Handler              [WEAK]
                B       .
                ENDP

GPION_Handler PROC
                EXPORT  GPION_Handler              [WEAK]
                B       .
                ENDP

GPIOA0_Handler PROC
                EXPORT  GPIOA0_Handler             [WEAK]
                B       .
                ENDP

GPIOA1_Handler PROC
                EXPORT  GPIOA1_Handler             [WEAK]
                B       .
                ENDP

GPIOA5_Handler PROC
                EXPORT  GPIOA5_Handler             [WEAK]
                B       .
                ENDP

GPIOA6_Handler PROC
                EXPORT  GPIOA6_Handler             [WEAK]
                B       .
                ENDP

GPIOA10_Handler PROC
                EXPORT  GPIOA10_Handler            [WEAK]
                B       .
                ENDP

GPIOA11_Handler PROC
                EXPORT  GPIOA11_Handler            [WEAK]
                B       .
                ENDP

GPIOA12_Handler PROC
                EXPORT  GPIOA12_Handler            [WEAK]
                B       .
                ENDP

GPIOA13_Handler PROC
                EXPORT  GPIOA13_Handler            [WEAK]
                B       .
                ENDP

GPIOB0_Handler PROC
                EXPORT  GPIOB0_Handler             [WEAK]
                B       .
                ENDP

GPIOB1_Handler PROC
                EXPORT  GPIOB1_Handler             [WEAK]
                B       .
                ENDP

GPIOB2_Handler PROC
                EXPORT  GPIOB2_Handler             [WEAK]
                B       .
                ENDP

GPIOC0_Handler PROC
                EXPORT  GPIOC0_Handler             [WEAK]
                B       .
                ENDP

GPIOC1_Handler PROC
                EXPORT  GPIOC1_Handler             [WEAK]
                B       .
                ENDP

GPIOC2_Handler PROC
                EXPORT  GPIOC2_Handler             [WEAK]
                B       .
                ENDP

GPIOC3_Handler PROC
                EXPORT  GPIOC3_Handler             [WEAK]
                B       .
                ENDP

GPIOC4_Handler PROC
                EXPORT  GPIOC4_Handler             [WEAK]
                B       .
                ENDP

GPIOD3_Handler PROC
                EXPORT  GPIOD3_Handler             [WEAK]
                B       .
                ENDP

GPIOD4_Handler PROC
                EXPORT  GPIOD4_Handler             [WEAK]
                B       .
                ENDP

GPIOD5_Handler PROC
                EXPORT  GPIOD5_Handler             [WEAK]
                B       .
                ENDP

GPIOD6_Handler PROC
                EXPORT  GPIOD6_Handler             [WEAK]
                B       .
                ENDP

GPIOD7_Handler PROC
                EXPORT  GPIOD7_Handler             [WEAK]
                B       .
                ENDP

GPIOD8_Handler PROC
                EXPORT  GPIOD8_Handler             [WEAK]
                B       .
                ENDP

GPIOC9_Handler PROC
                EXPORT  GPIOC9_Handler             [WEAK]
                B       .
                ENDP

GPIOC10_Handler PROC
                EXPORT  GPIOC10_Handler            [WEAK]
                B       .
                ENDP

GPIOC11_Handler PROC
                EXPORT  GPIOC11_Handler            [WEAK]
                B       .
                ENDP

GPIOC12_Handler PROC
                EXPORT  GPIOC12_Handler            [WEAK]
                B       .
                ENDP

GPIOM0_Handler PROC
                EXPORT  GPIOM0_Handler             [WEAK]
                B       .
                ENDP

GPIOM1_Handler PROC
                EXPORT  GPIOM1_Handler             [WEAK]
                B       .
                ENDP

GPIOM2_Handler PROC
                EXPORT  GPIOM2_Handler             [WEAK]
                B       .
                ENDP

GPIOM3_Handler PROC
                EXPORT  GPIOM3_Handler             [WEAK]
                B       .
                ENDP

GPIOM4_Handler PROC
                EXPORT  GPIOM4_Handler             [WEAK]
                B       .
                ENDP

DIV_Handler PROC
                EXPORT  DIV_Handler                [WEAK]
                B       .
                ENDP

LCD_Handler PROC
                EXPORT  LCD_Handler                [WEAK]
                B       .
                ENDP

GPIOE_Handler PROC
                EXPORT  GPIOE_Handler              [WEAK]
                B       .
                ENDP
				
JPEG_Handler PROC
                EXPORT  JPEG_Handler               [WEAK]
                B       .
                ENDP

SDIO_Handler PROC
                EXPORT  SDIO_Handler               [WEAK]
                B       .
                ENDP

USB_Handler PROC
                EXPORT  USB_Handler                [WEAK]
                B       .
                ENDP

CAN1_Handler PROC
                EXPORT  CAN1_Handler               [WEAK]
                B       .
                ENDP

TIMR4_Handler PROC
                EXPORT  TIMR4_Handler              [WEAK]
                B       .
                ENDP

BTIMR4_Handler PROC
                EXPORT  BTIMR4_Handler             [WEAK]
                B       .
                ENDP

BTIMR5_Handler PROC
                EXPORT  BTIMR5_Handler             [WEAK]
                B       .
                ENDP

BTIMR6_Handler PROC
                EXPORT  BTIMR6_Handler             [WEAK]
                B       .
                ENDP

BTIMR7_Handler PROC
                EXPORT  BTIMR7_Handler             [WEAK]
                B       .
                ENDP

BTIMR8_Handler PROC
                EXPORT  BTIMR8_Handler             [WEAK]
                B       .
                ENDP

BTIMR9_Handler PROC
                EXPORT  BTIMR9_Handler             [WEAK]
                B       .
                ENDP

BTIMR10_Handler PROC
                EXPORT  BTIMR10_Handler            [WEAK]
                B       .
                ENDP

BTIMR11_Handler PROC
                EXPORT  BTIMR11_Handler            [WEAK]
                B       .
                ENDP

DMA2D_Handler PROC
                EXPORT  DMA2D_Handler              [WEAK]
                B       .
                ENDP

QEI_Handler PROC
                EXPORT  QEI_Handler                [WEAK]
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
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, =  Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END
