/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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

/**
 * @brief  dynamically load a shared library at runtime.
 *
 * @param  filename the path to the shared library to load, which shouldn't be set to NULL.
 * @param  flags options for loading the shared library.
 * @return void* on success, it returns a handle (a pointer) to the opened shared library, otherwise it returns NULL.
 *
 * @note   This function is an API of POSIX standard, which is used for dynamically loading shared libraries at runtime.
 *         the function first tries to check if the module is already loaded, by finding module in module list.
 *         If module is found in memory (RT_NULL check fails), the reference count (nref) is incremented.
 *         Otherwise,  dlmodule_load() will be called to load the module into memory.
 *         A handle (a pointer to the module) is returned at last, which can be used with other functions like dlsym().
 */
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
