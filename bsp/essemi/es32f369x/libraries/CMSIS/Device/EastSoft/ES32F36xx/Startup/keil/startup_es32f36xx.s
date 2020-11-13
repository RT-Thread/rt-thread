;*******************************************************************************
; file       : startup_es32f36xx.s
; description: es32f36xx Device Startup File
; author     : AE Team
; data       : 23 Jan 2019
; Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
;*******************************************************************************

;Stack Configuration------------------------------------------------------------
Stack_Size      EQU     0x00000800
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp
;-------------------------------------------------------------------------------

;Heap Configuration-------------------------------------------------------------
Heap_Size       EQU     0x00000000
                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit
;-------------------------------------------------------------------------------
                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset-------------------------------------
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp                    ;0,  load top of stack
                DCD     RESET_Handler                   ;1,  reset handler
                DCD     NMI_Handler                     ;2,  nmi handler
                DCD     HardFault_Handler               ;3,  hard fault handler
                DCD     MemManage_Handler               ;4,  MPU Fault Handler
                DCD     BusFault_Handler                ;5,  Bus Fault Handler
                DCD     UsageFault_Handler              ;6,  Usage Fault Handler
                DCD     0                               ;7,  Reserved
                DCD     0                               ;8,  Reserved
                DCD     0                               ;9,  Reserved
                DCD     0                               ;10, Reserved
                DCD     SVC_Handler                     ;11, svcall handler
                DCD     DebugMon_Handler                ;12, Debug Monitor Handler
                DCD     0                               ;13, Reserved
                DCD     PendSV_Handler                  ;14, pendsv handler
                DCD     SysTick_Handler                 ;15, systick handler
                DCD     WWDG_Handler                    ;16, irq0    WWDG handler
                DCD     IWDG_Handler                    ;17, irq1    IWDG handler
                DCD     LVD_Handler                     ;18, irq2    LVD handler
                DCD     RTC_Handler                     ;19, irq3    RTC handler
                DCD     0                               ;20, irq4    Reserved
                DCD     0                               ;21, irq5    Reserved
                DCD     CMU_Handler                     ;22, irq6    CMU handler
                DCD     ADC0_Handler                    ;23, irq7    ADC0 handler
                DCD     CAN0_TX_Handler                 ;24, irq8    CAN0_TX handler
                DCD     CAN0_RX0_Handler                ;25, irq9    CAN0_RX0 handler
                DCD     CAN0_RX1_Handler                ;26, irq10   CAN0_RX1 handler
                DCD     CAN0_EXCEPTION_Handler          ;27, irq11   CAN0_EXCEPTION handler
                DCD     AD16C4T0_BRK_Handler            ;28, irq12   AD16C4T0_BRK handler
                DCD     AD16C4T0_UP_Handler             ;29, irq13   AD16C4T0_UP handler
                DCD     AD16C4T0_TRIG_COM_Handler       ;30, irq14   AD16C4T0_TRIG_COM handler
                DCD     AD16C4T0_CC_Handler             ;31, irq15   AD16C4T0_CC handler
                DCD     AD16C4T1_BRK_Handler            ;32, irq16   AD16C4T1_BRK handler
                DCD     AD16C4T1_UP_Handler             ;33, irq17   AD16C4T1_UP handler
                DCD     AD16C4T1_TRIG_COM_Handler       ;34, irq18   AD16C4T1_TRIG_COM handler
                DCD     AD16C4T1_CC_Handler             ;35, irq19   AD16C4T1_CC handler
                DCD     GP32C4T0_Handler                ;36, irq20   GP32C4T0 handler
                DCD     GP32C4T1_Handler                ;37, irq21   GP32C4T1 handler
                DCD     BS16T0_Handler                  ;38, irq22   BS16T0 handler
                DCD     BS16T1_Handler                  ;39, irq23   BS16T1 handler
                DCD     GP16C4T0_Handler                ;40, irq24   GP16C4T0 handler
                DCD     GP16C4T1_Handler                ;41, irq25   GP16C4T1 handler
                DCD     0                               ;42, irq26   Reserved
                DCD     DAC0_CH0_Handler                ;43, irq27   DAC0_CH0 handler
                DCD     I2C0_EV_Handler                 ;44, irq28   I2C0_EV handler
                DCD     I2C0_ERR_Handler                ;45, irq29   I2C0_ERR handler
                DCD     I2C1_EV_Handler                 ;46, irq30   I2C1_EV handler
                DCD     I2C1_ERR_Handler                ;47, irq31   I2C1_ERR handler
                DCD     SPI0_I2S0_Handler               ;48, irq32   SPI0_I2S0 handler
                DCD     SPI1_I2S1_Handler               ;49, irq33   SPI1_I2S1 handler
                DCD     UART0_Handler                   ;50, irq34   UART0 handler
                DCD     UART1_Handler                   ;51, irq35   UART1 handler
                DCD     UART2_Handler                   ;52, irq36   UART2 handler
                DCD     UART3_Handler                   ;53, irq37   UART3 handler
                DCD     UART4_Handler                   ;54, irq38   UART4 handler
                DCD     UART5_Handler                   ;55, irq39   UART5 handler
                DCD     0                               ;56, irq40   Reserved
                DCD     0                               ;57, irq41   Reserved
                DCD     CRYPT_Handler                   ;58, irq42   CRYPT handler
                DCD     ACMP0_Handler                   ;59, irq43   ACMP0 handler
                DCD     ACMP1_Handler                   ;60, irq44   ACMP1 handler
                DCD     SPI2_I2S2_Handler               ;61, irq45   SPI2_I2S2 handler
                DCD     0                               ;62, irq46   Reserved
                DCD     EBI_Handler                     ;63, irq47   EBI handler
                DCD     TRNG_Handler                    ;64, irq48   TRNG handler
                DCD     TSENSE_Handler                  ;65, irq49   TSENSE handler
                DCD     EXTI0_Handler                   ;66, irq50   EXTI0 handler
                DCD     EXTI1_Handler                   ;67, irq51   EXTI1 handler
                DCD     EXTI2_Handler                   ;68, irq52   EXTI2 handler
                DCD     EXTI3_Handler                   ;69, irq53   EXTI3 handler
                DCD     EXTI4_Handler                   ;70, irq54   EXTI4 handler
                DCD     EXTI5_Handler                   ;71, irq55   EXTI5 handler
                DCD     EXTI6_Handler                   ;72, irq56   EXTI6 handler
                DCD     EXTI7_Handler                   ;73, irq57   EXTI7 handler
                DCD     EXTI8_Handler                   ;74, irq58   EXTI8 handler
                DCD     EXTI9_Handler                   ;75, irq59   EXTI9 handler
                DCD     EXTI10_Handler                  ;76, irq60   EXTI10 handler
                DCD     EXTI11_Handler                  ;77, irq61   EXTI11 handler
                DCD     EXTI12_Handler                  ;78, irq62   EXTI12 handler
                DCD     EXTI13_Handler                  ;79, irq63   EXTI13 handler
                DCD     EXTI14_Handler                  ;80, irq64   EXTI14 handler
                DCD     EXTI15_Handler                  ;81, irq65   EXTI15 handler
                DCD     DMA_Handler                     ;82, irq66   DMA handler
                DCD     ADC1_Handler                    ;83, irq67   ADC1 handler
                DCD     DAC0_CH1_Handler                ;84, irq68   DAC0_CH1 handler
                DCD     QSPI_Handler                    ;85, irq69   QSPI handler
                DCD     USB_INT_Handler                 ;86, irq70   USB_INT handler
                DCD     USB_DMA_Handler                 ;87, irq71   USB_DMA handler
                DCD     ACMP2_Handler                   ;88, irq72   ACMP2 handler

