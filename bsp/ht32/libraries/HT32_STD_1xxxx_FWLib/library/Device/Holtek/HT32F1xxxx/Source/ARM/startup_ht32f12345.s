;/*---------------------------------------------------------------------------------------------------------*/
;/* Holtek Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f1xxxx_01.s
;  Version          : $Rev:: 2524         $
;  Date             : $Date:: 2022-02-17 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

;  Supported Device
;  ========================================
;   HT32F1653, HT32F1654
;   HT32F1655, HT32F1656
;   HT32F12365, HT32F12366
;   HT32F12345

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */

;// <o>  HT32 Device
;// <i> Select HT32 Device for the assembly setting. 
;// <i> Notice that the project's Asm Define has the higher priority.
;//      <0=> By Project Asm Define
;//      <1=> HT32F1653/1654/1655/1656
;//      <2=> HT32F12365/12366
;//      <3=> HT32F12345
USE_HT32_CHIP_SET   EQU     3 ; Notice that the project's Asm Define has the higher priority.

_HT32FWID           EQU     0xFFFFFFFF
;_HT32FWID           EQU     0x00012366

HT32F1653_54_55_56  EQU     1
HT32F12365_66       EQU     2
HT32F12345          EQU     3

  IF USE_HT32_CHIP_SET=0
  ; Use project's Asm Define setting (default)
  ELSE
  IF :DEF:USE_HT32_CHIP
  ; Use project's Asm Define setting (higher priority than the "USE_HT32_CHIP_SET")
  ELSE
  ; Use "USE_HT32_CHIP_SET" in the "startup_ht32xxxxx_xx.s" file
USE_HT32_CHIP       EQU     USE_HT32_CHIP_SET
  ENDIF
  ENDIF

; Amount of memory (in bytes) allocated for Stack and Heap
; Tailor those values to your application needs
;//   <o> Stack Size (in Bytes, must 8 byte aligned) <0-131072:8>
Stack_Size          EQU     512

                    AREA    STACK, NOINIT, READWRITE, ALIGN = 3
__HT_check_sp
Stack_Mem           SPACE   Stack_Size
__initial_sp

;//   <o>  Heap Size (in Bytes) <0-131072:8>
Heap_Size           EQU     0

                    AREA    HEAP, NOINIT, READWRITE, ALIGN = 3
__HT_check_heap
__heap_base
Heap_Mem            SPACE   Heap_Size
__heap_limit

                    PRESERVE8
                    THUMB

;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;*******************************************************************************
                    AREA    RESET, CODE, READONLY
                    EXPORT  __Vectors
