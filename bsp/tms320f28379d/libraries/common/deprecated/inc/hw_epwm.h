//###########################################################################
//
// FILE:    hw_epwm.h
//
// TITLE:   Definitions for the C28x EPWM registers.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef __HW_EPWM_H__
#define __HW_EPWM_H__

//*****************************************************************************
//
// The following are defines for the EPWM register offsets
//
//*****************************************************************************
#define EPWM_O_TBCTL              0x0         // Time Base Control Register
#define EPWM_O_TBCTL2             0x1         // Time Base Control Register 2
#define EPWM_O_TBCTR              0x4         // Time Base Counter Register
#define EPWM_O_TBSTS              0x5         // Time Base Status Register
#define EPWM_O_CMPCTL             0x8         // Counter Compare Control
                                              // Register
#define EPWM_O_CMPCTL2            0x9         // Counter Compare Control
                                              // Register 2
#define EPWM_O_DBCTL              0xC         // Dead-Band Generator Control
                                              // Register
#define EPWM_O_DBCTL2             0xD         // Dead-Band Generator Control
                                              // Register 2
#define EPWM_O_AQCTL              0x10        // Action Qualifier Control
                                              // Register
#define EPWM_O_AQTSRCSEL          0x11        // Action Qualifier Trigger Event
                                              // Source Select Register
#define EPWM_O_PCCTL              0x14        // PWM Chopper Control Register
#define EPWM_O_HRCNFG             0x20        // HRPWM Configuration Register
#define EPWM_O_HRPWR              0x21        // HRPWM Power Register
#define EPWM_O_HRMSTEP            0x26        // HRPWM MEP Step Register
#define EPWM_O_HRPCTL             0x2D        // High Resolution Period Control
                                              // Register
#define EPWM_O_GLDCTL             0x34        // Global PWM Load Control
                                              // Register
#define EPWM_O_GLDCFG             0x35        // Global PWM Load Config Register
#define EPWM_O_XLINK              0x38        // EPWMx Link Register
#define EPWM_O_AQCTLA             0x40        // Action Qualifier Control
                                              // Register For Output A
#define EPWM_O_AQCTLA2            0x41        // Additional Action Qualifier
                                              // Control Register For Output A
#define EPWM_O_AQCTLB             0x42        // Action Qualifier Control
                                              // Register For Output B
#define EPWM_O_AQCTLB2            0x43        // Additional Action Qualifier
                                              // Control Register For Output B
#define EPWM_O_AQSFRC             0x47        // Action Qualifier Software Force
                                              // Register
#define EPWM_O_AQCSFRC            0x49        // Action Qualifier Continuous S/W
                                              // Force Register
#define EPWM_O_DBREDHR            0x50        // Dead-Band Generator Rising Edge
                                              // Delay High Resolution Mirror
                                              // Register
#define EPWM_O_DBRED              0x51        // Dead-Band Generator Rising Edge
                                              // Delay High Resolution Mirror
                                              // Register
#define EPWM_O_DBFEDHR            0x52        // Dead-Band Generator Falling
                                              // Edge Delay High Resolution
                                              // Register
#define EPWM_O_DBFED              0x53        // Dead-Band Generator Falling
                                              // Edge Delay Count Register
#define EPWM_O_TBPHS              0x60        // Time Base Phase High
#define EPWM_O_TBPRDHR            0x62        // Time Base Period High
                                              // Resolution Register
#define EPWM_O_TBPRD              0x63        // Time Base Period Register
#define EPWM_O_CMPA               0x6A        // Counter Compare A Register
#define EPWM_O_CMPB               0x6C        // Compare B Register
#define EPWM_O_CMPC               0x6F        // Counter Compare C Register
#define EPWM_O_CMPD               0x71        // Counter Compare D Register
#define EPWM_O_GLDCTL2            0x74        // Global PWM Load Control
                                              // Register 2
#define EPWM_O_TZSEL              0x80        // Trip Zone Select Register
#define EPWM_O_TZDCSEL            0x82        // Trip Zone Digital Comparator
                                              // Select Register
#define EPWM_O_TZCTL              0x84        // Trip Zone Control Register
#define EPWM_O_TZCTL2             0x85        // Additional Trip Zone Control
                                              // Register
#define EPWM_O_TZCTLDCA           0x86        // Trip Zone Control Register
                                              // Digital Compare A
#define EPWM_O_TZCTLDCB           0x87        // Trip Zone Control Register
                                              // Digital Compare B
#define EPWM_O_TZEINT             0x8D        // Trip Zone Enable Interrupt
                                              // Register
#define EPWM_O_TZFLG              0x93        // Trip Zone Flag Register
#define EPWM_O_TZCBCFLG           0x94        // Trip Zone CBC Flag Register
#define EPWM_O_TZOSTFLG           0x95        // Trip Zone OST Flag Register
#define EPWM_O_TZCLR              0x97        // Trip Zone Clear Register
#define EPWM_O_TZCBCCLR           0x98        // Trip Zone CBC Clear Register
#define EPWM_O_TZOSTCLR           0x99        // Trip Zone OST Clear Register
#define EPWM_O_TZFRC              0x9B        // Trip Zone Force Register
#define EPWM_O_ETSEL              0xA4        // Event Trigger Selection
                                              // Register
#define EPWM_O_ETPS               0xA6        // Event Trigger Pre-Scale
                                              // Register
#define EPWM_O_ETFLG              0xA8        // Event Trigger Flag Register
#define EPWM_O_ETCLR              0xAA        // Event Trigger Clear Register
#define EPWM_O_ETFRC              0xAC        // Event Trigger Force Register
#define EPWM_O_ETINTPS            0xAE        // Event-Trigger Interrupt
                                              // Pre-Scale Register
#define EPWM_O_ETSOCPS            0xB0        // Event-Trigger SOC Pre-Scale
                                              // Register
#define EPWM_O_ETCNTINITCTL       0xB2        // Event-Trigger Counter
                                              // Initialization Control
                                              // Register
#define EPWM_O_ETCNTINIT          0xB4        // Event-Trigger Counter
                                              // Initialization Register
#define EPWM_O_DCTRIPSEL          0xC0        // Digital Compare Trip Select
                                              // Register
#define EPWM_O_DCACTL             0xC3        // Digital Compare A Control
                                              // Register
#define EPWM_O_DCBCTL             0xC4        // Digital Compare B Control
                                              // Register
#define EPWM_O_DCFCTL             0xC7        // Digital Compare Filter Control
                                              // Register
#define EPWM_O_DCCAPCTL           0xC8        // Digital Compare Capture Control
                                              // Register
#define EPWM_O_DCFOFFSET          0xC9        // Digital Compare Filter Offset
                                              // Register
#define EPWM_O_DCFOFFSETCNT       0xCA        // Digital Compare Filter Offset
                                              // Counter Register
#define EPWM_O_DCFWINDOW          0xCB        // Digital Compare Filter Window
                                              // Register
#define EPWM_O_DCFWINDOWCNT       0xCC        // Digital Compare Filter Window
                                              // Counter Register
#define EPWM_O_DCCAP              0xCF        // Digital Compare Counter Capture
                                              // Register
#define EPWM_O_DCAHTRIPSEL        0xD2        // Digital Compare AH Trip Select
#define EPWM_O_DCALTRIPSEL        0xD3        // Digital Compare AL Trip Select
#define EPWM_O_DCBHTRIPSEL        0xD4        // Digital Compare BH Trip Select
#define EPWM_O_DCBLTRIPSEL        0xD5        // Digital Compare BL Trip Select

