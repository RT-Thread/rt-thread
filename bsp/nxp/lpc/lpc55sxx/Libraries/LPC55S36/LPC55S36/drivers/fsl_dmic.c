/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dmic.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dmic"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of DMIC peripheral base address. */
static DMIC_Type *const s_dmicBases[FSL_FEATURE_SOC_DMIC_COUNT] = DMIC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of DMIC clock name. */
static const clock_ip_name_t s_dmicClock[FSL_FEATURE_SOC_DMIC_COUNT] = DMIC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* Array of DMIC IRQ number. */
static const IRQn_Type s_dmicIRQ[FSL_FEATURE_SOC_DMIC_COUNT] = DMIC_IRQS;

/*! @brief Callback function array for DMIC(s). */
static dmic_callback_t s_dmicCallback[FSL_FEATURE_SOC_DMIC_COUNT];

/* Array of HWVAD IRQ number. */
static const IRQn_Type s_dmicHwvadIRQ[FSL_FEATURE_SOC_DMIC_COUNT] = DMIC_HWVAD_IRQS;

/*! @brief Callback function array for HWVAD(s). */
static dmic_hwvad_callback_t s_dmicHwvadCallback[FSL_FEATURE_SOC_DMIC_COUNT];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the DMIC instance from peripheral base address.
 *
 * @param base DMIC peripheral base address.
 * @return DMIC instance.
 */
/*!
 * brief Get the DMIC instance from peripheral base address.
 *
 * param base DMIC peripheral base address.
 * return DMIC instance.
 */
uint32_t DMIC_GetInstance(DMIC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dmicBases); instance++)
    {
        if (s_dmicBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dmicBases));

    return instance;
}

/*!
 * brief	Turns DMIC Clock on
 * param	base	: DMIC base
 * return	Nothing
 */
