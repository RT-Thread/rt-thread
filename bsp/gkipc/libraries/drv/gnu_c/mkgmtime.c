/*
********************************************************************************
**
** \file        ./boot/startup/src/mktime.c
**
** \version     $Id: mkgmtime.c 6392 2016-03-21 09:20:06Z liuwei $
**
** \brief       ARM1176 RealView libc function retargeting.
**
** This files implements the time-specific extension function mkgmtime().
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
** - Warning 586: function 'mktime' is deprecated. [MISRA 2004 Rule 20.12]
**
*****************************************************************************
*/

//**************************************************************************
//**************************************************************************
//** Standard includes
//**************************************************************************
//**************************************************************************

#include <string.h>
#include <time.h>
#include <internal.h>

//**************************************************************************
//**************************************************************************
//** FAPI includes
//**************************************************************************
//**************************************************************************

//#include <fapi/sys_services.h>

//**************************************************************************
//**************************************************************************
//** Defines and Macros
//**************************************************************************
//**************************************************************************

#define TZ_DEFAULT_DST_OFFSET    -3600    // in seconds (see same value in tzset)

//**************************************************************************
//**************************************************************************
//** Global Data
//**************************************************************************
//**************************************************************************

//******************************************************************************
//******************************************************************************
//** Local Functions Declaration
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//** API Functions
//******************************************************************************
//******************************************************************************

/*
********************************************************************************
** \brief Implementation of the stdc library extension function.
**
** This is the standard C library extension function mkgmtime() from time_ext.h.
**
** The mkgmtime() function shall convert the broken-down time structure
** representing local time to the seconds since the Epoch expressed as
** coordinated universal time (UTC).
**
** \param tm Pointer to the broken-down time structure representing local time.
**
** \return The mkgmtime() function shall return the specified time since the
** Epoch encoded as a value of type time_t, where this value represents the time
** based on UTC. If the time since the Epoch cannot be represented, the function
** shall return the value (time_t)-1.
********************************************************************************
*/
time_t mkgmtime(struct tm *tm)
{
    time_t t;

    /* check parameter validity */
    if (tm == NULL) {
        return (time_t) (-1);
    }

    /* retrieve seconds since epoch of given local time and normalize data */
    t = /*lint -e(586) */ mktime(tm);

    /* apply time tone shift */
    t += (time_t) _timezone;

    /* check, which TZ offset (std or dst) should be applied and return */
    if ((*tzname[1] != '\0') && (tm->tm_isdst > 0)) {
        t += (time_t) _daylight;
    }

    return (time_t) (t);
}

