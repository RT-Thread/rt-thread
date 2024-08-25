/*
 * Copyright 2024 NXP
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
/*! @brief CLOCK driver version 2.0.0. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief External XTAL0 (OSC0) clock frequency.
 *
 * The XTAL0/EXTAL0 (OSC0) clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetXtal0Freq to set the value in the clock driver. For example,
 * if XTAL0 is 8 MHz:
 * @code
 * CLOCK_InitOsc0(...);
 * CLOCK_SetXtal0Freq(80000000);
 * @endcode
 *
 * This is important for the multicore platforms where one core needs to set up the
 * OSC0 using the CLOCK_InitOsc0. All other cores need to call the CLOCK_SetXtal0Freq
 * to get a valid clock frequency.
 */
extern volatile uint32_t g_xtal0Freq;

/*! @brief The external XTAL32/EXTAL32/RTC_CLKIN clock frequency.
 *
 * The XTAL32/EXTAL32/RTC_CLKIN clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetXtal32Freq to set the value in the clock driver.
 *
 * This is important for the multicore platforms where one core needs to set up
 * the clock. All other cores need to call the CLOCK_SetXtal32Freq
 * to get a valid clock frequency.
 */
extern volatile uint32_t g_xtal32Freq;

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (48000000UL)
#endif
/*! @brief Clock ip name array for DMAMUX. */
#define DMAMUX_CLOCKS  \
    {                  \
        kCLOCK_Dmamux0 \
    }

