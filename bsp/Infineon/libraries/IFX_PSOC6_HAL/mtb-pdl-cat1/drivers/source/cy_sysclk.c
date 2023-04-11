/***************************************************************************//**
* \file cy_sysclk.c
* \version 3.50
*
* Provides an API implementation of the sysclk driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
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

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)

#include "cy_sysclk.h"
#include "cy_syslib.h"
#include <stdlib.h>

#if defined (CY_DEVICE_SECURE)
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 17.2', 24, \
'Checked manually. All the recursive cycles are handled properly.');
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.6', 6, \
'Checked manually. Assignment of Local to global variable does not create any issue.');
#endif

cy_en_sysclk_status_t
                Cy_SysClk_PeriphSetDivider(cy_en_divider_types_t dividerType,
                                           uint32_t dividerNum, uint32_t dividerValue)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if (dividerType == CY_SYSCLK_DIV_8_BIT)
    {
        if ((dividerNum < PERI_DIV_8_NR) &&
            (dividerValue <= (PERI_DIV_8_CTL_INT8_DIV_Msk >> PERI_DIV_8_CTL_INT8_DIV_Pos)))
        {
            CY_REG32_CLR_SET(PERI_DIV_8_CTL[dividerNum], PERI_DIV_8_CTL_INT8_DIV, dividerValue);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else if (dividerType == CY_SYSCLK_DIV_16_BIT)
    {
        if ((dividerNum < PERI_DIV_16_NR) &&
            (dividerValue <= (PERI_DIV_16_CTL_INT16_DIV_Msk >> PERI_DIV_16_CTL_INT16_DIV_Pos)))
        {
            CY_REG32_CLR_SET(PERI_DIV_16_CTL[dividerNum], PERI_DIV_16_CTL_INT16_DIV, dividerValue);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else
    { /* return bad parameter */
    }
    return (retVal);
}


uint32_t Cy_SysClk_PeriphGetDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    uint32_t retVal;

    CY_ASSERT_L1(dividerType <= CY_SYSCLK_DIV_16_BIT);

    if (dividerType == CY_SYSCLK_DIV_8_BIT)
    {
        CY_ASSERT_L1(dividerNum < PERI_DIV_8_NR);
        retVal = _FLD2VAL(PERI_DIV_8_CTL_INT8_DIV, PERI_DIV_8_CTL[dividerNum]);
    }
    else
    { /* 16-bit divider */
        CY_ASSERT_L1(dividerNum < PERI_DIV_16_NR);
        retVal = _FLD2VAL(PERI_DIV_16_CTL_INT16_DIV, PERI_DIV_16_CTL[dividerNum]);
    }
    return (retVal);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphSetFracDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                               uint32_t dividerIntValue, uint32_t dividerFracValue)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if (dividerType == CY_SYSCLK_DIV_16_5_BIT)
    {
        if ((dividerNum < PERI_DIV_16_5_NR) &&
            (dividerIntValue <= (PERI_DIV_16_5_CTL_INT16_DIV_Msk >> PERI_DIV_16_5_CTL_INT16_DIV_Pos)) &&
            (dividerFracValue <= (PERI_DIV_16_5_CTL_FRAC5_DIV_Msk >> PERI_DIV_16_5_CTL_FRAC5_DIV_Pos)))
        {
            CY_REG32_CLR_SET(PERI_DIV_16_5_CTL[dividerNum], PERI_DIV_16_5_CTL_INT16_DIV, dividerIntValue);
            CY_REG32_CLR_SET(PERI_DIV_16_5_CTL[dividerNum], PERI_DIV_16_5_CTL_FRAC5_DIV, dividerFracValue);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else if (dividerType == CY_SYSCLK_DIV_24_5_BIT)
    {
        if ((dividerNum < PERI_DIV_24_5_NR) &&
            (dividerIntValue <= (PERI_DIV_24_5_CTL_INT24_DIV_Msk >> PERI_DIV_24_5_CTL_INT24_DIV_Pos)) &&
            (dividerFracValue <= (PERI_DIV_24_5_CTL_FRAC5_DIV_Msk >> PERI_DIV_24_5_CTL_FRAC5_DIV_Pos)))
        {
            CY_REG32_CLR_SET(PERI_DIV_24_5_CTL[dividerNum], PERI_DIV_24_5_CTL_INT24_DIV, dividerIntValue);
            CY_REG32_CLR_SET(PERI_DIV_24_5_CTL[dividerNum], PERI_DIV_24_5_CTL_FRAC5_DIV, dividerFracValue);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else
    { /* return bad parameter */
    }
    return (retVal);
}


void Cy_SysClk_PeriphGetFracDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                    uint32_t *dividerIntValue, uint32_t *dividerFracValue)
{
    CY_ASSERT_L1(((dividerType == CY_SYSCLK_DIV_16_5_BIT) || (dividerType == CY_SYSCLK_DIV_24_5_BIT)) && \
                 (dividerIntValue != NULL) && (dividerFracValue != NULL));

    if (dividerType == CY_SYSCLK_DIV_16_5_BIT)
    {
        CY_ASSERT_L1(dividerNum < PERI_DIV_16_5_NR);
        *dividerIntValue  = _FLD2VAL(PERI_DIV_16_5_CTL_INT16_DIV, PERI_DIV_16_5_CTL[dividerNum]);
        *dividerFracValue = _FLD2VAL(PERI_DIV_16_5_CTL_FRAC5_DIV, PERI_DIV_16_5_CTL[dividerNum]);
    }
    else
    { /* 24.5-bit divider */
        CY_ASSERT_L1(dividerNum < PERI_DIV_24_5_NR);
        *dividerIntValue  = _FLD2VAL(PERI_DIV_24_5_CTL_INT24_DIV, PERI_DIV_24_5_CTL[dividerNum]);
        *dividerFracValue = _FLD2VAL(PERI_DIV_24_5_CTL_FRAC5_DIV, PERI_DIV_24_5_CTL[dividerNum]);
    }
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphAssignDivider(en_clk_dst_t ipBlock,
                                              cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if ((CY_PERI_CLOCK_NR > (uint32_t)ipBlock) && (CY_SYSCLK_DIV_24_5_BIT >= dividerType))
    {
        if (((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < PERI_DIV_8_NR))    ||
            ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < PERI_DIV_16_NR))   ||
            ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < PERI_DIV_16_5_NR)) ||
            ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < PERI_DIV_24_5_NR)))
        {
            PERI_CLOCK_CTL[ipBlock] = _VAL2FLD(CY_PERI_CLOCK_CTL_TYPE_SEL, dividerType) |
                                      _VAL2FLD(CY_PERI_CLOCK_CTL_DIV_SEL, dividerNum);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    return (retVal);
}


uint32_t Cy_SysClk_PeriphGetAssignedDivider(en_clk_dst_t ipBlock)
{
    CY_ASSERT_L1(CY_PERI_CLOCK_NR > (uint32_t)ipBlock);
    return (PERI_CLOCK_CTL[ipBlock] & (CY_PERI_CLOCK_CTL_DIV_SEL_Msk | CY_PERI_CLOCK_CTL_TYPE_SEL_Msk));
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphEnableDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if (dividerType <= CY_SYSCLK_DIV_24_5_BIT)
    {
        if (((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < PERI_DIV_8_NR))    ||
            ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < PERI_DIV_16_NR))   ||
            ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < PERI_DIV_16_5_NR)) ||
            ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < PERI_DIV_24_5_NR)))
        {
            /* specify the divider, make the reference = clk_peri, and enable the divider */
            PERI_DIV_CMD = PERI_DIV_CMD_ENABLE_Msk                         |
                           CY_PERI_DIV_CMD_PA_TYPE_SEL_Msk                 |
                           CY_PERI_DIV_CMD_PA_DIV_SEL_Msk                  |
                           _VAL2FLD(CY_PERI_DIV_CMD_TYPE_SEL, dividerType) |
                           _VAL2FLD(CY_PERI_DIV_CMD_DIV_SEL,  dividerNum);
            (void)PERI_DIV_CMD; /* dummy read to handle buffered writes */
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    return (retVal);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphDisableDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if (dividerType <= CY_SYSCLK_DIV_24_5_BIT)
    {
        if (((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < PERI_DIV_8_NR))    ||
            ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < PERI_DIV_16_NR))   ||
            ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < PERI_DIV_16_5_NR)) ||
            ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < PERI_DIV_24_5_NR)))
        {
            /* specify the divider and disable it */
            PERI_DIV_CMD = PERI_DIV_CMD_DISABLE_Msk          |
             _VAL2FLD(CY_PERI_DIV_CMD_TYPE_SEL, dividerType) |
             _VAL2FLD(CY_PERI_DIV_CMD_DIV_SEL,  dividerNum);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    return (retVal);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphEnablePhaseAlignDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                        cy_en_divider_types_t dividerTypePA, uint32_t dividerNumPA)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if (dividerTypePA <= CY_SYSCLK_DIV_24_5_BIT)
    {
        if (((dividerTypePA == CY_SYSCLK_DIV_8_BIT)    && (dividerNumPA < PERI_DIV_8_NR))    ||
            ((dividerTypePA == CY_SYSCLK_DIV_16_BIT)   && (dividerNumPA < PERI_DIV_16_NR))   ||
            ((dividerTypePA == CY_SYSCLK_DIV_16_5_BIT) && (dividerNumPA < PERI_DIV_16_5_NR)) ||
            ((dividerTypePA == CY_SYSCLK_DIV_24_5_BIT) && ((dividerNumPA < PERI_DIV_24_5_NR) || (dividerNumPA == 63u))))
        {
            /* First, disable the divider that is to be phase-aligned.
               The other two parameters are checked in that function;
               if they're not valid, the divider is not disabled. */
            retVal = Cy_SysClk_PeriphDisableDivider(dividerType, dividerNum);
            if (retVal == CY_SYSCLK_SUCCESS)
            {
                /* Then, specify the reference divider, and the divider, and enable the divider */
                PERI_DIV_CMD = PERI_DIV_CMD_ENABLE_Msk             |
                 _VAL2FLD(CY_PERI_DIV_CMD_PA_TYPE_SEL, dividerTypePA) |
                 _VAL2FLD(CY_PERI_DIV_CMD_PA_DIV_SEL,  dividerNumPA)  |
                 _VAL2FLD(CY_PERI_DIV_CMD_TYPE_SEL, dividerType)   |
                 _VAL2FLD(CY_PERI_DIV_CMD_DIV_SEL,  dividerNum);
            }
        }
    }
    return (retVal);
}


bool Cy_SysClk_PeriphGetDividerEnabled(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    bool retVal = false;

    CY_ASSERT_L1(((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < PERI_DIV_8_NR))    || \
                 ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < PERI_DIV_16_NR))   || \
                 ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < PERI_DIV_16_5_NR)) || \
                 ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < PERI_DIV_24_5_NR)));

    switch(dividerType)
    {
        case CY_SYSCLK_DIV_8_BIT:
            retVal = _FLD2BOOL(PERI_DIV_8_CTL_EN, PERI_DIV_8_CTL[dividerNum]);
            break;
        case CY_SYSCLK_DIV_16_BIT:
            retVal = _FLD2BOOL(PERI_DIV_16_CTL_EN, PERI_DIV_16_CTL[dividerNum]);
            break;
        case CY_SYSCLK_DIV_16_5_BIT:
            retVal = _FLD2BOOL(PERI_DIV_16_5_CTL_EN, PERI_DIV_16_5_CTL[dividerNum]);
            break;
        case CY_SYSCLK_DIV_24_5_BIT:
            retVal = _FLD2BOOL(PERI_DIV_24_5_CTL_EN, PERI_DIV_24_5_CTL[dividerNum]);
            break;
        default:
            /* Unknown Divider */
            break;
    }
    return (retVal);
}


/* ========================================================================== */
/* =========================    clk_slow SECTION    ========================= */
/* ========================================================================== */


uint32_t Cy_SysClk_ClkSlowGetFrequency(void)
{
    uint32_t locFreq = Cy_SysClk_ClkPeriGetFrequency(); /* Get Peri frequency */
    uint32_t locDiv = 1UL + (uint32_t)Cy_SysClk_ClkSlowGetDivider(); /* peri prescaler (1-256) */

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(locFreq, locDiv));
}


void Cy_SysClk_ClkSlowSetDivider(uint8_t divider)
{
#if defined (CY_DEVICE_SECURE)
    CY_PRA_FUNCTION_CALL_VOID_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_SLOW_SET_DIVIDER, divider);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_REG32_CLR_SET(CPUSS_CM0_CLOCK_CTL, CPUSS_CM0_CLOCK_CTL_SLOW_INT_DIV, divider);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


uint8_t Cy_SysClk_ClkSlowGetDivider(void)
{
    return ((uint8_t)_FLD2VAL(CPUSS_CM0_CLOCK_CTL_SLOW_INT_DIV, CPUSS_CM0_CLOCK_CTL));
}


void Cy_SysClk_ClkPumpSetSource(cy_en_clkpump_in_sources_t source)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PUMP_SET_SOURCE, source);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_ASSERT_L3(source <= CY_SYSCLK_PUMP_IN_CLKPATH15);
    CY_REG32_CLR_SET(SRSS_CLK_SELECT, SRSS_CLK_SELECT_PUMP_SEL, source);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


cy_en_clkpump_in_sources_t Cy_SysClk_ClkPumpGetSource(void)
{
    return ((cy_en_clkpump_in_sources_t)((uint32_t)_FLD2VAL(SRSS_CLK_SELECT_PUMP_SEL, SRSS_CLK_SELECT)));
}


void Cy_SysClk_ClkPumpSetDivider(cy_en_clkpump_divide_t divider)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PUMP_SET_DIVIDER, divider);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_ASSERT_L3(CY_SYSCLK_FLL_IS_DIVIDER_VALID(divider));
    CY_REG32_CLR_SET(SRSS_CLK_SELECT, SRSS_CLK_SELECT_PUMP_DIV, divider);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


cy_en_clkpump_divide_t Cy_SysClk_ClkPumpGetDivider(void)
{
    return ((cy_en_clkpump_divide_t)((uint32_t)_FLD2VAL(SRSS_CLK_SELECT_PUMP_DIV, SRSS_CLK_SELECT)));
}


void Cy_SysClk_ClkPumpEnable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PUMP_ENABLE, 1UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    SRSS_CLK_SELECT |= SRSS_CLK_SELECT_PUMP_ENABLE_Msk;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