_RESERVED           EQU  0xFFFFFFFF
__Vectors
                    DCD  __initial_sp                       ; ---, 00, 0x000, Top address of Stack
                    DCD  Reset_Handler                      ; ---, 01, 0x004, Reset Handler
                    DCD  NMI_Handler                        ; ---, 02, 0x008, NMI Handler
                    DCD  HardFault_Handler                  ; ---, 03, 0x00C, Hard Fault Handler
                    DCD  MemManage_Handler                  ; ---, 04, 0x010, Memory Management Fault Handler
                    DCD  BusFault_Handler                   ; ---, 05, 0x014, Bus Fault Handler
                    DCD  UsageFault_Handler                 ; ---, 06, 0x018, Usage Fault Handler
                    DCD  _RESERVED                          ; ---, 07, 0x01C, Reserved
                    DCD  _HT32FWID                          ; ---, 08, 0x020, Reserved
                    DCD  _RESERVED                          ; ---, 09, 0x024, Reserved
                    DCD  _RESERVED                          ; ---, 10, 0x028, Reserved
                    DCD  SVC_Handler                        ; ---, 11, 0x02C, SVC Handler
                    DCD  DebugMon_Handler                   ; ---, 12, 0x030, Debug Monitor Handler
                    DCD  _RESERVED                          ; ---, 13, 0x034, Reserved
                    DCD  PendSV_Handler                     ; ---, 14, 0x038, PendSV Handler
                    DCD  SysTick_Handler                    ; ---, 15, 0x03C, SysTick Handler

                    ; External Interrupt Handler
                    DCD  CKRDY_IRQHandler                   ;  00, 16, 0x040,
                    DCD  LVD_IRQHandler                     ;  01, 17, 0x044,
                    DCD  BOD_IRQHandler                     ;  02, 18, 0x048,
                  IF (USE_HT32_CHIP=HT32F1653_54_55_56)
                    DCD  WDT_IRQHandler                     ;  03, 19, 0x04C,
                  ELSE
                    DCD  _RESERVED                          ;  03, 19, 0x04C,
                  ENDIF
                    DCD  RTC_IRQHandler                     ;  04, 20, 0x050,
                    DCD  FLASH_IRQHandler                   ;  05, 21, 0x054,
                    DCD  EVWUP_IRQHandler                   ;  06, 22, 0x058,
                    DCD  LPWUP_IRQHandler                   ;  07, 23, 0x05C,
                    DCD  EXTI0_IRQHandler                   ;  08, 24, 0x060,
                    DCD  EXTI1_IRQHandler                   ;  09, 25, 0x064,
                    DCD  EXTI2_IRQHandler                   ;  10, 26, 0x068,
                    DCD  EXTI3_IRQHandler                   ;  11, 27, 0x06C,
                    DCD  EXTI4_IRQHandler                   ;  12, 28, 0x070,
                    DCD  EXTI5_IRQHandler                   ;  13, 29, 0x074,
                    DCD  EXTI6_IRQHandler                   ;  14, 30, 0x078,
                    DCD  EXTI7_IRQHandler                   ;  15, 31, 0x07C,
                    DCD  EXTI8_IRQHandler                   ;  16, 32, 0x080,
                    DCD  EXTI9_IRQHandler                   ;  17, 33, 0x084,
                    DCD  EXTI10_IRQHandler                  ;  18, 34, 0x088,
                    DCD  EXTI11_IRQHandler                  ;  19, 35, 0x08C,
                    DCD  EXTI12_IRQHandler                  ;  20, 36, 0x090,
                    DCD  EXTI13_IRQHandler                  ;  21, 37, 0x094,
                    DCD  EXTI14_IRQHandler                  ;  22, 38, 0x098,
                    DCD  EXTI15_IRQHandler                  ;  23, 39, 0x09C,
                    DCD  COMP_IRQHandler                    ;  24, 40, 0x0A0,
                    DCD  ADC_IRQHandler                     ;  25, 41, 0x0A4,
                    DCD  _RESERVED                          ;  26, 42, 0x0A8,
                    DCD  MCTM0BRK_IRQHandler                ;  27, 43, 0x0AC,
                    DCD  MCTM0UP_IRQHandler                 ;  28, 44, 0x0B0,
                    DCD  MCTM0TR_IRQHandler                 ;  29, 45, 0x0B4,
                    DCD  MCTM0CC_IRQHandler                 ;  30, 46, 0x0B8,
                    DCD  MCTM1BRK_IRQHandler                ;  31, 47, 0x0BC,
                    DCD  MCTM1UP_IRQHandler                 ;  32, 48, 0x0C0,
                    DCD  MCTM1TR_IRQHandler                 ;  33, 49, 0x0C4,
                    DCD  MCTM1CC_IRQHandler                 ;  34, 50, 0x0C8,
                    DCD  GPTM0_IRQHandler                   ;  35, 51, 0x0CC,
                    DCD  GPTM1_IRQHandler                   ;  36, 52, 0x0D0,
                    DCD  _RESERVED                          ;  37, 53, 0x0D4,
                    DCD  _RESERVED                          ;  38, 54, 0x0D8,
                    DCD  _RESERVED                          ;  39, 55, 0x0DC,
                    DCD  _RESERVED                          ;  40, 56, 0x0E0,
                    DCD  BFTM0_IRQHandler                   ;  41, 57, 0x0E4,
                    DCD  BFTM1_IRQHandler                   ;  42, 58, 0x0E8,
                    DCD  I2C0_IRQHandler                    ;  43, 59, 0x0EC,
                    DCD  I2C1_IRQHandler                    ;  44, 60, 0x0F0,
                    DCD  SPI0_IRQHandler                    ;  45, 61, 0x0F4,
                    DCD  SPI1_IRQHandler                    ;  46, 62, 0x0F8,
                    DCD  USART0_IRQHandler                  ;  47, 63, 0x0FC,
                    DCD  USART1_IRQHandler                  ;  48, 64, 0x100,
                    DCD  UART0_IRQHandler                   ;  49, 65, 0x104,
                    DCD  UART1_IRQHandler                   ;  50, 66, 0x108,
                  IF (USE_HT32_CHIP=HT32F12345)
                    DCD  _RESERVED                          ;  51, 67, 0x10C,
                  ELSE
                    DCD  SCI_IRQHandler                     ;  51, 67, 0x10C,
                  ENDIF
                    DCD  I2S_IRQHandler                     ;  52, 68, 0x110,
                    DCD  USB_IRQHandler                     ;  53, 69, 0x114,
                  IF (USE_HT32_CHIP=HT32F1653_54_55_56)
                    DCD  _RESERVED                          ;  54, 70, 0x118,
                  ELSE
                    DCD  SDIO_IRQHandler                    ;  54, 70, 0x118,
                  ENDIF
                    DCD  PDMA_CH0_IRQHandler                ;  55, 71, 0x11C,
                    DCD  PDMA_CH1_IRQHandler                ;  56, 72, 0x120,
                    DCD  PDMA_CH2_IRQHandler                ;  57, 73, 0x124,
                    DCD  PDMA_CH3_IRQHandler                ;  58, 74, 0x128,
                    DCD  PDMA_CH4_IRQHandler                ;  59, 75, 0x12C,
                    DCD  PDMA_CH5_IRQHandler                ;  60, 76, 0x130,
                    DCD  PDMA_CH6_IRQHandler                ;  61, 77, 0x134,
                    DCD  PDMA_CH7_IRQHandler                ;  62, 78, 0x138,
                  IF (USE_HT32_CHIP=HT32F1653_54_55_56)
                    DCD  _RESERVED                          ;  63, 79, 0x13C,
                    DCD  _RESERVED                          ;  64, 80, 0x140,
                    DCD  _RESERVED                          ;  65, 81, 0x144,
                    DCD  _RESERVED                          ;  66, 82, 0x148,
                  ELSE
                    DCD  PDMA_CH8_IRQHandler                ;  63, 79, 0x13C,
                    DCD  PDMA_CH9_IRQHandler                ;  64, 80, 0x140,
                    DCD  PDMA_CH10_IRQHandler               ;  65, 81, 0x144,
                    DCD  PDMA_CH11_IRQHandler               ;  66, 82, 0x148,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F12365_66)
                    DCD  CSIF_IRQHandler                    ;  67, 83, 0x14C,
                  ELSE
                    DCD  _RESERVED                          ;  67, 83, 0x14C,
                  ENDIF
                    DCD  EBI_IRQHandler                     ;  68, 84, 0x150,
                  IF (USE_HT32_CHIP=HT32F12365_66)
                    DCD  AES_IRQHandler                     ;  69, 85, 0x154,
                  ENDIF

