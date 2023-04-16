/*******************************************************************************
* \file cy_lpcomp.c
* \version 1.50
*
* \brief
*  This file provides the driver code to the API for the Low Power Comparator
*  component.
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXLPCOMP) || defined (CY_IP_MXS22LPCOMP)

#include "cy_lpcomp.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (CY_IP_MXLPCOMP)
static cy_stc_lpcomp_context_t cy_lpcomp_context;
#endif

/*******************************************************************************
* Function Name: Cy_LPComp_Init_Ext
****************************************************************************//**
*
* Cy_LPComp_Init_Ext() is an extended version of existing function Cy_LPComp_Init().
* This implementation follows the thread-safe approach and is preferable for usage.
*
* This function initializes the low-power comparator and returns
* the status of the initialization.
*
* \note Interrupt edge-detect mode and drive power mode are not written to the registers
* during the function execution. This can result in unexpected interrupts
* when the comparator is enabled. Instead, the configurations are saved to the
* context and applied in the \ref Cy_LPComp_Enable_Ext() function.
*
* \param *base
*     The low-power comparator registers structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param *config
*     The pointer to the configuration structure for PDL.
*
* \param *context
* The pointer to the context structure \ref cy_stc_lpcomp_context_t allocated by the user.
* The structure is used during the low-power comparator operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return cy_en_lpcomp_status_t
*     *base checking result. If the pointer is NULL, returns an error.
*
*******************************************************************************/
cy_en_lpcomp_status_t Cy_LPComp_Init_Ext(LPCOMP_Type *base, cy_en_lpcomp_channel_t channel, const cy_stc_lpcomp_config_t *config,
                                        cy_stc_lpcomp_context_t *context)
{
    cy_en_lpcomp_status_t ret = CY_LPCOMP_BAD_PARAM;

    if ((base != NULL) && (config != NULL) && (context != NULL))
    {
        CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
        CY_ASSERT_L3(CY_LPCOMP_IS_OUT_MODE_VALID(config->outputMode));
        CY_ASSERT_L3(CY_LPCOMP_IS_HYSTERESIS_VALID(config->hysteresis));
        CY_ASSERT_L3(CY_LPCOMP_IS_POWER_VALID(config->power));
        CY_ASSERT_L3(CY_LPCOMP_IS_INTR_MODE_VALID(config->intType));

        Cy_LPComp_GlobalEnable(base);

        if (CY_LPCOMP_CHANNEL_0 == channel)
        {
            LPCOMP_CMP0_CTRL(base) = _VAL2FLD(LPCOMP_CMP0_CTRL_HYST0, (uint32_t)config->hysteresis) |
                              _VAL2FLD(LPCOMP_CMP0_CTRL_DSI_BYPASS0, (uint32_t)config->outputMode) |
                              _VAL2FLD(LPCOMP_CMP0_CTRL_DSI_LEVEL0, (uint32_t)config->outputMode >> 1u);
        }
        else
        {
            LPCOMP_CMP1_CTRL(base) = _VAL2FLD(LPCOMP_CMP1_CTRL_HYST1, (uint32_t)config->hysteresis) |
                              _VAL2FLD(LPCOMP_CMP1_CTRL_DSI_BYPASS1, (uint32_t)config->outputMode) |
                              _VAL2FLD(LPCOMP_CMP1_CTRL_DSI_LEVEL1, (uint32_t)config->outputMode >> 1u);
        }

        /* Save intType to use it in the Cy_LPComp_Enable_Ext() function */
        context->intType[(uint8_t)channel - 1u] = config->intType;

        /* Save power to use it in the Cy_LPComp_Enable_Ext() function */
        context->power[(uint8_t)channel - 1u] = config->power;

        ret = CY_LPCOMP_SUCCESS;
    }

    return (ret);
}


