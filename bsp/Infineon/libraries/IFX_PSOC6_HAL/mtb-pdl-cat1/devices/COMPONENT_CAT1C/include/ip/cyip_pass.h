/***************************************************************************//**
* \file cyip_pass.h
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

#ifndef _CYIP_PASS_H_
#define _CYIP_PASS_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     PASS
*******************************************************************************/

#define PASS_SAR_CH_SECTION_SIZE                0x00000040UL
#define PASS_SAR_SECTION_SIZE                   0x00001000UL
#define PASS_EPASS_MMIO_SECTION_SIZE            0x00001000UL
#define PASS_SECTION_SIZE                       0x00100000UL

/**
  * \brief Channel structure (PASS_SAR_CH)
  */
typedef struct {
  __IOM uint32_t TR_CTL;                        /*!< 0x00000000 Trigger control. */
  __IOM uint32_t SAMPLE_CTL;                    /*!< 0x00000004 Sample control. */
  __IOM uint32_t POST_CTL;                      /*!< 0x00000008 Post processing control */
  __IOM uint32_t RANGE_CTL;                     /*!< 0x0000000C Range thresholds */
  __IOM uint32_t INTR;                          /*!< 0x00000010 Interrupt request register. */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000014 Interrupt set request register */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000018 Interrupt mask register. */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000001C Interrupt masked request register */
   __IM uint32_t WORK;                          /*!< 0x00000020 Working data register */
   __IM uint32_t RESULT;                        /*!< 0x00000024 Result data register */
   __IM uint32_t GRP_STAT;                      /*!< 0x00000028 Group status register */
   __IM uint32_t RESERVED[3];
  __IOM uint32_t ENABLE;                        /*!< 0x00000038 Enable register */
  __IOM uint32_t TR_CMD;                        /*!< 0x0000003C Software triggers */
} PASS_SAR_CH_Type;                             /*!< Size = 64 (0x40) */

/**
  * \brief SAR ADC with Sequencer for S40E (PASS_SAR)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Analog control register. */
  __IOM uint32_t DIAG_CTL;                      /*!< 0x00000004 Diagnostic Reference control register. */
   __IM uint32_t RESERVED[2];
  __IOM uint32_t PRECOND_CTL;                   /*!< 0x00000010 Preconditioning control register. */
   __IM uint32_t RESERVED1[27];
  __IOM uint32_t ANA_CAL;                       /*!< 0x00000080 Current analog calibration values */
  __IOM uint32_t DIG_CAL;                       /*!< 0x00000084 Current digital calibration values */
   __IM uint32_t RESERVED2[2];
  __IOM uint32_t ANA_CAL_ALT;                   /*!< 0x00000090 Alternate analog calibration values */
  __IOM uint32_t DIG_CAL_ALT;                   /*!< 0x00000094 Alternate digital calibration values */
  __IOM uint32_t CAL_UPD_CMD;                   /*!< 0x00000098 Calibration update command */
   __IM uint32_t RESERVED3[25];
   __IM uint32_t TR_PEND;                       /*!< 0x00000100 Trigger pending status */
   __IM uint32_t RESERVED4[31];
   __IM uint32_t WORK_VALID;                    /*!< 0x00000180 Channel working data register 'valid' bits */
   __IM uint32_t WORK_RANGE;                    /*!< 0x00000184 Range detected */
   __IM uint32_t WORK_RANGE_HI;                 /*!< 0x00000188 Range detect above Hi flag */
   __IM uint32_t WORK_PULSE;                    /*!< 0x0000018C Pulse detected */
   __IM uint32_t RESERVED5[4];
   __IM uint32_t RESULT_VALID;                  /*!< 0x000001A0 Channel result data register 'valid' bits */
   __IM uint32_t RESULT_RANGE_HI;               /*!< 0x000001A4 Channel Range above Hi flags */
   __IM uint32_t RESERVED6[22];
   __IM uint32_t STATUS;                        /*!< 0x00000200 Current status of internal SAR registers (mostly for debug) */
   __IM uint32_t AVG_STAT;                      /*!< 0x00000204 Current averaging status (for debug) */
   __IM uint32_t RESERVED7[382];
        PASS_SAR_CH_Type CH[32];                /*!< 0x00000800 Channel structure */
} PASS_SAR_Type;                                /*!< Size = 4096 (0x1000) */

