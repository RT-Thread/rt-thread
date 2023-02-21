/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef __MM32F3277G_FEATURES_H__
#define __MM32F3277G_FEATURES_H__

#include "mm32f3277g.h"

/*!
 * @brief TIM_ADV_Type.
 */
#define TIM_ADV_Type TIM1_Type /*!< TIM ADV Module Register set referring to TIM1. */

/*!
 * @brief TIM_16B_Type.
 */
#define TIM_16B_Type TIM3_Type /*!< TIM 16B Module Register set referring to TIM3. */

/*!
 * @brief TIM_32B_Type.
 */
#define TIM_32B_Type TIM2_Type /*!< TIM 32B Module Register set referring to TIM2. */

/*!
 * @brief TIM_BASIC_Type.
 */
#define TIM_BASIC_Type TIM6_Type /*!< TIM BASIC Module Register set referring to TIM6. */

/*******************************************************************************
 * TIM_ADV Type
 ******************************************************************************/

/*!
 * @addtogroup TIM_ADV_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief TIM_ADV_CR1 Register Bit Definition
 */

#define TIM_ADV_CR1_CKD_SHIFT                      TIM1_CR1_CKD_SHIFT
#define TIM_ADV_CR1_CKD_MASK                       TIM1_CR1_CKD_MASK
#define TIM_ADV_CR1_CKD(x)                         TIM1_CR1_CKD(x)

#define TIM_ADV_CR1_APRE_SHIFT                     TIM1_CR1_APRE_SHIFT
#define TIM_ADV_CR1_APRE_MASK                      TIM1_CR1_APRE_MASK
#define TIM_ADV_CR1_APRE(x)                        TIM1_CR1_APRE(x)

#define TIM_ADV_CR1_CMS_SHIFT                      TIM1_CR1_CMS_SHIFT
#define TIM_ADV_CR1_CMS_MASK                       TIM1_CR1_CMS_MASK
#define TIM_ADV_CR1_CMS(x)                         TIM1_CR1_CMS(x)

#define TIM_ADV_CR1_DIR_SHIFT                      TIM1_CR1_DIR_SHIFT
#define TIM_ADV_CR1_DIR_MASK                       TIM1_CR1_DIR_MASK
#define TIM_ADV_CR1_DIR(x)                         TIM1_CR1_DIR(x)

#define TIM_ADV_CR1_OPM_SHIFT                      TIM1_CR1_OPM_SHIFT
#define TIM_ADV_CR1_OPM_MASK                       TIM1_CR1_OPM_MASK
#define TIM_ADV_CR1_OPM(x)                         TIM1_CR1_OPM(x)

#define TIM_ADV_CR1_URS_SHIFT                      TIM1_CR1_URS_SHIFT
#define TIM_ADV_CR1_URS_MASK                       TIM1_CR1_URS_MASK
#define TIM_ADV_CR1_URS(x)                         TIM1_CR1_URS(x)

#define TIM_ADV_CR1_UDIS_SHIFT                     TIM1_CR1_UDIS_SHIFT
#define TIM_ADV_CR1_UDIS_MASK                      TIM1_CR1_UDIS_MASK
#define TIM_ADV_CR1_UDIS(x)                        TIM1_CR1_UDIS(x)

#define TIM_ADV_CR1_CEN_SHIFT                      TIM1_CR1_CEN_SHIFT
#define TIM_ADV_CR1_CEN_MASK                       TIM1_CR1_CEN_MASK
#define TIM_ADV_CR1_CEN(x)                         TIM1_CR1_CEN(x)

/*!
 * @brief TIM_ADV_CR2 Register Bit Definition
 */

#define TIM_ADV_CR2_OIS4_SHIFT                     TIM1_CR2_OIS4_SHIFT
#define TIM_ADV_CR2_OIS4_MASK                      TIM1_CR2_OIS4_MASK
#define TIM_ADV_CR2_OIS4(x)                        TIM1_CR2_OIS4(x)

#define TIM_ADV_CR2_OIS3N_SHIFT                    TIM1_CR2_OIS3N_SHIFT
#define TIM_ADV_CR2_OIS3N_MASK                     TIM1_CR2_OIS3N_MASK
#define TIM_ADV_CR2_OIS3N(x)                       TIM1_CR2_OIS3N(x)

#define TIM_ADV_CR2_OIS3_SHIFT                     TIM1_CR2_OIS3_SHIFT
#define TIM_ADV_CR2_OIS3_MASK                      TIM1_CR2_OIS3_MASK
#define TIM_ADV_CR2_OIS3(x)                        TIM1_CR2_OIS3(x)

#define TIM_ADV_CR2_OIS2N_SHIFT                    TIM1_CR2_OIS2N_SHIFT
#define TIM_ADV_CR2_OIS2N_MASK                     TIM1_CR2_OIS2N_MASK
#define TIM_ADV_CR2_OIS2N(x)                       TIM1_CR2_OIS2N(x)

#define TIM_ADV_CR2_OIS2_SHIFT                     TIM1_CR2_OIS2_SHIFT
#define TIM_ADV_CR2_OIS2_MASK                      TIM1_CR2_OIS2_MASK
#define TIM_ADV_CR2_OIS2(x)                        TIM1_CR2_OIS2(x)

#define TIM_ADV_CR2_OIS1N_SHIFT                    TIM1_CR2_OIS1N_SHIFT
#define TIM_ADV_CR2_OIS1N_MASK                     TIM1_CR2_OIS1N_MASK
#define TIM_ADV_CR2_OIS1N(x)                       TIM1_CR2_OIS1N(x)

#define TIM_ADV_CR2_OIS1_SHIFT                     TIM1_CR2_OIS1_SHIFT
#define TIM_ADV_CR2_OIS1_MASK                      TIM1_CR2_OIS1_MASK
#define TIM_ADV_CR2_OIS1(x)                        TIM1_CR2_OIS1(x)

#define TIM_ADV_CR2_TI1S_SHIFT                     TIM1_CR2_TI1S_SHIFT
#define TIM_ADV_CR2_TI1S_MASK                      TIM1_CR2_TI1S_MASK
#define TIM_ADV_CR2_TI1S(x)                        TIM1_CR2_TI1S(x)

#define TIM_ADV_CR2_MMS_SHIFT                      TIM1_CR2_MMS_SHIFT
#define TIM_ADV_CR2_MMS_MASK                       TIM1_CR2_MMS_MASK
#define TIM_ADV_CR2_MMS(x)                         TIM1_CR2_MMS(x)

#define TIM_ADV_CR2_CCDS_SHIFT                     TIM1_CR2_CCDS_SHIFT
#define TIM_ADV_CR2_CCDS_MASK                      TIM1_CR2_CCDS_MASK
#define TIM_ADV_CR2_CCDS(x)                        TIM1_CR2_CCDS(x)

#define TIM_ADV_CR2_CCUS_SHIFT                     TIM1_CR2_CCUS_SHIFT
#define TIM_ADV_CR2_CCUS_MASK                      TIM1_CR2_CCUS_MASK
#define TIM_ADV_CR2_CCUS(x)                        TIM1_CR2_CCUS(x)

#define TIM_ADV_CR2_CCPC_SHIFT                     TIM1_CR2_CCPC_SHIFT
#define TIM_ADV_CR2_CCPC_MASK                      TIM1_CR2_CCPC_MASK
#define TIM_ADV_CR2_CCPC(x)                        TIM1_CR2_CCPC(x)

/*!
 * @brief TIM_ADV_SMCR Register Bit Definition
 */

#define TIM_ADV_SMCR_ETP_SHIFT                     TIM1_SMCR_ETP_SHIFT
#define TIM_ADV_SMCR_ETP_MASK                      TIM1_SMCR_ETP_MASK
#define TIM_ADV_SMCR_ETP(x)                        TIM1_SMCR_ETP(x)

#define TIM_ADV_SMCR_ECE_SHIFT                     TIM1_SMCR_ECE_SHIFT
#define TIM_ADV_SMCR_ECE_MASK                      TIM1_SMCR_ECE_MASK
#define TIM_ADV_SMCR_ECE(x)                        TIM1_SMCR_ECE(x)

#define TIM_ADV_SMCR_ETPS_SHIFT                    TIM1_SMCR_ETPS_SHIFT
#define TIM_ADV_SMCR_ETPS_MASK                     TIM1_SMCR_ETPS_MASK
#define TIM_ADV_SMCR_ETPS(x)                       TIM1_SMCR_ETPS(x)

#define TIM_ADV_SMCR_ETF_SHIFT                     TIM1_SMCR_ETF_SHIFT
#define TIM_ADV_SMCR_ETF_MASK                      TIM1_SMCR_ETF_MASK
#define TIM_ADV_SMCR_ETF(x)                        TIM1_SMCR_ETF(x)

#define TIM_ADV_SMCR_MSM_SHIFT                     TIM1_SMCR_MSM_SHIFT
#define TIM_ADV_SMCR_MSM_MASK                      TIM1_SMCR_MSM_MASK
#define TIM_ADV_SMCR_MSM(x)                        TIM1_SMCR_MSM(x)

#define TIM_ADV_SMCR_TS_SHIFT                      TIM1_SMCR_TS_SHIFT
#define TIM_ADV_SMCR_TS_MASK                       TIM1_SMCR_TS_MASK
#define TIM_ADV_SMCR_TS(x)                         TIM1_SMCR_TS(x)

#define TIM_ADV_SMCR_OCCS_SHIFT                    TIM1_SMCR_OCCS_SHIFT
#define TIM_ADV_SMCR_OCCS_MASK                     TIM1_SMCR_OCCS_MASK
#define TIM_ADV_SMCR_OCCS(x)                       TIM1_SMCR_OCCS(x)

#define TIM_ADV_SMCR_SMS_SHIFT                     TIM1_SMCR_SMS_SHIFT
#define TIM_ADV_SMCR_SMS_MASK                      TIM1_SMCR_SMS_MASK
#define TIM_ADV_SMCR_SMS(x)                        TIM1_SMCR_SMS(x)

/*!
 * @brief TIM_ADV_DIER Register Bit Definition
 */

#define TIM_ADV_DIER_CC5DE_SHIFT                   TIM1_DIER_CC5DE_SHIFT
#define TIM_ADV_DIER_CC5DE_MASK                    TIM1_DIER_CC5DE_MASK
#define TIM_ADV_DIER_CC5DE(x)                      TIM1_DIER_CC5DE(x)

#define TIM_ADV_DIER_CC5IE_SHIFT                   TIM1_DIER_CC5IE_SHIFT
#define TIM_ADV_DIER_CC5IE_MASK                    TIM1_DIER_CC5IE_MASK
#define TIM_ADV_DIER_CC5IE(x)                      TIM1_DIER_CC5IE(x)

#define TIM_ADV_DIER_TDE_SHIFT                     TIM1_DIER_TDE_SHIFT
#define TIM_ADV_DIER_TDE_MASK                      TIM1_DIER_TDE_MASK
#define TIM_ADV_DIER_TDE(x)                        TIM1_DIER_TDE(x)

#define TIM_ADV_DIER_COMDE_SHIFT                   TIM1_DIER_COMDE_SHIFT
#define TIM_ADV_DIER_COMDE_MASK                    TIM1_DIER_COMDE_MASK
#define TIM_ADV_DIER_COMDE(x)                      TIM1_DIER_COMDE(x)

#define TIM_ADV_DIER_CC4DE_SHIFT                   TIM1_DIER_CC4DE_SHIFT
#define TIM_ADV_DIER_CC4DE_MASK                    TIM1_DIER_CC4DE_MASK
#define TIM_ADV_DIER_CC4DE(x)                      TIM1_DIER_CC4DE(x)

#define TIM_ADV_DIER_CC3DE_SHIFT                   TIM1_DIER_CC3DE_SHIFT
#define TIM_ADV_DIER_CC3DE_MASK                    TIM1_DIER_CC3DE_MASK
#define TIM_ADV_DIER_CC3DE(x)                      TIM1_DIER_CC3DE(x)

#define TIM_ADV_DIER_CC2DE_SHIFT                   TIM1_DIER_CC2DE_SHIFT
#define TIM_ADV_DIER_CC2DE_MASK                    TIM1_DIER_CC2DE_MASK
#define TIM_ADV_DIER_CC2DE(x)                      TIM1_DIER_CC2DE(x)

#define TIM_ADV_DIER_CC1DE_SHIFT                   TIM1_DIER_CC1DE_SHIFT
#define TIM_ADV_DIER_CC1DE_MASK                    TIM1_DIER_CC1DE_MASK
#define TIM_ADV_DIER_CC1DE(x)                      TIM1_DIER_CC1DE(x)

#define TIM_ADV_DIER_UDE_SHIFT                     TIM1_DIER_UDE_SHIFT
#define TIM_ADV_DIER_UDE_MASK                      TIM1_DIER_UDE_MASK
#define TIM_ADV_DIER_UDE(x)                        TIM1_DIER_UDE(x)

#define TIM_ADV_DIER_BIE_SHIFT                     TIM1_DIER_BIE_SHIFT
#define TIM_ADV_DIER_BIE_MASK                      TIM1_DIER_BIE_MASK
#define TIM_ADV_DIER_BIE(x)                        TIM1_DIER_BIE(x)

#define TIM_ADV_DIER_TIE_SHIFT                     TIM1_DIER_TIE_SHIFT
#define TIM_ADV_DIER_TIE_MASK                      TIM1_DIER_TIE_MASK
#define TIM_ADV_DIER_TIE(x)                        TIM1_DIER_TIE(x)

#define TIM_ADV_DIER_COMIE_SHIFT                   TIM1_DIER_COMIE_SHIFT
#define TIM_ADV_DIER_COMIE_MASK                    TIM1_DIER_COMIE_MASK
#define TIM_ADV_DIER_COMIE(x)                      TIM1_DIER_COMIE(x)

#define TIM_ADV_DIER_CC4IE_SHIFT                   TIM1_DIER_CC4IE_SHIFT
#define TIM_ADV_DIER_CC4IE_MASK                    TIM1_DIER_CC4IE_MASK
#define TIM_ADV_DIER_CC4IE(x)                      TIM1_DIER_CC4IE(x)

#define TIM_ADV_DIER_CC3IE_SHIFT                   TIM1_DIER_CC3IE_SHIFT
#define TIM_ADV_DIER_CC3IE_MASK                    TIM1_DIER_CC3IE_MASK
#define TIM_ADV_DIER_CC3IE(x)                      TIM1_DIER_CC3IE(x)

#define TIM_ADV_DIER_CC2IE_SHIFT                   TIM1_DIER_CC2IE_SHIFT
#define TIM_ADV_DIER_CC2IE_MASK                    TIM1_DIER_CC2IE_MASK
#define TIM_ADV_DIER_CC2IE(x)                      TIM1_DIER_CC2IE(x)

#define TIM_ADV_DIER_CC1IE_SHIFT                   TIM1_DIER_CC1IE_SHIFT
#define TIM_ADV_DIER_CC1IE_MASK                    TIM1_DIER_CC1IE_MASK
#define TIM_ADV_DIER_CC1IE(x)                      TIM1_DIER_CC1IE(x)

#define TIM_ADV_DIER_UIE_SHIFT                     TIM1_DIER_UIE_SHIFT
#define TIM_ADV_DIER_UIE_MASK                      TIM1_DIER_UIE_MASK
#define TIM_ADV_DIER_UIE(x)                        TIM1_DIER_UIE(x)

/*!
 * @brief TIM_ADV_SR Register Bit Definition
 */

