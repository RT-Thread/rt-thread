/**********************************************************************************
 *
 * @file    reg_adc.h
 * @brief   ADC Head File
 *
 * @date    26 Dec. 2022
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          26 Dec. 2022    Lisq            the first version
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

#ifndef __REG_ADC_H__
#define __REG_ADC_H__

/****************** Bit definition for ADC_STAT register ************************/

#define ADC_STAT_ICHS_POS   9U
#define ADC_STAT_ICHS_MSK   BIT(ADC_STAT_ICHS_POS)

#define ADC_STAT_NCHS_POS   8U
#define ADC_STAT_NCHS_MSK   BIT(ADC_STAT_NCHS_POS)

#define ADC_STAT_OVR_POS    3U
#define ADC_STAT_OVR_MSK    BIT(ADC_STAT_OVR_POS)

#define ADC_STAT_ICHE_POS   2U
#define ADC_STAT_ICHE_MSK   BIT(ADC_STAT_ICHE_POS)

#define ADC_STAT_NCHE_POS   1U
#define ADC_STAT_NCHE_MSK   BIT(ADC_STAT_NCHE_POS)

#define ADC_STAT_AWDF_POS   0U
#define ADC_STAT_AWDF_MSK   BIT(ADC_STAT_AWDF_POS)

/****************** Bit definition for ADC_CLR register ************************/

#define ADC_CLR_ICHS_POS    9U
#define ADC_CLR_ICHS_MSK    BIT(ADC_CLR_ICHS_POS)

#define ADC_CLR_NCHS_POS    8U
#define ADC_CLR_NCHS_MSK    BIT(ADC_CLR_NCHS_POS)

#define ADC_CLR_OVR_POS 3U
#define ADC_CLR_OVR_MSK BIT(ADC_CLR_OVR_POS)

#define ADC_CLR_ICHE_POS    2U
#define ADC_CLR_ICHE_MSK    BIT(ADC_CLR_ICHE_POS)

#define ADC_CLR_NCHE_POS    1U
#define ADC_CLR_NCHE_MSK    BIT(ADC_CLR_NCHE_POS)

#define ADC_CLR_AWDF_POS    0U
#define ADC_CLR_AWDF_MSK    BIT(ADC_CLR_AWDF_POS)

/****************** Bit definition for ADC_CON0 register ************************/

#define ADC_CON0_OVRIE_POS  26U
#define ADC_CON0_OVRIE_MSK  BIT(ADC_CON0_OVRIE_POS)

#define ADC_CON0_RSEL_POSS  24U
#define ADC_CON0_RSEL_POSE  25U
#define ADC_CON0_RSEL_MSK   BITS(ADC_CON0_RSEL_POSS,ADC_CON0_RSEL_POSE)

#define ADC_CON0_NCHWDEN_POS    23U
#define ADC_CON0_NCHWDEN_MSK    BIT(ADC_CON0_NCHWDEN_POS)

#define ADC_CON0_ICHWDTEN_POS   22U
#define ADC_CON0_ICHWDTEN_MSK   BIT(ADC_CON0_ICHWDTEN_POS)

#define ADC_CON0_CNTW_POSS  16U
#define ADC_CON0_CNTW_POSE  18U
#define ADC_CON0_CNTW_MSK   BITS(ADC_CON0_CNTW_POSS,ADC_CON0_CNTW_POSE)

#define ADC_CON0_ETRGN_POSS 13U
#define ADC_CON0_ETRGN_POSE 15U
#define ADC_CON0_ETRGN_MSK  BITS(ADC_CON0_ETRGN_POSS,ADC_CON0_ETRGN_POSE)

#define ADC_CON0_ICHDCEN_POS    12U
#define ADC_CON0_ICHDCEN_MSK    BIT(ADC_CON0_ICHDCEN_POS)

#define ADC_CON0_NCHDCEN_POS    11U
#define ADC_CON0_NCHDCEN_MSK    BIT(ADC_CON0_NCHDCEN_POS)

#define ADC_CON0_IAUTO_POS  10U
#define ADC_CON0_IAUTO_MSK  BIT(ADC_CON0_IAUTO_POS)

#define ADC_CON0_AWDSGL_POS 9U
#define ADC_CON0_AWDSGL_MSK BIT(ADC_CON0_AWDSGL_POS)

