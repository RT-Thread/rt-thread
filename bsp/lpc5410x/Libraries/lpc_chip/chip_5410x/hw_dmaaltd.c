/*
 * @brief DMA controller ROM API declarations and functions
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

#include <stdint.h>
#include <string.h>
#include "hw_dmaaltd.h"

#define DRVVERSION 0x0100

typedef PRE_PACK struct POST_PACK {
	uint32_t            xfercfg;			/*!< DMA Configuration register */
	uint32_t            src;				/*!< DMA source address */
	uint32_t            dest;				/*!< DMA destination address */
	ROM_DMA_DESC_T      *pNextLink;			/*!< Pointer to next descriptor link in a chain, NULL to end */
} ROM_DMA_PRVXFERDESC_T;

/* Private data structure used for the DMA controller driver, holds the driver and
   peripheral context */
typedef struct {
	void                        *pUserData;		/*!< Pointer to user data used by driver instance, use NULL if not used */
	LPC_DMA_T                   *base;			/*!< Base address of DMA controller to use */
	ROM_DMA_PRVXFERDESC_T       *sramBase;		/*!< SRAM descriptor table (all channels) */
	ROM_DMA_QUEUE_T             *pQueueHead;	/*!< Pointer to linked list of queue descriptors */
} DMA_DATACONTEXT_T;

static const uint8_t mskAlign[3] = {0x0, 0x1, 0x3};
static const uint8_t widthBytes[3] = {0x1, 0x2, 0x4};

#define  _dma_ch_int_enable(p, ch) ((p)->DMACOMMON[0].INTENSET = (1 << (ch)))	/* Enable interrupts for a channel */
#define  _dma_ch_int_disable(p, ch) ((p)->DMACOMMON[0].INTENCLR = (1 << (ch)))	/* Disable interrupts for a channel */
#define  _dma_ch_enable(p, ch) ((p)->DMACOMMON[0].ENABLESET = (1 << (ch)))	/* Enable a channel */
#define  _dma_ch_disable(p, ch) ((p)->DMACOMMON[0].ENABLECLR = (1 << (ch)))	/* Disable a channel */

static void _dma_abort_ch(LPC_DMA_T *pDMA, uint8_t dmaCh)
{
	_dma_ch_disable(pDMA, dmaCh);

	/* Wait for channel to go unbusy */
	while ((pDMA->DMACOMMON[0].BUSY & (1 << dmaCh)) != 0) {}

	/* Abort */
	pDMA->DMACOMMON[0].ABORT = (1 << dmaCh);
}

static void _dma_start_desc_chain(DMA_DATACONTEXT_T *pDrv, uint8_t dmaCh, ROM_DMA_DESC_T *pDesc)
{
	/* Switch to busy state */
	pDesc->status = ROM_DMA_DESC_STS_BUSY;

	/* Move transfer descriptor to DMA table */
	pDrv->sramBase[dmaCh].xfercfg = pDesc->xfercfg;
	pDrv->sramBase[dmaCh].src = pDesc->src;
	pDrv->sramBase[dmaCh].dest = pDesc->dest;
	pDrv->sramBase[dmaCh].pNextLink = (ROM_DMA_DESC_T *) pDesc->pNextLink;

	/* Start transfer */
	pDrv->base->DMACH[dmaCh].XFERCFG = pDesc->xfercfg;
}

// **********************************************************
uint32_t dmaalt_get_mem_size(void)
{
	return sizeof(DMA_DATACONTEXT_T);
}

ROM_DMA_HANDLE_T dmaalt_init(void *mem, const ROM_DMA_INIT_T *pInit)
{
	DMA_DATACONTEXT_T *pDrv;

	/* Verify alignment is at least 4 bytes */
	if (((uint32_t) mem & 0x3) != 0) {
		return NULL;
	}

	pDrv = (DMA_DATACONTEXT_T *) mem;
	memset(pDrv, 0, sizeof(DMA_DATACONTEXT_T));

	/* Save pointer to user data */
	pDrv->pUserData = pInit->pUserData;
	pDrv->base = (LPC_DMA_T *) pInit->base;
	pDrv->sramBase = (ROM_DMA_PRVXFERDESC_T *) pInit->sramBase;

	/* Enable DMA controller */
	pDrv->base->CTRL = 1;
	pDrv->base->SRAMBASE = (uint32_t) pInit->sramBase;

	return (ROM_DMA_HANDLE_T) pDrv;
}