#define TIM_ADV_SR_CC5IF_SHIFT                     TIM1_SR_CC5IF_SHIFT
#define TIM_ADV_SR_CC5IF_MASK                      TIM1_SR_CC5IF_MASK
#define TIM_ADV_SR_CC5IF(x)                        TIM1_SR_CC5IF(x)

#define TIM_ADV_SR_CC4OF_SHIFT                     TIM1_SR_CC4OF_SHIFT
#define TIM_ADV_SR_CC4OF_MASK                      TIM1_SR_CC4OF_MASK
#define TIM_ADV_SR_CC4OF(x)                        TIM1_SR_CC4OF(x)

#define TIM_ADV_SR_CC3OF_SHIFT                     TIM1_SR_CC3OF_SHIFT
#define TIM_ADV_SR_CC3OF_MASK                      TIM1_SR_CC3OF_MASK
#define TIM_ADV_SR_CC3OF(x)                        TIM1_SR_CC3OF(x)

#define TIM_ADV_SR_CC2OF_SHIFT                     TIM1_SR_CC2OF_SHIFT
#define TIM_ADV_SR_CC2OF_MASK                      TIM1_SR_CC2OF_MASK
#define TIM_ADV_SR_CC2OF(x)                        TIM1_SR_CC2OF(x)

#define TIM_ADV_SR_CC1OF_SHIFT                     TIM1_SR_CC1OF_SHIFT
#define TIM_ADV_SR_CC1OF_MASK                      TIM1_SR_CC1OF_MASK
#define TIM_ADV_SR_CC1OF(x)                        TIM1_SR_CC1OF(x)

#define TIM_ADV_SR_BIF_SHIFT                       TIM1_SR_BIF_SHIFT
#define TIM_ADV_SR_BIF_MASK                        TIM1_SR_BIF_MASK
#define TIM_ADV_SR_BIF(x)                          TIM1_SR_BIF(x)

#define TIM_ADV_SR_TIF_SHIFT                       TIM1_SR_TIF_SHIFT
#define TIM_ADV_SR_TIF_MASK                        TIM1_SR_TIF_MASK
#define TIM_ADV_SR_TIF(x)                          TIM1_SR_TIF(x)

#define TIM_ADV_SR_COMIF_SHIFT                     TIM1_SR_COMIF_SHIFT
#define TIM_ADV_SR_COMIF_MASK                      TIM1_SR_COMIF_MASK
#define TIM_ADV_SR_COMIF(x)                        TIM1_SR_COMIF(x)

#define TIM_ADV_SR_CC4IF_SHIFT                     TIM1_SR_CC4IF_SHIFT
#define TIM_ADV_SR_CC4IF_MASK                      TIM1_SR_CC4IF_MASK
#define TIM_ADV_SR_CC4IF(x)                        TIM1_SR_CC4IF(x)

#define TIM_ADV_SR_CC3IF_SHIFT                     TIM1_SR_CC3IF_SHIFT
#define TIM_ADV_SR_CC3IF_MASK                      TIM1_SR_CC3IF_MASK
#define TIM_ADV_SR_CC3IF(x)                        TIM1_SR_CC3IF(x)

#define TIM_ADV_SR_CC2IF_SHIFT                     TIM1_SR_CC2IF_SHIFT
#define TIM_ADV_SR_CC2IF_MASK                      TIM1_SR_CC2IF_MASK
#define TIM_ADV_SR_CC2IF(x)                        TIM1_SR_CC2IF(x)

#define TIM_ADV_SR_CC1IF_SHIFT                     TIM1_SR_CC1IF_SHIFT
#define TIM_ADV_SR_CC1IF_MASK                      TIM1_SR_CC1IF_MASK
#define TIM_ADV_SR_CC1IF(x)                        TIM1_SR_CC1IF(x)

#define TIM_ADV_SR_UIF_SHIFT                       TIM1_SR_UIF_SHIFT
#define TIM_ADV_SR_UIF_MASK                        TIM1_SR_UIF_MASK
#define TIM_ADV_SR_UIF(x)                          TIM1_SR_UIF(x)

/*!
 * @brief TIM_ADV_EGR Register Bit Definition
 */

#define TIM_ADV_EGR_CC5G_SHIFT                     TIM1_EGR_CC5G_SHIFT
#define TIM_ADV_EGR_CC5G_MASK                      TIM1_EGR_CC5G_MASK
#define TIM_ADV_EGR_CC5G(x)                        TIM1_EGR_CC5G(x)

#define TIM_ADV_EGR_BG_SHIFT                       TIM1_EGR_BG_SHIFT
#define TIM_ADV_EGR_BG_MASK                        TIM1_EGR_BG_MASK
#define TIM_ADV_EGR_BG(x)                          TIM1_EGR_BG(x)

#define TIM_ADV_EGR_TG_SHIFT                       TIM1_EGR_TG_SHIFT
#define TIM_ADV_EGR_TG_MASK                        TIM1_EGR_TG_MASK
#define TIM_ADV_EGR_TG(x)                          TIM1_EGR_TG(x)

#define TIM_ADV_EGR_COMG_SHIFT                     TIM1_EGR_COMG_SHIFT
#define TIM_ADV_EGR_COMG_MASK                      TIM1_EGR_COMG_MASK
#define TIM_ADV_EGR_COMG(x)                        TIM1_EGR_COMG(x)

#define TIM_ADV_EGR_CC4G_SHIFT                     TIM1_EGR_CC4G_SHIFT
#define TIM_ADV_EGR_CC4G_MASK                      TIM1_EGR_CC4G_MASK
#define TIM_ADV_EGR_CC4G(x)                        TIM1_EGR_CC4G(x)

#define TIM_ADV_EGR_CC3G_SHIFT                     TIM1_EGR_CC3G_SHIFT
#define TIM_ADV_EGR_CC3G_MASK                      TIM1_EGR_CC3G_MASK
#define TIM_ADV_EGR_CC3G(x)                        TIM1_EGR_CC3G(x)

#define TIM_ADV_EGR_CC2G_SHIFT                     TIM1_EGR_CC2G_SHIFT
#define TIM_ADV_EGR_CC2G_MASK                      TIM1_EGR_CC2G_MASK
#define TIM_ADV_EGR_CC2G(x)                        TIM1_EGR_CC2G(x)

#define TIM_ADV_EGR_CC1G_SHIFT                     TIM1_EGR_CC1G_SHIFT
#define TIM_ADV_EGR_CC1G_MASK                      TIM1_EGR_CC1G_MASK
#define TIM_ADV_EGR_CC1G(x)                        TIM1_EGR_CC1G(x)

#define TIM_ADV_EGR_UG_SHIFT                       TIM1_EGR_UG_SHIFT
#define TIM_ADV_EGR_UG_MASK                        TIM1_EGR_UG_MASK
#define TIM_ADV_EGR_UG(x)                          TIM1_EGR_UG(x)

/*!
 * @brief TIM_ADV_CCMR1 Register Bit Definition
 */

#define TIM_ADV_CCMR1_OC2CE_SHIFT                  TIM1_CCMR1_OC2CE_SHIFT
#define TIM_ADV_CCMR1_OC2CE_MASK                   TIM1_CCMR1_OC2CE_MASK
#define TIM_ADV_CCMR1_OC2CE(x)                     TIM1_CCMR1_OC2CE(x)

#define TIM_ADV_CCMR1_OC2M_SHIFT                   TIM1_CCMR1_OC2M_SHIFT
#define TIM_ADV_CCMR1_OC2M_MASK                    TIM1_CCMR1_OC2M_MASK
#define TIM_ADV_CCMR1_OC2M(x)                      TIM1_CCMR1_OC2M(x)

#define TIM_ADV_CCMR1_OC2PE_SHIFT                  TIM1_CCMR1_OC2PE_SHIFT
#define TIM_ADV_CCMR1_OC2PE_MASK                   TIM1_CCMR1_OC2PE_MASK
#define TIM_ADV_CCMR1_OC2PE(x)                     TIM1_CCMR1_OC2PE(x)

#define TIM_ADV_CCMR1_OC2FE_SHIFT                  TIM1_CCMR1_OC2FE_SHIFT
#define TIM_ADV_CCMR1_OC2FE_MASK                   TIM1_CCMR1_OC2FE_MASK
#define TIM_ADV_CCMR1_OC2FE(x)                     TIM1_CCMR1_OC2FE(x)

#define TIM_ADV_CCMR1_CC2S_SHIFT                   TIM1_CCMR1_CC2S_SHIFT
#define TIM_ADV_CCMR1_CC2S_MASK                    TIM1_CCMR1_CC2S_MASK
#define TIM_ADV_CCMR1_CC2S(x)                      TIM1_CCMR1_CC2S(x)

#define TIM_ADV_CCMR1_OC1CE_SHIFT                  TIM1_CCMR1_OC1CE_SHIFT
#define TIM_ADV_CCMR1_OC1CE_MASK                   TIM1_CCMR1_OC1CE_MASK
#define TIM_ADV_CCMR1_OC1CE(x)                     TIM1_CCMR1_OC1CE(x)

#define TIM_ADV_CCMR1_OC1M_SHIFT                   TIM1_CCMR1_OC1M_SHIFT
#define TIM_ADV_CCMR1_OC1M_MASK                    TIM1_CCMR1_OC1M_MASK
#define TIM_ADV_CCMR1_OC1M(x)                      TIM1_CCMR1_OC1M(x)

#define TIM_ADV_CCMR1_OC1PE_SHIFT                  TIM1_CCMR1_OC1PE_SHIFT
#define TIM_ADV_CCMR1_OC1PE_MASK                   TIM1_CCMR1_OC1PE_MASK
#define TIM_ADV_CCMR1_OC1PE(x)                     TIM1_CCMR1_OC1PE(x)

#define TIM_ADV_CCMR1_OC1FE_SHIFT                  TIM1_CCMR1_OC1FE_SHIFT
#define TIM_ADV_CCMR1_OC1FE_MASK                   TIM1_CCMR1_OC1FE_MASK
#define TIM_ADV_CCMR1_OC1FE(x)                     TIM1_CCMR1_OC1FE(x)

#define TIM_ADV_CCMR1_CC1S_SHIFT                   TIM1_CCMR1_CC1S_SHIFT
#define TIM_ADV_CCMR1_CC1S_MASK                    TIM1_CCMR1_CC1S_MASK
#define TIM_ADV_CCMR1_CC1S(x)                      TIM1_CCMR1_CC1S(x)

/*!
 * @brief TIM_ADV_CCMR1 Register Bit Definition
 */

#define TIM_ADV_CCMR1_IC2F_SHIFT                   TIM1_CCMR1_IC2F_SHIFT
#define TIM_ADV_CCMR1_IC2F_MASK                    TIM1_CCMR1_IC2F_MASK
#define TIM_ADV_CCMR1_IC2F(x)                      TIM1_CCMR1_IC2F(x)

#define TIM_ADV_CCMR1_IC2PSC_SHIFT                 TIM1_CCMR1_IC2PSC_SHIFT
#define TIM_ADV_CCMR1_IC2PSC_MASK                  TIM1_CCMR1_IC2PSC_MASK
#define TIM_ADV_CCMR1_IC2PSC(x)                    TIM1_CCMR1_IC2PSC(x)

#define TIM_ADV_CCMR1_CC2S_SHIFT                   TIM1_CCMR1_CC2S_SHIFT
#define TIM_ADV_CCMR1_CC2S_MASK                    TIM1_CCMR1_CC2S_MASK
#define TIM_ADV_CCMR1_CC2S(x)                      TIM1_CCMR1_CC2S(x)

#define TIM_ADV_CCMR1_IC1F_SHIFT                   TIM1_CCMR1_IC1F_SHIFT
#define TIM_ADV_CCMR1_IC1F_MASK                    TIM1_CCMR1_IC1F_MASK
#define TIM_ADV_CCMR1_IC1F(x)                      TIM1_CCMR1_IC1F(x)

#define TIM_ADV_CCMR1_IC1PSC_SHIFT                 TIM1_CCMR1_IC1PSC_SHIFT
#define TIM_ADV_CCMR1_IC1PSC_MASK                  TIM1_CCMR1_IC1PSC_MASK
#define TIM_ADV_CCMR1_IC1PSC(x)                    TIM1_CCMR1_IC1PSC(x)

#define TIM_ADV_CCMR1_CC1S_SHIFT                   TIM1_CCMR1_CC1S_SHIFT
#define TIM_ADV_CCMR1_CC1S_MASK                    TIM1_CCMR1_CC1S_MASK
#define TIM_ADV_CCMR1_CC1S(x)                      TIM1_CCMR1_CC1S(x)

/*!
 * @brief TIM_ADV_CCMR2 Register Bit Definition
 */

#define TIM_ADV_CCMR2_OC4CE_SHIFT                  TIM1_CCMR2_OC4CE_SHIFT
#define TIM_ADV_CCMR2_OC4CE_MASK                   TIM1_CCMR2_OC4CE_MASK
#define TIM_ADV_CCMR2_OC4CE(x)                     TIM1_CCMR2_OC4CE(x)

#define TIM_ADV_CCMR2_OC4M_SHIFT                   TIM1_CCMR2_OC4M_SHIFT
#define TIM_ADV_CCMR2_OC4M_MASK                    TIM1_CCMR2_OC4M_MASK
#define TIM_ADV_CCMR2_OC4M(x)                      TIM1_CCMR2_OC4M(x)

#define TIM_ADV_CCMR2_OC4PE_SHIFT                  TIM1_CCMR2_OC4PE_SHIFT
#define TIM_ADV_CCMR2_OC4PE_MASK                   TIM1_CCMR2_OC4PE_MASK
#define TIM_ADV_CCMR2_OC4PE(x)                     TIM1_CCMR2_OC4PE(x)

#define TIM_ADV_CCMR2_OC4FE_SHIFT                  TIM1_CCMR2_OC4FE_SHIFT
#define TIM_ADV_CCMR2_OC4FE_MASK                   TIM1_CCMR2_OC4FE_MASK
#define TIM_ADV_CCMR2_OC4FE(x)                     TIM1_CCMR2_OC4FE(x)

#define TIM_ADV_CCMR2_CC4S_SHIFT                   TIM1_CCMR2_CC4S_SHIFT
#define TIM_ADV_CCMR2_CC4S_MASK                    TIM1_CCMR2_CC4S_MASK
#define TIM_ADV_CCMR2_CC4S(x)                      TIM1_CCMR2_CC4S(x)

#define TIM_ADV_CCMR2_OC3CE_SHIFT                  TIM1_CCMR2_OC3CE_SHIFT
#define TIM_ADV_CCMR2_OC3CE_MASK                   TIM1_CCMR2_OC3CE_MASK
#define TIM_ADV_CCMR2_OC3CE(x)                     TIM1_CCMR2_OC3CE(x)

#define TIM_ADV_CCMR2_OC3M_SHIFT                   TIM1_CCMR2_OC3M_SHIFT
#define TIM_ADV_CCMR2_OC3M_MASK                    TIM1_CCMR2_OC3M_MASK
#define TIM_ADV_CCMR2_OC3M(x)                      TIM1_CCMR2_OC3M(x)

#define TIM_ADV_CCMR2_OC3PE_SHIFT                  TIM1_CCMR2_OC3PE_SHIFT
#define TIM_ADV_CCMR2_OC3PE_MASK                   TIM1_CCMR2_OC3PE_MASK
#define TIM_ADV_CCMR2_OC3PE(x)                     TIM1_CCMR2_OC3PE(x)

