//###########################################################################
//
// FILE:    hw_emif.h
//
// TITLE:   Definitions for the C28x EMIF registers.
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

#ifndef __HW_EMIF_H__
#define __HW_EMIF_H__

//*****************************************************************************
//
// The following are defines for the EMIF register offsets
//
//*****************************************************************************
#define EMIF_O_RCSR               0x0         // Revision Code and Status
                                              // Register
#define EMIF_O_ASYNC_WCCR         0x2         // Async Wait Cycle Config
                                              // Register
#define EMIF_O_SDRAM_CR           0x4         // SDRAM
                                              // (pad_cs_o_n[0]/pad_cs_o_n[1])
                                              // Config Register
#define EMIF_O_SDRAM_RCR          0x6         // SDRAM Refresh Control Register
#define EMIF_O_ASYNC_CS2_CR       0x8         // Async 1 (pad_cs_o_n[2]) Config
                                              // Register
#define EMIF_O_ASYNC_CS3_CR       0xA         // Async 2 (pad_cs_o_n[3]) Config
                                              // Register
#define EMIF_O_ASYNC_CS4_CR       0xC         // Async 3 (pad_cs_o_n[4]) Config
                                              // Register
#define EMIF_O_ASYNC_CS5_CR       0xE         // Async 4 (pad_cs_o_n[5]) Config
                                              // Register
#define EMIF_O_SDRAM_TR           0x10        // SDRAM Timing Register
#define EMIF_O_TOTAL_SDRAM_AR     0x18        // Total SDRAM Accesses Register
#define EMIF_O_TOTAL_SDRAM_ACTR   0x1A        // Total SDRAM Activate Register
#define EMIF_O_SDR_EXT_TMNG       0x1E        // SDRAM SR/PD Exit Timing
                                              // Register
#define EMIF_O_INT_RAW            0x20        // Interrupt Raw Register
#define EMIF_O_INT_MSK            0x22        // Interrupt Masked Register
#define EMIF_O_INT_MSK_SET        0x24        // Interrupt Mask Set Register
#define EMIF_O_INT_MSK_CLR        0x26        // Interrupt Mask Clear Register
#define EMIF_O_IO_CTRL            0x28        // IO Control Register
#define EMIF_O_IO_STAT            0x2A        // IO Status Register
#define EMIF_O_MODEL_REL_NUM      0x56        // Module Release Number Register

//*****************************************************************************
//
// The following are defines for the bit fields in the RCSR register
//
//*****************************************************************************
#define EMIF_RCSR_MINOR_REVISION_S  0
#define EMIF_RCSR_MINOR_REVISION_M  0xFF        // Minor Revision.
#define EMIF_RCSR_MAJOR_REVISION_S  8
#define EMIF_RCSR_MAJOR_REVISION_M  0xFF00      // Major Revision.
#define EMIF_RCSR_MODULE_ID_S     16
#define EMIF_RCSR_MODULE_ID_M     0x3FFF0000  // EMIF module ID.
#define EMIF_RCSR_FR              0x40000000  // EMIF is running in full rate or
                                              // half rate.
#define EMIF_RCSR_BE              0x80000000  // EMIF endian mode.

//*****************************************************************************
//
// The following are defines for the bit fields in the ASYNC_WCCR register
//
//*****************************************************************************
#define EMIF_ASYNC_WCCR_MAX_EXT_WAIT_S  0
#define EMIF_ASYNC_WCCR_MAX_EXT_WAIT_M  0xFF        // Maximum Extended Wait cycles.
#define EMIF_ASYNC_WCCR_CS2_WAIT_S  16
#define EMIF_ASYNC_WCCR_CS2_WAIT_M  0x30000     // Maps the wait signal for chip
                                              // select 2.
#define EMIF_ASYNC_WCCR_CS3_WAIT_S  18
#define EMIF_ASYNC_WCCR_CS3_WAIT_M  0xC0000     // Maps the wait signal for chip
                                              // select 3.
#define EMIF_ASYNC_WCCR_CS4_WAIT_S  20
#define EMIF_ASYNC_WCCR_CS4_WAIT_M  0x300000    // Maps the wait signal for chip
                                              // select 4.
