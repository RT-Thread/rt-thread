/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_dac.h"

void DAC_Init(DAC_Type * DACx, uint32_t channel, DAC_Init_Type * init)
{
    uint32_t cr = 0u;

    cr = DACx->CR & ~(( DAC_CR_BOFF1_MASK
                      | DAC_CR_TEN1_MASK
                      | DAC_CR_TSEL1_MASK
                       ) << (channel<<4u));    /* Calculate the shift and clear the indicated bit. */

    /* Enable Output Buffer. */
    if (init->EnableOutBuf == false)
    {
        cr |= (DAC_CR_BOFF1_MASK << (channel<<4u));
    }

    /* Trigger Source. */
    if (init->TrgSource < DAC_TrgSource_None)
    {
        cr |= ((DAC_CR_TEN1_MASK | DAC_CR_TSEL1(init->TrgSource)) << (channel<<4u));
    }

    DAC->CR = cr;
}

void DAC_Enable(DAC_Type * DACx, uint32_t channel, bool enable)
{
    if (enable)
    {
        DACx->CR |= (DAC_CR_EN1_MASK << (channel << 4u));
    }
    else
    {
        DACx->CR &= ~(DAC_CR_EN1_MASK << (channel << 4u));
    }
}

uint32_t DAC_GetData(DAC_Type * DACx, uint32_t channel)
{
    uint32_t ret = 0u;

    if(channel == DAC_CHN_1)
    {
        ret = (DACx->DOR1 & DAC_DOR1_DACC1DOR_MASK);
    }
    else if (channel == DAC_CHN_2)
    {
        ret = (DACx->DOR2 & DAC_DOR2_DACC2DOR_MASK);
    }

    return ret;
}

uint32_t DAC_PutData(DAC_Type * DACx, uint32_t channel, uint32_t value, DAC_Align_Type align)
{
    uint32_t ret = 0u;

    switch (align)
    {
        case DAC_Align_8b_Dual:
        {
            DAC_PutDualChannelData8bRightAlign(DACx, value);
            ret = DAC_GetData(DACx, DAC_CHN_1) | ( DAC_GetData(DACx, DAC_CHN_2) << 16u);
            break;
        }
        case DAC_Align_8b_Right:
        {
            DAC_PutData8bRightAlign(DACx, channel, value);
            ret = DAC_GetData(DACx, channel);
            break;
        }
        case DAC_Align_12b_Left:
        {
            DAC_PutData12bLeftAlign(DACx, channel, value);
            ret = DAC_GetData(DACx, channel);
            break;
        }
        case DAC_Align_12b_Right:
        {
            DAC_PutData12bRightAlign(DACx, channel, value);
            ret = DAC_GetData(DACx, channel);
            break;
        }
        case DAC_Align_12b_Dual_Left:
        {
            DAC_PutDualChannelData12bLeftAlign(DACx, value);
            ret = DAC_GetData(DACx, DAC_CHN_1)
                | ( DAC_GetData(DACx, DAC_CHN_2) << 16u);
            break;
        }
        case DAC_Align_12b_Dual_Right:
        {
            DAC_PutDualChannelData12bRightAlign(DACx, value);
            ret =   DAC_GetData(DACx, DAC_CHN_1)
                | ( DAC_GetData(DACx, DAC_CHN_2) << 16u);
            break;
        }
        default:
            break;
    }
    return ret;
}

void DAC_EnableAddNoise(DAC_Type * DACx, uint32_t channel, DAC_AddNoise_Init_Type * init)
{
    if (init == NULL)
    {
        DAC->CR &=  ~(DAC_CR_WAVE1_MASK << (channel << 4u));
    }
    else
    {
        DAC->CR |= (( DAC_CR_WAVE1(1u) /* Noise wave need to set WAVEx = 01. */
                   |  DAC_CR_MAMP1(init->AddNoise)
                   ) << (channel << 4u));
    }
}

void DAC_EnableAddTriangle(DAC_Type * DACx, uint32_t channel, DAC_AddTriangle_Init_Type * init)
{
    if (init == NULL)
    {
        DAC->CR &=  ~(DAC_CR_WAVE1_MASK << (channel << 4u));
    }
    else
    {
        DAC->CR |= (( DAC_CR_WAVE1(2u) /* Noise wave need to set WAVEx = 1x. */
                   |  DAC_CR_MAMP1(init->AddTriangle)
                   ) << (channel << 4u));
    }
}

void DAC_EnableDMA(DAC_Type * DACx, uint32_t channel, bool enable)
{
    if (enable)
    {
        DACx->CR |= (DAC_CR_DMAEN1_MASK << (channel<<4u));
    }
    else
    {
        DACx->CR &= ~(DAC_CR_DMAEN1_MASK << (channel<<4u));
    }
}

void DAC_DoSwTrigger(DAC_Type * DACx, uint32_t channel)
{
    DACx->SWTRIGR |=  (DAC_SWTRIGR_SWTRIG1_MASK << channel);
}

