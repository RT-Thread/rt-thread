/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-17     yi.qiu        first version
 */

#include <rtthread.h>
#include <rtm.h>
#include <string.h>

#include "dlmodule.h"

#define MODULE_ROOT_DIR "/modules"

/**
 * @brief   Open and load a dynamic link library module.
 *
 * @param   filename  is the name of the dynamic link library module to be opened.
 * @param   flags     is an integer flag that specifies how the module should be opened.
 *
 * @return  A pointer to the loaded dynamic link library module, or RT_NULL if an error occurs.
 *
 * @note    This function allows you to open and load a dynamic link library module. If the module is already
 *          loaded, it increments the reference count. If the module is not loaded, it attempts to load it.
 *          The function automatically prefixes the module's name with the default root directory if the
 *          filename is relative.
 */
void *dlopen(const char *filename, int flags)
{
    struct rt_dlmodule *module;
    char *fullpath;
    const char *def_path = MODULE_ROOT_DIR;

    /* Check parameters */
    RT_ASSERT(filename != RT_NULL);

    if (filename[0] != '/') /* it's a relative path, prefix with MODULE_ROOT_DIR */
    {
        fullpath = rt_malloc(strlen(def_path) + strlen(filename) + 2);

        /* Join path and file name */
        rt_snprintf(fullpath, strlen(def_path) + strlen(filename) + 2,
                    "%s/%s", def_path, filename);
    }
    else
    {
        fullpath = (char *)filename; /* Absolute path, use it directly */
    }

    rt_enter_critical();

    /* Find in the module list */
    module = dlmodule_find(fullpath);

    if (module != RT_NULL)
    {
        rt_exit_critical();
        module->nref++;
    }
    else
    {
        rt_exit_critical();
        module = dlmodule_load(fullpath);
    }

    if (fullpath != filename)
    {
        rt_free(fullpath);
    }

    return (void *)module;
}
RTM_EXPORT(dlopen);
