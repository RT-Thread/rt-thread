/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2016 - 2017 , NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name ofcopyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_device_registers.h"
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/*!
 * @addtogroup clock
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CCM_TUPLE(reg, shift, mask, busyShift) ((((uint32_t)(&((CCM_Type *)0U)->reg)) & 0xFFU) | ((shift) << 8U) | ((((mask) >> (shift)) & 0x1FFFU) << 13U) | ((busyShift) << 26U))
#define CCM_TUPLE_REG(base, tuple)     (*((volatile uint32_t *)(((uint32_t)(base)) + ((tuple) & 0xFFU))))
#define CCM_TUPLE_SHIFT(tuple)         (((tuple) >> 8U) & 0x1FU)
#define CCM_TUPLE_MASK(tuple)          ((uint32_t)((((tuple) >> 13U) & 0x1FFFU) << ((((tuple) >> 8U) & 0x1FU))))
#define CCM_TUPLE_BUSY_SHIFT(tuple)    (((tuple) >> 26U) & 0x3FU)

#define CCM_NO_BUSY_WAIT (0x20U)

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

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.1.0. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/


/*! @brief External XTAL (24M OSC/SYSOSC) clock frequency.
 *
 * The XTAL (24M OSC/SYSOSC) clock frequency in Hz, when the clock is setup, use the
 * function CLOCK_SetXtalFreq to set the value in to clock driver. For example,
 * if XTAL is 24MHz,
 * @code
 * CLOCK_InitExternalClk(false); // Setup the 24M OSC/SYSOSC
 * CLOCK_SetXtalFreq(240000000); // Set the XTAL value to clock driver.
 * @endcode
 */
extern uint32_t g_xtalFreq;

/*! @brief External RTC XTAL (32K OSC) clock frequency.
 *
 * The RTC XTAL (32K OSC) clock frequency in Hz, when the clock is setup, use the
 * function CLOCK_SetRtcXtalFreq to set the value in to clock driver.
 */
extern uint32_t g_rtcXtalFreq;

/* For compatible with other platforms */
#define CLOCK_SetXtal0Freq CLOCK_SetXtalFreq
#define CLOCK_SetXtal32Freq CLOCK_SetRtcXtalFreq

 /*! @brief Clock ip name array for ADC. */
#define ADC_CLOCKS                                                   \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Adc1                                \
    }

/*! @brief Clock ip name array for ADC_5HC. */
#define ADC_5HC_CLOCKS                                               \
    {                                                                \
        kCLOCK_Adc_5hc                                               \
    }

/*! @brief Clock ip name array for ECSPI. */
#define ECSPI_CLOCKS                                                 \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Ecspi1, kCLOCK_Ecspi2,              \
        kCLOCK_Ecspi3, kCLOCK_Ecspi4                                 \
    }

/*! @brief Clock ip name array for ENET. */
#define ENET_CLOCKS                                                  \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Enet, kCLOCK_Enet                   \
    }

/*! @brief Clock ip name array for EPIT. */
#define EPIT_CLOCKS                                                  \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Epit1, kCLOCK_Epit2                 \
    }

/*! @brief Clock ip name array for ESAI. */
#define ESAI_CLOCKS                                                  \
    {                                                                \
        kCLOCK_Esai                                                  \
    }

/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS                                               \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Can1, kCLOCK_Can2                   \
    }

/*! @brief Serial Clock ip name array for FLEXCAN. */
#define FLEXCAN_PERIPH_CLOCKS                                        \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Can1S, kCLOCK_Can2S                 \
    }

/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                                                  \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Gpio1, kCLOCK_Gpio2,                \
        kCLOCK_Gpio3, kCLOCK_Gpio4, kCLOCK_Gpio5                     \
    }

/*! @brief Clock ip name array for GPT. */
#define GPT_CLOCKS                                                   \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Gpt1, kCLOCK_Gpt2                   \
    }

/*! @brief Serial Clock ip name array for GPT. */
#define GPT_PERIPH_CLOCKS                                            \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Gpt1S, kCLOCK_Gpt2S                 \
    }

/*! @brief Clock ip name array for I2C. */
#define I2C_CLOCKS                                                   \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_I2c1S, kCLOCK_I2c2S,                \
        kCLOCK_I2c3S, kCLOCK_I2c4S                                   \
    }

/*! @brief Clock ip name array for PWM. */
#define PWM_CLOCKS                                                   \
    {                                                                \
        kCLOCK_IpInvalid,                                            \
        kCLOCK_Pwm1, kCLOCK_Pwm2, kCLOCK_Pwm3, kCLOCK_Pwm4,          \
        kCLOCK_Pwm5, kCLOCK_Pwm6, kCLOCK_Pwm7, kCLOCK_Pwm8,          \
    }

/*! @brief Clock ip name array for QSPI. */
#define QSPI_CLOCKS                                                  \
    {                                                                \
        kCLOCK_Qspi1                                                 \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                                   \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Sai1, kCLOCK_Sai2, kCLOCK_Sai3,     \
    }

/*! @brief Clock ip name array for SDMA. */
#define SDMA_CLOCKS                                                  \
    {                                                                \
        kCLOCK_Sdma                                                  \
    }

/*! @brief Clock ip name array for TSC. */
#define TSC_CLOCKS                                                   \
    {                                                                \
        kCLOCK_Tsc                                                   \
    }

/*! @brief Clock ip name array for UART. */
#define UART_CLOCKS                                                  \
    {                                                                \
        kCLOCK_IpInvalid,                                            \
        kCLOCK_Uart1, kCLOCK_Uart2, kCLOCK_Uart3, kCLOCK_Uart4,      \
        kCLOCK_Uart5, kCLOCK_Uart6, kCLOCK_Uart7, kCLOCK_Uart8       \
    }

/*! @brief Clock ip name array for USDHC. */
#define USDHC_CLOCKS                                                 \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Usdhc1, kCLOCK_Usdhc2               \
    }

/*! @brief Clock ip name array for WDOG. */
#define WDOG_CLOCKS                                                  \
    {                                                                \
        kCLOCK_IpInvalid, kCLOCK_Wdog1, kCLOCK_Wdog2, kCLOCK_Wdog3   \
    }

/*! @brief eLCDIF apb_clk. */
#define LCDIF_CLOCKS \
    {                \
        kCLOCK_Lcd   \
    }

/*! @brief eLCDIF pix_clk. */
#define LCDIF_PERIPH_CLOCKS \
    {                       \
        kCLOCK_Lcdif1       \
    }

/*! @brief PXP clock. */
#define PXP_CLOCKS \
    {              \
        kCLOCK_Pxp \
    }

/*! @brief Clock ip name array for SNVS HP. */
#define SNVS_HP_CLOCKS \
    {                  \
        kCLOCK_SnvsHp  \
    }

/*! @brief Clock ip name array for SNVS LP. */
#define SNVS_LP_CLOCKS \
    {                  \
        kCLOCK_SnvsLp  \
    }

/*! @brief CSI clock. */
#define CSI_CLOCKS  \
    {               \
        kCLOCK_Csi  \
    }

/*! @brief CSI MCLK. */
#define CSI_MCLK_CLOCKS  \
    {                    \
        kCLOCK_CsiMclk   \
    }

/*! @brief MMDC IPG clock. */
#define FSL_CLOCK_MMDC_IPG_GATE_COUNT 2U
#define MMDC_CLOCKS                          \
    {                                        \
        {kCLOCK_MmdcIpgP0, kCLOCK_MmdcIpgP1} \
    }

