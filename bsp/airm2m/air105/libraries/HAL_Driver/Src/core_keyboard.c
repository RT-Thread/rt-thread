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
    const I2C_TypeDef *RegBase;
    const int IrqLine;
    CBFuncEx_t CB;
    void *pParam;
}KB_CtrlStruct;

static KB_CtrlStruct prvKB = {
        KCU,
        KBD_IRQn,
};

static int32_t prvKB_DummyCB(void *pData, void *pParam)
{
    return 0;
}



static void KB_IrqHandle(int32_t IrqLine, void *pData)
{
    uint32_t Status, Event, i, type, key;
    Status = KCU->KCU_STATUS;
    Event = KCU->KCU_EVENT;
    ISR_Clear(IrqLine);
    for(i = 0; i < 4; i++)
    {
        if (Status & (1 << (2 * i + 5)))
        {
            type = (Status & (1 << (2 * i + 4)))?1:0;
            key = (Event & (0x000000ff << (i * 8))) >> (i * 8);
            key |= (type << 16);
            prvKB.CB(key, prvKB.pParam);
        }
    }
}

void KB_Setup(uint16_t PinConfigMap, uint16_t Debounce, CBFuncEx_t CB, void *pParam)
{
    uint32_t Dummy;
    ISR_OnOff(prvKB.IrqLine, 0);
    KCU->KCU_CTRL1 &= KCU_CTRL1_KCU_RUNING;
    while ((KCU->KCU_CTRL1 & KCU_CTRL1_KCU_RUNING));
    Dummy = KCU->KCU_EVENT;
    Debounce &= 0x7;
    KCU->KCU_CTRL0 = (PinConfigMap & 0x01ff) | (Debounce << 9);
    if (CB)
    {
        prvKB.CB = CB;
    }
    else
    {
        prvKB.CB = prvKB_DummyCB;
    }
    prvKB.pParam = pParam;
    KCU->KCU_CTRL1 |= (KCU_CTRL1_KBD_EN|KCU_CTRL1_PUSH_IT|KCU_CTRL1_RELEASE_IT|KCU_CTRL1_OVERRUN_IT);
    ISR_SetHandler(prvKB.IrqLine, KB_IrqHandle, NULL);
#ifdef __BUILD_OS__
    ISR_SetPriority(prvKB.IrqLine, configLIBRARY_LOWEST_INTERRUPT_PRIORITY - 1);
#else
    ISR_SetPriority(prvKB.IrqLine, 7);
#endif
    ISR_OnOff(prvKB.IrqLine, 1);
}

void KB_Stop(void)
{
    ISR_OnOff(prvKB.IrqLine, 0);
    KCU->KCU_CTRL1 &= KCU_CTRL1_KCU_RUNING;
}
