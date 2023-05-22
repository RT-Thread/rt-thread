/**********************************************************************************
 *
 * @file    reg_i2c.h
 * @brief   I2C Head File
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

#ifndef __REG_I2C_H__
#define __REG_I2C_H__

/****************** Bit definition for I2C_CON1 register ************************/

# define  I2C_CON1_NBYTES_POSS 24U
# define  I2C_CON1_NBYTES_POSE 31U
# define  I2C_CON1_NBYTES_MSK  BITS(I2C_CON1_NBYTES_POSS, I2C_CON1_NBYTES_POSE)

# define  I2C_CON1_PECEN_POS 23U
# define  I2C_CON1_PECEN_MSK BIT(I2C_CON1_PECEN_POS)

# define  I2C_CON1_ALERTEN_POS 22U
# define  I2C_CON1_ALERTEN_MSK BIT(I2C_CON1_ALERTEN_POS)

# define  I2C_CON1_SMBDEN_POS 21U
# define  I2C_CON1_SMBDEN_MSK BIT(I2C_CON1_SMBDEN_POS)

# define  I2C_CON1_SMBHEN_POS 20U
# define  I2C_CON1_SMBHEN_MSK BIT(I2C_CON1_SMBHEN_POS)

# define  I2C_CON1_GCEN_POS 19U
# define  I2C_CON1_GCEN_MSK BIT(I2C_CON1_GCEN_POS)

# define  I2C_CON1_NOSTRETCH_POS 17U
# define  I2C_CON1_NOSTRETCH_MSK BIT(I2C_CON1_NOSTRETCH_POS)

# define  I2C_CON1_SBC_POS 16U
# define  I2C_CON1_SBC_MSK BIT(I2C_CON1_SBC_POS)

# define  I2C_CON1_RXDMAEN_POS 15U
# define  I2C_CON1_RXDMAEN_MSK BIT(I2C_CON1_RXDMAEN_POS)

# define  I2C_CON1_TXDMAEN_POS 14U
# define  I2C_CON1_TXDMAEN_MSK BIT(I2C_CON1_TXDMAEN_POS)

# define  I2C_CON1_DNF_POSS 8U
# define  I2C_CON1_DNF_POSE 11U
# define  I2C_CON1_DNF_MSK  BITS(I2C_CON1_DNF_POSS, I2C_CON1_DNF_POSE)

# define  I2C_CON1_PE_POS 0U
# define  I2C_CON1_PE_MSK BIT(I2C_CON1_PE_POS)

/****************** Bit definition for I2C_CON2 register ************************/

# define  I2C_CON2_ACK_UPD_POS 29U
# define  I2C_CON2_ACK_UPD_MSK BIT(I2C_CON2_ACK_UPD_POS)

# define  I2C_CON2_HOLDACK_POS 28U
# define  I2C_CON2_HOLDACK_MSK BIT(I2C_CON2_HOLDACK_POS)

# define  I2C_CON2_PECBYTE_POS 26U
# define  I2C_CON2_PECBYTE_MSK BIT(I2C_CON2_PECBYTE_POS)

# define  I2C_CON2_AUTOEND_POS 25U
# define  I2C_CON2_AUTOEND_MSK BIT(I2C_CON2_AUTOEND_POS)

# define  I2C_CON2_RELOAD_POS 24U
# define  I2C_CON2_RELOAD_MSK BIT(I2C_CON2_RELOAD_POS)

# define  I2C_CON2_NBYTES_POSS 16U
# define  I2C_CON2_NBYTES_POSE 23U
# define  I2C_CON2_NBYTES_MSK  BITS(I2C_CON2_NBYTES_POSS, I2C_CON2_NBYTES_POSE)

# define  I2C_CON2_NACK_POS 15U
# define  I2C_CON2_NACK_MSK BIT(I2C_CON2_NACK_POS)

# define  I2C_CON2_STOP_POS 14U
# define  I2C_CON2_STOP_MSK BIT(I2C_CON2_STOP_POS)

