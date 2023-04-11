/***************************************************************************//**
* \file cyip_mxcm33.h
*
* \brief
* MXCM33 IP definitions
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

#ifndef _CYIP_MXCM33_H_
#define _CYIP_MXCM33_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    MXCM33
*******************************************************************************/

#define MXCM33_SECTION_SIZE                     0x00010000UL

/**
  * \brief MXCM33-0/1 (MXCM33)
  */
typedef struct {
  __IOM uint32_t CM33_CTL;                      /*!< 0x00000000 Control */
  __IOM uint32_t CM33_CMD;                      /*!< 0x00000004 Command */
   __IM uint32_t CM33_STATUS;                   /*!< 0x00000008 Status */
   __IM uint32_t RESERVED[13];
   __IM uint32_t CM33_INT_STATUS[16];           /*!< 0x00000040 CM33 interrupt status */
  __IOM uint32_t CM33_NMI_CTL[4];               /*!< 0x00000080 CM33 NMI control */
   __IM uint32_t RESERVED1[988];
  __IOM uint32_t CM33_S_VECTOR_TABLE_BASE;      /*!< 0x00001000 CM33 secure vector table base */
  __IOM uint32_t CM33_NS_VECTOR_TABLE_BASE;     /*!< 0x00001004 CM33 non-secure vector table base */
   __IM uint32_t RESERVED2[1022];
  __IOM uint32_t CM33_PC_CTL;                   /*!< 0x00002000 CM33 protection context control */
   __IM uint32_t RESERVED3[15];
  __IOM uint32_t CM33_PC0_HANDLER;              /*!< 0x00002040 CM33 protection context 0 handler */
  __IOM uint32_t CM33_PC1_HANDLER;              /*!< 0x00002044 CM33 protection context 1 handler */
  __IOM uint32_t CM33_PC2_HANDLER;              /*!< 0x00002048 CM33 protection context 2 handler */
  __IOM uint32_t CM33_PC3_HANDLER;              /*!< 0x0000204C CM33 protection context 3 handler */
   __IM uint32_t RESERVED4[6124];
  __IOM uint32_t CM33_SYSTEM_INT_CTL[1023];     /*!< 0x00008000 CM33 system interrupt control */
} MXCM33_Type;                                  /*!< Size = 36860 (0x8FFC) */


