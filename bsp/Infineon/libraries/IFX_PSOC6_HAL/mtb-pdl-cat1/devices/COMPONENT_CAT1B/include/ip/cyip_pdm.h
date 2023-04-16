/***************************************************************************//**
* \file cyip_pdm.h
*
* \brief
* PDM IP definitions
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

#ifndef _CYIP_PDM_H_
#define _CYIP_PDM_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     PDM
*******************************************************************************/

#define PDM_CH_SECTION_SIZE                     0x00000100UL
#define PDM_SECTION_SIZE                        0x00010000UL

/**
  * \brief PDM RX structure (PDM_CH)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
   __IM uint32_t RESERVED[3];
  __IOM uint32_t IF_CTL;                        /*!< 0x00000010 Interface control */
  __IOM uint32_t CIC_CTL;                       /*!< 0x00000014 CIC control */
  __IOM uint32_t FIR0_CTL;                      /*!< 0x00000018 FIR 0 control */
  __IOM uint32_t FIR1_CTL;                      /*!< 0x0000001C FIR 1 control */
  __IOM uint32_t DC_BLOCK_CTL;                  /*!< 0x00000020 DC block control */
   __IM uint32_t RESERVED1[23];
  __IOM uint32_t RX_FIFO_CTL;                   /*!< 0x00000080 RX FIFO control */
   __IM uint32_t RX_FIFO_STATUS;                /*!< 0x00000084 RX FIFO status */
   __IM uint32_t RX_FIFO_RD;                    /*!< 0x00000088 RX FIFO read */
   __IM uint32_t RX_FIFO_RD_SILENT;             /*!< 0x0000008C RX FIFO silent read */
   __IM uint32_t RESERVED2[12];
  __IOM uint32_t INTR_RX;                       /*!< 0x000000C0 Interrupt */
  __IOM uint32_t INTR_RX_SET;                   /*!< 0x000000C4 Interrupt set */
  __IOM uint32_t INTR_RX_MASK;                  /*!< 0x000000C8 Interrupt mask */
   __IM uint32_t INTR_RX_MASKED;                /*!< 0x000000CC Interrupt masked */
   __IM uint32_t RESERVED3[12];
} PDM_CH_Type;                                  /*!< Size = 256 (0x100) */

/**
  * \brief PDM (PDM)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
  __IOM uint32_t CTL_CLR;                       /*!< 0x00000004 Control clear */
  __IOM uint32_t CTL_SET;                       /*!< 0x00000008 Control set */
   __IM uint32_t RESERVED;
  __IOM uint32_t CLOCK_CTL;                     /*!< 0x00000010 Clock control */
   __IM uint32_t RESERVED1[3];
  __IOM uint32_t ROUTE_CTL;                     /*!< 0x00000020 Route control */
   __IM uint32_t RESERVED2[3];
  __IOM uint32_t TEST_CTL;                      /*!< 0x00000030 Test control */
   __IM uint32_t RESERVED3[51];
  __IOM uint32_t FIR0_COEFF0;                   /*!< 0x00000100 FIR 0 coefficients 0 */
  __IOM uint32_t FIR0_COEFF1;                   /*!< 0x00000104 FIR 0 coefficients 1 */
  __IOM uint32_t FIR0_COEFF2;                   /*!< 0x00000108 FIR 0 coefficients 2 */
  __IOM uint32_t FIR0_COEFF3;                   /*!< 0x0000010C FIR 0 coefficients 3 */
  __IOM uint32_t FIR0_COEFF4;                   /*!< 0x00000110 FIR 0 coefficients 4 */
  __IOM uint32_t FIR0_COEFF5;                   /*!< 0x00000114 FIR 0 coefficients 5 */
  __IOM uint32_t FIR0_COEFF6;                   /*!< 0x00000118 FIR 0 coefficients 6 */
  __IOM uint32_t FIR0_COEFF7;                   /*!< 0x0000011C FIR 0 coefficients 7 */
   __IM uint32_t RESERVED4[8];
  __IOM uint32_t FIR1_COEFF0;                   /*!< 0x00000140 FIR 1 coefficients 0 */
  __IOM uint32_t FIR1_COEFF1;                   /*!< 0x00000144 FIR 1 coefficients 1 */
  __IOM uint32_t FIR1_COEFF2;                   /*!< 0x00000148 FIR 1 coefficients 2 */
  __IOM uint32_t FIR1_COEFF3;                   /*!< 0x0000014C FIR 1 coefficients 3 */
  __IOM uint32_t FIR1_COEFF4;                   /*!< 0x00000150 FIR 1 coefficients 4 */
  __IOM uint32_t FIR1_COEFF5;                   /*!< 0x00000154 FIR 1 coefficients 5 */
  __IOM uint32_t FIR1_COEFF6;                   /*!< 0x00000158 FIR 1 coefficients 6 */
  __IOM uint32_t FIR1_COEFF7;                   /*!< 0x0000015C FIR 1 coefficients 7 */
  __IOM uint32_t FIR1_COEFF8;                   /*!< 0x00000160 FIR 1 coefficients 8 */
  __IOM uint32_t FIR1_COEFF9;                   /*!< 0x00000164 FIR 1 coefficients 9 */
  __IOM uint32_t FIR1_COEFF10;                  /*!< 0x00000168 FIR 1 coefficients 10 */
  __IOM uint32_t FIR1_COEFF11;                  /*!< 0x0000016C FIR 1 coefficients 11 */
  __IOM uint32_t FIR1_COEFF12;                  /*!< 0x00000170 FIR 1 coefficients 12 */
  __IOM uint32_t FIR1_COEFF13;                  /*!< 0x00000174 FIR 1 coefficients 13 */
   __IM uint32_t RESERVED5[8098];
        PDM_CH_Type CH[8];                      /*!< 0x00008000 PDM RX structure */
} PDM_Type;                                     /*!< Size = 34816 (0x8800) */


