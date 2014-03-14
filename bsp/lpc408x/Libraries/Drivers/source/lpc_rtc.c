/**********************************************************************
* $Id$      lpc_rtc.c           2011-06-02
*//**
* @file     lpc_rtc.c
* @brief    Contains all functions support for RTC firmware library
*           on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup RTC
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _RTC

/* Includes ------------------------------------------------------------------- */
#include "lpc_rtc.h"
#include "lpc_clkpwr.h"

/* Public Functions ----------------------------------------------------------- */
/** @addtogroup RTC_Public_Functions
 * @{
 */

/********************************************************************//**
 * @brief       Initializes the RTC peripheral.
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @return      None
 *********************************************************************/
void RTC_Init (LPC_RTC_TypeDef *RTCx)
{
    /* Set up clock and power for RTC module */
    CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCRTC, ENABLE);

    // Clear all register to be default
    RTCx->ILR = 0x00;
    RTCx->CCR = 0x00;
    RTCx->CIIR = 0x00;
    RTCx->AMR = 0xFF;
    RTCx->CALIBRATION = 0x00;
}


/*********************************************************************//**
 * @brief       De-initializes the RTC peripheral registers to their
*                  default reset values.
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @return      None
 **********************************************************************/
void RTC_DeInit(LPC_RTC_TypeDef *RTCx)
{
    RTCx->CCR = 0x00;
    // Disable power and clock for RTC module
    CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCRTC, DISABLE);
}

/*********************************************************************//**
 * @brief       Reset clock tick counter in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @return      None
 **********************************************************************/
void RTC_ResetClockTickCounter(LPC_RTC_TypeDef *RTCx)
{
    RTCx->CCR |= RTC_CCR_CTCRST;
    RTCx->CCR &= (~RTC_CCR_CTCRST) & RTC_CCR_BITMASK;
}

/*********************************************************************//**
 * @brief       Start/Stop RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   NewState New State of this function, should be:
 *              - ENABLE: The time counters are enabled
 *              - DISABLE: The time counters are disabled
 * @return      None
 **********************************************************************/
void RTC_Cmd (LPC_RTC_TypeDef *RTCx, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        RTCx->CCR |= RTC_CCR_CLKEN;
    }
    else
    {
        RTCx->CCR &= (~RTC_CCR_CLKEN) & RTC_CCR_BITMASK;
    }
}


/*********************************************************************//**
 * @brief       Enable/Disable Counter increment interrupt for each time type
 *              in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   CntIncrIntType: Counter Increment Interrupt type,
 *              an increment of this type value below will generates
 *              an interrupt, should be:
 *              - RTC_TIMETYPE_SECOND
 *              - RTC_TIMETYPE_MINUTE
 *              - RTC_TIMETYPE_HOUR
 *              - RTC_TIMETYPE_DAYOFWEEK
 *              - RTC_TIMETYPE_DAYOFMONTH
 *              - RTC_TIMETYPE_DAYOFYEAR
 *              - RTC_TIMETYPE_MONTH
 *              - RTC_TIMETYPE_YEAR
 * @param[in]   NewState New State of this function, should be:
 *              - ENABLE: Counter Increment interrupt for this
 *                  time type are enabled
 *              - DISABLE: Counter Increment interrupt for this
 *                  time type are disabled
 * @return      None
 **********************************************************************/
void RTC_CntIncrIntConfig (LPC_RTC_TypeDef *RTCx, uint32_t CntIncrIntType, \
                                FunctionalState NewState)
{
    if (NewState ==  ENABLE)
    {
        switch (CntIncrIntType)
        {
        case RTC_TIMETYPE_SECOND:
            RTCx->CIIR |= RTC_CIIR_IMSEC;
            break;
        case RTC_TIMETYPE_MINUTE:
            RTCx->CIIR |= RTC_CIIR_IMMIN;
            break;
        case RTC_TIMETYPE_HOUR:
            RTCx->CIIR |= RTC_CIIR_IMHOUR;
            break;
        case RTC_TIMETYPE_DAYOFWEEK:
            RTCx->CIIR |= RTC_CIIR_IMDOW;
            break;
        case RTC_TIMETYPE_DAYOFMONTH:
            RTCx->CIIR |= RTC_CIIR_IMDOM;
            break;
        case RTC_TIMETYPE_DAYOFYEAR:
            RTCx->CIIR |= RTC_CIIR_IMDOY;
            break;
        case RTC_TIMETYPE_MONTH:
            RTCx->CIIR |= RTC_CIIR_IMMON;
            break;
        case RTC_TIMETYPE_YEAR:
            RTCx->CIIR |= RTC_CIIR_IMYEAR;
            break;
        }
    }
    else
    {
        switch (CntIncrIntType)
        {
        case RTC_TIMETYPE_SECOND:
            RTCx->CIIR &= (~RTC_CIIR_IMSEC) & RTC_CIIR_BITMASK;
            break;
        case RTC_TIMETYPE_MINUTE:
            RTCx->CIIR &= (~RTC_CIIR_IMMIN) & RTC_CIIR_BITMASK;
            break;
        case RTC_TIMETYPE_HOUR:
            RTCx->CIIR &= (~RTC_CIIR_IMHOUR) & RTC_CIIR_BITMASK;
            break;
        case RTC_TIMETYPE_DAYOFWEEK:
            RTCx->CIIR &= (~RTC_CIIR_IMDOW) & RTC_CIIR_BITMASK;
            break;
        case RTC_TIMETYPE_DAYOFMONTH:
            RTCx->CIIR &= (~RTC_CIIR_IMDOM) & RTC_CIIR_BITMASK;
            break;
        case RTC_TIMETYPE_DAYOFYEAR:
            RTCx->CIIR &= (~RTC_CIIR_IMDOY) & RTC_CIIR_BITMASK;
            break;
        case RTC_TIMETYPE_MONTH:
            RTCx->CIIR &= (~RTC_CIIR_IMMON) & RTC_CIIR_BITMASK;
            break;
        case RTC_TIMETYPE_YEAR:
            RTCx->CIIR &= (~RTC_CIIR_IMYEAR) & RTC_CIIR_BITMASK;
            break;
        }
    }
}


