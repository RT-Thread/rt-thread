/***************************************************************************//**
* \file cyip_ramc.h
*
* \brief
* RAMC IP definitions
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

#ifndef _CYIP_RAMC_H_
#define _CYIP_RAMC_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     RAMC
*******************************************************************************/

#define RAMC_MPC_SECTION_SIZE                   0x00001000UL
#define RAMC_SECTION_SIZE                       0x00010000UL

/**
  * \brief MPC Memory Protection Controller registers (RAMC_MPC)
  */
typedef struct {
  __IOM uint32_t CFG;                           /*!< 0x00000000 Config register with error response, RegionID PPC_MPC_MAIN is
                                                                the security owner PC. The error response configuration is
                                                                located in CFG.RESPONSE, only one such configuration exists
                                                                applying to all protection contexts in the system. */
   __IM uint32_t RESERVED[3];
  __IOM uint32_t INTR;                          /*!< 0x00000010 Interrupt */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000014 Interrupt set */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000018 Interrupt mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000001C Interrupt masked */
   __IM uint32_t INTR_INFO1;                    /*!< 0x00000020 Infor about violation */
   __IM uint32_t INTR_INFO2;                    /*!< 0x00000024 Infor about violation */
   __IM uint32_t RESERVED1[54];
  __IOM uint32_t CTRL;                          /*!< 0x00000100 Control register with lock bit and auto-increment only
                                                                (Separate CTRL for each PC depends on access_pc) */
   __IM uint32_t BLK_MAX;                       /*!< 0x00000104 Max value of block-based index register */
   __IM uint32_t BLK_CFG;                       /*!< 0x00000108 Block size & initialization in progress */
  __IOM uint32_t BLK_IDX;                       /*!< 0x0000010C Index of 32-block group accessed through BLK_LUT (Separate IDX
                                                                for each PC depending on access_pc) */
  __IOM uint32_t BLK_LUT;                       /*!< 0x00000110 NS status for 32 blocks at BLK_IDX with PC=<access_pc> */
   __IM uint32_t RESERVED2[59];
  __IOM uint32_t ROT_CTRL;                      /*!< 0x00000200 Control register with lock bit and auto-increment only */
  __IOM uint32_t ROT_CFG;                       /*!< 0x00000204 Sets block-size to match memory size (external memory only) */
   __IM uint32_t ROT_BLK_MAX;                   /*!< 0x00000208 Max value of block-based index register for ROT */
   __IM uint32_t ROT_BLK_CFG;                   /*!< 0x0000020C Same as BLK_CFG */
  __IOM uint32_t ROT_BLK_IDX;                   /*!< 0x00000210 Index of 8-block group accessed through ROT_BLK_LUT_* */
  __IOM uint32_t ROT_BLK_PC;                    /*!< 0x00000214 Protection context of 8-block group accesses through
                                                                ROT_BLK_LUT */
  __IOM uint32_t ROT_BLK_LUT;                   /*!< 0x00000218 (R,W,NS) bits for 8 blocks at ROT_BLK_IDX for PC=ROT_BKL_PC */
   __IM uint32_t RESERVED3[889];
} RAMC_MPC_Type;                                /*!< Size = 4096 (0x1000) */

/**
  * \brief RAMC0/1/2 (RAMC)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
   __IM uint32_t RESERVED;
   __IM uint32_t STATUS;                        /*!< 0x00000008 Status */
   __IM uint32_t RESERVED1[5];
  __IOM uint32_t ECC_CTL;                       /*!< 0x00000020 ECC control */
  __IOM uint32_t ECC_MATCH;                     /*!< 0x00000024 ECC match */
   __IM uint32_t ECC_STATUS0;                   /*!< 0x00000028 ECC status 0 */
   __IM uint32_t ECC_STATUS1;                   /*!< 0x0000002C ECC status 1 */
   __IM uint32_t RESERVED2[116];
  __IOM uint32_t PWR_MACRO_CTL;                 /*!< 0x00000200 SRAM power partition power control */
   __IM uint32_t RESERVED3[15];
  __IOM uint32_t PWR_MACRO_CTL_LOCK;            /*!< 0x00000240 SRAM power partition power control Lock */
   __IM uint32_t RESERVED4[15];
  __IOM uint32_t PWR_DELAY_CTL;                 /*!< 0x00000280 SRAM power switch power up & sequence delay */
   __IM uint32_t RESERVED5[3935];
        RAMC_MPC_Type MPC[1];                   /*!< 0x00004000 MPC Memory Protection Controller registers */
} RAMC_Type;                                    /*!< Size = 20480 (0x5000) */


