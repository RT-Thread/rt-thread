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
    const UART_TypeDef *RegBase;
    const int IrqLine;
    const uint16_t DMATxChannel;
    const uint16_t DMARxChannel;
    CBFuncEx_t Callback;
    Buffer_Struct TxBuf;
    Buffer_Struct RxBuf;
    uint32_t LastError;
    uint8_t RxCacheMode;
    uint8_t DMATxStream;
    uint8_t DMARxStream;
}Uart_ResourceStruct;

static Uart_ResourceStruct prvUart[UART_MAX] = {
        {
                UART0,
                UART0_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART0_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART0_RX,
        },
        {
                UART1,
                UART1_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART1_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART1_RX,
        },
        {
                UART2,
                UART2_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART2_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART2_RX,
        },
        {
                UART3,
                UART3_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART3_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART3_RX,
        },
};

static int32_t prvUart_DummyCB(void *pData, void *pParam)
{
    return 0;
}
static void prvUart_IrqHandle(int32_t IrqLine, void *pData);


static int32_t prvUart_DMAIrqCB(void *pData, void *pParam)
{
    uint8_t UartID = (uint32_t)pData;
    prvUart[UartID].Callback(pData, pParam);
}

static void prvUart_FIFOInit(UART_TypeDef *UARTx, UART_FIFOInitTypeDef *UART_FIFOInitStruct)
{
    /**************************  FIFO Tx Interrupt Config ******************************/
    if (DISABLE != UART_FIFOInitStruct->FIFO_TX_TriggerIntEnable)
    {
        UARTx->OFFSET_4.IER |= UART_IER_PTIME;
    }
    else
    {
        UARTx->OFFSET_4.IER &= ~UART_IER_PTIME;
    }

    /**************************  FIFO Config ******************************/
    /* FCR Write Only So Here we Use FCR Shadow Register SDMAM(WR) */
    if (UARTx->SFE | UART_SFE_SFE)
    {
        UARTx->SFE &= ~UART_SFE_SFE;
    }

    if (UART_FIFO_DMA_Mode_0 == UART_FIFOInitStruct->FIFO_DMA_Mode)
    {
        UARTx->SDMAM &= ~UART_SDMAM_SDMAM;
    }
    else if(UART_FIFO_DMA_Mode_1 == UART_FIFOInitStruct->FIFO_DMA_Mode)
    {
        UARTx->SDMAM |= UART_SDMAM_SDMAM;
    }

    /* FCR Write Only So Here we Use FCR Shadow Register SRT and STET(WR) */
    UARTx->SRT = UART_FIFOInitStruct->FIFO_RX_Trigger;
    UARTx->STET = UART_FIFOInitStruct->FIFO_TX_Trigger;

    if (DISABLE != UART_FIFOInitStruct->FIFO_Enable)
    {
        UARTx->SFE |= UART_SFE_SFE;
    }
    else
    {
        UARTx->SFE &= ~UART_SFE_SFE;
    }
}


void Uart_GlobalInit(void)
{
    int i, j;
    for(i = 0; i < UART_MAX; i++)
    {
        memset(&prvUart[i].RxBuf, 0, sizeof(Buffer_Struct));
        prvUart[i].RxCacheMode = 0;
    }
}

