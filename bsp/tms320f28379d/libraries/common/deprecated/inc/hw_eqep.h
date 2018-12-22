//###########################################################################
//
// FILE:    hw_eqep.h
//
// TITLE:   Definitions for the C28x EQEP registers.
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

#ifndef __HW_EQEP_H__
#define __HW_EQEP_H__

//*****************************************************************************
//
// The following are defines for the EQEP register offsets
//
//*****************************************************************************
#define EQEP_O_QPOSCNT            0x0         // Position Counter
#define EQEP_O_QPOSINIT           0x2         // Position Counter Init
#define EQEP_O_QPOSMAX            0x4         // Maximum Position Count
#define EQEP_O_QPOSCMP            0x6         // Position Compare
#define EQEP_O_QPOSILAT           0x8         // Index Position Latch
#define EQEP_O_QPOSSLAT           0xA         // Strobe Position Latch
#define EQEP_O_QPOSLAT            0xC         // Position Latch
#define EQEP_O_QUTMR              0xE         // QEP Unit Timer
#define EQEP_O_QUPRD              0x10        // QEP Unit Period
#define EQEP_O_QWDTMR             0x12        // QEP Watchdog Timer
#define EQEP_O_QWDPRD             0x13        // QEP Watchdog Period
#define EQEP_O_QDECCTL            0x14        // Quadrature Decoder Control
#define EQEP_O_QEPCTL             0x15        // QEP Control
#define EQEP_O_QCAPCTL            0x16        // Qaudrature Capture Control
#define EQEP_O_QPOSCTL            0x17        // Position Compare Control
#define EQEP_O_QEINT              0x18        // QEP Interrupt Control
#define EQEP_O_QFLG               0x19        // QEP Interrupt Flag
#define EQEP_O_QCLR               0x1A        // QEP Interrupt Clear
#define EQEP_O_QFRC               0x1B        // QEP Interrupt Force
#define EQEP_O_QEPSTS             0x1C        // QEP Status
#define EQEP_O_QCTMR              0x1D        // QEP Capture Timer
#define EQEP_O_QCPRD              0x1E        // QEP Capture Period
#define EQEP_O_QCTMRLAT           0x1F        // QEP Capture Latch
#define EQEP_O_QCPRDLAT           0x20        // QEP Capture Period Latch

//*****************************************************************************
//
// The following are defines for the bit fields in the QPOSCNT register
//
//*****************************************************************************
#define EQEP_QPOSCNT_QPOSCNT_S    0
#define EQEP_QPOSCNT_QPOSCNT_M    0xFFFFFFFF  // Position Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the QPOSINIT register
//
//*****************************************************************************
#define EQEP_QPOSINIT_QPOSINIT_S  0
#define EQEP_QPOSINIT_QPOSINIT_M  0xFFFFFFFF  // Position Counter Init

//*****************************************************************************
//
// The following are defines for the bit fields in the QPOSMAX register
//
//*****************************************************************************
#define EQEP_QPOSMAX_QPOSMAX_S    0
#define EQEP_QPOSMAX_QPOSMAX_M    0xFFFFFFFF  // Maximum Position Count

//*****************************************************************************
//
// The following are defines for the bit fields in the QPOSCMP register
//
//*****************************************************************************
#define EQEP_QPOSCMP_QPOSCMP_S    0
#define EQEP_QPOSCMP_QPOSCMP_M    0xFFFFFFFF  // Position Compare

//*****************************************************************************
//
// The following are defines for the bit fields in the QPOSILAT register
//
//*****************************************************************************
#define EQEP_QPOSILAT_QPOSILAT_S  0
#define EQEP_QPOSILAT_QPOSILAT_M  0xFFFFFFFF  // Index Position Latch

//*****************************************************************************
//
// The following are defines for the bit fields in the QPOSSLAT register
//
//*****************************************************************************
#define EQEP_QPOSSLAT_QPOSSLAT_S  0
#define EQEP_QPOSSLAT_QPOSSLAT_M  0xFFFFFFFF  // Strobe Position Latch