bool Cy_SysClk_ClkPumpIsEnabled(void)
{
    return (_FLD2BOOL(SRSS_CLK_SELECT_PUMP_ENABLE, SRSS_CLK_SELECT));
}


void Cy_SysClk_ClkPumpDisable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PUMP_DISABLE, 0UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    SRSS_CLK_SELECT &= ~SRSS_CLK_SELECT_PUMP_ENABLE_Msk;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


uint32_t Cy_SysClk_ClkPumpGetFrequency(void)
{
    /* Divide the input frequency down and return the result */
    return (Cy_SysClk_ClkPumpIsEnabled() ?
            (Cy_SysClk_ClkPathGetFrequency((uint32_t)Cy_SysClk_ClkPumpGetSource()) /
             (1UL << (uint32_t)Cy_SysClk_ClkPumpGetDivider())) : 0UL);
}


void Cy_SysClk_ClkBakSetSource(cy_en_clkbak_in_sources_t source)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_BAK_SET_SOURCE, source);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_ASSERT_L3(source <= CY_SYSCLK_BAK_IN_CLKLF);
    CY_REG32_CLR_SET(BACKUP_CTL, BACKUP_CTL_CLK_SEL, source);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


cy_en_clkbak_in_sources_t Cy_SysClk_ClkBakGetSource(void)
{
    return ((cy_en_clkbak_in_sources_t)((uint32_t)_FLD2VAL(BACKUP_CTL_CLK_SEL, BACKUP_CTL)));
}


void Cy_SysClk_ClkTimerSetSource(cy_en_clktimer_in_sources_t source)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_TIMER_SET_SOURCE, source);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_ASSERT_L3(source <= CY_SYSCLK_CLKTIMER_IN_HF0_DIV8);
    /* set both fields TIMER_SEL and TIMER_HF0_DIV with the same input value */
    CY_REG32_CLR_SET(SRSS_CLK_TIMER_CTL, CY_SRSS_CLK_TIMER_CTL_TIMER, source);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


cy_en_clktimer_in_sources_t Cy_SysClk_ClkTimerGetSource(void)
{
    /* return both fields TIMER_SEL and TIMER_HF0_DIV as a single combined value */
    return ((cy_en_clktimer_in_sources_t)((uint32_t)(SRSS_CLK_TIMER_CTL & CY_SRSS_CLK_TIMER_CTL_TIMER_Msk)));
}


void Cy_SysClk_ClkTimerSetDivider(uint8_t divider)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_TIMER_SET_DIVIDER, divider);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_REG32_CLR_SET(SRSS_CLK_TIMER_CTL, SRSS_CLK_TIMER_CTL_TIMER_DIV, divider);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


uint8_t Cy_SysClk_ClkTimerGetDivider(void)
{
    return ((uint8_t)_FLD2VAL(SRSS_CLK_TIMER_CTL_TIMER_DIV, SRSS_CLK_TIMER_CTL));
}


void Cy_SysClk_ClkTimerEnable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_TIMER_ENABLE, 1UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    SRSS_CLK_TIMER_CTL |= SRSS_CLK_TIMER_CTL_ENABLE_Msk;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


bool Cy_SysClk_ClkTimerIsEnabled(void)
{
    return (_FLD2BOOL(SRSS_CLK_TIMER_CTL_ENABLE, SRSS_CLK_TIMER_CTL));
}


void Cy_SysClk_ClkTimerDisable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_TIMER_DISABLE, 0UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    SRSS_CLK_TIMER_CTL &= ~SRSS_CLK_TIMER_CTL_ENABLE_Msk;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


void Cy_SysClk_ClkLfSetSource(cy_en_clklf_in_sources_t source)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_LF_SET_SOURCE, source);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_ASSERT_L3(source <= CY_SYSCLK_CLKLF_IN_PILO);
    CY_REG32_CLR_SET(SRSS_CLK_SELECT, SRSS_CLK_SELECT_LFCLK_SEL, source);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


cy_en_clklf_in_sources_t Cy_SysClk_ClkLfGetSource(void)
{
    return ((cy_en_clklf_in_sources_t)(((uint32_t)_FLD2VAL(SRSS_CLK_SELECT_LFCLK_SEL, SRSS_CLK_SELECT))));
}


uint32_t Cy_SysClk_ClkPeriGetFrequency(void)
{
    uint32_t locFreq = Cy_SysClk_ClkHfGetFrequency(0UL); /* Get root frequency */
    uint32_t locDiv = 1UL + (uint32_t)Cy_SysClk_ClkPeriGetDivider(); /* peri prescaler (1-256) */

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(locFreq, locDiv));
}


void Cy_SysClk_ClkPeriSetDivider(uint8_t divider)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PERI_SET_DIVIDER, divider);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_REG32_CLR_SET(CPUSS_CM0_CLOCK_CTL, CPUSS_CM0_CLOCK_CTL_PERI_INT_DIV, divider);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


uint8_t Cy_SysClk_ClkPeriGetDivider(void)
{
    return ((uint8_t)_FLD2VAL(CPUSS_CM0_CLOCK_CTL_PERI_INT_DIV, CPUSS_CM0_CLOCK_CTL));
}


/* ========================================================================== */
/* =========================    clk_fast SECTION    ========================= */
/* ========================================================================== */


uint32_t Cy_SysClk_ClkFastGetFrequency(void)
{
    uint32_t locFreq = Cy_SysClk_ClkHfGetFrequency(0UL); /* Get root frequency */
    uint32_t locDiv = 1UL + (uint32_t)Cy_SysClk_ClkFastGetDivider(); /* fast prescaler (1-256) */

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(locFreq, locDiv));
}


void Cy_SysClk_ClkFastSetDivider(uint8_t divider)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_FAST_SET_DIVIDER, divider);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_REG32_CLR_SET(CPUSS_CM4_CLOCK_CTL, CPUSS_CM4_CLOCK_CTL_FAST_INT_DIV, divider);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


uint8_t Cy_SysClk_ClkFastGetDivider(void)
{
    return ((uint8_t)_FLD2VAL(CPUSS_CM4_CLOCK_CTL_FAST_INT_DIV, CPUSS_CM4_CLOCK_CTL));
}


cy_en_sysclk_status_t Cy_SysClk_ClkHfEnable(uint32_t clkHf)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if (clkHf < CY_SRSS_NUM_HFROOT)
    {
#if defined (CY_DEVICE_SECURE)
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_HF_ENABLE, clkHf);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
        SRSS_CLK_ROOT_SELECT[clkHf] |= SRSS_CLK_ROOT_SELECT_ENABLE_Msk;
        retVal = CY_SYSCLK_SUCCESS;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    }
    return (retVal);
}


bool Cy_SysClk_ClkHfIsEnabled(uint32_t clkHf)
{
    bool retVal = false;
    if (clkHf < CY_SRSS_NUM_HFROOT)
    {
        retVal = _FLD2BOOL(SRSS_CLK_ROOT_SELECT_ENABLE, SRSS_CLK_ROOT_SELECT[clkHf]);
    }
    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_ClkHfDisable(uint32_t clkHf)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if ((0UL < clkHf) /* prevent CLK_HF0 disabling */
           && (clkHf < CY_SRSS_NUM_HFROOT))
    {
#if defined (CY_DEVICE_SECURE)
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_HF_DISABLE, clkHf);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
        SRSS_CLK_ROOT_SELECT[clkHf] &= ~SRSS_CLK_ROOT_SELECT_ENABLE_Msk;
        retVal = CY_SYSCLK_SUCCESS;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    }
    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_ClkHfSetSource(uint32_t clkHf, cy_en_clkhf_in_sources_t source)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if ((clkHf < CY_SRSS_NUM_HFROOT) && (source <= CY_SYSCLK_CLKHF_IN_CLKPATH15))
    {
#if defined (CY_DEVICE_SECURE)
        cy_stc_pra_clkhfsetsource_t set_source;
        set_source.clkHf = clkHf;
        set_source.source = source;
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_HF_SET_SOURCE, &set_source);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
        CY_REG32_CLR_SET(SRSS_CLK_ROOT_SELECT[clkHf], SRSS_CLK_ROOT_SELECT_ROOT_MUX, source);
        retVal = CY_SYSCLK_SUCCESS;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    }
    return (retVal);
}


cy_en_clkhf_in_sources_t Cy_SysClk_ClkHfGetSource(uint32_t clkHf)
{
    CY_ASSERT_L1(clkHf < CY_SRSS_NUM_HFROOT);
    return ((cy_en_clkhf_in_sources_t)((uint32_t)(_FLD2VAL(SRSS_CLK_ROOT_SELECT_ROOT_MUX, SRSS_CLK_ROOT_SELECT[clkHf]))));
}


cy_en_sysclk_status_t Cy_SysClk_ClkHfSetDivider(uint32_t clkHf, cy_en_clkhf_dividers_t divider)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if ((clkHf < CY_SRSS_NUM_HFROOT) && (divider <= CY_SYSCLK_CLKHF_DIVIDE_BY_8))
    {
#if defined (CY_DEVICE_SECURE)
        cy_stc_pra_clkhfsetdivider_t set_divider;
        set_divider.clkHf = clkHf;
        set_divider.divider = divider;
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_HF_SET_DIVIDER, &set_divider);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
        CY_REG32_CLR_SET(SRSS_CLK_ROOT_SELECT[clkHf], SRSS_CLK_ROOT_SELECT_ROOT_DIV, divider);
        retVal = CY_SYSCLK_SUCCESS;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    }
    return (retVal);
}


cy_en_clkhf_dividers_t Cy_SysClk_ClkHfGetDivider(uint32_t clkHf)
{
    CY_ASSERT_L1(clkHf < CY_SRSS_NUM_HFROOT);
    return ((cy_en_clkhf_dividers_t)(((uint32_t)_FLD2VAL(SRSS_CLK_ROOT_SELECT_ROOT_DIV, SRSS_CLK_ROOT_SELECT[clkHf]))));
}


/* ========================================================================== */
/* ============================    MF SECTION    ============================ */
/* ========================================================================== */


void Cy_SysClk_MfoEnable(bool deepSleepEnable)
{
    if (CY_SRSS_MFO_PRESENT)
    {
    #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE)
        CY_PRA_REG32_SET(CY_PRA_INDX_SRSS_CLK_MFO_CONFIG, (SRSS_CLK_MFO_CONFIG_ENABLE_Msk | (deepSleepEnable ? SRSS_CLK_MFO_CONFIG_DPSLP_ENABLE_Msk : 0UL)));
    #else
        SRSS_CLK_MFO_CONFIG = SRSS_CLK_MFO_CONFIG_ENABLE_Msk | (deepSleepEnable ? SRSS_CLK_MFO_CONFIG_DPSLP_ENABLE_Msk : 0UL);
    #endif /* CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE) */
    }
}


bool Cy_SysClk_MfoIsEnabled(void)
{
    return (CY_SRSS_MFO_PRESENT && (0UL != (SRSS_CLK_MFO_CONFIG & SRSS_CLK_MFO_CONFIG_ENABLE_Msk)));
}


void Cy_SysClk_MfoDisable(void)
{
    if (CY_SRSS_MFO_PRESENT)
    {
    #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE)
        CY_PRA_REG32_SET(CY_PRA_INDX_SRSS_CLK_MFO_CONFIG, 0UL);
    #else
        SRSS_CLK_MFO_CONFIG = 0UL;
    #endif /* CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE) */
    }
}


void Cy_SysClk_ClkMfEnable(void)
{
    if (CY_SRSS_MFO_PRESENT)
    {
    #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE)
        CY_PRA_REG32_CLR_SET(CY_PRA_INDX_SRSS_CLK_MF_SELECT, SRSS_CLK_MF_SELECT_ENABLE, 1U);
    #else
        SRSS_CLK_MF_SELECT |= SRSS_CLK_MF_SELECT_ENABLE_Msk;
    #endif /* CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE) */
    }
}


bool Cy_SysClk_ClkMfIsEnabled(void)
{
    return ((CY_SRSS_MFO_PRESENT) && (0UL != (SRSS_CLK_MF_SELECT & SRSS_CLK_MF_SELECT_ENABLE_Msk)));
}


void Cy_SysClk_ClkMfDisable(void)
{
    if (CY_SRSS_MFO_PRESENT)
    {
    #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE)
        CY_PRA_REG32_CLR_SET(CY_PRA_INDX_SRSS_CLK_MF_SELECT, SRSS_CLK_MF_SELECT_ENABLE, 0U);
    #else
        SRSS_CLK_MF_SELECT &= ~SRSS_CLK_MF_SELECT_ENABLE_Msk;
    #endif /* CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE) */
    }
}


void Cy_SysClk_ClkMfSetDivider(uint32_t divider)
{
    if ((CY_SRSS_MFO_PRESENT) && CY_SYSCLK_IS_MF_DIVIDER_VALID(divider))
    {
        if (!Cy_SysClk_ClkMfIsEnabled())
        {
        #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE)
            CY_PRA_REG32_CLR_SET(CY_PRA_INDX_SRSS_CLK_MF_SELECT, SRSS_CLK_MF_SELECT_MFCLK_DIV, divider - 1UL);
        #else
            CY_REG32_CLR_SET(SRSS_CLK_MF_SELECT, SRSS_CLK_MF_SELECT_MFCLK_DIV, divider - 1UL);
        #endif /* CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE) */
        }
    }
}


uint32_t Cy_SysClk_ClkMfGetDivider(void)
{
    return ((CY_SRSS_MFO_PRESENT) ? (1UL + _FLD2VAL(SRSS_CLK_MF_SELECT_MFCLK_DIV, SRSS_CLK_MF_SELECT)) : 1UL);
}


uint32_t Cy_SysClk_ClkMfGetFrequency(void)
{
    uint32_t locFreq = (Cy_SysClk_MfoIsEnabled()) ? CY_SYSCLK_MFO_FREQ : 0UL; /* Get root frequency */
    uint32_t locDiv = Cy_SysClk_ClkMfGetDivider(); /* clkMf prescaler (1-256) */

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(locFreq, locDiv));
}