;-------------------------------------------------------------------------------
                AREA    INT, CODE, READONLY             ;code begin

;Reset Handler----------------------------------------------
RESET_Handler   PROC
	EXPORT  RESET_Handler                  [WEAK]
	IMPORT  __main
	LDR     R0, =__main
	BX      R0
	NOP
	ALIGN
	ENDP

;system int-------------------------------------------------
NMI_Handler     PROC                           ;int 2
	EXPORT  NMI_Handler                    [WEAK]
	B       .
	ENDP

HardFault_Handler \
	PROC                                   ;int3
	EXPORT  HardFault_Handler              [WEAK]
	B       .
	ENDP

MemManage_Handler \
	PROC                                   ;int4
	EXPORT  MemManage_Handler              [WEAK]
	B       .
	ENDP

BusFault_Handler \
	PROC                                   ;int5
	EXPORT  BusFault_Handler               [WEAK]
	B       .
	ENDP

UsageFault_Handler \
	PROC                                   ;int6
	EXPORT  UsageFault_Handler             [WEAK]
	B       .
	ENDP

SVC_Handler \
	PROC                                   ;int11
	EXPORT  SVC_Handler                    [WEAK]
	B       .
	ENDP

DebugMon_Handler \
	PROC                                   ;int12
	EXPORT  DebugMon_Handler               [WEAK]
	B       .
	ENDP

