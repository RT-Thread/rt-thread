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

#ifndef __CORE_SERVICE_H__
#define __CORE_SERVICE_H__
#include "bsp_common.h"

typedef struct
{
    uint32_t Speed;
    uint32_t x1;
    uint32_t y1;
    uint32_t x2;
    uint32_t y2;
    uint32_t xoffset;
    uint32_t yoffset;
    uint32_t Size;
    uint32_t DCDelay;
    uint8_t *Data;
    uint8_t SpiID;
    uint8_t Mode;
    uint8_t CSPin;
    uint8_t DCPin;
    uint8_t ColorMode;
}LCD_DrawStruct;

void Core_ServiceInit(void);
void Core_LCDDraw(LCD_DrawStruct *Draw);
void Core_CameraDraw(LCD_DrawStruct *Draw);
void Core_DecodeQR(uint8_t *ImageData, uint16_t ImageW, uint16_t ImageH,  CBDataFun_t CB);
uint32_t Core_LCDDrawCacheLen(void);
void Core_USBDefaultDeviceStart(uint8_t USB_ID);
void Core_USBAction(uint8_t USB_ID, uint8_t Action, void *pParam);
void Core_PrintMemInfo(void);
void Core_PrintServiceStack(void);
void Core_DebugMem(uint8_t HeapID, const char *FuncName, uint32_t Line);

uint8_t Core_GetSleepFlag(void);
void Core_SetSleepEnable(uint8_t OnOff);

void Core_VUartInit(uint8_t UartID, uint32_t BaudRate, uint8_t IsRxCacheEnable, uint8_t DataBits, uint8_t Parity, uint8_t StopBits, CBFuncEx_t CB);
void Core_VUartDeInit(uint8_t UartID);
void Core_VUartSetRxTimeout(uint8_t UartID, uint32_t TimeoutUS);
void Core_VUartSetCb(uint8_t UartID, CBFuncEx_t CB);
uint32_t Core_VUartRxBufferRead(uint8_t UartID, uint8_t *Data, uint32_t Len);
int32_t Core_VUartBufferTx(uint8_t UartID, const uint8_t *Data, uint32_t Len);
void Core_VUartBufferTxStop(uint8_t UartID);

void Core_VHIDInit(uint8_t USB_ID, CBFuncEx_t CB);
void Core_VHIDUploadData(uint8_t USB_ID, uint8_t *Data, uint16_t Len);
void Core_VHIDUploadStop(uint8_t USB_ID);
#endif
