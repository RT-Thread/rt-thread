//*****************************************************************************
//
//  am_reg_rtc.h
//! @file
//!
//! @brief Register macros for the RTC module
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
#ifndef AM_REG_RTC_H
#define AM_REG_RTC_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_RTC_NUM_MODULES                       1
#define AM_REG_RTCn(n) \
    (REG_RTC_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_RTC_CTRLOW_O                          0x00000040
#define AM_REG_RTC_CTRUP_O                           0x00000044
#define AM_REG_RTC_ALMLOW_O                          0x00000048
#define AM_REG_RTC_ALMUP_O                           0x0000004C
#define AM_REG_RTC_RTCCTL_O                          0x00000050
#define AM_REG_RTC_INTEN_O                           0x00000100
#define AM_REG_RTC_INTSTAT_O                         0x00000104
#define AM_REG_RTC_INTCLR_O                          0x00000108
#define AM_REG_RTC_INTSET_O                          0x0000010C

//*****************************************************************************
//
// RTC_INTEN - RTC Interrupt Register: Enable
//
//*****************************************************************************
// RTC Alarm interrupt
#define AM_REG_RTC_INTEN_ALM_S                       3
#define AM_REG_RTC_INTEN_ALM_M                       0x00000008
#define AM_REG_RTC_INTEN_ALM(n)                      (((uint32_t)(n) << 3) & 0x00000008)

// XT Oscillator Fail interrupt
#define AM_REG_RTC_INTEN_OF_S                        2
#define AM_REG_RTC_INTEN_OF_M                        0x00000004
#define AM_REG_RTC_INTEN_OF(n)                       (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_RTC_INTEN_ACC_S                       1
#define AM_REG_RTC_INTEN_ACC_M                       0x00000002
#define AM_REG_RTC_INTEN_ACC(n)                      (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_RTC_INTEN_ACF_S                       0
#define AM_REG_RTC_INTEN_ACF_M                       0x00000001
#define AM_REG_RTC_INTEN_ACF(n)                      (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RTC_INTSTAT - RTC Interrupt Register: Status
//
//*****************************************************************************
// RTC Alarm interrupt
#define AM_REG_RTC_INTSTAT_ALM_S                     3
#define AM_REG_RTC_INTSTAT_ALM_M                     0x00000008
#define AM_REG_RTC_INTSTAT_ALM(n)                    (((uint32_t)(n) << 3) & 0x00000008)

// XT Oscillator Fail interrupt
#define AM_REG_RTC_INTSTAT_OF_S                      2
#define AM_REG_RTC_INTSTAT_OF_M                      0x00000004
#define AM_REG_RTC_INTSTAT_OF(n)                     (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_RTC_INTSTAT_ACC_S                     1
#define AM_REG_RTC_INTSTAT_ACC_M                     0x00000002
#define AM_REG_RTC_INTSTAT_ACC(n)                    (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_RTC_INTSTAT_ACF_S                     0
#define AM_REG_RTC_INTSTAT_ACF_M                     0x00000001
#define AM_REG_RTC_INTSTAT_ACF(n)                    (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RTC_INTCLR - RTC Interrupt Register: Clear
//
//*****************************************************************************
// RTC Alarm interrupt
#define AM_REG_RTC_INTCLR_ALM_S                      3
#define AM_REG_RTC_INTCLR_ALM_M                      0x00000008
#define AM_REG_RTC_INTCLR_ALM(n)                     (((uint32_t)(n) << 3) & 0x00000008)

// XT Oscillator Fail interrupt
#define AM_REG_RTC_INTCLR_OF_S                       2
#define AM_REG_RTC_INTCLR_OF_M                       0x00000004
#define AM_REG_RTC_INTCLR_OF(n)                      (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_RTC_INTCLR_ACC_S                      1
#define AM_REG_RTC_INTCLR_ACC_M                      0x00000002
#define AM_REG_RTC_INTCLR_ACC(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_RTC_INTCLR_ACF_S                      0
#define AM_REG_RTC_INTCLR_ACF_M                      0x00000001
#define AM_REG_RTC_INTCLR_ACF(n)                     (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RTC_INTSET - RTC Interrupt Register: Set
//
//*****************************************************************************
// RTC Alarm interrupt
#define AM_REG_RTC_INTSET_ALM_S                      3
#define AM_REG_RTC_INTSET_ALM_M                      0x00000008
#define AM_REG_RTC_INTSET_ALM(n)                     (((uint32_t)(n) << 3) & 0x00000008)

// XT Oscillator Fail interrupt
#define AM_REG_RTC_INTSET_OF_S                       2
#define AM_REG_RTC_INTSET_OF_M                       0x00000004
#define AM_REG_RTC_INTSET_OF(n)                      (((uint32_t)(n) << 2) & 0x00000004)

// Autocalibration Complete interrupt
#define AM_REG_RTC_INTSET_ACC_S                      1
#define AM_REG_RTC_INTSET_ACC_M                      0x00000002
#define AM_REG_RTC_INTSET_ACC(n)                     (((uint32_t)(n) << 1) & 0x00000002)

// Autocalibration Fail interrupt
#define AM_REG_RTC_INTSET_ACF_S                      0
#define AM_REG_RTC_INTSET_ACF_M                      0x00000001
#define AM_REG_RTC_INTSET_ACF(n)                     (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// RTC_CTRLOW - RTC Counters Lower
//
//*****************************************************************************
// Hours Counter
#define AM_REG_RTC_CTRLOW_CTRHR_S                    24
#define AM_REG_RTC_CTRLOW_CTRHR_M                    0x3F000000
#define AM_REG_RTC_CTRLOW_CTRHR(n)                   (((uint32_t)(n) << 24) & 0x3F000000)

// Minutes Counter
#define AM_REG_RTC_CTRLOW_CTRMIN_S                   16
#define AM_REG_RTC_CTRLOW_CTRMIN_M                   0x007F0000
#define AM_REG_RTC_CTRLOW_CTRMIN(n)                  (((uint32_t)(n) << 16) & 0x007F0000)

// Seconds Counter
#define AM_REG_RTC_CTRLOW_CTRSEC_S                   8
#define AM_REG_RTC_CTRLOW_CTRSEC_M                   0x00007F00
#define AM_REG_RTC_CTRLOW_CTRSEC(n)                  (((uint32_t)(n) << 8) & 0x00007F00)

// 100ths of a second Counter
#define AM_REG_RTC_CTRLOW_CTR100_S                   0
#define AM_REG_RTC_CTRLOW_CTR100_M                   0x000000FF
#define AM_REG_RTC_CTRLOW_CTR100(n)                  (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// RTC_CTRUP - RTC Counters Upper
//
//*****************************************************************************
// Counter read error status
#define AM_REG_RTC_CTRUP_CTERR_S                     31
#define AM_REG_RTC_CTRUP_CTERR_M                     0x80000000
#define AM_REG_RTC_CTRUP_CTERR(n)                    (((uint32_t)(n) << 31) & 0x80000000)
#define AM_REG_RTC_CTRUP_CTERR_NOERR                 0x00000000
#define AM_REG_RTC_CTRUP_CTERR_RDERR                 0x80000000

// Century enable
#define AM_REG_RTC_CTRUP_CEB_S                       28
#define AM_REG_RTC_CTRUP_CEB_M                       0x10000000
#define AM_REG_RTC_CTRUP_CEB(n)                      (((uint32_t)(n) << 28) & 0x10000000)
#define AM_REG_RTC_CTRUP_CEB_DIS                     0x00000000
#define AM_REG_RTC_CTRUP_CEB_EN                      0x10000000

// Century
#define AM_REG_RTC_CTRUP_CB_S                        27
#define AM_REG_RTC_CTRUP_CB_M                        0x08000000
#define AM_REG_RTC_CTRUP_CB(n)                       (((uint32_t)(n) << 27) & 0x08000000)
#define AM_REG_RTC_CTRUP_CB_2000                     0x00000000
#define AM_REG_RTC_CTRUP_CB_1900_2100                0x08000000

// Weekdays Counter
#define AM_REG_RTC_CTRUP_CTRWKDY_S                   24
#define AM_REG_RTC_CTRUP_CTRWKDY_M                   0x07000000
#define AM_REG_RTC_CTRUP_CTRWKDY(n)                  (((uint32_t)(n) << 24) & 0x07000000)

// Years Counter
#define AM_REG_RTC_CTRUP_CTRYR_S                     16
#define AM_REG_RTC_CTRUP_CTRYR_M                     0x00FF0000
#define AM_REG_RTC_CTRUP_CTRYR(n)                    (((uint32_t)(n) << 16) & 0x00FF0000)

// Months Counter
#define AM_REG_RTC_CTRUP_CTRMO_S                     8
#define AM_REG_RTC_CTRUP_CTRMO_M                     0x00001F00
#define AM_REG_RTC_CTRUP_CTRMO(n)                    (((uint32_t)(n) << 8) & 0x00001F00)

// Date Counter
#define AM_REG_RTC_CTRUP_CTRDATE_S                   0
#define AM_REG_RTC_CTRUP_CTRDATE_M                   0x0000003F
#define AM_REG_RTC_CTRUP_CTRDATE(n)                  (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// RTC_ALMLOW - RTC Alarms Lower
//
//*****************************************************************************
// Hours Alarm
#define AM_REG_RTC_ALMLOW_ALMHR_S                    24
#define AM_REG_RTC_ALMLOW_ALMHR_M                    0x3F000000
#define AM_REG_RTC_ALMLOW_ALMHR(n)                   (((uint32_t)(n) << 24) & 0x3F000000)

// Minutes Alarm
#define AM_REG_RTC_ALMLOW_ALMMIN_S                   16
#define AM_REG_RTC_ALMLOW_ALMMIN_M                   0x007F0000
#define AM_REG_RTC_ALMLOW_ALMMIN(n)                  (((uint32_t)(n) << 16) & 0x007F0000)

// Seconds Alarm
#define AM_REG_RTC_ALMLOW_ALMSEC_S                   8
#define AM_REG_RTC_ALMLOW_ALMSEC_M                   0x00007F00
#define AM_REG_RTC_ALMLOW_ALMSEC(n)                  (((uint32_t)(n) << 8) & 0x00007F00)

// 100ths of a second Alarm
#define AM_REG_RTC_ALMLOW_ALM100_S                   0
#define AM_REG_RTC_ALMLOW_ALM100_M                   0x000000FF
#define AM_REG_RTC_ALMLOW_ALM100(n)                  (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// RTC_ALMUP - RTC Alarms Upper
//
//*****************************************************************************
// Weekdays Alarm
#define AM_REG_RTC_ALMUP_ALMWKDY_S                   16
#define AM_REG_RTC_ALMUP_ALMWKDY_M                   0x00070000
#define AM_REG_RTC_ALMUP_ALMWKDY(n)                  (((uint32_t)(n) << 16) & 0x00070000)

// Months Alarm
#define AM_REG_RTC_ALMUP_ALMMO_S                     8
#define AM_REG_RTC_ALMUP_ALMMO_M                     0x00001F00
#define AM_REG_RTC_ALMUP_ALMMO(n)                    (((uint32_t)(n) << 8) & 0x00001F00)

// Date Alarm
#define AM_REG_RTC_ALMUP_ALMDATE_S                   0
#define AM_REG_RTC_ALMUP_ALMDATE_M                   0x0000003F
#define AM_REG_RTC_ALMUP_ALMDATE(n)                  (((uint32_t)(n) << 0) & 0x0000003F)

//*****************************************************************************
//
// RTC_RTCCTL - RTC Control Register
//
//*****************************************************************************
// Hours Counter mode
#define AM_REG_RTC_RTCCTL_HR1224_S                   5
#define AM_REG_RTC_RTCCTL_HR1224_M                   0x00000020
#define AM_REG_RTC_RTCCTL_HR1224(n)                  (((uint32_t)(n) << 5) & 0x00000020)
#define AM_REG_RTC_RTCCTL_HR1224_24HR                0x00000000
#define AM_REG_RTC_RTCCTL_HR1224_12HR                0x00000020

// RTC input clock control
#define AM_REG_RTC_RTCCTL_RSTOP_S                    4
#define AM_REG_RTC_RTCCTL_RSTOP_M                    0x00000010
#define AM_REG_RTC_RTCCTL_RSTOP(n)                   (((uint32_t)(n) << 4) & 0x00000010)
#define AM_REG_RTC_RTCCTL_RSTOP_RUN                  0x00000000
#define AM_REG_RTC_RTCCTL_RSTOP_STOP                 0x00000010

// Alarm repeat interval
#define AM_REG_RTC_RTCCTL_RPT_S                      1
#define AM_REG_RTC_RTCCTL_RPT_M                      0x0000000E
#define AM_REG_RTC_RTCCTL_RPT(n)                     (((uint32_t)(n) << 1) & 0x0000000E)
#define AM_REG_RTC_RTCCTL_RPT_DIS                    0x00000000
#define AM_REG_RTC_RTCCTL_RPT_YEAR                   0x00000002
#define AM_REG_RTC_RTCCTL_RPT_MONTH                  0x00000004
#define AM_REG_RTC_RTCCTL_RPT_WEEK                   0x00000006
#define AM_REG_RTC_RTCCTL_RPT_DAY                    0x00000008
#define AM_REG_RTC_RTCCTL_RPT_HR                     0x0000000A
#define AM_REG_RTC_RTCCTL_RPT_MIN                    0x0000000C
#define AM_REG_RTC_RTCCTL_RPT_SEC                    0x0000000E

// Counter write control
#define AM_REG_RTC_RTCCTL_WRTC_S                     0
#define AM_REG_RTC_RTCCTL_WRTC_M                     0x00000001
#define AM_REG_RTC_RTCCTL_WRTC(n)                    (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_RTC_RTCCTL_WRTC_DIS                   0x00000000
#define AM_REG_RTC_RTCCTL_WRTC_EN                    0x00000001

#endif // AM_REG_RTC_H
