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

#ifndef __CORE_GPIO_H__
#define __CORE_GPIO_H__
#include "bsp_common.h"
/**
 * @brief GPIO全局初始化
 *
 * @param Fun 中断回调函数，回调时，PIN序号是pData，void *->uint32_t

 */
void GPIO_GlobalInit(CBFuncEx_t Fun);

/**
 * @brief GPIO初始化
 *
 * @param Pin Pin序号
 * @param IsInput 是否为输入功能，1是，0否
 * @param InitValue 初始电平，1高，0低，只对输出有效

 */
void GPIO_Config(uint32_t Pin, uint8_t IsInput, uint8_t InitValue);
/**
 * @brief GPIO上下拉控制
 *
 * @param Pin Pin序号
 * @param IsPull 是否需要上下拉
 * @param IsUp 是否上拉

 */
void GPIO_PullConfig(uint32_t Pin, uint8_t IsPull, uint8_t IsUp);

/**
 * @brief GPIO外部中断初始化
 *
 * @param Pin Pin序号
 * @param IsLevel 是否是电平中断，0边沿型，1电平型
 * @param IsRiseHigh 上升沿或者高电平
 * @param IsFallLow 下降沿或者低电平
 */
void GPIO_ExtiConfig(uint32_t Pin, uint8_t IsLevel, uint8_t IsRiseHigh, uint8_t IsFallLow);

/**
 * @brief GPIO复用功能
 *
 * @param Pin Pin序号
 * @param Function 复用功能，这个需要根据芯片实际情况决定，当前是0~3，注意GPIO功能是1
 */
void GPIO_Iomux(uint32_t Pin, uint32_t Function);

/**
 * @brief GPIO输出电平
 *
 * @param Pin Pin序号
 * @param Level 1高电平，0低电平
 */
void GPIO_Output(uint32_t Pin, uint8_t Level);

/**
 * @brief 读取GPIO输入电平
 *
 * @param Pin Pin序号
 * @return 1高电平， 0低电平，其他无效
 */
uint8_t GPIO_Input(uint32_t Pin);

/**
 * @brief GPIO同一端口多个pin输出电平，针对类似STM32GPIO分布有效
 *
 * @param Port 端口号
 * @param Pins Pin序号组合
 * @param Level 1高电平，0低电平
 */
void GPIO_OutputMulti(uint32_t Port, uint32_t Pins, uint32_t Level);

/**
 * @brief 读取GPIO同一端口多个pin输入电平
 *
 * @param Port 端口号
 * @return
 */
uint32_t GPIO_InputMulti(uint32_t Port);

void GPIO_ExtiSetHWTimerCB(CBFuncEx_t CB, void *pParam);
void GPIO_ODConfig(uint32_t Pin, uint8_t InitValue);
#endif