ErrorCode_t dmaalt_setup_channel(ROM_DMA_HANDLE_T pHandle, ROM_DMA_CHAN_CFG_T *pCfg, uint8_t dmaCh)
{
	uint32_t cfg;
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;

	/* Parameter checks */
	if ((pCfg->burstSize > (uint32_t) ROM_DMA_BURSTPOWER_1024)  || (pCfg->channelPrio > 7)) {
		return ERR_DMA_PARAM;
	}

	/* Enable DMA channel, clear any errors, enable interrupts */
	pDrv->base->DMACOMMON[0].ENABLECLR = (1 << dmaCh);
	pDrv->base->DMACOMMON[0].ERRINT = (1 << dmaCh);
	pDrv->base->DMACOMMON[0].INTA = (1 << dmaCh);
	pDrv->base->DMACOMMON[0].INTB = (1 << dmaCh);

	/* Basic DMA configuration */
	if (pCfg->periphReq) {
		cfg = DMA_CFG_PERIPHREQEN;
	}
	else {
		/* Hardware triggering */
		cfg = DMA_CFG_HWTRIGEN;
		cfg |= (pCfg->triggerPolHi << 4) |  (pCfg->triggerLevel << 5) | (pCfg->triggerBurst << 6);
	}
	cfg |= (pCfg->burstSize << 8) | (pCfg->srcBurstWrap << 14) | (pCfg->dstBurstWrap << 15) | (pCfg->channelPrio << 16);
	pDrv->base->DMACH[dmaCh].CFG = cfg;

	return LPC_OK;
}

ErrorCode_t dmaalt_init_queue(ROM_DMA_HANDLE_T pHandle, uint8_t dmaCh, ROM_DMA_QUEUE_T *pQueue)
{
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;

	/* Check queue structure alignment */
	if (((uint32_t) pQueue & 0x3) != 0) {
		/* Not aligned at 4 bytes, error */
		return ERR_DMA_NOT_ALIGNMENT;
	}

	memset(pQueue, 0, sizeof(ROM_DMA_QUEUE_T));

	/* Save DMA channekl for this queue */
	pQueue->dmaCh = dmaCh;

	/* Append to existing queue */
	if (pDrv->pQueueHead) {
		pQueue->pQueueHead = (struct ROM_DMA_QUEUE *) pDrv->pQueueHead;
	}
	pDrv->pQueueHead = pQueue;
	pQueue->queueSt = (uint8_t) ROM_QUEUE_ST_IDLE;

	return LPC_OK;
}

void dmaalt_register_queue_callback(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, uint32_t cbIndex, void *pCB)
{
	switch (cbIndex) {
	case ROM_DMA_XFERCOMPLETE_CB:
		pQueue->dmaCompCB = (dmaTransferCompleteCB) pCB;
		break;

	case ROM_DMA_XFERDESCCOMPLETE_CB:
		pQueue->dmaDescCompCB = (dmaTransferDescCompleteCB) pCB;
		break;

	case ROM_DMA_XFERERROR_CB:
		pQueue->dmaErrorCB = (dmaTransferErrorCB) pCB;
		break;
	}
}