//*****************************************************************************
//
// The following are defines for the bit fields in the QPOSLAT register
//
//*****************************************************************************
#define EQEP_QPOSLAT_QPOSLAT_S    0
#define EQEP_QPOSLAT_QPOSLAT_M    0xFFFFFFFF  // Position Latch

//*****************************************************************************
//
// The following are defines for the bit fields in the QUTMR register
//
//*****************************************************************************
#define EQEP_QUTMR_QUTMR_S        0
#define EQEP_QUTMR_QUTMR_M        0xFFFFFFFF  // QEP Unit Timer

//*****************************************************************************
//
// The following are defines for the bit fields in the QUPRD register
//
//*****************************************************************************
#define EQEP_QUPRD_QUPRD_S        0
#define EQEP_QUPRD_QUPRD_M        0xFFFFFFFF  // QEP Unit Period

//*****************************************************************************
//
// The following are defines for the bit fields in the QWDTMR register
//
//*****************************************************************************
#define EQEP_QWDTMR_QWDTMR_S      0
#define EQEP_QWDTMR_QWDTMR_M      0xFFFF      // QEP Watchdog Timer

//*****************************************************************************
//
// The following are defines for the bit fields in the QWDPRD register
//
//*****************************************************************************
#define EQEP_QWDPRD_QWDPRD_S      0
#define EQEP_QWDPRD_QWDPRD_M      0xFFFF      // QEP Watchdog Period

//*****************************************************************************
//
// The following are defines for the bit fields in the QDECCTL register
//
//*****************************************************************************
#define EQEP_QDECCTL_QSP          0x20        // QEPS input polarity
#define EQEP_QDECCTL_QIP          0x40        // QEPI input polarity
#define EQEP_QDECCTL_QBP          0x80        // QEPB input polarity
#define EQEP_QDECCTL_QAP          0x100       // QEPA input polarity
#define EQEP_QDECCTL_IGATE        0x200       // Index pulse gating option
#define EQEP_QDECCTL_SWAP         0x400       // CLK/DIR Signal Source for
                                              // Position Counter
#define EQEP_QDECCTL_XCR          0x800       // External Clock Rate
#define EQEP_QDECCTL_SPSEL        0x1000      // Sync output pin selection
#define EQEP_QDECCTL_SOEN         0x2000      // Sync output-enable
#define EQEP_QDECCTL_QSRC_S       14
#define EQEP_QDECCTL_QSRC_M       0xC000      // Position-counter source
                                              // selection

//*****************************************************************************
//
// The following are defines for the bit fields in the QEPCTL register
//
//*****************************************************************************
#define EQEP_QEPCTL_WDE           0x1         // QEP watchdog enable
#define EQEP_QEPCTL_UTE           0x2         // QEP unit timer enable
#define EQEP_QEPCTL_QCLM          0x4         // QEP capture latch mode
#define EQEP_QEPCTL_QPEN          0x8         // Quadrature postotion counter
                                              // enable
#define EQEP_QEPCTL_IEL_S         4
#define EQEP_QEPCTL_IEL_M         0x30        // Index event latch
#define EQEP_QEPCTL_SEL           0x40        // Strobe event latch
#define EQEP_QEPCTL_SWI           0x80        // Software init position counter
#define EQEP_QEPCTL_IEI_S         8
#define EQEP_QEPCTL_IEI_M         0x300       // Index event init of position
                                              // count
#define EQEP_QEPCTL_SEI_S         10
#define EQEP_QEPCTL_SEI_M         0xC00       // Strobe event init
#define EQEP_QEPCTL_PCRM_S        12
#define EQEP_QEPCTL_PCRM_M        0x3000      // Postion counter reset
#define EQEP_QEPCTL_FREE_SOFT_S   14
#define EQEP_QEPCTL_FREE_SOFT_M   0xC000      // Emulation mode

