/***************************************************************************//**
* \file cyip_promc.h
*
* \brief
* PROMC IP definitions
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

#ifndef _CYIP_PROMC_H_
#define _CYIP_PROMC_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    PROMC
*******************************************************************************/

#define PROMC_MPC_SECTION_SIZE                  0x00001000UL
#define PROMC_SECTION_SIZE                      0x00010000UL

/**
  * \brief MPC Memory Protection Controller registers (PROMC_MPC)
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
} PROMC_MPC_Type;                               /*!< Size = 4096 (0x1000) */

/**
  * \brief Patchable ROM Controller (PROMC)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
   __IM uint32_t RESERVED[63];
  __IOM uint32_t PATCH_CTL;                     /*!< 0x00000100 Patch control */
   __IM uint32_t PATCH_STATUS;                  /*!< 0x00000104 Patch status */
   __IM uint32_t RESERVED1[2];
   __IM uint32_t PATCH_CFG;                     /*!< 0x00000110 Patch design time configuration info */
   __IM uint32_t RESERVED2[3];
  __IOM uint32_t PATCH_SROM;                    /*!< 0x00000120 Patch SROM boundary */
   __IM uint32_t RESERVED3[439];
  __IOM uint32_t PATCH_STRUCT_CTL[512];         /*!< 0x00000800 Patch structure control */
        PROMC_MPC_Type MPC[1];                  /*!< 0x00001000 MPC Memory Protection Controller registers */
   __IM uint32_t RESERVED4[6144];
  __IOM uint32_t PATCH_DATA[8192];              /*!< 0x00008000 Patch data RAM */
} PROMC_Type;                                   /*!< Size = 65536 (0x10000) */


