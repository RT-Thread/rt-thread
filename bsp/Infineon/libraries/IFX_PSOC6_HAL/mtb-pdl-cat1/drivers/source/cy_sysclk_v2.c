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

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS)

#include "cy_sysclk.h"
#include "cy_syslib.h"
#include "cy_syspm_btss.h"
#include <stdlib.h>

cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkSetDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType,
                                           uint32_t dividerNum, uint32_t dividerValue)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint8_t grpNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    if (dividerType == CY_SYSCLK_DIV_8_BIT)
    {
        if ((dividerNum < (PERI_DIV_8_NR(instNum, grpNum))) &&
            (dividerValue <= (PERI_DIV_8_CTL_INT8_DIV_Msk >> PERI_DIV_8_CTL_INT8_DIV_Pos)))
        {
            CY_REG32_CLR_SET(PERI_DIV_8_CTL(instNum, grpNum, dividerNum), PERI_DIV_8_CTL_INT8_DIV, dividerValue);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else if (dividerType == CY_SYSCLK_DIV_16_BIT)
    {
        if ((dividerNum < (PERI_DIV_16_NR(instNum, grpNum))) &&
            (dividerValue <= (PERI_DIV_16_CTL_INT16_DIV_Msk >> PERI_DIV_16_CTL_INT16_DIV_Pos)))
        {
            CY_REG32_CLR_SET(PERI_DIV_16_CTL(instNum, grpNum, dividerNum), PERI_DIV_16_CTL_INT16_DIV, dividerValue);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else
    { /* return bad parameter */
    }
    return (retVal);
}


uint32_t Cy_SysClk_PeriPclkGetDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    uint32_t retVal;
    uint8_t grpNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));
    CY_ASSERT_L1(dividerType <= CY_SYSCLK_DIV_16_BIT);

    if (dividerType == CY_SYSCLK_DIV_8_BIT)
    {
        CY_ASSERT_L1(dividerNum < PERI_DIV_8_NR(instNum, grpNum));
        retVal = _FLD2VAL(PERI_DIV_8_CTL_INT8_DIV, PERI_DIV_8_CTL(instNum, grpNum, dividerNum));
    }
    else
    { /* 16-bit divider */
        CY_ASSERT_L1(dividerNum < PERI_DIV_16_NR(instNum, grpNum));
        retVal = _FLD2VAL(PERI_DIV_16_CTL_INT16_DIV, PERI_DIV_16_CTL(instNum, grpNum, dividerNum));
    }
    return (retVal);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkSetFracDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                               uint32_t dividerIntValue, uint32_t dividerFracValue)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint8_t grpNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    if (dividerType == CY_SYSCLK_DIV_16_5_BIT)
    {
        if (((uint32_t)dividerNum < (PERI_DIV_16_5_NR(instNum, grpNum))) &&
            (dividerIntValue <= (PERI_DIV_16_5_CTL_INT16_DIV_Msk >> PERI_DIV_16_5_CTL_INT16_DIV_Pos)) &&
            (dividerFracValue <= (PERI_DIV_16_5_CTL_FRAC5_DIV_Msk >> PERI_DIV_16_5_CTL_FRAC5_DIV_Pos)))
        {
            CY_REG32_CLR_SET(PERI_DIV_16_5_CTL(instNum, grpNum, dividerNum), PERI_DIV_16_5_CTL_INT16_DIV, dividerIntValue);
            CY_REG32_CLR_SET(PERI_DIV_16_5_CTL(instNum, grpNum, dividerNum), PERI_DIV_16_5_CTL_FRAC5_DIV, dividerFracValue);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else if (dividerType == CY_SYSCLK_DIV_24_5_BIT)
    {
        if (((uint32_t)dividerNum < (PERI_DIV_24_5_NR(instNum, grpNum))) &&
            (dividerIntValue <= (PERI_DIV_24_5_CTL_INT24_DIV_Msk >> PERI_DIV_24_5_CTL_INT24_DIV_Pos)) &&
            (dividerFracValue <= (PERI_DIV_24_5_CTL_FRAC5_DIV_Msk >> PERI_DIV_24_5_CTL_FRAC5_DIV_Pos)))
        {
            CY_REG32_CLR_SET(PERI_DIV_24_5_CTL(instNum, grpNum, dividerNum), PERI_DIV_24_5_CTL_INT24_DIV, dividerIntValue);
            CY_REG32_CLR_SET(PERI_DIV_24_5_CTL(instNum, grpNum, dividerNum), PERI_DIV_24_5_CTL_FRAC5_DIV, dividerFracValue);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else
    { /* return bad parameter */
    }
    return (retVal);
}


void Cy_SysClk_PeriPclkGetFracDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                    uint32_t *dividerIntValue, uint32_t *dividerFracValue)
{
    uint8_t grpNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    CY_ASSERT_L1(((dividerType == CY_SYSCLK_DIV_16_5_BIT) || (dividerType == CY_SYSCLK_DIV_24_5_BIT)) && \
                 (dividerIntValue != NULL) && (dividerFracValue != NULL));

    if (dividerType == CY_SYSCLK_DIV_16_5_BIT)
    {
        CY_ASSERT_L1(dividerNum < PERI_DIV_16_5_NR(instNum, grpNum));
        *dividerIntValue  = _FLD2VAL(PERI_DIV_16_5_CTL_INT16_DIV, PERI_DIV_16_5_CTL(instNum, grpNum, dividerNum));
        *dividerFracValue = _FLD2VAL(PERI_DIV_16_5_CTL_FRAC5_DIV, PERI_DIV_16_5_CTL(instNum, grpNum, dividerNum));
    }
    else
    { /* 24.5-bit divider */
        CY_ASSERT_L1(dividerNum < PERI_DIV_24_5_NR(instNum, grpNum));
        *dividerIntValue  = _FLD2VAL(PERI_DIV_24_5_CTL_INT24_DIV, PERI_DIV_24_5_CTL(instNum, grpNum, dividerNum));
        *dividerFracValue = _FLD2VAL(PERI_DIV_24_5_CTL_FRAC5_DIV, PERI_DIV_24_5_CTL(instNum, grpNum, dividerNum));
    }
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkAssignDivider(en_clk_dst_t ipBlock,
                                              cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint8_t grpNum    = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);
    uint8_t periNum  = (uint8_t)((uint32_t)ipBlock & PERI_PCLK_PERI_NUM_Msk);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    if (CY_SYSCLK_DIV_24_5_BIT >= dividerType)
    {
        if (((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < (PERI_DIV_8_NR(instNum, grpNum))))    ||
            ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < (PERI_DIV_16_NR(instNum, grpNum))))   ||
            ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < (PERI_DIV_16_5_NR(instNum, grpNum)))) ||
            ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < (PERI_DIV_24_5_NR(instNum, grpNum)))))
        {
            PERI_CLOCK_CTL(instNum, grpNum, periNum) = _VAL2FLD(CY_PERI_CLOCK_CTL_TYPE_SEL, dividerType) |
                                      _VAL2FLD(CY_PERI_CLOCK_CTL_DIV_SEL, dividerNum);

            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    return (retVal);
}


uint32_t Cy_SysClk_PeriPclkGetAssignedDivider(en_clk_dst_t ipBlock)
{
    uint8_t grpNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);
    uint8_t periNum  = (uint8_t)((uint32_t)ipBlock & PERI_PCLK_PERI_NUM_Msk );

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    return (PERI_CLOCK_CTL(instNum, grpNum, periNum) & (CY_PERI_CLOCK_CTL_DIV_SEL_Msk | CY_PERI_CLOCK_CTL_TYPE_SEL_Msk));
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkEnableDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint8_t grpNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    if (dividerType <= CY_SYSCLK_DIV_24_5_BIT)
    {
        if (((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < (PERI_DIV_8_NR(instNum, grpNum))))    ||
            ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < (PERI_DIV_16_NR(instNum, grpNum))))   ||
            ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < (PERI_DIV_16_5_NR(instNum, grpNum)))) ||
            ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < (PERI_DIV_24_5_NR(instNum, grpNum)))))
        {
            /* specify the divider, make the reference = clk_peri, and enable the divider */
            PERI_DIV_CMD(instNum, grpNum) = PERI_DIV_CMD_ENABLE_Msk                         |
                           CY_PERI_DIV_CMD_PA_TYPE_SEL_Msk                 |
                           CY_PERI_DIV_CMD_PA_DIV_SEL_Msk                  |
                           _VAL2FLD(CY_PERI_DIV_CMD_TYPE_SEL, dividerType) |
                           _VAL2FLD(CY_PERI_DIV_CMD_DIV_SEL,  dividerNum);
            (void)PERI_DIV_CMD(instNum, grpNum); /* dummy read to handle buffered writes */
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    return (retVal);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkDisableDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint32_t grpNum = (((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    if (dividerType <= CY_SYSCLK_DIV_24_5_BIT)
    {
        if (((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < (PERI_DIV_8_NR(instNum, grpNum))))    ||
            ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < (PERI_DIV_16_NR(instNum, grpNum))))   ||
            ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < (PERI_DIV_16_5_NR(instNum, grpNum)))) ||
            ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < (PERI_DIV_24_5_NR(instNum, grpNum)))))
        {
            /* specify the divider and disable it */
            PERI_DIV_CMD(instNum, grpNum) = PERI_DIV_CMD_DISABLE_Msk          |
             _VAL2FLD(CY_PERI_DIV_CMD_TYPE_SEL, dividerType) |
             _VAL2FLD(CY_PERI_DIV_CMD_DIV_SEL,  dividerNum);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    return (retVal);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkEnablePhaseAlignDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                        cy_en_divider_types_t dividerTypePA, uint32_t dividerNumPA)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint32_t grpNum = (((uint32_t)ipBlock & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    if (dividerTypePA <= CY_SYSCLK_DIV_24_5_BIT)
    {
        if (((dividerTypePA == CY_SYSCLK_DIV_8_BIT)    && (dividerNumPA < (PERI_DIV_8_NR(instNum, grpNum))))    ||
            ((dividerTypePA == CY_SYSCLK_DIV_16_BIT)   && (dividerNumPA < (PERI_DIV_16_NR(instNum, grpNum))))   ||
            ((dividerTypePA == CY_SYSCLK_DIV_16_5_BIT) && (dividerNumPA < (PERI_DIV_16_5_NR(instNum, grpNum)))) ||
            ((dividerTypePA == CY_SYSCLK_DIV_24_5_BIT) && ((dividerNumPA < (PERI_DIV_24_5_NR(instNum, grpNum))) || (dividerNumPA == 63u))))
        {
            /* First, disable the divider that is to be phase-aligned.
               The other two parameters are checked in that function;
               if they're not valid, the divider is not disabled. */
            retVal = Cy_SysClk_PeriphDisableDivider(dividerType, dividerNum);
            if (retVal == CY_SYSCLK_SUCCESS)
            {
                /* Then, specify the reference divider, and the divider, and enable the divider */
                PERI_DIV_CMD(instNum, grpNum) = PERI_DIV_CMD_ENABLE_Msk             |
                 _VAL2FLD(CY_PERI_DIV_CMD_PA_TYPE_SEL, dividerTypePA) |
                 _VAL2FLD(CY_PERI_DIV_CMD_PA_DIV_SEL,  dividerNumPA)  |
                 _VAL2FLD(CY_PERI_DIV_CMD_TYPE_SEL, dividerType)   |
                 _VAL2FLD(CY_PERI_DIV_CMD_DIV_SEL,  dividerNum);
            }
        }
    }
    return (retVal);
}


bool Cy_SysClk_PeriPclkGetDividerEnabled(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    bool retVal = false;
    uint8_t grpNum = (uint8_t)((((uint32_t)ipBlock) & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos);
    uint8_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    CY_ASSERT_L1(((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < PERI_DIV_8_NR(instNum, grpNum)))    || \
                 ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < PERI_DIV_16_NR(instNum, grpNum)))   || \
                 ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < PERI_DIV_16_5_NR(instNum, grpNum))) || \
                 ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < PERI_DIV_24_5_NR(instNum, grpNum))));

    switch(dividerType)
    {
        case CY_SYSCLK_DIV_8_BIT:
            retVal = _FLD2BOOL(PERI_DIV_8_CTL_EN, PERI_DIV_8_CTL(instNum, grpNum, dividerNum));
            break;
        case CY_SYSCLK_DIV_16_BIT:
            retVal = _FLD2BOOL(PERI_DIV_16_CTL_EN, PERI_DIV_16_CTL(instNum, grpNum, dividerNum));
            break;
        case CY_SYSCLK_DIV_16_5_BIT:
            retVal = _FLD2BOOL(PERI_DIV_16_5_CTL_EN, PERI_DIV_16_5_CTL(instNum, grpNum, dividerNum));
            break;
        case CY_SYSCLK_DIV_24_5_BIT:
            retVal = _FLD2BOOL(PERI_DIV_24_5_CTL_EN, PERI_DIV_24_5_CTL(instNum, grpNum, dividerNum));
            break;
        default:
            /* Unknown Divider */
            break;
    }
    return (retVal);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphSetDivider(cy_en_divider_types_t dividerType,
                                           uint32_t dividerNum, uint32_t dividerValue)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    return Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum, dividerValue);
}


uint32_t Cy_SysClk_PeriphGetDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    return Cy_SysClk_PeriPclkGetDivider((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphSetFracDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                               uint32_t dividerIntValue, uint32_t dividerFracValue)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    return Cy_SysClk_PeriPclkSetFracDivider((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum, dividerIntValue, dividerFracValue);
}


void Cy_SysClk_PeriphGetFracDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                    uint32_t *dividerIntValue, uint32_t *dividerFracValue)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    Cy_SysClk_PeriPclkGetFracDivider((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum, dividerIntValue, dividerFracValue);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphAssignDivider(en_clk_dst_t ipBlock,
                                              cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    return Cy_SysClk_PeriPclkAssignDivider(ipBlock, dividerType, dividerNum);
}


uint32_t Cy_SysClk_PeriphGetAssignedDivider(en_clk_dst_t ipBlock)
{
    return Cy_SysClk_PeriPclkGetAssignedDivider(ipBlock);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphEnableDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    return Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphDisableDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    return Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum);
}


cy_en_sysclk_status_t
                Cy_SysClk_PeriphEnablePhaseAlignDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                        cy_en_divider_types_t dividerTypePA, uint32_t dividerNumPA)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    return Cy_SysClk_PeriPclkEnablePhaseAlignDivider((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum, dividerTypePA,  dividerNumPA);
}


bool Cy_SysClk_PeriphGetDividerEnabled(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    return Cy_SysClk_PeriPclkGetDividerEnabled((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum);
}


/* ========================================================================== */
/* =========================    clk_slow SECTION    ========================= */
/* ========================================================================== */

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)

uint32_t Cy_SysClk_ClkSlowGetFrequency(void)
{
    uint32_t locFreq = Cy_SysClk_ClkMemGetFrequency(); /* Get Mem frequency */
    uint32_t locDiv = 1UL + (uint32_t)Cy_SysClk_ClkSlowGetDivider(); /* Range (1-256) */

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(locFreq, locDiv));
}


void Cy_SysClk_ClkSlowSetDivider(uint8_t divider)
{
    CY_REG32_CLR_SET(CPUSS_SLOW_CLOCK_CTL, CPUSS_SLOW_CLOCK_CTL_INT_DIV, divider);
}


uint8_t Cy_SysClk_ClkSlowGetDivider(void)
{
    return ((uint8_t)_FLD2VAL(CPUSS_SLOW_CLOCK_CTL_INT_DIV, CPUSS_SLOW_CLOCK_CTL));
}

#endif /* defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

/* ========================================================================== */
/* =========================    clk_mem SECTION    ========================= */
/* ========================================================================== */

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)

uint32_t Cy_SysClk_ClkMemGetFrequency(void)
{
    uint32_t locFreq = Cy_SysClk_ClkHfGetFrequency(CY_SYSCLK_CLK_MEM_HF_PATH_NUM); /* Get HF frequency */
    uint32_t locDiv = 1UL + (uint32_t)Cy_SysClk_ClkMemGetDivider(); /* Range (1-256) */

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(locFreq, locDiv));
}


void Cy_SysClk_ClkMemSetDivider(uint8_t divider)
{
    CY_REG32_CLR_SET(CPUSS_MEM_CLOCK_CTL, CPUSS_MEM_CLOCK_CTL_INT_DIV, divider);
}


uint8_t Cy_SysClk_ClkMemGetDivider(void)
{
    return ((uint8_t)_FLD2VAL(CPUSS_MEM_CLOCK_CTL_INT_DIV, CPUSS_MEM_CLOCK_CTL));
}

#endif /* defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

/* ========================================================================== */
/* =========================    clk_pump SECTION    ========================= */
/* ========================================================================== */

#if defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
void Cy_SysClk_ClkPumpSetSource(cy_en_clkpump_in_sources_t source)
{
    CY_ASSERT_L3(source <= CY_SYSCLK_PUMP_IN_CLKPATH15);
    CY_REG32_CLR_SET(SRSS_CLK_SELECT, SRSS_CLK_SELECT_PUMP_SEL, source);
}