//*****************************************************************************
//
// The following are defines for the bit fields in the TBCTL register
//
//*****************************************************************************
#define EPWM_TBCTL_CTRMODE_S      0
#define EPWM_TBCTL_CTRMODE_M      0x3         // Counter Mode
#define EPWM_TBCTL_PHSEN          0x4         // Phase Load Enable
#define EPWM_TBCTL_PRDLD          0x8         // Active Period Load
#define EPWM_TBCTL_SYNCOSEL_S     4
#define EPWM_TBCTL_SYNCOSEL_M     0x30        // Sync Output Select
#define EPWM_TBCTL_SWFSYNC        0x40        // Software Force Sync Pulse
#define EPWM_TBCTL_HSPCLKDIV_S    7
#define EPWM_TBCTL_HSPCLKDIV_M    0x380       // High Speed TBCLK Pre-scaler
#define EPWM_TBCTL_CLKDIV_S       10
#define EPWM_TBCTL_CLKDIV_M       0x1C00      // Time Base Clock Pre-scaler
#define EPWM_TBCTL_PHSDIR         0x2000      // Phase Direction Bit
#define EPWM_TBCTL_FREE_SOFT_S    14
#define EPWM_TBCTL_FREE_SOFT_M    0xC000      // Emulation Mode Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the TBCTL2 register
//
//*****************************************************************************
#define EPWM_TBCTL2_SELFCLRTRREM  0x20        // Self clear Translator reminder
#define EPWM_TBCTL2_OSHTSYNCMODE  0x40        // One shot sync mode
#define EPWM_TBCTL2_OSHTSYNC      0x80        // One shot sync
#define EPWM_TBCTL2_SYNCOSELX_S   12
#define EPWM_TBCTL2_SYNCOSELX_M   0x3000      // Syncout selection
#define EPWM_TBCTL2_PRDLDSYNC_S   14
#define EPWM_TBCTL2_PRDLDSYNC_M   0xC000      // PRD Shadow to Active Load on
                                              // SYNC Event

//*****************************************************************************
//
// The following are defines for the bit fields in the TBCTR register
//
//*****************************************************************************
#define EPWM_TBCTR_TBCTR_S        0
#define EPWM_TBCTR_TBCTR_M        0xFFFF      // Counter Value

//*****************************************************************************
//
// The following are defines for the bit fields in the TBSTS register
//
//*****************************************************************************
#define EPWM_TBSTS_CTRDIR         0x1         // Counter Direction Status
#define EPWM_TBSTS_SYNCI          0x2         // External Input Sync Status
#define EPWM_TBSTS_CTRMAX         0x4         // Counter Max Latched Status

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPCTL register
//
//*****************************************************************************
#define EPWM_CMPCTL_LOADAMODE_S   0
#define EPWM_CMPCTL_LOADAMODE_M   0x3         // Active Compare A Load
#define EPWM_CMPCTL_LOADBMODE_S   2
#define EPWM_CMPCTL_LOADBMODE_M   0xC         // Active Compare B Load
#define EPWM_CMPCTL_SHDWAMODE     0x10        // Compare A Register Block
                                              // Operating Mode
#define EPWM_CMPCTL_SHDWBMODE     0x40        // Compare B Register Block
                                              // Operating Mode
#define EPWM_CMPCTL_SHDWAFULL     0x100       // Compare A Shadow Register Full
                                              // Status
#define EPWM_CMPCTL_SHDWBFULL     0x200       // Compare B Shadow Register Full
                                              // Status
#define EPWM_CMPCTL_LOADASYNC_S   10
#define EPWM_CMPCTL_LOADASYNC_M   0xC00       // Active Compare A Load on SYNC
#define EPWM_CMPCTL_LOADBSYNC_S   12
#define EPWM_CMPCTL_LOADBSYNC_M   0x3000      // Active Compare B Load on SYNC

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPCTL2 register
//
//*****************************************************************************
#define EPWM_CMPCTL2_LOADCMODE_S  0
#define EPWM_CMPCTL2_LOADCMODE_M  0x3         // Active Compare C Load
#define EPWM_CMPCTL2_LOADDMODE_S  2
#define EPWM_CMPCTL2_LOADDMODE_M  0xC         // Active Compare D load
#define EPWM_CMPCTL2_SHDWCMODE    0x10        // Compare C Block Operating Mode
#define EPWM_CMPCTL2_SHDWDMODE    0x40        // Compare D Block Operating Mode
#define EPWM_CMPCTL2_LOADCSYNC_S  10
#define EPWM_CMPCTL2_LOADCSYNC_M  0xC00       // Active Compare C Load on SYNC
#define EPWM_CMPCTL2_LOADDSYNC_S  12
#define EPWM_CMPCTL2_LOADDSYNC_M  0x3000      // Active Compare D Load on SYNC

//*****************************************************************************
//
// The following are defines for the bit fields in the DBCTL register
//
//*****************************************************************************
#define EPWM_DBCTL_OUT_MODE_S     0
#define EPWM_DBCTL_OUT_MODE_M     0x3         // Dead Band Output Mode Control
#define EPWM_DBCTL_POLSEL_S       2
#define EPWM_DBCTL_POLSEL_M       0xC         // Polarity Select Control
#define EPWM_DBCTL_IN_MODE_S      4
#define EPWM_DBCTL_IN_MODE_M      0x30        // Dead Band Input Select Mode
                                              // Control
#define EPWM_DBCTL_LOADREDMODE_S  6
#define EPWM_DBCTL_LOADREDMODE_M  0xC0        // Active DBRED Load Mode
#define EPWM_DBCTL_LOADFEDMODE_S  8
#define EPWM_DBCTL_LOADFEDMODE_M  0x300       // Active DBFED Load Mode
#define EPWM_DBCTL_SHDWDBREDMODE  0x400       // DBRED Block Operating Mode
#define EPWM_DBCTL_SHDWDBFEDMODE  0x800       // DBFED Block Operating Mode
#define EPWM_DBCTL_OUTSWAP_S      12
#define EPWM_DBCTL_OUTSWAP_M      0x3000      // Dead Band Output Swap Control
#define EPWM_DBCTL_DEDB_MODE      0x4000      // Dead Band Dual-Edge B Mode
                                              // Control
#define EPWM_DBCTL_HALFCYCLE      0x8000      // Half Cycle Clocking Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the DBCTL2 register
//
//*****************************************************************************
#define EPWM_DBCTL2_LOADDBCTLMODE_S  0
#define EPWM_DBCTL2_LOADDBCTLMODE_M  0x3         // DBCTL Load from Shadow Mode
                                              // Select
#define EPWM_DBCTL2_SHDWDBCTLMODE  0x4         // DBCTL Load mode Select

//*****************************************************************************
//
// The following are defines for the bit fields in the AQCTL register
//
//*****************************************************************************
#define EPWM_AQCTL_LDAQAMODE_S    0
#define EPWM_AQCTL_LDAQAMODE_M    0x3         // Action Qualifier A Load Select
#define EPWM_AQCTL_LDAQBMODE_S    2
#define EPWM_AQCTL_LDAQBMODE_M    0xC         // Action Qualifier B Load Select
#define EPWM_AQCTL_SHDWAQAMODE    0x10        // Action Qualifer A Operating
                                              // Mode
#define EPWM_AQCTL_SHDWAQBMODE    0x40        // Action Qualifier B Operating
                                              // Mode
