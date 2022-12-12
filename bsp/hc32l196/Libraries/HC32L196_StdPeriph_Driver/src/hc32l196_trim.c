/******************************************************************************
*Copyright(C)2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd("HDSC").
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

/** \file trim.c
 **
 ** Common API of trim.
 ** @link trimGroup Some description @endlink
 **
 **   - 2017-05-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_trim.h"
/**
 *******************************************************************************
 ** \addtogroup TrimGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
#define IS_VALID_TRIMINT(x)             (TrimStop     == (x) ||\
                                         TrimCalCntOf == (x) ||\
                                         TrimXTLFault == (x) ||\
                                         TrimXTHFault == (x) ||\
                                         TrimPLLFault == (x))


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *****************************************************************************
 ** \brief Trim中断标志获取
 **
 **
 ** \param [in]  enIntType           中断类型（RefStop、CalCntOf、XTAL32KFault、XTAL32MFault）
 ** 
 ** \retval TRUE or FALSE                                      
 *****************************************************************************/
boolean_t Trim_GetIntFlag(en_trim_inttype_t enIntType)
{  
    ASSERT(IS_VALID_TRIMINT(enIntType));
    
    if(M0P_CLK_TRIM->IFR&enIntType)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
     
}

/**
 *****************************************************************************
 ** \brief Trim中断标志清除
 **
 **
 ** \param [in]  enIntType           中断类型（RefStop、CalCntOf、XTAL32KFault、XTAL32MFault）
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Trim_ClearIntFlag(en_trim_inttype_t enIntType)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_TRIMINT(enIntType));
    
    M0P_CLK_TRIM->ICLR &= ~(uint32_t)enIntType;
    
    return enResult;
}



/**
 *****************************************************************************
 ** \brief Trim中断使能
 **
 **
 ** 
 ** \retval Null                                      
 *****************************************************************************/
void Trim_EnableIrq (void)
{
    M0P_CLK_TRIM->CR_f.IE = TRUE;
}

/**
 *****************************************************************************
 ** \brief Trim中断禁止
 **
 **
 **
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
void Trim_DisableIrq(void)
{
    M0P_CLK_TRIM->CR_f.IE = FALSE;
}

/**
 *****************************************************************************
 ** \brief Trim初始化配置
 **
 **
 ** \param [in]  pstcCfg           Trim配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Trim_Init(stc_trim_cfg_t* pstcCfg)
{
    en_result_t enResult = Error;

    M0P_CLK_TRIM->CR = 0;
    
    M0P_CLK_TRIM->CR = (uint32_t)pstcCfg->enCALCLK |
                       (uint32_t)pstcCfg->enREFCLK |
                       (uint32_t)pstcCfg->enMON;  
    
    M0P_CLK_TRIM->REFCON = pstcCfg->u32RefCon;
    M0P_CLK_TRIM->CALCON = pstcCfg->u32CalCon;
    
    enResult = Ok;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Trim校准/监测启动运行
 **
 **
 ** 
 ** \retval Null                                     
 *****************************************************************************/
void Trim_Run(void)
{
    M0P_CLK_TRIM->CR_f.TRIM_START = TRUE;
}

/**
 *****************************************************************************
 ** \brief Trim校准/监测停止
 **
 **
 **
 ** 
 ** \retval Null                                      
 *****************************************************************************/
void Trim_Stop(void)
{
    M0P_CLK_TRIM->CR_f.TRIM_START = FALSE;
}

/**
 *****************************************************************************
 ** \brief Trim参考计数器计数值获取
 **
 ** 
 ** \retval u32Data                参考计数器计数值                      
 *****************************************************************************/
uint32_t Trim_RefCntGet(void)
{
    return (uint32_t)M0P_CLK_TRIM->REFCNT;
}

/**
 *****************************************************************************
 ** \brief Trim校准计数器计数值获取
 **
 **
 ** 
 ** 
 ** \retval u32Data                校准计数器计数值                      
 *****************************************************************************/
uint32_t Trim_CalCntGet(void)
{
    return (uint32_t)M0P_CLK_TRIM->CALCNT;
}

//@} // TrimGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