ErrorCode_t dmaalt_build_descriptor_chain(ROM_DMA_HANDLE_T pHandle,
										  ROM_DMA_XFERDESC_CFG_T *pXferCfg,
										  ROM_DMA_DESC_T *pDesc,
										  ROM_DMA_DESC_T *pDescPrev)
{
	uint32_t cfg, xfercnt, burstSize;
	uint8_t srcWrap, destWrap;
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;

	/* Parameter checks */
	if (pDesc == NULL) {
		return ERR_DMA_PARAM;
	}

	/* Passed descriptor must be correctly aligned */
	if (((uint32_t) pDesc & 0xF) != 0) {
		return ERR_DMA_NOT_ALIGNMENT;
	}

	/* Parameter checks */
	if (pXferCfg->width > (uint8_t) ROM_DMA_WIDTH_4) {
		return ERR_DMA_PARAM;
	}
	if ((pXferCfg->srcInc > (uint8_t) ROM_DMA_ADDRINC_4X) ||
		(pXferCfg->dstInc > (uint8_t) ROM_DMA_ADDRINC_4X)) {
		return ERR_DMA_PARAM;
	}
	if ((pXferCfg->xferCount < 1) || (pXferCfg->xferCount > 1024)) {
		return ERR_DMA_PARAM;
	}
	xfercnt = pXferCfg->xferCount - 1;	/* Adjust for use with DMA */

	/* Check source and destination address alignment */
	if (((uint32_t) pXferCfg->src & mskAlign[pXferCfg->width]) != 0) {
		return ERR_DMA_NOT_ALIGNMENT;
	}
	if (((uint32_t) pXferCfg->dest & mskAlign[pXferCfg->width]) != 0) {
		return ERR_DMA_NOT_ALIGNMENT;
	}

	/* Get source and destination wrap states for the channel */
	cfg = pDrv->base->DMACH[pXferCfg->dmaCh].CFG;

	/* Get burst size in datum count, used for wrap end address, offset by
	   (-1) for end address computation	*/
	burstSize = (1 << ((cfg >> 8) & 0xF)) - 1;

	/* Setup source transfer address */
	if (pXferCfg->srcInc == ROM_DMA_ADDRINC_0X) {
		/* No address increment - even with burst - so source address doesn't need
		   to be adjusted */
		pDesc->src = (uint32_t) pXferCfg->src;
	}
	else {
		srcWrap = (uint8_t) ((cfg & (1 << 14)) != 0);
		if (srcWrap) {
			/* Wrap enabled - compute end address based on burst size and datum width */
			pDesc->src = (uint32_t) pXferCfg->src + ((uint32_t) widthBytes[pXferCfg->width] *
													 burstSize * (1 << ((uint32_t) pXferCfg->srcInc - 1)));
		}
		else {
			/* No wrap - compute end address based on transfer size and datum width */
			pDesc->src = (uint32_t) pXferCfg->src + ((uint32_t) widthBytes[pXferCfg->width] *
													 xfercnt * (1 << ((uint32_t) pXferCfg->srcInc - 1)));
		}
	}

	/* Setup destination transfer address */
	if (pXferCfg->dstInc == ROM_DMA_ADDRINC_0X) {
		/* No address increment - even with burst - so destination address doesn't need
		   to be adjusted */
		pDesc->dest = (uint32_t) pXferCfg->dest;
	}
	else {
		destWrap = (uint8_t) ((cfg & (1 << 15)) != 0);
		if (destWrap) {
			/* Wrap enabled - compute end address based on burst size and datum width */
			pDesc->dest = (uint32_t) pXferCfg->dest + ((uint32_t) widthBytes[pXferCfg->width] *
													   burstSize * (1 << ((uint32_t) pXferCfg->dstInc - 1)));
		}
		else {
			/* No wrap - compute end address based on transfer size and datum width */
			pDesc->dest = (uint32_t) pXferCfg->dest + ((uint32_t) widthBytes[pXferCfg->width] *
													   xfercnt * (1 << ((uint32_t) pXferCfg->dstInc - 1)));
		}
	}

	/* Save pointer to user data context */
	pDesc->pUserData = pXferCfg->pUserData;

	/* Is the descriptor linked from a previous descriptor? */
	if (pDescPrev) {
		pDescPrev->pNextLink = (struct ROM_DMA_DESC *) pDesc;

		if (pXferCfg->enabCirc == 0) {
			pDescPrev->xfercfg &= ~(1 << 5);/* Disables INTB on previous descriptor link */
			pDescPrev->xfercfg |= (1 << 1);	/* Reload on chained links */
		}
	}
	else {
		pDesc->pNextLink = NULL;
	}

	/* NULL out next chain descriptor pointers. The next chain descriptor is
	   managed by the queue function, while the next link descriptor indicates the end
	   of a chain. */
	pDesc->pNextChain = NULL;

	/* Current descriptor status is queueing. Status only applies to the first descriptor
	   in a chain. */
	pDesc->status = ROM_DMA_DESC_STS_QUEUEING;
	pDesc->savedXferSize = pXferCfg->xferCount;

	/* Normalize parameters that are multibit to single bit */
	pXferCfg->swTrig = (pXferCfg->swTrig != 0);
	pXferCfg->clrTrig = (pXferCfg->clrTrig != 0);
	pXferCfg->fireDescCB = (pXferCfg->fireDescCB != 0);

	if (pXferCfg->enabCirc) {
		cfg = (1 << 1);	/* Reload on chained links */
	}
	else {
		cfg = (1 << 5);	/* INTB support for completion and next descriptor */
	}
	if (pXferCfg->stallDesc == 0) {
		cfg |= 0x1;	/* CFGVALID */
	}

	/* Setup transfer configuration */
	cfg |= (pXferCfg->swTrig << 2) | (pXferCfg->clrTrig << 3) |
		   (pXferCfg->fireDescCB << 4) | (pXferCfg->width << 8) | (pXferCfg->srcInc << 12) |
		   (pXferCfg->dstInc << 14);
	cfg |= (xfercnt << 16);
	pDesc->xfercfg = cfg;

	return LPC_OK;
}

