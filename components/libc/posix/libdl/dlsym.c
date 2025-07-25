/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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
 * @brief  look up the address of a symbol in a dynamically loaded shared library.
 *
 * @param  handle the handle returned by dlopen() when the library was previously loaded.
 * @param  symbol A string containing the name of the symbol to locate.
 * @return void* On success, it returns a pointer to the symbol. Otherwise, it returns RT_NULL.
 *
 * @note   This function is an API of POSIX standard, which is commonly used in conjunction with dlopen() to retrieve function pointers from shared libraries.
 *         the input symbol name, which can be the name of a function or variable, is compared with each symbol
 *         in the module symbol table. if the same symbol is found, return its address.
 */
void* dlsym(void *handle, const char* symbol)
{
    int i;
    struct rt_dlmodule *module;

    RT_ASSERT(handle != RT_NULL);

    module = (struct rt_dlmodule *)handle;

    for(i=0; i<module->nsym; i++)
    {
        if (rt_strcmp(module->symtab[i].name, symbol) == 0)
            return (void*)module->symtab[i].addr;
    }

    return RT_NULL;
}
RTM_EXPORT(dlsym)
