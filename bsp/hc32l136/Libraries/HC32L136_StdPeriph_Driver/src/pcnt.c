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
/** \file pcnt.c
 **
 ** pcnt driver API.
 ** @link pcnt Group Some description @endlink
 **
 **   - 2018-04-15   Devi    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "pcnt.h"

/**
 ******************************************************************************
 ** \addtogroup PCNTGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define IS_VALID_pagagain(x)     ( (x) <= 7 )

#define IS_VALID_channel(x)      (  (OPA0 == (x)) ||\
                                    (OPA1 == (x)) ||\
                                    (OPA2 == (x)) )

#define IS_VALID_STAT(x)         (   (PCNT_S1E == (x)) ||\
                                     (PCNT_S0E == (x)) ||\
                                     (PCNT_BB == (x)) ||\
                                     (PCNT_FE == (x)) ||\
                                     (PCNT_DIR == (x)) ||\
                                     (PCNT_TO == (x)) ||\
                                     (PCNT_OV == (x)) ||\
                                     (PCNT_UF == (x)) )



/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/


/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static func_ptr_t pfnPcntCallback = NULL; ///< callback function pointer for PCNT Irq
/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

void Pcnt_IRQHandler(void)
{
	if(NULL != pfnPcntCallback)
	{
		pfnPcntCallback();
	}	
}

/**
 * \brief   
 *          PCNT 初始化
 *
 * \param   无
 * \param   无
 *
 * \retval  无
 * \retval  无
 */
en_result_t PCNT_Init(stc_pcnt_config_t*  pstcPcntConfig)
{

	
	  M0P_SYSCTRL->PERI_CLKEN_f.PCNT = 1; 
  
    M0P_PCNT->CR_f.S1P = pstcPcntConfig->bS1Sel; 
    M0P_PCNT->CR_f.S0P = pstcPcntConfig->bS0Sel;
    M0P_PCNT->CR_f.DIR = pstcPcntConfig->u8Direc;   //计数方式
    M0P_PCNT->CR_f.CLKSEL = pstcPcntConfig->u8Clk;
    M0P_PCNT->CR_f.MODE = pstcPcntConfig->u8Mode;
    
    M0P_PCNT->FLT_f.CLKDIV = pstcPcntConfig->u8FLTClk;
    
    if(pstcPcntConfig->bFLTEn)
    {
      if(pstcPcntConfig->u8FLTDep == 0)	
    	{
    	 	M0P_PCNT->FLT_f.DEBTOP = 2;
    	}
    	else
    	{
    		M0P_PCNT->FLT_f.DEBTOP = pstcPcntConfig->u8FLTDep;
    	}
    }
    M0P_PCNT->FLT_f.EN = pstcPcntConfig->bFLTEn;
    
    M0P_PCNT->TOCR_f.TH = pstcPcntConfig->u16TODep;
    M0P_PCNT->TOCR_f.EN = pstcPcntConfig->bTOEn;    
    
    if (TRUE == pstcPcntConfig->bIrqEn)
    {
        M0P_PCNT->IEN = pstcPcntConfig->u8IrqStatus;
        EnableNvic(PCNT_IRQn,IrqLevel3,TRUE);
    }
    else
    {
    	  M0P_PCNT->IEN = 0x00;
        EnableNvic(PCNT_IRQn,IrqLevel3,FALSE);
    }
    if(NULL != pstcPcntConfig->pfnIrqCb)
    {
        pfnPcntCallback = pstcPcntConfig->pfnIrqCb;
    }
   return Ok;
}

/**
 * \brief   
 *          PCNT 去初始化
 *
 * \param   无
 * \param   无
 *
 * \retval  无
 * \retval  无
 */
void PCNT_DeInit(void)
{
   M0P_PCNT->CR = 0;
   M0P_PCNT->RUN = 0;
   M0P_SYSCTRL->PERI_CLKEN_f.PCNT = 0; 

}

/**
 * \brief   
 *          PCNT 脉冲计数设置
 *
 * \param   [in]  start  开始计数设置
 * \param   [in]  end    结束计数设置
 *
 * \retval  无
 */
en_result_t PCNT_Parameter(uint8_t start,uint8_t end)
{
  uint32_t u32TimeOut;
    
   u32TimeOut = 1000;
   M0P_PCNT->BUF = end;     //加载结束溢出值
	 M0P_PCNT->CMD_f.B2T = 1;
	
	  while(u32TimeOut--)
    {
        if(FALSE == M0P_PCNT->SR2_f.B2T)
        {
            break;
        }
    }
    if(u32TimeOut == 0)
    {
        return ErrorTimeout;
    }

   u32TimeOut = 1000;
   M0P_PCNT->BUF = start;     //加载初始值
	 M0P_PCNT->CMD_f.B2C = 1;
	
	  while(u32TimeOut--)
    {
        if(FALSE == M0P_PCNT->SR2_f.B2C)
        {
            break;
        }
    }
    if(u32TimeOut == 0)
    {
        return ErrorTimeout;
    }
   return Ok;   
}