#if defined (CY_IP_MXLPCOMP)
/*******************************************************************************
* Function Name: Cy_LPComp_Init
****************************************************************************//**
*
* Initializes the low-power comparator and returns
* the status of the initialization.
*
* \param *base
*     The low-power comparator registers structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param *config
*     The pointer to the configuration structure for PDL.
*
* \return cy_en_lpcomp_status_t
*     *base checking result. If the pointer is NULL, returns an error.
*
*******************************************************************************/
cy_en_lpcomp_status_t Cy_LPComp_Init(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, const cy_stc_lpcomp_config_t* config)
{
    cy_en_lpcomp_status_t ret = CY_LPCOMP_BAD_PARAM;

    if ((base != NULL) && (config != NULL))
    {
        CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
        CY_ASSERT_L3(CY_LPCOMP_IS_OUT_MODE_VALID(config->outputMode));
        CY_ASSERT_L3(CY_LPCOMP_IS_HYSTERESIS_VALID(config->hysteresis));
        CY_ASSERT_L3(CY_LPCOMP_IS_POWER_VALID(config->power));
        CY_ASSERT_L3(CY_LPCOMP_IS_INTR_MODE_VALID(config->intType));

        Cy_LPComp_GlobalEnable(base);

        if (CY_LPCOMP_CHANNEL_0 == channel)
        {
            LPCOMP_CMP0_CTRL(base) = _VAL2FLD(LPCOMP_CMP0_CTRL_HYST0, (uint32_t)config->hysteresis) |
                              _VAL2FLD(LPCOMP_CMP0_CTRL_DSI_BYPASS0, (uint32_t)config->outputMode) |
                              _VAL2FLD(LPCOMP_CMP0_CTRL_DSI_LEVEL0, (uint32_t)config->outputMode >> 1u);
        }
        else
        {
            LPCOMP_CMP1_CTRL(base) = _VAL2FLD(LPCOMP_CMP1_CTRL_HYST1, (uint32_t)config->hysteresis) |
                              _VAL2FLD(LPCOMP_CMP1_CTRL_DSI_BYPASS1, (uint32_t)config->outputMode) |
                              _VAL2FLD(LPCOMP_CMP1_CTRL_DSI_LEVEL1, (uint32_t)config->outputMode >> 1u);
        }

        /* Save intType to use it in the Cy_LPComp_Enable() function */
        cy_lpcomp_context.intType[(uint8_t)channel - 1u] = config->intType;

        /* Save power to use it in the Cy_LPComp_Enable() function */
        cy_lpcomp_context.power[(uint8_t)channel - 1u] = config->power;

        ret = CY_LPCOMP_SUCCESS;
    }

    return (ret);
}
#endif


/*******************************************************************************
* Function Name: Cy_LPComp_Enable_Ext
****************************************************************************//**
*
* Cy_LPComp_Enable_Ext() is an extended version of existing function Cy_LPComp_Enable().
* This implementation follows the thread-safe approach and is preferable for usage.
*
* This function enables the low-power comparator and sets
* interrupt edge-detect and drive power modes.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param *context
* The pointer to the context structure \ref cy_stc_lpcomp_context_t allocated by the user.
* The structure is used during the low-power comparator operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_Enable_Ext(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_stc_lpcomp_context_t *context)
{
    cy_en_lpcomp_pwr_t powerSpeed;

    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));

    powerSpeed = context->power[(uint8_t)channel - 1u];

    /* Set power */
    Cy_LPComp_SetPower_Ext(base, channel, powerSpeed, context);

    /* Make delay before enabling the comparator interrupt to prevent false triggering */
    if (CY_LPCOMP_MODE_ULP == powerSpeed)
    {
        Cy_SysLib_DelayUs(CY_LPCOMP_ULP_POWER_DELAY);
    }
    else if (CY_LPCOMP_MODE_LP == powerSpeed)
    {
        Cy_SysLib_DelayUs(CY_LPCOMP_LP_POWER_DELAY);
    }
    else
    {
        Cy_SysLib_DelayUs(CY_LPCOMP_NORMAL_POWER_DELAY);
    }

    /* Enable the comparator interrupt */
    Cy_LPComp_SetInterruptTriggerMode_Ext(base, channel, context->intType[(uint8_t)channel - 1u], context);
}


#if defined (CY_IP_MXLPCOMP)
/*******************************************************************************
* Function Name: Cy_LPComp_Enable
****************************************************************************//**
*
* Enables the low-power comparator and sets Interrupt mode.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_Enable(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel)
{
    cy_en_lpcomp_pwr_t powerSpeed;

    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));

    powerSpeed = cy_lpcomp_context.power[(uint8_t)channel - 1u];

    /* Set power */
    Cy_LPComp_SetPower(base, channel, powerSpeed);

    /* Make delay before enabling the comparator interrupt to prevent false triggering */
    if (CY_LPCOMP_MODE_ULP == powerSpeed)
    {
        Cy_SysLib_DelayUs(CY_LPCOMP_ULP_POWER_DELAY);
    }
    else if (CY_LPCOMP_MODE_LP == powerSpeed)
    {
        Cy_SysLib_DelayUs(CY_LPCOMP_LP_POWER_DELAY);
    }
    else
    {
        Cy_SysLib_DelayUs(CY_LPCOMP_NORMAL_POWER_DELAY);
    }

    /* Enable the comparator interrupt */
    Cy_LPComp_SetInterruptTriggerMode(base, channel, cy_lpcomp_context.intType[(uint8_t)channel - 1u]);
}
#endif