/* RAMC_MPC.CFG */
#define RAMC_MPC_CFG_RESPONSE_Pos               4UL
#define RAMC_MPC_CFG_RESPONSE_Msk               0x10UL
/* RAMC_MPC.INTR */
#define RAMC_MPC_INTR_VIOLATION_Pos             0UL
#define RAMC_MPC_INTR_VIOLATION_Msk             0x1UL
/* RAMC_MPC.INTR_SET */
#define RAMC_MPC_INTR_SET_VIOLATION_Pos         0UL
#define RAMC_MPC_INTR_SET_VIOLATION_Msk         0x1UL
/* RAMC_MPC.INTR_MASK */
#define RAMC_MPC_INTR_MASK_VIOLATION_Pos        0UL
#define RAMC_MPC_INTR_MASK_VIOLATION_Msk        0x1UL
/* RAMC_MPC.INTR_MASKED */
#define RAMC_MPC_INTR_MASKED_VIOLATION_Pos      0UL
#define RAMC_MPC_INTR_MASKED_VIOLATION_Msk      0x1UL
/* RAMC_MPC.INTR_INFO1 */
#define RAMC_MPC_INTR_INFO1_VALUE_Pos           0UL
#define RAMC_MPC_INTR_INFO1_VALUE_Msk           0xFFFFFFFFUL
/* RAMC_MPC.INTR_INFO2 */
#define RAMC_MPC_INTR_INFO2_HMASTER_Pos         0UL
#define RAMC_MPC_INTR_INFO2_HMASTER_Msk         0xFFFFUL
#define RAMC_MPC_INTR_INFO2_HNONSEC_Pos         16UL
#define RAMC_MPC_INTR_INFO2_HNONSEC_Msk         0x10000UL
#define RAMC_MPC_INTR_INFO2_CFG_NS_Pos          17UL
#define RAMC_MPC_INTR_INFO2_CFG_NS_Msk          0x20000UL
#define RAMC_MPC_INTR_INFO2_HWRITE_Pos          18UL
#define RAMC_MPC_INTR_INFO2_HWRITE_Msk          0x40000UL
#define RAMC_MPC_INTR_INFO2_HAUSER_Pos          24UL
#define RAMC_MPC_INTR_INFO2_HAUSER_Msk          0xF000000UL
#define RAMC_MPC_INTR_INFO2_SECURITY_VIOLATION_Pos 30UL
#define RAMC_MPC_INTR_INFO2_SECURITY_VIOLATION_Msk 0x40000000UL
#define RAMC_MPC_INTR_INFO2_ACCESS_VIOLATION_Pos 31UL
#define RAMC_MPC_INTR_INFO2_ACCESS_VIOLATION_Msk 0x80000000UL
/* RAMC_MPC.CTRL */
#define RAMC_MPC_CTRL_AUTO_INC_Pos              8UL
#define RAMC_MPC_CTRL_AUTO_INC_Msk              0x100UL
#define RAMC_MPC_CTRL_LOCK_Pos                  31UL
#define RAMC_MPC_CTRL_LOCK_Msk                  0x80000000UL
/* RAMC_MPC.BLK_MAX */
#define RAMC_MPC_BLK_MAX_VALUE_Pos              0UL
#define RAMC_MPC_BLK_MAX_VALUE_Msk              0xFFFFFFFFUL
/* RAMC_MPC.BLK_CFG */
#define RAMC_MPC_BLK_CFG_BLOCK_SIZE_Pos         0UL
#define RAMC_MPC_BLK_CFG_BLOCK_SIZE_Msk         0xFUL
#define RAMC_MPC_BLK_CFG_INIT_IN_PROGRESS_Pos   31UL
#define RAMC_MPC_BLK_CFG_INIT_IN_PROGRESS_Msk   0x80000000UL
/* RAMC_MPC.BLK_IDX */
#define RAMC_MPC_BLK_IDX_VALUE_Pos              0UL
#define RAMC_MPC_BLK_IDX_VALUE_Msk              0xFFFFFFFFUL
/* RAMC_MPC.BLK_LUT */
#define RAMC_MPC_BLK_LUT_ATTR_NS0_Pos           0UL
#define RAMC_MPC_BLK_LUT_ATTR_NS0_Msk           0x1UL
#define RAMC_MPC_BLK_LUT_ATTR_NS1_Pos           1UL
#define RAMC_MPC_BLK_LUT_ATTR_NS1_Msk           0x2UL
#define RAMC_MPC_BLK_LUT_ATTR_NS2_Pos           2UL
#define RAMC_MPC_BLK_LUT_ATTR_NS2_Msk           0x4UL
#define RAMC_MPC_BLK_LUT_ATTR_NS3_Pos           3UL
#define RAMC_MPC_BLK_LUT_ATTR_NS3_Msk           0x8UL
#define RAMC_MPC_BLK_LUT_ATTR_NS4_Pos           4UL
#define RAMC_MPC_BLK_LUT_ATTR_NS4_Msk           0x10UL
#define RAMC_MPC_BLK_LUT_ATTR_NS5_Pos           5UL
#define RAMC_MPC_BLK_LUT_ATTR_NS5_Msk           0x20UL
#define RAMC_MPC_BLK_LUT_ATTR_NS6_Pos           6UL
#define RAMC_MPC_BLK_LUT_ATTR_NS6_Msk           0x40UL
#define RAMC_MPC_BLK_LUT_ATTR_NS7_Pos           7UL
#define RAMC_MPC_BLK_LUT_ATTR_NS7_Msk           0x80UL
#define RAMC_MPC_BLK_LUT_ATTR_NS8_Pos           8UL
#define RAMC_MPC_BLK_LUT_ATTR_NS8_Msk           0x100UL
#define RAMC_MPC_BLK_LUT_ATTR_NS9_Pos           9UL
#define RAMC_MPC_BLK_LUT_ATTR_NS9_Msk           0x200UL
#define RAMC_MPC_BLK_LUT_ATTR_NS10_Pos          10UL
#define RAMC_MPC_BLK_LUT_ATTR_NS10_Msk          0x400UL
#define RAMC_MPC_BLK_LUT_ATTR_NS11_Pos          11UL
#define RAMC_MPC_BLK_LUT_ATTR_NS11_Msk          0x800UL
#define RAMC_MPC_BLK_LUT_ATTR_NS12_Pos          12UL
#define RAMC_MPC_BLK_LUT_ATTR_NS12_Msk          0x1000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS13_Pos          13UL
#define RAMC_MPC_BLK_LUT_ATTR_NS13_Msk          0x2000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS14_Pos          14UL
#define RAMC_MPC_BLK_LUT_ATTR_NS14_Msk          0x4000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS15_Pos          15UL
#define RAMC_MPC_BLK_LUT_ATTR_NS15_Msk          0x8000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS16_Pos          16UL
#define RAMC_MPC_BLK_LUT_ATTR_NS16_Msk          0x10000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS17_Pos          17UL
#define RAMC_MPC_BLK_LUT_ATTR_NS17_Msk          0x20000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS18_Pos          18UL
#define RAMC_MPC_BLK_LUT_ATTR_NS18_Msk          0x40000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS19_Pos          19UL
#define RAMC_MPC_BLK_LUT_ATTR_NS19_Msk          0x80000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS20_Pos          20UL
#define RAMC_MPC_BLK_LUT_ATTR_NS20_Msk          0x100000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS21_Pos          21UL
#define RAMC_MPC_BLK_LUT_ATTR_NS21_Msk          0x200000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS22_Pos          22UL
#define RAMC_MPC_BLK_LUT_ATTR_NS22_Msk          0x400000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS23_Pos          23UL
#define RAMC_MPC_BLK_LUT_ATTR_NS23_Msk          0x800000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS24_Pos          24UL
#define RAMC_MPC_BLK_LUT_ATTR_NS24_Msk          0x1000000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS25_Pos          25UL
#define RAMC_MPC_BLK_LUT_ATTR_NS25_Msk          0x2000000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS26_Pos          26UL
#define RAMC_MPC_BLK_LUT_ATTR_NS26_Msk          0x4000000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS27_Pos          27UL
#define RAMC_MPC_BLK_LUT_ATTR_NS27_Msk          0x8000000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS28_Pos          28UL
#define RAMC_MPC_BLK_LUT_ATTR_NS28_Msk          0x10000000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS29_Pos          29UL
#define RAMC_MPC_BLK_LUT_ATTR_NS29_Msk          0x20000000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS30_Pos          30UL
#define RAMC_MPC_BLK_LUT_ATTR_NS30_Msk          0x40000000UL
#define RAMC_MPC_BLK_LUT_ATTR_NS31_Pos          31UL
#define RAMC_MPC_BLK_LUT_ATTR_NS31_Msk          0x80000000UL
/* RAMC_MPC.ROT_CTRL */
#define RAMC_MPC_ROT_CTRL_AUTO_INC_Pos          8UL
#define RAMC_MPC_ROT_CTRL_AUTO_INC_Msk          0x100UL
#define RAMC_MPC_ROT_CTRL_LOCK_Pos              31UL
#define RAMC_MPC_ROT_CTRL_LOCK_Msk              0x80000000UL
/* RAMC_MPC.ROT_CFG */
#define RAMC_MPC_ROT_CFG_BLOCK_SIZE_Pos         0UL
#define RAMC_MPC_ROT_CFG_BLOCK_SIZE_Msk         0xFUL
/* RAMC_MPC.ROT_BLK_MAX */
#define RAMC_MPC_ROT_BLK_MAX_VALUE_Pos          0UL
#define RAMC_MPC_ROT_BLK_MAX_VALUE_Msk          0xFFFFFFFFUL
/* RAMC_MPC.ROT_BLK_CFG */
#define RAMC_MPC_ROT_BLK_CFG_BLOCK_SIZE_Pos     0UL
#define RAMC_MPC_ROT_BLK_CFG_BLOCK_SIZE_Msk     0xFUL
#define RAMC_MPC_ROT_BLK_CFG_INIT_IN_PROGRESS_Pos 31UL
#define RAMC_MPC_ROT_BLK_CFG_INIT_IN_PROGRESS_Msk 0x80000000UL
/* RAMC_MPC.ROT_BLK_IDX */
#define RAMC_MPC_ROT_BLK_IDX_VALUE_Pos          0UL
#define RAMC_MPC_ROT_BLK_IDX_VALUE_Msk          0xFFFFFFFFUL
/* RAMC_MPC.ROT_BLK_PC */
#define RAMC_MPC_ROT_BLK_PC_PC_Pos              0UL
#define RAMC_MPC_ROT_BLK_PC_PC_Msk              0xFUL
/* RAMC_MPC.ROT_BLK_LUT */
#define RAMC_MPC_ROT_BLK_LUT_ATTR0_Pos          0UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR0_Msk          0x7UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR1_Pos          4UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR1_Msk          0x70UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR2_Pos          8UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR2_Msk          0x700UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR3_Pos          12UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR3_Msk          0x7000UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR4_Pos          16UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR4_Msk          0x70000UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR5_Pos          20UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR5_Msk          0x700000UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR6_Pos          24UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR6_Msk          0x7000000UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR7_Pos          28UL
#define RAMC_MPC_ROT_BLK_LUT_ATTR7_Msk          0x70000000UL


