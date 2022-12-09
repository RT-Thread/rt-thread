/***************************************************************************//**
* \file cyhal_hw_resources.h
*
* \brief
* Provides struct definitions for configuration resources in the PDL.
*
********************************************************************************
* \copyright
* Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_hal_impl_availability HAL Driver Availability Macros
* \ingroup group_hal_impl
* \{
*/

#pragma once

#include "cy_pdl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Documented in cyhal.h
#define CYHAL_API_VERSION                   (2)

/** \cond INTERNAL */
#define _CYHAL_DRIVER_AVAILABLE_SCB         ((CY_IP_MXSCB_INSTANCES) > 0)

#if !defined(COMPONENT_CAT1D)

#define _CYHAL_DRIVER_AVAILABLE_ADC_SAR     ((CY_IP_MXS40PASS_SAR_INSTANCES) > 0)
#define _CYHAL_DRIVER_AVAILABLE_ADC_MIC     ((CY_IP_MXS40ADCMIC_INSTANCES) > 0)
#define _CYHAL_DRIVER_AVAILABLE_COMP_LP     ((CY_IP_MXLPCOMP_INSTANCES) > 0)
#define _CYHAL_DRIVER_AVAILABLE_COMP_CTB    (((CY_IP_MXS40PASS_INSTANCES) > 0) && ((CY_IP_MXS40PASS_CTB_INSTANCES) > 0))
#define _CYHAL_DRIVER_AVAILABLE_DMA_DMAC    (((CY_IP_M4CPUSS_DMAC_INSTANCES) > 0) || ((CY_IP_M7CPUSS_DMAC_INSTANCES) > 0) || ((CY_IP_MXAHBDMAC_INSTANCES) > 0))
#define _CYHAL_DRIVER_AVAILABLE_DMA_DW      (((CY_IP_M4CPUSS_DMA_INSTANCES) > 0) || ((CY_IP_M7CPUSS_DMA_INSTANCES) > 0) || ((CY_IP_MXDW_INSTANCES) > 0))

#define _CYHAL_DRIVER_AVAILABLE_PASS        ((CY_IP_MXS40PASS_INSTANCES) > 0)
#define _CYHAL_DRIVER_AVAILABLE_CRYPTO      (((CY_IP_MXCRYPTO_INSTANCES) > 0) || ((CY_IP_MXCRYPTOLITE_INSTANCES) > 0))
#if defined(CYHAL_UDB_SDIO)
#define _CYHAL_DRIVER_AVAILABLE_SDIO_UDB    (1)
#else
#define _CYHAL_DRIVER_AVAILABLE_SDIO_UDB    (0)
#endif
#if (!defined(CPUSS_FLASHC_PRESENT) || ((CPUSS_FLASHC_PRESENT) > 0))
#define _CYHAL_DRIVER_AVAILABLE_FLASH       (1)
#else
#define _CYHAL_DRIVER_AVAILABLE_FLASH       (0)
#endif
#define _CYHAL_DRIVER_AVAILABLE_TCPWM       ((CY_IP_MXTCPWM_INSTANCES) > 0)

#else

#define _CYHAL_DRIVER_AVAILABLE_ADC_SAR     (0)
#define _CYHAL_DRIVER_AVAILABLE_ADC_MIC     (0)
#define _CYHAL_DRIVER_AVAILABLE_DMA_DMAC    (0)
#define _CYHAL_DRIVER_AVAILABLE_DMA_DW      (0)
#define _CYHAL_DRIVER_AVAILABLE_COMP_LP     (0)
#define _CYHAL_DRIVER_AVAILABLE_COMP_CTB    (0)
#define _CYHAL_DRIVER_AVAILABLE_PASS        (0)
#define _CYHAL_DRIVER_AVAILABLE_CRYPTO      (0)
#define _CYHAL_DRIVER_AVAILABLE_SDIO_UDB    (0)
#define _CYHAL_DRIVER_AVAILABLE_FLASH       (0)
#define _CYHAL_DRIVER_AVAILABLE_TCPWM       (0)

#endif /* not COMPONENT_CAT1D or COMPONENTCAT1D */

/* CAT1C devices define _CYHAL_SRSS_NUM_PLL to be the macro that documents the number of 200MHz PLL's present */
#if defined(COMPONENT_CAT1C)
    #define SRSS_NUM_PLL200M SRSS_NUM_PLL
