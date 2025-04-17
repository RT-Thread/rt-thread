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
#include "core_irq.h"
#include "user.h"
typedef struct
{
    DMA_TypeDef *RegBase;
    const uint32_t Index;
    CBFuncEx_t CB;
    void *pData;
    uint8_t TxDir;
}DMAChannal_struct;

/************ operation definition for DMA  DMA_CTL_H REGISTER ************/
#define DMA_CTL_BLOCK_TS_Pos                                (0)
#define DMA_CTL_BLOCK_TS_Mask                               (0x0fffU<<DMA_CTL_BLOCK_TS_Pos)

/************ operation definition for DMA  DMA_CTL_L REGISTER ************/
#define DMA_CTL_TT_FC_Pos                                   (20)
#define DMA_CTL_TT_FC_Mask                                  (0x07U<<DMA_CTL_TT_FC_Pos)

#define DMA_CTL_TT_FC_Memory_to_Memory_Set                  (0x00U<<DMA_CTL_TT_FC_Pos)
#define DMA_CTL_TT_FC_Memory_to_Peripheral_Set              (0x01U<<DMA_CTL_TT_FC_Pos)
#define DMA_CTL_TT_FC_Peripheral_to_Memory_Set              (0x02U<<DMA_CTL_TT_FC_Pos)
#define DMA_CTL_TT_FC_Peripheral_to_Memory_P_Set            (0x04U<<DMA_CTL_TT_FC_Pos)
#define DMA_CTL_TT_FC_Memory_to_Peripheral_P_Set            (0x06U<<DMA_CTL_TT_FC_Pos)

#define DMA_CTL_SRC_MSIZE_Pos                               (14)
#define DMA_CTL_SRC_MSIZE_Mask                              (0x07U<<DMA_CTL_SRC_MSIZE_Pos)

#define DMA_CTL_DEST_MSIZE_Pos                              (11)
#define DMA_CTL_DEST_MSIZE_Mask                             (0x07U<<DMA_CTL_DEST_MSIZE_Pos)

#define DMA_CTL_SINC_Pos                                    (9)
#define DMA_CTL_SINC_Mask                                   (0x03U<<DMA_CTL_SINC_Pos)

#define DMA_CTL_DINC_Pos                                    (7)
#define DMA_CTL_DINC_Mask                                   (0x03U<<DMA_CTL_DINC_Pos)

#define DMA_CTL_SRC_TR_WIDTH_Pos                            (4)
#define DMA_CTL_SRC_TR_WIDTH_Mask                           (0x07U<<DMA_CTL_SRC_TR_WIDTH_Pos)

#define DMA_CTL_DST_TR_WIDTH_Pos                            (1)
#define DMA_CTL_DST_TR_WIDTH_Mask                           (0x07U<<DMA_CTL_DST_TR_WIDTH_Pos)

#define DMA_CTL_INT_EN_Set                                  ((uint32_t)0x01)

/************ operation definition for DMA  DMA_CFG_L REGISTER ************/
#define DMA_CFG_HS_SEL_SRC_Pos                              (11)
#define DMA_CFG_HS_SEL_SRC_Mask                             (0x01U<<DMA_CFG_HS_SEL_SRC_Pos)/*0 HARD 1 SOFT*/

#define DMA_CFG_HS_SEL_DST_Pos                              (10)
#define DMA_CFG_HS_SEL_DST_Mask                             (0x01U<<DMA_CFG_HS_SEL_DST_Pos)

/************ operation definition for DMA  DMA_CFG_H REGISTER ************/
#define DMA_CFG_DEST_PER_Pos                                (11)
#define DMA_CFG_DEST_PER_Mask                               (0x07U<<DMA_CFG_DEST_PER_Pos)/*need write current channel num*/

#define DMA_CFG_SRC_PER_Pos                                 (7)
#define DMA_CFG_SRC_PER_Mask                                (0x07U<<DMA_CFG_SRC_PER_Pos)/*need write current channel num*/

/************ operation definition for DMA  DMA_LLP_L REGISTER ************/
#define DMAC_LLP_NEXT_LLI_MSK                                   (0x3)

