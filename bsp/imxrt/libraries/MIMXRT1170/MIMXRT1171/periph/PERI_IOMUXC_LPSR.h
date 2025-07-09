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
**         CMSIS Peripheral Access Layer for IOMUXC_LPSR
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
 * @file PERI_IOMUXC_LPSR.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for IOMUXC_LPSR
 *
 * CMSIS Peripheral Access Layer for IOMUXC_LPSR
 */

#if !defined(PERI_IOMUXC_LPSR_H_)
#define PERI_IOMUXC_LPSR_H_                      /**< Symbol preventing repeated inclusion */

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
#if !defined(IOMUXC_LPSR_SW_MUX_CTL_PAD_T_)
#define IOMUXC_LPSR_SW_MUX_CTL_PAD_T_
/*!
 * @addtogroup iomuxc_lpsr_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC_LPSR SW_MUX_CTL_PAD
 *
 * Defines the enumeration for the IOMUXC_LPSR SW_MUX_CTL_PAD collections.
 */
typedef enum _iomuxc_lpsr_sw_mux_ctl_pad
{
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_00 = 0U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_01 = 1U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_02 = 2U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_03 = 3U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_04 = 4U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_05 = 5U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_06 = 6U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_07 = 7U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_08 = 8U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_09 = 9U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_10 = 10U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_11 = 11U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_12 = 12U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_13 = 13U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_14 = 14U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_15 = 15U, /**< IOMUXC SW_MUX_CTL_PAD index */
} iomuxc_lpsr_sw_mux_ctl_pad_t;

/* @} */
#endif /* IOMUXC_LPSR_SW_MUX_CTL_PAD_T_ */

#if !defined(IOMUXC_LPSR_SW_PAD_CTL_PAD_T_)
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_T_
/*!
 * @addtogroup iomuxc_lpsr_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC_LPSR SW_PAD_CTL_PAD
 *
 * Defines the enumeration for the IOMUXC_LPSR SW_PAD_CTL_PAD collections.
 */
typedef enum _iomuxc_lpsr_sw_pad_ctl_pad
{
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_00 = 0U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_01 = 1U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_02 = 2U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_03 = 3U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_04 = 4U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_05 = 5U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_06 = 6U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_07 = 7U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_08 = 8U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_09 = 9U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_10 = 10U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_11 = 11U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_12 = 12U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_13 = 13U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_14 = 14U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO_LPSR_15 = 15U, /**< IOMUXC SW_PAD_CTL_PAD index */
} iomuxc_lpsr_sw_pad_ctl_pad_t;

/* @} */
#endif /* IOMUXC_LPSR_SW_PAD_CTL_PAD_T_ */

#if !defined(IOMUXC_LPSR_SELECT_INPUT_T_)
#define IOMUXC_LPSR_SELECT_INPUT_T_
/*!
 * @brief Enumeration for the IOMUXC_LPSR select input
 *
 * Defines the enumeration for the IOMUXC_LPSR select input collections.
 */
