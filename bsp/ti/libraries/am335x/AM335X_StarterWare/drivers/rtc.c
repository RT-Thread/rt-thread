/**
 * \file    rtc.c
 *
 * \brief   This file contains driver API implementations for
 *          Real Time Clock(RTC) module.
 *
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "hw_types.h"
#include "rtc.h"

/******************************************************************************
**                 LOCAL MACRO DEFINITIONS                                   
******************************************************************************/

#define IS_RTC_BUSY             (HWREG(baseAdd + RTC_STATUS) & (RTC_STATUS_BUSY))

/* Macros used by RTCWriteProtectDisable() API. */
#define RTC_KICK0R_KEY          (0x83E70B13u)
#define RTC_KICK1R_KEY          (0x95A4F1E0u)

/* Macros used by RTCTimeSet() and RTCAlarmTimeSet() APIs. */
#define SECOND_MASK             (0xFF00u)
#define MINUTE_MASK             (0xFF0000u)
#define HOUR_MASK               (0xFF000000u)
#define MERIDIEM_MASK           (0x00000080u)

#define HOUR_SHIFT              (24)
#define MINUTE_SHIFT            (16)
#define SECOND_SHIFT            (8)

/* Macros used by RTCCalendarSet() and RTCAlarmCalendarSet() APIs. */
#define DAY_MASK                (0x3F000000u)
#define MONTH_MASK              (0x1F0000u)
#define YEAR_MASK               (0xFF00u)
#define DOTW_MASK               (0x07u)

#define DAY_SHIFT               (24)
#define MONTH_SHIFT             (16)
#define YEAR_SHIFT              (8)

/* Macros used by RTCCompensationSet() and RTCCompensationGet() APIs.*/
#define COMP_LOW_MASK           (0xFFu)
#define COMP_HIGH_MASK          (0xFF00u)
#define COMP_SHIFT              (0x08u)

/* Values that help identify the SoC(Platform) in use. */
#define RTC_REV_AM1808          (1)
#define RTC_REV_AM335X          (2)

/******************************************************************************
**                   EXTERNAL FUNCTION DECLARATION
******************************************************************************/

/******************************************************************************
**                   LOCAL FUNCTION DEFINITIONS
******************************************************************************/

/******************************************************************************
**         APIs common to the RTC IPs of both AM1808 and AM335x.
******************************************************************************/

/**
 * \brief    This function sets the 32KHz counter to run.\n
 * 
 * \param    baseAdd   The base address of the RTC instance being used.\n
 *
 * \return   None.\n
 */
void RTCRun(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** BUSY bit in STATUS register should be checked for being low
    ** only when RTC is running. The current function is invoked when
    ** RTC is stopped. Thus, BUSY status need not be checked.
    */
    
    /* Setting the RUN bit in CTRL register.*/
    HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_RUN | splitPower);
} 


/**
 * \brief   This function stops the 32KHz counter. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  None. \n
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 *
 */
void RTCStop(unsigned int baseAdd)
{
   
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** Writing to INTERRUPT register requires that BUSY bit in STATUS register
    ** is low.
    */
    while(IS_RTC_BUSY);
     
      /* Clearing the RUN bit in CTRL register. */    
    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RUN);
    HWREG(baseAdd + RTC_CTRL) |= splitPower;
}

/**
 * \brief   This function enables write-protection for RTC registers.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None.\n
 * 
 * \note    To enable write-protection for RTC registers, the KICK registers
 *          have to be programmed with any value other than their key values.\n
 */

void RTCWriteProtectEnable(unsigned int baseAdd)
{
    /* Writing a random value into KICK registers.*/
    HWREG(baseAdd + RTC_KICK0) = RTC_KICK0_KICK0;
    HWREG(baseAdd + RTC_KICK1) = RTC_KICK1_KICK1;
}

/**
 * \brief   This function disables write-protection for RTC registers.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None.\n
 *
 * \note    To disable write-protection for RTC registers, the KICK registers
 *          namely KICK0R and KICK1R have to be programmed with specific key 
 *          values .\n
 *          The pre-requisite to write to any RTC registers except KICK  
 *          registers is that the KICK registers have to be programmed with
 *          specific key values mentioned in the RTC peripheral user manual. 
 */


void RTCWriteProtectDisable(unsigned int baseAdd)
{
    HWREG(baseAdd + RTC_KICK0) = RTC_KICK0R_KEY;
    HWREG(baseAdd + RTC_KICK1) = RTC_KICK1R_KEY;
}


/**
 * \brief   This function enables ALARM interrupts.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None. \n 
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 *          By ALARM, the functional specification effectively means ALARM1,
 *          although it does not use the name ALARM1. This comes into context
 *          in the RTC IP of AM335x where an ALARM2 feature is also provided.
 */

void RTCIntAlarmEnable(unsigned int baseAdd)
{
    /*
    ** Writing to INTERRUPT register requires that BUSY bit in STATUS register
    ** is low.
    */
    while(IS_RTC_BUSY);
        
    HWREG(baseAdd + RTC_INTERRUPT) |= RTC_INTERRUPTS_ALARM;
}

/**
 * \brief   This function disables the ALARM interrupts.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None. \n
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 *
 */
void RTCIntAlarmDisable(unsigned int baseAdd)
{
    /*
    ** Writing to INTERRUPT register requires that BUSY bit in STATUS register
    ** is low.
    */
    while(IS_RTC_BUSY);
    HWREG(baseAdd + RTC_INTERRUPT) &= ~(RTC_INTERRUPTS_ALARM);
}   

/**
 * \brief   This function enables the periodic timer interrupt.\n
 *
 * \param   baseAdd     The base address of the RTC instance being used.\n
 * \param   timerPeriod  This specifies the period between two consecutive 
 *                       interrupts. This can take one of the following values:\n
 *                       RTC_INT_EVERY_SECOND \n
 *                       RTC_INT_EVERY_MINUTE \n
 *                       RTC_INT_EVERY_HOUR   \n
 *                       RTC_INT_EVERY_DAY    \n
 *
 * \return  None. \n
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */

void RTCIntTimerEnable(unsigned int baseAdd, unsigned int timerPeriod)
{
    /*
    ** Writing to INTERRUPT register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);

    HWREG(baseAdd + RTC_INTERRUPT) |= RTC_INTERRUPTS_TIMER;
    HWREG(baseAdd + RTC_INTERRUPT) |= (timerPeriod & RTC_INTERRUPTS_EVERY);
}

/**
 * \brief   This function disables the periodic timer interrupts.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None. \n
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */

void RTCIntTimerDisable(unsigned int baseAdd)
{
    /*
    ** Writing to INTERRUPT register requires that BUSY bit in STATUS register
    ** is low.
    */
    while(IS_RTC_BUSY); 
    HWREG(baseAdd + RTC_INTERRUPT) &= ~(RTC_INTERRUPTS_TIMER);    
}


/**
 * \brief  This function indicates whether or not RTC is busy in updating its
 *         time and calendar registers.\n
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 *
 * \return The functions returns either of the below two values:\n
 *         1> RTC_BUSY - indicating that RTC is busy in updating its registers.\n
 *         2> RTC_FREE - indicating that RTC is currently free and is not
 *                       updating its registers.\n
 */
unsigned int  RTCBusyStatusGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_STATUS) & (RTC_STATUS_BUSY));
}

/**
 * \brief   This function indicates whether RTC is currently running or 
 *          stopped.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  This function returns either of the following two values:\n
 *          1> RTC_STATUS_RUNNING - indicating that RTC is in running state.\n
 *          2> RTC_STATUS_STOPPED - indicating that RTC is in stopped state.\n
 * 
 */

unsigned int RTCRunStatusGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_STATUS) & RTC_STATUS_RUN);
}

/**
 * \brief   This function indicates whether RTC ALARM interrupt has been
 *          generated or not.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  This function returns either of the below two values:\n
 *          RTC_NEW_ALARM_INTERRUPT - indicating that a new ALARM interrupt
 *          has been generated.\n
 *          RTC_NO_NEW_ALARM_INTERRUPT - indicating that no new ALARM interrupt
 *          has been generated. \n
 * 
 * \note    It is important to invoke the function RTCSAlarmIntStatusClear()
 *          to clear the ALARM interrupt status whenever an ALARM interrupt is \n
 *          generated. Otherwise, there is a possibility of the interrupt 
 *          handler being entered again since the previous interrupt's status
 *          was not cleared. \n 
 */
unsigned int RTCAlarmIntStatusGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_STATUS) & RTC_STATUS_ALARM);
}

/**
 * \brief   This function clears the ALARM interrupt's status.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None.\n
 *
 */

void RTCAlarmIntStatusClear(unsigned int baseAdd)
{
    /*
    ** Writing logic 1 to the ALARM bit in STATUS register clears the ALARM
    ** interrupt status.
    */
    HWREG(baseAdd + RTC_STATUS) |= RTC_STATUS_ALARM;
}

