/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名： lib_iic.h
 *作 者： Liut
 *版 本： V1.00
 *日 期： 2017/07/14
 *描 述： I2C模块库函数头文件
 *备 注： 适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBIIC_H__
#define __LIBIIC_H__

#include "ES8P508x.h"
#include "type.h"
#include "system_ES8P508x.h"

/* 引脚开漏设置 */
typedef enum
{
    I2C_PinMode_PP = 0x0 , //端口输出模式:推挽
    I2C_PinMode_OD = 0x1 , //端口输出模式:开漏
}I2C_TYPE_PINOD;

/* 工作模式 */
typedef enum
{
    I2C_Mode_Master = 0x0 , //工作模式：主
    I2C_Mode_Slave = 0x1 ,  //工作模式：从
}I2C_TYPE_MODE;

/* 应答延时 */
typedef enum
{
    I2C_AckDelay_0P5 = 0x0 , //应答延时:0.5个时钟周期
    I2C_AckDelay_1 = 0x1 ,   //应答延时:1个时钟周期
    I2C_AckDelay_1P5 = 0x2 , //应答延时:1.5个时钟周期
    I2C_AckDelay_2 = 0x3 ,   //应答延时:2个时钟周期
    I2C_AckDelay_2P5 = 0x4 , //应答延时:2.5个时钟周期
    I2C_AckDelay_3 = 0x5 ,   //应答延时:3个时钟周期
    I2C_AckDelay_3P5 = 0x6 , //应答延时:3.5个时钟周期
    I2C_AckDelay_4 = 0x7 ,   //应答延时:4个时钟周期
}I2C_TYPE_ADLY;

/* 接收模式 */
typedef enum
{
    I2C_RecMode_0 = 0x0 , //接收模式：接收1字节，发送ACK
    I2C_RecMode_1 = 0x1 , //接收模式：接收1字节，发送NACK
    I2C_RecMode_2 = 0x2 , //接收模式：接收2字节，每字节发送ACK
    I2C_RecMode_3 = 0x3 , //接收模式：接收2字节，前一字节发送ACK，后一字节发送NACK
    I2C_RecMode_4 = 0x4 , //接收模式：接收4字节，每字节发送ACK
    I2C_RecMode_5 = 0x5 , //接收模式：接收4字节，前3字节发送ACK，后一字节发送NACK
    I2C_RecMode_6 = 0x6,  //接收模式：连续接收，每个字节发送ACK
    I2C_RecMode_7 = 0x7,  //接收模式：完成该字节接收，发送NACK
}I2C_TYPE_RECMODE;

/* 数据帧传输间隔 */
typedef enum
{
    I2C_TI_Disable = 0x0 , //数据帧传输间隔:0
    I2C_TI_1 = 0x1 ,       //数据帧传输间隔:1
    I2C_TI_2 = 0x2 ,       //数据帧传输间隔:2
    I2C_TI_3 = 0x3 ,       //数据帧传输间隔:3
    I2C_TI_4 = 0x4 ,       //数据帧传输间隔:4
    I2C_TI_5 = 0x5 ,       //数据帧传输间隔:5
    I2C_TI_6 = 0x6 ,       //数据帧传输间隔:6
    I2C_TI_7 = 0x7 ,       //数据帧传输间隔:7
    I2C_TI_8 = 0x8 ,       //数据帧传输间隔:8
    I2C_TI_9 = 0x9 ,       //数据帧传输间隔:9
    I2C_TI_10 = 0xA ,      //数据帧传输间隔:10
    I2C_TI_11 = 0xB ,      //数据帧传输间隔:11
    I2C_TI_12 = 0xC ,      //数据帧传输间隔:12
    I2C_TI_13 = 0xD ,      //数据帧传输间隔:13
    I2C_TI_14 = 0xE ,      //数据帧传输间隔:14
    I2C_TI_15 = 0xF ,      //数据帧传输间隔:15
}I2C_TYPE_TIS;

/* I2C初始化配置结构体定义 */
typedef struct
{
    I2C_TYPE_PINOD  I2C_SclOd; //SCL端口输出模式

    I2C_TYPE_PINOD  I2C_SdaOd; //SDA端口输出模式

    TYPE_FUNCEN  I2C_16XSamp;  //端口16倍速采样使能

    uint32_t  I2C_Clk;         //I2C频率

    I2C_TYPE_MODE  I2C_Mode;   //工作模式

    TYPE_FUNCEN  I2C_AutoStop; //自动停止

    TYPE_FUNCEN  I2C_AutoCall; //自动寻呼
}I2C_InitStruType;

/* 发送、接收中断模式 */
typedef enum
{
    I2C_TRBIM_Byte = 0x0 ,     //字节满产生中断
    I2C_TRBIM_HalfWord = 0x1 , //半字满产生中断
    I2C_TRBIM_Word = 0x2 ,     //字满产生中断
}I2C_TYPE_TRBIM;


/* 读写模式 */
typedef enum
{
    I2C_Mode_Write = 0x0 , 
    I2C_Mode_Read = 0x1 ,
}I2C_TYPE_RWMODE;

/* 中断使能标志位 */
typedef enum
{
    I2C_IT_SR = 0x0001 ,   //起始位
    I2C_IT_SP = 0x0002 ,   //停止位
    I2C_IT_TB = 0x0004 ,   //发送缓冲空
    I2C_IT_RB = 0x0008 ,   //接收缓冲满
    I2C_IT_TE = 0x0010 ,   //发送数据错误
    I2C_IT_RO = 0x0020 ,   //接收数据溢出
    I2C_IT_NA = 0x0040 ,   //未应答NACK
    I2C_IT_TBWE = 0x0080 , //发送数据写错误
    I2C_IT_TIDLE = 0x01000 , //发送空闲中断
}I2C_TYPE_IT;

