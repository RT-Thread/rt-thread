/*******************************************************************************
 * File Name: cycfg_clocks.h
 *
 * Description:
 * Clock configuration
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.20.0
 * device-db 4.15.0.5746
 * mtb-pdl-cat1 3.10.0.32115
 *
 *******************************************************************************
 * Copyright 2024 Cypress Semiconductor Corporation (an Infineon company) or
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

#if !defined(CYCFG_CLOCKS_H)
#define CYCFG_CLOCKS_H

#include "cycfg_notices.h"
#include "cy_sysclk.h"

#if defined (CY_USING_HAL)
#include "cyhal_hwmgr.h"
#endif /* defined (CY_USING_HAL) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#define CYBSP_TRACE_CLK_DIV_ENABLED 1U

#if defined (CY_USING_HAL) || defined (CY_USING_HAL_LITE)
#define CYBSP_TRACE_CLK_DIV_HW CYHAL_CLOCK_BLOCK_PERIPHERAL0_8BIT
#endif /* defined (CY_USING_HAL) || defined (CY_USING_HAL_LITE) */

#if !defined (CY_USING_HAL) && !defined (CY_USING_HAL_LITE)
#define CYBSP_TRACE_CLK_DIV_HW CY_SYSCLK_DIV_8_BIT
#endif /* !defined (CY_USING_HAL) && !defined (CY_USING_HAL_LITE) */

#define CYBSP_TRACE_CLK_DIV_NUM 3U
#define CYBSP_TRACE_CLK_DIV_GRP_NUM ((0U << PERI_PCLK_GR_NUM_Pos) | (0U << PERI_PCLK_INST_NUM_Pos))
#define peri_0_group_1_div_8_0_ENABLED 1U

#if defined (CY_USING_HAL) || defined (CY_USING_HAL_LITE)
#define peri_0_group_1_div_8_0_HW CYHAL_CLOCK_BLOCK_PERIPHERAL1_8BIT
#endif /* defined (CY_USING_HAL) || defined (CY_USING_HAL_LITE) */

#if !defined (CY_USING_HAL) && !defined (CY_USING_HAL_LITE)
#define peri_0_group_1_div_8_0_HW CY_SYSCLK_DIV_8_BIT
#endif /* !defined (CY_USING_HAL) && !defined (CY_USING_HAL_LITE) */

#define peri_0_group_1_div_8_0_NUM 0U
#define PERI_0_GROUP_1_DIV_8_0_GRP_NUM ((1U << PERI_PCLK_GR_NUM_Pos) | (0U << PERI_PCLK_INST_NUM_Pos))

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t CYBSP_TRACE_CLK_DIV_obj;
extern const cyhal_resource_inst_t peri_0_group_1_div_8_0_obj;
#endif /* defined (CY_USING_HAL) */

void init_cycfg_clocks(void);
void reserve_cycfg_clocks(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_CLOCKS_H */
