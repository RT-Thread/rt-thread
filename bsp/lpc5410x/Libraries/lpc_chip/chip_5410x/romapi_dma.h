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

#ifndef __ROMAPI_DMA_H_
#define __ROMAPI_DMA_H_

#include "hw_dmaaltd.h"

/** @defgroup ROMAPI_DMA_WRAPPER CHIP: DMA controller ROM wrapper functions
 * @ingroup ROMAPI_5410X
 * @{
 */

/** @brief Minimum byte alignment value needed for the channel table.
 * Use 4 for 4 byte alginment, 8 for 8 byte alignment, etc. */
#define MINDMATABLEALIGN                512

/** @brief Number of DMA channels the DMA controller supports. */
#define NUMDMACHANNELS                  22

/**
 * @brief	Get memory size in bytes needed for DMA controller driver context
 * @return	Size in bytes needed for the ROM driver
 */
uint32_t ROM_DMA_GetMemSize(void);

/**
 * @brief	Initialize DMA controller
 * @param	mem		: Pointer to memory area used to driver context
 * @param	pInit	: Pointer to DMA controller init data
 * @return	NULL on error, or a pointer to the device context handle
 */
ROM_DMA_HANDLE_T ROM_DMA_Init(void *mem, ROM_DMA_INIT_T *pInit);

/**
 * @brief	Configures a DMA channel
 * @param	pHandle	: Pointer to driver context handle
 * @param	pCfg	: Pointer to DMA channel configuration structure
 * @param	dmaCh	: DMA channel to configure
 * @return	LPC_OK if no errors occured, or an error code
 */
ErrorCode_t ROM_DMA_SetupChannel(ROM_DMA_HANDLE_T pHandle, ROM_DMA_CHAN_CFG_T *pCfg, uint8_t dmaCh);

/**
 * @brief	Initialzies a transfer descriptor queue for a channel
 * @param	pHandle		: Pointer to driver context handle
 * @param	dmaCh		: DMA channel to configure
 * @param	pQueue		: Pointer to a queue to initialize
 * @return	LPC_OK if no errors occured, or an error code
 */
