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
/** \file rtc.c
 **
 ** A detailed description is available at
 ** @link RtcGroup Rtc description @endlink
 **
 **   - 2017-03-20  1.0  yangjp First version for Device Driver Library of Rtc.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "rtc.h"

/**
 *******************************************************************************
 ** \addtogroup RtcGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*! Parameter validity check for clock source */
#define IS_RTC_CLOCK_SOURCE(x)      (((x) == Rtc_Clock_Xtal32)          || \
                                     ((x) == Rtc_Clock_Lrc))

/*! Parameter validity check for hour format */
#define IS_RTC_HOUR_FORMAT(x)       (((x) == Rtc_Hour_Format_12)        || \
                                     ((x) == Rtc_Hour_Format_24))

/*! Parameter validity check for Enable rtc function state */
#define IS_RTC_FUNCTION_STATE(x)    (((x) == FALSE)                     || \
                                     ((x) == TRUE))

/*! Parameter validity check for time format */
#define IS_RTC_TIME_FORMAT(x)       (((x) == Rtc_Format_Dec)            || \
                                     ((x) == Rtc_Format_Bcd))

/*! Parameter validity check for time seconds */
#define IS_RTC_TIME_SECONDS(x)      ((x) <= 59)

/*! Parameter validity check for time minutes */
#define IS_RTC_TIME_MINUTES(x)      ((x) <= 59)

/*! Parameter validity check for time hour */
#define IS_RTC_TIME_HOUR12(x)       (((x) >= 1) && ((x) <= 12))
#define IS_RTC_TIME_HOUR24(x)       ((x) <= 23)

/*! Parameter validity check for date weekday */
#define IS_RTC_DATE_WEEKDAY(x)      ((x) <= 6)

/*! Parameter validity check for date day */
#define IS_RTC_DATE_DAY(x)          (((x) >= 1) && ((x) <= 31))

/*! Parameter validity check for date month */
#define IS_RTC_DATE_MONTH(x)        (((x) >= 1) && ((x) <= 12))

/*! Parameter validity check for date year */
#define IS_RTC_DATE_YEAR(x)         ((x) <= 99)

/*! Parameter validity check for hour am/pm */
#define IS_RTC_HOUR_AMPM(x)         (((x) == Rtc_Hour12_AM)             || \
                                     ((x) == Rtc_Hour12_PM))

/*! Parameter validity check for alarm weekday */
#define IS_RTC_ALARM_WEEKDAY(x)     (((x) >= 1) && ((x) <= 0x3F))

/*! Parameter validity check for period interrupt */
#define IS_RTC_PERIOD_INTERRUPT(x)  (((x) == Rtc_Period_Int_Disable)    || \
                                     ((x) == Rtc_Period_Int_OneHalf_Sec)|| \
                                     ((x) == Rtc_Period_Int_One_Sec)    || \
                                     ((x) == Rtc_Period_Int_One_Min)    || \
                                     ((x) == Rtc_Period_Int_One_Hour)   || \
                                     ((x) == Rtc_Period_Int_One_Day)    || \
                                     ((x) == Rtc_Period_Int_One_Mon))

/*! Parameter validity check for output format */
#define IS_RTC_OUTPUT_FORMAT(x)     (((x) == Rtc_Output_Distributed)    || \
                                     ((x) == Rtc_Output_Uniform))

/*! Parameter validity check for clock compensation */
#define IS_RTC_CLOCK_COMPENSATION(x)    ((x) <= 0x1FF)

/*! Parameter validity check for intrusion channel */
#define IS_RTC_INTRUSION_CHANNEL(x) (((x) == Rtc_Intrusion_Ch0)         || \
                                     ((x) == Rtc_Intrusion_Ch1))

/*! Parameter validity check for intrusion valid input edges */
#define IS_RTC_INTRUSION_EDGE(x)    (((x) == Rtc_Intrusion_Edge_Disable)|| \
                                     ((x) == Rtc_Intrusion_Edge_Rising) || \
                                     ((x) == Rtc_Intrusion_Edge_Falling)|| \
                                     ((x) == Rtc_Intrusion_Edge_Rising_Falling))

/*! Parameter validity check for intrusion filter */
#define IS_RTC_INTRUSION_FILTER(x)  (((x) == Rtc_Intrusion_Filter_Disable)  || \
                                     ((x) == Rtc_Intrusion_Filter_Onethird) || \
                                     ((x) == Rtc_Intrusion_Filter_32Div_Onethird))

/*! Parameter validity check for interrupt source */
#define IS_RTC_INTERRUPT_SOURCE(x)  (((x) == Rtc_Int_Compensation)      || \
                                     ((x) == Rtc_Int_Alarm)             || \
                                     ((x) == Rtc_Int_Period_Count)      || \
                                     ((x) == Rtc_Int_Intrusion_Ch0)     || \
                                     ((x) == Rtc_Int_Intrusion_Ch1))

/*! Parameter validity check for event flag */
#define IS_RTC_EVENT_FLAG(x)        (((x) == Rtc_Falg_Alarm_Clock)          || \
                                     ((x) == Rtc_Flag_Period)               || \
                                     ((x) == Rtc_Flag_Intrusion_Overflow)   || \
                                     ((x) == Rtc_Flag_Intrusion_Flag0)      || \
                                     ((x) == Rtc_Flag_Intrusion_Flag1))