cy_en_clkpump_in_sources_t Cy_SysClk_ClkPumpGetSource(void)
{
    return ((cy_en_clkpump_in_sources_t)((uint32_t)_FLD2VAL(SRSS_CLK_SELECT_PUMP_SEL, SRSS_CLK_SELECT)));
}

void Cy_SysClk_ClkPumpSetDivider(cy_en_clkpump_divide_t divider)
{
    CY_ASSERT_L3(CY_SYSCLK_FLL_IS_DIVIDER_VALID(divider));
    CY_REG32_CLR_SET(SRSS_CLK_SELECT, SRSS_CLK_SELECT_PUMP_DIV, divider);
}

cy_en_clkpump_divide_t Cy_SysClk_ClkPumpGetDivider(void)
{
    return ((cy_en_clkpump_divide_t)((uint32_t)_FLD2VAL(SRSS_CLK_SELECT_PUMP_DIV, SRSS_CLK_SELECT)));
}

bool Cy_SysClk_ClkPumpIsEnabled(void)
{
    return (_FLD2BOOL(SRSS_CLK_SELECT_PUMP_ENABLE, SRSS_CLK_SELECT));
}

void Cy_SysClk_ClkPumpEnable(void)
{
    SRSS_CLK_SELECT |= SRSS_CLK_SELECT_PUMP_ENABLE_Msk;
}


void Cy_SysClk_ClkPumpDisable(void)
{
    SRSS_CLK_SELECT &= ~SRSS_CLK_SELECT_PUMP_ENABLE_Msk;
}

uint32_t Cy_SysClk_ClkPumpGetFrequency(void)
{
    /* Divide the input frequency down and return the result */
    return (Cy_SysClk_ClkPumpIsEnabled() ?
            (Cy_SysClk_ClkPathGetFrequency((uint32_t)Cy_SysClk_ClkPumpGetSource()) /
             (1UL << (uint32_t)Cy_SysClk_ClkPumpGetDivider())) : 0UL);
}
#endif /* defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) */
/* ========================================================================== */
/* ==========================    clk_bak SECTION    ========================= */
/* ========================================================================== */

void Cy_SysClk_ClkBakSetSource(cy_en_clkbak_in_sources_t source)
{
    CY_ASSERT_L3(source <= CY_SYSCLK_BAK_IN_PILO);

#if defined (CY_IP_MXS22SRSS)
    BACKUP_CTL = (_CLR_SET_FLD32U(BACKUP_CTL, SRSS_CLK_WCO_CONFIG_CLK_RTC_SEL, (uint32_t) source));
#else
    BACKUP_CTL = (_CLR_SET_FLD32U(BACKUP_CTL, BACKUP_CTL_CLK_SEL, (uint32_t) source));
#endif
}


cy_en_clkbak_in_sources_t Cy_SysClk_ClkBakGetSource(void)
{
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.8', 1, 'Intentional typecast to cy_en_clkbak_in_sources_t enum.');
#if defined (CY_IP_MXS22SRSS)
    return ((cy_en_clkbak_in_sources_t)_FLD2VAL(SRSS_CLK_WCO_CONFIG_CLK_RTC_SEL, BACKUP_CTL));
#else
    return ((cy_en_clkbak_in_sources_t)_FLD2VAL(BACKUP_CTL_CLK_SEL, BACKUP_CTL));
#endif
    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.8');
}

/* ========================================================================== */
/* ===========================    clkLf SECTION    ========================== */
/* ========================================================================== */

void Cy_SysClk_ClkLfSetSource(cy_en_clklf_in_sources_t source)
{
    CY_ASSERT_L3(source <= CY_SYSCLK_CLKLF_IN_MAX);
    CY_REG32_CLR_SET(SRSS_CLK_SELECT, SRSS_CLK_SELECT_LFCLK_SEL, source);
}


cy_en_clklf_in_sources_t Cy_SysClk_ClkLfGetSource(void)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_clklf_in_sources_t enum.');
    return ((cy_en_clklf_in_sources_t)(_FLD2VAL(SRSS_CLK_SELECT_LFCLK_SEL, SRSS_CLK_SELECT)));
}

/* ========================================================================== */
/* ========================    clk_peri SECTION    ========================== */
/* ========================================================================== */

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)

uint32_t Cy_SysClk_ClkPeriGetFrequency(void)
{
    uint32_t locFreq = Cy_SysClk_ClkHfGetFrequency(0UL); /* Get root frequency */
    uint32_t locDiv = 1UL + (uint32_t)Cy_SysClk_ClkPeriGetDivider(); /* peri prescaler (1-256) */

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(locFreq, locDiv));
}

void Cy_SysClk_ClkPeriSetDivider(uint8_t divider)
{
    CY_REG32_CLR_SET(CPUSS_PERI_CLOCK_CTL, CPUSS_PERI_CLOCK_CTL_INT_DIV, divider);
}

uint8_t Cy_SysClk_ClkPeriGetDivider(void)
{
    return ((uint8_t)_FLD2VAL(CPUSS_PERI_CLOCK_CTL_INT_DIV, CPUSS_PERI_CLOCK_CTL));
}

#endif /* defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

/* ========================================================================== */
/* ========================    PERI SECTION    ========================== */
/* ========================================================================== */
cy_en_sysclk_status_t Cy_SysClk_PeriGroupSetDivider(uint32_t groupNum, uint32_t divider)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint8_t instNum = (uint8_t)(((uint32_t)groupNum & PERI_GR_INST_NUM_Msk )>>PERI_GR_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);

    if (groupNum < ((uint32_t)CY_PERI_GROUP_NR))
    {
        if (divider <= (PERI_GR_CLOCK_CTL_INT8_DIV_Msk >> PERI_GR_CLOCK_CTL_INT8_DIV_Pos))
        {
            CY_REG32_CLR_SET(PERI_GR_CLOCK_CTL(instNum, groupNum), PERI_GR_CLOCK_CTL_INT8_DIV, divider);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }

    return retVal;
}


uint32_t Cy_SysClk_PeriGroupGetDivider(uint32_t groupNum)
{
    uint32_t retVal = 0UL;
    uint8_t instNum = (uint8_t)(((uint32_t)groupNum & PERI_GR_INST_NUM_Msk )>>PERI_GR_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);

    if (groupNum < ((uint32_t)CY_PERI_GROUP_NR))
    {
        return(_FLD2VAL(PERI_GR_CLOCK_CTL_INT8_DIV, PERI_GR_CLOCK_CTL(instNum, groupNum)));

    }

    return retVal;
}

cy_en_sysclk_status_t Cy_SysClk_PeriGroupSetSlaveCtl(uint32_t groupNum, cy_en_peri_grp_sl_ctl_num_t slaveCtl, uint32_t value)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint8_t instNum = (uint8_t)(((uint32_t)groupNum & PERI_GR_INST_NUM_Msk )>>PERI_GR_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L3(groupNum < CY_PERI_GROUP_NR);
    CY_ASSERT_L2(CY_SYSCLK_IS_SL_CTL_NUM_VALID(slaveCtl));

    switch(slaveCtl)
    {
        case CY_SYSCLK_PERI_GROUP_SL_CTL:
            PERI_GR_SL_CTL(instNum, groupNum) = value;
            retVal = CY_SYSCLK_SUCCESS;
            break;
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)  || defined (CY_IP_MXS22SRSS)
        case CY_SYSCLK_PERI_GROUP_SL_CTL2:
            PERI_GR_SL_CTL2(instNum, groupNum) = value;
            retVal = CY_SYSCLK_SUCCESS;
            break;
        case CY_SYSCLK_PERI_GROUP_SL_CTL3:
            /* Writes not allowed on SL_CTL3 */
            retVal = CY_SYSCLK_BAD_PARAM;
            break;
#endif
        default:
            retVal = CY_SYSCLK_BAD_PARAM;
            break;
    }

    return retVal;
}


uint32_t Cy_SysClk_PeriGroupGetSlaveCtl(uint32_t groupNum, cy_en_peri_grp_sl_ctl_num_t slaveCtl)
{
    uint32_t retVal = 0;
    uint8_t instNum = (uint8_t)(((uint32_t)groupNum & PERI_GR_INST_NUM_Msk )>>PERI_GR_INST_NUM_Pos);

    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L3(groupNum < CY_PERI_GROUP_NR);
    CY_ASSERT_L2(CY_SYSCLK_IS_SL_CTL_NUM_VALID(slaveCtl));

    switch(slaveCtl)
    {
        case CY_SYSCLK_PERI_GROUP_SL_CTL:
            retVal = PERI_GR_SL_CTL(instNum, groupNum);
            break;
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)
        case CY_SYSCLK_PERI_GROUP_SL_CTL2:
            retVal = PERI_GR_SL_CTL2(instNum, groupNum);
            break;
        case CY_SYSCLK_PERI_GROUP_SL_CTL3:
            retVal = PERI_GR_SL_CTL3(instNum, groupNum);
            break;
#endif
        default:
            retVal = (uint32_t)CY_SYSCLK_BAD_PARAM;
            break;
    }

    return retVal;
}

bool Cy_SysClk_IsPeriGroupSlaveCtlSet(uint32_t groupNum,cy_en_peri_grp_sl_ctl_num_t slaveCtl, uint32_t slaveMsk)
{
    bool retVal = false;
    uint8_t instNum = (uint8_t)(((uint32_t)groupNum & PERI_GR_INST_NUM_Msk )>>PERI_GR_INST_NUM_Pos);

    CY_ASSERT_L3(groupNum < CY_PERI_GROUP_NR);
    CY_ASSERT_L2(CY_SYSCLK_IS_SL_CTL_NUM_VALID(slaveCtl));

    switch(slaveCtl)
    {
        case CY_SYSCLK_PERI_GROUP_SL_CTL:
            if ((PERI_GR_SL_CTL(instNum, groupNum) & slaveMsk) != 0UL)
            {
                retVal = true;
            }
            break;
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)
        case CY_SYSCLK_PERI_GROUP_SL_CTL2:
            if ((PERI_GR_SL_CTL2(instNum, groupNum) & slaveMsk) != 0UL)
            {
                retVal = true;
            }
            break;
        case CY_SYSCLK_PERI_GROUP_SL_CTL3:
            if ((PERI_GR_SL_CTL3(instNum, groupNum) & slaveMsk) != 0UL)
            {
                retVal = true;
            }
            break;
#endif
        default:
            CY_ASSERT_L2(false);
            break;
    }

    return retVal;
}

/* ========================================================================== */
/* =========================    clk_fast SECTION    ========================= */
/* ========================================================================== */

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)

uint32_t Cy_SysClk_ClkFastSrcGetFrequency(uint32_t clkFastNum)
{
    uint32_t freq = Cy_SysClk_ClkHfGetFrequency(CY_SYSCLK_CLK_FAST_HF_NUM); /* Get root frequency */
    uint32_t integer = 0UL;        /* Integer part of peripheral divider */
    uint32_t locFrac;
    uint32_t locDiv;
    uint64_t locFreq = freq * 32ULL;

    Cy_SysClk_ClkFastSrcGetDivider(clkFastNum, &integer, &locFrac);
    /* For fractional dividers, the divider is (int + 1) + frac/32 */
    locDiv = ((1UL + integer) * 32UL) + locFrac;

    return (uint32_t) CY_SYSLIB_DIV_ROUND(locFreq, (uint64_t)locDiv);
}

void Cy_SysClk_ClkFastSrcSetDivider(uint32_t clkFastNum, uint8_t intDiv, uint8_t fracDiv)
{
    if(0UL == clkFastNum)
    {
        CY_REG32_CLR_SET(CPUSS_FAST_0_CLOCK_CTL, CPUSS_FAST_0_CLOCK_CTL_INT_DIV, intDiv);
        CY_REG32_CLR_SET(CPUSS_FAST_0_CLOCK_CTL, CPUSS_FAST_0_CLOCK_CTL_FRAC_DIV, fracDiv);
    }
    else
    {
        CY_REG32_CLR_SET(CPUSS_FAST_1_CLOCK_CTL, CPUSS_FAST_1_CLOCK_CTL_INT_DIV, intDiv);
        CY_REG32_CLR_SET(CPUSS_FAST_1_CLOCK_CTL, CPUSS_FAST_1_CLOCK_CTL_FRAC_DIV, fracDiv);
    }
}

void Cy_SysClk_ClkFastSrcGetDivider(uint32_t clkFastNum, uint32_t *dividerIntValue, uint32_t *dividerFracValue)
{
    if(0UL == clkFastNum)
    {
        *dividerIntValue = ((uint8_t)_FLD2VAL(CPUSS_FAST_0_CLOCK_CTL_INT_DIV, CPUSS_FAST_0_CLOCK_CTL));
        *dividerFracValue = ((uint8_t)_FLD2VAL(CPUSS_FAST_0_CLOCK_CTL_FRAC_DIV, CPUSS_FAST_0_CLOCK_CTL));
    }
    else
    {
        *dividerIntValue = ((uint8_t)_FLD2VAL(CPUSS_FAST_1_CLOCK_CTL_INT_DIV, CPUSS_FAST_1_CLOCK_CTL));
        *dividerFracValue = ((uint8_t)_FLD2VAL(CPUSS_FAST_1_CLOCK_CTL_FRAC_DIV, CPUSS_FAST_1_CLOCK_CTL));
    }
}

#endif /* defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

/* ========================================================================== */
/* =========================    clkHf[n] SECTION    ========================= */
/* ========================================================================== */

cy_en_sysclk_status_t Cy_SysClk_ClkHfEnable(uint32_t clkHf)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    uint32_t hfFreq = Cy_SysClk_ClkHfGetFrequency(clkHf);

    if(clkHf < CY_SRSS_NUM_HFROOT)
    {
        if (hfFreq <= CY_SYSCLK_HF_MAX_FREQ(clkHf))
        {
            SRSS_CLK_ROOT_SELECT[clkHf] |= SRSS_CLK_ROOT_SELECT_ENABLE_Msk;
            retVal = CY_SYSCLK_SUCCESS;
        }
        else
        {
            retVal = CY_SYSCLK_INVALID_STATE;
        }
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
        SRSS_CLK_ROOT_SELECT[clkHf] &= ~SRSS_CLK_ROOT_SELECT_ENABLE_Msk;
        retVal = CY_SYSCLK_SUCCESS;
    }
    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_ClkHfSetSource(uint32_t clkHf, cy_en_clkhf_in_sources_t source)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if ((clkHf < CY_SRSS_NUM_HFROOT) && (source <= CY_SYSCLK_CLKHF_IN_CLKPATH15))
    {
        CY_REG32_CLR_SET(SRSS_CLK_ROOT_SELECT[clkHf], SRSS_CLK_ROOT_SELECT_ROOT_MUX, source);
        retVal = CY_SYSCLK_SUCCESS;
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
        CY_REG32_CLR_SET(SRSS_CLK_ROOT_SELECT[clkHf], SRSS_CLK_ROOT_SELECT_ROOT_DIV, divider);
        retVal = CY_SYSCLK_SUCCESS;
    }
    return (retVal);
}


cy_en_clkhf_dividers_t Cy_SysClk_ClkHfGetDivider(uint32_t clkHf)
{
    CY_ASSERT_L1(clkHf < CY_SRSS_NUM_HFROOT);
    return ((cy_en_clkhf_dividers_t)(((uint32_t)_FLD2VAL(SRSS_CLK_ROOT_SELECT_ROOT_DIV, SRSS_CLK_ROOT_SELECT[clkHf]))));
}

uint32_t Cy_SysClk_ClkHfGetFrequency(uint32_t clkHf)
{
    /* variables holding intermediate clock frequencies, dividers and FLL/PLL settings */
    uint32_t pDiv = 1UL << (uint32_t)Cy_SysClk_ClkHfGetDivider(clkHf); /* root prescaler (1/2/4/8) */
    uint32_t path = (uint32_t) Cy_SysClk_ClkHfGetSource(clkHf); /* path input for root 0 (clkHf[0]) */
    uint32_t freq = Cy_SysClk_ClkPathGetFrequency(path);

    /* Divide the path input frequency down and return the result */
#if defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    if(Cy_SysClk_IsClkHfDirectSelEnabled(clkHf))
    {
        return (CY_SYSCLK_IMO_FREQ);
    }
    else
    {
        return (CY_SYSLIB_DIV_ROUND(freq, pDiv));
    }
#else
        return (CY_SYSLIB_DIV_ROUND(freq, pDiv));
#endif
}

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)

cy_en_sysclk_status_t Cy_SysClk_ClkHfDirectSel(uint32_t clkHf, bool enable)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if (clkHf < CY_SRSS_NUM_HFROOT)
    {
        CY_REG32_CLR_SET(SRSS_CLK_DIRECT_SELECT[clkHf], SRSS_CLK_DIRECT_SELECT_DIRECT_MUX, !(enable));
        retVal = CY_SYSCLK_SUCCESS;
    }
    return (retVal);
}

