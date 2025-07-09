/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**                          MIMXRT1172AVM8A
**                          MIMXRT1172AVM8B
**                          MIMXRT1172CVM8A
**                          MIMXRT1172CVM8B
**                          MIMXRT1172DVMAA
**                          MIMXRT1172DVMAB
**                          MIMXRT1173CVM8A_cm4
**                          MIMXRT1173CVM8A_cm7
**                          MIMXRT1173CVM8B_cm4
**                          MIMXRT1173CVM8B_cm7
**                          MIMXRT1175AVM8A_cm4
**                          MIMXRT1175AVM8A_cm7
**                          MIMXRT1175AVM8B_cm4
**                          MIMXRT1175AVM8B_cm7
**                          MIMXRT1175CVM8A_cm4
**                          MIMXRT1175CVM8A_cm7
**                          MIMXRT1175CVM8B_cm4
**                          MIMXRT1175CVM8B_cm7
**                          MIMXRT1175DVMAA_cm4
**                          MIMXRT1175DVMAA_cm7
**                          MIMXRT1175DVMAB_cm4
**                          MIMXRT1175DVMAB_cm7
**                          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176AVM8B_cm4
**                          MIMXRT1176AVM8B_cm7
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176CVM8B_cm4
**                          MIMXRT1176CVM8B_cm7
**                          MIMXRT1176DVMAA_cm4
**                          MIMXRT1176DVMAA_cm7
**                          MIMXRT1176DVMAB_cm4
**                          MIMXRT1176DVMAB_cm7
**                          MIMXRT117HAVM8A_cm4
**                          MIMXRT117HAVM8A_cm7
**                          MIMXRT117HAVM8B_cm4
**                          MIMXRT117HAVM8B_cm7
**                          MIMXRT117HCVM8A_cm4
**                          MIMXRT117HCVM8A_cm7
**                          MIMXRT117HCVM8B_cm4
**                          MIMXRT117HCVM8B_cm7
**                          MIMXRT117HDVMAA_cm4
**                          MIMXRT117HDVMAA_cm7
**                          MIMXRT117HDVMAB_cm4
**                          MIMXRT117HDVMAB_cm7
**
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for IOMUXC
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file PERI_IOMUXC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for IOMUXC
 *
 * CMSIS Peripheral Access Layer for IOMUXC
 */

#if !defined(PERI_IOMUXC_H_)
#define PERI_IOMUXC_H_                           /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMXRT1171AVM8A) || defined(CPU_MIMXRT1171AVM8B) || defined(CPU_MIMXRT1171CVM8A) || defined(CPU_MIMXRT1171CVM8B) || defined(CPU_MIMXRT1171DVMAA) || defined(CPU_MIMXRT1171DVMAB))
#include "MIMXRT1171_COMMON.h"
#elif (defined(CPU_MIMXRT1172AVM8A) || defined(CPU_MIMXRT1172AVM8B) || defined(CPU_MIMXRT1172CVM8A) || defined(CPU_MIMXRT1172CVM8B) || defined(CPU_MIMXRT1172DVMAA) || defined(CPU_MIMXRT1172DVMAB))
#include "MIMXRT1172_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm4) || defined(CPU_MIMXRT1173CVM8B_cm4))
#include "MIMXRT1173_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm7) || defined(CPU_MIMXRT1173CVM8B_cm7))
#include "MIMXRT1173_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm4) || defined(CPU_MIMXRT1175AVM8B_cm4) || defined(CPU_MIMXRT1175CVM8A_cm4) || defined(CPU_MIMXRT1175CVM8B_cm4) || defined(CPU_MIMXRT1175DVMAA_cm4) || defined(CPU_MIMXRT1175DVMAB_cm4))
#include "MIMXRT1175_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm7) || defined(CPU_MIMXRT1175AVM8B_cm7) || defined(CPU_MIMXRT1175CVM8A_cm7) || defined(CPU_MIMXRT1175CVM8B_cm7) || defined(CPU_MIMXRT1175DVMAA_cm7) || defined(CPU_MIMXRT1175DVMAB_cm7))
#include "MIMXRT1175_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm4) || defined(CPU_MIMXRT1176AVM8B_cm4) || defined(CPU_MIMXRT1176CVM8A_cm4) || defined(CPU_MIMXRT1176CVM8B_cm4) || defined(CPU_MIMXRT1176DVMAA_cm4) || defined(CPU_MIMXRT1176DVMAB_cm4))
#include "MIMXRT1176_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm7) || defined(CPU_MIMXRT1176AVM8B_cm7) || defined(CPU_MIMXRT1176CVM8A_cm7) || defined(CPU_MIMXRT1176CVM8B_cm7) || defined(CPU_MIMXRT1176DVMAA_cm7) || defined(CPU_MIMXRT1176DVMAB_cm7))
#include "MIMXRT1176_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm4) || defined(CPU_MIMXRT117HAVM8B_cm4) || defined(CPU_MIMXRT117HCVM8A_cm4) || defined(CPU_MIMXRT117HCVM8B_cm4) || defined(CPU_MIMXRT117HDVMAA_cm4) || defined(CPU_MIMXRT117HDVMAB_cm4))
#include "MIMXRT117H_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm7) || defined(CPU_MIMXRT117HAVM8B_cm7) || defined(CPU_MIMXRT117HCVM8A_cm7) || defined(CPU_MIMXRT117HCVM8B_cm7) || defined(CPU_MIMXRT117HDVMAA_cm7) || defined(CPU_MIMXRT117HDVMAB_cm7))
#include "MIMXRT117H_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
#if !defined(IOMUXC_SW_MUX_CTL_PAD_T_)
#define IOMUXC_SW_MUX_CTL_PAD_T_
/*!
 * @addtogroup iomuxc_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC SW_MUX_CTL_PAD
 *
 * Defines the enumeration for the IOMUXC SW_MUX_CTL_PAD collections.
 */