/**
  * \brief PASS top-level MMIO (Generic Triggers) (PASS_EPASS_MMIO)
  */
typedef struct {
  __IOM uint32_t PASS_CTL;                      /*!< 0x00000000 PASS control register */
   __IM uint32_t RESERVED[7];
  __IOM uint32_t SAR_TR_IN_SEL[4];              /*!< 0x00000020 per SAR generic input trigger select */
   __IM uint32_t RESERVED1[4];
  __IOM uint32_t SAR_TR_OUT_SEL[4];             /*!< 0x00000040 per SAR generic output trigger select */
   __IM uint32_t RESERVED2[12];
  __IOM uint32_t TEST_CTL;                      /*!< 0x00000080 Test control bits */
   __IM uint32_t RESERVED3[991];
} PASS_EPASS_MMIO_Type;                         /*!< Size = 4096 (0x1000) */

/**
  * \brief Programmable Analog Subsystem for S40E (PASS)
  */
typedef struct {
        PASS_SAR_Type SAR[4];                   /*!< 0x00000000 SAR ADC with Sequencer for S40E */
   __IM uint32_t RESERVED[241664];
        PASS_EPASS_MMIO_Type EPASS_MMIO;        /*!< 0x000F0000 PASS top-level MMIO (Generic Triggers) */
} PASS_Type;                                    /*!< Size = 987136 (0xF1000) */


