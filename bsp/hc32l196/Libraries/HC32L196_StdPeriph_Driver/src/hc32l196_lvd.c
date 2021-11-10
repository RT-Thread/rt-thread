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
/** \file lvd.c
 **
 ** Low Voltage Detect driver API.
 ** @link Lvd Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_lvd.h"

/**
 ******************************************************************************
 ** \addtogroup LvdGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define IS_VALID_INPUT(x)       ( (x) <= LvdInputPB07 )

#define IS_VALID_THRESHOLD(x)   ( (x) <= LvdTH3p3V )

#define IS_VALID_FILTER(x)      ( (x) <= LvdFilter29ms )

#define IS_VALID_IRQTYPE(x)     ( (x) <= LvdIrqFall )


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
// static void LvdEnableNvic(void);
// static void LvdDisableNvic(void);
// static en_result_t LvdEnable(en_lvd_type_t enType, boolean_t bFlag);

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * \brief   
 *          使能LVD中断
 *
 * \param   [in]  enType  LVD中断类型
 *
 * \retval  en_result_t  Ok:  设置成功
 * \retval  en_result_t  ErrorInvalidParameter:  无效类型
 */
void Lvd_EnableIrq(void)
{
    M0P_LVD->CR_f.IE = TRUE;
}

/**
 * \brief   
 *          除能LVD中断
 *
 * \param   无
 *
 * \retval  无
 */
void Lvd_DisableIrq(void)
{
    M0P_LVD->CR_f.IE = FALSE;
}

/**
 * \brief   
 *          LVD初始化
 *
 * \param   [in]  pstcCfg  LVD配置指针
 *
 * \retval  无
 */
void Lvd_Init(stc_lvd_cfg_t *pstcCfg)
{
    M0P_LVD->CR = 0;

    M0P_LVD->CR = (uint32_t)pstcCfg->enAct        |
                  (uint32_t)pstcCfg->enFilter     |
                  (uint32_t)pstcCfg->enFilterTime |
                  (uint32_t)pstcCfg->enInputSrc   |
                  (uint32_t)pstcCfg->enIrqType    |
                  (uint32_t)pstcCfg->enThreshold;
}

/**
 * \brief   
 *          使能LVD
 *
 * \param   无
 *
 * \retval  无
 *
 */
void Lvd_Enable(void)
{
    M0P_LVD->CR_f.LVDEN = 1u;
}

/**
 * \brief   
 *          除能LVD
 *
 * \param   无
 *
 * \retval  无
 */
void Lvd_Disable(void)
{
    M0P_LVD->CR_f.LVDEN = 0u;
}

/**
 * \brief   
 *          获取LVD中断标志
 *
 * \param   无
 *
 * \retval  boolean_t  中断标志
 */
boolean_t Lvd_GetIrqStat(void)
{
    return M0P_LVD->IFR_f.INTF;

}

/**
 * \brief   
 *          清除LVD中断标志
 *
 * \param   无
 *
 * \retval  无
 */
void Lvd_ClearIrq(void)
{
    M0P_LVD->IFR_f.INTF = 0u;
}

/**
 * \brief   
 *          获取Filter结果
 *
 * \param   无
 *
 * \retval  boolean_t Fliter结果
 */
boolean_t Lvd_GetFilterResult(void)
{
    return (boolean_t)M0P_LVD->IFR_f.FILTER;
}
//@} // LvdGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

