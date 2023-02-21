/**
  ******************************************************************************
  * @file    bl808_spi.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL808_SPI_H__
#define __BL808_SPI_H__

#include "spi_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SPI
 *  @{
 */

/** @defgroup  SPI_Public_Types
 *  @{
 */

/**
 *  @brief SPI No. type definition
 */
typedef enum {
    SPI0_ID,    /*!< SPI0 port define */
    SPI0_MM_ID, /*!< MM system SPI0 port define */
    SPI_ID_MAX, /*!< SPI MAX ID define */
} SPI_ID_Type;

/**
 *  @brief SPI slave pin mode type definition
 */
typedef enum {
    SPI_SLAVE_PIN_4, /*!< SPI 4-pin mode(CS is enabled) */
    SPI_SLAVE_PIN_3, /*!< SPI 3-pin mode(CS don't case) */
} SPI_Slave_Pin_Type;

/**
 *  @brief SPI byte inverse type definition
 */
typedef enum {
    SPI_BYTE_INVERSE_BYTE0_FIRST, /*!< SPI byte 0 is sent out first */
    SPI_BYTE_INVERSE_BYTE3_FIRST, /*!< SPI byte 3 is sent out first */
} SPI_BYTE_INVERSE_Type;

/**
 *  @brief SPI bit inverse type definition
 */
typedef enum {
    SPI_BIT_INVERSE_MSB_FIRST, /*!< SPI each byte is sent out MSB first */
    SPI_BIT_INVERSE_LSB_FIRST, /*!< SPI each byte is sent out LSB first */
} SPI_BIT_INVERSE_Type;

/**
 *  @brief SPI clock phase inverse type definition
 */
typedef enum {
    SPI_CLK_PHASE_INVERSE_0, /*!< SPI clock phase inverse 0 */
    SPI_CLK_PHASE_INVERSE_1, /*!< SPI clock phase inverse 1 */
} SPI_CLK_PHASE_INVERSE_Type;

/**
 *  @brief SPI clock polarity type definition
 */
typedef enum {
    SPI_CLK_POLARITY_LOW,  /*!< SPI clock output low at IDLE state */
    SPI_CLK_POLARITY_HIGH, /*!< SPI clock output high at IDLE state */
} SPI_CLK_POLARITY_Type;

/**
 *  @brief SPI frame size(also the valid width for each fifo entry) type definition
 */
typedef enum {
    SPI_FRAME_SIZE_8,  /*!< SPI frame size 8 bit */
    SPI_FRAME_SIZE_16, /*!< SPI frame size 16 bit */
    SPI_FRAME_SIZE_24, /*!< SPI frame size 24 bit */
    SPI_FRAME_SIZE_32, /*!< SPI frame size 32 bit */
} SPI_FrameSize_Type;

/**
 *  @brief SPI work mode select type definition
 */
typedef enum {
    SPI_WORK_MODE_SLAVE,  /*!< SPI work at slave mode */
    SPI_WORK_MODE_MASTER, /*!< SPI work at master mode */
} SPI_WORK_MODE_Type;

/**
 *  @brief SPI enable or disable timeout judgment definition
 */
typedef enum {
    SPI_TIMEOUT_DISABLE, /*!< SPI disable timeout judgment */
    SPI_TIMEOUT_ENABLE,  /*!< SPI enable timeout judgment */
} SPI_Timeout_Type;

/**
 *  @brief SPI fifo overflow/underflow flag type definition
 */
typedef enum {
    SPI_FIFO_TX_OVERFLOW,  /*!< SPI tx fifo overflow flag */
    SPI_FIFO_TX_UNDERFLOW, /*!< SPI tx fifo underflow flag */
    SPI_FIFO_RX_OVERFLOW,  /*!< SPI rx fifo overflow flag */
    SPI_FIFO_RX_UNDERFLOW, /*!< SPI rx fifo underflow flag */
} SPI_FifoStatus_Type;

/**
 *  @brief SPI interrupt type definition
 */
typedef enum {
    SPI_INT_END,            /*!< SPI transfer end interrupt,shared by both master and slave mode */
    SPI_INT_TX_FIFO_REQ,    /*!< SPI tx fifo ready interrupt(tx fifo count > tx fifo threshold) */
    SPI_INT_RX_FIFO_REQ,    /*!< SPI rx fifo ready interrupt(rx fifo count > rx fifo threshold) */
    SPI_INT_SLAVE_TIMEOUT,  /*!< SPI slave mode transfer time-out interrupt,triggered when spi bus is idle for the given value */
    SPI_INT_SLAVE_UNDERRUN, /*!< SPI slave mode tx underrun error interrupt,triggered when tx is not ready during transfer */
    SPI_INT_FIFO_ERROR,     /*!< SPI tx/rx fifo error interrupt(overflow/underflow) */
    SPI_INT_ALL,            /*!< All the interrupt */
} SPI_INT_Type;