#define ADC_CON0_SCANEN_POS 8U
#define ADC_CON0_SCANEN_MSK BIT(ADC_CON0_SCANEN_POS)

#define ADC_CON0_ICHEIE_POS 7U
#define ADC_CON0_ICHEIE_MSK BIT(ADC_CON0_ICHEIE_POS)

#define ADC_CON0_AWDIE_POS  6U
#define ADC_CON0_AWDIE_MSK  BIT(ADC_CON0_AWDIE_POS)

#define ADC_CON0_NCHEIE_POS 5U
#define ADC_CON0_NCHEIE_MSK BIT(ADC_CON0_NCHEIE_POS)

#define ADC_CON0_AWDCH_POSS 0U
#define ADC_CON0_AWDCH_POSE 4U
#define ADC_CON0_AWDCH_MSK  BITS(ADC_CON0_AWDCH_POSS,ADC_CON0_AWDCH_POSE)

/****************** Bit definition for ADC_CON1 register ************************/

#define ADC_CON1_NCHTRG_POS 30U
#define ADC_CON1_NCHTRG_MSK BIT(ADC_CON1_NCHTRG_POS)

#define ADC_CON1_NETS_POSS  28U
#define ADC_CON1_NETS_POSE  29U
#define ADC_CON1_NETS_MSK   BITS(ADC_CON1_NETS_POSS,ADC_CON1_NETS_POSE)

#define ADC_CON1_ICHTRG_POS 22U
#define ADC_CON1_ICHTRG_MSK BIT(ADC_CON1_ICHTRG_POS)

#define ADC_CON1_IETS_POSS  20U
#define ADC_CON1_IETS_POSE  21U
#define ADC_CON1_IETS_MSK   BITS(ADC_CON1_IETS_POSS,ADC_CON1_IETS_POSE)

#define ADC_CON1_ALIGN_POS  11U
#define ADC_CON1_ALIGN_MSK  BIT(ADC_CON1_ALIGN_POS)

#define ADC_CON1_NCHESEL_POS    10U
#define ADC_CON1_NCHESEL_MSK    BIT(ADC_CON1_NCHESEL_POS)

#define ADC_CON1_DMA_POS    8U
#define ADC_CON1_DMA_MSK    BIT(ADC_CON1_DMA_POS)

#define ADC_CON1_CM_POS 1U
#define ADC_CON1_CM_MSK BIT(ADC_CON1_CM_POS)

#define ADC_CON1_ADCEN_POS  0U
#define ADC_CON1_ADCEN_MSK  BIT(ADC_CON1_ADCEN_POS)

/****************** Bit definition for ADC_SMPT1 register ************************/

#define ADC_SMPT1_CHT_POSS  0U
#define ADC_SMPT1_CHT_POSE  31U
#define ADC_SMPT1_CHT_MSK   BITS(ADC_SMPT1_CHT_POSS,ADC_SMPT1_CHT_POSE)

/****************** Bit definition for ADC_SMPT2 register ************************/

#define ADC_SMPT2_CHT_POSS  0U
#define ADC_SMPT2_CHT_POSE  31U
#define ADC_SMPT2_CHT_MSK   BITS(ADC_SMPT2_CHT_POSS,ADC_SMPT2_CHT_POSE)

/****************** Bit definition for ADC_SMPT3 register ************************/

#define ADC_SMPT3_SMP_POSS  0U
#define ADC_SMPT3_SMP_POSE  31U
#define ADC_SMPT3_SMP_MSK   BITS(ADC_SMPT3_SMP_POSS,ADC_SMPT3_SMP_POSE)

/****************** Bit definition for ADC_NCHOFF register ************************/

#define ADC_NCHOFF_NOFF_POSS    0U
#define ADC_NCHOFF_NOFF_POSE    11U
#define ADC_NCHOFF_NOFF_MSK BITS(ADC_NCHOFF_NOFF_POSS,ADC_NCHOFF_NOFF_POSE)

/****************** Bit definition for ADC_ICHOFF1 register ************************/

#define ADC_ICHOFF1_IOFF1_POSS  0U
#define ADC_ICHOFF1_IOFF1_POSE  11U
#define ADC_ICHOFF1_IOFF1_MSK   BITS(ADC_ICHOFF1_IOFF1_POSS,ADC_ICHOFF1_IOFF1_POSE)

