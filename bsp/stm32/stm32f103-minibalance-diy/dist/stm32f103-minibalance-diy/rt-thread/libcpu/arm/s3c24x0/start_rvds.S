;/*****************************************************************************/
;/* S3C2440.S: Startup file for Samsung S3C440                                */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2008 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


;/*
; *  The S3C2440.S code is executed after CPU Reset. This file may be
; *  translated with the following SET symbols. In uVision these SET
; *  symbols are entered under Options - ASM - Define.
; *
; *  NO_CLOCK_SETUP: when set the startup code will not initialize Clock
; *  (used mostly when clock is already initialized from script .ini
; *  file).
; *
; *  NO_MC_SETUP: when set the startup code will not initialize Memory
; *  Controller (used mostly when clock is already initialized from script
; *  .ini file).
; *
; *  NO_GP_SETUP: when set the startup code will not initialize General Ports
; *  (used mostly when clock is already initialized from script .ini
; *  file).
; *
; *  RAM_INTVEC: when set the startup code copies exception vectors
; *  from execution address to on-chip RAM.
; */


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled


;----------------------- Stack and Heap Definitions ----------------------------

;// <h> Stack Configuration (Stack Sizes in Bytes)
;//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:8>
;//   <o1> Supervisor Mode     <0x0-0xFFFFFFFF:8>
;//   <o2> Abort Mode          <0x0-0xFFFFFFFF:8>
;//   <o3> Fast Interrupt Mode <0x0-0xFFFFFFFF:8>
;//   <o4> Interrupt Mode      <0x0-0xFFFFFFFF:8>
;//   <o5> User/System Mode    <0x0-0xFFFFFFFF:8>
;// </h>

UND_Stack_Size  EQU     0x00000000
SVC_Stack_Size  EQU     0x00000100
ABT_Stack_Size  EQU     0x00000000
FIQ_Stack_Size  EQU     0x00000000
IRQ_Stack_Size  EQU     0x00000100
USR_Stack_Size  EQU     0x00000100

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF>
;// </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


;----------------------- Memory Definitions ------------------------------------

; Internal Memory Base Addresses
IRAM_BASE       EQU     0x40000000


;----------------------- Watchdog Timer Definitions ----------------------------

WT_BASE         EQU     0x53000000      ; Watchdog Timer Base Address
WTCON_OFS       EQU     0x00            ; Watchdog Timer Control Register Offset
WTDAT_OFS       EQU     0x04            ; Watchdog Timer Data Register    Offset
WTCNT_OFS       EQU     0x08            ; Watchdog Timer Count Register   Offset

;// <e> Watchdog Timer Setup
;//   <h> Watchdog Timer Control Register (WTCON)
;//     <o1.8..15>  Prescaler Value <0-255>
;//     <o1.5>      Watchdog Timer Enable
;//     <o1.3..4>   Clock Division Factor
;//       <0=> 16   <1=> 32  <2=> 64  <3=> 128
;//     <o1.2>      Interrupt Generation Enable
;//     <o1.0>      Reset Enable
;//   </h>
;//   <h> Watchdog Timer Data Register (WTDAT)
;//     <o2.0..15>  Count Reload Value <0-65535>
;//   </h>
;// </e> Watchdog Timer Setup
WT_SETUP        EQU     1
WTCON_Val       EQU     0x00000000
WTDAT_Val       EQU     0x00008000


;----------------------- Clock and Power Management Definitions ----------------

CLOCK_BASE      EQU     0x4C000000      ; Clock Base Address
LOCKTIME_OFS    EQU     0x00            ; PLL Lock Time Count Register   Offset
MPLLCON_OFS     EQU     0x04            ; MPLL Configuration Register    Offset
UPLLCON_OFS     EQU     0x08            ; UPLL Configuration Register    Offset
CLKCON_OFS      EQU     0x0C            ; Clock Generator Control Reg    Offset
CLKSLOW_OFS     EQU     0x10            ; Clock Slow Control Register    Offset
CLKDIVN_OFS     EQU     0x14            ; Clock Divider Control Register Offset
CAMDIVN_OFS     EQU     0x18            ; Camera Clock Divider Register  Offset

;// <e> Clock Setup
;//   <h> PLL Lock Time Count Register (LOCKTIME)
;//     <o1.16..31> U_LTIME: UPLL Lock Time Count Value for UCLK <0x0-0xFFFF>
;//     <o1.0..15>  M_LTIME: MPLL Lock Time Count Value for FCLK, HCLK and PCLK <0x0-0xFFFF>
;//   </h>
;//   <h> MPLL Configuration Register (MPLLCON)
;//     <i> MPLL = (2 * m * Fin) / (p * 2^s)
;//     <o2.12..19> m: Main Divider m Value <9-256><#-8>
;//       <i> m = MDIV + 8
;//     <o2.4..9>   p: Pre-divider p Value <3-64><#-2>
;//       <i> p = PDIV + 2
;//     <o2.0..1>   s: Post Divider s Value <0-3>
;//       <i> s = SDIV
;//   </h>
;//   <h> UPLL Configuration Register (UPLLCON)
;//     <i> UPLL = ( m * Fin) / (p * 2^s)
;//     <o3.12..19> m: Main Divider m Value <8-263><#-8>
;//       <i> m = MDIV + 8
;//     <o3.4..9>   p: Pre-divider p Value <2-65><#-2>
;//       <i> p = PDIV + 2
;//     <o3.0..1>   s: Post Divider s Value <0-3>
;//       <i> s = SDIV
;//   </h>
;//   <h> Clock Generation Control Register (CLKCON)
;//     <o4.20>     AC97 Enable
;//     <o4.19>     Camera Enable
;//     <o4.18>     SPI Enable
;//     <o4.17>     IIS Enable
;//     <o4.16>     IIC Enable
;//     <o4.15>     ADC + Touch Screen Enable
;//     <o4.14>     RTC Enable
;//     <o4.13>     GPIO Enable
;//     <o4.12>     UART2 Enable
;//     <o4.11>     UART1 Enable
;//     <o4.10>     UART0 Enable
;//     <o4.9>      SDI Enable
;//     <o4.8>      PWMTIMER Enable
;//     <o4.7>      USB Device Enable
;//     <o4.6>      USB Host Enable
;//     <o4.5>      LCDC Enable
;//     <o4.4>      NAND FLASH Controller Enable
;//     <o4.3>      SLEEP Enable
;//     <o4.2>      IDLE BIT Enable
;//   </h>
;//   <h> Clock Slow Control Register (CLKSLOW)
;//     <o5.7>      UCLK_ON: UCLK ON
;//     <o5.5>      MPLL_OFF: Turn off PLL
;//     <o5.4>      SLOW_BIT: Slow Mode Enable
;//     <o5.0..2>   SLOW_VAL: Slow Clock Divider <0-7>
;//   </h>
;//   <h> Clock Divider Control Register (CLKDIVN)
;//     <o6.3>      DIVN_UPLL: UCLK Select
;//       <0=> UCLK = UPLL clock
;//       <1=> UCLK = UPLL clock / 2
;//     <o6.1..2>   HDIVN: HCLK Select
;//       <0=> HCLK = FCLK
;//       <1=> HCLK = FCLK / 2
;//       <2=> HCLK = FCLK / 4 if HCLK4_HALF = 0 in CAMDIVN, else HCLK = FCLK / 8
;//       <3=> HCLK = FCLK / 3 if HCLK3_HALF = 0 in CAMDIVN, else HCLK = FCLK / 6
;//     <o6.0>      PDIVN: PCLK Select
;//       <0=> PCLK = HCLK
;//       <1=> PCLK = HCLK / 2
;//   </h>
;//   <h> Camera Clock Divider Control Register (CAMDIVN)
;//     <o7.12>     DVS_EN: ARM Core Clock Select
;//       <0=> ARM core runs at FCLK
;//       <1=> ARM core runs at HCLK
;//     <o7.9>      HCLK4_HALF: HDIVN Division Rate Change Bit
;//       <0=> If HDIVN = 2 in CLKDIVN then HCLK = FCLK / 4
;//       <1=> If HDIVN = 2 in CLKDIVN then HCLK = FCLK / 8
;//     <o7.8>      HCLK3_HALF: HDIVN Division Rate Change Bit
;//       <0=> If HDIVN = 3 in CLKDIVN then HCLK = FCLK / 3
;//       <1=> If HDIVN = 3 in CLKDIVN then HCLK = FCLK / 6
;//     <o7.4>      CAMCLK Select
;//       <0=> CAMCLK = UPLL
;//       <1=> CAMCLK = UPLL / CAMCLK_DIV
;//     <o7.0..3>   CAMCLK_DIV: CAMCLK Divider <0-15>
;//       <i> Camera Clock = UPLL / (2 * (CAMCLK_DIV + 1))
;//       <i> Divider is used only if CAMCLK_SEL = 1
;//   </h>
;// </e> Clock Setup
CLOCK_SETUP     EQU     0
LOCKTIME_Val    EQU     0x0FFF0FFF
MPLLCON_Val     EQU     0x00043011
UPLLCON_Val     EQU     0x00038021
CLKCON_Val      EQU     0x001FFFF0
CLKSLOW_Val     EQU     0x00000004
CLKDIVN_Val     EQU     0x0000000F
CAMDIVN_Val     EQU     0x00000000