#define EPWM_AQCTL_LDAQASYNC_S    8
#define EPWM_AQCTL_LDAQASYNC_M    0x300       // AQCTLA Register Load on SYNC
#define EPWM_AQCTL_LDAQBSYNC_S    10
#define EPWM_AQCTL_LDAQBSYNC_M    0xC00       // AQCTLB Register Load on SYNC

//*****************************************************************************
//
// The following are defines for the bit fields in the AQTSRCSEL register
//
//*****************************************************************************
#define EPWM_AQTSRCSEL_T1SEL_S    0
#define EPWM_AQTSRCSEL_T1SEL_M    0xF         // T1 Event Source Select Bits
#define EPWM_AQTSRCSEL_T2SEL_S    4
#define EPWM_AQTSRCSEL_T2SEL_M    0xF0        // T2 Event Source Select Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the PCCTL register
//
//*****************************************************************************
#define EPWM_PCCTL_CHPEN          0x1         // PWM chopping enable
#define EPWM_PCCTL_OSHTWTH_S      1
#define EPWM_PCCTL_OSHTWTH_M      0x1E        // One-shot pulse width
#define EPWM_PCCTL_CHPFREQ_S      5
#define EPWM_PCCTL_CHPFREQ_M      0xE0        // Chopping clock frequency
#define EPWM_PCCTL_CHPDUTY_S      8
#define EPWM_PCCTL_CHPDUTY_M      0x700       // Chopping clock Duty cycle

//*****************************************************************************
//
// The following are defines for the bit fields in the HRCNFG register
//
//*****************************************************************************
#define EPWM_HRCNFG_EDGMODE_S     0
#define EPWM_HRCNFG_EDGMODE_M     0x3         // ePWMxA Edge Mode Select Bits
#define EPWM_HRCNFG_CTLMODE       0x4         // ePWMxA Control Mode Select Bits
#define EPWM_HRCNFG_HRLOAD_S      3
#define EPWM_HRCNFG_HRLOAD_M      0x18        // ePWMxA Shadow Mode Select Bits
#define EPWM_HRCNFG_SELOUTB       0x20        // EPWMB Output Selection Bit
#define EPWM_HRCNFG_AUTOCONV      0x40        // Autoconversion Bit
#define EPWM_HRCNFG_SWAPAB        0x80        // Swap EPWMA and EPWMB Outputs
                                              // Bit
#define EPWM_HRCNFG_EDGMODEB_S    8
#define EPWM_HRCNFG_EDGMODEB_M    0x300       // ePWMxB Edge Mode Select Bits
#define EPWM_HRCNFG_CTLMODEB      0x400       // ePWMxB Control Mode Select Bits
#define EPWM_HRCNFG_HRLOADB_S     11
#define EPWM_HRCNFG_HRLOADB_M     0x1800      // ePWMxB Shadow Mode Select Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the HRPWR register
//
//*****************************************************************************
#define EPWM_HRPWR_CALPWRON       0x8000      // Calibration Power On

//*****************************************************************************
//
// The following are defines for the bit fields in the HRMSTEP register
//
//*****************************************************************************
#define EPWM_HRMSTEP_HRMSTEP_S    0
#define EPWM_HRMSTEP_HRMSTEP_M    0xFF        // High Resolution Micro Step
                                              // Value

//*****************************************************************************
//
// The following are defines for the bit fields in the HRPCTL register
//
//*****************************************************************************
#define EPWM_HRPCTL_HRPE          0x1         // High Resolution Period Enable
#define EPWM_HRPCTL_TBPHSHRLOADE  0x4         // TBPHSHR Load Enable
#define EPWM_HRPCTL_PWMSYNCSELX_S  4
#define EPWM_HRPCTL_PWMSYNCSELX_M  0x70        // PWMSYNCX Source Select Bit:

//*****************************************************************************
//
// The following are defines for the bit fields in the GLDCTL register
//
//*****************************************************************************
#define EPWM_GLDCTL_GLD           0x1         // Global Shadow to Active load
                                              // event control
#define EPWM_GLDCTL_GLDMODE_S     1
#define EPWM_GLDCTL_GLDMODE_M     0x1E        // Shadow to Active Global Load
                                              // Pulse Selection
#define EPWM_GLDCTL_OSHTMODE      0x20        // One Shot Load mode control bit
#define EPWM_GLDCTL_GLDPRD_S      7
#define EPWM_GLDCTL_GLDPRD_M      0x380       // Global Reload Strobe Period
                                              // Select Register
#define EPWM_GLDCTL_GLDCNT_S      10
#define EPWM_GLDCTL_GLDCNT_M      0x1C00      // Global Reload Strobe Counter
                                              // Register

//*****************************************************************************
//
// The following are defines for the bit fields in the GLDCFG register
//
//*****************************************************************************
#define EPWM_GLDCFG_TBPRD_TBPRDHR  0x1         // Global load event configuration
                                              // for TBPRD:TBPRDHR
#define EPWM_GLDCFG_CMPA_CMPAHR   0x2         // Global load event configuration
                                              // for CMPA:CMPAHR
#define EPWM_GLDCFG_CMPB_CMPBHR   0x4         // Global load event configuration
                                              // for CMPB:CMPBHR
#define EPWM_GLDCFG_CMPC          0x8         // Global load event configuration
                                              // for CMPC
#define EPWM_GLDCFG_CMPD          0x10        // Global load event configuration
                                              // for CMPD
#define EPWM_GLDCFG_DBRED_DBREDHR  0x20        // Global load event configuration
                                              // for DBRED:DBREDHR
#define EPWM_GLDCFG_DBFED_DBFEDHR  0x40        // Global load event configuration
                                              // for DBFED:DBFEDHR
#define EPWM_GLDCFG_DBCTL         0x80        // Global load event configuration
                                              // for DBCTL
#define EPWM_GLDCFG_AQCTLA_AQCTLA2  0x100       // Global load event configuration
                                              // for AQCTLA/A2
#define EPWM_GLDCFG_AQCTLB_AQCTLB2  0x200       // Global load event configuration
                                              // for AQCTLB/B2
#define EPWM_GLDCFG_AQCSFRC       0x400       // Global load event configuration
                                              // for AQCSFRC

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWMXLINK register
//
//*****************************************************************************
#define EPWM_XLINK_TBPRDLINK_S    0
#define EPWM_XLINK_TBPRDLINK_M    0xF         // TBPRD:TBPRDHR  Link
#define EPWM_XLINK_CMPALINK_S     4
#define EPWM_XLINK_CMPALINK_M     0xF0        // CMPA:CMPAHR Link
#define EPWM_XLINK_CMPBLINK_S     8
#define EPWM_XLINK_CMPBLINK_M     0xF00       // CMPB:CMPBHR Link
#define EPWM_XLINK_CMPCLINK_S     12
#define EPWM_XLINK_CMPCLINK_M     0xF000      // CMPC Link
#define EPWM_XLINK_CMPDLINK_S     16
#define EPWM_XLINK_CMPDLINK_M     0xF0000     // CMPD Link
#define EPWM_XLINK_GLDCTL2LINK_S  28
#define EPWM_XLINK_GLDCTL2LINK_M  0xF0000000  // GLDCTL2 Link

