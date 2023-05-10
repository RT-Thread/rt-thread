/**********************************************************************************
 *
 * @file    reg_iwdt.h
 * @brief   IWDT Head File
 *
 * @date    07 July 2022
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          07 July 2022    Lisq            the first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************
 */

#ifndef __REG_IWDT_H__
#define __REG_IWDT_H__

/****************** Bit definition for IWDT_LOAD register ************************/

#define IWDT_LOAD_LOAD_POSS 0U
#define IWDT_LOAD_LOAD_POSE 31U
#define IWDT_LOAD_LOAD_MSK  BITS(IWDT_LOAD_LOAD_POSS,IWDT_LOAD_LOAD_POSE)

/****************** Bit definition for IWDT_VALUE register ************************/

#define IWDT_VALUE_VALUE_POSS   0U
#define IWDT_VALUE_VALUE_POSE   31U
#define IWDT_VALUE_VALUE_MSK    BITS(IWDT_VALUE_VALUE_POSS,IWDT_VALUE_VALUE_POSE)

/****************** Bit definition for IWDT_CON register ************************/

#define IWDT_CON_CLKS_POS   3U
#define IWDT_CON_CLKS_MSK   BIT(IWDT_CON_CLKS_POS)

#define IWDT_CON_RSTEN_POS  2U
#define IWDT_CON_RSTEN_MSK  BIT(IWDT_CON_RSTEN_POS)

#define IWDT_CON_IE_POS 1U
#define IWDT_CON_IE_MSK BIT(IWDT_CON_IE_POS)

#define IWDT_CON_EN_POS 0U
#define IWDT_CON_EN_MSK BIT(IWDT_CON_EN_POS)

/****************** Bit definition for IWDT_INTCLR register ************************/

#define IWDT_INTCLR_INTCLR_POSS 0U
#define IWDT_INTCLR_INTCLR_POSE 31U
#define IWDT_INTCLR_INTCLR_MSK  BITS(IWDT_INTCLR_INTCLR_POSS,IWDT_INTCLR_INTCLR_POSE)

/****************** Bit definition for IWDT_RIS register ************************/

#define IWDT_RIS_WDTIF_POS  0U
#define IWDT_RIS_WDTIF_MSK  BIT(IWDT_RIS_WDTIF_POS)

/****************** Bit definition for IWDT_LOCK register ************************/

#define IWDT_LOCK_LOCK_POS  0U
#define IWDT_LOCK_LOCK_MSK  BIT(IWDT_LOCK_LOCK_POS)

typedef struct
{
    __O uint32_t LOAD;
    __I uint32_t VALUE;
    __IO uint32_t CON;
    __O uint32_t INTCLR;
    __I uint32_t RIS;
    uint32_t RESERVED0[59] ;
    __IO uint32_t LOCK;
} IWDT_TypeDef;





#endif /* __REG_IWDT_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
