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
**         CMSIS Peripheral Access Layer for XRDC2
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
 * @file PERI_XRDC2.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for XRDC2
 *
 * CMSIS Peripheral Access Layer for XRDC2
 */

#if !defined(PERI_XRDC2_H_)
#define PERI_XRDC2_H_                            /**< Symbol preventing repeated inclusion */

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
   --
   ---------------------------------------------------------------------------- */

/* Extra XRDC2 definition */
#define XRDC2_MAKE_MEM(mrc, mrgd) (((mrc) << 5U) | (mrgd))
#define XRDC2_GET_MRC(mem) ((mem) >> 5U)
#define XRDC2_GET_MRGD(mem) ((mem) & 31U)
#define XRDC2_MAKE_PERIPH(pac, pdac) (((pac) << 8U) | (pdac))
#define XRDC2_GET_PAC(periph) ((periph) >> 8U)
#define XRDC2_GET_PDAC(periph) ((periph) & 255U)


/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
#if !defined(XRDC2_MASTER_T_)
#define XRDC2_MASTER_T_
/*!
 * @addtogroup xrdc2_mapping
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure for the XRDC2 mapping
 *
 * Defines the structure for the XRDC2 resource collections.
 */

typedef enum _xrdc2_master
{
    kXRDC2_Master_M7_AHB            = 0U,          /**< M7 AHB */
    kXRDC2_Master_M4_AHBC           = 0U,          /**< M4 AHBC */
    kXRDC2_Master_M7_AXI            = 1U,          /**< M7 AXI */
    kXRDC2_Master_M4_AHBS           = 1U,          /**< M4 AHBS */
    kXRDC2_Master_CAAM              = 2U,          /**< CAAM */
    kXRDC2_Master_M7_EDMA           = 4U,          /**< M7 EDMA */
    kXRDC2_Master_M4_EDMA           = 4U,          /**< M4 EDMA */
    kXRDC2_Master_ENET              = 5U,          /**< ENET */
    kXRDC2_Master_ENET_1G_RX        = 6U,          /**< ENET_1G_RX */
    kXRDC2_Master_ENET_1G_TX        = 7U,          /**< ENET_1G_TX */
    kXRDC2_Master_ENET_QOS          = 8U,          /**< ENET_QOS */
    kXRDC2_Master_GPU               = 9U,          /**< GPU */
    kXRDC2_Master_LCDIFV2           = 11U,         /**< LCDIFV2 */
    kXRDC2_Master_SSARC             = 14U,         /**< SSARC */
    kXRDC2_Master_USB               = 15U,         /**< USB */
    kXRDC2_Master_USDHC1            = 16U,         /**< USDHC1 */
    kXRDC2_Master_USDHC2            = 17U,         /**< USDHC2 */
    kXRDC2_Master_CSI               = 3U,          /**< CSI */
    kXRDC2_Master_LCDIF             = 10U,         /**< LCDIF */
    kXRDC2_Master_PXP               = 12U,         /**< PXP */
} xrdc2_master_t;
#endif /* XRDC2_MASTER_T_ */

