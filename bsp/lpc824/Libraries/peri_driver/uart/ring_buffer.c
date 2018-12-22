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

#include "ring_buffer.h"



int32_t RingBuf_Init(ring_buffer_t* pRB, uint8_t* buffer, uint32_t size )
{
	pRB->pBuf	 = (uint8_t*)buffer;
	pRB->size		 = size;
	pRB->rNdx		 = 0;
	pRB->wNdx		 = 0;
	pRB->cnt = 0;
	return 0;
}

int32_t RingBuf_Deinit(ring_buffer_t* pRB )
{
	pRB = pRB;;
	return 0;
}

int32_t RingBuf_GetFreeBytes(ring_buffer_t* pRB )
{
	return pRB->size - pRB->cnt;
}

int32_t RingBuf_GetUsedBytes(ring_buffer_t* pRB)
{
	return pRB->cnt;
}

int32_t RingBuf_Write(ring_buffer_t* pRB, const uint8_t* data, uint32_t dataBytes)
{
	uint32_t writeToEnd, bytesToCopy;
	INIT_CRITICAL();
	ENTER_CRITICAL();
	/* Calculate the maximum amount we can copy */
	writeToEnd = pRB->size - pRB->wNdx;
	bytesToCopy = MIN(dataBytes, pRB->size - pRB->cnt);
	
	if (bytesToCopy != 0)
	{
		/* Copy as much as we can until we fall off the end of the buffer */
		memcpy(&pRB->pBuf[pRB->wNdx], data, MIN(bytesToCopy, writeToEnd));

		/* Check if we have more to copy to the front of the buffer */
		if (writeToEnd < bytesToCopy)
		{
			memcpy(pRB->pBuf, data + writeToEnd, bytesToCopy - writeToEnd);
		}

		/* Update the wNdx */
		
		pRB->wNdx = (pRB->wNdx + bytesToCopy) % pRB->size;
		pRB->cnt += dataBytes;
	}
	LEAVE_CRITICAL();
	return bytesToCopy;
}

int32_t RingBuf_Write1Byte(ring_buffer_t* pRB, const uint8_t *pcData)
{
	uint32_t ret = 0;
	INIT_CRITICAL();
	ENTER_CRITICAL();
	if (pRB->cnt < pRB->size)
	{
		pRB->pBuf[pRB->wNdx] = pcData[0];
		pRB->wNdx = (pRB->wNdx + 1) % pRB->size;
		pRB->cnt++;
		ret = 1;
	}
	LEAVE_CRITICAL();
	return ret;
}

int32_t _prvRingBuf_Read(ring_buffer_t* pRB, uint8_t* data, uint32_t dataBytes, uint32_t isToFree)
{
	uint32_t readToEnd, bytesToCopy;
	INIT_CRITICAL();
	ENTER_CRITICAL();
	readToEnd = pRB->size - pRB->rNdx;
	bytesToCopy = MIN(dataBytes, pRB->cnt);
	if (bytesToCopy != 0)
	{
		memcpy(data, &pRB->pBuf[pRB->rNdx], MIN(bytesToCopy, readToEnd));
		
		if (readToEnd < bytesToCopy)
			memcpy(data + readToEnd, &pRB->pBuf[0], bytesToCopy - readToEnd);

		if (isToFree)
		{
			pRB->rNdx = (pRB->rNdx + bytesToCopy) % pRB->size;
			pRB->cnt -= bytesToCopy;	
		}
	}
	LEAVE_CRITICAL();
	
	return bytesToCopy;
}

int32_t RingBuf_Read(ring_buffer_t* pRB, uint8_t* data, uint32_t dataBytes)
{
	return _prvRingBuf_Read(pRB, data, dataBytes, 1);
}

int32_t RingBuf_Copy(ring_buffer_t* pRB, uint8_t* data, uint32_t dataBytes)
{
	return _prvRingBuf_Read(pRB, data, dataBytes, 0);
}

int32_t RingBuf_Read1Byte(ring_buffer_t* pRB, uint8_t *pData)
{
	uint32_t ret = 0;
	INIT_CRITICAL();
	ENTER_CRITICAL();
	if (pRB->cnt != 0)
	{
		pData[0] = pRB->pBuf[pRB->rNdx];
		pRB->rNdx = (pRB->rNdx + 1) % pRB->size;
		pRB->cnt--;
		ret = 1;
	}
	LEAVE_CRITICAL();
	return ret;
}

int32_t RingBuf_Peek(ring_buffer_t* pRB, uint8_t **ppData)
{
	uint32_t readToEnd = pRB->size - pRB->rNdx;
	uint32_t contiguousBytes;
	*ppData = &(pRB->pBuf[pRB->rNdx]);
	contiguousBytes = MIN(readToEnd, (readToEnd + pRB->wNdx) % pRB->size);
	return contiguousBytes;
}

int32_t RingBuf_Free(ring_buffer_t* pRB, uint32_t bytesToFree)
{
	INIT_CRITICAL();
	ENTER_CRITICAL();
	pRB->rNdx = (pRB->rNdx + bytesToFree) % pRB->size;
	pRB->cnt -= bytesToFree;
	LEAVE_CRITICAL();
	return bytesToFree;
}


