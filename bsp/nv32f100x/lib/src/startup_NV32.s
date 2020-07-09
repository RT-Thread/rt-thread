;/*****************************************************************************
; * @file:    startup_NV32.s
; * @purpose: CMSIS Cortex-M0plus Core Device Startup File for the
; *           NV32F100
;*
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

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

__Vectors       DCD     __initial_sp  ; Top of Stack
                DCD     Reset_Handler  ; Reset Handler
                DCD     NMI_Handler  ; NMI Handler
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     SVC_Handler  ; SVCall Handler
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     PendSV_Handler  ; PendSV Handler
                DCD     SysTick_Handler  ; SysTick Handler

                ; External Interrupts
                DCD     Reserved16_IRQHandler  ; Reserved interrupt 16
                DCD     Reserved17_IRQHandler  ; Reserved interrupt 17
                DCD     Reserved18_IRQHandler  ; Reserved interrupt 18
                DCD     Reserved19_IRQHandler  ; Reserved interrupt 19
                DCD     Reserved20_IRQHandler  ; Reserved interrupt 20
                DCD     ETMRH_IRQHandler  ; ETMRH command complete/read collision interrupt
                DCD     LVD_LVW_IRQHandler  ; Low Voltage Detect, Low Voltage Warning
                DCD     IRQ_IRQHandler  ; External interrupt
                DCD     I2C0_IRQHandler  ; I2C0 interrupt
                DCD     Reserved25_IRQHandler  ; Reserved interrupt 25
                DCD     SPI0_IRQHandler  ; SPI0 interrupt
                DCD     SPI1_IRQHandler  ; SPI1 interrupt
                DCD     UART0_IRQHandler  ; UART0 status/error interrupt
                DCD     UART1_IRQHandler  ; UART1 status/error interrupt
                DCD     UART2_IRQHandler  ; UART2 status/error interrupt
                DCD     ADC0_IRQHandler  ; ADC0 interrupt
                DCD     ACMP0_IRQHandler  ; ACMP0 interrupt
                DCD     ETM0_IRQHandler  ; ETM0 Single interrupt vector for all sources
                DCD     ETM1_IRQHandler  ; ETM1 Single interrupt vector for all sources
                DCD     ETM2_IRQHandler  ; ETM2 Single interrupt vector for all sources
                DCD     RTC_IRQHandler  ; RTC overflow
                DCD     ACMP1_IRQHandler  ; ACMP1 interrupt
                DCD     PIT_CH0_IRQHandler  ; PIT CH0 overflow
                DCD     PIT_CH1_IRQHandler  ; PIT CH1 overflow
                DCD     KBI0_IRQHandler  ; Keyboard interrupt 0
                DCD     KBI1_IRQHandler  ; Keyboard interrupt 1
                DCD     Reserved42_IRQHandler  ; Reserved interrupt 42
                DCD     ICS_IRQHandler  ; MCG interrupt
                DCD     Watchdog_IRQHandler  ; WDOG Interrupt
                DCD     Reserved45_IRQHandler  ; Reserved interrupt 45
                DCD     Reserved46_IRQHandler  ; Reserved interrupt 46
                DCD     Reserved47_IRQHandler  ; Reserved interrupt 47
__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

; <h> Flash Configuration
;   <i> 16-byte flash configuration field that stores default protection settings (loaded on reset)
;   <i> and security information that allows the MCU to restrict acces to the FTFL module.
;   <h> Backdoor Comparison Key
;     <o0>  Backdoor Key 0  <0x0-0xFF:2>
;     <o1>  Backdoor Key 1  <0x0-0xFF:2>
;     <o2>  Backdoor Key 2  <0x0-0xFF:2>
;     <o3>  Backdoor Key 3  <0x0-0xFF:2>
;     <o4>  Backdoor Key 4  <0x0-0xFF:2>
;     <o5>  Backdoor Key 5  <0x0-0xFF:2>
;     <o6>  Backdoor Key 6  <0x0-0xFF:2>
;     <o7>  Backdoor Key 7  <0x0-0xFF:2>
BackDoorK0      EQU     0xFF
BackDoorK1      EQU     0xFF
BackDoorK2      EQU     0xFF
BackDoorK3      EQU     0xFF
BackDoorK4      EQU     0xFF
BackDoorK5      EQU     0xFF
BackDoorK6      EQU     0xFF
BackDoorK7      EQU     0xFF
;   </h>
;   <h> EEPROM Protection Register (EEPROT)
;     <i> The DFPROT register defines which D-Flash sectors are protected against program and erase operations.
;     <o.7>  DPOPEN
;       <0=> Enables EEPROM memory protection
;       <1=> Disables EEPROM memory protection
;     <o.0..2> DPS
;       <0=> Flash address range: 0x00_0000 - 0x00_001F; protected size: 32 bytes
;       <1=> Flash address range: 0x00_0000 - 0x00_003F; protected size: 64 bytes
;       <2=> Flash address range: 0x00_0000 - 0x00_005F; protected size: 96 bytes
;       <3=> Flash address range: 0x00_0000 - 0x00_007F; protected size: 128 bytes
;       <4=> Flash address range: 0x00_0000 - 0x00_009F; protected size: 160 bytes
;       <5=> Flash address range: 0x00_0000 - 0x00_00BF; protected size: 192 bytes
;       <6=> Flash address range: 0x00_0000 - 0x00_00DF; protected size: 224 bytes
;       <7=> Flash address range: 0x00_0000 - 0x00_00FF; protected size: 256 bytes
EEPROT          EQU     0xFF
;     </h>
;     <h> FPROT
;       <i> P-Flash Protection Register
;       <o.7> FPOPEN
;         <0=> FPHDIS and FPLDIS bits define unprotected address ranges as specified by the corresponding FPHS and FPLS bits FPROT1.1
;         <1=> FPHDIS and FPLDIS bits enable protection for the address range specified by the corresponding FPHS and FPLS bits
;       <o.5> FPHDIS
;         <0=> Protection/Unprotection enabled
;         <1=> Protection/Unprotection disabled
;       <o.3..4> FPHS
;         <0=> Address range: 0x00_7C00-0x00_7FFF; protected size: 1 KB
;         <1=> Address range: 0x00_7800-0x00_7FFF; protected size: 2 KB
;         <2=> Address range: 0x00_7000-0x00_7FFF; protected size: 4 KB
;         <3=> Address range: 0x00_6000-0x00_7FFF; protected size: 8 KB
;       <o.5> FPLDIS
;         <0=> Protection/Unprotection enabled
;         <1=> Protection/Unprotection disabled
;       <o.3..4> FPLS
;         <0=> Address range: 0x00_0000-0x00_07FF; protected size: 2 KB
;         <1=> Address range: 0x00_0000-0x00_0FFF; protected size: 4 KB
;         <2=> Address range: 0x00_0000-0x00_1FFF; protected size: 8 KB
;         <3=> Address range: 0x00_0000-0x00_3FFF; protected size: 16 KB
FPROT         EQU     0xFF
;     </h>
;   </h>
;   <h> Flash security byte (FSEC)
;     <i> WARNING: If SEC field is configured as "MCU security status is secure" and MEEN field is configured as "Mass erase is disabled",
;     <i> MCU's security status cannot be set back to unsecure state since Mass erase via the debugger is blocked !!!
;     <o.0..1> SEC
;       <2=> MCU security status is unsecure
;       <3=> MCU security status is secure
;         <i> Flash Security
;         <i> This bits define the security state of the MCU.
;     <o.6..7> KEYEN
;       <2=> Backdoor key access enabled
;       <3=> Backdoor key access disabled
;         <i> Backdoor key Security Enable
;         <i> These bits enable and disable backdoor key access to the FTFL module.
FSEC            EQU     0xFE
;   </h>
;   <h> Flash Option Register (FOPT)
FOPT            EQU     0xFE
;   </h>
                IF      :LNOT::DEF:RAM_TARGET
                AREA    |.ARM.__at_0x400|, CODE, READONLY
                DCB     BackDoorK0, BackDoorK1, BackDoorK2, BackDoorK3
                DCB     BackDoorK4, BackDoorK5, BackDoorK6, BackDoorK7
                DCB     0xFF,       0xFF,       0xFF,       0xFF
                DCB     EEPROT,      FPROT,     FSEC,       FOPT              ;Modified by ARM.  DCB     FPROT,      EEPROT,     FOPT,       FSEC
                ENDIF

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  Reserved16_IRQHandler     [WEAK]
                EXPORT  Reserved17_IRQHandler     [WEAK]
                EXPORT  Reserved18_IRQHandler     [WEAK]
                EXPORT  Reserved19_IRQHandler     [WEAK]
                EXPORT  Reserved20_IRQHandler     [WEAK]
                EXPORT  ETMRH_IRQHandler     [WEAK]
                EXPORT  LVD_LVW_IRQHandler     [WEAK]
                EXPORT  IRQ_IRQHandler     [WEAK]
                EXPORT  I2C0_IRQHandler     [WEAK]
                EXPORT  Reserved25_IRQHandler     [WEAK]
                EXPORT  SPI0_IRQHandler     [WEAK]
                EXPORT  SPI1_IRQHandler     [WEAK]
                EXPORT  UART0_IRQHandler     [WEAK]
                EXPORT  UART1_IRQHandler     [WEAK]
                EXPORT  UART2_IRQHandler     [WEAK]
                EXPORT  ADC0_IRQHandler     [WEAK]
                EXPORT  ACMP0_IRQHandler     [WEAK]
                EXPORT  ETM0_IRQHandler     [WEAK]
                EXPORT  ETM1_IRQHandler     [WEAK]
                EXPORT  ETM2_IRQHandler     [WEAK]
                EXPORT  RTC_IRQHandler     [WEAK]
                EXPORT  ACMP1_IRQHandler     [WEAK]
                EXPORT  PIT_CH0_IRQHandler     [WEAK]
                EXPORT  PIT_CH1_IRQHandler     [WEAK]
                EXPORT  KBI0_IRQHandler     [WEAK]
                EXPORT  KBI1_IRQHandler     [WEAK]
                EXPORT  Reserved42_IRQHandler     [WEAK]
                EXPORT  ICS_IRQHandler     [WEAK]
                EXPORT  Watchdog_IRQHandler     [WEAK]
                EXPORT  Reserved45_IRQHandler     [WEAK]
                EXPORT  Reserved46_IRQHandler     [WEAK]
                EXPORT  Reserved47_IRQHandler     [WEAK]
                EXPORT  DefaultISR                      [WEAK]

Reserved16_IRQHandler
Reserved17_IRQHandler
Reserved18_IRQHandler
Reserved19_IRQHandler
Reserved20_IRQHandler
ETMRH_IRQHandler
LVD_LVW_IRQHandler
IRQ_IRQHandler
I2C0_IRQHandler
Reserved25_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
ADC0_IRQHandler
ACMP0_IRQHandler
ETM0_IRQHandler
ETM1_IRQHandler
ETM2_IRQHandler
RTC_IRQHandler
ACMP1_IRQHandler
PIT_CH0_IRQHandler
PIT_CH1_IRQHandler
KBI0_IRQHandler
KBI1_IRQHandler
Reserved42_IRQHandler
ICS_IRQHandler
Watchdog_IRQHandler
Reserved45_IRQHandler
Reserved46_IRQHandler
Reserved47_IRQHandler
DefaultISR

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