/*********************************************************************//**
 * @brief       Enable/Disable Alarm interrupt for each time type
 *              in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   AlarmTimeType: Alarm Time Interrupt type,
 *              an matching of this type value below with current time
 *              in RTC will generates an interrupt, should be:
 *              - RTC_TIMETYPE_SECOND
 *              - RTC_TIMETYPE_MINUTE
 *              - RTC_TIMETYPE_HOUR
 *              - RTC_TIMETYPE_DAYOFWEEK
 *              - RTC_TIMETYPE_DAYOFMONTH
 *              - RTC_TIMETYPE_DAYOFYEAR
 *              - RTC_TIMETYPE_MONTH
 *              - RTC_TIMETYPE_YEAR
 * @param[in]   NewState New State of this function, should be:
 *              - ENABLE: Alarm interrupt for this
 *                  time type are enabled
 *              - DISABLE: Alarm interrupt for this
 *                  time type are disabled
 * @return      None
 **********************************************************************/
void RTC_AlarmIntConfig (LPC_RTC_TypeDef *RTCx, uint32_t AlarmTimeType, \
                                FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        switch (AlarmTimeType)
        {
        case RTC_TIMETYPE_SECOND:
            RTCx->AMR &= (~RTC_AMR_AMRSEC) & RTC_AMR_BITMASK;
            break;
        case RTC_TIMETYPE_MINUTE:
            RTCx->AMR &= (~RTC_AMR_AMRMIN) & RTC_AMR_BITMASK;
            break;
        case RTC_TIMETYPE_HOUR:
            RTCx->AMR &= (~RTC_AMR_AMRHOUR) & RTC_AMR_BITMASK;
            break;
        case RTC_TIMETYPE_DAYOFWEEK:
            RTCx->AMR &= (~RTC_AMR_AMRDOW) & RTC_AMR_BITMASK;
            break;
        case RTC_TIMETYPE_DAYOFMONTH:
            RTCx->AMR &= (~RTC_AMR_AMRDOM) & RTC_AMR_BITMASK;
            break;
        case RTC_TIMETYPE_DAYOFYEAR:
            RTCx->AMR &= (~RTC_AMR_AMRDOY) & RTC_AMR_BITMASK;
            break;
        case RTC_TIMETYPE_MONTH:
            RTCx->AMR &= (~RTC_AMR_AMRMON) & RTC_AMR_BITMASK;
            break;
        case RTC_TIMETYPE_YEAR:
            RTCx->AMR &= (~RTC_AMR_AMRYEAR) & RTC_AMR_BITMASK;
            break;
        }
    }
    else
    {
        switch (AlarmTimeType)
        {
        case RTC_TIMETYPE_SECOND:
            RTCx->AMR |= (RTC_AMR_AMRSEC);
            break;
        case RTC_TIMETYPE_MINUTE:
            RTCx->AMR |= (RTC_AMR_AMRMIN);
            break;
        case RTC_TIMETYPE_HOUR:
            RTCx->AMR |= (RTC_AMR_AMRHOUR);
            break;
        case RTC_TIMETYPE_DAYOFWEEK:
            RTCx->AMR |= (RTC_AMR_AMRDOW);
            break;
        case RTC_TIMETYPE_DAYOFMONTH:
            RTCx->AMR |= (RTC_AMR_AMRDOM);
            break;
        case RTC_TIMETYPE_DAYOFYEAR:
            RTCx->AMR |= (RTC_AMR_AMRDOY);
            break;
        case RTC_TIMETYPE_MONTH:
            RTCx->AMR |= (RTC_AMR_AMRMON);
            break;
        case RTC_TIMETYPE_YEAR:
            RTCx->AMR |= (RTC_AMR_AMRYEAR);
            break;
        }
    }
}


