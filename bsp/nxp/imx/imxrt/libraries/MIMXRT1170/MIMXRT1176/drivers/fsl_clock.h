/*
 * Copyright 2019-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_common.h"

/*! @addtogroup clock */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Configurations
 ******************************************************************************/

/*! @brief Configure whether driver controls clock
 *
 * When set to 0, peripheral drivers will enable clock in initialize function
 * and disable clock in de-initialize function. When set to 1, peripheral
 * driver will not control the clock, application could control the clock out of
 * the driver.
 *
 * @note All drivers share this feature switcher. If it is set to 1, application
 * should handle clock enable and disable for all drivers.
 */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
#define FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL 0
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 5, 2))

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#if __CORTEX_M == 7
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (1000000000UL)
#else
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (400000000UL)
#endif
#endif

/*@}*/

/*!
 * @brief CCM registers offset.
 */
#define CCSR_OFFSET   0x0C
#define CBCDR_OFFSET  0x14
#define CBCMR_OFFSET  0x18
#define CSCMR1_OFFSET 0x1C
#define CSCMR2_OFFSET 0x20
#define CSCDR1_OFFSET 0x24
#define CDCDR_OFFSET  0x30
#define CSCDR2_OFFSET 0x38
#define CSCDR3_OFFSET 0x3C
#define CACRR_OFFSET  0x10
#define CS1CDR_OFFSET 0x28
#define CS2CDR_OFFSET 0x2C

/*!
 * @brief CCM Analog registers offset.
 */
#define ARM_PLL_OFFSET   0x00
#define PLL_SYS_OFFSET   0x30
#define PLL_USB1_OFFSET  0x10
#define PLL_AUDIO_OFFSET 0x70
#define PLL_VIDEO_OFFSET 0xA0
#define PLL_ENET_OFFSET  0xE0
#define PLL_USB2_OFFSET  0x20

#define CCM_TUPLE(reg, shift, mask, busyShift) \
    (int)((reg & 0xFFU) | ((shift) << 8U) | ((((mask) >> (shift)) & 0x1FFFU) << 13U) | ((busyShift) << 26U))
#define CCM_TUPLE_REG(base, tuple)  (*((volatile uint32_t *)(((uint32_t)(base)) + ((tuple)&0xFFU))))
#define CCM_TUPLE_SHIFT(tuple)      (((tuple) >> 8U) & 0x1FU)
#define CCM_TUPLE_MASK(tuple)       ((uint32_t)((((tuple) >> 13U) & 0x1FFFU) << ((((tuple) >> 8U) & 0x1FU))))
#define CCM_TUPLE_BUSY_SHIFT(tuple) (((tuple) >> 26U) & 0x3FU)

#define CCM_BUSY_WAIT (0x20U)

/*!
 * @brief CCM ANALOG tuple macros to map corresponding registers and bit fields.
 */
#define CCM_ANALOG_TUPLE(reg, shift)  (((reg & 0xFFFU) << 16U) | (shift))
#define CCM_ANALOG_TUPLE_SHIFT(tuple) (((uint32_t)tuple) & 0x1FU)
#define CCM_ANALOG_TUPLE_REG_OFF(base, tuple, off) \
    (*((volatile uint32_t *)((uint32_t)base + (((uint32_t)tuple >> 16U) & 0xFFFU) + off)))
#define CCM_ANALOG_TUPLE_REG(base, tuple) CCM_ANALOG_TUPLE_REG_OFF(base, tuple, 0U)

/*!
 * @brief SYS_PLL_FREQ frequency in Hz.
 */
#define SYS_PLL1_FREQ (1000000000UL)
#define SYS_PLL2_MFI  (22UL)
#define SYS_PLL2_FREQ (XTAL_FREQ * SYS_PLL2_MFI)
#define SYS_PLL3_MFI  (20UL)
#define SYS_PLL3_FREQ (XTAL_FREQ * SYS_PLL3_MFI)
#define XTAL_FREQ     (24000000UL)

/*! @brief Clock gate name array for ADC. */
#define LPADC_CLOCKS                                   \
    {                                                  \
        kCLOCK_IpInvalid, kCLOCK_Lpadc1, kCLOCK_Lpadc2 \
    }

/*! @brief Clock gate name array for ADC. */
#define ADC_ETC_CLOCKS \
    {                  \
        kCLOCK_Adc_Etc \
    }

/*! @brief Clock gate name array for AOI. */
#define AOI_CLOCKS                                 \
    {                                              \
        kCLOCK_IpInvalid, kCLOCK_Aoi1, kCLOCK_Aoi2 \
    }

/*! @brief Clock gate name array for DCDC. */
#define DCDC_CLOCKS \
    {               \
        kCLOCK_Dcdc \
    }

/*! @brief Clock gate name array for SRC. */
#define SRC_CLOCKS \
    {              \
        kCLOCK_Src \
    }

/*! @brief Clock gate name array for GPC. */
#define GPC_CLOCKS \
    {              \
        kCLOCK_Gpc \
    }

/*! @brief Clock gate name array for SSARC. */
#define SSARC_CLOCKS \
    {                \
        kCLOCK_Ssarc \
    }

/*! @brief Clock gate name array for WDOG. */
#define WDOG_CLOCKS                                                              \
    {                                                                            \
        kCLOCK_IpInvalid, kCLOCK_Wdog1, kCLOCK_Wdog2, kCLOCK_Wdog3, kCLOCK_Wdog4 \
    }

/*! @brief Clock gate name array for EWM. */
#define EWM_CLOCKS  \
    {               \
        kCLOCK_Ewm0 \
    }

/*! @brief Clock gate name array for Sema. */
#define SEMA_CLOCKS \
    {               \
        kCLOCK_Sema \
    }

/*! @brief Clock gate name array for MU. */
#if (__CORTEX_M == 7)
#define MU_CLOCKS   \
    {               \
        kCLOCK_Mu_A \
    }
#else
#define MU_CLOCKS   \
    {               \
        kCLOCK_Mu_B \
    }
#endif

/*! @brief Clock gate name array for EDMA. */
#define EDMA_CLOCKS                   \
    {                                 \
        kCLOCK_Edma, kCLOCK_Edma_Lpsr \
    }

/*! @brief Clock gate name array for FLEXRAM. */
#define FLEXRAM_CLOCKS \
    {                  \
        kCLOCK_Flexram \
    }

/*! @brief Clock gate name array for LMEM. */
#define LMEM_CLOCKS \
    {               \
        kCLOCK_Lmem \
    }

/*! @brief Clock gate name array for FLEXSPI. */
#define FLEXSPI_CLOCKS                                     \
    {                                                      \
        kCLOCK_IpInvalid, kCLOCK_Flexspi1, kCLOCK_Flexspi2 \
    }

/*! @brief Clock gate name array for RDC. */
#define RDC_CLOCKS                                 \
    {                                              \
        kCLOCK_Rdc, kCLOCK_M7_Xrdc, kCLOCK_M4_Xrdc \
    }

/*! @brief Clock ip name array for DCDC. */
#define DCDC_CLOCKS \
    {               \
        kCLOCK_Dcdc \
    }

/*! @brief Clock ip name array for SEMC. */
#define SEMC_CLOCKS \
    {               \
        kCLOCK_Semc \
    }

/*! @brief Clock ip name array for XECC. */
#define XECC_CLOCKS \
    {               \
        kCLOCK_Xecc \
    }

/*! @brief Clock ip name array for IEE. */
#define IEE_CLOCKS \
    {              \
        kCLOCK_Iee \
    }

/*! @brief Clock ip name array for KEY_MANAGER. */
#define KEYMANAGER_CLOCKS  \
    {                      \
        kCLOCK_Key_Manager \
    }

/*! @brief Clock ip name array for PUF. */
#define PUF_CLOCKS \
    {              \
        kCLOCK_Puf \
    }

/*! @brief Clock ip name array for OCOTP. */
#define OCOTP_CLOCKS \
    {                \
        kCLOCK_Ocotp \
    }

/*! @brief Clock ip name array for CAAM. */
#define CAAM_CLOCKS \
    {               \
        kCLOCK_Caam \
    }

/*! @brief Clock ip name array for XBAR. */
#define XBAR_CLOCKS                                                \
    {                                                              \
        kCLOCK_IpInvalid, kCLOCK_Xbar1, kCLOCK_Xbar2, kCLOCK_Xbar3 \
    }

/*! @brief Clock ip name array for IOMUXC. */
#define IOMUXC_CLOCKS                     \
    {                                     \
        kCLOCK_Iomuxc, kCLOCK_Iomuxc_Lpsr \
    }

/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                                                                                                  \
    {                                                                                                                \
        kCLOCK_IpInvalid, kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio, \
            kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio, kCLOCK_Gpio,                            \
    }

/*! @brief Clock ip name array for KPP. */
#define KPP_CLOCKS \
    {              \
        kCLOCK_Kpp \
    }

/*! @brief Clock ip name array for FLEXIO. */
#define FLEXIO_CLOCKS                                    \
    {                                                    \
        kCLOCK_IpInvalid, kCLOCK_Flexio1, kCLOCK_Flexio2 \
    }

/*! @brief Clock ip name array for DAC. */
#define DAC_CLOCKS \
    {              \
        kCLOCK_Dac \
    }

/*! @brief Clock ip name array for CMP. */
#define CMP_CLOCKS                                                               \
    {                                                                            \
        kCLOCK_IpInvalid, kCLOCK_Acmp1, kCLOCK_Acmp2, kCLOCK_Acmp3, kCLOCK_Acmp4 \
    }

/*! @brief Clock ip name array for PIT. */
#define PIT_CLOCKS                                 \
    {                                              \
        kCLOCK_IpInvalid, kCLOCK_Pit1, kCLOCK_Pit2 \
    }

/*! @brief Clock ip name array for GPT. */
#define GPT_CLOCKS                                                                                     \
    {                                                                                                  \
        kCLOCK_IpInvalid, kCLOCK_Gpt1, kCLOCK_Gpt2, kCLOCK_Gpt3, kCLOCK_Gpt4, kCLOCK_Gpt5, kCLOCK_Gpt6 \
    }

/*! @brief Clock ip name array for QTIMER. */
#define TMR_CLOCKS                                                                       \
    {                                                                                    \
        kCLOCK_IpInvalid, kCLOCK_Qtimer1, kCLOCK_Qtimer2, kCLOCK_Qtimer3, kCLOCK_Qtimer4 \
    }

/*! @brief Clock ip name array for ENC. */
#define ENC_CLOCKS                                                           \
    {                                                                        \
        kCLOCK_IpInvalid, kCLOCK_Enc1, kCLOCK_Enc2, kCLOCK_Enc3, kCLOCK_Enc4 \
    }

/*! @brief Clock ip name array for PWM. */
#define PWM_CLOCKS                                                                \
    {                                                                             \
        {kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_IpInvalid}, \
            {kCLOCK_Pwm1, kCLOCK_Pwm1, kCLOCK_Pwm1, kCLOCK_Pwm1},                 \
            {kCLOCK_Pwm2, kCLOCK_Pwm2, kCLOCK_Pwm2, kCLOCK_Pwm2},                 \
            {kCLOCK_Pwm3, kCLOCK_Pwm3, kCLOCK_Pwm3, kCLOCK_Pwm3},                 \
        {                                                                         \
            kCLOCK_Pwm4, kCLOCK_Pwm4, kCLOCK_Pwm4, kCLOCK_Pwm4                    \
        }                                                                         \
    }

/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS                                          \
    {                                                           \
        kCLOCK_IpInvalid, kCLOCK_Can1, kCLOCK_Can2, kCLOCK_Can3 \
    }

