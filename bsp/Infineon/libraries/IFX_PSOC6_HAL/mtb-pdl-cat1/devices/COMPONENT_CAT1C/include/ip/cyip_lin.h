/***************************************************************************//**
* \file cyip_lin.h
*
* \brief
* LIN IP definitions
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

#ifndef _CYIP_LIN_H_
#define _CYIP_LIN_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     LIN
*******************************************************************************/

#define LIN_CH_SECTION_SIZE                     0x00000100UL
#define LIN_SECTION_SIZE                        0x00010000UL

/**
  * \brief LIN channel structure (LIN_CH)
  */
typedef struct {
  __IOM uint32_t CTL0;                          /*!< 0x00000000 Control 0 */
  __IOM uint32_t CTL1;                          /*!< 0x00000004 Control 1 */
   __IM uint32_t STATUS;                        /*!< 0x00000008 Status */
   __IM uint32_t RESERVED;
  __IOM uint32_t CMD;                           /*!< 0x00000010 Command */
   __IM uint32_t RESERVED1[19];
  __IOM uint32_t TX_RX_STATUS;                  /*!< 0x00000060 TX/RX status */
   __IM uint32_t RESERVED2[7];
  __IOM uint32_t PID_CHECKSUM;                  /*!< 0x00000080 PID and checksum */
  __IOM uint32_t DATA0;                         /*!< 0x00000084 Response data 0 */
  __IOM uint32_t DATA1;                         /*!< 0x00000088 Response data 1 */
   __IM uint32_t RESERVED3[13];
  __IOM uint32_t INTR;                          /*!< 0x000000C0 Interrupt */
  __IOM uint32_t INTR_SET;                      /*!< 0x000000C4 Interrupt set */
  __IOM uint32_t INTR_MASK;                     /*!< 0x000000C8 Interrupt mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x000000CC Interrupt masked */
   __IM uint32_t RESERVED4[12];
} LIN_CH_Type;                                  /*!< Size = 256 (0x100) */

/**
  * \brief LIN (LIN)
  */
typedef struct {
  __IOM uint32_t ERROR_CTL;                     /*!< 0x00000000 Error control */
  __IOM uint32_t TEST_CTL;                      /*!< 0x00000004 Test control */
   __IM uint32_t RESERVED[8190];
        LIN_CH_Type CH[32];                     /*!< 0x00008000 LIN channel structure */
} LIN_Type;                                     /*!< Size = 40960 (0xA000) */


