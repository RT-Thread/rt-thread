/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_iic.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  IIC模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_iic.h"

/***************************************************************
  函数名：I2C_Init
  描  述：I2C初始化
  输入值：I2C_InitStruct：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_Init(I2C_InitStruType* I2C_InitStruct)
{
    uint32_t temp;

    if(I2C_InitStruct->I2C_Mode == I2C_Mode_Master)
    {
        if(I2C_InitStruct->I2C_16XSamp != DISABLE)
            temp = SystemCoreClock/24/I2C_InitStruct->I2C_Clk - 1;
        else
            temp = SystemCoreClock/16/I2C_InitStruct->I2C_Clk - 1;

        if(temp > 254)
            temp = 255;

        I2C0->CON.TJP = temp;      //设置时基定时器周期

        I2C0->CON.TJE = 0x1;       //使能时基定时器
    }

    I2C0->CON.SDASE = I2C_InitStruct->I2C_16XSamp;  //16倍采样设置
    I2C0->CON.SCKSE = I2C_InitStruct->I2C_16XSamp; 
    I2C0->CON.SCKOD = I2C_InitStruct->I2C_SclOd;    //端口开漏设置
    I2C0->CON.SDAOD = I2C_InitStruct->I2C_SdaOd;
    I2C0->MOD.MS = I2C_InitStruct->I2C_Mode;       //主从模式设置
    I2C0->MOD.SPAE = I2C_InitStruct->I2C_AutoStop; //自动停止设置
    I2C0->MOD.SRAE = I2C_InitStruct->I2C_AutoCall; //自动寻呼设置
}

/***************************************************************
  函数名：I2C_ITConfig
  描  述：I2C中断配置
  输入值：I2C_IT：需要配置的中断 、 NewState：使能或关闭
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_ITConfig(I2C_TYPE_IT I2C_IT,TYPE_FUNCEN NewState)
{
    if (NewState != DISABLE)
        I2C0->IE.Word |= (uint32_t)I2C_IT;
    else
        I2C0->IE.Word &= ~((uint32_t)I2C_IT);
}

/***************************************************************
  函数名：I2C_SendAddress
  描  述：I2C发送从机地址
  输入值：I2C_Address：7位从机地址，左对齐 0x00~0xfe 、 Mode：读或写
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_SendAddress(uint8_t I2C_Address,I2C_TYPE_RWMODE Mode)
{
    I2C0->CON.SA = I2C_Address>>1;
    I2C0->CON.RW = Mode;
}

/***************************************************************
  函数名：I2C_SetAddress
  描  述：I2C设置地址（适用于从机模式）
  输入值：I2C_Address：7位从机地址，左对齐 0x00~0xfe
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_SetAddress(uint8_t I2C_Address)
{
    I2C0->CON.SA = I2C_Address>>1;
}

/***************************************************************
  函数名：I2C_RecModeConfig
  描  述：I2C配置接收模式
  输入值：RecType：接收模式
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_RecModeConfig(I2C_TYPE_RECMODE RecType)
{
    I2C0->MOD.RDM = RecType;
}

/***************************************************************
  函数名：I2C_TBIMConfig
  描  述：I2C发送缓冲器空中断模式选择
  输入值：Type：空中断模式
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_TBIMConfig(I2C_TYPE_TRBIM Type)
{
    I2C0->IE.TBIM = Type;
}

/***************************************************************
  函数名：I2C_RBIMConfig
  描  述：I2C接收缓冲器满中断模式选择
  输入值：Type：满中断模式
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_RBIMConfig(I2C_TYPE_TRBIM Type)
{
    I2C0->IE.RBIM = Type;
}

/***************************************************************
  函数名：I2C_AckDelay
  描  述：I2C应答延时配置
  输入值：Type：延时时间 、 NewStatus：使能、失能
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_AckDelay(I2C_TYPE_ADLY Type,TYPE_FUNCEN NewStatus)
{
    I2C0->MOD.ADLY = Type;
    I2C0->MOD.ADE = NewStatus;
}

/***************************************************************
  函数名：I2C_TISConfig
  描  述：I2C数据帧传输间隔设置
  输入值：Time：传输间隔
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_TISConfig(I2C_TYPE_TIS Time)
{
    I2C0->MOD.TIS = Time;
}

/***************************************************************
  函数名：I2C_SendByte
  描  述：I2C字节发送
  输入值：Byte：字节数据
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_SendByte(uint8_t Byte)
{
    I2C0->TBW.Byte[0] = Byte;
}

/***************************************************************
  函数名：I2C_SendHalfWord
  描  述：I2C半字发送
  输入值：HalfWord：半节数据
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_SendHalfWord(uint16_t HalfWord)
{
    I2C0->TBW.HalfWord[0] = HalfWord;
}

/***************************************************************
  函数名：I2C_SendWord
  描  述：I2C字发送
  输入值：Word：字数据
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_SendWord(uint32_t Word)
{
    I2C0->TBW.Word = Word;
}

/***************************************************************
  函数名：I2C_RecByte
  描  述：I2C接收-字节
  输入值：无
  输出值：无
  返回值：接收的数据
 ***************************************************************/