/**
 * \brief   This function determines what registers have been incremented in 
 *          the latest time update.\n
 *
 * \param    baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  This function can return one of the following four values:\n
 *          1> RTC_SECOND_EVENT - when only SECOND register has incremented.\n 
 *          2> (RTC_SECOND_EVENT | RTC_MINUTE_EVENT) - when both SECOND and 
 *             MINUTE registers have been incremented.\n
 *          3> (RTC_SECOND_EVENT | RTC_MINUTE_EVENT | RTC_HOUR_EVENT) - when 
 *              SECOND, MINUTE and HOUR register have been incremented.\n
 *          4> (RTC_SECOND_EVENT | RTC_MINUTE_EVENT | RTC_HOUR_EVENT | 
 *              RTC_DAY_EVENT) - when SECOND, MINUTE, HOUR and DAY registers 
 *              have been incremented.\n
 * 
 */
unsigned int RTCEventUpdateGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_STATUS) & (RTC_STATUS_DAYEVT |
                                          RTC_STATUS_HREVT |
                                          RTC_STATUS_MINEVT |
                                          RTC_STATUS_SECEVT));

}

/**
 * \brief   This function enables the rounding feature on the current time to 
 *          the nearest minute.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * 
 * \return  None.
 *
 */
void RTCMinRoundingEnable(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** Writing to any bit in CTRL register except for SET32COUNTER bit does 
    ** not require BUSY bit in STATUS register to be low.
    */
    HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_ROUNDMIN | splitPower);
}

/**
 * \brief  This function disables the rounding feature on the current time
 *         to the nearest minute.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  None.
 */

void RTCMinRoundingDisable(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** Writing to any bit in CTRL register except for SET32COUNTER bit does
    ** not require BUSY bit in STATUS register to be low.
    */

    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_ROUNDMIN);
    HWREG(baseAdd + RTC_CTRL) |= splitPower;
}

/**
 * \brief   This function enables automatic oscillator compensation mode
 *          for the RTC.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  None. 
 *
 */

void RTCAutoCompEnable(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** Writing to any bit in CTRL register except for SET32COUNTER bit does
    ** not require BUSY bit in STATUS register to be low.
    */

    HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_AUTOCOMP | splitPower);
}

/**
 * \brief   This function disables automatic oscillator compensation mode
 *          for the RTC.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  None.
 *
 */

void RTCAutoCompDisable(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** Writing to any bit in CTRL register except for SET32COUNTER bit does
    ** not require BUSY bit in STATUS register to be low.
    */
    
    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_AUTOCOMP);
    HWREG(baseAdd + RTC_CTRL) |= splitPower;
}


/**
 * \brief   This function configures the representation type for hours for the
 *          RTC as either being 24 hour type or 12 hour type. \n
 * 
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * \param   hourType   Represents the hour mode representation type. This can 
 *                     take one of the two below values: \n
 *                     RTC_12HOUR_MODE - for 12 hour mode representation.\n
 *                     RTC_24HOUR_MODE - for 24 hour mode representation.\n
 * 
 * \return  None. \n
 */

void RTCHourModeSet(unsigned int baseAdd, unsigned int hourType)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    switch(hourType)
    {
        case RTC_12HOUR_MODE:            
             HWREG(baseAdd + RTC_CTRL) |= (RTC_12HOUR_MODE | splitPower);
        break;
   
        case RTC_24HOUR_MODE:
        default:    
             HWREG(baseAdd + RTC_CTRL) |= (RTC_24HOUR_MODE | splitPower);
        break;

    }
}


/**
 * \brief  This function reads the hour mode representation currently used in RTC. 
 *         The hour mode representation used could either be a 12 hour mode or 
 *         24 hour mode representation.
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 *
 * \return This function returns either of the following two macros:
 *         RTC_12HOUR_MODE - indicating 12 hour mode of representation. \n
 *         RTC_24HOUR_MODE - indicating 24 hour mode of representation. \n
 *
 */
unsigned int RTCHourModeGet(unsigned int baseAdd)
{

    return(HWREG(baseAdd + RTC_CTRL) & (RTC_12HOUR_MODE));
} 

/**
 * \brief   This function sets the SET32COUNTER bit in CTRL register.
 *          Setting the SET32COUNTER bit results in the 32KHz counter
 *          getting compensated with the value in the compensation registers.
 *
 * \param   baseAdd   The base address of the RTC instance being used.
 *
 * \return  None
 *
 * \note    The compensation registers contains the number of 32KHz periods
 *          to be added to the 32KHz counter every hour. This is used to
 *          compensate the oscillator drift.
 */

void RTCSet32CounterEnable(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** Modifying the SET_32_COUNTER bit in CTRL register requires that RTC
    ** is frozen. Clearing the CTRL[0] bit.
    */
    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RUN);

    /* Setting the SET_32_COUNTER bit in CTRL register. */
    HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_SET32COUNTER | splitPower);

    /* Setting the RTC 32KHz Counter to run i.e. setting CTRL[0] to 1. */
    HWREG(baseAdd + RTC_CTRL) |= RTC_CTRL_RUN;

}

/**
 * \brief   This function clears the SET32COUNTER bit in CTRL register.
 *          Clearing the SET32COUNTER bit results in the 32KHz counter not
 *          being compensated with the value in the compensation registers.
 *
 * \param   baseAdd   The base address of the RTC instance being used.
 *
 * \return  None
 *
 * \note    The compensation registers contains the number of 32KHz periods
 *          to be added to the 32KHz counter every hour. This is used to
 *          compensate the oscillator drift.
 */

void RTCSet32CounterDisable(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** Modifying the SET_32_COUNTER bit in CTRL register requires that RTC
    ** is frozen. Clearing the CTRL[0] bit.
    */
    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RUN);

    /* Clearing the SET_32_COUNTER bit in CTRL register. */
    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_SET32COUNTER);
    HWREG(baseAdd + RTC_CTRL) |= splitPower;

    /* Setting the RTC 32KHz Counter to run i.e. setting CTRL[0] to 1. */
    HWREG(baseAdd + RTC_CTRL) |= RTC_CTRL_RUN;
}

/**
 * \brief   This function is used to disable the RTC instance. Disabling the
 *          RTC would gate the 32KHz reference clock to the RTC.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n  
 *
 * \return  None.
 *
 * \note    This function sets the RTCDISABLE bit in CTRL register. Once this
 *          bit has been set, it should not be cleared again. This function
 *          should only be used when the RTC function is unwanted in the
 *          application. This bit is cleared after a reset and RTC becomes
 *          enabled. \n
 */

void RTCDisable(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /*
    ** Writing to any bit in CTRL register except for SET32COUNTER bit does
    ** not require BUSY bit in STATUS register to be low.
    */

    HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_RTCDISABLE | splitPower);
}

/**
 * \brief  This function enables the RTC. For the RTC IP in AM1808, this
 *         also performs a software reset of the RTC.
 *
 * \param  baseAdd    The base address of the RTC instance being used.
 *
 * \return None.
 *
 * \note   Registers must not be accessed for three 32-KHz reference
 *         periods after reset is asserted. The application invoking
 *         this API should provide an appropriate delay after this
 *         API's call.\n
 */

void RTCEnable(unsigned int baseAdd)
{
    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
        HWREG(baseAdd + RTC_OSC) |= RTC_OSC_SWRESET;
    }

    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RTCDISABLE);
    HWREG(baseAdd + RTC_CTRL) |= splitPower;
}
 
/**
 * \brief   This function indicates whether RTC is disabled or is enabled 
 *          and functional.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  This can return one of the two below values:
 *          RTC_ENABLED - indicating that RTC is enabled and is 
 *                        functional.
 *          RTC_DISABLED - indicating that RTC is disabled.
 */
unsigned int RTCEnableStatus(unsigned int baseAdd)
{
   return(HWREG(baseAdd + RTC_CTRL) & (RTC_CTRL_RTCDISABLE));
}

/**
 *  \brief  This function enables the split power feature of RTC and 
 *          in turn enabling the leakage isolation circuitry.
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  None.
 *
 */

void RTCSplitPwrEnable(unsigned int baseAdd)
{
    HWREG(baseAdd + RTC_CTRL) |= RTC_CTRL_SPLITPOWER;
}

/**
 * \brief   This function disables the split power feature of RTC and 
 *          in turn disabling the leakage isolation circuitry. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  None.
 *
 */

void RTCSplitPwrDisable(unsigned int baseAdd)
{
    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_SPLITPOWER);
}