void DMIC_Init(DMIC_Type *base)
{
    assert(base != NULL);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_dmicClock[DMIC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(kDMIC_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

    /* reset FIFO configuration */
    base->CHANNEL[0].FIFO_CTRL = 0U;
    base->CHANNEL[1].FIFO_CTRL = 0U;
#if defined(FSL_FEATURE_DMIC_CHANNEL_NUM) && (FSL_FEATURE_DMIC_CHANNEL_NUM == 8U)
    base->CHANNEL[3].FIFO_CTRL = 0U;
    base->CHANNEL[4].FIFO_CTRL = 0U;
    base->CHANNEL[5].FIFO_CTRL = 0U;
    base->CHANNEL[6].FIFO_CTRL = 0U;
    base->CHANNEL[7].FIFO_CTRL = 0U;
#endif
}

/*!
 * brief	Turns DMIC Clock off
 * param	base	: DMIC base
 * return	Nothing
 */
void DMIC_DeInit(DMIC_Type *base)
{
    assert(base != NULL);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_dmicClock[DMIC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

#if !(defined(FSL_FEATURE_DMIC_HAS_NO_IOCFG) && FSL_FEATURE_DMIC_HAS_NO_IOCFG)
/*!
 * brief	Configure DMIC io
 * @deprecated Do not use this function.  It has been superceded by @ref DMIC_SetIOCFG
 * param	base	: The base address of DMIC interface
 * param	config		: DMIC io configuration
 * return	Nothing
 */
void DMIC_ConfigIO(DMIC_Type *base, dmic_io_t config)
{
    base->IOCFG = (uint32_t)config;
}
#endif

/*!
 * brief	Set DMIC operating mode
 * deprecated Do not use this function.  It has been superceded by @ref
 * DMIC_EnableChannelInterrupt/DMIC_EnableChannelDma
 * param	base	: The base address of DMIC interface
 * param	mode	: DMIC mode
 * return	Nothing
 */
void DMIC_SetOperationMode(DMIC_Type *base, operation_mode_t mode)
{
    if (mode == kDMIC_OperationModeInterrupt)
    {
        /* Enable DMIC interrupt. */
        base->CHANNEL[0].FIFO_CTRL |= DMIC_CHANNEL_FIFO_CTRL_INTEN(1);
        base->CHANNEL[1].FIFO_CTRL |= DMIC_CHANNEL_FIFO_CTRL_INTEN(1);
    }
    if (mode == kDMIC_OperationModeDma)
    {
        /* enable DMA request*/
        base->CHANNEL[0].FIFO_CTRL |= DMIC_CHANNEL_FIFO_CTRL_DMAEN(1);
        base->CHANNEL[1].FIFO_CTRL |= DMIC_CHANNEL_FIFO_CTRL_DMAEN(1);
    }
}

/*!
 * brief	Configure DMIC channel
 *
 * param	base		: The base address of DMIC interface
 * param	channel		: DMIC channel
 * param side     : stereo_side_t, choice of left or right
 * param	channel_config	: Channel configuration
 * return	Nothing
 */
void DMIC_ConfigChannel(DMIC_Type *base,
                        dmic_channel_t channel,
                        stereo_side_t side,
                        dmic_channel_config_t *channel_config)
{
    base->CHANNEL[channel].DIVHFCLK     = (uint32_t)channel_config->divhfclk;
    base->CHANNEL[channel].OSR          = channel_config->osr;
    base->CHANNEL[channel].GAINSHIFT    = (uint32_t)channel_config->gainshft;
    base->CHANNEL[channel].PREAC2FSCOEF = (uint32_t)channel_config->preac2coef;
    base->CHANNEL[channel].PREAC4FSCOEF = (uint32_t)channel_config->preac4coef;
    base->CHANNEL[channel].PHY_CTRL =
        DMIC_CHANNEL_PHY_CTRL_PHY_FALL(side) | DMIC_CHANNEL_PHY_CTRL_PHY_HALF(channel_config->sample_rate);
    base->CHANNEL[channel].DC_CTRL = DMIC_CHANNEL_DC_CTRL_DCPOLE(channel_config->dc_cut_level) |
                                     DMIC_CHANNEL_DC_CTRL_DCGAIN(channel_config->post_dc_gain_reduce) |
                                     DMIC_CHANNEL_DC_CTRL_SATURATEAT16BIT(channel_config->saturate16bit);

#if defined(FSL_FEATURE_DMIC_CHANNEL_HAS_SIGNEXTEND) && (FSL_FEATURE_DMIC_CHANNEL_HAS_SIGNEXTEND)
    base->CHANNEL[channel].DC_CTRL |= DMIC_CHANNEL_DC_CTRL_SIGNEXTEND(channel_config->enableSignExtend);
#endif
}

/*!
 * brief	Configure DMIC channel
 * param	base		: The base address of DMIC interface
 * param	channel		: DMIC channel
 * param   dc_cut_level  : dc_removal_t, Cut off Frequency
 * param	post_dc_gain_reduce	: Fine g!y!9
 * param   saturate16bit : If selects 16-bit saturation.
 */
void DMIC_CfgChannelDc(DMIC_Type *base,
                       dmic_channel_t channel,
                       dc_removal_t dc_cut_level,
                       uint32_t post_dc_gain_reduce,
                       bool saturate16bit)
{
    base->CHANNEL[channel].DC_CTRL = DMIC_CHANNEL_DC_CTRL_DCPOLE(dc_cut_level) |
                                     DMIC_CHANNEL_DC_CTRL_DCGAIN(post_dc_gain_reduce) |
                                     DMIC_CHANNEL_DC_CTRL_SATURATEAT16BIT(saturate16bit);
}

/*!
 * brief	Configure Clock scaling
 * param	base		: The base address of DMIC interface
 * param	use2fs		: clock scaling
 * return	Nothing
 */
void DMIC_Use2fs(DMIC_Type *base, bool use2fs)
{
    base->USE2FS = (use2fs) ? 0x1UL : 0x0UL;
}

/*!
 * brief	Enable a particualr channel
 * param	base		: The base address of DMIC interface
 * param	channelmask	: Channel selection
 * return	Nothing
 */
void DMIC_EnableChannnel(DMIC_Type *base, uint32_t channelmask)
{
    base->CHANEN |= channelmask;
}

/*!
 * brief	Configure fifo settings for DMIC channel
 * param	base		: The base address of DMIC interface
 * param	channel		: DMIC channel
 * param	trig_level	: FIFO trigger level
 * param	enable		: FIFO level
 * param	resetn		: FIFO reset
 * return	Nothing
 */
void DMIC_FifoChannel(DMIC_Type *base, uint32_t channel, uint32_t trig_level, uint32_t enable, uint32_t resetn)
{
    base->CHANNEL[channel].FIFO_CTRL =
        ((base->CHANNEL[channel].FIFO_CTRL & (DMIC_CHANNEL_FIFO_CTRL_INTEN_MASK | DMIC_CHANNEL_FIFO_CTRL_DMAEN_MASK)) |
         DMIC_CHANNEL_FIFO_CTRL_TRIGLVL(trig_level) | DMIC_CHANNEL_FIFO_CTRL_ENABLE(enable) |
         DMIC_CHANNEL_FIFO_CTRL_RESETN(resetn));
}

#if defined(FSL_FEATURE_DMIC_HAS_DECIMATOR_RESET_FUNC) && FSL_FEATURE_DMIC_HAS_DECIMATOR_RESET_FUNC
/*!
 * brief   DMIC channel Decimator reset
 * param   base        : The base address of DMIC interface
 * param   channelMask     : DMIC channel mask, reference _dmic_channel_mask
 * param   reset           : true is reset decimator, false is release decimator.
 */
void DMIC_ResetChannelDecimator(DMIC_Type *base, uint32_t channelMask, bool reset)
{
    uint32_t decReset = 0U;

    if ((channelMask & ((uint32_t)kDMIC_EnableChannel1 | (uint32_t)kDMIC_EnableChannel0)) != 0U)
    {
        decReset |= 1U;
    }
#if defined(FSL_FEATURE_DMIC_CHANNEL_NUM) && (FSL_FEATURE_DMIC_CHANNEL_NUM == 8U)
    if ((channelMask & ((uint32_t)kDMIC_EnableChannel3 | (uint32_t)kDMIC_EnableChannel2)) != 0U)
    {
        decReset |= 2U;
    }

    if ((channelMask & ((uint32_t)kDMIC_EnableChannel5 | (uint32_t)kDMIC_EnableChannel4)) != 0U)
    {
        decReset |= 4U;
    }

    if ((channelMask & ((uint32_t)kDMIC_EnableChannel7 | (uint32_t)kDMIC_EnableChannel6)) != 0U)
    {
        decReset |= 8U;
    }
#endif

    if (reset)
    {
        base->DECRESET |= decReset;
    }
    else
    {
        base->DECRESET &= ~decReset;
    }
}
#endif

/*!
 * brief	Enable callback.

 * This function enables the interrupt for the selected DMIC peripheral.
 * The callback function is not enabled until this function is called.
 *
 * param base Base address of the DMIC peripheral.
 * param cb callback Pointer to store callback function.
 * retval None.
 */
void DMIC_EnableIntCallback(DMIC_Type *base, dmic_callback_t cb)
{
    uint32_t instance;

    instance = DMIC_GetInstance(base);
    NVIC_ClearPendingIRQ(s_dmicIRQ[instance]);
    /* Save callback pointer */
    s_dmicCallback[instance] = cb;
    (void)EnableIRQ(s_dmicIRQ[instance]);
}

/*!
 * brief	Disable callback.

 * This function disables the interrupt for the selected DMIC peripheral.
 *
 * param base Base address of the DMIC peripheral.
 * param cb callback Pointer to store callback function..
 * retval None.
 */
void DMIC_DisableIntCallback(DMIC_Type *base, dmic_callback_t cb)
{
    uint32_t instance;

    instance = DMIC_GetInstance(base);
    (void)DisableIRQ(s_dmicIRQ[instance]);
    s_dmicCallback[instance] = NULL;
    NVIC_ClearPendingIRQ(s_dmicIRQ[instance]);
}

/*!
 * brief	Enable hwvad callback.

 * This function enables the hwvad interrupt for the selected DMIC  peripheral.
 * The callback function is not enabled until this function is called.
 *
 * param base Base address of the DMIC peripheral.
 * param vadcb callback Pointer to store callback function.
 * retval None.
 */
void DMIC_HwvadEnableIntCallback(DMIC_Type *base, dmic_hwvad_callback_t vadcb)
{
    uint32_t instance;

    instance = DMIC_GetInstance(base);
    NVIC_ClearPendingIRQ(s_dmicHwvadIRQ[instance]);
    /* Save callback pointer */
    s_dmicHwvadCallback[instance] = vadcb;
    (void)EnableIRQ(s_dmicHwvadIRQ[instance]);
}

/*!
 * brief	Disable callback.

 * This function disables the hwvad interrupt for the selected DMIC peripheral.
 *
 * param base Base address of the DMIC peripheral.
 * param vadcb callback Pointer to store callback function..
 * retval None.
 */
void DMIC_HwvadDisableIntCallback(DMIC_Type *base, dmic_hwvad_callback_t vadcb)
{
    uint32_t instance;

    instance = DMIC_GetInstance(base);
    (void)DisableIRQ(s_dmicHwvadIRQ[instance]);
    s_dmicHwvadCallback[instance] = NULL;
    NVIC_ClearPendingIRQ(s_dmicHwvadIRQ[instance]);
}

/* IRQ handler functions overloading weak symbols in the startup */
#if defined(DMIC0)
/*DMIC0 IRQ handler */
void DMIC0_DriverIRQHandler(void);
void DMIC0_DriverIRQHandler(void)
{
    if (s_dmicCallback[0] != NULL)
    {
        s_dmicCallback[0]();
    }
    SDK_ISR_EXIT_BARRIER;
}
/*DMIC0 HWVAD IRQ handler */
void HWVAD0_DriverIRQHandler(void);
void HWVAD0_DriverIRQHandler(void)
{
    if (s_dmicHwvadCallback[0] != NULL)
    {
        s_dmicHwvadCallback[0]();
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif
