/***************************************************************************//**
* \file cyip_cpuss_ppu.h
*
* \brief
* CPUSS_PPU IP definitions
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

#ifndef _CYIP_CPUSS_PPU_H_
#define _CYIP_CPUSS_PPU_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                  CPUSS_PPU
*******************************************************************************/

#define CPUSS_PPU_SECTION_SIZE                  0x00001000UL

/**
  * \brief Power Policy Unit Registers for CPUSS (CPUSS_PPU)
  */
typedef struct {
  __IOM uint32_t PWPR;                          /*!< 0x00000000 Power Policy Register */
  __IOM uint32_t PMER;                          /*!< 0x00000004 Power Mode Emulation Register */
   __IM uint32_t PWSR;                          /*!< 0x00000008 Power Status Register */
   __IM uint32_t RESERVED;
   __IM uint32_t DISR;                          /*!< 0x00000010 Device Interface Input Current Status Register */
   __IM uint32_t MISR;                          /*!< 0x00000014 Miscellaneous Input Current Status Register */
   __IM uint32_t STSR;                          /*!< 0x00000018 Stored Status Register */
  __IOM uint32_t UNLK;                          /*!< 0x0000001C Unlock register */
  __IOM uint32_t PWCR;                          /*!< 0x00000020 Power Configuration Register */
  __IOM uint32_t PTCR;                          /*!< 0x00000024 Power Mode Transition Configuration Register */
   __IM uint32_t RESERVED1[2];
  __IOM uint32_t IMR;                           /*!< 0x00000030 Interrupt Mask Register */
  __IOM uint32_t AIMR;                          /*!< 0x00000034 Additional Interrupt Mask Register */
  __IOM uint32_t ISR;                           /*!< 0x00000038 Interrupt Status Register */
  __IOM uint32_t AISR;                          /*!< 0x0000003C Additional Interrupt Status Register */
  __IOM uint32_t IESR;                          /*!< 0x00000040 Input Edge Sensitivity Register */
  __IOM uint32_t OPSR;                          /*!< 0x00000044 Operating Mode Active Edge Sensitivity Register */
   __IM uint32_t RESERVED2[2];
  __IOM uint32_t FUNRR;                         /*!< 0x00000050 Functional Retention RAM Configuration Register */
  __IOM uint32_t FULRR;                         /*!< 0x00000054 Full Retention RAM Configuration Register */
  __IOM uint32_t MEMRR;                         /*!< 0x00000058 Memory Retention RAM Configuration Register */
   __IM uint32_t RESERVED3[65];
  __IOM uint32_t EDTR0;                         /*!< 0x00000160 Power Mode Entry Delay Register 0 */
  __IOM uint32_t EDTR1;                         /*!< 0x00000164 Power Mode Entry Delay Register 1 */
   __IM uint32_t RESERVED4[2];
   __IM uint32_t DCDR0;                         /*!< 0x00000170 Device Control Delay Configuration Register 0 */
   __IM uint32_t DCDR1;                         /*!< 0x00000174 Device Control Delay Configuration Register 1 */
   __IM uint32_t RESERVED5[910];
   __IM uint32_t IDR0;                          /*!< 0x00000FB0 PPU Identification Register 0 */
   __IM uint32_t IDR1;                          /*!< 0x00000FB4 PPU Identification Register 1 */
   __IM uint32_t RESERVED6[4];
   __IM uint32_t IIDR;                          /*!< 0x00000FC8 Implementation Identification Register */
   __IM uint32_t AIDR;                          /*!< 0x00000FCC Architecture Identification Register */
   __IM uint32_t PID4;                          /*!< 0x00000FD0 Implementation Defined Identification Register (PID4) */
   __IM uint32_t RESERVED7[3];
   __IM uint32_t PID0;                          /*!< 0x00000FE0 Implementation Defined Identification Register (PID0) */
   __IM uint32_t PID1;                          /*!< 0x00000FE4 Implementation Defined Identification Register (PID1) */
   __IM uint32_t PID2;                          /*!< 0x00000FE8 Implementation Defined Identification Register (PID2) */
   __IM uint32_t PID3;                          /*!< 0x00000FEC Implementation Defined Identification Register (PID3) */
   __IM uint32_t ID0;                           /*!< 0x00000FF0 Implementation Defined Identification Register (ID0) */
   __IM uint32_t ID1;                           /*!< 0x00000FF4 Implementation Defined Identification Register (ID1) */
   __IM uint32_t ID2;                           /*!< 0x00000FF8 Implementation Defined Identification Register (ID2) */
   __IM uint32_t ID3;                           /*!< 0x00000FFC Implementation Defined Identification Register (ID3) */
} CPUSS_PPU_Type;                               /*!< Size = 4096 (0x1000) */


