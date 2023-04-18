/***************************************************************************//**
* \file cyip_peri_pclk_v3.h
*
* \brief
* PERI_PCLK IP definitions
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

#ifndef _CYIP_PERI_PCLK_V3_H_
#define _CYIP_PERI_PCLK_V3_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                  PERI_PCLK
*******************************************************************************/

#define PERI_PCLK_GR_SECTION_SIZE               0x00002000UL
#define PERI_PCLK_SECTION_SIZE                  0x00020000UL

/**
  * \brief PERI clock domains (PERI_PCLK_GR)
  */
typedef struct {
  __IOM uint32_t DIV_CMD;                       /*!< 0x00000000 Divider command */
   __IM uint32_t RESERVED[767];
  __IOM uint32_t CLOCK_CTL[256];                /*!< 0x00000C00 Clock control */
  __IOM uint32_t DIV_8_CTL[256];                /*!< 0x00001000 Divider control (for 8.0 divider) */
  __IOM uint32_t DIV_16_CTL[256];               /*!< 0x00001400 Divider control (for 16.0 divider) */
  __IOM uint32_t DIV_16_5_CTL[256];             /*!< 0x00001800 Divider control (for 16.5 divider) */
  __IOM uint32_t DIV_24_5_CTL[255];             /*!< 0x00001C00 Divider control (for 24.5 divider) */
   __IM uint32_t RESERVED1;
} PERI_PCLK_GR_Type;                            /*!< Size = 8192 (0x2000) */

/**
  * \brief Peripheral PCLK groups (PERI_PCLK)
  */
typedef struct {
        PERI_PCLK_GR_Type GR[16];               /*!< 0x00000000 PERI clock domains */
} PERI_PCLK_Type;                               /*!< Size = 131072 (0x20000) */


/* PERI_PCLK_GR.DIV_CMD */
#define PERI_PCLK_GR_DIV_CMD_DIV_SEL_Pos        0UL
#define PERI_PCLK_GR_DIV_CMD_DIV_SEL_Msk        0xFFUL
#define PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Pos       8UL
#define PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Msk       0x300UL
#define PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Pos     16UL
#define PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Msk     0xFF0000UL
#define PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Pos    24UL
#define PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Msk    0x3000000UL
#define PERI_PCLK_GR_DIV_CMD_DISABLE_Pos        30UL
#define PERI_PCLK_GR_DIV_CMD_DISABLE_Msk        0x40000000UL
#define PERI_PCLK_GR_DIV_CMD_ENABLE_Pos         31UL
#define PERI_PCLK_GR_DIV_CMD_ENABLE_Msk         0x80000000UL
/* PERI_PCLK_GR.CLOCK_CTL */
#define PERI_PCLK_GR_CLOCK_CTL_DIV_SEL_Pos      0UL
#define PERI_PCLK_GR_CLOCK_CTL_DIV_SEL_Msk      0xFFUL
#define PERI_PCLK_GR_CLOCK_CTL_TYPE_SEL_Pos     8UL
#define PERI_PCLK_GR_CLOCK_CTL_TYPE_SEL_Msk     0x300UL
/* PERI_PCLK_GR.DIV_8_CTL */
#define PERI_PCLK_GR_DIV_8_CTL_EN_Pos           0UL
#define PERI_PCLK_GR_DIV_8_CTL_EN_Msk           0x1UL
#define PERI_PCLK_GR_DIV_8_CTL_INT8_DIV_Pos     8UL
#define PERI_PCLK_GR_DIV_8_CTL_INT8_DIV_Msk     0xFF00UL
/* PERI_PCLK_GR.DIV_16_CTL */
#define PERI_PCLK_GR_DIV_16_CTL_EN_Pos          0UL
#define PERI_PCLK_GR_DIV_16_CTL_EN_Msk          0x1UL
#define PERI_PCLK_GR_DIV_16_CTL_INT16_DIV_Pos   8UL
#define PERI_PCLK_GR_DIV_16_CTL_INT16_DIV_Msk   0xFFFF00UL
/* PERI_PCLK_GR.DIV_16_5_CTL */
#define PERI_PCLK_GR_DIV_16_5_CTL_EN_Pos        0UL
#define PERI_PCLK_GR_DIV_16_5_CTL_EN_Msk        0x1UL
#define PERI_PCLK_GR_DIV_16_5_CTL_FRAC5_DIV_Pos 3UL
#define PERI_PCLK_GR_DIV_16_5_CTL_FRAC5_DIV_Msk 0xF8UL
#define PERI_PCLK_GR_DIV_16_5_CTL_INT16_DIV_Pos 8UL
#define PERI_PCLK_GR_DIV_16_5_CTL_INT16_DIV_Msk 0xFFFF00UL
/* PERI_PCLK_GR.DIV_24_5_CTL */
#define PERI_PCLK_GR_DIV_24_5_CTL_EN_Pos        0UL
#define PERI_PCLK_GR_DIV_24_5_CTL_EN_Msk        0x1UL
#define PERI_PCLK_GR_DIV_24_5_CTL_FRAC5_DIV_Pos 3UL
#define PERI_PCLK_GR_DIV_24_5_CTL_FRAC5_DIV_Msk 0xF8UL
#define PERI_PCLK_GR_DIV_24_5_CTL_INT24_DIV_Pos 8UL
#define PERI_PCLK_GR_DIV_24_5_CTL_INT24_DIV_Msk 0xFFFFFF00UL


#endif /* _CYIP_PERI_PCLK_V3_H_ */


/* [] END OF FILE */