//*****************************************************************************
//
// The following are defines for the bit fields in the AQCTLA register
//
//*****************************************************************************
#define EPWM_AQCTLA_ZRO_S         0
#define EPWM_AQCTLA_ZRO_M         0x3         // Action Counter = Zero
#define EPWM_AQCTLA_PRD_S         2
#define EPWM_AQCTLA_PRD_M         0xC         // Action Counter = Period
#define EPWM_AQCTLA_CAU_S         4
#define EPWM_AQCTLA_CAU_M         0x30        // Action Counter = Compare A Up
#define EPWM_AQCTLA_CAD_S         6
#define EPWM_AQCTLA_CAD_M         0xC0        // Action Counter = Compare A Down
#define EPWM_AQCTLA_CBU_S         8
#define EPWM_AQCTLA_CBU_M         0x300       // Action Counter = Compare B Up
#define EPWM_AQCTLA_CBD_S         10
#define EPWM_AQCTLA_CBD_M         0xC00       // Action Counter = Compare B Down

//*****************************************************************************
//
// The following are defines for the bit fields in the AQCTLA2 register
//
//*****************************************************************************
#define EPWM_AQCTLA2_T1U_S        0
#define EPWM_AQCTLA2_T1U_M        0x3         // Action when event occurs on T1
                                              // in UP-Count
#define EPWM_AQCTLA2_T1D_S        2
#define EPWM_AQCTLA2_T1D_M        0xC         // Action when event occurs on T1
                                              // in DOWN-Count
#define EPWM_AQCTLA2_T2U_S        4
#define EPWM_AQCTLA2_T2U_M        0x30        // Action when event occurs on T2
                                              // in UP-Count
#define EPWM_AQCTLA2_T2D_S        6
#define EPWM_AQCTLA2_T2D_M        0xC0        // Action when event occurs on T2
                                              // in DOWN-Count

//*****************************************************************************
//
// The following are defines for the bit fields in the AQCTLB register
//
//*****************************************************************************
#define EPWM_AQCTLB_ZRO_S         0
#define EPWM_AQCTLB_ZRO_M         0x3         // Action Counter = Zero
#define EPWM_AQCTLB_PRD_S         2
#define EPWM_AQCTLB_PRD_M         0xC         // Action Counter = Period
#define EPWM_AQCTLB_CAU_S         4
#define EPWM_AQCTLB_CAU_M         0x30        // Action Counter = Compare A Up
#define EPWM_AQCTLB_CAD_S         6
#define EPWM_AQCTLB_CAD_M         0xC0        // Action Counter = Compare A Down
#define EPWM_AQCTLB_CBU_S         8
#define EPWM_AQCTLB_CBU_M         0x300       // Action Counter = Compare B Up
#define EPWM_AQCTLB_CBD_S         10
#define EPWM_AQCTLB_CBD_M         0xC00       // Action Counter = Compare B Down

//*****************************************************************************
//
// The following are defines for the bit fields in the AQCTLB2 register
//
//*****************************************************************************
#define EPWM_AQCTLB2_T1U_S        0
#define EPWM_AQCTLB2_T1U_M        0x3         // Action when event occurs on T1
                                              // in UP-Count
#define EPWM_AQCTLB2_T1D_S        2
#define EPWM_AQCTLB2_T1D_M        0xC         // Action when event occurs on T1
                                              // in DOWN-Count
#define EPWM_AQCTLB2_T2U_S        4
#define EPWM_AQCTLB2_T2U_M        0x30        // Action when event occurs on T2
                                              // in UP-Count
#define EPWM_AQCTLB2_T2D_S        6
#define EPWM_AQCTLB2_T2D_M        0xC0        // Action when event occurs on T2
                                              // in DOWN-Count

//*****************************************************************************
//
// The following are defines for the bit fields in the AQSFRC register
//
//*****************************************************************************
#define EPWM_AQSFRC_ACTSFA_S      0
#define EPWM_AQSFRC_ACTSFA_M      0x3         // Action when One-time SW Force A
                                              // Invoked
#define EPWM_AQSFRC_OTSFA         0x4         // One-time SW Force A Output
#define EPWM_AQSFRC_ACTSFB_S      3
#define EPWM_AQSFRC_ACTSFB_M      0x18        // Action when One-time SW Force B
                                              // Invoked
#define EPWM_AQSFRC_OTSFB         0x20        // One-time SW Force A Output
#define EPWM_AQSFRC_RLDCSF_S      6
#define EPWM_AQSFRC_RLDCSF_M      0xC0        // Reload from Shadow Options

//*****************************************************************************
//
// The following are defines for the bit fields in the AQCSFRC register
//
//*****************************************************************************
#define EPWM_AQCSFRC_CSFA_S       0
#define EPWM_AQCSFRC_CSFA_M       0x3         // Continuous Software Force on
                                              // output A
#define EPWM_AQCSFRC_CSFB_S       2
#define EPWM_AQCSFRC_CSFB_M       0xC         // Continuous Software Force on
                                              // output B

//*****************************************************************************
//
// The following are defines for the bit fields in the DBREDHR register
//
//*****************************************************************************
#define EPWM_DBREDHR_DBREDHR_S    9
#define EPWM_DBREDHR_DBREDHR_M    0xFE00      // DBREDHR High Resolution Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the DBRED register
//
//*****************************************************************************
#define EPWM_DBRED_DBRED_S        0
#define EPWM_DBRED_DBRED_M        0xFFFF      // Rising edge delay value

//*****************************************************************************
//
// The following are defines for the bit fields in the DBFEDHR register
//
//*****************************************************************************
#define EPWM_DBFEDHR_DBFEDHR_S    9
#define EPWM_DBFEDHR_DBFEDHR_M    0xFE00      // DBFEDHR High Resolution Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the DBFED register
//
//*****************************************************************************
#define EPWM_DBFED_DBFED_S        0
#define EPWM_DBFED_DBFED_M        0xFFFF      // Falling edge delay value

//*****************************************************************************
//
// The following are defines for the bit fields in the TBPHS register
//
//*****************************************************************************
#define EPWM_TBPHS_TBPHSHR_S      0
#define EPWM_TBPHS_TBPHSHR_M      0xFFFF      // Extension Register for HRPWM
                                              // Phase (8-bits)
#define EPWM_TBPHS_TBPHS_S        16
#define EPWM_TBPHS_TBPHS_M        0xFFFF0000  // Phase Offset Register

//*****************************************************************************
//
// The following are defines for the bit fields in the TBPRDHR register
//
//*****************************************************************************
#define EPWM_TBPRDHR_TBPRDHR_S    0
#define EPWM_TBPRDHR_TBPRDHR_M    0xFFFF      // High res Time base period
                                              // register

//*****************************************************************************
//
// The following are defines for the bit fields in the TBPRD register
//
//*****************************************************************************
#define EPWM_TBPRD_TBPRD_S        0
#define EPWM_TBPRD_TBPRD_M        0xFFFF      // Time base period register

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPA register
//
//*****************************************************************************
#define EPWM_CMPA_CMPAHR_S        0
#define EPWM_CMPA_CMPAHR_M        0xFFFF      // Compare A HRPWM Extension
                                              // Register
#define EPWM_CMPA_CMPA_S          16
#define EPWM_CMPA_CMPA_M          0xFFFF0000  // Compare A Register

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPB register
//
//*****************************************************************************
#define EPWM_CMPB_CMPB_S          16
#define EPWM_CMPB_CMPB_M          0xFFFF0000  // Compare B Register

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPC register
//
//*****************************************************************************
#define EPWM_CMPC_CMPC_S          0
#define EPWM_CMPC_CMPC_M          0xFFFF      // Compare C Register

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPD register
//
//*****************************************************************************
#define EPWM_CMPD_CMPD_S          0
#define EPWM_CMPD_CMPD_M          0xFFFF      // Compare D Register

