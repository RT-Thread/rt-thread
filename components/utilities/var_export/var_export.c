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

#include <var_export.h>

static const ve_exporter_t *ve_exporter_table = RT_NULL;
static rt_size_t ve_exporter_num = 0;

/* for IAR compiler */
#if defined(__ICCARM__) || defined(__ICCRX__)
#pragma section="VarExpTab"
#endif

/* for ARM C and IAR Compiler */
#if defined(__ARMCC_VERSION) || defined (__ICCARM__) || defined(__ICCRX__)
static RT_USED const struct ve_exporter __ve_table_start
RT_SECTION("0.""VarExpTab") = {"ve_start", "ve_start", 0};

static RT_USED const struct ve_exporter __ve_table_end
RT_SECTION("2.""VarExpTab") = {"ve_end", "ve_end", 2};
#endif

/* for MS VC++ compiler */
#if defined(_MSC_VER)
#pragma section("VarExpTab$a", read)
__declspec(allocate("VarExpTab$a"))
RT_USED const struct ve_exporter __ve_table_start = { "ve_start", "ve_start", 0};

#pragma section("VarExpTab$z", read)
__declspec(allocate("VarExpTab$z"))
RT_USED const struct ve_exporter __ve_table_end = { "ve_end", "ve_end", 2};

/* Find var objects in VarExpTab segments */
static int ve_init_find_obj(unsigned int *begin, unsigned int *end, ve_exporter_t *table)
{
    int obj_count = 0;

    while (begin < end)
    {
        if (*begin != RT_NULL)
        {
            *table++ = *((struct ve_exporter *)begin);
            begin += sizeof(struct ve_exporter) / sizeof(unsigned int);
            obj_count += 1;
        }
        else
        {
            begin++;
        }
    }

    return obj_count;
}
#endif /* _MSC_VER */

/* initialize var export */
int var_export_init(void)
{
    /* initialize the var export table.*/
#if defined(__ARMCC_VERSION)                        /* for ARM C Compiler */
    ve_exporter_table = &__ve_table_start + 1;
    ve_exporter_num = &__ve_table_end - &__ve_table_start;
#elif defined (__IAR_SYSTEMS_ICC__)                 /* for IAR Compiler */
    ve_exporter_table = &__ve_table_start + 1;
    ve_exporter_num = &__ve_table_end - &__ve_table_start - 1;
#elif defined (__GNUC__)                            /* for GCC Compiler */
    extern const int __ve_table_start;
    extern const int __ve_table_end;
    ve_exporter_table = (const ve_exporter_t *)&__ve_table_start;
    ve_exporter_num = (const ve_exporter_t *)&__ve_table_end - ve_exporter_table;
#elif defined (_MSC_VER)                            /* for MS VC++ compiler */
    unsigned int *ptr_begin = (unsigned int *)&__ve_table_start;
    unsigned int *ptr_end = (unsigned int *)&__ve_table_end;
    static ve_exporter_t ve_exporter_tab[2048];
    static char __vexp_strbuf1[1024];
    static char __vexp_strbuf2[1024];
    ve_exporter_t ve_exporter_temp;
    int index_i, index_j;

    /* past the three members in first ptr_begin */
    ptr_begin += (sizeof(struct ve_exporter) / sizeof(unsigned int));
    while (*ptr_begin == 0) ptr_begin++;
    do ptr_end--; while (*ptr_end == 0);

    /* Find var objects in custom segments to solve the problem of holes in objects in different files */
    ve_exporter_num = ve_init_find_obj(ptr_begin, ptr_end, ve_exporter_tab);

    /* check if the ve_exporter_num is out of bounds */
    RT_ASSERT(ve_exporter_num < (sizeof(ve_exporter_tab) / sizeof(ve_exporter_t)));

    /* bubble sort algorithms */
    for (index_i = 0; index_i < (ve_exporter_num - 1); index_i++)
    {
        for (index_j = 0; index_j < ((ve_exporter_num - 1) - index_i); index_j++)
        {
            /* splice ve_exporter's module and ve_exporter's identifier into a complete string */
            rt_snprintf(__vexp_strbuf1,
                        sizeof(__vexp_strbuf1),
                        "%s%s",
                        ve_exporter_tab[index_j].module,
                        ve_exporter_tab[index_j].identifier);
            rt_snprintf(__vexp_strbuf2,
                        sizeof(__vexp_strbuf2),
                        "%s%s",
                        ve_exporter_tab[index_j + 1].module,
                        ve_exporter_tab[index_j + 1].identifier);
            if (rt_strcmp(__vexp_strbuf1, __vexp_strbuf2) > 0)
            {
                ve_exporter_temp = ve_exporter_tab[index_j];
                ve_exporter_tab[index_j] = ve_exporter_tab[index_j + 1];
                ve_exporter_tab[index_j + 1] = ve_exporter_temp;
            }
        }
    }

    ve_exporter_table = ve_exporter_tab;
#endif /* __ARMCC_VERSION */

    return ve_exporter_num;
}
INIT_PREV_EXPORT(var_export_init);

/* initialize module */
int ve_module_init(ve_module_t *mod, const char *module)
{
    const ve_exporter_t *exporter = ve_exporter_table;
    rt_bool_t first_exist = RT_FALSE;
    rt_size_t found_index;

    for (found_index = 0; found_index < ve_exporter_num; found_index++)
    {
        if (!rt_strcmp(exporter->module, module))
        {
            if (first_exist == RT_FALSE)
            {
                mod->begin = exporter;
                first_exist = RT_TRUE;
            }
            mod->end = exporter;
        }
        exporter++;
    }

    if (first_exist == RT_FALSE)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* initialize iterator */
void ve_iter_init(ve_module_t *mod, ve_iterator_t *iter)
{
    if (iter)
    {
        iter->exp_index = mod->begin;
        iter->exp_end = mod->end;
    }
}

/* iterate backward */
const ve_exporter_t *ve_iter_next(ve_iterator_t *iter)
{
    if (iter->exp_index <= iter->exp_end)
    {
        return iter->exp_index++;
    }
    else
    {
        return RT_NULL;
    }
}

/* binary search based on identifier */
static const ve_exporter_t *ve_binary_search(ve_module_t *mod, const char *identifier)
{
    int ve_low_num = 0;
    int ve_high_num = mod->end - mod->begin;
    int ve_mid_num = 0;
    int strcmp_rst = 0;

    while ((ve_low_num <= ve_high_num) && (ve_high_num >= 0) && (ve_low_num >= 0))
    {
        ve_mid_num = (ve_high_num + ve_low_num) / 2;
        strcmp_rst = rt_strcmp(mod->begin[ve_mid_num].identifier, identifier);

        if (strcmp_rst == 0)
        {
            return &mod->begin[ve_mid_num];
        }
        else if (strcmp_rst > 0)
        {
            ve_high_num = ve_mid_num - 1;
        }
        else
        {
            ve_low_num = ve_mid_num + 1;
        }
    }

    return RT_NULL;
}

/* get the value by identifier */
rt_base_t ve_value_get(ve_module_t *mod, const char *identifier)
{
    const ve_exporter_t *exporter = ve_binary_search(mod, identifier);

    if (exporter)
    {
        return exporter->value;
    }
    else
    {
        return VE_NOT_FOUND;
    }
}

/* check if this value exists in the module*/
rt_bool_t ve_value_exist(ve_module_t *mod, const char *identifier)
{
    if (ve_binary_search(mod, identifier))
    {
        return RT_TRUE;
    }
    else
    {
        return RT_FALSE;
    }
}
