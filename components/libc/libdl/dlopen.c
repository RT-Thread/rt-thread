/*
 * File      : dlopen.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-17      yi.qiu   first version
 */

#include <rtthread.h>
#include <rtm.h>
#include <string.h>

#define MODULE_ROOT_DIR     "/modules"

void* dlopen(const char *filename, int flags)
{
    rt_module_t module;
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

    /* find in module list */
    module = rt_module_find(fullpath);

    if(module != RT_NULL) module->nref++;
    else module = rt_module_open(fullpath);

    if(fullpath != filename)
    {
        rt_free(fullpath);
    }

    return (void*)module;
}
RTM_EXPORT(dlopen);

