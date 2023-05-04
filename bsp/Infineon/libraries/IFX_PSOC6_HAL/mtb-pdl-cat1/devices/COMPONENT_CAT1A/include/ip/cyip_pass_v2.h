/***************************************************************************//**
* \file cyip_pass_v2.h
*
* \brief
* PASS IP definitions
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

#ifndef _CYIP_PASS_V2_H_
#define _CYIP_PASS_V2_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     PASS
*******************************************************************************/

#define PASS_TIMER_V2_SECTION_SIZE              0x00000100UL
#define PASS_LPOSC_V2_SECTION_SIZE              0x00000100UL
#define PASS_FIFO_V2_SECTION_SIZE               0x00000100UL
#define PASS_AREFV2_V2_SECTION_SIZE             0x00000100UL
#define PASS_V2_SECTION_SIZE                    0x00010000UL

/**
  * \brief Programmable Analog Subsystem (PASS_TIMER)
  */
typedef struct {
  __IOM uint32_t CTRL;                          /*!< 0x00000000 Timer trigger control register */
  __IOM uint32_t CONFIG;                        /*!< 0x00000004 Timer trigger configuration register */
  __IOM uint32_t PERIOD;                        /*!< 0x00000008 Timer trigger period register */
   __IM uint32_t RESERVED[61];
} PASS_TIMER_V2_Type;                           /*!< Size = 256 (0x100) */

/**
  * \brief LPOSC configuration (PASS_LPOSC)
  */
typedef struct {
  __IOM uint32_t CTRL;                          /*!< 0x00000000 Low Power Oscillator control */
  __IOM uint32_t CONFIG;                        /*!< 0x00000004 Low Power Oscillator configuration register */
  __IOM uint32_t ADFT;                          /*!< 0x00000008 Retention, Hidden */
   __IM uint32_t RESERVED[61];
} PASS_LPOSC_V2_Type;                           /*!< Size = 256 (0x100) */

/**
  * \brief FIFO configuration (PASS_FIFO)
  */
typedef struct {
  __IOM uint32_t CTRL;                          /*!< 0x00000000 FIFO control register */
  __IOM uint32_t CONFIG;                        /*!< 0x00000004 FIFO configuration register */
  __IOM uint32_t CLEAR;                         /*!< 0x00000008 FIFO clear register */
  __IOM uint32_t LEVEL;                         /*!< 0x0000000C FIFO level register */
   __IM uint32_t USED;                          /*!< 0x00000010 FIFO used register */
   __IM uint32_t STATUS;                        /*!< 0x00000014 FIFO status register */
   __IM uint32_t RD_DATA;                       /*!< 0x00000018 FIFO read data register */
   __IM uint32_t RESERVED;
  __IOM uint32_t INTR;                          /*!< 0x00000020 Interrupt register */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000024 Interrupt set register */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000028 Interrupt mask register */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000002C Interrupt masked register */
   __IM uint32_t RESERVED1[52];
} PASS_FIFO_V2_Type;                            /*!< Size = 256 (0x100) */

/**
  * \brief AREF configuration (PASS_AREFV2)
  */
typedef struct {
  __IOM uint32_t AREF_CTRL;                     /*!< 0x00000000 global AREF control */
   __IM uint32_t RESERVED[63];
} PASS_AREFV2_V2_Type;                          /*!< Size = 256 (0x100) */

/**
  * \brief PASS top-level MMIO (AREF, LPOSC, FIFO, INTR, Trigger) (PASS)
  */