#define TIM_ADV_CCMR2_OC3FE_SHIFT                  TIM1_CCMR2_OC3FE_SHIFT
#define TIM_ADV_CCMR2_OC3FE_MASK                   TIM1_CCMR2_OC3FE_MASK
#define TIM_ADV_CCMR2_OC3FE(x)                     TIM1_CCMR2_OC3FE(x)

#define TIM_ADV_CCMR2_CC3S_SHIFT                   TIM1_CCMR2_CC3S_SHIFT
#define TIM_ADV_CCMR2_CC3S_MASK                    TIM1_CCMR2_CC3S_MASK
#define TIM_ADV_CCMR2_CC3S(x)                      TIM1_CCMR2_CC3S(x)

/*!
 * @brief TIM_ADV_CCMR2 Register Bit Definition
 */

#define TIM_ADV_CCMR2_IC4F_SHIFT                   TIM1_CCMR2_IC4F_SHIFT
#define TIM_ADV_CCMR2_IC4F_MASK                    TIM1_CCMR2_IC4F_MASK
#define TIM_ADV_CCMR2_IC4F(x)                      TIM1_CCMR2_IC4F(x)

#define TIM_ADV_CCMR2_IC4PSC_SHIFT                 TIM1_CCMR2_IC4PSC_SHIFT
#define TIM_ADV_CCMR2_IC4PSC_MASK                  TIM1_CCMR2_IC4PSC_MASK
#define TIM_ADV_CCMR2_IC4PSC(x)                    TIM1_CCMR2_IC4PSC(x)

#define TIM_ADV_CCMR2_CC4S_SHIFT                   TIM1_CCMR2_CC4S_SHIFT
#define TIM_ADV_CCMR2_CC4S_MASK                    TIM1_CCMR2_CC4S_MASK
#define TIM_ADV_CCMR2_CC4S(x)                      TIM1_CCMR2_CC4S(x)

#define TIM_ADV_CCMR2_IC3F_SHIFT                   TIM1_CCMR2_IC3F_SHIFT
#define TIM_ADV_CCMR2_IC3F_MASK                    TIM1_CCMR2_IC3F_MASK
#define TIM_ADV_CCMR2_IC3F(x)                      TIM1_CCMR2_IC3F(x)

#define TIM_ADV_CCMR2_IC3PSC_SHIFT                 TIM1_CCMR2_IC3PSC_SHIFT
#define TIM_ADV_CCMR2_IC3PSC_MASK                  TIM1_CCMR2_IC3PSC_MASK
#define TIM_ADV_CCMR2_IC3PSC(x)                    TIM1_CCMR2_IC3PSC(x)

#define TIM_ADV_CCMR2_CC3S_SHIFT                   TIM1_CCMR2_CC3S_SHIFT
#define TIM_ADV_CCMR2_CC3S_MASK                    TIM1_CCMR2_CC3S_MASK
#define TIM_ADV_CCMR2_CC3S(x)                      TIM1_CCMR2_CC3S(x)

/*!
 * @brief TIM_ADV_CCER Register Bit Definition
 */

#define TIM_ADV_CCER_CC4NP_SHIFT                   TIM1_CCER_CC4NP_SHIFT
#define TIM_ADV_CCER_CC4NP_MASK                    TIM1_CCER_CC4NP_MASK
#define TIM_ADV_CCER_CC4NP(x)                      TIM1_CCER_CC4NP(x)

#define TIM_ADV_CCER_CC4P_SHIFT                    TIM1_CCER_CC4P_SHIFT
#define TIM_ADV_CCER_CC4P_MASK                     TIM1_CCER_CC4P_MASK
#define TIM_ADV_CCER_CC4P(x)                       TIM1_CCER_CC4P(x)

#define TIM_ADV_CCER_CC4E_SHIFT                    TIM1_CCER_CC4E_SHIFT
#define TIM_ADV_CCER_CC4E_MASK                     TIM1_CCER_CC4E_MASK
#define TIM_ADV_CCER_CC4E(x)                       TIM1_CCER_CC4E(x)

#define TIM_ADV_CCER_CC3NP_SHIFT                   TIM1_CCER_CC3NP_SHIFT
#define TIM_ADV_CCER_CC3NP_MASK                    TIM1_CCER_CC3NP_MASK
#define TIM_ADV_CCER_CC3NP(x)                      TIM1_CCER_CC3NP(x)

#define TIM_ADV_CCER_CC3NE_SHIFT                   TIM1_CCER_CC3NE_SHIFT
#define TIM_ADV_CCER_CC3NE_MASK                    TIM1_CCER_CC3NE_MASK
#define TIM_ADV_CCER_CC3NE(x)                      TIM1_CCER_CC3NE(x)

#define TIM_ADV_CCER_CC3P_SHIFT                    TIM1_CCER_CC3P_SHIFT
#define TIM_ADV_CCER_CC3P_MASK                     TIM1_CCER_CC3P_MASK
#define TIM_ADV_CCER_CC3P(x)                       TIM1_CCER_CC3P(x)

#define TIM_ADV_CCER_CC3E_SHIFT                    TIM1_CCER_CC3E_SHIFT
#define TIM_ADV_CCER_CC3E_MASK                     TIM1_CCER_CC3E_MASK
#define TIM_ADV_CCER_CC3E(x)                       TIM1_CCER_CC3E(x)

#define TIM_ADV_CCER_CC2NP_SHIFT                   TIM1_CCER_CC2NP_SHIFT
#define TIM_ADV_CCER_CC2NP_MASK                    TIM1_CCER_CC2NP_MASK
#define TIM_ADV_CCER_CC2NP(x)                      TIM1_CCER_CC2NP(x)

#define TIM_ADV_CCER_CC2NE_SHIFT                   TIM1_CCER_CC2NE_SHIFT
#define TIM_ADV_CCER_CC2NE_MASK                    TIM1_CCER_CC2NE_MASK
#define TIM_ADV_CCER_CC2NE(x)                      TIM1_CCER_CC2NE(x)

#define TIM_ADV_CCER_CC2P_SHIFT                    TIM1_CCER_CC2P_SHIFT
#define TIM_ADV_CCER_CC2P_MASK                     TIM1_CCER_CC2P_MASK
#define TIM_ADV_CCER_CC2P(x)                       TIM1_CCER_CC2P(x)

#define TIM_ADV_CCER_CC2E_SHIFT                    TIM1_CCER_CC2E_SHIFT
#define TIM_ADV_CCER_CC2E_MASK                     TIM1_CCER_CC2E_MASK
#define TIM_ADV_CCER_CC2E(x)                       TIM1_CCER_CC2E(x)

#define TIM_ADV_CCER_CC1NP_SHIFT                   TIM1_CCER_CC1NP_SHIFT
#define TIM_ADV_CCER_CC1NP_MASK                    TIM1_CCER_CC1NP_MASK
#define TIM_ADV_CCER_CC1NP(x)                      TIM1_CCER_CC1NP(x)

#define TIM_ADV_CCER_CC1NE_SHIFT                   TIM1_CCER_CC1NE_SHIFT
#define TIM_ADV_CCER_CC1NE_MASK                    TIM1_CCER_CC1NE_MASK
#define TIM_ADV_CCER_CC1NE(x)                      TIM1_CCER_CC1NE(x)

#define TIM_ADV_CCER_CC1P_SHIFT                    TIM1_CCER_CC1P_SHIFT
#define TIM_ADV_CCER_CC1P_MASK                     TIM1_CCER_CC1P_MASK
#define TIM_ADV_CCER_CC1P(x)                       TIM1_CCER_CC1P(x)

#define TIM_ADV_CCER_CC1E_SHIFT                    TIM1_CCER_CC1E_SHIFT
#define TIM_ADV_CCER_CC1E_MASK                     TIM1_CCER_CC1E_MASK
#define TIM_ADV_CCER_CC1E(x)                       TIM1_CCER_CC1E(x)

/*!
 * @brief TIM_ADV_CNT Register Bit Definition
 */

#define TIM_ADV_CNT_CNT_SHIFT                      TIM1_CNT_CNT_SHIFT
#define TIM_ADV_CNT_CNT_MASK                       TIM1_CNT_CNT_MASK
#define TIM_ADV_CNT_CNT(x)                         TIM1_CNT_CNT(x)

/*!
 * @brief TIM_ADV_PSC Register Bit Definition
 */

#define TIM_ADV_PSC_PSC_SHIFT                      TIM1_PSC_PSC_SHIFT
#define TIM_ADV_PSC_PSC_MASK                       TIM1_PSC_PSC_MASK
#define TIM_ADV_PSC_PSC(x)                         TIM1_PSC_PSC(x)

/*!
 * @brief TIM_ADV_ARR Register Bit Definition
 */

#define TIM_ADV_ARR_ARR_SHIFT                      TIM1_ARR_ARR_SHIFT
#define TIM_ADV_ARR_ARR_MASK                       TIM1_ARR_ARR_MASK
#define TIM_ADV_ARR_ARR(x)                         TIM1_ARR_ARR(x)

/*!
 * @brief TIM_ADV_RCR Register Bit Definition
 */

#define TIM_ADV_RCR_REPCNT_SHIFT                   TIM1_RCR_REPCNT_SHIFT
#define TIM_ADV_RCR_REPCNT_MASK                    TIM1_RCR_REPCNT_MASK
#define TIM_ADV_RCR_REPCNT(x)                      TIM1_RCR_REPCNT(x)

#define TIM_ADV_RCR_REP_SHIFT                      TIM1_RCR_REP_SHIFT
#define TIM_ADV_RCR_REP_MASK                       TIM1_RCR_REP_MASK
#define TIM_ADV_RCR_REP(x)                         TIM1_RCR_REP(x)

/*!
 * @brief TIM_ADV_CCR1 Register Bit Definition
 */

#define TIM_ADV_CCR1_CCR1_SHIFT                    TIM1_CCR1_CCR1_SHIFT
#define TIM_ADV_CCR1_CCR1_MASK                     TIM1_CCR1_CCR1_MASK
#define TIM_ADV_CCR1_CCR1(x)                       TIM1_CCR1_CCR1(x)

/*!
 * @brief TIM_ADV_CCR2 Register Bit Definition
 */

#define TIM_ADV_CCR2_CCR2_SHIFT                    TIM1_CCR2_CCR2_SHIFT
#define TIM_ADV_CCR2_CCR2_MASK                     TIM1_CCR2_CCR2_MASK
#define TIM_ADV_CCR2_CCR2(x)                       TIM1_CCR2_CCR2(x)

/*!
 * @brief TIM_ADV_CCR3 Register Bit Definition
 */

#define TIM_ADV_CCR3_CCR3_SHIFT                    TIM1_CCR3_CCR3_SHIFT
#define TIM_ADV_CCR3_CCR3_MASK                     TIM1_CCR3_CCR3_MASK
#define TIM_ADV_CCR3_CCR3(x)                       TIM1_CCR3_CCR3(x)

/*!
 * @brief TIM_ADV_CCR4 Register Bit Definition
 */

#define TIM_ADV_CCR4_CCR4_SHIFT                    TIM1_CCR4_CCR4_SHIFT
#define TIM_ADV_CCR4_CCR4_MASK                     TIM1_CCR4_CCR4_MASK
#define TIM_ADV_CCR4_CCR4(x)                       TIM1_CCR4_CCR4(x)

/*!
 * @brief TIM_ADV_BDTR Register Bit Definition
 */

#define TIM_ADV_BDTR_DOE_SHIFT                     TIM1_BDTR_DOE_SHIFT
#define TIM_ADV_BDTR_DOE_MASK                      TIM1_BDTR_DOE_MASK
#define TIM_ADV_BDTR_DOE(x)                        TIM1_BDTR_DOE(x)

#define TIM_ADV_BDTR_MOE_SHIFT                     TIM1_BDTR_MOE_SHIFT
#define TIM_ADV_BDTR_MOE_MASK                      TIM1_BDTR_MOE_MASK
#define TIM_ADV_BDTR_MOE(x)                        TIM1_BDTR_MOE(x)

#define TIM_ADV_BDTR_AOE_SHIFT                     TIM1_BDTR_AOE_SHIFT
#define TIM_ADV_BDTR_AOE_MASK                      TIM1_BDTR_AOE_MASK
#define TIM_ADV_BDTR_AOE(x)                        TIM1_BDTR_AOE(x)

#define TIM_ADV_BDTR_BKP_SHIFT                     TIM1_BDTR_BKP_SHIFT
#define TIM_ADV_BDTR_BKP_MASK                      TIM1_BDTR_BKP_MASK
#define TIM_ADV_BDTR_BKP(x)                        TIM1_BDTR_BKP(x)

#define TIM_ADV_BDTR_BKE_SHIFT                     TIM1_BDTR_BKE_SHIFT
#define TIM_ADV_BDTR_BKE_MASK                      TIM1_BDTR_BKE_MASK
#define TIM_ADV_BDTR_BKE(x)                        TIM1_BDTR_BKE(x)

#define TIM_ADV_BDTR_OSSR_SHIFT                    TIM1_BDTR_OSSR_SHIFT
#define TIM_ADV_BDTR_OSSR_MASK                     TIM1_BDTR_OSSR_MASK
#define TIM_ADV_BDTR_OSSR(x)                       TIM1_BDTR_OSSR(x)

#define TIM_ADV_BDTR_OSSI_SHIFT                    TIM1_BDTR_OSSI_SHIFT
#define TIM_ADV_BDTR_OSSI_MASK                     TIM1_BDTR_OSSI_MASK
#define TIM_ADV_BDTR_OSSI(x)                       TIM1_BDTR_OSSI(x)

#define TIM_ADV_BDTR_LOCK_SHIFT                    TIM1_BDTR_LOCK_SHIFT
#define TIM_ADV_BDTR_LOCK_MASK                     TIM1_BDTR_LOCK_MASK
#define TIM_ADV_BDTR_LOCK(x)                       TIM1_BDTR_LOCK(x)

#define TIM_ADV_BDTR_DTG_SHIFT                     TIM1_BDTR_DTG_SHIFT
#define TIM_ADV_BDTR_DTG_MASK                      TIM1_BDTR_DTG_MASK
#define TIM_ADV_BDTR_DTG(x)                        TIM1_BDTR_DTG(x)

/*!
 * @brief TIM_ADV_DCR Register Bit Definition
 */

#define TIM_ADV_DCR_DBL_SHIFT                      TIM1_DCR_DBL_SHIFT
#define TIM_ADV_DCR_DBL_MASK                       TIM1_DCR_DBL_MASK
#define TIM_ADV_DCR_DBL(x)                         TIM1_DCR_DBL(x)

#define TIM_ADV_DCR_DBA_SHIFT                      TIM1_DCR_DBA_SHIFT
#define TIM_ADV_DCR_DBA_MASK                       TIM1_DCR_DBA_MASK
#define TIM_ADV_DCR_DBA(x)                         TIM1_DCR_DBA(x)

/*!
 * @brief TIM_ADV_DMAR Register Bit Definition
 */

#define TIM_ADV_DMAR_DMAB_SHIFT                    TIM1_DMAR_DMAB_SHIFT
#define TIM_ADV_DMAR_DMAB_MASK                     TIM1_DMAR_DMAB_MASK
#define TIM_ADV_DMAR_DMAB(x)                       TIM1_DMAR_DMAB(x)

/*!
 * @brief TIM_ADV_CCMR3 Register Bit Definition
 */

#define TIM_ADV_CCMR3_OC5M_SHIFT                   TIM1_CCMR3_OC5M_SHIFT
#define TIM_ADV_CCMR3_OC5M_MASK                    TIM1_CCMR3_OC5M_MASK
#define TIM_ADV_CCMR3_OC5M(x)                      TIM1_CCMR3_OC5M(x)

