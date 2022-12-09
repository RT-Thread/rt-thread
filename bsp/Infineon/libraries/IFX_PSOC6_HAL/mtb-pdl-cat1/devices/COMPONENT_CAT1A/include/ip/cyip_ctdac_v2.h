/***************************************************************************//**
* \file cyip_ctdac_v2.h
*
* \brief
* CTDAC IP definitions
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

#ifndef _CYIP_CTDAC_V2_H_
#define _CYIP_CTDAC_V2_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    CTDAC
*******************************************************************************/

#define CTDAC_V2_SECTION_SIZE                   0x00010000UL

/**
  * \brief Continuous Time DAC (CTDAC)
  */
typedef struct {
  __IOM uint32_t CTDAC_CTRL;                    /*!< 0x00000000 Global CTDAC control */
   __IM uint32_t RESERVED[7];
  __IOM uint32_t INTR;                          /*!< 0x00000020 Interrupt request register */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000024 Interrupt request set register */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000028 Interrupt request mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000002C Interrupt request masked */
   __IM uint32_t RESERVED1[32];
  __IOM uint32_t CTDAC_SW;                      /*!< 0x000000B0 CTDAC switch control */
  __IOM uint32_t CTDAC_SW_CLEAR;                /*!< 0x000000B4 CTDAC switch control clear */
   __IM uint32_t RESERVED2[18];
  __IOM uint32_t CTDAC_VAL;                     /*!< 0x00000100 DAC Value */
  __IOM uint32_t CTDAC_VAL_NXT;                 /*!< 0x00000104 Next DAC value (double buffering) */
} CTDAC_V2_Type;                                /*!< Size = 264 (0x108) */


/* CTDAC.CTDAC_CTRL */
#define CTDAC_V2_CTDAC_CTRL_DEGLITCH_CNT_Pos    0UL
#define CTDAC_V2_CTDAC_CTRL_DEGLITCH_CNT_Msk    0x3FUL
#define CTDAC_V2_CTDAC_CTRL_DEGLITCH_CO6_Pos    8UL
#define CTDAC_V2_CTDAC_CTRL_DEGLITCH_CO6_Msk    0x100UL
#define CTDAC_V2_CTDAC_CTRL_DEGLITCH_COS_Pos    9UL
#define CTDAC_V2_CTDAC_CTRL_DEGLITCH_COS_Msk    0x200UL
#define CTDAC_V2_CTDAC_CTRL_OUT_EN_Pos          22UL
#define CTDAC_V2_CTDAC_CTRL_OUT_EN_Msk          0x400000UL
#define CTDAC_V2_CTDAC_CTRL_CTDAC_RANGE_Pos     23UL
#define CTDAC_V2_CTDAC_CTRL_CTDAC_RANGE_Msk     0x800000UL
#define CTDAC_V2_CTDAC_CTRL_CTDAC_MODE_Pos      24UL
#define CTDAC_V2_CTDAC_CTRL_CTDAC_MODE_Msk      0x3000000UL
#define CTDAC_V2_CTDAC_CTRL_DISABLED_MODE_Pos   27UL
#define CTDAC_V2_CTDAC_CTRL_DISABLED_MODE_Msk   0x8000000UL
#define CTDAC_V2_CTDAC_CTRL_DSI_STROBE_EN_Pos   28UL
#define CTDAC_V2_CTDAC_CTRL_DSI_STROBE_EN_Msk   0x10000000UL
#define CTDAC_V2_CTDAC_CTRL_DSI_STROBE_LEVEL_Pos 29UL
#define CTDAC_V2_CTDAC_CTRL_DSI_STROBE_LEVEL_Msk 0x20000000UL
#define CTDAC_V2_CTDAC_CTRL_DEEPSLEEP_ON_Pos    30UL
#define CTDAC_V2_CTDAC_CTRL_DEEPSLEEP_ON_Msk    0x40000000UL
#define CTDAC_V2_CTDAC_CTRL_ENABLED_Pos         31UL
#define CTDAC_V2_CTDAC_CTRL_ENABLED_Msk         0x80000000UL
/* CTDAC.INTR */
#define CTDAC_V2_INTR_VDAC_EMPTY_Pos            0UL
#define CTDAC_V2_INTR_VDAC_EMPTY_Msk            0x1UL
/* CTDAC.INTR_SET */
#define CTDAC_V2_INTR_SET_VDAC_EMPTY_SET_Pos    0UL
#define CTDAC_V2_INTR_SET_VDAC_EMPTY_SET_Msk    0x1UL
/* CTDAC.INTR_MASK */
#define CTDAC_V2_INTR_MASK_VDAC_EMPTY_MASK_Pos  0UL
#define CTDAC_V2_INTR_MASK_VDAC_EMPTY_MASK_Msk  0x1UL
/* CTDAC.INTR_MASKED */
#define CTDAC_V2_INTR_MASKED_VDAC_EMPTY_MASKED_Pos 0UL
#define CTDAC_V2_INTR_MASKED_VDAC_EMPTY_MASKED_Msk 0x1UL
/* CTDAC.CTDAC_SW */
#define CTDAC_V2_CTDAC_SW_CTDD_CVD_Pos          0UL
#define CTDAC_V2_CTDAC_SW_CTDD_CVD_Msk          0x1UL
#define CTDAC_V2_CTDAC_SW_CTDO_CO6_Pos          8UL
#define CTDAC_V2_CTDAC_SW_CTDO_CO6_Msk          0x100UL
/* CTDAC.CTDAC_SW_CLEAR */
#define CTDAC_V2_CTDAC_SW_CLEAR_CTDD_CVD_Pos    0UL
#define CTDAC_V2_CTDAC_SW_CLEAR_CTDD_CVD_Msk    0x1UL
#define CTDAC_V2_CTDAC_SW_CLEAR_CTDO_CO6_Pos    8UL
#define CTDAC_V2_CTDAC_SW_CLEAR_CTDO_CO6_Msk    0x100UL
/* CTDAC.CTDAC_VAL */
#define CTDAC_V2_CTDAC_VAL_VALUE_Pos            0UL
#define CTDAC_V2_CTDAC_VAL_VALUE_Msk            0xFFFUL
/* CTDAC.CTDAC_VAL_NXT */
#define CTDAC_V2_CTDAC_VAL_NXT_VALUE_Pos        0UL
#define CTDAC_V2_CTDAC_VAL_NXT_VALUE_Msk        0xFFFUL


#endif /* _CYIP_CTDAC_V2_H_ */


/* [] END OF FILE */
