/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 */

#include <rtthread.h>
#include <rtm.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

RTM_EXPORT(strcpy);
RTM_EXPORT(strncpy);
RTM_EXPORT(strlen);
RTM_EXPORT(strcat);
RTM_EXPORT(strstr);
RTM_EXPORT(strchr);
RTM_EXPORT(strcmp);
RTM_EXPORT(strtol);
RTM_EXPORT(strtoul);
RTM_EXPORT(strncmp);

RTM_EXPORT(memcpy);
RTM_EXPORT(memcmp);
RTM_EXPORT(memmove);
RTM_EXPORT(memset);
RTM_EXPORT(memchr);

RTM_EXPORT(putchar);
RTM_EXPORT(puts);
RTM_EXPORT(printf);
RTM_EXPORT(sprintf);
RTM_EXPORT(snprintf);

RTM_EXPORT(fwrite);

#include <setjmp.h>
RTM_EXPORT(longjmp);
RTM_EXPORT(setjmp);

RTM_EXPORT(exit);
RTM_EXPORT(abort);

RTM_EXPORT(rand);

#include <assert.h>
RTM_EXPORT(__assert_func);
