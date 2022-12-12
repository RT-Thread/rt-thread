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

#ifndef __CORE_DMA_H__
#define __CORE_DMA_H__

enum
{
    DMA1_STREAM_0,
    DMA1_STREAM_1,
    DMA1_STREAM_2,
    DMA1_STREAM_3,
    DMA1_STREAM_4,
    DMA1_STREAM_5,
    DMA1_STREAM_6,
    DMA1_STREAM_7,
//  DMA1_STREAM_QTY,
//  DMA2_STREAM_0 = DMA1_STREAM_QTY,
//  DMA2_STREAM_1,
//  DMA2_STREAM_2,
//  DMA2_STREAM_3,
//  DMA2_STREAM_4,
//  DMA2_STREAM_5,
//  DMA2_STREAM_6,
//  DMA2_STREAM_7,
    DMA2_STREAM_QTY,
    DMA_STREAM_QTY = DMA2_STREAM_QTY,
};
void DMA_GlobalInit(void);
void *DMA_TakeStream(uint8_t Stream);
int DMA_CheckStreamLock(uint8_t Stream);
void DMA_ReleaseStream(uint8_t Stream);
uint8_t DMA_CheckStreamBusy(uint8_t Stream);
int DMA_ConfigStream(uint8_t Stream, void *Config);
int DMA_StartStream(uint8_t Stream, const void *Data, uint32_t Len, CBFuncEx_t CB, void *pUserData, uint8_t NeedIrq);
/**
 * @brief 强制启动DMA传输
 * @param Stream DMA流序号
 * @param Data DMA缓存
 * @param Len DMA缓存长度
 * @param CB 完成或者出错回调。完成时，回调函数参数pParam为0，出错为0xffffffff
 * @param NeedIrq 是否需要中断
 * @return 无
 */
void DMA_ForceStartStream(uint8_t Stream, const void *Data, uint32_t Len, CBFuncEx_t CB, void *pUserData, uint8_t NeedIrq);
void DMA_ClearStreamFlag(uint8_t Stream);
void DMA_StopStream(uint8_t Stream);
uint32_t DMA_GetRemainingDataLength(uint8_t Stream);
uint32_t DMA_GetDataLength(uint8_t Stream, uint32_t FirstAddress);
void DMA_BaseConfig(void *Config);
void DMA_PrintGlobalReg(void);
void DMA_PrintReg(uint8_t Stream);
#endif
