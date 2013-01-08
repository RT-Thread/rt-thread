;/*****************************************************************************/
;/* S3C44B0X.S: Startup file for Samsung S3C44B0X                             */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */ 
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2006 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


; *** Startup Code (executed after Reset) ***


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


; CPU Wrapper and Bus Priorities definitions
CPUW_BASE       EQU     0x01C00000      ; CPU Wrapper Base Address
SYSCFG_OFS      EQU     0x00            ; SYSCFG Offset
NCACHBE0_OFS    EQU     0x04            ; NCACHBE0 Offset
NCACHBE1_OFS    EQU     0x08            ; NCACHBE0 Offset
BUSP_BASE       EQU     0x01C40000      ; Bus Priority Base Address
SBUSCON_OFS     EQU     0x00            ; SBUSCON Offset

;// <e> CPU Wrapper and Bus Priorities
;//   <h> CPU Wrapper
;//     <o1.0>      SE: Stall Enable
;//     <o1.1..2>   CM: Cache Mode
;//                 <0=> Disable Cache (8kB SRAM)
;//                 <1=> Half Cache Enable (4kB Cache, 4kB SRAM)
;//                 <2=> Reserved
;//                 <3=> Full Cache Enable (8kB Cache)
;//     <o1.3>      WE: Write Buffer Enable
;//     <o1.4>      RSE: Read Stall Enable
;//     <o1.5>      DA: Data Abort  <0=> Enable <1=> Disable
;//     <h> Non-cacheable Area 0
;//       <o2.0..15>  Start Address     <0x0-0x0FFFF000:0x1000><#/0x1000>
;//                   <i> SA = (Start Address) / 4k
;//       <o2.16..31> End Address + 1   <0x0-0x10000000:0x1000><#/0x1000>
;//                   <i> SE = (End Address + 1) / 4k
;//     </h>
;//     <h> Non-cacheable Area 1
;//       <o3.0..15>  Start Address     <0x0-0x0FFFF000:0x1000><#/0x1000>
;//                   <i> SA = (Start Address) / 4k
;//       <o3.16..31> End Address + 1   <0x0-0x10000000:0x1000><#/0x1000>
;//                   <i> SE = (End Address + 1) / 4k
;//     </h>
;//   </h>
;//   <h> Bus Priorities
;//     <o4.31>       FIX: Fixed Priorities
;//     <o4.6..7>     LCD_DMA    <0=> 1st  <1=> 2nd  <2=> 3rd  <3=> 4th
;//     <o4.4..5>     ZDMA       <0=> 1st  <1=> 2nd  <2=> 3rd  <3=> 4th
;//     <o4.2..3>     BDMA       <0=> 1st  <1=> 2nd  <2=> 3rd  <3=> 4th
;//     <o4.0..1>     nBREQ      <0=> 1st  <1=> 2nd  <2=> 3rd  <3=> 4th
;//   </h>
;// </e>
SYS_SETUP       EQU     0
SYSCFG_Val      EQU     0x00000001
NCACHBE0_Val    EQU     0x00000000
NCACHBE1_Val    EQU     0x00000000
SBUSCON_Val     EQU     0x80001B1B


;// <e> Vectored Interrupt Mode (for IRQ)
;//   <o1.25> EINT0      <i> External Interrupt 0
;//   <o1.24> EINT1      <i> External Interrupt 1
;//   <o1.23> EINT2      <i> External Interrupt 2                        
;//   <o1.22> EINT3      <i> External Interrupt 3
;//   <o1.21> EINT4567   <i> External Interrupt 4/5/6/7
;//   <o1.20> TICK       <i> RTC Time Tick Interrupt
;//   <o1.19> ZDMA0      <i> General DMA0 Interrupt
;//   <o1.18> ZDMA1      <i> General DMA1 Interrupt
;//   <o1.17> BDMA0      <i> Bridge DMA0 Interrupt
;//   <o1.16> BDMA1      <i> Bridge DMA1 Interrupt
;//   <o1.15> WDT        <i> Watchdog Timer Interrupt
;//   <o1.14> UERR01     <i> UART0/1 Error Interrupt
;//   <o1.13> TIMER0     <i> Timer0 Interrupt
;//   <o1.12> TIMER1     <i> Timer1 Interrupt
;//   <o1.11> TIMER2     <i> Timer2 Interrupt
;//   <o1.10> TIMER3     <i> Timer3 Interrupt
;//   <o1.9>  TIMER4     <i> Timer4 Interrupt
;//   <o1.8>  TIMER5     <i> Timer5 Interrupt
;//   <o1.7>  URXD0      <i> UART0 Rx Interrupt
;//   <o1.6>  URXD1      <i> UART1 Rx Interrupt
;//   <o1.5>  IIC        <i> IIC Interrupt
;//   <o1.4>  SIO        <i> SIO Interrupt
;//   <o1.3>  UTXD0      <i> UART0 Tx Interrupt
;//   <o1.2>  UTXD1      <i> UART1 Tx Interrupt
;//   <o1.1>  RTC        <i> RTC Alarm Interrupt
;//   <o1.0>  ADC        <i> ADC EOC Interrupt
;// </e>
VIM_SETUP       EQU     0
VIM_CFG         EQU     0x00000000


; Clock Management definitions
CLK_BASE        EQU     0x01D80000      ; Clock Base Address
PLLCON_OFS      EQU     0x00            ; PLLCON Offset
CLKCON_OFS      EQU     0x04            ; CLKCON Offset
CLKSLOW_OFS     EQU     0x08            ; CLKSLOW Offset
LOCKTIME_OFS    EQU     0x0C            ; LOCKTIME Offset