typedef struct {
   __IM uint32_t INTR_CAUSE;                    /*!< 0x00000000 Interrupt cause register */
   __IM uint32_t RESERVED[3];
  __IOM uint32_t DPSLP_CLOCK_SEL;               /*!< 0x00000010 Deepsleep clock select */
  __IOM uint32_t ANA_PWR_CFG;                   /*!< 0x00000014 Analog power configuration */
   __IM uint32_t RESERVED1[2];
  __IOM uint32_t CTBM_CLOCK_SEL[2];             /*!< 0x00000020 Clock select for CTBm */
   __IM uint32_t RESERVED2[2];
  __IOM uint32_t SAR_DPSLP_CTRL[2];             /*!< 0x00000030 Deepsleep control for SARv3 */
   __IM uint32_t RESERVED3[2];
  __IOM uint32_t SAR_CLOCK_SEL[2];              /*!< 0x00000040 Clock select for SARv3 */
   __IM uint32_t RESERVED4[2];
   __IM uint32_t SAR_TR_SCAN_CNT_STATUS[2];     /*!< 0x00000050 SAR trigger scan control status */
   __IM uint32_t RESERVED5[2];
  __IOM uint32_t SAR_TR_SCAN_CNT;               /*!< 0x00000060 SAR trigger scan control */
  __IOM uint32_t SAR_OVR_CTRL;                  /*!< 0x00000064 SAR HW trigger override */
  __IOM uint32_t SAR_SIMULT_CTRL;               /*!< 0x00000068 SAR simultaneous trigger control */
  __IOM uint32_t SAR_SIMULT_FW_START_CTRL;      /*!< 0x0000006C SAR simultaneous start control */
  __IOM uint32_t SAR_TR_OUT_CTRL;               /*!< 0x00000070 SAR trigger out control */
   __IM uint32_t RESERVED6[35];
        PASS_TIMER_V2_Type TIMER;               /*!< 0x00000100 Programmable Analog Subsystem */
        PASS_LPOSC_V2_Type LPOSC;               /*!< 0x00000200 LPOSC configuration */
        PASS_FIFO_V2_Type FIFO[2];              /*!< 0x00000300 FIFO configuration */
   __IM uint32_t RESERVED7[576];
        PASS_AREFV2_V2_Type AREFV2;             /*!< 0x00000E00 AREF configuration */
  __IOM uint32_t VREF_TRIM0;                    /*!< 0x00000F00 VREF Trim bits */
  __IOM uint32_t VREF_TRIM1;                    /*!< 0x00000F04 VREF Trim bits */
  __IOM uint32_t VREF_TRIM2;                    /*!< 0x00000F08 VREF Trim bits */
  __IOM uint32_t VREF_TRIM3;                    /*!< 0x00000F0C VREF Trim bits */
  __IOM uint32_t IZTAT_TRIM0;                   /*!< 0x00000F10 VREF Trim bits */
  __IOM uint32_t IZTAT_TRIM1;                   /*!< 0x00000F14 IZTAT Trim bits */
  __IOM uint32_t IPTAT_TRIM0;                   /*!< 0x00000F18 IPTAT Trim bits */
  __IOM uint32_t ICTAT_TRIM0;                   /*!< 0x00000F1C ICTAT Trim bits */
} PASS_V2_Type;                                 /*!< Size = 3872 (0xF20) */


/* PASS_TIMER.CTRL */
#define PASS_TIMER_V2_CTRL_ENABLED_Pos          31UL
#define PASS_TIMER_V2_CTRL_ENABLED_Msk          0x80000000UL
/* PASS_TIMER.CONFIG */
#define PASS_TIMER_V2_CONFIG_CLOCK_SEL_Pos      0UL
#define PASS_TIMER_V2_CONFIG_CLOCK_SEL_Msk      0x3UL
/* PASS_TIMER.PERIOD */
#define PASS_TIMER_V2_PERIOD_PER_VAL_Pos        0UL
#define PASS_TIMER_V2_PERIOD_PER_VAL_Msk        0xFFFFUL