/**
 * \brief   This function sets the SECOND register with the specified value.\n
 
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * \param   secValue   The value of 'seconds' to be written to SECOND 
 *                     register.\n
 * \return  None.
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */
void RTCSecondSet(unsigned int baseAdd, unsigned int secValue)
{
    
    /*
    ** Writing to SECOND register requires that BUSY bit in STATUS register
    ** is low.    
    */
 
    while(IS_RTC_BUSY); 
    
    /* Writing least 7 bits of 'secValue' into SECOND register.*/
    HWREG(baseAdd + RTC_SECOND) = (secValue & (RTC_SECOND_SEC1 | 
                                               RTC_SECOND_SEC0));        
}

/**
 * \brief   This function determines the 'second' value of the current time.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *        
 * \return  The value in the SECOND register. 
 */
unsigned int RTCSecondGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_SECOND) & (RTC_SECOND_SEC1 | RTC_SECOND_SEC0)); 
}

/**
 * \brief   This function sets the MINUTE register with the specified value.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 * \param   minValue  The value of 'minutes' to be written to MINUTE 
 *                    register.\n  
 *
 * \return  None.
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 *  
 */

void RTCMinuteSet(unsigned int baseAdd, unsigned int minValue)
{
    /*
    ** Writing to MINUTE register requires that BUSY bit in STATUS register
    ** is low.    
    */
 
    while(IS_RTC_BUSY);

    /* Writing least 7 bits of 'minValue' into MINUTE register.*/
    HWREG(baseAdd + RTC_MINUTE) = (minValue & (RTC_MINUTE_MIN1 | 
                                                RTC_MINUTE_MIN0));
}

/**
 * \brief   This function determines the minute value of the current time.
 *
 * \param   baseAdd The base address of the RTC instance being used.\n
 *
 * \return  The value in MINUTE register.
 */

unsigned int RTCMinuteGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_MINUTE) & (RTC_MINUTE_MIN1 | 
                                           RTC_MINUTE_MIN0));
}

/**
 * \brief  This function sets the hour value of the current time.\n
 *
 * \param  baseAdd   The base address of the RTC instance being used.\n
 * \param  hourValue  The value of 'hours' to be written into HOURS register.\n
 * 
 * \return None.
 *
 * \note   Programming the HOUR register with the hours value will also modify
 *         the MERIDIEM bit present in the HOUR register. Thus, invoke the \n
 *         API \RTCMeridiemSet after invoking this API to set the meridiem 
 *         type. \n
 *         If the RTC is busy in updating its registers, then this API waits 
 *         until this update is complete. \n
 * 
 */


void RTCHourSet(unsigned int baseAdd, unsigned int hourValue)
{

    /*
    ** Writing to HOUR register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);

    /* Writing least 6 bits of 'hourValue' into HOUR register.*/
    HWREG(baseAdd + RTC_HOUR) = (hourValue & (RTC_HOUR_HOUR1 | 
                                              RTC_HOUR_HOUR0));
}



/**
 * \brief  This function reads hour value of the current time.\n
 *
 * \param  baseAdd   The base address of the RTC instance being used.\n
 *
 * \return The value in the HOUR register. 
 */
unsigned int RTCHourGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_HOUR) & (RTC_HOUR_HOUR1 | RTC_HOUR_HOUR0));
}

/**
 * \brief  This function sets the meridiem type for the time that is 
 *         programmed. 
 *
 * \param   baseAdd      The base address of the RTC instance being used.\n
 * \param   meridiemType  This specifies the meridiem type. This can take one
 *                        of the below two values: \n
 *                        RTC_ANTE_MERIDIEM - for ante-meridiem(AM).
 *                        RTC_POST_MERIDIEM - for post-meridiem(PM).
 *
 * \return  None.
 *
 * \note    Programming the type of meridiem is meaningful only when 12-hour
 *          mode of time representation has been opted for. Use RTCHourModeSet()
 *          to do this. 
 *          If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 */                        



void RTCMeridiemSet(unsigned int baseAdd, unsigned int meridiemType)
{
    /*
    ** Writing to HOUR register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);
    
    /* Set the MERIDIEM bit in HOUR register.*/
    HWREG(baseAdd + RTC_HOUR) |= (meridiemType & RTC_HOUR_MERIDIEM);

}

/**
 * \brief   This function determines the meridiem type of the current time.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  The meridiem type of the current time. This will be one of the 
 *          two below values:
 *          RTC_ANTE_MERIDIEM - indicating ante-meridiem(AM).
 *          RTC_POST_MERIDIEM - indicating post-meridiem(PM).
 *
 * \note    The meridiem type of the current time should be ignored if the 
 *          time representation is in 24 hour mode format.
 */

unsigned int RTCMeridiemGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_HOUR) & RTC_HOUR_MERIDIEM);
}

/**
 * \brief  This function sets the day of the month in the relevant register.  
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 * \param  dayValue  The 'day' value to be written to DAY register.\n
 *
 * \return None.\n
 *
 * \note   If the RTC is busy in updating its registers, then this API waits 
 *         until this update is complete. \n
 *
 */

void RTCDayOfMonthSet(unsigned int baseAdd, unsigned int dayValue)
{
    /*
    ** Writing to DAY register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);

    /* Writing least 6 bits of 'dayValue' to DAY register.*/
    HWREG(baseAdd + RTC_DAY) = (dayValue & (RTC_DAY_DAY1 | RTC_DAY_DAY0));    

}

/**
 * \brief  This function determines the day of the month currently held by 
 *         relevant RTC register.
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 *
 * \return The 'day' value in the DAY register.
 *
 */

unsigned int RTCDayOfMonthGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_DAY) & (RTC_DAY_DAY1 | RTC_DAY_DAY0));
}

/**
 * \brief   This function sets the month of the year in the relevant RTC
 *          register. 
 *
 * \param   baseAdd    The base address of the RTC instance being used.\n
 * \param   monthValue  The 'month' value to be written to MONTH regsiter.\n
 *
 * \return  None.\n
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 
 */

void RTCMonthSet(unsigned int baseAdd, unsigned int monthValue)
{
    /*
    ** Writing to MONTH register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);

    /* Writing least 5 bits of 'monthValue' into MONTH register.*/
    HWREG(baseAdd + RTC_MONTH) = (monthValue & (RTC_MONTH_MONTH1 | 
                                                RTC_MONTH_MONTH0));

}

/**
 * \brief  This function determines the month of the year from the relevant 
 *         RTC register. 
 *
 * \param   baseAdd    The base address of the RTC instance being used.\n
 *
 * \return  The 'month' value in the MONTH register. \n
 */


unsigned int RTCMonthGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_MONTH) & (RTC_MONTH_MONTH1 | RTC_MONTH_MONTH0));
}

/**
 * \brief   This function sets the year value in the relevant RTC register. 
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 * \param   yearValue  The 'year' value to be written to YEAR register. \n
 *
 * \return  None. \n
 *
 * \note    We can program only the last two digits of the four digit year
 *          value. Ex: 87 is programmed for year being 1987. \n
 *          If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */


void RTCYearSet(unsigned int baseAdd, unsigned int yearValue)
{
    /*
    ** Writing to YEAR register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);

    /* Write least 8 bits of 'yearValue' to YEAR register.*/
    HWREG(baseAdd + RTC_YEAR) = (yearValue & (RTC_YEAR_YEAR1 | RTC_YEAR_YEAR0));

}

/**
 * \brief  This function determines the current year value from the relevant
 *         RTC register. 
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 * 
 * \return  The 'year' value in the YEAR register.\n
 */

unsigned int RTCYearGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_YEAR) & (RTC_YEAR_YEAR1 | RTC_YEAR_YEAR0));
}

/**
 * \brief   This function sets the day of the week in the relevant RTC register. 
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * \param   weekValue  The 'day of the week' value to be written to DOTW
 *                     register. This will take one of the following seven
 *                     values:
 *                     RTC_DOTW_SUN - indicating Sunday. \n
 *                     RTC_DOTW_MON - indicating Monday. \n
 *                     RTC_DOTW_TUE - indicating Tuesday. \n
 *                     RTC_DOTW_WED - indicating Wednesday. \n
 *                     RTC_DOTW_THU - indicating Thursday. \n
 *                     RTC_DOTW_FRI - indicating Friday. \n
 *                     RTC_DOTW_SAT - indicating Saturday. \n                     
 *
 * \return  None.
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */
void RTCDayOfTheWeekSet(unsigned int baseAdd, unsigned int dotwValue)
{
    /*
    ** Writing to DOTW register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);
    
    /* Write least 3 bits of 'weekValue' to DOTW register.*/
    HWREG(baseAdd + RTC_DOTW) = (dotwValue & RTC_DOTW_DOTW);
}

/**
 * \brief   This function reads the current day of the week from the relevant
 *          RTC register.
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  The 'day of the week' value in the DOTW register. 
 *          This returns one of the seven values mentioned in the API
 *          \RTCDayOfTheWeekSet. \n
 */

unsigned int RTCDayOfTheWeekGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_DOTW) & RTC_DOTW_DOTW);
}