/*! @brief Clock ip name array for RTC. */
#define RTC_CLOCKS  \
    {               \
        kCLOCK_Rtc0 \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS  \
    {               \
        kCLOCK_Sai0 \
    }

/*! @brief Clock ip name array for SPI. */
#define SPI_CLOCKS               \
    {                            \
        kCLOCK_Spi0, kCLOCK_Spi1 \
    }

/*! @brief Clock ip name array for SLCD. */
#define SLCD_CLOCKS  \
    {                \
        kCLOCK_Slcd0 \
    }

/*! @brief Clock ip name array for PIT. */
#define PIT_CLOCKS  \
    {               \
        kCLOCK_Pit0 \
    }

/*! @brief Clock ip name array for PORT. */
#define PORT_CLOCKS                                                          \
    {                                                                        \
        kCLOCK_PortA, kCLOCK_PortB, kCLOCK_PortC, kCLOCK_PortD, kCLOCK_PortE \
    }

/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                  \
    {                                  \
        kCLOCK_Lpuart0, kCLOCK_Lpuart1 \
    }

/*! @brief Clock ip name array for DAC. */
#define DAC_CLOCKS  \
    {               \
        kCLOCK_Dac0 \
    }

/*! @brief Clock ip name array for LPTMR. */
#define LPTMR_CLOCKS  \
    {                 \
        kCLOCK_Lptmr0 \
    }

/*! @brief Clock ip name array for ADC16. */
#define ADC16_CLOCKS \
    {                \
        kCLOCK_Adc0  \
    }

/*! @brief Clock ip name array for FLEXIO. */
#define FLEXIO_CLOCKS  \
    {                  \
        kCLOCK_Flexio0 \
    }

/*! @brief Clock ip name array for VREF. */
#define VREF_CLOCKS  \
    {                \
        kCLOCK_Vref0 \
    }

/*! @brief Clock ip name array for DMA. */
#define DMA_CLOCKS  \
    {               \
        kCLOCK_Dma0 \
    }

/*! @brief Clock ip name array for UART. */
#define UART_CLOCKS                                      \
    {                                                    \
        kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_Uart2 \
    }

/*! @brief Clock ip name array for TPM. */
#define TPM_CLOCKS                            \
    {                                         \
        kCLOCK_Tpm0, kCLOCK_Tpm1, kCLOCK_Tpm2 \
    }

/*! @brief Clock ip name array for I2C. */
#define I2C_CLOCKS               \
    {                            \
        kCLOCK_I2c0, kCLOCK_I2c1 \
    }

/*! @brief Clock ip name array for FTF. */
#define FTF_CLOCKS  \
    {               \
        kCLOCK_Ftf0 \
    }

/*! @brief Clock ip name array for CMP. */
#define CMP_CLOCKS  \
    {               \
        kCLOCK_Cmp0 \
    }

/*!
 * @brief LPO clock frequency.
 */
#define LPO_CLK_FREQ 1000U

/*! @brief Peripherals clock source definition. */
#define SYS_CLK kCLOCK_CoreSysClk
#define BUS_CLK kCLOCK_BusClk

#define I2C0_CLK_SRC SYS_CLK
#define I2C1_CLK_SRC SYS_CLK
#define SPI0_CLK_SRC BUS_CLK
#define SPI1_CLK_SRC SYS_CLK
#define UART2_CLK_SRC BUS_CLK

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{

    /* ----------------------------- System layer clock -------------------------------*/
    kCLOCK_CoreSysClk,    /*!< Core/system clock                                         */
    kCLOCK_PlatClk,       /*!< Platform clock                                            */
    kCLOCK_BusClk,        /*!< Bus clock                                                 */
    kCLOCK_FlexBusClk,    /*!< FlexBus clock                                             */
    kCLOCK_FlashClk,      /*!< Flash clock                                               */
    kCLOCK_FastPeriphClk, /*!< Fast peripheral clock                                     */
    kCLOCK_PllFllSelClk,  /*!< The clock after SIM[PLLFLLSEL].                           */

    /* ---------------------------------- OSC clock -----------------------------------*/
    kCLOCK_Er32kClk,       /*!< External reference 32K clock (ERCLK32K)                   */
    kCLOCK_Osc0ErClk,      /*!< OSC0 external reference clock (OSC0ERCLK)                 */
    kCLOCK_Osc1ErClk,      /*!< OSC1 external reference clock (OSC1ERCLK)                 */
    kCLOCK_Osc0ErClkUndiv, /*!< OSC0 external reference undivided clock(OSC0ERCLK_UNDIV). */

    /* ----------------------------- MCG and MCG-Lite clock ---------------------------*/
    kCLOCK_McgFixedFreqClk,   /*!< MCG fixed frequency clock (MCGFFCLK)                      */
    kCLOCK_McgInternalRefClk, /*!< MCG internal reference clock (MCGIRCLK)                   */
    kCLOCK_McgFllClk,         /*!< MCGFLLCLK                                                 */
    kCLOCK_McgPll0Clk,        /*!< MCGPLL0CLK                                                */
    kCLOCK_McgPll1Clk,        /*!< MCGPLL1CLK                                                */
    kCLOCK_McgExtPllClk,      /*!< EXT_PLLCLK                                                */
    kCLOCK_McgPeriphClk,      /*!< MCG peripheral clock (MCGPCLK)                            */
    kCLOCK_McgIrc48MClk,      /*!< MCG IRC48M clock                                          */

    /* --------------------------------- Other clock ----------------------------------*/
    kCLOCK_LpoClk, /*!< LPO clock                                                 */

} clock_name_t;

/*! @brief USB clock source definition. */
typedef enum _clock_usb_src
{
    kCLOCK_UsbSrcIrc48M = SIM_SOPT2_USBSRC(1U), /*!< Use IRC48M.    */
    kCLOCK_UsbSrcExt    = SIM_SOPT2_USBSRC(0U)  /*!< Use USB_CLKIN. */
} clock_usb_src_t;
/*------------------------------------------------------------------------------

 clock_gate_t definition:

 31                              16                              0
 -----------------------------------------------------------------
 | SIM_SCGC register offset       |   control bit offset in SCGC |
 -----------------------------------------------------------------

 For example, the SDHC clock gate is controlled by SIM_SCGC3[17], the
 SIM_SCGC3 offset in SIM is 0x1030, then kCLOCK_GateSdhc0 is defined as

              kCLOCK_GateSdhc0 = (0x1030 << 16) | 17;

------------------------------------------------------------------------------*/

#define CLK_GATE_REG_OFFSET_SHIFT 16U
#define CLK_GATE_REG_OFFSET_MASK 0xFFFF0000U
#define CLK_GATE_BIT_SHIFT_SHIFT 0U
#define CLK_GATE_BIT_SHIFT_MASK 0x0000FFFFU

#define CLK_GATE_DEFINE(reg_offset, bit_shift)                                            \
    ((((uint32_t)(reg_offset) << CLK_GATE_REG_OFFSET_SHIFT) & CLK_GATE_REG_OFFSET_MASK) | \
     (((uint32_t)(bit_shift) << CLK_GATE_BIT_SHIFT_SHIFT) & CLK_GATE_BIT_SHIFT_MASK))

#define CLK_GATE_ABSTRACT_REG_OFFSET(x) (((x)&CLK_GATE_REG_OFFSET_MASK) >> CLK_GATE_REG_OFFSET_SHIFT)
#define CLK_GATE_ABSTRACT_BITS_SHIFT(x) (((x)&CLK_GATE_BIT_SHIFT_MASK) >> CLK_GATE_BIT_SHIFT_SHIFT)

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,
    kCLOCK_I2c0      = CLK_GATE_DEFINE(0x1034U, 6U),
    kCLOCK_I2c1      = CLK_GATE_DEFINE(0x1034U, 7U),
    kCLOCK_Uart2     = CLK_GATE_DEFINE(0x1034U, 12U),
    kCLOCK_Usbfs0    = CLK_GATE_DEFINE(0x1034U, 18U),
    kCLOCK_Cmp0      = CLK_GATE_DEFINE(0x1034U, 19U),
    kCLOCK_Vref0     = CLK_GATE_DEFINE(0x1034U, 20U),
    kCLOCK_Spi0      = CLK_GATE_DEFINE(0x1034U, 22U),
    kCLOCK_Spi1      = CLK_GATE_DEFINE(0x1034U, 23U),

    kCLOCK_Lptmr0  = CLK_GATE_DEFINE(0x1038U, 0U),
    kCLOCK_PortA   = CLK_GATE_DEFINE(0x1038U, 9U),
    kCLOCK_PortB   = CLK_GATE_DEFINE(0x1038U, 10U),
    kCLOCK_PortC   = CLK_GATE_DEFINE(0x1038U, 11U),
    kCLOCK_PortD   = CLK_GATE_DEFINE(0x1038U, 12U),
    kCLOCK_PortE   = CLK_GATE_DEFINE(0x1038U, 13U),
    kCLOCK_Slcd0   = CLK_GATE_DEFINE(0x1038U, 19U),
    kCLOCK_Lpuart0 = CLK_GATE_DEFINE(0x1038U, 20U),
    kCLOCK_Lpuart1 = CLK_GATE_DEFINE(0x1038U, 21U),
    kCLOCK_Flexio0 = CLK_GATE_DEFINE(0x1038U, 31U),

    kCLOCK_Ftf0    = CLK_GATE_DEFINE(0x103CU, 0U),
    kCLOCK_Dmamux0 = CLK_GATE_DEFINE(0x103CU, 1U),
    kCLOCK_Sai0    = CLK_GATE_DEFINE(0x103CU, 15U),
    kCLOCK_Pit0    = CLK_GATE_DEFINE(0x103CU, 23U),
    kCLOCK_Tpm0    = CLK_GATE_DEFINE(0x103CU, 24U),
    kCLOCK_Tpm1    = CLK_GATE_DEFINE(0x103CU, 25U),
    kCLOCK_Tpm2    = CLK_GATE_DEFINE(0x103CU, 26U),
    kCLOCK_Adc0    = CLK_GATE_DEFINE(0x103CU, 27U),
    kCLOCK_Rtc0    = CLK_GATE_DEFINE(0x103CU, 29U),
    kCLOCK_Dac0    = CLK_GATE_DEFINE(0x103CU, 31U),

    kCLOCK_Dma0 = CLK_GATE_DEFINE(0x1040U, 8U),
} clock_ip_name_t;