/**
 *******************************************************************************
 ** \name The macros related to intrusion configuration.
 ******************************************************************************/
/*! init intrusion register mask */
#define RTC_INTRUSION_INIT_MASK                 (0x5F)
/*! Enable/disable intrusion mask */
#define RTC_INTRUSION_EN_MASK                   (0x80)
/*! Enable/disable intrusion event interrupt mask */
#define RTC_INTRUSION_INT_EN_MASK               (0x20)

/*! 12 hour format am/pm status bit */
#define RTC_HOUR_AMPM_MASK                      (0x20)

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
 ** \brief   Rtc init
 **
 ** \param   [in]  stcRtcInit    Pointer to a stc_rtc_init_t Structure which
 **                              will be initialized
 **                                   
 ** \retval  An en_result_t enumeration value:
 **          - Ok: init successfully
 **          - Error: init failed
 **
 ******************************************************************************/
en_result_t Rtc_Init(stc_rtc_init_t *stcRtcInit)
{
    /* Check the parameters */
    DDL_ASSERT(NULL != stcRtcInit);
    DDL_ASSERT(IS_RTC_CLOCK_SOURCE(stcRtcInit->enClk));
    DDL_ASSERT(IS_RTC_HOUR_FORMAT(stcRtcInit->enHourFormat));

    /* set clock source */
    if (Rtc_Clock_Lrc == stcRtcInit->enClk)
    {
        M4_RTC->CR3_f.LRCEN = 1u;
    }
    M4_RTC->CR3_f.RCKSEL = stcRtcInit->enClk;
    /* set hour format */
    M4_RTC->CR1_f.AMPM = stcRtcInit->enHourFormat;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief   Deinitializes the RTC registers
 **
 ** \param   none
 **                                   
 ** \retval  An en_result_t enumeration value:
 **          - Ok: Deinitializes successfully
 **          - ErrorTimeout: Deinitializes timeout
 **
 ******************************************************************************/
en_result_t Rtc_DeInit(void)
{
    uint8_t u8ResetSta;
    uint32_t u32Timeout;
    en_result_t retSta = Error;

    /* stop rtc count */
    M4_RTC->CR0_f.RESET = 0;
    /* Wait RTC RESET bit is zero or Timeout exit */
    u32Timeout = SystemCoreClock/100;
    do
    {
        u8ResetSta = M4_RTC->CR0_f.RESET;
        u32Timeout--;  
    } while((u32Timeout != 0) && (u8ResetSta == 0x01));

    if (TRUE == M4_RTC->CR0_f.RESET)
    {
        retSta = ErrorTimeout;
    } 
    else
    {
        /* reset all rtc register */
        M4_RTC->CR0_f.RESET = 1;
        M4_RTC->CR1 = 0x00;
        M4_RTC->CR3 = 0x00;

        retSta = Ok;
    }

    return retSta;
}

/**
 *******************************************************************************
 ** \brief   Rtc count enable/disable
 **
 ** \param   [in]  bCountEn    enable/disable rtc count
 **                 - FALSE: disable rtc count
 **                 - TRUE: enable rtc count
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_CountCmd(boolean_t bCountEn)
{
    /* Check the parameters */
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(bCountEn));

    /* enable/disable rtc count */
    M4_RTC->CR1_f.START = bCountEn;
}

/**
 *******************************************************************************
 ** \brief   Rtc enter read/write mode
 **
 ** \param   none
 **                                   
 ** \retval  An en_result_t enumeration value:
 **          - Ok: enter mode successfully
 **          - ErrorTimeout: enter mode timeout
 **
 ******************************************************************************/
en_result_t Rtc_EnterRwMode(void)
{
    uint8_t u8ResetSta;
    uint32_t u32Timeout;
    en_result_t retSta = Error;

    /* set RTC WAIT bit */
    M4_RTC->CR2_f.WAIT = 1;
    /* stop RTC count */
    M4_RTC->CR1_f.START = 0;
    /* Wait RTC WAITF bit is set or Timeout exit */
    u32Timeout = SystemCoreClock/100;
    do
    {
        u8ResetSta = M4_RTC->CR2_f.WAITF;
        u32Timeout--;  
    } while((u32Timeout != 0) && (u8ResetSta == 0x00));

    if (FALSE == M4_RTC->CR2_f.WAITF)
    {
        retSta = ErrorTimeout;
    } 
    else
    {
        retSta = Ok;
    }

    return retSta;
}

/**
 *******************************************************************************
 ** \brief   Rtc exit read/write mode
 **
 ** \param   none
 **                                   
 ** \retval  An en_result_t enumeration value:
 **          - Ok: exit mode successfully
 **          - ErrorTimeout: exit mode timeout
 **
 ******************************************************************************/