/**
 * \brief   This function programs the specified time information in
 *          the Time registers.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 * \param   time      The time is specified here and should be in the
 *                    following format: <hours><minutes><seconds><meridiem>.\n
 *                    Example - For 12-hour representation mode:\n
 *                    If the time is 8 hours, 47 minutes and 31 seconds AM,
 *                    then the 'time' should be
 *                    (0x08473100 | RTC_ANTE_MERIDIEM). \n
 *                    For 24-hour representation mode:
 *                    If the time is 19 hours, 53 minutes, 02 seconds, then
 *                    'time' should be (0x19530200).
 *
 * \return  None.
 *
 * \note    Though this API programs the required time value in the relevant
 *          Time registers of RTC, it does not start the RTC. The API RTCRun()
 *          should be explicitly called later to start the RTC.
 */

void RTCTimeSet(unsigned int baseAdd, unsigned int time)
{

    volatile unsigned int splitPower = 0;

    if(RTC_REV_AM1808 == RtcVersionGet())
    {
        splitPower = RTC_CTRL_SPLITPOWER;
    }

    /* Stop the RTC.*/
    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RUN);
    /* Enable split power mode.*/
    HWREG(baseAdd + RTC_CTRL) |= splitPower;

    /* Writing to SECOND register.*/
    HWREG(baseAdd + RTC_SECOND) = (time & SECOND_MASK) >> SECOND_SHIFT;

    /* Writing to MINUTE register.*/
    HWREG(baseAdd + RTC_MINUTE) = (time & MINUTE_MASK) >> MINUTE_SHIFT;

    /* Writing to HOUR register.*/
    HWREG(baseAdd + RTC_HOUR) = (((time & HOUR_MASK) >> HOUR_SHIFT) |
                                 (time & MERIDIEM_MASK));

}  


/**
 * \brief   This function reads the current time from the registers holding 
 *          time information. \n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  The time in the format: <hours><minutes><seconds><meridiem>.
 *
 */
unsigned int RTCTimeGet(unsigned int baseAdd)
{
    unsigned int sec = 0, min = 0, hour = 0, mer = 0;

    /* Reading from SECOND register.*/
    sec = HWREG(baseAdd + RTC_SECOND);
    sec = (sec & (RTC_SECOND_SEC1 | RTC_SECOND_SEC0)) << SECOND_SHIFT;

    /* Reading from MINUTE register.*/
    min = HWREG(baseAdd +  RTC_MINUTE);
    min = (min & (RTC_MINUTE_MIN1 | RTC_MINUTE_MIN0)) << MINUTE_SHIFT;

    /* Reading from HOUR register.*/
    hour = HWREG(baseAdd + RTC_HOUR);
    hour = (hour & (RTC_HOUR_HOUR1 | RTC_HOUR_HOUR0)) << HOUR_SHIFT;

    /* Reading MERIDIEM bit in HOUR register.*/
    mer = (HWREG(baseAdd + RTC_HOUR) & RTC_HOUR_MERIDIEM);      
          
 
    return ( sec | min | hour | mer);  
}

/**
 * \brief  This function sets the specified calendar information in registers 
 *         holding calendar settings. \n
 *          
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 * \param   calendar  This parameter includes values for day of the month,
 *                    month, year and day of the week. The format is:  
 *                    <day of the month><month><year><day of the week>
 *
 *                    For example, if the date is: 29 November,2010,Monday,then
 *                    the representation would be: 0x29111000 | RTC_DOTW_MON.
 *                   (Nov = 11, 2010 = 10). \n
 *
 * \return  None.
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */

void RTCCalendarSet(unsigned int baseAdd, unsigned int calendar)
{

    while(IS_RTC_BUSY);

    /* Writing to YEAR register.*/
    HWREG(baseAdd + RTC_YEAR) = (calendar & YEAR_MASK) >> YEAR_SHIFT;

    /* Writing to MONTH register.*/
    HWREG(baseAdd + RTC_MONTH) = (calendar & MONTH_MASK) >> MONTH_SHIFT;

    /* Writing to DAY register.*/
    HWREG(baseAdd + RTC_DAY) = (calendar & DAY_MASK) >> DAY_SHIFT;

    /* Writing to DOTW register.*/
    HWREG(baseAdd + RTC_DOTW) = (calendar & DOTW_MASK);

}

/**
 * \brief   This function reads the calendar information from relevant
 *          registers holding calendar settings. \n
 *
 * \param   baseAdd The base address of the RTC instance being used.\n
 *
 * \return  The calendar information in the format:
 *          <day of the month><month><year><day of the week>.
 */

unsigned int RTCCalendarGet(unsigned int baseAdd)
{
    unsigned int calVal = 0;
    
    /* Reading from the DAY register.*/
    calVal = (HWREG(baseAdd + RTC_DAY) & (RTC_DAY_DAY1 | RTC_DAY_DAY0)) <<  \
                                             DAY_SHIFT;

    /* Reading from MONTH register.*/
    calVal |= (HWREG(baseAdd + RTC_MONTH) & (RTC_MONTH_MONTH1 | 
                                              RTC_MONTH_MONTH0)) << MONTH_SHIFT;

    /* Reading from YEAR register.*/
    calVal |= (HWREG(baseAdd + RTC_YEAR) & (RTC_YEAR_YEAR1 | 
                                             RTC_YEAR_YEAR0))  << YEAR_SHIFT;

    /* Reading from DOTW register.*/
    calVal |= (HWREG(baseAdd + RTC_DOTW) & RTC_DOTW_DOTW);

    return calVal;
}

/**
 * \brief  This configures the seconds value in the ALARM registers. \n
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 * \param  alarmsecValue  The seconds value to be set in the ALARMSECOND
 *                        registers. \n 
 *
 * \return None.
 *
 * \note   If the RTC is busy in updating its registers, then this API waits 
 *         until this update is complete. \n
 * 
 */

void RTCAlarmSecondSet(unsigned int baseAdd, unsigned int alarmSecValue)
{    
    /*
    ** Writing to ALARMSECOND register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);

    /* Writing least 7 bits of 'alarmsecValue' to ALARMSECOND register.*/
    HWREG(baseAdd + RTC_ALARMSECOND) = (alarmSecValue & (RTC_ALARMSECOND_SEC1 |
                                                          RTC_ALARMSECOND_SEC0));
}


/**
 * \brief  This determines the seconds value being set in the ALARM
 *         registers. \n
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 *
 * \return The value of seconds being set in the ALARMSECOND register.\n
 *
 */

unsigned int RTCAlarmSecondGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_ALARMSECOND) & (RTC_ALARMSECOND_SEC1 | 
                                                RTC_ALARMSECOND_SEC0));
}

/**
 * \brief   This configures the minutes value in the ALARM registers. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * \param   alarmminValue  The minutes value to be written to 
 *                         ALARMMINUTES register. \n
 * \return  None.
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n 
 *
 */


void RTCAlarmMinuteSet(unsigned int baseAdd, unsigned int alrmMinValue)
{
    /*
    ** Writing to ALARMMINUTE register requires that BUSY bit in STATUS register
    ** is low.    
    */
    
    while(IS_RTC_BUSY);

    /* Write least 7 bits to ALARMMINUTE register.*/
    HWREG(baseAdd + RTC_ALARMMINUTE) = (alrmMinValue & (RTC_ALARMMINUTE_MIN1 |
                                                         RTC_ALARMMINUTE_MIN0));

}

/**
 * \brief   This determines the value of minutes being set in the ALARM
 *          registers.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  The value of minutes being set in the ALARMMINUTES register. \n
 */

unsigned int RTCAlarmMinuteGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_ALARMMINUTE) & (RTC_ALARMMINUTE_MIN1 | 
                                                RTC_ALARMMINUTE_MIN0));
}

/**
 * \brief  This sets the value of hours in the ALARM registers. \n
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 * \param  alarmhourValue  The value of hours to be written to 
 *                         ALARMHOUR register. \n
 * \return None.
 * 
 * \note   Programming the ALARMHOUR register with the hours value will also 
 *         modify the MERIDIEM bit present in the ALARMHOUR register.
 *         Thus, invoke the API RTCAlarmHourMeridiemSet() after invoking
 *         the current API to configure the MERIDIEM bit. \n
 *         If the RTC is busy in updating its registers, then this API waits 
 *         until this update is complete. \n
 * 
 */

void RTCAlarmHourSet(unsigned int baseAdd, unsigned int alrmHourVal)
{
    /*
    ** Writing to ALARMHOUR register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);

    /*
    ** Writing the least 6 bits of 'alrmHourVal' to the ALARMHOUR 
    ** register.
    */
    HWREG(baseAdd + RTC_ALARMHOUR) = (alrmHourVal & (RTC_ALARMHOUR_HOUR1 | 
                                                      RTC_ALARMHOUR_HOUR0));
}

/**
 * \brief   This determines the value of hours being set in the ALARM
 *          registers.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  The value of hours being set in the ALARMHOUR register. \n
 */

