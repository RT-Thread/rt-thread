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
#include "interrupts_hc32l136.h"

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

typedef enum en_lpuart_channel
{
    LPUART0 = 0u, ///<串口2
    LPUART1 = 1u, ///<串口3
}en_lpuart_channel_t;
/**
 ******************************************************************************
 ** \brief lpuart 的sclk时钟源选择
 ******************************************************************************/

typedef enum en_lpuart_sclk_sel
{
    LPUart_Pclk   = 0u, ///<pclk
    LPUart_Pclk_1 = 1u, ///<pclk
    LPUart_Xtl    = 2u, ///<外部低速晶振
    LPUart_Rcl    = 3u, ///<内部低速晶振
} en_lpuart_sclksel_t;

/**
 ******************************************************************************
 ** \brief lpuart多主机模式地址帧/数据帧或者奇偶校验
 ******************************************************************************/
typedef enum en_lpuart_mmdorck
{
    LPUartDataOrAddr = 0u, ///<多主机模式时，通过读写SBUF[8]决定帧为数据帧或地址帧
    LPUartEven       = 1u, ///<非多主机模式偶校验   
    LPUartOdd        = 2u, ///<非多主机模式奇校验    
}en_lpuart_mmdorck_t;

/**
 ******************************************************************************
 ** \brief lpuart多主机模式配置
 ******************************************************************************/
typedef enum en_lpuart_multimode
{
    LPUartNormal = 0u, ///<正常工作模式
    LPUartMulti  = 1u, ///<多主机工作模式
}en_lpuart_multimode_t;
/**
 ******************************************************************************
 ** \brief lpuart多主机模式及从机地址和地址掩码配置
 ******************************************************************************/

typedef struct stc_lpuart_multimode
{
    en_lpuart_multimode_t enMulti_mode; ///<多主机模式配置
    uint8_t             u8SlaveAddr;  ///<从机地址
    uint8_t                u8SaddEn;  ///<从及地址掩码
}stc_lpuart_multimode_t;

/**
 ******************************************************************************
 ** \brief lpuart 四种工作模式选择
 ******************************************************************************/

typedef enum en_lpuart_mode
{
    LPUartMode0 = 0u, ///<模式0    
    LPUartMode1 = 1u, ///<模式1
    LPUartMode2 = 2u, ///<模式2
    LPUartMode3 = 3u, ///<模式3
} en_lpuart_mode_t;
/**
 ******************************************************************************
 ** \brief lpuart stop长度选择
 ******************************************************************************/

typedef enum en_lpuart_stop
{
    LPUart1bit  = 0u, ///<1位停止位 
    LPUart15bit = 1u, ///<1.5位停止位
    LPUart2bit  = 2u, ///<2位停止位
} en_lpuart_stop_t;
/**
 ******************************************************************************
 ** \brief lpuart 功能使能
 ******************************************************************************/
typedef enum en_lpuart_func
{
    LPUartTx     = 0u, ///<mode0模式代表TX    
    LPUartRx     = 1u, ///<非mode0模式代表RX and TX ,mode0模式代表RX  
    LPUartDmaTx  = 3u, ///<DMA发送使能
    LPUartDmaRx  = 4u, ///<DMA接收使能
    LPUartCtsRts = 5u, ///<硬件流使能
}en_lpuart_func_t;
/**
 ******************************************************************************
 ** \brief lpuart中断使能控制
 ******************************************************************************/
typedef enum en_lpuart_irq_sel
{
    LPUartTxIrq  = 0u,  ///<发送中断使能        
    LPUartRxIrq  = 1u,  ///<接收中断使能
    LPUartFEIrq  = 3u,  ///<帧错误中断使能
    LPUartCtsIrq = 4u,  ///<CTS信号翻转中断使能
    LPUartPEIrq  = 5u,  ///<奇偶校验中断使能
    LPUartTxEIrq = 6u,  ///<TX空中断使能   
}en_lpuart_irq_sel_t;
/**
 ******************************************************************************
 ** \brief lpuart发送接收中断处理函数接口
 ******************************************************************************/

typedef struct stc_lpuart_irq_cb
{
    func_ptr_t pfnTxIrqCb;    ///<发送中断服务函数     
    func_ptr_t pfnRxFEIrqCb;  ///<接收帧错误中断服务函数
    func_ptr_t pfnRxIrqCb;    ///<接收中断服务函数 
    func_ptr_t pfnCtsIrqCb;   ///<CTS信号翻转中断服务函数 
    func_ptr_t pfnPEIrqCb;    ///<奇偶校验错误中断服务函数 
}stc_lpuart_irq_cb_t;
/**
 ******************************************************************************
 ** \brief lpuart 状态标志位
 ******************************************************************************/
typedef enum en_lpuart_status
{
    LPUartCts   = 0u,  ///<CTS信号标记
    LPUartRC    = 1u,  ///<接收数据完成标记
    LPUartTC    = 2u,  ///<发送数据完成标记
    LPUartPE    = 3u,  ///<奇偶校验错误标记
    LPUartFE    = 4u,  ///<帧错误标记  
    LPUartCtsIf = 5u,  ///CTS中断标志
    LPUartTxe   = 6u,  ///TXbuff空标记
}en_lpuart_status_t;
/**
 ******************************************************************************
 ** \brief lpuart 通道地址及中断函数地址结构
 ******************************************************************************/
