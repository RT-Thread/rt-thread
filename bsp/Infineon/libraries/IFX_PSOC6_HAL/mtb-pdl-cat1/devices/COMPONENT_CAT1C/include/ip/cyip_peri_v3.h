/***************************************************************************//**
* \file cyip_peri_v3.h
*
* \brief
* PERI IP definitions
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

#ifndef _CYIP_PERI_V3_H_
#define _CYIP_PERI_V3_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     PERI
*******************************************************************************/

#define PERI_GR_SECTION_SIZE                    0x00000040UL
#define PERI_TR_GR_SECTION_SIZE                 0x00000400UL
#define PERI_TR_1TO1_GR_SECTION_SIZE            0x00000400UL
#define PERI_SECTION_SIZE                       0x00010000UL

/**
  * \brief Peripheral group structure (PERI_GR)
  */
typedef struct {
  __IOM uint32_t CLOCK_CTL;                     /*!< 0x00000000 Clock control */
   __IM uint32_t RESERVED[3];
  __IOM uint32_t SL_CTL;                        /*!< 0x00000010 Slave control */
   __IM uint32_t RESERVED1[11];
} PERI_GR_Type;                                 /*!< Size = 64 (0x40) */

/**
  * \brief Trigger group (PERI_TR_GR)
  */
typedef struct {
  __IOM uint32_t TR_CTL[256];                   /*!< 0x00000000 Trigger control register */
} PERI_TR_GR_Type;                              /*!< Size = 1024 (0x400) */

/**
  * \brief Trigger 1-to-1 group (PERI_TR_1TO1_GR)
  */
typedef struct {
  __IOM uint32_t TR_CTL[256];                   /*!< 0x00000000 Trigger control register */
} PERI_TR_1TO1_GR_Type;                         /*!< Size = 1024 (0x400) */

/**
  * \brief Peripheral interconnect (PERI)
  */
typedef struct {
   __IM uint32_t RESERVED[128];
  __IOM uint32_t TIMEOUT_CTL;                   /*!< 0x00000200 Timeout control */
   __IM uint32_t RESERVED1[7];
  __IOM uint32_t TR_CMD;                        /*!< 0x00000220 Trigger command */
   __IM uint32_t RESERVED2[1911];
  __IOM uint32_t ECC_CTL;                       /*!< 0x00002000 ECC control */
   __IM uint32_t RESERVED3[2047];
        PERI_GR_Type GR[16];                    /*!< 0x00004000 Peripheral group structure */
   __IM uint32_t RESERVED4[3840];
        PERI_TR_GR_Type TR_GR[16];              /*!< 0x00008000 Trigger group */
        PERI_TR_1TO1_GR_Type TR_1TO1_GR[16];    /*!< 0x0000C000 Trigger 1-to-1 group */
} PERI_Type;                                    /*!< Size = 65536 (0x10000) */


/* PERI_GR.CLOCK_CTL */
#define PERI_GR_CLOCK_CTL_INT8_DIV_Pos          8UL
#define PERI_GR_CLOCK_CTL_INT8_DIV_Msk          0xFF00UL
/* PERI_GR.SL_CTL */
#define PERI_GR_SL_CTL_ENABLED_0_Pos            0UL
#define PERI_GR_SL_CTL_ENABLED_0_Msk            0x1UL
#define PERI_GR_SL_CTL_ENABLED_1_Pos            1UL
#define PERI_GR_SL_CTL_ENABLED_1_Msk            0x2UL
#define PERI_GR_SL_CTL_ENABLED_2_Pos            2UL
#define PERI_GR_SL_CTL_ENABLED_2_Msk            0x4UL
#define PERI_GR_SL_CTL_ENABLED_3_Pos            3UL
#define PERI_GR_SL_CTL_ENABLED_3_Msk            0x8UL
#define PERI_GR_SL_CTL_ENABLED_4_Pos            4UL
#define PERI_GR_SL_CTL_ENABLED_4_Msk            0x10UL
#define PERI_GR_SL_CTL_ENABLED_5_Pos            5UL
#define PERI_GR_SL_CTL_ENABLED_5_Msk            0x20UL
#define PERI_GR_SL_CTL_ENABLED_6_Pos            6UL
#define PERI_GR_SL_CTL_ENABLED_6_Msk            0x40UL
#define PERI_GR_SL_CTL_ENABLED_7_Pos            7UL
#define PERI_GR_SL_CTL_ENABLED_7_Msk            0x80UL
#define PERI_GR_SL_CTL_ENABLED_8_Pos            8UL
#define PERI_GR_SL_CTL_ENABLED_8_Msk            0x100UL
#define PERI_GR_SL_CTL_ENABLED_9_Pos            9UL
#define PERI_GR_SL_CTL_ENABLED_9_Msk            0x200UL
#define PERI_GR_SL_CTL_ENABLED_10_Pos           10UL
#define PERI_GR_SL_CTL_ENABLED_10_Msk           0x400UL
#define PERI_GR_SL_CTL_ENABLED_11_Pos           11UL
#define PERI_GR_SL_CTL_ENABLED_11_Msk           0x800UL
#define PERI_GR_SL_CTL_ENABLED_12_Pos           12UL
#define PERI_GR_SL_CTL_ENABLED_12_Msk           0x1000UL
#define PERI_GR_SL_CTL_ENABLED_13_Pos           13UL
#define PERI_GR_SL_CTL_ENABLED_13_Msk           0x2000UL
#define PERI_GR_SL_CTL_ENABLED_14_Pos           14UL
#define PERI_GR_SL_CTL_ENABLED_14_Msk           0x4000UL
#define PERI_GR_SL_CTL_ENABLED_15_Pos           15UL
#define PERI_GR_SL_CTL_ENABLED_15_Msk           0x8000UL