/*! @brief MMDC ACLK. */
#define MMDC_ACLK_CLOCKS  \
    {                     \
        kCLOCK_MmdcAClk   \
    }

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CpuClk            = 0x0U, /*!< CPU clock */
    kCLOCK_AxiClk            = 0x1U, /*!< AXI clock */
    kCLOCK_AhbClk            = 0x2U, /*!< AHB clock */
    kCLOCK_IpgClk            = 0x3U, /*!< IPG clock */
    kCLOCK_MmdcClk           = 0x4U, /*!< MMDC clock */

    kCLOCK_OscClk            = 0x5U, /*!< OSC clock selected by PMU_LOWPWR_CTRL[OSC_SEL]. */
    kCLOCK_RtcClk            = 0x6U, /*!< RTC clock. (RTCCLK)                           */

    kCLOCK_ArmPllClk         = 0x7U, /*!< ARMPLLCLK.                              */

    kCLOCK_Usb1PllClk        = 0x8U, /*!< USB1PLLCLK.                              */
    kCLOCK_Usb1PllPfd0Clk    = 0x9U, /*!< USB1PLLPDF0CLK.                          */
    kCLOCK_Usb1PllPfd1Clk    = 0xAU, /*!< USB1PLLPFD1CLK.                          */
    kCLOCK_Usb1PllPfd2Clk    = 0xBU, /*!< USB1PLLPFD2CLK.                          */
    kCLOCK_Usb1PllPfd3Clk    = 0xCU, /*!< USB1PLLPFD3CLK.                          */

    kCLOCK_Usb2PllClk        = 0xDU, /*!< USB2PLLCLK.                          */

    kCLOCK_SysPllClk         = 0xEU, /*!< SYSPLLCLK.                          */
    kCLOCK_SysPllPfd0Clk     = 0xFU, /*!< SYSPLLPDF0CLK.                          */
    kCLOCK_SysPllPfd1Clk     = 0x10U, /*!< SYSPLLPFD1CLK.                          */
    kCLOCK_SysPllPfd2Clk     = 0x11U, /*!< SYSPLLPFD2CLK.                          */
    kCLOCK_SysPllPfd3Clk     = 0x12U, /*!< SYSPLLPFD3CLK.                          */

    kCLOCK_EnetPll0Clk       = 0x13U,   /*!< Enet PLLCLK ref_enetpll0.               */
    kCLOCK_EnetPll1Clk       = 0x14U,   /*!< Enet PLLCLK ref_enetpll1.               */
    kCLOCK_EnetPll2Clk       = 0x15U,   /*!< Enet PLLCLK ref_enetpll2.               */

    kCLOCK_AudioPllClk       = 0x16U,   /*!< Audio PLLCLK.                          */
    kCLOCK_VideoPllClk       = 0x17U,   /*!< Video PLLCLK.                          */
} clock_name_t;

#define kCLOCK_CoreSysClk kCLOCK_CpuClk             /*!< For compatible with other platforms without CCM. */
#define CLOCK_GetCoreSysClkFreq CLOCK_GetCpuClkFreq /*!< For compatible with other platforms without CCM. */