unsigned int RTCAlarmHourGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_ALARMHOUR) & (RTC_ALARMHOUR_HOUR1 | 
                                              RTC_ALARMHOUR_HOUR0));
}

/**
 * \brief  This function sets the meridiem type for the ALARM time that is
 *         programmed.\n
 *
 * \param   baseAdd       The base address of the RTC instance being used.\n
 * \param   meridiemType  This specifies the meridiem type. This can take one
 *                        of the below two values: \n
 *                        RTC_ANTE_MERIDIEM - for ante-meridiem(AM).
 *                        RTC_POST_MERIDIEM - for post-meridiem(PM).
 *
 * \return  None.
 *
 * \note    Programming the type of meridiem is meaningful only when 12-hour
 *          mode of time representation has been opted for. Use RTCHourModeSet()
 *          to do this.
 *          If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 */


void RTCAlarmHourMeridiemSet(unsigned int baseAdd, unsigned int meridiemType)
{
    /*
    ** Writing to YEAR register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);

    /* Set the MERIDIEM bit in ALARMHOUR register.*/
    HWREG(baseAdd + RTC_ALARMHOUR) |= (meridiemType & RTC_ALARMHOUR_MERIDIEM);
}

/**
 * \brief   This function determines the meridiem type of the ALARM time.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  The meridiem type of the ALARM time. This will be one of the
 *          two below values:
 *          RTC_ANTE_MERIDIEM - indicating ante-meridiem(AM).
 *          RTC_POST_MERIDIEM - indicating post-meridiem(PM).
 *
 * \note    The meridiem type of the ALARM time should be ignored if the
 *          time representation is in 24 hour mode format.
 */
 
unsigned int RTCAlarmHourMeridiemGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_ALARMHOUR) & RTC_HOUR_MERIDIEM);
}

/**
 * \brief  This function sets the ALARM time regiters with the specified
 *         ALARM time value. \n
 *
 * \param  baseAdd   The base address of the RTC instance being used.\n  
 * \param  alarmTime  The time is specified here and should be in the
 *                    following format: <hours><minutes><seconds><meridiem>.\n
 *                    Example - For 12-hour mode representation:\n
 *                    If the time is 10 hours, 54 minutes and 31 seconds PM,
 *                    then the 'alarmTime' should be
 *                    (0x10543100 | RTC_POST_MERIDIEM). \n
 *                    For 24-hour mode representation:\n
 *                    If the time is 17 hours, 36 minutes, 41 seconds, then
 *                    'alarmTime' should be (0x17364100).\n
 *
 * \note   If the RTC is busy in updating its registers, then this API waits 
 *         until this update is complete. \n
 * 
 */


void RTCAlarmTimeSet(unsigned int baseAdd, unsigned int alarmTime)
{
    while(IS_RTC_BUSY);

    /* Writing to ALARMSECOND register.*/
    HWREG(baseAdd + RTC_ALARMSECOND) = (alarmTime & SECOND_MASK) >> SECOND_SHIFT;

    /* Writing to ALARMMINUTE register.*/
    HWREG(baseAdd + RTC_ALARMMINUTE) = (alarmTime & MINUTE_MASK) >> MINUTE_SHIFT;

    /* Writing to ALARMHOUR register.*/
    HWREG(baseAdd + RTC_ALARMHOUR) = (((alarmTime & HOUR_MASK) >> HOUR_SHIFT) |
                                      (alarmTime & MERIDIEM_MASK));

}



/**  
 * \brief   This function reads the programmed ALARM time from the ALARM
 *          registers.
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  The ALARM time is returned in the format:
 *          <hour><minute><second><meridiem>.
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */
unsigned int RTCAlarmTimeGet(unsigned int baseAdd)
{
    unsigned int alrmSec = 0, alrmMin = 0, alrmHour = 0, alrmMer = 0;

    while(IS_RTC_BUSY);

    /* Reading from ALARMSECOND register.*/
    alrmSec = HWREG(baseAdd + RTC_ALARMSECOND);
    alrmSec = (alrmSec & (RTC_SECOND_SEC1 | RTC_SECOND_SEC0)) << SECOND_SHIFT;

    /* Reading from ALARMMINUTE register.*/
    alrmMin = HWREG(baseAdd +  RTC_ALARMMINUTE);
    alrmMin = (alrmMin & (RTC_MINUTE_MIN1 | RTC_MINUTE_MIN0)) << MINUTE_SHIFT;

    /* Reading from ALARMHOUR register.*/
    alrmHour = HWREG(baseAdd + RTC_ALARMHOUR);
    alrmHour = (alrmHour & (RTC_HOUR_HOUR1 | RTC_HOUR_HOUR0)) << HOUR_SHIFT;

    /* Reading MERIDIEM bit in ALARMHOUR register.*/
    alrmMer = (HWREG(baseAdd + RTC_ALARMHOUR) & RTC_HOUR_MERIDIEM);      
          
 
    return ( alrmSec | alrmMin | alrmHour | alrmMer);  
}

 /**
 * \brief  This function sets the day of the month in the ALARM registers. \n
 *
 * \param  baseAdd      The base address of the RTC instance being used.\n
 * \param  alarmdayValue The day of the month to be written to ALARMDAY
 *                       register. \n
 *
 * \return None.
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */

void RTCAlarmDayOfMonthSet(unsigned int baseAdd, unsigned int alarmDayValue)
{
    /*
    ** Writing to YEAR register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);
 
    /* Writing the least 6 bits of 'alarmDayValue' to ALARMHOUR register.*/
    HWREG(baseAdd + RTC_ALARMDAY) = (alarmDayValue & (RTC_ALARMDAY_DAY1 | 
                                                  RTC_ALARMDAY_DAY0));

}

/**
 * \brief  This function determines the day of the month being set in the
 *         ALARM registers. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  The day of the month value set in ALARMDAY register. \n
 */
unsigned int RTCAlarmDayOfMonthGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_ALARMDAY) & (RTC_ALARMDAY_DAY1 | RTC_ALARMDAY_DAY0));
}

/**
 * \brief   This function sets the value of the month in the ALARM registers.\n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * \param   alarmmonthValue  The value of the month to be written to 
 *                           ALARMMONTH register. \n
 * \return  None.
 *
 * \note    If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 * 
 */

void RTCAlarmMonthSet(unsigned int baseAdd, unsigned int alrmMnthVal)
{
    /*
    ** Writing to YEAR register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);
   
    /* Writing the least 6 bits of 'alrmMnthVal' to ALARMHOUR register.*/
    HWREG(baseAdd + RTC_ALARMMONTH) = (alrmMnthVal & (RTC_ALARMMONTH_MONTH1 | 
                                                       RTC_ALARMMONTH_MONTH0));
}

/**
 * \brief  This function determines the value of month being set in the
 *         ALARM registers. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * 
 * \return  The value of month being set in the ALARMMONTH register. \n
 */

unsigned int RTCAlarmMonthGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_ALARMMONTH) & (RTC_ALARMMONTH_MONTH1 | 
                                               RTC_ALARMMONTH_MONTH0));
}

/**
 * \brief   This function sets the value of year in the ALARM registers. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * \param   alarmyearValue  The value of year to be written to ALARMYEAR
 *                          register. \n
 * 
 * \return  None.
 *
 * \note    We can program only the last two digits of the four digit year
 *          value. Ex: 87 is programmed for year being 1987.
 *          If the RTC is busy in updating its registers, then this API waits 
 *          until this update is complete. \n
 *
 */

void RTCAlarmYearSet(unsigned int baseAdd, unsigned int alrmYrVal)
{
    /*
    ** Writing to YEAR register requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);
    
    /* Writing the least 8 bits of 'alrmYrVal' to ALARMYEAR register.*/
    HWREG(baseAdd + RTC_ALARMYEAR) = (alrmYrVal & (RTC_ALARMYEAR_YEAR1 | 
                                                    RTC_ALARMYEAR_YEAR0));
}

/**
 * \brief  This function determines the value of the year being set in the 
 *         ALARM registers. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  The value of year being set in the ALARMYEAR register. \n
 *
 */

unsigned int RTCAlarmYearGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_ALARMYEAR) & (RTC_ALARMYEAR_YEAR1 | 
                                              RTC_ALARMYEAR_YEAR0));
}

/**
 * \brief  This sets the ALARM calendar registers of the RTC with the specified
 *         ALARM calendar information. \n
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 * \param  calVal    This parameter includes values for day of the month,
 *                   month and  year. The format is:  
 *                   <day of the month><month><year>.
 *                   For example, if the ALARM calendar registers are to be
 *                   loaded with a date namely 24 February, 2003, then 
 *                   'calVal' should be 0x24020300(February=0x02, 2003=0x03)
 *
 * \return None. \n
 * 
 * \note   If the RTC is busy in updating its registers, then this API waits 
 *         until this update is complete. \n
 * 
 */
