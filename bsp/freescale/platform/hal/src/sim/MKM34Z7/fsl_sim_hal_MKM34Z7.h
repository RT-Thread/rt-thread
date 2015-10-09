/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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

#if !defined(__FSL_SIM_HAL_KM34Z2567_H__)
#define __FSL_SIM_HAL_KM34Z2567_H__

#include <assert.h>

/*! @addtogroup sim_hal_km34z7 */
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief WDOG clock source select */
typedef enum _clock_wdog_src
{
    kClockWdogSrcLpoClk,       /* LPO       clock  */
    kClockWdogSrcOsc32kClk,    /* OSC32K    clock  */
    kClockWdogSrcMcgIrClk,     /* MCGIRCLK  clock  */
    kClockWdogSrcEr32kClk      /* ERCLK32K  clock  */
} clock_wdog_src_t;

/*! @brief AFE clock source select. SIM_MISC_CTL[AFECLKSEL] */
typedef enum _clock_afe_src
{
    kClockAfeSrcPllClk,       /* MCG PLL clock */
    kClockAfeSrcFllClk,       /* MCG FLL clock */
    kClockAfeSrcOscClk,       /* OSC clock */  
    kClockAfeSrcExt           /* External clock input */
} clock_afe_src_t;

/*! @brief LPTMR clock source select, table 5-2 */
typedef enum _clock_lptmr_src
{
    kClockLptmrSrcMcgIrClk,        /* MCGIRC    clock */
    kClockLptmrSrcLpoClk,          /* LPO       clock */
    kClockLptmrSrcEr32kClk,        /* ERCLK32K  clock */
    kClockLptmrSrcOsc0erClk        /* OSCERCLK  clock */
} clock_lptmr_src_t;

/*! @brief LCD clock source select, table 5-2  */
typedef enum _clock_slcd_src
{
    kClockSLcdSrcMcgIrClk,        /* MCGIRC    clock */
    kClockSLcdSrcOsc32kClk        /* OSC32KCLK clock */
} clock_slcd_src_t;

/*! @brief SIM external reference clock source select (OSC32KSEL) */
typedef enum _clock_er32k_src
{
    kClockEr32kSrcOsc32kClk  = 0U,     /* OSC 32k  clock */
    kClockEr32kSrcEr32kClk   = 1U,     /* ERCLK32K clock */
    kClockEr32kSrcMcgIrClk   = 2U,     /* MCGIRCLK clock */
    kClockEr32kSrcLpo        = 3U      /* LPO      clock */
} clock_er32k_src_t;

/*! @brief SIM CLKOUT_SEL clock source select */
typedef enum _clock_clkout_src
{
    kClockClkoutGatedCoreClk = 1U,  /* Gated Core   clock */
    kClockClkoutBusFlashClk  = 2U,  /* Bus          clock */
    kClockClkoutLpoClk       = 3U,  /* LPO          clock */
    kClockClkoutMcgIrClk     = 4U,  /* MCGIRCLK     clock */
    kClockClkoutOsc32kSel    = 5U,  /* SOPT1[19:18] clock selection */
    kClockClkoutOsc0erClk    = 6U,  /* OSC0ER       clock */
    kClockClkoutMcgPllClk    = 7U   /* MCGPLL       clock */      
} clock_clkout_src_t;

/*! @brief SIM RTCCLKSEL clock source select, SIM_MISC_CTL */
typedef enum _clock_rtcout_src
{
    kClockRtcSrcRtcOsc32kClk,      /* RTC OSC 32K clock  */
    kClockRtcSrcMcgIrClk           /* MCGIRC 32KHz clock */
} clock_rtcout_src_t; 

/*! @brief SIM LPUART clock source selection, SIM_CTRL_REG */
typedef enum _clock_lpuart_src
{
    kClockLpuartSrcNone,     /* Clock disabled.    */
    kClockLpuartSrcPllFllSel,   /* MCGPLL/FLL clock.    */
    kClockLpuartSrcOsc0erClk,   /* OSCERCLK clock.      */
    kClockLpuartSrcMcgIrClk     /* MCGIRCLK             */
} clock_lpuart_src_t;

/*! @brief SIM TMR counter freeze control, SIM_CTRL_REG */
typedef enum _sim_tmr_cnt_freeze_sel
{
    kSimTmrCntFreezeEnable,       /* QTMR0 counter is frozen.. */
    kSimTmrCntFreezeDisable       /* QTMR0 counter starts counting and all the 4 channel OFLAGs are reset. */
} sim_tmr_cnt_freeze_sel_t;

/*! @brief SIM AFE clock out dividing setting, SIM_CTRL_REG */
typedef enum _sim_afe_clk_div_sel
{
    kSimAfeClkDivEnable,       /* AFE output clock is divided by AFE clock prescaler. */
    kSimAfeClkDivDisable       /* AFE output clock is NOT divided by AFE clock prescaler.. */
} sim_afe_clk_div_sel_t;

/*! @brief SIM XBAR clock out source select, SIM_CTRL_REG */
typedef enum _clock_xbar_out_src
{
    kClockXbarOutGatedCoreClk = 1U,  /* Gated Core   clock */
    kClockXbarOutBusFlashClk  = 2U,  /* Bus          clock */
    kClockXbarOutLpoClk       = 3U,  /* LPO          clock */
    kClockXbarOutMcgIrClk     = 4U,  /* MCGIRCLK     clock */
    kClockXbarOutOsc32kSel    = 5U,  /* SOPT1[19:18] clock selection */
    kClockXbarOutOsc0erClk    = 6U,  /* OSC0ER       clock */
    kClockXbarOutMcgPllClk    = 7U   /* MCGPLL       clock */      
} clock_xbar_out_src_t;

/*! @brief SIM PLLFLLSEL clock source select, SIM_CTRL_REG */
typedef enum _clock_pllfll_sel
{
    kClockPllFllSelFll    = 0U,    /* Fll  clock                  */
    kClockPllFllSelPll    = 1U,    /* Pll0 clock                  */
    kClockPllFllSelBus    = 2U,    /* BUS  clock                  */
    kClockPllFllSelOsc32k = 3U     /* OSC32K from RTC oscillator  */
} clock_pllfll_sel_t;

/*! @brief SIM SPI output signal inverting setting, SIM_CTRL_REG */
typedef enum _sim_spi_out_invert_sel
{
    kSimSpiOutInvertSel0,      /* not inverted. */
    kSimSpiOutInvertSel1       /* inverted.     */
} sim_spi_out_invert_sel_t;