static DMAChannal_struct hwDMAChannal[DMA_STREAM_QTY] = {
        {
            DMA_Channel_0,
            1 << 0,
        },
        {
            DMA_Channel_1,
            1 << 1,
        },
        {
            DMA_Channel_2,
            1 << 2,
        },
        {
            DMA_Channel_3,
            1 << 3,
        },
        {
            DMA_Channel_4,
            1 << 4,
        },
        {
            DMA_Channel_5,
            1 << 5,
        },
        {
            DMA_Channel_6,
            1 << 6,
        },
        {
            DMA_Channel_7,
            1 << 7,
        },
};

static uint8_t DMALock[(DMA_STREAM_QTY - 1)/8 + 1];

static int32_t DMA_DummyCB(void *pData, void *pParam)
{
    return 0;
}

void *DMA_TakeStream(uint8_t Stream)
{
    if (BSP_TestBit(DMALock, Stream))
    {
        return NULL;
    }
    BSP_SetBit(DMALock, Stream, 1);
    return &hwDMAChannal[Stream];
}

int DMA_CheckStreamLock(uint8_t Stream)
{
    return BSP_TestBit(DMALock, Stream);
}

void DMA_ReleaseStream(uint8_t Stream)
{
    BSP_SetBit(DMALock, Stream, 0);
}

uint8_t DMA_CheckStreamBusy(uint8_t Stream)
{
    DMA_TypeDef *hwDMA = hwDMAChannal[Stream].RegBase;
    uint32_t BaseIndex = hwDMAChannal[Stream].Index;
    if (DMA->ChEnReg_L & BaseIndex)
    {
        return 1;
    }

    return 0;
}

void DMA_BaseConfig(void *Config)
{
    DMA_InitTypeDef *DMA_InitStruct = (DMA_InitTypeDef *)Config;
    memset(DMA_InitStruct, 0, sizeof(DMA_InitTypeDef));
    DMA_InitStruct->DMA_PeripheralBurstSize = DMA_BurstSize_1;
    DMA_InitStruct->DMA_PeripheralDataSize = DMA_DataSize_Byte;
    DMA_InitStruct->DMA_PeripheralInc = DMA_Inc_Nochange;
    DMA_InitStruct->DMA_MemoryBurstSize = DMA_BurstSize_1;
    DMA_InitStruct->DMA_MemoryDataSize = DMA_DataSize_Byte;
    DMA_InitStruct->DMA_MemoryInc = DMA_Inc_Increment;
}

