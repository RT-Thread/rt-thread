/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __BSP_COMMON_H__
#define __BSP_COMMON_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include "cmsis_gcc.h"


typedef struct
{
    uint32_t param_max_num;
    uint32_t param_max_len;
    uint32_t param_num;
    int8_t *param_str;
}CmdParam;

typedef struct
{
    uint8_t Sec;
    uint8_t Min;
    uint8_t Hour;
    uint8_t Week;//表示日期0~6,sun~sat，表示预约时，bit0~bit6,sun~sat
}Time_UserDataStruct;

typedef struct
{
    uint16_t Year;
    uint8_t Mon;
    uint8_t Day;
}Date_UserDataStruct;

typedef union
{
    uint32_t dwTime;
    Time_UserDataStruct Time;
}Time_Union;

typedef union
{
    uint32_t dwDate;
    Date_UserDataStruct Date;
}Date_Union;

typedef struct
{
    uint8_t *Data;
    uint32_t Len;
    uint32_t Offset;
    uint32_t MaxLength;
    uint32_t DataSize;
}Loop_Buffer;

typedef struct
{
    uint8_t *Data;
    uint32_t Pos;
    uint32_t MaxLen;
}Buffer_Struct;

typedef union
{
    void *p;
    char *pc8;
    uint8_t *pu8;
    uint16_t *pu16;
    uint32_t *pu32;
    uint32_t u32;
    uint8_t u8[4];
    uint16_t u16[2];
}PV_Union;

enum
{
    ERROR_NONE,
    ERROR_NO_SUCH_ID,
    ERROR_PERMISSION_DENIED,
    ERROR_PARAM_INVALID,
    ERROR_PARAM_OVERFLOW,
    ERROR_DEVICE_BUSY,
    ERROR_OPERATION_FAILED,
    ERROR_BUFFER_FULL,
    ERROR_NO_MEMORY,
    ERROR_CMD_NOT_SUPPORT,
    ERROR_NO_DATA,
    ERROR_NO_FLASH,
    ERROR_NO_TIMER,
    ERROR_TIMEOUT,
    ERROR_SSL_HANDSHAKE,
    ERROR_PROTOCL,
    ERROR_ID_INVALID,
    ERROR_MID_INVALID,
    ERROR_RETRY_TOO_MUCH,
    ERROR_CMD_BLOCK,
    LIST_FIND = 1,
    LIST_PASS = 0,
    LIST_DEL = -1,

    DMA_CB_DONE = 0,
    UART_CB_TX_BUFFER_DONE,
    UART_CB_TX_ALL_DONE,
    UART_CB_RX_NEW,
    UART_CB_RX_TIMEOUT,
    UART_CB_RX_BUFFER_FULL,
    UART_CB_ERROR,
    UART_CB_CONNECTED,  //串口工具对方已经打开
    DMA_CB_ERROR = 0xffffffff,

    CORE_EVENT_ID_START = 0,
    CORE_EVENT_ID_ANY = 0,
    CORE_EVENT_TIMEOUT,
    CORE_TIMER_TIMEOUT = 0x00010000,
    SERVICE_EVENT_ID_START = 0x00100000,
    USER_EVENT_ID_START = 0x10000000,
    INVALID_EVENT_ID = 0xffffffff,
};

#define INVALID_HANDLE_VALUE  ((void *)0xffffffff)
#define INVALID_PARAM  (0xffffffff)
#define CRC32_GEN       (0x04C11DB7)
#define CRC32_START     (0xffffffff)
#define CRC16_CCITT_GEN     (0x1021)
#define CRC16_MODBUS_GEN        (0x8005)
#define CRC16_START     (0xffff)
#define CRC16_IBM_SEED  (0xffff)
#define CRC16_CCITT_SEED        (0x1D0F)
#define HANDLE          void *

#define MIN(X,Y)    (((X) < (Y))?(X):(Y))

typedef void (* TaskFun_t)( void * );
typedef void(* CBDataFun_t)(uint8_t *Data, uint32_t Len);
typedef int32_t(*CBFuncEx_t)(void *pData, void *pParam);
typedef uint64_t LongInt;