uint32_t dmaalt_get_transfer_count(ROM_DMA_HANDLE_T pHandle, ROM_DMA_DESC_T *pDesc)
{
	uint32_t dataCount = 0;

	/* Count is only valid if descriptor is used */
	while (pDesc != NULL) {
		if (pDesc->status == ROM_DMA_DESC_STS_SPENT) {
			dataCount += (uint32_t) pDesc->savedXferSize;
		}

		pDesc = (ROM_DMA_DESC_T *) pDesc->pNextLink;
	}

	return dataCount;
}

void dmaalt_unstall_descriptor_chain(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;

	pDrv->base->DMACOMMON[0].SETVALID = (1 << pQueue->dmaCh);
}

void dmaalt_queue_descriptor(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, ROM_DMA_DESC_T *pDescChainHead)
{
	/* Add the link to the passed descriptor to the end of the queue */
	if (pQueue->pDescEnd != NULL) {
		pQueue->pDescEnd->pNextChain = (struct ROM_DMA_DESC *) pDescChainHead;
	}
	pQueue->pDescEnd = pDescChainHead;

	/* Next descriptor in queue */
	if (pQueue->pDescNext == NULL) {
		pQueue->pDescNext = pDescChainHead;
	}

	/* Descriptor is ready */
	pDescChainHead->status = ROM_DMA_DESC_STS_READY;
}

ROM_DMA_DESC_STS_T dmaalt_get_queue_pop_descriptor_status(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
	if (pQueue->pDescPop) {
		return (ROM_DMA_DESC_STS_T) pQueue->pDescPop->status;
	}

	return ROM_DMA_DESC_STS_INVALID;
}

ROM_DMA_DESC_T *dmaalt_unqueue_descriptor(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
	ROM_DMA_DESC_T *pDesc = NULL;

	/* Get current queue pop descriptor */
	if (pQueue->pDescPop) {
		/* Only expired (spent, error, or aborted descriptors can be unqueued. Use StopQueue to halt all
		   descriptors queued. */
		if (pQueue->pDescPop->status >= ROM_DMA_DESC_STS_SPENT) {
			pDesc = (ROM_DMA_DESC_T *) pQueue->pDescPop;
			pQueue->pDescPop = (ROM_DMA_DESC_T *) pQueue->pDescPop->pNextChain;
		}
	}

	return pDesc;
}

ErrorCode_t dmaalt_start_queue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;

	/* Is DMA already running? No need to restart */
	if ((pDrv->base->DMACOMMON[0].ACTIVE & (1 << pQueue->dmaCh)) != 0) {
		return LPC_OK;
	}

	/* Is queue empty? */
	if (pQueue->pDescNext == NULL) {
		return ERR_DMA_QUEUE_EMPTY;
	}

	/* Does the queue currently have a descriptor in it? */
	if (pQueue->pDescNext) {
		/* Is current descriptor chain ready? */
		if (pQueue->pDescNext->status == ROM_DMA_DESC_STS_READY) {
			/* Queue is now running */
			pQueue->queueSt = (uint8_t) ROM_QUEUE_ST_RUNNING;

			/* Enable this channel */
			_dma_ch_enable(pDrv->base, pQueue->dmaCh);
			_dma_ch_int_enable(pDrv->base, pQueue->dmaCh);

			_dma_start_desc_chain(pDrv, pQueue->dmaCh, pQueue->pDescNext);
		}
	}

	return LPC_OK;
}

