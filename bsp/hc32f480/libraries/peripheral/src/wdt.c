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
/** \file wdt.c
 **
 ** A detailed description is available at
 ** @link WdtGroup Wdt description @endlink
 **
 **   - 2017-03-13  1.0  yangjp First version for Device Driver Library of Wdt.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "wdt.h"

/**
 *******************************************************************************
 ** \addtogroup WdtGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*! WDT_RR register refresh key */
#define WDT_REFRESH_KEY_START       ((uint16_t)0x0123)
#define WDT_REFRESH_KEY_END         ((uint16_t)0x3210)

/*! Parameter validity check for clock Division */
#define IS_WDT_CLK_DIV(x)           (((x) == Wdt_Pclk3_Div4)            || \
                                     ((x) == Wdt_Pclk3_Div64)           || \
                                     ((x) == Wdt_Pclk3_Div128)          || \
                                     ((x) == Wdt_Pclk3_Div256)          || \
                                     ((x) == Wdt_Pclk3_Div512)          || \
                                     ((x) == Wdt_Pclk3_Div1024)         || \
                                     ((x) == Wdt_Pclk3_Div2048)         || \
                                     ((x) == Wdt_Pclk3_Div8192))
                                    
/*! Parameter validity check for count cycle */
#define IS_WDT_COUNT_CYCLE(x)       (((x) == Wdt_Count_256Cycle)        || \
                                     ((x) == Wdt_Count_4096Cycle)       || \
                                     ((x) == Wdt_Count_16384Cycle)      || \
                                     ((x) == Wdt_Count_65536Cycle))

/*! Parameter validity check for allow refresh percent */
#define IS_WDT_REFRESH_PERCENT(x)   (((x) == Wdt_100Pct)                || \
                                     ((x) == Wdt_0To25Pct)              || \
                                     ((x) == Wdt_25To50Pct)             || \
                                     ((x) == Wdt_0To50Pct)              || \
                                     ((x) == Wdt_50To75Pct)             || \
                                     ((x) == Wdt_0To25Pct_50To75Pct)    || \
                                     ((x) == Wdt_25To75Pct)             || \
                                     ((x) == Wdt_0To75Pct)              || \
                                     ((x) == Wdt_75To100Pct)            || \
                                     ((x) == Wdt_0To25Pct_75To100Pct)   || \
                                     ((x) == Wdt_25To50Pct_75To100Pct)  || \
                                     ((x) == Wdt_0To50Pct_75To100Pct)   || \
                                     ((x) == Wdt_0To25Pct_50To100Pct)   || \
                                     ((x) == Wdt_25To100Pct)            || \
                                     ((x) == Wdt_0To100Pct))

/*! Parameter validity check for Event Type */
#define IS_WDT_EVENT_TYPE(x)        (((x) == Wdt_Interrupt_Request)     || \
                                     ((x) == Wdt_Reset_Request))
 
/*! Parameter validity check for Enable Count In Sleep Mode */
#define IS_WDT_SLEEP_COUNT_EN(x)    (((x) == FALSE)                     || \
                                     ((x) == TRUE))

/*! Parameter validity check for interrupt flag type */
#define IS_WDT_IRQ_FLAG(x)          (((x) == Wdt_CountUnderflow_Irq)    || \
                                     ((x) == Wdt_RefreshError_Irq))

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
 *******************************************************************************
 ** \brief   Wdt init
 **
 ** \param   [in]  stcWdtInit    Pointer to a stc_wdt_init_t Structure which
 **                              will be initialized
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Wdt_Init(stc_wdt_init_t *stcWdtInit)
{
    uint32_t tmpreg;

    /* Check the parameters */
    DDL_ASSERT(IS_WDT_CLK_DIV(stcWdtInit->enDiv));
    DDL_ASSERT(IS_WDT_COUNT_CYCLE(stcWdtInit->enCycle));
    DDL_ASSERT(IS_WDT_REFRESH_PERCENT(stcWdtInit->enRefreshPct));
    DDL_ASSERT(IS_WDT_EVENT_TYPE(stcWdtInit->enEventType));
    DDL_ASSERT(IS_WDT_SLEEP_COUNT_EN(stcWdtInit->bSleepCountEn));

    /* software start mode */
    tmpreg = ((((uint32_t)stcWdtInit->enEventType) << 31)   | \
              (((uint32_t)stcWdtInit->bSleepCountEn) << 16) | \
              (((uint32_t)stcWdtInit->enRefreshPct) << 8)   | \
              (((uint32_t)stcWdtInit->enDiv) << 4) | \
              ((uint32_t)stcWdtInit->enCycle));
    /* store the new value */
    M4_WDT->CR = tmpreg;
}

/**
 *******************************************************************************
 ** \brief   Wdt refresh counter
 **
 ** \param   none
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Wdt_RefreshCounter(void)
{
    M4_WDT->RR = WDT_REFRESH_KEY_START;
    M4_WDT->RR = WDT_REFRESH_KEY_END;
}


/**
 *******************************************************************************
 ** \brief   Wdt gets the current count value
 **
 ** \param   none
 **                                   
 ** \retval  [out]  current count value
 **
 ******************************************************************************/
uint16_t Wdt_GetCountValue(void)
{
    return ((uint16_t)M4_WDT->SR);
}

/**
 *******************************************************************************
 ** \brief   Wdt get interrupt flags
 **
 ** \param   none
 **                                   
 ** \retval  [out]  status register all interrupt flags
 **
 ******************************************************************************/
uint8_t Wdt_GetIrqFlag(void)
{
    return ((uint8_t)(((M4_WDT->SR)>>16) & 0x03));
}

/**
 *******************************************************************************
 ** \brief   Wdt clear interrupt flags
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be 
 **                                   any value of @ref en_port_t
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Wdt_ClearIrqFlag(en_wdt_irq_flag_t irqFlag)
{
    /* Check the parameter */
    DDL_ASSERT(IS_WDT_IRQ_FLAG(irqFlag));

    /* clear the status */
    switch (irqFlag)
    {
        case Wdt_CountUnderflow_Irq:
            M4_WDT->SR_f.UDF = 0u;
            break;
        case Wdt_RefreshError_Irq:
            M4_WDT->SR_f.REF = 0u;
            break;
        default:
            break;
    }
}


//@} // WdtGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