/*!@brief SIM configuration structure for clock setting. */
typedef struct _sim_clock_config
{
    uint8_t er32kSrc; /*!< ERCLK32K source selection.   */
    uint32_t clkdiv1; /*!< SIM_CLKDIV1.                 */
} sim_clock_config_t;

/*! @brief Oscillator capacitor load setting.*/
enum _osc_cap_load
{
    kOSC_Cap2P  = OSC_CR_SC2P_MASK, /*!< 2  pF capacitor load */
    kOSC_Cap4P  = OSC_CR_SC4P_MASK, /*!< 4  pF capacitor load */
    kOSC_Cap8P  = OSC_CR_SC8P_MASK, /*!< 8  pF capacitor load */
    kOSC_Cap16P = OSC_CR_SC16P_MASK /*!< 16 pF capacitor load */
};

/*! @brief OSCERCLK enable mode. */
enum _oscer_enable_mode
{
    kOSC_ErClkEnable       = OSC_CR_ERCLKEN_MASK, /*!< Enable.              */
    kOSC_ErClkEnableInStop = OSC_CR_EREFSTEN_MASK /*!< Enable in stop mode. */
};

/*! @brief The OSC configuration for OSCERCLK. */
typedef struct _oscer_config
{
    uint8_t enableMode; /*!< OSCERCLK enable mode. OR'ed value of \ref _oscer_enable_mode. */

} oscer_config_t;