#define TIM_ADV_CCMR3_OC5PE_SHIFT                  TIM1_CCMR3_OC5PE_SHIFT
#define TIM_ADV_CCMR3_OC5PE_MASK                   TIM1_CCMR3_OC5PE_MASK
#define TIM_ADV_CCMR3_OC5PE(x)                     TIM1_CCMR3_OC5PE(x)

#define TIM_ADV_CCMR3_OC5FE_SHIFT                  TIM1_CCMR3_OC5FE_SHIFT
#define TIM_ADV_CCMR3_OC5FE_MASK                   TIM1_CCMR3_OC5FE_MASK
#define TIM_ADV_CCMR3_OC5FE(x)                     TIM1_CCMR3_OC5FE(x)

/*!
 * @brief TIM_ADV_CCR5 Register Bit Definition
 */

#define TIM_ADV_CCR5_CCR5_SHIFT                    TIM1_CCR5_CCR5_SHIFT
#define TIM_ADV_CCR5_CCR5_MASK                     TIM1_CCR5_CCR5_MASK
#define TIM_ADV_CCR5_CCR5(x)                       TIM1_CCR5_CCR5(x)

/*!
 * @brief TIM_ADV_PDER Register Bit Definition
 */

#define TIM_ADV_PDER_CCR5SHIFTEN_SHIFT             TIM1_PDER_CCR5SHIFTEN_SHIFT
#define TIM_ADV_PDER_CCR5SHIFTEN_MASK              TIM1_PDER_CCR5SHIFTEN_MASK
#define TIM_ADV_PDER_CCR5SHIFTEN(x)                TIM1_PDER_CCR5SHIFTEN(x)

#define TIM_ADV_PDER_CCR4SHIFTEN_SHIFT             TIM1_PDER_CCR4SHIFTEN_SHIFT
#define TIM_ADV_PDER_CCR4SHIFTEN_MASK              TIM1_PDER_CCR4SHIFTEN_MASK
#define TIM_ADV_PDER_CCR4SHIFTEN(x)                TIM1_PDER_CCR4SHIFTEN(x)

#define TIM_ADV_PDER_CCR3SHIFTEN_SHIFT             TIM1_PDER_CCR3SHIFTEN_SHIFT
#define TIM_ADV_PDER_CCR3SHIFTEN_MASK              TIM1_PDER_CCR3SHIFTEN_MASK
#define TIM_ADV_PDER_CCR3SHIFTEN(x)                TIM1_PDER_CCR3SHIFTEN(x)

#define TIM_ADV_PDER_CCR2SHIFTEN_SHIFT             TIM1_PDER_CCR2SHIFTEN_SHIFT
#define TIM_ADV_PDER_CCR2SHIFTEN_MASK              TIM1_PDER_CCR2SHIFTEN_MASK
#define TIM_ADV_PDER_CCR2SHIFTEN(x)                TIM1_PDER_CCR2SHIFTEN(x)

#define TIM_ADV_PDER_CCR1SHIFTEN_SHIFT             TIM1_PDER_CCR1SHIFTEN_SHIFT
#define TIM_ADV_PDER_CCR1SHIFTEN_MASK              TIM1_PDER_CCR1SHIFTEN_MASK
#define TIM_ADV_PDER_CCR1SHIFTEN(x)                TIM1_PDER_CCR1SHIFTEN(x)

#define TIM_ADV_PDER_CCDREPE_SHIFT                 TIM1_PDER_CCDREPE_SHIFT
#define TIM_ADV_PDER_CCDREPE_MASK                  TIM1_PDER_CCDREPE_MASK
#define TIM_ADV_PDER_CCDREPE(x)                    TIM1_PDER_CCDREPE(x)

/*!
 * @brief TIM_ADV_CCRFALL Register Bit Definition
 */

#define TIM_ADV_CCRFALL_CCRXFALL_SHIFT             TIM1_CCRFALL_CCRXFALL_SHIFT
#define TIM_ADV_CCRFALL_CCRXFALL_MASK              TIM1_CCRFALL_CCRXFALL_MASK
#define TIM_ADV_CCRFALL_CCRXFALL(x)                TIM1_CCRFALL_CCRXFALL(x)

/*!
 * @}
 */ /* end of group TIM_ADV_Register_Masks */

/*******************************************************************************
 * TIM_16B Type
 ******************************************************************************/

/*!
 * @addtogroup TIM_16B_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief TIM_16B_CR1 Register Bit Definition
 */

#define TIM_16B_CR1_CKD_SHIFT                      TIM3_CR1_CKD_SHIFT
#define TIM_16B_CR1_CKD_MASK                       TIM3_CR1_CKD_MASK
#define TIM_16B_CR1_CKD(x)                         TIM3_CR1_CKD(x)

#define TIM_16B_CR1_APRE_SHIFT                     TIM3_CR1_APRE_SHIFT
#define TIM_16B_CR1_APRE_MASK                      TIM3_CR1_APRE_MASK
#define TIM_16B_CR1_APRE(x)                        TIM3_CR1_APRE(x)

#define TIM_16B_CR1_CMS_SHIFT                      TIM3_CR1_CMS_SHIFT
#define TIM_16B_CR1_CMS_MASK                       TIM3_CR1_CMS_MASK
#define TIM_16B_CR1_CMS(x)                         TIM3_CR1_CMS(x)

#define TIM_16B_CR1_DIR_SHIFT                      TIM3_CR1_DIR_SHIFT
#define TIM_16B_CR1_DIR_MASK                       TIM3_CR1_DIR_MASK
#define TIM_16B_CR1_DIR(x)                         TIM3_CR1_DIR(x)

#define TIM_16B_CR1_OPM_SHIFT                      TIM3_CR1_OPM_SHIFT
#define TIM_16B_CR1_OPM_MASK                       TIM3_CR1_OPM_MASK
#define TIM_16B_CR1_OPM(x)                         TIM3_CR1_OPM(x)

#define TIM_16B_CR1_URS_SHIFT                      TIM3_CR1_URS_SHIFT
#define TIM_16B_CR1_URS_MASK                       TIM3_CR1_URS_MASK
#define TIM_16B_CR1_URS(x)                         TIM3_CR1_URS(x)

#define TIM_16B_CR1_UDIS_SHIFT                     TIM3_CR1_UDIS_SHIFT
#define TIM_16B_CR1_UDIS_MASK                      TIM3_CR1_UDIS_MASK
#define TIM_16B_CR1_UDIS(x)                        TIM3_CR1_UDIS(x)

#define TIM_16B_CR1_CEN_SHIFT                      TIM3_CR1_CEN_SHIFT
#define TIM_16B_CR1_CEN_MASK                       TIM3_CR1_CEN_MASK
#define TIM_16B_CR1_CEN(x)                         TIM3_CR1_CEN(x)

/*!
 * @brief TIM_16B_CR2 Register Bit Definition
 */

#define TIM_16B_CR2_TI1S_SHIFT                     TIM3_CR2_TI1S_SHIFT
#define TIM_16B_CR2_TI1S_MASK                      TIM3_CR2_TI1S_MASK
#define TIM_16B_CR2_TI1S(x)                        TIM3_CR2_TI1S(x)

#define TIM_16B_CR2_MMS_SHIFT                      TIM3_CR2_MMS_SHIFT
#define TIM_16B_CR2_MMS_MASK                       TIM3_CR2_MMS_MASK
#define TIM_16B_CR2_MMS(x)                         TIM3_CR2_MMS(x)

#define TIM_16B_CR2_CCDS_SHIFT                     TIM3_CR2_CCDS_SHIFT
#define TIM_16B_CR2_CCDS_MASK                      TIM3_CR2_CCDS_MASK
#define TIM_16B_CR2_CCDS(x)                        TIM3_CR2_CCDS(x)

/*!
 * @brief TIM_16B_SMCR Register Bit Definition
 */

#define TIM_16B_SMCR_ETP_SHIFT                     TIM3_SMCR_ETP_SHIFT
#define TIM_16B_SMCR_ETP_MASK                      TIM3_SMCR_ETP_MASK
#define TIM_16B_SMCR_ETP(x)                        TIM3_SMCR_ETP(x)

#define TIM_16B_SMCR_ECE_SHIFT                     TIM3_SMCR_ECE_SHIFT
#define TIM_16B_SMCR_ECE_MASK                      TIM3_SMCR_ECE_MASK
#define TIM_16B_SMCR_ECE(x)                        TIM3_SMCR_ECE(x)

#define TIM_16B_SMCR_ETPS_SHIFT                    TIM3_SMCR_ETPS_SHIFT
#define TIM_16B_SMCR_ETPS_MASK                     TIM3_SMCR_ETPS_MASK
#define TIM_16B_SMCR_ETPS(x)                       TIM3_SMCR_ETPS(x)

#define TIM_16B_SMCR_ETF_SHIFT                     TIM3_SMCR_ETF_SHIFT
#define TIM_16B_SMCR_ETF_MASK                      TIM3_SMCR_ETF_MASK
#define TIM_16B_SMCR_ETF(x)                        TIM3_SMCR_ETF(x)

#define TIM_16B_SMCR_MSM_SHIFT                     TIM3_SMCR_MSM_SHIFT
#define TIM_16B_SMCR_MSM_MASK                      TIM3_SMCR_MSM_MASK
#define TIM_16B_SMCR_MSM(x)                        TIM3_SMCR_MSM(x)

#define TIM_16B_SMCR_TS_SHIFT                      TIM3_SMCR_TS_SHIFT
#define TIM_16B_SMCR_TS_MASK                       TIM3_SMCR_TS_MASK
#define TIM_16B_SMCR_TS(x)                         TIM3_SMCR_TS(x)

#define TIM_16B_SMCR_OCCS_SHIFT                    TIM3_SMCR_OCCS_SHIFT
#define TIM_16B_SMCR_OCCS_MASK                     TIM3_SMCR_OCCS_MASK
#define TIM_16B_SMCR_OCCS(x)                       TIM3_SMCR_OCCS(x)

#define TIM_16B_SMCR_SMS_SHIFT                     TIM3_SMCR_SMS_SHIFT
#define TIM_16B_SMCR_SMS_MASK                      TIM3_SMCR_SMS_MASK
#define TIM_16B_SMCR_SMS(x)                        TIM3_SMCR_SMS(x)

/*!
 * @brief TIM_16B_DIER Register Bit Definition
 */

#define TIM_16B_DIER_TDE_SHIFT                     TIM3_DIER_TDE_SHIFT
#define TIM_16B_DIER_TDE_MASK                      TIM3_DIER_TDE_MASK
#define TIM_16B_DIER_TDE(x)                        TIM3_DIER_TDE(x)

#define TIM_16B_DIER_CC4DE_SHIFT                   TIM3_DIER_CC4DE_SHIFT
#define TIM_16B_DIER_CC4DE_MASK                    TIM3_DIER_CC4DE_MASK
#define TIM_16B_DIER_CC4DE(x)                      TIM3_DIER_CC4DE(x)

#define TIM_16B_DIER_CC3DE_SHIFT                   TIM3_DIER_CC3DE_SHIFT
#define TIM_16B_DIER_CC3DE_MASK                    TIM3_DIER_CC3DE_MASK
#define TIM_16B_DIER_CC3DE(x)                      TIM3_DIER_CC3DE(x)

#define TIM_16B_DIER_CC2DE_SHIFT                   TIM3_DIER_CC2DE_SHIFT
#define TIM_16B_DIER_CC2DE_MASK                    TIM3_DIER_CC2DE_MASK
#define TIM_16B_DIER_CC2DE(x)                      TIM3_DIER_CC2DE(x)

#define TIM_16B_DIER_CC1DE_SHIFT                   TIM3_DIER_CC1DE_SHIFT
#define TIM_16B_DIER_CC1DE_MASK                    TIM3_DIER_CC1DE_MASK
#define TIM_16B_DIER_CC1DE(x)                      TIM3_DIER_CC1DE(x)

#define TIM_16B_DIER_UDE_SHIFT                     TIM3_DIER_UDE_SHIFT
#define TIM_16B_DIER_UDE_MASK                      TIM3_DIER_UDE_MASK
#define TIM_16B_DIER_UDE(x)                        TIM3_DIER_UDE(x)

#define TIM_16B_DIER_TIE_SHIFT                     TIM3_DIER_TIE_SHIFT
#define TIM_16B_DIER_TIE_MASK                      TIM3_DIER_TIE_MASK
#define TIM_16B_DIER_TIE(x)                        TIM3_DIER_TIE(x)

#define TIM_16B_DIER_CC4IE_SHIFT                   TIM3_DIER_CC4IE_SHIFT
#define TIM_16B_DIER_CC4IE_MASK                    TIM3_DIER_CC4IE_MASK
#define TIM_16B_DIER_CC4IE(x)                      TIM3_DIER_CC4IE(x)

#define TIM_16B_DIER_CC3IE_SHIFT                   TIM3_DIER_CC3IE_SHIFT
#define TIM_16B_DIER_CC3IE_MASK                    TIM3_DIER_CC3IE_MASK
#define TIM_16B_DIER_CC3IE(x)                      TIM3_DIER_CC3IE(x)

#define TIM_16B_DIER_CC2IE_SHIFT                   TIM3_DIER_CC2IE_SHIFT
#define TIM_16B_DIER_CC2IE_MASK                    TIM3_DIER_CC2IE_MASK
#define TIM_16B_DIER_CC2IE(x)                      TIM3_DIER_CC2IE(x)

#define TIM_16B_DIER_CC1IE_SHIFT                   TIM3_DIER_CC1IE_SHIFT
#define TIM_16B_DIER_CC1IE_MASK                    TIM3_DIER_CC1IE_MASK
#define TIM_16B_DIER_CC1IE(x)                      TIM3_DIER_CC1IE(x)

#define TIM_16B_DIER_UIE_SHIFT                     TIM3_DIER_UIE_SHIFT
#define TIM_16B_DIER_UIE_MASK                      TIM3_DIER_UIE_MASK
#define TIM_16B_DIER_UIE(x)                        TIM3_DIER_UIE(x)

/*!
 * @brief TIM_16B_SR Register Bit Definition
 */

#define TIM_16B_SR_CC4OF_SHIFT                     TIM3_SR_CC4OF_SHIFT
#define TIM_16B_SR_CC4OF_MASK                      TIM3_SR_CC4OF_MASK
#define TIM_16B_SR_CC4OF(x)                        TIM3_SR_CC4OF(x)

#define TIM_16B_SR_CC3OF_SHIFT                     TIM3_SR_CC3OF_SHIFT
#define TIM_16B_SR_CC3OF_MASK                      TIM3_SR_CC3OF_MASK
#define TIM_16B_SR_CC3OF(x)                        TIM3_SR_CC3OF(x)

#define TIM_16B_SR_CC2OF_SHIFT                     TIM3_SR_CC2OF_SHIFT
#define TIM_16B_SR_CC2OF_MASK                      TIM3_SR_CC2OF_MASK
#define TIM_16B_SR_CC2OF(x)                        TIM3_SR_CC2OF(x)

#define TIM_16B_SR_CC1OF_SHIFT                     TIM3_SR_CC1OF_SHIFT
#define TIM_16B_SR_CC1OF_MASK                      TIM3_SR_CC1OF_MASK
#define TIM_16B_SR_CC1OF(x)                        TIM3_SR_CC1OF(x)

