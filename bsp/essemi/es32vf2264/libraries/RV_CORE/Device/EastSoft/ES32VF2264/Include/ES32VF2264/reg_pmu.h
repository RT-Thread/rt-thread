/**********************************************************************************
 *
 * @file    reg_pmu.h
 * @brief   PMU Head File
 *
 * @date    15 Dec. 2022
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          15 Dec. 2022    Lisq            the first version
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

#ifndef __REG_PMU_H__
#define __REG_PMU_H__

/****************** Bit definition for PMU_CR register ************************/

#define PMU_CR_WKEVNSEL_POSS    24U
#define PMU_CR_WKEVNSEL_POSE    28U
#define PMU_CR_WKEVNSEL_MSK BITS(PMU_CR_WKEVNSEL_POSS,PMU_CR_WKEVNSEL_POSE)

#define PMU_CR_FSTOP_POS    23U
#define PMU_CR_FSTOP_MSK    BIT(PMU_CR_FSTOP_POS)

#define PMU_CR_BGSTOP_POS   21U
#define PMU_CR_BGSTOP_MSK   BIT(PMU_CR_BGSTOP_POS)

#define PMU_CR_LPSTOP_POS   20U
#define PMU_CR_LPSTOP_MSK   BIT(PMU_CR_LPSTOP_POS)

#define PMU_CR_LPRUN_POS    19U
#define PMU_CR_LPRUN_MSK    BIT(PMU_CR_LPRUN_POS)

#define PMU_CR_LPVS_POSS    16U
#define PMU_CR_LPVS_POSE    17U
#define PMU_CR_LPVS_MSK BITS(PMU_CR_LPVS_POSS,PMU_CR_LPVS_POSE)

#define PMU_CR_VROSCEN_POS  7U
#define PMU_CR_VROSCEN_MSK  BIT(PMU_CR_VROSCEN_POS)

#define PMU_CR_NORRTNEN_POS 6U
#define PMU_CR_NORRTNEN_MSK BIT(PMU_CR_NORRTNEN_POS)

#define PMU_CR_STPRTNEN_POS 5U
#define PMU_CR_STPRTNEN_MSK BIT(PMU_CR_STPRTNEN_POS)

#define PMU_CR_CWUF_POS 2U
#define PMU_CR_CWUF_MSK BIT(PMU_CR_CWUF_POS)

#define PMU_CR_LPM_POSS 0U
#define PMU_CR_LPM_POSE 1U
#define PMU_CR_LPM_MSK  BITS(PMU_CR_LPM_POSS,PMU_CR_LPM_POSE)

/****************** Bit definition for PMU_SR register ************************/

#define PMU_SR_WUF_POS  0U
#define PMU_SR_WUF_MSK  BIT(PMU_SR_WUF_POS)

/****************** Bit definition for PMU_LVDCR register ************************/

#define PMU_LVDCR_LVDO_POS  15U
#define PMU_LVDCR_LVDO_MSK  BIT(PMU_LVDCR_LVDO_POS)

#define PMU_LVDCR_LVDFLT_POS    11U
#define PMU_LVDCR_LVDFLT_MSK    BIT(PMU_LVDCR_LVDFLT_POS)

#define PMU_LVDCR_LVDIFS_POSS   8U
#define PMU_LVDCR_LVDIFS_POSE   10U
#define PMU_LVDCR_LVDIFS_MSK    BITS(PMU_LVDCR_LVDIFS_POSS,PMU_LVDCR_LVDIFS_POSE)

#define PMU_LVDCR_LVDS_POSS 4U
#define PMU_LVDCR_LVDS_POSE 7U
#define PMU_LVDCR_LVDS_MSK  BITS(PMU_LVDCR_LVDS_POSS,PMU_LVDCR_LVDS_POSE)

#define PMU_LVDCR_LVDCIF_POS    3U
#define PMU_LVDCR_LVDCIF_MSK    BIT(PMU_LVDCR_LVDCIF_POS)

#define PMU_LVDCR_LVDIF_POS 2U
#define PMU_LVDCR_LVDIF_MSK BIT(PMU_LVDCR_LVDIF_POS)

#define PMU_LVDCR_LVDIE_POS 1U
#define PMU_LVDCR_LVDIE_MSK BIT(PMU_LVDCR_LVDIE_POS)

#define PMU_LVDCR_LVDEN_POS 0U
#define PMU_LVDCR_LVDEN_MSK BIT(PMU_LVDCR_LVDEN_POS)

/****************** Bit definition for PMU_TWUR register ************************/

#define PMU_TWUR_TWU_POSS   0U
#define PMU_TWUR_TWU_POSE   11U
#define PMU_TWUR_TWU_MSK    BITS(PMU_TWUR_TWU_POSS,PMU_TWUR_TWU_POSE)

typedef struct
{
    __IO uint32_t CR;
    __I uint32_t SR;
    __IO uint32_t LVDCR;
    uint32_t RESERVED0 ;
    __IO uint32_t TWUR;
} PMU_TypeDef;





#endif /* __REG_PMU_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
