/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_i2c.h
  * @author  FMSH Application Team
  * @brief   Head file of I2C FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LC0XX_FL_I2C_H
#define __FM33LC0XX_FL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup I2C I2C
  * @brief I2C FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup I2C_FL_ES_INIT I2C Exported Init structures
  * @{
  */

/**
  * @brief I2C Init Sturcture Definition
  */
typedef struct
{
    /** 主机时使用的时钟源*/
    uint32_t clockSource;

    /** I2C通讯速率*/
    uint32_t baudRate;

} FL_I2C_MasterMode_InitTypeDef;

/**
  * @brief I2C Slavemode Init Sturcture Definition
  */
typedef struct
{
    /** 从机模式从机地址 */
    uint32_t ownAddr;

    /** 从机模式自动回应ACK */
    uint32_t ACK;

    /** 从机模式地址位宽 */
    uint32_t ownAddrSize10bit;

    /** 从机时钟延展*/
    uint32_t SCLSEN;

} FL_I2C_SlaveMode_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup I2C_FL_Exported_Constants I2C Exported Constants
  * @{
  */

#define    I2C_MSPCFGR_MSPEN_Pos                                  (0U)
#define    I2C_MSPCFGR_MSPEN_Msk                                  (0x1U << I2C_MSPCFGR_MSPEN_Pos)
#define    I2C_MSPCFGR_MSPEN                                      I2C_MSPCFGR_MSPEN_Msk

#define    I2C_MSPCFGR_TOEN_Pos                                   (1U)
#define    I2C_MSPCFGR_TOEN_Msk                                   (0x1U << I2C_MSPCFGR_TOEN_Pos)
#define    I2C_MSPCFGR_TOEN                                       I2C_MSPCFGR_TOEN_Msk

#define    I2C_MSPCFGR_DMAEN_Pos                                  (16U)
#define    I2C_MSPCFGR_DMAEN_Msk                                  (0x1U << I2C_MSPCFGR_DMAEN_Pos)
#define    I2C_MSPCFGR_DMAEN                                      I2C_MSPCFGR_DMAEN_Msk

#define    I2C_MSPCFGR_AUTOEND_Pos                                (17U)
#define    I2C_MSPCFGR_AUTOEND_Msk                                (0x1U << I2C_MSPCFGR_AUTOEND_Pos)
#define    I2C_MSPCFGR_AUTOEND                                    I2C_MSPCFGR_AUTOEND_Msk

#define    I2C_MSPCR_RCEN_Pos                                     (3U)
#define    I2C_MSPCR_RCEN_Msk                                     (0x1U << I2C_MSPCR_RCEN_Pos)
#define    I2C_MSPCR_RCEN                                         I2C_MSPCR_RCEN_Msk

#define    I2C_MSPCR_PEN_Pos                                      (2U)
#define    I2C_MSPCR_PEN_Msk                                      (0x1U << I2C_MSPCR_PEN_Pos)
#define    I2C_MSPCR_PEN                                          I2C_MSPCR_PEN_Msk

#define    I2C_MSPCR_RSEN_Pos                                     (1U)
#define    I2C_MSPCR_RSEN_Msk                                     (0x1U << I2C_MSPCR_RSEN_Pos)
#define    I2C_MSPCR_RSEN                                         I2C_MSPCR_RSEN_Msk

#define    I2C_MSPCR_SEN_Pos                                      (0U)
#define    I2C_MSPCR_SEN_Msk                                      (0x1U << I2C_MSPCR_SEN_Pos)
#define    I2C_MSPCR_SEN                                          I2C_MSPCR_SEN_Msk

#define    I2C_MSPIER_WCOLIE_Pos                                  (6U)
#define    I2C_MSPIER_WCOLIE_Msk                                  (0x1U << I2C_MSPIER_WCOLIE_Pos)
#define    I2C_MSPIER_WCOLIE                                      I2C_MSPIER_WCOLIE_Msk

#define    I2C_MSPIER_TOIE_Pos                                    (5U)
#define    I2C_MSPIER_TOIE_Msk                                    (0x1U << I2C_MSPIER_TOIE_Pos)
#define    I2C_MSPIER_TOIE                                        I2C_MSPIER_TOIE_Msk

#define    I2C_MSPIER_SIE_Pos                                     (4U)
#define    I2C_MSPIER_SIE_Msk                                     (0x1U << I2C_MSPIER_SIE_Pos)
#define    I2C_MSPIER_SIE                                         I2C_MSPIER_SIE_Msk

#define    I2C_MSPIER_PIE_Pos                                     (3U)
#define    I2C_MSPIER_PIE_Msk                                     (0x1U << I2C_MSPIER_PIE_Pos)
#define    I2C_MSPIER_PIE                                         I2C_MSPIER_PIE_Msk

#define    I2C_MSPIER_NACKIE_Pos                                  (2U)
#define    I2C_MSPIER_NACKIE_Msk                                  (0x1U << I2C_MSPIER_NACKIE_Pos)
#define    I2C_MSPIER_NACKIE                                      I2C_MSPIER_NACKIE_Msk

#define    I2C_MSPIER_TXIE_Pos                                    (1U)
#define    I2C_MSPIER_TXIE_Msk                                    (0x1U << I2C_MSPIER_TXIE_Pos)
#define    I2C_MSPIER_TXIE                                        I2C_MSPIER_TXIE_Msk

#define    I2C_MSPIER_RXIE_Pos                                    (0U)
#define    I2C_MSPIER_RXIE_Msk                                    (0x1U << I2C_MSPIER_RXIE_Pos)
#define    I2C_MSPIER_RXIE                                        I2C_MSPIER_RXIE_Msk

#define    I2C_MSPISR_WCOL_Pos                                    (6U)
#define    I2C_MSPISR_WCOL_Msk                                    (0x1U << I2C_MSPISR_WCOL_Pos)
#define    I2C_MSPISR_WCOL                                        I2C_MSPISR_WCOL_Msk

#define    I2C_MSPISR_TO_Pos                                      (5U)
#define    I2C_MSPISR_TO_Msk                                      (0x1U << I2C_MSPISR_TO_Pos)
#define    I2C_MSPISR_TO                                          I2C_MSPISR_TO_Msk

#define    I2C_MSPISR_S_Pos                                       (4U)
#define    I2C_MSPISR_S_Msk                                       (0x1U << I2C_MSPISR_S_Pos)
#define    I2C_MSPISR_S                                           I2C_MSPISR_S_Msk

#define    I2C_MSPISR_P_Pos                                       (3U)
#define    I2C_MSPISR_P_Msk                                       (0x1U << I2C_MSPISR_P_Pos)
#define    I2C_MSPISR_P                                           I2C_MSPISR_P_Msk

#define    I2C_MSPISR_ACKSTA_Pos                                  (2U)
#define    I2C_MSPISR_ACKSTA_Msk                                  (0x1U << I2C_MSPISR_ACKSTA_Pos)
#define    I2C_MSPISR_ACKSTA                                      I2C_MSPISR_ACKSTA_Msk

#define    I2C_MSPISR_TXIF_Pos                                    (1U)
#define    I2C_MSPISR_TXIF_Msk                                    (0x1U << I2C_MSPISR_TXIF_Pos)
#define    I2C_MSPISR_TXIF                                        I2C_MSPISR_TXIF_Msk

#define    I2C_MSPISR_RXIF_Pos                                    (0U)
#define    I2C_MSPISR_RXIF_Msk                                    (0x1U << I2C_MSPISR_RXIF_Pos)
#define    I2C_MSPISR_RXIF                                        I2C_MSPISR_RXIF_Msk

#define    I2C_MSPSR_BUSY_Pos                                     (5U)
#define    I2C_MSPSR_BUSY_Msk                                     (0x1U << I2C_MSPSR_BUSY_Pos)
#define    I2C_MSPSR_BUSY                                         I2C_MSPSR_BUSY_Msk

#define    I2C_MSPSR_RW_Pos                                       (4U)
#define    I2C_MSPSR_RW_Msk                                       (0x1U << I2C_MSPSR_RW_Pos)
#define    I2C_MSPSR_RW                                           I2C_MSPSR_RW_Msk

#define    I2C_MSPSR_BF_Pos                                       (2U)
#define    I2C_MSPSR_BF_Msk                                       (0x1U << I2C_MSPSR_BF_Pos)
#define    I2C_MSPSR_BF                                           I2C_MSPSR_BF_Msk

#define    I2C_MSPSR_ACKMO_Pos                                    (0U)
#define    I2C_MSPSR_ACKMO_Msk                                    (0x1U << I2C_MSPSR_ACKMO_Pos)
#define    I2C_MSPSR_ACKMO                                        I2C_MSPSR_ACKMO_Msk

#define    I2C_MSPBGR_MSPBGRH_Pos                                 (16U)
#define    I2C_MSPBGR_MSPBGRH_Msk                                 (0x1ffU << I2C_MSPBGR_MSPBGRH_Pos)
#define    I2C_MSPBGR_MSPBGRH                                     I2C_MSPBGR_MSPBGRH_Msk

#define    I2C_MSPBGR_MSPBGRL_Pos                                 (0U)
#define    I2C_MSPBGR_MSPBGRL_Msk                                 (0x1ffU << I2C_MSPBGR_MSPBGRL_Pos)
#define    I2C_MSPBGR_MSPBGRL                                     I2C_MSPBGR_MSPBGRL_Msk

#define    I2C_MSPBUF_MSPBUF_Pos                                  (0U)
#define    I2C_MSPBUF_MSPBUF_Msk                                  (0xffU << I2C_MSPBUF_MSPBUF_Pos)
#define    I2C_MSPBUF_MSPBUF                                      I2C_MSPBUF_MSPBUF_Msk

#define    I2C_MSPTCR_SDAHD_Pos                                   (0U)
#define    I2C_MSPTCR_SDAHD_Msk                                   (0x1ffU << I2C_MSPTCR_SDAHD_Pos)
#define    I2C_MSPTCR_SDAHD                                       I2C_MSPTCR_SDAHD_Msk

#define    I2C_MSPTOR_TIMEOUT_Pos                                 (0U)
#define    I2C_MSPTOR_TIMEOUT_Msk                                 (0xfffU << I2C_MSPTOR_TIMEOUT_Pos)
#define    I2C_MSPTOR_TIMEOUT                                     I2C_MSPTOR_TIMEOUT_Msk

#define    I2C_SSPCR_SCLSEN_Pos                                   (9U)
#define    I2C_SSPCR_SCLSEN_Msk                                   (0x1U << I2C_SSPCR_SCLSEN_Pos)
#define    I2C_SSPCR_SCLSEN                                       I2C_SSPCR_SCLSEN_Msk

#define    I2C_SSPCR_DMAEN_Pos                                    (8U)
#define    I2C_SSPCR_DMAEN_Msk                                    (0x1U << I2C_SSPCR_DMAEN_Pos)
#define    I2C_SSPCR_DMAEN                                        I2C_SSPCR_DMAEN_Msk

#define    I2C_SSPCR_ACKEN_Pos                                    (4U)
#define    I2C_SSPCR_ACKEN_Msk                                    (0x1U << I2C_SSPCR_ACKEN_Pos)
#define    I2C_SSPCR_ACKEN                                        I2C_SSPCR_ACKEN_Msk

#define    I2C_SSPCR_SDAO_DLYEN_Pos                               (3U)
#define    I2C_SSPCR_SDAO_DLYEN_Msk                               (0x1U << I2C_SSPCR_SDAO_DLYEN_Pos)
#define    I2C_SSPCR_SDAO_DLYEN                                   I2C_SSPCR_SDAO_DLYEN_Msk

#define    I2C_SSPCR_SCLI_ANFEN_Pos                               (2U)
#define    I2C_SSPCR_SCLI_ANFEN_Msk                               (0x1U << I2C_SSPCR_SCLI_ANFEN_Pos)
#define    I2C_SSPCR_SCLI_ANFEN                                   I2C_SSPCR_SCLI_ANFEN_Msk

#define    I2C_SSPCR_A10EN_Pos                                    (1U)
#define    I2C_SSPCR_A10EN_Msk                                    (0x1U << I2C_SSPCR_A10EN_Pos)
#define    I2C_SSPCR_A10EN                                        I2C_SSPCR_A10EN_Msk

#define    I2C_SSPCR_SSPEN_Pos                                    (0U)
#define    I2C_SSPCR_SSPEN_Msk                                    (0x1U << I2C_SSPCR_SSPEN_Pos)
#define    I2C_SSPCR_SSPEN                                        I2C_SSPCR_SSPEN_Msk

#define    I2C_SSPIER_ADEIE_Pos                                   (7U)
#define    I2C_SSPIER_ADEIE_Msk                                   (0x1U << I2C_SSPIER_ADEIE_Pos)
#define    I2C_SSPIER_ADEIE                                       I2C_SSPIER_ADEIE_Msk

#define    I2C_SSPIER_SIE_Pos                                     (6U)
#define    I2C_SSPIER_SIE_Msk                                     (0x1U << I2C_SSPIER_SIE_Pos)
#define    I2C_SSPIER_SIE                                         I2C_SSPIER_SIE_Msk

#define    I2C_SSPIER_PIE_Pos                                     (5U)
#define    I2C_SSPIER_PIE_Msk                                     (0x1U << I2C_SSPIER_PIE_Pos)
#define    I2C_SSPIER_PIE                                         I2C_SSPIER_PIE_Msk

#define    I2C_SSPIER_WCOLIE_Pos                                  (4U)
#define    I2C_SSPIER_WCOLIE_Msk                                  (0x1U << I2C_SSPIER_WCOLIE_Pos)
#define    I2C_SSPIER_WCOLIE                                      I2C_SSPIER_WCOLIE_Msk

#define    I2C_SSPIER_SSPOVIE_Pos                                 (3U)
#define    I2C_SSPIER_SSPOVIE_Msk                                 (0x1U << I2C_SSPIER_SSPOVIE_Pos)
#define    I2C_SSPIER_SSPOVIE                                     I2C_SSPIER_SSPOVIE_Msk

#define    I2C_SSPIER_ADMIE_Pos                                   (2U)
#define    I2C_SSPIER_ADMIE_Msk                                   (0x1U << I2C_SSPIER_ADMIE_Pos)
#define    I2C_SSPIER_ADMIE                                       I2C_SSPIER_ADMIE_Msk

#define    I2C_SSPIER_TXIE_Pos                                    (1U)
#define    I2C_SSPIER_TXIE_Msk                                    (0x1U << I2C_SSPIER_TXIE_Pos)
#define    I2C_SSPIER_TXIE                                        I2C_SSPIER_TXIE_Msk

#define    I2C_SSPIER_RXIE_Pos                                    (0U)
#define    I2C_SSPIER_RXIE_Msk                                    (0x1U << I2C_SSPIER_RXIE_Pos)
#define    I2C_SSPIER_RXIE                                        I2C_SSPIER_RXIE_Msk

#define    I2C_SSPISR_ADE_Pos                                     (7U)
#define    I2C_SSPISR_ADE_Msk                                     (0x1U << I2C_SSPISR_ADE_Pos)
#define    I2C_SSPISR_ADE                                         I2C_SSPISR_ADE_Msk

#define    I2C_SSPISR_S_Pos                                       (6U)
#define    I2C_SSPISR_S_Msk                                       (0x1U << I2C_SSPISR_S_Pos)
#define    I2C_SSPISR_S                                           I2C_SSPISR_S_Msk

#define    I2C_SSPISR_P_Pos                                       (5U)
#define    I2C_SSPISR_P_Msk                                       (0x1U << I2C_SSPISR_P_Pos)
#define    I2C_SSPISR_P                                           I2C_SSPISR_P_Msk

#define    I2C_SSPISR_WCOL_Pos                                    (4U)
#define    I2C_SSPISR_WCOL_Msk                                    (0x1U << I2C_SSPISR_WCOL_Pos)
#define    I2C_SSPISR_WCOL                                        I2C_SSPISR_WCOL_Msk

#define    I2C_SSPISR_SSPOV_Pos                                   (3U)
#define    I2C_SSPISR_SSPOV_Msk                                   (0x1U << I2C_SSPISR_SSPOV_Pos)
#define    I2C_SSPISR_SSPOV                                       I2C_SSPISR_SSPOV_Msk

#define    I2C_SSPISR_ADM_Pos                                     (2U)
#define    I2C_SSPISR_ADM_Msk                                     (0x1U << I2C_SSPISR_ADM_Pos)
#define    I2C_SSPISR_ADM                                         I2C_SSPISR_ADM_Msk

#define    I2C_SSPISR_TXIF_Pos                                    (1U)
#define    I2C_SSPISR_TXIF_Msk                                    (0x1U << I2C_SSPISR_TXIF_Pos)
#define    I2C_SSPISR_TXIF                                        I2C_SSPISR_TXIF_Msk

#define    I2C_SSPISR_RXIF_Pos                                    (0U)
#define    I2C_SSPISR_RXIF_Msk                                    (0x1U << I2C_SSPISR_RXIF_Pos)
#define    I2C_SSPISR_RXIF                                        I2C_SSPISR_RXIF_Msk

#define    I2C_SSPSR_BUSY_Pos                                     (3U)
#define    I2C_SSPSR_BUSY_Msk                                     (0x1U << I2C_SSPSR_BUSY_Pos)
#define    I2C_SSPSR_BUSY                                         I2C_SSPSR_BUSY_Msk

#define    I2C_SSPSR_RW_Pos                                       (2U)
#define    I2C_SSPSR_RW_Msk                                       (0x1U << I2C_SSPSR_RW_Pos)
#define    I2C_SSPSR_RW                                           I2C_SSPSR_RW_Msk

#define    I2C_SSPSR_DA_Pos                                       (1U)
#define    I2C_SSPSR_DA_Msk                                       (0x1U << I2C_SSPSR_DA_Pos)
#define    I2C_SSPSR_DA                                           I2C_SSPSR_DA_Msk

#define    I2C_SSPSR_BF_Pos                                       (0U)
#define    I2C_SSPSR_BF_Msk                                       (0x1U << I2C_SSPSR_BF_Pos)
#define    I2C_SSPSR_BF                                           I2C_SSPSR_BF_Msk






#define    FL_I2C_MSP_DATA_DIRECTION_SLAVE_TO_MASTER              (0x0U << I2C_MSPSR_RW_Pos)
#define    FL_I2C_MSP_DATA_DIRECTION_MASTER_TO_SLAVE              (0x1U << I2C_MSPSR_RW_Pos)

#define    FL_I2C_MSP_DATA_BUFF_STATUS_FULL                       (0x0U << I2C_MSPSR_BF_Pos)
#define    FL_I2C_MSP_DATA_BUFF_STATUS_EMPTY                      (0x1U << I2C_MSPSR_BF_Pos)

#define    FL_I2C_MASTER_RESPOND_ACK                              (0x0U << I2C_MSPSR_ACKMO_Pos)
#define    FL_I2C_MASTER_RESPOND_NACK                             (0x1U << I2C_MSPSR_ACKMO_Pos)

#define    FL_I2C_SSP_DATA_DIRECTION_SLAVE_TO_MASTER              (0x1U << I2C_SSPSR_RW_Pos)
#define    FL_I2C_SSP_DATA_DIRECTION_MASTER_TO_SLAVE              (0x0U << I2C_SSPSR_RW_Pos)

#define    FL_I2C_SSP_DATA_TYPE_DATA                              (0x1U << I2C_SSPSR_DA_Pos)
#define    FL_I2C_SSP_DATA_TYPE_ADDR                              (0x0U << I2C_SSPSR_DA_Pos)

#define    FL_I2C_SSP_DATA_BUFF_STATUS_FULL                       (0x1U << I2C_SSPSR_BF_Pos)
#define    FL_I2C_SSP_DATA_BUFF_STATUS_EMPTY                      (0x0U << I2C_SSPSR_BF_Pos)

/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup I2C_FL_Exported_Functions I2C Exported Functions
  * @{
  */

/**
  * @brief
  * @rmtoll   MSPCFGR    MSPEN    FL_I2C_Master_Enable
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_Enable(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_MSPEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    MSPEN    FL_I2C_Master_IsEnabled
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabled(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_MSPEN_Msk) == I2C_MSPCFGR_MSPEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    MSPEN    FL_I2C_Master_Disable
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_Disable(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_MSPEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    TOEN    FL_I2C_Master_EnableTimeout
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableTimeout(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_TOEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    TOEN    FL_I2C_Master_IsEnabledTimeout
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledTimeout(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_TOEN_Msk) == I2C_MSPCFGR_TOEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    TOEN    FL_I2C_Master_DisableTimeout
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableTimeout(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_TOEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    DMAEN    FL_I2C_Master_EnableDMAReq
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableDMAReq(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_DMAEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    DMAEN    FL_I2C_Master_IsEnabledDMAReq
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledDMAReq(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_DMAEN_Msk) == I2C_MSPCFGR_DMAEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    DMAEN    FL_I2C_Master_DisableDMAReq
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableDMAReq(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_DMAEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    AUTOEND    FL_I2C_Master_EnableAutoStop
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableAutoStop(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_AUTOEND_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    AUTOEND    FL_I2C_Master_IsEnabledAutoStop
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledAutoStop(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_AUTOEND_Msk) == I2C_MSPCFGR_AUTOEND_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCFGR    AUTOEND    FL_I2C_Master_DisableAutoStop
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableAutoStop(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPCFGR, I2C_MSPCFGR_AUTOEND_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCR    RCEN    FL_I2C_Master_EnableRX
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableRX(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPCR, I2C_MSPCR_RCEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCR    RCEN    FL_I2C_Master_IsEnabledRX
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledRX(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPCR, I2C_MSPCR_RCEN_Msk) == I2C_MSPCR_RCEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCR    RCEN    FL_I2C_Master_DisableRX
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableRX(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPCR, I2C_MSPCR_RCEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCR    PEN    FL_I2C_Master_EnableI2CStop
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableI2CStop(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPCR, I2C_MSPCR_PEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCR    RSEN    FL_I2C_Master_EnableI2CRestart
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableI2CRestart(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPCR, I2C_MSPCR_RSEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPCR    SEN    FL_I2C_Master_EnableI2CStart
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableI2CStart(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPCR, I2C_MSPCR_SEN_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    WCOLIE    FL_I2C_Master_EnableIT_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableIT_WriteConflict(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPIER, I2C_MSPIER_WCOLIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    WCOLIE    FL_I2C_Master_IsEnabledIT_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledIT_WriteConflict(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPIER, I2C_MSPIER_WCOLIE_Msk) == I2C_MSPIER_WCOLIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    WCOLIE    FL_I2C_Master_DisableIT_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableIT_WriteConflict(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPIER, I2C_MSPIER_WCOLIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    TOIE    FL_I2C_Master_EnableIT_Timeout
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableIT_Timeout(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPIER, I2C_MSPIER_TOIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    TOIE    FL_I2C_Master_IsEnabledIT_Timeout
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledIT_Timeout(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPIER, I2C_MSPIER_TOIE_Msk) == I2C_MSPIER_TOIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    TOIE    FL_I2C_Master_DisableIT_Timeout
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableIT_Timeout(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPIER, I2C_MSPIER_TOIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    SIE    FL_I2C_Master_EnableIT_Start
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableIT_Start(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPIER, I2C_MSPIER_SIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    SIE    FL_I2C_Master_IsEnabledIT_Start
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledIT_Start(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPIER, I2C_MSPIER_SIE_Msk) == I2C_MSPIER_SIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    SIE    FL_I2C_Master_DisableIT_Start
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableIT_Start(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPIER, I2C_MSPIER_SIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    PIE    FL_I2C_Master_EnableIT_Stop
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableIT_Stop(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPIER, I2C_MSPIER_PIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    PIE    FL_I2C_Master_IsEnabledIT_Stop
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledIT_Stop(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPIER, I2C_MSPIER_PIE_Msk) == I2C_MSPIER_PIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    PIE    FL_I2C_Master_DisableIT_Stop
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableIT_Stop(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPIER, I2C_MSPIER_PIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    NACKIE    FL_I2C_Master_EnableIT_NACK
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableIT_NACK(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPIER, I2C_MSPIER_NACKIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    NACKIE    FL_I2C_Master_IsEnabledIT_NACK
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledIT_NACK(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPIER, I2C_MSPIER_NACKIE_Msk) == I2C_MSPIER_NACKIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    NACKIE    FL_I2C_Master_DisableIT_NACK
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableIT_NACK(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPIER, I2C_MSPIER_NACKIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    TXIE    FL_I2C_Master_EnableIT_TXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableIT_TXComplete(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPIER, I2C_MSPIER_TXIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    TXIE    FL_I2C_Master_IsEnabledIT_TXComplete
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledIT_TXComplete(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPIER, I2C_MSPIER_TXIE_Msk) == I2C_MSPIER_TXIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    TXIE    FL_I2C_Master_DisableIT_TXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableIT_TXComplete(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPIER, I2C_MSPIER_TXIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    RXIE    FL_I2C_Master_EnableIT_RXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_EnableIT_RXComplete(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->MSPIER, I2C_MSPIER_RXIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    RXIE    FL_I2C_Master_IsEnabledIT_RXComplete
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsEnabledIT_RXComplete(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPIER, I2C_MSPIER_RXIE_Msk) == I2C_MSPIER_RXIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPIER    RXIE    FL_I2C_Master_DisableIT_RXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_DisableIT_RXComplete(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->MSPIER, I2C_MSPIER_RXIE_Msk);
}

/**
  * @brief
  * @rmtoll   MSPISR    WCOL    FL_I2C_Master_IsActiveFlag_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsActiveFlag_WriteConflict(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPISR, I2C_MSPISR_WCOL_Msk) == (I2C_MSPISR_WCOL_Msk));
}

/**
  * @brief
  * @rmtoll   MSPISR    WCOL    FL_I2C_Master_ClearFlag_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_ClearFlag_WriteConflict(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->MSPISR, I2C_MSPISR_WCOL_Msk);
}

/**
  * @brief
  * @rmtoll   MSPISR    TO    FL_I2C_Master_IsActiveFlag_Timeout
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsActiveFlag_Timeout(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPISR, I2C_MSPISR_TO_Msk) == (I2C_MSPISR_TO_Msk));
}

/**
  * @brief
  * @rmtoll   MSPISR    TO    FL_I2C_Master_ClearFlag_Timeout
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_ClearFlag_Timeout(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->MSPISR, I2C_MSPISR_TO_Msk);
}

/**
  * @brief
  * @rmtoll   MSPISR    S    FL_I2C_Master_IsActiveFlag_Start
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsActiveFlag_Start(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPISR, I2C_MSPISR_S_Msk) == (I2C_MSPISR_S_Msk));
}

/**
  * @brief
  * @rmtoll   MSPISR    P    FL_I2C_Master_IsActiveFlag_Stop
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsActiveFlag_Stop(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPISR, I2C_MSPISR_P_Msk) == (I2C_MSPISR_P_Msk));
}

/**
  * @brief
  * @rmtoll   MSPISR    ACKSTA    FL_I2C_Master_IsActiveFlag_NACK
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsActiveFlag_NACK(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPISR, I2C_MSPISR_ACKSTA_Msk) == (I2C_MSPISR_ACKSTA_Msk));
}

/**
  * @brief
  * @rmtoll   MSPISR    ACKSTA    FL_I2C_Master_ClearFlag_NACK
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_ClearFlag_NACK(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->MSPISR, I2C_MSPISR_ACKSTA_Msk);
}

/**
  * @brief
  * @rmtoll   MSPISR    TXIF    FL_I2C_Master_IsActiveFlag_TXComplete
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsActiveFlag_TXComplete(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPISR, I2C_MSPISR_TXIF_Msk) == (I2C_MSPISR_TXIF_Msk));
}

/**
  * @brief
  * @rmtoll   MSPISR    TXIF    FL_I2C_Master_ClearFlag_TXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_ClearFlag_TXComplete(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->MSPISR, I2C_MSPISR_TXIF_Msk);
}

/**
  * @brief
  * @rmtoll   MSPISR    RXIF    FL_I2C_Master_IsActiveFlag_RXComplete
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsActiveFlag_RXComplete(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPISR, I2C_MSPISR_RXIF_Msk) == (I2C_MSPISR_RXIF_Msk));
}

/**
  * @brief
  * @rmtoll   MSPISR    RXIF    FL_I2C_Master_ClearFlag_RXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_ClearFlag_RXComplete(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->MSPISR, I2C_MSPISR_RXIF_Msk);
}

/**
  * @brief
  * @rmtoll   MSPSR    BUSY    FL_I2C_Master_IsActiveFlag_Busy
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Master_IsActiveFlag_Busy(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPSR, I2C_MSPSR_BUSY_Msk) == (I2C_MSPSR_BUSY_Msk));
}

/**
  * @brief
  * @rmtoll   MSPSR    RW    FL_I2C_Master_GetDirection
  * @param    I2Cx I2C instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_I2C_MSP_DATA_DIRECTION_SLAVE_TO_MASTER
  *           @arg @ref FL_I2C_MSP_DATA_DIRECTION_MASTER_TO_SLAVE
  */
__STATIC_INLINE uint32_t FL_I2C_Master_GetDirection(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPSR, I2C_MSPSR_RW_Msk));
}

/**
  * @brief
  * @rmtoll   MSPSR    BF    FL_I2C_Master_GetBuffStatus
  * @param    I2Cx I2C instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_I2C_MSP_DATA_BUFF_STATUS_FULL
  *           @arg @ref FL_I2C_MSP_DATA_BUFF_STATUS_EMPTY
  */
__STATIC_INLINE uint32_t FL_I2C_Master_GetBuffStatus(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPSR, I2C_MSPSR_BF_Msk));
}