en_result_t Rtc_ExitRwMode(void)
{
    uint8_t u8ResetSta;
    uint32_t u32Timeout;
    en_result_t retSta = Error;

    /* reset RTC WAIT bit */
    M4_RTC->CR2_f.WAIT = 0;
    /* start RTC count */
    M4_RTC->CR1_f.START = 1;
    /* Wait RTC WAITF bit is zero or Timeout exit */
    u32Timeout = SystemCoreClock/100;
    do
    {
        u8ResetSta = M4_RTC->CR2_f.WAITF;
        u32Timeout--;  
    } while((u32Timeout != 0) && (u8ResetSta == 0x01));

    if (TRUE == M4_RTC->CR2_f.WAITF)
    {
        retSta = ErrorTimeout;
    } 
    else
    {
        retSta = Ok;
    }

    return retSta;
}

/**
 *******************************************************************************
 ** \brief   Rtc switch to low power mode
 **
 ** \param   none
 **                                   
 ** \retval  An en_result_t enumeration value:
 **          - Ok: switch successfully
 **          - Error: switch timeout
 **
 ******************************************************************************/
en_result_t Rtc_LowPowerSwitch(void)
{
    uint8_t u8ResetSta;
    uint32_t u32Timeout;
    en_result_t retSta = Error;

    /* check rtc run status */
    if (FALSE == M4_RTC->CR1_f.START)
    {
        return retSta;
    }

    /* set RTC WAIT bit */
    M4_RTC->CR2_f.WAIT = 1;
    /* Wait RTC WAITF bit is set or Timeout exit */
    u32Timeout = SystemCoreClock/100;
    do
    {
        u8ResetSta = M4_RTC->CR2_f.WAITF;
        u32Timeout--;  
    } while((u32Timeout != 0) && (u8ResetSta == 0x00));

    if (FALSE == M4_RTC->CR2_f.WAITF)
    {
        retSta = ErrorTimeout;
    } 
    else
    {
        /* reset RTC WAIT bit */
        M4_RTC->CR2_f.WAIT = 0;
        /* Wait RTC WAITF bit is zero or Timeout exit */
        u32Timeout = SystemCoreClock/100;
        do
        {
            u8ResetSta = M4_RTC->CR2_f.WAITF;
            u32Timeout--;  
        } while((u32Timeout != 0) && (u8ResetSta == 0x01));

        if (TRUE == M4_RTC->CR2_f.WAITF)
        {
            retSta = ErrorTimeout;
        } 
        else
        {
            retSta = Ok;
        }
    }

    return retSta;
}

/**
 *******************************************************************************
 ** \brief   Set rtc current date and time
 **
 ** \param   [in]  enFormat      Rtc date and time format
 **                 - Rtc_Format_Bcd: BCD data format
 **                 - Rtc_Format_Dec: Binary data format 
 ** \param   [in]  stcRtcDateTime    Pointer to a stc_rtc_time_t Structure
 ** \param   [in]  bUpdateDate   enable/disable update date
 **                 - FALSE: don't update date
 **                 - TRUE: update date
 ** \param   [in]  bUpdateTime   enable/disable update time
 **                 - FALSE: don't update time
 **                 - TRUE: update time                  
 **                                   
 ** \retval  An en_result_t enumeration value:
 **          - Ok: set successfully
 **          - Error: set failed
 **          - ErrorInvalidParameter: Both bUpdateDate and bUpdateTime are equal to 0
 **
 ******************************************************************************/