bool Cy_SysClk_IsClkHfDirectSelEnabled(uint32_t clkHf)
{
    bool retVal = false;
    if (clkHf < CY_SRSS_NUM_HFROOT)
    {
        return !(_FLD2BOOL(SRSS_CLK_DIRECT_SELECT_DIRECT_MUX, SRSS_CLK_DIRECT_SELECT[clkHf]));
    }
    return (retVal);
}
#elif (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
cy_en_sysclk_status_t Cy_SysClk_ClkHfDirectSel(uint32_t clkHf, bool enable)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if (clkHf < CY_SRSS_NUM_HFROOT)
    {
        CY_REG32_CLR_SET(SRSS_CLK_ROOT_SELECT[clkHf], SRSS_CLK_ROOT_SELECT_DIRECT_MUX, !(enable));
        retVal = CY_SYSCLK_SUCCESS;
    }
    return (retVal);
}

bool Cy_SysClk_IsClkHfDirectSelEnabled(uint32_t clkHf)
{
    bool retVal = false;
    if (clkHf < CY_SRSS_NUM_HFROOT)
    {
        return !(_FLD2BOOL(SRSS_CLK_ROOT_SELECT_DIRECT_MUX, SRSS_CLK_ROOT_SELECT[clkHf]));
    }
    return (retVal);
}

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) */

/* ========================================================================== */
/* ============================    MFO SECTION    ============================ */
/* ========================================================================== */


void Cy_SysClk_MfoEnable(bool deepSleepEnable)
{
#if (defined(CY_SRSS_MFO_PRESENT) && (CY_SRSS_MFO_PRESENT))
#if defined (CY_IP_MXS28SRSS)
    SRSS_CLK_MFO_CONFIG = SRSS_CLK_MFO_CONFIG_ENABLE_Msk;
#else
    SRSS_CLK_MFO_CONFIG = SRSS_CLK_MFO_CONFIG_ENABLE_Msk | (deepSleepEnable ? SRSS_CLK_MFO_CONFIG_DPSLP_ENABLE_Msk : 0UL);
#endif
#endif
    (void) deepSleepEnable;
}

bool Cy_SysClk_MfoIsEnabled(void)
{
#if (defined(CY_SRSS_MFO_PRESENT) && (CY_SRSS_MFO_PRESENT))
    return (0UL != (SRSS_CLK_MFO_CONFIG & SRSS_CLK_MFO_CONFIG_ENABLE_Msk));
#else
    return false;
#endif

}

void Cy_SysClk_MfoDisable(void)
{
#if (defined(CY_SRSS_MFO_PRESENT) && (CY_SRSS_MFO_PRESENT))
    SRSS_CLK_MFO_CONFIG = 0UL;
#endif
}


/* ========================================================================== */
/* ============================    CLK_MF SECTION    ============================ */
/* ========================================================================== */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined(CY_IP_MXS22SRSS)

void Cy_SysClk_ClkMfEnable(void)
{
    SRSS_CLK_MF_SELECT |= SRSS_CLK_MF_SELECT_ENABLE_Msk;
}


bool Cy_SysClk_ClkMfIsEnabled(void)
{
    return ((0UL != (SRSS_CLK_MF_SELECT & SRSS_CLK_MF_SELECT_ENABLE_Msk)));
}


void Cy_SysClk_ClkMfDisable(void)
{
    SRSS_CLK_MF_SELECT &= ~SRSS_CLK_MF_SELECT_ENABLE_Msk;
}


void Cy_SysClk_ClkMfSetDivider(uint32_t divider)
{
    if (CY_SYSCLK_IS_MF_DIVIDER_VALID(divider))
    {
        if (!Cy_SysClk_ClkMfIsEnabled())
        {
            CY_REG32_CLR_SET(SRSS_CLK_MF_SELECT, SRSS_CLK_MF_SELECT_MFCLK_DIV, divider - 1UL);
        }
    }
}


uint32_t Cy_SysClk_ClkMfGetDivider(void)
{
    return ((1UL + _FLD2VAL(SRSS_CLK_MF_SELECT_MFCLK_DIV, SRSS_CLK_MF_SELECT)));
}


uint32_t Cy_SysClk_ClkMfGetFrequency(void)
{
    uint32_t locFreq = (Cy_SysClk_MfoIsEnabled()) ? CY_SYSCLK_MFO_FREQ : 0UL; /* Get root frequency */
    uint32_t locDiv = Cy_SysClk_ClkMfGetDivider(); /* clkMf prescaler (1-256) */

    /* Divide the path input frequency down and return the result */
    return (CY_SYSLIB_DIV_ROUND(locFreq, locDiv));
}

void Cy_SysClk_ClkMfSetSource(cy_en_clkmf_in_sources_t source)
{
    CY_ASSERT_L3(CY_SYSCLK_IF_MF_SOURCE_VALID(source));
    CY_REG32_CLR_SET(SRSS_CLK_MF_SELECT, SRSS_CLK_MF_SELECT_MFCLK_SEL, source);
}


cy_en_clkmf_in_sources_t Cy_SysClk_ClkMfGetSource(void)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_clkmf_in_sources_t enum.');
    return ((cy_en_clkmf_in_sources_t)(_FLD2VAL(SRSS_CLK_MF_SELECT_MFCLK_SEL, SRSS_CLK_MF_SELECT)));
}

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) */

/* ========================================================================== */
/* ===========================    WCO SECTION    =========================== */
/* ========================================================================== */

cy_en_sysclk_status_t Cy_SysClk_WcoEnable(uint32_t timeoutus)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_TIMEOUT;

    /* Enable WCO */
#if defined (CY_IP_MXS28SRSS)
    BACKUP_WCO_CTL |= BACKUP_WCO_CTL_WCO_EN_Msk;
#elif defined (CY_IP_MXS22SRSS)
    BACKUP_CTL |= SRSS_CLK_WCO_CONFIG_WCO_EN_Msk;
#else
    BACKUP_CTL |= BACKUP_CTL_WCO_EN_Msk;
#endif

    /* now do the timeout wait for STATUS, bit WCO_OK */
    for (; (Cy_SysClk_WcoOkay() == false) && (0UL != timeoutus); timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    if (0UL != timeoutus)
    {
        retVal = CY_SYSCLK_SUCCESS;
    }

    return (retVal);
}

bool Cy_SysClk_WcoOkay(void)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    return (_FLD2BOOL(BACKUP_STATUS_WCO_OK, BACKUP_STATUS));
#elif defined (CY_IP_MXS22SRSS)
    return (_FLD2BOOL(SRSS_CLK_WCO_STATUS_WCO_OK, BACKUP_STATUS));
#else
    return (_FLD2BOOL(BACKUP_WCO_STATUS_WCO_OK, BACKUP_STATUS));
#endif
}

void Cy_SysClk_WcoDisable(void)
{
#if defined (CY_IP_MXS28SRSS)
    BACKUP_WCO_CTL &= (uint32_t)~BACKUP_WCO_CTL_WCO_EN_Msk;
#elif defined (CY_IP_MXS22SRSS)
    BACKUP_CTL &= (uint32_t)~SRSS_CLK_WCO_CONFIG_WCO_EN_Msk;
#else
    BACKUP_CTL &= (uint32_t)~BACKUP_CTL_WCO_EN_Msk;
#endif
}

#if defined (CY_IP_MXS28SRSS)
void Cy_SysClk_WcoGainControl(cy_en_wco_gain_ctrl_modes_t gmMode)
{
    CY_REG32_CLR_SET(BACKUP_WCO_CTL, BACKUP_WCO_CTL_GM, gmMode);
}
#endif /* defined (CY_IP_MXS28SRSS) */

void Cy_SysClk_WcoBypass(cy_en_wco_bypass_modes_t bypass)
{
#if defined (CY_IP_MXS28SRSS)
    CY_REG32_CLR_SET(BACKUP_WCO_CTL, BACKUP_WCO_CTL_WCO_BYP_EN, bypass);
#elif defined (CY_IP_MXS22SRSS)
    CY_REG32_CLR_SET(BACKUP_CTL, SRSS_CLK_WCO_CONFIG_WCO_BYPASS, bypass);
#else
    CY_REG32_CLR_SET(BACKUP_CTL, BACKUP_CTL_WCO_BYPASS, bypass);
#endif
}

/* ========================================================================== */
/* ===========================    PILO SECTION    =========================== */
/* ========================================================================== */

void Cy_SysClk_PiloEnable(void)
{
#if (defined (CY_SRSS_PILO_PRESENT) && (CY_SRSS_PILO_PRESENT))
    SRSS_CLK_PILO_CONFIG |= SRSS_CLK_PILO_CONFIG_PILO_EN_Msk; /* 1 = enable */
#endif
}
#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
void Cy_SysClk_PiloBackupEnable(void)
{
#if (defined (CY_SRSS_PILO_PRESENT) && (0U != CY_SRSS_PILO_PRESENT) && (!defined (CY_IP_MXS22SRSS)))
    SRSS_CLK_PILO_CONFIG |= SRSS_CLK_PILO_CONFIG_PILO_BACKUP_Msk; /* 1 = enable */
#endif
}

void Cy_SysClk_PiloBackupDisable(void)
{
#if (defined (CY_SRSS_PILO_PRESENT) && (CY_SRSS_PILO_PRESENT) && (!defined (CY_IP_MXS22SRSS)))
    /* Clear PILO_BACKUP bitfields. */
    SRSS_CLK_PILO_CONFIG &= (uint32_t)~(SRSS_CLK_PILO_CONFIG_PILO_BACKUP_Msk);
#endif
}
#endif

#if defined (CY_IP_MXS40SSRSS)
void Cy_SysClk_PiloTcscEnable(void)
{
#if (CY_SRSS_PILO_PRESENT)
    SRSS_CLK_PILO_CONFIG |= SRSS_CLK_PILO_CONFIG_PILO_TCSC_EN_Msk; /* 1 = enable */
#endif
}

void Cy_SysClk_PiloTcscDisable(void)
{
#if (CY_SRSS_PILO_PRESENT)
    /* Clear PILO_TCSC_EN( Second order temperature curvature correction.) bitfields. */
    SRSS_CLK_PILO_CONFIG &= (uint32_t)~(SRSS_CLK_PILO_CONFIG_PILO_TCSC_EN_Msk);
#endif
}

#endif /* defined (CY_IP_MXS40SSRSS) */

bool Cy_SysClk_PiloIsEnabled(void)
{
#if (defined (CY_SRSS_PILO_PRESENT) && (CY_SRSS_PILO_PRESENT))
    return (_FLD2BOOL(SRSS_CLK_PILO_CONFIG_PILO_EN, SRSS_CLK_PILO_CONFIG));
#else
    return false;
#endif
}

void Cy_SysClk_PiloDisable(void)
{
#if (defined (CY_SRSS_PILO_PRESENT) && (CY_SRSS_PILO_PRESENT))
    /* Clear PILO_EN */
    SRSS_CLK_PILO_CONFIG &= (uint32_t)~(SRSS_CLK_PILO_CONFIG_PILO_EN_Msk);
#endif
}

/* ========================================================================== */
/* ==========================    ALTHF SECTION    =========================== */
/* ========================================================================== */

uint32_t Cy_SysClk_AltHfGetFrequency(void)
{
    #if defined (CY_IP_MXS40BLE52SS)
        return Cy_BTSS_GetXtalOscFreq();
    #else
        return (0UL);
    #endif /* CY_IP_MXS40BLE52SS */
}

cy_en_sysclk_status_t Cy_SysClk_AltHfEnable(uint32_t timeoutus)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_TIMEOUT;

    CY_UNUSED_PARAMETER(timeoutus);
#if (CY_SRSS_ALTHF_PRESENT)
    /* Enable ALTHF */
    SRSS_CLK_ALTHF_CTL |= SRSS_CLK_ALTHF_CTL_ALTHF_ENABLE_Msk;

    /* now do the timeout for ALTHF to be enabled  */
    for (; (Cy_SysClk_IsAltHfEnabled() == false) && (0UL != timeoutus); timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    if (0UL != timeoutus)
    {
        retVal = CY_SYSCLK_SUCCESS;
    }
#endif

    return (retVal);
}

bool Cy_SysClk_IsAltHfEnabled(void)
{
#if (CY_SRSS_ALTHF_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_ALTHF_CTL_ALTHF_ENABLED, SRSS_CLK_ALTHF_CTL));
#else
    return false;
#endif
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

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))


/* Below ILO API's are valid for both ILO0 and ILO1 */
void Cy_SysClk_IloSrcEnable(uint32_t iloNum)
{
    CY_ASSERT_L1(iloNum < CY_SRSS_ILO_COUNT);

    if (0UL == iloNum)
    {
        SRSS_CLK_ILO0_CONFIG |= SRSS_CLK_ILO0_CONFIG_ENABLE_Msk;
    }
    else
    {
        SRSS_CLK_ILO1_CONFIG |= SRSS_CLK_ILO1_CONFIG_ENABLE_Msk;
    }
}

cy_en_sysclk_status_t Cy_SysClk_IloSrcDisable(uint32_t iloNum)
{
    CY_ASSERT_L1(iloNum < CY_SRSS_ILO_COUNT);
    cy_en_sysclk_status_t retVal = CY_SYSCLK_INVALID_STATE;

    if (0UL == iloNum)
    {
        if (!_FLD2BOOL(WDT_CTL_ENABLED, SRSS_WDT_CTL)) /* if disabled */
        {
            SRSS_CLK_ILO0_CONFIG &= ~SRSS_CLK_ILO0_CONFIG_ENABLE_Msk;
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else
    {
        SRSS_CLK_ILO1_CONFIG &= ~SRSS_CLK_ILO1_CONFIG_ENABLE_Msk;
        retVal = CY_SYSCLK_SUCCESS;
    }
    return (retVal);
}

bool Cy_SysClk_IloSrcIsEnabled(uint32_t iloNum)
{
    CY_ASSERT_L1(iloNum < CY_SRSS_ILO_COUNT);

    if (0UL == iloNum)
    {
        return (_FLD2BOOL(SRSS_CLK_ILO0_CONFIG_ENABLE, SRSS_CLK_ILO0_CONFIG));
    }
    else
    {
        return (_FLD2BOOL(SRSS_CLK_ILO1_CONFIG_ENABLE, SRSS_CLK_ILO1_CONFIG));
    }
}

void Cy_SysClk_IloSrcHibernateOn(uint32_t iloNum, bool on)
{
    if (0UL == iloNum)
    {
        CY_REG32_CLR_SET(SRSS_CLK_ILO0_CONFIG, SRSS_CLK_ILO0_CONFIG_ILO0_BACKUP, ((on) ? 1UL : 0UL));
    }
}

#else
void Cy_SysClk_IloEnable(void)
{
#if (CY_SRSS_ILO_PRESENT)
    SRSS_CLK_ILO_CONFIG |= SRSS_CLK_ILO_CONFIG_ENABLE_Msk;
#endif
}


cy_en_sysclk_status_t Cy_SysClk_IloDisable(void)
{
#if (CY_SRSS_ILO_PRESENT)
    cy_en_sysclk_status_t retVal = CY_SYSCLK_INVALID_STATE;
    if (!_FLD2BOOL(SRSS_WDT_CTL_WDT_EN, SRSS_WDT_CTL)) /* if disabled */
    {
        SRSS_CLK_ILO_CONFIG &= ~SRSS_CLK_ILO_CONFIG_ENABLE_Msk;
        retVal = CY_SYSCLK_SUCCESS;
    }
    return (retVal);
#else
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}

bool Cy_SysClk_IloIsEnabled(void)
{
#if (CY_SRSS_ILO_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_ILO_CONFIG_ENABLE, SRSS_CLK_ILO_CONFIG));
#else
    return false;
#endif
}

void Cy_SysClk_IloHibernateOn(bool on)
{
    CY_UNUSED_PARAMETER(on);
#if (CY_SRSS_ILO_PRESENT)
    CY_REG32_CLR_SET(SRSS_CLK_ILO_CONFIG, SRSS_CLK_ILO_CONFIG_ILO_BACKUP, ((on) ? 1UL : 0UL));
#endif
}

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) */


/* ========================================================================== */
/* =========================    EXTCLK SECTION    =========================== */
/* ========================================================================== */


    static uint32_t cySysClkExtFreq = 0UL;


#define CY_SYSCLK_EXTCLK_MAX_FREQ (100000000UL) /* 100 MHz */


void Cy_SysClk_ExtClkSetFrequency(uint32_t freq)
{
    if (freq <= CY_SYSCLK_EXTCLK_MAX_FREQ)
    {
        cySysClkExtFreq = freq;
    }
}

/*******************************************************************************
* Function Name: Cy_SysClk_ExtClkGetFrequency
****************************************************************************//**
*
* Returns the frequency of the External Clock Source (EXTCLK) from the
* internal storage.
*
* \return The frequency of the External Clock Source.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ExtClkSetFrequency
*
*******************************************************************************/
uint32_t Cy_SysClk_ExtClkGetFrequency(void)
{
    return (cySysClkExtFreq);
}

/* ========================================================================== */
/* ===========================    ECO SECTION    ============================ */
/* ========================================================================== */

#if (CY_SRSS_ECO_PRESENT)
static uint32_t ecoFreq = 0UL; /* Internal storage for ECO frequency user setting */
#endif

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS)

