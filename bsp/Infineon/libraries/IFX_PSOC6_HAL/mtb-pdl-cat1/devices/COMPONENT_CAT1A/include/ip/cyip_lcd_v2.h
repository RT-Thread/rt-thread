/***************************************************************************//**
* \file cyip_lcd_v2.h
*
* \brief
* LCD IP definitions
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

#ifndef _CYIP_LCD_V2_H_
#define _CYIP_LCD_V2_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     LCD
*******************************************************************************/

#define LCD_V2_SECTION_SIZE                     0x00010000UL

/**
  * \brief LCD Controller Block (LCD)
  */
typedef struct {
   __IM uint32_t ID;                            /*!< 0x00000000 ID & Revision */
  __IOM uint32_t DIVIDER;                       /*!< 0x00000004 LCD Divider Register */
  __IOM uint32_t CONTROL;                       /*!< 0x00000008 LCD Configuration Register */
   __IM uint32_t RESERVED[61];
  __IOM uint32_t DATA0[8];                      /*!< 0x00000100 LCD Pin Data Registers */
   __IM uint32_t RESERVED1[56];
  __IOM uint32_t DATA1[8];                      /*!< 0x00000200 LCD Pin Data Registers */
   __IM uint32_t RESERVED2[56];
  __IOM uint32_t DATA2[8];                      /*!< 0x00000300 LCD Pin Data Registers */
   __IM uint32_t RESERVED3[56];
  __IOM uint32_t DATA3[8];                      /*!< 0x00000400 LCD Pin Data Registers */
} LCD_V2_Type;                                  /*!< Size = 1056 (0x420) */


/* LCD.ID */
#define LCD_V2_ID_ID_Pos                        0UL
#define LCD_V2_ID_ID_Msk                        0xFFFFUL
#define LCD_V2_ID_REVISION_Pos                  16UL
#define LCD_V2_ID_REVISION_Msk                  0xFFFF0000UL
/* LCD.DIVIDER */
#define LCD_V2_DIVIDER_SUBFR_DIV_Pos            0UL
#define LCD_V2_DIVIDER_SUBFR_DIV_Msk            0xFFFFUL
#define LCD_V2_DIVIDER_DEAD_DIV_Pos             16UL
#define LCD_V2_DIVIDER_DEAD_DIV_Msk             0xFFFF0000UL
/* LCD.CONTROL */
#define LCD_V2_CONTROL_LS_EN_Pos                0UL
#define LCD_V2_CONTROL_LS_EN_Msk                0x1UL
#define LCD_V2_CONTROL_HS_EN_Pos                1UL
#define LCD_V2_CONTROL_HS_EN_Msk                0x2UL
#define LCD_V2_CONTROL_LCD_MODE_Pos             2UL
#define LCD_V2_CONTROL_LCD_MODE_Msk             0x4UL
#define LCD_V2_CONTROL_TYPE_Pos                 3UL
#define LCD_V2_CONTROL_TYPE_Msk                 0x8UL
#define LCD_V2_CONTROL_OP_MODE_Pos              4UL
#define LCD_V2_CONTROL_OP_MODE_Msk              0x10UL
#define LCD_V2_CONTROL_BIAS_Pos                 5UL
#define LCD_V2_CONTROL_BIAS_Msk                 0x60UL
#define LCD_V2_CONTROL_CLOCK_LS_SEL_Pos         7UL
#define LCD_V2_CONTROL_CLOCK_LS_SEL_Msk         0x80UL
#define LCD_V2_CONTROL_COM_NUM_Pos              8UL
#define LCD_V2_CONTROL_COM_NUM_Msk              0xF00UL
#define LCD_V2_CONTROL_LS_EN_STAT_Pos           31UL
#define LCD_V2_CONTROL_LS_EN_STAT_Msk           0x80000000UL
/* LCD.DATA0 */
#define LCD_V2_DATA0_DATA_Pos                   0UL
#define LCD_V2_DATA0_DATA_Msk                   0xFFFFFFFFUL
/* LCD.DATA1 */
#define LCD_V2_DATA1_DATA_Pos                   0UL
#define LCD_V2_DATA1_DATA_Msk                   0xFFFFFFFFUL
/* LCD.DATA2 */
#define LCD_V2_DATA2_DATA_Pos                   0UL
#define LCD_V2_DATA2_DATA_Msk                   0xFFFFFFFFUL
/* LCD.DATA3 */
#define LCD_V2_DATA3_DATA_Pos                   0UL
#define LCD_V2_DATA3_DATA_Msk                   0xFFFFFFFFUL


#endif /* _CYIP_LCD_V2_H_ */


/* [] END OF FILE */
