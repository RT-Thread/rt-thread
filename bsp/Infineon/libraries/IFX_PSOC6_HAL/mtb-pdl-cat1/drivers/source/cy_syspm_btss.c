/***************************************************************************//**
* \file cy_syspm_btss.c
* \version 5.91
*
* Provides implementation of the BTSS PDL driver.
*
********************************************************************************
* \copyright
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

#if defined (CY_IP_MXS40BLE52SS)

#include "cy_syspm_btss.h"

#define CY_BTSS_RADIO_XTAL_OSC_FREQ    (24000000UL) /* Hz */

/* BTSS Lock counter */
static uint32_t cy_btss_lock_count;

/* CPUSS Lock counter */
static uint32_t cy_cpuss_lock_count;


uint32_t Cy_BTSS_GetXtalOscFreq(void)
{
    return CY_BTSS_RADIO_XTAL_OSC_FREQ;
}

cy_en_btss_status_t Cy_BTSS_PowerDep(bool enable)
{
    cy_en_btss_status_t retVal = CY_BTSS_INVALID_STATE;
    uint32_t interruptState;
    uint32_t timeoutus = CY_BTSS_SL_CTL3_WAIT_DELAY_US;

    if(enable)
    {
        interruptState = Cy_SysLib_EnterCriticalSection();
        /* Set only if cy_btss_lock_count == 0 */
        if(cy_btss_lock_count == 0UL)
        {
            (void)cy_pd_pdcm_set_dependency(CY_PD_PDCM_BTSS, CY_PD_PDCM_CPUSS); /* Suppress a compiler warning about unused return value */
        }
        Cy_SysLib_ExitCriticalSection(interruptState);

        for(;(Cy_SysClk_PeriGroupGetSlaveCtl(CY_PERI_BLESS_GROUP_NR,CY_SYSCLK_PERI_GROUP_SL_CTL3) == 0UL) &&
            (0UL != timeoutus);
            timeoutus--)
        {
            Cy_SysLib_DelayUs(1U);
        }
        if(0UL == timeoutus)
        {
            retVal = CY_BTSS_TIMEOUT;
        }
        else
        {
            retVal = CY_BTSS_SUCCESS;
        }

        interruptState = Cy_SysLib_EnterCriticalSection();
        if(retVal == CY_BTSS_SUCCESS)
        {
            cy_btss_lock_count++;
        }
        Cy_SysLib_ExitCriticalSection(interruptState);
    }
    else
    {
        /* Dont Decrement if already in Disable State */
        interruptState = Cy_SysLib_EnterCriticalSection();
        if(cy_btss_lock_count != 0UL)
        {
            cy_btss_lock_count--;
        }

        /* Clear only if cy_btss_lock_count == 0 */
        if(cy_btss_lock_count  == 0UL)
        {
            (void)cy_pd_pdcm_clear_dependency(CY_PD_PDCM_BTSS, CY_PD_PDCM_CPUSS); /* Suppress a compiler warning about unused return value */
        }
        Cy_SysLib_ExitCriticalSection(interruptState);

        retVal = CY_BTSS_SUCCESS;
    }

    return retVal;
}

cy_en_btss_status_t Cy_BTSS_CPUSSPowerDep(bool enable)
{
    cy_en_btss_status_t retVal = CY_BTSS_INVALID_STATE;
    uint32_t interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();

    if(enable)
    {
        /* Set only if cy_btss_lock_count == 0 */
        if(cy_cpuss_lock_count == 0UL)
        {
            (void)cy_pd_pdcm_set_dependency(CY_PD_PDCM_CPUSS, CY_PD_PDCM_BTSS); /* Suppress a compiler warning about unused return value */
        }

        cy_cpuss_lock_count++;

        retVal = CY_BTSS_SUCCESS;
    }
    else
    {
        /* Dont Decrement if already in Disable State */
        if(cy_cpuss_lock_count != 0UL)
        {
            cy_cpuss_lock_count--;
        }

        /* Clear only if cy_btss_lock_count == 0 */
        if(cy_cpuss_lock_count  == 0UL)
        {
            (void)cy_pd_pdcm_clear_dependency(CY_PD_PDCM_CPUSS, CY_PD_PDCM_BTSS); /* Suppress a compiler warning about unused return value */
        }

        retVal = CY_BTSS_SUCCESS;
    }

    Cy_SysLib_ExitCriticalSection(interruptState);

    return retVal;
}


void Cy_BTSS_AssertReset(bool assertEn)
{
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(CY_PERI_BLESS_GROUP_NR, CY_SYSCLK_PERI_GROUP_SL_CTL2, (assertEn ? 0x1U : 0x0U));
}

bool Cy_BTSS_IsResetAsserted(void)
{
    return (Cy_SysClk_PeriGroupGetSlaveCtl(CY_PERI_BLESS_GROUP_NR, CY_SYSCLK_PERI_GROUP_SL_CTL2) != 0x0U);
}

#endif /* CY_IP_MXS40BLE52SS */
/* [] END OF FILE */

