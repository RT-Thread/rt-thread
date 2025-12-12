/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rgpio.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rgpio"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
static PORT_Type *const s_portBases[] = PORT_BASE_PTRS;
#endif /* FSL_FEATURE_SOC_PORT_COUNT */

static RGPIO_Type *const s_rgpioBases[] = RGPIO_BASE_PTRS;

#if defined(FSL_FEATURE_SOC_FGPIO_COUNT) && FSL_FEATURE_SOC_FGPIO_COUNT

#if defined(FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL) && FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Array to map FGPIO instance number to clock name. */
static const clock_ip_name_t s_fgpioClockName[] = FGPIO_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#endif /* FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL */

#endif /* FSL_FEATURE_SOC_FGPIO_COUNT */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Gets the RGPIO instance according to the RGPIO base
 *
 * param base    RGPIO peripheral base pointer(PTA, PTB, PTC, etc.)
 * retval RGPIO instance
 */
uint32_t RGPIO_GetInstance(RGPIO_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_rgpioBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_rgpioBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_rgpioBases));

    return instance;
}

/*!
 * brief Initializes a RGPIO pin used by the board.
 *
 * To initialize the RGPIO, define a pin configuration, as either input or output, in the user file.
 * Then, call the RGPIO_PinInit() function.
 *
 * This is an example to define an input pin or an output pin configuration.
 * code
 *  Define a digital input pin configuration,
 * rgpio_pin_config_t config =
 * {
 *   kRGPIO_DigitalInput,
 *   0,
 * }
 * Define a digital output pin configuration,
 * rgpio_pin_config_t config =
 * {
 *   kRGPIO_DigitalOutput,
 *   0,
 * }
 * endcode
 *
 * param base   RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * param pin    RGPIO port pin number
 * param config RGPIO pin configuration pointer
 */
void RGPIO_PinInit(RGPIO_Type *base, uint32_t pin, const rgpio_pin_config_t *config)
{
    assert(NULL != config);

    if (config->pinDirection == kRGPIO_DigitalInput)
    {
        base->PDDR &= ~(1UL << pin);
    }
    else
    {
        RGPIO_WritePinOutput(base, pin, config->outputLogic);
        base->PDDR |= (1UL << pin);
    }
}

#if defined(FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
/*!
 * brief Reads the RGPIO port interrupt status flag.
 *
 * If a pin is configured to generate the DMA request, the corresponding flag
 * is cleared automatically at the completion of the requested DMA transfer.
 * Otherwise, the flag remains set until a logic one is written to that flag.
 * If configured for a level sensitive interrupt that remains asserted, the flag
 * is set again immediately.
 *
 * param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * retval The current RGPIO port interrupt status flag, for example, 0x00010001 means the
 *         pin 0 and 17 have the interrupt.
 */
uint32_t RGPIO_PortGetInterruptFlags(RGPIO_Type *base)
{
    uint8_t instance;
    PORT_Type *portBase;
    instance = RGPIO_GetInstance(base);
    portBase = s_portBases[instance];
    return portBase->ISFR;
}

/*!
 * brief Clears multiple RGPIO pin interrupt status flags.
 *
 * param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * param mask RGPIO pin number macro
 */
void RGPIO_PortClearInterruptFlags(RGPIO_Type *base, uint32_t mask)
{
    uint8_t instance;
    PORT_Type *portBase;
    instance       = RGPIO_GetInstance(base);
    portBase       = s_portBases[instance];
    portBase->ISFR = mask;
}
#endif /* FSL_FEATURE_SOC_PORT_COUNT */

#if defined(FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER) && FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER
/*!
 * brief The RGPIO module supports a device-specific number of data ports, organized as 32-bit
 * words. Each 32-bit data port includes a GACR register, which defines the byte-level
 * attributes required for a successful access to the RGPIO programming model. The attribute controls for the 4 data
 * bytes in the GACR follow a standard little endian
 * data convention.
 *
 * param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * param mask RGPIO pin number macro
 */
void RGPIO_CheckAttributeBytes(RGPIO_Type *base, rgpio_checker_attribute_t attribute)
{
    base->GACR = ((uint32_t)attribute << RGPIO_GACR_ACB0_SHIFT) | ((uint32_t)attribute << RGPIO_GACR_ACB1_SHIFT) |
                 ((uint32_t)attribute << RGPIO_GACR_ACB2_SHIFT) | ((uint32_t)attribute << RGPIO_GACR_ACB3_SHIFT);
}
#endif