/**
 * \brief   
 *          获取PCNT计数方向
 * \param   [in]  
 *
 * \retval  无
 */
en_pcnt_direcsel_t PCNT_Direction(void)
{
   return  (en_pcnt_direcsel_t)M0P_PCNT->SR1_f.DIR;
}

/**
 * \brief   
 *          获取PCNT计数值
 * \param   [in]  
 *
 * \retval  无
 */
uint16_t PCNT_Count(void)
{
   return  M0P_PCNT->CNT;
}

/**
 * \brief   
 *          获取PCNT溢出值
 * \param   [in]  
 *
 * \retval  无
 */
uint16_t PCNT_TopCount(void)
{
   return  M0P_PCNT->TOP;
}

/**
 * \brief   
 *          PCNT使能
 * \param   [in]  
 *
 * \retval  无
 */
void PCNT_Run(boolean_t work)
{
   M0P_PCNT->RUN_f.RUN = work; 
}

/**
 * \brief   
 *          PCNT 读取状态
  * \param  [in]  en_pcnt_status_t  PCNT状态
 *
 * \retval  无
 */
boolean_t PCNT_GetStatus(en_pcnt_status_t enStatus)
{
    boolean_t bFlag = FALSE;
    
    ASSERT(IS_VALID_STAT(enStatus));

    switch (enStatus)
    {
        case PCNT_S1E:
            bFlag = M0P_PCNT->IFR_f.S1E;
            break;
        case PCNT_S0E:
            bFlag = M0P_PCNT->IFR_f.S0E;
            break;
        case PCNT_BB:
            bFlag = M0P_PCNT->IFR_f.BB;
            break;
        case PCNT_FE:
            bFlag = M0P_PCNT->IFR_f.FE;
            break;
        case PCNT_DIR:
            bFlag = M0P_PCNT->IFR_f.DIR;
            break;
        case PCNT_TO:
            bFlag = M0P_PCNT->IFR_f.TO;
            break;
        case PCNT_OV:
            bFlag = M0P_PCNT->IFR_f.OV;
            break;
        case PCNT_UF:
            bFlag = M0P_PCNT->IFR_f.UF;
            break;             
        default:
            break;
    }
    return bFlag;
}
/**
 * \brief   
 *          PCNT 清除状态
  * \param  [in]  en_pcnt_status_t  PCNT状态
 *
 * \retval  无
 */
void PCNT_ClrStatus(en_pcnt_status_t enStatus)
{

    ASSERT(IS_VALID_STAT(enStatus));

    switch (enStatus)
    {
        case PCNT_S1E:
            M0P_PCNT->ICR_f.S1E = 0;
            break;
        case PCNT_S0E:
            M0P_PCNT->ICR_f.S0E = 0;
            break;
        case PCNT_BB:
             M0P_PCNT->ICR_f.BB = 0;
            break;
        case PCNT_FE:
            M0P_PCNT->ICR_f.FE = 0;
            break;
        case PCNT_DIR:
            M0P_PCNT->ICR_f.DIR = 0;
            break;
        case PCNT_TO:
            M0P_PCNT->ICR_f.TO = 0;
            break;
        case PCNT_OV:
            M0P_PCNT->ICR_f.OV = 0;
            break;
        case PCNT_UF:
            M0P_PCNT->ICR_f.UF = 0;
            break;             
        default:
            break;
    }
}
/**
 * \brief   
 *          PCNT 中断设置
  * \param  [in]  en_pcnt_status_t  PCNT状态
 *
 * \retval  无
 */
void PCNT_SetIrqStatus(en_pcnt_status_t enStatus)
{

    ASSERT(IS_VALID_STAT(enStatus));

    switch (enStatus)
    {
        case PCNT_S1E:
            M0P_PCNT->IEN_f.S1E = 1;
            break;                
        case PCNT_S0E:            
            M0P_PCNT->IEN_f.S0E = 1;
            break;                
        case PCNT_BB:            
             M0P_PCNT->IEN_f.BB = 1;
            break;                
        case PCNT_FE:             
            M0P_PCNT->IEN_f.FE =  1;
            break;                
        case PCNT_DIR:            
            M0P_PCNT->IEN_f.DIR = 1;
            break;                
        case PCNT_TO:             
            M0P_PCNT->IEN_f.TO =  1;
            break;                
        case PCNT_OV:             
            M0P_PCNT->IEN_f.OV =  1;
            break;                
        case PCNT_UF:             
            M0P_PCNT->IEN_f.UF =  1;
            break;             
        default:
            break;
    }
}
//@} // OPAGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

