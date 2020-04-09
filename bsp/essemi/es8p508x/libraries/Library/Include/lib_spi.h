/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名： lib_spi.h
 *作 者： Liut
 *版 本： V1.00
 *日 期： 2017/07/14
 *描 述： SPI模块库函数头文件
 *备 注： 适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBSPI_H__
#define __LIBSPI_H__

#include "system_ES8P508x.h"
#include "ES8P508x.h"
#include "type.h"

/* 通信数据格式 */
typedef enum
{
    SPI_RiseSendFallRec = 0x0 , //通信数据格式：上升沿发送（先），下降沿接收（后）
    SPI_FallSendRiseRec = 0x1 , //通信数据格式：下降沿发送（先），上升沿接收（后）
    SPI_RiseRecFallSend = 0x2 , //通信数据格式：上升沿接收（先），下降沿发送（后）
    SPI_FallRecRiseSend = 0x3 , //通信数据格式：下降沿接收（先），上升沿发送（后）
}SPI_TYPE_DFS;

/* 通讯模式 */
typedef enum
{
    SPI_Mode_Master = 0x0 , //通讯模式：主控
    SPI_Mode_Slave = 0x1 ,  //通讯模式：从动
}SPI_TYPE_MODE;

/* ADC初始化配置结构体定义 */
typedef struct
{
    uint32_t  SPI_Freq;          //SPI频率 

    SPI_TYPE_DFS  SPI_Df;        //通讯数据格式

    SPI_TYPE_MODE  SPI_Mode;     //通讯模式

    uint8_t SPI_DW;             //发送帧位宽

    TYPE_FUNCEN  SPI_DelayRec;   //延时接收使能

    TYPE_FUNCEN  SPI_DelaySend;  //发送间隔使能

    uint8_t  SPI_SendDelayPeroid;//发送间隔周期

}SPI_InitStruType;

/* 标志位 */
typedef enum
{
    SPI_Flag_TB = 0x00000001,
    SPI_Flag_RB = 0x00000002,
    SPI_Flag_TE = 0x00000004,
    SPI_Flag_RO = 0x00000008,
    SPI_Flag_ID = 0x00000010,
    SPI_Flag_NSSIF = 0x00000020,
    SPI_Flag_TBWE = 0x00000040,
    SPI_Flag_NSS = 0x00000080,
    SPI_Flag_TBEF0 = 0x00000100,
    SPI_Flag_TBEF1 = 0x00000200,
    SPI_Flag_TBEF2 = 0x00000400,
    SPI_Flag_TBEF3 = 0x00000800,
    SPI_Flag_RBFF0 = 0x00001000,
    SPI_Flag_RBFF1 = 0x00002000,
    SPI_Flag_RBFF2 = 0x00004000,
    SPI_Flag_RBFF3 = 0x00008000,
    SPI_Flag_IDLE = 0x00010000,
    SPI_Flag_TMS = 0x00020000,
}SPI_TYPE_FLAG;

/* 中断模式选择 */
typedef enum
{
    SPI_IType_BYTE = 0x0 ,
    SPI_IType_HALFWORD = 0x1 ,
    SPI_IType_WORD = 0x2 ,
}SPI_TYPE_TRBIM;

/* SPI中断 */
typedef enum
{
    SPI_IT_TB = 0x01 ,
    SPI_IT_RB = 0x02 ,
    SPI_IT_TE = 0x04 ,
    SPI_IT_RO = 0x08 ,
    SPI_IT_ID = 0x10 ,
    SPI_IT_NSS = 0x20 ,
    SPI_IT_TBWE = 0x40 ,
}SPI_TYPE_IT;

/* SPI清除中断标志 */
typedef enum
{
    SPI_Clr_TE = 0x04 ,
    SPI_Clr_RO = 0x08 ,
    SPI_Clr_ID = 0x10 ,
    SPI_Clr_NSS = 0x20 ,
    SPI_Clr_TBWE = 0x40 ,
}SPI_CLR_IF;

/************SPI模块宏定义***********/

/* SPI使能控制 */
#define SPI_Enable()  (SPI0->CON.EN = 1)
#define SPI_Disable() (SPI0->CON.EN = 0)

/* SPI接收使能控制 */
#define SPI_RecEnable()  (SPI0->CON.REN = 1)
#define SPI_RecDisable() (SPI0->CON.REN = 0)

/* SPI软件复位 */
#define SPI_Rst() (SPI0->CON.RST = 1)

/* SPI缓冲器清空 */
#define SPI_RX_CLR() (SPI0->CON.RXCLR = 1)
#define SPI_TX_CLR() (SPI0->CON.TXCLR = 1)

/************SPI模块函数声明***********/
void SPI_Init(SPI_InitStruType* SPI_InitStruct);
void SPI_ITConfig(SPI_TYPE_IT SPI_IE,TYPE_FUNCEN NewState);
void SPI_DataFormatConfig(SPI_TYPE_DFS Type);
void SPI_SendByte(uint8_t Temp);
void SPI_SendHalfWord(uint16_t Temp);
void SPI_SendWord(uint32_t Temp);
uint8_t SPI_RecByte(void);
uint16_t SPI_RecHalfWord(void);
uint32_t SPI_RecWord(void);
void SPI_TBIMConfig(SPI_TYPE_TRBIM Type);
void SPI_RBIMConfig(SPI_TYPE_TRBIM Type);
FlagStatus SPI_GetFlagStatus(SPI_TYPE_FLAG Flag);
ITStatus SPI_GetITStatus(SPI_TYPE_IT Flag);
void SPI_ClearITPendingBit(SPI_CLR_IF Flag);

#endif

/*************************END OF FILE**********************/