/* MXCM33.CM33_CTL */
#define MXCM33_CM33_CTL_CPU_WAIT_Pos            4UL
#define MXCM33_CM33_CTL_CPU_WAIT_Msk            0x10UL
#define MXCM33_CM33_CTL_LOCKNSVTOR_Pos          8UL
#define MXCM33_CM33_CTL_LOCKNSVTOR_Msk          0x100UL
#define MXCM33_CM33_CTL_LOCKSVTAIRCR_Pos        9UL
#define MXCM33_CM33_CTL_LOCKSVTAIRCR_Msk        0x200UL
#define MXCM33_CM33_CTL_LOCKSMPU_Pos            10UL
#define MXCM33_CM33_CTL_LOCKSMPU_Msk            0x400UL
#define MXCM33_CM33_CTL_LOCKNSMPU_Pos           11UL
#define MXCM33_CM33_CTL_LOCKNSMPU_Msk           0x800UL
#define MXCM33_CM33_CTL_LOCKSAU_Pos             12UL
#define MXCM33_CM33_CTL_LOCKSAU_Msk             0x1000UL
#define MXCM33_CM33_CTL_IOC_MASK_Pos            24UL
#define MXCM33_CM33_CTL_IOC_MASK_Msk            0x1000000UL
#define MXCM33_CM33_CTL_DZC_MASK_Pos            25UL
#define MXCM33_CM33_CTL_DZC_MASK_Msk            0x2000000UL
#define MXCM33_CM33_CTL_OFC_MASK_Pos            26UL
#define MXCM33_CM33_CTL_OFC_MASK_Msk            0x4000000UL
#define MXCM33_CM33_CTL_UFC_MASK_Pos            27UL
#define MXCM33_CM33_CTL_UFC_MASK_Msk            0x8000000UL
#define MXCM33_CM33_CTL_IXC_MASK_Pos            28UL
#define MXCM33_CM33_CTL_IXC_MASK_Msk            0x10000000UL
#define MXCM33_CM33_CTL_IDC_MASK_Pos            31UL
#define MXCM33_CM33_CTL_IDC_MASK_Msk            0x80000000UL
/* MXCM33.CM33_CMD */
#define MXCM33_CM33_CMD_ENABLED_Pos             1UL
#define MXCM33_CM33_CMD_ENABLED_Msk             0x2UL
#define MXCM33_CM33_CMD_VECTKEYSTAT_Pos         16UL
#define MXCM33_CM33_CMD_VECTKEYSTAT_Msk         0xFFFF0000UL
/* MXCM33.CM33_STATUS */
#define MXCM33_CM33_STATUS_SLEEPING_Pos         0UL
#define MXCM33_CM33_STATUS_SLEEPING_Msk         0x1UL
#define MXCM33_CM33_STATUS_SLEEPDEEP_Pos        1UL
#define MXCM33_CM33_STATUS_SLEEPDEEP_Msk        0x2UL
/* MXCM33.CM33_INT_STATUS */
#define MXCM33_CM33_INT_STATUS_SYSTEM_INT_IDX_Pos 0UL
#define MXCM33_CM33_INT_STATUS_SYSTEM_INT_IDX_Msk 0x3FFUL
#define MXCM33_CM33_INT_STATUS_SYSTEM_INT_VALID_Pos 31UL
#define MXCM33_CM33_INT_STATUS_SYSTEM_INT_VALID_Msk 0x80000000UL
/* MXCM33.CM33_NMI_CTL */
#define MXCM33_CM33_NMI_CTL_SYSTEM_INT_IDX_Pos  0UL
#define MXCM33_CM33_NMI_CTL_SYSTEM_INT_IDX_Msk  0x3FFUL
/* MXCM33.CM33_S_VECTOR_TABLE_BASE */
#define MXCM33_CM33_S_VECTOR_TABLE_BASE_ADDR25_Pos 7UL
#define MXCM33_CM33_S_VECTOR_TABLE_BASE_ADDR25_Msk 0xFFFFFF80UL
/* MXCM33.CM33_NS_VECTOR_TABLE_BASE */
#define MXCM33_CM33_NS_VECTOR_TABLE_BASE_ADDR25_Pos 7UL
#define MXCM33_CM33_NS_VECTOR_TABLE_BASE_ADDR25_Msk 0xFFFFFF80UL
/* MXCM33.CM33_PC_CTL */
#define MXCM33_CM33_PC_CTL_VALID_Pos            0UL
#define MXCM33_CM33_PC_CTL_VALID_Msk            0xFUL
/* MXCM33.CM33_PC0_HANDLER */
#define MXCM33_CM33_PC0_HANDLER_ADDR_Pos        0UL
#define MXCM33_CM33_PC0_HANDLER_ADDR_Msk        0xFFFFFFFFUL
/* MXCM33.CM33_PC1_HANDLER */
#define MXCM33_CM33_PC1_HANDLER_ADDR_Pos        0UL
#define MXCM33_CM33_PC1_HANDLER_ADDR_Msk        0xFFFFFFFFUL
/* MXCM33.CM33_PC2_HANDLER */
#define MXCM33_CM33_PC2_HANDLER_ADDR_Pos        0UL
#define MXCM33_CM33_PC2_HANDLER_ADDR_Msk        0xFFFFFFFFUL
/* MXCM33.CM33_PC3_HANDLER */
#define MXCM33_CM33_PC3_HANDLER_ADDR_Pos        0UL
#define MXCM33_CM33_PC3_HANDLER_ADDR_Msk        0xFFFFFFFFUL
/* MXCM33.CM33_SYSTEM_INT_CTL */
#define MXCM33_CM33_SYSTEM_INT_CTL_CPU_INT_IDX_Pos 0UL
#define MXCM33_CM33_SYSTEM_INT_CTL_CPU_INT_IDX_Msk 0xFUL
#define MXCM33_CM33_SYSTEM_INT_CTL_CPU_INT_VALID_Pos 31UL
#define MXCM33_CM33_SYSTEM_INT_CTL_CPU_INT_VALID_Msk 0x80000000UL


#endif /* _CYIP_MXCM33_H_ */


/* [] END OF FILE */
