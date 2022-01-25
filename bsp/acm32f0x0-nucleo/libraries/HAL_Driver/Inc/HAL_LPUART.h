/*
  ******************************************************************************
  * @file    HAL_LPUART.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of CAN HAL module.
  ******************************************************************************
*/
#ifndef __HAL_LPUART_H__
#define __HAL_LPUART_H__

#include "ACM32Fxx_HAL.h"


#define IS_LPUART_INSTANCE(INSTANCE)          ((INSTANCE) == LPUART)

#define LPUART_PEN_INDEX  0
#define LPUART_SPS_INDEX  1
#define LPUART_EPS_INDEX  2

#define LPUART_IE_RX_INDEX         0  //has wakeup function
#define LPUART_IE_TX_FINISH_INDEX  1
#define LPUART_IE_TX_EMPTY_INDEX   2

#define LPUART_SR_RX_INDEX         0
#define LPUART_SR_TX_FINISH_INDEX  1
#define LPUART_SR_TX_EMPTY_INDEX   2
#define LPUART_SR_RX_FULL_INDEX    6
#define LPUART_SR_MATCH_INDEX      8  //has wakeup function
#define LPUART_SR_START_INDEX      9  //has wakeup function
#define LPUART_SR_BITS_ALL         0x1FFU

#define LPUART_WAKEUP_RX_BIT       BIT0
#define LPUART_WAKEUP_MATCH_BIT    BIT8
#define LPUART_WAKEUP_START_BIT    BIT9

#define LPUART_CR_RXE_INDEX  0
#define LPUART_CR_TXE_INDEX  1
#define LPUART_CR_DMA_EN_INDEX  2

/** @defgroup  GPIO Private Macros
  * @{
  */
typedef enum
{
    LPUART_RXWKS_START = 0x00,
    LPUART_RXWKS_OneByte = 0x01,
    LPUART_RXWKS_DataCompare = 0x02,
    LPUART_RXWKS_NoWake = 0x03,
} LPUART_RXWKS;

typedef enum
{
    LPUART_WKCK_Check = 0x00,
    LPUART_WKCK_NoCheck = 0x01,
} LPUART_WKCK ;

/**
  * @}
  */



/*
 * @brief  LPUART DATABITS  definition
 */
typedef enum
{
    LPUART_DATABITS_8 = 0x00,
    LPUART_DATABITS_7 = 0x01,
} LPUART_DATABITS;

/*
 * @brief  LPUART STOPBITS  definition
 */
typedef enum
{
    LPUART_STOPBITS_ONE = 0x00U,
    LPUART_STOPBITS_TWO = 0x01U,
}LPUART_STOPBITS;

/*
 * @brief  LPUART CLOCK_SOURCE  definition
 */
typedef enum
{
    LPUART_CLOCK_SOURCE_RC32K = 0x00U,
    LPUART_CLOCK_SOURCE_XTAL = 0x01U,
    LPUART_CLOCK_SOURCE_PLL_DIV = 0x02U,
}LPUART_CLOCK_SOURCE;

/*
 * @brief  LPUART PARITY  definition
 */
typedef enum
{
    LPUART_PARITY_NONE = 0x00U,
    LPUART_PARITY_SELECT_ODD = 0x01U,
    LPUART_PARITY_SELECT_EVEN = 0x02U,
    LPUART_PARITY_SELECT_ONE = 0x03U,
    LPUART_PARITY_SELECT_ZERO = 0x04U,
}LPUART_PARITY_SELECT;

/**
  * @brief  LPUART  Config structure definition
  */
typedef struct
{
    uint8_t  WordLength;  // LPUART_DATABITS
    uint8_t  StopBits;    // LPUART_STOPBITS
    uint8_t  Parity;     // LPUART_PARITY_SELECT
    uint8_t  ClockSrc;   // LPUART_CLOCK_SOURCE
    uint32_t BaudRate;
}LPUART_ConfigParam;

/**
  * @brief  LPUART  Config structure definition
  */
typedef struct
{
    uint8_t  Wakeup_Source;  // Wakeup_Source
    uint8_t  Wakeup_Check;  // Wakeup_Check
    uint8_t  Wakeup_Addr;  // Wakeup_Addr

}LPUART_StopWakeupDef;



/**
  * @brief  LPUART  init structure definition
  */
typedef struct
{
    LPUART_TypeDef *Instance;
    LPUART_ConfigParam ConfigParam;
    LPUART_StopWakeupDef StopWakeup;
    volatile uint8_t *rx_buffer;
    volatile uint16_t rx_buffer_size;
    volatile uint16_t rx_write_index;
    volatile uint16_t rx_read_index;
    volatile uint16_t tx_busy;
    DMA_HandleTypeDef *dma_rx_handler;
    DMA_HandleTypeDef *dma_tx_handler;
}LPUART_HandleTypeDef;

/* HAL_LPUART_Init */
HAL_StatusTypeDef HAL_LPUART_Init(LPUART_HandleTypeDef *hlpuart);

HAL_StatusTypeDef HAL_LPUART_DeInit(LPUART_HandleTypeDef *hlpuart);

void HAL_LPUART_MSPInit(LPUART_HandleTypeDef *hlpuart);

void HAL_LPUART_MspDeInit(LPUART_HandleTypeDef *hlpuart);

/* HAL_LPUART_Send_Bytes */
void HAL_LPUART_Send_Bytes(LPUART_HandleTypeDef *hlpuart, uint8_t *buff, uint32_t length);

/* HAL_LPUART_IRQHander */
void HAL_LPUART_IRQHander(LPUART_HandleTypeDef *hlpuart);

/* HAL_LPUART_Receive_Bytes_Timeout */
uint32_t HAL_LPUART_Receive_Bytes_Timeout(LPUART_HandleTypeDef *hlpuart, uint8_t * rxbuff, uint32_t length, uint32_t ms);

/* HAL_LPUART_Receive_Bytes */
uint32_t HAL_LPUART_Receive_Bytes(LPUART_HandleTypeDef *hlpuart, uint8_t * rxbuff, uint32_t length);

/* HAL_LPUART_DMA_Send_Bytes */
void HAL_LPUART_DMA_Send_Bytes(LPUART_HandleTypeDef *hlpuart, uint8_t *buff, uint32_t length);

/* HAL_LPUART_Clear_Wakeup_Flags */
void HAL_LPUART_Clear_Wakeup_Flags(LPUART_HandleTypeDef *hlpuart, uint32_t Wakeup_Bits);

#endif
