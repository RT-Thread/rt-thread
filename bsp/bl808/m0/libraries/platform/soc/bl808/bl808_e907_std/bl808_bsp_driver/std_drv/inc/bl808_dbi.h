/**
  ******************************************************************************
  * @file    bl808_dbi.h
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
#ifndef __BL808_DBI_H__
#define __BL808_DBI_H__

#include "dbi_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DBI
 *  @{
 */

/** @defgroup  DBI_Public_Types
 *  @{
 */

/**
 *  @brief DBI mode type definition
 */
typedef enum {
    DBI_TYPE_B = 0,    /*!< DBI type B */
    DBI_TYPE_C_3_WIRE, /*!< DBI type C 3 wire mode */
    DBI_TYPE_C_4_WIRE, /*!< DBI type C 4 wire mode */
} DBI_Mode_Type;

/**
 *  @brief DBI pixel format type definition
 */
typedef enum {
    DBI_PIXEL_RGB565 = 0, /*!< DBI pixel format is RGB565 */
    DBI_PIXEL_RGB666 = 1, /*!< DBI pixel format is RGB666 */
    DBI_PIXEL_RGB888 = 1, /*!< DBI pixel format is RGB888 */
} DBI_Pixel_Format_Type;

/**
 *  @brief DBI SCL clock phase definition
 */
typedef enum {
    DBI_SCL_CLK_PHASE_0 = 0, /*!< DBI SCL clock phase 0 */
    DBI_SCL_CLK_PHASE_1,     /*!< DBI SCL clock phase 1 */
} DBI_SCL_CLK_Phase_Type;

/**
 *  @brief DBI SCL clock polarity definition
 */
typedef enum {
    DBI_SCL_CLK_POLARITY_LOW = 0, /*!< DBI SCL clock output low at idle state */
    DBI_SCL_CLK_POLARITY_HIGH,    /*!< DBI SCL clock output high at idle state */
} DBI_SCL_CLK_Polarity_Type;

/**
 *  @brief DBI read/write data direction type definition
 */
typedef enum {
    DBI_DATA_READ = 0, /*!< DBI read data */
    DBI_DATA_WRITE,    /*!< DBI write data */
} DBI_Data_Direction_Type;

/**
 *  @brief DBI data type definition
 */
typedef enum {
    DBI_DATA_NORMAL = 0, /*!< Normal data */
    DBI_DATA_PIXEL,      /*!< Pixel data */
} DBI_Data_Type;

/**
 *  @brief DBI interrupt type definition
 */
typedef enum {
    DBI_INT_END = 0,     /*!< DBI transfer end interrupt,shared by both type B and C mode */
    DBI_INT_TX_FIFO_REQ, /*!< DBI tx fifo ready interrupt(tx fifo count > tx fifo threshold) */
    DBI_INT_FIFO_ERR,    /*!< DBI tx/rx fifo overflow/underflow error interrupt */
    DBI_INT_ALL,         /*!< DBI all interrupt */
} DBI_INT_Type;

/**
 *  @brief DBI tx fifo overflow or underflow type definition
 */
typedef enum {
    DBI_TX_OVERFLOW,  /*!< DBI tx fifo overflow */
    DBI_TX_UNDERFLOW, /*!< DBI tx fifo underflow */
} DBI_Overflow_Type;

/**
 *  @brief DBI fifo format type definition
 */
typedef enum {
    DBI_FIFO_888_NBGR = 0, /*!< DBI fifo format is None[31:24] B[23:16] G[15:8] R[7:0] */
    DBI_FIFO_888_NRGB,     /*!< DBI fifo format is None[31:24] R[23:16] G[15:8] B[7:0] */
    DBI_FIFO_888_BGRN,     /*!< DBI fifo format is B[31:24] G[23:16] R[15:8] None[7:0] */
    DBI_FIFO_888_RGBN,     /*!< DBI fifo format is R[31:24] G[23:16] B[15:8] None[7:0] */
    DBI_FIFO_888_RGBR,     /*!< DBI fifo format is R[31:24] G[23:16] B[15:8] R[7:0] */
    DBI_FIFO_888_BGRB,     /*!< DBI fifo format is B[31:24] G[23:16] R[15:8] B[7:0] */
    DBI_FIFO_565_BGRBGR,   /*!< DBI fifo format is B[31:27] G[26:21] R[20:16] B[15:11] G[10:5] R[4:0] */
    DBI_FIFO_565_RGBRGB,   /*!< DBI fifo format is R[31:27] G[26:21] B[20:16] R[15:11] G[10:5] B[4:0] */
} DBI_FIFO_Format_Type;

