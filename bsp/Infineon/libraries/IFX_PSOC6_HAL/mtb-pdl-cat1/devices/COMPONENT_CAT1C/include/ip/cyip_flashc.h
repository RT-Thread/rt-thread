/***************************************************************************//**
* \file cyip_flashc.h
*
* \brief
* FLASHC IP definitions
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

#ifndef _CYIP_FLASHC_H_
#define _CYIP_FLASHC_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    FLASHC
*******************************************************************************/

#define FLASHC_FM_CTL_ECT_SECTION_SIZE          0x00001000UL
#define FLASHC_SECTION_SIZE                     0x00010000UL

/**
  * \brief Flash Macro Registers (FLASHC_FM_CTL_ECT)
  */
typedef struct {
  __IOM uint32_t FM_CTL;                        /*!< 0x00000000 Flash Macro Control */
  __IOM uint32_t FM_CODE_MARGIN;                /*!< 0x00000004 Flash Macro Margin Mode on Code Flash */
   __OM uint32_t FM_ADDR;                       /*!< 0x00000008 Flash Macro Address */
   __IM uint32_t RESERVED[5];
  __IOM uint32_t INTR;                          /*!< 0x00000020 Interrupt */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000024 Interrupt Set */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000028 Interrupt Mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000002C Interrupt Masked */
   __OM uint32_t ECC_OVERRIDE;                  /*!< 0x00000030 ECC Data In override information and control bits */
   __IM uint32_t RESERVED1[3];
   __OM uint32_t FM_DATA;                       /*!< 0x00000040 Flash macro data_in[31 to 0] both Code and Work Flash */
   __IM uint32_t RESERVED2[8];
  __IOM uint32_t BOOKMARK;                      /*!< 0x00000064 Bookmark register - keeps the current FW HV seq */
   __IM uint32_t RESERVED3[230];
  __IOM uint32_t MAIN_FLASH_SAFETY;             /*!< 0x00000400 Main (Code) Flash Security enable */
   __IM uint32_t STATUS;                        /*!< 0x00000404 Status read from Flash Macro */
   __IM uint32_t RESERVED4[62];
  __IOM uint32_t WORK_FLASH_SAFETY;             /*!< 0x00000500 Work Flash Security enable */
   __IM uint32_t RESERVED5[703];
} FLASHC_FM_CTL_ECT_Type;                       /*!< Size = 4096 (0x1000) */

/**
  * \brief Flash controller (FLASHC)
  */