PendSV_Handler  \
        PROC                                   ;int14
	EXPORT  PendSV_Handler                 [WEAK]
	B       .
	ENDP

SysTick_Handler \
	PROC                                   ;int15
	EXPORT  SysTick_Handler                [WEAK]
	B       .
	ENDP

;peripheral module int -----------------------------------------------
WWDG_Handler \
	PROC                                   ;int16
	EXPORT  WWDG_Handler                   [WEAK]
	B       .
	ENDP

IWDG_Handler \
	PROC                                   ;int17
	EXPORT  IWDG_Handler                   [WEAK]
	B       .
	ENDP

LVD_Handler \
	PROC                                   ;int18
	EXPORT  LVD_Handler                    [WEAK]
	B       .
	ENDP

RTC_Handler \
	PROC                                   ;int19
	EXPORT  RTC_Handler                    [WEAK]
	B       .
	ENDP

FLASH_Handler \
	PROC                                   ;int21
	EXPORT  FLASH_Handler                  [WEAK]
	B       .
	ENDP

CMU_Handler \
	PROC                                   ;int22
	EXPORT  CMU_Handler                    [WEAK]
	B       .
	ENDP

ADC0_Handler \
	PROC                                   ;int23
	EXPORT  ADC0_Handler                   [WEAK]
	B       .
	ENDP

CAN0_TX_Handler \
	PROC                                   ;int24
	EXPORT  CAN0_TX_Handler                [WEAK]
	B       .
	ENDP

CAN0_RX0_Handler \
	PROC                                   ;int25
	EXPORT  CAN0_RX0_Handler               [WEAK]
	B       .
	ENDP

CAN0_RX1_Handler \
	PROC                                   ;int26
	EXPORT  CAN0_RX1_Handler               [WEAK]
	B       .
	ENDP

CAN0_EXCEPTION_Handler \
	PROC                                   ;int27
	EXPORT  CAN0_EXCEPTION_Handler         [WEAK]
	B       .
	ENDP

AD16C4T0_BRK_Handler \
	PROC                                   ;int28
	EXPORT  AD16C4T0_BRK_Handler           [WEAK]
	B       .
	ENDP

AD16C4T0_UP_Handler \
	PROC                                   ;int29
	EXPORT  AD16C4T0_UP_Handler            [WEAK]
	B       .
	ENDP

AD16C4T0_TRIG_COM_Handler \
	PROC                                   ;int30
	EXPORT  AD16C4T0_TRIG_COM_Handler      [WEAK]
	B       .
	ENDP

AD16C4T0_CC_Handler \
	PROC                                   ;int31
	EXPORT  AD16C4T0_CC_Handler            [WEAK]
	B       .
	ENDP

AD16C4T1_BRK_Handler \
	PROC                                   ;int32
	EXPORT  AD16C4T1_BRK_Handler           [WEAK]
	B       .
	ENDP

