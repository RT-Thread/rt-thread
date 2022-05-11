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

#ifndef __CORE_USB_LL_DRIVER_H__
#define __CORE_USB_LL_DRIVER_H__

void USB_GlobalInit(void);
void USB_PowerOnOff(HANDLE hUSB, uint8_t OnOff);
void USB_Stop(HANDLE hUSB);
void USB_ResetStart(HANDLE hUSB);
void USB_ResetEnd(HANDLE hUSB);
void USB_SetWorkMode(HANDLE hUSB, uint8_t Mode);
void USB_SetDeviceAddress(HANDLE hUSB, uint8_t Address);
int USB_InitEpCfg(HANDLE hUSB);
int USB_ReInitEpCfg(HANDLE hUSB);
void USB_Start(HANDLE hUSB);
void USB_TxPacket(HANDLE hUSB, uint8_t EpIndex, const uint8_t *Data, uint16_t Len);
void USB_DeviceXfer(HANDLE hUSB, uint8_t EpIndex);
void USB_DeviceXferStop(HANDLE hUSB, uint8_t EpIndex);
void USB_EpIntOnOff(HANDLE hUSB, uint8_t EpIndex, uint8_t IsToDevice, uint8_t OnOff);
void USB_SetDeviceNoDataSetup(HANDLE hUSB);
void USB_FlushFifo(HANDLE hUSB, uint8_t EpIndex, uint8_t IsRxFifo);

void USB_SetDeviceEPStatus (HANDLE hUSB, uint8_t Index, uint8_t IsToDevice, uint8_t Status);
uint8_t USB_GetDeviceEPStatus (HANDLE hUSB, uint8_t Index, uint8_t IsToDevice);

int32_t USB_SetISOCHDelay(HANDLE hUSB, uint16_t DelayNS);
int32_t USB_ExitLatency(HANDLE hUSB, uint8_t Config[6]);

void USB_ResumeStart(HANDLE hUSB);
void USB_ResumeEnd(HANDLE hUSB);
#endif
