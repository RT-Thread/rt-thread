
/*
 * Copyright (c) 2011-2023, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#include <rtthread.h>
#include <ofw.h>
#include "ofw_internal.h"
static void dump_dts(int argc,char** argv)
{
    if(ofw_node_root)
    {
        if(argc==1)
        {
            rt_ofw_node_dump_dts(ofw_node_root,RT_TRUE);
        }
        else if (argv[1][0]== '/')
        {
            struct rt_ofw_node *np = rt_ofw_find_node_by_path(argv[1]);
            
            if (np)
            {
                rt_ofw_node_dump_dts(np, RT_FALSE);
            }
            else
            {
                rt_kprintf("%s not found.\n", argv[1]);
            }
        }
        else
        {
            rt_kprintf("Usage: %s {path}\n",__func__);
        }
    }
    else
    {
        rt_kprintf("\"/\" path not found.");
    }
}
MSH_CMD_EXPORT(dump_dts,dump the dts);