/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                         \
    {                                                                                                         \
        kCLOCK_IpInvalid, kCLOCK_Lpuart1, kCLOCK_Lpuart2, kCLOCK_Lpuart3, kCLOCK_Lpuart4, kCLOCK_Lpuart5,     \
            kCLOCK_Lpuart6, kCLOCK_Lpuart7, kCLOCK_Lpuart8, kCLOCK_Lpuart9, kCLOCK_Lpuart10, kCLOCK_Lpuart11, \
            kCLOCK_Lpuart12                                                                                   \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                                                                                               \
    {                                                                                                              \
        kCLOCK_IpInvalid, kCLOCK_Lpi2c1, kCLOCK_Lpi2c2, kCLOCK_Lpi2c3, kCLOCK_Lpi2c4, kCLOCK_Lpi2c5, kCLOCK_Lpi2c6 \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS                                                                                               \
    {                                                                                                              \
        kCLOCK_IpInvalid, kCLOCK_Lpspi1, kCLOCK_Lpspi2, kCLOCK_Lpspi3, kCLOCK_Lpspi4, kCLOCK_Lpspi5, kCLOCK_Lpspi6 \
    }

/*! @brief Clock ip name array for EMVSIM. */
#define EMVSIM_CLOCKS                              \
    {                                              \
        kCLOCK_IpInvalid, kCLOCK_Sim1, kCLOCK_Sim2 \
    }

/*! @brief Clock ip name array for ENET. */
#define ENET_CLOCKS                 \
    {                               \
        kCLOCK_Enet, kCLOCK_Enet_1g \
    }

/*! @brief Clock ip name array for ENET_QOS. */
#define ENETQOS_CLOCKS  \
    {                   \
        kCLOCK_Enet_Qos \
    }

/*! @brief Clock ip name array for USB. */
#define USB_CLOCKS \
    {              \
        kCLOCK_Usb \
    }

/*! @brief Clock ip name array for CDOG. */
#define CDOG_CLOCKS \
    {               \
        kCLOCK_Cdog \
    }

/*! @brief Clock ip name array for USDHC. */
#define USDHC_CLOCKS                                   \
    {                                                  \
        kCLOCK_IpInvalid, kCLOCK_Usdhc1, kCLOCK_Usdhc2 \
    }

/*! @brief Clock ip name array for ASRC. */
#define ASRC_CLOCKS \
    {               \
        kCLOCK_Asrc \
    }

/*! @brief Clock ip name array for MQS. */
#define MQS_CLOCKS \
    {              \
        kCLOCK_Mqs \
    }

/*! @brief Clock ip name array for PDM. */
#define PDM_CLOCKS \
    {              \
        kCLOCK_Pdm \
    }

/*! @brief Clock ip name array for SPDIF. */
#define SPDIF_CLOCKS \
    {                \
        kCLOCK_Spdif \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                                           \
    {                                                                        \
        kCLOCK_IpInvalid, kCLOCK_Sai1, kCLOCK_Sai2, kCLOCK_Sai3, kCLOCK_Sai4 \
    }

/*! @brief Clock ip name array for PXP. */
#define PXP_CLOCKS \
    {              \
        kCLOCK_Pxp \
    }

/*! @brief Clock ip name array for GPU2d. */
#define GPU2D_CLOCKS \
    {                \
        kCLOCK_Gpu2d \
    }

/*! @brief Clock ip name array for LCDIF. */
#define LCDIF_CLOCKS \
    {                \
        kCLOCK_Lcdif \
    }

/*! @brief Clock ip name array for LCDIFV2. */
#define LCDIFV2_CLOCKS \
    {                  \
        kCLOCK_Lcdifv2 \
    }

/*! @brief Clock ip name array for MIPI_DSI. */
#define MIPI_DSI_HOST_CLOCKS \
    {                        \
        kCLOCK_Mipi_Dsi      \
    }

/*! @brief Clock ip name array for MIPI_CSI. */
#define MIPI_CSI2RX_CLOCKS \
    {                      \
        kCLOCK_Mipi_Csi    \
    }

/*! @brief Clock ip name array for CSI. */
#define CSI_CLOCKS \
    {              \
        kCLOCK_Csi \
    }

/*! @brief Clock ip name array for DCIC. */
#define DCIC_CLOCKS                                         \
    {                                                       \
        kCLOCK_IpInvalid, kCLOCK_Dcic_Mipi, kCLOCK_Dcic_Lcd \
    }

/*! @brief Clock ip name array for DMAMUX_CLOCKS. */
#define DMAMUX_CLOCKS                 \
    {                                 \
        kCLOCK_Edma, kCLOCK_Edma_Lpsr \
    }

/*! @brief Clock ip name array for XBARA. */
#define XBARA_CLOCKS                   \
    {                                  \
        kCLOCK_IpInvalid, kCLOCK_Xbar1 \
    }

/*! @brief Clock ip name array for XBARB. */
#define XBARB_CLOCKS                                                   \
    {                                                                  \
        kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_Xbar2, kCLOCK_Xbar3 \
    }

/*!
 * @brief Clock LPCG index
 */
typedef enum _clock_lpcg
{
    kCLOCK_M7          = 0,   /*!< Clock LPCG M7. */
    kCLOCK_M4          = 1,   /*!< Clock LPCG M4. */
    kCLOCK_Sim_M7      = 2,   /*!< Clock LPCG SIM M7. */
    kCLOCK_Sim_M       = 3,   /*!< Clock LPCG SIM M4. */
    kCLOCK_Sim_Disp    = 4,   /*!< Clock LPCG SIM DISP. */
    kCLOCK_Sim_Per     = 5,   /*!< Clock LPCG SIM PER. */
    kCLOCK_Sim_Lpsr    = 6,   /*!< Clock LPCG SIM LPSR. */
    kCLOCK_Anadig      = 7,   /*!< Clock LPCG Anadig. */
    kCLOCK_Dcdc        = 8,   /*!< Clock LPCG DCDC. */
    kCLOCK_Src         = 9,   /*!< Clock LPCG SRC. */
    kCLOCK_Ccm         = 10,  /*!< Clock LPCG CCM. */
    kCLOCK_Gpc         = 11,  /*!< Clock LPCG GPC. */
    kCLOCK_Ssarc       = 12,  /*!< Clock LPCG SSARC. */
    kCLOCK_Sim_R       = 13,  /*!< Clock LPCG SIM_R. */
    kCLOCK_Wdog1       = 14,  /*!< Clock LPCG WDOG1. */
    kCLOCK_Wdog2       = 15,  /*!< Clock LPCG WDOG2. */
    kCLOCK_Wdog3       = 16,  /*!< Clock LPCG WDOG3. */
    kCLOCK_Wdog4       = 17,  /*!< Clock LPCG WDOG4. */
    kCLOCK_Ewm0        = 18,  /*!< Clock LPCG EWM0. */
    kCLOCK_Sema        = 19,  /*!< Clock LPCG SEMA. */
    kCLOCK_Mu_A        = 20,  /*!< Clock LPCG MU_A. */
    kCLOCK_Mu_B        = 21,  /*!< Clock LPCG MU_B. */
    kCLOCK_Edma        = 22,  /*!< Clock LPCG EDMA. */
    kCLOCK_Edma_Lpsr   = 23,  /*!< Clock LPCG EDMA_LPSR. */
    kCLOCK_Romcp       = 24,  /*!< Clock LPCG ROMCP. */
    kCLOCK_Ocram       = 25,  /*!< Clock LPCG OCRAM. */
    kCLOCK_Flexram     = 26,  /*!< Clock LPCG FLEXRAM. */
    kCLOCK_Lmem        = 27,  /*!< Clock LPCG Lmem. */
    kCLOCK_Flexspi1    = 28,  /*!< Clock LPCG Flexspi1. */
    kCLOCK_Flexspi2    = 29,  /*!< Clock LPCG Flexspi2. */
    kCLOCK_Rdc         = 30,  /*!< Clock LPCG RDC. */
    kCLOCK_M7_Xrdc     = 31,  /*!< Clock LPCG M7 XRDC. */
    kCLOCK_M4_Xrdc     = 32,  /*!< Clock LPCG M4 XRDC. */
    kCLOCK_Semc        = 33,  /*!< Clock LPCG SEMC. */
    kCLOCK_Xecc        = 34,  /*!< Clock LPCG XECC. */
    kCLOCK_Iee         = 35,  /*!< Clock LPCG IEE. */
    kCLOCK_Key_Manager = 36,  /*!< Clock LPCG KEY_MANAGER. */
    kCLOCK_Puf         = 36,  /*!< Clock LPCG PUF. */
    kCLOCK_Ocotp       = 37,  /*!< Clock LPCG OSOTP. */
    kCLOCK_Snvs_Hp     = 38,  /*!< Clock LPCG SNVS_HP. */
    kCLOCK_Snvs        = 39,  /*!< Clock LPCG SNVS. */
    kCLOCK_Caam        = 40,  /*!< Clock LPCG Caam. */
    kCLOCK_Jtag_Mux    = 41,  /*!< Clock LPCG JTAG_MUX. */
    kCLOCK_Cstrace     = 42,  /*!< Clock LPCG CSTRACE. */
    kCLOCK_Xbar1       = 43,  /*!< Clock LPCG XBAR1. */
    kCLOCK_Xbar2       = 44,  /*!< Clock LPCG XBAR2. */
    kCLOCK_Xbar3       = 45,  /*!< Clock LPCG XBAR3. */
    kCLOCK_Aoi1        = 46,  /*!< Clock LPCG AOI1. */
    kCLOCK_Aoi2        = 47,  /*!< Clock LPCG AOI2. */
    kCLOCK_Adc_Etc     = 48,  /*!< Clock LPCG ADC_ETC. */
    kCLOCK_Iomuxc      = 49,  /*!< Clock LPCG IOMUXC. */
    kCLOCK_Iomuxc_Lpsr = 50,  /*!< Clock LPCG IOMUXC_LPSR. */
    kCLOCK_Gpio        = 51,  /*!< Clock LPCG GPIO. */
    kCLOCK_Kpp         = 52,  /*!< Clock LPCG KPP. */
    kCLOCK_Flexio1     = 53,  /*!< Clock LPCG FLEXIO1. */
    kCLOCK_Flexio2     = 54,  /*!< Clock LPCG FLEXIO2. */
    kCLOCK_Lpadc1      = 55,  /*!< Clock LPCG LPADC1. */
    kCLOCK_Lpadc2      = 56,  /*!< Clock LPCG LPADC2. */
    kCLOCK_Dac         = 57,  /*!< Clock LPCG DAC. */
    kCLOCK_Acmp1       = 58,  /*!< Clock LPCG ACMP1. */
    kCLOCK_Acmp2       = 59,  /*!< Clock LPCG ACMP2. */
    kCLOCK_Acmp3       = 60,  /*!< Clock LPCG ACMP3. */
    kCLOCK_Acmp4       = 61,  /*!< Clock LPCG ACMP4. */
    kCLOCK_Pit1        = 62,  /*!< Clock LPCG PIT1. */
    kCLOCK_Pit2        = 63,  /*!< Clock LPCG PIT2. */
    kCLOCK_Gpt1        = 64,  /*!< Clock LPCG GPT1. */
    kCLOCK_Gpt2        = 65,  /*!< Clock LPCG GPT2. */
    kCLOCK_Gpt3        = 66,  /*!< Clock LPCG GPT3. */
    kCLOCK_Gpt4        = 67,  /*!< Clock LPCG GPT4. */
    kCLOCK_Gpt5        = 68,  /*!< Clock LPCG GPT5. */
    kCLOCK_Gpt6        = 69,  /*!< Clock LPCG GPT6. */
    kCLOCK_Qtimer1     = 70,  /*!< Clock LPCG QTIMER1. */
    kCLOCK_Qtimer2     = 71,  /*!< Clock LPCG QTIMER2. */
    kCLOCK_Qtimer3     = 72,  /*!< Clock LPCG QTIMER3. */
    kCLOCK_Qtimer4     = 73,  /*!< Clock LPCG QTIMER4. */
    kCLOCK_Enc1        = 74,  /*!< Clock LPCG Enc1. */
    kCLOCK_Enc2        = 75,  /*!< Clock LPCG Enc2. */
    kCLOCK_Enc3        = 76,  /*!< Clock LPCG Enc3. */
    kCLOCK_Enc4        = 77,  /*!< Clock LPCG Enc4. */
    kCLOCK_Hrtimer     = 78,  /*!< Clock LPCG Hrtimer. */
    kCLOCK_Pwm1        = 79,  /*!< Clock LPCG PWM1. */
    kCLOCK_Pwm2        = 80,  /*!< Clock LPCG PWM2. */
    kCLOCK_Pwm3        = 81,  /*!< Clock LPCG PWM3. */
    kCLOCK_Pwm4        = 82,  /*!< Clock LPCG PWM4. */
    kCLOCK_Can1        = 83,  /*!< Clock LPCG CAN1. */
    kCLOCK_Can2        = 84,  /*!< Clock LPCG CAN2. */
    kCLOCK_Can3        = 85,  /*!< Clock LPCG CAN3. */
    kCLOCK_Lpuart1     = 86,  /*!< Clock LPCG LPUART1. */
    kCLOCK_Lpuart2     = 87,  /*!< Clock LPCG LPUART2. */
    kCLOCK_Lpuart3     = 88,  /*!< Clock LPCG LPUART3. */
    kCLOCK_Lpuart4     = 89,  /*!< Clock LPCG LPUART4. */
    kCLOCK_Lpuart5     = 90,  /*!< Clock LPCG LPUART5. */
    kCLOCK_Lpuart6     = 91,  /*!< Clock LPCG LPUART6. */
    kCLOCK_Lpuart7     = 92,  /*!< Clock LPCG LPUART7. */
    kCLOCK_Lpuart8     = 93,  /*!< Clock LPCG LPUART8. */
    kCLOCK_Lpuart9     = 94,  /*!< Clock LPCG LPUART9. */
    kCLOCK_Lpuart10    = 95,  /*!< Clock LPCG LPUART10. */
    kCLOCK_Lpuart11    = 96,  /*!< Clock LPCG LPUART11. */
    kCLOCK_Lpuart12    = 97,  /*!< Clock LPCG LPUART12. */
    kCLOCK_Lpi2c1      = 98,  /*!< Clock LPCG LPI2C1. */
    kCLOCK_Lpi2c2      = 99,  /*!< Clock LPCG LPI2C2. */
    kCLOCK_Lpi2c3      = 100, /*!< Clock LPCG LPI2C3. */
    kCLOCK_Lpi2c4      = 101, /*!< Clock LPCG LPI2C4. */
    kCLOCK_Lpi2c5      = 102, /*!< Clock LPCG LPI2C5. */
    kCLOCK_Lpi2c6      = 103, /*!< Clock LPCG LPI2C6. */
    kCLOCK_Lpspi1      = 104, /*!< Clock LPCG LPSPI1. */
    kCLOCK_Lpspi2      = 105, /*!< Clock LPCG LPSPI2. */
    kCLOCK_Lpspi3      = 106, /*!< Clock LPCG LPSPI3. */
    kCLOCK_Lpspi4      = 107, /*!< Clock LPCG LPSPI4. */
    kCLOCK_Lpspi5      = 108, /*!< Clock LPCG LPSPI5. */
    kCLOCK_Lpspi6      = 109, /*!< Clock LPCG LPSPI6. */
    kCLOCK_Sim1        = 110, /*!< Clock LPCG SIM1. */
    kCLOCK_Sim2        = 111, /*!< Clock LPCG SIM2. */
    kCLOCK_Enet        = 112, /*!< Clock LPCG ENET. */
    kCLOCK_Enet_1g     = 113, /*!< Clock LPCG ENET 1G. */
    kCLOCK_Enet_Qos    = 114, /*!< Clock LPCG ENET QOS. */
    kCLOCK_Usb         = 115, /*!< Clock LPCG USB. */
    kCLOCK_Cdog        = 116, /*!< Clock LPCG CDOG. */
    kCLOCK_Usdhc1      = 117, /*!< Clock LPCG USDHC1. */
    kCLOCK_Usdhc2      = 118, /*!< Clock LPCG USDHC2. */
    kCLOCK_Asrc        = 119, /*!< Clock LPCG ASRC. */
    kCLOCK_Mqs         = 120, /*!< Clock LPCG MQS. */
    kCLOCK_Pdm         = 121, /*!< Clock LPCG PDM. */
    kCLOCK_Spdif       = 122, /*!< Clock LPCG SPDIF. */
    kCLOCK_Sai1        = 123, /*!< Clock LPCG SAI1. */
    kCLOCK_Sai2        = 124, /*!< Clock LPCG SAI2. */
    kCLOCK_Sai3        = 125, /*!< Clock LPCG SAI3. */
    kCLOCK_Sai4        = 126, /*!< Clock LPCG SAI4. */
    kCLOCK_Pxp         = 127, /*!< Clock LPCG PXP. */
    kCLOCK_Gpu2d       = 128, /*!< Clock LPCG GPU2D. */
    kCLOCK_Lcdif       = 129, /*!< Clock LPCG LCDIF. */
    kCLOCK_Lcdifv2     = 130, /*!< Clock LPCG LCDIFV2. */
    kCLOCK_Mipi_Dsi    = 131, /*!< Clock LPCG MIPI DSI. */
    kCLOCK_Mipi_Csi    = 132, /*!< Clock LPCG MIPI CSI. */
    kCLOCK_Csi         = 133, /*!< Clock LPCG CSI. */
    kCLOCK_Dcic_Mipi   = 134, /*!< Clock LPCG DCIC MIPI. */
    kCLOCK_Dcic_Lcd    = 135, /*!< Clock LPCG DCIC LCD. */
    kCLOCK_Video_Mux   = 136, /*!< Clock LPCG VIDEO MUX. */
    kCLOCK_Uniq_Edt_I  = 137, /*!< Clock LPCG Uniq_Edt_I. */

    kCLOCK_IpInvalid, /*!< Invalid value. */
} clock_lpcg_t;

/*!
 * @brief Clock name.
 */
typedef enum _clock_name
{
    kCLOCK_OscRc16M     = 0,  /*!< 16MHz RC Oscillator. */
    kCLOCK_OscRc48M     = 1,  /*!< 48MHz RC Oscillator. */
    kCLOCK_OscRc48MDiv2 = 2,  /*!< 48MHz RC Oscillator Div2. */
    kCLOCK_OscRc400M    = 3,  /*!< 400MHz RC Oscillator. */
    kCLOCK_Osc24M       = 4,  /*!< 24MHz Oscillator. */
    kCLOCK_Osc24MOut    = 5,  /*!< 48MHz Oscillator Out. */
    kCLOCK_ArmPll       = 6,  /*!< ARM PLL. */
    kCLOCK_ArmPllOut    = 7,  /*!< ARM PLL Out. */
    kCLOCK_SysPll2      = 8,  /*!< SYS PLL2. */
    kCLOCK_SysPll2Out   = 9,  /*!< SYS PLL2 OUT. */
    kCLOCK_SysPll2Pfd0  = 10, /*!< SYS PLL2 PFD0. */
    kCLOCK_SysPll2Pfd1  = 11, /*!< SYS PLL2 PFD1. */
    kCLOCK_SysPll2Pfd2  = 12, /*!< SYS PLL2 PFD2. */
    kCLOCK_SysPll2Pfd3  = 13, /*!< SYS PLL2 PFD3. */
    kCLOCK_SysPll3      = 14, /*!< SYS PLL3. */
    kCLOCK_SysPll3Out   = 15, /*!< SYS PLL3 OUT. */
    kCLOCK_SysPll3Div2  = 16, /*!< SYS PLL3 DIV2 */
    kCLOCK_SysPll3Pfd0  = 17, /*!< SYS PLL3 PFD0. */
    kCLOCK_SysPll3Pfd1  = 18, /*!< SYS PLL3 PFD1 */
    kCLOCK_SysPll3Pfd2  = 19, /*!< SYS PLL3 PFD2 */
    kCLOCK_SysPll3Pfd3  = 20, /*!< SYS PLL3 PFD3 */
    kCLOCK_SysPll1      = 21, /*!< SYS PLL1. */
    kCLOCK_SysPll1Out   = 22, /*!< SYS PLL1 OUT. */
    kCLOCK_SysPll1Div2  = 23, /*!< SYS PLL1 DIV2. */
    kCLOCK_SysPll1Div5  = 24, /*!< SYS PLL1 DIV5. */
    kCLOCK_AudioPll     = 25, /*!< SYS AUDIO PLL. */
    kCLOCK_AudioPllOut  = 26, /*!< SYS AUDIO PLL OUT. */
    kCLOCK_VideoPll     = 27, /*!< SYS VIDEO PLL. */
    kCLOCK_VideoPllOut  = 28, /*!< SYS VIDEO PLL OUT. */
    kCLOCK_CpuClk,            /*!< SYS CPU CLK. */
    kCLOCK_CoreSysClk,        /*!< SYS CORE SYS CLK. */
} clock_name_t;

/* Clock OBSERVE SIGNALS */
#define CCM_OBS_M7_CLK_ROOT          128, 4
#define CCM_OBS_M4_CLK_ROOT          129, 0
#define CCM_OBS_BUS_CLK_ROOT         130, 2
#define CCM_OBS_BUS_LPSR_CLK_ROOT    131, 0
#define CCM_OBS_SEMC_CLK_ROOT        132, 2
#define CCM_OBS_CSSYS_CLK_ROOT       133, 2
#define CCM_OBS_CSTRACE_CLK_ROOT     134, 2
#define CCM_OBS_M4_SYSTICK_CLK_ROOT  135, 0
#define CCM_OBS_M7_SYSTICK_CLK_ROOT  136, 2
#define CCM_OBS_ADC1_CLK_ROOT        137, 2
#define CCM_OBS_ADC2_CLK_ROOT        138, 2
#define CCM_OBS_ACMP_CLK_ROOT        139, 2
#define CCM_OBS_FLEXIO1_CLK_ROOT     140, 2
#define CCM_OBS_FLEXIO2_CLK_ROOT     141, 2
#define CCM_OBS_GPT1_CLK_ROOT        142, 2
#define CCM_OBS_GPT2_CLK_ROOT        143, 2
#define CCM_OBS_GPT3_CLK_ROOT        144, 2
#define CCM_OBS_GPT4_CLK_ROOT        145, 2
#define CCM_OBS_GPT5_CLK_ROOT        146, 2
#define CCM_OBS_GPT6_CLK_ROOT        147, 2
#define CCM_OBS_FLEXSPI1_CLK_ROOT    148, 2
#define CCM_OBS_FLEXSPI2_CLK_ROOT    149, 2
#define CCM_OBS_CAN1_CLK_ROOT        150, 2
#define CCM_OBS_CAN2_CLK_ROOT        151, 2
#define CCM_OBS_CAN3_CLK_ROOT        152, 0
#define CCM_OBS_LPUART1_CLK_ROOT     153, 2
#define CCM_OBS_LPUART2_CLK_ROOT     154, 2
#define CCM_OBS_LPUART3_CLK_ROOT     155, 2
#define CCM_OBS_LPUART4_CLK_ROOT     156, 2
#define CCM_OBS_LPUART5_CLK_ROOT     157, 2
#define CCM_OBS_LPUART6_CLK_ROOT     158, 2
#define CCM_OBS_LPUART7_CLK_ROOT     159, 2
#define CCM_OBS_LPUART8_CLK_ROOT     160, 2
#define CCM_OBS_LPUART9_CLK_ROOT     161, 2
#define CCM_OBS_LPUART10_CLK_ROOT    162, 2
#define CCM_OBS_LPUART11_CLK_ROOT    163, 0
#define CCM_OBS_LPUART12_CLK_ROOT    164, 0
#define CCM_OBS_LPI2C1_CLK_ROOT      165, 2
#define CCM_OBS_LPI2C2_CLK_ROOT      166, 2
#define CCM_OBS_LPI2C3_CLK_ROOT      167, 2
#define CCM_OBS_LPI2C4_CLK_ROOT      168, 2
#define CCM_OBS_LPI2C5_CLK_ROOT      169, 0
#define CCM_OBS_LPI2C6_CLK_ROOT      170, 0
#define CCM_OBS_LPSPI1_CLK_ROOT      171, 2
#define CCM_OBS_LPSPI2_CLK_ROOT      172, 2
#define CCM_OBS_LPSPI3_CLK_ROOT      173, 2
#define CCM_OBS_LPSPI4_CLK_ROOT      174, 2
#define CCM_OBS_LPSPI5_CLK_ROOT      175, 0
#define CCM_OBS_LPSPI6_CLK_ROOT      176, 0
#define CCM_OBS_EMV1_CLK_ROOT        177, 2
#define CCM_OBS_EMV2_CLK_ROOT        178, 2
#define CCM_OBS_ENET1_CLK_ROOT       179, 2
#define CCM_OBS_ENET2_CLK_ROOT       180, 2
#define CCM_OBS_ENET_QOS_CLK_ROOT    181, 2
#define CCM_OBS_ENET_25M_CLK_ROOT    182, 2
#define CCM_OBS_ENET_TIMER1_CLK_ROOT 183, 2
#define CCM_OBS_ENET_TIMER2_CLK_ROOT 184, 2
#define CCM_OBS_ENET_TIMER3_CLK_ROOT 185, 2
#define CCM_OBS_USDHC1_CLK_ROOT      186, 2
#define CCM_OBS_USDHC2_CLK_ROOT      187, 2
#define CCM_OBS_ASRC_CLK_ROOT        188, 2
#define CCM_OBS_MQS_CLK_ROOT         189, 2
#define CCM_OBS_MIC_CLK_ROOT         190, 0
#define CCM_OBS_SPDIF_CLK_ROOT       191, 2
#define CCM_OBS_SAI1_CLK_ROOT        192, 2
#define CCM_OBS_SAI2_CLK_ROOT        193, 2
#define CCM_OBS_SAI3_CLK_ROOT        194, 2
#define CCM_OBS_SAI4_CLK_ROOT        195, 0
#define CCM_OBS_GC355_CLK_ROOT       196, 2
#define CCM_OBS_LCDIF_CLK_ROOT       197, 2
#define CCM_OBS_LCDIFV2_CLK_ROOT     198, 2
#define CCM_OBS_MIPI_REF_CLK_ROOT    199, 2
#define CCM_OBS_MIPI_ESC_CLK_ROOT    200, 2
#define CCM_OBS_CSI2_CLK_ROOT        201, 2
#define CCM_OBS_CSI2_ESC_CLK_ROOT    202, 2
#define CCM_OBS_CSI2_UI_CLK_ROOT     203, 2
#define CCM_OBS_CSI_CLK_ROOT         204, 2
#define CCM_OBS_CCM_CKO1_CLK_ROOT    205, 0
#define CCM_OBS_CCM_CKO2_CLK_ROOT    206, 2
#define CCM_OBS_CM7_CORE_STCLKEN     207, 4
#define CCM_OBS_CCM_FLEXRAM_CLK_ROOT 208, 4
#define CCM_OBS_MIPI_DSI_TXESC       209, 2
#define CCM_OBS_MIPI_DSI_RXESC       210, 2
#define CCM_OBS_OSC_RC_16M           224, 0
#define CCM_OBS_OSC_RC_48M           225, 0
#define CCM_OBS_OSC_RC_48M_DIV2      226, 0
#define CCM_OBS_OSC_RC_400M          227, 0
#define CCM_OBS_OSC_24M_OUT          229, 0
#define CCM_OBS_ARM_PLL_OUT          231, 2
#define CCM_OBS_SYS_PLL2_OUT         233, 2
#define CCM_OBS_SYS_PLL2_PFD0        234, 2
#define CCM_OBS_SYS_PLL2_PFD1        235, 2
#define CCM_OBS_SYS_PLL2_PFD2        236, 2
#define CCM_OBS_SYS_PLL2_PFD3        237, 2
#define CCM_OBS_SYS_PLL3_OUT         239, 2
#define CCM_OBS_SYS_PLL3_DIV2        240, 2
#define CCM_OBS_SYS_PLL3_PFD0        241, 2
#define CCM_OBS_SYS_PLL3_PFD1        242, 2
#define CCM_OBS_SYS_PLL3_PFD2        243, 2
#define CCM_OBS_SYS_PLL3_PFD3        244, 2
#define CCM_OBS_SYS_PLL1_OUT         246, 2
#define CCM_OBS_SYS_PLL1_DIV2        247, 2
#define CCM_OBS_SYS_PLL1_DIV5        248, 2
#define CCM_OBS_PLL_AUDIO_OUT        250, 2
#define CCM_OBS_PLL_VIDEO_OUT        252, 2

#define CCM_OBS_DIV 3

/* Clock Source Definitions */
/* clang-format off */
static const clock_name_t s_clockSourceName[][8] = {
        /*SRC0,               SRC1,             SRC2,             SRC3,            SRC4,             SRC5,              SRC6,              SRC7,                      name             index */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_ArmPllOut, kCLOCK_SysPll1Out, kCLOCK_SysPll3Out, kCLOCK_VideoPllOut},     /* M7               0    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll2Out, kCLOCK_SysPll1Div5},   /* M4               1    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Out, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},   /* BUS              2    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll2Out, kCLOCK_SysPll1Div5},   /* BUS_LPSR         3    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd1, kCLOCK_SysPll3Pfd0},  /* SEMC             4    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* CSSYS            5    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd1, kCLOCK_SysPll2Out},  /* CSTRACE          6    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd0, kCLOCK_SysPll1Div5},  /* M4_SYSTICK       7    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Out, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd0},  /* M7_SYSTICK       8    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* ADC1             9    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* ADC2            10    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Out, kCLOCK_SysPll1Div5, kCLOCK_AudioPllOut, kCLOCK_SysPll2Pfd3},  /* ACMP            11    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* FLEXIO1         12    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* FLEXIO2         13    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll3Pfd3}, /* GPT1            14    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_AudioPllOut, kCLOCK_VideoPllOut}, /* GPT2            15    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_AudioPllOut, kCLOCK_VideoPllOut}, /* GPT3            16    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll3Pfd3}, /* GPT4            17    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll3Pfd3}, /* GPT5            18    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll3Pfd3}, /* GPT6            19    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd0, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll3Out},   /* FLEXSPI1        20    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd0, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll3Out},   /* FLEXSPI2        21    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* CAN1            22    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* CAN2            23    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd3, kCLOCK_SysPll1Div5},  /* CAN3            24    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART1         25    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART2         26    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART3         27    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART4         28    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART5         29    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART6         30    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART7         31    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART8         32    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART9         33    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPUART10        34    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd3, kCLOCK_SysPll1Div5},  /* LPUART11        35    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd3, kCLOCK_SysPll1Div5},  /* LPUART12        36    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPI2C1          37    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPI2C2          38    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPI2C3          39    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPI2C4          40    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd3, kCLOCK_SysPll1Div5},  /* LPI2C5          41    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd3, kCLOCK_SysPll1Div5},  /* LPI2C6          42    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPSPI1          43    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPSPI2          44    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPSPI3          45    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* LPSPI4          46    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5},  /* LPSPI5          47    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5},  /* LPSPI6          48    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* EMV1            49    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd3},  /* EMV2            50    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd1}, /* ENET1           51    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd1}, /* ENET2           52    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd1}, /* ENET_QOS        53    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd1}, /* ENET_25M        54    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd1}, /* ENET_TIMER1     55    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd1}, /* ENET_TIMER2     56    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd1}, /* ENET_TIMER3     57    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll2Pfd0, kCLOCK_SysPll1Div5, kCLOCK_ArmPllOut},   /* USDHC1          58    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll2Pfd0, kCLOCK_SysPll1Div5, kCLOCK_ArmPllOut},   /* USDHC2          59    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div5, kCLOCK_SysPll3Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll2Pfd3}, /* ASRC            60    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll1Div5, kCLOCK_SysPll3Div2, kCLOCK_AudioPllOut, kCLOCK_SysPll2Pfd3}, /* MQS             61    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5},  /* MIC             62    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Out, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll2Pfd3},  /* SPDIF           63    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd3}, /* SAI1            64    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd3}, /* SAI2            65    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll1Div5, kCLOCK_SysPll2Pfd3}, /* SAI3            66    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll3Out, kCLOCK_AudioPllOut, kCLOCK_SysPll1Div5},  /* SAI4            67    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd1, kCLOCK_SysPll3Out, kCLOCK_VideoPllOut},   /* GC355           68    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll3Pfd0, kCLOCK_VideoPllOut},  /* LCDIF           69    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll3Pfd0, kCLOCK_VideoPllOut},  /* LCDIFV2         70    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd0, kCLOCK_SysPll3Pfd0, kCLOCK_VideoPllOut},  /* MIPI_REF        71    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Out, kCLOCK_SysPll2Pfd0, kCLOCK_SysPll3Pfd0, kCLOCK_VideoPllOut},  /* MIPI_ESC        72    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd0, kCLOCK_VideoPllOut},  /* CSI2            73    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd0, kCLOCK_VideoPllOut},  /* CSI2_ESC        74    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll3Out, kCLOCK_SysPll2Pfd0, kCLOCK_VideoPllOut},  /* CSI2_UI         75    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll3Out, kCLOCK_SysPll3Pfd1, kCLOCK_VideoPllOut},  /* CSI             76    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll2Out, kCLOCK_SysPll3Pfd1, kCLOCK_SysPll1Div5},  /* CKO1            77    */ \
        {kCLOCK_OscRc48MDiv2, kCLOCK_Osc24MOut, kCLOCK_OscRc400M, kCLOCK_OscRc16M, kCLOCK_SysPll2Pfd3, kCLOCK_OscRc48M, kCLOCK_SysPll3Pfd1, kCLOCK_AudioPllOut}     /* CKO2            78    */ \
};
/* clang-format on */

/*!
 * @brief Root clock index
 *
 */
typedef enum _clock_root
{
    kCLOCK_Root_M7          = 0,  /*!< CLOCK Root M7. */
    kCLOCK_Root_M4          = 1,  /*!< CLOCK Root M4. */
    kCLOCK_Root_Bus         = 2,  /*!< CLOCK Root Bus. */
    kCLOCK_Root_Bus_Lpsr    = 3,  /*!< CLOCK Root Bus Lpsr. */
    kCLOCK_Root_Semc        = 4,  /*!< CLOCK Root Semc. */
    kCLOCK_Root_Cssys       = 5,  /*!< CLOCK Root Cssys. */
    kCLOCK_Root_Cstrace     = 6,  /*!< CLOCK Root Cstrace. */
    kCLOCK_Root_M4_Systick  = 7,  /*!< CLOCK Root M4 Systick. */
    kCLOCK_Root_M7_Systick  = 8,  /*!< CLOCK Root M7 Systick. */
    kCLOCK_Root_Adc1        = 9,  /*!< CLOCK Root Adc1. */
    kCLOCK_Root_Adc2        = 10, /*!< CLOCK Root Adc2. */
    kCLOCK_Root_Acmp        = 11, /*!< CLOCK Root Acmp. */
    kCLOCK_Root_Flexio1     = 12, /*!< CLOCK Root Flexio1. */
    kCLOCK_Root_Flexio2     = 13, /*!< CLOCK Root Flexio2. */
    kCLOCK_Root_Gpt1        = 14, /*!< CLOCK Root Gpt1. */
    kCLOCK_Root_Gpt2        = 15, /*!< CLOCK Root Gpt2. */
    kCLOCK_Root_Gpt3        = 16, /*!< CLOCK Root Gpt3. */
    kCLOCK_Root_Gpt4        = 17, /*!< CLOCK Root Gpt4. */
    kCLOCK_Root_Gpt5        = 18, /*!< CLOCK Root Gpt5. */
    kCLOCK_Root_Gpt6        = 19, /*!< CLOCK Root Gpt6. */
    kCLOCK_Root_Flexspi1    = 20, /*!< CLOCK Root Flexspi1. */
    kCLOCK_Root_Flexspi2    = 21, /*!< CLOCK Root Flexspi2. */
    kCLOCK_Root_Can1        = 22, /*!< CLOCK Root Can1. */
    kCLOCK_Root_Can2        = 23, /*!< CLOCK Root Can2. */
    kCLOCK_Root_Can3        = 24, /*!< CLOCK Root Can3. */
    kCLOCK_Root_Lpuart1     = 25, /*!< CLOCK Root Lpuart1. */
    kCLOCK_Root_Lpuart2     = 26, /*!< CLOCK Root Lpuart2. */
    kCLOCK_Root_Lpuart3     = 27, /*!< CLOCK Root Lpuart3. */
    kCLOCK_Root_Lpuart4     = 28, /*!< CLOCK Root Lpuart4. */
    kCLOCK_Root_Lpuart5     = 29, /*!< CLOCK Root Lpuart5. */
    kCLOCK_Root_Lpuart6     = 30, /*!< CLOCK Root Lpuart6. */
    kCLOCK_Root_Lpuart7     = 31, /*!< CLOCK Root Lpuart7. */
    kCLOCK_Root_Lpuart8     = 32, /*!< CLOCK Root Lpuart8. */
    kCLOCK_Root_Lpuart9     = 33, /*!< CLOCK Root Lpuart9. */
    kCLOCK_Root_Lpuart10    = 34, /*!< CLOCK Root Lpuart10. */
    kCLOCK_Root_Lpuart11    = 35, /*!< CLOCK Root Lpuart11. */
    kCLOCK_Root_Lpuart12    = 36, /*!< CLOCK Root Lpuart12. */
    kCLOCK_Root_Lpi2c1      = 37, /*!< CLOCK Root Lpi2c1. */
    kCLOCK_Root_Lpi2c2      = 38, /*!< CLOCK Root Lpi2c2. */
    kCLOCK_Root_Lpi2c3      = 39, /*!< CLOCK Root Lpi2c3. */
    kCLOCK_Root_Lpi2c4      = 40, /*!< CLOCK Root Lpi2c4. */
    kCLOCK_Root_Lpi2c5      = 41, /*!< CLOCK Root Lpi2c5. */
    kCLOCK_Root_Lpi2c6      = 42, /*!< CLOCK Root Lpi2c6. */
    kCLOCK_Root_Lpspi1      = 43, /*!< CLOCK Root Lpspi1. */
    kCLOCK_Root_Lpspi2      = 44, /*!< CLOCK Root Lpspi2. */
    kCLOCK_Root_Lpspi3      = 45, /*!< CLOCK Root Lpspi3. */
    kCLOCK_Root_Lpspi4      = 46, /*!< CLOCK Root Lpspi4. */
    kCLOCK_Root_Lpspi5      = 47, /*!< CLOCK Root Lpspi5. */
    kCLOCK_Root_Lpspi6      = 48, /*!< CLOCK Root Lpspi6. */
    kCLOCK_Root_Emv1        = 49, /*!< CLOCK Root Emv1. */
    kCLOCK_Root_Emv2        = 50, /*!< CLOCK Root Emv2. */
    kCLOCK_Root_Enet1       = 51, /*!< CLOCK Root Enet1. */
    kCLOCK_Root_Enet2       = 52, /*!< CLOCK Root Enet2. */
    kCLOCK_Root_Enet_Qos    = 53, /*!< CLOCK Root Enet Qos. */
    kCLOCK_Root_Enet_25m    = 54, /*!< CLOCK Root Enet 25M. */
    kCLOCK_Root_Enet_Timer1 = 55, /*!< CLOCK Root Enet Timer1. */
    kCLOCK_Root_Enet_Timer2 = 56, /*!< CLOCK Root Enet Timer2. */
    kCLOCK_Root_Enet_Timer3 = 57, /*!< CLOCK Root Enet Timer3. */
    kCLOCK_Root_Usdhc1      = 58, /*!< CLOCK Root Usdhc1. */
    kCLOCK_Root_Usdhc2      = 59, /*!< CLOCK Root Usdhc2. */
    kCLOCK_Root_Asrc        = 60, /*!< CLOCK Root Asrc. */
    kCLOCK_Root_Mqs         = 61, /*!< CLOCK Root Mqs. */
    kCLOCK_Root_Mic         = 62, /*!< CLOCK Root MIC. */
    kCLOCK_Root_Spdif       = 63, /*!< CLOCK Root Spdif */
    kCLOCK_Root_Sai1        = 64, /*!< CLOCK Root Sai1. */
    kCLOCK_Root_Sai2        = 65, /*!< CLOCK Root Sai2. */
    kCLOCK_Root_Sai3        = 66, /*!< CLOCK Root Sai3. */
    kCLOCK_Root_Sai4        = 67, /*!< CLOCK Root Sai4. */
    kCLOCK_Root_Gc355       = 68, /*!< CLOCK Root Gc355. */
    kCLOCK_Root_Lcdif       = 69, /*!< CLOCK Root Lcdif. */
    kCLOCK_Root_Lcdifv2     = 70, /*!< CLOCK Root Lcdifv2. */
    kCLOCK_Root_Mipi_Ref    = 71, /*!< CLOCK Root Mipi Ref. */
    kCLOCK_Root_Mipi_Esc    = 72, /*!< CLOCK Root Mipi Esc. */
    kCLOCK_Root_Csi2        = 73, /*!< CLOCK Root Csi2. */
    kCLOCK_Root_Csi2_Esc    = 74, /*!< CLOCK Root Csi2 Esc. */
    kCLOCK_Root_Csi2_Ui     = 75, /*!< CLOCK Root Csi2 Ui. */
    kCLOCK_Root_Csi         = 76, /*!< CLOCK Root Csi. */
    kCLOCK_Root_Cko1        = 77, /*!< CLOCK Root CKo1. */
    kCLOCK_Root_Cko2        = 78, /*!< CLOCK Root CKo2. */
} clock_root_t;

/*!
 * @brief The enumerator of clock roots' clock source mux value.
 */
typedef enum _clock_root_mux_source
{
    /* M7 */
    kCLOCK_M7_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< M7 mux from MuxOscRc48MDiv2. */
    kCLOCK_M7_ClockRoot_MuxOsc24MOut    = 1U, /*!< M7 mux from MuxOsc24MOut. */
    kCLOCK_M7_ClockRoot_MuxOscRc400M    = 2U, /*!< M7 mux from MuxOscRc400M. */
    kCLOCK_M7_ClockRoot_MuxOscRc16M     = 3U, /*!< M7 mux from MuxOscRc16M. */
    kCLOCK_M7_ClockRoot_MuxArmPllOut    = 4U, /*!< M7 mux from MuxArmPllOut. */
    kCLOCK_M7_ClockRoot_MuxSysPll1Out   = 5U, /*!< M7 mux from MuxSysPll1Out. */
    kCLOCK_M7_ClockRoot_MuxSysPll3Out   = 6U, /*!< M7 mux from MuxSysPll3Out. */
    kCLOCK_M7_ClockRoot_MuxVideoPllOut  = 7U, /*!< M7 mux from MuxVideoPllOut. */

    /* M4 */
    kCLOCK_M4_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< M4 mux from MuxOscRc48MDiv2. */
    kCLOCK_M4_ClockRoot_MuxOsc24MOut    = 1U, /*!< M4 mux from MuxOsc24MOut. */
    kCLOCK_M4_ClockRoot_MuxOscRc400M    = 2U, /*!< M4 mux from MuxOscRc400M. */
    kCLOCK_M4_ClockRoot_MuxOscRc16M     = 3U, /*!< M4 mux from MuxOscRc16M. */
    kCLOCK_M4_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< M4 mux from MuxSysPll3Pfd3. */
    kCLOCK_M4_ClockRoot_MuxSysPll3Out   = 5U, /*!< M4 mux from MuxSysPll3Out. */
    kCLOCK_M4_ClockRoot_MuxSysPll2Out   = 6U, /*!< M4 mux from MuxSysPll2Out. */
    kCLOCK_M4_ClockRoot_MuxSysPll1Div5  = 7U, /*!< M4 mux from MuxSysPll1Div5. */

    /* BUS */
    kCLOCK_BUS_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< BUS mux from MuxOscRc48MDiv2. */
    kCLOCK_BUS_ClockRoot_MuxOsc24MOut    = 1U, /*!< BUS mux from MuxOsc24MOut. */
    kCLOCK_BUS_ClockRoot_MuxOscRc400M    = 2U, /*!< BUS mux from MuxOscRc400M. */
    kCLOCK_BUS_ClockRoot_MuxOscRc16M     = 3U, /*!< BUS mux from MuxOscRc16M. */
    kCLOCK_BUS_ClockRoot_MuxSysPll3Out   = 4U, /*!< BUS mux from MuxSysPll3Out. */
    kCLOCK_BUS_ClockRoot_MuxSysPll1Div5  = 5U, /*!< BUS mux from MuxSysPll1Div5. */
    kCLOCK_BUS_ClockRoot_MuxSysPll2Out   = 6U, /*!< BUS mux from MuxSysPll2Out. */
    kCLOCK_BUS_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< BUS mux from MuxSysPll2Pfd3. */

    /* BUS_LPSR */
    kCLOCK_BUS_LPSR_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< BUS_LPSR mux from MuxOscRc48MDiv2. */
    kCLOCK_BUS_LPSR_ClockRoot_MuxOsc24MOut    = 1U, /*!< BUS_LPSR mux from MuxOsc24MOut. */
    kCLOCK_BUS_LPSR_ClockRoot_MuxOscRc400M    = 2U, /*!< BUS_LPSR mux from MuxOscRc400M. */
    kCLOCK_BUS_LPSR_ClockRoot_MuxOscRc16M     = 3U, /*!< BUS_LPSR mux from MuxOscRc16M. */
    kCLOCK_BUS_LPSR_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< BUS_LPSR mux from MuxSysPll3Pfd3. */
    kCLOCK_BUS_LPSR_ClockRoot_MuxSysPll3Out   = 5U, /*!< BUS_LPSR mux from MuxSysPll3Out. */
    kCLOCK_BUS_LPSR_ClockRoot_MuxSysPll2Out   = 6U, /*!< BUS_LPSR mux from MuxSysPll2Out. */
    kCLOCK_BUS_LPSR_ClockRoot_MuxSysPll1Div5  = 7U, /*!< BUS_LPSR mux from MuxSysPll1Div5. */

    /* SEMC */
    kCLOCK_SEMC_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< SEMC mux from MuxOscRc48MDiv2. */
    kCLOCK_SEMC_ClockRoot_MuxOsc24MOut    = 1U, /*!< SEMC mux from MuxOsc24MOut. */
    kCLOCK_SEMC_ClockRoot_MuxOscRc400M    = 2U, /*!< SEMC mux from MuxOscRc400M. */
    kCLOCK_SEMC_ClockRoot_MuxOscRc16M     = 3U, /*!< SEMC mux from MuxOscRc16M. */
    kCLOCK_SEMC_ClockRoot_MuxSysPll1Div5  = 4U, /*!< SEMC mux from MuxSysPll1Div5. */
    kCLOCK_SEMC_ClockRoot_MuxSysPll2Out   = 5U, /*!< SEMC mux from MuxSysPll2Out. */
    kCLOCK_SEMC_ClockRoot_MuxSysPll2Pfd1  = 6U, /*!< SEMC mux from MuxSysPll2Pfd1. */
    kCLOCK_SEMC_ClockRoot_MuxSysPll3Pfd0  = 7U, /*!< SEMC mux from MuxSysPll3Pfd0. */

    /* CSSYS */
    kCLOCK_CSSYS_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CSSYS mux from MuxOscRc48MDiv2. */
    kCLOCK_CSSYS_ClockRoot_MuxOsc24MOut    = 1U, /*!< CSSYS mux from MuxOsc24MOut. */
    kCLOCK_CSSYS_ClockRoot_MuxOscRc400M    = 2U, /*!< CSSYS mux from MuxOscRc400M. */
    kCLOCK_CSSYS_ClockRoot_MuxOscRc16M     = 3U, /*!< CSSYS mux from MuxOscRc16M. */
    kCLOCK_CSSYS_ClockRoot_MuxSysPll3Div2  = 4U, /*!< CSSYS mux from MuxSysPll3Div2. */
    kCLOCK_CSSYS_ClockRoot_MuxSysPll1Div5  = 5U, /*!< CSSYS mux from MuxSysPll1Div5. */
    kCLOCK_CSSYS_ClockRoot_MuxSysPll2Out   = 6U, /*!< CSSYS mux from MuxSysPll2Out. */
    kCLOCK_CSSYS_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< CSSYS mux from MuxSysPll2Pfd3. */

    /* CSTRACE */
    kCLOCK_CSTRACE_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CSTRACE mux from MuxOscRc48MDiv2. */
    kCLOCK_CSTRACE_ClockRoot_MuxOsc24MOut    = 1U, /*!< CSTRACE mux from MuxOsc24MOut. */
    kCLOCK_CSTRACE_ClockRoot_MuxOscRc400M    = 2U, /*!< CSTRACE mux from MuxOscRc400M. */
    kCLOCK_CSTRACE_ClockRoot_MuxOscRc16M     = 3U, /*!< CSTRACE mux from MuxOscRc16M. */
    kCLOCK_CSTRACE_ClockRoot_MuxSysPll3Div2  = 4U, /*!< CSTRACE mux from MuxSysPll3Div2. */
    kCLOCK_CSTRACE_ClockRoot_MuxSysPll1Div5  = 5U, /*!< CSTRACE mux from MuxSysPll1Div5. */
    kCLOCK_CSTRACE_ClockRoot_MuxSysPll2Pfd1  = 6U, /*!< CSTRACE mux from MuxSysPll2Pfd1. */
    kCLOCK_CSTRACE_ClockRoot_MuxSysPll2Out   = 7U, /*!< CSTRACE mux from MuxSysPll2Out. */

    /* M4_SYSTICK */
    kCLOCK_M4_SYSTICK_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< M4_SYSTICK mux from MuxOscRc48MDiv2. */
    kCLOCK_M4_SYSTICK_ClockRoot_MuxOsc24MOut    = 1U, /*!< M4_SYSTICK mux from MuxOsc24MOut. */
    kCLOCK_M4_SYSTICK_ClockRoot_MuxOscRc400M    = 2U, /*!< M4_SYSTICK mux from MuxOscRc400M. */
    kCLOCK_M4_SYSTICK_ClockRoot_MuxOscRc16M     = 3U, /*!< M4_SYSTICK mux from MuxOscRc16M. */
    kCLOCK_M4_SYSTICK_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< M4_SYSTICK mux from MuxSysPll3Pfd3. */
    kCLOCK_M4_SYSTICK_ClockRoot_MuxSysPll3Out   = 5U, /*!< M4_SYSTICK mux from MuxSysPll3Out. */
    kCLOCK_M4_SYSTICK_ClockRoot_MuxSysPll2Pfd0  = 6U, /*!< M4_SYSTICK mux from MuxSysPll2Pfd0. */
    kCLOCK_M4_SYSTICK_ClockRoot_MuxSysPll1Div5  = 7U, /*!< M4_SYSTICK mux from MuxSysPll1Div5. */

    /* M7_SYSTICK */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< M7_SYSTICK mux from MuxOscRc48MDiv2. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxOsc24MOut    = 1U, /*!< M7_SYSTICK mux from MuxOsc24MOut. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxOscRc400M    = 2U, /*!< M7_SYSTICK mux from MuxOscRc400M. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxOscRc16M     = 3U, /*!< M7_SYSTICK mux from MuxOscRc16M. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxSysPll2Out   = 4U, /*!< M7_SYSTICK mux from MuxSysPll2Out. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxSysPll3Div2  = 5U, /*!< M7_SYSTICK mux from MuxSysPll3Div2. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxSysPll1Div5  = 6U, /*!< M7_SYSTICK mux from MuxSysPll1Div5. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxSysPll2Pfd0  = 7U, /*!< M7_SYSTICK mux from MuxSysPll2Pfd0. */

    /* ADC1 */
    kCLOCK_ADC1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ADC1 mux from MuxOscRc48MDiv2. */
    kCLOCK_ADC1_ClockRoot_MuxOsc24MOut    = 1U, /*!< ADC1 mux from MuxOsc24MOut. */
    kCLOCK_ADC1_ClockRoot_MuxOscRc400M    = 2U, /*!< ADC1 mux from MuxOscRc400M. */
    kCLOCK_ADC1_ClockRoot_MuxOscRc16M     = 3U, /*!< ADC1 mux from MuxOscRc16M. */
    kCLOCK_ADC1_ClockRoot_MuxSysPll3Div2  = 4U, /*!< ADC1 mux from MuxSysPll3Div2. */
    kCLOCK_ADC1_ClockRoot_MuxSysPll1Div5  = 5U, /*!< ADC1 mux from MuxSysPll1Div5. */
    kCLOCK_ADC1_ClockRoot_MuxSysPll2Out   = 6U, /*!< ADC1 mux from MuxSysPll2Out. */
    kCLOCK_ADC1_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< ADC1 mux from MuxSysPll2Pfd3. */

    /* ADC2 */
    kCLOCK_ADC2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ADC2 mux from MuxOscRc48MDiv2. */
    kCLOCK_ADC2_ClockRoot_MuxOsc24MOut    = 1U, /*!< ADC2 mux from MuxOsc24MOut. */
    kCLOCK_ADC2_ClockRoot_MuxOscRc400M    = 2U, /*!< ADC2 mux from MuxOscRc400M. */
    kCLOCK_ADC2_ClockRoot_MuxOscRc16M     = 3U, /*!< ADC2 mux from MuxOscRc16M. */
    kCLOCK_ADC2_ClockRoot_MuxSysPll3Div2  = 4U, /*!< ADC2 mux from MuxSysPll3Div2. */
    kCLOCK_ADC2_ClockRoot_MuxSysPll1Div5  = 5U, /*!< ADC2 mux from MuxSysPll1Div5. */
    kCLOCK_ADC2_ClockRoot_MuxSysPll2Out   = 6U, /*!< ADC2 mux from MuxSysPll2Out. */
    kCLOCK_ADC2_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< ADC2 mux from MuxSysPll2Pfd3. */

    /* ACMP */
    kCLOCK_ACMP_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ACMP mux from MuxOscRc48MDiv2. */
    kCLOCK_ACMP_ClockRoot_MuxOsc24MOut    = 1U, /*!< ACMP mux from MuxOsc24MOut. */
    kCLOCK_ACMP_ClockRoot_MuxOscRc400M    = 2U, /*!< ACMP mux from MuxOscRc400M. */
    kCLOCK_ACMP_ClockRoot_MuxOscRc16M     = 3U, /*!< ACMP mux from MuxOscRc16M. */
    kCLOCK_ACMP_ClockRoot_MuxSysPll3Out   = 4U, /*!< ACMP mux from MuxSysPll3Out. */
    kCLOCK_ACMP_ClockRoot_MuxSysPll1Div5  = 5U, /*!< ACMP mux from MuxSysPll1Div5. */
    kCLOCK_ACMP_ClockRoot_MuxAudioPllOut  = 6U, /*!< ACMP mux from MuxAudioPllOut. */
    kCLOCK_ACMP_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< ACMP mux from MuxSysPll2Pfd3. */

    /* FLEXIO1 */
    kCLOCK_FLEXIO1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< FLEXIO1 mux from MuxOscRc48MDiv2. */
    kCLOCK_FLEXIO1_ClockRoot_MuxOsc24MOut    = 1U, /*!< FLEXIO1 mux from MuxOsc24MOut. */
    kCLOCK_FLEXIO1_ClockRoot_MuxOscRc400M    = 2U, /*!< FLEXIO1 mux from MuxOscRc400M. */
    kCLOCK_FLEXIO1_ClockRoot_MuxOscRc16M     = 3U, /*!< FLEXIO1 mux from MuxOscRc16M. */
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll3Div2  = 4U, /*!< FLEXIO1 mux from MuxSysPll3Div2. */
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll1Div5  = 5U, /*!< FLEXIO1 mux from MuxSysPll1Div5. */
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll2Out   = 6U, /*!< FLEXIO1 mux from MuxSysPll2Out. */
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< FLEXIO1 mux from MuxSysPll2Pfd3. */

    /* FLEXIO2 */
    kCLOCK_FLEXIO2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< FLEXIO2 mux from MuxOscRc48MDiv2. */
    kCLOCK_FLEXIO2_ClockRoot_MuxOsc24MOut    = 1U, /*!< FLEXIO2 mux from MuxOsc24MOut. */
    kCLOCK_FLEXIO2_ClockRoot_MuxOscRc400M    = 2U, /*!< FLEXIO2 mux from MuxOscRc400M. */
    kCLOCK_FLEXIO2_ClockRoot_MuxOscRc16M     = 3U, /*!< FLEXIO2 mux from MuxOscRc16M. */
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll3Div2  = 4U, /*!< FLEXIO2 mux from MuxSysPll3Div2. */
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll1Div5  = 5U, /*!< FLEXIO2 mux from MuxSysPll1Div5. */
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll2Out   = 6U, /*!< FLEXIO2 mux from MuxSysPll2Out. */
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< FLEXIO2 mux from MuxSysPll2Pfd3. */

    /* GPT1 */
    kCLOCK_GPT1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< GPT1 mux from MuxOscRc48MDiv2. */
    kCLOCK_GPT1_ClockRoot_MuxOsc24MOut    = 1U, /*!< GPT1 mux from MuxOsc24MOut. */
    kCLOCK_GPT1_ClockRoot_MuxOscRc400M    = 2U, /*!< GPT1 mux from MuxOscRc400M. */
    kCLOCK_GPT1_ClockRoot_MuxOscRc16M     = 3U, /*!< GPT1 mux from MuxOscRc16M. */
    kCLOCK_GPT1_ClockRoot_MuxSysPll3Div2  = 4U, /*!< GPT1 mux from MuxSysPll3Div2. */
    kCLOCK_GPT1_ClockRoot_MuxSysPll1Div5  = 5U, /*!< GPT1 mux from MuxSysPll1Div5. */
    kCLOCK_GPT1_ClockRoot_MuxSysPll3Pfd2  = 6U, /*!< GPT1 mux from MuxSysPll3Pfd2. */
    kCLOCK_GPT1_ClockRoot_MuxSysPll3Pfd3  = 7U, /*!< GPT1 mux from MuxSysPll3Pfd3. */

    /* GPT2 */
    kCLOCK_GPT2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< GPT2 mux from MuxOscRc48MDiv2. */
    kCLOCK_GPT2_ClockRoot_MuxOsc24MOut    = 1U, /*!< GPT2 mux from MuxOsc24MOut. */
    kCLOCK_GPT2_ClockRoot_MuxOscRc400M    = 2U, /*!< GPT2 mux from MuxOscRc400M. */
    kCLOCK_GPT2_ClockRoot_MuxOscRc16M     = 3U, /*!< GPT2 mux from MuxOscRc16M. */
    kCLOCK_GPT2_ClockRoot_MuxSysPll3Div2  = 4U, /*!< GPT2 mux from MuxSysPll3Div2. */
    kCLOCK_GPT2_ClockRoot_MuxSysPll1Div5  = 5U, /*!< GPT2 mux from MuxSysPll1Div5. */
    kCLOCK_GPT2_ClockRoot_MuxAudioPllOut  = 6U, /*!< GPT2 mux from MuxAudioPllOut. */
    kCLOCK_GPT2_ClockRoot_MuxVideoPllOut  = 7U, /*!< GPT2 mux from MuxVideoPllOut. */

    /* GPT3 */
    kCLOCK_GPT3_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< GPT3 mux from MuxOscRc48MDiv2. */
    kCLOCK_GPT3_ClockRoot_MuxOsc24MOut    = 1U, /*!< GPT3 mux from MuxOsc24MOut. */
    kCLOCK_GPT3_ClockRoot_MuxOscRc400M    = 2U, /*!< GPT3 mux from MuxOscRc400M. */
    kCLOCK_GPT3_ClockRoot_MuxOscRc16M     = 3U, /*!< GPT3 mux from MuxOscRc16M. */
    kCLOCK_GPT3_ClockRoot_MuxSysPll3Div2  = 4U, /*!< GPT3 mux from MuxSysPll3Div2. */
    kCLOCK_GPT3_ClockRoot_MuxSysPll1Div5  = 5U, /*!< GPT3 mux from MuxSysPll1Div5. */
    kCLOCK_GPT3_ClockRoot_MuxAudioPllOut  = 6U, /*!< GPT3 mux from MuxAudioPllOut. */
    kCLOCK_GPT3_ClockRoot_MuxVideoPllOut  = 7U, /*!< GPT3 mux from MuxVideoPllOut. */

    /* GPT4 */
    kCLOCK_GPT4_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< GPT4 mux from MuxOscRc48MDiv2. */
    kCLOCK_GPT4_ClockRoot_MuxOsc24MOut    = 1U, /*!< GPT4 mux from MuxOsc24MOut. */
    kCLOCK_GPT4_ClockRoot_MuxOscRc400M    = 2U, /*!< GPT4 mux from MuxOscRc400M. */
    kCLOCK_GPT4_ClockRoot_MuxOscRc16M     = 3U, /*!< GPT4 mux from MuxOscRc16M. */
    kCLOCK_GPT4_ClockRoot_MuxSysPll3Div2  = 4U, /*!< GPT4 mux from MuxSysPll3Div2. */
    kCLOCK_GPT4_ClockRoot_MuxSysPll1Div5  = 5U, /*!< GPT4 mux from MuxSysPll1Div5. */
    kCLOCK_GPT4_ClockRoot_MuxSysPll3Pfd2  = 6U, /*!< GPT4 mux from MuxSysPll3Pfd2. */
    kCLOCK_GPT4_ClockRoot_MuxSysPll3Pfd3  = 7U, /*!< GPT4 mux from MuxSysPll3Pfd3. */

    /* GPT5 */
    kCLOCK_GPT5_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< GPT5 mux from MuxOscRc48MDiv2. */
    kCLOCK_GPT5_ClockRoot_MuxOsc24MOut    = 1U, /*!< GPT5 mux from MuxOsc24MOut. */
    kCLOCK_GPT5_ClockRoot_MuxOscRc400M    = 2U, /*!< GPT5 mux from MuxOscRc400M. */
    kCLOCK_GPT5_ClockRoot_MuxOscRc16M     = 3U, /*!< GPT5 mux from MuxOscRc16M. */
    kCLOCK_GPT5_ClockRoot_MuxSysPll3Div2  = 4U, /*!< GPT5 mux from MuxSysPll3Div2. */
    kCLOCK_GPT5_ClockRoot_MuxSysPll1Div5  = 5U, /*!< GPT5 mux from MuxSysPll1Div5. */
    kCLOCK_GPT5_ClockRoot_MuxSysPll3Pfd2  = 6U, /*!< GPT5 mux from MuxSysPll3Pfd2. */
    kCLOCK_GPT5_ClockRoot_MuxSysPll3Pfd3  = 7U, /*!< GPT5 mux from MuxSysPll3Pfd3. */

    /* GPT6 */
    kCLOCK_GPT6_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< GPT6 mux from MuxOscRc48MDiv2. */
    kCLOCK_GPT6_ClockRoot_MuxOsc24MOut    = 1U, /*!< GPT6 mux from MuxOsc24MOut. */
    kCLOCK_GPT6_ClockRoot_MuxOscRc400M    = 2U, /*!< GPT6 mux from MuxOscRc400M. */
    kCLOCK_GPT6_ClockRoot_MuxOscRc16M     = 3U, /*!< GPT6 mux from MuxOscRc16M. */
    kCLOCK_GPT6_ClockRoot_MuxSysPll3Div2  = 4U, /*!< GPT6 mux from MuxSysPll3Div2. */
    kCLOCK_GPT6_ClockRoot_MuxSysPll1Div5  = 5U, /*!< GPT6 mux from MuxSysPll1Div5. */
    kCLOCK_GPT6_ClockRoot_MuxSysPll3Pfd2  = 6U, /*!< GPT6 mux from MuxSysPll3Pfd2. */
    kCLOCK_GPT6_ClockRoot_MuxSysPll3Pfd3  = 7U, /*!< GPT6 mux from MuxSysPll3Pfd3. */

    /* FLEXSPI1 */
    kCLOCK_FLEXSPI1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< FLEXSPI1 mux from MuxOscRc48MDiv2. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxOsc24MOut    = 1U, /*!< FLEXSPI1 mux from MuxOsc24MOut. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxOscRc400M    = 2U, /*!< FLEXSPI1 mux from MuxOscRc400M. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxOscRc16M     = 3U, /*!< FLEXSPI1 mux from MuxOscRc16M. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll3Pfd0  = 4U, /*!< FLEXSPI1 mux from MuxSysPll3Pfd0. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll2Out   = 5U, /*!< FLEXSPI1 mux from MuxSysPll2Out. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll2Pfd2  = 6U, /*!< FLEXSPI1 mux from MuxSysPll2Pfd2. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll3Out   = 7U, /*!< FLEXSPI1 mux from MuxSysPll3Out. */

    /* FLEXSPI2 */
    kCLOCK_FLEXSPI2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< FLEXSPI2 mux from MuxOscRc48MDiv2. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxOsc24MOut    = 1U, /*!< FLEXSPI2 mux from MuxOsc24MOut. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxOscRc400M    = 2U, /*!< FLEXSPI2 mux from MuxOscRc400M. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxOscRc16M     = 3U, /*!< FLEXSPI2 mux from MuxOscRc16M. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxSysPll3Pfd0  = 4U, /*!< FLEXSPI2 mux from MuxSysPll3Pfd0. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxSysPll2Out   = 5U, /*!< FLEXSPI2 mux from MuxSysPll2Out. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxSysPll2Pfd2  = 6U, /*!< FLEXSPI2 mux from MuxSysPll2Pfd2. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxSysPll3Out   = 7U, /*!< FLEXSPI2 mux from MuxSysPll3Out. */

    /* CAN1 */
    kCLOCK_CAN1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CAN1 mux from MuxOscRc48MDiv2. */
    kCLOCK_CAN1_ClockRoot_MuxOsc24MOut    = 1U, /*!< CAN1 mux from MuxOsc24MOut. */
    kCLOCK_CAN1_ClockRoot_MuxOscRc400M    = 2U, /*!< CAN1 mux from MuxOscRc400M. */
    kCLOCK_CAN1_ClockRoot_MuxOscRc16M     = 3U, /*!< CAN1 mux from MuxOscRc16M. */
    kCLOCK_CAN1_ClockRoot_MuxSysPll3Div2  = 4U, /*!< CAN1 mux from MuxSysPll3Div2. */
    kCLOCK_CAN1_ClockRoot_MuxSysPll1Div5  = 5U, /*!< CAN1 mux from MuxSysPll1Div5. */
    kCLOCK_CAN1_ClockRoot_MuxSysPll2Out   = 6U, /*!< CAN1 mux from MuxSysPll2Out. */
    kCLOCK_CAN1_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< CAN1 mux from MuxSysPll2Pfd3. */

    /* CAN2 */
    kCLOCK_CAN2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CAN2 mux from MuxOscRc48MDiv2. */
    kCLOCK_CAN2_ClockRoot_MuxOsc24MOut    = 1U, /*!< CAN2 mux from MuxOsc24MOut. */
    kCLOCK_CAN2_ClockRoot_MuxOscRc400M    = 2U, /*!< CAN2 mux from MuxOscRc400M. */
    kCLOCK_CAN2_ClockRoot_MuxOscRc16M     = 3U, /*!< CAN2 mux from MuxOscRc16M. */
    kCLOCK_CAN2_ClockRoot_MuxSysPll3Div2  = 4U, /*!< CAN2 mux from MuxSysPll3Div2. */
    kCLOCK_CAN2_ClockRoot_MuxSysPll1Div5  = 5U, /*!< CAN2 mux from MuxSysPll1Div5. */
    kCLOCK_CAN2_ClockRoot_MuxSysPll2Out   = 6U, /*!< CAN2 mux from MuxSysPll2Out. */
    kCLOCK_CAN2_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< CAN2 mux from MuxSysPll2Pfd3. */

    /* CAN3 */
    kCLOCK_CAN3_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CAN3 mux from MuxOscRc48MDiv2. */
    kCLOCK_CAN3_ClockRoot_MuxOsc24MOut    = 1U, /*!< CAN3 mux from MuxOsc24MOut. */
    kCLOCK_CAN3_ClockRoot_MuxOscRc400M    = 2U, /*!< CAN3 mux from MuxOscRc400M. */
    kCLOCK_CAN3_ClockRoot_MuxOscRc16M     = 3U, /*!< CAN3 mux from MuxOscRc16M. */
    kCLOCK_CAN3_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< CAN3 mux from MuxSysPll3Pfd3. */
    kCLOCK_CAN3_ClockRoot_MuxSysPll3Out   = 5U, /*!< CAN3 mux from MuxSysPll3Out. */
    kCLOCK_CAN3_ClockRoot_MuxSysPll2Pfd3  = 6U, /*!< CAN3 mux from MuxSysPll2Pfd3. */
    kCLOCK_CAN3_ClockRoot_MuxSysPll1Div5  = 7U, /*!< CAN3 mux from MuxSysPll1Div5. */

    /* LPUART1 */
    kCLOCK_LPUART1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART1 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART1_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART1 mux from MuxOsc24MOut. */
    kCLOCK_LPUART1_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART1 mux from MuxOscRc400M. */
    kCLOCK_LPUART1_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART1 mux from MuxOscRc16M. */
    kCLOCK_LPUART1_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART1 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART1_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART1 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART1_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART1 mux from MuxSysPll2Out. */
    kCLOCK_LPUART1_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART1 mux from MuxSysPll2Pfd3. */

    /* LPUART2 */
    kCLOCK_LPUART2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART2 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART2_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART2 mux from MuxOsc24MOut. */
    kCLOCK_LPUART2_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART2 mux from MuxOscRc400M. */
    kCLOCK_LPUART2_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART2 mux from MuxOscRc16M. */
    kCLOCK_LPUART2_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART2 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART2_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART2 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART2_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART2 mux from MuxSysPll2Out. */
    kCLOCK_LPUART2_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART2 mux from MuxSysPll2Pfd3. */

    /* LPUART3 */
    kCLOCK_LPUART3_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART3 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART3_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART3 mux from MuxOsc24MOut. */
    kCLOCK_LPUART3_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART3 mux from MuxOscRc400M. */
    kCLOCK_LPUART3_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART3 mux from MuxOscRc16M. */
    kCLOCK_LPUART3_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART3 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART3_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART3 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART3_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART3 mux from MuxSysPll2Out. */
    kCLOCK_LPUART3_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART3 mux from MuxSysPll2Pfd3. */

    /* LPUART4 */
    kCLOCK_LPUART4_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART4 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART4_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART4 mux from MuxOsc24MOut. */
    kCLOCK_LPUART4_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART4 mux from MuxOscRc400M. */
    kCLOCK_LPUART4_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART4 mux from MuxOscRc16M. */
    kCLOCK_LPUART4_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART4 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART4_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART4 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART4_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART4 mux from MuxSysPll2Out. */
    kCLOCK_LPUART4_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART4 mux from MuxSysPll2Pfd3. */

    /* LPUART5 */
    kCLOCK_LPUART5_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART5 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART5_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART5 mux from MuxOsc24MOut. */
    kCLOCK_LPUART5_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART5 mux from MuxOscRc400M. */
    kCLOCK_LPUART5_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART5 mux from MuxOscRc16M. */
    kCLOCK_LPUART5_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART5 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART5_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART5 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART5_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART5 mux from MuxSysPll2Out. */
    kCLOCK_LPUART5_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART5 mux from MuxSysPll2Pfd3. */

    /* LPUART6 */
    kCLOCK_LPUART6_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART6 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART6_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART6 mux from MuxOsc24MOut. */
    kCLOCK_LPUART6_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART6 mux from MuxOscRc400M. */
    kCLOCK_LPUART6_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART6 mux from MuxOscRc16M. */
    kCLOCK_LPUART6_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART6 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART6_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART6 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART6_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART6 mux from MuxSysPll2Out. */
    kCLOCK_LPUART6_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART6 mux from MuxSysPll2Pfd3. */

    /* LPUART7 */
    kCLOCK_LPUART7_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART7 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART7_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART7 mux from MuxOsc24MOut. */
    kCLOCK_LPUART7_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART7 mux from MuxOscRc400M. */
    kCLOCK_LPUART7_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART7 mux from MuxOscRc16M. */
    kCLOCK_LPUART7_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART7 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART7_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART7 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART7_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART7 mux from MuxSysPll2Out. */
    kCLOCK_LPUART7_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART7 mux from MuxSysPll2Pfd3. */

    /* LPUART8 */
    kCLOCK_LPUART8_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART8 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART8_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART8 mux from MuxOsc24MOut. */
    kCLOCK_LPUART8_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART8 mux from MuxOscRc400M. */
    kCLOCK_LPUART8_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART8 mux from MuxOscRc16M. */
    kCLOCK_LPUART8_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART8 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART8_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART8 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART8_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART8 mux from MuxSysPll2Out. */
    kCLOCK_LPUART8_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART8 mux from MuxSysPll2Pfd3. */

    /* LPUART9 */
    kCLOCK_LPUART9_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART9 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART9_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART9 mux from MuxOsc24MOut. */
    kCLOCK_LPUART9_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART9 mux from MuxOscRc400M. */
    kCLOCK_LPUART9_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART9 mux from MuxOscRc16M. */
    kCLOCK_LPUART9_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART9 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART9_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART9 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART9_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART9 mux from MuxSysPll2Out. */
    kCLOCK_LPUART9_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART9 mux from MuxSysPll2Pfd3. */

    /* LPUART10 */
    kCLOCK_LPUART10_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART10 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART10_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART10 mux from MuxOsc24MOut. */
    kCLOCK_LPUART10_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART10 mux from MuxOscRc400M. */
    kCLOCK_LPUART10_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART10 mux from MuxOscRc16M. */
    kCLOCK_LPUART10_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPUART10 mux from MuxSysPll3Div2. */
    kCLOCK_LPUART10_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPUART10 mux from MuxSysPll1Div5. */
    kCLOCK_LPUART10_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPUART10 mux from MuxSysPll2Out. */
    kCLOCK_LPUART10_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPUART10 mux from MuxSysPll2Pfd3. */

    /* LPUART11 */
    kCLOCK_LPUART11_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART11 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART11_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART11 mux from MuxOsc24MOut. */
    kCLOCK_LPUART11_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART11 mux from MuxOscRc400M. */
    kCLOCK_LPUART11_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART11 mux from MuxOscRc16M. */
    kCLOCK_LPUART11_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< LPUART11 mux from MuxSysPll3Pfd3. */
    kCLOCK_LPUART11_ClockRoot_MuxSysPll3Out   = 5U, /*!< LPUART11 mux from MuxSysPll3Out. */
    kCLOCK_LPUART11_ClockRoot_MuxSysPll2Pfd3  = 6U, /*!< LPUART11 mux from MuxSysPll2Pfd3. */
    kCLOCK_LPUART11_ClockRoot_MuxSysPll1Div5  = 7U, /*!< LPUART11 mux from MuxSysPll1Div5. */

    /* LPUART12 */
    kCLOCK_LPUART12_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPUART12 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPUART12_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPUART12 mux from MuxOsc24MOut. */
    kCLOCK_LPUART12_ClockRoot_MuxOscRc400M    = 2U, /*!< LPUART12 mux from MuxOscRc400M. */
    kCLOCK_LPUART12_ClockRoot_MuxOscRc16M     = 3U, /*!< LPUART12 mux from MuxOscRc16M. */
    kCLOCK_LPUART12_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< LPUART12 mux from MuxSysPll3Pfd3. */
    kCLOCK_LPUART12_ClockRoot_MuxSysPll3Out   = 5U, /*!< LPUART12 mux from MuxSysPll3Out. */
    kCLOCK_LPUART12_ClockRoot_MuxSysPll2Pfd3  = 6U, /*!< LPUART12 mux from MuxSysPll2Pfd3. */
    kCLOCK_LPUART12_ClockRoot_MuxSysPll1Div5  = 7U, /*!< LPUART12 mux from MuxSysPll1Div5. */

    /* LPI2C1 */
    kCLOCK_LPI2C1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPI2C1 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPI2C1_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPI2C1 mux from MuxOsc24MOut. */
    kCLOCK_LPI2C1_ClockRoot_MuxOscRc400M    = 2U, /*!< LPI2C1 mux from MuxOscRc400M. */
    kCLOCK_LPI2C1_ClockRoot_MuxOscRc16M     = 3U, /*!< LPI2C1 mux from MuxOscRc16M. */
    kCLOCK_LPI2C1_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPI2C1 mux from MuxSysPll3Div2. */
    kCLOCK_LPI2C1_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPI2C1 mux from MuxSysPll1Div5. */
    kCLOCK_LPI2C1_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPI2C1 mux from MuxSysPll2Out. */
    kCLOCK_LPI2C1_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPI2C1 mux from MuxSysPll2Pfd3. */

    /* LPI2C2 */
    kCLOCK_LPI2C2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPI2C2 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPI2C2_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPI2C2 mux from MuxOsc24MOut. */
    kCLOCK_LPI2C2_ClockRoot_MuxOscRc400M    = 2U, /*!< LPI2C2 mux from MuxOscRc400M. */
    kCLOCK_LPI2C2_ClockRoot_MuxOscRc16M     = 3U, /*!< LPI2C2 mux from MuxOscRc16M. */
    kCLOCK_LPI2C2_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPI2C2 mux from MuxSysPll3Div2. */
    kCLOCK_LPI2C2_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPI2C2 mux from MuxSysPll1Div5. */
    kCLOCK_LPI2C2_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPI2C2 mux from MuxSysPll2Out. */
    kCLOCK_LPI2C2_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPI2C2 mux from MuxSysPll2Pfd3. */

    /* LPI2C3 */
    kCLOCK_LPI2C3_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPI2C3 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPI2C3_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPI2C3 mux from MuxOsc24MOut. */
    kCLOCK_LPI2C3_ClockRoot_MuxOscRc400M    = 2U, /*!< LPI2C3 mux from MuxOscRc400M. */
    kCLOCK_LPI2C3_ClockRoot_MuxOscRc16M     = 3U, /*!< LPI2C3 mux from MuxOscRc16M. */
    kCLOCK_LPI2C3_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPI2C3 mux from MuxSysPll3Div2. */
    kCLOCK_LPI2C3_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPI2C3 mux from MuxSysPll1Div5. */
    kCLOCK_LPI2C3_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPI2C3 mux from MuxSysPll2Out. */
    kCLOCK_LPI2C3_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPI2C3 mux from MuxSysPll2Pfd3. */

    /* LPI2C4 */
    kCLOCK_LPI2C4_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPI2C4 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPI2C4_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPI2C4 mux from MuxOsc24MOut. */
    kCLOCK_LPI2C4_ClockRoot_MuxOscRc400M    = 2U, /*!< LPI2C4 mux from MuxOscRc400M. */
    kCLOCK_LPI2C4_ClockRoot_MuxOscRc16M     = 3U, /*!< LPI2C4 mux from MuxOscRc16M. */
    kCLOCK_LPI2C4_ClockRoot_MuxSysPll3Div2  = 4U, /*!< LPI2C4 mux from MuxSysPll3Div2. */
    kCLOCK_LPI2C4_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPI2C4 mux from MuxSysPll1Div5. */
    kCLOCK_LPI2C4_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPI2C4 mux from MuxSysPll2Out. */
    kCLOCK_LPI2C4_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPI2C4 mux from MuxSysPll2Pfd3. */

    /* LPI2C5 */
    kCLOCK_LPI2C5_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPI2C5 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPI2C5_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPI2C5 mux from MuxOsc24MOut. */
    kCLOCK_LPI2C5_ClockRoot_MuxOscRc400M    = 2U, /*!< LPI2C5 mux from MuxOscRc400M. */
    kCLOCK_LPI2C5_ClockRoot_MuxOscRc16M     = 3U, /*!< LPI2C5 mux from MuxOscRc16M. */
    kCLOCK_LPI2C5_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< LPI2C5 mux from MuxSysPll3Pfd3. */
    kCLOCK_LPI2C5_ClockRoot_MuxSysPll3Out   = 5U, /*!< LPI2C5 mux from MuxSysPll3Out. */
    kCLOCK_LPI2C5_ClockRoot_MuxSysPll2Pfd3  = 6U, /*!< LPI2C5 mux from MuxSysPll2Pfd3. */
    kCLOCK_LPI2C5_ClockRoot_MuxSysPll1Div5  = 7U, /*!< LPI2C5 mux from MuxSysPll1Div5. */

    /* LPI2C6 */
    kCLOCK_LPI2C6_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPI2C6 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPI2C6_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPI2C6 mux from MuxOsc24MOut. */
    kCLOCK_LPI2C6_ClockRoot_MuxOscRc400M    = 2U, /*!< LPI2C6 mux from MuxOscRc400M. */
    kCLOCK_LPI2C6_ClockRoot_MuxOscRc16M     = 3U, /*!< LPI2C6 mux from MuxOscRc16M. */
    kCLOCK_LPI2C6_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< LPI2C6 mux from MuxSysPll3Pfd3. */
    kCLOCK_LPI2C6_ClockRoot_MuxSysPll3Out   = 5U, /*!< LPI2C6 mux from MuxSysPll3Out. */
    kCLOCK_LPI2C6_ClockRoot_MuxSysPll2Pfd3  = 6U, /*!< LPI2C6 mux from MuxSysPll2Pfd3. */
    kCLOCK_LPI2C6_ClockRoot_MuxSysPll1Div5  = 7U, /*!< LPI2C6 mux from MuxSysPll1Div5. */

    /* LPSPI1 */
    kCLOCK_LPSPI1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPSPI1 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPSPI1_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPSPI1 mux from MuxOsc24MOut. */
    kCLOCK_LPSPI1_ClockRoot_MuxOscRc400M    = 2U, /*!< LPSPI1 mux from MuxOscRc400M. */
    kCLOCK_LPSPI1_ClockRoot_MuxOscRc16M     = 3U, /*!< LPSPI1 mux from MuxOscRc16M. */
    kCLOCK_LPSPI1_ClockRoot_MuxSysPll3Pfd2  = 4U, /*!< LPSPI1 mux from MuxSysPll3Pfd2. */
    kCLOCK_LPSPI1_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPSPI1 mux from MuxSysPll1Div5. */
    kCLOCK_LPSPI1_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPSPI1 mux from MuxSysPll2Out. */
    kCLOCK_LPSPI1_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPSPI1 mux from MuxSysPll2Pfd3. */

    /* LPSPI2 */
    kCLOCK_LPSPI2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPSPI2 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPSPI2_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPSPI2 mux from MuxOsc24MOut. */
    kCLOCK_LPSPI2_ClockRoot_MuxOscRc400M    = 2U, /*!< LPSPI2 mux from MuxOscRc400M. */
    kCLOCK_LPSPI2_ClockRoot_MuxOscRc16M     = 3U, /*!< LPSPI2 mux from MuxOscRc16M. */
    kCLOCK_LPSPI2_ClockRoot_MuxSysPll3Pfd2  = 4U, /*!< LPSPI2 mux from MuxSysPll3Pfd2. */
    kCLOCK_LPSPI2_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPSPI2 mux from MuxSysPll1Div5. */
    kCLOCK_LPSPI2_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPSPI2 mux from MuxSysPll2Out. */
    kCLOCK_LPSPI2_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPSPI2 mux from MuxSysPll2Pfd3. */

    /* LPSPI3 */
    kCLOCK_LPSPI3_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPSPI3 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPSPI3_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPSPI3 mux from MuxOsc24MOut. */
    kCLOCK_LPSPI3_ClockRoot_MuxOscRc400M    = 2U, /*!< LPSPI3 mux from MuxOscRc400M. */
    kCLOCK_LPSPI3_ClockRoot_MuxOscRc16M     = 3U, /*!< LPSPI3 mux from MuxOscRc16M. */
    kCLOCK_LPSPI3_ClockRoot_MuxSysPll3Pfd2  = 4U, /*!< LPSPI3 mux from MuxSysPll3Pfd2. */
    kCLOCK_LPSPI3_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPSPI3 mux from MuxSysPll1Div5. */
    kCLOCK_LPSPI3_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPSPI3 mux from MuxSysPll2Out. */
    kCLOCK_LPSPI3_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPSPI3 mux from MuxSysPll2Pfd3. */

    /* LPSPI4 */
    kCLOCK_LPSPI4_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPSPI4 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPSPI4_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPSPI4 mux from MuxOsc24MOut. */
    kCLOCK_LPSPI4_ClockRoot_MuxOscRc400M    = 2U, /*!< LPSPI4 mux from MuxOscRc400M. */
    kCLOCK_LPSPI4_ClockRoot_MuxOscRc16M     = 3U, /*!< LPSPI4 mux from MuxOscRc16M. */
    kCLOCK_LPSPI4_ClockRoot_MuxSysPll3Pfd2  = 4U, /*!< LPSPI4 mux from MuxSysPll3Pfd2. */
    kCLOCK_LPSPI4_ClockRoot_MuxSysPll1Div5  = 5U, /*!< LPSPI4 mux from MuxSysPll1Div5. */
    kCLOCK_LPSPI4_ClockRoot_MuxSysPll2Out   = 6U, /*!< LPSPI4 mux from MuxSysPll2Out. */
    kCLOCK_LPSPI4_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< LPSPI4 mux from MuxSysPll2Pfd3. */

    /* LPSPI5 */
    kCLOCK_LPSPI5_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPSPI5 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPSPI5_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPSPI5 mux from MuxOsc24MOut. */
    kCLOCK_LPSPI5_ClockRoot_MuxOscRc400M    = 2U, /*!< LPSPI5 mux from MuxOscRc400M. */
    kCLOCK_LPSPI5_ClockRoot_MuxOscRc16M     = 3U, /*!< LPSPI5 mux from MuxOscRc16M. */
    kCLOCK_LPSPI5_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< LPSPI5 mux from MuxSysPll3Pfd3. */
    kCLOCK_LPSPI5_ClockRoot_MuxSysPll3Out   = 5U, /*!< LPSPI5 mux from MuxSysPll3Out. */
    kCLOCK_LPSPI5_ClockRoot_MuxSysPll3Pfd2  = 6U, /*!< LPSPI5 mux from MuxSysPll3Pfd2. */
    kCLOCK_LPSPI5_ClockRoot_MuxSysPll1Div5  = 7U, /*!< LPSPI5 mux from MuxSysPll1Div5. */

    /* LPSPI6 */
    kCLOCK_LPSPI6_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LPSPI6 mux from MuxOscRc48MDiv2. */
    kCLOCK_LPSPI6_ClockRoot_MuxOsc24MOut    = 1U, /*!< LPSPI6 mux from MuxOsc24MOut. */
    kCLOCK_LPSPI6_ClockRoot_MuxOscRc400M    = 2U, /*!< LPSPI6 mux from MuxOscRc400M. */
    kCLOCK_LPSPI6_ClockRoot_MuxOscRc16M     = 3U, /*!< LPSPI6 mux from MuxOscRc16M. */
    kCLOCK_LPSPI6_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< LPSPI6 mux from MuxSysPll3Pfd3. */
    kCLOCK_LPSPI6_ClockRoot_MuxSysPll3Out   = 5U, /*!< LPSPI6 mux from MuxSysPll3Out. */
    kCLOCK_LPSPI6_ClockRoot_MuxSysPll3Pfd2  = 6U, /*!< LPSPI6 mux from MuxSysPll3Pfd2. */
    kCLOCK_LPSPI6_ClockRoot_MuxSysPll1Div5  = 7U, /*!< LPSPI6 mux from MuxSysPll1Div5. */

    /* EMV1 */
    kCLOCK_EMV1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< EMV1 mux from MuxOscRc48MDiv2. */
    kCLOCK_EMV1_ClockRoot_MuxOsc24MOut    = 1U, /*!< EMV1 mux from MuxOsc24MOut. */
    kCLOCK_EMV1_ClockRoot_MuxOscRc400M    = 2U, /*!< EMV1 mux from MuxOscRc400M. */
    kCLOCK_EMV1_ClockRoot_MuxOscRc16M     = 3U, /*!< EMV1 mux from MuxOscRc16M. */
    kCLOCK_EMV1_ClockRoot_MuxSysPll3Div2  = 4U, /*!< EMV1 mux from MuxSysPll3Div2. */
    kCLOCK_EMV1_ClockRoot_MuxSysPll1Div5  = 5U, /*!< EMV1 mux from MuxSysPll1Div5. */
    kCLOCK_EMV1_ClockRoot_MuxSysPll2Out   = 6U, /*!< EMV1 mux from MuxSysPll2Out. */
    kCLOCK_EMV1_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< EMV1 mux from MuxSysPll2Pfd3. */

    /* EMV2 */
    kCLOCK_EMV2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< EMV2 mux from MuxOscRc48MDiv2. */
    kCLOCK_EMV2_ClockRoot_MuxOsc24MOut    = 1U, /*!< EMV2 mux from MuxOsc24MOut. */
    kCLOCK_EMV2_ClockRoot_MuxOscRc400M    = 2U, /*!< EMV2 mux from MuxOscRc400M. */
    kCLOCK_EMV2_ClockRoot_MuxOscRc16M     = 3U, /*!< EMV2 mux from MuxOscRc16M. */
    kCLOCK_EMV2_ClockRoot_MuxSysPll3Div2  = 4U, /*!< EMV2 mux from MuxSysPll3Div2. */
    kCLOCK_EMV2_ClockRoot_MuxSysPll1Div5  = 5U, /*!< EMV2 mux from MuxSysPll1Div5. */
    kCLOCK_EMV2_ClockRoot_MuxSysPll2Out   = 6U, /*!< EMV2 mux from MuxSysPll2Out. */
    kCLOCK_EMV2_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< EMV2 mux from MuxSysPll2Pfd3. */

    /* ENET1 */
    kCLOCK_ENET1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ENET1 mux from MuxOscRc48MDiv2. */
    kCLOCK_ENET1_ClockRoot_MuxOsc24MOut    = 1U, /*!< ENET1 mux from MuxOsc24MOut. */
    kCLOCK_ENET1_ClockRoot_MuxOscRc400M    = 2U, /*!< ENET1 mux from MuxOscRc400M. */
    kCLOCK_ENET1_ClockRoot_MuxOscRc16M     = 3U, /*!< ENET1 mux from MuxOscRc16M. */
    kCLOCK_ENET1_ClockRoot_MuxSysPll1Div2  = 4U, /*!< ENET1 mux from MuxSysPll1Div2. */
    kCLOCK_ENET1_ClockRoot_MuxAudioPllOut  = 5U, /*!< ENET1 mux from MuxAudioPllOut. */
    kCLOCK_ENET1_ClockRoot_MuxSysPll1Div5  = 6U, /*!< ENET1 mux from MuxSysPll1Div5. */
    kCLOCK_ENET1_ClockRoot_MuxSysPll2Pfd1  = 7U, /*!< ENET1 mux from MuxSysPll2Pfd1. */

    /* ENET2 */
    kCLOCK_ENET2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ENET2 mux from MuxOscRc48MDiv2. */
    kCLOCK_ENET2_ClockRoot_MuxOsc24MOut    = 1U, /*!< ENET2 mux from MuxOsc24MOut. */
    kCLOCK_ENET2_ClockRoot_MuxOscRc400M    = 2U, /*!< ENET2 mux from MuxOscRc400M. */
    kCLOCK_ENET2_ClockRoot_MuxOscRc16M     = 3U, /*!< ENET2 mux from MuxOscRc16M. */
    kCLOCK_ENET2_ClockRoot_MuxSysPll1Div2  = 4U, /*!< ENET2 mux from MuxSysPll1Div2. */
    kCLOCK_ENET2_ClockRoot_MuxAudioPllOut  = 5U, /*!< ENET2 mux from MuxAudioPllOut. */
    kCLOCK_ENET2_ClockRoot_MuxSysPll1Div5  = 6U, /*!< ENET2 mux from MuxSysPll1Div5. */
    kCLOCK_ENET2_ClockRoot_MuxSysPll2Pfd1  = 7U, /*!< ENET2 mux from MuxSysPll2Pfd1. */

    /* ENET_QOS */
    kCLOCK_ENET_QOS_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ENET_QOS mux from MuxOscRc48MDiv2. */
    kCLOCK_ENET_QOS_ClockRoot_MuxOsc24MOut    = 1U, /*!< ENET_QOS mux from MuxOsc24MOut. */
    kCLOCK_ENET_QOS_ClockRoot_MuxOscRc400M    = 2U, /*!< ENET_QOS mux from MuxOscRc400M. */
    kCLOCK_ENET_QOS_ClockRoot_MuxOscRc16M     = 3U, /*!< ENET_QOS mux from MuxOscRc16M. */
    kCLOCK_ENET_QOS_ClockRoot_MuxSysPll1Div2  = 4U, /*!< ENET_QOS mux from MuxSysPll1Div2. */
    kCLOCK_ENET_QOS_ClockRoot_MuxAudioPllOut  = 5U, /*!< ENET_QOS mux from MuxAudioPllOut. */
    kCLOCK_ENET_QOS_ClockRoot_MuxSysPll1Div5  = 6U, /*!< ENET_QOS mux from MuxSysPll1Div5. */
    kCLOCK_ENET_QOS_ClockRoot_MuxSysPll2Pfd1  = 7U, /*!< ENET_QOS mux from MuxSysPll2Pfd1. */

    /* ENET_25M */
    kCLOCK_ENET_25M_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ENET_25M mux from MuxOscRc48MDiv2. */
    kCLOCK_ENET_25M_ClockRoot_MuxOsc24MOut    = 1U, /*!< ENET_25M mux from MuxOsc24MOut. */
    kCLOCK_ENET_25M_ClockRoot_MuxOscRc400M    = 2U, /*!< ENET_25M mux from MuxOscRc400M. */
    kCLOCK_ENET_25M_ClockRoot_MuxOscRc16M     = 3U, /*!< ENET_25M mux from MuxOscRc16M. */
    kCLOCK_ENET_25M_ClockRoot_MuxSysPll1Div2  = 4U, /*!< ENET_25M mux from MuxSysPll1Div2. */
    kCLOCK_ENET_25M_ClockRoot_MuxAudioPllOut  = 5U, /*!< ENET_25M mux from MuxAudioPllOut. */
    kCLOCK_ENET_25M_ClockRoot_MuxSysPll1Div5  = 6U, /*!< ENET_25M mux from MuxSysPll1Div5. */
    kCLOCK_ENET_25M_ClockRoot_MuxSysPll2Pfd1  = 7U, /*!< ENET_25M mux from MuxSysPll2Pfd1. */

    /* ENET_TIMER1 */
    kCLOCK_ENET_TIMER1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ENET_TIMER1 mux from MuxOscRc48MDiv2. */
    kCLOCK_ENET_TIMER1_ClockRoot_MuxOsc24MOut    = 1U, /*!< ENET_TIMER1 mux from MuxOsc24MOut. */
    kCLOCK_ENET_TIMER1_ClockRoot_MuxOscRc400M    = 2U, /*!< ENET_TIMER1 mux from MuxOscRc400M. */
    kCLOCK_ENET_TIMER1_ClockRoot_MuxOscRc16M     = 3U, /*!< ENET_TIMER1 mux from MuxOscRc16M. */
    kCLOCK_ENET_TIMER1_ClockRoot_MuxSysPll1Div2  = 4U, /*!< ENET_TIMER1 mux from MuxSysPll1Div2. */
    kCLOCK_ENET_TIMER1_ClockRoot_MuxAudioPllOut  = 5U, /*!< ENET_TIMER1 mux from MuxAudioPllOut. */
    kCLOCK_ENET_TIMER1_ClockRoot_MuxSysPll1Div5  = 6U, /*!< ENET_TIMER1 mux from MuxSysPll1Div5. */
    kCLOCK_ENET_TIMER1_ClockRoot_MuxSysPll2Pfd1  = 7U, /*!< ENET_TIMER1 mux from MuxSysPll2Pfd1. */

    /* ENET_TIMER2 */
    kCLOCK_ENET_TIMER2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ENET_TIMER2 mux from MuxOscRc48MDiv2. */
    kCLOCK_ENET_TIMER2_ClockRoot_MuxOsc24MOut    = 1U, /*!< ENET_TIMER2 mux from MuxOsc24MOut. */
    kCLOCK_ENET_TIMER2_ClockRoot_MuxOscRc400M    = 2U, /*!< ENET_TIMER2 mux from MuxOscRc400M. */
    kCLOCK_ENET_TIMER2_ClockRoot_MuxOscRc16M     = 3U, /*!< ENET_TIMER2 mux from MuxOscRc16M. */
    kCLOCK_ENET_TIMER2_ClockRoot_MuxSysPll1Div2  = 4U, /*!< ENET_TIMER2 mux from MuxSysPll1Div2. */
    kCLOCK_ENET_TIMER2_ClockRoot_MuxAudioPllOut  = 5U, /*!< ENET_TIMER2 mux from MuxAudioPllOut. */
    kCLOCK_ENET_TIMER2_ClockRoot_MuxSysPll1Div5  = 6U, /*!< ENET_TIMER2 mux from MuxSysPll1Div5. */
    kCLOCK_ENET_TIMER2_ClockRoot_MuxSysPll2Pfd1  = 7U, /*!< ENET_TIMER2 mux from MuxSysPll2Pfd1. */

    /* ENET_TIMER3 */
    kCLOCK_ENET_TIMER3_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ENET_TIMER3 mux from MuxOscRc48MDiv2. */
    kCLOCK_ENET_TIMER3_ClockRoot_MuxOsc24MOut    = 1U, /*!< ENET_TIMER3 mux from MuxOsc24MOut. */
    kCLOCK_ENET_TIMER3_ClockRoot_MuxOscRc400M    = 2U, /*!< ENET_TIMER3 mux from MuxOscRc400M. */
    kCLOCK_ENET_TIMER3_ClockRoot_MuxOscRc16M     = 3U, /*!< ENET_TIMER3 mux from MuxOscRc16M. */
    kCLOCK_ENET_TIMER3_ClockRoot_MuxSysPll1Div2  = 4U, /*!< ENET_TIMER3 mux from MuxSysPll1Div2. */
    kCLOCK_ENET_TIMER3_ClockRoot_MuxAudioPllOut  = 5U, /*!< ENET_TIMER3 mux from MuxAudioPllOut. */
    kCLOCK_ENET_TIMER3_ClockRoot_MuxSysPll1Div5  = 6U, /*!< ENET_TIMER3 mux from MuxSysPll1Div5. */
    kCLOCK_ENET_TIMER3_ClockRoot_MuxSysPll2Pfd1  = 7U, /*!< ENET_TIMER3 mux from MuxSysPll2Pfd1. */

    /* USDHC1 */
    kCLOCK_USDHC1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< USDHC1 mux from MuxOscRc48MDiv2. */
    kCLOCK_USDHC1_ClockRoot_MuxOsc24MOut    = 1U, /*!< USDHC1 mux from MuxOsc24MOut. */
    kCLOCK_USDHC1_ClockRoot_MuxOscRc400M    = 2U, /*!< USDHC1 mux from MuxOscRc400M. */
    kCLOCK_USDHC1_ClockRoot_MuxOscRc16M     = 3U, /*!< USDHC1 mux from MuxOscRc16M. */
    kCLOCK_USDHC1_ClockRoot_MuxSysPll2Pfd2  = 4U, /*!< USDHC1 mux from MuxSysPll2Pfd2. */
    kCLOCK_USDHC1_ClockRoot_MuxSysPll2Pfd0  = 5U, /*!< USDHC1 mux from MuxSysPll2Pfd0. */
    kCLOCK_USDHC1_ClockRoot_MuxSysPll1Div5  = 6U, /*!< USDHC1 mux from MuxSysPll1Div5. */
    kCLOCK_USDHC1_ClockRoot_MuxArmPllOut    = 7U, /*!< USDHC1 mux from MuxArmPllOut. */

    /* USDHC2 */
    kCLOCK_USDHC2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< USDHC2 mux from MuxOscRc48MDiv2. */
    kCLOCK_USDHC2_ClockRoot_MuxOsc24MOut    = 1U, /*!< USDHC2 mux from MuxOsc24MOut. */
    kCLOCK_USDHC2_ClockRoot_MuxOscRc400M    = 2U, /*!< USDHC2 mux from MuxOscRc400M. */
    kCLOCK_USDHC2_ClockRoot_MuxOscRc16M     = 3U, /*!< USDHC2 mux from MuxOscRc16M. */
    kCLOCK_USDHC2_ClockRoot_MuxSysPll2Pfd2  = 4U, /*!< USDHC2 mux from MuxSysPll2Pfd2. */
    kCLOCK_USDHC2_ClockRoot_MuxSysPll2Pfd0  = 5U, /*!< USDHC2 mux from MuxSysPll2Pfd0. */
    kCLOCK_USDHC2_ClockRoot_MuxSysPll1Div5  = 6U, /*!< USDHC2 mux from MuxSysPll1Div5. */
    kCLOCK_USDHC2_ClockRoot_MuxArmPllOut    = 7U, /*!< USDHC2 mux from MuxArmPllOut. */

    /* ASRC */
    kCLOCK_ASRC_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< ASRC mux from MuxOscRc48MDiv2. */
    kCLOCK_ASRC_ClockRoot_MuxOsc24MOut    = 1U, /*!< ASRC mux from MuxOsc24MOut. */
    kCLOCK_ASRC_ClockRoot_MuxOscRc400M    = 2U, /*!< ASRC mux from MuxOscRc400M. */
    kCLOCK_ASRC_ClockRoot_MuxOscRc16M     = 3U, /*!< ASRC mux from MuxOscRc16M. */
    kCLOCK_ASRC_ClockRoot_MuxSysPll1Div5  = 4U, /*!< ASRC mux from MuxSysPll1Div5. */
    kCLOCK_ASRC_ClockRoot_MuxSysPll3Div2  = 5U, /*!< ASRC mux from MuxSysPll3Div2. */
    kCLOCK_ASRC_ClockRoot_MuxAudioPllOut  = 6U, /*!< ASRC mux from MuxAudioPllOut. */
    kCLOCK_ASRC_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< ASRC mux from MuxSysPll2Pfd3. */

    /* MQS */
    kCLOCK_MQS_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< MQS mux from MuxOscRc48MDiv2. */
    kCLOCK_MQS_ClockRoot_MuxOsc24MOut    = 1U, /*!< MQS mux from MuxOsc24MOut. */
    kCLOCK_MQS_ClockRoot_MuxOscRc400M    = 2U, /*!< MQS mux from MuxOscRc400M. */
    kCLOCK_MQS_ClockRoot_MuxOscRc16M     = 3U, /*!< MQS mux from MuxOscRc16M. */
    kCLOCK_MQS_ClockRoot_MuxSysPll1Div5  = 4U, /*!< MQS mux from MuxSysPll1Div5. */
    kCLOCK_MQS_ClockRoot_MuxSysPll3Div2  = 5U, /*!< MQS mux from MuxSysPll3Div2. */
    kCLOCK_MQS_ClockRoot_MuxAudioPllOut  = 6U, /*!< MQS mux from MuxAudioPllOut. */
    kCLOCK_MQS_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< MQS mux from MuxSysPll2Pfd3. */

    /* MIC */
    kCLOCK_MIC_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< MIC mux from MuxOscRc48MDiv2. */
    kCLOCK_MIC_ClockRoot_MuxOsc24MOut    = 1U, /*!< MIC mux from MuxOsc24MOut. */
    kCLOCK_MIC_ClockRoot_MuxOscRc400M    = 2U, /*!< MIC mux from MuxOscRc400M. */
    kCLOCK_MIC_ClockRoot_MuxOscRc16M     = 3U, /*!< MIC mux from MuxOscRc16M. */
    kCLOCK_MIC_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< MIC mux from MuxSysPll3Pfd3. */
    kCLOCK_MIC_ClockRoot_MuxSysPll3Out   = 5U, /*!< MIC mux from MuxSysPll3Out. */
    kCLOCK_MIC_ClockRoot_MuxAudioPllOut  = 6U, /*!< MIC mux from MuxAudioPllOut. */
    kCLOCK_MIC_ClockRoot_MuxSysPll1Div5  = 7U, /*!< MIC mux from MuxSysPll1Div5. */

    /* SPDIF */
    kCLOCK_SPDIF_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< SPDIF mux from MuxOscRc48MDiv2. */
    kCLOCK_SPDIF_ClockRoot_MuxOsc24MOut    = 1U, /*!< SPDIF mux from MuxOsc24MOut. */
    kCLOCK_SPDIF_ClockRoot_MuxOscRc400M    = 2U, /*!< SPDIF mux from MuxOscRc400M. */
    kCLOCK_SPDIF_ClockRoot_MuxOscRc16M     = 3U, /*!< SPDIF mux from MuxOscRc16M. */
    kCLOCK_SPDIF_ClockRoot_MuxAudioPllOut  = 4U, /*!< SPDIF mux from MuxAudioPllOut. */
    kCLOCK_SPDIF_ClockRoot_MuxSysPll3Out   = 5U, /*!< SPDIF mux from MuxSysPll3Out. */
    kCLOCK_SPDIF_ClockRoot_MuxSysPll3Pfd2  = 6U, /*!< SPDIF mux from MuxSysPll3Pfd2. */
    kCLOCK_SPDIF_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< SPDIF mux from MuxSysPll2Pfd3. */

    /* SAI1 */
    kCLOCK_SAI1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< SAI1 mux from MuxOscRc48MDiv2. */
    kCLOCK_SAI1_ClockRoot_MuxOsc24MOut    = 1U, /*!< SAI1 mux from MuxOsc24MOut. */
    kCLOCK_SAI1_ClockRoot_MuxOscRc400M    = 2U, /*!< SAI1 mux from MuxOscRc400M. */
    kCLOCK_SAI1_ClockRoot_MuxOscRc16M     = 3U, /*!< SAI1 mux from MuxOscRc16M. */
    kCLOCK_SAI1_ClockRoot_MuxAudioPllOut  = 4U, /*!< SAI1 mux from MuxAudioPllOut. */
    kCLOCK_SAI1_ClockRoot_MuxSysPll3Pfd2  = 5U, /*!< SAI1 mux from MuxSysPll3Pfd2. */
    kCLOCK_SAI1_ClockRoot_MuxSysPll1Div5  = 6U, /*!< SAI1 mux from MuxSysPll1Div5. */
    kCLOCK_SAI1_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< SAI1 mux from MuxSysPll2Pfd3. */

    /* SAI2 */
    kCLOCK_SAI2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< SAI2 mux from MuxOscRc48MDiv2. */
    kCLOCK_SAI2_ClockRoot_MuxOsc24MOut    = 1U, /*!< SAI2 mux from MuxOsc24MOut. */
    kCLOCK_SAI2_ClockRoot_MuxOscRc400M    = 2U, /*!< SAI2 mux from MuxOscRc400M. */
    kCLOCK_SAI2_ClockRoot_MuxOscRc16M     = 3U, /*!< SAI2 mux from MuxOscRc16M. */
    kCLOCK_SAI2_ClockRoot_MuxAudioPllOut  = 4U, /*!< SAI2 mux from MuxAudioPllOut. */
    kCLOCK_SAI2_ClockRoot_MuxSysPll3Pfd2  = 5U, /*!< SAI2 mux from MuxSysPll3Pfd2. */
    kCLOCK_SAI2_ClockRoot_MuxSysPll1Div5  = 6U, /*!< SAI2 mux from MuxSysPll1Div5. */
    kCLOCK_SAI2_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< SAI2 mux from MuxSysPll2Pfd3. */

    /* SAI3 */
    kCLOCK_SAI3_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< SAI3 mux from MuxOscRc48MDiv2. */
    kCLOCK_SAI3_ClockRoot_MuxOsc24MOut    = 1U, /*!< SAI3 mux from MuxOsc24MOut. */
    kCLOCK_SAI3_ClockRoot_MuxOscRc400M    = 2U, /*!< SAI3 mux from MuxOscRc400M. */
    kCLOCK_SAI3_ClockRoot_MuxOscRc16M     = 3U, /*!< SAI3 mux from MuxOscRc16M. */
    kCLOCK_SAI3_ClockRoot_MuxAudioPllOut  = 4U, /*!< SAI3 mux from MuxAudioPllOut. */
    kCLOCK_SAI3_ClockRoot_MuxSysPll3Pfd2  = 5U, /*!< SAI3 mux from MuxSysPll3Pfd2. */
    kCLOCK_SAI3_ClockRoot_MuxSysPll1Div5  = 6U, /*!< SAI3 mux from MuxSysPll1Div5. */
    kCLOCK_SAI3_ClockRoot_MuxSysPll2Pfd3  = 7U, /*!< SAI3 mux from MuxSysPll2Pfd3. */

    /* SAI4 */
    kCLOCK_SAI4_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< SAI4 mux from MuxOscRc48MDiv2. */
    kCLOCK_SAI4_ClockRoot_MuxOsc24MOut    = 1U, /*!< SAI4 mux from MuxOsc24MOut. */
    kCLOCK_SAI4_ClockRoot_MuxOscRc400M    = 2U, /*!< SAI4 mux from MuxOscRc400M. */
    kCLOCK_SAI4_ClockRoot_MuxOscRc16M     = 3U, /*!< SAI4 mux from MuxOscRc16M. */
    kCLOCK_SAI4_ClockRoot_MuxSysPll3Pfd3  = 4U, /*!< SAI4 mux from MuxSysPll3Pfd3. */
    kCLOCK_SAI4_ClockRoot_MuxSysPll3Out   = 5U, /*!< SAI4 mux from MuxSysPll3Out. */
    kCLOCK_SAI4_ClockRoot_MuxAudioPllOut  = 6U, /*!< SAI4 mux from MuxAudioPllOut. */
    kCLOCK_SAI4_ClockRoot_MuxSysPll1Div5  = 7U, /*!< SAI4 mux from MuxSysPll1Div5. */

    /* GC355 */
    kCLOCK_GC355_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< GC355 mux from MuxOscRc48MDiv2. */
    kCLOCK_GC355_ClockRoot_MuxOsc24MOut    = 1U, /*!< GC355 mux from MuxOsc24MOut. */
    kCLOCK_GC355_ClockRoot_MuxOscRc400M    = 2U, /*!< GC355 mux from MuxOscRc400M. */
    kCLOCK_GC355_ClockRoot_MuxOscRc16M     = 3U, /*!< GC355 mux from MuxOscRc16M. */
    kCLOCK_GC355_ClockRoot_MuxSysPll2Out   = 4U, /*!< GC355 mux from MuxSysPll2Out. */
    kCLOCK_GC355_ClockRoot_MuxSysPll2Pfd1  = 5U, /*!< GC355 mux from MuxSysPll2Pfd1. */
    kCLOCK_GC355_ClockRoot_MuxSysPll3Out   = 6U, /*!< GC355 mux from MuxSysPll3Out. */
    kCLOCK_GC355_ClockRoot_MuxVideoPllOut  = 7U, /*!< GC355 mux from MuxVideoPllOut. */

    /* LCDIF */
    kCLOCK_LCDIF_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LCDIF mux from MuxOscRc48MDiv2. */
    kCLOCK_LCDIF_ClockRoot_MuxOsc24MOut    = 1U, /*!< LCDIF mux from MuxOsc24MOut. */
    kCLOCK_LCDIF_ClockRoot_MuxOscRc400M    = 2U, /*!< LCDIF mux from MuxOscRc400M. */
    kCLOCK_LCDIF_ClockRoot_MuxOscRc16M     = 3U, /*!< LCDIF mux from MuxOscRc16M. */
    kCLOCK_LCDIF_ClockRoot_MuxSysPll2Out   = 4U, /*!< LCDIF mux from MuxSysPll2Out. */
    kCLOCK_LCDIF_ClockRoot_MuxSysPll2Pfd2  = 5U, /*!< LCDIF mux from MuxSysPll2Pfd2. */
    kCLOCK_LCDIF_ClockRoot_MuxSysPll3Pfd0  = 6U, /*!< LCDIF mux from MuxSysPll3Pfd0. */
    kCLOCK_LCDIF_ClockRoot_MuxVideoPllOut  = 7U, /*!< LCDIF mux from MuxVideoPllOut. */

    /* LCDIFV2 */
    kCLOCK_LCDIFV2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< LCDIFV2 mux from MuxOscRc48MDiv2. */
    kCLOCK_LCDIFV2_ClockRoot_MuxOsc24MOut    = 1U, /*!< LCDIFV2 mux from MuxOsc24MOut. */
    kCLOCK_LCDIFV2_ClockRoot_MuxOscRc400M    = 2U, /*!< LCDIFV2 mux from MuxOscRc400M. */
    kCLOCK_LCDIFV2_ClockRoot_MuxOscRc16M     = 3U, /*!< LCDIFV2 mux from MuxOscRc16M. */
    kCLOCK_LCDIFV2_ClockRoot_MuxSysPll2Out   = 4U, /*!< LCDIFV2 mux from MuxSysPll2Out. */
    kCLOCK_LCDIFV2_ClockRoot_MuxSysPll2Pfd2  = 5U, /*!< LCDIFV2 mux from MuxSysPll2Pfd2. */
    kCLOCK_LCDIFV2_ClockRoot_MuxSysPll3Pfd0  = 6U, /*!< LCDIFV2 mux from MuxSysPll3Pfd0. */
    kCLOCK_LCDIFV2_ClockRoot_MuxVideoPllOut  = 7U, /*!< LCDIFV2 mux from MuxVideoPllOut. */

    /* MIPI_REF */
    kCLOCK_MIPI_REF_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< MIPI_REF mux from MuxOscRc48MDiv2. */
    kCLOCK_MIPI_REF_ClockRoot_MuxOsc24MOut    = 1U, /*!< MIPI_REF mux from MuxOsc24MOut. */
    kCLOCK_MIPI_REF_ClockRoot_MuxOscRc400M    = 2U, /*!< MIPI_REF mux from MuxOscRc400M. */
    kCLOCK_MIPI_REF_ClockRoot_MuxOscRc16M     = 3U, /*!< MIPI_REF mux from MuxOscRc16M. */
    kCLOCK_MIPI_REF_ClockRoot_MuxSysPll2Out   = 4U, /*!< MIPI_REF mux from MuxSysPll2Out. */
    kCLOCK_MIPI_REF_ClockRoot_MuxSysPll2Pfd0  = 5U, /*!< MIPI_REF mux from MuxSysPll2Pfd0. */
    kCLOCK_MIPI_REF_ClockRoot_MuxSysPll3Pfd0  = 6U, /*!< MIPI_REF mux from MuxSysPll3Pfd0. */
    kCLOCK_MIPI_REF_ClockRoot_MuxVideoPllOut  = 7U, /*!< MIPI_REF mux from MuxVideoPllOut. */

    /* MIPI_ESC */
    kCLOCK_MIPI_ESC_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< MIPI_ESC mux from MuxOscRc48MDiv2. */
    kCLOCK_MIPI_ESC_ClockRoot_MuxOsc24MOut    = 1U, /*!< MIPI_ESC mux from MuxOsc24MOut. */
    kCLOCK_MIPI_ESC_ClockRoot_MuxOscRc400M    = 2U, /*!< MIPI_ESC mux from MuxOscRc400M. */
    kCLOCK_MIPI_ESC_ClockRoot_MuxOscRc16M     = 3U, /*!< MIPI_ESC mux from MuxOscRc16M. */
    kCLOCK_MIPI_ESC_ClockRoot_MuxSysPll2Out   = 4U, /*!< MIPI_ESC mux from MuxSysPll2Out. */
    kCLOCK_MIPI_ESC_ClockRoot_MuxSysPll2Pfd0  = 5U, /*!< MIPI_ESC mux from MuxSysPll2Pfd0. */
    kCLOCK_MIPI_ESC_ClockRoot_MuxSysPll3Pfd0  = 6U, /*!< MIPI_ESC mux from MuxSysPll3Pfd0. */
    kCLOCK_MIPI_ESC_ClockRoot_MuxVideoPllOut  = 7U, /*!< MIPI_ESC mux from MuxVideoPllOut. */

    /* CSI2 */
    kCLOCK_CSI2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CSI2 mux from MuxOscRc48MDiv2. */
    kCLOCK_CSI2_ClockRoot_MuxOsc24MOut    = 1U, /*!< CSI2 mux from MuxOsc24MOut. */
    kCLOCK_CSI2_ClockRoot_MuxOscRc400M    = 2U, /*!< CSI2 mux from MuxOscRc400M. */
    kCLOCK_CSI2_ClockRoot_MuxOscRc16M     = 3U, /*!< CSI2 mux from MuxOscRc16M. */
    kCLOCK_CSI2_ClockRoot_MuxSysPll2Pfd2  = 4U, /*!< CSI2 mux from MuxSysPll2Pfd2. */
    kCLOCK_CSI2_ClockRoot_MuxSysPll3Out   = 5U, /*!< CSI2 mux from MuxSysPll3Out. */
    kCLOCK_CSI2_ClockRoot_MuxSysPll2Pfd0  = 6U, /*!< CSI2 mux from MuxSysPll2Pfd0. */
    kCLOCK_CSI2_ClockRoot_MuxVideoPllOut  = 7U, /*!< CSI2 mux from MuxVideoPllOut. */

    /* CSI2_ESC */
    kCLOCK_CSI2_ESC_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CSI2_ESC mux from MuxOscRc48MDiv2. */
    kCLOCK_CSI2_ESC_ClockRoot_MuxOsc24MOut    = 1U, /*!< CSI2_ESC mux from MuxOsc24MOut. */
    kCLOCK_CSI2_ESC_ClockRoot_MuxOscRc400M    = 2U, /*!< CSI2_ESC mux from MuxOscRc400M. */
    kCLOCK_CSI2_ESC_ClockRoot_MuxOscRc16M     = 3U, /*!< CSI2_ESC mux from MuxOscRc16M. */
    kCLOCK_CSI2_ESC_ClockRoot_MuxSysPll2Pfd2  = 4U, /*!< CSI2_ESC mux from MuxSysPll2Pfd2. */
    kCLOCK_CSI2_ESC_ClockRoot_MuxSysPll3Out   = 5U, /*!< CSI2_ESC mux from MuxSysPll3Out. */
    kCLOCK_CSI2_ESC_ClockRoot_MuxSysPll2Pfd0  = 6U, /*!< CSI2_ESC mux from MuxSysPll2Pfd0. */
    kCLOCK_CSI2_ESC_ClockRoot_MuxVideoPllOut  = 7U, /*!< CSI2_ESC mux from MuxVideoPllOut. */

    /* CSI2_UI */
    kCLOCK_CSI2_UI_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CSI2_UI mux from MuxOscRc48MDiv2. */
    kCLOCK_CSI2_UI_ClockRoot_MuxOsc24MOut    = 1U, /*!< CSI2_UI mux from MuxOsc24MOut. */
    kCLOCK_CSI2_UI_ClockRoot_MuxOscRc400M    = 2U, /*!< CSI2_UI mux from MuxOscRc400M. */
    kCLOCK_CSI2_UI_ClockRoot_MuxOscRc16M     = 3U, /*!< CSI2_UI mux from MuxOscRc16M. */
    kCLOCK_CSI2_UI_ClockRoot_MuxSysPll2Pfd2  = 4U, /*!< CSI2_UI mux from MuxSysPll2Pfd2. */
    kCLOCK_CSI2_UI_ClockRoot_MuxSysPll3Out   = 5U, /*!< CSI2_UI mux from MuxSysPll3Out. */
    kCLOCK_CSI2_UI_ClockRoot_MuxSysPll2Pfd0  = 6U, /*!< CSI2_UI mux from MuxSysPll2Pfd0. */
    kCLOCK_CSI2_UI_ClockRoot_MuxVideoPllOut  = 7U, /*!< CSI2_UI mux from MuxVideoPllOut. */

    /* CSI */
    kCLOCK_CSI_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CSI mux from MuxOscRc48MDiv2. */
    kCLOCK_CSI_ClockRoot_MuxOsc24MOut    = 1U, /*!< CSI mux from MuxOsc24MOut. */
    kCLOCK_CSI_ClockRoot_MuxOscRc400M    = 2U, /*!< CSI mux from MuxOscRc400M. */
    kCLOCK_CSI_ClockRoot_MuxOscRc16M     = 3U, /*!< CSI mux from MuxOscRc16M. */
    kCLOCK_CSI_ClockRoot_MuxSysPll2Pfd2  = 4U, /*!< CSI mux from MuxSysPll2Pfd2. */
    kCLOCK_CSI_ClockRoot_MuxSysPll3Out   = 5U, /*!< CSI mux from MuxSysPll3Out. */
    kCLOCK_CSI_ClockRoot_MuxSysPll3Pfd1  = 6U, /*!< CSI mux from MuxSysPll3Pfd1. */
    kCLOCK_CSI_ClockRoot_MuxVideoPllOut  = 7U, /*!< CSI mux from MuxVideoPllOut. */

    /* CKO1 */
    kCLOCK_CKO1_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CKO1 mux from MuxOscRc48MDiv2. */
    kCLOCK_CKO1_ClockRoot_MuxOsc24MOut    = 1U, /*!< CKO1 mux from MuxOsc24MOut. */
    kCLOCK_CKO1_ClockRoot_MuxOscRc400M    = 2U, /*!< CKO1 mux from MuxOscRc400M. */
    kCLOCK_CKO1_ClockRoot_MuxOscRc16M     = 3U, /*!< CKO1 mux from MuxOscRc16M. */
    kCLOCK_CKO1_ClockRoot_MuxSysPll2Pfd2  = 4U, /*!< CKO1 mux from MuxSysPll2Pfd2. */
    kCLOCK_CKO1_ClockRoot_MuxSysPll2Out   = 5U, /*!< CKO1 mux from MuxSysPll2Out. */
    kCLOCK_CKO1_ClockRoot_MuxSysPll3Pfd1  = 6U, /*!< CKO1 mux from MuxSysPll3Pfd1. */
    kCLOCK_CKO1_ClockRoot_MuxSysPll1Div5  = 7U, /*!< CKO1 mux from MuxSysPll1Div5. */

    /* CKO2 */
    kCLOCK_CKO2_ClockRoot_MuxOscRc48MDiv2 = 0U, /*!< CKO2 mux from MuxOscRc48MDiv2. */
    kCLOCK_CKO2_ClockRoot_MuxOsc24MOut    = 1U, /*!< CKO2 mux from MuxOsc24MOut. */
    kCLOCK_CKO2_ClockRoot_MuxOscRc400M    = 2U, /*!< CKO2 mux from MuxOscRc400M. */
    kCLOCK_CKO2_ClockRoot_MuxOscRc16M     = 3U, /*!< CKO2 mux from MuxOscRc16M. */
    kCLOCK_CKO2_ClockRoot_MuxSysPll2Pfd3  = 4U, /*!< CKO2 mux from MuxSysPll2Pfd3. */
    kCLOCK_CKO2_ClockRoot_MuxOscRc48M     = 5U, /*!< CKO2 mux from MuxOscRc48M. */
    kCLOCK_CKO2_ClockRoot_MuxSysPll3Pfd1  = 6U, /*!< CKO2 mux from MuxSysPll3Pfd1. */
    kCLOCK_CKO2_ClockRoot_MuxAudioPllOut  = 7U, /*!< CKO2 mux from MuxAudioPllOut. */
} clock_root_mux_source_t;

/*!
 * @brief Clock group enumeration.
 */
typedef enum _clock_group
{
    kCLOCK_Group_FlexRAM = 0, /*!< FlexRAM clock group. */
    kCLOCK_Group_MipiDsi = 1, /*!< Mipi Dsi clock group. */
    kCLOCK_Group_Last,        /*!< Last clock group. */
} clock_group_t;

/*!
 * @brief The structure used to configure clock group.
 */
typedef struct _clock_group_config
{
    bool clockOff;     /*!< Turn off the clock. */
    uint16_t resetDiv; /*!< resetDiv + 1 should be common multiple of all dividers, valid range 0 ~ 255. */
    uint8_t div0;      /*!< Divide root clock by div0 + 1, valid range: 0 ~ 15. */
} clock_group_config_t;

#define clock_ip_name_t clock_lpcg_t

#if (__CORTEX_M == 7)
#define CLOCK_GetCpuClkFreq CLOCK_GetM7Freq
#else
#define CLOCK_GetCpuClkFreq CLOCK_GetM4Freq
#endif

#define CLOCK_GetCoreSysClkFreq CLOCK_GetCpuClkFreq /*!< For compatible with other platforms without CCM. */

/* uncomment the following line if want to use OBS to retrieve frequency */
/* #define GET_FREQ_FROM_OBS */

/*! @brief OSC 24M sorce select */
typedef enum _clock_osc
{
    kCLOCK_RcOsc   = 0U, /*!< On chip OSC. */
    kCLOCK_XtalOsc = 1U, /*!< 24M Xtal OSC */
} clock_osc_t;

/*! @brief Clock gate value */
typedef enum _clock_gate_value
{
    kCLOCK_Off = (int)~CCM_LPCG_DIRECT_ON_MASK, /*!< Clock is off. */
    kCLOCK_On  = CCM_LPCG_DIRECT_ON_MASK,       /*!< Clock is on*/
} clock_gate_value_t;

/*! @brief System clock mode */
typedef enum _clock_mode_t
{
    kCLOCK_ModeRun  = 0U, /*!< Remain in run mode. */
    kCLOCK_ModeWait = 1U, /*!< Transfer to wait mode. */
    kCLOCK_ModeStop = 2U, /*!< Transfer to stop mode. */
} clock_mode_t;

/*! @brief USB clock source definition. */
typedef enum _clock_usb_src
{
    kCLOCK_Usb480M      = 0,                /*!< Use 480M.      */
    kCLOCK_UsbSrcUnused = (int)0xFFFFFFFFU, /*!< Used when the function does not
                                            care the clock source. */
} clock_usb_src_t;

/*! @brief Source of the USB HS PHY. */
typedef enum _clock_usb_phy_src
{
    kCLOCK_Usbphy480M = 0, /*!< Use 480M.      */
} clock_usb_phy_src_t;

/*! @brief PLL clock source, bypass cloco source also */
enum _clock_pll_clk_src
{
    kCLOCK_PllClkSrc24M = 0U, /*!< Pll clock source 24M */
    kCLOCK_PllSrcClkPN  = 1U, /*!< Pll clock source CLK1_P and CLK1_N */
};

/*!
 * @brief PLL post divider enumeration.
 */
typedef enum _clock_pll_post_div
{
    kCLOCK_PllPostDiv2 = 0U, /*!< Divide by 2. */
    kCLOCK_PllPostDiv4 = 1U, /*!< Divide by 4. */
    kCLOCK_PllPostDiv8 = 2U, /*!< Divide by 8. */
    kCLOCK_PllPostDiv1 = 3U, /*!< Divide by 1. */
} clock_pll_post_div_t;

/*!
 * @brief PLL configuration for ARM.
 *
 * The output clock frequency is:
 *
 *  Fout=Fin*loopDivider /(2 * postDivider).
 *
 * Fin is always 24MHz.
 */
typedef struct _clock_arm_pll_config
{
    clock_pll_post_div_t postDivider; /*!< Post divider. */
    uint32_t loopDivider;             /*!< PLL loop divider. Valid range: 104-208. */
} clock_arm_pll_config_t;

/*! @brief PLL configuration for USB */
typedef struct _clock_usb_pll_config
{
    uint8_t loopDivider; /*!< PLL loop divider.
                              0 - Fout=Fref*20;
                              1 - Fout=Fref*22 */
    uint8_t src;         /*!< Pll clock source, reference _clock_pll_clk_src */

} clock_usb_pll_config_t;

/*! @brief Spread specturm configure Pll */
typedef struct _clock_pll_ss_config
{
    uint16_t stop; /*!< Spread spectrum stop value to get frequency change. */
    uint16_t step; /*!< Spread spectrum step value to get frequency change step. */
} clock_pll_ss_config_t;

/*! @brief PLL configure for Sys Pll2 */
typedef struct _clock_sys_pll2_config
{
    uint32_t mfd;              /*!< Denominator of spread spectrum */
    clock_pll_ss_config_t *ss; /*!< Spread spectrum parameter,
                                 it can be NULL, if ssEnable is set to false */
    bool ssEnable;             /*!< Enable spread spectrum flag */
} clock_sys_pll2_config_t;

/*! @brief PLL configure for Sys Pll1 */
typedef struct _clock_sys_pll1_config
{
    bool pllDiv2En;            /*!< Enable Sys Pll1 divide-by-2 clock or not. */
    bool pllDiv5En;            /*!< Enable Sys Pll1 divide-by-5 clock or not. */
    clock_pll_ss_config_t *ss; /*!< Spread spectrum parameter,
                                 it can be NULL, if ssEnable is set to false */
    bool ssEnable;             /*!< Enable spread spectrum flag */
} clock_sys_pll1_config_t;

/*! @brief PLL configuration for AUDIO and VIDEO */
typedef struct _clock_audio_pll_config
{
    uint8_t loopDivider;       /*!< PLL loop divider. Valid range for DIV_SELECT divider value: 27~54. */
    uint8_t postDivider;       /*!< Divider after the PLL, 0x0=divided by 1, 0x1=divided by 2, 0x2=divided by 4,
                                    0x3=divided by 8, 0x4=divided by 16, 0x5=divided by 32.*/
    uint32_t numerator;        /*!< 30 bit numerator of fractional loop divider.*/
    uint32_t denominator;      /*!< 30 bit denominator of fractional loop divider */
    clock_pll_ss_config_t *ss; /*!< Spread spectrum parameter,
                                 it can be NULL, if ssEnable is set to false */
    bool ssEnable;             /*!< Enable spread spectrum flag */
} clock_av_pll_config_t, clock_audio_pll_config_t, clock_video_pll_config_t;

/*!
 * @brief PLL configuration fro AUDIO PLL, SYSTEM PLL1 and VIDEO PLL.
 */
typedef struct _clock_audio_pll_gpc_config
{
    uint8_t loopDivider;       /*!< PLL loop divider.  */
    uint32_t numerator;        /*!< 30 bit numerator of fractional loop divider.*/
    uint32_t denominator;      /*!< 30 bit denominator of fractional loop divider */
    clock_pll_ss_config_t *ss; /*!< Spread spectrum parameter,
                                 it can be NULL, if ssEnable is set to false */
    bool ssEnable;             /*!< Enable spread spectrum flag */
} clock_audio_pll_gpc_config_t, clock_video_pll_gpc_config_t, clock_sys_pll1_gpc_config_t;

/*! @brief PLL configuration for ENET */
typedef struct _clock_enet_pll_config
{
    bool enableClkOutput;    /*!< Power on and enable PLL clock output for ENET0 (ref_enetpll0). */
    bool enableClkOutput25M; /*!< Power on and enable PLL clock output for ENET2 (ref_enetpll2). */
    uint8_t loopDivider;     /*!< Controls the frequency of the ENET0 reference clock.
                                  b00 25MHz
                                  b01 50MHz
                                  b10 100MHz (not 50% duty cycle)
                                  b11 125MHz */
    uint8_t src;             /*!< Pll clock source, reference _clock_pll_clk_src */
    bool enableClkOutput1;   /*!< Power on and enable PLL clock output for ENET1 (ref_enetpll1). */
    uint8_t loopDivider1;    /*!< Controls the frequency of the ENET1 reference clock.
                                  b00 25MHz
                                  b01 50MHz
                                  b10 100MHz (not 50% duty cycle)
                                  b11 125MHz */
} clock_enet_pll_config_t;

/*! @brief Clock root configuration */
typedef struct _clock_root_config_t
{
    bool clockOff;
    uint8_t mux; /*!< See #clock_root_mux_source_t for details. */
    uint8_t div; /*!< it's the actual divider */
} clock_root_config_t;

/*! @brief Clock root configuration in SetPoint Mode */
typedef struct _clock_root_setpoint_config_t
{
    uint8_t grade; /*!< Indicate speed grade for each SetPoint */
    bool clockOff;
    uint8_t mux; /*!< See #clock_root_mux_source_t for details. */
    uint8_t div; /*!< it's the actual divider */
} clock_root_setpoint_config_t;

/*! @brief PLL name */
typedef enum _clock_pll
{
    kCLOCK_PllArm,          /*!< ARM PLL. */
    kCLOCK_PllSys1,         /*!< SYS1 PLL, it has a dedicated frequency of 1GHz. */
    kCLOCK_PllSys2,         /*!< SYS2 PLL, it has a dedicated frequency of 528MHz. */
    kCLOCK_PllSys3,         /*!< SYS3 PLL, it has a dedicated frequency of 480MHz. */
    kCLOCK_PllAudio,        /*!< Audio PLL. */
    kCLOCK_PllVideo,        /*!< Video PLL. */
    kCLOCK_PllInvalid = -1, /*!< Invalid value. */
} clock_pll_t;

#define PLL_PFD_COUNT 4

/*! @brief PLL PFD name */
typedef enum _clock_pfd
{
    kCLOCK_Pfd0 = 0U, /*!< PLL PFD0 */
    kCLOCK_Pfd1 = 1U, /*!< PLL PFD1 */
    kCLOCK_Pfd2 = 2U, /*!< PLL PFD2 */
    kCLOCK_Pfd3 = 3U, /*!< PLL PFD3 */
} clock_pfd_t;

/*!
 * @brief The enumeration of control mode.
 *
 */
typedef enum _clock_control_mode
{
    kCLOCK_SoftwareMode = 0U, /*!< Software control mode. */
    kCLOCK_GpcMode,           /*!< GPC control mode. */
} clock_control_mode_t;

/*!
 * @brief The enumeration of 24MHz crystal oscillator mode.
 */
typedef enum _clock_24MOsc_mode
{
    kCLOCK_24MOscHighGainMode = 0U, /*!< 24MHz crystal oscillator work as high gain mode. */
    kCLOCK_24MOscBypassMode   = 1U, /*!< 24MHz crystal oscillator work as bypass mode. */
    kCLOCK_24MOscLowPowerMode = 2U, /*!< 24MHz crystal oscillator work as low power mode. */
} clock_24MOsc_mode_t;

/*!
 * @brief The enumeration of 16MHz RC oscillator clock source.
 */
typedef enum _clock_16MOsc_source
{
    kCLOCK_16MOscSourceFrom16MOsc = 0U, /*!< Source from 16MHz RC oscialltor. */
    kCLOCK_16MOscSourceFrom24MOsc = 1U, /*!< Source from 24MHz crystal oscillator. */
} clock_16MOsc_source_t;

/*!
 * @brief The enumeration of 1MHz output clock behavior, including disabling 1MHz output,
 * enabling locked 1MHz clock output, and enabling free-running 1MHz clock output.
 */
typedef enum _clock_1MHzOut_behavior
{
    kCLOCK_1MHzOutDisable               = 0U, /*!< Disable 1MHz output clock. */
    kCLOCK_1MHzOutEnableLocked1Mhz      = 1U, /*!< Enable 1MHz output clock, and select locked 1MHz to output. */
    kCLOCK_1MHzOutEnableFreeRunning1Mhz = 2U, /*!< Enable 1MHZ output clock,
                                                   and select free-running 1MHz to output. */
} clock_1MHzOut_behavior_t;

/*!
 * @brief The clock dependence level.
 */
typedef enum _clock_level
{
    kCLOCK_Level0 = 0x0UL, /*!< Not needed in any mode. */
    kCLOCK_Level1 = 0x1UL, /*!< Needed in RUN mode. */
    kCLOCK_Level2 = 0x2UL, /*!< Needed in RUN and WAIT mode. */
    kCLOCK_Level3 = 0x3UL, /*!< Needed in RUN, WAIT and STOP mode. */
    kCLOCK_Level4 = 0x4UL, /*!< Always on in any mode. */
} clock_level_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Set CCM Root Clock MUX node to certain value.
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param src Clock mux value to set, different mux has different value range. See \ref clock_root_mux_source_t.
 */
static inline void CLOCK_SetRootClockMux(clock_root_t root, uint8_t src)
{
    assert(src < 8U);
    CCM->CLOCK_ROOT[root].CONTROL =
        (CCM->CLOCK_ROOT[root].CONTROL & ~(CCM_CLOCK_ROOT_CONTROL_MUX_MASK)) | CCM_CLOCK_ROOT_CONTROL_MUX(src);
    __DSB();
    __ISB();
#if __CORTEX_M == 4
    (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
}

/*!
 * @brief Get CCM Root Clock MUX value.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @return Clock mux value.
 */
static inline uint32_t CLOCK_GetRootClockMux(clock_root_t root)
{
    return (CCM->CLOCK_ROOT[root].CONTROL & CCM_CLOCK_ROOT_CONTROL_MUX_MASK) >> CCM_CLOCK_ROOT_CONTROL_MUX_SHIFT;
}

/*!
 * @brief Get CCM Root Clock Source.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @param src Clock mux value to get, see \ref clock_root_mux_source_t.
 * @return Clock source
 */
static inline clock_name_t CLOCK_GetRootClockSource(clock_root_t root, uint32_t src)
{
    return s_clockSourceName[root][src];
}

/*!
 * @brief Set CCM Root Clock DIV certain value.
 *
 * @param root Which root clock to set, see \ref clock_root_t.
 * @param div Clock div value to set, different divider has different value range.
 */
static inline void CLOCK_SetRootClockDiv(clock_root_t root, uint8_t div)
{
    assert(div);
    CCM->CLOCK_ROOT[root].CONTROL = (CCM->CLOCK_ROOT[root].CONTROL & ~CCM_CLOCK_ROOT_CONTROL_DIV_MASK) |
                                    CCM_CLOCK_ROOT_CONTROL_DIV((uint32_t)div - 1UL);
    __DSB();
    __ISB();
#if __CORTEX_M == 4
    (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
}

/*!
 * @brief Get CCM DIV node value.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @return divider set for this root
 */
static inline uint32_t CLOCK_GetRootClockDiv(clock_root_t root)
{
    return ((CCM->CLOCK_ROOT[root].CONTROL & CCM_CLOCK_ROOT_CONTROL_DIV_MASK) >> CCM_CLOCK_ROOT_CONTROL_DIV_SHIFT) +
           1UL;
}

/*!
 * @brief Power Off Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
static inline void CLOCK_PowerOffRootClock(clock_root_t root)
{
    if (0UL == (CCM->CLOCK_ROOT[root].CONTROL & CCM_CLOCK_ROOT_CONTROL_OFF_MASK))
    {
        CCM->CLOCK_ROOT[root].CONTROL_SET = CCM_CLOCK_ROOT_CONTROL_OFF_MASK;
        __DSB();
        __ISB();
#if __CORTEX_M == 4
        (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
    }
}

/*!
 * @brief Power On Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
static inline void CLOCK_PowerOnRootClock(clock_root_t root)
{
    CCM->CLOCK_ROOT[root].CONTROL_CLR = CCM_CLOCK_ROOT_CONTROL_OFF_MASK;
    __DSB();
    __ISB();
#if __CORTEX_M == 4
    (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
}

/*!
 * @brief Configure Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param config root clock config, see \ref clock_root_config_t
 */
static inline void CLOCK_SetRootClock(clock_root_t root, const clock_root_config_t *config)
{
    assert(config);
    CCM->CLOCK_ROOT[root].CONTROL = CCM_CLOCK_ROOT_CONTROL_MUX(config->mux) |
                                    CCM_CLOCK_ROOT_CONTROL_DIV((uint32_t)config->div - 1UL) |
                                    (config->clockOff ? CCM_CLOCK_ROOT_CONTROL_OFF(config->clockOff) : 0UL);
    __DSB();
    __ISB();
#if __CORTEX_M == 4
    (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
}

/*!
 * @brief Control the clock gate for specific IP.
 *
 * @note This API will not have any effect when this clock is in CPULPM or SetPoint Mode
 *
 * @param name  Which clock to enable, see \ref clock_lpcg_t.
 * @param value Clock gate value to set, see \ref clock_gate_value_t.
 */
static inline void CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value)
{
    if (((uint32_t)value & CCM_LPCG_DIRECT_ON_MASK) != (CCM->LPCG[name].DIRECT & CCM_LPCG_DIRECT_ON_MASK))
    {
        CCM->LPCG[name].DIRECT = ((uint32_t)value & CCM_LPCG_DIRECT_ON_MASK);
        __DSB();
        __ISB();

        while ((CCM->LPCG[name].STATUS0 & CCM_LPCG_STATUS0_ON_MASK) != ((uint32_t)value & CCM_LPCG_STATUS0_ON_MASK))
        {
        }
    }
}

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_lpcg_t.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_On);
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_lpcg_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_Off);
}

/*!
 * @brief Set the clock group configuration.
 *
 * @param group  Which group to configure, see \ref clock_group_t.
 * @param config Configuration to set.
 */
void CLOCK_SetGroupConfig(clock_group_t group, const clock_group_config_t *config);

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 *
 * @param name Clock names defined in clock_name_t
 * @return Clock frequency value in hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t name);

