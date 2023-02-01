/*******************************************************************************
* File Name: cycfg_peripherals.c
*
* Description:
* Peripheral Hardware Block configuration
* This file was automatically generated and should not be modified.
* Tools Package 2.4.0.5972
* mtb-pdl-cat1 2.4.0.13881
* personalities 6.0.0.0
* udd 3.0.0.1974
*
********************************************************************************
* Copyright 2022 Cypress Semiconductor Corporation (an Infineon company) or
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
********************************************************************************/
#include <rtthread.h>

#include "cycfg_peripherals.h"

cy_stc_csd_context_t cy_csd_0_context =
{
    .lockKey = CY_CSD_NONE_KEY,
};

void init_cycfg_peripherals(void)
{
    Cy_SysClk_PeriphAssignDivider(PCLK_CSD_CLOCK, CY_SYSCLK_DIV_8_BIT, 0U);

#ifdef BSP_USING_UART0
    /* UART0 Device Clock*/
    Cy_SysClk_PeriphAssignDivider(PCLK_SCB0_CLOCK, CY_SYSCLK_DIV_8_BIT, 0U);
#endif
#ifdef BSP_USING_UART1
    /* UART1 Device Clock*/
    Cy_SysClk_PeriphAssignDivider(PCLK_SCB1_CLOCK, CY_SYSCLK_DIV_8_BIT, 0U);
#endif
#ifdef BSP_USING_UART2
    /* UART2 Device Clock*/
    Cy_SysClk_PeriphAssignDivider(PCLK_SCB2_CLOCK, CY_SYSCLK_DIV_8_BIT, 0U);
#endif
#if defined(BSP_USING_UART3) || defined(BSP_USING_HW_I2C3)
    /* UART3 Device Clock*/
    Cy_SysClk_PeriphAssignDivider(PCLK_SCB3_CLOCK, CY_SYSCLK_DIV_8_BIT, 0U);
#endif
#ifdef BSP_USING_UART4
    /* UART4 Device Clock*/
    Cy_SysClk_PeriphAssignDivider(PCLK_SCB4_CLOCK, CY_SYSCLK_DIV_8_BIT, 0U);
#endif
#ifdef BSP_USING_UART5
    /* UART5 Device Clock*/
    Cy_SysClk_PeriphAssignDivider(PCLK_SCB5_CLOCK, CY_SYSCLK_DIV_8_BIT, 0U);
#endif
}