cy_en_sysclk_status_t Cy_SysClk_WcoEnable(uint32_t timeoutus)
{
    cy_en_sysclk_status_t retVal;
#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_WCO_ENABLE, timeoutus);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    retVal = CY_SYSCLK_TIMEOUT;

    /* first set the WCO enable bit */
    BACKUP_CTL |= BACKUP_CTL_WCO_EN_Msk;

    /* now do the timeout wait for STATUS, bit WCO_OK */
    for (; (Cy_SysClk_WcoOkay() == false) && (0UL != timeoutus); timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    if (0UL != timeoutus)
    {
        retVal = CY_SYSCLK_SUCCESS;
    }
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    return (retVal);
}


bool Cy_SysClk_WcoOkay(void)
{
    return (_FLD2BOOL(BACKUP_STATUS_WCO_OK, BACKUP_STATUS));
}


void Cy_SysClk_WcoDisable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_WCO_DISABLE, 0UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    BACKUP_CTL &= (uint32_t)~BACKUP_CTL_WCO_EN_Msk;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


void Cy_SysClk_WcoBypass(cy_en_wco_bypass_modes_t bypass)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_WCO_BYPASS, bypass);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_REG32_CLR_SET(BACKUP_CTL, BACKUP_CTL_WCO_BYPASS, bypass);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


/* ========================================================================== */
/* ===========================    PILO SECTION    =========================== */
/* ========================================================================== */


void Cy_SysClk_PiloEnable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PILO_ENABLE, 1UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    SRSS_CLK_PILO_CONFIG |= SRSS_CLK_PILO_CONFIG_PILO_EN_Msk; /* 1 = enable */
    Cy_SysLib_Delay(1U/*msec*/);
    /* release the reset and enable clock output */
    SRSS_CLK_PILO_CONFIG |= SRSS_CLK_PILO_CONFIG_PILO_RESET_N_Msk |
                            SRSS_CLK_PILO_CONFIG_PILO_CLK_EN_Msk;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


bool Cy_SysClk_PiloIsEnabled(void)
{
    return (_FLD2BOOL(SRSS_CLK_PILO_CONFIG_PILO_CLK_EN, SRSS_CLK_PILO_CONFIG));
}


void Cy_SysClk_PiloDisable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PILO_DISABLE, 0UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    /* Clear PILO_EN, PILO_RESET_N, and PILO_CLK_EN bitfields. This disables the
       PILO and holds the PILO in a reset state. */
    SRSS_CLK_PILO_CONFIG &= (uint32_t)~(SRSS_CLK_PILO_CONFIG_PILO_EN_Msk      |
                                        SRSS_CLK_PILO_CONFIG_PILO_RESET_N_Msk |
                                        SRSS_CLK_PILO_CONFIG_PILO_CLK_EN_Msk);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


void Cy_SysClk_PiloSetTrim(uint32_t trimVal)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    CY_PRA_FUNCTION_CALL_VOID_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_CLK_FUNC_SET_PILO_TRIM, trimVal);
#else
    CY_REG32_CLR_SET(SRSS_CLK_PILO_CONFIG, SRSS_CLK_PILO_CONFIG_PILO_FFREQ, trimVal);
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
}


uint32_t Cy_SysClk_PiloGetTrim(void)
{
    return (_FLD2VAL(SRSS_CLK_PILO_CONFIG_PILO_FFREQ, SRSS_CLK_PILO_CONFIG));
}


/* ========================================================================== */
/* ==========================    ALTHF SECTION    =========================== */
/* ========================================================================== */


uint32_t Cy_SysClk_AltHfGetFrequency(void)
{
    #if defined(CY_IP_MXBLESS)
        return (cy_BleEcoClockFreqHz);
    #else /* CY_IP_MXBLESS */
        return (0UL);
    #endif /* CY_IP_MXBLESS */
}


/* ========================================================================== */
/* ==========================    ALTLF SECTION    =========================== */
/* ========================================================================== */


uint32_t Cy_SysClk_AltLfGetFrequency(void)
{
    return (0UL);
}


bool Cy_SysClk_AltLfIsEnabled(void)
{
    return (false);
}


/* ========================================================================== */
/* ===========================    ILO SECTION    ============================ */
/* ========================================================================== */


void Cy_SysClk_IloEnable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_ILO_ENABLE, 1UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    SRSS_CLK_ILO_CONFIG |= SRSS_CLK_ILO_CONFIG_ENABLE_Msk;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


bool Cy_SysClk_IloIsEnabled(void)
{
    return (_FLD2BOOL(SRSS_CLK_ILO_CONFIG_ENABLE, SRSS_CLK_ILO_CONFIG));
}


cy_en_sysclk_status_t Cy_SysClk_IloDisable(void)
{
    cy_en_sysclk_status_t retVal;
#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_ILO_DISABLE, 0UL);

#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    retVal = CY_SYSCLK_INVALID_STATE;
    if (!_FLD2BOOL(SRSS_WDT_CTL_WDT_EN, SRSS_WDT_CTL)) /* if disabled */
    {
        SRSS_CLK_ILO_CONFIG &= ~SRSS_CLK_ILO_CONFIG_ENABLE_Msk;
        retVal = CY_SYSCLK_SUCCESS;
    }
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    return (retVal);
}


void Cy_SysClk_IloHibernateOn(bool on)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_ILO_HIBERNATE_ON, on);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_REG32_CLR_SET(SRSS_CLK_ILO_CONFIG, SRSS_CLK_ILO_CONFIG_ILO_BACKUP, ((on) ? 1UL : 0UL));
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


/* ========================================================================== */
/* =========================    EXTCLK SECTION    =========================== */
/* ========================================================================== */

#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    uint32_t cySysClkExtFreq = 0UL;
#else
    static uint32_t cySysClkExtFreq = 0UL;
#endif

#define CY_SYSCLK_EXTCLK_MAX_FREQ (100000000UL) /* 100 MHz */
/** \endcond */

void Cy_SysClk_ExtClkSetFrequency(uint32_t freq)
{
    if (freq <= CY_SYSCLK_EXTCLK_MAX_FREQ)
    {
#if defined (CY_DEVICE_SECURE)
        CY_PRA_FUNCTION_CALL_VOID_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_EXT_CLK_SET_FREQUENCY, freq);
#endif
        cySysClkExtFreq = freq;
    }

}


uint32_t Cy_SysClk_ExtClkGetFrequency(void)
{
    return (cySysClkExtFreq);
}


/* ========================================================================== */
/* ===========================    ECO SECTION    ============================ */
/* ========================================================================== */
/** \cond INTERNAL */
#define CY_SYSCLK_TRIM_ECO_Pos  (SRSS_CLK_TRIM_ECO_CTL_WDTRIM_Pos)
#define CY_SYSCLK_TRIM_ECO_Msk  (SRSS_CLK_TRIM_ECO_CTL_WDTRIM_Msk | \
                                 SRSS_CLK_TRIM_ECO_CTL_ATRIM_Msk  | \
                                 SRSS_CLK_TRIM_ECO_CTL_FTRIM_Msk  | \
                                 SRSS_CLK_TRIM_ECO_CTL_RTRIM_Msk  | \
                                 SRSS_CLK_TRIM_ECO_CTL_GTRIM_Msk)

/** \cond *********************************************************************
* Function Name: cy_sqrt
* Calculates square root.
* The input is 32-bit wide.
* The result is 16-bit wide.
*******************************************************************************/
#if !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
static uint32_t cy_sqrt(uint32_t x);
static uint32_t cy_sqrt(uint32_t x)
{
    uint32_t i;
    uint32_t res = 0UL;
    uint32_t add = 0x8000UL;

    for(i = 0UL; i < 16UL; i++)
    {
        uint32_t tmp = res | add;

        if (x >= (tmp * tmp))
        {
            res = tmp;
        }

        add >>= 1U;
    }

    return (res);
}
#endif /* !((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

static uint32_t ecoFrequency = 0UL; /* Internal storage for ECO frequency user setting */

#define CY_SYSCLK_ECO_FREQ_MIN (16000000UL) /* 16 MHz */
#define CY_SYSCLK_ECO_FREQ_MAX (35000000UL) /* 35 MHz */
#define CY_SYSCLK_ECO_CSM_MAX  (100UL)      /* 100 pF */
#define CY_SYSCLK_ECO_ESR_MAX  (1000UL)     /* 1000 Ohm */
#define CY_SYSCLK_ECO_DRV_MAX  (2000UL)     /* 2 mW */

#define CY_SYSCLK_ECO_IS_FREQ_VALID(freq) ((CY_SYSCLK_ECO_FREQ_MIN <= (freq)) && ((freq) <= CY_SYSCLK_ECO_FREQ_MAX))
#define CY_SYSCLK_ECO_IS_CSM_VALID(csm)   ((0UL < (csm)) && ((csm) <= CY_SYSCLK_ECO_CSM_MAX))
#define CY_SYSCLK_ECO_IS_ESR_VALID(esr)   ((0UL < (esr)) && ((esr) <= CY_SYSCLK_ECO_ESR_MAX))
#define CY_SYSCLK_ECO_IS_DRV_VALID(drv)   ((0UL < (drv)) && ((drv) <= CY_SYSCLK_ECO_DRV_MAX))
/** \endcond */

void Cy_SysClk_EcoDisable(void)
{
#if defined (CY_DEVICE_SECURE)
    cy_en_pra_status_t retStatus;
    retStatus = CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_ECO_DISABLE, 0UL);

    if (retStatus != CY_PRA_STATUS_SUCCESS)
    {
        CY_ASSERT_L1(false);
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    SRSS_CLK_ECO_CONFIG &= ~SRSS_CLK_ECO_CONFIG_ECO_EN_Msk;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
}


uint32_t Cy_SysClk_EcoGetStatus(void)
{
    /* if ECO is not ready, just report the ECO_OK bit. Otherwise report 2 = ECO ready */
    return ((SRSS_CLK_ECO_STATUS_Msk == (SRSS_CLK_ECO_STATUS_Msk & SRSS_CLK_ECO_STATUS)) ?
      CY_SYSCLK_ECOSTAT_STABLE : (SRSS_CLK_ECO_STATUS_ECO_OK_Msk & SRSS_CLK_ECO_STATUS));
}


cy_en_sysclk_status_t Cy_SysClk_EcoConfigure(uint32_t freq, uint32_t cSum, uint32_t esr, uint32_t driveLevel)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;

#if defined (CY_DEVICE_SECURE)
    cy_stc_pra_clk_eco_configure_t ecoConfig;
    ecoConfig.praClkEcofreq = freq;
    ecoConfig.praCsum = cSum;
    ecoConfig.praEsr = esr;
    ecoConfig.praDriveLevel = driveLevel;
    retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_ECO_CONFIGURE, &ecoConfig);
    if(CY_SYSCLK_SUCCESS == retVal)
    {
        ecoFrequency = freq; /* Store the ECO frequency */
    }
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))


    if (0UL != (SRSS_CLK_ECO_CONFIG_ECO_EN_Msk & SRSS_CLK_ECO_CONFIG))
    {
        retVal = CY_SYSCLK_INVALID_STATE;
    }
    else if ((CY_SYSCLK_ECO_IS_FREQ_VALID(freq)) &&
             (CY_SYSCLK_ECO_IS_CSM_VALID(cSum)) &&
             (CY_SYSCLK_ECO_IS_ESR_VALID(esr)) &&
             (CY_SYSCLK_ECO_IS_DRV_VALID(driveLevel)))
    {
        /* Calculate intermediate values */
        uint32_t freqKhz = CY_SYSLIB_DIV_ROUND(freq, 1000UL);

        uint32_t maxAmpl = CY_SYSLIB_DIV_ROUND((159155UL * /* 5 * 100000 / PI */
                   cy_sqrt(CY_SYSLIB_DIV_ROUND(2000000UL * driveLevel, esr))), /* Scaled by 2 */
                                               (freqKhz * cSum)); /* The result is scaled by 10^3 */

        /* 10^9 / (5 * 4 * 4 * PI^2) = 1266514,7955292221430484932901216.. -> 126651, scaled by 10 */
        uint32_t ampSect = (CY_SYSLIB_DIV_ROUND(cSum * cSum *
                            CY_SYSLIB_DIV_ROUND(freqKhz * freqKhz, 126651UL), 100UL) * esr)/ 900000UL;

        if ((maxAmpl >= 650UL) && (ampSect <= 3UL))
        {
            uint32_t gtrim = (ampSect > 1UL) ? ampSect :
                            ((ampSect == 1UL) ? 0UL : 1UL);

            /* Update all fields of trim control register with one write, without changing the ITRIM field */
            uint32_t reg = _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_WDTRIM, 7UL) |
                           _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_ATRIM, 15UL) |
                           _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_FTRIM, 3UL)  |
                           _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_RTRIM, 0UL)  |
                           _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_GTRIM, gtrim);

            CY_REG32_CLR_SET(SRSS_CLK_TRIM_ECO_CTL, CY_SYSCLK_TRIM_ECO, reg);

            SRSS_CLK_ECO_CONFIG |= SRSS_CLK_ECO_CONFIG_AGC_EN_Msk;

            ecoFrequency = freq; /* Store the ECO frequency */

            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else
    {
        /* Return CY_SYSCLK_BAD_PARAM */
    }
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_EcoEnable(uint32_t timeoutus)
{
    cy_en_sysclk_status_t retVal;
#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_ECO_ENABLE, timeoutus);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))

    bool zeroTimeout = (0UL == timeoutus);
    retVal = CY_SYSCLK_INVALID_STATE;

    /* Invalid state error if ECO is already enabled */
    if (0UL == (SRSS_CLK_ECO_CONFIG_ECO_EN_Msk & SRSS_CLK_ECO_CONFIG))
    {
        /* Set ECO enable */
        SRSS_CLK_ECO_CONFIG |= SRSS_CLK_ECO_CONFIG_ECO_EN_Msk;

        /* Wait for CY_SYSCLK_ECOSTAT_STABLE */
        for (; (CY_SYSCLK_ECOSTAT_STABLE != Cy_SysClk_EcoGetStatus()) && (0UL != timeoutus); timeoutus--)
        {
            Cy_SysLib_DelayUs(1U);
        }

        if (zeroTimeout || (0UL != timeoutus))
        {
            retVal = CY_SYSCLK_SUCCESS;
        }
        else
        {
            /* If ECO doesn't start, then disable it */
            SRSS_CLK_ECO_CONFIG &= ~SRSS_CLK_ECO_CONFIG_ECO_EN_Msk;
            retVal = CY_SYSCLK_TIMEOUT;
        }
    }
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    return (retVal);
}


