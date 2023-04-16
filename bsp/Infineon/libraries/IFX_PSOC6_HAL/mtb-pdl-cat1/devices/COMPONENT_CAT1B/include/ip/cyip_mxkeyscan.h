/***************************************************************************//**
* \file cyip_mxkeyscan.h
*
* \brief
* MXKEYSCAN IP definitions
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

#ifndef _CYIP_MXKEYSCAN_H_
#define _CYIP_MXKEYSCAN_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                  MXKEYSCAN
*******************************************************************************/

#define MXKEYSCAN_SECTION_SIZE                  0x00001000UL

/**
  * \brief 0 (MXKEYSCAN)
  */
typedef struct {
  __IOM uint32_t KEYSCAN_CTL;                   /*!< 0x00000000 Keyscan Control Reg */
  __IOM uint32_t DEBOUNCE;                      /*!< 0x00000004 Debounce (micro/macro) */
   __IM uint32_t KEYFIFO_CNT;                   /*!< 0x00000008 Number of entries in Key FIFO */
   __IM uint32_t KEYFIFO;                       /*!< 0x0000000C KEYFIFO values */
   __IM uint32_t RESERVED;
  __IOM uint32_t MIA_CTL;                       /*!< 0x00000014 MIA CTL (legacy) */
   __IM uint32_t MIA_STATUS;                    /*!< 0x00000018 MIA STAUS (Legacy) */
  __IOM uint32_t KSI_USED;                      /*!< 0x0000001C Number of input key rows */
  __IOM uint32_t INTR;                          /*!< 0x00000020 Interrupt */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000024 Interrupt set */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000028 Interrupt mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000002C Interrupt mask */
} MXKEYSCAN_Type;                               /*!< Size = 48 (0x30) */


