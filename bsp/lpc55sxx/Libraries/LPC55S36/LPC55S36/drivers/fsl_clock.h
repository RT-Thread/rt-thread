/*
 * Copyright 2017 - 2021 , NXP
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
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.3.1. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 3, 1))
/*@}*/

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

/*!
 * @brief User-defined the size of cache for CLOCK_PllGetConfig() function.
 *
 * Once define this MACRO to be non-zero value, CLOCK_PllGetConfig() function
 * would cache the recent calulation and accelerate the execution to get the
 * right settings.
 */
#ifndef CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT
#define CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT 2U
#endif

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (100000000UL)
#endif

/*! @brief Clock ip name array for ROM. */
#define ROM_CLOCKS \
    {              \
        kCLOCK_Rom \
    }
/*! @brief Clock ip name array for SRAM. */
#define SRAM_CLOCKS                                            \
    {                                                          \
        kCLOCK_Sram1, kCLOCK_Sram2, kCLOCK_Sram3, kCLOCK_Sram4 \
    }
/*! @brief Clock ip name array for FLASH. */
#define FLASH_CLOCKS \
    {                \
        kCLOCK_Flash \
    }
/*! @brief Clock ip name array for FMC. */
#define FMC_CLOCKS \
    {              \
        kCLOCK_Fmc \
    }
/*! @brief Clock ip name array for INPUTMUX. */
#define INPUTMUX_CLOCKS \
    {                   \
        kCLOCK_InputMux \
    }
/*! @brief Clock ip name array for IOCON. */
#define IOCON_CLOCKS \
    {                \
        kCLOCK_Iocon \
    }
/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                                            \
    {                                                          \
        kCLOCK_Gpio0, kCLOCK_Gpio1, kCLOCK_Gpio2, kCLOCK_Gpio3 \
    }
/*! @brief Clock ip name array for PINT. */
#define PINT_CLOCKS \
    {               \
        kCLOCK_Pint \
    }
/*! @brief Clock ip name array for GINT. */
#define GINT_CLOCKS              \
    {                            \
        kCLOCK_Gint, kCLOCK_Gint \
    }
/*! @brief Clock ip name array for DMA. */
#define DMA_CLOCKS               \
    {                            \
        kCLOCK_Dma0, kCLOCK_Dma1 \
    }
/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS  \
    {               \
        kCLOCK_Crc0 \
    }
/*! @brief Clock ip name array for WWDT. */
#define WWDT_CLOCKS \
    {               \
        kCLOCK_Wwdt \
    }
/*! @brief Clock ip name array for RTC. */
#define RTC_CLOCKS  \
    {               \
        kCLOCK_Rtc0 \
    }
/*! @brief Clock ip name array for Mailbox. */
#define MAILBOX_CLOCKS \
    {                  \
        kCLOCK_Mailbox \
    }
/*! @brief Clock ip name array for LPADC. */
#define LPADC_CLOCKS             \
    {                            \
        kCLOCK_Adc0, kCLOCK_Adc1 \
    }
/*! @brief Clock ip name array for DAC. */
#define LPDAC_CLOCKS                          \
    {                                         \
        kCLOCK_Dac0, kCLOCK_Dac1, kCLOCK_Dac2 \
    }
/*! @brief Clock ip name array for MRT. */
#define MRT_CLOCKS \
    {              \
        kCLOCK_Mrt \
    }
/*! @brief Clock ip name array for OSTIMER. */
#define OSTIMER_CLOCKS \
    {                  \
        kCLOCK_Ostimer \
    }
/*! @brief Clock ip name array for SCT0. */
#define SCT_CLOCKS \
    {              \
        kCLOCK_Sct \
    }
/*! @brief Clock ip name array for MCAN. */
#define MCAN_CLOCKS \
    {               \
        kCLOCK_Mcan \
    }
/*! @brief Clock ip name array for UTICK. */
#define UTICK_CLOCKS \
    {                \
        kCLOCK_Utick \
    }
/*! @brief Clock ip name array for FLEXCOMM. */
#define FLEXCOMM_CLOCKS                                                                                             \
    {                                                                                                               \
        kCLOCK_FlexComm0, kCLOCK_FlexComm1, kCLOCK_FlexComm2, kCLOCK_FlexComm3, kCLOCK_FlexComm4, kCLOCK_FlexComm5, \
            kCLOCK_FlexComm6, kCLOCK_FlexComm7, kCLOCK_Hs_Lspi                                                      \
    }
/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                         \
    {                                                                                                         \
        kCLOCK_MinUart0, kCLOCK_MinUart1, kCLOCK_MinUart2, kCLOCK_MinUart3, kCLOCK_MinUart4, kCLOCK_MinUart5, \
            kCLOCK_MinUart6, kCLOCK_MinUart7                                                                  \
    }

/*! @brief Clock ip name array for BI2C. */
#define BI2C_CLOCKS                                                                                                    \
    {                                                                                                                  \
        kCLOCK_BI2c0, kCLOCK_BI2c1, kCLOCK_BI2c2, kCLOCK_BI2c3, kCLOCK_BI2c4, kCLOCK_BI2c5, kCLOCK_BI2c6, kCLOCK_BI2c7 \
    }
/*! @brief Clock ip name array for LSPI. */
#define LPSPI_CLOCKS                                                                                                   \
    {                                                                                                                  \
        kCLOCK_LSpi0, kCLOCK_LSpi1, kCLOCK_LSpi2, kCLOCK_LSpi3, kCLOCK_LSpi4, kCLOCK_LSpi5, kCLOCK_LSpi6, kCLOCK_LSpi7 \
    }
/*! @brief Clock ip name array for FLEXI2S. */
#define FLEXI2S_CLOCKS                                                                                        \
    {                                                                                                         \
        kCLOCK_FlexI2s0, kCLOCK_FlexI2s1, kCLOCK_FlexI2s2, kCLOCK_FlexI2s3, kCLOCK_FlexI2s4, kCLOCK_FlexI2s5, \
            kCLOCK_FlexI2s6, kCLOCK_FlexI2s7                                                                  \
    }
/*! @brief Clock ip name array for CTIMER. */
#define CTIMER_CLOCKS                                                             \
    {                                                                             \
        kCLOCK_Timer0, kCLOCK_Timer1, kCLOCK_Timer2, kCLOCK_Timer3, kCLOCK_Timer4 \
    }
/*! @brief Clock ip name array for COMP */
#define COMP_CLOCKS \
    {               \
        kCLOCK_Comp \
    }
/*! @brief Clock ip name array for FREQME. */
#define FREQME_CLOCKS \
    {                 \
        kCLOCK_Freqme \
    }
/*! @brief Clock ip name array for CDOG. */
#define CDOG_CLOCKS \
    {               \
        kCLOCK_Cdog \
    }
/*! @brief Clock ip name array for RNG. */
#define RNG_CLOCKS \
    {              \
        kCLOCK_Rng \
    }
/*! @brief Clock ip name array for USBHMR0. */
#define USBHMR0_CLOCKS \
    {                  \
        kCLOCK_Usbhmr0 \
    }
/*! @brief Clock ip name array for USBHSL0. */
#define USBHSL0_CLOCKS \
    {                  \
        kCLOCK_Usbhsl0 \
    }
/*! @brief Clock ip name array for ANALOGCTRL. */
#define ANALOGCTRL_CLOCKS \
    {                     \
        kCLOCK_AnalogCtrl \
    }
/*! @brief Clock ip name array for HS_LSPI. */
#define HS_LSPI_CLOCKS \
    {                  \
        kCLOCK_Hs_Lspi \
    }
/*! @brief Clock ip name array for GPIO_SEC. */
#define GPIO_SEC_CLOCKS \
    {                   \
        kCLOCK_Gpio_Sec \
    }
/*! @brief Clock ip name array for GPIO_SEC_INT. */
#define GPIO_SEC_INT_CLOCKS \
    {                       \
        kCLOCK_Gpio_Sec_Int \
    }
/*! @brief Clock ip name array for USBD. */
#define USBD_CLOCKS  \
    {                \
        kCLOCK_Usbd0 \
    }
/*! @brief Clock ip name array for SYSCTL. */
#define SYSCTL_CLOCKS \
    {                 \
        kCLOCK_Sysctl \
    }
/*! @brief Clock ip name array for DMIC. */
#define DMIC_CLOCKS \
    {               \
        kCLOCK_Dmic \
    }
/*! @brief Clock ip name array for PWM. */
#define PWM_CLOCKS                                             \
    {                                                          \
        {kCLOCK_Pwm0, kCLOCK_Pwm0, kCLOCK_Pwm0, kCLOCK_Pwm0},  \
        {                                                      \
            kCLOCK_Pwm1, kCLOCK_Pwm1, kCLOCK_Pwm1, kCLOCK_Pwm1 \
        }                                                      \
    }
/*! @brief Clock ip name array for ENC. */
#define ENC_CLOCKS               \
    {                            \
        kCLOCK_Enc0, kCLOCK_Enc1 \
    }
/*! @brief Clock ip name array for OPAMP. */
#define OPAMP_CLOCKS                                \
    {                                               \
        kCLOCK_Opamp0, kCLOCK_Opamp1, kCLOCK_Opamp2 \
    }
/*! @brief Clock ip name array for VREF. */
#define VREF_CLOCKS \
    {               \
        kCLOCK_Vref \
    }
/*! @brief Clock ip name array for FLEXSPI */
#define FLEXSPI_CLOCKS \
    {                  \
        kCLOCK_Flexspi \
    }
/*! @brief Clock ip name array for Cache64 */
#define CACHE64_CLOCKS \
    {                  \
        kCLOCK_Flexspi \
    }
/*! @brief Clock ip name array for I3C */
#define I3C_CLOCKS  \
    {               \
        kCLOCK_I3c0 \
    }
/*! @brief Clock ip name array for HSCMP */
#define HSCMP_CLOCKS                                \
    {                                               \
        kCLOCK_Hscmp0, kCLOCK_Hscmp1, kCLOCK_Hscmp2 \
    }
/*! @brief Clock ip name array for PowerQuad. */
#define POWERQUAD_CLOCKS \
    {                    \
        kCLOCK_PowerQuad \
    }
/*! @brief Clock ip name array for AOI. */
#define AOI_CLOCKS               \
    {                            \
        kCLOCK_Aoi0, kCLOCK_Aoi1 \
    }
/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
/*------------------------------------------------------------------------------
 clock_ip_name_t definition:
------------------------------------------------------------------------------*/

#define CLK_GATE_REG_OFFSET_SHIFT 8U
#define CLK_GATE_REG_OFFSET_MASK  0xFFFFFF00U
#define CLK_GATE_BIT_SHIFT_SHIFT  0U
#define CLK_GATE_BIT_SHIFT_MASK   0x000000FFU

#define CLK_GATE_DEFINE(reg_offset, bit_shift)                                  \
    ((((reg_offset) << CLK_GATE_REG_OFFSET_SHIFT) & CLK_GATE_REG_OFFSET_MASK) | \
     (((bit_shift) << CLK_GATE_BIT_SHIFT_SHIFT) & CLK_GATE_BIT_SHIFT_MASK))

#define CLK_GATE_ABSTRACT_REG_OFFSET(x) (((uint32_t)(x)&CLK_GATE_REG_OFFSET_MASK) >> CLK_GATE_REG_OFFSET_SHIFT)
#define CLK_GATE_ABSTRACT_BITS_SHIFT(x) (((uint32_t)(x)&CLK_GATE_BIT_SHIFT_MASK) >> CLK_GATE_BIT_SHIFT_SHIFT)

