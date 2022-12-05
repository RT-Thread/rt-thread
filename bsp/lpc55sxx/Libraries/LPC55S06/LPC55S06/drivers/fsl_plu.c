/*
 * Copyright  2018-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_plu.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.plu"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Gets the instance from the base address
 *
 * @param base PLU peripheral base address
 *
 * @return The PLU instance
 */
static uint32_t PLU_GetInstance(PLU_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to PLU bases for each instance. */
static PLU_Type *const s_pluBases[] = PLU_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to PLU clocks for each instance. */
static const clock_ip_name_t s_pluClocks[] = PLU_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
/*! @brief Pointers to PLU resets for each instance. */
static const reset_ip_name_t s_lpuResets[] = PLU_RSTS_N;
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t PLU_GetInstance(PLU_Type *base)
{
    uint32_t instance;
    uint32_t pluArrayCount = (sizeof(s_pluBases) / sizeof(s_pluBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < pluArrayCount; instance++)
    {
        if (s_pluBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < pluArrayCount);

    return instance;
}

/*!
 * brief Ungates the PLU clock and reset the module.
 *
 * note This API should be called at the beginning of the application using the PLU driver.
 *
 * param base PLU peripheral base address
 */
void PLU_Init(PLU_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the PLU peripheral clock */
    CLOCK_EnableClock(s_pluClocks[PLU_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(s_lpuResets[PLU_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
}

/*!
 * brief Gate the PLU clock
 *
 * param base PLU peripheral base address
 */
void PLU_Deinit(PLU_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the module clock */
    CLOCK_DisableClock((s_pluClocks[PLU_GetInstance(base)]));
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

#if defined(FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG) && FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG
/*!
 * @brief Gets an available pre-defined settings for wakeup/interrupt control.
 *
 * This function initializes the initial configuration structure with an available settings. The default values are:
 * @code
 *   config->filterMode = kPLU_WAKEINT_FILTER_MODE_BYPASS;
 *   config->clockSource = kPLU_WAKEINT_FILTER_CLK_SRC_1MHZ_LPOSC;
 * @endcode
 * @param config Pointer to configuration structure.
 */
void PLU_GetDefaultWakeIntConfig(plu_wakeint_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->filterMode  = kPLU_WAKEINT_FILTER_MODE_BYPASS;
    config->clockSource = kPLU_WAKEINT_FILTER_CLK_SRC_1MHZ_LPOSC;
}

/*!
 * @brief Enable PLU outputs wakeup/interrupt request.
 *
 * This function enables Any of the eight selected PLU outputs to contribute to an asynchronous wake-up or an interrupt
 * request.
 *
 * Note: If a PLU_CLKIN is provided, the raw wake-up/interrupt request will be set on the rising-edge of the PLU_CLKIN
 * whenever the raw request signal is high. This registered signal will be glitch-free and just use the default wakeint
 * config by PLU_GetDefaultWakeIntConfig(). If not, have to specify the filter mode and clock source to eliminate the
 * glitches caused by long and widely disparate delays through the network of LUTs making up the PLU. This way may
 * increase power consumption in low-power operating modes and inject delay before the wake-up/interrupt request is
 * generated.
 *
 * @param base PLU peripheral base address.
 * @param interruptMask PLU interrupt mask (see @ref _plu_interrupt_mask enumeration).
 * @param config Pointer to configuration structure (see @ref plu_wakeint_config_t typedef enumeration)
 */
void PLU_EnableWakeIntRequest(PLU_Type *base, uint32_t interruptMask, const plu_wakeint_config_t *config)
{
    uint32_t tmp32 = 0U;

    tmp32 = PLU_WAKEINT_CTRL_FILTER_MODE(config->filterMode) | PLU_WAKEINT_CTRL_FILTER_CLKSEL(config->clockSource) |
            PLU_WAKEINT_CTRL_MASK(interruptMask);

    base->WAKEINT_CTRL = tmp32;
}

/*!
 * @brief Clear the latched interrupt
 *
 * This function clears the wake-up/interrupt request flag latched by PLU_LatchInterrupt()
 *
 * Note: It is not necessary for the PLU bus clock to be enabled in order to write-to or read-back this bit.
 *
 * @param base PLU peripheral base address.
 */
void PLU_ClearLatchedInterrupt(PLU_Type *base)
{
    base->WAKEINT_CTRL |= PLU_WAKEINT_CTRL_INTR_CLEAR_MASK;
    /* It will take a delay of up to 1.5 PLU_CLKIN clock cycles before this write-to-clear takes effect. */
    while (PLU_WAKEINT_CTRL_INTR_CLEAR_MASK == (base->WAKEINT_CTRL & PLU_WAKEINT_CTRL_INTR_CLEAR_MASK))
    {
    }
}
#endif /* FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG */
