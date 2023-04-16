/***************************************************************************//**
* \file cy_lvd.c
* \version 1.60
*
* The source code file for the LVD driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2017-2022), Cypress Semiconductor Corporation (an Infineon company) or
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

#if defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_IP_MXS22SRSS)

#include "cy_lvd.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
* Function Name: Cy_LVD_DeepSleepCallback
****************************************************************************//**
*
* When this function is registered by \ref Cy_SysPm_RegisterCallback - it
* automatically enables the LVD after wake up from Deep-Sleep mode.
*
* \param callbackParams The pointer to the callback parameters structure,
* see \ref cy_stc_syspm_callback_params_t.
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return the SysPm callback status \ref cy_en_syspm_status_t.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_LVD_DeepSleepCallback(cy_stc_syspm_callback_params_t * callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t ret = CY_SYSPM_SUCCESS;

    if (callbackParams != NULL)
    {
        switch(mode)
        {
            case CY_SYSPM_CHECK_READY:
            case CY_SYSPM_CHECK_FAIL:
            case CY_SYSPM_BEFORE_TRANSITION:
                break;

            case CY_SYSPM_AFTER_TRANSITION:
                Cy_LVD_Enable();
                break;

            default:
                ret = CY_SYSPM_FAIL;
                break;
        }
    }
    return (ret);
}


#ifdef __cplusplus
}
#endif

#endif
/* [] END OF FILE */