;// <e> Clock Management
;//   <h> PLL Settings
;//   <i> Fpllo = (m * Fin) / (p * 2^s), 20MHz < Fpllo < 66MHz
;//     <o1.12..19> MDIV: Main divider <0x0-0xFF>
;//                 <i> m = MDIV + 8
;//     <o1.4..9>   PDIV: Pre-divider  <0x0-0x3F>
;//                 <i> p = PDIV + 2, 1MHz <= Fin/p < 2MHz
;//     <o1.0..1>   SDIV: Post Divider <0x0-0x03>
;//                 <i> s = SDIV, Fpllo * 2^s < 170MHz
;//     <o4.0..11>  LTIME CNT: PLL Lock Time Count  <0x0-0x0FFF>
;//   </h>
;//   <h> Master Clock
;//   <i> PLL Clock:  Fout = Fpllo
;//   <i> Slow Clock: Fout = Fin / (2 * SLOW_VAL), SLOW_VAL > 0
;//   <i> Slow Clock: Fout = Fin, SLOW_VAL = 0
;//     <o3.5>      PLL_OFF: PLL Off
;//                 <i> PLL is turned Off only when SLOW_BIT = 1
;//     <o3.4>      SLOW_BIT: Slow Clock
;//     <o3.0..3>   SLOW_VAL: Slow Clock divider    <0x0-0x0F>
;//   </h>
;//   <h> Clock Generation
;//     <o2.14>     IIS       <0=> Disable  <1=> Enable
;//     <o2.13>     IIC       <0=> Disable  <1=> Enable
;//     <o2.12>     ADC       <0=> Disable  <1=> Enable
;//     <o2.11>     RTC       <0=> Disable  <1=> Enable
;//     <o2.10>     GPIO      <0=> Disable  <1=> Enable
;//     <o2.9>      UART1     <0=> Disable  <1=> Enable
;//     <o2.8>      UART0     <0=> Disable  <1=> Enable
;//     <o2.7>      BDMA0,1   <0=> Disable  <1=> Enable
;//     <o2.6>      LCDC      <0=> Disable  <1=> Enable
;//     <o2.5>      SIO       <0=> Disable  <1=> Enable
;//     <o2.4>      ZDMA0,1   <0=> Disable  <1=> Enable
;//     <o2.3>      PWMTIMER  <0=> Disable  <1=> Enable
;//   </h>
;// </e>
CLK_SETUP       EQU     1
PLLCON_Val      EQU     0x00038080
CLKCON_Val      EQU     0x00007FF8
CLKSLOW_Val     EQU     0x00000009
LOCKTIME_Val    EQU     0x00000FFF


; Watchdog Timer definitions
WT_BASE         EQU     0x01D30000      ; WT Base Address
WTCON_OFS       EQU     0x00            ; WTCON Offset
WTDAT_OFS       EQU     0x04            ; WTDAT Offset
WTCNT_OFS       EQU     0x08            ; WTCNT Offset

;// <e> Watchdog Timer
;//   <o1.5>      Watchdog Timer Enable/Disable
;//   <o1.0>      Reset Enable/Disable
;//   <o1.2>      Interrupt Enable/Disable
;//   <o1.3..4>   Clock Select  
;//               <0=> 1/16  <1=> 1/32  <2=> 1/64  <3=> 1/128
;//               <i> Clock Division Factor
;//   <o1.8..15>  Prescaler Value <0x0-0xFF>
;//   <o2.0..15>  Time-out Value  <0x0-0xFFFF>
;// </e>
WT_SETUP        EQU     1
WTCON_Val       EQU     0x00008000
WTDAT_Val       EQU     0x00008000


; Memory Controller definitions
MC_BASE         EQU     0x01C80000      ; Memory Controller Base Address

;// <e> Memory Controller
MC_SETUP        EQU     1