void RTCAlarmCalendarSet(unsigned int baseAdd, unsigned int calVal)
{
    while(IS_RTC_BUSY);

    /* Writing to ALARMYEAR register.*/
    HWREG(baseAdd + RTC_ALARMYEAR) = (calVal & YEAR_MASK) >> YEAR_SHIFT;

    /* Writing to ALARMMONTH register.*/
    HWREG(baseAdd + RTC_ALARMMONTH) = (calVal & MONTH_MASK) >> MONTH_SHIFT;

    /* Writing to ALARMDAY register.*/
    HWREG(baseAdd + RTC_ALARMDAY) = (calVal & DAY_MASK) >> DAY_SHIFT;
}

/**
 * \brief   This function reads the ALARM calendar information being set in
 *          the ALARM calendar registers. \n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  The ALARM calendar information read from the ALARM calendar
 *          registers. The format of this information is:
 *          <day of the week><month><year>.
 *
 * 
 */
unsigned int RTCAlarmCalendarGet(unsigned int baseAdd)
{
    unsigned int calVal = 0;
    
    /* Reading from the ALARMDAY register.*/
    calVal = (HWREG(baseAdd + RTC_ALARMDAY) & (RTC_DAY_DAY1 | 
                                                RTC_DAY_DAY0)) << DAY_SHIFT;

    /* Reading from ALARMMONTH register.*/
    calVal |= (HWREG(baseAdd + RTC_ALARMMONTH) & (RTC_MONTH_MONTH1 | 
                                                   RTC_MONTH_MONTH0)) <<   \
                                                   MONTH_SHIFT;

    /* Reading from ALARMYEAR register.*/
    calVal |= (HWREG(baseAdd + RTC_ALARMYEAR) & (RTC_YEAR_YEAR1 | 
                                                  RTC_YEAR_YEAR0))  <<     \
                                                  YEAR_SHIFT;

    return calVal;
}


/**
 * \brief  This function sets the compensation registers with the specified
 *         compensation value. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 * \param   compVal    The compensation value.
 *
 * \return None. \n
 *
 * \note   Compensation value is subtracted from the 32KHz period. The 
 *         subtraction here is accomplished by two's complement
 *         addititon. Thus the application should pass the two's 
 *         complement value of the value to be subtracted.\n
 *         If the RTC is busy in updating its registers, then this API waits 
 *         until this update is complete. \n
 * 
 */
void RTCCompensationSet(unsigned int baseAdd, unsigned int compVal)
{
    /*
    ** Writing to COMPENSATION registers requires that BUSY bit in STATUS register
    ** is low.    
    */
    while(IS_RTC_BUSY);  

    /* Writing the lower 8 bits of 'compVal' to COMPLSB register.*/
    HWREG(baseAdd + RTC_COMPLSB) = (compVal & COMP_LOW_MASK);

    /* Writing the higher 8 bits of 'compVal' to COMPMSB register.*/
    HWREG(baseAdd + RTC_COMPMSB) = (compVal & COMP_HIGH_MASK);
}

/**
 * \brief   This function reads the compensation value being set in the 
 *          compensation registers. \n
 *
 * \param   baseAdd   The base address of the RTC instance being used.\n
 *
 * \return  The value in the compensation registers COMPMSB and COMPLSB.
 *
 * \note    This returns the two's complement value of the number to be 
 *          subtracted from 32KHz period. Refer to \note of 
 *          \RTCCompensationSet  API for more details.
 */

unsigned int RTCCompensationGet(unsigned int baseAdd)
{
    unsigned int compVal = 0;

    /* Reading from the COMPLSB register.*/
    compVal = (HWREG(baseAdd + RTC_COMPLSB) & COMP_LOW_MASK);

    /* Reading from the COMPMSB register.*/
    compVal |= ((HWREG(baseAdd + RTC_COMPMSB) & 0xFF) << COMP_SHIFT);

    return compVal;
}



/**
 * \brief   This function writes the specified arbitrary value to the specified
 *          scratch register. \n
 *
 * \param   baseAdd       The base address of the RTC instance being used.\n
 * \param   regNumber     This specifies the scratch register number to be
 *                        accessed. This can take the values: 0, 1 or 2. \n
 * \param   scratchValue  Refers to the value to be written to the scratch 
 *                        registers. \n
 *
 * \return  None.
 *
 */

void RTCScratchPadSet(unsigned int baseAdd, unsigned int regNumber, 
                      unsigned int scratchValue)
{
    unsigned int offset = 0;

    offset = regNumber * 4;
    HWREG(baseAdd + RTC_SCRATCH0 + offset) = scratchValue;
}

/**
 * \brief   This function reads the value stored in a specified scratch
 *          register. \n
 * 
 * \param   baseAdd  The base address of the RTC instance being used.\n
 * \param   regNumber Specifies the scratch register number to be accessed.
 *                    This can take the values: 0, 1 or 2. \n
 *
 * \return  None. \n
 *
 */
unsigned int RTCScratchPadGet(unsigned int baseAdd, unsigned int regNumber)
{
    unsigned int offset = 0;
 
    offset = regNumber * 4;
    return(HWREG(baseAdd + RTC_SCRATCH0 + offset));
}

/*****************************************************************************
**  APIs specific to RTC IP of AM1808 and not applicable for that in AM335x.
*****************************************************************************/
/**
 * \brief   This function resets the RTC module and registers except
 *          Oscillator(OSC) and KICKnR registers. \n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None.
 *
 * \note    1> When the device is initially powered on, the RTC may issue
 *             spurious interrupt signals to the CPU. To avoid issues,
 *             a software reset should be performed on the RTC module before
 *             the CPU interrupt controller is initialized.\n
 *
 *          2> Registers must not be accessed for three 32-KHz reference
 *             periods after reset is asserted. The application invoking
 *             this API should provide an appropriate delay after this
 *             API's call.\n
 *
 */
void RTCSoftwareReset(unsigned int baseAdd)
{
    HWREG(baseAdd + RTC_OSC) |= RTC_OSC_SWRESET;
}

/****************************************************************************/

/*****************************************************************************
**  APIs specific to RTC IP of AM335x and not applicable for that in AM1808.
*****************************************************************************/

/**
 * \brief   This API gets the Revision Identity of the RTC Module.
 *
 * \param   baseAdd  The base address of the RTC instance being used.
 *
 * \return  The Revision Identity of the RTC Module.
 */

unsigned int RTCRevisionIDGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_REVISION));
}

/**
 * \brief   This API configures the Idle Mode for the RTC.
 *
 * \param   baseAdd  The base address of the RTC instance being used.
 * \param   modeFlag  This specifies the idle mode that is to be enabled.
 *
 * 'modeFlag' can take one of the following four values:
 * - RTC_IDLEMODE_FORCE_IDLE - to enable Force-Idle mode\n
 * - RTC_IDLEMODE_NO_IDLE - to enable No-Idle mode\n
 * - RTC_IDLEMODE_SMART_IDLE - to enable Smart-Idle mode\n
 * - RTC_IDLEMODE_SMART_IDLE_WAKEUP - to enable Smart-Idle Wakeup-capable mode\n
 *
 * \return  None
 */

void RTCIdleModeConfigure(unsigned int baseAdd, unsigned int modeFlag)
{
    /* Clearing the IDLEMODE field in RTC_SYSCONFIG register. */
    HWREG(baseAdd + RTC_SYSCONFIG) &= ~(RTC_SYSCONFIG_IDLEMODE);

    /* Programming the IDLEMODE field in RTC_SYSCONFIG register. */
    HWREG(baseAdd + RTC_SYSCONFIG) |= (modeFlag &
                                       RTC_SYSCONFIG_IDLEMODE);
}

/**
 * \brief  This API is used to control(enable/disable) the feature where
 *         ALARM events can trigger a Wake-up signal to the CPU.
 *
 * \param  baseAdd      The base address of the RTC instance being used.
 * \param  controlFlag  This specifies whether to enable/disable the feature
 *                       where an Alarm event shall trigger a Wake-Up signal to
 *                       the CPU.
 *
 * 'controlFlag' can take one of the following values:
 * - RTC_ALARM_WAKEUP_ENABLE - to trigger a Wake-Up signal on an Alarm event\n
 * - RTC_ALARM_WAKEUP_DISABLE - to not trigger a Wake-Up signal on an Alarm
 *   event\n
 *
 * \return  None
 *
 * \note  The ALARM_WAKEEN bit in RTC_IRQWAKEEN register which this API controls,
 *        caters only to ALARM feature and not ALARM2 feature.
 */