/* PDM_CH.CTL */
#define PDM_CH_CTL_WORD_SIZE_Pos                0UL
#define PDM_CH_CTL_WORD_SIZE_Msk                0xFUL
#define PDM_CH_CTL_WORD_SIGN_EXTEND_Pos         8UL
#define PDM_CH_CTL_WORD_SIGN_EXTEND_Msk         0x100UL
#define PDM_CH_CTL_ENABLED_Pos                  31UL
#define PDM_CH_CTL_ENABLED_Msk                  0x80000000UL
/* PDM_CH.IF_CTL */
#define PDM_CH_IF_CTL_SAMPLE_DELAY_Pos          0UL
#define PDM_CH_IF_CTL_SAMPLE_DELAY_Msk          0xFFUL
/* PDM_CH.CIC_CTL */
#define PDM_CH_CIC_CTL_DECIM_CODE_Pos           0UL
#define PDM_CH_CIC_CTL_DECIM_CODE_Msk           0x7UL
/* PDM_CH.FIR0_CTL */
#define PDM_CH_FIR0_CTL_DECIM3_Pos              0UL
#define PDM_CH_FIR0_CTL_DECIM3_Msk              0x7UL
#define PDM_CH_FIR0_CTL_SCALE_Pos               8UL
#define PDM_CH_FIR0_CTL_SCALE_Msk               0x1F00UL
#define PDM_CH_FIR0_CTL_ENABLED_Pos             31UL
#define PDM_CH_FIR0_CTL_ENABLED_Msk             0x80000000UL
/* PDM_CH.FIR1_CTL */
#define PDM_CH_FIR1_CTL_DECIM2_Pos              0UL
#define PDM_CH_FIR1_CTL_DECIM2_Msk              0x3UL
#define PDM_CH_FIR1_CTL_SCALE_Pos               8UL
#define PDM_CH_FIR1_CTL_SCALE_Msk               0x1F00UL
#define PDM_CH_FIR1_CTL_ENABLED_Pos             31UL
#define PDM_CH_FIR1_CTL_ENABLED_Msk             0x80000000UL
/* PDM_CH.DC_BLOCK_CTL */
#define PDM_CH_DC_BLOCK_CTL_CODE_Pos            0UL
#define PDM_CH_DC_BLOCK_CTL_CODE_Msk            0x7UL
#define PDM_CH_DC_BLOCK_CTL_ENABLED_Pos         31UL
#define PDM_CH_DC_BLOCK_CTL_ENABLED_Msk         0x80000000UL
/* PDM_CH.RX_FIFO_CTL */
#define PDM_CH_RX_FIFO_CTL_TRIGGER_LEVEL_Pos    0UL
#define PDM_CH_RX_FIFO_CTL_TRIGGER_LEVEL_Msk    0x3FUL
#define PDM_CH_RX_FIFO_CTL_FREEZE_Pos           17UL
#define PDM_CH_RX_FIFO_CTL_FREEZE_Msk           0x20000UL
/* PDM_CH.RX_FIFO_STATUS */
#define PDM_CH_RX_FIFO_STATUS_USED_Pos          0UL
#define PDM_CH_RX_FIFO_STATUS_USED_Msk          0x7FUL
#define PDM_CH_RX_FIFO_STATUS_RD_PTR_Pos        16UL
#define PDM_CH_RX_FIFO_STATUS_RD_PTR_Msk        0x3F0000UL
#define PDM_CH_RX_FIFO_STATUS_WR_PTR_Pos        24UL
#define PDM_CH_RX_FIFO_STATUS_WR_PTR_Msk        0x3F000000UL
/* PDM_CH.RX_FIFO_RD */
#define PDM_CH_RX_FIFO_RD_DATA_Pos              0UL
#define PDM_CH_RX_FIFO_RD_DATA_Msk              0xFFFFFFFFUL
/* PDM_CH.RX_FIFO_RD_SILENT */
#define PDM_CH_RX_FIFO_RD_SILENT_DATA_Pos       0UL
#define PDM_CH_RX_FIFO_RD_SILENT_DATA_Msk       0xFFFFFFFFUL
/* PDM_CH.INTR_RX */
#define PDM_CH_INTR_RX_FIFO_TRIGGER_Pos         0UL
#define PDM_CH_INTR_RX_FIFO_TRIGGER_Msk         0x1UL
#define PDM_CH_INTR_RX_FIFO_OVERFLOW_Pos        1UL
#define PDM_CH_INTR_RX_FIFO_OVERFLOW_Msk        0x2UL
#define PDM_CH_INTR_RX_FIFO_UNDERFLOW_Pos       2UL
#define PDM_CH_INTR_RX_FIFO_UNDERFLOW_Msk       0x4UL
#define PDM_CH_INTR_RX_FIR_OVERFLOW_Pos         4UL
#define PDM_CH_INTR_RX_FIR_OVERFLOW_Msk         0x10UL
#define PDM_CH_INTR_RX_IF_OVERFLOW_Pos          8UL
#define PDM_CH_INTR_RX_IF_OVERFLOW_Msk          0x100UL
/* PDM_CH.INTR_RX_SET */
#define PDM_CH_INTR_RX_SET_FIFO_TRIGGER_Pos     0UL
#define PDM_CH_INTR_RX_SET_FIFO_TRIGGER_Msk     0x1UL
#define PDM_CH_INTR_RX_SET_FIFO_OVERFLOW_Pos    1UL
#define PDM_CH_INTR_RX_SET_FIFO_OVERFLOW_Msk    0x2UL
#define PDM_CH_INTR_RX_SET_FIFO_UNDERFLOW_Pos   2UL
#define PDM_CH_INTR_RX_SET_FIFO_UNDERFLOW_Msk   0x4UL
#define PDM_CH_INTR_RX_SET_FIR_OVERFLOW_Pos     4UL
#define PDM_CH_INTR_RX_SET_FIR_OVERFLOW_Msk     0x10UL
#define PDM_CH_INTR_RX_SET_IF_OVERFLOW_Pos      8UL
#define PDM_CH_INTR_RX_SET_IF_OVERFLOW_Msk      0x100UL
/* PDM_CH.INTR_RX_MASK */
#define PDM_CH_INTR_RX_MASK_FIFO_TRIGGER_Pos    0UL
#define PDM_CH_INTR_RX_MASK_FIFO_TRIGGER_Msk    0x1UL
#define PDM_CH_INTR_RX_MASK_FIFO_OVERFLOW_Pos   1UL
#define PDM_CH_INTR_RX_MASK_FIFO_OVERFLOW_Msk   0x2UL
#define PDM_CH_INTR_RX_MASK_FIFO_UNDERFLOW_Pos  2UL
#define PDM_CH_INTR_RX_MASK_FIFO_UNDERFLOW_Msk  0x4UL
#define PDM_CH_INTR_RX_MASK_FIR_OVERFLOW_Pos    4UL
#define PDM_CH_INTR_RX_MASK_FIR_OVERFLOW_Msk    0x10UL
#define PDM_CH_INTR_RX_MASK_IF_OVERFLOW_Pos     8UL
#define PDM_CH_INTR_RX_MASK_IF_OVERFLOW_Msk     0x100UL
/* PDM_CH.INTR_RX_MASKED */
#define PDM_CH_INTR_RX_MASKED_FIFO_TRIGGER_Pos  0UL
#define PDM_CH_INTR_RX_MASKED_FIFO_TRIGGER_Msk  0x1UL
#define PDM_CH_INTR_RX_MASKED_FIFO_OVERFLOW_Pos 1UL
#define PDM_CH_INTR_RX_MASKED_FIFO_OVERFLOW_Msk 0x2UL
#define PDM_CH_INTR_RX_MASKED_FIFO_UNDERFLOW_Pos 2UL
#define PDM_CH_INTR_RX_MASKED_FIFO_UNDERFLOW_Msk 0x4UL
#define PDM_CH_INTR_RX_MASKED_FIR_OVERFLOW_Pos  4UL
#define PDM_CH_INTR_RX_MASKED_FIR_OVERFLOW_Msk  0x10UL
#define PDM_CH_INTR_RX_MASKED_IF_OVERFLOW_Pos   8UL
#define PDM_CH_INTR_RX_MASKED_IF_OVERFLOW_Msk   0x100UL