# define  I2C_CON2_START_POS 13U
# define  I2C_CON2_START_MSK BIT(I2C_CON2_START_POS)

# define  I2C_CON2_HEAD10R_POS 12U
# define  I2C_CON2_HEAD10R_MSK BIT(I2C_CON2_HEAD10R_POS)

# define  I2C_CON2_ADD10_POS 11U
# define  I2C_CON2_ADD10_MSK BIT(I2C_CON2_ADD10_POS)

# define  I2C_CON2_RD_WRN_POS 10U
# define  I2C_CON2_RD_WRN_MSK BIT(I2C_CON2_RD_WRN_POS)

# define  I2C_CON2_SADD_POSS 0U
# define  I2C_CON2_SADD_POSE 9U
# define  I2C_CON2_SADD_MSK  BITS(I2C_CON2_SADD_POSS, I2C_CON2_SADD_POSE)

/****************** Bit definition for I2C_ADDR1 register ************************/

# define  I2C_ADDR1_OA1EN_POS 15U
# define  I2C_ADDR1_OA1EN_MSK BIT(I2C_ADDR1_OA1EN_POS)

# define  I2C_ADDR1_OA1MODE_POS 10U
# define  I2C_ADDR1_OA1MODE_MSK BIT(I2C_ADDR1_OA1MODE_POS)

# define  I2C_ADDR1_OA1_POSS 0U
# define  I2C_ADDR1_OA1_POSE 9U
# define  I2C_ADDR1_OA1_MSK  BITS(I2C_ADDR1_OA1_POSS, I2C_ADDR1_OA1_POSE)

/****************** Bit definition for I2C_ADDR2 register ************************/

# define  I2C_ADDR2_OA2EN_POS 15U
# define  I2C_ADDR2_OA2EN_MSK BIT(I2C_ADDR2_OA2EN_POS)

# define  I2C_ADDR2_OA2MSK_POSS 8U
# define  I2C_ADDR2_OA2MSK_POSE 10U
# define  I2C_ADDR2_OA2MSK_MSK  BITS(I2C_ADDR2_OA2MSK_POSS, I2C_ADDR2_OA2MSK_POSE)

# define  I2C_ADDR2_OA2_POSS 1U
# define  I2C_ADDR2_OA2_POSE 7U
# define  I2C_ADDR2_OA2_MSK  BITS(I2C_ADDR2_OA2_POSS, I2C_ADDR2_OA2_POSE)

/****************** Bit definition for I2C_TIMINGR register ************************/

# define  I2C_TIMINGR_PRESC_POSS 28U
# define  I2C_TIMINGR_PRESC_POSE 31U
# define  I2C_TIMINGR_PRESC_MSK  BITS(I2C_TIMINGR_PRESC_POSS, I2C_TIMINGR_PRESC_POSE)

# define  I2C_TIMINGR_SCLDEL_POSS 20U
# define  I2C_TIMINGR_SCLDEL_POSE 23U
# define  I2C_TIMINGR_SCLDEL_MSK  BITS(I2C_TIMINGR_SCLDEL_POSS, I2C_TIMINGR_SCLDEL_POSE)

# define  I2C_TIMINGR_SDADEL_POSS 16U
# define  I2C_TIMINGR_SDADEL_POSE 19U
# define  I2C_TIMINGR_SDADEL_MSK  BITS(I2C_TIMINGR_SDADEL_POSS, I2C_TIMINGR_SDADEL_POSE)

# define  I2C_TIMINGR_SCLH_POSS 8U
# define  I2C_TIMINGR_SCLH_POSE 15U
# define  I2C_TIMINGR_SCLH_MSK  BITS(I2C_TIMINGR_SCLH_POSS, I2C_TIMINGR_SCLH_POSE)

# define  I2C_TIMINGR_SCLL_POSS 0U
# define  I2C_TIMINGR_SCLL_POSE 7U
# define  I2C_TIMINGR_SCLL_MSK  BITS(I2C_TIMINGR_SCLL_POSS, I2C_TIMINGR_SCLL_POSE)

/****************** Bit definition for I2C_TIMEOUTR register ************************/

# define  I2C_TIMEOUTR_TEXTEN_POS 31U
# define  I2C_TIMEOUTR_TEXTEN_MSK BIT(I2C_TIMEOUTR_TEXTEN_POS)

# define  I2C_TIMEOUTR_TIMEOUTB_POSS 16U
# define  I2C_TIMEOUTR_TIMEOUTB_POSE 27U
# define  I2C_TIMEOUTR_TIMEOUTB_MSK  BITS(I2C_TIMEOUTR_TIMEOUTB_POSS, I2C_TIMEOUTR_TIMEOUTB_POSE)

# define  I2C_TIMEOUTR_TIMEOUTEN_POS 15U
# define  I2C_TIMEOUTR_TIMEOUTEN_MSK BIT(I2C_TIMEOUTR_TIMEOUTEN_POS)

# define  I2C_TIMEOUTR_TIDLE_POS 12U
# define  I2C_TIMEOUTR_TIDLE_MSK BIT(I2C_TIMEOUTR_TIDLE_POS)

# define  I2C_TIMEOUTR_TIMEOUTA_POSS 0U
# define  I2C_TIMEOUTR_TIMEOUTA_POSE 11U
# define  I2C_TIMEOUTR_TIMEOUTA_MSK  BITS(I2C_TIMEOUTR_TIMEOUTA_POSS, I2C_TIMEOUTR_TIMEOUTA_POSE)

/****************** Bit definition for I2C_STAT register ************************/

# define  I2C_STAT_ADDCODE_POSS 17U
# define  I2C_STAT_ADDCODE_POSE 23U
# define  I2C_STAT_ADDCODE_MSK  BITS(I2C_STAT_ADDCODE_POSS, I2C_STAT_ADDCODE_POSE)

# define  I2C_STAT_DIR_POS 16U
# define  I2C_STAT_DIR_MSK BIT(I2C_STAT_DIR_POS)

# define  I2C_STAT_BUSY_POS 15U
# define  I2C_STAT_BUSY_MSK BIT(I2C_STAT_BUSY_POS)

# define  I2C_STAT_TCR_POS 11U
# define  I2C_STAT_TCR_MSK BIT(I2C_STAT_TCR_POS)

# define  I2C_STAT_TC_POS 10U
# define  I2C_STAT_TC_MSK BIT(I2C_STAT_TC_POS)

# define  I2C_STAT_RXUD_POS 8U
# define  I2C_STAT_RXUD_MSK BIT(I2C_STAT_RXUD_POS)

# define  I2C_STAT_RXOV_POS 7U
# define  I2C_STAT_RXOV_MSK BIT(I2C_STAT_RXOV_POS)

# define  I2C_STAT_RXNE_POS 5U
# define  I2C_STAT_RXNE_MSK BIT(I2C_STAT_RXNE_POS)

# define  I2C_STAT_TXUD_POS 3U
# define  I2C_STAT_TXUD_MSK BIT(I2C_STAT_TXUD_POS)

# define  I2C_STAT_TXOV_POS 2U
# define  I2C_STAT_TXOV_MSK BIT(I2C_STAT_TXOV_POS)

# define  I2C_STAT_TXE_POS 0U
# define  I2C_STAT_TXE_MSK BIT(I2C_STAT_TXE_POS)

/****************** Bit definition for I2C_PECR register ************************/

# define  I2C_PECR_PEC_POSS 0U
# define  I2C_PECR_PEC_POSE 7U
# define  I2C_PECR_PEC_MSK  BITS(I2C_PECR_PEC_POSS, I2C_PECR_PEC_POSE)

/****************** Bit definition for I2C_RXDATA register ************************/

# define  I2C_RXDATA_RXDATA_POSS 0U
# define  I2C_RXDATA_RXDATA_POSE 7U
# define  I2C_RXDATA_RXDATA_MSK  BITS(I2C_RXDATA_RXDATA_POSS, I2C_RXDATA_RXDATA_POSE)

