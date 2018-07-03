/******************************************************************************
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
/** \file timer2.c
 **
 ** A detailed description is available at
 ** @link Timer2Group Timer2 description @endlink
 **
 **   - 2018-03-15  1.0  HeChun First version for Device Driver Library of
 **                      Timer2.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "timer2.h"

/**
 *******************************************************************************
 ** \addtogroup Timer2Group
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief Timer instance structure definition
 **
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define     IS_VALID_CHANNEL(x)     (Tim2_ChannelA == (x) || \
                                     Tim2_ChannelB == (x))
#define     IS_TIM_LIST_PERIPH(x)   (M4_TMR20 == (x) || \
                                     M4_TMR21 == (x) || \
                                     M4_TMR22 == (x) || \
                                     M4_TMR23 == (x))
#define     IS_TIM_COUNTER_MODE(x)  (Tim2_Sync == (x) || \
                                     Tim2_Async == (x))
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/


/**
 ******************************************************************************
 ** \brief Tim2_GetFlag
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 **
 ** \retval     Set                The state register had be set
 **             Reset              The state register had be reset
 **
 *****************************************************************************/
en_flag_status_t Tim2_GetFlag(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh)
{
    en_flag_status_t enFlag;
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    switch(enCh)

    {
        case Tim2_ChannelA:
            if(TRUE == stcTimx->STFLR_f.CMAF)
            {
                enFlag = Set;
            }
            else
            {
                enFlag = Reset;
            }
            break;
        case Tim2_ChannelB:
            if(TRUE == stcTimx->STFLR_f.CMBF)
            {
                enFlag = Set;
            }
            else
            {
                enFlag = Reset;
            }
            break;
        default:
            break;
    }
    return enFlag;
}

/**
 ******************************************************************************
 ** \brief TIM2_ClearFlag
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 **
 ** \retval     None
 **
 *****************************************************************************/
void TIM2_ClearFlag(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    if(Tim2_ChannelA == enCh)
    {
        stcTimx->STFLR_f.CMAF = 0x00;
    }
    else if(Tim2_ChannelB == enCh)
    {
        stcTimx->STFLR_f.CMBF = 0x00;
    }
}

/**
 ******************************************************************************
 ** \brief Tim2_Cmd
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 ** \param [in] enCmd              ENABLE start timer
 **                                DISABLE stop timer
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim2_Cmd(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh,
                en_functional_state_t enCmd)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    switch (enCh)
    {
        case Tim2_ChannelA:
            /*start channelA counter*/
            stcTimx->BCONR_f.CSTA = enCmd;
            break;
        case Tim2_ChannelB:
            /*start channelB counter*/
            stcTimx->BCONR_f.CSTB = enCmd;
            break;
        default:
            break;
    }
}

/**
 ******************************************************************************
 ** \brief Tim2_ITConfig
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 ** \param [in] enCmd              ENABLE timer interrupt
 **                                DISABLE timer interrupt
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim2_ITConfig(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh,
                       en_functional_state_t enCmd)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    switch (enCh)
    {
        case Tim2_ChannelA:
            stcTimx->ICONR_f.INTENA = enCmd;
            break;
        case Tim2_ChannelB:
            stcTimx->ICONR_f.INTENB = enCmd;
            break;
        default:
            break;
    }
}

/**
 ******************************************************************************
 ** \brief Tim2_SetFunc
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 ** \param [in] enFunc             set Tim2_OutputCapare mode
 **                                or Tim2_InputCaptrue mode
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim2_SetFunc(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh,
                       en_tim2_function_t enFunc)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));
    
    switch (enCh)
    {
        case Tim2_ChannelA:
            stcTimx->PCONR_f.CAPMDA = enFunc;
            break;
        case Tim2_ChannelB:
            stcTimx->PCONR_f.CAPMDB = enFunc;
            break;
        default:
            break;
    }
}
/**
 ******************************************************************************
 ** \brief Tim2_GetCntCounter
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 **
 ** \retval                        Return the value of counter
 **
 *****************************************************************************/