#define AHB_CLK_CTRL0 0
#define AHB_CLK_CTRL1 1
#define AHB_CLK_CTRL2 2
#define AHB_CLK_CTRL3 3

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,                                 /*!< Invalid IP name. */
    kCLOCK_Rom       = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 1U), /*!< Clock gate name: Rom. */

    kCLOCK_Sram1 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 3U), /*!< Clock gate name: Sram1. */

    kCLOCK_Sram2 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 4U), /*!< Clock gate name: Sram2. */

    kCLOCK_Sram3 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 5U), /*!< Clock gate name: Sram3. */

    kCLOCK_Sram4 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 6U), /*!< Clock gate name: Sram4. */

    kCLOCK_Flash = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 7U), /*!< Clock gate name: Flash. */

    kCLOCK_Fmc = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 8U), /*!< Clock gate name: Fmc. */

    kCLOCK_Flexspi = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 10U), /*!< Clock gate name: Flexspi. */

    kCLOCK_InputMux = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 11U), /*!< Clock gate name: InputMux. */

    kCLOCK_Iocon = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 13U), /*!< Clock gate name: Iocon. */

    kCLOCK_Gpio0 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 14U), /*!< Clock gate name: Gpio0. */

    kCLOCK_Gpio1 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 15U), /*!< Clock gate name: Gpio1. */

    kCLOCK_Gpio2 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 16U), /*!< Clock gate name: Gpio2. */

    kCLOCK_Gpio3 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 17U), /*!< Clock gate name: Gpio3. */

    kCLOCK_Pint = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 18U), /*!< Clock gate name: Pint. */

    kCLOCK_Gint = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 19U), /*!< Clock gate name: Gint. */

    kCLOCK_Dma0 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 20U), /*!< Clock gate name: Dma0. */

    kCLOCK_Crc0 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 21U), /*!< Clock gate name: Crc. */

    kCLOCK_Wwdt = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 22U), /*!< Clock gate name: Wwdt. */

    kCLOCK_Rtc0 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 23U), /*!< Clock gate name: Rtc0. */

    kCLOCK_Mailbox = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 26U), /*!< Clock gate name: Mailbox. */

    kCLOCK_Adc0 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 27U), /*!< Clock gate name: Adc0. */

    kCLOCK_Adc1 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 28U), /*!< Clock gate name: Adc1. */

    kCLOCK_Dac0 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 29U), /*!< Clock gate name: Dac0. */

    kCLOCK_Mrt = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 0U), /*!< Clock gate name: Mrt. */

    kCLOCK_Ostimer = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 1U), /*!< Clock gate name: Ostimer. */

    kCLOCK_Sct = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 2U), /*!< Clock gate name: Sct. */

    kCLOCK_Mcan = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 7U), /*!< Clock gate name: Mcan. */

    kCLOCK_Utick = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 10U), /*!< Clock gate name: Utick. */

    kCLOCK_FlexComm0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11U), /*!< Clock gate name: FlexComm0. */

    kCLOCK_FlexComm1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12U), /*!< Clock gate name: FlexComm1. */

    kCLOCK_FlexComm2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13U), /*!< Clock gate name: FlexComm2. */

    kCLOCK_FlexComm3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14U), /*!< Clock gate name: FlexComm3. */

    kCLOCK_FlexComm4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15U), /*!< Clock gate name: FlexComm4. */

    kCLOCK_FlexComm5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16U), /*!< Clock gate name: FlexComm5. */

    kCLOCK_FlexComm6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17U), /*!< Clock gate name: FlexComm6. */

    kCLOCK_FlexComm7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18U), /*!< Clock gate name: FlexComm7. */

    kCLOCK_MinUart0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: MinUart0. */

    kCLOCK_MinUart1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: MinUart1. */

    kCLOCK_MinUart2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: MinUart2. */

    kCLOCK_MinUart3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: MinUart3. */

    kCLOCK_MinUart4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: MinUart4. */

    kCLOCK_MinUart5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: MinUart5. */

    kCLOCK_MinUart6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: MinUart6. */

    kCLOCK_MinUart7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: MinUart7. */

    kCLOCK_LSpi0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: LSpi0. */

    kCLOCK_LSpi1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: LSpi1. */

    kCLOCK_LSpi2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: LSpi2. */

    kCLOCK_LSpi3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: LSpi3. */

    kCLOCK_LSpi4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: LSpi4. */

    kCLOCK_LSpi5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: LSpi5. */

    kCLOCK_LSpi6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: LSpi6. */

    kCLOCK_LSpi7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: LSpi7. */

    kCLOCK_BI2c0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: BI2c0. */

    kCLOCK_BI2c1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: BI2c1. */

    kCLOCK_BI2c2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: BI2c2. */

    kCLOCK_BI2c3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: BI2c3. */

    kCLOCK_BI2c4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: BI2c4. */

    kCLOCK_BI2c5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: BI2c5. */

    kCLOCK_BI2c6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: BI2c6. */

    kCLOCK_BI2c7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: BI2c7. */

    kCLOCK_FlexI2s0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: FlexI2s0. */

    kCLOCK_FlexI2s1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: FlexI2s1. */

    kCLOCK_FlexI2s2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: FlexI2s2. */

    kCLOCK_FlexI2s3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: FlexI2s3. */

    kCLOCK_FlexI2s4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: FlexI2s4. */

    kCLOCK_FlexI2s5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: FlexI2s5. */

    kCLOCK_FlexI2s6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: FlexI2s6. */

    kCLOCK_FlexI2s7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: FlexI2s7. */

    kCLOCK_Dmic = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 19U), /*!< Clock gate name: Dmic. */

    kCLOCK_Timer2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 22U), /*!< Clock gate name: Timer2. */

    kCLOCK_Usbd0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 25U), /*!< Clock gate name: Usbd0. */

    kCLOCK_Timer0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 26U), /*!< Clock gate name: Timer0. */

    kCLOCK_Timer1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 27U), /*!< Clock gate name: Timer1. */

    kCLOCK_Dma1 = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 1U), /*!< Clock gate name: Dma1. */

    kCLOCK_Comp = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 2U), /*!< Clock gate name: Comp. */

    kCLOCK_Freqme = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 8U), /*!< Clock gate name: Freqme. */

    kCLOCK_Cdog = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 11U), /*!< Clock gate name: Cdog. */

    kCLOCK_Rng = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 13U), /*!< Clock gate name: Rng. */

    kCLOCK_Pmux1 = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 14U), /*!< Clock gate name: Pmux1. */

    kCLOCK_Sysctl = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 15U), /*!< Clock gate name: Sysctl. */

    kCLOCK_Usbhmr0 = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 16U), /*!< Clock gate name: Usbhmr0. */

    kCLOCK_Usbhsl0 = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 17U), /*!< Clock gate name: Usbhsl0. */

    kCLOCK_Css = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 18U), /*!< Clock gate name: Css. */

    kCLOCK_PowerQuad = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 19U), /*!< Clock gate name: PowerQuad. */

    kCLOCK_Timer3 = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 21U), /*!< Clock gate name: Timer3. */

    kCLOCK_Timer4 = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 22U), /*!< Clock gate name: Timer4. */

    kCLOCK_Puf = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 23U), /*!< Clock gate name: Puf. */

    kCLOCK_Pkc = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 24U), /*!< Clock gate name: Pkc. */

    kCLOCK_AnalogCtrl = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 27U), /*!< Clock gate name: AnalogCtrl. */

    kCLOCK_Hs_Lspi = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 28U), /*!< Clock gate name: Lspi. */

    kCLOCK_Gpio_Sec = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 29U), /*!< Clock gate name: Sec. */

    kCLOCK_Gpio_Sec_Int = CLK_GATE_DEFINE(AHB_CLK_CTRL2, 30U), /*!< Clock gate name: Int. */

    kCLOCK_I3c0 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 0U), /*!< Clock gate name: I3c0. */

    kCLOCK_Enc0 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 3U), /*!< Clock gate name: Enc0. */

    kCLOCK_Enc1 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 4U), /*!< Clock gate name: Enc1. */

    kCLOCK_Pwm0 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 5U), /*!< Clock gate name: Pwm0. */

    kCLOCK_Pwm1 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 6U), /*!< Clock gate name: Pwm1. */

    kCLOCK_Aoi0 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 7U), /*!< Clock gate name: Aoi0. */

    kCLOCK_Aoi1 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 8U), /*!< Clock gate name: Aoi1. */

    kCLOCK_Ftm0 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 9U), /*!< Clock gate name: Ftm0. */

    kCLOCK_Dac1 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 10U), /*!< Clock gate name: Dac1. */

    kCLOCK_Dac2 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 11U), /*!< Clock gate name: Dac2. */

    kCLOCK_Opamp0 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 12U), /*!< Clock gate name: Opamp0. */

    kCLOCK_Opamp1 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 13U), /*!< Clock gate name: Opamp1. */

    kCLOCK_Opamp2 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 14U), /*!< Clock gate name: Opamp2. */

    kCLOCK_Hscmp0 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 15U), /*!< Clock gate name: Hscmp0. */

    kCLOCK_Hscmp1 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 16U), /*!< Clock gate name: Hscmp1. */

    kCLOCK_Hscmp2 = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 17U), /*!< Clock gate name: Hscmp2. */

    kCLOCK_Vref = CLK_GATE_DEFINE(AHB_CLK_CTRL3, 18U) /*!< Clock gate name: Vref. */

} clock_ip_name_t;

/*! @brief Peripherals clock source definition. */
#define BUS_CLK kCLOCK_BusClk

#define I2C0_CLK_SRC BUS_CLK

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreSysClk, /*!< Core/system clock  (aka MAIN_CLK)                       */
    kCLOCK_BusClk,     /*!< Bus clock (AHB clock)                                   */
    kCLOCK_ClockOut,   /*!< CLOCKOUT                                                */
    kCLOCK_FroHf,      /*!< FRO48/96                                                */
    kCLOCK_Pll1Out,    /*!< PLL1 Output                                             */
    kCLOCK_Mclk,       /*!< MCLK                                                    */
    kCLOCK_Fro12M,     /*!< FRO12M                                                  */
    kCLOCK_Fro1M,      /*!< FRO1M                                                   */
    kCLOCK_ExtClk,     /*!< External Clock                                          */
    kCLOCK_Pll0Out,    /*!< PLL0 Output                                             */
    kCLOCK_PllClkDiv,  /*!< PLLCLKDIV clock                                         */
    kCLOCK_FlexI2S,    /*!< FlexI2S clock                                           */
} clock_name_t;

/*! @brief Clock Mux Switches
 *  The encoding is as follows each connection identified is 32bits wide while 24bits are valuable
 *  starting from LSB upwards
 *
 *  [4 bits for choice, 0 means invalid choice] [8 bits mux ID]*
 *
 */

#define CLK_ATTACH_ID(mux, sel, pos) \
    ((((uint32_t)(mux) << 0U) | (((uint32_t)(sel) + 1U) & 0xFU) << 12U) << ((uint32_t)(pos)*16U))
#define MUX_A(mux, sel)           CLK_ATTACH_ID((mux), (sel), 0U)
#define MUX_B(mux, sel, selector) (CLK_ATTACH_ID((mux), (sel), 1U) | ((selector) << 24U))

#define GET_ID_ITEM(connection)      ((connection)&0xFFFFU)
#define GET_ID_NEXT_ITEM(connection) ((connection) >> 16U)
#define GET_ID_ITEM_MUX(connection)  (((uint16_t)connection) & 0xFFFU)
#define GET_ID_ITEM_SEL(connection)  ((uint8_t)((((uint32_t)(connection)&0xF000U) >> 12U) - 1U))
#define GET_ID_SELECTOR(connection)  ((connection)&0xF000000U)

#define CM_SYSTICKCLKSEL0 (0)
#define CM_TRACECLKSEL    (2)
#define CM_CTIMERCLKSEL0  (3)
#define CM_CTIMERCLKSEL1  (4)
#define CM_CTIMERCLKSEL2  (5)
#define CM_CTIMERCLKSEL3  (6)
#define CM_CTIMERCLKSEL4  (7)
#define CM_MAINCLKSELA    (8)
#define CM_MAINCLKSELB    (9)
#define CM_CLKOUTCLKSEL   (10)
#define CM_PLL0CLKSEL     (12)
#define CM_PLL1CLKSEL     (13)
#define CM_MCANCLKSEL     (16)
#define CM_ADC0CLKSEL     (17)
#define CM_USB0CLKSEL     (18)
#define CM_FXCOMCLKSEL0   (20)
#define CM_FXCOMCLKSEL1   (21)
#define CM_FXCOMCLKSEL2   (22)
#define CM_FXCOMCLKSEL3   (23)
#define CM_FXCOMCLKSEL4   (24)
#define CM_FXCOMCLKSEL5   (25)
#define CM_FXCOMCLKSEL6   (26)
#define CM_FXCOMCLKSEL7   (27)
#define CM_HSLSPICLKSEL   (28)
#define CM_MCLKCLKSEL     (32)
#define CM_SCTCLKSEL      (36)