;----------------------- Memory Controller Definitions -------------------------

MC_BASE         EQU     0x48000000      ; Memory Controller Base Address
BWSCON_OFS      EQU     0x00            ; Bus Width and Wait Status Ctrl Offset
BANKCON0_OFS    EQU     0x04            ; Bank 0 Control Register        Offset
BANKCON1_OFS    EQU     0x08            ; Bank 1 Control Register        Offset
BANKCON2_OFS    EQU     0x0C            ; Bank 2 Control Register        Offset
BANKCON3_OFS    EQU     0x10            ; Bank 3 Control Register        Offset
BANKCON4_OFS    EQU     0x14            ; Bank 4 Control Register        Offset
BANKCON5_OFS    EQU     0x18            ; Bank 5 Control Register        Offset
BANKCON6_OFS    EQU     0x1C            ; Bank 6 Control Register        Offset
BANKCON7_OFS    EQU     0x20            ; Bank 7 Control Register        Offset
REFRESH_OFS     EQU     0x24            ; SDRAM Refresh Control Register Offset
BANKSIZE_OFS    EQU     0x28            ; Flexible Bank Size Register    Offset
MRSRB6_OFS      EQU     0x2C            ; Bank 6 Mode Register           Offset
MRSRB7_OFS      EQU     0x30            ; Bank 7 Mode Register           Offset