#endif

#if defined(COMPONENT_CAT1C) && (SRSS_HT_VARIANT)
    #define _CYHAL_SRSS_NUM_ILO 2U
#else
    #define _CYHAL_SRSS_NUM_ILO 1U
#endif

#define _CYHAL_SRSS_NUM_FAST (1 + CPUSS_CM7_1_PRESENT)
/** \endcond */

// Documented in cyhal.h
#define CYHAL_DRIVER_AVAILABLE_HWMGR        (1)
#define CYHAL_DRIVER_AVAILABLE_GPIO         (1)
#define CYHAL_DRIVER_AVAILABLE_INTERCONNECT (1)
#define CYHAL_DRIVER_AVAILABLE_CLOCK        (1)
#define CYHAL_DRIVER_AVAILABLE_SYSTEM       (1)

#define CYHAL_DRIVER_AVAILABLE_EZI2C        (_CYHAL_DRIVER_AVAILABLE_SCB) //SCB[x]_I2C
#define CYHAL_DRIVER_AVAILABLE_I2C          (_CYHAL_DRIVER_AVAILABLE_SCB) //SCB[x]_I2C
#define CYHAL_DRIVER_AVAILABLE_SPI          (_CYHAL_DRIVER_AVAILABLE_SCB) //SCB[x]_SPI
#define CYHAL_DRIVER_AVAILABLE_UART         (_CYHAL_DRIVER_AVAILABLE_SCB) //SCB[x]_UART
#define CYHAL_DRIVER_AVAILABLE_WDT          (1)

#if !defined(COMPONENT_CAT1D)

#define CYHAL_DRIVER_AVAILABLE_COMP         ((_CYHAL_DRIVER_AVAILABLE_COMP_LP) || (_CYHAL_DRIVER_AVAILABLE_COMP_CTB))
#define CYHAL_DRIVER_AVAILABLE_CRC          (((CY_IP_MXCRYPTO_INSTANCES) > 0) && (CPUSS_CRYPTO_CRC))
#define CYHAL_DRIVER_AVAILABLE_DAC          (((CY_IP_MXS40PASS_INSTANCES) > 0) && ((CY_IP_MXS40PASS_CTDAC_INSTANCES) > 0))
#define CYHAL_DRIVER_AVAILABLE_DMA          ((_CYHAL_DRIVER_AVAILABLE_DMA_DMAC) || (_CYHAL_DRIVER_AVAILABLE_DMA_DW))
#define CYHAL_DRIVER_AVAILABLE_FLASH        (_CYHAL_DRIVER_AVAILABLE_FLASH)
#define CYHAL_DRIVER_AVAILABLE_I2S          ((((CY_IP_MXAUDIOSS_INSTANCES) > 0) && (AUDIOSS_I2S || AUDIOSS0_I2S || AUDIOSS0_I2S_I2S)) || ((CY_IP_MXTDM_INSTANCES) > 0)) //AUDIOSS[x]_I2S
#define CYHAL_DRIVER_AVAILABLE_I2S_TX       (CYHAL_DRIVER_AVAILABLE_I2S)
#define CYHAL_DRIVER_AVAILABLE_I2S_RX       (CYHAL_DRIVER_AVAILABLE_I2S)
#define CYHAL_DRIVER_AVAILABLE_KEYSCAN      ((CY_IP_MXKEYSCAN_INSTANCES) > 0)
#define CYHAL_DRIVER_AVAILABLE_OPAMP        (((CY_IP_MXS40PASS_INSTANCES) > 0) && ((CY_IP_MXS40PASS_CTB_INSTANCES) > 0))
#define CYHAL_DRIVER_AVAILABLE_PDMPCM       ((((CY_IP_MXAUDIOSS_INSTANCES) > 0) && (AUDIOSS_PDM || AUDIOSS0_PDM || AUDIOSS0_PDM_PDM)) || ((CY_IP_MXPDM_INSTANCES) > 0)) //AUDIOSS[x]_PDM
#define CYHAL_DRIVER_AVAILABLE_PWM          (_CYHAL_DRIVER_AVAILABLE_TCPWM)
#define CYHAL_DRIVER_AVAILABLE_QUADDEC      (_CYHAL_DRIVER_AVAILABLE_TCPWM)
#define CYHAL_DRIVER_AVAILABLE_QSPI         ((CY_IP_MXSMIF_INSTANCES) > 0)
#define CYHAL_DRIVER_AVAILABLE_SYSPM        (1)
#define CYHAL_DRIVER_AVAILABLE_RTC          ((((CY_IP_MXS40SSRSS_INSTANCES) > 0) || ((CY_IP_MXS40SRSS_INSTANCES) > 0)) && ((SRSS_BACKUP_PRESENT) > 0))
#define CYHAL_DRIVER_AVAILABLE_TDM          ((((CY_IP_MXAUDIOSS_INSTANCES) > 0) && (AUDIOSS_I2S || AUDIOSS0_I2S || AUDIOSS0_I2S_I2S)) || ((CY_IP_MXTDM_INSTANCES) > 0)) //AUDIOSS[x]_I2S
#define CYHAL_DRIVER_AVAILABLE_TDM_TX       (CYHAL_DRIVER_AVAILABLE_TDM)
#define CYHAL_DRIVER_AVAILABLE_TDM_RX       (CYHAL_DRIVER_AVAILABLE_TDM)
#define CYHAL_DRIVER_AVAILABLE_TIMER        (_CYHAL_DRIVER_AVAILABLE_TCPWM)
#define CYHAL_DRIVER_AVAILABLE_TRNG         ((((CY_IP_MXCRYPTO_INSTANCES) > 0) && ((CPUSS_CRYPTO_TR) > 0)) /*|| (((CY_IP_MXCRYPTOLITE_INSTANCES) > 0) && ((CRYPTO_TRNG_PRESENT) > 0))*/)
#define CYHAL_DRIVER_AVAILABLE_USB_DEV      ((CY_IP_MXUSBFS_INSTANCES) > 0)
#define CYHAL_DRIVER_AVAILABLE_LPTIMER      ((SRSS_NUM_MCWDT) > 0)

