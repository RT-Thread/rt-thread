/**********************************************************************************
 *
 * @file    reg_wwdt.h
 * @brief   WWDT Head File
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

#ifndef __REG_WWDT_H__
#define __REG_WWDT_H__

/****************** Bit definition for WWDT_LOAD register ************************/

#define WWDT_LOAD_LOAD_POSS 0U
#define WWDT_LOAD_LOAD_POSE 31U
#define WWDT_LOAD_LOAD_MSK  BITS(WWDT_LOAD_LOAD_POSS,WWDT_LOAD_LOAD_POSE)

/****************** Bit definition for WWDT_VALUE register ************************/

#define WWDT_VALUE_VALUE_POSS   0U
#define WWDT_VALUE_VALUE_POSE   31U
#define WWDT_VALUE_VALUE_MSK    BITS(WWDT_VALUE_VALUE_POSS,WWDT_VALUE_VALUE_POSE)

/****************** Bit definition for WWDT_CON register ************************/

#define WWDT_CON_WWDTWIN_POSS   4U
#define WWDT_CON_WWDTWIN_POSE   5U
#define WWDT_CON_WWDTWIN_MSK    BITS(WWDT_CON_WWDTWIN_POSS,WWDT_CON_WWDTWIN_POSE)

#define WWDT_CON_CLKS_POS   3U
#define WWDT_CON_CLKS_MSK   BIT(WWDT_CON_CLKS_POS)

#define WWDT_CON_RSTEN_POS  2U
#define WWDT_CON_RSTEN_MSK  BIT(WWDT_CON_RSTEN_POS)

#define WWDT_CON_IE_POS 1U
#define WWDT_CON_IE_MSK BIT(WWDT_CON_IE_POS)

#define WWDT_CON_EN_POS 0U
#define WWDT_CON_EN_MSK BIT(WWDT_CON_EN_POS)

/****************** Bit definition for WWDT_INTCLR register ************************/

#define WWDT_INTCLR_INTCLR_POSS 0U
#define WWDT_INTCLR_INTCLR_POSE 31U
#define WWDT_INTCLR_INTCLR_MSK  BITS(WWDT_INTCLR_INTCLR_POSS,WWDT_INTCLR_INTCLR_POSE)

/****************** Bit definition for WWDT_RIS register ************************/

#define WWDT_RIS_WWDTIF_POS 0U
#define WWDT_RIS_WWDTIF_MSK BIT(WWDT_RIS_WWDTIF_POS)

/****************** Bit definition for WWDT_LOCK register ************************/

#define WWDT_LOCK_LOCK_POS  0U
#define WWDT_LOCK_LOCK_MSK  BIT(WWDT_LOCK_LOCK_POS)

typedef struct
{
    __O uint32_t LOAD;
    __I uint32_t VALUE;
    __IO uint32_t CON;
    __O uint32_t INTCLR;
    __I uint32_t RIS;
    uint32_t RESERVED0[59] ;
    __IO uint32_t LOCK;
} WWDT_TypeDef;





#endif /* __REG_WWDT_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
