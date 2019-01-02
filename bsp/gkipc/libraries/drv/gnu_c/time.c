/*
********************************************************************************
**
** \file        ./boot/startup/src/time.c
**
** \version     $Id: time.c 6426 2016-03-22 05:49:59Z liuwei $
**
** \brief       ARM1176 RealView libc function retargeting.
**
** This files general (compiler independent) time specific retargets.
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
**
*****************************************************************************
*/
#include <rtthread.h>

#include <sys/time.h>
#include <time.h>
#include "internal.h"


/* Checks if a type is signed or unsigned */
/*lint -emacro((506), IS_SIGNED) */
/*lint -e(961) */
#define IS_SIGNED(type) (((type) -1) < 0)

/* Calculates maximum positive value for given scalar type with respect */
/*lint -e(961) */
#define POSITIVE_MAX_OF_TYPE(type)                                          \
    ((type) (IS_SIGNED(type) ?                                              \
                                ((1LL << ((sizeof(type) * 8) - 1)) - 1) :   \
                                (-1)))

/* Precalculate maximum type positive type values */
#define Int64TMax (9223372036854775807LL)

static const clock_t ClockTMax = (POSITIVE_MAX_OF_TYPE(clock_t));

#if defined(__arm__) && !defined(__GNUC__) /* RVCT v3- */
    static const time_t TimeTMax = (POSITIVE_MAX_OF_TYPE(time_t) - 1);
#else
    static const time_t TimeTMax = (POSITIVE_MAX_OF_TYPE(time_t));
#endif

static int64_t systemTimeBase = 0LL;


static int32_t get_system_time( time_t *time )
{
    int32_t rc = 0;
    uint64_t ts = rt_tick_get()/1000; //seconed

    /* check input parameter */
    if (time == NULL) {
        rc = -1;
    }
    /* check for time overflow */
    else if ((ts > Int64TMax) ||    /* pre-check downcast precision loss */
        ((int64_t) ts > ((int64_t) TimeTMax - systemTimeBase))) {
        rc = -1;
    }
    else {
        *time = (time_t) (systemTimeBase + (int64_t) ts);
    }

    return (rc);
}



/*
********************************************************************************
** \brief Retarget implementation of the stdc library function.
**
** This is the standard C library clock() function from time.h.
**
** This function returns the implementation's best approximation to the
** processor time used by the program since program invocation.
**
** \return Returns elapsed processor time used by program. The time in seconds
** is the value returned divided by the value of the macro CLOCKS_PER_SEC.
** The value ((clock_t) -1) is returned if the processor time used is
** not available or invalid.
********************************************************************************
*/
clock_t clock(void)
{
    clock_t c;

    if (get_system_time((time_t*)&c) != 0) {
        c = (clock_t) -1;
    }

    return (c);
}

/*
********************************************************************************
** \brief Retarget implementation of the stdc library function.
**
** This is the standard C library time() function from time.h.
**
** This function returns an approximation of the current calendar time.
**
** \param timer Return value resource for time_t. If timer is not a
** NULL pointer, the return value is also assigned to the time_t*.
**
** \return Returns current calendar time, which represents the number of seconds
** elapsed since 00:00:00 on January 1, 1970, Coordinated Universal Time.
** (This date is sometimes referred to as the epoch.)
** The value ((time_t) -1) is returned if the calendar time is not available.
********************************************************************************
*/
time_t time(time_t * timer)
{
    time_t tv;

    if (get_system_time(&tv) != 0) {
        tv = (time_t) -1;
    }

    if (timer) {
        *timer = tv;
    }

    return (tv);
}

int gettimeofday(struct timeval *tp, void *tzvp)
{
    time_t tvl;
    get_system_time(&tvl);
    tp->tv_sec = tvl;
    tp->tv_usec = (rt_tick_get()%1000) * 1000;
    return (0);
}

int settimeofday(const struct timeval *tv, const struct timezone *tz)
{
    if(tv )
        systemTimeBase = tv->tv_sec + tv->tv_usec/1000000 - rt_tick_get()/1000;
    return 0;

}


