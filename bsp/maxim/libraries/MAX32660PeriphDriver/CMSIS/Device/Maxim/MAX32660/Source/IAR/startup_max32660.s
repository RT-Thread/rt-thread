;*******************************************************************************
;* Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
;*
;* Permission is hereby granted, free of charge, to any person obtaining a
;* copy of this software and associated documentation files (the "Software"),
;* to deal in the Software without restriction, including without limitation
;* the rights to use, copy, modify, merge, publish, distribute, sublicense,
;* and/or sell copies of the Software, and to permit persons to whom the
;* Software is furnished to do so, subject to the following conditions:
;*
;* The above copyright notice and this permission notice shall be included
;* in all copies or substantial portions of the Software.
;*
;* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
;* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
;* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
;* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
;* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
;* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
;* OTHER DEALINGS IN THE SOFTWARE.
;*
;* Except as contained in this notice, the name of Maxim Integrated
;* Products, Inc. shall not be used except as stated in the Maxim Integrated
;* Products, Inc. Branding Policy.
;*
;* The mere transfer of this software does not imply any licenses
;* of trade secrets, proprietary technology, copyrights, patents,
;* trademarks, maskwork rights, or any other form of intellectual
;* property whatsoever. Maxim Integrated Products, Inc. retains all
;* ownership rights.
;*
;* Description        : MAX32660 device vector table for IAR EWARM toolchain.
;*                      - Sets the initial SP
;*                      - Sets the initial PC == _iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR
;*                        address, all set as PUBWEAK. User may override any ISR
;*                        defined as PUBWEAK.
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M4 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************
    MODULE  ?cstartup

    ;; Forward declaration of sections.
    SECTION CSTACK:DATA:NOROOT(3)

    SECTION .intvec:CODE:NOROOT(2)

    EXTERN  __iar_program_start
    ; EXTERN  SystemInit
    PUBLIC  __vector_table
    PUBLIC  __isr_vector
    PUBLIC  __vector_table_modify
    PUBLIC  __Vectors
    PUBLIC  __Vectors_End
    PUBLIC  __Vectors_Size

    DATA
__vector_table
__isr_vector
    DCD     sfe(CSTACK)
    DCD     Reset_Handler               ; Reset Handler

    DCD     NMI_Handler                 ; NMI Handler
    DCD     HardFault_Handler           ; Hard Fault Handler
    DCD     MemManage_Handler           ; MPU Fault Handler
    DCD     BusFault_Handler            ; Bus Fault Handler
    DCD     UsageFault_Handler          ; Usage Fault Handler