typedef enum _iomuxc_lpsr_select_input
{
    kIOMUXC_LPSR_CAN3_IPP_IND_CANRX_SELECT_INPUT = 0U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPI2C5_IPP_IND_LPI2C_SCL_SELECT_INPUT = 1U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPI2C5_IPP_IND_LPI2C_SDA_SELECT_INPUT = 2U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPI2C6_IPP_IND_LPI2C_SCL_SELECT_INPUT = 3U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPI2C6_IPP_IND_LPI2C_SDA_SELECT_INPUT = 4U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPSPI5_IPP_IND_LPSPI_PCS_SELECT_INPUT_0 = 5U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPSPI5_IPP_IND_LPSPI_SCK_SELECT_INPUT = 6U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPSPI5_IPP_IND_LPSPI_SDI_SELECT_INPUT = 7U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPSPI5_IPP_IND_LPSPI_SDO_SELECT_INPUT = 8U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPUART11_IPP_IND_LPUART_RXD_SELECT_INPUT = 9U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPUART11_IPP_IND_LPUART_TXD_SELECT_INPUT = 10U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPUART12_IPP_IND_LPUART_RXD_SELECT_INPUT = 11U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_LPUART12_IPP_IND_LPUART_TXD_SELECT_INPUT = 12U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_MIC_IPP_IND_MIC_PDM_BITSTREAM_SELECT_INPUT_0 = 13U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_MIC_IPP_IND_MIC_PDM_BITSTREAM_SELECT_INPUT_1 = 14U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_MIC_IPP_IND_MIC_PDM_BITSTREAM_SELECT_INPUT_2 = 15U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_MIC_IPP_IND_MIC_PDM_BITSTREAM_SELECT_INPUT_3 = 16U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_NMI_GLUE_IPP_IND_NMI_SELECT_INPUT = 17U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_SAI4_IPG_CLK_SAI_MCLK_SELECT_INPUT = 18U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_SAI4_IPP_IND_SAI_RXBCLK_SELECT_INPUT = 19U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_SAI4_IPP_IND_SAI_RXDATA_SELECT_INPUT_0 = 20U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_SAI4_IPP_IND_SAI_RXSYNC_SELECT_INPUT = 21U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_SAI4_IPP_IND_SAI_TXBCLK_SELECT_INPUT = 22U, /**< IOMUXC select input index */
    kIOMUXC_LPSR_SAI4_IPP_IND_SAI_TXSYNC_SELECT_INPUT = 23U, /**< IOMUXC select input index */
} iomuxc_lpsr_select_input_t;
#endif /* IOMUXC_LPSR_SELECT_INPUT_T_ */


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
   -- IOMUXC_LPSR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_LPSR_Peripheral_Access_Layer IOMUXC_LPSR Peripheral Access Layer
 * @{
 */

/** IOMUXC_LPSR - Size of Registers Arrays */
#define IOMUXC_LPSR_SW_MUX_CTL_PAD_COUNT          16u
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_COUNT          16u
#define IOMUXC_LPSR_SELECT_INPUT_COUNT            24u

/** IOMUXC_LPSR - Register Layout Typedef */
typedef struct {
  __IO uint32_t SW_MUX_CTL_PAD[IOMUXC_LPSR_SW_MUX_CTL_PAD_COUNT]; /**< SW_MUX_CTL_PAD_GPIO_LPSR_00 SW MUX Control Register..SW_MUX_CTL_PAD_GPIO_LPSR_15 SW MUX Control Register, array offset: 0x0, array step: 0x4 */
  __IO uint32_t SW_PAD_CTL_PAD[IOMUXC_LPSR_SW_PAD_CTL_PAD_COUNT]; /**< SW_PAD_CTL_PAD_GPIO_LPSR_00 SW PAD Control Register..SW_PAD_CTL_PAD_GPIO_LPSR_15 SW PAD Control Register, array offset: 0x40, array step: 0x4 */
  __IO uint32_t SELECT_INPUT[IOMUXC_LPSR_SELECT_INPUT_COUNT]; /**< CAN3_IPP_IND_CANRX_SELECT_INPUT DAISY Register..SAI4_IPP_IND_SAI_TXSYNC_SELECT_INPUT DAISY Register, array offset: 0x80, array step: 0x4 */
} IOMUXC_LPSR_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC_LPSR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_LPSR_Register_Masks IOMUXC_LPSR Register Masks
 * @{
 */

/*! @name SW_MUX_CTL_PAD - SW_MUX_CTL_PAD_GPIO_LPSR_00 SW MUX Control Register..SW_MUX_CTL_PAD_GPIO_LPSR_15 SW MUX Control Register */
/*! @{ */

#define IOMUXC_LPSR_SW_MUX_CTL_PAD_MUX_MODE_MASK (0xFU)
#define IOMUXC_LPSR_SW_MUX_CTL_PAD_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b0000..Select mux mode: ALT0 mux port: JTAG_MUX_TRSTB of instance: JTAG_MUX
 *  0b0001..Select mux mode: ALT1 mux port: LPUART11_CTS_B of instance: LPUART11
 *  0b0010..Select mux mode: ALT2 mux port: LPI2C6_SDA of instance: LPI2C6
 *  0b0011..Select mux mode: ALT3 mux port: MIC_BITSTREAM1 of instance: MIC
 *  0b0100..Select mux mode: ALT4 mux port: LPSPI6_SCK of instance: LPSPI6
 *  0b0101..Select mux mode: ALT5 mux port: GPIO_MUX6_IO10 of instance: GPIO_MUX6
 *  0b0110..Select mux mode: ALT6 mux port: LPI2C5_SCLS of instance: LPI2C5
 *  0b0111..Select mux mode: ALT7 mux port: SAI4_TX_SYNC of instance: SAI4
 *  0b1000..Select mux mode: ALT8 mux port: LPUART12_TXD of instance: LPUART12
 *  0b1010..Select mux mode: ALT10 mux port: GPIO12_IO10 of instance: GPIO12
 */
#define IOMUXC_LPSR_SW_MUX_CTL_PAD_MUX_MODE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_MUX_CTL_PAD_MUX_MODE_SHIFT)) & IOMUXC_LPSR_SW_MUX_CTL_PAD_MUX_MODE_MASK)

#define IOMUXC_LPSR_SW_MUX_CTL_PAD_SION_MASK     (0x10U)
#define IOMUXC_LPSR_SW_MUX_CTL_PAD_SION_SHIFT    (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_LPSR_00
 */
#define IOMUXC_LPSR_SW_MUX_CTL_PAD_SION(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_MUX_CTL_PAD_SION_SHIFT)) & IOMUXC_LPSR_SW_MUX_CTL_PAD_SION_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD - SW_PAD_CTL_PAD_GPIO_LPSR_00 SW PAD Control Register..SW_PAD_CTL_PAD_GPIO_LPSR_15 SW PAD Control Register */
/*! @{ */

#define IOMUXC_LPSR_SW_PAD_CTL_PAD_SRE_MASK      (0x1U)
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_SRE_SHIFT     (0U)
/*! SRE - Slew Rate Field
 *  0b0..Fast Slew Rate
 *  0b1..Slow Slew Rate
 */
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_SRE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_PAD_CTL_PAD_SRE_SHIFT)) & IOMUXC_LPSR_SW_PAD_CTL_PAD_SRE_MASK)