typedef enum _iomuxc_sw_mux_ctl_pad
{
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_00 = 0U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_01 = 1U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_02 = 2U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_03 = 3U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_04 = 4U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_05 = 5U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_06 = 6U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_07 = 7U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_08 = 8U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_09 = 9U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_10 = 10U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_11 = 11U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_12 = 12U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_13 = 13U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_14 = 14U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_15 = 15U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_16 = 16U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_17 = 17U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_18 = 18U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_19 = 19U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_20 = 20U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_21 = 21U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_22 = 22U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_23 = 23U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_24 = 24U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_25 = 25U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_26 = 26U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_27 = 27U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_28 = 28U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_29 = 29U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_30 = 30U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_31 = 31U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_32 = 32U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_33 = 33U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_34 = 34U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_35 = 35U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_36 = 36U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_37 = 37U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_38 = 38U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_39 = 39U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_40 = 40U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B1_41 = 41U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_00 = 42U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_01 = 43U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_02 = 44U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_03 = 45U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_04 = 46U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_05 = 47U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_06 = 48U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_07 = 49U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_08 = 50U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_09 = 51U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_10 = 52U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_11 = 53U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_12 = 54U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_13 = 55U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_14 = 56U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_15 = 57U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_16 = 58U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_17 = 59U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_18 = 60U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_19 = 61U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_B2_20 = 62U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_00 = 63U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_01 = 64U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_02 = 65U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_03 = 66U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_04 = 67U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_05 = 68U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_06 = 69U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_07 = 70U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_08 = 71U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_09 = 72U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_10 = 73U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_11 = 74U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_12 = 75U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_13 = 76U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_14 = 77U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_15 = 78U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_16 = 79U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_17 = 80U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_18 = 81U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_19 = 82U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_20 = 83U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_21 = 84U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_22 = 85U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_23 = 86U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_24 = 87U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_25 = 88U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_26 = 89U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_27 = 90U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_28 = 91U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_29 = 92U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_30 = 93U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_31 = 94U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_32 = 95U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_33 = 96U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_34 = 97U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_35 = 98U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_00 = 99U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_01 = 100U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_02 = 101U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_03 = 102U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_04 = 103U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_05 = 104U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_00 = 105U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_01 = 106U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_02 = 107U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_03 = 108U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_04 = 109U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_05 = 110U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_06 = 111U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_07 = 112U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_08 = 113U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_09 = 114U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_10 = 115U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B2_11 = 116U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_00 = 117U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_01 = 118U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_02 = 119U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_03 = 120U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_04 = 121U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_05 = 122U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_06 = 123U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_07 = 124U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_08 = 125U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_09 = 126U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_10 = 127U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B1_11 = 128U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_00 = 129U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_01 = 130U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_02 = 131U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_03 = 132U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_04 = 133U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_05 = 134U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_06 = 135U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_07 = 136U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_08 = 137U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_09 = 138U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_10 = 139U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_11 = 140U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_12 = 141U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_13 = 142U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_14 = 143U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO_DISP_B2_15 = 144U, /**< IOMUXC SW_MUX_CTL_PAD index */
} iomuxc_sw_mux_ctl_pad_t;

