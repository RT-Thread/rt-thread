/***************************************************************************//**
* \file cy_mcwdt_b.c
* \version 1.70
*
*  Description:
*   Provides a system API for the MCWDT driver.
*
********************************************************************************
* Copyright 2016-2021 Cypress Semiconductor Corporation
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

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined(CY_DOXYGEN)

#include "cy_mcwdt.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Function Name: Cy_MCWDT_Init
****************************************************************************//**
*
* Initializes the MCWDT_B block.
*
*  \param base
*  The base pointer to a structure that describes the registers.
*
*  \param config
*  The pointer to a structure that contains component configuration data.
*
* \return cy_en_mcwdt_status_t
*     *base checking result. If the pointer is NULL, returns error.
*
*  \note
*  This API should not be called when the counters are running. Prior to calling
*  this API the counter should be disabled.
*
*******************************************************************************/
cy_en_mcwdt_status_t Cy_MCWDT_Init(MCWDT_Type *base, cy_stc_mcwdt_config_t const *config)
{
    cy_en_mcwdt_status_t ret = CY_MCWDT_BAD_PARAM;
    if ((base != NULL) && (config != NULL))
    {
        Cy_MCWDT_Unlock(base);

        Cy_MCWDT_CpuSelectForDpSlpPauseAction(base, config->coreSelect);

        Cy_MCWDT_SetLowerLimit(base, CY_MCWDT_COUNTER0, config->c0LowerLimit, 0);
        Cy_MCWDT_SetUpperLimit(base, CY_MCWDT_COUNTER0, config->c0UpperLimit, 0);
        Cy_MCWDT_SetWarnLimit(base, CY_MCWDT_COUNTER0, config->c0WarnLimit, 0);

        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0) = _VAL2FLD(MCWDT_CTR_CONFIG_LOWER_ACTION, config->c0LowerAction)   |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_UPPER_ACTION, config->c0UpperAction)       |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_WARN_ACTION, config->c0WarnAction)         |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_AUTO_SERVICE, config->c0AutoService)       |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_SLEEPDEEP_PAUSE, config->c0SleepDeepPause) |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_DEBUG_RUN, config->c0DebugRun);


        Cy_MCWDT_SetLowerLimit(base, CY_MCWDT_COUNTER1, config->c1LowerLimit, 0);
        Cy_MCWDT_SetUpperLimit(base, CY_MCWDT_COUNTER1, config->c1UpperLimit, 0);
        Cy_MCWDT_SetWarnLimit(base, CY_MCWDT_COUNTER1, config->c1WarnLimit, 0);

        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1) = _VAL2FLD(MCWDT_CTR_CONFIG_LOWER_ACTION, config->c1LowerAction)   |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_UPPER_ACTION, config->c1UpperAction)       |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_WARN_ACTION, config->c1WarnAction)         |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_AUTO_SERVICE, config->c1AutoService)       |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_SLEEPDEEP_PAUSE, config->c1SleepDeepPause) |
                                               _VAL2FLD(MCWDT_CTR_CONFIG_DEBUG_RUN, config->c1DebugRun);

        MCWDT_CTR2_CONFIG(base) = _VAL2FLD(MCWDT_CTR2_CONFIG_BITS, config->c2ToggleBit)   |
                              _VAL2FLD(MCWDT_CTR2_CONFIG_ACTION, config->c2Action)       |
                              _VAL2FLD(MCWDT_CTR2_CONFIG_SLEEPDEEP_PAUSE, config->c2SleepDeepPause)         |
                              _VAL2FLD(MCWDT_CTR2_CONFIG_DEBUG_RUN, config->c2DebugRun);

        Cy_MCWDT_Lock(base);

        ret = CY_MCWDT_SUCCESS;
    }

    return (ret);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_DeInit
