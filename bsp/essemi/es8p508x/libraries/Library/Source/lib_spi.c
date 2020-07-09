/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_spi.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  SPI模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_spi.h"

/***************************************************************
  函数名：SPI0_Init
  描  述：SPI初始化
  输入值：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_Init(SPI_InitStruType* SPI_InitStruct)
{
    uint32_t Temp = 0;

    Temp = SystemCoreClock / (SPI_InitStruct->SPI_Freq * 2);
    if(Temp > 254)
        Temp = 255;
    
    SPI0->CKS.CKS = Temp;
    
    SPI0->CON.DFS = SPI_InitStruct->SPI_Df;
    SPI0->CON.MS = SPI_InitStruct->SPI_Mode;
    SPI0->CON.DW = SPI_InitStruct->SPI_DW;
    SPI0->CON.DRE = SPI_InitStruct->SPI_DelayRec;
    SPI0->CON.TME = SPI_InitStruct->SPI_DelaySend;

    Temp = (uint32_t)SPI_InitStruct->SPI_SendDelayPeroid - 1;
    if(Temp > 62)
        Temp = 63;

    SPI0->CON.TMP = Temp;
}

/***************************************************************
  函数名：SPI0_ITConfig
  描  述：SPI中断配置
  输入值：SPI_IE：中断类型 、 NewState：使能、失能
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_ITConfig(SPI_TYPE_IT SPI_IE,TYPE_FUNCEN NewState)
{
    if(NewState != DISABLE)
        SPI0->IE.Word |= (uint32_t)SPI_IE;
    else
        SPI0->IE.Word &= ~((uint32_t)SPI_IE);
}

/***************************************************************
  函数名：SPI0_DataFormatConfig
  描  述：SPI数据格式配置
  输入值：数据格式
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_DataFormatConfig(SPI_TYPE_DFS Type)
{
    SPI0->CON.DFS = Type;
}

/***************************************************************
  函数名：SPI0_SendByte
  描  述：SPI发送一个字节（8位）
  输入值：要发送的数据
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_SendByte(uint8_t Temp)
{
    SPI0->TBW.Byte[0] = Temp;
}

/***************************************************************
  函数名：SPI0_SendHalfWord
  描  述：SPI发送一个半字（16位）
  输入值：要发送的数据
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_SendHalfWord(uint16_t Temp)
{
    SPI0->TBW.HalfWord[0] = Temp;
}

/***************************************************************
  函数名：SPI0_SendWord
  描  述：SPI发送一个字（32位）
  输入值：要发送的数据
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_SendWord(uint32_t Temp)
{
    SPI0->TBW.Word = Temp;
}

/***************************************************************
  函数名：SPI0_RecByte
  描  述：SPI接收一个字节
  输入值：无
  输出值：无
  返回值：接收的数据
 ***************************************************************/
uint8_t SPI_RecByte(void)
{
    return SPI0->RBR.Byte[0];
}

/***************************************************************
  函数名：SPI0_RecHalfWord
  描  述：SPI接收一个半字
  输入值：无
  输出值：无
  返回值：接收的数据
 ***************************************************************/
uint16_t SPI_RecHalfWord(void)
{
    return SPI0->RBR.HalfWord[0];
}

/***************************************************************
  函数名：SPI0_RecWord
  描  述：SPI接收一个字
  输入值：无
  输出值：无
  返回值：接收的数据
 ***************************************************************/
uint32_t SPI_RecWord(void)
{
    return SPI0->RBR.Word;
}

/***************************************************************
  函数名：SPI0_TBIMConfig
  描  述：SPI发送缓冲器空中断模式选择
  输入值：空中断模式
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_TBIMConfig(SPI_TYPE_TRBIM Type)
{
    SPI0->IE.TBIM = Type;
}

/***************************************************************
  函数名：SPI0_RBIMConfig
  描  述：SPI接收缓冲器满中断模式选择
  输入值：满中断模式
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_RBIMConfig(SPI_TYPE_TRBIM Type)
{
    SPI0->IE.RBIM = Type;
}

/***************************************************************
  函数名：SPI0_GetFlagStatus
  描  述：SPI检查标志位状态
  输入值：标志位
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus SPI_GetFlagStatus(SPI_TYPE_FLAG Flag)
{
    FlagStatus bitstatus = RESET;

    /* 读取寄存器 */
    if((uint32_t)Flag <= 0x00000040)
    {
        if ((SPI0->IF.Word & Flag) != (uint32_t)RESET)
            bitstatus = SET;
        else
            bitstatus = RESET;
    }

    else
    {
        if ((SPI0->STA.Word & Flag) != (uint32_t)RESET)
            bitstatus = SET;
        else
            bitstatus = RESET;
    }

    return  bitstatus;
}

/***************************************************************
  函数名：SPI0_GetITStatus
  描  述：SPI检查中断状态,未使能相应中断时不会返回SET
  输入值：中断标志位
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
ITStatus SPI_GetITStatus(SPI_TYPE_IT Flag)
{
    FlagStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    itstatus = SPI0->IF.Word & (uint32_t)Flag;
    itenable = SPI0->IE.Word & (uint32_t)Flag;

    if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;    
}

/***************************************************************
  函数名：SPI0_ClearITPendingBit
  描  述：SPI中断标志清除
  输入值：标志位
  输出值：无
  返回值：无
 ***************************************************************/
void SPI_ClearITPendingBit(SPI_CLR_IF Flag)
{
    SPI0->IF.Word = (uint32_t)Flag;
}

/*************************END OF FILE**********************/