#define EMIF_ASYNC_WCCR_CS5_WAIT_S  22
#define EMIF_ASYNC_WCCR_CS5_WAIT_M  0xC00000    // Maps the wait signal for chip
                                              // select 5.
#define EMIF_ASYNC_WCCR_WP0       0x10000000  // Wait Polarity for
                                              // pad_wait_i[0].
#define EMIF_ASYNC_WCCR_WP1       0x20000000  // Wait Polarity for
                                              // pad_wait_i[1].
#define EMIF_ASYNC_WCCR_WP2       0x40000000  // Wait Polarity for
                                              // pad_wait_i[2].
#define EMIF_ASYNC_WCCR_WP3       0x80000000  // Wait Polarity for
                                              // pad_wait_i[3].

//*****************************************************************************
//
// The following are defines for the bit fields in the SDRAM_CR register
//
//*****************************************************************************
#define EMIF_SDRAM_CR_PAGESIGE_S  0
#define EMIF_SDRAM_CR_PAGESIGE_M  0x7         // Page Size.
#define EMIF_SDRAM_CR_EBANK       0x8         // External chip select setup.
#define EMIF_SDRAM_CR_IBANK_S     4
#define EMIF_SDRAM_CR_IBANK_M     0x70        // Internal Bank setup of SDRAM
                                              // devices.
#define EMIF_SDRAM_CR_BIT_11_9_LOCK  0x100       // Bits 11 to 9 are writable only
                                              // if this bit is set.
#define EMIF_SDRAM_CR_CL_S        9
#define EMIF_SDRAM_CR_CL_M        0xE00       // CAS Latency.
#define EMIF_SDRAM_CR_BIT_13_LOCK  0x1000      // Bits 13 is writable only if
                                              // this bit is set.
#define EMIF_SDRAM_CR_NM          0x4000      // Narrow Mode.
#define EMIF_SDRAM_CR_BIT_25_17_LOCK  0x10000     // Bits 25 to 17 are writable only
                                              // if this bit is set
#define EMIF_SDRAM_CR_IBANK_POS   0x80000     // Internal bank position.
#define EMIF_SDRAM_CR_ROWSIZE_S   20
#define EMIF_SDRAM_CR_ROWSIZE_M   0x700000    // Row Size.
#define EMIF_SDRAM_CR_PASR_S      23
#define EMIF_SDRAM_CR_PASR_M      0x3800000   // Partial Array Self Refresh.
#define EMIF_SDRAM_CR_PDWR        0x20000000  // Perform refreshes during Power
                                              // Down.
#define EMIF_SDRAM_CR_PD          0x40000000  // Power Down.
#define EMIF_SDRAM_CR_SR          0x80000000  // Self Refresh.

//*****************************************************************************
//
// The following are defines for the bit fields in the SDRAM_RCR register
//
//*****************************************************************************
#define EMIF_SDRAM_RCR_REFRESH_RATE_S  0
#define EMIF_SDRAM_RCR_REFRESH_RATE_M  0x1FFF      // Refresh Rate.