/**
 *  @brief SPI configuration type definition
 */
typedef struct
{
    BL_Fun_Type deglitchEnable;             /*!< Enable or disable de-glitch function */
    SPI_Slave_Pin_Type slavePin;            /*!< Slave 4/3 pin mode */
    BL_Fun_Type continuousEnable;           /*!< Enable or disable master continuous transfer mode,enable:SS will stay asserted if next data is valid */
    SPI_BYTE_INVERSE_Type byteSequence;     /*!< The byte is sent first in SPI transfer */
    SPI_BIT_INVERSE_Type bitSequence;       /*!< The bit is sent first in SPI transfer */
    SPI_CLK_PHASE_INVERSE_Type clkPhaseInv; /*!< Inverse SPI clock phase */
    SPI_CLK_POLARITY_Type clkPolarity;      /*!< SPI clock plarity */
    SPI_FrameSize_Type frameSize;           /*!< SPI frame size(also the valid width for each fifo entry) */
} SPI_CFG_Type;

/**
 *  @brief SPI configuration type definition
 */
typedef struct
{
    uint8_t startLen;      /*!< Length of start condition */
    uint8_t stopLen;       /*!< Length of stop condition */
    uint8_t dataPhase0Len; /*!< Length of data phase 0,affecting clock */
    uint8_t dataPhase1Len; /*!< Length of data phase 1,affecting clock */
    uint8_t intervalLen;   /*!< Length of interval between frame */
} SPI_ClockCfg_Type;

/**
 *  @brief SPI DMA configuration type definition
 */
typedef struct
{
    uint8_t txFifoThreshold;     /*!< SPI tx FIFO threshold */
    uint8_t rxFifoThreshold;     /*!< SPI rx FIFO threshold */
    BL_Fun_Type txFifoDmaEnable; /*!< Enable or disable tx dma req/ack interface */
    BL_Fun_Type rxFifoDmaEnable; /*!< Enable or disable rx dma req/ack interface */
} SPI_FifoCfg_Type;

/*@} end of group SPI_Public_Types */

/** @defgroup  SPI_Public_Constants
 *  @{
 */

/** @defgroup  SPI_ID_TYPE
 *  @{
 */
#define IS_SPI_ID_TYPE(type) (((type) == SPI0_ID) ||    \
                              ((type) == SPI0_MM_ID) || \
                              ((type) == SPI_ID_MAX))

/** @defgroup  SPI_SLAVE_PIN_TYPE
 *  @{
 */
#define IS_SPI_SLAVE_PIN_TYPE(type) (((type) == SPI_SLAVE_PIN_4) || \
                                     ((type) == SPI_SLAVE_PIN_3))

/** @defgroup  SPI_BYTE_INVERSE_TYPE
 *  @{
 */
#define IS_SPI_BYTE_INVERSE_TYPE(type) (((type) == SPI_BYTE_INVERSE_BYTE0_FIRST) || \
                                        ((type) == SPI_BYTE_INVERSE_BYTE3_FIRST))

/** @defgroup  SPI_BIT_INVERSE_TYPE
 *  @{
 */
#define IS_SPI_BIT_INVERSE_TYPE(type) (((type) == SPI_BIT_INVERSE_MSB_FIRST) || \
                                       ((type) == SPI_BIT_INVERSE_LSB_FIRST))

/** @defgroup  SPI_CLK_PHASE_INVERSE_TYPE
 *  @{
 */
#define IS_SPI_CLK_PHASE_INVERSE_TYPE(type) (((type) == SPI_CLK_PHASE_INVERSE_0) || \
                                             ((type) == SPI_CLK_PHASE_INVERSE_1))

/** @defgroup  SPI_CLK_POLARITY_TYPE
 *  @{
 */
#define IS_SPI_CLK_POLARITY_TYPE(type) (((type) == SPI_CLK_POLARITY_LOW) || \
                                        ((type) == SPI_CLK_POLARITY_HIGH))

/** @defgroup  SPI_FRAMESIZE_TYPE
 *  @{
 */
#define IS_SPI_FRAMESIZE_TYPE(type) (((type) == SPI_FRAME_SIZE_8) ||  \
                                     ((type) == SPI_FRAME_SIZE_16) || \
                                     ((type) == SPI_FRAME_SIZE_24) || \
                                     ((type) == SPI_FRAME_SIZE_32))

/** @defgroup  SPI_WORK_MODE_TYPE
 *  @{
 */
#define IS_SPI_WORK_MODE_TYPE(type) (((type) == SPI_WORK_MODE_SLAVE) || \
                                     ((type) == SPI_WORK_MODE_MASTER))

/** @defgroup  SPI_TIMEOUT_TYPE
 *  @{
 */