en_result_t Rtc_SetDateTime(en_rtc_format_t enFormat, stc_rtc_time_t *stcRtcDateTime,
                            boolean_t bUpdateDate, boolean_t bUpdateTime)
{
    en_result_t retSta = Error;

    /* Check the parameters */
    DDL_ASSERT(NULL != stcRtcDateTime);
    DDL_ASSERT(IS_RTC_TIME_FORMAT(enFormat));
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(bUpdateDate));
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(bUpdateTime));

    /* Check the parameters valid */
    if ((FALSE == bUpdateDate) && (FALSE == bUpdateTime))
    {
        return ErrorInvalidParameter;
    }

    /* Check the date parameters */
    if (TRUE == bUpdateDate)
    {
        if (Rtc_Format_Dec == enFormat)
        {
            DDL_ASSERT(IS_RTC_DATE_YEAR(stcRtcDateTime->u8Year));
            DDL_ASSERT(IS_RTC_DATE_MONTH(stcRtcDateTime->u8Month));
            DDL_ASSERT(IS_RTC_DATE_DAY(stcRtcDateTime->u8Day));
        }
        else
        {
            DDL_ASSERT(IS_RTC_DATE_YEAR(BCD2DEC(stcRtcDateTime->u8Year)));
            DDL_ASSERT(IS_RTC_DATE_MONTH(BCD2DEC(stcRtcDateTime->u8Month)));
            DDL_ASSERT(IS_RTC_DATE_DAY(BCD2DEC(stcRtcDateTime->u8Day)));
        }
        DDL_ASSERT(IS_RTC_DATE_WEEKDAY(stcRtcDateTime->u8Weekday));
    }
    /* Check the time parameters */
    if (TRUE == bUpdateTime)
    {
        if (Rtc_Format_Dec == enFormat)
        {
            if (Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM)
            {
                DDL_ASSERT(IS_RTC_TIME_HOUR12(stcRtcDateTime->u8Hour));
                DDL_ASSERT(IS_RTC_HOUR_AMPM(stcRtcDateTime->u8AmPm));
            }
            else
            {
                DDL_ASSERT(IS_RTC_TIME_HOUR24(stcRtcDateTime->u8Hour));
            }
            DDL_ASSERT(IS_RTC_TIME_MINUTES(stcRtcDateTime->u8Minute));
            DDL_ASSERT(IS_RTC_TIME_SECONDS(stcRtcDateTime->u8Second));
        }
        else
        {
            if (Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM)
            {
                DDL_ASSERT(IS_RTC_TIME_HOUR12(BCD2DEC(stcRtcDateTime->u8Hour)));
                DDL_ASSERT(IS_RTC_HOUR_AMPM(stcRtcDateTime->u8AmPm));
            }
            else
            {
                DDL_ASSERT(IS_RTC_TIME_HOUR24(BCD2DEC(stcRtcDateTime->u8Hour)));
            }
            DDL_ASSERT(IS_RTC_TIME_MINUTES(BCD2DEC(stcRtcDateTime->u8Minute)));
            DDL_ASSERT(IS_RTC_TIME_SECONDS(BCD2DEC(stcRtcDateTime->u8Second)));
        }
    }

    /* enter read/write mode */
    if (Rtc_EnterRwMode() == ErrorTimeout)
    {
        retSta = Error;
    }
    else
    {
        /* update date */
        if (TRUE == bUpdateDate)
        {
            if (Rtc_Format_Dec == enFormat)
            {
                M4_RTC->YEAR = DEC2BCD(stcRtcDateTime->u8Year);
                M4_RTC->MON = DEC2BCD(stcRtcDateTime->u8Month);
                M4_RTC->DAY = DEC2BCD(stcRtcDateTime->u8Day);
            }
            else
            {
                M4_RTC->YEAR = stcRtcDateTime->u8Year;
                M4_RTC->MON = stcRtcDateTime->u8Month;
                M4_RTC->DAY = stcRtcDateTime->u8Day;
            }
            M4_RTC->WEEK = stcRtcDateTime->u8Weekday;
        }
        /* update time */
        if (TRUE == bUpdateTime)
        {
            if (Rtc_Format_Dec == enFormat)
            {
                if ((Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM) && (Rtc_Hour12_PM == stcRtcDateTime->u8AmPm))
                {
                    M4_RTC->HOUR = DEC2BCD(stcRtcDateTime->u8Hour) | RTC_HOUR_AMPM_MASK;
                }
                else
                {
                    M4_RTC->HOUR = DEC2BCD(stcRtcDateTime->u8Hour);
                }
                M4_RTC->MIN = DEC2BCD(stcRtcDateTime->u8Minute);
                M4_RTC->SEC = DEC2BCD(stcRtcDateTime->u8Second);
            }
            else
            {
                if ((Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM) && (Rtc_Hour12_PM == stcRtcDateTime->u8AmPm))
                {
                    M4_RTC->HOUR = stcRtcDateTime->u8Hour | RTC_HOUR_AMPM_MASK;
                }
                else
                {
                    M4_RTC->HOUR = stcRtcDateTime->u8Hour;
                }
                M4_RTC->MIN = stcRtcDateTime->u8Minute;
                M4_RTC->SEC = stcRtcDateTime->u8Second;
            }
        }   
        /* exit read/write mode */
        if (Rtc_ExitRwMode() == ErrorTimeout)
        {
            retSta = Error;
        } 
        else
        {
            retSta = Ok;
        }
    }

    return retSta;
}

/**
 *******************************************************************************
 ** \brief   Get rtc current date and time
 **
 ** \param   [in]  enFormat      Rtc date and time format
 **                 - Rtc_Format_Bcd: BCD data format
 **                 - Rtc_Format_Dec: Binary data format 
 ** \param   [out]  stcRtcDateTime    Pointer to a stc_rtc_time_t Structure
 **                                   
 ** \retval  An en_result_t enumeration value:
 **          - Ok£ºinit successfully
 **          - Error£ºinit failed
 **
 ******************************************************************************/
en_result_t Rtc_GetDateTime(en_rtc_format_t enFormat, stc_rtc_time_t *stcRtcDateTime)
{
    en_result_t retSta = Error;

    /* Check the parameters */
    DDL_ASSERT(NULL != stcRtcDateTime);
    DDL_ASSERT(IS_RTC_TIME_FORMAT(enFormat));

    /* enter read/write mode */
    if (Rtc_EnterRwMode() == ErrorTimeout)
    {
        retSta = Error;
    }
    else
    {
        /* get rtc date and time register */
        stcRtcDateTime->u8Year = M4_RTC->YEAR;
        stcRtcDateTime->u8Month = M4_RTC->MON;
        stcRtcDateTime->u8Day = M4_RTC->DAY;
        stcRtcDateTime->u8Weekday = M4_RTC->WEEK;
        stcRtcDateTime->u8Hour = M4_RTC->HOUR;
        stcRtcDateTime->u8Minute = M4_RTC->MIN;
        stcRtcDateTime->u8Second = M4_RTC->SEC; 
        if (Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM)
        {
            /* pm */
            if ((stcRtcDateTime->u8Hour & RTC_HOUR_AMPM_MASK) == RTC_HOUR_AMPM_MASK)
            {
                stcRtcDateTime->u8Hour &= ~RTC_HOUR_AMPM_MASK;
                stcRtcDateTime->u8AmPm = Rtc_Hour12_PM;
            }
            else
            {
                stcRtcDateTime->u8AmPm = Rtc_Hour12_AM;
            }
        }

        /* Check and modify the parameter format*/
        if (Rtc_Format_Dec == enFormat)
        {
            stcRtcDateTime->u8Year = BCD2DEC(stcRtcDateTime->u8Year);
            stcRtcDateTime->u8Month = BCD2DEC(stcRtcDateTime->u8Month);
            stcRtcDateTime->u8Day = BCD2DEC(stcRtcDateTime->u8Day);
            stcRtcDateTime->u8Hour = BCD2DEC(stcRtcDateTime->u8Hour);
            stcRtcDateTime->u8Minute = BCD2DEC(stcRtcDateTime->u8Minute);
            stcRtcDateTime->u8Second = BCD2DEC(stcRtcDateTime->u8Second);
        }

        /* exit read/write mode */
        if (Rtc_ExitRwMode() == ErrorTimeout)
        {
            retSta = Error;
        } 
        else
        {
            retSta = Ok;
        }
    }

    return retSta;
}