//*****************************************************************************
//
// The following are defines for the bit fields in the ASYNC_CS2_CR register
//
//*****************************************************************************
#define EMIF_ASYNC_CS2_CR_ASIZE_S  0
#define EMIF_ASYNC_CS2_CR_ASIZE_M  0x3         // Asynchronous Memory Size.
#define EMIF_ASYNC_CS2_CR_TA_S    2
#define EMIF_ASYNC_CS2_CR_TA_M    0xC         // Turn Around cycles.
#define EMIF_ASYNC_CS2_CR_R_HOLD_S  4
#define EMIF_ASYNC_CS2_CR_R_HOLD_M  0x70        // Read Strobe Hold cycles.
#define EMIF_ASYNC_CS2_CR_R_STROBE_S  7
#define EMIF_ASYNC_CS2_CR_R_STROBE_M  0x1F80      // Read Strobe Duration cycles.
#define EMIF_ASYNC_CS2_CR_R_SETUP_S  13
#define EMIF_ASYNC_CS2_CR_R_SETUP_M  0x1E000     // Read Strobe Setup cycles.
#define EMIF_ASYNC_CS2_CR_W_HOLD_S  17
#define EMIF_ASYNC_CS2_CR_W_HOLD_M  0xE0000     // Write Strobe Hold cycles.
#define EMIF_ASYNC_CS2_CR_W_STROBE_S  20
#define EMIF_ASYNC_CS2_CR_W_STROBE_M  0x3F00000   // Write Strobe Duration cycles.
#define EMIF_ASYNC_CS2_CR_W_SETUP_S  26
#define EMIF_ASYNC_CS2_CR_W_SETUP_M  0x3C000000  // Write Strobe Setup cycles.
#define EMIF_ASYNC_CS2_CR_EW      0x40000000  // Extend Wait mode.
#define EMIF_ASYNC_CS2_CR_SS      0x80000000  // Select Strobe mode.

//*****************************************************************************
//
// The following are defines for the bit fields in the ASYNC_CS3_CR register
//
//*****************************************************************************
#define EMIF_ASYNC_CS3_CR_ASIZE_S  0
#define EMIF_ASYNC_CS3_CR_ASIZE_M  0x3         // Asynchronous Memory Size.
#define EMIF_ASYNC_CS3_CR_TA_S    2
#define EMIF_ASYNC_CS3_CR_TA_M    0xC         // Turn Around cycles.
#define EMIF_ASYNC_CS3_CR_R_HOLD_S  4
#define EMIF_ASYNC_CS3_CR_R_HOLD_M  0x70        // Read Strobe Hold cycles.
#define EMIF_ASYNC_CS3_CR_R_STROBE_S  7
#define EMIF_ASYNC_CS3_CR_R_STROBE_M  0x1F80      // Read Strobe Duration cycles.
#define EMIF_ASYNC_CS3_CR_R_SETUP_S  13
#define EMIF_ASYNC_CS3_CR_R_SETUP_M  0x1E000     // Read Strobe Setup cycles.
#define EMIF_ASYNC_CS3_CR_W_HOLD_S  17
#define EMIF_ASYNC_CS3_CR_W_HOLD_M  0xE0000     // Write Strobe Hold cycles.
#define EMIF_ASYNC_CS3_CR_W_STROBE_S  20
#define EMIF_ASYNC_CS3_CR_W_STROBE_M  0x3F00000   // Write Strobe Duration cycles.
#define EMIF_ASYNC_CS3_CR_W_SETUP_S  26
#define EMIF_ASYNC_CS3_CR_W_SETUP_M  0x3C000000  // Write Strobe Setup cycles.
#define EMIF_ASYNC_CS3_CR_EW      0x40000000  // Extend Wait mode.
#define EMIF_ASYNC_CS3_CR_SS      0x80000000  // Select Strobe mode.

//*****************************************************************************
//
// The following are defines for the bit fields in the ASYNC_CS4_CR register
//
//*****************************************************************************
#define EMIF_ASYNC_CS4_CR_ASIZE_S  0
#define EMIF_ASYNC_CS4_CR_ASIZE_M  0x3         // Asynchronous Memory Size.
#define EMIF_ASYNC_CS4_CR_TA_S    2
#define EMIF_ASYNC_CS4_CR_TA_M    0xC         // Turn Around cycles.
#define EMIF_ASYNC_CS4_CR_R_HOLD_S  4
#define EMIF_ASYNC_CS4_CR_R_HOLD_M  0x70        // Read Strobe Hold cycles.
#define EMIF_ASYNC_CS4_CR_R_STROBE_S  7
#define EMIF_ASYNC_CS4_CR_R_STROBE_M  0x1F80      // Read Strobe Duration cycles.
#define EMIF_ASYNC_CS4_CR_R_SETUP_S  13
#define EMIF_ASYNC_CS4_CR_R_SETUP_M  0x1E000     // Read Strobe Setup cycles.
#define EMIF_ASYNC_CS4_CR_W_HOLD_S  17
#define EMIF_ASYNC_CS4_CR_W_HOLD_M  0xE0000     // Write Strobe Hold cycles.
#define EMIF_ASYNC_CS4_CR_W_STROBE_S  20
#define EMIF_ASYNC_CS4_CR_W_STROBE_M  0x3F00000   // Write Strobe Duration cycles.
#define EMIF_ASYNC_CS4_CR_W_SETUP_S  26
#define EMIF_ASYNC_CS4_CR_W_SETUP_M  0x3C000000  // Write Strobe Setup cycles.
#define EMIF_ASYNC_CS4_CR_EW      0x40000000  // Extend Wait mode.
#define EMIF_ASYNC_CS4_CR_SS      0x80000000  // Select Strobe mode.

