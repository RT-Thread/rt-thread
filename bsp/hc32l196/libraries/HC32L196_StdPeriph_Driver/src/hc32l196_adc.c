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
/******************************************************************************/
/** \file adc.c
 **
 ** ADC driver API.
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_adc.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
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
 * \brief
 *          获取ADC中断状态
 *
 * \param   [in]  enAdcIrq  ADC中断类型 @ref en_adc_irq_type_t
 *
 * \retval  中断标志
 */
boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq)
{
    if(M0P_ADC->IFR&enAdcIrq)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * \brief
 *          获取ADC中断状态
 *
 * \param   [in]  enAdcIrq  ADC中断类型 @ref en_adc_irq_type_t
 *
 * \retval  Null
 */
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq)
{
    M0P_ADC->ICR &= ~(uint32_t)enAdcIrq;
}

/**
 * \brief
 *          ADC中断使能
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_EnableIrq(void)
{
    M0P_ADC->CR0_f.IE = 1u;
}

/**
 * \brief
 *          ADC中断禁止
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_DisableIrq(void)
{
    M0P_ADC->CR0_f.IE = 0u;
}

/**
 * \brief
 *          ADC初始化
 *
 * \param   [in]  pstcAdcCfg  ADC配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcCfg)
{
    if (NULL == pstcAdcCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR0 = 0x1u;    ///< ADC 使能
    delay10us(2);

    M0P_ADC->CR0 |= (uint32_t)pstcAdcCfg->enAdcClkDiv       |
                    (uint32_t)pstcAdcCfg->enAdcRefVolSel    |
                    (uint32_t)pstcAdcCfg->enAdcOpBuf        |
                    (uint32_t)pstcAdcCfg->enAdcSampCycleSel |
                    (uint32_t)pstcAdcCfg->enInRef;

    M0P_ADC->CR1_f.MODE  = pstcAdcCfg->enAdcMode;
    M0P_ADC->CR1_f.ALIGN = pstcAdcCfg->enAdcAlign;

    return Ok;
}


/**
 * \brief
 *          ADC单次转换外部中断触发源配置
 *
 * \param   [in]  enAdcTrigSel  触发源
 *
 * \retval  en_result_t  Null
 */
void Adc_SglExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue)
{
    if(TRUE == bValue)
    {
        M0P_ADC->EXTTRIGGER0 |= (uint32_t)enAdcTrigSel;
    }
    else
    {
        M0P_ADC->EXTTRIGGER0 &= ~(uint32_t)enAdcTrigSel;
    }

}

/**
 * \brief
 *          ADC顺序扫描转换外部中断触发源配置
 *
 * \param   [in]  enAdcTrigSel  触发源
 * \param   [in]  TRUE or FALSE
 *
 * \retval  en_result_t  Null
 */
void Adc_SqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue)
{
    if(TRUE == bValue)
    {
        M0P_ADC->EXTTRIGGER0 |= (uint32_t)enAdcTrigSel;
    }
    else
    {
        M0P_ADC->EXTTRIGGER0 &= ~(uint32_t)enAdcTrigSel;
    }

}

/**
 * \brief
 *          ADC插队扫描转换外部中断触发源配置
 *
 * \param   [in]  enAdcTrigSel  触发源
 * \param   [in]  TRUE or FALSE
 *
 * \retval  en_result_t  Null
 */
void Adc_JqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue)
{
    if(TRUE == bValue)
    {
        M0P_ADC->EXTTRIGGER1 |= (uint32_t)enAdcTrigSel;
    }
    else
    {
        M0P_ADC->EXTTRIGGER1 &= ~(uint32_t)enAdcTrigSel;
    }

}


/**
 * \brief
 *          ADC 单次转换开始
 *
 * \param   无
 *
 * \retval  无
 */

void Adc_SGL_Start(void)
{
    M0P_ADC->SGLSTART = 1u;
}

/**
 * \brief
 *          ADC 单次转换停止
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_SGL_Stop(void)
{
    M0P_ADC->SGLSTART = 0u;
}

/**
 * \brief
 *          ADC 单次转换一直转换开始
 *
 * \param   无
 *
 * \retval  无
 */

