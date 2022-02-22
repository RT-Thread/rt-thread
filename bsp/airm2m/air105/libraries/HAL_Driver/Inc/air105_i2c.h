/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef __AIR105_I2C_H
#define __AIR105_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"


/** @defgroup I2C_mode
  * @{
  */
typedef enum
{
    I2C_Mode_Master                 =((uint32_t)0x0001),
    I2C_Mode_Slave                  =((uint32_t)0x0002)
}I2CMode_TypeDef;

#define IS_I2C_MODE(MODE)           (((MODE) == I2C_Mode_Master) || \
                                    ((MODE) == I2C_Mode_Slave))
/**
  * @}
  */

typedef struct
{
    uint32_t I2C_ClockSpeed;            /*!< Specifies the clock frequency. */

    I2CMode_TypeDef I2C_Mode;

    uint32_t I2C_DutyCycle;             /*!< Specifies the I2C fast mode duty cycle.
                                         This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */
    uint32_t I2C_SDASetupTime;

    uint32_t I2C_SDAHoldTime;

    uint32_t I2C_TargetAddress;

    uint32_t I2C_TargetAddressMode;

    uint32_t I2C_OwnAddress;            /*!< Specifies the slave mode own address.
                                         This parameter can be a 7-bit or 10-bit address. */

    uint32_t I2C_AcknowledgedAddress;   /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                         This parameter can be a value of @ref I2C_acknowledged_address */

    uint32_t I2C_RXFIFOFullThreshold;

    uint32_t I2C_TXFIFOEmptyThreshold;

    FunctionalState I2C_GenerateRestartEnable;
}I2C_InitTypeDef;


typedef struct
{
    uint32_t I2C_DMAReq;
    uint32_t I2C_DMAReceiveLevel;
    uint32_t I2C_DMATransmitLevel;
    FunctionalState I2C_DMAEnCmd;
}I2C_DMAInitTypeDef;


#define I2C_ClockSpeed_100KHz                   (100000)
#define I2C_ClockSpeed_400KHz                   (400000)


/** @defgroup I2C_duty_cycle_in_fast_mode
  * @{
  */
/*Tlow/Thigh = ((I2C_DutyCycle_x_y & 0xFF00) >> 8) / (I2C_DutyCycle_x_y & 0x00FF)*/
#define I2C_DutyCycle_1                 ((uint16_t)0x0101) /*!< I2C standard mode Tlow/Thigh = 1 */
#define I2C_DutyCycle_16_9              ((uint16_t)0x1009) /*!< I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_DutyCycle_2                 ((uint16_t)0x0201) /*!< I2C fast mode Tlow/Thigh = 2 */
#define I2C_DutyCycle_8_3               ((uint16_t)0x0803) /*!< I2C high mode Tlow/Thigh = 8/3 */
#define IS_I2C_DUTY_CYCLE(CYCLE)        (((CYCLE) == I2C_DutyCycle_16_9) || \
                                        ((CYCLE) == I2C_DutyCycle_2))
/**
  * @}
  */

#define IS_I2C_SDA_SETUP_TIME(TIME)     ((TIME) <= 0x000000FF)
#define IS_I2C_SDA_HOLD_TIME(TIME)      ((TIME) <= 0x0000FFFF)

/** @defgroup I2C_acknowledged_address
  * @{
  */
#define I2C_AcknowledgedAddress_7bit            ((uint16_t)0x0001)
#define I2C_AcknowledgedAddress_10bit           ((uint16_t)0x0002)
#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS)     (((ADDRESS) == I2C_AcknowledgedAddress_7bit) || \
                                                ((ADDRESS) == I2C_AcknowledgedAddress_10bit))
/**
  * @}
  */

/** @defgroup Target_Address_Bit
  * @{
  */