uint32_t Cy_SysClk_EcoGetFrequency(void)
{
    return ((CY_SYSCLK_ECOSTAT_STABLE == Cy_SysClk_EcoGetStatus()) ? ecoFrequency : 0UL);
}


/* ========================================================================== */
/* ====================    INPUT MULTIPLEXER SECTION    ===================== */
/* ========================================================================== */


cy_en_sysclk_status_t Cy_SysClk_ClkPathSetSource(uint32_t clkPath, cy_en_clkpath_in_sources_t source)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if ((clkPath < CY_SRSS_NUM_CLKPATH) &&
        ((source <= CY_SYSCLK_CLKPATH_IN_DSIMUX) ||
         ((CY_SYSCLK_CLKPATH_IN_DSI <= source) && (source <= CY_SYSCLK_CLKPATH_IN_PILO))))
    {
#if defined (CY_DEVICE_SECURE)
        cy_stc_pra_clkpathsetsource_t clkpath_set_source;
        clkpath_set_source.clk_path = clkPath;
        clkpath_set_source.source   = source;
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PATH_SET_SOURCE, &clkpath_set_source);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))

        if (source >= CY_SYSCLK_CLKPATH_IN_DSI)
        {
            SRSS_CLK_DSI_SELECT[clkPath] = _VAL2FLD(SRSS_CLK_DSI_SELECT_DSI_MUX, (uint32_t)source);
            SRSS_CLK_PATH_SELECT[clkPath] = _VAL2FLD(SRSS_CLK_PATH_SELECT_PATH_MUX, (uint32_t)CY_SYSCLK_CLKPATH_IN_DSIMUX);
        }
        else
        {
            SRSS_CLK_PATH_SELECT[clkPath] = _VAL2FLD(SRSS_CLK_PATH_SELECT_PATH_MUX, (uint32_t)source);
        }
        retVal = CY_SYSCLK_SUCCESS;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    }
    return (retVal);

}


cy_en_clkpath_in_sources_t Cy_SysClk_ClkPathGetSource(uint32_t clkPath)
{
    CY_ASSERT_L1(clkPath < CY_SRSS_NUM_CLKPATH);
    cy_en_clkpath_in_sources_t retVal =
        (cy_en_clkpath_in_sources_t )((uint32_t)_FLD2VAL(SRSS_CLK_PATH_SELECT_PATH_MUX, SRSS_CLK_PATH_SELECT[clkPath]));
    if (retVal == CY_SYSCLK_CLKPATH_IN_DSIMUX)
    {
        retVal = (cy_en_clkpath_in_sources_t)((uint32_t)(((uint32_t)CY_SYSCLK_CLKPATH_IN_DSI) |
                    ((uint32_t)(_FLD2VAL(SRSS_CLK_DSI_SELECT_DSI_MUX, SRSS_CLK_DSI_SELECT[clkPath])))));
    }
    return (retVal);
}


uint32_t Cy_SysClk_ClkPathMuxGetFrequency(uint32_t clkPath)
{
    CY_ASSERT_L1(clkPath < CY_SRSS_NUM_CLKPATH);

    uint32_t freq = 0UL;    /* The path mux output frequency in Hz, 0 = an unknown frequency */

    /* Get the frequency of the source, i.e., the path mux input */
    switch(Cy_SysClk_ClkPathGetSource(clkPath))
    {
        case CY_SYSCLK_CLKPATH_IN_IMO: /* The IMO frequency is fixed at 8 MHz */
            freq = CY_SYSCLK_IMO_FREQ;
            break;

        case CY_SYSCLK_CLKPATH_IN_EXT:
            freq = Cy_SysClk_ExtClkGetFrequency();
            break;

        case CY_SYSCLK_CLKPATH_IN_ECO:
            freq = Cy_SysClk_EcoGetFrequency();
            break;

        case CY_SYSCLK_CLKPATH_IN_ALTHF:
            freq = Cy_SysClk_AltHfGetFrequency();
            break;

        case CY_SYSCLK_CLKPATH_IN_ILO:
            freq = (0UL != (SRSS_CLK_ILO_CONFIG & SRSS_CLK_ILO_CONFIG_ENABLE_Msk)) ? CY_SYSCLK_ILO_FREQ : 0UL;
            break;

        case CY_SYSCLK_CLKPATH_IN_WCO:
            freq = (Cy_SysClk_WcoOkay()) ? CY_SYSCLK_WCO_FREQ : 0UL;
            break;

        case CY_SYSCLK_CLKPATH_IN_PILO:
            freq = (0UL != (SRSS_CLK_PILO_CONFIG & SRSS_CLK_PILO_CONFIG_PILO_EN_Msk)) ? CY_SYSCLK_PILO_FREQ : 0UL;
            break;

        case CY_SYSCLK_CLKPATH_IN_ALTLF:
            freq = Cy_SysClk_AltLfGetFrequency();
            break;

        default:
            /* Don't know the frequency of dsi_out, leave freq = 0UL */
            break;
    }

    return (freq);
}


uint32_t Cy_SysClk_ClkPathGetFrequency(uint32_t clkPath)
{
    CY_ASSERT_L1(clkPath < CY_SRSS_NUM_CLKPATH);

    uint32_t freq = 0UL;

    if (clkPath == (uint32_t)CY_SYSCLK_CLKHF_IN_CLKPATH0) /* FLL? (always path 0) */
    {
        freq = Cy_SysClk_FllGetFrequency();
    }
    else if (clkPath <= CY_SRSS_NUM_PLL) /* PLL? (always path 1...N)*/
    {
        freq = Cy_SysClk_PllGetFrequency(clkPath);
    }
    else
    {
        /* Do nothing with the path mux frequency */
    }

    if(freq==0UL)
    {
        freq = Cy_SysClk_ClkPathMuxGetFrequency(clkPath);
    }

return (freq);
}


/* ========================================================================== */
/* ===========================    FLL SECTION    ============================ */
/* ========================================================================== */


#define  CY_SYSCLK_FLL_MIN_CCO_OUTPUT_FREQ (48000000UL)
#define  CY_SYSCLK_FLL_MIN_OUTPUT_FREQ     (CY_SYSCLK_FLL_MIN_CCO_OUTPUT_FREQ / 2U)
#define  CY_SYSCLK_FLL_MAX_OUTPUT_FREQ     (100000000UL)

#define  CY_SYSCLK_FLL_IS_CCO_RANGE_VALID(range) (((range) == CY_SYSCLK_FLL_CCO_RANGE0) || \
                                                  ((range) == CY_SYSCLK_FLL_CCO_RANGE1) || \
                                                  ((range) == CY_SYSCLK_FLL_CCO_RANGE2) || \
                                                  ((range) == CY_SYSCLK_FLL_CCO_RANGE3) || \
                                                  ((range) == CY_SYSCLK_FLL_CCO_RANGE4))
/** \cond INTERNAL */
#define  CY_SYSCLK_FLL_INT_COEF (327680000UL)
#define  CY_SYSCLK_FLL_GAIN_IDX (11U)
#define  CY_SYSCLK_FLL_GAIN_VAL (8UL * CY_SYSCLK_FLL_INT_COEF)

#define TRIM_STEPS_SCALE        (100000000ULL) /* 10 ^ 8 */
#define MARGIN_SCALE            (100000ULL) /* 10 ^ 5 */
/** \endcond */

bool Cy_SysClk_FllIsEnabled(void)
{
    return (_FLD2BOOL(SRSS_CLK_FLL_CONFIG_FLL_ENABLE, SRSS_CLK_FLL_CONFIG));
}


bool Cy_SysClk_FllLocked(void)
{
    return (_FLD2BOOL(SRSS_CLK_FLL_STATUS_LOCKED, SRSS_CLK_FLL_STATUS));
}


cy_en_sysclk_status_t Cy_SysClk_FllDisable(void)
{
    cy_en_sysclk_status_t retStatus;
#if defined (CY_DEVICE_SECURE)
    retStatus = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_FLL_DISABLE, 0UL);

#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
    SRSS_CLK_FLL_CONFIG  &= ~SRSS_CLK_FLL_CONFIG_FLL_ENABLE_Msk;
    SRSS_CLK_FLL_CONFIG4 &= ~SRSS_CLK_FLL_CONFIG4_CCO_ENABLE_Msk;
    retStatus = (CY_SYSCLK_SUCCESS);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    return retStatus;
}


cy_en_sysclk_status_t Cy_SysClk_FllConfigure(uint32_t inputFreq, uint32_t outputFreq, cy_en_fll_pll_output_mode_t outputMode)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_SUCCESS;

    /* check for errors */
    if ((outputFreq < CY_SYSCLK_FLL_MIN_OUTPUT_FREQ) || (CY_SYSCLK_FLL_MAX_OUTPUT_FREQ < outputFreq) || /* invalid output frequency */
      (((outputFreq * 5UL) / inputFreq) < 11UL)) /* check output/input frequency ratio */
    {
        retVal = CY_SYSCLK_BAD_PARAM;
    }
    else /* no errors */
    {
        /* If output mode is bypass (input routed directly to output), then done.
           The output frequency equals the input frequency regardless of the
           frequency parameters. */
        if (outputMode != CY_SYSCLK_FLLPLL_OUTPUT_INPUT)
        {
            cy_stc_fll_manual_config_t config;
            uint32_t ccoFreq;
            bool wcoSource = (CY_SYSCLK_CLKPATH_IN_WCO == Cy_SysClk_ClkPathGetSource(0UL/*FLL*/)) ? true : false;

            config.outputMode = outputMode;
            /* 1. Output division by 2 is always required */
            config.enableOutputDiv = true;
            /* 2. Compute the target CCO frequency from the target output frequency and output division */
            ccoFreq = outputFreq * 2UL;
            /* 3. Compute the CCO range value from the CCO frequency */
            config.ccoRange = ((ccoFreq >= 150339200UL) ? CY_SYSCLK_FLL_CCO_RANGE4 :
                               ((ccoFreq >= 113009380UL) ? CY_SYSCLK_FLL_CCO_RANGE3 :
                                ((ccoFreq >=  84948700UL) ? CY_SYSCLK_FLL_CCO_RANGE2 :
                                 ((ccoFreq >=  63855600UL) ? CY_SYSCLK_FLL_CCO_RANGE1 : CY_SYSCLK_FLL_CCO_RANGE0))));

        /* 4. Compute the FLL reference divider value.
              refDiv is a constant if the WCO is the FLL source, otherwise the formula is
              refDiv = ROUNDUP((inputFreq / outputFreq) * 250) */
            config.refDiv = wcoSource ? 19U : (uint16_t)CY_SYSLIB_DIV_ROUNDUP((uint64_t)inputFreq * 250ULL, (uint64_t)outputFreq);

        /* 5. Compute the FLL multiplier value.
              Formula is fllMult = ccoFreq / (inputFreq / refDiv) */
            config.fllMult = (uint32_t)CY_SYSLIB_DIV_ROUNDUP((uint64_t)ccoFreq * (uint64_t)config.refDiv, (uint64_t)inputFreq);
        /* 6. Compute the lock tolerance.
              Formula is lock tolerance = 1.5 * fllMult * (((1 + CCO accuracy) / (1 - source clock accuracy)) - 1)
              We assume CCO accuracy is 0.25%.
              We assume the source clock accuracy = 1%. This is the accuracy of the IMO.
              Therefore the formula is lock tolerance = 1.5 * fllMult * 0.012626 = 0.018939 * fllMult */
            config.lockTolerance = (uint16_t)CY_SYSLIB_DIV_ROUNDUP(config.fllMult * 18939UL, 1000000UL);

            {
                /* constants indexed by ccoRange */
                const uint32_t trimSteps[] = {110340UL, 110200UL, 110000UL, 110000UL, 117062UL}; /* Scaled by 10^8 */
                const uint32_t margin[] = {436UL, 581UL, 772UL, 1030UL, 1320UL}; /* Scaled by 10^5 */
        /* 7. Compute the CCO igain and pgain */
                {
                    /* intermediate parameters */
                    uint32_t kcco = (trimSteps[config.ccoRange] * margin[config.ccoRange]);
                    uint32_t ki_p = (uint32_t)CY_SYSLIB_DIV_ROUND(850ULL * CY_SYSCLK_FLL_INT_COEF * inputFreq, (uint64_t)kcco * (uint64_t)config.refDiv);

                    /* find the largest IGAIN value that is less than or equal to ki_p */
                    uint32_t locigain = CY_SYSCLK_FLL_GAIN_VAL;
                    uint32_t locpgain = CY_SYSCLK_FLL_GAIN_VAL;

                    /* find the largest IGAIN value that is less than or equal to ki_p */
                    for(config.igain = CY_SYSCLK_FLL_GAIN_IDX; config.igain != 0UL; config.igain--)
                    {
                       if(locigain <= ki_p)
                       {
                          break;
                       }
                       locigain >>= 1U;
                    }
                    /* decrement igain if the WCO is the FLL source */
                    if (wcoSource && (config.igain > 0U))
                    {
                        config.igain--;
                        locigain >>= 1U;
                    }

                    /* then find the largest PGAIN value that is less than or equal to ki_p - igain */
                    for(config.pgain = CY_SYSCLK_FLL_GAIN_IDX; config.pgain != 0UL; config.pgain--)
                    {
                      if(locpgain <= (ki_p - locigain))
                      {
                          break;
                      }
                      locpgain >>= 1U;
                    }

                    /* decrement pgain if the WCO is the FLL source */
                    if (wcoSource && (config.pgain > 0U))
                    {
                        config.pgain--;
                    }
                }

        /* 8. Compute the CCO_FREQ bits in CLK_FLL_CONFIG4 register */
                {
                    uint64_t cmp = CY_SYSLIB_DIV_ROUND(((TRIM_STEPS_SCALE / MARGIN_SCALE) * (uint64_t)ccoFreq), (uint64_t)margin[config.ccoRange]);
                    uint64_t mlt = TRIM_STEPS_SCALE + (uint64_t)trimSteps[config.ccoRange];
                    uint64_t res = mlt;

                    config.cco_Freq = 0U;

                    while(res < cmp)
                    {
                        res *= mlt;
                        res /= TRIM_STEPS_SCALE;
                        config.cco_Freq++;
                    }
                }
            }

        /* 9. Compute the settling count, using a 1 usec settling time. Use a constant if the WCO is the FLL source */
            {
                uint64_t fref = CY_SYSLIB_DIV_ROUND(6000ULL * (uint64_t)inputFreq, (uint64_t)config.refDiv);
                uint32_t divval = CY_SYSLIB_DIV_ROUNDUP(inputFreq, 1000000UL);
                uint32_t altval = (uint32_t)CY_SYSLIB_DIV_ROUNDUP((uint64_t)divval * fref, 6000000ULL) + 1UL;

                config.settlingCount = wcoSource ? 200U : (uint16_t)
                          ((outputFreq < fref) ? divval :
                            ((divval > altval) ? divval : altval));
            }
        /* Configure FLL based on calculated values */
            retVal = Cy_SysClk_FllManualConfigure(&config);
        }
        else /* if not, bypass output mode */
        {
            CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
        }
    }

    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_FllManualConfigure(const cy_stc_fll_manual_config_t *config)
{
    cy_en_sysclk_status_t retVal;
#if defined (CY_DEVICE_SECURE)
    retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_FLL_MANCONFIG, config);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    retVal = CY_SYSCLK_INVALID_STATE;

    /* Check for errors */
    CY_ASSERT_L1(config != NULL);

    if (!Cy_SysClk_FllIsEnabled()) /* If disabled */
    {
        /* update CLK_FLL_CONFIG register with 2 parameters; FLL_ENABLE is already 0 */
        /* asserts just check for bitfield overflow */
        CY_ASSERT_L1(config->fllMult <= (SRSS_CLK_FLL_CONFIG_FLL_MULT_Msk >> SRSS_CLK_FLL_CONFIG_FLL_MULT_Pos));

        SRSS_CLK_FLL_CONFIG = _VAL2FLD(SRSS_CLK_FLL_CONFIG_FLL_MULT, config->fllMult) |
                             _BOOL2FLD(SRSS_CLK_FLL_CONFIG_FLL_OUTPUT_DIV, config->enableOutputDiv);

        /* update CLK_FLL_CONFIG2 register with 2 parameters */
        /* asserts just check for bitfield overflow */
        CY_ASSERT_L1(config->refDiv <= (SRSS_CLK_FLL_CONFIG2_FLL_REF_DIV_Msk >> SRSS_CLK_FLL_CONFIG2_FLL_REF_DIV_Pos));
        CY_ASSERT_L1(config->lockTolerance <= (SRSS_CLK_FLL_CONFIG2_LOCK_TOL_Msk >> SRSS_CLK_FLL_CONFIG2_LOCK_TOL_Pos));

        SRSS_CLK_FLL_CONFIG2 = _VAL2FLD(SRSS_CLK_FLL_CONFIG2_FLL_REF_DIV, config->refDiv) |
                               _VAL2FLD(SRSS_CLK_FLL_CONFIG2_LOCK_TOL, config->lockTolerance);

        /* update CLK_FLL_CONFIG3 register with 4 parameters */
        /* asserts just check for bitfield overflow */
        CY_ASSERT_L1(config->igain <= (SRSS_CLK_FLL_CONFIG3_FLL_LF_IGAIN_Msk >> SRSS_CLK_FLL_CONFIG3_FLL_LF_IGAIN_Pos));
        CY_ASSERT_L1(config->pgain <= (SRSS_CLK_FLL_CONFIG3_FLL_LF_PGAIN_Msk >> SRSS_CLK_FLL_CONFIG3_FLL_LF_PGAIN_Pos));
        CY_ASSERT_L1(config->settlingCount <= (SRSS_CLK_FLL_CONFIG3_SETTLING_COUNT_Msk >> SRSS_CLK_FLL_CONFIG3_SETTLING_COUNT_Pos));

        SRSS_CLK_FLL_CONFIG3 = _VAL2FLD(SRSS_CLK_FLL_CONFIG3_FLL_LF_IGAIN, config->igain) |
                               _VAL2FLD(SRSS_CLK_FLL_CONFIG3_FLL_LF_PGAIN, config->pgain) |
                               _VAL2FLD(SRSS_CLK_FLL_CONFIG3_SETTLING_COUNT, config->settlingCount) |
                               _VAL2FLD(SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, config->outputMode);

        /* update CLK_FLL_CONFIG4 register with 1 parameter; preserve other bits */
        /* asserts just check for bitfield overflow */
        CY_ASSERT_L1(CY_SYSCLK_FLL_IS_CCO_RANGE_VALID(config->ccoRange));
        CY_ASSERT_L1(config->cco_Freq <= (SRSS_CLK_FLL_CONFIG4_CCO_FREQ_Msk >> SRSS_CLK_FLL_CONFIG4_CCO_FREQ_Pos));

        CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG4, SRSS_CLK_FLL_CONFIG4_CCO_RANGE, (uint32_t)(config->ccoRange));
        CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG4, SRSS_CLK_FLL_CONFIG4_CCO_FREQ, (uint32_t)(config->cco_Freq));

        retVal = CY_SYSCLK_SUCCESS;
    }