typedef struct {
  __IOM uint32_t FLASH_CTL;                     /*!< 0x00000000 Control */
  __IOM uint32_t FLASH_PWR_CTL;                 /*!< 0x00000004 Flash power control */
  __IOM uint32_t FLASH_CMD;                     /*!< 0x00000008 Command */
   __IM uint32_t RESERVED[165];
  __IOM uint32_t ECC_CTL;                       /*!< 0x000002A0 ECC control */
   __IM uint32_t RESERVED1[3];
  __IOM uint32_t FM_SRAM_ECC_CTL0;              /*!< 0x000002B0 eCT Flash SRAM ECC control 0 */
  __IOM uint32_t FM_SRAM_ECC_CTL1;              /*!< 0x000002B4 eCT Flash SRAM ECC control 1 */
   __IM uint32_t FM_SRAM_ECC_CTL2;              /*!< 0x000002B8 eCT Flash SRAM ECC control 2 */
  __IOM uint32_t FM_SRAM_ECC_CTL3;              /*!< 0x000002BC eCT Flash SRAM ECC control 3 */
   __IM uint32_t RESERVED2[80];
  __IOM uint32_t CM0_CA_CTL0;                   /*!< 0x00000400 CM0+ cache control */
  __IOM uint32_t CM0_CA_CTL1;                   /*!< 0x00000404 CM0+ cache control */
  __IOM uint32_t CM0_CA_CTL2;                   /*!< 0x00000408 CM0+ cache control */
   __IM uint32_t RESERVED3[13];
   __IM uint32_t CM0_CA_STATUS0;                /*!< 0x00000440 CM0+ cache status 0 */
   __IM uint32_t CM0_CA_STATUS1;                /*!< 0x00000444 CM0+ cache status 1 */
   __IM uint32_t CM0_CA_STATUS2;                /*!< 0x00000448 CM0+ cache status 2 */
   __IM uint32_t RESERVED4[5];
  __IOM uint32_t CM0_STATUS;                    /*!< 0x00000460 CM0+ interface status */
   __IM uint32_t RESERVED5[31];
  __IOM uint32_t CM7_0_STATUS;                  /*!< 0x000004E0 CM7 #0 interface status */
   __IM uint32_t RESERVED6[31];
  __IOM uint32_t CM7_1_STATUS;                  /*!< 0x00000560 CM7 #1 interface status */
   __IM uint32_t RESERVED7[7];
  __IOM uint32_t CRYPTO_BUFF_CTL;               /*!< 0x00000580 Cryptography buffer control */
   __IM uint32_t RESERVED8[31];
  __IOM uint32_t DW0_BUFF_CTL;                  /*!< 0x00000600 Datawire 0 buffer control */
   __IM uint32_t RESERVED9[31];
  __IOM uint32_t DW1_BUFF_CTL;                  /*!< 0x00000680 Datawire 1 buffer control */
   __IM uint32_t RESERVED10[31];
  __IOM uint32_t DMAC_BUFF_CTL;                 /*!< 0x00000700 DMA controller buffer control */
   __IM uint32_t RESERVED11[31];
  __IOM uint32_t SLOW0_MS_BUFF_CTL;             /*!< 0x00000780 Slow external master 0 buffer control */
   __IM uint32_t RESERVED12[31];
  __IOM uint32_t SLOW1_MS_BUFF_CTL;             /*!< 0x00000800 Slow external master 1 buffer control */
   __IM uint32_t RESERVED13[14847];
        FLASHC_FM_CTL_ECT_Type FM_CTL_ECT;      /*!< 0x0000F000 Flash Macro Registers */
} FLASHC_Type;                                  /*!< Size = 65536 (0x10000) */