/****************** Bit definition for I2C_TXDATA register ************************/

# define  I2C_TXDATA_TXDATA_POSS 0U
# define  I2C_TXDATA_TXDATA_POSE 7U
# define  I2C_TXDATA_TXDATA_MSK  BITS(I2C_TXDATA_TXDATA_POSS, I2C_TXDATA_TXDATA_POSE)

/****************** Bit definition for I2C_IER register ************************/

# define  I2C_IER_ALERT_POS 20U
# define  I2C_IER_ALERT_MSK BIT(I2C_IER_ALERT_POS)

# define  I2C_IER_TOUT_POS 19U
# define  I2C_IER_TOUT_MSK BIT(I2C_IER_TOUT_POS)

# define  I2C_IER_PECE_POS 18U
# define  I2C_IER_PECE_MSK BIT(I2C_IER_PECE_POS)

# define  I2C_IER_ARLO_POS 17U
# define  I2C_IER_ARLO_MSK BIT(I2C_IER_ARLO_POS)

# define  I2C_IER_BERR_POS 16U
# define  I2C_IER_BERR_MSK BIT(I2C_IER_BERR_POS)

# define  I2C_IER_STOP_POS 14U
# define  I2C_IER_STOP_MSK BIT(I2C_IER_STOP_POS)

# define  I2C_IER_NACK_POS 13U
# define  I2C_IER_NACK_MSK BIT(I2C_IER_NACK_POS)

# define  I2C_IER_ADDR_POS 12U
# define  I2C_IER_ADDR_MSK BIT(I2C_IER_ADDR_POS)

# define  I2C_IER_TCR_POS 11U
# define  I2C_IER_TCR_MSK BIT(I2C_IER_TCR_POS)

# define  I2C_IER_TC_POS 10U
# define  I2C_IER_TC_MSK BIT(I2C_IER_TC_POS)

# define  I2C_IER_RXUD_POS 8U
# define  I2C_IER_RXUD_MSK BIT(I2C_IER_RXUD_POS)

# define  I2C_IER_RXOV_POS 7U
# define  I2C_IER_RXOV_MSK BIT(I2C_IER_RXOV_POS)

# define  I2C_IER_RXNE_POS 5U
# define  I2C_IER_RXNE_MSK BIT(I2C_IER_RXNE_POS)

# define  I2C_IER_TXUD_POS 3U
# define  I2C_IER_TXUD_MSK BIT(I2C_IER_TXUD_POS)

# define  I2C_IER_TXOV_POS 2U
# define  I2C_IER_TXOV_MSK BIT(I2C_IER_TXOV_POS)

# define  I2C_IER_TXE_POS 0U
# define  I2C_IER_TXE_MSK BIT(I2C_IER_TXE_POS)

/****************** Bit definition for I2C_IDR register ************************/

# define  I2C_IDR_ALERT_POS 20U
# define  I2C_IDR_ALERT_MSK BIT(I2C_IDR_ALERT_POS)

# define  I2C_IDR_TOUT_POS 19U
# define  I2C_IDR_TOUT_MSK BIT(I2C_IDR_TOUT_POS)

# define  I2C_IDR_PECE_POS 18U
# define  I2C_IDR_PECE_MSK BIT(I2C_IDR_PECE_POS)

# define  I2C_IDR_ARLO_POS 17U
# define  I2C_IDR_ARLO_MSK BIT(I2C_IDR_ARLO_POS)

# define  I2C_IDR_BERR_POS 16U
# define  I2C_IDR_BERR_MSK BIT(I2C_IDR_BERR_POS)

# define  I2C_IDR_STOP_POS 14U
# define  I2C_IDR_STOP_MSK BIT(I2C_IDR_STOP_POS)

# define  I2C_IDR_NACK_POS 13U
# define  I2C_IDR_NACK_MSK BIT(I2C_IDR_NACK_POS)

# define  I2C_IDR_ADDR_POS 12U
# define  I2C_IDR_ADDR_MSK BIT(I2C_IDR_ADDR_POS)

