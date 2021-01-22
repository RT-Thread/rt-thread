/**
 *******************************************************************************
 * @file  hc32f4a0_hash.h
 * @brief This file contains all the functions prototypes of the HASH driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb         First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_HASH_H__
#define __HC32F4A0_HASH_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_HASH
 * @{
 */

#if (DDL_HASH_ENABLE == DDL_ON)

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

#define HASH_GROUP_LEN               (64U)
#define LAST_GROUP_MAX_LEN           (56U)

/** @defgroup HASH_Mode HASH Mode
  * @{
  */
#define HASH_MODE_SHA_256            (0x00000000UL)       /*!< SHA_256 Operating mode */
#define HASH_MODE_HMAC               (0x00000010UL)       /*!< HMAC Operating mode */
/**
 * @}
 */

/**
 * @defgroup HASH_Key_Len HASH Key Length
 * @{
 */
#define HASH_KEY_LEN_LONG            (HASH_CR_LKEY)             /*!< Key length > 64 Bytes */
#define HASH_KEY_LEN_SHORT           (0x0UL)                    /*!< Key length <= 64 Bytes */
/**
 * @}
 */

/**
 * @defgroup HASH_Interrupt_Definition HASH Interrupt Definition
 * @{
 */
#define HASH_INT_GROUP               (HASH_CR_HEIE)             /*!< A set of data operations complete interrupt */
#define HASH_INT_ALL                 (HASH_CR_HCIE)             /*!< All data operations complete interrupt */
/**
 * @}
 */

/**
 * @defgroup HASH_Msg_Group HASH Messages Group
 * @{
 */
#define HASH_MSG_GRP_FIRST           (HASH_CR_FST_GRP)          /*!< The first group of messages or keys */
#define HASH_MSG_GRP_END             (HASH_CR_KMSG_END)         /*!< The last group of messages or keys */
#define HASH_MSG_GRP_ONLY_ONE        (HASH_CR_FST_GRP | \
                                      HASH_CR_KMSG_END)         /*!< Only one set of message or key */
/**
 * @}
 */

/**
 * @defgroup HASH_Status HASH Status
 * @{
 */
#define HASH_FLAG_START              (HASH_CR_START)            /*!< Operation in progress */
#define HASH_FLAG_BUSY               (HASH_CR_BUSY)             /*!< HASH in operation */
#define HASH_FLAG_CYC_END            (HASH_CR_CYC_END)          /*!< key or message operation completed */
#define HASH_FLAG_HMAC_END           (HASH_CR_HMAC_END)         /*!< HMAC operation completed */
/**
 * @}
 */

/**
 * @defgroup HASH_Common_Trigger_Sel HASH common trigger source select
 * @{
 */
#define HASH_COM_TRIG1               (AOS_HASH_ITRGSELA_COMTRG_EN_0)
#define HASH_COM_TRIG2               (AOS_HASH_ITRGSELA_COMTRG_EN_1)
#define HASH_COM_TRIG_MASk           (AOS_HASH_ITRGSELA_COMTRG_EN)
/**
 * @}
 */

/**
 * @defgroup HASH_Common_Trigger_Reg_Sel HASH common trigger cource select
 * @{
 */
#define HASH_TRIG_REG_BLKCOM          (0U)              /*!< DMA block transfer complete register */
#define HASH_TRIG_REG_TRNCOM          (1U)              /*!< DMA transfer complete register*/
/**
 * @}
 */

/**
 * @defgroup HASH_Trigger_Source_Sel HASH Trigger Source Select
 * @{
 */