#if defined(FSL_FEATURE_SOC_FGPIO_COUNT) && FSL_FEATURE_SOC_FGPIO_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/
static FGPIO_Type *const s_fgpioBases[] = FGPIO_BASE_PTRS;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Gets the FGPIO instance according to the RGPIO base
 *
 * param base    FGPIO peripheral base pointer(PTA, PTB, PTC, etc.)
 * retval FGPIO instance
 */
uint32_t FGPIO_GetInstance(FGPIO_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_fgpioBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_fgpioBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_fgpioBases));

    return instance;
}

#if defined(FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL) && FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL
void FGPIO_PortInit(FGPIO_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate FGPIO periphral clock */
    CLOCK_EnableClock(s_fgpioClockName[FGPIO_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
#endif /* FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL */

/*!
 * brief Initializes a FGPIO pin used by the board.
 *
 * To initialize the FGPIO driver, define a pin configuration, as either input or output, in the user file.
 * Then, call the FGPIO_PinInit() function.
 *
 * This is an example to define an input pin or an output pin configuration:
 * code
 * Define a digital input pin configuration,
 * rgpio_pin_config_t config =
 * {
 *   kRGPIO_DigitalInput,
 *   0,
 * }
 * Define a digital output pin configuration,
 * rgpio_pin_config_t config =
 * {
 *   kRGPIO_DigitalOutput,
 *   0,
 * }
 * endcode
 *
 * param base   FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * param pin    FGPIO port pin number
 * param config FGPIO pin configuration pointer
 */
void FGPIO_PinInit(FGPIO_Type *base, uint32_t pin, const rgpio_pin_config_t *config)
{
    assert(NULL != config);

#if defined(FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL) && FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate FGPIO periphral clock */
    CLOCK_EnableClock(s_fgpioClockName[FGPIO_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL */

    if (config->pinDirection == kRGPIO_DigitalInput)
    {
        base->PDDR &= ~(1UL << pin);
    }
    else
    {
        FGPIO_WritePinOutput(base, pin, config->outputLogic);
        base->PDDR |= (1UL << pin);
    }
}

#if defined(FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
/*!
 * brief Reads the FGPIO port interrupt status flag.
 *
 * If a pin is configured to generate the DMA request, the corresponding flag
 * is cleared automatically at the completion of the requested DMA transfer.
 * Otherwise, the flag remains set until a logic one is written to that flag.
 * If configured for a level-sensitive interrupt that remains asserted, the flag
 * is set again immediately.
 *
 * param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * retval The current FGPIO port interrupt status flags, for example, 0x00010001 means the
 *         pin 0 and 17 have the interrupt.
 */
uint32_t FGPIO_PortGetInterruptFlags(FGPIO_Type *base)
{
    uint8_t instance;
    instance = FGPIO_GetInstance(base);
    PORT_Type *portBase;
    portBase = s_portBases[instance];
    return portBase->ISFR;
}

/*!
 * brief Clears the multiple FGPIO pin interrupt status flag.
 *
 * param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * param mask FGPIO pin number macro
 */
void FGPIO_PortClearInterruptFlags(FGPIO_Type *base, uint32_t mask)
{
    uint8_t instance;
    instance = FGPIO_GetInstance(base);
    PORT_Type *portBase;
    portBase       = s_portBases[instance];
    portBase->ISFR = mask;
}
#endif /* FSL_FEATURE_SOC_PORT_COUNT */

#if defined(FSL_FEATURE_FGPIO_HAS_ATTRIBUTE_CHECKER) && FSL_FEATURE_FGPIO_HAS_ATTRIBUTE_CHECKER
/*!
 * brief The FGPIO module supports a device-specific number of data ports, organized as 32-bit
 * words. Each 32-bit data port includes a GACR register, which defines the byte-level
 * attributes required for a successful access to the RGPIO programming model. The attribute controls for the 4 data
 * bytes in the GACR follow a standard little endian
 * data convention.
 *
 * param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * param mask FGPIO pin number macro
 */
void FGPIO_CheckAttributeBytes(FGPIO_Type *base, rgpio_checker_attribute_t attribute)
{
    base->GACR = (attribute << FGPIO_GACR_ACB0_SHIFT) | (attribute << FGPIO_GACR_ACB1_SHIFT) |
                 (attribute << FGPIO_GACR_ACB2_SHIFT) | (attribute << FGPIO_GACR_ACB3_SHIFT);
}
#endif

#endif /* FSL_FEATURE_SOC_FGPIO_COUNT */