//*****************************************************************************
//
// The following are defines for the bit fields in the QCAPCTL register
//
//*****************************************************************************
#define EQEP_QCAPCTL_UPPS_S       0
#define EQEP_QCAPCTL_UPPS_M       0xF         // Unit position event prescaler
#define EQEP_QCAPCTL_CCPS_S       4
#define EQEP_QCAPCTL_CCPS_M       0x70        // eQEP capture timer clock
                                              // prescaler
#define EQEP_QCAPCTL_CEN          0x8000      // Enable eQEP capture

//*****************************************************************************
//
// The following are defines for the bit fields in the QPOSCTL register
//
//*****************************************************************************
#define EQEP_QPOSCTL_PCSPW_S      0
#define EQEP_QPOSCTL_PCSPW_M      0xFFF       // Position compare sync pulse
                                              // width
#define EQEP_QPOSCTL_PCE          0x1000      // Position compare enable/disable
#define EQEP_QPOSCTL_PCPOL        0x2000      // Polarity of sync output
#define EQEP_QPOSCTL_PCLOAD       0x4000      // Position compare of shadow load
#define EQEP_QPOSCTL_PCSHDW       0x8000      // Position compare of shadow
                                              // enable

//*****************************************************************************
//
// The following are defines for the bit fields in the QEINT register
//
//*****************************************************************************
#define EQEP_QEINT_PCE            0x2         // Position counter error
                                              // interrupt enable
#define EQEP_QEINT_QPE            0x4         // Quadrature phase error
                                              // interrupt enable
#define EQEP_QEINT_QDC            0x8         // Quadrature direction change
                                              // interrupt enable
#define EQEP_QEINT_WTO            0x10        // Watchdog time out interrupt
                                              // enable
#define EQEP_QEINT_PCU            0x20        // Position counter underflow
                                              // interrupt enable
#define EQEP_QEINT_PCO            0x40        // Position counter overflow
                                              // interrupt enable
#define EQEP_QEINT_PCR            0x80        // Position-compare ready
                                              // interrupt enable
#define EQEP_QEINT_PCM            0x100       // Position-compare match
                                              // interrupt enable
#define EQEP_QEINT_SEL            0x200       // Strobe event latch interrupt
                                              // enable
#define EQEP_QEINT_IEL            0x400       // Index event latch interrupt
                                              // enable
#define EQEP_QEINT_UTO            0x800       // Unit time out interrupt enable

//*****************************************************************************
//
// The following are defines for the bit fields in the QFLG register
//
//*****************************************************************************
#define EQEP_QFLG_INT             0x1         // Global interrupt status flag
#define EQEP_QFLG_PCE             0x2         // Position counter error
                                              // interrupt flag
#define EQEP_QFLG_PHE             0x4         // Quadrature phase error
                                              // interrupt flag
#define EQEP_QFLG_QDC             0x8         // Quadrature direction change
                                              // interrupt flag
#define EQEP_QFLG_WTO             0x10        // Watchdog timeout interrupt flag
#define EQEP_QFLG_PCU             0x20        // Position counter underflow
                                              // interrupt flag
#define EQEP_QFLG_PCO             0x40        // Position counter overflow
                                              // interrupt flag
#define EQEP_QFLG_PCR             0x80        // Position-compare ready
                                              // interrupt flag
#define EQEP_QFLG_PCM             0x100       // eQEP compare match event
                                              // interrupt flag
#define EQEP_QFLG_SEL             0x200       // Strobe event latch interrupt
                                              // flag
#define EQEP_QFLG_IEL             0x400       // Index event latch interrupt
                                              // flag
#define EQEP_QFLG_UTO             0x800       // Unit time out interrupt flag

//*****************************************************************************
//
// The following are defines for the bit fields in the QCLR register
//
//*****************************************************************************
#define EQEP_QCLR_INT             0x1         // Global interrupt clear flag
#define EQEP_QCLR_PCE             0x2         // Clear position counter error
                                              // interrupt flag
#define EQEP_QCLR_PHE             0x4         // Clear quadrature phase error
                                              // interrupt flag
#define EQEP_QCLR_QDC             0x8         // Clear quadrature direction
                                              // change interrupt flag