/* MXKEYSCAN.KEYSCAN_CTL */
#define MXKEYSCAN_KEYSCAN_CTL_KS_EN_Pos         0UL
#define MXKEYSCAN_KEYSCAN_CTL_KS_EN_Msk         0x1UL
#define MXKEYSCAN_KEYSCAN_CTL_GHOST_EN_Pos      2UL
#define MXKEYSCAN_KEYSCAN_CTL_GHOST_EN_Msk      0x4UL
#define MXKEYSCAN_KEYSCAN_CTL_KS_INT_EN_Pos     3UL
#define MXKEYSCAN_KEYSCAN_CTL_KS_INT_EN_Msk     0x8UL
#define MXKEYSCAN_KEYSCAN_CTL_KYS_RST_EN_Pos    4UL
#define MXKEYSCAN_KEYSCAN_CTL_KYS_RST_EN_Msk    0x10UL
#define MXKEYSCAN_KEYSCAN_CTL_RC_EXT_Pos        6UL
#define MXKEYSCAN_KEYSCAN_CTL_RC_EXT_Msk        0xC0UL
#define MXKEYSCAN_KEYSCAN_CTL_RCTC_ROW_Pos      8UL
#define MXKEYSCAN_KEYSCAN_CTL_RCTC_ROW_Msk      0x700UL
#define MXKEYSCAN_KEYSCAN_CTL_RCTC_COLUMN_Pos   11UL
#define MXKEYSCAN_KEYSCAN_CTL_RCTC_COLUMN_Msk   0xF800UL
#define MXKEYSCAN_KEYSCAN_CTL_PULL_HIGH_Pos     16UL
#define MXKEYSCAN_KEYSCAN_CTL_PULL_HIGH_Msk     0x10000UL
#define MXKEYSCAN_KEYSCAN_CTL_KSI_DRV_HIGH_Pos  17UL
#define MXKEYSCAN_KEYSCAN_CTL_KSI_DRV_HIGH_Msk  0x20000UL
#define MXKEYSCAN_KEYSCAN_CTL_KYSCLK_STAYON_Pos 18UL
#define MXKEYSCAN_KEYSCAN_CTL_KYSCLK_STAYON_Msk 0x40000UL
/* MXKEYSCAN.DEBOUNCE */
#define MXKEYSCAN_DEBOUNCE_MD_DEBOUNCE_Pos      0UL
#define MXKEYSCAN_DEBOUNCE_MD_DEBOUNCE_Msk      0xFUL
#define MXKEYSCAN_DEBOUNCE_MU_DEBOUNCE_Pos      4UL
#define MXKEYSCAN_DEBOUNCE_MU_DEBOUNCE_Msk      0xF0UL
#define MXKEYSCAN_DEBOUNCE_U_DEBOUNCE_Pos       8UL
#define MXKEYSCAN_DEBOUNCE_U_DEBOUNCE_Msk       0x300UL
/* MXKEYSCAN.KEYFIFO_CNT */
#define MXKEYSCAN_KEYFIFO_CNT_KEYFIFO_CNT_Pos   0UL
#define MXKEYSCAN_KEYFIFO_CNT_KEYFIFO_CNT_Msk   0x1FUL
/* MXKEYSCAN.KEYFIFO */
#define MXKEYSCAN_KEYFIFO_KEYFIFO_Pos           0UL
#define MXKEYSCAN_KEYFIFO_KEYFIFO_Msk           0xFFUL
#define MXKEYSCAN_KEYFIFO_TRACK_SCAN_CYCLE_Pos  30UL
#define MXKEYSCAN_KEYFIFO_TRACK_SCAN_CYCLE_Msk  0x40000000UL
#define MXKEYSCAN_KEYFIFO_KEY_UP_DOWN_Pos       31UL
#define MXKEYSCAN_KEYFIFO_KEY_UP_DOWN_Msk       0x80000000UL
/* MXKEYSCAN.MIA_CTL */
#define MXKEYSCAN_MIA_CTL_FREEZE_MIA_Pos        0UL
#define MXKEYSCAN_MIA_CTL_FREEZE_MIA_Msk        0x1UL
#define MXKEYSCAN_MIA_CTL_REPORTED_CLEAR_KYS_Pos 1UL
#define MXKEYSCAN_MIA_CTL_REPORTED_CLEAR_KYS_Msk 0x2UL
#define MXKEYSCAN_MIA_CTL_CLK_LF_SEL_Pos        2UL
#define MXKEYSCAN_MIA_CTL_CLK_LF_SEL_Msk        0x4UL
/* MXKEYSCAN.MIA_STATUS */
#define MXKEYSCAN_MIA_STATUS_MIA_CLOCK_FREEZED_STATUS_Pos 0UL
#define MXKEYSCAN_MIA_STATUS_MIA_CLOCK_FREEZED_STATUS_Msk 0x1UL
#define MXKEYSCAN_MIA_STATUS_KEYCODE_SET_STATUS_Pos 1UL
#define MXKEYSCAN_MIA_STATUS_KEYCODE_SET_STATUS_Msk 0x2UL
#define MXKEYSCAN_MIA_STATUS_OVERFLOW_STATUS_Pos 2UL
#define MXKEYSCAN_MIA_STATUS_OVERFLOW_STATUS_Msk 0x4UL
#define MXKEYSCAN_MIA_STATUS_GHOST_STATUS_Pos   3UL
#define MXKEYSCAN_MIA_STATUS_GHOST_STATUS_Msk   0x8UL
#define MXKEYSCAN_MIA_STATUS_KYS_INT_SYNC_STATUS_Pos 5UL
#define MXKEYSCAN_MIA_STATUS_KYS_INT_SYNC_STATUS_Msk 0x20UL
#define MXKEYSCAN_MIA_STATUS_CLK_G_TO_KYS_DBG_Pos 6UL
#define MXKEYSCAN_MIA_STATUS_CLK_G_TO_KYS_DBG_Msk 0x40UL
/* MXKEYSCAN.KSI_USED */
#define MXKEYSCAN_KSI_USED_KSI_USED_Pos         0UL
#define MXKEYSCAN_KSI_USED_KSI_USED_Msk         0x7UL
/* MXKEYSCAN.INTR */
#define MXKEYSCAN_INTR_KEY_EDGE_Pos             0UL
#define MXKEYSCAN_INTR_KEY_EDGE_Msk             0x1UL
#define MXKEYSCAN_INTR_FIFO_THRESH_Pos          1UL
#define MXKEYSCAN_INTR_FIFO_THRESH_Msk          0x2UL
/* MXKEYSCAN.INTR_SET */
#define MXKEYSCAN_INTR_SET_KEY_EDGE_Pos         0UL
#define MXKEYSCAN_INTR_SET_KEY_EDGE_Msk         0x1UL
#define MXKEYSCAN_INTR_SET_FIFO_THRESH_Pos      1UL
#define MXKEYSCAN_INTR_SET_FIFO_THRESH_Msk      0x2UL
/* MXKEYSCAN.INTR_MASK */
#define MXKEYSCAN_INTR_MASK_KEY_EDGE_Pos        0UL
#define MXKEYSCAN_INTR_MASK_KEY_EDGE_Msk        0x1UL
#define MXKEYSCAN_INTR_MASK_FIFO_THRESH_Pos     1UL
#define MXKEYSCAN_INTR_MASK_FIFO_THRESH_Msk     0x2UL
/* MXKEYSCAN.INTR_MASKED */
#define MXKEYSCAN_INTR_MASKED_KEY_EDGE_Pos      0UL
#define MXKEYSCAN_INTR_MASKED_KEY_EDGE_Msk      0x1UL
#define MXKEYSCAN_INTR_MASKED_FIFO_THRESH_Pos   1UL
#define MXKEYSCAN_INTR_MASKED_FIFO_THRESH_Msk   0x2UL


#endif /* _CYIP_MXKEYSCAN_H_ */


/* [] END OF FILE */