/* @} */
#endif /* IOMUXC_SW_MUX_CTL_PAD_T_ */

#if !defined(IOMUXC_SW_PAD_CTL_PAD_T_)
#define IOMUXC_SW_PAD_CTL_PAD_T_
/*!
 * @addtogroup iomuxc_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC SW_PAD_CTL_PAD
 *
 * Defines the enumeration for the IOMUXC SW_PAD_CTL_PAD collections.
 */
typedef enum _iomuxc_sw_pad_ctl_pad
{
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_00 = 0U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_01 = 1U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_02 = 2U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_03 = 3U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_04 = 4U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_05 = 5U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_06 = 6U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_07 = 7U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_08 = 8U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_09 = 9U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_10 = 10U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_11 = 11U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_12 = 12U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_13 = 13U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_14 = 14U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_15 = 15U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_16 = 16U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_17 = 17U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_18 = 18U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_19 = 19U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_20 = 20U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_21 = 21U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_22 = 22U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_23 = 23U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_24 = 24U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_25 = 25U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_26 = 26U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_27 = 27U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_28 = 28U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_29 = 29U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_30 = 30U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_31 = 31U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_32 = 32U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_33 = 33U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_34 = 34U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_35 = 35U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_36 = 36U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_37 = 37U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_38 = 38U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_39 = 39U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_40 = 40U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B1_41 = 41U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_00 = 42U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_01 = 43U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_02 = 44U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_03 = 45U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_04 = 46U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_05 = 47U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_06 = 48U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_07 = 49U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_08 = 50U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_09 = 51U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_10 = 52U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_11 = 53U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_12 = 54U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_13 = 55U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_14 = 56U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_15 = 57U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_16 = 58U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_17 = 59U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_18 = 60U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_19 = 61U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_B2_20 = 62U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_00 = 63U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_01 = 64U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_02 = 65U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_03 = 66U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_04 = 67U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_05 = 68U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_06 = 69U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_07 = 70U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_08 = 71U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_09 = 72U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_10 = 73U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_11 = 74U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_12 = 75U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_13 = 76U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_14 = 77U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_15 = 78U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_16 = 79U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_17 = 80U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_18 = 81U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_19 = 82U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_20 = 83U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_21 = 84U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_22 = 85U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_23 = 86U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_24 = 87U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_25 = 88U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_26 = 89U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_27 = 90U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_28 = 91U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_29 = 92U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_30 = 93U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_31 = 94U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_32 = 95U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_33 = 96U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_34 = 97U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_35 = 98U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_00 = 99U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_01 = 100U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_02 = 101U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_03 = 102U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_04 = 103U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_05 = 104U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_00 = 105U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_01 = 106U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_02 = 107U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_03 = 108U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_04 = 109U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_05 = 110U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_06 = 111U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_07 = 112U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_08 = 113U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_09 = 114U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_10 = 115U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B2_11 = 116U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_00 = 117U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_01 = 118U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_02 = 119U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_03 = 120U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_04 = 121U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_05 = 122U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_06 = 123U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_07 = 124U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_08 = 125U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_09 = 126U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_10 = 127U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B1_11 = 128U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_00 = 129U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_01 = 130U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_02 = 131U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_03 = 132U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_04 = 133U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_05 = 134U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_06 = 135U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_07 = 136U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_08 = 137U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_09 = 138U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_10 = 139U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_11 = 140U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_12 = 141U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_13 = 142U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_14 = 143U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO_DISP_B2_15 = 144U, /**< IOMUXC SW_PAD_CTL_PAD index */
} iomuxc_sw_pad_ctl_pad_t;

/* @} */
#endif /* IOMUXC_SW_PAD_CTL_PAD_T_ */

#if !defined(IOMUXC_SELECT_INPUT_T_)
#define IOMUXC_SELECT_INPUT_T_
/*!
 * @brief Enumeration for the IOMUXC select input
 *
 * Defines the enumeration for the IOMUXC select input collections.
 */
