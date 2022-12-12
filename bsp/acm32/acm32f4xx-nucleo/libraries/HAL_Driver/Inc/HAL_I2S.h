/*
  ******************************************************************************
  * @file    HAL_I2S.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of I2S HAL module.
  ******************************************************************************
*/

#ifndef __HAL_I2S_H__
#define __HAL_I2S_H__

#include "ACM32Fxx_HAL.h"

/************************************************************************************/
/*                             Registers Bits Definition                            */
/************************************************************************************/

/****************  Bit definition for I2S CTL Register  ***********************/
#define I2S_CTL_I2SEN               (BIT10)
#define I2S_CTL_I2SOPMOD            (BIT9|BIT8)
#define I2S_CTL_PCMSMOD             (BIT7)
#define I2S_CTL_I2SSTD              (BIT5|BIT4)
#define I2S_CTL_CKPL                (BIT3)
#define I2S_CTL_DTLEN               (BIT2|BIT1)
#define I2S_CTL_CHLEN               (BIT0)

/****************  Bit definition for I2S PSC Register  ***********************/
#define I2S_PSC_MCKOEN              (BIT10)
#define I2S_PSC_OF                  (BIT9)
#define I2S_PSC_DIV                 (0x1FF)

/****************  Bit definition for I2S DIE Register  ***********************/
#define I2S_DIE_TBEIE               (BIT7)
#define I2S_DIE_RBNEIE              (BIT6)
#define I2S_DIE_ERRIE               (BIT5)
#define I2S_DIE_DMATEN              (BIT1)
#define I2S_DIE_DMAREN              (BIT0)

/****************  Bit definition for I2S STATUS Register  ***********************/
#define I2S_STATUS_FERR             (BIT8)
#define I2S_STATUS_TRANS            (BIT7)
#define I2S_STATUS_RXORERR          (BIT6)
#define I2S_STATUS_TXURERR          (BIT3)
#define I2S_STATUS_I2SCH            (BIT2)
#define I2S_STATUS_TXBE             (BIT1)
#define I2S_STATUS_RXBNE            (BIT0)



/** @defgroup I2S_Mode I2S Mode
  * @{
  */
#define I2S_MODE_SLAVE_TX                (0x00000000)
#define I2S_MODE_SLAVE_RX                (0x00000100)
#define I2S_MODE_MASTER_TX               (0x00000200)
#define I2S_MODE_MASTER_RX               (I2S_CTL_I2SOPMOD)
/**
  * @}
  */


/** @defgroup I2S_Standard I2S Standard
  * @{
  */
#define I2S_STANDARD_PHILIPS             (0x00000000U)
#define I2S_STANDARD_MSB                 (0x00000010U)
#define I2S_STANDARD_LSB                 (0x00000020U)
#define I2S_STANDARD_PCM_SHORT           (I2S_CTL_I2SSTD)
#define I2S_STANDARD_PCM_LONG            (I2S_CTL_I2SSTD | I2S_CTL_PCMSMOD)
/**
  * @}
  */


/** @defgroup I2S_Data_Format I2S Data Format
  * @{
  */
#define I2S_DATAFORMAT_16B               (0x00000000U)
#define I2S_DATAFORMAT_16B_EXTENDED      (I2S_CTL_CHLEN)
#define I2S_DATAFORMAT_24B               (I2S_CTL_CHLEN | 0x02)
#define I2S_DATAFORMAT_32B               (I2S_CTL_CHLEN | 0x04)
/**
  * @}
  */


/** @defgroup I2S_MCLK_Output I2S MCLK Output
  * @{
  */
#define I2S_MCLKOUTPUT_ENABLE            (I2S_PSC_MCKOEN)
#define I2S_MCLKOUTPUT_DISABLE           (0x00000000U)
/**
  * @}
  */


/** @defgroup I2S_Clock_Polarity I2S Clock Polarity
  * @{
  */
#define I2S_CPOL_LOW                     (0x00000000U)
#define I2S_CPOL_HIGH                    (I2S_CTL_CKPL)
/**
  * @}
  */


/** @defgroup I2S_Audio_FrequencyOF I2S Clock Frequency OF
  * @{
  */
#define I2S_FREQ_OF_DISABLE              (0x00000000U)
#define I2S_FREQ_OF_ENABLE               (I2S_PSC_OF)
/**
  * @}
  */

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
    HAL_I2S_STATE_RESET      = 0x00U,    /*!< I2S not yet initialized or disabled                */
    HAL_I2S_STATE_READY      = 0x01U,    /*!< I2S initialized and ready for use                  */
    HAL_I2S_STATE_BUSY       = 0x02U,    /*!< I2S internal process is ongoing                    */
    HAL_I2S_STATE_BUSY_TX    = 0x03U,    /*!< Data Transmission process is ongoing               */
    HAL_I2S_STATE_BUSY_RX    = 0x04U,    /*!< Data Reception process is ongoing                  */
    HAL_I2S_STATE_TIMEOUT    = 0x06U,    /*!< I2S timeout state                                  */
    HAL_I2S_STATE_ERROR      = 0x07U     /*!< I2S error state                                    */
}enum_I2S_State;


/**
  * @brief I2S Init structure definition
  */