/*! @brief The OSC work mode. */
typedef enum _osc_mode
{
    kOSC_ModeExt         = 0U,                                    /*!< Use external clock.   */
    kOSC_ModeOscLowPower = MCG_C2_EREFS0_MASK,                    /*!< Oscillator low power. */
    kOSC_ModeOscHighGain = MCG_C2_EREFS0_MASK | MCG_C2_HGO0_MASK, /*!< Oscillator high gain. */
} osc_mode_t;

/*!
 * @brief OSC Initialization Configuration Structure
 *
 * Defines the configuration data structure to initialize the OSC.
 * When porting to a new board, set the following members
 * according to the board settings:
 * 1. freq: The external frequency.
 * 2. workMode: The OSC module mode.
 */
typedef struct _osc_config
{
    uint32_t freq;              /*!< External clock frequency.    */
    uint8_t capLoad;            /*!< Capacitor load setting.      */
    osc_mode_t workMode;        /*!< OSC work mode setting.       */
    oscer_config_t oscerConfig; /*!< Configuration for OSCERCLK.  */
} osc_config_t;

/*! @brief MCG_Lite clock source selection. */
typedef enum _mcglite_clkout_src
{
    kMCGLITE_ClkSrcHirc, /*!< MCGOUTCLK source is HIRC */
    kMCGLITE_ClkSrcLirc, /*!< MCGOUTCLK source is LIRC */
    kMCGLITE_ClkSrcExt,  /*!< MCGOUTCLK source is external clock source */
    kMCGLITE_ClkSrcReserved
} mcglite_clkout_src_t;

/*! @brief MCG_Lite LIRC select. */
typedef enum _mcglite_lirc_mode
{
    kMCGLITE_Lirc2M, /*!< Slow internal reference(LIRC) 2 MHz clock selected */
    kMCGLITE_Lirc8M, /*!< Slow internal reference(LIRC) 8 MHz clock selected */
} mcglite_lirc_mode_t;

/*! @brief MCG_Lite divider factor selection for clock source*/
typedef enum _mcglite_lirc_div
{
    kMCGLITE_LircDivBy1 = 0U, /*!< Divider is 1    */
    kMCGLITE_LircDivBy2,      /*!< Divider is 2    */
    kMCGLITE_LircDivBy4,      /*!< Divider is 4    */
    kMCGLITE_LircDivBy8,      /*!< Divider is 8    */
    kMCGLITE_LircDivBy16,     /*!< Divider is 16   */
    kMCGLITE_LircDivBy32,     /*!< Divider is 32   */
    kMCGLITE_LircDivBy64,     /*!< Divider is 64   */
    kMCGLITE_LircDivBy128     /*!< Divider is 128  */
} mcglite_lirc_div_t;

