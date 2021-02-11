;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ; Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 ;
 ; Permission is hereby granted, free of charge, to any person obtaining a
 ; copy of this software and associated documentation files (the "Software"),
 ; to deal in the Software without restriction, including without limitation
 ; the rights to use, copy, modify, merge, publish, distribute, sublicense,
 ; and/or sell copies of the Software, and to permit persons to whom the
 ; Software is furnished to do so, subject to the following conditions:
 ;
 ; The above copyright notice and this permission notice shall be included
 ; in all copies or substantial portions of the Software.
 ;
 ; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 ; OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 ; MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 ; IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 ; OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ; ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 ; OTHER DEALINGS IN THE SOFTWARE.
 ;
 ; Except as contained in this notice, the name of Maxim Integrated
 ; Products, Inc. shall not be used except as stated in the Maxim Integrated
 ; Products, Inc. Branding Policy.
 ;
 ; The mere transfer of this software does not imply any licenses
 ; of trade secrets, proprietary technology, copyrights, patents,
 ; trademarks, maskwork rights, or any other form of intellectual
 ; property whatsoever. Maxim Integrated Products, Inc. retains all
 ; ownership rights.
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; To map FreeRTOS function names to their CMSIS equivalents add following lines to FreeRTOSConfig.h
; #define vPortSVCHandler SVC_Handler
; #define xPortPendSVHandler PendSV_Handler
; #define xPortSysTickHandler SysTick_Handler
; *------- <<< Use Configuration Wizard in Context Menu to Modify Stack Size and Heap Size. >>> ----

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp    ; Name used with Keil Configuration Wizard and Keil MicroLib

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000C00

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
                EXPORT  __isr_vector
                IMPORT  SysTick_Handler

__isr_vector    DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; Device-specific Interrupts
                DCD     PF_IRQHandler             ; 0x10  0x0040  16: Power Fail
                DCD     WDT0_IRQHandler           ; 0x11  0x0044  17: Watchdog 0
                DCD     RSV00_IRQHandler          ; 0x12  0x0048  18: RSV00
                DCD     RTC_IRQHandler            ; 0x13  0x004C  19: RTC
                DCD     RSV01_IRQHandler          ; 0x14  0x0050  20: RSV1
                DCD     TMR0_IRQHandler           ; 0x15  0x0054  21: Timer 0
                DCD     TMR1_IRQHandler           ; 0x16  0x0058  22: Timer 1
                DCD     TMR2_IRQHandler           ; 0x17  0x005C  23: Timer 2
                DCD     RSV02_IRQHandler          ; 0x18  0x0060  24: RSV02
                DCD     RSV03_IRQHandler          ; 0x19  0x0064  25: RSV03
                DCD     RSV04_IRQHandler          ; 0x1A  0x0068  26: RSV04
                DCD     RSV05_IRQHandler          ; 0x1B  0x006C  27: RSV05
                DCD     RSV06_IRQHandler          ; 0x1C  0x0070  28: RSV06
                DCD     I2C0_IRQHandler           ; 0x1D  0x0074  29: I2C0
                DCD     UART0_IRQHandler          ; 0x1E  0x0078  30: UART 0
                DCD     UART1_IRQHandler          ; 0x1F  0x007C  31: UART 1
                DCD     SPI0_IRQHandler           ; 0x20  0x0080  32: SPIY17
                DCD     SPI1_IRQHandler           ; 0x21  0x0084  33: SPIMSS
                DCD     RSV07_IRQHandler          ; 0x22  0x0088  34: RSV07
                DCD     RSV08_IRQHandler          ; 0x23  0x008C  35: RSV08
                DCD     RSV09_IRQHandler          ; 0x24  0x0090  36: RSV09
                DCD     RSV10_IRQHandler          ; 0x25  0x0094  37: RSV10
                DCD     RSV11_IRQHandler          ; 0x26  0x0098  38: RSV11
                DCD     FLC_IRQHandler            ; 0x27  0x009C  39: FLC
                DCD     GPIO0_IRQHandler          ; 0x28  0x00A0  40: GPIO0
                DCD     RSV12_IRQHandler          ; 0x29  0x00A4  41: RSV12
                DCD     RSV13_IRQHandler          ; 0x2A  0x00A8  42: RSV13
                DCD     RSV14_IRQHandler          ; 0x2B  0x00AC  43: RSV14
                DCD     DMA0_IRQHandler           ; 0x2C  0x00B0  44: DMA0
                DCD     DMA1_IRQHandler           ; 0x2D  0x00B4  45: DMA1
                DCD     DMA2_IRQHandler           ; 0x2E  0x00B8  46: DMA2
                DCD     DMA3_IRQHandler           ; 0x2F  0x00BC  47: DMA3
                DCD     RSV15_IRQHandler          ; 0x30  0x00C0  48: RSV15
                DCD     RSV16_IRQHandler          ; 0x31  0x00C4  49: RSV16
                DCD     RSV17_IRQHandler          ; 0x32  0x00C8  50: RSV17
                DCD     RSV18_IRQHandler          ; 0x33  0x00CC  51: RSV18
                DCD     I2C1_IRQHandler           ; 0x34  0x00D0  52: I2C1
                DCD     RSV19_IRQHandler          ; 0x35  0x00D4  53: RSV19
                DCD     RSV20_IRQHandler          ; 0x36  0x00D8  54: RSV20
                DCD     RSV21_IRQHandler          ; 0x37  0x00DC  55: RSV21
                DCD     RSV22_IRQHandler          ; 0x38  0x00E0  56: RSV22
                DCD     RSV23_IRQHandler          ; 0x39  0x00E4  57: RSV23
                DCD     RSV24_IRQHandler          ; 0x3A  0x00E8  58: RSV24
                DCD     RSV25_IRQHandler          ; 0x3B  0x00EC  59: RSV25
                DCD     RSV26_IRQHandler          ; 0x3C  0x00F0  60: RSV26
                DCD     RSV27_IRQHandler          ; 0x3D  0x00F4  61: RSV27
                DCD     RSV28_IRQHandler          ; 0x3E  0x00F8  62: RSV28
                DCD     RSV29_IRQHandler          ; 0x3F  0x00FC  63: RSV29
                DCD     RSV30_IRQHandler          ; 0x40  0x0100  64: RSV30
                DCD     RSV31_IRQHandler          ; 0x41  0x0104  65: RSV31
                DCD     RSV32_IRQHandler          ; 0x42  0x0108  66: RSV32
                DCD     RSV33_IRQHandler          ; 0x43  0x010C  67: RSV33
                DCD     RSV34_IRQHandler          ; 0x44  0x0110  68: RSV34
                DCD     RSV35_IRQHandler          ; 0x45  0x0114  69: RSV35
                DCD     GPIOWAKE_IRQHandler       ; 0x46  0x0118  70: GPIO Wakeup