/****************** Bit definition for ADC_ICHOFF2 register ************************/

#define ADC_ICHOFF2_IOFF2_POSS  0U
#define ADC_ICHOFF2_IOFF2_POSE  11U
#define ADC_ICHOFF2_IOFF2_MSK   BITS(ADC_ICHOFF2_IOFF2_POSS,ADC_ICHOFF2_IOFF2_POSE)

/****************** Bit definition for ADC_ICHOFF3 register ************************/

#define ADC_ICHOFF3_IOFF3_POSS  0U
#define ADC_ICHOFF3_IOFF3_POSE  11U
#define ADC_ICHOFF3_IOFF3_MSK   BITS(ADC_ICHOFF3_IOFF3_POSS,ADC_ICHOFF3_IOFF3_POSE)

/****************** Bit definition for ADC_ICHOFF4 register ************************/

#define ADC_ICHOFF4_IOFF4_POSS  0U
#define ADC_ICHOFF4_IOFF4_POSE  11U
#define ADC_ICHOFF4_IOFF4_MSK   BITS(ADC_ICHOFF4_IOFF4_POSS,ADC_ICHOFF4_IOFF4_POSE)

/****************** Bit definition for ADC_NCHS1 register ************************/

#define ADC_NCHS1_NS4_POSS  24U
#define ADC_NCHS1_NS4_POSE  28U
#define ADC_NCHS1_NS4_MSK   BITS(ADC_NCHS1_NS4_POSS,ADC_NCHS1_NS4_POSE)

#define ADC_NCHS1_NS3_POSS  16U
#define ADC_NCHS1_NS3_POSE  20U
#define ADC_NCHS1_NS3_MSK   BITS(ADC_NCHS1_NS3_POSS,ADC_NCHS1_NS3_POSE)

#define ADC_NCHS1_NS2_POSS  8U
#define ADC_NCHS1_NS2_POSE  12U
#define ADC_NCHS1_NS2_MSK   BITS(ADC_NCHS1_NS2_POSS,ADC_NCHS1_NS2_POSE)

#define ADC_NCHS1_NS1_POSS  0U
#define ADC_NCHS1_NS1_POSE  4U
#define ADC_NCHS1_NS1_MSK   BITS(ADC_NCHS1_NS1_POSS,ADC_NCHS1_NS1_POSE)

/****************** Bit definition for ADC_NCHS2 register ************************/

#define ADC_NCHS2_NS8_POSS  24U
#define ADC_NCHS2_NS8_POSE  28U
#define ADC_NCHS2_NS8_MSK   BITS(ADC_NCHS2_NS8_POSS,ADC_NCHS2_NS8_POSE)

#define ADC_NCHS2_NS7_POSS  16U
#define ADC_NCHS2_NS7_POSE  20U
#define ADC_NCHS2_NS7_MSK   BITS(ADC_NCHS2_NS7_POSS,ADC_NCHS2_NS7_POSE)

#define ADC_NCHS2_NS6_POSS  8U
#define ADC_NCHS2_NS6_POSE  12U
#define ADC_NCHS2_NS6_MSK   BITS(ADC_NCHS2_NS6_POSS,ADC_NCHS2_NS6_POSE)

#define ADC_NCHS2_NS5_POSS  0U
#define ADC_NCHS2_NS5_POSE  4U
#define ADC_NCHS2_NS5_MSK   BITS(ADC_NCHS2_NS5_POSS,ADC_NCHS2_NS5_POSE)

/****************** Bit definition for ADC_NCHS3 register ************************/

#define ADC_NCHS3_NS12_POSS 24U
#define ADC_NCHS3_NS12_POSE 28U
#define ADC_NCHS3_NS12_MSK  BITS(ADC_NCHS3_NS12_POSS,ADC_NCHS3_NS12_POSE)

#define ADC_NCHS3_NS11_POSS 16U
#define ADC_NCHS3_NS11_POSE 20U
#define ADC_NCHS3_NS11_MSK  BITS(ADC_NCHS3_NS11_POSS,ADC_NCHS3_NS11_POSE)