//*****************************************************************************
//
// The following are defines for the bit fields in the GLDCTL2 register
//
//*****************************************************************************
#define EPWM_GLDCTL2_OSHTLD       0x1         // Enable reload event in one shot
                                              // mode
#define EPWM_GLDCTL2_GFRCLD       0x2         // Force reload event in one shot
                                              // mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TZSEL register
//
//*****************************************************************************
#define EPWM_TZSEL_CBC1           0x1         // TZ1 CBC select
#define EPWM_TZSEL_CBC2           0x2         // TZ2 CBC select
#define EPWM_TZSEL_CBC3           0x4         // TZ3 CBC select
#define EPWM_TZSEL_CBC4           0x8         // TZ4 CBC select
#define EPWM_TZSEL_CBC5           0x10        // TZ5 CBC select
#define EPWM_TZSEL_CBC6           0x20        // TZ6 CBC select
#define EPWM_TZSEL_DCAEVT2        0x40        // DCAEVT2 CBC select
#define EPWM_TZSEL_DCBEVT2        0x80        // DCBEVT2 CBC select
#define EPWM_TZSEL_OSHT1          0x100       // One-shot TZ1 select
#define EPWM_TZSEL_OSHT2          0x200       // One-shot TZ2 select
#define EPWM_TZSEL_OSHT3          0x400       // One-shot TZ3 select
#define EPWM_TZSEL_OSHT4          0x800       // One-shot TZ4 select
#define EPWM_TZSEL_OSHT5          0x1000      // One-shot TZ5 select
#define EPWM_TZSEL_OSHT6          0x2000      // One-shot TZ6 select
#define EPWM_TZSEL_DCAEVT1        0x4000      // One-shot DCAEVT1 select
#define EPWM_TZSEL_DCBEVT1        0x8000      // One-shot DCBEVT1 select

//*****************************************************************************
//
// The following are defines for the bit fields in the TZDCSEL register
//
//*****************************************************************************
#define EPWM_TZDCSEL_DCAEVT1_S    0
#define EPWM_TZDCSEL_DCAEVT1_M    0x7         // Digital Compare Output A Event
                                              // 1
#define EPWM_TZDCSEL_DCAEVT2_S    3
#define EPWM_TZDCSEL_DCAEVT2_M    0x38        // Digital Compare Output A Event
                                              // 2
#define EPWM_TZDCSEL_DCBEVT1_S    6
#define EPWM_TZDCSEL_DCBEVT1_M    0x1C0       // Digital Compare Output B Event
                                              // 1
#define EPWM_TZDCSEL_DCBEVT2_S    9
#define EPWM_TZDCSEL_DCBEVT2_M    0xE00       // Digital Compare Output B Event
                                              // 2

//*****************************************************************************
//
// The following are defines for the bit fields in the TZCTL register
//
//*****************************************************************************
#define EPWM_TZCTL_TZA_S          0
#define EPWM_TZCTL_TZA_M          0x3         // TZ1 to TZ6 Trip Action On
                                              // EPWMxA
#define EPWM_TZCTL_TZB_S          2
#define EPWM_TZCTL_TZB_M          0xC         // TZ1 to TZ6 Trip Action On
                                              // EPWMxB
#define EPWM_TZCTL_DCAEVT1_S      4
#define EPWM_TZCTL_DCAEVT1_M      0x30        // EPWMxA action on DCAEVT1
#define EPWM_TZCTL_DCAEVT2_S      6
#define EPWM_TZCTL_DCAEVT2_M      0xC0        // EPWMxA action on DCAEVT2
#define EPWM_TZCTL_DCBEVT1_S      8
#define EPWM_TZCTL_DCBEVT1_M      0x300       // EPWMxB action on DCBEVT1
#define EPWM_TZCTL_DCBEVT2_S      10
#define EPWM_TZCTL_DCBEVT2_M      0xC00       // EPWMxB action on DCBEVT2

//*****************************************************************************
//
// The following are defines for the bit fields in the TZCTL2 register
//
//*****************************************************************************
#define EPWM_TZCTL2_TZAU_S        0
#define EPWM_TZCTL2_TZAU_M        0x7         // Trip Action On EPWMxA while
                                              // Count direction is UP
#define EPWM_TZCTL2_TZAD_S        3
#define EPWM_TZCTL2_TZAD_M        0x38        // Trip Action On EPWMxA while
                                              // Count direction is DOWN
#define EPWM_TZCTL2_TZBU_S        6
#define EPWM_TZCTL2_TZBU_M        0x1C0       // Trip Action On EPWMxB while
                                              // Count direction is UP
#define EPWM_TZCTL2_TZBD_S        9
#define EPWM_TZCTL2_TZBD_M        0xE00       // Trip Action On EPWMxB while
                                              // Count direction is DOWN
#define EPWM_TZCTL2_ETZE          0x8000      // TZCTL2 Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TZCTLDCA register
//
//*****************************************************************************
#define EPWM_TZCTLDCA_DCAEVT1U_S  0
#define EPWM_TZCTLDCA_DCAEVT1U_M  0x7         // DCAEVT1 Action On EPWMxA while
                                              // Count direction is UP
#define EPWM_TZCTLDCA_DCAEVT1D_S  3
#define EPWM_TZCTLDCA_DCAEVT1D_M  0x38        // DCAEVT1 Action On EPWMxA while
                                              // Count direction is DOWN
#define EPWM_TZCTLDCA_DCAEVT2U_S  6
#define EPWM_TZCTLDCA_DCAEVT2U_M  0x1C0       // DCAEVT2 Action On EPWMxA while
                                              // Count direction is UP
#define EPWM_TZCTLDCA_DCAEVT2D_S  9
#define EPWM_TZCTLDCA_DCAEVT2D_M  0xE00       // DCAEVT2 Action On EPWMxA while
                                              // Count direction is DOWN

//*****************************************************************************
//
// The following are defines for the bit fields in the TZCTLDCB register
//
//*****************************************************************************
#define EPWM_TZCTLDCB_DCBEVT1U_S  0
#define EPWM_TZCTLDCB_DCBEVT1U_M  0x7         // DCBEVT1 Action On EPWMxA while
                                              // Count direction is UP
#define EPWM_TZCTLDCB_DCBEVT1D_S  3
#define EPWM_TZCTLDCB_DCBEVT1D_M  0x38        // DCBEVT1 Action On EPWMxA while
                                              // Count direction is DOWN
#define EPWM_TZCTLDCB_DCBEVT2U_S  6
#define EPWM_TZCTLDCB_DCBEVT2U_M  0x1C0       // DCBEVT2 Action On EPWMxA while
                                              // Count direction is UP
#define EPWM_TZCTLDCB_DCBEVT2D_S  9
#define EPWM_TZCTLDCB_DCBEVT2D_M  0xE00       // DCBEVT2 Action On EPWMxA while
                                              // Count direction is DOWN

//*****************************************************************************
//
// The following are defines for the bit fields in the TZEINT register
//
//*****************************************************************************
#define EPWM_TZEINT_CBC           0x2         // Trip Zones Cycle By Cycle Int
                                              // Enable
#define EPWM_TZEINT_OST           0x4         // Trip Zones One Shot Int Enable
#define EPWM_TZEINT_DCAEVT1       0x8         // Digital Compare A Event 1 Int
                                              // Enable
#define EPWM_TZEINT_DCAEVT2       0x10        // Digital Compare A Event 2 Int
                                              // Enable
#define EPWM_TZEINT_DCBEVT1       0x20        // Digital Compare B Event 1 Int
                                              // Enable
