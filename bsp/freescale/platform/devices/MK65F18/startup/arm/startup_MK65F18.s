; * ---------------------------------------------------------------------------------------
; *  @file:    startup_MK65F18.s
; *  @purpose: CMSIS Cortex-M4 Core Device Startup File
; *            MK65F18
; *  @version: 3.0
; *  @date:    2015-3-25
; *  @build:   b150602
; * ---------------------------------------------------------------------------------------
; *
; * Copyright (c) 1997 - 2015 , Freescale Semiconductor, Inc.
; * All rights reserved.
; *
; * Redistribution and use in source and binary forms, with or without modification,
; * are permitted provided that the following conditions are met:
; *
; * o Redistributions of source code must retain the above copyright notice, this list
; *   of conditions and the following disclaimer.
; *
; * o Redistributions in binary form must reproduce the above copyright notice, this
; *   list of conditions and the following disclaimer in the documentation and/or
; *   other materials provided with the distribution.
; *
; * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
; *   contributors may be used to endorse or promote products derived from this
; *   software without specific prior written permission.
; *
; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; *
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
                IMPORT  |Image$$ARM_LIB_STACK$$ZI$$Limit|

__Vectors       DCD     |Image$$ARM_LIB_STACK$$ZI$$Limit| ; Top of Stack
                DCD     Reset_Handler  ; Reset Handler
                DCD     NMI_Handler                         ;NMI Handler
                DCD     HardFault_Handler                   ;Hard Fault Handler
                DCD     MemManage_Handler                   ;MPU Fault Handler
                DCD     BusFault_Handler                    ;Bus Fault Handler
                DCD     UsageFault_Handler                  ;Usage Fault Handler
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     SVC_Handler                         ;SVCall Handler
                DCD     DebugMon_Handler                    ;Debug Monitor Handler
                DCD     0                                   ;Reserved
                DCD     PendSV_Handler                      ;PendSV Handler
                DCD     SysTick_Handler                     ;SysTick Handler

                                                            ;External Interrupts
                DCD     DMA0_DMA16_IRQHandler               ;DMA Channel 0, 16 Transfer Complete
                DCD     DMA1_DMA17_IRQHandler               ;DMA Channel 1, 17 Transfer Complete
                DCD     DMA2_DMA18_IRQHandler               ;DMA Channel 2, 18 Transfer Complete
                DCD     DMA3_DMA19_IRQHandler               ;DMA Channel 3, 19 Transfer Complete
                DCD     DMA4_DMA20_IRQHandler               ;DMA Channel 4, 20 Transfer Complete
                DCD     DMA5_DMA21_IRQHandler               ;DMA Channel 5, 21 Transfer Complete
                DCD     DMA6_DMA22_IRQHandler               ;DMA Channel 6, 22 Transfer Complete
                DCD     DMA7_DMA23_IRQHandler               ;DMA Channel 7, 23 Transfer Complete
                DCD     DMA8_DMA24_IRQHandler               ;DMA Channel 8, 24 Transfer Complete
                DCD     DMA9_DMA25_IRQHandler               ;DMA Channel 9, 25 Transfer Complete
                DCD     DMA10_DMA26_IRQHandler              ;DMA Channel 10, 26 Transfer Complete
                DCD     DMA11_DMA27_IRQHandler              ;DMA Channel 11, 27 Transfer Complete
                DCD     DMA12_DMA28_IRQHandler              ;DMA Channel 12, 28 Transfer Complete
                DCD     DMA13_DMA29_IRQHandler              ;DMA Channel 13, 29 Transfer Complete
                DCD     DMA14_DMA30_IRQHandler              ;DMA Channel 14, 30 Transfer Complete
                DCD     DMA15_DMA31_IRQHandler              ;DMA Channel 15, 31 Transfer Complete
                DCD     DMA_Error_IRQHandler                ;DMA Error Interrupt
                DCD     MCM_IRQHandler                      ;Normal Interrupt
                DCD     FTFE_IRQHandler                     ;FTFE Command complete interrupt
                DCD     Read_Collision_IRQHandler           ;Read Collision Interrupt
                DCD     LVD_LVW_IRQHandler                  ;Low Voltage Detect, Low Voltage Warning
                DCD     LLWU_IRQHandler                     ;Low Leakage Wakeup Unit
                DCD     WDOG_EWM_IRQHandler                 ;WDOG Interrupt
                DCD     RNG_IRQHandler                      ;RNG Interrupt
                DCD     I2C0_IRQHandler                     ;I2C0 interrupt
                DCD     I2C1_IRQHandler                     ;I2C1 interrupt
                DCD     SPI0_IRQHandler                     ;SPI0 Interrupt
                DCD     SPI1_IRQHandler                     ;SPI1 Interrupt
                DCD     I2S0_Tx_IRQHandler                  ;I2S0 transmit interrupt
                DCD     I2S0_Rx_IRQHandler                  ;I2S0 receive interrupt
                DCD     Reserved46_IRQHandler               ;Reserved interrupt 46
                DCD     UART0_RX_TX_IRQHandler              ;UART0 Receive/Transmit interrupt
                DCD     UART0_ERR_IRQHandler                ;UART0 Error interrupt
                DCD     UART1_RX_TX_IRQHandler              ;UART1 Receive/Transmit interrupt
                DCD     UART1_ERR_IRQHandler                ;UART1 Error interrupt
                DCD     UART2_RX_TX_IRQHandler              ;UART2 Receive/Transmit interrupt
                DCD     UART2_ERR_IRQHandler                ;UART2 Error interrupt
                DCD     UART3_RX_TX_IRQHandler              ;UART3 Receive/Transmit interrupt
                DCD     UART3_ERR_IRQHandler                ;UART3 Error interrupt
                DCD     ADC0_IRQHandler                     ;ADC0 interrupt
                DCD     CMP0_IRQHandler                     ;CMP0 interrupt
                DCD     CMP1_IRQHandler                     ;CMP1 interrupt
                DCD     FTM0_IRQHandler                     ;FTM0 fault, overflow and channels interrupt
                DCD     FTM1_IRQHandler                     ;FTM1 fault, overflow and channels interrupt
                DCD     FTM2_IRQHandler                     ;FTM2 fault, overflow and channels interrupt
                DCD     CMT_IRQHandler                      ;CMT interrupt
                DCD     RTC_IRQHandler                      ;RTC interrupt
                DCD     RTC_Seconds_IRQHandler              ;RTC seconds interrupt
                DCD     PIT0_IRQHandler                     ;PIT timer channel 0 interrupt
                DCD     PIT1_IRQHandler                     ;PIT timer channel 1 interrupt
                DCD     PIT2_IRQHandler                     ;PIT timer channel 2 interrupt
                DCD     PIT3_IRQHandler                     ;PIT timer channel 3 interrupt
                DCD     PDB0_IRQHandler                     ;PDB0 Interrupt
                DCD     USB0_IRQHandler                     ;USB0 interrupt
                DCD     USBDCD_IRQHandler                   ;USBDCD Interrupt
                DCD     Reserved71_IRQHandler               ;Reserved interrupt 71
                DCD     DAC0_IRQHandler                     ;DAC0 interrupt
                DCD     MCG_IRQHandler                      ;MCG Interrupt
                DCD     LPTMR0_IRQHandler                   ;LPTimer interrupt
                DCD     PORTA_IRQHandler                    ;Port A interrupt
                DCD     PORTB_IRQHandler                    ;Port B interrupt
                DCD     PORTC_IRQHandler                    ;Port C interrupt
                DCD     PORTD_IRQHandler                    ;Port D interrupt
                DCD     PORTE_IRQHandler                    ;Port E interrupt
                DCD     SWI_IRQHandler                      ;Software interrupt
                DCD     SPI2_IRQHandler                     ;SPI2 Interrupt
                DCD     UART4_RX_TX_IRQHandler              ;UART4 Receive/Transmit interrupt
                DCD     UART4_ERR_IRQHandler                ;UART4 Error interrupt
                DCD     Reserved84_IRQHandler               ;Reserved interrupt 84
                DCD     Reserved85_IRQHandler               ;Reserved interrupt 85
                DCD     CMP2_IRQHandler                     ;CMP2 interrupt
                DCD     FTM3_IRQHandler                     ;FTM3 fault, overflow and channels interrupt
                DCD     DAC1_IRQHandler                     ;DAC1 interrupt
                DCD     ADC1_IRQHandler                     ;ADC1 interrupt
                DCD     I2C2_IRQHandler                     ;I2C2 interrupt
                DCD     CAN0_ORed_Message_buffer_IRQHandler ;CAN0 OR'd message buffers interrupt
                DCD     CAN0_Bus_Off_IRQHandler             ;CAN0 bus off interrupt
                DCD     CAN0_Error_IRQHandler               ;CAN0 error interrupt
                DCD     CAN0_Tx_Warning_IRQHandler          ;CAN0 Tx warning interrupt
                DCD     CAN0_Rx_Warning_IRQHandler          ;CAN0 Rx warning interrupt
                DCD     CAN0_Wake_Up_IRQHandler             ;CAN0 wake up interrupt
                DCD     SDHC_IRQHandler                     ;SDHC interrupt
                DCD     ENET_1588_Timer_IRQHandler          ;Ethernet MAC IEEE 1588 Timer Interrupt
                DCD     ENET_Transmit_IRQHandler            ;Ethernet MAC Transmit Interrupt
                DCD     ENET_Receive_IRQHandler             ;Ethernet MAC Receive Interrupt
                DCD     ENET_Error_IRQHandler               ;Ethernet MAC Error and miscelaneous Interrupt
                DCD     LPUART0_IRQHandler                  ;LPUART0 status/error interrupt
                DCD     TSI0_IRQHandler                     ;TSI0 interrupt
                DCD     TPM1_IRQHandler                     ;TPM1 fault, overflow and channels interrupt
                DCD     TPM2_IRQHandler                     ;TPM2 fault, overflow and channels interrupt
                DCD     USBHSDCD_IRQHandler                 ;USBHSDCD, USBHS Phy Interrupt
                DCD     I2C3_IRQHandler                     ;I2C3 interrupt
                DCD     CMP3_IRQHandler                     ;CMP3 interrupt
                DCD     USBHS_IRQHandler                    ;USB high speed OTG interrupt
                DCD     CAN1_ORed_Message_buffer_IRQHandler ;CAN1 OR'd message buffers interrupt
                DCD     CAN1_Bus_Off_IRQHandler             ;CAN1 bus off interrupt
                DCD     CAN1_Error_IRQHandler               ;CAN1 error interrupt
                DCD     CAN1_Tx_Warning_IRQHandler          ;CAN1 Tx warning interrupt
                DCD     CAN1_Rx_Warning_IRQHandler          ;CAN1 Rx warning interrupt
                DCD     CAN1_Wake_Up_IRQHandler             ;CAN1 wake up interrupt
                DCD     DefaultISR                          ;116
                DCD     DefaultISR                          ;117
                DCD     DefaultISR                          ;118
                DCD     DefaultISR                          ;119
                DCD     DefaultISR                          ;120
                DCD     DefaultISR                          ;121
                DCD     DefaultISR                          ;122
                DCD     DefaultISR                          ;123
                DCD     DefaultISR                          ;124
                DCD     DefaultISR                          ;125
                DCD     DefaultISR                          ;126
                DCD     DefaultISR                          ;127
                DCD     DefaultISR                          ;128
                DCD     DefaultISR                          ;129
                DCD     DefaultISR                          ;130
                DCD     DefaultISR                          ;131
                DCD     DefaultISR                          ;132
                DCD     DefaultISR                          ;133
                DCD     DefaultISR                          ;134
                DCD     DefaultISR                          ;135
                DCD     DefaultISR                          ;136
                DCD     DefaultISR                          ;137
                DCD     DefaultISR                          ;138
                DCD     DefaultISR                          ;139
                DCD     DefaultISR                          ;140
                DCD     DefaultISR                          ;141
                DCD     DefaultISR                          ;142
                DCD     DefaultISR                          ;143
                DCD     DefaultISR                          ;144
                DCD     DefaultISR                          ;145
                DCD     DefaultISR                          ;146
                DCD     DefaultISR                          ;147
                DCD     DefaultISR                          ;148
                DCD     DefaultISR                          ;149
                DCD     DefaultISR                          ;150
                DCD     DefaultISR                          ;151
                DCD     DefaultISR                          ;152
                DCD     DefaultISR                          ;153
                DCD     DefaultISR                          ;154
                DCD     DefaultISR                          ;155
                DCD     DefaultISR                          ;156
                DCD     DefaultISR                          ;157
                DCD     DefaultISR                          ;158
                DCD     DefaultISR                          ;159
                DCD     DefaultISR                          ;160
                DCD     DefaultISR                          ;161
                DCD     DefaultISR                          ;162
                DCD     DefaultISR                          ;163
                DCD     DefaultISR                          ;164
                DCD     DefaultISR                          ;165
                DCD     DefaultISR                          ;166
                DCD     DefaultISR                          ;167
                DCD     DefaultISR                          ;168
                DCD     DefaultISR                          ;169
                DCD     DefaultISR                          ;170
                DCD     DefaultISR                          ;171
                DCD     DefaultISR                          ;172
                DCD     DefaultISR                          ;173
                DCD     DefaultISR                          ;174
                DCD     DefaultISR                          ;175
                DCD     DefaultISR                          ;176
                DCD     DefaultISR                          ;177
                DCD     DefaultISR                          ;178
                DCD     DefaultISR                          ;179
                DCD     DefaultISR                          ;180
                DCD     DefaultISR                          ;181
                DCD     DefaultISR                          ;182
                DCD     DefaultISR                          ;183
                DCD     DefaultISR                          ;184
                DCD     DefaultISR                          ;185
                DCD     DefaultISR                          ;186
                DCD     DefaultISR                          ;187
                DCD     DefaultISR                          ;188
                DCD     DefaultISR                          ;189
                DCD     DefaultISR                          ;190
                DCD     DefaultISR                          ;191
                DCD     DefaultISR                          ;192
                DCD     DefaultISR                          ;193
                DCD     DefaultISR                          ;194
                DCD     DefaultISR                          ;195
                DCD     DefaultISR                          ;196
                DCD     DefaultISR                          ;197
                DCD     DefaultISR                          ;198
                DCD     DefaultISR                          ;199
                DCD     DefaultISR                          ;200
                DCD     DefaultISR                          ;201
                DCD     DefaultISR                          ;202
                DCD     DefaultISR                          ;203
                DCD     DefaultISR                          ;204
                DCD     DefaultISR                          ;205
                DCD     DefaultISR                          ;206
                DCD     DefaultISR                          ;207
                DCD     DefaultISR                          ;208
                DCD     DefaultISR                          ;209
                DCD     DefaultISR                          ;210
                DCD     DefaultISR                          ;211
                DCD     DefaultISR                          ;212
                DCD     DefaultISR                          ;213
                DCD     DefaultISR                          ;214
                DCD     DefaultISR                          ;215
                DCD     DefaultISR                          ;216
                DCD     DefaultISR                          ;217
                DCD     DefaultISR                          ;218
                DCD     DefaultISR                          ;219
                DCD     DefaultISR                          ;220
                DCD     DefaultISR                          ;221
                DCD     DefaultISR                          ;222
                DCD     DefaultISR                          ;223
                DCD     DefaultISR                          ;224
                DCD     DefaultISR                          ;225
                DCD     DefaultISR                          ;226
                DCD     DefaultISR                          ;227
                DCD     DefaultISR                          ;228
                DCD     DefaultISR                          ;229
                DCD     DefaultISR                          ;230
                DCD     DefaultISR                          ;231
                DCD     DefaultISR                          ;232
                DCD     DefaultISR                          ;233
                DCD     DefaultISR                          ;234
                DCD     DefaultISR                          ;235
                DCD     DefaultISR                          ;236
                DCD     DefaultISR                          ;237
                DCD     DefaultISR                          ;238
                DCD     DefaultISR                          ;239
                DCD     DefaultISR                          ;240
                DCD     DefaultISR                          ;241
                DCD     DefaultISR                          ;242
                DCD     DefaultISR                          ;243
                DCD     DefaultISR                          ;244
                DCD     DefaultISR                          ;245
                DCD     DefaultISR                          ;246
                DCD     DefaultISR                          ;247
                DCD     DefaultISR                          ;248
                DCD     DefaultISR                          ;249
                DCD     DefaultISR                          ;250
                DCD     DefaultISR                          ;251
                DCD     DefaultISR                          ;252
                DCD     DefaultISR                          ;253
                DCD     DefaultISR                          ;254
                DCD     0xFFFFFFFF                          ; Reserved for user TRIM value
