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

#ifndef __CORE_DCMI_H__
#define __CORE_DCMI_H__

/**
 * @brief 对摄像头做基本的初始化工作
 *
 * @param VsyncLevel 垂直同步极性 0： VSYNC 低电平有效 1： VSYNC 高电平有效
 * @param HsyncLevel 水平同步极性 0： HSYNC 低电平有效 1： HSYNC 高电平有效
 * @param PclkPOL Pixel时钟极性 0：下降沿有效 1：上升沿有效
 * @param DataBits 数据位8~14
 * @param FrameRate 帧率控制，0不控制，1减少为50%，2减少为25%
 */
void DCMI_Setup(uint8_t VsyncLevel, uint8_t HsyncLevel, uint8_t PclkPOL, uint8_t DataBit, uint32_t FrameRate);

/**
 * @brief 摄像头捕获开关
 *
 * @param OnOff 0： 关 1： 开
 * @param BufLen 缓存大小，注意单位是4byte，如果为0，看下面的参数自动生成，如果不为0，必须是行数据量的倍数，且能被总行数整除，比如320*240，16bit数据，那么就是320*2/4的N倍，比如8倍的1280
 * @param ImageW 输出图像一行的像素点数
 * @param ImageW 输出图像行数
 * @param DataByte 1个像素点的数据量byte
 * @param OutH 自动计算出的单次回调行数
 */
void DCMI_CaptureSwitch(uint8_t OnOff, uint32_t BufLen, uint32_t ImageW, uint32_t ImageH, uint8_t DataByte, uint32_t *OutH);
void DCMI_SetCallback(CBFuncEx_t CB, void *pData);
/**
 * @brief 摄像头裁剪功能
 *
 * @param OnOff 0： 关 1： 开
 * @param VStart 裁剪从第几行开始
 * @param HStart 裁剪每行从第几个像素数据开始，如果是16bit数据，则要*2，依次类推
 * @param VLen 裁剪保留的行数，最小1
 * @param HLen 裁剪每行保留的像素数据，如果是16bit数据，则要*2，依次类推
 */
void DCMI_SetCROPConfig(uint8_t OnOff, uint32_t VStart, uint32_t HStart, uint32_t VLen, uint32_t HLen);
#endif
