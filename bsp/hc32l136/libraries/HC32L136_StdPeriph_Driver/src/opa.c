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
/** \file opa.c
 **
 ** opa driver API.
 ** @link opa Group Some description @endlink
 **
 **   - 2018-04-15   Devi    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "opa.h"

/**
 ******************************************************************************
 ** \addtogroup OPAGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define IS_VALID_pagagain(x)     ( (x) <= 7 )

#define IS_VALID_channel(x)      (  (OPA0 == (x)) ||\
                                    (OPA1 == (x)) ||\
                                    (OPA2 == (x)) )

#define IS_VALID_Mode(x)         (   (OpaUintMode == (x)) ||\
                                     (OpaForWardMode == (x)) ||\
                                     (OpaOppositeMode == (x)) ||\
                                     (OpaThreeOppMode == (x)) ||\
                                     (OpaThreeForMode == (x)) ||\
                                     (OpaDiffMode == (x)) ||\
                                     (OpaMeterMode == (x)) ||\
                                     (OpaGpMode == (x)) )

#define IS_VALID_metergain(x)      (  (OpaMeterGain3   == (x)) ||\
                                      (OpaMeterGain1_3 == (x)) ||\
                                      (OpaMeterGain1   == (x)) )

#define IS_VALID_calsel(x)         (  (OpaSoftMode   == (x)) ||\
                                      (OpaSoftTriggerMode == (x)) ||\
                                      (OpaADCTriggerMode   == (x)) )

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
 *          OPA 初始化
 *
 * \param   无
 * \param   无
 *
 * \retval  无
 * \retval  无
 */
en_result_t OPA_Init(void)
{
	 uint16_t i;
	
	 M0P_SYSCTRL->PERI_CLKEN_f.ADC = 1; 
	 M0P_BGR->CR_f.BGR_EN = 1;
   for(i=0;i<2000;i++)
   {
      ;	
   }
   
   M0P_OPA->CR0 = 0x120;
   M0P_OPA->CR1 = 0x120;
	 M0P_OPA->CR2 = 0x120;
   M0P_OPA->CR = 0x00;
   return Ok;
}

/**
 * \brief   
 *          OPA 去初始化
 *
 * \param   无
 * \param   无
 *
 * \retval  无
 * \retval  无
 */
en_result_t OPA_DeInit(void)
{
   
   M0P_OPA->CR0 = 0x120;
   M0P_OPA->CR1 = 0x120;
	 M0P_OPA->CR2 = 0x120;
   M0P_OPA->CR = 0x00;
   M0P_BGR->CR_f.BGR_EN = 0;
   M0P_SYSCTRL->PERI_CLKEN_f.ADC = 0; 
   return Ok;
}

/**
 * \brief   
 *          OPA 基本功能设置
 *
 * \param   [in]  en_opa_channel_t  使用那个通道的OPA
 * \param   [in]  en_opa_modesel_t  OPA模式选择
  * \param  [in]  stc_opa_gain_config_t  OPA增益选择
 *
 * \retval  无
 */
