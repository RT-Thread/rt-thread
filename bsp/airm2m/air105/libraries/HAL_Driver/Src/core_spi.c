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

#define HSPIM_CR0_CLEAR_MASK                                        ((uint32_t)~0xFFEEFFFF)
#define HSPIM_CR0_MODE_SELECT_CLEAR_MASK                            ((uint32_t)~0x1C00)
#define HSPIM_CR1_CLEAR_MASK                                        ((uint32_t)~0xFFFFF)
#define HSPIM_FCR_CLEAR_MASK                                        ((uint32_t)~0x3F3F3F00)
#define HSPIM_DCR_RECEIVE_LEVEL_CLEAR_MASK                          ((uint32_t)~0x3F80)
#define HSPIM_DCR_TRANSMIT_LEVEL_CLEAR_MASK                         ((uint32_t)~0x7F)


#define HSPIM_CR0_PARAM_ENABLE_POS                                  (0x18)
#define HSPIM_CR0_PARAM_DMA_RECEIVE_ENABLE_POS                      (0x14)
#define HSPIM_CR0_PARAM_DMA_TRANSMIT_ENABLE_POS                     (0x10)
#define HSPIM_CR0_PARAM_INTERRPUT_RX_POS                            (0x0F)
#define HSPIM_CR0_PARAM_INTERRPUT_TX_POS                            (0x0E)
#define HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS                        (0x0D)
#define HSPIM_CR0_PARAM_MODEL_SELECT_POS                            (0x0A)
#define HSPIM_CR0_PARAM_FIRST_BIT_POS                               (0x09)
#define HSPIM_CR0_PARAM_CPOL_POS                                    (0x08)
#define HSPIM_CR0_PARAM_CPHA_POS                                    (0x07)
#define HSPIM_CR0_PARAM_DIVIDE_ENABLE_POS                           (0x02)
#define HSPIM_CR0_PARAM_TRANSMIT_ENABLE_POS                         (0x01)
#define HSPIM_CR0_PARAM_BUSY_POS                                    (0x00)

#define HSPIM_CR1_PARAM_BAUDRATE_POS                                (0x0A)
#define HSPIM_CR1_PARAM_RECEIVE_DATA_LENGTH_POS                     (0x00)

#define HSPIM_DCR_PARAM_DMA_RECEIVE_LEVEL_POS                       (0x07)
#define HSPIM_DCR_PARAM_DMA_TRANSMIT_LEVEL_POS                      (0x00)

#define HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS         (0x08)
#define HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS            (0x10)

#define HSPIM_SR_PUSH_FULL_TX                               (1 << 4)
#define HSPIM_SR_POP_EMPTY_RX                               (1 << 10)
#define HSPIM_FIFO_TX_NUM                                   (64)
#define HSPIM_FIFO_RX_NUM                                   (64)
#define HSPIM_FIFO_LEVEL                                    (48)

#define SPIM_FIFO_TX_NUM                                    (16)
#define SPIM_FIFO_RX_NUM                                    (16)
#define SPIM_FIFO_RX_LEVEL                                  (7)
#define SPIM_FIFO_TX_LEVEL                                  (8)
typedef struct
{
    const volatile void *RegBase;
    const int32_t IrqLine;
    const uint16_t DMATxChannel;
    const uint16_t DMARxChannel;
    CBFuncEx_t Callback;
    void *pParam;
    HANDLE Sem;
    Buffer_Struct TxBuf;
    Buffer_Struct RxBuf;
    uint32_t Speed;
    uint8_t DMATxStream;
    uint8_t DMARxStream;
    uint8_t Is16Bit;
    uint8_t IsOnlyTx;
    uint8_t IsBusy;
    uint8_t IsBlockMode;
}SPI_ResourceStruct;

static SPI_ResourceStruct prvSPI[SPI_MAX] = {
        {
                HSPIM,
                SPI5_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_HSPI_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_HSPI_RX,
        },
        {
                SPIM0,
                SPI0_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI0_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI0_RX,
        },
        {
                SPIM1,
                SPI1_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI1_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI1_RX,
        },
        {
                SPIM2,
                SPI2_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI2_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI2_RX,
        },
        {
                SPIS0,
                SPI0_IRQn,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI0_TX,
                SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI0_RX,
        },
};