#if !defined(XRDC2_MEM_T_)
#define XRDC2_MEM_T_
typedef enum _xrdc2_mem
{
    kXRDC2_Mem_CAAM_Region0         = XRDC2_MAKE_MEM(0, 0), /**< MRC0 Memory 0 */
    kXRDC2_Mem_CAAM_Region1         = XRDC2_MAKE_MEM(0, 1), /**< MRC0 Memory 1 */
    kXRDC2_Mem_CAAM_Region2         = XRDC2_MAKE_MEM(0, 2), /**< MRC0 Memory 2 */
    kXRDC2_Mem_CAAM_Region3         = XRDC2_MAKE_MEM(0, 3), /**< MRC0 Memory 3 */
    kXRDC2_Mem_CAAM_Region4         = XRDC2_MAKE_MEM(0, 4), /**< MRC0 Memory 4 */
    kXRDC2_Mem_CAAM_Region5         = XRDC2_MAKE_MEM(0, 5), /**< MRC0 Memory 5 */
    kXRDC2_Mem_CAAM_Region6         = XRDC2_MAKE_MEM(0, 6), /**< MRC0 Memory 6 */
    kXRDC2_Mem_CAAM_Region7         = XRDC2_MAKE_MEM(0, 7), /**< MRC0 Memory 7 */
    kXRDC2_Mem_CAAM_Region8         = XRDC2_MAKE_MEM(0, 8), /**< MRC0 Memory 8 */
    kXRDC2_Mem_CAAM_Region9         = XRDC2_MAKE_MEM(0, 9), /**< MRC0 Memory 9 */
    kXRDC2_Mem_CAAM_Region10        = XRDC2_MAKE_MEM(0, 10), /**< MRC0 Memory 10 */
    kXRDC2_Mem_CAAM_Region11        = XRDC2_MAKE_MEM(0, 11), /**< MRC0 Memory 11 */
    kXRDC2_Mem_CAAM_Region12        = XRDC2_MAKE_MEM(0, 12), /**< MRC0 Memory 12 */
    kXRDC2_Mem_CAAM_Region13        = XRDC2_MAKE_MEM(0, 13), /**< MRC0 Memory 13 */
    kXRDC2_Mem_CAAM_Region14        = XRDC2_MAKE_MEM(0, 14), /**< MRC0 Memory 14 */
    kXRDC2_Mem_CAAM_Region15        = XRDC2_MAKE_MEM(0, 15), /**< MRC0 Memory 15 */
    kXRDC2_Mem_FLEXSPI1_Region0     = XRDC2_MAKE_MEM(1, 0), /**< MRC1 Memory 0 */
    kXRDC2_Mem_FLEXSPI1_Region1     = XRDC2_MAKE_MEM(1, 1), /**< MRC1 Memory 1 */
    kXRDC2_Mem_FLEXSPI1_Region2     = XRDC2_MAKE_MEM(1, 2), /**< MRC1 Memory 2 */
    kXRDC2_Mem_FLEXSPI1_Region3     = XRDC2_MAKE_MEM(1, 3), /**< MRC1 Memory 3 */
    kXRDC2_Mem_FLEXSPI1_Region4     = XRDC2_MAKE_MEM(1, 4), /**< MRC1 Memory 4 */
    kXRDC2_Mem_FLEXSPI1_Region5     = XRDC2_MAKE_MEM(1, 5), /**< MRC1 Memory 5 */
    kXRDC2_Mem_FLEXSPI1_Region6     = XRDC2_MAKE_MEM(1, 6), /**< MRC1 Memory 6 */
    kXRDC2_Mem_FLEXSPI1_Region7     = XRDC2_MAKE_MEM(1, 7), /**< MRC1 Memory 7 */
    kXRDC2_Mem_FLEXSPI1_Region8     = XRDC2_MAKE_MEM(1, 8), /**< MRC1 Memory 8 */
    kXRDC2_Mem_FLEXSPI1_Region9     = XRDC2_MAKE_MEM(1, 9), /**< MRC1 Memory 9 */
    kXRDC2_Mem_FLEXSPI1_Region10    = XRDC2_MAKE_MEM(1, 10), /**< MRC1 Memory 10 */
    kXRDC2_Mem_FLEXSPI1_Region11    = XRDC2_MAKE_MEM(1, 11), /**< MRC1 Memory 11 */
    kXRDC2_Mem_FLEXSPI1_Region12    = XRDC2_MAKE_MEM(1, 12), /**< MRC1 Memory 12 */
    kXRDC2_Mem_FLEXSPI1_Region13    = XRDC2_MAKE_MEM(1, 13), /**< MRC1 Memory 13 */
    kXRDC2_Mem_FLEXSPI1_Region14    = XRDC2_MAKE_MEM(1, 14), /**< MRC1 Memory 14 */
    kXRDC2_Mem_FLEXSPI1_Region15    = XRDC2_MAKE_MEM(1, 15), /**< MRC1 Memory 15 */
    kXRDC2_Mem_FLEXSPI2_Region0     = XRDC2_MAKE_MEM(2, 0), /**< MRC2 Memory 0 */
    kXRDC2_Mem_FLEXSPI2_Region1     = XRDC2_MAKE_MEM(2, 1), /**< MRC2 Memory 1 */
    kXRDC2_Mem_FLEXSPI2_Region2     = XRDC2_MAKE_MEM(2, 2), /**< MRC2 Memory 2 */
    kXRDC2_Mem_FLEXSPI2_Region3     = XRDC2_MAKE_MEM(2, 3), /**< MRC2 Memory 3 */
    kXRDC2_Mem_FLEXSPI2_Region4     = XRDC2_MAKE_MEM(2, 4), /**< MRC2 Memory 4 */
    kXRDC2_Mem_FLEXSPI2_Region5     = XRDC2_MAKE_MEM(2, 5), /**< MRC2 Memory 5 */
    kXRDC2_Mem_FLEXSPI2_Region6     = XRDC2_MAKE_MEM(2, 6), /**< MRC2 Memory 6 */
    kXRDC2_Mem_FLEXSPI2_Region7     = XRDC2_MAKE_MEM(2, 7), /**< MRC2 Memory 7 */
    kXRDC2_Mem_FLEXSPI2_Region8     = XRDC2_MAKE_MEM(2, 8), /**< MRC2 Memory 8 */
    kXRDC2_Mem_FLEXSPI2_Region9     = XRDC2_MAKE_MEM(2, 9), /**< MRC2 Memory 9 */
    kXRDC2_Mem_FLEXSPI2_Region10    = XRDC2_MAKE_MEM(2, 10), /**< MRC2 Memory 10 */
    kXRDC2_Mem_FLEXSPI2_Region11    = XRDC2_MAKE_MEM(2, 11), /**< MRC2 Memory 11 */
    kXRDC2_Mem_FLEXSPI2_Region12    = XRDC2_MAKE_MEM(2, 12), /**< MRC2 Memory 12 */
    kXRDC2_Mem_FLEXSPI2_Region13    = XRDC2_MAKE_MEM(2, 13), /**< MRC2 Memory 13 */
    kXRDC2_Mem_FLEXSPI2_Region14    = XRDC2_MAKE_MEM(2, 14), /**< MRC2 Memory 14 */
    kXRDC2_Mem_FLEXSPI2_Region15    = XRDC2_MAKE_MEM(2, 15), /**< MRC2 Memory 15 */
    kXRDC2_Mem_M4LMEM_Region0       = XRDC2_MAKE_MEM(3, 0), /**< MRC3 Memory 0 */
    kXRDC2_Mem_M4LMEM_Region1       = XRDC2_MAKE_MEM(3, 1), /**< MRC3 Memory 1 */
    kXRDC2_Mem_M4LMEM_Region2       = XRDC2_MAKE_MEM(3, 2), /**< MRC3 Memory 2 */
    kXRDC2_Mem_M4LMEM_Region3       = XRDC2_MAKE_MEM(3, 3), /**< MRC3 Memory 3 */
    kXRDC2_Mem_M4LMEM_Region4       = XRDC2_MAKE_MEM(3, 4), /**< MRC3 Memory 4 */
    kXRDC2_Mem_M4LMEM_Region5       = XRDC2_MAKE_MEM(3, 5), /**< MRC3 Memory 5 */
    kXRDC2_Mem_M4LMEM_Region6       = XRDC2_MAKE_MEM(3, 6), /**< MRC3 Memory 6 */
    kXRDC2_Mem_M4LMEM_Region7       = XRDC2_MAKE_MEM(3, 7), /**< MRC3 Memory 7 */
    kXRDC2_Mem_M4LMEM_Region8       = XRDC2_MAKE_MEM(3, 8), /**< MRC3 Memory 8 */
    kXRDC2_Mem_M4LMEM_Region9       = XRDC2_MAKE_MEM(3, 9), /**< MRC3 Memory 9 */
    kXRDC2_Mem_M4LMEM_Region10      = XRDC2_MAKE_MEM(3, 10), /**< MRC3 Memory 10 */
    kXRDC2_Mem_M4LMEM_Region11      = XRDC2_MAKE_MEM(3, 11), /**< MRC3 Memory 11 */
    kXRDC2_Mem_M4LMEM_Region12      = XRDC2_MAKE_MEM(3, 12), /**< MRC3 Memory 12 */
    kXRDC2_Mem_M4LMEM_Region13      = XRDC2_MAKE_MEM(3, 13), /**< MRC3 Memory 13 */
    kXRDC2_Mem_M4LMEM_Region14      = XRDC2_MAKE_MEM(3, 14), /**< MRC3 Memory 14 */
    kXRDC2_Mem_M4LMEM_Region15      = XRDC2_MAKE_MEM(3, 15), /**< MRC3 Memory 15 */
    kXRDC2_Mem_M7OC_Region0         = XRDC2_MAKE_MEM(4, 0), /**< MRC4 Memory 0 */
    kXRDC2_Mem_M7OC_Region1         = XRDC2_MAKE_MEM(4, 1), /**< MRC4 Memory 1 */
    kXRDC2_Mem_M7OC_Region2         = XRDC2_MAKE_MEM(4, 2), /**< MRC4 Memory 2 */
    kXRDC2_Mem_M7OC_Region3         = XRDC2_MAKE_MEM(4, 3), /**< MRC4 Memory 3 */
    kXRDC2_Mem_M7OC_Region4         = XRDC2_MAKE_MEM(4, 4), /**< MRC4 Memory 4 */
    kXRDC2_Mem_M7OC_Region5         = XRDC2_MAKE_MEM(4, 5), /**< MRC4 Memory 5 */
    kXRDC2_Mem_M7OC_Region6         = XRDC2_MAKE_MEM(4, 6), /**< MRC4 Memory 6 */
    kXRDC2_Mem_M7OC_Region7         = XRDC2_MAKE_MEM(4, 7), /**< MRC4 Memory 7 */
    kXRDC2_Mem_M7OC_Region8         = XRDC2_MAKE_MEM(4, 8), /**< MRC4 Memory 8 */
    kXRDC2_Mem_M7OC_Region9         = XRDC2_MAKE_MEM(4, 9), /**< MRC4 Memory 9 */
    kXRDC2_Mem_M7OC_Region10        = XRDC2_MAKE_MEM(4, 10), /**< MRC4 Memory 10 */
    kXRDC2_Mem_M7OC_Region11        = XRDC2_MAKE_MEM(4, 11), /**< MRC4 Memory 11 */
    kXRDC2_Mem_M7OC_Region12        = XRDC2_MAKE_MEM(4, 12), /**< MRC4 Memory 12 */
    kXRDC2_Mem_M7OC_Region13        = XRDC2_MAKE_MEM(4, 13), /**< MRC4 Memory 13 */
    kXRDC2_Mem_M7OC_Region14        = XRDC2_MAKE_MEM(4, 14), /**< MRC4 Memory 14 */
    kXRDC2_Mem_M7OC_Region15        = XRDC2_MAKE_MEM(4, 15), /**< MRC4 Memory 15 */
    kXRDC2_Mem_MECC1_Region0        = XRDC2_MAKE_MEM(5, 0), /**< MRC5 Memory 0 */
    kXRDC2_Mem_MECC1_Region1        = XRDC2_MAKE_MEM(5, 1), /**< MRC5 Memory 1 */
    kXRDC2_Mem_MECC1_Region2        = XRDC2_MAKE_MEM(5, 2), /**< MRC5 Memory 2 */
    kXRDC2_Mem_MECC1_Region3        = XRDC2_MAKE_MEM(5, 3), /**< MRC5 Memory 3 */
    kXRDC2_Mem_MECC1_Region4        = XRDC2_MAKE_MEM(5, 4), /**< MRC5 Memory 4 */
    kXRDC2_Mem_MECC1_Region5        = XRDC2_MAKE_MEM(5, 5), /**< MRC5 Memory 5 */
    kXRDC2_Mem_MECC1_Region6        = XRDC2_MAKE_MEM(5, 6), /**< MRC5 Memory 6 */
    kXRDC2_Mem_MECC1_Region7        = XRDC2_MAKE_MEM(5, 7), /**< MRC5 Memory 7 */
    kXRDC2_Mem_MECC1_Region8        = XRDC2_MAKE_MEM(5, 8), /**< MRC5 Memory 8 */
    kXRDC2_Mem_MECC1_Region9        = XRDC2_MAKE_MEM(5, 9), /**< MRC5 Memory 9 */
    kXRDC2_Mem_MECC1_Region10       = XRDC2_MAKE_MEM(5, 10), /**< MRC5 Memory 10 */
    kXRDC2_Mem_MECC1_Region11       = XRDC2_MAKE_MEM(5, 11), /**< MRC5 Memory 11 */
    kXRDC2_Mem_MECC1_Region12       = XRDC2_MAKE_MEM(5, 12), /**< MRC5 Memory 12 */
    kXRDC2_Mem_MECC1_Region13       = XRDC2_MAKE_MEM(5, 13), /**< MRC5 Memory 13 */
    kXRDC2_Mem_MECC1_Region14       = XRDC2_MAKE_MEM(5, 14), /**< MRC5 Memory 14 */
    kXRDC2_Mem_MECC1_Region15       = XRDC2_MAKE_MEM(5, 15), /**< MRC5 Memory 15 */
    kXRDC2_Mem_MECC2_Region0        = XRDC2_MAKE_MEM(6, 0), /**< MRC6 Memory 0 */
    kXRDC2_Mem_MECC2_Region1        = XRDC2_MAKE_MEM(6, 1), /**< MRC6 Memory 1 */
    kXRDC2_Mem_MECC2_Region2        = XRDC2_MAKE_MEM(6, 2), /**< MRC6 Memory 2 */
    kXRDC2_Mem_MECC2_Region3        = XRDC2_MAKE_MEM(6, 3), /**< MRC6 Memory 3 */
    kXRDC2_Mem_MECC2_Region4        = XRDC2_MAKE_MEM(6, 4), /**< MRC6 Memory 4 */
    kXRDC2_Mem_MECC2_Region5        = XRDC2_MAKE_MEM(6, 5), /**< MRC6 Memory 5 */
    kXRDC2_Mem_MECC2_Region6        = XRDC2_MAKE_MEM(6, 6), /**< MRC6 Memory 6 */
    kXRDC2_Mem_MECC2_Region7        = XRDC2_MAKE_MEM(6, 7), /**< MRC6 Memory 7 */
    kXRDC2_Mem_MECC2_Region8        = XRDC2_MAKE_MEM(6, 8), /**< MRC6 Memory 8 */
    kXRDC2_Mem_MECC2_Region9        = XRDC2_MAKE_MEM(6, 9), /**< MRC6 Memory 9 */
    kXRDC2_Mem_MECC2_Region10       = XRDC2_MAKE_MEM(6, 10), /**< MRC6 Memory 10 */
    kXRDC2_Mem_MECC2_Region11       = XRDC2_MAKE_MEM(6, 11), /**< MRC6 Memory 11 */
    kXRDC2_Mem_MECC2_Region12       = XRDC2_MAKE_MEM(6, 12), /**< MRC6 Memory 12 */
    kXRDC2_Mem_MECC2_Region13       = XRDC2_MAKE_MEM(6, 13), /**< MRC6 Memory 13 */
    kXRDC2_Mem_MECC2_Region14       = XRDC2_MAKE_MEM(6, 14), /**< MRC6 Memory 14 */
    kXRDC2_Mem_MECC2_Region15       = XRDC2_MAKE_MEM(6, 15), /**< MRC6 Memory 15 */
    kXRDC2_Mem_SEMC_Region0         = XRDC2_MAKE_MEM(7, 0), /**< MRC7 Memory 0 */
    kXRDC2_Mem_SEMC_Region1         = XRDC2_MAKE_MEM(7, 1), /**< MRC7 Memory 1 */
    kXRDC2_Mem_SEMC_Region2         = XRDC2_MAKE_MEM(7, 2), /**< MRC7 Memory 2 */
    kXRDC2_Mem_SEMC_Region3         = XRDC2_MAKE_MEM(7, 3), /**< MRC7 Memory 3 */
    kXRDC2_Mem_SEMC_Region4         = XRDC2_MAKE_MEM(7, 4), /**< MRC7 Memory 4 */
    kXRDC2_Mem_SEMC_Region5         = XRDC2_MAKE_MEM(7, 5), /**< MRC7 Memory 5 */
    kXRDC2_Mem_SEMC_Region6         = XRDC2_MAKE_MEM(7, 6), /**< MRC7 Memory 6 */
    kXRDC2_Mem_SEMC_Region7         = XRDC2_MAKE_MEM(7, 7), /**< MRC7 Memory 7 */
    kXRDC2_Mem_SEMC_Region8         = XRDC2_MAKE_MEM(7, 8), /**< MRC7 Memory 8 */
    kXRDC2_Mem_SEMC_Region9         = XRDC2_MAKE_MEM(7, 9), /**< MRC7 Memory 9 */
    kXRDC2_Mem_SEMC_Region10        = XRDC2_MAKE_MEM(7, 10), /**< MRC7 Memory 10 */
    kXRDC2_Mem_SEMC_Region11        = XRDC2_MAKE_MEM(7, 11), /**< MRC7 Memory 11 */
    kXRDC2_Mem_SEMC_Region12        = XRDC2_MAKE_MEM(7, 12), /**< MRC7 Memory 12 */
    kXRDC2_Mem_SEMC_Region13        = XRDC2_MAKE_MEM(7, 13), /**< MRC7 Memory 13 */
    kXRDC2_Mem_SEMC_Region14        = XRDC2_MAKE_MEM(7, 14), /**< MRC7 Memory 14 */
    kXRDC2_Mem_SEMC_Region15        = XRDC2_MAKE_MEM(7, 15), /**< MRC7 Memory 15 */
} xrdc2_mem_t;
#endif /* XRDC2_MEM_T_ */