/*********************************************************************//**
 * @brief       Set current time value for each time type in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   Timetype: Time Type, should be:
 *              - RTC_TIMETYPE_SECOND
 *              - RTC_TIMETYPE_MINUTE
 *              - RTC_TIMETYPE_HOUR
 *              - RTC_TIMETYPE_DAYOFWEEK
 *              - RTC_TIMETYPE_DAYOFMONTH
 *              - RTC_TIMETYPE_DAYOFYEAR
 *              - RTC_TIMETYPE_MONTH
 *              - RTC_TIMETYPE_YEAR
 * @param[in]   TimeValue Time value to set
 * @return      None
 **********************************************************************/
void RTC_SetTime (LPC_RTC_TypeDef *RTCx, uint32_t Timetype, uint32_t TimeValue)
{
    switch ( Timetype)
    {
    case RTC_TIMETYPE_SECOND:
        if(TimeValue <= RTC_SECOND_MAX) 
            RTCx->SEC = TimeValue & RTC_SEC_MASK;
        break;

    case RTC_TIMETYPE_MINUTE:
        if(TimeValue <= RTC_MINUTE_MAX)
            RTCx->MIN = TimeValue & RTC_MIN_MASK;
        break;

    case RTC_TIMETYPE_HOUR:
        if(TimeValue <= RTC_HOUR_MAX)
            RTCx->HOUR = TimeValue & RTC_HOUR_MASK;
        break;

    case RTC_TIMETYPE_DAYOFWEEK:
        if(TimeValue <= RTC_DAYOFWEEK_MAX)
            RTCx->DOW = TimeValue & RTC_DOW_MASK;
        break;

    case RTC_TIMETYPE_DAYOFMONTH:
        if((TimeValue >= RTC_DAYOFMONTH_MIN)&&(TimeValue <= RTC_DAYOFMONTH_MAX))
            RTCx->DOM = TimeValue & RTC_DOM_MASK;
        break;

    case RTC_TIMETYPE_DAYOFYEAR:
        if((TimeValue >= RTC_DAYOFYEAR_MIN)&&(TimeValue <= RTC_DAYOFYEAR_MAX))
            RTCx->DOY = TimeValue & RTC_DOY_MASK;
        break;

    case RTC_TIMETYPE_MONTH:
        if((TimeValue >= RTC_MONTH_MIN)&&(TimeValue <= RTC_MONTH_MAX))
            RTCx->MONTH = TimeValue & RTC_MONTH_MASK;
        break;

    case RTC_TIMETYPE_YEAR:
        if(TimeValue <= RTC_YEAR_MAX)
            RTCx->YEAR = TimeValue & RTC_YEAR_MASK;
        break;
    }
}

/*********************************************************************//**
 * @brief       Get current time value for each type time type
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   Timetype: Time Type, should be:
 *              - RTC_TIMETYPE_SECOND
 *              - RTC_TIMETYPE_MINUTE
 *              - RTC_TIMETYPE_HOUR
 *              - RTC_TIMETYPE_DAYOFWEEK
 *              - RTC_TIMETYPE_DAYOFMONTH
 *              - RTC_TIMETYPE_DAYOFYEAR
 *              - RTC_TIMETYPE_MONTH
 *              - RTC_TIMETYPE_YEAR
 * @return      Value of time according to specified time type
 **********************************************************************/
uint32_t RTC_GetTime(LPC_RTC_TypeDef *RTCx, uint32_t Timetype)
{
    switch (Timetype)
    {
    case RTC_TIMETYPE_SECOND:
        return (RTCx->SEC & RTC_SEC_MASK);
    case RTC_TIMETYPE_MINUTE:
        return (RTCx->MIN & RTC_MIN_MASK);
    case RTC_TIMETYPE_HOUR:
        return (RTCx->HOUR & RTC_HOUR_MASK);
    case RTC_TIMETYPE_DAYOFWEEK:
        return (RTCx->DOW & RTC_DOW_MASK);
    case RTC_TIMETYPE_DAYOFMONTH:
        return (RTCx->DOM & RTC_DOM_MASK);
    case RTC_TIMETYPE_DAYOFYEAR:
        return (RTCx->DOY & RTC_DOY_MASK);
    case RTC_TIMETYPE_MONTH:
        return (RTCx->MONTH & RTC_MONTH_MASK);
    case RTC_TIMETYPE_YEAR:
        return (RTCx->YEAR & RTC_YEAR_MASK);
    default:
        return (0);
    }
}


/*********************************************************************//**
 * @brief       Set full of time in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   pFullTime Pointer to a RTC_TIME_Type structure that
 *              contains time value in full.
 * @return      None
 **********************************************************************/