#define HASH_TRG_SRC_DMA1_BTC0         (EVT_DMA1_BTC0)              /*!< Select the DMA1 ch0 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC1         (EVT_DMA1_BTC1)              /*!< Select the DMA1 ch1 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC2         (EVT_DMA1_BTC2)              /*!< Select the DMA1 ch2 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC3         (EVT_DMA1_BTC3)              /*!< Select the DMA1 ch3 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC4         (EVT_DMA1_BTC4)              /*!< Select the DMA1 ch4 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC5         (EVT_DMA1_BTC5)              /*!< Select the DMA1 ch5 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC6         (EVT_DMA1_BTC6)              /*!< Select the DMA1 ch6 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC7         (EVT_DMA1_BTC7)              /*!< Select the DMA1 ch7 block transfer complete */
#define HASH_TRG_SRC_DMA1_TC0          (EVT_DMA1_TC0)               /*!< Select the DMA1 ch0 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC1          (EVT_DMA1_TC1)               /*!< Select the DMA1 ch1 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC2          (EVT_DMA1_TC2)               /*!< Select the DMA1 ch2 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC3          (EVT_DMA1_TC3)               /*!< Select the DMA1 ch3 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC4          (EVT_DMA1_TC4)               /*!< Select the DMA1 ch4 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC5          (EVT_DMA1_TC5)               /*!< Select the DMA1 ch5 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC6          (EVT_DMA1_TC6)               /*!< Select the DMA1 ch6 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC7          (EVT_DMA1_TC7)               /*!< Select the DMA1 ch7 transfer complete*/
#define HASH_TRG_SRC_DMA2_BTC0         (EVT_DMA2_BTC0)              /*!< Select the DMA2 ch0 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC1         (EVT_DMA2_BTC1)              /*!< Select the DMA2 ch1 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC2         (EVT_DMA2_BTC2)              /*!< Select the DMA2 ch2 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC3         (EVT_DMA2_BTC3)              /*!< Select the DMA2 ch3 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC4         (EVT_DMA2_BTC4)              /*!< Select the DMA2 ch4 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC5         (EVT_DMA2_BTC5)              /*!< Select the DMA2 ch5 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC6         (EVT_DMA2_BTC6)              /*!< Select the DMA2 ch6 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC7         (EVT_DMA2_BTC7)              /*!< Select the DMA2 ch7 block transfer complete */
#define HASH_TRG_SRC_DMA2_TC0          (EVT_DMA2_TC0)               /*!< Select the DMA2 ch0 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC1          (EVT_DMA2_TC1)               /*!< Select the DMA2 ch1 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC2          (EVT_DMA2_TC2)               /*!< Select the DMA2 ch2 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC3          (EVT_DMA2_TC3)               /*!< Select the DMA2 ch3 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC4          (EVT_DMA2_TC4)               /*!< Select the DMA2 ch4 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC5          (EVT_DMA2_TC5)               /*!< Select the DMA2 ch5 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC6          (EVT_DMA2_TC6)               /*!< Select the DMA2 ch6 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC7          (EVT_DMA2_TC7)               /*!< Select the DMA2 ch7 transfer complete*/
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
en_result_t HASH_Calculate(const void *pvSrcData,
                           uint32_t u32SrcDataSize,
                           uint8_t au8MsgDigest[]);
en_result_t HMAC_Calculate(const void *pvSrcData,
                           uint32_t u32SrcDataSize,
                           const uint8_t au8Key[],
                           uint32_t u32KeyLength,
                           uint8_t au8MsgDigest[]);
en_result_t HASH_Start(void);
en_result_t HASH_IntCmd(uint32_t u32HashInt, en_functional_state_t enNewState);
en_result_t HASH_SetMode(uint32_t u32HashMode);
en_result_t HASH_SetKeyLength(uint32_t u32KeyLen);
en_result_t HASH_MsgGrpConfig(uint32_t u32MsgGroup);
en_result_t HASH_ClearStatus(uint32_t u32ClearFlag);
void HASH_SetTriggerSrc(en_event_src_t enSrc);
void HASH_ComTriggerCmd(uint8_t u8TrigReg, uint32_t u32ComTrig, \
                        en_functional_state_t enNewState);
en_flag_status_t HASH_GetStatus(uint32_t u32HashFlag);
void HASH_GetResult(uint8_t au8MsgDigest[]);
/**
 * @}
 */

#endif /* DDL_HASH_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_HASH_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