/* PASS_SAR_CH.TR_CTL */
#define PASS_SAR_CH_TR_CTL_SEL_Pos              0UL
#define PASS_SAR_CH_TR_CTL_SEL_Msk              0x7UL
#define PASS_SAR_CH_TR_CTL_PRIO_Pos             4UL
#define PASS_SAR_CH_TR_CTL_PRIO_Msk             0x70UL
#define PASS_SAR_CH_TR_CTL_PREEMPT_TYPE_Pos     8UL
#define PASS_SAR_CH_TR_CTL_PREEMPT_TYPE_Msk     0x300UL
#define PASS_SAR_CH_TR_CTL_GROUP_END_Pos        11UL
#define PASS_SAR_CH_TR_CTL_GROUP_END_Msk        0x800UL
#define PASS_SAR_CH_TR_CTL_DONE_LEVEL_Pos       31UL
#define PASS_SAR_CH_TR_CTL_DONE_LEVEL_Msk       0x80000000UL
/* PASS_SAR_CH.SAMPLE_CTL */
#define PASS_SAR_CH_SAMPLE_CTL_PIN_ADDR_Pos     0UL
#define PASS_SAR_CH_SAMPLE_CTL_PIN_ADDR_Msk     0x3FUL
#define PASS_SAR_CH_SAMPLE_CTL_PORT_ADDR_Pos    6UL
#define PASS_SAR_CH_SAMPLE_CTL_PORT_ADDR_Msk    0xC0UL
#define PASS_SAR_CH_SAMPLE_CTL_EXT_MUX_SEL_Pos  8UL
#define PASS_SAR_CH_SAMPLE_CTL_EXT_MUX_SEL_Msk  0x700UL
#define PASS_SAR_CH_SAMPLE_CTL_EXT_MUX_EN_Pos   11UL
#define PASS_SAR_CH_SAMPLE_CTL_EXT_MUX_EN_Msk   0x800UL
#define PASS_SAR_CH_SAMPLE_CTL_PRECOND_MODE_Pos 12UL
#define PASS_SAR_CH_SAMPLE_CTL_PRECOND_MODE_Msk 0x3000UL
#define PASS_SAR_CH_SAMPLE_CTL_OVERLAP_DIAG_Pos 14UL
#define PASS_SAR_CH_SAMPLE_CTL_OVERLAP_DIAG_Msk 0xC000UL
#define PASS_SAR_CH_SAMPLE_CTL_SAMPLE_TIME_Pos  16UL
#define PASS_SAR_CH_SAMPLE_CTL_SAMPLE_TIME_Msk  0xFFF0000UL
#define PASS_SAR_CH_SAMPLE_CTL_ALT_CAL_Pos      31UL
#define PASS_SAR_CH_SAMPLE_CTL_ALT_CAL_Msk      0x80000000UL
/* PASS_SAR_CH.POST_CTL */
#define PASS_SAR_CH_POST_CTL_POST_PROC_Pos      0UL
#define PASS_SAR_CH_POST_CTL_POST_PROC_Msk      0x7UL
#define PASS_SAR_CH_POST_CTL_LEFT_ALIGN_Pos     6UL
#define PASS_SAR_CH_POST_CTL_LEFT_ALIGN_Msk     0x40UL
#define PASS_SAR_CH_POST_CTL_SIGN_EXT_Pos       7UL
#define PASS_SAR_CH_POST_CTL_SIGN_EXT_Msk       0x80UL
#define PASS_SAR_CH_POST_CTL_AVG_CNT_Pos        8UL
#define PASS_SAR_CH_POST_CTL_AVG_CNT_Msk        0xFF00UL
#define PASS_SAR_CH_POST_CTL_SHIFT_R_Pos        16UL
#define PASS_SAR_CH_POST_CTL_SHIFT_R_Msk        0x1F0000UL
#define PASS_SAR_CH_POST_CTL_RANGE_MODE_Pos     22UL
#define PASS_SAR_CH_POST_CTL_RANGE_MODE_Msk     0xC00000UL
#define PASS_SAR_CH_POST_CTL_TR_DONE_GRP_VIO_Pos 25UL
#define PASS_SAR_CH_POST_CTL_TR_DONE_GRP_VIO_Msk 0x2000000UL
/* PASS_SAR_CH.RANGE_CTL */
#define PASS_SAR_CH_RANGE_CTL_RANGE_LO_Pos      0UL
#define PASS_SAR_CH_RANGE_CTL_RANGE_LO_Msk      0xFFFFUL
#define PASS_SAR_CH_RANGE_CTL_RANGE_HI_Pos      16UL
#define PASS_SAR_CH_RANGE_CTL_RANGE_HI_Msk      0xFFFF0000UL
/* PASS_SAR_CH.INTR */
#define PASS_SAR_CH_INTR_GRP_DONE_Pos           0UL
#define PASS_SAR_CH_INTR_GRP_DONE_Msk           0x1UL
#define PASS_SAR_CH_INTR_GRP_CANCELLED_Pos      1UL
#define PASS_SAR_CH_INTR_GRP_CANCELLED_Msk      0x2UL
#define PASS_SAR_CH_INTR_GRP_OVERFLOW_Pos       2UL
#define PASS_SAR_CH_INTR_GRP_OVERFLOW_Msk       0x4UL
#define PASS_SAR_CH_INTR_CH_RANGE_Pos           8UL
#define PASS_SAR_CH_INTR_CH_RANGE_Msk           0x100UL
#define PASS_SAR_CH_INTR_CH_PULSE_Pos           9UL
#define PASS_SAR_CH_INTR_CH_PULSE_Msk           0x200UL
#define PASS_SAR_CH_INTR_CH_OVERFLOW_Pos        10UL
#define PASS_SAR_CH_INTR_CH_OVERFLOW_Msk        0x400UL
/* PASS_SAR_CH.INTR_SET */
#define PASS_SAR_CH_INTR_SET_GRP_DONE_SET_Pos   0UL
#define PASS_SAR_CH_INTR_SET_GRP_DONE_SET_Msk   0x1UL
#define PASS_SAR_CH_INTR_SET_GRP_CANCELLED_SET_Pos 1UL
#define PASS_SAR_CH_INTR_SET_GRP_CANCELLED_SET_Msk 0x2UL
#define PASS_SAR_CH_INTR_SET_GRP_OVERFLOW_SET_Pos 2UL
#define PASS_SAR_CH_INTR_SET_GRP_OVERFLOW_SET_Msk 0x4UL
#define PASS_SAR_CH_INTR_SET_CH_RANGE_SET_Pos   8UL
#define PASS_SAR_CH_INTR_SET_CH_RANGE_SET_Msk   0x100UL
#define PASS_SAR_CH_INTR_SET_CH_PULSE_SET_Pos   9UL
#define PASS_SAR_CH_INTR_SET_CH_PULSE_SET_Msk   0x200UL
#define PASS_SAR_CH_INTR_SET_CH_OVERFLOW_SET_Pos 10UL
#define PASS_SAR_CH_INTR_SET_CH_OVERFLOW_SET_Msk 0x400UL
/* PASS_SAR_CH.INTR_MASK */
#define PASS_SAR_CH_INTR_MASK_GRP_DONE_MASK_Pos 0UL
#define PASS_SAR_CH_INTR_MASK_GRP_DONE_MASK_Msk 0x1UL
#define PASS_SAR_CH_INTR_MASK_GRP_CANCELLED_MASK_Pos 1UL
#define PASS_SAR_CH_INTR_MASK_GRP_CANCELLED_MASK_Msk 0x2UL
#define PASS_SAR_CH_INTR_MASK_GRP_OVERFLOW_MASK_Pos 2UL
#define PASS_SAR_CH_INTR_MASK_GRP_OVERFLOW_MASK_Msk 0x4UL
#define PASS_SAR_CH_INTR_MASK_CH_RANGE_MASK_Pos 8UL
#define PASS_SAR_CH_INTR_MASK_CH_RANGE_MASK_Msk 0x100UL
#define PASS_SAR_CH_INTR_MASK_CH_PULSE_MASK_Pos 9UL
#define PASS_SAR_CH_INTR_MASK_CH_PULSE_MASK_Msk 0x200UL
#define PASS_SAR_CH_INTR_MASK_CH_OVERFLOW_MASK_Pos 10UL
#define PASS_SAR_CH_INTR_MASK_CH_OVERFLOW_MASK_Msk 0x400UL
/* PASS_SAR_CH.INTR_MASKED */
#define PASS_SAR_CH_INTR_MASKED_GRP_DONE_MASKED_Pos 0UL
#define PASS_SAR_CH_INTR_MASKED_GRP_DONE_MASKED_Msk 0x1UL
#define PASS_SAR_CH_INTR_MASKED_GRP_CANCELLED_MASKED_Pos 1UL
#define PASS_SAR_CH_INTR_MASKED_GRP_CANCELLED_MASKED_Msk 0x2UL
#define PASS_SAR_CH_INTR_MASKED_GRP_OVERFLOW_MASKED_Pos 2UL
#define PASS_SAR_CH_INTR_MASKED_GRP_OVERFLOW_MASKED_Msk 0x4UL
#define PASS_SAR_CH_INTR_MASKED_CH_RANGE_MASKED_Pos 8UL
#define PASS_SAR_CH_INTR_MASKED_CH_RANGE_MASKED_Msk 0x100UL
#define PASS_SAR_CH_INTR_MASKED_CH_PULSE_MASKED_Pos 9UL
#define PASS_SAR_CH_INTR_MASKED_CH_PULSE_MASKED_Msk 0x200UL
#define PASS_SAR_CH_INTR_MASKED_CH_OVERFLOW_MASKED_Pos 10UL
#define PASS_SAR_CH_INTR_MASKED_CH_OVERFLOW_MASKED_Msk 0x400UL
/* PASS_SAR_CH.WORK */
#define PASS_SAR_CH_WORK_WORK_Pos               0UL
#define PASS_SAR_CH_WORK_WORK_Msk               0xFFFFUL
#define PASS_SAR_CH_WORK_ABOVE_HI_MIR_Pos       28UL
#define PASS_SAR_CH_WORK_ABOVE_HI_MIR_Msk       0x10000000UL
#define PASS_SAR_CH_WORK_RANGE_MIR_Pos          29UL
#define PASS_SAR_CH_WORK_RANGE_MIR_Msk          0x20000000UL
#define PASS_SAR_CH_WORK_PULSE_MIR_Pos          30UL
#define PASS_SAR_CH_WORK_PULSE_MIR_Msk          0x40000000UL
#define PASS_SAR_CH_WORK_VALID_MIR_Pos          31UL
#define PASS_SAR_CH_WORK_VALID_MIR_Msk          0x80000000UL
/* PASS_SAR_CH.RESULT */
#define PASS_SAR_CH_RESULT_RESULT_Pos           0UL
#define PASS_SAR_CH_RESULT_RESULT_Msk           0xFFFFUL
#define PASS_SAR_CH_RESULT_ABOVE_HI_MIR_Pos     28UL
#define PASS_SAR_CH_RESULT_ABOVE_HI_MIR_Msk     0x10000000UL
#define PASS_SAR_CH_RESULT_RANGE_INTR_MIR_Pos   29UL
#define PASS_SAR_CH_RESULT_RANGE_INTR_MIR_Msk   0x20000000UL
#define PASS_SAR_CH_RESULT_PULSE_INTR_MIR_Pos   30UL
#define PASS_SAR_CH_RESULT_PULSE_INTR_MIR_Msk   0x40000000UL
#define PASS_SAR_CH_RESULT_VALID_MIR_Pos        31UL
#define PASS_SAR_CH_RESULT_VALID_MIR_Msk        0x80000000UL
/* PASS_SAR_CH.GRP_STAT */
#define PASS_SAR_CH_GRP_STAT_GRP_COMPLETE_Pos   0UL
#define PASS_SAR_CH_GRP_STAT_GRP_COMPLETE_Msk   0x1UL
#define PASS_SAR_CH_GRP_STAT_GRP_CANCELLED_Pos  1UL
#define PASS_SAR_CH_GRP_STAT_GRP_CANCELLED_Msk  0x2UL
#define PASS_SAR_CH_GRP_STAT_GRP_OVERFLOW_Pos   2UL
#define PASS_SAR_CH_GRP_STAT_GRP_OVERFLOW_Msk   0x4UL
#define PASS_SAR_CH_GRP_STAT_CH_RANGE_COMPLETE_Pos 8UL
#define PASS_SAR_CH_GRP_STAT_CH_RANGE_COMPLETE_Msk 0x100UL
#define PASS_SAR_CH_GRP_STAT_CH_PULSE_COMPLETE_Pos 9UL
#define PASS_SAR_CH_GRP_STAT_CH_PULSE_COMPLETE_Msk 0x200UL
#define PASS_SAR_CH_GRP_STAT_CH_OVERFLOW_Pos    10UL
#define PASS_SAR_CH_GRP_STAT_CH_OVERFLOW_Msk    0x400UL
#define PASS_SAR_CH_GRP_STAT_GRP_BUSY_Pos       16UL
#define PASS_SAR_CH_GRP_STAT_GRP_BUSY_Msk       0x10000UL
/* PASS_SAR_CH.ENABLE */
#define PASS_SAR_CH_ENABLE_CHAN_EN_Pos          0UL
#define PASS_SAR_CH_ENABLE_CHAN_EN_Msk          0x1UL
/* PASS_SAR_CH.TR_CMD */
#define PASS_SAR_CH_TR_CMD_START_Pos            0UL
#define PASS_SAR_CH_TR_CMD_START_Msk            0x1UL


