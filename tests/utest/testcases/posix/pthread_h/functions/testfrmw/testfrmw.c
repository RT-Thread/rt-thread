/*
 * Copyright (c) 2004, Bull S.A..  All rights reserved.
 * Created by: Sebastien Decugis

 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *

 * This file is a wrapper to use the tests from the NPTL Test & Trace Project
 * with either the Linux Test Project or the Open POSIX Test Suite.

 * The following function are defined:
 * void output_init()
 * void output_fini()
 * void output(char * string, ...)
 *
 * The are used to output informative text (as a printf).
 */

#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdarg.h>

/* We use a mutex to avoid conflicts in traces */
static pthread_mutex_t m_trace = PTHREAD_MUTEX_INITIALIZER;

static void output_init(void)
{
    return;
}

static void output(char *string, ...)
{
    va_list ap;
    struct tm *now;
    time_t nw;
    int oldstate;

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
    pthread_mutex_lock(&m_trace);
    nw = time(NULL);
    now = localtime(&nw);
    if (now == NULL)
        printf("[??:??:??]\n");
    else
        printf("[%2.2d:%2.2d:%2.2d]\n",
               now->tm_hour, now->tm_min, now->tm_sec);
    va_start(ap, string);
    vprintf(string, ap);
    va_end(ap);
    pthread_mutex_unlock(&m_trace);
    pthread_setcancelstate(oldstate, NULL);
}

static void output_fini(void)
{
    return;
}