typedef struct
{
    uint32_t u32_Mode;            /*!< Specifies the I2S operating mode.
                                       This parameter can be a value of @ref I2S_Mode */
    
    uint32_t u32_Standard;        /*!< Specifies the standard used for the I2S communication.
                                       This parameter can be a value of @ref I2S_Standard */
    
    uint32_t u32_DataFormat;      /*!< Specifies the data format for the I2S communication.
                                       This parameter can be a value of @ref I2S_Data_Format */
    
    uint32_t u32_MCLKOutput;      /*!< Specifies whether the I2S MCLK output is enabled or not.
                                       This parameter can be a value of @ref I2S_MCLK_Output */

    uint32_t u32_CPOL;            /*!< Specifies the idle state of the I2S clock.
                                       This parameter can be a value of @ref I2S_Clock_Polarity */

    uint32_t u32_FreqOF;          /*!< Specifies the frequency selected for the I2S communication.
                                       This parameter can be a value of @ref I2S_Audio_FrequencyFO */

    uint32_t u32_FreqDIV;         /*!< Specifies the frequency selected for the I2S communication.
                                       This parameter must be a number between Min_Data = 0x001 and Max_Data = 0x1FF */
}I2S_InitTypeDef;



/**
  * @brief I2S handle Structure definition
  */
typedef struct
{
    I2S_TypeDef           *Instance;     /*!< I2S registers base address */

    I2S_InitTypeDef        Init;         /*!< I2S communication parameters */

    enum_I2S_State         I2S_Status;

    uint32_t              *u32_Rx_Buffer;        /* I2S Rx Buffer */
    uint32_t              *u32_Tx_Buffer;        /* I2S Tx Buffer */
    
    uint32_t               u32_Rx_Size;          /* I2S Rx Size */
    uint32_t               u32_Tx_Size;          /* I2S Tx Size */
    
    uint32_t               u32_Rx_Count;         /* I2S RX Count */
    uint32_t               u32_Tx_Count;         /* I2S TX Count */

    DMA_HandleTypeDef   *HDMA_Rx;          /* SPI Rx DMA handle parameters */
    DMA_HandleTypeDef   *HDMA_Tx;          /* SPI Tx DMA handle parameters */

}I2S_HandleTypeDef;


/** @defgroup  RTC Private Macros
  * @{
  */
#define IS_I2S_MODE(__MODE__)             (((__MODE__) == I2S_MODE_SLAVE_TX)  || \
                                           ((__MODE__) == I2S_MODE_SLAVE_RX)  || \
                                           ((__MODE__) == I2S_MODE_MASTER_TX) || \
                                           ((__MODE__) == I2S_MODE_MASTER_RX))

#define IS_I2S_STANDARD(__STANDARD__)     (((__STANDARD__) == I2S_STANDARD_PHILIPS)   || \
                                           ((__STANDARD__) == I2S_STANDARD_MSB)       || \
                                           ((__STANDARD__) == I2S_STANDARD_LSB)       || \
                                           ((__STANDARD__) == I2S_STANDARD_PCM_SHORT) || \
                                           ((__STANDARD__) == I2S_STANDARD_PCM_LONG))
                                           
#define IS_I2S_DATAFORMAT(__DATAFORMAT__)       (((__DATAFORMAT__) == I2S_DATAFORMAT_16B)           || \
                                                 ((__DATAFORMAT__) == I2S_DATAFORMAT_16B_EXTENDED)  || \
                                                 ((__DATAFORMAT__) == I2S_DATAFORMAT_24B)           || \
                                                 ((__DATAFORMAT__) == I2S_DATAFORMAT_32B))

#define IS_I2S_MCLK_OUTPUT(__MCLK_OUTPUT__)     (((__MCLK_OUTPUT__) == I2S_MCLKOUTPUT_ENABLE)  || \
                                                 ((__MCLK_OUTPUT__) == I2S_MCLKOUTPUT_DISABLE))

#define IS_I2S_MCLK_CPOL(__CPOL__)              (((__CPOL__) == I2S_CPOL_LOW)  || \
                                                 ((__CPOL__) == I2S_CPOL_HIGH))

#define IS_I2S_OF(__OF__)                       (((__OF__) == I2S_FREQ_OF_DISABLE)  || \
                                                 ((__OF__) == I2S_FREQ_OF_ENABLE))

#define IS_I2S_DIV(__DIV__)                      ((__DIV__) >= 0x001 && (__DIV__) <= 0x1FF)
/**
  * @}
  */

/* HAL_I2S_IRQHandler */
void HAL_I2S_IRQHandler(I2S_HandleTypeDef *hi2s);

/* HAL_I2S_MspInit */
void HAL_I2S_MspInit(I2S_HandleTypeDef *hspi);

/* HAL_I2S_Init */
HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s);

/* HAL_I2S_Transmit */
HAL_StatusTypeDef HAL_I2S_Transmit(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size, uint32_t fu32_Timeout);

/* HAL_I2S_Receive */
HAL_StatusTypeDef HAL_I2S_Receive(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size, uint32_t fu32_Timeout);

/* HAL_I2S_Transmit_IT */
HAL_StatusTypeDef HAL_I2S_Transmit_IT(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size);

/* HAL_I2S_Receive_IT */
HAL_StatusTypeDef HAL_I2S_Receive_IT(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size);

/* HAL_I2S_Transmit_DMA */
HAL_StatusTypeDef HAL_I2S_Transmit_DMA(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size);

/* HAL_I2S_Receive_DMA */
HAL_StatusTypeDef HAL_I2S_Receive_DMA(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size);

#endif

