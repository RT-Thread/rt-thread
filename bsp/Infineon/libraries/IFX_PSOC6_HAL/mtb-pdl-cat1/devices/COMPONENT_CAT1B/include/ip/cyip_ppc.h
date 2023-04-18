/***************************************************************************//**
* \file cyip_ppc.h
*
* \brief
* PPC IP definitions
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

#ifndef _CYIP_PPC_H_
#define _CYIP_PPC_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     PPC
*******************************************************************************/

#define PPC_R_ADDR_SECTION_SIZE                 0x00000004UL
#define PPC_R_ATT_SECTION_SIZE                  0x00000004UL
#define PPC_SECTION_SIZE                        0x00010000UL

/**
  * \brief Region Address (PPC_R_ADDR)
  */
typedef struct {
   __IM uint32_t R_ADDR;                        /*!< 0x00000000 Region Address */
} PPC_R_ADDR_Type;                              /*!< Size = 4 (0x4) */

/**
  * \brief Region Attribute (PPC_R_ATT)
  */
typedef struct {
   __IM uint32_t R_ATT;                         /*!< 0x00000000 Region Attribute */
} PPC_R_ATT_Type;                               /*!< Size = 4 (0x4) */

/**
  * \brief Peripheral Protection Controller (PPC)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 PPC Control Registers */
   __IM uint32_t STATUS1;                       /*!< 0x00000004 Status1 Register */
   __IM uint32_t STATUS2;                       /*!< 0x00000008 Status2 Register */
  __IOM uint32_t LOCK_MASK;                     /*!< 0x0000000C Locked Mask */
   __IM uint32_t RESERVED[4];
  __IOM uint32_t INTR_PPC;                      /*!< 0x00000020 Interrupt */
  __IOM uint32_t INTR_PPC_SET;                  /*!< 0x00000024 Interrupt set */
  __IOM uint32_t INTR_PPC_MASK;                 /*!< 0x00000028 Interrupt mask */
   __IM uint32_t INTR_PPC_MASKED;               /*!< 0x0000002C Interrupt masked */
   __IM uint32_t RESERVED1[1012];
  __IOM uint32_t PC_MASK[1024];                 /*!< 0x00001000 Protection Context Mask */
  __IOM uint32_t NS_ATT[32];                    /*!< 0x00002000 Non-secure attribute */
   __IM uint32_t RESERVED2[224];
  __IOM uint32_t S_P_ATT[32];                   /*!< 0x00002400 Secure Privilege Attribute */
   __IM uint32_t RESERVED3[1760];
  __IOM uint32_t NS_P_ATT[32];                  /*!< 0x00004000 Non-secure Privilege Attribute */
   __IM uint32_t RESERVED4[992];
        PPC_R_ADDR_Type R_ADDR[1024];           /*!< 0x00005000 Region Address */
        PPC_R_ATT_Type R_ATT[1024];             /*!< 0x00006000 Region Attribute */
} PPC_Type;                                     /*!< Size = 28672 (0x7000) */


/* PPC_R_ADDR.R_ADDR */
#define PPC_R_ADDR_R_ADDR_R_ADDR_Pos            2UL
#define PPC_R_ADDR_R_ADDR_R_ADDR_Msk            0xFFFFFFFCUL


/* PPC_R_ATT.R_ATT */
#define PPC_R_ATT_R_ATT_R_SIZE_Pos              24UL
#define PPC_R_ATT_R_ATT_R_SIZE_Msk              0x1F000000UL


/* PPC.CTL */
#define PPC_CTL_RESP_CFG_Pos                    0UL
#define PPC_CTL_RESP_CFG_Msk                    0x1UL
/* PPC.STATUS1 */
#define PPC_STATUS1_INDEX_Pos                   0UL
#define PPC_STATUS1_INDEX_Msk                   0x3FFUL
#define PPC_STATUS1_PC_Pos                      12UL
#define PPC_STATUS1_PC_Msk                      0xF000UL
#define PPC_STATUS1_TYPE_Pos                    16UL
#define PPC_STATUS1_TYPE_Msk                    0x70000UL
#define PPC_STATUS1_MS_Pos                      24UL
#define PPC_STATUS1_MS_Msk                      0xFF000000UL
/* PPC.STATUS2 */
#define PPC_STATUS2_ADDR_Pos                    0UL
#define PPC_STATUS2_ADDR_Msk                    0xFFFFFFFFUL
/* PPC.LOCK_MASK */
#define PPC_LOCK_MASK_LOCK_MASK_Pos             0UL
#define PPC_LOCK_MASK_LOCK_MASK_Msk             0xFFFFFFFFUL
/* PPC.INTR_PPC */
#define PPC_INTR_PPC_SECURE_VIO_Pos             0UL
#define PPC_INTR_PPC_SECURE_VIO_Msk             0x1UL
/* PPC.INTR_PPC_SET */
#define PPC_INTR_PPC_SET_SECURE_VIO_Pos         0UL
#define PPC_INTR_PPC_SET_SECURE_VIO_Msk         0x1UL
/* PPC.INTR_PPC_MASK */
#define PPC_INTR_PPC_MASK_SECURE_VIO_Pos        0UL
#define PPC_INTR_PPC_MASK_SECURE_VIO_Msk        0x1UL
/* PPC.INTR_PPC_MASKED */
#define PPC_INTR_PPC_MASKED_SECURE_VIO_Pos      0UL
#define PPC_INTR_PPC_MASKED_SECURE_VIO_Msk      0x1UL
/* PPC.PC_MASK */
#define PPC_PC_MASK_PC_MASK_Pos                 0UL
#define PPC_PC_MASK_PC_MASK_Msk                 0xFFFFFFFFUL
/* PPC.NS_ATT */
#define PPC_NS_ATT_NS_Pos                       0UL
#define PPC_NS_ATT_NS_Msk                       0xFFFFFFFFUL
/* PPC.S_P_ATT */
#define PPC_S_P_ATT_S_P_Pos                     0UL
#define PPC_S_P_ATT_S_P_Msk                     0xFFFFFFFFUL
/* PPC.NS_P_ATT */
#define PPC_NS_P_ATT_NS_P_Pos                   0UL
#define PPC_NS_P_ATT_NS_P_Msk                   0xFFFFFFFFUL


#endif /* _CYIP_PPC_H_ */


/* [] END OF FILE */