typedef struct
{
    uint8_t startLen;                      /*!< Length of start/stop condition */
    uint8_t dataPhase0Len;                 /*!< Length of data phase 0 */
    uint8_t dataPhase1Len;                 /*!< Length of data phase 1 */
    uint8_t intervalLen;                   /*!< Length of interval between pixel data */
}DBI_Period_CFG_Type;

/**
 *  @brief DBI configuration structure type definition
 */
typedef struct
{
    DBI_Mode_Type mode;                    /*!< DBI type B or C select */
    DBI_Pixel_Format_Type pixelFormat;     /*!< DBI pixel format */
    DBI_FIFO_Format_Type fifoFormat;       /*!< DBI fifo format */
    BL_Fun_Type continueEn;                /*!< Enable:CS will stay asserted between each consecutive pixel, disable:CS will de-assert between each pixel */
    BL_Fun_Type dummyEn;                   /*!< Enable:dummy cycle will be inserted between command phase adn data phase, disable:no dummy cycle */
    uint8_t dummyCnt;                      /*!< Dummy cycle count,effective only in type C(fixed to 1 in type B) */
    DBI_SCL_CLK_Phase_Type clkPhase;       /*!< DBI clock phase */
    DBI_SCL_CLK_Polarity_Type clkPolarity; /*!< DBI clock polarity */
    DBI_Period_CFG_Type period;            /*!< Period configuration */
} DBI_CFG_Type;

/**
 *  @brief DBI command and data configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type commandEn;           /*!< Enable or disable command */
    uint8_t command;                 /*!< Command to send */
    BL_Fun_Type dataEn;              /*!< Enable or disable data */
    DBI_Data_Type dataType;          /*!< Select normal data or pixel data */
    DBI_Data_Direction_Type dataDir; /*!< Select read or write data */
    uint8_t dataCnt;                 /*!< Set byte count of normal data */
    uint32_t data;                   /*!< Data to send */
} DBI_CD_CFG_Type;

/*@} end of group DBI_Public_Types */

/** @defgroup  DBI_Public_Constants
 *  @{
 */

/** @defgroup  DBI_MODE_TYPE
 *  @{
 */
#define IS_DBI_MODE_TYPE(type) (((type) == DBI_TYPE_B) ||        \
                                ((type) == DBI_TYPE_C_3_WIRE) || \
                                ((type) == DBI_TYPE_C_4_WIRE))

/** @defgroup  DBI_PIXEL_FORMAT_TYPE
 *  @{
 */
#define IS_DBI_PIXEL_FORMAT_TYPE(type) (((type) == DBI_PIXEL_RGB565) || \
                                        ((type) == DBI_PIXEL_RGB666) || \
                                        ((type) == DBI_PIXEL_RGB888))

/** @defgroup  DBI_SCL_CLK_PHASE_TYPE
 *  @{
 */
#define IS_DBI_SCL_CLK_PHASE_TYPE(type) (((type) == DBI_SCL_CLK_PHASE_0) || \
                                         ((type) == DBI_SCL_CLK_PHASE_1))

/** @defgroup  DBI_SCL_CLK_POLARITY_TYPE
 *  @{
 */
#define IS_DBI_SCL_CLK_POLARITY_TYPE(type) (((type) == DBI_SCL_CLK_POLARITY_LOW) || \
                                            ((type) == DBI_SCL_CLK_POLARITY_HIGH))

/** @defgroup  DBI_DATA_DIRECTION_TYPE
 *  @{
 */
#define IS_DBI_DATA_DIRECTION_TYPE(type) (((type) == DBI_DATA_READ) || \
                                          ((type) == DBI_DATA_WRITE))