/* PROMC_MPC.CFG */
#define PROMC_MPC_CFG_RESPONSE_Pos              4UL
#define PROMC_MPC_CFG_RESPONSE_Msk              0x10UL
/* PROMC_MPC.INTR */
#define PROMC_MPC_INTR_VIOLATION_Pos            0UL
#define PROMC_MPC_INTR_VIOLATION_Msk            0x1UL
/* PROMC_MPC.INTR_SET */
#define PROMC_MPC_INTR_SET_VIOLATION_Pos        0UL
#define PROMC_MPC_INTR_SET_VIOLATION_Msk        0x1UL
/* PROMC_MPC.INTR_MASK */
#define PROMC_MPC_INTR_MASK_VIOLATION_Pos       0UL
#define PROMC_MPC_INTR_MASK_VIOLATION_Msk       0x1UL
/* PROMC_MPC.INTR_MASKED */
#define PROMC_MPC_INTR_MASKED_VIOLATION_Pos     0UL
#define PROMC_MPC_INTR_MASKED_VIOLATION_Msk     0x1UL
/* PROMC_MPC.INTR_INFO1 */
#define PROMC_MPC_INTR_INFO1_VALUE_Pos          0UL
#define PROMC_MPC_INTR_INFO1_VALUE_Msk          0xFFFFFFFFUL
/* PROMC_MPC.INTR_INFO2 */
#define PROMC_MPC_INTR_INFO2_HMASTER_Pos        0UL
#define PROMC_MPC_INTR_INFO2_HMASTER_Msk        0xFFFFUL
#define PROMC_MPC_INTR_INFO2_HNONSEC_Pos        16UL
#define PROMC_MPC_INTR_INFO2_HNONSEC_Msk        0x10000UL
#define PROMC_MPC_INTR_INFO2_CFG_NS_Pos         17UL
#define PROMC_MPC_INTR_INFO2_CFG_NS_Msk         0x20000UL
#define PROMC_MPC_INTR_INFO2_HWRITE_Pos         18UL
#define PROMC_MPC_INTR_INFO2_HWRITE_Msk         0x40000UL
#define PROMC_MPC_INTR_INFO2_HAUSER_Pos         24UL
#define PROMC_MPC_INTR_INFO2_HAUSER_Msk         0xF000000UL
#define PROMC_MPC_INTR_INFO2_SECURITY_VIOLATION_Pos 30UL
#define PROMC_MPC_INTR_INFO2_SECURITY_VIOLATION_Msk 0x40000000UL
#define PROMC_MPC_INTR_INFO2_ACCESS_VIOLATION_Pos 31UL
#define PROMC_MPC_INTR_INFO2_ACCESS_VIOLATION_Msk 0x80000000UL
/* PROMC_MPC.CTRL */
#define PROMC_MPC_CTRL_AUTO_INC_Pos             8UL
#define PROMC_MPC_CTRL_AUTO_INC_Msk             0x100UL
#define PROMC_MPC_CTRL_LOCK_Pos                 31UL
#define PROMC_MPC_CTRL_LOCK_Msk                 0x80000000UL
/* PROMC_MPC.BLK_MAX */
#define PROMC_MPC_BLK_MAX_VALUE_Pos             0UL
#define PROMC_MPC_BLK_MAX_VALUE_Msk             0xFFFFFFFFUL
/* PROMC_MPC.BLK_CFG */
#define PROMC_MPC_BLK_CFG_BLOCK_SIZE_Pos        0UL
#define PROMC_MPC_BLK_CFG_BLOCK_SIZE_Msk        0xFUL
#define PROMC_MPC_BLK_CFG_INIT_IN_PROGRESS_Pos  31UL
#define PROMC_MPC_BLK_CFG_INIT_IN_PROGRESS_Msk  0x80000000UL
/* PROMC_MPC.BLK_IDX */
#define PROMC_MPC_BLK_IDX_VALUE_Pos             0UL
#define PROMC_MPC_BLK_IDX_VALUE_Msk             0xFFFFFFFFUL
/* PROMC_MPC.BLK_LUT */
#define PROMC_MPC_BLK_LUT_ATTR_NS0_Pos          0UL
#define PROMC_MPC_BLK_LUT_ATTR_NS0_Msk          0x1UL
#define PROMC_MPC_BLK_LUT_ATTR_NS1_Pos          1UL
#define PROMC_MPC_BLK_LUT_ATTR_NS1_Msk          0x2UL
#define PROMC_MPC_BLK_LUT_ATTR_NS2_Pos          2UL
#define PROMC_MPC_BLK_LUT_ATTR_NS2_Msk          0x4UL
#define PROMC_MPC_BLK_LUT_ATTR_NS3_Pos          3UL
#define PROMC_MPC_BLK_LUT_ATTR_NS3_Msk          0x8UL
#define PROMC_MPC_BLK_LUT_ATTR_NS4_Pos          4UL
#define PROMC_MPC_BLK_LUT_ATTR_NS4_Msk          0x10UL
#define PROMC_MPC_BLK_LUT_ATTR_NS5_Pos          5UL
#define PROMC_MPC_BLK_LUT_ATTR_NS5_Msk          0x20UL
#define PROMC_MPC_BLK_LUT_ATTR_NS6_Pos          6UL
#define PROMC_MPC_BLK_LUT_ATTR_NS6_Msk          0x40UL
#define PROMC_MPC_BLK_LUT_ATTR_NS7_Pos          7UL
#define PROMC_MPC_BLK_LUT_ATTR_NS7_Msk          0x80UL
#define PROMC_MPC_BLK_LUT_ATTR_NS8_Pos          8UL
#define PROMC_MPC_BLK_LUT_ATTR_NS8_Msk          0x100UL
#define PROMC_MPC_BLK_LUT_ATTR_NS9_Pos          9UL
#define PROMC_MPC_BLK_LUT_ATTR_NS9_Msk          0x200UL
#define PROMC_MPC_BLK_LUT_ATTR_NS10_Pos         10UL
#define PROMC_MPC_BLK_LUT_ATTR_NS10_Msk         0x400UL
#define PROMC_MPC_BLK_LUT_ATTR_NS11_Pos         11UL
#define PROMC_MPC_BLK_LUT_ATTR_NS11_Msk         0x800UL
#define PROMC_MPC_BLK_LUT_ATTR_NS12_Pos         12UL
#define PROMC_MPC_BLK_LUT_ATTR_NS12_Msk         0x1000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS13_Pos         13UL
#define PROMC_MPC_BLK_LUT_ATTR_NS13_Msk         0x2000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS14_Pos         14UL
#define PROMC_MPC_BLK_LUT_ATTR_NS14_Msk         0x4000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS15_Pos         15UL
#define PROMC_MPC_BLK_LUT_ATTR_NS15_Msk         0x8000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS16_Pos         16UL
#define PROMC_MPC_BLK_LUT_ATTR_NS16_Msk         0x10000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS17_Pos         17UL
#define PROMC_MPC_BLK_LUT_ATTR_NS17_Msk         0x20000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS18_Pos         18UL
#define PROMC_MPC_BLK_LUT_ATTR_NS18_Msk         0x40000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS19_Pos         19UL
#define PROMC_MPC_BLK_LUT_ATTR_NS19_Msk         0x80000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS20_Pos         20UL
#define PROMC_MPC_BLK_LUT_ATTR_NS20_Msk         0x100000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS21_Pos         21UL
#define PROMC_MPC_BLK_LUT_ATTR_NS21_Msk         0x200000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS22_Pos         22UL
#define PROMC_MPC_BLK_LUT_ATTR_NS22_Msk         0x400000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS23_Pos         23UL
#define PROMC_MPC_BLK_LUT_ATTR_NS23_Msk         0x800000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS24_Pos         24UL
#define PROMC_MPC_BLK_LUT_ATTR_NS24_Msk         0x1000000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS25_Pos         25UL
#define PROMC_MPC_BLK_LUT_ATTR_NS25_Msk         0x2000000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS26_Pos         26UL
#define PROMC_MPC_BLK_LUT_ATTR_NS26_Msk         0x4000000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS27_Pos         27UL
#define PROMC_MPC_BLK_LUT_ATTR_NS27_Msk         0x8000000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS28_Pos         28UL
#define PROMC_MPC_BLK_LUT_ATTR_NS28_Msk         0x10000000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS29_Pos         29UL
#define PROMC_MPC_BLK_LUT_ATTR_NS29_Msk         0x20000000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS30_Pos         30UL
#define PROMC_MPC_BLK_LUT_ATTR_NS30_Msk         0x40000000UL
#define PROMC_MPC_BLK_LUT_ATTR_NS31_Pos         31UL
#define PROMC_MPC_BLK_LUT_ATTR_NS31_Msk         0x80000000UL
/* PROMC_MPC.ROT_CTRL */
#define PROMC_MPC_ROT_CTRL_AUTO_INC_Pos         8UL
#define PROMC_MPC_ROT_CTRL_AUTO_INC_Msk         0x100UL
#define PROMC_MPC_ROT_CTRL_LOCK_Pos             31UL
#define PROMC_MPC_ROT_CTRL_LOCK_Msk             0x80000000UL
/* PROMC_MPC.ROT_CFG */
#define PROMC_MPC_ROT_CFG_BLOCK_SIZE_Pos        0UL
#define PROMC_MPC_ROT_CFG_BLOCK_SIZE_Msk        0xFUL
/* PROMC_MPC.ROT_BLK_MAX */
#define PROMC_MPC_ROT_BLK_MAX_VALUE_Pos         0UL
#define PROMC_MPC_ROT_BLK_MAX_VALUE_Msk         0xFFFFFFFFUL
/* PROMC_MPC.ROT_BLK_CFG */
#define PROMC_MPC_ROT_BLK_CFG_BLOCK_SIZE_Pos    0UL
#define PROMC_MPC_ROT_BLK_CFG_BLOCK_SIZE_Msk    0xFUL
#define PROMC_MPC_ROT_BLK_CFG_INIT_IN_PROGRESS_Pos 31UL
#define PROMC_MPC_ROT_BLK_CFG_INIT_IN_PROGRESS_Msk 0x80000000UL
/* PROMC_MPC.ROT_BLK_IDX */
#define PROMC_MPC_ROT_BLK_IDX_VALUE_Pos         0UL
#define PROMC_MPC_ROT_BLK_IDX_VALUE_Msk         0xFFFFFFFFUL
/* PROMC_MPC.ROT_BLK_PC */
#define PROMC_MPC_ROT_BLK_PC_PC_Pos             0UL
#define PROMC_MPC_ROT_BLK_PC_PC_Msk             0xFUL
/* PROMC_MPC.ROT_BLK_LUT */
#define PROMC_MPC_ROT_BLK_LUT_ATTR0_Pos         0UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR0_Msk         0x7UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR1_Pos         4UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR1_Msk         0x70UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR2_Pos         8UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR2_Msk         0x700UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR3_Pos         12UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR3_Msk         0x7000UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR4_Pos         16UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR4_Msk         0x70000UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR5_Pos         20UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR5_Msk         0x700000UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR6_Pos         24UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR6_Msk         0x7000000UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR7_Pos         28UL
#define PROMC_MPC_ROT_BLK_LUT_ATTR7_Msk         0x70000000UL


