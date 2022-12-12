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

#ifndef __CORE_OTP_H__
#define __CORE_OTP_H__
/**
 * @brief 写OTP区
 *
 * @param Address 写入首地址，注意从0开始，一共3KB，必须4字节对齐
 * @param Data 写入数据，必须4字节对齐
 * @param Len 写入数据长度，单位4字节，比如写入128字节，这里填32
 */
void OTP_Write(uint32_t Address, const uint32_t *Data, uint32_t Len);
/**
 * @brief 读OTP区
 *
 * @param Address 首地址，注意从0开始，一共3KB
 * @param Data 缓存数据
 * @param Len 读出长度
 */
void OTP_Read(uint32_t Address, uint8_t *Data, uint32_t Len);
/**
 * @brief 锁定全部OTP区，变成只读，只能重启恢复
 *
 */
void OTP_Lock(void);

void OTP_GetSn(uint8_t *ChipSN);
#endif
