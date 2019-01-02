/*
********************************************************************************
**
** \file        ./boot/startup/src/tzset.c
**
** \version     $Id: tzset.c 6304 2016-03-18 03:39:06Z chenke $
**
** \brief       ARM1176 RealView libc function retargeting.
**
** This files retargets the time zone specific function tzset().
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

//**************************************************************************
//**************************************************************************
//** Standard includes
//**************************************************************************
//**************************************************************************

//#include <stdchar.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include <time_ext.h>
#include <time.h>
#include "internal.h"

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
#ifndef TZNAME_MAX
    #define TZNAME_MAX              16
#endif

#define TZ_DEFAULT              "GMT0"
#define TZ_INIT_STD_OFFSET      0L          // in seconds
#define TZ_INIT_STD_NAME        "GMT"
#define TZ_INIT_DST_OFFSET      0           // in seconds
#define TZ_INIT_DST_NAME        ""
#define TZ_DEFAULT_DST_OFFSET   -3600        // in seconds


//**************************************************************************
//**************************************************************************
//** Global Data
//**************************************************************************
//**************************************************************************
static char _stdname[TZNAME_MAX] = TZ_INIT_STD_NAME;
static char _dstname[TZNAME_MAX] = TZ_INIT_DST_NAME;
char * _tzname[2] = { _stdname, _dstname };
long _timezone = TZ_INIT_STD_OFFSET;
int _daylight  = TZ_INIT_DST_OFFSET;

//******************************************************************************
//******************************************************************************
//** Local Functions Declaration
//******************************************************************************
//******************************************************************************
static size_t scanTzString(char_t **tz, char_t *name);
static int8_t scanTzOffset(char_t **tz, int32_t *offset);

//******************************************************************************
//******************************************************************************
//** API Functions
//******************************************************************************
//******************************************************************************

/*
********************************************************************************
** \brief Retarget implementation of the stdc library function.
**
** This is the standard C library tzset() function from time.h.
**
** The tzset() function shall use the value of the environment variable TZ to
** set time conversion information used by ctime(), localtime(), mktime() and
** strftime().
** The tzset() function also shall set the external variable daylight to 0
** if daylight savings time (DST) conversions should never be applied for the
** timezone in use; otherwise, non-zero. The external variable timezone shall be
** set to the difference, in seconds, between coordinated universal time (UTC)
** and local standard time.
********************************************************************************
*/
void tzset( void )
{
    char_t *tzdefault = TZ_DEFAULT;
    char_t std_name[TZNAME_MAX];
    char_t dst_name[TZNAME_MAX];
    int32_t std_offset = TZ_INIT_STD_OFFSET;
    int32_t dst_offset = TZ_INIT_DST_OFFSET;
    char_t *tz = getenv("TZ"); /* get the environment time zone setting */
    uint32_t cpu_flags;

    /* check, if tz string is valid */
    if (tz == NULL) {
        tz = tzdefault; /* if environment doesn't exist, use default */
    }

    /* extract std timzone name */
    if (scanTzString(&tz, std_name) == 0) {
        strcpy(std_name, TZ_INIT_STD_NAME);
    }

    /* extract std timzone offset (in s) */
    if (scanTzOffset(&tz, &std_offset) == 0) {
        std_offset = TZ_INIT_STD_OFFSET;
    }

    /* extract dst timzone name */
    if (scanTzString(&tz, dst_name) == 0) {
        strcpy(dst_name, TZ_INIT_DST_NAME);
        dst_offset = TZ_INIT_DST_OFFSET;
    }
    /* extract dst timzone offset (in s) relative to std */
    else if (scanTzOffset(&tz, &dst_offset) == 0) {
        dst_offset = TZ_DEFAULT_DST_OFFSET;
    }
    else {
        dst_offset -= std_offset;
    }

    //////////////////////////////////
    cpu_flags = st_enter_crit_func();
    //////////////////////////////////

    /* assign global values */
    _daylight = (strcmp(dst_name, "") != 0) ? dst_offset : 0;
    _timezone = std_offset;
    strcpy(tzname[0], std_name);
    strcpy(tzname[1], dst_name);

    //////////////////////////////
    st_exit_crit_func(cpu_flags);
    //////////////////////////////

}

//******************************************************************************
//******************************************************************************
//** Local Functions
//******************************************************************************
//******************************************************************************

/*
********************************************************************************
** \brief Extracts (next) timezone (resp. DST) name from timezone string.
**
** This function extracts the next occurrence of a timezone name (either std
** or dst) in the given timezone string.
**
** \note A leading colon, which POSIX allows as an implementation-
**       specific extension, is not supported.
**
** \param tz (part of a) time zone string
** \param name extracted time zone (std resp. dst) name from first part of tz
**
** \return length of extracted time zone name string
********************************************************************************
*/
static size_t scanTzString(char_t **tz, char_t *name) {
    char_t *p = *tz;
    size_t i = 0;

    /* leading colon for implementation-specific extension is not supported */
    if (*p != ':') {
        while ((strchr("0123456789-+,", *p) == NULL) && (i < TZNAME_MAX)) {
            name[i++] = *p++;
        }
        /* finalize string */
        if (i == TZNAME_MAX) {
            --i;
        }
        name[i] = '\0';
    }

    *tz = p;
    return (i);
}

/*
********************************************************************************
** \brief Extracts (next) timezone (resp. DST) offset from timezone string.
**
** This function extracts the next occurrence of a timezone offset (either std
** or dst) in the given timezone string.
**
** \note A leading colon, which POSIX allows as an implementation-
**       specific extension, is not supported.
**
** \param tz (part of a) time zone string
** \param offset extracted time zone (std resp. dst) offset (in seconds) from
** first part of tz
**
** \return
**    - 1, if time zone value was successfully extracted and is valid,
**    - 0, in error case
********************************************************************************
*/
static int8_t scanTzOffset(char_t **tz, int32_t *offset) {
    int8_t sign;
    char_t *p;
    char_t *endp = 0;
    int32_t secs;
    int32_t v;

    /* check parameter valitidy */
    if ((offset == 0) || (tz == 0) || (*tz == 0)) {
        return (0);
    }

    /* extract hours value */
    v = strtol(*tz, &endp, 10);

    /* no offset value found */
    if (*tz == endp ) {
        return (0);
    }

    /* extract sign for correct calculation and latter assignment */
    sign = (v < 0) ? -1 : 1;
    v = v * sign;

    /* convert to seconds */
    secs = v * 3600L;

    /* extract minutes value */
    p = endp;
    if ( *p == ':' ) {
        p++;
        v = strtol(p, &endp, 10);
        if (p != endp) {
            secs += v * 60L;
        }

        /* extract seconds value */
        p = endp;
        if ( *p == ':' ) {
            p++;
            v = strtol(p, &endp, 10);
            if (p != endp) {
                secs += v;
            }
            p = endp;
        }
    }

    /* re-apply sign value */
    *offset = sign * secs;

    /* move timezone pointer to the residual string */
    *tz = p;

    return(1);
}