typedef enum _iomuxc_select_input
{
    kIOMUXC_FLEXCAN1_RX_SELECT_INPUT = 0U,         /**< IOMUXC select input index */
    kIOMUXC_FLEXCAN2_RX_SELECT_INPUT = 1U,         /**< IOMUXC select input index */
    kIOMUXC_CCM_ENET_QOS_REF_CLK_SELECT_INPUT = 2U, /**< IOMUXC select input index */
    kIOMUXC_CCM_ENET_QOS_TX_CLK_SELECT_INPUT = 3U, /**< IOMUXC select input index */
    kIOMUXC_ENET_IPG_CLK_RMII_SELECT_INPUT = 4U,   /**< IOMUXC select input index */
    kIOMUXC_ENET_MAC0_MDIO_SELECT_INPUT = 5U,      /**< IOMUXC select input index */
    kIOMUXC_ENET_MAC0_RXDATA_SELECT_INPUT_0 = 6U,  /**< IOMUXC select input index */
    kIOMUXC_ENET_MAC0_RXDATA_SELECT_INPUT_1 = 7U,  /**< IOMUXC select input index */
    kIOMUXC_ENET_MAC0_RXEN_SELECT_INPUT = 8U,      /**< IOMUXC select input index */
    kIOMUXC_ENET_MAC0_RXERR_SELECT_INPUT = 9U,     /**< IOMUXC select input index */
    kIOMUXC_ENET_MAC0_TXCLK_SELECT_INPUT = 10U,    /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_IPG_CLK_RMII_SELECT_INPUT = 11U, /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_MDIO_SELECT_INPUT = 12U,  /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_RXCLK_SELECT_INPUT = 13U, /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_RXDATA_0_SELECT_INPUT = 14U, /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_RXDATA_1_SELECT_INPUT = 15U, /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_RXDATA_2_SELECT_INPUT = 16U, /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_RXDATA_3_SELECT_INPUT = 17U, /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_RXEN_SELECT_INPUT = 18U,  /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_RXERR_SELECT_INPUT = 19U, /**< IOMUXC select input index */
    kIOMUXC_ENET_1G_MAC0_TXCLK_SELECT_INPUT = 20U, /**< IOMUXC select input index */
    kIOMUXC_ENET_QOS_GMII_MDI_I_SELECT_INPUT = 21U, /**< IOMUXC select input index */
    kIOMUXC_ENET_QOS_PHY_RXD_I_SELECT_INPUT_0 = 22U, /**< IOMUXC select input index */
    kIOMUXC_ENET_QOS_PHY_RXD_I_SELECT_INPUT_1 = 23U, /**< IOMUXC select input index */
    kIOMUXC_ENET_QOS_PHY_RXDV_I_SELECT_INPUT = 24U, /**< IOMUXC select input index */
    kIOMUXC_ENET_QOS_PHY_RXER_I_SELECT_INPUT = 25U, /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM1_PWMA_SELECT_INPUT_0 = 26U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM1_PWMA_SELECT_INPUT_1 = 27U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM1_PWMA_SELECT_INPUT_2 = 28U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM1_PWMB_SELECT_INPUT_0 = 29U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM1_PWMB_SELECT_INPUT_1 = 30U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM1_PWMB_SELECT_INPUT_2 = 31U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM2_PWMA_SELECT_INPUT_0 = 32U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM2_PWMA_SELECT_INPUT_1 = 33U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM2_PWMA_SELECT_INPUT_2 = 34U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM2_PWMB_SELECT_INPUT_0 = 35U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM2_PWMB_SELECT_INPUT_1 = 36U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM2_PWMB_SELECT_INPUT_2 = 37U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM3_PWMA_SELECT_INPUT_0 = 38U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM3_PWMA_SELECT_INPUT_1 = 39U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM3_PWMA_SELECT_INPUT_2 = 40U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM3_PWMA_SELECT_INPUT_3 = 41U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM3_PWMB_SELECT_INPUT_0 = 42U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM3_PWMB_SELECT_INPUT_1 = 43U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM3_PWMB_SELECT_INPUT_2 = 44U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXPWM3_PWMB_SELECT_INPUT_3 = 45U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_DQS_FA_SELECT_INPUT = 46U,  /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_IO_FA_SELECT_INPUT_0 = 47U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_IO_FA_SELECT_INPUT_1 = 48U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_IO_FA_SELECT_INPUT_2 = 49U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_IO_FA_SELECT_INPUT_3 = 50U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_IO_FB_SELECT_INPUT_0 = 51U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_IO_FB_SELECT_INPUT_1 = 52U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_IO_FB_SELECT_INPUT_2 = 53U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_IO_FB_SELECT_INPUT_3 = 54U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_SCK_FA_SELECT_INPUT = 55U,  /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI1_I_SCK_FB_SELECT_INPUT = 56U,  /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI2_I_IO_FA_SELECT_INPUT_0 = 57U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI2_I_IO_FA_SELECT_INPUT_1 = 58U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI2_I_IO_FA_SELECT_INPUT_2 = 59U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI2_I_IO_FA_SELECT_INPUT_3 = 60U, /**< IOMUXC select input index */
    kIOMUXC_FLEXSPI2_I_SCK_FA_SELECT_INPUT = 61U,  /**< IOMUXC select input index */
    kIOMUXC_GPT3_CAPIN1_SELECT_INPUT = 62U,        /**< IOMUXC select input index */
    kIOMUXC_GPT3_CAPIN2_SELECT_INPUT = 63U,        /**< IOMUXC select input index */
    kIOMUXC_GPT3_CLKIN_SELECT_INPUT = 64U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_COL_SELECT_INPUT_6  = 65U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_COL_SELECT_INPUT_7  = 66U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_ROW_SELECT_INPUT_6  = 67U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_ROW_SELECT_INPUT_7  = 68U,         /**< IOMUXC select input index */
    kIOMUXC_LPI2C1_LPI2C_SCL_SELECT_INPUT = 69U,   /**< IOMUXC select input index */
    kIOMUXC_LPI2C1_LPI2C_SDA_SELECT_INPUT = 70U,   /**< IOMUXC select input index */
    kIOMUXC_LPI2C2_LPI2C_SCL_SELECT_INPUT = 71U,   /**< IOMUXC select input index */
    kIOMUXC_LPI2C2_LPI2C_SDA_SELECT_INPUT = 72U,   /**< IOMUXC select input index */
    kIOMUXC_LPI2C3_LPI2C_SCL_SELECT_INPUT = 73U,   /**< IOMUXC select input index */
    kIOMUXC_LPI2C3_LPI2C_SDA_SELECT_INPUT = 74U,   /**< IOMUXC select input index */
    kIOMUXC_LPI2C4_LPI2C_SCL_SELECT_INPUT = 75U,   /**< IOMUXC select input index */
    kIOMUXC_LPI2C4_LPI2C_SDA_SELECT_INPUT = 76U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI1_LPSPI_PCS_SELECT_INPUT_0 = 77U, /**< IOMUXC select input index */
    kIOMUXC_LPSPI1_LPSPI_SCK_SELECT_INPUT = 78U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI1_LPSPI_SDI_SELECT_INPUT = 79U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI1_LPSPI_SDO_SELECT_INPUT = 80U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI2_LPSPI_PCS_SELECT_INPUT_0 = 81U, /**< IOMUXC select input index */
    kIOMUXC_LPSPI2_LPSPI_PCS_SELECT_INPUT_1 = 82U, /**< IOMUXC select input index */
    kIOMUXC_LPSPI2_LPSPI_SCK_SELECT_INPUT = 83U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI2_LPSPI_SDI_SELECT_INPUT = 84U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI2_LPSPI_SDO_SELECT_INPUT = 85U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI3_LPSPI_PCS_SELECT_INPUT_0 = 86U, /**< IOMUXC select input index */
    kIOMUXC_LPSPI3_LPSPI_PCS_SELECT_INPUT_1 = 87U, /**< IOMUXC select input index */
    kIOMUXC_LPSPI3_LPSPI_PCS_SELECT_INPUT_2 = 88U, /**< IOMUXC select input index */
    kIOMUXC_LPSPI3_LPSPI_PCS_SELECT_INPUT_3 = 89U, /**< IOMUXC select input index */
    kIOMUXC_LPSPI3_LPSPI_SCK_SELECT_INPUT = 90U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI3_LPSPI_SDI_SELECT_INPUT = 91U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI3_LPSPI_SDO_SELECT_INPUT = 92U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI4_LPSPI_PCS_SELECT_INPUT_0 = 93U, /**< IOMUXC select input index */
    kIOMUXC_LPSPI4_LPSPI_SCK_SELECT_INPUT = 94U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI4_LPSPI_SDI_SELECT_INPUT = 95U,   /**< IOMUXC select input index */
    kIOMUXC_LPSPI4_LPSPI_SDO_SELECT_INPUT = 96U,   /**< IOMUXC select input index */
    kIOMUXC_LPUART1_LPUART_RXD_SELECT_INPUT = 97U, /**< IOMUXC select input index */
    kIOMUXC_LPUART1_LPUART_TXD_SELECT_INPUT = 98U, /**< IOMUXC select input index */
    kIOMUXC_LPUART10_LPUART_RXD_SELECT_INPUT = 99U, /**< IOMUXC select input index */
    kIOMUXC_LPUART10_LPUART_TXD_SELECT_INPUT = 100U, /**< IOMUXC select input index */
    kIOMUXC_LPUART7_LPUART_RXD_SELECT_INPUT = 101U, /**< IOMUXC select input index */
    kIOMUXC_LPUART7_LPUART_TXD_SELECT_INPUT = 102U, /**< IOMUXC select input index */
    kIOMUXC_LPUART8_LPUART_RXD_SELECT_INPUT = 103U, /**< IOMUXC select input index */
    kIOMUXC_LPUART8_LPUART_TXD_SELECT_INPUT = 104U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER1_TMR0_INPUT_SELECT_INPUT = 105U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER1_TMR1_INPUT_SELECT_INPUT = 106U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER1_TMR2_INPUT_SELECT_INPUT = 107U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER2_TMR0_INPUT_SELECT_INPUT = 108U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER2_TMR1_INPUT_SELECT_INPUT = 109U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER2_TMR2_INPUT_SELECT_INPUT = 110U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER3_TMR0_INPUT_SELECT_INPUT = 111U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER3_TMR1_INPUT_SELECT_INPUT = 112U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER3_TMR2_INPUT_SELECT_INPUT = 113U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER4_TMR0_INPUT_SELECT_INPUT = 114U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER4_TMR1_INPUT_SELECT_INPUT = 115U, /**< IOMUXC select input index */
    kIOMUXC_QTIMER4_TMR2_INPUT_SELECT_INPUT = 116U, /**< IOMUXC select input index */
    kIOMUXC_SAI1_IPG_CLK_SAI_MCLK_SELECT_INPUT = 117U, /**< IOMUXC select input index */
    kIOMUXC_SAI1_SAI_RXBCLK_SELECT_INPUT = 118U,   /**< IOMUXC select input index */
    kIOMUXC_SAI1_SAI_RXDATA_SELECT_INPUT_0 = 119U, /**< IOMUXC select input index */
    kIOMUXC_SAI1_SAI_RXSYNC_SELECT_INPUT = 120U,   /**< IOMUXC select input index */
    kIOMUXC_SAI1_SAI_TXBCLK_SELECT_INPUT = 121U,   /**< IOMUXC select input index */
    kIOMUXC_SAI1_SAI_TXSYNC_SELECT_INPUT = 122U,   /**< IOMUXC select input index */
    kIOMUXC_EMVSIM1_SIO_SELECT_INPUT = 129U,       /**< IOMUXC select input index */
    kIOMUXC_EMVSIM1_IPP_SIMPD_SELECT_INPUT = 130U, /**< IOMUXC select input index */
    kIOMUXC_EMVSIM1_POWER_FAIL_SELECT_INPUT = 131U, /**< IOMUXC select input index */
    kIOMUXC_EMVSIM2_SIO_SELECT_INPUT = 132U,       /**< IOMUXC select input index */
    kIOMUXC_EMVSIM2_IPP_SIMPD_SELECT_INPUT = 133U, /**< IOMUXC select input index */
    kIOMUXC_EMVSIM2_POWER_FAIL_SELECT_INPUT = 134U, /**< IOMUXC select input index */
    kIOMUXC_SPDIF_SPDIF_IN1_SELECT_INPUT = 135U,   /**< IOMUXC select input index */
    kIOMUXC_USB_OTG2_OC_SELECT_INPUT = 136U,       /**< IOMUXC select input index */
    kIOMUXC_USB_OTG_OC_SELECT_INPUT = 137U,        /**< IOMUXC select input index */
    kIOMUXC_USBPHY1_USB_ID_SELECT_INPUT = 138U,    /**< IOMUXC select input index */
    kIOMUXC_USBPHY2_USB_ID_SELECT_INPUT = 139U,    /**< IOMUXC select input index */
    kIOMUXC_USDHC1_IPP_CARD_DET_SELECT_INPUT = 140U, /**< IOMUXC select input index */
    kIOMUXC_USDHC1_IPP_WP_ON_SELECT_INPUT = 141U,  /**< IOMUXC select input index */
    kIOMUXC_USDHC2_IPP_CARD_DET_SELECT_INPUT = 142U, /**< IOMUXC select input index */
    kIOMUXC_USDHC2_IPP_WP_ON_SELECT_INPUT = 143U,  /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_20 = 144U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_21 = 145U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_22 = 146U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_23 = 147U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_24 = 148U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_25 = 149U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_26 = 150U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_27 = 151U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_28 = 152U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_29 = 153U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_30 = 154U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_31 = 155U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_32 = 156U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_33 = 157U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_34 = 158U,       /**< IOMUXC select input index */
    kIOMUXC_XBAR1_IN_SELECT_INPUT_35 = 159U,       /**< IOMUXC select input index */
} iomuxc_select_input_t;
#endif /* IOMUXC_SELECT_INPUT_T_ */


