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

#ifndef __CORE_SPI_H__
#define __CORE_SPI_H__
#include "bsp_common.h"
void SPI_MasterInit(uint8_t SpiID, uint8_t DataBit, uint8_t Mode, uint32_t Speed, CBFuncEx_t CB, void *pUserData);
int32_t SPI_Transfer(uint8_t SpiID, const uint8_t *TxData, uint8_t *RxData, uint32_t Len, uint8_t UseDMA);
/*
 * polling传输，不发生线程调度
 */
int32_t SPI_BlockTransfer(uint8_t SpiID, const uint8_t *TxData, uint8_t *RxData, uint32_t Len);
/*
 * 类似spiflash的cmd+data型传输用，先发WLen数据，忽略Rx数据，再接收RLen数据
 */
int32_t SPI_FlashBlockTransfer(uint8_t SpiID, const uint8_t *TxData, uint32_t WLen, uint8_t *RxData, uint32_t RLen);
void SPI_DMATxInit(uint8_t SpiID, uint8_t Stream, uint32_t Channel);
void SPI_DMARxInit(uint8_t SpiID, uint8_t Stream, uint32_t Channel);
void SPI_TransferStop(uint8_t UartID);
uint8_t SPI_IsTransferBusy(uint8_t UartID);
void SPI_SetNewConfig(uint8_t SpiID, uint32_t Speed, uint8_t NewMode);
void SPI_SetCallbackFun(uint8_t SpiID, CBFuncEx_t CB, void *pUserData);
void SPI_SetTxOnlyFlag(uint8_t SpiID, uint8_t OnOff);
#endif