/*! @brief SIM SAR ADC trigger clock select, SIM_CTRL_REG */
typedef enum _sim_sadc_trg_clk_sel
{
    kSimSAdcTrgClksel0,      /* SAR ADC trigger clock selection 0 */
    kSimSAdcTrgClksel1,      /* SAR ADC trigger clock selection 1 */
    kSimSAdcTrgClksel2,      /* SAR ADC trigger clock selection 2 */
    kSimSAdcTrgClksel3       /* SAR ADC trigger clock selection 3 */
} sim_sadc_trg_clk_sel_t;

/*! @brief SIM LP timer channel x source selection, SIM_SOPT1_CFG */
typedef enum _sim_lptmr_src_sel
{
    kSimLptmrSrcSel0,      /* source selection 0 for LPTMR channel x. */
    kSimLptmrSrcSel1,      /* source selection 1 for LPTMR channel x. */
    kSimLptmrSrcSel2       /* source selection 2 for LPTMR channel x. */
} sim_lptmr_src_sel_t;

/*! @brief SIM VrefBuffer input selection, SIM_MISC_CTL */
typedef enum _sim_vref_buff_input_sel
{
    kSimVrefBuffInputSel0,      /* source selection 0 for VrefBuffer input. */
    kSimVrefBuffInputSel1       /* source selection 1 for VrefBuffer input. */
} sim_vref_buff_input_sel_t;

/*! @brief SIM Quadtimer channel x primary count source selection, SIM_MISC_CTL */
typedef enum _sim_tmr_Primary_src_sel
{
    kSimTmrPrimarySrcSel0,    /* source selection 0 for Quadtimer channel x. */
    kSimTmrPrimarySrcSel1,    /* source selection 1 for Quadtimer channel x. */
    kSimTmrPrimarySrcSel2,    /* source selection 2 for Quadtimer channel x. */
    kSimTmrPrimarySrcDisable  /* disabled for Quadtimer channel x. */
} sim_tmr_Primary_src_sel_t;

/*! @brief SIM Quadtimer channel x secondary count source selection */
typedef enum _sim_tmr_second_src_sel
{
    kSimTmrSecondSrcSel0,    /* source selection 0 for Quadtimer channel x. */
    kSimTmrSecondSrcSel1     /* source selection 1 for Quadtimer channel x. */
} sim_tmr_sencond_src_sel_t;

/*! @brief SIM Timer channel 0 PLL clock selection, SIM_MISC_CTL */
typedef enum _clock_tmr0_pll_src
{
    kSimTmr0PllClkSel0,    /* clock selection 0 for Timer CH0. */
    kSimTmr0PllClkSel1     /* clock selection 1 for Timer CH0. */
} clock_tmr0_pll_src_t;

/*! @brief SIM External watchdog monitor input selection, SIM_MISC_CTL */
typedef enum _sim_ewm_input_sel
{
    kSimEwmInputSel0,    /* input selection 0 for EWM. */
    kSimEwmInputSel1     /* input selection 1 for EWM. */
} sim_ewm_input_sel_t;

/*! @brief SIM UARTx IRDA selection, SIM_MISC_CTL */
typedef enum _sim_uart_irda_sel
{
    kSimUartIrdaSel0,    /* IRDA selection 0 for UARTx. */
    kSimUartIrdaSel1     /* IRDA selection 1 for UARTx. */
} sim_uart_irda_sel_t;

/*! @brief SIM UARTx IRDA modulation type selection, SIM_MISC_CTL */
typedef enum _sim_uart_irda_type_sel
{
    kSimUartIrdaTypeSelA,    /* IRDA modulation type selection A for UARTx. */
    kSimUartIrdaTypeSelB     /* IRDA modulation type selection B for UARTx. */
} sim_uart_irda_type_sel_t;

/*! @brief SIM, Controls the direction of the AFE CLK pin, SIM_MISC_CTL */
typedef enum _sim_afe_clk_pad_dir
{
    kSimAfeClkPadDirInput,     /* AFE CLK PAD is input. */
    kSimAfeClkPadDirOutput     /* AFE CLK PAD is output. */
}sim_afe_clk_pad_dir_t;

/*! @brief SIM DMA done selection, SIM_MISC_CTL */
typedef enum _sim_dma_done_sel
{
    kSimDmaDoneSel0,          /* DMA0. */
    kSimDmaDoneSel1,          /* DMA1. */
    kSimDmaDoneSel2,          /* DMA2. */
    kSimDmaDoneSel3           /* DMA3. */
} sim_dma_done_sel_t;

/*! @brief SIM ADC trigger source selection, SIM_MISC_CTL */
typedef enum _sim_adc_trg_src_sel
{
    kSimAdcTrgSelXbar,        /* XBAR to trigger ADC.      */
    kSimAdcTrgSelPdb          /* PDB output to trigger ADC.*/
} sim_adc_trg_src_sel_t;

/* SCGC bit index. */
#define FSL_SIM_SCGC_BIT(SCGCx, n) (((SCGCx-1U)<<5U) + n)

