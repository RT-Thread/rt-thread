/*******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file exint.c
 **
 ** A detailed description is available at
 ** @link ExintGroup Exint description @endlink
 **
 **   - 2018-03-11  1.0  Zhangxl First version for Device Driver Library of exint
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "exint.h"

/**
 *******************************************************************************
 ** \addtogroup ExintGroup
 ******************************************************************************/
//@{
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_CH(x) (ExtiChMax > (x))
#define IS_NULL_POINT(x) (NULL != (x))

#define IS_VALID_LEVEL(x)               \
(   ExIntLowLevel == (x) ||             \
    ExIntHighLevel == (x) ||            \
    ExIntRisingEdge == (x) ||           \
    ExIntFallingEdge == (x))


/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static func_ptr_t pfnNmiCallback;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief External Int Initilization
 **
 ** \param [in]  stcNmiConfig       EXTI configure structure 
 **
 ** \retval Ok                      EXTI initialized
 **
 ******************************************************************************/
en_result_t Exint_Init(stc_exint_config_t stcExtiConfig)
{
    stc_intc_eirqcr0_field_t *EIRQCRx;

    DDL_ASSERT(IS_VALID_CH(stcExtiConfig.enExitCh));
    EIRQCRx = (stc_intc_eirqcr0_field_t *)((&M4_INTC->EIRQCR0) + (4 * stcExtiConfig.enExitCh));

    /* Set filter function */
    EIRQCRx->EFEN = stcExtiConfig.bFltEn;
    EIRQCRx->EISMPCLK = stcExtiConfig.enFltClk;

    /* Set detection level */
    EIRQCRx->EIRQTRG = stcExtiConfig.enExtiLvl;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief NMI Initilization
 **
 ** \param [in]  stcNmiConfig       NMI configure structure 
 **
 ** \retval Ok                      NMI initialized
 **
 ******************************************************************************/
en_result_t Nmi_Init(stc_nmi_config_t stcNmiConfig)
{
    
    /* Set filter function */
    M4_INTC->NMICR_f.NFEN = stcNmiConfig.bFltEn;
    /* Set filter clock */
    M4_INTC->NMICR_f.NSMPCLK = stcNmiConfig.enFltClk;
    /* Set detection level */
    M4_INTC->NMICR_f.NMITRG = stcNmiConfig.enNmiLvl;
    /* Set NMI source */
    M4_INTC->NMIMR = stcNmiConfig.u16NmiSrc;
    /* NMI callback function  */
    pfnNmiCallback = stcNmiConfig.pfnNmiCallback;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief De-Init Non-Maskable Interrupt (NMI)
 **
 ** This function de-initializes the NMI according to the given
 ** configuration.
 **
 ** \param [in]  pstcConfig        NMI configuration parameters
 ** 
 ** \retval Ok                     NMI De-initialized
 **
 ******************************************************************************/
en_result_t Nmi_DeInit(void)
{
    /* Set internal data */
    pfnNmiCallback = NULL;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief Get NMI Interrupt Flag
 **
 ** \param [in]  uint16_t           NMI Int source, This parameter can be 
 **                                 any value of @ref en_nmi_src_t
 **
 ** \retval None
 **
 ******************************************************************************/
uint16_t Nmi_IrqFlgGet(void)
{
    return (uint16_t)M4_INTC->NMIPR;
}

/**
 *******************************************************************************
 ** \brief Clear NMI Interrupt Flag
 **
 ** \param [in]  u16NmiSrc          NMI Int source, This parameter can be 
 **                                 any value of @ref en_nmi_src_t
 **
 ** \retval Ok                      Interrupt source be cleared 
 **
 ******************************************************************************/
en_result_t Nmi_IrqFlgClr(uint16_t u16NmiSrc)
{
    M4_INTC->NMICPR = u16NmiSrc;
    return Ok;
}

/**
 *******************************************************************************
 ** \brief ISR for NMI
 **
 ** \param [in]  None
 **
 ** \retval None
 **
 ******************************************************************************/
void Nmi_IrqHandler(void)
{
    DDL_ASSERT(IS_NULL_POINT(pfnNmiCallback));
    
    pfnNmiCallback();
}

//@} // ExintGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