; Reset handler routine
Reset_Handler       PROC
                    EXPORT  Reset_Handler                   [WEAK]
                    IMPORT  SystemInit
                    IMPORT  __main
                    IF (USE_HT32_CHIP=HT32F1653_54_55_56)
                    ELSE
                    LDR     R0, =BootProcess
                    BLX     R0
                    ENDIF
                    LDR     R0, =SystemInit
                    BLX     R0
                    LDR     R0, =__main
                    BX      R0
                    ENDP

                    IF (USE_HT32_CHIP=HT32F1653_54_55_56)
                    ELSE
BootProcess         PROC
                    LDR     R0, =0x40080300
                    LDR     R1,[R0, #0x10]
                    CMP     R1, #0
                    BNE     BP1
                    LDR     R1,[R0, #0x14]
                    CMP     R1, #0
                    BNE     BP1
                    LDR     R1,[R0, #0x18]
                    CMP     R1, #0
                    BNE     BP1
                    LDR     R1,[R0, #0x1C]
                    CMP     R1, #0
                    BEQ     BP2
BP1                 LDR     R0, =0x40080180
                    LDR     R1,[R0, #0xC]
                    LSLS    R1, R1, #4
                    LSRS    R1, R1, #20
                    CMP     R1, #0
                    BEQ     BP3
                    CMP     R1, #1
                    BEQ     BP3
                    CMP     R1, #2
                    BEQ     BP3
BP2                 DSB
                    LDR     R0, =0x20000000
                    LDR     R1, =0x05fa0004
                    STR     R1, [R0]
                    LDR     R1, =0xe000ed00
                    LDR     R0, =0x05fa0004
                    STR     R0, [R1, #0xC]
                    DSB
                    B       .
BP3                 LDR     R0, =0x20000000
                    LDR     R1, [R0]
                    LDR     R0, =0x05fa0004
                    CMP     R0, R1
                    BEQ     BP4
                    BX      LR
BP4                 LDR     R0, =0x40088100
                    LDR     R1, =0x00000001
                    STR     R1, [R0]
                    LDR     R0, =0x20000000
                    LDR     R1, =0x0
                    STR     R1, [R0]
                    BX      LR
                    ENDP
                    ENDIF

; Dummy Exception Handlers
NMI_Handler         PROC
                    EXPORT  NMI_Handler                     [WEAK]
                    B       .
                    ENDP

HardFault_Handler   PROC
                    EXPORT  HardFault_Handler               [WEAK]
                    B       .
                    ENDP

MemManage_Handler   PROC
                    EXPORT  MemManage_Handler               [WEAK]
                    B       .
                    ENDP

BusFault_Handler    PROC
                    EXPORT  BusFault_Handler                [WEAK]
                    B       .
                    ENDP

UsageFault_Handler  PROC
                    EXPORT  UsageFault_Handler              [WEAK]
                    B       .
                    ENDP

SVC_Handler         PROC
                    EXPORT  SVC_Handler                     [WEAK]
                    B       .
                    ENDP

DebugMon_Handler    PROC
                    EXPORT  DebugMon_Handler                [WEAK]
                    B       .
                    ENDP

PendSV_Handler      PROC
                    EXPORT  PendSV_Handler                  [WEAK]
                    B       .
                    ENDP

SysTick_Handler     PROC
                    EXPORT  SysTick_Handler                 [WEAK]
                    B       .
                    ENDP

Default_Handler     PROC
                    EXPORT  CKRDY_IRQHandler                [WEAK]
                    EXPORT  LVD_IRQHandler                  [WEAK]
                    EXPORT  BOD_IRQHandler                  [WEAK]
                    EXPORT  WDT_IRQHandler                  [WEAK]
                    EXPORT  RTC_IRQHandler                  [WEAK]
                    EXPORT  FLASH_IRQHandler                [WEAK]
                    EXPORT  EVWUP_IRQHandler                [WEAK]
                    EXPORT  LPWUP_IRQHandler                [WEAK]
                    EXPORT  EXTI0_IRQHandler                [WEAK]
                    EXPORT  EXTI1_IRQHandler                [WEAK]
                    EXPORT  EXTI2_IRQHandler                [WEAK]
                    EXPORT  EXTI3_IRQHandler                [WEAK]
                    EXPORT  EXTI4_IRQHandler                [WEAK]
                    EXPORT  EXTI5_IRQHandler                [WEAK]
                    EXPORT  EXTI6_IRQHandler                [WEAK]
                    EXPORT  EXTI7_IRQHandler                [WEAK]
                    EXPORT  EXTI8_IRQHandler                [WEAK]
                    EXPORT  EXTI9_IRQHandler                [WEAK]
                    EXPORT  EXTI10_IRQHandler               [WEAK]
                    EXPORT  EXTI11_IRQHandler               [WEAK]
                    EXPORT  EXTI12_IRQHandler               [WEAK]
                    EXPORT  EXTI13_IRQHandler               [WEAK]
                    EXPORT  EXTI14_IRQHandler               [WEAK]
                    EXPORT  EXTI15_IRQHandler               [WEAK]
                    EXPORT  COMP_IRQHandler                 [WEAK]
                    EXPORT  ADC_IRQHandler                  [WEAK]
                    EXPORT  MCTM0BRK_IRQHandler             [WEAK]
                    EXPORT  MCTM0UP_IRQHandler              [WEAK]
                    EXPORT  MCTM0TR_IRQHandler              [WEAK]
                    EXPORT  MCTM0CC_IRQHandler              [WEAK]
                    EXPORT  MCTM1BRK_IRQHandler             [WEAK]
                    EXPORT  MCTM1UP_IRQHandler              [WEAK]
                    EXPORT  MCTM1TR_IRQHandler              [WEAK]
                    EXPORT  MCTM1CC_IRQHandler              [WEAK]
                    EXPORT  GPTM0_IRQHandler                [WEAK]
                    EXPORT  GPTM1_IRQHandler                [WEAK]
                    EXPORT  BFTM0_IRQHandler                [WEAK]
                    EXPORT  BFTM1_IRQHandler                [WEAK]
                    EXPORT  I2C0_IRQHandler                 [WEAK]
                    EXPORT  I2C1_IRQHandler                 [WEAK]
                    EXPORT  SPI0_IRQHandler                 [WEAK]
                    EXPORT  SPI1_IRQHandler                 [WEAK]
                    EXPORT  USART0_IRQHandler               [WEAK]
                    EXPORT  USART1_IRQHandler               [WEAK]
                    EXPORT  UART0_IRQHandler                [WEAK]
                    EXPORT  UART1_IRQHandler                [WEAK]
                    EXPORT  SCI_IRQHandler                  [WEAK]
                    EXPORT  I2S_IRQHandler                  [WEAK]
                    EXPORT  USB_IRQHandler                  [WEAK]
                    EXPORT  SDIO_IRQHandler                 [WEAK]
                    EXPORT  PDMA_CH0_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH1_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH2_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH3_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH4_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH5_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH6_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH7_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH8_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH9_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH10_IRQHandler            [WEAK]
                    EXPORT  PDMA_CH11_IRQHandler            [WEAK]
                    EXPORT  CSIF_IRQHandler                 [WEAK]
                    EXPORT  EBI_IRQHandler                  [WEAK]
                    EXPORT  AES_IRQHandler                  [WEAK]
CKRDY_IRQHandler
LVD_IRQHandler
BOD_IRQHandler
WDT_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
EVWUP_IRQHandler
LPWUP_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
EXTI5_IRQHandler
EXTI6_IRQHandler
EXTI7_IRQHandler
EXTI8_IRQHandler
EXTI9_IRQHandler
EXTI10_IRQHandler
EXTI11_IRQHandler
EXTI12_IRQHandler
EXTI13_IRQHandler
EXTI14_IRQHandler
EXTI15_IRQHandler
COMP_IRQHandler
ADC_IRQHandler
MCTM0BRK_IRQHandler
MCTM0UP_IRQHandler
MCTM0TR_IRQHandler
MCTM0CC_IRQHandler
MCTM1BRK_IRQHandler
MCTM1UP_IRQHandler
MCTM1TR_IRQHandler
MCTM1CC_IRQHandler
GPTM0_IRQHandler
GPTM1_IRQHandler
BFTM0_IRQHandler
BFTM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
SCI_IRQHandler
I2S_IRQHandler
USB_IRQHandler
SDIO_IRQHandler
PDMA_CH0_IRQHandler
PDMA_CH1_IRQHandler
PDMA_CH2_IRQHandler
PDMA_CH3_IRQHandler
PDMA_CH4_IRQHandler
PDMA_CH5_IRQHandler
PDMA_CH6_IRQHandler
PDMA_CH7_IRQHandler
PDMA_CH8_IRQHandler
PDMA_CH9_IRQHandler
PDMA_CH10_IRQHandler
PDMA_CH11_IRQHandler
CSIF_IRQHandler
EBI_IRQHandler
AES_IRQHandler
                    B       .
                    ENDP

                    ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                    IF      :DEF:__MICROLIB

                    EXPORT  __HT_check_heap
                    EXPORT  __HT_check_sp
                    EXPORT  __initial_sp
                    EXPORT  __heap_base
                    EXPORT  __heap_limit

                    ELSE

                    IMPORT  __use_two_region_memory
                    EXPORT  __user_initial_stackheap
__user_initial_stackheap

                    LDR     R0, =  Heap_Mem
                    LDR     R1, = (Stack_Mem + Stack_Size)
                    LDR     R2, = (Heap_Mem + Heap_Size)
                    LDR     R3, = Stack_Mem
                    BX      LR

                    ALIGN

                    ENDIF

                    END