typedef struct
{
    CBFuncEx_t CB;
    union {
        void *pParam;   //用户回调模式
        uint32_t MaxCnt;    //设置捕获模式时的最大tick，捕获时的tick
    }uParam;

    union {
        struct {
            uint8_t Level;  //IO输入输出电平，捕获模式下中断时IO电平
            uint8_t PullMode; //IO上下拉控制
        } IOArg;
        struct {
            uint8_t ExtiMode;   //中断模式
            uint8_t PullMode; //IO上下拉控制
        } ExitArg;
        uint16_t Time;  //delay时间，us
    } uArg;
    uint8_t Operation;  //操作类型
    uint8_t Arg1;       //IO操作时为IOpin，delay操作时则为微调值，0~47，48为1us
}OPQueue_CmdStruct;

__attribute__((weak)) uint8_t OS_CheckInIrq(void);

uint32_t OS_EnterCritical(void);
void OS_ExitCritical(uint32_t Critical);
void *OS_Malloc(uint32_t Size);
void *OS_Zalloc(uint32_t Size);
void OS_Free(void *p);
void *OS_Realloc(void *buf, uint32_t size);
void OS_MemInfo(uint32_t *curalloc, uint32_t *totfree, uint32_t *maxfree);
int32_t OS_InitBuffer(Buffer_Struct *Buf, uint32_t Size);
void OS_DeInitBuffer(Buffer_Struct *Buf);
int32_t OS_ReInitBuffer(Buffer_Struct *Buf, uint32_t Size);
int32_t OS_ReSizeBuffer(Buffer_Struct *Buf, uint32_t Size);
int32_t OS_BufferWrite(Buffer_Struct *Buf, void *Data, uint32_t Len);
int32_t OS_BufferWriteLimit(Buffer_Struct *Buf, void *Data, uint32_t Len);
void OS_BufferRemove(Buffer_Struct *Buf, uint32_t Len);

void Buffer_StaticInit(Buffer_Struct *Buf, void *Src, uint32_t MaxLen);
int32_t Buffer_StaticWrite(Buffer_Struct *Buf, void *Data, uint32_t Len);
void Buffer_Remove(Buffer_Struct *Buf, uint32_t Len);
void LoopBuffer_Init(Loop_Buffer *Buf, void *Src, uint32_t MaxLen, uint32_t DataSize);
uint32_t LoopBuffer_Query(Loop_Buffer *Buf, void *Src, uint32_t Len);
uint32_t LoopBuffer_Read(Loop_Buffer *Buf, void *Src, uint32_t Len);
void LoopBuffer_Del(Loop_Buffer *Buf, uint32_t Len);
uint32_t LoopBuffer_Write(Loop_Buffer *Buf, void *Src, uint32_t Len);
int32_t BSP_SetBit(uint8_t *Data, uint32_t Sn, uint8_t Value);
int32_t BSP_GetBit(uint8_t *Data, uint32_t Sn, uint8_t *Value);
uint8_t BSP_TestBit(uint8_t *Data, uint32_t Sn);
uint8_t XorCheck(void *Src, uint32_t Len, uint8_t CheckStart);
uint8_t SumCheck(uint8_t *Data, uint32_t Len);
uint16_t CRC16Cal(void *Data, uint16_t Len, uint16_t CRC16Last, uint16_t CRCRoot, uint8_t IsReverse);
uint32_t AsciiToU32(uint8_t *Src, uint32_t Len);
void CRC32_CreateTable(uint32_t *Tab, uint32_t Gen);
uint32_t CRC32_Cal(uint32_t * CRC32_Table, uint8_t *Buf, uint32_t Size, uint32_t CRC32Last);
uint32_t CmdParseParam(int8_t* pStr, CmdParam *CmdParam, int8_t Cut);
uint8_t IsLeapYear(uint32_t Year);
LongInt UTC2Tamp(Date_UserDataStruct *Date, Time_UserDataStruct *Time);
uint32_t Tamp2UTC(LongInt Sec, Date_UserDataStruct *Date, Time_UserDataStruct *Time, uint32_t LastDDay);
/*
 * 转义解包
 * 标识Flag，即包头包尾加入Flag
 * 数据中遇到Code F1 -> Flag
 * 数据中遇到Code F2 -> Code
 * 数据中遇到Flag 出错返回0
 */

uint32_t TransferUnpack(uint8_t Flag, uint8_t Code, uint8_t F1, uint8_t F2, uint8_t *InBuf, uint32_t Len, uint8_t *OutBuf);
/*
 * llist相关代码，大部分来自linux内核
 */
/**
 * container_of - cast a member of a structure out to the containing structure
 *
 * @ptr:    the pointer to the member.
 * @type:   the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({          \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})


/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized llist entries.
 */
#define LLIST_POISON1  (0)
#define LLIST_POISON2  (0)

