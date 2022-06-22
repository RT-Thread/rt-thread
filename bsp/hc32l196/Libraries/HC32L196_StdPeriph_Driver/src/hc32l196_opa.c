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
/** \file opa.c
 **
 ** opa driver API.
 ** @link opa Group Some description @endlink
 **
 **   - 2019-04-11       First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_opa.h"

/**
 ******************************************************************************
 ** \addtogroup OPAGroup
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
    ** \brief  OPA 通道使能
    **
    ** \param  NewStatus : TRUE FALSE    
    ** \retval 无
    **
******************************************************************************/
void Opa_Cmd(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_OPA->CR0)), 0, NewStatus);
}

void Opa_CmdBuf(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_OPA->CR0)), 2, NewStatus);
}

/**
******************************************************************************
    ** \brief  OPA零点校准配置
    **
    ** \param  InitZero :  
    ** \retval 无
    **
******************************************************************************/
void Opa_SetZero(stc_opa_zcfg_t* InitZero)
{
    M0P_OPA->CR0_f.AZEN       = InitZero->bAzen;
    M0P_OPA->CR1_f.CLK_SW_SET = InitZero->bClk_sw_set;
    M0P_OPA->CR1_f.AZ_PULSE   = InitZero->bAz_pulse;
    M0P_OPA->CR1_f.TRIGGER    = InitZero->bTrigger;
    M0P_OPA->CR1_f.ADCTR_EN   = InitZero->bAdctr_en; 
}

/**
******************************************************************************
    ** \brief  使能输出OUTX
    **
    ** \param  onex : en_opa_oenx_t定义的元素
    ** \retval 无
    **
******************************************************************************/
void Opa_CmdOnex(en_opa_oenx_t onex, boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_OPA->CR0)), onex, NewState);  //使能OP3输出X使能
}

/**
******************************************************************************
    ** \brief  配置校零相关的位
    **
    ** \param  CtrlBit : en_opa_set0ctrl_t定义的元素
    ** \param  NewState: TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Opa_ZeroBitCtrl(en_opa_set0ctrl_t CtrlBit, boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_OPA->CR1)), CtrlBit, NewState);  
}
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

