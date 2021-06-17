/****************************************************************************
 *
 * File Name
 *  cyclequeue.c
 * Author
 *  wangk
 * Date
 *  2018/01/11
 * Descriptions:
 * 循环队列接口实现
 *
 ******************************************************************************/
/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common.h"
#include "cyclequeue.h"

/**---------------------------------------------------------------------------*
 **                            Debugging Flag                                 *
 **---------------------------------------------------------------------------*/
 
/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/
#define QUEUE_LOCK_MAX_WAIT_TIME 100 // 获取队列锁最大等待时间(ms)
#define CYCLE_QUEUE_USE_V2 // 使用高性能版本
	
/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: CycleQueue_Create
* Description:  创建Cycle Queue,
*               数据Buffer有调用者自行分配,避免动态内存申请
* Author: wangk
* Returns:
* Parameter:
*               ptCycleQueue    [out]    Point to cycle queue object
*               pu8Buf          [in]     调用者分配的内存Buffer
*               u32BufLen       [in]     Buffer长度(字节数, 必须为2^n,由用户保证
* History:
*************************************************/
void CycleQueue_Create(CycleQueue_T* ptCycleQueue, uint8_t* pu8Buf, uint32_t u32BufLen)
{
	// 设置存储Buffer
	ptCycleQueue->pu8Buf = pu8Buf;
	ptCycleQueue->u32Capacity = u32BufLen;
	
	// 清空queue
	ptCycleQueue->u32Head = 0;
	ptCycleQueue->u32Tail = 0;
	ptCycleQueue->u32Len = 0;
}

/*************************************************
* Function: CycleQueue_Release
* Description: 释放Cycle Queue
* Author: wangk
* Returns:
* Parameter:
*               ptCycleQueue    [out]    Point to cycle queue object
* History:
*************************************************/
void CycleQueue_Release(CycleQueue_T* ptCycleQueue)
{
	// 释放Buffer
	ptCycleQueue->pu8Buf = NULL;
	ptCycleQueue->u32Capacity = 0;
	
	// 清空queue
	ptCycleQueue->u32Head = 0;
	ptCycleQueue->u32Tail = 0;
	ptCycleQueue->u32Len = 0;
}

/*************************************************
* Function: CycleQueue_Clean
* Description: 清空Cycle Queue
* Author: wangk
* Returns:
* Parameter:
*               ptCycleQueue    [out]    Point to cycle queue object
* History:
*************************************************/
bool CycleQueue_Clean(CycleQueue_T* ptCycleQueue)
{
	// 清空queue
	ptCycleQueue->u32Head = 0;
	ptCycleQueue->u32Tail = 0;
	ptCycleQueue->u32Len = 0;
	
	return true;
}

/*************************************************
* Function: CycleQueue_Insert
* Description: 插入数据到Cycle Queue头部
* Author: wangk
* Returns: 实际插入的字节数
* Parameter:
*               ptCycleQueue    [in]    Point to cycle queue object
*               pcu8Data        [in]    待插入的数据
*               u32DataLen      [in]    待插入的数据长度(字节数)
* History:
*************************************************/
uint32_t CycleQueue_Insert(CycleQueue_T* ptCycleQueue, const uint8_t* pcu8Data, uint32_t u32DataLen)
{
	/* Determine how much we can actually insert */
	uint32_t u32InsertLen = MIN(u32DataLen, ptCycleQueue->u32Capacity - ptCycleQueue->u32Len); // 实际能够插入的数据长度
	if (u32InsertLen > 0)
	{
#ifdef CYCLE_QUEUE_USE_V2
		/* Determine how much to write before wrapping */
		uint32_t u32NoWrapInsertLen = MIN(u32InsertLen, ptCycleQueue->u32Capacity - ptCycleQueue->u32Head);
		if (u32NoWrapInsertLen > 0)
		{
			memcpy(ptCycleQueue->pu8Buf + ptCycleQueue->u32Head, pcu8Data, u32NoWrapInsertLen);
		}
		
		/* Now put the remainder on the beginning of the buffer */
		if (u32InsertLen > u32NoWrapInsertLen)
		{
			memcpy(ptCycleQueue->pu8Buf, pcu8Data + u32NoWrapInsertLen, u32InsertLen - u32NoWrapInsertLen);
		}

		/* 修改头指针 */
		ptCycleQueue->u32Head += u32InsertLen;
		uint32_t u32Mask = ptCycleQueue->u32Capacity - 1; // u32Capacity必须为2^n,由用户保证
		ptCycleQueue->u32Head &= u32Mask;
#else
		uint32_t i = 0;
		for (i = 0; i < u32InsertLen; ++i)
		{ // 插入数据
			ptCycleQueue->pu8Buf[ptCycleQueue->u32Head++] = pcu8Data[i];
			if (ptCycleQueue->u32Head >= ptCycleQueue->u32Capacity)
			{
				ptCycleQueue->u32Head = 0;
			}
		}
#endif
		/* 数据已插入, 递增队列长度 */
		ptCycleQueue->u32Len += u32InsertLen;
	}
	
	return u32InsertLen;
}

/*************************************************
* Function: CycleQueue_Delete
* Description:  从Cycle Queue尾部读出数据,
*               已读数据将会从队列删除
* Author: wangk
* Returns: 实际读取的字节数
* Parameter:
*               ptCycleQueue   [in]    Point to cycle queue object
*               pu8Buf         [out]   用于存放读出数据的缓冲区
*               u32BufLen      [in]    缓冲区长度(字节数)
*								pu32RemainLen  [out]   剩余数据长度(字节数)
* History:
*************************************************/
uint32_t CycleQueue_Delete(CycleQueue_T* ptCycleQueue, uint8_t* pu8Buf, uint32_t u32BufLen, uint32_t* pu32RemainLen)
{
	/* Determine how much we can actually delete */
	uint32_t u32DelLen = MIN(ptCycleQueue->u32Len, u32BufLen); // 实际能够删除的数据长度
	if (u32DelLen > 0)
	{
#ifdef CYCLE_QUEUE_USE_V2
		/* Delete data from buffer starting at offset until the end */
		uint32_t u32NoWrapDelLen = MIN(u32DelLen, ptCycleQueue->u32Capacity - ptCycleQueue->u32Tail);
		if (u32NoWrapDelLen > 0)
		{
			memcpy(pu8Buf, ptCycleQueue->pu8Buf + ptCycleQueue->u32Tail, u32NoWrapDelLen);
		}

		/* Now delete remainder from the beginning */
		if (u32DelLen > u32NoWrapDelLen)
		{
			memcpy(pu8Buf + u32NoWrapDelLen, ptCycleQueue->pu8Buf, u32DelLen - u32NoWrapDelLen);
		}

		/* 修改尾指针 */
		ptCycleQueue->u32Tail += u32DelLen;
		uint32_t u32Mask = ptCycleQueue->u32Capacity - 1; // u32Capacity必须为2^n,由用户保证
		ptCycleQueue->u32Tail &= u32Mask;
#else
		uint32_t i = 0;
		for (; i < u32DelLen; ++i)
		{ // 读取并删除数据
			pu8Buf[i] = ptCycleQueue->pu8Buf[ptCycleQueue->u32Tail++];
			if (ptCycleQueue->u32Tail >= ptCycleQueue->u32Capacity)
			{
					ptCycleQueue->u32Tail = 0;
			}
		}
#endif
		/* 数据已被读取并删除, 递减数据长度 */
		ptCycleQueue->u32Len -= u32DelLen;
	}

	if (pu32RemainLen)
	{ // 输出剩余数据长度
		*pu32RemainLen = ptCycleQueue->u32Len;
	}
	
	return u32DelLen;
}

/**---------------------------------------------------------------------------*
 **                            Compiler Flag                                  *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of sdy_cyclequeue.c
