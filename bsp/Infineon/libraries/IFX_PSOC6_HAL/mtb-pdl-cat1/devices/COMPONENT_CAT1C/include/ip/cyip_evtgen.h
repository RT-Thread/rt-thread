/***************************************************************************//**
* \file cyip_evtgen.h
*
* \brief
* EVTGEN IP definitions
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

#ifndef _CYIP_EVTGEN_H_
#define _CYIP_EVTGEN_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    EVTGEN
*******************************************************************************/

#define EVTGEN_COMP_STRUCT_SECTION_SIZE         0x00000020UL
#define EVTGEN_SECTION_SIZE                     0x00001000UL

/**
  * \brief Comparator structure (EVTGEN_COMP_STRUCT)
  */
typedef struct {
  __IOM uint32_t COMP_CTL;                      /*!< 0x00000000 Comparator control */
  __IOM uint32_t COMP0;                         /*!< 0x00000004 Comparator 0 (Active functionality) */
  __IOM uint32_t COMP1;                         /*!< 0x00000008 Comparator 1 (DeepSleep functionality) */
   __IM uint32_t RESERVED[5];
} EVTGEN_COMP_STRUCT_Type;                      /*!< Size = 32 (0x20) */

/**
  * \brief Event generator (EVTGEN)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
   __IM uint32_t COMP0_STATUS;                  /*!< 0x00000004 Comparator structures comparator 0 status */
   __IM uint32_t COMP1_STATUS;                  /*!< 0x00000008 Comparator structures comparator 1 status */
   __IM uint32_t RESERVED;
   __IM uint32_t COUNTER_STATUS;                /*!< 0x00000010 Counter status */
   __IM uint32_t COUNTER;                       /*!< 0x00000014 Counter */
   __IM uint32_t RESERVED1[2];
  __IOM uint32_t RATIO_CTL;                     /*!< 0x00000020 Ratio control */
  __IOM uint32_t RATIO;                         /*!< 0x00000024 Ratio */
   __IM uint32_t RESERVED2[2];
  __IOM uint32_t REF_CLOCK_CTL;                 /*!< 0x00000030 Reference clock control */
   __IM uint32_t RESERVED3[435];
  __IOM uint32_t INTR;                          /*!< 0x00000700 Interrupt */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000704 Interrupt set */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000708 Interrupt mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000070C Interrupt masked */
  __IOM uint32_t INTR_DPSLP;                    /*!< 0x00000710 DeepSleep interrupt */
  __IOM uint32_t INTR_DPSLP_SET;                /*!< 0x00000714 DeepSleep interrupt set */
  __IOM uint32_t INTR_DPSLP_MASK;               /*!< 0x00000718 DeepSleep interrupt mask */
   __IM uint32_t INTR_DPSLP_MASKED;             /*!< 0x0000071C DeepSleep interrupt masked */
   __IM uint32_t RESERVED4[56];
        EVTGEN_COMP_STRUCT_Type COMP_STRUCT[32]; /*!< 0x00000800 Comparator structure */
} EVTGEN_Type;                                  /*!< Size = 3072 (0xC00) */


/* EVTGEN_COMP_STRUCT.COMP_CTL */
#define EVTGEN_COMP_STRUCT_COMP_CTL_COMP0_EN_Pos 0UL
#define EVTGEN_COMP_STRUCT_COMP_CTL_COMP0_EN_Msk 0x1UL
#define EVTGEN_COMP_STRUCT_COMP_CTL_COMP1_EN_Pos 1UL
#define EVTGEN_COMP_STRUCT_COMP_CTL_COMP1_EN_Msk 0x2UL
#define EVTGEN_COMP_STRUCT_COMP_CTL_TR_OUT_EDGE_Pos 16UL
#define EVTGEN_COMP_STRUCT_COMP_CTL_TR_OUT_EDGE_Msk 0x10000UL
#define EVTGEN_COMP_STRUCT_COMP_CTL_ENABLED_Pos 31UL
#define EVTGEN_COMP_STRUCT_COMP_CTL_ENABLED_Msk 0x80000000UL
/* EVTGEN_COMP_STRUCT.COMP0 */
#define EVTGEN_COMP_STRUCT_COMP0_INT32_Pos      0UL
#define EVTGEN_COMP_STRUCT_COMP0_INT32_Msk      0xFFFFFFFFUL
/* EVTGEN_COMP_STRUCT.COMP1 */
#define EVTGEN_COMP_STRUCT_COMP1_INT32_Pos      0UL
#define EVTGEN_COMP_STRUCT_COMP1_INT32_Msk      0xFFFFFFFFUL


