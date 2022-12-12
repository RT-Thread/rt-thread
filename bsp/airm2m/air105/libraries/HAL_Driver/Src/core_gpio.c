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
    volatile GPIO_TypeDef *RegBase;
    const int32_t IrqLine;
    uint16_t ODBitMap;

}GPIO_ResourceStruct;

typedef struct
{
    CBFuncEx_t AllCB;
    CBFuncEx_t HWTimerCB;
    void *pParam;
}GPIO_CtrlStruct;

static GPIO_CtrlStruct prvGPIO;

static GPIO_ResourceStruct prvGPIO_Resource[6] =
{
        {
                GPIOA,
                EXTI0_IRQn,
                0,
        },
        {
                GPIOB,
                EXTI1_IRQn,
                0,
        },
        {
                GPIOC,
                EXTI2_IRQn,
                0,
        },
        {
                GPIOD,
                EXTI3_IRQn,
                0,
        },
        {
                GPIOE,
                EXTI4_IRQn,
                0,
        },
        {
                GPIOF,
                EXTI5_IRQn,
                0,
        },
};

static int32_t GPIO_IrqDummyCB(void *pData, void *pParam)
{
//  DBG("%d", pData);
    return 0;
}
static void __FUNC_IN_RAM__ GPIO_IrqHandle(int32_t IrqLine, void *pData)
{
    volatile uint32_t Port = (uint32_t)pData;
    volatile uint32_t Sn, i;
    if (GPIO->INTP_TYPE_STA[Port].INTP_STA)
    {
        Sn = GPIO->INTP_TYPE_STA[Port].INTP_STA;
        GPIO->INTP_TYPE_STA[Port].INTP_STA = 0xffff;
        prvGPIO.HWTimerCB((Port << 16) | Sn, prvGPIO.pParam);
        Port = (Port << 4);

        for(i = 0; i < 16; i++)
        {
            if (Sn & (1 << i))
            {
                prvGPIO.AllCB((void *)(Port+i), 0);
            }
        }
    }
    ISR_Clear(IrqLine);
}

void GPIO_GlobalInit(CBFuncEx_t Fun)
{
    uint32_t i;
    if (Fun)
    {
        prvGPIO.AllCB = Fun;
    }
    else
    {
        prvGPIO.AllCB = GPIO_IrqDummyCB;
    }
    prvGPIO.HWTimerCB = GPIO_IrqDummyCB;
    for(i = 0; i < 6; i++)
    {
        GPIO->INTP_TYPE_STA[i].INTP_TYPE = 0;
        GPIO->INTP_TYPE_STA[i].INTP_STA = 0xffff;
#ifdef __BUILD_OS__
        ISR_SetPriority(prvGPIO_Resource[i].IrqLine, IRQ_MAX_PRIORITY + 1);
#else
        ISR_SetPriority(prvGPIO_Resource[i].IrqLine, 3);
#endif
        ISR_SetHandler(prvGPIO_Resource[i].IrqLine, GPIO_IrqHandle, (void *)i);
        ISR_OnOff(prvGPIO_Resource[i].IrqLine, 1);
    }

}

void __FUNC_IN_RAM__ GPIO_Config(uint32_t Pin, uint8_t IsInput, uint8_t InitValue)
{
    uint8_t Port = (Pin >> 4);
    uint8_t orgPin = Pin;
    Pin = 1 << (Pin & 0x0000000f);
    GPIO_Iomux(orgPin, 1);
    if (IsInput)
    {
        prvGPIO_Resource[Port].RegBase->OEN |= Pin;
    }
    else
    {
        prvGPIO_Resource[Port].RegBase->BSRR |= InitValue?Pin:(Pin << 16);
        prvGPIO_Resource[Port].RegBase->OEN &= ~Pin;
    }
    prvGPIO_Resource[Port].ODBitMap &= ~Pin;
}