#define CM_ADC1CLKSEL    ((0x464 - 0x260) / 4)
#define CM_DAC0CLKSEL    ((0x490 - 0x260) / 4)
#define CM_DAC1CLKSEL    ((0x498 - 0x260) / 4)
#define CM_DAC2CLKSEL    ((0x4A0 - 0x260) / 4)
#define CM_FLEXSPICLKSEL ((0x4A8 - 0x260) / 4)
#define CM_PLLCLKDIVSEL  ((0x52C - 0x260) / 4)
#define CM_I3CFCLKSEL    ((0x530 - 0x260) / 4)
#define CM_I3CFCLKSTCSEL ((0x534 - 0x260) / 4)
#define CM_I3CFCLKSSEL   ((0x534 - 0x260) / 4)
#define CM_DMICFCLKSEL   ((0x548 - 0x260) / 4)
#define CM_FC32KCLKSEL   ((0x82C - 0x260) / 4)
#define CM_FRGCLKSEL0    ((0x830 - 0x260) / 4)
#define CM_FRGCLKSEL1    ((0x834 - 0x260) / 4)
#define CM_FRGCLKSEL2    ((0x838 - 0x260) / 4)
#define CM_FRGCLKSEL3    ((0x83C - 0x260) / 4)
#define CM_FRGCLKSEL4    ((0x840 - 0x260) / 4)
#define CM_FRGCLKSEL5    ((0x844 - 0x260) / 4)
#define CM_FRGCLKSEL6    ((0x848 - 0x260) / 4)
#define CM_FRGCLKSEL7    ((0x84C - 0x260) / 4)

#define CM_OSTIMERCLKSEL   (252U)
#define CM_RTCOSC32KCLKSEL (253U)