void RTC_SetFullTime (LPC_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
    RTCx->DOM = pFullTime->DOM & RTC_DOM_MASK;
    RTCx->DOW = pFullTime->DOW & RTC_DOW_MASK;
    RTCx->DOY = pFullTime->DOY & RTC_DOY_MASK;
    RTCx->HOUR = pFullTime->HOUR & RTC_HOUR_MASK;
    RTCx->MIN = pFullTime->MIN & RTC_MIN_MASK;
    RTCx->SEC = pFullTime->SEC & RTC_SEC_MASK;
    RTCx->MONTH = pFullTime->MONTH & RTC_MONTH_MASK;
    RTCx->YEAR = pFullTime->YEAR & RTC_YEAR_MASK;
}


/*********************************************************************//**
 * @brief       Get full of time in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   pFullTime Pointer to a RTC_TIME_Type structure that
 *              will be stored time in full.
 * @return      None
 **********************************************************************/
void RTC_GetFullTime (LPC_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
    pFullTime->DOM = RTCx->DOM & RTC_DOM_MASK;
    pFullTime->DOW = RTCx->DOW & RTC_DOW_MASK;
    pFullTime->DOY = RTCx->DOY & RTC_DOY_MASK;
    pFullTime->HOUR = RTCx->HOUR & RTC_HOUR_MASK;
    pFullTime->MIN = RTCx->MIN & RTC_MIN_MASK;
    pFullTime->SEC = RTCx->SEC & RTC_SEC_MASK;
    pFullTime->MONTH = RTCx->MONTH & RTC_MONTH_MASK;
    pFullTime->YEAR = RTCx->YEAR & RTC_YEAR_MASK;
}


/*********************************************************************//**
 * @brief       Set alarm time value for each time type
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   Timetype: Time Type, should be:
 *              - RTC_TIMETYPE_SECOND
 *              - RTC_TIMETYPE_MINUTE
 *              - RTC_TIMETYPE_HOUR
 *              - RTC_TIMETYPE_DAYOFWEEK
 *              - RTC_TIMETYPE_DAYOFMONTH
 *              - RTC_TIMETYPE_DAYOFYEAR
 *              - RTC_TIMETYPE_MONTH
 *              - RTC_TIMETYPE_YEAR
 * @param[in]   ALValue Alarm time value to set
 * @return      None
 **********************************************************************/
void RTC_SetAlarmTime (LPC_RTC_TypeDef *RTCx, uint32_t Timetype, uint32_t ALValue)
{
    switch (Timetype)
    {
    case RTC_TIMETYPE_SECOND:
        if(ALValue <= RTC_SECOND_MAX)
            RTCx->ALSEC = ALValue & RTC_SEC_MASK;
        break;

    case RTC_TIMETYPE_MINUTE:
        if(ALValue <= RTC_MINUTE_MAX)
            RTCx->ALMIN = ALValue & RTC_MIN_MASK;
        break;

    case RTC_TIMETYPE_HOUR:
        if(ALValue <= RTC_HOUR_MAX)
            RTCx->ALHOUR = ALValue & RTC_HOUR_MASK;
        break;

    case RTC_TIMETYPE_DAYOFWEEK:
        if(ALValue <= RTC_DAYOFWEEK_MAX)
            RTCx->ALDOW = ALValue & RTC_DOW_MASK;
        break;

    case RTC_TIMETYPE_DAYOFMONTH:
        if((ALValue >= RTC_DAYOFMONTH_MIN)&&(ALValue <= RTC_DAYOFMONTH_MAX))
            RTCx->ALDOM = ALValue & RTC_DOM_MASK;
        break;

    case RTC_TIMETYPE_DAYOFYEAR:
        if((ALValue >= RTC_DAYOFYEAR_MIN)&&(ALValue <= RTC_DAYOFYEAR_MAX))
            RTCx->ALDOY = ALValue & RTC_DOY_MASK;
        break;

    case RTC_TIMETYPE_MONTH:
        if((ALValue >= RTC_MONTH_MIN)&&(ALValue <= RTC_MONTH_MAX))
            RTCx->ALMON = ALValue & RTC_MONTH_MASK;
        break;

    case RTC_TIMETYPE_YEAR:
        if(ALValue <= RTC_YEAR_MAX)
            RTCx->ALYEAR = ALValue & RTC_YEAR_MASK;
        break;
    }
}



/*********************************************************************//**
 * @brief       Get alarm time value for each time type
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   Timetype: Time Type, should be:
 *              - RTC_TIMETYPE_SECOND
 *              - RTC_TIMETYPE_MINUTE
 *              - RTC_TIMETYPE_HOUR
 *              - RTC_TIMETYPE_DAYOFWEEK
 *              - RTC_TIMETYPE_DAYOFMONTH
 *              - RTC_TIMETYPE_DAYOFYEAR
 *              - RTC_TIMETYPE_MONTH
 *              - RTC_TIMETYPE_YEAR
  * @return     Value of Alarm time according to specified time type
 **********************************************************************/
