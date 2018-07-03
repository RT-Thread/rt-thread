/*****************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
/******************************************************************************/
/** \file usart.h
 **
 ** A detailed description is available at
 ** @link UsartGroup Usart description @endlink
 **
 **   - 2018-05-03  1.0  Wangmin First version for Device Driver Library of UART.
 **
 ******************************************************************************/

#ifndef __USART_H__
#define __USART_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "base_types.h"
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup UsartGroup Universal Synchronous/Asynchronous Receiver/Transmitter(USART)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/


/**
 *******************************************************************************
 ** \brief  The USART mode type define.
 **
 ******************************************************************************/
typedef enum en_usart_mode
{
    UartNormal = 0,             ///< Chose UART normal mode.
    UartMultiDeviceMode = 1,    ///< Chose UART multi-device mode.
    UartSyncMode = 2,           ///< Chose UART synchronous mode.
    SmartCardMode = 3,          ///< not support
}en_usart_mode_t;

/**
 *******************************************************************************
 ** \brief  The usart data format sequence type define.
 **
 ******************************************************************************/
typedef enum en_usart_data_sequence
{
    DataLSB = 0,       ///< Data send LSB.(for all mode)
    DataMSB = 1,       ///< Data send MSB.(for all mode)
}en_usart_data_sequence_t;

/**
 *******************************************************************************
 ** \brief  The uart data format length type define.
 **
 ******************************************************************************/
typedef enum en_usart_data_len
{
    Len9bit = 0,        ///< data length 9 bit.(for uart mode)
    Len8bit = 2,        ///< data length 8 bit.(for uart mode)
}en_usart_data_len_t;

/**
 *******************************************************************************
 ** \brief  The uart data format parity type define.
 **
 ******************************************************************************/
typedef enum en_usart_parity
{
    ParityDisEn = 0,  ///< Parity bit disenable.(for uart mode)
    ParityEven = 2,   ///< Even parity check.(for uart mode)
    ParityOdd = 3,    ///< Odd parity check.(for uart mode)
}en_usart_parity_t;

/**
 *******************************************************************************
 ** \brief  The uart data format stop bit length type define.
 **
 ******************************************************************************/
typedef enum en_usart_stop_bit
{
    Stop1Bit = 0,    ///< stop bit 1 bit.(for uart mode)
    Stop2Bit = 1,    ///< stop bit 2 bit.(for uart mode)
}en_usart_stop_bit_t;


/**
 *******************************************************************************
 ** \brief  The usart hardware flow control config type define.
 **
 ******************************************************************************/
typedef enum en_usart_hardware_ctl
{
//    HardwareCtlDisEn = 0,
    HardwareCtlRTS = 0,   ///< RTS flow control enable
    HardwareCtlCTS = 1,   ///< CTS flow control enable
}en_usart_hardware_ctl_t;


/**
 *******************************************************************************
 ** \brief  The usart internal clock source division typedef.
 **
 ******************************************************************************/
typedef enum en_usart_inter_clk_src
{
    SrcPclk = 0,        ///< Clock source chose PCLK.
    SrcPclkDiv4 = 1,    ///< Clock source chose PCLK/4.
    SrcPclkDiv16 = 2,   ///< Clock source chose PCLK/16.
    SrcPclkDiv64 = 3,   ///< Clock source chose PCLK/64.
    SrcMax,
}en_usart_inter_clk_src_t;


/**
 *******************************************************************************
 ** \brief  The usart clock source config typedef.
 **
 ******************************************************************************/
typedef enum en_usart_clk_config
{
    ClkInter = 0,       ///< Clock internal source, SCK not output.
    ClkInterSckOut = 1, ///< Clock internal source, SCK output.
    ClkExt = 2,         ///< Clock external source, SCK input.
}en_usart_clk_config_t;


/**
 *******************************************************************************
 ** \brief  The usart config structure type define.
 **
 ******************************************************************************/
typedef struct stc_uart_config
{
    uint32_t u32Baudrate;                       ///< baud rate

    en_usart_data_sequence_t enDataSequence;    ///< data Sequence(for uart all mode and smart card mode).
    en_usart_data_len_t      enDataLength;      ///< data length.(if bSyncMode on, not need config)
    en_usart_parity_t        enParity;          ///< data parity.(if bSyncMode on, not need config)
    en_usart_stop_bit_t      enStopBit;         ///< stop bit length.(if bSyncMode on, not need config)
    en_usart_hardware_ctl_t  enHwFlowCtl;        ///< hard ware flow control config.(for uart all mode)

    en_usart_clk_config_t enClkCfg;             ///< clock source config and clock output config
}stc_uart_config_t;

/**
 *******************************************************************************
 ** \brief  The usart function typedef.
 **
 ******************************************************************************/
typedef enum en_usart_function
{
    FuncRxIrqEn = 0,       ///< USART date receive interrupt enable function
    FuncTxIrqEn = 1,       ///< USART date transfer interrupt enable function
    FuncTxEn = 2,          ///< USART date transfer enable function
    FuncRxEn = 3,          ///< USART date receive enable function
    FuncSilenceEn = 4,     ///< USART silence mode enable function in synchronous mode
    FuncTxCompleteIrqEn = 5, ///< USART transfer complete interrupt function enable
    FuncTxIrqAndTxEn =6,   ///< USART transfer interrupt and transfer function enable
}en_usart_function_t;

/**
 *******************************************************************************
 ** \brief  The usart status flag typedef.
 **
 ******************************************************************************/
typedef enum en_usart_status_flag
{
    FlagRxMpb = 0,      ///< Flag for mutil-device mode, 0: receive date; 1: received ID
    FlagTxComplete = 1, ///< Transfer data compelete flag
    FlagParityErr = 2,  ///< Receive data parity error flag
    FlagFrameErr = 3,   ///< Receive data frame error flag
    FlagOverrunErr = 4, ///< Receive data overrun error flag
    FlagRxFull = 5,     ///< Receive data full.
}en_usart_status_t;


/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
void UART_Init(M4_USART_TypeDef* pstcUsartReg, stc_uart_config_t* pstcUartCfg);
void UART_DeInit(M4_USART_TypeDef* pstcUsartReg);
void UART_FuncCfg(M4_USART_TypeDef* pstcUsartReg, en_usart_function_t enFunction, en_functional_state_t enOp);
boolean_t UART_GetStatus(M4_USART_TypeDef* pstcUsartReg, en_usart_status_t enStatus);
void UART_ClrStatus(M4_USART_TypeDef* pstcUsartReg, en_usart_status_t enStatus);
void UART_BaudrateCfg(M4_USART_TypeDef* pstcUsartReg, uint32_t u32Baudrate);
void UART_SendData(M4_USART_TypeDef* pstcUsartReg, uint16_t u16Data);
void UART_SendId(M4_USART_TypeDef* pstcUsartReg, uint16_t u16Data);
uint16_t UART_RevData(M4_USART_TypeDef* pstcUsartReg);
void UART_CfgHwFlowCtl(M4_USART_TypeDef* pstcUsartReg, en_usart_hardware_ctl_t enFlowCtl);


//@} // UsartGroup

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
