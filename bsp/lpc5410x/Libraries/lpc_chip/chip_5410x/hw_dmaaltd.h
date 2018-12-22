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

#ifndef __HW_DMAALTD_H
#define __HW_DMAALTD_H

#include "error.h"
#include "hw_dmaaltd_rom_api.h"

// *** DMA controller functions called by Application Program ***
uint32_t dmaalt_get_mem_size(void);

ROM_DMA_HANDLE_T dmaalt_init(void *mem, const ROM_DMA_INIT_T *pInit);

ErrorCode_t dmaalt_setup_channel(ROM_DMA_HANDLE_T pHandle, ROM_DMA_CHAN_CFG_T *pCfg, uint8_t dmaCh);

ErrorCode_t dmaalt_init_queue(ROM_DMA_HANDLE_T pHandle, uint8_t dmaCh, ROM_DMA_QUEUE_T *pQueue);

void dmaalt_register_queue_callback(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, uint32_t cbIndex, void *pCB);

ErrorCode_t dmaalt_build_descriptor_chain(ROM_DMA_HANDLE_T pHandle,
										  ROM_DMA_XFERDESC_CFG_T *pXferCfg,
										  ROM_DMA_DESC_T *pDesc,
										  ROM_DMA_DESC_T *pDescPrev);

uint32_t dmaalt_get_transfer_count(ROM_DMA_HANDLE_T pHandle, ROM_DMA_DESC_T *pDesc);

void dmaalt_unstall_descriptor_chain(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

void dmaalt_queue_descriptor(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue, ROM_DMA_DESC_T *pDescChainHead);

ROM_DMA_DESC_STS_T dmaalt_get_queue_pop_descriptor_status(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

ROM_DMA_DESC_T *dmaalt_unqueue_descriptor(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

ErrorCode_t dmaalt_start_queue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

ErrorCode_t dmaalt_stop_queue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

void dmaalt_flush_queue(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

uint8_t dmaalt_get_queue_state(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

void dmaalt_force_trigger(ROM_DMA_HANDLE_T pHandle, ROM_DMA_QUEUE_T *pQueue);

void dmaalt_handler(ROM_DMA_HANDLE_T pHandle);

uint32_t dmaalt_get_driver_version(void);

// ***

#endif /* __HW_DMAALTD_H */