typedef enum _clock_attach_id
{

    kFRO12M_to_MAIN_CLK  = MUX_A(CM_MAINCLKSELA, 0) | MUX_B(CM_MAINCLKSELB, 0, 0), /*!< Attach FRO12M to MAIN_CLK. */
    kEXT_CLK_to_MAIN_CLK = MUX_A(CM_MAINCLKSELA, 1) | MUX_B(CM_MAINCLKSELB, 0, 0), /*!< Attach EXT_CLK to MAIN_CLK. */
    kFRO1M_to_MAIN_CLK   = MUX_A(CM_MAINCLKSELA, 2) | MUX_B(CM_MAINCLKSELB, 0, 0), /*!< Attach FRO1M to MAIN_CLK. */
    kFRO_HF_to_MAIN_CLK  = MUX_A(CM_MAINCLKSELA, 3) | MUX_B(CM_MAINCLKSELB, 0, 0), /*!< Attach FRO_HF to MAIN_CLK. */
    kPLL0_to_MAIN_CLK    = MUX_A(CM_MAINCLKSELA, 0) | MUX_B(CM_MAINCLKSELB, 1, 0), /*!< Attach PLL0 to MAIN_CLK. */
    kPLL1_to_MAIN_CLK    = MUX_A(CM_MAINCLKSELA, 0) | MUX_B(CM_MAINCLKSELB, 2, 0), /*!< Attach PLL1 to MAIN_CLK. */
    kOSC32K_to_MAIN_CLK  = MUX_A(CM_MAINCLKSELA, 0) | MUX_B(CM_MAINCLKSELB, 3, 0), /*!< Attach OSC32K to MAIN_CLK. */

    kSYSTICK_DIV_to_SYSTICK0 = MUX_A(CM_SYSTICKCLKSEL0, 0), /*!< Attach SYSTICK_DIV to SYSTICK0. */
    kFRO1M_to_SYSTICK0       = MUX_A(CM_SYSTICKCLKSEL0, 1), /*!< Attach FRO1M to SYSTICK0. */
    kOSC32K_to_SYSTICK0      = MUX_A(CM_SYSTICKCLKSEL0, 2), /*!< Attach OSC32K to SYSTICK0. */
    kNONE_to_SYSTICK0        = MUX_A(CM_SYSTICKCLKSEL0, 7), /*!< Attach NONE to SYSTICK0. */

    kTRACE_DIV_to_TRACE = MUX_A(CM_TRACECLKSEL, 0), /*!< Attach TRACE_DIV to TRACE. */
    kFRO1M_to_TRACE     = MUX_A(CM_TRACECLKSEL, 1), /*!< Attach FRO1M to TRACE. */
    kOSC32K_to_TRACE    = MUX_A(CM_TRACECLKSEL, 2), /*!< Attach OSC32K to TRACE. */
    kNONE_to_TRACE      = MUX_A(CM_TRACECLKSEL, 7), /*!< Attach NONE to TRACE. */

    kMAIN_CLK_to_CTIMER0 = MUX_A(CM_CTIMERCLKSEL0, 0), /*!< Attach MAIN_CLK to CTIMER0. */
    kPLL0_to_CTIMER0     = MUX_A(CM_CTIMERCLKSEL0, 1), /*!< Attach PLL0 to CTIMER0. */
    kPLL1_to_CTIMER0     = MUX_A(CM_CTIMERCLKSEL0, 2), /*!< Attach PLL1 to CTIMER0. */
    kFRO_HF_to_CTIMER0   = MUX_A(CM_CTIMERCLKSEL0, 3), /*!< Attach FRO_HF to CTIMER0. */
    kFRO1M_to_CTIMER0    = MUX_A(CM_CTIMERCLKSEL0, 4), /*!< Attach FRO1M to CTIMER0. */
    kMCLK_IN_to_CTIMER0  = MUX_A(CM_CTIMERCLKSEL0, 5),
    kOSC32K_to_CTIMER0   = MUX_A(CM_CTIMERCLKSEL0, 6), /*!< Attach OSC32K to CTIMER0. */
    kNONE_to_CTIMER0     = MUX_A(CM_CTIMERCLKSEL0, 7), /*!< Attach NONE to CTIMER0. */

    kMAIN_CLK_to_CTIMER1 = MUX_A(CM_CTIMERCLKSEL1, 0), /*!< Attach MAIN_CLK to CTIMER1. */
    kPLL0_to_CTIMER1     = MUX_A(CM_CTIMERCLKSEL1, 1), /*!< Attach PLL0 to CTIMER1. */
    kPLL1_to_CTIMER1     = MUX_A(CM_CTIMERCLKSEL1, 2), /*!< Attach PLL1 to CTIMER1. */
    kFRO_HF_to_CTIMER1   = MUX_A(CM_CTIMERCLKSEL1, 3), /*!< Attach FRO_HF to CTIMER1. */
    kFRO1M_to_CTIMER1    = MUX_A(CM_CTIMERCLKSEL1, 4), /*!< Attach FRO1M to CTIMER1. */
    kMCLK_IN_to_CTIMER1  = MUX_A(CM_CTIMERCLKSEL1, 5), /*!< Attach MCLK_IN to CTIMER1. */
    kOSC32K_to_CTIMER1   = MUX_A(CM_CTIMERCLKSEL1, 6), /*!< Attach OSC32K to CTIMER1. */
    kNONE_to_CTIMER1     = MUX_A(CM_CTIMERCLKSEL1, 7), /*!< Attach NONE to CTIMER1. */

    kMAIN_CLK_to_CTIMER2 = MUX_A(CM_CTIMERCLKSEL2, 0), /*!< Attach MAIN_CLK to CTIMER2. */
    kPLL0_to_CTIMER2     = MUX_A(CM_CTIMERCLKSEL2, 1), /*!< Attach PLL0 to CTIMER2. */
    kPLL1_to_CTIMER2     = MUX_A(CM_CTIMERCLKSEL2, 2), /*!< Attach PLL1 to CTIMER2. */
    kFRO_HF_to_CTIMER2   = MUX_A(CM_CTIMERCLKSEL2, 3), /*!< Attach FRO_HF to CTIMER2. */
    kFRO1M_to_CTIMER2    = MUX_A(CM_CTIMERCLKSEL2, 4), /*!< Attach FRO1M to CTIMER2. */
    kMCLK_IN_to_CTIMER2  = MUX_A(CM_CTIMERCLKSEL2, 5), /*!< Attach MCLK_IN to CTIMER2. */
    kOSC32K_to_CTIMER2   = MUX_A(CM_CTIMERCLKSEL2, 6), /*!< Attach OSC32K to CTIMER2. */
    kNONE_to_CTIMER2     = MUX_A(CM_CTIMERCLKSEL2, 7), /*!< Attach NONE to CTIMER2. */

    kMAIN_CLK_to_CTIMER3 = MUX_A(CM_CTIMERCLKSEL3, 0), /*!< Attach MAIN_CLK to CTIMER3. */
    kPLL0_to_CTIMER3     = MUX_A(CM_CTIMERCLKSEL3, 1), /*!< Attach PLL0 to CTIMER3. */
    kPLL1_to_CTIMER3     = MUX_A(CM_CTIMERCLKSEL3, 2), /*!< Attach PLL1 to CTIMER3. */
    kFRO_HF_to_CTIMER3   = MUX_A(CM_CTIMERCLKSEL3, 3), /*!< Attach FRO_HF to CTIMER3. */
    kFRO1M_to_CTIMER3    = MUX_A(CM_CTIMERCLKSEL3, 4), /*!< Attach FRO1M to CTIMER3. */
    kMCLK_IN_to_CTIMER3  = MUX_A(CM_CTIMERCLKSEL3, 5), /*!< Attach MCLK_IN to CTIMER3. */
    kOSC32K_to_CTIMER3   = MUX_A(CM_CTIMERCLKSEL3, 6), /*!< Attach OSC32K to CTIMER3. */
    kNONE_to_CTIMER3     = MUX_A(CM_CTIMERCLKSEL3, 7), /*!< Attach NONE to CTIMER3. */

    kMAIN_CLK_to_CTIMER4 = MUX_A(CM_CTIMERCLKSEL4, 0), /*!< Attach MAIN_CLK to CTIMER4. */
    kPLL0_to_CTIMER4     = MUX_A(CM_CTIMERCLKSEL4, 1), /*!< Attach PLL0 to CTIMER4. */
    kPLL1_to_CTIMER4     = MUX_A(CM_CTIMERCLKSEL4, 2), /*!< Attach PLL1 to CTIMER4. */
    kFRO_HF_to_CTIMER4   = MUX_A(CM_CTIMERCLKSEL4, 3), /*!< Attach FRO_HF to CTIMER4. */
    kFRO1M_to_CTIMER4    = MUX_A(CM_CTIMERCLKSEL4, 4), /*!< Attach FRO1M to CTIMER4. */
    kMCLK_IN_to_CTIMER4  = MUX_A(CM_CTIMERCLKSEL4, 5), /*!< Attach MCLK_IN to CTIMER4. */
    kOSC32K_to_CTIMER4   = MUX_A(CM_CTIMERCLKSEL4, 6), /*!< Attach OSC32K to CTIMER4. */
    kNONE_to_CTIMER4     = MUX_A(CM_CTIMERCLKSEL4, 7), /*!< Attach NONE to CTIMER4. */

    kMAIN_CLK_to_CLKOUT = MUX_A(CM_CLKOUTCLKSEL, 0), /*!< Attach MAIN_CLK to CLKOUT. */
    kPLL0_to_CLKOUT     = MUX_A(CM_CLKOUTCLKSEL, 1), /*!< Attach PLL0 to CLKOUT. */
    kEXT_CLK_to_CLKOUT  = MUX_A(CM_CLKOUTCLKSEL, 2), /*!< Attach EXT_CLK to CLKOUT. */
    kFRO_HF_to_CLKOUT   = MUX_A(CM_CLKOUTCLKSEL, 3), /*!< Attach FRO_HF to CLKOUT. */
    kFRO1M_to_CLKOUT    = MUX_A(CM_CLKOUTCLKSEL, 4), /*!< Attach FRO1M to CLKOUT. */
    kPLL1_to_CLKOUT     = MUX_A(CM_CLKOUTCLKSEL, 5), /*!< Attach PLL1 to CLKOUT. */
    kOSC32K_to_CLKOUT   = MUX_A(CM_CLKOUTCLKSEL, 6), /*!< Attach OSC32K to CLKOUT. */
    kNONE_to_CLKOUT     = MUX_A(CM_CLKOUTCLKSEL, 7), /*!< Attach NONE to CLKOUT. */

    kFRO12M_to_PLL0  = MUX_A(CM_PLL0CLKSEL, 0), /*!< Attach FRO12M to PLL0. */
    kEXT_CLK_to_PLL0 = MUX_A(CM_PLL0CLKSEL, 1), /*!< Attach EXT_CLK to PLL0. */
    kFRO1M_to_PLL0   = MUX_A(CM_PLL0CLKSEL, 2), /*!< Attach FRO1M to PLL0. */
    kOSC32K_to_PLL0  = MUX_A(CM_PLL0CLKSEL, 3), /*!< Attach OSC32K to PLL0. */
    kNONE_to_PLL0    = MUX_A(CM_PLL0CLKSEL, 7), /*!< Attach NONE to PLL0. */

    kFRO12M_to_PLL1  = MUX_A(CM_PLL1CLKSEL, 0), /*!< Attach FRO12M to PLL1. */
    kEXT_CLK_to_PLL1 = MUX_A(CM_PLL1CLKSEL, 1), /*!< Attach EXT_CLK to PLL1. */
    kFRO1M_to_PLL1   = MUX_A(CM_PLL1CLKSEL, 2), /*!< Attach FRO1M to PLL1. */
    kOSC32K_to_PLL1  = MUX_A(CM_PLL1CLKSEL, 3), /*!< Attach OSC32K to PLL1. */
    kNONE_to_PLL1    = MUX_A(CM_PLL1CLKSEL, 7), /*!< Attach NONE to PLL1. */

    kMCAN_DIV_to_MCAN = MUX_A(CM_MCANCLKSEL, 0), /*!< Attach MCAN_DIV to MCAN. */
    kFRO1M_to_MCAN    = MUX_A(CM_MCANCLKSEL, 1), /*!< Attach FRO1M to MCAN. */
    kOSC32K_to_MCAN   = MUX_A(CM_MCANCLKSEL, 2), /*!< Attach OSC32K to MCAN. */
    kNONE_to_MCAN     = MUX_A(CM_MCANCLKSEL, 7), /*!< Attach NONE to MCAN. */

    kMAIN_CLK_to_ADC0 = MUX_A(CM_ADC0CLKSEL, 0), /*!< Attach MAIN_CLK to ADC0. */
    kPLL0_to_ADC0     = MUX_A(CM_ADC0CLKSEL, 1), /*!< Attach PLL0 to ADC0. */
    kFRO_HF_to_ADC0   = MUX_A(CM_ADC0CLKSEL, 2), /*!< Attach FRO_HF to ADC0. */
    kEXT_CLK_to_ADC0  = MUX_A(CM_ADC0CLKSEL, 4), /*!< Attach XO to ADC0. */
    kNONE_to_ADC0     = MUX_A(CM_ADC0CLKSEL, 7), /*!< Attach NONE to ADC0. */

    kMAIN_CLK_to_ADC1 = MUX_A(CM_ADC1CLKSEL, 0), /*!< Attach MAIN_CLK to ADC1. */
    kPLL0_to_ADC1     = MUX_A(CM_ADC1CLKSEL, 1), /*!< Attach PLL0 to ADC1. */
    kFRO_HF_to_ADC1   = MUX_A(CM_ADC1CLKSEL, 2), /*!< Attach FRO_HF to ADC1. */
    kNONE_to_ADC1     = MUX_A(CM_ADC1CLKSEL, 7), /*!< Attach NONE to ADC1. */

    kMAIN_CLK_to_USB0 = MUX_A(CM_USB0CLKSEL, 0), /*!< Attach MAIN_CLK to USB0. */
    kPLL0_to_USB0     = MUX_A(CM_USB0CLKSEL, 1), /*!< Attach PLL0 to USB0. */
    kFRO_HF_to_USB0   = MUX_A(CM_USB0CLKSEL, 3), /*!< Attach FRO_HF to USB0. */
    kPLL1_to_USB0     = MUX_A(CM_USB0CLKSEL, 5), /*!< Attach PLL1 to USB0. */
    kNONE_to_USB0     = MUX_A(CM_USB0CLKSEL, 7), /*!< Attach NONE to USB0. */

    kMAIN_CLK_to_FLEXCOMM0      = MUX_A(CM_FXCOMCLKSEL0, 0), /*!< Attach MAIN_CLK to FLEXCOMM0. */
    kMAIN_CLK_FRG0_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 1) | MUX_B(CM_FRGCLKSEL0, 0, 0),    /*!< Attach Main clock
                                                                                                     to FlexComm0. */
    kPLL_CLK_DIV_FRG0_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 1) | MUX_B(CM_FRGCLKSEL0, 1, 0), /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm0. */
    kFRO_HF_DIV_FRG0_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 1) | MUX_B(CM_FRGCLKSEL0, 2, 0),  /*!< Attach FRO HF DIV
                                                                                                 FRG to FlexComm0. */
    kFRO12M_to_FLEXCOMM0     = MUX_A(CM_FXCOMCLKSEL0, 2), /*!< Attach FRO12M to FLEXCOMM0. */
    kFRO_HF_DIV_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 3), /*!< Attach FRO_HF_DIV to FLEXCOMM0. */
    kFRO1M_to_FLEXCOMM0      = MUX_A(CM_FXCOMCLKSEL0, 4), /*!< Attach FRO1M to FLEXCOMM0. */
    kMCLK_IN_to_FLEXCOMM0    = MUX_A(CM_FXCOMCLKSEL0, 5), /*!< Attach MCLK_IN to FLEXCOMM0. */
    kOSC32K_to_FLEXCOMM0     = MUX_A(CM_FXCOMCLKSEL0, 6), /*!< Attach OSC32K to FLEXCOMM0. */
    kNONE_to_FLEXCOMM0       = MUX_A(CM_FXCOMCLKSEL0, 7), /*!< Attach NONE to FLEXCOMM0. */

    kMAIN_CLK_to_FLEXCOMM1      = MUX_A(CM_FXCOMCLKSEL1, 0), /*!< Attach MAIN_CLK to FLEXCOMM1. */
    kMAIN_CLK_FRG1_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 1) | MUX_B(CM_FRGCLKSEL1, 0, 0),    /*!< Attach Main clock
                                                                                                     to FlexComm1. */
    kPLL_CLK_DIV_FRG1_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 1) | MUX_B(CM_FRGCLKSEL1, 1, 0), /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm1. */
    kFRO_HF_DIV_FRG1_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 1) | MUX_B(CM_FRGCLKSEL1, 2, 0),  /*!< Attach FRO HF DIV
                                                                                                 FRG to FlexComm1. */
    kFRO12M_to_FLEXCOMM1     = MUX_A(CM_FXCOMCLKSEL1, 2), /*!< Attach FRO12M to FLEXCOMM1. */
    kFRO_HF_DIV_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 3), /*!< Attach FRO_HF_DIV to FLEXCOMM1. */
    kFRO1M_to_FLEXCOMM1      = MUX_A(CM_FXCOMCLKSEL1, 4), /*!< Attach FRO1M to FLEXCOMM1. */
    kMCLK_IN_to_FLEXCOMM1    = MUX_A(CM_FXCOMCLKSEL1, 5), /*!< Attach MCLK_IN to FLEXCOMM1. */
    kOSC32K_to_FLEXCOMM1     = MUX_A(CM_FXCOMCLKSEL1, 6), /*!< Attach OSC32K to FLEXCOMM1. */
    kNONE_to_FLEXCOMM1       = MUX_A(CM_FXCOMCLKSEL1, 7), /*!< Attach NONE to FLEXCOMM1. */

    kMAIN_CLK_to_FLEXCOMM2      = MUX_A(CM_FXCOMCLKSEL2, 0), /*!< Attach MAIN_CLK to FLEXCOMM2. */
    kMAIN_CLK_FRG2_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 1) | MUX_B(CM_FRGCLKSEL2, 0, 0),    /*!< Attach Main clock
                                                                                                     to FlexComm2. */
    kPLL_CLK_DIV_FRG2_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 1) | MUX_B(CM_FRGCLKSEL2, 1, 0), /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm2. */
    kFRO_HF_DIV_FRG2_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 1) | MUX_B(CM_FRGCLKSEL2, 2, 0),  /*!< Attach FRO HF DIV
                                                                                                 FRG to FlexComm2. */
    kFRO12M_to_FLEXCOMM2     = MUX_A(CM_FXCOMCLKSEL2, 2), /*!< Attach FRO12M to FLEXCOMM2. */
    kFRO_HF_DIV_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 3), /*!< Attach FRO_HF_DIV to FLEXCOMM2. */
    kFRO1M_to_FLEXCOMM2      = MUX_A(CM_FXCOMCLKSEL2, 4), /*!< Attach FRO1M to FLEXCOMM2. */
    kMCLK_IN_to_FLEXCOMM2    = MUX_A(CM_FXCOMCLKSEL2, 5), /*!< Attach MCLK_IN to FLEXCOMM2. */
    kOSC32K_to_FLEXCOMM2     = MUX_A(CM_FXCOMCLKSEL2, 6), /*!< Attach OSC32K to FLEXCOMM2. */
    kNONE_to_FLEXCOMM2       = MUX_A(CM_FXCOMCLKSEL2, 7), /*!< Attach NONE to FLEXCOMM2. */

    kMAIN_CLK_to_FLEXCOMM3      = MUX_A(CM_FXCOMCLKSEL3, 0), /*!< Attach MAIN_CLK to FLEXCOMM3. */
    kMAIN_CLK_FRG3_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 1) | MUX_B(CM_FRGCLKSEL3, 0, 0),    /*!< Attach Main clock
                                                                                                     to FlexComm3. */
    kPLL_CLK_DIV_FRG3_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 1) | MUX_B(CM_FRGCLKSEL3, 1, 0), /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm3. */
    kFRO_HF_DIV_FRG3_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 1) | MUX_B(CM_FRGCLKSEL3, 2, 0),  /*!< Attach FRO HF DIV
                                                                                                 FRG to FlexComm3. */
    kFRO12M_to_FLEXCOMM3     = MUX_A(CM_FXCOMCLKSEL3, 2), /*!< Attach FRO12M to FLEXCOMM3. */
    kFRO_HF_DIV_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 3), /*!< Attach FRO_HF_DIV to FLEXCOMM3. */
    kFRO1M_to_FLEXCOMM3      = MUX_A(CM_FXCOMCLKSEL3, 4), /*!< Attach FRO1M to FLEXCOMM3. */
    kMCLK_IN_to_FLEXCOMM3    = MUX_A(CM_FXCOMCLKSEL3, 5), /*!< Attach MCLK_IN to FLEXCOMM3. */
    kOSC32K_to_FLEXCOMM3     = MUX_A(CM_FXCOMCLKSEL3, 6), /*!< Attach OSC32K to FLEXCOMM3. */
    kNONE_to_FLEXCOMM3       = MUX_A(CM_FXCOMCLKSEL3, 7), /*!< Attach NONE to FLEXCOMM3. */

    kMAIN_CLK_to_FLEXCOMM4      = MUX_A(CM_FXCOMCLKSEL4, 0), /*!< Attach MAIN_CLK to FLEXCOMM4. */
    kMAIN_CLK_FRG4_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 1) | MUX_B(CM_FRGCLKSEL4, 0, 0),    /*!< Attach Main clock
                                                                                                     to FlexComm4. */
    kPLL_CLK_DIV_FRG4_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 1) | MUX_B(CM_FRGCLKSEL4, 1, 0), /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm4. */
    kFRO_HF_DIV_FRG4_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 1) | MUX_B(CM_FRGCLKSEL4, 2, 0),  /*!< Attach FRO HF DIV
                                                                                                 FRG to FlexComm4. */
    kFRO12M_to_FLEXCOMM4     = MUX_A(CM_FXCOMCLKSEL4, 2), /*!< Attach FRO12M to FLEXCOMM4. */
    kFRO_HF_DIV_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 3), /*!< Attach FRO_HF_DIV to FLEXCOMM4. */
    kFRO1M_to_FLEXCOMM4      = MUX_A(CM_FXCOMCLKSEL4, 4), /*!< Attach FRO1M to FLEXCOMM4. */
    kMCLK_IN_to_FLEXCOMM4    = MUX_A(CM_FXCOMCLKSEL4, 5), /*!< Attach MCLK_IN to FLEXCOMM4. */
    kOSC32K_to_FLEXCOMM4     = MUX_A(CM_FXCOMCLKSEL4, 6), /*!< Attach OSC32K to FLEXCOMM4. */
    kNONE_to_FLEXCOMM4       = MUX_A(CM_FXCOMCLKSEL4, 7), /*!< Attach NONE to FLEXCOMM4. */

    kMAIN_CLK_to_FLEXCOMM5      = MUX_A(CM_FXCOMCLKSEL5, 0), /*!< Attach MAIN_CLK to FLEXCOMM5. */
    kMAIN_CLK_FRG5_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 1) | MUX_B(CM_FRGCLKSEL5, 0, 0),    /*!< Attach Main clock
                                                                                                 to FlexComm5. */
    kPLL_CLK_DIV_FRG5_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 1) | MUX_B(CM_FRGCLKSEL5, 1, 0), /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm5. */
    kFRO_HF_DIV_FRG5_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 1) | MUX_B(CM_FRGCLKSEL5, 2, 0),  /*!< Attach FRO HF DIV
                                                                                                 FRG to FlexComm5. */
    kFRO12M_to_FLEXCOMM5     = MUX_A(CM_FXCOMCLKSEL5, 2), /*!< Attach FRO12M to FLEXCOMM5. */
    kFRO_HF_DIV_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 3), /*!< Attach FRO_HF_DIV to FLEXCOMM5. */
    kFRO1M_to_FLEXCOMM5      = MUX_A(CM_FXCOMCLKSEL5, 4), /*!< Attach FRO1M to FLEXCOMM5. */
    kMCLK_IN_to_FLEXCOMM5    = MUX_A(CM_FXCOMCLKSEL5, 5), /*!< Attach MCLK_IN to FLEXCOMM5. */
    kOSC32K_to_FLEXCOMM5     = MUX_A(CM_FXCOMCLKSEL5, 6), /*!< Attach OSC32K to FLEXCOMM5. */
    kNONE_to_FLEXCOMM5       = MUX_A(CM_FXCOMCLKSEL5, 7), /*!< Attach NONE to FLEXCOMM5. */

    kMAIN_CLK_to_FLEXCOMM6      = MUX_A(CM_FXCOMCLKSEL6, 0), /*!< Attach MAIN_CLK to FLEXCOMM6. */
    kMAIN_CLK_FRG6_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 1) | MUX_B(CM_FRGCLKSEL6, 0, 0),    /*!< Attach Main clock
                                                                                                 to FlexComm6. */
    kPLL_CLK_DIV_FRG6_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 1) | MUX_B(CM_FRGCLKSEL6, 1, 0), /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm6. */
    kFRO_HF_DIV_FRG6_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 1) | MUX_B(CM_FRGCLKSEL6, 2, 0),  /*!< Attach FRO HF DIV
                                                                                                 FRG to FlexComm6. */
    kFRO12M_to_FLEXCOMM6     = MUX_A(CM_FXCOMCLKSEL6, 2), /*!< Attach FRO12M to FLEXCOMM6. */
    kFRO_HF_DIV_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 3), /*!< Attach FRO_HF_DIV to FLEXCOMM6. */
    kFRO1M_to_FLEXCOMM6      = MUX_A(CM_FXCOMCLKSEL6, 4), /*!< Attach FRO1M to FLEXCOMM6. */
    kMCLK_IN_to_FLEXCOMM6    = MUX_A(CM_FXCOMCLKSEL6, 5), /*!< Attach MCLK_IN to FLEXCOMM6. */
    kOSC32K_to_FLEXCOMM6     = MUX_A(CM_FXCOMCLKSEL6, 6), /*!< Attach OSC32K to FLEXCOMM6. */
    kNONE_to_FLEXCOMM6       = MUX_A(CM_FXCOMCLKSEL6, 7), /*!< Attach NONE to FLEXCOMM6. */

    kMAIN_CLK_to_FLEXCOMM7      = MUX_A(CM_FXCOMCLKSEL7, 0), /*!< Attach MAIN_CLK to FLEXCOMM7. */
    kMAIN_CLK_FRG7_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 1) | MUX_B(CM_FRGCLKSEL7, 0, 0),    /*!< Attach Main clock
                                                                                                 to FlexComm7. */
    kPLL_CLK_DIV_FRG7_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 1) | MUX_B(CM_FRGCLKSEL7, 1, 0), /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm7. */
    kFRO_HF_DIV_FRG7_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 1) | MUX_B(CM_FRGCLKSEL7, 2, 0),  /*!< Attach PLL clock
                                                                                             DIV Frg to FlexComm7. */
    kFRO12M_to_FLEXCOMM7     = MUX_A(CM_FXCOMCLKSEL7, 2), /*!< Attach FRO12M to FLEXCOMM7. */
    kFRO_HF_DIV_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 3), /*!< Attach FRO_HF_DIV to FLEXCOMM7. */
    kFRO1M_to_FLEXCOMM7      = MUX_A(CM_FXCOMCLKSEL7, 4), /*!< Attach FRO1M to FLEXCOMM7. */
    kMCLK_IN_to_FLEXCOMM7    = MUX_A(CM_FXCOMCLKSEL7, 5), /*!< Attach MCLK_IN to FLEXCOMM7. */
    kOSC32K_to_FLEXCOMM7     = MUX_A(CM_FXCOMCLKSEL7, 6), /*!< Attach OSC32K to FLEXCOMM7. */
    kNONE_to_FLEXCOMM7       = MUX_A(CM_FXCOMCLKSEL7, 7), /*!< Attach NONE to FLEXCOMM7. */

    kMAIN_CLK_to_HSLSPI    = MUX_A(CM_HSLSPICLKSEL, 0), /*!< Attach MAIN_CLK to HSLSPI. */
    kPLL_CLK_DIV_to_HSLSPI = MUX_A(CM_HSLSPICLKSEL, 1), /*!< Attach PLL_CLK_DIV to HSLSPI. */
    kFRO12M_to_HSLSPI      = MUX_A(CM_HSLSPICLKSEL, 2), /*!< Attach FRO12M to HSLSPI. */
    kFRO_HF_DIV_to_HSLSPI  = MUX_A(CM_HSLSPICLKSEL, 3), /*!< Attach FRO_HF_DIV to HSLSPI. */
    kFRO1M_to_HSLSPI       = MUX_A(CM_HSLSPICLKSEL, 4), /*!< Attach FRO1M to HSLSPI. */
    kOSC32K_to_HSLSPI      = MUX_A(CM_HSLSPICLKSEL, 6), /*!< Attach OSC32K to HSLSPI. */
    kNONE_to_HSLSPI        = MUX_A(CM_HSLSPICLKSEL, 7), /*!< Attach NONE to HSLSPI. */

    kFRO_HF_to_MCLK = MUX_A(CM_MCLKCLKSEL, 0), /*!< Attach FRO_HF to MCLK. */
    kPLL0_to_MCLK   = MUX_A(CM_MCLKCLKSEL, 1), /*!< Attach PLL0 to MCLK. */
    kNONE_to_MCLK   = MUX_A(CM_MCLKCLKSEL, 7), /*!< Attach NONE to MCLK. */

    kMAIN_CLK_to_SCT = MUX_A(CM_SCTCLKSEL, 0), /*!< Attach MAIN_CLK to SCT. */
    kPLL0_to_SCT     = MUX_A(CM_SCTCLKSEL, 1), /*!< Attach PLL0 to SCT. */
    kEXT_CLK_to_SCT  = MUX_A(CM_SCTCLKSEL, 2), /*!< Attach EXT_CLK to SCT. */
    kFRO_HF_to_SCT   = MUX_A(CM_SCTCLKSEL, 3), /*!< Attach FRO_HF to SCT. */
    kPLL1_to_SCT     = MUX_A(CM_SCTCLKSEL, 4), /*!< Attach PLL1 to SCT. */
    kMCLK_IN_to_SCT  = MUX_A(CM_SCTCLKSEL, 5), /*!< Attach MCLK_IN to SCT. */
    kNONE_to_SCT     = MUX_A(CM_SCTCLKSEL, 7), /*!< Attach NONE to SCT. */

    kMAIN_CLK_to_DAC0 = MUX_A(CM_DAC0CLKSEL, 0), /*!< Attach MAIN_CLK to DAC0. */
    kPLL0_to_DAC0     = MUX_A(CM_DAC0CLKSEL, 1), /*!< Attach PLL0 to DAC0. */
    kFRO_HF_to_DAC0   = MUX_A(CM_DAC0CLKSEL, 3), /*!< Attach FRO_HF to DAC0. */
    kFRO12M_to_DAC0   = MUX_A(CM_DAC0CLKSEL, 4), /*!< Attach FRO12M to DAC0. */
    kPLL1_to_DAC0     = MUX_A(CM_DAC0CLKSEL, 5), /*!< Attach PLL1 to DAC0. */
    kFRO1M_to_DAC0    = MUX_A(CM_DAC0CLKSEL, 6), /*!< Attach FRO1M to DAC0. */
    kNONE_to_DAC0     = MUX_A(CM_DAC0CLKSEL, 7), /*!< Attach NONE to DAC0. */

    kMAIN_CLK_to_DAC1 = MUX_A(CM_DAC1CLKSEL, 0), /*!< Attach MAIN_CLK to DAC1. */
    kPLL0_to_DAC1     = MUX_A(CM_DAC1CLKSEL, 1), /*!< Attach PLL0 to DAC1. */
    kFRO_HF_to_DAC1   = MUX_A(CM_DAC1CLKSEL, 3), /*!< Attach FRO_HF to DAC1. */
    kFRO12M_to_DAC1   = MUX_A(CM_DAC1CLKSEL, 4), /*!< Attach FRO12M to DAC1. */
    kPLL1_to_DAC1     = MUX_A(CM_DAC1CLKSEL, 5), /*!< Attach PLL1 to DAC1. */
    kFRO1M_to_DAC1    = MUX_A(CM_DAC1CLKSEL, 6), /*!< Attach FRO1M to DAC1. */
    kNONE_to_DAC1     = MUX_A(CM_DAC1CLKSEL, 7), /*!< Attach NONE to DAC1. */

    kMAIN_CLK_to_DAC2 = MUX_A(CM_DAC2CLKSEL, 0), /*!< Attach MAIN_CLK to DAC2. */
    kPLL0_to_DAC2     = MUX_A(CM_DAC2CLKSEL, 1), /*!< Attach PLL0 to DAC2. */
    kFRO_HF_to_DAC2   = MUX_A(CM_DAC2CLKSEL, 3), /*!< Attach FRO_HF to DAC2. */
    kFRO12M_to_DAC2   = MUX_A(CM_DAC2CLKSEL, 4), /*!< Attach FRO12M to DAC2. */
    kPLL1_to_DAC2     = MUX_A(CM_DAC2CLKSEL, 5), /*!< Attach PLL1 to DAC2. */
    kFRO1M_to_DAC2    = MUX_A(CM_DAC2CLKSEL, 6), /*!< Attach FRO1M to DAC2. */
    kNONE_to_DAC2     = MUX_A(CM_DAC2CLKSEL, 7), /*!< Attach NONE to DAC2. */

    kMAIN_CLK_to_FLEXSPI = MUX_A(CM_FLEXSPICLKSEL, 0), /*!< Attach MAIN_CLK to FLEXSPI. */
    kPLL0_to_FLEXSPI     = MUX_A(CM_FLEXSPICLKSEL, 1), /*!< Attach PLL0 to FLEXSPI. */
    kFRO_HF_to_FLEXSPI   = MUX_A(CM_FLEXSPICLKSEL, 3), /*!< Attach FRO_HF to FLEXSPI. */
    kPLL1_to_FLEXSPI     = MUX_A(CM_FLEXSPICLKSEL, 5), /*!< Attach PLL1 to FLEXSPI. */
    kNONE_to_FLEXSPI     = MUX_A(CM_FLEXSPICLKSEL, 7), /*!< Attach NONE to FLEXSPI. */

    kPLL0_to_PLLCLKDIV = MUX_A(CM_PLLCLKDIVSEL, 0), /*!< Attach PLL0 to PLLCLKDIV. */
    kPLL1_to_PLLCLKDIV = MUX_A(CM_PLLCLKDIVSEL, 1), /*!< Attach PLL1 to PLLCLKDIV. */
    kNONE_to_PLLCLKDIV = MUX_A(CM_PLLCLKDIVSEL, 7), /*!< Attach NONE to PLLCLKDIV. */

    kMAIN_CLK_to_I3CFCLK   = MUX_A(CM_I3CFCLKSEL, 0), /*!< Attach MAIN_CLK to I3CFCLK. */
    kFRO_HF_DIV_to_I3CFCLK = MUX_A(CM_I3CFCLKSEL, 1), /*!< Attach FRO_HF_DIV to I3CFCLK. */
    kNONE_to_I3CFCLK       = MUX_A(CM_I3CFCLKSEL, 7), /*!< Attach NONE to I3CFCLK. */

    kI3CFCLKSEL_to_I3CFCLKSTC = MUX_A(CM_I3CFCLKSTCSEL, 0), /*!< Attach I3CFCLKSEL to I3CFCLKSTC. */
    kFRO1M_to_I3CFCLKSTC      = MUX_A(CM_I3CFCLKSTCSEL, 1), /*!< Attach FRO1M to I3CFCLKSTC. */
    kNONE_to_I3CFCLKSTC       = MUX_A(CM_I3CFCLKSTCSEL, 7), /*!< Attach NONE to I3CFCLKSTC. */

    kMAIN_CLK_to_DMIC = MUX_A(CM_DMICFCLKSEL, 0), /*!< Attach MAIN_CLK to DMIC. */
    kPLL0_to_DMIC     = MUX_A(CM_DMICFCLKSEL, 1), /*!< Attach PLL0 to DMIC. */
    kEXT_CLK_to_DMIC  = MUX_A(CM_DMICFCLKSEL, 2), /*!< Attach EXT_CLK to DMIC. */
    kFRO_HF_to_DMIC   = MUX_A(CM_DMICFCLKSEL, 3), /*!< Attach FRO_HF to DMIC. */
    kPLL1_to_DMIC     = MUX_A(CM_DMICFCLKSEL, 2), /*!< Attach PLL1 to DMIC. */
    kMCLK_IN_to_DMIC  = MUX_A(CM_DMICFCLKSEL, 5), /*!< Attach MCLK_IN to DMIC. */
    kNONE_to_DMIC     = MUX_A(CM_DMICFCLKSEL, 7), /*!< Attach NONE to DMIC. */

    kFRO32K_to_FCOSC32K  = MUX_A(CM_FC32KCLKSEL, 0),     /*!< Attach FRO32K to FCOSC32K. */
    kXTAL32K_to_FCOSC32K = MUX_A(CM_FC32KCLKSEL, 1),     /*!< Attach XTAL32K to FCOSC32K. */
    kFRO32K_to_OSC32K    = MUX_A(CM_RTCOSC32KCLKSEL, 0), /*!< Attach FRO32K to OSC32K. */
    kXTAL32K_to_OSC32K   = MUX_A(CM_RTCOSC32KCLKSEL, 1), /*!< Attach XTAL32K to OSC32K. */
    kFRO32K_to_FC32K     = MUX_A(CM_FC32KCLKSEL, 0),     /*!< Attach FRO32K to FC32K. */
    kXTAL32K_to_FC32K    = MUX_A(CM_FC32KCLKSEL, 1),     /*!< Attach XTAL32K to FC32K. */

    kFRO32K_to_OSTIMER  = MUX_A(CM_OSTIMERCLKSEL, 0), /*!< Attach FRO32K to OSTIMER. */
    kOSC32K_to_OSTIMER  = MUX_A(CM_OSTIMERCLKSEL, 1), /*!< Attach OSC32K to OSTIMER. */
    kFRO1M_to_OSTIMER   = MUX_A(CM_OSTIMERCLKSEL, 2), /*!< Attach FRO1M to OSTIMER. */
    kAHB_CLK_to_OSTIMER = MUX_A(CM_OSTIMERCLKSEL, 3), /*!< Attach AHB_CLK to OSTIMER. */

    kNONE_to_NONE = (int)0x80000000U, /*!< Attach NONE to NONE. */

} clock_attach_id_t;

