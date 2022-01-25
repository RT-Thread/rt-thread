/*
 * Copyright (C) 2014-2020 Xilinx, Inc.
 * Copyright (c) 2020-2021, WangHuachen
 * All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-30     WangHuachen  the first version
 */
#ifndef XPLATFORM_INFO_H        /* prevent circular inclusions */
#define XPLATFORM_INFO_H        /* by using protection macros */

#include "xil_types.h"
#include "xparameters.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined (versal)
#define XPAR_PMC_TAP_BASEADDR 0xF11A0000U
#define XPAR_PMC_TAP_VERSION_OFFSET 0x00000004U
#define XPLAT_PS_VERSION_ADDRESS (XPAR_PMC_TAP_BASEADDR + \
                                    XPAR_PMC_TAP_VERSION_OFFSET)
#else
#define XPAR_CSU_BASEADDR 0xFFCA0000U
#define    XPAR_CSU_VER_OFFSET 0x00000044U
#define XPLAT_PS_VERSION_ADDRESS (XPAR_CSU_BASEADDR + \
                                    XPAR_CSU_VER_OFFSET)
#endif
#define XPLAT_ZYNQ_ULTRA_MP_SILICON 0x0
#define XPLAT_ZYNQ_ULTRA_MP 0x1
#define XPLAT_ZYNQ_ULTRA_MPVEL 0x2
#define XPLAT_ZYNQ_ULTRA_MPQEMU 0x3
#define XPLAT_ZYNQ 0x4
#define XPLAT_MICROBLAZE 0x5
#define XPLAT_VERSAL 0x6U

#define XPS_VERSION_1 0x0
#define XPS_VERSION_2 0x1
#define XPLAT_INFO_MASK (0xF)

#if defined (versal)
#define XPS_VERSION_INFO_MASK 0xFF00U
#define XPS_VERSION_INFO_SHIFT 0x8U
#define XPLAT_INFO_SHIFT 0x18U
#else
#define XPS_VERSION_INFO_MASK (0xF)
#define XPS_VERSION_INFO_SHIFT 0x0U
#define XPLAT_INFO_SHIFT 0xCU
#endif

static INLINE u32 XGetPlatform_Info()
{
#if defined (versal)
    return XPLAT_VERSAL;
#elif defined (ARMR5) || (__aarch64__) || (ARMA53_32) || (PSU_PMU)
    return XPLAT_ZYNQ_ULTRA_MP;
#elif (__microblaze__)
    return XPLAT_MICROBLAZE;
#else
    return XPLAT_ZYNQ;
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
/**
* @} End of "addtogroup common_platform_info".
*/