# define  I2C_IDR_TCR_POS 11U
# define  I2C_IDR_TCR_MSK BIT(I2C_IDR_TCR_POS)

# define  I2C_IDR_TC_POS 10U
# define  I2C_IDR_TC_MSK BIT(I2C_IDR_TC_POS)

# define  I2C_IDR_RXUD_POS 8U
# define  I2C_IDR_RXUD_MSK BIT(I2C_IDR_RXUD_POS)

# define  I2C_IDR_RXOV_POS 7U
# define  I2C_IDR_RXOV_MSK BIT(I2C_IDR_RXOV_POS)

# define  I2C_IDR_RXNE_POS 5U
# define  I2C_IDR_RXNE_MSK BIT(I2C_IDR_RXNE_POS)

# define  I2C_IDR_TXUD_POS 3U
# define  I2C_IDR_TXUD_MSK BIT(I2C_IDR_TXUD_POS)

# define  I2C_IDR_TXOV_POS 2U
# define  I2C_IDR_TXOV_MSK BIT(I2C_IDR_TXOV_POS)

# define  I2C_IDR_TXE_POS 0U
# define  I2C_IDR_TXE_MSK BIT(I2C_IDR_TXE_POS)
/****************** Bit definition for I2C_IVS register ************************/

# define  I2C_IVS_ALERT_POS 20U
# define  I2C_IVS_ALERT_MSK BIT(I2C_IVS_ALERT_POS)

# define  I2C_IVS_TOUT_POS 19U
# define  I2C_IVS_TOUT_MSK BIT(I2C_IVS_TOUT_POS)

# define  I2C_IVS_PECE_POS 18U
# define  I2C_IVS_PECE_MSK BIT(I2C_IVS_PECE_POS)

# define  I2C_IVS_ARLO_POS 17U
# define  I2C_IVS_ARLO_MSK BIT(I2C_IVS_ARLO_POS)

# define  I2C_IVS_BERR_POS 16U
# define  I2C_IVS_BERR_MSK BIT(I2C_IVS_BERR_POS)

# define  I2C_IVS_STOP_POS 14U
# define  I2C_IVS_STOP_MSK BIT(I2C_IVS_STOP_POS)

# define  I2C_IVS_NACK_POS 13U
# define  I2C_IVS_NACK_MSK BIT(I2C_IVS_NACK_POS)

# define  I2C_IVS_ADDR_POS 12U
# define  I2C_IVS_ADDR_MSK BIT(I2C_IVS_ADDR_POS)

# define  I2C_IVS_TCR_POS 11U
# define  I2C_IVS_TCR_MSK BIT(I2C_IVS_TCR_POS)

# define  I2C_IVS_TC_POS 10U
# define  I2C_IVS_TC_MSK BIT(I2C_IVS_TC_POS)

# define  I2C_IVS_RXUD_POS 8U
# define  I2C_IVS_RXUD_MSK BIT(I2C_IVS_RXUD_POS)

# define  I2C_IVS_RXOV_POS 7U
# define  I2C_IVS_RXOV_MSK BIT(I2C_IVS_RXOV_POS)

# define  I2C_IVS_RXNE_POS 5U
# define  I2C_IVS_RXNE_MSK BIT(I2C_IVS_RXNE_POS)

# define  I2C_IVS_TXUD_POS 3U
# define  I2C_IVS_TXUD_MSK BIT(I2C_IVS_TXUD_POS)

# define  I2C_IVS_TXOV_POS 2U
# define  I2C_IVS_TXOV_MSK BIT(I2C_IVS_TXOV_POS)

# define  I2C_IVS_TXE_POS 0U
# define  I2C_IVS_TXE_MSK BIT(I2C_IVS_TXE_POS)

/****************** Bit definition for I2C_RIF register ************************/

# define  I2C_RIF_ALERT_POS 20U
# define  I2C_RIF_ALERT_MSK BIT(I2C_RIF_ALERT_POS)

