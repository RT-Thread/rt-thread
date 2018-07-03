/******************************************************************************
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
/** \file usart.c
 **
 ** A detailed description is available at
 ** @link UsartGroup Usart description @endlink
 **
 **   - 2018-05-03  1.0  Wangmin First version for Device Driver Library of UART.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usart.h"
#include "clk.h"

/**
 *******************************************************************************
 ** \addtogroup UsartGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define  IS_USART_VALID_PERIPH(x) (((x) == M4_USART0) || \
                                  ((x) == M4_USART1) || \
                                  ((x) == M4_USART2) || \
                                  ((x) == M4_USART3) || \
                                  ((x) == M4_USART4) || \
                                  ((x) == M4_USART5) || \
                                  ((x) == M4_USART6))

#define  IS_USART_VALID_LENGTH(x) (((x) == Len9bit) || \
                                   ((x) == Len8bit))

#define  IS_USART_VALID_STOPBITS(x) (((x) == Stop1Bit) || \
                               ((x) == Stop2Bit))

#define  IS_USART_VALID_PARITY(x) (((x) == ParityDisEn) || \
                             ((x) == ParityEven) || \
                             ((x) == ParityOdd))

#define  IS_USART_VALID_BAUDRATE(x)     (((x) > 0) && ((x) <= 6000000))

#define  IS_USART_VALID_HARDWARE_FLOW_CONTROL(x)\
                              (((x) == HardwareCtlRTS) || \
                               ((x) == HardwareCtlCTS))

#define  IS_USART_VALID_CLK_CFG(x) (((x) == ClkInter) || \
                              ((x) == ClkInterSckOut) || \
                              ((x) == ClkExt))

#define  IS_USART_VALID_FUNC(x)(((x) == FuncRxIrqEn) || \
                              ((x) == FuncTxIrqEn) || \
                              ((x) == FuncTxEn) || \
                              ((x) == FuncRxEn) || \
                              ((x) == FuncSilenceEn) || \
                              ((x) == FuncTxCompleteIrqEn) || \
                              ((x) == FuncTxIrqAndTxEn))

#define  IS_USART_VALID_READ_FLAG(x)(((x) == FlagRxMpb) || \
                                     ((x) == FlagTxComplete) || \
                                     ((x) == FlagParityErr) || \
                                     ((x) == FlagFrameErr) || \
                                     ((x) == FlagOverrunErr))

#define  IS_USART_VALID_CLR_FLAG(x)( ((x) == FlagParityErr) || \
                                     ((x) == FlagFrameErr) || \
                                     ((x) == FlagOverrunErr))

#define  IS_USART_VALID_DATA(x) ((x) <= 0x1FF)

#define USART_CR_DEFAULT                 ((uint32_t)0x00000000)
#define USART_MR_DEFAULT                 ((uint32_t)0x80000200)
#define USART_BRR_DEFAULT                ((uint32_t)0xFF)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

static en_usart_inter_clk_src_t CalPrescaler(uint32_t u32Baudrate, uint8_t* pu8Div)
{
    stc_clk_freq_t u32ClkFreq;
    DDL_ASSERT(IS_USART_VALID_BAUDRATE(u32Baudrate));

    Clk_GetClockFreq(&u32ClkFreq);

    if((u32ClkFreq.pclk1Freq / u32Baudrate) <= (256 * 32))
    {
        *pu8Div = 1;
        return SrcPclk;
    }
    else if((u32ClkFreq.pclk1Freq / u32Baudrate) <= (256 * 32 * 4))
    {
        *pu8Div = 4;
        return SrcPclkDiv4;
    }
    else if((u32ClkFreq.pclk1Freq / u32Baudrate) <= (256 * 32 * 16))
    {
        *pu8Div = 16;
        return SrcPclkDiv16;
    }
    else
    {
        *pu8Div = 64;
        return SrcPclkDiv64;
    }
}

/**
 *******************************************************************************
 ** \brief  UART register initialize
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 ** \param  [in] pstcUartCfg    The UART configures struct.
 **
 ** \retval None
 **
 ******************************************************************************/