void Uart_BaseInit(uint8_t UartID, uint32_t BaudRate, uint8_t IsRxCacheEnable, uint8_t DataBits, uint8_t Parity, uint8_t StopBits, CBFuncEx_t CB)
{
    uint32_t tmpBaudRateDiv, LCR;
    UART_FIFOInitTypeDef UART_FIFOInitStruct;
    UART_TypeDef* Uart = prvUart[UartID].RegBase;
    SYSCTRL->SOFT_RST1 = (1 << UartID);
    while(SYSCTRL->SOFT_RST1 & (1 << UartID)){;}
    UART_FIFOInitStruct.FIFO_Enable = ENABLE;
    UART_FIFOInitStruct.FIFO_DMA_Mode = UART_FIFO_DMA_Mode_1;
    UART_FIFOInitStruct.FIFO_RX_Trigger = UART_FIFO_RX_Trigger_1_2_Full;
    UART_FIFOInitStruct.FIFO_TX_Trigger = UART_FIFO_TX_Trigger_1_4_Full;
    UART_FIFOInitStruct.FIFO_TX_TriggerIntEnable = ENABLE;

    ISR_SetHandler(prvUart[UartID].IrqLine, prvUart_IrqHandle, (void *)UartID);
#ifdef __BUILD_OS__
    ISR_SetPriority(prvUart[UartID].IrqLine, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2);
#else
    ISR_SetPriority(prvUart[UartID].IrqLine, 5);
#endif
    if (CB)
    {
        prvUart[UartID].Callback = CB;
    }
    else
    {
        prvUart[UartID].Callback = prvUart_DummyCB;
    }
//  UART_Init(Uart, &UART_InitStruct);
    Uart->LCR |= UART_LCR_DLAB;

    // baud rate = (serial clock freq) / (16 * divisor).
    tmpBaudRateDiv = (SystemCoreClock >> 6) / BaudRate;
    Uart->OFFSET_0.DLL = (tmpBaudRateDiv & 0x00FF);
    Uart->OFFSET_4.DLH = ((tmpBaudRateDiv >> 8) & 0x00FF);

    /* LCR = 0 */
    Uart->LCR &= ~UART_LCR_DLAB;
    LCR = UART_WordLength_5b + DataBits - UART_DATA_BIT5;
    switch(Parity)
    {
    case UART_STOP_BIT1:
        LCR |= UART_StopBits_1;
        break;
    case UART_STOP_BIT1_5:
        LCR |= UART_StopBits_1_5;
        break;
    case UART_STOP_BIT2:
        LCR |= UART_StopBits_2;
        break;
    }
    switch(Parity)
    {
    case UART_PARITY_NONE:
        LCR |= UART_Parity_No;
        break;
    case UART_PARITY_ODD:
        LCR |= UART_Parity_Odd;
        break;
    case UART_PARITY_EVEN:
        LCR |= UART_Parity_Even;
        break;
    }
    Uart->LCR = LCR;
    prvUart_FIFOInit(Uart, &UART_FIFOInitStruct);
    ISR_OnOff(prvUart[UartID].IrqLine, 0);
    Uart->SFE |= UART_SFE_SFE;
    Uart->OFFSET_4.IER = UART_IER_ELSI;
    prvUart[UartID].RxCacheMode = IsRxCacheEnable;
}


void Uart_SetCb(uint8_t UartID, CBFuncEx_t CB)
{
    if (CB)
    {
        prvUart[UartID].Callback = CB;
    }
    else
    {
        prvUart[UartID].Callback = prvUart_DummyCB;
    }
}

void Uart_DeInit(uint8_t UartID)
{
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    Uart->OFFSET_4.IER = 0;
    Uart_BufferTxStop(UartID);
    ISR_OnOff(prvUart[UartID].IrqLine, 0);
    ISR_Clear(prvUart[UartID].IrqLine);
    /* LCR = 1 */
    Uart->LCR |= UART_LCR_DLAB;
    Uart->OFFSET_0.DLL = 0;
    Uart->OFFSET_4.DLH = 0;

    /* LCR = 0 */
    Uart->LCR &= ~UART_LCR_DLAB;


}

int Uart_DMATxInit(uint8_t UartID, uint8_t Stream, uint32_t Channel)
{
    DMA_InitTypeDef DMA_InitStruct;
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    DMA_BaseConfig(&DMA_InitStruct);
    DMA_InitStruct.DMA_Peripheral = prvUart[UartID].DMATxChannel;
    DMA_InitStruct.DMA_PeripheralBurstSize = DMA_BurstSize_8;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&Uart->OFFSET_0.THR;
    DMA_InitStruct.DMA_Priority = DMA_Priority_3;
    DMA_InitStruct.DMA_MemoryBurstSize = DMA_BurstSize_8;
    prvUart[UartID].DMATxStream = Stream;
    return DMA_ConfigStream(Stream, &DMA_InitStruct);
}

int Uart_DMARxInit(uint8_t UartID, uint8_t Stream, uint32_t Channel)
{
    DMA_InitTypeDef DMA_InitStruct;
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    DMA_BaseConfig(&DMA_InitStruct);
    DMA_InitStruct.DMA_Peripheral = prvUart[UartID].DMARxChannel;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&Uart->OFFSET_0.RBR;
    DMA_InitStruct.DMA_Priority = DMA_Priority_3;
    prvUart[UartID].DMARxStream = Stream;
    return DMA_ConfigStream(Stream, &DMA_InitStruct);
}

