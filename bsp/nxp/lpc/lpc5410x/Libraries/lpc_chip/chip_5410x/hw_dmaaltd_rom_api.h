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

#ifndef __HW_DMAALTD_ROM_API_H
#define __HW_DMAALTD_ROM_API_H

#include "stdint.h"		// added to define uint32_t, etc.
#include "error.h"
#include "packing.h"
#include "hw_dmaaltd_regs.h"

/** @defgroup ROMAPI_DMAALT DMA controller ROM driver functions and definitions
 * @ingroup ROMAPI_DMA_WRAPPER
 * @{
 */

/** @brief DMA controller handle type */
typedef void *ROM_DMA_HANDLE_T;

/** @brief User context conversion macro
 * Macro used to extract the user defined data pointer from a DMA controller
 * handle context.<br>
 * To get a user context, simple use the macro on the drivers handle:
 * void *pUserData = (void *) ROM_DMA_HANDLE_TOUDATA(driverHandle);
 */
#define ROM_DMA_HANDLE_TOUDATA(p)           (void *) (*(uint32_t *) p)

/** @brief DMA channel mapping
 * Each channel is mapped to an individual peripheral and direction or a DMA
 * imput mux trigger.
 */
typedef enum {
	ROM_DMAREQ_UART0_RX = 0,		/*!< UART00 receive DMA channel */
	ROM_DMA_CH0 = ROM_DMAREQ_UART0_RX,
	ROM_DMAREQ_UART0_TX,			/*!< UART0 transmit DMA channel */
	ROM_DMA_CH1 = ROM_DMAREQ_UART0_TX,
	ROM_DMAREQ_UART1_RX,			/*!< UART1 receive DMA channel */
	ROM_DMA_CH2 = ROM_DMAREQ_UART1_RX,
	ROM_DMAREQ_UART1_TX,			/*!< UART1 transmit DMA channel */
	ROM_DMA_CH3 = ROM_DMAREQ_UART1_TX,
	ROM_DMAREQ_UART2_RX,			/*!< UART2 receive DMA channel */
	ROM_DMA_CH4 = ROM_DMAREQ_UART2_RX,
	ROM_DMAREQ_UART2_TX,			/*!< UART2 transmit DMA channel */
	ROM_DMA_CH5 = ROM_DMAREQ_UART2_TX,
	ROM_DMAREQ_UART3_RX,			/*!< UART3 receive DMA channel */
	ROM_DMA_CH6 = ROM_DMAREQ_UART3_RX,
	ROM_DMAREQ_UART3_TX,			/*!< UART3 transmit DMA channel */
	ROM_DMA_CH7 = ROM_DMAREQ_UART3_TX,
	ROM_DMAREQ_SPI0_RX,				/*!< SPI0 receive DMA channel */
	ROM_DMA_CH8 = ROM_DMAREQ_SPI0_RX,
	ROM_DMAREQ_SPI0_TX,				/*!< SPI0 transmit DMA channel */
	ROM_DMA_CH9 = ROM_DMAREQ_SPI0_TX,
	ROM_DMAREQ_SPI1_RX,				/*!< SPI1 receive DMA channel */
	ROM_DMA_CH10 = ROM_DMAREQ_SPI1_RX,
	ROM_DMAREQ_SPI1_TX,				/*!< SPI1 transmit DMA channel */
	ROM_DMA_CH11 = ROM_DMAREQ_SPI1_TX,
	ROM_DMAREQ_I2C0_SLAVE,			/*!< I2C0 Slave DMA channel */
	ROM_DMA_CH12 = ROM_DMAREQ_I2C0_SLAVE,
	ROM_DMAREQ_I2C0_MASTER,			/*!< I2C0 Master DMA channel */
	ROM_DMA_CH13 = ROM_DMAREQ_I2C0_MASTER,
	ROM_DMAREQ_I2C1_SLAVE,			/*!< I2C1 Slave DMA channel */
	ROM_DMA_CH14 = ROM_DMAREQ_I2C1_SLAVE,
	ROM_DMAREQ_I2C1_MASTER,			/*!< I2C1 Master DMA channel */
	ROM_DMA_CH15 = ROM_DMAREQ_I2C1_MASTER,
	ROM_DMAREQ_I2C2_SLAVE,			/*!< I2C2 Slave DMA channel */
	ROM_DMA_CH16 = ROM_DMAREQ_I2C2_SLAVE,
	ROM_DMAREQ_I2C2_MASTER,			/*!< I2C2 Master DMA channel */
	ROM_DMA_CH17 = ROM_DMAREQ_I2C2_MASTER,
	ROM_DMAREQ_I2C0_MONITOR,		/*!< I2C0 Monitor DMA channel */
	ROM_DMA_CH18 = ROM_DMAREQ_I2C0_MONITOR,
	ROM_DMAREQ_I2C1_MONITOR,		/*!< I2C1 Monitor DMA channel */
	ROM_DMA_CH19 = ROM_DMAREQ_I2C1_MONITOR,
	ROM_DMAREQ_I2C2_MONITOR,		/*!< I2C2 Monitor DMA channel */
	ROM_DMA_CH20 = ROM_DMAREQ_I2C2_MONITOR,
	ROM_RESERVED_SPARE_DMA,
	ROM_DMAREG_CH21 = ROM_RESERVED_SPARE_DMA,
	ROM_DMALASTCHANNEL = ROM_RESERVED_SPARE_DMA,
} ROM_DMA_CHID_T;