#define I2C_TargetAddressMode_7bit              ((uint16_t)0x0001)
#define I2C_TargetAddressMode_10bit             ((uint16_t)0x0002)
#define IS_I2C_TARGET_ADDRESS_MODE(ADDRESS)     (((ADDRESS) == I2C_TargetAddressMode_7bit) || \
                                                ((ADDRESS) == I2C_TargetAddressMode_10bit))
/**
  * @}
  */


/** @defgroup SPI_RXFIFOFullThreshold
  * @{
  */
#define I2C_RXFIFOFullThreshold_1               ((uint32_t)0x0000)
#define I2C_RXFIFOFullThreshold_2               ((uint32_t)0x0001)
#define I2C_RXFIFOFullThreshold_3               ((uint32_t)0x0002)
#define I2C_RXFIFOFullThreshold_4               ((uint32_t)0x0003)
#define I2C_RXFIFOFullThreshold_5               ((uint32_t)0x0004)
#define I2C_RXFIFOFullThreshold_6               ((uint32_t)0x0005)
#define I2C_RXFIFOFullThreshold_7               ((uint32_t)0x0006)
#define I2C_RXFIFOFullThreshold_8               ((uint32_t)0x0007)

#define IS_I2C_RX_FIFO_FULL_THRESHOLD(THRESHOLD)    (THRESHOLD <= I2C_RXFIFOFullThreshold_8)
/**
  * @}
  */

/** @defgroup SPI_TXFIFOEmptyThreshold
  * @{
  */
#define I2C_TXFIFOEmptyThreshold_0              ((uint32_t)0x0000)
#define I2C_TXFIFOEmptyThreshold_1              ((uint32_t)0x0001)
#define I2C_TXFIFOEmptyThreshold_2              ((uint32_t)0x0002)
#define I2C_TXFIFOEmptyThreshold_3              ((uint32_t)0x0003)
#define I2C_TXFIFOEmptyThreshold_4              ((uint32_t)0x0004)
#define I2C_TXFIFOEmptyThreshold_5              ((uint32_t)0x0005)
#define I2C_TXFIFOEmptyThreshold_6              ((uint32_t)0x0006)
#define I2C_TXFIFOEmptyThreshold_7              ((uint32_t)0x0007)
#define I2C_TXFIFOEmptyThreshold_8              ((uint32_t)0x0008)

#define IS_I2C_TX_FIFO_EMPTY_THRESHOLD(THRESHOLD)   (THRESHOLD <= I2C_TXFIFOEmptyThreshold_8)
/**
  * @}
  */


/** @defgroup I2C_DMAReceiveLevel
  * @{
  */
#define I2C_DMAReceiveLevel_1                   ((uint32_t)0x0000)
#define I2C_DMAReceiveLevel_2                   ((uint32_t)0x0001)
#define I2C_DMAReceiveLevel_3                   ((uint32_t)0x0002)
#define I2C_DMAReceiveLevel_4                   ((uint32_t)0x0003)
#define I2C_DMAReceiveLevel_5                   ((uint32_t)0x0004)
#define I2C_DMAReceiveLevel_6                   ((uint32_t)0x0005)
#define I2C_DMAReceiveLevel_7                   ((uint32_t)0x0006)
#define I2C_DMAReceiveLevel_8                   ((uint32_t)0x0007)

#define IS_I2C_DMA_RECEIVE_LEVEL(LEVEL)         (LEVEL <= I2C_DMAReceiveLevel_8)
/**
  * @}
  */

/** @defgroup I2C_DMATransmitLevel
  * @{
  */
#define I2C_DMATransmitLevel_0                  ((uint32_t)0x0000)
#define I2C_DMATransmitLevel_1                  ((uint32_t)0x0001)
#define I2C_DMATransmitLevel_2                  ((uint32_t)0x0002)
#define I2C_DMATransmitLevel_3                  ((uint32_t)0x0003)
#define I2C_DMATransmitLevel_4                  ((uint32_t)0x0004)
#define I2C_DMATransmitLevel_5                  ((uint32_t)0x0005)
#define I2C_DMATransmitLevel_6                  ((uint32_t)0x0006)
#define I2C_DMATransmitLevel_7                  ((uint32_t)0x0007)