__vector_table_modify
    DCD     0                           ; Reserved
    DCD     0                           ; Reserved
    DCD     0                           ; Reserved
    DCD     0                           ; Reserved
    DCD     SVC_Handler                 ; SVCall Handler
    DCD     DebugMon_Handler            ; Debug Monitor Handler
    DCD     0                           ; Reserved
    DCD     PendSV_Handler              ; PendSV Handler
    DCD     SysTick_Handler             ; SysTick Handler

    ; MAX32660 Device-specific Interrupts
    DCD     PF_IRQHandler               ; /* 0x10  0x0040  16: Power Fail */
    DCD     WDT0_IRQHandler             ; /* 0x11  0x0044  17: Watchdog 0 */
    DCD     RSV00_IRQHandler            ; /* 0x12  0x0048  18: RSV00 */
    DCD     RTC_IRQHandler              ; /* 0x13  0x004C  19: RTC */
    DCD     RSV1_IRQHandler             ; /* 0x14  0x0050  20: RSV1 */
    DCD     TMR0_IRQHandler             ; /* 0x15  0x0054  21: Timer 0 */
    DCD     TMR1_IRQHandler             ; /* 0x16  0x0058  22: Timer 1 */
    DCD     TMR2_IRQHandler             ; /* 0x17  0x005C  23: Timer 2 */
    DCD     RSV02_IRQHandler            ; /* 0x18  0x0060  24: RSV02 */
    DCD     RSV03_IRQHandler            ; /* 0x19  0x0064  25: RSV03 */
    DCD     RSV04_IRQHandler            ; /* 0x1A  0x0068  26: RSV04 */
    DCD     RSV05_IRQHandler            ; /* 0x1B  0x006C  27: RSV05 */
    DCD     RSV06_IRQHandler            ; /* 0x1C  0x0070  28: RSV06 */
    DCD     I2C0_IRQHandler             ; /* 0x1D  0x0074  29: I2C0 */
    DCD     UART0_IRQHandler            ; /* 0x1E  0x0078  30: UART 0 */
    DCD     UART1_IRQHandler            ; /* 0x1F  0x007C  31: UART 1 */
    DCD     SPI0_IRQHandler             ; /* 0x20  0x0080  32: SPI0 */
    DCD     SPI1_IRQHandler             ; /* 0x21  0x0084  33: SPI1 */
    DCD     RSV07_IRQHandler            ; /* 0x22  0x0088  34: RSV07 */
    DCD     RSV08_IRQHandler            ; /* 0x23  0x008C  35: RSV08 */
    DCD     RSV09_IRQHandler            ; /* 0x24  0x0090  36: RSV09 */
    DCD     RSV10_IRQHandler            ; /* 0x25  0x0094  37: RSV10 */
    DCD     RSV11_IRQHandler            ; /* 0x26  0x0098  38: RSV11 */
    DCD     FLC_IRQHandler              ; /* 0x27  0x009C  39: FLC */
    DCD     GPIO0_IRQHandler            ; /* 0x28  0x00A0  40: GPIO0 */
    DCD     RSV12_IRQHandler            ; /* 0x29  0x00A4  41: RSV12 */
    DCD     RSV13_IRQHandler            ; /* 0x2A  0x00A8  42: RSV13 */
    DCD     RSV14_IRQHandler            ; /* 0x2B  0x00AC  43: RSV14 */
    DCD     DMA0_IRQHandler             ; /* 0x2C  0x00B0  44: DMA0 */
    DCD     DMA1_IRQHandler             ; /* 0x2D  0x00B4  45: DMA1 */
    DCD     DMA2_IRQHandler             ; /* 0x2E  0x00B8  46: DMA2 */
    DCD     DMA3_IRQHandler             ; /* 0x2F  0x00BC  47: DMA3 */
    DCD     RSV15_IRQHandler            ; /* 0x30  0x00C0  48: RSV15 */
    DCD     RSV16_IRQHandler            ; /* 0x31  0x00C4  49: RSV16 */
    DCD     RSV17_IRQHandler            ; /* 0x32  0x00C8  50: RSV17 */
    DCD     RSV18_IRQHandler            ; /* 0x33  0x00CC  51: RSV18 */
    DCD     I2C1_IRQHandler             ; /* 0x34  0x00D0  52: I2C1 */
    DCD     RSV19_IRQHandler            ; /* 0x35  0x00D4  53: RSV19 */
    DCD     RSV20_IRQHandler            ; /* 0x36  0x00D8  54: RSV20 */
    DCD     RSV21_IRQHandler            ; /* 0x37  0x00DC  55: RSV21 */
    DCD     RSV22_IRQHandler            ; /* 0x38  0x00E0  56: RSV22 */
    DCD     RSV23_IRQHandler            ; /* 0x39  0x00E4  57: RSV23 */
    DCD     RSV24_IRQHandler            ; /* 0x3A  0x00E8  58: RSV24 */
    DCD     RSV25_IRQHandler            ; /* 0x3B  0x00EC  59: RSV25 */
    DCD     RSV26_IRQHandler            ; /* 0x3C  0x00F0  60: RSV26 */
    DCD     RSV27_IRQHandler            ; /* 0x3D  0x00F4  61: RSV27 */
    DCD     RSV28_IRQHandler            ; /* 0x3E  0x00F8  62: RSV28 */
    DCD     RSV29_IRQHandler            ; /* 0x3F  0x00FC  63: RSV29 */
    DCD     RSV30_IRQHandler            ; /* 0x40  0x0100  64: RSV30 */
    DCD     RSV31_IRQHandler            ; /* 0x41  0x0104  65: RSV31 */
    DCD     RSV32_IRQHandler            ; /* 0x42  0x0108  66: RSV32 */
    DCD     RSV33_IRQHandler            ; /* 0x43  0x010C  67: RSV33 */
    DCD     RSV34_IRQHandler            ; /* 0x44  0x0110  68: RSV34 */
    DCD     RSV35_IRQHandler            ; /* 0x45  0x0114  69: RSV35 */
    DCD     GPIOWAKE_IRQHandler         ; /* 0x46  0x0118  70: GPIO Wakeup */
    ; Continue this pattern when vectors are eventually assigned by hardware

__Vectors_End
__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors



    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
    THUMB
    PUBWEAK Reset_Handler
    SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        ; IAR: PreInit is called from low_level_init.c
        ; IAR: SystemInit is called from cmain.s
        LDR        R0, =__iar_program_start
        BX         R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