;//   <h> Bank 0
;//     <o0.0..1>   PMC: Page Mode Configuration
;//                 <0=> 1 Data  <1=> 4 Data  <2=> 8 Data  <3=> 16 Data
;//     <o0.2..3>   Tpac: Page Mode Access Cycle
;//                 <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> 6 clks
;//     <o0.4..5>   Tcah: Address Holding Time after nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o0.6..7>   Toch: Chip Select Hold on nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o0.8..10>  Tacc: Access Cycle
;//                 <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//                 <4=> 6 clk   <5=> 8 clks  <6=> 10 clks <7=> 14 clks
;//     <o0.11..12> Tcos: Chip Select Set-up nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o0.13..14> Tacs: Address Set-up before nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//   </h>
;//
;//   <h> Bank 1
;//     <o8.4..5>   DW: Data Bus Width
;//                 <0=> 8-bit   <1=> 16-bit  <2=> 32-bit  <3=> Rsrvd
;//     <o8.6>      WS: WAIT Status
;//                 <0=> WAIT Disable
;//                 <1=> WAIT Enable
;//     <o8.7>      ST: SRAM Type
;//                 <0=> Not using UB/LB
;//                 <1=> Using UB/LB
;//     <o1.0..1>   PMC: Page Mode Configuration
;//                 <0=> 1 Data  <1=> 4 Data  <2=> 8 Data  <3=> 16 Data
;//     <o1.2..3>   Tpac: Page Mode Access Cycle
;//                 <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> 6 clks
;//     <o1.4..5>   Tcah: Address Holding Time after nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o1.6..7>   Toch: Chip Select Hold on nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o1.8..10>  Tacc: Access Cycle
;//                 <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//                 <4=> 6 clk   <5=> 8 clks  <6=> 10 clks <7=> 14 clks
;//     <o1.11..12> Tcos: Chip Select Set-up nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o1.13..14> Tacs: Address Set-up before nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//   </h>
;//
;//   <h> Bank 2
;//     <o8.8..9>   DW: Data Bus Width
;//                 <0=> 8-bit   <1=> 16-bit  <2=> 32-bit  <3=> Rsrvd
;//     <o8.10>     WS: WAIT Status
;//                 <0=> WAIT Disable
;//                 <1=> WAIT Enable
;//     <o8.11>     ST: SRAM Type
;//                 <0=> Not using UB/LB
;//                 <1=> Using UB/LB
;//     <o2.0..1>   PMC: Page Mode Configuration
;//                 <0=> 1 Data  <1=> 4 Data  <2=> 8 Data  <3=> 16 Data
;//     <o2.2..3>   Tpac: Page Mode Access Cycle
;//                 <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> 6 clks
;//     <o2.4..5>   Tcah: Address Holding Time after nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o2.6..7>   Toch: Chip Select Hold on nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o2.8..10>  Tacc: Access Cycle
;//                 <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//                 <4=> 6 clk   <5=> 8 clks  <6=> 10 clks <7=> 14 clks
;//     <o2.11..12> Tcos: Chip Select Set-up nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o2.13..14> Tacs: Address Set-up before nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//   </h>
;//
;//   <h> Bank 3
;//     <o8.12..13> DW: Data Bus Width
;//                 <0=> 8-bit   <1=> 16-bit  <2=> 32-bit  <3=> Rsrvd
;//     <o8.14>     WS: WAIT Status
;//                 <0=> WAIT Disable
;//                 <1=> WAIT Enable
;//     <o8.15>     ST: SRAM Type
;//                 <0=> Not using UB/LB
;//                 <1=> Using UB/LB
;//     <o3.0..1>   PMC: Page Mode Configuration
;//                 <0=> 1 Data  <1=> 4 Data  <2=> 8 Data  <3=> 16 Data
;//     <o3.2..3>   Tpac: Page Mode Access Cycle
;//                 <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> 6 clks
;//     <o3.4..5>   Tcah: Address Holding Time after nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o3.6..7>   Toch: Chip Select Hold on nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o3.8..10>  Tacc: Access Cycle
;//                 <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//                 <4=> 6 clk   <5=> 8 clks  <6=> 10 clks <7=> 14 clks
;//     <o3.11..12> Tcos: Chip Select Set-up nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o3.13..14> Tacs: Address Set-up before nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//   </h>
;//
;//   <h> Bank 4
;//     <o8.16..17> DW: Data Bus Width
;//                 <0=> 8-bit   <1=> 16-bit  <2=> 32-bit  <3=> Rsrvd
;//     <o8.18>     WS: WAIT Status
;//                 <0=> WAIT Disable
;//                 <1=> WAIT Enable
;//     <o8.19>     ST: SRAM Type
;//                 <0=> Not using UB/LB
;//                 <1=> Using UB/LB
;//     <o4.0..1>   PMC: Page Mode Configuration
;//                 <0=> 1 Data  <1=> 4 Data  <2=> 8 Data  <3=> 16 Data
;//     <o4.2..3>   Tpac: Page Mode Access Cycle
;//                 <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> 6 clks
;//     <o4.4..5>   Tcah: Address Holding Time after nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o4.6..7>   Toch: Chip Select Hold on nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o4.8..10>  Tacc: Access Cycle
;//                 <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//                 <4=> 6 clk   <5=> 8 clks  <6=> 10 clks <7=> 14 clks
;//     <o4.11..12> Tcos: Chip Select Set-up nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o4.13..14> Tacs: Address Set-up before nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//   </h>
;//
;//   <h> Bank 5
;//     <o8.20..21> DW: Data Bus Width
;//                 <0=> 8-bit   <1=> 16-bit  <2=> 32-bit  <3=> Rsrvd
;//     <o8.22>     WS: WAIT Status
;//                 <0=> WAIT Disable
;//                 <1=> WAIT Enable
;//     <o8.23>     ST: SRAM Type
;//                 <0=> Not using UB/LB
;//                 <1=> Using UB/LB
;//     <o5.0..1>   PMC: Page Mode Configuration
;//                 <0=> 1 Data  <1=> 4 Data  <2=> 8 Data  <3=> 16 Data
;//     <o5.2..3>   Tpac: Page Mode Access Cycle
;//                 <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> 6 clks
;//     <o5.4..5>   Tcah: Address Holding Time after nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o5.6..7>   Toch: Chip Select Hold on nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o5.8..10>  Tacc: Access Cycle
;//                 <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//                 <4=> 6 clk   <5=> 8 clks  <6=> 10 clks <7=> 14 clks
;//     <o5.11..12> Tcos: Chip Select Set-up nOE
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     <o5.13..14> Tacs: Address Set-up before nGCSn
;//                 <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//   </h>
;//
;//   <h> Bank 6
;//     <o10.0..2>  BK76MAP: Bank 6/7 Memory Map
;//                 <0=> 32M  <4=> 2M   <5=> 4M   <6=> 8M   <7=> 16M
;//     <o8.24..25> DW: Data Bus Width
;//                 <0=> 8-bit   <1=> 16-bit  <2=> 32-bit  <3=> Rsrvd
;//     <o8.26>     WS: WAIT Status
;//                 <0=> WAIT Disable
;//                 <1=> WAIT Enable
;//     <o8.27>     ST: SRAM Type
;//                 <0=> Not using UB/LB
;//                 <1=> Using UB/LB
;//     <o6.15..16> MT: Memory Type
;//                 <0=> ROM or SRAM
;//                 <1=> FP DRAMP
;//                 <2=> EDO DRAM
;//                 <3=> SDRAM
;//     <h> ROM or SRAM
;//       <o6.0..1>   PMC: Page Mode Configuration
;//                   <0=> 1 Data  <1=> 4 Data  <2=> 8 Data  <3=> 16 Data
;//       <o6.2..3>   Tpac: Page Mode Access Cycle
;//                 <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> 6 clks
;//       <o6.4..5>   Tcah: Address Holding Time after nGCSn
;//                   <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//       <o6.6..7>   Toch: Chip Select Hold on nOE
;//                   <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//       <o6.8..10>  Tacc: Access Cycle
;//                   <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//                   <4=> 6 clk   <5=> 8 clks  <6=> 10 clks <7=> 14 clks
;//       <o6.11..12> Tcos: Chip Select Set-up nOE
;//                   <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//       <o6.13..14> Tacs: Address Set-up before nGCSn
;//                   <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     </h>
;//     <h> FP DRAM or EDO DRAM
;//       <o6.0..1>   CAN: Columnn Address Number
;//                   <0=> 8-bit   <1=> 9-bit   <2=> 10-bit  <3=> 11-bit
;//       <o6.2>      Tcp: CAS Pre-charge
;//                   <0=> 1 clk   <1=> 2 clks
;//       <o6.3>      Tcas: CAS Pulse Width
;//                   <0=> 1 clk   <1=> 2 clks
;//       <o6.4..5>   Trcd: RAS to CAS Delay
;//                   <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//     </h>
;//     <h> SDRAM
;//       <o6.0..1>   SCAN: Columnn Address Number
;//                   <0=> 8-bit   <1=> 9-bit   <2=> 10-bit  <3=> Rsrvd
;//       <o6.2..3>   Trcd: RAS to CAS Delay
;//                   <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> Rsrvd
;//       <o10.4>     SCLKEN: SCLK Selection (Bank 6/7)
;//                   <0=> Normal
;//                   <1=> Reduced Power 
;//       <o11.0..2>  BL: Burst Length
;//                   <0=> 1
;//       <o11.3>     BT: Burst Type
;//                   <0=> Sequential
;//       <o11.4..6>  CL: CAS Latency
;//                   <0=> 1 clk   <1=> 2 clks  <2=> 3 clks
;//       <o11.7..8>  TM: Test Mode
;//                   <0=> Mode Register Set
;//       <o11.9>     WBL: Write Burst Length
;//                   <0=> 0
;//     </h>
;//   </h>
;//
;//   <h> Bank 7
;//     <o10.0..2>  BK76MAP: Bank 6/7 Memory Map
;//                 <0=> 32M  <4=> 2M   <5=> 4M   <6=> 8M   <7=> 16M
;//     <o8.28..29> DW: Data Bus Width
;//                 <0=> 8-bit   <1=> 16-bit  <2=> 32-bit  <3=> Rsrvd
;//     <o8.30>     WS: WAIT Status
;//                 <0=> WAIT Disable
;//                 <1=> WAIT Enable
;//     <o8.31>     ST: SRAM Type
;//                 <0=> Not using UB/LB
;//                 <1=> Using UB/LB
;//     <o7.15..16> MT: Memory Type
;//                 <0=> ROM or SRAM
;//                 <1=> FP DRAMP
;//                 <2=> EDO DRAM
;//                 <3=> SDRAM
;//     <h> ROM or SRAM
;//       <o7.0..1>   PMC: Page Mode Configuration
;//                   <0=> 1 Data  <1=> 4 Data  <2=> 8 Data  <3=> 16 Data
;//       <o7.2..3>   Tpac: Page Mode Access Cycle
;//                 <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> 6 clks
;//       <o7.4..5>   Tcah: Address Holding Time after nGCSn
;//                   <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//       <o7.6..7>   Toch: Chip Select Hold on nOE
;//                   <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//       <o7.8..10>  Tacc: Access Cycle
;//                   <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//                   <4=> 6 clk   <5=> 8 clks  <6=> 10 clks <7=> 14 clks
;//       <o7.11..12> Tcos: Chip Select Set-up nOE
;//                   <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//       <o7.13..14> Tacs: Address Set-up before nGCSn
;//                   <0=> 0 clk   <1=> 1 clk   <2=> 2 clks  <3=> 4 clks
;//     </h>
;//     <h> FP DRAM or EDO DRAM
;//       <o7.0..1>   CAN: Columnn Address Number
;//                   <0=> 8-bit   <1=> 9-bit   <2=> 10-bit  <3=> 11-bit
;//       <o7.2>      Tcp: CAS Pre-charge
;//                   <0=> 1 clk   <1=> 2 clks
;//       <o7.3>      Tcas: CAS Pulse Width
;//                   <0=> 1 clk   <1=> 2 clks
;//       <o7.4..5>   Trcd: RAS to CAS Delay
;//                   <0=> 1 clk   <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//     </h>
;//     <h> SDRAM
;//       <o7.0..1>   SCAN: Columnn Address Number
;//                   <0=> 8-bit   <1=> 9-bit   <2=> 10-bit  <3=> Rsrvd
;//       <o7.2..3>   Trcd: RAS to CAS Delay
;//                   <0=> 2 clks  <1=> 3 clks  <2=> 4 clks  <3=> Rsrvd
;//       <o10.4>     SCLKEN: SCLK Selection (Bank 6/7)
;//                   <0=> Normal
;//                   <1=> Reduced Power 
;//       <o12.0..2>  BL: Burst Length
;//                   <0=> 1
;//       <o12.3>     BT: Burst Type
;//                   <0=> Sequential
;//       <o12.4..6>  CL: CAS Latency
;//                   <0=> 1 clk   <1=> 2 clks  <2=> 3 clks
;//       <o12.7..8>  TM: Test Mode
;//                   <0=> Mode Register Set
;//       <o12.9>     WBL: Write Burst Length
;//                   <0=> 0
;//     </h>
;//   </h>
;//
;//   <h> Refresh
;//     <o9.23>     REFEN: DRAM/SDRAM Refresh
;//                 <0=> Disable <1=> Enable
;//     <o9.22>     TREFMD: DRAM/SDRAM Refresh Mode
;//                 <0=> CBR/Auto Refresh
;//                 <1=> Self Refresh
;//     <o9.20..21> Trp: DRAM/SDRAM RAS Pre-charge Time
;//                 <0=> 1.5 clks (DRAM) / 2 clks (SDRAM)
;//                 <1=> 2.5 clks (DRAM) / 3 clks (SDRAM)
;//                 <2=> 3.5 clks (DRAM) / 4 clks (SDRAM)
;//                 <3=> 4.5 clks (DRAM) / Rsrvd (SDRAM)
;//     <o9.18..19> Trc: SDRAM RC Min Time
;//                 <0=> 4 clks  <1=> 5 clks  <2=> 6 clks  <3=> 7 clks
;//     <o9.16..17> Tchr: DRAM CAS Hold Time
;//                 <0=> 1 clks  <1=> 2 clks  <2=> 3 clks  <3=> 4 clks
;//     <o9.0..10>  Refresh Counter <0x0-0x07FF>
;//                 <i> Refresh Period = (2^11 - Refresh Count + 1) / MCLK
;//   </h>
BANKCON0_Val    EQU     0x00000700
BANKCON1_Val    EQU     0x00000700
BANKCON2_Val    EQU     0x00000700
BANKCON3_Val    EQU     0x00000700
BANKCON4_Val    EQU     0x00000700
BANKCON5_Val    EQU     0x00000700
BANKCON6_Val    EQU     0x00018008
BANKCON7_Val    EQU     0x00018008
BWSCON_Val      EQU     0x00000000
REFRESH_Val     EQU     0x00AC0000
BANKSIZE_Val    EQU     0x00000000
MRSRB6_Val      EQU     0x00000000
MRSRB7_Val      EQU     0x00000000

