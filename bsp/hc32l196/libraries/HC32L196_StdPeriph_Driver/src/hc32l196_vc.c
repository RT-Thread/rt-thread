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
/** \file vc.c
 **
 ** voltage comparator driver API.
 ** @link VC Group Some description @endlink
 **
 **   - 2019-04-10   First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_vc.h"

/**
 ******************************************************************************
 ** \addtogroup VcGroup
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

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/**
******************************************************************************
    ** \brief  配置VC中断触发方式
    **
    ** @param  Channelx : VcChannelx  x=0、1、2
    ** @param  enSel : VcIrqRise、VcIrqFall、VcIrqHigh
    ** \retval 无
    **
******************************************************************************/
void Vc_CfgItType(en_vc_channel_t Channelx, en_vc_irq_sel_t ItType)
{
    stc_vc_vc0_cr_field_t *stcVcnCr;
        switch(Channelx)
        {
            case VcChannel0:
                stcVcnCr = (stc_vc_vc0_cr_field_t*)&M0P_VC->VC0_CR_f;
                break;
            case VcChannel1:
                stcVcnCr = (stc_vc_vc0_cr_field_t*)&M0P_VC->VC1_CR_f;
                break;
            case VcChannel2:
                stcVcnCr = (stc_vc_vc0_cr_field_t*)&M0P_VC->VC2_CR_f;
                break;
            default:
                break;
        }
    switch (ItType)
    {
        case VcIrqNone:
            stcVcnCr->RISING  = 0u;
            stcVcnCr->FALLING = 0u;
            stcVcnCr->LEVEL   = 0u;
            break;
        case VcIrqRise:
            stcVcnCr->RISING  = 1u;
            break;
        case VcIrqFall:
            stcVcnCr->FALLING = 1u;
            break;
        case VcIrqHigh:
            stcVcnCr->LEVEL   = 1u;
            break;
        default:
            break;
    }
}

/**
******************************************************************************
    ** \brief  VC 中断使能与禁止
    **
    ** @param  Channelx : VcChannelx  x=0、1、2
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void  Vc_ItCfg(en_vc_channel_t Channelx, boolean_t NewStatus)
{
    switch(Channelx)
    {
        case VcChannel0:
            SetBit((uint32_t)(&(M0P_VC->VC0_CR)), 15, NewStatus);
        break;
        case VcChannel1:
            SetBit((uint32_t)(&(M0P_VC->VC1_CR)), 15, NewStatus);
        break;
        case VcChannel2:
            SetBit((uint32_t)(&(M0P_VC->VC2_CR)), 15, NewStatus);
        break;
        default:
            break;
    }
}

/**
******************************************************************************
    ** \brief  VC 比较结果获取，包含中断标志位和滤波结果
    **
    ** @param  Result : 所要读取的结果
    ** \retval TRUE 或  FALSE
    **
******************************************************************************/
boolean_t Vc_GetItStatus(en_vc_ifr_t Result)
{
    boolean_t bFlag;
    bFlag = GetBit((uint32_t)(&(M0P_VC->IFR)), Result);
    return bFlag;
}

/**
******************************************************************************
    ** \brief  VC 清除中断标志位
    **
    ** @param  NewStatus : Vc0_Intf、Vc1_Intf、Vc2_Intf
    ** \retval 无
    **
******************************************************************************/
void Vc_ClearItStatus(en_vc_ifr_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_VC->IFR)), NewStatus, 0);
}

