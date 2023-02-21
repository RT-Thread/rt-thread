/**
  ******************************************************************************
  * @file    bl808_i2c.h
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
#ifndef __BL808_I2C_H__
#define __BL808_I2C_H__

#include "i2c_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  I2C
 *  @{
 */

/** @defgroup  I2C_Public_Types
 *  @{
 */

/**
 *  @brief I2C No. type definition
 */
typedef enum {
    I2C0_ID = 0,    /*!< I2C0 define */
    I2C1_ID = 1,    /*!< I2C1 define */
    I2C0_MM_ID = 2, /*!< MM system I2C0 define */
    I2C1_MM_ID = 3, /*!< MM system I2C1 define */
    I2C_ID_MAX,     /*!< I2C max define */
} I2C_ID_Type;

/**
 *  @brief I2C read/write type definition
 */
typedef enum {
    I2C_WRITE = 0, /*!< I2C write direction */
    I2C_READ,      /*!< I2C read direction */
} I2C_Direction_Type;

/**
 *  @brief I2C interrupt type definition
 */
typedef enum {
    I2C_TRANS_END_INT,     /*!< I2C transfer end interrupt */
    I2C_TX_FIFO_READY_INT, /*!< I2C TX fifo ready interrupt */
    I2C_RX_FIFO_READY_INT, /*!< I2C RX fifo ready interrupt */
    I2C_NACK_RECV_INT,     /*!< I2C nack received interrupt */
    I2C_ARB_LOST_INT,      /*!< I2C arbitration lost interrupt */
    I2C_FIFO_ERR_INT,      /*!< I2C TX/RX FIFO error interrupt */
    I2C_INT_ALL,           /*!< I2C interrupt all type */
} I2C_INT_Type;

/**
 *  @brief I2S start condition phase structure type definition
 */
typedef struct
{
    uint8_t len0; /*!< Length of START condition phase 0 */
    uint8_t len1; /*!< Length of START condition phase 1 */
    uint8_t len2; /*!< Length of START condition phase 2 */
    uint8_t len3; /*!< Length of START condition phase 3 */
} I2C_Start_Condition_Phase_Type;

/**
 *  @brief I2S stop condition phase structure type definition
 */
typedef struct
{
    uint8_t len0; /*!< Length of STOP condition phase 0 */
    uint8_t len1; /*!< Length of STOP condition phase 1 */
    uint8_t len2; /*!< Length of STOP condition phase 2 */
    uint8_t len3; /*!< Length of STOP condition phase 3 */
} I2C_Stop_Condition_Phase_Type;

/**
 *  @brief I2S data phase structure type definition
 */
typedef struct
{
    uint8_t len0; /*!< Length of DATA phase 0 */
    uint8_t len1; /*!< Length of DATA phase 1 */
    uint8_t len2; /*!< Length of DATA phase 2 */
    uint8_t len3; /*!< Length of DATA phase 3 */
} I2C_Data_Phase_Type;

/**
 *  @brief I2S transfer structure type definition
 */
typedef struct
{
    uint16_t slaveAddr;         /*!< I2C slave address */
    BL_Fun_Type slaveAddr10Bit; /*!< Enable or disable slave address 10-bit mode */
    BL_Fun_Type stopEveryByte;  /*!< I2C all data byte with stop bit */
    uint8_t subAddrSize;        /*!< Specifies the size of I2C sub address section */
    uint32_t subAddr;           /*!< I2C sub address */
    uint16_t dataSize;          /*!< Specifies the size of I2C data section */
    uint8_t *data;              /*!< Specifies the pointer of I2C R/W data */
    uint32_t clk;               /*!< I2C clk:default is 400k */
} I2C_Transfer_Cfg;

/*@} end of group I2C_Public_Types */

/** @defgroup  I2C_Public_Constants
 *  @{
 */

/** @defgroup  I2C_ID_TYPE
 *  @{
 */
#define IS_I2C_ID_TYPE(type) (((type) == I2C0_ID) ||    \
                              ((type) == I2C1_ID) ||    \
                              ((type) == I2C0_MM_ID) || \
                              ((type) == I2C1_MM_ID) || \
                              ((type) == I2C_ID_MAX))

/** @defgroup  I2C_DIRECTION_TYPE
 *  @{
 */
#define IS_I2C_DIRECTION_TYPE(type) (((type) == I2C_WRITE) || \
                                     ((type) == I2C_READ))

/** @defgroup  I2C_INT_TYPE
 *  @{
 */
#define IS_I2C_INT_TYPE(type) (((type) == I2C_TRANS_END_INT) ||     \
                               ((type) == I2C_TX_FIFO_READY_INT) || \
                               ((type) == I2C_RX_FIFO_READY_INT) || \
                               ((type) == I2C_NACK_RECV_INT) ||     \
                               ((type) == I2C_ARB_LOST_INT) ||      \
                               ((type) == I2C_FIFO_ERR_INT) ||      \
                               ((type) == I2C_INT_ALL))

/*@} end of group I2C_Public_Constants */

/** @defgroup  I2C_Public_Macros
 *  @{
 */

/*@} end of group I2C_Public_Macros */

/** @defgroup  I2C_Public_Functions
 *  @{
 */

/**
 *  @brief I2C Functions
 */
#ifndef BFLB_USE_HAL_DRIVER
void I2C0_IRQHandler(void);
void I2C1_IRQHandler(void);
void I2C2_IRQHandler(void);
void I2C3_IRQHandler(void);
#endif
BL_Err_Type I2C_SendWord(I2C_ID_Type i2cNo, uint32_t data);
BL_Err_Type I2C_RecieveWord(I2C_ID_Type i2cNo, uint32_t *recvBuff);
void I2C_Enable(I2C_ID_Type i2cNo);
void I2C_Disable(I2C_ID_Type i2cNo);
BL_Err_Type I2C_SetDeglitchCount(I2C_ID_Type i2cNo, uint8_t cnt);
BL_Err_Type I2C_DeInit(I2C_ID_Type i2cNo);
void I2C_SetPrd(I2C_ID_Type i2cNo, uint8_t phase);
void I2C_ClockSet(I2C_ID_Type i2cNo, uint32_t clk);
void I2C_SetSclSync(I2C_ID_Type i2cNo, uint8_t enable);
void I2C_Init(I2C_ID_Type i2cNo, I2C_Direction_Type direct, I2C_Transfer_Cfg *cfg);
BL_Sts_Type I2C_IsBusy(I2C_ID_Type i2cNo);
BL_Sts_Type I2C_TransferEndStatus(I2C_ID_Type i2cNo);
BL_Err_Type I2C_MasterSendBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg);
BL_Err_Type I2C_MasterReceiveBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg);
void I2C_IntMask(I2C_ID_Type i2cNo, I2C_INT_Type intType, BL_Mask_Type intMask);
void I2C_Int_Callback_Install(I2C_ID_Type i2cNo, I2C_INT_Type intType, intCallback_Type *cbFun);

/*@} end of group I2C_Public_Functions */

/*@} end of group I2C */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_I2C_H__ */