/* LIN_CH.CTL0 */
#define LIN_CH_CTL0_STOP_BITS_Pos               0UL
#define LIN_CH_CTL0_STOP_BITS_Msk               0x3UL
#define LIN_CH_CTL0_AUTO_EN_Pos                 4UL
#define LIN_CH_CTL0_AUTO_EN_Msk                 0x10UL
#define LIN_CH_CTL0_BREAK_DELIMITER_LENGTH_Pos  8UL
#define LIN_CH_CTL0_BREAK_DELIMITER_LENGTH_Msk  0x300UL
#define LIN_CH_CTL0_BREAK_WAKEUP_LENGTH_Pos     16UL
#define LIN_CH_CTL0_BREAK_WAKEUP_LENGTH_Msk     0x1F0000UL
#define LIN_CH_CTL0_MODE_Pos                    24UL
#define LIN_CH_CTL0_MODE_Msk                    0x1000000UL
#define LIN_CH_CTL0_BIT_ERROR_IGNORE_Pos        27UL
#define LIN_CH_CTL0_BIT_ERROR_IGNORE_Msk        0x8000000UL
#define LIN_CH_CTL0_PARITY_Pos                  28UL
#define LIN_CH_CTL0_PARITY_Msk                  0x10000000UL
#define LIN_CH_CTL0_PARITY_EN_Pos               29UL
#define LIN_CH_CTL0_PARITY_EN_Msk               0x20000000UL
#define LIN_CH_CTL0_FILTER_EN_Pos               30UL
#define LIN_CH_CTL0_FILTER_EN_Msk               0x40000000UL
#define LIN_CH_CTL0_ENABLED_Pos                 31UL
#define LIN_CH_CTL0_ENABLED_Msk                 0x80000000UL
/* LIN_CH.CTL1 */
#define LIN_CH_CTL1_DATA_NR_Pos                 0UL
#define LIN_CH_CTL1_DATA_NR_Msk                 0x7UL
#define LIN_CH_CTL1_CHECKSUM_ENHANCED_Pos       8UL
#define LIN_CH_CTL1_CHECKSUM_ENHANCED_Msk       0x100UL
#define LIN_CH_CTL1_FRAME_TIMEOUT_Pos           16UL
#define LIN_CH_CTL1_FRAME_TIMEOUT_Msk           0xFF0000UL
#define LIN_CH_CTL1_FRAME_TIMEOUT_SEL_Pos       24UL
#define LIN_CH_CTL1_FRAME_TIMEOUT_SEL_Msk       0x3000000UL
/* LIN_CH.STATUS */
#define LIN_CH_STATUS_DATA_IDX_Pos              0UL
#define LIN_CH_STATUS_DATA_IDX_Msk              0xFUL
#define LIN_CH_STATUS_HEADER_RESPONSE_Pos       4UL
#define LIN_CH_STATUS_HEADER_RESPONSE_Msk       0x10UL
#define LIN_CH_STATUS_RX_DATA0_FRAME_ERROR_Pos  5UL
#define LIN_CH_STATUS_RX_DATA0_FRAME_ERROR_Msk  0x20UL
#define LIN_CH_STATUS_TX_BUSY_Pos               8UL
#define LIN_CH_STATUS_TX_BUSY_Msk               0x100UL
#define LIN_CH_STATUS_RX_BUSY_Pos               9UL
#define LIN_CH_STATUS_RX_BUSY_Msk               0x200UL
#define LIN_CH_STATUS_TX_DONE_Pos               12UL
#define LIN_CH_STATUS_TX_DONE_Msk               0x1000UL
#define LIN_CH_STATUS_RX_DONE_Pos               13UL
#define LIN_CH_STATUS_RX_DONE_Msk               0x2000UL
#define LIN_CH_STATUS_TX_HEADER_BIT_ERROR_Pos   16UL
#define LIN_CH_STATUS_TX_HEADER_BIT_ERROR_Msk   0x10000UL
#define LIN_CH_STATUS_TX_RESPONSE_BIT_ERROR_Pos 17UL
#define LIN_CH_STATUS_TX_RESPONSE_BIT_ERROR_Msk 0x20000UL
#define LIN_CH_STATUS_RX_HEADER_FRAME_ERROR_Pos 24UL
#define LIN_CH_STATUS_RX_HEADER_FRAME_ERROR_Msk 0x1000000UL
#define LIN_CH_STATUS_RX_HEADER_SYNC_ERROR_Pos  25UL
#define LIN_CH_STATUS_RX_HEADER_SYNC_ERROR_Msk  0x2000000UL
#define LIN_CH_STATUS_RX_HEADER_PARITY_ERROR_Pos 26UL
#define LIN_CH_STATUS_RX_HEADER_PARITY_ERROR_Msk 0x4000000UL
#define LIN_CH_STATUS_RX_RESPONSE_FRAME_ERROR_Pos 27UL
#define LIN_CH_STATUS_RX_RESPONSE_FRAME_ERROR_Msk 0x8000000UL
#define LIN_CH_STATUS_RX_RESPONSE_CHECKSUM_ERROR_Pos 28UL
#define LIN_CH_STATUS_RX_RESPONSE_CHECKSUM_ERROR_Msk 0x10000000UL
/* LIN_CH.CMD */
#define LIN_CH_CMD_TX_HEADER_Pos                0UL
#define LIN_CH_CMD_TX_HEADER_Msk                0x1UL
#define LIN_CH_CMD_TX_RESPONSE_Pos              1UL
#define LIN_CH_CMD_TX_RESPONSE_Msk              0x2UL
#define LIN_CH_CMD_TX_WAKEUP_Pos                2UL
#define LIN_CH_CMD_TX_WAKEUP_Msk                0x4UL
#define LIN_CH_CMD_RX_HEADER_Pos                8UL
#define LIN_CH_CMD_RX_HEADER_Msk                0x100UL
#define LIN_CH_CMD_RX_RESPONSE_Pos              9UL
#define LIN_CH_CMD_RX_RESPONSE_Msk              0x200UL
/* LIN_CH.TX_RX_STATUS */
#define LIN_CH_TX_RX_STATUS_SYNC_COUNTER_Pos    0UL
#define LIN_CH_TX_RX_STATUS_SYNC_COUNTER_Msk    0xFFUL
#define LIN_CH_TX_RX_STATUS_TX_IN_Pos           16UL
#define LIN_CH_TX_RX_STATUS_TX_IN_Msk           0x10000UL
#define LIN_CH_TX_RX_STATUS_RX_IN_Pos           17UL
#define LIN_CH_TX_RX_STATUS_RX_IN_Msk           0x20000UL
#define LIN_CH_TX_RX_STATUS_TX_OUT_Pos          24UL
#define LIN_CH_TX_RX_STATUS_TX_OUT_Msk          0x1000000UL
#define LIN_CH_TX_RX_STATUS_EN_OUT_Pos          26UL
#define LIN_CH_TX_RX_STATUS_EN_OUT_Msk          0x4000000UL
/* LIN_CH.PID_CHECKSUM */
#define LIN_CH_PID_CHECKSUM_PID_Pos             0UL
#define LIN_CH_PID_CHECKSUM_PID_Msk             0xFFUL
#define LIN_CH_PID_CHECKSUM_CHECKSUM_Pos        8UL
#define LIN_CH_PID_CHECKSUM_CHECKSUM_Msk        0xFF00UL
/* LIN_CH.DATA0 */
#define LIN_CH_DATA0_DATA1_Pos                  0UL
#define LIN_CH_DATA0_DATA1_Msk                  0xFFUL
#define LIN_CH_DATA0_DATA2_Pos                  8UL
#define LIN_CH_DATA0_DATA2_Msk                  0xFF00UL
#define LIN_CH_DATA0_DATA3_Pos                  16UL
#define LIN_CH_DATA0_DATA3_Msk                  0xFF0000UL
#define LIN_CH_DATA0_DATA4_Pos                  24UL
#define LIN_CH_DATA0_DATA4_Msk                  0xFF000000UL
/* LIN_CH.DATA1 */
#define LIN_CH_DATA1_DATA5_Pos                  0UL
#define LIN_CH_DATA1_DATA5_Msk                  0xFFUL
#define LIN_CH_DATA1_DATA6_Pos                  8UL
#define LIN_CH_DATA1_DATA6_Msk                  0xFF00UL
#define LIN_CH_DATA1_DATA7_Pos                  16UL
#define LIN_CH_DATA1_DATA7_Msk                  0xFF0000UL
#define LIN_CH_DATA1_DATA8_Pos                  24UL
#define LIN_CH_DATA1_DATA8_Msk                  0xFF000000UL
/* LIN_CH.INTR */
#define LIN_CH_INTR_TX_HEADER_DONE_Pos          0UL
#define LIN_CH_INTR_TX_HEADER_DONE_Msk          0x1UL
#define LIN_CH_INTR_TX_RESPONSE_DONE_Pos        1UL
#define LIN_CH_INTR_TX_RESPONSE_DONE_Msk        0x2UL
#define LIN_CH_INTR_TX_WAKEUP_DONE_Pos          2UL
#define LIN_CH_INTR_TX_WAKEUP_DONE_Msk          0x4UL
#define LIN_CH_INTR_RX_HEADER_DONE_Pos          8UL
#define LIN_CH_INTR_RX_HEADER_DONE_Msk          0x100UL
#define LIN_CH_INTR_RX_RESPONSE_DONE_Pos        9UL
#define LIN_CH_INTR_RX_RESPONSE_DONE_Msk        0x200UL
#define LIN_CH_INTR_RX_BREAK_WAKEUP_DONE_Pos    10UL
#define LIN_CH_INTR_RX_BREAK_WAKEUP_DONE_Msk    0x400UL
#define LIN_CH_INTR_RX_HEADER_SYNC_DONE_Pos     11UL
#define LIN_CH_INTR_RX_HEADER_SYNC_DONE_Msk     0x800UL
#define LIN_CH_INTR_RX_NOISE_DETECT_Pos         13UL
#define LIN_CH_INTR_RX_NOISE_DETECT_Msk         0x2000UL
#define LIN_CH_INTR_TIMEOUT_Pos                 14UL
#define LIN_CH_INTR_TIMEOUT_Msk                 0x4000UL
#define LIN_CH_INTR_TX_HEADER_BIT_ERROR_Pos     16UL
#define LIN_CH_INTR_TX_HEADER_BIT_ERROR_Msk     0x10000UL
#define LIN_CH_INTR_TX_RESPONSE_BIT_ERROR_Pos   17UL
#define LIN_CH_INTR_TX_RESPONSE_BIT_ERROR_Msk   0x20000UL
#define LIN_CH_INTR_RX_HEADER_FRAME_ERROR_Pos   24UL
#define LIN_CH_INTR_RX_HEADER_FRAME_ERROR_Msk   0x1000000UL
#define LIN_CH_INTR_RX_HEADER_SYNC_ERROR_Pos    25UL
#define LIN_CH_INTR_RX_HEADER_SYNC_ERROR_Msk    0x2000000UL
#define LIN_CH_INTR_RX_HEADER_PARITY_ERROR_Pos  26UL
#define LIN_CH_INTR_RX_HEADER_PARITY_ERROR_Msk  0x4000000UL
#define LIN_CH_INTR_RX_RESPONSE_FRAME_ERROR_Pos 27UL
#define LIN_CH_INTR_RX_RESPONSE_FRAME_ERROR_Msk 0x8000000UL
#define LIN_CH_INTR_RX_RESPONSE_CHECKSUM_ERROR_Pos 28UL
#define LIN_CH_INTR_RX_RESPONSE_CHECKSUM_ERROR_Msk 0x10000000UL
/* LIN_CH.INTR_SET */
#define LIN_CH_INTR_SET_TX_HEADER_DONE_Pos      0UL
#define LIN_CH_INTR_SET_TX_HEADER_DONE_Msk      0x1UL
#define LIN_CH_INTR_SET_TX_RESPONSE_DONE_Pos    1UL
#define LIN_CH_INTR_SET_TX_RESPONSE_DONE_Msk    0x2UL
#define LIN_CH_INTR_SET_TX_WAKEUP_DONE_Pos      2UL
#define LIN_CH_INTR_SET_TX_WAKEUP_DONE_Msk      0x4UL
#define LIN_CH_INTR_SET_RX_HEADER_DONE_Pos      8UL
#define LIN_CH_INTR_SET_RX_HEADER_DONE_Msk      0x100UL
#define LIN_CH_INTR_SET_RX_RESPONSE_DONE_Pos    9UL
#define LIN_CH_INTR_SET_RX_RESPONSE_DONE_Msk    0x200UL
#define LIN_CH_INTR_SET_RX_BREAK_WAKEUP_DONE_Pos 10UL
#define LIN_CH_INTR_SET_RX_BREAK_WAKEUP_DONE_Msk 0x400UL
#define LIN_CH_INTR_SET_RX_HEADER_SYNC_DONE_Pos 11UL
#define LIN_CH_INTR_SET_RX_HEADER_SYNC_DONE_Msk 0x800UL
#define LIN_CH_INTR_SET_RX_NOISE_DETECT_Pos     13UL
#define LIN_CH_INTR_SET_RX_NOISE_DETECT_Msk     0x2000UL
#define LIN_CH_INTR_SET_TIMEOUT_Pos             14UL
#define LIN_CH_INTR_SET_TIMEOUT_Msk             0x4000UL
#define LIN_CH_INTR_SET_TX_HEADER_BIT_ERROR_Pos 16UL
#define LIN_CH_INTR_SET_TX_HEADER_BIT_ERROR_Msk 0x10000UL
#define LIN_CH_INTR_SET_TX_RESPONSE_BIT_ERROR_Pos 17UL
#define LIN_CH_INTR_SET_TX_RESPONSE_BIT_ERROR_Msk 0x20000UL
#define LIN_CH_INTR_SET_RX_HEADER_FRAME_ERROR_Pos 24UL
#define LIN_CH_INTR_SET_RX_HEADER_FRAME_ERROR_Msk 0x1000000UL
#define LIN_CH_INTR_SET_RX_HEADER_SYNC_ERROR_Pos 25UL
#define LIN_CH_INTR_SET_RX_HEADER_SYNC_ERROR_Msk 0x2000000UL
#define LIN_CH_INTR_SET_RX_HEADER_PARITY_ERROR_Pos 26UL
#define LIN_CH_INTR_SET_RX_HEADER_PARITY_ERROR_Msk 0x4000000UL
#define LIN_CH_INTR_SET_RX_RESPONSE_FRAME_ERROR_Pos 27UL
#define LIN_CH_INTR_SET_RX_RESPONSE_FRAME_ERROR_Msk 0x8000000UL
#define LIN_CH_INTR_SET_RX_RESPONSE_CHECKSUM_ERROR_Pos 28UL
#define LIN_CH_INTR_SET_RX_RESPONSE_CHECKSUM_ERROR_Msk 0x10000000UL
/* LIN_CH.INTR_MASK */
#define LIN_CH_INTR_MASK_TX_HEADER_DONE_Pos     0UL
#define LIN_CH_INTR_MASK_TX_HEADER_DONE_Msk     0x1UL
#define LIN_CH_INTR_MASK_TX_RESPONSE_DONE_Pos   1UL
#define LIN_CH_INTR_MASK_TX_RESPONSE_DONE_Msk   0x2UL
#define LIN_CH_INTR_MASK_TX_WAKEUP_DONE_Pos     2UL
#define LIN_CH_INTR_MASK_TX_WAKEUP_DONE_Msk     0x4UL
#define LIN_CH_INTR_MASK_RX_HEADER_DONE_Pos     8UL
#define LIN_CH_INTR_MASK_RX_HEADER_DONE_Msk     0x100UL
#define LIN_CH_INTR_MASK_RX_RESPONSE_DONE_Pos   9UL
#define LIN_CH_INTR_MASK_RX_RESPONSE_DONE_Msk   0x200UL
#define LIN_CH_INTR_MASK_RX_BREAK_WAKEUP_DONE_Pos 10UL
#define LIN_CH_INTR_MASK_RX_BREAK_WAKEUP_DONE_Msk 0x400UL
#define LIN_CH_INTR_MASK_RX_HEADER_SYNC_DONE_Pos 11UL
#define LIN_CH_INTR_MASK_RX_HEADER_SYNC_DONE_Msk 0x800UL
#define LIN_CH_INTR_MASK_RX_NOISE_DETECT_Pos    13UL
#define LIN_CH_INTR_MASK_RX_NOISE_DETECT_Msk    0x2000UL
#define LIN_CH_INTR_MASK_TIMEOUT_Pos            14UL
#define LIN_CH_INTR_MASK_TIMEOUT_Msk            0x4000UL
#define LIN_CH_INTR_MASK_TX_HEADER_BIT_ERROR_Pos 16UL
#define LIN_CH_INTR_MASK_TX_HEADER_BIT_ERROR_Msk 0x10000UL
#define LIN_CH_INTR_MASK_TX_RESPONSE_BIT_ERROR_Pos 17UL
#define LIN_CH_INTR_MASK_TX_RESPONSE_BIT_ERROR_Msk 0x20000UL
#define LIN_CH_INTR_MASK_RX_HEADER_FRAME_ERROR_Pos 24UL
#define LIN_CH_INTR_MASK_RX_HEADER_FRAME_ERROR_Msk 0x1000000UL
#define LIN_CH_INTR_MASK_RX_HEADER_SYNC_ERROR_Pos 25UL
#define LIN_CH_INTR_MASK_RX_HEADER_SYNC_ERROR_Msk 0x2000000UL
#define LIN_CH_INTR_MASK_RX_HEADER_PARITY_ERROR_Pos 26UL
#define LIN_CH_INTR_MASK_RX_HEADER_PARITY_ERROR_Msk 0x4000000UL
#define LIN_CH_INTR_MASK_RX_RESPONSE_FRAME_ERROR_Pos 27UL
#define LIN_CH_INTR_MASK_RX_RESPONSE_FRAME_ERROR_Msk 0x8000000UL
#define LIN_CH_INTR_MASK_RX_RESPONSE_CHECKSUM_ERROR_Pos 28UL
#define LIN_CH_INTR_MASK_RX_RESPONSE_CHECKSUM_ERROR_Msk 0x10000000UL
/* LIN_CH.INTR_MASKED */
#define LIN_CH_INTR_MASKED_TX_HEADER_DONE_Pos   0UL
#define LIN_CH_INTR_MASKED_TX_HEADER_DONE_Msk   0x1UL
#define LIN_CH_INTR_MASKED_TX_RESPONSE_DONE_Pos 1UL
#define LIN_CH_INTR_MASKED_TX_RESPONSE_DONE_Msk 0x2UL
#define LIN_CH_INTR_MASKED_TX_WAKEUP_DONE_Pos   2UL
#define LIN_CH_INTR_MASKED_TX_WAKEUP_DONE_Msk   0x4UL
#define LIN_CH_INTR_MASKED_RX_HEADER_DONE_Pos   8UL
#define LIN_CH_INTR_MASKED_RX_HEADER_DONE_Msk   0x100UL
#define LIN_CH_INTR_MASKED_RX_RESPONSE_DONE_Pos 9UL
#define LIN_CH_INTR_MASKED_RX_RESPONSE_DONE_Msk 0x200UL
#define LIN_CH_INTR_MASKED_RX_BREAK_WAKEUP_DONE_Pos 10UL
#define LIN_CH_INTR_MASKED_RX_BREAK_WAKEUP_DONE_Msk 0x400UL
#define LIN_CH_INTR_MASKED_RX_HEADER_SYNC_DONE_Pos 11UL
#define LIN_CH_INTR_MASKED_RX_HEADER_SYNC_DONE_Msk 0x800UL
#define LIN_CH_INTR_MASKED_RX_NOISE_DETECT_Pos  13UL
#define LIN_CH_INTR_MASKED_RX_NOISE_DETECT_Msk  0x2000UL
#define LIN_CH_INTR_MASKED_TIMEOUT_Pos          14UL
#define LIN_CH_INTR_MASKED_TIMEOUT_Msk          0x4000UL
#define LIN_CH_INTR_MASKED_TX_HEADER_BIT_ERROR_Pos 16UL
#define LIN_CH_INTR_MASKED_TX_HEADER_BIT_ERROR_Msk 0x10000UL
#define LIN_CH_INTR_MASKED_TX_RESPONSE_BIT_ERROR_Pos 17UL
#define LIN_CH_INTR_MASKED_TX_RESPONSE_BIT_ERROR_Msk 0x20000UL
#define LIN_CH_INTR_MASKED_RX_HEADER_FRAME_ERROR_Pos 24UL
#define LIN_CH_INTR_MASKED_RX_HEADER_FRAME_ERROR_Msk 0x1000000UL
#define LIN_CH_INTR_MASKED_RX_HEADER_SYNC_ERROR_Pos 25UL
#define LIN_CH_INTR_MASKED_RX_HEADER_SYNC_ERROR_Msk 0x2000000UL
#define LIN_CH_INTR_MASKED_RX_HEADER_PARITY_ERROR_Pos 26UL
#define LIN_CH_INTR_MASKED_RX_HEADER_PARITY_ERROR_Msk 0x4000000UL
#define LIN_CH_INTR_MASKED_RX_RESPONSE_FRAME_ERROR_Pos 27UL
#define LIN_CH_INTR_MASKED_RX_RESPONSE_FRAME_ERROR_Msk 0x8000000UL
#define LIN_CH_INTR_MASKED_RX_RESPONSE_CHECKSUM_ERROR_Pos 28UL
#define LIN_CH_INTR_MASKED_RX_RESPONSE_CHECKSUM_ERROR_Msk 0x10000000UL