AD16C4T1_UP_Handler \
	PROC                                   ;int33
	EXPORT  AD16C4T1_UP_Handler            [WEAK]
	B       .
	ENDP

AD16C4T1_TRIG_COM_Handler \
	PROC                                   ;int34
	EXPORT  AD16C4T1_TRIG_COM_Handler      [WEAK]
	B       .
	ENDP

AD16C4T1_CC_Handler \
	PROC                                   ;int35
	EXPORT  AD16C4T1_CC_Handler            [WEAK]
	B       .
	ENDP

GP32C4T0_Handler \
	PROC                                   ;int36
	EXPORT  GP32C4T0_Handler               [WEAK]
	B       .
	ENDP

GP32C4T1_Handler \
	PROC                                   ;int37
	EXPORT  GP32C4T1_Handler               [WEAK]
	B       .
	ENDP

BS16T0_Handler \
	PROC                                   ;int38
	EXPORT  BS16T0_Handler                 [WEAK]
	B       .
	ENDP

BS16T1_Handler \
	PROC                                   ;int39
	EXPORT  BS16T1_Handler                 [WEAK]
	B       .
	ENDP

GP16C4T0_Handler \
	PROC                                   ;int40
	EXPORT  GP16C4T0_Handler               [WEAK]
	B       .
	ENDP

GP16C4T1_Handler \
	PROC                                   ;int41
	EXPORT  GP16C4T1_Handler               [WEAK]
	B       .
	ENDP

DAC0_CH0_Handler \
	PROC                                   ;int43
	EXPORT  DAC0_CH0_Handler               [WEAK]
	B       .
	ENDP

I2C0_EV_Handler \
	PROC                                   ;int44
	EXPORT  I2C0_EV_Handler                [WEAK]
	B       .
	ENDP

I2C0_ERR_Handler \
	PROC                                   ;int45
	EXPORT  I2C0_ERR_Handler               [WEAK]
	B       .
	ENDP

I2C1_EV_Handler \
	PROC                                   ;int46
	EXPORT  I2C1_EV_Handler                [WEAK]
	B       .
	ENDP

I2C1_ERR_Handler \
	PROC                                   ;int47
	EXPORT  I2C1_ERR_Handler               [WEAK]
	B       .
	ENDP

SPI0_I2S0_Handler \
	PROC                                   ;int48
	EXPORT  SPI0_I2S0_Handler              [WEAK]
	B       .
	ENDP

SPI1_I2S1_Handler \
	PROC                                   ;int49
	EXPORT  SPI1_I2S1_Handler              [WEAK]
	B       .
	ENDP

UART0_Handler \
	PROC                                   ;int50
	EXPORT  UART0_Handler                  [WEAK]
	B       .
	ENDP

UART1_Handler \
	PROC                                   ;int51
	EXPORT  UART1_Handler                  [WEAK]
	B       .
	ENDP

UART2_Handler \
	PROC                                   ;int52
	EXPORT  UART2_Handler                  [WEAK]
	B       .
	ENDP

UART3_Handler \
	PROC                                   ;int53
	EXPORT  UART3_Handler                  [WEAK]
	B       .
	ENDP

UART4_Handler \
	PROC                                   ;int54
	EXPORT  UART4_Handler                 [WEAK]
	B       .
	ENDP

UART5_Handler \
	PROC                                   ;int55
	EXPORT  UART5_Handler                 [WEAK]
	B       .
	ENDP

CRYPT_Handler \
	PROC                                   ;int58
	EXPORT  CRYPT_Handler                  [WEAK]
	B       .
	ENDP

ACMP0_Handler \
	PROC                                   ;int59
	EXPORT  ACMP0_Handler                  [WEAK]
	B       .
	ENDP

ACMP1_Handler \
	PROC                                   ;int60
	EXPORT  ACMP1_Handler                  [WEAK]
	B       .
	ENDP

SPI2_I2S2_Handler \
	PROC                                   ;int61
	EXPORT  SPI2_I2S2_Handler              [WEAK]
	B       .
	ENDP