/*  Clock dividers */
typedef enum _clock_div_name
{
    kCLOCK_DivSystickClk  = (0),                   /*!< Systick Clock Divider. */
    kCLOCK_DivArmTrClkDiv = ((0x308 - 0x300) / 4), /*!< Trace Clock Divider. */
    kCLOCK_DivCanClk      = ((0x30C - 0x300) / 4), /*!< Can Clock Divider. */
    kCLOCK_DivFlexFrg0    = ((0x320 - 0x300) / 4), /*!< FRGCTRL0 register. */
    kCLOCK_DivFlexFrg1    = ((0x324 - 0x300) / 4), /*!< FRGCTRL1 register. */
    kCLOCK_DivFlexFrg2    = ((0x328 - 0x300) / 4), /*!< FRGCTRL2 register. */
    kCLOCK_DivFlexFrg3    = ((0x32C - 0x300) / 4), /*!< FRGCTRL3 register. */
    kCLOCK_DivFlexFrg4    = ((0x330 - 0x300) / 4), /*!< FRGCTRL4 register. */
    kCLOCK_DivFlexFrg5    = ((0x334 - 0x300) / 4), /*!< FRGCTRL5 register. */
    kCLOCK_DivFlexFrg6    = ((0x338 - 0x300) / 4), /*!< FRGCTRL6 register. */
    kCLOCK_DivFlexFrg7    = ((0x33C - 0x300) / 4), /*!< FRGCTRL7 register. */
    kCLOCK_DivAhbClk      = ((0x380 - 0x300) / 4), /*!< Ahb Clock Divider. */
    kCLOCK_DivClkOut      = ((0x384 - 0x300) / 4), /*!< Clk Out Divider. */
    kCLOCK_DivFrohfClk    = ((0x388 - 0x300) / 4), /*!< Frohf Divider. */
    kCLOCK_DivWdtClk      = ((0x38C - 0x300) / 4), /*!< Wdt Clock Divider. */
    kCLOCK_DivAdc0Clk     = ((0x394 - 0x300) / 4), /*!< Adc0 Clock Divider. */
    kCLOCK_DivUsb0Clk     = ((0x398 - 0x300) / 4), /*!< Usb0 Clock Divider. */
    kCLOCK_DivMclk        = ((0x3AC - 0x300) / 4), /*!< Mclk Divider. */
    kCLOCK_DivSctClk      = ((0x3B4 - 0x300) / 4), /*!< Sct Clock Divider. */
    kCLOCK_DivPllClk      = ((0x3C4 - 0x300) / 4), /*!< Pll0 Clock Divider. */
    kCLOCK_DivCtimer0Clk  = ((0x3D0 - 0x300) / 4), /*!< Ctimer0 Clock Divider. */
    kCLOCK_DivCtimer1Clk  = ((0x3D4 - 0x300) / 4), /*!< Ctimer1 Clock Divider. */
    kCLOCK_DivCtimer2Clk  = ((0x3D8 - 0x300) / 4), /*!< Ctimer2 Clock Divider. */
    kCLOCK_DivCtimer3Clk  = ((0x3DC - 0x300) / 4), /*!< Ctimer3 Clock Divider. */
    kCLOCK_DivCtimer4Clk  = ((0x3E0 - 0x300) / 4), /*!< Ctimer4 Clock Divider. */
    kCLOCK_DivAdc1Clk     = ((0x468 - 0x300) / 4), /*!< Adc1 Clock Divider. */
    kCLOCK_DivDac0Clk     = ((0x494 - 0x300) / 4), /*!< Dac0 Clock Divider. */
    kCLOCK_DivDac1Clk     = ((0x49C - 0x300) / 4), /*!< Dac1 Clock Divider. */
    kCLOCK_DivDac2Clk     = ((0x4A4 - 0x300) / 4), /*!< Dac2 Clock Divider. */
    kCLOCK_DivFlexSpiClk  = ((0x4AC - 0x300) / 4), /*!< Flex Spi Clock Divider. */
    kCLOCK_DivI3cFclkStc  = ((0x538 - 0x300) / 4), /*!< I3c Fclk Stc Divider. */
    kCLOCK_DivI3cFclkS    = ((0x53C - 0x300) / 4), /*!< I3c Fclk S Divider. */
    kCLOCK_DivI3cFclk     = ((0x540 - 0x300) / 4), /*!< I3c Fclk Divider. */
    kCLOCK_DivDmicClk     = ((0x54C - 0x300) / 4), /*!< Dmic Clock Divider. */
    kCLOCK_DivFlexcom0Clk = ((0x850 - 0x300) / 4), /*!< Flexcom0 Clock Divider. */
    kCLOCK_DivFlexcom1Clk = ((0x854 - 0x300) / 4), /*!< Flexcom1 Clock Divider. */
    kCLOCK_DivFlexcom2Clk = ((0x858 - 0x300) / 4), /*!< Flexcom2 Clock Divider. */
    kCLOCK_DivFlexcom3Clk = ((0x85C - 0x300) / 4), /*!< Flexcom3 Clock Divider. */
    kCLOCK_DivFlexcom4Clk = ((0x860 - 0x300) / 4), /*!< Flexcom4 Clock Divider. */
    kCLOCK_DivFlexcom5Clk = ((0x864 - 0x300) / 4), /*!< Flexcom5 Clock Divider. */
    kCLOCK_DivFlexcom6Clk = ((0x868 - 0x300) / 4), /*!< Flexcom6 Clock Divider. */
    kCLOCK_DivFlexcom7Clk = ((0x86C - 0x300) / 4), /*!< Flexcom7 Clock Divider. */
} clock_div_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/**
 * @brief Enable the clock for specific IP.
 * @param clk : Clock to be enabled.
 * @return  Nothing
 */
