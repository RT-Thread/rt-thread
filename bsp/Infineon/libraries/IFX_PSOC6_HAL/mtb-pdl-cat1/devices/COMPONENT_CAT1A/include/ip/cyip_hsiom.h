/***************************************************************************//**
* \file cyip_hsiom.h
*
* \brief
* HSIOM IP definitions
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
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

#ifndef _CYIP_HSIOM_H_
#define _CYIP_HSIOM_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    HSIOM
*******************************************************************************/

#define HSIOM_PRT_SECTION_SIZE                  0x00000010UL
#define HSIOM_SECTION_SIZE                      0x00004000UL

/**
  * \brief HSIOM port registers (HSIOM_PRT)
  */
typedef struct {
  __IOM uint32_t PORT_SEL0;                     /*!< 0x00000000 Port selection 0 */
  __IOM uint32_t PORT_SEL1;                     /*!< 0x00000004 Port selection 1 */
   __IM uint32_t RESERVED[2];
} HSIOM_PRT_V1_Type;                            /*!< Size = 16 (0x10) */

/**
  * \brief High Speed IO Matrix (HSIOM) (HSIOM)
  */
typedef struct {
        HSIOM_PRT_V1_Type PRT[128];             /*!< 0x00000000 HSIOM port registers */
   __IM uint32_t RESERVED[1536];
  __IOM uint32_t AMUX_SPLIT_CTL[64];            /*!< 0x00002000 AMUX splitter cell control */
} HSIOM_V1_Type;                                /*!< Size = 8448 (0x2100) */


/* HSIOM_PRT.PORT_SEL0 */
#define HSIOM_PRT_PORT_SEL0_IO0_SEL_Pos         0UL
#define HSIOM_PRT_PORT_SEL0_IO0_SEL_Msk         0x1FUL
#define HSIOM_PRT_PORT_SEL0_IO1_SEL_Pos         8UL
#define HSIOM_PRT_PORT_SEL0_IO1_SEL_Msk         0x1F00UL
#define HSIOM_PRT_PORT_SEL0_IO2_SEL_Pos         16UL
#define HSIOM_PRT_PORT_SEL0_IO2_SEL_Msk         0x1F0000UL
#define HSIOM_PRT_PORT_SEL0_IO3_SEL_Pos         24UL
#define HSIOM_PRT_PORT_SEL0_IO3_SEL_Msk         0x1F000000UL
/* HSIOM_PRT.PORT_SEL1 */
#define HSIOM_PRT_PORT_SEL1_IO4_SEL_Pos         0UL
#define HSIOM_PRT_PORT_SEL1_IO4_SEL_Msk         0x1FUL
#define HSIOM_PRT_PORT_SEL1_IO5_SEL_Pos         8UL
#define HSIOM_PRT_PORT_SEL1_IO5_SEL_Msk         0x1F00UL
#define HSIOM_PRT_PORT_SEL1_IO6_SEL_Pos         16UL
#define HSIOM_PRT_PORT_SEL1_IO6_SEL_Msk         0x1F0000UL
#define HSIOM_PRT_PORT_SEL1_IO7_SEL_Pos         24UL
#define HSIOM_PRT_PORT_SEL1_IO7_SEL_Msk         0x1F000000UL


/* HSIOM.AMUX_SPLIT_CTL */
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_Pos   0UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_Msk   0x1UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SR_Pos   1UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SR_Msk   0x2UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_S0_Pos   2UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_S0_Msk   0x4UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_Pos   4UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_Msk   0x10UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SR_Pos   5UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SR_Msk   0x20UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_S0_Pos   6UL
#define HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_S0_Msk   0x40UL


#endif /* _CYIP_HSIOM_H_ */


/* [] END OF FILE */