/*******************************************************************************
* Function Name: Cy_LPComp_Disable_Ext
****************************************************************************//**
*
* Cy_LPComp_Disable_Ext() is an extended version of existing function Cy_LPComp_Disable().
* This implementation follows the thread-safe approach and is preferable for usage.
*
* This function disables the low-power comparator power and sets interrupt edge-detect mode
* to the disabled state.
*
* \note This function disables the comparator interrupt to prevent a false trigger
* that may happen due to stop working of the comparator unpowered output. \n
*
* \note Disabled states for comparator interrupt and drive power are not preserved in the context.
* The actual configurations for interrupt edge-detect and drive power
* are restored from the context in: \ref Cy_LPComp_Enable_Ext().
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param *context
* The pointer to the context structure \ref cy_stc_lpcomp_context_t allocated by the user.
* The structure is used during the low-power comparator operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_Disable_Ext(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_stc_lpcomp_context_t *context)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));

    /* Disable the comparator interrupt */
    Cy_LPComp_SetInterruptTriggerMode_Ext(base, channel, CY_LPCOMP_INTR_DISABLE, context);

    /* Set power off */
    Cy_LPComp_SetPower_Ext(base, channel, CY_LPCOMP_MODE_OFF, context);
}


#if defined (CY_IP_MXLPCOMP)
/*******************************************************************************
* Function Name: Cy_LPComp_Disable
****************************************************************************//**
*
* Disables the low-power comparator power and sets Interrupt mode to the disabled state.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_Disable(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));

    /* Disable the comparator interrupt */
    Cy_LPComp_SetInterruptTriggerMode(base, channel, CY_LPCOMP_INTR_DISABLE);

    /* Set power off */
    Cy_LPComp_SetPower(base, channel, CY_LPCOMP_MODE_OFF);
}
#endif


/*******************************************************************************
* Function Name: Cy_LPComp_SetInterruptTriggerMode_Ext
****************************************************************************//**
*
* Cy_LPComp_SetInterruptTriggerMode_Ext() is an extended version of existing function
* Cy_LPComp_SetInterruptTriggerMode().
* This implementation follows the thread-safe approach and is preferable for usage.
*
* This function sets the interrupt edge-detect mode and controls the value
* provided on the output.
*
* \note The interrupt edge-detect mode is preserved in the context,
* except state CY_LPCOMP_INTR_DISABLE. \n
*
* \note  The mode of the interrupt is restored after the block is enabled and appropriate
* start-up time has elapsed:
* * 3 us is for normal power mode;
* * 6 us for LP mode;
* * 50 us for ULP mode.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param intType
*   Interrupt edge trigger selection:
*   * CY_LPCOMP_INTR_DISABLE (=0) - disabled, no interrupt will be detected;
*   * CY_LPCOMP_INTR_RISING  (=1) - the rising edge;
*   * CY_LPCOMP_INTR_FALLING (=2) - the falling edge;
*   * CY_LPCOMP_INTR_BOTH    (=3) - both rising and falling edges.
*
* \param *context
* The pointer to the context structure \ref cy_stc_lpcomp_context_t allocated by the user.
* The structure is used during the low-power comparator operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_SetInterruptTriggerMode_Ext(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_int_t intType,
                                          cy_stc_lpcomp_context_t *context)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
    CY_ASSERT_L3(CY_LPCOMP_IS_INTR_MODE_VALID(intType));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP0_CTRL(base), LPCOMP_CMP0_CTRL_INTTYPE0, (uint32_t)intType);
    }
    else
    {
        LPCOMP_CMP1_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP1_CTRL(base), LPCOMP_CMP1_CTRL_INTTYPE1, (uint32_t)intType);
    }

    /* Save interrupt type to use it in the Cy_LPComp_Enable_Ext() function */
    if (intType != CY_LPCOMP_INTR_DISABLE)
    {
        context->intType[(uint8_t)channel - 1u] = intType;
    }
}


