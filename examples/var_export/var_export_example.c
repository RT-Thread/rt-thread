/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-02     WillianChan  add var_export example code
 */

#include <var_export.h>

/* use VAR_EXPOR() to export 10 pieces of data into sections */
VAR_EXPORT(module0, identi0, 0);
VAR_EXPORT(module1, identi1, 1);
VAR_EXPORT(module2, identi2, 2);
VAR_EXPORT(module3, identi3, 3);
VAR_EXPORT(module4, identi4, 4);
VAR_EXPORT(module5, identi5, 5);
VAR_EXPORT(module6, identi6, 6);
VAR_EXPORT(module7, identi7, 7);
VAR_EXPORT(module8, identi8, 8);
VAR_EXPORT(module9, identi9, 9);

void found_by_module(void)
{
    ve_iterator_t iter;
    const ve_exporter_t* exporter;
    ve_module_t module;
    rt_base_t value;

    /* query all exporters with the same name as module1 */
    if (!ve_module_init(&module, "module1"))
        /* initialize the iterator */
        ve_iter_init(&module, &iter);
    else
        return;

    while (1)
    {
        /* start iterating */
        exporter = ve_iter_next(&iter);
        if (exporter == RT_NULL)
            break;
        else
        {
            /* checks whether the value exists */
            if (ve_value_exist(&module, "identi1") == RT_TRUE)
            {
                value = ve_value_get(&module, "identi1");
                rt_kprintf("[ve_example] value = %dn", value);
                return;
            }
            else
            {
                rt_kprintf("[ve_example] value not exist.\n");
                return;
            }
        }
    }
}
#ifdef RT_USING_FINSH
#include <finsh.h>
MSH_CMD_EXPORT(found_by_module, found by module);
#endif /* RT_USING_FINSH */