static inline void CLOCK_EnableClock(clock_ip_name_t clk)
{
    uint32_t index               = CLK_GATE_ABSTRACT_REG_OFFSET(clk);
    SYSCON->AHBCLKCTRLSET[index] = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
}
/**
 * @brief Disable the clock for specific IP.
 * @param clk : Clock to be Disabled.
 * @return  Nothing
 */
static inline void CLOCK_DisableClock(clock_ip_name_t clk)
{
    uint32_t index               = CLK_GATE_ABSTRACT_REG_OFFSET(clk);
    SYSCON->AHBCLKCTRLCLR[index] = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
}
/**
 * @brief   Initialize the Core clock to given frequency (12, 48 or 96 MHz).
 * Turns on FRO and uses default CCO, if freq is 12000000, then high speed output is off, else high speed output is
 * enabled.
 * @param   iFreq   : Desired frequency (must be one of CLK_FRO_12MHZ or CLK_FRO_48MHZ or CLK_FRO_96MHZ)
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupFROClocking(uint32_t iFreq);
/**
 * @brief	Set the flash wait states for the input freuqency.
 * @param	system_freq_hz	: Input frequency
 * @return	Nothing
 */
void CLOCK_SetFLASHAccessCyclesForFreq(uint32_t system_freq_hz);
/**
 * @brief   Initialize the external osc clock to given frequency.
 * @param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupExtClocking(uint32_t iFreq);
/**
 * @brief   Initialize the I2S MCLK clock to given frequency.
 * @param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupI2SMClkClocking(uint32_t iFreq);
/**
 * @brief   Initialize the PLU CLKIN clock to given frequency.
 * @param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupPLUClkInClocking(uint32_t iFreq);
/**
 * @brief   Configure the clock selection muxes.
 * @param   connection  : Clock to be configured.
 * @return  Nothing
 */
void CLOCK_AttachClk(clock_attach_id_t connection);
/**
 * @brief   Get the actual clock attach id.
 * This fuction uses the offset in input attach id, then it reads the actual source value in
 * the register and combine the offset to obtain an actual attach id.
 * @param   attachId  : Clock attach id to get.
 * @return  Clock source value.
 */
clock_attach_id_t CLOCK_GetClockAttachId(clock_attach_id_t attachId);
/**
 * @brief   Setup peripheral clock dividers.
 * @param   div_name    : Clock divider name
 * @param divided_by_value: Value to be divided
 * @param reset :  Whether to reset the divider counter.
 * @return  Nothing
 */
