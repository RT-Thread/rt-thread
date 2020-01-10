/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_uart.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  UART模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_uart.h"

/***************************************************************
  函数名：UART_Init
  描  述：UART初始化
  输入值：UARTx：可以是UART0/1/2/3/4/5 、 UART_InitStruct：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void UART_Init(UART_TypeDef* UARTx,UART_InitStruType* UART_InitStruct)
{
    uint32_t BaudClockTemp = 0, BaudTemp = 0;

    if(UART_InitStruct->UART_ClockSet == UART_Clock_1)
    {
        BaudClockTemp = (SystemCoreClock/16)%UART_InitStruct->UART_BaudRate;
        if(UART_InitStruct->UART_BaudRate >= (2*BaudClockTemp))
        {
            BaudTemp = (SystemCoreClock/16/UART_InitStruct->UART_BaudRate)-1;
        }
        else
        {
            BaudTemp = SystemCoreClock/16/UART_InitStruct->UART_BaudRate;
        }
    }
    else if(UART_InitStruct->UART_ClockSet == UART_Clock_2)
    {
        BaudClockTemp = (SystemCoreClock/32)%UART_InitStruct->UART_BaudRate;
        if(UART_InitStruct->UART_BaudRate >= (2*BaudClockTemp))
        {
            BaudTemp = (SystemCoreClock/32/UART_InitStruct->UART_BaudRate)-1;
        }
        else
        {
            BaudTemp = SystemCoreClock/32/UART_InitStruct->UART_BaudRate;
        }
    }
    else if(UART_InitStruct->UART_ClockSet == UART_Clock_4)
    {
        BaudClockTemp = (SystemCoreClock/64)%UART_InitStruct->UART_BaudRate;
        if(UART_InitStruct->UART_BaudRate >= (2*BaudClockTemp))
        {
            BaudTemp = (SystemCoreClock/64/UART_InitStruct->UART_BaudRate)-1;
        }
        else
        {
            BaudTemp = SystemCoreClock/64/UART_InitStruct->UART_BaudRate;
        }
    }

    if(BaudTemp > 2046)
    {
        BaudTemp = 2047;
    }

    UARTx->CON.BCS = UART_InitStruct->UART_ClockSet;
    UARTx->BRR.BRR = BaudTemp ;

    UARTx->CON.TXFS = UART_InitStruct->UART_StopBits;
    UARTx->CON.TXMOD = UART_InitStruct->UART_TxMode;
    UARTx->CON.TXP = UART_InitStruct->UART_TxPolar;
    UARTx->CON.RXMOD = UART_InitStruct->UART_RxMode;
    UARTx->CON.RXP = UART_InitStruct->UART_RxPolar;
}
/***************************************************************
  函数名：UART_ITConfig
  描  述：UART中断配置
  输入值：UARTx：可以是UART0/1/2/3/4/5 、 UART_IT：中断类型 、 NewState：使能/失能
  输出值：无
  返回值：无
 ***************************************************************/
void UART_ITConfig(UART_TypeDef* UARTx,UART_TYPE_IT UART_IT,TYPE_FUNCEN NewState)
{
    if (NewState != DISABLE)
        UARTx->IE.Word = (UARTx->IE.Word & (uint32_t)0x0000FFFF) | (uint32_t) UART_IT;
    else
        UARTx->IE.Word = (UARTx->IE.Word & (uint32_t)0x0000FFFF) & (~((uint32_t) UART_IT));
}
/***************************************************************
  函数名：UART_TBIMConfig
  描  述：UART发送缓冲器空中断模式选择
  输入值：UARTx：可以是UART0/1/2/3/4/5 、 Type：空中断模式
  输出值：无
  返回值：无
 ***************************************************************/
void UART_TBIMConfig(UART_TypeDef* UARTx,UART_TYPE_TRBIM Type)
{
    UARTx->IE.TBIM = Type;
}
/***************************************************************
  函数名：UART_RBIMConfig
  描  述：UART接收缓冲器满中断模式选择
  输入值：UARTx：可以是UART0/1/2/3 、 Type：满中断模式
  输出值：无
  返回值：无
 ***************************************************************/
void UART_RBIMConfig(UART_TypeDef* UARTx,UART_TYPE_TRBIM Type)
{
    UARTx->IE.RBIM = Type;
}
/***************************************************************
  函数名：UART_Sendxxxx
  描  述：UART发送字节、半字、字
  输入值：UARTx：可以是UART0/1/2/3/4/5 、 数据
  输出值：无
  返回值：无
 ***************************************************************/
void UART_SendByte(UART_TypeDef* UARTx,uint8_t Temp08)
{
    UARTx->TBW.Byte[0] = Temp08;
}
void UART_SendHalfWord(UART_TypeDef* UARTx,uint16_t Temp16)
{
    UARTx->TBW.HalfWord[0] = Temp16;
}
void UART_SendWord(UART_TypeDef* UARTx,uint32_t Temp32)
{
    UARTx->TBW.Word = Temp32;
}
/***************************************************************
  函数名：UART_Recxxxx
  描  述：UART接收字节、半字、字
  输入值：UARTx：可以是UART0/1/2/3/4/5
  输出值：无
  返回值：数据
 ***************************************************************/
uint8_t UART_RecByte(UART_TypeDef* UARTx)
{
    return UARTx->RBR.Byte[0];
}
uint16_t UART_RecHalfWord(UART_TypeDef* UARTx)
{
    return UARTx->RBR.HalfWord[0];
}
uint32_t UART_RecWord(UART_TypeDef* UARTx)
{
    return UARTx->RBR.Word;
}
/***************************************************************
  函数名：UART_GetFlagStatus
  描  述：UART获取标志位状态
  输入值：UARTx：可以是UART0/1/2/3/4/5 、 UART_Flag：标志位
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx,UART_TYPE_FLAG UART_Flag)
{
    FlagStatus bitstatus = RESET;

    if ((UARTx->IF.Word & ((uint32_t)UART_Flag)) != RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return bitstatus;
}

/***************************************************************
  函数名：UART_GetITStatus
  描  述：UART获取中断状态
  输入值：UARTx：可以是UART0/1/2/3/4/5 、 UART_Flag：标志位
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
ITStatus UART_GetITStatus(UART_TypeDef* UARTx,UART_TYPE_IT UART_IT)
{
    FlagStatus bitstatus = RESET;

    if((UARTx->IE.Word & ((uint32_t)UART_IT)) == 0)
        bitstatus = RESET;
    else
        bitstatus = SET;

    return bitstatus;
}
/***************************************************************
  函数名：UART_ClearIFPendingBit
  描  述：UART标志位清除
  输入值：UARTx：可以是UART0/1/2/3/4/5、 UART_Flag：标志位
  输出值：无
  返回值：无
 ***************************************************************/
void UART_ClearIFPendingBit(UART_TypeDef* UARTx,UART_CLR_IF UART_Flag)
{
    UARTx->IF.Word = (uint32_t)UART_Flag;
}

/*************************END OF FILE**********************/