/*!
 * @brief Gets the clock frequency for a specific root clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_root_t.
 *
 * @param root Clock names defined in clock_root_t
 * @return Clock frequency value in hertz
 */
static inline uint32_t CLOCK_GetRootClockFreq(clock_root_t root)
{
    uint32_t freq, mux;
    mux  = CLOCK_GetRootClockMux(root);
    freq = CLOCK_GetFreq(s_clockSourceName[root][mux]) / (CLOCK_GetRootClockDiv(root));
    assert(freq);
    return freq;
}

/*!
 * @brief Get the CCM CPU/core/system frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static inline uint32_t CLOCK_GetM7Freq(void)
{
    return CLOCK_GetRootClockFreq(kCLOCK_Root_M7);
}

/*!
 * @brief Get the CCM CPU/core/system frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static inline uint32_t CLOCK_GetM4Freq(void)
{
    return CLOCK_GetRootClockFreq(kCLOCK_Root_M4);
}

/*!
 * @brief Check if PLL is bypassed
 *
 * @param pll PLL control name (see @ref clock_pll_t enumeration)
 * @return PLL bypass status.
 *         - true: The PLL is bypassed.
 *         - false: The PLL is not bypassed.
 */
static inline bool CLOCK_IsPllBypassed(clock_pll_t pll)
{
    if (pll == kCLOCK_PllArm)
    {
        return (bool)((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_BYPASS_MASK) >>
                      ANADIG_PLL_ARM_PLL_CTRL_BYPASS_SHIFT);
    }
    else if (pll == kCLOCK_PllSys2)
    {
        return (bool)((ANADIG_PLL->SYS_PLL2_CTRL & ANADIG_PLL_SYS_PLL2_CTRL_BYPASS_MASK) >>
                      ANADIG_PLL_SYS_PLL2_CTRL_BYPASS_SHIFT);
    }
    else if (pll == kCLOCK_PllSys3)
    {
        return (bool)((ANADIG_PLL->SYS_PLL3_CTRL & ANADIG_PLL_SYS_PLL3_CTRL_BYPASS_MASK) >>
                      ANADIG_PLL_SYS_PLL3_CTRL_BYPASS_SHIFT);
    }
    else
    {
        return false;
    }
}