/** @brief Descriptor status tags */
typedef enum {
	ROM_DMA_DESC_STS_INVALID,		/*!< DMA descriptor is invalid */
	ROM_DMA_DESC_STS_QUEUEING,		/*!< DMA descriptor is being queued */
	ROM_DMA_DESC_STS_READY,			/*!< DMA descriptor ready status */
	ROM_DMA_DESC_STS_BUSY,			/*!< DMA descriptor busy status */
	ROM_DMA_DESC_STS_SPENT,			/*!< DMA descriptor spent (complete) status */
	ROM_DMA_DESC_STS_ABORT,			/*!< DMA descriptor aborted status */
	ROM_DMA_DESC_STS_ERROR,			/*!< DMA descriptor error status */
} ROM_DMA_DESC_STS_T;

/** @brief DMA transfer descriptor - must be 16 byte aligned */
struct ROM_DMA_DESC;

typedef PRE_PACK struct POST_PACK {
	uint32_t                xfercfg;		/*!< DMA Configuration register */
	uint32_t                src;			/*!< DMA source address */
	uint32_t                dest;			/*!< DMA destination address */
	struct ROM_DMA_DESC     *pNextLink;		/*!< Pointer to next descriptor link in a chain, NULL to end */

	struct ROM_DMA_DESC     *pNextChain;	/*!< Pointer to next descriptor chain to process, NULL to end */

	uint32_t                status;			/*!< Descriptor's current status (ROM_DMA_DESC_STS_T) */
	void                    *pUserData;		/*!< Pointer to user data for the descriptor (chain) */
	uint16_t                savedXferSize;	/*!< Saved transfer size for this descriptor */
	uint16_t                reserved1[1];	/*!< Needed to maintain alignment at 16 bytes */
} ROM_DMA_DESC_T;

/** @brief DMA controller callback IDs */
typedef enum {
	ROM_DMA_XFERCOMPLETE_CB = 0,			/*!< Callback ID for DMA transfer descriptor chain complete */
	ROM_DMA_XFERDESCCOMPLETE_CB,			/*!< Callback ID for DMA transfer descriptor complete */
	ROM_DMA_XFERERROR_CB,					/*!< Callback ID for DMA transfer error occurance */
} ROM_DMA_CALLBACK_T;

struct ROM_DMA_QUEUE;

/** @brief DMA controller transfer descriptor chain complete callback
 * This callback is called from the DMA controller handler when the DMA controller
 * has completed a complete transfer descriptor chain, the chain has stopped due to an error,
 * or the chain has been aborted. The callback is only called if it has been registered.
 */