/* PROMC.CTL */
#define PROMC_CTL_ROM_WS_Pos                    0UL
#define PROMC_CTL_ROM_WS_Msk                    0x3UL
/* PROMC.PATCH_CTL */
#define PROMC_PATCH_CTL_ENABLED_Pos             31UL
#define PROMC_PATCH_CTL_ENABLED_Msk             0x80000000UL
/* PROMC.PATCH_STATUS */
#define PROMC_PATCH_STATUS_PATCH_IDX_Pos        0UL
#define PROMC_PATCH_STATUS_PATCH_IDX_Msk        0x1FFUL
#define PROMC_PATCH_STATUS_PATCH_VALID_Pos      31UL
#define PROMC_PATCH_STATUS_PATCH_VALID_Msk      0x80000000UL
/* PROMC.PATCH_CFG */
#define PROMC_PATCH_CFG_PATCH_NR_Pos            0UL
#define PROMC_PATCH_CFG_PATCH_NR_Msk            0x3FFUL
#define PROMC_PATCH_CFG_PATCH_SIZE_Pos          16UL
#define PROMC_PATCH_CFG_PATCH_SIZE_Msk          0x30000UL
/* PROMC.PATCH_SROM */
#define PROMC_PATCH_SROM_BOUNDARY_Pos           0UL
#define PROMC_PATCH_SROM_BOUNDARY_Msk           0xFFFFFFFFUL
/* PROMC.PATCH_STRUCT_CTL */
#define PROMC_PATCH_STRUCT_CTL_VALID_Pos        0UL
#define PROMC_PATCH_STRUCT_CTL_VALID_Msk        0x1UL
#define PROMC_PATCH_STRUCT_CTL_MATCH_ADDR_Pos   4UL
#define PROMC_PATCH_STRUCT_CTL_MATCH_ADDR_Msk   0xFFFFFFF0UL
/* PROMC.PATCH_DATA */
#define PROMC_PATCH_DATA_DATA_Pos               0UL
#define PROMC_PATCH_DATA_DATA_Msk               0xFFFFFFFFUL


#endif /* _CYIP_PROMC_H_ */


/* [] END OF FILE */
