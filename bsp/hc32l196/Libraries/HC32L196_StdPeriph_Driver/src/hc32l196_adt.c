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
/** \file adt.c
 **
 ** Low Voltage Detect driver API.
 ** @link Lvd Group Some description @endlink
 **
 **   - 2019-04-19 Husj    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_adt.h"

/**
 ******************************************************************************
 ** \addtogroup AdtGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_ADT_STATE(x)         (  AdtCMAF == (x)||\
                                         AdtCMBF == (x)||\
                                         AdtCMCF == (x)||\
                                         AdtCMDF == (x)||\
                                         AdtOVFF == (x)||\
                                         AdtUDFF == (x)||\
                                         AdtDTEF == (x)||\
                                         AdtCMSAUF == (x)||\
                                         AdtCMSADF == (x)||\
                                         AdtCMSBUF == (x)||\
                                         AdtCMSBDF == (x)||\
                                         AdtCntDir == (x) )
#define ADTIM_HW_STASTPCLR_EN            31
#define ADTIM_HW_STASTPCLR_DIS           0x7FFFFFFF
#define ADTIM_SS_TIM4                    1
#define ADTIM_SS_TIM5                    2
#define ADTIM_SS_TIM6                    4
#define ADTIM_PORT_BKE_NUM               15
/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
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



/*****************************************************************
 * \brief   
 *          配置中断
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtIrq         中断类型
 * \param   [in]  bEn              中断使能/禁止
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ****************************************************************/
en_result_t Adt_CfgIrq(M0P_ADTIM_TypeDef *ADTx,
                          en_adt_irq_type_t enAdtIrq,
                          boolean_t bEn)
{
    uint32_t u32Val;

    u32Val = ADTx->ICONR;
    if (bEn)
    {
        u32Val |= 1u<<enAdtIrq;
    }
    else
    {
        u32Val &= ~(1u<<enAdtIrq);
    }
    ADTx->ICONR = u32Val;
    return Ok;
}

/*******************************************************************
 * \brief   
 *          获取中断标志
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtIrq         中断类型
 * 
 *
 * \retval  TRUE/FALSE
 * 
 *****************************************************************/
boolean_t Adt_GetIrqFlag(M0P_ADTIM_TypeDef *ADTx,
                           en_adt_irq_type_t enAdtIrq)
{
    uint32_t u32Val;
    boolean_t bEn;

    ASSERT(IS_VALID_ADT_UNIT(enAdtUnit));

    u32Val = ADTx->IFR;
    bEn = (u32Val>>enAdtIrq) & 0x1;

    return bEn;
}

/****************************************************************
 * \brief   
 *          清除中断标志
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtIrq         中断类型
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 ****************************************************************/
en_result_t Adt_ClearIrqFlag(M0P_ADTIM_TypeDef *ADTx,
                             en_adt_irq_type_t enAdtIrq)
{
    ADTx->ICLR = ~(1u<<enAdtIrq);
    return Ok;
}

/****************************************************************
 * \brief   
 *          清除所有中断标志
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 ****************************************************************/
en_result_t Adt_ClearAllIrqFlag(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->ICLR = 0;
    return Ok;
}

/**************************************************************
 * \brief   
 *          配置硬件递加事件
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwCntUp     硬件递加事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 ****************************************************************/
en_result_t Adt_CfgHwCntUp(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_cnt_t enAdtHwCntUp)
{
    uint32_t u32Val;
     

    if (AdtHwCntMax <= enAdtHwCntUp)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCUPR;
    ADTx->HCUPR = u32Val | (1u<<enAdtHwCntUp);
    return Ok;
}

/**************************************************************
 * \brief   
 *          清除硬件递加事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 ************************************************************/
en_result_t Adt_ClearHwCntUp(M0P_ADTIM_TypeDef *ADTx)
{

    ADTx->HCUPR = 0;
    return Ok;
}


/**********************************************************
 * \brief   
 *          配置硬件递减事件
 *
 * \param   [in]  ADTx               ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwCntDwn      硬件递减事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ***********************************************************/
en_result_t Adt_CfgHwCntDwn(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_cnt_t enAdtHwCntDwn)
{
    uint32_t u32Val;
     

    if(AdtHwCntMax <= enAdtHwCntDwn)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCDOR;
    ADTx->HCDOR = u32Val | (1u<<enAdtHwCntDwn);
    return Ok;
}

/******************************************************************
 * \brief   
 *          清除硬件递减事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 *****************************************************************/
en_result_t Adt_ClearHwCntDwn(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HCDOR = 0;
    return Ok;
}

/******************************************************************
 * \brief   
 *          配置硬件启动事件
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwStart     硬件启动事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *******************************************************************/
en_result_t Adt_CfgHwStart(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwStart)
{
    uint32_t u32Val;
     

    if(AdtHwTrigEnd <= enAdtHwStart)
    {
        return ErrorInvalidParameter;
    }
    u32Val = ADTx->HSTAR;
    ADTx->HSTAR = u32Val | (1u<<enAdtHwStart);
    return Ok;
}

