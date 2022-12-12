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
#define DCMI_BUF_SIZE   (1280)
#define DCMI_RXBUF_BAND (2)
typedef struct
{
    PV_Union uBuf[DCMI_RXBUF_BAND];
    CBFuncEx_t CB;
    void *pUserData;
    uint32_t BufLen;
    uint8_t RxDMASn;

}DCMI_CtrlStruct;

static DCMI_CtrlStruct prvDCMI;
static int32_t prvDCMI_DMADone(void *pData, void *pParam);
static int32_t prvDCMI_DummyCB(void *pData, void *pParam)
{
    return -1;
}
static void prvDCMI_IrqHandler(int32_t Line, void *pData)
{
    uint32_t SR = DCMI->RISR;

    DCMI->ICR = 0xff;
    if (SR & DCMI_IER_VSYNC_IE)
    {
        prvDCMI.RxDMASn = (prvDCMI.RxDMASn + 1)%DCMI_RXBUF_BAND;
        DMA_ClearStreamFlag(DCMI_RX_DMA_STREAM);
        DMA_ForceStartStream(DCMI_RX_DMA_STREAM, prvDCMI.uBuf[prvDCMI.RxDMASn].pu32, prvDCMI.BufLen, prvDCMI_DMADone, NULL, 1);
        prvDCMI.CB(NULL, prvDCMI.pUserData);
    }
}

static int32_t prvDCMI_DMADone(void *pData, void *pParam)
{
    uint8_t LastRxDMASn;
    Buffer_Struct RxBuf;
    LastRxDMASn = prvDCMI.RxDMASn;
    prvDCMI.RxDMASn = (prvDCMI.RxDMASn + 1)%DCMI_RXBUF_BAND;
    DMA_ClearStreamFlag(DCMI_RX_DMA_STREAM);
    DMA_ForceStartStream(DCMI_RX_DMA_STREAM, prvDCMI.uBuf[prvDCMI.RxDMASn].pu32, prvDCMI.BufLen, prvDCMI_DMADone, NULL, 1);
    Buffer_StaticInit(&RxBuf, prvDCMI.uBuf[LastRxDMASn].pu32, prvDCMI.BufLen);
    prvDCMI.CB(&RxBuf, prvDCMI.pUserData);
    return 0;
}

void DCMI_Setup(uint8_t VsyncLevel, uint8_t HsyncLevel, uint8_t PclkPOL, uint8_t DataBit, uint32_t FrameRate)
{
    uint32_t Ctrl = (1 << 29);
    Ctrl |= VsyncLevel?DCMI_CR_VSPOL:0;
    Ctrl |= HsyncLevel?DCMI_CR_HSPOL:0;
    Ctrl |= PclkPOL?DCMI_CR_PCKPOL:0;
    Ctrl |= ((DataBit - 8) >> 1) << 10;
    Ctrl |= (FrameRate & 0x03 ) << 8;
    SYSCTRL->DBG_CR |= DCMI_FROM_OUT;
    DCMI->CR = Ctrl | (1 << 21);
    DCMI->IER = DCMI_IER_VSYNC_IE|DCMI_IER_OVF_IE|DCMI_IER_ERR_IE;
    DCMI->ICR = 0xff;
    ISR_OnOff(DCMI_IRQn, 0);
    ISR_SetHandler(DCMI_IRQn, prvDCMI_IrqHandler, NULL);
#ifdef __BUILD_OS__
    ISR_SetPriority(DCMI_IRQn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY - 2);
#else
    ISR_SetPriority(DCMI_IRQn, 5);
#endif
    DMA_InitTypeDef DMA_InitStruct;
    DMA_BaseConfig(&DMA_InitStruct);
    DMA_InitStruct.DMA_Peripheral = SYSCTRL_PHER_CTRL_DMA_CHx_IF_DCMI_TX;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&DCMI->DR;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_DataSize_Word;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_DataSize_Word;
    DMA_InitStruct.DMA_Priority = DMA_Priority_1;
    DMA_ConfigStream(DCMI_RX_DMA_STREAM, &DMA_InitStruct);
    if (!prvDCMI.CB)
    {
        prvDCMI.CB = prvDCMI_DummyCB;
    }
}

void DCMI_SetCallback(CBFuncEx_t CB, void *pData)
{
    if (CB)
    {
        prvDCMI.CB = CB;
    }
    else
    {
        prvDCMI.CB = prvDCMI_DummyCB;
    }
    prvDCMI.pUserData = pData;
}

void DCMI_SetCROPConfig(uint8_t OnOff, uint32_t VStart, uint32_t HStart, uint32_t VLen, uint32_t HLen)
{
    if (OnOff)
    {
        /* Sets the CROP window coordinates */
        DCMI->CWSTRTR = (VStart << 16)|HStart;

        /* Sets the CROP window size */
        DCMI->CWSIZER = (VLen << 16)|HLen;
        DCMI->CR |= DCMI_CR_CROP;
    }
    else
    {
        DCMI->CR &= ~DCMI_CR_CROP;
    }
}
/**
 * @brief 摄像头捕获开关
 *
 * @param OnOff 0： 关 1： 开
 */
void DCMI_CaptureSwitch(uint8_t OnOff, uint32_t BufLen, uint32_t ImageW, uint32_t ImageH, uint8_t DataByte, uint32_t *OutH)
{
    uint32_t i;
    uint32_t WDataLen, HLen;
    if (OnOff)
    {
        if (DCMI->CR & DCMI_CR_CAPTURE) return;
        if (!BufLen)
        {
            WDataLen = (ImageW * DataByte) >> 2;
            if (ImageH > 100)
            {
                if (!(ImageH % 10))
                {
                    HLen = ImageH / 10;
                }
                else
                {
                    HLen = ImageH >> 1;
                }
            }
            else
            {
                HLen = ImageH >> 1;
            }
            while( (WDataLen * HLen) > 2048)
            {
                HLen >>= 1;
            }
            BufLen = WDataLen * HLen;
            DBG("buf %u, H %u", BufLen, HLen);
            *OutH = HLen;
        }
        for(i = 0; i < DCMI_RXBUF_BAND; i++)
        {
            prvDCMI.uBuf[i].pu32 = OS_Malloc(BufLen * sizeof(uint32_t));
        }
        prvDCMI.RxDMASn = 0;
        prvDCMI.BufLen = BufLen;
        DMA_ClearStreamFlag(DCMI_RX_DMA_STREAM);
        DMA_ForceStartStream(DCMI_RX_DMA_STREAM, prvDCMI.uBuf[0].pu32, prvDCMI.BufLen, prvDCMI_DMADone, NULL, 1);
        DCMI->ICR = 0x1f;
        ISR_OnOff(DCMI_IRQn, 1);
        DCMI->CR |= DCMI_CR_CAPTURE|DCMI_CR_ENABLE;
    }
    else
    {
        DMA_StopStream(DCMI_RX_DMA_STREAM);
        DCMI->CR &= ~(DCMI_CR_CAPTURE|DCMI_CR_ENABLE|DCMI_CR_CM);
        DCMI->CR |= (1 << 21);
        ISR_OnOff(DCMI_IRQn, 0);
        DCMI->ICR = 0x1f;
        ISR_Clear(DCMI_IRQn);
        for(i = 0; i < DCMI_RXBUF_BAND; i++)
        {
            if (prvDCMI.uBuf[i].pu32)
            {
                OS_Free(prvDCMI.uBuf[i].pu32);
                prvDCMI.uBuf[i].pu32 = 0;
            }
        }
    }
}