int DMA_ConfigStream(uint8_t Stream, void *Config)
{
    DMA_TypeDef *hwDMA = hwDMAChannal[Stream].RegBase;
    uint32_t tmpChannelxBit = hwDMAChannal[Stream].Index;
    DMA_InitTypeDef *DMA_InitStruct = (DMA_InitTypeDef *)Config;
    if (DMA->ChEnReg_L & tmpChannelxBit)
    {
        return -1;
    }
    DMA->ClearTfr_L = tmpChannelxBit;
    DMA->ClearBlock_L = tmpChannelxBit;
    DMA->ClearSrcTran_L = tmpChannelxBit;
    DMA->ClearDstTran_L = tmpChannelxBit;
    DMA->ClearErr_L = tmpChannelxBit;
    if((DMA->RawBlock_L & tmpChannelxBit) | (DMA->RawDstTran_L & tmpChannelxBit) | (DMA->RawErr_L & tmpChannelxBit) \
        | (DMA->RawSrcTran_L & tmpChannelxBit) | (DMA->RawTfr_L & tmpChannelxBit)  | (DMA->StatusBlock_L & tmpChannelxBit) \
        | (DMA->StatusDstTran_L & tmpChannelxBit) | (DMA->StatusErr_L & tmpChannelxBit) | (DMA->StatusSrcTran_L & tmpChannelxBit) \
        | (DMA->StatusTfr_L & tmpChannelxBit) )
    {
        return -1;
    }
    switch(DMA_InitStruct->DMA_Peripheral)
    {
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_LCD:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART0_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART1_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_DAC:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI0_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI1_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_SPI2_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART2_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART3_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_I2C_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_QSPI_TX:
    case SYSCTRL_PHER_CTRL_DMA_CHx_IF_HSPI_TX:
        hwDMA->SAR_L = DMA_InitStruct->DMA_MemoryBaseAddr;
        hwDMA->DAR_L = DMA_InitStruct->DMA_PeripheralBaseAddr;
        hwDMA->CTL_L = DMA_CTL_TT_FC_Memory_to_Peripheral_Set|
                (DMA_InitStruct->DMA_MemoryBurstSize << DMA_CTL_SRC_MSIZE_Pos)|
                (DMA_InitStruct->DMA_PeripheralBurstSize << DMA_CTL_DEST_MSIZE_Pos)|
                (DMA_InitStruct->DMA_MemoryInc << DMA_CTL_SINC_Pos)|
                (DMA_InitStruct->DMA_PeripheralInc << DMA_CTL_DINC_Pos)|
                (DMA_InitStruct->DMA_MemoryDataSize << DMA_CTL_SRC_TR_WIDTH_Pos)|
                (DMA_InitStruct->DMA_PeripheralDataSize << DMA_CTL_DST_TR_WIDTH_Pos);

        hwDMAChannal[Stream].TxDir = 1;
        /* hwDMA->CFG_L = (1 << 18); */
        hwDMA->CFG_L = 0;
        break;
    default:
        hwDMA->SAR_L = DMA_InitStruct->DMA_PeripheralBaseAddr;
        hwDMA->DAR_L = DMA_InitStruct->DMA_MemoryBaseAddr;
        hwDMA->CTL_L = DMA_CTL_TT_FC_Peripheral_to_Memory_Set|
                (DMA_InitStruct->DMA_PeripheralBurstSize << DMA_CTL_SRC_MSIZE_Pos)|
                (DMA_InitStruct->DMA_MemoryBurstSize << DMA_CTL_DEST_MSIZE_Pos)|
                (DMA_InitStruct->DMA_PeripheralInc << DMA_CTL_SINC_Pos)|
                (DMA_InitStruct->DMA_MemoryInc << DMA_CTL_DINC_Pos)|
                (DMA_InitStruct->DMA_PeripheralDataSize << DMA_CTL_SRC_TR_WIDTH_Pos)|
                (DMA_InitStruct->DMA_MemoryDataSize << DMA_CTL_DST_TR_WIDTH_Pos);
        hwDMAChannal[Stream].TxDir = 0;
        hwDMA->CFG_L = 0;
        break;
    }
    hwDMA->CFG_L |= DMA_InitStruct->DMA_Priority;
    hwDMA->CFG_H |= (Stream << DMA_CFG_DEST_PER_Pos) | (Stream << DMA_CFG_SRC_PER_Pos);

    if (Stream <= DMA1_STREAM_3)
    {
        tmpChannelxBit = (Stream - DMA1_STREAM_0) * 8;
        SYSCTRL->DMA_CHAN = (SYSCTRL->DMA_CHAN & ~(0x0000003f << tmpChannelxBit)) | (DMA_InitStruct->DMA_Peripheral << tmpChannelxBit);
    }
    else
    {
        tmpChannelxBit = (Stream - DMA1_STREAM_4) * 8;
        SYSCTRL->DMA_CHAN1 = (SYSCTRL->DMA_CHAN1 & ~(0x0000003f << tmpChannelxBit)) | (DMA_InitStruct->DMA_Peripheral << tmpChannelxBit);
    }
    return 0;
}

int DMA_StartStream(uint8_t Stream, const void *Data, uint32_t Len, CBFuncEx_t CB, void *pUserData, uint8_t NeedIrq)
{
    uint32_t tmpChannelxBit = hwDMAChannal[Stream].Index;
    if (DMA->ChEnReg_L & tmpChannelxBit)
    {
        return -1;
    }
    DMA_ForceStartStream(Stream, Data, Len, CB, pUserData, NeedIrq);
    return 0;
}

void DMA_ForceStartStream(uint8_t Stream, const void *Data, uint32_t Len, CBFuncEx_t CB, void *pUserData, uint8_t NeedIrq)
{
    DMA_TypeDef *hwDMA = hwDMAChannal[Stream].RegBase;
    volatile uint32_t tmpChannelxBit = hwDMAChannal[Stream].Index;
    DMA->ChEnReg_L = (tmpChannelxBit << 8);
    while(DMA->ChEnReg_L & tmpChannelxBit) {;}

    if (hwDMAChannal[Stream].TxDir)
    {
        hwDMA->SAR_L = (uint32_t)Data;
    }
    else
    {
        hwDMA->DAR_L = (uint32_t)Data;
    }
    hwDMA->CTL_H &= ~DMA_CTL_BLOCK_TS_Mask;
    hwDMA->CTL_H |= Len;

    tmpChannelxBit = (tmpChannelxBit << 8) + tmpChannelxBit;
    if (NeedIrq)
    {
        hwDMA->CTL_L |= DMA_CTL_INT_EN_Set;
    }
    else
    {
        hwDMA->CTL_L &= ~DMA_CTL_INT_EN_Set;
    }
    hwDMAChannal[Stream].pData = pUserData;
    if (CB)
    {
        hwDMAChannal[Stream].CB = CB;
    }
    else
    {
        hwDMAChannal[Stream].CB = DMA_DummyCB;
    }
    DMA->ChEnReg_L = tmpChannelxBit;
}

