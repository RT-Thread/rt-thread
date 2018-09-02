//###########################################################################
//
// FILE:    hw_ecap.h
//
// TITLE:   Definitions for the C28x ECAP registers.
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

#ifndef __HW_ECAP_H__
#define __HW_ECAP_H__

//*****************************************************************************
//
// The following are defines for the ECAP register offsets
//
//*****************************************************************************
#define ECAP_O_TSCTR              0x0         // Time-Stamp Counter
#define ECAP_O_CTRPHS             0x2         // Counter Phase Offset Value
                                              // Register
#define ECAP_O_CAP1               0x4         // Capture 1 Register
#define ECAP_O_CAP2               0x6         // Capture 2 Register
#define ECAP_O_CAP3               0x8         // Capture 3Register
#define ECAP_O_CAP4               0xA         // Capture 4 Register
#define ECAP_O_ECCTL1             0x14        // Capture Control Register 1
#define ECAP_O_ECCTL2             0x15        // Capture Control Register 2
#define ECAP_O_ECEINT             0x16        // Capture Interrupt Enable
                                              // Register
#define ECAP_O_ECFLG              0x17        // Capture Interrupt Flag Register
#define ECAP_O_ECCLR              0x18        // Capture Interrupt Flag Register
#define ECAP_O_ECFRC              0x19        // Capture Interrupt Force
                                              // Register

//*****************************************************************************
//
// The following are defines for the bit fields in the TSCTR register
//
//*****************************************************************************
#define ECAP_TSCTR_TSCTR_S        0
#define ECAP_TSCTR_TSCTR_M        0xFFFFFFFF  // Time Stamp Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the CTRPHS register
//
//*****************************************************************************
#define ECAP_CTRPHS_CTRPHS_S      0
#define ECAP_CTRPHS_CTRPHS_M      0xFFFFFFFF  // Counter phase

//*****************************************************************************
//
// The following are defines for the bit fields in the CAP1 register
//
//*****************************************************************************
#define ECAP_CAP1_CAP1_S          0
#define ECAP_CAP1_CAP1_M          0xFFFFFFFF  // Capture 1

//*****************************************************************************
//
// The following are defines for the bit fields in the CAP2 register
//
//*****************************************************************************
#define ECAP_CAP2_CAP2_S          0
#define ECAP_CAP2_CAP2_M          0xFFFFFFFF  // Capture 2

//*****************************************************************************
//
// The following are defines for the bit fields in the CAP3 register
//
//*****************************************************************************
#define ECAP_CAP3_CAP3_S          0
#define ECAP_CAP3_CAP3_M          0xFFFFFFFF  // Capture 3

//*****************************************************************************
//
// The following are defines for the bit fields in the CAP4 register
//
//*****************************************************************************
#define ECAP_CAP4_CAP4_S          0
#define ECAP_CAP4_CAP4_M          0xFFFFFFFF  // Capture 4

//*****************************************************************************
//
// The following are defines for the bit fields in the ECCTL1 register
//
//*****************************************************************************
#define ECAP_ECCTL1_CAP1POL       0x1         // Capture Event 1 Polarity select
#define ECAP_ECCTL1_CTRRST1       0x2         // Counter Reset on Capture Event
                                              // 1
#define ECAP_ECCTL1_CAP2POL       0x4         // Capture Event 2 Polarity select
#define ECAP_ECCTL1_CTRRST2       0x8         // Counter Reset on Capture Event
                                              // 2
#define ECAP_ECCTL1_CAP3POL       0x10        // Capture Event 3 Polarity select
#define ECAP_ECCTL1_CTRRST3       0x20        // Counter Reset on Capture Event
                                              // 3
#define ECAP_ECCTL1_CAP4POL       0x40        // Capture Event 4 Polarity select
#define ECAP_ECCTL1_CTRRST4       0x80        // Counter Reset on Capture Event
                                              // 4
#define ECAP_ECCTL1_CAPLDEN       0x100       // Enable Loading CAP1-4 regs on a
                                              // Cap Event
#define ECAP_ECCTL1_PRESCALE_S    9
#define ECAP_ECCTL1_PRESCALE_M    0x3E00      // Event Filter prescale select
#define ECAP_ECCTL1_FREE_SOFT_S   14
#define ECAP_ECCTL1_FREE_SOFT_M   0xC000      // Emulation mode