/** @defgroup  DBI_DATA_TYPE
 *  @{
 */
#define IS_DBI_DATA_TYPE(type) (((type) == DBI_DATA_NORMAL) || \
                                ((type) == DBI_DATA_PIXEL))

/** @defgroup  DBI_INT_TYPE
 *  @{
 */
#define IS_DBI_INT_TYPE(type) (((type) == DBI_INT_END) ||         \
                               ((type) == DBI_INT_TX_FIFO_REQ) || \
                               ((type) == DBI_INT_FIFO_ERR) ||    \
                               ((type) == DBI_INT_ALL))

/** @defgroup  DBI_OVERFLOW_TYPE
 *  @{
 */
#define IS_DBI_OVERFLOW_TYPE(type) (((type) == DBI_TX_OVERFLOW) || \
                                    ((type) == DBI_TX_UNDERFLOW))

/** @defgroup  DBI_FIFO_FORMAT_TYPE
 *  @{
 */
#define IS_DBI_FIFO_FORMAT_TYPE(type) (((type) == DBI_FIFO_888_NBGR) ||   \
                                       ((type) == DBI_FIFO_888_NRGB) ||   \
                                       ((type) == DBI_FIFO_888_BGRN) ||   \
                                       ((type) == DBI_FIFO_888_RGBN) ||   \
                                       ((type) == DBI_FIFO_888_RGBR) ||   \
                                       ((type) == DBI_FIFO_888_BGRB) ||   \
                                       ((type) == DBI_FIFO_565_BGRBGR) || \
                                       ((type) == DBI_FIFO_565_RGBRGB))

/*@} end of group DBI_Public_Constants */

/** @defgroup  DBI_Public_Macros
 *  @{
 */
#define DBI_TX_FIFO_SIZE 8

/*@} end of group DBI_Public_Macros */

/** @defgroup  DBI_Public_Functions
 *  @{
 */
#ifndef BL808_USE_HAL_DRIVER
void DBI_IRQHandler(void);
#endif
BL_Err_Type DBI_Init(DBI_CFG_Type *dbiCfg);
void DBI_Enable(void);
void DBI_Disable(void);

void DBI_SetPeriod(DBI_Period_CFG_Type *period);
void DBI_SetCommand(uint8_t Command);
void DBI_SetPhaseState(BL_Fun_Type commandEn, BL_Fun_Type dataEn);
void DBI_SetDataTypeAndCount(DBI_Data_Type dataType, uint32_t dataCount);
void DBI_SetNormalDataDir(DBI_Data_Direction_Type dataDir);
void DBI_ReadNormlData(uint8_t dataSize, uint8_t *dataBuff);
void DBI_WriteNormlData(uint8_t dataSize, uint8_t *dataBuff);
void DBI_WirteData2FIFO(uint32_t wordCount, uint32_t *dataBuff);

uint32_t DBI_GetWordCountOfPixelData(int32_t PixelCount);
void DBI_SendCmdWithNormalData(uint8_t command, uint8_t dataSize, uint8_t *dataBuff);
void DBI_SendCmdAndReadNormalData(uint8_t command, uint8_t dataSize, uint8_t *dataBuff);
void DBI_SendCmdWithPixelData(uint8_t command, int32_t PixelCount, uint32_t *pixelBuff);

void DBI_TxFifoClear(void);
void DBI_SetDMA(BL_Fun_Type dmaEn);
void DBI_SetTxFifoThreshold(uint8_t threshold);
uint8_t DBI_GetTxFifoCount(void);
BL_Sts_Type DBI_GetIntStatus(DBI_INT_Type intType);
BL_Sts_Type DBI_GetOverflowStatus(DBI_Overflow_Type overflow);
BL_Sts_Type DBI_GetBusBusyStatus(void);
void DBI_IntMask(DBI_INT_Type intType, BL_Mask_Type intMask);
void DBI_IntClear(void);
void DBI_Int_Callback_Install(DBI_INT_Type intType, intCallback_Type *cbFun);

/*@} end of group DBI_Public_Functions */

/*@} end of group DBI */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DBI_H__ */