/************************************************************************
 * \brief   
 *          清除硬件启动事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 ***********************************************************************/
en_result_t Adt_ClearHwStart(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HSTAR = 0;
    return Ok;
}

/*********************************************************************
 * \brief   
 *          使能硬件启动
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 *********************************************************************/
en_result_t Adt_EnableHwStart(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;
    
    u32Val = ADTx->HSTAR;
    ADTx->HSTAR = u32Val | (1u<<ADTIM_HW_STASTPCLR_EN);
    return Ok;
}

/*************************************************************************
 * \brief   
 *          除能硬件启动
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 ************************************************************************/
en_result_t Adt_DisableHwStart(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HSTAR;
    ADTx->HSTAR = u32Val & ADTIM_HW_STASTPCLR_DIS;
    return Ok;
}

/****************************************************************
 * \brief   
 *          配置硬件停止事件
 *
 * \param   [in]  ADTx            ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwStop     硬件停止事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ***************************************************************/
en_result_t Adt_CfgHwStop(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwStop)
{
    uint32_t u32Val;
    
    if(AdtHwTrigEnd <= enAdtHwStop)
    {
        return ErrorInvalidParameter;
    }
    
    u32Val = ADTx->HSTPR;
    ADTx->HSTPR = u32Val | (1u<<enAdtHwStop);
    return Ok;
}

/***************************************************************
 * \brief
 *          清除硬件停止事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 ***************************************************************/
en_result_t Adt_ClearHwStop(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HSTPR = 0;
    return Ok;
}

/*************************************************************
 * \brief   
 *          使能硬件停止
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 **********************************************************/
en_result_t Adt_EnableHwStop(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;
    
    u32Val = ADTx->HSTPR;
    ADTx->HSTPR = u32Val | (1u<<ADTIM_HW_STASTPCLR_EN);
    return Ok;
}

/*****************************************************************************
 * \brief   
 *          除能硬件停止
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 ***************************************************************************/
en_result_t Adt_DisableHwStop(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HSTPR;
    ADTx->HSTPR = u32Val & ADTIM_HW_STASTPCLR_DIS;
    return Ok;
}

/**************************************************************************
 * \brief   
 *          配置硬件清零事件
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwClear      硬件清零事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *************************************************************************/
en_result_t Adt_CfgHwClear(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwClear)
{
    uint32_t u32Val;
     

    if(AdtHwTrigEnd <= enAdtHwClear)
    {
        return ErrorInvalidParameter;
    }
    
    u32Val = ADTx->HCELR;
    ADTx->HCELR = u32Val | (1u<<enAdtHwClear);
    return Ok;
}

/**************************************************************************
 * \brief   
 *          清除硬件清零事件
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 **************************************************************************/
en_result_t Adt_ClearHwClear(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HCELR = 0;
    return Ok;
}

/***************************************************************************
 * \brief   
 *          使能硬件清零
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 *************************************************************************/
en_result_t Adt_EnableHwClear(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HCELR;
    ADTx->HCELR = u32Val | (1u<<ADTIM_HW_STASTPCLR_EN);
    return Ok;
}

/************************************************************************
 * \brief   
 *          除能硬件清零
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 **********************************************************************/
en_result_t Adt_DisableHwClear(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HCELR;
    ADTx->HCELR = u32Val & ADTIM_HW_STASTPCLR_DIS;
    return Ok;
}

/*******************************************************************
 * \brief   
 *          配置硬件捕获A事件
 *
 * \param   [in]  ADTx               ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwCaptureA    硬件捕获A事件选择
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *******************************************************************/
en_result_t Adt_CfgHwCaptureA(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwCaptureA)
{
    uint32_t u32Val;
     

    if(AdtHwTrigEnd <= enAdtHwCaptureA)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCPAR;
    ADTx->HCPAR = u32Val | (1u<<enAdtHwCaptureA);
    ADTx->PCONR_f.CAPCA = 1;
    return Ok;
}

/************************************************************************
 * \brief   
 *          清除硬件捕获A事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 ***********************************************************************/
en_result_t Adt_ClearHwCaptureA(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HCPAR = 0;
    return Ok;
}

/*********************************************************************
 * \brief   
 *          配置硬件捕获B事件
 *
 * \param   [in]  ADTx                ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwCaptureB     硬件捕获B事件选择
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ********************************************************************/
en_result_t Adt_CfgHwCaptureB(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwCaptureB)
{
    uint32_t u32Val;
     

    if(AdtHwTrigEnd <= enAdtHwCaptureB)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCPBR;
    ADTx->HCPBR =  u32Val | (1u<<enAdtHwCaptureB);
    ADTx->PCONR_f.CAPCB = 1;
    return Ok;
}

/********************************************************************
 * \brief   
 *          清除硬件捕获B事件
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 * 
 *******************************************************************/