void UART_Init(M4_USART_TypeDef* pstcUsartReg, stc_uart_config_t* pstcUartCfg)
{
    stc_clk_freq_t u32ClkFreq;
    uint8_t u8Div = 0;

    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));
    DDL_ASSERT(IS_USART_VALID_BAUDRATE(pstcUartCfg->u32Baudrate));
    DDL_ASSERT(IS_USART_VALID_LENGTH(pstcUartCfg->enDataLength));
    DDL_ASSERT(IS_USART_VALID_STOPBITS(pstcUartCfg->enStopBit));
    DDL_ASSERT(IS_USART_VALID_PARITY(pstcUartCfg->enParity));
    DDL_ASSERT(IS_USART_VALID_HARDWARE_FLOW_CONTROL(pstcUartCfg->enHwFlowCtl));
    DDL_ASSERT(IS_USART_VALID_CLK_CFG(pstcUartCfg->enClkCfg));

    pstcUsartReg->CR = 0;        /* clear CR register */
    pstcUsartReg->CLR = 0x1C;    /* clear SR register */

    /*USART mode config*/
    pstcUsartReg->MR_f.SME = 0;  /* smart card mode disable */
    pstcUsartReg->MR_f.MS = 0;   /* sych mode disable */
    pstcUsartReg->MR_f.MP = 0;   /* Mutil device mode disable */

    /*USART data format config*/
    pstcUsartReg->MR_f.NFE = 1; /* receive noise filter enable */
    pstcUsartReg->MR_f.SBS = 1; /* falling edge as start bit */
    pstcUsartReg->MR_f.CL = pstcUartCfg->enDataLength;
    pstcUsartReg->MR_f.ML = pstcUartCfg->enDataSequence;
    pstcUsartReg->MR_f.STP = pstcUartCfg->enStopBit;
    if(ParityDisEn == pstcUartCfg->enParity)
    {
        pstcUsartReg->MR_f.PE = 0; /* parity check bit disable  */
    }
    else
    {
        pstcUsartReg->MR_f.PE = 1; /* parity check bit enable  */
        pstcUsartReg->MR_f.P = pstcUartCfg->enParity & 0x1;
    }

    /*USART hardware flow control config*/
    pstcUsartReg->MR_f.CTSE = pstcUartCfg->enHwFlowCtl;

    /*clock config and baudrate config*/
    pstcUsartReg->CR_f.CKC = pstcUartCfg->enClkCfg;
    if((ClkInter == pstcUartCfg->enClkCfg) || (ClkInterSckOut == pstcUartCfg->enClkCfg))
    {
        Clk_GetClockFreq(&u32ClkFreq);
        /* chose internal clock, set internal clock source*/
        pstcUsartReg->MR_f.CKS = CalPrescaler(pstcUartCfg->u32Baudrate, &u8Div);
        /* baudrate config*/
        pstcUsartReg->BRR = u32ClkFreq.pclk1Freq /(32 * pstcUartCfg->u32Baudrate * u8Div) - 1;
    }
}

/**
 *******************************************************************************
 ** \brief  Deinitializes the Uart peripheral register to default value.
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 **
 ** \retval None
 **
 ******************************************************************************/
void UART_DeInit(M4_USART_TypeDef* pstcUsartReg)
{
    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));

    pstcUsartReg->CR = USART_CR_DEFAULT;
    pstcUsartReg->MR = USART_MR_DEFAULT;
    pstcUsartReg->BRR = USART_BRR_DEFAULT;
}


/**
 *******************************************************************************
 ** \brief  UART function config
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 ** \param  [in] pstcUartCfg    The UART configures struct.
 ** \param  [in] enOp           Turn on or off the function.
 **
 ** \retval None
 **
 ******************************************************************************/
void UART_FuncCfg(M4_USART_TypeDef* pstcUsartReg, en_usart_function_t enFunction, en_functional_state_t enOp)
{
    stc_usart_cr_field_t stcReg;
    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));
    DDL_ASSERT(IS_USART_VALID_FUNC(enFunction));

    switch(enFunction)
    {
        case FuncRxIrqEn:
          pstcUsartReg->CR_f.RIE = enOp;
          break;
        case FuncTxIrqEn:
          pstcUsartReg->CR_f.TIE = enOp;
          break;
        case FuncTxEn:
          pstcUsartReg->CR_f.TE = enOp;
          break;
        case FuncRxEn:
          pstcUsartReg->CR_f.RE = enOp;
          break;
        case FuncSilenceEn:
          pstcUsartReg->CR_f.SLME = enOp;
          break;
        case FuncTxCompleteIrqEn:
          pstcUsartReg->CR_f.TCIE = enOp;
          break;
        case FuncTxIrqAndTxEn:
          /*Enanle Tx function write TE and TIE bit simultaneous*/
          stcReg = pstcUsartReg->CR_f;
          stcReg.TE = enOp;
          stcReg.TIE = enOp;
          pstcUsartReg->CR_f = stcReg;
          break;
        default:
          break;
    }
}

