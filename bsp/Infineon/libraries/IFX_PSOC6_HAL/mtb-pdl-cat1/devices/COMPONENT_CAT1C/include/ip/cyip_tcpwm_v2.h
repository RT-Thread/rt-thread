/***************************************************************************//**
* \file cyip_tcpwm_v2.h
*
* \brief
* TCPWM IP definitions
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

#ifndef _CYIP_TCPWM_V2_H_
#define _CYIP_TCPWM_V2_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    TCPWM
*******************************************************************************/

#define TCPWM_GRP_CNT_SECTION_SIZE              0x00000080UL
#define TCPWM_GRP_SECTION_SIZE                  0x00008000UL
#define TCPWM_SECTION_SIZE                      0x00020000UL

/**
  * \brief Timer/Counter/PWM Counter Module (TCPWM_GRP_CNT)
  */
typedef struct {
  __IOM uint32_t CTRL;                          /*!< 0x00000000 Counter control register */
   __IM uint32_t STATUS;                        /*!< 0x00000004 Counter status register */
  __IOM uint32_t COUNTER;                       /*!< 0x00000008 Counter count register */
   __IM uint32_t RESERVED;
  __IOM uint32_t CC0;                           /*!< 0x00000010 Counter compare/capture 0 register */
  __IOM uint32_t CC0_BUFF;                      /*!< 0x00000014 Counter buffered compare/capture 0 register */
  __IOM uint32_t CC1;                           /*!< 0x00000018 Counter compare/capture 1 register */
  __IOM uint32_t CC1_BUFF;                      /*!< 0x0000001C Counter buffered compare/capture 1 register */
  __IOM uint32_t PERIOD;                        /*!< 0x00000020 Counter period register */
  __IOM uint32_t PERIOD_BUFF;                   /*!< 0x00000024 Counter buffered period register */
  __IOM uint32_t LINE_SEL;                      /*!< 0x00000028 Counter line selection register */
  __IOM uint32_t LINE_SEL_BUFF;                 /*!< 0x0000002C Counter buffered line selection register */
  __IOM uint32_t DT;                            /*!< 0x00000030 Counter PWM dead time register */
   __IM uint32_t RESERVED1[3];
  __IOM uint32_t TR_CMD;                        /*!< 0x00000040 Counter trigger command register */
  __IOM uint32_t TR_IN_SEL0;                    /*!< 0x00000044 Counter input trigger selection register 0 */
  __IOM uint32_t TR_IN_SEL1;                    /*!< 0x00000048 Counter input trigger selection register 1 */
  __IOM uint32_t TR_IN_EDGE_SEL;                /*!< 0x0000004C Counter input trigger edge selection register */
  __IOM uint32_t TR_PWM_CTRL;                   /*!< 0x00000050 Counter trigger PWM control register */
  __IOM uint32_t TR_OUT_SEL;                    /*!< 0x00000054 Counter output trigger selection register */
   __IM uint32_t RESERVED2[6];
  __IOM uint32_t INTR;                          /*!< 0x00000070 Interrupt request register */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000074 Interrupt set request register */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000078 Interrupt mask register */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000007C Interrupt masked request register */
} TCPWM_GRP_CNT_Type;                           /*!< Size = 128 (0x80) */

/**
  * \brief Group of counters (TCPWM_GRP)
  */
typedef struct {
        TCPWM_GRP_CNT_Type CNT[256];            /*!< 0x00000000 Timer/Counter/PWM Counter Module */
} TCPWM_GRP_Type;                               /*!< Size = 32768 (0x8000) */

/**
  * \brief Timer/Counter/PWM (TCPWM)
  */
typedef struct {
        TCPWM_GRP_Type GRP[4];                  /*!< 0x00000000 Group of counters */
} TCPWM_Type;                                   /*!< Size = 131072 (0x20000) */


