;/*---------------------------------------------------------------------------------------------------------*/
;/* Holtek Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f5xxxx_iar_01.s
;  Version          : $Rev:: 6953         $
;  Date             : $Date:: 2023-05-30 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

;  Supported Device
;  ========================================
;   HT32F52220, HT32F52230
;   HT32F52231, HT32F52241
;   HT32F52331, HT32F52341
;   HT32F52342, HT32F52352
;   HT32F52243, HT32F52253
;   HT32F0008
;   HT32F52344, HT32F52354
;   HT32F0006
;   HT32F61352
;   HT50F32003
;   HT32F62030, HT32F62040, HT32F62050
;   HT32F67741
;   HT32F67232
;   HT32F67233

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */

;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <1=> HT32F52220/30
;//      <2=> HT32F52231/41
;//      <3=> HT32F52331/41
;//      <4=> HT32F52342/52
;//      <5=> HT32F52243/53
;//      <6=> HT32F0008
;//      <9=> HT32F52344/54
;//      <10=> HT32F0006
;//      <10=> HT32F61352
;//      <4=> HT50F32003
;//      <2=> HT32F67741
;//      <1=> HT32F67232
;//      <1=> HT32F67233
;//      <1=> HT32F62030
;//      <2=> HT32F62040
;//      <5=> HT32F62050
USE_HT32_CHIP_SET   EQU     0

_HT32FWID           EQU     0xFFFFFFFF
;_HT32FWID           EQU     0x00052220
;_HT32FWID           EQU     0x00052230
;_HT32FWID           EQU     0x00052231
;_HT32FWID           EQU     0x00052241
;_HT32FWID           EQU     0x00052331
;_HT32FWID           EQU     0x00052341
;_HT32FWID           EQU     0x00052342
;_HT32FWID           EQU     0x00052352
;_HT32FWID           EQU     0x00052243
;_HT32FWID           EQU     0x00052253
;_HT32FWID           EQU     0x00000008
;_HT32FWID           EQU     0x00052344
;_HT32FWID           EQU     0x00052354
;_HT32FWID           EQU     0x00000006
;_HT32FWID           EQU     0x00061352
;_HT32FWID           EQU     0x00032003
;_HT32FWID           EQU     0x00062030
;_HT32FWID           EQU     0x00062040
;_HT32FWID           EQU     0x00062050
;_HT32FWID           EQU     0x00067741
;_HT32FWID           EQU     0x00067232
;_HT32FWID           EQU     0x00067233