#define TIM_16B_SR_TIF_SHIFT                       TIM3_SR_TIF_SHIFT
#define TIM_16B_SR_TIF_MASK                        TIM3_SR_TIF_MASK
#define TIM_16B_SR_TIF(x)                          TIM3_SR_TIF(x)

#define TIM_16B_SR_CC4IF_SHIFT                     TIM3_SR_CC4IF_SHIFT
#define TIM_16B_SR_CC4IF_MASK                      TIM3_SR_CC4IF_MASK
#define TIM_16B_SR_CC4IF(x)                        TIM3_SR_CC4IF(x)

#define TIM_16B_SR_CC3IF_SHIFT                     TIM3_SR_CC3IF_SHIFT
#define TIM_16B_SR_CC3IF_MASK                      TIM3_SR_CC3IF_MASK
#define TIM_16B_SR_CC3IF(x)                        TIM3_SR_CC3IF(x)

#define TIM_16B_SR_CC2IF_SHIFT                     TIM3_SR_CC2IF_SHIFT
#define TIM_16B_SR_CC2IF_MASK                      TIM3_SR_CC2IF_MASK
#define TIM_16B_SR_CC2IF(x)                        TIM3_SR_CC2IF(x)

#define TIM_16B_SR_CC1IF_SHIFT                     TIM3_SR_CC1IF_SHIFT
#define TIM_16B_SR_CC1IF_MASK                      TIM3_SR_CC1IF_MASK
#define TIM_16B_SR_CC1IF(x)                        TIM3_SR_CC1IF(x)

#define TIM_16B_SR_UIF_SHIFT                       TIM3_SR_UIF_SHIFT
#define TIM_16B_SR_UIF_MASK                        TIM3_SR_UIF_MASK
#define TIM_16B_SR_UIF(x)                          TIM3_SR_UIF(x)

/*!
 * @brief TIM_16B_EGR Register Bit Definition
 */

#define TIM_16B_EGR_TG_SHIFT                       TIM3_EGR_TG_SHIFT
#define TIM_16B_EGR_TG_MASK                        TIM3_EGR_TG_MASK
#define TIM_16B_EGR_TG(x)                          TIM3_EGR_TG(x)

#define TIM_16B_EGR_COMG_SHIFT                     TIM3_EGR_COMG_SHIFT
#define TIM_16B_EGR_COMG_MASK                      TIM3_EGR_COMG_MASK
#define TIM_16B_EGR_COMG(x)                        TIM3_EGR_COMG(x)

#define TIM_16B_EGR_CC4G_SHIFT                     TIM3_EGR_CC4G_SHIFT
#define TIM_16B_EGR_CC4G_MASK                      TIM3_EGR_CC4G_MASK
#define TIM_16B_EGR_CC4G(x)                        TIM3_EGR_CC4G(x)

#define TIM_16B_EGR_CC3G_SHIFT                     TIM3_EGR_CC3G_SHIFT
#define TIM_16B_EGR_CC3G_MASK                      TIM3_EGR_CC3G_MASK
#define TIM_16B_EGR_CC3G(x)                        TIM3_EGR_CC3G(x)

#define TIM_16B_EGR_CC2G_SHIFT                     TIM3_EGR_CC2G_SHIFT
#define TIM_16B_EGR_CC2G_MASK                      TIM3_EGR_CC2G_MASK
#define TIM_16B_EGR_CC2G(x)                        TIM3_EGR_CC2G(x)

#define TIM_16B_EGR_CC1G_SHIFT                     TIM3_EGR_CC1G_SHIFT
#define TIM_16B_EGR_CC1G_MASK                      TIM3_EGR_CC1G_MASK
#define TIM_16B_EGR_CC1G(x)                        TIM3_EGR_CC1G(x)

#define TIM_16B_EGR_UG_SHIFT                       TIM3_EGR_UG_SHIFT
#define TIM_16B_EGR_UG_MASK                        TIM3_EGR_UG_MASK
#define TIM_16B_EGR_UG(x)                          TIM3_EGR_UG(x)

/*!
 * @brief TIM_16B_CCMR1 Register Bit Definition
 */

#define TIM_16B_CCMR1_OC2CE_SHIFT                  TIM3_CCMR1_OC2CE_SHIFT
#define TIM_16B_CCMR1_OC2CE_MASK                   TIM3_CCMR1_OC2CE_MASK
#define TIM_16B_CCMR1_OC2CE(x)                     TIM3_CCMR1_OC2CE(x)

#define TIM_16B_CCMR1_OC2M_SHIFT                   TIM3_CCMR1_OC2M_SHIFT
#define TIM_16B_CCMR1_OC2M_MASK                    TIM3_CCMR1_OC2M_MASK
#define TIM_16B_CCMR1_OC2M(x)                      TIM3_CCMR1_OC2M(x)

#define TIM_16B_CCMR1_OC2PE_SHIFT                  TIM3_CCMR1_OC2PE_SHIFT
#define TIM_16B_CCMR1_OC2PE_MASK                   TIM3_CCMR1_OC2PE_MASK
#define TIM_16B_CCMR1_OC2PE(x)                     TIM3_CCMR1_OC2PE(x)

#define TIM_16B_CCMR1_OC2FE_SHIFT                  TIM3_CCMR1_OC2FE_SHIFT
#define TIM_16B_CCMR1_OC2FE_MASK                   TIM3_CCMR1_OC2FE_MASK
#define TIM_16B_CCMR1_OC2FE(x)                     TIM3_CCMR1_OC2FE(x)

#define TIM_16B_CCMR1_CC2S_SHIFT                   TIM3_CCMR1_CC2S_SHIFT
#define TIM_16B_CCMR1_CC2S_MASK                    TIM3_CCMR1_CC2S_MASK
#define TIM_16B_CCMR1_CC2S(x)                      TIM3_CCMR1_CC2S(x)

#define TIM_16B_CCMR1_OC1CE_SHIFT                  TIM3_CCMR1_OC1CE_SHIFT
#define TIM_16B_CCMR1_OC1CE_MASK                   TIM3_CCMR1_OC1CE_MASK
#define TIM_16B_CCMR1_OC1CE(x)                     TIM3_CCMR1_OC1CE(x)

#define TIM_16B_CCMR1_OC1M_SHIFT                   TIM3_CCMR1_OC1M_SHIFT
#define TIM_16B_CCMR1_OC1M_MASK                    TIM3_CCMR1_OC1M_MASK
#define TIM_16B_CCMR1_OC1M(x)                      TIM3_CCMR1_OC1M(x)

#define TIM_16B_CCMR1_OC1PE_SHIFT                  TIM3_CCMR1_OC1PE_SHIFT
#define TIM_16B_CCMR1_OC1PE_MASK                   TIM3_CCMR1_OC1PE_MASK
#define TIM_16B_CCMR1_OC1PE(x)                     TIM3_CCMR1_OC1PE(x)

#define TIM_16B_CCMR1_OC1FE_SHIFT                  TIM3_CCMR1_OC1FE_SHIFT
#define TIM_16B_CCMR1_OC1FE_MASK                   TIM3_CCMR1_OC1FE_MASK
#define TIM_16B_CCMR1_OC1FE(x)                     TIM3_CCMR1_OC1FE(x)

#define TIM_16B_CCMR1_CC1S_SHIFT                   TIM3_CCMR1_CC1S_SHIFT
#define TIM_16B_CCMR1_CC1S_MASK                    TIM3_CCMR1_CC1S_MASK
#define TIM_16B_CCMR1_CC1S(x)                      TIM3_CCMR1_CC1S(x)

/*!
 * @brief TIM_16B_CCMR1 Register Bit Definition
 */

#define TIM_16B_CCMR1_IC2F_SHIFT                   TIM3_CCMR1_IC2F_SHIFT
#define TIM_16B_CCMR1_IC2F_MASK                    TIM3_CCMR1_IC2F_MASK
#define TIM_16B_CCMR1_IC2F(x)                      TIM3_CCMR1_IC2F(x)

#define TIM_16B_CCMR1_IC2PSC_SHIFT                 TIM3_CCMR1_IC2PSC_SHIFT
#define TIM_16B_CCMR1_IC2PSC_MASK                  TIM3_CCMR1_IC2PSC_MASK
#define TIM_16B_CCMR1_IC2PSC(x)                    TIM3_CCMR1_IC2PSC(x)

#define TIM_16B_CCMR1_CC2S_SHIFT                   TIM3_CCMR1_CC2S_SHIFT
#define TIM_16B_CCMR1_CC2S_MASK                    TIM3_CCMR1_CC2S_MASK
#define TIM_16B_CCMR1_CC2S(x)                      TIM3_CCMR1_CC2S(x)

#define TIM_16B_CCMR1_IC1F_SHIFT                   TIM3_CCMR1_IC1F_SHIFT
#define TIM_16B_CCMR1_IC1F_MASK                    TIM3_CCMR1_IC1F_MASK
#define TIM_16B_CCMR1_IC1F(x)                      TIM3_CCMR1_IC1F(x)

#define TIM_16B_CCMR1_IC1PSC_SHIFT                 TIM3_CCMR1_IC1PSC_SHIFT
#define TIM_16B_CCMR1_IC1PSC_MASK                  TIM3_CCMR1_IC1PSC_MASK
#define TIM_16B_CCMR1_IC1PSC(x)                    TIM3_CCMR1_IC1PSC(x)

#define TIM_16B_CCMR1_CC1S_SHIFT                   TIM3_CCMR1_CC1S_SHIFT
#define TIM_16B_CCMR1_CC1S_MASK                    TIM3_CCMR1_CC1S_MASK
#define TIM_16B_CCMR1_CC1S(x)                      TIM3_CCMR1_CC1S(x)

/*!
 * @brief TIM_16B_CCMR2 Register Bit Definition
 */

#define TIM_16B_CCMR2_OC4CE_SHIFT                  TIM3_CCMR2_OC4CE_SHIFT
#define TIM_16B_CCMR2_OC4CE_MASK                   TIM3_CCMR2_OC4CE_MASK
#define TIM_16B_CCMR2_OC4CE(x)                     TIM3_CCMR2_OC4CE(x)

#define TIM_16B_CCMR2_OC4M_SHIFT                   TIM3_CCMR2_OC4M_SHIFT
#define TIM_16B_CCMR2_OC4M_MASK                    TIM3_CCMR2_OC4M_MASK
#define TIM_16B_CCMR2_OC4M(x)                      TIM3_CCMR2_OC4M(x)

#define TIM_16B_CCMR2_OC4PE_SHIFT                  TIM3_CCMR2_OC4PE_SHIFT
#define TIM_16B_CCMR2_OC4PE_MASK                   TIM3_CCMR2_OC4PE_MASK
#define TIM_16B_CCMR2_OC4PE(x)                     TIM3_CCMR2_OC4PE(x)

#define TIM_16B_CCMR2_OC4FE_SHIFT                  TIM3_CCMR2_OC4FE_SHIFT
#define TIM_16B_CCMR2_OC4FE_MASK                   TIM3_CCMR2_OC4FE_MASK
#define TIM_16B_CCMR2_OC4FE(x)                     TIM3_CCMR2_OC4FE(x)

#define TIM_16B_CCMR2_CC4S_SHIFT                   TIM3_CCMR2_CC4S_SHIFT
#define TIM_16B_CCMR2_CC4S_MASK                    TIM3_CCMR2_CC4S_MASK
#define TIM_16B_CCMR2_CC4S(x)                      TIM3_CCMR2_CC4S(x)

#define TIM_16B_CCMR2_OC3CE_SHIFT                  TIM3_CCMR2_OC3CE_SHIFT
#define TIM_16B_CCMR2_OC3CE_MASK                   TIM3_CCMR2_OC3CE_MASK
#define TIM_16B_CCMR2_OC3CE(x)                     TIM3_CCMR2_OC3CE(x)

#define TIM_16B_CCMR2_OC3M_SHIFT                   TIM3_CCMR2_OC3M_SHIFT
#define TIM_16B_CCMR2_OC3M_MASK                    TIM3_CCMR2_OC3M_MASK
#define TIM_16B_CCMR2_OC3M(x)                      TIM3_CCMR2_OC3M(x)

#define TIM_16B_CCMR2_OC3PE_SHIFT                  TIM3_CCMR2_OC3PE_SHIFT
#define TIM_16B_CCMR2_OC3PE_MASK                   TIM3_CCMR2_OC3PE_MASK
#define TIM_16B_CCMR2_OC3PE(x)                     TIM3_CCMR2_OC3PE(x)

#define TIM_16B_CCMR2_OC3FE_SHIFT                  TIM3_CCMR2_OC3FE_SHIFT
#define TIM_16B_CCMR2_OC3FE_MASK                   TIM3_CCMR2_OC3FE_MASK
#define TIM_16B_CCMR2_OC3FE(x)                     TIM3_CCMR2_OC3FE(x)

#define TIM_16B_CCMR2_CC3S_SHIFT                   TIM3_CCMR2_CC3S_SHIFT
#define TIM_16B_CCMR2_CC3S_MASK                    TIM3_CCMR2_CC3S_MASK
#define TIM_16B_CCMR2_CC3S(x)                      TIM3_CCMR2_CC3S(x)

/*!
 * @brief TIM_16B_CCMR2 Register Bit Definition
 */

#define TIM_16B_CCMR2_IC4F_SHIFT                   TIM3_CCMR2_IC4F_SHIFT
#define TIM_16B_CCMR2_IC4F_MASK                    TIM3_CCMR2_IC4F_MASK
#define TIM_16B_CCMR2_IC4F(x)                      TIM3_CCMR2_IC4F(x)

#define TIM_16B_CCMR2_IC4PSC_SHIFT                 TIM3_CCMR2_IC4PSC_SHIFT
#define TIM_16B_CCMR2_IC4PSC_MASK                  TIM3_CCMR2_IC4PSC_MASK
#define TIM_16B_CCMR2_IC4PSC(x)                    TIM3_CCMR2_IC4PSC(x)

#define TIM_16B_CCMR2_CC4S_SHIFT                   TIM3_CCMR2_CC4S_SHIFT
#define TIM_16B_CCMR2_CC4S_MASK                    TIM3_CCMR2_CC4S_MASK
#define TIM_16B_CCMR2_CC4S(x)                      TIM3_CCMR2_CC4S(x)

#define TIM_16B_CCMR2_IC3F_SHIFT                   TIM3_CCMR2_IC3F_SHIFT
#define TIM_16B_CCMR2_IC3F_MASK                    TIM3_CCMR2_IC3F_MASK
#define TIM_16B_CCMR2_IC3F(x)                      TIM3_CCMR2_IC3F(x)

#define TIM_16B_CCMR2_IC3PSC_SHIFT                 TIM3_CCMR2_IC3PSC_SHIFT
#define TIM_16B_CCMR2_IC3PSC_MASK                  TIM3_CCMR2_IC3PSC_MASK
#define TIM_16B_CCMR2_IC3PSC(x)                    TIM3_CCMR2_IC3PSC(x)

#define TIM_16B_CCMR2_CC3S_SHIFT                   TIM3_CCMR2_CC3S_SHIFT
#define TIM_16B_CCMR2_CC3S_MASK                    TIM3_CCMR2_CC3S_MASK
#define TIM_16B_CCMR2_CC3S(x)                      TIM3_CCMR2_CC3S(x)

/*!
 * @brief TIM_16B_CCER Register Bit Definition
 */

#define TIM_16B_CCER_CC4NP_SHIFT                   TIM3_CCER_CC4NP_SHIFT
#define TIM_16B_CCER_CC4NP_MASK                    TIM3_CCER_CC4NP_MASK
#define TIM_16B_CCER_CC4NP(x)                      TIM3_CCER_CC4NP(x)