/**
  * @brief
  * @rmtoll   MSPSR    ACKMO    FL_I2C_Master_SetRespond
  * @param    I2Cx I2C instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_I2C_MASTER_RESPOND_ACK
  *           @arg @ref FL_I2C_MASTER_RESPOND_NACK
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_SetRespond(I2C_Type *I2Cx, uint32_t mode)
{
    MODIFY_REG(I2Cx->MSPSR, I2C_MSPSR_ACKMO_Msk, mode);
}

/**
  * @brief
  * @rmtoll   MSPSR    ACKMO    FL_I2C_Master_GetRespond
  * @param    I2Cx I2C instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_I2C_MASTER_RESPOND_ACK
  *           @arg @ref FL_I2C_MASTER_RESPOND_NACK
  */
__STATIC_INLINE uint32_t FL_I2C_Master_GetRespond(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPSR, I2C_MSPSR_ACKMO_Msk));
}

/**
  * @brief
  * @rmtoll   MSPBGR    MSPBGRH    FL_I2C_Master_WriteSCLHighWidth
  * @param    I2Cx I2C instance
  * @param    width
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_WriteSCLHighWidth(I2C_Type *I2Cx, uint32_t width)
{
    MODIFY_REG(I2Cx->MSPBGR, (0x1ffU << 16U), (width << 16U));
}

/**
  * @brief
  * @rmtoll   MSPBGR    MSPBGRH    FL_I2C_Master_ReadSCLHighWidth
  * @param    I2Cx I2C instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_I2C_Master_ReadSCLHighWidth(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPBGR, (0x1ffU << 16U)) >> 16U);
}

/**
  * @brief
  * @rmtoll   MSPBGR    MSPBGRL    FL_I2C_Master_WriteSCLLowWidth
  * @param    I2Cx I2C instance
  * @param    width
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_WriteSCLLowWidth(I2C_Type *I2Cx, uint32_t width)
{
    MODIFY_REG(I2Cx->MSPBGR, (0x1ffU << 0U), (width << 0U));
}

/**
  * @brief
  * @rmtoll   MSPBGR    MSPBGRL    FL_I2C_Master_ReadSCLLowWidth
  * @param    I2Cx I2C instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_I2C_Master_ReadSCLLowWidth(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPBGR, (0x1ffU << 0U)) >> 0U);
}

/**
  * @brief
  * @rmtoll   MSPBUF    MSPBUF    FL_I2C_Master_WriteTXBuff
  * @param    I2Cx I2C instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_WriteTXBuff(I2C_Type *I2Cx, uint32_t data)
{
    MODIFY_REG(I2Cx->MSPBUF, (0xffU << 0U), (data << 0U));
}

/**
  * @brief
  * @rmtoll   MSPBUF    MSPBUF    FL_I2C_Master_ReadRXBuff
  * @param    I2Cx I2C instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_I2C_Master_ReadRXBuff(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPBUF, (0xffU << 0U)) >> 0U);
}

/**
  * @brief
  * @rmtoll   MSPTCR    SDAHD    FL_I2C_Master_WriteSDAHoldTime
  * @param    I2Cx I2C instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_WriteSDAHoldTime(I2C_Type *I2Cx, uint32_t time)
{
    MODIFY_REG(I2Cx->MSPTCR, (0x1ffU << 0U), (time << 0U));
}

/**
  * @brief
  * @rmtoll   MSPTCR    SDAHD    FL_I2C_Master_ReadSDAHoldTime
  * @param    I2Cx I2C instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_I2C_Master_ReadSDAHoldTime(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPTCR, (0x1ffU << 0U)) >> 0U);
}

/**
  * @brief
  * @rmtoll   MSPTOR    TIMEOUT    FL_I2C_Master_WriteSlaveSCLTimeout
  * @param    I2Cx I2C instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Master_WriteSlaveSCLTimeout(I2C_Type *I2Cx, uint32_t time)
{
    MODIFY_REG(I2Cx->MSPTOR, (0xfffU << 0U), (time << 0U));
}

/**
  * @brief
  * @rmtoll   MSPTOR    TIMEOUT    FL_I2C_Master_ReadSlaveSCLTimeout
  * @param    I2Cx I2C instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_I2C_Master_ReadSlaveSCLTimeout(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->MSPTOR, (0xfffU << 0U)) >> 0U);
}

/**
  * @brief
  * @rmtoll   SSPCR    SCLSEN    FL_I2C_Slave_EnableSCLStretching
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableSCLStretching(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPCR, I2C_SSPCR_SCLSEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SCLSEN    FL_I2C_Slave_IsEnabledSCLStretching
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledSCLStretching(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPCR, I2C_SSPCR_SCLSEN_Msk) == I2C_SSPCR_SCLSEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SCLSEN    FL_I2C_Slave_DisableSCLStretching
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableSCLStretching(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPCR, I2C_SSPCR_SCLSEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    DMAEN    FL_I2C_Slave_EnableDMAReq
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableDMAReq(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPCR, I2C_SSPCR_DMAEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    DMAEN    FL_I2C_Slave_IsEnabledDMAReq
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledDMAReq(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPCR, I2C_SSPCR_DMAEN_Msk) == I2C_SSPCR_DMAEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    DMAEN    FL_I2C_Slave_DisableDMAReq
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableDMAReq(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPCR, I2C_SSPCR_DMAEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    ACKEN    FL_I2C_Slave_EnableACK
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableACK(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPCR, I2C_SSPCR_ACKEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    ACKEN    FL_I2C_Slave_IsEnabledACK
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledACK(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPCR, I2C_SSPCR_ACKEN_Msk) == I2C_SSPCR_ACKEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    ACKEN    FL_I2C_Slave_DisableACK
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableACK(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPCR, I2C_SSPCR_ACKEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SDAO_DLYEN    FL_I2C_Slave_EnableSDAStretching
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableSDAStretching(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPCR, I2C_SSPCR_SDAO_DLYEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SDAO_DLYEN    FL_I2C_Slave_IsEnabledSDAStretching
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledSDAStretching(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPCR, I2C_SSPCR_SDAO_DLYEN_Msk) == I2C_SSPCR_SDAO_DLYEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SDAO_DLYEN    FL_I2C_Slave_DisableSDAStretching
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableSDAStretching(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPCR, I2C_SSPCR_SDAO_DLYEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SCLI_ANFEN    FL_I2C_Slave_EnableSCLAnalogFilter
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableSCLAnalogFilter(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPCR, I2C_SSPCR_SCLI_ANFEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SCLI_ANFEN    FL_I2C_Slave_IsEnabledSCLAnalogFilter
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledSCLAnalogFilter(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPCR, I2C_SSPCR_SCLI_ANFEN_Msk) == I2C_SSPCR_SCLI_ANFEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SCLI_ANFEN    FL_I2C_Slave_DisableSCLAnalogFilter
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableSCLAnalogFilter(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPCR, I2C_SSPCR_SCLI_ANFEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    A10EN    FL_I2C_Slave_Enable10BitAddress
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_Enable10BitAddress(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPCR, I2C_SSPCR_A10EN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    A10EN    FL_I2C_Slave_IsEnabled10BitAddress
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabled10BitAddress(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPCR, I2C_SSPCR_A10EN_Msk) == I2C_SSPCR_A10EN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    A10EN    FL_I2C_Slave_Disable10BitAddress
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_Disable10BitAddress(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPCR, I2C_SSPCR_A10EN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SSPEN    FL_I2C_Slave_Enable
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_Enable(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPCR, I2C_SSPCR_SSPEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SSPEN    FL_I2C_Slave_IsEnabled
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabled(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPCR, I2C_SSPCR_SSPEN_Msk) == I2C_SSPCR_SSPEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPCR    SSPEN    FL_I2C_Slave_Disable
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_Disable(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPCR, I2C_SSPCR_SSPEN_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    ADEIE    FL_I2C_Slave_EnableIT_AddressError
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableIT_AddressError(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPIER, I2C_SSPIER_ADEIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    ADEIE    FL_I2C_Slave_IsEnabledIT_AddressError
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledIT_AddressError(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPIER, I2C_SSPIER_ADEIE_Msk) == I2C_SSPIER_ADEIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    ADEIE    FL_I2C_Slave_DisableIT_AddressError
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableIT_AddressError(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPIER, I2C_SSPIER_ADEIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    SIE    FL_I2C_Slave_EnableIT_Start
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableIT_Start(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPIER, I2C_SSPIER_SIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    SIE    FL_I2C_Slave_IsEnabledIT_Start
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledIT_Start(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPIER, I2C_SSPIER_SIE_Msk) == I2C_SSPIER_SIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    SIE    FL_I2C_Slave_DisableIT_Start
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableIT_Start(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPIER, I2C_SSPIER_SIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    PIE    FL_I2C_Slave_EnableIT_Stop
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableIT_Stop(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPIER, I2C_SSPIER_PIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    PIE    FL_I2C_Slave_IsEnabledIT_Stop
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledIT_Stop(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPIER, I2C_SSPIER_PIE_Msk) == I2C_SSPIER_PIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    PIE    FL_I2C_Slave_DisableIT_Stop
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableIT_Stop(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPIER, I2C_SSPIER_PIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    WCOLIE    FL_I2C_Slave_EnableIT_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableIT_WriteConflict(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPIER, I2C_SSPIER_WCOLIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    WCOLIE    FL_I2C_Slave_IsEnabledIT_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledIT_WriteConflict(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPIER, I2C_SSPIER_WCOLIE_Msk) == I2C_SSPIER_WCOLIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    WCOLIE    FL_I2C_Slave_DisableIT_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableIT_WriteConflict(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPIER, I2C_SSPIER_WCOLIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    SSPOVIE    FL_I2C_Slave_EnableIT_BuffOverflow
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableIT_BuffOverflow(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPIER, I2C_SSPIER_SSPOVIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    SSPOVIE    FL_I2C_Slave_IsEnabledIT_BuffOverflow
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledIT_BuffOverflow(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPIER, I2C_SSPIER_SSPOVIE_Msk) == I2C_SSPIER_SSPOVIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    SSPOVIE    FL_I2C_Slave_DisableIT_BuffOverflow
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableIT_BuffOverflow(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPIER, I2C_SSPIER_SSPOVIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    ADMIE    FL_I2C_Slave_EnableIT_AddressMatch
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableIT_AddressMatch(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPIER, I2C_SSPIER_ADMIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    ADMIE    FL_I2C_Slave_IsEnabledIT_AddressMatch
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledIT_AddressMatch(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPIER, I2C_SSPIER_ADMIE_Msk) == I2C_SSPIER_ADMIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    ADMIE    FL_I2C_Slave_DisableIT_AddressMatch
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableIT_AddressMatch(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPIER, I2C_SSPIER_ADMIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    TXIE    FL_I2C_Slave_EnableIT_TXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableIT_TXComplete(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPIER, I2C_SSPIER_TXIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    TXIE    FL_I2C_Slave_IsEnabledIT_TXComplete
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledIT_TXComplete(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPIER, I2C_SSPIER_TXIE_Msk) == I2C_SSPIER_TXIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    TXIE    FL_I2C_Slave_DisableIT_TXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableIT_TXComplete(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPIER, I2C_SSPIER_TXIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    RXIE    FL_I2C_Slave_EnableIT_RXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_EnableIT_RXComplete(I2C_Type *I2Cx)
{
    SET_BIT(I2Cx->SSPIER, I2C_SSPIER_RXIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    RXIE    FL_I2C_Slave_IsEnabledIT_RXComplete
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsEnabledIT_RXComplete(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPIER, I2C_SSPIER_RXIE_Msk) == I2C_SSPIER_RXIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPIER    RXIE    FL_I2C_Slave_DisableIT_RXCompleted
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_DisableIT_RXComplete(I2C_Type *I2Cx)
{
    CLEAR_BIT(I2Cx->SSPIER, I2C_SSPIER_RXIE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPISR    ADE    FL_I2C_Slave_IsActiveFlag_AddressError
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_AddressError(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPISR, I2C_SSPISR_ADE_Msk) == (I2C_SSPISR_ADE_Msk));
}

/**
  * @brief
  * @rmtoll   SSPISR    ADE    FL_I2C_Slave_ClearFlag_AddressError
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_ClearFlag_AddressError(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->SSPISR, I2C_SSPISR_ADE_Msk);
}

/**
  * @brief
  * @rmtoll   SSPISR    S    FL_I2C_Slave_IsActiveFlag_Start
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_Start(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPISR, I2C_SSPISR_S_Msk) == (I2C_SSPISR_S_Msk));
}

/**
  * @brief
  * @rmtoll   SSPISR    P    FL_I2C_Slave_IsActiveFlag_Stop
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_Stop(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPISR, I2C_SSPISR_P_Msk) == (I2C_SSPISR_P_Msk));
}

/**
  * @brief
  * @rmtoll   SSPISR    WCOL    FL_I2C_Slave_IsActiveFlag_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_WriteConflict(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPISR, I2C_SSPISR_WCOL_Msk) == (I2C_SSPISR_WCOL_Msk));
}

/**
  * @brief
  * @rmtoll   SSPISR    WCOL    FL_I2C_Slave_ClearFlag_WriteConflict
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_ClearFlag_WriteConflict(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->SSPISR, I2C_SSPISR_WCOL_Msk);
}

/**
  * @brief
  * @rmtoll   SSPISR    SSPOV    FL_I2C_Slave_IsActiveFlag_BuffOverflow
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_BuffOverflow(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPISR, I2C_SSPISR_SSPOV_Msk) == (I2C_SSPISR_SSPOV_Msk));
}
/**
  * @brief
  * @rmtoll   SSPISR    SSPOV    FL_I2C_Slave_ClearFlag_BuffOverflow
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_ClearFlag_BuffOverflow(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->SSPISR, I2C_SSPISR_SSPOV_Msk);
}

/**
  * @brief
  * @rmtoll   SSPISR    ADM    FL_I2C_Slave_IsActiveFlag_AddressMatch
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_AddressMatch(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPISR, I2C_SSPISR_ADM_Msk) == (I2C_SSPISR_ADM_Msk));
}

/**
  * @brief
  * @rmtoll   SSPISR    ADM    FL_I2C_Slave_ClearFlag_AddressMatch
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_ClearFlag_AddressMatch(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->SSPISR, I2C_SSPISR_ADM_Msk);
}

/**
  * @brief
  * @rmtoll   SSPISR    TXIF    FL_I2C_Slave_IsActiveFlag_TXComplete
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_TXComplete(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPISR, I2C_SSPISR_TXIF_Msk) == (I2C_SSPISR_TXIF_Msk));
}

/**
  * @brief
  * @rmtoll   SSPISR    TXIF    FL_I2C_Slave_ClearFlag_TXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_ClearFlag_TXComplete(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->SSPISR, I2C_SSPISR_TXIF_Msk);
}

/**
  * @brief
  * @rmtoll   SSPISR    RXIF    FL_I2C_Slave_IsActiveFlag_RXComplete
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_RXComplete(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPISR, I2C_SSPISR_RXIF_Msk) == (I2C_SSPISR_RXIF_Msk));
}

/**
  * @brief
  * @rmtoll   SSPISR    RXIF    FL_I2C_Slave_ClearFlag_RXComplete
  * @param    I2Cx I2C instance
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_ClearFlag_RXComplete(I2C_Type *I2Cx)
{
    WRITE_REG(I2Cx->SSPISR, I2C_SSPISR_RXIF_Msk);
}

/**
  * @brief
  * @rmtoll   SSPSR    BUSY    FL_I2C_Slave_IsActiveFlag_Busy
  * @param    I2Cx I2C instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_IsActiveFlag_Busy(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPSR, I2C_SSPSR_BUSY_Msk) == (I2C_SSPSR_BUSY_Msk));
}

/**
  * @brief
  * @rmtoll   SSPSR    RW    FL_I2C_Slave_GetDataDirection
  * @param    I2Cx I2C instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_I2C_SSP_DATA_DIRECTION_SLAVE_TO_MASTER
  *           @arg @ref FL_I2C_SSP_DATA_DIRECTION_MASTER_TO_SLAVE
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_GetDataDirection(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPSR, I2C_SSPSR_RW_Msk));
}

/**
  * @brief
  * @rmtoll   SSPSR    DA    FL_I2C_Slave_GetDataType
  * @param    I2Cx I2C instance
  * @param    I2Cx I2C instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_I2C_SSP_DATA_TYPE_DATA
  *           @arg @ref FL_I2C_SSP_DATA_TYPE_ADDR
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_GetDataType(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPSR, I2C_SSPSR_DA_Msk));
}
/**
  * @brief
  * @rmtoll   SSPSR    BF    FL_I2C_Slave_GetBuffStatus
  * @param    I2Cx I2C instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_I2C_SSP_DATA_BUFF_STATUS_FULL
  *           @arg @ref FL_I2C_SSP_DATA_BUFF_STATUS_EMPTY
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_GetBuffStatus(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPSR, I2C_SSPSR_BF_Msk));
}

/**
  * @brief
  * @rmtoll   SSPBUF        FL_I2C_Slave_WriteTXBuff
  * @param    I2Cx I2C instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_WriteTXBuff(I2C_Type *I2Cx, uint32_t data)
{
    MODIFY_REG(I2Cx->SSPBUF, (0xffU << 0U), (data << 0U));
}

/**
  * @brief
  * @rmtoll   SSPBUF        FL_I2C_Slave_ReadRXBuff
  * @param    I2Cx I2C instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_ReadRXBuff(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPBUF, (0xffU << 0U)) >> 0U);
}

/**
  * @brief
  * @rmtoll   SSPADR        FL_I2C_Slave_WriteSlaveAddress
  * @param    I2Cx I2C instance
  * @param    address
  * @retval   None
  */