#define EPWM_TZEINT_DCBEVT2       0x40        // Digital Compare B Event 2 Int
                                              // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TZFLG register
//
//*****************************************************************************
#define EPWM_TZFLG_INT            0x1         // Global Int Status Flag
#define EPWM_TZFLG_CBC            0x2         // Trip Zones Cycle By Cycle Flag
#define EPWM_TZFLG_OST            0x4         // Trip Zones One Shot Flag
#define EPWM_TZFLG_DCAEVT1        0x8         // Digital Compare A Event 1 Flag
#define EPWM_TZFLG_DCAEVT2        0x10        // Digital Compare A Event 2 Flag
#define EPWM_TZFLG_DCBEVT1        0x20        // Digital Compare B Event 1 Flag
#define EPWM_TZFLG_DCBEVT2        0x40        // Digital Compare B Event 2 Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the TZCBCFLG register
//
//*****************************************************************************
#define EPWM_TZCBCFLG_CBC1        0x1         // Latched Status Flag for CBC1
                                              // Trip Latch
#define EPWM_TZCBCFLG_CBC2        0x2         // Latched Status Flag for CBC2
                                              // Trip Latch
#define EPWM_TZCBCFLG_CBC3        0x4         // Latched Status Flag for CBC3
                                              // Trip Latch
#define EPWM_TZCBCFLG_CBC4        0x8         // Latched Status Flag for CBC4
                                              // Trip Latch
#define EPWM_TZCBCFLG_CBC5        0x10        // Latched Status Flag for CBC5
                                              // Trip Latch
#define EPWM_TZCBCFLG_CBC6        0x20        // Latched Status Flag for CBC6
                                              // Trip Latch
#define EPWM_TZCBCFLG_DCAEVT2     0x40        // Latched Status Flag for Digital
                                              // Compare Output A Event 2
#define EPWM_TZCBCFLG_DCBEVT2     0x80        // Latched Status Flag for Digital
                                              // Compare Output B Event 2

//*****************************************************************************
//
// The following are defines for the bit fields in the TZOSTFLG register
//
//*****************************************************************************
#define EPWM_TZOSTFLG_OST1        0x1         // Latched Status Flag for OST1
                                              // Trip Latch
#define EPWM_TZOSTFLG_OST2        0x2         // Latched Status Flag for OST2
                                              // Trip Latch
#define EPWM_TZOSTFLG_OST3        0x4         // Latched Status Flag for OST3
                                              // Trip Latch
#define EPWM_TZOSTFLG_OST4        0x8         // Latched Status Flag for OST4
                                              // Trip Latch
#define EPWM_TZOSTFLG_OST5        0x10        // Latched Status Flag for OST5
                                              // Trip Latch
#define EPWM_TZOSTFLG_OST6        0x20        // Latched Status Flag for OST6
                                              // Trip Latch
#define EPWM_TZOSTFLG_DCAEVT2     0x40        // Latched Status Flag for Digital
                                              // Compare Output A Event 1
#define EPWM_TZOSTFLG_DCBEVT2     0x80        // Latched Status Flag for Digital
                                              // Compare Output B Event 1

//*****************************************************************************
//
// The following are defines for the bit fields in the TZCLR register
//
//*****************************************************************************
#define EPWM_TZCLR_INT            0x1         // Global Interrupt Clear Flag
#define EPWM_TZCLR_CBC            0x2         // Cycle-By-Cycle Flag Clear
#define EPWM_TZCLR_OST            0x4         // One-Shot Flag Clear
#define EPWM_TZCLR_DCAEVT1        0x8         // DCAVET1 Flag Clear
#define EPWM_TZCLR_DCAEVT2        0x10        // DCAEVT2 Flag Clear
#define EPWM_TZCLR_DCBEVT1        0x20        // DCBEVT1 Flag Clear
#define EPWM_TZCLR_DCBEVT2        0x40        // DCBEVT2 Flag Clear
#define EPWM_TZCLR_CBCPULSE_S     14
#define EPWM_TZCLR_CBCPULSE_M     0xC000      // Clear Pulse for CBC Trip Latch

//*****************************************************************************
//
// The following are defines for the bit fields in the TZCBCCLR register
//
//*****************************************************************************
#define EPWM_TZCBCCLR_CBC1        0x1         // Clear Flag for Cycle-By-Cycle
                                              // (CBC1) Trip Latch
#define EPWM_TZCBCCLR_CBC2        0x2         // Clear Flag for Cycle-By-Cycle
                                              // (CBC2) Trip Latch
#define EPWM_TZCBCCLR_CBC3        0x4         // Clear Flag for Cycle-By-Cycle
                                              // (CBC3) Trip Latch
#define EPWM_TZCBCCLR_CBC4        0x8         // Clear Flag for Cycle-By-Cycle
                                              // (CBC4) Trip Latch
#define EPWM_TZCBCCLR_CBC5        0x10        // Clear Flag for Cycle-By-Cycle
                                              // (CBC5) Trip Latch
#define EPWM_TZCBCCLR_CBC6        0x20        // Clear Flag for Cycle-By-Cycle
                                              // (CBC6) Trip Latch
#define EPWM_TZCBCCLR_DCAEVT2     0x40        // Clear Flag forDCAEVT2 selected
                                              // for CBC
#define EPWM_TZCBCCLR_DCBEVT2     0x80        // Clear Flag for DCBEVT2 selected
                                              // for CBC

//*****************************************************************************
//
// The following are defines for the bit fields in the TZOSTCLR register
//
//*****************************************************************************
#define EPWM_TZOSTCLR_OST1        0x1         // Clear Flag for Oneshot (OST1)
                                              // Trip Latch
#define EPWM_TZOSTCLR_OST2        0x2         // Clear Flag for Oneshot (OST2)
                                              // Trip Latch
#define EPWM_TZOSTCLR_OST3        0x4         // Clear Flag for Oneshot (OST3)
                                              // Trip Latch
#define EPWM_TZOSTCLR_OST4        0x8         // Clear Flag for Oneshot (OST4)
                                              // Trip Latch
#define EPWM_TZOSTCLR_OST5        0x10        // Clear Flag for Oneshot (OST5)
                                              // Trip Latch
#define EPWM_TZOSTCLR_OST6        0x20        // Clear Flag for Oneshot (OST6)
                                              // Trip Latch
#define EPWM_TZOSTCLR_DCAEVT2     0x40        // Clear Flag for DCAEVT1 selected
                                              // for OST
#define EPWM_TZOSTCLR_DCBEVT2     0x80        // Clear Flag for DCBEVT1 selected
                                              // for OST

//*****************************************************************************
//
// The following are defines for the bit fields in the TZFRC register
//
//*****************************************************************************
#define EPWM_TZFRC_CBC            0x2         // Force Trip Zones Cycle By Cycle
                                              // Event
#define EPWM_TZFRC_OST            0x4         // Force Trip Zones One Shot Event
#define EPWM_TZFRC_DCAEVT1        0x8         // Force Digital Compare A Event 1
#define EPWM_TZFRC_DCAEVT2        0x10        // Force Digital Compare A Event 2
#define EPWM_TZFRC_DCBEVT1        0x20        // Force Digital Compare B Event 1
#define EPWM_TZFRC_DCBEVT2        0x40        // Force Digital Compare B Event 2