//*****************************************************************************
//
// The following are defines for the bit fields in the ASYNC_CS5_CR register
//
//*****************************************************************************
#define EMIF_ASYNC_CS5_CR_ASIZE_S  0
#define EMIF_ASYNC_CS5_CR_ASIZE_M  0x3         // Asynchronous Memory Size.
#define EMIF_ASYNC_CS5_CR_TA_S    2
#define EMIF_ASYNC_CS5_CR_TA_M    0xC         // Turn Around cycles.
#define EMIF_ASYNC_CS5_CR_R_HOLD_S  4
#define EMIF_ASYNC_CS5_CR_R_HOLD_M  0x70        // Read Strobe Hold cycles.
#define EMIF_ASYNC_CS5_CR_R_STROBE_S  7
#define EMIF_ASYNC_CS5_CR_R_STROBE_M  0x1F80      // Read Strobe Duration cycles.
#define EMIF_ASYNC_CS5_CR_R_SETUP_S  13
#define EMIF_ASYNC_CS5_CR_R_SETUP_M  0x1E000     // Read Strobe Setup cycles.
#define EMIF_ASYNC_CS5_CR_W_HOLD_S  17
#define EMIF_ASYNC_CS5_CR_W_HOLD_M  0xE0000     // Write Strobe Hold cycles.
#define EMIF_ASYNC_CS5_CR_W_STROBE_S  20
#define EMIF_ASYNC_CS5_CR_W_STROBE_M  0x3F00000   // Write Strobe Duration cycles.
#define EMIF_ASYNC_CS5_CR_W_SETUP_S  26
#define EMIF_ASYNC_CS5_CR_W_SETUP_M  0x3C000000  // Write Strobe Setup cycles.
#define EMIF_ASYNC_CS5_CR_EW      0x40000000  // Extend Wait mode.
#define EMIF_ASYNC_CS5_CR_SS      0x80000000  // Select Strobe mode.

//*****************************************************************************
//
// The following are defines for the bit fields in the SDRAM_TR register
//
//*****************************************************************************
#define EMIF_SDRAM_TR_T_RRD_S     4
#define EMIF_SDRAM_TR_T_RRD_M     0x70        // Activate to Activate timing for
                                              // different bank.
#define EMIF_SDRAM_TR_T_RC_S      8
#define EMIF_SDRAM_TR_T_RC_M      0xF00       // Activate to Activate timing .
#define EMIF_SDRAM_TR_T_RAS_S     12
#define EMIF_SDRAM_TR_T_RAS_M     0xF000      // Activate to Precharge timing.
#define EMIF_SDRAM_TR_T_WR_S      16
#define EMIF_SDRAM_TR_T_WR_M      0x70000     // Last Write to Precharge timing.
#define EMIF_SDRAM_TR_T_RCD_S     20
#define EMIF_SDRAM_TR_T_RCD_M     0x700000    // Activate to Read/Write timing.
#define EMIF_SDRAM_TR_T_RP_S      24
#define EMIF_SDRAM_TR_T_RP_M      0x7000000   // Precharge to Activate/Refresh
                                              // timing.
#define EMIF_SDRAM_TR_T_RFC_S     27
#define EMIF_SDRAM_TR_T_RFC_M     0xF8000000  // Refresh/Load Mode to
                                              // Refresh/Activate timing