__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

; <h> Flash Configuration
;   <i> 16-byte flash configuration field that stores default protection settings (loaded on reset)
;   <i> and security information that allows the MCU to restrict access to the FTFL module.
;   <h> Backdoor Comparison Key
;     <o0>  Backdoor Comparison Key 0.  <0x0-0xFF:2>
;     <o1>  Backdoor Comparison Key 1.  <0x0-0xFF:2>
;     <o2>  Backdoor Comparison Key 2.  <0x0-0xFF:2>
;     <o3>  Backdoor Comparison Key 3.  <0x0-0xFF:2>
;     <o4>  Backdoor Comparison Key 4.  <0x0-0xFF:2>
;     <o5>  Backdoor Comparison Key 5.  <0x0-0xFF:2>
;     <o6>  Backdoor Comparison Key 6.  <0x0-0xFF:2>
;     <o7>  Backdoor Comparison Key 7.  <0x0-0xFF:2>
BackDoorK0      EQU     0xFF
BackDoorK1      EQU     0xFF
BackDoorK2      EQU     0xFF
BackDoorK3      EQU     0xFF
BackDoorK4      EQU     0xFF
BackDoorK5      EQU     0xFF
BackDoorK6      EQU     0xFF
BackDoorK7      EQU     0xFF
;   </h>
;   <h> Program flash protection bytes (FPROT)
;     <i> Each program flash region can be protected from program and erase operation by setting the associated PROT bit.
;     <i> Each bit protects a 1/32 region of the program flash memory.
;     <h> FPROT0
;       <i> Program Flash Region Protect Register 0
;       <i> 1/32 - 8/32 region
;       <o.0>   FPROT0.0
;       <o.1>   FPROT0.1
;       <o.2>   FPROT0.2
;       <o.3>   FPROT0.3
;       <o.4>   FPROT0.4
;       <o.5>   FPROT0.5
;       <o.6>   FPROT0.6
;       <o.7>   FPROT0.7
nFPROT0         EQU     0x00
FPROT0          EQU     nFPROT0:EOR:0xFF
;     </h>
;     <h> FPROT1
;       <i> Program Flash Region Protect Register 1
;       <i> 9/32 - 16/32 region
;       <o.0>   FPROT1.0
;       <o.1>   FPROT1.1
;       <o.2>   FPROT1.2
;       <o.3>   FPROT1.3
;       <o.4>   FPROT1.4
;       <o.5>   FPROT1.5
;       <o.6>   FPROT1.6
;       <o.7>   FPROT1.7
nFPROT1         EQU     0x00
FPROT1          EQU     nFPROT1:EOR:0xFF
;     </h>
;     <h> FPROT2
;       <i> Program Flash Region Protect Register 2
;       <i> 17/32 - 24/32 region
;       <o.0>   FPROT2.0
;       <o.1>   FPROT2.1
;       <o.2>   FPROT2.2
;       <o.3>   FPROT2.3
;       <o.4>   FPROT2.4
;       <o.5>   FPROT2.5
;       <o.6>   FPROT2.6
;       <o.7>   FPROT2.7
nFPROT2         EQU     0x00
FPROT2          EQU     nFPROT2:EOR:0xFF
;     </h>
;     <h> FPROT3
;       <i> Program Flash Region Protect Register 3
;       <i> 25/32 - 32/32 region
;       <o.0>   FPROT3.0
;       <o.1>   FPROT3.1
;       <o.2>   FPROT3.2
;       <o.3>   FPROT3.3
;       <o.4>   FPROT3.4
;       <o.5>   FPROT3.5
;       <o.6>   FPROT3.6
;       <o.7>   FPROT3.7
nFPROT3         EQU     0x00
FPROT3          EQU     nFPROT3:EOR:0xFF
;     </h>
;   </h>
;   <h> Data flash protection byte (FDPROT)
;     <i> Each bit protects a 1/8 region of the data flash memory.
;     <i> (Program flash only devices: Reserved)
;       <o.0>   FDPROT.0
;       <o.1>   FDPROT.1
;       <o.2>   FDPROT.2
;       <o.3>   FDPROT.3
;       <o.4>   FDPROT.4
;       <o.5>   FDPROT.5
;       <o.6>   FDPROT.6
;       <o.7>   FDPROT.7
nFDPROT         EQU     0x00
FDPROT          EQU     nFDPROT:EOR:0xFF
;   </h>
;   <h> EEPROM protection byte (FEPROT)
;     <i> FlexNVM devices: Each bit protects a 1/8 region of the EEPROM.
;     <i> (Program flash only devices: Reserved)
;       <o.0>   FEPROT.0
;       <o.1>   FEPROT.1
;       <o.2>   FEPROT.2
;       <o.3>   FEPROT.3
;       <o.4>   FEPROT.4
;       <o.5>   FEPROT.5
;       <o.6>   FEPROT.6
;       <o.7>   FEPROT.7
nFEPROT         EQU     0x00
FEPROT          EQU     nFEPROT:EOR:0xFF
;   </h>
;   <h> Flash nonvolatile option byte (FOPT)
;     <i> Allows the user to customize the operation of the MCU at boot time.
;     <o.0> LPBOOT
;       <0=> Low-power boot
;       <1=> Normal boot
;     <o.1> EZPORT_DIS
;       <0=> EzPort operation is disabled
;       <1=> EzPort operation is enabled
;     <o.2> NMI_DIS
;       <0=> NMI interrupts are always blocked
;       <1=> NMI_b pin/interrupts reset default to enabled
FOPT          EQU     0xFF
;   </h>
;   <h> Flash security byte (FSEC)
;     <i> WARNING: If SEC field is configured as "MCU security status is secure" and MEEN field is configured as "Mass erase is disabled",
;     <i> MCU's security status cannot be set back to unsecure state since Mass erase via the debugger is blocked !!!
;     <o.0..1> SEC
;       <2=> MCU security status is unsecure
;       <3=> MCU security status is secure
;         <i> Flash Security
;     <o.2..3> FSLACC
;       <2=> Freescale factory access denied
;       <3=> Freescale factory access granted
;         <i> Freescale Failure Analysis Access Code
;     <o.4..5> MEEN
;       <2=> Mass erase is disabled
;       <3=> Mass erase is enabled
;     <o.6..7> KEYEN
;       <2=> Backdoor key access enabled
;       <3=> Backdoor key access disabled
;         <i> Backdoor Key Security Enable
FSEC          EQU     0xFE
;   </h>
; </h>
                IF      :LNOT::DEF:RAM_TARGET
                AREA    FlashConfig, DATA, READONLY