void Uart_BlockTx(uint8_t UartID, uint8_t *Data, uint32_t Len)
{
    uint32_t i = 0;
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    Uart->OFFSET_4.IER &= ~(UART_IER_PTIME|UART_IER_ETBEI);
    while(i < Len)
    {
        while (Uart->USR & UART_STATUS_TX_FIFO_NOT_FULL)
        {
            Uart->OFFSET_0.THR = Data[i];
            i++;
        }
    }
}

void Uart_NoBlockTx(uint8_t UartID, uint8_t Data)
{
    uint32_t i = 0;
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    while (!(Uart->USR & UART_STATUS_TX_FIFO_NOT_FULL))
    {

    }
    Uart->OFFSET_0.THR = Data;
}

void Uart_EnableRxIrq(uint8_t UartID)
{
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    Uart->SRT = UART_FIFO_RX_Trigger_1_2_Full;
    Uart->OFFSET_4.IER |= UART_IT_RX_RECVD|UART_IER_ELSI;
    ISR_OnOff(prvUart[UartID].IrqLine, 1);
}

void Uart_EnableTxDoneIrq(uint8_t UartID)
{


}

void Uart_DMATx(uint8_t UartID, uint8_t Stream, const uint8_t *Data, uint32_t Len)
{
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    Uart->OFFSET_4.IER &= ~(UART_IER_PTIME|UART_IER_ETBEI);
    DMA_ClearStreamFlag(Stream);
    DMA_ForceStartStream(Stream, Data, Len, prvUart_DMAIrqCB, (uint32_t)UartID, 1);
    Uart->OFFSET_4.IER |= UART_IER_PTIME|UART_IER_ETBEI;
    ISR_OnOff(prvUart[UartID].IrqLine, 1);
}

void Uart_DMARx(uint8_t UartID, uint8_t Stream, uint8_t *Data, uint32_t Len)
{
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    Uart->OFFSET_4.IER |= UART_IT_RX_RECVD;
    Uart->SRT = UART_FIFO_RX_Trigger_1_4_Full;
    ISR_OnOff(prvUart[UartID].IrqLine, 1);
    DMA_ClearStreamFlag(Stream);
    DMA_ForceStartStream(Stream, Data, Len, prvUart_DMAIrqCB, (uint32_t)UartID, 1);
}


int32_t Uart_BufferTx(uint8_t UartID, const uint8_t *Data, uint32_t Len)
{
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;

    ISR_OnOff(prvUart[UartID].IrqLine, 0);
#ifdef __BUILD_OS__
    if (Data && Len)
    {
        OS_BufferWrite(&prvUart[UartID].TxCacheBuf, Data, Len);
    }
#endif
    if (prvUart[UartID].TxBuf.Data || prvUart[UartID].TxBuf.MaxLen)
    {
        ISR_OnOff(prvUart[UartID].IrqLine, 1);
        return 0;
    }
    Uart->OFFSET_4.IER &= ~(UART_IER_PTIME|UART_IER_ETBEI);
#ifdef __BUILD_OS__
    // 把缓存的Tx指针交给发送的Tx指针，缓存的Tx指针重新建立一个
    Buffer_StaticInit(&prvUart[UartID].TxBuf, prvUart[UartID].TxCacheBuf.Data, prvUart[UartID].TxCacheBuf.Pos);
#else
    Buffer_StaticInit(&prvUart[UartID].TxBuf, Data, Len);
#endif
    while ((prvUart[UartID].TxBuf.Pos < prvUart[UartID].TxBuf.MaxLen) && (Uart->USR & UART_STATUS_TX_FIFO_NOT_FULL))
    {
        Uart->OFFSET_0.THR = prvUart[UartID].TxBuf.Data[prvUart[UartID].TxBuf.Pos];
        prvUart[UartID].TxBuf.Pos++;
    }
    if (prvUart[UartID].TxBuf.Pos >= prvUart[UartID].TxBuf.MaxLen)
    {
        // 只有少量数据，只靠FIFO就能填充满，就不需要重新分配内存
        memset(&prvUart[UartID].TxBuf, 0, sizeof(prvUart[UartID].TxBuf));
#ifdef __BUILD_OS__
        prvUart[UartID].TxCacheBuf.Pos = 0;
#endif
        ISR_OnOff(prvUart[UartID].IrqLine, 1);
        Uart->OFFSET_4.IER |= UART_IER_ETBEI|UART_IER_ELSI;
        return 0;
    }
    else
    {
        // 数据多，暂时发不完，就需要为缓存重新分配内存
#ifdef __BUILD_OS__
        OS_InitBuffer(&prvUart[UartID].TxCacheBuf, TX_BUF_INIT);
#endif
        ISR_OnOff(prvUart[UartID].IrqLine, 1);
        Uart->OFFSET_4.IER |= UART_IER_PTIME|UART_IER_ETBEI|UART_IER_ELSI;
        return 1;
    }
}