#define ADC_NCHS3_NS10_POSS 8U
#define ADC_NCHS3_NS10_POSE 12U
#define ADC_NCHS3_NS10_MSK  BITS(ADC_NCHS3_NS10_POSS,ADC_NCHS3_NS10_POSE)

#define ADC_NCHS3_NS9_POSS  0U
#define ADC_NCHS3_NS9_POSE  4U
#define ADC_NCHS3_NS9_MSK   BITS(ADC_NCHS3_NS9_POSS,ADC_NCHS3_NS9_POSE)

/****************** Bit definition for ADC_NCHS4 register ************************/

#define ADC_NCHS4_NS16_POSS 24U
#define ADC_NCHS4_NS16_POSE 28U
#define ADC_NCHS4_NS16_MSK  BITS(ADC_NCHS4_NS16_POSS,ADC_NCHS4_NS16_POSE)

#define ADC_NCHS4_NS15_POSS 16U
#define ADC_NCHS4_NS15_POSE 20U
#define ADC_NCHS4_NS15_MSK  BITS(ADC_NCHS4_NS15_POSS,ADC_NCHS4_NS15_POSE)

#define ADC_NCHS4_NS14_POSS 8U
#define ADC_NCHS4_NS14_POSE 12U
#define ADC_NCHS4_NS14_MSK  BITS(ADC_NCHS4_NS14_POSS,ADC_NCHS4_NS14_POSE)

#define ADC_NCHS4_NS13_POSS 0U
#define ADC_NCHS4_NS13_POSE 4U
#define ADC_NCHS4_NS13_MSK  BITS(ADC_NCHS4_NS13_POSS,ADC_NCHS4_NS13_POSE)

/****************** Bit definition for ADC_ICHS register ************************/

#define ADC_ICHS_IS4_POSS   24U
#define ADC_ICHS_IS4_POSE   28U
#define ADC_ICHS_IS4_MSK    BITS(ADC_ICHS_IS4_POSS,ADC_ICHS_IS4_POSE)

#define ADC_ICHS_IS3_POSS   16U
#define ADC_ICHS_IS3_POSE   20U
#define ADC_ICHS_IS3_MSK    BITS(ADC_ICHS_IS3_POSS,ADC_ICHS_IS3_POSE)

#define ADC_ICHS_IS2_POSS   8U
#define ADC_ICHS_IS2_POSE   12U
#define ADC_ICHS_IS2_MSK    BITS(ADC_ICHS_IS2_POSS,ADC_ICHS_IS2_POSE)

#define ADC_ICHS_IS1_POSS   0U
#define ADC_ICHS_IS1_POSE   4U
#define ADC_ICHS_IS1_MSK    BITS(ADC_ICHS_IS1_POSS,ADC_ICHS_IS1_POSE)

/****************** Bit definition for ADC_CHSL register ************************/

#define ADC_CHSL_ISL_POSS   8U
#define ADC_CHSL_ISL_POSE   9U
#define ADC_CHSL_ISL_MSK    BITS(ADC_CHSL_ISL_POSS,ADC_CHSL_ISL_POSE)

#define ADC_CHSL_NSL_POSS   0U
#define ADC_CHSL_NSL_POSE   3U
#define ADC_CHSL_NSL_MSK    BITS(ADC_CHSL_NSL_POSS,ADC_CHSL_NSL_POSE)

/****************** Bit definition for ADC_WDTH register ************************/

#define ADC_WDTH_HT_POSS    0U
#define ADC_WDTH_HT_POSE    11U
#define ADC_WDTH_HT_MSK BITS(ADC_WDTH_HT_POSS,ADC_WDTH_HT_POSE)

/****************** Bit definition for ADC_WDTL register ************************/

#define ADC_WDTL_LT_POSS    0U
#define ADC_WDTL_LT_POSE    11U
#define ADC_WDTL_LT_MSK BITS(ADC_WDTL_LT_POSS,ADC_WDTL_LT_POSE)

/****************** Bit definition for ADC_ICHDR1 register ************************/

#define ADC_ICHDR1_VAL_POSS 0U
#define ADC_ICHDR1_VAL_POSE 15U
#define ADC_ICHDR1_VAL_MSK  BITS(ADC_ICHDR1_VAL_POSS,ADC_ICHDR1_VAL_POSE)

/****************** Bit definition for ADC_ICHDR2 register ************************/