en_result_t OPA_Operate(en_opa_channel_t enchannel ,en_opa_modesel_t enMode,stc_opa_gain_config_t *pstrGain)
{
    stc_opa_cr0_field_t *stcOpacr;
    
    ASSERT( IS_VALID_Mode(enMode) );
    ASSERT( IS_VALID_channel(enchannel) );

    if (OPA0 == enchannel)
    {
        stcOpacr = (stc_opa_cr0_field_t*)&M0P_OPA->CR0_f;
    }
    if (OPA1 == enchannel)
    {
        stcOpacr = (stc_opa_cr0_field_t*)&M0P_OPA->CR1_f;
    }
    if (OPA2 == enchannel)
    {
        stcOpacr = (stc_opa_cr0_field_t*)&M0P_OPA->CR2_f;
    }
 
    if(enMode == OpaUintMode)
    {
      	stcOpacr->NEGSEL = 0;
			  stcOpacr->POSSEL = 3;
      	stcOpacr->UBUFSEL = 1; 
        stcOpacr->POEN = 1;			
    }
    else if(enMode == OpaForWardMode)
    {
        stcOpacr->NEGSEL = 1;
	      stcOpacr->POEN = 1;
	      stcOpacr->PGAGAIN = pstrGain->enNoInGain;
	      stcOpacr->POSSEL = 3;
	      stcOpacr->RESINMUX = 0;
	      stcOpacr->RESSEL = 1;        	
    }    
    else if(enMode == OpaOppositeMode)
    {
         stcOpacr->NEGSEL = 1;
	       stcOpacr->POEN = 1;
	       stcOpacr->PGAGAIN = pstrGain->enInGain;
	       stcOpacr->POSSEL = 3;
	       stcOpacr->RESINMUX = 2;
	       stcOpacr->RESSEL = 1;    	
    }    
    else if(enMode == OpaDiffMode) 
    {
          M0P_OPA->CR0_f.POSSEL = 3;	
        	M0P_OPA->CR1_f.POSSEL = 3;	
        	M0P_OPA->CR2_f.POSSEL = 0;
          
        	M0P_OPA->CR0_f.NEGSEL = 0;
          M0P_OPA->CR1_f.NEGSEL = 1;
          M0P_OPA->CR2_f.NEGSEL = 1;
        
        	M0P_OPA->CR0_f.RESINMUX = 0;
        	M0P_OPA->CR1_f.RESINMUX = 1;
        	M0P_OPA->CR2_f.RESINMUX = 0;
        	
        	M0P_OPA->CR0_f.UBUFSEL = 1; 	
        	M0P_OPA->CR1_f.UBUFSEL = 0; 	
        	M0P_OPA->CR2_f.UBUFSEL = 0; 
        
        	M0P_OPA->CR0_f.RESSEL = 0; 
        	M0P_OPA->CR1_f.RESSEL = 1; 	
        	M0P_OPA->CR2_f.RESSEL = 0; 
        
        	M0P_OPA->CR0_f.POEN = 0;
        	M0P_OPA->CR1_f.POEN = 1;
        	M0P_OPA->CR2_f.POEN = 0;
        	
        	M0P_OPA->CR0_f.PGAGAIN = 0;
          M0P_OPA->CR1_f.PGAGAIN = pstrGain->enNoInGain;  
          M0P_OPA->CR2_f.PGAGAIN = 0;    
    }
    else if(enMode == OpaGpMode)
    {      
	        stcOpacr->BIASSEL = 1;
          stcOpacr->MODE = 1;	
          stcOpacr->NEGSEL = 3;
	        stcOpacr->POEN = 0;
	        stcOpacr->PGAGAIN = 5;
	        stcOpacr->POSSEL = 3;
	        stcOpacr->RESINMUX = 0;
	        stcOpacr->RESSEL = 0;     
	        stcOpacr->UBUFSEL = 0;    
    }     
    else 
    {
    	return ErrorInvalidParameter;     
    } 
 	 M0P_OPA->CR0_f.EN = 1;  
 	 M0P_OPA->CR1_f.EN = 1;
 	 M0P_OPA->CR2_f.EN = 1;  
   return Ok;   
}

/**
 * \brief   
 *          OPA 基本功能设置  (级联正向和反向模式以及仪表模式)
 * \param   [in]  en_opa_modesel_t  OPA模式选择
  * \param  [in]  stc_opa_gain_config_t  OPA增益选择
 *
 * \retval  无
 */
en_result_t OPA_ThreeOperate(en_opa_modesel_t enMode,stc_opa_gain_config_t *pstrGain0,stc_opa_gain_config_t *pstrGain1,stc_opa_gain_config_t *pstrGain2)
{
    
    ASSERT( IS_VALID_Mode(enMode) );

    if(enMode == OpaThreeOppMode)
    {
	     M0P_OPA->CR0_f.POSSEL = 3;	
	     M0P_OPA->CR1_f.POSSEL = 3;	
	     M0P_OPA->CR2_f.POSSEL = 3;
       
	     M0P_OPA->CR0_f.NEGSEL = 1;
       M0P_OPA->CR1_f.NEGSEL = 1;
       M0P_OPA->CR2_f.NEGSEL = 1;
       
	     M0P_OPA->CR0_f.RESINMUX = 2;
	     M0P_OPA->CR1_f.RESINMUX = 1;
	     M0P_OPA->CR2_f.RESINMUX = 1;
       
	     M0P_OPA->CR0_f.RESSEL = 1; 
	     M0P_OPA->CR1_f.RESSEL = 1; 	
	     M0P_OPA->CR2_f.RESSEL = 1; 
       
	     M0P_OPA->CR0_f.POEN = 0;
	     M0P_OPA->CR1_f.POEN = 0;
	     M0P_OPA->CR2_f.POEN = 1;
	     
	     M0P_OPA->CR0_f.PGAGAIN = pstrGain0->enInGain;
       M0P_OPA->CR1_f.PGAGAIN = pstrGain1->enInGain;
       M0P_OPA->CR2_f.PGAGAIN = pstrGain2->enInGain;           	
    }
    else if(enMode == OpaThreeForMode)
    {
	     M0P_OPA->CR0_f.POSSEL = 3;	
	     M0P_OPA->CR1_f.POSSEL = 2;	
	     M0P_OPA->CR2_f.POSSEL = 2;
       
	     M0P_OPA->CR0_f.NEGSEL = 1;
       M0P_OPA->CR1_f.NEGSEL = 1;
       M0P_OPA->CR2_f.NEGSEL = 1;
       
	     M0P_OPA->CR0_f.RESINMUX = 0;
	     M0P_OPA->CR1_f.RESINMUX = 0;
	     M0P_OPA->CR2_f.RESINMUX = 0;
	     
	     M0P_OPA->CR0_f.UBUFSEL = 0; 	
	     M0P_OPA->CR1_f.UBUFSEL = 0; 	
	     M0P_OPA->CR2_f.UBUFSEL = 0; 
       
	     M0P_OPA->CR0_f.RESSEL = 1; 
	     M0P_OPA->CR1_f.RESSEL = 1; 	
	     M0P_OPA->CR2_f.RESSEL = 1; 
       
	     M0P_OPA->CR0_f.POEN = 0;
	     M0P_OPA->CR1_f.POEN = 0;
	     M0P_OPA->CR2_f.POEN = 1;
	     
	     M0P_OPA->CR0_f.PGAGAIN = pstrGain0->enNoInGain;
       M0P_OPA->CR1_f.PGAGAIN = pstrGain1->enNoInGain;
       M0P_OPA->CR2_f.PGAGAIN = pstrGain2->enNoInGain;      	
    }       
    else 
    {
    	return ErrorInvalidParameter;     
    } 
 	 M0P_OPA->CR0_f.EN = 1;  
 	 M0P_OPA->CR1_f.EN = 1;
 	 M0P_OPA->CR2_f.EN = 1;  
   return Ok; 
}