#if defined (CY_IP_MXLPCOMP)
/*******************************************************************************
* Function Name: Cy_LPComp_SetInterruptTriggerMode
****************************************************************************//**
*
* This function sets the interrupt edge-detect mode and controls the value
* provided on the output.
* \note  Interrupts can be enabled after the block is enabled and appropriate
* start-up time has elapsed:
* * 3 us is for normal power mode;
* * 6 us for LP mode;
* * 50 us for ULP mode.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param intType
*   The interrupt edge trigger selection:
*   * CY_LPCOMP_INTR_DISABLE (=0) - disabled, no interrupt will be detected;
*   * CY_LPCOMP_INTR_RISING  (=1) - the rising edge;
*   * CY_LPCOMP_INTR_FALLING (=2) - the falling edge;
*   * CY_LPCOMP_INTR_BOTH    (=3) - both rising and falling edges.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_SetInterruptTriggerMode(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_int_t intType)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
    CY_ASSERT_L3(CY_LPCOMP_IS_INTR_MODE_VALID(intType));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP0_CTRL(base), LPCOMP_CMP0_CTRL_INTTYPE0, (uint32_t)intType);
    }
    else
    {
        LPCOMP_CMP1_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP1_CTRL(base), LPCOMP_CMP1_CTRL_INTTYPE1, (uint32_t)intType);
    }

    /* Save interrupt type to use it in the Cy_LPComp_Enable() function */
    cy_lpcomp_context.intType[(uint8_t)channel - 1u] = intType;
}
#endif


/*******************************************************************************
* Function Name: Cy_LPComp_SetPower_Ext
****************************************************************************//**
*
* Cy_LPComp_SetPower_Ext() is an extended version of existing function Cy_LPComp_SetPower().
* This implementation follows the thread-safe approach and is preferable for usage.
*
* This function sets the drive power and speeds to one of the four settings.
*
* \note The drive power mode is preserved in the context,
* except state CY_LPCOMP_MODE_OFF. \n
*
* \note  The mode of the interrupt is restored after the block is enabled and appropriate
* start-up time has elapsed:
* * 3 us for normal power mode;
* * 6 us for LP mode;
* * 50 us for ULP mode.
* Otherwise, unexpected interrupts can occur.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param power
*     Defines the component power mode:
*     * CY_LPCOMP_OFF_POWER   (=0) - off power;
*     * CY_LPCOMP_MODE_ULP    (=1) - slow/ultra low power;
*     * CY_LPCOMP_MODE_LP     (=2) - medium/low power;
*     * CY_LPCOMP_MODE_NORMAL (=3) - fast/normal power.
*
* \param *context
* The pointer to the context structure \ref cy_stc_lpcomp_context_t allocated by the user.
* The structure is used during the low-power comparator operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_SetPower_Ext(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_pwr_t power,
                           cy_stc_lpcomp_context_t *context)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
    CY_ASSERT_L3(CY_LPCOMP_IS_POWER_VALID(power));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP0_CTRL(base), LPCOMP_CMP0_CTRL_MODE0, (uint32_t)power);
    }
    else
    {
        LPCOMP_CMP1_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP1_CTRL(base), LPCOMP_CMP1_CTRL_MODE1, (uint32_t)power);
    }

    /* Save power to use it in the Cy_LPComp_Enable_Ext() function */
    if (power != CY_LPCOMP_MODE_OFF)
    {
        context->power[(uint8_t)channel - 1u] = power;
    }
}


