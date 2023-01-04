/***************************************************************************//**
* \file cyhal_peri_common.h
*
* Description:
* Provides definitions for the triggers for each supported device family.
*
********************************************************************************
* \copyright
* Copyright 2018-2019 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
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

#pragma once

#include "cy_device.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#if defined(CY_IP_MXPERI) || defined(CY_IP_M0S8PERI)

    #define _CYHAL_PCLK_GROUP(clkdst)       0
    #define _CYHAL_TCPWM0_PCLK_CLOCK0       PCLK_TCPWM0_CLOCKS0
    #define _CYHAL_TCPWM1_PCLK_CLOCK0       PCLK_TCPWM1_CLOCKS0
    #define _CYHAL_SCB0_PCLK_CLOCK          PCLK_SCB0_CLOCK

#elif defined(CY_IP_MXSPERI)

    #define _CYHAL_PCLK_GROUP(clkdst)       ((uint8_t)((uint32_t)(clkdst) >> 8))
    #define _CYHAL_TCPWM0_PCLK_CLOCK0       PCLK_TCPWM0_CLOCK_COUNTER_EN0
    #define _CYHAL_TCPWM1_PCLK_CLOCK0       PCLK_TCPWM1_CLOCK_COUNTER_EN0
    #define _CYHAL_SCB0_PCLK_CLOCK          PCLK_SCB0_CLOCK_SCB_EN

#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

