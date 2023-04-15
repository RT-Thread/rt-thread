/***************************************************************************//**
* \file cyip_peri.h
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

#ifndef _CYIP_PERI_H_
#define _CYIP_PERI_H_

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
  __IOM uint32_t SL_CTL2;                       /*!< 0x00000014 Slave control2 */
   __IM uint32_t SL_CTL3;                       /*!< 0x00000018 Slave control3 */
   __IM uint32_t RESERVED1[9];
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
   __IM uint32_t RESERVED1[895];
   __IM uint32_t AHB_ERROR_STATUS1[16];         /*!< 0x00001000 AHB error status1 */
   __IM uint32_t AHB_ERROR_STATUS2[16];         /*!< 0x00001040 AHB error status2 */
   __IM uint32_t AHB_ERROR_STATUS3[16];         /*!< 0x00001080 AHB error status3 */
  __IOM uint32_t INTR_AHB_ERROR;                /*!< 0x000010C0 Interrupt AHB error */
  __IOM uint32_t INTR_AHB_ERROR_SET;            /*!< 0x000010C4 Interrupt AHB error set */
  __IOM uint32_t INTR_AHB_ERROR_MASK;           /*!< 0x000010C8 Interrupt AHB error mask */
   __IM uint32_t INTR_AHB_ERROR_MASKED;         /*!< 0x000010CC Interrupt AHB error masked */
   __IM uint32_t RESERVED2[972];
  __IOM uint32_t TR_CMD;                        /*!< 0x00002000 Trigger command */
  __IOM uint32_t INFRA_CLK_FORCE;               /*!< 0x00002004 Infrastructure clock force enable */
   __IM uint32_t RESERVED3[2046];
        PERI_GR_Type GR[16];                    /*!< 0x00004000 Peripheral group structure */
   __IM uint32_t RESERVED4[3840];
        PERI_TR_GR_Type TR_GR[16];              /*!< 0x00008000 Trigger group */
        PERI_TR_1TO1_GR_Type TR_1TO1_GR[16];    /*!< 0x0000C000 Trigger 1-to-1 group */
} PERI_Type;                                    /*!< Size = 65536 (0x10000) */


/* PERI_GR.CLOCK_CTL */
#define PERI_GR_CLOCK_CTL_INT8_DIV_Pos          8UL
#define PERI_GR_CLOCK_CTL_INT8_DIV_Msk          0xFF00UL
/* PERI_GR.SL_CTL */
#define PERI_GR_SL_CTL_ENABLED_Pos              0UL
#define PERI_GR_SL_CTL_ENABLED_Msk              0xFFFFFFFFUL
/* PERI_GR.SL_CTL2 */
#define PERI_GR_SL_CTL2_RST_Pos                 0UL
#define PERI_GR_SL_CTL2_RST_Msk                 0xFFFFFFFFUL
/* PERI_GR.SL_CTL3 */
#define PERI_GR_SL_CTL3_SS_POWERSTATE_Pos       0UL
#define PERI_GR_SL_CTL3_SS_POWERSTATE_Msk       0xFFFFFFFFUL


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
#define PERI_TIMEOUT_CTL_HWRST_DISABLE_Pos      31UL
#define PERI_TIMEOUT_CTL_HWRST_DISABLE_Msk      0x80000000UL
/* PERI.AHB_ERROR_STATUS1 */
#define PERI_AHB_ERROR_STATUS1_ADDR_Pos         0UL
#define PERI_AHB_ERROR_STATUS1_ADDR_Msk         0xFFFFFFFFUL
/* PERI.AHB_ERROR_STATUS2 */
#define PERI_AHB_ERROR_STATUS2_P_Pos            0UL
#define PERI_AHB_ERROR_STATUS2_P_Msk            0x1UL
#define PERI_AHB_ERROR_STATUS2_NS_Pos           1UL
#define PERI_AHB_ERROR_STATUS2_NS_Msk           0x2UL
#define PERI_AHB_ERROR_STATUS2_W_Pos            2UL
#define PERI_AHB_ERROR_STATUS2_W_Msk            0x4UL
#define PERI_AHB_ERROR_STATUS2_PC_Pos           4UL
#define PERI_AHB_ERROR_STATUS2_PC_Msk           0xF0UL
#define PERI_AHB_ERROR_STATUS2_MS_Pos           8UL
#define PERI_AHB_ERROR_STATUS2_MS_Msk           0xFFFF00UL
#define PERI_AHB_ERROR_STATUS2_TYPE_Pos         30UL
#define PERI_AHB_ERROR_STATUS2_TYPE_Msk         0xC0000000UL
/* PERI.AHB_ERROR_STATUS3 */
#define PERI_AHB_ERROR_STATUS3_SLAVE_NO_Pos     0UL
#define PERI_AHB_ERROR_STATUS3_SLAVE_NO_Msk     0x1FUL
/* PERI.INTR_AHB_ERROR */
#define PERI_INTR_AHB_ERROR_AHB_ERROR_VIO_Pos   0UL
#define PERI_INTR_AHB_ERROR_AHB_ERROR_VIO_Msk   0xFFFFUL
#define PERI_INTR_AHB_ERROR_TIMEOUT_VIO_Pos     17UL
#define PERI_INTR_AHB_ERROR_TIMEOUT_VIO_Msk     0xFFFE0000UL
/* PERI.INTR_AHB_ERROR_SET */
#define PERI_INTR_AHB_ERROR_SET_AHB_ERROR_VIO_Pos 0UL
#define PERI_INTR_AHB_ERROR_SET_AHB_ERROR_VIO_Msk 0xFFFFUL
#define PERI_INTR_AHB_ERROR_SET_TIMEOUT_VIO_Pos 17UL
#define PERI_INTR_AHB_ERROR_SET_TIMEOUT_VIO_Msk 0xFFFE0000UL
/* PERI.INTR_AHB_ERROR_MASK */
#define PERI_INTR_AHB_ERROR_MASK_AHB_ERROR_VIO_Pos 0UL
#define PERI_INTR_AHB_ERROR_MASK_AHB_ERROR_VIO_Msk 0xFFFFUL
#define PERI_INTR_AHB_ERROR_MASK_TIMEOUT_VIO_Pos 17UL
#define PERI_INTR_AHB_ERROR_MASK_TIMEOUT_VIO_Msk 0xFFFE0000UL
/* PERI.INTR_AHB_ERROR_MASKED */
#define PERI_INTR_AHB_ERROR_MASKED_AHB_ERROR_VIO_Pos 0UL
#define PERI_INTR_AHB_ERROR_MASKED_AHB_ERROR_VIO_Msk 0xFFFFUL
#define PERI_INTR_AHB_ERROR_MASKED_TIMEOUT_VIO_Pos 17UL
#define PERI_INTR_AHB_ERROR_MASKED_TIMEOUT_VIO_Msk 0xFFFE0000UL
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
/* PERI.INFRA_CLK_FORCE */
#define PERI_INFRA_CLK_FORCE_ENABLED_Pos        0UL
#define PERI_INFRA_CLK_FORCE_ENABLED_Msk        0x1UL


#endif /* _CYIP_PERI_H_ */


/* [] END OF FILE */
