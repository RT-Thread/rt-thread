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


#ifndef __AIR105_OTP_H
#define __AIR105_OTP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    OTP_Complete = 0,
    OTP_ReadOnProgramOrSleep,               //在编程或休眠状态下读取OTP数据
    OTP_ProgramIn_HiddenOrRO_Block,         //在只读或隐藏块中编程
    OTP_ProgramOutOfAddr,                   //超出OTP地址范围
    OTP_ProgramOnSleep,                     //在睡眠状态下编程
    OTP_WakeUpOnNoSleep,                    //在非睡眠状态下从唤醒
    OTP_TimeOut,                            //OTP写入超时
    OTP_DataWrong,
}OTP_StatusTypeDef;

#define IS_OTP_ADDRESS(ADDRESS) (((ADDRESS) > AIR105_OTP_SIZE - 1) && ((ADDRESS) < AIR105_OTP_BASE + AIR105_OTP_SIZE))


void OTP_WakeUp(void);
void OTP_Unlock(void);
void OTP_Lock(void);
void OTP_ClearStatus(void);
void OTP_SetLatency(uint8_t u8_1UsClk, uint8_t u8_10NsCLK);
void OTP_TimCmd(FunctionalState NewState);

void OTP_SetProtect(uint32_t u32Addr);
void OTP_SetProtectLock(uint32_t u32Addr);
void OTP_UnProtect(uint32_t u32Addr);
uint32_t OTP_GetProtect(void);
uint32_t OTP_GetProtectLock(void);

void OTP_PowerOn(void);

Boolean OTP_IsReadReady(void);
Boolean OTP_IsWriteDone(void);

OTP_StatusTypeDef OTP_GetFlag(void);

Boolean OTP_IsProtect(uint32_t u32Addr);
Boolean OTP_IsProtectLock(uint32_t u32Addr);

OTP_StatusTypeDef OTP_WriteWord(uint32_t addr, uint32_t w);


#ifdef __cplusplus
}
#endif

#endif