#if !defined(XRDC2_MEM_SLOT_T_)
#define XRDC2_MEM_SLOT_T_
typedef enum _xrdc2_mem_slot
{
    kXRDC2_MemSlot_GPV0             = 0U,          /**< GPV0 */
    kXRDC2_MemSlot_GPV1             = 1U,          /**< GPV1 */
    kXRDC2_MemSlot_GPV2             = 2U,          /**< GPV2 */
    kXRDC2_MemSlot_ROMCP            = 3U,          /**< ROMCP */
} xrdc2_mem_slot_t;
#endif /* XRDC2_MEM_SLOT_T_ */

#if !defined(XRDC2_PERIPH_T_)
#define XRDC2_PERIPH_T_
typedef enum _xrdc2_periph
{
    kXRDC2_Periph_ACMP4             = XRDC2_MAKE_PERIPH(0, 108), /**< ACMP4 */
    kXRDC2_Periph_ACMP3             = XRDC2_MAKE_PERIPH(0, 107), /**< ACMP3 */
    kXRDC2_Periph_ACMP2             = XRDC2_MAKE_PERIPH(0, 106), /**< ACMP2 */
    kXRDC2_Periph_ACMP1             = XRDC2_MAKE_PERIPH(0, 105), /**< ACMP1 */
    kXRDC2_Periph_FLEXPWM4          = XRDC2_MAKE_PERIPH(0, 102), /**< FLEXPWM4 */
    kXRDC2_Periph_FLEXPWM3          = XRDC2_MAKE_PERIPH(0, 101), /**< FLEXPWM3 */
    kXRDC2_Periph_FLEXPWM2          = XRDC2_MAKE_PERIPH(0, 100), /**< FLEXPWM2 */
    kXRDC2_Periph_FLEXPWM1          = XRDC2_MAKE_PERIPH(0, 99 ), /**< FLEXPWM1 */
    kXRDC2_Periph_ENC4              = XRDC2_MAKE_PERIPH(0, 96 ), /**< ENC4 */
    kXRDC2_Periph_ENC3              = XRDC2_MAKE_PERIPH(0, 95 ), /**< ENC3 */
    kXRDC2_Periph_ENC2              = XRDC2_MAKE_PERIPH(0, 94 ), /**< ENC2 */
    kXRDC2_Periph_ENC1              = XRDC2_MAKE_PERIPH(0, 93 ), /**< ENC1 */
    kXRDC2_Periph_QTIMER4           = XRDC2_MAKE_PERIPH(0, 90 ), /**< QTIMER4 */
    kXRDC2_Periph_QTIMER3           = XRDC2_MAKE_PERIPH(0, 89 ), /**< QTIMER3 */
    kXRDC2_Periph_QTIMER2           = XRDC2_MAKE_PERIPH(0, 88 ), /**< QTIMER2 */
    kXRDC2_Periph_QTIMER1           = XRDC2_MAKE_PERIPH(0, 87 ), /**< QTIMER1 */
    kXRDC2_Periph_SIM2              = XRDC2_MAKE_PERIPH(0, 86 ), /**< SIM2 */
    kXRDC2_Periph_SIM1              = XRDC2_MAKE_PERIPH(0, 85 ), /**< SIM1 */
    kXRDC2_Periph_CCM_OBS           = XRDC2_MAKE_PERIPH(0, 84 ), /**< CCM_OBS */
    kXRDC2_Periph_GPIO6             = XRDC2_MAKE_PERIPH(0, 80 ), /**< GPIO6 */
    kXRDC2_Periph_GPIO5             = XRDC2_MAKE_PERIPH(0, 79 ), /**< GPIO5 */
    kXRDC2_Periph_GPIO4             = XRDC2_MAKE_PERIPH(0, 78 ), /**< GPIO4 */
    kXRDC2_Periph_GPIO3             = XRDC2_MAKE_PERIPH(0, 77 ), /**< GPIO3 */
    kXRDC2_Periph_GPIO2             = XRDC2_MAKE_PERIPH(0, 76 ), /**< GPIO2 */
    kXRDC2_Periph_GPIO1             = XRDC2_MAKE_PERIPH(0, 75 ), /**< GPIO1 */
    kXRDC2_Periph_LPSPI4            = XRDC2_MAKE_PERIPH(0, 72 ), /**< LPSPI4 */
    kXRDC2_Periph_LPSPI3            = XRDC2_MAKE_PERIPH(0, 71 ), /**< LPSPI3 */
    kXRDC2_Periph_LPSPI2            = XRDC2_MAKE_PERIPH(0, 70 ), /**< LPSPI2 */
    kXRDC2_Periph_LPSPI1            = XRDC2_MAKE_PERIPH(0, 69 ), /**< LPSPI1 */
    kXRDC2_Periph_LPI2C4            = XRDC2_MAKE_PERIPH(0, 68 ), /**< LPI2C4 */
    kXRDC2_Periph_LPI2C3            = XRDC2_MAKE_PERIPH(0, 67 ), /**< LPI2C3 */
    kXRDC2_Periph_LPI2C2            = XRDC2_MAKE_PERIPH(0, 66 ), /**< LPI2C2 */
    kXRDC2_Periph_LPI2C1            = XRDC2_MAKE_PERIPH(0, 65 ), /**< LPI2C1 */
    kXRDC2_Periph_GPT6              = XRDC2_MAKE_PERIPH(0, 64 ), /**< GPT6 */
    kXRDC2_Periph_GPT5              = XRDC2_MAKE_PERIPH(0, 63 ), /**< GPT5 */
    kXRDC2_Periph_GPT4              = XRDC2_MAKE_PERIPH(0, 62 ), /**< GPT4 */
    kXRDC2_Periph_GPT3              = XRDC2_MAKE_PERIPH(0, 61 ), /**< GPT3 */
    kXRDC2_Periph_GPT2              = XRDC2_MAKE_PERIPH(0, 60 ), /**< GPT2 */
    kXRDC2_Periph_GPT1              = XRDC2_MAKE_PERIPH(0, 59 ), /**< GPT1 */
    kXRDC2_Periph_IOMUXC            = XRDC2_MAKE_PERIPH(0, 58 ), /**< IOMUXC */
    kXRDC2_Periph_IOMUXC_GPR        = XRDC2_MAKE_PERIPH(0, 57 ), /**< IOMUXC_GPR */
    kXRDC2_Periph_KPP               = XRDC2_MAKE_PERIPH(0, 56 ), /**< KPP */
    kXRDC2_Periph_PIT1              = XRDC2_MAKE_PERIPH(0, 54 ), /**< PIT1 */
    kXRDC2_Periph_SEMC              = XRDC2_MAKE_PERIPH(0, 53 ), /**< SEMC */
    kXRDC2_Periph_FLEXSPI2          = XRDC2_MAKE_PERIPH(0, 52 ), /**< FLEXSPI2 */
    kXRDC2_Periph_FLEXSPI1          = XRDC2_MAKE_PERIPH(0, 51 ), /**< FLEXSPI1 */
    kXRDC2_Periph_CAN2              = XRDC2_MAKE_PERIPH(0, 50 ), /**< CAN2 */
    kXRDC2_Periph_CAN1              = XRDC2_MAKE_PERIPH(0, 49 ), /**< CAN1 */
    kXRDC2_Periph_AOI2              = XRDC2_MAKE_PERIPH(0, 47 ), /**< AOI2 */
    kXRDC2_Periph_AOI1              = XRDC2_MAKE_PERIPH(0, 46 ), /**< AOI1 */
    kXRDC2_Periph_FLEXIO2           = XRDC2_MAKE_PERIPH(0, 44 ), /**< FLEXIO2 */
    kXRDC2_Periph_FLEXIO1           = XRDC2_MAKE_PERIPH(0, 43 ), /**< FLEXIO1 */
    kXRDC2_Periph_LPUART10          = XRDC2_MAKE_PERIPH(0, 40 ), /**< LPUART10 */
    kXRDC2_Periph_LPUART9           = XRDC2_MAKE_PERIPH(0, 39 ), /**< LPUART9 */
    kXRDC2_Periph_LPUART8           = XRDC2_MAKE_PERIPH(0, 38 ), /**< LPUART8 */
    kXRDC2_Periph_LPUART7           = XRDC2_MAKE_PERIPH(0, 37 ), /**< LPUART7 */
    kXRDC2_Periph_LPUART6           = XRDC2_MAKE_PERIPH(0, 36 ), /**< LPUART6 */
    kXRDC2_Periph_LPUART5           = XRDC2_MAKE_PERIPH(0, 35 ), /**< LPUART5 */
    kXRDC2_Periph_LPUART4           = XRDC2_MAKE_PERIPH(0, 34 ), /**< LPUART4 */
    kXRDC2_Periph_LPUART3           = XRDC2_MAKE_PERIPH(0, 33 ), /**< LPUART3 */
    kXRDC2_Periph_LPUART2           = XRDC2_MAKE_PERIPH(0, 32 ), /**< LPUART2 */
    kXRDC2_Periph_LPUART1           = XRDC2_MAKE_PERIPH(0, 31 ), /**< LPUART1 */
    kXRDC2_Periph_DMA_CH_MUX        = XRDC2_MAKE_PERIPH(0, 29 ), /**< DMA_CH_MUX */
    kXRDC2_Periph_EDMA              = XRDC2_MAKE_PERIPH(0, 28 ), /**< EDMA */
    kXRDC2_Periph_IEE               = XRDC2_MAKE_PERIPH(0, 27 ), /**< IEE */
    kXRDC2_Periph_DAC               = XRDC2_MAKE_PERIPH(0, 25 ), /**< DAC */
    kXRDC2_Periph_TSC_DIG           = XRDC2_MAKE_PERIPH(0, 23 ), /**< TSC_DIG */
    kXRDC2_Periph_ADC2              = XRDC2_MAKE_PERIPH(0, 21 ), /**< ADC2 */
    kXRDC2_Periph_ADC1              = XRDC2_MAKE_PERIPH(0, 20 ), /**< ADC1 */
    kXRDC2_Periph_ADC_ETC           = XRDC2_MAKE_PERIPH(0, 18 ), /**< ADC_ETC */
    kXRDC2_Periph_XBAR3             = XRDC2_MAKE_PERIPH(0, 17 ), /**< XBAR3 */
    kXRDC2_Periph_XBAR2             = XRDC2_MAKE_PERIPH(0, 16 ), /**< XBAR2 */
    kXRDC2_Periph_XBAR1             = XRDC2_MAKE_PERIPH(0, 15 ), /**< XBAR1 */
    kXRDC2_Periph_WDOG3             = XRDC2_MAKE_PERIPH(0, 14 ), /**< WDOG3 */
    kXRDC2_Periph_WDOG2             = XRDC2_MAKE_PERIPH(0, 13 ), /**< WDOG2 */
    kXRDC2_Periph_WDOG1             = XRDC2_MAKE_PERIPH(0, 12 ), /**< WDOG1 */
    kXRDC2_Periph_EWM               = XRDC2_MAKE_PERIPH(0, 11 ), /**< EWM */
    kXRDC2_Periph_FLEXRAM           = XRDC2_MAKE_PERIPH(0, 10 ), /**< FLEXRAM */
    kXRDC2_Periph_XECC_SEMC         = XRDC2_MAKE_PERIPH(0, 9  ), /**< XECC_SEMC */
    kXRDC2_Periph_XECC_FLEXSPI2     = XRDC2_MAKE_PERIPH(0, 8  ), /**< XECC_FLEXSPI2 */
    kXRDC2_Periph_XECC_FLEXSPI1     = XRDC2_MAKE_PERIPH(0, 7  ), /**< XECC_FLEXSPI1 */
    kXRDC2_Periph_MECC2             = XRDC2_MAKE_PERIPH(0, 6  ), /**< MECC2 */
    kXRDC2_Periph_MECC1             = XRDC2_MAKE_PERIPH(0, 5  ), /**< MECC1 */
    kXRDC2_Periph_MTR               = XRDC2_MAKE_PERIPH(0, 4  ), /**< MTR */
    kXRDC2_Periph_SFA               = XRDC2_MAKE_PERIPH(0, 3  ), /**< SFA */
    kXRDC2_Periph_CAAM_DEBUG_3      = XRDC2_MAKE_PERIPH(1, 51 ), /**< CAAM_DEBUG_3 */
    kXRDC2_Periph_CAAM_DEBUG_2      = XRDC2_MAKE_PERIPH(1, 50 ), /**< CAAM_DEBUG_2 */
    kXRDC2_Periph_CAAM_DEBUG_1      = XRDC2_MAKE_PERIPH(1, 49 ), /**< CAAM_DEBUG_1 */
    kXRDC2_Periph_CAAM_DEBUG_0      = XRDC2_MAKE_PERIPH(1, 48 ), /**< CAAM_DEBUG_0 */
    kXRDC2_Periph_CAAM_RTIC_3       = XRDC2_MAKE_PERIPH(1, 43 ), /**< CAAM_RTIC_3 */
    kXRDC2_Periph_CAAM_RTIC_2       = XRDC2_MAKE_PERIPH(1, 42 ), /**< CAAM_RTIC_2 */
    kXRDC2_Periph_CAAM_RTIC_1       = XRDC2_MAKE_PERIPH(1, 41 ), /**< CAAM_RTIC_1 */
    kXRDC2_Periph_CAAM_RTIC_0       = XRDC2_MAKE_PERIPH(1, 40 ), /**< CAAM_RTIC_0 */
    kXRDC2_Periph_CAAM_JR3_3        = XRDC2_MAKE_PERIPH(1, 35 ), /**< CAAM_JR3_3 */
    kXRDC2_Periph_CAAM_JR3_2        = XRDC2_MAKE_PERIPH(1, 34 ), /**< CAAM_JR3_2 */
    kXRDC2_Periph_CAAM_JR3_1        = XRDC2_MAKE_PERIPH(1, 33 ), /**< CAAM_JR3_1 */
    kXRDC2_Periph_CAAM_JR3_0        = XRDC2_MAKE_PERIPH(1, 32 ), /**< CAAM_JR3_0 */
    kXRDC2_Periph_CAAM_JR2_3        = XRDC2_MAKE_PERIPH(1, 31 ), /**< CAAM_JR2_3 */
    kXRDC2_Periph_CAAM_JR2_2        = XRDC2_MAKE_PERIPH(1, 30 ), /**< CAAM_JR2_2 */
    kXRDC2_Periph_CAAM_JR2_1        = XRDC2_MAKE_PERIPH(1, 29 ), /**< CAAM_JR2_1 */
    kXRDC2_Periph_CAAM_JR2_0        = XRDC2_MAKE_PERIPH(1, 28 ), /**< CAAM_JR2_0 */
    kXRDC2_Periph_CAAM_JR1_3        = XRDC2_MAKE_PERIPH(1, 27 ), /**< CAAM_JR1_3 */
    kXRDC2_Periph_CAAM_JR1_2        = XRDC2_MAKE_PERIPH(1, 26 ), /**< CAAM_JR1_2 */
    kXRDC2_Periph_CAAM_JR1_1        = XRDC2_MAKE_PERIPH(1, 25 ), /**< CAAM_JR1_1 */
    kXRDC2_Periph_CAAM_JR1_0        = XRDC2_MAKE_PERIPH(1, 24 ), /**< CAAM_JR1_0 */
    kXRDC2_Periph_CAAM_JR0_3        = XRDC2_MAKE_PERIPH(1, 23 ), /**< CAAM_JR0_3 */
    kXRDC2_Periph_CAAM_JR0_2        = XRDC2_MAKE_PERIPH(1, 22 ), /**< CAAM_JR0_2 */
    kXRDC2_Periph_CAAM_JR0_1        = XRDC2_MAKE_PERIPH(1, 21 ), /**< CAAM_JR0_1 */
    kXRDC2_Periph_CAAM_JR0_0        = XRDC2_MAKE_PERIPH(1, 20 ), /**< CAAM_JR0_0 */
    kXRDC2_Periph_CAAM_GENERAL_3    = XRDC2_MAKE_PERIPH(1, 19 ), /**< CAAM_GENERAL_3 */
    kXRDC2_Periph_CAAM_GENERAL_2    = XRDC2_MAKE_PERIPH(1, 18 ), /**< CAAM_GENERAL_2 */
    kXRDC2_Periph_CAAM_GENERAL_1    = XRDC2_MAKE_PERIPH(1, 17 ), /**< CAAM_GENERAL_1 */
    kXRDC2_Periph_CAAM_GENERAL_0    = XRDC2_MAKE_PERIPH(1, 16 ), /**< CAAM_GENERAL_0 */
    kXRDC2_Periph_ENET_QOS          = XRDC2_MAKE_PERIPH(1, 15 ), /**< ENET_QOS */
    kXRDC2_Periph_USBPHY2           = XRDC2_MAKE_PERIPH(1, 14 ), /**< USBPHY2 */
    kXRDC2_Periph_USBPHY1           = XRDC2_MAKE_PERIPH(1, 13 ), /**< USBPHY1 */
    kXRDC2_Periph_USB_OTG           = XRDC2_MAKE_PERIPH(1, 12 ), /**< USB_OTG */
    kXRDC2_Periph_USB_OTG2          = XRDC2_MAKE_PERIPH(1, 11 ), /**< USB_OTG2 */
    kXRDC2_Periph_USB_PL301         = XRDC2_MAKE_PERIPH(1, 10 ), /**< USB_PL301 */
    kXRDC2_Periph_ENET              = XRDC2_MAKE_PERIPH(1, 9  ), /**< ENET */
    kXRDC2_Periph_ENET_1G           = XRDC2_MAKE_PERIPH(1, 8  ), /**< ENET_1G */
    kXRDC2_Periph_USDHC2            = XRDC2_MAKE_PERIPH(1, 7  ), /**< USDHC2 */
    kXRDC2_Periph_USDHC1            = XRDC2_MAKE_PERIPH(1, 6  ), /**< USDHC1 */
    kXRDC2_Periph_ASRC              = XRDC2_MAKE_PERIPH(1, 5  ), /**< ASRC */
    kXRDC2_Periph_SAI3              = XRDC2_MAKE_PERIPH(1, 3  ), /**< SAI3 */
    kXRDC2_Periph_SAI2              = XRDC2_MAKE_PERIPH(1, 2  ), /**< SAI2 */
    kXRDC2_Periph_SAI1              = XRDC2_MAKE_PERIPH(1, 1  ), /**< SAI1 */
    kXRDC2_Periph_SPDIF             = XRDC2_MAKE_PERIPH(1, 0  ), /**< SPDIF */
    kXRDC2_Periph_VIDEO_MUX         = XRDC2_MAKE_PERIPH(2, 6  ), /**< VIDEO_MUX */
    kXRDC2_Periph_MIPI_CSI          = XRDC2_MAKE_PERIPH(2, 4  ), /**< MIPI_CSI */
    kXRDC2_Periph_MIPI_DSI          = XRDC2_MAKE_PERIPH(2, 3  ), /**< MIPI_DSI */
    kXRDC2_Periph_LCDIFV2           = XRDC2_MAKE_PERIPH(2, 2  ), /**< LCDIFV2 */
    kXRDC2_Periph_XRDC2_MGR_M7_3    = XRDC2_MAKE_PERIPH(3, 59 ), /**< XRDC2_MGR_M7_3 */
    kXRDC2_Periph_XRDC2_MGR_M7_2    = XRDC2_MAKE_PERIPH(3, 58 ), /**< XRDC2_MGR_M7_2 */
    kXRDC2_Periph_XRDC2_MGR_M7_1    = XRDC2_MAKE_PERIPH(3, 57 ), /**< XRDC2_MGR_M7_1 */
    kXRDC2_Periph_XRDC2_MGR_M7_0    = XRDC2_MAKE_PERIPH(3, 56 ), /**< XRDC2_MGR_M7_0 */
    kXRDC2_Periph_XRDC2_MGR_M4_3    = XRDC2_MAKE_PERIPH(3, 55 ), /**< XRDC2_MGR_M4_3 */
    kXRDC2_Periph_XRDC2_MGR_M4_2    = XRDC2_MAKE_PERIPH(3, 54 ), /**< XRDC2_MGR_M4_2 */
    kXRDC2_Periph_XRDC2_MGR_M4_1    = XRDC2_MAKE_PERIPH(3, 53 ), /**< XRDC2_MGR_M4_1 */
    kXRDC2_Periph_XRDC2_MGR_M4_0    = XRDC2_MAKE_PERIPH(3, 52 ), /**< XRDC2_MGR_M4_0 */
    kXRDC2_Periph_SEMA2             = XRDC2_MAKE_PERIPH(3, 51 ), /**< SEMA2 */
    kXRDC2_Periph_SEMA_HS           = XRDC2_MAKE_PERIPH(3, 50 ), /**< SEMA_HS */
    kXRDC2_Periph_CCM_1             = XRDC2_MAKE_PERIPH(3, 49 ), /**< CCM_1 */
    kXRDC2_Periph_CCM_0             = XRDC2_MAKE_PERIPH(3, 48 ), /**< CCM_0 */
    kXRDC2_Periph_SSARC_LP          = XRDC2_MAKE_PERIPH(3, 46 ), /**< SSARC_LP */
    kXRDC2_Periph_SSARC_HP          = XRDC2_MAKE_PERIPH(3, 45 ), /**< SSARC_HP */
    kXRDC2_Periph_PIT2              = XRDC2_MAKE_PERIPH(3, 44 ), /**< PIT2 */
    kXRDC2_Periph_OCOTP_CTRL_WRAPPER = XRDC2_MAKE_PERIPH(3, 43 ), /**< OCOTP_CTRL_WRAPPER */
    kXRDC2_Periph_DCDC              = XRDC2_MAKE_PERIPH(3, 42 ), /**< DCDC */
    kXRDC2_Periph_ROMCP             = XRDC2_MAKE_PERIPH(3, 41 ), /**< ROMCP */
    kXRDC2_Periph_GPIO13            = XRDC2_MAKE_PERIPH(3, 40 ), /**< GPIO13 */
    kXRDC2_Periph_SNVS_SRAM         = XRDC2_MAKE_PERIPH(3, 39 ), /**< SNVS_SRAM */
    kXRDC2_Periph_IOMUXC_SNVS_GPR   = XRDC2_MAKE_PERIPH(3, 38 ), /**< IOMUXC_SNVS_GPR */
    kXRDC2_Periph_IOMUXC_SNVS       = XRDC2_MAKE_PERIPH(3, 37 ), /**< IOMUXC_SNVS */
    kXRDC2_Periph_SNVS_HP_WRAPPER   = XRDC2_MAKE_PERIPH(3, 36 ), /**< SNVS_HP_WRAPPER */
    kXRDC2_Periph_PGMC              = XRDC2_MAKE_PERIPH(3, 34 ), /**< PGMC */
    kXRDC2_Periph_ANATOP            = XRDC2_MAKE_PERIPH(3, 33 ), /**< ANATOP */
    kXRDC2_Periph_KEY_MANAGER       = XRDC2_MAKE_PERIPH(3, 32 ), /**< KEY_MANAGER */
    kXRDC2_Periph_RDC               = XRDC2_MAKE_PERIPH(3, 30 ), /**< RDC */
    kXRDC2_Periph_GPIO12            = XRDC2_MAKE_PERIPH(3, 28 ), /**< GPIO12 */
    kXRDC2_Periph_GPIO11            = XRDC2_MAKE_PERIPH(3, 27 ), /**< GPIO11 */
    kXRDC2_Periph_GPIO10            = XRDC2_MAKE_PERIPH(3, 26 ), /**< GPIO10 */
    kXRDC2_Periph_GPIO9             = XRDC2_MAKE_PERIPH(3, 25 ), /**< GPIO9 */
    kXRDC2_Periph_GPIO8             = XRDC2_MAKE_PERIPH(3, 24 ), /**< GPIO8 */
    kXRDC2_Periph_GPIO7             = XRDC2_MAKE_PERIPH(3, 23 ), /**< GPIO7 */
    kXRDC2_Periph_MU_B              = XRDC2_MAKE_PERIPH(3, 19 ), /**< MU_B */
    kXRDC2_Periph_MU_A              = XRDC2_MAKE_PERIPH(3, 18 ), /**< MU_A */
    kXRDC2_Periph_SEMA1             = XRDC2_MAKE_PERIPH(3, 17 ), /**< SEMA1 */
    kXRDC2_Periph_SAI4              = XRDC2_MAKE_PERIPH(3, 16 ), /**< SAI4 */
    kXRDC2_Periph_CAN3              = XRDC2_MAKE_PERIPH(3, 15 ), /**< CAN3 */
    kXRDC2_Periph_LPI2C6            = XRDC2_MAKE_PERIPH(3, 14 ), /**< LPI2C6 */
    kXRDC2_Periph_LPI2C5            = XRDC2_MAKE_PERIPH(3, 13 ), /**< LPI2C5 */
    kXRDC2_Periph_LPSPI6            = XRDC2_MAKE_PERIPH(3, 12 ), /**< LPSPI6 */
    kXRDC2_Periph_LPSPI5            = XRDC2_MAKE_PERIPH(3, 11 ), /**< LPSPI5 */
    kXRDC2_Periph_LPUART12          = XRDC2_MAKE_PERIPH(3, 10 ), /**< LPUART12 */
    kXRDC2_Periph_LPUART11          = XRDC2_MAKE_PERIPH(3, 9  ), /**< LPUART11 */
    kXRDC2_Periph_MIC               = XRDC2_MAKE_PERIPH(3, 8  ), /**< MIC */
    kXRDC2_Periph_DMA_CH_MUX_LPSR   = XRDC2_MAKE_PERIPH(3, 6  ), /**< DMA_CH_MUX_LPSR */
    kXRDC2_Periph_EDMA_LPSR         = XRDC2_MAKE_PERIPH(3, 5  ), /**< EDMA_LPSR */
    kXRDC2_Periph_WDOG4             = XRDC2_MAKE_PERIPH(3, 4  ), /**< WDOG4 */
    kXRDC2_Periph_IOMUXC_LPSR_GPR   = XRDC2_MAKE_PERIPH(3, 3  ), /**< IOMUXC_LPSR_GPR */
    kXRDC2_Periph_IOMUXC_LPSR       = XRDC2_MAKE_PERIPH(3, 2  ), /**< IOMUXC_LPSR */
    kXRDC2_Periph_SRC               = XRDC2_MAKE_PERIPH(3, 1  ), /**< SRC */
    kXRDC2_Periph_GPC               = XRDC2_MAKE_PERIPH(3, 0  ), /**< GPC */
    kXRDC2_Periph_GPU               = XRDC2_MAKE_PERIPH(4, 0  ), /**< GPU */
    kXRDC2_Periph_PXP               = XRDC2_MAKE_PERIPH(2, 5  ), /**< PXP */
    kXRDC2_Periph_LCDIF             = XRDC2_MAKE_PERIPH(2, 1  ), /**< LCDIF */
    kXRDC2_Periph_CSI               = XRDC2_MAKE_PERIPH(2, 0  ), /**< CSI */
} xrdc2_periph_t;

