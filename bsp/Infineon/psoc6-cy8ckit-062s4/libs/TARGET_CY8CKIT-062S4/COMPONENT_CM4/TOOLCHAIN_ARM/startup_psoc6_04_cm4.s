;/**************************************************************************//**
; * @file     startup_psoc6_04_cm4.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM4 Device Series
; * @version  V5.00
; * @date     02. March 2016
; ******************************************************************************/
;/*
; * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

                IMPORT |Image$$ARM_LIB_STACK$$ZI$$Base|
                IMPORT |Image$$ARM_LIB_STACK$$ZI$$Length|

__Vectors       DCD    |Image$$ARM_LIB_STACK$$ZI$$Base| + |Image$$ARM_LIB_STACK$$ZI$$Length| ; Top of Stack

                DCD     Reset_Handler             ; Reset Handler

                DCD     0x0000000D                            ; NMI Handler located at ROM code
                DCD     HardFault_Handler                     ; Hard Fault Handler
                DCD     MemManage_Handler                     ; MPU Fault Handler
                DCD     BusFault_Handler                      ; Bus Fault Handler
                DCD     UsageFault_Handler                    ; Usage Fault Handler
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     SVC_Handler                           ; SVCall Handler
                DCD     DebugMon_Handler                      ; Debug Monitor Handler
                DCD     0                                     ; Reserved
                DCD     PendSV_Handler                        ; PendSV Handler
                DCD     SysTick_Handler                       ; SysTick Handler

                ; External interrupts                           Description
                DCD     ioss_interrupts_gpio_0_IRQHandler     ; GPIO Port Interrupt #0
                DCD     0                                     ; Reserved
                DCD     ioss_interrupts_gpio_2_IRQHandler     ; GPIO Port Interrupt #2
                DCD     ioss_interrupts_gpio_3_IRQHandler     ; GPIO Port Interrupt #3
                DCD     0                                     ; Reserved
                DCD     ioss_interrupts_gpio_5_IRQHandler     ; GPIO Port Interrupt #5
                DCD     ioss_interrupts_gpio_6_IRQHandler     ; GPIO Port Interrupt #6
                DCD     ioss_interrupts_gpio_7_IRQHandler     ; GPIO Port Interrupt #7
                DCD     ioss_interrupts_gpio_8_IRQHandler     ; GPIO Port Interrupt #8
                DCD     ioss_interrupts_gpio_9_IRQHandler     ; GPIO Port Interrupt #9
                DCD     ioss_interrupts_gpio_10_IRQHandler    ; GPIO Port Interrupt #10
                DCD     ioss_interrupts_gpio_11_IRQHandler    ; GPIO Port Interrupt #11
                DCD     ioss_interrupts_gpio_12_IRQHandler    ; GPIO Port Interrupt #12
                DCD     0                                     ; Reserved
                DCD     ioss_interrupts_gpio_14_IRQHandler    ; GPIO Port Interrupt #14
                DCD     ioss_interrupt_gpio_IRQHandler        ; GPIO All Ports
                DCD     ioss_interrupt_vdd_IRQHandler         ; GPIO Supply Detect Interrupt
                DCD     lpcomp_interrupt_IRQHandler           ; Low Power Comparator Interrupt
                DCD     scb_6_interrupt_IRQHandler            ; Serial Communication Block #6 (DeepSleep capable)
                DCD     srss_interrupt_mcwdt_0_IRQHandler     ; Multi Counter Watchdog Timer interrupt
                DCD     srss_interrupt_mcwdt_1_IRQHandler     ; Multi Counter Watchdog Timer interrupt
                DCD     srss_interrupt_backup_IRQHandler      ; Backup domain interrupt
                DCD     srss_interrupt_IRQHandler             ; Other combined Interrupts for SRSS (LVD, WDT, CLKCAL)
                DCD     cpuss_interrupts_ipc_0_IRQHandler     ; CPUSS Inter Process Communication Interrupt #0
                DCD     cpuss_interrupts_ipc_1_IRQHandler     ; CPUSS Inter Process Communication Interrupt #1
                DCD     cpuss_interrupts_ipc_2_IRQHandler     ; CPUSS Inter Process Communication Interrupt #2
                DCD     cpuss_interrupts_ipc_3_IRQHandler     ; CPUSS Inter Process Communication Interrupt #3
                DCD     cpuss_interrupts_ipc_4_IRQHandler     ; CPUSS Inter Process Communication Interrupt #4
                DCD     cpuss_interrupts_ipc_5_IRQHandler     ; CPUSS Inter Process Communication Interrupt #5
                DCD     cpuss_interrupts_ipc_6_IRQHandler     ; CPUSS Inter Process Communication Interrupt #6
                DCD     cpuss_interrupts_ipc_7_IRQHandler     ; CPUSS Inter Process Communication Interrupt #7
                DCD     cpuss_interrupts_ipc_8_IRQHandler     ; CPUSS Inter Process Communication Interrupt #8
                DCD     cpuss_interrupts_ipc_9_IRQHandler     ; CPUSS Inter Process Communication Interrupt #9
                DCD     cpuss_interrupts_ipc_10_IRQHandler    ; CPUSS Inter Process Communication Interrupt #10
                DCD     cpuss_interrupts_ipc_11_IRQHandler    ; CPUSS Inter Process Communication Interrupt #11
                DCD     cpuss_interrupts_ipc_12_IRQHandler    ; CPUSS Inter Process Communication Interrupt #12
                DCD     cpuss_interrupts_ipc_13_IRQHandler    ; CPUSS Inter Process Communication Interrupt #13
                DCD     cpuss_interrupts_ipc_14_IRQHandler    ; CPUSS Inter Process Communication Interrupt #14
                DCD     cpuss_interrupts_ipc_15_IRQHandler    ; CPUSS Inter Process Communication Interrupt #15
                DCD     pass_interrupt_sar_0_IRQHandler       ; SAR ADC0 interrupt
                DCD     pass_interrupt_sar_1_IRQHandler       ; SAR ADC1 interrupt
                DCD     pass_interrupt_ctbs_IRQHandler        ; individual interrupt per CTB
                DCD     0                                     ; Reserved
                DCD     pass_interrupt_fifo_0_IRQHandler      ; PASS FIFO0
                DCD     pass_interrupt_fifo_1_IRQHandler      ; PASS FIFO1
                DCD     scb_0_interrupt_IRQHandler            ; Serial Communication Block #0
                DCD     scb_1_interrupt_IRQHandler            ; Serial Communication Block #1
                DCD     scb_2_interrupt_IRQHandler            ; Serial Communication Block #2
                DCD     0                                     ; Reserved
                DCD     scb_4_interrupt_IRQHandler            ; Serial Communication Block #4
                DCD     scb_5_interrupt_IRQHandler            ; Serial Communication Block #5
                DCD     csd_interrupt_IRQHandler              ; CSD (Capsense) interrupt
                DCD     cpuss_interrupts_dmac_0_IRQHandler    ; CPUSS DMAC, Channel #0
                DCD     cpuss_interrupts_dmac_1_IRQHandler    ; CPUSS DMAC, Channel #1
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     cpuss_interrupts_dw0_0_IRQHandler     ; CPUSS DataWire #0, Channel #0
                DCD     cpuss_interrupts_dw0_1_IRQHandler     ; CPUSS DataWire #0, Channel #1
                DCD     cpuss_interrupts_dw0_2_IRQHandler     ; CPUSS DataWire #0, Channel #2
                DCD     cpuss_interrupts_dw0_3_IRQHandler     ; CPUSS DataWire #0, Channel #3
                DCD     cpuss_interrupts_dw0_4_IRQHandler     ; CPUSS DataWire #0, Channel #4
                DCD     cpuss_interrupts_dw0_5_IRQHandler     ; CPUSS DataWire #0, Channel #5
                DCD     cpuss_interrupts_dw0_6_IRQHandler     ; CPUSS DataWire #0, Channel #6
                DCD     cpuss_interrupts_dw0_7_IRQHandler     ; CPUSS DataWire #0, Channel #7
                DCD     cpuss_interrupts_dw0_8_IRQHandler     ; CPUSS DataWire #0, Channel #8
                DCD     cpuss_interrupts_dw0_9_IRQHandler     ; CPUSS DataWire #0, Channel #9
                DCD     cpuss_interrupts_dw0_10_IRQHandler    ; CPUSS DataWire #0, Channel #10
                DCD     cpuss_interrupts_dw0_11_IRQHandler    ; CPUSS DataWire #0, Channel #11
                DCD     cpuss_interrupts_dw0_12_IRQHandler    ; CPUSS DataWire #0, Channel #12
                DCD     cpuss_interrupts_dw0_13_IRQHandler    ; CPUSS DataWire #0, Channel #13
                DCD     cpuss_interrupts_dw0_14_IRQHandler    ; CPUSS DataWire #0, Channel #14
                DCD     cpuss_interrupts_dw0_15_IRQHandler    ; CPUSS DataWire #0, Channel #15
                DCD     cpuss_interrupts_dw0_16_IRQHandler    ; CPUSS DataWire #0, Channel #16
                DCD     cpuss_interrupts_dw0_17_IRQHandler    ; CPUSS DataWire #0, Channel #17
                DCD     cpuss_interrupts_dw0_18_IRQHandler    ; CPUSS DataWire #0, Channel #18
                DCD     cpuss_interrupts_dw0_19_IRQHandler    ; CPUSS DataWire #0, Channel #19
                DCD     cpuss_interrupts_dw0_20_IRQHandler    ; CPUSS DataWire #0, Channel #20
                DCD     cpuss_interrupts_dw0_21_IRQHandler    ; CPUSS DataWire #0, Channel #21
                DCD     cpuss_interrupts_dw0_22_IRQHandler    ; CPUSS DataWire #0, Channel #22
                DCD     cpuss_interrupts_dw0_23_IRQHandler    ; CPUSS DataWire #0, Channel #23
                DCD     cpuss_interrupts_dw0_24_IRQHandler    ; CPUSS DataWire #0, Channel #24
                DCD     cpuss_interrupts_dw0_25_IRQHandler    ; CPUSS DataWire #0, Channel #25
                DCD     cpuss_interrupts_dw0_26_IRQHandler    ; CPUSS DataWire #0, Channel #26
                DCD     cpuss_interrupts_dw0_27_IRQHandler    ; CPUSS DataWire #0, Channel #27
                DCD     cpuss_interrupts_dw0_28_IRQHandler    ; CPUSS DataWire #0, Channel #28
                DCD     cpuss_interrupts_dw1_0_IRQHandler     ; CPUSS DataWire #1, Channel #0
                DCD     cpuss_interrupts_dw1_1_IRQHandler     ; CPUSS DataWire #1, Channel #1
                DCD     cpuss_interrupts_dw1_2_IRQHandler     ; CPUSS DataWire #1, Channel #2
                DCD     cpuss_interrupts_dw1_3_IRQHandler     ; CPUSS DataWire #1, Channel #3
                DCD     cpuss_interrupts_dw1_4_IRQHandler     ; CPUSS DataWire #1, Channel #4
                DCD     cpuss_interrupts_dw1_5_IRQHandler     ; CPUSS DataWire #1, Channel #5
                DCD     cpuss_interrupts_dw1_6_IRQHandler     ; CPUSS DataWire #1, Channel #6
                DCD     cpuss_interrupts_dw1_7_IRQHandler     ; CPUSS DataWire #1, Channel #7
                DCD     cpuss_interrupts_dw1_8_IRQHandler     ; CPUSS DataWire #1, Channel #8
                DCD     cpuss_interrupts_dw1_9_IRQHandler     ; CPUSS DataWire #1, Channel #9
                DCD     cpuss_interrupts_dw1_10_IRQHandler    ; CPUSS DataWire #1, Channel #10
                DCD     cpuss_interrupts_dw1_11_IRQHandler    ; CPUSS DataWire #1, Channel #11
                DCD     cpuss_interrupts_dw1_12_IRQHandler    ; CPUSS DataWire #1, Channel #12
                DCD     cpuss_interrupts_dw1_13_IRQHandler    ; CPUSS DataWire #1, Channel #13
                DCD     cpuss_interrupts_dw1_14_IRQHandler    ; CPUSS DataWire #1, Channel #14
                DCD     cpuss_interrupts_dw1_15_IRQHandler    ; CPUSS DataWire #1, Channel #15
                DCD     cpuss_interrupts_dw1_16_IRQHandler    ; CPUSS DataWire #1, Channel #16
                DCD     cpuss_interrupts_dw1_17_IRQHandler    ; CPUSS DataWire #1, Channel #17
                DCD     cpuss_interrupts_dw1_18_IRQHandler    ; CPUSS DataWire #1, Channel #18
                DCD     cpuss_interrupts_dw1_19_IRQHandler    ; CPUSS DataWire #1, Channel #19
                DCD     cpuss_interrupts_dw1_20_IRQHandler    ; CPUSS DataWire #1, Channel #20
                DCD     cpuss_interrupts_dw1_21_IRQHandler    ; CPUSS DataWire #1, Channel #21
                DCD     cpuss_interrupts_dw1_22_IRQHandler    ; CPUSS DataWire #1, Channel #22
                DCD     cpuss_interrupts_dw1_23_IRQHandler    ; CPUSS DataWire #1, Channel #23
                DCD     cpuss_interrupts_dw1_24_IRQHandler    ; CPUSS DataWire #1, Channel #24
                DCD     cpuss_interrupts_dw1_25_IRQHandler    ; CPUSS DataWire #1, Channel #25
                DCD     cpuss_interrupts_dw1_26_IRQHandler    ; CPUSS DataWire #1, Channel #26
                DCD     cpuss_interrupts_dw1_27_IRQHandler    ; CPUSS DataWire #1, Channel #27
                DCD     cpuss_interrupts_dw1_28_IRQHandler    ; CPUSS DataWire #1, Channel #28
                DCD     cpuss_interrupts_fault_0_IRQHandler   ; CPUSS Fault Structure Interrupt #0
                DCD     cpuss_interrupts_fault_1_IRQHandler   ; CPUSS Fault Structure Interrupt #1
                DCD     cpuss_interrupt_crypto_IRQHandler     ; CRYPTO Accelerator Interrupt
                DCD     cpuss_interrupt_fm_IRQHandler         ; FLASH Macro Interrupt
                DCD     cpuss_interrupts_cm4_fp_IRQHandler    ; Floating Point operation fault
                DCD     cpuss_interrupts_cm0_cti_0_IRQHandler ; CM0+ CTI #0
                DCD     cpuss_interrupts_cm0_cti_1_IRQHandler ; CM0+ CTI #1
                DCD     cpuss_interrupts_cm4_cti_0_IRQHandler ; CM4 CTI #0
                DCD     cpuss_interrupts_cm4_cti_1_IRQHandler ; CM4 CTI #1
                DCD     tcpwm_0_interrupts_0_IRQHandler       ; TCPWM #0, Counter #0
                DCD     tcpwm_0_interrupts_1_IRQHandler       ; TCPWM #0, Counter #1
                DCD     tcpwm_0_interrupts_2_IRQHandler       ; TCPWM #0, Counter #2
                DCD     tcpwm_0_interrupts_3_IRQHandler       ; TCPWM #0, Counter #3
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     tcpwm_0_interrupts_256_IRQHandler     ; TCPWM #0, Counter #256
                DCD     tcpwm_0_interrupts_257_IRQHandler     ; TCPWM #0, Counter #257
                DCD     tcpwm_0_interrupts_258_IRQHandler     ; TCPWM #0, Counter #258
                DCD     tcpwm_0_interrupts_259_IRQHandler     ; TCPWM #0, Counter #259
                DCD     tcpwm_0_interrupts_260_IRQHandler     ; TCPWM #0, Counter #260
                DCD     tcpwm_0_interrupts_261_IRQHandler     ; TCPWM #0, Counter #261
                DCD     tcpwm_0_interrupts_262_IRQHandler     ; TCPWM #0, Counter #262
                DCD     tcpwm_0_interrupts_263_IRQHandler     ; TCPWM #0, Counter #263
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     pass_interrupt_dacs_IRQHandler        ; Consolidated interrrupt for all DACs
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     smif_interrupt_IRQHandler             ; Serial Memory Interface interrupt
                DCD     usb_interrupt_hi_IRQHandler           ; USB Interrupt
                DCD     usb_interrupt_med_IRQHandler          ; USB Interrupt
                DCD     usb_interrupt_lo_IRQHandler           ; USB Interrupt
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     0                                     ; Reserved
                DCD     canfd_0_interrupt0_IRQHandler         ; Can #0, Consolidated interrupt #0
                DCD     canfd_0_interrupts0_0_IRQHandler      ; CAN #0, Interrupt #0, Channel #0
                DCD     canfd_0_interrupts1_0_IRQHandler      ; CAN #0, Interrupt #1, Channel #0
                DCD     cpuss_interrupts_dw1_29_IRQHandler    ; CPUSS DataWire #1, Channel #29
                DCD     cpuss_interrupts_dw1_30_IRQHandler    ; CPUSS DataWire #1, Channel #30
                DCD     cpuss_interrupts_dw1_31_IRQHandler    ; CPUSS DataWire #1, Channel #31
                DCD     cpuss_interrupts_dw0_29_IRQHandler    ; CPUSS DataWire #0, Channel #29

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors
                EXPORT __ramVectors
                AREA    RESET_RAM, READWRITE, NOINIT
__ramVectors    SPACE   __Vectors_Size


                AREA    |.text|, CODE, READONLY


; Weak function for startup customization
;
; Note. The global resources are not yet initialized (for example global variables, peripherals, clocks)
; because this function is executed as the first instruction in the ResetHandler.
; The PDL is also not initialized to use the proper register offsets.
; The user of this function is responsible for initializing the PDL and resources before using them.
;
Cy_OnResetUser  PROC
                EXPORT  Cy_OnResetUser            [WEAK]
                BX      LR
                ENDP

; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  Cy_SystemInitFpuEnable
                IMPORT  __main

                ; Define strong function for startup customization
                BL      Cy_OnResetUser

                ; Disable global interrupts
                CPSID I

                ; Copy vectors from ROM to RAM
                LDR r1, =__Vectors
                LDR r0, =__ramVectors
                LDR r2, =__Vectors_Size
Vectors_Copy
                LDR r3, [r1]
                STR r3, [r0]
                ADDS r0, r0, #4
                ADDS r1, r1, #4
                SUBS r2, r2, #4
                CMP r2, #0
                BNE Vectors_Copy

                ; Update Vector Table Offset Register. */
                LDR r0, =__ramVectors
                LDR r1, =0xE000ED08
                STR r0, [r1]
                dsb 0xF

                ; Enable the FPU if used
                LDR     R0, =Cy_SystemInitFpuEnable
                BLX     R0

                LDR     R0, =__main
                BLX     R0

                ; Should never get here
                B       .

                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler         PROC
                    EXPORT  NMI_Handler               [WEAK]
                    B       .
                    ENDP

