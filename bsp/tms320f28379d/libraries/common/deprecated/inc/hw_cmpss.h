//###########################################################################
//
// FILE:    hw_cmpss.h
//
// TITLE:   Definitions for the C28x CMPSS registers.
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

#ifndef __HW_CMPSS_H__
#define __HW_CMPSS_H__

//*****************************************************************************
//
// The following are defines for the CMPSS register offsets
//
//*****************************************************************************
#define CMPSS_O_COMPCTL           0x0         // CMPSS Comparator Control
                                              // Register
#define CMPSS_O_COMPHYSCTL        0x1         // CMPSS Comparator Hysteresis
                                              // Control Register
#define CMPSS_O_COMPSTS           0x2         // CMPSS Comparator Status
                                              // Register
#define CMPSS_O_COMPSTSCLR        0x3         // CMPSS Comparator Status Clear
                                              // Register
#define CMPSS_O_COMPDACCTL        0x4         // CMPSS DAC Control Register
#define CMPSS_O_DACHVALS          0x6         // CMPSS High DAC Value Shadow
                                              // Register
#define CMPSS_O_DACHVALA          0x7         // CMPSS High DAC Value Active
                                              // Register
#define CMPSS_O_RAMPMAXREFA       0x8         // CMPSS Ramp Max Reference Active
                                              // Register
#define CMPSS_O_RAMPMAXREFS       0xA         // CMPSS Ramp Max Reference Shadow
                                              // Register
#define CMPSS_O_RAMPDECVALA       0xC         // CMPSS Ramp Decrement Value
                                              // Active Register
#define CMPSS_O_RAMPDECVALS       0xE         // CMPSS Ramp Decrement Value
                                              // Shadow Register
#define CMPSS_O_RAMPSTS           0x10        // CMPSS Ramp Status Register
#define CMPSS_O_DACLVALS          0x12        // CMPSS Low DAC Value Shadow
                                              // Register
#define CMPSS_O_DACLVALA          0x13        // CMPSS Low DAC Value Active
                                              // Register
#define CMPSS_O_RAMPDLYA          0x14        // CMPSS Ramp Delay Active
                                              // Register
#define CMPSS_O_RAMPDLYS          0x15        // CMPSS Ramp Delay Shadow
                                              // Register
#define CMPSS_O_CTRIPLFILCTL      0x16        // CTRIPL Filter Control Register
#define CMPSS_O_CTRIPLFILCLKCTL   0x17        // CTRIPL Filter Clock Control
                                              // Register
#define CMPSS_O_CTRIPHFILCTL      0x18        // CTRIPH Filter Control Register
#define CMPSS_O_CTRIPHFILCLKCTL   0x19        // CTRIPH Filter Clock Control
                                              // Register
#define CMPSS_O_COMPLOCK          0x1A        // CMPSS Lock Register

//*****************************************************************************
//
// The following are defines for the bit fields in the COMPCTL register
//
//*****************************************************************************
#define CMPSS_COMPCTL_COMPHSOURCE  0x1         // High Comparator Source Select
#define CMPSS_COMPCTL_COMPHINV    0x2         // High Comparator Invert Select
#define CMPSS_COMPCTL_CTRIPHSEL_S  2
#define CMPSS_COMPCTL_CTRIPHSEL_M  0xC         // High Comparator Trip Select
#define CMPSS_COMPCTL_CTRIPOUTHSEL_S  4
#define CMPSS_COMPCTL_CTRIPOUTHSEL_M  0x30        // High Comparator Trip Output
                                              // Select
#define CMPSS_COMPCTL_ASYNCHEN    0x40        // High Comparator Asynchronous
                                              // Path Enable