void Adc_SGL_Always_Start(void)
{
    M0P_ADC->ALLSTART = 1u;
}

/**
 * \brief
 *          ADC 单次转换一直转换停止
 *
 * \param   无
 *
 * \retval  无
 */

void Adc_SGL_Always_Stop(void)
{
    M0P_ADC->ALLSTART = 0u;
}

/**
 * \brief
 *          ADC 顺序扫描转换开始
 *
 * \param   无
 *
 * \retval  无
 */

void Adc_SQR_Start(void)
{
    M0P_ADC->SQRSTART = 1u;
}

/**
 * \brief
 *          ADC 顺序扫描转换停止
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_SQR_Stop(void)
{
    M0P_ADC->SQRSTART = 0u;
}
/**
 * \brief
 *          ADC 插队扫描转换开始
 *
 * \param   无
 *
 * \retval  无
 */

void Adc_JQR_Start(void)
{
    M0P_ADC->JQRSTART = 1u;
}

/**
 * \brief
 *          ADC 插队扫描转换停止
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_JQR_Stop(void)
{
    M0P_ADC->JQRSTART = 0u;
}

/**
 * \brief
 *          ADC使能
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_Enable(void)
{
    M0P_ADC->CR0_f.EN = 1u;
}

/**
 * \brief
 *          ADC除能
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_Disable(void)
{
    M0P_ADC->CR0_f.EN = 0u;
}

/**
 * \brief
 *          配置顺序扫描转换模式
 *
 * \param   [in]  pstcAdcCfg   ADC配置指针
 * \param   [in]  pstcAdcNormCfg  连续转换模式配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t* pstcAdcSqrCfg)
{
    if ((NULL == pstcAdcSqrCfg) || (pstcAdcSqrCfg->u8SqrCnt > 16))
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.RACCCLR = 0; //ADC转换结果累加寄存器（ADC_ResultAcc）清零
    M0P_ADC->CR1_f.RACCEN  = pstcAdcSqrCfg->enResultAcc;
    M0P_ADC->CR1_f.DMASQR  = pstcAdcSqrCfg->bSqrDmaTrig;

    M0P_ADC->SQR2_f.CNT  = pstcAdcSqrCfg->u8SqrCnt - 1;

    return Ok;
}

/**
 * \brief
 *          配置插队扫描转换模式
 *
 * \param   [in]  pstcAdcCfg   ADC配置指针
 * \param   [in]  pstcAdcNormCfg  扫描转换模式配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t* pstcAdcJqrCfg)
{
    if ((NULL == pstcAdcJqrCfg) || (pstcAdcJqrCfg->u8JqrCnt > 4))
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.DMASQR  = pstcAdcJqrCfg->bJqrDmaTrig;

    M0P_ADC->JQR_f.CNT  = pstcAdcJqrCfg->u8JqrCnt - 1;

    return Ok;
}

/**
 * \brief
 *          配置单次转换通道
 *
 * \param   [in]enstcAdcSampCh 转换通道
 *
 * \retval  en_result_t  Ok:  成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_CfgSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    M0P_ADC->CR0_f.SGLMUX = enstcAdcSampCh;

    return Ok;
}

/**
 * \brief
 *          配置顺序扫描转换通道
 *
 * \param   [in]enstcAdcSqrChMux 顺序扫描转换通道顺序
 * \param   [in]enstcAdcSampCh   转换通道
 *
 * \retval  en_result_t  Ok:  成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    en_result_t enResult = Ok;
    
    switch(enstcAdcSqrChMux)
    {
        case AdcSQRCH0MUX:
            M0P_ADC->SQR0_f.CH0MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH1MUX:
            M0P_ADC->SQR0_f.CH1MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH2MUX:
            M0P_ADC->SQR0_f.CH2MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH3MUX:
            M0P_ADC->SQR0_f.CH3MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH4MUX:
            M0P_ADC->SQR0_f.CH4MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH5MUX:
            M0P_ADC->SQR0_f.CH5MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH6MUX:
            M0P_ADC->SQR1_f.CH6MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH7MUX:
            M0P_ADC->SQR1_f.CH7MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH8MUX:
            M0P_ADC->SQR1_f.CH8MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH9MUX:
            M0P_ADC->SQR1_f.CH9MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH10MUX:
            M0P_ADC->SQR1_f.CH10MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH11MUX:
            M0P_ADC->SQR1_f.CH11MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH12MUX:
            M0P_ADC->SQR2_f.CH12MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH13MUX:
            M0P_ADC->SQR2_f.CH13MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH14MUX:
            M0P_ADC->SQR2_f.CH14MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH15MUX:
            M0P_ADC->SQR2_f.CH15MUX = enstcAdcSampCh;
        break;
        default:
            enResult = ErrorInvalidParameter;
        break;

    }
    
    return enResult;
}
/**
 * \brief
 *          配置插队扫描转换通道
 *
 * \param   [in]enstcAdcSqrChMux 插队扫描转换通道顺序
 * \param   [in]enstcAdcSampCh   转换通道
 *
 * \retval  en_result_t  Ok:  成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    en_result_t enResult = Ok;
    
    switch(enstcAdcJqrChMux)
    {
        case AdcJQRCH0MUX:
            M0P_ADC->JQR_f.CH0MUX = enstcAdcSampCh;
        break;
        case AdcJQRCH1MUX:
            M0P_ADC->JQR_f.CH1MUX = enstcAdcSampCh;
        break;
        case AdcJQRCH2MUX:
            M0P_ADC->JQR_f.CH2MUX = enstcAdcSampCh;
        break;
        case AdcJQRCH3MUX:
            M0P_ADC->JQR_f.CH3MUX = enstcAdcSampCh;
        break;
        default:
            enResult = ErrorInvalidParameter;
        break;
    }
    
    return enResult;
}

/**
 * \brief
 *          获取采样值
 *
 *
 * \retval  en_result_t  采样值
 */
