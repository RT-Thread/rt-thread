/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_gdet.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.gdet"
#endif

#define ISOLATE_ON  (0x2u << 2)
#define ISOLATE_OFF (0x0u << 2)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * Weak implementation of GDET IRQ, should be re-defined by user when using GDET IRQ
 */
__WEAK void GDET_DriverIRQHandler(void)
{
    /* GDET generates IRQ if voltage glitching is detected
     */
}

/*!
 * brief Initialize GDET
 *
 * This function initializes GDET setting and enable interrupts.
 *
 * param base GDET peripheral base address
 * return Status of the init operation
 */
status_t GDET_Init(GDET_Type *base)
{
    /* Ungate clock to GDET engine and reset it */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Gdet);
#endif /* !FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    NVIC_EnableIRQ(GDET_IRQn);

    return kStatus_Success;
}

/*!
 * brief Deinitialize GDET
 *
 * This function stops GDET glitch detector.
 *
 * param base GDET peripheral base address
 */
void GDET_Deinit(GDET_Type *base)
{
    NVIC_DisableIRQ(GDET_IRQn);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

    CLOCK_DisableClock(kCLOCK_Gdet);
#endif /* !FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/* Array of GDET peripheral base address. */
static GDET_Type *const s_gdetBases[] = GDET_BASE_PTRS;

/*!
 * brief Get the GDET instance from peripheral base address.
 *
 * param base GDET peripheral base address.
 * return GDET instance.
 */
static uint32_t GDET_GetInstance(GDET_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_gdetBases); instance++)
    {
        if (s_gdetBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_gdetBases));

    return instance;
}

status_t GDET_IsolateOn(GDET_Type *base)
{
    status_t status = kStatus_Fail;
    uint32_t instance;

    instance = GDET_GetInstance(base);

    SYSCON->GDET_CTRL[instance] = ISOLATE_ON;

    if (ISOLATE_ON != SYSCON->GDET_CTRL[instance])
    {
        return kStatus_Fail;
    }
    status = kStatus_Success;

    return status;
}

status_t GDET_IsolateOff(GDET_Type *base)
{
    status_t status = kStatus_Fail;
    uint32_t instance;

    instance = GDET_GetInstance(base);

    SYSCON->GDET_CTRL[instance] = ISOLATE_ON;

    if (ISOLATE_ON != SYSCON->GDET_CTRL[instance])
    {
        return kStatus_Fail;
    }
    status = kStatus_Success;

    return status;
}

status_t GDET_ReconfigureVoltageMode(GDET_Type *base, gdet_core_voltage_t voltage)
{
    uint32_t tmp0   = 0;
    status_t status = kStatus_Fail;

    if ((voltage != kGDET_MidVoltage) && (voltage != kGDET_NormalVoltage) && (voltage != kGDET_OverDriveVoltage))
    {
        return kStatus_InvalidArgument;
    }

    /*Change the GDET_DLY_CTRL to select the new drive mode (and set high also GDET_DLY_CTRL[SW_VOL_CTRL] for a SW
     * control)*/
    tmp0 = (((uint32_t)voltage) << GDET_GDET_DLY_CTRL_VOL_SEL_SHIFT);
    tmp0 |= GDET_GDET_DLY_CTRL_SW_VOL_CTRL_MASK;
    base->GDET_DLY_CTRL = tmp0;

    /*Write high the GDET_RESET[SFT_RST] to issue a fast update of the detector to the new voltage level.*/
    base->GDET_RESET = GDET_GDET_RESET_SFT_RST(1u);

    /* according to the GDET module documentation, the GDET_CFG[SFT_RST] reads as 0 */
    if (0u == (GDET_GDET_RESET_SFT_RST_MASK & base->GDET_RESET))
    {
        status = kStatus_Success;
    }

    return status;
}
