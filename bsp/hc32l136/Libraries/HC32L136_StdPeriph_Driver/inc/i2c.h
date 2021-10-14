/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file i2c.h
 **
 ** Headerfile for I2C functions
 **  
 **
 ** History:
 **   - 2018-03-1   CJ    First Version
 **
 *****************************************************************************/

#ifndef __I2C_H__
#define __I2C_H__

#include "ddl.h"
#include "interrupts_hc32l136.h"

/**
 *******************************************************************************
 ** \defgroup I2cGroup Inter-Integrated Circuit (I2C)
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
 /**
 ******************************************************************************
 ** \brief I2C通道选择
 *****************************************************************************/
 typedef enum en_i2c_channel
 {
    I2C0 = 0,///<通道0
    I2C1 = 1,///<通道1  
 }en_i2c_channel_t;
 /**
 ******************************************************************************
 ** \brief I2C功能配置
 *****************************************************************************/
typedef enum en_i2c_func
{
    I2cMode_En  = 0, ///<I2C模块使能
    I2cStart_En = 1, ///<开始信号
    I2cStop_En  = 2, ///<结束信号
    I2cAck_En   = 3, ///<应答信号
    I2cHlm_En   = 4, ///<高速使能
    I2cBaud_En  = 5, ///<波特率使能
}en_i2c_func_t; 
/**
 ******************************************************************************
 ** \brief I2C从机地址配置
 *****************************************************************************/
typedef struct stc_i2c_addr
{
    uint8_t Addr;       ///<从机模式地址
    uint8_t Gc;         ///<广播地址使能

}stc_i2c_addr_t;
/**
 ******************************************************************************
 ** \brief I2C初始化配置结构
 *****************************************************************************/
typedef struct stc_i2c_config
{
    en_i2c_func_t   enFunc;      ///<功能使能
    uint8_t         u8Tm;        ///<波特率计数器配置
    stc_i2c_addr_t  stcSlaveAddr;///<从机地址
    func_ptr_t      pfnI2c0Cb;    ///<中断服务函数指针
    func_ptr_t      pfnI2c1Cb;
    boolean_t       bTouchNvic;  ///<是否使能NVIC
}stc_i2c_config_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
 //I2C初始化函数
 en_result_t I2C_Init(en_i2c_channel_t enCh,stc_i2c_config_t *pstcI2CCfg);
  //I2C模块关闭函数
 en_result_t I2C_DeInit(en_i2c_channel_t enCh);
 //设置波特率配置寄存器
 en_result_t I2C_SetBaud(en_i2c_channel_t enCh,uint8_t u8Tm);
 //I2C功能设置函数
 en_result_t I2C_SetFunc(en_i2c_channel_t enCh,en_i2c_func_t enFunc);
  //I2C功能清除函数
 en_result_t I2C_ClearFunc(en_i2c_channel_t enCh,en_i2c_func_t enFunc);
 //获取中断标记SI
 boolean_t I2C_GetIrq(en_i2c_channel_t enCh);
  //清除中断标记SI
 en_result_t I2C_ClearIrq(en_i2c_channel_t enCh);
 //获取状态
 uint8_t I2C_GetState(en_i2c_channel_t enCh);
 //写从机地址函数
 en_result_t I2C_WriteSlaveAddr(en_i2c_channel_t enCh,stc_i2c_addr_t *pstcSlaveAddr);
 //主发送函数
 en_result_t I2C_MasterWriteData(en_i2c_channel_t enCh,uint8_t u8DevAddr,uint8_t u8Addr,uint8_t *pu8Data,uint32_t u32Len);
  //从发送函数
 en_result_t I2C_SlaveWriteData(en_i2c_channel_t enCh,uint8_t *pu8Data,uint32_t *u32Len);
 //字节写函数
 en_result_t I2C_WriteByte(en_i2c_channel_t enCh,uint8_t u8Data);
 //主接收函数
 en_result_t I2C_MasterReadData(en_i2c_channel_t enCh,uint8_t u8DevAddr,uint8_t *pu8Data,uint8_t u8Addr,uint32_t u32Len);
  //主接收函数
 en_result_t I2C_SlaveReadData(en_i2c_channel_t enCh,uint8_t *pu8Data,uint32_t *pu32Len);
  //字节读函数
uint8_t I2C_ReadByte(en_i2c_channel_t enCh);
 
//@} // I2cGroup

#ifdef __cplusplus
#endif

#endif /* __I2C_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