;// <e> Memory Controller Setup
;//   <h> Bus Width and Wait Control Register (BWSCON)
;//     <o1.31>     ST7: Use UB/LB for Bank 7
;//     <o1.30>     WS7: Enable Wait Status for Bank 7
;//     <o1.28..29> DW7: Data Bus Width for Bank 7
;//       <0=> 8-bit  <1=> 16-bit  <2=> 32-bit  <3=> Reserved
;//     <o1.27>     ST6: Use UB/LB for Bank 6
;//     <o1.26>     WS6: Enable Wait Status for Bank 6
;//     <o1.24..25> DW6: Data Bus Width for Bank 6
;//       <0=> 8-bit  <1=> 16-bit  <2=> 32-bit  <3=> Reserved
;//     <o1.23>     ST5: Use UB/LB for Bank 5
;//     <o1.22>     WS5: Enable Wait Status for Bank 5
;//     <o1.20..21> DW5: Data Bus Width for Bank 5
;//       <0=> 8-bit  <1=> 16-bit  <2=> 32-bit  <3=> Reserved
;//     <o1.19>     ST4: Use UB/LB for Bank 4
;//     <o1.18>     WS4: Enable Wait Status for Bank 4
;//     <o1.16..17> DW4: Data Bus Width for Bank 4
;//       <0=> 8-bit  <1=> 16-bit  <2=> 32-bit  <3=> Reserved
;//     <o1.15>     ST3: Use UB/LB for Bank 3
;//     <o1.14>     WS3: Enable Wait Status for Bank 3
;//     <o1.12..13> DW3: Data Bus Width for Bank 3
;//       <0=> 8-bit  <1=> 16-bit  <2=> 32-bit  <3=> Reserved
;//     <o1.11>     ST2: Use UB/LB for Bank 2
;//     <o1.10>     WS2: Enable Wait Status for Bank 2
;//     <o1.8..9>   DW2: Data Bus Width for Bank 2
;//       <0=> 8-bit  <1=> 16-bit  <2=> 32-bit  <3=> Reserved
;//     <o1.7>      ST1: Use UB/LB for Bank 1
;//     <o1.6>      WS1: Enable Wait Status for Bank 1
;//     <o1.4..5>   DW1: Data Bus Width for Bank 1
;//       <0=> 8-bit  <1=> 16-bit  <2=> 32-bit  <3=> Reserved
;//     <o1.1..2>   DW0: Indicate Data Bus Width for Bank 0
;//       <1=> 16-bit  <2=> 32-bit
;//   </h>
;//   <h> Bank 0 Control Register (BANKCON0)
;//     <o2.13..14> Tacs: Address Set-up Time before nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o2.11..12> Tcos: Chip Selection Set-up Time before nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o2.8..10>  Tacc: Access Cycle
;//       <0=>  1 clocks  <1=>  2 clocks  <2=>  3 clocks  <3=>  4 clocks
;//       <4=>  6 clocks  <5=>  8 clocks  <6=> 10 clocks  <7=> 14 clocks
;//     <o2.6..7>   Tcoh: Chip Selection Hold Time after nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o2.4..5>   Tcah: Address Hold Time after nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o2.2..3>   Tacp: Page Mode Access Cycle at Page Mode
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> 6 clocks
;//     <o2.0..1>   PMC: Page Mode Configuration
;//       <0=> normal (1 data)  <1=> 4 data  <2=> 8 data  <3=> 16 data
;//   </h>
;//   <h> Bank 1 Control Register (BANKCON1)
;//     <o3.13..14> Tacs: Address Set-up Time before nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o3.11..12> Tcos: Chip Selection Set-up Time before nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o3.8..10>  Tacc: Access Cycle
;//       <0=>  1 clocks  <1=>  2 clocks  <2=>  3 clocks  <3=>  4 clocks
;//       <4=>  6 clocks  <5=>  8 clocks  <6=> 10 clocks  <7=> 14 clocks
;//     <o3.6..7>   Tcoh: Chip Selection Hold Time after nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o3.4..5>   Tcah: Address Hold Time after nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o3.2..3>   Tacp: Page Mode Access Cycle at Page Mode
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> 6 clocks
;//     <o3.0..1>   PMC: Page Mode Configuration
;//       <0=> normal (1 data)  <1=> 4 data  <2=> 8 data  <3=> 16 data
;//   </h>
;//   <h> Bank 2 Control Register (BANKCON2)
;//     <o4.13..14> Tacs: Address Set-up Time before nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o4.11..12> Tcos: Chip Selection Set-up Time before nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o4.8..10>  Tacc: Access Cycle
;//       <0=>  1 clocks  <1=>  2 clocks  <2=>  3 clocks  <3=>  4 clocks
;//       <4=>  6 clocks  <5=>  8 clocks  <6=> 10 clocks  <7=> 14 clocks
;//     <o4.6..7>   Tcoh: Chip Selection Hold Time after nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o4.4..5>   Tcah: Address Hold Time after nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o4.2..3>   Tacp: Page Mode Access Cycle at Page Mode
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> 6 clocks
;//     <o4.0..1>   PMC: Page Mode Configuration
;//       <0=> normal (1 data)  <1=> 4 data  <2=> 8 data  <3=> 16 data
;//   </h>
;//   <h> Bank 3 Control Register (BANKCON3)
;//     <o5.13..14> Tacs: Address Set-up Time before nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o5.11..12> Tcos: Chip Selection Set-up Time before nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o5.8..10>  Tacc: Access Cycle
;//       <0=>  1 clocks  <1=>  2 clocks  <2=>  3 clocks  <3=>  4 clocks
;//       <4=>  6 clocks  <5=>  8 clocks  <6=> 10 clocks  <7=> 14 clocks
;//     <o5.6..7>   Tcoh: Chip Selection Hold Time after nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o5.4..5>   Tcah: Address Hold Time after nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o5.2..3>   Tacp: Page Mode Access Cycle at Page Mode
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> 6 clocks
;//     <o5.0..1>   PMC: Page Mode Configuration
;//       <0=> normal (1 data)  <1=> 4 data  <2=> 8 data  <3=> 16 data
;//   </h>
;//   <h> Bank 4 Control Register (BANKCON4)
;//     <o6.13..14> Tacs: Address Set-up Time before nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o6.11..12> Tcos: Chip Selection Set-up Time before nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o6.8..10>  Tacc: Access Cycle
;//       <0=>  1 clocks  <1=>  2 clocks  <2=>  3 clocks  <3=>  4 clocks
;//       <4=>  6 clocks  <5=>  8 clocks  <6=> 10 clocks  <7=> 14 clocks
;//     <o6.6..7>   Tcoh: Chip Selection Hold Time after nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o6.4..5>   Tcah: Address Hold Time after nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o6.2..3>   Tacp: Page Mode Access Cycle at Page Mode
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> 6 clocks
;//     <o6.0..1>   PMC: Page Mode Configuration
;//       <0=> normal (1 data)  <1=> 4 data  <2=> 8 data  <3=> 16 data
;//   </h>
;//   <h> Bank 5 Control Register (BANKCON5)
;//     <o7.13..14> Tacs: Address Set-up Time before nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o7.11..12> Tcos: Chip Selection Set-up Time before nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o7.8..10>  Tacc: Access Cycle
;//       <0=>  1 clocks  <1=>  2 clocks  <2=>  3 clocks  <3=>  4 clocks
;//       <4=>  6 clocks  <5=>  8 clocks  <6=> 10 clocks  <7=> 14 clocks
;//     <o7.6..7>   Tcoh: Chip Selection Hold Time after nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o7.4..5>   Tcah: Address Hold Time after nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o7.2..3>   Tacp: Page Mode Access Cycle at Page Mode
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> 6 clocks
;//     <o7.0..1>   PMC: Page Mode Configuration
;//       <0=> normal (1 data)  <1=> 4 data  <2=> 8 data  <3=> 16 data
;//   </h>
;//   <h> Bank 6 Control Register (BANKCON6)
;//     <o8.15..16> Memory Type Selection
;//       <0=> ROM or SRAM  <3=> SDRAM
;//     <o8.13..14> Tacs: Address Set-up Time before nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o8.11..12> Tcos: Chip Selection Set-up Time before nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o8.8..10>  Tacc: Access Cycle
;//       <0=>  1 clocks  <1=>  2 clocks  <2=>  3 clocks  <3=>  4 clocks
;//       <4=>  6 clocks  <5=>  8 clocks  <6=> 10 clocks  <7=> 14 clocks
;//     <o8.6..7>   Tcoh: Chip Selection Hold Time after nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o8.4..5>   Tcah: Address Hold Time after nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o8.2..3>   Tacp/Trcd: Page Mode Access Cycle at Page Mode / RAS to CAS Delay
;//       <i>  Parameter depends on Memory Type: if type SRAM then parameter is Tacp,
;//       <i>  if type is SDRAM then parameter is Trcd
;//       <i>  For SDRAM 6 cycles setting is not allowed
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> 6 clocks
;//     <o8.0..1>   PMC/SCAN: Page Mode Configuration / Column Address Number <0-3>
;//       <i>  Parameter depends on Memory Type: if type SRAM then parameter is PMC,
;//       <i>  if type is SDRAM then parameter is SCAN
;//   </h>
;//   <h> Bank 7 Control Register (BANKCON7)
;//     <o9.15..16> Memory Type Selection
;//       <0=> ROM or SRAM  <3=> SDRAM
;//     <o9.13..14> Tacs: Address Set-up Time before nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o9.11..12> Tcos: Chip Selection Set-up Time before nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o9.8..10>  Tacc: Access Cycle
;//       <0=>  1 clocks  <1=>  2 clocks  <2=>  3 clocks  <3=>  4 clocks
;//       <4=>  6 clocks  <5=>  8 clocks  <6=> 10 clocks  <7=> 14 clocks
;//     <o9.6..7>   Tcoh: Chip Selection Hold Time after nOE
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o9.4..5>   Tcah: Address Hold Time after nGCS
;//       <0=> 0 clocks  <1=> 1 clocks  <2=> 2 clocks  <3=> 4 clocks
;//     <o9.2..3>   Tacp/Trcd: Page Mode Access Cycle at Page Mode / RAS to CAS Delay
;//       <i>  Parameter depends on Memory Type: if type SRAM then parameter is Tacp,
;//       <i>  if type is SDRAM then parameter is Trcd
;//       <i>  For SDRAM 6 cycles setting is not allowed
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> 6 clocks
;//     <o9.0..1>   PMC/SCAN: Page Mode Configuration / Column Address Number <0-3>
;//       <i>  Parameter depends on Memory Type: if type SRAM then parameter is PMC,
;//       <i>  if type is SDRAM then parameter is SCAN
;//   </h>
;//   <h> SDRAM Refresh Control Register (REFRESH)
;//     <o10.23>    REFEN: SDRAM Refresh Enable
;//     <o10.22>    TREFMD: SDRAM Refresh Mode
;//       <0=> CBR/Auto Refresh  <1=> Self Refresh
;//     <o10.20..21> Trp: SDRAM RAS Pre-charge Time
;//       <0=> 2 clocks  <1=> 3 clocks  <2=> 4 clocks  <3=> Reserved
;//     <o10.18..19> Tsrc: SDRAM Semi Row Cycle Time
;//       <i> SDRAM Row cycle time: Trc = Tsrc + Trp
;//       <0=> 4 clocks  <1=> 5 clocks  <2=> 6 clocks  <3=> 7 clocks
;//     <o10.0..10> Refresh Counter <0-1023>
;//       <i> Refresh Period = (2048 - Refresh Count + 1) / HCLK
;//   </h>
;//   <h> Flexible Bank Size Register (BANKSIZE)
;//     <o11.7>     BURST_EN: ARM Core Burst Operation Enable
;//     <o11.5>     SCKE_EN: SDRAM Power Down Mode Enable
;//     <o11.4>     SCLK_EN: SCLK Enabled During SDRAM Access Cycle
;//       <0=> SCLK is always active  <1=> SCLK is active only during the access
;//     <o11.0..2>  BK76MAP: BANK6 and BANK7 Memory Map
;//       <0=> 32MB / 32MB  <1=> 64MB / 64MB  <2=> 128MB / 128MB
;//       <4=> 2MB / 2MB    <5=> 4MB / 4MB    <6=> 8MB / 8MB      <7=> 16MB / 16MB
;//     <o11.0..10> Refresh Counter <0-1023>
;//       <i> Refresh Period = (2048 - Refresh Count + 1) / HCLK
;//   </h>
;//   <h> SDRAM Mode Register Set Register 6 (MRSRB6)
;//     <o12.7>     WBL: Write Burst Length
;//       <0=> Burst (Fixed)
;//     <o12.7..8>  TM: Test Mode
;//       <0=> Mode register set (Fixed)
;//     <o12.4..6>  CL: CAS Latency
;//       <0=> 1 clocks  <1=> 2 clocks  <2=> 3 clocks
;//     <o12.3>     BT: Burst Type
;//       <0=> Sequential (Fixed)
;//     <o12.0..2>  BL: Burst Length
;//       <0=> 1 (Fixed)
;//   </h>
;//   <h> SDRAM Mode Register Set Register 7 (MRSRB7)
;//     <o13.7>     WBL: Write Burst Length
;//       <0=> Burst (Fixed)
;//     <o13.7..8>  TM: Test Mode
;//       <0=> Mode register set (Fixed)
;//     <o13.4..6>  CL: CAS Latency
;//       <0=> 1 clocks  <1=> 2 clocks  <2=> 3 clocks
;//     <o13.3>     BT: Burst Type
;//       <0=> Sequential (Fixed)
;//     <o13.0..2>  BL: Burst Length
;//       <0=> 1 (Fixed)
;//   </h>
;// </e> Memory Controller Setup
MC_SETUP        EQU     0
BWSCON_Val      EQU     0x22000000
BANKCON0_Val    EQU     0x00000700
BANKCON1_Val    EQU     0x00000700
BANKCON2_Val    EQU     0x00000700
BANKCON3_Val    EQU     0x00000700
BANKCON4_Val    EQU     0x00000700
BANKCON5_Val    EQU     0x00000700
BANKCON6_Val    EQU     0x00018005
BANKCON7_Val    EQU     0x00018005
REFRESH_Val     EQU     0x008404F3
BANKSIZE_Val    EQU     0x00000032
MRSRB6_Val      EQU     0x00000020
MRSRB7_Val      EQU     0x00000020


