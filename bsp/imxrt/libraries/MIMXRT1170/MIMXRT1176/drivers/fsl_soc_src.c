/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_soc_src.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.soc_src"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_MASK (0x3U)
#define SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_CONFIG(resetSource, resetMode) \
    ((uint32_t)(resetMode) << (uint32_t)(resetSource))

#define SRC_SLICE_CTRL_SW_RESET_MASK (0x1U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Release related core reset operation.
 *
 * The core reset will be held until boot core to release it.
 *
 * param base SRC peripheral base address.
 * param coreName The name of the reset core to be released.
 */
void SRC_ReleaseCoreReset(SRC_Type *base, src_core_name_t coreName)
{
    uint32_t coreMaskArray[] = {SRC_SCR_BT_RELEASE_M7_MASK, SRC_SCR_BT_RELEASE_M4_MASK};
    uint32_t regValue;

    regValue = base->SCR;

    if ((regValue & coreMaskArray[((uint32_t)coreName) - 1UL]) == 0UL)
    {
        base->SCR |= coreMaskArray[((uint32_t)coreName) - 1UL];
    }
}

/*!
 * brief Sets the reset mode of global system reset source.
 *
 * This function sets the selected mode of the input global system reset sources. This function will return as soon as
 * the reset if finished.
 *
 * param base SRC peripheral base address.
 * param resetSource The global system reset source. See @ref src_global_system_reset_source_t for more details.
 * param resetMode The reset mode of each reset source. See @ref src_global_system_reset_mode_t for more details.
 */
void SRC_SetGlobalSystemResetMode(SRC_Type *base,
                                  src_global_system_reset_source_t resetSource,
                                  src_global_system_reset_mode_t resetMode)
{
    uint32_t regValue;

    regValue = base->SRMR;
    regValue &= ~SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_CONFIG(resetSource, SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_MASK);
    regValue |= SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_CONFIG(resetSource, resetMode);

    base->SRMR = regValue;
}

/*!
 * brief Asserts software reset for the selected slice.
 *
 * param base SRC peripheral base address.
 * param sliceName The selected reset slice. See @ref src_reset_slice_name_t for more details.
 */
void SRC_AssertSliceSoftwareReset(SRC_Type *base, src_reset_slice_name_t sliceName)
{
    uint32_t regAddress;
    uint32_t sliceStatusRegAddress;

    regAddress            = SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, SRC_SLICE_CONTROL_REGISTER_OFFSET);
    sliceStatusRegAddress = SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, SRC_SLICE_STATUS_REGISTER_OFFSET);

    *(volatile uint32_t *)regAddress |= SRC_SLICE_CTRL_SW_RESET_MASK;

    while (((*(volatile uint32_t *)sliceStatusRegAddress) & SRC_SLICE_STAT_UNDER_RST_MASK) != 0UL)
    {
        ;
    }
}

/*!
 * brief Locks the value of SETPOINT_MODE and DOMAIN_MODE for the selected reset slice.
 *
 * param base SRC peripheral base address.
 * param sliceName The selected reset slice. See @ref src_reset_slice_name_t for more details.
 */
void SRC_LockSliceMode(SRC_Type *base, src_reset_slice_name_t sliceName)
{
    uint32_t authenticationRegAddress;

    authenticationRegAddress =
        SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, SRC_SLICE_AUTHENTICATION_REGISTER_OFFSET);

    *(volatile uint32_t *)authenticationRegAddress |= SRC_SLICE_AUTHEN_LOCK_MODE_MASK;
}

/*!
 * brief Sets setpoint configuration for the selected reset slice.
 *
 * param base SRC peripheral base address.
 * param sliceName The selected reset slice. See @ref src_reset_slice_name_t for more details.
 * param setPointConfig The logic OR'ed value of @ref _src_setpoint_selection. When the system in the selected setpoint
 * slice reset will be assert.
 */
void SRC_SetSliceSetPointConfig(SRC_Type *base, src_reset_slice_name_t sliceName, uint32_t setpointConfig)
{
    uint32_t setpointConfigRegAddress;

    setpointConfigRegAddress =
        SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, SRC_SLICE_SETPOINT_CONFIG_REGISTER_OFFSET);

    if (setpointConfig != 0UL)
    {
        *(volatile uint32_t *)setpointConfigRegAddress = setpointConfig;
    }
}

/*!
 * brief Sets domain mode configuration for the selected reset slice.
 *
 * param base SRC peripheral base address.
 * param sliceName The selected reset slice. See src_reset_slice_name_t for more details.
 * param domainConfig The logic OR'ed value of _src_domain_mode_selection.
 */
void SRC_SetSliceDomainModeConfig(SRC_Type *base, src_reset_slice_name_t sliceName, uint32_t domainConfig)
{
    uint32_t domainConfigRegAddress;

    domainConfigRegAddress = SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, SRC_SLICE_DOMAIN_CONFIG_REGISTER_OFFSET);

    if (domainConfig != 0UL)
    {
        *(volatile uint32_t *)domainConfigRegAddress = domainConfig;
    }
}

/*!
 * brief Gets the reset state of the selected slice.
 *
 * param base SRC peripheral base address.
 * param sliceName The selected slice. See @ref src_reset_slice_name_t for more details.
 * retval kSRC_SliceResetInProcess The reset is in process.
 * retval kSRC_SliceResetFinished  The reset is finished.
 */
src_slice_reset_state_t SRC_GetSliceResetState(SRC_Type *base, src_reset_slice_name_t sliceName)
{
    uint32_t statusRegAddress;
    src_slice_reset_state_t ret;

    statusRegAddress = SRC_GET_SLICE_REGISTER_ADDRESS(base, sliceName, SRC_SLICE_STATUS_REGISTER_OFFSET);

    if (((*(uint32_t *)statusRegAddress) & SRC_SLICE_STAT_UNDER_RST_MASK) != 0UL)
    {
        ret = kSRC_SliceResetInProcess;
    }
    else
    {
        ret = kSRC_SliceResetFinished;
    }

    return ret;
}