;// </e> End of MC


; I/O Ports definitions
PIO_BASE        EQU     0x01D20000      ; PIO Base Address
PCONA_OFS       EQU     0x00            ; PCONA Offset
PCONB_OFS       EQU     0x08            ; PCONB Offset
PCONC_OFS       EQU     0x10            ; PCONC Offset
PCOND_OFS       EQU     0x1C            ; PCOND Offset
PCONE_OFS       EQU     0x28            ; PCONE Offset
PCONF_OFS       EQU     0x34            ; PCONF Offset
PCONG_OFS       EQU     0x40            ; PCONG Offset
PUPC_OFS        EQU     0x18            ; PUPC Offset
PUPD_OFS        EQU     0x24            ; PUPD Offset
PUPE_OFS        EQU     0x30            ; PUPE Offset
PUPF_OFS        EQU     0x3C            ; PUPF Offset
PUPG_OFS        EQU     0x48            ; PUPG Offset
SPUCR_OFS       EQU     0x4C            ; SPUCR Offset

;// <e> I/O Configuration
PIO_SETUP       EQU     0

;//   <e> Port A
;//     <o1.0>      PA0  <0=> Output   <1=> ADDR0
;//     <o1.1>      PA1  <0=> Output   <1=> ADDR16
;//     <o1.2>      PA2  <0=> Output   <1=> ADDR17
;//     <o1.3>      PA3  <0=> Output   <1=> ADDR18
;//     <o1.4>      PA4  <0=> Output   <1=> ADDR19
;//     <o1.5>      PA5  <0=> Output   <1=> ADDR20
;//     <o1.6>      PA6  <0=> Output   <1=> ADDR21
;//     <o1.7>      PA7  <0=> Output   <1=> ADDR22
;//     <o1.8>      PA8  <0=> Output   <1=> ADDR23
;//     <o1.9>      PA9  <0=> Output   <1=> ADDR24
;//   </e>
PIOA_SETUP      EQU     1
PCONA_Val       EQU     0x000003FF

