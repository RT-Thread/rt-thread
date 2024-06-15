/**********************************************************************************
 *
 * @file    reg_crc.h
 * @brief   CRC Head File
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

#ifndef __REG_CRC_H__
#define __REG_CRC_H__

/****************** Bit definition for CRC_CR register ************************/

#define CRC_CR_BYTORD_POS   24U
#define CRC_CR_BYTORD_MSK   BIT(CRC_CR_BYTORD_POS)

#define CRC_CR_DATLEN_POSS  22U
#define CRC_CR_DATLEN_POSE  23U
#define CRC_CR_DATLEN_MSK   BITS(CRC_CR_DATLEN_POSS,CRC_CR_DATLEN_POSE)

#define CRC_CR_MODE_POSS    20U
#define CRC_CR_MODE_POSE    21U
#define CRC_CR_MODE_MSK BITS(CRC_CR_MODE_POSS,CRC_CR_MODE_POSE)

#define CRC_CR_CHSINV_POS   19U
#define CRC_CR_CHSINV_MSK   BIT(CRC_CR_CHSINV_POS)

#define CRC_CR_DATINV_POS   18U
#define CRC_CR_DATINV_MSK   BIT(CRC_CR_DATINV_POS)

#define CRC_CR_CHSREV_POS   17U
#define CRC_CR_CHSREV_MSK   BIT(CRC_CR_CHSREV_POS)

#define CRC_CR_DATREV_POS   16U
#define CRC_CR_DATREV_MSK   BIT(CRC_CR_DATREV_POS)

#define CRC_CR_DMAEN_POS    4U
#define CRC_CR_DMAEN_MSK    BIT(CRC_CR_DMAEN_POS)

#define CRC_CR_CWERR_POS    3U
#define CRC_CR_CWERR_MSK    BIT(CRC_CR_CWERR_POS)

#define CRC_CR_WERR_POS 2U
#define CRC_CR_WERR_MSK BIT(CRC_CR_WERR_POS)

#define CRC_CR_RST_POS  1U
#define CRC_CR_RST_MSK  BIT(CRC_CR_RST_POS)

#define CRC_CR_EN_POS   0U
#define CRC_CR_EN_MSK   BIT(CRC_CR_EN_POS)

/****************** Bit definition for CRC_DATA register ************************/

#define CRC_DATA_DATA_POSS  0U
#define CRC_DATA_DATA_POSE  31U
#define CRC_DATA_DATA_MSK   BITS(CRC_DATA_DATA_POSS,CRC_DATA_DATA_POSE)

/****************** Bit definition for CRC_SEED register ************************/

#define CRC_SEED_SEED_POSS  0U
#define CRC_SEED_SEED_POSE  31U
#define CRC_SEED_SEED_MSK   BITS(CRC_SEED_SEED_POSS,CRC_SEED_SEED_POSE)

/****************** Bit definition for CRC_CHECKSUM register ************************/

#define CRC_CHECKSUM_CHECKSUM_POSS  0U
#define CRC_CHECKSUM_CHECKSUM_POSE  31U
#define CRC_CHECKSUM_CHECKSUM_MSK   BITS(CRC_CHECKSUM_CHECKSUM_POSS,CRC_CHECKSUM_CHECKSUM_POSE)

typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t DATA;
    __IO uint32_t SEED;
    __I uint32_t CHECKSUM;
} CRC_TypeDef;





#endif /* __REG_CRC_H__ */