#if !defined(COMPONENT_CAT1C)
#define CYHAL_DRIVER_AVAILABLE_ADC          ((_CYHAL_DRIVER_AVAILABLE_ADC_SAR) || (_CYHAL_DRIVER_AVAILABLE_ADC_MIC))
#define CYHAL_DRIVER_AVAILABLE_SDHC         ((CY_IP_MXSDHC_INSTANCES) > 0)
#define CYHAL_DRIVER_AVAILABLE_SDIO         (((CY_IP_MXSDHC_INSTANCES) > 0) || (_CYHAL_DRIVER_AVAILABLE_SDIO_UDB))
#else
#define CYHAL_DRIVER_AVAILABLE_ADC          (0)
#define CYHAL_DRIVER_AVAILABLE_SDHC         (0)
#define CYHAL_DRIVER_AVAILABLE_SDIO         (0)
#endif /* not COMPONENT_CAT1C or other */

#else /* COMPONENT_CAT1D */

#define CYHAL_DRIVER_AVAILABLE_COMP         (0)
#define CYHAL_DRIVER_AVAILABLE_CRC          (0)
#define CYHAL_DRIVER_AVAILABLE_DAC          (0)
#define CYHAL_DRIVER_AVAILABLE_DMA          (0)
#define CYHAL_DRIVER_AVAILABLE_I2S          (0)
#define CYHAL_DRIVER_AVAILABLE_I2S_TX       (0)
#define CYHAL_DRIVER_AVAILABLE_I2S_RX       (0)
#define CYHAL_DRIVER_AVAILABLE_KEYSCAN      (0)
#define CYHAL_DRIVER_AVAILABLE_OPAMP        (0)
#define CYHAL_DRIVER_AVAILABLE_PDMPCM       (0)
#define CYHAL_DRIVER_AVAILABLE_SYSPM        (0)
#define CYHAL_DRIVER_AVAILABLE_RTC          (0)
#define CYHAL_DRIVER_AVAILABLE_TDM          (0)
#define CYHAL_DRIVER_AVAILABLE_TDM_TX       (0)
#define CYHAL_DRIVER_AVAILABLE_TDM_RX       (0)
#define CYHAL_DRIVER_AVAILABLE_TRNG         (0)
#define CYHAL_DRIVER_AVAILABLE_USB_DEV      (0)

