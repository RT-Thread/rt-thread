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

/** \file crc.c
**
** Common API of crc.
** @link crcGroup Some description @endlink
**
**   - 2017-05-16
**
******************************************************************************/

/*******************************************************************************
* Include files
******************************************************************************/
#include "ddl.h"
#include "hdiv.h"
/**
*******************************************************************************
** \addtogroup CrcGroup
******************************************************************************/
//@{

/*******************************************************************************
* Local pre-processor symbols/macros ('#define')
******************************************************************************/

/*******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/

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
* \brief   
*          HDIV 有符号除法
*
* \param   [in]   Dividend      被除数
* \param   [in]   Dividsor      除数
* \param   [out]  stcDivResult  商和余数
*
* \retval  en_result_t  Ok:  配置成功
* \retval  en_result_t  ErrorInvalidParameter: 无效参数
*/
en_result_t Hdiv_Unsigned(uint32_t Dividend,uint16_t Divisor,stc_div_unsigned_result_t* stcDivResult)
{
  M0P_HDIV->SIGN_f.SIGN = 0;
  if(NULL == stcDivResult)
  {
    return ErrorInvalidParameter;
  }
  (M0P_HDIV ->DIVIDEND) = Dividend;
  (M0P_HDIV ->DIVISOR) = Divisor;
  
  if(Hdiv_GetZeroState() == TRUE)
  {
    return ErrorInvalidParameter;
  }
  
  while(Hdiv_GetEndState() != TRUE)
  {
    ;
  }
  
  stcDivResult->Quotient = M0P_HDIV->QUOTIENT_f.QUOTIENT;
  stcDivResult->Remainder = M0P_HDIV ->REMAINDER_f.REMAINDER; 		
  return Ok;
}


/**
* \brief   
*          HDIV 无符号除法
*
* \param   [in]   Dividend      被除数
* \param   [in]   Dividsor      除数
* \param   [out]  stcDivResult  商和余数
*
* \retval  en_result_t  Ok:  配置成功
* \retval  en_result_t  ErrorInvalidParameter: 无效参数
*/
en_result_t Hdiv_Signed(int32_t Dividend,int16_t Divisor,stc_div_signed_result_t* stcDivResult)
{

  __IO uint32_t * pDivdend = &(M0P_HDIV ->DIVIDEND);
  __IO uint32_t * pDivsor = &(M0P_HDIV ->DIVISOR);
  if(NULL == stcDivResult)
  {
    return ErrorInvalidParameter;
  }
  M0P_HDIV->SIGN_f.SIGN = 1;
  *(__IO int32_t *)pDivdend = Dividend;
  *(__IO int16_t *)pDivsor = Divisor;
  
  if(Hdiv_GetZeroState() == TRUE)
  {
    return ErrorInvalidParameter;
  }
  
  while(Hdiv_GetEndState() != TRUE)
  {
    ;
  }
  
  stcDivResult->Quotient = M0P_HDIV->QUOTIENT_f.QUOTIENT;
  stcDivResult->Remainder = M0P_HDIV ->REMAINDER_f.REMAINDER; 		
  return Ok;
}

boolean_t Hdiv_GetEndState(void)
{
  return M0P_HDIV->STAT_f.END;
}

boolean_t Hdiv_GetZeroState(void)
{
  return M0P_HDIV->STAT_f.ZERO;
}
//@} // CrcGroup

/*******************************************************************************
* EOF (not truncated)
******************************************************************************/