typedef void (*dmaTransferCompleteCB)(ROM_DMA_HANDLE_T spimHandle, struct ROM_DMA_QUEUE *pQueue,
									  ROM_DMA_DESC_T *pTranDesc);

/** @brief DMA controller transfer descriptor complete callback
 * This callback is called from the DMA controller handler when the DMA controller
 * has completed a transfer descriptor. The callback is only called if it has been registered
 * and the transfer descriptor has been enabled for interrupt operation with the fireDescCB option.
 */
typedef void (*dmaTransferDescCompleteCB)(ROM_DMA_HANDLE_T spimHandle, struct ROM_DMA_QUEUE *pQueue,
										  ROM_DMA_DESC_T *pTranDesc);

/** @brief DMA controller transfer descriptor error callback
 * This callback is called from the DMA controller handler when and error has occured in the
 * DMA transfer. The callback is only called if it has been registered and the transfer descriptor has
 * been enabled for interrupt operation.
 */
typedef void (*dmaTransferErrorCB)(ROM_DMA_HANDLE_T spimHandle, struct ROM_DMA_QUEUE *pQueue, ROM_DMA_DESC_T *pTranDesc);

/** @brief DMA transfer queue - must be 16 byte aligned */
typedef PRE_PACK struct POST_PACK {
	dmaTransferCompleteCB       dmaCompCB;			/*!< Transfer descriptor chain completion callback */
	dmaTransferDescCompleteCB   dmaDescCompCB;		/*!< Transfer descriptor completion callback */
	dmaTransferErrorCB          dmaErrorCB;			/*!< Transfer error callback */
	ROM_DMA_DESC_T              *pDescEnd;			/*!< Pointer to last descriptor chain */
	ROM_DMA_DESC_T              *pDescNext;			/*!< Pointer to next descriptor chain to process */
	ROM_DMA_DESC_T              *pDescPop;			/*!< Pointer to first descriptor chain */
	struct ROM_DMA_QUEUE        *pQueueHead;		/*!< Pointer to next queue descriptor */

	uint8_t                     dmaCh;				/*!< DMA channel mapped to this queue (ROM_DMA_CHID_T) */
	uint8_t                     queueSt;			/*!< Current state of this queue (ROM_DMA_QUEUE_STATES_T) */
	uint8_t                     reserved[2];
} ROM_DMA_QUEUE_T;

/** @brief DMA burst transfer sizing
 */
typedef enum {
	ROM_DMA_BURSTPOWER_1 = 0,		/*!< Set DMA burst size to 1 data transfer */
	ROM_DMA_BURSTPOWER_2,			/*!< Set DMA burst size to 2 data transfer */
	ROM_DMA_BURSTPOWER_4,			/*!< Set DMA burst size to 4 data transfer */
	ROM_DMA_BURSTPOWER_8,			/*!< Set DMA burst size to 8 data transfer */
	ROM_DMA_BURSTPOWER_16,			/*!< Set DMA burst size to 16 data transfer */
	ROM_DMA_BURSTPOWER_32,			/*!< Set DMA burst size to 32 data transfer */
	ROM_DMA_BURSTPOWER_64,			/*!< Set DMA burst size to 64 data transfer */
	ROM_DMA_BURSTPOWER_128,			/*!< Set DMA burst size to 128 data transfer */
	ROM_DMA_BURSTPOWER_256,			/*!< Set DMA burst size to 256 data transfer */
	ROM_DMA_BURSTPOWER_512,			/*!< Set DMA burst size to 512 data transfer */
	ROM_DMA_BURSTPOWER_1024			/*!< Set DMA burst size to 1024 data transfer */
} ROM_DMA_BURSTPOWER_T;