#define CYHAL_DRIVER_AVAILABLE_ADC          (0)
#define CYHAL_DRIVER_AVAILABLE_FLASH        (0)
#define CYHAL_DRIVER_AVAILABLE_LPTIMER      (0)
#define CYHAL_DRIVER_AVAILABLE_PWM          (0)
#define CYHAL_DRIVER_AVAILABLE_QSPI         (0)
#define CYHAL_DRIVER_AVAILABLE_QUADDEC      (0)
#define CYHAL_DRIVER_AVAILABLE_SDHC         (0)
#define CYHAL_DRIVER_AVAILABLE_SDIO         (0)
#define CYHAL_DRIVER_AVAILABLE_TIMER        (0)

#endif /* not COMPONENT_CAT1D or other */

/** \} group_hal_impl_availability */
/**
* \addtogroup group_hal_impl_hw_types
* \ingroup group_hal_impl
* \{
*/


/* NOTE: Any changes made to this enum must also be made to the hardware manager resource tracking */
/** Resource types that the hardware manager supports */
typedef enum
{
    CYHAL_RSC_ADC,       /*!< Analog to digital converter */
    CYHAL_RSC_ADCMIC,    /*!< Analog to digital converter with Analog Mic support */
    CYHAL_RSC_BLESS,     /*!< Bluetooth communications block */
    CYHAL_RSC_CAN,       /*!< CAN communication block */
    CYHAL_RSC_CLKPATH,   /*!< Clock Path. DEPRECATED. */
    CYHAL_RSC_CLOCK,     /*!< Clock */
    CYHAL_RSC_CRYPTO,    /*!< Crypto hardware accelerator */
    CYHAL_RSC_DAC,       /*!< Digital to analog converter */
    CYHAL_RSC_DMA,       /*!< DMA controller */
    CYHAL_RSC_DW,        /*!< Datawire DMA controller */
    CYHAL_RSC_ETH,       /*!< Ethernet communications block */
    CYHAL_RSC_GPIO,      /*!< General purpose I/O pin */
    CYHAL_RSC_I2S,       /*!< I2S communications block */
    CYHAL_RSC_I3C,       /*!< I3C communications block */
    CYHAL_RSC_KEYSCAN,   /*!< KeyScan block */
    CYHAL_RSC_LCD,       /*!< Segment LCD controller */
    CYHAL_RSC_LIN,       /*!< LIN communications block */
    CYHAL_RSC_LPCOMP,    /*!< Low power comparator */
    CYHAL_RSC_LPTIMER,   /*!< Low power timer */
    CYHAL_RSC_OPAMP,     /*!< Opamp */
    CYHAL_RSC_PDM,       /*!< PCM/PDM communications block */
    CYHAL_RSC_SMIF,      /*!< Quad-SPI communications block */
    CYHAL_RSC_RTC,       /*!< Real time clock */
    CYHAL_RSC_SCB,       /*!< Serial Communications Block */
    CYHAL_RSC_SDHC,      /*!< SD Host Controller */
    CYHAL_RSC_SDIODEV,   /*!< SDIO Device Block */
    CYHAL_RSC_TCPWM,     /*!< Timer/Counter/PWM block */
    CYHAL_RSC_TDM,       /*!< TDM block */
    CYHAL_RSC_UDB,       /*!< UDB Array */
    CYHAL_RSC_USB,       /*!< USB communication block */
    CYHAL_RSC_INVALID,   /*!< Placeholder for invalid type */
} cyhal_resource_t;

/** \cond INTERNAL */
    /* Extracts the divider from the Peri group block number */
    #define _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(block)     ((cy_en_divider_types_t)((block) & 0x03))
    #define _CYHAL_PERIPHERAL_GROUP_GET_GROUP(block)            ((block) >> 2)
