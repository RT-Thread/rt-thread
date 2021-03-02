/**
    *****************************************************************************
    * @file     cmem7_spi.h
    *
    * @brief    CMEM7 SPI header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_SPI_H
#define __CMEM7_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cmem7.h"
#include "cmem7_conf.h"


#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI0) || \
                                   ((PERIPH) == SPI1))


/** @defgroup SPI_MODE
  * @{
  */
#define SPI_MODE_CPOL_0_CPHA_0         0    /*!< CPOL : Idle clock level is low level.
                                                                                                 CPHA : Capture data at the first edge */
#define SPI_MODE_CPOL_0_CPHA_1         1        /*!< CPOL : Idle clock level is low level.
                                                                                                 CPHA : Capture data at the second edge */
#define SPI_MODE_CPOL_1_CPHA_0         2        /*!< CPOL : Idle clock level is high level.
                                                                                                 CPHA : Capture data at the first edge */
#define SPI_MODE_CPOL_1_CPHA_1         3        /*!< CPOL : Idle clock level is high level.
                                                                                                 CPHA : Capture data at the first edge */
#define IS_SPI_MODE(MODE)              (((MODE) == SPI_MODE_CPOL_0_CPHA_0) || \
                                        ((MODE) == SPI_MODE_CPOL_0_CPHA_1) || \
                                        ((MODE) == SPI_MODE_CPOL_1_CPHA_0) || \
                                                                                ((MODE) == SPI_MODE_CPOL_1_CPHA_1))
/**
  * @}
  */

/** @defgroup SPI_INT
  * @{
  */
#define SPI_INT_RX_FIFO_UNDERFLOW      0x00000001
#define SPI_INT_RX_FIFO_OVERFLOW       0x00000002
#define SPI_INT_RX_FIFO_ALMOST_FULL    0x00000004
#define SPI_INT_TX_FIFO_UNDERFLOW      0x00000008
#define SPI_INT_TX_FIFO_OVERFLOW       0x00000010
#define SPI_INT_TX_FIFO_ALMOST_FULL    0x00000020
#define SPI_INT_DONE                   0x00000040
#define SPI_INT_ALL                    0x0000007F

#define IS_SPI_INT(INT)                (((INT) != 0) && (((INT) & ~SPI_INT_ALL) == 0))
/**
  * @}
  */

/**
  * @brief  SPI initialization structure
    */
typedef struct
{
  uint8_t SPI_Mode;                 /*!< indicates SPI's CPOL and CPHA, ref as @ref SPI_MODE */
  BOOL SPI_RxEn;                    /*!< indicates if SPI receiver is enabled or not */
  uint8_t SPI_BitLength;            /*!< bit length while transmitting and receiving */
  uint8_t SPI_Gap;                  /*!< cycle number between continuous data frame */
    uint8_t SPI_ClockDividor;         /*!< SPI clock dividor, 1 / ((1 + DIV) * 2) */
} SPI_InitTypeDef;
/**
  * @}
  */

/**
  * @brief  SPI initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
    * @param[in] init A pointer to structure SPI_InitTypeDef
  * @retval None
    */
void SPI_Init(SPI0_Type* SPIx, SPI_InitTypeDef *init);

/**
  * @brief  Enable or disable SPI.
    * @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
    * @param[in] Enable The bit indicates if the specific SPI is enable or not
  * @retval None
    */
void SPI_Enable(SPI0_Type* SPIx, BOOL enable);

/**
  * @brief  Enable or disable SPI interrupt.
    * @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
    * @param[in] Int interrupt mask bits, which can be the combination of @ref SPI_Int
    * @param[in] Enable The bit indicates if specific interrupts are enable or not
  * @retval None
    */
void SPI_EnableInt(SPI0_Type* SPIx, uint32_t Int, BOOL enable);

/**
  * @brief  Check specific interrupts are set or not
    * @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
    * @param[in] Int interrupt mask bits, which can be the combination of @ref SPI_Int
  * @retval BOOL The bit indicates if specific interrupts are set or not
    */
BOOL SPI_GetIntStatus(SPI0_Type* SPIx, uint32_t Int);

/**
  * @brief  Clear specific interrupts
    * @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
    * @param[in] Int interrupt mask bits, which can be the combination of @ref SPI_Int
  * @retval None
    */
void SPI_ClearInt(SPI0_Type* SPIx, uint32_t Int);

/**
  * @brief  Read data from SPI FIFO
    * @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
    * @param[in] size Expected data size to be read
    * @param[out] data A user-allocated buffer to fetch data to be read
  * @retval uint8_t Actual read data size
    */
uint8_t SPI_ReadFifo(SPI0_Type* SPIx, uint8_t size, uint32_t* data);

/**
  * @brief  Write data to SPI FIFO
    * @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
    * @param[in] size Expected data size to be written
    * @param[in] data A pointer to the data to be written
  * @retval uint8_t Actual written data size
    */
uint8_t SPI_WriteFifo(SPI0_Type* SPIx, uint8_t Size, uint32_t* data);

/**
  * @brief  send a SPI transcation request
    * @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
    * @param[in] size Expected data size to be written and read
    * @retval BOOL The bit indicates if the request is sent
    */
BOOL SPI_Transcation(SPI0_Type* SPIx, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif /*__CMEM7_SPI_H */

