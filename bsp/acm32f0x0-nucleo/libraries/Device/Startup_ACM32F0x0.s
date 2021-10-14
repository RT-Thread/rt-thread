;* File Name          : Startup_ACM32F0x0.s
;* Version            : V1.0.0
;* Date               : 2020
;* Description        : ACM32F0x0 Devices vector table for MDK-ARM toolchain. 
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the SC000 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************

Stack_Size      EQU     0x00000800
Heap_Size       EQU     0x00000000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT __Vectors

__Vectors
                DCD     __initial_sp                    ; Top of Stack
                DCD     Reset_Handler                   ; Reset Handler
                DCD     NMI_Handler                     ; NMI Handler
                DCD     HardFault_Handler               ; Hard Fault Handler
                DCD     MemManage_Handler               ; MPU Fault Handler
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     SVC_Handler                     ; SVCall Handler 
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     PendSV_Handler                  ; PendSV Handler
                DCD     SysTick_Handler                 ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler                  ; 0:  WDT_IRQHandler    
                DCD     RTC_IRQHandler                  ; 1:  RTC_IRQHandler 
                DCD     EFC_IRQHandler                  ; 2:  EFC_IRQHandler 
                DCD     GPIOAB_IRQHandler               ; 3:  GPIOAB_IRQHandler 
                DCD     GPIOCD_IRQHandler               ; 4:  GPIOCD_IRQHandler
                DCD     EXTI_IRQHandler                 ; 5:  EXTI_IRQHandler 
                DCD     SRAM_PARITY_IRQHandler          ; 6:  SRAM_PARITY_IRQHandler
                DCD     CLKRDY_IRQHandler               ; 7:  CLKRDY_IRQHandler
                DCD     LCD_IRQHandler                  ; 8:  LCD_IRQHandler
                DCD     DMA_IRQHandler                  ; 9:  DMA_IRQHandler
                DCD     UART3_IRQHandler                ; 10: UART3_IRQHandler
                DCD     TKEY_IRQHandler                 ; 11: TKEY_IRQHandler
                DCD     ADC_IRQHandler                  ; 12: ADC_IRQHandler
                DCD     TIM1_BRK_UP_TRG_COM_IRQHandler  ; 13: TIM1_BRK_UP_TRG_COM_IRQHandler
                DCD     TIM1_CC_IRQHandler              ; 14: TIM1_CC_IRQHandler
                DCD     RSV_IRQHandler                  ; 15: Reserved
                DCD     TIM3_IRQHandler                 ; 16: TIM3_IRQHandler 
                DCD     TIM6_IRQHandler                 ; 17: TIM6_IRQHandler
                DCD     RSV_IRQHandler                  ; 18: Reserved
                DCD     TIM14_IRQHandler                ; 19: TIM14_IRQHandler
                DCD     TIM15_IRQHandler                ; 20: TIM15_IRQHandler 
                DCD     TIM16_IRQHandler                ; 21: TIM16_IRQHandler   
                DCD     TIM17_IRQHandler                ; 22: TIM17_IRQHandler   
                DCD     I2C1_IRQHandler                 ; 23: I2C1_IRQHandler    
                DCD     I2C2_IRQHandler                 ; 24: I2C2_IRQHandler     
                DCD     SPI1_IRQHandler                 ; 25: SPI1_IRQHandler    
                DCD     SPI2_IRQHandler                 ; 26: SPI2_IRQHandler    
                DCD     UART1_IRQHandler                ; 27: UART1_IRQHandler   
                DCD     UART2_IRQHandler                ; 28: UART2_IRQHandler      
                DCD     LPUART_IRQHandler               ; 29: LPUART_IRQHandler
                DCD     CAN1_IRQHandler                 ; 30: CAN1_IRQHandler
                DCD     AES_IRQHandler                  ; 31: AES_IRQHandler 

                AREA    |.text|, CODE, READONLY

Reset_Handler     PROC
                  EXPORT  Reset_Handler             [WEAK]
                  IMPORT  __main
                  LDR     R0, =__main
                  BX      R0
                  ENDP


NMI_Handler       PROC
                  EXPORT  NMI_Handler               [WEAK]
                  B       .
                  ENDP
HardFault_Handler PROC
                  EXPORT  HardFault_Handler         [WEAK]
                  B       .
                  ENDP
MemManage_Handler PROC
                  EXPORT  MemManage_Handler         [WEAK]
                  B       .
                  ENDP
SVC_Handler       PROC
                  EXPORT  SVC_Handler               [WEAK]
                  B       .
                  ENDP
PendSV_Handler    PROC
                  EXPORT  PendSV_Handler            [WEAK]
                  B       .
                  ENDP
SysTick_Handler   PROC
                  EXPORT  SysTick_Handler           [WEAK]
                  B       .
                  ENDP

Default_Handler PROC
                EXPORT   WDT_IRQHandler                 [WEAK]
                EXPORT   RTC_IRQHandler                 [WEAK]
                EXPORT   EFC_IRQHandler                 [WEAK]
                EXPORT   GPIOAB_IRQHandler              [WEAK]
                EXPORT   GPIOCD_IRQHandler              [WEAK]
                EXPORT   EXTI_IRQHandler                [WEAK]
                EXPORT   SRAM_PARITY_IRQHandler         [WEAK]
                EXPORT   CLKRDY_IRQHandler              [WEAK]
                EXPORT   LCD_IRQHandler                 [WEAK]
                EXPORT   DMA_IRQHandler                 [WEAK]
                EXPORT   UART3_IRQHandler               [WEAK]
                EXPORT   TKEY_IRQHandler                [WEAK]
                EXPORT   ADC_IRQHandler                 [WEAK]
                EXPORT   TIM1_BRK_UP_TRG_COM_IRQHandler [WEAK]
                EXPORT   TIM1_CC_IRQHandler             [WEAK]
                EXPORT   TIM3_IRQHandler                [WEAK]
                EXPORT   TIM6_IRQHandler                [WEAK]
                EXPORT   TIM14_IRQHandler               [WEAK]
                EXPORT   TIM15_IRQHandler               [WEAK]
                EXPORT   TIM16_IRQHandler               [WEAK]
                EXPORT   TIM17_IRQHandler               [WEAK]
                EXPORT   I2C1_IRQHandler                [WEAK]
                EXPORT   I2C2_IRQHandler                [WEAK]
                EXPORT   SPI1_IRQHandler                [WEAK]
                EXPORT   SPI2_IRQHandler                [WEAK]
                EXPORT   UART1_IRQHandler               [WEAK]
                EXPORT   UART2_IRQHandler               [WEAK]
                EXPORT   LPUART_IRQHandler              [WEAK]
                EXPORT   CAN1_IRQHandler                [WEAK]
                EXPORT   AES_IRQHandler                 [WEAK]
                EXPORT   RSV_IRQHandler                 [WEAK]
WDT_IRQHandler
RTC_IRQHandler
EFC_IRQHandler
GPIOAB_IRQHandler
GPIOCD_IRQHandler
EXTI_IRQHandler
SRAM_PARITY_IRQHandler
CLKRDY_IRQHandler
LCD_IRQHandler
DMA_IRQHandler
UART3_IRQHandler
TKEY_IRQHandler
ADC_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM3_IRQHandler
TIM6_IRQHandler
TIM14_IRQHandler
TIM15_IRQHandler
TIM16_IRQHandler
TIM17_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
LPUART_IRQHandler
CAN1_IRQHandler
AES_IRQHandler
RSV_IRQHandler
                B       .
                ENDP

                ALIGN

; User Initial Stack & Heap
                 
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