ErrorCode_t ROM_DMA_InitQueue(ROM_DMA_HANDLE_T pHandle, uint8_t dmaCh, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	Registers an DMA controller callback for a queue
 * @param	pHandle		: Pointer to driver context handle
 * @param	pQueue		: Pointer to a queue
 * @param	cbIndex	: Callback to register
 * @param	pCB		: Pointer to callback function
 * @return	Nothing
 */
void ROM_DMA_RegisterQueueCallback(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, uint32_t cbIndex, void *pCB);

/**
 * @brief	Builds a transfer descriptor chain from the passed settings
 * @param	pHandle		: Pointer to driver context handle
 * @param	pXferCfg	: Pointer to the transfer configuration
 * @param	pDesc		: Pointer to a descriptor to setup
 * @param	pDescPrev	: Pointer to previous descriptor that will link to this one
 * @return	LPC_OK if no errors occured, or an error code
 * @note	When creating a DMA descriptor chain (more than 1 link), chain the descriptors
 * together by passing the previous descriptor pointers for subsequenct calls to this function.
 */
ErrorCode_t ROM_DMA_BuildDescriptorChain(ROM_DMA_HANDLE_T pHandle,
										 ROM_DMA_XFERDESC_CFG_T *pXferCfg,
										 ROM_DMA_DESC_T *pDesc,
										 ROM_DMA_DESC_T *pDescPrev);

/**
 * @brief	Returns the number of items transferred on the last descriptor chain (spent status only)
 * @param	pHandle	: Pointer to driver context handle
 * @param	pDesc	: Pointer to a descriptor chain to count
 * @return	LPC_OK if no errors occured, or an error code
 */
uint32_t ROM_DMA_GetTransferCount(ROM_DMA_HANDLE_T pHandle, ROM_DMA_DESC_T *pDesc);

/**
 * @brief	Unstalls a descriptor chain that has been setup using the stallDesc option
 * @param	pHandle	: Pointer to driver context handle
 * @param	pQueue	: Pointer to a descriptor chain to unstall
 * @return	Nothing
 * @note	If a descriptor in a chain is setup with the stallDesc!=0 option in the
 * @ref ROM_DMA_XFERDESC_CFG_T setup structure, the descriptor will stall when it
 * is loaded. A stalled descriptor is ready to be processed, but won't start until a
 * call to this fucntion is made.
 */
void ROM_DMA_UnstallDescriptorChain(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	Queues a transfer descriptor chain
 * @param	pHandle			: Pointer to driver context handle
 * @param	pQueue			: Pointer to a queue
 * @param	pDescChainHead	: Pointer to the start of a descriptor chain to queue
 * @return	Nothing
 */
void ROM_DMA_QueueDescriptor(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, ROM_DMA_DESC_T *pDescChainHead);

/**
 * @brief	Returns current status of next descriptor to be popped from the queue
 * @param	pHandle	: Pointer to driver context handle
 * @param	pQueue	: Pointer to a queue
 * @return	Pointer to next pop descriptor, or ROM_DMA_DESC_STS_INVALID if no descriptors exist to be popped
 * @note	Only descriptors that are spent, aborted, or have an error can be popped. Calling ROM_DMA_StopQueue()
 * will abort the current descriptor in progress. This function returns the next descriptor that can be popped
 * regardless of status without actually popping it.
 */
ROM_DMA_DESC_STS_T ROM_DMA_GetQueuePopDescriptorStatus(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	Pops (unqueues) an expired transfer descriptor from the queue - expired descriptors are in spent, error, or abort states
 * @param	pHandle	: Pointer to driver context handle
 * @param	pQueue	: Pointer to a queue
 * @return	Pointer to popped descriptor, or NULL if no descriptors exist to be popped
 * @note	Only descriptors that are spent, aborted, or have an error can be popped. Calling ROM_DMA_StopQueue()
 * will abort the current descriptor in progress.
 */
ROM_DMA_DESC_T *ROM_DMA_UnQueueDescriptor(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	Starts or restarts a queue at the next descriptor chain
 * @param	pHandle	: Pointer to driver context handle
 * @param	pQueue	: Pointer to a queue
 * @return	LPC_OK if the queue is started or currently started, or an error code
 */
ErrorCode_t ROM_DMA_StartQueue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	Stops DMA and aborts current descriptor chain being processed in queue
 * @param	pHandle	: Pointer to driver context handle
 * @param	pQueue	: Pointer to a queue
 * @return	LPC_OK if the queue is stopped or already stopped, or an error code
 * @note	If multiple descriptor chains are queued up, this aborts the current one
 * being processed in queueing, ready, or busy states. All descriptors after the aborted
 * descriptor remain ready.
 */
ErrorCode_t ROM_DMA_StopQueue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	Stops DMA and completely flushes a transfer queue, queue is completely reset
 * @param	pHandle	: Pointer to driver context handle
 * @param	pQueue	: Pointer to a queue
 * @return	Nothing
 * @note	Flushes the entire queue of all descriptors and stops DMA.
 */
void ROM_DMA_FlushQueue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	Returns the current queue state (ROM_DMA_QUEUE_STATES_T)
 * @param	pHandle	: Pointer to driver context handle
 * @param	pQueue	: Pointer to a queue
 * @return	Current queue status (ROM_DMA_QUEUE_STATES_T)
 */
uint8_t ROM_DMA_GetQueueState(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	Forces a DMA transfer to trigger
 * @param	pHandle	: Pointer to driver context handle
 * @param	pQueue	: Pointer to a queue
 * @return	Nothing
 */
void ROM_DMA_ForceTrigger(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

/**
 * @brief	DMA controller (interrupt) handler
 * @param	pHandle	: Pointer to driver context handle
 * @return	Nothing
 * @note	This function should be called from the DMA interrupt handler.
 */
void ROM_DMA_DMAHandler(ROM_DMA_HANDLE_T pHandle);

/**
 * @brief	Return the DMA controller ROM driver version
 * @return	Driver version number
 * @note	The returned driver version number consists of a major and minor
 * number, with the minor number in the lower 8 bits and the major number in
 * the upper 8 bits.
 */
uint16_t ROM_DMA_GetDriverVersion(void);

/**
 * @}
 */

#endif /* __ROMAPI_DMA_H_ */