/* PASS_LPOSC.CTRL */
#define PASS_LPOSC_V2_CTRL_ENABLED_Pos          31UL
#define PASS_LPOSC_V2_CTRL_ENABLED_Msk          0x80000000UL
/* PASS_LPOSC.CONFIG */
#define PASS_LPOSC_V2_CONFIG_DEEPSLEEP_MODE_Pos 0UL
#define PASS_LPOSC_V2_CONFIG_DEEPSLEEP_MODE_Msk 0x1UL
/* PASS_LPOSC.ADFT */
#define PASS_LPOSC_V2_ADFT_ADFT_SEL_Pos         0UL
#define PASS_LPOSC_V2_ADFT_ADFT_SEL_Msk         0x3UL


/* PASS_FIFO.CTRL */
#define PASS_FIFO_V2_CTRL_ENABLED_Pos           31UL
#define PASS_FIFO_V2_CTRL_ENABLED_Msk           0x80000000UL
/* PASS_FIFO.CONFIG */
#define PASS_FIFO_V2_CONFIG_CHAN_ID_EN_Pos      0UL
#define PASS_FIFO_V2_CONFIG_CHAN_ID_EN_Msk      0x1UL
#define PASS_FIFO_V2_CONFIG_CHAIN_TO_NXT_Pos    1UL
#define PASS_FIFO_V2_CONFIG_CHAIN_TO_NXT_Msk    0x2UL
#define PASS_FIFO_V2_CONFIG_TR_INTR_CLR_RD_EN_Pos 2UL
#define PASS_FIFO_V2_CONFIG_TR_INTR_CLR_RD_EN_Msk 0x4UL
/* PASS_FIFO.CLEAR */
#define PASS_FIFO_V2_CLEAR_CLEAR_Pos            0UL
#define PASS_FIFO_V2_CLEAR_CLEAR_Msk            0x1UL
/* PASS_FIFO.LEVEL */
#define PASS_FIFO_V2_LEVEL_LEVEL_Pos            0UL
#define PASS_FIFO_V2_LEVEL_LEVEL_Msk            0xFFUL
/* PASS_FIFO.USED */
#define PASS_FIFO_V2_USED_USED_Pos              0UL
#define PASS_FIFO_V2_USED_USED_Msk              0xFFUL
/* PASS_FIFO.STATUS */
#define PASS_FIFO_V2_STATUS_RD_PTR_Pos          0UL
#define PASS_FIFO_V2_STATUS_RD_PTR_Msk          0xFFUL
#define PASS_FIFO_V2_STATUS_WR_PTR_Pos          8UL
#define PASS_FIFO_V2_STATUS_WR_PTR_Msk          0xFF00UL
/* PASS_FIFO.RD_DATA */
#define PASS_FIFO_V2_RD_DATA_RESULT_Pos         0UL
#define PASS_FIFO_V2_RD_DATA_RESULT_Msk         0xFFFFUL
#define PASS_FIFO_V2_RD_DATA_CHAN_ID_Pos        16UL
#define PASS_FIFO_V2_RD_DATA_CHAN_ID_Msk        0xF0000UL
/* PASS_FIFO.INTR */
#define PASS_FIFO_V2_INTR_FIFO_LEVEL_Pos        0UL
#define PASS_FIFO_V2_INTR_FIFO_LEVEL_Msk        0x1UL
#define PASS_FIFO_V2_INTR_FIFO_OVERFLOW_Pos     1UL
#define PASS_FIFO_V2_INTR_FIFO_OVERFLOW_Msk     0x2UL
#define PASS_FIFO_V2_INTR_FIFO_UNDERFLOW_Pos    2UL
#define PASS_FIFO_V2_INTR_FIFO_UNDERFLOW_Msk    0x4UL
/* PASS_FIFO.INTR_SET */
#define PASS_FIFO_V2_INTR_SET_FIFO_LEVEL_Pos    0UL
#define PASS_FIFO_V2_INTR_SET_FIFO_LEVEL_Msk    0x1UL
#define PASS_FIFO_V2_INTR_SET_FIFO_OVERFLOW_Pos 1UL
#define PASS_FIFO_V2_INTR_SET_FIFO_OVERFLOW_Msk 0x2UL
#define PASS_FIFO_V2_INTR_SET_FIFO_UNDERFLOW_Pos 2UL
#define PASS_FIFO_V2_INTR_SET_FIFO_UNDERFLOW_Msk 0x4UL
/* PASS_FIFO.INTR_MASK */
#define PASS_FIFO_V2_INTR_MASK_FIFO_LEVEL_Pos   0UL
#define PASS_FIFO_V2_INTR_MASK_FIFO_LEVEL_Msk   0x1UL
#define PASS_FIFO_V2_INTR_MASK_FIFO_OVERFLOW_Pos 1UL
#define PASS_FIFO_V2_INTR_MASK_FIFO_OVERFLOW_Msk 0x2UL
#define PASS_FIFO_V2_INTR_MASK_FIFO_UNDERFLOW_Pos 2UL
#define PASS_FIFO_V2_INTR_MASK_FIFO_UNDERFLOW_Msk 0x4UL
/* PASS_FIFO.INTR_MASKED */
#define PASS_FIFO_V2_INTR_MASKED_FIFO_LEVEL_Pos 0UL
#define PASS_FIFO_V2_INTR_MASKED_FIFO_LEVEL_Msk 0x1UL
#define PASS_FIFO_V2_INTR_MASKED_FIFO_OVERFLOW_Pos 1UL
#define PASS_FIFO_V2_INTR_MASKED_FIFO_OVERFLOW_Msk 0x2UL
#define PASS_FIFO_V2_INTR_MASKED_FIFO_UNDERFLOW_Pos 2UL
#define PASS_FIFO_V2_INTR_MASKED_FIFO_UNDERFLOW_Msk 0x4UL


