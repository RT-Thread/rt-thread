/*
  ******************************************************************************
  * @file    HAL_SPI.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of SPI HAL module.
  ******************************************************************************
*/
#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__

#include  "ACM32Fxx_HAL.h"

/****************  Bit definition for SPI_CTL register  **************************/
#define SPI_CTL_CS_TIME                       (BIT11|BIT12|BIT13|BIT14|BIT15|BIT16|BIT17|BIT18)
#define SPI_CTL_CS_FILTER                      BIT10
#define SPI_CTL_CS_RST                         BIT9
#define SPI_CTL_SLAVE_EN                       BIT8
#define SPI_CTL_IO_MODE                        BIT7
#define SPI_CTL_X_MODE                        (BIT6|BIT5)
#define SPI_CTL_LSB_FIRST                      BIT4
#define SPI_CTL_CPOL                           BIT3
#define SPI_CTL_CPHA                           BIT2
#define SPI_CTL_SFILTER                        BIT1
#define SPI_CTL_MST_MODE                       BIT0

/****************  Bit definition for SPI_TX_CTL register  ***********************/
#define SPI_TX_CTL_DMA_LEVEL                  (BIT4|BIT5|BIT6|BIT7)
#define SPI_TX_CTL_DMA_LEVEL_3                 BIT7
#define SPI_TX_CTL_DMA_LEVEL_2                 BIT6
#define SPI_TX_CTL_DMA_LEVEL_1                 BIT5
#define SPI_TX_CTL_DMA_LEVEL_0                 BIT4
#define SPI_TX_CTL_DMA_REQ_EN                  BIT3
#define SPI_TX_CTL_MODE                        BIT2
#define SPI_TX_CTL_FIFO_RESET                  BIT1
#define SPI_TX_CTL_EN                          BIT0

/****************  Bit definition for SPI_RX_CTL register  ***********************/
#define SPI_RX_CTL_DMA_LEVEL                  (BIT4|BIT5|BIT6|BIT7)
#define SPI_RX_CTL_DMA_LEVEL_3                 BIT7
#define SPI_RX_CTL_DMA_LEVEL_2                 BIT6
#define SPI_RX_CTL_DMA_LEVEL_1                 BIT5
#define SPI_RX_CTL_DMA_LEVEL_0                 BIT4
#define SPI_RX_CTL_DMA_REQ_EN                  BIT3
#define SPI_RX_CTL_FIFO_RESET                  BIT1
#define SPI_RX_CTL_EN                          BIT0

/****************  Bit definition for SPI_IE register  ***************************/
#define SPI_IE_RX_BATCH_DONE_EN                BIT15
#define SPI_IE_TX_BATCH_DONE_EN                BIT14
#define SPI_IE_RX_FIFO_FULL_OV_EN              BIT13
#define SPI_IE_RX_FIFO_EMPTY_OV_EN             BIT12
#define SPI_IE_RX_NOT_EMPTY_EN                 BIT11
#define SPI_IE_CS_POS_EN                       BIT10
#define SPI_IE_RX_FIFO_HALF_FULL_EN            BIT9
#define SPI_IE_RX_FIFO_HALF_EMPTY_EN           BIT8
#define SPI_IE_TX_FIFO_HALF_FULL_EN            BIT7
#define SPI_IE_TX_FIFO_HALF_EMPTY_EN           BIT6
#define SPI_IE_RX_FIFO_FULL_EN                 BIT5
#define SPI_IE_RX_FIFO_EMPTY_EN                BIT4
#define SPI_IE_TX_FIFO_FULL_EN                 BIT3
#define SPI_IE_TX_FIFO_EMPTY_EN                BIT2
#define SPI_IE_BATCH_DONE_EN                   BIT1

