/*****************************************************************************
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
/** \file timer2.h
 **
 ** A detailed description is available at
 ** @link Timer2Group Timer2 description @endlink
 **
 **   - 2018-03-09  1.0  HeChun First version for Device Driver Library of
 **                      Timer2.
 **
 ******************************************************************************/

#ifndef __TIMER2_H__
#define __TIMER2_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "base_types.h"
#include "hc32f480.h"
#include "ddl.h"
#include "interrupts_hc32f480.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup Timer2Group General Timer2 (TIMER2)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief Timer2 channel enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim2_ChannelA = 0x00,
    Tim2_ChannelB = 0x01
}en_tim2_channel_t;

/**
 *******************************************************************************
 ** \brief Timer2 Async Mode clock enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim2_LRC       = 0x00,
    Tim2_XTAL32    = 0x01,
    Tim2_Tim2ClkIn = 0x02
}en_tim2_async_clock_src_t;

/**
 *******************************************************************************
 ** \brief Timer2 Sync Mode clock enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim2_Pclk1          = 0x00,
    Tim2_Tim2ClkRise    = 0x01,
    Tim2_Tim2ClkFall    = 0x02,
    Tim2_InsideHardTrig = 0x03
}en_tim2_sync_clock_src_t;

/**
 *******************************************************************************
 ** \brief Timer2 counter mode enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim2_Sync  = 0x00,
    Tim2_Async = 0x01
}en_tim2_counter_mode_t;

/**
 *******************************************************************************
 ** \brief Timer2 work  mode enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim2_OutputCapare = 0x00,
    Tim2_InputCaptrue = 0x01
}en_tim2_function_t;

/**
 *******************************************************************************
 ** \brief Timer2 clock division enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim2_ClkDiv0 = 0,
    Tim2_ClkDiv2,
    Tim2_ClkDiv4,
    Tim2_ClkDiv8,
    Tim2_ClkDiv16,
    Tim2_ClkDiv32,
    Tim2_ClkDiv64,
    Tim2_ClkDiv128,
    Tim2_ClkDiv256,
    Tim2_ClkDiv512,
    Tim2_ClkDiv1024
}en_tim2_clock_div_t;

/**
 *******************************************************************************
 ** \brief Timer2 input filter clock division enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim2_ClkSrc = 0,
    Tim2_ClkSrcDiv4,
    Tim2_ClkSrcDiv16,
    Tim2_ClkSrcDiv64
}en_filter_clock_div_t;

/**
 *******************************************************************************
 ** \brief Timer2 occur output compare port level enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim2_Low = 0,
    Tim2_High,
    Tim2_Keep,
    Tim2_Negation
}en_tim2_port_stat_t;


/**
 *******************************************************************************
 ** \brief Timer2 inside trigger function init structrue definition
 **
 ******************************************************************************/
typedef struct
{
    en_tim2_function_t  Tim2_OCMode;     /*!<specifies the TIM mode
                                             This This parameter can be a
                                             value of @ref en_tim2_function_t*/
    en_int_src_t        Tim2_SelTrigSrc;/*!<specifies the TIM Clk Src
                                            This This parameter can be a
                                            value of @ref en_int_src_t*/
    boolean_t           Tim2_InTrigEnable;/*!<specifies the TIM enable trigger*/
    boolean_t           Tim2_InTrigClear; /*!<specifies the TIM enable trigger clear*/
    boolean_t           Tim2_InTrigStop;  /*!<specifies the TIM enable trigger stop*/
    boolean_t           Tim2_InTrigStart; /*!<specifies the TIM enable trigger start*/
}stc_tim2_trigger_init_t;

/**
 *******************************************************************************
 ** \brief Timer2 port out compare function init structrue definition
 **
 ******************************************************************************/
typedef struct
{
    en_tim2_function_t    Tim2_OCMode;  /*!<specifies the TIM mode
                                            This This parameter can be a value of
                                            @ref en_tim2_function_t*/
    boolean_t             Tim2_OutEnable;/*!<specifies the TIM enable port out function*/
    boolean_t             Tim2_StaStpStatSel;/*!<specifies the TIM port idle state level*/
    en_tim2_port_stat_t   Tim2_StartStat;/*!<specifies the TIM port start state level
                                             This This parameter only can be a value of
                                             low or high*/
    en_tim2_port_stat_t   Tim2_StopStat; /*!<specifies the TIM port stop state level
                                             This This parameter only can be a value
                                             of low or high*/
    en_tim2_port_stat_t   Tim2_CMPCStat; /*!<specifies the TIM port cmp state level
                                            This This parameter can be a value of
                                            @ref en_tim2_port_stat_t*/
}stc_tim2_oc_init_t;

