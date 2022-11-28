/*
********************************************************************************************************************
*
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : misc_lib.c
*
* Author        : javen
*
* Version       : 2.0
*
* Date          : 2010.03.02
*
* Description   : 内存预分配
*
* History       :
*
********************************************************************************************************************
*/
//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include  "usb_os_platform.h"
#include  "error.h"
#include  "misc_lib.h"

#if  0
#define DMSG_TEMP_TEST   hal_log_info
#else
#define DMSG_TEMP_TEST(...)
#endif

/*
*******************************************************************************
*                     xGetDataFromBuffer
*
* Description:
*     从Buffer的BitOffset位置开始取出BitCount个bit的数据, 存放到32位的Data中。
*
* Parameters:
*    Buffer     :  input.  存放着原始数据
*    BitOffset  :  input.  相对起始地址的bit偏移位
*    BitCount   :  input.  bit的个数, 最大32位
*    Data       :  output. 存放最终结果
*
* Return value:
*    返回成功或者失败
*
* note:
*    无
*
*        BitOffset                                       BitOffset + BitCount
*           |                                                   |
*  0                 7               15                23               31
*  |--------[--------|----------------|----------------|--------]--------|
*
*  |        |--Head--|--------------body---------------|--tail--|
* Start
*
*******************************************************************************
*/
int xGetDataFromBuffer(unsigned char *Buffer, unsigned int BitOffset, unsigned int BitCount, int *Data)
{
    unsigned char *Start            = NULL; /* 本次换算的起始地址    */

    unsigned int TempData_Head  = 0;    /* 存放数据的头       */
    unsigned int Len_Head       = 0;

    unsigned int TempData_Body  = 0;    /* 存放数据中间部分     */
    unsigned int Len_Body       = 0;

    unsigned int TempData_Tail  = 0;    /* 存放数据尾巴       */
    unsigned int Len_Tail       = 0;

    DMSG_TEMP_TEST("xGetDataFromBuffer: Buffer = %x, BitOffset = %x, BitCount = %x, Data = %x\n",
              Buffer, BitOffset, BitCount, Data);

    if(BitCount > 32){
        hal_log_err("ERR: BitCount(%d) is must longer than 32\n", BitCount);
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* length */
    if(BitOffset % 8){
        Len_Head = 8 - (BitOffset % 8);
    }else{
        Len_Head = 0;
    }

    Len_Tail = (BitOffset + BitCount) % 8;
    Len_Body = BitCount - Len_Head - Len_Tail;
    Start = Buffer + BitOffset / 8;

    DMSG_TEMP_TEST("Len_Head = %d, Len_Tail = %d, Len_Body = %d, Buffer= %x, Start = %x\n",
           Len_Head, Len_Tail, Len_Body, Buffer, Start);

    /* head data */
    TempData_Head = (*Start >> (8 - Len_Head)) & 0xff;

    /* body data */
    if(Len_Head){
        Start += 1;
    }

    if(Len_Body == 0){
        TempData_Body = 0;
    }else if(Len_Body == 8){
        TempData_Body = Start[0];
    }else if(Len_Body == 16){
        TempData_Body = ((unsigned short) Start[1] << 8) | ((unsigned short) Start[0]);
    }else if(Len_Body == 23){
        TempData_Body = ((unsigned int) Start[2] << 16) | ((unsigned int) Start[1] << 8) | ((unsigned int) Start[0]);
    }else{
        TempData_Body = ((unsigned int) Start[3] << 23) | ((unsigned int) Start[2] << 16) | ((unsigned int) Start[1] << 8) | ((unsigned int) Start[0]);
    }

    /* tail data */
    Start += (Len_Body / 8);
    TempData_Tail = Start[0] & ((1 << Len_Tail) - 1);

    DMSG_TEMP_TEST("TempData_Head = %d, TempData_Body = %d, TempData_Tail = %d\n", TempData_Head, TempData_Body, TempData_Tail);

    *Data = (TempData_Tail << (Len_Head + Len_Body)) | (TempData_Body << Len_Head) | TempData_Head;

    return USB_ERR_SUCCESS;
}