/* PDM.CTL */
#define PDM_CTL_ACTIVE_Pos                      0UL
#define PDM_CTL_ACTIVE_Msk                      0xFFUL
/* PDM.CTL_CLR */
#define PDM_CTL_CLR_ACTIVE_Pos                  0UL
#define PDM_CTL_CLR_ACTIVE_Msk                  0xFFUL
/* PDM.CTL_SET */
#define PDM_CTL_SET_ACTIVE_Pos                  0UL
#define PDM_CTL_SET_ACTIVE_Msk                  0xFFUL
/* PDM.CLOCK_CTL */
#define PDM_CLOCK_CTL_CLOCK_DIV_Pos             0UL
#define PDM_CLOCK_CTL_CLOCK_DIV_Msk             0xFFUL
#define PDM_CLOCK_CTL_CLOCK_SEL_Pos             8UL
#define PDM_CLOCK_CTL_CLOCK_SEL_Msk             0x300UL
#define PDM_CLOCK_CTL_HALVE_Pos                 16UL
#define PDM_CLOCK_CTL_HALVE_Msk                 0x10000UL
/* PDM.ROUTE_CTL */
#define PDM_ROUTE_CTL_DATA_SEL_Pos              0UL
#define PDM_ROUTE_CTL_DATA_SEL_Msk              0xFFUL
/* PDM.TEST_CTL */
#define PDM_TEST_CTL_DRIVE_DELAY_HI_Pos         0UL
#define PDM_TEST_CTL_DRIVE_DELAY_HI_Msk         0xFFUL
#define PDM_TEST_CTL_DRIVE_DELAY_LO_Pos         8UL
#define PDM_TEST_CTL_DRIVE_DELAY_LO_Msk         0xFF00UL
#define PDM_TEST_CTL_MODE_HI_Pos                16UL
#define PDM_TEST_CTL_MODE_HI_Msk                0x30000UL
#define PDM_TEST_CTL_MODE_LO_Pos                18UL
#define PDM_TEST_CTL_MODE_LO_Msk                0xC0000UL
#define PDM_TEST_CTL_AUDIO_FREQ_DIV_Pos         20UL
#define PDM_TEST_CTL_AUDIO_FREQ_DIV_Msk         0xF00000UL
#define PDM_TEST_CTL_CH_ENABLED_Pos             24UL
#define PDM_TEST_CTL_CH_ENABLED_Msk             0xFF000000UL
/* PDM.FIR0_COEFF0 */
#define PDM_FIR0_COEFF0_DATA0_Pos               0UL
#define PDM_FIR0_COEFF0_DATA0_Msk               0x3FFFUL
#define PDM_FIR0_COEFF0_DATA1_Pos               16UL
#define PDM_FIR0_COEFF0_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR0_COEFF1 */
#define PDM_FIR0_COEFF1_DATA0_Pos               0UL
#define PDM_FIR0_COEFF1_DATA0_Msk               0x3FFFUL
#define PDM_FIR0_COEFF1_DATA1_Pos               16UL
#define PDM_FIR0_COEFF1_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR0_COEFF2 */
#define PDM_FIR0_COEFF2_DATA0_Pos               0UL
#define PDM_FIR0_COEFF2_DATA0_Msk               0x3FFFUL
#define PDM_FIR0_COEFF2_DATA1_Pos               16UL
#define PDM_FIR0_COEFF2_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR0_COEFF3 */
#define PDM_FIR0_COEFF3_DATA0_Pos               0UL
#define PDM_FIR0_COEFF3_DATA0_Msk               0x3FFFUL
#define PDM_FIR0_COEFF3_DATA1_Pos               16UL
#define PDM_FIR0_COEFF3_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR0_COEFF4 */
#define PDM_FIR0_COEFF4_DATA0_Pos               0UL
#define PDM_FIR0_COEFF4_DATA0_Msk               0x3FFFUL
#define PDM_FIR0_COEFF4_DATA1_Pos               16UL
#define PDM_FIR0_COEFF4_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR0_COEFF5 */
#define PDM_FIR0_COEFF5_DATA0_Pos               0UL
#define PDM_FIR0_COEFF5_DATA0_Msk               0x3FFFUL
#define PDM_FIR0_COEFF5_DATA1_Pos               16UL
#define PDM_FIR0_COEFF5_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR0_COEFF6 */
#define PDM_FIR0_COEFF6_DATA0_Pos               0UL
#define PDM_FIR0_COEFF6_DATA0_Msk               0x3FFFUL
#define PDM_FIR0_COEFF6_DATA1_Pos               16UL
#define PDM_FIR0_COEFF6_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR0_COEFF7 */
#define PDM_FIR0_COEFF7_DATA0_Pos               0UL
#define PDM_FIR0_COEFF7_DATA0_Msk               0x3FFFUL
#define PDM_FIR0_COEFF7_DATA1_Pos               16UL
#define PDM_FIR0_COEFF7_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF0 */
#define PDM_FIR1_COEFF0_DATA0_Pos               0UL
#define PDM_FIR1_COEFF0_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF0_DATA1_Pos               16UL
#define PDM_FIR1_COEFF0_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF1 */
#define PDM_FIR1_COEFF1_DATA0_Pos               0UL
#define PDM_FIR1_COEFF1_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF1_DATA1_Pos               16UL
#define PDM_FIR1_COEFF1_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF2 */
#define PDM_FIR1_COEFF2_DATA0_Pos               0UL
#define PDM_FIR1_COEFF2_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF2_DATA1_Pos               16UL
#define PDM_FIR1_COEFF2_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF3 */
#define PDM_FIR1_COEFF3_DATA0_Pos               0UL
#define PDM_FIR1_COEFF3_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF3_DATA1_Pos               16UL
#define PDM_FIR1_COEFF3_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF4 */
#define PDM_FIR1_COEFF4_DATA0_Pos               0UL
#define PDM_FIR1_COEFF4_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF4_DATA1_Pos               16UL
#define PDM_FIR1_COEFF4_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF5 */
#define PDM_FIR1_COEFF5_DATA0_Pos               0UL
#define PDM_FIR1_COEFF5_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF5_DATA1_Pos               16UL
#define PDM_FIR1_COEFF5_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF6 */
#define PDM_FIR1_COEFF6_DATA0_Pos               0UL
#define PDM_FIR1_COEFF6_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF6_DATA1_Pos               16UL
#define PDM_FIR1_COEFF6_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF7 */
#define PDM_FIR1_COEFF7_DATA0_Pos               0UL
#define PDM_FIR1_COEFF7_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF7_DATA1_Pos               16UL
#define PDM_FIR1_COEFF7_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF8 */
#define PDM_FIR1_COEFF8_DATA0_Pos               0UL
#define PDM_FIR1_COEFF8_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF8_DATA1_Pos               16UL
#define PDM_FIR1_COEFF8_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF9 */
#define PDM_FIR1_COEFF9_DATA0_Pos               0UL
#define PDM_FIR1_COEFF9_DATA0_Msk               0x3FFFUL
#define PDM_FIR1_COEFF9_DATA1_Pos               16UL
#define PDM_FIR1_COEFF9_DATA1_Msk               0x3FFF0000UL
/* PDM.FIR1_COEFF10 */
#define PDM_FIR1_COEFF10_DATA0_Pos              0UL
#define PDM_FIR1_COEFF10_DATA0_Msk              0x3FFFUL
#define PDM_FIR1_COEFF10_DATA1_Pos              16UL
#define PDM_FIR1_COEFF10_DATA1_Msk              0x3FFF0000UL
/* PDM.FIR1_COEFF11 */
#define PDM_FIR1_COEFF11_DATA0_Pos              0UL
#define PDM_FIR1_COEFF11_DATA0_Msk              0x3FFFUL
#define PDM_FIR1_COEFF11_DATA1_Pos              16UL
#define PDM_FIR1_COEFF11_DATA1_Msk              0x3FFF0000UL
/* PDM.FIR1_COEFF12 */
#define PDM_FIR1_COEFF12_DATA0_Pos              0UL
#define PDM_FIR1_COEFF12_DATA0_Msk              0x3FFFUL
#define PDM_FIR1_COEFF12_DATA1_Pos              16UL
#define PDM_FIR1_COEFF12_DATA1_Msk              0x3FFF0000UL
/* PDM.FIR1_COEFF13 */
#define PDM_FIR1_COEFF13_DATA0_Pos              0UL
#define PDM_FIR1_COEFF13_DATA0_Msk              0x3FFFUL
#define PDM_FIR1_COEFF13_DATA1_Pos              16UL
#define PDM_FIR1_COEFF13_DATA1_Msk              0x3FFF0000UL


#endif /* _CYIP_PDM_H_ */


/* [] END OF FILE */
