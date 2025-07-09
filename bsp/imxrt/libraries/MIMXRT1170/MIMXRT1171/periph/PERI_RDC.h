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
**         CMSIS Peripheral Access Layer for RDC
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
 * @file PERI_RDC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for RDC
 *
 * CMSIS Peripheral Access Layer for RDC
 */

#if !defined(PERI_RDC_H_)
#define PERI_RDC_H_                              /**< Symbol preventing repeated inclusion */

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
#if !defined(RDC_MASTER_T_)
#define RDC_MASTER_T_
/*!
 * @addtogroup rdc_mapping
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure for the RDC mapping
 *
 * Defines the structure for the RDC resource collections.
 */
/*
 * Domain of these masters are not assigned by RDC
 * CM7, CM7_DMA: Always use domain ID 0.
 * CM4, CM4_DMA: Use domain ID 0 in single core case, 1 in dual core case.
 * CAAM: Defined in CAAM mst_a[x]icid[10]
 * LCDIFv2: Defined in LCDIF2 user bit[0]
 * SSARC: Defined in SSARC user bit[0]
 */

typedef enum _rdc_master
{
    kRDC_Master_ENET_1G_TX          = 1U,          /**< ENET_1G_TX */
    kRDC_Master_ENET_1G_RX          = 2U,          /**< ENET_1G_RX */
    kRDC_Master_ENET                = 3U,          /**< ENET */
    kRDC_Master_ENET_QOS            = 4U,          /**< ENET_QOS */
    kRDC_Master_USDHC1              = 5U,          /**< USDHC1 */
    kRDC_Master_USDHC2              = 6U,          /**< USDHC2 */
    kRDC_Master_USB                 = 7U,          /**< USB */
    kRDC_Master_GPU                 = 8U,          /**< GPU */
    kRDC_Master_PXP                 = 9U,          /**< PXP */
    kRDC_Master_LCDIF               = 10U,         /**< LCDIF */
    kRDC_Master_CSI                 = 11U,         /**< CSI */
} rdc_master_t;
#endif /* RDC_MASTER_T_ */

#if !defined(RDC_MEM_T_)
#define RDC_MEM_T_
typedef enum _rdc_mem
{
    kRDC_Mem_MRC0_0                 = 0U,
    kRDC_Mem_MRC0_1                 = 1U,
    kRDC_Mem_MRC0_2                 = 2U,
    kRDC_Mem_MRC0_3                 = 3U,
    kRDC_Mem_MRC0_4                 = 4U,
    kRDC_Mem_MRC0_5                 = 5U,
    kRDC_Mem_MRC0_6                 = 6U,
    kRDC_Mem_MRC0_7                 = 7U,
    kRDC_Mem_MRC1_0                 = 8U,
    kRDC_Mem_MRC1_1                 = 9U,
    kRDC_Mem_MRC1_2                 = 10U,
    kRDC_Mem_MRC1_3                 = 11U,
    kRDC_Mem_MRC1_4                 = 12U,
    kRDC_Mem_MRC1_5                 = 13U,
    kRDC_Mem_MRC1_6                 = 14U,
    kRDC_Mem_MRC1_7                 = 15U,
    kRDC_Mem_MRC2_0                 = 16U,
    kRDC_Mem_MRC2_1                 = 17U,
    kRDC_Mem_MRC2_2                 = 18U,
    kRDC_Mem_MRC2_3                 = 19U,
    kRDC_Mem_MRC2_4                 = 20U,
    kRDC_Mem_MRC2_5                 = 21U,
    kRDC_Mem_MRC2_6                 = 22U,
    kRDC_Mem_MRC2_7                 = 23U,
    kRDC_Mem_MRC3_0                 = 24U,
    kRDC_Mem_MRC3_1                 = 25U,
    kRDC_Mem_MRC3_2                 = 26U,
    kRDC_Mem_MRC3_3                 = 27U,
    kRDC_Mem_MRC3_4                 = 28U,
    kRDC_Mem_MRC3_5                 = 29U,
    kRDC_Mem_MRC3_6                 = 30U,
    kRDC_Mem_MRC3_7                 = 31U,
    kRDC_Mem_MRC4_0                 = 32U,
    kRDC_Mem_MRC4_1                 = 33U,
    kRDC_Mem_MRC4_2                 = 34U,
    kRDC_Mem_MRC4_3                 = 35U,
    kRDC_Mem_MRC4_4                 = 36U,
    kRDC_Mem_MRC4_5                 = 37U,
    kRDC_Mem_MRC4_6                 = 38U,
    kRDC_Mem_MRC4_7                 = 39U,
    kRDC_Mem_MRC5_0                 = 40U,
    kRDC_Mem_MRC5_1                 = 41U,
    kRDC_Mem_MRC5_2                 = 42U,
    kRDC_Mem_MRC5_3                 = 43U,
    kRDC_Mem_MRC6_0                 = 44U,
    kRDC_Mem_MRC6_1                 = 45U,
    kRDC_Mem_MRC6_2                 = 46U,
    kRDC_Mem_MRC6_3                 = 47U,
    kRDC_Mem_MRC7_0                 = 48U,
    kRDC_Mem_MRC7_1                 = 49U,
    kRDC_Mem_MRC7_2                 = 50U,
    kRDC_Mem_MRC7_3                 = 51U,
    kRDC_Mem_MRC7_4                 = 52U,
    kRDC_Mem_MRC7_5                 = 53U,
    kRDC_Mem_MRC7_6                 = 54U,
    kRDC_Mem_MRC7_7                 = 55U,
    kRDC_Mem_MRC8_0                 = 56U,
    kRDC_Mem_MRC8_1                 = 57U,
    kRDC_Mem_MRC8_2                 = 58U,
} rdc_mem_t;
#endif /* RDC_MEM_T_ */