uint32_t RTC_GetAlarmTime (LPC_RTC_TypeDef *RTCx, uint32_t Timetype)
{
    switch (Timetype)
    {
    case RTC_TIMETYPE_SECOND:
        return (RTCx->ALSEC & RTC_SEC_MASK);
    case RTC_TIMETYPE_MINUTE:
        return (RTCx->ALMIN & RTC_MIN_MASK);
    case RTC_TIMETYPE_HOUR:
        return (RTCx->ALHOUR & RTC_HOUR_MASK);
    case RTC_TIMETYPE_DAYOFWEEK:
        return (RTCx->ALDOW & RTC_DOW_MASK);
    case RTC_TIMETYPE_DAYOFMONTH:
        return (RTCx->ALDOM & RTC_DOM_MASK);
    case RTC_TIMETYPE_DAYOFYEAR:
        return (RTCx->ALDOY & RTC_DOY_MASK);
    case RTC_TIMETYPE_MONTH:
        return (RTCx->ALMON & RTC_MONTH_MASK);
    case RTC_TIMETYPE_YEAR:
        return (RTCx->ALYEAR & RTC_YEAR_MASK);
    default:
        return (0);
    }
}


/*********************************************************************//**
 * @brief       Set full of alarm time in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   pFullTime Pointer to a RTC_TIME_Type structure that
 *              contains alarm time value in full.
 * @return      None
 **********************************************************************/
void RTC_SetFullAlarmTime (LPC_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
    RTCx->ALDOM = pFullTime->DOM & RTC_DOM_MASK;
    RTCx->ALDOW = pFullTime->DOW & RTC_DOW_MASK;
    RTCx->ALDOY = pFullTime->DOY & RTC_DOY_MASK;
    RTCx->ALHOUR = pFullTime->HOUR & RTC_HOUR_MASK;
    RTCx->ALMIN = pFullTime->MIN & RTC_MIN_MASK;
    RTCx->ALSEC = pFullTime->SEC & RTC_SEC_MASK;
    RTCx->ALMON = pFullTime->MONTH & RTC_MONTH_MASK;
    RTCx->ALYEAR = pFullTime->YEAR & RTC_YEAR_MASK;
}


/*********************************************************************//**
 * @brief       Get full of alarm time in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   pFullTime Pointer to a RTC_TIME_Type structure that
 *              will be stored alarm time in full.
 * @return      None
 **********************************************************************/
void RTC_GetFullAlarmTime (LPC_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
    pFullTime->DOM = RTCx->ALDOM & RTC_DOM_MASK;
    pFullTime->DOW = RTCx->ALDOW & RTC_DOW_MASK;
    pFullTime->DOY = RTCx->ALDOY & RTC_DOY_MASK;
    pFullTime->HOUR = RTCx->ALHOUR & RTC_HOUR_MASK;
    pFullTime->MIN = RTCx->ALMIN & RTC_MIN_MASK;
    pFullTime->SEC = RTCx->ALSEC & RTC_SEC_MASK;
    pFullTime->MONTH = RTCx->ALMON & RTC_MONTH_MASK;
    pFullTime->YEAR = RTCx->ALYEAR & RTC_YEAR_MASK;
}


/*********************************************************************//**
 * @brief       Check whether if specified Location interrupt in
 *              RTC peripheral is set or not
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   IntType Interrupt location type, should be:
 *                      - RTC_INT_COUNTER_INCREASE: Counter Increment Interrupt
 *                          block generated an interrupt.
 *                      - RTC_INT_ALARM: Alarm generated an
 *                          interrupt.
 * @return      New state of specified Location interrupt in RTC peripheral
 *              (SET or RESET)
 **********************************************************************/
IntStatus RTC_GetIntPending (LPC_RTC_TypeDef *RTCx, uint32_t IntType)
{
    return ((RTCx->ILR & IntType) ? SET : RESET);
}


/*********************************************************************//**
 * @brief       Clear specified Location interrupt pending in
 *              RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   IntType Interrupt location type, should be:
 *                      - RTC_INT_COUNTER_INCREASE: Clear Counter Increment
 *                      Interrupt pending.
 *                      - RTC_INT_ALARM: Clear alarm interrupt pending
 * @return      None
 **********************************************************************/
void RTC_ClearIntPending (LPC_RTC_TypeDef *RTCx, uint32_t IntType)
{
    RTCx->ILR |= IntType;
}

/*********************************************************************//**
 * @brief       Enable/Disable calibration counter in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   NewState New State of this function, should be:
 *              - ENABLE: The calibration counter is enabled and counting
 *              - DISABLE: The calibration counter is disabled and reset to zero
 * @return      None
 **********************************************************************/
void RTC_CalibCounterCmd(LPC_RTC_TypeDef *RTCx, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        RTCx->CCR &= (~RTC_CCR_CCALEN) & RTC_CCR_BITMASK;
    }
    else
    {
        RTCx->CCR |= RTC_CCR_CCALEN;
    }
}