#define CY_SYSCLK_INVALID_TRIM_VALUE (0xFFFFFFFFUL)

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))

#define M_PI (3.1415927f)

/** \cond *********************************************************************
* Function Name: cy_sqrt
* Calculates square root.
* The input is 32-bit wide.
* The result is 16-bit wide.
*******************************************************************************/
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

/*******************************************************************************
* Function Name: Cy_SysClk_SelectEcoAtrim
****************************************************************************//**
*
*   In accordance with the table below, this function Outputs proper
*   value for ATRIM bits in register CLK_ECO_CONFIG2.
*   max amplitude (Vp) |   ATRIM value
*      0.50[V] <= Vp < 0.55[V]    |      0x04
*      0.55[V] <= Vp < 0.55[V]    |      0x05
*      0.60[V] <= Vp < 0.65[V]    |      0x06
*      0.65[V] <= Vp < 0.65[V]    |      0x07
*      0.70[V] <= Vp < 0.75[V]    |      0x08
*      0.75[V] <= Vp < 0.75[V]    |      0x09
*      0.80[V] <= Vp < 0.85[V]    |      0x0A
*      0.85[V] <= Vp < 0.75[V]    |      0x0B
*      0.90[V] <= Vp < 0.95[V]    |      0x0C
*      0.95[V] <= Vp < 1.00[V]    |      0x0D
*      1.00[V] <= Vp < 1.05[V]    |      0x0E
*      1.05[V] <= Vp < 1.10[V]    |      0x0F
*      1.10[V] <= Vp              |      0x00
*
*   \param maxAmplitude: Max amplitude (Vp) calculated by below formula.
*         Vpp = 1,000 * sqrt(drivelevel / 2 / esr) / 3.14 / freqMHz / cLoad
*
*   \return : value to be set to ATRIM.
*             It returns 0xFFFFFFFF, when there are no proper value.
*
*******************************************************************************/

__STATIC_INLINE uint32_t Cy_SysClk_SelectEcoAtrim(float32_t maxAmplitude)
{
    if(maxAmplitude < 0.50f)
    {
        return (CY_SYSCLK_INVALID_TRIM_VALUE);
    }

    if((0.50f <= maxAmplitude) && (maxAmplitude < 0.55f))
    {
        return(0x04UL);
    }
    else if(maxAmplitude < 0.60f)
    {
        return(0x05UL);
    }
    else if(maxAmplitude < 0.65f)
    {
        return(0x06UL);
    }
    else if(maxAmplitude < 0.70f)
    {
        return(0x07UL);
    }
    else if(maxAmplitude < 0.75f)
    {
        return(0x08UL);
    }
    else if(maxAmplitude < 0.80f)
    {
        return(0x09UL);
    }
    else if(maxAmplitude < 0.85f)
    {
        return(0x0AUL);
    }
    else if(maxAmplitude < 0.90f)
    {
        return(0x0BUL);
    }
    else if(maxAmplitude < 0.95f)
    {
        return(0x0CUL);
    }
    else if(maxAmplitude < 1.00f)
    {
        return(0x0DUL);
    }
    else if(maxAmplitude < 1.05f)
    {
        return(0x0EUL);
    }
    else if(maxAmplitude < 1.10f)
    {
        return(0x0FUL);
    }
    else if(1.1f <= maxAmplitude)
    {
        return(0x00UL);
    }
    else
    {
        // invalid input
        return(CY_SYSCLK_INVALID_TRIM_VALUE);
    }

}

/*******************************************************************************
* Function Name: Cy_SysClk_SelectEcoAGCEN
****************************************************************************//**
*
*   In accordance with the table below, this function Outputs proper
*   value for AGC_EN bits in register CLK_ECO_CONFIG.
*   max amplitude (Vp) |   ATRIM value
*      0.50[V] <= Vp < 1.10[V]    |      0x00
*      1.10[V] <= Vp              |      0x01
*
*   \param maxAmplitude: Max amplitude (Vp) calculated by below formula.
*         Vpp = 1,000 * sqrt(drivelevel / 2 / esr) / 3.14 / freqMHz / cLoad
*
*   \return : value to be set to AGC_EN.
*             It returns 0xFFFFFFFF, when there are no proper value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysClk_SelectEcoAGCEN(float32_t maxAmplitude)
{
    if((0.50f <= maxAmplitude) && (maxAmplitude < 1.10f))
    {
        return(0x01UL);
    }
    else if(1.10f <= maxAmplitude)
    {
        return(0x00UL);
    }
    else
    {
        return(CY_SYSCLK_INVALID_TRIM_VALUE);
    }
}

/*******************************************************************************
* Function Name: Cy_SysClk_SelectEcoWDtrim
****************************************************************************//**
*
*   In accordance with the table below, this function Outputs proper
*   value for WDTRIM bits in register CLK_ECO_CONFIG2.
*   max amplitude (Vp) |   WDTRIM value
*      0.5[V] <= Vp <  0.6[V]    |      0x02
*      0.6[V] <= Vp <  0.7[V]    |      0x03
*      0.7[V] <= Vp <  0.8[V]    |      0x04
*      0.8[V] <= Vp <  0.9[V]    |      0x05
*      0.9[V] <= Vp <  1.0[V]    |      0x06
*      1.0[V] <= Vp <  1.1[V]    |      0x07
*      1.1[V] <= Vp              |      0x07
*
*   \param amplitude: Max amplitude (Vp) calculated by below formula.
*         Vp = 1,000 * sqrt(drivelevel / 2 / esr) / 3.14 / freqMHz / cLoad
*
*   \return : value to be set to WDTRIM.
*             It returns CY_SYSCLK_INVALID_TRIM_VALUE, when there are no proper value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysClk_SelectEcoWDtrim(float32_t amplitude)
{
    if(amplitude < 0.50f)
    {
        return (CY_SYSCLK_INVALID_TRIM_VALUE);
    }

    if( (0.50f <= amplitude) && (amplitude < 0.60f))
    {
        return(0x02UL);
    }
    else if(amplitude < 0.7f)
    {
        return(0x03UL);
    }
    else if(amplitude < 0.8f)
    {
        return(0x04UL);
    }
    else if(amplitude < 0.9f)
    {
        return(0x05UL);
    }
    else if(amplitude < 1.0f)
    {
        return(0x06UL);
    }
    else if(amplitude < 1.1f)
    {
        return(0x07UL);
    }
    else if(1.1f <= amplitude)
    {
        return(0x07UL);
    }
    else
    {
        // invalid input
        return(CY_SYSCLK_INVALID_TRIM_VALUE);
    }
}

/*******************************************************************************
* Function Name: Cy_SysClk_SelectEcoGtrim
****************************************************************************//**
*
*   The range of gm value will be defined by GTRIM value as shown in below table.
*   We set the GTRIM value so that it is guaranteed for gm value to be more than gm_min
*
*    GTRIM value |  gm
*       0x00     |  0.0[mA/V] <= gm < 2.2[mA/V]
*       0x01     |  2.2[mA/V] <= gm < 4.4[mA/V]
*       0x02     |  4.4[mA/V] <= gm < 6.6[mA/V]
*       0x03     |  6.6[mA/V] <= gm < 8.8[mA/V]
*       0x04     |  8.8[mA/V] <= gm <11.0[mA/V]
*       0x05     | 11.0[mA/V] <= gm <13.2[mA/V]
*       0x06     | 13.2[mA/V] <= gm <15.4[mA/V]
*       0x07     | 15.4[mA/V] <= gm <17.6[mA/V]
*
*   \param gm_min: Minimum of gm (gm_min) calculated by below formula.
*   gm_min mA/V = 5 * 4 * 3.14 * 3.14 * freqMhz^2 * cLoad^2 * 4 * esr / 1,000,000,000
*
*   \return : value to be set to GTRIM.
*             It returns CY_SYSCLK_INVALID_TRIM_VALUE, when there are no proper value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysClk_SelectEcoGtrim(float32_t gm_min)
{
    if( (0.0f <= gm_min) && (gm_min < 2.2f))
    {
        return(0x00UL+1UL);
    }
    else if(gm_min < 4.4f)
    {
        return(0x01UL+1UL);
    }
    else if(gm_min < 6.6f)
    {
        return(0x02UL+1UL);
    }
    else if(gm_min < 8.8f)
    {
        return(0x03UL+1UL);
    }
    else if(gm_min < 11.0f)
    {
        return(0x04UL+1UL);
    }
    else if(gm_min < 13.2f)
    {
        return(0x05UL+1UL);
    }
    else if(gm_min < 15.4f)
    {
        return(0x06UL+1UL);
    }
    else if(gm_min < 17.6f)
    {
        // invalid input
        return(CY_SYSCLK_INVALID_TRIM_VALUE);
    }
    else
    {
        // invalid input
        return(CY_SYSCLK_INVALID_TRIM_VALUE);
    }
}

/*******************************************************************************
* Function Name: Cy_SysClk_SelectEcoRtrim
****************************************************************************//**
*
*   In accordance with the table below, this function Outputs proper
*   value for RTRIM bits in register CLK_ECO_CONFIG2.
*         Eco freq  (F)            |   RTRIM value
*                  F > 28.60[MHz]  |      0x00
*    28.60[MHz] >= F > 23.33[MHz]  |      0x01
*    23.33[MHz] >= F > 16.50[MHz]  |      0x02
*    16.50[MHz] >= F               |      0x03
*
*   \param freqMHz: Operating frequency of the crystal in MHz.
*
*   \return : value to be set to RTRIM.
*             It returns CY_SYSCLK_INVALID_TRIM_VALUE, when there are no proper value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysClk_SelectEcoRtrim(float32_t freqMHz)
{
    if(freqMHz > 28.6f)
    {
        return(0x00UL);
    }
    else if(freqMHz > 23.33f)
    {
        return(0x01UL);
    }
    else if(freqMHz > 16.5f)
    {
        return(0x02UL);
    }
    else if(freqMHz > 0.0f)
    {
        return(0x03UL);
    }
    else
    {
        // invalid input
        return(CY_SYSCLK_INVALID_TRIM_VALUE);
    }
}

/*******************************************************************************
* Function Name: Cy_SysClk_SelectEcoFtrim
****************************************************************************//**
*
*   In accordance with the table below, this function Outputs proper
*   value for FTRIM bits in register CLK_ECO_CONFIG2.
*
*   \return : value to be set to FTRIM.
*
*   \note: This function does not check the invalid input value.
*          It should be cared by caller program.
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysClk_SelectEcoFtrim(void)
{
    return(0x03UL);
}

cy_en_sysclk_status_t Cy_SysClk_EcoConfigure(uint32_t freq, uint32_t cSum, uint32_t esr, uint32_t driveLevel)
{
    uint32_t minRneg = (5UL * esr);

    /* Invalid state error if ECO is already enabled */
    if (0UL != (SRSS_CLK_ECO_CONFIG_ECO_EN_Msk & SRSS_CLK_ECO_CONFIG))
    {
        return(CY_SYSCLK_INVALID_STATE);
    }

    /* calculate intermediate values */
    float32_t freqMHz = (float32_t)freq / 1000000.0f;

    uint32_t maxAmpl = CY_SYSLIB_DIV_ROUND((159155UL * /* 5 * 100000 / PI */
           cy_sqrt(CY_SYSLIB_DIV_ROUND(2000000UL * driveLevel, esr))), /* Scaled by 2 */
                                       (CY_SYSLIB_DIV_ROUND(freq, 1000UL)/* KHz */ * cSum)); /* The result is scaled by 10^3 */

    float32_t maxAmplitude = (float32_t)maxAmpl/1000.0f;

    float32_t gm_min = (157.91367042f /*4 * M_PI * M_PI * 4*/ * (float32_t)minRneg * freqMHz * freqMHz * (float32_t)cSum * (float32_t)cSum) /
                             1000000000.0f;

    /* Get trim values according to calculated values */
    uint32_t atrim, agcen, wdtrim, gtrim, rtrim, ftrim;

    atrim  = Cy_SysClk_SelectEcoAtrim(maxAmplitude);
    if(atrim == CY_SYSCLK_INVALID_TRIM_VALUE)
    {
        return(CY_SYSCLK_BAD_PARAM);
    }

    agcen = Cy_SysClk_SelectEcoAGCEN(maxAmplitude);
    if(agcen == CY_SYSCLK_INVALID_TRIM_VALUE)
    {
        return(CY_SYSCLK_BAD_PARAM);
    }

    wdtrim = Cy_SysClk_SelectEcoWDtrim(maxAmplitude);
    if(wdtrim == CY_SYSCLK_INVALID_TRIM_VALUE)
    {
        return(CY_SYSCLK_BAD_PARAM);
    }

    gtrim  = Cy_SysClk_SelectEcoGtrim(gm_min);
    if(gtrim == CY_SYSCLK_INVALID_TRIM_VALUE)
    {
        return(CY_SYSCLK_BAD_PARAM);
    }

    rtrim  = Cy_SysClk_SelectEcoRtrim(freqMHz);
    if(rtrim == CY_SYSCLK_INVALID_TRIM_VALUE)
    {
        return(CY_SYSCLK_BAD_PARAM);
    }

    ftrim  = Cy_SysClk_SelectEcoFtrim();

    /* Update all fields of trim control register with one write, without changing the ITRIM field */
    SRSS_CLK_ECO_CONFIG2 =
        _VAL2FLD(SRSS_CLK_ECO_CONFIG2_WDTRIM, wdtrim)  |
        _VAL2FLD(SRSS_CLK_ECO_CONFIG2_ATRIM, atrim) |
        _VAL2FLD(SRSS_CLK_ECO_CONFIG2_FTRIM, ftrim)    |
        _VAL2FLD(SRSS_CLK_ECO_CONFIG2_RTRIM, rtrim)    |
        _VAL2FLD(SRSS_CLK_ECO_CONFIG2_GTRIM, gtrim);

    SRSS_CLK_ECO_CONFIG = _VAL2FLD(SRSS_CLK_ECO_CONFIG_AGC_EN, agcen);

    ecoFreq = freq;

    return(CY_SYSCLK_SUCCESS);
}

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) */

#if defined (CY_IP_MXS22SRSS)

#define CY_SYSCLK_CTRIM_TABLE_MAX_ENTRIES 33U

/*******************************************************************************
* Function Name: Cy_SysClk_SelectEcoCtrim
****************************************************************************//**
*
*    Get CTRIM value(CL- Crystal load cap configuration trim)
*
*    Calculations:
*    Target Cap = (2 * Load Capacitance) - (Board Trace Cap + Chip Pad Cap)
*    Pick CTRIM based on below table
*
*    CTRIM|  Condition
*    0x1  |  Target Cap <= 2.73(pF)
*    0x2  |  Target Cap <= 4.73(pF)
*    0x3  |  Target Cap <= 6.57(pF)
*    0x4  |  Target Cap <= 8.75(pF)
*    0x5  |  Target Cap <= 10.6(pF)
*    0x6  |  Target Cap <= 12.6(pF)
*    0x7  |  Target Cap <= 14.4(pF)
*    0x8  |  Target Cap <= 16.8(pF)
*    0x9  |  Target Cap <= 18.6(pF)
*    0xa  |  Target Cap <= 20.6(pF)
*    0xb  |  Target Cap <= 22.5(pF)
*    0xc  |  Target Cap <= 24.6(pF)
*    0xd  |  Target Cap <= 26.5(pF)
*    0xe  |  Target Cap <= 28.5(pF)
*    0xf  |  Target Cap <= 30.3(pF)
*    0x10 |  Target Cap <= 10.8(pF)
*    0x11 |  Target Cap <= 12.6(pF)
*    0x12 |  Target Cap <= 14.6(pF)
*    0x13 |  Target Cap <= 16.4(pF)
*    0x14 |  Target Cap <= 18.6(pF)
*    0x15 |  Target Cap <= 20.5(pF)
*    0x16 |  Target Cap <= 22.5(pF)
*    0x17 |  Target Cap <= 24.3(pF)
*    0x18 |  Target Cap <= 26.6(pF)
*    0x19 |  Target Cap <= 28.5(pF)
*    0x1a |  Target Cap <= 30.5(pF)
*    0x1b |  Target Cap <= 32.3(pF)
*    0x1c |  Target Cap <= 34.5(pF)
*    0x1d |  Target Cap <= 36.3(pF)
*    0x1e |  Target Cap <= 38.3(pF)
*    0x1f |  Target Cap <= 40.2(pF)
*    0x20 |  Target Cap <= 500(pF)
*
*   \param loadCap: Load Capacitance (In pF * 100)
*   \param boardTraceCap: Board Trace Capacitance (In pF * 100)
*   \param chipPadCap: Chip Pad Capacitance (In pF * 100)
*
*   \return : value to be set to CTRIM.
*             It returns CY_SYSCLK_INVALID_TRIM_VALUE, when there are no proper value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysClk_SelectEcoCtrim(uint32_t loadCap, uint32_t boardTraceCap, uint32_t chipPadCap)
{
    uint32_t targetCap, idx;
    uint32_t cTrimValue = CY_SYSCLK_INVALID_TRIM_VALUE;
    uint32_t simCapTable[] = {   /* Simulated Capacitance are multiplied by 100 to take care of decimal values */
        273,
        473,
        657,
        875,
        106,
        126,
        144,
        168,
        186,
        206,
        225,
        246,
        265,
        285,
        303,
        108,
        126,
        146,
        164,
        186,
        205,
        225,
        243,
        266,
        285,
        305,
        323,
        345,
        363,
        383,
        402,
        5000
    };

    /* All Capacitance are multiplied by 100 to take care of the decimal values */
    targetCap = (2 * loadCap) - (boardTraceCap + chipPadCap);

    for(idx = 0; idx < CY_SYSCLK_CTRIM_TABLE_MAX_ENTRIES; idx++)
    {
        if(targetCap <= simCapTable[idx])
        {
           break;
        }
    }
    if(idx != CY_SYSCLK_CTRIM_TABLE_MAX_ENTRIES)
    {
        cTrimValue = idx + 1U;
    }

    return cTrimValue;
}


