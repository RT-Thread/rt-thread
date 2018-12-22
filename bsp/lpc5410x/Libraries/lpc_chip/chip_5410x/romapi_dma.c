/*
 * @brief DMA master ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "romapi_5410x.h"

/* Get memory size in bytes needed for DMA controller driver context */
uint32_t ROM_DMA_GetMemSize(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->GetMemSize();
#else
	return dmaalt_api.GetMemSize();
#endif
}

/* Initialize DMA controller */
ROM_DMA_HANDLE_T ROM_DMA_Init(void *mem, ROM_DMA_INIT_T *pInit)
{
	/* Verify SRAMBASE alginemnt is at least MINDMATABLEALIGN bytes */
	if (((uint32_t) pInit->sramBase & (MINDMATABLEALIGN - 1)) != 0) {
		return NULL;
	}

#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->Init(mem, pInit);
#else
	return dmaalt_api.Init(mem, pInit);
#endif
}

/* Configures a DMA channel */
ErrorCode_t ROM_DMA_SetupChannel(ROM_DMA_HANDLE_T pHandle, ROM_DMA_CHAN_CFG_T *pCfg, uint8_t dmaCh)
{
	if (dmaCh >= NUMDMACHANNELS) {
		return ERR_DMA_CHANNEL_NUMBER;
	}

#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->SetupChannel(pHandle, pCfg, dmaCh);
#else
	return dmaalt_api.SetupChannel(pHandle, pCfg, dmaCh);
#endif
}

/* Initializes a transfer descriptor queue for a channel */
ErrorCode_t ROM_DMA_InitQueue(ROM_DMA_HANDLE_T pHandle, uint8_t dmaCh, ROM_DMA_QUEUE_T *pQueue)
{
	if (dmaCh >= NUMDMACHANNELS) {
		return ERR_DMA_CHANNEL_NUMBER;
	}

#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->InitQueue(pHandle, dmaCh, pQueue);
#else
	return dmaalt_api.InitQueue(pHandle, dmaCh, pQueue);
#endif
}

/* Registers an DMA controller callback for a queue */
void ROM_DMA_RegisterQueueCallback(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, uint32_t cbIndex, void *pCB)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_DMAALT_API->RegisterQueueCallback(pHandle, pQueue, cbIndex, pCB);
#else
	dmaalt_api.RegisterQueueCallback(pHandle, pQueue, cbIndex, pCB);
#endif
}

/* Builds a transfer descriptor chain from the passed settings */
ErrorCode_t ROM_DMA_BuildDescriptorChain(ROM_DMA_HANDLE_T pHandle,
										 ROM_DMA_XFERDESC_CFG_T *pXferCfg,
										 ROM_DMA_DESC_T *pDesc,
										 ROM_DMA_DESC_T *pDescPrev)
{
	if (pXferCfg->dmaCh >= NUMDMACHANNELS) {
		return ERR_DMA_CHANNEL_NUMBER;
	}

#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->BuildDescriptorChain(pHandle, pXferCfg, pDesc, pDescPrev);
#else
	return dmaalt_api.BuildDescriptorChain(pHandle, pXferCfg, pDesc, pDescPrev);
#endif
}

/* Returns the number of items transferred on the last descriptor chain (spent status only) */
uint32_t ROM_DMA_GetTransferCount(ROM_DMA_HANDLE_T pHandle, ROM_DMA_DESC_T *pDesc)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->GetTransferCount(pHandle, pDesc);
#else
	return dmaalt_api.GetTransferCount(pHandle, pDesc);
#endif
}

/* Unstalls a descriptor chain that has been setup using the stallDesc option */
void ROM_DMA_UnstallDescriptorChain(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_DMAALT_API->UnstallDescriptorChain(pHandle, pQueue);
#else
	dmaalt_api.UnstallDescriptorChain(pHandle, pQueue);
#endif
}

/* Queues a transfer descriptor chain */
void ROM_DMA_QueueDescriptor(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, ROM_DMA_DESC_T *pDescChainHead)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_DMAALT_API->QueueDescriptor(pHandle, pQueue, pDescChainHead);
#else
	dmaalt_api.QueueDescriptor(pHandle, pQueue, pDescChainHead);
#endif
}

/* Returns current status of next descriptor to be popped from the queue */
ROM_DMA_DESC_STS_T ROM_DMA_GetQueuePopDescriptorStatus(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->GetQueuePopDescriptorStatus(pHandle, pQueue);
#else
	return dmaalt_api.GetQueuePopDescriptorStatus(pHandle, pQueue);
#endif
}

/* Pops (unqueues) an expired transfer descriptor from the queue - expired descriptors are in spent, error, or abort states */
ROM_DMA_DESC_T *ROM_DMA_UnQueueDescriptor(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->UnQueueDescriptor(pHandle, pQueue);
#else
	return dmaalt_api.UnQueueDescriptor(pHandle, pQueue);
#endif
}

/* Starts or restarts a queue at the next descriptor chain */
ErrorCode_t ROM_DMA_StartQueue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->StartQueue(pHandle, pQueue);
#else
	return dmaalt_api.StartQueue(pHandle, pQueue);
#endif
}

/* Stops DMA and aborts current descriptor chain being processed in queue */
ErrorCode_t ROM_DMA_StopQueue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->StopQueue(pHandle, pQueue);
#else
	return dmaalt_api.StopQueue(pHandle, pQueue);
#endif
}

/* Stops DMA and completely flushes a transfer queue, queue is completely reset */
void ROM_DMA_FlushQueue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_DMAALT_API->FlushQueue(pHandle, pQueue);
#else
	dmaalt_api.FlushQueue(pHandle, pQueue);
#endif
}

/* Returns the current queue state (ROM_DMA_QUEUE_STATES_T) */
uint8_t ROM_DMA_GetQueueState(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->GetQueueState(pHandle, pQueue);
#else
	return dmaalt_api.GetQueueState(pHandle, pQueue);
#endif
}

/* Forces a DMA transfer to trigger */
void ROM_DMA_ForceTrigger(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_DMAALT_API->ForceTrigger(pHandle, pQueue);
#else
	dmaalt_api.ForceTrigger(pHandle, pQueue);
#endif
}

/* DMA controller (interrupt) handler */
void ROM_DMA_DMAHandler(ROM_DMA_HANDLE_T pHandle)
{
#if defined(ROMDRIVERSV2_PRESENT)
	ROMAPI_DMAALT_API->DMAHandler(pHandle);
#else
	dmaalt_api.DMAHandler(pHandle);
#endif
}

/* Return the DMA controller ROM driver version */
uint16_t ROM_DMA_GetDriverVersion(void)
{
#if defined(ROMDRIVERSV2_PRESENT)
	return ROMAPI_DMAALT_API->GetDriverVersion();
#else
	return dmaalt_api.GetDriverVersion();
#endif
}