Cy_SysLib_FaultHandler PROC
                    EXPORT  Cy_SysLib_FaultHandler   [WEAK]
                    B       .
                    ENDP
HardFault_Wrapper\
                    PROC
                    EXPORT HardFault_Wrapper         [WEAK]
                    movs r0, #4
                    mov r1, LR
                    tst r0, r1
                    beq L_MSP
                    mrs r0, PSP
                    bl L_API_call
L_MSP
                    mrs r0, MSP
L_API_call
                    bl Cy_SysLib_FaultHandler
                    ENDP
HardFault_Handler\
                    PROC
                    EXPORT  HardFault_Handler         [WEAK]
                    B       HardFault_Wrapper
                    ENDP
MemManage_Handler\
                    PROC
                    EXPORT  MemManage_Handler         [WEAK]
                    B       HardFault_Wrapper
                    ENDP
BusFault_Handler\
                    PROC
                    EXPORT  BusFault_Handler          [WEAK]
                    B       HardFault_Wrapper
                    ENDP
UsageFault_Handler\
                    PROC
                    EXPORT  UsageFault_Handler        [WEAK]
                    B       HardFault_Wrapper
                    ENDP
SVC_Handler         PROC
                    EXPORT  SVC_Handler               [WEAK]
                    B       .
                    ENDP
