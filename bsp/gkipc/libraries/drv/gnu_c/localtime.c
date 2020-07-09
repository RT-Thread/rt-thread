/*
********************************************************************************
**
** \file        ./boot/startup/src/localtime.c
**
** \version     $Id: localtime.c 6304 2016-03-18 03:39:06Z chenke $
**
** \brief       ARM1176 RealView libc function retargeting.
**
** This files retargets the time-specific function localtime().
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. FUJITSU MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS.
**
** (C) Copyright 2006-2010 by Fujitsu Microelectronics Europe GmbH
** (C) Copyright 2010 by Fujitsu Semiconductor Europe GmbH
**
********************************************************************************
**
** \note The following LINT statements have been suppressed:
**
** - Warning 438: Last value assigned to variable not used.
** - Warning 586: function 'mktime' is deprecated. [MISRA 2004 Rule 20.12]
** - Note 961: Violates MISRA 2004 Advisory Rule 19.7, Function-like macro
**             defined
*****************************************************************************
*/

//**************************************************************************
//**************************************************************************
//** Standard includes
//**************************************************************************
//**************************************************************************
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "internal.h"
#include "errno.h"

//**************************************************************************
//**************************************************************************
//** FAPI includes
//**************************************************************************
//**************************************************************************


//**************************************************************************
//**************************************************************************
//** Defines and Macros
//**************************************************************************
//**************************************************************************

/*lint -save -e(961) */
#define IS_HIGH_BIT_SET(val) (((1LL << ((sizeof(val) * 8) - 1)) & val) != 0)
/*lint -restore */

//**************************************************************************
//**************************************************************************
//** Global Data
//**************************************************************************
//**************************************************************************

static struct tm _localtime_tm;

//******************************************************************************
//******************************************************************************
//** Local Functions Declaration
//******************************************************************************
//******************************************************************************
int _is_dst(time_t t);

//******************************************************************************
//******************************************************************************
//** API Functions
//******************************************************************************
//******************************************************************************

/*
********************************************************************************
** \brief Retarget implementation of the stdc library function.
**
** This is the standard C library gmtime() function from time.h.
**
** The localtime() function shall convert the time in seconds since the epoch
** pointed to by timer into a broken-down time, expressed as a local time.
** The function corrects for the timezone and any seasonal time adjustments.
** Local timezone information is used as though localtime() calls tzset().
**
** The relationship between a time in seconds since the Epoch used as an
** argument to localtime() and the tm structure (defined in the <time.h> header) is
** that the result shall be as specified in the expression given in the
** definition of seconds since the Epoch (see the Base Definitions volume of
** IEEE Std 1003.1-2001, Section 4.14, Seconds Since the Epoch), where the names
** in the structure and in the expression correspond.
**
** The asctime(), ctime(), gmtime(), and localtime() functions shall return
** values in one of two static objects: a broken-down time structure and an
** array of type char. Execution of any of the functions may overwrite the
** information returned in either of these objects by any of the other
** functions.
**
** \param timer Pointer to time in seconds since the epoch (00:00:00 UTC on
** 1 January 1970)
**
** \return Upon successful completion, the localtime() function shall return a
** pointer to the broken-down time structure. If an error is detected,
** localtime() shall return a null pointer and set errno to indicate the error.
** ERRORS:
**    - EOVERFLOW The result cannot be represented.
********************************************************************************
*/

struct tm * localtime_r(const time_t *timer,struct tm * tmp)
{
    struct tm *tm = tmp;
    uint32_t cpu_flags;

    /* check parameter validity */
    if (timer == NULL) {
        return (NULL);
    }

    /* check parameter validity */
    if (tm == NULL) {
        return (NULL);
    }


    /* irrespective of values sign representation, high bit set in time_t leads
       to an invalid (overflow) result */
    if (IS_HIGH_BIT_SET(*timer)) {
        /*lint -e{48,63} */
        errno = EOVERFLOW;
        return (NULL);
    }

    /* update time zone values based on environment variable TZ */
    tzset();

    //////////////////////////////////
    cpu_flags = st_enter_crit_func();
    //////////////////////////////////

    /* reset local time structure */
    memset(tm, 0x0, sizeof(struct tm));

    /* fill up time based on epoch using given seconds */
    tm->tm_year = 70;
    tm->tm_mday = 1;
    tm->tm_sec = (int) *timer - (int) _timezone;  /* ignore DST offset first */
    tm->tm_isdst = _is_dst((time_t) tm->tm_sec);
    if (tm->tm_isdst) {                           /* do DST correction */
        tm->tm_sec -= (int) _daylight;
    }

    /* check if overflow has happened */
    /* irrespective of values sign representation, high bit set leads to an
       invalid (overflow) result */
    if (IS_HIGH_BIT_SET(tm->tm_sec)) {
        /*lint -e{48,63} */
        errno = EOVERFLOW;
        return (NULL);
    }

    /* normalize data */
    /*lint -e(586) */
    mktime(tm);

    //////////////////////////////
    st_exit_crit_func(cpu_flags);
    //////////////////////////////

    return (tm);
}

//******************************************************************************
//******************************************************************************
//** Local Functions
//******************************************************************************
//******************************************************************************

/*
********************************************************************************
** \brief Determines if the daylight savings time should be applied.
**
** This function should normally implement the various DST rules applied to
** different timezones, which would imply extensive calculation.
**
** \attention The current implementation is very limited, simply informing if
** the DST is activated in the TZ variable.
** This means this implementation only works correct if the current time zone
** value is updated accordingly.
**
** \param now defines the current timestamp, where DST is checked to be applied.
**
** \return
**      - 1, if actual time stamp is in DST range
**      - 0, otherwise
********************************************************************************
*/
/*lint -e{438} */
int _is_dst(time_t now)
{
    now = now;
    if (!_daylight) {
        return (0);
    }

    return (1);
}



struct tm * localtime(const time_t *timer)	
{
	return localtime_r(timer,&_localtime_tm);
}