//*****************************************************************************
//
// The following are defines for the bit fields in the TOTAL_SDRAM_AR register
//
//*****************************************************************************
#define EMIF_TOTAL_SDRAM_AR_TOTAL_SDRAM_AR_S  0
#define EMIF_TOTAL_SDRAM_AR_TOTAL_SDRAM_AR_M  0xFFFFFFFF  // Total number of VBUSP accesses
                                              // to SDRAM.

//*****************************************************************************
//
// The following are defines for the bit fields in the TOTAL_SDRAM_ACTR register
//
//*****************************************************************************
#define EMIF_TOTAL_SDRAM_ACTR_TOTAL_SDRAM_ACTR_S  0
#define EMIF_TOTAL_SDRAM_ACTR_TOTAL_SDRAM_ACTR_M  0xFFFFFFFF  // Number of SDRAM accesses which
                                              // required an activate command.

//*****************************************************************************
//
// The following are defines for the bit fields in the SDR_EXT_TMNG register
//
//*****************************************************************************
#define EMIF_SDR_EXT_TMNG_T_XS_S  0
#define EMIF_SDR_EXT_TMNG_T_XS_M  0x1F        // Self Refresh exit to new
                                              // command timing.

//*****************************************************************************
//
// The following are defines for the bit fields in the INT_RAW register
//
//*****************************************************************************
#define EMIF_INT_RAW_AT           0x1         // Asynchronous Timeout.
#define EMIF_INT_RAW_LT           0x2         // Line Trap.
#define EMIF_INT_RAW_WR_S         2
#define EMIF_INT_RAW_WR_M         0x3C        // Wait Rise.

//*****************************************************************************
//
// The following are defines for the bit fields in the INT_MSK register
//
//*****************************************************************************
#define EMIF_INT_MSK_AT_MASKED    0x1         // Asynchronous Timeout.
#define EMIF_INT_MSK_LT_MASKED    0x2         // Line Trap.
#define EMIF_INT_MSK_WR_MASKED_S  2
#define EMIF_INT_MSK_WR_MASKED_M  0x3C        // Wait Rise.

//*****************************************************************************
//
// The following are defines for the bit fields in the INT_MSK_SET register
//
//*****************************************************************************
#define EMIF_INT_MSK_SET_AT_MASK_SET  0x1         // Asynchronous Timeout.
#define EMIF_INT_MSK_SET_LT_MASK_SET  0x2         // Line Trap.
#define EMIF_INT_MSK_SET_WR_MASK_SET_S  2
#define EMIF_INT_MSK_SET_WR_MASK_SET_M  0x3C        // Wait Rise.

//*****************************************************************************
//
// The following are defines for the bit fields in the INT_MSK_CLR register
//
//*****************************************************************************
#define EMIF_INT_MSK_CLR_AT_MASK_CLR  0x1         // Asynchronous Timeout.
#define EMIF_INT_MSK_CLR_LT_MASK_CLR  0x2         // Line Trap.
#define EMIF_INT_MSK_CLR_WR_MASK_CLR_S  2
#define EMIF_INT_MSK_CLR_WR_MASK_CLR_M  0x3C        // Wait Rise.

//*****************************************************************************
//
// The following are defines for the bit fields in the IO_CTRL register
//
//*****************************************************************************
#define EMIF_IO_CTRL_IO_CTRL_S    0
#define EMIF_IO_CTRL_IO_CTRL_M    0xFFFF      // VTP calibration control for the
                                              // IOs

//*****************************************************************************
//
// The following are defines for the bit fields in the IO_STAT register
//
//*****************************************************************************
#define EMIF_IO_STAT_IO_STAT_S    0
#define EMIF_IO_STAT_IO_STAT_M    0xFFFF      // VTP calibration status of the
                                              // IOs

//*****************************************************************************
//
// The following are defines for the bit fields in the MODEL_REL_NUM register
//
//*****************************************************************************
#define EMIF_MODEL_REL_NUM_RELEASE_NUM_S  0
#define EMIF_MODEL_REL_NUM_RELEASE_NUM_M  0xFF        // Release Number.
#endif
