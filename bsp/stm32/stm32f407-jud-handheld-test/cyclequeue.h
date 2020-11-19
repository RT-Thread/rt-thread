/****************************************************************************
 *
 * File Name
 *  cyclequeue.h
 * Author
 *  wangk
 * Date
 *  2017/03/08
 * Descriptions:
 * 循环队列接口定义
 *
 ****************************************************************************/

#ifndef __CYCLEQUEUE_H__
#define __CYCLEQUEUE_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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
	
/**---------------------------------------------------------------------------*
 **                         Data Structure Definition                         *
 **---------------------------------------------------------------------------*/
// cycle queue 对象
typedef struct {
	uint8_t *pu8Buf; // 队列缓冲区
	uint32_t u32Capacity; // 队列容量(字节)
	uint32_t u32Head; // 队列头部索引
	uint32_t u32Tail; // 队列尾部索引
	uint32_t u32Len; // 当前数据长度
} CycleQueue_T;

/*----------------------------------------------------------------------------*
**                             Function Define                                *
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
*               u32BufLen       [in]     Buffer长度(字节数), 必须为2^n,由用户保证
* History:
*************************************************/
void CycleQueue_Create(CycleQueue_T* ptCycleQueue, uint8_t* pu8Buf, uint32_t u32BufLen);

/*************************************************
* Function: CycleQueue_Release
* Description: 释放Cycle Queue
* Author: wangk
* Returns:
* Parameter:
*               ptCycleQueue    [out]    Point to cycle queue object
* History:
*************************************************/
void CycleQueue_Release(CycleQueue_T* ptCycleQueue);

/*************************************************
* Function: CycleQueue_Clean
* Description: 清空Cycle Queue
* Author: wangk
* Returns:
* Parameter:
*               ptCycleQueue    [out]    Point to cycle queue object
* History:
*************************************************/
bool CycleQueue_Clean(CycleQueue_T* ptCycleQueue);

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
uint32_t CycleQueue_Insert(CycleQueue_T* ptCycleQueue, const uint8_t* pcu8Data, uint32_t u32DataLen);

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
uint32_t CycleQueue_Delete(CycleQueue_T* ptCycleQueue, uint8_t* pu8Buf, uint32_t u32BufLen, uint32_t* pu32RemainLen);

/**--------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif

#endif // __CYCLEQUEUE_H__