HT32F52220_30       EQU     1
HT32F52231_41       EQU     2
HT32F52331_41       EQU     3
HT32F52342_52       EQU     4
HT32F52243_53       EQU     5
HT32F0008           EQU     6
HT32F52344_54       EQU     9
HT32F0006           EQU     10
HT32F61352          EQU     10
HT50F32003          EQU     4
HT32F62030          EQU     1
HT32F62040          EQU     2
HT32F62050          EQU     5
HT32F67741          EQU     2
HT32F67232          EQU     1
HT32F67233          EQU     1

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
                  IF (USE_HT32_CHIP=HT32F52220_30)
                    DCD  _RESERVED                          ;  01, 17, 0x044,
                  ELSE
                    DCD  RTC_IRQHandler                     ;  01, 17, 0x044,
                  ENDIF
                    DCD  FLASH_IRQHandler                   ;  02, 18, 0x048,
                    DCD  EVWUP_IRQHandler                   ;  03, 19, 0x04C,
                    DCD  EXTI0_1_IRQHandler                 ;  04, 20, 0x050,
                    DCD  EXTI2_3_IRQHandler                 ;  05, 21, 0x054,
                    DCD  EXTI4_15_IRQHandler                ;  06, 22, 0x058,
                  IF (USE_HT32_CHIP=HT32F52342_52) || (USE_HT32_CHIP=HT32F52344_54)
                    DCD  COMP_IRQHandler                    ;  07, 23, 0x05C,
                  ELSE
                    DCD  _RESERVED                          ;  07, 23, 0x05C,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F0008)
                    DCD  _RESERVED                          ;  08, 24, 0x060,
                  ELSE
                    DCD  ADC_IRQHandler                     ;  08, 24, 0x060,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52243_53)
                    DCD  I2C2_IRQHandler                    ;  09, 25, 0x064,
                  ELSE
                    DCD  _RESERVED                          ;  09, 25, 0x064,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52220_30) || (USE_HT32_CHIP=HT32F0008) || (USE_HT32_CHIP=HT32F0006)
                    DCD  _RESERVED                          ;  10, 26, 0x068,
                  ELSE
                    DCD  MCTM0_IRQHandler                   ;  10, 26, 0x068,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52342_52)
                    DCD  GPTM1_IRQHandler                   ;  11, 27, 0x06C,
                  ELSE
                    DCD  _RESERVED                          ;  11, 27, 0x06C,
                  ENDIF
                    DCD  GPTM0_IRQHandler                   ;  12, 28, 0x070,
                  IF (USE_HT32_CHIP=HT32F0008)
                    DCD  _RESERVED                          ;  13, 29, 0x074,
                    DCD  _RESERVED                          ;  14, 30, 0x078,
                  ELSE
                    DCD  SCTM0_IRQHandler                   ;  13, 29, 0x074,
                    DCD  SCTM1_IRQHandler                   ;  14, 30, 0x078,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52231_41) || (USE_HT32_CHIP=HT32F52331_41) || (USE_HT32_CHIP=HT32F52243_53) || (USE_HT32_CHIP=HT32F0006)
                    DCD  SCTM2_IRQHandler                   ;  15, 31, 0x07C,
                    DCD  SCTM3_IRQHandler                   ;  16, 32, 0x080,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F0008)
                    DCD  PWM0_IRQHandler                    ;  15, 31, 0x07C,
                    DCD  PWM1_IRQHandler                    ;  16, 32, 0x080,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52220_30) || (USE_HT32_CHIP=HT32F52342_52) || (USE_HT32_CHIP=HT32F52344_54)
                    DCD  _RESERVED                          ;  15, 31, 0x07C,
                    DCD  _RESERVED                          ;  16, 32, 0x080,
                  ENDIF
                    DCD  BFTM0_IRQHandler                   ;  17, 33, 0x084,
                  IF (USE_HT32_CHIP=HT32F52220_30)
                    DCD  _RESERVED                          ;  18, 34, 0x088,
                  ELSE
                    DCD  BFTM1_IRQHandler                   ;  18, 34, 0x088,
                  ENDIF
                    DCD  I2C0_IRQHandler                    ;  19, 35, 0x08C,
                  IF (USE_HT32_CHIP=HT32F52220_30) || (USE_HT32_CHIP=HT32F0008) || (USE_HT32_CHIP=HT32F52344_54) || (USE_HT32_CHIP=HT32F0006)
                    DCD  _RESERVED                          ;  20, 36, 0x090,
                  ELSE
                    DCD  I2C1_IRQHandler                    ;  20, 36, 0x090,
                  ENDIF
                    DCD  SPI0_IRQHandler                    ;  21, 37, 0x094,
                  IF (USE_HT32_CHIP=HT32F52220_30) || (USE_HT32_CHIP=HT32F0008)
                    DCD  _RESERVED                          ;  22, 38, 0x098,
                  ELSE
                    IF (USE_HT32_CHIP=HT32F0006)
                      DCD  QSPI_IRQHandler                  ;  22, 38, 0x098,
                    ELSE
                      DCD  SPI1_IRQHandler                  ;  22, 38, 0x098,
                    ENDIF
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52344_54)
                    DCD  _RESERVED                          ;  23, 39, 0x09C,
                  ELSE
                    DCD  USART0_IRQHandler                  ;  23, 39, 0x09C,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52342_52) || (USE_HT32_CHIP=HT32F52243_53)
                    DCD  USART1_IRQHandler                  ;  24, 40, 0x0A0,
                  ELSE
                    DCD  _RESERVED                          ;  24, 40, 0x0A0,
                  ENDIF
                    DCD  UART0_IRQHandler                   ;  25, 41, 0x0A4,
                  IF (USE_HT32_CHIP=HT32F52220_30) || (USE_HT32_CHIP=HT32F0008) || (USE_HT32_CHIP=HT32F0006)
                    DCD  _RESERVED                          ;  26, 42, 0x0A8,
                  ELSE
                    DCD  UART1_IRQHandler                   ;  26, 42, 0x0A8,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52331_41) || (USE_HT32_CHIP=HT32F52342_52)
                    DCD  SCI_IRQHandler                     ;  27, 43, 0x0AC,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52243_53)
                    DCD  UART2_IRQHandler                   ;  27, 43, 0x0AC,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F0006)
                    DCD  MIDI_IRQHandler                    ;  27, 43, 0x0AC,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F0008) || (USE_HT32_CHIP=HT32F52344_54)
                    DCD  _RESERVED                          ;  27, 43, 0xAC,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52342_52) || (USE_HT32_CHIP=HT32F0006)
                    DCD  I2S_IRQHandler                     ;  28, 44, 0x0B0,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52331_41) || (USE_HT32_CHIP=HT32F52344_54)
                    DCD  _RESERVED                          ;  28, 44, 0x0B0,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52243_53)
                    DCD  UART3_IRQHandler                   ;  28, 44, 0x0B0,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F0008)
                    DCD  AES_IRQHandler                     ;  28, 44, 0x0B0,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52331_41) || (USE_HT32_CHIP=HT32F52342_52) || (USE_HT32_CHIP=HT32F0008) || (USE_HT32_CHIP=HT32F52344_54) || (USE_HT32_CHIP=HT32F0006)
                    DCD  USB_IRQHandler                     ;  29, 45, 0x0B4,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52243_53)
                    DCD  _RESERVED                          ;  29, 45, 0x0B4,
                  ENDIF
                  IF (USE_HT32_CHIP=HT32F52342_52) || (USE_HT32_CHIP=HT32F52243_53) || (USE_HT32_CHIP=HT32F0008) || (USE_HT32_CHIP=HT32F52344_54) || (USE_HT32_CHIP=HT32F0006)
                    DCD  PDMA_CH0_1_IRQHandler              ;  30, 46, 0x0B8,
                    DCD  PDMA_CH2_5_IRQHandler              ;  31, 47, 0x0BC,
                  ENDIF

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                    LDR     R0, =BootProcess
                    BLX     R0
                    LDR     R0, =SystemInit
                    BLX     R0
                    LDR     R0, =__iar_program_start
                    BX      R0