/*******************************************************************************
* Function Name: Cy_SysClk_SelectEcoGtrim
****************************************************************************//**
*
*   The range of gm value will be defined by GTRIM value as shown in below table.
*   We set the GTRIM value so that it is guaranteed for gm value to be more than gm_min
*
*    GTRIM value |  gm
*       0x00     |  0.0[mA/V] <= gm < 2.2[mA/V]
*       0x01     |  2.2[mA/V] <= gm < 4.4[mA/V]
*       0x02     |  4.4[mA/V] <= gm < 6.6[mA/V]
*       0x03     |  6.6[mA/V] <= gm < 8.8[mA/V]
*       0x04     |  8.8[mA/V] <= gm <11.0[mA/V]
*       0x05     | 11.0[mA/V] <= gm <13.2[mA/V]
*       0x06     | 13.2[mA/V] <= gm <15.4[mA/V]
*       0x07     | 15.4[mA/V] <= gm <17.6[mA/V]
*
*   \param gm_min: Minimum of gm (gm_min) calculated by below formula.
*   gm_min mA/V = 5 * 4 * 3.14 * 3.14 * freqMhz^2 * cLoad^2 * 4 * esr / 1,000,000,000
*
*   \return : value to be set to GTRIM.
*             It returns CY_SYSCLK_INVALID_TRIM_VALUE, when there are no proper value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysClk_SelectEcoGtrim(float32_t gm_min)
{
    if( (0.0f <= gm_min) && (gm_min < 2.2f))
    {
        return(0x00UL+1UL);
    }
    else if(gm_min < 4.4f)
    {
        return(0x01UL+1UL);
    }
    else if(gm_min < 6.6f)
    {
        return(0x02UL+1UL);
    }
    else if(gm_min < 8.8f)
    {
        return(0x03UL+1UL);
    }
    else if(gm_min < 11.0f)
    {
        return(0x04UL+1UL);
    }
    else if(gm_min < 13.2f)
    {
        return(0x05UL+1UL);
    }
    else if(gm_min < 15.4f)
    {
        return(0x06UL+1UL);
    }
    else if(gm_min < 17.6f)
    {
        return(0x07UL+1UL);
    }
    else if(gm_min < 19.8f)
    {
        return(0x08UL+1UL);
    }
    else if(gm_min < 22.0f)
    {
        return(0x09UL+1UL);
    }
    else if(gm_min < 24.2f)
    {
        return(0xaUL+1UL);
    }
    else if(gm_min < 26.4f)
    {
        return(0xbUL+1UL);
    }
    else if(gm_min < 28.6f)
    {
        return(0xcUL+1UL);
    }
    else if(gm_min < 30.2f)
    {
        return(0x0dUL+1UL);
    }
    else if(gm_min < 32.4f)
    {
        return(0x0eUL+1UL);
    }
    else if(gm_min < 34.6f)
    {
        // invalid input
        return(CY_SYSCLK_INVALID_TRIM_VALUE);
    }
    else
    {
        // invalid input
        return(CY_SYSCLK_INVALID_TRIM_VALUE);
    }
}

cy_en_sysclk_status_t Cy_SysClk_EcoConfigure(uint32_t freq, uint32_t cSum, uint32_t esr, uint32_t driveLevel)
{
    uint32_t minRneg = (5UL * esr);

    CY_UNUSED_PARAMETER(driveLevel);

    /* Invalid state error if ECO is already enabled */
    if (0UL != (SRSS_CLK_ECO_CONFIG_ECO_EN_Msk & SRSS_CLK_ECO_CONFIG))
    {
        return(CY_SYSCLK_INVALID_STATE);
    }

    /* calculate intermediate values */
    float32_t freqMHz = (float32_t)freq / 1000000.0f;

    float32_t gm_min = (157.91367042f /*4 * M_PI * M_PI * 4*/ * (float32_t)minRneg * freqMHz * freqMHz * (float32_t)cSum * (float32_t)cSum) /
                             1000000000.0f;

    uint32_t gtrim, cTrim;

    gtrim  = Cy_SysClk_SelectEcoGtrim(gm_min);
    if(gtrim == CY_SYSCLK_INVALID_TRIM_VALUE)
    {
        return(CY_SYSCLK_BAD_PARAM);
    }

    cTrim  = Cy_SysClk_SelectEcoCtrim((cSum * 100), 0U, 0U);
    if(cTrim == CY_SYSCLK_INVALID_TRIM_VALUE)
    {
        return(CY_SYSCLK_BAD_PARAM);
    }

    SRSS_CLK_ECO_CONFIG2 =
        _VAL2FLD(SRSS_CLK_ECO_CONFIG2_ECO_TRIM_CL, cTrim) |
        _VAL2FLD(SRSS_CLK_ECO_CONFIG2_ECO_TRIM_GAIN, gtrim) |
        _VAL2FLD(SRSS_CLK_ECO_CONFIG2_ECO_CTRL_AMPDETEN, 0x0U);

    SRSS_CLK_TRIM_ECO_CTL =
        _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_ECO_CTRL_IBOOSTEN, 0x0U)  |
        _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_ECO_CTRL_CPBOOST, 0x0U) |
        _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_ECO_CTRL_WDBOOST, 0x0U)    |
        _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_ECO_TRIM_FBK, 0x0U)    |
        _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_ECO_TRIM_WDHYST, 0x0U)    |
        _VAL2FLD(SRSS_CLK_TRIM_ECO_CTL_ECO_TRIM_IREF, 0x8U);

    ecoFreq = freq;

    return(CY_SYSCLK_SUCCESS);

}


#endif


void Cy_SysClk_EcoDisable(void)
{
#if (CY_SRSS_ECO_PRESENT)
    SRSS_CLK_ECO_CONFIG &= ~SRSS_CLK_ECO_CONFIG_ECO_EN_Msk;
#endif
}


uint32_t Cy_SysClk_EcoGetStatus(void)
{
#if (CY_SRSS_ECO_PRESENT)
    uint32_t eco_status        = SRSS_CLK_ECO_STATUS;
    uint32_t eco_status_mask   = SRSS_CLK_ECO_STATUS_Msk;

    /* if ECO is not ready, just report the ECO_OK bit. Otherwise report 2 = ECO ready */
    return ((eco_status_mask == (eco_status_mask & eco_status)) ?
        CY_SYSCLK_ECOSTAT_STABLE : (SRSS_CLK_ECO_STATUS_Msk & eco_status));
#else
    return 0;
#endif
}


cy_en_sysclk_status_t Cy_SysClk_EcoEnable(uint32_t timeoutus)
{
#if (CY_SRSS_ECO_PRESENT)
    cy_en_sysclk_status_t retVal = CY_SYSCLK_INVALID_STATE;
    bool zeroTimeout = (0UL == timeoutus);

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

    return (retVal);

#else
    (void) timeoutus;
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}

uint32_t Cy_SysClk_EcoGetFrequency(void)
{
#if (CY_SRSS_ECO_PRESENT)
    return ((CY_SYSCLK_ECOSTAT_STABLE == Cy_SysClk_EcoGetStatus()) ? ecoFreq : 0UL);
#else
    return 0;
#endif
}

cy_en_sysclk_status_t Cy_SysClk_EcoPrescaleConfigure(uint32_t enable, uint32_t int_div, uint32_t frac_div)
{
    (void) enable;
#if (CY_SRSS_ECO_PRESENT)
    cy_en_sysclk_status_t retVal = CY_SYSCLK_INVALID_STATE;

    if(0UL != enable) {
        /* Invalid state error if CO_DIV_ENABLED is already enabled */
        if (0UL == (SRSS_CLK_ECO_PRESCALE_ECO_DIV_ENABLED_Msk & SRSS_CLK_ECO_PRESCALE))
        {
            SRSS_CLK_ECO_PRESCALE |= (_VAL2FLD(SRSS_CLK_ECO_PRESCALE_ECO_INT_DIV, int_div) | \
                                      _VAL2FLD(SRSS_CLK_ECO_PRESCALE_ECO_FRAC_DIV, frac_div));

            SRSS_CLK_ECO_CONFIG |= SRSS_CLK_ECO_CONFIG_ECO_DIV_ENABLE_Msk;

            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    else {
        /* Invalid state error if CO_DIV_ENABLED is already disabled */
        if (1UL == (SRSS_CLK_ECO_PRESCALE_ECO_DIV_ENABLED_Msk & SRSS_CLK_ECO_PRESCALE))
        {
            SRSS_CLK_ECO_CONFIG |= (SRSS_CLK_ECO_CONFIG_ECO_DIV_DISABLE_Msk);
            retVal = CY_SYSCLK_SUCCESS;
        }
    }
    return retVal;
#else
    (void) frac_div;
    (void) int_div;

    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}


bool Cy_SysClk_EcoPrescaleIsEnabled(void)
{
#if (CY_SRSS_ECO_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_ECO_PRESCALE_ECO_DIV_ENABLED, SRSS_CLK_ECO_PRESCALE));
#else
    return false;
#endif
}

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS) */


#if defined (CY_IP_MXS28SRSS)
cy_en_sysclk_status_t Cy_SysClk_EcoBleControl(cy_en_eco_for_ble_t control, uint32_t timeoutus)
{
#if (CY_SRSS_ECO_PRESENT)
    cy_en_sysclk_status_t retVal = CY_SYSCLK_INVALID_STATE;
    bool zeroTimeout = (0UL == timeoutus);

    CY_ASSERT_L1(control < sizeof(cy_en_eco_for_ble_t));

    /* Set ECO for BLE with control value */
    SRSS_CLK_ECO_CONFIG |= (control << SRSS_CLK_ECO_CONFIG_ECO_BLE_EN_Pos);

    /* Wait for CY_SYSCLK_ECOSTAT_STABLE */
    for (; (CY_SYSCLK_ECOSTAT_BLE_ENABLED != Cy_SysClk_EcoBleGetStatus()) && (0UL != timeoutus); timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    retVal = (zeroTimeout || (0UL != timeoutus)) ? CY_SYSCLK_SUCCESS : CY_SYSCLK_TIMEOUT;

    return (retVal);
#else
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}

#endif /* defined (CY_IP_MXS28SRSS) */

#if defined (CY_IP_MXS28SRSS)

uint32_t Cy_SysClk_EcoBleGetStatus(void)
{
#if defined (CY_IP_MXS28SRSS)
#if (CY_SRSS_ECO_PRESENT)
    /* if ECO for BLE is Enabled, report 1. Otherwise report 0 */
    return ((SRSS_CLK_ECO_STATUS_ECO_BLE_ENABLED_Msk == (SRSS_CLK_ECO_STATUS_ECO_BLE_ENABLED_Msk & SRSS_CLK_ECO_STATUS)) ?
      CY_SYSCLK_ECOSTAT_BLE_ENABLED : CY_SYSCLK_ECOSTAT_BLE_DISABLED);
#else
    return 0;
#endif
#else
    return 0;
#endif

}

#endif /* defined (CY_IP_MXS28SRSS) */

/* ========================================================================== */
/* ===========================    IHO SECTION    ============================ */
/* ========================================================================== */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
bool Cy_SysClk_IhoIsEnabled(void)
{
#if (CY_SRSS_IHO_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_IHO_CONFIG_ENABLE, SRSS_CLK_IHO_CONFIG));
#else
    return false;
#endif
}

void Cy_SysClk_IhoDisable(void)
{
#if (CY_SRSS_IHO_PRESENT)
    SRSS_CLK_IHO_CONFIG &= ~SRSS_CLK_IHO_CONFIG_ENABLE_Msk;
#endif
}

void Cy_SysClk_IhoEnable(void)
{
#if (CY_SRSS_IHO_PRESENT)
    SRSS_CLK_IHO_CONFIG |= SRSS_CLK_IHO_CONFIG_ENABLE_Msk;
#endif
}

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) */

#if defined (CY_IP_MXS22SRSS)
void Cy_SysClk_IhoDeepsleepEnable(void)
{
#if (CY_SRSS_IHO_PRESENT)
    SRSS_CLK_IHO_CONFIG |= SRSS_CLK_IHO_CONFIG_DPSLP_ENABLE_Msk;
#endif
}

bool Cy_SysClk_IhoIsDeepsleepEnabled(void)
{
#if (CY_SRSS_IHO_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_IHO_CONFIG_DPSLP_ENABLE, SRSS_CLK_IHO_CONFIG));
#else
    return false;
#endif
}

void Cy_SysClk_IhoDeepsleepDisable(void)
{
#if (CY_SRSS_IHO_PRESENT)
    SRSS_CLK_IHO_CONFIG &= ~SRSS_CLK_IHO_CONFIG_DPSLP_ENABLE_Msk;
#endif
}

void Cy_SysClk_IhoSetTrim(uint32_t trimVal)
{
#if (CY_SRSS_IHO_PRESENT)
    CY_REG32_CLR_SET(SRSS_CLK_IHO_CONFIG, SRSS_CLK_IHO_CONFIG_IHO_TRIM_FREQ, trimVal);
#endif
}

uint32_t Cy_SysClk_IhoGetTrim(void)
{
#if (CY_SRSS_IHO_PRESENT)
    return (_FLD2VAL(SRSS_CLK_IHO_CONFIG_IHO_TRIM_FREQ, SRSS_CLK_IHO_CONFIG));
#else
    return 0U;
#endif
}


#endif /* defined (CY_IP_MXS22SRSS) */


/* ========================================================================== */
/* ===========================    IMO SECTION    ============================ */
/* ========================================================================== */
#if defined (CY_IP_MXS22SRSS)

void Cy_SysClk_ImoEnable(void)
{
#if (CY_SRSS_IMO_PRESENT)
    SRSS_CLK_IMO_CONFIG |= SRSS_CLK_IMO_CONFIG_ENABLE_Msk;
#endif
}

void Cy_SysClk_ImoDisable(void)
{
#if (CY_SRSS_IMO_PRESENT)
    SRSS_CLK_IMO_CONFIG &= ~SRSS_CLK_IMO_CONFIG_ENABLE_Msk;
#endif
}

bool Cy_SysClk_ImoIsEnabled(void)
{
#if (CY_SRSS_IMO_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_IMO_CONFIG_ENABLE, SRSS_CLK_IMO_CONFIG));
#else
    return false;
#endif
}

void Cy_SysClk_ImoDeepsleepEnable(void)
{
#if (CY_SRSS_IMO_PRESENT)
    SRSS_CLK_IMO_CONFIG |= SRSS_CLK_IMO_CONFIG_DPSLP_ENABLE_Msk;
#endif
}

bool Cy_SysClk_ImoIsDeepsleepEnabled(void)
{
#if (CY_SRSS_IMO_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_IMO_CONFIG_DPSLP_ENABLE, SRSS_CLK_IMO_CONFIG));
#else
    return false;
#endif
}

void Cy_SysClk_ImoDeepsleepDisable(void)
{
#if (CY_SRSS_IMO_PRESENT)
    SRSS_CLK_IMO_CONFIG &= ~SRSS_CLK_IMO_CONFIG_DPSLP_ENABLE_Msk;
#endif
}
#endif /* defined (CY_IP_MXS22SRSS) */

/* ========================================================================== */
/* ====================    INPUT MULTIPLEXER SECTION    ===================== */
/* ========================================================================== */


cy_en_sysclk_status_t Cy_SysClk_ClkPathSetSource(uint32_t clkPath, cy_en_clkpath_in_sources_t source)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    if ((clkPath < CY_SRSS_NUM_CLKPATH) &&
        ((source <= CY_SYSCLK_CLKPATH_IN_IHO) ||
         ((CY_SYSCLK_CLKPATH_IN_DSI <= source) && (source <= CY_SYSCLK_CLKPATH_IN_ILO1))))
    {
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
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
            freq = Cy_SysClk_EcoGetFrequency();
#endif
            break;

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)

        case CY_SYSCLK_CLKPATH_IN_ALTHF:
            freq = Cy_SysClk_AltHfGetFrequency();
            break;

        case CY_SYSCLK_CLKPATH_IN_PILO:
            freq = (0UL != (SRSS_CLK_PILO_CONFIG & SRSS_CLK_PILO_CONFIG_PILO_EN_Msk)) ? CY_SYSCLK_PILO_FREQ : 0UL;
            break;

        case CY_SYSCLK_CLKPATH_IN_ALTLF:
            freq = Cy_SysClk_AltLfGetFrequency();
            break;
#endif

#if defined (CY_IP_MXS40SSRSS)
        case CY_SYSCLK_CLKPATH_IN_IHO:
            freq = (Cy_SysClk_IhoIsEnabled()) ? CY_SYSCLK_IHO_FREQ : 0UL;
            break;
#endif

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
        case CY_SYSCLK_CLKPATH_IN_ILO0:
#else
        case CY_SYSCLK_CLKPATH_IN_ILO:
#endif
            freq = (0UL != (SRSS_CLK_ILO_CONFIG & SRSS_CLK_ILO_CONFIG_ENABLE_Msk)) ? CY_SYSCLK_ILO_FREQ : 0UL;
            break;

        case CY_SYSCLK_CLKPATH_IN_WCO:
            freq = (Cy_SysClk_WcoOkay()) ? CY_SYSCLK_WCO_FREQ : 0UL;
            break;

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
        case CY_SYSCLK_CLKPATH_IN_ILO1:
            freq = (0UL != (SRSS_CLK_ILO_CONFIG & SRSS_CLK_ILO_CONFIG_ENABLE_Msk)) ? CY_SYSCLK_ILO_FREQ : 0UL;
            break;
#endif

        default:
            /* Don't know the frequency of dsi_out, leave freq = 0UL */
            break;
    }

    return (freq);
}

