/*
 * @brief Common ring buffer support functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
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

#ifndef __RING_BUFFER_H_
#define __RING_BUFFER_H_

#include "lpc_types.h"

/** @defgroup Ring_Buffer CHIP: Simple ring buffer implementation
 * @ingroup CHIP_Common
 * @{
 */

/**
 * @brief Ring buffer structure
 */
typedef struct {
	uint8_t *bufferBase, *bufferLast;
	uint8_t *bufferIn, *bufferOut;
	int count, used, itemSize;
} RINGBUFF_T;

/**
 * @brief	Initialize ring buffer
 * @param	RingBuff	: Pointer to ring buffer to initialize
 * @param	buffer		: Pointer to buffer to associate with RingBuff
 * @param	itemSize	: Size of each buffer item size (1, 2 or 4 bytes)
 * @param	count		: Size of ring buffer
 * @return	Nothing
 */
void RingBuffer_Init(RINGBUFF_T *RingBuff, void *buffer, int itemSize, int count);

/**
 * @brief	Return number of items in the ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @return	Number of items in the ring buffer
 */
STATIC INLINE int RingBuffer_GetCount(RINGBUFF_T *RingBuff)
{
	return RingBuff->used;
}

/**
 * @brief	Return number of items in the ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @return	true if the ring buffer is full, otherwise false
 */
STATIC INLINE bool RingBuffer_IsFull(RINGBUFF_T *RingBuff)
{
	return (bool) (RingBuff->used >= RingBuff->count);
}

/**
 * @brief	Return empty status of ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @return	true if the ring buffer is empty, otherwise false
 */
STATIC INLINE bool RingBuffer_IsEmpty(RINGBUFF_T *RingBuff)
{
	return (bool) (RingBuff->used == 0);
}

/**
 * @brief	Insert 8-bit value in ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @param	data8		: Byte to insert in ring buffer
 * @return	true if a valid byte was inserted, or false if the ring buffer was full
 */
bool RingBuffer_Insert8(RINGBUFF_T *RingBuff, uint8_t data8);

/**
 * @brief	Insert 16-bit value in ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @param	data16		: 16-bit value to insert in ring buffer
 * @return	true if valid data was inserted, or false if the ring buffer was full
 */
bool RingBuffer_Insert16(RINGBUFF_T *RingBuff, uint16_t data16);

/**
 * @brief	Insert 32-bit value in ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @param	data32		: 32-bit value to insert in ring buffer
 * @return	true if valid data was inserted, or false if the ring buffer was full
 */
bool RingBuffer_Insert32(RINGBUFF_T *RingBuff, uint32_t data32);

/**
 * @brief	Pop a 8-bit value from the ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @param	data8		: Pointer to where to place value
 * @return	true if a valid byte was popped, or false if the ring buffer was empty
 */
bool RingBuffer_Pop8(RINGBUFF_T *RingBuff, uint8_t *data8);

/**
 * @brief	Pop a 16-bit value from the ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @param	data16		: Pointer to where to place value
 * @return	true if a valid byte was popped, or false if the ring buffer was empty
 */
bool RingBuffer_Pop16(RINGBUFF_T *RingBuff, uint16_t *data16);

/**
 * @brief	Pop a 32-bit value from the ring buffer
 * @param	RingBuff	: Pointer to ring buffer
 * @param	data32		: Pointer to where to place value
 * @return	true if a valid byte was popped, or false if the ring buffer was empty
 */
bool RingBuffer_Pop32(RINGBUFF_T *RingBuff, uint32_t *data32);

/**
 * @}
 */

#endif /* __RING_BUFFER_H_ */