#define TIM_16B_CCER_CC4P_SHIFT                    TIM3_CCER_CC4P_SHIFT
#define TIM_16B_CCER_CC4P_MASK                     TIM3_CCER_CC4P_MASK
#define TIM_16B_CCER_CC4P(x)                       TIM3_CCER_CC4P(x)

#define TIM_16B_CCER_CC4E_SHIFT                    TIM3_CCER_CC4E_SHIFT
#define TIM_16B_CCER_CC4E_MASK                     TIM3_CCER_CC4E_MASK
#define TIM_16B_CCER_CC4E(x)                       TIM3_CCER_CC4E(x)

#define TIM_16B_CCER_CC3NP_SHIFT                   TIM3_CCER_CC3NP_SHIFT
#define TIM_16B_CCER_CC3NP_MASK                    TIM3_CCER_CC3NP_MASK
#define TIM_16B_CCER_CC3NP(x)                      TIM3_CCER_CC3NP(x)

#define TIM_16B_CCER_CC3P_SHIFT                    TIM3_CCER_CC3P_SHIFT
#define TIM_16B_CCER_CC3P_MASK                     TIM3_CCER_CC3P_MASK
#define TIM_16B_CCER_CC3P(x)                       TIM3_CCER_CC3P(x)

#define TIM_16B_CCER_CC3E_SHIFT                    TIM3_CCER_CC3E_SHIFT
#define TIM_16B_CCER_CC3E_MASK                     TIM3_CCER_CC3E_MASK
#define TIM_16B_CCER_CC3E(x)                       TIM3_CCER_CC3E(x)

#define TIM_16B_CCER_CC2NP_SHIFT                   TIM3_CCER_CC2NP_SHIFT
#define TIM_16B_CCER_CC2NP_MASK                    TIM3_CCER_CC2NP_MASK
#define TIM_16B_CCER_CC2NP(x)                      TIM3_CCER_CC2NP(x)

#define TIM_16B_CCER_CC2P_SHIFT                    TIM3_CCER_CC2P_SHIFT
#define TIM_16B_CCER_CC2P_MASK                     TIM3_CCER_CC2P_MASK
#define TIM_16B_CCER_CC2P(x)                       TIM3_CCER_CC2P(x)

#define TIM_16B_CCER_CC2E_SHIFT                    TIM3_CCER_CC2E_SHIFT
#define TIM_16B_CCER_CC2E_MASK                     TIM3_CCER_CC2E_MASK
#define TIM_16B_CCER_CC2E(x)                       TIM3_CCER_CC2E(x)

#define TIM_16B_CCER_CC1NP_SHIFT                   TIM3_CCER_CC1NP_SHIFT
#define TIM_16B_CCER_CC1NP_MASK                    TIM3_CCER_CC1NP_MASK
#define TIM_16B_CCER_CC1NP(x)                      TIM3_CCER_CC1NP(x)

#define TIM_16B_CCER_CC1P_SHIFT                    TIM3_CCER_CC1P_SHIFT
#define TIM_16B_CCER_CC1P_MASK                     TIM3_CCER_CC1P_MASK
#define TIM_16B_CCER_CC1P(x)                       TIM3_CCER_CC1P(x)

#define TIM_16B_CCER_CC1E_SHIFT                    TIM3_CCER_CC1E_SHIFT
#define TIM_16B_CCER_CC1E_MASK                     TIM3_CCER_CC1E_MASK
#define TIM_16B_CCER_CC1E(x)                       TIM3_CCER_CC1E(x)

/*!
 * @brief TIM_16B_CNT Register Bit Definition
 */

#define TIM_16B_CNT_CNT_SHIFT                      TIM3_CNT_CNT_SHIFT
#define TIM_16B_CNT_CNT_MASK                       TIM3_CNT_CNT_MASK
#define TIM_16B_CNT_CNT(x)                         TIM3_CNT_CNT(x)

/*!
 * @brief TIM_16B_PSC Register Bit Definition
 */

#define TIM_16B_PSC_PSC_SHIFT                      TIM3_PSC_PSC_SHIFT
#define TIM_16B_PSC_PSC_MASK                       TIM3_PSC_PSC_MASK
#define TIM_16B_PSC_PSC(x)                         TIM3_PSC_PSC(x)

/*!
 * @brief TIM_16B_ARR Register Bit Definition
 */

#define TIM_16B_ARR_ARR_SHIFT                      TIM3_ARR_ARR_SHIFT
#define TIM_16B_ARR_ARR_MASK                       TIM3_ARR_ARR_MASK
#define TIM_16B_ARR_ARR(x)                         TIM3_ARR_ARR(x)

/*!
 * @brief TIM_16B_CCR1 Register Bit Definition
 */

#define TIM_16B_CCR1_CCR1_SHIFT                    TIM3_CCR1_CCR1_SHIFT
#define TIM_16B_CCR1_CCR1_MASK                     TIM3_CCR1_CCR1_MASK
#define TIM_16B_CCR1_CCR1(x)                       TIM3_CCR1_CCR1(x)

/*!
 * @brief TIM_16B_CCR2 Register Bit Definition
 */

#define TIM_16B_CCR2_CCR2_SHIFT                    TIM3_CCR2_CCR2_SHIFT
#define TIM_16B_CCR2_CCR2_MASK                     TIM3_CCR2_CCR2_MASK
#define TIM_16B_CCR2_CCR2(x)                       TIM3_CCR2_CCR2(x)

/*!
 * @brief TIM_16B_CCR3 Register Bit Definition
 */

#define TIM_16B_CCR3_CCR3_SHIFT                    TIM3_CCR3_CCR3_SHIFT
#define TIM_16B_CCR3_CCR3_MASK                     TIM3_CCR3_CCR3_MASK
#define TIM_16B_CCR3_CCR3(x)                       TIM3_CCR3_CCR3(x)

/*!
 * @brief TIM_16B_CCR4 Register Bit Definition
 */

#define TIM_16B_CCR4_CCR4_SHIFT                    TIM3_CCR4_CCR4_SHIFT
#define TIM_16B_CCR4_CCR4_MASK                     TIM3_CCR4_CCR4_MASK
#define TIM_16B_CCR4_CCR4(x)                       TIM3_CCR4_CCR4(x)

/*!
 * @brief TIM_16B_DCR Register Bit Definition
 */

#define TIM_16B_DCR_DBL_SHIFT                      TIM3_DCR_DBL_SHIFT
#define TIM_16B_DCR_DBL_MASK                       TIM3_DCR_DBL_MASK
#define TIM_16B_DCR_DBL(x)                         TIM3_DCR_DBL(x)

#define TIM_16B_DCR_DBA_SHIFT                      TIM3_DCR_DBA_SHIFT
#define TIM_16B_DCR_DBA_MASK                       TIM3_DCR_DBA_MASK
#define TIM_16B_DCR_DBA(x)                         TIM3_DCR_DBA(x)

/*!
 * @brief TIM_16B_DMAR Register Bit Definition
 */

#define TIM_16B_DMAR_DMAB_SHIFT                    TIM3_DMAR_DMAB_SHIFT
#define TIM_16B_DMAR_DMAB_MASK                     TIM3_DMAR_DMAB_MASK
#define TIM_16B_DMAR_DMAB(x)                       TIM3_DMAR_DMAB(x)

/*!
 * @}
 */ /* end of group TIM_16B_Register_Masks */

/*******************************************************************************
 * TIM_32B Type
 ******************************************************************************/
/*!
 * @addtogroup TIM_32B_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief TIM_32B_CR1 Register Bit Definition
 */

#define TIM_32B_CR1_CKD_SHIFT                      TIM2_CR1_CKD_SHIFT
#define TIM_32B_CR1_CKD_MASK                       TIM2_CR1_CKD_MASK
#define TIM_32B_CR1_CKD(x)                         TIM2_CR1_CKD(x)

#define TIM_32B_CR1_APRE_SHIFT                     TIM2_CR1_APRE_SHIFT
#define TIM_32B_CR1_APRE_MASK                      TIM2_CR1_APRE_MASK
#define TIM_32B_CR1_APRE(x)                        TIM2_CR1_APRE(x)

#define TIM_32B_CR1_CMS_SHIFT                      TIM2_CR1_CMS_SHIFT
#define TIM_32B_CR1_CMS_MASK                       TIM2_CR1_CMS_MASK
#define TIM_32B_CR1_CMS(x)                         TIM2_CR1_CMS(x)

#define TIM_32B_CR1_DIR_SHIFT                      TIM2_CR1_DIR_SHIFT
#define TIM_32B_CR1_DIR_MASK                       TIM2_CR1_DIR_MASK
#define TIM_32B_CR1_DIR(x)                         TIM2_CR1_DIR(x)

#define TIM_32B_CR1_OPM_SHIFT                      TIM2_CR1_OPM_SHIFT
#define TIM_32B_CR1_OPM_MASK                       TIM2_CR1_OPM_MASK
#define TIM_32B_CR1_OPM(x)                         TIM2_CR1_OPM(x)

#define TIM_32B_CR1_URS_SHIFT                      TIM2_CR1_URS_SHIFT
#define TIM_32B_CR1_URS_MASK                       TIM2_CR1_URS_MASK
#define TIM_32B_CR1_URS(x)                         TIM2_CR1_URS(x)

#define TIM_32B_CR1_UDIS_SHIFT                     TIM2_CR1_UDIS_SHIFT
#define TIM_32B_CR1_UDIS_MASK                      TIM2_CR1_UDIS_MASK
#define TIM_32B_CR1_UDIS(x)                        TIM2_CR1_UDIS(x)

#define TIM_32B_CR1_CEN_SHIFT                      TIM2_CR1_CEN_SHIFT
#define TIM_32B_CR1_CEN_MASK                       TIM2_CR1_CEN_MASK
#define TIM_32B_CR1_CEN(x)                         TIM2_CR1_CEN(x)

/*!
 * @brief TIM_32B_CR2 Register Bit Definition
 */

#define TIM_32B_CR2_TI1S_SHIFT                     TIM2_CR2_TI1S_SHIFT
#define TIM_32B_CR2_TI1S_MASK                      TIM2_CR2_TI1S_MASK
#define TIM_32B_CR2_TI1S(x)                        TIM2_CR2_TI1S(x)

#define TIM_32B_CR2_MMS_SHIFT                      TIM2_CR2_MMS_SHIFT
#define TIM_32B_CR2_MMS_MASK                       TIM2_CR2_MMS_MASK
#define TIM_32B_CR2_MMS(x)                         TIM2_CR2_MMS(x)

#define TIM_32B_CR2_CCDS_SHIFT                     TIM2_CR2_CCDS_SHIFT
#define TIM_32B_CR2_CCDS_MASK                      TIM2_CR2_CCDS_MASK
#define TIM_32B_CR2_CCDS(x)                        TIM2_CR2_CCDS(x)

/*!
 * @brief TIM_32B_SMCR Register Bit Definition
 */

#define TIM_32B_SMCR_ETP_SHIFT                     TIM2_SMCR_ETP_SHIFT
#define TIM_32B_SMCR_ETP_MASK                      TIM2_SMCR_ETP_MASK
#define TIM_32B_SMCR_ETP(x)                        TIM2_SMCR_ETP(x)

#define TIM_32B_SMCR_ECE_SHIFT                     TIM2_SMCR_ECE_SHIFT
#define TIM_32B_SMCR_ECE_MASK                      TIM2_SMCR_ECE_MASK
#define TIM_32B_SMCR_ECE(x)                        TIM2_SMCR_ECE(x)

#define TIM_32B_SMCR_ETPS_SHIFT                    TIM2_SMCR_ETPS_SHIFT
#define TIM_32B_SMCR_ETPS_MASK                     TIM2_SMCR_ETPS_MASK
#define TIM_32B_SMCR_ETPS(x)                       TIM2_SMCR_ETPS(x)

#define TIM_32B_SMCR_ETF_SHIFT                     TIM2_SMCR_ETF_SHIFT
#define TIM_32B_SMCR_ETF_MASK                      TIM2_SMCR_ETF_MASK
#define TIM_32B_SMCR_ETF(x)                        TIM2_SMCR_ETF(x)

#define TIM_32B_SMCR_MSM_SHIFT                     TIM2_SMCR_MSM_SHIFT
#define TIM_32B_SMCR_MSM_MASK                      TIM2_SMCR_MSM_MASK
#define TIM_32B_SMCR_MSM(x)                        TIM2_SMCR_MSM(x)

#define TIM_32B_SMCR_TS_SHIFT                      TIM2_SMCR_TS_SHIFT
#define TIM_32B_SMCR_TS_MASK                       TIM2_SMCR_TS_MASK
#define TIM_32B_SMCR_TS(x)                         TIM2_SMCR_TS(x)

#define TIM_32B_SMCR_OCCS_SHIFT                    TIM2_SMCR_OCCS_SHIFT
#define TIM_32B_SMCR_OCCS_MASK                     TIM2_SMCR_OCCS_MASK
#define TIM_32B_SMCR_OCCS(x)                       TIM2_SMCR_OCCS(x)

#define TIM_32B_SMCR_SMS_SHIFT                     TIM2_SMCR_SMS_SHIFT
#define TIM_32B_SMCR_SMS_MASK                      TIM2_SMCR_SMS_MASK
#define TIM_32B_SMCR_SMS(x)                        TIM2_SMCR_SMS(x)

/*!
 * @brief TIM_32B_DIER Register Bit Definition
 */

#define TIM_32B_DIER_TDE_SHIFT                     TIM2_DIER_TDE_SHIFT
#define TIM_32B_DIER_TDE_MASK                      TIM2_DIER_TDE_MASK
#define TIM_32B_DIER_TDE(x)                        TIM2_DIER_TDE(x)

#define TIM_32B_DIER_CC4DE_SHIFT                   TIM2_DIER_CC4DE_SHIFT
#define TIM_32B_DIER_CC4DE_MASK                    TIM2_DIER_CC4DE_MASK
#define TIM_32B_DIER_CC4DE(x)                      TIM2_DIER_CC4DE(x)

#define TIM_32B_DIER_CC3DE_SHIFT                   TIM2_DIER_CC3DE_SHIFT
#define TIM_32B_DIER_CC3DE_MASK                    TIM2_DIER_CC3DE_MASK
#define TIM_32B_DIER_CC3DE(x)                      TIM2_DIER_CC3DE(x)

#define TIM_32B_DIER_CC2DE_SHIFT                   TIM2_DIER_CC2DE_SHIFT
#define TIM_32B_DIER_CC2DE_MASK                    TIM2_DIER_CC2DE_MASK
#define TIM_32B_DIER_CC2DE(x)                      TIM2_DIER_CC2DE(x)

#define TIM_32B_DIER_CC1DE_SHIFT                   TIM2_DIER_CC1DE_SHIFT
#define TIM_32B_DIER_CC1DE_MASK                    TIM2_DIER_CC1DE_MASK
#define TIM_32B_DIER_CC1DE(x)                      TIM2_DIER_CC1DE(x)

#define TIM_32B_DIER_UDE_SHIFT                     TIM2_DIER_UDE_SHIFT
#define TIM_32B_DIER_UDE_MASK                      TIM2_DIER_UDE_MASK
#define TIM_32B_DIER_UDE(x)                        TIM2_DIER_UDE(x)

#define TIM_32B_DIER_TIE_SHIFT                     TIM2_DIER_TIE_SHIFT
#define TIM_32B_DIER_TIE_MASK                      TIM2_DIER_TIE_MASK
#define TIM_32B_DIER_TIE(x)                        TIM2_DIER_TIE(x)