DebugMon_Handler\
                    PROC
                    EXPORT  DebugMon_Handler          [WEAK]
                    B       .
                    ENDP
PendSV_Handler      PROC
                    EXPORT  PendSV_Handler            [WEAK]
                    B       .
                    ENDP
SysTick_Handler     PROC
                    EXPORT  SysTick_Handler           [WEAK]
                    B       .
                    ENDP

Default_Handler     PROC
                    EXPORT  Default_Handler                       [WEAK]
                    EXPORT  ioss_interrupts_gpio_0_IRQHandler     [WEAK]
                    EXPORT  ioss_interrupts_gpio_2_IRQHandler     [WEAK]
                    EXPORT  ioss_interrupts_gpio_3_IRQHandler     [WEAK]
                    EXPORT  ioss_interrupts_gpio_5_IRQHandler     [WEAK]
                    EXPORT  ioss_interrupts_gpio_6_IRQHandler     [WEAK]
                    EXPORT  ioss_interrupts_gpio_7_IRQHandler     [WEAK]
                    EXPORT  ioss_interrupts_gpio_8_IRQHandler     [WEAK]
                    EXPORT  ioss_interrupts_gpio_9_IRQHandler     [WEAK]
                    EXPORT  ioss_interrupts_gpio_10_IRQHandler    [WEAK]
                    EXPORT  ioss_interrupts_gpio_11_IRQHandler    [WEAK]
                    EXPORT  ioss_interrupts_gpio_12_IRQHandler    [WEAK]
                    EXPORT  ioss_interrupts_gpio_14_IRQHandler    [WEAK]
                    EXPORT  ioss_interrupt_gpio_IRQHandler        [WEAK]
                    EXPORT  ioss_interrupt_vdd_IRQHandler         [WEAK]
                    EXPORT  lpcomp_interrupt_IRQHandler           [WEAK]
                    EXPORT  scb_6_interrupt_IRQHandler            [WEAK]
                    EXPORT  srss_interrupt_mcwdt_0_IRQHandler     [WEAK]
                    EXPORT  srss_interrupt_mcwdt_1_IRQHandler     [WEAK]
                    EXPORT  srss_interrupt_backup_IRQHandler      [WEAK]
                    EXPORT  srss_interrupt_IRQHandler             [WEAK]
                    EXPORT  cpuss_interrupts_ipc_0_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_1_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_2_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_3_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_4_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_5_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_6_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_7_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_8_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_9_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_ipc_10_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_ipc_11_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_ipc_12_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_ipc_13_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_ipc_14_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_ipc_15_IRQHandler    [WEAK]
                    EXPORT  pass_interrupt_sar_0_IRQHandler       [WEAK]
                    EXPORT  pass_interrupt_sar_1_IRQHandler       [WEAK]
                    EXPORT  pass_interrupt_ctbs_IRQHandler        [WEAK]
                    EXPORT  pass_interrupt_fifo_0_IRQHandler      [WEAK]
                    EXPORT  pass_interrupt_fifo_1_IRQHandler      [WEAK]
                    EXPORT  scb_0_interrupt_IRQHandler            [WEAK]
                    EXPORT  scb_1_interrupt_IRQHandler            [WEAK]
                    EXPORT  scb_2_interrupt_IRQHandler            [WEAK]
                    EXPORT  scb_4_interrupt_IRQHandler            [WEAK]
                    EXPORT  scb_5_interrupt_IRQHandler            [WEAK]
                    EXPORT  csd_interrupt_IRQHandler              [WEAK]
                    EXPORT  cpuss_interrupts_dmac_0_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dmac_1_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_0_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_1_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_2_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_3_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_4_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_5_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_6_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_7_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_8_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_9_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw0_10_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_11_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_12_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_13_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_14_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_15_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_16_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_17_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_18_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_19_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_20_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_21_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_22_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_23_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_24_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_25_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_26_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_27_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_28_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_0_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_1_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_2_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_3_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_4_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_5_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_6_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_7_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_8_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_9_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupts_dw1_10_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_11_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_12_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_13_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_14_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_15_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_16_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_17_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_18_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_19_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_20_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_21_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_22_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_23_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_24_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_25_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_26_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_27_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_28_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_fault_0_IRQHandler   [WEAK]
                    EXPORT  cpuss_interrupts_fault_1_IRQHandler   [WEAK]
                    EXPORT  cpuss_interrupt_crypto_IRQHandler     [WEAK]
                    EXPORT  cpuss_interrupt_fm_IRQHandler         [WEAK]
                    EXPORT  cpuss_interrupts_cm4_fp_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_cm0_cti_0_IRQHandler [WEAK]
                    EXPORT  cpuss_interrupts_cm0_cti_1_IRQHandler [WEAK]
                    EXPORT  cpuss_interrupts_cm4_cti_0_IRQHandler [WEAK]
                    EXPORT  cpuss_interrupts_cm4_cti_1_IRQHandler [WEAK]
                    EXPORT  tcpwm_0_interrupts_0_IRQHandler       [WEAK]
                    EXPORT  tcpwm_0_interrupts_1_IRQHandler       [WEAK]
                    EXPORT  tcpwm_0_interrupts_2_IRQHandler       [WEAK]
                    EXPORT  tcpwm_0_interrupts_3_IRQHandler       [WEAK]
                    EXPORT  tcpwm_0_interrupts_256_IRQHandler     [WEAK]
                    EXPORT  tcpwm_0_interrupts_257_IRQHandler     [WEAK]
                    EXPORT  tcpwm_0_interrupts_258_IRQHandler     [WEAK]
                    EXPORT  tcpwm_0_interrupts_259_IRQHandler     [WEAK]
                    EXPORT  tcpwm_0_interrupts_260_IRQHandler     [WEAK]
                    EXPORT  tcpwm_0_interrupts_261_IRQHandler     [WEAK]
                    EXPORT  tcpwm_0_interrupts_262_IRQHandler     [WEAK]
                    EXPORT  tcpwm_0_interrupts_263_IRQHandler     [WEAK]
                    EXPORT  pass_interrupt_dacs_IRQHandler        [WEAK]
                    EXPORT  smif_interrupt_IRQHandler             [WEAK]
                    EXPORT  usb_interrupt_hi_IRQHandler           [WEAK]
                    EXPORT  usb_interrupt_med_IRQHandler          [WEAK]
                    EXPORT  usb_interrupt_lo_IRQHandler           [WEAK]
                    EXPORT  canfd_0_interrupt0_IRQHandler         [WEAK]
                    EXPORT  canfd_0_interrupts0_0_IRQHandler      [WEAK]
                    EXPORT  canfd_0_interrupts1_0_IRQHandler      [WEAK]
                    EXPORT  cpuss_interrupts_dw1_29_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_30_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw1_31_IRQHandler    [WEAK]
                    EXPORT  cpuss_interrupts_dw0_29_IRQHandler    [WEAK]

