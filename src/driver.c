/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#ifdef RT_USING_FDT
#include <dtb_node.h>
#endif
#if defined(RT_USING_POSIX_DEVIO)
#include <rtdevice.h> /* for wqueue_init */
#endif

/**
 * This function driver device match with id
 *
 * @param drv the pointer of driver structure
 * @param device_id the id of the device
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_driver_match_with_id(const rt_driver_t drv,int device_id)
{
    rt_device_t device;
    int ret;
    if (!drv)
    {
        return -RT_EINVAL;
    }
    device = rt_device_create_since_driver(drv,device_id);
    if(!device)
    {
        return -RT_ERROR;
    }
    ret = rt_device_bind_driver(device,drv,RT_NULL);
    if(ret != 0)
    {
        return -RT_ERROR;
    }
    ret = rt_device_probe_and_init(device);
    if(ret != 0)
    {
        return -RT_ERROR;
    }
    return ret;
}

RTM_EXPORT(rt_driver_match_with_id);

#ifdef RT_USING_FDT
/**
 * This function driver device match with dtb_node
 *
 * @param drv the pointer of driver structure
 * @param from_node dtb node entry 
 * @param max_dev_num the max device support 
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_driver_match_with_dtb(const rt_driver_t drv,void *from_node,int max_dev_num)
{
    struct dtb_node** node_list; 
    rt_device_t device;
    int ret,i;
    int total_dev_num = 0;
    if ((!drv)||(!drv->dev_match)||(!drv->dev_match->compatible)||(!from_node)||(!drv->device_size))
    {
        return -RT_EINVAL;
    }

    node_list = rt_calloc(max_dev_num,sizeof(void *));
    if(!node_list)
    {
        return -RT_ERROR;
    }

    ret = dtb_node_find_all_compatible_node(from_node,drv->dev_match->compatible,node_list,max_dev_num,&total_dev_num);
    if((ret != 0) || (!total_dev_num))
    {
        return -RT_ERROR;
    }
    
    for(i = 0; i < total_dev_num; i ++)
    {
        if (!dtb_node_device_is_available(node_list[i]))
        {
            continue;
        }
        device = rt_device_create_since_driver(drv,i);
        if(!device)
        {
            continue;
        }
    
        ret = rt_device_bind_driver(device,drv,node_list[i]);
        if(ret != 0)
        {
            continue;
        }
        ret = rt_device_probe_and_init(device);
        if(ret != 0)
        {
            continue;
        }
    }
    rt_free(node_list);
    return ret;
}

RTM_EXPORT(rt_driver_match_with_dtb);
#endif  