#define TIM_32B_DIER_CC4IE_SHIFT                   TIM2_DIER_CC4IE_SHIFT
#define TIM_32B_DIER_CC4IE_MASK                    TIM2_DIER_CC4IE_MASK
#define TIM_32B_DIER_CC4IE(x)                      TIM2_DIER_CC4IE(x)

#define TIM_32B_DIER_CC3IE_SHIFT                   TIM2_DIER_CC3IE_SHIFT
#define TIM_32B_DIER_CC3IE_MASK                    TIM2_DIER_CC3IE_MASK
#define TIM_32B_DIER_CC3IE(x)                      TIM2_DIER_CC3IE(x)

#define TIM_32B_DIER_CC2IE_SHIFT                   TIM2_DIER_CC2IE_SHIFT
#define TIM_32B_DIER_CC2IE_MASK                    TIM2_DIER_CC2IE_MASK
#define TIM_32B_DIER_CC2IE(x)                      TIM2_DIER_CC2IE(x)

#define TIM_32B_DIER_CC1IE_SHIFT                   TIM2_DIER_CC1IE_SHIFT
#define TIM_32B_DIER_CC1IE_MASK                    TIM2_DIER_CC1IE_MASK
#define TIM_32B_DIER_CC1IE(x)                      TIM2_DIER_CC1IE(x)

#define TIM_32B_DIER_UIE_SHIFT                     TIM2_DIER_UIE_SHIFT
#define TIM_32B_DIER_UIE_MASK                      TIM2_DIER_UIE_MASK
#define TIM_32B_DIER_UIE(x)                        TIM2_DIER_UIE(x)

/*!
 * @brief TIM_32B_SR Register Bit Definition
 */

#define TIM_32B_SR_CC4OF_SHIFT                     TIM2_SR_CC4OF_SHIFT
#define TIM_32B_SR_CC4OF_MASK                      TIM2_SR_CC4OF_MASK
#define TIM_32B_SR_CC4OF(x)                        TIM2_SR_CC4OF(x)

#define TIM_32B_SR_CC3OF_SHIFT                     TIM2_SR_CC3OF_SHIFT
#define TIM_32B_SR_CC3OF_MASK                      TIM2_SR_CC3OF_MASK
#define TIM_32B_SR_CC3OF(x)                        TIM2_SR_CC3OF(x)

#define TIM_32B_SR_CC2OF_SHIFT                     TIM2_SR_CC2OF_SHIFT
#define TIM_32B_SR_CC2OF_MASK                      TIM2_SR_CC2OF_MASK
#define TIM_32B_SR_CC2OF(x)                        TIM2_SR_CC2OF(x)

#define TIM_32B_SR_CC1OF_SHIFT                     TIM2_SR_CC1OF_SHIFT
#define TIM_32B_SR_CC1OF_MASK                      TIM2_SR_CC1OF_MASK
#define TIM_32B_SR_CC1OF(x)                        TIM2_SR_CC1OF(x)

#define TIM_32B_SR_TIF_SHIFT                       TIM2_SR_TIF_SHIFT
#define TIM_32B_SR_TIF_MASK                        TIM2_SR_TIF_MASK
#define TIM_32B_SR_TIF(x)                          TIM2_SR_TIF(x)

#define TIM_32B_SR_CC4IF_SHIFT                     TIM2_SR_CC4IF_SHIFT
#define TIM_32B_SR_CC4IF_MASK                      TIM2_SR_CC4IF_MASK
#define TIM_32B_SR_CC4IF(x)                        TIM2_SR_CC4IF(x)

#define TIM_32B_SR_CC3IF_SHIFT                     TIM2_SR_CC3IF_SHIFT
#define TIM_32B_SR_CC3IF_MASK                      TIM2_SR_CC3IF_MASK
#define TIM_32B_SR_CC3IF(x)                        TIM2_SR_CC3IF(x)

#define TIM_32B_SR_CC2IF_SHIFT                     TIM2_SR_CC2IF_SHIFT
#define TIM_32B_SR_CC2IF_MASK                      TIM2_SR_CC2IF_MASK
#define TIM_32B_SR_CC2IF(x)                        TIM2_SR_CC2IF(x)

#define TIM_32B_SR_CC1IF_SHIFT                     TIM2_SR_CC1IF_SHIFT
#define TIM_32B_SR_CC1IF_MASK                      TIM2_SR_CC1IF_MASK
#define TIM_32B_SR_CC1IF(x)                        TIM2_SR_CC1IF(x)

#define TIM_32B_SR_UIF_SHIFT                       TIM2_SR_UIF_SHIFT
#define TIM_32B_SR_UIF_MASK                        TIM2_SR_UIF_MASK
#define TIM_32B_SR_UIF(x)                          TIM2_SR_UIF(x)

/*!
 * @brief TIM_32B_EGR Register Bit Definition
 */

#define TIM_32B_EGR_TG_SHIFT                       TIM2_EGR_TG_SHIFT
#define TIM_32B_EGR_TG_MASK                        TIM2_EGR_TG_MASK
#define TIM_32B_EGR_TG(x)                          TIM2_EGR_TG(x)

#define TIM_32B_EGR_COMG_SHIFT                     TIM2_EGR_COMG_SHIFT
#define TIM_32B_EGR_COMG_MASK                      TIM2_EGR_COMG_MASK
#define TIM_32B_EGR_COMG(x)                        TIM2_EGR_COMG(x)

#define TIM_32B_EGR_CC4G_SHIFT                     TIM2_EGR_CC4G_SHIFT
#define TIM_32B_EGR_CC4G_MASK                      TIM2_EGR_CC4G_MASK
#define TIM_32B_EGR_CC4G(x)                        TIM2_EGR_CC4G(x)

#define TIM_32B_EGR_CC3G_SHIFT                     TIM2_EGR_CC3G_SHIFT
#define TIM_32B_EGR_CC3G_MASK                      TIM2_EGR_CC3G_MASK
#define TIM_32B_EGR_CC3G(x)                        TIM2_EGR_CC3G(x)

#define TIM_32B_EGR_CC2G_SHIFT                     TIM2_EGR_CC2G_SHIFT
#define TIM_32B_EGR_CC2G_MASK                      TIM2_EGR_CC2G_MASK
#define TIM_32B_EGR_CC2G(x)                        TIM2_EGR_CC2G(x)

#define TIM_32B_EGR_CC1G_SHIFT                     TIM2_EGR_CC1G_SHIFT
#define TIM_32B_EGR_CC1G_MASK                      TIM2_EGR_CC1G_MASK
#define TIM_32B_EGR_CC1G(x)                        TIM2_EGR_CC1G(x)

#define TIM_32B_EGR_UG_SHIFT                       TIM2_EGR_UG_SHIFT
#define TIM_32B_EGR_UG_MASK                        TIM2_EGR_UG_MASK
#define TIM_32B_EGR_UG(x)                          TIM2_EGR_UG(x)

/*!
 * @brief TIM_32B_CCMR1 Register Bit Definition
 */

#define TIM_32B_CCMR1_OC2CE_SHIFT                  TIM2_CCMR1_OC2CE_SHIFT
#define TIM_32B_CCMR1_OC2CE_MASK                   TIM2_CCMR1_OC2CE_MASK
#define TIM_32B_CCMR1_OC2CE(x)                     TIM2_CCMR1_OC2CE(x)

#define TIM_32B_CCMR1_OC2M_SHIFT                   TIM2_CCMR1_OC2M_SHIFT
#define TIM_32B_CCMR1_OC2M_MASK                    TIM2_CCMR1_OC2M_MASK
#define TIM_32B_CCMR1_OC2M(x)                      TIM2_CCMR1_OC2M(x)

#define TIM_32B_CCMR1_OC2PE_SHIFT                  TIM2_CCMR1_OC2PE_SHIFT
#define TIM_32B_CCMR1_OC2PE_MASK                   TIM2_CCMR1_OC2PE_MASK
#define TIM_32B_CCMR1_OC2PE(x)                     TIM2_CCMR1_OC2PE(x)

#define TIM_32B_CCMR1_OC2FE_SHIFT                  TIM2_CCMR1_OC2FE_SHIFT
#define TIM_32B_CCMR1_OC2FE_MASK                   TIM2_CCMR1_OC2FE_MASK
#define TIM_32B_CCMR1_OC2FE(x)                     TIM2_CCMR1_OC2FE(x)

#define TIM_32B_CCMR1_CC2S_SHIFT                   TIM2_CCMR1_CC2S_SHIFT
#define TIM_32B_CCMR1_CC2S_MASK                    TIM2_CCMR1_CC2S_MASK
#define TIM_32B_CCMR1_CC2S(x)                      TIM2_CCMR1_CC2S(x)

#define TIM_32B_CCMR1_OC1CE_SHIFT                  TIM2_CCMR1_OC1CE_SHIFT
#define TIM_32B_CCMR1_OC1CE_MASK                   TIM2_CCMR1_OC1CE_MASK
#define TIM_32B_CCMR1_OC1CE(x)                     TIM2_CCMR1_OC1CE(x)

#define TIM_32B_CCMR1_OC1M_SHIFT                   TIM2_CCMR1_OC1M_SHIFT
#define TIM_32B_CCMR1_OC1M_MASK                    TIM2_CCMR1_OC1M_MASK
#define TIM_32B_CCMR1_OC1M(x)                      TIM2_CCMR1_OC1M(x)

#define TIM_32B_CCMR1_OC1PE_SHIFT                  TIM2_CCMR1_OC1PE_SHIFT
#define TIM_32B_CCMR1_OC1PE_MASK                   TIM2_CCMR1_OC1PE_MASK
#define TIM_32B_CCMR1_OC1PE(x)                     TIM2_CCMR1_OC1PE(x)

#define TIM_32B_CCMR1_OC1FE_SHIFT                  TIM2_CCMR1_OC1FE_SHIFT
#define TIM_32B_CCMR1_OC1FE_MASK                   TIM2_CCMR1_OC1FE_MASK
#define TIM_32B_CCMR1_OC1FE(x)                     TIM2_CCMR1_OC1FE(x)

#define TIM_32B_CCMR1_CC1S_SHIFT                   TIM2_CCMR1_CC1S_SHIFT
#define TIM_32B_CCMR1_CC1S_MASK                    TIM2_CCMR1_CC1S_MASK
#define TIM_32B_CCMR1_CC1S(x)                      TIM2_CCMR1_CC1S(x)

/*!
 * @brief TIM_32B_CCMR1 Register Bit Definition
 */

#define TIM_32B_CCMR1_IC2F_SHIFT                   TIM2_CCMR1_IC2F_SHIFT
#define TIM_32B_CCMR1_IC2F_MASK                    TIM2_CCMR1_IC2F_MASK
#define TIM_32B_CCMR1_IC2F(x)                      TIM2_CCMR1_IC2F(x)

#define TIM_32B_CCMR1_IC2PSC_SHIFT                 TIM2_CCMR1_IC2PSC_SHIFT
#define TIM_32B_CCMR1_IC2PSC_MASK                  TIM2_CCMR1_IC2PSC_MASK
#define TIM_32B_CCMR1_IC2PSC(x)                    TIM2_CCMR1_IC2PSC(x)

#define TIM_32B_CCMR1_CC2S_SHIFT                   TIM2_CCMR1_CC2S_SHIFT
#define TIM_32B_CCMR1_CC2S_MASK                    TIM2_CCMR1_CC2S_MASK
#define TIM_32B_CCMR1_CC2S(x)                      TIM2_CCMR1_CC2S(x)

#define TIM_32B_CCMR1_IC1F_SHIFT                   TIM2_CCMR1_IC1F_SHIFT
#define TIM_32B_CCMR1_IC1F_MASK                    TIM2_CCMR1_IC1F_MASK
#define TIM_32B_CCMR1_IC1F(x)                      TIM2_CCMR1_IC1F(x)

#define TIM_32B_CCMR1_IC1PSC_SHIFT                 TIM2_CCMR1_IC1PSC_SHIFT
#define TIM_32B_CCMR1_IC1PSC_MASK                  TIM2_CCMR1_IC1PSC_MASK
#define TIM_32B_CCMR1_IC1PSC(x)                    TIM2_CCMR1_IC1PSC(x)

#define TIM_32B_CCMR1_CC1S_SHIFT                   TIM2_CCMR1_CC1S_SHIFT
#define TIM_32B_CCMR1_CC1S_MASK                    TIM2_CCMR1_CC1S_MASK
#define TIM_32B_CCMR1_CC1S(x)                      TIM2_CCMR1_CC1S(x)

/*!
 * @brief TIM_32B_CCMR2 Register Bit Definition
 */

#define TIM_32B_CCMR2_OC4CE_SHIFT                  TIM2_CCMR2_OC4CE_SHIFT
#define TIM_32B_CCMR2_OC4CE_MASK                   TIM2_CCMR2_OC4CE_MASK
#define TIM_32B_CCMR2_OC4CE(x)                     TIM2_CCMR2_OC4CE(x)

#define TIM_32B_CCMR2_OC4M_SHIFT                   TIM2_CCMR2_OC4M_SHIFT
#define TIM_32B_CCMR2_OC4M_MASK                    TIM2_CCMR2_OC4M_MASK
#define TIM_32B_CCMR2_OC4M(x)                      TIM2_CCMR2_OC4M(x)

#define TIM_32B_CCMR2_OC4PE_SHIFT                  TIM2_CCMR2_OC4PE_SHIFT
#define TIM_32B_CCMR2_OC4PE_MASK                   TIM2_CCMR2_OC4PE_MASK
#define TIM_32B_CCMR2_OC4PE(x)                     TIM2_CCMR2_OC4PE(x)

#define TIM_32B_CCMR2_OC4FE_SHIFT                  TIM2_CCMR2_OC4FE_SHIFT
#define TIM_32B_CCMR2_OC4FE_MASK                   TIM2_CCMR2_OC4FE_MASK
#define TIM_32B_CCMR2_OC4FE(x)                     TIM2_CCMR2_OC4FE(x)

#define TIM_32B_CCMR2_CC4S_SHIFT                   TIM2_CCMR2_CC4S_SHIFT
#define TIM_32B_CCMR2_CC4S_MASK                    TIM2_CCMR2_CC4S_MASK
#define TIM_32B_CCMR2_CC4S(x)                      TIM2_CCMR2_CC4S(x)

#define TIM_32B_CCMR2_OC3CE_SHIFT                  TIM2_CCMR2_OC3CE_SHIFT
#define TIM_32B_CCMR2_OC3CE_MASK                   TIM2_CCMR2_OC3CE_MASK
#define TIM_32B_CCMR2_OC3CE(x)                     TIM2_CCMR2_OC3CE(x)

#define TIM_32B_CCMR2_OC3M_SHIFT                   TIM2_CCMR2_OC3M_SHIFT
#define TIM_32B_CCMR2_OC3M_MASK                    TIM2_CCMR2_OC3M_MASK
#define TIM_32B_CCMR2_OC3M(x)                      TIM2_CCMR2_OC3M(x)

#define TIM_32B_CCMR2_OC3PE_SHIFT                  TIM2_CCMR2_OC3PE_SHIFT
#define TIM_32B_CCMR2_OC3PE_MASK                   TIM2_CCMR2_OC3PE_MASK
#define TIM_32B_CCMR2_OC3PE(x)                     TIM2_CCMR2_OC3PE(x)

