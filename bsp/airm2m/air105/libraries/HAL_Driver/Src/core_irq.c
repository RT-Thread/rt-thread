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
#define __IRQ_IN_RAM__
#ifdef __IRQ_IN_RAM__
#else
#define __FUNC_IN_RAM__
#endif
typedef struct {
    void (*Irq_Handler)(int32_t IrqLine, void *pData);
    void *pData;
}Irq_Handler_t;

static Irq_Handler_t Irq_Table[IRQ_LINE_MAX + 16 - IRQ_LINE_OFFSET];

static void ISR_DummyHandler(int32_t IrqLine, void *pData)
{

}

void __FUNC_IN_RAM__ ISR_GlobalHandler(void)
{
    int IrqLine = ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) >> SCB_ICSR_VECTACTIVE_Pos) - IRQ_LINE_OFFSET;
    if (IrqLine < 0 || IrqLine >= IRQ_LINE_MAX)
    {
        return;
    }
    rt_interrupt_enter();
    if (Irq_Table[IrqLine].Irq_Handler)
    {
        Irq_Table[IrqLine].Irq_Handler(IrqLine + IRQ_LINE_OFFSET - 16, Irq_Table[IrqLine].pData);
    }
    rt_interrupt_leave();
}

void ISR_SetHandler(int32_t Irq, void *Handler, void *pData)
{
    Irq_Table[Irq + 16 - IRQ_LINE_OFFSET].Irq_Handler = Handler;
    Irq_Table[Irq + 16 - IRQ_LINE_OFFSET].pData = pData;
}

void ISR_SetPriority(int32_t Irq, uint32_t PriorityLevel)
{
    NVIC_SetPriority(Irq, PriorityLevel);
}

void __FUNC_IN_RAM__ ISR_OnOff(int32_t Irq, uint32_t OnOff)
{
    if (OnOff)
    {
        if (!Irq_Table[Irq + 16 - IRQ_LINE_OFFSET].Irq_Handler)
        {
            Irq_Table[Irq + 16 - IRQ_LINE_OFFSET].Irq_Handler = ISR_DummyHandler;
        }
        NVIC_EnableIRQ(Irq);
    }
    else
    {
        NVIC_DisableIRQ(Irq);
    }
}

void __FUNC_IN_RAM__ ISR_Clear(int32_t Irq)
{
    NVIC_ClearPendingIRQ(Irq);
}

uint32_t __FUNC_IN_RAM__ ISR_CheckIn(void)
{
    return __get_IPSR();
}