/**
 *******************************************************************************
 ** \brief   Set rtc alarm time
 **
 ** \param   [in]  enFormat      Rtc date and time format
 **                 - Rtc_Format_Bcd: BCD data format
 **                 - Rtc_Format_Dec: Binary data format 
 ** \param   [in]  stcRtcAlarmTime    Pointer to a stc_rtc_alarm_t Structure               
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_SetAlarmTime(en_rtc_format_t enFormat, stc_rtc_alarm_t *stcRtcAlarmTime)
{
    /* Check the parameters */
    DDL_ASSERT(NULL != stcRtcAlarmTime);
    DDL_ASSERT(IS_RTC_TIME_FORMAT(enFormat));
    
    if (Rtc_Format_Dec == enFormat)
    {
        if (Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM)
        {
            DDL_ASSERT(IS_RTC_TIME_HOUR12(stcRtcAlarmTime->u8Hour));
            DDL_ASSERT(IS_RTC_HOUR_AMPM(stcRtcAlarmTime->u8AmPm));
        }
        else
        {
            DDL_ASSERT(IS_RTC_TIME_HOUR24(stcRtcAlarmTime->u8Hour));
        }
        DDL_ASSERT(IS_RTC_TIME_MINUTES(stcRtcAlarmTime->u8Minute));  
    } 
    else
    {
        if (Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM)
        {
            DDL_ASSERT(IS_RTC_TIME_HOUR12(BCD2DEC(stcRtcAlarmTime->u8Hour)));
            DDL_ASSERT(IS_RTC_HOUR_AMPM(stcRtcAlarmTime->u8AmPm));
        }
        else
        {
            DDL_ASSERT(IS_RTC_TIME_HOUR24(BCD2DEC(stcRtcAlarmTime->u8Hour)));
        }
        DDL_ASSERT(IS_RTC_TIME_MINUTES(BCD2DEC(stcRtcAlarmTime->u8Minute))); 
    }
    DDL_ASSERT(IS_RTC_ALARM_WEEKDAY(stcRtcAlarmTime->u8Weekday));

    /* disable alarm function */
    M4_RTC->CR2_f.ALME = 0;
    /* set alarm register */
    if (Rtc_Format_Dec == enFormat)
    {
        if ((Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM) && (Rtc_Hour12_PM == stcRtcAlarmTime->u8AmPm))
        {
            M4_RTC->ALMHOUR = DEC2BCD(stcRtcAlarmTime->u8Hour) | RTC_HOUR_AMPM_MASK;
        }
        else
        {
            M4_RTC->ALMHOUR = DEC2BCD(stcRtcAlarmTime->u8Hour);
        }
        M4_RTC->ALMMIN = DEC2BCD(stcRtcAlarmTime->u8Minute);
    }
    else
    {
        if ((Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM) && (Rtc_Hour12_PM == stcRtcAlarmTime->u8AmPm))
        {
            M4_RTC->ALMHOUR = stcRtcAlarmTime->u8Hour | RTC_HOUR_AMPM_MASK;
        }
        else
        {
            M4_RTC->ALMHOUR = stcRtcAlarmTime->u8Hour;
        }
        M4_RTC->ALMMIN = stcRtcAlarmTime->u8Minute;
    }
    M4_RTC->ALMWEEK = stcRtcAlarmTime->u8Weekday;
}