uint16_t Tim2_GetCntCounter(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh)
{
    uint16_t u16Value = 0;
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    if(enCh == Tim2_ChannelA)
    {
        u16Value = stcTimx->CNTAR&0xFFFF;
    }
    else if(enCh == Tim2_ChannelB)
    {
        u16Value = stcTimx->CNTBR&0xFFFF;
    }
    return u16Value;
}

/**
 ******************************************************************************
 ** \brief Tim2_GetCmpCounter
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 **
 ** \retval                        Return the value of cmp counter
 **
 *****************************************************************************/
uint16_t Tim2_GetCmpCounter(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh)
{
    uint16_t u16Value = 0;
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    if(enCh == Tim2_ChannelA)
    {
        u16Value = stcTimx->CMPAR&0xFFFF;
    }
    else if(enCh == Tim2_ChannelB)
    {
        u16Value = stcTimx->CMPBR&0xFFFF;
    }
    return u16Value;
}

/**
 ******************************************************************************
 ** \brief Tim2_SetCmpCounter
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 ** \param [in] u16Counter         Specifies the Counter register new
 **                                value
 **
 ** \retval                        Return the value of cmp counter
 **
 *****************************************************************************/

void Tim2_SetCmpCounter(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,uint16_t u16Counter)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));


    if(enCh == Tim2_ChannelA)
    {
        stcTimx->CMPAR = u16Counter&0xFFFF;
    }
    else if(enCh == Tim2_ChannelB)
    {
        stcTimx->CMPBR = u16Counter&0xFFFF;
    }
}


/**
 ******************************************************************************
 ** \brief Tim2_BaseInit
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 ** \param [in] stcBaseInit        This is base timer function parameter
 **                                structure
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim2_BaseInit(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,
                       stc_tim2_base_init_t* stcBaseInit)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));
    DDL_ASSERT(IS_TIM_COUNTER_MODE(stcBaseInit->Tim2_CounterMode));

    switch(enCh)
    {
        /*set channal A*/
        case Tim2_ChannelA:
            /*set counter mode is Sync or Async*/
            stcTimx->BCONR_f.SYNSA = stcBaseInit->Tim2_CounterMode;
            /*set sync or async clock source*/
            switch(stcBaseInit->Tim2_CounterMode)
            {
                case Tim2_Sync:
                    stcTimx->BCONR_f.SYNSCLKA = stcBaseInit->Tim2_SyncClockSource;
                    break;
                case Tim2_Async:
                    stcTimx->BCONR_f.ASYNSCLKA = stcBaseInit->Tim2_AsyncClockSource;
                    break;
                default:
                    break;
            }
            /*set clock division*/
            stcTimx->BCONR_f.CKDIVA = stcBaseInit->Tim2_ClockDivision;
            /*set compare value*/
            stcTimx->CMPAR = stcBaseInit->Tim2_CmpValue;
            break;
        /*set channal B*/
        case Tim2_ChannelB:
            /*set counter mode is Sync or Async*/
            stcTimx->BCONR_f.SYNSB = stcBaseInit->Tim2_CounterMode;
            /*set sync or async clock source*/
            switch(stcBaseInit->Tim2_CounterMode)
            {
                case Tim2_Sync:
                    stcTimx->BCONR_f.SYNSCLKB = stcBaseInit->Tim2_SyncClockSource;
                    break;
                case Tim2_Async:
                    stcTimx->BCONR_f.ASYNSCLKB = stcBaseInit->Tim2_AsyncClockSource;
                    break;
                default:
                    break;
            }
            /*set clock division*/
            stcTimx->BCONR_f.CKDIVB = stcBaseInit->Tim2_ClockDivision;
            /*set compare value*/
            stcTimx->CMPBR = stcBaseInit->Tim2_CmpValue;
            break;
        default:
            break;
    }
}