typedef struct stc_lpuart_instance_data
{   
    uint32_t               u32Idx;               ///< 通道号
    M0P_LPUART_TypeDef     *pstcInstance;        ///< 通道寄存器地址
    stc_lpuart_irq_cb_t    stcLPUartInternIrqCb;   ///< 通道中断服务函数
} stc_lpuart_instance_data_t;
/**
 ******************************************************************************
 ** \brief lpuart 通道波特率配置
 ******************************************************************************/
typedef enum en_lpuart_clkdiv
{
    LPUart16Or32Div = 0u,///<模式0无效，模式1/3为16分频，模式2为32分频
    LPUart8Or16Div  = 1u,///<模式0无效，模式1/3为8分频，模式2为16分频
    LPUart4Or8Div   = 2u,///<模式0无效，模式1/3为4分频，模式2为8分频
}en_lpuart_clkdiv_t;
/**
 ******************************************************************************
 ** \brief lpuart 时钟相关配置
 ******************************************************************************/
typedef struct stc_lpuart_sclk_sel
{
    en_lpuart_clkdiv_t  enSclk_Prs; ///<分频选择
    en_lpuart_sclksel_t enSclk_sel; ///<传输时钟选择
}stc_lpuart_sclk_sel_t;
/**
 ******************************************************************************
 ** \brief lpuart 通道波特率计算参数
 ******************************************************************************/
typedef struct stc_lpuart_baud
{
    uint32_t             u32Sclk;        ///<sclk
    en_lpuart_mode_t     enRunMode;      ///< 四种模式配置
    uint32_t             u32Baud;        ///< 波特率
} stc_lpuart_baud_t;
/**
 ******************************************************************************
 ** \lpuart 总体配置
 ******************************************************************************/

typedef struct stc_lpuart_config
{
    en_lpuart_mode_t       enRunMode;      ///< 四种模式配置
    stc_lpuart_sclk_sel_t* pstcLpuart_clk; ///<时钟源配置
    en_lpuart_stop_t       enStopBit;      ///<停止位长度
    stc_lpuart_multimode_t* pstcMultiMode; ///<多主机模式配置
    stc_lpuart_irq_cb_t*  pstcIrqCb;       ///<中断服务函数          
    boolean_t           bTouchNvic;      ///<NVIC中断使能    
} stc_lpuart_config_t;
//中断相关设置函数
en_result_t LPUart_EnableIrq(uint8_t u8Idx,
                           en_lpuart_irq_sel_t enIrqSel);
en_result_t LPUart_DisableIrq(uint8_t u8Idx,
                            en_lpuart_irq_sel_t enIrqSel);
// 总初始化处理
en_result_t LPUart_Init(uint8_t u8Idx, 
                      stc_lpuart_config_t* pstcConfig);
//LPUART模块工作模式设置函数
en_result_t LPUart_SetMode(uint8_t u8Idx,en_lpuart_mode_t enMode);
//LPUART模块工作模式设置函数
en_result_t LPUart_SetMultiMode(uint8_t u8Idx,stc_lpuart_multimode_t* pstcMultiConfig);
//LPUART通道多主机模式发送数据/地址帧或者奇偶校验配置TB8
en_result_t LPUart_SetMMDOrCk(uint8_t u8Idx,en_lpuart_mmdorck_t enTb8);
//从机地址配置
en_result_t LPUart_SetSaddr(uint8_t u8Idx,uint8_t u8Addr);
//从机地址掩码配置
en_result_t LPUart_SetSaddrEn(uint8_t u8Idx,uint8_t u8Addren);
//停止位配置
en_result_t LPUart_SetStopBit(uint8_t u8Idx,uint8_t u8Len);
//数据寄存器bit8位获取
boolean_t LPUart_GetRb8(uint8_t u8Idx);
//时钟源选择
en_result_t LPUart_SelSclk(uint8_t u8Idx,en_lpuart_sclksel_t enClk);
//时钟源时钟获取
uint32_t LPUart_GetSclk(uint8_t u8Idx);
//采样分频设置
en_result_t LPUart_SetClkDiv(uint8_t u8Idx,en_lpuart_clkdiv_t enClkDiv);
//波特率设置值计算
uint16_t LPUart_CalScnt(uint8_t u8Idx,stc_lpuart_baud_t *pstcBaud);
//波特率设置
en_result_t LPUart_SetBaud(uint8_t u8Idx,uint16_t u16Scnt);
//获取波特率
uint32_t LPUart_GetBaud(uint8_t u8Idx,uint8_t u8Mode,uint32_t u32Pclk);
                             
//功能使能和禁止
en_result_t LPUart_EnableFunc(uint8_t u8Idx, en_lpuart_func_t enFunc);
en_result_t LPUart_DisableFunc(uint8_t u8Idx, en_lpuart_func_t enFunc);
//某个状态bit获取函数
boolean_t LPUart_GetStatus(uint8_t u8Idx,en_lpuart_status_t enStatus);
//某个状态bit状态位的清除
en_result_t LPUart_ClrStatus(uint8_t u8Idx,en_lpuart_status_t enStatus);
//整个状态寄存器获取
uint8_t LPUart_GetIsr(uint8_t u8Idx);
//整个状态寄存器清除
en_result_t LPUart_ClrIsr(uint8_t u8Idx);
//数据查询方式的发送操作
en_result_t LPUart_SendData(uint8_t u8Idx, uint8_t u8Data);
//数据查询方式的接收操作
uint8_t LPUart_ReceiveData(uint8_t u8Idx);

//@} // LPUartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