static void HSPI_IrqHandle(int32_t IrqLine, void *pData)
{
    uint32_t SpiID = HSPI_ID0;
    uint32_t RxLevel, i, TxLen;
    HSPIM_TypeDef *SPI = HSPIM;
    volatile uint32_t DummyData;
    if (!prvSPI[SpiID].IsBusy)
    {

        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        return;
    }
    if (prvSPI[SpiID].RxBuf.Data)
    {
        while (prvSPI[SpiID].RxBuf.Pos < prvSPI[SpiID].RxBuf.MaxLen)
        {
            if (SPI->SR & HSPIM_SR_POP_EMPTY_RX)
            {
                break;
            }
            else
            {
                prvSPI[SpiID].RxBuf.Data[prvSPI[SpiID].RxBuf.Pos] = SPI->RDR;
                prvSPI[SpiID].RxBuf.Pos++;
            }
        }
    }
    else
    {
        while (prvSPI[SpiID].RxBuf.Pos < prvSPI[SpiID].RxBuf.MaxLen)
        {
            if (SPI->SR & HSPIM_SR_POP_EMPTY_RX)
            {
                break;
            }
            else
            {
                DummyData = SPI->RDR;
                prvSPI[SpiID].RxBuf.Pos++;
            }
        }
    }


    if (prvSPI[SpiID].RxBuf.Pos >= prvSPI[SpiID].RxBuf.MaxLen)
    {
        SPI->CR0 &= ~(7 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        prvSPI[SpiID].IsBusy = 0;
        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        if ((prvSPI[SpiID].TxBuf.Pos != prvSPI[SpiID].RxBuf.Pos) || (prvSPI[SpiID].RxBuf.Pos != prvSPI[SpiID].RxBuf.MaxLen))
        {
            DBG("%u, %u", prvSPI[SpiID].TxBuf.Pos, prvSPI[SpiID].RxBuf.Pos);
        }
#ifdef __BUILD_OS__
        if (prvSPI[SpiID].IsBlockMode)
        {
            OS_MutexRelease(prvSPI[SpiID].Sem);
        }
#endif
        prvSPI[SpiID].Callback((void *)SpiID, prvSPI[SpiID].pParam);
        return;
    }

    if (prvSPI[SpiID].TxBuf.Pos < prvSPI[SpiID].TxBuf.MaxLen)
    {
        i = 0;
        TxLen = (HSPIM_FIFO_TX_NUM - (SPI->FSR & 0x0000003f));
        if (TxLen > (prvSPI[SpiID].TxBuf.MaxLen -prvSPI[SpiID].TxBuf.Pos))
        {
            TxLen = prvSPI[SpiID].TxBuf.MaxLen - prvSPI[SpiID].TxBuf.Pos;
        }
        while((i < TxLen))
        {
            SPI->WDR = prvSPI[SpiID].TxBuf.Data[prvSPI[SpiID].TxBuf.Pos + i];
            i++;
        }
        prvSPI[SpiID].TxBuf.Pos += TxLen;
        if (prvSPI[SpiID].TxBuf.Pos >= prvSPI[SpiID].TxBuf.MaxLen)
        {
            SPI->FCR = (63 << HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS)|(0 << HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS)|(63);
            SPI->CR0 &= ~(7 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
            SPI->CR0 |= (5 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        }
    }
    else
    {
        SPI->FCR = (63 << HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS)|(0 << HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS)|(63);
        SPI->CR0 &= ~(7 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        SPI->CR0 |= (5 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
    }
}

static int32_t SPI_DMADoneCB(void *pData, void *pParam)
{
    uint32_t SpiID = (uint32_t)pData;
    uint32_t RxLevel;

    if (prvSPI[SpiID].RxBuf.MaxLen > prvSPI[SpiID].RxBuf.Pos)
    {
        RxLevel = ((prvSPI[SpiID].RxBuf.MaxLen -  prvSPI[SpiID].RxBuf.Pos) > 4080)?4000:(prvSPI[SpiID].RxBuf.MaxLen -  prvSPI[SpiID].RxBuf.Pos);

        DMA_ClearStreamFlag(prvSPI[SpiID].DMATxStream);

        DMA_ClearStreamFlag(prvSPI[SpiID].DMARxStream);

        if (prvSPI[SpiID].IsOnlyTx)
        {
            DMA_ForceStartStream(prvSPI[SpiID].DMATxStream, &prvSPI[SpiID].TxBuf.Data[prvSPI[SpiID].TxBuf.Pos], RxLevel, SPI_DMADoneCB, (void *)SpiID, 1);
            DMA_ForceStartStream(prvSPI[SpiID].DMARxStream, &prvSPI[SpiID].RxBuf.Data[prvSPI[SpiID].RxBuf.Pos], RxLevel, NULL, NULL, 0);
        }
        else
        {
            DMA_ForceStartStream(prvSPI[SpiID].DMATxStream, &prvSPI[SpiID].TxBuf.Data[prvSPI[SpiID].TxBuf.Pos], RxLevel, NULL, NULL, 0);
            DMA_ForceStartStream(prvSPI[SpiID].DMARxStream, &prvSPI[SpiID].RxBuf.Data[prvSPI[SpiID].RxBuf.Pos], RxLevel, SPI_DMADoneCB, (void *)SpiID, 1);
        }
        prvSPI[SpiID].RxBuf.Pos += RxLevel;
        prvSPI[SpiID].TxBuf.Pos += RxLevel;
    }

    else
    {
        prvSPI[SpiID].IsBusy = 0;
        if ((prvSPI[SpiID].TxBuf.Pos != prvSPI[SpiID].RxBuf.Pos) || (prvSPI[SpiID].RxBuf.Pos != prvSPI[SpiID].RxBuf.MaxLen))
        {
            DBG("%u, %u", prvSPI[SpiID].TxBuf.Pos, prvSPI[SpiID].RxBuf.Pos);
        }
#ifdef __BUILD_OS__
        if (prvSPI[SpiID].IsBlockMode)
        {
            OS_MutexRelease(prvSPI[SpiID].Sem);
        }
#endif
        prvSPI[SpiID].Callback((void *)SpiID, prvSPI[SpiID].pParam);
    }


}

static void SPI_IrqHandle(int32_t IrqLine, void *pData)
{
    uint32_t SpiID = (uint32_t)pData;
    volatile uint32_t DummyData;
    uint32_t RxLevel, SR, i, TxLen;
    SPI_TypeDef *SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
    if (!prvSPI[SpiID].IsBusy)
    {
        SR = SPI->ICR;
        SPI->IMR = 0;
        SPI->SER = 0;
        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        return;
    }
    TxLen = SPIM_FIFO_TX_NUM - SPI->TXFLR;

    SR = SPI->ICR;
    if (prvSPI[SpiID].RxBuf.Data)
    {
        while(SPI->RXFLR)
        {
            prvSPI[SpiID].RxBuf.Data[prvSPI[SpiID].RxBuf.Pos] = SPI->DR;
            prvSPI[SpiID].RxBuf.Pos++;
        }
    }
    else
    {
        while(SPI->RXFLR)
        {
            DummyData = SPI->DR;
            prvSPI[SpiID].RxBuf.Pos++;
        }
    }

    if (prvSPI[SpiID].RxBuf.Pos >= prvSPI[SpiID].RxBuf.MaxLen)
    {

        SR = SPI->ICR;
        SPI->IMR = 0;
        SPI->SER = 0;
        prvSPI[SpiID].IsBusy = 0;
        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        if (prvSPI[SpiID].TxBuf.Pos != prvSPI[SpiID].RxBuf.Pos)
        {
            DBG("%u, %u", prvSPI[SpiID].TxBuf.Pos, prvSPI[SpiID].RxBuf.Pos);
        }
#ifdef __BUILD_OS__
        if (prvSPI[SpiID].IsBlockMode)
        {
            OS_MutexRelease(prvSPI[SpiID].Sem);
        }
#endif
        prvSPI[SpiID].Callback((void *)SpiID, prvSPI[SpiID].pParam);
        return;
    }

    if (prvSPI[SpiID].TxBuf.Pos < prvSPI[SpiID].TxBuf.MaxLen)
    {
        i = 0;
        if (TxLen > (prvSPI[SpiID].TxBuf.MaxLen -prvSPI[SpiID].TxBuf.Pos))
        {
            TxLen = prvSPI[SpiID].TxBuf.MaxLen - prvSPI[SpiID].TxBuf.Pos;
        }
        while((i < TxLen))
        {
            SPI->DR = prvSPI[SpiID].TxBuf.Data[prvSPI[SpiID].TxBuf.Pos + i];
            i++;
        }
        prvSPI[SpiID].TxBuf.Pos += i;
    }
    else
    {

        if ((prvSPI[SpiID].RxBuf.MaxLen - prvSPI[SpiID].RxBuf.Pos) >= SPIM_FIFO_RX_NUM)
        {
            SPI->RXFTLR = (SPIM_FIFO_RX_NUM - 1);
        }
        else
        {
            SPI->RXFTLR = prvSPI[SpiID].RxBuf.MaxLen - prvSPI[SpiID].RxBuf.Pos - 1;
        }
        SPI->IMR = SPI_IMR_RXOIM|SPI_IMR_RXFIM;
    }
}

static int32_t SPI_DummyCB(void *pData, void *pParam)
{
    return 0;
}

static void HSPI_MasterInit(uint8_t SpiID, uint8_t Mode, uint32_t Speed)
{
    HSPIM_TypeDef *SPI = (HSPIM_TypeDef *)prvSPI[SpiID].RegBase;
    uint32_t div = (SystemCoreClock / Speed) >> 1;
    uint32_t ctrl = (1 << 24) | (1 << 10) | (1 << 2) | (1 << 1);
    switch(Mode)
    {
    case SPI_MODE_0:
        break;
    case SPI_MODE_1:
        ctrl |= (1 << HSPIM_CR0_PARAM_CPHA_POS);
        break;
    case SPI_MODE_2:
        ctrl |= (1 << HSPIM_CR0_PARAM_CPOL_POS);
        break;
    case SPI_MODE_3:
        ctrl |= (1 << HSPIM_CR0_PARAM_CPOL_POS)|(1 << HSPIM_CR0_PARAM_CPHA_POS);
        break;
    }
    SPI->CR1 = (div << HSPIM_CR1_PARAM_BAUDRATE_POS) + 1;
    SPI->CR0 = ctrl;
    SPI->DCR = 30|(1 << 7);
    prvSPI[SpiID].Speed = (SystemCoreClock >> 1) / div;

    ISR_SetHandler(prvSPI[SpiID].IrqLine, HSPI_IrqHandle, (uint32_t)SpiID);
#ifdef __BUILD_OS__
    ISR_SetPriority(prvSPI[SpiID].IrqLine, IRQ_MAX_PRIORITY + 1);
#else
    ISR_SetPriority(prvSPI[SpiID].IrqLine, 3);
#endif
    ISR_Clear(prvSPI[SpiID].IrqLine);
    ISR_OnOff(prvSPI[SpiID].IrqLine, 0);

}

void SPI_MasterInit(uint8_t SpiID, uint8_t DataBit, uint8_t Mode, uint32_t Speed, CBFuncEx_t CB, void *pUserData)
{
    SPI_TypeDef *SPI;
    uint32_t ctrl;
    uint32_t div;
    switch(SpiID)
    {
    case HSPI_ID0:
        HSPI_MasterInit(SpiID, Mode, Speed);
        break;
    case SPI_ID0:
        SYSCTRL->PHER_CTRL &= ~SYSCTRL_PHER_CTRL_SPI0_SLV_EN;
    case SPI_ID1:
    case SPI_ID2:
        SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
        SPI->SSIENR = 0;
        SPI->SER = 0;
        SPI->IMR = 0;
        SPI->DMACR = 0;
        ctrl = DataBit - 1;
        switch(Mode)
        {
        case SPI_MODE_0:
            break;
        case SPI_MODE_1:
            ctrl |= SPI_CTRLR0_SCPH;
            break;
        case SPI_MODE_2:
            ctrl |= SPI_CTRLR0_SCPOL;
            break;
        case SPI_MODE_3:
            ctrl |= SPI_CTRLR0_SCPOL|SPI_CTRLR0_SCPH;
            break;
        }
        div = (SystemCoreClock >> 2) / Speed;
        if (div % 2) div++;
        prvSPI[SpiID].Speed = (SystemCoreClock >> 2) / div;
        SPI->CTRLR0 = ctrl;
        SPI->BAUDR = div;
        SPI->TXFTLR = 0;
        SPI->RXFTLR = 0;
        SPI->DMATDLR = 7;
        SPI->DMARDLR = 0;
        ISR_SetHandler(prvSPI[SpiID].IrqLine, SPI_IrqHandle, (uint32_t)SpiID);
#ifdef __BUILD_OS__
        ISR_SetPriority(prvSPI[SpiID].IrqLine, IRQ_LOWEST_PRIORITY - 2);
#else
        ISR_SetPriority(prvSPI[SpiID].IrqLine, 5);
#endif
        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        SPI->SSIENR = 1;
        break;
//  case SPI_ID3:
//      SYSCTRL->PHER_CTRL |= SYSCTRL_PHER_CTRL_SPI0_SLV_EN;
//      break;
    default:
        return;
    }
    prvSPI[SpiID].DMATxStream = 0xff;
    prvSPI[SpiID].DMARxStream = 0xff;
    if (CB)
    {
        prvSPI[SpiID].Callback = CB;
    }
    else
    {
        prvSPI[SpiID].Callback = SPI_DummyCB;
    }
    prvSPI[SpiID].pParam = pUserData;
#ifdef __BUILD_OS__
    if (!prvSPI[SpiID].Sem)
    {
        prvSPI[SpiID].Sem = OS_MutexCreate();
    }
#endif
}


void SPI_SetTxOnlyFlag(uint8_t SpiID, uint8_t OnOff)
{
    prvSPI[SpiID].IsOnlyTx = OnOff;
}

void SPI_SetCallbackFun(uint8_t SpiID, CBFuncEx_t CB, void *pUserData)
{
    if (CB)
    {
        prvSPI[SpiID].Callback = CB;
    }
    else
    {
        prvSPI[SpiID].Callback = SPI_DummyCB;
    }
    prvSPI[SpiID].pParam = pUserData;
}


static void SPI_DMATransfer(uint8_t SpiID, uint8_t UseDMA)
{
    uint32_t RxLevel;

    RxLevel = (prvSPI[SpiID].RxBuf.MaxLen > 4080)?4000:prvSPI[SpiID].RxBuf.MaxLen;
    prvSPI[SpiID].RxBuf.Pos += RxLevel;
    prvSPI[SpiID].TxBuf.Pos += RxLevel;
    DMA_StopStream(prvSPI[SpiID].DMATxStream);
    DMA_StopStream(prvSPI[SpiID].DMARxStream);
    if (prvSPI[SpiID].IsOnlyTx)
    {
        DMA_ForceStartStream(prvSPI[SpiID].DMATxStream, prvSPI[SpiID].TxBuf.Data, RxLevel, SPI_DMADoneCB, (void *)SpiID, 1);
        DMA_ForceStartStream(prvSPI[SpiID].DMARxStream, prvSPI[SpiID].RxBuf.Data, RxLevel, NULL, NULL, 0);
    }
    else
    {
        DMA_ForceStartStream(prvSPI[SpiID].DMATxStream, prvSPI[SpiID].TxBuf.Data, RxLevel, NULL, NULL, 0);
        DMA_ForceStartStream(prvSPI[SpiID].DMARxStream, prvSPI[SpiID].RxBuf.Data, RxLevel, SPI_DMADoneCB, (void *)SpiID, 1);
    }


}

static int32_t HSPI_Transfer(uint8_t SpiID, uint8_t UseDMA)
{
    HSPIM_TypeDef *SPI = (HSPIM_TypeDef *)prvSPI[SpiID].RegBase;
    uint32_t TxLen, i;
    if (UseDMA)
    {
        SPI->CR0 &= ~(7 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        SPI->CR0 |= (1 << HSPIM_CR0_PARAM_DMA_TRANSMIT_ENABLE_POS)|(1 << HSPIM_CR0_PARAM_DMA_RECEIVE_ENABLE_POS);
        SPI->FCR = (32 << HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS)|(0 << HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS)|(3 << 6)|(63);
        SPI->FCR &= ~(3 << 6);
        SPI_DMATransfer(SpiID, UseDMA);
    }
    else
    {
        SPI->CR0 &= ~(7 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
//      SPI->CR0 &= ~(1 << 10);
        SPI->CR0 &= ~((1 << HSPIM_CR0_PARAM_DMA_TRANSMIT_ENABLE_POS)|(1 << HSPIM_CR0_PARAM_DMA_RECEIVE_ENABLE_POS));



        if (prvSPI[SpiID].TxBuf.MaxLen <= HSPIM_FIFO_TX_NUM)
        {
            TxLen = prvSPI[SpiID].TxBuf.MaxLen;
            SPI->FCR = (32 << HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS)|((TxLen - 1) << HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS)|(3 << 6)|(63);
            SPI->CR0 |= (5 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        }
        else
        {
            TxLen = HSPIM_FIFO_TX_NUM;
            SPI->FCR = (32 << HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS)|(63 << HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS)|(3 << 6)|(63);
            SPI->CR0 |= (3 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        }

        SPI->FCR &= ~(3 << 6);

        for(i = 0; i < TxLen; i++)
        {
            SPI->WDR = prvSPI[SpiID].TxBuf.Data[i];
        }
        prvSPI[SpiID].TxBuf.Pos += TxLen;
//      SPI->CR0 |= (1 << 10);
        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 1);
        return ERROR_NONE;
    }
    return ERROR_NONE;
}

int32_t SPI_Transfer(uint8_t SpiID, const uint8_t *TxData, uint8_t *RxData, uint32_t Len, uint8_t UseDMA)
{
    uint32_t SR;
    SPI_TypeDef *SPI;
    if (prvSPI[SpiID].IsBusy)
    {
        return -ERROR_DEVICE_BUSY;
    }
    prvSPI[SpiID].IsBusy = 1;
//
    uint32_t RxLevel, i, TxLen;
    Buffer_StaticInit(&prvSPI[SpiID].TxBuf, TxData, Len);
    Buffer_StaticInit(&prvSPI[SpiID].RxBuf, RxData, Len);
    switch(SpiID)
    {
    case HSPI_ID0:
        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        return HSPI_Transfer(SpiID, UseDMA);
    case SPI_ID0:
        SYSCTRL->PHER_CTRL &= ~SYSCTRL_PHER_CTRL_SPI0_SLV_EN;
    case SPI_ID1:
    case SPI_ID2:
        break;
//  case SPI_ID3:
//      SYSCTRL->PHER_CTRL |= SYSCTRL_PHER_CTRL_SPI0_SLV_EN;
//      break;
    default:
        return -ERROR_ID_INVALID;
    }
    SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
    SPI->SER = 0;
    if (UseDMA)
    {

        SR = SPI->ICR;
        SPI->IMR = 0;
        SPI->DMACR = SPI_DMACR_RDMAE|SPI_DMACR_TDMAE;
        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        SPI->SER = 1;
        SPI_DMATransfer(SpiID, 1);

    }
    else
    {
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);

        if (prvSPI[SpiID].RxBuf.MaxLen <= SPIM_FIFO_RX_NUM)
        {
            SPI->RXFTLR = prvSPI[SpiID].RxBuf.MaxLen - 1;
            TxLen = prvSPI[SpiID].RxBuf.MaxLen;
            SPI->IMR = SPI_IMR_RXOIM|SPI_IMR_RXFIM;
        }
        else
        {
            SPI->IMR = SPI_IMR_TXEIM;
            SPI->RXFTLR = SPIM_FIFO_RX_LEVEL;
            SPI->TXFTLR = SPIM_FIFO_TX_LEVEL;
            TxLen = SPIM_FIFO_TX_NUM;
        }
        for(i = 0; i < TxLen; i++)
        {
            SPI->DR = prvSPI[SpiID].TxBuf.Data[i];
        }
        prvSPI[SpiID].TxBuf.Pos += TxLen;
        ISR_Clear(prvSPI[SpiID].IrqLine);
        ISR_OnOff(prvSPI[SpiID].IrqLine, 1);
    }
    SPI->SER = 1;

    return ERROR_NONE;
}


static int32_t prvSPI_BlockTransfer(uint8_t SpiID, const uint8_t *TxData, uint8_t *RxData, uint32_t Len)
{
    volatile uint32_t DummyData;
    uint32_t TxLen, RxLen, i, To;
    HSPIM_TypeDef *HSPI;
    SPI_TypeDef *SPI;
    prvSPI[SpiID].IsBusy = 1;
    switch(SpiID)
    {
    case HSPI_ID0:
        HSPI = (HSPIM_TypeDef *)prvSPI[SpiID].RegBase;
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        HSPI->FCR = (32 << HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS)|(32 << HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS)|(3 << 6)|(63);
        HSPI->FCR &= ~(3 << 6);
        HSPI->CR0 &= ~(7 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        if (Len <= HSPIM_FIFO_TX_NUM)
        {
            TxLen = Len;
        }
        else
        {
            TxLen = HSPIM_FIFO_TX_NUM;
        }
        for(i = 0; i < TxLen; i++)
        {
            HSPI->WDR = TxData[i];
        }
        if (RxData)
        {
            for(RxLen = 0; RxLen < Len; RxLen++)
            {
                while (HSPI->SR & HSPIM_SR_POP_EMPTY_RX)
                {
                    ;
                }
                RxData[RxLen] = HSPI->RDR;
                if (TxLen < Len)
                {
                    HSPI->WDR = TxData[TxLen];
                    TxLen++;
                }
            }
        }
        else
        {
            while(TxLen < Len)
            {
                while ((HSPI->FSR & 0x7f) > 16)
                {
                    ;
                }
                HSPI->WDR = TxData[TxLen];
                TxLen++;
            }
            while ((HSPI->FSR & 0x7f))
            {
                ;
            }
//          for(RxLen = 0; RxLen < Len; RxLen++)
//          {
//              while (HSPI->SR & HSPIM_SR_POP_EMPTY_RX)
//              {
//                  ;
//              }
//              DummyData = HSPI->RDR;
//              if (TxLen < Len)
//              {
//                  HSPI->WDR = TxData[TxLen];
//                  TxLen++;
//              }
//          }
        }
        break;
    case SPI_ID0:
    case SPI_ID1:
    case SPI_ID2:
        SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        SPI->SER = 0;
        if (Len <= SPIM_FIFO_TX_NUM)
        {
            TxLen = Len;
        }
        else
        {
            TxLen = SPIM_FIFO_TX_NUM;
        }
        for(i = 0; i < TxLen; i++)
        {
            SPI->DR = TxData[i];
        }
        SPI->SER = 1;
        if (RxData)
        {
            for(RxLen = 0; RxLen < Len; RxLen++)
            {
                while (!SPI->RXFLR)
                {
                    ;
                }
                RxData[RxLen] = SPI->DR;
                if (TxLen < Len)
                {
                    SPI->DR = TxData[TxLen];
                    TxLen++;
                }
            }
        }
        else
        {
            for(RxLen = 0; RxLen < Len; RxLen++)
            {
                while (!SPI->RXFLR)
                {
                    ;
                }
                DummyData = SPI->DR;
                if (TxLen < Len)
                {
                    SPI->DR = TxData[TxLen];
                    TxLen++;
                }
            }
        }
        SPI->SER = 0;
        break;
    }
    prvSPI[SpiID].IsBusy = 0;
    prvSPI[SpiID].Callback((void *)SpiID, prvSPI[SpiID].pParam);
    return 0;
}

int32_t SPI_BlockTransfer(uint8_t SpiID, const uint8_t *TxData, uint8_t *RxData, uint32_t Len)
{
#ifdef __BUILD_OS__
    if ( (prvSPI[SpiID].DMARxStream == 0xff) || (prvSPI[SpiID].DMATxStream == 0xff) || OS_CheckInIrq() || ((prvSPI[SpiID].Speed >> 3) >= (Len * 100000)))
    {
        prvSPI[SpiID].IsBlockMode = 0;
#endif
        return prvSPI_BlockTransfer(SpiID, TxData, RxData, Len);
#ifdef __BUILD_OS__
    }
    int32_t Result;
    uint32_t Time = (Len * 1000) / (prvSPI[SpiID].Speed >> 3);
    prvSPI[SpiID].IsBlockMode = 1;
    if (TxData)
    {
        Result = SPI_Transfer(SpiID, TxData, RxData, Len, 1);
    }
    else
    {
        Result = SPI_Transfer(SpiID, RxData, RxData, Len, 1);
    }
    if (Result)
    {
        prvSPI[SpiID].IsBlockMode = 0;
        DBG("!");
        return Result;
    }
    if (OS_MutexLockWtihTime(prvSPI[SpiID].Sem, Time + 10))
    {
        DBG("!!!");
        SPI_TransferStop(SpiID);
        prvSPI[SpiID].IsBlockMode = 0;
        return -1;
    }
    prvSPI[SpiID].IsBlockMode = 0;
    return 0;
#endif
}


static int32_t prvSPI_FlashBlockTransfer(uint8_t SpiID, const uint8_t *TxData, uint32_t WLen, uint8_t *RxData, uint32_t RLen)
{
    volatile uint32_t DummyData;
    uint32_t TxLen, RxLen, i;
    HSPIM_TypeDef *HSPI;
    SPI_TypeDef *SPI;
    prvSPI[SpiID].IsBusy = 1;
    switch(SpiID)
    {
    case HSPI_ID0:
        HSPI = (HSPIM_TypeDef *)prvSPI[SpiID].RegBase;

        HSPI->FCR = (32 << HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS)|(32 << HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS)|(3 << 6)|(63);
        HSPI->FCR &= ~(3 << 6);
        HSPI->CR0 &= ~(7 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        if (WLen <= HSPIM_FIFO_TX_NUM)
        {
            TxLen = WLen;
        }
        else
        {
            TxLen = HSPIM_FIFO_TX_NUM;
        }
        for(i = 0; i < TxLen; i++)
        {
            HSPI->WDR = TxData[i];
        }
        for(RxLen = 0; RxLen < WLen; RxLen++)
        {
            while (HSPI->SR & HSPIM_SR_POP_EMPTY_RX)
            {
                ;
            }
            DummyData = HSPI->RDR;
            if (TxLen < WLen)
            {
                HSPI->WDR = TxData[TxLen];
                TxLen++;
            }
        }
        if (RLen <= HSPIM_FIFO_TX_NUM)
        {
            TxLen = RLen;
        }
        else
        {
            TxLen = HSPIM_FIFO_TX_NUM;
        }
        for(i = 0; i < TxLen; i++)
        {
            HSPI->WDR = TxData[i];
        }
        for(RxLen = 0; RxLen < RLen; RxLen++)
        {
            while (HSPI->SR & HSPIM_SR_POP_EMPTY_RX)
            {
                ;
            }
            RxData[RxLen] = HSPI->RDR;
            if (TxLen < RLen)
            {
                HSPI->WDR = 0xff;
                TxLen++;
            }
        }

        break;
    case SPI_ID0:
    case SPI_ID1:
    case SPI_ID2:
        SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
        ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
        SPI->SER = 0;
        if (WLen <= SPIM_FIFO_TX_NUM)
        {
            TxLen = WLen;
        }
        else
        {
            TxLen = SPIM_FIFO_TX_NUM;
        }
        for(i = 0; i < TxLen; i++)
        {
            SPI->DR = TxData[i];
        }
        SPI->SER = 1;
        for(RxLen = 0; RxLen < WLen; RxLen++)
        {
            while (!SPI->RXFLR)
            {
                ;
            }
            DummyData = SPI->DR;
            if (TxLen < WLen)
            {
                SPI->DR = TxData[TxLen];
                TxLen++;
            }
        }
        if (RLen <= SPIM_FIFO_TX_NUM)
        {
            TxLen = RLen;
        }
        else
        {
            TxLen = SPIM_FIFO_TX_NUM;
        }
        for(i = 0; i < TxLen; i++)
        {
            SPI->DR = TxData[i];
        }

        for(RxLen = 0; RxLen < RLen; RxLen++)
        {
            while (!SPI->RXFLR)
            {
                ;
            }
            RxData[RxLen] = SPI->DR;
            if (TxLen < RLen)
            {
                SPI->DR = 0xff;
                TxLen++;
            }
        }
        SPI->SER = 0;
        break;
    }
    prvSPI[SpiID].IsBusy = 0;
    prvSPI[SpiID].Callback((void *)SpiID, prvSPI[SpiID].pParam);
    return 0;
}

int32_t SPI_FlashBlockTransfer(uint8_t SpiID, const uint8_t *TxData, uint32_t WLen, uint8_t *RxData, uint32_t RLen)
{
#ifdef __BUILD_OS__
    if ( (prvSPI[SpiID].DMARxStream == 0xff) || (prvSPI[SpiID].DMATxStream == 0xff) || OS_CheckInIrq() || ((prvSPI[SpiID].Speed >> 3) >= ((WLen + RLen) * 100000)))
    {
        prvSPI[SpiID].IsBlockMode = 0;
#endif
        return prvSPI_FlashBlockTransfer(SpiID, TxData, WLen, RxData, RLen);
#ifdef __BUILD_OS__
    }
    int32_t Result;
    uint32_t Time = ((WLen + RLen) * 1000) / (prvSPI[SpiID].Speed >> 3);
    uint8_t *Temp = malloc(WLen + RLen);
    memcpy(Temp, TxData, WLen);
    prvSPI[SpiID].IsBlockMode = 1;

    if (TxData)
    {
        Result = SPI_Transfer(SpiID, Temp, Temp, WLen + RLen, 1);
    }
    else
    {
        Result = SPI_Transfer(SpiID, Temp, Temp, WLen + RLen, 1);
    }
    if (Result)
    {
        prvSPI[SpiID].IsBlockMode = 0;
        free(Temp);
        return Result;
    }
    if (OS_MutexLockWtihTime(prvSPI[SpiID].Sem, Time + 10))
    {
        free(Temp);
        DBG("!!!");
        DMA_StopStream(prvSPI[SpiID].DMATxStream);
        DMA_StopStream(prvSPI[SpiID].DMARxStream);
        SPI_TransferStop(SpiID);
        prvSPI[SpiID].IsBlockMode = 0;
        return -1;
    }
    memcpy(RxData, Temp + WLen, RLen);
    prvSPI[SpiID].IsBlockMode = 0;
    free(Temp);
    return 0;
#endif
}


void SPI_DMATxInit(uint8_t SpiID, uint8_t Stream, uint32_t Channel)
{
    SPI_TypeDef *SPI;
    HSPIM_TypeDef *HSPI;
    DMA_InitTypeDef DMA_InitStruct;
    DMA_BaseConfig(&DMA_InitStruct);
    DMA_InitStruct.DMA_Peripheral = prvSPI[SpiID].DMATxChannel;
    DMA_InitStruct.DMA_Priority = DMA_Priority_3;
    prvSPI[SpiID].DMATxStream = Stream;
    switch(SpiID)
    {
    case HSPI_ID0:
        HSPI = (HSPIM_TypeDef *)prvSPI[SpiID].RegBase;
        if (prvSPI[SpiID].IsOnlyTx)
        {
            DMA_InitStruct.DMA_Priority = DMA_Priority_0;
        }
        DMA_InitStruct.DMA_PeripheralBurstSize = DMA_BurstSize_32;
        DMA_InitStruct.DMA_MemoryBurstSize = DMA_BurstSize_32;
        DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&HSPI->WDR;
        break;
    case SPI_ID0:
    case SPI_ID1:
    case SPI_ID2:
        SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
        DMA_InitStruct.DMA_PeripheralBurstSize = DMA_BurstSize_8;
        DMA_InitStruct.DMA_MemoryBurstSize = DMA_BurstSize_8;
        DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&SPI->DR;
        break;
//  case SPI_ID3:
//      SYSCTRL->PHER_CTRL |= SYSCTRL_PHER_CTRL_SPI0_SLV_EN;
//      break;
    default:
        return;
    }
    DMA_ConfigStream(Stream, &DMA_InitStruct);
}
void SPI_DMARxInit(uint8_t SpiID, uint8_t Stream, uint32_t Channel)
{
    SPI_TypeDef *SPI;
    HSPIM_TypeDef *HSPI;
    DMA_InitTypeDef DMA_InitStruct;
    DMA_BaseConfig(&DMA_InitStruct);
    DMA_InitStruct.DMA_Peripheral = prvSPI[SpiID].DMARxChannel;
    DMA_InitStruct.DMA_Priority = DMA_Priority_2;
    prvSPI[SpiID].DMARxStream = Stream;
    switch(SpiID)
    {
    case HSPI_ID0:
        HSPI = (HSPIM_TypeDef *)prvSPI[SpiID].RegBase;
        DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&HSPI->RDR;
        break;
    case SPI_ID0:
    case SPI_ID1:
    case SPI_ID2:
        SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
        DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&SPI->DR;
        break;
//  case SPI_ID3:
//      SYSCTRL->PHER_CTRL |= SYSCTRL_PHER_CTRL_SPI0_SLV_EN;
//      break;
    default:
        return;
    }
    DMA_ConfigStream(Stream, &DMA_InitStruct);
}

void SPI_TransferStop(uint8_t SpiID)
{
    uint16_t Data;
    ISR_Clear(prvSPI[SpiID].IrqLine);
    ISR_OnOff(prvSPI[SpiID].IrqLine, 0);
    SPI_TypeDef *SPI;
    HSPIM_TypeDef *HSPI;
    uint32_t TxLen, i;
    DMA_StopStream(prvSPI[SpiID].DMATxStream);
    DMA_StopStream(prvSPI[SpiID].DMARxStream);
    switch(SpiID)
    {
    case HSPI_ID0:
        HSPI = (HSPIM_TypeDef *)prvSPI[SpiID].RegBase;
        HSPI->CR0 &= ~(7 << HSPIM_CR0_PARAM_INTERRPUT_ENABLE_POS);
        HSPI->FCR = (32 << HSPIM_FCR_PARAM_TRANSIMIT_FIFO_EMPTY_THRESHOULD_POS)|(32 << HSPIM_FCR_PARAM_RECEIVE_FIFO_FULL_THRESHOULD_POS)|(3 << 6)|(63);
        HSPI->FCR &= ~(3 << 6);
        break;
    case SPI_ID0:
        SYSCTRL->PHER_CTRL &= ~SYSCTRL_PHER_CTRL_SPI0_SLV_EN;
    case SPI_ID1:
    case SPI_ID2:
        SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
        while(SPI->TXFLR){;}
        while(SPI->RXFLR){Data = SPI->DR;}
        SPI->SER = 0;
        break;
//  case SPI_ID3:
//      SYSCTRL->PHER_CTRL |= SYSCTRL_PHER_CTRL_SPI0_SLV_EN;
//      break;
    default:
        return ;
    }

    prvSPI[SpiID].IsBusy = 0;

}

uint8_t SPI_IsTransferBusy(uint8_t SpiID)
{
    return prvSPI[SpiID].IsBusy;
}

void SPI_SetNewConfig(uint8_t SpiID, uint32_t Speed, uint8_t NewMode)
{
    HSPIM_TypeDef *HSPI;
    SPI_TypeDef *SPI;
    uint32_t div;
    if (prvSPI[SpiID].IsBusy) return;

    switch(SpiID)
    {
    case HSPI_ID0:
        HSPI = (HSPIM_TypeDef *)prvSPI[SpiID].RegBase;
        div = (SystemCoreClock / Speed) >> 1;
        HSPI->CR1 = (div << HSPIM_CR1_PARAM_BAUDRATE_POS) + 1;
        prvSPI[SpiID].Speed = (SystemCoreClock >> 1) / div;
        HSPI->CR0 &= ~((1 << HSPIM_CR0_PARAM_CPOL_POS)|(1 << HSPIM_CR0_PARAM_CPHA_POS));
        switch(NewMode)
        {
        case SPI_MODE_0:

            break;
        case SPI_MODE_1:
            HSPI->CR0 |= (1 << HSPIM_CR0_PARAM_CPHA_POS);
            break;
        case SPI_MODE_2:
            HSPI->CR0 |= (1 << HSPIM_CR0_PARAM_CPOL_POS);
            break;
        case SPI_MODE_3:
            HSPI->CR0 |= (1 << HSPIM_CR0_PARAM_CPOL_POS)|(1 << HSPIM_CR0_PARAM_CPHA_POS);
            break;
        }
        break;
    case SPI_ID0:
    case SPI_ID1:
    case SPI_ID2:
        SPI = (SPI_TypeDef *)prvSPI[SpiID].RegBase;
        SPI->SSIENR = 0;
        div = (SystemCoreClock >> 2) / Speed;
        if (div % 2) div++;
        prvSPI[SpiID].Speed = (SystemCoreClock >> 2) / div;
        SPI->BAUDR = div;
        SPI->CTRLR0 &= ~(SPI_CTRLR0_SCPOL|SPI_CTRLR0_SCPH);
        switch(NewMode)
        {
        case SPI_MODE_0:
            break;
        case SPI_MODE_1:
            SPI->CTRLR0 |= SPI_CTRLR0_SCPH;
            break;
        case SPI_MODE_2:
            SPI->CTRLR0 |= SPI_CTRLR0_SCPOL;
            break;
        case SPI_MODE_3:
            SPI->CTRLR0 |= SPI_CTRLR0_SCPOL|SPI_CTRLR0_SCPH;
            break;
        }
        SPI->SSIENR = 1;
        break;
    }
}
