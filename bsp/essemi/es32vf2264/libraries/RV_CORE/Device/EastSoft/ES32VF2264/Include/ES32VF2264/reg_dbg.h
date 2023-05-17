/**********************************************************************************
 *
 * @file    reg_dbg.h
 * @brief   DBG Head File
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

#ifndef __REG_DBG_H__
#define __REG_DBG_H__

/****************** Bit definition for DBGC_IDCODE register ************************/

#define DBGC_IDCODE_REV_ID_POSS 16U
#define DBGC_IDCODE_REV_ID_POSE 31U
#define DBGC_IDCODE_REV_ID_MSK  BITS(DBGC_IDCODE_REV_ID_POSS,DBGC_IDCODE_REV_ID_POSE)

#define DBGC_IDCODE_CORE_ID_POSS    12U
#define DBGC_IDCODE_CORE_ID_POSE    15U
#define DBGC_IDCODE_CORE_ID_MSK BITS(DBGC_IDCODE_CORE_ID_POSS,DBGC_IDCODE_CORE_ID_POSE)

#define DBGC_IDCODE_DEV_ID_POSS 0U
#define DBGC_IDCODE_DEV_ID_POSE 11U
#define DBGC_IDCODE_DEV_ID_MSK  BITS(DBGC_IDCODE_DEV_ID_POSS,DBGC_IDCODE_DEV_ID_POSE)

/****************** Bit definition for DBGC_APB1FZ register ************************/

#define DBGC_APB1FZ_GP16C2T2_STOP_POS   4U
#define DBGC_APB1FZ_GP16C2T2_STOP_MSK   BIT(DBGC_APB1FZ_GP16C2T2_STOP_POS)

#define DBGC_APB1FZ_GP16C2T1_STOP_POS   3U
#define DBGC_APB1FZ_GP16C2T1_STOP_MSK   BIT(DBGC_APB1FZ_GP16C2T1_STOP_POS)

#define DBGC_APB1FZ_GP16C2T0_STOP_POS   2U
#define DBGC_APB1FZ_GP16C2T0_STOP_MSK   BIT(DBGC_APB1FZ_GP16C2T0_STOP_POS)

#define DBGC_APB1FZ_BS16T0_STOP_POS 1U
#define DBGC_APB1FZ_BS16T0_STOP_MSK BIT(DBGC_APB1FZ_BS16T0_STOP_POS)

#define DBGC_APB1FZ_AD16C4T0_STOP_POS   0U
#define DBGC_APB1FZ_AD16C4T0_STOP_MSK   BIT(DBGC_APB1FZ_AD16C4T0_STOP_POS)

/****************** Bit definition for DBGC_APB2FZ register ************************/

#define DBGC_APB2FZ_WWDT_STOP_POS   9U
#define DBGC_APB2FZ_WWDT_STOP_MSK   BIT(DBGC_APB2FZ_WWDT_STOP_POS)

#define DBGC_APB2FZ_IWDT_STOP_POS   8U
#define DBGC_APB2FZ_IWDT_STOP_MSK   BIT(DBGC_APB2FZ_IWDT_STOP_POS)

#define DBGC_APB2FZ_I2C0_STOP_POS   0U
#define DBGC_APB2FZ_I2C0_STOP_MSK   BIT(DBGC_APB2FZ_I2C0_STOP_POS)

typedef struct
{
    __I uint32_t IDCODE;
    uint32_t RESERVED0 ;
    __IO uint32_t APB1FZ;
    __IO uint32_t APB2FZ;
} DBGC_TypeDef;





#endif /* __REG_DBG_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