/* FLASHC_FM_CTL_ECT.FM_CTL */
#define FLASHC_FM_CTL_ECT_FM_CTL_FM_MODE_Pos    0UL
#define FLASHC_FM_CTL_ECT_FM_CTL_FM_MODE_Msk    0x1FUL
#define FLASHC_FM_CTL_ECT_FM_CTL_EMB_START_Pos  31UL
#define FLASHC_FM_CTL_ECT_FM_CTL_EMB_START_Msk  0x80000000UL
/* FLASHC_FM_CTL_ECT.FM_CODE_MARGIN */
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_DCS_TRIM_Pos 0UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_DCS_TRIM_Msk 0x1FFUL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_DCS_TRIM_EN_Pos 9UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_DCS_TRIM_EN_Msk 0x200UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_RDREG_TRIM_Pos 10UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_RDREG_TRIM_Msk 0xFC00UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_PGM_ERS_B_Pos 29UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_PGM_ERS_B_Msk 0x20000000UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_MODE_RDREG_CHNG_EN_Pos 30UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_MODE_RDREG_CHNG_EN_Msk 0x40000000UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_MODE_EN_Pos 31UL
#define FLASHC_FM_CTL_ECT_FM_CODE_MARGIN_MARGIN_MODE_EN_Msk 0x80000000UL
/* FLASHC_FM_CTL_ECT.FM_ADDR */
#define FLASHC_FM_CTL_ECT_FM_ADDR_FM_ADDR_Pos   0UL
#define FLASHC_FM_CTL_ECT_FM_ADDR_FM_ADDR_Msk   0xFFFFFFFFUL
/* FLASHC_FM_CTL_ECT.INTR */
#define FLASHC_FM_CTL_ECT_INTR_INTR_Pos         0UL
#define FLASHC_FM_CTL_ECT_INTR_INTR_Msk         0x1UL
/* FLASHC_FM_CTL_ECT.INTR_SET */
#define FLASHC_FM_CTL_ECT_INTR_SET_INTR_SET_Pos 0UL
#define FLASHC_FM_CTL_ECT_INTR_SET_INTR_SET_Msk 0x1UL
/* FLASHC_FM_CTL_ECT.INTR_MASK */
#define FLASHC_FM_CTL_ECT_INTR_MASK_INTR_MASK_Pos 0UL
#define FLASHC_FM_CTL_ECT_INTR_MASK_INTR_MASK_Msk 0x1UL
/* FLASHC_FM_CTL_ECT.INTR_MASKED */
#define FLASHC_FM_CTL_ECT_INTR_MASKED_INTR_MASKED_Pos 0UL
#define FLASHC_FM_CTL_ECT_INTR_MASKED_INTR_MASKED_Msk 0x1UL
/* FLASHC_FM_CTL_ECT.ECC_OVERRIDE */
#define FLASHC_FM_CTL_ECT_ECC_OVERRIDE_ECC_OVERRIDE_SYNDROME_Pos 0UL
#define FLASHC_FM_CTL_ECT_ECC_OVERRIDE_ECC_OVERRIDE_SYNDROME_Msk 0xFFUL
#define FLASHC_FM_CTL_ECT_ECC_OVERRIDE_ECC_OVERRIDE_WORK_Pos 30UL
#define FLASHC_FM_CTL_ECT_ECC_OVERRIDE_ECC_OVERRIDE_WORK_Msk 0x40000000UL
#define FLASHC_FM_CTL_ECT_ECC_OVERRIDE_ECC_OVERRIDE_CODE_Pos 31UL
#define FLASHC_FM_CTL_ECT_ECC_OVERRIDE_ECC_OVERRIDE_CODE_Msk 0x80000000UL
/* FLASHC_FM_CTL_ECT.FM_DATA */
#define FLASHC_FM_CTL_ECT_FM_DATA_FM_DATA_Pos   0UL
#define FLASHC_FM_CTL_ECT_FM_DATA_FM_DATA_Msk   0xFFFFFFFFUL
/* FLASHC_FM_CTL_ECT.BOOKMARK */
#define FLASHC_FM_CTL_ECT_BOOKMARK_BOOKMARK_Pos 0UL
#define FLASHC_FM_CTL_ECT_BOOKMARK_BOOKMARK_Msk 0xFFFFFFFFUL
/* FLASHC_FM_CTL_ECT.MAIN_FLASH_SAFETY */
#define FLASHC_FM_CTL_ECT_MAIN_FLASH_SAFETY_MAINFLASHWRITEENABLE_Pos 0UL
#define FLASHC_FM_CTL_ECT_MAIN_FLASH_SAFETY_MAINFLASHWRITEENABLE_Msk 0x1UL
/* FLASHC_FM_CTL_ECT.STATUS */
#define FLASHC_FM_CTL_ECT_STATUS_PGM_CODE_Pos   0UL
#define FLASHC_FM_CTL_ECT_STATUS_PGM_CODE_Msk   0x1UL
#define FLASHC_FM_CTL_ECT_STATUS_PGM_WORK_Pos   1UL
#define FLASHC_FM_CTL_ECT_STATUS_PGM_WORK_Msk   0x2UL
#define FLASHC_FM_CTL_ECT_STATUS_ERASE_CODE_Pos 2UL
#define FLASHC_FM_CTL_ECT_STATUS_ERASE_CODE_Msk 0x4UL
#define FLASHC_FM_CTL_ECT_STATUS_ERASE_WORK_Pos 3UL
#define FLASHC_FM_CTL_ECT_STATUS_ERASE_WORK_Msk 0x8UL
#define FLASHC_FM_CTL_ECT_STATUS_ERS_SUSPEND_Pos 4UL
#define FLASHC_FM_CTL_ECT_STATUS_ERS_SUSPEND_Msk 0x10UL
#define FLASHC_FM_CTL_ECT_STATUS_BLANK_CHECK_WORK_Pos 5UL
#define FLASHC_FM_CTL_ECT_STATUS_BLANK_CHECK_WORK_Msk 0x20UL
#define FLASHC_FM_CTL_ECT_STATUS_BLANK_CHCEK_PASS_Pos 6UL
#define FLASHC_FM_CTL_ECT_STATUS_BLANK_CHCEK_PASS_Msk 0x40UL
#define FLASHC_FM_CTL_ECT_STATUS_POR_1B_ECC_CORRECTED_Pos 27UL
#define FLASHC_FM_CTL_ECT_STATUS_POR_1B_ECC_CORRECTED_Msk 0x8000000UL
#define FLASHC_FM_CTL_ECT_STATUS_POR_2B_ECC_ERROR_Pos 28UL
#define FLASHC_FM_CTL_ECT_STATUS_POR_2B_ECC_ERROR_Msk 0x10000000UL
#define FLASHC_FM_CTL_ECT_STATUS_NATIVE_POR_Pos 29UL
#define FLASHC_FM_CTL_ECT_STATUS_NATIVE_POR_Msk 0x20000000UL
#define FLASHC_FM_CTL_ECT_STATUS_HANG_Pos       30UL
#define FLASHC_FM_CTL_ECT_STATUS_HANG_Msk       0x40000000UL
#define FLASHC_FM_CTL_ECT_STATUS_BUSY_Pos       31UL
#define FLASHC_FM_CTL_ECT_STATUS_BUSY_Msk       0x80000000UL
/* FLASHC_FM_CTL_ECT.WORK_FLASH_SAFETY */
#define FLASHC_FM_CTL_ECT_WORK_FLASH_SAFETY_WORKFLASHWRITEENABLE_Pos 0UL
#define FLASHC_FM_CTL_ECT_WORK_FLASH_SAFETY_WORKFLASHWRITEENABLE_Msk 0x1UL


