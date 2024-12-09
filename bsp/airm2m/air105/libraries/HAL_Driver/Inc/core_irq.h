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

#ifndef __CORE_IRQ_H__
#define __CORE_IRQ_H__
#include <stdint.h>
/**
 * @brief 设置中断回调函数
 *
 * @param Irq 中断号 0~IRQ_LINE_MAX
 * @param Handler 中断回调函数，如 void Irq_Handler(uint32_t IrqLine, void *pData); 可以多个中断号对应1个中断函数，回调时传入中断号和用户数据
 */
void ISR_SetHandler(int32_t Irq, void *Handler, void *pData);
/**
 * @brief 设置中断优先级
 *
 * @param Irq 中断号 0~IRQ_LINE_MAX
 * @param PriorityLevel 优先级范围根据芯片实际情况决定
 */
void ISR_SetPriority(int32_t Irq, uint32_t PriorityLevel);

void ISR_OnOff(int32_t Irq, uint32_t OnOff);
void ISR_Clear(int32_t Irq);
void ISR_PrintCallback(int32_t Irq);
#endif