#if !defined(RDC_PERIPH_T_)
#define RDC_PERIPH_T_
typedef enum _rdc_periph
{
    kRDC_Periph_MTR                 = 0U,          /**< MTR */
    kRDC_Periph_MECC1               = 1U,          /**< MECC1 */
    kRDC_Periph_MECC2               = 2U,          /**< MECC2 */
    kRDC_Periph_FLEXSPI1            = 3U,          /**< FlexSPI1 */
    kRDC_Periph_FLEXSPI2            = 4U,          /**< FlexSPI2 */
    kRDC_Periph_SEMC                = 5U,          /**< SEMC */
    kRDC_Periph_CM7_IMXRT           = 6U,          /**< CM7_IMXRT */
    kRDC_Periph_EWM                 = 7U,          /**< EWM */
    kRDC_Periph_WDOG1               = 8U,          /**< WDOG1 */
    kRDC_Periph_WDOG2               = 9U,          /**< WDOG2 */
    kRDC_Periph_WDOG3               = 10U,         /**< WDOG3 */
    kRDC_Periph_AOI_XBAR            = 11U,         /**< AOI_XBAR */
    kRDC_Periph_ADC_ETC             = 12U,         /**< ADC_ETC */
    kRDC_Periph_CAAM_1              = 13U,         /**< CAAM_1 */
    kRDC_Periph_ADC1                = 14U,         /**< ADC1 */
    kRDC_Periph_ADC2                = 15U,         /**< ADC2 */
    kRDC_Periph_TSC_DIG             = 16U,         /**< TSC_DIG */
    kRDC_Periph_DAC                 = 17U,         /**< DAC */
    kRDC_Periph_IEE                 = 18U,         /**< IEE */
    kRDC_Periph_DMAMUX              = 19U,         /**< DMAMUX */
    kRDC_Periph_EDMA                = 19U,         /**< EDMA */
    kRDC_Periph_LPUART1             = 20U,         /**< LPUART1 */
    kRDC_Periph_LPUART2             = 21U,         /**< LPUART2 */
    kRDC_Periph_LPUART3             = 22U,         /**< LPUART3 */
    kRDC_Periph_LPUART4             = 23U,         /**< LPUART4 */
    kRDC_Periph_LPUART5             = 24U,         /**< LPUART5 */
    kRDC_Periph_LPUART6             = 25U,         /**< LPUART6 */
    kRDC_Periph_LPUART7             = 26U,         /**< LPUART7 */
    kRDC_Periph_LPUART8             = 27U,         /**< LPUART8 */
    kRDC_Periph_LPUART9             = 28U,         /**< LPUART9 */
    kRDC_Periph_LPUART10            = 29U,         /**< LPUART10 */
    kRDC_Periph_FLEXIO1             = 30U,         /**< FlexIO1 */
    kRDC_Periph_FLEXIO2             = 31U,         /**< FlexIO2 */
    kRDC_Periph_CAN1                = 32U,         /**< CAN1 */
    kRDC_Periph_CAN2                = 33U,         /**< CAN2 */
    kRDC_Periph_PIT1                = 34U,         /**< PIT1 */
    kRDC_Periph_KPP                 = 35U,         /**< KPP */
    kRDC_Periph_IOMUXC_GPR          = 36U,         /**< IOMUXC_GPR */
    kRDC_Periph_IOMUXC              = 37U,         /**< IOMUXC */
    kRDC_Periph_GPT1                = 38U,         /**< GPT1 */
    kRDC_Periph_GPT2                = 39U,         /**< GPT2 */
    kRDC_Periph_GPT3                = 40U,         /**< GPT3 */
    kRDC_Periph_GPT4                = 41U,         /**< GPT4 */
    kRDC_Periph_GPT5                = 42U,         /**< GPT5 */
    kRDC_Periph_GPT6                = 43U,         /**< GPT6 */
    kRDC_Periph_LPI2C1              = 44U,         /**< LPI2C1 */
    kRDC_Periph_LPI2C2              = 45U,         /**< LPI2C2 */
    kRDC_Periph_LPI2C3              = 46U,         /**< LPI2C3 */
    kRDC_Periph_LPI2C4              = 47U,         /**< LPI2C4 */
    kRDC_Periph_LPSPI1              = 48U,         /**< LPSPI1 */
    kRDC_Periph_LPSPI2              = 49U,         /**< LPSPI2 */
    kRDC_Periph_LPSPI3              = 50U,         /**< LPSPI3 */
    kRDC_Periph_LPSPI4              = 51U,         /**< LPSPI4 */
    kRDC_Periph_GPIO_1_6            = 52U,         /**< GPIO_1_6 */
    kRDC_Periph_CCM_OBS             = 53U,         /**< CCM_OBS */
    kRDC_Periph_SIM1                = 54U,         /**< SIM1 */
    kRDC_Periph_SIM2                = 55U,         /**< SIM2 */
    kRDC_Periph_QTIMER1             = 56U,         /**< QTimer1 */
    kRDC_Periph_QTIMER2             = 57U,         /**< QTimer2 */
    kRDC_Periph_QTIMER3             = 58U,         /**< QTimer3 */
    kRDC_Periph_QTIMER4             = 59U,         /**< QTimer4 */
    kRDC_Periph_ENC1                = 60U,         /**< ENC1 */
    kRDC_Periph_ENC2                = 61U,         /**< ENC2 */
    kRDC_Periph_ENC3                = 62U,         /**< ENC3 */
    kRDC_Periph_ENC4                = 63U,         /**< ENC4 */
    kRDC_Periph_FLEXPWM1            = 64U,         /**< FLEXPWM1 */
    kRDC_Periph_FLEXPWM2            = 65U,         /**< FLEXPWM2 */
    kRDC_Periph_FLEXPWM3            = 66U,         /**< FLEXPWM3 */
    kRDC_Periph_FLEXPWM4            = 67U,         /**< FLEXPWM4 */
    kRDC_Periph_CAAM_2              = 68U,         /**< CAAM_2 */
    kRDC_Periph_CAAM_3              = 69U,         /**< CAAM_3 */
    kRDC_Periph_ACMP1               = 70U,         /**< ACMP1 */
    kRDC_Periph_ACMP2               = 71U,         /**< ACMP2 */
    kRDC_Periph_ACMP3               = 72U,         /**< ACMP3 */
    kRDC_Periph_ACMP4               = 73U,         /**< ACMP4 */
    kRDC_Periph_CAAM                = 74U,         /**< CAAM */
    kRDC_Periph_SPDIF               = 75U,         /**< SPDIF */
    kRDC_Periph_SAI1                = 76U,         /**< SAI1 */
    kRDC_Periph_SAI2                = 77U,         /**< SAI2 */
    kRDC_Periph_SAI3                = 78U,         /**< SAI3 */
    kRDC_Periph_ASRC                = 79U,         /**< ASRC */
    kRDC_Periph_USDHC1              = 80U,         /**< USDHC1 */
    kRDC_Periph_USDHC2              = 81U,         /**< USDHC2 */
    kRDC_Periph_ENET_1G             = 82U,         /**< ENET_1G */
    kRDC_Periph_ENET                = 83U,         /**< ENET */
    kRDC_Periph_USB_PL301           = 84U,         /**< USB_PL301 */
    kRDC_Periph_USBPHY2             = 85U,         /**< USBPHY2 */
    kRDC_Periph_USB_OTG2            = 85U,         /**< USB_OTG2 */
    kRDC_Periph_USBPHY1             = 86U,         /**< USBPHY1 */
    kRDC_Periph_USB_OTG1            = 86U,         /**< USB_OTG1 */
    kRDC_Periph_ENET_QOS            = 87U,         /**< ENET_QOS */
    kRDC_Periph_CAAM_5              = 88U,         /**< CAAM_5 */
    kRDC_Periph_LCDIF2              = 91U,         /**< LCDIF2 */
    kRDC_Periph_MIPI_DSI            = 92U,         /**< MIPI_DSI */
    kRDC_Periph_MIPI_CSI            = 93U,         /**< MIPI_CSI */
    kRDC_Periph_VIDEO_MUX           = 95U,         /**< VIDEO_MUX */
    kRDC_Periph_PGMC_SRC_GPC        = 96U,         /**< PGMC_SRC_GPC */
    kRDC_Periph_IOMUXC_LPSR         = 97U,         /**< IOMUXC_LPSR */
    kRDC_Periph_IOMUXC_LPSR_GPR     = 98U,         /**< IOMUXC_LPSR_GPR */
    kRDC_Periph_WDOG4               = 99U,         /**< WDOG4 */
    kRDC_Periph_DMAMUX_LPSR         = 100U,        /**< DMAMUX_LPSR */
    kRDC_Periph_EDMA_LPSR           = 100U,        /**< EDMA_LPSR */
    kRDC_Periph_Reserved            = 101U,        /**< Reserved */
    kRDC_Periph_MIC                 = 102U,        /**< MIC */
    kRDC_Periph_LPUART11            = 103U,        /**< LPUART11 */
    kRDC_Periph_LPUART12            = 104U,        /**< LPUART12 */
    kRDC_Periph_LPSPI5              = 105U,        /**< LPSPI5 */
    kRDC_Periph_LPSPI6              = 106U,        /**< LPSPI6 */
    kRDC_Periph_LPI2C5              = 107U,        /**< LPI2C5 */
    kRDC_Periph_LPI2C6              = 108U,        /**< LPI2C6 */
    kRDC_Periph_CAN3                = 109U,        /**< CAN3 */
    kRDC_Periph_SAI4                = 110U,        /**< SAI4 */
    kRDC_Periph_SEMA1               = 111U,        /**< SEMA1 */
    kRDC_Periph_GPIO_7_12           = 112U,        /**< GPIO_7_12 */
    kRDC_Periph_KEY_MANAGER         = 113U,        /**< KEY_MANAGER */
    kRDC_Periph_ANATOP              = 114U,        /**< ANATOP */
    kRDC_Periph_SNVS_HP_WRAPPER     = 115U,        /**< SNVS_HP_WRAPPER */
    kRDC_Periph_IOMUXC_SNVS         = 116U,        /**< IOMUXC_SNVS */
    kRDC_Periph_IOMUXC_SNVS_GPR     = 117U,        /**< IOMUXC_SNVS_GPR */
    kRDC_Periph_SNVS_SRAM           = 118U,        /**< SNVS_SRAM */
    kRDC_Periph_GPIO13              = 119U,        /**< GPIO13 */
    kRDC_Periph_ROMCP               = 120U,        /**< ROMCP */
    kRDC_Periph_DCDC                = 121U,        /**< DCDC */
    kRDC_Periph_OCOTP_CTRL_WRAPPER  = 122U,        /**< OCOTP_CTRL_WRAPPER */
    kRDC_Periph_PIT2                = 123U,        /**< PIT2 */
    kRDC_Periph_SSARC               = 124U,        /**< SSARC */
    kRDC_Periph_CCM                 = 125U,        /**< CCM */
    kRDC_Periph_CAAM_6              = 126U,        /**< CAAM_6 */
    kRDC_Periph_CAAM_7              = 127U,        /**< CAAM_7 */
    kRDC_Periph_CSI                 = 89U,         /**< CSI */
    kRDC_Periph_LCDIF1              = 90U,         /**< LCDIF1 */
    kRDC_Periph_PXP                 = 94U,         /**< PXP */
} rdc_periph_t;