;----------------------- I/O Port Definitions ----------------------------------

GPA_BASE        EQU     0x56000000      ; GPA Base Address
GPB_BASE        EQU     0x56000010      ; GPB Base Address
GPC_BASE        EQU     0x56000020      ; GPC Base Address
GPD_BASE        EQU     0x56000030      ; GPD Base Address
GPE_BASE        EQU     0x56000040      ; GPE Base Address
GPF_BASE        EQU     0x56000050      ; GPF Base Address
GPG_BASE        EQU     0x56000060      ; GPG Base Address
GPH_BASE        EQU     0x56000070      ; GPH Base Address
GPJ_BASE        EQU     0x560000D0      ; GPJ Base Address
GPCON_OFS       EQU     0x00            ; Control Register Offset
GPDAT_OFS       EQU     0x04            ; Data Register Offset
GPUP_OFS        EQU     0x08            ; Pull-up Disable Register Offset

;// <e> I/O Setup
GP_SETUP        EQU     1

;//   <e> Port A Settings
;//     <h> Port A Control Register (GPACON)
;//         <o1.22>     GPA22     <0=> Output   <1=> nFCE
;//         <o1.21>     GPA21     <0=> Output   <1=> nRSTOUT
;//         <o1.20>     GPA20     <0=> Output   <1=> nFRE
;//         <o1.19>     GPA19     <0=> Output   <1=> nFWE
;//         <o1.18>     GPA18     <0=> Output   <1=> ALE
;//         <o1.17>     GPA17     <0=> Output   <1=> CLE
;//         <o1.16>     GPA16     <0=> Output   <1=> nGCS[5]
;//         <o1.15>     GPA15     <0=> Output   <1=> nGCS[4]
;//         <o1.14>     GPA14     <0=> Output   <1=> nGCS[3]
;//         <o1.13>     GPA13     <0=> Output   <1=> nGCS[2]
;//         <o1.12>     GPA12     <0=> Output   <1=> nGCS[1]
;//         <o1.11>     GPA11     <0=> Output   <1=> ADDR26
;//         <o1.10>     GPA10     <0=> Output   <1=> ADDR25
;//         <o1.9>      GPA9      <0=> Output   <1=> ADDR24
;//         <o1.8>      GPA8      <0=> Output   <1=> ADDR23
;//         <o1.7>      GPA7      <0=> Output   <1=> ADDR22
;//         <o1.6>      GPA6      <0=> Output   <1=> ADDR21
;//         <o1.5>      GPA5      <0=> Output   <1=> ADDR20
;//         <o1.4>      GPA4      <0=> Output   <1=> ADDR19
;//         <o1.3>      GPA3      <0=> Output   <1=> ADDR18
;//         <o1.2>      GPA2      <0=> Output   <1=> ADDR17
;//         <o1.1>      GPA1      <0=> Output   <1=> ADDR16
;//         <o1.0>      GPA0      <0=> Output   <1=> ADDR0
;//     </h>
;//   </e>
GPA_SETUP       EQU     0
GPACON_Val      EQU     0x000003FF

;//   <e> Port B Settings
;//     <h> Port B Control Register (GPBCON)
;//       <o1.20..21> GPB10     <0=> Input <1=> Output <2=> nXDREQ0 <3=> Reserved
;//       <o1.18..19> GPB9      <0=> Input <1=> Output <2=> nXDACK0 <3=> Reserved
;//       <o1.16..17> GPB8      <0=> Input <1=> Output <2=> nXDREQ1 <3=> Reserved
;//       <o1.14..15> GPB7      <0=> Input <1=> Output <2=> nXDACK1 <3=> Reserved
;//       <o1.12..13> GPB6      <0=> Input <1=> Output <2=> nXBREQ  <3=> Reserved
;//       <o1.10..11> GPB5      <0=> Input <1=> Output <2=> nXBACK  <3=> Reserved
;//       <o1.8..9>   GPB4      <0=> Input <1=> Output <2=> TCLK[0] <3=> Reserved
;//       <o1.6..7>   GPB3      <0=> Input <1=> Output <2=> TOUT3   <3=> Reserved
;//       <o1.4..5>   GPB2      <0=> Input <1=> Output <2=> TOUT2   <3=> Reserved
;//       <o1.2..3>   GPB1      <0=> Input <1=> Output <2=> TOUT1   <3=> Reserved
;//       <o1.0..1>   GPB0      <0=> Input <1=> Output <2=> TOUT0   <3=> Reserved
;//     </h>
;//     <h> Port B Pull-up Settings Register (GPBUP)
;//       <o2.10>     GPB10 Pull-up Disable
;//       <o2.9>      GPB9  Pull-up Disable
;//       <o2.8>      GPB8  Pull-up Disable
;//       <o2.7>      GPB7  Pull-up Disable
;//       <o2.6>      GPB6  Pull-up Disable
;//       <o2.5>      GPB5  Pull-up Disable
;//       <o2.4>      GPB4  Pull-up Disable
;//       <o2.3>      GPB3  Pull-up Disable
;//       <o2.2>      GPB2  Pull-up Disable
;//       <o2.1>      GPB1  Pull-up Disable
;//       <o2.0>      GPB0  Pull-up Disable
;//     </h>
;//   </e>
GPB_SETUP       EQU     0
GPBCON_Val      EQU     0x00000000
GPBUP_Val       EQU     0x00000000

