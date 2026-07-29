/*
File Name    : yc_dma.c
Author       : Yichip
Version      : V1.0
Date         : 2018/03/27
Description  : DMA Mem_TO_Mem Mode encapsulation.		
		       If enable DMA interrupt ,enter interrupt after sending data by default,and just one DMA IT Mode.
*/

#include "yc_dma.h"

#define DMA_Channel DMACH_MEMCP
#define DMA_CLEAR_IT_BIT_Pos 6
#define DMA_ENTERIT_BIT_Pos 1
#define DMA_DATA_COMPLETE_BIT_Pos 0

void DMA_Init(DMA_InitTypeDef *DMA_InitStruct)
{
	DMA_SRC_ADDR(DMACH_MEMCP) = DMA_InitStruct->DMA_MemorySourceAddr;
	DMA_DEST_ADDR(DMACH_MEMCP) = DMA_InitStruct->DMA_MemoryDestAddr;
	DMA_LEN(DMACH_MEMCP) = (DMA_InitStruct->DMA_BlockSize << 16) | DMA_InitStruct->DMA_BlockSize;
}

void DMA_ChannelCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		DMA_START(DMACH_MEMCP) |= (DMA_ENABLE);
	}
	else
	{
		DMA_START(DMACH_MEMCP) &= ~(DMA_ENABLE);
	}
}

void DMA_SetSRCAddress(uint32_t Address)
{
	DMA_SRC_ADDR(DMACH_MEMCP) = Address;
}

void DMA_SetDSRAddress(uint32_t Address)
{
	DMA_DEST_ADDR(DMACH_MEMCP) = Address;
}

FunctionalState DMA_IsChannelEnabled(void)
{
	if (1 == (DMA_START(DMACH_MEMCP) & DMA_ENABLE))
	{
		return ENABLE;
	}
	else
	{
		return DISABLE;
	}
}

FlagStatus DMA_GetFlagStatus(void)
{
	return (FlagStatus)((DMA_STATUS(DMACH_MEMCP) & (1 << DMA_DATA_COMPLETE_BIT_Pos)));
}

void DMA_ClearITPendingBit(void)
{
	DMA_START(DMACH_MEMCP) |= (1 << DMA_CLEAR_IT_BIT_Pos);
}

void DMA_ITConfig(FunctionalState NewState)
{
	DMA_CONFIG(DMACH_MEMCP) &= ~(1 << DMA_ENTERIT_BIT_Pos);
	DMA_CONFIG(DMACH_MEMCP) |= (NewState << DMA_ENTERIT_BIT_Pos);
}
