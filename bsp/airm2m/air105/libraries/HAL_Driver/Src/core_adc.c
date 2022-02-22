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
#define SAMPLE_PER_CH   (15)
#if 0
typedef struct
{
    uint32_t Data[SAMPLE_PER_CH];

}Channel_DataStruct;

typedef struct
{
    Channel_DataStruct ChannelData[ADC_CHANNEL_MAX];
    uint32_t Ctrl;
    uint8_t Enable[ADC_CHANNEL_MAX];
    uint8_t CurChannel;
}ADC_CtrlStruct;

static ADC_CtrlStruct prvADC;

static void __FUNC_IN_RAM__ ADC_IrqHandle(int32_t IrqLine, void *pData)
{
    int i;
    uint8_t NextChannel;

    ADC0->ADC_CR1 = 0;
    {
        for(i = 0; i < SAMPLE_PER_CH; i++)
        {
            prvADC.ChannelData[prvADC.CurChannel].Data[i] = ADC0->ADC_DATA & 0x0fff;
        }


        if (prvADC.CurChannel == (ADC_CHANNEL_MAX - 1))
        {
            NextChannel = 0;
        }
        else
        {
            NextChannel = prvADC.CurChannel + 1;
        }
        prvADC.CurChannel = 0;
        for(i = NextChannel; i < ADC_CHANNEL_MAX; i++)
        {
            if (prvADC.Enable[i])
            {
                prvADC.CurChannel = i;
                break;
            }
        }
        ADC0->ADC_FIFO = 3;
        ADC0->ADC_CR1 = 0x060 | prvADC.Ctrl | prvADC.CurChannel;
    }
}

void ADC_GlobalInit(void)
{
    int i;
//  for(i = 0; i < ADC_CHANNEL_MAX;i++)
//  {
//      prvADC.Enable[i] = 1;
//  }
    prvADC.Enable[0] = 1;
    prvADC.Ctrl = 2 << 3;
    ADC0->ADC_FIFO_THR = SAMPLE_PER_CH - 1;
    ADC0->ADC_FIFO = 3;
    ADC0->ADC_CR2 &= ~(1 << 14);
    ADC0->ADC_CR2 &= ~(1 << 13);
    ISR_SetHandler(ADC0_IRQn, ADC_IrqHandle, NULL);
#ifdef __BUILD_OS___
    ISR_SetPriority(ADC0_IRQn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
#else
    ISR_SetPriority(ADC0_IRQn, 6);
#endif
    ISR_OnOff(ADC0_IRQn, 1);
    ADC0->ADC_CR1 = 0x060 | prvADC.Ctrl | prvADC.CurChannel;
}

void ADC_SetSpeed(uint8_t Level)
{
    prvADC.Ctrl = Level << 3;
}

void ADC_IntelResistance(uint8_t OnOff)
{
    if (OnOff)
    {
        ADC0->ADC_CR2 |= (1 << 13);
    }
    else
    {
        ADC0->ADC_CR2 &= ~(1 << 13);
    }
}
void ADC_ChannelOnOff(uint8_t Channel, uint8_t OnOff)
{
    if (!Channel) return;
    int i;
    ISR_OnOff(ADC0_IRQn, 0);
    prvADC.Enable[Channel] = OnOff;
    ISR_OnOff(ADC0_IRQn, 1);
}
uint32_t ADC_GetChannelValue(uint8_t Channel)
{
    uint32_t total= 0;
    uint32_t value = 0;
    uint32_t max = 0;
    uint32_t min = 0xffff;
    uint32_t i;
    uint32_t Data[SAMPLE_PER_CH];
    ISR_OnOff(ADC0_IRQn, 0);
    memcpy(&Data[10], &prvADC.ChannelData[Channel].Data[10], (SAMPLE_PER_CH - 10) * sizeof(uint32_t));
    ISR_OnOff(ADC0_IRQn, 1);
    for (i = 10; i < SAMPLE_PER_CH; i++)
    {
//      DBG("%d,%d", i, Data[i]);
        value = Data[i];
        if(max < value)
            max = value;
        if(min > value)
            min = value;
        total += value;
    }

    return ((total - max) -min)/(SAMPLE_PER_CH-12);
}

uint32_t ADC_GetChannelValueBlock(uint8_t Channel)
{

}
#else

typedef struct
{
    uint32_t Data[SAMPLE_PER_CH];
    volatile uint8_t Done;
}ADC_CtrlStruct;
static ADC_CtrlStruct prvADC;
static void ADC_IrqHandle(int32_t IrqLine, void *pData)
{
    int i;

    ADC0->ADC_CR1 = 0;
    prvADC.Done = 1;
    for(i = 0; i < SAMPLE_PER_CH; i++)
    {
        prvADC.Data[i] = ADC0->ADC_DATA & 0x0fff;
    }
    ADC0->ADC_FIFO = 3;
}

void ADC_GlobalInit(void)
{
    int i;
    ADC0->ADC_FIFO_THR = SAMPLE_PER_CH - 1;
    ADC0->ADC_FIFO = 3;
    ADC0->ADC_CR2 &= ~(1 << 14);
    ADC0->ADC_CR2 &= ~(1 << 13);
    ADC0->ADC_CR1 = 0;
    ISR_SetHandler(ADC0_IRQn, ADC_IrqHandle, NULL);
#ifdef __BUILD_OS___
    ISR_SetPriority(ADC0_IRQn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY - 1);
#else
    ISR_SetPriority(ADC0_IRQn, 6);
#endif
    ISR_OnOff(ADC0_IRQn, 0);
}

void ADC_IntelResistance(uint8_t OnOff)
{
    if (OnOff)
    {
        ADC0->ADC_CR2 |= (1 << 13);
    }
    else
    {
        ADC0->ADC_CR2 &= ~(1 << 13);
    }
}
void ADC_ChannelOnOff(uint8_t Channel, uint8_t OnOff)
{

}

uint32_t ADC_GetChannelValue(uint8_t Channel)
{

    uint32_t total= 0;
    uint32_t value = 0;
    uint32_t max = 0;
    uint32_t min = 0x0fff;
    uint32_t i;
    ADC0->ADC_FIFO = 3;
    prvADC.Done = 0;
    ISR_OnOff(ADC0_IRQn, 1);
    ADC0->ADC_CR1 = 0x060 | Channel;
    while(!prvADC.Done){;}
    for (i = 10; i < SAMPLE_PER_CH; i++)
    {
//      DBG("%d,%d", i, prvADC.Data[i]);
        value = prvADC.Data[i];
        if(max < value)
            max = value;
        if(min > value)
            min = value;
        total += value;
    }
    ADC0->ADC_CR1 = 0;
    return ((total - max) -min)/(SAMPLE_PER_CH-12);
}
#endif
