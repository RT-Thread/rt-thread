/***************************************************************************//**
* \file cyip_crypto.h
*
* \brief
* CRYPTO IP definitions
*
********************************************************************************
* \copyright
* (c) (2016-2021), Cypress Semiconductor Corporation (an Infineon company) or
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

#ifndef _CYIP_CRYPTO_H_
#define _CYIP_CRYPTO_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    CRYPTO
*******************************************************************************/

#define CRYPTO_SECTION_SIZE                     0x00010000UL

/**
  * \brief N/A (CRYPTO)
  */
typedef struct {
   __IM uint32_t CTL;                           /*!< 0x00000000 Control */
   __IM uint32_t STATUS;                        /*!< 0x00000004 Status */
   __IM uint32_t RESERVED[2];
  __IOM uint32_t ECC_CTL;                       /*!< 0x00000010 ECC control */
   __IM uint32_t RESERVED1[11];
  __IOM uint32_t AES_DESCR;                     /*!< 0x00000040 AES descriptor pointer */
   __IM uint32_t RESERVED2[15];
  __IOM uint32_t VU_DESCR;                      /*!< 0x00000080 VU descriptor pointer */
   __IM uint32_t RESERVED3[15];
  __IOM uint32_t SHA_DESCR;                     /*!< 0x000000C0 SHA descriptor pointer */
   __IM uint32_t RESERVED4[11];
  __IOM uint32_t INTR_ERROR;                    /*!< 0x000000F0 Error interrupt */
  __IOM uint32_t INTR_ERROR_SET;                /*!< 0x000000F4 Error interrupt set */
  __IOM uint32_t INTR_ERROR_MASK;               /*!< 0x000000F8 Error interrupt mask */
   __IM uint32_t INTR_ERROR_MASKED;             /*!< 0x000000FC Error interrupt masked */
  __IOM uint32_t TRNG_CTL0;                     /*!< 0x00000100 TRNG control 0 */
  __IOM uint32_t TRNG_CTL1;                     /*!< 0x00000104 TRNG control 1 */
   __IM uint32_t RESERVED5;
   __IM uint32_t TRNG_STATUS;                   /*!< 0x0000010C TRNG status */
   __IM uint32_t TRNG_RESULT;                   /*!< 0x00000110 TRNG result */
   __IM uint32_t RESERVED6[3];
  __IOM uint32_t TRNG_GARO_CTL;                 /*!< 0x00000120 TRNG GARO control */
  __IOM uint32_t TRNG_FIRO_CTL;                 /*!< 0x00000124 TRNG FIRO control */
   __IM uint32_t RESERVED7[6];
  __IOM uint32_t TRNG_MON_CTL;                  /*!< 0x00000140 TRNG monitor control */
   __IM uint32_t RESERVED8[3];
  __IOM uint32_t TRNG_MON_RC_CTL;               /*!< 0x00000150 TRNG monitor RC control */
   __IM uint32_t RESERVED9;
   __IM uint32_t TRNG_MON_RC_STATUS0;           /*!< 0x00000158 TRNG monitor RC status 0 */
   __IM uint32_t TRNG_MON_RC_STATUS1;           /*!< 0x0000015C TRNG monitor RC status 1 */
  __IOM uint32_t TRNG_MON_AP_CTL;               /*!< 0x00000160 TRNG monitor AP control */
   __IM uint32_t RESERVED10;
   __IM uint32_t TRNG_MON_AP_STATUS0;           /*!< 0x00000168 TRNG monitor AP status 0 */
   __IM uint32_t TRNG_MON_AP_STATUS1;           /*!< 0x0000016C TRNG monitor AP status 1 */
   __IM uint32_t RESERVED11[32];
  __IOM uint32_t INTR_TRNG;                     /*!< 0x000001F0 TRNG interrupt */
  __IOM uint32_t INTR_TRNG_SET;                 /*!< 0x000001F4 TRNG Interrupt set */
  __IOM uint32_t INTR_TRNG_MASK;                /*!< 0x000001F8 TRNG Interrupt mask */
   __IM uint32_t INTR_TRNG_MASKED;              /*!< 0x000001FC TRNG Interrupt masked */
} CRYPTO_Type;                                  /*!< Size = 512 (0x200) */