#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    return (retVal);
}


void Cy_SysClk_FllGetConfiguration(cy_stc_fll_manual_config_t *config)
{
    CY_ASSERT_L1(config != NULL);
    /* read 2 parameters from CLK_FLL_CONFIG register */
    uint32_t tempReg = SRSS_CLK_FLL_CONFIG;
    config->fllMult         = _FLD2VAL(SRSS_CLK_FLL_CONFIG_FLL_MULT, tempReg);
    config->enableOutputDiv = _FLD2BOOL(SRSS_CLK_FLL_CONFIG_FLL_OUTPUT_DIV, tempReg);
    /* read 2 parameters from CLK_FLL_CONFIG2 register */
    tempReg = SRSS_CLK_FLL_CONFIG2;
    config->refDiv          = (uint16_t)_FLD2VAL(SRSS_CLK_FLL_CONFIG2_FLL_REF_DIV, tempReg);
    config->lockTolerance   = (uint16_t)_FLD2VAL(SRSS_CLK_FLL_CONFIG2_LOCK_TOL, tempReg);
    /* read 4 parameters from CLK_FLL_CONFIG3 register */
    tempReg = SRSS_CLK_FLL_CONFIG3;
    config->igain           = (uint8_t)_FLD2VAL(SRSS_CLK_FLL_CONFIG3_FLL_LF_IGAIN, tempReg);
    config->pgain           = (uint8_t)_FLD2VAL(SRSS_CLK_FLL_CONFIG3_FLL_LF_PGAIN, tempReg);
    config->settlingCount   = (uint16_t)_FLD2VAL(SRSS_CLK_FLL_CONFIG3_SETTLING_COUNT, tempReg);
    config->outputMode      = (cy_en_fll_pll_output_mode_t)((uint32_t)_FLD2VAL(SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, tempReg));
    /* read 2 parameters from CLK_FLL_CONFIG4 register */
    tempReg = SRSS_CLK_FLL_CONFIG4;
    config->ccoRange        = (cy_en_fll_cco_ranges_t)((uint32_t)_FLD2VAL(SRSS_CLK_FLL_CONFIG4_CCO_RANGE, tempReg));
    config->cco_Freq        = (uint16_t)_FLD2VAL(SRSS_CLK_FLL_CONFIG4_CCO_FREQ, tempReg);
}


cy_en_sysclk_status_t Cy_SysClk_FllEnable(uint32_t timeoutus)
{
    cy_en_sysclk_status_t retStatus;
#if defined (CY_DEVICE_SECURE)
    retStatus = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_FLL_ENABLE, timeoutus);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
    bool zeroTimeout = (0UL == timeoutus);

    /* first set the CCO enable bit */
    SRSS_CLK_FLL_CONFIG4 |= SRSS_CLK_FLL_CONFIG4_CCO_ENABLE_Msk;

    /* Wait until CCO is ready */
    for (; (!_FLD2BOOL(SRSS_CLK_FLL_STATUS_CCO_READY, SRSS_CLK_FLL_STATUS)) && /* if cco_ready == 0 */
           (0UL != timeoutus);
         timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    /* Set the FLL bypass mode to FLL_REF */
    CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);

    /* Set the FLL enable bit, if CCO is ready */
    if (zeroTimeout || (0UL != timeoutus))
    {
        SRSS_CLK_FLL_CONFIG |= SRSS_CLK_FLL_CONFIG_FLL_ENABLE_Msk;
    }

    /* now do the timeout wait for FLL_STATUS, bit LOCKED */
    for (; (!Cy_SysClk_FllLocked()) && /* if locked == 0 */
           (0UL != timeoutus);
         timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    if (zeroTimeout || (0UL != timeoutus))
    {
        /* Set the FLL bypass mode to FLL_OUT (ignoring lock indicator) */
        CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
    }
    else
    {
        /* If lock doesn't occur, FLL is stopped */
        (void)Cy_SysClk_FllDisable();
    }

    retStatus = ((zeroTimeout || (0UL != timeoutus)) ? CY_SYSCLK_SUCCESS : CY_SYSCLK_TIMEOUT);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    return retStatus;
}


/* ========================================================================== */
/* ===========================    PLL SECTION    ============================ */
/* ========================================================================== */

/* PLL OUTPUT_DIV bitfield allowable range */
#define CY_SYSCLK_PLL_MIN_OUTPUT_DIV   (2UL)
#define CY_SYSCLK_PLL_MAX_OUTPUT_DIV   (16UL)

/* PLL REFERENCE_DIV bitfield allowable range */
#define CY_SYSCLK_PLL_MIN_REF_DIV      (1UL)
#define CY_SYSCLK_PLL_MAX_REF_DIV      (18UL)

/* PLL FEEDBACK_DIV bitfield allowable ranges, LF and normal modes */
#define CY_SYSCLK_PLL_MIN_FB_DIV_LF    (19UL)
#define CY_SYSCLK_PLL_MAX_FB_DIV_LF    (56UL)
#define CY_SYSCLK_PLL_MIN_FB_DIV_NORM  (22UL)
#define CY_SYSCLK_PLL_MAX_FB_DIV_NORM  (112UL)

/* PLL FEEDBACK_DIV bitfield allowable range selection */
#define CY_SYSCLK_PLL_MIN_FB_DIV       ((config->lfMode) ? CY_SYSCLK_PLL_MIN_FB_DIV_LF : CY_SYSCLK_PLL_MIN_FB_DIV_NORM)
#define CY_SYSCLK_PLL_MAX_FB_DIV       ((config->lfMode) ? CY_SYSCLK_PLL_MAX_FB_DIV_LF : CY_SYSCLK_PLL_MAX_FB_DIV_NORM)

/* PLL Fvco range allowable ranges, LF and normal modes */
#define CY_SYSCLK_PLL_MIN_FVCO_LF      (170000000UL)
#define CY_SYSCLK_PLL_MAX_FVCO_LF      (200000000UL)
#define CY_SYSCLK_PLL_MIN_FVCO_NORM    (200000000UL)
#define CY_SYSCLK_PLL_MAX_FVCO_NORM    (400000000UL)
/* PLL Fvco range selection */
#define CY_SYSCLK_PLL_MIN_FVCO         ((config->lfMode) ? CY_SYSCLK_PLL_MIN_FVCO_LF : CY_SYSCLK_PLL_MIN_FVCO_NORM)
#define CY_SYSCLK_PLL_MAX_FVCO         ((config->lfMode) ? CY_SYSCLK_PLL_MAX_FVCO_LF : CY_SYSCLK_PLL_MAX_FVCO_NORM)

/* PLL input and output frequency limits */
#define CY_SYSCLK_PLL_MIN_IN_FREQ  (4000000UL)
#define CY_SYSCLK_PLL_MAX_IN_FREQ  (64000000UL)
#define CY_SYSCLK_PLL_MIN_OUT_FREQ (CY_SYSCLK_PLL_MIN_FVCO / CY_SYSCLK_PLL_MAX_OUTPUT_DIV)
#define CY_SYSCLK_PLL_MAX_OUT_FREQ (150000000UL)


bool Cy_SysClk_PllIsEnabled(uint32_t clkPath)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < CY_SRSS_NUM_PLL);
    return (_FLD2BOOL(SRSS_CLK_PLL_CONFIG_ENABLE, SRSS_CLK_PLL_CONFIG[clkPath]));
}


bool Cy_SysClk_PllLocked(uint32_t clkPath)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < CY_SRSS_NUM_PLL);
    return (_FLD2BOOL(SRSS_CLK_PLL_STATUS_LOCKED, SRSS_CLK_PLL_STATUS[clkPath]));
}


bool Cy_SysClk_PllLostLock(uint32_t clkPath)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    (void) clkPath;
    return false;

#else
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < CY_SRSS_NUM_PLL);
    bool retVal = _FLD2BOOL(SRSS_CLK_PLL_STATUS_UNLOCK_OCCURRED, SRSS_CLK_PLL_STATUS[clkPath]);
    /* write a 1 to clear the unlock occurred bit */
    SRSS_CLK_PLL_STATUS[clkPath] = SRSS_CLK_PLL_STATUS_UNLOCK_OCCURRED_Msk;
    return (retVal);
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
}


