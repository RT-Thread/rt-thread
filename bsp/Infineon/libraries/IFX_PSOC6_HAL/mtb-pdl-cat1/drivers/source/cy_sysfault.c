/***************************************************************************//**
* \file cy_sysfault.c
* \version 1.0
*
* \brief
* Provides an API implementation of the SysFault driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
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

#include "cy_sysfault.h"

#if defined (CY_IP_M7CPUSS)


cy_en_SysFault_status_t  Cy_SysFault_Init(FAULT_STRUCT_Type *base, cy_stc_SysFault_t *config)
{
    if(config != NULL)
    {
        FAULT_CTL(base) = _VAL2FLD(FAULT_STRUCT_CTL_TR_EN, config->TriggerEnable) |
                          _VAL2FLD(FAULT_STRUCT_CTL_OUT_EN, config->OutputEnable) |
                          _VAL2FLD(FAULT_STRUCT_CTL_RESET_REQ_EN, config->ResetEnable);
        return CY_SYSFAULT_SUCCESS;
    }
    else
    {
        return CY_SYSFAULT_BAD_PARAM;
    }
}


void Cy_SysFault_ClearStatus(FAULT_STRUCT_Type *base)
{
    FAULT_STATUS(base) = 0UL;
}


cy_en_SysFault_source_t Cy_SysFault_GetErrorSource(FAULT_STRUCT_Type *base)
{
    if(_FLD2VAL(FAULT_STRUCT_STATUS_VALID, FAULT_STATUS(base)) == 1UL)
    {
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_SysFault_source_t enum.');
        return((cy_en_SysFault_source_t)(_FLD2VAL(FAULT_STRUCT_STATUS_IDX, FAULT_STATUS(base))));
    }
    else
    {
        return CY_SYSFAULT_NO_FAULT;
    }

}


uint32_t Cy_SysFault_GetFaultData(FAULT_STRUCT_Type *base, cy_en_SysFault_Data_t dataSet)
{
    CY_ASSERT_L3(CY_SYSFAULT_IS_DATA_SET_VALID(dataSet));

    return _FLD2VAL(FAULT_STRUCT_DATA_DATA, FAULT_DATA(base)[dataSet]);
}


uint32_t Cy_SysFault_GetPendingFault(FAULT_STRUCT_Type *base, cy_en_SysFault_Set_t pendingFault)
{
    CY_ASSERT_L3(CY_SYSFAULT_IS_FAULT_SET_VALID(pendingFault));
    uint32_t retVal = 0;

    switch(pendingFault)
    {
        case CY_SYSFAULT_SET0:
        {
            retVal = _FLD2VAL(FAULT_STRUCT_PENDING0_SOURCE, FAULT_PENDING0(base));
        }
        break;

        case CY_SYSFAULT_SET1:
        {
            retVal = _FLD2VAL(FAULT_STRUCT_PENDING1_SOURCE, FAULT_PENDING1(base));
        }
        break;

        case CY_SYSFAULT_SET2:
        {
            retVal = _FLD2VAL(FAULT_STRUCT_PENDING1_SOURCE, FAULT_PENDING2(base));
        }
        break;

        default:
        {
            CY_ASSERT_L3(0);
        }
        break;
    }

    return retVal;
}

void Cy_SysFault_SetMaskByIdx(FAULT_STRUCT_Type *base, cy_en_SysFault_source_t idx)
{
    CY_ASSERT_L3(idx < CY_SYSFAULT_NO_FAULT);
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_SysFault_Set_t enum.');
    switch(((cy_en_SysFault_Set_t)((uint32_t)idx / 32UL)))
    {
        case CY_SYSFAULT_SET0:
        {
            FAULT_MASK0(base) |= _VAL2FLD(FAULT_STRUCT_MASK0_SOURCE, (1UL << (uint32_t)idx));
        }
        break;

        case CY_SYSFAULT_SET1:
        {
            FAULT_MASK1(base) |= _VAL2FLD(FAULT_STRUCT_MASK1_SOURCE, (1UL << ((uint32_t)idx - 32UL)));
        }
        break;

        case CY_SYSFAULT_SET2:
        {
            FAULT_MASK2(base) |= _VAL2FLD(FAULT_STRUCT_MASK2_SOURCE, (1UL << ((uint32_t)idx - 64UL)));
        }
        break;

        default:
        {
            CY_ASSERT_L3(0);
        }
        break;
    }
}


void  Cy_SysFault_ClearMaskByIdx(FAULT_STRUCT_Type *base, cy_en_SysFault_source_t idx)
{
    CY_ASSERT_L3(idx < CY_SYSFAULT_NO_FAULT);
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_SysFault_Set_t enum.');
    switch(((cy_en_SysFault_Set_t)((uint32_t)idx / 32UL)))
    {
        case CY_SYSFAULT_SET0:
        {
            FAULT_MASK0(base) &= ~(1UL << (uint32_t)idx);
        }
        break;

        case CY_SYSFAULT_SET1:
        {
            FAULT_MASK1(base) &= ~(1UL << ((uint32_t)idx - 32UL));
        }
        break;

        case CY_SYSFAULT_SET2:
        {
            FAULT_MASK2(base) &= ~(1UL << ((uint32_t)idx - 64UL));
        }
        break;

        default:
        {
            CY_ASSERT_L3(0);
        }
        break;
    }
}


uint32_t Cy_SysFault_GetInterruptStatus(FAULT_STRUCT_Type *base)
{
    return _FLD2VAL(FAULT_STRUCT_INTR_FAULT, FAULT_INTR(base));
}


void Cy_SysFault_ClearInterrupt(FAULT_STRUCT_Type *base)
{
     FAULT_INTR(base) = 1UL;
}


void Cy_SysFault_SetInterrupt(FAULT_STRUCT_Type *base)
{
    FAULT_INTR_SET(base) = FAULT_STRUCT_INTR_SET_FAULT_Msk;
}


void Cy_SysFault_SetInterruptMask(FAULT_STRUCT_Type *base)
{
    FAULT_INTR_MASK(base) = FAULT_STRUCT_INTR_MASK_FAULT_Msk;
}

void Cy_SysFault_ClearInterruptMask(FAULT_STRUCT_Type *base)
{
    FAULT_INTR_MASK(base) &=  ~FAULT_STRUCT_INTR_MASK_FAULT_Msk;
}

uint32_t Cy_SysFault_GetInterruptMask(FAULT_STRUCT_Type *base)
{
    return(FAULT_INTR_MASK(base));
}


uint32_t Cy_SysFault_GetInterruptStatusMasked(FAULT_STRUCT_Type *base)
{
    return(FAULT_INTR_MASKED(base));
}

#endif /* CY_IP_M7CPUSS */
/* [] END OF FILE */
