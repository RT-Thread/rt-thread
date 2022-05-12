/**
 *******************************************************************************
 * @file  hc32_ll_hash.h
 * @brief This file contains all the functions prototypes of the HASH driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_HASH_H__
#define __HC32_LL_HASH_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_HASH
 * @{
 */

#if (LL_HASH_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup HASH_Global_Macros HASH Global Macros
 * @{
 */

/**
 * @defgroup HASH_Mode HASH Mode
 * @{
 */
#define HASH_MD_SHA256              (0x0UL)                     /*!< SHA256 operating mode */
#define HASH_MD_HMAC                (HASH_CR_MODE_0)            /*!< HMAC operating mode */
/**
 * @}
 */

/**
 * @defgroup HASH_Key_Size_Mode HASH Key Size Mode
 * @{
 */
#define HASH_KEY_MD_SHORT_SIZE      (0x0UL)                     /*!< Key length <= 64 Bytes */
#define HASH_KEY_MD_LONG_SIZE       (HASH_CR_LKEY)              /*!< Key length > 64 Bytes */
/**
 * @}
 */

/**
 * @defgroup HASH_Interrupt HASH Interrupt
 * @{
 */
#define HASH_INT_GRP                (HASH_CR_HEIE)              /*!< A set of data operations complete interrupt */
#define HASH_INT_ALL_CPLT           (HASH_CR_HCIE)              /*!< All data operations complete interrupt */
#define HASH_INT_ALL                (HASH_INT_GRP | HASH_INT_ALL_CPLT)
/**
 * @}
 */

/**
 * @defgroup HASH_Msg_Group HASH Messages Group
 * @{
 */
#define HASH_MSG_GRP_FIRST          (HASH_CR_FST_GRP)           /*!< The first group of messages or keys */
#define HASH_MSG_GRP_END            (HASH_CR_KMSG_END)          /*!< The last group of messages or keys */
#define HASH_MSG_GRP_ONLY_ONE       (HASH_CR_FST_GRP | \
                                     HASH_CR_KMSG_END)          /*!< Only one set of message or key */
/**
 * @}
 */

/**
 * @defgroup HASH_Status_Flag HASH Status Flag
 * @{
 */
#define HASH_FLAG_START             (HASH_CR_START)             /*!< Operation in progress */
#define HASH_FLAG_BUSY              (HASH_CR_BUSY)              /*!< HASH in operation */
#define HASH_FLAG_CYC_END           (HASH_CR_CYC_END)           /*!< key or message operation completed */
#define HASH_FLAG_HMAC_END          (HASH_CR_HMAC_END)          /*!< HMAC operation completed */
#define HASH_FLAG_ALL               (HASH_FLAG_START | HASH_FLAG_BUSY | \
                                     HASH_FLAG_CYC_END | HASH_FLAG_HMAC_END)
#define HASH_FLAG_CLR_ALL           (HASH_FLAG_CYC_END | HASH_FLAG_HMAC_END)
/**
 * @}
 */

/**
 * @defgroup HASH_Trigger_Event HASH Trigger Event
 * @{
 */
#define HASH_TRIG_EVT_DMA1_TC0      (EVT_SRC_DMA1_TC0)          /*!< Select the DMA1 ch0 transfer complete*/
#define HASH_TRIG_EVT_DMA1_TC1      (EVT_SRC_DMA1_TC1)          /*!< Select the DMA1 ch1 transfer complete*/
#define HASH_TRIG_EVT_DMA1_TC2      (EVT_SRC_DMA1_TC2)          /*!< Select the DMA1 ch2 transfer complete*/
#define HASH_TRIG_EVT_DMA1_TC3      (EVT_SRC_DMA1_TC3)          /*!< Select the DMA1 ch3 transfer complete*/
#define HASH_TRIG_EVT_DMA1_TC4      (EVT_SRC_DMA1_TC4)          /*!< Select the DMA1 ch4 transfer complete*/
#define HASH_TRIG_EVT_DMA1_TC5      (EVT_SRC_DMA1_TC5)          /*!< Select the DMA1 ch5 transfer complete*/
#define HASH_TRIG_EVT_DMA1_TC6      (EVT_SRC_DMA1_TC6)          /*!< Select the DMA1 ch6 transfer complete*/
#define HASH_TRIG_EVT_DMA1_TC7      (EVT_SRC_DMA1_TC7)          /*!< Select the DMA1 ch7 transfer complete*/
#define HASH_TRIG_EVT_DMA1_BTC0     (EVT_SRC_DMA1_BTC0)         /*!< Select the DMA1 ch0 block transfer complete */
#define HASH_TRIG_EVT_DMA1_BTC1     (EVT_SRC_DMA1_BTC1)         /*!< Select the DMA1 ch1 block transfer complete */
#define HASH_TRIG_EVT_DMA1_BTC2     (EVT_SRC_DMA1_BTC2)         /*!< Select the DMA1 ch2 block transfer complete */
#define HASH_TRIG_EVT_DMA1_BTC3     (EVT_SRC_DMA1_BTC3)         /*!< Select the DMA1 ch3 block transfer complete */
#define HASH_TRIG_EVT_DMA1_BTC4     (EVT_SRC_DMA1_BTC4)         /*!< Select the DMA1 ch4 block transfer complete */
#define HASH_TRIG_EVT_DMA1_BTC5     (EVT_SRC_DMA1_BTC5)         /*!< Select the DMA1 ch5 block transfer complete */
#define HASH_TRIG_EVT_DMA1_BTC6     (EVT_SRC_DMA1_BTC6)         /*!< Select the DMA1 ch6 block transfer complete */
#define HASH_TRIG_EVT_DMA1_BTC7     (EVT_SRC_DMA1_BTC7)         /*!< Select the DMA1 ch7 block transfer complete */