ErrorCode_t dmaalt_stop_queue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;
	ErrorCode_t error = LPC_OK;

	/* Disable interrupts for this channel */
	_dma_ch_int_disable(pDrv->base, pQueue->dmaCh);

	/* If queue is empty, no need to stop */
	if (pQueue->pDescNext == NULL) {
		return LPC_OK;
	}

	/* If current transfer is queued or ready, then switch it to aborted status
	   and call completion callback if needed. */
	if (pQueue->pDescNext->status == ROM_DMA_DESC_STS_BUSY) {
		/* Abort transfer */
		_dma_abort_ch(pDrv->base, pQueue->dmaCh);
	}
	else if (!((pQueue->pDescNext->status == ROM_DMA_DESC_STS_QUEUEING) ||
			   (pQueue->pDescNext->status == ROM_DMA_DESC_STS_READY))) {
		/* Other statuses are not legal for a queued descriptor */
		error = ERR_DMA_GENERAL;
	}

	/* Unlatch interrupts */
	pDrv->base->DMACOMMON[0].ERRINT = (1 << pQueue->dmaCh);
	pDrv->base->DMACOMMON[0].INTA = (1 << pQueue->dmaCh);
	pDrv->base->DMACOMMON[0].INTB = (1 << pQueue->dmaCh);

	/* Call completion callback to indicate abort state */
	pQueue->pDescNext->status = ROM_DMA_DESC_STS_ABORT;
	if (pQueue->dmaCompCB) {
		pQueue->dmaCompCB(pHandle, (struct ROM_DMA_QUEUE *) pQueue, pQueue->pDescNext);
	}

	/* Increment to next available descriptor since this one was aborted */
	pQueue->pDescNext = (ROM_DMA_DESC_T *) pQueue->pDescNext->pNextChain;

	/* Queue is now idle */
	pQueue->queueSt = (uint8_t) ROM_QUEUE_ST_IDLE;

	return error;
}

void dmaalt_flush_queue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;

	/* Disable interrupts for this channel */
	_dma_ch_int_disable(pDrv->base, pQueue->dmaCh);

	/* Abort transfer */
	_dma_abort_ch(pDrv->base, pQueue->dmaCh);

	/* Unlatch interrupts */
	pDrv->base->DMACOMMON[0].ERRINT = (1 << pQueue->dmaCh);
	pDrv->base->DMACOMMON[0].INTA = (1 << pQueue->dmaCh);
	pDrv->base->DMACOMMON[0].INTB = (1 << pQueue->dmaCh);

	/* No callbacks on abort, all descriptors flushed */
	pQueue->pDescEnd = pQueue->pDescNext = pQueue->pDescPop = NULL;

	/* Queue is now idle */
	pQueue->queueSt = (uint8_t) ROM_QUEUE_ST_IDLE;
}

uint8_t dmaalt_get_queue_state(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
	return pQueue->queueSt;
}

void dmaalt_force_trigger(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue)
{
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;

	pDrv->base->DMACOMMON[0].SETTRIG = (1 << pQueue->dmaCh);
}