void CLOCK_SetClkDiv(clock_div_name_t div_name, uint32_t divided_by_value, bool reset);
/*! @brief  Return Frequency of selected clock
 *  @return Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);
/*! @brief  Return Frequency of FRO 12MHz
 *  @return Frequency of FRO 12MHz
 */
uint32_t CLOCK_GetFro12MFreq(void);
/*! @brief  Return Frequency of FRO 1MHz
 *  @return Frequency of FRO 1MHz
 */
uint32_t CLOCK_GetFro1MFreq(void);
/*! @brief  Return Frequency of ClockOut
 *  @return Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void);
/*! @brief  Return Frequency of Can Clock
 *  @return Frequency of Can.
 */
uint32_t CLOCK_GetMCanClkFreq(void);
/*! @brief  Return Frequency of Adc Clock
 *  @return Frequency of Adc.
 */
uint32_t CLOCK_GetAdcClkFreq(uint32_t id);
/*! @brief  Return Frequency of Usb0 Clock
 *  @return Frequency of Usb0 Clock.
 */
uint32_t CLOCK_GetUsb0ClkFreq(void);
/*! @brief  Return Frequency of MClk Clock
 *  @return Frequency of MClk Clock.
 */
uint32_t CLOCK_GetMclkClkFreq(void);
/*! @brief  Return Frequency of SCTimer Clock
 *  @return Frequency of SCTimer Clock.
 */
uint32_t CLOCK_GetSctClkFreq(void);
/*! @brief  Return Frequency of External Clock
 *  @return Frequency of External Clock. If no external clock is used returns 0.
 */
uint32_t CLOCK_GetExtClkFreq(void);
/*! @brief  Return Frequency of Watchdog
 *  @return Frequency of Watchdog
 */
uint32_t CLOCK_GetWdtClkFreq(void);
/*! @brief  Return Frequency of High-Freq output of FRO
 *  @return Frequency of High-Freq output of FRO
 */
uint32_t CLOCK_GetFroHfFreq(void);
/*! @brief  Return Frequency of PLL
 *  @return Frequency of PLL
 */
uint32_t CLOCK_GetPll0OutFreq(void);
/*! @brief  Return Frequency of USB PLL
 *  @return Frequency of PLL
 */
uint32_t CLOCK_GetPll1OutFreq(void);
/*! @brief  Return Frequency of PLL_CLK_DIV
 *  @return Frequency of PLL_CLK_DIV
 */
uint32_t CLOCK_GetPllClkDivFreq(void);
/*! @brief  Return Frequency of 32kHz osc
 *  @return Frequency of 32kHz osc
 */
uint32_t CLOCK_GetOsc32KFreq(void);
/*! @brief  Return Frequency of Flexcomm 32kHz osc
 *  @return Frequency of Flexcomm 32kHz osc
 */
uint32_t CLOCK_GetFC32KFreq(void);
/*! @brief  Return Frequency of Core System
 *  @return Frequency of Core System
 */
uint32_t CLOCK_GetCoreSysClkFreq(void);
/*! @brief  Return Frequency of I2S MCLK Clock
 *  @return Frequency of I2S MCLK Clock
 */
uint32_t CLOCK_GetI2SMClkFreq(void);
/*! @brief  Return Frequency of FRG Clock
 *  @return Frequency of FRG Clock
 */
uint32_t CLOCK_GetFrgFreq(uint32_t id);
/*! @brief  Return Frequency of FlexComm Clock
 *  @return Frequency of FlexComm Clock
 */
uint32_t CLOCK_GetFlexCommClkFreq(uint32_t id);
/*! @brief  Return Frequency of High speed SPI Clock
 *  @return Frequency of High speed SPI Clock
 */
uint32_t CLOCK_GetHsLspiClkFreq(void);
/*! @brief  Return Frequency of CTimer functional Clock
 *  @return Frequency of CTimer functional Clock
 */
uint32_t CLOCK_GetCTimerClkFreq(uint32_t id);
/*! @brief  Return Frequency of SystickClock
 *  @return Frequency of Systick Clock
 */
uint32_t CLOCK_GetSystickClkFreq(void);

/*! @brief  Return Frequency of FlexSPI
 *  @return Frequency of FlexSPI Clock
 */
uint32_t CLOCK_GetFlexSpiClkFreq(void);

/*! @brief  Return Frequency of DMIC
 *  @return Frequency of DMIC Clock
 */
uint32_t CLOCK_GetDmicClkFreq(void);

/*! @brief  Return Frequency of DAC Clock
 *  @return Frequency of DAC Clock
 */
uint32_t CLOCK_GetDacClkFreq(uint32_t id);
/*! @brief  Return Frequency of I3C function slow TC Clock
 *  @return Frequency of I3C function slow TC Clock
 */
uint32_t CLOCK_GetI3cSTCClkFreq(void);
/*! @brief  Return Frequency of I3C function slow Clock
 *  @return Frequency of I3C function slow Clock
 */
uint32_t CLOCK_GetI3cSClkFreq(void);
/*! @brief  Return Frequency of I3C function Clock
 *  @return Frequency of I3C function Clock
 */
uint32_t CLOCK_GetI3cClkFreq(void);

/*! @brief    Return  PLL0 input clock rate
 *  @return    PLL0 input clock rate
 */
uint32_t CLOCK_GetPLL0InClockRate(void);

/*! @brief    Return  PLL1 input clock rate
 *  @return    PLL1 input clock rate
 */
uint32_t CLOCK_GetPLL1InClockRate(void);

/*! @brief    Return  PLL0 output clock rate
 *  @param    recompute   : Forces a PLL rate recomputation if true
 *  @return    PLL0 output clock rate
 *  @note The PLL rate is cached in the driver in a variable as
 *  the rate computation function can take some time to perform. It
 *  is recommended to use 'false' with the 'recompute' parameter.
 */
uint32_t CLOCK_GetPLL0OutClockRate(bool recompute);

/*! @brief    Return  PLL1 output clock rate
 *  @param    recompute   : Forces a PLL rate recomputation if true
 *  @return    PLL1 output clock rate
 *  @note The PLL rate is cached in the driver in a variable as
 *  the rate computation function can take some time to perform. It
 *  is recommended to use 'false' with the 'recompute' parameter.
 */
uint32_t CLOCK_GetPLL1OutClockRate(bool recompute);

/*! @brief    Enables and disables PLL0 bypass mode
 *  @brief    bypass  : true to bypass PLL0 (PLL0 output = PLL0 input, false to disable bypass
 *  @return   PLL0 output clock rate
 */
__STATIC_INLINE void CLOCK_SetBypassPLL0(bool bypass)
{
    if (bypass)
    {
        SYSCON->PLL0CTRL |= (1UL << SYSCON_PLL0CTRL_BYPASSPLL_SHIFT);
    }
    else
    {
        SYSCON->PLL0CTRL &= ~(1UL << SYSCON_PLL0CTRL_BYPASSPLL_SHIFT);
    }
}

/*! @brief    Enables and disables PLL1 bypass mode
 *  @brief    bypass  : true to bypass PLL1 (PLL1 output = PLL1 input, false to disable bypass
 *  @return   PLL1 output clock rate
 */
__STATIC_INLINE void CLOCK_SetBypassPLL1(bool bypass)
{
    if (bypass)
    {
        SYSCON->PLL1CTRL |= (1UL << SYSCON_PLL1CTRL_BYPASSPLL_SHIFT);
    }
    else
    {
        SYSCON->PLL1CTRL &= ~(1UL << SYSCON_PLL1CTRL_BYPASSPLL_SHIFT);
    }
}

/*! @brief    Check if PLL is locked or not
 *  @return   true if the PLL is locked, false if not locked
 */
__STATIC_INLINE bool CLOCK_IsPLL0Locked(void)
{
    return (bool)((SYSCON->PLL0STAT & SYSCON_PLL0STAT_LOCK_MASK) != 0UL);
}

/*! @brief	Check if PLL1 is locked or not
 *  @return	true if the PLL1 is locked, false if not locked
 */
__STATIC_INLINE bool CLOCK_IsPLL1Locked(void)
{
    return (bool)((SYSCON->PLL1STAT & SYSCON_PLL1STAT_LOCK_MASK) != 0UL);
}

/*! @brief Store the current PLL0 rate
 *  @param    rate: Current rate of the PLL0
 *  @return   Nothing
 **/
void CLOCK_SetStoredPLL0ClockRate(uint32_t rate);

/*! @brief PLL configuration structure flags for 'flags' field
 * These flags control how the PLL configuration function sets up the PLL setup structure.<br>
 *
 * When the PLL_CONFIGFLAG_USEINRATE flag is selected, the 'InputRate' field in the
 * configuration structure must be assigned with the expected PLL frequency. If the
 * PLL_CONFIGFLAG_USEINRATE is not used, 'InputRate' is ignored in the configuration
 * function and the driver will determine the PLL rate from the currently selected
 * PLL source. This flag might be used to configure the PLL input clock more accurately
 * when using the WDT oscillator or a more dyanmic CLKIN source.<br>
 *
 * When the PLL_CONFIGFLAG_FORCENOFRACT flag is selected, the PLL hardware for the
 * automatic bandwidth selection, Spread Spectrum (SS) support, and fractional M-divider
 * are not used.<br>
 */
#define PLL_CONFIGFLAG_USEINRATE    (1U << 0U) /*!< Flag to use InputRate in PLL configuration structure for setup */
#define PLL_CONFIGFLAG_FORCENOFRACT (1U << 2U)
/*!< Force non-fractional output mode, PLL output will not use the fractional, automatic bandwidth, or SS hardware */

/*! @brief PLL Spread Spectrum (SS) Programmable modulation frequency
 * See (MF) field in the PLL0SSCG1 register in the UM.
 */
typedef enum _ss_progmodfm
{
    kSS_MF_512 = (0 << 20), /*!< Nss = 512 (fm ? 3.9 - 7.8 kHz) */
    kSS_MF_384 = (1 << 20), /*!< Nss ?= 384 (fm ? 5.2 - 10.4 kHz) */
    kSS_MF_256 = (2 << 20), /*!< Nss = 256 (fm ? 7.8 - 15.6 kHz) */
    kSS_MF_128 = (3 << 20), /*!< Nss = 128 (fm ? 15.6 - 31.3 kHz) */
    kSS_MF_64  = (4 << 20), /*!< Nss = 64 (fm ? 32.3 - 64.5 kHz) */
    kSS_MF_32  = (5 << 20), /*!< Nss = 32 (fm ? 62.5- 125 kHz) */
    kSS_MF_24  = (6 << 20), /*!< Nss ?= 24 (fm ? 83.3- 166.6 kHz) */
    kSS_MF_16  = (7 << 20)  /*!< Nss = 16 (fm ? 125- 250 kHz) */
} ss_progmodfm_t;

/*! @brief PLL Spread Spectrum (SS) Programmable frequency modulation depth
 * See (MR) field in the PLL0SSCG1 register in the UM.
 */
typedef enum _ss_progmoddp
{
    kSS_MR_K0   = (0 << 23), /*!< k = 0 (no spread spectrum) */
    kSS_MR_K1   = (1 << 23), /*!< k = 1 */
    kSS_MR_K1_5 = (2 << 23), /*!< k = 1.5 */
    kSS_MR_K2   = (3 << 23), /*!< k = 2 */
    kSS_MR_K3   = (4 << 23), /*!< k = 3 */
    kSS_MR_K4   = (5 << 23), /*!< k = 4 */
    kSS_MR_K6   = (6 << 23), /*!< k = 6 */
    kSS_MR_K8   = (7 << 23)  /*!< k = 8 */
} ss_progmoddp_t;

/*! @brief PLL Spread Spectrum (SS) Modulation waveform control
 * See (MC) field in the PLL0SSCG1 register in the UM.<br>
 * Compensation for low pass filtering of the PLL to get a triangular
 * modulation at the output of the PLL, giving a flat frequency spectrum.
 */
typedef enum _ss_modwvctrl
{
    kSS_MC_NOC  = (0 << 26), /*!< no compensation */
    kSS_MC_RECC = (2 << 26), /*!< recommended setting */
    kSS_MC_MAXC = (3 << 26), /*!< max. compensation */
} ss_modwvctrl_t;