/**
******************************************************************************
    ** \brief  VC 配置DAC相关的内容  VC_CR中 VC_REF2P5_SEL VC_DIV_EN VC_DIV
    **
    ** @param  pstcDacCfg : 
    ** \retval Ok 或 ErrorInvalidParameter
    **
******************************************************************************/
en_result_t Vc_DacInit(stc_vc_dac_cfg_t *pstcDacCfg)
{
    if (NULL == pstcDacCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_VC->CR_f.DIV_EN = pstcDacCfg->bDivEn;
    M0P_VC->CR_f.REF2P5_SEL = pstcDacCfg->enDivVref;

    if (pstcDacCfg->u8DivVal < 0x40)
    {
        M0P_VC->CR_f.DIV = pstcDacCfg->u8DivVal;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
******************************************************************************
    ** \brief  VC通道初始化
    **
    ** @param  pstcDacCfg : 
    ** \retval 无
    **
******************************************************************************/
void Vc_Init(stc_vc_channel_cfg_t *pstcChannelCfg)
{
    if (VcChannel0 == pstcChannelCfg->enVcChannel)
    {
        M0P_VC->CR_f.VC0_HYS_SEL = pstcChannelCfg->enVcCmpDly;
        M0P_VC->CR_f.VC0_BIAS_SEL = pstcChannelCfg->enVcBiasCurrent;
        M0P_VC->VC0_CR_f.DEBOUNCE_TIME = pstcChannelCfg->enVcFilterTime;
        M0P_VC->VC0_CR_f.P_SEL = pstcChannelCfg->enVcInPin_P;
        M0P_VC->VC0_CR_f.N_SEL = pstcChannelCfg->enVcInPin_N;
                M0P_VC->VC0_CR_f.FLTEN = pstcChannelCfg->bFlten;
        M0P_VC->VC0_OUT_CFG = 1<<pstcChannelCfg->enVcOutCfg;
    }
    else if (VcChannel1 == pstcChannelCfg->enVcChannel)
    {
        M0P_VC->CR_f.VC1_HYS_SEL = pstcChannelCfg->enVcCmpDly;
        M0P_VC->CR_f.VC1_BIAS_SEL = pstcChannelCfg->enVcBiasCurrent;
        M0P_VC->VC1_CR_f.DEBOUNCE_TIME = pstcChannelCfg->enVcFilterTime;
        M0P_VC->VC1_CR_f.P_SEL = pstcChannelCfg->enVcInPin_P;
        M0P_VC->VC1_CR_f.N_SEL = pstcChannelCfg->enVcInPin_N;
                M0P_VC->VC1_CR_f.FLTEN = pstcChannelCfg->bFlten;
        M0P_VC->VC1_OUT_CFG = 1<<pstcChannelCfg->enVcOutCfg;
    }
    else if(VcChannel2 ==  pstcChannelCfg->enVcChannel)
    {
    M0P_VC->CR_f.VC2_HYS_SEL = pstcChannelCfg->enVcCmpDly;
    M0P_VC->CR_f.VC2_BIAS_SEL = pstcChannelCfg->enVcBiasCurrent;
    M0P_VC->VC2_CR_f.DEBOUNCE_TIME = pstcChannelCfg->enVcFilterTime;
    M0P_VC->VC2_CR_f.P_SEL = pstcChannelCfg->enVcInPin_P;
    M0P_VC->VC2_CR_f.N_SEL = pstcChannelCfg->enVcInPin_N;
            M0P_VC->VC2_CR_f.FLTEN = pstcChannelCfg->bFlten;
    M0P_VC->VC2_OUT_CFG = 1<<pstcChannelCfg->enVcOutCfg;            
    }
    else
    {
        ;
    }
}

/**
******************************************************************************
    ** \brief  VC 通道使能
    **
    ** \param  enChannel :  通道号VcChannel0 VcChannel1 VcChannel2
    ** \param  NewStatus : TRUE FALSE    
    ** \retval NewStatus : TRUE FALSE
    **
******************************************************************************/
void Vc_Cmd(en_vc_channel_t enChannel, boolean_t NewStatus)
{
    switch(enChannel)
    {
        case VcChannel0:
            SetBit((uint32_t)(&(M0P_VC->VC0_CR)), 16, NewStatus);
            break;
        case VcChannel1:
            SetBit((uint32_t)(&(M0P_VC->VC1_CR)), 16, NewStatus);
            break;
        case VcChannel2:
            SetBit((uint32_t)(&(M0P_VC->VC2_CR)), 16, NewStatus);
            break;
        default:
            break;
    }
}

//@} // VcGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