// TODO: CAT1D to be confirmed here
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    /* Converts the group/div pair into a unique block number. */
    #define _CYHAL_PERIPHERAL_GROUP_ADJUST(group, div)        (((group) << 2) | (div))

    #define _CYHAL_CLOCK_BLOCK_PERI_GROUP(gr) \
        CYHAL_CLOCK_BLOCK_PERIPHERAL##gr##_8BIT = _CYHAL_PERIPHERAL_GROUP_ADJUST((gr), CY_SYSCLK_DIV_8_BIT),        /*!< 8bit Peripheral Divider Group 1 */ \
        CYHAL_CLOCK_BLOCK_PERIPHERAL##gr##_16BIT = _CYHAL_PERIPHERAL_GROUP_ADJUST((gr), CY_SYSCLK_DIV_16_BIT),      /*!< 16bit Peripheral Divider Group 1 */ \
        CYHAL_CLOCK_BLOCK_PERIPHERAL##gr##_16_5BIT = _CYHAL_PERIPHERAL_GROUP_ADJUST((gr), CY_SYSCLK_DIV_16_5_BIT),  /*!< 16.5bit Peripheral Divider Group 1 */ \
        CYHAL_CLOCK_BLOCK_PERIPHERAL##gr##_24_5BIT = _CYHAL_PERIPHERAL_GROUP_ADJUST((gr), CY_SYSCLK_DIV_24_5_BIT)   /*!< 24.5bit Peripheral Divider Group 1 */
#endif
/** \endcond */

/* NOTE: Any changes here must also be made in cyhal_hwmgr.c */
/** Enum for the different types of clocks that exist on the device. */
typedef enum
{
#if defined(COMPONENT_CAT1A)
    // The first four items are here for backwards compatability with old clock APIs
    CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT = CY_SYSCLK_DIV_8_BIT,        /*!< 8bit Peripheral Divider */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT = CY_SYSCLK_DIV_16_BIT,      /*!< 16bit Peripheral Divider */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT = CY_SYSCLK_DIV_16_5_BIT,  /*!< 16.5bit Peripheral Divider */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT = CY_SYSCLK_DIV_24_5_BIT,  /*!< 24.5bit Peripheral Divider */

    CYHAL_CLOCK_BLOCK_IMO,                                          /*!< Internal Main Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_ECO,                                          /*!< External Crystal Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_EXT,                                          /*!< External Input Clock */
    CYHAL_CLOCK_BLOCK_ALTHF,                                        /*!< Alternate High Frequency Input Clock */
    CYHAL_CLOCK_BLOCK_ALTLF,                                        /*!< Alternate Low Frequency Input Clock */
    CYHAL_CLOCK_BLOCK_ILO,                                          /*!< Internal Low Speed Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_PILO,                                         /*!< Precision ILO Input Clock */
    CYHAL_CLOCK_BLOCK_WCO,                                          /*!< Watch Crystal Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_MFO,                                          /*!< Medium Frequency Oscillator Clock */

    CYHAL_CLOCK_BLOCK_PATHMUX,                                      /*!< Path selection mux for input to FLL/PLLs */

    CYHAL_CLOCK_BLOCK_FLL,                                          /*!< Frequency-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_PLL,                                          /*!< Phase-Locked Loop Clock */

    CYHAL_CLOCK_BLOCK_LF,                                           /*!< Low Frequency Clock */
    CYHAL_CLOCK_BLOCK_MF,                                           /*!< Medium Frequency Clock */
    CYHAL_CLOCK_BLOCK_HF,                                           /*!< High Frequency Clock */

    CYHAL_CLOCK_BLOCK_PUMP,                                         /*!< Analog Pump Clock */
    CYHAL_CLOCK_BLOCK_BAK,                                          /*!< Backup Power Domain Clock */
    CYHAL_CLOCK_BLOCK_TIMER,                                        /*!< Timer Clock */
    CYHAL_CLOCK_BLOCK_ALT_SYS_TICK,                                 /*!< Alternative SysTick Clock */

    CYHAL_CLOCK_BLOCK_FAST,                                         /*!< Fast Clock for CM4 */
    CYHAL_CLOCK_BLOCK_PERI,                                         /*!< Peripheral Clock */
    CYHAL_CLOCK_BLOCK_SLOW,                                         /*!< Slow Clock for CM0+ */
#elif defined(COMPONENT_CAT1B)

    CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT = CY_SYSCLK_DIV_8_BIT,        /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_8_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT = CY_SYSCLK_DIV_16_BIT,      /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_16_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT = CY_SYSCLK_DIV_16_5_BIT,  /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_16_5_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT = CY_SYSCLK_DIV_24_5_BIT,  /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_24_5_BIT */

    // The first four items are here for backwards compatability with old clock APIs
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 1)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(0),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 2)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(1),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 3)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(2),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 4)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(3),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 5)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(4),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 6)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(5),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 7)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(6),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 8)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(7),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 9)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(8),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 10)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(9),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 11)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(10),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 12)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(11),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 13)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(12),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 14)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(13),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 15)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(14),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 16)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(15),
    #endif

    CYHAL_CLOCK_BLOCK_IHO,                                          /*!< Internal High Speed Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_IMO,                                          /*!< Internal Main Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_ECO,                                          /*!< External Crystal Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_EXT,                                          /*!< External Input Clock */
    CYHAL_CLOCK_BLOCK_ALTHF,                                        /*!< Alternate High Frequency Input Clock */
    CYHAL_CLOCK_BLOCK_ALTLF,                                        /*!< Alternate Low Frequency Input Clock */
    CYHAL_CLOCK_BLOCK_ILO,                                          /*!< Internal Low Speed Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_PILO,                                         /*!< Precision ILO Input Clock */
    CYHAL_CLOCK_BLOCK_WCO,                                          /*!< Watch Crystal Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_MFO,                                          /*!< Medium Frequency Oscillator Clock */

    CYHAL_CLOCK_BLOCK_PATHMUX,                                      /*!< Path selection mux for input to FLL/PLLs */

    CYHAL_CLOCK_BLOCK_FLL,                                          /*!< Frequency-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_PLL200,                                       /*!< 200MHz Phase-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_PLL400,                                       /*!< 400MHz Phase-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_ECO_PRESCALER,                                /*!< ECO Prescaler Divider */

    CYHAL_CLOCK_BLOCK_LF,                                           /*!< Low Frequency Clock */
    CYHAL_CLOCK_BLOCK_MF,                                           /*!< Medium Frequency Clock */
    CYHAL_CLOCK_BLOCK_HF,                                           /*!< High Frequency Clock */

    CYHAL_CLOCK_BLOCK_PUMP,                                         /*!< Analog Pump Clock */
    CYHAL_CLOCK_BLOCK_BAK,                                          /*!< Backup Power Domain Clock */
    CYHAL_CLOCK_BLOCK_ALT_SYS_TICK,                                 /*!< Alternative SysTick Clock */
    CYHAL_CLOCK_BLOCK_PERI,                                         /*!< Peripheral Clock Group */