/*! @brief Clock name used to enable/disable gate */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid      = -1,
    /* CCM CCGR0 */
    kCLOCK_AipsTz1        = (0U << 8) | 0x0U,     /*!< CCGR0, CG0  */
    kCLOCK_AipsTz2        = (0U << 8) | 0x1U,     /*!< CCGR0, CG1  */
    kCLOCK_Apbhdma        = (0U << 8) | 0x2U,     /*!< CCGR0, CG2  */
    kCLOCK_Asrc           = (0U << 8) | 0x3U,     /*!< CCGR0, CG3  */
                                                  /*!< CCGR(0U << 8), CG4 reserved */
    kCLOCK_Dcp            = (0U << 8) | 0x5U,     /*!< CCGR0, CG5  */
    kCLOCK_Enet           = (0U << 8) | 0x6U,     /*!< CCGR0, CG6  */
    kCLOCK_Can1           = (0U << 8) | 0x7U,     /*!< CCGR0, CG7  */
    kCLOCK_Can1S          = (0U << 8) | 0x8U,     /*!< CCGR0, CG8 , Serial Clock */
    kCLOCK_Can2           = (0U << 8) | 0x9U,     /*!< CCGR0, CG9  */
    kCLOCK_Can2S          = (0U << 8) | 0xAU,     /*!< CCGR0, CG10, Serial Clock */
    kCLOCK_CpuDbg         = (0U << 8) | 0xBU,     /*!< CCGR0, CG11 */
    kCLOCK_Gpt2           = (0U << 8) | 0xCU,     /*!< CCGR0, CG12 */
    kCLOCK_Gpt2S          = (0U << 8) | 0xDU,     /*!< CCGR0, CG13, Serial Clock */
    kCLOCK_Uart2          = (0U << 8) | 0xEU,     /*!< CCGR0, CG14 */
    kCLOCK_Gpio2          = (0U << 8) | 0xFU,     /*!< CCGR0, CG15 */

    /*!< CCM CCGR1 */
    kCLOCK_Ecspi1         = (1U << 8) | 0x0U,     /*!< CCGR1, CG0  */
    kCLOCK_Ecspi2         = (1U << 8) | 0x1U,     /*!< CCGR1, CG1  */
    kCLOCK_Ecspi3         = (1U << 8) | 0x2U,     /*!< CCGR1, CG2  */
    kCLOCK_Ecspi4         = (1U << 8) | 0x3U,     /*!< CCGR1, CG3  */
    kCLOCK_Adc_5hc        = (1U << 8) | 0x4U,     /*!< CCGR1, CG4  */
    kCLOCK_Uart3          = (1U << 8) | 0x5U,     /*!< CCGR1, CG5  */
    kCLOCK_Epit1          = (1U << 8) | 0x6U,     /*!< CCGR1, CG6  */
    kCLOCK_Epit2          = (1U << 8) | 0x7U,     /*!< CCGR1, CG7  */
    kCLOCK_Adc1           = (1U << 8) | 0x8U,     /*!< CCGR1, CG8  */
    kCLOCK_SimS           = (1U << 8) | 0x9U,     /*!< CCGR1, CG9  */
    kCLOCK_Gpt1           = (1U << 8) | 0xAU,     /*!< CCGR1, CG10 */
    kCLOCK_Gpt1S          = (1U << 8) | 0xBU,     /*!< CCGR1, CG11, Serial Clock */
    kCLOCK_Uart4          = (1U << 8) | 0xCU,     /*!< CCGR1, CG12 */
    kCLOCK_Gpio1          = (1U << 8) | 0xDU,     /*!< CCGR1, CG13 */
    kCLOCK_Csu            = (1U << 8) | 0xEU,     /*!< CCGR1, CG14 */
    kCLOCK_Gpio5          = (1U << 8) | 0xFU,     /*!< CCGR1, CG15 */

    /*!< CCM CCGR2 */
    kCLOCK_Esai           = (2U << 8) | 0x0U,     /*!< CCGR2, CG0  */
    kCLOCK_Csi            = (2U << 8) | 0x1U,     /*!< CCGR2, CG1  */
    kCLOCK_IomuxcSnvs     = (2U << 8) | 0x2U,     /*!< CCGR2, CG2  */
    kCLOCK_I2c1S          = (2U << 8) | 0x3U,     /*!< CCGR2, CG3,  Serial Clock */
    kCLOCK_I2c2S          = (2U << 8) | 0x4U,     /*!< CCGR2, CG4,  Serial Clock */
    kCLOCK_I2c3S          = (2U << 8) | 0x5U,     /*!< CCGR2, CG5,  Serial Clock */
    kCLOCK_Ocotp          = (2U << 8) | 0x6U,     /*!< CCGR2, CG6  */
    kCLOCK_IomuxcIpt      = (2U << 8) | 0x7U,     /*!< CCGR2, CG7  */
    kCLOCK_Ipmux1         = (2U << 8) | 0x8U,     /*!< CCGR2, CG8  */
    kCLOCK_Ipmux2         = (2U << 8) | 0x9U,     /*!< CCGR2, CG9  */
    kCLOCK_Ipmux3         = (2U << 8) | 0xAU,     /*!< CCGR2, CG10 */
    kCLOCK_Ipsync         = (2U << 8) | 0xBU,     /*!< CCGR2, CG11 */
                                                  /*!< CCGR2, CG12 reserved */
    kCLOCK_Gpio3          = (2U << 8) | 0xDU,     /*!< CCGR2, CG13 */
    kCLOCK_Lcd            = (2U << 8) | 0xEU,     /*!< CCGR2, CG14 */
    kCLOCK_Pxp            = (2U << 8) | 0xFU,     /*!< CCGR2, CG15 */

    /*!< CCM CCGR3 */
    kCLOCK_CsiMclk        = (3U << 8) | 0x0U,     /*!< CCGR3, CG0  */
    kCLOCK_Uart5          = (3U << 8) | 0x1U,     /*!< CCGR3, CG1  */
    kCLOCK_Epdc           = (3U << 8) | 0x2U,     /*!< CCGR3, CG2  */
    kCLOCK_Uart6          = (3U << 8) | 0x3U,     /*!< CCGR3, CG3  */
    kCLOCK_Dap            = (3U << 8) | 0x4U,     /*!< CCGR3, CG4  */
    kCLOCK_Lcdif1         = (3U << 8) | 0x5U,     /*!< CCGR3, CG5  */
    kCLOCK_Gpio4          = (3U << 8) | 0x6U,     /*!< CCGR3, CG6  */
    kCLOCK_Qspi1          = (3U << 8) | 0x7U,     /*!< CCGR3, CG7  */
    kCLOCK_Wdog1          = (3U << 8) | 0x8U,     /*!< CCGR3, CG8  */
    kCLOCK_Patch          = (3U << 8) | 0x9U,     /*!< CCGR3, CG9  */
    kCLOCK_MmdcAClk       = (3U << 8) | 0xAU,     /*!< CCGR3, CG10 */
                                                  /*!< CCGR3, CG11 reserved */
    kCLOCK_MmdcIpgP0      = (3U << 8) | 0xCU,     /*!< CCGR3, CG12 */
    kCLOCK_MmdcIpgP1      = (3U << 8) | 0xDU,     /*!< CCGR3, CG13 */
    kCLOCK_Axi            = (3U << 8) | 0xEU,     /*!< CCGR3, CG14 */
    kCLOCK_IomuxcSnvsGpr  = (3U << 8) | 0xFU,     /*!< CCGR3, CG15 */

    /*!< CCM CCGR4 */
                                                  /*!< CCGR4, CG0 reserved */
    kCLOCK_Iomuxc         = (4U << 8) | 0x1U,     /*!< CCGR4, CG1  */
    kCLOCK_IomuxcGpr      = (4U << 8) | 0x2U,     /*!< CCGR4, CG2  */
    kCLOCK_SimCpu         = (4U << 8) | 0x3U,     /*!< CCGR4, CG3  */
    kCLOCK_ApbSlave       = (4U << 8) | 0x4U,     /*!< CCGR4, CG4  */
    kCLOCK_Tsc            = (4U << 8) | 0x5U,     /*!< CCGR4, CG5  */
    kCLOCK_SimM           = (4U << 8) | 0x6U,     /*!< CCGR4, CG6  */
    kCLOCK_Axi2Apb        = (4U << 8) | 0x7U,     /*!< CCGR4, CG7  */
    kCLOCK_Pwm1           = (4U << 8) | 0x8U,     /*!< CCGR4, CG8  */
    kCLOCK_Pwm2           = (4U << 8) | 0x9U,     /*!< CCGR4, CG9  */
    kCLOCK_Pwm3           = (4U << 8) | 0xAU,     /*!< CCGR4, CG10 */
    kCLOCK_Pwm4           = (4U << 8) | 0xBU,     /*!< CCGR4, CG11 */
    kCLOCK_RawNandBchApb  = (4U << 8) | 0xCU,     /*!< CCGR4, CG12 */
    kCLOCK_RawNandBch     = (4U << 8) | 0xDU,     /*!< CCGR4, CG13 */
    kCLOCK_RawNandGpmi    = (4U << 8) | 0xEU,     /*!< CCGR4, CG14 */
    kCLOCK_RawNandGpmiApb = (4U << 8) | 0xFU,     /*!< CCGR4, CG15 */

    /*!< CCM CCGR5 */
    kCLOCK_Rom            = (5U << 8) | 0x0U,     /*!< CCGR5, CG0  */
    kCLOCK_Stcr           = (5U << 8) | 0x1U,     /*!< CCGR5, CG1  */
    kCLOCK_SnvsDryice     = (5U << 8) | 0x2U,     /*!< CCGR5, CG2  */
    kCLOCK_Sdma           = (5U << 8) | 0x3U,     /*!< CCGR5, CG3  */
    kCLOCK_Kpp            = (5U << 8) | 0x4U,     /*!< CCGR5, CG4  */
    kCLOCK_Wdog2          = (5U << 8) | 0x5U,     /*!< CCGR5, CG5  */
    kCLOCK_Spba           = (5U << 8) | 0x6U,     /*!< CCGR5, CG6  */
    kCLOCK_Spdif          = (5U << 8) | 0x7U,     /*!< CCGR5, CG7  */
    kCLOCK_SimMain        = (5U << 8) | 0x8U,     /*!< CCGR5, CG8  */
    kCLOCK_SnvsHp         = (5U << 8) | 0x9U,     /*!< CCGR5, CG9  */
    kCLOCK_SnvsLp         = (5U << 8) | 0xAU,     /*!< CCGR5, CG10 */
    kCLOCK_Sai3           = (5U << 8) | 0xBU,     /*!< CCGR5, CG11 */
    kCLOCK_Uart1          = (5U << 8) | 0xCU,     /*!< CCGR5, CG12 */
    kCLOCK_Uart7          = (5U << 8) | 0xDU,     /*!< CCGR5, CG13 */
    kCLOCK_Sai1           = (5U << 8) | 0xEU,     /*!< CCGR5, CG14 */
    kCLOCK_Sai2           = (5U << 8) | 0xFU,     /*!< CCGR5, CG15 */

    /*!< CCM CCGR6 */
    kCLOCK_UsbOh3         = (6U << 8) | 0x0U,     /*!< CCGR6, CG0  */
    kCLOCK_Usdhc1         = (6U << 8) | 0x1U,     /*!< CCGR6, CG1  */
    kCLOCK_Usdhc2         = (6U << 8) | 0x2U,     /*!< CCGR6, CG2  */
                                                  /*!< CCGR6, CG3 reserved */
    kCLOCK_Ipmux4         = (6U << 8) | 0x4U,     /*!< CCGR6, CG4  */
    kCLOCK_EimSlow        = (6U << 8) | 0x5U,     /*!< CCGR6, CG5  */
                                                  /*!< CCGR6, CG6 reserved */
    kCLOCK_Uart8          = (6U << 8) | 0x7U,     /*!< CCGR6, CG7  */
    kCLOCK_Pwm8           = (6U << 8) | 0x8U,     /*!< CCGR6, CG8  */
    kCLOCK_AipsTz3        = (6U << 8) | 0x9U,     /*!< CCGR6, CG9  */
    kCLOCK_Wdog3          = (6U << 8) | 0xAU,     /*!< CCGR6, CG10 */
    kCLOCK_Anadig         = (6U << 8) | 0xBU,     /*!< CCGR6, CG11 */
    kCLOCK_I2c4S          = (6U << 8) | 0xCU,     /*!< CCGR6, CG12, Serial Clock */
    kCLOCK_Pwm5           = (6U << 8) | 0xDU,     /*!< CCGR6, CG13 */
    kCLOCK_Pwm6           = (6U << 8) | 0xEU,     /*!< CCGR6, CG14 */
    kCLOCK_Pwm7           = (6U << 8) | 0xFU,     /*!< CCGR6, CG15 */
} clock_ip_name_t;