/*********************************************************************//**
 * @brief       Configures Calibration in RTC peripheral
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   CalibValue Calibration value, should be in range from
 *                  0 to 131,072
 * @param[in]   CalibDir Calibration Direction, should be:
 *                  - RTC_CALIB_DIR_FORWARD: Forward calibration
 *                  - RTC_CALIB_DIR_BACKWARD: Backward calibration
 * @return      None
 **********************************************************************/
void RTC_CalibConfig(LPC_RTC_TypeDef *RTCx, uint32_t CalibValue, uint8_t CalibDir)
{
    RTCx->CALIBRATION = ((CalibValue) & RTC_CALIBRATION_CALVAL_MASK) \
            | ((CalibDir == RTC_CALIB_DIR_BACKWARD) ? RTC_CALIBRATION_LIBDIR : 0);
}


/*********************************************************************//**
 * @brief       Write value to General purpose registers
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   Channel General purpose registers Channel number,
 *              should be in range from 0 to 4.
 * @param[in]   Value Value to write
 * @return      None
 * Note: These General purpose registers can be used to store important
 * information when the main power supply is off. The value in these
 * registers is not affected by chip reset.
 **********************************************************************/
void RTC_WriteGPREG (LPC_RTC_TypeDef *RTCx, uint8_t Channel, uint32_t Value)
{
    uint32_t *preg;

    preg = (uint32_t *)&RTCx->GPREG0;
    preg += Channel;
    *preg = Value;
}


/*********************************************************************//**
 * @brief       Read value from General purpose registers
 * @param[in]   RTCx    RTC peripheral selected, should be LPC_RTC
 * @param[in]   Channel General purpose registers Channel number,
 *              should be in range from 0 to 4.
 * @return      Read Value
 * Note: These General purpose registers can be used to store important
 * information when the main power supply is off. The value in these
 * registers is not affected by chip reset.
 **********************************************************************/
uint32_t RTC_ReadGPREG (LPC_RTC_TypeDef *RTCx, uint8_t Channel)
{
    uint32_t *preg;
    uint32_t value;

    preg = (uint32_t *)&RTCx->GPREG0;
    preg += Channel;
    value = *preg;
    return (value);
}
/*********************************************************************//**
 * @brief       Initialize an variable of type RTC_ER_CONFIG_Type.
 * @param[in]   pConfig The address of input variable.
 * @return      None
 **********************************************************************/
void RTC_ER_InitConfigStruct(RTC_ER_CONFIG_Type* pConfig)
{
    uint32_t tmp;
    if(pConfig == NULL)
        return;

    for(tmp = 0; tmp < RTC_ER_INPUT_CHANNEL_NUM; tmp++)
    {
        pConfig->InputChannel[tmp].EventOnPosEdge = FALSE;
        pConfig->InputChannel[tmp].GPClear= FALSE;
        pConfig->InputChannel[tmp].IntWake= FALSE;
    }
    pConfig->Clk = 64;
}

/*********************************************************************//**
 * @brief       Initialize Event Monitor/Recorder
 * @param[in]   pConfig Configuration
 * @return      SUCCESS/ERROR
 * Note: The RTC Module must be intialized before initializing this module.
 **********************************************************************/
Status RTC_ER_Init(RTC_ER_CONFIG_Type* pConfig)
{
    if(pConfig == NULL)
        return ERROR;
    if((LPC_RTC->CCR & RTC_CCR_CLKEN) == 0)
        return ERROR;

    /* EV0 */
    if(pConfig->InputChannel[0].EventOnPosEdge)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV0_POS_EDGE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV0_POS_EDGE;
    
    if(pConfig->InputChannel[0].IntWake)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV0_INTWAKE_ENABLE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV0_INTWAKE_ENABLE;

    if(pConfig->InputChannel[0].GPClear)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV0_GPCLEAR_ENABLE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV0_GPCLEAR_ENABLE;

    /* EV1 */
    if(pConfig->InputChannel[1].EventOnPosEdge)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV1_POS_EDGE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV1_POS_EDGE;
    
    if(pConfig->InputChannel[1].IntWake)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV1_INTWAKE_ENABLE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV1_INTWAKE_ENABLE;

    if(pConfig->InputChannel[1].GPClear)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV1_GPCLEAR_ENABLE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV1_GPCLEAR_ENABLE;

    /* EV2 */
    if(pConfig->InputChannel[2].EventOnPosEdge)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV2_POS_EDGE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV2_POS_EDGE;
    
    if(pConfig->InputChannel[2].IntWake)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV2_INTWAKE_ENABLE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV2_INTWAKE_ENABLE;

    if(pConfig->InputChannel[2].GPClear)
        LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV2_GPCLEAR_ENABLE;
    else
        LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV2_GPCLEAR_ENABLE;

    /* Sample Clock */
    LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_MODE_MASK;
    switch(pConfig->Clk)
    {
        case 0:
            LPC_RTC->ERCONTROL |= RTC_ERCTRL_MODE_CLK_DISABLE;
            break;
        case 16:
            LPC_RTC->ERCONTROL |= RTC_ERCTRL_MODE_16HZ;
            break;
        case 64:
            LPC_RTC->ERCONTROL |= RTC_ERCTRL_MODE_64HZ;
            break;
        case 1000:
            LPC_RTC->ERCONTROL |= RTC_ERCTRL_MODE_1KHZ;
            break;
        default:
            return ERROR;
    }
    return SUCCESS;
}
/*********************************************************************//**
 * @brief       Enable/Disable a input channel for Event Monitor/Recorder
 * @param[in]   channel Channel Number. It should be 0~2
  * @param[in]state ENABLE/DISABLE
 * @return      SUCCESS/ERROR
 **********************************************************************/
