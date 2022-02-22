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

#include "user.h"

typedef struct
{
    CBFuncEx_t Callback;
    void *pParam;
    uint16_t *TxData;
    uint32_t Pos;
    uint32_t MaxLen;
    uint32_t Freq;
    uint8_t DMATxStream;
    uint8_t IsBusy;
}DAC_ResourceStruct;

static DAC_ResourceStruct prvDAC;

static int32_t DAC_DMADoneCB(void *pData, void *pParam)
{
    uint32_t TxLevel;
    if (prvDAC.MaxLen > prvDAC.Pos)
    {
        TxLevel = ((prvDAC.MaxLen -  prvDAC.Pos) > 4090)?4000:(prvDAC.MaxLen -  prvDAC.Pos);
        DMA_ClearStreamFlag(prvDAC.DMATxStream);
        DMA_ForceStartStream(prvDAC.DMATxStream, &prvDAC.TxData[prvDAC.Pos], TxLevel, DAC_DMADoneCB, NULL, 1);
        prvDAC.Pos += TxLevel;
    }

    else
    {
        prvDAC.IsBusy = 0;
        prvDAC.Callback(NULL, prvDAC.pParam);
    }

}

static int32_t DAC_DummyCB(void *pData, void *pParam)
{
    DBG("!");
    return 0;
}

void DAC_Init(uint8_t Stream)
{
    DMA_InitTypeDef DMA_InitStruct;
    DMA_BaseConfig(&DMA_InitStruct);
    DMA_InitStruct.DMA_Peripheral = SYSCTRL_PHER_CTRL_DMA_CHx_IF_DAC;
    DMA_InitStruct.DMA_PeripheralBurstSize = DMA_BurstSize_8;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&DAC->DAC_DATA;
    DMA_InitStruct.DMA_Priority = DMA_Priority_3;
    DMA_InitStruct.DMA_MemoryBurstSize = DMA_BurstSize_8;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_DataSize_HalfWord;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_DataSize_HalfWord;
    DMA_ConfigStream(Stream, &DMA_InitStruct);
    prvDAC.DMATxStream = Stream;
}

void DAC_Setup(uint32_t Freq, uint32_t OutRMode)
{
    uint32_t Ctrl;
    while (DAC->DAC_CR1 & (1 << 29));

    DAC->DAC_CR1 = (OutRMode << 5) | 0x0c;
    DAC->DAC_TIMER = ((SystemCoreClock >> 3) / Freq) - 1;
    DAC->DAC_FIFO_THR = 7;
}

void DAC_Send(const uint16_t *Data, uint32_t Len, CBFuncEx_t Callback, void *pParam)
{
    uint32_t TxLevel;
    if (prvDAC.IsBusy)
    {
        DMA_PrintReg(prvDAC.DMATxStream);
        return;
    }
    prvDAC.IsBusy = 1;
    prvDAC.TxData = Data;
    prvDAC.MaxLen = Len;
    prvDAC.Pos = 0;
    if (Callback)
    {
        prvDAC.Callback = Callback;
    }
    else
    {
        prvDAC.Callback = DAC_DummyCB;
    }
    prvDAC.pParam = pParam;
    TxLevel = ((prvDAC.MaxLen -  prvDAC.Pos) > 4090)?4000:(prvDAC.MaxLen -  prvDAC.Pos);
    prvDAC.Pos += TxLevel;
    DMA_ClearStreamFlag(prvDAC.DMATxStream);
    DMA_ForceStartStream(prvDAC.DMATxStream, &prvDAC.TxData[prvDAC.Pos], TxLevel, DAC_DMADoneCB, NULL, 1);
}