;//   <e> Port C Settings
;//     <h> Port C Control Register (GPCCON)
;//       <o1.30..31> GPC15     <0=> Input <1=> Output <2=> VD[7]   <3=> Reserved
;//       <o1.28..29> GPC14     <0=> Input <1=> Output <2=> VD[6]   <3=> Reserved
;//       <o1.26..27> GPC13     <0=> Input <1=> Output <2=> VD[5]   <3=> Reserved
;//       <o1.24..25> GPC12     <0=> Input <1=> Output <2=> VD[4]   <3=> Reserved
;//       <o1.22..23> GPC11     <0=> Input <1=> Output <2=> VD[3]   <3=> Reserved
;//       <o1.20..21> GPC10     <0=> Input <1=> Output <2=> VD[2]   <3=> Reserved
;//       <o1.18..19> GPC9      <0=> Input <1=> Output <2=> VD[1]   <3=> Reserved
;//       <o1.16..17> GPC8      <0=> Input <1=> Output <2=> VD[0]   <3=> Reserved
;//       <o1.14..15> GPC7      <0=> Input <1=> Output <2=> LCD_LPCREVB <3=> Reserved
;//       <o1.12..13> GPC6      <0=> Input <1=> Output <2=> LCD_LPCREV  <3=> Reserved
;//       <o1.10..11> GPC5      <0=> Input <1=> Output <2=> LCD_LPCOE   <3=> Reserved
;//       <o1.8..9>   GPC4      <0=> Input <1=> Output <2=> VM      <3=> I2SSDI
;//       <o1.6..7>   GPC3      <0=> Input <1=> Output <2=> VFRAME  <3=> Reserved
;//       <o1.4..5>   GPC2      <0=> Input <1=> Output <2=> VLINE   <3=> Reserved
;//       <o1.2..3>   GPC1      <0=> Input <1=> Output <2=> VCLK    <3=> Reserved
;//       <o1.0..1>   GPC0      <0=> Input <1=> Output <2=> LEND    <3=> Reserved
;//     </h>
;//     <h> Port C Pull-up Settings Register (GPCUP)
;//       <o2.15>     GPC15 Pull-up Disable
;//       <o2.14>     GPC14 Pull-up Disable
;//       <o2.13>     GPC13 Pull-up Disable
;//       <o2.12>     GPC12 Pull-up Disable
;//       <o2.11>     GPC11 Pull-up Disable
;//       <o2.10>     GPC10 Pull-up Disable
;//       <o2.9>      GPC9  Pull-up Disable
;//       <o2.8>      GPC8  Pull-up Disable
;//       <o2.7>      GPC7  Pull-up Disable
;//       <o2.6>      GPC6  Pull-up Disable
;//       <o2.5>      GPC5  Pull-up Disable
;//       <o2.4>      GPC4  Pull-up Disable
;//       <o2.3>      GPC3  Pull-up Disable
;//       <o2.2>      GPC2  Pull-up Disable
;//       <o2.1>      GPC1  Pull-up Disable
;//       <o2.0>      GPC0  Pull-up Disable
;//     </h>
;//   </e>
GPC_SETUP       EQU     0
GPCCON_Val      EQU     0x00000000
GPCUP_Val       EQU     0x00000000

;//   <e> Port D Settings
;//     <h> Port D Control Register (GPDCON)
;//       <o1.30..31> GPD15     <0=> Input <1=> Output <2=> VD[23]  <3=> nSS0
;//       <o1.28..29> GPD14     <0=> Input <1=> Output <2=> VD[22]  <3=> nSS1
;//       <o1.26..27> GPD13     <0=> Input <1=> Output <2=> VD[21]  <3=> Reserved
;//       <o1.24..25> GPD12     <0=> Input <1=> Output <2=> VD[20]  <3=> Reserved
;//       <o1.22..23> GPD11     <0=> Input <1=> Output <2=> VD[19]  <3=> Reserved
;//       <o1.20..21> GPD10     <0=> Input <1=> Output <2=> VD[18]  <3=> SPICLK1
;//       <o1.18..19> GPD9      <0=> Input <1=> Output <2=> VD[17]  <3=> SPIMOSI1
;//       <o1.16..17> GPD8      <0=> Input <1=> Output <2=> VD[16]  <3=> SPIMISO1
;//       <o1.14..15> GPD7      <0=> Input <1=> Output <2=> VD[15]  <3=> Reserved
;//       <o1.12..13> GPD6      <0=> Input <1=> Output <2=> VD[14]  <3=> Reserved
;//       <o1.10..11> GPD5      <0=> Input <1=> Output <2=> VD[13]  <3=> Reserved
;//       <o1.8..9>   GPD4      <0=> Input <1=> Output <2=> VD[12]  <3=> Reserved
;//       <o1.6..7>   GPD3      <0=> Input <1=> Output <2=> VD[11]  <3=> Reserved
;//       <o1.4..5>   GPD2      <0=> Input <1=> Output <2=> VD[10]  <3=> Reserved
;//       <o1.2..3>   GPD1      <0=> Input <1=> Output <2=> VD[9]   <3=> Reserved
;//       <o1.0..1>   GPD0      <0=> Input <1=> Output <2=> VD[8]   <3=> Reserved
;//     </h>
;//     <h> Port D Pull-up Settings Register (GPDUP)
;//       <o2.15>     GPD15 Pull-up Disable
;//       <o2.14>     GPD14 Pull-up Disable
;//       <o2.13>     GPD13 Pull-up Disable
;//       <o2.12>     GPD12 Pull-up Disable
;//       <o2.11>     GPD11 Pull-up Disable
;//       <o2.10>     GPD10 Pull-up Disable
;//       <o2.9>      GPD9  Pull-up Disable
;//       <o2.8>      GPD8  Pull-up Disable
;//       <o2.7>      GPD7  Pull-up Disable
;//       <o2.6>      GPD6  Pull-up Disable
;//       <o2.5>      GPD5  Pull-up Disable
;//       <o2.4>      GPD4  Pull-up Disable
;//       <o2.3>      GPD3  Pull-up Disable
;//       <o2.2>      GPD2  Pull-up Disable
;//       <o2.1>      GPD1  Pull-up Disable
;//       <o2.0>      GPD0  Pull-up Disable
;//     </h>
;//   </e>
GPD_SETUP       EQU     0
GPDCON_Val      EQU     0x00000000
GPDUP_Val       EQU     0x00000000