/**
 *******************************************************************************
 ** \brief   get rtc alarm time
 **
 ** \param   [in]  enFormat      Rtc date and time format
 **                 - Rtc_Format_Bcd: BCD data format
 **                 - Rtc_Format_Dec: Binary data format 
 ** \param   [out]  stcRtcAlarmTime    Pointer to a stc_rtc_alarm_t Structure
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_GetAlarmTime(en_rtc_format_t enFormat, stc_rtc_alarm_t *stcRtcAlarmTime)
{
    /* Check the parameters */
    DDL_ASSERT(NULL != stcRtcAlarmTime);
    DDL_ASSERT(IS_RTC_TIME_FORMAT(enFormat));

    /* get rtc date and time register */
    stcRtcAlarmTime->u8Weekday = M4_RTC->ALMWEEK;
    stcRtcAlarmTime->u8Minute = M4_RTC->ALMMIN;
    if (Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM)
    {
        stcRtcAlarmTime->u8Hour = M4_RTC->ALMHOUR;
        /* pm */
        if ((stcRtcAlarmTime->u8Hour & RTC_HOUR_AMPM_MASK) == RTC_HOUR_AMPM_MASK)
        {
            stcRtcAlarmTime->u8Hour &= ~RTC_HOUR_AMPM_MASK;
            stcRtcAlarmTime->u8AmPm = Rtc_Hour12_PM;
        }
        else
        {
            stcRtcAlarmTime->u8AmPm = Rtc_Hour12_AM;
        }
    }
    else
    {
        stcRtcAlarmTime->u8Hour = M4_RTC->ALMHOUR;
    }

    /* Check and modify the parameter format*/
    if (Rtc_Format_Dec == enFormat)
    {
        stcRtcAlarmTime->u8Hour = BCD2DEC(stcRtcAlarmTime->u8Hour);
        stcRtcAlarmTime->u8Minute = BCD2DEC(stcRtcAlarmTime->u8Minute);
    }
}

/**
 *******************************************************************************
 ** \brief   Rtc alarm enable/disable
 **
 ** \param   [in]  bAlarmEn    enable/disable rtc alarm
 **                 - FALSE: disable rtc alarm
 **                 - TRUE: enable rtc alarm
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_AlarmCmd(boolean_t bAlarmEn)
{
    /* Check the parameters */
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(bAlarmEn));

    /* enable/disable rtc alarm */
    M4_RTC->CR2_f.ALME = bAlarmEn;
}

/**
 *******************************************************************************
 ** \brief   Rtc period interrupt configuration
 **
 ** \param   [in]  enIntSel    interrupt event type selection
 **                 - Rtc_Period_Int_Disable: disable period interrupt
 **                 - Rtc_Period_Int_OneHalf_Sec: 0.5 second period
 **                 - Rtc_Period_Int_One_Sec: 1 second period interrupt  
 **                 - Rtc_Period_Int_One_Min: 1 minute period interrupt 
 **                 - Rtc_Period_Int_One_Hour: 1 hour period interrupt   
 **                 - Rtc_Period_Int_One_Day: 1 day period interrupt   
 **                 - Rtc_Period_Int_One_Mon: 1 month period interrupt  
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_PeriodIntConfig(en_rtc_period_interrupt_t enIntSel)
{
    /* Check the parameters */
    DDL_ASSERT(IS_RTC_PERIOD_INTERRUPT(enIntSel));

    /* set interrupt type */
    M4_RTC->CR1_f.PRDS = enIntSel;
}

/**
 *******************************************************************************
 ** \brief   Rtc output configuration
 **
 ** \param   [in]  enSel    rtc output format selection
 **                 - Rtc_Output_Distributed: Distributed Compensation 1hz output
 **                 - Rtc_Output_Uniform: Uniform Compensation 1hz output
 ** \param   [in]  bOutputEn    enable/disable rtc output
 **                 - FALSE: disable rtc output
 **                 - TRUE: enable rtc output
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_OutputConfig(en_rtc_output_format_t enSel, boolean_t bOutputEn)
{
    /* Check the parameters */
    DDL_ASSERT(IS_RTC_OUTPUT_FORMAT(enSel));
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(bOutputEn));

    /* set output format */
    M4_RTC->CR1_f.ONEHZSEL = enSel;
    /* enable/disable output */
    M4_RTC->CR1_f.ONEHZOE = bOutputEn;
}

/**
 *******************************************************************************
 ** \brief   Rtc clock compensation configuration 
 **
 ** \param   [in]  u16Val    rtc clock compensation value
 **                 - value valid range: 0--0x1FF
 ** \param   [in]  bClockCompenEn    enable/disable rtc clock compensation
 **                 - FALSE: disable rtc clock compensation
 **                 - TRUE: enable rtc clock compensation
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_ClockCompenConfig(uint16_t u16Val, boolean_t bClockCompenEn)
{
    /* Check the parameters */
    DDL_ASSERT(IS_RTC_CLOCK_COMPENSATION(u16Val));
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(bClockCompenEn));

    /* write compensation value to ERRCR */
    M4_RTC->ERRCRA_f.CR8 = (u16Val >> 8) & 0x01;
    M4_RTC->ERRCRB = u16Val & 0x00FF;
    /* enable/disable clock compensation */
    M4_RTC->ERRCRA_f.CREEN = bClockCompenEn;
}