/* CRYPTO.CTL */
#define CRYPTO_CTL_P_Pos                        0UL
#define CRYPTO_CTL_P_Msk                        0x1UL
#define CRYPTO_CTL_NS_Pos                       1UL
#define CRYPTO_CTL_NS_Msk                       0x2UL
#define CRYPTO_CTL_PC_Pos                       4UL
#define CRYPTO_CTL_PC_Msk                       0xF0UL
#define CRYPTO_CTL_MS_Pos                       8UL
#define CRYPTO_CTL_MS_Msk                       0xF00UL
/* CRYPTO.STATUS */
#define CRYPTO_STATUS_BUSY_Pos                  0UL
#define CRYPTO_STATUS_BUSY_Msk                  0x1UL
/* CRYPTO.ECC_CTL */
#define CRYPTO_ECC_CTL_CHECK_EN_Pos             3UL
#define CRYPTO_ECC_CTL_CHECK_EN_Msk             0x8UL
/* CRYPTO.AES_DESCR */
#define CRYPTO_AES_DESCR_PTR_Pos                2UL
#define CRYPTO_AES_DESCR_PTR_Msk                0xFFFFFFFCUL
/* CRYPTO.VU_DESCR */
#define CRYPTO_VU_DESCR_PTR_Pos                 2UL
#define CRYPTO_VU_DESCR_PTR_Msk                 0xFFFFFFFCUL
/* CRYPTO.SHA_DESCR */
#define CRYPTO_SHA_DESCR_PTR_Pos                2UL
#define CRYPTO_SHA_DESCR_PTR_Msk                0xFFFFFFFCUL
/* CRYPTO.INTR_ERROR */
#define CRYPTO_INTR_ERROR_BUS_ERROR_Pos         0UL
#define CRYPTO_INTR_ERROR_BUS_ERROR_Msk         0x1UL
/* CRYPTO.INTR_ERROR_SET */
#define CRYPTO_INTR_ERROR_SET_BUS_ERROR_Pos     0UL
#define CRYPTO_INTR_ERROR_SET_BUS_ERROR_Msk     0x1UL
/* CRYPTO.INTR_ERROR_MASK */
#define CRYPTO_INTR_ERROR_MASK_BUS_ERROR_Pos    0UL
#define CRYPTO_INTR_ERROR_MASK_BUS_ERROR_Msk    0x1UL
/* CRYPTO.INTR_ERROR_MASKED */
#define CRYPTO_INTR_ERROR_MASKED_BUS_ERROR_Pos  0UL
#define CRYPTO_INTR_ERROR_MASKED_BUS_ERROR_Msk  0x1UL
/* CRYPTO.TRNG_CTL0 */
#define CRYPTO_TRNG_CTL0_SAMPLE_CLOCK_DIV_Pos   0UL
#define CRYPTO_TRNG_CTL0_SAMPLE_CLOCK_DIV_Msk   0xFFUL
#define CRYPTO_TRNG_CTL0_RED_CLOCK_DIV_Pos      8UL
#define CRYPTO_TRNG_CTL0_RED_CLOCK_DIV_Msk      0xFF00UL
#define CRYPTO_TRNG_CTL0_INIT_DELAY_Pos         16UL
#define CRYPTO_TRNG_CTL0_INIT_DELAY_Msk         0xFF0000UL
#define CRYPTO_TRNG_CTL0_VON_NEUMANN_CORR_Pos   24UL
#define CRYPTO_TRNG_CTL0_VON_NEUMANN_CORR_Msk   0x1000000UL
#define CRYPTO_TRNG_CTL0_FEEDBACK_EN_Pos        25UL
#define CRYPTO_TRNG_CTL0_FEEDBACK_EN_Msk        0x2000000UL
#define CRYPTO_TRNG_CTL0_STOP_ON_AP_DETECT_Pos  28UL
#define CRYPTO_TRNG_CTL0_STOP_ON_AP_DETECT_Msk  0x10000000UL
#define CRYPTO_TRNG_CTL0_STOP_ON_RC_DETECT_Pos  29UL
#define CRYPTO_TRNG_CTL0_STOP_ON_RC_DETECT_Msk  0x20000000UL
/* CRYPTO.TRNG_CTL1 */
#define CRYPTO_TRNG_CTL1_RO11_EN_Pos            0UL
#define CRYPTO_TRNG_CTL1_RO11_EN_Msk            0x1UL
#define CRYPTO_TRNG_CTL1_RO15_EN_Pos            1UL
#define CRYPTO_TRNG_CTL1_RO15_EN_Msk            0x2UL
#define CRYPTO_TRNG_CTL1_GARO15_EN_Pos          2UL
#define CRYPTO_TRNG_CTL1_GARO15_EN_Msk          0x4UL
#define CRYPTO_TRNG_CTL1_GARO31_EN_Pos          3UL
#define CRYPTO_TRNG_CTL1_GARO31_EN_Msk          0x8UL
#define CRYPTO_TRNG_CTL1_FIRO15_EN_Pos          4UL
#define CRYPTO_TRNG_CTL1_FIRO15_EN_Msk          0x10UL
#define CRYPTO_TRNG_CTL1_FIRO31_EN_Pos          5UL
#define CRYPTO_TRNG_CTL1_FIRO31_EN_Msk          0x20UL
/* CRYPTO.TRNG_STATUS */
#define CRYPTO_TRNG_STATUS_INITIALIZED_Pos      0UL
#define CRYPTO_TRNG_STATUS_INITIALIZED_Msk      0x1UL
/* CRYPTO.TRNG_RESULT */
#define CRYPTO_TRNG_RESULT_DATA_Pos             0UL
#define CRYPTO_TRNG_RESULT_DATA_Msk             0xFFFFFFFFUL
/* CRYPTO.TRNG_GARO_CTL */
#define CRYPTO_TRNG_GARO_CTL_POLYNOMIAL_Pos     0UL
#define CRYPTO_TRNG_GARO_CTL_POLYNOMIAL_Msk     0x7FFFFFFFUL
/* CRYPTO.TRNG_FIRO_CTL */
#define CRYPTO_TRNG_FIRO_CTL_POLYNOMIAL_Pos     0UL
#define CRYPTO_TRNG_FIRO_CTL_POLYNOMIAL_Msk     0x7FFFFFFFUL
/* CRYPTO.TRNG_MON_CTL */
#define CRYPTO_TRNG_MON_CTL_BITSTREAM_SEL_Pos   0UL
#define CRYPTO_TRNG_MON_CTL_BITSTREAM_SEL_Msk   0x3UL
#define CRYPTO_TRNG_MON_CTL_AP_Pos              8UL
#define CRYPTO_TRNG_MON_CTL_AP_Msk              0x100UL
#define CRYPTO_TRNG_MON_CTL_RC_Pos              9UL
#define CRYPTO_TRNG_MON_CTL_RC_Msk              0x200UL
/* CRYPTO.TRNG_MON_RC_CTL */
#define CRYPTO_TRNG_MON_RC_CTL_CUTOFF_COUNT8_Pos 0UL
#define CRYPTO_TRNG_MON_RC_CTL_CUTOFF_COUNT8_Msk 0xFFUL
/* CRYPTO.TRNG_MON_RC_STATUS0 */
#define CRYPTO_TRNG_MON_RC_STATUS0_BIT_Pos      0UL
#define CRYPTO_TRNG_MON_RC_STATUS0_BIT_Msk      0x1UL
/* CRYPTO.TRNG_MON_RC_STATUS1 */
#define CRYPTO_TRNG_MON_RC_STATUS1_REP_COUNT_Pos 0UL
#define CRYPTO_TRNG_MON_RC_STATUS1_REP_COUNT_Msk 0xFFUL
/* CRYPTO.TRNG_MON_AP_CTL */
#define CRYPTO_TRNG_MON_AP_CTL_CUTOFF_COUNT16_Pos 0UL
#define CRYPTO_TRNG_MON_AP_CTL_CUTOFF_COUNT16_Msk 0xFFFFUL
#define CRYPTO_TRNG_MON_AP_CTL_WINDOW_SIZE_Pos  16UL
#define CRYPTO_TRNG_MON_AP_CTL_WINDOW_SIZE_Msk  0xFFFF0000UL
/* CRYPTO.TRNG_MON_AP_STATUS0 */
#define CRYPTO_TRNG_MON_AP_STATUS0_BIT_Pos      0UL
#define CRYPTO_TRNG_MON_AP_STATUS0_BIT_Msk      0x1UL
/* CRYPTO.TRNG_MON_AP_STATUS1 */
#define CRYPTO_TRNG_MON_AP_STATUS1_OCC_COUNT_Pos 0UL
#define CRYPTO_TRNG_MON_AP_STATUS1_OCC_COUNT_Msk 0xFFFFUL
#define CRYPTO_TRNG_MON_AP_STATUS1_WINDOW_INDEX_Pos 16UL
#define CRYPTO_TRNG_MON_AP_STATUS1_WINDOW_INDEX_Msk 0xFFFF0000UL
/* CRYPTO.INTR_TRNG */
#define CRYPTO_INTR_TRNG_INITIALIZED_Pos        0UL
#define CRYPTO_INTR_TRNG_INITIALIZED_Msk        0x1UL
#define CRYPTO_INTR_TRNG_DATA_AVAILABLE_Pos     1UL
#define CRYPTO_INTR_TRNG_DATA_AVAILABLE_Msk     0x2UL
#define CRYPTO_INTR_TRNG_AP_DETECT_Pos          2UL
#define CRYPTO_INTR_TRNG_AP_DETECT_Msk          0x4UL
#define CRYPTO_INTR_TRNG_RC_DETECT_Pos          3UL
#define CRYPTO_INTR_TRNG_RC_DETECT_Msk          0x8UL
/* CRYPTO.INTR_TRNG_SET */
#define CRYPTO_INTR_TRNG_SET_INITIALIZED_Pos    0UL
#define CRYPTO_INTR_TRNG_SET_INITIALIZED_Msk    0x1UL
#define CRYPTO_INTR_TRNG_SET_DATA_AVAILABLE_Pos 1UL
#define CRYPTO_INTR_TRNG_SET_DATA_AVAILABLE_Msk 0x2UL
#define CRYPTO_INTR_TRNG_SET_AP_DETECT_Pos      2UL
#define CRYPTO_INTR_TRNG_SET_AP_DETECT_Msk      0x4UL
#define CRYPTO_INTR_TRNG_SET_RC_DETECT_Pos      3UL
#define CRYPTO_INTR_TRNG_SET_RC_DETECT_Msk      0x8UL
/* CRYPTO.INTR_TRNG_MASK */
#define CRYPTO_INTR_TRNG_MASK_INITIALIZED_Pos   0UL
#define CRYPTO_INTR_TRNG_MASK_INITIALIZED_Msk   0x1UL
#define CRYPTO_INTR_TRNG_MASK_DATA_AVAILABLE_Pos 1UL
#define CRYPTO_INTR_TRNG_MASK_DATA_AVAILABLE_Msk 0x2UL
#define CRYPTO_INTR_TRNG_MASK_AP_DETECT_Pos     2UL
#define CRYPTO_INTR_TRNG_MASK_AP_DETECT_Msk     0x4UL
#define CRYPTO_INTR_TRNG_MASK_RC_DETECT_Pos     3UL
#define CRYPTO_INTR_TRNG_MASK_RC_DETECT_Msk     0x8UL
/* CRYPTO.INTR_TRNG_MASKED */
#define CRYPTO_INTR_TRNG_MASKED_INITIALIZED_Pos 0UL
#define CRYPTO_INTR_TRNG_MASKED_INITIALIZED_Msk 0x1UL
#define CRYPTO_INTR_TRNG_MASKED_DATA_AVAILABLE_Pos 1UL
#define CRYPTO_INTR_TRNG_MASKED_DATA_AVAILABLE_Msk 0x2UL
#define CRYPTO_INTR_TRNG_MASKED_AP_DETECT_Pos   2UL
#define CRYPTO_INTR_TRNG_MASKED_AP_DETECT_Msk   0x4UL
#define CRYPTO_INTR_TRNG_MASKED_RC_DETECT_Pos   3UL
#define CRYPTO_INTR_TRNG_MASKED_RC_DETECT_Msk   0x8UL


#endif /* _CYIP_CRYPTO_H_ */


/* [] END OF FILE */