/****************  Bit definition for SPI_STATUS register  ***********************/
#define SPI_STATUS_RX_BATCH_DONE               BIT15
#define SPI_STATUS_TX_BATCH_DONE               BIT14
#define SPI_STATUS_RX_FIFO_FULL_OV             BIT13
#define SPI_STATUS_RX_FIFO_EMPTY_OV            BIT12
#define SPI_STATUS_RX_NOT_EMPTY                BIT11
#define SPI_STATUS_CS_POS                      BIT10
#define SPI_STATUS_RX_FIFO_HALF_FULL           BIT9
#define SPI_STATUS_RX_FIFO_HALF_EMPTY          BIT8
#define SPI_STATUS_TX_FIFO_HALF_FULL           BIT7
#define SPI_STATUS_TX_FIFO_HALF_EMPTY          BIT6
#define SPI_STATUS_RX_FIFO_FULL                BIT5
#define SPI_STATUS_RX_FIFO_EMPTY               BIT4
#define SPI_STATUS_TX_FIFO_FULL                BIT3
#define SPI_STATUS_TX_FIFO_EMPTY               BIT2
#define SPI_STATUS_BATCH_DONE                  BIT1
#define SPI_STATUS_TX_BUSY                     BIT0

/****************  Bit definition for SPI_CS register  ***************************/
#define SPI_CS_CSX                             BIT1
#define SPI_CS_CS0                             BIT0

/****************  Bit definition for SPI_OUT_EN register  ***********************/
#define SPI_HOLD_EN                            BIT3
#define SPI_HOLD_WP_EN                         BIT2
#define SPI_HOLD_MISO_EN                       BIT1
#define SPI_HOLD_MOSI_EN                       BIT0

/****************  Bit definition for SPI_MEMO_ACC register  ***********************/
#define SPI_ADDR_WIDTH                        (BIT14|BIT15|BIT16|BIT17|BIT18)
#define SPI_PARA_NO2                          (BIT9|BIT10|BIT11|BIT12|BIT13)
#define SPI_PARA_NO1                          (BIT5|BIT6|BIT7|BIT8)
#define SPI_CON_RD_EN                          BIT3
#define SPI_PARA_ORD2                          BIT2
#define SPI_PARA_ORD1                          BIT1
#define SPI_ACC_EN                             BIT0

/** @defgroup SLAVE State machine
 *  @{
 */
#define    SPI_RX_STATE_IDLE         (0U)
#define    SPI_RX_STATE_RECEIVING    (1U)
#define    SPI_TX_STATE_IDLE         (0U)
#define    SPI_TX_STATE_SENDING      (1U)
/**
  * @}
  */


/** @defgroup SPI_MODE
 *  @{
 */
#define    SPI_MODE_SLAVE     (0U)
#define    SPI_MODE_MASTER    (1U)
/**
  * @}
  */


/** @defgroup SPI_WORK_MODE
  * @{
  */
#define SPI_WORK_MODE_0    (0x00000000)
#define SPI_WORK_MODE_1    (0x00000004)
#define SPI_WORK_MODE_2    (0x00000008)
#define SPI_WORK_MODE_3    (0x0000000C)
/**
  * @}
  */


/** @defgroup SPI_CLOCK_PHASE SPI Clock Phase
  * @{
  */
#define SPI_PHASE_1EDGE    (0U)
#define SPI_PHASE_2EDGE    (1U)
/**
  * @}
  */


/** @defgroup X_MODE SPI Clock Phase
  * @{
  */
#define SPI_1X_MODE    (0x00000000)
#define SPI_2X_MODE    (0x00000020)
#define SPI_4X_MODE    (0x00000040)
/**
  * @}
  */


/** @defgroup SPI_MSB_LSB_FIRST
  * @{
  */
#define SPI_FIRSTBIT_MSB    (0U)
#define SPI_FIRSTBIT_LSB    (1U)
/**
  * @}
  */


/** @defgroup BAUDRATE_PRESCALER
  * @{
  */
#define SPI_BAUDRATE_PRESCALER_4      (4U)
#define SPI_BAUDRATE_PRESCALER_8      (8U)
#define SPI_BAUDRATE_PRESCALER_16     (16U)
#define SPI_BAUDRATE_PRESCALER_32     (32U)
#define SPI_BAUDRATE_PRESCALER_64     (64U)
#define SPI_BAUDRATE_PRESCALER_128    (128U)
#define SPI_BAUDRATE_PRESCALER_254    (254U)
/**
  * @}
  */


/**
  * @brief  SPI Configuration Structure definition
  */