#define ADC_ICHDR2_VAL_POSS 0U
#define ADC_ICHDR2_VAL_POSE 15U
#define ADC_ICHDR2_VAL_MSK  BITS(ADC_ICHDR2_VAL_POSS,ADC_ICHDR2_VAL_POSE)

/****************** Bit definition for ADC_ICHDR3 register ************************/

#define ADC_ICHDR3_VAL_POSS 0U
#define ADC_ICHDR3_VAL_POSE 15U
#define ADC_ICHDR3_VAL_MSK  BITS(ADC_ICHDR3_VAL_POSS,ADC_ICHDR3_VAL_POSE)

/****************** Bit definition for ADC_ICHDR4 register ************************/

#define ADC_ICHDR4_VAL_POSS 0U
#define ADC_ICHDR4_VAL_POSE 15U
#define ADC_ICHDR4_VAL_MSK  BITS(ADC_ICHDR4_VAL_POSS,ADC_ICHDR4_VAL_POSE)

/****************** Bit definition for ADC_NCHDR register ************************/

#define ADC_NCHDR_VAL_POSS  0U
#define ADC_NCHDR_VAL_POSE  15U
#define ADC_NCHDR_VAL_MSK   BITS(ADC_NCHDR_VAL_POSS,ADC_NCHDR_VAL_POSE)

/****************** Bit definition for ADC_CCR register ************************/

#define ADC_CCR_CALZERO_POS 29U
#define ADC_CCR_CALZERO_MSK BIT(ADC_CCR_CALZERO_POS)

#define ADC_CCR_TRMEN_POS   28U
#define ADC_CCR_TRMEN_MSK   BIT(ADC_CCR_TRMEN_POS)

#define ADC_CCR_TSEN_POS    20U
#define ADC_CCR_TSEN_MSK    BIT(ADC_CCR_TSEN_POS)

#define ADC_CCR_VRNSEL_POS  18U
#define ADC_CCR_VRNSEL_MSK  BIT(ADC_CCR_VRNSEL_POS)

#define ADC_CCR_VRPSEL_POS  17U
#define ADC_CCR_VRPSEL_MSK  BIT(ADC_CCR_VRPSEL_POS)

#define ADC_CCR_PWRMODSEL_POS   15U
#define ADC_CCR_PWRMODSEL_MSK   BIT(ADC_CCR_PWRMODSEL_POS)

#define ADC_CCR_IREFEN_POS  11U
#define ADC_CCR_IREFEN_MSK  BIT(ADC_CCR_IREFEN_POS)

#define ADC_CCR_VREFEN_POS  8U
#define ADC_CCR_VREFEN_MSK  BIT(ADC_CCR_VREFEN_POS)

#define ADC_CCR_PREDIV_POS  3U
#define ADC_CCR_PREDIV_MSK  BIT(ADC_CCR_PREDIV_POS)

#define ADC_CCR_POSDIV_POSS 0U
#define ADC_CCR_POSDIV_POSE 2U
#define ADC_CCR_POSDIV_MSK  BITS(ADC_CCR_POSDIV_POSS,ADC_CCR_POSDIV_POSE)

typedef struct
{
    __I uint32_t STAT;
    __O uint32_t CLR;
    __IO uint32_t CON0;
    __IO uint32_t CON1;
    __IO uint32_t SMPT1;
    __IO uint32_t SMPT2;
    __IO uint32_t SMPT3;
    __IO uint32_t NCHOFF;
    __IO uint32_t ICHOFF1;
    __IO uint32_t ICHOFF2;
    __IO uint32_t ICHOFF3;
    __IO uint32_t ICHOFF4;
    __IO uint32_t NCHS1;
    __IO uint32_t NCHS2;
    __IO uint32_t NCHS3;
    __IO uint32_t NCHS4;
    __IO uint32_t ICHS;
    __IO uint32_t CHSL;
    __IO uint32_t WDTH;
    __IO uint32_t WDTL;
    __I uint32_t ICHDR1;
    __I uint32_t ICHDR2;
    __I uint32_t ICHDR3;
    __I uint32_t ICHDR4;
    __I uint32_t NCHDR;
    __IO uint32_t CCR;
} ADC_TypeDef;





#endif /* __REG_ADC_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