cy_en_sysclk_status_t Cy_SysClk_PllDisable(uint32_t clkPath)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    clkPath--; /* to correctly access PLL config and status registers structures */
    if (clkPath < CY_SRSS_NUM_PLL)
    {
#if defined (CY_DEVICE_SECURE)
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PLL_DISABLE, (clkPath + 1U));
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
        /* First bypass PLL */
        CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[clkPath], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
        /* Wait at least 6 PLL clock cycles */
        Cy_SysLib_DelayUs(1U);
        /* And now disable the PLL itself */
        SRSS_CLK_PLL_CONFIG[clkPath] &= ~SRSS_CLK_PLL_CONFIG_ENABLE_Msk;
        retVal = CY_SYSCLK_SUCCESS;
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    }
    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_PllConfigure(uint32_t clkPath, const cy_stc_pll_config_t *config)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_SUCCESS;

    if (((config->inputFreq)  < CY_SYSCLK_PLL_MIN_IN_FREQ)  || (CY_SYSCLK_PLL_MAX_IN_FREQ  < (config->inputFreq)) ||
        ((config->outputFreq) < CY_SYSCLK_PLL_MIN_OUT_FREQ) || (CY_SYSCLK_PLL_MAX_OUT_FREQ < (config->outputFreq)))
    {
        retVal = CY_SYSCLK_BAD_PARAM;
    }
    else
    {
        cy_stc_pll_manual_config_t manualConfig = {0U, 0U, 0U, false, CY_SYSCLK_FLLPLL_OUTPUT_AUTO};

        /* If output mode is not bypass (input routed directly to output), then
           calculate new parameters. */
        if (config->outputMode != CY_SYSCLK_FLLPLL_OUTPUT_INPUT)
        {
            /* for each possible value of OUTPUT_DIV and REFERENCE_DIV (Q), try
               to find a value for FEEDBACK_DIV (P) that gives an output frequency
               as close as possible to the desired output frequency. */
            uint32_t p, q, out;
            uint32_t foutBest = 0UL; /* to ensure at least one pass through the for loops below */

            /* REFERENCE_DIV (Q) selection */
            for (q = CY_SYSCLK_PLL_MIN_REF_DIV; q <= CY_SYSCLK_PLL_MAX_REF_DIV; q++)
            {
                /* FEEDBACK_DIV (P) selection */
                for (p = CY_SYSCLK_PLL_MIN_FB_DIV; p <= CY_SYSCLK_PLL_MAX_FB_DIV; p++)
                {
                    /* Calculate the intermediate Fvco, and make sure that it's in range */
                    uint32_t fvco = (uint32_t)(((uint64_t)(config->inputFreq) * (uint64_t)p) / (uint64_t)q);
                    if ((CY_SYSCLK_PLL_MIN_FVCO <= fvco) && (fvco <= CY_SYSCLK_PLL_MAX_FVCO))
                    {
                        /* OUTPUT_DIV selection */
                        for (out = CY_SYSCLK_PLL_MIN_OUTPUT_DIV; out <= CY_SYSCLK_PLL_MAX_OUTPUT_DIV; out++)
                        {
                            /* Calculate what output frequency will actually be produced.
                               If it's closer to the target than what we have so far, then save it. */
                            uint32_t fout = ((p * config->inputFreq) / q) / out;
                            if ((uint32_t)abs((int32_t)fout - (int32_t)(config->outputFreq)) <
                                (uint32_t)abs((int32_t)foutBest - (int32_t)(config->outputFreq)))
                            {
                                if (foutBest == (config->outputFreq))
                                {
                                   break;
                                }

                                foutBest = fout;
                                manualConfig.feedbackDiv  = (uint8_t)p;
                                manualConfig.referenceDiv = (uint8_t)q;
                                manualConfig.outputDiv    = (uint8_t)out;
                            }
                        }
                    }
                }
            }
            /* exit loops if foutBest equals outputFreq */

            manualConfig.lfMode = config->lfMode;
        } /* if not, bypass output mode */

        /* If output mode is bypass (input routed directly to output), then
           use old parameters. */
        else
        {
            (void)Cy_SysClk_PllGetConfiguration(clkPath, &manualConfig);
        }
        /* configure PLL based on calculated values */

        manualConfig.outputMode = config->outputMode;
        retVal = Cy_SysClk_PllManualConfigure(clkPath, &manualConfig);

    } /* if no error */

    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_PllManualConfigure(uint32_t clkPath, const cy_stc_pll_manual_config_t *config)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_SUCCESS;

    /* check for errors */
    if (clkPath > CY_SRSS_NUM_PLL) /* invalid clock path number */
    {
        retVal = CY_SYSCLK_BAD_PARAM;
    }
    else if (Cy_SysClk_PllIsEnabled(clkPath))
    {
        retVal = CY_SYSCLK_INVALID_STATE;
    }
    /* valid divider bitfield values */
    else if ((config->outputDiv    < CY_SYSCLK_PLL_MIN_OUTPUT_DIV) || (CY_SYSCLK_PLL_MAX_OUTPUT_DIV < config->outputDiv)    ||
             (config->referenceDiv < CY_SYSCLK_PLL_MIN_REF_DIV)    || (CY_SYSCLK_PLL_MAX_REF_DIV    < config->referenceDiv) ||
             (config->feedbackDiv  < CY_SYSCLK_PLL_MIN_FB_DIV)     || (CY_SYSCLK_PLL_MAX_FB_DIV     < config->feedbackDiv))
    {
         retVal = CY_SYSCLK_BAD_PARAM;
    }
    else /* no errors */
    {
#if defined (CY_DEVICE_SECURE)
        cy_stc_pra_clk_pll_manconfigure_t pll_config;
        pll_config.clkPath   = clkPath;
        pll_config.praConfig    = (cy_stc_pll_manual_config_t *)config;
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PLL_MANCONFIG, &pll_config);
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
        clkPath--; /* to correctly access PLL config registers structure */
        /* If output mode is bypass (input routed directly to output), then done.
           The output frequency equals the input frequency regardless of the frequency parameters. */
        if (config->outputMode != CY_SYSCLK_FLLPLL_OUTPUT_INPUT)
        {
            SRSS_CLK_PLL_CONFIG[clkPath] =
                _VAL2FLD(SRSS_CLK_PLL_CONFIG_FEEDBACK_DIV,  config->feedbackDiv)  |
                _VAL2FLD(SRSS_CLK_PLL_CONFIG_REFERENCE_DIV, config->referenceDiv) |
                _VAL2FLD(SRSS_CLK_PLL_CONFIG_OUTPUT_DIV,    config->outputDiv)    |
                _VAL2FLD(SRSS_CLK_PLL_CONFIG_PLL_LF_MODE,   config->lfMode);
        }

        CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[clkPath], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, (uint32_t)config->outputMode);
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    }

    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_PllGetConfiguration(uint32_t clkPath, cy_stc_pll_manual_config_t *config)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    clkPath--; /* to correctly access PLL config and status register structures */
    if (clkPath < CY_SRSS_NUM_PLL)
    {
        uint32_t tempReg = SRSS_CLK_PLL_CONFIG[clkPath];
        config->feedbackDiv  = (uint8_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_FEEDBACK_DIV,  tempReg);
        config->referenceDiv = (uint8_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_REFERENCE_DIV, tempReg);
        config->outputDiv    = (uint8_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_OUTPUT_DIV,    tempReg);
        config->lfMode       =         _FLD2BOOL(SRSS_CLK_PLL_CONFIG_PLL_LF_MODE,   tempReg);
        config->outputMode   = (cy_en_fll_pll_output_mode_t)((uint32_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_BYPASS_SEL, tempReg));
        retVal = CY_SYSCLK_SUCCESS;
    }
    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_PllEnable(uint32_t clkPath, uint32_t timeoutus)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    bool zeroTimeout = (timeoutus == 0UL);
    clkPath--; /* to correctly access PLL config and status registers structures */
    if (clkPath < CY_SRSS_NUM_PLL)
    {
#if defined (CY_DEVICE_SECURE)
        (void)timeoutus;
        (void)zeroTimeout;
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_FUNC_POLICY, CY_PRA_CLK_FUNC_PLL_ENABLE, (clkPath + 1U));
#endif /* defined (CY_DEVICE_SECURE) */
#if ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE)))
        /* first set the PLL enable bit */
        SRSS_CLK_PLL_CONFIG[clkPath] |= SRSS_CLK_PLL_CONFIG_ENABLE_Msk;

        /* now do the timeout wait for PLL_STATUS, bit LOCKED */
        for (; (0UL == (SRSS_CLK_PLL_STATUS_LOCKED_Msk & SRSS_CLK_PLL_STATUS[clkPath])) &&
               (0UL != timeoutus);
             timeoutus--)
        {
            Cy_SysLib_DelayUs(1U);
        }

        if (zeroTimeout || (0UL != timeoutus))
        {
            /* Unbypass PLL, if it is not in AUTO mode */
            if ((uint32_t)CY_SYSCLK_FLLPLL_OUTPUT_INPUT == (uint32_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_BYPASS_SEL, SRSS_CLK_PLL_CONFIG[clkPath]))
            {
                CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[clkPath], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
            }

            retVal = CY_SYSCLK_SUCCESS;
        }
        else
        {
            /* If lock doesn't occur, then bypass PLL */
            CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[clkPath], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
            /* Wait at least 6 PLL clock cycles */
            Cy_SysLib_DelayUs(1U);
            /* And now disable the PLL itself */
            SRSS_CLK_PLL_CONFIG[clkPath] &= ~SRSS_CLK_PLL_CONFIG_ENABLE_Msk;
            retVal = CY_SYSCLK_TIMEOUT;
        }
#endif /* ((CY_CPU_CORTEX_M0P) || (!defined(CY_DEVICE_SECURE))) */
    }
    return (retVal);
}


/* ========================================================================== */
/* ====================    Clock Measurement section    ===================== */
/* ========================================================================== */
/* Slow control register default value */
#define TST_DDFT_SLOW_CTL_DEFAULT_VAL      (0x00001F1FUL)

/* Fast control register */
#define TST_DDFT_FAST_CTL_REG              (*(volatile uint32_t *) 0x40260104U)

/* Slow control register default value */
#define TST_DDFT_FAST_CTL_DEFAULT_VAL      (0x00003D3DUL)

/* Define for select signal outputs in slow clock */
#define SRSS_CLK_OUTPUT_SLOW_MASK  ((uint32_t) SRSS_CLK_OUTPUT_SLOW_SLOW_SEL0_Msk | \
                                               SRSS_CLK_OUTPUT_SLOW_SLOW_SEL1_Msk)

/* Define for select signal outputs in fast clock */
#define SRSS_CLK_OUTPUT_FAST_MASK  ((uint32_t) SRSS_CLK_OUTPUT_FAST_FAST_SEL0_Msk  | \
                                               SRSS_CLK_OUTPUT_FAST_FAST_SEL1_Msk  | \
                                               SRSS_CLK_OUTPUT_FAST_PATH_SEL0_Msk  | \
                                               SRSS_CLK_OUTPUT_FAST_PATH_SEL1_Msk  | \
                                               SRSS_CLK_OUTPUT_FAST_HFCLK_SEL0_Msk | \
                                               SRSS_CLK_OUTPUT_FAST_HFCLK_SEL1_Msk)

/* Cy_SysClk_StartClkMeasurementCounters() input parameter saved for use later in other functions */
static uint32_t clk1Count1;

/* These variables act as locks to prevent collisions between clock measurement and entry into
   Deep Sleep mode. See Cy_SysClk_DeepSleep(). */
static bool clkCounting = false;
static bool preventCounting = false;


uint32_t Cy_SysClk_ClkMeasurementCountersGetFreq(bool measuredClock, uint32_t refClkFreq)
{
    uint32_t retVal = 0UL;
    bool isMeasurementValid = false;

    /* Done counting; allow entry into Deep Sleep mode */
    clkCounting = false;

    /* Acquire the IPC to prevent changing of the shared resources at the same time */
    while(0U == (IPC_STRUCT_ACQUIRE_SUCCESS_Msk & REG_IPC_STRUCT_ACQUIRE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT))))
    {
        /* Wait until the IPC structure is released by another process */
    }

    /* Check whether the device was in the Deep Sleep mode or the flash partially blocked while the
    *  operation was done
    */
    if(SRSS_TST_DDFT_SLOW_CTL_REG == TST_DDFT_SLOW_CTL_DEFAULT_VAL)
    {
       if(SRSS_TST_DDFT_FAST_CTL_REG == TST_DDFT_FAST_CTL_DEFAULT_VAL)
       {
           isMeasurementValid = true;
       }
    }

    retVal = _FLD2VAL(SRSS_CLK_CAL_CNT2_CAL_COUNTER2, SRSS_CLK_CAL_CNT2);
    /* Release the IPC */
    REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = 0U;

    if (isMeasurementValid && (0UL != retVal))
    {
        if (!measuredClock)
        {   /* clock1 is the measured clock */
            retVal = (uint32_t)CY_SYSLIB_DIV_ROUND((uint64_t)clk1Count1 * (uint64_t)refClkFreq, (uint64_t)retVal);
        }
        else
        {   /* clock2 is the measured clock */
            retVal = (uint32_t)CY_SYSLIB_DIV_ROUND((uint64_t)retVal * (uint64_t)refClkFreq, (uint64_t)clk1Count1);
        }
    }
    else
    {
        /* Return zero value to indicate invalid measurement */
        retVal = 0UL;
    }

    return (retVal);
}


bool Cy_SysClk_ClkMeasurementCountersDone(void)
{
    return (_FLD2BOOL(SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE, SRSS_CLK_CAL_CNT1));
}


cy_en_sysclk_status_t Cy_SysClk_StartClkMeasurementCounters(cy_en_meas_clks_t clock1, uint32_t count1, cy_en_meas_clks_t clock2)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;

#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))

    cy_stc_pra_start_clk_measurement_t clkMeasurement;
    clkMeasurement.clock1 = clock1;
    clkMeasurement.count1 = count1;
    clkMeasurement.clock2 = clock2;

    /* Don't start a measurement if about to enter Deep Sleep mode */
    if (!preventCounting)
    {
        retVal = (cy_en_sysclk_status_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_CLK_FUNC_START_MEASUREMENT, &clkMeasurement);
    }

    if (CY_SYSCLK_SUCCESS == retVal)
    {
        /* Disallow entry into Deep Sleep mode while counting */
        clkCounting = true;

        /* Save this input parameter for use later, in other functions */
        clk1Count1 = count1;
    }