/**
 *******************************************************************************
 ** \brief   rtc intrusion detection init
 **
 ** \param   [in]  enChannel      rtc intrusion channel
 **                 - Rtc_Intrusion_Ch0: RTCC0 input pin intrusion
 **                 - Rtc_Intrusion_Ch1: RTCC1 input pin intrusion
 ** \param   [in]  stcRtcIntrusionInit    Pointer to a stc_rtc_intrusion_t Structure               
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_IntrusionInit(en_rtc_intrusion_ch_t enChannel, stc_rtc_intrusion_t *stcRtcIntrusionInit)
{
    uint8_t tmpreg;
    uint8_t *pTPCR = NULL;

    /* Check the parameters */
    DDL_ASSERT(NULL != stcRtcIntrusionInit);
    DDL_ASSERT(IS_RTC_INTRUSION_CHANNEL(enChannel));
    DDL_ASSERT(IS_RTC_INTRUSION_FILTER(stcRtcIntrusionInit->enFilter));
    DDL_ASSERT(IS_RTC_INTRUSION_EDGE(stcRtcIntrusionInit->enEdge));
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(stcRtcIntrusionInit->bTimeStampEn));
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(stcRtcIntrusionInit->bIntrusionResetEn));

    /* get current TPCR address and value*/
    pTPCR = (uint8_t *)((uint32_t)(&M4_RTC->TPCR0) + enChannel * 0x4);
    tmpreg = *pTPCR;
    /* clear init parameters bits */
    tmpreg &= ~RTC_INTRUSION_INIT_MASK;
    tmpreg |= ((((uint8_t)stcRtcIntrusionInit->bTimeStampEn) << 6)      | \
              (((uint8_t)stcRtcIntrusionInit->bIntrusionResetEn) << 4)  | \
              (((uint8_t)stcRtcIntrusionInit->enFilter) << 2)           | \
              ((uint8_t)stcRtcIntrusionInit->enEdge));
    /* write to TPCR */
    *pTPCR = tmpreg;
}

/**
 *******************************************************************************
 ** \brief   rtc intrusion detection enable/disable
 **
 ** \param   [in]  enChannel      rtc intrusion channel
 **                 - Rtc_Intrusion_Ch0: RTCC0 input pin intrusion
 **                 - Rtc_Intrusion_Ch1: RTCC1 input pin intrusion
 ** \param   [in]  bIntrusionEn    enable/disable rtc intrusion detection
 **                 - FALSE: disable rtc intrusion detection
 **                 - TRUE: enable rtc intrusion detection              
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_IntrusionCmd(en_rtc_intrusion_ch_t enChannel, boolean_t bIntrusionEn)
{
    uint8_t *pTPCR = NULL;

    /* Check the parameters */
    DDL_ASSERT(IS_RTC_INTRUSION_CHANNEL(enChannel));
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(bIntrusionEn));

    /* get current TPCR address */
    pTPCR = (uint8_t *)((uint32_t)(&M4_RTC->TPCR0) + enChannel * 0x4);
    /* enable/disable intrusion function */
    if (FALSE == bIntrusionEn)
    {
        *pTPCR &= ~RTC_INTRUSION_EN_MASK;
    } 
    else
    {
        *pTPCR |= RTC_INTRUSION_EN_MASK;
    }
}

/**
 *******************************************************************************
 ** \brief   get rtc timestamp date and time
 **
 ** \param   [in]  enFormat      Rtc date and time format
 **                 - Rtc_Format_Bcd: BCD data format
 **                 - Rtc_Format_Dec: Binary data format 
 ** \param   [out]  stcRtcTimestamp    Pointer to a stc_rtc_timestamp_t Structure           
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_GetTimeStamp(en_rtc_format_t enFormat, stc_rtc_timestamp_t *stcRtcTimestamp)
{
    /* Check the parameters */
    DDL_ASSERT(NULL != stcRtcTimestamp);
    DDL_ASSERT(IS_RTC_TIME_FORMAT(enFormat));

    /* get rtc timestamp date and time register */
    stcRtcTimestamp->u8Month = M4_RTC->MONTP;
    stcRtcTimestamp->u8Day = M4_RTC->DAYTP;
    stcRtcTimestamp->u8Hour = M4_RTC->HOURTP; 
    stcRtcTimestamp->u8Minute = M4_RTC->MINTP;
    stcRtcTimestamp->u8Second = M4_RTC->SECTP; 
    
    /* Rtc_Hour_Format_12 */
    if (Rtc_Hour_Format_12 == M4_RTC->CR1_f.AMPM)
    {
        /* pm */
        if ((stcRtcTimestamp->u8Hour & RTC_HOUR_AMPM_MASK) == RTC_HOUR_AMPM_MASK)
        {
            stcRtcTimestamp->u8Hour &= ~RTC_HOUR_AMPM_MASK;
            stcRtcTimestamp->u8AmPm = Rtc_Hour12_PM;
        }
        else
        {
            stcRtcTimestamp->u8AmPm = Rtc_Hour12_AM;
        }     
    }
 
    /* Check and modify the parameter format*/
    if (Rtc_Format_Dec == enFormat)
    {
        stcRtcTimestamp->u8Month = BCD2DEC(stcRtcTimestamp->u8Month);
        stcRtcTimestamp->u8Day = BCD2DEC(stcRtcTimestamp->u8Day);
        stcRtcTimestamp->u8Hour = BCD2DEC(stcRtcTimestamp->u8Hour);
        stcRtcTimestamp->u8Minute = BCD2DEC(stcRtcTimestamp->u8Minute);
        stcRtcTimestamp->u8Second = BCD2DEC(stcRtcTimestamp->u8Second);
    }
}

