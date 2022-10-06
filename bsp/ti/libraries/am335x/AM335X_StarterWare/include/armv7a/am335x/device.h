/**
 * \file   device.h
 *
 * \brief  This file contains the function prototype and external variable
 *         declaration.
 *
 */

/*
* Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef _DEVICE_H_
#define _DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                  MACRO DEFNITION
****************************************************************************/

#define DEVICE_VERSION_1_0                   (0u)
#define DEVICE_VERSION_2_0                   (1u)
#define DEVICE_VERSION_2_1                   (2u)

/* EFUSE OPP bit mask */
#define EFUSE_OPP_MASK                       (0x00001FFFu)

/* EFUSE bit for OPP100 275Mhz - 1.1v */
#define EFUSE_OPP100_275_MASK                (0x00000001u)
#define EFUSE_OPP100_275                     (0x0u)

/* EFUSE bit for OPP100 500Mhz - 1.1v */
#define EFUSE_OPP100_500_MASK                (0x00000002u)
#define EFUSE_OPP100_500                     (0x1u)

/* EFUSE bit for OPP120 600Mhz - 1.2v */
#define EFUSE_OPP120_600_MASK                (0x00000004u)
#define EFUSE_OPP120_600                     (0x2u)

/* EFUSE bit for OPP TURBO 720Mhz - 1.26v */
#define EFUSE_OPPTB_720_MASK                 (0x00000008u)
#define EFUSE_OPPTB_720                      (0x3u)

/* EFUSE bit for OPP50 300Mhz - 950mv */
#define EFUSE_OPP50_300_MASK                 (0x00000010u)
#define EFUSE_OPP50_300                      (0x4u)

/* EFUSE bit for OPP100 300Mhz - 1.1v */
#define EFUSE_OPP100_300_MASK                (0x00000020u)
#define EFUSE_OPP100_300                     (0x5u)

/* EFUSE bit for OPP100 600Mhz - 1.1v */
#define EFUSE_OPP100_600_MASK                (0x00000040u)
#define EFUSE_OPP100_600                     (0x6u)

/* EFUSE bit for OPP120 720Mhz - 1.2v */
#define EFUSE_OPP120_720_MASK                (0x00000050u)
#define EFUSE_OPP120_720                     (0x7u)

/* EFUSE bit for OPP TURBO 800Mhz - 1.26v */
#define EFUSE_OPPTB_800_MASK                 (0x00000100u)
#define EFUSE_OPPTB_800                      (0x8u)

/* EFUSE bit for OPP NITRO 1000Mhz - 1.325v */
#define EFUSE_OPPNT_1000_MASK                (0x00000200u)
#define EFUSE_OPPNT_1000                     (0x9u)

#define EFUSE_OPP_MAX                        (EFUSE_OPPNT_1000 + 1)

/* Types of Opp */
#define OPP_NONE                             (0u)
#define OPP_50                               (1u)
#define OPP_100                              (2u)
#define OPP_120                              (3u)
#define SR_TURBO                             (4u)
#define OPP_NITRO                            (5u)

/* MACROS to Configure MPU divider */
#define MPUPLL_N                             (23u)
#define MPUPLL_M2                            (1u)

/* MACROS to configure MPU PLL */
#define MPUPLL_M_275_MHZ                     (275u)
#define MPUPLL_M_300_MHZ                     (300u)
#define MPUPLL_M_500_MHZ                     (500u)
#define MPUPLL_M_600_MHZ                     (600u)
#define MPUPLL_M_720_MHZ                     (720u)
#define MPUPLL_M_800_MHZ                     (800u)
#define MPUPLL_M_1000_MHZ                    (1000u)

/****************************************************************************
**                    FUNCTION PROTOTYPES
****************************************************************************/

unsigned int DeviceVersionGet(void);
unsigned int SysConfigOppDataGet(void);

#ifdef __cplusplus
}
#endif
#endif