/**
 * \brief   
 *          OPA 仪表模式
  * \param  [in]  en_opa_metergain_t  OPA增益选择
 *
 * \retval  无
 */
en_result_t OPA_MeterOperate(en_opa_metergain_t enGainMode)
{
   ASSERT( IS_VALID_metergain(enGainMode) );

  M0P_OPA->CR0_f.POSSEL = 3;	
	M0P_OPA->CR1_f.POSSEL = 3;	
	M0P_OPA->CR2_f.POSSEL = 1;
  
	M0P_OPA->CR0_f.NEGSEL = 0;
  M0P_OPA->CR1_f.NEGSEL = 0;
  M0P_OPA->CR2_f.NEGSEL = 1;

	M0P_OPA->CR0_f.RESINMUX = 0;
	M0P_OPA->CR1_f.RESINMUX = 0;
	M0P_OPA->CR2_f.RESINMUX = 1;
	
	M0P_OPA->CR0_f.UBUFSEL = 1; 	
	M0P_OPA->CR1_f.UBUFSEL = 1; 	
	M0P_OPA->CR2_f.UBUFSEL = 0; 

	M0P_OPA->CR0_f.RESSEL = 1; 
	M0P_OPA->CR1_f.RESSEL = 0; 	
	M0P_OPA->CR2_f.RESSEL = 1; 

	M0P_OPA->CR0_f.POEN = 0;
	M0P_OPA->CR1_f.POEN = 0;
	M0P_OPA->CR2_f.POEN = 1;
	
	if(enGainMode == OpaMeterGain3)
	{
	 M0P_OPA->CR0_f.PGAGAIN = 6;
   M0P_OPA->CR2_f.PGAGAIN = 3;		
	}
	if(enGainMode == OpaMeterGain1_3)
	{
	 M0P_OPA->CR0_f.PGAGAIN = 3;
   M0P_OPA->CR2_f.PGAGAIN = 6;		
	}
	if(enGainMode == OpaMeterGain1)
	{
	 M0P_OPA->CR0_f.PGAGAIN = 5;
   M0P_OPA->CR2_f.PGAGAIN = 5;		
	} 

 	 M0P_OPA->CR0_f.EN = 1;  
 	 M0P_OPA->CR1_f.EN = 1;
 	 M0P_OPA->CR2_f.EN = 1;  
   return Ok; 
}
/**
 * \brief   
 *          OPA 校正模式
  * \param  [in]  en_opa_calsel_t  OPA校正模式选择
 *
 * \retval  无
 */
en_result_t OPA_Cal(en_opa_calsel_t enCalMode)
{
   ASSERT( IS_VALID_calsel(enCalMode) );
	
	if(enCalMode == OpaSoftMode)
	{
	
	}
	if(enCalMode == OpaSoftTriggerMode)
	{
		
	}
	if (enCalMode == OpaADCTriggerMode)
	{
	
	} 

 	 M0P_OPA->CR0_f.EN = 1;  
 	 M0P_OPA->CR1_f.EN = 1;
 	 M0P_OPA->CR2_f.EN = 1;  
   return Ok; 
}
//@} // OPAGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

