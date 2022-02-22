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


#ifndef __AIR105_DMA_H
#define __AIR105_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

typedef struct
{
  uint32_t DMA_Peripheral;

  uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx. */

  uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx. */

  uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction */

  uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_incremented_mode */

  uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_incremented_mode */

  uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data item width.
                                        This parameter can be a value of @ref DMA_data_size */

  uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data item width.
                                   This parameter can be a value of @ref DMA_data_size */

  uint32_t DMA_PeripheralBurstSize; /*!< Specifies the Peripheral Number of data items during per burst transaction.
                                    read or write from the Peripheral every time a burst transaction request
                                    This parameter can be a value of @ref DMA_burst_size */

  uint32_t DMA_MemoryBurstSize;     /*!< Specifies the Memory Number of data items during per burst transaction.
                                    read or write from the Memory every time a burst transaction request
                                    This parameter can be a value of @ref DMA_burst_size */

  uint32_t DMA_PeripheralHandShake; /*!< Specifies the HandShake to control the DMA transacation.
                                    This parameter can be a value of @ref DMA_peripheral_handshake */

  uint32_t DMA_BlockSize;           /*!< Specifies the Total Number of data items during the transaction. */

  uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level */
}DMA_InitTypeDef;

/**
 * DMA多块传输内存表
 *
 */
typedef struct _lli
{
    uint32_t SAR;
    uint32_t DAR;
    uint32_t LLP;
    uint32_t CTL_L;
    uint32_t CTL_H;
    uint32_t DSTAT;
}LLI;

/**多块传输模式
  * @}
  */
#define  Multi_Block_MODE01        (uint8_t)0x00    /*Single-block or last transfer of multi-block*/
#define  Multi_Block_MODE02        (uint8_t)0x01    /*Auto-reload multi-block transfer with contiguous SAR*/
#define  Multi_Block_MODE03        (uint8_t)0x02    /*Auto-reload multi-block transfer with contiguous DAR*/
#define  Multi_Block_MODE04        (uint8_t)0x03    /*Auto-reload multi-block transfer*/
#define  Multi_Block_MODE05        (uint8_t)0x04    /*Single-block or last transfer of multi-block*/
#define  Multi_Block_MODE06        (uint8_t)0x05    /*Linked list multi-block transfer with contiguous SAR*/
#define  Multi_Block_MODE07        (uint8_t)0x06    /*Linked list multi-block transfer with auto-reload SAR*/
#define  Multi_Block_MODE08        (uint8_t)0x07    /*Linked list multi-block transfer with contiguous DAR*/
#define  Multi_Block_MODE09        (uint8_t)0x08    /*Linked list multi-block transfer with auto-reload DAR*/
#define  Multi_Block_MODE10        (uint8_t)0x09    /*Linked list multi-block transfer*/

/** @defgroup DMA_data_transfer_direction
  * @{
  */

#define DMA_DIR_Memory_To_Memory                                ((uint32_t)0x0000)
#define DMA_DIR_Memory_To_Peripheral                            ((uint32_t)0x0001)
#define DMA_DIR_Peripheral_To_Memory                            ((uint32_t)0x0002)

/**
  * @}
  */

/** @defgroup DMA_incremented_mode
  * @{
  */

#define DMA_Inc_Increment                       ((uint32_t)0x00000000)
#define DMA_Inc_Decrement                       ((uint32_t)0x00000001)
#define DMA_Inc_Nochange                        ((uint32_t)0x00000002)
#define IS_DMA_INC_STATE(STATE) (((STATE) == DMA_Inc_Increment) || \
                                            ((STATE) == DMA_Inc_Decrement) || \
                                            ((STATE) == DMA_Inc_Nochange))
/**
  * @}
  */

/** @defgroup DMA_data_size
  * @{
  */