/**
 ******************************************************************************
 ** \brief Tim2_HardTriggerInit
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 ** \param [in] StcInit            This is trigger function parameter
 **                                structure
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim2_HardTriggerInit(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,
                                stc_tim2_trigger_init_t* StcInit)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));
    /*Enable peripheral circuit trigger function*/
    //M4_AOS->TMR2_HTSSR_f.TRGSEL = StcInit->Tim2_SelTrigSrc;
    *((volatile unsigned int*)(0x40010820UL)) = StcInit->Tim2_SelTrigSrc;
    switch(enCh)
    {
        case Tim2_ChannelA:
            /*set work on input captrue or output compare*/
            stcTimx->PCONR_f.CAPMDA = StcInit->Tim2_OCMode;
            /*set inside trigger effective*/
            stcTimx->HCONR_f.HICPA2 = StcInit->Tim2_InTrigEnable;
            /*enable trigger clear counter*/
            stcTimx->HCONR_f.HCLEA2 = StcInit->Tim2_InTrigClear;
            /*enable trigger stop counter*/
            stcTimx->HCONR_f.HSTPA2 = StcInit->Tim2_InTrigStop;
            /*enable trigger start counter*/
            stcTimx->HCONR_f.HSTAA2 = StcInit->Tim2_InTrigStart;
            break;
        case Tim2_ChannelB:
            /*set work on input captrue or output compare*/
            stcTimx->PCONR_f.CAPMDB = StcInit->Tim2_OCMode;
            /*set inside trigger effective*/
            stcTimx->HCONR_f.HICPB2 = StcInit->Tim2_InTrigEnable;
            /*enable trigger clear counter*/
            stcTimx->HCONR_f.HCLEB2 = StcInit->Tim2_InTrigClear;
            /*enable trigger stop counter*/
            stcTimx->HCONR_f.HSTPB2 = StcInit->Tim2_InTrigStop;
            /*enable trigger start counter*/
            stcTimx->HCONR_f.HSTAB2 = StcInit->Tim2_InTrigStart;
            break;
        default:
            break;
    }
}

/**
 ******************************************************************************
 ** \brief Tim2_OCInit
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 ** \param [in] StcInit            This is trigger function parameter
 **                                structure
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim2_OCInit(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,
                    stc_tim2_oc_init_t* stcOCInit)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));
    switch(enCh)
    {
        case Tim2_ChannelA:
            stcTimx->PCONR_f.CAPMDA = stcOCInit->Tim2_OCMode;
            /*set port out polarity while counter is equal to compare value */
            stcTimx->PCONR_f.CMPCA = stcOCInit->Tim2_CMPCStat;
            if(stcOCInit->Tim2_OutEnable == Enable)
            {
                stcTimx->PCONR_f.OUTENA = Enable;
            }
            else
            {
                stcTimx->PCONR_f.OUTENA = Disable;
            }
            /*counter start and stop polarity is determined by STACA register
              and STPCA register*/
            if(FALSE == stcOCInit->Tim2_StaStpStatSel)
            {
                stcTimx->PCONR_f.STASTPSA = FALSE;
                /*set port out polarity start counter*/
                stcTimx->PCONR_f.STACA = stcOCInit->Tim2_StartStat;
                /*set port out polarity stop counter*/
                stcTimx->PCONR_f.STPCA = stcOCInit->Tim2_StopStat;
            }
            else
            {
                /*counter start and stop polarity Keep the original level*/
                stcTimx->PCONR_f.STASTPSA = TRUE;
            }
            break;
        case Tim2_ChannelB:
            stcTimx->PCONR_f.CAPMDB = stcOCInit->Tim2_OCMode;
            /*set port out polarity while counter is equal to compare value */
            stcTimx->PCONR_f.CMPCB = stcOCInit->Tim2_CMPCStat;
            if(stcOCInit->Tim2_OutEnable == Enable)
            {
                stcTimx->PCONR_f.OUTENB = Enable;
            }
            else
            {
                stcTimx->PCONR_f.OUTENB = Disable;
            }
            /*counter start and stop polarity is determined by STACA register
              and STPCA register*/
            if(FALSE == stcOCInit->Tim2_StaStpStatSel)
            {
                stcTimx->PCONR_f.STASTPSB = FALSE;
                /*set port out polarity start counter*/
                stcTimx->PCONR_f.STACB = stcOCInit->Tim2_StartStat;
                /*set port out polarity stop counter*/
                stcTimx->PCONR_f.STPCB = stcOCInit->Tim2_StopStat;
            }
            else
            {
                /*counter start and stop polarity Keep the original level*/
                stcTimx->PCONR_f.STASTPSB = TRUE;
            }
            break;
        default:
            break;
    }
}