typedef enum _sim_clock_gate_name
{
    kSimClockGateEwm0         = FSL_SIM_SCGC_BIT(4U, 1U),
    kSimClockGateI2c0         = FSL_SIM_SCGC_BIT(4U, 7U),
    kSimClockGateI2c1         = FSL_SIM_SCGC_BIT(4U, 8U),
    kSimClockGateUart0        = FSL_SIM_SCGC_BIT(4U, 10U),
    kSimClockGateUart1        = FSL_SIM_SCGC_BIT(4U, 11U),
    kSimClockGateUart2        = FSL_SIM_SCGC_BIT(4U, 12U),
    kSimClockGateUart3        = FSL_SIM_SCGC_BIT(4U, 13U),
    kSimClockGateVref0        = FSL_SIM_SCGC_BIT(4U, 15U),
    kSimClockGateCmp0         = FSL_SIM_SCGC_BIT(4U, 18U),
    kSimClockGateSpi0         = FSL_SIM_SCGC_BIT(4U, 21U),
    kSimClockGateSpi1         = FSL_SIM_SCGC_BIT(4U, 22U),
    
    kSimClockGateSlcd0        = FSL_SIM_SCGC_BIT(5U, 3U),
    kSimClockGatePortA        = FSL_SIM_SCGC_BIT(5U, 6U),
    kSimClockGatePortB        = FSL_SIM_SCGC_BIT(5U, 7U),
    kSimClockGatePortC        = FSL_SIM_SCGC_BIT(5U, 8U),
    kSimClockGatePortD        = FSL_SIM_SCGC_BIT(5U, 9U),
    kSimClockGatePortE        = FSL_SIM_SCGC_BIT(5U, 10U),
    kSimClockGatePortF        = FSL_SIM_SCGC_BIT(5U, 11U),
    kSimClockGatePortG        = FSL_SIM_SCGC_BIT(5U, 12U),
    kSimClockGatePortH        = FSL_SIM_SCGC_BIT(5U, 13U),
    kSimClockGatePortI        = FSL_SIM_SCGC_BIT(5U, 14U),
    kSimClockGateIRtc0        = FSL_SIM_SCGC_BIT(5U, 16U),
    kSimClockGateIRtcRegFile0 = FSL_SIM_SCGC_BIT(5U, 17U),
    kSimClockGateXbar0        = FSL_SIM_SCGC_BIT(5U, 21U),
    kSimClockGateQuadTmr0     = FSL_SIM_SCGC_BIT(5U, 23U),
    kSimClockGateQuadTmr1     = FSL_SIM_SCGC_BIT(5U, 24U),
    kSimClockGateQuadTmr2     = FSL_SIM_SCGC_BIT(5U, 25U),
    kSimClockGateQuadTmr3     = FSL_SIM_SCGC_BIT(5U, 26U),
    
    kSimClockGateFtf0         = FSL_SIM_SCGC_BIT(6U, 0U),
    kSimClockGateDmamux0      = FSL_SIM_SCGC_BIT(6U, 1U),
    kSimClockGateRnga0        = FSL_SIM_SCGC_BIT(6U, 9U),
    kSimClockGateLpuart0      = FSL_SIM_SCGC_BIT(6U, 10U),
    kSimClockGateAdc0         = FSL_SIM_SCGC_BIT(6U, 11U),
    kSimClockGatePit0         = FSL_SIM_SCGC_BIT(6U, 13U),
    kSimClockGatePit1         = FSL_SIM_SCGC_BIT(6U, 14U),
    kSimClockGateAfe0         = FSL_SIM_SCGC_BIT(6U, 16U),
    kSimClockGateCrc0         = FSL_SIM_SCGC_BIT(6U, 20U),
    kSimClockGatePdb0         = FSL_SIM_SCGC_BIT(6U, 22U),
    kSimClockGatePortJ        = FSL_SIM_SCGC_BIT(6U, 23U),
    kSimClockGatePortK        = FSL_SIM_SCGC_BIT(6U, 24U),
    kSimClockGatePortL        = FSL_SIM_SCGC_BIT(6U, 25U),
    kSimClockGatePortM        = FSL_SIM_SCGC_BIT(6U, 26U),
    kSimClockGateLptmr0       = FSL_SIM_SCGC_BIT(6U, 28U),
    
    kSimClockGateMpu0         = FSL_SIM_SCGC_BIT(7U, 0U),
    kSimClockGateDma0         = FSL_SIM_SCGC_BIT(7U, 1U),
    kSimClockGateCau0         = FSL_SIM_SCGC_BIT(7U, 2U),
    kSimClockGateMmau0        = FSL_SIM_SCGC_BIT(7U, 3U),
} sim_clock_gate_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name IP related clock feature APIs*/
/*@{*/

/*!
 * @brief Enable the clock for specific module.
 *
 * This function enables the clock for specific module.
 *
 * @param base Base address for current SIM instance.
 * @param name Name of the module to enable.
 */
static inline void SIM_HAL_EnableClock(SIM_Type * base, sim_clock_gate_name_t name)
{
    SIM_BWR_SCGC_BIT(base, name, 1U);
}

/*!
 * @brief Disable the clock for specific module.
 *
 * This function disables the clock for specific module.
 *
 * @param base Base address for current SIM instance.
 * @param name Name of the module to disable.
 */
static inline void SIM_HAL_DisableClock(SIM_Type * base, sim_clock_gate_name_t name)
{
    SIM_BWR_SCGC_BIT(base, name, 0U);
}

/*!
 * @brief Get the the clock gate state for specific module.
 *
 * This function will get the clock gate state for specific module.
 *
 * @param base Base address for current SIM instance.
 * @param name Name of the module to get.
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool SIM_HAL_GetGateCmd(SIM_Type * base, sim_clock_gate_name_t name)
{
    return (bool)SIM_BRD_SCGC_BIT(base, name);
}

/*!
 * @brief Gets the Kinetis system RAM size in the System Options register 1(SIM_SOPT1).
 *
 * This function  gets the Kinetis system RAM size.
 *
 * @param base     Base address for current SIM instance.
 * @return             Kinetis System RAM Size
 */
static inline uint32_t SIM_HAL_GetSRamSize(SIM_Type * base)
{
    return SIM_BRD_SOPT1_SRAMSIZE(base);
}

/*!
 * @brief Set the clock selection of ERCLK32K.
 *
 * This function sets the clock selection of ERCLK32K.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetExternalRefClock32kSrc(SIM_Type * base,
                                                       clock_er32k_src_t setting)
{
    SIM_BWR_SOPT1_OSC32KSEL(base, setting);
}

/*!
 * @brief Get the clock selection of ERCLK32K.
 *
 * This function gets the clock selection of ERCLK32K.
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_er32k_src_t CLOCK_HAL_GetExternalRefClock32kSrc(SIM_Type * base)
{
    return (clock_er32k_src_t)SIM_BRD_SOPT1_OSC32KSEL(base);
}

/*!
 * @brief Sets the RAM Bitline Precharge enable setting.
 *
 * This function  controls whether System SRAM bitline precharge is enabled during VLPR and VLPW modes. 
 *
 * @param base  Base address for current SIM instance.
 * @param enable    RAM Bitline Precharge enable setting
 *                  - true: feature enabled.
 *                  - false: feature disabled.
 */