ioss_interrupts_gpio_0_IRQHandler
ioss_interrupts_gpio_2_IRQHandler
ioss_interrupts_gpio_3_IRQHandler
ioss_interrupts_gpio_5_IRQHandler
ioss_interrupts_gpio_6_IRQHandler
ioss_interrupts_gpio_7_IRQHandler
ioss_interrupts_gpio_8_IRQHandler
ioss_interrupts_gpio_9_IRQHandler
ioss_interrupts_gpio_10_IRQHandler
ioss_interrupts_gpio_11_IRQHandler
ioss_interrupts_gpio_12_IRQHandler
ioss_interrupts_gpio_14_IRQHandler
ioss_interrupt_gpio_IRQHandler
ioss_interrupt_vdd_IRQHandler
lpcomp_interrupt_IRQHandler
scb_6_interrupt_IRQHandler
srss_interrupt_mcwdt_0_IRQHandler
srss_interrupt_mcwdt_1_IRQHandler
srss_interrupt_backup_IRQHandler
srss_interrupt_IRQHandler
cpuss_interrupts_ipc_0_IRQHandler
cpuss_interrupts_ipc_1_IRQHandler
cpuss_interrupts_ipc_2_IRQHandler
cpuss_interrupts_ipc_3_IRQHandler
cpuss_interrupts_ipc_4_IRQHandler
cpuss_interrupts_ipc_5_IRQHandler
cpuss_interrupts_ipc_6_IRQHandler
cpuss_interrupts_ipc_7_IRQHandler
cpuss_interrupts_ipc_8_IRQHandler
cpuss_interrupts_ipc_9_IRQHandler
cpuss_interrupts_ipc_10_IRQHandler
cpuss_interrupts_ipc_11_IRQHandler
cpuss_interrupts_ipc_12_IRQHandler
cpuss_interrupts_ipc_13_IRQHandler
cpuss_interrupts_ipc_14_IRQHandler
cpuss_interrupts_ipc_15_IRQHandler
pass_interrupt_sar_0_IRQHandler
pass_interrupt_sar_1_IRQHandler
pass_interrupt_ctbs_IRQHandler
pass_interrupt_fifo_0_IRQHandler
pass_interrupt_fifo_1_IRQHandler
scb_0_interrupt_IRQHandler
scb_1_interrupt_IRQHandler
scb_2_interrupt_IRQHandler
scb_4_interrupt_IRQHandler
scb_5_interrupt_IRQHandler
csd_interrupt_IRQHandler
cpuss_interrupts_dmac_0_IRQHandler
cpuss_interrupts_dmac_1_IRQHandler
cpuss_interrupts_dw0_0_IRQHandler
cpuss_interrupts_dw0_1_IRQHandler
cpuss_interrupts_dw0_2_IRQHandler
cpuss_interrupts_dw0_3_IRQHandler
cpuss_interrupts_dw0_4_IRQHandler
cpuss_interrupts_dw0_5_IRQHandler
cpuss_interrupts_dw0_6_IRQHandler
cpuss_interrupts_dw0_7_IRQHandler
cpuss_interrupts_dw0_8_IRQHandler
cpuss_interrupts_dw0_9_IRQHandler
cpuss_interrupts_dw0_10_IRQHandler
cpuss_interrupts_dw0_11_IRQHandler
cpuss_interrupts_dw0_12_IRQHandler
cpuss_interrupts_dw0_13_IRQHandler
cpuss_interrupts_dw0_14_IRQHandler
cpuss_interrupts_dw0_15_IRQHandler
cpuss_interrupts_dw0_16_IRQHandler
cpuss_interrupts_dw0_17_IRQHandler
cpuss_interrupts_dw0_18_IRQHandler
cpuss_interrupts_dw0_19_IRQHandler
cpuss_interrupts_dw0_20_IRQHandler
cpuss_interrupts_dw0_21_IRQHandler
cpuss_interrupts_dw0_22_IRQHandler
cpuss_interrupts_dw0_23_IRQHandler
cpuss_interrupts_dw0_24_IRQHandler
cpuss_interrupts_dw0_25_IRQHandler
cpuss_interrupts_dw0_26_IRQHandler
cpuss_interrupts_dw0_27_IRQHandler
cpuss_interrupts_dw0_28_IRQHandler
cpuss_interrupts_dw1_0_IRQHandler
cpuss_interrupts_dw1_1_IRQHandler
cpuss_interrupts_dw1_2_IRQHandler
cpuss_interrupts_dw1_3_IRQHandler
cpuss_interrupts_dw1_4_IRQHandler
cpuss_interrupts_dw1_5_IRQHandler
cpuss_interrupts_dw1_6_IRQHandler
cpuss_interrupts_dw1_7_IRQHandler
cpuss_interrupts_dw1_8_IRQHandler
cpuss_interrupts_dw1_9_IRQHandler
cpuss_interrupts_dw1_10_IRQHandler
cpuss_interrupts_dw1_11_IRQHandler
cpuss_interrupts_dw1_12_IRQHandler
cpuss_interrupts_dw1_13_IRQHandler
cpuss_interrupts_dw1_14_IRQHandler
cpuss_interrupts_dw1_15_IRQHandler
cpuss_interrupts_dw1_16_IRQHandler
cpuss_interrupts_dw1_17_IRQHandler
cpuss_interrupts_dw1_18_IRQHandler
cpuss_interrupts_dw1_19_IRQHandler
cpuss_interrupts_dw1_20_IRQHandler
cpuss_interrupts_dw1_21_IRQHandler
cpuss_interrupts_dw1_22_IRQHandler
cpuss_interrupts_dw1_23_IRQHandler
cpuss_interrupts_dw1_24_IRQHandler
cpuss_interrupts_dw1_25_IRQHandler
cpuss_interrupts_dw1_26_IRQHandler
cpuss_interrupts_dw1_27_IRQHandler
cpuss_interrupts_dw1_28_IRQHandler
cpuss_interrupts_fault_0_IRQHandler
cpuss_interrupts_fault_1_IRQHandler
cpuss_interrupt_crypto_IRQHandler
cpuss_interrupt_fm_IRQHandler
cpuss_interrupts_cm4_fp_IRQHandler
cpuss_interrupts_cm0_cti_0_IRQHandler
cpuss_interrupts_cm0_cti_1_IRQHandler
cpuss_interrupts_cm4_cti_0_IRQHandler
cpuss_interrupts_cm4_cti_1_IRQHandler
tcpwm_0_interrupts_0_IRQHandler
tcpwm_0_interrupts_1_IRQHandler
tcpwm_0_interrupts_2_IRQHandler
tcpwm_0_interrupts_3_IRQHandler
tcpwm_0_interrupts_256_IRQHandler
tcpwm_0_interrupts_257_IRQHandler
tcpwm_0_interrupts_258_IRQHandler
tcpwm_0_interrupts_259_IRQHandler
tcpwm_0_interrupts_260_IRQHandler
tcpwm_0_interrupts_261_IRQHandler
tcpwm_0_interrupts_262_IRQHandler
tcpwm_0_interrupts_263_IRQHandler
pass_interrupt_dacs_IRQHandler
smif_interrupt_IRQHandler
usb_interrupt_hi_IRQHandler
usb_interrupt_med_IRQHandler
usb_interrupt_lo_IRQHandler
canfd_0_interrupt0_IRQHandler
canfd_0_interrupts0_0_IRQHandler
canfd_0_interrupts1_0_IRQHandler
cpuss_interrupts_dw1_29_IRQHandler
cpuss_interrupts_dw1_30_IRQHandler
cpuss_interrupts_dw1_31_IRQHandler
cpuss_interrupts_dw0_29_IRQHandler

                B       .
                ENDP

                ALIGN


; User Initial Stack & Heap
                IMPORT   __use_two_region_memory

                END


; [] END OF FILE
