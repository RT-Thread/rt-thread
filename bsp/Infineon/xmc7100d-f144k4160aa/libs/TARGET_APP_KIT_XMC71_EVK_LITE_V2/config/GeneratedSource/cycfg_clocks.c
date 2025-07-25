/*******************************************************************************
 * File Name: cycfg_clocks.c
 *
 * Description:
 * Clock configuration
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.50.0
 * device-db 4.22.0.7873
 * mtb-pdl-cat1 3.15.0.40227
 *
 *******************************************************************************
 * Copyright 2025 Cypress Semiconductor Corporation (an Infineon company) or
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
 ******************************************************************************/

#include "cycfg_clocks.h"

#if defined (CY_USING_HAL)
const cyhal_resource_inst_t CYBSP_TRACE_CLK_DIV2_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = CYBSP_TRACE_CLK_DIV2_HW,
    .channel_num = CYBSP_TRACE_CLK_DIV2_NUM,
};
const cyhal_resource_inst_t peri_0_group_1_div_8_0_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = peri_0_group_1_div_8_0_HW,
    .channel_num = peri_0_group_1_div_8_0_NUM,
};
const cyhal_resource_inst_t peri_0_group_1_div_8_1_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = peri_0_group_1_div_8_1_HW,
    .channel_num = peri_0_group_1_div_8_1_NUM,
};
const cyhal_resource_inst_t peri_0_group_1_div_8_2_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = peri_0_group_1_div_8_2_HW,
    .channel_num = peri_0_group_1_div_8_2_NUM,
};
const cyhal_resource_inst_t peri_0_group_1_div_8_3_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = peri_0_group_1_div_8_3_HW,
    .channel_num = peri_0_group_1_div_8_3_NUM,
};
const cyhal_resource_inst_t peri_0_group_1_div_8_4_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = peri_0_group_1_div_8_4_HW,
    .channel_num = peri_0_group_1_div_8_4_NUM,
};
const cyhal_resource_inst_t peri_0_group_1_div_8_5_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = peri_0_group_1_div_8_5_HW,
    .channel_num = peri_0_group_1_div_8_5_NUM,
};
const cyhal_resource_inst_t peri_0_group_1_div_8_6_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = peri_0_group_1_div_8_6_HW,
    .channel_num = peri_0_group_1_div_8_6_NUM,
};
const cyhal_resource_inst_t peri_0_group_1_div_8_7_obj =
{
    .type = CYHAL_RSC_CLOCK,
    .block_num = peri_0_group_1_div_8_7_HW,
    .channel_num = peri_0_group_1_div_8_7_NUM,
};
#endif /* defined (CY_USING_HAL) */

void init_cycfg_clocks(void)
{
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)CYBSP_TRACE_CLK_DIV2_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 2U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)CYBSP_TRACE_CLK_DIV2_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 2U, 0U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)CYBSP_TRACE_CLK_DIV2_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 2U);
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_0_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 0U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_0_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 0U, 108U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_0_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 0U);
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_1_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 1U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_1_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 1U, 0U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_1_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 1U);
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_2_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 2U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_2_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 2U, 0U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_2_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 2U);
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_3_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 3U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_3_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 3U, 0U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_3_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 3U);
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_4_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 4U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_4_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 4U, 0U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_4_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 4U);
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_5_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 5U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_5_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 5U, 0U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_5_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 5U);
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_6_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 6U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_6_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 6U, 0U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_6_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 6U);
    Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_7_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 7U);
    Cy_SysClk_PeriPclkSetDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_7_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 7U, 108U);
    Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)PERI_0_GROUP_1_DIV_8_7_GRP_NUM, CY_SYSCLK_DIV_8_BIT, 7U);
}
void reserve_cycfg_clocks(void)
{
#if defined (CY_USING_HAL)
    cyhal_hwmgr_reserve(&CYBSP_TRACE_CLK_DIV2_obj);
    cyhal_hwmgr_reserve(&peri_0_group_1_div_8_0_obj);
    cyhal_hwmgr_reserve(&peri_0_group_1_div_8_1_obj);
    cyhal_hwmgr_reserve(&peri_0_group_1_div_8_2_obj);
    cyhal_hwmgr_reserve(&peri_0_group_1_div_8_3_obj);
    cyhal_hwmgr_reserve(&peri_0_group_1_div_8_4_obj);
    cyhal_hwmgr_reserve(&peri_0_group_1_div_8_5_obj);
    cyhal_hwmgr_reserve(&peri_0_group_1_div_8_6_obj);
    cyhal_hwmgr_reserve(&peri_0_group_1_div_8_7_obj);
#endif /* defined (CY_USING_HAL) */
}