/*******************************************************************************
* Function Name: Cy_SysClk_ClkPathGetFrequency
****************************************************************************//**
*
* Returns the output frequency of the clock path mux.
*
* \return The output frequency of the path mux.
*
* \note If the return value equals zero, that means either:
* - the selected path mux source signal frequency is unknown (e.g. dsi_out, etc.) or
* - the selected path mux source is not configured/enabled/stable (e.g. ECO, EXTCLK, etc.).
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllEnable
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkPathGetFrequency(uint32_t clkPath)
{
    CY_ASSERT_L1(clkPath < CY_SRSS_NUM_CLKPATH);

    uint32_t freq = Cy_SysClk_ClkPathMuxGetFrequency(clkPath);
    uint32_t fDiv = 1UL;    /* FLL/PLL multiplier/feedback divider */
    uint32_t rDiv = 1UL;    /* FLL/PLL reference divider */
    uint32_t oDiv = 1UL;    /* FLL/PLL output divider */
    bool  enabled = false;  /* FLL or PLL enable status; n/a for direct */
#if CY_SRSS_PLL400M_PRESENT
    uint32_t fracDiv = 1UL;    /* PLL fractional divider */
    bool     fracEn  = false;  /* PLL fractional divider enable*/
#endif

    if (clkPath == (uint32_t)CY_SYSCLK_CLKHF_IN_CLKPATH0) /* FLL? (always path 0) */
    {
        cy_stc_fll_manual_config_t fllCfg = {0UL,0U,CY_SYSCLK_FLL_CCO_RANGE0,false,0U,0U,0U,0U,CY_SYSCLK_FLLPLL_OUTPUT_AUTO,0U};
        Cy_SysClk_FllGetConfiguration(&fllCfg);
        enabled = (Cy_SysClk_FllIsEnabled()) && (CY_SYSCLK_FLLPLL_OUTPUT_INPUT != fllCfg.outputMode);
        fDiv = fllCfg.fllMult;
        rDiv = fllCfg.refDiv;
        oDiv = (fllCfg.enableOutputDiv) ? 2UL : 1UL;
    }

#if (CY_SRSS_PLL_PRESENT) || (CY_SRSS_PLL400M_PRESENT)
    else if (clkPath <= (CY_SRSS_NUM_PLL)) /* PLL? (always path 1...N)*/
    {
#if CY_SRSS_PLL400M_PRESENT
        cy_stc_pll_manual_config_t pllcfg = {0U,0U,0U,false,CY_SYSCLK_FLLPLL_OUTPUT_AUTO, 0, false, false, 0 , 0 , false};
#else
        cy_stc_pll_manual_config_t pllcfg = {0U,0U,0U,false,CY_SYSCLK_FLLPLL_OUTPUT_AUTO};
#endif
        (void)Cy_SysClk_PllGetConfiguration(clkPath, &pllcfg);
        enabled = (Cy_SysClk_PllIsEnabled(clkPath)) && (CY_SYSCLK_FLLPLL_OUTPUT_INPUT != pllcfg.outputMode);
        fDiv = pllcfg.feedbackDiv;
        rDiv = pllcfg.referenceDiv;
        oDiv = pllcfg.outputDiv;
#if CY_SRSS_PLL400M_PRESENT
        fracEn  = pllcfg.fracEn;
        fracDiv = pllcfg.fracDiv;
#endif
    }
#endif /* CY_SRSS_PLL_PRESENT */

    else
    {
        /* Do nothing with the path mux frequency */
    }

    if (enabled && /* If FLL or PLL is enabled and not bypassed */
        (0UL != rDiv)) /* to avoid division by zero */
    {
#if CY_SRSS_PLL400M_PRESENT
        if(fracEn)
        {
            freq = (uint32_t)((((uint64_t)freq * (((uint64_t)fDiv << SRSS_PLL400M_FRAC_BIT_COUNT) + (uint64_t)fracDiv)) / ((uint64_t)rDiv * (uint64_t)oDiv)) >> SRSS_PLL400M_FRAC_BIT_COUNT);
        }
        else
#endif
        {
            freq = (uint32_t)CY_SYSLIB_DIV_ROUND(((uint64_t)freq * (uint64_t)fDiv),
                                                 ((uint64_t)rDiv * (uint64_t)oDiv));
        }
    }
    return (freq);
}

/* ========================================================================== */
/* ===========================    FLL SECTION    ============================ */
/* ========================================================================== */

/* min and max FLL output frequencies, in Hz */
#define  CY_SYSCLK_FLL_MIN_CCO_OUTPUT_FREQ (48000000UL)
#define  CY_SYSCLK_FLL_MIN_OUTPUT_FREQ     (CY_SYSCLK_FLL_MIN_CCO_OUTPUT_FREQ / 2U)

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
#if (CY_SRSS_FLL_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_FLL_CONFIG_FLL_ENABLE, SRSS_CLK_FLL_CONFIG));
#else
    return false;
#endif
}


bool Cy_SysClk_FllLocked(void)
{
#if (CY_SRSS_FLL_PRESENT)
    return (_FLD2BOOL(SRSS_CLK_FLL_STATUS_LOCKED, SRSS_CLK_FLL_STATUS));
#else
    return false;
#endif
}

cy_en_sysclk_status_t Cy_SysClk_FllDisable(void)
{
#if (CY_SRSS_FLL_PRESENT)
    uint32_t timeoutus = CY_SYSCLK_FLL_DISABLE_TIMEOUT;
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;


    CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);

    /* Wait until BYPASS bits are changed with a timeout */
    for (; (((uint32_t)CY_SYSCLK_FLLPLL_OUTPUT_INPUT) != _FLD2VAL(SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, SRSS_CLK_FLL_CONFIG3)) &&
           (0UL != timeoutus);
         timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    retVal = (0UL != timeoutus) ? CY_SYSCLK_SUCCESS : CY_SYSCLK_TIMEOUT;

    if(retVal == CY_SYSCLK_SUCCESS)
    {
        Cy_SysLib_DelayUs((uint16_t)CY_SYSCLK_BYPASS_CONFIGURE_DELAY);

        SRSS_CLK_FLL_CONFIG  &= ~SRSS_CLK_FLL_CONFIG_FLL_ENABLE_Msk;
        SRSS_CLK_FLL_CONFIG4 &= ~SRSS_CLK_FLL_CONFIG4_CCO_ENABLE_Msk;

    }

    return retVal;
#else
    return (CY_SYSCLK_UNSUPPORTED_STATE);
#endif
}

void Cy_SysClk_FllOutputDividerEnable(bool enable)
{
#if (CY_SRSS_FLL_PRESENT)
    SRSS_CLK_FLL_CONFIG = _BOOL2FLD(SRSS_CLK_FLL_CONFIG_FLL_OUTPUT_DIV, enable);
#else
    CY_UNUSED_PARAMETER(enable); /* Suppress a compiler warning about unused variables */
#endif
}


cy_en_sysclk_status_t Cy_SysClk_FllConfigure(uint32_t inputFreq, uint32_t outputFreq, cy_en_fll_pll_output_mode_t outputMode)
{
#if (CY_SRSS_FLL_PRESENT)
    cy_en_sysclk_status_t retVal = CY_SYSCLK_SUCCESS;

    /* check for errors */
    if ((outputFreq < CY_SYSCLK_FLL_MIN_OUTPUT_FREQ) || (CY_SYSCLK_FLL_MAX_OUTPUT_FREQ < outputFreq) || /* invalid output frequency */
      (outputFreq  < ((inputFreq * 11UL) / 10UL ))) /* check output/input frequency ratio */
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
#else
    CY_UNUSED_PARAMETER(inputFreq); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(outputFreq); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(outputMode); /* Suppress a compiler warning about unused variables */
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}


cy_en_sysclk_status_t Cy_SysClk_FllManualConfigure(const cy_stc_fll_manual_config_t *config)
{
#if (CY_SRSS_FLL_PRESENT)
    cy_en_sysclk_status_t retVal = CY_SYSCLK_INVALID_STATE;

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

    return (retVal);
#else
    CY_UNUSED_PARAMETER(config); /* Suppress a compiler warning about unused variables */
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}


void Cy_SysClk_FllGetConfiguration(cy_stc_fll_manual_config_t *config)
{
#if (CY_SRSS_FLL_PRESENT)
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
#else
    CY_UNUSED_PARAMETER(config); /* Suppress a compiler warning about unused variables */
#endif
}

#if defined (__ARMCC_VERSION)
cy_en_sysclk_status_t __attribute__((optnone)) Cy_SysClk_FllEnable(uint32_t timeoutus)
#elif defined(__GNUC__)
cy_en_sysclk_status_t __attribute__((optimize("Og"))) Cy_SysClk_FllEnable(uint32_t timeoutus)
#else
cy_en_sysclk_status_t Cy_SysClk_FllEnable(uint32_t timeoutus)
#endif /* defined (__ARMCC_VERSION) */
{
#if (CY_SRSS_FLL_PRESENT)
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

    return ((zeroTimeout || (0UL != timeoutus)) ? CY_SYSCLK_SUCCESS : CY_SYSCLK_TIMEOUT);
#else
    CY_UNUSED_PARAMETER(timeoutus); /* Suppress a compiler warning about unused variables */
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}

uint32_t Cy_SysClk_FllGetFrequency(void)
{
#if (CY_SRSS_FLL_PRESENT)

    uint32_t fDiv ;    /* FLL multiplier/feedback divider */
    uint32_t rDiv;    /* FLL reference divider */
    uint32_t oDiv;    /* FLL output divider */
    bool  enabled;    /* FLL enable status; n/a for direct */
    uint32_t freq = 0UL;    /* FLL Frequency */

    cy_stc_fll_manual_config_t fllCfg = {0UL,0U,CY_SYSCLK_FLL_CCO_RANGE0,false,0U,0U,0U,0U,CY_SYSCLK_FLLPLL_OUTPUT_AUTO,0U};
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
#else
    return 0U;
#endif
}

/* ========================================================================== */
/* ===========================    PLL SECTION    ============================ */
/* ========================================================================== */

/* PLL200M */
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
#define CY_SYSCLK_PLL_MAX_OUT_FREQ (200000000UL)

/* PLL400M */

/* PLL OUTPUT_DIV bitfield allowable range */
#define CY_SYSCLK_PLL400M_MIN_OUTPUT_DIV   (2UL)
#define CY_SYSCLK_PLL400M_MAX_OUTPUT_DIV   (16UL)

/* PLL REFERENCE_DIV bitfield allowable range */
#define CY_SYSCLK_PLL400M_MIN_REF_DIV      (1UL)
#define CY_SYSCLK_PLL400M_MAX_REF_DIV      (16UL)

/* PLL FEEDBACK_DIV bitfield allowable range selection */
#define CY_SYSCLK_PLL400M_MIN_FB_DIV       (16UL)
#define CY_SYSCLK_PLL400M_MAX_FB_DIV       (200UL)

/* PLL Fvco range selection */
#define CY_SYSCLK_PLL400M_MIN_FVCO         (400000000UL)
#define CY_SYSCLK_PLL400M_MAX_FVCO         (800000000UL)

/* PLL input and output frequency limits */
#define CY_SYSCLK_PLL400M_MIN_IN_FREQ  (4000000UL)
#define CY_SYSCLK_PLL400M_MAX_IN_FREQ  (64000000UL)
#define CY_SYSCLK_PLL400M_MIN_OUT_FREQ (25000000UL)
#define CY_SYSCLK_PLL400M_MAX_OUT_FREQ (400000000UL)

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))


bool Cy_SysClk_Pll400MIsEnabled(uint32_t pllNum)
{
    CY_UNUSED_PARAMETER(pllNum);
#if (CY_SRSS_PLL400M_PRESENT)
    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);
    return (_FLD2BOOL(CLK_PLL400M_CONFIG_ENABLE, SRSS_CLK_PLL_400M_CONFIG(pllNum)));
#else
    return false;
#endif
}


bool Cy_SysClk_Pll400MLocked(uint32_t pllNum)
{
    CY_UNUSED_PARAMETER(pllNum);
#if (CY_SRSS_PLL400M_PRESENT)
    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);
    return (_FLD2BOOL(CLK_PLL400M_STATUS_LOCKED, SRSS_CLK_PLL_400M_STATUS(pllNum)));
#else
     return false;
#endif
}


bool Cy_SysClk_Pll400MLostLock(uint32_t pllNum)
{
    CY_UNUSED_PARAMETER(pllNum);
#if (CY_SRSS_PLL400M_PRESENT)
    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);

    bool retVal = _FLD2BOOL(CLK_PLL400M_STATUS_UNLOCK_OCCURRED, SRSS_CLK_PLL_400M_STATUS(pllNum));
    /* write a 1 to clear the unlock occurred bit */
    SRSS_CLK_PLL_400M_STATUS(pllNum) = CLK_PLL400M_STATUS_UNLOCK_OCCURRED_Msk;
    return (retVal);
#else
    return false;
#endif
}


cy_en_sysclk_status_t Cy_SysClk_Pll400MDisable(uint32_t pllNum)
{
    CY_UNUSED_PARAMETER(pllNum);
#if (CY_SRSS_PLL400M_PRESENT)

    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);

    /* First bypass PLL */
    CY_REG32_CLR_SET(SRSS_CLK_PLL_400M_CONFIG(pllNum), CLK_PLL400M_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
    /* Wait at least 6 PLL clock cycles */
    Cy_SysLib_DelayUs(1U);
    /* And now disable the PLL itself */
    SRSS_CLK_PLL_400M_CONFIG(pllNum) &= ~CLK_PLL400M_CONFIG_ENABLE_Msk;
    retVal = CY_SYSCLK_SUCCESS;

    return (retVal);
#else
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}