/* FLASHC.FLASH_CTL */
#define FLASHC_FLASH_CTL_WS_Pos                 0UL
#define FLASHC_FLASH_CTL_WS_Msk                 0xFUL
#define FLASHC_FLASH_CTL_MAIN_MAP_Pos           8UL
#define FLASHC_FLASH_CTL_MAIN_MAP_Msk           0x100UL
#define FLASHC_FLASH_CTL_WORK_MAP_Pos           9UL
#define FLASHC_FLASH_CTL_WORK_MAP_Msk           0x200UL
#define FLASHC_FLASH_CTL_MAIN_BANK_MODE_Pos     12UL
#define FLASHC_FLASH_CTL_MAIN_BANK_MODE_Msk     0x1000UL
#define FLASHC_FLASH_CTL_WORK_BANK_MODE_Pos     13UL
#define FLASHC_FLASH_CTL_WORK_BANK_MODE_Msk     0x2000UL
#define FLASHC_FLASH_CTL_MAIN_ECC_EN_Pos        16UL
#define FLASHC_FLASH_CTL_MAIN_ECC_EN_Msk        0x10000UL
#define FLASHC_FLASH_CTL_MAIN_ECC_INJ_EN_Pos    17UL
#define FLASHC_FLASH_CTL_MAIN_ECC_INJ_EN_Msk    0x20000UL
#define FLASHC_FLASH_CTL_MAIN_ERR_SILENT_Pos    18UL
#define FLASHC_FLASH_CTL_MAIN_ERR_SILENT_Msk    0x40000UL
#define FLASHC_FLASH_CTL_WORK_ECC_EN_Pos        20UL
#define FLASHC_FLASH_CTL_WORK_ECC_EN_Msk        0x100000UL
#define FLASHC_FLASH_CTL_WORK_ECC_INJ_EN_Pos    21UL
#define FLASHC_FLASH_CTL_WORK_ECC_INJ_EN_Msk    0x200000UL
#define FLASHC_FLASH_CTL_WORK_ERR_SILENT_Pos    22UL
#define FLASHC_FLASH_CTL_WORK_ERR_SILENT_Msk    0x400000UL
#define FLASHC_FLASH_CTL_WORK_SEQ_RD_EN_Pos     24UL
#define FLASHC_FLASH_CTL_WORK_SEQ_RD_EN_Msk     0x1000000UL
/* FLASHC.FLASH_PWR_CTL */
#define FLASHC_FLASH_PWR_CTL_ENABLE_Pos         0UL
#define FLASHC_FLASH_PWR_CTL_ENABLE_Msk         0x1UL
#define FLASHC_FLASH_PWR_CTL_ENABLE_HV_Pos      1UL
#define FLASHC_FLASH_PWR_CTL_ENABLE_HV_Msk      0x2UL
/* FLASHC.FLASH_CMD */
#define FLASHC_FLASH_CMD_INV_Pos                0UL
#define FLASHC_FLASH_CMD_INV_Msk                0x1UL
#define FLASHC_FLASH_CMD_BUFF_INV_Pos           1UL
#define FLASHC_FLASH_CMD_BUFF_INV_Msk           0x2UL
/* FLASHC.ECC_CTL */
#define FLASHC_ECC_CTL_WORD_ADDR_Pos            0UL
#define FLASHC_ECC_CTL_WORD_ADDR_Msk            0xFFFFFFUL
#define FLASHC_ECC_CTL_PARITY_Pos               24UL
#define FLASHC_ECC_CTL_PARITY_Msk               0xFF000000UL
/* FLASHC.FM_SRAM_ECC_CTL0 */
#define FLASHC_FM_SRAM_ECC_CTL0_ECC_INJ_DATA_Pos 0UL
#define FLASHC_FM_SRAM_ECC_CTL0_ECC_INJ_DATA_Msk 0xFFFFFFFFUL
/* FLASHC.FM_SRAM_ECC_CTL1 */
#define FLASHC_FM_SRAM_ECC_CTL1_ECC_INJ_PARITY_Pos 0UL
#define FLASHC_FM_SRAM_ECC_CTL1_ECC_INJ_PARITY_Msk 0x7FUL
/* FLASHC.FM_SRAM_ECC_CTL2 */
#define FLASHC_FM_SRAM_ECC_CTL2_CORRECTED_DATA_Pos 0UL
#define FLASHC_FM_SRAM_ECC_CTL2_CORRECTED_DATA_Msk 0xFFFFFFFFUL
/* FLASHC.FM_SRAM_ECC_CTL3 */
#define FLASHC_FM_SRAM_ECC_CTL3_ECC_ENABLE_Pos  0UL
#define FLASHC_FM_SRAM_ECC_CTL3_ECC_ENABLE_Msk  0x1UL
#define FLASHC_FM_SRAM_ECC_CTL3_ECC_INJ_EN_Pos  4UL
#define FLASHC_FM_SRAM_ECC_CTL3_ECC_INJ_EN_Msk  0x10UL
#define FLASHC_FM_SRAM_ECC_CTL3_ECC_TEST_FAIL_Pos 8UL
#define FLASHC_FM_SRAM_ECC_CTL3_ECC_TEST_FAIL_Msk 0x100UL
/* FLASHC.CM0_CA_CTL0 */
#define FLASHC_CM0_CA_CTL0_RAM_ECC_EN_Pos       0UL
#define FLASHC_CM0_CA_CTL0_RAM_ECC_EN_Msk       0x1UL
#define FLASHC_CM0_CA_CTL0_RAM_ECC_INJ_EN_Pos   1UL
#define FLASHC_CM0_CA_CTL0_RAM_ECC_INJ_EN_Msk   0x2UL
#define FLASHC_CM0_CA_CTL0_WAY_Pos              16UL
#define FLASHC_CM0_CA_CTL0_WAY_Msk              0x30000UL
#define FLASHC_CM0_CA_CTL0_SET_ADDR_Pos         24UL
#define FLASHC_CM0_CA_CTL0_SET_ADDR_Msk         0x7000000UL
#define FLASHC_CM0_CA_CTL0_PREF_EN_Pos          30UL
#define FLASHC_CM0_CA_CTL0_PREF_EN_Msk          0x40000000UL
#define FLASHC_CM0_CA_CTL0_CA_EN_Pos            31UL
#define FLASHC_CM0_CA_CTL0_CA_EN_Msk            0x80000000UL
/* FLASHC.CM0_CA_CTL1 */
#define FLASHC_CM0_CA_CTL1_PWR_MODE_Pos         0UL
#define FLASHC_CM0_CA_CTL1_PWR_MODE_Msk         0x3UL
#define FLASHC_CM0_CA_CTL1_VECTKEYSTAT_Pos      16UL
#define FLASHC_CM0_CA_CTL1_VECTKEYSTAT_Msk      0xFFFF0000UL
/* FLASHC.CM0_CA_CTL2 */
#define FLASHC_CM0_CA_CTL2_PWRUP_DELAY_Pos      0UL
#define FLASHC_CM0_CA_CTL2_PWRUP_DELAY_Msk      0x3FFUL
/* FLASHC.CM0_CA_STATUS0 */
#define FLASHC_CM0_CA_STATUS0_VALID32_Pos       0UL
#define FLASHC_CM0_CA_STATUS0_VALID32_Msk       0xFFFFFFFFUL
/* FLASHC.CM0_CA_STATUS1 */
#define FLASHC_CM0_CA_STATUS1_TAG_Pos           0UL
#define FLASHC_CM0_CA_STATUS1_TAG_Msk           0xFFFFFFFFUL
/* FLASHC.CM0_CA_STATUS2 */
#define FLASHC_CM0_CA_STATUS2_LRU_Pos           0UL
#define FLASHC_CM0_CA_STATUS2_LRU_Msk           0x3FUL
/* FLASHC.CM0_STATUS */
#define FLASHC_CM0_STATUS_MAIN_INTERNAL_ERR_Pos 0UL
#define FLASHC_CM0_STATUS_MAIN_INTERNAL_ERR_Msk 0x1UL
#define FLASHC_CM0_STATUS_WORK_INTERNAL_ERR_Pos 1UL
#define FLASHC_CM0_STATUS_WORK_INTERNAL_ERR_Msk 0x2UL
/* FLASHC.CM7_0_STATUS */
#define FLASHC_CM7_0_STATUS_MAIN_INTERNAL_ERR_Pos 0UL
#define FLASHC_CM7_0_STATUS_MAIN_INTERNAL_ERR_Msk 0x1UL
#define FLASHC_CM7_0_STATUS_WORK_INTERNAL_ERR_Pos 1UL
#define FLASHC_CM7_0_STATUS_WORK_INTERNAL_ERR_Msk 0x2UL
/* FLASHC.CM7_1_STATUS */
#define FLASHC_CM7_1_STATUS_MAIN_INTERNAL_ERR_Pos 0UL
#define FLASHC_CM7_1_STATUS_MAIN_INTERNAL_ERR_Msk 0x1UL
#define FLASHC_CM7_1_STATUS_WORK_INTERNAL_ERR_Pos 1UL
#define FLASHC_CM7_1_STATUS_WORK_INTERNAL_ERR_Msk 0x2UL
/* FLASHC.CRYPTO_BUFF_CTL */
#define FLASHC_CRYPTO_BUFF_CTL_PREF_EN_Pos      30UL
#define FLASHC_CRYPTO_BUFF_CTL_PREF_EN_Msk      0x40000000UL
/* FLASHC.DW0_BUFF_CTL */
#define FLASHC_DW0_BUFF_CTL_PREF_EN_Pos         30UL
#define FLASHC_DW0_BUFF_CTL_PREF_EN_Msk         0x40000000UL
/* FLASHC.DW1_BUFF_CTL */
#define FLASHC_DW1_BUFF_CTL_PREF_EN_Pos         30UL
#define FLASHC_DW1_BUFF_CTL_PREF_EN_Msk         0x40000000UL
/* FLASHC.DMAC_BUFF_CTL */
#define FLASHC_DMAC_BUFF_CTL_PREF_EN_Pos        30UL
#define FLASHC_DMAC_BUFF_CTL_PREF_EN_Msk        0x40000000UL
/* FLASHC.SLOW0_MS_BUFF_CTL */
#define FLASHC_SLOW0_MS_BUFF_CTL_PREF_EN_Pos    30UL
#define FLASHC_SLOW0_MS_BUFF_CTL_PREF_EN_Msk    0x40000000UL
/* FLASHC.SLOW1_MS_BUFF_CTL */
#define FLASHC_SLOW1_MS_BUFF_CTL_PREF_EN_Pos    30UL
#define FLASHC_SLOW1_MS_BUFF_CTL_PREF_EN_Msk    0x40000000UL


#endif /* _CYIP_FLASHC_H_ */


/* [] END OF FILE */