#define HASH_TRIG_EVT_DMA2_TC0      (EVT_SRC_DMA2_TC0)          /*!< Select the DMA2 ch0 transfer complete*/
#define HASH_TRIG_EVT_DMA2_TC1      (EVT_SRC_DMA2_TC1)          /*!< Select the DMA2 ch1 transfer complete*/
#define HASH_TRIG_EVT_DMA2_TC2      (EVT_SRC_DMA2_TC2)          /*!< Select the DMA2 ch2 transfer complete*/
#define HASH_TRIG_EVT_DMA2_TC3      (EVT_SRC_DMA2_TC3)          /*!< Select the DMA2 ch3 transfer complete*/
#define HASH_TRIG_EVT_DMA2_TC4      (EVT_SRC_DMA2_TC4)          /*!< Select the DMA2 ch4 transfer complete*/
#define HASH_TRIG_EVT_DMA2_TC5      (EVT_SRC_DMA2_TC5)          /*!< Select the DMA2 ch5 transfer complete*/
#define HASH_TRIG_EVT_DMA2_TC6      (EVT_SRC_DMA2_TC6)          /*!< Select the DMA2 ch6 transfer complete*/
#define HASH_TRIG_EVT_DMA2_TC7      (EVT_SRC_DMA2_TC7)          /*!< Select the DMA2 ch7 transfer complete*/
#define HASH_TRIG_EVT_DMA2_BTC0     (EVT_SRC_DMA2_BTC0)         /*!< Select the DMA2 ch0 block transfer complete */
#define HASH_TRIG_EVT_DMA2_BTC1     (EVT_SRC_DMA2_BTC1)         /*!< Select the DMA2 ch1 block transfer complete */
#define HASH_TRIG_EVT_DMA2_BTC2     (EVT_SRC_DMA2_BTC2)         /*!< Select the DMA2 ch2 block transfer complete */
#define HASH_TRIG_EVT_DMA2_BTC3     (EVT_SRC_DMA2_BTC3)         /*!< Select the DMA2 ch3 block transfer complete */
#define HASH_TRIG_EVT_DMA2_BTC4     (EVT_SRC_DMA2_BTC4)         /*!< Select the DMA2 ch4 block transfer complete */
#define HASH_TRIG_EVT_DMA2_BTC5     (EVT_SRC_DMA2_BTC5)         /*!< Select the DMA2 ch5 block transfer complete */
#define HASH_TRIG_EVT_DMA2_BTC6     (EVT_SRC_DMA2_BTC6)         /*!< Select the DMA2 ch6 block transfer complete */
#define HASH_TRIG_EVT_DMA2_BTC7     (EVT_SRC_DMA2_BTC7)         /*!< Select the DMA2 ch7 block transfer complete */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup HASH_Global_Functions
 * @{
 */

int32_t HASH_Calculate(const uint8_t *pu8SrcData, uint32_t u32SrcDataSize, uint8_t *pu8MsgDigest);

int32_t HASH_HMAC_Calculate(const uint8_t *pu8SrcData, uint32_t u32SrcDataSize,
                            const uint8_t *pu8Key, uint32_t u32KeySize,
                            uint8_t *pu8MsgDigest);

int32_t HASH_IntCmd(uint32_t u32HashInt, en_functional_state_t enNewState);
en_flag_status_t HASH_GetStatus(uint32_t u32Flag);
int32_t HASH_ClearStatus(uint32_t u32Flag);

int32_t HASH_SetMode(uint32_t u32HashMode);
int32_t HASH_SetKeySizeMode(uint32_t u32SizeMode);
int32_t HASH_SetMsgGroup(uint32_t u32MsgGroup);
int32_t HASH_Start(void);
void HASH_GetMsgDigest(uint8_t *pu8MsgDigest);

/**
 * @}
 */

#endif /* LL_HASH_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_HASH_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