/* PASS_AREFV2.AREF_CTRL */
#define PASS_AREFV2_V2_AREF_CTRL_AREF_MODE_Pos  0UL
#define PASS_AREFV2_V2_AREF_CTRL_AREF_MODE_Msk  0x1UL
#define PASS_AREFV2_V2_AREF_CTRL_AREF_BIAS_SCALE_Pos 2UL
#define PASS_AREFV2_V2_AREF_CTRL_AREF_BIAS_SCALE_Msk 0xCUL
#define PASS_AREFV2_V2_AREF_CTRL_AREF_RMB_Pos   4UL
#define PASS_AREFV2_V2_AREF_CTRL_AREF_RMB_Msk   0x70UL
#define PASS_AREFV2_V2_AREF_CTRL_CTB_IPTAT_SCALE_Pos 7UL
#define PASS_AREFV2_V2_AREF_CTRL_CTB_IPTAT_SCALE_Msk 0x80UL
#define PASS_AREFV2_V2_AREF_CTRL_CTB_IPTAT_REDIRECT_Pos 8UL
#define PASS_AREFV2_V2_AREF_CTRL_CTB_IPTAT_REDIRECT_Msk 0xFF00UL
#define PASS_AREFV2_V2_AREF_CTRL_IZTAT_SEL_Pos  16UL
#define PASS_AREFV2_V2_AREF_CTRL_IZTAT_SEL_Msk  0x10000UL
#define PASS_AREFV2_V2_AREF_CTRL_CLOCK_PUMP_PERI_SEL_Pos 19UL
#define PASS_AREFV2_V2_AREF_CTRL_CLOCK_PUMP_PERI_SEL_Msk 0x80000UL
#define PASS_AREFV2_V2_AREF_CTRL_VREF_SEL_Pos   20UL
#define PASS_AREFV2_V2_AREF_CTRL_VREF_SEL_Msk   0x300000UL
#define PASS_AREFV2_V2_AREF_CTRL_DEEPSLEEP_MODE_Pos 28UL
#define PASS_AREFV2_V2_AREF_CTRL_DEEPSLEEP_MODE_Msk 0x30000000UL
#define PASS_AREFV2_V2_AREF_CTRL_DEEPSLEEP_ON_Pos 30UL
#define PASS_AREFV2_V2_AREF_CTRL_DEEPSLEEP_ON_Msk 0x40000000UL
#define PASS_AREFV2_V2_AREF_CTRL_ENABLED_Pos    31UL
#define PASS_AREFV2_V2_AREF_CTRL_ENABLED_Msk    0x80000000UL