;//   <e> Port E Settings
;//     <h> Port E Control Register (GPECON)
;//       <o1.30..31> GPE15     <0=> Input <1=> Output <2=> IICSDA  <3=> Reserved
;//         <i> This pad is open-drain, and has no pull-up option.
;//       <o1.28..29> GPE14     <0=> Input <1=> Output <2=> IICSCL  <3=> Reserved
;//         <i> This pad is open-drain, and has no pull-up option.
;//       <o1.26..27> GPE13     <0=> Input <1=> Output <2=> SPICLK0 <3=> Reserved
;//       <o1.24..25> GPE12     <0=> Input <1=> Output <2=> SPIMOSI0 <3=> Reserved
;//       <o1.22..23> GPE11     <0=> Input <1=> Output <2=> SPIMISO0 <3=> Reserved
;//       <o1.20..21> GPE10     <0=> Input <1=> Output <2=> SDDAT3  <3=> Reserved
;//       <o1.18..19> GPE9      <0=> Input <1=> Output <2=> SDDAT2  <3=> Reserved
;//       <o1.16..17> GPE8      <0=> Input <1=> Output <2=> SDDAT1  <3=> Reserved
;//       <o1.14..15> GPE7      <0=> Input <1=> Output <2=> SDDAT0  <3=> Reserved
;//       <o1.12..13> GPE6      <0=> Input <1=> Output <2=> SDCMD   <3=> Reserved
;//       <o1.10..11> GPE5      <0=> Input <1=> Output <2=> SDCLK   <3=> Reserved
;//       <o1.8..9>   GPE4      <0=> Input <1=> Output <2=> I2SDO   <3=> AC_SDATA_OUT
;//       <o1.6..7>   GPE3      <0=> Input <1=> Output <2=> I2SDI   <3=> AC_SDATA_IN
;//       <o1.4..5>   GPE2      <0=> Input <1=> Output <2=> CDCLK   <3=> AC_nRESET
;//       <o1.2..3>   GPE1      <0=> Input <1=> Output <2=> I2SSCLK <3=> AC_BIT_CLK
;//       <o1.0..1>   GPE0      <0=> Input <1=> Output <2=> I2SLRCK <3=> AC_SYNC
;//     </h>
;//     <h> Port E Pull-up Settings Register (GPEUP)
;//       <o2.13>     GPE13 Pull-up Disable
;//       <o2.12>     GPE12 Pull-up Disable
;//       <o2.11>     GPE11 Pull-up Disable
;//       <o2.10>     GPE10 Pull-up Disable
;//       <o2.9>      GPE9  Pull-up Disable
;//       <o2.8>      GPE8  Pull-up Disable
;//       <o2.7>      GPE7  Pull-up Disable
;//       <o2.6>      GPE6  Pull-up Disable
;//       <o2.5>      GPE5  Pull-up Disable
;//       <o2.4>      GPE4  Pull-up Disable
;//       <o2.3>      GPE3  Pull-up Disable
;//       <o2.2>      GPE2  Pull-up Disable
;//       <o2.1>      GPE1  Pull-up Disable
;//       <o2.0>      GPE0  Pull-up Disable
;//     </h>
;//   </e>
GPE_SETUP       EQU     0
GPECON_Val      EQU     0x00000000
GPEUP_Val       EQU     0x00000000

;//   <e> Port F Settings
;//     <h> Port F Control Register (GPFCON)
;//       <o1.14..15> GPF7      <0=> Input <1=> Output <2=> EINT[7] <3=> Reserved
;//       <o1.12..13> GPF6      <0=> Input <1=> Output <2=> EINT[6] <3=> Reserved
;//       <o1.10..11> GPF5      <0=> Input <1=> Output <2=> EINT[5] <3=> Reserved
;//       <o1.8..9>   GPF4      <0=> Input <1=> Output <2=> EINT[4] <3=> Reserved
;//       <o1.6..7>   GPF3      <0=> Input <1=> Output <2=> EINT[3] <3=> Reserved
;//       <o1.4..5>   GPF2      <0=> Input <1=> Output <2=> EINT[2] <3=> Reserved
;//       <o1.2..3>   GPF1      <0=> Input <1=> Output <2=> EINT[1] <3=> Reserved
;//       <o1.0..1>   GPF0      <0=> Input <1=> Output <2=> EINT[0] <3=> Reserved
;//     </h>
;//     <h> Port F Pull-up Settings Register (GPFUP)
;//       <o2.7>      GPF7  Pull-up Disable
;//       <o2.6>      GPF6  Pull-up Disable
;//       <o2.5>      GPF5  Pull-up Disable
;//       <o2.4>      GPF4  Pull-up Disable
;//       <o2.3>      GPF3  Pull-up Disable
;//       <o2.2>      GPF2  Pull-up Disable
;//       <o2.1>      GPF1  Pull-up Disable
;//       <o2.0>      GPF0  Pull-up Disable
;//     </h>
;//   </e>
GPF_SETUP       EQU     1
GPFCON_Val      EQU     0x000000AA
GPFUP_Val       EQU     0x0000000F

;//   <e> Port G Settings
;//     <h> Port G Control Register (GPGCON)
;//       <o1.30..31> GPG15     <0=> Input <1=> Output <2=> EINT[23] <3=> Reserved
;//       <o1.28..29> GPG14     <0=> Input <1=> Output <2=> EINT[22] <3=> Reserved
;//       <o1.26..27> GPG13     <0=> Input <1=> Output <2=> EINT[21] <3=> Reserved
;//       <o1.24..25> GPG12     <0=> Input <1=> Output <2=> EINT[20] <3=> Reserved
;//       <o1.22..23> GPG11     <0=> Input <1=> Output <2=> EINT[19] <3=> TCLK[1]
;//       <o1.20..21> GPG10     <0=> Input <1=> Output <2=> EINT[18] <3=> nCTS1
;//       <o1.18..19> GPG9      <0=> Input <1=> Output <2=> EINT[17] <3=> nRTS1
;//       <o1.16..17> GPG8      <0=> Input <1=> Output <2=> EINT[16] <3=> Reserved
;//       <o1.14..15> GPG7      <0=> Input <1=> Output <2=> EINT[15] <3=> SPICLK1
;//       <o1.12..13> GPG6      <0=> Input <1=> Output <2=> EINT[14] <3=> SPIMOSI1
;//       <o1.10..11> GPG5      <0=> Input <1=> Output <2=> EINT[13] <3=> SPIMISO1
;//       <o1.8..9>   GPG4      <0=> Input <1=> Output <2=> EINT[12] <3=> LCD_PWRDN
;//       <o1.6..7>   GPG3      <0=> Input <1=> Output <2=> EINT[11] <3=> nSS1
;//       <o1.4..5>   GPG2      <0=> Input <1=> Output <2=> EINT[10] <3=> nSS0
;//       <o1.2..3>   GPG1      <0=> Input <1=> Output <2=> EINT[9]  <3=> Reserved
;//       <o1.0..1>   GPG0      <0=> Input <1=> Output <2=> EINT[8]  <3=> Reserved
;//     </h>
;//     <h> Port G Pull-up Settings Register (GPGUP)
;//       <o2.15>     GPG15 Pull-up Disable
;//       <o2.14>     GPG14 Pull-up Disable
;//       <o2.13>     GPG13 Pull-up Disable
;//       <o2.12>     GPG12 Pull-up Disable
;//       <o2.11>     GPG11 Pull-up Disable
;//       <o2.10>     GPG10 Pull-up Disable
;//       <o2.9>      GPG9  Pull-up Disable
;//       <o2.8>      GPG8  Pull-up Disable
;//       <o2.7>      GPG7  Pull-up Disable
;//       <o2.6>      GPG6  Pull-up Disable
;//       <o2.5>      GPG5  Pull-up Disable
;//       <o2.4>      GPG4  Pull-up Disable
;//       <o2.3>      GPG3  Pull-up Disable
;//       <o2.2>      GPG2  Pull-up Disable
;//       <o2.1>      GPG1  Pull-up Disable
;//       <o2.0>      GPG0  Pull-up Disable
;//     </h>
;//   </e>
GPG_SETUP       EQU     0
GPGCON_Val      EQU     0x00000000
GPGUP_Val       EQU     0x00000000

