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
/** \file lpuart.h
 **
 ** Headerfile for LPUART functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __LPUART_H__
#define __LPUART_H__
/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup LPUartGroup Universal Asynchronous Receiver/Transmitter (LPUART)
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
 **\brief LPuart通道选择
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief lpuart 的sclk时钟源选择
 ******************************************************************************/

typedef enum en_lpuart_sclk_sel
{
    LPUartMskPclk   = 0u<<11, ///<pclk
    LPUartMskXtl    = 2u<<11, ///<外部低速晶振
    LPUartMskRcl    = 3u<<11, ///<内部低速晶振
} en_lpuart_sclksel_t;

/**
 ******************************************************************************
 ** \brief lpuart多机模式地址帧/数据帧或者奇偶校验
 ******************************************************************************/
typedef enum en_lpuart_mmdorck
{
    LPUartDataOrAddr = 0u, ///<多机模式时，通过读写SBUF[8]决定帧为数据帧或地址帧
    LPUartEven       = 0x4u, ///<非多机模式偶校验   
    LPUartOdd        = 0x8u, ///<非多机模式奇校验    
}en_lpuart_mmdorck_t;

/**
 ******************************************************************************
 ** \brief lpuart多机模式及从机地址和地址掩码配置
 ******************************************************************************/

typedef struct stc_lpuart_multimode
{
    uint8_t             u8SlaveAddr;  ///<从机地址
    uint8_t             u8SaddEn;  ///<从及地址掩码
}stc_lpuart_multimode_t;

/**
 ******************************************************************************
 ** \brief lpuart 四种工作模式选择
 ******************************************************************************/

typedef enum en_lpuart_mode
{
    LPUartMskMode0 = 0x00u, ///<模式0    
    LPUartMskMode1 = 0x40u, ///<模式1
    LPUartMskMode2 = 0x80u, ///<模式2
    LPUartMskMode3 = 0xc0u, ///<模式3
} en_lpuart_mode_t;
/**
 ******************************************************************************
 ** \brief lpuart stop长度选择
 ******************************************************************************/

typedef enum en_lpuart_stop
{
    LPUart1bit  = 0x0000u,  ///<1位停止位 
    LPUart1_5bit = 0x4000u, ///<1.5位停止位
    LPUart2bit  = 0x8000u,  ///<2位停止位
} en_lpuart_stop_t;
/**
 ******************************************************************************
 ** \brief lpuart 功能使能
 ******************************************************************************/
typedef enum en_lpuart_func
{
    LPUartRenFunc    = 4u,    ///<0-TX; ///<1-非mode0模式代表RX&TX ,mode0模式代表RX;       
    LPUartDmaRxFunc  = 16u,   ///<DMA接收功能   
    LPUartDmaTxFunc  = 17u,   ///<DMA发送功能
    LPUartRtsFunc    = 18u,   ///<硬件流RTS功能
    LPUartCtsFunc    = 19u,   ///<硬件流CTS功能
    LPUartHdFunc     = 22u,   ///<单线半双工功能    
}en_lpuart_func_t;
/**
 ******************************************************************************
 ** \brief lpuart中断使能控制
 ******************************************************************************/
typedef enum en_lpuart_irq_sel
{
    LPUartRxIrq  = 0u,    ///<接收中断使能
    LPUartTxIrq  = 1u,    ///<发送中断使能        
    LPUartTxEIrq = 8u,    ///<TX空中断使能
    LPUartPEIrq  = 13u,   ///<奇偶校验中断使能
    LPUartCtsIrq = 20u,   ///<CTS信号翻转中断使能    
    LPUartFEIrq  = 21u,   ///<帧错误中断使能 
}en_lpuart_irq_sel_t;

/**
 ******************************************************************************
 ** \brief lpuart 状态标志位
 ******************************************************************************/
