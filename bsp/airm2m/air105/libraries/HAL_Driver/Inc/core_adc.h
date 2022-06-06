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

#ifndef __CORE_ADC_H__
#define __CORE_ADC_H__
#define ADC_VALUE_ERROR (0xffffffff)
void ADC_GlobalInit(void);
/**
 * @brief 通道开关，在globalinit时只打开了0，0也无法被关闭，目前已经废弃，ADC_GetChannelValue的时候临时打开
 *
 * @param Channel 通道号
 * @param OnOff 开关
 */
void ADC_ChannelOnOff(uint8_t Channel, uint8_t OnOff);
/**
 * @brief 获取通道的原始ADC值，12bit，1.8V参考电压，通道0内部9:5分压，其他关闭
 *
 * @param Channel 通道号
 * @return != ADC_VALUE_ERROR 为有效值
 */
uint32_t ADC_GetChannelValue(uint8_t Channel);
/**
 * @brief 开关内部分压，1~5都是1:1 6就不确定了，手册和demo不一致
 *
 * @param OnOff 开关
 */
void ADC_IntelResistance(uint8_t OnOff);
#endif
