/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-04     WillianChan  first version
 * 2021-06-08     WillianChan  support to MS VC++ compiler
 */

#ifndef _VAR_EXPORT_H__
#define _VAR_EXPORT_H__

#include <rtthread.h>

/* exported object */
struct ve_exporter
{
    const char *module;             /* module name */
    const char *identifier;         /* module identifier */
    rt_base_t   value;              /* module value */
};
typedef struct ve_exporter ve_exporter_t;

/* module object */
struct ve_module
{
    const ve_exporter_t *begin;     /* the first module of the same name */
    const ve_exporter_t *end;       /* the last module of the same */
};
typedef struct ve_module ve_module_t;

/* iterator object */
struct ve_iterator
{
    const ve_exporter_t *exp_index; /* iterator index */
    const ve_exporter_t *exp_end;   /* iterate over exporter */
};
typedef struct ve_iterator ve_iterator_t;

#define VE_NOT_FOUND (0xFFFFFFFFu)  /* not found */

/* exporter's export command */
#if defined(__ARMCC_VERSION) || defined(__IAR_SYSTEMS_ICC__)
#define VAR_EXPORT(module, identi, value)                                       \
    const char _vexp_##identi##_module[] RT_SECTION(".rodata.vexp") = #module;  \
    const char _vexp_##identi##_identi[] RT_SECTION(".rodata.vexp") = #identi;  \
    RT_USED const struct ve_exporter _vexp_##module##identi                     \
    RT_SECTION("1."#module".VarExpTab."#identi) =                               \
    {                                                                           \
        _vexp_##identi##_module,                                                \
        _vexp_##identi##_identi,                                                \
        value,                                                                  \
    }
#elif defined(__GNUC__)
#define VAR_EXPORT(module, identi, value)                                       \
    const char _vexp_##identi##_module[] RT_SECTION(".rodata.vexp") = #module;  \
    const char _vexp_##identi##_identi[] RT_SECTION(".rodata.vexp") = #identi;  \
    RT_USED const struct ve_exporter _vexp_##module##identi                     \
    RT_SECTION(#module".VarExpTab."#identi) =                                   \
    {                                                                           \
        _vexp_##identi##_module,                                                \
        _vexp_##identi##_identi,                                                \
        value,                                                                  \
    }
#elif defined(_MSC_VER)
#pragma section("VarExpTab$f",read)
#define VAR_EXPORT(module, identi, value)                                       \
    const char _vexp_##identi##_module[] RT_SECTION(".rodata.vexp") = #module;  \
    const char _vexp_##identi##_identi[] RT_SECTION(".rodata.vexp") = #identi;  \
    __declspec(allocate("VarExpTab$f"))                                         \
    RT_USED const struct ve_exporter _vexp_##module##identi =                   \
    {                                                                           \
        _vexp_##identi##_module,                                                \
        _vexp_##identi##_identi,                                                \
        value,                                                                  \
    }
#endif

/* initialize var export */
int ve_exporter_init(void);
/* initialize module */
int ve_module_init(ve_module_t *mod, const char *module);
/* initialize iterator */
void ve_iter_init(ve_module_t *mod, ve_iterator_t *iter);
/* iterate backward */
const ve_exporter_t *ve_iter_next(ve_iterator_t *iter);
/* get the value by identifier */
rt_base_t ve_value_get(ve_module_t *mod, const char *identifier);
/* check if this value exists in the module*/
rt_bool_t ve_value_exist(ve_module_t *mod, const char *identifier);
rt_size_t ve_value_count(ve_module_t *mod);
const ve_exporter_t *ve_binary_search(ve_module_t *mod, const char *identifier);

#endif /* _VAR_EXPORT_H__ */
