/*
 * File      : rtm.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 */
 
#ifndef __RTM_H__
#define __RTM_H__

#include <rtdef.h>
#include <rtthread.h>

#ifdef RT_USING_MODULE
struct rt_module_symtab
{
    void       *addr;
    const char *name;
};

#define RTM_EXPORT(symbol)                                            \
const char __rtmsym_##symbol##_name[] = #symbol;                      \
const struct rt_module_symtab __rtmsym_##symbol SECTION("RTMSymTab")= \
{                                                                     \
    (void *)&symbol,                                                  \
    __rtmsym_##symbol##_name                                          \
};
#else
#define RTM_EXPORT(symbol)
#endif

#endif