void Uart_BufferTxStop(uint8_t UartID)
{
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    Uart->OFFSET_4.IER &= ~(UART_IER_PTIME|UART_IER_ETBEI);
    ISR_OnOff(prvUart[UartID].IrqLine, 0);
    memset(&prvUart[UartID].TxBuf, 0, sizeof(Buffer_Struct));
    ISR_OnOff(prvUart[UartID].IrqLine, 1);
}


static uint32_t prvUart_FifoRead(uint8_t UartID, uint8_t *Data, uint8_t Len)
{
    uint32_t i = 0;
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;

    while (Uart->USR & UART_STATUS_RX_FIFO_NOT_EMPTY && (--Len))
    {
        Data[i] = Uart->OFFSET_0.RBR;
        i++;
    }
    return i;

}

uint32_t Uart_FifoRead(uint8_t UartID, uint8_t *Data)
{
    uint32_t i = 0;
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;

    while (Uart->USR & UART_STATUS_RX_FIFO_NOT_EMPTY)
    {
        Data[i] = Uart->OFFSET_0.RBR;
        i++;
    }
    return i;

}

int Uart_ReadByte(uint8_t UartID, uint8_t *Data)
{
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    if (Uart->USR & UART_STATUS_RX_FIFO_NOT_EMPTY)
    {
        *Data = Uart->OFFSET_0.RBR;
        return 0;
    }
    else
    {
        return -1;
    }
}

void Uart_RxBufferCB(uint8_t UartID, CBFuncEx_t CB)
{
#ifdef __BUILD_OS__
    uint32_t ReadLen;
    if (!prvUart[UartID].RxCacheMode)
    {
        return ;
    }
    ISR_OnOff(prvUart[UartID].IrqLine, 0);
    if (!CB(prvUart[UartID].RxBuf.Data, (void *)prvUart[UartID].RxBuf.Pos))
    {
        prvUart[UartID].RxBuf.Pos = 0;
        if (prvUart[UartID].RxBuf.MaxLen > RX_BUF_HIGH)
        {
            OS_ReInitBuffer(&prvUart[UartID].RxBuf, RX_BUF_INIT);
        }
    }
    ISR_OnOff(prvUart[UartID].IrqLine, 1);
#endif
}

uint32_t Uart_RxBufferRead(uint8_t UartID, uint8_t *Data, uint32_t Len)
{
#ifdef __BUILD_OS__
    uint32_t ReadLen;
    if (!prvUart[UartID].RxCacheMode)
    {
        return 0;
    }
    ISR_OnOff(prvUart[UartID].IrqLine, 0);
    if (!Len)
    {
        ReadLen = prvUart[UartID].RxBuf.Pos;
        ISR_OnOff(prvUart[UartID].IrqLine, 1);
        return ReadLen;
    }
    ReadLen = (prvUart[UartID].RxBuf.Pos < Len)?prvUart[UartID].RxBuf.Pos:Len;
    memcpy(Data, prvUart[UartID].RxBuf.Data, ReadLen);
    OS_BufferRemove(&prvUart[UartID].RxBuf, ReadLen);
    if (!prvUart[UartID].RxBuf.Pos && prvUart[UartID].RxBuf.MaxLen > RX_BUF_HIGH)
    {
        OS_ReInitBuffer(&prvUart[UartID].RxBuf, RX_BUF_INIT);
    }
    ISR_OnOff(prvUart[UartID].IrqLine, 1);
    return ReadLen;
#else
    return 0;
#endif
}

void Uart_RxBufferClear(uint8_t UartID)
{
    uint32_t ReadLen;
    if (!prvUart[UartID].RxCacheMode)
    {
        return ;
    }
    ISR_OnOff(prvUart[UartID].IrqLine, 0);
    prvUart[UartID].RxBuf.Pos = 0;
    ISR_OnOff(prvUart[UartID].IrqLine, 1);
}