typedef struct
{
    uint32_t  SPI_Mode;              /* This parameter can be a value of @ref SPI_MODE */

    uint32_t  SPI_Work_Mode;         /* This parameter can be a value of @ref SPI_WORK_MODE */

    uint32_t  X_Mode;                /* This parameter can be a value of @ref X_MODE */

    uint32_t  First_Bit;             /* This parameter can be a value of @ref SPI_MSB_LSB_FIRST */

    uint32_t  BaudRate_Prescaler;    /* This parameter can be a value of @ref BAUDRATE_PRESCALER */
}SPI_InitTypeDef;

/******************************** Check SPI Parameter *******************************/
#define IS_SPI_ALL_MODE(SPI_Mode)          (((SPI_Mode) == SPI_MODE_SLAVE) || \
                                            ((SPI_Mode) == SPI_MODE_MASTER))

#define IS_SPI_WORK_MODE(WORK_MODE)        (((WORK_MODE) == SPI_WORK_MODE_0) || \
                                            ((WORK_MODE) == SPI_WORK_MODE_1) || \
                                            ((WORK_MODE) == SPI_WORK_MODE_2) || \
                                            ((WORK_MODE) == SPI_WORK_MODE_3))

#define IS_SPI_X_MODE(X_MODE)              (((X_MODE) == SPI_1X_MODE) || \
                                            ((X_MODE) == SPI_2X_MODE) || \
                                            ((X_MODE) == SPI_4X_MODE))

#define IS_SPI_FIRST_BIT(FIRST_BIT)        (((FIRST_BIT) == SPI_FIRSTBIT_MSB) || \
                                            ((FIRST_BIT) == SPI_FIRSTBIT_LSB))

#define IS_SPI_BAUDRATE_PRESCALER(BAUDRATE)    (((BAUDRATE) == SPI_BAUDRATE_PRESCALER_4)   || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_8)   || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_16)  || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_32)  || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_64)  || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_128) || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_254))

/**
  * @brief  SPI handle Structure definition
  */
typedef struct
{
    SPI_TypeDef         *Instance;         /* SPI registers base address */

    SPI_InitTypeDef      Init;             /* SPI communication parameters */

    uint32_t               RxState;          /* SPI state machine */
    uint32_t               TxState;          /* SPI state machine */

    uint8_t               *Rx_Buffer;        /* SPI Rx Buffer */
    uint8_t               *Tx_Buffer;        /* SPI Tx Buffer */

    uint32_t               Rx_Size;          /* SPI Rx Size */
    uint32_t               Tx_Size;          /* SPI Tx Size */

    uint32_t               Rx_Count;         /* SPI RX Count */
    uint32_t               Tx_Count;         /* SPI TX Count */

    DMA_HandleTypeDef   *HDMA_Rx;          /* SPI Rx DMA handle parameters */
    DMA_HandleTypeDef   *HDMA_Tx;          /* SPI Tx DMA handle parameters */

}SPI_HandleTypeDef;

/******************************** SPI Instances *******************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE)    (((INSTANCE) == SPI1) || ((INSTANCE) == SPI2))

/* Function : HAL_SPI_IRQHandler */
void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi);

/* Function : HAL_SPI_MspInit */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);

/* Function : HAL_SPI_MspDeInit */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);

/* Function : HAL_SPI_Init */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);

/* Function : HAL_SPI_DeInit */
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi);

/* Function : HAL_SPI_Transmit */
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);

/* Function : HAL_SPI_Transmit_DMA */
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);

/* Function : HAL_SPI_Receive */
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);

/* Function : HAL_SPI_Receive_DMA */
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);

/* Function : HAL_SPI_Wire_Config */
HAL_StatusTypeDef HAL_SPI_Wire_Config(SPI_HandleTypeDef *hspi, uint32_t X_Mode);

/* Function : HAL_SPI_Transmit_IT */
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);

/* Function : HAL_SPI_Receive_IT */
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);

/* Function : HAL_SPI_TransmitReceive */
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout);

/* Function : HAL_SPI_GetTxState */
uint8_t HAL_SPI_GetTxState(SPI_HandleTypeDef *hspi);

/* Function : HAL_SPI_GetRxState */
uint8_t HAL_SPI_GetRxState(SPI_HandleTypeDef *hspi);

#endif





