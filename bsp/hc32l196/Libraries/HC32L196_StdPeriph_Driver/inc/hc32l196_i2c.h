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
 ** \brief I2C功能配置
 *****************************************************************************/
typedef enum en_i2c_func
{
    I2cModule_En = 6u,  ///<I2C模块使能
    I2cStart_En  = 5u, ///<开始信号
    I2cStop_En   = 4u, ///<结束信号
    I2cAck_En    = 2u, ///<应答信号
    I2cHlm_En    = 0u, ///<高速使能
}en_i2c_func_t; 

 /**
 ******************************************************************************
 ** \brief I2C模式配置
 *****************************************************************************/
typedef enum en_i2c_mode
{
    I2cMasterMode = 0x40u,  ///<I2C主机模式
    I2cSlaveMode  = 0x44u,  ///<I2C从机模式
}en_i2c_mode_t;

/**
 ******************************************************************************
 ** \brief I2C初始化配置结构
 *****************************************************************************/
typedef struct stc_i2c_cfg
{
    uint32_t        u32Pclk;        ///<Pclk 设置(Hz)
    uint32_t        u32Baud;        ///<I2C通信波特率(Hz)
    en_i2c_mode_t   enMode;         ///<I2C主从模式配置
    uint8_t         u8SlaveAddr;    ///<从机地址配置(如果需要)
    boolean_t       bGc;            ///<广播地址使能(如果需要)
}stc_i2c_cfg_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
 //I2C初始化函数
 en_result_t I2C_Init(M0P_I2C_TypeDef* I2Cx,stc_i2c_cfg_t *pstcI2CCfg);
 //设置波特率配置寄存器
 en_result_t I2C_SetBaud(M0P_I2C_TypeDef* I2Cx,uint8_t u8Tm);
 //I2C功能设置函数
 en_result_t I2C_SetFunc(M0P_I2C_TypeDef* I2Cx,en_i2c_func_t enFunc);
  //I2C功能清除函数
 en_result_t I2C_ClearFunc(M0P_I2C_TypeDef* I2Cx,en_i2c_func_t enFunc);
 //获取中断标记SI
 boolean_t I2C_GetIrq(M0P_I2C_TypeDef* I2Cx);
  //清除中断标记SI
 en_result_t I2C_ClearIrq(M0P_I2C_TypeDef* I2Cx);
 //获取状态
 uint8_t I2C_GetState(M0P_I2C_TypeDef* I2Cx);

 //字节写函数
 en_result_t I2C_WriteByte(M0P_I2C_TypeDef* I2Cx,uint8_t u8Data);

//字节读函数
uint8_t I2C_ReadByte(M0P_I2C_TypeDef* I2Cx);
 
//@} // I2cGroup

#ifdef __cplusplus
#endif

#endif /* __I2C_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


