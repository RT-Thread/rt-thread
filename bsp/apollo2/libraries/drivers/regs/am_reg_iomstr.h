//*****************************************************************************
//
//  am_reg_iomstr.h
//! @file
//!
//! @brief Register macros for the IOMSTR module
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_REG_IOMSTR_H
#define AM_REG_IOMSTR_H

//*****************************************************************************
//
// Instance finder. (6 instance(s) available)
//
//*****************************************************************************
#define AM_REG_IOMSTR_NUM_MODULES                    6
#define AM_REG_IOMSTRn(n) \
    (REG_IOMSTR_BASEADDR + 0x00001000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_IOMSTR_FIFO_O                         0x00000000
#define AM_REG_IOMSTR_FIFOPTR_O                      0x00000100
#define AM_REG_IOMSTR_TLNGTH_O                       0x00000104
#define AM_REG_IOMSTR_FIFOTHR_O                      0x00000108
#define AM_REG_IOMSTR_CLKCFG_O                       0x0000010C
#define AM_REG_IOMSTR_CMD_O                          0x00000110
#define AM_REG_IOMSTR_CMDRPT_O                       0x00000114
#define AM_REG_IOMSTR_STATUS_O                       0x00000118
#define AM_REG_IOMSTR_CFG_O                          0x0000011C
#define AM_REG_IOMSTR_INTEN_O                        0x00000200
#define AM_REG_IOMSTR_INTSTAT_O                      0x00000204
#define AM_REG_IOMSTR_INTCLR_O                       0x00000208
#define AM_REG_IOMSTR_INTSET_O                       0x0000020C

//*****************************************************************************
//
// IOMSTR_INTEN - IO Master Interrupts: Enable
//
//*****************************************************************************
// This is the arbitration loss interrupt. This error occurs if another master
// collides with an IO Master transfer. Generally, the IOM started an operation
// but found SDA already low.
#define AM_REG_IOMSTR_INTEN_ARB_S                    10
#define AM_REG_IOMSTR_INTEN_ARB_M                    0x00000400
#define AM_REG_IOMSTR_INTEN_ARB(n)                   (((uint32_t)(n) << 10) & 0x00000400)

// This is the STOP command interrupt. A STOP bit was detected by the IOM.
#define AM_REG_IOMSTR_INTEN_STOP_S                   9
#define AM_REG_IOMSTR_INTEN_STOP_M                   0x00000200
#define AM_REG_IOMSTR_INTEN_STOP(n)                  (((uint32_t)(n) << 9) & 0x00000200)

// This is the START command interrupt. A START from another master was
// detected. Software must wait for a STOP before proceeding.
#define AM_REG_IOMSTR_INTEN_START_S                  8
#define AM_REG_IOMSTR_INTEN_START_M                  0x00000100
#define AM_REG_IOMSTR_INTEN_START(n)                 (((uint32_t)(n) << 8) & 0x00000100)

// This is the illegal command interrupt. Software attempted to issue a CMD
// while another CMD was already in progress. Or an attempt was made to issue a
// non-zero-length write CMD with an empty FIFO.
#define AM_REG_IOMSTR_INTEN_ICMD_S                   7
#define AM_REG_IOMSTR_INTEN_ICMD_M                   0x00000080
#define AM_REG_IOMSTR_INTEN_ICMD(n)                  (((uint32_t)(n) << 7) & 0x00000080)

// This is the illegal FIFO access interrupt. An attempt was made to read the
// FIFO during a write CMD. Or an attempt was made to write the FIFO on a read
// CMD.
#define AM_REG_IOMSTR_INTEN_IACC_S                   6
#define AM_REG_IOMSTR_INTEN_IACC_M                   0x00000040
#define AM_REG_IOMSTR_INTEN_IACC(n)                  (((uint32_t)(n) << 6) & 0x00000040)

// This is the WTLEN interrupt.
#define AM_REG_IOMSTR_INTEN_WTLEN_S                  5
#define AM_REG_IOMSTR_INTEN_WTLEN_M                  0x00000020
#define AM_REG_IOMSTR_INTEN_WTLEN(n)                 (((uint32_t)(n) << 5) & 0x00000020)

// This is the I2C NAK interrupt. The expected ACK from the slave was not
// received by the IOM.
#define AM_REG_IOMSTR_INTEN_NAK_S                    4
#define AM_REG_IOMSTR_INTEN_NAK_M                    0x00000010
#define AM_REG_IOMSTR_INTEN_NAK(n)                   (((uint32_t)(n) << 4) & 0x00000010)

// This is the Write FIFO Overflow interrupt. An attempt was made to write the
// FIFO while it was full (i.e. while FIFOSIZ > 124).
#define AM_REG_IOMSTR_INTEN_FOVFL_S                  3
#define AM_REG_IOMSTR_INTEN_FOVFL_M                  0x00000008
#define AM_REG_IOMSTR_INTEN_FOVFL(n)                 (((uint32_t)(n) << 3) & 0x00000008)

// This is the Read FIFO Underflow interrupt. An attempt was made to read FIFO
// when empty (i.e. while FIFOSIZ less than 4).
#define AM_REG_IOMSTR_INTEN_FUNDFL_S                 2
#define AM_REG_IOMSTR_INTEN_FUNDFL_M                 0x00000004
#define AM_REG_IOMSTR_INTEN_FUNDFL(n)                (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO Threshold interrupt.
#define AM_REG_IOMSTR_INTEN_THR_S                    1
#define AM_REG_IOMSTR_INTEN_THR_M                    0x00000002
#define AM_REG_IOMSTR_INTEN_THR(n)                   (((uint32_t)(n) << 1) & 0x00000002)

// This is the Command Complete interrupt.
#define AM_REG_IOMSTR_INTEN_CMDCMP_S                 0
#define AM_REG_IOMSTR_INTEN_CMDCMP_M                 0x00000001
#define AM_REG_IOMSTR_INTEN_CMDCMP(n)                (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOMSTR_INTSTAT - IO Master Interrupts: Status
//
//*****************************************************************************
// This is the arbitration loss interrupt. This error occurs if another master
// collides with an IO Master transfer. Generally, the IOM started an operation
// but found SDA already low.
#define AM_REG_IOMSTR_INTSTAT_ARB_S                  10
#define AM_REG_IOMSTR_INTSTAT_ARB_M                  0x00000400
#define AM_REG_IOMSTR_INTSTAT_ARB(n)                 (((uint32_t)(n) << 10) & 0x00000400)

// This is the STOP command interrupt. A STOP bit was detected by the IOM.
#define AM_REG_IOMSTR_INTSTAT_STOP_S                 9
#define AM_REG_IOMSTR_INTSTAT_STOP_M                 0x00000200
#define AM_REG_IOMSTR_INTSTAT_STOP(n)                (((uint32_t)(n) << 9) & 0x00000200)

// This is the START command interrupt. A START from another master was
// detected. Software must wait for a STOP before proceeding.
#define AM_REG_IOMSTR_INTSTAT_START_S                8
#define AM_REG_IOMSTR_INTSTAT_START_M                0x00000100
#define AM_REG_IOMSTR_INTSTAT_START(n)               (((uint32_t)(n) << 8) & 0x00000100)

// This is the illegal command interrupt. Software attempted to issue a CMD
// while another CMD was already in progress. Or an attempt was made to issue a
// non-zero-length write CMD with an empty FIFO.
#define AM_REG_IOMSTR_INTSTAT_ICMD_S                 7
#define AM_REG_IOMSTR_INTSTAT_ICMD_M                 0x00000080
#define AM_REG_IOMSTR_INTSTAT_ICMD(n)                (((uint32_t)(n) << 7) & 0x00000080)

// This is the illegal FIFO access interrupt. An attempt was made to read the
// FIFO during a write CMD. Or an attempt was made to write the FIFO on a read
// CMD.
#define AM_REG_IOMSTR_INTSTAT_IACC_S                 6
#define AM_REG_IOMSTR_INTSTAT_IACC_M                 0x00000040
#define AM_REG_IOMSTR_INTSTAT_IACC(n)                (((uint32_t)(n) << 6) & 0x00000040)

// This is the WTLEN interrupt.
#define AM_REG_IOMSTR_INTSTAT_WTLEN_S                5
#define AM_REG_IOMSTR_INTSTAT_WTLEN_M                0x00000020
#define AM_REG_IOMSTR_INTSTAT_WTLEN(n)               (((uint32_t)(n) << 5) & 0x00000020)

// This is the I2C NAK interrupt. The expected ACK from the slave was not
// received by the IOM.
#define AM_REG_IOMSTR_INTSTAT_NAK_S                  4
#define AM_REG_IOMSTR_INTSTAT_NAK_M                  0x00000010
#define AM_REG_IOMSTR_INTSTAT_NAK(n)                 (((uint32_t)(n) << 4) & 0x00000010)

// This is the Write FIFO Overflow interrupt. An attempt was made to write the
// FIFO while it was full (i.e. while FIFOSIZ > 124).
#define AM_REG_IOMSTR_INTSTAT_FOVFL_S                3
#define AM_REG_IOMSTR_INTSTAT_FOVFL_M                0x00000008
#define AM_REG_IOMSTR_INTSTAT_FOVFL(n)               (((uint32_t)(n) << 3) & 0x00000008)

// This is the Read FIFO Underflow interrupt. An attempt was made to read FIFO
// when empty (i.e. while FIFOSIZ less than 4).
#define AM_REG_IOMSTR_INTSTAT_FUNDFL_S               2
#define AM_REG_IOMSTR_INTSTAT_FUNDFL_M               0x00000004
#define AM_REG_IOMSTR_INTSTAT_FUNDFL(n)              (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO Threshold interrupt.
#define AM_REG_IOMSTR_INTSTAT_THR_S                  1
#define AM_REG_IOMSTR_INTSTAT_THR_M                  0x00000002
#define AM_REG_IOMSTR_INTSTAT_THR(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// This is the Command Complete interrupt.
#define AM_REG_IOMSTR_INTSTAT_CMDCMP_S               0
#define AM_REG_IOMSTR_INTSTAT_CMDCMP_M               0x00000001
#define AM_REG_IOMSTR_INTSTAT_CMDCMP(n)              (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOMSTR_INTCLR - IO Master Interrupts: Clear
//
//*****************************************************************************
// This is the arbitration loss interrupt. This error occurs if another master
// collides with an IO Master transfer. Generally, the IOM started an operation
// but found SDA already low.
#define AM_REG_IOMSTR_INTCLR_ARB_S                   10
#define AM_REG_IOMSTR_INTCLR_ARB_M                   0x00000400
#define AM_REG_IOMSTR_INTCLR_ARB(n)                  (((uint32_t)(n) << 10) & 0x00000400)

// This is the STOP command interrupt. A STOP bit was detected by the IOM.
#define AM_REG_IOMSTR_INTCLR_STOP_S                  9
#define AM_REG_IOMSTR_INTCLR_STOP_M                  0x00000200
#define AM_REG_IOMSTR_INTCLR_STOP(n)                 (((uint32_t)(n) << 9) & 0x00000200)

// This is the START command interrupt. A START from another master was
// detected. Software must wait for a STOP before proceeding.
#define AM_REG_IOMSTR_INTCLR_START_S                 8
#define AM_REG_IOMSTR_INTCLR_START_M                 0x00000100
#define AM_REG_IOMSTR_INTCLR_START(n)                (((uint32_t)(n) << 8) & 0x00000100)

// This is the illegal command interrupt. Software attempted to issue a CMD
// while another CMD was already in progress. Or an attempt was made to issue a
// non-zero-length write CMD with an empty FIFO.
#define AM_REG_IOMSTR_INTCLR_ICMD_S                  7
#define AM_REG_IOMSTR_INTCLR_ICMD_M                  0x00000080
#define AM_REG_IOMSTR_INTCLR_ICMD(n)                 (((uint32_t)(n) << 7) & 0x00000080)

// This is the illegal FIFO access interrupt. An attempt was made to read the
// FIFO during a write CMD. Or an attempt was made to write the FIFO on a read
// CMD.
#define AM_REG_IOMSTR_INTCLR_IACC_S                  6
#define AM_REG_IOMSTR_INTCLR_IACC_M                  0x00000040
#define AM_REG_IOMSTR_INTCLR_IACC(n)                 (((uint32_t)(n) << 6) & 0x00000040)

// This is the WTLEN interrupt.
#define AM_REG_IOMSTR_INTCLR_WTLEN_S                 5
#define AM_REG_IOMSTR_INTCLR_WTLEN_M                 0x00000020
#define AM_REG_IOMSTR_INTCLR_WTLEN(n)                (((uint32_t)(n) << 5) & 0x00000020)

// This is the I2C NAK interrupt. The expected ACK from the slave was not
// received by the IOM.
#define AM_REG_IOMSTR_INTCLR_NAK_S                   4
#define AM_REG_IOMSTR_INTCLR_NAK_M                   0x00000010
#define AM_REG_IOMSTR_INTCLR_NAK(n)                  (((uint32_t)(n) << 4) & 0x00000010)

// This is the Write FIFO Overflow interrupt. An attempt was made to write the
// FIFO while it was full (i.e. while FIFOSIZ > 124).
#define AM_REG_IOMSTR_INTCLR_FOVFL_S                 3
#define AM_REG_IOMSTR_INTCLR_FOVFL_M                 0x00000008
#define AM_REG_IOMSTR_INTCLR_FOVFL(n)                (((uint32_t)(n) << 3) & 0x00000008)

// This is the Read FIFO Underflow interrupt. An attempt was made to read FIFO
// when empty (i.e. while FIFOSIZ less than 4).
#define AM_REG_IOMSTR_INTCLR_FUNDFL_S                2
#define AM_REG_IOMSTR_INTCLR_FUNDFL_M                0x00000004
#define AM_REG_IOMSTR_INTCLR_FUNDFL(n)               (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO Threshold interrupt.
#define AM_REG_IOMSTR_INTCLR_THR_S                   1
#define AM_REG_IOMSTR_INTCLR_THR_M                   0x00000002
#define AM_REG_IOMSTR_INTCLR_THR(n)                  (((uint32_t)(n) << 1) & 0x00000002)

// This is the Command Complete interrupt.
#define AM_REG_IOMSTR_INTCLR_CMDCMP_S                0
#define AM_REG_IOMSTR_INTCLR_CMDCMP_M                0x00000001
#define AM_REG_IOMSTR_INTCLR_CMDCMP(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOMSTR_INTSET - IO Master Interrupts: Set
//
//*****************************************************************************
// This is the arbitration loss interrupt. This error occurs if another master
// collides with an IO Master transfer. Generally, the IOM started an operation
// but found SDA already low.
#define AM_REG_IOMSTR_INTSET_ARB_S                   10
#define AM_REG_IOMSTR_INTSET_ARB_M                   0x00000400
#define AM_REG_IOMSTR_INTSET_ARB(n)                  (((uint32_t)(n) << 10) & 0x00000400)

// This is the STOP command interrupt. A STOP bit was detected by the IOM.
#define AM_REG_IOMSTR_INTSET_STOP_S                  9
#define AM_REG_IOMSTR_INTSET_STOP_M                  0x00000200
#define AM_REG_IOMSTR_INTSET_STOP(n)                 (((uint32_t)(n) << 9) & 0x00000200)

// This is the START command interrupt. A START from another master was
// detected. Software must wait for a STOP before proceeding.
#define AM_REG_IOMSTR_INTSET_START_S                 8
#define AM_REG_IOMSTR_INTSET_START_M                 0x00000100
#define AM_REG_IOMSTR_INTSET_START(n)                (((uint32_t)(n) << 8) & 0x00000100)

// This is the illegal command interrupt. Software attempted to issue a CMD
// while another CMD was already in progress. Or an attempt was made to issue a
// non-zero-length write CMD with an empty FIFO.
#define AM_REG_IOMSTR_INTSET_ICMD_S                  7
#define AM_REG_IOMSTR_INTSET_ICMD_M                  0x00000080
#define AM_REG_IOMSTR_INTSET_ICMD(n)                 (((uint32_t)(n) << 7) & 0x00000080)

// This is the illegal FIFO access interrupt. An attempt was made to read the
// FIFO during a write CMD. Or an attempt was made to write the FIFO on a read
// CMD.
#define AM_REG_IOMSTR_INTSET_IACC_S                  6
#define AM_REG_IOMSTR_INTSET_IACC_M                  0x00000040
#define AM_REG_IOMSTR_INTSET_IACC(n)                 (((uint32_t)(n) << 6) & 0x00000040)

// This is the WTLEN interrupt.
#define AM_REG_IOMSTR_INTSET_WTLEN_S                 5
#define AM_REG_IOMSTR_INTSET_WTLEN_M                 0x00000020
#define AM_REG_IOMSTR_INTSET_WTLEN(n)                (((uint32_t)(n) << 5) & 0x00000020)

// This is the I2C NAK interrupt. The expected ACK from the slave was not
// received by the IOM.
#define AM_REG_IOMSTR_INTSET_NAK_S                   4
#define AM_REG_IOMSTR_INTSET_NAK_M                   0x00000010
#define AM_REG_IOMSTR_INTSET_NAK(n)                  (((uint32_t)(n) << 4) & 0x00000010)

// This is the Write FIFO Overflow interrupt. An attempt was made to write the
// FIFO while it was full (i.e. while FIFOSIZ > 124).
#define AM_REG_IOMSTR_INTSET_FOVFL_S                 3
#define AM_REG_IOMSTR_INTSET_FOVFL_M                 0x00000008
#define AM_REG_IOMSTR_INTSET_FOVFL(n)                (((uint32_t)(n) << 3) & 0x00000008)

// This is the Read FIFO Underflow interrupt. An attempt was made to read FIFO
// when empty (i.e. while FIFOSIZ less than 4).
#define AM_REG_IOMSTR_INTSET_FUNDFL_S                2
#define AM_REG_IOMSTR_INTSET_FUNDFL_M                0x00000004
#define AM_REG_IOMSTR_INTSET_FUNDFL(n)               (((uint32_t)(n) << 2) & 0x00000004)

// This is the FIFO Threshold interrupt.
#define AM_REG_IOMSTR_INTSET_THR_S                   1
#define AM_REG_IOMSTR_INTSET_THR_M                   0x00000002
#define AM_REG_IOMSTR_INTSET_THR(n)                  (((uint32_t)(n) << 1) & 0x00000002)

// This is the Command Complete interrupt.
#define AM_REG_IOMSTR_INTSET_CMDCMP_S                0
#define AM_REG_IOMSTR_INTSET_CMDCMP_M                0x00000001
#define AM_REG_IOMSTR_INTSET_CMDCMP(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// IOMSTR_FIFO - FIFO Access Port
//
//*****************************************************************************
// FIFO access port.
#define AM_REG_IOMSTR_FIFO_FIFO_S                    0
#define AM_REG_IOMSTR_FIFO_FIFO_M                    0xFFFFFFFF
#define AM_REG_IOMSTR_FIFO_FIFO(n)                   (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// IOMSTR_FIFOPTR - Current FIFO Pointers
//
//*****************************************************************************
// The number of bytes remaining in the FIFO (i.e. 128-FIFOSIZ if FULLDUP = 0 or
// 64-FIFOSIZ if FULLDUP = 1)).
#define AM_REG_IOMSTR_FIFOPTR_FIFOREM_S              16
#define AM_REG_IOMSTR_FIFOPTR_FIFOREM_M              0x00FF0000
#define AM_REG_IOMSTR_FIFOPTR_FIFOREM(n)             (((uint32_t)(n) << 16) & 0x00FF0000)

// The number of bytes currently in the FIFO.
#define AM_REG_IOMSTR_FIFOPTR_FIFOSIZ_S              0
#define AM_REG_IOMSTR_FIFOPTR_FIFOSIZ_M              0x000000FF
#define AM_REG_IOMSTR_FIFOPTR_FIFOSIZ(n)             (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// IOMSTR_TLNGTH - Transfer Length
//
//*****************************************************************************
// Remaining transfer length.
#define AM_REG_IOMSTR_TLNGTH_TLNGTH_S                0
#define AM_REG_IOMSTR_TLNGTH_TLNGTH_M                0x00000FFF
#define AM_REG_IOMSTR_TLNGTH_TLNGTH(n)               (((uint32_t)(n) << 0) & 0x00000FFF)

//*****************************************************************************
//
// IOMSTR_FIFOTHR - FIFO Threshold Configuration
//
//*****************************************************************************
// FIFO write threshold.
#define AM_REG_IOMSTR_FIFOTHR_FIFOWTHR_S             8
#define AM_REG_IOMSTR_FIFOTHR_FIFOWTHR_M             0x00007F00
#define AM_REG_IOMSTR_FIFOTHR_FIFOWTHR(n)            (((uint32_t)(n) << 8) & 0x00007F00)

// FIFO read threshold.
#define AM_REG_IOMSTR_FIFOTHR_FIFORTHR_S             0
#define AM_REG_IOMSTR_FIFOTHR_FIFORTHR_M             0x0000007F
#define AM_REG_IOMSTR_FIFOTHR_FIFORTHR(n)            (((uint32_t)(n) << 0) & 0x0000007F)

//*****************************************************************************
//
// IOMSTR_CLKCFG - I/O Clock Configuration
//
//*****************************************************************************
// Clock total count minus 1.
#define AM_REG_IOMSTR_CLKCFG_TOTPER_S                24
#define AM_REG_IOMSTR_CLKCFG_TOTPER_M                0xFF000000
#define AM_REG_IOMSTR_CLKCFG_TOTPER(n)               (((uint32_t)(n) << 24) & 0xFF000000)

// Clock low count minus 1.
#define AM_REG_IOMSTR_CLKCFG_LOWPER_S                16
#define AM_REG_IOMSTR_CLKCFG_LOWPER_M                0x00FF0000
#define AM_REG_IOMSTR_CLKCFG_LOWPER(n)               (((uint32_t)(n) << 16) & 0x00FF0000)

// Enable clock division by TOTPER.
#define AM_REG_IOMSTR_CLKCFG_DIVEN_S                 12
#define AM_REG_IOMSTR_CLKCFG_DIVEN_M                 0x00001000
#define AM_REG_IOMSTR_CLKCFG_DIVEN(n)                (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_IOMSTR_CLKCFG_DIVEN_DIS               0x00000000
#define AM_REG_IOMSTR_CLKCFG_DIVEN_EN                0x00001000

// Enable divide by 3.
#define AM_REG_IOMSTR_CLKCFG_DIV3_S                  11
#define AM_REG_IOMSTR_CLKCFG_DIV3_M                  0x00000800
#define AM_REG_IOMSTR_CLKCFG_DIV3(n)                 (((uint32_t)(n) << 11) & 0x00000800)
#define AM_REG_IOMSTR_CLKCFG_DIV3_DIS                0x00000000
#define AM_REG_IOMSTR_CLKCFG_DIV3_EN                 0x00000800

// Select the input clock frequency.
#define AM_REG_IOMSTR_CLKCFG_FSEL_S                  8
#define AM_REG_IOMSTR_CLKCFG_FSEL_M                  0x00000700
#define AM_REG_IOMSTR_CLKCFG_FSEL(n)                 (((uint32_t)(n) << 8) & 0x00000700)
#define AM_REG_IOMSTR_CLKCFG_FSEL_MIN_PWR            0x00000000
#define AM_REG_IOMSTR_CLKCFG_FSEL_HFRC               0x00000100
#define AM_REG_IOMSTR_CLKCFG_FSEL_HFRC_DIV2          0x00000200
#define AM_REG_IOMSTR_CLKCFG_FSEL_HFRC_DIV4          0x00000300
#define AM_REG_IOMSTR_CLKCFG_FSEL_HFRC_DIV8          0x00000400
#define AM_REG_IOMSTR_CLKCFG_FSEL_HFRC_DIV16         0x00000500
#define AM_REG_IOMSTR_CLKCFG_FSEL_HFRC_DIV32         0x00000600
#define AM_REG_IOMSTR_CLKCFG_FSEL_HFRC_DIV64         0x00000700

//*****************************************************************************
//
// IOMSTR_CMD - Command Register
//
//*****************************************************************************
// This register holds the I/O Command
#define AM_REG_IOMSTR_CMD_CMD_S                      0
#define AM_REG_IOMSTR_CMD_CMD_M                      0xFFFFFFFF
#define AM_REG_IOMSTR_CMD_CMD(n)                     (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// IOMSTR_CMDRPT - Command Repeat Register
//
//*****************************************************************************
// These bits hold the Command repeat count.
#define AM_REG_IOMSTR_CMDRPT_CMDRPT_S                0
#define AM_REG_IOMSTR_CMDRPT_CMDRPT_M                0x0000001F
#define AM_REG_IOMSTR_CMDRPT_CMDRPT(n)               (((uint32_t)(n) << 0) & 0x0000001F)

//*****************************************************************************
//
// IOMSTR_STATUS - Status Register
//
//*****************************************************************************
// This bit indicates if the I/O state machine is IDLE.
#define AM_REG_IOMSTR_STATUS_IDLEST_S                2
#define AM_REG_IOMSTR_STATUS_IDLEST_M                0x00000004
#define AM_REG_IOMSTR_STATUS_IDLEST(n)               (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_IOMSTR_STATUS_IDLEST_IDLE             0x00000004

// This bit indicates if the I/O Command is active.
#define AM_REG_IOMSTR_STATUS_CMDACT_S                1
#define AM_REG_IOMSTR_STATUS_CMDACT_M                0x00000002
#define AM_REG_IOMSTR_STATUS_CMDACT(n)               (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_IOMSTR_STATUS_CMDACT_ACTIVE           0x00000002

// This bit indicates if an error interrupt has occurred.
#define AM_REG_IOMSTR_STATUS_ERR_S                   0
#define AM_REG_IOMSTR_STATUS_ERR_M                   0x00000001
#define AM_REG_IOMSTR_STATUS_ERR(n)                  (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_IOMSTR_STATUS_ERR_ERROR               0x00000001

//*****************************************************************************
//
// IOMSTR_CFG - I/O Master Configuration
//
//*****************************************************************************
// This bit enables the IO Master.
#define AM_REG_IOMSTR_CFG_IFCEN_S                    31
#define AM_REG_IOMSTR_CFG_IFCEN_M                    0x80000000
#define AM_REG_IOMSTR_CFG_IFCEN(n)                   (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_IOMSTR_CFG_IFCEN_DIS                  0x00000000
#define AM_REG_IOMSTR_CFG_IFCEN_EN                   0x80000000

// This bit selects the read flow control signal polarity.
#define AM_REG_IOMSTR_CFG_RDFCPOL_S                  14
#define AM_REG_IOMSTR_CFG_RDFCPOL_M                  0x00004000
#define AM_REG_IOMSTR_CFG_RDFCPOL(n)                 (((uint32_t)(n) << 14) & 0x00004000)
#define AM_REG_IOMSTR_CFG_RDFCPOL_HIGH               0x00000000
#define AM_REG_IOMSTR_CFG_RDFCPOL_LOW                0x00004000

// This bit selects the write flow control signal polarity.
#define AM_REG_IOMSTR_CFG_WTFCPOL_S                  13
#define AM_REG_IOMSTR_CFG_WTFCPOL_M                  0x00002000
#define AM_REG_IOMSTR_CFG_WTFCPOL(n)                 (((uint32_t)(n) << 13) & 0x00002000)
#define AM_REG_IOMSTR_CFG_WTFCPOL_HIGH               0x00000000
#define AM_REG_IOMSTR_CFG_WTFCPOL_LOW                0x00002000

// This bit selects the write mode flow control signal.
#define AM_REG_IOMSTR_CFG_WTFCIRQ_S                  12
#define AM_REG_IOMSTR_CFG_WTFCIRQ_M                  0x00001000
#define AM_REG_IOMSTR_CFG_WTFCIRQ(n)                 (((uint32_t)(n) << 12) & 0x00001000)
#define AM_REG_IOMSTR_CFG_WTFCIRQ_MISO               0x00000000
#define AM_REG_IOMSTR_CFG_WTFCIRQ_IRQ                0x00001000

// This bit must be left at the default value of 0.
#define AM_REG_IOMSTR_CFG_FCDEL_S                    11
#define AM_REG_IOMSTR_CFG_FCDEL_M                    0x00000800
#define AM_REG_IOMSTR_CFG_FCDEL(n)                   (((uint32_t)(n) << 11) & 0x00000800)

// This bit invewrts MOSI when flow control is enabled.
#define AM_REG_IOMSTR_CFG_MOSIINV_S                  10
#define AM_REG_IOMSTR_CFG_MOSIINV_M                  0x00000400
#define AM_REG_IOMSTR_CFG_MOSIINV(n)                 (((uint32_t)(n) << 10) & 0x00000400)
#define AM_REG_IOMSTR_CFG_MOSIINV_NORMAL             0x00000000
#define AM_REG_IOMSTR_CFG_MOSIINV_INVERT             0x00000400

// This bit enables read mode flow control.
#define AM_REG_IOMSTR_CFG_RDFC_S                     9
#define AM_REG_IOMSTR_CFG_RDFC_M                     0x00000200
#define AM_REG_IOMSTR_CFG_RDFC(n)                    (((uint32_t)(n) << 9) & 0x00000200)
#define AM_REG_IOMSTR_CFG_RDFC_DIS                   0x00000000
#define AM_REG_IOMSTR_CFG_RDFC_EN                    0x00000200

// This bit enables write mode flow control.
#define AM_REG_IOMSTR_CFG_WTFC_S                     8
#define AM_REG_IOMSTR_CFG_WTFC_M                     0x00000100
#define AM_REG_IOMSTR_CFG_WTFC(n)                    (((uint32_t)(n) << 8) & 0x00000100)
#define AM_REG_IOMSTR_CFG_WTFC_DIS                   0x00000000
#define AM_REG_IOMSTR_CFG_WTFC_EN                    0x00000100

// This bit selects the preread timing.
#define AM_REG_IOMSTR_CFG_STARTRD_S                  4
#define AM_REG_IOMSTR_CFG_STARTRD_M                  0x00000030
#define AM_REG_IOMSTR_CFG_STARTRD(n)                 (((uint32_t)(n) << 4) & 0x00000030)
#define AM_REG_IOMSTR_CFG_STARTRD_PRERD0             0x00000000
#define AM_REG_IOMSTR_CFG_STARTRD_PRERD1             0x00000010
#define AM_REG_IOMSTR_CFG_STARTRD_PRERD2             0x00000020
#define AM_REG_IOMSTR_CFG_STARTRD_PRERD3             0x00000030

// This bit selects full duplex mode.
#define AM_REG_IOMSTR_CFG_FULLDUP_S                  3
#define AM_REG_IOMSTR_CFG_FULLDUP_M                  0x00000008
#define AM_REG_IOMSTR_CFG_FULLDUP(n)                 (((uint32_t)(n) << 3) & 0x00000008)
#define AM_REG_IOMSTR_CFG_FULLDUP_NORMAL             0x00000000
#define AM_REG_IOMSTR_CFG_FULLDUP_FULLDUP            0x00000008

// This bit selects SPI phase.
#define AM_REG_IOMSTR_CFG_SPHA_S                     2
#define AM_REG_IOMSTR_CFG_SPHA_M                     0x00000004
#define AM_REG_IOMSTR_CFG_SPHA(n)                    (((uint32_t)(n) << 2) & 0x00000004)
#define AM_REG_IOMSTR_CFG_SPHA_SAMPLE_LEADING_EDGE   0x00000000
#define AM_REG_IOMSTR_CFG_SPHA_SAMPLE_TRAILING_EDGE  0x00000004

// This bit selects SPI polarity.
#define AM_REG_IOMSTR_CFG_SPOL_S                     1
#define AM_REG_IOMSTR_CFG_SPOL_M                     0x00000002
#define AM_REG_IOMSTR_CFG_SPOL(n)                    (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_IOMSTR_CFG_SPOL_CLK_BASE_0            0x00000000
#define AM_REG_IOMSTR_CFG_SPOL_CLK_BASE_1            0x00000002

// This bit selects the I/O interface.
#define AM_REG_IOMSTR_CFG_IFCSEL_S                   0
#define AM_REG_IOMSTR_CFG_IFCSEL_M                   0x00000001
#define AM_REG_IOMSTR_CFG_IFCSEL(n)                  (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_IOMSTR_CFG_IFCSEL_I2C                 0x00000000
#define AM_REG_IOMSTR_CFG_IFCSEL_SPI                 0x00000001

#endif // AM_REG_IOMSTR_H
