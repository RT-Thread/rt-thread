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
#include <stdint.h>
#include <string.h>

#define RINGBUF_IRQ_SAFE
#ifdef RINGBUF_IRQ_SAFE
#include <cmsis.h>
#define INIT_CRITICAL() uint32_t priMask = __get_PRIMASK()
#define ENTER_CRITICAL() __set_PRIMASK(1)
#define LEAVE_CRITICAL() __set_PRIMASK(priMask)
#else
#define INIT_CRITICAL()
#define ENTER_CRITICAL()
#define LEAVE_CRITICAL()

#endif

typedef struct
{
	uint8_t *pBuf;
	uint32_t size;
	uint32_t cnt;
	uint32_t rNdx;
	uint32_t wNdx;
  
} ring_buffer_t, RINGBUFF_T;

#ifndef MIN
#define MIN(x,y)  ((x) < (y) ? (x) : (y))
#endif /* ifndef MIN */

/**
 * @brief	Create and initialize a ring buffer
 * @param	pRB	: pointer to ring buffer instance
 * @param	pBuffer: pointer to the buffer for ring buffer data
 * @param   size: The size of buffer pointed by pBuffer
 * @return	>=0:Success ; <0:Failed
 */
int32_t RingBuf_Init(ring_buffer_t *pRB, uint8_t *pBuffer, uint32_t size);

/**
 * @brief	Write new data to buffer
 * @param	pRB	: pointer to the ring buffer instance
 * @param	pcData: point to data array that will be written to ring buffer
 * @param   dataBytes: bytes to write
 * @return	>=0:Bytes written ; <0:Failed
 * @remark  This function updates the ring buffer
 */
int32_t RingBuf_Write(ring_buffer_t* pRB, const uint8_t *pcData, uint32_t dataBytes);

/**
 * @brief	Write 1 new byte data to buffer
 * @param	pRB	: pointer to the ring buffer instance
 * @param	pcData: point to data byte that will be written to ring buffer
 * @return	1:success; otherwise failed
 * @remark  This function updates the ring buffer. Optimized for byte-by-byte write
 */
int32_t RingBuf_Write1Byte(ring_buffer_t* pRB, const uint8_t *pcData);

/**
 * @brief	Read (copy and remove) data from ring buffer
 * @param	pRB	: pointer to the ring buffer instance
 * @param	pData : pointer to data array that receives read data
 * @param   dataBytes: bytes to copy
 * @return	>=0:Bytes read ; <0:Failed
 * @remark  This function updates the ring buffer. 
 */
int32_t RingBuf_Read(ring_buffer_t* pRB, uint8_t *pData, uint32_t dataBytes);

/**
 * @brief	Read (copy and remove) 1 oldest byte data from buffer
 * @param	pRB	: pointer to the ring buffer instance
 * @param	pData: point to data byte that will receive the oldest byte
 * @return	1:success ; otherwise failed
 * @remark  This function updates the ring buffer. Optimized for byte-by-byte read
 */
int32_t RingBuf_Read1Byte(ring_buffer_t* pRB, uint8_t *pData);

/**
 * @brief	Copy but does NOT remove data from ring buffer
 * @param	pRB	: pointer to the ring buffer instance
 * @param	pData : pointer to data array that receives read data
 * @param   dataBytes: bytes to read
 * @return	>=0:Read bytes ; <0:Failed
 */
int32_t RingBuf_Copy(ring_buffer_t* pRB, uint8_t *pData, uint32_t dataBytes);

/**
 * @brief	Get data pointer to oldest byte in ring buffer, and contigous byte count 
 * @param	pRB	: pointer to the ring buffer instance
 * @param	ppData : pointer to pointer variable that will be updated to point to oldest byte
 * @param   contiguous_bytes: Congigous bytes until roll back
 * @return	>=0:Contiuous bytes until roll back or whole data (if roll back won't happen) ; <0:Failed
 * @remak   Use this function if performance is critical since it does NOT copy data
 *          Use RingBuf_Free() to free (remove) data after use
 */
int32_t RingBuf_Peek(ring_buffer_t* pRB, uint8_t **ppData);

/**
 * @brief	Free (remove) data from ring buffer
 * @param	pRB	: pointer to the ring buffer instance
 * @param	bytesToFree : Bytes to free (remove)
 * @remak  Use this function to free data after data get from RingBuf_Peek() is used
 */
int32_t RingBuf_Free(ring_buffer_t* pRB, uint32_t bytesToFree);

/**
 * @brief	Get free bytes of ring buffer
 * @param	pRB	: pointer to the ring buffer instance
 * @return	>=0:Free bytes ; <0:Failed
 */
int32_t RingBuf_GetFreeBytes(ring_buffer_t* pRB);

/**
 * @brief	Get free bytes of ring buffer
 * @param	pRB	: pointer to the ring buffer instance
 * @return	>=0:Used bytes ; <0:Failed
 */
int32_t RingBuf_GetUsedBytes(ring_buffer_t* pRB);

/**
 * @}
 */

#endif /* __RING_BUFFER_H_ */