void DAC_DoDualChannelSwTrigger(DAC_Type * DACx)
{
    DACx->SWTRIGR |= DAC_SWTRIGR_SWTRIG1_MASK
                   | DAC_SWTRIGR_SWTRIG2_MASK
                   ;
}

uint32_t DAC_GetDataRegAddr(DAC_Type * DACx, uint32_t channel, DAC_Align_Type align)
{
    uint32_t ret = 0u;

    switch (align)
    {
        case DAC_Align_8b_Dual:
        {
            ret = DAC_GetDualChannelData8bRegAddr(DACx);
            break;
        }
        case DAC_Align_8b_Right:
        {
            ret = DAC_GetData8bRegAddr(DACx, channel);
            break;
        }
        case DAC_Align_12b_Left:
        {
            ret = DAC_GetData12bLeftRegAddr(DACx, channel);
            break;
        }
        case DAC_Align_12b_Right:
        {
            ret = DAC_GetData12bRightRegAddr(DACx, channel);
            break;
        }
        case DAC_Align_12b_Dual_Left:
        {
            ret = DAC_GetDualChannelData12bLeftRegAddr(DACx);
            break;
        }
        case DAC_Align_12b_Dual_Right:
        {
            ret = DAC_GetDualChannelData12bRightRegAddr(DACx);
            break;
        }
        default:
            break;
    }
    return ret;
}

/* input value bit[7:0]. 12b output: xxxxxxxx0000. */
void DAC_PutData8bRightAlign(DAC_Type * DACx, uint32_t channel, uint32_t value)
{
    if (channel == DAC_CHN_1)
    {
        DACx->DHR8R1 = value;
    }
    else if (channel == DAC_CHN_2)
    {
        DACx->DHR8R2 = value;
    }
}

/* input value bit[15:4]. 12b output: xxxxxxxxxxxx. */
void DAC_PutData12bLeftAlign(DAC_Type * DACx, uint32_t channel, uint32_t value)
{
    if (channel == DAC_CHN_1)
    {
        DACx->DHR12L1 = value;
    }
    else if (channel == DAC_CHN_2)
    {
        DACx->DHR12L2 = value;
    }
}

/* input value bit[11:0], 12b output: xxxxxxxxxxxx. */
void DAC_PutData12bRightAlign(DAC_Type * DACx, uint32_t channel, uint32_t value)
{
    if (channel == DAC_CHN_1)
    {
        DACx->DHR12R1 = value;
    }
    else if (channel == DAC_CHN_2)
    {
        DACx->DHR12R2 = value;
    }
}

/* bit[15:8] for channel 2, bit[7:0] for channel 1. */
void DAC_PutDualChannelData8bRightAlign(DAC_Type * DACx, uint32_t value)
{
    DACx->DHR8RD = value;
}

/* bit[31:16] for channel 2, bit[15:0] for channel 1. */
void DAC_PutDualChannelData12bLeftAlign(DAC_Type * DACx, uint32_t value)
{
    DACx->DHR12LD = value;
}

/* bit[31:16] for channel 2, bit[15:0] for channel 1. */
void DAC_PutDualChannelData12bRightAlign(DAC_Type * DACx, uint32_t value)
{
    DACx->DHR12RD = value;
}

uint32_t DAC_GetData8bRegAddr(DAC_Type * DACx, uint32_t channel)
{
    uint32_t ret = 0u;

    if (channel == DAC_CHN_1)
    {
        ret = (uint32_t)(&(DACx->DHR8R1));
    }
    else if (channel == DAC_CHN_2)
    {
        ret = (uint32_t)(&(DACx->DHR8R2));
    }

    return ret;
}

uint32_t DAC_GetData12bLeftRegAddr(DAC_Type * DACx, uint32_t channel)
{
    uint32_t ret = 0u;

    if (channel == DAC_CHN_1)
    {
        ret = (uint32_t)(&(DACx->DHR12L1));
    }
    else if (channel == DAC_CHN_2)
    {
        ret = (uint32_t)(&(DACx->DHR12L2));
    }

    return ret;
}

uint32_t DAC_GetData12bRightRegAddr(DAC_Type * DACx, uint32_t channel)
{
    uint32_t ret = 0;

    if (channel == DAC_CHN_1)
    {
        ret = (uint32_t)(&(DACx->DHR12R1));
    }
    else if (channel == DAC_CHN_2)
    {
        ret = (uint32_t)(&(DACx->DHR12R2));
    }

    return ret;
}

uint32_t DAC_GetDualChannelData8bRegAddr(DAC_Type * DACx)
{
    return (uint32_t)(&(DACx->DHR8RD));
}

uint32_t DAC_GetDualChannelData12bLeftRegAddr(DAC_Type * DACx)
{
    return (uint32_t)(&(DACx->DHR12LD));
}

uint32_t DAC_GetDualChannelData12bRightRegAddr(DAC_Type * DACx)
{
    return (uint32_t)(&(DACx->DHR12RD));
}

/* EOF. */