#else

    uint32_t clkOutputSlowVal = 0UL;
    uint32_t clkOutputFastVal = 0UL;

    uint32_t clkOutputSlowMask = 0UL;
    uint32_t clkOutputFastMask = 0UL;

    /* Prepare values for measurement control registers */

    /* Connect the indicated clocks to the respective counters:

       if clock1 is a slow clock,
         select it in SRSS_CLK_OUTPUT_SLOW.SLOW_SEL0, and SRSS_CLK_OUTPUT_FAST.FAST_SEL0 = SLOW_SEL0
       else if clock1 is a fast clock,
         select it in SRSS_CLK_OUTPUT_FAST.FAST_SEL0,
       else error, do nothing and return.

       if clock2 is a slow clock,
         select it in SRSS_CLK_OUTPUT_SLOW.SLOW_SEL1, and SRSS_CLK_OUTPUT_FAST.FAST_SEL1 = SLOW_SEL1
       else if clock2 is a fast clock,
         select it in SRSS_CLK_OUTPUT_FAST.FAST_SEL1,
       else error, do nothing and return.
    */
    if ((clock1 < CY_SYSCLK_MEAS_CLK_LAST_CLK) && (clock2 < CY_SYSCLK_MEAS_CLK_LAST_CLK) &&
        (count1 <= (SRSS_CLK_CAL_CNT1_CAL_COUNTER1_Msk >> SRSS_CLK_CAL_CNT1_CAL_COUNTER1_Pos)))
    {
        /* Disallow entry into Deep Sleep mode while counting */
        clkCounting = true;

        if (clock1 < CY_SYSCLK_MEAS_CLK_FAST_CLKS)
        { /* slow clock */
            clkOutputSlowVal |= _VAL2FLD(SRSS_CLK_OUTPUT_SLOW_SLOW_SEL0, (uint32_t)clock1);
            clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_FAST_SEL0, 7UL/*slow_sel0 output*/);

            clkOutputSlowMask |= SRSS_CLK_OUTPUT_SLOW_SLOW_SEL0_Msk;
            clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_FAST_SEL0_Msk;
        }
        else
        { /* fast clock */
            if (clock1 < CY_SYSCLK_MEAS_CLK_PATH_CLKS)
            { /* ECO, EXT, ALTHF */
                clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_FAST_SEL0, (uint32_t)clock1);
                clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_FAST_SEL0_Msk;
            }
            else
            { /* PATH or CLKHF */
                clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_FAST_SEL0, (((uint32_t)clock1 >> 8) & 0xFUL) /*use enum bits [11:8]*/);
                clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_FAST_SEL0_Msk;

                if (clock1 < CY_SYSCLK_MEAS_CLK_CLKHFS)
                { /* PATH select */
                    clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_PATH_SEL0, ((uint32_t)clock1 & 0xFUL) /*use enum bits [3:0]*/);
                    clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_PATH_SEL0_Msk;
                }
                else
                { /* CLKHF select */
                    clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_HFCLK_SEL0, ((uint32_t)clock1 & 0xFUL) /*use enum bits [3:0]*/);
                    clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_HFCLK_SEL0_Msk;
                }
            }
        } /* clock1 fast clock */

        if (clock2 < CY_SYSCLK_MEAS_CLK_FAST_CLKS)
        { /* slow clock */
            clkOutputSlowVal |= _VAL2FLD(SRSS_CLK_OUTPUT_SLOW_SLOW_SEL1, (uint32_t)clock2);
            clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_FAST_SEL1, 7UL/*slow_sel1 output*/);

            clkOutputSlowMask |= SRSS_CLK_OUTPUT_SLOW_SLOW_SEL1_Msk;
            clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_FAST_SEL1_Msk;
        }
        else
        { /* fast clock */
            if (clock2 < CY_SYSCLK_MEAS_CLK_PATH_CLKS)
            { /* ECO, EXT, ALTHF */
                clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_FAST_SEL1, (uint32_t)clock2);
                clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_FAST_SEL1_Msk;
            }
            else
            { /* PATH or CLKHF */
                clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_FAST_SEL1, (((uint32_t)clock2 >> 8) & 0xFUL) /*use enum bits [11:8]*/);
                clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_FAST_SEL1_Msk;

                if (clock2 < CY_SYSCLK_MEAS_CLK_CLKHFS)
                { /* PATH select */
                    clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_PATH_SEL1, ((uint32_t)clock2 & 0xFUL) /*use enum bits [3:0]*/);
                    clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_PATH_SEL1_Msk;
                }
                else
                { /* CLKHF select */
                    clkOutputFastVal |= _VAL2FLD(SRSS_CLK_OUTPUT_FAST_HFCLK_SEL1, ((uint32_t)clock2 & 0xFUL) /*use enum bits [3:0]*/);
                    clkOutputFastMask |= SRSS_CLK_OUTPUT_FAST_HFCLK_SEL1_Msk;
                }
            }
        } /* clock2 fast clock */

        /* Acquire the IPC to prevent changing of the shared resources at the same time */
        while(0U == (IPC_STRUCT_ACQUIRE_SUCCESS_Msk & REG_IPC_STRUCT_ACQUIRE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT))))
        {
            /* Wait until the IPC structure is released by another process */
        }

        if ((!preventCounting) /* don't start a measurement if about to enter Deep Sleep mode */  ||
            (_FLD2VAL(SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE, SRSS_CLK_CAL_CNT1) != 0UL/*1 = done*/))
        {
            /* Set default values for counters measurement control registers */
            SRSS_TST_DDFT_SLOW_CTL_REG = TST_DDFT_SLOW_CTL_DEFAULT_VAL;
            SRSS_TST_DDFT_FAST_CTL_REG = TST_DDFT_FAST_CTL_DEFAULT_VAL;

            SRSS_CLK_OUTPUT_SLOW = ((SRSS_CLK_OUTPUT_SLOW & ((uint32_t) ~clkOutputSlowMask)) | clkOutputSlowVal);
            SRSS_CLK_OUTPUT_FAST = ((SRSS_CLK_OUTPUT_FAST & ((uint32_t) ~clkOutputFastMask)) | clkOutputFastVal);

            /* Save this input parameter for use later, in other functions.
               No error checking is done on this parameter */
            clk1Count1 = count1;

            /* Counting starts when counter1 is written with a nonzero value */
            SRSS_CLK_CAL_CNT1 = clk1Count1;

            retVal = CY_SYSCLK_SUCCESS;
        }

        /* Release the IPC */
        REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = 0U;
    }

#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

    return (retVal);
}

/* ========================================================================== */
/* ==========================    TRIM SECTION    ============================ */
/* ========================================================================== */


/** \cond INTERNAL */
#define CY_SYSCLK_ILO_TARGET_FREQ  (32768UL)
/* Nominal trim step size is 1.5% of "the frequency". Using the target frequency */
#define CY_SYSCLK_ILO_TRIM_STEP    (CY_SYSLIB_DIV_ROUND(CY_SYSCLK_ILO_TARGET_FREQ * 15UL, 1000UL))

/* The step size to be used by Cy_SysClk_PiloTrim function */
static uint32_t stepSize = CY_SYSCLK_PILO_TRIM_STEP;
/** \endcond */

int32_t Cy_SysClk_IloTrim(uint32_t iloFreq)
{
    int32_t changeInTrim;
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    (void) iloFreq;
    changeInTrim = (int32_t)CY_PRA_FUNCTION_CALL_RETURN_PARAM(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_CLK_FUNC_ILO_TRIM, iloFreq);
#else
    uint32_t diff;
    bool sign = false;

    if(iloFreq > (CY_SYSCLK_ILO_TARGET_FREQ + CY_SYSCLK_ILO_TRIM_STEP))
    {
        diff = iloFreq - CY_SYSCLK_ILO_TARGET_FREQ;
    }
    else if (iloFreq < (CY_SYSCLK_ILO_TARGET_FREQ - CY_SYSCLK_ILO_TRIM_STEP))
    {
        diff = CY_SYSCLK_ILO_TARGET_FREQ - iloFreq;
        sign = true;
    }
    else
    {
        diff = 0UL;
    }

    /* Do nothing if iloFreq is already within one trim step from the target */
    if(0UL != diff)
    {
        /* Get current trim value */
        uint32_t trim = _FLD2VAL(SRSS_CLK_TRIM_ILO_CTL_ILO_FTRIM, SRSS_CLK_TRIM_ILO_CTL);

        diff = CY_SYSLIB_DIV_ROUND(diff, CY_SYSCLK_ILO_TRIM_STEP);

        if(sign)
        {
            trim += diff;
        }
        else
        {
            trim -= diff;
        }

        /* Update the trim value */
        CY_REG32_CLR_SET(SRSS_CLK_TRIM_ILO_CTL, SRSS_CLK_TRIM_ILO_CTL_ILO_FTRIM, trim);
    }

    changeInTrim = (sign ? (int32_t)diff : (0L - (int32_t)diff));
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */

    return changeInTrim;
}


/** \cond INTERNAL */
#define CY_SYSCLK_PILO_TARGET_FREQ  (32768UL)
/* nominal trim step size */
#define CY_SYSCLK_PILO_TRIM_STEP        (5UL)
/** \endcond */

int32_t Cy_SysClk_PiloTrim(uint32_t piloFreq)
{
    int32_t changeInTrim;
    uint32_t diff;
    bool sign = false;

    if(piloFreq > (CY_SYSCLK_PILO_TARGET_FREQ + stepSize))
    {
        diff = piloFreq - CY_SYSCLK_PILO_TARGET_FREQ;
    }
    else if (piloFreq < (CY_SYSCLK_PILO_TARGET_FREQ - stepSize))
    {
        diff = CY_SYSCLK_PILO_TARGET_FREQ - piloFreq;
        sign = true;
    }
    else
    {
        diff = 0UL;
    }

    /* Do nothing if piloFreq is already within one trim step from the target */
    if(0UL != diff)
    {
        /* Get current trim value */
        uint32_t trim = Cy_SysClk_PiloGetTrim();

        diff = CY_SYSLIB_DIV_ROUND(diff, stepSize);

        if(sign)
        {/* piloFreq too low. Increase the trim value */
            trim += diff;
            if (trim >= SRSS_CLK_PILO_CONFIG_PILO_FFREQ_Msk) /* limit overflow */
            {
                trim = SRSS_CLK_PILO_CONFIG_PILO_FFREQ_Msk;
            }
        }
        else
        {/* piloFreq too high. Decrease the trim value */
            trim -= diff;
            if ((int32_t)trim < 0) /* limit underflow */
            {
                trim = 0UL;
            }
        }

        /* Update the trim value */
        Cy_SysClk_PiloSetTrim(trim);
    }

    changeInTrim = ((int32_t)(sign ? (int32_t)diff : (0L - (int32_t)diff)));
return changeInTrim;
}
/** \cond INTERNAL */
#define LF_COUNT          (64u)
#define REF_COUNT         (212u)
#define FREQ_REF          (31250u)
#define TRIM_DELAY        (2000u)
#define STEP_SIZE_ITER    (8u)
/** \endcond */



void Cy_SysClk_PiloInitialTrim(void)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    CY_PRA_FUNCTION_CALL_VOID_VOID(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_CLK_FUNC_PILO_INITIAL_TRIM);
#else
    uint32_t measuredCnt  = 0xFFFFFFFFUL;
    uint32_t trimVal      = 0UL;
    int32_t  bitPos       = 9;

    do
    {
        SRSS_CLK_PILO_CONFIG &= ~(SRSS_CLK_PILO_CONFIG_PILO_FFREQ_Msk);

        /* Set 1 at BitPos in FTRIM*/
        SRSS_CLK_PILO_CONFIG |= (trimVal | ((uint32_t) 1U  << (uint32_t) bitPos));

        /* Wait for 2 ms after setting FTRIM */
        Cy_SysLib_DelayUs(TRIM_DELAY);
        /* Start frequency measurement of PILO for
         * 64 PILO clock counts with BLE ECO ALTHF(configured to 16MHz) as reference clock */
        (void) Cy_SysClk_StartClkMeasurementCounters(CY_SYSCLK_MEAS_CLK_PILO, LF_COUNT, CY_SYSCLK_MEAS_CLK_ALTHF);
        while ( true != Cy_SysClk_ClkMeasurementCountersDone() )
        {
            /* Wait for the measurement to complete */
        }
        /* Read the number of reference clock cycles for 64 PILO clock cycles */
        measuredCnt = (uint32_t)_FLD2VAL(SRSS_CLK_CAL_CNT2_CAL_COUNTER2, SRSS_CLK_CAL_CNT2);
        /* If the measured clock cycles are greater than expected 31250 cycles, retain the bitPos as 1 in FTRIM */
        if (measuredCnt > FREQ_REF)
        {
            trimVal |= ((uint32_t) 1U << (uint32_t) bitPos);
        }
        /* Repeat until this is done for all 10 bits of FTRIM */
        bitPos--;

    } while (bitPos >= 0);
    SRSS_CLK_PILO_CONFIG &= ~(SRSS_CLK_PILO_CONFIG_PILO_FFREQ_Msk);
    SRSS_CLK_PILO_CONFIG |= (trimVal);
#endif
}


void Cy_SysClk_PiloUpdateTrimStep(void)
{
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    (void)stepSize;
    CY_PRA_FUNCTION_CALL_VOID_VOID(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_CLK_FUNC_UPDATE_PILO_TRIM_STEP);
#else
    uint32_t iteration    = 0u;
    uint32_t fTrim        = 0u;
    uint32_t newFreq      = 0u;
    uint32_t oldFreq      = 0u;
    uint32_t initialFtrim = _FLD2VAL(SRSS_CLK_PILO_CONFIG_PILO_FFREQ, SRSS_CLK_PILO_CONFIG);
    uint32_t refClkFreq   = Cy_SysClk_AltHfGetFrequency();

    stepSize = 8U;

    (void) Cy_SysClk_StartClkMeasurementCounters(CY_SYSCLK_MEAS_CLK_PILO, REF_COUNT, CY_SYSCLK_MEAS_CLK_ALTHF);
    while ( true != Cy_SysClk_ClkMeasurementCountersDone() )
    {
        /* Wait for the measurement to complete */
    }

    oldFreq = Cy_SysClk_ClkMeasurementCountersGetFreq(false, refClkFreq);
    do
    {
        fTrim = _FLD2VAL(SRSS_CLK_PILO_CONFIG_PILO_FFREQ, SRSS_CLK_PILO_CONFIG);
        /* Update the fine trim value */
        CY_REG32_CLR_SET(SRSS_CLK_PILO_CONFIG, SRSS_CLK_PILO_CONFIG_PILO_FFREQ, fTrim + 1u);
        /* Wait for 2 ms after setting FTRIM */
        Cy_SysLib_DelayUs(TRIM_DELAY);
        (void) Cy_SysClk_StartClkMeasurementCounters(CY_SYSCLK_MEAS_CLK_PILO, REF_COUNT, CY_SYSCLK_MEAS_CLK_ALTHF);
        while ( true != Cy_SysClk_ClkMeasurementCountersDone() )
        {
            /* Wait for the measurement to complete */
        }
        newFreq = Cy_SysClk_ClkMeasurementCountersGetFreq(false, refClkFreq);
        stepSize += (newFreq - oldFreq);
        oldFreq = newFreq;
        iteration++;

    } while (iteration < STEP_SIZE_ITER);
    stepSize = (stepSize/STEP_SIZE_ITER);
    /* Restore the fine trim value */
    CY_REG32_CLR_SET(SRSS_CLK_PILO_CONFIG, SRSS_CLK_PILO_CONFIG_PILO_FFREQ, initialFtrim);
    /* Wait for 2 ms after setting FTRIM */
    Cy_SysLib_DelayUs(TRIM_DELAY);
#endif
}