Status RTC_ER_Cmd(uint8_t channel, FunctionalState state)
{
    switch(channel)
    {
        case 0:
            if(state)
                LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV0_INPUT_ENABLE;
            else
                LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV0_INPUT_ENABLE;
            break;
        case 1:
            if(state)
                LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV1_INPUT_ENABLE;
            else
                LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV1_INPUT_ENABLE;
            break;
        case 2:
            if(state)
                LPC_RTC->ERCONTROL |= RTC_ERCTRL_EV2_INPUT_ENABLE;
            else
                LPC_RTC->ERCONTROL &= ~RTC_ERCTRL_EV2_INPUT_ENABLE;
            break;
        default:
            return ERROR;
    }
    return SUCCESS;
}
/*********************************************************************//**
 * @brief       Get event count on a given channel.
 * @param[in]   channel Channel Number. It should be 0~2
 * @return  counter
 **********************************************************************/
uint8_t RTC_ER_GetEventCount(uint8_t channel)
{
    uint8_t count = 0;
    switch(channel)
    {
        case 0:
            count = RTC_ER_EV0_COUNTER(LPC_RTC->ERCOUNTERS);
            break;
        case 1:
            count = RTC_ER_EV1_COUNTER(LPC_RTC->ERCOUNTERS);
            break;
        case 2:
            count = RTC_ER_EV2_COUNTER(LPC_RTC->ERCOUNTERS);
            break;
        default: 
            break;      
    }
    return count;
}
/*********************************************************************//**
 * @brief       Get Event Monirot/Recorder Status.
 * @param[in]   None
 * @return      Status. It can includes:
 *                  RTC_ER_EVENTS_ON_EV0_FLG
 *                  RTC_ER_EVENTS_ON_EV1_FLG
 *                  RTC_ER_EVENTS_ON_EV2_FLG
 *                  RTC_ER_STATUS_GP_CLEARED_FLG
 *                  RTC_ER_STATUS_WAKEUP_REQ_PENDING
 **********************************************************************/
uint32_t RTC_ER_GetStatus(void)
{
    return LPC_RTC->ERSTATUS;
}
/*********************************************************************//**
 * @brief       Clear Event Monitor/recoder status register.
 * @param[in] status    Status Flag. It should be:
 *                  RTC_ER_EVENTS_ON_EV0_FLG
 *                  RTC_ER_EVENTS_ON_EV1_FLG
 *                  RTC_ER_EVENTS_ON_EV2_FLG
 *                  RTC_ER_STATUS_GP_CLEARED_FLG
 *                  RTC_ER_STATUS_WAKEUP_REQ_PENDING
 * @return  None
 **********************************************************************/
void RTC_ER_ClearStatus(uint32_t status)
{
    LPC_RTC->ERSTATUS |= status;
}
/*********************************************************************//**
 * @brief       Check whether a Wakup request is pending or not.
 * @param[in] None
 * @return  TRUE/FALSE
 **********************************************************************/
Bool RTC_ER_WakupReqPending(void)
{
    if(LPC_RTC->ERSTATUS & RTC_ER_STATUS_WAKEUP_REQ_PENDING)
        return TRUE;
    else
        return FALSE;
}
/*********************************************************************//**
 * @brief       Check whether RTC General Purpose registed has been cleared or not.
 * @param[in] None
 * @return  TRUE/FALSE
 **********************************************************************/
Bool     RTC_ER_GPCleared(void)
{
    if(LPC_RTC->ERSTATUS & RTC_ER_STATUS_GP_CLEARED_FLG)
        return TRUE;
    else
        return FALSE;
}
/*********************************************************************//**
 * @brief       Get the timestamp of the fist event on a given channel.
 * @param[in] channel   Channel number (It should be 0~2)
 * @param[in] pTimeStamp    point to the buffer
 * @return  SUCCESS/ERROR
 **********************************************************************/