/* PASS_SAR.CTL */
#define PASS_SAR_CTL_PWRUP_TIME_Pos             0UL
#define PASS_SAR_CTL_PWRUP_TIME_Msk             0xFFUL
#define PASS_SAR_CTL_IDLE_PWRDWN_Pos            8UL
#define PASS_SAR_CTL_IDLE_PWRDWN_Msk            0x100UL
#define PASS_SAR_CTL_MSB_STRETCH_Pos            9UL
#define PASS_SAR_CTL_MSB_STRETCH_Msk            0x200UL
#define PASS_SAR_CTL_HALF_LSB_Pos               10UL
#define PASS_SAR_CTL_HALF_LSB_Msk               0x400UL
#define PASS_SAR_CTL_SARMUX_EN_Pos              29UL
#define PASS_SAR_CTL_SARMUX_EN_Msk              0x20000000UL
#define PASS_SAR_CTL_ADC_EN_Pos                 30UL
#define PASS_SAR_CTL_ADC_EN_Msk                 0x40000000UL
#define PASS_SAR_CTL_ENABLED_Pos                31UL
#define PASS_SAR_CTL_ENABLED_Msk                0x80000000UL
/* PASS_SAR.DIAG_CTL */
#define PASS_SAR_DIAG_CTL_DIAG_SEL_Pos          0UL
#define PASS_SAR_DIAG_CTL_DIAG_SEL_Msk          0xFUL
#define PASS_SAR_DIAG_CTL_DIAG_EN_Pos           31UL
#define PASS_SAR_DIAG_CTL_DIAG_EN_Msk           0x80000000UL
/* PASS_SAR.PRECOND_CTL */
#define PASS_SAR_PRECOND_CTL_PRECOND_TIME_Pos   0UL
#define PASS_SAR_PRECOND_CTL_PRECOND_TIME_Msk   0xFUL
/* PASS_SAR.ANA_CAL */
#define PASS_SAR_ANA_CAL_AOFFSET_Pos            0UL
#define PASS_SAR_ANA_CAL_AOFFSET_Msk            0xFFUL
#define PASS_SAR_ANA_CAL_AGAIN_Pos              16UL
#define PASS_SAR_ANA_CAL_AGAIN_Msk              0x1F0000UL
/* PASS_SAR.DIG_CAL */
#define PASS_SAR_DIG_CAL_DOFFSET_Pos            0UL
#define PASS_SAR_DIG_CAL_DOFFSET_Msk            0xFFFUL
#define PASS_SAR_DIG_CAL_DGAIN_Pos              16UL
#define PASS_SAR_DIG_CAL_DGAIN_Msk              0x3F0000UL
/* PASS_SAR.ANA_CAL_ALT */
#define PASS_SAR_ANA_CAL_ALT_AOFFSET_Pos        0UL
#define PASS_SAR_ANA_CAL_ALT_AOFFSET_Msk        0xFFUL
#define PASS_SAR_ANA_CAL_ALT_AGAIN_Pos          16UL
#define PASS_SAR_ANA_CAL_ALT_AGAIN_Msk          0x1F0000UL
/* PASS_SAR.DIG_CAL_ALT */
#define PASS_SAR_DIG_CAL_ALT_DOFFSET_Pos        0UL
#define PASS_SAR_DIG_CAL_ALT_DOFFSET_Msk        0xFFFUL
#define PASS_SAR_DIG_CAL_ALT_DGAIN_Pos          16UL
#define PASS_SAR_DIG_CAL_ALT_DGAIN_Msk          0x3F0000UL
/* PASS_SAR.CAL_UPD_CMD */
#define PASS_SAR_CAL_UPD_CMD_UPDATE_Pos         0UL
#define PASS_SAR_CAL_UPD_CMD_UPDATE_Msk         0x1UL
/* PASS_SAR.TR_PEND */
#define PASS_SAR_TR_PEND_TR_PEND_Pos            0UL
#define PASS_SAR_TR_PEND_TR_PEND_Msk            0xFFFFFFFFUL
/* PASS_SAR.WORK_VALID */
#define PASS_SAR_WORK_VALID_WORK_VALID_Pos      0UL
#define PASS_SAR_WORK_VALID_WORK_VALID_Msk      0xFFFFFFFFUL
/* PASS_SAR.WORK_RANGE */
#define PASS_SAR_WORK_RANGE_RANGE_Pos           0UL
#define PASS_SAR_WORK_RANGE_RANGE_Msk           0xFFFFFFFFUL
/* PASS_SAR.WORK_RANGE_HI */
#define PASS_SAR_WORK_RANGE_HI_ABOVE_HI_Pos     0UL
#define PASS_SAR_WORK_RANGE_HI_ABOVE_HI_Msk     0xFFFFFFFFUL
/* PASS_SAR.WORK_PULSE */
#define PASS_SAR_WORK_PULSE_PULSE_Pos           0UL
#define PASS_SAR_WORK_PULSE_PULSE_Msk           0xFFFFFFFFUL
/* PASS_SAR.RESULT_VALID */
#define PASS_SAR_RESULT_VALID_RESULT_VALID_Pos  0UL
#define PASS_SAR_RESULT_VALID_RESULT_VALID_Msk  0xFFFFFFFFUL
/* PASS_SAR.RESULT_RANGE_HI */
#define PASS_SAR_RESULT_RANGE_HI_ABOVE_HI_Pos   0UL
#define PASS_SAR_RESULT_RANGE_HI_ABOVE_HI_Msk   0xFFFFFFFFUL
/* PASS_SAR.STATUS */
#define PASS_SAR_STATUS_CUR_CHAN_Pos            0UL
#define PASS_SAR_STATUS_CUR_CHAN_Msk            0x1FUL
#define PASS_SAR_STATUS_CUR_PRIO_Pos            8UL
#define PASS_SAR_STATUS_CUR_PRIO_Msk            0x700UL
#define PASS_SAR_STATUS_CUR_PREEMPT_TYPE_Pos    12UL
#define PASS_SAR_STATUS_CUR_PREEMPT_TYPE_Msk    0x3000UL
#define PASS_SAR_STATUS_DBG_FREEZE_Pos          29UL
#define PASS_SAR_STATUS_DBG_FREEZE_Msk          0x20000000UL
#define PASS_SAR_STATUS_PWRUP_BUSY_Pos          30UL
#define PASS_SAR_STATUS_PWRUP_BUSY_Msk          0x40000000UL
#define PASS_SAR_STATUS_BUSY_Pos                31UL
#define PASS_SAR_STATUS_BUSY_Msk                0x80000000UL
/* PASS_SAR.AVG_STAT */
#define PASS_SAR_AVG_STAT_CUR_AVG_ACCU_Pos      0UL
#define PASS_SAR_AVG_STAT_CUR_AVG_ACCU_Msk      0xFFFFFUL
#define PASS_SAR_AVG_STAT_CUR_AVG_CNT_Pos       24UL
#define PASS_SAR_AVG_STAT_CUR_AVG_CNT_Msk       0xFF000000UL