/*! @brief MCG_Lite clock mode definitions */
typedef enum _mcglite_mode
{
    kMCGLITE_ModeHirc48M, /*!< Clock mode is HIRC 48 M  */
    kMCGLITE_ModeLirc8M,  /*!< Clock mode is LIRC 8 M   */
    kMCGLITE_ModeLirc2M,  /*!< Clock mode is LIRC 2 M   */
    kMCGLITE_ModeExt,     /*!< Clock mode is EXT       */
    kMCGLITE_ModeError    /*!< Unknown mode            */
} mcglite_mode_t;

/*! @brief MCG internal reference clock (MCGIRCLK) enable mode definition. */
enum _mcglite_irclk_enable_mode
{
    kMCGLITE_IrclkEnable       = MCG_C1_IRCLKEN_MASK, /*!< MCGIRCLK enable.              */
    kMCGLITE_IrclkEnableInStop = MCG_C1_IREFSTEN_MASK /*!< MCGIRCLK enable in stop mode. */
};

/*! @brief MCG_Lite configure structure for mode change. */
typedef struct _mcglite_config
{
    mcglite_clkout_src_t outSrc;  /*!< MCGOUT clock select.                */
    uint8_t irclkEnableMode;      /*!< MCGIRCLK enable mode, OR'ed value of _mcglite_irclk_enable_mode. */
    mcglite_lirc_mode_t ircs;     /*!< MCG_C2[IRCS].                       */
    mcglite_lirc_div_t fcrdiv;    /*!< MCG_SC[FCRDIV].                     */
    mcglite_lirc_div_t lircDiv2;  /*!< MCG_MC[LIRC_DIV2].                  */
    bool hircEnableInNotHircMode; /*!< HIRC enable when not in HIRC mode.  */
} mcglite_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    uint32_t regAddr = SIM_BASE + CLK_GATE_ABSTRACT_REG_OFFSET((uint32_t)name);
    (*(volatile uint32_t *)regAddr) |= (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT((uint32_t)name));
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    uint32_t regAddr = SIM_BASE + CLK_GATE_ABSTRACT_REG_OFFSET((uint32_t)name);
    (*(volatile uint32_t *)regAddr) &= ~(1UL << CLK_GATE_ABSTRACT_BITS_SHIFT((uint32_t)name));
}

/*!
 * @brief Set ERCLK32K source.
 *
 * @param src The value to set ERCLK32K clock source.
 */
static inline void CLOCK_SetEr32kClock(uint32_t src)
{
    SIM->SOPT1 = ((SIM->SOPT1 & ~SIM_SOPT1_OSC32KSEL_MASK) | SIM_SOPT1_OSC32KSEL(src));
}

/*!
 * @brief Set LPUART0 clock source.
 *
 * @param src The value to set LPUART0 clock source.
 */
static inline void CLOCK_SetLpuart0Clock(uint32_t src)
{
    SIM->SOPT2 = ((SIM->SOPT2 & ~SIM_SOPT2_LPUART0SRC_MASK) | SIM_SOPT2_LPUART0SRC(src));
}

/*!
 * @brief Set LPUART1 clock source.
 *
 * @param src The value to set LPUART1 clock source.
 */
static inline void CLOCK_SetLpuart1Clock(uint32_t src)
{
    SIM->SOPT2 = ((SIM->SOPT2 & ~SIM_SOPT2_LPUART1SRC_MASK) | SIM_SOPT2_LPUART1SRC(src));
}

/*!
 * @brief Set TPM clock source.
 *
 * @param src The value to set TPM clock source.
 */
static inline void CLOCK_SetTpmClock(uint32_t src)
{
    SIM->SOPT2 = ((SIM->SOPT2 & ~SIM_SOPT2_TPMSRC_MASK) | SIM_SOPT2_TPMSRC(src));
}

/*!
 * @brief Set FLEXIO clock source.
 *
 * @param src The value to set FLEXIO clock source.
 */
static inline void CLOCK_SetFlexio0Clock(uint32_t src)
{
    SIM->SOPT2 = ((SIM->SOPT2 & ~SIM_SOPT2_FLEXIOSRC_MASK) | SIM_SOPT2_FLEXIOSRC(src));
}

