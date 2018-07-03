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
/** \file timer0.c
 **
 ** A detailed description is available at
 ** @link Timer0Group Timer0 description @endlink
 **
 **   - 2018-03-09  1.0  HeChun First version for Device Driver Library of
 **                      Timer0.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "timer0.h"

/**
 *******************************************************************************
 ** \addtogroup Timer0Group
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
#define     IS_VALID_CHANNEL(x)     (Tim0_ChannelA == (x) || \
                                     Tim0_ChannelB == (x))
#define     IS_TIM_LIST_PERIPH(x)   (M4_TMR00 == (x) || \
                                     M4_TMR01 == (x))
#define     IS_TIM_COUNTER_MODE(x)  (Tim0_Sync == (x) || \
                                     Tim0_Async == (x))
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
 ** \brief Tim0_GetFlag
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 **
 ** \retval     Set                The count value is equal to set value
 **             Reset              The count value is differ to set value
 **
 *****************************************************************************/

en_flag_status_t Tim0_GetFlag(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh)
{
    en_flag_status_t enFlag;
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    switch(enCh)

    {
        case Tim0_ChannelA:
            if(TRUE == stcTimx->STFLR_f.CMAF)
            {
                enFlag = Set;
            }
            else
            {
                enFlag = Reset;
            }
            break;
        case Tim0_ChannelB:
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
 ** \brief Tim0_ClearFlag
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim0_ClearFlag(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    if(Tim0_ChannelA == enCh)
    {
        stcTimx->STFLR_f.CMAF =0x00;
    }
    else if(Tim0_ChannelB == enCh)
    {
        stcTimx->STFLR_f.CMBF = 0x00;
    }
}

/**
 ******************************************************************************
 ** \brief Tim0_Cmd
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 ** \param [in] enCmd              ENABLE start timer
 **                                DISABLE stop timer
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim0_Cmd(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh,
                en_functional_state_t enCmd)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));

    switch (enCh)
    {
        case Tim0_ChannelA:
            stcTimx->BCONR_f.CSTA = enCmd;
            break;
        case Tim0_ChannelB:
            stcTimx->BCONR_f.CSTB = enCmd;
            break;
        default:
            break;
    }
}

/**
 ******************************************************************************
 ** \brief Tim0_SetFunc
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 ** \param [in] enFunc             set Tim0_OutputCapare mode
 **                                or Tim0_InputCaptrue mode
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim0_SetFunc(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh,
                       en_tim0_function_t enFunc)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));
    
    switch (enCh)
    {
        case Tim0_ChannelA:
            stcTimx->BCONR_f.CAPMDA = enFunc;
            break;
        case Tim0_ChannelB:
            stcTimx->BCONR_f.CAPMDB = enFunc;
            break;
        default:
            break;
    }
}
/**
 ******************************************************************************
 ** \brief Tim0_ITConfig
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 ** \param [in] enCmd              ENABLE timer interrupt
 **                                DISABLE timer interrupt
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim0_ITConfig(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh,
                       en_functional_state_t enCmd)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));


    switch (enCh)
    {
        case Tim0_ChannelA:
            stcTimx->BCONR_f.INTENA = enCmd;
            break;
        case Tim0_ChannelB:
            stcTimx->BCONR_f.INTENB = enCmd;
            break;
        default:
            break;
    }
}

/**
 ******************************************************************************
 ** \brief Tim0_GetCntCounter
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 **
 ** \retval                        Return the value of counter
 **
 *****************************************************************************/
uint16_t Tim0_GetCntCounter(M4_TMR0_TypeDef* stcTimx,en_tim0_channel_t enCh)
{
    uint16_t u16Value = 0;
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));


    if(enCh == Tim0_ChannelA)
    {
        u16Value = stcTimx->CNTAR&0xFFFF;
    }
    else if(enCh == Tim0_ChannelB)
    {
        u16Value = stcTimx->CNTBR&0xFFFF;
    }
    return u16Value;
}

/**
 ******************************************************************************
 ** \brief Tim0_GetCmpCounter
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 **
 ** \retval                        Return the value of cmp counter
 **
 *****************************************************************************/
uint16_t Tim0_GetCmpCounter(M4_TMR0_TypeDef* stcTimx,en_tim0_channel_t enCh)
{
    uint16_t u16Value = 0;
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));


    if(enCh == Tim0_ChannelA)
    {
        u16Value = stcTimx->CMPAR&0xFFFF;
    }
    else if(enCh == Tim0_ChannelB)
    {
        u16Value = stcTimx->CMPBR&0xFFFF;
    }
    return u16Value;
}

/**
 ******************************************************************************
 ** \brief Tim0_BaseInit
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 ** \param [in] stcBaseInit        This is base timer function parameter
 **                                structure
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim0_BaseInit(M4_TMR0_TypeDef* stcTimx,en_tim0_channel_t enCh,
                       stc_tim0_base_init_t* stcBaseInit)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));
    DDL_ASSERT(IS_TIM_COUNTER_MODE(stcBaseInit->Tim0_CounterMode));

    switch(enCh)
    {
        case Tim0_ChannelA:
            /*set timer counter mode*/
            stcTimx->BCONR_f.SYNSA = stcBaseInit->Tim0_CounterMode;
            switch(stcBaseInit->Tim0_CounterMode)
            {
                case Tim0_Sync:
                    stcTimx->BCONR_f.SYNCLKA = stcBaseInit->Tim0_SyncClockSource;
                    break;
                case Tim0_Async:
                    stcTimx->BCONR_f.ASYNCLKA = stcBaseInit->Tim0_AsyncClockSource;
                    break;
                default:
                    break;
            }
            /*set clock division*/
            stcTimx->BCONR_f.CKDIVA = stcBaseInit->Tim0_ClockDivision;
            /*set timer compare value*/
            stcTimx->CMPAR = ((stcBaseInit->Tim0_CmpValue)&0xFFFF);
            break;

        case Tim0_ChannelB:
            /*set timer counter mode*/
            stcTimx->BCONR_f.SYNSB = stcBaseInit->Tim0_CounterMode;
            switch(stcBaseInit->Tim0_CounterMode)
            {
                case Tim0_Sync:
                    stcTimx->BCONR_f.SYNCLKB = stcBaseInit->Tim0_SyncClockSource;
                    break;
                case Tim0_Async:
                    stcTimx->BCONR_f.ASYNCLKB = stcBaseInit->Tim0_AsyncClockSource;
                    break;
                default:
                    break;
            }
            /*set clock division*/
            stcTimx->BCONR_f.CKDIVB = stcBaseInit->Tim0_ClockDivision;
            /*set timer compare value*/
            stcTimx->CMPBR = ((stcBaseInit->Tim0_CmpValue)&0xFFFF);
            break;
        default:
            break;
    }
}

/**
 ******************************************************************************
 ** \brief Tim0_HardTriggerInit
 **
 ** \param [in] stcTimx            where x can be 0 to 1 to select the
 **                                TIM peripheral
 ** \param [in] enCh               This parameter can be any value of
 **                                @ref en_tim0_channel_t
 ** \param [in] StcInit            This is trigger function parameter
 **                                structure
 **
 ** \retval     None
 **
 *****************************************************************************/
void Tim0_HardTriggerInit(M4_TMR0_TypeDef* stcTimx,en_tim0_channel_t enCh,
                                stc_tim0_trigger_init_t* StcInit)
{
    DDL_ASSERT(IS_TIM_LIST_PERIPH(stcTimx));
    DDL_ASSERT(IS_VALID_CHANNEL(enCh));
    /*Enable peripheral circuit trigger function*/
    *((volatile unsigned int*)0x4001081C) = StcInit->Tim0_SelTrigSrc;
    switch(enCh)
    {
        case Tim0_ChannelA:
            /*set work on input captrue or output capare*/
            stcTimx->BCONR_f.CAPMDA = StcInit->Tim0_OCMode;
            /*enable input capture*/
            stcTimx->BCONR_f.HICPA = StcInit->Tim0_InTrigEnable;
            /*enable trigger clear counter*/
            stcTimx->BCONR_f.HCLEA = StcInit->Tim0_InTrigClear;
            /*enable trigger start counter*/
            stcTimx->BCONR_f.HSTAA = StcInit->Tim0_InTrigStart;
            /*enable trigger stop counter*/
            stcTimx->BCONR_f.HSTPA = StcInit->Tim0_InTrigStop;
            break;
        case Tim0_ChannelB:
            /*set work on input captrue or output capare*/
            stcTimx->BCONR_f.CAPMDB = StcInit->Tim0_OCMode;
            /*enable input capture*/
            stcTimx->BCONR_f.HICPB = StcInit->Tim0_InTrigEnable;
            /*enable trigger clear counter*/
            stcTimx->BCONR_f.HCLEB = StcInit->Tim0_InTrigClear;
            /*enable trigger start counter*/
            stcTimx->BCONR_f.HSTAB = StcInit->Tim0_InTrigStart;
            /*enable trigger stop counter*/
            stcTimx->BCONR_f.HSTPB = StcInit->Tim0_InTrigStop;
            break;
        default:
            break;
    }
}


//@} // Timer0Group

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