#define TIM_32B_CCMR2_OC3FE_SHIFT                  TIM2_CCMR2_OC3FE_SHIFT
#define TIM_32B_CCMR2_OC3FE_MASK                   TIM2_CCMR2_OC3FE_MASK
#define TIM_32B_CCMR2_OC3FE(x)                     TIM2_CCMR2_OC3FE(x)

#define TIM_32B_CCMR2_CC3S_SHIFT                   TIM2_CCMR2_CC3S_SHIFT
#define TIM_32B_CCMR2_CC3S_MASK                    TIM2_CCMR2_CC3S_MASK
#define TIM_32B_CCMR2_CC3S(x)                      TIM2_CCMR2_CC3S(x)

/*!
 * @brief TIM_32B_CCMR2 Register Bit Definition
 */

#define TIM_32B_CCMR2_IC4F_SHIFT                   TIM2_CCMR2_IC4F_SHIFT
#define TIM_32B_CCMR2_IC4F_MASK                    TIM2_CCMR2_IC4F_MASK
#define TIM_32B_CCMR2_IC4F(x)                      TIM2_CCMR2_IC4F(x)

#define TIM_32B_CCMR2_IC4PSC_SHIFT                 TIM2_CCMR2_IC4PSC_SHIFT
#define TIM_32B_CCMR2_IC4PSC_MASK                  TIM2_CCMR2_IC4PSC_MASK
#define TIM_32B_CCMR2_IC4PSC(x)                    TIM2_CCMR2_IC4PSC(x)

#define TIM_32B_CCMR2_CC4S_SHIFT                   TIM2_CCMR2_CC4S_SHIFT
#define TIM_32B_CCMR2_CC4S_MASK                    TIM2_CCMR2_CC4S_MASK
#define TIM_32B_CCMR2_CC4S(x)                      TIM2_CCMR2_CC4S(x)

#define TIM_32B_CCMR2_IC3F_SHIFT                   TIM2_CCMR2_IC3F_SHIFT
#define TIM_32B_CCMR2_IC3F_MASK                    TIM2_CCMR2_IC3F_MASK
#define TIM_32B_CCMR2_IC3F(x)                      TIM2_CCMR2_IC3F(x)

#define TIM_32B_CCMR2_IC3PSC_SHIFT                 TIM2_CCMR2_IC3PSC_SHIFT
#define TIM_32B_CCMR2_IC3PSC_MASK                  TIM2_CCMR2_IC3PSC_MASK
#define TIM_32B_CCMR2_IC3PSC(x)                    TIM2_CCMR2_IC3PSC(x)

#define TIM_32B_CCMR2_CC3S_SHIFT                   TIM2_CCMR2_CC3S_SHIFT
#define TIM_32B_CCMR2_CC3S_MASK                    TIM2_CCMR2_CC3S_MASK
#define TIM_32B_CCMR2_CC3S(x)                      TIM2_CCMR2_CC3S(x)

/*!
 * @brief TIM_32B_CCER Register Bit Definition
 */

#define TIM_32B_CCER_CC4NP_SHIFT                   TIM2_CCER_CC4NP_SHIFT
#define TIM_32B_CCER_CC4NP_MASK                    TIM2_CCER_CC4NP_MASK
#define TIM_32B_CCER_CC4NP(x)                      TIM2_CCER_CC4NP(x)

#define TIM_32B_CCER_CC4P_SHIFT                    TIM2_CCER_CC4P_SHIFT
#define TIM_32B_CCER_CC4P_MASK                     TIM2_CCER_CC4P_MASK
#define TIM_32B_CCER_CC4P(x)                       TIM2_CCER_CC4P(x)

#define TIM_32B_CCER_CC4E_SHIFT                    TIM2_CCER_CC4E_SHIFT
#define TIM_32B_CCER_CC4E_MASK                     TIM2_CCER_CC4E_MASK
#define TIM_32B_CCER_CC4E(x)                       TIM2_CCER_CC4E(x)

#define TIM_32B_CCER_CC3NP_SHIFT                   TIM2_CCER_CC3NP_SHIFT
#define TIM_32B_CCER_CC3NP_MASK                    TIM2_CCER_CC3NP_MASK
#define TIM_32B_CCER_CC3NP(x)                      TIM2_CCER_CC3NP(x)

#define TIM_32B_CCER_CC3P_SHIFT                    TIM2_CCER_CC3P_SHIFT
#define TIM_32B_CCER_CC3P_MASK                     TIM2_CCER_CC3P_MASK
#define TIM_32B_CCER_CC3P(x)                       TIM2_CCER_CC3P(x)

#define TIM_32B_CCER_CC3E_SHIFT                    TIM2_CCER_CC3E_SHIFT
#define TIM_32B_CCER_CC3E_MASK                     TIM2_CCER_CC3E_MASK
#define TIM_32B_CCER_CC3E(x)                       TIM2_CCER_CC3E(x)

#define TIM_32B_CCER_CC2NP_SHIFT                   TIM2_CCER_CC2NP_SHIFT
#define TIM_32B_CCER_CC2NP_MASK                    TIM2_CCER_CC2NP_MASK
#define TIM_32B_CCER_CC2NP(x)                      TIM2_CCER_CC2NP(x)

#define TIM_32B_CCER_CC2P_SHIFT                    TIM2_CCER_CC2P_SHIFT
#define TIM_32B_CCER_CC2P_MASK                     TIM2_CCER_CC2P_MASK
#define TIM_32B_CCER_CC2P(x)                       TIM2_CCER_CC2P(x)

#define TIM_32B_CCER_CC2E_SHIFT                    TIM2_CCER_CC2E_SHIFT
#define TIM_32B_CCER_CC2E_MASK                     TIM2_CCER_CC2E_MASK
#define TIM_32B_CCER_CC2E(x)                       TIM2_CCER_CC2E(x)

#define TIM_32B_CCER_CC1NP_SHIFT                   TIM2_CCER_CC1NP_SHIFT
#define TIM_32B_CCER_CC1NP_MASK                    TIM2_CCER_CC1NP_MASK
#define TIM_32B_CCER_CC1NP(x)                      TIM2_CCER_CC1NP(x)

#define TIM_32B_CCER_CC1P_SHIFT                    TIM2_CCER_CC1P_SHIFT
#define TIM_32B_CCER_CC1P_MASK                     TIM2_CCER_CC1P_MASK
#define TIM_32B_CCER_CC1P(x)                       TIM2_CCER_CC1P(x)

#define TIM_32B_CCER_CC1E_SHIFT                    TIM2_CCER_CC1E_SHIFT
#define TIM_32B_CCER_CC1E_MASK                     TIM2_CCER_CC1E_MASK
#define TIM_32B_CCER_CC1E(x)                       TIM2_CCER_CC1E(x)

/*!
 * @brief TIM_32B_CNT Register Bit Definition
 */

#define TIM_32B_CNT_CNT_SHIFT                      TIM2_CNT_CNT_SHIFT
#define TIM_32B_CNT_CNT_MASK                       TIM2_CNT_CNT_MASK
#define TIM_32B_CNT_CNT(x)                         TIM2_CNT_CNT(x)

/*!
 * @brief TIM_32B_PSC Register Bit Definition
 */

#define TIM_32B_PSC_PSC_SHIFT                      TIM2_PSC_PSC_SHIFT
#define TIM_32B_PSC_PSC_MASK                       TIM2_PSC_PSC_MASK
#define TIM_32B_PSC_PSC(x)                         TIM2_PSC_PSC(x)

/*!
 * @brief TIM_32B_ARR Register Bit Definition
 */

#define TIM_32B_ARR_ARR_SHIFT                      TIM2_ARR_ARR_SHIFT
#define TIM_32B_ARR_ARR_MASK                       TIM2_ARR_ARR_MASK
#define TIM_32B_ARR_ARR(x)                         TIM2_ARR_ARR(x)

/*!
 * @brief TIM_32B_CCR1 Register Bit Definition
 */

#define TIM_32B_CCR1_CCR1_SHIFT                    TIM2_CCR1_CCR1_SHIFT
#define TIM_32B_CCR1_CCR1_MASK                     TIM2_CCR1_CCR1_MASK
#define TIM_32B_CCR1_CCR1(x)                       TIM2_CCR1_CCR1(x)

/*!
 * @brief TIM_32B_CCR2 Register Bit Definition
 */

#define TIM_32B_CCR2_CCR2_SHIFT                    TIM2_CCR2_CCR2_SHIFT
#define TIM_32B_CCR2_CCR2_MASK                     TIM2_CCR2_CCR2_MASK
#define TIM_32B_CCR2_CCR2(x)                       TIM2_CCR2_CCR2(x)

/*!
 * @brief TIM_32B_CCR3 Register Bit Definition
 */

#define TIM_32B_CCR3_CCR3_SHIFT                    TIM2_CCR3_CCR3_SHIFT
#define TIM_32B_CCR3_CCR3_MASK                     TIM2_CCR3_CCR3_MASK
#define TIM_32B_CCR3_CCR3(x)                       TIM2_CCR3_CCR3(x)

/*!
 * @brief TIM_32B_CCR4 Register Bit Definition
 */

#define TIM_32B_CCR4_CCR4_SHIFT                    TIM2_CCR4_CCR4_SHIFT
#define TIM_32B_CCR4_CCR4_MASK                     TIM2_CCR4_CCR4_MASK
#define TIM_32B_CCR4_CCR4(x)                       TIM2_CCR4_CCR4(x)

/*!
 * @brief TIM_32B_DCR Register Bit Definition
 */

#define TIM_32B_DCR_DBL_SHIFT                      TIM2_DCR_DBL_SHIFT
#define TIM_32B_DCR_DBL_MASK                       TIM2_DCR_DBL_MASK
#define TIM_32B_DCR_DBL(x)                         TIM2_DCR_DBL(x)

#define TIM_32B_DCR_DBA_SHIFT                      TIM2_DCR_DBA_SHIFT
#define TIM_32B_DCR_DBA_MASK                       TIM2_DCR_DBA_MASK
#define TIM_32B_DCR_DBA(x)                         TIM2_DCR_DBA(x)

/*!
 * @brief TIM_32B_DMAR Register Bit Definition
 */

#define TIM_32B_DMAR_DMAB_SHIFT                    TIM2_DMAR_DMAB_SHIFT
#define TIM_32B_DMAR_DMAB_MASK                     TIM2_DMAR_DMAB_MASK
#define TIM_32B_DMAR_DMAB(x)                       TIM2_DMAR_DMAB(x)

/*!
 * @brief TIM_32B_OR Register Bit Definition
 */

#define TIM_32B_OR_TI4RMP_SHIFT                    TIM2_OR_TI4RMP_SHIFT
#define TIM_32B_OR_TI4RMP_MASK                     TIM2_OR_TI4RMP_MASK
#define TIM_32B_OR_TI4RMP(x)                       TIM2_OR_TI4RMP(x)

#define TIM_32B_OR_ETRRMP_SHIFT                    TIM2_OR_ETRRMP_SHIFT
#define TIM_32B_OR_ETRRMP_MASK                     TIM2_OR_ETRRMP_MASK
#define TIM_32B_OR_ETRRMP(x)                       TIM2_OR_ETRRMP(x)

/*!
 * @}
 */ /* end of group TIM_32B_Register_Masks */

/*******************************************************************************
 * TIM6 Type
 ******************************************************************************/

/*!
 * @addtogroup TIM_BASIC_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief TIM_BASIC_CR1 Register Bit Definition
 */

#define TIM_BASIC_CR1_APRE_SHIFT                     TIM6_CR1_APRE_SHIFT
#define TIM_BASIC_CR1_APRE_MASK                      TIM6_CR1_APRE_MASK
#define TIM_BASIC_CR1_APRE(x)                        TIM6_CR1_APRE(x)

#define TIM_BASIC_CR1_OPM_SHIFT                      TIM6_CR1_OPM_SHIFT
#define TIM_BASIC_CR1_OPM_MASK                       TIM6_CR1_OPM_MASK
#define TIM_BASIC_CR1_OPM(x)                         TIM6_CR1_OPM(x)

#define TIM_BASIC_CR1_URS_SHIFT                      TIM6_CR1_URS_SHIFT
#define TIM_BASIC_CR1_URS_MASK                       TIM6_CR1_URS_MASK
#define TIM_BASIC_CR1_URS(x)                         TIM6_CR1_URS(x)

#define TIM_BASIC_CR1_UDIS_SHIFT                     TIM6_CR1_UDIS_SHIFT
#define TIM_BASIC_CR1_UDIS_MASK                      TIM6_CR1_UDIS_MASK
#define TIM_BASIC_CR1_UDIS(x)                        TIM6_CR1_UDIS(x)

#define TIM_BASIC_CR1_CEN_SHIFT                      TIM6_CR1_CEN_SHIFT
#define TIM_BASIC_CR1_CEN_MASK                       TIM6_CR1_CEN_MASK
#define TIM_BASIC_CR1_CEN(x)                         TIM6_CR1_CEN(x)

/*!
 * @brief TIM_BASIC_DIER Register Bit Definition
 */

#define TIM_BASIC_DIER_UDE_SHIFT                     TIM6_DIER_UDE_SHIFT
#define TIM_BASIC_DIER_UDE_MASK                      TIM6_DIER_UDE_MASK
#define TIM_BASIC_DIER_UDE(x)                        TIM6_DIER_UDE(x)

#define TIM_BASIC_DIER_UIE_SHIFT                     TIM6_DIER_UIE_SHIFT
#define TIM_BASIC_DIER_UIE_MASK                      TIM6_DIER_UIE_MASK
#define TIM_BASIC_DIER_UIE(x)                        TIM6_DIER_UIE(x)

/*!
 * @brief TIM_BASIC_SR Register Bit Definition
 */

#define TIM_BASIC_SR_UIF_SHIFT                       TIM6_SR_UIF_SHIFT
#define TIM_BASIC_SR_UIF_MASK                        TIM6_SR_UIF_MASK
#define TIM_BASIC_SR_UIF(x)                          TIM6_SR_UIF(x)

/*!
 * @brief TIM_BASIC_EGR Register Bit Definition
 */

#define TIM_BASIC_EGR_UG_SHIFT                       TIM6_EGR_UG_SHIFT
#define TIM_BASIC_EGR_UG_MASK                        TIM6_EGR_UG_MASK
#define TIM_BASIC_EGR_UG(x)                          TIM6_EGR_UG(x)

/*!
 * @brief TIM_BASIC_CNT Register Bit Definition
 */

#define TIM_BASIC_CNT_CNT_SHIFT                      TIM6_CNT_CNT_SHIFT
#define TIM_BASIC_CNT_CNT_MASK                       TIM6_CNT_CNT_MASK
#define TIM_BASIC_CNT_CNT(x)                         TIM6_CNT_CNT(x)

/*!
 * @brief TIM_BASIC_PSC Register Bit Definition
 */

#define TIM_BASIC_PSC_PSC_SHIFT                      TIM6_PSC_PSC_SHIFT
#define TIM_BASIC_PSC_PSC_MASK                       TIM6_PSC_PSC_MASK
#define TIM_BASIC_PSC_PSC(x)                         TIM6_PSC_PSC(x)

/*!
 * @brief TIM_BASIC_ARR Register Bit Definition
 */

#define TIM_BASIC_ARR_ARR_SHIFT                      TIM6_ARR_ARR_SHIFT
#define TIM_BASIC_ARR_ARR_MASK                       TIM6_ARR_ARR_MASK
#define TIM_BASIC_ARR_ARR(x)                         TIM6_ARR_ARR(x)

/*!
 * @}
 */ /* end of group TIM_BASIC_Register_Masks */

 #endif /* __MM32F3277G_FEATURES_H__ */
