/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名： lib_uart.h
 *作 者： Liut
 *版 本： V1.00
 *日 期： 2017/07/14
 *描 述： UART模块库函数头文件
 *备 注： 适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBUART_H__
#define __LIBUART_H__

#include "ES8P508x.h"
#include "type.h"
#include "system_ES8P508x.h"

/* 发送帧停止位选择 */
typedef enum
{
    UART_StopBits_1 = 0x0 , //发送帧停止位：1位
    UART_StopBits_2 = 0x1 , //发送帧停止位：2位
}UART_TYPE_TXFS;

/* 数据格式 */
typedef enum
{
    UART_DataMode_7 = 0x0 ,    //数据格式:7位数据
    UART_DataMode_8 = 0x1 ,    //数据格式:8位数据
    UART_DataMode_9 = 0x2 ,    //数据格式:9位数据
    UART_DataMode_7Odd = 0x4 , //数据格式:7位数据+奇校验
    UART_DataMode_7Even = 0x5 , //数据格式:7位数据+偶校验
    UART_DataMode_8Odd = 0x6 , //数据格式:8位数据+奇校验
    UART_DataMode_8Even = 0x7 , //数据格式:8位数据+偶校验
}UART_TYPE_DATAMOD;

/* 端口极性 */
typedef enum
{
    UART_Polar_Normal = 0x0 ,   //发送端口极性:正常
    UART_Polar_Opposite = 0x1 , //发送端口极性:反向
}UART_TYPE_RTXP;

/* 波特率发生器时钟选择 */
typedef enum
{
    UART_Clock_1 = 0x1 , //波特率发生器时钟:PCLK
    UART_Clock_2 = 0x2 , //波特率发生器时钟:PCLK/2
    UART_Clock_4 = 0x3 , //波特率发生器时钟:PCLK/4
	  UART_Clock_8 = 0x4 , //波特率发生器时钟:PCLK/8
	  
}UART_TYPE_BCS;

/* UART初始化配置结构体定义 */
typedef struct
{
    UART_TYPE_TXFS  UART_StopBits;  //发送帧停止位选择
    UART_TYPE_DATAMOD  UART_TxMode; //发送数据帧格式
    UART_TYPE_RTXP  UART_TxPolar;   //发送端口极性
    UART_TYPE_DATAMOD  UART_RxMode; //接收数据帧格式
    UART_TYPE_RTXP  UART_RxPolar;   //接收端口极性
    uint32_t  UART_BaudRate;        //传输波特率
    UART_TYPE_BCS  UART_ClockSet;   //波特率发生器时钟选择
}UART_InitStruType;

/* 中断选择 */
typedef enum
{
    UART_IT_TB = 0x0001 ,
    UART_IT_RB = 0x0002 ,
    UART_IT_RO = 0x0004 ,
    UART_IT_FE = 0x0008 ,
    UART_IT_PE = 0x0010 ,
    UART_IT_TBWE = 0x0020 ,
    UART_IT_TXIDLE = 0x1000 ,
    UART_IT_RXIDLE = 0x2000 ,
}UART_TYPE_IT;

/* 标志位 */
typedef enum
{
	  UART_FLAG_TB = 0x0001 ,
    UART_FLAG_RB = 0x0002 ,
    UART_FLAG_RO = 0x0004 ,
    UART_FLAG_FE = 0x0008 ,
    UART_FLAG_PE = 0x0010 ,
    UART_FLAG_TBWE = 0x0020 ,
    UART_FLAG_TXIDLE = 0x1000 ,
    UART_FLAG_RXIDLE = 0x2000 ,
}UART_TYPE_FLAG;

/*  清除中断标志位 */
typedef enum
{
    UART_Clr_RO = 0x0004 ,
    UART_Clr_FE = 0x0008 ,
    UART_Clr_PE = 0x0010 ,
    UART_Clr_TBWE = 0x0020 ,
}UART_CLR_IF;

/* 发送、接收中断模式 */
typedef enum
{
    UART_TRBIM_Byte = 0x0 ,     //中断:字节
    UART_TRBIM_HalfWord = 0x1 , //中断:半字
    UART_TRBIM_Word = 0x2 ,     //中断:字
}UART_TYPE_TRBIM;