/* @} */
#endif /* XRDC2_PERIPH_T_ */


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
   -- XRDC2 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XRDC2_Peripheral_Access_Layer XRDC2 Peripheral Access Layer
 * @{
 */

/** XRDC2 - Size of Registers Arrays */
#define XRDC2_MSCI_MSAC_WK_COUNT                  128u
#define XRDC2_MDACI_COUNT                         32u
#define XRDC2_MDACI_MDACI_MDAJ_COUNT              32u
#define XRDC2_PACI_COUNT                          8u
#define XRDC2_PACI_PACI_PDACJ_COUNT               256u
#define XRDC2_MRCI_COUNT                          32u
#define XRDC2_MRCI_MRCI_MRGDJ_COUNT               32u

/** XRDC2 - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Control Register, offset: 0x0 */
  __I  uint32_t SR;                                /**< Status Register, offset: 0x4 */
       uint8_t RESERVED_0[4088];
  struct {                                         /* offset: 0x1000, array step: 0x8 */
    __IO uint32_t MSC_MSAC_W0;                       /**< Memory Slot Access Control, array offset: 0x1000, array step: 0x8 */
    __IO uint32_t MSC_MSAC_W1;                       /**< Memory Slot Access Control, array offset: 0x1004, array step: 0x8 */
  } MSCI_MSAC_WK[XRDC2_MSCI_MSAC_WK_COUNT];
       uint8_t RESERVED_1[3072];
  struct {                                         /* offset: 0x2000, array step: index*0x100, index2*0x8 */
    __IO uint32_t MDAC_MDA_W0;                       /**< Master Domain Assignment, array offset: 0x2000, array step: index*0x100, index2*0x8 */
    __IO uint32_t MDAC_MDA_W1;                       /**< Master Domain Assignment, array offset: 0x2004, array step: index*0x100, index2*0x8 */
  } MDACI_MDAJ[XRDC2_MDACI_COUNT][XRDC2_MDACI_MDACI_MDAJ_COUNT];
  struct {                                         /* offset: 0x4000, array step: index*0x800, index2*0x8 */
    __IO uint32_t PAC_PDAC_W0;                       /**< Peripheral Domain Access Control, array offset: 0x4000, array step: index*0x800, index2*0x8 */
    __IO uint32_t PAC_PDAC_W1;                       /**< Peripheral Domain Access Control, array offset: 0x4004, array step: index*0x800, index2*0x8 */
  } PACI_PDACJ[XRDC2_PACI_COUNT][XRDC2_PACI_PACI_PDACJ_COUNT];
  struct {                                         /* offset: 0x8000, array step: index*0x400, index2*0x20 */
    __IO uint32_t MRC_MRGD_W0;                       /**< Memory Region Descriptor, array offset: 0x8000, array step: index*0x400, index2*0x20 */
    __IO uint32_t MRC_MRGD_W1;                       /**< Memory Region Descriptor, array offset: 0x8004, array step: index*0x400, index2*0x20 */
    __IO uint32_t MRC_MRGD_W2;                       /**< Memory Region Descriptor, array offset: 0x8008, array step: index*0x400, index2*0x20 */
    __IO uint32_t MRC_MRGD_W3;                       /**< Memory Region Descriptor, array offset: 0x800C, array step: index*0x400, index2*0x20 */
         uint8_t RESERVED_0[4];
    __IO uint32_t MRC_MRGD_W5;                       /**< Memory Region Descriptor, array offset: 0x8014, array step: index*0x400, index2*0x20 */
    __IO uint32_t MRC_MRGD_W6;                       /**< Memory Region Descriptor, array offset: 0x8018, array step: index*0x400, index2*0x20 */
         uint8_t RESERVED_1[4];
  } MRCI_MRGDJ[XRDC2_MRCI_COUNT][XRDC2_MRCI_MRCI_MRGDJ_COUNT];
} XRDC2_Type;

