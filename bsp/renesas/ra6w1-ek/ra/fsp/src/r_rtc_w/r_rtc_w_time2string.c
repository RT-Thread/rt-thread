/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_rtc_w.h"

#include <stdio.h>
#include <stdlib.h>

char *_fmt(const char *format, const struct tm *const t, char *pt,
           const char *const ptlim, int *warnp);

#define Locale    (&C_time_locale)

#ifndef YEAR_2000_NAME
#define YEAR_2000_NAME    "CHECK_STRFTIME_FORMATS_FOR_TWO_DIGIT_YEARS"
#endif /* !defined YEAR_2000_NAME */

#define IN_NONE        0

size_t ra6w1_strftime(char * ptr, size_t maxsize, const char * format, const struct tm * t)
{
    char * p;
    int warn;

    warn = IN_NONE;
    p = _fmt(((format == NULL) ? "%c" : format), t, ptr, ptr + maxsize, &warn);
#ifdef RUN_TIME_WARNINGS_ABOUT_YEAR_2000_PROBLEMS_THANK_YOU

    if (warn != IN_NONE && getenv(YEAR_2000_NAME) != NULL) {
        printf("\n");

        if (format == NULL) {
            printf("NULL strftime format ");
        } else {
            printf("strftime format \"%s\" ", format);
        }

        printf("yields only two digits of years in ");

        if (warn == IN_SOME) {
            printf("some locales");
        } else if (warn == IN_THIS) {
            printf("the current locale");
        } else {
            printf("all locales");
        }

        printf("\n");
    }

#endif /* defined RUN_TIME_WARNINGS_ABOUT_YEAR_2000_PROBLEMS_THANK_YOU */

    if (p == ptr + maxsize) {
        return 0;
    }

    *p = '\0';
    return (size_t)(p - ptr);
}

/* EOF */
