/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-12     Yi Qiu      first version
 * 2021-02-23     Leslie Lee  provide possibility for multi usb host
 */

#include <rtthread.h>
#include <rtservice.h>
#include <drivers/usb_host.h>

static rt_list_t _driver_list;
static rt_bool_t _driver_list_created = RT_FALSE;

/**
 * This function will initilize the usb class driver related data structure,
 * and it should be invoked in the usb system initialization.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_class_driver_init(void)
{
    if (_driver_list_created == RT_FALSE)
    {
        rt_list_init(&_driver_list);
        _driver_list_created = RT_TRUE;
    }
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

    if (rt_usbh_class_driver_find(drv->class_code, drv->subclass_code) == RT_NULL)
    {
        /* insert class driver into driver list */
        rt_list_insert_after(&_driver_list, &(drv->list));
    }

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