cy_en_sysclk_status_t Cy_SysClk_Pll400MConfigure(uint32_t pllNum, const cy_stc_pll_config_t *config)
{
    CY_UNUSED_PARAMETER(pllNum);
    CY_UNUSED_PARAMETER(config);

#if (CY_SRSS_PLL400M_PRESENT)

    cy_en_sysclk_status_t retVal = CY_SYSCLK_SUCCESS;

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);

    if (((config->inputFreq)  < CY_SYSCLK_PLL400M_MIN_IN_FREQ)  || (CY_SYSCLK_PLL400M_MAX_IN_FREQ  < (config->inputFreq)) ||
        ((config->outputFreq) < CY_SYSCLK_PLL400M_MIN_OUT_FREQ) || (CY_SYSCLK_PLL400M_MAX_OUT_FREQ < (config->outputFreq)))
    {
        retVal = CY_SYSCLK_BAD_PARAM;
    }
    else
    {
        cy_stc_pll_manual_config_t manualConfig = {0U,0U,0U,false,CY_SYSCLK_FLLPLL_OUTPUT_AUTO, 0, false, false, 0 , 0 , false};

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
            for (q = CY_SYSCLK_PLL400M_MIN_REF_DIV; q <= CY_SYSCLK_PLL400M_MAX_REF_DIV; q++)
            {
                /* FEEDBACK_DIV (P) selection */
                for (p = CY_SYSCLK_PLL400M_MIN_FB_DIV; p <= CY_SYSCLK_PLL400M_MAX_FB_DIV; p++)
                {
                    /* Calculate the intermediate Fvco, and make sure that it's in range */
                    uint32_t fvco = (uint32_t)(((uint64_t)(config->inputFreq) * (uint64_t)p) / (uint64_t)q);
                    if ((CY_SYSCLK_PLL400M_MIN_FVCO <= fvco) && (fvco <= CY_SYSCLK_PLL400M_MAX_FVCO))
                    {
                        /* OUTPUT_DIV selection */
                        for (out = CY_SYSCLK_PLL400M_MIN_OUTPUT_DIV; out <= CY_SYSCLK_PLL400M_MAX_OUTPUT_DIV; out++)
                        {
                            uint64_t tempVco = ((uint64_t)config->outputFreq) * ((uint64_t)out);
                            uint64_t tempFeedBackDivLeftShifted = ((tempVco << (uint64_t)SRSS_PLL400M_FRAC_BIT_COUNT) * (uint64_t)q) / (uint64_t)config->inputFreq;
                            volatile uint32_t feedBackFracDiv  = (uint32_t)(tempFeedBackDivLeftShifted & ((1ULL << (uint64_t)SRSS_PLL400M_FRAC_BIT_COUNT) - 1ULL));
                            /* Calculate what output frequency will actually be produced.
                               If it's closer to the target than what we have so far, then save it. */
                            uint32_t fout = (uint32_t)((((uint64_t)config->inputFreq * (((uint64_t)p << SRSS_PLL400M_FRAC_BIT_COUNT) + (uint64_t)feedBackFracDiv)) / ((uint64_t)q * (uint64_t)out)) >> SRSS_PLL400M_FRAC_BIT_COUNT);

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
                                manualConfig.fracEn       = true;
                                manualConfig.fracDiv      = feedBackFracDiv;
                            }
                        }
                    }
                }
            }
            /* exit loops if foutBest equals outputFreq */

        } /* if not, bypass output mode */

        /* If output mode is bypass (input routed directly to output), then
           use old parameters. */
        else
        {
            (void)Cy_SysClk_Pll400MGetConfiguration(pllNum, &manualConfig);
        }
        /* configure PLL based on calculated values */

        manualConfig.outputMode = config->outputMode;
        retVal = Cy_SysClk_Pll400MManualConfigure(pllNum, &manualConfig);

    } /* if no error */

    return (retVal);
#else
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}


cy_en_sysclk_status_t Cy_SysClk_Pll400MManualConfigure(uint32_t pllNum, const cy_stc_pll_manual_config_t *config)
{
    CY_UNUSED_PARAMETER(pllNum);
    CY_UNUSED_PARAMETER(config);

#if (CY_SRSS_PLL400M_PRESENT)

    cy_en_sysclk_status_t retVal = CY_SYSCLK_SUCCESS;

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);

    if (Cy_SysClk_Pll400MIsEnabled(pllNum))
    {
        retVal = CY_SYSCLK_INVALID_STATE;
    }
    /* valid divider bitfield values */
    else if ((config->outputDiv    < CY_SYSCLK_PLL400M_MIN_OUTPUT_DIV) || (CY_SYSCLK_PLL400M_MAX_OUTPUT_DIV < config->outputDiv)    ||
             (config->referenceDiv < CY_SYSCLK_PLL400M_MIN_REF_DIV)    || (CY_SYSCLK_PLL400M_MAX_REF_DIV    < config->referenceDiv) ||
             (config->feedbackDiv  < CY_SYSCLK_PLL400M_MIN_FB_DIV)     || (CY_SYSCLK_PLL400M_MAX_FB_DIV     < config->feedbackDiv))
    {
         retVal = CY_SYSCLK_BAD_PARAM;
    }
    else /* no errors */
    {
        /* If output mode is bypass (input routed directly to output), then done.
           The output frequency equals the input frequency regardless of the frequency parameters. */
        if (config->outputMode != CY_SYSCLK_FLLPLL_OUTPUT_INPUT)
        {
                SRSS_CLK_PLL_400M_CONFIG(pllNum) =
                _VAL2FLD(CLK_PLL400M_CONFIG_FEEDBACK_DIV,  config->feedbackDiv)  |
                _VAL2FLD(CLK_PLL400M_CONFIG_REFERENCE_DIV, config->referenceDiv) |
                _VAL2FLD(CLK_PLL400M_CONFIG_OUTPUT_DIV,    config->outputDiv);

                SRSS_CLK_PLL_400M_CONFIG2(pllNum) =
                _VAL2FLD(CLK_PLL400M_CONFIG2_FRAC_DIV, config->fracDiv)  |
                _VAL2FLD(CLK_PLL400M_CONFIG2_FRAC_DITHER_EN, config->fracDitherEn) |
                _VAL2FLD(CLK_PLL400M_CONFIG2_FRAC_EN, config->fracEn);

                SRSS_CLK_PLL_400M_CONFIG3(pllNum) =
                _VAL2FLD(CLK_PLL400M_CONFIG3_SSCG_DEPTH, config->sscgDepth)  |
                _VAL2FLD(CLK_PLL400M_CONFIG3_SSCG_RATE, config->sscgRate) |
                _VAL2FLD(CLK_PLL400M_CONFIG3_SSCG_EN, config->sscgEn);

        }

        CY_REG32_CLR_SET(SRSS_CLK_PLL_400M_CONFIG(pllNum), CLK_PLL400M_CONFIG_BYPASS_SEL, (uint32_t)config->outputMode);
    }

    return (retVal);
#else
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}


cy_en_sysclk_status_t Cy_SysClk_Pll400MGetConfiguration(uint32_t pllNum, cy_stc_pll_manual_config_t *config)
{
    CY_UNUSED_PARAMETER(pllNum);
    CY_UNUSED_PARAMETER(config);

#if (CY_SRSS_PLL400M_PRESENT)

    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);

    /* Initialize config structure to 0 */
    *config = (cy_stc_pll_manual_config_t){0};

    uint32_t tempReg = SRSS_CLK_PLL_400M_CONFIG(pllNum);
    config->feedbackDiv  = (uint8_t)_FLD2VAL(CLK_PLL400M_CONFIG_FEEDBACK_DIV,  tempReg);
    config->referenceDiv = (uint8_t)_FLD2VAL(CLK_PLL400M_CONFIG_REFERENCE_DIV, tempReg);
    config->outputDiv    = (uint8_t)_FLD2VAL(CLK_PLL400M_CONFIG_OUTPUT_DIV,    tempReg);
    config->outputMode   = (cy_en_fll_pll_output_mode_t)((uint32_t)_FLD2VAL(CLK_PLL400M_CONFIG_BYPASS_SEL, tempReg));

    tempReg = SRSS_CLK_PLL_400M_CONFIG2(pllNum);
    config->fracDiv      = _FLD2VAL(CLK_PLL400M_CONFIG2_FRAC_DIV,  tempReg);
    config->fracDitherEn = (bool)_FLD2VAL(CLK_PLL400M_CONFIG2_FRAC_DITHER_EN, tempReg);
    config->fracEn       = (bool)_FLD2VAL(CLK_PLL400M_CONFIG2_FRAC_EN,    tempReg);

    tempReg = SRSS_CLK_PLL_400M_CONFIG3(pllNum);
    config->sscgDepth  = (uint8_t)_FLD2VAL(CLK_PLL400M_CONFIG3_SSCG_DEPTH,  tempReg);
    config->sscgRate   = (uint8_t)_FLD2VAL(CLK_PLL400M_CONFIG3_SSCG_RATE, tempReg);
    config->sscgEn     = (bool)_FLD2VAL(CLK_PLL400M_CONFIG3_SSCG_EN,    tempReg);

    retVal = CY_SYSCLK_SUCCESS;

    return (retVal);
#else
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}

cy_en_sysclk_status_t Cy_SysClk_Pll400MEnable(uint32_t pllNum, uint32_t timeoutus)
{
    CY_UNUSED_PARAMETER(pllNum);
    CY_UNUSED_PARAMETER(timeoutus);
#if (CY_SRSS_PLL400M_PRESENT)

    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    bool zeroTimeout = (timeoutus == 0UL);

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);

    /* first set the PLL enable bit */
    SRSS_CLK_PLL_400M_CONFIG(pllNum) |= CLK_PLL400M_CONFIG_ENABLE_Msk;

    /* now do the timeout wait for PLL_STATUS, bit LOCKED */
    for (; (0UL == (CLK_PLL400M_STATUS_LOCKED_Msk & SRSS_CLK_PLL_400M_STATUS(pllNum))) &&
           (0UL != timeoutus);
         timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    if (zeroTimeout || (0UL != timeoutus))
    {
        /* Unbypass PLL, if it is not in AUTO mode */
        if ((uint32_t)CY_SYSCLK_FLLPLL_OUTPUT_INPUT == (uint32_t)_FLD2VAL(CLK_PLL400M_CONFIG_BYPASS_SEL, SRSS_CLK_PLL_400M_CONFIG(pllNum)))
        {
            CY_REG32_CLR_SET(SRSS_CLK_PLL_400M_CONFIG(pllNum), CLK_PLL400M_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
        }

        retVal = CY_SYSCLK_SUCCESS;
    }
    else
    {
        /* If lock doesn't occur, then bypass PLL */
        CY_REG32_CLR_SET(SRSS_CLK_PLL_400M_CONFIG(pllNum), CLK_PLL400M_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
        /* Wait at least 6 PLL clock cycles */
        Cy_SysLib_DelayUs(1U);
        /* And now disable the PLL itself */
        SRSS_CLK_PLL_400M_CONFIG(pllNum) &= ~CLK_PLL400M_CONFIG_ENABLE_Msk;
        retVal = CY_SYSCLK_TIMEOUT;
    }

    return (retVal);
#else
    return CY_SYSCLK_UNSUPPORTED_STATE;
#endif
}

uint32_t Cy_SysClk_Pll400MGetFrequency(uint32_t pllNum)
{
    uint32_t fDiv;    /* PLL multiplier/feedback divider */
    uint32_t rDiv;    /* PLL reference divider */
    uint32_t oDiv;    /* PLL output divider */
    uint32_t fracDiv; /* PLL Fractional divider */
    bool  enabled;    /* PLL enable status; n/a for direct */
    uint32_t freq=0UL;    /* PLL Frequency */


    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL400M);

    cy_stc_pll_manual_config_t pllcfg = {0U,0U,0U,false,CY_SYSCLK_FLLPLL_OUTPUT_AUTO, 0, false, false, 0 , 0 , false};
    (void)Cy_SysClk_Pll400MGetConfiguration(pllNum, &pllcfg);
    enabled = (Cy_SysClk_Pll400MIsEnabled(pllNum)) && (CY_SYSCLK_FLLPLL_OUTPUT_INPUT != pllcfg.outputMode);
    fDiv    = pllcfg.feedbackDiv;
    rDiv    = pllcfg.referenceDiv;
    oDiv    = pllcfg.outputDiv;
    fracDiv = pllcfg.fracDiv;

    if (enabled && /* If PLL is enabled and not bypassed */
    (0UL != rDiv) && (0UL != oDiv)) /* to avoid division by zero */
    {
        freq = Cy_SysClk_ClkPathMuxGetFrequency(pllNum + 1UL);
        freq = (uint32_t)((((uint64_t)freq * (((uint64_t)fDiv << SRSS_PLL400M_FRAC_BIT_COUNT) + (uint64_t)fracDiv)) / ((uint64_t)rDiv * (uint64_t)oDiv)) >> SRSS_PLL400M_FRAC_BIT_COUNT);
    }

    return (freq);
}

bool Cy_SysClk_Pll200MIsEnabled(uint32_t pllNum)
{
    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    return (_FLD2BOOL(SRSS_CLK_PLL_CONFIG_ENABLE, SRSS_CLK_PLL_CONFIG[pllNum]));
}

bool Cy_SysClk_Pll200MLocked(uint32_t pllNum)
{
    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    return (_FLD2BOOL(SRSS_CLK_PLL_STATUS_LOCKED, SRSS_CLK_PLL_STATUS[pllNum]));
}

bool Cy_SysClk_Pll200MLostLock(uint32_t pllNum)
{
    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    bool retVal = _FLD2BOOL(SRSS_CLK_PLL_STATUS_UNLOCK_OCCURRED, SRSS_CLK_PLL_STATUS[pllNum]);
    /* write a 1 to clear the unlock occurred bit */
    SRSS_CLK_PLL_STATUS[pllNum] = SRSS_CLK_PLL_STATUS_UNLOCK_OCCURRED_Msk;
    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_Pll200MDisable(uint32_t pllNum)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    /* First bypass PLL */
    CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[pllNum], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
    /* Wait at least 6 PLL clock cycles */
    Cy_SysLib_DelayUs(1U);
    /* And now disable the PLL itself */
    SRSS_CLK_PLL_CONFIG[pllNum] &= ~SRSS_CLK_PLL_CONFIG_ENABLE_Msk;
    retVal = CY_SYSCLK_SUCCESS;

    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_Pll200MConfigure(uint32_t pllNum, const cy_stc_pll_config_t *config)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_SUCCESS;

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    if (((config->inputFreq)  < CY_SYSCLK_PLL_MIN_IN_FREQ)  || (CY_SYSCLK_PLL_MAX_IN_FREQ  < (config->inputFreq)) ||
        ((config->outputFreq) < CY_SYSCLK_PLL_MIN_OUT_FREQ) || (CY_SYSCLK_PLL_MAX_OUT_FREQ < (config->outputFreq)))
    {
        retVal = CY_SYSCLK_BAD_PARAM;
    }
    else
    {
        cy_stc_pll_manual_config_t manualConfig;

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
            (void)Cy_SysClk_Pll200MGetConfiguration(pllNum, &manualConfig);
        }
        /* configure PLL based on calculated values */

        manualConfig.outputMode = config->outputMode;
        retVal = Cy_SysClk_Pll200MManualConfigure(pllNum, &manualConfig);

    } /* if no error */

    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_Pll200MManualConfigure(uint32_t pllNum, const cy_stc_pll_manual_config_t *config)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_SUCCESS;

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    if (Cy_SysClk_Pll200MIsEnabled(pllNum))
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
        /* If output mode is bypass (input routed directly to output), then done.
           The output frequency equals the input frequency regardless of the frequency parameters. */
        if (config->outputMode != CY_SYSCLK_FLLPLL_OUTPUT_INPUT)
        {
            SRSS_CLK_PLL_CONFIG[pllNum] =
                _VAL2FLD(SRSS_CLK_PLL_CONFIG_FEEDBACK_DIV,  config->feedbackDiv)  |
                _VAL2FLD(SRSS_CLK_PLL_CONFIG_REFERENCE_DIV, config->referenceDiv) |
                _VAL2FLD(SRSS_CLK_PLL_CONFIG_OUTPUT_DIV,    config->outputDiv)    |
                _VAL2FLD(SRSS_CLK_PLL_CONFIG_PLL_LF_MODE,   config->lfMode);
        }

        CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[pllNum], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, (uint32_t)config->outputMode);
    }

    return (retVal);
}


cy_en_sysclk_status_t Cy_SysClk_Pll200MGetConfiguration(uint32_t pllNum, cy_stc_pll_manual_config_t *config)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    /* Initialize config structure to 0 */
    *config = (cy_stc_pll_manual_config_t){0};

    uint32_t tempReg = SRSS_CLK_PLL_CONFIG[pllNum];
    config->feedbackDiv  = (uint8_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_FEEDBACK_DIV,  tempReg);
    config->referenceDiv = (uint8_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_REFERENCE_DIV, tempReg);
    config->outputDiv    = (uint8_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_OUTPUT_DIV,    tempReg);
    config->lfMode       =         _FLD2BOOL(SRSS_CLK_PLL_CONFIG_PLL_LF_MODE,   tempReg);
    config->outputMode   = (cy_en_fll_pll_output_mode_t)((uint32_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_BYPASS_SEL, tempReg));
    retVal = CY_SYSCLK_SUCCESS;

    return (retVal);
}

cy_en_sysclk_status_t Cy_SysClk_Pll200MEnable(uint32_t pllNum, uint32_t timeoutus)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;
    bool zeroTimeout = (timeoutus == 0UL);

    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    /* first set the PLL enable bit */
    SRSS_CLK_PLL_CONFIG[pllNum] |= SRSS_CLK_PLL_CONFIG_ENABLE_Msk;

    /* now do the timeout wait for PLL_STATUS, bit LOCKED */
    for (; (0UL == (SRSS_CLK_PLL_STATUS_LOCKED_Msk & SRSS_CLK_PLL_STATUS[pllNum])) &&
           (0UL != timeoutus);
         timeoutus--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    if (zeroTimeout || (0UL != timeoutus))
    {
        /* Unbypass PLL, if it is not in AUTO mode */
        if ((uint32_t)CY_SYSCLK_FLLPLL_OUTPUT_INPUT == (uint32_t)_FLD2VAL(SRSS_CLK_PLL_CONFIG_BYPASS_SEL, SRSS_CLK_PLL_CONFIG[pllNum]))
        {
            CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[pllNum], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
        }

        retVal = CY_SYSCLK_SUCCESS;
    }
    else
    {
        /* If lock doesn't occur, then bypass PLL */
        CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[pllNum], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
        /* Wait at least 6 PLL clock cycles */
        Cy_SysLib_DelayUs(1U);
        /* And now disable the PLL itself */
        SRSS_CLK_PLL_CONFIG[pllNum] &= ~SRSS_CLK_PLL_CONFIG_ENABLE_Msk;
        retVal = CY_SYSCLK_TIMEOUT;
    }

    return (retVal);
}


