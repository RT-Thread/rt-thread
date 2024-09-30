/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019, 2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_slcd.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.slcd"
#endif

#define SLCD_WAVEFORM_CONFIG_NUM 16U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the SLCD instance from peripheral base address.
 *
 * @param base SLCD peripheral base address.
 * @return SLCD instance.
 */
static uint32_t SLCD_GetInstance(LCD_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to slcd clocks for each instance. */
static const clock_ip_name_t s_slcdClock[FSL_FEATURE_SOC_SLCD_COUNT] = SLCD_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to slcd bases for each instance. */
static LCD_Type *const s_slcdBases[] = LCD_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t SLCD_GetInstance(LCD_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_slcdBases); instance++)
    {
        if (s_slcdBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_slcdBases));

    return instance;
}

/*!
 * brief Initializes the SLCD, ungates the module clock, initializes the power
 * setting, enables all used plane pins, and sets with interrupt and work mode
 * with the configuration.
 *
 * param base  SLCD peripheral base address.
 * param configure SLCD configuration pointer.
 *   For the configuration structure, many parameters have the default setting
 *   and the SLCD_Getdefaultconfig() is provided to get them. Use it
 *   verified for their applications.
 *   The others have no default settings, such as "clkConfig", and must be provided
 *   by the application before calling the SLCD_Init() API.
 */