#define CMPSS_COMPCTL_COMPLSOURCE  0x100       // Low Comparator Source Select
#define CMPSS_COMPCTL_COMPLINV    0x200       // Low Comparator Invert Select
#define CMPSS_COMPCTL_CTRIPLSEL_S  10
#define CMPSS_COMPCTL_CTRIPLSEL_M  0xC00       // Low Comparator Trip Select
#define CMPSS_COMPCTL_CTRIPOUTLSEL_S  12
#define CMPSS_COMPCTL_CTRIPOUTLSEL_M  0x3000      // Low Comparator Trip Output
                                              // Select
#define CMPSS_COMPCTL_ASYNCLEN    0x4000      // Low Comparator Asynchronous
                                              // Path Enable
#define CMPSS_COMPCTL_COMPDACE    0x8000      // Comparator/DAC Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the COMPHYSCTL register
//
//*****************************************************************************
#define CMPSS_COMPHYSCTL_COMPHYS_S  0
#define CMPSS_COMPHYSCTL_COMPHYS_M  0x7         // Comparator Hysteresis Trim

//*****************************************************************************
//
// The following are defines for the bit fields in the COMPSTS register
//
//*****************************************************************************
#define CMPSS_COMPSTS_COMPHSTS    0x1         // High Comparator Status
#define CMPSS_COMPSTS_COMPHLATCH  0x2         // High Comparator Latched Status
#define CMPSS_COMPSTS_COMPLSTS    0x100       // Low Comparator Status
#define CMPSS_COMPSTS_COMPLLATCH  0x200       // Low Comparator Latched Status

//*****************************************************************************
//
// The following are defines for the bit fields in the COMPSTSCLR register
//
//*****************************************************************************
#define CMPSS_COMPSTSCLR_HLATCHCLR  0x2         // High Comparator Latched Status
                                              // Clear
#define CMPSS_COMPSTSCLR_HSYNCCLREN  0x4         // High Comparator PWMSYNC Clear
                                              // Enable
#define CMPSS_COMPSTSCLR_LLATCHCLR  0x200       // Low Comparator Latched Status
                                              // Clear
#define CMPSS_COMPSTSCLR_LSYNCCLREN  0x400       // Low Comparator PWMSYNC Clear
                                              // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the COMPDACCTL register
//
//*****************************************************************************
#define CMPSS_COMPDACCTL_DACSOURCE  0x1         // DAC Source Control
#define CMPSS_COMPDACCTL_RAMPSOURCE_S  1
#define CMPSS_COMPDACCTL_RAMPSOURCE_M  0x1E        // Ramp Generator Source Control
#define CMPSS_COMPDACCTL_SELREF   0x20        // DAC Reference Select
#define CMPSS_COMPDACCTL_RAMPLOADSEL  0x40        // Ramp Load Select
#define CMPSS_COMPDACCTL_SWLOADSEL  0x80        // Software Load Select
#define CMPSS_COMPDACCTL_FREESOFT_S  14
#define CMPSS_COMPDACCTL_FREESOFT_M  0xC000      // Free/Soft Emulation Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the DACHVALS register
//
//*****************************************************************************
#define CMPSS_DACHVALS_DACVAL_S   0
#define CMPSS_DACHVALS_DACVAL_M   0xFFF       // DAC Value Control

//*****************************************************************************
//
// The following are defines for the bit fields in the DACHVALA register
//
//*****************************************************************************
#define CMPSS_DACHVALA_DACVAL_S   0
#define CMPSS_DACHVALA_DACVAL_M   0xFFF       // DAC Value Control

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMPMAXREFA register
//
//*****************************************************************************
#define CMPSS_RAMPMAXREFA_RAMPMAXREF_S  0
#define CMPSS_RAMPMAXREFA_RAMPMAXREF_M  0xFFFF      // Ramp Maximum Reference Active

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMPMAXREFS register
//
//*****************************************************************************
#define CMPSS_RAMPMAXREFS_RAMPMAXREF_S  0
#define CMPSS_RAMPMAXREFS_RAMPMAXREF_M  0xFFFF      // Ramp Maximum Reference Shadow

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMPDECVALA register
//
//*****************************************************************************
#define CMPSS_RAMPDECVALA_RAMPDECVAL_S  0
#define CMPSS_RAMPDECVALA_RAMPDECVAL_M  0xFFFF      // Ramp Decrement Value Active

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMPDECVALS register
//
//*****************************************************************************
#define CMPSS_RAMPDECVALS_RAMPDECVAL_S  0
#define CMPSS_RAMPDECVALS_RAMPDECVAL_M  0xFFFF      // Ramp Decrement Value Shadow

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMPSTS register
//
//*****************************************************************************
#define CMPSS_RAMPSTS_RAMPVALUE_S  0
#define CMPSS_RAMPSTS_RAMPVALUE_M  0xFFFF      // Ramp Value

