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



#ifndef __AIR105_SSC_H
#define __AIR105_SSC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

#define SSC_ITSysXTAL12M                    BIT(18) //系统12M时钟源标志
#define SSC_ITSysGlitch                     BIT(17) //供源噪声标志
#define SSC_ITSysVolHigh                    BIT(16) //供源电压高标志
#define SSC_ITSysVolLow                     BIT(15) //供源电压低标志

typedef struct
{
    FunctionalState ParityCheck;                                //偶校验使用
}SSC_InitTypeDef;


/*
 *  以BPK为4，每256为一单元格编号，用于多单元格写入
 *  SSC_BPKAccessCtrBlock_0为初始0地址。
 */ 
#define SSC_BPKAccessCtrBlock_0             (0x01)
#define SSC_BPKAccessCtrBlock_1             (0x02)
#define SSC_BPKAccessCtrBlock_All           (0x03)

typedef enum
{
    SSC_BPKReadOnly     = 0x01,     //BPK只读
    SSC_BPKWriteOnly    = 0x02,     //BPK只写
    SSC_BPKReadWrite    = 0x03      //BPK读写
}SSC_BPKAccessCtrlTypeDef;
#define IS_BPK_ACCESS_CTRL(CTRL) (((CTRL) == SSC_BPKReadOnly) || ((CTRL) == SSC_BPKWriteOnly) || \
                                ((CTRL) == SSC_BPKReadWrite))

#define SSC_SENSOR_XTAL12M                          ((uint32_t)0x00000001)
#define SSC_SENSOR_VOL_LOW                          ((uint32_t)0x00000002)
#define SSC_SENSOR_VOL_HIGH                         ((uint32_t)0x00000004)
#define SSC_SENSOR_VOLGLITCH                        ((uint32_t)0x00000008)
#define IS_SSC_SENSOR(SENSOR)                       ((((SENSOR) & (uint32_t)0xFFFFFFF0) == 0x00) && ((SENSOR) != (uint32_t)0x00))

typedef enum
{
    SSC_SENSOR_CPUReset  = 0,
    SSC_SENSOR_Interrupt = 1
}SSC_SENSOR_RespModeTypeDef;
#define IS_SSC_SENSOR_RESP_MODE(Mode)               ((Mode) == SSC_SENSOR_CPUReset ||\
                                                    (Mode) == SSC_SENSOR_Interrupt)

/**
  * @method SSC_Init
  * @brief  SSC全局初始化函数
  * @param  SSC_InitTypeDef SSC_InitStruct
  * @retval void
  */
void SSC_Init(SSC_InitTypeDef *SSC_InitStruct);


/**
  * @method SSC_GetITStatus
  * @brief  SSC全局状态判断函数
  * @param  uint32_t SSC_IT
  * @retval ITStatus
  */
ITStatus SSC_GetITStatus(uint32_t SSC_IT);


/**
  * @method SSC_ClearITPendingBit
  * @brief  SSC清除全局中断状态函数
  * @param  uint32_t SSC_IT
  * @retval void
  */
void SSC_ClearITPendingBit( uint32_t SSC_IT);


/**
  * @method SSC_SetDataRAMScrambler
  * @brief  设置数据RAM扰码
  * @param  uint32_t Scrambler
  * @retval void
  */
void SSC_SetDataRAMScrambler(uint32_t Scrambler);


/**
  * @method SSC_BPKAccessCtrConfig
  * @brief  配置BPK访问权限
  * @param  uint32_t SSC_BPKAccessCtrBlock
  * @param  SSC_BPKAccessCtrlTypeDef SSC_BPKAccessCtr
  * @retval void
  */
void SSC_BPKAccessCtrlConfig(uint32_t SSC_BPKAccessCtrBlock, SSC_BPKAccessCtrlTypeDef SSC_BPKAccessCtr);


/**
  * @method SSC_SENSOR_Enable
  * @brief  使能系统Sensor
  * @param  SSC_SENSOR
  * @retval
  */
uint32_t SSC_SENSORCmd(uint32_t SSC_SENSOR, FunctionalState NewState);


/**
  * @method SSC_SENSORLock
  * @brief  锁定系统Sensor状态
  * @param  SSC_SENSOR
  * @retval
  */
void SSC_SENSORLock(uint32_t SSC_SENSOR);


/**
  * @method SSC_SENSOR_AttackRespMode
  * @brief  系统Sensor响应模式
  * @param  SSC_SENSOR_RespMode
  * @retval
  */
void SSC_SENSORAttackRespMode(SSC_SENSOR_RespModeTypeDef SSC_SENSOR_RespMode);


void SSC_SENSORKeyClearCmd(uint32_t SSC_SENSOR, FunctionalState KeyClearEn);


#ifdef __cplusplus
}
#endif

#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
