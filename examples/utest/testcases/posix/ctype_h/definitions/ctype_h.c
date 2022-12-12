/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  Laurent.Vivier@bull.net
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

 /* <ctype.h> */

#include <ctype.h>

static char xx;

static int test_defined()
{
    isalnum(xx);
    isalpha(xx);
    isblank(xx);
    iscntrl(xx);
    isdigit(xx);
    isgraph(xx);
    islower(xx);
    isprint(xx);
    ispunct(xx);
    isspace(xx);
    isupper(xx);
    isxdigit(xx);
    tolower(xx);
    toupper(xx);
}