/* LIN.ERROR_CTL */
#define LIN_ERROR_CTL_CH_IDX_Pos                0UL
#define LIN_ERROR_CTL_CH_IDX_Msk                0x1FUL
#define LIN_ERROR_CTL_TX_SYNC_ERROR_Pos         16UL
#define LIN_ERROR_CTL_TX_SYNC_ERROR_Msk         0x10000UL
#define LIN_ERROR_CTL_TX_SYNC_STOP_ERROR_Pos    17UL
#define LIN_ERROR_CTL_TX_SYNC_STOP_ERROR_Msk    0x20000UL
#define LIN_ERROR_CTL_TX_PARITY_ERROR_Pos       18UL
#define LIN_ERROR_CTL_TX_PARITY_ERROR_Msk       0x40000UL
#define LIN_ERROR_CTL_TX_PID_STOP_ERROR_Pos     19UL
#define LIN_ERROR_CTL_TX_PID_STOP_ERROR_Msk     0x80000UL
#define LIN_ERROR_CTL_TX_DATA_STOP_ERROR_Pos    21UL
#define LIN_ERROR_CTL_TX_DATA_STOP_ERROR_Msk    0x200000UL
#define LIN_ERROR_CTL_TX_CHECKSUM_ERROR_Pos     22UL
#define LIN_ERROR_CTL_TX_CHECKSUM_ERROR_Msk     0x400000UL
#define LIN_ERROR_CTL_TX_CHECKSUM_STOP_ERROR_Pos 23UL
#define LIN_ERROR_CTL_TX_CHECKSUM_STOP_ERROR_Msk 0x800000UL
#define LIN_ERROR_CTL_ENABLED_Pos               31UL
#define LIN_ERROR_CTL_ENABLED_Msk               0x80000000UL
/* LIN.TEST_CTL */
#define LIN_TEST_CTL_CH_IDX_Pos                 0UL
#define LIN_TEST_CTL_CH_IDX_Msk                 0x1FUL
#define LIN_TEST_CTL_MODE_Pos                   16UL
#define LIN_TEST_CTL_MODE_Msk                   0x10000UL
#define LIN_TEST_CTL_ENABLED_Pos                31UL
#define LIN_TEST_CTL_ENABLED_Msk                0x80000000UL


#endif /* _CYIP_LIN_H_ */


/* [] END OF FILE */