#elif defined(COMPONENT_CAT1C)

    CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT = CY_SYSCLK_DIV_8_BIT,        /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_8_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT = CY_SYSCLK_DIV_16_BIT,      /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_16_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT = CY_SYSCLK_DIV_16_5_BIT,  /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_16_5_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT = CY_SYSCLK_DIV_24_5_BIT,  /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_24_5_BIT */

    // The first four items are here for backwards compatability with old clock APIs
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 1)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(0),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 2)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(1),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 3)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(2),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 4)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(3),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 5)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(4),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 6)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(5),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 7)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(6),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 8)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(7),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 9)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(8),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 10)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(9),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 11)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(10),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 12)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(11),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 13)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(12),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 14)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(13),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 15)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(14),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 16)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(15),
    #endif

    CYHAL_CLOCK_BLOCK_IMO,                                          /*!< Internal Main Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_ECO,                                          /*!< External Crystal Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_EXT,                                          /*!< External Input Clock */
    CYHAL_CLOCK_BLOCK_ILO,                                          /*!< Internal Low Speed Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_WCO,                                          /*!< Watch Crystal Oscillator Input Clock */

    CYHAL_CLOCK_BLOCK_PATHMUX,                                      /*!< Path selection mux for input to FLL/PLLs */

    CYHAL_CLOCK_BLOCK_FLL,                                          /*!< Frequency-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_PLL200,                                       /*!< 200MHz Phase-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_PLL400,                                       /*!< 400MHz Phase-Locked Loop Clock */

    CYHAL_CLOCK_BLOCK_LF,                                           /*!< Low Frequency Clock */
    CYHAL_CLOCK_BLOCK_HF,                                           /*!< High Frequency Clock */
    CYHAL_CLOCK_BLOCK_PUMP,                                         /*!< Analog Pump Clock */
    CYHAL_CLOCK_BLOCK_BAK,                                          /*!< Backup Power Domain Clock */
    CYHAL_CLOCK_BLOCK_ALT_SYS_TICK,                                 /*!< Alternative SysTick Clock */

    CYHAL_CLOCK_BLOCK_PERI,                                         /*!< Peripheral Clock Group */
    CYHAL_CLOCK_BLOCK_FAST,                                         /*!< Fast Clock for CM7 */
    CYHAL_CLOCK_BLOCK_SLOW,                                         /*!< Slow Clock for CM0+ */
    CYHAL_CLOCK_BLOCK_MEM,                                          /*!< CLK MEM */
    CYHAL_CLOCK_BLOCK_TIMER,                                        /*!< CLK Timer */

