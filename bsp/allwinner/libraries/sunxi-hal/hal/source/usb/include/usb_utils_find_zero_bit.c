/*
*******************************************************************************
*                                    usb host module
*
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : javen
*
* Version : 1.0
*
* Date : 2008.07.xx
*
* Description :
*
* History :
*******************************************************************************
*/
//#include "usb_host_config.h"

//#include "usb_host_base_types.h"
#include <stdio.h>
#include "usb_utils_find_zero_bit.h"
#define FIND_NEXT_ZERO_BIT_MAX_SIZE     (128)
#define FIND_NEXT_ZERO_BIT_NOT_FOUND        (0xffffffff)


/*
******************************************************************************
*
*             find_next_zero_bit
*
* Description:
*     在地址连续的n个int字节中，从指定bit位开始查找第一个为0的bit的位.
*
* Parameters:
*     addr    :   起始地址.
*     size    :   n个字节的总长度,(32 * n).
*     offset  :   开始查找的bit位.
*
*  Return value:
*     查找成功，返回查找到的第一个为0的bit位。查找失败，则返回0xffffffff。
*
******************************************************************************
*/
u32 find_next_zero_bit(const volatile u32 *addr, u32 size, u32 offset)
{
    u32 *p = (u32 *) addr ;
    u32 bit = FIND_NEXT_ZERO_BIT_NOT_FOUND;
    int k;      //字节中的偏移量
    int i, j;
    int n;      //int字节的个数
    int m;      //所在字节的位置
    n = size / 32;
    k = 32 - (offset % 32);
    m = offset / 32;

    //offset为0 ~ size-1
    if (size > FIND_NEXT_ZERO_BIT_MAX_SIZE || offset >= size || m > n)
    {
        return bit;
    }

    //从offsize位置向前查找，直到结尾
    for (j = 0; j < (n - m); j++)
    {
        if (j == 0) //offsize所在的字节
        {
            for (i = 0; i < k; i++)
            {
                if (((*(p + m + j) >> ((offset % 32) + i))) & 0x01)
                {
                    continue;
                }
                else
                {
                    bit = (offset + i);
                    return bit;
                }
            }
        }
        else  //offsize所在字节的下j个字节
        {
            for (i = 0; i < 32; i++)
            {
                if ((*(p + m + j) >> i) & 0x01)
                {
                    continue;
                }
                else
                {
                    //                  bit = (offset+(j*32)+i);
                    bit = ((j * 32) + i);
                    return bit;
                }
            }
        }
    }

    //从addr位置向前查找，直到offsize处停止
    for (j = 0; j <= m; j++)
    {
        if (j != m) //从addr位置向前查找
        {
            for (i = 0; i < 32; i++)
            {
                if (((*(p + j) >> i)) & 0x01)
                {
                    continue;
                }
                else
                {
                    bit = i + (j * 32);
                    return bit;
                }
            }
        }
        else  //offsize所在的字节
        {
            for (i = 0; i < (32 - k); i++)
            {
                if (((*(p + j) >> i)) & 0x01)
                {
                    continue;
                }
                else
                {
                    bit = i + (j * 32);
                    return bit;
                }
            }
        }
    }

    return bit;
}