/*! @brief Enable USB FS clock.
 *
 * @param src  USB FS clock source.
 * @param freq The frequency specified by src.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB FS clock.
 */
bool CLOCK_EnableUsbfs0Clock(clock_usb_src_t src, uint32_t freq);

/*! @brief Disable USB FS clock.
 *
 * Disable USB FS clock.
 */
static inline void CLOCK_DisableUsbfs0Clock(void)
{
    CLOCK_DisableClock(kCLOCK_Usbfs0);
}

/*!
 * @brief Set CLKOUT source.
 *
 * @param src The value to set CLKOUT source.
 */
static inline void CLOCK_SetClkOutClock(uint32_t src)
{
    SIM->SOPT2 = ((SIM->SOPT2 & ~SIM_SOPT2_CLKOUTSEL_MASK) | SIM_SOPT2_CLKOUTSEL(src));
}

/*!
 * @brief Set RTC_CLKOUT source.
 *
 * @param src The value to set RTC_CLKOUT source.
 */
static inline void CLOCK_SetRtcClkOutClock(uint32_t src)
{
    SIM->SOPT2 = ((SIM->SOPT2 & ~SIM_SOPT2_RTCCLKOUTSEL_MASK) | SIM_SOPT2_RTCCLKOUTSEL(src));
}

/*!
 * @brief System clock divider
 *
 * Set the SIM_CLKDIV1[OUTDIV1], SIM_CLKDIV1[OUTDIV4].
 *
 * @param outdiv1 Clock 1 output divider value.
 *
 * @param outdiv4 Clock 4 output divider value.
 */
static inline void CLOCK_SetOutDiv(uint32_t outdiv1, uint32_t outdiv4)
{
    SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(outdiv1) | SIM_CLKDIV1_OUTDIV4(outdiv4);
}

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 * The MCG must be properly configured before using this function.
 *
 * @param clockName Clock names defined in clock_name_t
 * @return Clock frequency value in Hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*!
 * @brief Get the core clock or system clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCoreSysClkFreq(void);

/*!
 * @brief Get the platform clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetPlatClkFreq(void);

/*!
 * @brief Get the bus clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetBusClkFreq(void);

/*!
 * @brief Get the flash clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFlashClkFreq(void);

/*!
 * @brief Get the external reference 32K clock frequency (ERCLK32K).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetEr32kClkFreq(void);

/*!
 * @brief Get the OSC0 external reference clock frequency (OSC0ERCLK).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc0ErClkFreq(void);

/*!
 * @brief Set the clock configure in SIM module.
 *
 * This function sets system layer clock settings in SIM module.
 *
 * @param config Pointer to the configure structure.
 */
void CLOCK_SetSimConfig(sim_clock_config_t const *config);

/*!
 * @brief Set the system clock dividers in SIM to safe value.
 *
 * The system level clocks (core clock, bus clock, flexbus clock and flash clock)
 * must be in allowed ranges. During MCG clock mode switch, the MCG output clock
 * changes then the system level clocks may be out of range. This function could
 * be used before MCG mode change, to make sure system level clocks are in allowed
 * range.
 */
static inline void CLOCK_SetSimSafeDivs(void)
{
    SIM->CLKDIV1 = 0x10030000U;
}

/*!
 * @name MCG_Lite clock frequency
 * @{
 */

/*!
 * @brief Gets the MCG_Lite output clock (MCGOUTCLK) frequency.
 *
 * This function gets the MCG_Lite output clock frequency in Hz based on the current
 * MCG_Lite register value.
 *
 * @return The frequency of MCGOUTCLK.
 */
uint32_t CLOCK_GetOutClkFreq(void);

/*!
 * @brief Gets the MCG internal reference clock (MCGIRCLK) frequency.
 *
 * This function gets the MCG_Lite internal reference clock frequency in Hz based
 * on the current MCG register value.
 *
 * @return The frequency of MCGIRCLK.
 */
uint32_t CLOCK_GetInternalRefClkFreq(void);

