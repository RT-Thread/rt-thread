;/*---------------------------------------------------------------------------------------------------------*/
;/* Holtek Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f65230_40_iar.s
;  Version          : $Rev:: 6877         $
;  Date             : $Date:: 2023-05-04 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

;  Supported Device
;  ========================================
;   HT32F65230
;   HT32F65240

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */

;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <12=> HT32F65230_40
USE_HT32_CHIP_SET   EQU     0

_HT32FWID           EQU     0xFFFFFFFF
;_HT32FWID           EQU     0x00065230
;_HT32FWID           EQU     0x00065240

HT32F65230_40          EQU     12

  IF USE_HT32_CHIP_SET=0
  ELSE
  #undef  USE_HT32_CHIP
  #define USE_HT32_CHIP      USE_HT32_CHIP_SET
  ENDIF

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;*******************************************************************************
                    DATA
_RESERVED           EQU  0xFFFFFFFF
__vector_table
                    DCD  sfe(CSTACK)                        ; ---, 00, 0x000, Top address of Stack
                    DCD  Reset_Handler                      ; ---, 01, 0x004, Reset Handler
                    DCD  NMI_Handler                        ; -14, 02, 0x008, NMI Handler
                    DCD  HardFault_Handler                  ; -13, 03, 0x00C, Hard Fault Handler
                    DCD  _RESERVED                          ; ---, 04, 0x010, Reserved
                    DCD  _RESERVED                          ; ---, 05, 0x014, Reserved
                    DCD  _RESERVED                          ; ---, 06, 0x018, Reserved
                    DCD  _RESERVED                          ; ---, 07, 0x01C, Reserved
                    DCD  _HT32FWID                          ; ---, 08, 0x020, Reserved
                    DCD  _RESERVED                          ; ---, 09, 0x024, Reserved
                    DCD  _RESERVED                          ; ---, 10, 0x028, Reserved
                    DCD  SVC_Handler                        ; -05, 11, 0x02C, SVC Handler
                    DCD  _RESERVED                          ; ---, 12, 0x030, Reserved
                    DCD  _RESERVED                          ; ---, 13, 0x034, Reserved
                    DCD  PendSV_Handler                     ; -02, 14, 0x038, PendSV Handler
                    DCD  SysTick_Handler                    ; -01, 15, 0x03C, SysTick Handler

                    ; External Interrupt Handler
                    DCD  LVD_BOD_IRQHandler                 ;  00, 16, 0x040,
                    DCD  RTC_IRQHandler                     ;  01, 17, 0x044,
                    DCD  FLASH_IRQHandler                   ;  02, 18, 0x048,
                    DCD  EVWUP_IRQHandler                   ;  03, 19, 0x04C,
                    DCD  EXTI0_1_IRQHandler                 ;  04, 20, 0x050,
                    DCD  EXTI2_3_IRQHandler                 ;  05, 21, 0x054,
                    DCD  EXTI4_9_IRQHandler                 ;  06, 22, 0x058,
                    DCD  EXTI10_15_IRQHandler               ;  07, 23, 0x05C,
                    DCD  ADC0_IRQHandler                    ;  08, 24, 0x060,
                    DCD  ADC1_IRQHandler                    ;  09, 25, 0x064,
                    DCD  MCTM0_BRK_IRQHandler               ;  10, 26, 0x068,
                    DCD  MCTM0_UP_IRQHandler                ;  11, 27, 0x06C,
                    DCD  MCTM0_TR_UP2_IRQHandler            ;  12, 28, 0x070,
                    DCD  MCTM0_CC_IRQHandler                ;  13, 29, 0x074,
                    DCD  GPTM0_G_IRQHandler                 ;  14, 30, 0x078,
                    DCD  GPTM0_VCLK_IRQHandler              ;  15, 31, 0x07C,
                    DCD  BFTM0_IRQHandler                   ;  16, 32, 0x080,
                    DCD  BFTM1_IRQHandler                   ;  17, 33, 0x084,
                    DCD  CMP0_IRQHandler                    ;  18, 34, 0x088,
                    DCD  CMP1_IRQHandler                    ;  19, 35, 0x08C,
                    DCD  CMP2_IRQHandler                    ;  20, 36, 0x090,
                    DCD  I2C0_IRQHandler                    ;  21, 37, 0x094,
                    DCD  SPI0_IRQHandler                    ;  22, 38, 0x098,
                    DCD  USART0_IRQHandler                  ;  23, 39, 0x09C,
                    DCD  UART0_IRQHandler                   ;  24, 40, 0x0A0,
                    DCD  PDMA_CH0_1_IRQHandler              ;  25, 41, 0x0A4,
                    DCD  PDMA_CH2_3_IRQHandler              ;  26, 42, 0x0A8,
                    DCD  PDMA_CH4_5_IRQHandler              ;  27, 43, 0x0AC,
                    DCD  SCTM0_IRQHandler                   ;  28, 44, 0x0B0,
                    DCD  SCTM1_IRQHandler                   ;  29, 45, 0x0B4,
                    DCD  SCTM2_IRQHandler                   ;  30, 46, 0x0B8,
                    DCD  SCTM3_IRQHandler                   ;  31, 47, 0x0BC,

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
                    B       .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
                    B       .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
                    B       .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
                    B       .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
                    B       .


        PUBWEAK LVD_BOD_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK FLASH_IRQHandler
        PUBWEAK EVWUP_IRQHandler
        PUBWEAK EXTI0_1_IRQHandler
        PUBWEAK EXTI2_3_IRQHandler
        PUBWEAK EXTI4_9_IRQHandler
        PUBWEAK EXTI10_15_IRQHandler
        PUBWEAK ADC0_IRQHandler
        PUBWEAK ADC1_IRQHandler
        PUBWEAK MCTM0_BRK_IRQHandler
        PUBWEAK MCTM0_UP_IRQHandler
        PUBWEAK MCTM0_TR_UP2_IRQHandler
        PUBWEAK MCTM0_CC_IRQHandler
        PUBWEAK GPTM0_G_IRQHandler
        PUBWEAK GPTM0_VCLK_IRQHandler
        PUBWEAK BFTM0_IRQHandler
        PUBWEAK BFTM1_IRQHandler
        PUBWEAK CMP0_IRQHandler
        PUBWEAK CMP1_IRQHandler
        PUBWEAK CMP2_IRQHandler
        PUBWEAK I2C0_IRQHandler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK USART0_IRQHandler
        PUBWEAK UART0_IRQHandler
        PUBWEAK PDMA_CH0_1_IRQHandler
        PUBWEAK PDMA_CH2_3_IRQHandler
        PUBWEAK PDMA_CH4_5_IRQHandler
        PUBWEAK SCTM0_IRQHandler
        PUBWEAK SCTM1_IRQHandler
        PUBWEAK SCTM2_IRQHandler
        PUBWEAK SCTM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LVD_BOD_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
EVWUP_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_9_IRQHandler
EXTI10_15_IRQHandler
ADC0_IRQHandler
ADC1_IRQHandler
MCTM0_BRK_IRQHandler
MCTM0_UP_IRQHandler
MCTM0_TR_UP2_IRQHandler
MCTM0_CC_IRQHandler
GPTM0_G_IRQHandler
GPTM0_VCLK_IRQHandler
BFTM0_IRQHandler
BFTM1_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
CMP2_IRQHandler
I2C0_IRQHandler
SPI0_IRQHandler
USART0_IRQHandler
UART0_IRQHandler
PDMA_CH0_1_IRQHandler
PDMA_CH2_3_IRQHandler
PDMA_CH4_5_IRQHandler
SCTM0_IRQHandler
SCTM1_IRQHandler
SCTM2_IRQHandler
SCTM3_IRQHandler
                    B       .

                    END
