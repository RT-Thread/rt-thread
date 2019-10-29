/***************************************************************************//**
* \file cy_lvd.c
* \version 1.10
*
* The source code file for the LVD driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

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


/* [] END OF FILE */