uint8_t I2C_RecByte(void)
{
    return I2C0->RBR.Byte[0] ;
}

/***************************************************************
  函数名：I2C_RecHalfWord
  描  述：I2C接收-半字
  输入值：无
  输出值：无
  返回值：接收的数据
 ***************************************************************/
uint16_t I2C_RecHalfWord(void)
{
    return I2C0->RBR.HalfWord[0];
}

/***************************************************************
  函数名：I2C_RecWord
  描  述：I2C接收-字
  输入值：无
  输出值：无
  返回值：接收的数据
 ***************************************************************/
uint32_t I2C_RecWord(void)
{
    return I2C0->RBR.Word ;
}

/***************************************************************
  函数名：I2C_GetRWMode
  描  述：I2C工作读写状态读取
  输入值：无
  输出值：无
  返回值：读/写
 ***************************************************************/
I2C_TYPE_RWMODE I2C_GetRWMode(void)
{
    I2C_TYPE_RWMODE Status = I2C_Mode_Write;

    if(I2C0->CON.RW != 0)
        Status = I2C_Mode_Read;
    else
        Status = I2C_Mode_Write;

    return Status;
}

/***************************************************************
  函数名：I2C_GetTBStatus
  描  述：I2C获取发送缓冲寄存器状态,TB0-TB3全空则返回SET,否则返回RESET
  输入值：无
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus I2C_GetTBStatus(void)
{
    FlagStatus bitstatus = RESET;

    if((I2C0->STA.Word&(uint32_t)0x0f00) != (uint32_t)0x0f00)
        bitstatus = RESET;
    else
        bitstatus = SET;

    return  bitstatus;
}

/***************************************************************
  函数名：I2C_GetFlagStatus
  描  述：I2C获取标志位状态
  输入值：I2C_Flag：选择需要的标志位
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus I2C_GetFlagStatus(I2C_TYPE_FLAG I2C_Flag)
{
    FlagStatus bitstatus = RESET;

    if ((I2C0->IF.Word & (uint32_t)I2C_Flag) != RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/*************************************
  函数名：I2C_GetITStatus
  描  述：获取中断使能状态
  输入值：I2C_Flag 中断使能位
  中断类型
  返回值：SET/RESET
 **************************************/
FlagStatus I2C_GetITStatus( I2C_TYPE_IT I2C_Flag)
{
    FlagStatus status = RESET;

    if ((I2C0->IE.Word & (uint32_t)I2C_Flag) == RESET)
        return status;

    if ((I2C0->IF.Word & (uint32_t)I2C_Flag) != RESET)
        status = SET;

    return status;
}

/***************************************************************
  函数名：I2C_ClearITPendingBit
  描  述：I2C中断标志清除
  输入值：I2C_IT：标志位
  输出值：无
  返回值：无
 ***************************************************************/
void I2C_ClearITPendingBit(I2C_CLR_IF I2C_IT)
{
    I2C0->IF.Word = (uint32_t)I2C_IT;
}

/*************************END OF FILE**********************/