void RTCWakeUpAlarmEventControl(unsigned int baseAdd, unsigned int controlFlag)
{
    /* Clearing the ALARM_WAKEEN field of RTC_IRQWAKEEN register. */
    HWREG(baseAdd + RTC_IRQWAKEEN) &= ~(RTC_IRQ_WAKEEN_ALARM_WAKEEN);

    /* Programming the ALARM_WAKEEN field of RTC_WAKEEN register. */
    HWREG(baseAdd + RTC_IRQWAKEEN) |= (controlFlag &
                                       RTC_IRQ_WAKEEN_ALARM_WAKEEN);
}

/**
 * \brief  This API is used to control(enable/disable) the feature where
 *         Timer events can trigger a Wake-Up signal to the CPU.
 *
 * \param   baseAdd      The base address of the RTC instance being used.\n
 * \param   controlFlag  This specifies whether to enable/disable the feature
 *                       where a Timer event shall trigger a Wake-Up signal
 *                       to the CPU.
 *
 * 'controlFlag' can take one of the following values:
 * - RTC_TIMER_WAKEUP_ENABLE - to trigger a Wake-Up signal on a Timer event\n
 * - RTC_TIMER_WAKEUP_DISABLE - to not trigger a Wake-Up signal on a Timer
 *   event\n
 *
 * \return  None
 */ 

void RTCWakeUpTimerEventControl(unsigned int baseAdd, unsigned int controlFlag)
{
    /* Clearing the TIMER_WAKEEN field of RTC_WAKEEN register. */
    HWREG(baseAdd + RTC_IRQWAKEEN) &= ~(RTC_IRQ_WAKEEN_TIMER_WAKEEN);

    /* Programming the TIMER_WAKEEN field of RTC_WAKEEN register. */
    HWREG(baseAdd + RTC_IRQWAKEEN) |= (controlFlag &
                                       RTC_IRQ_WAKEEN_TIMER_WAKEEN);
}

/**
 * \brief   This API controls(enables/disables) the Test mode functionality
 *          of the RTC.
 *
 * \param   baseAdd      The base address of the RTC instance being used\n
 * \param   controlFlag  This specifies whether to enable or disable Test
 *                       Mode functionality
 *
 * 'controlFlag' can take one of the following values:\n
 * - RTC_FUNCTIONAL_MODE_ENABLE - to disable Test Mode and thus enabling
 *   normal functional mode\n
 * - RTC_TEST_MODE_ENABLE - to enable Test Mode\n
 *
 * \return  None
 */

void RTCTestModeControl(unsigned int baseAdd, unsigned int controlFlag)
{
    /* Clearing the TEST_MODE field in RTC_CTRL register. */
    HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_TEST_MODE);

    /* Setting the TEST_MODE bit of RT Control Register. */
    HWREG(baseAdd + RTC_CTRL) |= (controlFlag & RTC_CTRL_TEST_MODE);
}

/**
 * \brief  This API selects the clock source for the RTC module.
 *         RTC can be supplied with a 32.768KHz clock either from an
 *         Internal clock source or an External clock source.
 *
 * \param  baseAdd     The base address of the RTC instance being used
 * \param  clkSrcFlag  This specifies the RTC Clock source to be selected
 *
 * 'clkSrcFlag' can take one of the following two values:
 * - RTC_INTERNAL_CLK_SRC_SELECT - to select the Internal Clock source\n
 * - RTC_EXTERNAL_CLK_SRC_SELECT - to select the External Clock source\n
 *
 * \return None
 */

void RTC32KClkSourceSelect(unsigned int baseAdd, unsigned int clkSrcFlag)
{
    /* Clearing the 32KCLK_SEL bit in Oscilltor register. */
    HWREG(baseAdd + RTC_OSC) &= ~(RTC_OSC_32KCLK_SEL);

    /* Programming the 32KCLK_SEL bit in Oscillator register. */
    HWREG(baseAdd + RTC_OSC) |= (clkSrcFlag & RTC_OSC_32KCLK_SEL);

    if(RTC_EXTERNAL_CLK_SRC_SELECT == clkSrcFlag)
    {
        /* Clearing the OSC32K_GZ field in RTC_OSC register. */
        HWREG(baseAdd + RTC_OSC) =
              ((HWREG(baseAdd + RTC_OSC) & (~RTC_OSC_OSC32K_GZ)) |
               (RTC_OSC_OSC32K_GZ_ENABLE << RTC_OSC_OSC32K_GZ_SHIFT));
    }
}

/**
 * \brief This API controls(enables/disables) the RTC to receive clocks
 *        from the selected clock source.
 *
 * \param  baseAdd      The base address of the RTC instance being used
 * \param  controlFlag  This specifies whether to enable or disable the
 *                      RTC to receive clock inputs from the selected
 *                      clock source.
 *
 * 'controlDFlag' can take one of the following values:
 * - RTC_32KCLK_ENABLE - to enable RTC to receive clock inputs\n
 * - RTC_32KCLK_DISABLE - to disable RTC to receive clock inputs\n
 *
 * \return None
 *
 * \note  The RTC Clock source(Internal or External) should be selected
 *        using the API RTC32KClkSourceSelect() before invoking this API.
 */

void RTC32KClkClockControl(unsigned int baseAdd, unsigned int controlFlag)
{
    /* Clearing the 32KCLK_EN bit in RTC_OSC register. */
    HWREG(baseAdd + RTC_OSC) &= ~(RTC_OSC_32KCLK_EN);

    /* Programming the 32KCLK_EN bit in RTC_OSC register. */
    HWREG(baseAdd + RTC_OSC) |= (controlFlag & RTC_OSC_32KCLK_EN);
}

/**
 * \brief This API is used to control(enable/disable) the use of External
 *        Oscillator for RTC.
 *
 * \param  baseAdd      The base address of the RTC instance being used
 * \param  controlFlag  This specifies whether to enable or disable the
 *                      use of the External Oscillator for the RTC.
 *
 * 'controlFlag' can take one of the following two values:
 * - RTC_32KOSC_ENABLE - to enable the External Oscillator\n
 * - RTC_32KOSC_DISABLE - to disable the External Oscillator. Disabling
 *   the Oscillator would drive the Oscillator outputs to High Impedance.
 *
 * \return None
 */

void RTCOscillatorStateControl(unsigned int baseAdd, unsigned int controlFlag)
{
    /* Clearing the OSC32K_GZ bit in Oscillator register. */
    HWREG(baseAdd + RTC_OSC) &= ~(RTC_OSC_OSC32K_GZ);

    /* Programming the OSC32K_GZ bit in Oscillator register. */
    HWREG(baseAdd + RTC_OSC) |= (controlFlag & RTC_OSC_OSC32K_GZ);
}

/**
 * \brief  This selects the mode of the Oscillator Feedback resistor.
 *         The Oscillator Feedback resistor could be either external or
 *         internal to the SoC.
 *
 * \param  baseAdd      The base address of the RTC instance being used
 * \param  selectFlag   This specifies whether the Oscillator Feedback
 *                      resistor to be used should be either external or
 *                      internal to the SoC.
 *
 * 'selectFlag' can take one of the following two values:
 * - RTC_INTERNAL_FEEDBACK_RES_SEL - to select an internal oscillator
 *   feedback resistor for use\n
 * - RTC_EXTERNAL_FEEDBACK_RES_SEL - to select an external oscillator
 *   feedback resistor for use\n
 *
 * \return None
 */

void RTCFeedbackResistanceSelect(unsigned int baseAdd, unsigned int selectFlag)
{
    /* Clearing the RES_SELECT bit in Oscillator register. */
    HWREG(baseAdd + RTC_OSC) &= ~(RTC_OSC_RES_SELECT);

    /* Programming the RES_SELECT bit in Oscillator register. */
    HWREG(baseAdd + RTC_OSC) |= (selectFlag & RTC_OSC_RES_SELECT);

}

/**
 * \brief  This API configures the PMIC power Enable signal
 *
 * \param  baseAdd      The base address of the RTC instance being used
 * \param  selectFlag   This specifies whether the PMIC power enable signal has
 *                      to be pulled low or high.
 *
 * 'selectFlag' can take one of the following two values:
 * - RTC_PMIC_PWR_ENABLE - to enable PMIC power\n
 * - RTC_PMIC_PWR_DISABLE - to disable PMIC power\n
 *
 * \return None
 */

void RTCConfigPmicPowerEnable(unsigned int baseAdd, unsigned int selectFlag)
{
    /* Clear the PMIC enable flag. */
    HWREG(baseAdd + RTC_PMIC) &= ~(RTC_PMIC_PWR_ENABLE_EN);

    /* Write the value passed by the user. */
    HWREG(baseAdd + RTC_PMIC) |= (selectFlag & RTC_PMIC_PWR_ENABLE_EN);
}