/*!
 * @brief Check if PLL is enabled
 *
 * @param pll PLL control name (see @ref clock_pll_t enumeration)
 * @return PLL bypass status.
 *         - true: The PLL is enabled.
 *         - false: The PLL is not enabled.
 */
static inline bool CLOCK_IsPllEnabled(clock_pll_t pll)
{
    if (pll == kCLOCK_PllArm)
    {
        return (bool)((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllSys2)
    {
        return (bool)((ANADIG_PLL->SYS_PLL2_CTRL & ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllSys3)
    {
        return (bool)((ANADIG_PLL->SYS_PLL3_CTRL & ANADIG_PLL_SYS_PLL3_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_SYS_PLL3_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllSys1)
    {
        return (bool)((ANADIG_PLL->SYS_PLL1_CTRL & ANADIG_PLL_SYS_PLL1_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_SYS_PLL1_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllAudio)
    {
        return (bool)((ANADIG_PLL->PLL_AUDIO_CTRL & ANADIG_PLL_PLL_AUDIO_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_PLL_AUDIO_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllVideo)
    {
        return (bool)((ANADIG_PLL->PLL_VIDEO_CTRL & ANADIG_PLL_PLL_VIDEO_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_PLL_VIDEO_CTRL_ENABLE_CLK_SHIFT);
    }
    else
    {
        return false;
    }
}

/*!
 * @name OSC operations
 * @{
 */

/*!
 * @brief Gets the RTC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static inline uint32_t CLOCK_GetRtcFreq(void)
{
    return 32768U;
}

/*!
 * @brief Set the control mode of 48MHz RC oscillator.
 *
 * @param controlMode The control mode to be set, please refer to @ref clock_control_mode_t.
 */
static inline void CLOCK_OSC_SetOsc48MControlMode(clock_control_mode_t controlMode)
{
    ANADIG_OSC->OSC_48M_CTRL = (ANADIG_OSC->OSC_48M_CTRL & ~(ANADIG_OSC_OSC_48M_CTRL_RC_48M_CONTROL_MODE_MASK)) |
                               ANADIG_OSC_OSC_48M_CTRL_RC_48M_CONTROL_MODE(controlMode);
}

/*!
 * @brief Enable/disable 48MHz RC oscillator.
 *
 * @param enable Used to enable or disable the 48MHz RC oscillator.
 *          - \b true Enable the 48MHz RC oscillator.
 *          - \b false Dissable the 48MHz RC oscillator.
 */
static inline void CLOCK_OSC_EnableOsc48M(bool enable)
{
    if (enable)
    {
        ANADIG_OSC->OSC_48M_CTRL |= ANADIG_OSC_OSC_48M_CTRL_TEN_MASK;
    }
    else
    {
        ANADIG_OSC->OSC_48M_CTRL &= ~ANADIG_OSC_OSC_48M_CTRL_TEN_MASK;
    }
}

/*!
 * @brief Set the control mode of the 24MHz clock sourced from 48MHz RC oscillator.
 *
 * @param controlMode The control mode to be set, please refer to @ref clock_control_mode_t.
 */
static inline void CLOCK_OSC_SetOsc48MDiv2ControlMode(clock_control_mode_t controlMode)
{
    ANADIG_OSC->OSC_48M_CTRL = (ANADIG_OSC->OSC_48M_CTRL & ~(ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_CONTROL_MODE_MASK)) |
                               ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_CONTROL_MODE(controlMode);
}

/*!
 * @brief Enable/disable the 24MHz clock sourced from 48MHz RC oscillator.
 *
 * @note The 48MHz RC oscillator must be enabled before enabling this 24MHz clock.
 *
 * @param enable Used to enable/disable the 24MHz clock sourced from 48MHz RC oscillator.
 *          - \b true Enable the 24MHz clock sourced from 48MHz.
 *          - \b false Disable the 24MHz clock sourced from 48MHz.
 */
static inline void CLOCK_OSC_EnableOsc48MDiv2(bool enable)
{
    if (enable)
    {
        ANADIG_OSC->OSC_48M_CTRL |= ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_EN_MASK;
    }
    else
    {
        ANADIG_OSC->OSC_48M_CTRL &= ~ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_EN_MASK;
    }
}

/*!
 * @brief Set the control mode of 24MHz crystal oscillator.
 *
 * @param controlMode The control mode to be set, please refer to @ref clock_control_mode_t.
 */
static inline void CLOCK_OSC_SetOsc24MControlMode(clock_control_mode_t controlMode)
{
    ANADIG_OSC->OSC_24M_CTRL = (ANADIG_OSC->OSC_24M_CTRL & ~(ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE_MASK)) |
                               ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE(controlMode);
}

/*! @brief Enable OSC 24Mhz
 *
 * This function enables OSC 24Mhz.
 */
void CLOCK_OSC_EnableOsc24M(void);

/*!
 * @brief Gate/ungate the 24MHz crystal oscillator output.
 *
 * @note Gating the 24MHz crystal oscillator can save power.
 *
 * @param enableGate Used to gate/ungate the 24MHz crystal oscillator.
 *          - \b true Gate the 24MHz crystal oscillator to save power.
 *          - \b false Ungate the 24MHz crystal oscillator.
 */
static inline void CLOCK_OSC_GateOsc24M(bool enableGate)
{
    if (enableGate)
    {
        ANADIG_OSC->OSC_24M_CTRL |= ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE_MASK;
    }
    else
    {
        ANADIG_OSC->OSC_24M_CTRL &= ~ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE_MASK;
    }
}

/*!
 * @brief Set the work mode of 24MHz crystal oscillator, the available modes are high gian mode, low power mode, and
 * bypass mode.
 *
 * @param workMode The work mode of 24MHz crystal oscillator, please refer to @ref clock_24MOsc_mode_t for details.
 */
void CLOCK_OSC_SetOsc24MWorkMode(clock_24MOsc_mode_t workMode);

/*!
 * @brief Set the control mode of 400MHz RC oscillator.
 *
 * @param controlMode The control mode to be set, please refer to @ref clock_control_mode_t.
 */
static inline void CLOCK_OSC_SetOscRc400MControlMode(clock_control_mode_t controlMode)
{
    ANADIG_OSC->OSC_400M_CTRL1 = (ANADIG_OSC->OSC_400M_CTRL1 & (~ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE_MASK)) |
                                 ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE(controlMode);
}

/*! @brief Enable OSC RC 400Mhz
 *
 * This function enables OSC RC 400Mhz.
 */
void CLOCK_OSC_EnableOscRc400M(void);

/*!
 * @brief Gate/ungate 400MHz RC oscillator.
 *
 * @param enableGate Used to gate/ungate 400MHz RC oscillator.
 *          - \b true Gate the 400MHz RC oscillator.
 *          - \b false Ungate the 400MHz RC oscillator.
 */
static inline void CLOCK_OSC_GateOscRc400M(bool enableGate)
{
    if (enableGate)
    {
        ANADIG_OSC->OSC_400M_CTRL1 |= ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG_MASK;
    }
    else
    {
        ANADIG_OSC->OSC_400M_CTRL1 &= ~ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG_MASK;
    }
}

/*!
 * @brief Trims OSC RC 400MHz.
 *
 * @param enable Used to enable trim function.
 * @param bypass Bypass the trim function.
 * @param trim Trim value.
 */
void CLOCK_OSC_TrimOscRc400M(bool enable, bool bypass, uint16_t trim);

/*!
 * @brief Set the divide value for ref_clk to generate slow clock.
 *
 * @note slow_clk = ref_clk / (divValue + 1), and the recommand divide value is 24.
 *
 * @param divValue The divide value to be set, the available range is 0~63.
 */
void CLOCK_OSC_SetOscRc400MRefClkDiv(uint8_t divValue);

/*!
 * @brief Set the target count for the fast clock.
 *
 * @param targetCount The desired target for the fast clock, should be the number of clock cycles of the fast_clk per
 * divided ref_clk.
 */
void CLOCK_OSC_SetOscRc400MFastClkCount(uint16_t targetCount);

/*!
 * @brief Set the negative and positive hysteresis value for the tuned clock.
 *
 * @note The hysteresis value should be set after the clock is tuned.
 *
 * @param negHysteresis The negative hysteresis value for the turned clock, this value in number of clock cycles of the
 * fast clock
 * @param posHysteresis The positive hysteresis value for the turned clock, this value in number of clock cycles of the
 * fast clock
 */
void CLOCK_OSC_SetOscRc400MHysteresisValue(uint8_t negHysteresis, uint8_t posHysteresis);

/*!
 * @brief Bypass/un-bypass the tune logic
 *
 * @param enableBypass Used to control whether to bypass the turn logic.
 *        - \b true Bypass the tune logic and use the programmed oscillator frequency to run the oscillator.
 *                  Function CLOCK_OSC_SetOscRc400MTuneValue() can be used to set oscillator frequency.
 *        - \b false Use the output of tune logic to run the oscillator.
 */
void CLOCK_OSC_BypassOscRc400MTuneLogic(bool enableBypass);

/*!
 * @brief Start/Stop the tune logic.
 *
 * @param enable Used to start or stop the tune logic.
 *          - \b true Start tuning
 *          - \b false Stop tuning and reset the tuning logic.
 */
void CLOCK_OSC_EnableOscRc400MTuneLogic(bool enable);

/*!
 * @brief Freeze/Unfreeze the tuning value.
 *
 * @param enableFreeze Used to control whether to freeze the tune value.
 *          - \b true Freeze the tune at the current tuned value and the oscillator runs at tje frozen tune value.
 *          - \b false Unfreezes and continues the tune operation.
 */
void CLOCK_OSC_FreezeOscRc400MTuneValue(bool enableFreeze);

/*!
 * @brief Set the 400MHz RC oscillator tune value when the tune logic is disabled.
 *
 * @param tuneValue The tune value to determine the frequency of Oscillator.
 */
void CLOCK_OSC_SetOscRc400MTuneValue(uint8_t tuneValue);

/*!
 * @brief Set the behavior of the 1MHz output clock, such as disable the 1MHz clock output,
 * enable the free-running 1MHz clock output, enable the locked 1MHz clock output.
 *
 * @note The 1MHz clock is divided from 400M RC Oscillator.
 *
 * @param behavior The behavior of 1MHz output clock, please refer to @ref clock_1MHzOut_behavior_t for details.
 */
void CLOCK_OSC_Set1MHzOutputBehavior(clock_1MHzOut_behavior_t behavior);

/*!
 * @brief Set the count for the locked 1MHz clock out.
 *
 * @param count Used to set the desired target for the locked 1MHz clock out, the value in number of clock cycles of the
 * fast clock per divided ref_clk.
 */
void CLOCK_OSC_SetLocked1MHzCount(uint16_t count);

/*!
 * @brief Check the error flag for locked 1MHz clock out.
 *
 * @return The error flag for locked 1MHz clock out.
 *      - \b true The count value has been reached within one diviced ref clock period
 *      - \b false No effect.
 */
bool CLOCK_OSC_CheckLocked1MHzErrorFlag(void);

/*!
 * @brief Clear the error flag for locked 1MHz clock out.
 */
void CLOCK_OSC_ClearLocked1MHzErrorFlag(void);

/*!
 * @brief Get current count for the fast clock during the tune process.
 *
 * @return The current count for the fast clock.
 */
uint16_t CLOCK_OSC_GetCurrentOscRc400MFastClockCount(void);

/*!
 * @brief Get current tune value used by oscillator during tune process.
 *
 * @return The current tune value.
 */
uint8_t CLOCK_OSC_GetCurrentOscRc400MTuneValue(void);

/*!
 * @brief Set the control mode of 16MHz crystal oscillator.
 *
 * @param controlMode The control mode to be set, please refer to @ref clock_control_mode_t.
 */
static inline void CLOCK_OSC_SetOsc16MControlMode(clock_control_mode_t controlMode)
{
    ANADIG_OSC->OSC_16M_CTRL = (ANADIG_OSC->OSC_16M_CTRL & (~ANADIG_OSC_OSC_16M_CTRL_RC_16M_CONTROL_MODE_MASK)) |
                               ANADIG_OSC_OSC_16M_CTRL_RC_16M_CONTROL_MODE(controlMode);
}

/*!
 * @brief Configure the 16MHz oscillator.
 *
 * @param source Used to select the source for 16MHz RC oscillator, please refer to @ref clock_16MOsc_source_t.
 * @param enablePowerSave Enable/disable power save mode function at 16MHz OSC.
 *          - \b true Enable power save mode function at 16MHz osc.
 *          - \b false Disable power save mode function at 16MHz osc.
 * @param enableClockOut Enable/Disable clock output for 16MHz RCOSC.
 *          - \b true Enable clock output for 16MHz RCOSC.
 *          - \b false Disable clock output for 16MHz RCOSC.
 */
void CLOCK_OSC_SetOsc16MConfig(clock_16MOsc_source_t source, bool enablePowerSave, bool enableClockOut);

/* @} */

/*!
 * @brief Initialize the ARM PLL.
 *
 * This function initialize the ARM PLL with specific settings
 *
 * @param config   configuration to set to PLL.
 */
void CLOCK_InitArmPll(const clock_arm_pll_config_t *config);

/*!
 * @brief Calculate corresponding config values per given frequency
 *
 * This function calculates config valudes per given frequency for Arm PLL
 *
 * @param config pll config structure
 * @param freqInMhz target frequency
 */
status_t CLOCK_CalcArmPllFreq(clock_arm_pll_config_t *config, uint32_t freqInMhz);

/*!
 * @brief Initializes the Arm PLL with Specific Frequency (in Mhz).
 *
 * This function initializes the Arm PLL with specific frequency
 *
 * @param freqInMhz target frequency
 */
status_t CLOCK_InitArmPllWithFreq(uint32_t freqInMhz);

/*!
 * @brief De-initialize the ARM PLL.
 */
void CLOCK_DeinitArmPll(void);

/*!
 * @brief Calculate spread spectrum step and stop.
 *
 * This function calculate spread spectrum step and stop according to given
 * parameters. For integer PLL (syspll2) the factor is mfd, while for other
 * fractional PLLs (audio/video/syspll1), the factor is denominator.
 *
 * @param factor factor to calculate step/stop
 * @param range spread spectrum range
 * @param mod spread spectrum modulation frequency
 * @param ss calculated spread spectrum values
 *
 */
void CLOCK_CalcPllSpreadSpectrum(uint32_t factor, uint32_t range, uint32_t mod, clock_pll_ss_config_t *ss);

/*!
 * @brief Initialize the System PLL1.
 *
 * This function initializes the System PLL1 with specific settings
 *
 * @param config Configuration to set to PLL1.
 */
void CLOCK_InitSysPll1(const clock_sys_pll1_config_t *config);

/*!
 * @brief De-initialize the System PLL1.
 */
void CLOCK_DeinitSysPll1(void);

/*!
 * @brief Set System PLL1 output frequency in GPC mode.
 *
 * @param config Pointer to @ref clock_sys_pll1_gpc_config_t.
 */
void CLOCK_GPC_SetSysPll1OutputFreq(const clock_sys_pll1_gpc_config_t *config);

/*!
 * @brief Initialize the System PLL2.
 *
 * This function initializes the System PLL2 with specific settings
 *
 * @param config Configuration to configure spread spectrum. This parameter can
 *            be NULL, if no need to enabled spread spectrum
 */
void CLOCK_InitSysPll2(const clock_sys_pll2_config_t *config);

/*!
 * @brief De-initialize the System PLL2.
 */
void CLOCK_DeinitSysPll2(void);

/*!
 * @brief Check if Sys PLL2 PFD is enabled
 *
 * @param pfd PFD control name
 * @return PFD bypass status.
 *         - true: power on.
 *         - false: power off.
 * @note Only useful in software control mode.
 */
bool CLOCK_IsSysPll2PfdEnabled(clock_pfd_t pfd);

/*!
 * @brief Initialize the System PLL3.
 *
 * This function initializes the System PLL3 with specific settings
 *
 */
void CLOCK_InitSysPll3(void);

/*!
 * @brief De-initialize the System PLL3.
 */
void CLOCK_DeinitSysPll3(void);

/*!
 * @brief Check if Sys PLL3 PFD is enabled
 *
 * @param pfd PFD control name
 * @return PFD bypass status.
 *         - true: power on.
 *         - false: power off.
 * @note Only useful in software control mode.
 */
bool CLOCK_IsSysPll3PfdEnabled(clock_pfd_t pfd);

/*!
 * @name PLL/PFD operations
 * @{
 */
/*!
 * @brief PLL bypass setting
 *
 * @param pll PLL control name (see @ref clock_pll_t enumeration)
 * @param bypass Bypass the PLL.
 *               - true: Bypass the PLL.
 *               - false:Not bypass the PLL.
 */
void CLOCK_SetPllBypass(clock_pll_t pll, bool bypass);

/*!
 * @brief Calculate corresponding config values per given frequency
 *
 * This function calculates config valudes per given frequency for Audio/Video
 * PLL.
 *
 * @param config pll config structure
 * @param freqInMhz target frequency
 */
status_t CLOCK_CalcAvPllFreq(clock_av_pll_config_t *config, uint32_t freqInMhz);

/*!
 * @brief Initializes the Audio PLL with Specific Frequency (in Mhz).
 *
 * This function initializes the Audio PLL with specific frequency
 *
 * @param freqInMhz target frequency
 * @param ssEnable  enable spread spectrum or not
 * @param ssRange   range spread spectrum range
 * @param ssMod spread spectrum modulation frequency
 */
status_t CLOCK_InitAudioPllWithFreq(uint32_t freqInMhz, bool ssEnable, uint32_t ssRange, uint32_t ssMod);

/*!
 * @brief Initializes the Audio PLL.
 *
 * This function initializes the Audio PLL with specific settings
 *
 * @param config Configuration to set to PLL.
 */
void CLOCK_InitAudioPll(const clock_audio_pll_config_t *config);

/*!
 * @brief De-initialize the Audio PLL.
 */
void CLOCK_DeinitAudioPll(void);

/*!
 * @brief Set Audio PLL output frequency in GPC mode.
 *
 * @param config Pointer to clock_audio_pll_gpc_config_t structure.
 */
void CLOCK_GPC_SetAudioPllOutputFreq(const clock_audio_pll_gpc_config_t *config);

/*!
 * @brief Initializes the Video PLL with Specific Frequency (in Mhz).
 *
 * This function initializes the Video PLL with specific frequency
 *
 * @param freqInMhz target frequency
 * @param ssEnable  enable spread spectrum or not
 * @param ssRange   range spread spectrum range
 * @param ssMod spread spectrum modulation frequency
 */
status_t CLOCK_InitVideoPllWithFreq(uint32_t freqInMhz, bool ssEnable, uint32_t ssRange, uint32_t ssMod);

/*!
 * @brief Initialize the video PLL.
 *
 * This function configures the Video PLL with specific settings
 *
 * @param config   configuration to set to PLL.
 */
void CLOCK_InitVideoPll(const clock_video_pll_config_t *config);

/*!
 * @brief De-initialize the Video PLL.
 */
void CLOCK_DeinitVideoPll(void);

/*!
 * @brief Set Video PLL output frequency in GPC mode.
 *
 * @param config Pointer to clock_audio_pll_gpc_config_t structure.
 */
void CLOCK_GPC_SetVideoPllOutputFreq(const clock_video_pll_gpc_config_t *config);
/*!
 * @brief Get current PLL output frequency.
 *
 * This function get current output frequency of specific PLL
 *
 * @param pll   pll name to get frequency.
 * @return The PLL output frequency in hertz.
 */
uint32_t CLOCK_GetPllFreq(clock_pll_t pll);

/*!
 * @brief Initialize PLL PFD.
 *
 * This function initializes the System PLL PFD. During new value setting,
 * the clock output is disabled to prevent glitch.
 *
 * @param pll Which PLL of targeting PFD to be operated.
 * @param pfd Which PFD clock to enable.
 * @param frac The PFD FRAC value.
 * @note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitPfd(clock_pll_t pll, clock_pfd_t pfd, uint8_t frac);

/*!
 * @brief De-initialize selected PLL PFD.
 *
 * @param pll Which PLL of targeting PFD to be operated.
 * @param pfd Which PFD clock to enable.
 */
void CLOCK_DeinitPfd(clock_pll_t pll, clock_pfd_t pfd);

/*!
 * @brief Get current PFD output frequency.
 *
 * This function get current output frequency of specific System PLL PFD
 *
 * @param pll Which PLL of targeting PFD to be operated.
 * @param pfd pfd name to get frequency.
 * @return The PFD output frequency in hertz.
 */
uint32_t CLOCK_GetPfdFreq(clock_pll_t pll, clock_pfd_t pfd);

uint32_t CLOCK_GetFreqFromObs(uint32_t obsSigIndex, uint32_t obsIndex);

/*! @brief Enable USB HS clock.
 *
 * This function only enables the access to USB HS prepheral, upper layer
 * should first call the @ref CLOCK_EnableUsbhs0PhyPllClock to enable the PHY
 * clock to use USB HS.
 *
 * @param src  USB HS does not care about the clock source, here must be @ref kCLOCK_UsbSrcUnused.
 * @param freq USB HS does not care about the clock source, so this parameter is ignored.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0Clock(clock_usb_src_t src, uint32_t freq);

/*! @brief Enable USB HS clock.
 *
 * This function only enables the access to USB HS prepheral, upper layer
 * should first call the @ref CLOCK_EnableUsbhs0PhyPllClock to enable the PHY
 * clock to use USB HS.
 *
 * @param src  USB HS does not care about the clock source, here must be @ref kCLOCK_UsbSrcUnused.
 * @param freq USB HS does not care about the clock source, so this parameter is ignored.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs1Clock(clock_usb_src_t src, uint32_t freq);

/*! @brief Enable USB HS PHY PLL clock.
 *
 * This function enables the internal 480MHz USB PHY PLL clock.
 *
 * @param src  USB HS PHY PLL clock source.
 * @param freq The frequency specified by src.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0PhyPllClock(clock_usb_phy_src_t src, uint32_t freq);

/*! @brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs0PhyPllClock(void);

/*! @brief Enable USB HS PHY PLL clock.
 *
 * This function enables the internal 480MHz USB PHY PLL clock.
 *
 * @param src  USB HS PHY PLL clock source.
 * @param freq The frequency specified by src.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs1PhyPllClock(clock_usb_phy_src_t src, uint32_t freq);

/*! @brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs1PhyPllClock(void);

/*!
 * @brief Lock low power and access control mode for this clock.
 *
 * @note When this bit is set, bits 16-20 can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 */
static inline void CLOCK_OSCPLL_LockControlMode(clock_name_t name)
{
    CCM->OSCPLL[name].AUTHEN |= CCM_OSCPLL_AUTHEN_LOCK_MODE_MASK;
}

/*!
 * @brief Lock the value of Domain ID white list for this clock.
 *
 * @note Once locked, this bit and domain ID white list can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 */
static inline void CLOCK_OSCPLL_LockWhiteList(clock_name_t name)
{
    CCM->OSCPLL[name].AUTHEN |= CCM_OSCPLL_AUTHEN_LOCK_LIST_MASK;
}

/*!
 * @brief Set domain ID that can change this clock.
 *
 * @note If LOCK_LIST bit is set, domain ID white list can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_OSCPLL_SetWhiteList(clock_name_t name, uint8_t domainId)
{
    CCM->OSCPLL[name].AUTHEN =
        (CCM->OSCPLL[name].AUTHEN & ~CCM_OSCPLL_AUTHEN_WHITE_LIST_MASK) | CCM_OSCPLL_AUTHEN_WHITE_LIST(domainId);
}

/*!
 * @brief Check whether this clock implement SetPoint control scheme.
 *
 * @param name Clock source name, see \ref clock_name_t.
 * @return  Clock source SetPoint implement status.
 *         - true: SetPoint is implemented.
 *         - false: SetPoint is not implemented.
 */
static inline bool CLOCK_OSCPLL_IsSetPointImplemented(clock_name_t name)
{
    return (((CCM->OSCPLL[name].CONFIG & CCM_OSCPLL_CONFIG_SETPOINT_PRESENT_MASK) >>
             CCM_OSCPLL_CONFIG_SETPOINT_PRESENT_SHIFT) != 0UL);
}

/*!
 * @brief Set this clock works in Unassigned Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 */
static inline void CLOCK_OSCPLL_ControlByUnassignedMode(clock_name_t name)
{
    CCM->OSCPLL[name].AUTHEN &=
        ~(CCM_OSCPLL_AUTHEN_CPULPM_MASK | CCM_OSCPLL_AUTHEN_DOMAIN_MODE_MASK | CCM_OSCPLL_AUTHEN_SETPOINT_MODE_MASK);
}

/*!
 * @brief Set this clock works in SetPoint control Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 * @param spValue Bit0~Bit15 hold value for Setpoint 0~16 respectively.
 *                A bitfield value of 0 implies clock will be shutdown in this Setpoint.
 *                A bitfield value of 1 implies clock will be turn on in this Setpoint.
 * @param stbyValue Bit0~Bit15 hold value for Setpoint 0~16 standby.
 *                A bitfield value of 0 implies clock will be shutdown during standby.
 *                A bitfield value of 1 represent clock will keep Setpoint setting during standby.
 */
void CLOCK_OSCPLL_ControlBySetPointMode(clock_name_t name, uint16_t spValue, uint16_t stbyValue);

/*!
 * @brief Set this clock works in CPU Low Power Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 * @param domainId Domains that on the whitelist can change this clock.
 * @param level0,level1 Depend level of this clock.
 */
void CLOCK_OSCPLL_ControlByCpuLowPowerMode(clock_name_t name,
                                           uint8_t domainId,
                                           clock_level_t level0,
                                           clock_level_t level1);

/*!
 * @brief Set clock depend level for current accessing domain.
 *
 * @note This setting only take effects in CPU Low Power Mode.
 *
 * @param name Clock source name, see \ref clock_name_t.
 * @param level Depend level of this clock.
 */
static inline void CLOCK_OSCPLL_SetCurrentClockLevel(clock_name_t name, clock_level_t level)
{
    CCM->OSCPLL[name].DOMAINr =
        (CCM->OSCPLL[name].DOMAINr & ~CCM_OSCPLL_DOMAIN_LEVEL_MASK) | CCM_OSCPLL_DOMAIN_LEVEL(level);
}

/*!
 * @brief Set this clock works in Domain Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_OSCPLL_ControlByDomainMode(clock_name_t name, uint8_t domainId)
{
    CCM->OSCPLL[name].AUTHEN =
        (CCM->OSCPLL[name].AUTHEN &
         ~(CCM_OSCPLL_AUTHEN_CPULPM_MASK | CCM_OSCPLL_AUTHEN_SETPOINT_MODE_MASK | CCM_OSCPLL_AUTHEN_WHITE_LIST_MASK)) |
        CCM_OSCPLL_AUTHEN_DOMAIN_MODE_MASK | CCM_OSCPLL_AUTHEN_WHITE_LIST(domainId);
}

/*!
 * @brief Lock low power and access control mode for this clock.
 *
 * @note When this bit is set, bits 16-20 can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 */
static inline void CLOCK_ROOT_LockControlMode(clock_root_t name)
{
    CCM->CLOCK_ROOT[name].AUTHEN |= CCM_CLOCK_ROOT_AUTHEN_LOCK_MODE_MASK;
}

/*!
 * @brief Lock the value of Domain ID white list for this clock.
 *
 * @note Once locked, this bit and domain ID white list can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 */
static inline void CLOCK_ROOT_LockWhiteList(clock_root_t name)
{
    CCM->CLOCK_ROOT[name].AUTHEN |= CCM_CLOCK_ROOT_AUTHEN_LOCK_LIST_MASK;
}

/*!
 * @brief Set domain ID that can change this clock.
 *
 * @note If LOCK_LIST bit is set, domain ID white list can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_ROOT_SetWhiteList(clock_root_t name, uint8_t domainId)
{
    CCM->CLOCK_ROOT[name].AUTHEN = (CCM->CLOCK_ROOT[name].AUTHEN & ~CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST_MASK) |
                                   CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST(domainId);
}

/*!
 * @brief Check whether this clock implement SetPoint control scheme.
 *
 * @param name Clock root name, see \ref clock_root_t.
 * @return  Clock root SetPoint implement status.
 *         - true: SetPoint is implemented.
 *         - false: SetPoint is not implemented.
 */
static inline bool CLOCK_ROOT_IsSetPointImplemented(clock_root_t name)
{
    return (((CCM->CLOCK_ROOT[name].CONFIG & CCM_CLOCK_ROOT_CONFIG_SETPOINT_PRESENT_MASK) >>
             CCM_CLOCK_ROOT_CONFIG_SETPOINT_PRESENT_SHIFT) != 0UL);
}

/*!
 * @brief Set this clock works in Unassigned Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 */
static inline void CLOCK_ROOT_ControlByUnassignedMode(clock_root_t name)
{
    CCM->CLOCK_ROOT[name].AUTHEN &=
        ~(CCM_CLOCK_ROOT_AUTHEN_DOMAIN_MODE_MASK | CCM_CLOCK_ROOT_AUTHEN_SETPOINT_MODE_MASK);
}

/*!
 * @brief Configure one SetPoint for this clock.
 *
 * @note SetPoint value could only be changed in Unassigend Mode.
 *
 * @param name Which clock root to set, see \ref clock_root_t.
 * @param spIndex Which SetPoint of this clock root to set.
 * @param config SetPoint config, see \ref clock_root_setpoint_config_t
 */
static inline void CLOCK_ROOT_ConfigSetPoint(clock_root_t name,
                                             uint16_t spIndex,
                                             const clock_root_setpoint_config_t *config)
{
    assert(config != NULL);
    CCM->CLOCK_ROOT[name].SETPOINT[spIndex] =
        CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_GRADE(config->grade) |
        CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_MUX(config->mux) |
        CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_DIV((uint32_t)config->div - 1UL) |
        CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_OFF(config->clockOff);
}

/*!
 * @brief Enable SetPoint control for this clock root.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 */
static inline void CLOCK_ROOT_EnableSetPointControl(clock_root_t name)
{
    CCM->CLOCK_ROOT[name].AUTHEN = (CCM->CLOCK_ROOT[name].AUTHEN & ~CCM_CLOCK_ROOT_AUTHEN_DOMAIN_MODE_MASK) |
                                   CCM_CLOCK_ROOT_AUTHEN_SETPOINT_MODE_MASK;
}

/*!
 * @brief Set this clock works in SetPoint controlled Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 * @param spTable Point to the array that stores clock root settings for each setpoint. Note that the pointed array must
 * have 16 elements.
 */
void CLOCK_ROOT_ControlBySetPointMode(clock_root_t name, const clock_root_setpoint_config_t *spTable);

/*!
 * @brief Set this clock works in CPU Low Power Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_ROOT_ControlByDomainMode(clock_root_t name, uint8_t domainId)
{
    CCM->CLOCK_ROOT[name].AUTHEN = (CCM->CLOCK_ROOT[name].AUTHEN & ~(CCM_CLOCK_ROOT_AUTHEN_SETPOINT_MODE_MASK |
                                                                     CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST_MASK)) |
                                   CCM_CLOCK_ROOT_AUTHEN_DOMAIN_MODE_MASK | CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST(domainId);
}

/*!
 * @brief Lock low power and access control mode for this clock.
 *
 * @note When this bit is set, bits 16-20 can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 */
static inline void CLOCK_LPCG_LockControlMode(clock_lpcg_t name)
{
    CCM->LPCG[name].AUTHEN |= CCM_LPCG_AUTHEN_LOCK_MODE_MASK;
}

/*!
 * @brief Lock the value of Domain ID white list for this clock.
 *
 * @note Once locked, this bit and domain ID white list can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 */
static inline void CLOCK_LPCG_LockWhiteList(clock_lpcg_t name)
{
    CCM->LPCG[name].AUTHEN |= CCM_LPCG_AUTHEN_LOCK_LIST_MASK;
}

/*!
 * @brief Set domain ID that can change this clock.
 *
 * @note If LOCK_LIST bit is set, domain ID white list can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_LPCG_SetWhiteList(clock_lpcg_t name, uint8_t domainId)
{
    CCM->LPCG[name].AUTHEN =
        (CCM->LPCG[name].AUTHEN & ~CCM_LPCG_AUTHEN_WHITE_LIST_MASK) | CCM_LPCG_AUTHEN_WHITE_LIST(domainId);
}

/*!
 * @brief Check whether this clock implement SetPoint control scheme.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 * @return  Clock gate SetPoint implement status.
 *         - true: SetPoint is implemented.
 *         - false: SetPoint is not implemented.
 */
static inline bool CLOCK_LPCG_IsSetPointImplemented(clock_lpcg_t name)
{
    return (((CCM->LPCG[name].CONFIG & CCM_LPCG_CONFIG_SETPOINT_PRESENT_MASK) >>
             CCM_LPCG_CONFIG_SETPOINT_PRESENT_SHIFT) != 0UL);
}

/*!
 * @brief Set this clock works in Unassigned Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 */
static inline void CLOCK_LPCG_ControlByUnassignedMode(clock_lpcg_t name)
{
    CCM->LPCG[name].AUTHEN &=
        ~(CCM_LPCG_AUTHEN_CPULPM_MASK | CCM_LPCG_AUTHEN_DOMAIN_MODE_MASK | CCM_LPCG_AUTHEN_SETPOINT_MODE_MASK);
}

/*!
 * @brief Set this clock works in SetPoint control Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 * @param spValue Bit0~Bit15 hold value for Setpoint 0~16 respectively.
 *                A bitfield value of 0 implies clock will be shutdown in this Setpoint.
 *                A bitfield value of 1 implies clock will be turn on in this Setpoint.
 * @param stbyValue Bit0~Bit15 hold value for Setpoint 0~16 standby.
 *                A bitfield value of 0 implies clock will be shutdown during standby.
 *                A bitfield value of 1 represent clock will keep Setpoint setting during standby.
 */
void CLOCK_LPCG_ControlBySetPointMode(clock_lpcg_t name, uint16_t spValue, uint16_t stbyValue);

/*!
 * @brief Set this clock works in CPU Low Power Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 * @param domainId Domains that on the whitelist can change this clock.
 * @param level0,level1 Depend level of this clock.
 */
void CLOCK_LPCG_ControlByCpuLowPowerMode(clock_lpcg_t name,
                                         uint8_t domainId,
                                         clock_level_t level0,
                                         clock_level_t level1);

/*!
 * @brief Set clock depend level for current accessing domain.
 *
 * @note This setting only take effects in CPU Low Power Mode.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 * @param level Depend level of this clock.
 */
static inline void CLOCK_LPCG_SetCurrentClockLevel(clock_lpcg_t name, clock_level_t level)
{
    CCM->LPCG[name].DOMAINr = (CCM->LPCG[name].DOMAINr & ~CCM_LPCG_DOMAIN_LEVEL_MASK) | CCM_LPCG_DOMAIN_LEVEL(level);
}

/*!
 * @brief Set this clock works in Domain Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_LPCG_ControlByDomainMode(clock_lpcg_t name, uint8_t domainId)
{
    CCM->LPCG[name].AUTHEN =
        (CCM->LPCG[name].AUTHEN &
         ~(CCM_LPCG_AUTHEN_SETPOINT_MODE_MASK | CCM_LPCG_AUTHEN_CPULPM_MASK | CCM_LPCG_AUTHEN_WHITE_LIST_MASK)) |
        CCM_LPCG_AUTHEN_DOMAIN_MODE_MASK | CCM_LPCG_AUTHEN_WHITE_LIST(domainId);
}

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