****************************************************************************//**
*
*  De-initializes the MCWDT block, returns register values to their default state.
*
*  \param base
*  The base pointer to a structure that describes the registers.
*
*  \note
*  This API should not be called when the counters are running. Prior to calling
*  this API the counter should be disabled.
*
*******************************************************************************/
void Cy_MCWDT_DeInit(MCWDT_Type *base)
{
    Cy_MCWDT_Unlock(base);

    // disable all counter
    Cy_MCWDT_Disable(base, CY_MCWDT_CTR0, 0);
    Cy_MCWDT_Disable(base, CY_MCWDT_CTR1, 0);
    Cy_MCWDT_Disable(base, CY_MCWDT_CTR2, 0);

    /* De-Init counter-0 */
    while(Cy_MCWDT_GetEnabledStatus(base, CY_MCWDT_COUNTER0)  != 0x0UL)
    {
        // wait until enabled bit become 1
    }
    Cy_MCWDT_SetLowerLimit(base, CY_MCWDT_COUNTER0, 0x0U, 0);
    Cy_MCWDT_SetUpperLimit(base, CY_MCWDT_COUNTER0, 0x0U, 0);
    Cy_MCWDT_SetWarnLimit(base, CY_MCWDT_COUNTER0, 0x0U, 0);
    MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0) = 0x0UL;
    MCWDT_CTR_CNT(base, CY_MCWDT_COUNTER0) = 0x0UL;

    /* De-Init counter-1 */
    while(Cy_MCWDT_GetEnabledStatus(base, CY_MCWDT_COUNTER1)  != 0x0UL)
    {
        // wait until enabled bit become 1
    }
    Cy_MCWDT_SetLowerLimit(base, CY_MCWDT_COUNTER1, 0x0U, 0);
    Cy_MCWDT_SetUpperLimit(base, CY_MCWDT_COUNTER1, 0x0U, 0);
    Cy_MCWDT_SetWarnLimit(base, CY_MCWDT_COUNTER1, 0x0U, 0);
    MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1) = 0x0UL;
    MCWDT_CTR_CNT(base, CY_MCWDT_COUNTER1) = 0x0UL;

    /* De-Init counter-2 */
    while(Cy_MCWDT_GetEnabledStatus(base, CY_MCWDT_COUNTER2)  != 0x0UL)
    {
        // wait until enabled bit become 1
    }
    Cy_MCWDT_CpuSelectForDpSlpPauseAction(base, CY_MCWDT_PAUSED_BY_DPSLP_CM0);
    MCWDT_CTR2_CONFIG(base) = 0x0UL;
    Cy_MCWDT_ResetCounters(base, CY_MCWDT_CTR0, 0);
    Cy_MCWDT_ResetCounters(base, CY_MCWDT_CTR1, 0);
    MCWDT_INTR(base) = 0xFFFFFFFFUL;
    MCWDT_INTR_MASK(base) = 0x0UL;

    Cy_MCWDT_Lock(base);

}