static inline void SIM_HAL_SetRamBitlinePrechargeCmd(SIM_Type * base, bool enable)
{
    SIM_BWR_SOPT1_CFG_RAMBPEN(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the RAM Bitline Precharge enable setting.
 *
 * This function  gets the RAM Bitline Precharge enable setting.
 *
 * @param base   Base address for current SIM instance.
 * @return           True, if RAM Bitline Precharge is enabled.
 */
static inline bool SIM_HAL_GetRamBitlinePrechargeCmd(SIM_Type * base)
{
    return SIM_BRD_SOPT1_CFG_RAMBPEN(base);
}

/*!
 * @brief Sets the source bias of SRAM arrays enable setting.
 *
 * This function controls whether to DISABLE source bias of 
 * System SRAM arrays during VLPR and VLPW modes.  
 *
 * @param base  Base address for current SIM instance.
 * @param disable    source bias of SRAM arrays enable setting
 *                  - true: feature DISABLED.
 *                  - false: feature ENABLED.
 */
static inline void SIM_HAL_SetRamSrcBiasCmd(SIM_Type * base, bool disable)
{
    SIM_BWR_SOPT1_CFG_RAMSBDIS(base, disable);
}

/*!
 * @brief Gets the source bias of SRAM arrays enable setting.
 *
 * This function  gets the source bias of SRAM arrays enable setting.
 *
 * @param base   Base address for current SIM instance.
 * @return           1, if source bias of SRAM arrays is Disabled.
 *                   0, if source bias of SRAM arrays is Enabled.
 */
static inline bool SIM_HAL_GetRamSrcBiasCmd(SIM_Type * base)
{
    return SIM_BRD_SOPT1_CFG_RAMSBDIS(base);
}

/*!
 * @brief Sets the LPTMR channel x source select setting.
 *
 * This function selects the LPTMR channel x source select setting.
 *
 * @param base   Base address for current SIM instance.
 * @param channel    LPTMR channel x
 * @param select     LPTMR channel x source
 */
void SIM_HAL_SetLptmrChSelMode(SIM_Type * base,
                               uint8_t channel,
                               sim_lptmr_src_sel_t select);

/*!
 * @brief Gets the LPTMR channel x source select setting.
 *
 * This function gets the LPTMR channel x source select setting.
 *
 * @param base   Base address for current SIM instance.
 * @param channel    LPTMR channel x
 * @return select    LPTMR channel x source select setting
 */
sim_lptmr_src_sel_t SIM_HAL_GetLptmrChSelMode(SIM_Type * base,
                                              uint8_t channel);
                                       
/*!
 * @brief Set CLKOUTSEL selection.
 *
 * This function sets the selection of the clock to output on the CLKOUT pin.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetClkOutSel(SIM_Type * base, clock_clkout_src_t setting)
{
    SIM_BWR_CTRL_REG_CLKOUT(base, setting);
}

/*!
 * @brief Get CLKOUTSEL selection.
 *
 * This function gets the selection of the clock to output on the CLKOUT pin.
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_clkout_src_t CLOCK_HAL_GetClkOutSel(SIM_Type * base)
{
    return (clock_clkout_src_t)SIM_BRD_CTRL_REG_CLKOUT(base);
}

/*!
 * @brief Set SAR ADC trigger clock selection.
 *
 * This function selects the clock used to generate the ADC triggers.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetSAdcTrgClkSel(SIM_Type * base, sim_sadc_trg_clk_sel_t setting)
{
    SIM_BWR_CTRL_REG_ADCTRGSEL(base, setting);
}

/*!
 * @brief Get the SAR ADC trigger clock selection..
 *
 * This function gets the selection of SAR ADC trigger clock.
 *
 * @param base Base address for current SIM instance.
 * @return         Current selection.
 */
static inline sim_sadc_trg_clk_sel_t CLOCK_HAL_GetSAdcTrgClkSel(SIM_Type * base)
{
    return (sim_sadc_trg_clk_sel_t)SIM_BRD_CTRL_REG_ADCTRGSEL(base);
}

/*!
 * @brief Set TMR counter freeze setting.
 *
 * This function sets TMR counter freeze setting.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetTmrCntFreezeCmd(SIM_Type * base, sim_tmr_cnt_freeze_sel_t setting)
{
    SIM_BWR_CTRL_REG_TMRFREEZE(base, setting);
}

/*!
 * @brief Get the TMR counter freeze setting.
 *
 * This function gets the TMR counter freeze setting.
 *
 * @param base Base address for current SIM instance.
 * @return         Current selection.
 */
static inline sim_tmr_cnt_freeze_sel_t CLOCK_HAL_GetTmrCntFreezeCmd(SIM_Type * base)
{
    return (sim_tmr_cnt_freeze_sel_t)SIM_BRD_CTRL_REG_TMRFREEZE(base);
}

/*!
 * @brief Set LPUART clock source selection.
 *
 * This function selects the clock used for LPUART.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetLpuartClkSel(SIM_Type * base, clock_lpuart_src_t setting)
{
    SIM_BWR_CTRL_REG_LPUARTSRC(base, setting);
}

/*!
 * @brief Get the LPUART clock source selection..
 *
 * This function gets the selection of LPUART clock.
 *
 * @param base Base address for current SIM instance.
 * @return         Current selection.
 */
static inline clock_lpuart_src_t CLOCK_HAL_GetLpuartClkSel(SIM_Type * base)
{
    return (clock_lpuart_src_t)SIM_BRD_CTRL_REG_LPUARTSRC(base);
}

/*!
 * @brief Set AFE output clock dividing setting.
 *
 * This function controls whether AFE output clock is divided by AFE clock prescaler.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetAfeOutDivCmd(SIM_Type * base, sim_afe_clk_div_sel_t setting)
{
    SIM_BWR_CTRL_REG_AFEOUTCLKSEL(base, setting);
}

/*!
 * @brief Get the AFE output clock dividing setting.
 *
 * This function gets the AFE output clock dividing setting.
 *
 * @param base Base address for current SIM instance.
 * @return         Current selection.
 */
static inline sim_afe_clk_div_sel_t CLOCK_HAL_GetAfeOutDivCmd(SIM_Type * base)
{
    return (sim_afe_clk_div_sel_t)SIM_BRD_CTRL_REG_AFEOUTCLKSEL(base);
}

/*!
 * @brief Set XBARCLKOUT selection.
 *
 * This function sets the selection of the clock to XBAR_IN[5] pin.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetXbarOutSel(SIM_Type * base, clock_xbar_out_src_t setting)
{
    SIM_BWR_CTRL_REG_XBARCLKOUT(base, setting);
}

/*!
 * @brief Get XBARCLKOUT selection.
 *
 * This function gets the selection of the clock to XBAR_IN[5] pin.
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_xbar_out_src_t CLOCK_HAL_GetXbarOutSel(SIM_Type * base)
{
    return (clock_xbar_out_src_t)SIM_BRD_CTRL_REG_XBARCLKOUT(base);
}

/*!
 * @brief Set PLL/FLL clock selection.
 *
 * This function sets the selection of the high frequency clock for
 * various peripheral clocking options
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetPllfllSel(SIM_Type * base,
                                          clock_pllfll_sel_t setting)
{
    SIM_BWR_CTRL_REG_PLLFLLSEL(base, setting);
}

/*!
 * @brief Get PLL/FLL clock selection.
 *
 * This function gets the selection of the high frequency clock for
 * various peripheral clocking options
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_pllfll_sel_t CLOCK_HAL_GetPllfllSel(SIM_Type * base)
{
    return (clock_pllfll_sel_t)SIM_BRD_CTRL_REG_PLLFLLSEL(base);
}

/*!
 * @brief Set SPI output signal inverting setting.
 *
 * This function sets SPI output signal inverting setting.
 *
 * @param base Base address for current SIM instance.
 * @param instance device instance
 * @param inv_type inverting type
                   3 - MISI
                   2 - MOSI
                   1 - SCK
                   0 - SS
 * @param setting  The value to set.
 */
void CLOCK_HAL_SetSpiOutInvCmd(SIM_Type * base, 
                                uint32_t instance,
                                uint8_t  inv_type,
                                sim_spi_out_invert_sel_t setting);

/*!
 * @brief Get the SPI output signal inverting setting.
 *
 * This function gets the SPI output signal inverting setting.
 *
 * @param base Base address for current SIM instance.
 * @param instance device instance
 * @param inv_type inverting type
                   3 - MISI
                   2 - MOSI
                   1 - SCK
                   0 - SS
 * @return         Current selection.
 */
sim_spi_out_invert_sel_t CLOCK_HAL_GetSpiOutInvCmd(SIM_Type * base,
                                                   uint32_t instance,
                                                   uint8_t  inv_type);
                                                   
/*!
 * @brief Sets the PLL VLP enable setting.
 *
 * This function controls whether to enable the PLL in VLP modes.  
 *
 * @param base  Base address for current SIM instance.
 * @param enable    enable setting of PLL VLP feature
 *                  - true: feature enabled.
 *                  - false: feature disabled.
 */
static inline void SIM_HAL_SetPllInVlpCmd(SIM_Type * base, bool enable)
{
    SIM_BWR_CTRL_REG_PLLVLPEN(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the PLL VLP enable setting.
 *
 * This function  gets the PLL VLP enable setting.
 *
 * @param base   Base address for current SIM instance.
 * @return           1, if PLL in VLP modes feature is enabled.
 *                   0, if PLL in VLP modes feature is disabled.
 */
static inline bool SIM_HAL_GetPllInVlpCmd(SIM_Type * base)
{
    return SIM_BRD_CTRL_REG_PLLVLPEN(base);
}

/*!
 * @brief Sets the NMI feature enable setting.
 *
 * This function controls whether to disable the NMI feature.  
 *
 * @param base  Base address for current SIM instance.
 * @param disable    enable setting of NMI feature
 *                  - true: feature DISABLED.
 *                  - false: feature ENABLED.
 */
static inline void SIM_HAL_SetNmiDisCmd(SIM_Type * base, bool disable)
{
    SIM_BWR_CTRL_REG_NMIDIS(base, disable);
}

/*!
 * @brief Gets the NMI feature enable setting.
 *
 * This function  gets the NMI feature enable setting.
 *
 * @param base   Base address for current SIM instance.
 * @return           1, if PLL in VLP modes feature is DISABLED.
 *                   0, if PLL in VLP modes feature is ENABLED.
 */
static inline bool SIM_HAL_GetNmiDisCmd(SIM_Type * base)
{
    return SIM_BRD_CTRL_REG_NMIDIS(base);
}

/*!
 * @brief Gets the Kinetis Family ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Family ID in the System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Family ID
 */
static inline uint32_t SIM_HAL_GetFamilyId(SIM_Type * base)
{
    return SIM_BRD_SDID_FAMID(base);
}

/*!
 * @brief Gets the Kinetis Sub-Family ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Sub-Family ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Sub-Family ID
 */
static inline uint32_t SIM_HAL_GetSubFamilyId(SIM_Type * base)
{
    return SIM_BRD_SDID_SUBFAMID(base);
}

/*!
 * @brief Gets the Kinetis SeriesID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Series ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Series ID
 */
static inline uint32_t SIM_HAL_GetSeriesId(SIM_Type * base)
{
    return SIM_BRD_SDID_SERIESID(base);
}

/*!
 * @brief Gets the Attribute ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Attribute ID in System Device ID register.
 *
 * @param base  Base address for current SIM instance.
 * @return id       Attribute ID
 */
static inline uint32_t SIM_HAL_GetAttributeId(SIM_Type * base)
{
    return SIM_BRD_SDID_ATTR(base);
}

/*!
 * @brief Gets the SRAM SIZE in the System Device ID register (SIM_SDID).
 *
 * This function  gets the SRAM SIZE in System Device ID register.
 *
 * @param base  Base address for current SIM instance.
 * @return id       SRAM size
 */
static inline uint32_t SIM_HAL_GetSRamSizeId(SIM_Type * base)
{
    return SIM_BRD_SDID_SRAMSIZE(base);
}

/*!
 * @brief Gets the Kinetis Revision ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Revision ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Revision ID
 */
static inline uint32_t SIM_HAL_GetRevId(SIM_Type * base)
{
    return SIM_BRD_SDID_REVID(base);
}

/*!
 * @brief Gets the Kinetis Die ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Die ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Die ID
 */
static inline uint32_t SIM_HAL_GetDieId(SIM_Type * base)
{
    return SIM_BRD_SDID_DIEID(base);
}	

/*!
 * @brief Gets the Kinetis Pincount ID in System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Pincount ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Pincount ID
 */
static inline uint32_t SIM_HAL_GetPinCntId(SIM_Type * base)
{
    return SIM_BRD_SDID_PINID(base);
}

/*!
 * @brief Set system clock divider.
 *
 * This function sets divide value SYSDIV.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetSysDiv(SIM_Type * base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_CLKDIVSYS(base, setting);
}

/*!
 * @brief Get SYSDIV.
 *
 * This function gets divide value SYSDIV.
 *
 * @param base Base address for current SIM instance.
 * @return         Current divide value.
 */
static inline uint8_t CLOCK_HAL_GetSysDiv(SIM_Type * base)
{
    return SIM_BRD_CLKDIV1_CLKDIVSYS(base);
}

/*!
 * @brief Set BUS clock divider.
 *
 * This function sets BUS clock divider.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetBusDiv(SIM_Type * base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_CLKDIVBUS(base, setting);
}

/*!
 * @brief Get BUS clock divider value.
 *
 * This function gets BUS clock divider value.
 *
 * @param base Base address for current SIM instance.
 * @return         Current divide value.
 */
static inline uint8_t CLOCK_HAL_GetBusDiv(SIM_Type * base)
{
    return SIM_BRD_CLKDIV1_CLKDIVBUS(base);
}

/*!
 * @brief Set FLASH clock mode.
 *
 * This function sets FLASH clock mode.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetFlashClkMode(SIM_Type * base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_FLASHCLKMODE(base, setting);
}

/*!
 * @brief Get FLASH clock mode value.
 *
 * This function gets FLASH clock mode value.
 *
 * @param base Base address for current SIM instance.
 * @return         Current divide value.
 */
static inline uint8_t CLOCK_HAL_GetFlashClkMode(SIM_Type * base)
{
    return SIM_BRD_CLKDIV1_FLASHCLKMODE(base);
}

/*!
 * @brief Set all clock out dividers setting at one time
 *
 * This function sets all clock out dividers setting at one time.
 *
 * @param base Base address for current SIM instance.
 * @param sysDiv        system clock divider
 * @param busDiv        bus clock divider
 * @param flashclkmode  flash clock mode setting
 */
void CLOCK_HAL_SetOutDiv(SIM_Type * base,
                         uint8_t sysDiv,
                         uint8_t busDiv,
                         uint8_t flashclkmode);

/*!
 * @brief Get all clock out dividers setting at one time.
 *
 * This function gets all clock out dividers setting at one time
 *
 * @param base      Base address for current SIM instance.
 * @param sysDiv        system clock divider
 * @param busDiv        bus clock divider
 * @param flashclkmode  flash clock mode setting
 * @return              Current all divide values.
 */
void CLOCK_HAL_GetOutDiv(SIM_Type * base,
                         uint8_t *sysDiv,
                         uint8_t *busDiv,
                         uint8_t *flashclkmode);

/*!
 * @brief Gets the program flash size in the Flash Configuration Register 1 (SIM_FCFG).
 *
 * This function  gets the program flash size in the Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @return size Program flash Size
 */
static inline uint32_t SIM_HAL_GetProgramFlashSize(SIM_Type * base)
{
    return SIM_BRD_FCFG1_PFSIZE(base);
}		

/*!
 * @brief Sets the Flash Doze in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  sets the Flash Doze in the Flash Configuration Register 1.
 *
 * @param base   Base address for current SIM instance.
 * @param setting    Flash Doze setting
 */
static inline void SIM_HAL_SetFlashDoze(SIM_Type * base, uint32_t setting)
{
    SIM_BWR_FCFG1_FLASHDOZE(base, setting);
}

/*!
 * @brief Gets the Flash Doze in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash Doze in the Flash Configuration Register 1.
 *
 * @param base   Base address for current SIM instance.
 * @return setting   Flash Doze setting
 */
static inline uint32_t SIM_HAL_GetFlashDoze(SIM_Type * base)
{
    return SIM_BRD_FCFG1_FLASHDOZE(base);
}

/*!
 * @brief Sets the Flash disable setting.
 *
 * This function  sets the Flash disable setting in the
 * Flash Configuration Register 1.
 *
 * @param base   Base address for current SIM instance.
 * @param disable    Flash disable setting
 */
static inline void SIM_HAL_SetFlashDisableCmd(SIM_Type * base, bool disable)
{
    SIM_BWR_FCFG1_FLASHDIS(base, disable);
}

/*!
 * @brief Gets the RAM size.
 *
 * This function  gets the RAM size
 * 
 *
 * @param base     Base address for current SIM instance.
 * @return RAM size
 */
static inline bool SIM_HAL_GetRamSize(SIM_Type * base)
{
  return SIM_BRD_SOPT1_SRAMSIZE(base);
}

/*!
 * @brief Gets the Flash disable setting.
 *
 * This function  gets the Flash disable setting in the
 * Flash Configuration Register 1.
 *
 * @param base     Base address for current SIM instance.
 * @return setting Flash disable setting
 */


static inline bool SIM_HAL_GetFlashDisableCmd(SIM_Type * base)
{
    return (bool)SIM_BRD_FCFG1_FLASHDIS(base);
}


/*!
 * @brief Gets the Flash maximum address block in the Flash Configuration Register 2(SIM_FCFG2).
 *
 * This function gets the Flash maximum block in Flash Configuration Register 2.
 *
 * @param base  Base address for current SIM instance.
 * @return address  Flash maximum block address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock0(SIM_Type * base)
{
    return SIM_BRD_FCFG2_MAXADDR(base);
}

/*!
 * @brief Sets the VrefBuffer enable setting.
 *
 * This function controls whether to enable the VrefBuffer power down feature.  
 *
 * @param base  Base address for current SIM instance.
 * @param enable    enable setting of VrefBuffer Power Down feature
 *                  - true: power down VrefBuffer.
 *                  - false: VrefBuffer enabled.
 */
static inline void SIM_HAL_SetVrefBuffPowerDownCmd(SIM_Type * base, bool enable)
{
    SIM_BWR_MISC_CTL_VREFBUFPD(base, enable ? 0 : 1);
}

/*!
 * @brief Gets the VrefBuffer enable setting.
 *
 * This function  gets the VrefBuffer enable setting.
 *
 * @param base   Base address for current SIM instance.
 * @return           1, if VrefBuffer is powered down.
 *                   0, if VrefBuffer is enabled.
 */
static inline bool SIM_HAL_GetVrefBuffPowerDownCmd(SIM_Type * base)
{
    return SIM_BRD_MISC_CTL_VREFBUFPD(base);
}

/*!
 * @brief Set the VrefBuffer input selection.
 *
 * This function selects the VrefBuffer input selection.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetVrefBuffInputSel(SIM_Type * base, sim_vref_buff_input_sel_t setting)
{
    SIM_BWR_MISC_CTL_VREFBUFINSEL(base, setting);
}

/*!
 * @brief Get the VrefBuffer input selection.
 *
 * This function gets the selection of VrefBuffer input.
 *
 * @param base Base address for current SIM instance.
 * @return         Current selection.
 */
static inline sim_vref_buff_input_sel_t CLOCK_HAL_GetVrefBuffInputSel(SIM_Type * base)
{
    return (sim_vref_buff_input_sel_t)SIM_BRD_MISC_CTL_VREFBUFINSEL(base);
}

/*!
 * @brief Sets the VrefBuffer Output enable setting.
 *
 * This function controls whether to enable the VrefBuffer to drive PAD.  
 *
 * @param base  Base address for current SIM instance.
 * @param enable    enable setting of VrefBuffer output drive feature
 *                  - true:  VrefBuffer drives selected voltage on pad.
 *                  - false: VrefBuffer not drive PAD.
 */
static inline void SIM_HAL_SetVrefBuffOutCmd(SIM_Type * base, bool enable)
{
    SIM_BWR_MISC_CTL_VREFBUFOUTEN(base, enable);
}

/*!
 * @brief Gets the VrefBuffer Output enable setting.
 *
 * This function  gets the VrefBuffer Output enable setting.
 *
 * @param base   Base address for current SIM instance.
 * @return           1, if VrefBuffer output drive feature is enabled.
 *                   0, if VrefBuffer output drive feature is disabled.
 */
static inline bool SIM_HAL_GetVrefBuffOutCmd(SIM_Type * base)
{
    return SIM_BRD_MISC_CTL_VREFBUFOUTEN(base);
}

/*!
 * @brief Set the RTC clock source selection for RTC operation.
 *
 * This function selects the clock source for RTC operation.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetRtcClkSel(SIM_Type * base, clock_rtcout_src_t setting)
{
    SIM_BWR_MISC_CTL_RTCCLKSEL(base, setting);
}

/*!
 * @brief Get the RTC clock source selection for RTC operation..
 *
 * This function gets the selection of RTC clock source.
 *
 * @param base Base address for current SIM instance.
 * @return         Current selection.
 */
static inline clock_rtcout_src_t CLOCK_HAL_GetRtcClkSel(SIM_Type * base)
{
    return (clock_rtcout_src_t)SIM_BRD_MISC_CTL_RTCCLKSEL(base);
}

/*!
 * @brief Sets the Quadtimer channel x Primary Count source select setting.
 *
 * This function selects the Quadtimer channel x Primary Count source.
 *
 * @param base   Base address for current SIM instance.
 * @param channel    Quadtimer channel x
 * @param select     Quadtimer channel x primary count source
 */
void SIM_HAL_SetTmrPrimaryCntSrcSelMode(SIM_Type * base,
                                        uint8_t channel,
                                        sim_tmr_Primary_src_sel_t select);

/*!
 * @brief Gets the Quadtimer channel x Primary Count source select setting.
 *
 * This function gets the Quadtimer channel x Primary Count source select setting.
 *
 * @param base   Base address for current SIM instance.
 * @param channel    Quadtimer channel x
 * @return select    Quadtimer channel x primary count source select setting
 */
sim_tmr_Primary_src_sel_t SIM_HAL_GetTmrPrimaryCntSrcSelMode(SIM_Type * base,
                                                             uint8_t channel);

/*!
 * @brief Sets the Quadtimer channel x Secondary Count source select setting.
 *
 * This function selects the Quadtimer channel x Secondary Count source.
 *
 * @param base   Base address for current SIM instance.
 * @param channel    Quadtimer channel x
 * @param select     Quadtimer channel x Secondary count source
 */
void SIM_HAL_SetTmrSecondCntSrcSelMode(SIM_Type * base,
                                       uint8_t channel,
                                       sim_tmr_sencond_src_sel_t select);

/*!
 * @brief Gets the Quadtimer channel x Secondary Count source select setting.
 *
 * This function gets the Quadtimer channel x Secondary Count source select setting.
 *
 * @param base   Base address for current SIM instance.
 * @param channel    Quadtimer channel x
 * @return select    Quadtimer channel x Secondary count source select setting
 */
sim_tmr_sencond_src_sel_t SIM_HAL_GetTmrSecondCntSrcSelMode(SIM_Type * base,
                                                            uint8_t channel);

/*!
 * @brief Sets the Timer0 CH0 PLL clock source select setting.
 *
 * This function selects the Timer0 CH0 PLL clock source.
 *
 * @param base   Base address for current SIM instance.
 * @param select     Timer0 CH0 PLL clock source selection
 */
static inline void SIM_HAL_SetTmr0PllClkSelMode(SIM_Type * base,
                                  clock_tmr0_pll_src_t select)
{
    SIM_BWR_MISC_CTL_TMR0PLLSEL(base, select);
}                                       

/*!
 * @brief Gets the Timer0 CH0 PLL clock source select setting.
 *
 * This function gets the Timer0 CH0 PLL clock source select setting.
 *
 * @param base   Base address for current SIM instance.
 * @return select    Timer0 CH0 PLL clock source selection.
 */
static inline clock_tmr0_pll_src_t SIM_HAL_GetTmr0PllClkSelMode(SIM_Type * base)
{
    return (clock_tmr0_pll_src_t)SIM_BRD_MISC_CTL_TMR0PLLSEL(base);
}
                                                            
/*!
 * @brief Sets the EWM input select setting.
 *
 * This function selects the External Watchdog Monitor Input source.
 *
 * @param base   Base address for current SIM instance.
 * @param select     EWM input source selection
 */
static inline void SIM_HAL_SetEwmInputSelMode(SIM_Type * base,
                                sim_ewm_input_sel_t select)
{
    SIM_BWR_MISC_CTL_EWMINSEL(base, select);
}                                       

/*!
 * @brief Gets the EWM input select setting.
 *
 * This function gets the EWM input select setting.
 *
 * @param base   Base address for current SIM instance.
 * @return select    EWM input source selection.
 */
static inline sim_ewm_input_sel_t SIM_HAL_GetEwmInputSelMode(SIM_Type * base)
{
    return (sim_ewm_input_sel_t)SIM_BRD_MISC_CTL_EWMINSEL(base);
}                                                            
                                                            
/*!
 * @brief Sets the UART x IRDA select setting.
 *
 * This function  sets the UART x IRDA select setting.
 *
 * @param base   Base address for current SIM instance.
 * @param instance   Device instance.
 * @param select     UART x IRDA selection.
 */
void SIM_HAL_SetUartIrdaSelMode(SIM_Type * base,
                                uint32_t instance,
                                sim_uart_irda_sel_t select);

/*!
 * @brief Gets the UART x IRDA select setting.
 *
 * This function  gets the UART x IRDA select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     Device instance.
 * @return select      UART x IRDA selection.
 */
sim_uart_irda_sel_t SIM_HAL_GetUartIrdaSelMode(SIM_Type * base,
                                               uint32_t instance);                                                           
                                                            
/*!
 * @brief Sets the UART modulation select setting.
 *
 * This function selects the modulation type for IRDA support.
 *
 * @param base   Base address for current SIM instance.
 * @param select     UART modulation type selection.
 */
static inline void SIM_HAL_SetUartModTypeSelMode(SIM_Type * base,
                                                 sim_uart_irda_type_sel_t select)
{
    SIM_BWR_MISC_CTL_UARTMODTYPE(base, select);
}                                       

/*!
 * @brief Gets the UART modulation select setting.
 *
 * This function gets the UART modulation select setting.
 *
 * @param base   Base address for current SIM instance.
 * @return select    UART modulation selection.
 */
static inline sim_uart_irda_type_sel_t SIM_HAL_GetUartModTypeSelMode(SIM_Type * base)
{
    return (sim_uart_irda_type_sel_t)SIM_BRD_MISC_CTL_UARTMODTYPE(base);
}                                                             
                                                            
/*!
 * @brief Sets the AFE clock Pad direction setting.
 *
 * This function  controls the direction of the AFE CLK pin. 
 *
 * @param base  Base address for current SIM instance.
 * @param setting   AFE clock Pad direction setting
 *                  - 0: input.
 *                  - 1: output.
 */
static inline void SIM_HAL_SetAfeClkPadDirCmd(SIM_Type * base, sim_afe_clk_pad_dir_t setting)
{
    SIM_BWR_MISC_CTL_AFECLKPADDIR(base, setting);
}

/*!
 * @brief Gets the AFE clock Pad direction setting.
 *
 * This function gets the AFE clock Pad direction setting.
 *
 * @param base  Base address for current SIM instance.
 * @return setting  AFE clock Pad direction setting.
 */
static inline sim_afe_clk_pad_dir_t SIM_HAL_GetAfeClkPadDirCmd(SIM_Type * base)
{
    return (sim_afe_clk_pad_dir_t)SIM_BRD_MISC_CTL_AFECLKPADDIR(base);
}                                                            
   
/*!
 * @brief Set the clock selection of AFECLKSEL.
 *
 * This function sets the clock selection of AFECLKSEL.
 *
 * @param base Base address for current SIM instance.
 * @param select   The clock source to select.
 */
static inline void CLOCK_HAL_SetAfeClkSrc(SIM_Type * base,
                                          clock_afe_src_t select)
{
    SIM_BWR_MISC_CTL_AFECLKSEL(base, select);
}

/*!
 * @brief Get the clock source selection of AFECLKSEL.
 *
 * This function gets the clock source selection of AFECLKSEL.
 *
 * @param base Base address for current SIM instance.
 * @return         Current selection.
 */
static inline clock_afe_src_t CLOCK_HAL_GetAfeClkSrc(SIM_Type * base)
{
    return (clock_afe_src_t)SIM_BRD_MISC_CTL_AFECLKSEL(base);
} 
                                                            
/*!
 * @brief Sets the DMA Done select setting.
 *
 * This function selects the DMA Done flag to drive XBAR_IN[32].
 *
 * @param base   Base address for current SIM instance.
 * @param select     DMA Done selection.
 */
static inline void SIM_HAL_SetDmaDoneSelMode(SIM_Type * base,
                                             sim_dma_done_sel_t select)
{
    SIM_BWR_MISC_CTL_DMADONESEL(base, select);
}                                       

/*!
 * @brief Gets the DMA Done select setting.
 *
 * This function gets the DMA Done select setting.
 *
 * @param base   Base address for current SIM instance.
 * @return           Current DMA Done selection.
 */
static inline sim_dma_done_sel_t SIM_HAL_GetDmaDoneSelMode(SIM_Type * base)
{
    return (sim_dma_done_sel_t)SIM_BRD_MISC_CTL_DMADONESEL(base);
}                                                             
               
/*!
 * @brief Sets the ADC trigger source setting.
 *
 * This function controls whether PDB can trigger ADC directly.
 *
 * @param base   Base address for current SIM instance.
 * @param select     ADC trigger selection.
 */
static inline void SIM_HAL_SetAdcTrgSelMode(SIM_Type * base,
                                            sim_adc_trg_src_sel_t select)
{
    SIM_BWR_MISC_CTL_PDBADCTRG(base, select);
}                                       

/*!
 * @brief Gets the ADC trigger source setting.
 *
 * This function gets the ADC trigger source setting.
 *
 * @param base   Base address for current SIM instance.
 * @return           Current ADC trigger selection.
 */
static inline sim_adc_trg_src_sel_t SIM_HAL_GetAdcTrgSelMode(SIM_Type * base)
{
    return (sim_adc_trg_src_sel_t)SIM_BRD_MISC_CTL_PDBADCTRG(base);
}    

/*!
 * @brief Gets the status of RTC oscillator.
 *
 * This function gets the status of RTC oscillator.
 *
 * @param base   Base address for current SIM instance.
 * @return           1, if RTC oscillator is enabled.
 *                   0, if RTC oscillator is disabled.
 */
static inline bool SIM_HAL_GetRtcOscStatusCmd(SIM_Type * base)
{
    return SIM_BRD_MISC_CTL_OSCON(base);
}                
   
/*!
 * @brief Gets the ADC Temperature Compensation Value.
 *
 * This function gets the status of RTC oscillator.
 *
 * @param base     Base address for current SIM instance.
 * @param temperature  under which temperature
                       0 - +25 degrees Celsius
                       1 - -40 degrees Celsius
                       2 - +85 degrees Celsius
 *                       
 * @return             Compensation value
 */
uint16_t SIM_HAL_GetAdcCompensationValueCmd(SIM_Type * base, uint8_t temperature);   
                
#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_SIM_HAL_KM34Z2567_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