;//   <e> Port B
;//     <o1.0>      PB0  <0=> Output   <1=> SCKE
;//     <o1.1>      PB1  <0=> Output   <1=> CKLK
;//     <o1.2>      PB2  <0=> Output   <1=> nSCAS/nCAS2
;//     <o1.3>      PB3  <0=> Output   <1=> nSRAS/nCAS3
;//     <o1.4>      PB4  <0=> Output   <1=> nWBE2/nBE2/DQM2
;//     <o1.5>      PB5  <0=> Output   <1=> nWBE3/nBE3/DQM3
;//     <o1.6>      PB6  <0=> Output   <1=> nGCS1
;//     <o1.7>      PB7  <0=> Output   <1=> nGCS2
;//     <o1.8>      PB8  <0=> Output   <1=> nGCS3
;//     <o1.9>      PB9  <0=> Output   <1=> nGCS4
;//     <o1.10>     PB10 <0=> Output   <1=> nGCS5
;//   </e>
PIOB_SETUP      EQU     1
PCONB_Val       EQU     0x000007FF

;//   <e> Port C
;//     <o1.0..1>   PC0  <0=> Input    <1=> Output   <2=> DATA16   <3=> IISLRCK
;//     <o1.2..3>   PC1  <0=> Input    <1=> Output   <2=> DATA17   <3=> IISDO
;//     <o1.4..5>   PC2  <0=> Input    <1=> Output   <2=> DATA18   <3=> IISDI
;//     <o1.6..7>   PC3  <0=> Input    <1=> Output   <2=> DATA19   <3=> IISCLK
;//     <o1.8..9>   PC4  <0=> Input    <1=> Output   <2=> DATA20   <3=> VD7
;//     <o1.10..11> PC5  <0=> Input    <1=> Output   <2=> DATA21   <3=> VD6
;//     <o1.12..13> PC6  <0=> Input    <1=> Output   <2=> DATA22   <3=> VD5
;//     <o1.14..15> PC7  <0=> Input    <1=> Output   <2=> DATA23   <3=> VD4
;//     <o1.16..17> PC8  <0=> Input    <1=> Output   <2=> DATA24   <3=> nXDACK1
;//     <o1.18..19> PC9  <0=> Input    <1=> Output   <2=> DATA25   <3=> nXDREQ1
;//     <o1.20..21> PC10 <0=> Input    <1=> Output   <2=> DATA26   <3=> nRTS1
;//     <o1.22..23> PC11 <0=> Input    <1=> Output   <2=> DATA27   <3=> nCTS1
;//     <o1.24..25> PC12 <0=> Input    <1=> Output   <2=> DATA28   <3=> TxD1
;//     <o1.26..27> PC13 <0=> Input    <1=> Output   <2=> DATA29   <3=> RxD1
;//     <o1.28..29> PC14 <0=> Input    <1=> Output   <2=> DATA30   <3=> nRTS0
;//     <o1.30..31> PC15 <0=> Input    <1=> Output   <2=> DATA31   <3=> nCTS0
;//     <h> Pull-up Resistors
;//       <o2.0>    PC0 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.1>    PC1 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.2>    PC2 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.3>    PC3 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.4>    PC4 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.5>    PC5 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.6>    PC6 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.7>    PC7 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.8>    PC8 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.9>    PC9 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.10>   PC10 Pull-up       <0=> Enabled  <1=> Disabled
;//       <o2.11>   PC11 Pull-up       <0=> Enabled  <1=> Disabled
;//       <o2.12>   PC12 Pull-up       <0=> Enabled  <1=> Disabled
;//       <o2.13>   PC13 Pull-up       <0=> Enabled  <1=> Disabled
;//       <o2.14>   PC14 Pull-up       <0=> Enabled  <1=> Disabled
;//       <o2.15>   PC15 Pull-up       <0=> Enabled  <1=> Disabled
;//     </h>
;//   </e>
PIOC_SETUP      EQU     1
PCONC_Val       EQU     0xAAAAAAAA
PUPC_Val        EQU     0x00000000

