/**
 *******************************************************************************
 * @file  hc32_ll_i2s.h
 * @brief This file contains all the functions prototypes of the I2S driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_I2S_H__
#define __HC32_LL_I2S_H__

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
 * @addtogroup LL_I2S
 * @{
 */

#if (LL_I2S_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup I2S_Global_Types I2S Global Types
 * @{
 */

/**
 * @brief I2S Init structure definition
 */
typedef struct {
    uint32_t u32ClockSrc;               /*!< Specifies the clock source of I2S.
                                             This parameter can be a value of @ref I2S_Clock_Source */
    uint32_t u32Mode;                   /*!< Specifies the master/slave mode of I2S.
                                             This parameter can be a value of @ref I2S_Mode */
    uint32_t u32Protocol;               /*!< Specifies the communication protocol of I2S.
                                             This parameter can be a value of @ref I2S_Protocol */
    uint32_t u32TransMode;              /*!< Specifies the transmission mode for the I2S communication.
                                             This parameter can be a value of @ref I2S_Trans_Mode */
    uint32_t u32AudioFreq;              /*!< Specifies the frequency selected for the I2S communication.
                                             This parameter can be a value of @ref I2S_Audio_Frequency */
    uint32_t u32ChWidth;                /*!< Specifies the channel length for the I2S communication.
                                             This parameter can be a value of @ref I2S_Channel_Length */
    uint32_t u32DataWidth;              /*!< Specifies the data length for the I2S communication.
                                             This parameter can be a value of @ref I2S_Data_Length */
    uint32_t u32MCKOutput;              /*!< Specifies the validity of the MCK output for I2S.
                                             This parameter can be a value of @ref I2S_MCK_Output */
    uint32_t u32TransFIFOLevel;         /*!< Specifies the level of transfer FIFO.
                                             This parameter can be a value of @ref I2S_Trans_Level */
    uint32_t u32ReceiveFIFOLevel;       /*!< Specifies the level of receive FIFO.
                                             This parameter can be a value of @ref I2S_Receive_Level */
} stc_i2s_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup I2S_Global_Macros I2S Global Macros
 * @{
 */

/**
 * @defgroup I2S_External_Clock_Frequency I2S External Clock Frequency
 * @{
 */
#ifndef I2S_EXT_CLK_FREQ
#define I2S_EXT_CLK_FREQ                        (12288000UL)    /*!< Value of the external oscillator */
#endif /* I2S_EXT_CLK_FREQ */
/**
 * @}
 */

/**
 * @defgroup I2S_Clock_Source I2S Clock Source
 * @{
 */
#define I2S_CLK_SRC_PLL                         (I2S_CTRL_I2SPLLSEL)  /*!< Internal PLL Clock */
#define I2S_CLK_SRC_EXT                         (I2S_CTRL_CLKSEL)     /*!< External Clock     */
/**
 * @}
 */

/**
 * @defgroup I2S_Mode I2S Mode
 * @{
 */
#define I2S_MD_MASTER                           (0UL)           /*!< Master mode */
#define I2S_MD_SLAVE                            (I2S_CTRL_WMS)  /*!< Slave mode  */
/**
 * @}
 */

/**
 * @defgroup I2S_Protocol I2S Communication Protocol
 * @{
 */
#define I2S_PROTOCOL_PHILLIPS                   (0UL)                                 /*!< Phillips protocol        */
#define I2S_PROTOCOL_MSB                        (I2S_CFGR_I2SSTD_0)                   /*!< MSB justified protocol   */
#define I2S_PROTOCOL_LSB                        (I2S_CFGR_I2SSTD_1)                   /*!< LSB justified protocol   */
#define I2S_PROTOCOL_PCM_SHORT                  (I2S_CFGR_I2SSTD)                     /*!< PCM short-frame protocol */
#define I2S_PROTOCOL_PCM_LONG                   (I2S_CFGR_I2SSTD | I2S_CFGR_PCMSYNC)  /*!< PCM long-frame protocol  */
/**
 * @}
 */

/**
 * @defgroup I2S_Trans_Mode I2S Transfer Mode
 * @{
 */
#define I2S_TRANS_MD_HALF_DUPLEX_RX             (0UL)                               /*!< Receive only and half duplex mode */
#define I2S_TRANS_MD_HALF_DUPLEX_TX             (I2S_CTRL_SDOE)                     /*!< Send only and half duplex mode    */
#define I2S_TRANS_MD_FULL_DUPLEX                (I2S_CTRL_DUPLEX | I2S_CTRL_SDOE)   /*!< Full duplex mode                  */
/**
 * @}
 */

/**
 * @defgroup I2S_Audio_Frequency I2S Audio Frequency
 * @{
 */
#define I2S_AUDIO_FREQ_192K                     (192000UL)  /*!< FS = 192000Hz */
#define I2S_AUDIO_FREQ_96K                      (96000UL)   /*!< FS = 96000Hz  */
#define I2S_AUDIO_FREQ_48K                      (48000UL)   /*!< FS = 48000Hz  */
#define I2S_AUDIO_FREQ_44K                      (44100UL)   /*!< FS = 44100Hz  */
#define I2S_AUDIO_FREQ_32K                      (32000UL)   /*!< FS = 32000Hz  */
#define I2S_AUDIO_FREQ_22K                      (22050UL)   /*!< FS = 22050Hz  */
#define I2S_AUDIO_FREQ_16K                      (16000UL)   /*!< FS = 16000Hz  */
#define I2S_AUDIO_FREQ_8K                       (8000UL)    /*!< FS = 8000Hz   */
#define I2S_AUDIO_FREQ_DEFAULT                  (2UL)
/**
 * @}
 */

/**
 * @defgroup I2S_Channel_Length I2S Channel Length
 * @{
 */
#define I2S_CH_LEN_16BIT                        (0UL)             /*!< Channel length is 16bits */
#define I2S_CH_LEN_32BIT                        (I2S_CFGR_CHLEN)  /*!< Channel length is 32bits */
/**
 * @}
 */

/**
 * @defgroup I2S_Data_Length I2S Data Length
 * @{
 */
#define I2S_DATA_LEN_16BIT                      (0UL)                 /*!< Transfer data length is 16bits */
#define I2S_DATA_LEN_24BIT                      (I2S_CFGR_DATLEN_0)   /*!< Transfer data length is 24bits */
#define I2S_DATA_LEN_32BIT                      (I2S_CFGR_DATLEN_1)   /*!< Transfer data length is 32bits */
/**
 * @}
 */

/**
 * @defgroup I2S_MCK_Output I2S MCK Output
 * @{
 */
#define I2S_MCK_OUTPUT_DISABLE                  (0UL)             /*!< Disable the drive clock(MCK) output */
#define I2S_MCK_OUTPUT_ENABLE                   (I2S_CTRL_MCKOE)  /*!< Enable the drive clock(MCK) output  */
/**
 * @}
 */

/**
 * @defgroup I2S_Trans_Level I2S Transfer Level
 * @{
 */
#define I2S_TRANS_LVL0                          (0x00UL << I2S_CTRL_TXBIRQWL_POS)   /*!< Transfer FIFO level is 0 */
#define I2S_TRANS_LVL1                          (0x01UL << I2S_CTRL_TXBIRQWL_POS)   /*!< Transfer FIFO level is 1 */
#define I2S_TRANS_LVL2                          (0x02UL << I2S_CTRL_TXBIRQWL_POS)   /*!< Transfer FIFO level is 2 */

/**
 * @}
 */

/**
 * @defgroup I2S_Receive_Level I2S Receive Level
 * @{
 */
#define I2S_RECEIVE_LVL0                        (0x00UL << I2S_CTRL_RXBIRQWL_POS)   /*!< Receive FIFO level is 0 */
#define I2S_RECEIVE_LVL1                        (0x01UL << I2S_CTRL_RXBIRQWL_POS)   /*!< Receive FIFO level is 1 */
#define I2S_RECEIVE_LVL2                        (0x02UL << I2S_CTRL_RXBIRQWL_POS)   /*!< Receive FIFO level is 2 */

/**
 * @}
 */

/**
 * @defgroup I2S_Com_Func I2S Communication Function
 * @{
 */
#define I2S_FUNC_TX                             (I2S_CTRL_TXE)  /*!< Transfer function */
#define I2S_FUNC_RX                             (I2S_CTRL_RXE)  /*!< Receive function  */
#define I2S_FUNC_ALL                            (I2S_FUNC_TX | I2S_FUNC_RX)
/**
 * @}
 */

/**
 * @defgroup I2S_Reset_Type I2S Reset Type
 * @{
 */
#define I2S_RST_TYPE_CODEC                      (I2S_CTRL_CODECRC)  /*!< Reset codec of I2S */
#define I2S_RST_TYPE_FIFO                       (I2S_CTRL_FIFOR)    /*!< Reset FIFO of I2S  */

#define I2S_RST_TYPE_ALL                        (I2S_RST_TYPE_CODEC | I2S_RST_TYPE_FIFO)
/**
 * @}
 */

/**
 * @defgroup I2S_Interrupt I2S Interrupt
 * @{
 */
#define I2S_INT_TX                              (I2S_CTRL_TXIE)   /*!< Transfer interrupt            */
#define I2S_INT_RX                              (I2S_CTRL_RXIE)   /*!< Receive interrupt             */
#define I2S_INT_ERR                             (I2S_CTRL_EIE)    /*!< Communication error interrupt */
#define I2S_INT_ALL                             (I2S_INT_TX | I2S_INT_RX | I2S_INT_ERR)
/**
 * @}
 */

/**
 * @defgroup I2S_Flag I2S Flag
 * @{
 */
#define I2S_FLAG_TX_ALARM                       (I2S_SR_TXBA)           /*!< Transfer buffer alarm flag          */
#define I2S_FLAG_RX_ALARM                       (I2S_SR_RXBA)           /*!< Receive buffer alarm flag           */
#define I2S_FLAG_TX_EMPTY                       (I2S_SR_TXBE)           /*!< Transfer buffer empty flag          */
#define I2S_FLAG_TX_FULL                        (I2S_SR_TXBF)           /*!< Transfer buffer full flag           */
#define I2S_FLAG_RX_EMPTY                       (I2S_SR_RXBE)           /*!< Receive buffer empty flag           */
#define I2S_FLAG_RX_FULL                        (I2S_SR_RXBF)           /*!< Receive buffer full flag            */
#define I2S_FLAG_TX_ERR                         (I2S_ER_TXERR << 16U)   /*!< Transfer overflow or underflow flag */
#define I2S_FLAG_RX_ERR                         (I2S_ER_RXERR << 16U)   /*!< Receive overflow flag               */
#define I2S_FLAG_ALL                            (I2S_FLAG_TX_ALARM | I2S_FLAG_RX_ALARM | I2S_FLAG_TX_EMPTY | \
                                                 I2S_FLAG_TX_FULL  | I2S_FLAG_RX_EMPTY | I2S_FLAG_RX_FULL  | \
                                                 I2S_FLAG_TX_ERR   | I2S_FLAG_RX_ERR)
#define I2S_FLAG_CLR_ALL                        (I2S_FLAG_TX_ERR   | I2S_FLAG_RX_ERR)
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
 * @addtogroup I2S_Global_Functions
 * @{
 */

/* Initialization and configuration functions */
void I2S_DeInit(CM_I2S_TypeDef *I2Sx);
int32_t I2S_Init(CM_I2S_TypeDef *I2Sx, const stc_i2s_init_t *pstcI2sInit);
int32_t I2S_StructInit(stc_i2s_init_t *pstcI2sInit);
void I2S_SWReset(CM_I2S_TypeDef *I2Sx, uint32_t u32Type);
void I2S_SetTransMode(CM_I2S_TypeDef *I2Sx, uint32_t u32Mode);
void I2S_SetTransFIFOLevel(CM_I2S_TypeDef *I2Sx, uint32_t u32Level);
void I2S_SetReceiveFIFOLevel(CM_I2S_TypeDef *I2Sx, uint32_t u32Level);
void I2S_SetProtocol(CM_I2S_TypeDef *I2Sx, uint32_t u32Protocol);
int32_t I2S_SetAudioFreq(CM_I2S_TypeDef *I2Sx, uint32_t u32Freq);
void I2S_MCKOutputCmd(CM_I2S_TypeDef *I2Sx, en_functional_state_t enNewState);
void I2S_FuncCmd(CM_I2S_TypeDef *I2Sx, uint32_t u32Func, en_functional_state_t enNewState);

/* Transfer and receive data functions */
void I2S_WriteData(CM_I2S_TypeDef *I2Sx, uint32_t u32Data);
uint32_t I2S_ReadData(const CM_I2S_TypeDef *I2Sx);
int32_t I2S_Trans(CM_I2S_TypeDef *I2Sx, const void *pvTxBuf, uint32_t u32Len, uint32_t u32Timeout);
int32_t I2S_Receive(const CM_I2S_TypeDef *I2Sx, void *pvRxBuf, uint32_t u32Len, uint32_t u32Timeout);
int32_t I2S_TransReceive(CM_I2S_TypeDef *I2Sx, const void *pvTxBuf,
                         void *pvRxBuf, uint32_t u32Len, uint32_t u32Timeout);

/* Interrupt and flag management functions */
void I2S_IntCmd(CM_I2S_TypeDef *I2Sx, uint32_t u32IntType, en_functional_state_t enNewState);
en_flag_status_t I2S_GetStatus(const CM_I2S_TypeDef *I2Sx, uint32_t u32Flag);
void I2S_ClearStatus(CM_I2S_TypeDef *I2Sx, uint32_t u32Flag);

/**
 * @}
 */

#endif /* LL_I2S_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_I2S_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