#define EQEP_QCLR_WTO             0x10        // Clear watchdog timeout
                                              // interrupt flag
#define EQEP_QCLR_PCU             0x20        // Clear position counter
                                              // underflow interrupt flag
#define EQEP_QCLR_PCO             0x40        // Clear position counter overflow
                                              // interrupt flag
#define EQEP_QCLR_PCR             0x80        // Clear position-compare ready
                                              // interrupt flag
#define EQEP_QCLR_PCM             0x100       // Clear eQEP compare match event
                                              // interrupt flag
#define EQEP_QCLR_SEL             0x200       // Clear strobe event latch
                                              // interrupt flag
#define EQEP_QCLR_IEL             0x400       // Clear index event latch
                                              // interrupt flag
#define EQEP_QCLR_UTO             0x800       // Clear unit time out interrupt
                                              // flag

//*****************************************************************************
//
// The following are defines for the bit fields in the QFRC register
//
//*****************************************************************************
#define EQEP_QFRC_PCE             0x2         // Force position counter error
                                              // interrupt
#define EQEP_QFRC_PHE             0x4         // Force quadrature phase error
                                              // interrupt
#define EQEP_QFRC_QDC             0x8         // Force quadrature direction
                                              // change interrupt
#define EQEP_QFRC_WTO             0x10        // Force watchdog time out
                                              // interrupt
#define EQEP_QFRC_PCU             0x20        // Force position counter
                                              // underflow interrupt
#define EQEP_QFRC_PCO             0x40        // Force position counter overflow
                                              // interrupt
#define EQEP_QFRC_PCR             0x80        // Force position-compare ready
                                              // interrupt
#define EQEP_QFRC_PCM             0x100       // Force position-compare match
                                              // interrupt
#define EQEP_QFRC_SEL             0x200       // Force strobe event latch
                                              // interrupt
#define EQEP_QFRC_IEL             0x400       // Force index event latch
                                              // interrupt
#define EQEP_QFRC_UTO             0x800       // Force unit time out interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the QEPSTS register
//
//*****************************************************************************
#define EQEP_QEPSTS_PCEF          0x1         // Position counter error flag.
#define EQEP_QEPSTS_FIMF          0x2         // First index marker flag
#define EQEP_QEPSTS_CDEF          0x4         // Capture direction error flag
#define EQEP_QEPSTS_COEF          0x8         // Capture overflow error flag
#define EQEP_QEPSTS_QDLF          0x10        // eQEP direction latch flag
#define EQEP_QEPSTS_QDF           0x20        // Quadrature direction flag
#define EQEP_QEPSTS_FIDF          0x40        // The first index marker
#define EQEP_QEPSTS_UPEVNT        0x80        // Unit position event flag

//*****************************************************************************
//
// The following are defines for the bit fields in the QCTMR register
//
//*****************************************************************************
#define EQEP_QCTMR_QCTMR_S        0
#define EQEP_QCTMR_QCTMR_M        0xFFFF      // This register provides time
                                              // base for edge capture unit.

//*****************************************************************************
//
// The following are defines for the bit fields in the QCPRD register
//
//*****************************************************************************
#define EQEP_QCPRD_QCPRD_S        0
#define EQEP_QCPRD_QCPRD_M        0xFFFF      // Period count value between 
                                              // eQEP position events

//*****************************************************************************
//
// The following are defines for the bit fields in the QCTMRLAT register
//
//*****************************************************************************
#define EQEP_QCTMRLAT_QCTMRLAT_S  0
#define EQEP_QCTMRLAT_QCTMRLAT_M  0xFFFF      // The eQEP capture timer latch
                                              // value

//*****************************************************************************
//
// The following are defines for the bit fields in the QCPRDLAT register
//
//*****************************************************************************
#define EQEP_QCPRDLAT_QCPRDLAT_S  0
#define EQEP_QCPRDLAT_QCPRDLAT_M  0xFFFF      // eQEP capture period latch value
#endif