//*****************************************************************************
//
// The following are defines for the bit fields in the DACLVALS register
//
//*****************************************************************************
#define CMPSS_DACLVALS_DACVAL_S   0
#define CMPSS_DACLVALS_DACVAL_M   0xFFF       // DAC Value Control

//*****************************************************************************
//
// The following are defines for the bit fields in the DACLVALA register
//
//*****************************************************************************
#define CMPSS_DACLVALA_DACVAL_S   0
#define CMPSS_DACLVALA_DACVAL_M   0xFFF       // DAC Value Control

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMPDLYA register
//
//*****************************************************************************
#define CMPSS_RAMPDLYA_DELAY_S    0
#define CMPSS_RAMPDLYA_DELAY_M    0x1FFF      // Ramp Delay Value

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMPDLYS register
//
//*****************************************************************************
#define CMPSS_RAMPDLYS_DELAY_S    0
#define CMPSS_RAMPDLYS_DELAY_M    0x1FFF      // Ramp Delay Value

//*****************************************************************************
//
// The following are defines for the bit fields in the CTRIPLFILCTL register
//
//*****************************************************************************
#define CMPSS_CTRIPLFILCTL_SAMPWIN_S  4
#define CMPSS_CTRIPLFILCTL_SAMPWIN_M  0x1F0       // Sample Window
#define CMPSS_CTRIPLFILCTL_THRESH_S  9
#define CMPSS_CTRIPLFILCTL_THRESH_M  0x3E00      // Majority Voting Threshold
#define CMPSS_CTRIPLFILCTL_FILINIT  0x8000      // Filter Initialization Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the CTRIPLFILCLKCTL register
//
//*****************************************************************************
#define CMPSS_CTRIPLFILCLKCTL_CLKPRESCALE_S  0
#define CMPSS_CTRIPLFILCLKCTL_CLKPRESCALE_M  0x3FF       // Sample Clock Prescale

//*****************************************************************************
//
// The following are defines for the bit fields in the CTRIPHFILCTL register
//
//*****************************************************************************
#define CMPSS_CTRIPHFILCTL_SAMPWIN_S  4
#define CMPSS_CTRIPHFILCTL_SAMPWIN_M  0x1F0       // Sample Window
#define CMPSS_CTRIPHFILCTL_THRESH_S  9
#define CMPSS_CTRIPHFILCTL_THRESH_M  0x3E00      // Majority Voting Threshold
#define CMPSS_CTRIPHFILCTL_FILINIT  0x8000      // Filter Initialization Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the CTRIPHFILCLKCTL register
//
//*****************************************************************************
#define CMPSS_CTRIPHFILCLKCTL_CLKPRESCALE_S  0
#define CMPSS_CTRIPHFILCLKCTL_CLKPRESCALE_M  0x3FF       // Sample Clock Prescale

//*****************************************************************************
//
// The following are defines for the bit fields in the COMPLOCK register
//
//*****************************************************************************
#define CMPSS_COMPLOCK_COMPCTL    0x1         // COMPCTL Lock
#define CMPSS_COMPLOCK_COMPHYSCTL  0x2         // COMPHYSCTL Lock
#define CMPSS_COMPLOCK_DACCTL     0x4         // DACCTL Lock
#define CMPSS_COMPLOCK_CTRIP      0x8         // CTRIP Lock
#endif