uint32_t Adc_GetSglResult(void)
{
    return M0P_ADC->RESULT;
}

/**
 * \brief
 *          获取采样值
 *
 * \param   [in] enstcAdcSqrChMux  顺序扫描通道序号 @ref en_adc_sqr_chmux_t
 *
 * \retval  en_result_t  采样值
 */
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux)
{
    volatile uint32_t *BaseSqrResultAddress = &(M0P_ADC->SQRRESULT0);

    return *(BaseSqrResultAddress + enstcAdcSqrChMux);

}

/**
 * \brief
 *          获取插队扫描采样值
 *
 * \param   [in] enstcAdcJqrChMux  插队扫描通道序号@ref en_adc_jqr_chmux_t
 *
 * \retval  en_result_t  采样值
 */
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux)
{
      volatile uint32_t *BaseJqrResultAddress = &(M0P_ADC->JQRRESULT0);

      return *(BaseJqrResultAddress + enstcAdcJqrChMux);

}

/**
 * \brief
 *          获取累加采样值
 *
 *
 * \retval  en_result_t  累加采样结果
 */
uint32_t Adc_GetAccResult(void)
{
    return M0P_ADC->RESULTACC;

}

/**
 * \brief
 *          清零累加采样值
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_ClrAccResult(void)
{
    M0P_ADC->CR1_f.RACCCLR = 0u;
}

/**
 * \brief
 *          ADC比较使能(比较中断)
 *
 * \param   [in]  pstcAdcIrqCfg  ADC比较配置 @ref stc_adc_threshold_cfg_t
 *
 * \retval  无
 */

void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* pstcAdcThrCfg)
{
    M0P_ADC->HT = pstcAdcThrCfg->u32AdcHighThd;
    M0P_ADC->LT = pstcAdcThrCfg->u32AdcLowThd;

    M0P_ADC->CR1_f.THCH = pstcAdcThrCfg->enSampChSel;

    M0P_ADC->CR1_f.REGCMP = pstcAdcThrCfg->bAdcRegCmp;
    M0P_ADC->CR1_f.HTCMP  = pstcAdcThrCfg->bAdcHtCmp;
    M0P_ADC->CR1_f.LTCMP  = pstcAdcThrCfg->bAdcLtCmp;

}


//@} // AdcGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