/* @} */
#endif /* RDC_PERIPH_T_ */


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
   -- RDC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RDC_Peripheral_Access_Layer RDC Peripheral Access Layer
 * @{
 */

/** RDC - Size of Registers Arrays */
#define RDC_MDA_COUNT                             12u
#define RDC_PDAP_COUNT                            128u
#define RDC_MR_COUNT                              59u

/** RDC - Register Layout Typedef */
typedef struct {
  __I  uint32_t VIR;                               /**< Version Information, offset: 0x0 */
       uint8_t RESERVED_0[32];
  __IO uint32_t STAT;                              /**< Status, offset: 0x24 */
  __IO uint32_t INTCTRL;                           /**< Interrupt and Control, offset: 0x28 */
  __IO uint32_t INTSTAT;                           /**< Interrupt Status, offset: 0x2C */
       uint8_t RESERVED_1[464];
  __IO uint32_t MDA[RDC_MDA_COUNT];                /**< Master Domain Assignment, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_2[464];
  __IO uint32_t PDAP[RDC_PDAP_COUNT];              /**< Peripheral Domain Access Permissions, array offset: 0x400, array step: 0x4 */
       uint8_t RESERVED_3[512];
  struct {                                         /* offset: 0x800, array step: 0x10 */
    __IO uint32_t MRSA;                              /**< Memory Region Start Address, array offset: 0x800, array step: 0x10 */
    __IO uint32_t MREA;                              /**< Memory Region End Address, array offset: 0x804, array step: 0x10 */
    __IO uint32_t MRC;                               /**< Memory Region Control, array offset: 0x808, array step: 0x10 */
    __IO uint32_t MRVS;                              /**< Memory Region Violation Status, array offset: 0x80C, array step: 0x10 */
  } MR[RDC_MR_COUNT];
} RDC_Type;

/* ----------------------------------------------------------------------------
   -- RDC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RDC_Register_Masks RDC Register Masks
 * @{
 */

/*! @name VIR - Version Information */
/*! @{ */

#define RDC_VIR_NDID_MASK                        (0xFU)
#define RDC_VIR_NDID_SHIFT                       (0U)
/*! NDID - Number of Domains */
#define RDC_VIR_NDID(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_VIR_NDID_SHIFT)) & RDC_VIR_NDID_MASK)

#define RDC_VIR_NMSTR_MASK                       (0xFF0U)
#define RDC_VIR_NMSTR_SHIFT                      (4U)
/*! NMSTR - Number of Masters */
#define RDC_VIR_NMSTR(x)                         (((uint32_t)(((uint32_t)(x)) << RDC_VIR_NMSTR_SHIFT)) & RDC_VIR_NMSTR_MASK)

#define RDC_VIR_NPER_MASK                        (0xFF000U)
#define RDC_VIR_NPER_SHIFT                       (12U)
/*! NPER - Number of Peripherals */
#define RDC_VIR_NPER(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_VIR_NPER_SHIFT)) & RDC_VIR_NPER_MASK)

#define RDC_VIR_NRGN_MASK                        (0xFF00000U)
#define RDC_VIR_NRGN_SHIFT                       (20U)
/*! NRGN - Number of Memory Regions */
#define RDC_VIR_NRGN(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_VIR_NRGN_SHIFT)) & RDC_VIR_NRGN_MASK)
/*! @} */

/*! @name STAT - Status */
/*! @{ */

#define RDC_STAT_DID_MASK                        (0xFU)
#define RDC_STAT_DID_SHIFT                       (0U)
/*! DID - Domain ID */
#define RDC_STAT_DID(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_STAT_DID_SHIFT)) & RDC_STAT_DID_MASK)

#define RDC_STAT_PDS_MASK                        (0x100U)
#define RDC_STAT_PDS_SHIFT                       (8U)
/*! PDS - Power Domain Status
 *  0b0..Power Down Domain is OFF
 *  0b1..Power Down Domain is ON
 */
#define RDC_STAT_PDS(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_STAT_PDS_SHIFT)) & RDC_STAT_PDS_MASK)
/*! @} */

/*! @name INTCTRL - Interrupt and Control */
/*! @{ */

#define RDC_INTCTRL_RCI_EN_MASK                  (0x1U)
#define RDC_INTCTRL_RCI_EN_SHIFT                 (0U)
/*! RCI_EN - Restoration Complete Interrupt
 *  0b0..Interrupt Disabled
 *  0b1..Interrupt Enabled
 */
#define RDC_INTCTRL_RCI_EN(x)                    (((uint32_t)(((uint32_t)(x)) << RDC_INTCTRL_RCI_EN_SHIFT)) & RDC_INTCTRL_RCI_EN_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt Status */
/*! @{ */

#define RDC_INTSTAT_INT_MASK                     (0x1U)
#define RDC_INTSTAT_INT_SHIFT                    (0U)
/*! INT - Interrupt Status
 *  0b0..No Interrupt Pending
 *  0b1..Interrupt Pending
 */
#define RDC_INTSTAT_INT(x)                       (((uint32_t)(((uint32_t)(x)) << RDC_INTSTAT_INT_SHIFT)) & RDC_INTSTAT_INT_MASK)
/*! @} */

/*! @name MDA - Master Domain Assignment */
/*! @{ */

#define RDC_MDA_DID_MASK                         (0x3U)
#define RDC_MDA_DID_SHIFT                        (0U)
/*! DID - Domain ID
 *  0b00..Master assigned to Processing Domain 0
 *  0b01..Master assigned to Processing Domain 1
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define RDC_MDA_DID(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MDA_DID_SHIFT)) & RDC_MDA_DID_MASK)

#define RDC_MDA_LCK_MASK                         (0x80000000U)
#define RDC_MDA_LCK_SHIFT                        (31U)
/*! LCK - Assignment Lock
 *  0b0..Not Locked
 *  0b1..Locked
 */
#define RDC_MDA_LCK(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MDA_LCK_SHIFT)) & RDC_MDA_LCK_MASK)
/*! @} */

/*! @name PDAP - Peripheral Domain Access Permissions */
/*! @{ */

#define RDC_PDAP_D0W_MASK                        (0x1U)
#define RDC_PDAP_D0W_SHIFT                       (0U)
/*! D0W - Domain 0 Write Access
 *  0b0..No Write Access
 *  0b1..Write Access Allowed
 */
#define RDC_PDAP_D0W(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_PDAP_D0W_SHIFT)) & RDC_PDAP_D0W_MASK)

#define RDC_PDAP_D0R_MASK                        (0x2U)
#define RDC_PDAP_D0R_SHIFT                       (1U)
/*! D0R - Domain 0 Read Access
 *  0b0..No Read Access
 *  0b1..Read Access Allowed
 */
#define RDC_PDAP_D0R(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_PDAP_D0R_SHIFT)) & RDC_PDAP_D0R_MASK)

#define RDC_PDAP_D1W_MASK                        (0x4U)
#define RDC_PDAP_D1W_SHIFT                       (2U)
/*! D1W - Domain 1 Write Access
 *  0b0..No Write Access
 *  0b1..Write Access Allowed
 */
#define RDC_PDAP_D1W(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_PDAP_D1W_SHIFT)) & RDC_PDAP_D1W_MASK)

#define RDC_PDAP_D1R_MASK                        (0x8U)
#define RDC_PDAP_D1R_SHIFT                       (3U)
/*! D1R - Domain 1 Read Access
 *  0b0..No Read Access
 *  0b1..Read Access Allowed
 */
#define RDC_PDAP_D1R(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_PDAP_D1R_SHIFT)) & RDC_PDAP_D1R_MASK)

#define RDC_PDAP_SREQ_MASK                       (0x40000000U)
#define RDC_PDAP_SREQ_SHIFT                      (30U)
/*! SREQ - Semaphore Required
 *  0b0..Semaphores have no effect
 *  0b1..Semaphores are enforced
 */
#define RDC_PDAP_SREQ(x)                         (((uint32_t)(((uint32_t)(x)) << RDC_PDAP_SREQ_SHIFT)) & RDC_PDAP_SREQ_MASK)

#define RDC_PDAP_LCK_MASK                        (0x80000000U)
#define RDC_PDAP_LCK_SHIFT                       (31U)
/*! LCK - Peripheral Permissions Lock
 *  0b0..Not Locked
 *  0b1..Locked
 */
#define RDC_PDAP_LCK(x)                          (((uint32_t)(((uint32_t)(x)) << RDC_PDAP_LCK_SHIFT)) & RDC_PDAP_LCK_MASK)
/*! @} */

/*! @name MRSA - Memory Region Start Address */
/*! @{ */

#define RDC_MRSA_SADR_MASK                       (0xFFFFFF80U)
#define RDC_MRSA_SADR_SHIFT                      (7U)
/*! SADR - Start address for memory region */
#define RDC_MRSA_SADR(x)                         (((uint32_t)(((uint32_t)(x)) << RDC_MRSA_SADR_SHIFT)) & RDC_MRSA_SADR_MASK)
/*! @} */

/* The count of RDC_MRSA */
#define RDC_MRSA_COUNT                           (59U)

/*! @name MREA - Memory Region End Address */
/*! @{ */

#define RDC_MREA_EADR_MASK                       (0xFFFFFF80U)
#define RDC_MREA_EADR_SHIFT                      (7U)
/*! EADR - Upper bound for memory region */
#define RDC_MREA_EADR(x)                         (((uint32_t)(((uint32_t)(x)) << RDC_MREA_EADR_SHIFT)) & RDC_MREA_EADR_MASK)
/*! @} */

/* The count of RDC_MREA */
#define RDC_MREA_COUNT                           (59U)

/*! @name MRC - Memory Region Control */
/*! @{ */

#define RDC_MRC_D0W_MASK                         (0x1U)
#define RDC_MRC_D0W_SHIFT                        (0U)
/*! D0W - Domain 0 Write Access to Region
 *  0b0..Processing Domain 0 does not have Write access to the memory region
 *  0b1..Processing Domain 0 has Write access to the memory region
 */
#define RDC_MRC_D0W(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MRC_D0W_SHIFT)) & RDC_MRC_D0W_MASK)

#define RDC_MRC_D0R_MASK                         (0x2U)
#define RDC_MRC_D0R_SHIFT                        (1U)
/*! D0R - Domain 0 Read Access to Region
 *  0b0..Processing Domain 0 does not have Read access to the memory region
 *  0b1..Processing Domain 0 has Read access to the memory region
 */
#define RDC_MRC_D0R(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MRC_D0R_SHIFT)) & RDC_MRC_D0R_MASK)

#define RDC_MRC_D1W_MASK                         (0x4U)
#define RDC_MRC_D1W_SHIFT                        (2U)
/*! D1W - Domain 1 Write Access to Region
 *  0b0..Processing Domain 1 does not have Write access to the memory region
 *  0b1..Processing Domain 1 has Write access to the memory region
 */
#define RDC_MRC_D1W(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MRC_D1W_SHIFT)) & RDC_MRC_D1W_MASK)

#define RDC_MRC_D1R_MASK                         (0x8U)
#define RDC_MRC_D1R_SHIFT                        (3U)
/*! D1R - Domain 1 Read Access to Region
 *  0b0..Processing Domain 1 does not have Read access to the memory region
 *  0b1..Processing Domain 1 has Read access to the memory region
 */
#define RDC_MRC_D1R(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MRC_D1R_SHIFT)) & RDC_MRC_D1R_MASK)

#define RDC_MRC_ENA_MASK                         (0x40000000U)
#define RDC_MRC_ENA_SHIFT                        (30U)
/*! ENA - Region Enable
 *  0b0..Memory region is not defined or restricted.
 *  0b1..Memory boundaries, domain permissions and controls are in effect.
 */
#define RDC_MRC_ENA(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MRC_ENA_SHIFT)) & RDC_MRC_ENA_MASK)

#define RDC_MRC_LCK_MASK                         (0x80000000U)
#define RDC_MRC_LCK_SHIFT                        (31U)
/*! LCK - Region Lock
 *  0b0..No Lock. All fields in this register may be modified.
 *  0b1..Locked. No fields in this register may be modified except ENA, which may be set but not cleared.
 */
#define RDC_MRC_LCK(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MRC_LCK_SHIFT)) & RDC_MRC_LCK_MASK)
/*! @} */

/* The count of RDC_MRC */
#define RDC_MRC_COUNT                            (59U)

/*! @name MRVS - Memory Region Violation Status */
/*! @{ */

#define RDC_MRVS_VDID_MASK                       (0x3U)
#define RDC_MRVS_VDID_SHIFT                      (0U)
/*! VDID - Violating Domain ID
 *  0b00..Processing Domain 0
 *  0b01..Processing Domain 1
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define RDC_MRVS_VDID(x)                         (((uint32_t)(((uint32_t)(x)) << RDC_MRVS_VDID_SHIFT)) & RDC_MRVS_VDID_MASK)

#define RDC_MRVS_AD_MASK                         (0x10U)
#define RDC_MRVS_AD_SHIFT                        (4U)
/*! AD - Access Denied */
#define RDC_MRVS_AD(x)                           (((uint32_t)(((uint32_t)(x)) << RDC_MRVS_AD_SHIFT)) & RDC_MRVS_AD_MASK)

#define RDC_MRVS_VADR_MASK                       (0xFFFFFFE0U)
#define RDC_MRVS_VADR_SHIFT                      (5U)
/*! VADR - Violating Address */
#define RDC_MRVS_VADR(x)                         (((uint32_t)(((uint32_t)(x)) << RDC_MRVS_VADR_SHIFT)) & RDC_MRVS_VADR_MASK)
/*! @} */

/* The count of RDC_MRVS */
#define RDC_MRVS_COUNT                           (59U)


/*!
 * @}
 */ /* end of group RDC_Register_Masks */


/*!
 * @}
 */ /* end of group RDC_Peripheral_Access_Layer */


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


#endif  /* PERI_RDC_H_ */