/**
 * \brief  This API configures the Polarity of PMIC External Wakeup pin
 *
 * \param  baseAdd      The base address of the RTC instance being used
 * \param  extInput     The external Input pin to be configured
 * \param  selectFlag   This specifies whether the PMIC External Wakeup Polarity
 *                      to be low or high.
 *
 * 'extInput' can take values from 0 to 3
 *
 * 'selectFlag' can take one of the following two values:
 * - RTC_EXT_WAKEUP_POL_ACTIVE_HIGH - to set polarity High\n
 * - RTC_EXT_WAKEUP_POL_ACTIVE_LOW  - to set polarity Low\n
 *
 * \return None
 */

void RTCConfigPmicExtWakePolarity(unsigned int baseAdd, unsigned int extInput,
                                  unsigned int selectFlag)
{
    /* Clear the PMIC External Wakeup pin Polarity flag. */
    HWREG(baseAdd + RTC_PMIC) &=
                            ~((1 << extInput) << RTC_PMIC_EXT_WAKEUP_POL_SHIFT);

    /* Write the value passed by the user. */
    HWREG(baseAdd + RTC_PMIC) |= (RTC_PMIC_EXT_WAKEUP_POL &
                   ((selectFlag << extInput) << RTC_PMIC_EXT_WAKEUP_POL_SHIFT));
}

/**
 * \brief  This API configures the PMIC External Wakeup
 *
 * \param  baseAdd      The base address of the RTC instance being used
 * \param  extInput     The external Input pin to be configured
 * \param  selectFlag   This specifies whether the PMIC External Wakeup
 *                      to be enabled or disabled.
 *
 * 'extInput' can take values from 0 to 3
 *
 * 'selectFlag' can take one of the following two values:
 * - RTC_EXT_WAKEUP_ENABLE  - to enable\n
 * - RTC_EXT_WAKEUP_DISABLE - to disable\n
 *
 * \return None
 */

void RTCConfigPmicExtWake(unsigned int baseAdd, unsigned int extInput,
                          unsigned int selectFlag)
{
    /* Clear the PMIC External Wakeup flag. */
    HWREG(baseAdd + RTC_PMIC) &=
                             ~((1 << extInput) << RTC_PMIC_EXT_WAKEUP_EN_SHIFT);

    /* Write the value passed by the user. */
    HWREG(baseAdd + RTC_PMIC) |= (RTC_PMIC_EXT_WAKEUP_EN &
                    ((selectFlag << extInput) << RTC_PMIC_EXT_WAKEUP_EN_SHIFT));
}

/**
 * \brief  This API configures the debounce for PMIC External Wakeup pin
 *
 * \param  baseAdd      The base address of the RTC instance being used
 * \param  extInput     The external Input pin to be configured
 * \param  selectFlag   This specifies whether debounce of External Wakeup pin
 *                      to be enabled or disabled.
 *
 * 'extInput' can take values from 0 to 3
 *
 * 'selectFlag' can take one of the following two values:
 * - RTC_EXT_WAKEUP_DB_ENABLE  - to enable\n
 * - RTC_EXT_WAKEUP_DB_DISABLE - to disable\n
 *
 * \return None
 */

void RTCConfigPmicExtWakeDebounce(unsigned int baseAdd, unsigned int extInput,
                                  unsigned int selectFlag)
{
    /* Clear the PMIC External Wakeup pin Debounce flag. */
    HWREG(baseAdd + RTC_PMIC) &=
                          ~((1 << extInput) << RTC_PMIC_EXT_WAKEUP_DB_EN_SHIFT);

    /* Write the value passed by the user. */
    HWREG(baseAdd + RTC_PMIC) |= (RTC_PMIC_EXT_WAKEUP_DB_EN &
                 ((selectFlag << extInput) << RTC_PMIC_EXT_WAKEUP_DB_EN_SHIFT));
}

/**
 * \brief  This API clears the PMIC External Wakeup Status
 *
 * \param  baseAdd      The base address of the RTC instance being used
 * \param  extInput     The external Input pin to be configured
 *
 * 'extInput' can take values from 0 to 3
 *
 * \return None
 */

void RTCPmicExtWakeStatusClear(unsigned int baseAdd, unsigned int extInput)
{
    HWREG(baseAdd + RTC_PMIC) |= (RTC_PMIC_EXT_WAKEUP_STATUS &
                         ((1 << extInput) << RTC_PMIC_EXT_WAKEUP_STATUS_SHIFT));
}

/**
 * \brief   This function enables ALARM2 interrupts.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None. \n
 *
 * \note    If the RTC is busy in updating its registers, then this API waits
 *          until this update is complete. \n
 *
 */

void RTCIntAlarm2Enable(unsigned int baseAdd)
{
    /*
    ** Writing to INTERRUPT register requires that BUSY bit in STATUS register
    ** is low.
    */
    while(IS_RTC_BUSY);

    HWREG(baseAdd + RTC_INTERRUPT) |= RTC_INTERRUPTS_ALARM2;
}

/**
 * \brief   This function indicates whether RTC ALARM2 interrupt has been
 *          generated or not.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  This function returns either of the below two values:\n
 *          RTC_NEW_ALARM2_INTERRUPT - indicating that a new ALARM2 interrupt
 *          has been generated.\n
 *          RTC_NO_NEW_ALARM2_INTERRUPT - indicating that no new ALARM2
 *          interrupt has been generated. \n
 */

unsigned int RTCAlarm2IntStatusGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + RTC_STATUS) & RTC_STATUS_ALARM2);
}

/**
 * \brief   This function clears the ALARM2 interrupt's status.\n
 *
 * \param   baseAdd  The base address of the RTC instance being used.\n
 *
 * \return  None.\n
 */

void RTCAlarm2IntStatusClear(unsigned int baseAdd)
{
    /*
    ** Writing logic 1 to the ALARM2 bit in STATUS register clears the ALARM2
    ** interrupt status.
    */
    HWREG(baseAdd + RTC_STATUS) |= RTC_STATUS_ALARM2;
}

/**
 * \brief  This function sets the ALARM2 time registers with the specified
 *         alarm time value.
 *
 * \param  baseAdd   The base address of the RTC instance being used.\n
 * \param  alarmTime  The time is specified here and should be in the
 *                    following format: <hours><minutes><seconds><meridiem>.\n
 *                    Example - For 12-hour mode representation:\n
 *                    If the time is 01 hours, 29 minutes and 43 seconds PM,
 *                    then the 'alarmTime' should be
 *                    (0x01294300 | RTC_POST_MERIDIEM). \n
 *                    For 24-hour mode representation:\n
 *                    If the time is 23 hours, 48 minutes, 08 seconds, then
 *                    'alarmTime' should be (0x23480800).\n
 *
 * \note   If the RTC is busy in updating its registers, then this API waits
 *         until this update is complete. \n
 */

void RTCAlarm2TimeSet(unsigned int baseAdd, unsigned int alarmTime)
{
    while(IS_RTC_BUSY);

    /* Writing to RTC_ALARM2_SECONDS register. */
    HWREG(baseAdd + RTC_ALARM2_SECONDS) = (alarmTime & SECOND_MASK) >> SECOND_SHIFT;

    /* Writing to RTC_ALARM2_MINUTES register. */
    HWREG(baseAdd + RTC_ALARM2_MINUTES) = (alarmTime & MINUTE_MASK) >> MINUTE_SHIFT;

    /* Writing to RTC_ALARM2_HOURS register. */
    HWREG(baseAdd + RTC_ALARM2_HOURS) = (((alarmTime & HOUR_MASK) >> HOUR_SHIFT) |
                                         (alarmTime & MERIDIEM_MASK));
}

/**
 * \brief  This sets the ALARM2 calendar registers of the RTC with the specified
 *         alarm calendar information. \n
 *
 * \param  baseAdd  The base address of the RTC instance being used.\n
 * \param  calVal   This parameter includes values for day of the month,
 *                  month and  year. The format is:
 *                  <day of the month><month><year>.
 *                  For example, if the ALARM2 calendar registers are to be
 *                  loaded with a date namely 31 December, 1945, then
 *                  'calVal' should be 0x31124500(December=12, 1945=45)
 *
 * \return None. \n
 *
 * \note   If the RTC is busy in updating its registers, then this API waits
 *         until this update is complete. \n
 */

void RTCAlarm2CalendarSet(unsigned int baseAdd, unsigned int calVal)
{
    while(IS_RTC_BUSY);

    /* Writing to RTC_ALARM2_YEARS register.*/
    HWREG(baseAdd + RTC_ALARM2_YEARS) = (calVal & YEAR_MASK) >> YEAR_SHIFT;

    /* Writing to RTC_ALARM2_MONTHS register.*/
    HWREG(baseAdd + RTC_ALARM2_MONTHS) = (calVal & MONTH_MASK) >> MONTH_SHIFT;

    /* Writing to RTC_ALARM2_DAYS register.*/
    HWREG(baseAdd + RTC_ALARM2_DAYS) = (calVal & DAY_MASK) >> DAY_SHIFT;
}

/*****************************************************************************
**                      End of APIs specific to AM335x                       
*****************************************************************************/

/************************* End of file ***************************************/
