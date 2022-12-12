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

#ifndef __CORE_HWTIMER_H__
#define __CORE_HWTIMER_H__


/**
 * @brief 硬件定时器按照周期和占空比设置成PWM并启动
 *
 * @param HWTimerID 硬件定时器ID
 * @param Period 周期，最大24M，
 * @param Duty 占空比，0.1%，只有50KHz以下才能达到这个精度，500KHz到1%
 * @param IsOnePulse 只触发一次脉冲
 */
void HWTimer_SetPWM(uint8_t HWTimerID, uint32_t Period, uint16_t Duty, uint8_t IsOnePulse);

/**
 * @brief 硬件定时器按照高低电平分辨率设置成PWM并启动，时钟48M
 *
 * @param HWTimerID 硬件定时器ID
 * @param HighCnt 高电平时钟周期数
 * @param LowCnt 低电平时钟周期数
 * @param IsOnePulse 只触发一次脉冲
 */
void HWTimer_StartPWM(uint8_t HWTimerID, uint32_t HighCnt, uint32_t LowCnt, uint8_t IsOnePulse);

/**
 * @brief 硬件定时器关闭
 *
 * @param HWTimerID 硬件定时器ID
 */
void HWTimer_Stop(uint8_t HWTimerID);
/**
 * @brief 初始化IO操作序列，会完全清除之前保留的操作序列
 *
 * @param HWTimerID 硬件定时器ID
 * @param nCount 操作步骤总数
 * @param Repeat 重复次数
 * @param InputByte IO读取的次数，注意每8次1个byte，不足8个也算1个byte
 * @param CmdDoneCB 全部完成后回调函数
 * @param pCmdDoneParam 回调函数的用户参数
 *
 */
void HWTimer_InitOperationQueue(uint8_t HWTimerID, uint32_t nCount, uint32_t Repeat, uint32_t InputByte, CBFuncEx_t CmdDoneCB, void *pCmdDoneParam);
/**
 * @brief 加入IO操作序列
 *
 * @param HWTimerID 硬件定时器ID
 * @param pCmd IO操作
 */
void HWTimer_AddOperation(uint8_t HWTimerID, OPQueue_CmdStruct *pCmd);
/**
 * @brief 启动IO操作序列
 *
 * @param HWTimerID 硬件定时器ID
 */
void HWTimer_StartOperationQueue(uint8_t HWTimerID);
/**
 * @brief 清空IO操作序列，需要重新AddOperation，但是不需要init
 *
 * @param HWTimerID 硬件定时器ID
 */
void HWTimer_ClearOperationQueue(uint8_t HWTimerID);
/**
 * @brief 完全释放IO操作序列，下次使用需要重新init，必须在HWTimer_CheckOperationQueueDone确认完成的情况下调用
 *
 * @param HWTimerID 硬件定时器ID
 */
void HWTimer_FreeOperationQueue(uint8_t HWTimerID);
/**
 * @brief 在OP_QUEUE_CMD_CB时，需要在CB里调用本函数来安全的结束序列操作，只能在OP_QUEUE_CMD_CB时调用
 *
 * @param HWTimerID 硬件定时器ID
 */
void HWTimer_AddEndCmdInOperationQueue(uint8_t HWTimerID);
/**
 * @brief 检查IO操作序列是否完成
 *
 * @param HWTimerID 硬件定时器ID
 * @return =0未完成，其他已完成
 */
uint8_t HWTimer_CheckOperationQueueDone(uint8_t HWTimerID);
/**
 * @brief 获取IO操作序列中IO读取的值
 *
 * @param HWTimerID 硬件定时器ID
 * @param Value copy的空间
 * @return 获取的byte数，和init时InputByte一致
 */
int HWTimer_GetOperationQueueInputResult(uint8_t HWTimerID, uint8_t *Value);

/**
 * @brief 获取IO操作序列中捕获状态
 *
 * @param HWTimerID 硬件定时器ID
 * @param CB 捕获回调函数
 * @param CB 捕获回调函数的用户参数
 * @return 捕获次数
 */
uint32_t HWTimer_GetOperationQueueCaptureResult(uint8_t HWTimerID, CBFuncEx_t CB, void *pParam);
#endif
