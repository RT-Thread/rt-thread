
/*
 * Copyright (c) 2011-2023, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author          Notes
 * 2023-09-24     fang-jianzhou   first version
 */

#include <rtthread.h>
#include <ofw.h>
#include "ofw_internal.h"

static void dump_dts(int argc,char** argv)
{
    if(ofw_node_root == RT_NULL)
    {
        rt_kprintf("\"/\" path not found.");
        return;
    }

    if(argc==1)
    {
        rt_ofw_node_dump_dts(ofw_node_root, RT_TRUE);
    }
    else if (argv[1][0]== '/')
    {
        struct rt_ofw_node *ofw_node_pointer = rt_ofw_find_node_by_path(argv[1]);

        if (ofw_node_pointer)
        {
            rt_ofw_node_dump_dts(ofw_node_pointer, RT_FALSE);
        }
        else
        {
            rt_kprintf("%s not found.\n", argv[1]);
        }
    }
    else
    {
        rt_kprintf("Usage: %s {path}\n", __func__);
    }
}
MSH_CMD_EXPORT(dump_dts, dump the dts);

