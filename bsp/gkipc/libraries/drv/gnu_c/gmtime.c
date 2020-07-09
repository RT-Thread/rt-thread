/*
********************************************************************************
**
** \file        ./boot/startup/src/gmtime.c
**
** \version     $Id: gmtime.c 6304 2016-03-18 03:39:06Z chenke $
**
** \brief       ARM1176 RealView libc function retargeting.
**
** This files retargets the time-specific function gmtime().
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

#include <stdint.h>
//#include <errno_ext.h>
#include <errno.h>
#include <string.h>
//#include <time_ext.h>
#include <time.h>
#include <internal.h>

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

static struct tm _gmtime_tm;

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
** \brief Retarget implementation of the stdc library function.
**
** This is the standard C library gmtime() function from time.h.
**
** The gmtime() function shall convert the time in seconds since the epoch
** pointed to by timer into a broken-down time, expressed as coordinated
** universal time (UTC).
**
** The relationship between a time in seconds since the Epoch used as an
** argument to gmtime() and the tm structure (defined in the <time.h> header) is
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
** \return Upon successful completion, the gmtime() function shall return a
** pointer to a struct tm. If an error is detected, gmtime() shall return a null
** pointer and set errno to indicate the error.
** ERRORS:
**    - EOVERFLOW The result cannot be represented.
********************************************************************************
*/
struct tm * gmtime(const time_t *timer)
{
    struct tm *tm = &_gmtime_tm;
    uint32_t cpu_flags;

    /* check parameter validity */
    if (timer == NULL) {
        return (NULL);
    }

    /* irrespective of values sign representation, high bit set in time_t leads
       to an invalid (overflow) result */
    if (IS_HIGH_BIT_SET(*timer)) {
        /*lint -e{48,63} */
        errno = EOVERFLOW;
        return (NULL);
    }

    //////////////////////////////////
    cpu_flags = st_enter_crit_func();
    //////////////////////////////////

    /* reset local time structure */
    memset(tm, 0x0, sizeof(struct tm));

    /* fill up time based on epoch using given seconds */
    tm->tm_year = 70;
    tm->tm_mday = 1;
    tm->tm_sec =  (int) *timer;

    /* normalize data */
    /*lint -e(586) */
    mktime(tm);

    //////////////////////////////
    st_exit_crit_func(cpu_flags);
    //////////////////////////////

    return (tm);
}