/* PASS.INTR_CAUSE */
#define PASS_V2_INTR_CAUSE_CTB0_INT_Pos         0UL
#define PASS_V2_INTR_CAUSE_CTB0_INT_Msk         0x1UL
#define PASS_V2_INTR_CAUSE_CTB1_INT_Pos         1UL
#define PASS_V2_INTR_CAUSE_CTB1_INT_Msk         0x2UL
#define PASS_V2_INTR_CAUSE_CTB2_INT_Pos         2UL
#define PASS_V2_INTR_CAUSE_CTB2_INT_Msk         0x4UL
#define PASS_V2_INTR_CAUSE_CTB3_INT_Pos         3UL
#define PASS_V2_INTR_CAUSE_CTB3_INT_Msk         0x8UL
#define PASS_V2_INTR_CAUSE_CTDAC0_INT_Pos       4UL
#define PASS_V2_INTR_CAUSE_CTDAC0_INT_Msk       0x10UL
#define PASS_V2_INTR_CAUSE_CTDAC1_INT_Pos       5UL
#define PASS_V2_INTR_CAUSE_CTDAC1_INT_Msk       0x20UL
#define PASS_V2_INTR_CAUSE_CTDAC2_INT_Pos       6UL
#define PASS_V2_INTR_CAUSE_CTDAC2_INT_Msk       0x40UL
#define PASS_V2_INTR_CAUSE_CTDAC3_INT_Pos       7UL
#define PASS_V2_INTR_CAUSE_CTDAC3_INT_Msk       0x80UL
#define PASS_V2_INTR_CAUSE_SAR0_INT_Pos         8UL
#define PASS_V2_INTR_CAUSE_SAR0_INT_Msk         0x100UL
#define PASS_V2_INTR_CAUSE_SAR1_INT_Pos         9UL
#define PASS_V2_INTR_CAUSE_SAR1_INT_Msk         0x200UL
#define PASS_V2_INTR_CAUSE_SAR2_INT_Pos         10UL
#define PASS_V2_INTR_CAUSE_SAR2_INT_Msk         0x400UL
#define PASS_V2_INTR_CAUSE_SAR3_INT_Pos         11UL
#define PASS_V2_INTR_CAUSE_SAR3_INT_Msk         0x800UL
#define PASS_V2_INTR_CAUSE_FIFO0_INT_Pos        12UL
#define PASS_V2_INTR_CAUSE_FIFO0_INT_Msk        0x1000UL
#define PASS_V2_INTR_CAUSE_FIFO1_INT_Pos        13UL
#define PASS_V2_INTR_CAUSE_FIFO1_INT_Msk        0x2000UL
#define PASS_V2_INTR_CAUSE_FIFO2_INT_Pos        14UL
#define PASS_V2_INTR_CAUSE_FIFO2_INT_Msk        0x4000UL
#define PASS_V2_INTR_CAUSE_FIFO3_INT_Pos        15UL
#define PASS_V2_INTR_CAUSE_FIFO3_INT_Msk        0x8000UL
/* PASS.DPSLP_CLOCK_SEL */
#define PASS_V2_DPSLP_CLOCK_SEL_DPSLP_CLOCK_SEL_Pos 0UL
#define PASS_V2_DPSLP_CLOCK_SEL_DPSLP_CLOCK_SEL_Msk 0x1UL
#define PASS_V2_DPSLP_CLOCK_SEL_DPSLP_CLOCK_DIV_Pos 4UL
#define PASS_V2_DPSLP_CLOCK_SEL_DPSLP_CLOCK_DIV_Msk 0x70UL
/* PASS.ANA_PWR_CFG */
#define PASS_V2_ANA_PWR_CFG_PWR_UP_DELAY_Pos    0UL
#define PASS_V2_ANA_PWR_CFG_PWR_UP_DELAY_Msk    0xFFUL
#define PASS_V2_ANA_PWR_CFG_DUTY_CYCLE_SAR_ACT_EN_Pos 8UL
#define PASS_V2_ANA_PWR_CFG_DUTY_CYCLE_SAR_ACT_EN_Msk 0xF00UL
/* PASS.CTBM_CLOCK_SEL */
#define PASS_V2_CTBM_CLOCK_SEL_PUMP_CLOCK_SEL_Pos 0UL
#define PASS_V2_CTBM_CLOCK_SEL_PUMP_CLOCK_SEL_Msk 0x1UL
/* PASS.SAR_DPSLP_CTRL */
#define PASS_V2_SAR_DPSLP_CTRL_ENABLED_Pos      31UL
#define PASS_V2_SAR_DPSLP_CTRL_ENABLED_Msk      0x80000000UL
/* PASS.SAR_CLOCK_SEL */
#define PASS_V2_SAR_CLOCK_SEL_CLOCK_SEL_Pos     30UL
#define PASS_V2_SAR_CLOCK_SEL_CLOCK_SEL_Msk     0x40000000UL
/* PASS.SAR_TR_SCAN_CNT_STATUS */
#define PASS_V2_SAR_TR_SCAN_CNT_STATUS_SCAN_CNT_STATUS_Pos 0UL
#define PASS_V2_SAR_TR_SCAN_CNT_STATUS_SCAN_CNT_STATUS_Msk 0xFFUL
/* PASS.SAR_TR_SCAN_CNT */
#define PASS_V2_SAR_TR_SCAN_CNT_SCAN_CNT_Pos    0UL
#define PASS_V2_SAR_TR_SCAN_CNT_SCAN_CNT_Msk    0xFFUL
/* PASS.SAR_OVR_CTRL */
#define PASS_V2_SAR_OVR_CTRL_HW_TR_TIMER_SEL_Pos 0UL
#define PASS_V2_SAR_OVR_CTRL_HW_TR_TIMER_SEL_Msk 0xFUL
#define PASS_V2_SAR_OVR_CTRL_TR_SCAN_CNT_SEL_Pos 4UL
#define PASS_V2_SAR_OVR_CTRL_TR_SCAN_CNT_SEL_Msk 0xF0UL
#define PASS_V2_SAR_OVR_CTRL_EOS_INTR_SCAN_CNT_SEL_Pos 8UL
#define PASS_V2_SAR_OVR_CTRL_EOS_INTR_SCAN_CNT_SEL_Msk 0xF00UL
/* PASS.SAR_SIMULT_CTRL */
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_EN_Pos 0UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_EN_Msk 0xFUL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_SRC_Pos 4UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_SRC_Msk 0x30UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_TIMER_SEL_Pos 8UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_TIMER_SEL_Msk 0x100UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_LEVEL_Pos 18UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_LEVEL_Msk 0x40000UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_SYNC_TR_Pos 19UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_SYNC_TR_Msk 0x80000UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_TR_SCAN_CNT_SEL_Pos 20UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_TR_SCAN_CNT_SEL_Msk 0x100000UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_EOS_INTR_SCAN_CNT_SEL_Pos 21UL
#define PASS_V2_SAR_SIMULT_CTRL_SIMULT_EOS_INTR_SCAN_CNT_SEL_Msk 0x200000UL
/* PASS.SAR_SIMULT_FW_START_CTRL */
#define PASS_V2_SAR_SIMULT_FW_START_CTRL_FW_TRIGGER_Pos 0UL
#define PASS_V2_SAR_SIMULT_FW_START_CTRL_FW_TRIGGER_Msk 0xFUL
#define PASS_V2_SAR_SIMULT_FW_START_CTRL_CONTINUOUS_Pos 16UL
#define PASS_V2_SAR_SIMULT_FW_START_CTRL_CONTINUOUS_Msk 0xF0000UL
/* PASS.SAR_TR_OUT_CTRL */
#define PASS_V2_SAR_TR_OUT_CTRL_SAR0_TR_OUT_SEL_Pos 0UL
#define PASS_V2_SAR_TR_OUT_CTRL_SAR0_TR_OUT_SEL_Msk 0x1UL
#define PASS_V2_SAR_TR_OUT_CTRL_SAR1_TR_OUT_SEL_Pos 1UL
#define PASS_V2_SAR_TR_OUT_CTRL_SAR1_TR_OUT_SEL_Msk 0x2UL
#define PASS_V2_SAR_TR_OUT_CTRL_SAR2_TR_OUT_SEL_Pos 2UL
#define PASS_V2_SAR_TR_OUT_CTRL_SAR2_TR_OUT_SEL_Msk 0x4UL
#define PASS_V2_SAR_TR_OUT_CTRL_SAR3_TR_OUT_SEL_Pos 3UL
#define PASS_V2_SAR_TR_OUT_CTRL_SAR3_TR_OUT_SEL_Msk 0x8UL
/* PASS.VREF_TRIM0 */
#define PASS_V2_VREF_TRIM0_VREF_ABS_TRIM_Pos    0UL
#define PASS_V2_VREF_TRIM0_VREF_ABS_TRIM_Msk    0xFFUL
/* PASS.VREF_TRIM1 */
#define PASS_V2_VREF_TRIM1_VREF_TEMPCO_TRIM_Pos 0UL
#define PASS_V2_VREF_TRIM1_VREF_TEMPCO_TRIM_Msk 0xFFUL
/* PASS.VREF_TRIM2 */
#define PASS_V2_VREF_TRIM2_VREF_CURV_TRIM_Pos   0UL
#define PASS_V2_VREF_TRIM2_VREF_CURV_TRIM_Msk   0xFFUL
/* PASS.VREF_TRIM3 */
#define PASS_V2_VREF_TRIM3_VREF_ATTEN_TRIM_Pos  0UL
#define PASS_V2_VREF_TRIM3_VREF_ATTEN_TRIM_Msk  0xFUL
/* PASS.IZTAT_TRIM0 */
#define PASS_V2_IZTAT_TRIM0_IZTAT_ABS_TRIM_Pos  0UL
#define PASS_V2_IZTAT_TRIM0_IZTAT_ABS_TRIM_Msk  0xFFUL
/* PASS.IZTAT_TRIM1 */
#define PASS_V2_IZTAT_TRIM1_IZTAT_TC_TRIM_Pos   0UL
#define PASS_V2_IZTAT_TRIM1_IZTAT_TC_TRIM_Msk   0xFFUL
/* PASS.IPTAT_TRIM0 */
#define PASS_V2_IPTAT_TRIM0_IPTAT_CORE_TRIM_Pos 0UL
#define PASS_V2_IPTAT_TRIM0_IPTAT_CORE_TRIM_Msk 0xFUL
#define PASS_V2_IPTAT_TRIM0_IPTAT_CTBM_TRIM_Pos 4UL
#define PASS_V2_IPTAT_TRIM0_IPTAT_CTBM_TRIM_Msk 0xF0UL
/* PASS.ICTAT_TRIM0 */
#define PASS_V2_ICTAT_TRIM0_ICTAT_TRIM_Pos      0UL
#define PASS_V2_ICTAT_TRIM0_ICTAT_TRIM_Msk      0xFUL


#endif /* _CYIP_PASS_V2_H_ */


/* [] END OF FILE */