/*!
 * @brief Gets the current MCGPCLK frequency.
 *
 * This function gets the MCGPCLK frequency in Hz based on the current MCG_Lite
 * register settings.
 *
 * @return The frequency of MCGPCLK.
 */
uint32_t CLOCK_GetPeriphClkFreq(void);

/*! @}*/

/*!
 * @name MCG_Lite mode.
 * @{
 */

/*!
 * @brief Gets the current MCG_Lite mode.
 *
 * This function checks the MCG_Lite registers and determines the current MCG_Lite mode.
 *
 * @return The current MCG_Lite mode or error code.
 */
mcglite_mode_t CLOCK_GetMode(void);

/*!
 * @brief Sets the MCG_Lite configuration.
 *
 * This function configures the MCG_Lite, includes the output clock source, MCGIRCLK
 * settings, HIRC settings, and so on. See @ref mcglite_config_t for details.
 *
 * @param  targetConfig Pointer to the target MCG_Lite mode configuration structure.
 * @return Error code.
 */
status_t CLOCK_SetMcgliteConfig(mcglite_config_t const *targetConfig);

/*! @}*/

/*!
 * @name OSC configuration
 * @{
 */

/*!
 * @brief Configures the OSC external reference clock (OSCERCLK).
 *
 * This function configures the OSC external reference clock (OSCERCLK).
 * This is an example to enable the OSCERCLK in normal mode and stop mode, and set
 * the output divider to 1.
 *
   @code
   oscer_config_t config =
   {
       .enableMode = kOSC_ErClkEnable | kOSC_ErClkEnableInStop,
       .erclkDiv   = 1U,
   };

   OSC_SetExtRefClkConfig(OSC, &config);
   @endcode
 *
 * @param base   OSC peripheral address.
 * @param config Pointer to the configuration structure.
 */
static inline void OSC_SetExtRefClkConfig(OSC_Type *base, oscer_config_t const *config)
{
    uint8_t reg = base->CR;

    reg &= (uint8_t)(~(OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK));
    reg |= config->enableMode;

    base->CR = reg;
}

/*!
 * @brief Sets the capacitor load configuration for the oscillator.
 *
 * This function sets the specified capacitor configuration for the oscillator.
 * This should be done in the early system level initialization function call
 * based on the system configuration.
 *
 * @param base   OSC peripheral address.
 * @param capLoad OR'ed value for the capacitor load option.See \ref _osc_cap_load.
 *
 * Example:
   @code
   OSC_SetCapLoad(OSC, kOSC_Cap2P | kOSC_Cap8P);
   @endcode
 */

static inline void OSC_SetCapLoad(OSC_Type *base, uint8_t capLoad)
{
    uint8_t reg = base->CR;

    reg &= (uint8_t)(~(OSC_CR_SC2P_MASK | OSC_CR_SC4P_MASK | OSC_CR_SC8P_MASK | OSC_CR_SC16P_MASK));
    reg |= capLoad;

    base->CR = reg;
}

/*!
 * @brief Initializes the OSC0.
 *
 * This function initializes the OSC0 according to the board configuration.
 *
 * @param  config Pointer to the OSC0 configuration structure.
 */
void CLOCK_InitOsc0(osc_config_t const *config);

/*!
 * @brief Deinitializes the OSC0.
 *
 * This function deinitializes the OSC0.
 */
void CLOCK_DeinitOsc0(void);

/*! @}*/

/*!
 * @name External clock frequency
 * @{
 */

/*!
 * @brief Sets the XTAL0 frequency based on board settings.
 *
 * @param freq The XTAL0/EXTAL0 input clock frequency in Hz.
 */
static inline void CLOCK_SetXtal0Freq(uint32_t freq)
{
    g_xtal0Freq = freq;
}

/*!
 * @brief Sets the XTAL32/RTC_CLKIN frequency based on board settings.
 *
 * @param freq The XTAL32/EXTAL32/RTC_CLKIN input clock frequency in Hz.
 */
static inline void CLOCK_SetXtal32Freq(uint32_t freq)
{
    g_xtal32Freq = freq;
}
/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