#define IS_I2C_DMA_TRANSMIT_LEVEL(LEVEL)        (LEVEL <= I2C_DMATransmitLevel_7)
/**
  * @}
  */

/** @defgroup I2C_DMA_transfer_requests
  * @{
  */
#define I2C_DMAReq_Rx               ((uint32_t)0x0001)
#define I2C_DMAReq_Tx               ((uint32_t)0x0002)
#define IS_I2C_DMAREQ(DMAREQ)       (((DMAREQ) & I2C_DMAReq_Tx) || \
                                    ((DMAREQ) & I2C_DMAReq_Rx))
/**
  * @}
  */

#define I2C_IT_RXUDF                    ((uint32_t)0x0001)              //clear by hardware
#define I2C_IT_RXOVF                    ((uint32_t)0x0002)              //clear by read
#define I2C_IT_RXF                      ((uint32_t)0x0004)              //clear by read
#define I2C_IT_TXOVF                    ((uint32_t)0x0008)              //clear by read
#define I2C_IT_TXE                      ((uint32_t)0x0010)              //clear by hardware
#define I2C_IT_RD_REQ                   ((uint32_t)0x0020)              //clear by read
#define I2C_IT_TX_ABRT                  ((uint32_t)0x0040)              //clear by read
#define I2C_IT_RX_DONE                  ((uint32_t)0x0080)              //clear by read
#define I2C_IT_ACTIVITY                 ((uint32_t)0x0100)              //clear by read
#define I2C_IT_STOP_DET                 ((uint32_t)0x0200)              //clear by read
#define I2C_IT_START_DET                ((uint32_t)0x0400)
#define I2C_IT_GEN_CALL                 ((uint32_t)0x0800)
#define I2C_IT_ALL                      ((uint32_t)0x0FFF)

#define IS_I2C_CONFIG_IT(IT)            ((((IT) & (~(uint32_t)0x0FFF)) == 0x00) && ((IT) != 0x00))
#define IS_I2C_CLEAR_IT(IT)             ((((IT) & (~(uint32_t)0x0FFF)) == 0x00) && ((IT) != 0x00))
#define IS_I2C_GET_IT(IT)               (((IT) == I2C_IT_RXUDF) || \
                                        ((IT) == I2C_IT_RXOVF) || \
                                        ((IT) == I2C_IT_RXF) || \
                                        ((IT) == I2C_IT_TXOVF) || \
                                        ((IT) == I2C_IT_TXE) || \
                                        ((IT) == I2C_IT_RD_REQ) || \
                                        ((IT) == I2C_IT_TX_ABRT) || \
                                        ((IT) == I2C_IT_RX_DONE) || \
                                        ((IT) == I2C_IT_ACTIVITY) || \
                                        ((IT) == I2C_IT_STOP_DET) || \
                                        ((IT) == I2C_IT_START_DET) || \
                                        ((IT) == I2C_IT_GEN_CALL) || \
                                        ((IT) == I2C_IT_ALL))

#define I2C_FLAG_ACTIVITY               ((uint32_t)0x0001)
#define I2C_FLAG_TXNF                   ((uint32_t)0x0002)
#define I2C_FLAG_TXE                    ((uint32_t)0x0004)
#define I2C_FLAG_RXNE                   ((uint32_t)0x0008)
#define I2C_FLAG_RXF                    ((uint32_t)0x0010)
#define I2C_FLAG_MST_ACTIVITY           ((uint32_t)0x0020)
#define I2C_FLAG_SLV_ACTIVITY           ((uint32_t)0x0040)
#define I2C_FLAG_ALL                    ((uint32_t)0x007F)
#define IS_I2C_GET_FLAG(FLAG)           (((FLAG) == I2C_FLAG_ACTIVITY) || \
                                        ((FLAG) == I2C_FLAG_TXNF) || \
                                        ((FLAG) == I2C_FLAG_TXE) || \
                                        ((FLAG) == I2C_FLAG_RXNE) || \
                                        ((FLAG) == I2C_FLAG_RXF) || \
                                        ((FLAG) == I2C_FLAG_MST_ACTIVITY) || \
                                        ((FLAG) == I2C_FLAG_SLV_ACTIVITY) || \
                                        ((FLAG) == I2C_FLAG_ALL))

