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

#ifndef __CORE_I2C_H__
#define __CORE_I2C_H__
#include "bsp_common.h"
typedef struct
{
    uint8_t Data[2];
}I2C_CommonRegDataStruct;

void I2C_GlobalInit(void);
/**
 * @brief i2c主机配置
 *
 * @param I2CID I2C通道号
 * @param Speed 速度，只有100000和400000
 */
void I2C_MasterSetup(uint8_t I2CID, uint32_t Speed);
/*
 * @brief i2c传输前配置，如果配置和上次一致，则不用设置
 *
 * @param I2CID I2C通道号
 * @param ChipAddress I2C设备地址
 * @param ChipAddressLen I2C设备地址长度 ，1或者2
 * @param CB 完成后回调函数
 * @param pParam 完成后回调函数中的pParam
 */
void I2C_Prepare(uint8_t I2CID, uint16_t ChipAddress, uint8_t ChipAddressLen, CBFuncEx_t CB, void *pParam);
/**
 * @brief i2c主机传输，兼容直接读写和先写寄存器地址后读数据
 *
 * @param I2CID I2C通道号
 * @param Operate 操作类型
 *  I2C_OP_READ_REG = 0,    //i2c通用读寄存器，一写一读，自动带start信号
    I2C_OP_READ,        //i2c通用读，只读
    I2C_OP_WRITE,       //i2c通用写，只写
 * @param RegAddress 寄存器地址，在通用读写时忽略
 * @param Data 读写数据缓存，直接使用用户的空间，在完成前不可以释放空间
 * @param Len 读写数据长度
 * @param Toms 传输单个字节超时时间，单位ms
 */
void I2C_MasterXfer(uint8_t I2CID, uint8_t Operate, uint8_t RegAddress, uint8_t *Data, uint32_t Len, uint16_t Toms);

/**
 * @brief i2c主机传输，多个单一寄存器写入
 *
 * @param I2CID I2C通道号
 * @param RegQueue 寄存器序列
 * @param TotalNum 序列长度
 * @param Toms 传输单个字节超时时间，单位ms
 * @param IsBlock 是否要阻塞
 * @return =0 传输成功，其他失败 IsBlock=1才有效，IsBlock=0直接返回0
 */
int32_t I2C_MasterWriteRegQueue(uint8_t I2CID, I2C_CommonRegDataStruct *RegQueue, uint32_t TotalNum, uint16_t Toms, uint8_t IsBlock);

/**
 * @brief i2c主机传输结果查询
 *
 * @param I2CID I2C通道号
 * @param Result 传输结果 =0成功，其他失败，只有return != 0才有效
 * @return =0 传输还未完成 其他已完成
 */
int I2C_WaitResult(uint8_t I2CID, int32_t *Result);

int32_t I2C_BlockWrite(uint8_t I2CID, uint8_t ChipAddress, const uint8_t *Data, uint32_t Len, uint16_t Toms, CBFuncEx_t CB, void *pParam);

int32_t I2C_BlockRead(uint8_t I2CID, uint8_t ChipAddress, uint8_t *Reg, uint8_t *Data, uint32_t Len, uint16_t Toms, CBFuncEx_t CB, void *pParam);
#endif