/**
 *******************************************************************************
 ** \brief  Get UART function status
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 ** \param  [in] enStatus       The UART status flag.
 **
 ** \retval TRUE  status is true
 ** \retval FALSE  status is false
 **
 ******************************************************************************/
boolean_t UART_GetStatus(M4_USART_TypeDef* pstcUsartReg, en_usart_status_t enStatus)
{
    boolean_t bFlag;
    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));
    DDL_ASSERT(IS_USART_VALID_READ_FLAG(enStatus));
    switch(enStatus)
    {
        case FlagRxMpb:
          bFlag = pstcUsartReg->SR_f.MPB;
          break;
        case FlagTxComplete:
          bFlag = pstcUsartReg->SR_f.TCF;
          break;
        case FlagParityErr:
          bFlag = pstcUsartReg->SR_f.PEF;
          break;
        case FlagFrameErr:
          bFlag = pstcUsartReg->SR_f.FEF;
          break;
        case FlagOverrunErr:
          bFlag = pstcUsartReg->SR_f.OREF;
          break;
        case FlagRxFull:
            bFlag = pstcUsartReg->SR_f.RXFF;
        default:
          break;
    }
    return bFlag;
}

/**
 *******************************************************************************
 ** \brief  Clear UART function status
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 ** \param  [in] enStatus       The UART status to clear.
 **
 ** \retval none
 **
 ******************************************************************************/
void UART_ClrStatus(M4_USART_TypeDef* pstcUsartReg, en_usart_status_t enStatus)
{
    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));
    DDL_ASSERT(IS_USART_VALID_CLR_FLAG(enStatus));
    switch(enStatus)
    {
        case FlagParityErr:
          pstcUsartReg->CLR_f.CPEF = 1;
          break;
        case FlagFrameErr:
          pstcUsartReg->CLR_f.CFEF = 1;
          break;
        case FlagOverrunErr:
          pstcUsartReg->CLR_f.COREF = 1;
          break;
    }
}

/**
 *******************************************************************************
 ** \brief  Config UART baudrate register
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 ** \param  [in] u32Baudrate    The baudrate.
 **
 ** \retval none
 **
 ******************************************************************************/
void UART_BaudrateCfg(M4_USART_TypeDef* pstcUsartReg, uint32_t u32Baudrate)
{
    stc_clk_freq_t u32ClkFreq;
    uint8_t u8Div;
    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));
    DDL_ASSERT(IS_USART_VALID_BAUDRATE(u32Baudrate));

    /* baudrate config*/
    Clk_GetClockFreq(&u32ClkFreq);

    /* chose internal clock, set internal clock source*/
    pstcUsartReg->MR_f.CKS = CalPrescaler(u32Baudrate, &u8Div);
    /* baudrate config*/
    pstcUsartReg->BRR = u32ClkFreq.pclk1Freq /(32 * u32Baudrate * u8Div) - 1;
}

/**
 *******************************************************************************
 ** \brief  Send data to UART shift out register
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 ** \param  [in] u16Data        Data to send.
 **
 ** \retval none
 **
 ******************************************************************************/
void UART_SendData(M4_USART_TypeDef* pstcUsartReg, uint16_t u16Data)
{
    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));
    DDL_ASSERT(IS_USART_VALID_DATA(u16Data));

    pstcUsartReg->TDR = (u16Data & (uint16_t)0x01FF);
}

/**
 *******************************************************************************
 ** \brief  Receive data from UART RDR register
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 **
 ** \retval u16Data           Data to read out.
 **
 ******************************************************************************/
uint16_t UART_RevData(M4_USART_TypeDef* pstcUsartReg)
{
    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));

    return (pstcUsartReg->RDR & (uint16_t)0x01FF);
}

/**
 *******************************************************************************
 ** \brief  Config usart hardware flow control register bit
 **
 ** \param  [in] pstcUsartReg   The UART peripheral register pointer.
 ** \param  [in] enFlowCtl      hardware flow control mode
 **
 ** \retval None
 **
 ******************************************************************************/
void UART_CfgHwFlowCtl(M4_USART_TypeDef* pstcUsartReg, en_usart_hardware_ctl_t enFlowCtl)
{
    DDL_ASSERT(IS_USART_VALID_PERIPH(pstcUsartReg));
    DDL_ASSERT(IS_USART_VALID_HARDWARE_FLOW_CONTROL(enFlowCtl));

    pstcUsartReg->MR_f.CTSE = enFlowCtl;

}


//@} // UsartGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