#define IS_SPI_TIMEOUT_TYPE(type) (((type) == SPI_TIMEOUT_DISABLE) || \
                                   ((type) == SPI_TIMEOUT_ENABLE))

/** @defgroup  SPI_FIFOSTATUS_TYPE
 *  @{
 */
#define IS_SPI_FIFOSTATUS_TYPE(type) (((type) == SPI_FIFO_TX_OVERFLOW) ||  \
                                      ((type) == SPI_FIFO_TX_UNDERFLOW) || \
                                      ((type) == SPI_FIFO_RX_OVERFLOW) ||  \
                                      ((type) == SPI_FIFO_RX_UNDERFLOW))

/** @defgroup  SPI_INT_TYPE
 *  @{
 */
#define IS_SPI_INT_TYPE(type) (((type) == SPI_INT_END) ||            \
                               ((type) == SPI_INT_TX_FIFO_REQ) ||    \
                               ((type) == SPI_INT_RX_FIFO_REQ) ||    \
                               ((type) == SPI_INT_SLAVE_TIMEOUT) ||  \
                               ((type) == SPI_INT_SLAVE_UNDERRUN) || \
                               ((type) == SPI_INT_FIFO_ERROR) ||     \
                               ((type) == SPI_INT_ALL))

/*@} end of group SPI_Public_Constants */

/** @defgroup  SPI_Public_Macros
 *  @{
 */
#define SPI_RX_FIFO_SIZE 32
#define SPI_TX_FIFO_SIZE 32

/*@} end of group SPI_Public_Macros */

/** @defgroup  SPI_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void SPI0_IRQHandler(void);
void SPI1_IRQHandler(void);
#endif
BL_Err_Type SPI_Init(SPI_ID_Type spiNo, SPI_CFG_Type *spiCfg);
BL_Err_Type SPI_DeInit(SPI_ID_Type spiNo);
BL_Err_Type SPI_ClockConfig(SPI_ID_Type spiNo, SPI_ClockCfg_Type *clockCfg);
BL_Err_Type SPI_FifoConfig(SPI_ID_Type spiNo, SPI_FifoCfg_Type *fifoCfg);
BL_Err_Type SPI_Enable(SPI_ID_Type spiNo, SPI_WORK_MODE_Type modeType);
BL_Err_Type SPI_Disable(SPI_ID_Type spiNo, SPI_WORK_MODE_Type modeType);
BL_Err_Type SPI_SetFrameSize(SPI_ID_Type spiNo, SPI_FrameSize_Type frameSize);
BL_Err_Type SPI_SetTimeOutValue(SPI_ID_Type spiNo, uint16_t value);
BL_Err_Type SPI_SetDeglitchCount(SPI_ID_Type spiNo, uint8_t cnt);
BL_Err_Type SPI_RxIgnoreEnable(SPI_ID_Type spiNo, uint8_t startPoint, uint8_t stopPoint);
BL_Err_Type SPI_RxIgnoreDisable(SPI_ID_Type spiNo);
BL_Err_Type SPI_ClrTxFifo(SPI_ID_Type spiNo);
BL_Err_Type SPI_ClrRxFifo(SPI_ID_Type spiNo);
BL_Err_Type SPI_ClrIntStatus(SPI_ID_Type spiNo, SPI_INT_Type intType);
BL_Err_Type SPI_IntMask(SPI_ID_Type spiNo, SPI_INT_Type intType, BL_Mask_Type intMask);
BL_Err_Type SPI_Int_Callback_Install(SPI_ID_Type spiNo, SPI_INT_Type intType, intCallback_Type *cbFun);
BL_Err_Type SPI_SendData(SPI_ID_Type spiNo, void *buff, uint32_t length, SPI_Timeout_Type timeoutType);
BL_Err_Type SPI_ReceiveData(SPI_ID_Type spiNo, void *buff, uint32_t length, SPI_Timeout_Type timeoutType);
BL_Err_Type SPI_SendRecvData(SPI_ID_Type spiNo, void *sendBuff, void *recvBuff, uint32_t length,
                             SPI_Timeout_Type timeoutType);
uint8_t SPI_GetTxFifoCount(SPI_ID_Type spiNo);
uint8_t SPI_GetRxFifoCount(SPI_ID_Type spiNo);
BL_Sts_Type SPI_GetIntStatus(SPI_ID_Type spiNo, SPI_INT_Type intType);
BL_Sts_Type SPI_GetFifoStatus(SPI_ID_Type spiNo, SPI_FifoStatus_Type fifoSts);
BL_Sts_Type SPI_GetBusyStatus(SPI_ID_Type spiNo);
BL_Err_Type SPI_SetClock(SPI_ID_Type spiNo, uint32_t clk);
/*@} end of group SPI_Public_Functions */

/*@} end of group SPI */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_SPI_H__ */