static void prvUart_Tx(uint8_t UartID, UART_TypeDef* Uart)
{
    if (prvUart[UartID].TxBuf.Data)
    {
        while ((prvUart[UartID].TxBuf.Pos < prvUart[UartID].TxBuf.MaxLen) && (Uart->USR & UART_STATUS_TX_FIFO_NOT_FULL))
        {
            Uart->OFFSET_0.THR = prvUart[UartID].TxBuf.Data[prvUart[UartID].TxBuf.Pos];
            prvUart[UartID].TxBuf.Pos++;
        }
        if (prvUart[UartID].TxBuf.Pos >= prvUart[UartID].TxBuf.MaxLen)
        {
#ifdef __BUILD_OS__
            OS_DeInitBuffer(&prvUart[UartID].TxBuf);
            Uart_BufferTx(UartID, NULL, 0);
#else
            memset(&prvUart[UartID].TxBuf, 0, sizeof(prvUart[UartID].TxBuf));
#endif
        }
    }
#ifdef __BUILD_OS__
    else if (prvUart[UartID].TxCacheBuf.Pos)
    {
        Uart_BufferTx(UartID, NULL, 0);
    }

    if (!prvUart[UartID].TxBuf.Data && !prvUart[UartID].TxCacheBuf.Pos)
#else
    if (!prvUart[UartID].TxBuf.Data)
#endif
    {
        if (Uart->OFFSET_4.IER & UART_IER_PTIME)
        {
            Uart->OFFSET_4.IER &= ~UART_IER_PTIME;
            prvUart[UartID].Callback((uint32_t)UartID, (void *)UART_CB_TX_BUFFER_DONE);
        }
        else
        {
            Uart->OFFSET_4.IER &= ~UART_IER_ETBEI;
            prvUart[UartID].Callback((uint32_t)UartID, (void *)UART_CB_TX_ALL_DONE);
        }
    }
}

static void prvUart_IrqHandle(int32_t IrqLine, void *pData)
{
    uint8_t UartID = (uint32_t)pData;
    UART_TypeDef* Uart = (UART_TypeDef*)prvUart[UartID].RegBase;
    uint32_t reg_value, read_len;
    switch(Uart->OFFSET_8.IIR & 0x0f)
    {
    case UART_IT_ID_RX_RECVD:
        {
            prvUart[UartID].Callback((uint32_t)UartID, (void *)UART_CB_RX_NEW);
        }
        break;
    case UART_IT_ID_TX_EMPTY:
        {

            prvUart_Tx(UartID, Uart);

        }
        break;
    case UART_IT_ID_MODEM_STATUS:
        {
            reg_value = Uart->MSR;
        }
        break;
    case UART_IT_ID_LINE_STATUS:
        {
            reg_value = Uart->LSR;
            if (reg_value & UART_LSR_TEMT)
            {
                prvUart_Tx(UartID, Uart);
            }
            if (reg_value & (UART_LSR_PFE|UART_LSR_BI|UART_LSR_FE|UART_LSR_PE|UART_LSR_OE))
            {
                prvUart[UartID].LastError = reg_value;
                prvUart[UartID].Callback((uint32_t)UartID, (void *)UART_CB_ERROR);
            }
        }
        break;
    case UART_IT_ID_BUSY_DETECT:
        {
            reg_value = Uart->USR;
        }
        break;
    case UART_IT_ID_CHAR_TIMEOUT:
        prvUart[UartID].Callback((uint32_t)UartID, (void *)UART_CB_RX_TIMEOUT);
        break;
    default:
        break;
    }
}
void Uart_ChangeBR(uint8_t UartID, uint32_t BaudRate)
{
    UART_TypeDef* Uart = prvUart[UartID].RegBase;
    Uart->LCR |= UART_LCR_DLAB;

    // baud rate = (serial clock freq) / (16 * divisor).
    uint32_t tmpBaudRateDiv = (SystemCoreClock >> 6) / BaudRate;
    Uart->OFFSET_0.DLL = (tmpBaudRateDiv & 0x00FF);
    Uart->OFFSET_4.DLH = ((tmpBaudRateDiv >> 8) & 0x00FF);

    /* LCR = 0 */
    Uart->LCR &= ~UART_LCR_DLAB;
}

uint32_t Uart_GetLastError(uint8_t UartID)
{
    return prvUart[UartID].LastError;
}

void Uart_IrqOnOff(uint8_t UartID, uint8_t OnOff)
{
    ISR_OnOff(prvUart[UartID].IrqLine, OnOff);
}
