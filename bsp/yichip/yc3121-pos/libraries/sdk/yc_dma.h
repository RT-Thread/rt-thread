/*
File Name    : yc_dma.h
Author       : Yichip
Version      : V1.0
Date         : 2018/03/27
Description  : DMA Mem_TO_Mem Mode encapsulation.		
		           If enable DMA interrupt ,enter interrupt after sending data by default,and just one DMA IT Mode.
*/

#ifndef __YC_DMA_H_
#define __YC_DMA_H_

#include "yc3121.h"
#define DMACH_QSPI 0

#define DMA_ENABLE_BIT_Pos 7
#define DMA_ENABLE ((uint8_t)1 << DMA_ENABLE_BIT_Pos)

#define DMA_IT_BIT_Pos 1
#define DMA_IT_ENABLE ((uint32_t)1 << DMA_IT_BIT_Pos)
/*Peripheral DMA Channel*/

typedef struct
{
  uint32_t DMA_MemorySourceAddr; /*!< Specifies the memory Source address for Channel Mem_to_Mem. */

  uint32_t DMA_MemoryDestAddr; /*!<Specifies the memory Destination  address for Channel Mem_to_Mem. */

  uint32_t DMA_BlockSize; /*!< Specifies the  Total Number of data items during the transaction. */

} DMA_InitTypeDef;

/**
  * @brief  Initializes the DMA Mem_to_Mem Channelx according to the specified
  *         parameters in the DMA_InitStruct.
  * @param  DMA_InitStruct: pointer to a DMA_InitTypeDef structure that
  *         contains the configuration information for the specified DMA Channel.
  * @retval None
  */
void DMA_Init(DMA_InitTypeDef *DMA_InitStruct);

/**
  * @brief  Enables or disables  Channel DMACH_MEMCP.
  * @param  NewState: new state of the DMAy Channelx. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_ChannelCmd(FunctionalState NewState);

/**
  * @brief  Set  DMA Source Address.
  * @param  Address: DMA source address
  * @retval None
  */
void DMA_SetSRCAddress(uint32_t Address);

/**
  * @brief  Set  DMA destination Address.
  * @param  Address: DMA source address
  * @retval None
  */
void DMA_SetDSRAddress(uint32_t Address);

/**
  * @brief  Checks whether the DMACH_MEMCP Channelx flag is set or not.
  * @param  None
  * @retval None
  */
FlagStatus DMA_GetFlagStatus(void);

/**
  * @brief  Clears the  DMACH_MEMCP Channelx's pending flags.
  * @param  None
  * @retval Enable or Disable.
  */
FunctionalState DMA_IsChannelEnabled(void);

/**
  * @brief   Clears the DMACH_MEMCP Channelx's interrupt pending bits.
  * @param  None
  * @retval None
  */
void DMA_ClearITPendingBit(void);

/**
  * @brief   ENABLE or DISABLE intterrupt
  * @param  NewState
  * @retval None
  */
void DMA_ITConfig(FunctionalState NewState);
#endif