;//   <e> Port H Settings
;//     <h> Port H Control Register (GPHCON)
;//       <o1.20..21> GPH10     <0=> Input <1=> Output <2=> CLKOUT1  <3=> Reserved
;//       <o1.18..19> GPH9      <0=> Input <1=> Output <2=> CLKOUT0  <3=> Reserved
;//       <o1.16..17> GPH8      <0=> Input <1=> Output <2=> UEXTCLK  <3=> Reserved
;//       <o1.14..15> GPH7      <0=> Input <1=> Output <2=> RXD[2]   <3=> nCTS1
;//       <o1.12..13> GPH6      <0=> Input <1=> Output <2=> TXD[2]   <3=> nRTS1
;//       <o1.10..11> GPH5      <0=> Input <1=> Output <2=> RXD[1]   <3=> Reserved
;//       <o1.8..9>   GPH4      <0=> Input <1=> Output <2=> TXD[1]   <3=> Reserved
;//       <o1.6..7>   GPH3      <0=> Input <1=> Output <2=> RXD[0]   <3=> Reserved
;//       <o1.4..5>   GPH2      <0=> Input <1=> Output <2=> TXD[0]   <3=> Reserved
;//       <o1.2..3>   GPH1      <0=> Input <1=> Output <2=> nRTS0    <3=> Reserved
;//       <o1.0..1>   GPH0      <0=> Input <1=> Output <2=> nCTS0    <3=> Reserved
;//     </h>
;//     <h> Port H Pull-up Settings Register (GPHUP)
;//       <o2.10>     GPH10 Pull-up Disable
;//       <o2.9>      GPH9  Pull-up Disable
;//       <o2.8>      GPH8  Pull-up Disable
;//       <o2.7>      GPH7  Pull-up Disable
;//       <o2.6>      GPH6  Pull-up Disable
;//       <o2.5>      GPH5  Pull-up Disable
;//       <o2.4>      GPH4  Pull-up Disable
;//       <o2.3>      GPH3  Pull-up Disable
;//       <o2.2>      GPH2  Pull-up Disable
;//       <o2.1>      GPH1  Pull-up Disable
;//       <o2.0>      GPH0  Pull-up Disable
;//     </h>
;//   </e>
GPH_SETUP       EQU     0
GPHCON_Val      EQU     0x00000000
GPHUP_Val       EQU     0x00000000

;//   <e> Port J Settings
;//     <h> Port J Control Register (GPJCON)
;//       <o1.24..25> GPJ12     <0=> Input <1=> Output <2=> CAMRESET   <3=> Reserved
;//       <o1.22..23> GPJ11     <0=> Input <1=> Output <2=> CAMCLKOUT  <3=> Reserved
;//       <o1.20..21> GPJ10     <0=> Input <1=> Output <2=> CAMHREF    <3=> Reserved
;//       <o1.18..19> GPJ9      <0=> Input <1=> Output <2=> CAMVSYNC   <3=> Reserved
;//       <o1.16..17> GPJ8      <0=> Input <1=> Output <2=> CAMPCLK    <3=> Reserved
;//       <o1.14..15> GPJ7      <0=> Input <1=> Output <2=> CAMDATA[7] <3=> Reserved
;//       <o1.12..13> GPJ6      <0=> Input <1=> Output <2=> CAMDATA[6] <3=> Reserved
;//       <o1.10..11> GPJ5      <0=> Input <1=> Output <2=> CAMDATA[5] <3=> Reserved
;//       <o1.8..9>   GPJ4      <0=> Input <1=> Output <2=> CAMDATA[4] <3=> Reserved
;//       <o1.6..7>   GPJ3      <0=> Input <1=> Output <2=> CAMDATA[3] <3=> Reserved
;//       <o1.4..5>   GPJ2      <0=> Input <1=> Output <2=> CAMDATA[2] <3=> Reserved
;//       <o1.2..3>   GPJ1      <0=> Input <1=> Output <2=> CAMDATA[1] <3=> Reserved
;//       <o1.0..1>   GPJ0      <0=> Input <1=> Output <2=> CAMDATA[0] <3=> Reserved
;//     </h>
;//     <h> Port J Pull-up Settings Register (GPJUP)
;//       <o2.12>     GPJ12 Pull-up Disable
;//       <o2.11>     GPJ11 Pull-up Disable
;//       <o2.10>     GPJ10 Pull-up Disable
;//       <o2.9>      GPJ9  Pull-up Disable
;//       <o2.8>      GPJ8  Pull-up Disable
;//       <o2.7>      GPJ7  Pull-up Disable
;//       <o2.6>      GPJ6  Pull-up Disable
;//       <o2.5>      GPJ5  Pull-up Disable
;//       <o2.4>      GPJ4  Pull-up Disable
;//       <o2.3>      GPJ3  Pull-up Disable
;//       <o2.2>      GPJ2  Pull-up Disable
;//       <o2.1>      GPJ1  Pull-up Disable
;//       <o2.0>      GPJ0  Pull-up Disable
;//     </h>
;//   </e>
GPJ_SETUP       EQU     0
GPJCON_Val      EQU     0x00000000
GPJUP_Val       EQU     0x00000000

;// </e> I/O Setup


;----------------------- CODE --------------------------------------------------

                PRESERVE8


; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM

; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

				EXPORT Entry_Point
Entry_Point
Vectors         LDR     PC, Reset_Addr
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
		NOP
                LDR     PC, IRQ_Addr
                LDR     PC, FIQ_Addr

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0                   ; Reserved Address
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
SWI_Handler     B       SWI_Handler
PAbt_Handler    B       PAbt_Handler
;DAbt_Handler    B       DAbt_Handler
FIQ_Handler     B       FIQ_Handler

