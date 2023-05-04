/*******************************************************************************
* File Name: cycfg_clocks.c
*
* Description:
* Clock configuration
* This file was automatically generated and should not be modified.
* Configurator Backend 3.0.0
* device-db 4.1.0.3437
* mtb-pdl-cat1 3.3.0.21979
*
********************************************************************************
* Copyright 2023 Cypress Semiconductor Corporation (an Infineon company) or
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

#include "cycfg_clocks.h"

#if defined (CY_USING_HAL)
    const cyhal_resource_inst_t peri_0_div_16_15_obj =
    {
        .type = CYHAL_RSC_CLOCK,
        .block_num = peri_0_div_16_15_HW,
        .channel_num = peri_0_div_16_15_NUM,
    };
    const cyhal_resource_inst_t CYBSP_CSD_CLK_DIV_obj =
    {
        .type = CYHAL_RSC_CLOCK,
        .block_num = CYBSP_CSD_CLK_DIV_HW,
        .channel_num = CYBSP_CSD_CLK_DIV_NUM,
    };
    const cyhal_resource_inst_t CYBSP_TRACE_CLK_DIV_obj =
    {
        .type = CYHAL_RSC_CLOCK,
        .block_num = CYBSP_TRACE_CLK_DIV_HW,
        .channel_num = CYBSP_TRACE_CLK_DIV_NUM,
    };
#endif //defined (CY_USING_HAL)


void init_cycfg_clocks(void)
{
    Cy_SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_16_BIT, 15U);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 15U, 0U);
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 15U);
    Cy_SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_8_BIT, 0U);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_8_BIT, 0U, 255U);
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_8_BIT, 0U);
    Cy_SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_8_BIT, 7U);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_8_BIT, 7U, 0U);
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_8_BIT, 7U);
}

void reserve_cycfg_clocks(void)
{
#if defined (CY_USING_HAL)
    cyhal_hwmgr_reserve(&peri_0_div_16_15_obj);
    cyhal_hwmgr_reserve(&CYBSP_CSD_CLK_DIV_obj);
    cyhal_hwmgr_reserve(&CYBSP_TRACE_CLK_DIV_obj);
#endif //defined (CY_USING_HAL)
}