/*
 * Simple doubly linked llist implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole llists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

typedef struct llist_head_t{
    struct llist_head_t *next, *prev;
}llist_head;

#define LLIST_HEAD_INIT(name) { &(name), &(name) }

#define LLIST_HEAD(name) \
    llist_head name = LLIST_HEAD_INIT(name)

#define INIT_LLIST_HEAD(ptr) do { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal llist manipulation where we know
 * the prev/next entries already!
 */
void __llist_add(llist_head *p,
                         llist_head *prev,
                         llist_head *next);

/**
 * llist_add - add a new entry
 * @new: new entry to be added
 * @head: llist head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
void llist_add(llist_head *p, llist_head *head);

/**
 * llist_add_tail - add a new entry
 * @new: new entry to be added
 * @head: llist head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
void llist_add_tail(llist_head *p, llist_head *head);


/*
 * Delete a llist entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal llist manipulation where we know
 * the prev/next entries already!
 */
void __llist_del(llist_head * prev, llist_head * next);

/**
 * llist_del - deletes entry from llist.
 * @entry: the element to delete from the llist.
 * Note: llist_empty on entry does not return true after this, the entry is
 * in an undefined state.
 */
void llist_del(llist_head *entry);

/**
 * llist_del_init - deletes entry from llist and reinitialize it.
 * @entry: the element to delete from the llist.
 */
void llist_del_init(llist_head *entry);

/**
 * llist_move - delete from one llist and add as another's head
 * @llist: the entry to move
 * @head: the head that will precede our entry
 */
void llist_move(llist_head *llist, llist_head *head);

/**
 * llist_move_tail - delete from one llist and add as another's tail
 * @llist: the entry to move
 * @head: the head that will follow our entry
 */
void llist_move_tail(llist_head *llist,
                  llist_head *head);

/**
 * llist_empty - tests whether a llist is empty
 * @head: the llist to test.
 */
int llist_empty(const llist_head *head);

uint32_t llist_num(const llist_head *head);

void *llist_traversal(llist_head *head, CBFuncEx_t cb, void *pData);
/**
 * llist_entry - get the struct for this entry
 * @ptr:    the &llist_head pointer.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the llist_struct within the struct.
 */
#define llist_entry(ptr, type, member) \
    container_of(ptr, type, member)


uint8_t BytesGet8(const void *ptr);
void BytesPut8(void *ptr, uint8_t v);
uint16_t BytesGetBe16(const void *ptr);
void BytesPutBe16(void *ptr, uint16_t v);
uint32_t BytesGetBe32(const void *ptr);
void BytesPutBe32(void *ptr, uint32_t v);
uint16_t BytesGetLe16(const void *ptr);
void BytesPutLe16(void *ptr, uint16_t v);
uint32_t BytesGetLe32(const void *ptr);
void BytesPutLe32(void *ptr, uint32_t v);
uint64_t BytesGetLe64(const void *ptr);
void BytesPutLe64(void *ptr, uint64_t v);
uint8_t BytesGet8FromBuf(Buffer_Struct *Buf);
void BytesPut8ToBuf(Buffer_Struct *Buf, uint8_t v);
uint16_t BytesGetBe16FromBuf(Buffer_Struct *Buf);
void BytesPutBe16ToBuf(Buffer_Struct *Buf, uint16_t v);
uint32_t BytesGetBe32FromBuf(Buffer_Struct *Buf);
void BytesPutBe32ToBuf(Buffer_Struct *Buf, uint32_t v);
uint16_t BytesGetLe16FromBuf(Buffer_Struct *Buf);
void BytesPutLe16ToBuf(Buffer_Struct *Buf, uint16_t v);
uint32_t BytesGetLe32FromBuf(Buffer_Struct *Buf);
void BytesPutLe32ToBuf(Buffer_Struct *Buf, uint32_t v);
uint64_t BytesGetLe64FromBuf(Buffer_Struct *Buf);
void BytesPutLe64ToBuf(Buffer_Struct *Buf, uint64_t v);
float BytesGetFloatFromBuf(Buffer_Struct *Buf);
void BytesPutFloatToBuf(Buffer_Struct *Buf, float v);
double BytesGetDoubleFromBuf(Buffer_Struct *Buf);
void BytesPutDoubleToBuf(Buffer_Struct *Buf, double v);
/*************************************************************************/


#define malloc OS_Malloc
#define free OS_Free
#define realloc OS_Realloc
#define zalloc OS_Zalloc
#define calloc OS_Calloc
#endif
