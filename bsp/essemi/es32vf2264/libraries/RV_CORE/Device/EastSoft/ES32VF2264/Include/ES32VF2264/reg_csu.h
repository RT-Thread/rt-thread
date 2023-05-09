/**********************************************************************************
 *
 * @file    reg_csu.h
 * @brief   CSU Head File
 *
 * @date    07 July 2022
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          07 July 2022    Lisq            the first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************
 */

#ifndef __REG_CSU_H__
#define __REG_CSU_H__

/****************** Bit definition for CSU_CON register ************************/

#define CSU_CON_TRIM_POSS   8U
#define CSU_CON_TRIM_POSE   16U
#define CSU_CON_TRIM_MSK    BITS(CSU_CON_TRIM_POSS,CSU_CON_TRIM_POSE)

#define CSU_CON_SYNCGEN_POS 2U
#define CSU_CON_SYNCGEN_MSK BIT(CSU_CON_SYNCGEN_POS)

#define CSU_CON_AUTOEN_POS  1U
#define CSU_CON_AUTOEN_MSK  BIT(CSU_CON_AUTOEN_POS)

#define CSU_CON_CNTEN_POS   0U
#define CSU_CON_CNTEN_MSK   BIT(CSU_CON_CNTEN_POS)

/****************** Bit definition for CSU_CFG register ************************/

#define CSU_CFG_TRIMSEL_POS 31U
#define CSU_CFG_TRIMSEL_MSK BIT(CSU_CFG_TRIMSEL_POS)

#define CSU_CFG_POLSEL_POS  30U
#define CSU_CFG_POLSEL_MSK  BIT(CSU_CFG_POLSEL_POS)

#define CSU_CFG_SYNCSRC_POSS    28U
#define CSU_CFG_SYNCSRC_POSE    29U
#define CSU_CFG_SYNCSRC_MSK BITS(CSU_CFG_SYNCSRC_POSS,CSU_CFG_SYNCSRC_POSE)

#define CSU_CFG_SYNCDIV_POSS    24U
#define CSU_CFG_SYNCDIV_POSE    26U
#define CSU_CFG_SYNCDIV_MSK BITS(CSU_CFG_SYNCDIV_POSS,CSU_CFG_SYNCDIV_POSE)

#define CSU_CFG_CNTTH_POSS  16U
#define CSU_CFG_CNTTH_POSE  23U
#define CSU_CFG_CNTTH_MSK   BITS(CSU_CFG_CNTTH_POSS,CSU_CFG_CNTTH_POSE)

#define CSU_CFG_RELOAD_POSS 0U
#define CSU_CFG_RELOAD_POSE 15U
#define CSU_CFG_RELOAD_MSK  BITS(CSU_CFG_RELOAD_POSS,CSU_CFG_RELOAD_POSE)

/****************** Bit definition for CSU_STAT register ************************/

#define CSU_STAT_OPT_TRIM_POSS  23U
#define CSU_STAT_OPT_TRIM_POSE  31U
#define CSU_STAT_OPT_TRIM_MSK   BITS(CSU_STAT_OPT_TRIM_POSS,CSU_STAT_OPT_TRIM_POSE)

#define CSU_STAT_CNTDIR_POS 16U
#define CSU_STAT_CNTDIR_MSK BIT(CSU_STAT_CNTDIR_POS)

#define CSU_STAT_CNTCAP_POSS    0U
#define CSU_STAT_CNTCAP_POSE    15U
#define CSU_STAT_CNTCAP_MSK BITS(CSU_STAT_CNTCAP_POSS,CSU_STAT_CNTCAP_POSE)

/****************** Bit definition for CSU_IER register ************************/

#define CSU_IER_FHIT_POS    5U
#define CSU_IER_FHIT_MSK    BIT(CSU_IER_FHIT_POS)

#define CSU_IER_TRIMERR_POS 4U
#define CSU_IER_TRIMERR_MSK BIT(CSU_IER_TRIMERR_POS)

#define CSU_IER_FFAULT_POS  3U
#define CSU_IER_FFAULT_MSK  BIT(CSU_IER_FFAULT_POS)

#define CSU_IER_FERROR_POS  2U
#define CSU_IER_FERROR_MSK  BIT(CSU_IER_FERROR_POS)

#define CSU_IER_FWARN_POS   1U
#define CSU_IER_FWARN_MSK   BIT(CSU_IER_FWARN_POS)

#define CSU_IER_FMATCH_POS  0U
#define CSU_IER_FMATCH_MSK  BIT(CSU_IER_FMATCH_POS)

/****************** Bit definition for CSU_IDR register ************************/

#define CSU_IDR_FHIT_POS    5U
#define CSU_IDR_FHIT_MSK    BIT(CSU_IDR_FHIT_POS)

#define CSU_IDR_TRIMERR_POS 4U
#define CSU_IDR_TRIMERR_MSK BIT(CSU_IDR_TRIMERR_POS)