__isr_vector_end

__isr_vector_size       EQU  __isr_vector_end - __isr_vector
__Vectors       EQU     __isr_vector
__Vectors_End   EQU     __isr_vector_end
__Vectors_Size  EQU     __isr_vector_size

                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT Reset_Handler                    [WEAK]
                IMPORT PreInit
                ;IMPORT SystemInit
                IMPORT __main
                LDR     R0, =PreInit            ; Call to PreInit (prior to RAM initialization)
                BLX     R0
                LDR     R0, =__main             ; SystemInit() is called from post scatter memory initialization in function  $Sub$$__main_after_scatterload - system_max32660.c
                BX      R0
__SPIN
                WFI
                BL __SPIN
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler\
                PROC
                EXPORT  NMI_Handler             [WEAK]
                B       .
                ENDP

HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler       [WEAK]
                B       .
                ENDP

MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler       [WEAK]
                B       .
                ENDP

BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler        [WEAK]
                B       .
                ENDP

UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler      [WEAK]
                B       .
                ENDP

SVC_Handler\
                PROC
                EXPORT  SVC_Handler             [WEAK]
                B       .
                ENDP

DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler        [WEAK]
                B       .
                ENDP

PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler          [WEAK]
                B       .
                ENDP
Default_Handler\
                PROC
                ; MAX32660 Device-specific Interrupts
                EXPORT PF_IRQHandler            [WEAK] ;  0x10  0x0040  16: Power Fail
                EXPORT WDT0_IRQHandler          [WEAK] ;  0x11  0x0044  17: Watchdog 0
                EXPORT RSV00_IRQHandler         [WEAK] ;  0x12  0x0048  18: RSV00
                EXPORT RTC_IRQHandler           [WEAK] ;  0x13  0x004C  19: RTC
                EXPORT RSV01_IRQHandler         [WEAK] ;  0x14  0x0050  20: RSV01
                EXPORT TMR0_IRQHandler          [WEAK] ;  0x15  0x0054  21: Timer 0
                EXPORT TMR1_IRQHandler          [WEAK] ;  0x16  0x0058  22: Timer 1
                EXPORT TMR2_IRQHandler          [WEAK] ;  0x17  0x005C  23: Timer 2
                EXPORT RSV02_IRQHandler         [WEAK] ;  0x18  0x0060  24: RSV02
                EXPORT RSV03_IRQHandler         [WEAK] ;  0x19  0x0064  25: RSV03
                EXPORT RSV04_IRQHandler         [WEAK] ;  0x1A  0x0068  26: RSV04
                EXPORT RSV05_IRQHandler         [WEAK] ;  0x1B  0x006C  27: RSV05
                EXPORT RSV06_IRQHandler         [WEAK] ;  0x1C  0x0070  28: RSV06
                EXPORT I2C0_IRQHandler          [WEAK] ;  0x1D  0x0074  29: I2C0
                EXPORT UART0_IRQHandler         [WEAK] ;  0x1E  0x0078  30: UART 0
                EXPORT UART1_IRQHandler         [WEAK] ;  0x1F  0x007C  31: UART 1
                EXPORT SPI0_IRQHandler          [WEAK] ;  0x20  0x0080  32: SPIY17
                EXPORT SPI1_IRQHandler          [WEAK] ;  0x21  0x0084  33: SPIMSS
                EXPORT RSV07_IRQHandler         [WEAK] ;  0x22  0x0088  34: RSV07
                EXPORT RSV08_IRQHandler         [WEAK] ;  0x23  0x008C  35: RSV08
                EXPORT RSV09_IRQHandler         [WEAK] ;  0x24  0x0090  36: RSV09
                EXPORT RSV10_IRQHandler         [WEAK] ;  0x25  0x0094  37: RSV10
                EXPORT RSV11_IRQHandler         [WEAK] ;  0x26  0x0098  38: RSV11
                EXPORT FLC_IRQHandler           [WEAK] ;  0x27  0x009C  39: FLC
                EXPORT GPIO0_IRQHandler         [WEAK] ;  0x28  0x00A0  40: GPIO0
                EXPORT RSV12_IRQHandler         [WEAK] ;  0x29  0x00A4  41: RSV12
                EXPORT RSV13_IRQHandler         [WEAK] ;  0x2A  0x00A8  42: RSV13
                EXPORT RSV14_IRQHandler         [WEAK] ;  0x2B  0x00AC  43: RSV14
                EXPORT DMA0_IRQHandler          [WEAK] ;  0x2C  0x00B0  44: DMA0
                EXPORT DMA1_IRQHandler          [WEAK] ;  0x2D  0x00B4  45: DMA1
                EXPORT DMA2_IRQHandler          [WEAK] ;  0x2E  0x00B8  46: DMA2
                EXPORT DMA3_IRQHandler          [WEAK] ;  0x2F  0x00BC  47: DMA3
                EXPORT RSV15_IRQHandler         [WEAK] ;  0x30  0x00C0  48: RSV15
                EXPORT RSV16_IRQHandler         [WEAK] ;  0x31  0x00C4  49: RSV16
                EXPORT RSV17_IRQHandler         [WEAK] ;  0x32  0x00C8  50: RSV17
                EXPORT RSV18_IRQHandler         [WEAK] ;  0x33  0x00CC  51: RSV18
                EXPORT I2C1_IRQHandler          [WEAK] ;  0x34  0x00D0  52: I2C1
                EXPORT RSV19_IRQHandler         [WEAK] ;  0x35  0x00D4  53: RSV19
                EXPORT RSV20_IRQHandler         [WEAK] ;  0x36  0x00D8  54: RSV20
                EXPORT RSV21_IRQHandler         [WEAK] ;  0x37  0x00DC  55: RSV21
                EXPORT RSV22_IRQHandler         [WEAK] ;  0x38  0x00E0  56: RSV22
                EXPORT RSV23_IRQHandler         [WEAK] ;  0x39  0x00E4  57: RSV23
                EXPORT RSV24_IRQHandler         [WEAK] ;  0x3A  0x00E8  58: RSV24
                EXPORT RSV25_IRQHandler         [WEAK] ;  0x3B  0x00EC  59: RSV25
                EXPORT RSV26_IRQHandler         [WEAK] ;  0x3C  0x00F0  60: RSV26
                EXPORT RSV27_IRQHandler         [WEAK] ;  0x3D  0x00F4  61: RSV27
                EXPORT RSV28_IRQHandler         [WEAK] ;  0x3E  0x00F8  62: RSV28
                EXPORT RSV29_IRQHandler         [WEAK] ;  0x3F  0x00FC  63: RSV29
                EXPORT RSV30_IRQHandler         [WEAK] ;  0x40  0x0100  64: RSV30
                EXPORT RSV31_IRQHandler         [WEAK] ;  0x41  0x0104  65: RSV31
                EXPORT RSV32_IRQHandler         [WEAK] ;  0x42  0x0108  66: RSV32
                EXPORT RSV33_IRQHandler         [WEAK] ;  0x43  0x010C  67: RSV33
                EXPORT RSV34_IRQHandler         [WEAK] ;  0x44  0x0110  68: RSV34
                EXPORT RSV35_IRQHandler         [WEAK] ;  0x45  0x0114  69: RSV35
                EXPORT GPIOWAKE_IRQHandler      [WEAK] ;  0x46  0x0118  70: GPIO Wakeup