/* ----------------------------------------------------------------------------
   -- XRDC2 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XRDC2_Register_Masks XRDC2 Register Masks
 * @{
 */

/*! @name MCR - Module Control Register */
/*! @{ */

#define XRDC2_MCR_GVLDM_MASK                     (0x1U)
#define XRDC2_MCR_GVLDM_SHIFT                    (0U)
/*! GVLDM - Global Valid MDAC
 *  0b0..MDACs are disabled.
 *  0b1..MDACs are enabled.
 */
#define XRDC2_MCR_GVLDM(x)                       (((uint32_t)(((uint32_t)(x)) << XRDC2_MCR_GVLDM_SHIFT)) & XRDC2_MCR_GVLDM_MASK)

#define XRDC2_MCR_GVLDC_MASK                     (0x2U)
#define XRDC2_MCR_GVLDC_SHIFT                    (1U)
/*! GVLDC - Global Valid Access Control
 *  0b0..Access controls are disabled, XRDC2 allows all transactions.
 *  0b1..Access controls are enabled.
 */
#define XRDC2_MCR_GVLDC(x)                       (((uint32_t)(((uint32_t)(x)) << XRDC2_MCR_GVLDC_SHIFT)) & XRDC2_MCR_GVLDC_MASK)

#define XRDC2_MCR_GCL_MASK                       (0x30U)
#define XRDC2_MCR_GCL_SHIFT                      (4U)
/*! GCL - Global Configuration Lock
 *  0b00..Lock disabled, registers can be written by any domain.
 *  0b01..Lock disabled until the next reset, registers can be written by any domain.
 *  0b10..Lock enabled, only the global configuration lock owner (SR[GCLO]) can write to registers.
 *  0b11..Lock enabled, all registers are read only until the next reset.
 */
#define XRDC2_MCR_GCL(x)                         (((uint32_t)(((uint32_t)(x)) << XRDC2_MCR_GCL_SHIFT)) & XRDC2_MCR_GCL_MASK)
/*! @} */

/*! @name SR - Status Register */
/*! @{ */

#define XRDC2_SR_DIN_MASK                        (0xFU)
#define XRDC2_SR_DIN_SHIFT                       (0U)
/*! DIN - Domain Identifier Number */
#define XRDC2_SR_DIN(x)                          (((uint32_t)(((uint32_t)(x)) << XRDC2_SR_DIN_SHIFT)) & XRDC2_SR_DIN_MASK)

