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
/** \file timer0.h
 **
 ** A detailed description is available at
 ** @link Timer0Group Timer0 description @endlink
 **
 **   - 2018-03-09  1.0  HeChun First version for Device Driver Library of Timer0.
 **
 ******************************************************************************/

#ifndef __TIMER0_H__
#define __TIMER0_H__

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
 ** \defgroup Timer0Group General Timer0 (TIMER0)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief Timer0 channel enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim0_ChannelA = 0x00,
    Tim0_ChannelB = 0x01
}en_tim0_channel_t;

/**
 *******************************************************************************
 ** \brief Timer0 Async Mode clock enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim0_LRC    = 0x00,
    Tim0_XTAL32 = 0x01
}en_tim0_async_clock_src_t;

/**
 *******************************************************************************
 ** \brief Timer0 Sync Mode clock enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim0_Pclk1          = 0x00,
    Tim0_InsideHardTrig = 0x01
}en_tim0_sync_clock_src_t;

/**
 *******************************************************************************
 ** \brief Timer0 counter mode enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim0_Sync  = 0x00,
    Tim0_Async = 0x01
}en_tim0_counter_mode_t;

/**
 *******************************************************************************
 ** \brief Timer0 trigger event mode enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim0_OutputCapare = 0x00,
    Tim0_InputCaptrue = 0x01
}en_tim0_function_t;

/**
 *******************************************************************************
 ** \brief Timer0 clock division enumeration
 **
 ******************************************************************************/
typedef enum
{
    Tim0_ClkDiv0 = 0,
    Tim0_ClkDiv2,
    Tim0_ClkDiv4,
    Tim0_ClkDiv8,
    Tim0_ClkDiv16,
    Tim0_ClkDiv32,
    Tim0_ClkDiv64,
    Tim0_ClkDiv128,
    Tim0_ClkDiv256,
    Tim0_ClkDiv512,
    Tim0_ClkDiv1024
}en_tim0_clock_div_t;


/**
 *******************************************************************************
 ** \brief Timer0 trigger function init structrue definition
 **
 ******************************************************************************/
typedef struct
{
    en_tim0_function_t    Tim0_OCMode;/*!<specifies the TIM mode
                                          This This parameter can be a 
                                          value of @ref en_tim0_function_t*/
    en_int_src_t          Tim0_SelTrigSrc;/*!<specifies the TIM Clk Src
                                              This This parameter can be a
                                              value of @ref en_int_src_t*/
    boolean_t             Tim0_InTrigEnable;/*!<specifies the TIM enable trigger*/
    boolean_t             Tim0_InTrigClear; /*!<specifies the TIM enable trigger clear*/
    boolean_t             Tim0_InTrigStop;  /*!<specifies the TIM enable trigger stop*/
    boolean_t             Tim0_InTrigStart; /*!<specifies the TIM enable trigger start*/
}stc_tim0_trigger_init_t;

/**
 *******************************************************************************
 ** \brief Timer0 base counter function init structrue definition
 **
 ******************************************************************************/
typedef struct
{
    en_tim0_clock_div_t       Tim0_ClockDivision; /*!<specifies the TIM clock division
                                                      This This parameter can be a value of 
                                                      @ref en_tim0_clock_div_t*/
    en_tim0_sync_clock_src_t  Tim0_SyncClockSource;/*!<specifies the TIM sync clock source
                                                      This This parameter can be a value of 
                                                      @ref en_tim0_sync_clock_src_t*/
    en_tim0_async_clock_src_t Tim0_AsyncClockSource;/*!<specifies the TIM async clock source
                                                      This This parameter can be a value of 
                                                      @ref en_tim0_async_clock_src_t*/
    en_tim0_counter_mode_t    Tim0_CounterMode;/*!<specifies the TIM counter mode 
                                                   This This parameter can be a value of 
                                                   @ref en_tim0_counter_mode_t*/
    uint16_t                  Tim0_CmpValue;/*!<specifies the TIM counter value
                                                This value can be set 0-0xFFFF*/
}stc_tim0_base_init_t;
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
en_flag_status_t Tim0_GetFlag(M4_TMR0_TypeDef* stcTimx,
                                  en_tim0_channel_t enCh);
void Tim0_Cmd(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh,
                  en_functional_state_t enCmd);
void Tim0_ITConfig(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh,
                       en_functional_state_t enCmd);
uint16_t Tim0_GetCntCounter(M4_TMR0_TypeDef* stcTimx,en_tim0_channel_t enCh);
uint16_t Tim0_GetCmpCounter(M4_TMR0_TypeDef* stcTimx,en_tim0_channel_t enCh);

void Tim0_BaseInit(M4_TMR0_TypeDef* stcTimx,en_tim0_channel_t enCh,
                       stc_tim0_base_init_t* stcBaseInit);
void Tim0_HardTriggerInit(M4_TMR0_TypeDef* stcTimx,en_tim0_channel_t enCh,
                              stc_tim0_trigger_init_t* enStcInit);
void Tim0_ClearFlag(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh);
void Tim0_SetFunc(M4_TMR0_TypeDef* stcTimx, en_tim0_channel_t enCh,
                       en_tim0_function_t enFunc);

//@} // Timer0Group

#ifdef __cplusplus
}
#endif

#endif /* __TIMER0_H_ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
