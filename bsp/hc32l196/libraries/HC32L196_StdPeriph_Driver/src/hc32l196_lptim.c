/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file lptim.c
 **
 ** lptim driver API.
 ** @link pcnt Group Some description @endlink
 **
 **   - 2019-04-09       First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/

#include "hc32l196_lptim.h"

/**
 ******************************************************************************
 ** \addtogroup PCNTGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/


/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/**
******************************************************************************
    ** \brief  定时器LPTIMx中断使能控制
    ** @param  Lptimx    : LPTIM0 或LPTIM1
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Lptim_ConfIt(M0P_LPTIMER_TypeDef* Lptimx, boolean_t NewStatus)
{
    SetBit((uint32_t)(&(Lptimx->CR)), 10, NewStatus);
}

/**
******************************************************************************
    ** \brief  定时器LPTIMx的启动/停止控制
    ** @param  Lptimx    : LPTIM0 或LPTIM1
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Lptim_Cmd(M0P_LPTIMER_TypeDef* Lptimx, boolean_t NewStatus)
{
    SetBit((uint32_t)(&(Lptimx->CR)), 0, NewStatus);
}

/**
******************************************************************************
    ** \brief  定时器LPTIMx的中断标志位获取
    ** @param  Lptimx    : LPTIM0 或LPTIM1
    ** \retval TRUE 或 FALSE
    **
******************************************************************************/
boolean_t Lptim_GetItStatus(M0P_LPTIMER_TypeDef* Lptimx)
{
    return GetBit((uint32_t)(&(Lptimx->IFR)), 0);
}

/**
******************************************************************************
    ** \brief  定时器LPTIMx的中断标志位清除
    ** @param  Lptimx    : LPTIM0 或LPTIM1
    ** \retval 无
    **
******************************************************************************/
void Lptim_ClrItStatus(M0P_LPTIMER_TypeDef* Lptimx)
{
    SetBit((uint32_t)(&(Lptimx->ICLR)), 0, 0);
}

/**
******************************************************************************
    ** \brief  定时器LPTIMx的初始化配置
    ** @param  Lptimx    : LPTIM0 或LPTIM1
    ** @param  InitStruct : 初始化LPTIMx的结构体
    ** \retval en_result_t类型数据
    **
******************************************************************************/
en_result_t Lptim_Init(M0P_LPTIMER_TypeDef* Lptimx, stc_lptim_cfg_t* InitStruct)
{
    uint16_t u16TimeOut;
    u16TimeOut = 1000;
    Lptimx->CR_f.PRS      = InitStruct->enPrs;
    Lptimx->CR_f.TCK_SEL  = InitStruct->enTcksel;
    Lptimx->CR_f.GATE_P   = InitStruct->enGatep;
    Lptimx->CR_f.GATE     = InitStruct->enGate;
    Lptimx->CR_f.TOG_EN   = InitStruct->enTogen;
    Lptimx->CR_f.CT       = InitStruct->enCt;
    Lptimx->CR_f.MD       = InitStruct->enMd;
    while(u16TimeOut--)
    {
        if(Lptimx->CR_f.WT_FLAG)
        {
            break;
        }
    }
    if(u16TimeOut == 0)
    {
        return ErrorTimeout;        
    }
    Lptimx->ARR_f.ARR = InitStruct->u16Arr;
    return Ok;
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