/* ========================================================================== */
/* ======================    POWER MANAGEMENT SECTION    ==================== */
/* ========================================================================== */


/** \cond INTERNAL */
/* Timeout count for use in function Cy_SysClk_DeepSleepCallback() is sufficiently large for ~1 second */
#define TIMEOUT (1000000UL)
/** \endcond */

cy_en_syspm_status_t Cy_SysClk_DeepSleepCallback(cy_stc_syspm_callback_params_t * callbackParams, cy_en_syspm_callback_mode_t mode)
{

    /* Bitmapped paths with enabled FLL/PLL sourced by ECO */
    static uint16_t changedSourcePaths;
    static uint16_t pllAutoModes;

    cy_en_syspm_status_t retVal = CY_SYSPM_FAIL;

    (void)callbackParams; /* Suppress "not used" warning */
    (void)changedSourcePaths;
    (void)pllAutoModes;

    switch (mode)
    {
        case CY_SYSPM_CHECK_READY:
            /* Don't allow entry into Deep Sleep mode if currently measuring a frequency */
            if (!clkCounting)
            {
                /* Indicating that we can go into Deep Sleep.
                 * Prevent starting a new clock measurement until
                 * after we've come back from Deep Sleep.
                 */
                preventCounting = true;
                retVal = CY_SYSPM_SUCCESS;
            }
            break;

        case CY_SYSPM_CHECK_FAIL:
            /* Cancellation of going into Deep Sleep, therefore allow a new clock measurement */
            preventCounting = false;
            retVal = CY_SYSPM_SUCCESS;
            break;

        case CY_SYSPM_BEFORE_TRANSITION:
            {
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
                retVal = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_VOID(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_CLK_FUNC_DS_BEFORE_TRANSITION);
#else
                uint32_t fllpll; /* 0 = FLL, all other values = a PLL */

                /* Initialize the storage of changed paths */
                changedSourcePaths = 0U;
                pllAutoModes = 0U;

                /* For FLL and each PLL */
                for (fllpll = 0UL; fllpll <= CY_SRSS_NUM_PLL; fllpll++)
                {
                    /* If FLL or PLL is enabled */
                    if ((0UL == fllpll) ? Cy_SysClk_FllIsEnabled() : Cy_SysClk_PllIsEnabled(fllpll))
                    {
                        /* And the FLL/PLL has ECO as a source */
                        if (Cy_SysClk_ClkPathGetSource(fllpll) == CY_SYSCLK_CLKPATH_IN_ECO)
                        {
                            /* Bypass the FLL/PLL */
                            if (0UL == fllpll)
                            {
                                CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
                            }
                            else
                            {
                                if (((uint32_t)CY_SYSCLK_FLLPLL_OUTPUT_AUTO  == _FLD2VAL(SRSS_CLK_PLL_CONFIG_BYPASS_SEL, SRSS_CLK_PLL_CONFIG[fllpll - 1UL])) ||
                                    ((uint32_t)CY_SYSCLK_FLLPLL_OUTPUT_AUTO1 == _FLD2VAL(SRSS_CLK_PLL_CONFIG_BYPASS_SEL, SRSS_CLK_PLL_CONFIG[fllpll - 1UL])))
                                {
                                    pllAutoModes |= (uint16_t)(1UL << fllpll);
                                }

                                CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[fllpll - 1UL], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
                            }

                            /* Change this path source to IMO */
                            (void)Cy_SysClk_ClkPathSetSource(fllpll, CY_SYSCLK_CLKPATH_IN_IMO);

                            /* Store a record that this path source was changed from ECO */
                            changedSourcePaths |= (uint16_t)(1UL << fllpll);
                        }
                        else if (0UL == fllpll)
                        {
                            CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
                        }
                        else
                        {
                            /* Do nothing */
                        }
                    }
                }

                retVal = CY_SYSPM_SUCCESS;
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))  */
            }
            break;

        case CY_SYSPM_AFTER_TRANSITION:
            {
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
                retVal = (cy_en_syspm_status_t)CY_PRA_FUNCTION_CALL_RETURN_VOID(CY_PRA_MSG_TYPE_SECURE_ONLY, CY_PRA_CLK_FUNC_DS_AFTER_TRANSITION);
#else
                /* After return from Deep Sleep, for each FLL/PLL, if needed, restore the source to ECO.
                 * And block until the FLL/PLL has regained its frequency lock.
                 */
                uint32_t timeout = TIMEOUT;
                retVal = CY_SYSPM_TIMEOUT;

                if (0U != changedSourcePaths)
                {
                    /* If any FLL/PLL was sourced by the ECO, timeout wait for the ECO to become fully stabilized again */
                    while ((CY_SYSCLK_ECOSTAT_STABLE != Cy_SysClk_EcoGetStatus()) && (0UL != timeout))
                    {
                        timeout--;
                    }

                    if (0UL != timeout)
                    {
                        uint32_t fllpll; /* 0 = FLL, all other values = PLL */

                        for (fllpll = 0UL; fllpll <= CY_SRSS_NUM_PLL; fllpll++)
                        {
                            /* If there is a correspondent record about a changed clock source */
                            if (0U != (changedSourcePaths & (uint16_t)(1UL << fllpll)))
                            {
                                /* Change this path source back to ECO */
                                (void)Cy_SysClk_ClkPathSetSource(fllpll, CY_SYSCLK_CLKPATH_IN_ECO);

                                /* Timeout wait for FLL/PLL to regain lock.
                                 * Split FLL and PLL lock polling loops into two separate threads to minimize one polling loop duration.
                                 */
                                if (0UL == fllpll)
                                {
                                    while ((!Cy_SysClk_FllLocked()) && (0UL != timeout))
                                    {
                                        timeout--;
                                    }
                                }
                                else
                                {
                                    while ((!Cy_SysClk_PllLocked(fllpll)) && (0UL != timeout))
                                    {
                                        timeout--;
                                    }
                                }

                                if (0UL != timeout)
                                {
                                    /* Undo bypass the FLL/PLL */
                                    if (0UL == fllpll)
                                    {
                                        CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
                                    }
                                    else
                                    {
                                        if (0U != (pllAutoModes & (uint16_t)(1UL << fllpll)))
                                        {
                                            CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[fllpll - 1UL], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_AUTO);
                                        }
                                        else
                                        {
                                            CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[fllpll - 1UL], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
                                        }
                                    }

                                    retVal = CY_SYSPM_SUCCESS;
                                }
                            }
                        }
                    }
                }
                else if (Cy_SysClk_FllIsEnabled())
                {
                    /* Timeout wait for FLL to regain lock */
                    while ((!Cy_SysClk_FllLocked()) && (0UL != timeout))
                    {
                        timeout--;
                    }

                    if (0UL != timeout)
                    {
                        /* Undo bypass the FLL */
                        CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
                        retVal = CY_SYSPM_SUCCESS;
                    }
                }
                else
                {
                    retVal = CY_SYSPM_SUCCESS;
                }

                preventCounting = false; /* Allow clock measurement */
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
            }
            break;

        default: /* Unsupported mode, return CY_SYSPM_FAIL */
            break;
    }

    return (retVal);

}


/* ========================================================================== */
/* =========================    clkHf[n] SECTION    ========================= */
/* ========================================================================== */


uint32_t Cy_SysClk_ClkHfGetFrequency(uint32_t clkHf)
{
    /* variables holding intermediate clock frequencies, dividers and FLL/PLL settings */
    uint32_t pDiv = 1UL << (uint32_t)Cy_SysClk_ClkHfGetDivider(clkHf); /* root prescaler (1/2/4/8) */
    uint32_t path = (uint32_t) Cy_SysClk_ClkHfGetSource(clkHf); /* path input for root 0 (clkHf[0]) */
    uint32_t freq = Cy_SysClk_ClkPathGetFrequency(path);

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(freq, pDiv));
}


/* ========================================================================== */
/* =====================    clk_peripherals SECTION    ====================== */
/* ========================================================================== */


uint32_t Cy_SysClk_PeriphGetFrequency(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    uint32_t integer = 0UL;        /* Integer part of peripheral divider */
    uint32_t freq = Cy_SysClk_ClkPeriGetFrequency(); /* Get Peri frequency */

    CY_ASSERT_L1(((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < PERI_DIV_8_NR))    || \
                 ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < PERI_DIV_16_NR))   || \
                 ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < PERI_DIV_16_5_NR)) || \
                 ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < PERI_DIV_24_5_NR)));

    /* get the divider value for clk_peri to the selected peripheral clock */
    switch(dividerType)
    {
        case CY_SYSCLK_DIV_8_BIT:
        case CY_SYSCLK_DIV_16_BIT:
            integer = 1UL + Cy_SysClk_PeriphGetDivider(dividerType, dividerNum);
            freq = CY_SYSLIB_DIV_ROUND(freq, integer);
            break;

        case CY_SYSCLK_DIV_16_5_BIT:
        case CY_SYSCLK_DIV_24_5_BIT:
            {
                uint32_t locFrac;
                uint32_t locDiv;
                uint64_t locFreq = freq * 32ULL;
                Cy_SysClk_PeriphGetFracDivider(dividerType, dividerNum, &integer, &locFrac);
                /* For fractional dividers, the divider is (int + 1) + frac/32 */
                locDiv = ((1UL + integer) * 32UL) + locFrac;
                freq = (uint32_t) CY_SYSLIB_DIV_ROUND(locFreq, (uint64_t)locDiv);
            }
            break;

        default:
            /* Unknown divider */
            break;
    }

    return (freq);
}


uint32_t Cy_SysClk_ClkTimerGetFrequency(void)
{
    uint32_t freq = 0UL;

    if (Cy_SysClk_ClkTimerIsEnabled())
    {
        freq = Cy_SysClk_ClkHfGetFrequency(0UL);

        switch (Cy_SysClk_ClkTimerGetSource())
        {
            case CY_SYSCLK_CLKTIMER_IN_IMO:
                freq = CY_SYSCLK_IMO_FREQ;
                break;

            case CY_SYSCLK_CLKTIMER_IN_HF0_NODIV:
                break;

            case CY_SYSCLK_CLKTIMER_IN_HF0_DIV2:
                freq /= 2UL;
                break;

            case CY_SYSCLK_CLKTIMER_IN_HF0_DIV4:
                freq /= 4UL;
                break;

            case CY_SYSCLK_CLKTIMER_IN_HF0_DIV8:
                freq /= 8UL;
                break;

            default:
                freq = 0UL;
                break;
        }
    }

    /* Divide the input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(freq, 1UL + (uint32_t)Cy_SysClk_ClkTimerGetDivider()));
}


uint32_t Cy_SysClk_FllGetFrequency(void)
{
    uint32_t fDiv ;    /* FLL multiplier/feedback divider */
    uint32_t rDiv;    /* FLL reference divider */
    uint32_t oDiv;    /* FLL output divider */
    bool  enabled;    /* FLL enable status; n/a for direct */
    uint32_t freq = 0UL;    /* FLL Frequency */

    cy_stc_fll_manual_config_t fllCfg;
    Cy_SysClk_FllGetConfiguration(&fllCfg);
    enabled = (Cy_SysClk_FllIsEnabled()) && (CY_SYSCLK_FLLPLL_OUTPUT_INPUT != fllCfg.outputMode);
    fDiv = fllCfg.fllMult;
    rDiv = fllCfg.refDiv;
    oDiv = (fllCfg.enableOutputDiv) ? 2UL : 1UL;

    if (enabled && /* If FLL is enabled and not bypassed */
        (0UL != rDiv)) /* to avoid division by zero */
    {
        freq = Cy_SysClk_ClkPathMuxGetFrequency(0UL); /* FLL mapped always to path 0 */
        freq = (uint32_t)CY_SYSLIB_DIV_ROUND(((uint64_t)freq * (uint64_t)fDiv),
                                             ((uint64_t)rDiv * (uint64_t)oDiv));
    }

    return (freq);
}

uint32_t Cy_SysClk_PllGetFrequency(uint32_t clkPath)
{
    uint32_t fDiv = 0UL;    /* PLL multiplier/feedback divider */
    uint32_t rDiv = 0UL;    /* PLL reference divider */
    uint32_t oDiv = 0UL;    /* PLL output divider */
    bool  enabled = false;    /* PLL enable status; n/a for direct */
    uint32_t freq=0UL;    /* PLL Frequency */

    if((CY_SRSS_NUM_PLL > 0UL) && (clkPath > 0UL))
    {
        CY_ASSERT_L1(clkPath < CY_SRSS_NUM_CLKPATH);

        if (clkPath <= CY_SRSS_NUM_PLL)
        {
            cy_stc_pll_manual_config_t pllcfg;
            if (CY_SYSCLK_SUCCESS == Cy_SysClk_PllGetConfiguration(clkPath, &pllcfg))
            {
                enabled = (Cy_SysClk_PllIsEnabled(clkPath)) && (CY_SYSCLK_FLLPLL_OUTPUT_INPUT != pllcfg.outputMode);
                fDiv = pllcfg.feedbackDiv;
                rDiv = pllcfg.referenceDiv;
                oDiv = pllcfg.outputDiv;
            }

            if (enabled && /* If PLL is enabled and not bypassed */
            (0UL != rDiv) && (0UL != oDiv)) /* to avoid division by zero */
            {
                freq = Cy_SysClk_ClkPathMuxGetFrequency(clkPath);
                freq = (uint32_t)CY_SYSLIB_DIV_ROUND(((uint64_t)freq * (uint64_t)fDiv),
                                                     ((uint64_t)rDiv * (uint64_t)oDiv));
            }
        }
    }

    return (freq);
}

#if defined (CY_DEVICE_SECURE)
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 17.2');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.6');
#endif

#endif

/* [] END OF FILE */
