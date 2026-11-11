/*************************************************************************************
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
/******************************************************************************/
/** \file lpuart.c
 **
 ** LPUART function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "hc32l196_lpuart.h"
/**
 ******************************************************************************
 ** \addtogroup LPUartGroup
 ******************************************************************************/
//@{
/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief  LPUART通信中断使能函数设置
 **
 ** \param [in] LPUARTx通道号，enIrqSel发送or接收中断使能
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t LPUart_EnableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{

    SetBit((uint32_t)(&(LPUARTx->SCON)), enIrqSel, TRUE);

    return Ok;
}
/**
 ******************************************************************************
 ** \brief  LPUART通信中断禁止函数设置
 **
 ** \param [in] LPUARTx通道号，enIrqSel发送or接收中断禁止
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t LPUart_DisableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{

    SetBit((uint32_t)(&(LPUARTx->SCON)), enIrqSel, FALSE);

    return Ok;
}
/**
 ******************************************************************************
 ** \brief lpuart通信时钟源选择
 **
 ** \param [in] LPUARTx通道号，enClk 时钟源选项
 **
 ** \retval Ok 设置成功
 **\retval ErrorInvalidParameter设置失败
 ******************************************************************************/
en_result_t LPUart_SelSclk(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_sclksel_t enSclk)
{
    ASSERT(IS_VALID_CLK(enSclk));

    LPUARTx->SCON_f.SCLKSEL = enSclk;

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道多主机模式配置
 **
 ** \param [in] LPUARTx通道号，stcMultiCfg多主机模式结构
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t LPUart_SetMultiMode(M0P_LPUART_TypeDef* LPUARTx, stc_lpuart_multimode_t* pstcMultiCfg)
{

    if(NULL != pstcMultiCfg)
    {
        LPUARTx->SCON_f.ADRDET = TRUE;
        LPUARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        LPUARTx->SADEN = pstcMultiCfg->u8SaddEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART单线半双工模式使能
 **
 ** \param [in] LPUARTx 通道号
 **
 ** \retval Null
 ******************************************************************************/
void LPUart_HdModeEnable(M0P_LPUART_TypeDef* LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = TRUE;
}


/**
 ******************************************************************************
 ** \brief  LPUART单线半双工模式关闭
 **
 ** \param [in] LPUARTx 通道号
 **
 ** \retval Null
 ******************************************************************************/
void LPUart_HdModeDisable(M0P_LPUART_TypeDef* LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = FALSE;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道多机模式发送数据/地址帧配置TB8
 **
 ** \param [in] LPUARTx 通道号
 ** \param [in] TRUE-TB8为地址帧标志；FALSE-TB8为数据帧标志；
 **
 ** \retval Null
 ******************************************************************************/
void LPUart_SetTb8(M0P_LPUART_TypeDef* LPUARTx, boolean_t bTB8Value)
{
    LPUARTx->SCON_f.B8CONT = bTB8Value;

}

/**
 ******************************************************************************
 ** \brief 获取RB8数值
 **
 ** \param [in] LPUARTx 通道号
 **
 ** \retval RB8
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
boolean_t LPUart_GetRb8(M0P_LPUART_TypeDef* LPUARTx)
{
    return (LPUARTx->SBUF_f.DATA8);
}
/**
 ******************************************************************************
 ** \brief  LPUART通道多主机模式从机地址配置函数
 **
 ** \param [in] LPUARTx 通道号，addr地址
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t LPUart_SetSaddr(M0P_LPUART_TypeDef* LPUARTx,uint8_t u8Addr)
{
    LPUARTx->SADDR = u8Addr;

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道发送或接收等功能使能设置
 **
 ** \param [in] u8Idx通道号，enFunc功能
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t LPUart_EnableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), enFunc, TRUE);

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道发送或接收等功能禁止设置
 **
 ** \param [in] u8Idx通道号，enFunc功能
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t LPUart_DisableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), enFunc, FALSE);

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道通信状态获取
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 状态值
 ******************************************************************************/
uint8_t LPUart_GetIsr(M0P_LPUART_TypeDef* LPUARTx)
{
    return (LPUARTx->ISR);
}

/**
 ******************************************************************************
 ** \brief  LPUART通道通信状态获取
 **
 ** \param [in] u8Idx通道号，enStatus获取哪个状态
 **
 ** \retval 状态值
 **\retval ErrorInvalidParameter获取失败
 ******************************************************************************/
boolean_t LPUart_GetStatus(M0P_LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus)
{
    boolean_t bStatus = FALSE;

    ASSERT(IS_VALID_STATUS(enStatus));

    bStatus =  GetBit((uint32_t)(&(LPUARTx->ISR)), enStatus);

    return bStatus;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道通信状态全部清除
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval OK
 ******************************************************************************/
en_result_t LPUart_ClrIsr(M0P_LPUART_TypeDef* LPUARTx)
{
    LPUARTx->ICR = 0u;
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道通信状态清除
 **
 ** \param [in] u8Idx通道号，enStatus清除哪个状态
 **
 ** \retval 状态值
 **\retval ErrorInvalidParameter清除失败
 ******************************************************************************/
en_result_t LPUart_ClrStatus(M0P_LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));

    SetBit((uint32_t)(&(LPUARTx->ICR)), enStatus, FALSE);

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道发送数据函数,查询方式调用此函数，中断方式发送不适用
 **
 ** \param [in] u8Idx通道号，Data发送数据
 **
 ** \retval Ok发送成功
 **\retval ErrorInvalidParameter发送失败
 ******************************************************************************/
en_result_t LPUart_SendData(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data)
{
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe))
    {}
    LPUARTx->SBUF_f.DATA = u8Data;
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTC))
    {}
    LPUart_ClrStatus(LPUARTx,LPUartTC);
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道发送数据函数,中断方式调用此函数
 **
 ** \param [in] u8Idx通道号，Data发送数据
 **
 ** \retval Ok发送成功
 **\retval ErrorInvalidParameter发送失败
 ******************************************************************************/
en_result_t LPUart_SendDataIt(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data)
{
    LPUARTx->SBUF_f.DATA = u8Data;

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  LPUART通道接收数据函数
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 接收数据
 **\retval ErrorInvalidParameter接收失败
 ******************************************************************************/
uint8_t LPUart_ReceiveData(M0P_LPUART_TypeDef* LPUARTx)
{
    return (LPUARTx->SBUF_f.DATA);
}

/**
 ******************************************************************************
 ** \brief  LPUART通道初始化函数
 **
 ** \param [in] u8Idx通道号，pstcCfg初始化结构体  @ref stc_lpuart_cfg_t
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t LPUart_Init(M0P_LPUART_TypeDef* LPUARTx,stc_lpuart_cfg_t* pstcCfg)
{
    en_result_t enRet = Error;
    const uint32_t u32Over[3] = {0x4, 0x3, 0x2};
    uint16_t u16OverShift;
    float32_t f32Scnt=0;

    if(NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }

    LPUARTx->SCON = 0;

    LPUARTx->SCON = (uint32_t)pstcCfg->enStopBit          |
                    (uint32_t)pstcCfg->enMmdorCk          |
                    (uint32_t)pstcCfg->stcBaud.enSclkDiv  |
                    (uint32_t)pstcCfg->stcBaud.enSclkSel  |
                    (uint32_t)pstcCfg->enRunMode;

    if((LPUartMskMode1 == pstcCfg->enRunMode) || (LPUartMskMode3 == pstcCfg->enRunMode))
    {
        u16OverShift = u32Over[pstcCfg->stcBaud.enSclkDiv/LPUartMsk8Or16Div];
        f32Scnt = (float32_t)(pstcCfg->stcBaud.u32Sclk)/(float32_t)(pstcCfg->stcBaud.u32Baud<<u16OverShift);
        LPUARTx->SCNT = (uint16_t)(float32_t)(f32Scnt + 0.5f);
        LPUart_EnableFunc(LPUARTx,LPUartRenFunc);       ///<使能收发
    }



    enRet = Ok;
    return enRet;
}
//@} // LPUartGroup