#define I2C_TX_ABRT_7BIT_ADDR_NOACK                 ((uint32_t)0x00000001)
#define I2C_TX_ABRT_10BIT_ADDR1_NOACK               ((uint32_t)0x00000002)
#define I2C_TX_ABRT_10BIT_ADDR2_NOACK               ((uint32_t)0x00000004)
#define I2C_TX_ABRT_TXDATA_NOACK                    ((uint32_t)0x00000008)
#define I2C_TX_ABRT_GEN_CALL_NOACK                  ((uint32_t)0x00000010)
#define I2C_TX_ABRT_GEN_CALL_READ                   ((uint32_t)0x00000020)
#define I2C_TX_ABRT_HIGH_SPEED_ACKDET               ((uint32_t)0x00000040)
#define I2C_TX_ABRT_START_BYTE_ACKDET               ((uint32_t)0x00000080)
#define I2C_TX_ABRT_HIGH_SPEED_NORSTRT              ((uint32_t)0x00000100)
#define I2C_TX_ABRT_START_BYTE_NORSTRT              ((uint32_t)0x00000200)
#define I2C_TX_ABRT_10BIT_RD_NORSTRT                ((uint32_t)0x00000400)
#define I2C_TX_ABRT_LOST_ARB                        ((uint32_t)0x00000800)
#define I2C_TX_ABRT_SLVFLUSH_TXFIFO                 ((uint32_t)0x00001000)
#define I2C_TX_ABRT_SLV_LOST_ARB                    ((uint32_t)0x00002000)
#define I2C_TX_ABRT_SLV_RD_INTX                     ((uint32_t)0x00004000)
#define I2C_TX_ABRT_MASTER_DISABLE                  ((uint32_t)0x00008000)
#define I2C_TX_ABRT_USER_ABRT                       ((uint32_t)0x00010000)
#define I2C_TX_ABRT_TX_FLUSH_CNT                    ((uint32_t)0x00020000)
#define IS_I2C_TX_ABRT(ABRT)                        (((ABRT) == I2C_TX_ABRT_7BIT_ADDR_NOACK) || \
                                                    ((ABRT) == I2C_TX_ABRT_10BIT_ADDR1_NOACK) || \
                                                    ((FLAG) == I2C_TX_ABRT_10BIT_ADDR2_NOACK) || \
                                                    ((FLAG) == I2C_TX_ABRT_TXDATA_NOACK) || \
                                                    ((FLAG) == I2C_TX_ABRT_GEN_CALL_NOACK) || \
                                                    ((FLAG) == I2C_TX_ABRT_GEN_CALL_READ) || \
                                                    ((FLAG) == I2C_TX_ABRT_HIGH_SPEED_ACKDET) || \
                                                    ((FLAG) == I2C_TX_ABRT_START_BYTE_ACKDET) || \
                                                    ((FLAG) == I2C_TX_ABRT_HIGH_SPEED_NORSTRT) || \
                                                    ((FLAG) == I2C_TX_ABRT_START_BYTE_NORSTRT) || \
                                                    ((FLAG) == I2C_TX_ABRT_10BIT_RD_NORSTRT) || \
                                                    ((FLAG) == I2C_TX_ABRT_LOST_ARB) || \
                                                    ((FLAG) == I2C_TX_ABRT_SLVFLUSH_TXFIFO) || \
                                                    ((FLAG) == I2C_TX_ABRT_SLV_LOST_ARB) || \
                                                    ((FLAG) == I2C_TX_ABRT_SLV_RD_INTX) || \
                                                    ((FLAG) == I2C_TX_ABRT_MASTER_DISABLE) || \
                                                    ((FLAG) == I2C_TX_ABRT_USER_ABRT) || \
                                                    ((FLAG) == I2C_TX_ABRT_TX_FLUSH_CNT))