/* PASS_EPASS_MMIO.PASS_CTL */
#define PASS_EPASS_MMIO_PASS_CTL_SUPPLY_MON_EN_A_Pos 0UL
#define PASS_EPASS_MMIO_PASS_CTL_SUPPLY_MON_EN_A_Msk 0x1UL
#define PASS_EPASS_MMIO_PASS_CTL_SUPPLY_MON_LVL_A_Pos 1UL
#define PASS_EPASS_MMIO_PASS_CTL_SUPPLY_MON_LVL_A_Msk 0x2UL
#define PASS_EPASS_MMIO_PASS_CTL_SUPPLY_MON_EN_B_Pos 4UL
#define PASS_EPASS_MMIO_PASS_CTL_SUPPLY_MON_EN_B_Msk 0x10UL
#define PASS_EPASS_MMIO_PASS_CTL_SUPPLY_MON_LVL_B_Pos 5UL
#define PASS_EPASS_MMIO_PASS_CTL_SUPPLY_MON_LVL_B_Msk 0x20UL
#define PASS_EPASS_MMIO_PASS_CTL_REFBUF_MODE_Pos 21UL
#define PASS_EPASS_MMIO_PASS_CTL_REFBUF_MODE_Msk 0x600000UL
#define PASS_EPASS_MMIO_PASS_CTL_DBG_FREEZE_EN_Pos 28UL
#define PASS_EPASS_MMIO_PASS_CTL_DBG_FREEZE_EN_Msk 0xF0000000UL
/* PASS_EPASS_MMIO.SAR_TR_IN_SEL */
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN0_SEL_Pos 0UL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN0_SEL_Msk 0xFUL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN1_SEL_Pos 4UL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN1_SEL_Msk 0xF0UL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN2_SEL_Pos 8UL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN2_SEL_Msk 0xF00UL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN3_SEL_Pos 12UL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN3_SEL_Msk 0xF000UL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN4_SEL_Pos 16UL
#define PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN4_SEL_Msk 0xF0000UL
/* PASS_EPASS_MMIO.SAR_TR_OUT_SEL */
#define PASS_EPASS_MMIO_SAR_TR_OUT_SEL_OUT0_SEL_Pos 0UL
#define PASS_EPASS_MMIO_SAR_TR_OUT_SEL_OUT0_SEL_Msk 0x3FUL
#define PASS_EPASS_MMIO_SAR_TR_OUT_SEL_OUT1_SEL_Pos 8UL
#define PASS_EPASS_MMIO_SAR_TR_OUT_SEL_OUT1_SEL_Msk 0x3F00UL
/* PASS_EPASS_MMIO.TEST_CTL */
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_CUR_IN_Pos 0UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_CUR_IN_Msk 0x1UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_VB_OUT_Pos 2UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_VB_OUT_Msk 0x4UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_VE_OUT_Pos 3UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_VE_OUT_Msk 0x8UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_DIODE_EN_Pos 4UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_DIODE_EN_Msk 0x10UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_DIODE_PNP_EN_Pos 5UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_DIODE_PNP_EN_Msk 0x20UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_VI_SEL_Pos 6UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_VI_SEL_Msk 0x40UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_CUR_SEL_Pos 8UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_CUR_SEL_Msk 0x300UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_SPARE_Pos 12UL
#define PASS_EPASS_MMIO_TEST_CTL_TS_CAL_SPARE_Msk 0x1000UL


#endif /* _CYIP_PASS_H_ */


/* [] END OF FILE */