/*! @brief OSC 24M sorce select */
typedef enum _clock_osc
{
    kCLOCK_RcOsc          = 0U,       /*!< On chip OSC. */
    kCLOCK_XtalOsc        = 1U,       /*!< 24M Xtal OSC */
} clock_osc_t;

/*! @brief Clock gate value */
typedef enum _clock_gate_value
{
    kCLOCK_ClockNotNeeded      = 0U,       /*!< Clock is off during all modes. */
    kCLOCK_ClockNeededRun      = 1U,       /*!< Clock is on in run mode, but off in WAIT and STOP modes */
    kCLOCK_ClockNeededRunWait  = 3U,       /*!< Clock is on during all modes, except STOP mode */
} clock_gate_value_t;

/*! @brief System clock mode */
typedef enum _clock_mode_t
{
    kCLOCK_ModeRun         = 0U,        /*!< Remain in run mode. */
    kCLOCK_ModeWait        = 1U,        /*!< Transfer to wait mode. */
    kCLOCK_ModeStop        = 2U,        /*!< Transfer to stop mode. */
} clock_mode_t;

/*!
 * @brief MUX control names for clock mux setting.
 *
 * These constants define the mux control names for clock mux setting.\n
 * - 0:7: REG offset to CCM_BASE in bytes.
 * - 8:15: Root clock setting bit field shift.
 * - 16:31: Root clock setting bit field width.
 */
