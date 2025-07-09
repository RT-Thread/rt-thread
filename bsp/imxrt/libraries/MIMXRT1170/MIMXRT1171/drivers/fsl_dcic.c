/*
 * Copyright 2020-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dcic.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dcic"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for DCIC module.
 *
 * @param base DCIC peripheral base address.
 */
static uint32_t DCIC_GetInstance(const DCIC_Type *base);

static void DCIC_ResetRegister(DCIC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to dcic clocks for each instance. */
static const clock_ip_name_t s_dcicClocks[] = DCIC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t DCIC_GetInstance(const DCIC_Type *base)
{
    static DCIC_Type *const s_dcicBases[] = DCIC_BASE_PTRS;

    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dcicBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_dcicBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dcicBases));

    return instance;
}

#define DCIC_DCCIC_RESET_VALUE  (DCIC_DCICC_VSYNC_POL_MASK | DCIC_DCICC_HSYNC_POL_MASK | DCIC_DCICC_DE_POL_MASK)
#define DCIC_DCICIC_RESET_VALUE (DCIC_DCICIC_FI_MASK_MASK | DCIC_DCICIC_EI_MASK_MASK)

static void DCIC_ResetRegister(DCIC_Type *base)
{
    uint32_t i;

    base->DCICC  = DCIC_DCCIC_RESET_VALUE;
    base->DCICIC = DCIC_DCICIC_RESET_VALUE;

    /* Reset region registers. */
    for (i = 0; i < DCIC_REGION_COUNT; i++)
    {
        base->REGION[i].DCICRC  = 0UL;
        base->REGION[i].DCICRS  = 0UL;
        base->REGION[i].DCICRRS = 0UL;
    }

    /* Clear all status. */
    base->DCICS = (DCIC_DCICS_EI_STAT_MASK | DCIC_DCICS_FI_STAT_MASK | DCIC_DCICS_ROI_MATCH_STAT_MASK);
}

/*
 * brief Initializes the DCIC.
 *
 * param base   DCIC peripheral base address.
 * param config Pointer to the configuration.
 */
void DCIC_Init(DCIC_Type *base, const dcic_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && (0 != FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
    /* Enable the clock. */
    (void)CLOCK_EnableClock(s_dcicClocks[DCIC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    DCIC_ResetRegister(base);

    base->DCICC = config->polarityFlags;

    DCIC_EnableMismatchExternalSignal(base, config->enableExternalSignal);
    DCIC_EnableInterrupts(base, config->enableInterrupts);
}

/*
 * brief Disable the DCIC.
 *
 * param base DCIC peripheral base address.
 */
void DCIC_Deinit(DCIC_Type *base)
{
    base->DCICC = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && (0 != FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
    /* Disable the clock. */
    (void)CLOCK_DisableClock(s_dcicClocks[DCIC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * Get the default configuration to initialize DCIC.
 *
 * The default configuration is:
 *
    config->polarityFlags = kDCIC_VsyncActiveLow | kDCIC_HsyncActiveLow |
                            kDCIC_DataEnableActiveLow | kDCIC_DriveDataOnFallingClkEdge;
    config->enableExternalSignal = false;
    config->enableInterrupts = 0;
 *
 * param config Pointer to the configuration.
 */
void DCIC_GetDefaultConfig(dcic_config_t *config)
{
    assert(NULL != config);

    config->polarityFlags = (uint8_t)kDCIC_VsyncActiveLow | (uint8_t)kDCIC_HsyncActiveLow |
                            (uint8_t)kDCIC_DataEnableActiveLow | (uint8_t)kDCIC_DriveDataOnFallingClkEdge;
    config->enableExternalSignal = false;
    config->enableInterrupts     = 0;
}

/*
 * brief Enable the region of interest (ROI) with configuration.
 *
 * Enable the ROI with configuration. To change the configuration except reference
 * CRC value, the region should be disabled first by ref DCIC_DisableRegion,
 * then call this function again. The reference CRC value could be changed by
 * ref DCIC_SetRegionRefCrc without disabling the region.
 * If the configuration is locked, only the reference CRC value could be changed,
 * the region size and position, enable status could not be changed until reset.
 *
 * param base DCIC peripheral base address.
 * param regionIdx Region index, from 0 to (DCIC_REGION_COUNT - 1).
 * param config Pointer to the configuration.
 */
void DCIC_EnableRegion(DCIC_Type *base, uint8_t regionIdx, const dcic_region_config_t *config)
{
    assert(regionIdx < DCIC_REGION_COUNT);
    assert(NULL != config);

    if (regionIdx < DCIC_REGION_COUNT)
    {
        base->REGION[regionIdx].DCICRRS = config->refCrc;

        base->REGION[regionIdx].DCICRS = (((uint32_t)config->lowerRightX << DCIC_DCICRS_END_OFFSET_X_SHIFT) |
                                          ((uint32_t)config->lowerRightY << DCIC_DCICRS_END_OFFSET_Y_SHIFT));

        base->REGION[regionIdx].DCICRC = (((uint32_t)config->upperLeftX << DCIC_DCICRC_START_OFFSET_X_SHIFT) |
                                          ((uint32_t)config->upperLeftY << DCIC_DCICRC_START_OFFSET_Y_SHIFT) |
                                          (config->lock ? DCIC_DCICRC_ROI_FREEZE_MASK : 0UL) | DCIC_DCICRC_ROI_EN_MASK);
    }
}
