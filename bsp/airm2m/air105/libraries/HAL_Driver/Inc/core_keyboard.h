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

#ifndef __CORE_KEYBOARD_H__
#define __CORE_KEYBOARD_H__
/**
 * @brief 键盘扫描配置
 *
 * @param PinConfigMap 硬盘扫描通道配置，bit0~bit8对应通道0到8,0为输入,1为输出，开发板配置为0x0f0
 * @param Debounce 按键滤波，目前强制为7
    0： 5ms~75ms；
    1： 17.5ms~75ms；
    2： 27.5ms~75ms；
    3： 37.5 ms~75ms；
    4： 45ms~75ms；
    5： 50ms~75ms；
    6： 60ms~75ms；
    7： 70ms~75ms。
 * @param CB 按键中断回调，pData为按键参数32bit，pParam为用户数据，按键参数中bit16=1按下0释放，bit0~3，输入通道值，bit4~bit7，输出通道值
 * @param pParam 按键中断回调用户数据
 */
void KB_Setup(uint16_t PinConfigMap, uint16_t Debounce, CBFuncEx_t CB, void *pParam);
void KB_Stop(void);
#endif