typedef enum en_lpuart_status
{
    LPUartRC    = 0u,  ///<接收数据完成标记
    LPUartTC    = 1u,  ///<发送数据完成标记
    LPUartFE    = 2u,  ///<帧错误标记
    LPUartTxe   = 3u,  ///<TXbuff空标记    
    LPUartPE    = 4u,  ///<奇偶校验错误标记
    LPUartCtsIf = 5u,  ///<CTS中断标记
    LPUartCts   = 6u,  ///<CTS信号标记
}en_lpuart_status_t;

/**
 ******************************************************************************
 ** \brief lpuart 通道采样分频配置
 ******************************************************************************/
typedef enum en_lpuart_clkdiv
{
    LPUartMsk16Or32Div = 0u,        ///<模式0无效，模式1/3为16分频，模式2为32分频
    LPUartMsk8Or16Div  = 0x200u,    ///<模式0无效，模式1/3为8分频，模式2为16分频
    LPUartMsk4Or8Div   = 0x400u,    ///<模式0无效，模式1/3为4分频，模式2为8分频
}en_lpuart_clkdiv_t;

/**
 ******************************************************************************
 ** \brief lpuart 通道Mode1和Mode3波特率计算参数
 ******************************************************************************/
typedef struct stc_lpuart_baud
{
    en_lpuart_sclksel_t  enSclkSel;      ///<传输时钟源选择
    en_lpuart_clkdiv_t   enSclkDiv;     ///<采样分频选择 
    uint32_t             u32Sclk;        ///<sclk
    uint32_t             u32Baud;        ///< 波特率
} stc_lpuart_baud_t;
/**
 ******************************************************************************
 ** \lpuart 总体配置
 ******************************************************************************/
typedef struct stc_lpuart_cfg
{
    en_lpuart_mode_t       enRunMode;      ///<四种模式配置
    en_lpuart_mmdorck_t    enMmdorCk;      ///<校验模式
    en_lpuart_stop_t       enStopBit;      ///<停止位长度    
    stc_lpuart_baud_t      stcBaud;        ///<Mode1/3波特率配置                                                        
} stc_lpuart_cfg_t;

// 总初始化处理
en_result_t LPUart_Init(M0P_LPUART_TypeDef* LPUARTx, stc_lpuart_cfg_t* pstcCfg);

// LPUART 单线模式使能/禁止
void LPUart_HdModeEnable(M0P_LPUART_TypeDef* LPUARTx);
void LPUart_HdModeDisable(M0P_LPUART_TypeDef* LPUARTx);


//TB8数据设置
void LPUart_SetTb8(M0P_LPUART_TypeDef* LPUARTx, boolean_t bTB8Value);

//数据寄存器bit8位获取
boolean_t LPUart_GetRb8(M0P_LPUART_TypeDef* LPUARTx);

//中断相关设置函数使能和禁止
en_result_t LPUart_EnableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel);
en_result_t LPUart_DisableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel);

//特殊功能使能和禁止
en_result_t LPUart_EnableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc);
en_result_t LPUart_DisableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc);

//状态位获取函数
boolean_t LPUart_GetStatus(M0P_LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus);
//状态位的清除
en_result_t LPUart_ClrStatus(M0P_LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus);
//整个状态寄存器获取
uint8_t LPUart_GetIsr(M0P_LPUART_TypeDef* LPUARTx);
//整个状态寄存器清除
en_result_t LPUart_ClrIsr(M0P_LPUART_TypeDef* LPUARTx);

//数据查询方式的发送
en_result_t LPUart_SendData(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data);
//数据中断方式的发送
en_result_t LPUart_SendDataIt(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data);
//数据接收
uint8_t LPUart_ReceiveData(M0P_LPUART_TypeDef* LPUARTx);

//LPUARTx通道号，enClk 时钟源选项
en_result_t LPUart_SelSclk(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_sclksel_t enSclk);

//LPUART通道多主机模式配置
en_result_t LPUart_SetMultiMode(M0P_LPUART_TypeDef* LPUARTx, stc_lpuart_multimode_t* pstcMultiCfg);

//LPUART通道多主机模式从机地址配置函数
en_result_t LPUart_SetSaddr(M0P_LPUART_TypeDef* LPUARTx,uint8_t u8Addr);

//@} // LPUartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