;//   <e> Port D
;//     <o1.0..1>   PD0  <0=> Input    <1=> Output   <2=> VD0      <3=> Reserved
;//     <o1.2..3>   PD1  <0=> Input    <1=> Output   <2=> VD1      <3=> Reserved
;//     <o1.4..5>   PD2  <0=> Input    <1=> Output   <2=> VD2      <3=> Reserved
;//     <o1.6..7>   PD3  <0=> Input    <1=> Output   <2=> VD3      <3=> Reserved
;//     <o1.8..9>   PD4  <0=> Input    <1=> Output   <2=> VCLK     <3=> Reserved
;//     <o1.10..11> PD5  <0=> Input    <1=> Output   <2=> VLINE    <3=> Reserved
;//     <o1.12..13> PD6  <0=> Input    <1=> Output   <2=> VM       <3=> Reserved
;//     <o1.14..15> PD7  <0=> Input    <1=> Output   <2=> VFRAME   <3=> Reserved
;//     <h> Pull-up Resistors
;//       <o2.0>    PD0 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.1>    PD1 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.2>    PD2 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.3>    PD3 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.4>    PD4 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.5>    PD5 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.6>    PD6 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.7>    PD7 Pull-up        <0=> Enabled  <1=> Disabled
;//     </h>
;//   </e>
PIOD_SETUP      EQU     1
PCOND_Val       EQU     0x00000000
PUPD_Val        EQU     0x00000000

;//   <e> Port E
;//     <o1.0..1>   PE0  <0=> Input    <1=> Output   <2=> Fpllo    <3=> Fout
;//     <o1.2..3>   PE1  <0=> Input    <1=> Output   <2=> TxD0     <3=> Reserved
;//     <o1.4..5>   PE2  <0=> Input    <1=> Output   <2=> RxD0     <3=> Reserved
;//     <o1.6..7>   PE3  <0=> Input    <1=> Output   <2=> TOUT0    <3=> Reserved
;//     <o1.8..9>   PE4  <0=> Input    <1=> Output   <2=> TOUT1    <3=> TCLK
;//     <o1.10..11> PE5  <0=> Input    <1=> Output   <2=> TOUT2    <3=> TCLK
;//     <o1.12..13> PE6  <0=> Input    <1=> Output   <2=> TOUT3    <3=> VD6
;//     <o1.14..15> PE7  <0=> Input    <1=> Output   <2=> TOUT4    <3=> VD7
;//     <o1.16..17> PE8  <0=> Input    <1=> Output   <2=> CODECLK  <3=> Reserved
;//     <h> Pull-up Resistors
;//       <o2.0>    PE0 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.1>    PE1 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.2>    PE2 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.3>    PE3 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.4>    PE4 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.5>    PE5 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.6>    PE6 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.7>    PE7 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.8>    PE8 Pull-up        <0=> Enabled  <1=> Disabled
;//     </h>
;//   </e>
PIOE_SETUP      EQU     1
PCONE_Val       EQU     0x00000000
PUPE_Val        EQU     0x00000000