# define  I2C_RIF_TOUT_POS 19U
# define  I2C_RIF_TOUT_MSK BIT(I2C_RIF_TOUT_POS)

# define  I2C_RIF_PECE_POS 18U
# define  I2C_RIF_PECE_MSK BIT(I2C_RIF_PECE_POS)

# define  I2C_RIF_ARLO_POS 17U
# define  I2C_RIF_ARLO_MSK BIT(I2C_RIF_ARLO_POS)

# define  I2C_RIF_BERR_POS 16U
# define  I2C_RIF_BERR_MSK BIT(I2C_RIF_BERR_POS)

# define  I2C_RIF_STOP_POS 14U
# define  I2C_RIF_STOP_MSK BIT(I2C_RIF_STOP_POS)

# define  I2C_RIF_NACK_POS 13U
# define  I2C_RIF_NACK_MSK BIT(I2C_RIF_NACK_POS)

# define  I2C_RIF_ADDR_POS 12U
# define  I2C_RIF_ADDR_MSK BIT(I2C_RIF_ADDR_POS)

# define  I2C_RIF_TCR_POS 11U
# define  I2C_RIF_TCR_MSK BIT(I2C_RIF_TCR_POS)

# define  I2C_RIF_TC_POS 10U
# define  I2C_RIF_TC_MSK BIT(I2C_RIF_TC_POS)

# define  I2C_RIF_RXUD_POS 8U
# define  I2C_RIF_RXUD_MSK BIT(I2C_RIF_RXUD_POS)

# define  I2C_RIF_RXOV_POS 7U
# define  I2C_RIF_RXOV_MSK BIT(I2C_RIF_RXOV_POS)

# define  I2C_RIF_RXNE_POS 5U
# define  I2C_RIF_RXNE_MSK BIT(I2C_RIF_RXNE_POS)

# define  I2C_RIF_TXUD_POS 3U
# define  I2C_RIF_TXUD_MSK BIT(I2C_RIF_TXUD_POS)

# define  I2C_RIF_TXOV_POS 2U
# define  I2C_RIF_TXOV_MSK BIT(I2C_RIF_TXOV_POS)

# define  I2C_RIF_TXE_POS 0U
# define  I2C_RIF_TXE_MSK BIT(I2C_RIF_TXE_POS)

/****************** Bit definition for I2C_IFM register ************************/

# define  I2C_IFM_ALERT_POS 20U
# define  I2C_IFM_ALERT_MSK BIT(I2C_IFM_ALERT_POS)

# define  I2C_IFM_TOUT_POS 19U
# define  I2C_IFM_TOUT_MSK BIT(I2C_IFM_TOUT_POS)

# define  I2C_IFM_PECE_POS 18U
# define  I2C_IFM_PECE_MSK BIT(I2C_IFM_PECE_POS)

# define  I2C_IFM_ARLO_POS 17U
# define  I2C_IFM_ARLO_MSK BIT(I2C_IFM_ARLO_POS)

# define  I2C_IFM_BERR_POS 16U
# define  I2C_IFM_BERR_MSK BIT(I2C_IFM_BERR_POS)

# define  I2C_IFM_STOP_POS 14U
# define  I2C_IFM_STOP_MSK BIT(I2C_IFM_STOP_POS)

# define  I2C_IFM_NACK_POS 13U
# define  I2C_IFM_NACK_MSK BIT(I2C_IFM_NACK_POS)

# define  I2C_IFM_ADDR_POS 12U
# define  I2C_IFM_ADDR_MSK BIT(I2C_IFM_ADDR_POS)

# define  I2C_IFM_TCR_POS 11U
# define  I2C_IFM_TCR_MSK BIT(I2C_IFM_TCR_POS)

# define  I2C_IFM_TC_POS 10U
# define  I2C_IFM_TC_MSK BIT(I2C_IFM_TC_POS)

# define  I2C_IFM_RXUD_POS 8U
# define  I2C_IFM_RXUD_MSK BIT(I2C_IFM_RXUD_POS)