EBI_Handler \
	PROC                                   ;int63
	EXPORT  EBI_Handler                   [WEAK]
	B       .
	ENDP

TRNG_Handler \
	PROC                                   ;int64
	EXPORT  TRNG_Handler                   [WEAK]
	B       .
	ENDP

TSENSE_Handler \
	PROC                                   ;int65
	EXPORT  TSENSE_Handler                 [WEAK]
	B       .
	ENDP

EXTI0_Handler \
	PROC                                   ;int66
	EXPORT  EXTI0_Handler                  [WEAK]
	B       .
	ENDP

EXTI1_Handler \
	PROC                                   ;int67
	EXPORT  EXTI1_Handler                  [WEAK]
	B       .
	ENDP

EXTI2_Handler \
	PROC                                   ;int68
	EXPORT  EXTI2_Handler                  [WEAK]
	B       .
	ENDP

EXTI3_Handler \
	PROC                                   ;int69
	EXPORT  EXTI3_Handler                  [WEAK]
	B       .
	ENDP

EXTI4_Handler \
	PROC                                   ;int70
	EXPORT  EXTI4_Handler                  [WEAK]
	B       .
	ENDP

EXTI5_Handler \
	PROC                                   ;int71
	EXPORT  EXTI5_Handler                  [WEAK]
	B       .
	ENDP

EXTI6_Handler \
	PROC                                   ;int72
	EXPORT  EXTI6_Handler                  [WEAK]
	B       .
	ENDP

EXTI7_Handler \
	PROC                                   ;int73
	EXPORT  EXTI7_Handler                  [WEAK]
	B       .
	ENDP

EXTI8_Handler \
	PROC                                   ;int74
	EXPORT  EXTI8_Handler                  [WEAK]
	B       .
	ENDP

EXTI9_Handler \
	PROC                                   ;int75
	EXPORT  EXTI9_Handler                  [WEAK]
	B       .
	ENDP

EXTI10_Handler \
	PROC                                   ;int76
	EXPORT  EXTI10_Handler                 [WEAK]
	B       .
	ENDP

EXTI11_Handler \
	PROC                                   ;int77
	EXPORT  EXTI11_Handler                 [WEAK]
	B       .
	ENDP

EXTI12_Handler \
	PROC                                   ;int78
	EXPORT  EXTI12_Handler                 [WEAK]
	B       .
	ENDP

EXTI13_Handler \
	PROC                                   ;int79
	EXPORT  EXTI13_Handler                 [WEAK]
	B       .
	ENDP

EXTI14_Handler \
	PROC                                   ;int80
	EXPORT  EXTI14_Handler                 [WEAK]
	B       .
	ENDP

EXTI15_Handler \
	PROC                                   ;int81
	EXPORT  EXTI15_Handler                 [WEAK]
	B       .
	ENDP

DMA_Handler \
	PROC                                   ;int82
	EXPORT  DMA_Handler                    [WEAK]
	B       .
	ENDP

ADC1_Handler \
	PROC                                   ;int83
	EXPORT  ADC1_Handler                   [WEAK]
	B       .
	ENDP

DAC0_CH1_Handler \
	PROC                                   ;int84
	EXPORT  DAC0_CH1_Handler               [WEAK]
	B       .
	ENDP

QSPI_Handler \
	PROC                                   ;int85
	EXPORT  QSPI_Handler                   [WEAK]
	B       .
	ENDP

USB_INT_Handler \
	PROC                                   ;int86
	EXPORT  USB_INT_Handler                [WEAK]
	B       .
	ENDP

USB_DMA_Handler \
	PROC                                   ;int87
	EXPORT  USB_DMA_Handler                [WEAK]
	B       .
	ENDP

ACMP2_Handler \
	PROC                                   ;int88
	EXPORT  ACMP2_Handler                  [WEAK]
	B       .
	ENDP

; User Initial Stack & Heap-----------------------------------------------------
	ALIGN
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
	LDR     R3, = Stack_Mem
	BX      LR

	ALIGN

	ENDIF

	END
