/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-05     WillianChan  first version
 */

#include <var_export.h>

static int ve_cmd_help(int argc, char **argv);
static int ve_find_module(int argc, char **argv);
static int ve_find_value(int argc, char **argv);


struct ve_cmd_des
{
    const char *cmd;
    int (*fun)(int argc, char **argv);
};

/* dcm cmd table */
static const struct ve_cmd_des cmd_tab[] =
{
    {"module", ve_find_module},
    {"value", ve_find_value},
};

static int ve_cmd_help(int argc, char **argv)
{
    rt_kprintf("Usage:\n");
    rt_kprintf("ve_find module <module>                - Find by module name\n");
    rt_kprintf("ve_find value  <module> <identifier>   - Find accurately\n");

    return RT_EOK;
}

rt_inline void ve_object_split(int len)
{
    while (len--) rt_kprintf("-");
}

static int ve_find_module(int argc, char **argv)
{
    ve_iterator_t iter;
    const ve_exporter_t *exporter;
    ve_module_t module;
    int maxlen = (RT_NAME_MAX * 2);
    const char *item_title = "ve_module";

    rt_kprintf("%-*.s identifier       value\n", maxlen, item_title); ve_object_split(maxlen);
    rt_kprintf(" ---------------- -----\n");

    if (!ve_module_init(&module, argv[2]))
    {
        ve_iter_init(&module, &iter);
    }
    else
    {
        return -RT_ERROR;
    }

    while (1)
    {
        exporter = ve_iter_next(&iter);
        if (exporter == RT_NULL)
        {
            return -RT_ERROR;
        }
        else
        {
            rt_kprintf("%-*.s %-*.s %d\n",
                       maxlen, exporter->module,
                       maxlen, exporter->identifier,
                       exporter->value);
        }
    }
}

static int ve_find_value(int argc, char **argv)
{
    ve_iterator_t iter;
    const ve_exporter_t *exporter;
    ve_module_t module;
    int maxlen = (RT_NAME_MAX * 2);
    const char *item_title = "ve_module";

    rt_kprintf("%-*.s identifier       value\n", maxlen, item_title); ve_object_split(maxlen);
    rt_kprintf(" ---------------- -----\n");

    if (!ve_module_init(&module, argv[2]))
    {
        ve_iter_init(&module, &iter);
    }
    else
    {
        return -RT_ERROR;
    }

    while (1)
    {
        exporter = ve_iter_next(&iter);
        if (exporter == RT_NULL)
        {
            return -RT_ERROR;
        }
        else
        {
            if (!rt_strcmp(exporter->identifier, argv[3]))
            {
                rt_kprintf("%-*.s %-*.s %d\n",
                           maxlen, exporter->module,
                           maxlen, exporter->identifier,
                           exporter->value);

                return RT_EOK;
            }
        }
    }
}

static int ve_find(int argc, char **argv)
{
    int i, resule = RT_EOK;
    const struct ve_cmd_des *run_cmd = RT_NULL;

    if (argc == 1)
    {
        ve_cmd_help(argc, argv);
        return RT_EOK;
    }

    /* find command function */
    for (i = 0; i < sizeof(cmd_tab) / sizeof(cmd_tab[0]); i++)
    {
        if (rt_strcmp(cmd_tab[i].cmd, argv[1]) == 0)
        {
            run_cmd = &cmd_tab[i];
            break;
        }
    }

    /* not find command function, print help information */
    if (run_cmd == RT_NULL)
    {
        rt_kprintf("There is no command option named %s.\n", argv[1]);
        ve_cmd_help(argc, argv);
        return RT_EOK;
    }

    /* run command function */
    if (run_cmd->fun != RT_NULL)
    {
        resule = run_cmd->fun(argc, argv);
    }

    if (resule)
    {
        ve_cmd_help(argc, argv);
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(ve_find, find the specified export variable);