#if defined (CY_IP_MXLPCOMP)
/*******************************************************************************
* Function Name: Cy_LPComp_SetPower
****************************************************************************//**
*
* Sets the drive power and speeds to one of the four settings.
* \note Interrupts can be enabled after the block is enabled and appropriate
* start-up time has elapsed:
* * 3 us for normal power mode;
* * 6 us for LP mode;
* * 50 us for ULP mode.
* Otherwise, unexpected interrupts can occur.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param power
*     Defines the component power mode:
*     * CY_LPCOMP_OFF_POWER   (=0) - off power;
*     * CY_LPCOMP_MODE_ULP    (=1) - slow/ultra low power;
*     * CY_LPCOMP_MODE_LP     (=2) - medium/low power;
*     * CY_LPCOMP_MODE_NORMAL (=3) - fast/normal power.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_SetPower(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_pwr_t power)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
    CY_ASSERT_L3(CY_LPCOMP_IS_POWER_VALID(power));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP0_CTRL(base), LPCOMP_CMP0_CTRL_MODE0, (uint32_t)power);
    }
    else
    {
        LPCOMP_CMP1_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP1_CTRL(base), LPCOMP_CMP1_CTRL_MODE1, (uint32_t)power);
    }
}
#endif


/*******************************************************************************
* Function Name: Cy_LPComp_SetHysteresis
****************************************************************************//**
*
* Adds the 30mV hysteresis to the comparator.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param hysteresis
*   Defines the component operation mode:
*   * CY_LPCOMP_HYST_ENABLE  (=1) - enables HYST;
*   * CY_LPCOMP_HYST_DISABLE (=0) - disables HYST.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_SetHysteresis(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_hyst_t hysteresis)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
    CY_ASSERT_L3(CY_LPCOMP_IS_HYSTERESIS_VALID(hysteresis));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP0_CTRL(base), LPCOMP_CMP0_CTRL_HYST0, (uint32_t)hysteresis);
    }
    else
    {
        LPCOMP_CMP1_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP1_CTRL(base) , LPCOMP_CMP1_CTRL_HYST1, (uint32_t)hysteresis);
    }
}


/*******************************************************************************
* Function Name: Cy_LPComp_SetInputs
****************************************************************************//**
*
* Sets the comparator input sources. The comparator inputs can be connected
* to the dedicated GPIO pins or AMUXBUSA/AMUXBUSB. Additionally, the negative
* comparator input can be connected to the local VREF.
* Even one unconnected input causes a comparator undefined output.
*
* \note Connection to AMUXBUSA/AMUXBUSB requires closing the additional
* switches, which are part of the IO system. These switches can be configured
* using the HSIOM->AMUX_SPLIT_CTL[3] register.
* For details, refer to the appropriate Technical Reference Manual (TRM).
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param inputP
*   Positive input selection:
*   * CY_LPCOMP_SW_GPIO (0x01u);
*   * CY_LPCOMP_SW_AMUXBUSA (0x02u) - Hi-Z in Hibernate mode;
*   * CY_LPCOMP_SW_AMUXBUSB (0x04u) - Hi-Z in Hibernate mode.
*
* \param inputN
*   Negative input selection:
*   * CY_LPCOMP_SW_GPIO (0x01u);
*   * CY_LPCOMP_SW_AMUXBUSA   (0x02u) - Hi-Z in Hibernate mode;
*   * CY_LPCOMP_SW_AMUXBUSB   (0x04u) - Hi-Z in Hibernate mode;
*   * CY_LPCOMP_SW_LOCAL_VREF (0x08u) - the negative input only for a crude REF.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_SetInputs(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_inputs_t inputP, cy_en_lpcomp_inputs_t inputN)
{
    uint32_t input;

    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
    CY_ASSERT_L3(CY_LPCOMP_IS_INPUT_P_VALID(inputP));
    CY_ASSERT_L3(CY_LPCOMP_IS_INPUT_N_VALID(inputN));

    switch(inputP)
    {
        case CY_LPCOMP_SW_AMUXBUSA:
        {
            input = (channel == CY_LPCOMP_CHANNEL_0) ? LPCOMP_CMP0_SW_CMP0_AP0_Msk : LPCOMP_CMP1_SW_CMP1_AP1_Msk;
            HSIOM_AMUX_SPLIT_CTL(3U) = _CLR_SET_FLD32U(HSIOM_AMUX_SPLIT_CTL(3U), CY_HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_SR, 3u);
            break;
        }
        case CY_LPCOMP_SW_AMUXBUSB:
        {
            input = (channel == CY_LPCOMP_CHANNEL_0) ? LPCOMP_CMP0_SW_CMP0_BP0_Msk : LPCOMP_CMP1_SW_CMP1_BP1_Msk;
            HSIOM_AMUX_SPLIT_CTL(3U) = _CLR_SET_FLD32U(HSIOM_AMUX_SPLIT_CTL(3U), CY_HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_SR, 3u);
            break;
        }
        default:
        {
            input = (channel == CY_LPCOMP_CHANNEL_0) ? LPCOMP_CMP0_SW_CMP0_IP0_Msk : LPCOMP_CMP1_SW_CMP1_IP1_Msk;
            break;
        }
    }

    switch(inputN)
    {
        case CY_LPCOMP_SW_AMUXBUSA:
        {
            input |= (channel == CY_LPCOMP_CHANNEL_0) ? LPCOMP_CMP0_SW_CMP0_AN0_Msk : LPCOMP_CMP1_SW_CMP1_AN1_Msk;
            HSIOM_AMUX_SPLIT_CTL(3U) = _CLR_SET_FLD32U(HSIOM_AMUX_SPLIT_CTL(3U), CY_HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_SR, 3u);
            break;
        }
        case CY_LPCOMP_SW_AMUXBUSB:
        {
            input |= (channel == CY_LPCOMP_CHANNEL_0) ? LPCOMP_CMP0_SW_CMP0_BN0_Msk : LPCOMP_CMP1_SW_CMP1_BN1_Msk;
            HSIOM_AMUX_SPLIT_CTL(3U) = _CLR_SET_FLD32U(HSIOM_AMUX_SPLIT_CTL(3U), CY_HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_SR, 3u);
            break;
        }
        case CY_LPCOMP_SW_LOCAL_VREF:
        {
            input |= (channel == CY_LPCOMP_CHANNEL_0) ? LPCOMP_CMP0_SW_CMP0_VN0_Msk : LPCOMP_CMP1_SW_CMP1_VN1_Msk;
            break;
        }
        default:
        {
            input |= (channel == CY_LPCOMP_CHANNEL_0) ? LPCOMP_CMP0_SW_CMP0_IN0_Msk : LPCOMP_CMP1_SW_CMP1_IN1_Msk;
            break;
        }
    }

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_SW_CLEAR(base) = CY_LPCOMP_CMP0_SW_POS_Msk | CY_LPCOMP_CMP0_SW_NEG_Msk;
        LPCOMP_CMP0_SW(base) = input;
    }
    else
    {
        LPCOMP_CMP1_SW_CLEAR(base) = CY_LPCOMP_CMP1_SW_POS_Msk | CY_LPCOMP_CMP1_SW_NEG_Msk;
        LPCOMP_CMP1_SW(base) = input;
    }
}


/*******************************************************************************
* Function Name: Cy_LPComp_SetOutputMode
****************************************************************************//**
*
* Sets the type of the comparator DSI output.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param outType
*   Interrupt-edge trigger selection:
*   * CY_LPCOMP_OUT_PULSE  (=0) - the DSI output with the pulse option, no bypass;
*   * CY_LPCOMP_OUT_DIRECT (=1) - Bypass mode, the direct output of the comparator;
*   * CY_LPCOMP_OUT_SYNC   (=2) - the DSI output with the level option, it is similar to
*   Bypass mode, but it is 1 cycle slower.
*   [DSI_LEVELx : DSI_BYPASSx] = [Bit11 : Bit10]
*   0 : 0 = 0x00 -> Pulse (PULSE)
*   1 : 0 = 0x02 -> Level (SYNC)
*   x : 1 = 0x01 -> Bypass (Direct).
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_SetOutputMode(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_out_t outType)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
    CY_ASSERT_L3(CY_LPCOMP_IS_OUT_MODE_VALID(outType));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP0_CTRL(base), CY_LPCOMP_CMP0_OUTPUT_CONFIG, (uint32_t)outType);
    }
    else
    {
        LPCOMP_CMP1_CTRL(base) = _CLR_SET_FLD32U(LPCOMP_CMP1_CTRL(base), CY_LPCOMP_CMP1_OUTPUT_CONFIG, (uint32_t)outType);
    }
}


/*******************************************************************************
* Function Name: Cy_LPComp_DeepSleepCallback
****************************************************************************//**
*
* This function checks the current low-power comparator power mode and disables
* the low-power comparator block, if there is no wake-up source from
* the low-power comparator in Deep-Sleep mode.
* This function stores the state of the low-power comparator "Enable", disables
* the low-power comparator block before going to low power modes and then
* recovers the low-power comparator power "after a wake-up" state using
* the stored value.
*
* \param *callbackParams
*     A \ref cy_stc_syspm_callback_params_t structure with callback
*     parameters that consists of mode, base and context fields:
*    *base - a low-power comparator register structure pointer.
*    *context - context for the call-back function.
*     mode
*     * CY_SYSPM_CHECK_READY - no action for this state.
*     * CY_SYSPM_CHECK_FAIL - no action for this state.
*     * CY_SYSPM_BEFORE_TRANSITION - checks the low-power comparator interrupt mask
*                            and power mode and then disables or enables the
*                            low-power comparator block per condition.
*                            Stores the low-power comparator state
*                            to recover the state after a wake up.
*     * CY_SYSPM_AFTER_TRANSITION - enables the low-power comparator block
*                            if it was disabled before Sleep mode.
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return
* \ref cy_en_syspm_status_t
*
*******************************************************************************/
cy_en_syspm_status_t Cy_LPComp_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t ret = CY_SYSPM_FAIL;
    LPCOMP_Type *locBase = (LPCOMP_Type *) (callbackParams->base);
    static uint32_t enabled_status;

    switch(mode)
    {
        case CY_SYSPM_CHECK_READY:
        {
            ret = CY_SYSPM_SUCCESS;
        }
        break;

        case CY_SYSPM_CHECK_FAIL:
        {
            ret = CY_SYSPM_SUCCESS;
        }
        break;

        case CY_SYSPM_BEFORE_TRANSITION:
        {
            /* Save the low-power comparator the enabled/disabled status. */
            enabled_status = _FLD2VAL(LPCOMP_CONFIG_ENABLED, LPCOMP_CONFIG(locBase));

            if (0u != enabled_status)
            {
                /* Disable the low-power comparator block when there is no wake-up source from any channel. */
                if( !(((_FLD2VAL(LPCOMP_CMP0_CTRL_MODE0, LPCOMP_CMP0_CTRL(locBase)) == (uint32_t)CY_LPCOMP_MODE_ULP) &&
                        _FLD2BOOL(LPCOMP_INTR_MASK_COMP0_MASK, LPCOMP_INTR_MASK(locBase))) ||
                      ((_FLD2VAL(LPCOMP_CMP1_CTRL_MODE1, LPCOMP_CMP1_CTRL(locBase)) == (uint32_t)CY_LPCOMP_MODE_ULP) &&
                        _FLD2BOOL(LPCOMP_INTR_MASK_COMP1_MASK, LPCOMP_INTR_MASK(locBase)))))

                {
                    /* Disable the low-power comparator block to avoid leakage. */
                    Cy_LPComp_GlobalDisable(locBase);
                }
                else
                {
                    /* Set low-power comparator the status to the not changed state. */
                    enabled_status = 0u;
                }
            }
            else
            {
                /* The low-power comparator block was already disabled and
                *  the system is allowed to go to the low power mode.
                */
            }

            ret = CY_SYSPM_SUCCESS;
        }
        break;

        case CY_SYSPM_AFTER_TRANSITION:
        {
            /* Enable the low-power comparator to operate if it was enabled
            * before entering to the low power mode.
            */
            if (0u != enabled_status)
            {
                Cy_LPComp_GlobalEnable(locBase);
            }
            else
            {
                /* The low-power comparator block was disabled before calling this API
                * with mode = CY_SYSPM_CHECK_READY.
                */
            }

            ret = CY_SYSPM_SUCCESS;
        }
        break;

        default:
            /* Unknown state */
            break;
    }

    return (ret);
}


