/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <rtm.h>

/* some export routines for module */

RTM_EXPORT(strstr);
RTM_EXPORT(strlen);
RTM_EXPORT(strchr);
RTM_EXPORT(strcpy);
RTM_EXPORT(strncpy);
RTM_EXPORT(strcmp);
RTM_EXPORT(strncmp);
RTM_EXPORT(strcat);
RTM_EXPORT(strtol);

RTM_EXPORT(memcpy);
RTM_EXPORT(memcmp);
RTM_EXPORT(memmove);
RTM_EXPORT(memset);
RTM_EXPORT(memchr);

RTM_EXPORT(toupper);
RTM_EXPORT(atoi);

/* import the full stdio for printf */
#if defined(RT_USING_MODULE) && defined(__MICROLIB)
#error "[RT_USING_LIBC] Please use standard libc but not microlib."
#endif

RTM_EXPORT(puts);
RTM_EXPORT(printf);