//*****************************************************************************
//
// The following are defines for the bit fields in the ETSEL register
//
//*****************************************************************************
#define EPWM_ETSEL_INTSEL_S       0
#define EPWM_ETSEL_INTSEL_M       0x7         // EPWMxINTn Select
#define EPWM_ETSEL_INTEN          0x8         // EPWMxINTn Enable
#define EPWM_ETSEL_SOCASELCMP     0x10        // EPWMxSOCA Compare Select
#define EPWM_ETSEL_SOCBSELCMP     0x20        // EPWMxSOCB Compare Select
#define EPWM_ETSEL_INTSELCMP      0x40        // EPWMxINT Compare Select
#define EPWM_ETSEL_SOCASEL_S      8
#define EPWM_ETSEL_SOCASEL_M      0x700       // Start of Conversion A Select
#define EPWM_ETSEL_SOCAEN         0x800       // Start of Conversion A Enable
#define EPWM_ETSEL_SOCBSEL_S      12
#define EPWM_ETSEL_SOCBSEL_M      0x7000      // Start of Conversion B Select
#define EPWM_ETSEL_SOCBEN         0x8000      // Start of Conversion B Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ETPS register
//
//*****************************************************************************
#define EPWM_ETPS_INTPRD_S        0
#define EPWM_ETPS_INTPRD_M        0x3         // EPWMxINTn Period Select
#define EPWM_ETPS_INTCNT_S        2
#define EPWM_ETPS_INTCNT_M        0xC         // EPWMxINTn Counter Register
#define EPWM_ETPS_INTPSSEL        0x10        // EPWMxINTn Pre-Scale Selection
                                              // Bits
#define EPWM_ETPS_SOCPSSEL        0x20        // EPWMxSOC A/B  Pre-Scale
                                              // Selection Bits
#define EPWM_ETPS_SOCAPRD_S       8
#define EPWM_ETPS_SOCAPRD_M       0x300       // EPWMxSOCA Period Select
#define EPWM_ETPS_SOCACNT_S       10
#define EPWM_ETPS_SOCACNT_M       0xC00       // EPWMxSOCA Counter Register
#define EPWM_ETPS_SOCBPRD_S       12
#define EPWM_ETPS_SOCBPRD_M       0x3000      // EPWMxSOCB Period Select
#define EPWM_ETPS_SOCBCNT_S       14
#define EPWM_ETPS_SOCBCNT_M       0xC000      // EPWMxSOCB Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the ETFLG register
//
//*****************************************************************************
#define EPWM_ETFLG_INT            0x1         // EPWMxINTn Flag
#define EPWM_ETFLG_SOCA           0x4         // EPWMxSOCA Flag
#define EPWM_ETFLG_SOCB           0x8         // EPWMxSOCB Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ETCLR register
//
//*****************************************************************************
#define EPWM_ETCLR_INT            0x1         // EPWMxINTn Clear
#define EPWM_ETCLR_SOCA           0x4         // EPWMxSOCA Clear
#define EPWM_ETCLR_SOCB           0x8         // EPWMxSOCB Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the ETFRC register
//
//*****************************************************************************
#define EPWM_ETFRC_INT            0x1         // EPWMxINTn Force
#define EPWM_ETFRC_SOCA           0x4         // EPWMxSOCA Force
#define EPWM_ETFRC_SOCB           0x8         // EPWMxSOCB Force

//*****************************************************************************
//
// The following are defines for the bit fields in the ETINTPS register
//
//*****************************************************************************
#define EPWM_ETINTPS_INTPRD2_S    0
#define EPWM_ETINTPS_INTPRD2_M    0xF         // EPWMxINTn Period Select
#define EPWM_ETINTPS_INTCNT2_S    4
#define EPWM_ETINTPS_INTCNT2_M    0xF0        // EPWMxINTn Counter Register

//*****************************************************************************
//
// The following are defines for the bit fields in the ETSOCPS register
//
//*****************************************************************************
#define EPWM_ETSOCPS_SOCAPRD2_S   0
#define EPWM_ETSOCPS_SOCAPRD2_M   0xF         // EPWMxSOCA Period Select
#define EPWM_ETSOCPS_SOCACNT2_S   4
#define EPWM_ETSOCPS_SOCACNT2_M   0xF0        // EPWMxSOCA Counter Register
#define EPWM_ETSOCPS_SOCBPRD2_S   8
#define EPWM_ETSOCPS_SOCBPRD2_M   0xF00       // EPWMxSOCB Period Select
#define EPWM_ETSOCPS_SOCBCNT2_S   12
#define EPWM_ETSOCPS_SOCBCNT2_M   0xF000      // EPWMxSOCB Counter Register

//*****************************************************************************
//
// The following are defines for the bit fields in the ETCNTINITCTL register
//
//*****************************************************************************
#define EPWM_ETCNTINITCTL_INTINITFRC  0x400       // EPWMxINT Counter Initialization
                                              // Force
#define EPWM_ETCNTINITCTL_SOCAINITFRC  0x800       // EPWMxSOCA Counter
                                              // Initialization Force
#define EPWM_ETCNTINITCTL_SOCBINITFRC  0x1000      // EPWMxSOCB Counter
                                              // Initialization Force
#define EPWM_ETCNTINITCTL_INTINITEN  0x2000      // EPWMxINT Counter Initialization
                                              // Enable
#define EPWM_ETCNTINITCTL_SOCAINITEN  0x4000      // EPWMxSOCA Counter
                                              // Initialization Enable
#define EPWM_ETCNTINITCTL_SOCBINITEN  0x8000      // EPWMxSOCB Counter
                                              // Initialization Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ETCNTINIT register
//
//*****************************************************************************
#define EPWM_ETCNTINIT_INTINIT_S  0
#define EPWM_ETCNTINIT_INTINIT_M  0xF         // EPWMxINT Counter Initialization
                                              // Bits
#define EPWM_ETCNTINIT_SOCAINIT_S  4
#define EPWM_ETCNTINIT_SOCAINIT_M  0xF0        // EPWMxSOCA Counter
                                              // Initialization Bits
#define EPWM_ETCNTINIT_SOCBINIT_S  8
#define EPWM_ETCNTINIT_SOCBINIT_M  0xF00       // EPWMxSOCB Counter
                                              // Initialization Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the DCTRIPSEL register
//
//*****************************************************************************
#define EPWM_DCTRIPSEL_DCAHCOMPSEL_S  0
#define EPWM_DCTRIPSEL_DCAHCOMPSEL_M  0xF         // Digital Compare A High COMP
                                              // Input Select
#define EPWM_DCTRIPSEL_DCALCOMPSEL_S  4
#define EPWM_DCTRIPSEL_DCALCOMPSEL_M  0xF0        // Digital Compare A Low COMP
                                              // Input Select
#define EPWM_DCTRIPSEL_DCBHCOMPSEL_S  8
#define EPWM_DCTRIPSEL_DCBHCOMPSEL_M  0xF00       // Digital Compare B High COMP
                                              // Input Select
#define EPWM_DCTRIPSEL_DCBLCOMPSEL_S  12
#define EPWM_DCTRIPSEL_DCBLCOMPSEL_M  0xF000      // Digital Compare B Low COMP
                                              // Input Select