# define  I2C_IFM_RXOV_POS 7U
# define  I2C_IFM_RXOV_MSK BIT(I2C_IFM_RXOV_POS)

# define  I2C_IFM_RXNE_POS 5U
# define  I2C_IFM_RXNE_MSK BIT(I2C_IFM_RXNE_POS)

# define  I2C_IFM_TXUD_POS 3U
# define  I2C_IFM_TXUD_MSK BIT(I2C_IFM_TXUD_POS)

# define  I2C_IFM_TXOV_POS 2U
# define  I2C_IFM_TXOV_MSK BIT(I2C_IFM_TXOV_POS)

# define  I2C_IFM_TXE_POS 0U
# define  I2C_IFM_TXE_MSK BIT(I2C_IFM_TXE_POS)

/****************** Bit definition for I2C_ICR register ************************/

# define  I2C_ICR_ALERT_POS 20U
# define  I2C_ICR_ALERT_MSK BIT(I2C_ICR_ALERT_POS)

# define  I2C_ICR_TOUT_POS 19U
# define  I2C_ICR_TOUT_MSK BIT(I2C_ICR_TOUT_POS)

# define  I2C_ICR_PECE_POS 18U
# define  I2C_ICR_PECE_MSK BIT(I2C_ICR_PECE_POS)

# define  I2C_ICR_ARLO_POS 17U
# define  I2C_ICR_ARLO_MSK BIT(I2C_ICR_ARLO_POS)

# define  I2C_ICR_BERR_POS 16U
# define  I2C_ICR_BERR_MSK BIT(I2C_ICR_BERR_POS)

# define  I2C_ICR_STOP_POS 14U
# define  I2C_ICR_STOP_MSK BIT(I2C_ICR_STOP_POS)

# define  I2C_ICR_NACK_POS 13U
# define  I2C_ICR_NACK_MSK BIT(I2C_ICR_NACK_POS)

# define  I2C_ICR_ADDR_POS 12U
# define  I2C_ICR_ADDR_MSK BIT(I2C_ICR_ADDR_POS)

# define  I2C_ICR_TCR_POS 11U
# define  I2C_ICR_TCR_MSK BIT(I2C_ICR_TCR_POS)

# define  I2C_ICR_TC_POS 10U
# define  I2C_ICR_TC_MSK BIT(I2C_ICR_TC_POS)

# define  I2C_ICR_RXUD_POS 8U
# define  I2C_ICR_RXUD_MSK BIT(I2C_ICR_RXUD_POS)

# define  I2C_ICR_RXOV_POS 7U
# define  I2C_ICR_RXOV_MSK BIT(I2C_ICR_RXOV_POS)

# define  I2C_ICR_RXNE_POS 5U
# define  I2C_ICR_RXNE_MSK BIT(I2C_ICR_RXNE_POS)

# define  I2C_ICR_TXUD_POS 3U
# define  I2C_ICR_TXUD_MSK BIT(I2C_ICR_TXUD_POS)

# define  I2C_ICR_TXOV_POS 2U
# define  I2C_ICR_TXOV_MSK BIT(I2C_ICR_TXOV_POS)

# define  I2C_ICR_TXE_POS 0U
# define  I2C_ICR_TXE_MSK BIT(I2C_ICR_TXE_POS)

typedef struct
{
  __IO uint32_t CON1;
  __IO uint32_t CON2;
  __IO uint32_t ADDR1;
  __IO uint32_t ADDR2;
  __IO uint32_t TIMINGR;
  __IO uint32_t TIMEOUTR;
  __I  uint32_t STAT;
  __IO uint32_t RESERVED0;
  __IO uint32_t PECR;
  __I  uint32_t RXDATA;
  __O  uint32_t TXDATA;
  __O  uint32_t IER;
  __O  uint32_t IDR;
  __I  uint32_t IVS;
  __I  uint32_t RIF;
  __I  uint32_t IFM;
  __O  uint32_t ICR;
} I2C_TypeDef;





#endif /* __REG_I2C_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