/*******************************************************************************
* Function Name: Cy_LPComp_HibernateCallback
****************************************************************************//**
*
*  This function checks the current low-power comparator power mode and disables
* the low-power comparator block, if there is no wake-up source from
* the low-power comparator in Hibernate mode.
*
* \param *callbackParams
*     A \ref cy_stc_syspm_callback_params_t structure with callback
*     parameters that consists of mode, base and context fields:
*    *base - a low-power comparator register structure pointer.
*    *context - context for the call-back function.
*     mode
*     * CY_SYSPM_CHECK_READY - no action for this state.
*     * CY_SYSPM_CHECK_FAIL - no action for this state.
*     * CY_SYSPM_BEFORE_TRANSITION - checks the wake-up source from Hibernate mode
*                            of the low-power comparator block,
*                            and then disables or enables the low-power comparator
*                            block per condition.
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return
* \ref cy_en_syspm_status_t
*
*******************************************************************************/
cy_en_syspm_status_t Cy_LPComp_HibernateCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t ret = CY_SYSPM_FAIL;
    LPCOMP_Type *locBase = (LPCOMP_Type *) (callbackParams->base);
    static uint32_t enabled_status;

    switch(mode)
    {
        case CY_SYSPM_CHECK_READY:
        {
            ret = CY_SYSPM_SUCCESS;
        }
        break;

        case CY_SYSPM_CHECK_FAIL:
        {
            ret = CY_SYSPM_SUCCESS;
        }
        break;

        case CY_SYSPM_BEFORE_TRANSITION:
        {
            /* Save the low-power comparator the enabled/disabled status. */
            enabled_status = _FLD2VAL(LPCOMP_CONFIG_ENABLED, LPCOMP_CONFIG(locBase));

            if (0u != enabled_status)
            {
                /* Disable the low-power comparator block when there is no wake-up source from any channel. */
                if( (!(((_FLD2VAL(LPCOMP_CMP0_CTRL_MODE0, LPCOMP_CMP0_CTRL(locBase))) == (uint32_t)CY_LPCOMP_MODE_ULP) &&
                        _FLD2BOOL(CY_LPCOMP_WAKEUP_PIN0, SRSS_PWR_HIBERNATE))) ||
                      ((_FLD2VAL(LPCOMP_CMP1_CTRL_MODE1, LPCOMP_CMP1_CTRL(locBase)) == (uint32_t)CY_LPCOMP_MODE_ULP) &&
                        _FLD2BOOL(CY_LPCOMP_WAKEUP_PIN1, SRSS_PWR_HIBERNATE)))

                {
                    /* Disable the low-power comparator block to avoid leakage. */
                    Cy_LPComp_GlobalDisable(locBase);
                }
                else
                {
                    /* Set low-power comparator the status to the not changed state. */
                    enabled_status = 0u;
                }
            }
            else
            {
                /* The low-power comparator block was already disabled and
                *  the system is allowed to go to the low power mode.
                */
            }

            ret = CY_SYSPM_SUCCESS;
        }
        break;

        default:
            /* Unknown state */
            break;
    }

    return (ret);
}