void SLCD_Init(LCD_Type *base, slcd_config_t *configure)
{
    assert(configure);
    assert(configure->clkConfig);

    uint32_t gcrReg   = 0;
    bool intEnabled   = false;
    uint32_t regNum   = 0;
    uint32_t instance = SLCD_GetInstance(base);

    /* Bit mask of the LCD_GCR to modify in this function. */
    uint32_t gcrMsk = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Un-gate the SLCD clock. */
    CLOCK_EnableClock(s_slcdClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Configure general setting: power supply. */
    gcrReg = LCD_GCR_RVEN((uint32_t)configure->powerSupply & 0x1U) |
             LCD_GCR_CPSEL(((uint32_t)configure->powerSupply >> 1U) & 0x1U) |
             LCD_GCR_VSUPPLY(((uint32_t)configure->powerSupply >> 2U) & 0x1U) |
             LCD_GCR_LADJ((uint32_t)configure->loadAdjust);
    /* Configure general setting: clock source. */
    gcrReg |= LCD_GCR_SOURCE(((uint32_t)configure->clkConfig->clkSource) & 0x1U) |
              LCD_GCR_LCLK(configure->clkConfig->clkPrescaler) | LCD_GCR_ALTDIV(configure->clkConfig->altClkDivider);
    /* Configure the duty and set the work for low power wait and stop mode. */
    gcrReg |= LCD_GCR_DUTY(configure->dutyCycle) | LCD_GCR_LCDSTP((uint32_t)configure->lowPowerBehavior & 0x1U);

    gcrMsk = LCD_GCR_RVEN_MASK | LCD_GCR_CPSEL_MASK | LCD_GCR_VSUPPLY_MASK | LCD_GCR_LADJ_MASK | LCD_GCR_SOURCE_MASK |
             LCD_GCR_LCLK_MASK | LCD_GCR_ALTDIV_MASK | LCD_GCR_DUTY_MASK | LCD_GCR_LCDSTP_MASK;

#if FSL_FEATURE_SLCD_HAS_LCD_WAIT
    gcrReg |= LCD_GCR_LCDWAIT(((uint32_t)configure->lowPowerBehavior >> 1U) & 0x1U);
    gcrMsk |= LCD_GCR_LCDWAIT_MASK;
#endif
#if FSL_FEATURE_SLCD_HAS_LCD_DOZE_ENABLE
    gcrReg |= LCD_GCR_LCDDOZE(((uint32_t)configure->lowPowerBehavior >> 1U) & 0x1U);
    gcrMsk |= LCD_GCR_LCDDOZE_MASK;
#endif
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    /* Configure for frame frequency interrupt. */
    gcrReg |= LCD_GCR_LCDIEN(configure->frameFreqIntEnable);
    gcrMsk |= LCD_GCR_LCDIEN_MASK;
#endif /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */
#if FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE
    /* Select the alternate clock for alternate clock source. */
    gcrReg |= LCD_GCR_ALTSOURCE((((uint32_t)configure->clkConfig->clkSource) >> 1U) & 0x1U);
    gcrMsk |= LCD_GCR_ALTSOURCE_MASK;
#endif /* FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE */
#if FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE
    /* Configure the for fast frame rate. */
    gcrReg |= LCD_GCR_FFR(configure->clkConfig->fastFrameRateEnable ? 1U : 0U);
    gcrMsk |= LCD_GCR_FFR_MASK;
#endif /* FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE */

    gcrReg |= LCD_GCR_RVTRIM(configure->voltageTrim);
    gcrMsk |= LCD_GCR_RVTRIM_MASK;

    base->GCR = (base->GCR & ~gcrMsk) | gcrReg;

    /* Set display mode. */
    base->AR = LCD_AR_ALT((uint32_t)configure->displayMode & 0x1U) |
               LCD_AR_BLANK(((uint32_t)configure->displayMode >> 1U) & 0x1U);

    /* Configure the front plane and back plane pin setting. */
    base->BPEN[0] = configure->backPlaneLowPin;
    base->BPEN[1] = configure->backPlaneHighPin;
    base->PEN[0]  = configure->slcdLowPinEnabled;
    base->PEN[1]  = configure->slcdHighPinEnabled;

    /* Set the fault frame detection. */
    base->FDCR = 0;
    if (NULL != configure->faultConfig)
    {
        /* If fault configure structure is not NULL, the fault detection is enabled. */
        base->FDCR = LCD_FDCR_FDPRS(configure->faultConfig->faultPrescaler) |
                     LCD_FDCR_FDSWW(configure->faultConfig->width) |
                     LCD_FDCR_FDBPEN(configure->faultConfig->faultDetectBackPlaneEnable ? 1U : 0U) |
                     LCD_FDCR_FDPINID(configure->faultConfig->faultDetectPinIndex) | LCD_FDCR_FDEN_MASK;
        if (configure->faultConfig->faultDetectIntEnable)
        {
            base->GCR |= LCD_GCR_FDCIEN_MASK;
            intEnabled = true;
        }
    }

    /* Initialize the Waveform. */
    for (regNum = 0; regNum < SLCD_WAVEFORM_CONFIG_NUM; regNum++)
    {
        base->WF[regNum] = 0;
    }

/* Enable the NVIC. */
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    if (configure->frameFreqIntEnable)
    {
        intEnabled = true;
    }
#endif /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */
    if (intEnabled)
    {
        (void)EnableIRQ(LCD_IRQn);
    }
}

/*!
 * brief Deinitializes the SLCD module, gates the module clock, disables an interrupt,
 * and displays the SLCD.
 *
 * param base  SLCD peripheral base address.
 */
void SLCD_Deinit(LCD_Type *base)
{
    uint32_t instance = SLCD_GetInstance(base);

    /* Stop SLCD display. */
    SLCD_StopDisplay(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the SLCD clock. */
    CLOCK_DisableClock(s_slcdClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable NVIC. */
    (void)DisableIRQ(LCD_IRQn);
}

/*!
 * brief Gets the SLCD default configuration structure. The
 * purpose of this API is to get default parameters of the configuration structure
 * for the SLCD_Init(). Use these initialized parameters unchanged in SLCD_Init()
 * or modify fields of the structure before the calling SLCD_Init().
 * All default parameters of the configure structuration are listed.
 * code
   config.displayMode        = kSLCD_NormalMode;
   config.powerSupply        = kSLCD_InternalVll3UseChargePump;
   config.voltageTrim        = kSLCD_RegulatedVolatgeTrim00;
   config.lowPowerBehavior   = kSLCD_EnabledInWaitStop;
   config.interruptSrc       = 0;
   config.faultConfig        = NULL;
   config.frameFreqIntEnable =  false;
   endcode
 * param configure The SLCD configuration structure pointer.
 */
void SLCD_GetDefaultConfig(slcd_config_t *configure)
{
    assert(configure);

    /* Initializes the configure structure to zero. */
    (void)memset(configure, 0, sizeof(*configure));

    /* Get Default parameters for the configuration structure. */
    /* SLCD in normal mode. */
    configure->displayMode = kSLCD_NormalMode;
    /* Power supply default: use charge pump to generate VLL1 and VLL2, VLL3 connected to VDD internally. */
    configure->powerSupply = kSLCD_InternalVll3UseChargePump;
    configure->voltageTrim = kSLCD_RegulatedVolatgeTrim08;
    /* Work in low power mode. */
    configure->lowPowerBehavior = kSLCD_EnabledInWaitStop;
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    /* No interrupt source is enabled. */
    configure->frameFreqIntEnable = false;
#endif /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */
    /* Fault detection is disabled. */
    configure->faultConfig = NULL;
}

/*!
 * brief Starts the SLCD blink mode.
 *
 * param base  SLCD peripheral base address.
 * param mode  SLCD blink mode.
 * param rate  SLCD blink rate.
 */
void SLCD_StartBlinkMode(LCD_Type *base, slcd_blink_mode_t mode, slcd_blink_rate_t rate)
{
    uint32_t mask  = LCD_AR_BMODE_MASK | LCD_AR_BRATE_MASK;
    uint32_t arReg = base->AR;

#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    mask |= LCD_AR_LCDIF_MASK;
#endif /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */

    arReg &= ~mask;
    /* Set blink mode and blink rate. */
    arReg |= LCD_AR_BMODE(mode) | LCD_AR_BRATE(rate);
    base->AR = arReg;

    /* Enable Blink after setting the blink rate to meet some hardware requirement. */
    arReg |= LCD_AR_BLINK_MASK;
    base->AR = arReg;
}

/*!
 * brief Enables the SLCD interrupt.
 * For example, to enable fault detect complete interrupt and frame frequency interrupt,
 * for FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT enabled case, do the following.
 * code
 *     SLCD_EnableInterrupts(LCD,kSLCD_FaultDetectCompleteInterrupt | kSLCD_FrameFreqInterrupt);
 * endcode
 *
 * param base  SLCD peripheral base address.
 * param mask  SLCD interrupts to enable. This is a logical OR of the
 *             enumeration :: slcd_interrupt_enable_t.
 */
void SLCD_EnableInterrupts(LCD_Type *base, uint32_t mask)
{
    uint32_t gcReg = base->GCR;

    gcReg |= LCD_GCR_FDCIEN(mask & 0x1U);
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    gcReg |= LCD_GCR_LCDIEN((mask >> 1U) & 0x1U);
#endif /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */

    base->GCR = gcReg;
}

/*!
 * brief Disables the SLCD interrupt.
 * For example, to disable fault detect complete interrupt and frame frequency interrupt,
 * for FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT enabled case, do the following.
 * code
 *     SLCD_DisableInterrupts(LCD,kSLCD_FaultDetectCompleteInterrupt | kSLCD_FrameFreqInterrupt);
 * endcode
 *
 * param base  SLCD peripheral base address.
 * param mask  SLCD interrupts to disable. This is a logical OR of the
 *             enumeration :: slcd_interrupt_enable_t.
 */
void SLCD_DisableInterrupts(LCD_Type *base, uint32_t mask)
{
    uint32_t gcrReg = base->GCR;

    /*!< SLCD fault detection complete interrupt source. */
    if (0U != (mask & (uint32_t)kSLCD_FaultDetectCompleteInterrupt))
    {
        gcrReg &= ~LCD_GCR_FDCIEN_MASK;
    }
/*!< SLCD frame frequency interrupt source. */
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    if (0U != (mask & (uint32_t)kSLCD_FrameFreqInterrupt))
    {
        gcrReg &= ~LCD_GCR_LCDIEN_MASK;
    }
#endif /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */

    base->GCR = gcrReg;
}

/*!
 * brief Clears the SLCD interrupt events status flag.
 *
 * param base  SLCD peripheral base address.
 * param mask  SLCD interrupt source to be cleared.
 * This is the logical OR of members of the enumeration :: slcd_interrupt_enable_t.
 */
void SLCD_ClearInterruptStatus(LCD_Type *base, uint32_t mask)
{
    /*!< SLCD fault detection complete interrupt source. */
    if (0U != (mask & (uint32_t)kSLCD_FaultDetectCompleteInterrupt))
    {
        base->FDSR |= LCD_FDSR_FDCF_MASK;
    }
/*!< SLCD frame frequency interrupt source. */
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    if (0U != (mask & (uint32_t)kSLCD_FrameFreqInterrupt))
    {
        base->AR |= LCD_AR_LCDIF_MASK;
    }
#endif /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */
}

/*!
 * brief Gets the SLCD interrupt status flag.
 *
 * param base  SLCD peripheral base address.
 * return The event status of the interrupt source. This is the logical OR of members
 *         of the enumeration :: slcd_interrupt_enable_t.
 */
uint32_t SLCD_GetInterruptStatus(LCD_Type *base)
{
    uint32_t status = 0;

    /* Get the frame detect complete interrupt status. */
    status = ((base->FDSR & LCD_FDSR_FDCF_MASK) >> LCD_FDSR_FDCF_SHIFT);

#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    /* Get the frame frequency interrupt status. */
    status |= ((base->AR & LCD_AR_LCDIF_MASK) >> (LCD_AR_LCDIF_SHIFT - 1U));
#endif /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */

    return status;
}
