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
/** \file wdt.h
 **
 ** A detailed description is available at
 ** @link WdtGroup Wdt description @endlink
 **
 **   - 2018-03-13  1.0  yangjp First version for Device Driver Library of Wdt.
 **
 ******************************************************************************/

#ifndef __WDT_H__
#define __WDT_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup WdtGroup WatchDot Timer(Wdt)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
  /**
 *******************************************************************************
 ** \brief WDT Refresh Error Or Underflow Triggering Event Type enumeration
 **
 ******************************************************************************/
typedef enum
{
    Wdt_Interrupt_Request = 0x00,  /*!< Interrupt Request  */
    Wdt_Reset_Request     = 0x01,  /*!< Reset Request      */    
}en_wdt_event_type_t;

/**
 *******************************************************************************
 ** \brief Wdt Allow Refresh Percent enumeration
 **
 ******************************************************************************/
typedef enum
{
    Wdt_100Pct              = 0x00,  /*!< 100%               */
    Wdt_0To25Pct            = 0x01,  /*!< 0%~25%             */
    Wdt_25To50Pct           = 0x02,  /*!< 25%~50%            */
    Wdt_0To50Pct            = 0x03,  /*!< 0%~50%             */
    Wdt_50To75Pct           = 0x04,  /*!< 50%~75%            */
    Wdt_0To25Pct_50To75Pct  = 0x05,  /*!< 0%~25% & 50%~75%   */
    Wdt_25To75Pct           = 0x06,  /*!< 25%~75%            */
    Wdt_0To75Pct            = 0x07,  /*!< 0%~75%             */
    Wdt_75To100Pct          = 0x08,  /*!< 75%~100%           */
    Wdt_0To25Pct_75To100Pct = 0x09,  /*!< 0%~25% & 75%~100%  */
    Wdt_25To50Pct_75To100Pct= 0x0A,  /*!< 25%~50% & 75%~100% */
    Wdt_0To50Pct_75To100Pct = 0x0B,  /*!< 0%~50% & 75%~100%  */
    Wdt_50To100Pct          = 0x0C,  /*!< 50%~100%           */
    Wdt_0To25Pct_50To100Pct = 0x0D,  /*!< 0%~25% & 50%~100%  */
    Wdt_25To100Pct          = 0x0E,  /*!< 25%~100%           */
    Wdt_0To100Pct           = 0x0F,  /*!< 0%~100%            */
}en_wdt_refresh_percent_t;

/**
 *******************************************************************************
 ** \brief Wdt Clock Source(PCLK3) Division enumeration
 **
 ******************************************************************************/
typedef enum
{
    Wdt_Pclk3_Div4    = 0x02,  /*!< PCLK3/4     */
    Wdt_Pclk3_Div64   = 0x06,  /*!< PCLK3/64    */
    Wdt_Pclk3_Div128  = 0x07,  /*!< PCLK3/128   */    
    Wdt_Pclk3_Div256  = 0x08,  /*!< PCLK3/256   */
    Wdt_Pclk3_Div512  = 0x09,  /*!< PCLK3/512   */
    Wdt_Pclk3_Div1024 = 0x0A,  /*!< PCLK3/1024  */
    Wdt_Pclk3_Div2048 = 0x0B,  /*!< PCLK3/2048  */
    Wdt_Pclk3_Div8192 = 0x0D,  /*!< PCLK3/8192  */
}en_wdt_clock_div_t;

/**
 *******************************************************************************
 ** \brief Wdt Count Cycles enumeration
 **
 ******************************************************************************/
typedef enum
{
    Wdt_Count_256Cycle   = 0x00,  /*!< 256 Cycle    */
    Wdt_Count_4096Cycle  = 0x01,  /*!< 4096 Cycle   */
    Wdt_Count_16384Cycle = 0x02,  /*!< 16384 Cycle  */
    Wdt_Count_65536Cycle = 0x03,  /*!< 65536 Cycle  */
}en_wdt_count_cycle_t;

/**
 *******************************************************************************
 ** \brief Wdt Interrupt Trigger Source enumeration
 **
 ******************************************************************************/
typedef enum
{
    Wdt_CountUnderflow_Irq = 0x01,  /*!< count underflow interrupt flag  */
    Wdt_RefreshError_Irq   = 0x02,  /*!< refresh error interrupt flag    */
}en_wdt_irq_flag_t;
 
/**
 *******************************************************************************
 ** \brief WDT init structure definition
 **
 ******************************************************************************/
typedef struct
{
    en_wdt_clock_div_t       enDiv;          /*!< Clock Division                         */
    en_wdt_count_cycle_t     enCycle;        /*!< Count Cycle                            */
    en_wdt_refresh_percent_t enRefreshPct;   /*!< Refresh Percent                        */
    en_wdt_event_type_t      enEventType;    /*!< Refresh Error Or Underflow Event Type  */
    boolean_t                bSleepCountEn;  /*!< FALSE: Enable Count In Sleep Mode, \
                                                  TRUE: Disable Count In Sleep Mode */
}stc_wdt_init_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/* Initialization Configuration functions *****************/
void Wdt_Init(stc_wdt_init_t *stcWdtInit);

/* Refresh counter and Get count Value functions ******************************/ 
void Wdt_RefreshCounter(void);
uint16_t Wdt_GetCountValue(void);

/* Interrupts flags management functions **************************************/
uint8_t Wdt_GetIrqFlag(void);
void Wdt_ClearIrqFlag(en_wdt_irq_flag_t irqFlag);

//@} // WdtGroup

#ifdef __cplusplus
}
#endif

#endif /* __WDT_H_ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
