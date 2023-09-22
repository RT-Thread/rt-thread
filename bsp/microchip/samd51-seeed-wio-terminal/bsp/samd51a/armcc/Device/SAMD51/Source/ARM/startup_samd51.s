;/*****************************************************************************
; * @file     startup_samd51.s
; * @brief    CMSIS Cortex-M4 Core Device Startup File for
; *           Atmel SAMD51 Device Series
; * @version  V1.0.0
; * @date     13. January 2017
; *
; * @note
; * Copyright (C) 2017 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


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

Heap_Size       EQU     0x00000000

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

__Vectors       DCD     __initial_sp              ;    Top of Stack
                DCD     Reset_Handler             ;    Reset Handler
                DCD     NMI_Handler               ;    NMI Handler
                DCD     HardFault_Handler         ;    Hard Fault Handler
                DCD     MemManage_Handler         ;    MPU Fault Handler
                DCD     BusFault_Handler          ;    Bus Fault Handler
                DCD     UsageFault_Handler        ;    Usage Fault Handler
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     SVC_Handler               ;    SVCall Handler
                DCD     DebugMon_Handler          ;    Debug Monitor Handler
                DCD     0                         ;    Reserved
                DCD     PendSV_Handler            ;    PendSV Handler
                DCD     SysTick_Handler           ;    SysTick Handler

                ; External Interrupts
                DCD     PM_Handler                ;  0 Power Manager
                DCD     MCLK_Handler              ;  1 Main Clock
                DCD     OSCCTRL_0_Handler         ;  2 OSCCTRL_XOSCFAIL_0, OSCCTRL_XOSCRDY_0
                DCD     OSCCTRL_1_Handler         ;  3 OSCCTRL_XOSCFAIL_1, OSCCTRL_XOSCRDY_1
                DCD     OSCCTRL_2_Handler         ;  4 OSCCTRL_DFLLLOCKC, OSCCTRL_DFLLLOCKF, OSCCTRL_DFLLOOB, OSCCTRL_DFLLRCS, OSCCTRL_DFLLRDY
                DCD     OSCCTRL_3_Handler         ;  5 OSCCTRL_DPLLLCKF_0, OSCCTRL_DPLLLCKR_0, OSCCTRL_DPLLLDRTO_0, OSCCTRL_DPLLLTO_0
                DCD     OSCCTRL_4_Handler         ;  6 OSCCTRL_DPLLLCKF_1, OSCCTRL_DPLLLCKR_1, OSCCTRL_DPLLLDRTO_1, OSCCTRL_DPLLLTO_1
                DCD     OSC32KCTRL_Handler        ;  7 32kHz Oscillators Control
                DCD     SUPC_0_Handler            ;  8 SUPC_B12SRDY, SUPC_B33SRDY, SUPC_BOD12RDY, SUPC_BOD33RDY, SUPC_VCORERDY, SUPC_VREGRDY
                DCD     SUPC_1_Handler            ;  9 SUPC_BOD12DET, SUPC_BOD33DET
                DCD     WDT_Handler               ; 10 Watchdog Timer
                DCD     RTC_Handler               ; 11 Real-Time Counter
                DCD     EIC_0_Handler             ; 12 EIC_EXTINT_0
                DCD     EIC_1_Handler             ; 13 EIC_EXTINT_1
                DCD     EIC_2_Handler             ; 14 EIC_EXTINT_2
                DCD     EIC_3_Handler             ; 15 EIC_EXTINT_3
                DCD     EIC_4_Handler             ; 16 EIC_EXTINT_4
                DCD     EIC_5_Handler             ; 17 EIC_EXTINT_5
                DCD     EIC_6_Handler             ; 18 EIC_EXTINT_6
                DCD     EIC_7_Handler             ; 19 EIC_EXTINT_7
                DCD     EIC_8_Handler             ; 20 EIC_EXTINT_8
                DCD     EIC_9_Handler             ; 21 EIC_EXTINT_9
                DCD     EIC_10_Handler            ; 22 EIC_EXTINT_10
                DCD     EIC_11_Handler            ; 23 EIC_EXTINT_11
                DCD     EIC_12_Handler            ; 24 EIC_EXTINT_12
                DCD     EIC_13_Handler            ; 25 EIC_EXTINT_13
                DCD     EIC_14_Handler            ; 26 EIC_EXTINT_14
                DCD     EIC_15_Handler            ; 27 EIC_EXTINT_15
                DCD     FREQM_Handler             ; 28 Frequency Meter
                DCD     NVMCTRL_0_Handler         ; 29 NVMCTRL_0, NVMCTRL_1, NVMCTRL_2, NVMCTRL_3, NVMCTRL_4, NVMCTRL_5, NVMCTRL_6, NVMCTRL_7
                DCD     NVMCTRL_1_Handler         ; 30 NVMCTRL_10, NVMCTRL_8, NVMCTRL_9
                DCD     DMAC_0_Handler            ; 31 DMAC_SUSP_0, DMAC_TCMPL_0, DMAC_TERR_0
                DCD     DMAC_1_Handler            ; 32 DMAC_SUSP_1, DMAC_TCMPL_1, DMAC_TERR_1
                DCD     DMAC_2_Handler            ; 33 DMAC_SUSP_2, DMAC_TCMPL_2, DMAC_TERR_2
                DCD     DMAC_3_Handler            ; 34 DMAC_SUSP_3, DMAC_TCMPL_3, DMAC_TERR_3
                DCD     DMAC_4_Handler            ; 35 DMAC_SUSP_10, DMAC_SUSP_11, DMAC_SUSP_12, DMAC_SUSP_13, DMAC_SUSP_14, DMAC_SUSP_15, DMAC_SUSP_16, DMAC_SUSP_17, DMAC_SUSP_18, DMAC_SUSP_19, DMAC_SUSP_20, DMAC_SUSP_21, DMAC_SUSP_22, DMAC_SUSP_23, DMAC_SUSP_24, DMAC_SUSP_25, DMAC_SUSP_26, DMAC_SUSP_27, DMAC_SUSP_28, DMAC_SUSP_29, DMAC_SUSP_30, DMAC_SUSP_31, DMAC_SUSP_4, DMAC_SUSP_5, DMAC_SUSP_6, DMAC_SUSP_7, DMAC_SUSP_8, DMAC_SUSP_9, DMAC_TCMPL_10, DMAC_TCMPL_11, DMAC_TCMPL_12, DMAC_TCMPL_13, DMAC_TCMPL_14, DMAC_TCMPL_15, DMAC_TCMPL_16, DMAC_TCMPL_17, DMAC_TCMPL_18, DMAC_TCMPL_19, DMAC_TCMPL_20, DMAC_TCMPL_21, DMAC_TCMPL_22, DMAC_TCMPL_23, DMAC_TCMPL_24, DMAC_TCMPL_25, DMAC_TCMPL_26, DMAC_TCMPL_27, DMAC_TCMPL_28, DMAC_TCMPL_29, DMAC_TCMPL_30, DMAC_TCMPL_31, DMAC_TCMPL_4, DMAC_TCMPL_5, DMAC_TCMPL_6, DMAC_TCMPL_7, DMAC_TCMPL_8, DMAC_TCMPL_9, DMAC_TERR_10, DMAC_TERR_11, DMAC_TERR_12, DMAC_TERR_13, DMAC_TERR_14, DMAC_TERR_15, DMAC_TERR_16, DMAC_TERR_17, DMAC_TERR_18, DMAC_TERR_19, DMAC_TERR_20, DMAC_TERR_21, DMAC_TERR_22, DMAC_TERR_23, DMAC_TERR_24, DMAC_TERR_25, DMAC_TERR_26, DMAC_TERR_27, DMAC_TERR_28, DMAC_TERR_29, DMAC_TERR_30, DMAC_TERR_31, DMAC_TERR_4, DMAC_TERR_5, DMAC_TERR_6, DMAC_TERR_7, DMAC_TERR_8, DMAC_TERR_9
                DCD     EVSYS_0_Handler           ; 36 EVSYS_EVD_0, EVSYS_OVR_0
                DCD     EVSYS_1_Handler           ; 37 EVSYS_EVD_1, EVSYS_OVR_1
                DCD     EVSYS_2_Handler           ; 38 EVSYS_EVD_2, EVSYS_OVR_2
                DCD     EVSYS_3_Handler           ; 39 EVSYS_EVD_3, EVSYS_OVR_3
                DCD     EVSYS_4_Handler           ; 40 EVSYS_EVD_10, EVSYS_EVD_11, EVSYS_EVD_4, EVSYS_EVD_5, EVSYS_EVD_6, EVSYS_EVD_7, EVSYS_EVD_8, EVSYS_EVD_9, EVSYS_OVR_10, EVSYS_OVR_11, EVSYS_OVR_4, EVSYS_OVR_5, EVSYS_OVR_6, EVSYS_OVR_7, EVSYS_OVR_8, EVSYS_OVR_9
                DCD     PAC_Handler               ; 41 Peripheral Access Controller
                DCD     TAL_0_Handler             ; 42 TAL_BRK
                DCD     TAL_1_Handler             ; 43 TAL_IPS_0, TAL_IPS_1
                DCD     0                         ; 44 Reserved
                DCD     RAMECC_Handler            ; 45 RAM ECC
                DCD     SERCOM0_0_Handler         ; 46 SERCOM0_0
                DCD     SERCOM0_1_Handler         ; 47 SERCOM0_1
                DCD     SERCOM0_2_Handler         ; 48 SERCOM0_2
                DCD     SERCOM0_3_Handler         ; 49 SERCOM0_3, SERCOM0_4, SERCOM0_5, SERCOM0_6
                DCD     SERCOM1_0_Handler         ; 50 SERCOM1_0
                DCD     SERCOM1_1_Handler         ; 51 SERCOM1_1
                DCD     SERCOM1_2_Handler         ; 52 SERCOM1_2
                DCD     SERCOM1_3_Handler         ; 53 SERCOM1_3, SERCOM1_4, SERCOM1_5, SERCOM1_6
                DCD     SERCOM2_0_Handler         ; 54 SERCOM2_0
                DCD     SERCOM2_1_Handler         ; 55 SERCOM2_1
                DCD     SERCOM2_2_Handler         ; 56 SERCOM2_2
                DCD     SERCOM2_3_Handler         ; 57 SERCOM2_3, SERCOM2_4, SERCOM2_5, SERCOM2_6
                DCD     SERCOM3_0_Handler         ; 58 SERCOM3_0
                DCD     SERCOM3_1_Handler         ; 59 SERCOM3_1
                DCD     SERCOM3_2_Handler         ; 60 SERCOM3_2
                DCD     SERCOM3_3_Handler         ; 61 SERCOM3_3, SERCOM3_4, SERCOM3_5, SERCOM3_6
                DCD     SERCOM4_0_Handler         ; 62 SERCOM4_0
                DCD     SERCOM4_1_Handler         ; 63 SERCOM4_1
                DCD     SERCOM4_2_Handler         ; 64 SERCOM4_2
                DCD     SERCOM4_3_Handler         ; 65 SERCOM4_3, SERCOM4_4, SERCOM4_5, SERCOM4_6
                DCD     SERCOM5_0_Handler         ; 66 SERCOM5_0
                DCD     SERCOM5_1_Handler         ; 67 SERCOM5_1
                DCD     SERCOM5_2_Handler         ; 68 SERCOM5_2
                DCD     SERCOM5_3_Handler         ; 69 SERCOM5_3, SERCOM5_4, SERCOM5_5, SERCOM5_6
                DCD     SERCOM6_0_Handler         ; 70 SERCOM6_0
                DCD     SERCOM6_1_Handler         ; 71 SERCOM6_1
                DCD     SERCOM6_2_Handler         ; 72 SERCOM6_2
                DCD     SERCOM6_3_Handler         ; 73 SERCOM6_3, SERCOM6_4, SERCOM6_5, SERCOM6_6
                DCD     SERCOM7_0_Handler         ; 74 SERCOM7_0
                DCD     SERCOM7_1_Handler         ; 75 SERCOM7_1
                DCD     SERCOM7_2_Handler         ; 76 SERCOM7_2
                DCD     SERCOM7_3_Handler         ; 77 SERCOM7_3, SERCOM7_4, SERCOM7_5, SERCOM7_6
                DCD     CAN0_Handler              ; 78 Control Area Network 0
                DCD     CAN1_Handler              ; 79 Control Area Network 1
                DCD     USB_0_Handler             ; 80 USB_EORSM_DNRSM, USB_EORST_RST, USB_LPMSUSP_DDISC, USB_LPM_DCONN, USB_MSOF, USB_RAMACER, USB_RXSTP_TXSTP_0, USB_RXSTP_TXSTP_1, USB_RXSTP_TXSTP_2, USB_RXSTP_TXSTP_3, USB_RXSTP_TXSTP_4, USB_RXSTP_TXSTP_5, USB_RXSTP_TXSTP_6, USB_RXSTP_TXSTP_7, USB_STALL0_STALL_0, USB_STALL0_STALL_1, USB_STALL0_STALL_2, USB_STALL0_STALL_3, USB_STALL0_STALL_4, USB_STALL0_STALL_5, USB_STALL0_STALL_6, USB_STALL0_STALL_7, USB_STALL1_0, USB_STALL1_1, USB_STALL1_2, USB_STALL1_3, USB_STALL1_4, USB_STALL1_5, USB_STALL1_6, USB_STALL1_7, USB_SUSPEND, USB_TRFAIL0_TRFAIL_0, USB_TRFAIL0_TRFAIL_1, USB_TRFAIL0_TRFAIL_2, USB_TRFAIL0_TRFAIL_3, USB_TRFAIL0_TRFAIL_4, USB_TRFAIL0_TRFAIL_5, USB_TRFAIL0_TRFAIL_6, USB_TRFAIL0_TRFAIL_7, USB_TRFAIL1_PERR_0, USB_TRFAIL1_PERR_1, USB_TRFAIL1_PERR_2, USB_TRFAIL1_PERR_3, USB_TRFAIL1_PERR_4, USB_TRFAIL1_PERR_5, USB_TRFAIL1_PERR_6, USB_TRFAIL1_PERR_7, USB_UPRSM, USB_WAKEUP
                DCD     USB_1_Handler             ; 81 USB_SOF_HSOF
                DCD     USB_2_Handler             ; 82 USB_TRCPT0_0, USB_TRCPT0_1, USB_TRCPT0_2, USB_TRCPT0_3, USB_TRCPT0_4, USB_TRCPT0_5, USB_TRCPT0_6, USB_TRCPT0_7
                DCD     USB_3_Handler             ; 83 USB_TRCPT1_0, USB_TRCPT1_1, USB_TRCPT1_2, USB_TRCPT1_3, USB_TRCPT1_4, USB_TRCPT1_5, USB_TRCPT1_6, USB_TRCPT1_7
                DCD     GMAC_Handler              ; 84 Ethernet MAC
                DCD     TCC0_0_Handler            ; 85 TCC0_CNT_A, TCC0_DFS_A, TCC0_ERR_A, TCC0_FAULT0_A, TCC0_FAULT1_A, TCC0_FAULTA_A, TCC0_FAULTB_A, TCC0_OVF, TCC0_TRG, TCC0_UFS_A
                DCD     TCC0_1_Handler            ; 86 TCC0_MC_0
                DCD     TCC0_2_Handler            ; 87 TCC0_MC_1
                DCD     TCC0_3_Handler            ; 88 TCC0_MC_2
                DCD     TCC0_4_Handler            ; 89 TCC0_MC_3
                DCD     TCC0_5_Handler            ; 90 TCC0_MC_4
                DCD     TCC0_6_Handler            ; 91 TCC0_MC_5
                DCD     TCC1_0_Handler            ; 92 TCC1_CNT_A, TCC1_DFS_A, TCC1_ERR_A, TCC1_FAULT0_A, TCC1_FAULT1_A, TCC1_FAULTA_A, TCC1_FAULTB_A, TCC1_OVF, TCC1_TRG, TCC1_UFS_A
                DCD     TCC1_1_Handler            ; 93 TCC1_MC_0
                DCD     TCC1_2_Handler            ; 94 TCC1_MC_1
                DCD     TCC1_3_Handler            ; 95 TCC1_MC_2
                DCD     TCC1_4_Handler            ; 96 TCC1_MC_3
                DCD     TCC2_0_Handler            ; 97 TCC2_CNT_A, TCC2_DFS_A, TCC2_ERR_A, TCC2_FAULT0_A, TCC2_FAULT1_A, TCC2_FAULTA_A, TCC2_FAULTB_A, TCC2_OVF, TCC2_TRG, TCC2_UFS_A
                DCD     TCC2_1_Handler            ; 98 TCC2_MC_0
                DCD     TCC2_2_Handler            ; 99 TCC2_MC_1
                DCD     TCC2_3_Handler            ; 100 TCC2_MC_2
                DCD     TCC3_0_Handler            ; 101 TCC3_CNT_A, TCC3_DFS_A, TCC3_ERR_A, TCC3_FAULT0_A, TCC3_FAULT1_A, TCC3_FAULTA_A, TCC3_FAULTB_A, TCC3_OVF, TCC3_TRG, TCC3_UFS_A
                DCD     TCC3_1_Handler            ; 102 TCC3_MC_0
                DCD     TCC3_2_Handler            ; 103 TCC3_MC_1
                DCD     TCC4_0_Handler            ; 104 TCC4_CNT_A, TCC4_DFS_A, TCC4_ERR_A, TCC4_FAULT0_A, TCC4_FAULT1_A, TCC4_FAULTA_A, TCC4_FAULTB_A, TCC4_OVF, TCC4_TRG, TCC4_UFS_A
                DCD     TCC4_1_Handler            ; 105 TCC4_MC_0
                DCD     TCC4_2_Handler            ; 106 TCC4_MC_1
                DCD     TC0_Handler               ; 107 Basic Timer Counter 0
                DCD     TC1_Handler               ; 108 Basic Timer Counter 1
                DCD     TC2_Handler               ; 109 Basic Timer Counter 2
                DCD     TC3_Handler               ; 110 Basic Timer Counter 3
                DCD     TC4_Handler               ; 111 Basic Timer Counter 4
                DCD     TC5_Handler               ; 112 Basic Timer Counter 5
                DCD     TC6_Handler               ; 113 Basic Timer Counter 6
                DCD     TC7_Handler               ; 114 Basic Timer Counter 7
                DCD     PDEC_0_Handler            ; 115 PDEC_DIR_A, PDEC_ERR_A, PDEC_OVF, PDEC_VLC_A
                DCD     PDEC_1_Handler            ; 116 PDEC_MC_0
                DCD     PDEC_2_Handler            ; 117 PDEC_MC_1
                DCD     ADC0_0_Handler            ; 118 ADC0_OVERRUN, ADC0_WINMON
                DCD     ADC0_1_Handler            ; 119 ADC0_RESRDY
                DCD     ADC1_0_Handler            ; 120 ADC1_OVERRUN, ADC1_WINMON
                DCD     ADC1_1_Handler            ; 121 ADC1_RESRDY
                DCD     AC_Handler                ; 122 Analog Comparators
                DCD     DAC_0_Handler             ; 123 DAC_OVERRUN_A_0, DAC_OVERRUN_A_1, DAC_UNDERRUN_A_0, DAC_UNDERRUN_A_1
                DCD     DAC_1_Handler             ; 124 DAC_EMPTY_0
                DCD     DAC_2_Handler             ; 125 DAC_EMPTY_1
                DCD     DAC_3_Handler             ; 126 DAC_RESRDY_0
                DCD     DAC_4_Handler             ; 127 DAC_RESRDY_1
                DCD     I2S_Handler               ; 128 Inter-IC Sound Interface
                DCD     PCC_Handler               ; 129 Parallel Capture Controller
                DCD     AES_Handler               ; 130 Advanced Encryption Standard
                DCD     TRNG_Handler              ; 131 True Random Generator
                DCD     ICM_Handler               ; 132 Integrity Check Monitor
                DCD     PUKCC_Handler             ; 133 PUblic-Key Cryptography Controller
                DCD     QSPI_Handler              ; 134 Quad SPI interface
                DCD     SDHC0_Handler             ; 135 SD/MMC Host Controller 0
                DCD     SDHC1_Handler             ; 136 SD/MMC Host Controller 1
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

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
                EXPORT  PM_Handler                [WEAK]
                EXPORT  MCLK_Handler              [WEAK]
                EXPORT  OSCCTRL_0_Handler         [WEAK]
                EXPORT  OSCCTRL_1_Handler         [WEAK]
                EXPORT  OSCCTRL_2_Handler         [WEAK]
                EXPORT  OSCCTRL_3_Handler         [WEAK]
                EXPORT  OSCCTRL_4_Handler         [WEAK]
                EXPORT  OSC32KCTRL_Handler        [WEAK]
                EXPORT  SUPC_0_Handler            [WEAK]
                EXPORT  SUPC_1_Handler            [WEAK]
                EXPORT  WDT_Handler               [WEAK]
                EXPORT  RTC_Handler               [WEAK]
                EXPORT  EIC_0_Handler             [WEAK]
                EXPORT  EIC_1_Handler             [WEAK]
                EXPORT  EIC_2_Handler             [WEAK]
                EXPORT  EIC_3_Handler             [WEAK]
                EXPORT  EIC_4_Handler             [WEAK]
                EXPORT  EIC_5_Handler             [WEAK]
                EXPORT  EIC_6_Handler             [WEAK]
                EXPORT  EIC_7_Handler             [WEAK]
                EXPORT  EIC_8_Handler             [WEAK]
                EXPORT  EIC_9_Handler             [WEAK]
                EXPORT  EIC_10_Handler            [WEAK]
                EXPORT  EIC_11_Handler            [WEAK]
                EXPORT  EIC_12_Handler            [WEAK]
                EXPORT  EIC_13_Handler            [WEAK]
                EXPORT  EIC_14_Handler            [WEAK]
                EXPORT  EIC_15_Handler            [WEAK]
                EXPORT  FREQM_Handler             [WEAK]
                EXPORT  NVMCTRL_0_Handler         [WEAK]
                EXPORT  NVMCTRL_1_Handler         [WEAK]
                EXPORT  DMAC_0_Handler            [WEAK]
                EXPORT  DMAC_1_Handler            [WEAK]
                EXPORT  DMAC_2_Handler            [WEAK]
                EXPORT  DMAC_3_Handler            [WEAK]
                EXPORT  DMAC_4_Handler            [WEAK]
                EXPORT  EVSYS_0_Handler           [WEAK]
                EXPORT  EVSYS_1_Handler           [WEAK]
                EXPORT  EVSYS_2_Handler           [WEAK]
                EXPORT  EVSYS_3_Handler           [WEAK]
                EXPORT  EVSYS_4_Handler           [WEAK]
                EXPORT  PAC_Handler               [WEAK]
                EXPORT  TAL_0_Handler             [WEAK]
                EXPORT  TAL_1_Handler             [WEAK]
                EXPORT  RAMECC_Handler            [WEAK]
                EXPORT  SERCOM0_0_Handler         [WEAK]
                EXPORT  SERCOM0_1_Handler         [WEAK]
                EXPORT  SERCOM0_2_Handler         [WEAK]
                EXPORT  SERCOM0_3_Handler         [WEAK]
                EXPORT  SERCOM1_0_Handler         [WEAK]
                EXPORT  SERCOM1_1_Handler         [WEAK]
                EXPORT  SERCOM1_2_Handler         [WEAK]
                EXPORT  SERCOM1_3_Handler         [WEAK]
                EXPORT  SERCOM2_0_Handler         [WEAK]
                EXPORT  SERCOM2_1_Handler         [WEAK]
                EXPORT  SERCOM2_2_Handler         [WEAK]
                EXPORT  SERCOM2_3_Handler         [WEAK]
                EXPORT  SERCOM3_0_Handler         [WEAK]
                EXPORT  SERCOM3_1_Handler         [WEAK]
                EXPORT  SERCOM3_2_Handler         [WEAK]
                EXPORT  SERCOM3_3_Handler         [WEAK]
                EXPORT  SERCOM4_0_Handler         [WEAK]
                EXPORT  SERCOM4_1_Handler         [WEAK]
                EXPORT  SERCOM4_2_Handler         [WEAK]
                EXPORT  SERCOM4_3_Handler         [WEAK]
                EXPORT  SERCOM5_0_Handler         [WEAK]
                EXPORT  SERCOM5_1_Handler         [WEAK]
                EXPORT  SERCOM5_2_Handler         [WEAK]
                EXPORT  SERCOM5_3_Handler         [WEAK]
                EXPORT  SERCOM6_0_Handler         [WEAK]
                EXPORT  SERCOM6_1_Handler         [WEAK]
                EXPORT  SERCOM6_2_Handler         [WEAK]
                EXPORT  SERCOM6_3_Handler         [WEAK]
                EXPORT  SERCOM7_0_Handler         [WEAK]
                EXPORT  SERCOM7_1_Handler         [WEAK]
                EXPORT  SERCOM7_2_Handler         [WEAK]
                EXPORT  SERCOM7_3_Handler         [WEAK]
                EXPORT  CAN0_Handler              [WEAK]
                EXPORT  CAN1_Handler              [WEAK]
                EXPORT  USB_0_Handler             [WEAK]
                EXPORT  USB_1_Handler             [WEAK]
                EXPORT  USB_2_Handler             [WEAK]
                EXPORT  USB_3_Handler             [WEAK]
                EXPORT  GMAC_Handler              [WEAK]
                EXPORT  TCC0_0_Handler            [WEAK]
                EXPORT  TCC0_1_Handler            [WEAK]
                EXPORT  TCC0_2_Handler            [WEAK]
                EXPORT  TCC0_3_Handler            [WEAK]
                EXPORT  TCC0_4_Handler            [WEAK]
                EXPORT  TCC0_5_Handler            [WEAK]
                EXPORT  TCC0_6_Handler            [WEAK]
                EXPORT  TCC1_0_Handler            [WEAK]
                EXPORT  TCC1_1_Handler            [WEAK]
                EXPORT  TCC1_2_Handler            [WEAK]
                EXPORT  TCC1_3_Handler            [WEAK]
                EXPORT  TCC1_4_Handler            [WEAK]
                EXPORT  TCC2_0_Handler            [WEAK]
                EXPORT  TCC2_1_Handler            [WEAK]
                EXPORT  TCC2_2_Handler            [WEAK]
                EXPORT  TCC2_3_Handler            [WEAK]
                EXPORT  TCC3_0_Handler            [WEAK]
                EXPORT  TCC3_1_Handler            [WEAK]
                EXPORT  TCC3_2_Handler            [WEAK]
                EXPORT  TCC4_0_Handler            [WEAK]
                EXPORT  TCC4_1_Handler            [WEAK]
                EXPORT  TCC4_2_Handler            [WEAK]
                EXPORT  TC0_Handler               [WEAK]
                EXPORT  TC1_Handler               [WEAK]
                EXPORT  TC2_Handler               [WEAK]
                EXPORT  TC3_Handler               [WEAK]
                EXPORT  TC4_Handler               [WEAK]
                EXPORT  TC5_Handler               [WEAK]
                EXPORT  TC6_Handler               [WEAK]
                EXPORT  TC7_Handler               [WEAK]
                EXPORT  PDEC_0_Handler            [WEAK]
                EXPORT  PDEC_1_Handler            [WEAK]
                EXPORT  PDEC_2_Handler            [WEAK]
                EXPORT  ADC0_0_Handler            [WEAK]
                EXPORT  ADC0_1_Handler            [WEAK]
                EXPORT  ADC1_0_Handler            [WEAK]
                EXPORT  ADC1_1_Handler            [WEAK]
                EXPORT  AC_Handler                [WEAK]
                EXPORT  DAC_0_Handler             [WEAK]
                EXPORT  DAC_1_Handler             [WEAK]
                EXPORT  DAC_2_Handler             [WEAK]
                EXPORT  DAC_3_Handler             [WEAK]
                EXPORT  DAC_4_Handler             [WEAK]
                EXPORT  I2S_Handler               [WEAK]
                EXPORT  PCC_Handler               [WEAK]
                EXPORT  AES_Handler               [WEAK]
                EXPORT  TRNG_Handler              [WEAK]
                EXPORT  ICM_Handler               [WEAK]
                EXPORT  PUKCC_Handler             [WEAK]
                EXPORT  QSPI_Handler              [WEAK]
                EXPORT  SDHC0_Handler             [WEAK]
                EXPORT  SDHC1_Handler             [WEAK]

PM_Handler
MCLK_Handler
OSCCTRL_0_Handler
OSCCTRL_1_Handler
OSCCTRL_2_Handler
OSCCTRL_3_Handler
OSCCTRL_4_Handler
OSC32KCTRL_Handler
SUPC_0_Handler
SUPC_1_Handler
WDT_Handler
RTC_Handler
EIC_0_Handler
EIC_1_Handler
EIC_2_Handler
EIC_3_Handler
EIC_4_Handler
EIC_5_Handler
EIC_6_Handler
EIC_7_Handler
EIC_8_Handler
EIC_9_Handler
EIC_10_Handler
EIC_11_Handler
EIC_12_Handler
EIC_13_Handler
EIC_14_Handler
EIC_15_Handler
FREQM_Handler
NVMCTRL_0_Handler
NVMCTRL_1_Handler
DMAC_0_Handler
DMAC_1_Handler
DMAC_2_Handler
DMAC_3_Handler
DMAC_4_Handler
EVSYS_0_Handler
EVSYS_1_Handler
EVSYS_2_Handler
EVSYS_3_Handler
EVSYS_4_Handler
PAC_Handler
TAL_0_Handler
TAL_1_Handler
RAMECC_Handler
SERCOM0_0_Handler
SERCOM0_1_Handler
SERCOM0_2_Handler
SERCOM0_3_Handler
SERCOM1_0_Handler
SERCOM1_1_Handler
SERCOM1_2_Handler
SERCOM1_3_Handler
SERCOM2_0_Handler
SERCOM2_1_Handler
SERCOM2_2_Handler
SERCOM2_3_Handler
SERCOM3_0_Handler
SERCOM3_1_Handler
SERCOM3_2_Handler
SERCOM3_3_Handler
SERCOM4_0_Handler
SERCOM4_1_Handler
SERCOM4_2_Handler
SERCOM4_3_Handler
SERCOM5_0_Handler
SERCOM5_1_Handler
SERCOM5_2_Handler
SERCOM5_3_Handler
SERCOM6_0_Handler
SERCOM6_1_Handler
SERCOM6_2_Handler
SERCOM6_3_Handler
SERCOM7_0_Handler
SERCOM7_1_Handler
SERCOM7_2_Handler
SERCOM7_3_Handler
CAN0_Handler
CAN1_Handler
USB_0_Handler
USB_1_Handler
USB_2_Handler
USB_3_Handler
GMAC_Handler
TCC0_0_Handler
TCC0_1_Handler
TCC0_2_Handler
TCC0_3_Handler
TCC0_4_Handler
TCC0_5_Handler
TCC0_6_Handler
TCC1_0_Handler
TCC1_1_Handler
TCC1_2_Handler
TCC1_3_Handler
TCC1_4_Handler
TCC2_0_Handler
TCC2_1_Handler
TCC2_2_Handler
TCC2_3_Handler
TCC3_0_Handler
TCC3_1_Handler
TCC3_2_Handler
TCC4_0_Handler
TCC4_1_Handler
TCC4_2_Handler
TC0_Handler
TC1_Handler
TC2_Handler
TC3_Handler
TC4_Handler
TC5_Handler
TC6_Handler
TC7_Handler
PDEC_0_Handler
PDEC_1_Handler
PDEC_2_Handler
ADC0_0_Handler
ADC0_1_Handler
ADC1_0_Handler
ADC1_1_Handler
AC_Handler
DAC_0_Handler
DAC_1_Handler
DAC_2_Handler
DAC_3_Handler
DAC_4_Handler
I2S_Handler
PCC_Handler
AES_Handler
TRNG_Handler
ICM_Handler
PUKCC_Handler
QSPI_Handler
SDHC0_Handler
SDHC1_Handler
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