Status RTC_ER_GetFirstTimeStamp(uint8_t channel, RTC_ER_TIMESTAMP_Type* pTimeStamp)
{
    if(pTimeStamp == NULL)
        return ERROR;
    
    switch(channel)
    {
        case 0:
            if((LPC_RTC->ERSTATUS & (1<<RTC_ER_STATUS_EV0_BIT)) == 0)
                return ERROR;
            pTimeStamp->SEC = RTC_ER_TIMESTAMP_SEC(LPC_RTC->ERFIRSTSTAMP0);
            pTimeStamp->MIN= RTC_ER_TIMESTAMP_MIN(LPC_RTC->ERFIRSTSTAMP0);
            pTimeStamp->HOUR= RTC_ER_TIMESTAMP_HOUR(LPC_RTC->ERFIRSTSTAMP0);
            pTimeStamp->DOY = RTC_ER_TIMESTAMP_DOY(LPC_RTC->ERFIRSTSTAMP0);
            break;
        case 1:
            if((LPC_RTC->ERSTATUS & (1<<RTC_ER_STATUS_EV1_BIT)) == 0)
                return ERROR;
            pTimeStamp->SEC = RTC_ER_TIMESTAMP_SEC(LPC_RTC->ERFIRSTSTAMP1);
            pTimeStamp->MIN= RTC_ER_TIMESTAMP_MIN(LPC_RTC->ERFIRSTSTAMP1);
            pTimeStamp->HOUR= RTC_ER_TIMESTAMP_HOUR(LPC_RTC->ERFIRSTSTAMP1);
            pTimeStamp->DOY = RTC_ER_TIMESTAMP_DOY(LPC_RTC->ERFIRSTSTAMP1);
            break;
        case 2:
            if((LPC_RTC->ERSTATUS & (1<<RTC_ER_STATUS_EV2_BIT)) == 0)
                return ERROR;
            pTimeStamp->SEC = RTC_ER_TIMESTAMP_SEC(LPC_RTC->ERFIRSTSTAMP2);
            pTimeStamp->MIN= RTC_ER_TIMESTAMP_MIN(LPC_RTC->ERFIRSTSTAMP2);
            pTimeStamp->HOUR= RTC_ER_TIMESTAMP_HOUR(LPC_RTC->ERFIRSTSTAMP2);
            pTimeStamp->DOY = RTC_ER_TIMESTAMP_DOY(LPC_RTC->ERFIRSTSTAMP2);
            break;
        default: 
            break;      
    }
    return SUCCESS;

}
/*********************************************************************//**
 * @brief       Get the timestamp of the last event on a given channel.
 * @param[in] channel   Channel number (It should be 0~2)
 * @param[in] pTimeStamp    point to the buffer
 * @return  SUCCESS/ERROR
 **********************************************************************/
Status RTC_ER_GetLastTimeStamp(uint8_t channel, RTC_ER_TIMESTAMP_Type* pTimeStamp)
{
    if(pTimeStamp == NULL)
        return ERROR;
    
    switch(channel)
    {
        case 0:
            if((LPC_RTC->ERSTATUS & (1<<RTC_ER_STATUS_EV0_BIT)) == 0)
                return ERROR;
            pTimeStamp->SEC = RTC_ER_TIMESTAMP_SEC(LPC_RTC->ERLASTSTAMP0);
            pTimeStamp->MIN= RTC_ER_TIMESTAMP_MIN(LPC_RTC->ERLASTSTAMP0);
            pTimeStamp->HOUR= RTC_ER_TIMESTAMP_HOUR(LPC_RTC->ERLASTSTAMP0);
            pTimeStamp->DOY = RTC_ER_TIMESTAMP_DOY(LPC_RTC->ERLASTSTAMP0);
            break;
        case 1:
            if((LPC_RTC->ERSTATUS & (1<<RTC_ER_STATUS_EV1_BIT)) == 0)
                return ERROR;
            pTimeStamp->SEC = RTC_ER_TIMESTAMP_SEC(LPC_RTC->ERLASTSTAMP1);
            pTimeStamp->MIN= RTC_ER_TIMESTAMP_MIN(LPC_RTC->ERLASTSTAMP1);
            pTimeStamp->HOUR= RTC_ER_TIMESTAMP_HOUR(LPC_RTC->ERLASTSTAMP1);
            pTimeStamp->DOY = RTC_ER_TIMESTAMP_DOY(LPC_RTC->ERLASTSTAMP1);
            break;
        case 2:
            if((LPC_RTC->ERSTATUS & (1<<RTC_ER_STATUS_EV2_BIT)) == 0)
                return ERROR;
            pTimeStamp->SEC = RTC_ER_TIMESTAMP_SEC(LPC_RTC->ERLASTSTAMP2);
            pTimeStamp->MIN= RTC_ER_TIMESTAMP_MIN(LPC_RTC->ERLASTSTAMP2);
            pTimeStamp->HOUR= RTC_ER_TIMESTAMP_HOUR(LPC_RTC->ERLASTSTAMP2);
            pTimeStamp->DOY = RTC_ER_TIMESTAMP_DOY(LPC_RTC->ERLASTSTAMP2);
            break;
        default: 
            break;      
    }
    return SUCCESS;

}


/**
 * @}
 */

#endif /*_RTC*/
/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