#define XRDC2_SR_HRL_MASK                        (0xF0U)
#define XRDC2_SR_HRL_SHIFT                       (4U)
/*! HRL - Hardware Revision Level */
#define XRDC2_SR_HRL(x)                          (((uint32_t)(((uint32_t)(x)) << XRDC2_SR_HRL_SHIFT)) & XRDC2_SR_HRL_MASK)

#define XRDC2_SR_GCLO_MASK                       (0xF00U)
#define XRDC2_SR_GCLO_SHIFT                      (8U)
/*! GCLO - Global Configuration Lock Owner */
#define XRDC2_SR_GCLO(x)                         (((uint32_t)(((uint32_t)(x)) << XRDC2_SR_GCLO_SHIFT)) & XRDC2_SR_GCLO_MASK)
/*! @} */

/*! @name MSC_MSAC_W0 - Memory Slot Access Control */
/*! @{ */

#define XRDC2_MSC_MSAC_W0_D0ACP_MASK             (0x7U)
#define XRDC2_MSC_MSAC_W0_D0ACP_SHIFT            (0U)
/*! D0ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W0_D0ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_D0ACP_SHIFT)) & XRDC2_MSC_MSAC_W0_D0ACP_MASK)

#define XRDC2_MSC_MSAC_W0_D1ACP_MASK             (0x38U)
#define XRDC2_MSC_MSAC_W0_D1ACP_SHIFT            (3U)
/*! D1ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W0_D1ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_D1ACP_SHIFT)) & XRDC2_MSC_MSAC_W0_D1ACP_MASK)

#define XRDC2_MSC_MSAC_W0_D2ACP_MASK             (0x1C0U)
#define XRDC2_MSC_MSAC_W0_D2ACP_SHIFT            (6U)
/*! D2ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W0_D2ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_D2ACP_SHIFT)) & XRDC2_MSC_MSAC_W0_D2ACP_MASK)

#define XRDC2_MSC_MSAC_W0_D3ACP_MASK             (0xE00U)
#define XRDC2_MSC_MSAC_W0_D3ACP_SHIFT            (9U)
/*! D3ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W0_D3ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_D3ACP_SHIFT)) & XRDC2_MSC_MSAC_W0_D3ACP_MASK)

#define XRDC2_MSC_MSAC_W0_D4ACP_MASK             (0x7000U)
#define XRDC2_MSC_MSAC_W0_D4ACP_SHIFT            (12U)
/*! D4ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W0_D4ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_D4ACP_SHIFT)) & XRDC2_MSC_MSAC_W0_D4ACP_MASK)

#define XRDC2_MSC_MSAC_W0_D5ACP_MASK             (0x38000U)
#define XRDC2_MSC_MSAC_W0_D5ACP_SHIFT            (15U)
/*! D5ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W0_D5ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_D5ACP_SHIFT)) & XRDC2_MSC_MSAC_W0_D5ACP_MASK)

#define XRDC2_MSC_MSAC_W0_D6ACP_MASK             (0x1C0000U)
#define XRDC2_MSC_MSAC_W0_D6ACP_SHIFT            (18U)
/*! D6ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W0_D6ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_D6ACP_SHIFT)) & XRDC2_MSC_MSAC_W0_D6ACP_MASK)

#define XRDC2_MSC_MSAC_W0_D7ACP_MASK             (0xE00000U)
#define XRDC2_MSC_MSAC_W0_D7ACP_SHIFT            (21U)
/*! D7ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W0_D7ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_D7ACP_SHIFT)) & XRDC2_MSC_MSAC_W0_D7ACP_MASK)

#define XRDC2_MSC_MSAC_W0_EALO_MASK              (0xF000000U)
#define XRDC2_MSC_MSAC_W0_EALO_SHIFT             (24U)
/*! EALO - Exclusive Access Lock Owner */
#define XRDC2_MSC_MSAC_W0_EALO(x)                (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W0_EALO_SHIFT)) & XRDC2_MSC_MSAC_W0_EALO_MASK)
/*! @} */

/* The count of XRDC2_MSC_MSAC_W0 */
#define XRDC2_MSC_MSAC_W0_COUNT                  (128U)

/*! @name MSC_MSAC_W1 - Memory Slot Access Control */
/*! @{ */

#define XRDC2_MSC_MSAC_W1_D8ACP_MASK             (0x7U)
#define XRDC2_MSC_MSAC_W1_D8ACP_SHIFT            (0U)
/*! D8ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W1_D8ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_D8ACP_SHIFT)) & XRDC2_MSC_MSAC_W1_D8ACP_MASK)

#define XRDC2_MSC_MSAC_W1_D9ACP_MASK             (0x38U)
#define XRDC2_MSC_MSAC_W1_D9ACP_SHIFT            (3U)
/*! D9ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W1_D9ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_D9ACP_SHIFT)) & XRDC2_MSC_MSAC_W1_D9ACP_MASK)

#define XRDC2_MSC_MSAC_W1_D10ACP_MASK            (0x1C0U)
#define XRDC2_MSC_MSAC_W1_D10ACP_SHIFT           (6U)
/*! D10ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W1_D10ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_D10ACP_SHIFT)) & XRDC2_MSC_MSAC_W1_D10ACP_MASK)

#define XRDC2_MSC_MSAC_W1_D11ACP_MASK            (0xE00U)
#define XRDC2_MSC_MSAC_W1_D11ACP_SHIFT           (9U)
/*! D11ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W1_D11ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_D11ACP_SHIFT)) & XRDC2_MSC_MSAC_W1_D11ACP_MASK)

#define XRDC2_MSC_MSAC_W1_D12ACP_MASK            (0x7000U)
#define XRDC2_MSC_MSAC_W1_D12ACP_SHIFT           (12U)
/*! D12ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W1_D12ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_D12ACP_SHIFT)) & XRDC2_MSC_MSAC_W1_D12ACP_MASK)

#define XRDC2_MSC_MSAC_W1_D13ACP_MASK            (0x38000U)
#define XRDC2_MSC_MSAC_W1_D13ACP_SHIFT           (15U)
/*! D13ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W1_D13ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_D13ACP_SHIFT)) & XRDC2_MSC_MSAC_W1_D13ACP_MASK)

#define XRDC2_MSC_MSAC_W1_D14ACP_MASK            (0x1C0000U)
#define XRDC2_MSC_MSAC_W1_D14ACP_SHIFT           (18U)
/*! D14ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W1_D14ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_D14ACP_SHIFT)) & XRDC2_MSC_MSAC_W1_D14ACP_MASK)

#define XRDC2_MSC_MSAC_W1_D15ACP_MASK            (0xE00000U)
#define XRDC2_MSC_MSAC_W1_D15ACP_SHIFT           (21U)
/*! D15ACP - Domain "x" access control policy */
#define XRDC2_MSC_MSAC_W1_D15ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_D15ACP_SHIFT)) & XRDC2_MSC_MSAC_W1_D15ACP_MASK)

#define XRDC2_MSC_MSAC_W1_EAL_MASK               (0x3000000U)
#define XRDC2_MSC_MSAC_W1_EAL_SHIFT              (24U)
/*! EAL - Exclusive Access Lock
 *  0b00..Lock disabled.
 *  0b01..Lock disabled until next reset.
 *  0b10..Lock enabled, lock state = available.
 *  0b11..Lock enabled, lock state = not available.
 */
#define XRDC2_MSC_MSAC_W1_EAL(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_EAL_SHIFT)) & XRDC2_MSC_MSAC_W1_EAL_MASK)

#define XRDC2_MSC_MSAC_W1_DL2_MASK               (0x60000000U)
#define XRDC2_MSC_MSAC_W1_DL2_SHIFT              (29U)
/*! DL2 - Descriptor Lock
 *  0b00..Lock disabled, descriptor registers can be written.
 *  0b01..Lock disabled until the next reset, descriptor registers can be written.
 *  0b10..Lock enabled, only domain "x" can only update the DxACP field; no other fields can be written.
 *  0b11..Lock enabled, descriptor registers are read-only until the next reset.
 */
#define XRDC2_MSC_MSAC_W1_DL2(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_DL2_SHIFT)) & XRDC2_MSC_MSAC_W1_DL2_MASK)

#define XRDC2_MSC_MSAC_W1_VLD_MASK               (0x80000000U)
#define XRDC2_MSC_MSAC_W1_VLD_SHIFT              (31U)
/*! VLD - Valid
 *  0b0..The MSAC assignment is invalid.
 *  0b1..The MSAC assignment is valid.
 */
#define XRDC2_MSC_MSAC_W1_VLD(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_MSC_MSAC_W1_VLD_SHIFT)) & XRDC2_MSC_MSAC_W1_VLD_MASK)
/*! @} */

/* The count of XRDC2_MSC_MSAC_W1 */
#define XRDC2_MSC_MSAC_W1_COUNT                  (128U)

/*! @name MDAC_MDA_W0 - Master Domain Assignment */
/*! @{ */

#define XRDC2_MDAC_MDA_W0_MASK_MASK              (0xFFFFU)
#define XRDC2_MDAC_MDA_W0_MASK_SHIFT             (0U)
/*! MASK - Mask */
#define XRDC2_MDAC_MDA_W0_MASK(x)                (((uint32_t)(((uint32_t)(x)) << XRDC2_MDAC_MDA_W0_MASK_SHIFT)) & XRDC2_MDAC_MDA_W0_MASK_MASK)

#define XRDC2_MDAC_MDA_W0_MATCH_MASK             (0xFFFF0000U)
#define XRDC2_MDAC_MDA_W0_MATCH_SHIFT            (16U)
/*! MATCH - Match */
#define XRDC2_MDAC_MDA_W0_MATCH(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MDAC_MDA_W0_MATCH_SHIFT)) & XRDC2_MDAC_MDA_W0_MATCH_MASK)
/*! @} */

/* The count of XRDC2_MDAC_MDA_W0 */
#define XRDC2_MDAC_MDA_W0_COUNT                  (32U)

/* The count of XRDC2_MDAC_MDA_W0 */
#define XRDC2_MDAC_MDA_W0_COUNT2                 (32U)

/*! @name MDAC_MDA_W1 - Master Domain Assignment */
/*! @{ */

#define XRDC2_MDAC_MDA_W1_DID_MASK               (0xF0000U)
#define XRDC2_MDAC_MDA_W1_DID_SHIFT              (16U)
/*! DID - Domain Identifier */
#define XRDC2_MDAC_MDA_W1_DID(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_MDAC_MDA_W1_DID_SHIFT)) & XRDC2_MDAC_MDA_W1_DID_MASK)

#define XRDC2_MDAC_MDA_W1_PA_MASK                (0x3000000U)
#define XRDC2_MDAC_MDA_W1_PA_SHIFT               (24U)
/*! PA - Privileged attribute
 *  0b00..Use the bus master's privileged/user attribute directly.
 *  0b01..Use the bus master's privileged/user attribute directly.
 *  0b10..Force the bus attribute for this master to user.
 *  0b11..Force the bus attribute for this master to privileged.
 */
#define XRDC2_MDAC_MDA_W1_PA(x)                  (((uint32_t)(((uint32_t)(x)) << XRDC2_MDAC_MDA_W1_PA_SHIFT)) & XRDC2_MDAC_MDA_W1_PA_MASK)