__FlashConfig
                DCB     BackDoorK0, BackDoorK1, BackDoorK2, BackDoorK3
                DCB     BackDoorK4, BackDoorK5, BackDoorK6, BackDoorK7
                DCB     FPROT0    , FPROT1    , FPROT2    , FPROT3
                DCB     FSEC      , FOPT      , FEPROT    , FDPROT
                ENDIF


                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  init_data_bss
                IMPORT  __main

                IF      :LNOT::DEF:RAM_TARGET
                REQUIRE FlashConfig
                ENDIF

                CPSID   I               ; Mask interrupts
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =init_data_bss
                BLX     R0
                CPSIE   i               ; Unmask interrupts
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler\
                PROC
                EXPORT  NMI_Handler         [WEAK]
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
                EXPORT  BusFault_Handler         [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler         [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler         [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler         [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP
Default_Handler\
                PROC
                EXPORT  DMA0_DMA16_IRQHandler         [WEAK]
                EXPORT  DMA1_DMA17_IRQHandler         [WEAK]
                EXPORT  DMA2_DMA18_IRQHandler         [WEAK]
                EXPORT  DMA3_DMA19_IRQHandler         [WEAK]
                EXPORT  DMA4_DMA20_IRQHandler         [WEAK]
                EXPORT  DMA5_DMA21_IRQHandler         [WEAK]
                EXPORT  DMA6_DMA22_IRQHandler         [WEAK]
                EXPORT  DMA7_DMA23_IRQHandler         [WEAK]
                EXPORT  DMA8_DMA24_IRQHandler         [WEAK]
                EXPORT  DMA9_DMA25_IRQHandler         [WEAK]
                EXPORT  DMA10_DMA26_IRQHandler         [WEAK]
                EXPORT  DMA11_DMA27_IRQHandler         [WEAK]
                EXPORT  DMA12_DMA28_IRQHandler         [WEAK]
                EXPORT  DMA13_DMA29_IRQHandler         [WEAK]
                EXPORT  DMA14_DMA30_IRQHandler         [WEAK]
                EXPORT  DMA15_DMA31_IRQHandler         [WEAK]
                EXPORT  DMA_Error_IRQHandler         [WEAK]
                EXPORT  MCM_IRQHandler         [WEAK]
                EXPORT  FTFE_IRQHandler         [WEAK]
                EXPORT  Read_Collision_IRQHandler         [WEAK]
                EXPORT  LVD_LVW_IRQHandler         [WEAK]
                EXPORT  LLWU_IRQHandler         [WEAK]
                EXPORT  WDOG_EWM_IRQHandler         [WEAK]
                EXPORT  RNG_IRQHandler         [WEAK]
                EXPORT  I2C0_IRQHandler         [WEAK]
                EXPORT  I2C1_IRQHandler         [WEAK]
                EXPORT  SPI0_IRQHandler         [WEAK]
                EXPORT  SPI1_IRQHandler         [WEAK]
                EXPORT  I2S0_Tx_IRQHandler         [WEAK]
                EXPORT  I2S0_Rx_IRQHandler         [WEAK]
                EXPORT  Reserved46_IRQHandler         [WEAK]
                EXPORT  UART0_RX_TX_IRQHandler         [WEAK]
                EXPORT  UART0_ERR_IRQHandler         [WEAK]
                EXPORT  UART1_RX_TX_IRQHandler         [WEAK]
                EXPORT  UART1_ERR_IRQHandler         [WEAK]
                EXPORT  UART2_RX_TX_IRQHandler         [WEAK]
                EXPORT  UART2_ERR_IRQHandler         [WEAK]
                EXPORT  UART3_RX_TX_IRQHandler         [WEAK]
                EXPORT  UART3_ERR_IRQHandler         [WEAK]
                EXPORT  ADC0_IRQHandler         [WEAK]
                EXPORT  CMP0_IRQHandler         [WEAK]
                EXPORT  CMP1_IRQHandler         [WEAK]
                EXPORT  FTM0_IRQHandler         [WEAK]
                EXPORT  FTM1_IRQHandler         [WEAK]
                EXPORT  FTM2_IRQHandler         [WEAK]
                EXPORT  CMT_IRQHandler         [WEAK]
                EXPORT  RTC_IRQHandler         [WEAK]
                EXPORT  RTC_Seconds_IRQHandler         [WEAK]
                EXPORT  PIT0_IRQHandler         [WEAK]
                EXPORT  PIT1_IRQHandler         [WEAK]
                EXPORT  PIT2_IRQHandler         [WEAK]
                EXPORT  PIT3_IRQHandler         [WEAK]
                EXPORT  PDB0_IRQHandler         [WEAK]
                EXPORT  USB0_IRQHandler         [WEAK]
                EXPORT  USBDCD_IRQHandler         [WEAK]
                EXPORT  Reserved71_IRQHandler         [WEAK]
                EXPORT  DAC0_IRQHandler         [WEAK]
                EXPORT  MCG_IRQHandler         [WEAK]
                EXPORT  LPTMR0_IRQHandler         [WEAK]
                EXPORT  PORTA_IRQHandler         [WEAK]
                EXPORT  PORTB_IRQHandler         [WEAK]
                EXPORT  PORTC_IRQHandler         [WEAK]
                EXPORT  PORTD_IRQHandler         [WEAK]
                EXPORT  PORTE_IRQHandler         [WEAK]
                EXPORT  SWI_IRQHandler         [WEAK]
                EXPORT  SPI2_IRQHandler         [WEAK]
                EXPORT  UART4_RX_TX_IRQHandler         [WEAK]
                EXPORT  UART4_ERR_IRQHandler         [WEAK]
                EXPORT  Reserved84_IRQHandler         [WEAK]
                EXPORT  Reserved85_IRQHandler         [WEAK]
                EXPORT  CMP2_IRQHandler         [WEAK]
                EXPORT  FTM3_IRQHandler         [WEAK]
                EXPORT  DAC1_IRQHandler         [WEAK]
                EXPORT  ADC1_IRQHandler         [WEAK]
                EXPORT  I2C2_IRQHandler         [WEAK]
                EXPORT  CAN0_ORed_Message_buffer_IRQHandler         [WEAK]
                EXPORT  CAN0_Bus_Off_IRQHandler         [WEAK]
                EXPORT  CAN0_Error_IRQHandler         [WEAK]
                EXPORT  CAN0_Tx_Warning_IRQHandler         [WEAK]
                EXPORT  CAN0_Rx_Warning_IRQHandler         [WEAK]
                EXPORT  CAN0_Wake_Up_IRQHandler         [WEAK]
                EXPORT  SDHC_IRQHandler         [WEAK]
                EXPORT  ENET_1588_Timer_IRQHandler         [WEAK]
                EXPORT  ENET_Transmit_IRQHandler         [WEAK]
                EXPORT  ENET_Receive_IRQHandler         [WEAK]
                EXPORT  ENET_Error_IRQHandler         [WEAK]
                EXPORT  LPUART0_IRQHandler         [WEAK]
                EXPORT  TSI0_IRQHandler         [WEAK]
                EXPORT  TPM1_IRQHandler         [WEAK]
                EXPORT  TPM2_IRQHandler         [WEAK]
                EXPORT  USBHSDCD_IRQHandler         [WEAK]
                EXPORT  I2C3_IRQHandler         [WEAK]
                EXPORT  CMP3_IRQHandler         [WEAK]
                EXPORT  USBHS_IRQHandler         [WEAK]
                EXPORT  CAN1_ORed_Message_buffer_IRQHandler         [WEAK]
                EXPORT  CAN1_Bus_Off_IRQHandler         [WEAK]
                EXPORT  CAN1_Error_IRQHandler         [WEAK]
                EXPORT  CAN1_Tx_Warning_IRQHandler         [WEAK]
                EXPORT  CAN1_Rx_Warning_IRQHandler         [WEAK]
                EXPORT  CAN1_Wake_Up_IRQHandler         [WEAK]
                EXPORT  DefaultISR         [WEAK]
DMA0_DMA16_IRQHandler
DMA1_DMA17_IRQHandler
DMA2_DMA18_IRQHandler
DMA3_DMA19_IRQHandler
DMA4_DMA20_IRQHandler
DMA5_DMA21_IRQHandler
DMA6_DMA22_IRQHandler
DMA7_DMA23_IRQHandler
DMA8_DMA24_IRQHandler
DMA9_DMA25_IRQHandler
DMA10_DMA26_IRQHandler
DMA11_DMA27_IRQHandler
DMA12_DMA28_IRQHandler
DMA13_DMA29_IRQHandler
DMA14_DMA30_IRQHandler
DMA15_DMA31_IRQHandler
DMA_Error_IRQHandler
MCM_IRQHandler
FTFE_IRQHandler
Read_Collision_IRQHandler
LVD_LVW_IRQHandler
LLWU_IRQHandler
WDOG_EWM_IRQHandler
RNG_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
I2S0_Tx_IRQHandler
I2S0_Rx_IRQHandler
Reserved46_IRQHandler
UART0_RX_TX_IRQHandler
UART0_ERR_IRQHandler
UART1_RX_TX_IRQHandler
UART1_ERR_IRQHandler
UART2_RX_TX_IRQHandler
UART2_ERR_IRQHandler
UART3_RX_TX_IRQHandler
UART3_ERR_IRQHandler
ADC0_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
FTM0_IRQHandler
FTM1_IRQHandler
FTM2_IRQHandler
CMT_IRQHandler
RTC_IRQHandler
RTC_Seconds_IRQHandler
PIT0_IRQHandler
PIT1_IRQHandler
PIT2_IRQHandler
PIT3_IRQHandler
PDB0_IRQHandler
USB0_IRQHandler
USBDCD_IRQHandler
Reserved71_IRQHandler
DAC0_IRQHandler
MCG_IRQHandler
LPTMR0_IRQHandler
PORTA_IRQHandler
PORTB_IRQHandler
PORTC_IRQHandler
PORTD_IRQHandler
PORTE_IRQHandler
SWI_IRQHandler
SPI2_IRQHandler
UART4_RX_TX_IRQHandler
UART4_ERR_IRQHandler
Reserved84_IRQHandler
Reserved85_IRQHandler
CMP2_IRQHandler
FTM3_IRQHandler
DAC1_IRQHandler
ADC1_IRQHandler
I2C2_IRQHandler
CAN0_ORed_Message_buffer_IRQHandler
CAN0_Bus_Off_IRQHandler
CAN0_Error_IRQHandler
CAN0_Tx_Warning_IRQHandler
CAN0_Rx_Warning_IRQHandler
CAN0_Wake_Up_IRQHandler
SDHC_IRQHandler
ENET_1588_Timer_IRQHandler
ENET_Transmit_IRQHandler
ENET_Receive_IRQHandler
ENET_Error_IRQHandler
LPUART0_IRQHandler
TSI0_IRQHandler
TPM1_IRQHandler
TPM2_IRQHandler
USBHSDCD_IRQHandler
I2C3_IRQHandler
CMP3_IRQHandler
USBHS_IRQHandler
CAN1_ORed_Message_buffer_IRQHandler
CAN1_Bus_Off_IRQHandler
CAN1_Error_IRQHandler
CAN1_Tx_Warning_IRQHandler
CAN1_Rx_Warning_IRQHandler
CAN1_Wake_Up_IRQHandler
DefaultISR
                B      DefaultISR
                ENDP
                  ALIGN


                END