/*!
 * @}
 */ /* end of group Mapping_Information */


/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- IOMUXC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_Peripheral_Access_Layer IOMUXC Peripheral Access Layer
 * @{
 */

/** IOMUXC - Size of Registers Arrays */
#define IOMUXC_SW_MUX_CTL_PAD_COUNT               145u
#define IOMUXC_SW_PAD_CTL_PAD_COUNT               145u
#define IOMUXC_SELECT_INPUT_COUNT                 160u

/** IOMUXC - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[16];
  __IO uint32_t SW_MUX_CTL_PAD[IOMUXC_SW_MUX_CTL_PAD_COUNT]; /**< SW_MUX_CTL_PAD_GPIO_EMC_B1_00 SW MUX Control Register..SW_MUX_CTL_PAD_GPIO_DISP_B2_15 SW MUX Control Register, array offset: 0x10, array step: 0x4 */
  __IO uint32_t SW_PAD_CTL_PAD[IOMUXC_SW_PAD_CTL_PAD_COUNT]; /**< SW_PAD_CTL_PAD_GPIO_EMC_B1_00 SW PAD Control Register..SW_PAD_CTL_PAD_GPIO_DISP_B2_15 SW PAD Control Register, array offset: 0x254, array step: 0x4 */
  __IO uint32_t SELECT_INPUT[IOMUXC_SELECT_INPUT_COUNT]; /**< FLEXCAN1_RX_SELECT_INPUT DAISY Register..XBAR1_IN_SELECT_INPUT_35 DAISY Register, array offset: 0x498, array step: 0x4, valid indices: [0-122, 129-159] */
} IOMUXC_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_Register_Masks IOMUXC Register Masks
 * @{
 */

/*! @name SW_MUX_CTL_PAD - SW_MUX_CTL_PAD_GPIO_EMC_B1_00 SW MUX Control Register..SW_MUX_CTL_PAD_GPIO_DISP_B2_15 SW MUX Control Register */
/*! @{ */

#define IOMUXC_SW_MUX_CTL_PAD_MUX_MODE_MASK      (0xFU)
#define IOMUXC_SW_MUX_CTL_PAD_MUX_MODE_SHIFT     (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b0000..Select mux mode: ALT0 mux port: SEMC_DATA16 of instance: SEMC
 *  0b0001..Select mux mode: ALT1 mux port: CCM_ENET_REF_CLK_25M of instance: CCM
 *  0b0010..Select mux mode: ALT2 mux port: TMR3_TIMER1 of instance: TMR3
 *  0b0011..Select mux mode: ALT3 mux port: LPUART6_CTS_B of instance: LPUART6
 *  0b0100..Select mux mode: ALT4 mux port: FLEXSPI2_B_DATA06 of instance: FLEXSPI2
 *  0b0101..Select mux mode: ALT5 mux port: GPIO_MUX2_IO10 of instance: GPIO_MUX2
 *  0b0110..Select mux mode: ALT6 mux port: XBAR1_INOUT20 of instance: XBAR1
 *  0b0111..Select mux mode: ALT7 mux port: ENET_QOS_1588_EVENT1_OUT of instance: ENET_QOS
 *  0b1000..Select mux mode: ALT8 mux port: LPSPI1_SCK of instance: LPSPI1
 *  0b1001..Select mux mode: ALT9 mux port: LPI2C2_SCL of instance: LPI2C2
 *  0b1010..Select mux mode: ALT10 mux port: GPIO8_IO10 of instance: GPIO8
 *  0b1011..Select mux mode: ALT11 mux port: FLEXPWM3_PWM0_A of instance: FLEXPWM3
 */
#define IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_MUX_CTL_PAD_MUX_MODE_SHIFT)) & IOMUXC_SW_MUX_CTL_PAD_MUX_MODE_MASK)

#define IOMUXC_SW_MUX_CTL_PAD_SION_MASK          (0x10U)
#define IOMUXC_SW_MUX_CTL_PAD_SION_SHIFT         (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_DISP_B1_00
 */
#define IOMUXC_SW_MUX_CTL_PAD_SION(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_MUX_CTL_PAD_SION_SHIFT)) & IOMUXC_SW_MUX_CTL_PAD_SION_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD - SW_PAD_CTL_PAD_GPIO_EMC_B1_00 SW PAD Control Register..SW_PAD_CTL_PAD_GPIO_DISP_B2_15 SW PAD Control Register */
/*! @{ */

#define IOMUXC_SW_PAD_CTL_PAD_SRE_MASK           (0x1U)
#define IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT          (0U)
/*! SRE - Slew Rate Field
 *  0b0..Fast Slew Rate
 *  0b1..Slow Slew Rate
 */
#define IOMUXC_SW_PAD_CTL_PAD_SRE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_SRE_MASK)

#define IOMUXC_SW_PAD_CTL_PAD_DSE_MASK           (0x2U)
#define IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT          (1U)
/*! DSE - Drive Strength Field
 *  0b0..normal drive strength
 *  0b1..high drive strength
 */
#define IOMUXC_SW_PAD_CTL_PAD_DSE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DSE_MASK)

#define IOMUXC_SW_PAD_CTL_PAD_PDRV_MASK          (0x2U)
#define IOMUXC_SW_PAD_CTL_PAD_PDRV_SHIFT         (1U)
/*! PDRV - PDRV Field
 *  0b0..high drive strength
 *  0b1..normal drive strength
 */
#define IOMUXC_SW_PAD_CTL_PAD_PDRV(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_PDRV_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_PDRV_MASK)

#define IOMUXC_SW_PAD_CTL_PAD_PUE_MASK           (0x4U)
#define IOMUXC_SW_PAD_CTL_PAD_PUE_SHIFT          (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SW_PAD_CTL_PAD_PUE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_PUE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_PUE_MASK)

#define IOMUXC_SW_PAD_CTL_PAD_PULL_MASK          (0xCU)
#define IOMUXC_SW_PAD_CTL_PAD_PULL_SHIFT         (2U)
/*! PULL - Pull Down Pull Up Field
 *  0b00..Forbidden
 *  0b01..Internal pullup resistor enabled
 *  0b10..Internal pulldown resistor enabled
 *  0b11..No Pull
 */
#define IOMUXC_SW_PAD_CTL_PAD_PULL(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_PULL_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_PULL_MASK)

#define IOMUXC_SW_PAD_CTL_PAD_PUS_MASK           (0x8U)
#define IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT          (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SW_PAD_CTL_PAD_PUS(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_PUS_MASK)

#define IOMUXC_SW_PAD_CTL_PAD_ODE_MASK           (0x10U)
#define IOMUXC_SW_PAD_CTL_PAD_ODE_SHIFT          (4U)
/*! ODE - Open Drain Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SW_PAD_CTL_PAD_ODE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_ODE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_ODE_MASK)

#define IOMUXC_SW_PAD_CTL_PAD_DWP_MASK           (0x30000000U)
#define IOMUXC_SW_PAD_CTL_PAD_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SW_PAD_CTL_PAD_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DWP_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DWP_MASK)

#define IOMUXC_SW_PAD_CTL_PAD_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_SW_PAD_CTL_PAD_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SW_PAD_CTL_PAD_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DWP_LOCK_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DWP_LOCK_MASK)
/*! @} */

/*! @name SELECT_INPUT - FLEXCAN1_RX_SELECT_INPUT DAISY Register..XBAR1_IN_SELECT_INPUT_35 DAISY Register */
/*! @{ */

#define IOMUXC_SELECT_INPUT_DAISY_MASK           (0x3U)  /* Merged from fields with different position or width, of widths (1, 2), largest definition used */
#define IOMUXC_SELECT_INPUT_DAISY_SHIFT          (0U)
/*! DAISY - Selecting Pads Involved in Daisy Chain.
 *  0b00..Selecting Pad: GPIO_EMC_B2_19 for Mode: ALT3
 *  0b01..Selecting Pad: GPIO_SD_B2_11 for Mode: ALT3
 *  0b10..Selecting Pad: GPIO_DISP_B1_11 for Mode: ALT2
 *  0b11..Selecting Pad: GPIO_DISP_B2_14 for Mode: ALT4
 */
#define IOMUXC_SELECT_INPUT_DAISY(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SELECT_INPUT_DAISY_SHIFT)) & IOMUXC_SELECT_INPUT_DAISY_MASK)  /* Merged from fields with different position or width, of widths (1, 2), largest definition used */
/*! @} */


/*!
 * @}
 */ /* end of group IOMUXC_Register_Masks */


/*!
 * @}
 */ /* end of group IOMUXC_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* PERI_IOMUXC_H_ */