;//   <e> Port F
;//     <o1.0..1>   PF0  <0=> Input    <1=> Output   <2=> IICSCL   <3=> Reserved
;//     <o1.2..3>   PF1  <0=> Input    <1=> Output   <2=> IICSDA   <3=> Reserved
;//     <o1.4..5>   PF2  <0=> Input    <1=> Output   <2=> nWAIT    <3=> Reserved
;//     <o1.6..7>   PF3  <0=> Input    <1=> Output   <2=> nXBACK   <3=> nXDACK0
;//     <o1.8..9>   PF4  <0=> Input    <1=> Output   <2=> nXBREQ   <3=> nXDREQ0
;//     <o1.10..12> PF5  <0=> Input    <1=> Output   <2=> nRTS1    <3=> SIOTxD
;//                      <4=> IISLRCK  <5=> Reserved <6=> Reserved <7=> Reserved
;//     <o1.13..15> PF6  <0=> Input    <1=> Output   <2=> TxD1     <3=> SIORDY
;//                      <4=> IISDO    <5=> Reserved <6=> Reserved <7=> Reserved
;//     <o1.16..18> PF7  <0=> Input    <1=> Output   <2=> RxD1     <3=> SIORxD
;//                      <4=> IISDI    <5=> Reserved <6=> Reserved <7=> Reserved
;//     <o1.19..21> PF8  <0=> Input    <1=> Output   <2=> nCTS1    <3=> SIOCLK
;//                      <4=> IISCLK   <5=> Reserved <6=> Reserved <7=> Reserved
;//     <h> Pull-up Resistors
;//       <o2.0>    PF0 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.1>    PF1 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.2>    PF2 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.3>    PF3 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.4>    PF4 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.5>    PF5 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.6>    PF6 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.7>    PF7 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.8>    PF8 Pull-up        <0=> Enabled  <1=> Disabled
;//     </h>
;//   </e>
PIOF_SETUP      EQU     1
PCONF_Val       EQU     0x00000000
PUPF_Val        EQU     0x00000000

;//   <e> Port G
;//     <o1.0..1>   PG0  <0=> Input    <1=> Output   <2=> VD4      <3=> EINT0
;//     <o1.2..3>   PG1  <0=> Input    <1=> Output   <2=> VD5      <3=> EINT1
;//     <o1.4..5>   PG2  <0=> Input    <1=> Output   <2=> nCTS0    <3=> EINT2
;//     <o1.6..7>   PG3  <0=> Input    <1=> Output   <2=> nRTS0    <3=> EINT3
;//     <o1.8..9>   PG4  <0=> Input    <1=> Output   <2=> IISCLK   <3=> EINT4
;//     <o1.10..11> PG5  <0=> Input    <1=> Output   <2=> IISDI    <3=> EINT5
;//     <o1.12..13> PG6  <0=> Input    <1=> Output   <2=> IISDO    <3=> EINT6
;//     <o1.14..15> PG7  <0=> Input    <1=> Output   <2=> IISLRCK  <3=> EINT7
;//     <h> Pull-up Resistors
;//       <o2.0>    PG0 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.1>    PG1 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.2>    PG2 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.3>    PG3 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.4>    PG4 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.5>    PG5 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.6>    PG6 Pull-up        <0=> Enabled  <1=> Disabled
;//       <o2.7>    PG7 Pull-up        <0=> Enabled  <1=> Disabled
;//     </h>
;//   </e>
PIOG_SETUP      EQU     1
PCONG_Val       EQU     0x00000000
PUPG_Val        EQU     0x00000000

;//   <e> Special Pull-up
;//     <o1.0>    SPUCR0: DATA[7:0] Pull-up Resistor    
;//               <0=> Enabled  <1=> Disabled
;//     <o1.1>    SPUCR1: DATA[15:8] Pull-up Resistor    
;//               <0=> Enabled  <1=> Disabled
;//     <o1.2>    HZ@STOP
;//               <0=> Prevoius state of PAD
;//               <1=> HZ @ Stop
;//   </e>
PSPU_SETUP      EQU     1
SPUCR_Val       EQU     0x00000004

;// </e>
  

                PRESERVE8
                

; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM


; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

Vectors         LDR     PC, Reset_Addr         
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
                NOP                            ; Reserved Vector 
                LDR     PC, IRQ_Addr
                LDR     PC, FIQ_Addr

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0                      ; Reserved Address 
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
SWI_Handler     B       SWI_Handler
PAbt_Handler    B       PAbt_Handler
DAbt_Handler    B       DAbt_Handler
FIQ_Handler     B       FIQ_Handler


; CPU Wrapper and Bus Priorities Configuration
                IF      SYS_SETUP <> 0
SYS_CFG
                DCD     CPUW_BASE
                DCD     BUSP_BASE        
                DCD     SYSCFG_Val
                DCD     NCACHBE0_Val
                DCD     NCACHBE1_Val
                DCD     SBUSCON_Val
                ENDIF


; Memory Controller Configuration
                IF      MC_SETUP <> 0
MC_CFG
                DCD     BWSCON_Val
                DCD     BANKCON0_Val
                DCD     BANKCON1_Val
                DCD     BANKCON2_Val
                DCD     BANKCON3_Val
                DCD     BANKCON4_Val
                DCD     BANKCON5_Val
                DCD     BANKCON6_Val
                DCD     BANKCON7_Val
                DCD     REFRESH_Val
                DCD     BANKSIZE_Val
                DCD     MRSRB6_Val
                DCD     MRSRB7_Val
                ENDIF


; Clock Management Configuration
                IF      CLK_SETUP <> 0
CLK_CFG
                DCD     CLK_BASE        
                DCD     PLLCON_Val
                DCD     CLKCON_Val
                DCD     CLKSLOW_Val
                DCD     LOCKTIME_Val
                ENDIF


; I/O Configuration
                IF      PIO_SETUP <> 0
PIO_CFG        
                DCD     PCONA_Val
                DCD     PCONB_Val
                DCD     PCONC_Val
                DCD     PCOND_Val
                DCD     PCONE_Val
                DCD     PCONF_Val
                DCD     PCONG_Val
                DCD     PUPC_Val
                DCD     PUPD_Val
                DCD     PUPE_Val
                DCD     PUPF_Val
                DCD     PUPG_Val
                DCD     SPUCR_Val
                ENDIF


; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler   


                IF      SYS_SETUP <> 0
                ADR     R8, SYS_CFG
                LDMIA   R8, {R0-R5}
                STMIA   R0, {R2-R4}
                STR     R5, [R1]
                ENDIF


                IF      MC_SETUP <> 0
                ADR     R14, MC_CFG
                LDMIA   R14, {R0-R12}
                LDR     R14, =MC_BASE
                STMIA   R14, {R0-R12}
                ENDIF


                IF      CLK_SETUP <> 0
                ADR     R8, CLK_CFG
                LDMIA   R8, {R0-R4}
                STR     R4, [R0, #LOCKTIME_OFS]
                STR     R1, [R0, #PLLCON_OFS]
                STR     R3, [R0, #CLKSLOW_OFS]
                STR     R2, [R0, #CLKCON_OFS]
                ENDIF


                IF      WT_SETUP <> 0
                LDR     R0, =WT_BASE
                LDR     R1, =WTCON_Val
                LDR     R2, =WTDAT_Val
                STR     R2, [R0, #WTCNT_OFS]
                STR     R2, [R0, #WTDAT_OFS]
                STR     R1, [R0, #WTCON_OFS]
                ENDIF


                IF      PIO_SETUP <> 0
                ADR     R14, PIO_CFG
                LDMIA   R14, {R0-R12}
                LDR     R14, =PIO_BASE

                IF      PIOA_SETUP <> 0
                STR     R0, [R14, #PCONA_OFS]
                ENDIF

                IF      PIOB_SETUP <> 0
                STR     R1, [R14, #PCONB_OFS]
                ENDIF

                IF      PIOC_SETUP <> 0
                STR     R2, [R14, #PCONC_OFS]
                STR     R7, [R14, #PUPC_OFS]
                ENDIF

                IF      PIOD_SETUP <> 0
                STR     R3, [R14, #PCOND_OFS]
                STR     R8, [R14, #PUPD_OFS]
                ENDIF

                IF      PIOE_SETUP <> 0
                STR     R4, [R14, #PCONE_OFS]
                STR     R9, [R14, #PUPE_OFS]
                ENDIF

                IF      PIOF_SETUP <> 0
                STR     R5, [R14, #PCONF_OFS]
                STR     R10,[R14, #PUPF_OFS]
                ENDIF

                IF      PIOG_SETUP <> 0
                STR     R6, [R14, #PCONG_OFS]
                STR     R11,[R14, #PUPG_OFS]
                ENDIF

                IF      PSPU_SETUP <> 0
                STR     R12,[R14, #SPUCR_OFS]
                ENDIF

                ENDIF


; Setup Stack for each mode

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
                IF      :DEF:__MICROLIB

                EXPORT __initial_sp

                ELSE

                ; MOV     SP, R0
                ; SUB     SL, SP, #USR_Stack_Size

                ENDIF


; Enter the C code

                IMPORT  __main
                LDR     R0, =__main
                BX      R0

				IMPORT rt_interrupt_enter
				IMPORT rt_interrupt_leave
				IMPORT rt_thread_switch_interrupt_flag
				IMPORT rt_interrupt_from_thread
				IMPORT rt_interrupt_to_thread
				IMPORT rt_hw_trap_irq
				
IRQ_Handler		PROC
				EXPORT IRQ_Handler
				STMFD	sp!, {r0-r12,lr}
				BL	rt_interrupt_enter
				BL	rt_hw_trap_irq
				BL	rt_interrupt_leave

				; if rt_thread_switch_interrupt_flag set, jump to
				; rt_hw_context_switch_interrupt_do and don't return
				LDR	r0, =rt_thread_switch_interrupt_flag
				LDR	r1, [r0]
				CMP	r1, #1
				BEQ	rt_hw_context_switch_interrupt_do

				LDMFD	sp!, {r0-r12,lr}
				SUBS	pc, lr, #4
				ENDP

; /*
; * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
; */
rt_hw_context_switch_interrupt_do	PROC
				EXPORT rt_hw_context_switch_interrupt_do
				MOV		r1,  #0			; clear flag
				STR		r1,  [r0]

				LDMFD	sp!, {r0-r12,lr}; reload saved registers
				STMFD	sp!, {r0-r3}	; save r0-r3
				MOV		r1,  sp
				ADD		sp,  sp, #16	; restore sp
				SUB		r2,  lr, #4		; save old task's pc to r2

				MRS		r3,  spsr		; get cpsr of interrupt thread

				; switch to SVC mode and no interrupt
                MSR     cpsr_c, #I_Bit|F_Bit|Mode_SVC

				STMFD	sp!, {r2}		; push old task's pc
				STMFD	sp!, {r4-r12,lr}; push old task's lr,r12-r4
				MOV		r4,  r1			; Special optimised code below
				MOV		r5,  r3
				LDMFD	r4!, {r0-r3}
				STMFD	sp!, {r0-r3}	; push old task's r3-r0
				STMFD	sp!, {r5}		; push old task's cpsr
				MRS		r4,  spsr
				STMFD	sp!, {r4}		; push old task's spsr

				LDR		r4,  =rt_interrupt_from_thread
				LDR		r5,  [r4]
				STR		sp,  [r5]		; store sp in preempted tasks's TCB

				LDR		r6,  =rt_interrupt_to_thread
				LDR		r6,  [r6]
				LDR		sp,  [r6]		; get new task's stack pointer
			
				LDMFD	sp!, {r4}		; pop new task's spsr
				MSR		spsr_cxsf, r4
				LDMFD	sp!, {r4}		; pop new task's psr
				MSR		cpsr_cxsf, r4

				LDMFD	sp!, {r0-r12,lr,pc}	; pop new task's r0-r12,lr & pc
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