/**
 *******************************************************************************
 ** \brief Timer2 port input captrue function init structrue definition
 **
 ******************************************************************************/
typedef struct
{
    en_tim2_function_t     Tim2_OCMode;/*!<specifies the TIM mode
                                           This This parameter can be a value of
                                           @ref en_tim2_function_t*/
    boolean_t              Tim2_FilterEnable;/*!<specifies the TIM enable input filter*/
    en_filter_clock_div_t  Tim2_FilterClkDiv;/*!<specifies the TIM set filter clock division*/
    boolean_t              Tim2_PortTrigFallValid;/*!<specifies the TIM enable fall edge trigger*/
    boolean_t              Tim2_PortTrigRiseValid;/*!<specifies the TIM enable rise edge trigger*/
    boolean_t              Tim2_PortTrigRiseClean;/*!<specifies the TIM enable rise edge clear counter*/
    boolean_t              Tim2_PortTrigFallClean;/*!<specifies the TIM enable fall edge clear counter*/
    boolean_t              Tim2_PortTrigRiseStop;/*!<specifies the TIM enable rise edge stop counter*/
    boolean_t              Tim2_PortTrigFallStop;/*!<specifies the TIM enable fall edge stop counter*/
    boolean_t              Tim2_PortTrigRiseStart;/*!<specifies the TIM enable rise edge start counter*/
    boolean_t              Tim2_PortTrigFallStart;/*!<specifies the TIM enable fall edge start counter*/
}stc_tim2_ic_init_t;


/**
 *******************************************************************************
 ** \brief Timer2 base counter function init structrue definition
 **
 ******************************************************************************/
typedef struct
{
    en_tim2_clock_div_t       Tim2_ClockDivision; /*!<specifies the TIM clock division
                                                      This This parameter can be a value of
                                                      @ref en_tim2_clock_div_t*/
    en_tim2_sync_clock_src_t  Tim2_SyncClockSource;/*!<specifies the TIM sync clock source
                                                      This This parameter can be a value of
                                                      @ref en_tim2_sync_clock_src_t*/
    en_tim2_async_clock_src_t Tim2_AsyncClockSource;/*!<specifies the TIM async clock source
                                                      This This parameter can be a value of
                                                      @ref en_tim2_async_clock_src_t*/
    en_tim2_counter_mode_t    Tim2_CounterMode;/*!<specifies the TIM counter mode
                                                   This This parameter can be a value of
                                                   @ref en_tim2_counter_mode_t*/
    uint16_t                  Tim2_CmpValue;/*!<specifies the TIM counter value
                                                This value can be set 0-0xFFFF*/
}stc_tim2_base_init_t;
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
en_flag_status_t Tim2_GetFlag(M4_TMR2_TypeDef* stcTimx,
                                en_tim2_channel_t enCh);
void Tim2_SetFunc(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh,
                       en_tim2_function_t enFunc);
void Tim2_Cmd(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh,
                en_functional_state_t enCmd);
void Tim2_ITConfig(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh,
                     en_functional_state_t enCmd);
uint16_t Tim2_GetCntCounter(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh);
uint16_t Tim2_GetCmpCounter(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh);

void Tim2_BaseInit(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,
                      stc_tim2_base_init_t* stcBaseInit);
void Tim2_HardTriggerInit(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,
                            stc_tim2_trigger_init_t* enStcInit);
void Tim2_OCInit(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,
                   stc_tim2_oc_init_t* stcOCInit);
void Tim2_ICInit(M4_TMR2_TypeDef* stcTimx,en_tim2_channel_t enCh,
                   stc_tim2_ic_init_t* stcICInit);

void TIM2_ClearFlag(M4_TMR2_TypeDef* stcTimx, en_tim2_channel_t enCh);

//@} // Timer2Group

#ifdef __cplusplus
}
#endif

#endif /* __TIMER2_H_ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