#define XRDC2_MDAC_MDA_W1_SA_MASK                (0xC000000U)
#define XRDC2_MDAC_MDA_W1_SA_SHIFT               (26U)
/*! SA - Secure attribute
 *  0b00..Use the bus master's secure/nonsecure attribute directly.
 *  0b01..Use the bus master's secure/nonsecure attribute directly.
 *  0b10..Force the bus attribute for this master to secure.
 *  0b11..Force the bus attribute for this master to nonsecure.
 */
#define XRDC2_MDAC_MDA_W1_SA(x)                  (((uint32_t)(((uint32_t)(x)) << XRDC2_MDAC_MDA_W1_SA_SHIFT)) & XRDC2_MDAC_MDA_W1_SA_MASK)

#define XRDC2_MDAC_MDA_W1_DL_MASK                (0x40000000U)
#define XRDC2_MDAC_MDA_W1_DL_SHIFT               (30U)
/*! DL - Descriptor Lock
 *  0b0..Lock disabled, registers can be written.
 *  0b1..Lock enabled, registers are read-only until the next reset.
 */
#define XRDC2_MDAC_MDA_W1_DL(x)                  (((uint32_t)(((uint32_t)(x)) << XRDC2_MDAC_MDA_W1_DL_SHIFT)) & XRDC2_MDAC_MDA_W1_DL_MASK)

#define XRDC2_MDAC_MDA_W1_VLD_MASK               (0x80000000U)
#define XRDC2_MDAC_MDA_W1_VLD_SHIFT              (31U)
/*! VLD - Valid
 *  0b0..The MDA is invalid.
 *  0b1..The MDA is valid.
 */
#define XRDC2_MDAC_MDA_W1_VLD(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_MDAC_MDA_W1_VLD_SHIFT)) & XRDC2_MDAC_MDA_W1_VLD_MASK)
/*! @} */

/* The count of XRDC2_MDAC_MDA_W1 */
#define XRDC2_MDAC_MDA_W1_COUNT                  (32U)

/* The count of XRDC2_MDAC_MDA_W1 */
#define XRDC2_MDAC_MDA_W1_COUNT2                 (32U)

/*! @name PAC_PDAC_W0 - Peripheral Domain Access Control */
/*! @{ */

#define XRDC2_PAC_PDAC_W0_D0ACP_MASK             (0x7U)
#define XRDC2_PAC_PDAC_W0_D0ACP_SHIFT            (0U)
/*! D0ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W0_D0ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_D0ACP_SHIFT)) & XRDC2_PAC_PDAC_W0_D0ACP_MASK)

#define XRDC2_PAC_PDAC_W0_D1ACP_MASK             (0x38U)
#define XRDC2_PAC_PDAC_W0_D1ACP_SHIFT            (3U)
/*! D1ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W0_D1ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_D1ACP_SHIFT)) & XRDC2_PAC_PDAC_W0_D1ACP_MASK)

#define XRDC2_PAC_PDAC_W0_D2ACP_MASK             (0x1C0U)
#define XRDC2_PAC_PDAC_W0_D2ACP_SHIFT            (6U)
/*! D2ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W0_D2ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_D2ACP_SHIFT)) & XRDC2_PAC_PDAC_W0_D2ACP_MASK)

#define XRDC2_PAC_PDAC_W0_D3ACP_MASK             (0xE00U)
#define XRDC2_PAC_PDAC_W0_D3ACP_SHIFT            (9U)
/*! D3ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W0_D3ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_D3ACP_SHIFT)) & XRDC2_PAC_PDAC_W0_D3ACP_MASK)

#define XRDC2_PAC_PDAC_W0_D4ACP_MASK             (0x7000U)
#define XRDC2_PAC_PDAC_W0_D4ACP_SHIFT            (12U)
/*! D4ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W0_D4ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_D4ACP_SHIFT)) & XRDC2_PAC_PDAC_W0_D4ACP_MASK)

#define XRDC2_PAC_PDAC_W0_D5ACP_MASK             (0x38000U)
#define XRDC2_PAC_PDAC_W0_D5ACP_SHIFT            (15U)
/*! D5ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W0_D5ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_D5ACP_SHIFT)) & XRDC2_PAC_PDAC_W0_D5ACP_MASK)

#define XRDC2_PAC_PDAC_W0_D6ACP_MASK             (0x1C0000U)
#define XRDC2_PAC_PDAC_W0_D6ACP_SHIFT            (18U)
/*! D6ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W0_D6ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_D6ACP_SHIFT)) & XRDC2_PAC_PDAC_W0_D6ACP_MASK)

#define XRDC2_PAC_PDAC_W0_D7ACP_MASK             (0xE00000U)
#define XRDC2_PAC_PDAC_W0_D7ACP_SHIFT            (21U)
/*! D7ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W0_D7ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_D7ACP_SHIFT)) & XRDC2_PAC_PDAC_W0_D7ACP_MASK)

#define XRDC2_PAC_PDAC_W0_EALO_MASK              (0xF000000U)
#define XRDC2_PAC_PDAC_W0_EALO_SHIFT             (24U)
/*! EALO - Exclusive Access Lock Owner */
#define XRDC2_PAC_PDAC_W0_EALO(x)                (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W0_EALO_SHIFT)) & XRDC2_PAC_PDAC_W0_EALO_MASK)
/*! @} */

/* The count of XRDC2_PAC_PDAC_W0 */
#define XRDC2_PAC_PDAC_W0_COUNT                  (8U)

/* The count of XRDC2_PAC_PDAC_W0 */
#define XRDC2_PAC_PDAC_W0_COUNT2                 (256U)

/*! @name PAC_PDAC_W1 - Peripheral Domain Access Control */
/*! @{ */

#define XRDC2_PAC_PDAC_W1_D8ACP_MASK             (0x7U)
#define XRDC2_PAC_PDAC_W1_D8ACP_SHIFT            (0U)
/*! D8ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W1_D8ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_D8ACP_SHIFT)) & XRDC2_PAC_PDAC_W1_D8ACP_MASK)

#define XRDC2_PAC_PDAC_W1_D9ACP_MASK             (0x38U)
#define XRDC2_PAC_PDAC_W1_D9ACP_SHIFT            (3U)
/*! D9ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W1_D9ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_D9ACP_SHIFT)) & XRDC2_PAC_PDAC_W1_D9ACP_MASK)

#define XRDC2_PAC_PDAC_W1_D10ACP_MASK            (0x1C0U)
#define XRDC2_PAC_PDAC_W1_D10ACP_SHIFT           (6U)
/*! D10ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W1_D10ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_D10ACP_SHIFT)) & XRDC2_PAC_PDAC_W1_D10ACP_MASK)

#define XRDC2_PAC_PDAC_W1_D11ACP_MASK            (0xE00U)
#define XRDC2_PAC_PDAC_W1_D11ACP_SHIFT           (9U)
/*! D11ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W1_D11ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_D11ACP_SHIFT)) & XRDC2_PAC_PDAC_W1_D11ACP_MASK)

#define XRDC2_PAC_PDAC_W1_D12ACP_MASK            (0x7000U)
#define XRDC2_PAC_PDAC_W1_D12ACP_SHIFT           (12U)
/*! D12ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W1_D12ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_D12ACP_SHIFT)) & XRDC2_PAC_PDAC_W1_D12ACP_MASK)

#define XRDC2_PAC_PDAC_W1_D13ACP_MASK            (0x38000U)
#define XRDC2_PAC_PDAC_W1_D13ACP_SHIFT           (15U)
/*! D13ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W1_D13ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_D13ACP_SHIFT)) & XRDC2_PAC_PDAC_W1_D13ACP_MASK)

#define XRDC2_PAC_PDAC_W1_D14ACP_MASK            (0x1C0000U)
#define XRDC2_PAC_PDAC_W1_D14ACP_SHIFT           (18U)
/*! D14ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W1_D14ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_D14ACP_SHIFT)) & XRDC2_PAC_PDAC_W1_D14ACP_MASK)

#define XRDC2_PAC_PDAC_W1_D15ACP_MASK            (0xE00000U)
#define XRDC2_PAC_PDAC_W1_D15ACP_SHIFT           (21U)
/*! D15ACP - Domain "x" access control policy */
#define XRDC2_PAC_PDAC_W1_D15ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_D15ACP_SHIFT)) & XRDC2_PAC_PDAC_W1_D15ACP_MASK)

#define XRDC2_PAC_PDAC_W1_EAL_MASK               (0x3000000U)
#define XRDC2_PAC_PDAC_W1_EAL_SHIFT              (24U)
/*! EAL - Exclusive Access Lock
 *  0b00..Lock disabled.
 *  0b01..Lock disabled until next reset.
 *  0b10..Lock enabled, lock state = available.
 *  0b11..Lock enabled, lock state = not available.
 */
#define XRDC2_PAC_PDAC_W1_EAL(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_EAL_SHIFT)) & XRDC2_PAC_PDAC_W1_EAL_MASK)

#define XRDC2_PAC_PDAC_W1_DL2_MASK               (0x60000000U)
#define XRDC2_PAC_PDAC_W1_DL2_SHIFT              (29U)
/*! DL2 - Descriptor Lock
 *  0b00..Lock disabled, descriptor registers can be written..
 *  0b01..Lock disabled until the next reset, descriptor registers can be written..
 *  0b10..Lock enabled, only domain "x" can only update the DxACP field; no other fields can be written..
 *  0b11..Lock enabled, descriptor registers are read-only until the next reset.
 */
#define XRDC2_PAC_PDAC_W1_DL2(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_DL2_SHIFT)) & XRDC2_PAC_PDAC_W1_DL2_MASK)

#define XRDC2_PAC_PDAC_W1_VLD_MASK               (0x80000000U)
#define XRDC2_PAC_PDAC_W1_VLD_SHIFT              (31U)
/*! VLD - Valid
 *  0b0..The PDAC assignment is invalid.
 *  0b1..The PDAC assignment is valid.
 */
#define XRDC2_PAC_PDAC_W1_VLD(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_PAC_PDAC_W1_VLD_SHIFT)) & XRDC2_PAC_PDAC_W1_VLD_MASK)
/*! @} */

/* The count of XRDC2_PAC_PDAC_W1 */
#define XRDC2_PAC_PDAC_W1_COUNT                  (8U)

/* The count of XRDC2_PAC_PDAC_W1 */
#define XRDC2_PAC_PDAC_W1_COUNT2                 (256U)

/*! @name MRC_MRGD_W0 - Memory Region Descriptor */
/*! @{ */

#define XRDC2_MRC_MRGD_W0_SRTADDR_MASK           (0xFFFFF000U)
#define XRDC2_MRC_MRGD_W0_SRTADDR_SHIFT          (12U)
/*! SRTADDR - Start Address */
#define XRDC2_MRC_MRGD_W0_SRTADDR(x)             (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W0_SRTADDR_SHIFT)) & XRDC2_MRC_MRGD_W0_SRTADDR_MASK)
/*! @} */

/* The count of XRDC2_MRC_MRGD_W0 */
#define XRDC2_MRC_MRGD_W0_COUNT                  (32U)

