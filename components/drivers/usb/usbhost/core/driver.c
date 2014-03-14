/*
 * File      : driver.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-12     Yi Qiu      first version
 */

#include <rtthread.h>
#include <rtservice.h>
#include <rtdevice.h>

static rt_list_t _driver_list;

/**
 * This function will initilize the usb class driver related data structure,
 * and it should be invoked in the usb system initialization.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_class_driver_init(void)
{
    rt_list_init(&_driver_list);

    return RT_EOK;    
}

/**
 * This function will register an usb class driver to the class driver manager.
 *
 * @param drv the pointer of the usb class driver.
 * 
 * @return the error code, RT_EOK on successfully.
 */

rt_err_t rt_usbh_class_driver_register(ucd_t drv)
{
    if (drv == RT_NULL) return -RT_ERROR;

    /* insert class driver into driver list */
    rt_list_insert_after(&_driver_list, &(drv->list));
    
    return RT_EOK;    
}

/**
 * This function will removes a previously registed usb class driver.
 *
 * @param drv the pointer of the usb class driver structure.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_class_driver_unregister(ucd_t drv)
{
    RT_ASSERT(drv != RT_NULL);

    /* remove class driver from driver list */
    rt_list_remove(&(drv->list));

    return RT_EOK;
}

/**
 * This function will run an usb class driver.
 *
 * @param drv the pointer of usb class driver.
 * @param args the parameter of run function.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_class_driver_enable(ucd_t drv, void* args)
{
    RT_ASSERT(drv != RT_NULL);

    if(drv->enable != RT_NULL)
        drv->enable(args);

    return RT_EOK;
}

/**
 * This function will stop a usb class driver.
 *
 * @param drv the pointer of usb class driver structure.
 * @param args the argument of the stop function.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_class_driver_disable(ucd_t drv, void* args)
{
    RT_ASSERT(drv != RT_NULL);

    if(drv->disable != RT_NULL)
        drv->disable(args);

    return RT_EOK;
}


/**
 * This function finds a usb class driver by specified class code and subclass code.
 *
 * @param class_code the usb class driver's class code. 
 * @param subclass_code the usb class driver's sub class code.
 *
 * @return the registered usb class driver on successful, or RT_NULL on failure.
 */
ucd_t rt_usbh_class_driver_find(int class_code, int subclass_code)
{
    struct rt_list_node *node;

    /* enter critical */
    if (rt_thread_self() != RT_NULL)
        rt_enter_critical();

    /* try to find driver object */
    for (node = _driver_list.next; node != &_driver_list; node = node->next)
    {
        ucd_t drv = 
            (ucd_t)rt_list_entry(node, struct uclass_driver, list);
        if (drv->class_code == class_code)
        {
            /* leave critical */
            if (rt_thread_self() != RT_NULL)
                rt_exit_critical();

            return drv;
        }
    }

    /* leave critical */
    if (rt_thread_self() != RT_NULL)
        rt_exit_critical();

    /* not found */
    return RT_NULL;
}