/* PERI_TR_GR.TR_CTL */
#define PERI_TR_GR_TR_CTL_TR_SEL_Pos            0UL
#define PERI_TR_GR_TR_CTL_TR_SEL_Msk            0xFFUL
#define PERI_TR_GR_TR_CTL_TR_INV_Pos            8UL
#define PERI_TR_GR_TR_CTL_TR_INV_Msk            0x100UL
#define PERI_TR_GR_TR_CTL_TR_EDGE_Pos           9UL
#define PERI_TR_GR_TR_CTL_TR_EDGE_Msk           0x200UL
#define PERI_TR_GR_TR_CTL_DBG_FREEZE_EN_Pos     12UL
#define PERI_TR_GR_TR_CTL_DBG_FREEZE_EN_Msk     0x1000UL


/* PERI_TR_1TO1_GR.TR_CTL */
#define PERI_TR_1TO1_GR_TR_CTL_TR_SEL_Pos       0UL
#define PERI_TR_1TO1_GR_TR_CTL_TR_SEL_Msk       0x1UL
#define PERI_TR_1TO1_GR_TR_CTL_TR_INV_Pos       8UL
#define PERI_TR_1TO1_GR_TR_CTL_TR_INV_Msk       0x100UL
#define PERI_TR_1TO1_GR_TR_CTL_TR_EDGE_Pos      9UL
#define PERI_TR_1TO1_GR_TR_CTL_TR_EDGE_Msk      0x200UL
#define PERI_TR_1TO1_GR_TR_CTL_DBG_FREEZE_EN_Pos 12UL
#define PERI_TR_1TO1_GR_TR_CTL_DBG_FREEZE_EN_Msk 0x1000UL


/* PERI.TIMEOUT_CTL */
#define PERI_TIMEOUT_CTL_TIMEOUT_Pos            0UL
#define PERI_TIMEOUT_CTL_TIMEOUT_Msk            0xFFFFUL
/* PERI.TR_CMD */
#define PERI_TR_CMD_TR_SEL_Pos                  0UL
#define PERI_TR_CMD_TR_SEL_Msk                  0xFFUL
#define PERI_TR_CMD_GROUP_SEL_Pos               8UL
#define PERI_TR_CMD_GROUP_SEL_Msk               0x1F00UL
#define PERI_TR_CMD_TR_EDGE_Pos                 29UL
#define PERI_TR_CMD_TR_EDGE_Msk                 0x20000000UL
#define PERI_TR_CMD_OUT_SEL_Pos                 30UL
#define PERI_TR_CMD_OUT_SEL_Msk                 0x40000000UL
#define PERI_TR_CMD_ACTIVATE_Pos                31UL
#define PERI_TR_CMD_ACTIVATE_Msk                0x80000000UL
/* PERI.ECC_CTL */
#define PERI_ECC_CTL_WORD_ADDR_Pos              0UL
#define PERI_ECC_CTL_WORD_ADDR_Msk              0x7FFUL
#define PERI_ECC_CTL_ECC_EN_Pos                 16UL
#define PERI_ECC_CTL_ECC_EN_Msk                 0x10000UL
#define PERI_ECC_CTL_ECC_INJ_EN_Pos             18UL
#define PERI_ECC_CTL_ECC_INJ_EN_Msk             0x40000UL
#define PERI_ECC_CTL_PARITY_Pos                 24UL
#define PERI_ECC_CTL_PARITY_Msk                 0xFF000000UL


#endif /* _CYIP_PERI_V3_H_ */


/* [] END OF FILE */