//*****************************************************************************
//
// The following are defines for the bit fields in the ECCTL2 register
//
//*****************************************************************************
#define ECAP_ECCTL2_CONT_ONESHT   0x1         // Continuous or one-shot
#define ECAP_ECCTL2_STOP_WRAP_S   1
#define ECAP_ECCTL2_STOP_WRAP_M   0x6         // Stop value for one-shot, Wrap
                                              // for continuous
#define ECAP_ECCTL2_RE_ARM        0x8         // One-shot re-arm
#define ECAP_ECCTL2_TSCTRSTOP     0x10        // TSCNT counter stop
#define ECAP_ECCTL2_SYNCI_EN      0x20        // Counter sync-in select
#define ECAP_ECCTL2_SYNCO_SEL_S   6
#define ECAP_ECCTL2_SYNCO_SEL_M   0xC0        // Sync-out mode
#define ECAP_ECCTL2_SWSYNC        0x100       // SW forced counter sync
#define ECAP_ECCTL2_CAP_APWM      0x200       // CAP/APWM operating mode select
#define ECAP_ECCTL2_APWMPOL       0x400       // APWM output polarity select

//*****************************************************************************
//
// The following are defines for the bit fields in the ECEINT register
//
//*****************************************************************************
#define ECAP_ECEINT_CEVT1         0x2         // Capture Event 1 Interrupt
                                              // Enable
#define ECAP_ECEINT_CEVT2         0x4         // Capture Event 2 Interrupt
                                              // Enable
#define ECAP_ECEINT_CEVT3         0x8         // Capture Event 3 Interrupt
                                              // Enable
#define ECAP_ECEINT_CEVT4         0x10        // Capture Event 4 Interrupt
                                              // Enable
#define ECAP_ECEINT_CTROVF        0x20        // Counter Overflow Interrupt
                                              // Enable
#define ECAP_ECEINT_CTR_PRD       0x40        // Period Equal Interrupt Enable
#define ECAP_ECEINT_CTR_CMP       0x80        // Compare Equal Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ECFLG register
//
//*****************************************************************************
#define ECAP_ECFLG_INT            0x1         // Global Flag
#define ECAP_ECFLG_CEVT1          0x2         // Capture Event 1 Interrupt Flag
#define ECAP_ECFLG_CEVT2          0x4         // Capture Event 2 Interrupt Flag
#define ECAP_ECFLG_CEVT3          0x8         // Capture Event 3 Interrupt Flag
#define ECAP_ECFLG_CEVT4          0x10        // Capture Event 4 Interrupt Flag
#define ECAP_ECFLG_CTROVF         0x20        // Counter Overflow Interrupt Flag
#define ECAP_ECFLG_CTR_PRD        0x40        // Period Equal Interrupt Flag
#define ECAP_ECFLG_CTR_CMP        0x80        // Compare Equal Interrupt Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ECCLR register
//
//*****************************************************************************
#define ECAP_ECCLR_INT            0x1         // Global Flag
#define ECAP_ECCLR_CEVT1          0x2         // Capture Event 1 Interrupt Flag
#define ECAP_ECCLR_CEVT2          0x4         // Capture Event 2 Interrupt Flag
#define ECAP_ECCLR_CEVT3          0x8         // Capture Event 3 Interrupt Flag
#define ECAP_ECCLR_CEVT4          0x10        // Capture Event 4 Interrupt Flag
#define ECAP_ECCLR_CTROVF         0x20        // Counter Overflow Interrupt Flag
#define ECAP_ECCLR_CTR_PRD        0x40        // Period Equal Interrupt Flag
#define ECAP_ECCLR_CTR_CMP        0x80        // Compare Equal Interrupt Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ECFRC register
//
//*****************************************************************************
#define ECAP_ECFRC_CEVT1          0x2         // Capture Event 1 Interrupt
                                              // Enable
#define ECAP_ECFRC_CEVT2          0x4         // Capture Event 2 Interrupt
                                              // Enable
#define ECAP_ECFRC_CEVT3          0x8         // Capture Event 3 Interrupt
                                              // Enable
#define ECAP_ECFRC_CEVT4          0x10        // Capture Event 4 Interrupt
                                              // Enable
#define ECAP_ECFRC_CTROVF         0x20        // Counter Overflow Interrupt
                                              // Enable
#define ECAP_ECFRC_CTR_PRD        0x40        // Period Equal Interrupt Enable
#define ECAP_ECFRC_CTR_CMP        0x80        // Compare Equal Interrupt Enable
#endif