typedef enum
{
    I2C_DataCMD_Write                   = (uint32_t)0x01,
    I2C_DataCMD_Read                    = (uint32_t)0x02
}I2CDataCMD_TypeDef;
#define IS_I2C_DATA_CMD(CMD)            (((CMD) == I2C_DataCMD_Write) || \
                                        ((CMD) == I2C_DataCMD_Read))

typedef enum
{
    I2C_DataEndCondition_None           = (uint32_t)0x01,
    I2C_DataEndCondition_Stop           = (uint32_t)0x02,
    I2C_DataEndCondition_Restart        = (uint32_t)0x03
}I2CDataEndCondition_TypeDef;
#define IS_I2C_DATA_END_CONDITION(CONDITION)    (((CONDITION) == I2C_DataEndCondition_None) || \
                                                ((CONDITION) == I2C_DataEndCondition_Stop) || \
                                                ((CONDITION) == I2C_DataEndCondition_Restart))


void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx,I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SetTargetAddress(I2C_TypeDef* I2Cx, uint32_t TargetAddress, uint32_t TargetAddressMode);
void I2C_DMAInit(I2C_TypeDef* I2Cx, I2C_DMAInitTypeDef* I2C_DMAInitStruct);
void I2C_DMAStructInit(I2C_DMAInitTypeDef* I2C_DMAInitStruct);
void I2C_DMACmd(I2C_TypeDef* I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState);
void I2C_SetSDASetupTime(I2C_TypeDef* I2Cx,uint32_t PCLKCycles);
void I2C_SetSDAHoldTime(I2C_TypeDef* I2Cx,uint32_t PCLKCycles);

void I2C_ITConfig(I2C_TypeDef* I2Cx,uint32_t I2C_IT, FunctionalState NewState);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx,uint32_t I2C_IT);
ITStatus I2C_GetRawITStatus(I2C_TypeDef* I2Cx,uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx,uint32_t I2C_IT);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx,uint32_t I2C_FLAG);
uint32_t I2C_GetFlagStatusReg(I2C_TypeDef* I2Cx);
FlagStatus I2C_GetTXAbortSource(I2C_TypeDef* I2Cx,uint32_t I2C_TX_ABRT);
uint32_t I2C_GetTXAbortSourceReg(I2C_TypeDef* I2Cx);
I2CMode_TypeDef I2C_GetI2CMode(I2C_TypeDef* I2Cx);

void I2C_MasterGenerateReceiveSCL(I2C_TypeDef* I2Cx, I2CDataEndCondition_TypeDef DataCondition);
uint16_t I2C_ExtendData(uint8_t Data, I2CDataCMD_TypeDef DataCMD, I2CDataEndCondition_TypeDef DataCondition);
void I2C_WriteDataToDR(I2C_TypeDef* I2Cx, uint16_t ExtendData);
uint8_t I2C_ReadDataFromDR(I2C_TypeDef* I2Cx);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data, I2CDataEndCondition_TypeDef DataCondition);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx, I2CDataEndCondition_TypeDef DataCondition);
void I2C_SendBytes(I2C_TypeDef* I2Cx, uint8_t* Data, uint32_t DataLen, I2CDataEndCondition_TypeDef DataCondition);
void I2C_ReceiveBytes(I2C_TypeDef* I2Cx, uint8_t* Data, uint32_t DataLen, I2CDataEndCondition_TypeDef DataCondition);

void I2C_SlaveGeneralNACKOnlyCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);

FlagStatus I2C_IsEnable(I2C_TypeDef* I2Cx);


#ifdef __cplusplus
}
#endif

#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