#elif defined(COMPONENT_CAT1D)

    CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT = CY_SYSCLK_DIV_8_BIT,        /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_8_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT = CY_SYSCLK_DIV_16_BIT,      /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_16_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT = CY_SYSCLK_DIV_16_5_BIT,  /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_16_5_BIT */
    CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT = CY_SYSCLK_DIV_24_5_BIT,  /*!< Equivalent to CYHAL_CLOCK_BLOCK_PERIPHERAL0_24_5_BIT */

    // The first four items are here for backwards compatability with old clock APIs
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 1)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(0),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 2)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(1),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 3)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(2),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 4)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(3),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 5)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(4),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 6)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(5),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 7)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(6),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 8)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(7),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 9)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(8),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 10)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(9),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 11)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(10),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 12)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(11),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 13)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(12),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 14)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(13),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 15)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(14),
    #endif
    #if (PERI_PERI_PCLK_PCLK_GROUP_NR >= 16)
    _CYHAL_CLOCK_BLOCK_PERI_GROUP(15),
    #endif

    CYHAL_CLOCK_BLOCK_IMO,                                          /*!< Internal Main Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_ECO,                                          /*!< External Crystal Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_EXT,                                          /*!< External Input Clock */
    CYHAL_CLOCK_BLOCK_ILO,                                          /*!< Internal Low Speed Oscillator Input Clock */
    CYHAL_CLOCK_BLOCK_ILO1,
    CYHAL_CLOCK_BLOCK_WCO,                                          /*!< Watch Crystal Oscillator Input Clock */

    CYHAL_CLOCK_BLOCK_PATHMUX,                                      /*!< Path selection mux for input to FLL/PLLs */

    CYHAL_CLOCK_BLOCK_FLL,                                          /*!< Frequency-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_PLL200,                                       /*!< 200MHz Phase-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_PLL400,                                       /*!< 400MHz Phase-Locked Loop Clock */
    CYHAL_CLOCK_BLOCK_ECO_PRESCALER,                                /*!< ECO Prescaler Divider */

    CYHAL_CLOCK_BLOCK_LF,                                           /*!< Low Frequency Clock */
    CYHAL_CLOCK_BLOCK_HF,                                           /*!< High Frequency Clock */
    CYHAL_CLOCK_BLOCK_PUMP,                                         /*!< Analog Pump Clock */
    CYHAL_CLOCK_BLOCK_BAK,                                          /*!< Backup Power Domain Clock */
    CYHAL_CLOCK_BLOCK_ALT_SYS_TICK,                                 /*!< Alternative SysTick Clock */

    CYHAL_CLOCK_BLOCK_PERI,                                         /*!< Peripheral Clock Group */
    CYHAL_CLOCK_BLOCK_FAST,                                         /*!< Fast Clock for CM7 */
    CYHAL_CLOCK_BLOCK_SLOW,                                         /*!< Slow Clock for CM0+ */
    CYHAL_CLOCK_BLOCK_TIMER,                                        /*!< CLK TIMER */
    CYHAL_CLOCK_BLOCK_MEM,                                          /*!< CLK MEM */
#endif
} cyhal_clock_block_t;

/** @brief Clock object
  * Application code should not rely on the specific contents of this struct.
  * They are considered an implementation detail which is subject to change
  * between platforms and/or HAL releases. */
typedef struct
{
    cyhal_clock_block_t     block;
    uint8_t                 channel;
    bool                    reserved;
    const void*             funcs;
} cyhal_clock_t;

/**
  * @brief Represents a particular instance of a resource on the chip.
  * Application code should not rely on the specific contents of this struct.
  * They are considered an implementation detail which is subject to change
  * between platforms and/or HAL releases.
  */
typedef struct
{
    cyhal_resource_t type;      //!< The resource block type
    uint8_t          block_num; //!< The resource block index
    /**
      * The channel number, if the resource type defines multiple channels
      * per block instance. Otherwise, 0 */
    uint8_t          channel_num;
} cyhal_resource_inst_t;

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_hw_types */
