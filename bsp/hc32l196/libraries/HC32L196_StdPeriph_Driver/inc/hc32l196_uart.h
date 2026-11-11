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
/** \file uart.h
 **
 ** Headerfile for UART functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __UART_H__
#define __UART_H__
/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "hc32l196_ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup UartGroup Universal Asynchronous Receiver/Transmitter (UART)
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
 **\brief uart通道选择
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief uart多机模式地址帧/数据帧或者奇偶校验
 ******************************************************************************/
typedef enum en_uart_mmdorck
{
    UartMskDataOrAddr = 0u,     ///<多机模式时，通过读写SBUF[8]决定帧为数据帧或地址帧
    UartMskEven       = 0x4u,   ///<非多机模式偶校验   
    UartMskOdd        = 0x8u,   ///<非多机模式奇校验    
}en_uart_mmdorck_t;

/**
 ******************************************************************************
 ** \brief uart多机模式及从机地址和地址掩码配置
 ******************************************************************************/
typedef struct stc_uart_multimode
{
    uint8_t             u8SlaveAddr;    ///<从机地址
    uint8_t             u8SaddEn;       ///<从及地址掩码
}stc_uart_multimode_t;

/**
 ******************************************************************************
 ** \brief uart 四种工作模式选择
 ******************************************************************************/

typedef enum en_uart_mode
{
    UartMskMode0 = 0x00u, ///<模式0    
    UartMskMode1 = 0x40u, ///<模式1
    UartMskMode2 = 0x80u, ///<模式2
    UartMskMode3 = 0xc0u, ///<模式3
} en_uart_mode_t;
/**
 ******************************************************************************
 ** \brief uart stop长度选择
 ******************************************************************************/

typedef enum en_uart_stop
{
    UartMsk1bit   = 0x0000u, ///<1位停止位 
    UartMsk1_5bit = 0x4000u, ///<1.5位停止位
    UartMsk2bit   = 0x8000u, ///<2位停止位
} en_uart_stop_t;
/**
 ******************************************************************************
 ** \brief uart 功能使能
 ******************************************************************************/
typedef enum en_uart_func
{
    UartRenFunc    = 4u,    ///<0-TX; ///<1-非mode0模式代表RX&TX ,mode0模式代表RX;       
    UartDmaRxFunc  = 16u,   ///<DMA接收功能   
    UartDmaTxFunc  = 17u,   ///<DMA发送功能
    UartRtsFunc    = 18u,   ///<硬件流RTS功能
    UartCtsFunc    = 19u,   ///<硬件流CTS功能
    UartHdFunc     = 22u,   ///<单线半双工功能    
}en_uart_func_t;
/**
 ******************************************************************************
 ** \brief uart中断使能控制
 ******************************************************************************/
typedef enum en_uart_irq_sel
{
    UartRxIrq  = 0u,    ///<接收中断使能
    UartTxIrq  = 1u,    ///<发送中断使能        
    UartTxEIrq = 8u,    ///<TX空中断使能
    UartPEIrq  = 13u,   ///<奇偶校验中断使能
    UartCtsIrq = 20u,   ///<CTS信号翻转中断使能    
    UartFEIrq  = 21u,   ///<帧错误中断使能 
}en_uart_irq_sel_t;

/**
 ******************************************************************************
 ** \brief uart 状态标志位
 ******************************************************************************/
typedef enum en_uart_status
{
    UartRC    = 0u,  ///<接收数据完成标记
    UartTC    = 1u,  ///<发送数据完成标记
    UartFE    = 2u,  ///<帧错误标记
    UartTxe   = 3u,  ///<TXbuff空标记    
    UartPE    = 4u,  ///<奇偶校验错误标记
    UartCtsIf = 5u,  ///<CTS中断标记
    UartCts   = 6u,  ///<CTS信号标记
}en_uart_status_t;

/**
 ******************************************************************************
 ** \brief uart 通道采样分频配置
 ******************************************************************************/
typedef enum en_uart_clkdiv
{
    UartMsk16Or32Div = 0u,      ///<模式0无效，模式1/3为16分频，模式2为32分频
    UartMsk8Or16Div  = 0x200u,  ///<模式0无效，模式1/3为8分频，模式2为16分频
}en_uart_clkdiv_t;
/**
 ******************************************************************************
 ** \brief uart 通道Mode1和Mode3波特率计算参数
 ******************************************************************************/
typedef struct stc_uart_baud
{
    en_uart_clkdiv_t     enClkDiv;      ///<采样分频
    uint32_t             u32Pclk;       ///<pclk
    uint32_t             u32Baud;       ///<波特率
} stc_uart_baud_t;
/**
 ******************************************************************************
 ** \uart 总体配置
 ******************************************************************************/

typedef struct stc_uart_cfg
{
    en_uart_mode_t       enRunMode;     ///<四种模式配置
    en_uart_mmdorck_t    enMmdorCk;     ///<校验模式
    en_uart_stop_t       enStopBit;     ///<停止位长度
    stc_uart_baud_t      stcBaud;       ///<Mode1/3波特率配置
} stc_uart_cfg_t;

//UART初始化
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg);

///< UART 单线模式使能/禁止
void Uart_HdModeEnable(M0P_UART_TypeDef* UARTx);
void Uart_HdModeDisable(M0P_UART_TypeDef* UARTx);

//UART模块多机模式设置函数
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx,stc_uart_multimode_t* pstcMultiCfg);

//TB8数据设置
void Uart_SetTb8(M0P_UART_TypeDef* UARTx, boolean_t bTB8Value);
//RB8数据获取
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx);

//中断相关设置函数
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);
                             
//功能使能和禁止
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);

//状态位的获取和清除 
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx);
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus);
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx);
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus);

//数据收发操作
///< 数据查询模式发送
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
///< 数据中断模式发送
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx);

//@} // UartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