/*************UART模块宏定义************/
/* 发送使能控制 */
#define UART0_TxEnable() (UART0->CON.TXEN = 1)
#define UART1_TxEnable() (UART1->CON.TXEN = 1)
#define UART2_TxEnable() (UART2->CON.TXEN = 1)
#define UART3_TxEnable() (UART3->CON.TXEN = 1)
#define UART4_TxEnable() (UART4->CON.TXEN = 1)
#define UART5_TxEnable() (UART5->CON.TXEN = 1)
#define UART0_TxDisable() (UART0->CON.TXEN = 0)
#define UART1_TxDisable() (UART1->CON.TXEN = 0)
#define UART2_TxDisable() (UART2->CON.TXEN = 0)
#define UART3_TxDisable() (UART3->CON.TXEN = 0)
#define UART4_TxDisable() (UART4->CON.TXEN = 0)
#define UART5_TxDisable() (UART5->CON.TXEN = 0)

/* 接收使能控制 */
#define UART0_RxEnable() (UART0->CON.RXEN = 1)
#define UART1_RxEnable() (UART1->CON.RXEN = 1)
#define UART2_RxEnable() (UART2->CON.RXEN = 1)
#define UART3_RxEnable() (UART3->CON.RXEN = 1)
#define UART4_RxEnable() (UART4->CON.RXEN = 1)
#define UART5_RxEnable() (UART5->CON.RXEN = 1)
#define UART0_RxDisable() (UART0->CON.RXEN = 0)
#define UART1_RxDisable() (UART1->CON.RXEN = 0)
#define UART2_RxDisable() (UART2->CON.RXEN = 0)
#define UART3_RxDisable() (UART3->CON.RXEN = 0)
#define UART4_RxDisable() (UART4->CON.RXEN = 0)
#define UART5_RxDisable() (UART5->CON.RXEN = 0)

/* 发送器复位 */
#define UART0_TxRst() (UART0->CON.TRST = 1)
#define UART1_TxRst() (UART1->CON.TRST = 1)
#define UART2_TxRst() (UART2->CON.TRST = 1)
#define UART3_TxRst() (UART3->CON.TRST = 1)
#define UART4_TxRst() (UART4->CON.TRST = 1)
#define UART5_TxRst() (UART5->CON.TRST = 1)

/* 接收器复位 */
#define UART0_RxRst() (UART0->CON.RRST = 1)
#define UART1_RxRst() (UART1->CON.RRST = 1)
#define UART2_RxRst() (UART2->CON.RRST = 1)
#define UART3_RxRst() (UART3->CON.RRST = 1)
#define UART4_RxRst() (UART4->CON.RRST = 1)
#define UART5_RxRst() (UART5->CON.RRST = 1)

/************UART模块函数声明***********/
void UART_Init(UART_TypeDef* UARTx,UART_InitStruType* UART_InitStruct);
void UART_ITConfig(UART_TypeDef* UARTx,UART_TYPE_IT UART_IT,TYPE_FUNCEN NewState);
void UART_TBIMConfig(UART_TypeDef* UARTx,UART_TYPE_TRBIM Type);
void UART_RBIMConfig(UART_TypeDef* UARTx,UART_TYPE_TRBIM Type);
void UART_SendByte(UART_TypeDef* UARTx,uint8_t Temp08);
void UART_SendHalfWord(UART_TypeDef* UARTx,uint16_t Temp16);
void UART_SendWord(UART_TypeDef* UARTx,uint32_t Temp32);
uint8_t UART_RecByte(UART_TypeDef* UARTx);
uint16_t UART_RecHalfWord(UART_TypeDef* UARTx);
uint32_t UART_RecWord(UART_TypeDef* UARTx);
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx,UART_TYPE_FLAG UART_Flag);
ITStatus UART_GetITStatus(UART_TypeDef* UARTx,UART_TYPE_IT UART_Flag);
void UART_ClearITPendingBit(UART_TypeDef* UARTx,UART_CLR_IF UART_Flag);

#endif

/*************************END OF FILE**********************/