;*******************************************************************************
; Default handler implementations
;*******************************************************************************
PF_IRQHandler                                   ;  0x10  0x0040  16: Power Fail
WDT0_IRQHandler                                 ;  0x11  0x0044  17: Watchdog 0
RSV00_IRQHandler                                ;  0x12  0x0048  18: RSV00
RTC_IRQHandler                                  ;  0x13  0x004C  19: RTC
RSV01_IRQHandler                                ;  0x14  0x0050  20: RSV01
TMR0_IRQHandler                                 ;  0x15  0x0054  21: Timer 0
TMR1_IRQHandler                                 ;  0x16  0x0058  22: Timer 1
TMR2_IRQHandler                                 ;  0x17  0x005C  23: Timer 2
RSV02_IRQHandler                                ;  0x18  0x0060  24: RSV02
RSV03_IRQHandler                                ;  0x19  0x0064  25: RSV03
RSV04_IRQHandler                                ;  0x1A  0x0068  26: RSV04
RSV05_IRQHandler                                ;  0x1B  0x006C  27: RSV05
RSV06_IRQHandler                                ;  0x1C  0x0070  28: RSV06
I2C0_IRQHandler                                 ;  0x1D  0x0074  29: I2C0
UART0_IRQHandler                                ;  0x1E  0x0078  30: UART 0
UART1_IRQHandler                                ;  0x1F  0x007C  31: UART 1
SPI0_IRQHandler                                 ;  0x20  0x0080  32: SPI0
SPI1_IRQHandler                                 ;  0x21  0x0084  33: SPI1
RSV07_IRQHandler                                ;  0x22  0x0088  34: RSV07
RSV08_IRQHandler                                ;  0x23  0x008C  35: RSV08
RSV09_IRQHandler                                ;  0x24  0x0090  36: RSV09
RSV10_IRQHandler                                ;  0x25  0x0094  37: RSV10
RSV11_IRQHandler                                ;  0x26  0x0098  38: RSV11
FLC_IRQHandler                                  ;  0x27  0x009C  39: FLC
GPIO0_IRQHandler                                ;  0x28  0x00A0  40: GPIO0
RSV12_IRQHandler                                ;  0x29  0x00A4  41: RSV12
RSV13_IRQHandler                                ;  0x2A  0x00A8  42: RSV13
RSV14_IRQHandler                                ;  0x2B  0x00AC  43: RSV14
DMA0_IRQHandler                                 ;  0x2C  0x00B0  44: DMA0
DMA1_IRQHandler                                 ;  0x2D  0x00B4  45: DMA1
DMA2_IRQHandler                                 ;  0x2E  0x00B8  46: DMA2
DMA3_IRQHandler                                 ;  0x2F  0x00BC  47: DMA3
RSV15_IRQHandler                                ;  0x30  0x00C0  48: RSV15
RSV16_IRQHandler                                ;  0x31  0x00C4  49: RSV16
RSV17_IRQHandler                                ;  0x32  0x00C8  50: RSV17
RSV18_IRQHandler                                ;  0x33  0x00CC  51: RSV18
I2C1_IRQHandler                                 ;  0x34  0x00D0  52: I2C1
RSV19_IRQHandler                                ;  0x35  0x00D4  53: RSV19
RSV20_IRQHandler                                ;  0x36  0x00D8  54: RSV20
RSV21_IRQHandler                                ;  0x37  0x00DC  55: RSV21
RSV22_IRQHandler                                ;  0x38  0x00E0  56: RSV22
RSV23_IRQHandler                                ;  0x39  0x00E4  57: RSV23
RSV24_IRQHandler                                ;  0x3A  0x00E8  58: RSV24
RSV25_IRQHandler                                ;  0x3B  0x00EC  59: RSV25
RSV26_IRQHandler                                ;  0x3C  0x00F0  60: RSV26
RSV27_IRQHandler                                ;  0x3D  0x00F4  61: RSV27
RSV28_IRQHandler                                ;  0x3E  0x00F8  62: RSV28
RSV29_IRQHandler                                ;  0x3F  0x00FC  63: RSV29
RSV30_IRQHandler                                ;  0x40  0x0100  64: RSV30
RSV31_IRQHandler                                ;  0x41  0x0104  65: RSV31
RSV32_IRQHandler                                ;  0x42  0x0108  66: RSV32
RSV33_IRQHandler                                ;  0x43  0x010C  67: RSV33
RSV34_IRQHandler                                ;  0x44  0x0110  68: RSV34
RSV35_IRQHandler                                ;  0x45  0x0114  69: RSV35
GPIOWAKE_IRQHandler                             ;  0x46  0x0118  70: GPIO Wakeup

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

__user_initial_stackheap\
                PROC

                LDR     R0, =  Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF

                END

;;;;;;;;;;;;;;;;;;;;;;;;;
;; End of file.
;;;;;;;;;;;;;;;;;;;;;;;;;
