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
/** \file wdt.c
 **
 ** WDT function driver API.
 ** @link WdtGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "wdt.h"

/**
 ******************************************************************************
 ** \defgroup WdtGroup
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/
static func_ptr_t pfnWdtCallback = NULL;
/**
 ******************************************************************************
 ** \brief  WDT溢出时间设置函数
 **
 ** \param [in] u8LoadValue 溢出时间
 **
 ** \retval 无
 **
 ******************************************************************************/
void Wdt_WriteWdtLoad(uint8_t u8LoadValue)
{
    M0P_WDT->CON_f.WOV = u8LoadValue;
}
/**
 ******************************************************************************
 ** \brief  WDT初始化函数
 **
 ** \param [in] stcConfig 初始化结构
 **
 ** \retval Ok
 **
 ******************************************************************************/
en_result_t Wdt_Init(stc_wdt_config_t* pstcConfig)
{
    en_result_t enRet = Error;
    ASSERT(NULL != pstcConfig);
    Wdt_WriteWdtLoad(pstcConfig->u8LoadValue);
    pfnWdtCallback = pstcConfig->pfnWdtIrqCb;
    M0P_WDT->CON_f.WINT_EN = pstcConfig->enResetEnable;
    if(pstcConfig->enResetEnable)
    {
        EnableNvic(WDT_IRQn,IrqLevel3,TRUE);
    }
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief  WDT复位及启动函数
 **
 ** \param [in] 无
 **
 ** \retval Ok
 **
 ******************************************************************************/
en_result_t Wdt_Start(void)
{
    en_result_t enRet = Error;
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief  WDT复位及启动函数
 **
 ** \param [in] 无
 **
 ** \retval Ok
 **
 ******************************************************************************/
void Wdt_Feed(void) 
{
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;  
}
/**
 ******************************************************************************
 ** \brief  WDT读取当前计数值函数
 **
 ** \param [in] 无
 **
 ** \retval 计数值
 **
 ******************************************************************************/
uint8_t Wdt_ReadWdtValue(void)
{
    uint8_t u8Count;
    u8Count = M0P_WDT->CON_f.WCNTL;
    return u8Count;
}
/**
 ******************************************************************************
 ** \brief  WDT读取当前运行状态
 **
 ** \param [in] 无
 **
 ** \retval 状态值
 **
 ******************************************************************************/
uint8_t Wdt_ReadwdtStatus(void)
{
    return M0P_WDT->CON_f.WDTR;
}
/**
 ******************************************************************************
 ** \brief  WDT中断处理函数
 **
 ** \param [in] 无
 **
 ** \retval 无
 **
 ******************************************************************************/
void Wdt_IRQHandler(void)
{
    if(M0P_WDT->CON_f.WDINT)
    {
        Wdt_Start();//clr wdt 标记
        if(NULL != pfnWdtCallback)
        {
            pfnWdtCallback();
        }
    }
}

//@} // WdtGroup
