/*
 * Copyright (c) 2004, Bull S.A..  All rights reserved.
 * Created by: Sebastien Decugis
 *
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
 *
 * The following macros are defined here:
 * UNRESOLVED(ret, descr);
 *    where descr is a description of the error and ret is
 *    an int (error code for example)
 * FAILED(descr);
 *    where descr is a short text saying why the test has failed.
 * PASSED();
 *    No parameter.
 *
 * Both three macros shall terminate the calling process.
 * The testcase shall not terminate without calling one of those macros.
 */

#include "posixtest.h"
#include <string.h>

#ifdef __GNUC__

#define UNRESOLVED(x, s)                        \
{                                   \
    output("Test %s unresolved: got %i (%s) on line %i (%s)\n", \
        __FILE__, x, strerror(x), __LINE__, s);         \
    output_fini();                          \
    exit(PTS_UNRESOLVED);                       \
}

#define FAILED(s)                           \
{                                   \
    output("Test %s FAILED: %s\n", __FILE__, s);            \
    output_fini();                          \
    exit(PTS_FAIL);                         \
}

#define PASSED                              \
{                                   \
    output_fini();                          \
    exit(PTS_PASS);                         \
}

#define UNTESTED(s)                         \
{                                   \
    output("File %s cannot test: %s\n", __FILE__, s);       \
    output_fini();                          \
    exit(PTS_UNTESTED);                     \
}

#else

#define UNRESOLVED(x, s)                        \
{                                   \
    output("Test unresolved: got %i (%s) on line %i (%s)\n",    \
        x, strerror(x), __LINE__, s);               \
    output_fini();                          \
    exit(PTS_UNRESOLVED);                       \
}

#define FAILED(s)                           \
{                                   \
    output("Test FAILED: %s\n", s);                 \
    output_fini();                          \
    exit(PTS_FAIL);                         \
}

#define PASSED                              \
{                                   \
    output_fini();                          \
    exit(PTS_PASS);                         \
}

#define UNTESTED(s)                         \
{                                   \
    output("Unable to test: %s\n", s);              \
    output_fini();                          \
    exit(PTS_UNTESTED);                     \
}

#endif