/**
 ******************************************************************************
 ** \brief Tim2_ICInit
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim2_channel_t
 ** \param [in] StcInit            This is trigger function parameter
 **                                structure
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim2_ICInit(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,
                    stc_tim2_ic_init_t* stcICInit)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    switch(enCh)
    {
        case Tim2_ChannelA:
            /*set work mode is compare output or input captrue*/
            stcTimx->PCONR_f.CAPMDA = stcICInit->Tim2_OCMode;
            /*set input filter*/
            if(stcICInit->Tim2_FilterEnable == TRUE)
            {
                stcTimx->PCONR_f.NOFIENA = TRUE;
                stcTimx->PCONR_f.NOFICKA = stcICInit->Tim2_FilterClkDiv;
            }
            else
            {
                stcTimx->PCONR_f.NOFIENA = FALSE;
            }
            /*set fall edge and rise edge trigger effective*/
            stcTimx->HCONR_f.HICPA1 = stcICInit->Tim2_PortTrigFallValid;
            stcTimx->HCONR_f.HICPA0 = stcICInit->Tim2_PortTrigRiseValid;
            /*set fall edge and rise edge  clean counter*/
            stcTimx->HCONR_f.HCLEA1 = stcICInit->Tim2_PortTrigFallClean;
            stcTimx->HCONR_f.HCLEA0 = stcICInit->Tim2_PortTrigRiseClean;
            /*set fall edge and rise edge stop counter*/
            stcTimx->HCONR_f.HSTPA1 = stcICInit->Tim2_PortTrigFallStop;
            stcTimx->HCONR_f.HSTPA0 = stcICInit->Tim2_PortTrigRiseStop;
            /*set fall edge and rise edge start counter*/
            stcTimx->HCONR_f.HSTAA1 = stcICInit->Tim2_PortTrigFallStart;
            stcTimx->HCONR_f.HSTAA0 = stcICInit->Tim2_PortTrigRiseStart;
            break;
        case Tim2_ChannelB:
            stcTimx->PCONR_f.CAPMDB = stcICInit->Tim2_OCMode;
            /*set input filter*/
            if(stcICInit->Tim2_FilterEnable == TRUE)
            {
                stcTimx->PCONR_f.NOFIENB = TRUE;
                stcTimx->PCONR_f.NOFICKB = stcICInit->Tim2_FilterClkDiv;
            }
            else
            {
                stcTimx->PCONR_f.NOFIENB = FALSE;
            }
            /*set fall edge or rise edge trigger effective*/
            stcTimx->HCONR_f.HICPB1 = stcICInit->Tim2_PortTrigFallValid;
            stcTimx->HCONR_f.HICPB0 = stcICInit->Tim2_PortTrigRiseValid;
            /*set fall edge or rise edge clean counter*/
            stcTimx->HCONR_f.HCLEB1 = stcICInit->Tim2_PortTrigFallClean;
            stcTimx->HCONR_f.HCLEB0 = stcICInit->Tim2_PortTrigRiseClean;
            /*set fall edge or rise edge stop counter*/
            stcTimx->HCONR_f.HSTPB1 = stcICInit->Tim2_PortTrigFallStop;
            stcTimx->HCONR_f.HSTPB0 = stcICInit->Tim2_PortTrigRiseStop;
            /*set fall edge or rise edge start counter*/
            stcTimx->HCONR_f.HSTAB1 = stcICInit->Tim2_PortTrigFallStart;
            stcTimx->HCONR_f.HSTAB0 = stcICInit->Tim2_PortTrigRiseStart;
            break;
        default:
            break;
    }
}
//@} // Timer2Group

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
