/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author      Notes
 * 2010-11-17     yi.qiu      first version
 */

#include <rtthread.h>
#include <rtm.h>

#include "dlmodule.h"

/**
 * @brief   Get the address of a symbol in a dynamic link library module.
 *
 * @param   handle   is a pointer to the dynamic link library module handle obtained from dlopen.
 * @param   symbol   is the name of the symbol to retrieve the address.
 *
 * @return  A pointer to the symbol's address if found, or RT_NULL if the symbol is not found in the module.
 *
 * @note    This function allows you to retrieve the address of a symbol in a dynamic link library module.
 */
void *dlsym(void *handle, const char *symbol)
{
    int i;
    struct rt_dlmodule *module;

    RT_ASSERT(handle != RT_NULL);

    module = (struct rt_dlmodule *)handle;

    for (i = 0; i < module->nsym; i++)
    {
        if (rt_strcmp(module->symtab[i].name, symbol) == 0)
            return (void *)module->symtab[i].addr;
    }

    return RT_NULL;
}
RTM_EXPORT(dlsym)
