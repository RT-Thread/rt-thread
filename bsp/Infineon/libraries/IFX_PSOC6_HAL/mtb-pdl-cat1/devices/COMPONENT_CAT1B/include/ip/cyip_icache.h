/***************************************************************************//**
* \file cyip_icache.h
*
* \brief
* ICACHE IP definitions
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

#ifndef _CYIP_ICACHE_H_
#define _CYIP_ICACHE_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    ICACHE
*******************************************************************************/

#define ICACHE_SECTION_SIZE                     0x00001000UL

/**
  * \brief CM33_0/1 CA APB interface (ICACHE)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Cache control */
   __IM uint32_t RESERVED;
  __IOM uint32_t CMD;                           /*!< 0x00000008 Cache command */
   __IM uint32_t RESERVED1[29];
   __IM uint32_t STATUS0;                       /*!< 0x00000080 Cache status 0 */
   __IM uint32_t STATUS1;                       /*!< 0x00000084 Cache status 1 */
   __IM uint32_t STATUS2;                       /*!< 0x00000088 Cache status 2 */
   __IM uint32_t RESERVED2[29];
  __IOM uint32_t ECC_CTL;                       /*!< 0x00000100 ECC control */
} ICACHE_Type;                                  /*!< Size = 260 (0x104) */


/* ICACHE.CTL */
#define ICACHE_CTL_ECC_EN_Pos                   0UL
#define ICACHE_CTL_ECC_EN_Msk                   0x1UL
#define ICACHE_CTL_ECC_INJ_EN_Pos               1UL
#define ICACHE_CTL_ECC_INJ_EN_Msk               0x2UL
#define ICACHE_CTL_WAY_Pos                      16UL
#define ICACHE_CTL_WAY_Msk                      0x30000UL
#define ICACHE_CTL_SET_ADDR_Pos                 24UL
#define ICACHE_CTL_SET_ADDR_Msk                 0x1F000000UL
#define ICACHE_CTL_PREF_EN_Pos                  30UL
#define ICACHE_CTL_PREF_EN_Msk                  0x40000000UL
#define ICACHE_CTL_CA_EN_Pos                    31UL
#define ICACHE_CTL_CA_EN_Msk                    0x80000000UL
/* ICACHE.CMD */
#define ICACHE_CMD_INV_Pos                      0UL
#define ICACHE_CMD_INV_Msk                      0x1UL
#define ICACHE_CMD_BUFF_INV_Pos                 1UL
#define ICACHE_CMD_BUFF_INV_Msk                 0x2UL
/* ICACHE.STATUS0 */
#define ICACHE_STATUS0_VALID32_Pos              0UL
#define ICACHE_STATUS0_VALID32_Msk              0xFFFFFFFFUL
/* ICACHE.STATUS1 */
#define ICACHE_STATUS1_TAG_Pos                  0UL
#define ICACHE_STATUS1_TAG_Msk                  0xFFFFFFFFUL
/* ICACHE.STATUS2 */
#define ICACHE_STATUS2_LRU_Pos                  0UL
#define ICACHE_STATUS2_LRU_Msk                  0x3FUL
/* ICACHE.ECC_CTL */
#define ICACHE_ECC_CTL_WORD_ADDR_Pos            0UL
#define ICACHE_ECC_CTL_WORD_ADDR_Msk            0xFFFFFFUL
#define ICACHE_ECC_CTL_PARITY_Pos               24UL
#define ICACHE_ECC_CTL_PARITY_Msk               0x7F000000UL


#endif /* _CYIP_ICACHE_H_ */


/* [] END OF FILE */