// Otime = "optimize for speed of code execution"
// ...add this pragma 1 line above the interrupt service routine function.
void dmaalt_handler(ROM_DMA_HANDLE_T pHandle)
{
	uint32_t err, inta, intb, all, dmaChMask;
	ROM_DMA_QUEUE_T *pQueue;
	ROM_DMA_DESC_T *pDesc;
	DMA_DATACONTEXT_T *pDrv = (DMA_DATACONTEXT_T *) pHandle;
	uint8_t nextChain = 0;

	/* DMA interrupt fires on one of three possible events:
	   1) ERROR : A DMA error has occured
	      Calls error callback and stops queue
	   2) INTA on descriptor completion
	      Calls descriptor completed callback
	   3) INTB on descriptor chain completion
	      Calls descriptor chain completion callback */

	/* Loop through all enabled DMA channels */
	pQueue = pDrv->pQueueHead;
	err = pDrv->base->DMACOMMON[0].ERRINT;
	inta = pDrv->base->DMACOMMON[0].INTA;
	intb = pDrv->base->DMACOMMON[0].INTB;
	all = err | inta | intb;
	while (pQueue) {
		dmaChMask = (1 << pQueue->dmaCh);
		if ((all & dmaChMask) != 0) {
			/* DMA interrupt fire for this channel */
			if ((err & dmaChMask) != 0) {
				/* Abort current descriptor */
				_dma_ch_int_disable(pDrv->base, pQueue->dmaCh);
				_dma_abort_ch(pDrv->base, pQueue->dmaCh);

				/* Error interrupt, clear */
				pDrv->base->DMACOMMON[0].ERRINT = dmaChMask;
				pDrv->base->DMACOMMON[0].INTA = dmaChMask;
				pDrv->base->DMACOMMON[0].INTB = dmaChMask;

				/* Update status to error */
				pQueue->pDescNext->status = ROM_DMA_DESC_STS_ERROR;
				pQueue->queueSt = (uint8_t) ROM_QUEUE_ST_ERROR;

				/* Call error callback for channel */
				if (pQueue->dmaErrorCB) {
					pQueue->dmaErrorCB(pHandle, (struct ROM_DMA_QUEUE *) pQueue, pQueue->pDescNext);
				}

				nextChain = 1;
			}

			/* Interrupt A is used for user defined interrupt tied to a descriptor */
			if ((inta & dmaChMask) != 0) {
				pDrv->base->DMACOMMON[0].INTA = dmaChMask;

				/* Call transfer descriptor completion for channel */
				if (pQueue->dmaDescCompCB) {
					pQueue->dmaDescCompCB(pHandle, (struct ROM_DMA_QUEUE *) pQueue, pQueue->pDescNext);
				}
			}

			/* Interrupt B is used for user transfer descriptor chain completion */
			if ((intb & dmaChMask) != 0) {
				pDrv->base->DMACOMMON[0].INTB = dmaChMask;

				/* Update status to spent/complete */
				pQueue->pDescNext->status = ROM_DMA_DESC_STS_SPENT;

				/* Start the next descriptor chain? */
				pDesc = (ROM_DMA_DESC_T *) pQueue->pDescNext->pNextChain;
				if ((pDesc) && (pDesc->status == ROM_DMA_DESC_STS_READY)) {
					/* A queued descriptor is available and ready, so start it */
					_dma_start_desc_chain(pDrv, pQueue->dmaCh, pDesc);
				}

				/* Call transfer descriptor completion for channel */
				if (pQueue->dmaCompCB) {
					pQueue->dmaCompCB(pHandle, (struct ROM_DMA_QUEUE *) pQueue, pQueue->pDescNext);
				}

				nextChain = 1;
			}

			if (nextChain) {
				/* Need to save in pop queue? */
				if (pQueue->pDescPop == NULL) {
					pQueue->pDescPop = pQueue->pDescNext;
				}

				/* Advance to next queued descriptor */
				pQueue->pDescNext = (ROM_DMA_DESC_T *) pQueue->pDescNext->pNextChain;
				if (pQueue->pDescNext == NULL) {
					/* No more descriptors */
					pQueue->pDescEnd = NULL;
				}
			}

			all &= ~dmaChMask;
		}

		/* Next queue */
		pQueue = (ROM_DMA_QUEUE_T *) pQueue->pQueueHead;
	}

	if (all) {
		/* Unexpected interrupts, clear and disable */
		pDrv->base->DMACOMMON[0].ENABLECLR = all;
		pDrv->base->DMACOMMON[0].INTENCLR = all;
		pDrv->base->DMACOMMON[0].ERRINT = all;
		pDrv->base->DMACOMMON[0].INTA = all;
		pDrv->base->DMACOMMON[0].INTB = all;
	}
}

uint32_t dmaalt_get_driver_version(void)
{
	return DRVVERSION;
}

// *********************************************************