#define CSU_IDR_FFAULT_POS  3U
#define CSU_IDR_FFAULT_MSK  BIT(CSU_IDR_FFAULT_POS)

#define CSU_IDR_FERROR_POS  2U
#define CSU_IDR_FERROR_MSK  BIT(CSU_IDR_FERROR_POS)

#define CSU_IDR_FWARN_POS   1U
#define CSU_IDR_FWARN_MSK   BIT(CSU_IDR_FWARN_POS)

#define CSU_IDR_FMATCH_POS  0U
#define CSU_IDR_FMATCH_MSK  BIT(CSU_IDR_FMATCH_POS)

/****************** Bit definition for CSU_IVS register ************************/

#define CSU_IVS_FHIT_POS    5U
#define CSU_IVS_FHIT_MSK    BIT(CSU_IVS_FHIT_POS)

#define CSU_IVS_TRIMERR_POS 4U
#define CSU_IVS_TRIMERR_MSK BIT(CSU_IVS_TRIMERR_POS)

#define CSU_IVS_FFAULT_POS  3U
#define CSU_IVS_FFAULT_MSK  BIT(CSU_IVS_FFAULT_POS)

#define CSU_IVS_FERROR_POS  2U
#define CSU_IVS_FERROR_MSK  BIT(CSU_IVS_FERROR_POS)

#define CSU_IVS_FWARN_POS   1U
#define CSU_IVS_FWARN_MSK   BIT(CSU_IVS_FWARN_POS)

#define CSU_IVS_FMATCH_POS  0U
#define CSU_IVS_FMATCH_MSK  BIT(CSU_IVS_FMATCH_POS)

/****************** Bit definition for CSU_RIF register ************************/

#define CSU_RIF_FHIT_POS    5U
#define CSU_RIF_FHIT_MSK    BIT(CSU_RIF_FHIT_POS)

#define CSU_RIF_TRIMERR_POS 4U
#define CSU_RIF_TRIMERR_MSK BIT(CSU_RIF_TRIMERR_POS)

#define CSU_RIF_FFAULT_POS  3U
#define CSU_RIF_FFAULT_MSK  BIT(CSU_RIF_FFAULT_POS)

#define CSU_RIF_FERROR_POS  2U
#define CSU_RIF_FERROR_MSK  BIT(CSU_RIF_FERROR_POS)

#define CSU_RIF_FWARN_POS   1U
#define CSU_RIF_FWARN_MSK   BIT(CSU_RIF_FWARN_POS)

#define CSU_RIF_FMATCH_POS  0U
#define CSU_RIF_FMATCH_MSK  BIT(CSU_RIF_FMATCH_POS)

/****************** Bit definition for CSU_IFM register ************************/

#define CSU_IFM_FHIT_POS    5U
#define CSU_IFM_FHIT_MSK    BIT(CSU_IFM_FHIT_POS)

#define CSU_IFM_TRIMERR_POS 4U
#define CSU_IFM_TRIMERR_MSK BIT(CSU_IFM_TRIMERR_POS)

#define CSU_IFM_FFAULT_POS  3U
#define CSU_IFM_FFAULT_MSK  BIT(CSU_IFM_FFAULT_POS)

#define CSU_IFM_FERROR_POS  2U
#define CSU_IFM_FERROR_MSK  BIT(CSU_IFM_FERROR_POS)

#define CSU_IFM_FWARN_POS   1U
#define CSU_IFM_FWARN_MSK   BIT(CSU_IFM_FWARN_POS)

#define CSU_IFM_FMATCH_POS  0U
#define CSU_IFM_FMATCH_MSK  BIT(CSU_IFM_FMATCH_POS)

/****************** Bit definition for CSU_ICR register ************************/

#define CSU_ICR_FHIT_POS    5U
#define CSU_ICR_FHIT_MSK    BIT(CSU_ICR_FHIT_POS)

#define CSU_ICR_TRIMERR_POS 4U
#define CSU_ICR_TRIMERR_MSK BIT(CSU_ICR_TRIMERR_POS)

#define CSU_ICR_FFAULT_POS  3U
#define CSU_ICR_FFAULT_MSK  BIT(CSU_ICR_FFAULT_POS)

#define CSU_ICR_FERROR_POS  2U
#define CSU_ICR_FERROR_MSK  BIT(CSU_ICR_FERROR_POS)

#define CSU_ICR_FWARN_POS   1U
#define CSU_ICR_FWARN_MSK   BIT(CSU_ICR_FWARN_POS)

#define CSU_ICR_FMATCH_POS  0U
#define CSU_ICR_FMATCH_MSK  BIT(CSU_ICR_FMATCH_POS)

typedef struct
{
    __IO uint32_t CON;
    __IO uint32_t CFG;
    __I uint32_t STAT;
    uint32_t RESERVED0 ;
    __O uint32_t IER;
    __O uint32_t IDR;
    __I uint32_t IVS;
    __I uint32_t RIF;
    __I uint32_t IFM;
    __O uint32_t ICR;
} CSU_TypeDef;





#endif /* __REG_CSU_H__ */