;*
;*************************************************************************
;*
;* Interrupt handling
;*
;*************************************************************************
;*
; DAbt Handler
DAbt_Handler
               IMPORT rt_hw_trap_dabt

                	sub 	sp, sp, #72
	                stmia 	sp, {r0 - r12}   		;/* Calling r0-r12					*/
                    add		r8, sp, #60
	                stmdb   r8, {sp, lr}            ;/* Calling SP, LR					*/
	                str		lr, [r8, #0]            ;/* Save calling PC					*/
	                mrs		r6, spsr
	                str		r6, [r8, #4]            ;/* Save CPSR						*/
	                str		r0, [r8, #8]            ;/* Save OLD_R0						*/
	                mov		r0, sp

	                bl 		rt_hw_trap_dabt


;##########################################
; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler


; Watchdog Setup ---------------------------------------------------------------

                IF      WT_SETUP != 0
                LDR     R0, =WT_BASE
                LDR     R1, =WTCON_Val
                LDR     R2, =WTDAT_Val
                STR     R2, [R0, #WTCNT_OFS]
                STR     R2, [R0, #WTDAT_OFS]
                STR     R1, [R0, #WTCON_OFS]
                ENDIF


; Clock Setup ------------------------------------------------------------------

                IF      (:LNOT:(:DEF:NO_CLOCK_SETUP)):LAND:(CLOCK_SETUP != 0)
                LDR     R0, =CLOCK_BASE
                LDR     R1,      =LOCKTIME_Val
                STR     R1, [R0, #LOCKTIME_OFS]
                MOV     R1,      #CLKDIVN_Val
                STR     R1, [R0, #CLKDIVN_OFS]
                LDR     R1,      =CAMDIVN_Val
                STR     R1, [R0, #CAMDIVN_OFS]
                LDR     R1,      =MPLLCON_Val
                STR     R1, [R0, #MPLLCON_OFS]
                LDR     R1,      =UPLLCON_Val
                STR     R1, [R0, #UPLLCON_OFS]
                MOV     R1,      #CLKSLOW_Val
                STR     R1, [R0, #CLKSLOW_OFS]
                LDR     R1,      =CLKCON_Val
                STR     R1, [R0, #CLKCON_OFS]
                ENDIF


; Memory Controller Setup ------------------------------------------------------

                IF      (:LNOT:(:DEF:NO_MC_SETUP)):LAND:(CLOCK_SETUP != 0)
                LDR     R0, =MC_BASE
                LDR     R1,      =BWSCON_Val
                STR     R1, [R0, #BWSCON_OFS]
                LDR     R1,      =BANKCON0_Val
                STR     R1, [R0, #BANKCON0_OFS]
                LDR     R1,      =BANKCON1_Val
                STR     R1, [R0, #BANKCON1_OFS]
                LDR     R1,      =BANKCON2_Val
                STR     R1, [R0, #BANKCON2_OFS]
                LDR     R1,      =BANKCON3_Val
                STR     R1, [R0, #BANKCON3_OFS]
                LDR     R1,      =BANKCON4_Val
                STR     R1, [R0, #BANKCON4_OFS]
                LDR     R1,      =BANKCON5_Val
                STR     R1, [R0, #BANKCON5_OFS]
                LDR     R1,      =BANKCON6_Val
                STR     R1, [R0, #BANKCON6_OFS]
                LDR     R1,      =BANKCON7_Val
                STR     R1, [R0, #BANKCON7_OFS]
                LDR     R1,      =REFRESH_Val
                STR     R1, [R0, #REFRESH_OFS]
                MOV     R1,      #BANKSIZE_Val
                STR     R1, [R0, #BANKSIZE_OFS]
                MOV     R1,      #MRSRB6_Val
                STR     R1, [R0, #MRSRB6_OFS]
                MOV     R1,      #MRSRB7_Val
                STR     R1, [R0, #MRSRB7_OFS]
                ENDIF


; I/O Pins Setup ---------------------------------------------------------------

                IF      (:LNOT:(:DEF:NO_GP_SETUP)):LAND:(GP_SETUP != 0)

                IF      GPA_SETUP != 0
                LDR     R0, =GPA_BASE
                LDR     R1, =GPACON_Val
                STR     R1, [R0, #GPCON_OFS]
                ENDIF

                IF      GPB_SETUP != 0
                LDR     R0, =GPB_BASE
                LDR     R1, =GPBCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPBUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPC_SETUP != 0
                LDR     R0, =GPC_BASE
                LDR     R1, =GPCCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPCUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPD_SETUP != 0
                LDR     R0, =GPD_BASE
                LDR     R1, =GPDCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPDUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPE_SETUP != 0
                LDR     R0, =GPE_BASE
                LDR     R1, =GPECON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPEUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPF_SETUP != 0
                LDR     R0, =GPF_BASE
                LDR     R1, =GPFCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPFUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPG_SETUP != 0
                LDR     R0, =GPG_BASE
                LDR     R1, =GPGCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPGUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPH_SETUP != 0
                LDR     R0, =GPH_BASE
                LDR     R1, =GPHCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPHUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPJ_SETUP != 0
                LDR     R0, =GPJ_BASE
                LDR     R1, =GPJCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPJUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                ENDIF


; Copy Exception Vectors to Internal RAM ---------------------------------------

                IF      :DEF:RAM_INTVEC
                ADR     R8,  Vectors    ; Source
                LDR     R9, =IRAM_BASE  ; Destination
                LDMIA   R8!, {R0-R7}    ; Load Vectors
                STMIA   R9!, {R0-R7}    ; Store Vectors
                LDMIA   R8!, {R0-R7}    ; Load Handler Addresses
                STMIA   R9!, {R0-R7}    ; Store Handler Addresses
                ENDIF


; Setup Stack for each mode ----------------------------------------------------

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                ; MSR     CPSR_c, #Mode_USR
                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

; Enter the C code -------------------------------------------------------------

                IMPORT  __main
                LDR     R0, =__main
                BX      R0

                IMPORT rt_interrupt_enter
                IMPORT rt_interrupt_leave
                IMPORT rt_thread_switch_interrupt_flag
                IMPORT rt_interrupt_from_thread
                IMPORT rt_interrupt_to_thread
                IMPORT rt_hw_trap_irq

IRQ_Handler     PROC
                EXPORT IRQ_Handler
                STMFD   sp!, {r0-r12,lr}
                BL  rt_interrupt_enter
                BL  rt_hw_trap_irq
                BL  rt_interrupt_leave

                ; if rt_thread_switch_interrupt_flag set, jump to
                ; rt_hw_context_switch_interrupt_do and don't return
                LDR r0, =rt_thread_switch_interrupt_flag
                LDR r1, [r0]
                CMP r1, #1
                BEQ rt_hw_context_switch_interrupt_do

                LDMFD   sp!, {r0-r12,lr}
                SUBS    pc, lr, #4
                ENDP

; /*
; * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
; */
rt_hw_context_switch_interrupt_do   PROC
                EXPORT rt_hw_context_switch_interrupt_do
                MOV     r1,  #0         ; clear flag
                STR     r1,  [r0]

                LDMFD   sp!, {r0-r12,lr}; reload saved registers
                STMFD   sp!, {r0-r3}    ; save r0-r3
                MOV     r1,  sp
                ADD     sp,  sp, #16    ; restore sp
                SUB     r2,  lr, #4     ; save old task's pc to r2

                MRS     r3,  spsr       ; get cpsr of interrupt thread

                ; switch to SVC mode and no interrupt
				MSR 	cpsr_c, #I_Bit:OR:F_Bit:OR:Mode_SVC

                STMFD   sp!, {r2}       ; push old task's pc
                STMFD   sp!, {r4-r12,lr}; push old task's lr,r12-r4
                MOV     r4,  r1         ; Special optimised code below
                MOV     r5,  r3
                LDMFD   r4!, {r0-r3}
                STMFD   sp!, {r0-r3}    ; push old task's r3-r0
                STMFD   sp!, {r5}       ; push old task's cpsr
                MRS     r4,  spsr
                STMFD   sp!, {r4}       ; push old task's spsr

                LDR     r4,  =rt_interrupt_from_thread
                LDR     r5,  [r4]
                STR     sp,  [r5]       ; store sp in preempted tasks's TCB

                LDR     r6,  =rt_interrupt_to_thread
                LDR     r6,  [r6]
                LDR     sp,  [r6]       ; get new task's stack pointer

                LDMFD   sp!, {r4}       ; pop new task's spsr
                MSR     spsr_cxsf, r4
                LDMFD   sp!, {r4}       ; pop new task's psr
                MSR     cpsr_cxsf, r4

                LDMFD   sp!, {r0-r12,lr,pc} ; pop new task's r0-r12,lr & pc
                ENDP

                IF      :DEF:__MICROLIB

                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE
; User Initial Stack & Heap
                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDIF


                END