/*! @brief PLL configuration structure
 *
 * This structure can be used to configure the settings for a PLL
 * setup structure. Fill in the desired configuration for the PLL
 * and call the PLL setup function to fill in a PLL setup structure.
 */
typedef struct _pll_config
{
    uint32_t desiredRate; /*!< Desired PLL rate in Hz */
    uint32_t inputRate;   /*!< PLL input clock in Hz, only used if PLL_CONFIGFLAG_USEINRATE flag is set */
    uint32_t flags;       /*!< PLL configuration flags, Or'ed value of PLL_CONFIGFLAG_* definitions */
    ss_progmodfm_t ss_mf; /*!< SS Programmable modulation frequency, only applicable when not using
                             PLL_CONFIGFLAG_FORCENOFRACT flag */
    ss_progmoddp_t ss_mr; /*!< SS Programmable frequency modulation depth, only applicable when not using
                             PLL_CONFIGFLAG_FORCENOFRACT flag */
    ss_modwvctrl_t
        ss_mc; /*!< SS Modulation waveform control, only applicable when not using PLL_CONFIGFLAG_FORCENOFRACT flag */
    bool mfDither; /*!< false for fixed modulation frequency or true for dithering, only applicable when not using
                      PLL_CONFIGFLAG_FORCENOFRACT flag */

} pll_config_t;

/*! @brief PLL setup structure flags for 'flags' field
 * These flags control how the PLL setup function sets up the PLL
 */
#define PLL_SETUPFLAG_POWERUP         (1U << 0U) /*!< Setup will power on the PLL after setup */
#define PLL_SETUPFLAG_WAITLOCK        (1U << 1U) /*!< Setup will wait for PLL lock, implies the PLL will be pwoered on */
#define PLL_SETUPFLAG_ADGVOLT         (1U << 2U) /*!< Optimize system voltage for the new PLL rate */
#define PLL_SETUPFLAG_USEFEEDBACKDIV2 (1U << 3U) /*!< Use feedback divider by 2 in divider path */

/*! @brief PLL0 setup structure
 * This structure can be used to pre-build a PLL setup configuration
 * at run-time and quickly set the PLL to the configuration. It can be
 * populated with the PLL setup function. If powering up or waiting
 * for PLL lock, the PLL input clock source should be configured prior
 * to PLL setup.
 */
typedef struct _pll_setup
{
    uint32_t pllctrl;    /*!< PLL control register PLL0CTRL */
    uint32_t pllndec;    /*!< PLL NDEC register PLL0NDEC */
    uint32_t pllpdec;    /*!< PLL PDEC register PLL0PDEC */
    uint32_t pllmdec;    /*!< PLL MDEC registers PLL0PDEC */
    uint32_t pllsscg[2]; /*!< PLL SSCTL registers PLL0SSCG*/
    uint32_t pllRate;    /*!< Acutal PLL rate */
    uint32_t flags;      /*!< PLL setup flags, Or'ed value of PLL_SETUPFLAG_* definitions */
} pll_setup_t;

/*! @brief PLL status definitions
 */
typedef enum _pll_error
{
    kStatus_PLL_Success         = MAKE_STATUS(kStatusGroup_Generic, 0), /*!< PLL operation was successful */
    kStatus_PLL_OutputTooLow    = MAKE_STATUS(kStatusGroup_Generic, 1), /*!< PLL output rate request was too low */
    kStatus_PLL_OutputTooHigh   = MAKE_STATUS(kStatusGroup_Generic, 2), /*!< PLL output rate request was too high */
    kStatus_PLL_InputTooLow     = MAKE_STATUS(kStatusGroup_Generic, 3), /*!< PLL input rate is too low */
    kStatus_PLL_InputTooHigh    = MAKE_STATUS(kStatusGroup_Generic, 4), /*!< PLL input rate is too high */
    kStatus_PLL_OutsideIntLimit = MAKE_STATUS(kStatusGroup_Generic, 5), /*!< Requested output rate isn't possible */
    kStatus_PLL_CCOTooLow       = MAKE_STATUS(kStatusGroup_Generic, 6), /*!< Requested CCO rate isn't possible */
    kStatus_PLL_CCOTooHigh      = MAKE_STATUS(kStatusGroup_Generic, 7)  /*!< Requested CCO rate isn't possible */
} pll_error_t;

/*! @brief USB FS clock source definition. */
typedef enum _clock_usbfs_src
{
    kCLOCK_UsbfsSrcFro       = (uint32_t)kCLOCK_FroHf,      /*!< Use FRO 96 MHz. */
    kCLOCK_UsbfsSrcPll0      = (uint32_t)kCLOCK_Pll0Out,    /*!< Use PLL0 output. */
    kCLOCK_UsbfsSrcMainClock = (uint32_t)kCLOCK_CoreSysClk, /*!< Use Main clock.    */
    kCLOCK_UsbfsSrcPll1      = (uint32_t)kCLOCK_Pll1Out,    /*!< Use PLL1 clock.    */

    kCLOCK_UsbfsSrcNone =
        SYSCON_USB0CLKSEL_SEL(7) /*!<this may be selected in order to reduce power when no output is needed. */
} clock_usbfs_src_t;

/*! @brief Source of the USB HS PHY. */
typedef enum _clock_usb_phy_src
{
    kCLOCK_UsbPhySrcExt = 0U, /*!< Use external crystal. */
} clock_usb_phy_src_t;

/*! @brief    Return PLL0 output clock rate from setup structure
 *  @param    pSetup : Pointer to a PLL setup structure
 *  @return   System PLL output clock rate the setup structure will generate
 */
uint32_t CLOCK_GetPLL0OutFromSetup(pll_setup_t *pSetup);

/*! @brief    Return PLL1 output clock rate from setup structure
 *  @param    pSetup : Pointer to a PLL setup structure
 *  @return   PLL0 output clock rate the setup structure will generate
 */
uint32_t CLOCK_GetPLL1OutFromSetup(pll_setup_t *pSetup);

/*! @brief    Set PLL0 output based on the passed PLL setup data
 *  @param    pControl    : Pointer to populated PLL control structure to generate setup with
 *  @param    pSetup      : Pointer to PLL setup structure to be filled
 *  @return   PLL_ERROR_SUCCESS on success, or PLL setup error code
 *  @note Actual frequency for setup may vary from the desired frequency based on the
 *  accuracy of input clocks, rounding, non-fractional PLL mode, etc.
 */
pll_error_t CLOCK_SetupPLL0Data(pll_config_t *pControl, pll_setup_t *pSetup);

/*! @brief    Set PLL output from PLL setup structure (precise frequency)
 * @param pSetup  : Pointer to populated PLL setup structure
 * @param flagcfg : Flag configuration for PLL config structure
 * @return    PLL_ERROR_SUCCESS on success, or PLL setup error code
 * @note  This function will power off the PLL, setup the PLL with the
 * new setup data, and then optionally powerup the PLL, wait for PLL lock,
 * and adjust system voltages to the new PLL rate. The function will not
 * alter any source clocks (ie, main systen clock) that may use the PLL,
 * so these should be setup prior to and after exiting the function.
 */
pll_error_t CLOCK_SetupPLL0Prec(pll_setup_t *pSetup, uint32_t flagcfg);

/**
 * @brief Set PLL output from PLL setup structure (precise frequency)
 * @param pSetup  : Pointer to populated PLL setup structure
 * @return    kStatus_PLL_Success on success, or PLL setup error code
 * @note  This function will power off the PLL, setup the PLL with the
 * new setup data, and then optionally powerup the PLL, wait for PLL lock,
 * and adjust system voltages to the new PLL rate. The function will not
 * alter any source clocks (ie, main systen clock) that may use the PLL,
 * so these should be setup prior to and after exiting the function.
 */
pll_error_t CLOCK_SetPLL0Freq(const pll_setup_t *pSetup);

/**
 * @brief Set PLL output from PLL setup structure (precise frequency)
 * @param pSetup  : Pointer to populated PLL setup structure
 * @return    kStatus_PLL_Success on success, or PLL setup error code
 * @note  This function will power off the PLL, setup the PLL with the
 * new setup data, and then optionally powerup the PLL, wait for PLL lock,
 * and adjust system voltages to the new PLL rate. The function will not
 * alter any source clocks (ie, main systen clock) that may use the PLL,
 * so these should be setup prior to and after exiting the function.
 */
pll_error_t CLOCK_SetPLL1Freq(const pll_setup_t *pSetup);

/*! @brief    Set PLL0 output based on the multiplier and input frequency
 * @param multiply_by : multiplier
 * @param input_freq  : Clock input frequency of the PLL
 * @return    Nothing
 * @note  Unlike the Chip_Clock_SetupSystemPLLPrec() function, this
 * function does not disable or enable PLL power, wait for PLL lock,
 * or adjust system voltages. These must be done in the application.
 * The function will not alter any source clocks (ie, main systen clock)
 * that may use the PLL, so these should be setup prior to and after
 * exiting the function.
 */
void CLOCK_SetupPLL0Mult(uint32_t multiply_by, uint32_t input_freq);

/*! @brief Disable USB clock.
 *
 * Disable USB clock.
 */
static inline void CLOCK_DisableUsbDevicefs0Clock(clock_ip_name_t clk)
{
    CLOCK_DisableClock(clk);
}

/*! @brief Enable USB Device FS clock.
 * @param src : clock source
 * @param freq: clock frequency
 * Enable USB Device Full Speed clock.
 */
bool CLOCK_EnableUsbfs0DeviceClock(clock_usbfs_src_t src, uint32_t freq);

/*! @brief Enable USB HOST FS clock.
 * @param src : clock source
 * @param freq: clock frequency
 * Enable USB HOST Full Speed clock.
 */
bool CLOCK_EnableUsbfs0HostClock(clock_usbfs_src_t src, uint32_t freq);

/*! @brief Enable the OSTIMER 32k clock.
 *  @return  Nothing
 */
void CLOCK_EnableOstimer32kClock(void);

/**
 * @brief   Sets board-specific trim values for High Frequency crystal oscillator
 * @param   pi32_hfXtalIecLoadpF_x100 Load capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF becomes 120
 * @param   pi32_hfXtalPPcbParCappF_x100 PCB +ve parasitic capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF
 * becomes 120
 * @param   pi32_hfXtalNPcbParCappF_x100 PCB -ve parasitic capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF
 * becomes 120
 * @return  none
 * @note    Following default Values can be used:
 *          pi32_32MfXtalIecLoadpF_x100    Load capacitance, pF x 100 : 600
 *          pi32_32MfXtalPPcbParCappF_x100 PCB +ve parasitic capacitance, pF x 100 : 20
 *          pi32_32MfXtalNPcbParCappF_x100 PCB -ve parasitic capacitance, pF x 100 : 40
 */
void CLOCK_XtalHfCapabankTrim(int32_t pi32_hfXtalIecLoadpF_x100,
                              int32_t pi32_hfXtalPPcbParCappF_x100,
                              int32_t pi32_hfXtalNPcbParCappF_x100);
/**
 * @brief   Sets board-specific trim values for 32kHz XTAL
 * @param   pi32_32kfXtalIecLoadpF_x100 Load capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF becomes 120
 * @param   pi32_32kfXtalPPcbParCappF_x100 PCB +ve parasitic capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF
 becomes 120
 * @param   pi32_32kfXtalNPcbParCappF_x100 PCB -ve parasitic capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF
 becomes 120

 * @return  none
 * @note    Following default Values can be used:
 *          pi32_32kfXtalIecLoadpF_x100    Load capacitance, pF x 100 : 600
 *          pi32_32kfXtalPPcbParCappF_x100 PCB +ve parasitic capacitance, pF x 100 : 40
 *          pi32_32kfXtalNPcbParCappF_x100 PCB -ve parasitic capacitance, pF x 100 : 40
 */
void CLOCK_Xtal32khzCapabankTrim(int32_t pi32_32kfXtalIecLoadpF_x100,
                                 int32_t pi32_32kfXtalPPcbParCappF_x100,
                                 int32_t pi32_32kfXtalNPcbParCappF_x100);

/**
 * @brief   Initialize the trim value for FRO HF
 * @return  none
 */
void CLOCK_FroHfTrim(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