#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DSE_MASK      (0x2U)
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DSE_SHIFT     (1U)
/*! DSE - Drive Strength Field
 *  0b0..normal driver
 *  0b1..high driver
 */
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DSE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_PAD_CTL_PAD_DSE_SHIFT)) & IOMUXC_LPSR_SW_PAD_CTL_PAD_DSE_MASK)

#define IOMUXC_LPSR_SW_PAD_CTL_PAD_PUE_MASK      (0x4U)
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_PUE_SHIFT     (2U)
/*! PUE - Pull Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_PUE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_PAD_CTL_PAD_PUE_SHIFT)) & IOMUXC_LPSR_SW_PAD_CTL_PAD_PUE_MASK)

#define IOMUXC_LPSR_SW_PAD_CTL_PAD_PUS_MASK      (0x8U)
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_PUS_SHIFT     (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_PUS(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_PAD_CTL_PAD_PUS_SHIFT)) & IOMUXC_LPSR_SW_PAD_CTL_PAD_PUS_MASK)

#define IOMUXC_LPSR_SW_PAD_CTL_PAD_ODE_LPSR_MASK (0x20U)
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_ODE_LPSR_SHIFT (5U)
/*! ODE_LPSR - Open Drain LPSR Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_ODE_LPSR(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_PAD_CTL_PAD_ODE_LPSR_SHIFT)) & IOMUXC_LPSR_SW_PAD_CTL_PAD_ODE_LPSR_MASK)

#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_MASK      (0x30000000U)
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_SHIFT     (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_SHIFT)) & IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_MASK)

#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_LOCK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_SW_PAD_CTL_PAD_DWP_LOCK_MASK)
/*! @} */

/*! @name SELECT_INPUT - CAN3_IPP_IND_CANRX_SELECT_INPUT DAISY Register..SAI4_IPP_IND_SAI_TXSYNC_SELECT_INPUT DAISY Register */
/*! @{ */

#define IOMUXC_LPSR_SELECT_INPUT_DAISY_MASK      (0x3U)  /* Merged from fields with different position or width, of widths (1, 2), largest definition used */
#define IOMUXC_LPSR_SELECT_INPUT_DAISY_SHIFT     (0U)
/*! DAISY - Selecting Pads Involved in Daisy Chain.
 *  0b00..Selecting Pad: GPIO_LPSR_00 for Mode: ALT6
 *  0b01..Selecting Pad: GPIO_LPSR_06 for Mode: ALT3
 *  0b10..Selecting Pad: GPIO_LPSR_10 for Mode: ALT8
 */
#define IOMUXC_LPSR_SELECT_INPUT_DAISY(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_SELECT_INPUT_DAISY_SHIFT)) & IOMUXC_LPSR_SELECT_INPUT_DAISY_MASK)  /* Merged from fields with different position or width, of widths (1, 2), largest definition used */
/*! @} */


/*!
 * @}
 */ /* end of group IOMUXC_LPSR_Register_Masks */


/*!
 * @}
 */ /* end of group IOMUXC_LPSR_Peripheral_Access_Layer */


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


#endif  /* PERI_IOMUXC_LPSR_H_ */