#define DMA_DataSize_Byte                                   ((uint32_t)0x0000)
#define DMA_DataSize_HalfWord                               ((uint32_t)0x0001)
#define DMA_DataSize_Word                                   ((uint32_t)0x0002)
#define IS_DMA_DATA_SIZE(SIZE)                              (((SIZE) == DMA_DataSize_Byte) || \
                                                            ((SIZE) == DMA_DataSize_HalfWord) || \
                                                            ((SIZE) == DMA_DataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_burst_size
  * @{
  */
#define DMA_BurstSize_1                                     ((uint32_t)0x00)
#define DMA_BurstSize_4                                     ((uint32_t)0x01)
#define DMA_BurstSize_8                                     ((uint32_t)0x02)
#define DMA_BurstSize_16                                    ((uint32_t)0x03)
#define DMA_BurstSize_32                                    ((uint32_t)0x04)
/**
  * @}
  */

/** @defgroup DMA_peripheral_handshake
  * @{
  */
#define DMA_PeripheralHandShake_Hardware                        ((uint32_t)0x0000)
#define DMA_PeripheralHandShake_Software                        ((uint32_t)0x0001)
/**
  * @}
  */

/** @defgroup DMA_Priority
  * @{
  */
#define DMA_Priority_0                                          ((uint32_t)0x00000000)
#define DMA_Priority_1                                          ((uint32_t)0x00000020)
#define DMA_Priority_2                                          ((uint32_t)0x00000040)
#define DMA_Priority_3                                          ((uint32_t)0x00000060)
#define DMA_Priority_4                                          ((uint32_t)0x00000080)
#define DMA_Priority_5                                          ((uint32_t)0x000000A0)
#define DMA_Priority_6                                          ((uint32_t)0x000000C0)

/**
  * @}
  */

/** @defgroup DMA_IT
  * @{
  */
#define DMA_IT_BlockTransferComplete                    ((uint32_t)0x01)
#define DMA_IT_DestinationTransactionComplete           ((uint32_t)0x02)
#define DMA_IT_Error                                    ((uint32_t)0x04)
#define DMA_IT_SourceTransactionComplete                ((uint32_t)0x08)
#define DMA_IT_DMATransferComplete                      ((uint32_t)0x10)
/**
  * @}
  */

void DMA_Init(DMA_TypeDef* DMA_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_ChannelCmd(DMA_TypeDef* DMA_Channelx, FunctionalState NewState);
void DMA_Cmd(FunctionalState NewState);
void DMA_ChannelConfig(DMA_TypeDef* DMA_Channelx, uint32_t DMA_Peripheral, uint32_t DMA_DIR);
void DMA_SetSRCAddress(DMA_TypeDef* DMA_Channelx, uint32_t Address);
void DMA_SetDSRAddress(DMA_TypeDef* DMA_Channelx, uint32_t Address);

void DMA_ITConfig(DMA_TypeDef* DMA_Channelx, uint32_t DMA_IT, FunctionalState NewState);

FlagStatus DMA_GetFlagStatus(uint32_t DMA_FLAG);
void DMA_ClearFlag(uint32_t DMA_FLAG);

FunctionalState DMA_IsChannelEnabled(DMA_TypeDef* DMA_Channelx);

ITStatus DMA_GetITStatus(DMA_TypeDef* DMA_Channelx,uint32_t DMA_IT);
FlagStatus DMA_GetRawStatus(DMA_TypeDef* DMA_Channelx,uint32_t DMA_IT);
void DMA_ClearITPendingBit(DMA_TypeDef* DMA_Channelx,uint32_t DMA_IT);

void DMA_MultiBlockInit(DMA_TypeDef* DMA_Channelx, DMA_InitTypeDef* DMA_InitStruct ,\
                                LLI *first_lli,uint8_t Multi_Block_Mode);
void DMA_InitLLI(DMA_TypeDef* DMA_Channelx,LLI *lli,LLI *next_lli,
                            void *src_addr,void *dest_addr,uint16_t btsize);
uint32_t DMA_GetTransferNum(DMA_TypeDef* DMA_Channelx, uint32_t first_adr);

#ifdef __cplusplus
}
#endif

#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
