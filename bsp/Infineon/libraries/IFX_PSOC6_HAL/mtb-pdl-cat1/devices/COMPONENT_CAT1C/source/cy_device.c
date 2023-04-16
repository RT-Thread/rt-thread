/***************************************************************************//**
* \file cy_device.c
* \version 2.0
*
* This file provides the definitions for core and peripheral block HW base
* addresses, versions, and parameters.
*
********************************************************************************
* \copyright
* Copyright 2018-2019 Cypress Semiconductor Corporation
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

/*******************************************************************************
*                   Global Variables
*******************************************************************************/

/* This is set in Cy_PDL_Init() to the device information relevant
 * for the current target.
 */
const cy_stc_device_t* cy_device;

/* Platform and peripheral block configuration */
const cy_stc_device_t cy_deviceIpBlockCfg ;

/******************************************************************************
* Function Name: Cy_PDL_Init
****************************************************************************//**
*
* \brief Initializes the platform and peripheral block configuration for the
* given target device.
*
* \param device
* Pointer to the platform and peripheral block configuration
*
* \note
* This function must be called prior calling any function in PDL.
*
*******************************************************************************/
void Cy_PDL_Init(const cy_stc_device_t * device)
{
    cy_device = device;
}


/* [] END OF FILE */
