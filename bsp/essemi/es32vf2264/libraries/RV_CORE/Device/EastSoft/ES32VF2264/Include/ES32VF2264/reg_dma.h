/**********************************************************************************
 *
 * @file    reg_dma.h
 * @brief   DMA Head File
 *
 * @date    19 July 2022
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          12 July 2022    Lisq            the first version
 *          19 July 2022    Shiwa           the first version
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

#ifndef __REG_DMA_H__
#define __REG_DMA_H__

#define DMA_CHANNELS 7

#define DMA_CH0_TC_POS  0U
#define DMA_CH0_TC_MSK  BIT(DMA_CH0_TC_POS)
#define DMA_CH0_HT_POS  1U
#define DMA_CH0_HT_MSK  BIT(DMA_CH0_HT_POS)

#define DMA_CH1_TC_POS  2U
#define DMA_CH1_TC_MSK  BIT(DMA_CH1_TC_POS)
#define DMA_CH1_HT_POS  3U
#define DMA_CH1_HT_MSK  BIT(DMA_CH1_HT_POS)

#define DMA_CH2_TC_POS  4U
#define DMA_CH2_TC_MSK  BIT(DMA_CH2_TC_POS)
#define DMA_CH2_HT_POS  5U
#define DMA_CH2_HT_MSK  BIT(DMA_CH2_HT_POS)

#define DMA_CH3_TC_POS  6U
#define DMA_CH3_TC_MSK  BIT(DMA_CH3_TC_POS)
#define DMA_CH3_HT_POS  7U
#define DMA_CH3_HT_MSK  BIT(DMA_CH3_HT_POS)

#define DMA_CH4_TC_POS  8U
#define DMA_CH4_TC_MSK  BIT(DMA_CH4_TC_POS)
#define DMA_CH4_HT_POS  9U
#define DMA_CH4_HT_MSK  BIT(DMA_CH4_HT_POS)

#define DMA_CH5_TC_POS  10U
#define DMA_CH5_TC_MSK  BIT(DMA_CH5_TC_POS)
#define DMA_CH5_HT_POS  11U
#define DMA_CH5_HT_MSK  BIT(DMA_CH5_HT_POS)

#define DMA_CH6_TC_POS  12U
#define DMA_CH6_TC_MSK  BIT(DMA_CH6_TC_POS)
#define DMA_CH6_HT_POS  13U
#define DMA_CH6_HT_MSK  BIT(DMA_CH6_HT_POS)

#define DMA_SELCON_MSEL_POSS    8U
#define DMA_SELCON_MSEL_POSE    12U
#define DMA_SELCON_MSEL_MSK     BITS(DMA_SELCON_MSEL_POSS,DMA_SELCON_MSEL_POSE)

#define DMA_SELCON_MSIGSEL_POSS 0U
#define DMA_SELCON_MSIGSEL_POSE 3U
#define DMA_SELCON_MSIGSEL_MSK  BITS(DMA_SELCON_MSIGSEL_POSS,DMA_SELCON_MSIGSEL_POSE)

#define DMA_CON_MAX_BURST_POSS  16U
#define DMA_CON_MAX_BURST_POSE  19U
#define DMA_CON_MAX_BURST_MSK   BITS(DMA_CON_MAX_BURST_POSS,DMA_CON_MAX_BURST_POSE)

#define DMA_CON_DDWSEL_POSS     13U
#define DMA_CON_DDWSEL_POSE     14U
#define DMA_CON_DDWSEL_MSK      BITS(DMA_CON_DDWSEL_POSS,DMA_CON_DDWSEL_POSE)

#define DMA_CON_DINC_POS        12U
#define DMA_CON_DINC_MSK        BIT(DMA_CON_DINC_POS)

#define DMA_CON_SDWSEL_POSS     9U
#define DMA_CON_SDWSEL_POSE     10U
#define DMA_CON_SDWSEL_MSK      BITS(DMA_CON_SDWSEL_POSS,DMA_CON_SDWSEL_POSE)

#define DMA_CON_SINC_POS        8U
#define DMA_CON_SINC_MSK        BIT(DMA_CON_SINC_POS)

#define DMA_CON_CHPRI_POSS      4U
#define DMA_CON_CHPRI_POSE      5U
#define DMA_CON_CHPRI_MSK       BITS(DMA_CON_CHPRI_POSS,DMA_CON_CHPRI_POSE)

#define DMA_CON_M2M_POS         3U
#define DMA_CON_M2M_MSK         BIT(DMA_CON_M2M_POS)

#define DMA_CON_DIR_POS         2U
#define DMA_CON_DIR_MSK         BIT(DMA_CON_DIR_POS)

#define DMA_CON_CIRC_POS        1U
#define DMA_CON_CIRC_MSK        BIT(DMA_CON_CIRC_POS)

#define DMA_CON_CHEN_POS        0U
#define DMA_CON_CHEN_MSK        BIT(DMA_CON_CHEN_POS)

#define DMA_NDT_NRDT_POSS       16U
#define DMA_NDT_NRDT_POSE       31U
#define DMA_NDT_NRDT_MSK        BITS(DMA_NDT_NRDT_POSS,DMA_NDT_NRDT_POSE)

#define DMA_NDT_TNDT_POSS       0U
#define DMA_NDT_TNDT_POSE       15U
#define DMA_NDT_TNDT_MSK        BITS(DMA_NDT_TNDT_POSS,DMA_NDT_TNDT_POSE)

typedef struct
{
    __IO uint32_t CON;
    __IO uint32_t SAR;
    __IO uint32_t DAR;
    __IO uint32_t NDT;
} DMA_CHANNEL_Typedef;
typedef struct
{
    __O uint32_t IER;
    __O uint32_t IDR;
    __I uint32_t IVS;
    __I uint32_t RIF;
    __I uint32_t IFM;
    __O uint32_t ICR;
    __I uint32_t RESERVED[2];
    DMA_CHANNEL_Typedef CHANNEL[DMA_CHANNELS];
} DMA_TypeDef;

typedef struct
{
    __IO uint32_t CH_SELCON[DMA_CHANNELS];
} DMA_MUX_Typedef;



#endif /* __REG_DMA_H__ */
