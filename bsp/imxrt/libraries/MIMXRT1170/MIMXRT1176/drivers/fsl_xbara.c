/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_xbara.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xbara"
#endif

/* Macros for entire XBARA_CTRL register.  */
#define XBARA_CTRLx(base, index) (((volatile uint16_t *)(&((base)->CTRL0)))[(index)])

typedef union
{
    uint8_t _u8[2];
    uint16_t _u16;
} xbara_u8_u16_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the XBARA instance from peripheral base address.
 *
 * @param base XBARA peripheral base address.
 * @return XBARA instance.
 */
static uint32_t XBARA_GetInstance(XBARA_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of XBARA peripheral base address. */
static XBARA_Type *const s_xbaraBases[] = XBARA_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of XBARA clock name. */
static const clock_ip_name_t s_xbaraClock[] = XBARA_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t XBARA_GetInstance(XBARA_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_xbaraBases); instance++)
    {
        if (s_xbaraBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_xbaraBases));

    return instance;
}

/*!
 * brief Initializes the XBARA module.
 *
 * This function un-gates the XBARA clock.
 *
 * param base XBARA peripheral address.
 */
void XBARA_Init(XBARA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable XBARA module clock. */
    CLOCK_EnableClock(s_xbaraClock[XBARA_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Shuts down the XBARA module.
 *
 * This function disables XBARA clock.
 *
 * param base XBARA peripheral address.
 */
void XBARA_Deinit(XBARA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable XBARA module clock. */
    CLOCK_DisableClock(s_xbaraClock[XBARA_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Sets a connection between the selected XBARA_IN[*] input and the XBARA_OUT[*] output signal.
 *
 * This function connects the XBARA input to the selected XBARA output.
 * If more than one XBARA module is available, only the inputs and outputs from the same module
 * can be connected.
 *
 * Example:
   code
   XBARA_SetSignalsConnection(XBARA, kXBARA_InputPIT_TRG0, kXBARA_OutputDMAMUX18);
   endcode
 *
 * param base XBARA peripheral address.
 * param input XBARA input signal.
 * param output XBARA output signal.
 */
void XBARA_SetSignalsConnection(XBARA_Type *base, xbar_input_signal_t input, xbar_output_signal_t output)
{
    xbara_u8_u16_t regVal;
    uint8_t byteInReg;
    uint8_t outputIndex = (uint8_t)output;

    byteInReg = outputIndex % 2U;

    regVal._u16 = XBARA_SELx(base, outputIndex);

    regVal._u8[byteInReg] = (uint8_t)input;

    XBARA_SELx(base, outputIndex) = regVal._u16;
}

/*!
 * brief Gets the active edge detection status.
 *
 * This function gets the active edge detect status of all XBARA_OUTs. If the
 * active edge occurs, the return value is asserted. When the interrupt or the DMA
 * functionality is enabled for the XBARA_OUTx, this field is 1 when the interrupt
 * or DMA request is asserted and 0 when the interrupt or DMA request has been
 * cleared.
 *
 * param base XBARA peripheral address.
 * return the mask of these status flag bits.
 */
uint32_t XBARA_GetStatusFlags(XBARA_Type *base)
{
    uint32_t status_flag;

    status_flag = ((uint32_t)base->CTRL0 & (XBARA_CTRL0_STS0_MASK | XBARA_CTRL0_STS1_MASK));

    status_flag |= (((uint32_t)base->CTRL1 & (XBARA_CTRL1_STS2_MASK | XBARA_CTRL1_STS3_MASK)) << 16U);

    return status_flag;
}

/*!
 * brief Clears the edge detection status flags of relative mask.
 *
 * param base XBARA peripheral address.
 * param mask the status flags to clear.
 */
void XBARA_ClearStatusFlags(XBARA_Type *base, uint32_t mask)
{
    uint16_t regVal;

    /* Assign regVal to CTRL0 register's value */
    regVal = (base->CTRL0);
    /* Perform this command to avoid writing 1 into interrupt flag bits */
    regVal &= (uint16_t)(~(XBARA_CTRL0_STS0_MASK | XBARA_CTRL0_STS1_MASK));
    /* Write 1 to interrupt flag bits corresponding to mask */
    regVal |= (uint16_t)(mask & (XBARA_CTRL0_STS0_MASK | XBARA_CTRL0_STS1_MASK));
    /* Write regVal value into CTRL0 register */
    base->CTRL0 = regVal;

    /* Assign regVal to CTRL1 register's value */
    regVal = (base->CTRL1);
    /* Perform this command to avoid writing 1 into interrupt flag bits */
    regVal &= (uint16_t)(~(XBARA_CTRL1_STS2_MASK | XBARA_CTRL1_STS3_MASK));
    /* Write 1 to interrupt flag bits corresponding to mask */
    regVal |= (uint16_t)((mask >> 16U) & (XBARA_CTRL1_STS2_MASK | XBARA_CTRL1_STS3_MASK));
    /* Write regVal value into CTRL1 register */
    base->CTRL1 = regVal;
}

/*!
 * brief Configures the XBARA control register.
 *
 * This function configures an XBARA control register. The active edge detection
 * and the DMA/IRQ function on the corresponding XBARA output can be set.
 *
 * Example:
   code
   xbara_control_config_t userConfig;
   userConfig.activeEdge = kXBARA_EdgeRising;
   userConfig.requestType = kXBARA_RequestInterruptEnalbe;
   XBARA_SetOutputSignalConfig(XBARA, kXBARA_OutputDMAMUX18, &userConfig);
   endcode
 *
 * param base XBARA peripheral address.
 * param output XBARA output number.
 * param controlConfig Pointer to structure that keeps configuration of control register.
 */
void XBARA_SetOutputSignalConfig(XBARA_Type *base,
                                 xbar_output_signal_t output,
                                 const xbara_control_config_t *controlConfig)
{
    uint8_t outputIndex = (uint8_t)output;
    uint8_t regIndex;
    uint8_t byteInReg;
    xbara_u8_u16_t regVal;

    assert(outputIndex < (uint32_t)FSL_FEATURE_XBARA_INTERRUPT_COUNT);

    regIndex  = outputIndex / 2U;
    byteInReg = outputIndex % 2U;

    regVal._u16 = XBARA_CTRLx(base, regIndex);

    /* Don't clear the status flags. */
    regVal._u16 &= (uint16_t)(~(XBARA_CTRL0_STS0_MASK | XBARA_CTRL0_STS1_MASK));

    regVal._u8[byteInReg] = (uint8_t)(XBARA_CTRL0_EDGE0(controlConfig->activeEdge) |
                                      (uint16_t)(((uint32_t)controlConfig->requestType) << XBARA_CTRL0_DEN0_SHIFT));

    XBARA_CTRLx(base, regIndex) = regVal._u16;
}