/* 中断标志位 */
typedef enum
{
    I2C_Flag_SR = 0x0001 ,    //起始位
    I2C_Flag_SP = 0x0002 ,    //停止位
    I2C_Flag_TB = 0x0004 ,    //发送缓冲空
    I2C_Flag_RB = 0x0008 ,    //接收缓冲满
    I2C_Flag_TE = 0x0010 ,    //发送数据错误
    I2C_Flag_RO = 0x0020 ,    //接收数据溢出
    I2C_Flag_NA = 0x0040 ,    //未应答NACK
    I2C_Flag_TBWE = 0x0080,  //发送数据写错误中断标志位
    I2C_Flag_TIDLE= 0X1000,  //I2C 发送空闲中断标志位
}I2C_TYPE_FLAG;


/* 标志清除 */
typedef enum
{
    I2C_Clr_SR = 0x0001 ,   //起始位
    I2C_Clr_SP = 0x0002 ,   //停止位
    I2C_Clr_TE = 0x0010 ,   //发送数据错误
    I2C_Clr_RO = 0x0020 ,   //接收数据溢出
    I2C_Clr_NA = 0x0040 ,   //未应答NACK
    I2C_Clr_TBWE = 0x0080 , //发送数据写错误
    I2C_Clr_TIDLE= 0X01000,  //I2C 发送空闲
}I2C_CLR_IF;


/*************I2C模块宏定义************/

/* I2C模块使能控制 */
#define I2C_Enable() (I2C0->CON.EN = 1)
#define I2C_Disable() (I2C0->CON.EN = 0)

/* I2C模块复位 */
#define I2C_Reset() (I2C0->CON.RST = 1)

/* I2C时基使能控制 */
#define I2C_TJEnable() (I2C0->CON.TJE = 1)
#define I2C_TJDisable() (I2C0->CON.TJE = 0)

/* I2C主控模式读写控制 */
#define I2C_Read() (I2C0->CON.RW = 1)
#define I2C_Write() (I2C0->CON.RW = 0)

/* I2C时钟自动下拉等待使能控制（仅从机模式支持） */
#define I2C_CSEnable() (I2C0->MOD.CSE = 1)
#define I2C_CSDisable() (I2C0->MOD.CSE = 0)

/* I2C自动发送未应答使能控制（仅从机模式支持） */
#define I2C_ANAEnable() (I2C0->MOD.ANAE = 1)
#define I2C_ANADisable() (I2C0->MOD.ANAE = 0)

/* I2C自动寻呼使能控制（仅主机模式支持） */
#define I2C_SRAEnable() (I2C0->MOD.SRAE = 1)
#define I2C_SRADisable() (I2C0->MOD.SRAE = 0)

/* I2C自动结束使能控制（仅主机模式支持） */
#define I2C_SPAEnable() (I2C0->MOD.SPAE = 1)
#define I2C_SPADisable() (I2C0->MOD.SPAE = 0)

/* I2C起始位触发（仅主机模式支持） */
#define I2C_SRTrigger() (I2C0->MOD.SRT=1)

/* I2C停止位触发（仅主机模式支持） */
#define I2C_SPTrigger() (I2C0->MOD.SPT = 1)

/* I2C接收数据触发（仅主机模式支持） */
#define I2C_RDTrigger() (I2C0->MOD.RDT = 1)


/* I2C总线释放 */
#define I2C_Release() (I2C0->MOD.BLD = 1)

/* I2C发送应答设置（仅从机模式支持） */
#define I2C_TACK() (I2C0->MOD.TAS = 1)
#define I2C_TNACK() (I2C0->MOD.TAS = 0)

/************I2C模块函数声明***********/
void I2C_Init(I2C_InitStruType* I2C_InitStruct);
void I2C_ITConfig(I2C_TYPE_IT I2C_IT,TYPE_FUNCEN NewState);
void I2C_SendAddress(uint8_t I2C_Address,I2C_TYPE_RWMODE Mode);
void I2C_SetAddress(uint8_t I2C_Address);
void I2C_RecModeConfig(I2C_TYPE_RECMODE RecType);
void I2C_TBIMConfig(I2C_TYPE_TRBIM Type);
void I2C_RBIMConfig(I2C_TYPE_TRBIM Type);
void I2C_AckDelay(I2C_TYPE_ADLY Type,TYPE_FUNCEN NewStatus);
void I2C_TISConfig(I2C_TYPE_TIS Time);
void I2C_SendByte(uint8_t Byte);
void I2C_SendHalfWord(uint16_t HalfWord);
void I2C_SendWord(uint32_t Word);
uint8_t I2C_RecByte(void);
uint16_t I2C_RecHalfWord(void);
uint32_t I2C_RecWord(void);
I2C_TYPE_RWMODE I2C_GetRWMode(void);
FlagStatus I2C_GetTBStatus(void);
FlagStatus I2C_GetFlagStatus(I2C_TYPE_FLAG I2C_Flag);
FlagStatus I2C_GetITStatus( I2C_TYPE_IT I2C_Flag);
void I2C_ClearITPendingBit(I2C_CLR_IF I2C_IT);

#endif

/*************************END OF FILE**********************/
