/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-17      yi.qiu   first version
 */

#include <rtthread.h>
#include <rtm.h>
#include <string.h>

#include "dlmodule.h"

#define MODULE_ROOT_DIR     "/modules"

void* dlopen(const char *filename, int flags)
{
    struct rt_dlmodule *module;
    char *fullpath;
    const char*def_path = MODULE_ROOT_DIR;

    /* check parameters */
    RT_ASSERT(filename != RT_NULL);

    if (filename[0] != '/') /* it's a relative path, prefix with MODULE_ROOT_DIR */
    {
        fullpath = rt_malloc(strlen(def_path) + strlen(filename) + 2);

        /* join path and file name */
        rt_snprintf(fullpath, strlen(def_path) + strlen(filename) + 2,
            "%s/%s", def_path, filename);
    }
    else
    {
        fullpath = (char*)filename; /* absolute path, use it directly */
    }

    rt_enter_critical();

    /* find in module list */
    module = dlmodule_find(fullpath);

    if(module != RT_NULL) 
    {
        rt_exit_critical();
        module->nref++;
    }
    else 
    {
        rt_exit_critical();
        module = dlmodule_load(fullpath);
    }

    if(fullpath != filename)
    {
        rt_free(fullpath);
    }

    return (void*)module;
}
RTM_EXPORT(dlopen);