/**
 *******************************************************************************
 ** \brief   rtc interrupt configuration
 **
 ** \param   [in]  enIntSel      Rtc interrupt type 
 **                 - Rtc_Int_Intrusion_Ch0: intrusion detection interrupt channel 0
 **                 - Rtc_Int_Intrusion_Ch1: intrusion detection interrupt channel 1
 **                 - Rtc_Int_Alarm: alarm interrupt
 **                 - Rtc_Int_Period_Count: period count interrupt
 **                 - Rtc_Int_Compensation: clock compensation interrupt
 ** \param   [in]  bIntEn    enable/disable rtc interrupt
 **                 - FALSE: disable rtc interrupt
 **                 - TRUE: enable rtc interrupt
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_IntConfig(en_rtc_interrupt_t enIntSel, boolean_t bIntEn)
{
    /* Check the parameters */
    DDL_ASSERT(IS_RTC_INTERRUPT_SOURCE(enIntSel));
    DDL_ASSERT(IS_RTC_FUNCTION_STATE(bIntEn));

    /* enable/disable interrupt */
    switch(enIntSel)
    {
        case Rtc_Int_Intrusion_Ch0:
            M4_RTC->TPCR0_f.TPIE0 = bIntEn;
            break;
        case Rtc_Int_Intrusion_Ch1:
            M4_RTC->TPCR1_f.TPIE1 = bIntEn;
            break;
        case Rtc_Int_Alarm:
            M4_RTC->CR2_f.ALMIE = bIntEn;
            break;
        case Rtc_Int_Period_Count:
            M4_RTC->CR2_f.PRDIE = bIntEn;
            break;
        case Rtc_Int_Compensation:
            M4_RTC->CR2_f.CRIE = bIntEn;
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 ** \brief   get rtc status flag
 **
 ** \param   [in]  enFlag      Rtc event flag
 **                 - Rtc_Flag_Intrusion_Flag0: RTCC0 Pin trigger intrusion event flag
 **                 - Rtc_Flag_Intrusion_Flag1: RTCC1 Pin trigger intrusion event flag
 **                 - Rtc_Flag_Intrusion_Overflow: trigger intrusion overflow flag
 **                 - Rtc_Falg_Alarm_Clock: alarm clock match flag
 **                 - Rtc_Flag_Period: count period flag 
 **                                   
 ** \retval  An en_stat_flag_t enumeration value:
 **          - DdlClr£ºflag reset
 **          - DdlSet£ºflag set
 **
 ******************************************************************************/
en_stat_flag_t Rtc_GetFlagStatus(en_rtc_flag_t enFlag)
{
    en_stat_flag_t retSta = DdlClr;

    /* Check the parameters */
    DDL_ASSERT(IS_RTC_EVENT_FLAG(enFlag));

    /* get flag status */
    switch(enFlag)
    {
        case Rtc_Flag_Intrusion_Flag0:
            (M4_RTC->TPSR_f.TPF0 == 1u) ? (retSta = DdlSet) : (retSta = DdlClr);
            break;
        case Rtc_Flag_Intrusion_Flag1:
            (M4_RTC->TPSR_f.TPF1 == 1u) ? (retSta = DdlSet) : (retSta = DdlClr);
            break;
        case Rtc_Flag_Intrusion_Overflow:
            (M4_RTC->TPSR_f.TPOVF == 1u) ? (retSta = DdlSet) : (retSta = DdlClr);
            break;
        case Rtc_Falg_Alarm_Clock:
            (M4_RTC->CR2_f.ALMF == 1u) ? (retSta = DdlSet) : (retSta = DdlClr);
            break;
        case Rtc_Flag_Period:
            (M4_RTC->CR2_f.PRDF == 1u) ? (retSta = DdlSet) : (retSta = DdlClr);
            break;
        default:
            break;
    }

    return retSta;
}

/**
 *******************************************************************************
 ** \brief   clear rtc status flag
 **
 ** \param   [in]  enFlag      Rtc event flag
 **                 - Rtc_Flag_Intrusion_Flag0: RTCC0 Pin trigger intrusion event flag
 **                 - Rtc_Flag_Intrusion_Flag1: RTCC1 Pin trigger intrusion event flag
 **                 - Rtc_Flag_Intrusion_Overflow: trigger intrusion overflow flag
 **                 - Rtc_Falg_Alarm_Clock: alarm clock match flag
 **                 - Rtc_Flag_Period: count period flag 
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Rtc_ClearFlag(en_rtc_flag_t enFlag)
{
    /* Check the parameters */
    DDL_ASSERT(IS_RTC_EVENT_FLAG(enFlag));

    /* clear flag status */
    switch(enFlag)
    {
    case Rtc_Flag_Intrusion_Flag0:
        M4_RTC->TPSR_f.TPF0 = 0u;
        break;
    case Rtc_Flag_Intrusion_Flag1:
        M4_RTC->TPSR_f.TPF1 = 0u;
        break;
    case Rtc_Flag_Intrusion_Overflow:
        M4_RTC->TPSR_f.TPOVF = 0u;
        break;
    case Rtc_Falg_Alarm_Clock:
        M4_RTC->CR2_f.ALMF = 0u;
        break;
    case Rtc_Flag_Period:
        M4_RTC->CR2_f.PRDF = 0u;
        break;
    default:
        break;
    }
}

//@} // RtcGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