en_result_t Adt_ClearHwCaptureB(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HCPBR = 0;
    return Ok;
}

/*****************************************************************
 * \brief   
 *          软件同步开始
 *
 * \param   [in]  pstcAdtSwSyncStart    软件同步开始指针
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ***************************************************************/
en_result_t Adt_SwSyncStart(stc_adt_sw_sync_t* pstcAdtSwSyncStart)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncStart)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncStart->bAdTim4)
    {
        u32Val |= ADTIM_SS_TIM4;
    }
    if (pstcAdtSwSyncStart->bAdTim5)
    {
        u32Val |= ADTIM_SS_TIM5;
    }
    if (pstcAdtSwSyncStart->bAdTim6)
    {
        u32Val |= ADTIM_SS_TIM6;
    }

    M0P_ADTIM4->SSTAR = u32Val;
    return Ok;
}

/***************************************************************
 * \brief   
 *          软件同步停止
 *
 * \param   [in]  pstcAdtSwSyncStop     软件同步停止指针
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ***************************************************************/
en_result_t Adt_SwSyncStop(stc_adt_sw_sync_t* pstcAdtSwSyncStop)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncStop)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncStop->bAdTim4)
    {
        u32Val |= ADTIM_SS_TIM4;
    }
    if (pstcAdtSwSyncStop->bAdTim5)
    {
        u32Val |= ADTIM_SS_TIM5;
    }
    if (pstcAdtSwSyncStop->bAdTim6)
    {
        u32Val |= ADTIM_SS_TIM6;
    }

    M0P_ADTIM4->SSTPR = u32Val;
    return Ok;
}

/*****************************************************************
 * \brief   
 *          软件同步清零
 *
 * \param   [in]  pstcAdtSwSyncClear    软件同步清零指针
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *******************************************************************/
en_result_t Adt_SwSyncClear(stc_adt_sw_sync_t* pstcAdtSwSyncClear)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncClear)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncClear->bAdTim4)
    {
        u32Val |= ADTIM_SS_TIM4;
    }
    if (pstcAdtSwSyncClear->bAdTim5)
    {
        u32Val |= ADTIM_SS_TIM5;
    }
    if (pstcAdtSwSyncClear->bAdTim6)
    {
        u32Val |= ADTIM_SS_TIM6;
    }

    M0P_ADTIM4->SCLRR = u32Val;
    return Ok;
}

/*******************************************************************
 * \brief   
 *          获取软件同步运行状态
 *
 * \param   [in]  pstcAdtSwSyncState    ADV Timer软件同步运行状态指针
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *******************************************************************/
en_result_t Adt_GetSwSyncState(stc_adt_sw_sync_t* pstcAdtSwSyncState)
{
    if (NULL == pstcAdtSwSyncState)
    {
        return ErrorInvalidParameter;
    }

    if (M0P_ADTIM4->SSTAR & ADTIM_SS_TIM4)
    {
        pstcAdtSwSyncState->bAdTim4 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim4 = FALSE;
    }
    if (M0P_ADTIM4->SSTAR & ADTIM_SS_TIM5)
    {
        pstcAdtSwSyncState->bAdTim5 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim5 = FALSE;
    }
    if (M0P_ADTIM4->SSTAR & ADTIM_SS_TIM6)
    {
        pstcAdtSwSyncState->bAdTim6 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim6 = FALSE;
    }
    return Ok;
}

/************************************************************************
 * \brief   
 *          AOS触发配置
 *
 * \param   [in]  pstcAdtAosTrigCfg 触发配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ************************************************************************/