void DMA_ClearStreamFlag(uint8_t Stream)
{
    DMA_TypeDef *hwDMA = hwDMAChannal[Stream].RegBase;
    uint32_t tmpChannelxBit = hwDMAChannal[Stream].Index;
    DMA->ClearTfr_L = tmpChannelxBit;
    DMA->ClearBlock_L = tmpChannelxBit;
    DMA->ClearSrcTran_L = tmpChannelxBit;
    DMA->ClearDstTran_L = tmpChannelxBit;
    DMA->ClearErr_L = tmpChannelxBit;
}

void DMA_StopStream(uint8_t Stream)
{
    if (Stream >= DMA_STREAM_QTY) return;
    DMA_TypeDef *hwDMA = hwDMAChannal[Stream].RegBase;
    uint32_t tmpChannelxBit = hwDMAChannal[Stream].Index;
    DMA->ChEnReg_L = (tmpChannelxBit << 8);
    DMA->ClearTfr_L = tmpChannelxBit;
    DMA->ClearBlock_L = tmpChannelxBit;
    DMA->ClearSrcTran_L = tmpChannelxBit;
    DMA->ClearDstTran_L = tmpChannelxBit;
    DMA->ClearErr_L = tmpChannelxBit;
}

uint32_t DMA_GetRemainingDataLength(uint8_t Stream)
{
    return 0;
}

uint32_t DMA_GetDataLength(uint8_t Stream, uint32_t FirstAddress)
{
    DMA_TypeDef *hwDMA = hwDMAChannal[Stream].RegBase;
    return (hwDMA->CTL_H);
}

static void DMA_IrqHandle(int32_t IrqLine, void *pData)
{
    uint32_t i;
    /* DBG("%x", DMA->StatusTfr_L); */
    if (DMA->StatusInt_L & (1 << 0))
    {
        for(i = 0; i < DMA_STREAM_QTY; i++)
        {
            if (DMA->StatusTfr_L & (1 << i))
            {
                DMA->ClearTfr_L = (1 << i);
                hwDMAChannal[i].CB(hwDMAChannal[i].pData, 0);
            }
        }
    }
    if (DMA->StatusInt_L & (1 << 4))
    {
        for(i = 0; i < DMA_STREAM_QTY; i++)
        {
            if (DMA->StatusErr_L & (1 << i))
            {
                DMA->ClearErr_L = (1 << i);
                hwDMAChannal[i].CB(hwDMAChannal[i].pData, (void *)0xffffffff);
            }
        }
    }
    DMA->ClearBlock_L = 0x000000ff;
    DMA->ClearSrcTran_L = 0x000000ff;
    DMA->ClearDstTran_L = 0x000000ff;
}

void DMA_GlobalInit(void)
{
    ISR_SetHandler(DMA_IRQn, DMA_IrqHandle, NULL);
#ifdef __BUILD_OS__
    ISR_SetPriority(DMA_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2);
#else
    ISR_SetPriority(DMA_IRQn, 3);
#endif
    DMA->DmaCfgReg_L = 1;
    DMA->ChEnReg_L = 0x0000ff00;
    ISR_OnOff(DMA_IRQn, 1);
    DMA->MaskTfr_L = 0x0000ffff;
    DMA->MaskErr_L = 0x0000ffff;
}

void DMA_PrintReg(uint8_t Stream)
{
    DMA_TypeDef *hwDMA = hwDMAChannal[Stream].RegBase;
    DBG("%d, %d, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", Stream, hwDMAChannal[Stream].TxDir, hwDMA->SAR_L, hwDMA->DAR_L, hwDMA->CTL_H, hwDMA->CTL_L, hwDMA->CFG_L);
}

void DMA_PrintGlobalReg(void)
{
    DBG("global 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", SYSCTRL->DMA_CHAN, SYSCTRL->DMA_CHAN1, DMA->StatusTfr_L,
            DMA->StatusErr_L, DMA->ChEnReg_L, DMA->DmaCfgReg_L);
}