/** @brief DMA transfer channel setup structure (use this structure as const if possible) */
typedef PRE_PACK struct POST_PACK {
	uint32_t                periphReq       : 1;	/*!< 0 = hardware trigger request, !0 = peripheral request */
	uint32_t                triggerPolHi    : 1;	/*!< 0 = low trigger polarity, !0 = high polarity, only valid if triggerReq == 0 */
	uint32_t                triggerLevel    : 1;	/*!< 0 = edge triggered, !0 = level triggered, only valid if triggerReq == 0 */
	uint32_t                triggerBurst    : 1;	/*!< 0 = single data transfer, !0 = burst data transfer, only valid if triggerReq == 0 */
	uint32_t                burstSize       : 4;	/*!< Burst data transfer size, only valid if triggerReq == 0 (ROM_DMA_BURSTPOWER_T) */
	uint32_t                srcBurstWrap    : 1;	/*!< 0 = disable source burst wrap, !0 = enable source burst wrap */
	uint32_t                dstBurstWrap    : 1;	/*!< 0 = disable destination burst wrap, !0 = enable destination burst wrap */
	uint32_t                channelPrio     : 3;	/*!< 0 = highest channel priority, 7 = lowest channel priority */
	uint32_t                reserved        : 3;
} ROM_DMA_CHAN_CFG_T;

/** @brief DMA transfer width values
 */
typedef enum {
	ROM_DMA_WIDTH_1 = 0,			/*!< Transfer size of data is 8-bits (1 byte) */
	ROM_DMA_WIDTH_2,				/*!< Transfer size of data is 16-bits (1 byte) */
	ROM_DMA_WIDTH_4,				/*!< Transfer size of data is 32-bits (1 byte) */
} ROM_DMA_WIDTH_T;

/** @brief DMA source and destination address increment values
 */
typedef enum {
	ROM_DMA_ADDRINC_0X = 0,			/*!< No address increment, useful to reading and writing FIFOs */
	ROM_DMA_ADDRINC_1X,				/*!< Address increment by width */
	ROM_DMA_ADDRINC_2X,				/*!< Address increment by 2x width */
	ROM_DMA_ADDRINC_4X,				/*!< Address increment by 4x width */
} ROM_DMA_ADDRINC_T;

/** @brief DMA transfer setup structure */
typedef PRE_PACK struct POST_PACK {
	void                    *src;					/*!< DMA source address */
	void                    *dest;					/*!< DMA destination address */
	void                    *pUserData;				/*!< Pointer to user data for the descriptor (chain), this only matters for the head descriptor in a chain */
	uint16_t                xferCount;				/*!< DMA transfer size in size of data width (not bytes). 1 to 1024 */
	uint8_t                 swTrig;					/*!< !0 = Software trigger of channel when descriptor is started (not recommended) */
	uint8_t                 clrTrig;				/*!< !0 = Clear trigger when descriptor is completed */
	uint8_t                 fireDescCB;				/*!< !0 = DMA interrupt fires after this descriptor is complete and calls descriptor complete callback */
	uint8_t                 enabCirc;				/*!< !0 = Enable circular buffer support : Will disable completion callback */
	uint8_t                 width;					/*!< Data transfer width (ROM_DMA_WIDTH_T) */
	uint8_t                 srcInc;					/*!< Source address incremention (ROM_DMA_ADDRINC_T) */
	uint8_t                 dstInc;					/*!< Destination address incremention (ROM_DMA_ADDRINC_T) */
	uint8_t                 dmaCh;					/*!< Configured DMA channel mapped to this descriptor (ROM_DMA_CHID_T) */
	uint8_t                 stallDesc;				/*!< Stalls this descriptor using CFGVALID before transfer, must use SETVALID to restart */
	uint8_t                 reserved;
} ROM_DMA_XFERDESC_CFG_T;

/** @brief SPI master initialization structure */
typedef PRE_PACK struct POST_PACK {
	void                    *pUserData;				/*!< Pointer to user data used by driver instance, use NULL if not used */
	uint32_t                base;					/*!< Pointer to where the DMA peripheral is located */
	uint32_t                sramBase;				/*!< Pointer to memory used for DMA descriptor storage, must be 512 byte aligned */
} ROM_DMA_INIT_T;