/* TCPWM_GRP_CNT.CTRL */
#define TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC0_Pos  0UL
#define TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC0_Msk  0x1UL
#define TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC1_Pos  1UL
#define TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC1_Msk  0x2UL
#define TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_PERIOD_Pos 2UL
#define TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_PERIOD_Msk 0x4UL
#define TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_LINE_SEL_Pos 3UL
#define TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_LINE_SEL_Msk 0x8UL
#define TCPWM_GRP_CNT_CTRL_CC0_MATCH_UP_EN_Pos  4UL
#define TCPWM_GRP_CNT_CTRL_CC0_MATCH_UP_EN_Msk  0x10UL
#define TCPWM_GRP_CNT_CTRL_CC0_MATCH_DOWN_EN_Pos 5UL
#define TCPWM_GRP_CNT_CTRL_CC0_MATCH_DOWN_EN_Msk 0x20UL
#define TCPWM_GRP_CNT_CTRL_CC1_MATCH_UP_EN_Pos  6UL
#define TCPWM_GRP_CNT_CTRL_CC1_MATCH_UP_EN_Msk  0x40UL
#define TCPWM_GRP_CNT_CTRL_CC1_MATCH_DOWN_EN_Pos 7UL
#define TCPWM_GRP_CNT_CTRL_CC1_MATCH_DOWN_EN_Msk 0x80UL
#define TCPWM_GRP_CNT_CTRL_PWM_IMM_KILL_Pos     8UL
#define TCPWM_GRP_CNT_CTRL_PWM_IMM_KILL_Msk     0x100UL
#define TCPWM_GRP_CNT_CTRL_PWM_STOP_ON_KILL_Pos 9UL
#define TCPWM_GRP_CNT_CTRL_PWM_STOP_ON_KILL_Msk 0x200UL
#define TCPWM_GRP_CNT_CTRL_PWM_SYNC_KILL_Pos    10UL
#define TCPWM_GRP_CNT_CTRL_PWM_SYNC_KILL_Msk    0x400UL
#define TCPWM_GRP_CNT_CTRL_PWM_DISABLE_MODE_Pos 12UL
#define TCPWM_GRP_CNT_CTRL_PWM_DISABLE_MODE_Msk 0x3000UL
#define TCPWM_GRP_CNT_CTRL_UP_DOWN_MODE_Pos     16UL
#define TCPWM_GRP_CNT_CTRL_UP_DOWN_MODE_Msk     0x30000UL
#define TCPWM_GRP_CNT_CTRL_ONE_SHOT_Pos         18UL
#define TCPWM_GRP_CNT_CTRL_ONE_SHOT_Msk         0x40000UL
#define TCPWM_GRP_CNT_CTRL_QUAD_ENCODING_MODE_Pos 20UL
#define TCPWM_GRP_CNT_CTRL_QUAD_ENCODING_MODE_Msk 0x300000UL
#define TCPWM_GRP_CNT_CTRL_MODE_Pos             24UL
#define TCPWM_GRP_CNT_CTRL_MODE_Msk             0x7000000UL
#define TCPWM_GRP_CNT_CTRL_DBG_FREEZE_EN_Pos    30UL
#define TCPWM_GRP_CNT_CTRL_DBG_FREEZE_EN_Msk    0x40000000UL
#define TCPWM_GRP_CNT_CTRL_ENABLED_Pos          31UL
#define TCPWM_GRP_CNT_CTRL_ENABLED_Msk          0x80000000UL
/* TCPWM_GRP_CNT.STATUS */
#define TCPWM_GRP_CNT_STATUS_DOWN_Pos           0UL
#define TCPWM_GRP_CNT_STATUS_DOWN_Msk           0x1UL
#define TCPWM_GRP_CNT_STATUS_TR_CAPTURE0_Pos    4UL
#define TCPWM_GRP_CNT_STATUS_TR_CAPTURE0_Msk    0x10UL
#define TCPWM_GRP_CNT_STATUS_TR_COUNT_Pos       5UL
#define TCPWM_GRP_CNT_STATUS_TR_COUNT_Msk       0x20UL
#define TCPWM_GRP_CNT_STATUS_TR_RELOAD_Pos      6UL
#define TCPWM_GRP_CNT_STATUS_TR_RELOAD_Msk      0x40UL
#define TCPWM_GRP_CNT_STATUS_TR_STOP_Pos        7UL
#define TCPWM_GRP_CNT_STATUS_TR_STOP_Msk        0x80UL
#define TCPWM_GRP_CNT_STATUS_TR_START_Pos       8UL
#define TCPWM_GRP_CNT_STATUS_TR_START_Msk       0x100UL
#define TCPWM_GRP_CNT_STATUS_TR_CAPTURE1_Pos    9UL
#define TCPWM_GRP_CNT_STATUS_TR_CAPTURE1_Msk    0x200UL
#define TCPWM_GRP_CNT_STATUS_LINE_OUT_Pos       10UL
#define TCPWM_GRP_CNT_STATUS_LINE_OUT_Msk       0x400UL
#define TCPWM_GRP_CNT_STATUS_LINE_COMPL_OUT_Pos 11UL
#define TCPWM_GRP_CNT_STATUS_LINE_COMPL_OUT_Msk 0x800UL
#define TCPWM_GRP_CNT_STATUS_RUNNING_Pos        15UL
#define TCPWM_GRP_CNT_STATUS_RUNNING_Msk        0x8000UL
#define TCPWM_GRP_CNT_STATUS_DT_CNT_L_Pos       16UL
#define TCPWM_GRP_CNT_STATUS_DT_CNT_L_Msk       0xFF0000UL
#define TCPWM_GRP_CNT_STATUS_DT_CNT_H_Pos       24UL
#define TCPWM_GRP_CNT_STATUS_DT_CNT_H_Msk       0xFF000000UL
/* TCPWM_GRP_CNT.COUNTER */
#define TCPWM_GRP_CNT_COUNTER_COUNTER_Pos       0UL
#define TCPWM_GRP_CNT_COUNTER_COUNTER_Msk       0xFFFFFFFFUL
/* TCPWM_GRP_CNT.CC0 */
#define TCPWM_GRP_CNT_CC0_CC_Pos                0UL
#define TCPWM_GRP_CNT_CC0_CC_Msk                0xFFFFFFFFUL
/* TCPWM_GRP_CNT.CC0_BUFF */
#define TCPWM_GRP_CNT_CC0_BUFF_CC_Pos           0UL
#define TCPWM_GRP_CNT_CC0_BUFF_CC_Msk           0xFFFFFFFFUL
/* TCPWM_GRP_CNT.CC1 */
#define TCPWM_GRP_CNT_CC1_CC_Pos                0UL
#define TCPWM_GRP_CNT_CC1_CC_Msk                0xFFFFFFFFUL
/* TCPWM_GRP_CNT.CC1_BUFF */
#define TCPWM_GRP_CNT_CC1_BUFF_CC_Pos           0UL
#define TCPWM_GRP_CNT_CC1_BUFF_CC_Msk           0xFFFFFFFFUL
/* TCPWM_GRP_CNT.PERIOD */
#define TCPWM_GRP_CNT_PERIOD_PERIOD_Pos         0UL
#define TCPWM_GRP_CNT_PERIOD_PERIOD_Msk         0xFFFFFFFFUL
/* TCPWM_GRP_CNT.PERIOD_BUFF */
#define TCPWM_GRP_CNT_PERIOD_BUFF_PERIOD_Pos    0UL
#define TCPWM_GRP_CNT_PERIOD_BUFF_PERIOD_Msk    0xFFFFFFFFUL
/* TCPWM_GRP_CNT.LINE_SEL */
#define TCPWM_GRP_CNT_LINE_SEL_OUT_SEL_Pos      0UL
#define TCPWM_GRP_CNT_LINE_SEL_OUT_SEL_Msk      0x7UL
#define TCPWM_GRP_CNT_LINE_SEL_COMPL_OUT_SEL_Pos 4UL
#define TCPWM_GRP_CNT_LINE_SEL_COMPL_OUT_SEL_Msk 0x70UL
/* TCPWM_GRP_CNT.LINE_SEL_BUFF */
#define TCPWM_GRP_CNT_LINE_SEL_BUFF_OUT_SEL_Pos 0UL
#define TCPWM_GRP_CNT_LINE_SEL_BUFF_OUT_SEL_Msk 0x7UL
#define TCPWM_GRP_CNT_LINE_SEL_BUFF_COMPL_OUT_SEL_Pos 4UL
#define TCPWM_GRP_CNT_LINE_SEL_BUFF_COMPL_OUT_SEL_Msk 0x70UL
/* TCPWM_GRP_CNT.DT */
#define TCPWM_GRP_CNT_DT_DT_LINE_OUT_L_Pos      0UL
#define TCPWM_GRP_CNT_DT_DT_LINE_OUT_L_Msk      0xFFUL
#define TCPWM_GRP_CNT_DT_DT_LINE_OUT_H_Pos      8UL
#define TCPWM_GRP_CNT_DT_DT_LINE_OUT_H_Msk      0xFF00UL
#define TCPWM_GRP_CNT_DT_DT_LINE_COMPL_OUT_Pos  16UL
#define TCPWM_GRP_CNT_DT_DT_LINE_COMPL_OUT_Msk  0xFFFF0000UL
/* TCPWM_GRP_CNT.TR_CMD */
#define TCPWM_GRP_CNT_TR_CMD_CAPTURE0_Pos       0UL
#define TCPWM_GRP_CNT_TR_CMD_CAPTURE0_Msk       0x1UL
#define TCPWM_GRP_CNT_TR_CMD_RELOAD_Pos         2UL
#define TCPWM_GRP_CNT_TR_CMD_RELOAD_Msk         0x4UL
#define TCPWM_GRP_CNT_TR_CMD_STOP_Pos           3UL
#define TCPWM_GRP_CNT_TR_CMD_STOP_Msk           0x8UL
#define TCPWM_GRP_CNT_TR_CMD_START_Pos          4UL
#define TCPWM_GRP_CNT_TR_CMD_START_Msk          0x10UL
#define TCPWM_GRP_CNT_TR_CMD_CAPTURE1_Pos       5UL
#define TCPWM_GRP_CNT_TR_CMD_CAPTURE1_Msk       0x20UL
/* TCPWM_GRP_CNT.TR_IN_SEL0 */
#define TCPWM_GRP_CNT_TR_IN_SEL0_CAPTURE0_SEL_Pos 0UL
#define TCPWM_GRP_CNT_TR_IN_SEL0_CAPTURE0_SEL_Msk 0xFFUL
#define TCPWM_GRP_CNT_TR_IN_SEL0_COUNT_SEL_Pos  8UL
#define TCPWM_GRP_CNT_TR_IN_SEL0_COUNT_SEL_Msk  0xFF00UL
#define TCPWM_GRP_CNT_TR_IN_SEL0_RELOAD_SEL_Pos 16UL
#define TCPWM_GRP_CNT_TR_IN_SEL0_RELOAD_SEL_Msk 0xFF0000UL
#define TCPWM_GRP_CNT_TR_IN_SEL0_STOP_SEL_Pos   24UL
#define TCPWM_GRP_CNT_TR_IN_SEL0_STOP_SEL_Msk   0xFF000000UL
/* TCPWM_GRP_CNT.TR_IN_SEL1 */
#define TCPWM_GRP_CNT_TR_IN_SEL1_START_SEL_Pos  0UL
#define TCPWM_GRP_CNT_TR_IN_SEL1_START_SEL_Msk  0xFFUL
#define TCPWM_GRP_CNT_TR_IN_SEL1_CAPTURE1_SEL_Pos 8UL
#define TCPWM_GRP_CNT_TR_IN_SEL1_CAPTURE1_SEL_Msk 0xFF00UL
/* TCPWM_GRP_CNT.TR_IN_EDGE_SEL */
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Pos 0UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Msk 0x3UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_COUNT_EDGE_Pos 2UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_COUNT_EDGE_Msk 0xCUL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_RELOAD_EDGE_Pos 4UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_RELOAD_EDGE_Msk 0x30UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_STOP_EDGE_Pos 6UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_STOP_EDGE_Msk 0xC0UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_START_EDGE_Pos 8UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_START_EDGE_Msk 0x300UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Pos 10UL
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Msk 0xC00UL
/* TCPWM_GRP_CNT.TR_PWM_CTRL */
#define TCPWM_GRP_CNT_TR_PWM_CTRL_CC0_MATCH_MODE_Pos 0UL
#define TCPWM_GRP_CNT_TR_PWM_CTRL_CC0_MATCH_MODE_Msk 0x3UL
#define TCPWM_GRP_CNT_TR_PWM_CTRL_OVERFLOW_MODE_Pos 2UL
#define TCPWM_GRP_CNT_TR_PWM_CTRL_OVERFLOW_MODE_Msk 0xCUL
#define TCPWM_GRP_CNT_TR_PWM_CTRL_UNDERFLOW_MODE_Pos 4UL
#define TCPWM_GRP_CNT_TR_PWM_CTRL_UNDERFLOW_MODE_Msk 0x30UL
#define TCPWM_GRP_CNT_TR_PWM_CTRL_CC1_MATCH_MODE_Pos 6UL
#define TCPWM_GRP_CNT_TR_PWM_CTRL_CC1_MATCH_MODE_Msk 0xC0UL
/* TCPWM_GRP_CNT.TR_OUT_SEL */
#define TCPWM_GRP_CNT_TR_OUT_SEL_OUT0_Pos       0UL
#define TCPWM_GRP_CNT_TR_OUT_SEL_OUT0_Msk       0x7UL
#define TCPWM_GRP_CNT_TR_OUT_SEL_OUT1_Pos       4UL
#define TCPWM_GRP_CNT_TR_OUT_SEL_OUT1_Msk       0x70UL
/* TCPWM_GRP_CNT.INTR */
#define TCPWM_GRP_CNT_INTR_TC_Pos               0UL
#define TCPWM_GRP_CNT_INTR_TC_Msk               0x1UL
#define TCPWM_GRP_CNT_INTR_CC0_MATCH_Pos        1UL
#define TCPWM_GRP_CNT_INTR_CC0_MATCH_Msk        0x2UL
#define TCPWM_GRP_CNT_INTR_CC1_MATCH_Pos        2UL
#define TCPWM_GRP_CNT_INTR_CC1_MATCH_Msk        0x4UL
/* TCPWM_GRP_CNT.INTR_SET */
#define TCPWM_GRP_CNT_INTR_SET_TC_Pos           0UL
#define TCPWM_GRP_CNT_INTR_SET_TC_Msk           0x1UL
#define TCPWM_GRP_CNT_INTR_SET_CC0_MATCH_Pos    1UL
#define TCPWM_GRP_CNT_INTR_SET_CC0_MATCH_Msk    0x2UL
#define TCPWM_GRP_CNT_INTR_SET_CC1_MATCH_Pos    2UL
#define TCPWM_GRP_CNT_INTR_SET_CC1_MATCH_Msk    0x4UL
/* TCPWM_GRP_CNT.INTR_MASK */
#define TCPWM_GRP_CNT_INTR_MASK_TC_Pos          0UL
#define TCPWM_GRP_CNT_INTR_MASK_TC_Msk          0x1UL
#define TCPWM_GRP_CNT_INTR_MASK_CC0_MATCH_Pos   1UL
#define TCPWM_GRP_CNT_INTR_MASK_CC0_MATCH_Msk   0x2UL
#define TCPWM_GRP_CNT_INTR_MASK_CC1_MATCH_Pos   2UL
#define TCPWM_GRP_CNT_INTR_MASK_CC1_MATCH_Msk   0x4UL
/* TCPWM_GRP_CNT.INTR_MASKED */
#define TCPWM_GRP_CNT_INTR_MASKED_TC_Pos        0UL
#define TCPWM_GRP_CNT_INTR_MASKED_TC_Msk        0x1UL
#define TCPWM_GRP_CNT_INTR_MASKED_CC0_MATCH_Pos 1UL
#define TCPWM_GRP_CNT_INTR_MASKED_CC0_MATCH_Msk 0x2UL
#define TCPWM_GRP_CNT_INTR_MASKED_CC1_MATCH_Pos 2UL
#define TCPWM_GRP_CNT_INTR_MASKED_CC1_MATCH_Msk 0x4UL


#endif /* _CYIP_TCPWM_V2_H_ */


/* [] END OF FILE */