/* EVTGEN.CTL */
#define EVTGEN_CTL_ENABLED_Pos                  31UL
#define EVTGEN_CTL_ENABLED_Msk                  0x80000000UL
/* EVTGEN.COMP0_STATUS */
#define EVTGEN_COMP0_STATUS_COMP0_OUT_Pos       0UL
#define EVTGEN_COMP0_STATUS_COMP0_OUT_Msk       0xFFFFUL
/* EVTGEN.COMP1_STATUS */
#define EVTGEN_COMP1_STATUS_COMP1_OUT_Pos       0UL
#define EVTGEN_COMP1_STATUS_COMP1_OUT_Msk       0xFFFFUL
/* EVTGEN.COUNTER_STATUS */
#define EVTGEN_COUNTER_STATUS_VALID_Pos         31UL
#define EVTGEN_COUNTER_STATUS_VALID_Msk         0x80000000UL
/* EVTGEN.COUNTER */
#define EVTGEN_COUNTER_INT32_Pos                0UL
#define EVTGEN_COUNTER_INT32_Msk                0xFFFFFFFFUL
/* EVTGEN.RATIO_CTL */
#define EVTGEN_RATIO_CTL_DYNAMIC_MODE_Pos       16UL
#define EVTGEN_RATIO_CTL_DYNAMIC_MODE_Msk       0x70000UL
#define EVTGEN_RATIO_CTL_DYNAMIC_Pos            30UL
#define EVTGEN_RATIO_CTL_DYNAMIC_Msk            0x40000000UL
#define EVTGEN_RATIO_CTL_VALID_Pos              31UL
#define EVTGEN_RATIO_CTL_VALID_Msk              0x80000000UL
/* EVTGEN.RATIO */
#define EVTGEN_RATIO_FRAC8_Pos                  8UL
#define EVTGEN_RATIO_FRAC8_Msk                  0xFF00UL
#define EVTGEN_RATIO_INT16_Pos                  16UL
#define EVTGEN_RATIO_INT16_Msk                  0xFFFF0000UL
/* EVTGEN.REF_CLOCK_CTL */
#define EVTGEN_REF_CLOCK_CTL_INT_DIV_Pos        0UL
#define EVTGEN_REF_CLOCK_CTL_INT_DIV_Msk        0xFFUL
/* EVTGEN.INTR */
#define EVTGEN_INTR_COMP0_Pos                   0UL
#define EVTGEN_INTR_COMP0_Msk                   0xFFFFUL
/* EVTGEN.INTR_SET */
#define EVTGEN_INTR_SET_COMP0_Pos               0UL
#define EVTGEN_INTR_SET_COMP0_Msk               0xFFFFUL
/* EVTGEN.INTR_MASK */
#define EVTGEN_INTR_MASK_COMP0_Pos              0UL
#define EVTGEN_INTR_MASK_COMP0_Msk              0xFFFFUL
/* EVTGEN.INTR_MASKED */
#define EVTGEN_INTR_MASKED_COMP0_Pos            0UL
#define EVTGEN_INTR_MASKED_COMP0_Msk            0xFFFFUL
/* EVTGEN.INTR_DPSLP */
#define EVTGEN_INTR_DPSLP_COMP1_Pos             0UL
#define EVTGEN_INTR_DPSLP_COMP1_Msk             0xFFFFUL
/* EVTGEN.INTR_DPSLP_SET */
#define EVTGEN_INTR_DPSLP_SET_COMP1_Pos         0UL
#define EVTGEN_INTR_DPSLP_SET_COMP1_Msk         0xFFFFUL
/* EVTGEN.INTR_DPSLP_MASK */
#define EVTGEN_INTR_DPSLP_MASK_COMP1_Pos        0UL
#define EVTGEN_INTR_DPSLP_MASK_COMP1_Msk        0xFFFFUL
/* EVTGEN.INTR_DPSLP_MASKED */
#define EVTGEN_INTR_DPSLP_MASKED_COMP1_Pos      0UL
#define EVTGEN_INTR_DPSLP_MASKED_COMP1_Msk      0xFFFFUL


#endif /* _CYIP_EVTGEN_H_ */


/* [] END OF FILE */