void __FUNC_IN_RAM__ GPIO_ODConfig(uint32_t Pin, uint8_t InitValue)
{
    uint8_t Port = (Pin >> 4);
    uint8_t orgPin = Pin;
    Pin = 1 << (Pin & 0x0000000f);
    GPIO_Iomux(orgPin, 1);
    prvGPIO_Resource[Port].RegBase->OEN |= Pin;
    if (InitValue)
    {
        prvGPIO_Resource[Port].RegBase->PUE |= Pin;
    }
    else
    {
        prvGPIO_Resource[Port].RegBase->PUE &= ~Pin;
    }
    prvGPIO_Resource[Port].ODBitMap |= Pin;
}

void __FUNC_IN_RAM__ GPIO_PullConfig(uint32_t Pin, uint8_t IsPull, uint8_t IsUp)
{
    uint8_t Port = (Pin >> 4);
    Pin = 1 << (Pin & 0x0000000f);
    if (IsPull && IsUp)
    {
        prvGPIO_Resource[Port].RegBase->PUE |= Pin;
    }
    else
    {
        prvGPIO_Resource[Port].RegBase->PUE &= ~Pin;
    }
}

void GPIO_ExtiConfig(uint32_t Pin, uint8_t IsLevel, uint8_t IsRiseHigh, uint8_t IsFallLow)
{
    uint8_t Port = (Pin >> 4);
    uint32_t Type = 0;
    uint32_t Mask = ~(0x03 << ((Pin & 0x0000000f) * 2));
    if (!IsLevel)
    {
        if (IsRiseHigh && IsFallLow)
        {
            Type = 0x03 << ((Pin & 0x0000000f) * 2);
        }
        else if (IsFallLow)
        {
            Type = 0x02 << ((Pin & 0x0000000f) * 2);
        }
        else if (IsRiseHigh)
        {
            Type = 0x01 << ((Pin & 0x0000000f) * 2);
        }
    }
    GPIO->INTP_TYPE_STA[Port].INTP_TYPE = (GPIO->INTP_TYPE_STA[Port].INTP_TYPE & Mask) | Type;
}

void GPIO_ExtiSetHWTimerCB(CBFuncEx_t CB, void *pParam)
{
    if (CB)
    {
        prvGPIO.HWTimerCB = CB;
    }
    else
    {
        prvGPIO.HWTimerCB = GPIO_IrqDummyCB;
    }
    prvGPIO.pParam = pParam;
}

void __FUNC_IN_RAM__ GPIO_Iomux(uint32_t Pin, uint32_t Function)
{
    uint8_t Port = (Pin >> 4);
    uint32_t Mask = ~(0x03 << ((Pin & 0x0000000f) * 2));
    Function = Function << ((Pin & 0x0000000f) * 2);
    GPIO->ALT[Port] = (GPIO->ALT[Port] & Mask) | Function;
}

void __FUNC_IN_RAM__ GPIO_Output(uint32_t Pin, uint8_t Level)
{
    uint8_t Port = (Pin >> 4);
    Pin = 1 << (Pin & 0x0000000f);
    if (prvGPIO_Resource[Port].ODBitMap & Pin)
    {
        if (Level)
        {
            prvGPIO_Resource[Port].RegBase->PUE |= Pin;
        }
        else
        {
            prvGPIO_Resource[Port].RegBase->PUE &= ~Pin;
        }
    }
    else
    {
        prvGPIO_Resource[Port].RegBase->BSRR |= Level?Pin:(Pin << 16);
    }

//  DBG("%d, %x, %x, %x",Port, Pin, prvGPIO_Resource[Port].RegBase, prvGPIO_Resource[Port].RegBase->IODR);
}

uint8_t __FUNC_IN_RAM__ GPIO_Input(uint32_t Pin)
{
    uint8_t Port = (Pin >> 4);
    Pin = 1 << (Pin & 0x0000000f);
    return (prvGPIO_Resource[Port].RegBase->IODR & (Pin << 16))?1:0;
}

void __FUNC_IN_RAM__ GPIO_OutputMulti(uint32_t Port, uint32_t Pins, uint32_t Level)
{
    prvGPIO_Resource[Port].RegBase->BSRR |= Level?Pins:(Pins << 16);
}

uint32_t __FUNC_IN_RAM__ GPIO_InputMulti(uint32_t Port)
{
    return (prvGPIO_Resource[Port].RegBase->IODR >> 16);
}