/* CPUSS_PPU.PWPR */
#define CPUSS_PPU_PWPR_PWR_POLICY_Pos           0UL
#define CPUSS_PPU_PWPR_PWR_POLICY_Msk           0xFUL
#define CPUSS_PPU_PWPR_PWR_DYN_EN_Pos           8UL
#define CPUSS_PPU_PWPR_PWR_DYN_EN_Msk           0x100UL
#define CPUSS_PPU_PWPR_LOCK_EN_Pos              12UL
#define CPUSS_PPU_PWPR_LOCK_EN_Msk              0x1000UL
#define CPUSS_PPU_PWPR_OP_POLICY_Pos            16UL
#define CPUSS_PPU_PWPR_OP_POLICY_Msk            0xF0000UL
#define CPUSS_PPU_PWPR_OP_DYN_EN_Pos            24UL
#define CPUSS_PPU_PWPR_OP_DYN_EN_Msk            0x1000000UL
/* CPUSS_PPU.PMER */
#define CPUSS_PPU_PMER_EMU_EN_Pos               0UL
#define CPUSS_PPU_PMER_EMU_EN_Msk               0x1UL
/* CPUSS_PPU.PWSR */
#define CPUSS_PPU_PWSR_PWR_STATUS_Pos           0UL
#define CPUSS_PPU_PWSR_PWR_STATUS_Msk           0xFUL
#define CPUSS_PPU_PWSR_PWR_DYN_STATUS_Pos       8UL
#define CPUSS_PPU_PWSR_PWR_DYN_STATUS_Msk       0x100UL
#define CPUSS_PPU_PWSR_LOCK_STATUS_Pos          12UL
#define CPUSS_PPU_PWSR_LOCK_STATUS_Msk          0x1000UL
#define CPUSS_PPU_PWSR_OP_STATUS_Pos            16UL
#define CPUSS_PPU_PWSR_OP_STATUS_Msk            0xF0000UL
#define CPUSS_PPU_PWSR_OP_DYN_STATUS_Pos        24UL
#define CPUSS_PPU_PWSR_OP_DYN_STATUS_Msk        0x1000000UL
/* CPUSS_PPU.DISR */
#define CPUSS_PPU_DISR_PWR_DEVACTIVE_STATUS_Pos 0UL
#define CPUSS_PPU_DISR_PWR_DEVACTIVE_STATUS_Msk 0x7FFUL
#define CPUSS_PPU_DISR_OP_DEVACTIVE_STATUS_Pos  24UL
#define CPUSS_PPU_DISR_OP_DEVACTIVE_STATUS_Msk  0xFF000000UL
/* CPUSS_PPU.MISR */
#define CPUSS_PPU_MISR_PCSMPACCEPT_STATUS_Pos   0UL
#define CPUSS_PPU_MISR_PCSMPACCEPT_STATUS_Msk   0x1UL
#define CPUSS_PPU_MISR_DEVACCEPT_STATUS_Pos     8UL
#define CPUSS_PPU_MISR_DEVACCEPT_STATUS_Msk     0xFF00UL
#define CPUSS_PPU_MISR_DEVDENY_STATUS_Pos       16UL
#define CPUSS_PPU_MISR_DEVDENY_STATUS_Msk       0xFF0000UL
/* CPUSS_PPU.STSR */
#define CPUSS_PPU_STSR_STORED_DEVDENY_Pos       0UL
#define CPUSS_PPU_STSR_STORED_DEVDENY_Msk       0xFFUL
/* CPUSS_PPU.UNLK */
#define CPUSS_PPU_UNLK_UNLOCK_Pos               0UL
#define CPUSS_PPU_UNLK_UNLOCK_Msk               0x1UL
/* CPUSS_PPU.PWCR */
#define CPUSS_PPU_PWCR_DEVREQEN_Pos             0UL
#define CPUSS_PPU_PWCR_DEVREQEN_Msk             0xFFUL
#define CPUSS_PPU_PWCR_PWR_DEVACTIVEEN_Pos      8UL
#define CPUSS_PPU_PWCR_PWR_DEVACTIVEEN_Msk      0x7FF00UL
#define CPUSS_PPU_PWCR_OP_DEVACTIVEEN_Pos       24UL
#define CPUSS_PPU_PWCR_OP_DEVACTIVEEN_Msk       0xFF000000UL
/* CPUSS_PPU.PTCR */
#define CPUSS_PPU_PTCR_WARM_RST_DEVREQEN_Pos    0UL
#define CPUSS_PPU_PTCR_WARM_RST_DEVREQEN_Msk    0x1UL
#define CPUSS_PPU_PTCR_DBG_RECOV_PORST_EN_Pos   1UL
#define CPUSS_PPU_PTCR_DBG_RECOV_PORST_EN_Msk   0x2UL
/* CPUSS_PPU.IMR */
#define CPUSS_PPU_IMR_STA_POLICY_TRN_IRQ_MASK_Pos 0UL
#define CPUSS_PPU_IMR_STA_POLICY_TRN_IRQ_MASK_Msk 0x1UL
#define CPUSS_PPU_IMR_STA_ACCEPT_IRQ_MASK_Pos   1UL
#define CPUSS_PPU_IMR_STA_ACCEPT_IRQ_MASK_Msk   0x2UL
#define CPUSS_PPU_IMR_STA_DENY_IRQ_MASK_Pos     2UL
#define CPUSS_PPU_IMR_STA_DENY_IRQ_MASK_Msk     0x4UL
#define CPUSS_PPU_IMR_EMU_ACCEPT_IRQ_MASK_Pos   3UL
#define CPUSS_PPU_IMR_EMU_ACCEPT_IRQ_MASK_Msk   0x8UL
#define CPUSS_PPU_IMR_EMU_DENY_IRQ_MASK_Pos     4UL
#define CPUSS_PPU_IMR_EMU_DENY_IRQ_MASK_Msk     0x10UL
#define CPUSS_PPU_IMR_LOCKED_IRQ_MASK_Pos       5UL
#define CPUSS_PPU_IMR_LOCKED_IRQ_MASK_Msk       0x20UL
/* CPUSS_PPU.AIMR */
#define CPUSS_PPU_AIMR_UNSPT_POLICY_IRQ_MASK_Pos 0UL
#define CPUSS_PPU_AIMR_UNSPT_POLICY_IRQ_MASK_Msk 0x1UL
#define CPUSS_PPU_AIMR_DYN_ACCEPT_IRQ_MASK_Pos  1UL
#define CPUSS_PPU_AIMR_DYN_ACCEPT_IRQ_MASK_Msk  0x2UL
#define CPUSS_PPU_AIMR_DYN_DENY_IRQ_MASK_Pos    2UL
#define CPUSS_PPU_AIMR_DYN_DENY_IRQ_MASK_Msk    0x4UL
#define CPUSS_PPU_AIMR_STA_POLICY_PWR_IRQ_MASK_Pos 3UL
#define CPUSS_PPU_AIMR_STA_POLICY_PWR_IRQ_MASK_Msk 0x8UL
#define CPUSS_PPU_AIMR_STA_POLICY_OP_IRQ_MASK_Pos 4UL
#define CPUSS_PPU_AIMR_STA_POLICY_OP_IRQ_MASK_Msk 0x10UL
/* CPUSS_PPU.ISR */
#define CPUSS_PPU_ISR_STA_POLICY_TRN_IRQ_Pos    0UL
#define CPUSS_PPU_ISR_STA_POLICY_TRN_IRQ_Msk    0x1UL
#define CPUSS_PPU_ISR_STA_ACCEPT_IRQ_Pos        1UL
#define CPUSS_PPU_ISR_STA_ACCEPT_IRQ_Msk        0x2UL
#define CPUSS_PPU_ISR_STA_DENY_IRQ_Pos          2UL
#define CPUSS_PPU_ISR_STA_DENY_IRQ_Msk          0x4UL
#define CPUSS_PPU_ISR_EMU_ACCEPT_IRQ_Pos        3UL
#define CPUSS_PPU_ISR_EMU_ACCEPT_IRQ_Msk        0x8UL
#define CPUSS_PPU_ISR_EMU_DENY_IRQ_Pos          4UL
#define CPUSS_PPU_ISR_EMU_DENY_IRQ_Msk          0x10UL
#define CPUSS_PPU_ISR_LOCKED_IRQ_Pos            5UL
#define CPUSS_PPU_ISR_LOCKED_IRQ_Msk            0x20UL
#define CPUSS_PPU_ISR_OTHER_IRQ_Pos             7UL
#define CPUSS_PPU_ISR_OTHER_IRQ_Msk             0x80UL
#define CPUSS_PPU_ISR_PWR_ACTIVE_EDGE_IRQ_Pos   8UL
#define CPUSS_PPU_ISR_PWR_ACTIVE_EDGE_IRQ_Msk   0x7FF00UL
#define CPUSS_PPU_ISR_OP_ACTIVE_EDGE_IRQ_Pos    24UL
#define CPUSS_PPU_ISR_OP_ACTIVE_EDGE_IRQ_Msk    0xFF000000UL
/* CPUSS_PPU.AISR */
#define CPUSS_PPU_AISR_UNSPT_POLICY_IRQ_Pos     0UL
#define CPUSS_PPU_AISR_UNSPT_POLICY_IRQ_Msk     0x1UL
#define CPUSS_PPU_AISR_DYN_ACCEPT_IRQ_Pos       1UL
#define CPUSS_PPU_AISR_DYN_ACCEPT_IRQ_Msk       0x2UL
#define CPUSS_PPU_AISR_DYN_DENY_IRQ_Pos         2UL
#define CPUSS_PPU_AISR_DYN_DENY_IRQ_Msk         0x4UL
#define CPUSS_PPU_AISR_STA_POLICY_PWR_IRQ_Pos   3UL
#define CPUSS_PPU_AISR_STA_POLICY_PWR_IRQ_Msk   0x8UL
#define CPUSS_PPU_AISR_STA_POLICY_OP_IRQ_Pos    4UL
#define CPUSS_PPU_AISR_STA_POLICY_OP_IRQ_Msk    0x10UL
/* CPUSS_PPU.IESR */
#define CPUSS_PPU_IESR_DEVACTIVE00_EDGE_Pos     0UL
#define CPUSS_PPU_IESR_DEVACTIVE00_EDGE_Msk     0x3UL
#define CPUSS_PPU_IESR_DEVACTIVE01_EDGE_Pos     2UL
#define CPUSS_PPU_IESR_DEVACTIVE01_EDGE_Msk     0xCUL
#define CPUSS_PPU_IESR_DEVACTIVE02_EDGE_Pos     4UL
#define CPUSS_PPU_IESR_DEVACTIVE02_EDGE_Msk     0x30UL
#define CPUSS_PPU_IESR_DEVACTIVE03_EDGE_Pos     6UL
#define CPUSS_PPU_IESR_DEVACTIVE03_EDGE_Msk     0xC0UL
#define CPUSS_PPU_IESR_DEVACTIVE04_EDGE_Pos     8UL
#define CPUSS_PPU_IESR_DEVACTIVE04_EDGE_Msk     0x300UL
#define CPUSS_PPU_IESR_DEVACTIVE05_EDGE_Pos     10UL
#define CPUSS_PPU_IESR_DEVACTIVE05_EDGE_Msk     0xC00UL
#define CPUSS_PPU_IESR_DEVACTIVE06_EDGE_Pos     12UL
#define CPUSS_PPU_IESR_DEVACTIVE06_EDGE_Msk     0x3000UL
#define CPUSS_PPU_IESR_DEVACTIVE07_EDGE_Pos     14UL
#define CPUSS_PPU_IESR_DEVACTIVE07_EDGE_Msk     0xC000UL
#define CPUSS_PPU_IESR_DEVACTIVE08_EDGE_Pos     16UL
#define CPUSS_PPU_IESR_DEVACTIVE08_EDGE_Msk     0x30000UL
#define CPUSS_PPU_IESR_DEVACTIVE09_EDGE_Pos     18UL
#define CPUSS_PPU_IESR_DEVACTIVE09_EDGE_Msk     0xC0000UL
#define CPUSS_PPU_IESR_DEVACTIVE10_EDGE_Pos     20UL
#define CPUSS_PPU_IESR_DEVACTIVE10_EDGE_Msk     0x300000UL
/* CPUSS_PPU.OPSR */
#define CPUSS_PPU_OPSR_DEVACTIVE16_EDGE_Pos     0UL
#define CPUSS_PPU_OPSR_DEVACTIVE16_EDGE_Msk     0x3UL
#define CPUSS_PPU_OPSR_DEVACTIVE17_EDGE_Pos     2UL
#define CPUSS_PPU_OPSR_DEVACTIVE17_EDGE_Msk     0xCUL
#define CPUSS_PPU_OPSR_DEVACTIVE18_EDGE_Pos     4UL
#define CPUSS_PPU_OPSR_DEVACTIVE18_EDGE_Msk     0x30UL
#define CPUSS_PPU_OPSR_DEVACTIVE19_EDGE_Pos     6UL
#define CPUSS_PPU_OPSR_DEVACTIVE19_EDGE_Msk     0xC0UL
#define CPUSS_PPU_OPSR_DEVACTIVE20_EDGE_Pos     8UL
#define CPUSS_PPU_OPSR_DEVACTIVE20_EDGE_Msk     0x300UL
#define CPUSS_PPU_OPSR_DEVACTIVE21_EDGE_Pos     10UL
#define CPUSS_PPU_OPSR_DEVACTIVE21_EDGE_Msk     0xC00UL
#define CPUSS_PPU_OPSR_DEVACTIVE22_EDGE_Pos     12UL
#define CPUSS_PPU_OPSR_DEVACTIVE22_EDGE_Msk     0x3000UL
#define CPUSS_PPU_OPSR_DEVACTIVE23_EDGE_Pos     14UL
#define CPUSS_PPU_OPSR_DEVACTIVE23_EDGE_Msk     0xC000UL
/* CPUSS_PPU.FUNRR */
#define CPUSS_PPU_FUNRR_FUNC_RET_RAM_CFG_Pos    0UL
#define CPUSS_PPU_FUNRR_FUNC_RET_RAM_CFG_Msk    0xFFUL
/* CPUSS_PPU.FULRR */
#define CPUSS_PPU_FULRR_FULL_RET_RAM_CFG_Pos    0UL
#define CPUSS_PPU_FULRR_FULL_RET_RAM_CFG_Msk    0xFFUL
/* CPUSS_PPU.MEMRR */
#define CPUSS_PPU_MEMRR_MEM_RET_RAM_CFG_Pos     0UL
#define CPUSS_PPU_MEMRR_MEM_RET_RAM_CFG_Msk     0xFFUL
/* CPUSS_PPU.EDTR0 */
#define CPUSS_PPU_EDTR0_OFF_DEL_Pos             0UL
#define CPUSS_PPU_EDTR0_OFF_DEL_Msk             0xFFUL
#define CPUSS_PPU_EDTR0_MEM_RET_DEL_Pos         8UL
#define CPUSS_PPU_EDTR0_MEM_RET_DEL_Msk         0xFF00UL
#define CPUSS_PPU_EDTR0_LOGIC_RET_DEL_Pos       16UL
#define CPUSS_PPU_EDTR0_LOGIC_RET_DEL_Msk       0xFF0000UL
#define CPUSS_PPU_EDTR0_FULL_RET_DEL_Pos        24UL
#define CPUSS_PPU_EDTR0_FULL_RET_DEL_Msk        0xFF000000UL
/* CPUSS_PPU.EDTR1 */
#define CPUSS_PPU_EDTR1_MEM_OFF_DEL_Pos         0UL
#define CPUSS_PPU_EDTR1_MEM_OFF_DEL_Msk         0xFFUL
#define CPUSS_PPU_EDTR1_FUNC_RET_DEL_Pos        8UL
#define CPUSS_PPU_EDTR1_FUNC_RET_DEL_Msk        0xFF00UL
/* CPUSS_PPU.DCDR0 */
#define CPUSS_PPU_DCDR0_CLKEN_RST_DLY_Pos       0UL
#define CPUSS_PPU_DCDR0_CLKEN_RST_DLY_Msk       0xFFUL
#define CPUSS_PPU_DCDR0_ISO_CLKEN_DLY_Pos       8UL
#define CPUSS_PPU_DCDR0_ISO_CLKEN_DLY_Msk       0xFF00UL
#define CPUSS_PPU_DCDR0_RST_HWSTAT_DLY_Pos      16UL
#define CPUSS_PPU_DCDR0_RST_HWSTAT_DLY_Msk      0xFF0000UL
/* CPUSS_PPU.DCDR1 */
#define CPUSS_PPU_DCDR1_ISO_RST_DLY_Pos         0UL
#define CPUSS_PPU_DCDR1_ISO_RST_DLY_Msk         0xFFUL
#define CPUSS_PPU_DCDR1_CLKEN_ISO_DLY_Pos       8UL
#define CPUSS_PPU_DCDR1_CLKEN_ISO_DLY_Msk       0xFF00UL
/* CPUSS_PPU.IDR0 */
#define CPUSS_PPU_IDR0_DEVCHAN_Pos              0UL
#define CPUSS_PPU_IDR0_DEVCHAN_Msk              0xFUL
#define CPUSS_PPU_IDR0_NUM_OPMODE_Pos           4UL
#define CPUSS_PPU_IDR0_NUM_OPMODE_Msk           0xF0UL
#define CPUSS_PPU_IDR0_STA_OFF_SPT_Pos          8UL
#define CPUSS_PPU_IDR0_STA_OFF_SPT_Msk          0x100UL
#define CPUSS_PPU_IDR0_STA_OFF_EMU_SPT_Pos      9UL
#define CPUSS_PPU_IDR0_STA_OFF_EMU_SPT_Msk      0x200UL
#define CPUSS_PPU_IDR0_STA_MEM_RET_SPT_Pos      10UL
#define CPUSS_PPU_IDR0_STA_MEM_RET_SPT_Msk      0x400UL
#define CPUSS_PPU_IDR0_STA_MEM_RET_EMU_SPT_Pos  11UL
#define CPUSS_PPU_IDR0_STA_MEM_RET_EMU_SPT_Msk  0x800UL
#define CPUSS_PPU_IDR0_STA_LGC_RET_SPT_Pos      12UL
#define CPUSS_PPU_IDR0_STA_LGC_RET_SPT_Msk      0x1000UL
#define CPUSS_PPU_IDR0_STA_MEM_OFF_SPT_Pos      13UL
#define CPUSS_PPU_IDR0_STA_MEM_OFF_SPT_Msk      0x2000UL
#define CPUSS_PPU_IDR0_STA_FULL_RET_SPT_Pos     14UL
#define CPUSS_PPU_IDR0_STA_FULL_RET_SPT_Msk     0x4000UL
#define CPUSS_PPU_IDR0_STA_FUNC_RET_SPT_Pos     15UL
#define CPUSS_PPU_IDR0_STA_FUNC_RET_SPT_Msk     0x8000UL
#define CPUSS_PPU_IDR0_STA_ON_SPT_Pos           16UL
#define CPUSS_PPU_IDR0_STA_ON_SPT_Msk           0x10000UL
#define CPUSS_PPU_IDR0_STA_WRM_RST_SPT_Pos      17UL
#define CPUSS_PPU_IDR0_STA_WRM_RST_SPT_Msk      0x20000UL
#define CPUSS_PPU_IDR0_STA_DBG_RECOV_SPT_Pos    18UL
#define CPUSS_PPU_IDR0_STA_DBG_RECOV_SPT_Msk    0x40000UL
#define CPUSS_PPU_IDR0_DYN_OFF_SPT_Pos          20UL
#define CPUSS_PPU_IDR0_DYN_OFF_SPT_Msk          0x100000UL
#define CPUSS_PPU_IDR0_DYN_OFF_EMU_SPT_Pos      21UL
#define CPUSS_PPU_IDR0_DYN_OFF_EMU_SPT_Msk      0x200000UL
#define CPUSS_PPU_IDR0_DYN_MEM_RET_SPT_Pos      22UL
#define CPUSS_PPU_IDR0_DYN_MEM_RET_SPT_Msk      0x400000UL
#define CPUSS_PPU_IDR0_DYN_MEM_RET_EMU_SPT_Pos  23UL
#define CPUSS_PPU_IDR0_DYN_MEM_RET_EMU_SPT_Msk  0x800000UL
#define CPUSS_PPU_IDR0_DYN_LGC_RET_SPT_Pos      24UL
#define CPUSS_PPU_IDR0_DYN_LGC_RET_SPT_Msk      0x1000000UL
#define CPUSS_PPU_IDR0_DYN_MEM_OFF_SPT_Pos      25UL
#define CPUSS_PPU_IDR0_DYN_MEM_OFF_SPT_Msk      0x2000000UL
#define CPUSS_PPU_IDR0_DYN_FULL_RET_SPT_Pos     26UL
#define CPUSS_PPU_IDR0_DYN_FULL_RET_SPT_Msk     0x4000000UL
#define CPUSS_PPU_IDR0_DYN_FUNC_RET_SPT_Pos     27UL
#define CPUSS_PPU_IDR0_DYN_FUNC_RET_SPT_Msk     0x8000000UL
#define CPUSS_PPU_IDR0_DYN_ON_SPT_Pos           28UL
#define CPUSS_PPU_IDR0_DYN_ON_SPT_Msk           0x10000000UL
#define CPUSS_PPU_IDR0_DYN_WRM_RST_SPT_Pos      29UL
#define CPUSS_PPU_IDR0_DYN_WRM_RST_SPT_Msk      0x20000000UL
/* CPUSS_PPU.IDR1 */
#define CPUSS_PPU_IDR1_PWR_MODE_ENTRY_DEL_SPT_Pos 0UL
#define CPUSS_PPU_IDR1_PWR_MODE_ENTRY_DEL_SPT_Msk 0x1UL
#define CPUSS_PPU_IDR1_SW_DEV_DEL_SPT_Pos       1UL
#define CPUSS_PPU_IDR1_SW_DEV_DEL_SPT_Msk       0x2UL
#define CPUSS_PPU_IDR1_LOCK_SPT_Pos             2UL
#define CPUSS_PPU_IDR1_LOCK_SPT_Msk             0x4UL
#define CPUSS_PPU_IDR1_MEM_RET_RAM_REG_Pos      4UL
#define CPUSS_PPU_IDR1_MEM_RET_RAM_REG_Msk      0x10UL
#define CPUSS_PPU_IDR1_FULL_RET_RAM_REG_Pos     5UL
#define CPUSS_PPU_IDR1_FULL_RET_RAM_REG_Msk     0x20UL
#define CPUSS_PPU_IDR1_FUNC_RET_RAM_REG_Pos     6UL
#define CPUSS_PPU_IDR1_FUNC_RET_RAM_REG_Msk     0x40UL
#define CPUSS_PPU_IDR1_STA_POLICY_PWR_IRQ_SPT_Pos 8UL
#define CPUSS_PPU_IDR1_STA_POLICY_PWR_IRQ_SPT_Msk 0x100UL
#define CPUSS_PPU_IDR1_STA_POLICY_OP_IRQ_SPT_Pos 9UL
#define CPUSS_PPU_IDR1_STA_POLICY_OP_IRQ_SPT_Msk 0x200UL
#define CPUSS_PPU_IDR1_OP_ACTIVE_Pos            10UL
#define CPUSS_PPU_IDR1_OP_ACTIVE_Msk            0x400UL
#define CPUSS_PPU_IDR1_OFF_MEM_RET_TRANS_Pos    12UL
#define CPUSS_PPU_IDR1_OFF_MEM_RET_TRANS_Msk    0x1000UL
/* CPUSS_PPU.IIDR */
#define CPUSS_PPU_IIDR_IMPLEMENTER_Pos          0UL
#define CPUSS_PPU_IIDR_IMPLEMENTER_Msk          0xFFFUL
#define CPUSS_PPU_IIDR_REVISION_Pos             12UL
#define CPUSS_PPU_IIDR_REVISION_Msk             0xF000UL
#define CPUSS_PPU_IIDR_VARIANT_Pos              16UL
#define CPUSS_PPU_IIDR_VARIANT_Msk              0xF0000UL
#define CPUSS_PPU_IIDR_PRODUCT_ID_Pos           20UL
#define CPUSS_PPU_IIDR_PRODUCT_ID_Msk           0xFFF00000UL
/* CPUSS_PPU.AIDR */
#define CPUSS_PPU_AIDR_ARCH_REV_MINOR_Pos       0UL
#define CPUSS_PPU_AIDR_ARCH_REV_MINOR_Msk       0xFUL
#define CPUSS_PPU_AIDR_ARCH_REV_MAJOR_Pos       4UL
#define CPUSS_PPU_AIDR_ARCH_REV_MAJOR_Msk       0xF0UL
/* CPUSS_PPU.PID4 */
#define CPUSS_PPU_PID4_IMPLEMENTER_11_8_Pos     0UL
#define CPUSS_PPU_PID4_IMPLEMENTER_11_8_Msk     0xFUL
/* CPUSS_PPU.PID0 */
#define CPUSS_PPU_PID0_PRODUCT_ID_7_0_Pos       0UL
#define CPUSS_PPU_PID0_PRODUCT_ID_7_0_Msk       0xFFUL
/* CPUSS_PPU.PID1 */
#define CPUSS_PPU_PID1_PRODUCT_ID_11_8_Pos      0UL
#define CPUSS_PPU_PID1_PRODUCT_ID_11_8_Msk      0xFUL
#define CPUSS_PPU_PID1_IMPLEMENTER_3_0_Pos      4UL
#define CPUSS_PPU_PID1_IMPLEMENTER_3_0_Msk      0xF0UL
/* CPUSS_PPU.PID2 */
#define CPUSS_PPU_PID2_IMPLEMENTER_6_4_Pos      0UL
#define CPUSS_PPU_PID2_IMPLEMENTER_6_4_Msk      0x7UL
#define CPUSS_PPU_PID2_CONST_HIGH_Pos           3UL
#define CPUSS_PPU_PID2_CONST_HIGH_Msk           0x8UL
#define CPUSS_PPU_PID2_REV_CONST_Pos            4UL
#define CPUSS_PPU_PID2_REV_CONST_Msk            0xF0UL
/* CPUSS_PPU.PID3 */
#define CPUSS_PPU_PID3_PID3_REV_CONST_Pos       0UL
#define CPUSS_PPU_PID3_PID3_REV_CONST_Msk       0xFUL
#define CPUSS_PPU_PID3_PID3_REVISION_Pos        4UL
#define CPUSS_PPU_PID3_PID3_REVISION_Msk        0xF0UL
/* CPUSS_PPU.ID0 */
#define CPUSS_PPU_ID0_ID0_Pos                   0UL
#define CPUSS_PPU_ID0_ID0_Msk                   0xFFUL
/* CPUSS_PPU.ID1 */
#define CPUSS_PPU_ID1_ID1_Pos                   0UL
#define CPUSS_PPU_ID1_ID1_Msk                   0xFFUL
/* CPUSS_PPU.ID2 */
#define CPUSS_PPU_ID2_ID2_Pos                   0UL
#define CPUSS_PPU_ID2_ID2_Msk                   0xFFUL
/* CPUSS_PPU.ID3 */
#define CPUSS_PPU_ID3_ID3_Pos                   0UL
#define CPUSS_PPU_ID3_ID3_Msk                   0xFFUL


#endif /* _CYIP_CPUSS_PPU_H_ */


/* [] END OF FILE */