#if defined (CY_IP_MXS22LPCOMP)
/*******************************************************************************
* Function Name: Cy_LPComp_GetTrim
****************************************************************************//**
*
* This function returns current trim settings for a particular channel of
* low-power comparator.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param *trim
*     The low-power comparator trim structure pointer, see \ref cy_en_lpcomp_trim_t.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_GetTrim(LPCOMP_Type const * base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_trim_t * trim)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        trim->enable =   _FLD2BOOL(LPCOMP_CMP0_OFFSET_TRIM_CMP0_EN,        LPCOMP_CMP0_OFFSET_TRIM(base));
        CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.3', 2, 'Intentional typecast of uint32_t to enum');
        trim->polarity =  _FLD2VAL(LPCOMP_CMP0_OFFSET_TRIM_CMP0_POLARITY,  LPCOMP_CMP0_OFFSET_TRIM(base));
        trim->magnitude = _FLD2VAL(LPCOMP_CMP0_OFFSET_TRIM_CMP0_MAGNITUDE, LPCOMP_CMP0_OFFSET_TRIM(base));
        CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.3');
    }
    else
    {
        trim->enable =   _FLD2BOOL(LPCOMP_CMP1_OFFSET_TRIM_CMP1_EN,        LPCOMP_CMP1_OFFSET_TRIM(base));
        CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.3', 2, 'Intentional typecast of uint32_t to enum');
        trim->polarity =  _FLD2VAL(LPCOMP_CMP1_OFFSET_TRIM_CMP1_POLARITY,  LPCOMP_CMP1_OFFSET_TRIM(base));
        trim->magnitude = _FLD2VAL(LPCOMP_CMP1_OFFSET_TRIM_CMP1_MAGNITUDE, LPCOMP_CMP1_OFFSET_TRIM(base));
        CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.3');
    }
}


/*******************************************************************************
* Function Name: Cy_LPComp_SetTrim
****************************************************************************//**
*
* This function applies trim settings to the particular channel of
* low-power comparator.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \param *trim
*     The low-power comparator trim structure pointer, see \ref cy_en_lpcomp_trim_t.
*
* \return None.
*
*******************************************************************************/
void Cy_LPComp_SetTrim(LPCOMP_Type * base, cy_en_lpcomp_channel_t channel, const cy_en_lpcomp_trim_t * trim)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));
    CY_ASSERT_L3(CY_LPCOMP_IS_TRIM_VALID(trim));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_OFFSET_TRIM(base) = _BOOL2FLD(LPCOMP_CMP0_OFFSET_TRIM_CMP0_EN,        trim->enable) |
                                         _VAL2FLD(LPCOMP_CMP0_OFFSET_TRIM_CMP0_POLARITY,  trim->polarity) |
                                         _VAL2FLD(LPCOMP_CMP0_OFFSET_TRIM_CMP0_MAGNITUDE, trim->magnitude);
    }
    else
    {
        LPCOMP_CMP1_OFFSET_TRIM(base) = _BOOL2FLD(LPCOMP_CMP1_OFFSET_TRIM_CMP1_EN,        trim->enable) |
                                         _VAL2FLD(LPCOMP_CMP1_OFFSET_TRIM_CMP1_POLARITY,  trim->polarity) |
                                         _VAL2FLD(LPCOMP_CMP1_OFFSET_TRIM_CMP1_MAGNITUDE, trim->magnitude);
    }
}
#endif

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXLPCOMP and CY_IP_MXS22LPCOMP */

/* [] END OF FILE */