BootProcess
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
                    CMP     R1, #5
                    BEQ     BP3
                    CMP     R1, #6
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
        PUBWEAK EXTI4_15_IRQHandler
        PUBWEAK COMP_IRQHandler
        PUBWEAK ADC_IRQHandler
        PUBWEAK MCTM0_IRQHandler
        PUBWEAK GPTM0_IRQHandler
        PUBWEAK GPTM1_IRQHandler
        PUBWEAK SCTM0_IRQHandler
        PUBWEAK SCTM1_IRQHandler
        PUBWEAK SCTM2_IRQHandler
        PUBWEAK SCTM3_IRQHandler
        PUBWEAK PWM0_IRQHandler
        PUBWEAK PWM1_IRQHandler
        PUBWEAK BFTM0_IRQHandler
        PUBWEAK BFTM1_IRQHandler
        PUBWEAK I2C0_IRQHandler
        PUBWEAK I2C1_IRQHandler
        PUBWEAK I2C2_IRQHandler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK QSPI_IRQHandler
        PUBWEAK USART0_IRQHandler
        PUBWEAK USART1_IRQHandler
        PUBWEAK UART0_IRQHandler
        PUBWEAK UART1_IRQHandler
        PUBWEAK UART2_IRQHandler
        PUBWEAK UART3_IRQHandler
        PUBWEAK SCI_IRQHandler
        PUBWEAK MIDI_IRQHandler
        PUBWEAK I2S_IRQHandler
        PUBWEAK AES_IRQHandler
        PUBWEAK USB_IRQHandler
        PUBWEAK PDMA_CH0_1_IRQHandler
        PUBWEAK PDMA_CH2_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LVD_BOD_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
EVWUP_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
COMP_IRQHandler
ADC_IRQHandler
MCTM0_IRQHandler
GPTM1_IRQHandler
GPTM0_IRQHandler
SCTM0_IRQHandler
SCTM1_IRQHandler
SCTM2_IRQHandler
SCTM3_IRQHandler
PWM0_IRQHandler
PWM1_IRQHandler
BFTM0_IRQHandler
BFTM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
QSPI_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
SCI_IRQHandler
MIDI_IRQHandler
I2S_IRQHandler
AES_IRQHandler
USB_IRQHandler
PDMA_CH0_1_IRQHandler
PDMA_CH2_5_IRQHandler
                    B       .

                    END