/* The count of XRDC2_MRC_MRGD_W0 */
#define XRDC2_MRC_MRGD_W0_COUNT2                 (32U)

/*! @name MRC_MRGD_W1 - Memory Region Descriptor */
/*! @{ */

#define XRDC2_MRC_MRGD_W1_SRTADDR_MASK           (0xFU)
#define XRDC2_MRC_MRGD_W1_SRTADDR_SHIFT          (0U)
/*! SRTADDR - Start Address */
#define XRDC2_MRC_MRGD_W1_SRTADDR(x)             (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W1_SRTADDR_SHIFT)) & XRDC2_MRC_MRGD_W1_SRTADDR_MASK)
/*! @} */

/* The count of XRDC2_MRC_MRGD_W1 */
#define XRDC2_MRC_MRGD_W1_COUNT                  (32U)

/* The count of XRDC2_MRC_MRGD_W1 */
#define XRDC2_MRC_MRGD_W1_COUNT2                 (32U)

/*! @name MRC_MRGD_W2 - Memory Region Descriptor */
/*! @{ */

#define XRDC2_MRC_MRGD_W2_ENDADDR_MASK           (0xFFFFF000U)
#define XRDC2_MRC_MRGD_W2_ENDADDR_SHIFT          (12U)
/*! ENDADDR - End Address */
#define XRDC2_MRC_MRGD_W2_ENDADDR(x)             (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W2_ENDADDR_SHIFT)) & XRDC2_MRC_MRGD_W2_ENDADDR_MASK)
/*! @} */

/* The count of XRDC2_MRC_MRGD_W2 */
#define XRDC2_MRC_MRGD_W2_COUNT                  (32U)

/* The count of XRDC2_MRC_MRGD_W2 */
#define XRDC2_MRC_MRGD_W2_COUNT2                 (32U)

/*! @name MRC_MRGD_W3 - Memory Region Descriptor */
/*! @{ */

#define XRDC2_MRC_MRGD_W3_ENDADDR_MASK           (0xFU)
#define XRDC2_MRC_MRGD_W3_ENDADDR_SHIFT          (0U)
/*! ENDADDR - End Address */
#define XRDC2_MRC_MRGD_W3_ENDADDR(x)             (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W3_ENDADDR_SHIFT)) & XRDC2_MRC_MRGD_W3_ENDADDR_MASK)
/*! @} */

/* The count of XRDC2_MRC_MRGD_W3 */
#define XRDC2_MRC_MRGD_W3_COUNT                  (32U)

/* The count of XRDC2_MRC_MRGD_W3 */
#define XRDC2_MRC_MRGD_W3_COUNT2                 (32U)

/*! @name MRC_MRGD_W5 - Memory Region Descriptor */
/*! @{ */

#define XRDC2_MRC_MRGD_W5_D0ACP_MASK             (0x7U)
#define XRDC2_MRC_MRGD_W5_D0ACP_SHIFT            (0U)
/*! D0ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W5_D0ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_D0ACP_SHIFT)) & XRDC2_MRC_MRGD_W5_D0ACP_MASK)

#define XRDC2_MRC_MRGD_W5_D1ACP_MASK             (0x38U)
#define XRDC2_MRC_MRGD_W5_D1ACP_SHIFT            (3U)
/*! D1ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W5_D1ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_D1ACP_SHIFT)) & XRDC2_MRC_MRGD_W5_D1ACP_MASK)

#define XRDC2_MRC_MRGD_W5_D2ACP_MASK             (0x1C0U)
#define XRDC2_MRC_MRGD_W5_D2ACP_SHIFT            (6U)
/*! D2ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W5_D2ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_D2ACP_SHIFT)) & XRDC2_MRC_MRGD_W5_D2ACP_MASK)

#define XRDC2_MRC_MRGD_W5_D3ACP_MASK             (0xE00U)
#define XRDC2_MRC_MRGD_W5_D3ACP_SHIFT            (9U)
/*! D3ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W5_D3ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_D3ACP_SHIFT)) & XRDC2_MRC_MRGD_W5_D3ACP_MASK)

#define XRDC2_MRC_MRGD_W5_D4ACP_MASK             (0x7000U)
#define XRDC2_MRC_MRGD_W5_D4ACP_SHIFT            (12U)
/*! D4ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W5_D4ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_D4ACP_SHIFT)) & XRDC2_MRC_MRGD_W5_D4ACP_MASK)

#define XRDC2_MRC_MRGD_W5_D5ACP_MASK             (0x38000U)
#define XRDC2_MRC_MRGD_W5_D5ACP_SHIFT            (15U)
/*! D5ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W5_D5ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_D5ACP_SHIFT)) & XRDC2_MRC_MRGD_W5_D5ACP_MASK)

#define XRDC2_MRC_MRGD_W5_D6ACP_MASK             (0x1C0000U)
#define XRDC2_MRC_MRGD_W5_D6ACP_SHIFT            (18U)
/*! D6ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W5_D6ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_D6ACP_SHIFT)) & XRDC2_MRC_MRGD_W5_D6ACP_MASK)

#define XRDC2_MRC_MRGD_W5_D7ACP_MASK             (0xE00000U)
#define XRDC2_MRC_MRGD_W5_D7ACP_SHIFT            (21U)
/*! D7ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W5_D7ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_D7ACP_SHIFT)) & XRDC2_MRC_MRGD_W5_D7ACP_MASK)

#define XRDC2_MRC_MRGD_W5_EALO_MASK              (0xF000000U)
#define XRDC2_MRC_MRGD_W5_EALO_SHIFT             (24U)
/*! EALO - Exclusive Access Lock Owner */
#define XRDC2_MRC_MRGD_W5_EALO(x)                (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W5_EALO_SHIFT)) & XRDC2_MRC_MRGD_W5_EALO_MASK)
/*! @} */

/* The count of XRDC2_MRC_MRGD_W5 */
#define XRDC2_MRC_MRGD_W5_COUNT                  (32U)

/* The count of XRDC2_MRC_MRGD_W5 */
#define XRDC2_MRC_MRGD_W5_COUNT2                 (32U)

/*! @name MRC_MRGD_W6 - Memory Region Descriptor */
/*! @{ */

#define XRDC2_MRC_MRGD_W6_D8ACP_MASK             (0x7U)
#define XRDC2_MRC_MRGD_W6_D8ACP_SHIFT            (0U)
/*! D8ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W6_D8ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_D8ACP_SHIFT)) & XRDC2_MRC_MRGD_W6_D8ACP_MASK)

#define XRDC2_MRC_MRGD_W6_D9ACP_MASK             (0x38U)
#define XRDC2_MRC_MRGD_W6_D9ACP_SHIFT            (3U)
/*! D9ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W6_D9ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_D9ACP_SHIFT)) & XRDC2_MRC_MRGD_W6_D9ACP_MASK)

#define XRDC2_MRC_MRGD_W6_D10ACP_MASK            (0x1C0U)
#define XRDC2_MRC_MRGD_W6_D10ACP_SHIFT           (6U)
/*! D10ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W6_D10ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_D10ACP_SHIFT)) & XRDC2_MRC_MRGD_W6_D10ACP_MASK)

#define XRDC2_MRC_MRGD_W6_D11ACP_MASK            (0xE00U)
#define XRDC2_MRC_MRGD_W6_D11ACP_SHIFT           (9U)
/*! D11ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W6_D11ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_D11ACP_SHIFT)) & XRDC2_MRC_MRGD_W6_D11ACP_MASK)

#define XRDC2_MRC_MRGD_W6_D12ACP_MASK            (0x7000U)
#define XRDC2_MRC_MRGD_W6_D12ACP_SHIFT           (12U)
/*! D12ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W6_D12ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_D12ACP_SHIFT)) & XRDC2_MRC_MRGD_W6_D12ACP_MASK)

#define XRDC2_MRC_MRGD_W6_D13ACP_MASK            (0x38000U)
#define XRDC2_MRC_MRGD_W6_D13ACP_SHIFT           (15U)
/*! D13ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W6_D13ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_D13ACP_SHIFT)) & XRDC2_MRC_MRGD_W6_D13ACP_MASK)

#define XRDC2_MRC_MRGD_W6_D14ACP_MASK            (0x1C0000U)
#define XRDC2_MRC_MRGD_W6_D14ACP_SHIFT           (18U)
/*! D14ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W6_D14ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_D14ACP_SHIFT)) & XRDC2_MRC_MRGD_W6_D14ACP_MASK)

#define XRDC2_MRC_MRGD_W6_D15ACP_MASK            (0xE00000U)
#define XRDC2_MRC_MRGD_W6_D15ACP_SHIFT           (21U)
/*! D15ACP - Domain "x" access control policy */
#define XRDC2_MRC_MRGD_W6_D15ACP(x)              (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_D15ACP_SHIFT)) & XRDC2_MRC_MRGD_W6_D15ACP_MASK)

#define XRDC2_MRC_MRGD_W6_EAL_MASK               (0x3000000U)
#define XRDC2_MRC_MRGD_W6_EAL_SHIFT              (24U)
/*! EAL - Exclusive Access Lock
 *  0b00..Lock disabled.
 *  0b01..Lock disabled until next reset.
 *  0b10..Lock enabled, lock state = available.
 *  0b11..Lock enabled, lock state = not available.
 */
#define XRDC2_MRC_MRGD_W6_EAL(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_EAL_SHIFT)) & XRDC2_MRC_MRGD_W6_EAL_MASK)

#define XRDC2_MRC_MRGD_W6_DL2_MASK               (0x60000000U)
#define XRDC2_MRC_MRGD_W6_DL2_SHIFT              (29U)
/*! DL2 - Descriptor Lock
 *  0b00..Lock disabled, descriptor registers can be written.
 *  0b01..Lock disabled until the next reset, descriptor registers can be written.
 *  0b10..Lock enabled, only domain "x" can only update the DxACP field; no other fields can be written.
 *  0b11..Lock enabled, descriptor registers are read-only until the next reset.
 */
#define XRDC2_MRC_MRGD_W6_DL2(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_DL2_SHIFT)) & XRDC2_MRC_MRGD_W6_DL2_MASK)

#define XRDC2_MRC_MRGD_W6_VLD_MASK               (0x80000000U)
#define XRDC2_MRC_MRGD_W6_VLD_SHIFT              (31U)
/*! VLD - Valid
 *  0b0..The MRGD is invalid.
 *  0b1..The MRGD is valid.
 */
#define XRDC2_MRC_MRGD_W6_VLD(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC2_MRC_MRGD_W6_VLD_SHIFT)) & XRDC2_MRC_MRGD_W6_VLD_MASK)
/*! @} */

/* The count of XRDC2_MRC_MRGD_W6 */
#define XRDC2_MRC_MRGD_W6_COUNT                  (32U)

/* The count of XRDC2_MRC_MRGD_W6 */
#define XRDC2_MRC_MRGD_W6_COUNT2                 (32U)


/*!
 * @}
 */ /* end of group XRDC2_Register_Masks */


/*!
 * @}
 */ /* end of group XRDC2_Peripheral_Access_Layer */


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


#endif  /* PERI_XRDC2_H_ */