en_result_t Adt_AosTrigCfg(stc_adt_aos_trig_cfg_t* pstcAdtAosTrigCfg)
{
    if (NULL == pstcAdtAosTrigCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADTIM4->ITRIG_f.IAOS0S = pstcAdtAosTrigCfg->enAos0TrigSrc;
    M0P_ADTIM4->ITRIG_f.IAOS1S = pstcAdtAosTrigCfg->enAos1TrigSrc;
    M0P_ADTIM4->ITRIG_f.IAOS2S = pstcAdtAosTrigCfg->enAos2TrigSrc;
    M0P_ADTIM4->ITRIG_f.IAOS3S = pstcAdtAosTrigCfg->enAos3TrigSrc;
    return Ok;
}

/**********************************************************************
 * \brief   
 *          中断触发配置
 *
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtIrqTrigCfg     触发配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ***********************************************************************/
en_result_t Adt_IrqTrigCfg(M0P_ADTIM_TypeDef *ADTx,
                              stc_adt_irq_trig_cfg_t* pstcAdtIrqTrigCfg)
{
    if(NULL == pstcAdtIrqTrigCfg)
    {
        return ErrorInvalidParameter;
    }
    
    ADTx->CR_f.CMAE = pstcAdtIrqTrigCfg->bAdtCntMatchATrigEn;
    ADTx->CR_f.CMBE = pstcAdtIrqTrigCfg->bAdtCntMatchBTrigEn;
    ADTx->CR_f.CMCE = pstcAdtIrqTrigCfg->bAdtCntMatchCTrigEn;
    ADTx->CR_f.CMDE = pstcAdtIrqTrigCfg->bAdtCntMatchDTrigEn;
    ADTx->CR_f.OVFE = pstcAdtIrqTrigCfg->bAdtOverFlowTrigEn;
    ADTx->CR_f.UDFE = pstcAdtIrqTrigCfg->bAdtUnderFlowTrigEn;
    ADTx->CR_f.DMA_G_CMA = pstcAdtIrqTrigCfg->bAdtCntMatchATrigDmaEn;
    ADTx->CR_f.DMA_G_CMB = pstcAdtIrqTrigCfg->bAdtCntMatchBTrigDmaEn;
    ADTx->CR_f.DMA_G_CMC = pstcAdtIrqTrigCfg->bAdtCntMatchCTrigDmaEn;
    ADTx->CR_f.DMA_G_CMD = pstcAdtIrqTrigCfg->bAdtCntMatchDTrigDmaEn;
    ADTx->CR_f.DMA_G_OVF = pstcAdtIrqTrigCfg->bAdtOverFlowTrigDmaEn;
    ADTx->CR_f.DMA_G_UDF = pstcAdtIrqTrigCfg->bAdtUnderFlowTrigDmaEn;
    ADTx->CR_f.DMA_S_CMA = pstcAdtIrqTrigCfg->bAdtSpecilMatchATrigDmaEn;
    ADTx->CR_f.DMA_S_CMB = pstcAdtIrqTrigCfg->bAdtSpecilMatchBTrigDmaEn;
    
    return Ok;
}

/*************************************************************************
 * \brief   
 *          端口触发配置
 *
 * \param   [in]  enAdtTrigPort         触发端口
 * \param   [in]  pstcAdtPortTrigCfg    触发配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *************************************************************************/
en_result_t Adt_PortTrigCfg(en_adt_trig_port_t enAdtTrigPort,
                               stc_adt_port_trig_cfg_t* pstcAdtPortTrigCfg)
{
    if (NULL == pstcAdtPortTrigCfg)
    {
        return ErrorInvalidParameter;
    }

    switch (enAdtTrigPort)
    {
        case AdtTrigA:
            M0P_ADTIM4->TTRIG_f.TRIGAS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_ADTIM4->FCONR_f.NOFIENTA = pstcAdtPortTrigCfg->bFltEn;
            M0P_ADTIM4->FCONR_f.NOFICKTA = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigB:
            M0P_ADTIM4->TTRIG_f.TRIGBS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_ADTIM4->FCONR_f.NOFIENTB = pstcAdtPortTrigCfg->bFltEn;
            M0P_ADTIM4->FCONR_f.NOFICKTB = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigC:
            M0P_ADTIM4->TTRIG_f.TRIGCS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_ADTIM4->FCONR_f.NOFIENTC = pstcAdtPortTrigCfg->bFltEn;
            M0P_ADTIM4->FCONR_f.NOFICKTC = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigD:
            M0P_ADTIM4->TTRIG_f.TRIGDS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_ADTIM4->FCONR_f.NOFIENTD = pstcAdtPortTrigCfg->bFltEn;
            M0P_ADTIM4->FCONR_f.NOFICKTD = pstcAdtPortTrigCfg->enFltClk;
            break;

        default:
            return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief   
 *          CHxX端口配置
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort    CHxX端口
 * \param   [in]  pstcAdtCHxXCfg   CHxX端口配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *********************************************************************/
en_result_t Adt_CHxXPortCfg(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                stc_adt_CHxX_port_cfg_t* pstcAdtCHxXCfg)
{
    if(NULL == pstcAdtCHxXCfg)
    {
        return ErrorInvalidParameter;
    }

    switch (enAdtCHxXPort)
    {
        case AdtCHxA:
            ADTx->PCONR_f.CAPCA = pstcAdtCHxXCfg->enCap;
            ADTx->PCONR_f.STACA = pstcAdtCHxXCfg->enStaOut;
            ADTx->PCONR_f.STPCA = pstcAdtCHxXCfg->enStpOut;
            ADTx->PCONR_f.STASTPSA = pstcAdtCHxXCfg->enStaStp;
            ADTx->PCONR_f.CMPCA = pstcAdtCHxXCfg->enCmpc;
            ADTx->PCONR_f.PERCA = pstcAdtCHxXCfg->enPerc;
            ADTx->PCONR_f.OUTENA = pstcAdtCHxXCfg->bOutEn;
            ADTx->PCONR_f.DISSELA = pstcAdtCHxXCfg->enDisSel;
            ADTx->PCONR_f.DISVALA = pstcAdtCHxXCfg->enDisVal;
            ADTx->FCONR_f.NOFIENGA = pstcAdtCHxXCfg->bFltEn;
            ADTx->FCONR_f.NOFICKGA = pstcAdtCHxXCfg->enFltClk;
            break;

        case AdtCHxB:
            ADTx->PCONR_f.CAPCB = pstcAdtCHxXCfg->enCap;
            ADTx->PCONR_f.STACB = pstcAdtCHxXCfg->enStaOut;
            ADTx->PCONR_f.STPCB = pstcAdtCHxXCfg->enStpOut;
            ADTx->PCONR_f.STASTPSB = pstcAdtCHxXCfg->enStaStp;
            ADTx->PCONR_f.CMPCB = pstcAdtCHxXCfg->enCmpc;
            ADTx->PCONR_f.PERCB = pstcAdtCHxXCfg->enPerc;
            ADTx->PCONR_f.OUTENB = pstcAdtCHxXCfg->bOutEn;
            ADTx->PCONR_f.DISSELB = pstcAdtCHxXCfg->enDisSel;
            ADTx->PCONR_f.DISVALB = pstcAdtCHxXCfg->enDisVal;
            ADTx->FCONR_f.NOFIENGB = pstcAdtCHxXCfg->bFltEn;
            ADTx->FCONR_f.NOFICKGB = pstcAdtCHxXCfg->enFltClk;
            break;

        default:
            return ErrorInvalidParameter;
    }

    return Ok;
}

/************************************************************************
 * \brief   
 *          使能端口刹车
 *
 * \param   [in]  port              端口
 * \param   [in]  pstcAdtBrkPtCfg   端口刹车配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ************************************************************************/
en_result_t Adt_EnableBrakePort(uint8_t port, stc_adt_break_port_cfg_t* pstcAdtBrkPtCfg)
{
    uint32_t u32Val;

    if (NULL == pstcAdtBrkPtCfg)
    {
        return ErrorInvalidParameter;
    }
    
    u32Val = M0P_ADTIM4->PTBKP;
    u32Val &= ~(1u<<port);
    M0P_ADTIM4->PTBKP = u32Val | (pstcAdtBrkPtCfg->enPol<<port);
    
    u32Val = M0P_ADTIM4->PTBKS;
    M0P_ADTIM4->PTBKS = u32Val | (1u<<port);

    return Ok;
}

/**********************************************************************
 * \brief   
 *          清除端口刹车
 *
 * \param   none
 *
 * \retval  none
 **********************************************************************/
void Adt_ClearBrakePort(void)
{
    M0P_ADTIM4->PTBKS = 0;
}

/*********************************************************************
 * \brief   
 *          无效条件3配置
 *
 * \param   [in]  pstcAdtDisable3   无效条件3配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ********************************************************************/
en_result_t Adt_Disable3Cfg(stc_adt_disable_3_cfg_t* pstcAdtDisable3)
{
    uint8_t i;

    if (NULL == pstcAdtDisable3)
    {
        return ErrorInvalidParameter;
    }

    Adt_ClearBrakePort();
    for (i = 0; i <= ADTIM_PORT_BKE_NUM; i++)
    {
        if (TRUE == pstcAdtDisable3->stcBrkPtCfg[i].bPortEn)
        {
            Adt_EnableBrakePort(i, &pstcAdtDisable3->stcBrkPtCfg[i]);
        }
    }

    M0P_ADTIM4->AOSSR_f.BFILTEN = pstcAdtDisable3->bFltEn;
    M0P_ADTIM4->AOSSR_f.BFILTS = pstcAdtDisable3->enFltClk;

    return Ok;
}

/*********************************************************************
 * \brief   软件刹车 Enable/Disable(仅适用于无效条件3使能的情况下)
 *
 * \param   [in]  bSwBrk           软件刹车使能/禁止
 *
 * \retval  en_result_t  Ok:  配置成功
 ********************************************************************/
en_result_t Adt_SwBrake(boolean_t bSwBrk)
{
    M0P_ADTIM4->AOSSR_f.SOFTBK = bSwBrk;

    return Ok;
}

/*******************************************************************
 * \brief   
 *          获取端口刹车标志
 *
 * \param   none
 *
 * \retval  TRUE or FALSE
 ******************************************************************/
boolean_t Adt_GetPortBrakeFlag(void)
{
    return M0P_ADTIM4->AOSSR_f.FBRAKE;
}

/******************************************************************
 * \brief   
 *          清除端口刹车标志
 *
 * \param   none
 *
 * \retval  none
 ******************************************************************/
void Adt_ClearPortBrakeFlag(void)
{
    M0P_ADTIM4->AOSCL_f.FBRAKE = 0;
}

/********************************************************************
 * \brief   
 *          无效条件1配置
 *
 * \param   [in]  pstcAdtDisable1   无效条件1配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ********************************************************************/
en_result_t Adt_Disable1Cfg(stc_adt_disable_1_cfg_t* pstcAdtDisable1)
{

    if (NULL == pstcAdtDisable1)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADTIM4->AOSSR_f.SMH2 = pstcAdtDisable1->bTim6OutSH;
    M0P_ADTIM4->AOSSR_f.SMH1 = pstcAdtDisable1->bTim5OutSH;
    M0P_ADTIM4->AOSSR_f.SMH0 = pstcAdtDisable1->bTim4OutSH;
    M0P_ADTIM4->AOSSR_f.SML2 = pstcAdtDisable1->bTim6OutSL;
    M0P_ADTIM4->AOSSR_f.SML1 = pstcAdtDisable1->bTim5OutSL;
    M0P_ADTIM4->AOSSR_f.SML0 = pstcAdtDisable1->bTim4OutSL;

    return Ok;
}

/********************************************************************
 * \brief   
 *          获取同高同低刹车标志
 *
 * \param   none
 *
 * \retval  TRUE or FALSE
 ********************************************************************/
boolean_t Adt_GetSameBrakeFlag(void)
{
    return M0P_ADTIM4->AOSSR_f.FSAME;
}

/*********************************************************************
 * \brief   
 *          清除同高同低刹车标志
 *
 * \param   none
 *
 * \retval  none
 *********************************************************************/
void Adt_ClearSameBrakeFlag(void)
{
    M0P_ADTIM4->AOSCL_f.FSAME = 0;
}

/********************************************************************
 * \brief   
 *          PWM展频配置
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtPwmDitherCfg   PWM展频配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *********************************************************************/
en_result_t Adt_PwmDitherCfg(M0P_ADTIM_TypeDef *ADTx, stc_adt_pwm_dither_cfg_t* pstcAdtPwmDitherCfg)
{
     
    
    if (NULL == pstcAdtPwmDitherCfg)
    {
        return ErrorInvalidParameter;
    }

    ADTx->CR_f.DITENS = pstcAdtPwmDitherCfg->enAdtPDType;
    ADTx->CR_f.DITENB = pstcAdtPwmDitherCfg->bTimxBPDEn;
    ADTx->CR_f.DITENA = pstcAdtPwmDitherCfg->bTimxAPDEn;
    
    return Ok;
}

/**********************************************************************
 * \brief   
 *          ADT初始化
 *
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtBaseCntCfg     计数配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 **********************************************************************/
en_result_t Adt_Init(M0P_ADTIM_TypeDef *ADTx, stc_adt_basecnt_cfg_t* pstcAdtBaseCntCfg)
{
     

    if(NULL == pstcAdtBaseCntCfg)
    {
        return ErrorInvalidParameter;
    }

    if (AdtTriangleModeB < pstcAdtBaseCntCfg->enCntMode)
    {
        return ErrorInvalidParameter;
    }

    ADTx->GCONR_f.MODE = pstcAdtBaseCntCfg->enCntMode;
    ADTx->GCONR_f.DIR = pstcAdtBaseCntCfg->enCntDir;
    ADTx->GCONR_f.CKDIV = pstcAdtBaseCntCfg->enCntClkDiv;

    return Ok;
}

/************************************************************************
 * \brief   
 *          ADT Deinit
 *
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 ***********************************************************************/
en_result_t Adt_DeInit(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->GCONR_f.START = 0;
    ADTx->CNTER = 0;
    ADTx->PCONR = 0;
    ADTx->GCONR = 0x00000100;
    ADTx->DCONR = 0;
    ADTx->ICONR = 0;
    ADTx->BCONR = 0;
    ADTx->FCONR = 0;
    ADTx->VPERR = 0;
    ADTx->PERAR = 0xFFFF;
    ADTx->PERBR = 0xFFFF;
    ADTx->GCMAR = 0xFFFF;
    ADTx->GCMBR = 0xFFFF;
    ADTx->GCMCR = 0xFFFF;
    ADTx->GCMDR = 0xFFFF;
    ADTx->DTDAR = 0xFFFF;
    ADTx->DTUAR = 0xFFFF;
    ADTx->HSTAR = 0;
    ADTx->HSTPR = 0;
    ADTx->HCELR = 0;
    ADTx->HCPAR = 0;
    ADTx->HCPBR = 0;
    ADTx->HCUPR = 0;
    ADTx->HCDOR = 0;
    ADTx->SSTAR = 0;
    ADTx->SSTPR = 0;
    ADTx->SCLRR = 0;
    ADTx->IFR = 0;
    ADTx->CR = 0x00000300;
    ADTx->AOSSR = 0;
    ADTx->AOSCL = 0;
    ADTx->PTBKS = 0;
    ADTx->PTBKP = 0;
    ADTx->TTRIG = 0;
    ADTx->ITRIG = 0;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          开始计数
 *
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 ***********************************************************************/
en_result_t Adt_StartCount(M0P_ADTIM_TypeDef *ADTx)
{

    ADTx->GCONR_f.START = 1;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          停止计数
 *
 * \param   [in]  ADTx        ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 **********************************************************************/
en_result_t Adt_StopCount(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->GCONR_f.START = 0;

    return Ok;
}

/********************************************************************
 * \brief   
 *          设置计数值
 *
 * \param   [in]  ADTx           ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16Value       计数值
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 *******************************************************************/
en_result_t Adt_SetCount(M0P_ADTIM_TypeDef *ADTx, uint16_t u16Value)
{
    ADTx->CNTER_f.CNT = u16Value;
    return Ok;
}

/********************************************************************
 * \brief   
 *          获取计数值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * 
 *
 * \retval  uint16_t  u16Value:  当前计数值
 *  
 *******************************************************************/
uint16_t Adt_GetCount(M0P_ADTIM_TypeDef *ADTx)
{
    uint16_t u16Value;

    ASSERT(IS_VALID_ADT_UNIT(enAdtUnit));

    u16Value = ADTx->CNTER_f.CNT;
    
    return u16Value;
}

/**************************************************************************
 * \brief   
 *          清除计数值
 *
 * \param   [in]  ADTx        ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * 
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 **************************************************************************/
en_result_t Adt_ClearCount(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->CNTER_f.CNT = 0;
    return Ok;
}

/*************************************************************************
 * \brief   
 *          获取有效周期计数值
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  uint8_t u8TempCnt:    有效周期值
 * 
 *************************************************************************/
uint8_t Adt_GetVperNum(M0P_ADTIM_TypeDef *ADTx)
{
    uint8_t u8TempCnt;
     

    ASSERT(IS_VALID_ADT_UNIT(enAdtUnit));
    
    u8TempCnt = ADTx->STFLR_f.VPERNUM;

    return u8TempCnt;
}

/*************************************************************************
 * \brief   
 *          获取状态标志
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
* \param    [in]  enstate           状态标志类型 
 *
 * \retval  TURE/FALSE
 * 
 *************************************************************************/
boolean_t Adt_GetState(M0P_ADTIM_TypeDef *ADTx, en_adt_state_type_t enstate)
{
     

    ASSERT(IS_VALID_ADT_UNIT(enAdtUnit));
    ASSERT(IS_VALID_ADT_STATE(enstate));

    return GetBit(((uint32_t)&ADTx->STFLR), enstate);
}

/***********************************************************************
 * \brief   
 *          配置计数周期
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16Period         计数周期值
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 ***********************************************************************/
en_result_t Adt_SetPeriod(M0P_ADTIM_TypeDef *ADTx, uint16_t u16Period)
{
    ADTx->PERAR = u16Period;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          配置计数周期缓冲
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16PeriodBuf      计数周期缓冲值
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 ***********************************************************************/
en_result_t Adt_SetPeriodBuf(M0P_ADTIM_TypeDef *ADTx, uint16_t u16PeriodBuf)
{
    ADTx->PERBR = u16PeriodBuf;
    ADTx->BCONR_f.BENP = 1u;

    return Ok;
}

/**********************************************************************
 * \brief   
 *          清除计数周期缓冲
 *
 * \param   [in]  ADTx        ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 **********************************************************************/
en_result_t Adt_ClearPeriodBuf(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->BCONR_f.BENP = 0;
    ADTx->PERBR = 0;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          配置有效计数周期
 *
 * \param   [in]  ADTx                     ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtValidPerCfg       有效计数周期配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ***********************************************************************/
en_result_t Adt_SetValidPeriod(M0P_ADTIM_TypeDef *ADTx,
                               stc_adt_validper_cfg_t* pstcAdtValidPerCfg)
{
     

    if(NULL == pstcAdtValidPerCfg)
    {
        return ErrorInvalidParameter;
    }

    ADTx->VPERR_f.PCNTS = pstcAdtValidPerCfg->enValidCnt;
    ADTx->VPERR_f.PCNTE = pstcAdtValidPerCfg->enValidCdt;
    ADTx->VPERR_f.GEPERID = pstcAdtValidPerCfg->bPeriodD;
    ADTx->VPERR_f.GEPERIC = pstcAdtValidPerCfg->bPeriodC;
    ADTx->VPERR_f.GEPERIB = pstcAdtValidPerCfg->bPeriodB;
    ADTx->VPERR_f.GEPERIA = pstcAdtValidPerCfg->bPeriodA;

    return Ok;
}

/************************************************************************
 * \brief   
 *          配置比较输出计数基准值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCompare      通用比较基准寄存器
 * \param   [in]  u16Compare        比较基准值
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *************************************************************************/
en_result_t Adt_SetCompareValue(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_compare_t enAdtCompare,
                                uint16_t u16Compare)
{
    if (AdtCompareA == enAdtCompare)
    {
        ADTx->GCMAR = u16Compare;
    }
    else if (AdtCompareB == enAdtCompare)
    {
        ADTx->GCMBR = u16Compare;
    }
    else if (AdtCompareC == enAdtCompare)
    {
        ADTx->GCMCR = u16Compare;
    }
    else if (AdtCompareD == enAdtCompare)
    {
        ADTx->GCMDR = u16Compare;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/************************************************************************
 * \brief   
 *          配置专用比较计数基准值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtSpclCmp      专用比较基准值寄存器
 * \param   [in]  u16SpclCmp        比较基准值
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *************************************************************************/
en_result_t Adt_SetSpecilCompareValue(M0P_ADTIM_TypeDef *ADTx,
                                      en_adt_special_compare_t enAdtSpclCmp,
                                      uint16_t u16SpclCmp)
{
    if (AdtSpclCompA == enAdtSpclCmp)
    {
        ADTx->SCMAR_f.SCMA = u16SpclCmp;
    }
    else if (AdtSpclCompB == enAdtSpclCmp)
    {
        ADTx->SCMBR_f.SCMB = u16SpclCmp;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**********************************************************************
 * \brief   
 *          配置通用比较值/捕获值缓存传送
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort     TIMxX通道
 * \param   [in]  bCompareBufEn     通用比较值缓存传送使能
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 **********************************************************************/
en_result_t Adt_EnableValueBuf(M0P_ADTIM_TypeDef *ADTx,
                                 en_adt_CHxX_port_t enAdtCHxXPort,
                                 boolean_t bCompareBufEn)
{
    if (AdtCHxA == enAdtCHxXPort)
    {
        ADTx->BCONR_f.BENA = bCompareBufEn;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        ADTx->BCONR_f.BENB = bCompareBufEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief   
 *          清除比较输出计数值/捕获值缓存
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort     TIMxX通道
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 **********************************************************************/
en_result_t Adt_ClearValueBuf(M0P_ADTIM_TypeDef *ADTx,
                                     en_adt_CHxX_port_t enAdtCHxXPort)
{
    if (AdtCHxA == enAdtCHxXPort)
    {
        ADTx->GCMCR = 0;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        ADTx->GCMDR = 0;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief   
 *          获取捕获值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort     TIMxX通道
 * \param   [in]  pu16Capture       捕获值指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ***********************************************************************/
en_result_t Adt_GetCaptureValue(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16Capture)
{
    if (AdtCHxA == enAdtCHxXPort)
    {
        *pu16Capture = ADTx->GCMAR_f.GCMA;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        *pu16Capture = ADTx->GCMBR_f.GCMB;
    }
    else
    {
        return ErrorInvalidParameter;
    }
    return Ok;
}

/**********************************************************************
 * \brief   
 *          获取捕获缓存值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort     TIMxX通道
 * \param   [in]  pu16CaptureBuf    捕获缓存值指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ***********************************************************************/
en_result_t Adt_GetCaptureBuf(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16CaptureBuf)
{
    if (AdtCHxA == enAdtCHxXPort)
    {
        *pu16CaptureBuf = ADTx->GCMCR_f.GCMC;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        *pu16CaptureBuf = ADTx->GCMDR_f.GCMD;
    }
    else
    {
        return ErrorInvalidParameter;
    }
    return Ok;
}

/***********************************************************************
 * \brief   
 *          设置死区时间上基准值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16Value          死区时间上基准值
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 ************************************************************************/
en_result_t Adt_SetDTUA(M0P_ADTIM_TypeDef *ADTx,
                        uint16_t u16Value)
{
    ADTx->DTUAR = u16Value;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          设置死区时间下基准值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16Value          死区时间下基准值
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 ***********************************************************************/
en_result_t Adt_SetDTDA(M0P_ADTIM_TypeDef *ADTx,
                        uint16_t u16Value)
{
    ADTx->DTDAR = u16Value;

    return Ok;
}

/******************************************************************
 * \brief   
 *          配置死区时间功能
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  bDTEn         死区功能使能
 * \param   [in]  bEqual        DTDAR的值和DTUAR的值自动相等
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 *****************************************************************/
en_result_t Adt_CfgDT(M0P_ADTIM_TypeDef *ADTx,
                         boolean_t bDTEn,
                         boolean_t bEqual)
{
    ADTx->DCONR_f.DTCEN = bDTEn;
    ADTx->DCONR_f.SEPA = bEqual;

    return Ok;
}

/*************************************************************************
 * \brief   
 *          Z相输入屏蔽设置
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtZMaskCfg   Z相输入屏蔽功能配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * 
 *************************************************************************/
en_result_t Adt_CfgZMask(M0P_ADTIM_TypeDef *ADTx, stc_adt_zmask_cfg_t* pstcAdtZMaskCfg)
{
    if(NULL == pstcAdtZMaskCfg)
    {
        return ErrorInvalidParameter;
    }

    ADTx->GCONR_f.ZMSK = pstcAdtZMaskCfg->enZMaskCycle;
    ADTx->GCONR_f.ZMSKPOS = pstcAdtZMaskCfg->bFltPosCntMaksEn;
    ADTx->GCONR_f.ZMSKREV = pstcAdtZMaskCfg->bFltRevCntMaksEn;

    return Ok;
}

//@} // AdtGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