; SysTick Handler is defined in mxc_delay.c
;         PUBWEAK SysTick_Handler
;         SECTION .text:CODE:REORDER:NOROOT(1)
; SysTick_Handler
;         B SysTick_Handler

        PUBWEAK PF_IRQHandler             ; /* 0x10  0x0040  16: Power Fail */
        SECTION .text:CODE:REORDER:NOROOT(1)
PF_IRQHandler
        B PF_IRQHandler

        PUBWEAK WDT0_IRQHandler           ; /* 0x11  0x0044  17: Watchdog 0 */
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT0_IRQHandler
        B WDT0_IRQHandler

        PUBWEAK RSV00_IRQHandler          ; /* 0x12  0x0048  18: RSV00 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV00_IRQHandler
        B RSV00_IRQHandler

        PUBWEAK RTC_IRQHandler            ; /* 0x13  0x004C  19: RTC */
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK RSV1_IRQHandler           ; /* 0x14  0x0050  20: RSV1 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV1_IRQHandler
        B RSV1_IRQHandler

        PUBWEAK TMR0_IRQHandler           ; /* 0x15  0x0054  21: Timer 0 */
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR0_IRQHandler
        B TMR0_IRQHandler

        PUBWEAK TMR1_IRQHandler           ; /* 0x16  0x0058  22: Timer 1 */
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_IRQHandler
        B TMR1_IRQHandler

        PUBWEAK TMR2_IRQHandler           ; /* 0x17  0x005C  23: Timer 2 */
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR2_IRQHandler
        B TMR2_IRQHandler

        PUBWEAK RSV02_IRQHandler          ; /* 0x18  0x0060  24: RSV02 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV02_IRQHandler
        B RSV02_IRQHandler

        PUBWEAK RSV03_IRQHandler          ; /* 0x19  0x0064  25: RSV03 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV03_IRQHandler
        B RSV03_IRQHandler

        PUBWEAK RSV04_IRQHandler          ; /* 0x1A  0x0068  26: RSV04 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV04_IRQHandler
        B RSV04_IRQHandler

        PUBWEAK RSV05_IRQHandler          ; /* 0x1B  0x006C  27: RSV05 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV05_IRQHandler
        B RSV05_IRQHandler

        PUBWEAK RSV06_IRQHandler          ; /* 0x1C  0x0070  28: RSV06 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV06_IRQHandler
        B RSV06_IRQHandler

        PUBWEAK I2C0_IRQHandler           ; /* 0x1D  0x0074  29: I2C0 */
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C0_IRQHandler
        B I2C0_IRQHandler

        PUBWEAK UART0_IRQHandler          ; /* 0x1E  0x0078  30: UART 0 */
        SECTION .text:CODE:REORDER:NOROOT(1)
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK UART1_IRQHandler          ; /* 0x1F  0x007C  31: UART 1 */
        SECTION .text:CODE:REORDER:NOROOT(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK SPI0_IRQHandler           ; /* 0x20  0x0080  32: SPI0 */
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK SPI1_IRQHandler           ; /* 0x21  0x0084  33: SPI1 */
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK RSV07_IRQHandler          ; /* 0x22  0x0088  34: RSV07 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV07_IRQHandler
        B RSV07_IRQHandler

        PUBWEAK RSV08_IRQHandler          ; /* 0x23  0x008C  35: RSV08 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV08_IRQHandler
        B RSV08_IRQHandler

        PUBWEAK RSV09_IRQHandler          ; /* 0x24  0x0090  36: RSV09 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV09_IRQHandler
        B RSV09_IRQHandler

        PUBWEAK RSV10_IRQHandler          ; /* 0x25  0x0094  37: RSV10 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV10_IRQHandler
        B RSV10_IRQHandler

        PUBWEAK RSV11_IRQHandler          ; /* 0x26  0x0098  38: RSV11 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV11_IRQHandler
        B RSV11_IRQHandler

        PUBWEAK FLC_IRQHandler            ; /* 0x27  0x009C  39: FLC */
        SECTION .text:CODE:REORDER:NOROOT(1)
FLC_IRQHandler
        B FLC_IRQHandler

        PUBWEAK GPIO0_IRQHandler          ; /* 0x28  0x00A0  40: GPIO0 */
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO0_IRQHandler
        B GPIO0_IRQHandler

        PUBWEAK RSV12_IRQHandler          ; /* 0x29  0x00A4  41: RSV12 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV12_IRQHandler
        B RSV12_IRQHandler

        PUBWEAK RSV13_IRQHandler          ; /* 0x2A  0x00A8  42: RSV13 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV13_IRQHandler
        B RSV13_IRQHandler

        PUBWEAK RSV14_IRQHandler          ; /* 0x2B  0x00AC  43: RSV14 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV14_IRQHandler
        B RSV14_IRQHandler

        PUBWEAK DMA0_IRQHandler           ; /* 0x2C  0x00B0  44: DMA0 */
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA0_IRQHandler
        B DMA0_IRQHandler

        PUBWEAK DMA1_IRQHandler           ; /* 0x2D  0x00B4  45: DMA1 */
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_IRQHandler
        B DMA1_IRQHandler

        PUBWEAK DMA2_IRQHandler           ; /* 0x2E  0x00B8  46: DMA2 */
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_IRQHandler
        B DMA2_IRQHandler

        PUBWEAK DMA3_IRQHandler           ; /* 0x2F  0x00BC  47: DMA3 */
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_IRQHandler
        B DMA3_IRQHandler

        PUBWEAK RSV15_IRQHandler          ; /* 0x30  0x00C0  48: RSV15 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV15_IRQHandler
        B RSV15_IRQHandler

        PUBWEAK RSV16_IRQHandler          ; /* 0x31  0x00C4  49: RSV16 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV16_IRQHandler
        B RSV16_IRQHandler

        PUBWEAK RSV17_IRQHandler          ; /* 0x32  0x00C8  50: RSV17 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV17_IRQHandler
        B RSV17_IRQHandler

        PUBWEAK RSV18_IRQHandler          ; /* 0x33  0x00CC  51: RSV18 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV18_IRQHandler
        B RSV18_IRQHandler

        PUBWEAK I2C1_IRQHandler           ; /* 0x34  0x00D0  52: I2C1 */
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK RSV19_IRQHandler          ; /* 0x35  0x00D4  53: RSV19 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV19_IRQHandler
        B RSV19_IRQHandler

        PUBWEAK RSV20_IRQHandler          ; /* 0x36  0x00D8  54: RSV20 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV20_IRQHandler
        B RSV20_IRQHandler

        PUBWEAK RSV21_IRQHandler          ; /* 0x37  0x00DC  55: RSV21 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV21_IRQHandler
        B RSV21_IRQHandler

        PUBWEAK RSV22_IRQHandler          ; /* 0x38  0x00E0  56: RSV22 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV22_IRQHandler
        B RSV22_IRQHandler

        PUBWEAK RSV23_IRQHandler          ; /* 0x39  0x00E4  57: RSV23 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV23_IRQHandler
        B RSV23_IRQHandler

        PUBWEAK RSV24_IRQHandler          ; /* 0x3A  0x00E8  58: RSV24 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV24_IRQHandler
        B RSV24_IRQHandler

        PUBWEAK RSV25_IRQHandler          ; /* 0x3B  0x00EC  59: RSV25 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV25_IRQHandler
        B RSV25_IRQHandler

        PUBWEAK RSV26_IRQHandler          ; /* 0x3C  0x00F0  60: RSV26 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV26_IRQHandler
        B RSV26_IRQHandler

        PUBWEAK RSV27_IRQHandler          ; /* 0x3D  0x00F4  61: RSV27 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV27_IRQHandler
        B RSV27_IRQHandler

        PUBWEAK RSV28_IRQHandler          ; /* 0x3E  0x00F8  62: RSV28 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV28_IRQHandler
        B RSV28_IRQHandler

        PUBWEAK RSV29_IRQHandler          ; /* 0x3F  0x00FC  63: RSV29 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV29_IRQHandler
        B RSV29_IRQHandler

        PUBWEAK RSV30_IRQHandler          ; /* 0x40  0x0100  64: RSV30 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV30_IRQHandler
        B RSV30_IRQHandler

        PUBWEAK RSV31_IRQHandler          ; /* 0x41  0x0104  65: RSV31 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV31_IRQHandler
        B RSV31_IRQHandler

        PUBWEAK RSV32_IRQHandler          ; /* 0x42  0x0108  66: RSV32 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV32_IRQHandler
        B RSV32_IRQHandler

        PUBWEAK RSV33_IRQHandler          ; /* 0x43  0x010C  67: RSV33 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV33_IRQHandler
        B RSV33_IRQHandler

        PUBWEAK RSV34_IRQHandler          ; /* 0x44  0x0110  68: RSV34 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV34_IRQHandler
        B RSV34_IRQHandler

        PUBWEAK RSV35_IRQHandler          ; /* 0x45  0x0114  69: RSV35 */
        SECTION .text:CODE:REORDER:NOROOT(1)
RSV35_IRQHandler
        B RSV35_IRQHandler

        PUBWEAK GPIOWAKE_IRQHandler       ; /* 0x46  0x0118  70: GPIO Wakeup */
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOWAKE_IRQHandler
        B GPIOWAKE_IRQHandler


        END