typedef enum _clock_mux
{
    kCLOCK_StepMux   = CCM_TUPLE(CCSR, CCM_CCSR_STEP_SEL_SHIFT, CCM_CCSR_STEP_SEL_MASK, CCM_NO_BUSY_WAIT),                               /*!< atep clock mux name */
    kCLOCK_SecMux    = CCM_TUPLE(CCSR, CCM_CCSR_SECONDARY_CLK_SEL_SHIFT, CCM_CCSR_SECONDARY_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),             /*!< secondary clock mux name */
    kCLOCK_Pll1SwMux = CCM_TUPLE(CCSR, CCM_CCSR_PLL1_SW_CLK_SEL_SHIFT, CCM_CCSR_PLL1_SW_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                 /*!< pll1_sw_clk mux name */
    kCLOCK_Pll3SwMux = CCM_TUPLE(CCSR, CCM_CCSR_PLL3_SW_CLK_SEL_SHIFT, CCM_CCSR_PLL3_SW_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                 /*!< Pll3_sw_clk mux name */

    kCLOCK_Periph2Mux = CCM_TUPLE(CBCDR, CCM_CBCDR_PERIPH2_CLK_SEL_SHIFT, CCM_CBCDR_PERIPH2_CLK_SEL_MASK, CCM_CDHIPR_PERIPH2_CLK_SEL_BUSY_SHIFT), /*!< periph2 mux name */
    kCLOCK_PeriphMux  = CCM_TUPLE(CBCDR, CCM_CBCDR_PERIPH_CLK_SEL_SHIFT, CCM_CBCDR_PERIPH_CLK_SEL_MASK, CCM_CDHIPR_PERIPH_CLK_SEL_BUSY_SHIFT),    /*!< periph mux name */
    kCLOCK_AxiAltMux  = CCM_TUPLE(CBCDR, CCM_CBCDR_AXI_ALT_SEL_SHIFT, CCM_CBCDR_AXI_ALT_SEL_MASK, CCM_NO_BUSY_WAIT),                              /*!< axi alt mux name */
    kCLOCK_AxiMux     = CCM_TUPLE(CBCDR, CCM_CBCDR_AXI_SEL_SHIFT, CCM_CBCDR_AXI_SEL_MASK, CCM_NO_BUSY_WAIT),                                      /*!< axi mux name */

    kCLOCK_PrePeriph2Mux  = CCM_TUPLE(CBCMR, CCM_CBCMR_PRE_PERIPH2_CLK_SEL_SHIFT, CCM_CBCMR_PRE_PERIPH2_CLK_SEL_MASK, CCM_NO_BUSY_WAIT), /*!< pre-periph2 mux name */
    kCLOCK_PrePeriphMux   = CCM_TUPLE(CBCMR, CCM_CBCMR_PRE_PERIPH_CLK_SEL_SHIFT, CCM_CBCMR_PRE_PERIPH_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),   /*!< pre-periph mux name */
    kCLOCK_Periph2Clk2Mux = CCM_TUPLE(CBCMR, CCM_CBCMR_PERIPH2_CLK2_SEL_SHIFT, CCM_CBCMR_PERIPH2_CLK2_SEL_MASK, CCM_NO_BUSY_WAIT),       /*!< periph2 clock2 mux name */
    kCLOCK_PeriphClk2Mux  = CCM_TUPLE(CBCMR, CCM_CBCMR_PERIPH_CLK2_SEL_SHIFT, CCM_CBCMR_PERIPH_CLK2_SEL_MASK, CCM_NO_BUSY_WAIT),         /*!< periph clock2 mux name */

    kCLOCK_EimSlowMux = CCM_TUPLE(CSCMR1, CCM_CSCMR1_ACLK_EIM_SLOW_SEL_SHIFT, CCM_CSCMR1_ACLK_EIM_SLOW_SEL_MASK, CCM_NO_BUSY_WAIT),      /*!< aclk eim slow mux name */
    kCLOCK_GpmiMux    = CCM_TUPLE(CSCMR1, CCM_CSCMR1_GPMI_CLK_SEL_SHIFT, CCM_CSCMR1_GPMI_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                /*!< gpmi mux name */
    kCLOCK_BchMux     = CCM_TUPLE(CSCMR1, CCM_CSCMR1_BCH_CLK_SEL_SHIFT, CCM_CSCMR1_BCH_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                  /*!< bch mux name */
    kCLOCK_Usdhc2Mux  = CCM_TUPLE(CSCMR1, CCM_CSCMR1_USDHC2_CLK_SEL_SHIFT, CCM_CSCMR1_USDHC2_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),            /*!< usdhc2 mux name */
    kCLOCK_Usdhc1Mux  = CCM_TUPLE(CSCMR1, CCM_CSCMR1_USDHC1_CLK_SEL_SHIFT, CCM_CSCMR1_USDHC1_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),            /*!< usdhc1 mux name */
    kCLOCK_Sai3Mux    = CCM_TUPLE(CSCMR1, CCM_CSCMR1_SAI3_CLK_SEL_SHIFT, CCM_CSCMR1_SAI3_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                /*!< sai3 mux name */
    kCLOCK_Sai2Mux    = CCM_TUPLE(CSCMR1, CCM_CSCMR1_SAI2_CLK_SEL_SHIFT, CCM_CSCMR1_SAI2_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                /*!< sai2 mux name */
    kCLOCK_Sai1Mux    = CCM_TUPLE(CSCMR1, CCM_CSCMR1_SAI1_CLK_SEL_SHIFT, CCM_CSCMR1_SAI1_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                /*!< sai1 mux name */
    kCLOCK_Qspi1Mux   = CCM_TUPLE(CSCMR1, CCM_CSCMR1_QSPI1_CLK_SEL_SHIFT, CCM_CSCMR1_QSPI1_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),              /*!< qspi1 mux name */
    kCLOCK_PerclkMux  = CCM_TUPLE(CSCMR1, CCM_CSCMR1_PERCLK_CLK_SEL_SHIFT, CCM_CSCMR1_PERCLK_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),            /*!< perclk mux name */

    kCLOCK_VidMux     = CCM_TUPLE(CSCMR2, CCM_CSCMR2_VID_CLK_SEL_SHIFT, CCM_CSCMR2_VID_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                  /*!< vid mux name */
    kCLOCK_EsaiMux    = CCM_TUPLE(CSCMR2, CCM_CSCMR2_ESAI_CLK_SEL_SHIFT, CCM_CSCMR2_ESAI_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                /*!< esai mux name */
    kCLOCK_CanMux     = CCM_TUPLE(CSCMR2, CCM_CSCMR2_CAN_CLK_SEL_SHIFT, CCM_CSCMR2_CAN_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                  /*!< can mux name */

    kCLOCK_UartMux    = CCM_TUPLE(CSCDR1, CCM_CSCDR1_UART_CLK_SEL_SHIFT, CCM_CSCDR1_UART_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                /*!< uart mux name */

    kCLOCK_EnfcMux    = CCM_TUPLE(CS2CDR, CCM_CS2CDR_ENFC_CLK_SEL_SHIFT, CCM_CS2CDR_ENFC_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                /*!< enfc mux name */
    kCLOCK_LdbDi0Mux  = CCM_TUPLE(CS2CDR, CCM_CS2CDR_LDB_DI0_CLK_SEL_SHIFT, CCM_CS2CDR_LDB_DI0_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),          /*!< ldb di0 mux name */

    kCLOCK_SpdifMux   = CCM_TUPLE(CDCDR, CCM_CDCDR_SPDIF0_CLK_SEL_SHIFT, CCM_CDCDR_SPDIF0_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),               /*!< spdif mux name */

    kCLOCK_EpdcPreMux = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_EPDC_PRE_CLK_SEL_SHIFT, CCM_CHSCCDR_EPDC_PRE_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),     /*!< epdc pre mux name */
    kCLOCK_EpdcMux    = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_EPDC_CLK_SEL_SHIFT, CCM_CHSCCDR_EPDC_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),             /*!< epdc mux name */

    kCLOCK_EcspiMux     = CCM_TUPLE(CSCDR2, CCM_CSCDR2_ECSPI_CLK_SEL_SHIFT, CCM_CSCDR2_ECSPI_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),            /*!< ecspi mux name */
    kCLOCK_Lcdif1PreMux = CCM_TUPLE(CSCDR2, CCM_CSCDR2_LCDIF1_PRE_CLK_SEL_SHIFT, CCM_CSCDR2_LCDIF1_PRE_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),  /*!< lcdif1 pre mux name */
    kCLOCK_Lcdif1Mux    = CCM_TUPLE(CSCDR2, CCM_CSCDR2_LCDIF1_CLK_SEL_SHIFT, CCM_CSCDR2_LCDIF1_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),          /*!< lcdif1 mux name */

    kCLOCK_CsiMux     = CCM_TUPLE(CSCDR3, CCM_CSCDR3_CSI_CLK_SEL_SHIFT, CCM_CSCDR3_CSI_CLK_SEL_MASK, CCM_NO_BUSY_WAIT),                  /*!< csi mux name */
} clock_mux_t;

/*!
 * @brief DIV control names for clock div setting.
 *
 * These constants define div control names for clock div setting.\n
 * - 0:7: REG offset to CCM_BASE in bytes.
 * - 8:15: Root clock setting bit field shift.
 * - 16:31: Root clock setting bit field width.
 */
typedef enum _clock_div
{
    kCLOCK_ArmDiv     = CCM_TUPLE(CACRR, CCM_CACRR_ARM_PODF_SHIFT, CCM_CACRR_ARM_PODF_MASK, CCM_CDHIPR_ARM_PODF_BUSY_SHIFT),          /*!< core div name */

    kCLOCK_PeriphClk2Div  = CCM_TUPLE(CBCDR, CCM_CBCDR_PERIPH_CLK2_PODF_SHIFT, CCM_CBCDR_PERIPH_CLK2_PODF_MASK, CCM_NO_BUSY_WAIT),    /*!< periph clock2 div name */
    kCLOCK_Periph2Clk2Div = CCM_TUPLE(CBCDR, CCM_CBCDR_PERIPH2_CLK2_PODF_SHIFT, CCM_CBCDR_PERIPH2_CLK2_PODF_MASK, CCM_NO_BUSY_WAIT),  /*!< periph2 clock2 div name */
    kCLOCK_AxiDiv         = CCM_TUPLE(CBCDR, CCM_CBCDR_AXI_PODF_SHIFT, CCM_CBCDR_AXI_PODF_MASK, CCM_CDHIPR_AXI_PODF_BUSY_SHIFT),      /*!< axi div name */
    kCLOCK_AhbDiv         = CCM_TUPLE(CBCDR, CCM_CBCDR_AHB_PODF_SHIFT, CCM_CBCDR_AHB_PODF_MASK, CCM_CDHIPR_AHB_PODF_BUSY_SHIFT),      /*!< ahb div name */
    kCLOCK_IpgDiv         = CCM_TUPLE(CBCDR, CCM_CBCDR_IPG_PODF_SHIFT, CCM_CBCDR_IPG_PODF_MASK, CCM_NO_BUSY_WAIT),                    /*!< ipg div name */
    kCLOCK_FabricMmdcDiv  = CCM_TUPLE(CBCDR, CCM_CBCDR_FABRIC_MMDC_PODF_SHIFT, CCM_CBCDR_FABRIC_MMDC_PODF_MASK, CCM_CDHIPR_MMDC_PODF_BUSY_SHIFT), /*!< mmdc/fabric div name */

    kCLOCK_Lcdif1Div  = CCM_TUPLE(CBCMR, CCM_CBCMR_LCDIF1_PODF_SHIFT, CCM_CBCMR_LCDIF1_PODF_MASK, CCM_NO_BUSY_WAIT),                  /*!< lcdif1 div name */

    kCLOCK_Qspi1Div   = CCM_TUPLE(CSCMR1, CCM_CSCMR1_QSPI1_PODF_SHIFT, CCM_CSCMR1_QSPI1_PODF_MASK, CCM_NO_BUSY_WAIT),                 /*!< qspi1 div name */
    kCLOCK_EimSlowDiv = CCM_TUPLE(CSCMR1, CCM_CSCMR1_ACLK_EIM_SLOW_PODF_SHIFT, CCM_CSCMR1_ACLK_EIM_SLOW_PODF_MASK, CCM_NO_BUSY_WAIT), /*!< eim slow div name */
    kCLOCK_PerclkDiv  = CCM_TUPLE(CSCMR1, CCM_CSCMR1_PERCLK_PODF_SHIFT, CCM_CSCMR1_PERCLK_PODF_MASK, CCM_NO_BUSY_WAIT),               /*!< perclk div name */

    kCLOCK_VidDiv     = CCM_TUPLE(CSCMR2, CCM_CSCMR2_VID_CLK_PODF_SHIFT, CCM_CSCMR2_VID_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),             /*!< vid div name */
    kCLOCK_VidPreDiv  = CCM_TUPLE(CSCMR2, CCM_CSCMR2_VID_CLK_PRE_PODF_SHIFT, CCM_CSCMR2_VID_CLK_PRE_PODF_MASK, CCM_NO_BUSY_WAIT),     /*!< vid pre div name */
    kCLOCK_LdbDi0Div  = CCM_TUPLE(CSCMR2, CCM_CSCMR2_LDB_DI0_DIV_SHIFT, CCM_CSCMR2_LDB_DI0_DIV_MASK, CCM_NO_BUSY_WAIT),               /*!< ldb di0 div name */
    kCLOCK_LdbDi1Div  = CCM_TUPLE(CSCMR2, CCM_CSCMR2_LDB_DI1_DIV_SHIFT, CCM_CSCMR2_LDB_DI1_DIV_MASK, CCM_NO_BUSY_WAIT),               /*!< ldb di1 div name */
    kCLOCK_CanDiv     = CCM_TUPLE(CSCMR2, CCM_CSCMR2_CAN_CLK_PODF_SHIFT, CCM_CSCMR2_CAN_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),             /*!< can div name */

    kCLOCK_GpmiDiv    = CCM_TUPLE(CSCDR1, CCM_CSCDR1_GPMI_PODF_SHIFT, CCM_CSCDR1_GPMI_PODF_MASK, CCM_NO_BUSY_WAIT),                   /*!< gpmi div name */
    kCLOCK_BchDiv     = CCM_TUPLE(CSCDR1, CCM_CSCDR1_BCH_PODF_SHIFT, CCM_CSCDR1_BCH_PODF_MASK, CCM_NO_BUSY_WAIT),                     /*!< bch div name */
    kCLOCK_Usdhc2Div  = CCM_TUPLE(CSCDR1, CCM_CSCDR1_USDHC2_PODF_SHIFT, CCM_CSCDR1_USDHC2_PODF_MASK, CCM_NO_BUSY_WAIT),               /*!< usdhc2 div name */
    kCLOCK_Usdhc1Div  = CCM_TUPLE(CSCDR1, CCM_CSCDR1_USDHC1_PODF_SHIFT, CCM_CSCDR1_USDHC1_PODF_MASK, CCM_NO_BUSY_WAIT),               /*!< usdhc1 div name */
    kCLOCK_UartDiv    = CCM_TUPLE(CSCDR1, CCM_CSCDR1_UART_CLK_PODF_SHIFT, CCM_CSCDR1_UART_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),           /*!< uart div name */

    kCLOCK_EsaiPreDiv = CCM_TUPLE(CS1CDR, CCM_CS1CDR_ESAI_CLK_PRED_SHIFT, CCM_CS1CDR_ESAI_CLK_PRED_MASK, CCM_NO_BUSY_WAIT),           /*!< sai3 pre div name */
    kCLOCK_EsaiDiv    = CCM_TUPLE(CS1CDR, CCM_CS1CDR_ESAI_CLK_PODF_SHIFT, CCM_CS1CDR_ESAI_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),           /*!< esai div name */
    kCLOCK_Sai3PreDiv = CCM_TUPLE(CS1CDR, CCM_CS1CDR_SAI3_CLK_PRED_SHIFT, CCM_CS1CDR_SAI3_CLK_PRED_MASK, CCM_NO_BUSY_WAIT),           /*!< sai3 pre div name */
    kCLOCK_Sai3Div    = CCM_TUPLE(CS1CDR, CCM_CS1CDR_SAI3_CLK_PODF_SHIFT, CCM_CS1CDR_SAI3_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),           /*!< sai3 div name */
    kCLOCK_Sai1PreDiv = CCM_TUPLE(CS1CDR, CCM_CS1CDR_SAI1_CLK_PRED_SHIFT, CCM_CS1CDR_SAI1_CLK_PRED_MASK, CCM_NO_BUSY_WAIT),           /*!< sai1 pre div name */
    kCLOCK_Sai1Div    = CCM_TUPLE(CS1CDR, CCM_CS1CDR_SAI1_CLK_PODF_SHIFT, CCM_CS1CDR_SAI1_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),           /*!< sai1 div name */

    kCLOCK_EnfcPreDiv = CCM_TUPLE(CS2CDR, CCM_CS2CDR_ENFC_CLK_PRED_SHIFT, CCM_CS2CDR_ENFC_CLK_PRED_MASK, CCM_NO_BUSY_WAIT),           /*!< enfc pre div name */
    kCLOCK_EnfcDiv    = CCM_TUPLE(CS2CDR, CCM_CS2CDR_ENFC_CLK_PODF_SHIFT, CCM_CS2CDR_ENFC_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),           /*!< enfc div name */
    kCLOCK_Sai2PreDiv = CCM_TUPLE(CS2CDR, CCM_CS2CDR_SAI2_CLK_PRED_SHIFT, CCM_CS2CDR_SAI2_CLK_PRED_MASK, CCM_NO_BUSY_WAIT),           /*!< sai2 pre div name */
    kCLOCK_Sai2Div    = CCM_TUPLE(CS2CDR, CCM_CS2CDR_SAI2_CLK_PODF_SHIFT, CCM_CS2CDR_SAI2_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),           /*!< sai2 div name */

    kCLOCK_Spdif0PreDiv = CCM_TUPLE(CDCDR, CCM_CDCDR_SPDIF0_CLK_PRED_SHIFT, CCM_CDCDR_SPDIF0_CLK_PRED_MASK, CCM_NO_BUSY_WAIT),        /*!< spdif pre div name */
    kCLOCK_Spdif0Div  = CCM_TUPLE(CDCDR, CCM_CDCDR_SPDIF0_CLK_PODF_SHIFT, CCM_CDCDR_SPDIF0_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),          /*!< spdif div name */

    kCLOCK_EpdcDiv    = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_EPDC_PODF_SHIFT, CCM_CHSCCDR_EPDC_PODF_MASK, CCM_NO_BUSY_WAIT),                /*!< epdc div name */

    kCLOCK_EcspiDiv   = CCM_TUPLE(CSCDR2, CCM_CSCDR2_ECSPI_CLK_PODF_SHIFT, CCM_CSCDR2_ECSPI_CLK_PODF_MASK, CCM_NO_BUSY_WAIT),         /*!< ecspi div name */
    kCLOCK_Lcdif1PreDiv = CCM_TUPLE(CSCDR2, CCM_CSCDR2_LCDIF1_PRED_SHIFT, CCM_CSCDR2_LCDIF1_PRED_MASK, CCM_NO_BUSY_WAIT),             /*!< lcdif1 pre div name */

    kCLOCK_CsiDiv     = CCM_TUPLE(CSCDR3, CCM_CSCDR3_CSI_PODF_SHIFT, CCM_CSCDR3_CSI_PODF_MASK, CCM_NO_BUSY_WAIT),                     /*!< csi div name */
} clock_div_t;

/*! @brief PLL configuration for ARM */
typedef struct _clock_arm_pll_config
{
    uint32_t loopDivider;      /*!< PLL loop divider. Valid range for divider value: 54-108. Fout=Fin*loopDivider/2. */
} clock_arm_pll_config_t;

/*! @brief PLL configuration for USB */
typedef struct _clock_usb_pll_config
{
    uint8_t  loopDivider;      /*!< PLL loop divider.
                                    0 - Fout=Fref*20;
                                    1 - Fout=Fref*22 */
} clock_usb_pll_config_t;


/*! @brief PLL configuration for System */
typedef struct _clock_sys_pll_config
{
    uint8_t  loopDivider;      /*!< PLL loop divider. Intended to be 1 (528M).
                                    0 - Fout=Fref*20;
                                    1 - Fout=Fref*22 */
    uint32_t numerator;        /*!< 30 bit numerator of fractional loop divider.*/
    uint32_t denominator;      /*!< 30 bit denominator of fractional loop divider */
} clock_sys_pll_config_t;

/*! @brief PLL configuration for AUDIO and VIDEO */
typedef struct _clock_audio_pll_config
{
    uint8_t loopDivider;       /*!< PLL loop divider. Valid range for DIV_SELECT divider value: 27~54. */
    uint8_t postDivider;       /*!< Divider after the PLL, should only be 1, 2, 4, 8, 16. */
    uint32_t numerator;        /*!< 30 bit numerator of fractional loop divider.*/
    uint32_t denominator;      /*!< 30 bit denominator of fractional loop divider */
} clock_audio_pll_config_t;

/*! @brief PLL configuration for AUDIO and VIDEO */
typedef struct _clock_video_pll_config
{
    uint8_t loopDivider;       /*!< PLL loop divider. Valid range for DIV_SELECT divider value: 27~54. */
    uint8_t postDivider;       /*!< Divider after the PLL, should only be 1, 2, 4, 8, 16. */
    uint32_t numerator;        /*!< 30 bit numerator of fractional loop divider.*/
    uint32_t denominator;      /*!< 30 bit denominator of fractional loop divider */
} clock_video_pll_config_t;

/*! @brief PLL configuration for ENET */
typedef struct _clock_enet_pll_config
{
    bool     enableClkOutput0;  /*!< Power on and enable PLL clock output for ENET0 (ref_enetpll0). */
    bool     enableClkOutput1;  /*!< Power on and enable PLL clock output for ENET1 (ref_enetpll1). */
    bool     enableClkOutput2;  /*!< Power on and enable PLL clock output for ENET2 (ref_enetpll2). */
    uint8_t  loopDivider0;      /*!< Controls the frequency of the ENET0 reference clock.
                                     b00 25MHz
                                     b01 50MHz
                                     b10 100MHz (not 50% duty cycle)
                                     b11 125MHz */
    uint8_t  loopDivider1;      /*!< Controls the frequency of the ENET1 reference clock.
                                     b00 25MHz
                                     b01 50MHz
                                     b10 100MHz (not 50% duty cycle)
                                     b11 125MHz */
} clock_enet_pll_config_t;

/*! @brief PLL name */
typedef enum _clock_pll
{
    kCLOCK_PllArm    = 0U,   /*!< PLL ARM */
    kCLOCK_PllSys    = 1U,   /*!< PLL SYS */
    kCLOCK_PllUsb1   = 2U,   /*!< PLL USB1 */
    kCLOCK_PllAudio  = 3U,   /*!< PLL Audio */
    kCLOCK_PllVideo  = 4U,   /*!< PLL Video */
    kCLOCK_PllEnet0  = 5U,   /*!< PLL Enet0 */
    kCLOCK_PllEnet1  = 6U,   /*!< PLL Enet1 */
    kCLOCK_PllEnet2  = 7U,   /*!< PLL Enet2 */
    kCLOCK_PllUsb2   = 8U,   /*!< PLL USB2 */
} clock_pll_t;

/*! @brief PLL PFD name */
typedef enum _clock_pfd
{
    kCLOCK_Pfd0    = 0U,   /*!< PLL PFD0 */
    kCLOCK_Pfd1    = 1U,   /*!< PLL PFD1 */
    kCLOCK_Pfd2    = 2U,   /*!< PLL PFD2 */
    kCLOCK_Pfd3    = 3U,   /*!< PLL PFD3 */
} clock_pfd_t;

/*! @brief USB clock source definition. */
typedef enum _clock_usb_src
{
    kCLOCK_Usb480M = 0,   /*!< Use 480M.      */
    kCLOCK_UsbSrcUnused = 0xFFFFFFFFU,                                    /*!< Used when the function does not
                                                                               care the clock source. */
} clock_usb_src_t;

/*! @brief Source of the USB HS PHY. */
typedef enum _clock_usb_phy_src
{
    kCLOCK_Usbphy480M = 0,   /*!< Use 480M.      */
} clock_usb_phy_src_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Set CCM MUX node to certain value.
 *
 * @param mux   Which mux node to set, see \ref clock_mux_t.
 * @param value Clock mux value to set, different mux has different value range.
 */
static inline void CLOCK_SetMux(clock_mux_t mux, uint32_t value)
{
    uint32_t busyShift;

    busyShift = CCM_TUPLE_BUSY_SHIFT(mux);
    CCM_TUPLE_REG(CCM, mux) = (CCM_TUPLE_REG(CCM, mux) & (~CCM_TUPLE_MASK(mux))) |
                              (((uint32_t)((value) << CCM_TUPLE_SHIFT(mux))) & CCM_TUPLE_MASK(mux));

    assert(busyShift <= CCM_NO_BUSY_WAIT);

    /* Clock switch need Handshake? */
    if (CCM_NO_BUSY_WAIT != busyShift)
    {
        /* Wait until CCM internal handshake finish. */
        while (CCM->CDHIPR & (1U << busyShift))
        {
        }
    }
}

/*!
 * @brief Get CCM MUX value.
 *
 * @param mux   Which mux node to get, see \ref clock_mux_t.
 * @return Clock mux value.
 */
static inline uint32_t CLOCK_GetMux(clock_mux_t mux)
{
    return (CCM_TUPLE_REG(CCM, mux) & CCM_TUPLE_MASK(mux)) >> CCM_TUPLE_SHIFT(mux);
}

/*!
 * @brief Set CCM DIV node to certain value.
 *
 * @param divider Which div node to set, see \ref clock_div_t.
 * @param value   Clock div value to set, different divider has different value range.
 */
static inline void CLOCK_SetDiv(clock_div_t divider, uint32_t value)
{
    uint32_t busyShift;

    busyShift = CCM_TUPLE_BUSY_SHIFT(divider);
    CCM_TUPLE_REG(CCM, divider) = (CCM_TUPLE_REG(CCM, divider) & (~CCM_TUPLE_MASK(divider))) |
                              (((uint32_t)((value) << CCM_TUPLE_SHIFT(divider))) & CCM_TUPLE_MASK(divider));

    assert(busyShift <= CCM_NO_BUSY_WAIT);

    /* Clock switch need Handshake? */
    if (CCM_NO_BUSY_WAIT != busyShift)
    {
        /* Wait until CCM internal handshake finish. */
        while (CCM->CDHIPR & (1U << busyShift))
        {
        }
    }
}

/*!
 * @brief Get CCM DIV node value.
 *
 * @param divider Which div node to get, see \ref clock_div_t.
 */
static inline uint32_t CLOCK_GetDiv(clock_div_t divider)
{
    uint32_t value;

    value = (CCM_TUPLE_REG(CCM, divider) & CCM_TUPLE_MASK(divider)) >> CCM_TUPLE_SHIFT(divider);
    return value;
}

/*!
 * @brief Control the clock gate for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 * @param value Clock gate value to set, see \ref clock_gate_value_t.
 */
static inline void CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value)
{
    uint32_t index = ((uint32_t)name) >> 8;
    uint32_t shift = (((uint32_t)name) & 0xF) << 1;
    volatile uint32_t *reg;

    assert (index <= 6);

    reg = ((volatile uint32_t *)&CCM->CCGR0) + index;
    *reg = ((*reg) & ~(3U << shift)) | (((uint32_t)value) << shift);
}

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_ClockNeededRunWait);
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_ClockNotNeeded);
}

/*!
 * @brief Setting the low power mode that system will enter on next assertion of dsm_request signal.
 *
 * @param mode  Which mode to enter, see \ref clock_mode_t.
 */
static inline void CLOCK_SetMode(clock_mode_t mode)
{
    CCM->CLPCR = (CCM->CLPCR & ~CCM_CLPCR_LPM_MASK) | CCM_CLPCR_LPM((uint32_t)mode);
}

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 *
 * @param clockName Clock names defined in clock_name_t
 * @return Clock frequency value in hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t name);

/*!
 * @name OSC operations
 * @{
 */

/*!
 * @brief Initialize the external 24MHz clock.
 *
 * This function supports two modes:
 * 1. Use external crystal oscillator.
 * 2. Bypass the external crystal oscillator, using input source clock directly.
 *
 * After this function, please call @ref CLOCK_SetXtal0Freq to inform clock driver
 * the external clock frequency.
 *
 * @param bypassXtalOsc Pass in true to bypass the external crystal oscillator.
 * @note This device does not support bypass external crystal oscillator, so
 * the input parameter should always be false.
 */
void CLOCK_InitExternalClk(bool bypassXtalOsc);

/*!
 * @brief Deinitialize the external 24MHz clock.
 *
 * This function disables the external 24MHz clock.
 *
 * After this function, please call @ref CLOCK_SetXtal0Freq to set external clock
 * frequency to 0.
 */
void CLOCK_DeinitExternalClk(void);

/*!
 * @brief Switch the OSC.
 *
 * This function switches the OSC source for SoC.
 *
 * @param osc   OSC source to switch to.
 */
void CLOCK_SwitchOsc(clock_osc_t osc);

/*!
 * @brief Gets the OSC clock frequency.
 *
 * This function will return the external XTAL OSC frequency if it is selected as the source of OSC,
 * otherwise internal 24MHz RC OSC frequency will be returned.
 *
 * @param osc   OSC type to get frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static inline uint32_t CLOCK_GetOscFreq(void)
{
    return (PMU->LOWPWR_CTRL & PMU_LOWPWR_CTRL_OSC_SEL_MASK) ? 24000000UL : g_xtalFreq;
}

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
 * @brief Set the XTAL (24M OSC) frequency based on board setting.
 *
 * @param freq The XTAL input clock frequency in Hz.
 */
static inline void CLOCK_SetXtalFreq(uint32_t freq)
{
    g_xtalFreq = freq;
}

/*!
 * @brief Set the RTC XTAL (32K OSC) frequency based on board setting.
 *
 * @param freq The RTC XTAL input clock frequency in Hz.
 */
static inline void CLOCK_SetRtcXtalFreq(uint32_t freq)
{
    g_rtcXtalFreq = freq;
}


/*!
 * @brief Initialize the RC oscillator 24MHz clock.
 */
void CLOCK_InitRcOsc24M(void);

/*!
 * @brief Power down the RCOSC 24M clock.
 */
void CLOCK_DeinitRcOsc24M(void);
/* @} */

/*!
 * @name PLL/PFD operations
 * @{
 */

/*!
 * @brief Initialize the ARM PLL.
 *
 * This function initialize the ARM PLL with specific settings
 *
 * @param config   configuration to set to PLL.
 */
void CLOCK_InitArmPll(const clock_arm_pll_config_t *config);

/*!
 * @brief De-initialize the ARM PLL.
 */
void CLOCK_DeinitArmPll(void);

/*!
 * @brief Initialize the System PLL.
 *
 * This function initializes the System PLL with specific settings
 *
 * @param config Configuration to set to PLL.
 */
void CLOCK_InitSysPll(const clock_sys_pll_config_t *config);

/*!
 * @brief De-initialize the System PLL.
 */
void CLOCK_DeinitSysPll(void);

/*!
 * @brief Initialize the USB1 PLL.
 *
 * This function initializes the USB1 PLL with specific settings
 *
 * @param config Configuration to set to PLL.
 */
void CLOCK_InitUsb1Pll(const clock_usb_pll_config_t *config);

/*!
 * @brief Deinitialize the USB1 PLL.
 */
void CLOCK_DeinitUsb1Pll(void);

/*!
 * @brief Initialize the USB2 PLL.
 *
 * This function initializes the USB2 PLL with specific settings
 *
 * @param config Configuration to set to PLL.
 */
void CLOCK_InitUsb2Pll(const clock_usb_pll_config_t *config);

/*!
 * @brief Deinitialize the USB2 PLL.
 */
void CLOCK_DeinitUsb2Pll(void);

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
 * @brief Initialize the ENET PLL.
 *
 * This function initializes the ENET PLL with specific settings.
 *
 * @param config Configuration to set to PLL.
 */
void CLOCK_InitEnetPll(const clock_enet_pll_config_t *config);

/*!
 * @brief Deinitialize the ENET PLL.
 *
 * This function disables the ENET PLL.
 */
void CLOCK_DeinitEnetPll(void);

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
 * @brief Initialize the System PLL PFD.
 *
 * This function initializes the System PLL PFD. During new value setting,
 * the clock output is disabled to prevent glitch.
 *
 * @param pfd Which PFD clock to enable.
 * @param pfdFrac The PFD FRAC value.
 * @note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitSysPfd(clock_pfd_t pfd, uint8_t pfdFrac);

/*!
 * @brief De-initialize the System PLL PFD.
 *
 * This function disables the System PLL PFD.
 *
 * @param pfd Which PFD clock to disable.
 */
void CLOCK_DeinitSysPfd(clock_pfd_t pfd);

/*!
 * @brief Initialize the USB1 PLL PFD.
 *
 * This function initializes the USB1 PLL PFD. During new value setting,
 * the clock output is disabled to prevent glitch.
 *
 * @param pfd Which PFD clock to enable.
 * @param pfdFrac The PFD FRAC value.
 * @note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitUsb1Pfd(clock_pfd_t pfd, uint8_t pfdFrac);

/*!
 * @brief De-initialize the USB1 PLL PFD.
 *
 * This function disables the USB1 PLL PFD.
 *
 * @param pfd Which PFD clock to disable.
 */
void CLOCK_DeinitUsb1Pfd(clock_pfd_t pfd);

/*!
 * @brief Get current System PLL PFD output frequency.
 *
 * This function get current output frequency of specific System PLL PFD
 *
 * @param pfd   pfd name to get frequency.
 * @return The PFD output frequency in hertz.
 */
uint32_t CLOCK_GetSysPfdFreq(clock_pfd_t pfd);

/*!
 * @brief Get current USB1 PLL PFD output frequency.
 *
 * This function get current output frequency of specific USB1 PLL PFD
 *
 * @param pfd   pfd name to get frequency.
 * @return The PFD output frequency in hertz.
 */
uint32_t CLOCK_GetUsb1PfdFreq(clock_pfd_t pfd);

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
bool CLOCK_EnableUsbhs1PhyPllClock(clock_usb_phy_src_t src, uint32_t freq);

/*! @brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs1PhyPllClock(void);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