/** @brief Queue operating states
 * These are the possible states of the DMA descriptor channel queue.
 */
typedef enum {
	ROM_QUEUE_ST_IDLE = 0,		/*!< DMA queue is idle. Use ROM_SET_QUEUE_START to start */
	ROM_QUEUE_ST_RUNNING,			/*!< DMA queue is processing descriptor chains */
	ROM_QUEUE_ST_ERROR				/*!< DMA queue is stoipped due to an error. Use ROM_SET_QUEUE_START to restart at next descriptor chain */
} ROM_DMA_QUEUE_STATES_T;

/** @brief SPI master ROM indirect function structure */
typedef PRE_PACK struct POST_PACK {
	/* DMA driver initialization */
	uint32_t (*GetMemSize)(void);	/*!< Returns needed memory size required for run-time context of DMA controller driver */
	ROM_DMA_HANDLE_T (*Init)(void *mem, const ROM_DMA_INIT_T *pInit);	/*!< Initializes the DMA controller driver and peripheral */

	/* DMA channel setup, channel queue setup, and channel callback registration */
	ErrorCode_t (*SetupChannel)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_CHAN_CFG_T *pCfg, uint8_t dmaCh);	/*!< Configures a DMA channel */
	ErrorCode_t (*InitQueue)(ROM_DMA_HANDLE_T pHandle, uint8_t dmaCh, ROM_DMA_QUEUE_T *pQueue);	/*!< Initializes a transfer descriptor queue for a channel */
	void (*RegisterQueueCallback)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, uint32_t cbIndex, void *pCB);	/*!< Registers an DMA controller callback for a queue */

	/* DMA descriptor chain build and status support */
	ErrorCode_t (*BuildDescriptorChain)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_XFERDESC_CFG_T *pXferCfg,
										ROM_DMA_DESC_T *pDesc, ROM_DMA_DESC_T *pDescPrev);																/*!< Builds a transfer descriptor chain from the passed settings */
	uint32_t (*GetTransferCount)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_DESC_T *pDesc);	/*!< Returns the number of items transferred on the last descriptor chain (spent status only) */
	void (*UnstallDescriptorChain)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);	/*!< Unstalls a descriptor chain that has been setup using the stallDesc option */

	/* DMA queue management */
	void (*QueueDescriptor)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, ROM_DMA_DESC_T *pDescChainHead);	/*!< Queues a transfer descriptor chain */
	ROM_DMA_DESC_STS_T (*GetQueuePopDescriptorStatus)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);	/*!< Returns current status of next descriptro to be popped from the queue, ROM_DMA_DESC_STS_INVALID if no descriptors exist to be popped */
	ROM_DMA_DESC_T * (*UnQueueDescriptor)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T * pQueue);	/*!< Pops (unqueues) an expired transfer descriptor from the queue - expired descriptors are in spent, error, or abort states */
	ErrorCode_t (*StartQueue)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);	/*!< Starts or restarts a queue at the next descriptor chain */
	ErrorCode_t (*StopQueue)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);	/*!< Stops DMA and aborts current descriptor chain being processed in queue, call StartQueue to restart at the next descriptor chain */
	void (*FlushQueue)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);	/*!< Stops DMA and completely flushes a transfer queue, queue is completely reset */
	uint8_t (*GetQueueState)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);	/*!< Returns the current queue state (ROM_DMA_QUEUE_STATES_T) */

	/* Misc */
	void (*ForceTrigger)(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);	/*!< Forces a DMA transfer to trigger */

	/* DMA queue and transfer handler - must be called from DMA interrupt or from background as fast as possible */
	void (*DMAHandler)(ROM_DMA_HANDLE_T pHandle);	/*!< DMA transfer (interrupt) handler */

	/* Driver version */
	uint32_t (*GetDriverVersion)(void);
} ROM_DMAALTD_API_T;

/**
 * @}
 */

extern const ROM_DMAALTD_API_T dmaalt_api;	// so application program can access	pointer to
// function table

#endif /* __HW_DMAALTD_ROM_API_H */