//*****************************************************************************
//
// The following are defines for the bit fields in the DCACTL register
//
//*****************************************************************************
#define EPWM_DCACTL_EVT1SRCSEL    0x1         // DCAEVT1 Source Signal
#define EPWM_DCACTL_EVT1FRCSYNCSEL  0x2         // DCAEVT1 Force Sync Signal
#define EPWM_DCACTL_EVT1SOCE      0x4         // DCAEVT1 SOC Enable
#define EPWM_DCACTL_EVT1SYNCE     0x8         // DCAEVT1 SYNC Enable
#define EPWM_DCACTL_EVT2SRCSEL    0x100       // DCAEVT2 Source Signal
#define EPWM_DCACTL_EVT2FRCSYNCSEL  0x200       // DCAEVT2 Force Sync Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the DCBCTL register
//
//*****************************************************************************
#define EPWM_DCBCTL_EVT1SRCSEL    0x1         // DCBEVT1 Source Signal
#define EPWM_DCBCTL_EVT1FRCSYNCSEL  0x2         // DCBEVT1 Force Sync Signal
#define EPWM_DCBCTL_EVT1SOCE      0x4         // DCBEVT1 SOC Enable
#define EPWM_DCBCTL_EVT1SYNCE     0x8         // DCBEVT1 SYNC Enable
#define EPWM_DCBCTL_EVT2SRCSEL    0x100       // DCBEVT2 Source Signal
#define EPWM_DCBCTL_EVT2FRCSYNCSEL  0x200       // DCBEVT2 Force Sync Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the DCFCTL register
//
//*****************************************************************************
#define EPWM_DCFCTL_SRCSEL_S      0
#define EPWM_DCFCTL_SRCSEL_M      0x3         // Filter Block Signal Source
                                              // Select
#define EPWM_DCFCTL_BLANKE        0x4         // Blanking Enable/Disable
#define EPWM_DCFCTL_BLANKINV      0x8         // Blanking Window Inversion
#define EPWM_DCFCTL_PULSESEL_S    4
#define EPWM_DCFCTL_PULSESEL_M    0x30        // Pulse Select for Blanking &
                                              // Capture Alignment

//*****************************************************************************
//
// The following are defines for the bit fields in the DCCAPCTL register
//
//*****************************************************************************
#define EPWM_DCCAPCTL_CAPE        0x1         // Counter Capture Enable
#define EPWM_DCCAPCTL_SHDWMODE    0x2         // Counter Capture Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the DCFOFFSET register
//
//*****************************************************************************
#define EPWM_DCFOFFSET_DCFOFFSET_S  0
#define EPWM_DCFOFFSET_DCFOFFSET_M  0xFFFF      // Blanking Offset

//*****************************************************************************
//
// The following are defines for the bit fields in the DCFOFFSETCNT register
//
//*****************************************************************************
#define EPWM_DCFOFFSETCNT_DCFOFFSETCNT_S  0
#define EPWM_DCFOFFSETCNT_DCFOFFSETCNT_M  0xFFFF      // Blanking Offset Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the DCFWINDOW register
//
//*****************************************************************************
#define EPWM_DCFWINDOW_DCFWINDOW_S  0
#define EPWM_DCFWINDOW_DCFWINDOW_M  0xFFFF      // Digital Compare Filter Window
                                              // Register

//*****************************************************************************
//
// The following are defines for the bit fields in the DCFWINDOWCNT register
//
//*****************************************************************************
#define EPWM_DCFWINDOWCNT_DCFWINDOWCNT_S  0
#define EPWM_DCFWINDOWCNT_DCFWINDOWCNT_M  0xFFFF      // Digital Compare Filter Window
                                              // Counter Register

//*****************************************************************************
//
// The following are defines for the bit fields in the DCCAP register
//
//*****************************************************************************
#define EPWM_DCCAP_DCCAP_S        0
#define EPWM_DCCAP_DCCAP_M        0xFFFF      // Time Base Counter Capture
                                              // Register

//*****************************************************************************
//
// The following are defines for the bit fields in the DCAHTRIPSEL register
//
//*****************************************************************************
#define EPWM_DCAHTRIPSEL_TRIPINPUT1  0x1         // Trip Input 1 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT2  0x2         // Trip Input 2 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT3  0x4         // Trip Input 3 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT4  0x8         // Trip Input 4 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT5  0x10        // Trip Input 5 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT6  0x20        // Trip Input 6 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT7  0x40        // Trip Input 7 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT8  0x80        // Trip Input 8 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT9  0x100       // Trip Input 9 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT10  0x200       // Trip Input 10 Select to DCAH
                                              // Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT11  0x400       // Trip Input 11 Select to DCAH
                                              // Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT12  0x800       // Trip Input 12 Select to DCAH
                                              // Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT13  0x1000      // Trip Input 13 Select to DCAH
                                              // Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT14  0x2000      // Trip Input 14 Select to DCAH
                                              // Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT15  0x4000      // Trip Input 15 Select to DCAH
                                              // Mux

//*****************************************************************************
//
// The following are defines for the bit fields in the DCALTRIPSEL register
//
//*****************************************************************************
#define EPWM_DCALTRIPSEL_TRIPINPUT1  0x1         // Trip Input 1 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT2  0x2         // Trip Input 2 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT3  0x4         // Trip Input 3 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT4  0x8         // Trip Input 4 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT5  0x10        // Trip Input 5 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT6  0x20        // Trip Input 6 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT7  0x40        // Trip Input 7 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT8  0x80        // Trip Input 8 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT9  0x100       // Trip Input 9 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT10  0x200       // Trip Input 10 Select to DCAL
                                              // Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT11  0x400       // Trip Input 11 Select to DCAL
                                              // Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT12  0x800       // Trip Input 12 Select to DCAL
                                              // Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT13  0x1000      // Trip Input 13 Select to DCAL
                                              // Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT14  0x2000      // Trip Input 14 Select to DCAL
                                              // Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT15  0x4000      // Trip Input 15 Select to DCAL
                                              // Mux

//*****************************************************************************
//
// The following are defines for the bit fields in the DCBHTRIPSEL register
//
//*****************************************************************************
#define EPWM_DCBHTRIPSEL_TRIPINPUT1  0x1         // Trip Input 1 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT2  0x2         // Trip Input 2 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT3  0x4         // Trip Input 3 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT4  0x8         // Trip Input 4 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT5  0x10        // Trip Input 5 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT6  0x20        // Trip Input 6 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT7  0x40        // Trip Input 7 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT8  0x80        // Trip Input 8 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT9  0x100       // Trip Input 9 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT10  0x200       // Trip Input 10 Select to DCBH
                                              // Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT11  0x400       // Trip Input 11 Select to DCBH
                                              // Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT12  0x800       // Trip Input 12 Select to DCBH
                                              // Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT13  0x1000      // Trip Input 13 Select to DCBH
                                              // Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT14  0x2000      // Trip Input 14 Select to DCBH
                                              // Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT15  0x4000      // Trip Input 15 Select to DCBH
                                              // Mux

//*****************************************************************************
//
// The following are defines for the bit fields in the DCBLTRIPSEL register
//
//*****************************************************************************
#define EPWM_DCBLTRIPSEL_TRIPINPUT1  0x1         // Trip Input 1 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT2  0x2         // Trip Input 2 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT3  0x4         // Trip Input 3 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT4  0x8         // Trip Input 4 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT5  0x10        // Trip Input 5 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT6  0x20        // Trip Input 6 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT7  0x40        // Trip Input 7 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT8  0x80        // Trip Input 8 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT9  0x100       // Trip Input 9 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT10  0x200       // Trip Input 10 Select to DCBL
                                              // Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT11  0x400       // Trip Input 11 Select to DCBL
                                              // Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT12  0x800       // Trip Input 12 Select to DCBL
                                              // Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT13  0x1000      // Trip Input 13 Select to DCBL
                                              // Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT14  0x2000      // Trip Input 14 Select to DCBL
                                              // Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT15  0x4000      // Trip Input 15 Select to DCBL
                                              // Mux
#endif