uint32_t Cy_SysClk_Pll200MGetFrequency(uint32_t pllNum)
{
    uint32_t fDiv;    /* PLL multiplier/feedback divider */
    uint32_t rDiv;    /* PLL reference divider */
    uint32_t oDiv;    /* PLL output divider */
    bool  enabled;    /* PLL enable status; n/a for direct */
    uint32_t freq=0UL;    /* PLL Frequency */


    CY_ASSERT_L1(pllNum < CY_SRSS_NUM_PLL200M);

    cy_stc_pll_manual_config_t pllcfg = {0U,0U,0U,false,CY_SYSCLK_FLLPLL_OUTPUT_AUTO, 0, false, false, 0 , 0 , false};
    (void)Cy_SysClk_Pll200MGetConfiguration(pllNum, &pllcfg);
    enabled = (Cy_SysClk_Pll200MIsEnabled(pllNum)) && (CY_SYSCLK_FLLPLL_OUTPUT_INPUT != pllcfg.outputMode);
    fDiv = pllcfg.feedbackDiv;
    rDiv = pllcfg.referenceDiv;
    oDiv = pllcfg.outputDiv;

    if (enabled && /* If PLL is enabled and not bypassed */
    (0UL != rDiv) && (0UL != oDiv)) /* to avoid division by zero */
    {
        freq = Cy_SysClk_ClkPathMuxGetFrequency((pllNum + 1UL) + CY_SRSS_NUM_PLL400M);

        freq = (uint32_t)CY_SYSLIB_DIV_ROUND(((uint64_t)freq * (uint64_t)fDiv),
                                             ((uint64_t)rDiv * (uint64_t)oDiv));
    }

    return (freq);
}

bool Cy_SysClk_PllIsEnabled(uint32_t clkPath)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MIsEnabled(clkPath);
    }
    else
    {
        return Cy_SysClk_Pll200MIsEnabled(clkPath - CY_SRSS_NUM_PLL400M);
    }
}

bool Cy_SysClk_PllLocked(uint32_t clkPath)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MLocked(clkPath);
    }
    else
    {
        return Cy_SysClk_Pll200MLocked(clkPath - CY_SRSS_NUM_PLL400M);
    }
}

bool Cy_SysClk_PllLostLock(uint32_t clkPath)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MLostLock(clkPath);
    }
    else
    {
        return Cy_SysClk_Pll200MLostLock(clkPath - CY_SRSS_NUM_PLL400M);
    }
}

cy_en_sysclk_status_t Cy_SysClk_PllDisable(uint32_t clkPath)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MDisable(clkPath);
    }
    else
    {
        return Cy_SysClk_Pll200MDisable(clkPath - CY_SRSS_NUM_PLL400M);
    }
}


cy_en_sysclk_status_t Cy_SysClk_PllConfigure(uint32_t clkPath, const cy_stc_pll_config_t *config)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MConfigure(clkPath, config);
    }
    else
    {
        return Cy_SysClk_Pll200MConfigure((clkPath - CY_SRSS_NUM_PLL400M), config);
    }
}

cy_en_sysclk_status_t Cy_SysClk_PllManualConfigure(uint32_t clkPath, const cy_stc_pll_manual_config_t *config)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MManualConfigure(clkPath, config);
    }
    else
    {
        return Cy_SysClk_Pll200MManualConfigure((clkPath - CY_SRSS_NUM_PLL400M), config);
    }
}

cy_en_sysclk_status_t Cy_SysClk_PllGetConfiguration(uint32_t clkPath, cy_stc_pll_manual_config_t *config)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MGetConfiguration(clkPath, config);
    }
    else
    {
        return Cy_SysClk_Pll200MGetConfiguration((clkPath - CY_SRSS_NUM_PLL400M), config);
    }
}

cy_en_sysclk_status_t Cy_SysClk_PllEnable(uint32_t clkPath, uint32_t timeoutus)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MEnable(clkPath, timeoutus);
    }
    else
    {
        return Cy_SysClk_Pll200MEnable((clkPath - CY_SRSS_NUM_PLL400M), timeoutus);
    }
}

uint32_t Cy_SysClk_PllGetFrequency(uint32_t clkPath)
{
    clkPath--; /* to correctly access PLL config and status registers structures */
    CY_ASSERT_L1(clkPath < (CY_SRSS_NUM_PLL));

    if(clkPath < CY_SRSS_NUM_PLL400M)
    {
        return Cy_SysClk_Pll400MGetFrequency(clkPath);
    }
    else
    {
        return Cy_SysClk_Pll200MGetFrequency(clkPath - CY_SRSS_NUM_PLL400M);
    }
}

#elif defined (CY_IP_MXS22SRSS)

bool Cy_SysClk_PllIsEnabled(uint32_t clkPath)
{
    (void) clkPath;
    return false;
}


bool Cy_SysClk_PllLocked(uint32_t clkPath)
{
    (void) clkPath;
    return false;
}


bool Cy_SysClk_PllLostLock(uint32_t clkPath)
{
    (void) clkPath;
    return false;
}


cy_en_sysclk_status_t Cy_SysClk_PllDisable(uint32_t clkPath)
{
    (void) clkPath;
    return CY_SYSCLK_UNSUPPORTED_STATE;
}


cy_en_sysclk_status_t Cy_SysClk_PllConfigure(uint32_t clkPath, const cy_stc_pll_config_t *config)
{
    (void) clkPath;
    (void) config;

    return CY_SYSCLK_UNSUPPORTED_STATE;
}


cy_en_sysclk_status_t Cy_SysClk_PllManualConfigure(uint32_t clkPath, const cy_stc_pll_manual_config_t *config)
{
    (void) clkPath;
    (void) config;

    return CY_SYSCLK_UNSUPPORTED_STATE;
}


cy_en_sysclk_status_t Cy_SysClk_PllGetConfiguration(uint32_t clkPath, cy_stc_pll_manual_config_t *config)
{
    (void) clkPath;
    (void) config;

    return CY_SYSCLK_UNSUPPORTED_STATE;
}


cy_en_sysclk_status_t Cy_SysClk_PllEnable(uint32_t clkPath, uint32_t timeoutus)
{
    (void) clkPath;
    (void) timeoutus;

    return CY_SYSCLK_UNSUPPORTED_STATE;
}

uint32_t Cy_SysClk_PllGetFrequency(uint32_t clkPath)
{
    (void) clkPath;

    return 0;
}

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) */

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

bool Cy_SysClk_ClkMeasurementCountersDone(void)
{
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return (_FLD2BOOL(SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE, SRSS_CLK_CAL_CNT1));
}

cy_en_sysclk_status_t Cy_SysClk_StartClkMeasurementCounters(cy_en_meas_clks_t clock1, uint32_t count1, cy_en_meas_clks_t clock2)
{
    cy_en_sysclk_status_t retVal = CY_SYSCLK_BAD_PARAM;

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

        if ((!preventCounting) /* don't start a measurement if about to enter Deep Sleep mode */  ||
            (_FLD2VAL(SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE, SRSS_CLK_CAL_CNT1) != 0UL/*1 = done */))
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
    }
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return (retVal);
}


uint32_t Cy_SysClk_ClkMeasurementCountersGetFreq(bool measuredClock, uint32_t refClkFreq)
{
    uint32_t retVal = 0UL;
    bool isMeasurementValid = false;

    /* Done counting; allow entry into Deep Sleep mode */
    clkCounting = false;

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
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return (retVal);
}


/* ========================================================================== */
/* ==========================    TRIM SECTION    ============================ */
/* ========================================================================== */

/** \cond INTERNAL */
/** \cond INTERNAL */
#define CY_SYSCLK_ILO_TARGET_FREQ  (32768UL)
/* Nominal trim step size is 1.5% of "the frequency". Using the target frequency */
#define CY_SYSCLK_ILO_TRIM_STEP    (CY_SYSLIB_DIV_ROUND(CY_SYSCLK_ILO_TARGET_FREQ * 15UL, 1000UL))
/** \endcond */

int32_t Cy_SysClk_PiloTrim(uint32_t piloFreq)
{
    CY_UNUSED_PARAMETER(piloFreq); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return 0;
}

void Cy_SysClk_PiloInitialTrim(void)
{
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */
}

void Cy_SysClk_PiloUpdateTrimStep(void)
{
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */
}

void Cy_SysClk_PiloSetTrim(uint32_t trimVal)
{
CY_UNUSED_PARAMETER(trimVal); /* Suppress a compiler warning about unused variables */
CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */
}

uint32_t Cy_SysClk_PiloGetTrim(void)
{
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return 0;
}

int32_t Cy_SysClk_IloTrim(uint32_t iloFreq)
{
#if defined (CY_IP_MXS40SSRSS)
    int32_t changeInTrim;
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
        uint32_t trim = Cy_SysClk_IloGetTrim();

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
    Cy_SysClk_IloSetTrim(trim);
    }

    changeInTrim = (sign ? (int32_t)diff : (0L - (int32_t)diff));
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return changeInTrim;
#else
    CY_UNUSED_PARAMETER(iloFreq); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return 0;
#endif
}

#if  defined (CY_IP_MXS40SSRSS)
void Cy_SysClk_IloSetTrim(uint32_t trimVal)
{
#if defined (CY_IP_MXS40SSRSS)
    CY_REG32_CLR_SET(SRSS_CLK_TRIM_ILO_CTL, SRSS_CLK_TRIM_ILO_CTL_ILO_FTRIM, trimVal);
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */
#else
    CY_UNUSED_PARAMETER(trimVal); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */
#endif
}

uint32_t Cy_SysClk_IloGetTrim(void)
{
#if defined (CY_IP_MXS40SSRSS)
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return (_FLD2VAL(SRSS_CLK_TRIM_ILO_CTL_ILO_FTRIM, SRSS_CLK_TRIM_ILO_CTL));
#else
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return 0;
#endif
}
#endif /* defined (CY_IP_MXS40SSRSS) */

/* ========================================================================== */
/* ======================    POWER MANAGEMENT SECTION    ==================== */
/* ========================================================================== */


/** \cond INTERNAL */
/* Timeout count for use in function Cy_SysClk_DeepSleepCallback() is sufficiently large for ~1 second */
#define TIMEOUT (1000000UL)
/** \endcond */

cy_en_syspm_status_t Cy_SysClk_DeepSleepCallback(cy_stc_syspm_callback_params_t * callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_FAIL;

    /* Suppress "not used" warning */
    CY_UNUSED_PARAMETER(callbackParams);
    CY_UNUSED_PARAMETER(clkCounting);

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
            retVal = CY_SYSPM_SUCCESS;
            break;

        case CY_SYSPM_AFTER_TRANSITION:
            preventCounting = false; /* Allow clock measurement */
            break;

        default: /* Unsupported mode, return CY_SYSPM_FAIL */
            break;
    }

    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return (retVal);

}


/* ========================================================================== */
/* =====================    clk_peripherals SECTION    ====================== */
/* ========================================================================== */


uint32_t Cy_SysClk_PeriphGetFrequency(cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to en_clk_dst_t enum.');
    return Cy_SysClk_PeriPclkGetFrequency((en_clk_dst_t)PERI_PCLK_PERIPHERAL_GROUP_NUM, dividerType, dividerNum);
}

/** \cond INTERNAL */
/* Value to indicate invalid HF NUM */
#define CY_SYSCLK_INVALID_HF_NUM (0xFFFFFFFFUL)
/** \endcond */

uint32_t Cy_Sysclk_PeriPclkGetClkHfNum(uint32_t grpNum)
{
    uint32_t instNum = (uint8_t)(((uint32_t)grpNum & PERI_GR_INST_NUM_Msk )>>PERI_GR_INST_NUM_Pos);

    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    /* Additional check incase Asserts are disabled */
    if(grpNum >= PERI_PCLK_GR_NUM(instNum))
    {
        return CY_SYSCLK_INVALID_HF_NUM;
    }

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
        uint32_t peri0GrpToHfArray[] = { PERI0_PCLK_GR_NUM_0_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_1_CLK_HF_NUM,
                                  };

#elif defined (CY_IP_MXS22SRSS)
        uint32_t peri0GrpToHfArray[] = { PERI0_PCLK_GR_NUM_0_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_1_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_2_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_3_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_4_CLK_HF_NUM,
                                  };
#else
        uint32_t peri0GrpToHfArray[] = { PERI0_PCLK_GR_NUM_0_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_1_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_2_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_3_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_4_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_5_CLK_HF_NUM,
                                    PERI0_PCLK_GR_NUM_6_CLK_HF_NUM
                                  };
#endif

#if defined (CY_IP_MXS22SRSS)
    uint32_t peri1GrpToHfArray[] = { PERI1_PCLK_GR_NUM_0_CLK_HF_NUM,
                                PERI1_PCLK_GR_NUM_1_CLK_HF_NUM,
                                PERI1_PCLK_GR_NUM_2_CLK_HF_NUM,
                                PERI1_PCLK_GR_NUM_3_CLK_HF_NUM,
                                PERI1_PCLK_GR_NUM_4_CLK_HF_NUM,
                              };

#else
    uint32_t peri1GrpToHfArray[] = {0};
#endif

    if(0UL == instNum)
    {
        return peri0GrpToHfArray[grpNum];
    }
    else
    {
        return peri1GrpToHfArray[grpNum];
    }
}

uint32_t Cy_SysClk_PeriPclkGetFrequency(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum)
{
    uint32_t integer = 0UL;        /* Integer part of peripheral divider */
    uint32_t freq = 0UL;
    uint32_t grpNum = (((uint32_t)ipBlock) & PERI_PCLK_GR_NUM_Msk )>>PERI_PCLK_GR_NUM_Pos;
    uint32_t instNum = (uint8_t)(((uint32_t)ipBlock & PERI_PCLK_INST_NUM_Msk )>>PERI_PCLK_INST_NUM_Pos);
    uint32_t hfNum = Cy_Sysclk_PeriPclkGetClkHfNum(grpNum | (instNum << PERI_GR_INST_NUM_Pos));


    CY_ASSERT_L1(instNum < PERI_INSTANCE_COUNT);
    CY_ASSERT_L1(grpNum < PERI_PCLK_GR_NUM(instNum));

    CY_ASSERT_L1(((dividerType == CY_SYSCLK_DIV_8_BIT)    && (dividerNum < PERI_DIV_8_NR(instNum , grpNum)))    || \
                 ((dividerType == CY_SYSCLK_DIV_16_BIT)   && (dividerNum < PERI_DIV_16_NR(instNum , grpNum)))   || \
                 ((dividerType == CY_SYSCLK_DIV_16_5_BIT) && (dividerNum < PERI_DIV_16_5_NR(instNum , grpNum))) || \
                 ((dividerType == CY_SYSCLK_DIV_24_5_BIT) && (dividerNum < PERI_DIV_24_5_NR(instNum , grpNum))));

    if(hfNum != CY_SYSCLK_INVALID_HF_NUM)
    {
        freq = Cy_SysClk_ClkHfGetFrequency(hfNum); /* Get CLK_HF* frequency */

        /* get the divider value for clk_peri to the selected peripheral clock */
        switch(dividerType)
        {
            case CY_SYSCLK_DIV_8_BIT:
            case CY_SYSCLK_DIV_16_BIT:
                integer = 1UL + Cy_SysClk_PeriPclkGetDivider(ipBlock, dividerType, dividerNum);
                freq = CY_SYSLIB_DIV_ROUND(freq, integer);
                break;

            case CY_SYSCLK_DIV_16_5_BIT:
            case CY_SYSCLK_DIV_24_5_BIT:
                {
                    uint32_t locFrac;
                    uint32_t locDiv;
                    uint64_t locFreq = freq * 32ULL;
                    Cy_SysClk_PeriPclkGetFracDivider(ipBlock, dividerType, dividerNum, &integer, &locFrac);
                    /* For fractional dividers, the divider is (int + 1) + frac/32 */
                    locDiv = ((1UL + integer) * 32UL) + locFrac;
                    freq = (uint32_t) CY_SYSLIB_DIV_ROUND(locFreq, (uint64_t)locDiv);
                }
                break;

            default:
                /* Unknown Divider */
                break;
        }
    }
    CY_UNUSED_PARAMETER(clkCounting); /* Suppress a compiler warning about unused variables */

    return (freq);
}

#endif /* defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS) */
/* [] END OF FILE */