/* RAMC.CTL */
#define RAMC_CTL_SRAM_WS_Pos                    0UL
#define RAMC_CTL_SRAM_WS_Msk                    0x3UL
#define RAMC_CTL_CLOCK_FORCE_Pos                16UL
#define RAMC_CTL_CLOCK_FORCE_Msk                0x10000UL
/* RAMC.STATUS */
#define RAMC_STATUS_WB_EMPTY_Pos                0UL
#define RAMC_STATUS_WB_EMPTY_Msk                0x1UL
#define RAMC_STATUS_PWR_DONE_Pos                4UL
#define RAMC_STATUS_PWR_DONE_Msk                0x10UL
/* RAMC.ECC_CTL */
#define RAMC_ECC_CTL_EN_Pos                     0UL
#define RAMC_ECC_CTL_EN_Msk                     0x1UL
#define RAMC_ECC_CTL_AUTO_CORRECT_Pos           1UL
#define RAMC_ECC_CTL_AUTO_CORRECT_Msk           0x2UL
#define RAMC_ECC_CTL_INJ_EN_Pos                 2UL
#define RAMC_ECC_CTL_INJ_EN_Msk                 0x4UL
#define RAMC_ECC_CTL_CHECK_EN_Pos               3UL
#define RAMC_ECC_CTL_CHECK_EN_Msk               0x8UL
#define RAMC_ECC_CTL_PARITY_Pos                 16UL
#define RAMC_ECC_CTL_PARITY_Msk                 0x7F0000UL
/* RAMC.ECC_MATCH */
#define RAMC_ECC_MATCH_WORD_ADDR_Pos            0UL
#define RAMC_ECC_MATCH_WORD_ADDR_Msk            0x1FFFFFFUL
/* RAMC.ECC_STATUS0 */
#define RAMC_ECC_STATUS0_ADDR_Pos               0UL
#define RAMC_ECC_STATUS0_ADDR_Msk               0xFFFFFFFFUL
/* RAMC.ECC_STATUS1 */
#define RAMC_ECC_STATUS1_SYNDROME_Pos           0UL
#define RAMC_ECC_STATUS1_SYNDROME_Msk           0x7FUL
/* RAMC.PWR_MACRO_CTL */
#define RAMC_PWR_MACRO_CTL_OFF_Pos              0UL
#define RAMC_PWR_MACRO_CTL_OFF_Msk              0xFFFFFFFFUL
/* RAMC.PWR_MACRO_CTL_LOCK */
#define RAMC_PWR_MACRO_CTL_LOCK_PWR_MACRO_CTL_LOCK_Pos 0UL
#define RAMC_PWR_MACRO_CTL_LOCK_PWR_MACRO_CTL_LOCK_Msk 0x3UL
/* RAMC.PWR_DELAY_CTL */
#define RAMC_PWR_DELAY_CTL_UP_Pos               0UL
#define RAMC_PWR_DELAY_CTL_UP_Msk               0x3FFUL
#define RAMC_PWR_DELAY_CTL_SEQ0_DELAY_Pos       16UL
#define RAMC_PWR_DELAY_CTL_SEQ0_DELAY_Msk       0xFF0000UL
#define RAMC_PWR_DELAY_CTL_SEQ1_DELAY_Pos       24UL
#define RAMC_PWR_DELAY_CTL_SEQ1_DELAY_Msk       0xFF000000UL


#endif /* _CYIP_RAMC_H_ */


/* [] END OF FILE */