__STATIC_INLINE void FL_I2C_Slave_WriteSlaveAddress(I2C_Type *I2Cx, uint32_t address)
{
    MODIFY_REG(I2Cx->SSPADR, (0x3ffU << 0U), (address << 0U));
}

/**
  * @brief
  * @rmtoll   SSPADR        FL_I2C_Slave_ReadSlaveAddress
  * @param    I2Cx I2C instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_I2C_Slave_ReadSlaveAddress(I2C_Type *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->SSPADR, (0x3ffU << 0U)) >> 0U);
}

/**
  * @}
  */

/** @defgroup I2C_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_I2C_DeInit(I2C_Type *I2Cx);
void FL_I2C_SlaveMode_StructInit(FL_I2C_SlaveMode_InitTypeDef *I2C_InitStruct);
void FL_I2C_MasterMode_StructInit(FL_I2C_MasterMode_InitTypeDef *I2C_InitStruct);
FL_ErrorStatus FL_I2C_SlaveMode_Init(I2C_Type *I2cx, FL_I2C_SlaveMode_InitTypeDef *I2C_InitStruct);
FL_ErrorStatus FL_I2C_MasterMode_Init(I2C_Type *I2Cx, FL_I2C_MasterMode_InitTypeDef *I2C_InitStruct);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LC0XX_FL_I2C_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-12*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