/*******************************************************************************
* Function Name: Cy_MCWDT_ClearWatchdog
****************************************************************************//**
*
* Clears the MC watchdog counter, to prevent a XRES device reset or fault.
*
*  \param base
*  The base pointer to a structure that describes the registers.
*
*  \param counters
*  OR of all counters to clear watchdog. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2  macros.
*
*******************************************************************************/
void Cy_MCWDT_ClearWatchdog(MCWDT_Type *base, uint32_t counters)
{
    Cy_MCWDT_Unlock(base);
    Cy_MCWDT_ResetCounters(base, counters, 0u);
    Cy_MCWDT_Lock(base);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_CpuSelectForDpSlpPauseAction
****************************************************************************//**
*
*  Select deep sleep of which core for pausing this counter
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param core
*  The selected core. Deep sleep of the core pause this counter.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_CpuSelectForDpSlpPauseAction(MCWDT_Type *base, cy_en_mcwdt_select_core_t core)
{
    MCWDT_CPU_SELECT(base) = _CLR_SET_FLD32U(MCWDT_CPU_SELECT(base), MCWDT_CPU_SELECT_CPU_SEL, core);
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetLowerAction
****************************************************************************//**
*
*  Sets the lower limit action of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \param action
*  The action of operation for the counter. See enum typedef cy_en_mcwdt_lower_upper_action_t.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetLowerAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_lower_upper_action_t action)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0), MCWDT_CTR_CONFIG_LOWER_ACTION, action);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1), MCWDT_CTR_CONFIG_LOWER_ACTION, action);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetUpperAction
****************************************************************************//**
*
*  Sets the upper limit action of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \param action
*  The action of operation for the counter. See enum typedef cy_en_mcwdt_lower_upper_action_t.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetUpperAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_lower_upper_action_t action)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0), MCWDT_CTR_CONFIG_UPPER_ACTION, action);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1), MCWDT_CTR_CONFIG_UPPER_ACTION, action);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetUpperAction
****************************************************************************//**
*
*  Sets the warn limit action of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \param action
*  The action of operation for the counter. See enum typedef cy_en_mcwdt_warn_action_t.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetWarnAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_warn_action_t action)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0), MCWDT_CTR_CONFIG_WARN_ACTION, action);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1), MCWDT_CTR_CONFIG_WARN_ACTION, action);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetSubCounter2Action
****************************************************************************//**
*
*  Sets the counter 2 action of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param action
*  The action of operation for the counter. See enum typedef cy_en_mcwdt_cnt2_action_t.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetSubCounter2Action(MCWDT_Type *base, cy_en_mcwdt_cnt2_action_t action)
{
    MCWDT_CTR2_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CTR2_CONFIG(base), MCWDT_CTR2_CONFIG_ACTION, action);
}

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.8', 4, 'Intentional typecast to cy_en_mcwdt_lower_upper_action_t enum.');
/*******************************************************************************
* Function Name: Cy_MCWDT_GetLowerAction
****************************************************************************//**
*
*  Reports the lower limit action type of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \return
*  The current lower limit action type of the counter.
*  See enum typedef cy_en_mcwdt_lower_upper_action_t.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
cy_en_mcwdt_lower_upper_action_t Cy_MCWDT_GetLowerAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter)
{
    cy_en_mcwdt_lower_upper_action_t lowerLimitActionType = CY_MCWDT_ACTION_NONE;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        lowerLimitActionType = (cy_en_mcwdt_lower_upper_action_t)(_FLD2VAL(MCWDT_CTR_CONFIG_LOWER_ACTION, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        lowerLimitActionType = (cy_en_mcwdt_lower_upper_action_t)(_FLD2VAL(MCWDT_CTR_CONFIG_LOWER_ACTION, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return lowerLimitActionType; /* Control shouldn't reach here, fixes IAR compilation warning */
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetUpperAction
****************************************************************************//**
*
*  Reports the upper limit action type of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \return
*  The current upper limit action type of the counter.
*  See enum typedef cy_en_mcwdt_lower_upper_action_t.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
cy_en_mcwdt_lower_upper_action_t  Cy_MCWDT_GetUpperAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter)
{
    cy_en_mcwdt_lower_upper_action_t upperLimitActionType = CY_MCWDT_ACTION_NONE;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        upperLimitActionType = (cy_en_mcwdt_lower_upper_action_t)(_FLD2VAL(MCWDT_CTR_CONFIG_UPPER_ACTION, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        upperLimitActionType = (cy_en_mcwdt_lower_upper_action_t)(_FLD2VAL(MCWDT_CTR_CONFIG_UPPER_ACTION, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return upperLimitActionType; /* Control shouldn't reach here, fixes IAR compilation warning */
}
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.8');

/*******************************************************************************
* Function Name: Cy_MCWDT_GetWarnAction
****************************************************************************//**
*
*  Reports the warn limit action type of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \return
*  The current warn limit action type of the counter.
*  See enum typedef cy_en_mcwdt_warn_action_t.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
cy_en_mcwdt_warn_action_t Cy_MCWDT_GetWarnAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter)
{
    cy_en_mcwdt_warn_action_t warnAction = CY_MCWDT_WARN_ACTION_NONE;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
    {
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_mcwdt_warn_action_t enum.');
        warnAction = (cy_en_mcwdt_warn_action_t)(_FLD2VAL(MCWDT_CTR_CONFIG_WARN_ACTION, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0)));
        break;
    }
    case CY_MCWDT_COUNTER1:
    {
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_mcwdt_warn_action_t enum.');
        warnAction = (cy_en_mcwdt_warn_action_t)(_FLD2VAL(MCWDT_CTR_CONFIG_WARN_ACTION, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1)));
        break;
    }
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return warnAction; /* Control shouldn't reach here, fixes IAR compilation warning */
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetSubCounter2Action
****************************************************************************//**
*
*  Reports the counter 2 action type of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \return
*  The current counter 2 action type of the counter.
*  See enum typedef cy_en_mcwdt_cnt2_action_t.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
cy_en_mcwdt_cnt2_action_t Cy_MCWDT_GetSubCounter2Action(MCWDT_Type *base)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_mcwdt_cnt2_action_t enum.');
    return (cy_en_mcwdt_cnt2_action_t)(_FLD2VAL(MCWDT_CTR2_CONFIG_ACTION, MCWDT_CTR2_CONFIG(base)));
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetAutoService
****************************************************************************//**
*
*  Sets the Auto service option for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \note
*  The auto service option is not supported by Counter 2.
*
*  \param enable
*  Set 0 to disable; 1 to enable.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetAutoService(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint32_t enable)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0), MCWDT_CTR_CONFIG_AUTO_SERVICE, enable);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1), MCWDT_CTR_CONFIG_AUTO_SERVICE, enable);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetAutoService
****************************************************************************//**
*
*  Reports the Auto service setting for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \return
*  The Auto service status: 1 = enabled, 0 = disabled.
*
*  \note
*  The Auto service option is not supported by Counter 2.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_MCWDT_GetAutoService(MCWDT_Type const *base, cy_en_mcwdtctr_t counter)
{

    uint32_t retVal = 0UL;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        retVal = (_FLD2VAL(MCWDT_CTR_CONFIG_AUTO_SERVICE, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        retVal = (_FLD2VAL(MCWDT_CTR_CONFIG_AUTO_SERVICE, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return retVal;/* Control shouldn't reach here, fixes IAR compilation warning */
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetSleepDeepPause
****************************************************************************//**
*
*  Sets the Sleep deep pause option for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-2].
*
*  \param enable
*  Set 0 to disable; 1 to enable.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetSleepDeepPause(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint32_t enable)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0), MCWDT_CTR_CONFIG_SLEEPDEEP_PAUSE, enable);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1), MCWDT_CTR_CONFIG_SLEEPDEEP_PAUSE, enable);
        break;
    case CY_MCWDT_COUNTER2:
        MCWDT_CTR2_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CTR2_CONFIG(base), MCWDT_CTR2_CONFIG_SLEEPDEEP_PAUSE, enable);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetSleepDeepPause
****************************************************************************//**
*
*  Reports the Sleep deep pause setting for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-2].
*
*  \return
*  The Auto service status: 1 = enabled, 0 = disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_MCWDT_GetSleepDeepPause(MCWDT_Type const *base, cy_en_mcwdtctr_t counter)
{
    uint32_t retVal = 0UL;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        retVal = (_FLD2VAL(MCWDT_CTR_CONFIG_SLEEPDEEP_PAUSE, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        retVal = (_FLD2VAL(MCWDT_CTR_CONFIG_SLEEPDEEP_PAUSE, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1)));
        break;
    case CY_MCWDT_COUNTER2:
        retVal = (_FLD2VAL(MCWDT_CTR2_CONFIG_SLEEPDEEP_PAUSE, MCWDT_CTR2_CONFIG(base)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return retVal;/* Control shouldn't reach here, fixes IAR compilation warning */
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetDebugRun
****************************************************************************//**
*
*  Sets the Debug run option for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-2].
*
*  \param enable
*  Set 0 to disable; 1 to enable.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetDebugRun(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint32_t enable)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0), MCWDT_CTR_CONFIG_DEBUG_RUN, enable);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1), MCWDT_CTR_CONFIG_DEBUG_RUN, enable);
        break;
    case CY_MCWDT_COUNTER2:
        MCWDT_CTR2_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CTR2_CONFIG(base), MCWDT_CTR2_CONFIG_DEBUG_RUN, enable);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetDebugRun
****************************************************************************//**
*
*  Reports the Debug run setting for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-2].
*
*  \return
*  The Auto service status: 1 = enabled, 0 = disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_MCWDT_GetDebugRun(MCWDT_Type const *base, cy_en_mcwdtctr_t counter)
{
    uint32_t retVal = 0UL;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        retVal = (_FLD2VAL(MCWDT_CTR_CONFIG_DEBUG_RUN, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        retVal = (_FLD2VAL(MCWDT_CTR_CONFIG_DEBUG_RUN, MCWDT_CTR_CONFIG(base, CY_MCWDT_COUNTER1)));
        break;
    case CY_MCWDT_COUNTER2:
        retVal = (_FLD2VAL(MCWDT_CTR2_CONFIG_DEBUG_RUN, MCWDT_CTR2_CONFIG(base)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return retVal;/* Control shouldn't reach here, fixes IAR compilation warning */
}


/*******************************************************************************
* Function Name: Cy_MCWDT_SetLowerLimit
****************************************************************************//**
*
*  Sets the lower limit value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \param limit
*  The value to lower limit against the counter.
*  The valid range is [0-65535] when Auto service is disabled and [1-65535] when
*  Auto service enabled.
*
*  \note
*  The lower limit value is not supported by Counter 2.
*
*  \note
*  Action on lower limit is taken on the next increment after the counter value
*  equal to lower limit value.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the match affects after two lf_clk cycles pass. The recommended
*  value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. This must be taken
*  into account when changing the match values on the running counters.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetLowerLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_LOWER_LIMIT(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_LOWER_LIMIT(base, CY_MCWDT_COUNTER0), MCWDT_CTR_LOWER_LIMIT_LOWER_LIMIT, limit);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_LOWER_LIMIT(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_LOWER_LIMIT(base, CY_MCWDT_COUNTER1), MCWDT_CTR_LOWER_LIMIT_LOWER_LIMIT, limit);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
    Cy_SysLib_DelayUs(waitUs);
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetUpperLimit
****************************************************************************//**
*
*  Sets the upper limit value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \param limit
*  The value to upper limit against the counter.
*  The valid range is [0-65535] when Auto service is disabled and [1-65535] when
*  Auto service enabled.
*
*  \note
*  The upper limit value is not supported by Counter 2.
*
*  \note
*  Action on upper limit is taken on the next increment after the counter value
*  equal to upper limit value.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the match affects after two lf_clk cycles pass. The recommended
*  value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. This must be taken
*  into account when changing the match values on the running counters.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetUpperLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_UPPER_LIMIT(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_UPPER_LIMIT(base, CY_MCWDT_COUNTER0), MCWDT_CTR_UPPER_LIMIT_UPPER_LIMIT, limit);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_UPPER_LIMIT(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_UPPER_LIMIT(base, CY_MCWDT_COUNTER1), MCWDT_CTR_UPPER_LIMIT_UPPER_LIMIT, limit);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
    Cy_SysLib_DelayUs(waitUs);
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetWarnLimit
****************************************************************************//**
*
*  Sets the warn limit value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \param limit
*  The value to warn limit against the counter.
*  The valid range is [0-65535] when Auto service is disabled and [1-65535] when
*  Auto service enabled.
*
*  \note
*  The warn limit value is not supported by Counter 2.
*
*  \note
*  Action on warn limit is taken on the next increment after the counter value
*  equal to warn limit value.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the match affects after two lf_clk cycles pass. The recommended
*  value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. This must be taken
*  into account when changing the match values on the running counters.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_SetWarnLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        MCWDT_CTR_WARN_LIMIT(base, CY_MCWDT_COUNTER0) = _CLR_SET_FLD32U(MCWDT_CTR_WARN_LIMIT(base, CY_MCWDT_COUNTER0), MCWDT_CTR_WARN_LIMIT_WARN_LIMIT, limit);
        break;
    case CY_MCWDT_COUNTER1:
        MCWDT_CTR_WARN_LIMIT(base, CY_MCWDT_COUNTER1) = _CLR_SET_FLD32U(MCWDT_CTR_WARN_LIMIT(base, CY_MCWDT_COUNTER1), MCWDT_CTR_WARN_LIMIT_WARN_LIMIT, limit);
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
    Cy_SysLib_DelayUs(waitUs);
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetLowerLimit
****************************************************************************//**
*
*  Reports the lower limit comparison value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \note
*  The lower limit value is not supported by Counter 2.
*
*  \return
*  A 16-bit lower limit value.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
uint16_t Cy_MCWDT_GetLowerLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter)
{
    uint16_t retVal = 0u;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        retVal = (uint16_t)(_FLD2VAL(MCWDT_CTR_LOWER_LIMIT_LOWER_LIMIT, MCWDT_CTR_LOWER_LIMIT(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        retVal = (uint16_t)(_FLD2VAL(MCWDT_CTR_LOWER_LIMIT_LOWER_LIMIT, MCWDT_CTR_LOWER_LIMIT(base, CY_MCWDT_COUNTER1)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return retVal;/* Control shouldn't reach here, fixes IAR compilation warning */
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetUpperLimit
****************************************************************************//**
*
*  Reports the upper limit comparison value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \note
*  The upper limit value is not supported by Counter 2.
*
*  \return
*  A 16-bit upper limit value.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
uint16_t Cy_MCWDT_GetUpperLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter)
{
    uint16_t retVal = 0u;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        retVal = (uint16_t)(_FLD2VAL(MCWDT_CTR_UPPER_LIMIT_UPPER_LIMIT, MCWDT_CTR_UPPER_LIMIT(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        retVal = (uint16_t)(_FLD2VAL(MCWDT_CTR_UPPER_LIMIT_UPPER_LIMIT, MCWDT_CTR_UPPER_LIMIT(base, CY_MCWDT_COUNTER1)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return retVal;/* Control shouldn't reach here, fixes IAR compilation warning */
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetWarnLimit
****************************************************************************//**
*
*  Reports the warn limit comparison value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \note
*  The warn limit value is not supported by Counter 2.
*
*  \return
*  A 16-bit warn limit value.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
uint16_t Cy_MCWDT_GetWarnLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter)
{
    uint16_t retVal = 0u;

    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        retVal = (uint16_t)(_FLD2VAL(MCWDT_CTR_WARN_LIMIT_WARN_LIMIT, MCWDT_CTR_WARN_LIMIT(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        retVal = (uint16_t)(_FLD2VAL(MCWDT_CTR_WARN_LIMIT_WARN_LIMIT, MCWDT_CTR_WARN_LIMIT(base, CY_MCWDT_COUNTER1)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

    return retVal;/* Control shouldn't reach here, fixes IAR compilation warning */
}

/*******************************************************************************
* Function Name: Cy_MCWDT_WaitForCounterReset
****************************************************************************//**
*
*  wait completion of counter reset.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the MCWDT counter. The valid range is [0-1].
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_MCWDT_WaitForCounterReset(MCWDT_Type *base, cy_en_mcwdtctr_t counter)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
    {
        while((_FLD2VAL(MCWDT_SERVICE_CTR0_SERVICE, MCWDT_SERVICE(base))) != 0UL)
        {
        }
        break;
    }
    case CY_MCWDT_COUNTER1:
    {
        while((_FLD2VAL(MCWDT_SERVICE_CTR1_SERVICE, MCWDT_SERVICE(base))) != 0UL)
        {
        }
        break;
    }
    case CY_MCWDT_COUNTER2:
    default:
        CY_ASSERT(0u != 0u);
        break;
    }
}


#if defined(__cplusplus)
}
#endif

#endif /* (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

/* [] END OF FILE */
