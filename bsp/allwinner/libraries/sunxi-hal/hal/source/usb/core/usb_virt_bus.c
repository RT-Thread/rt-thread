/*===============================================================================================*
*                                                                                                *
* MMMMMMMM  MMMMMMM    MMMMMMM  MMMMMMMM    MMMMMMMM       MM      MM    MMMMMMMMMMMMM           *
*    MMM      MMM        MMM      MMM          MM      MM        . MM        MMM        MM       *
*    MMM      MMM        MMM      MMM          MM      MM          MM        MMM        MM.      *
*    MMM      MMM        MMM      MMM          MM    . MM          MM        MMM        MMMM     *
*    MMM      MMM        MMM      MMM          MM      MMMM                  MMM        MM       *
*    MMMMMMMMMMMM        MMM      MMM          MM          MMMM              MMMMMMMMMMM         *
*    MMM      MMM        MMM      MMM          MM              MMMM          MMM          .      *
*    MMM      MMM        MMM      MMM          MM                . MM        MMM          MM     *
*    MMM      MMM        MMM      MMM          .     MM            MMMM      MMM          MMMM   *
*    MMM      MMM        MM        MM                MM            MM.       MMM          MM     *
*    MMM      MMM  .     MM        MM.               MMMM          MM        MMM          MM     *
* MMMMMMMM  MMMMMMM  MM.                MMMMM         MM      MMMM        MMMMMMMMMMMMM.         *
*                                                                                                *
*================================================================================================
*
*                                              usb host module
*
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.07.01
*
* Description :
*
* History :
*================================================================================================
*/
//#include "usb_host_config.h"

//#include "usb_os_platform.h"
#include <usb_host_common.h>

//#include "usb_host_base_types.h"
//#include "sunxi_drv_list.h"

#include <log.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <list_head_ext.h>
#include <usb_list.h>


static struct usb_virt_bus  my_usb_virt_bus;    //super bus
static hal_spinlock_t device_lock;

/*
********************************************************************************
*                     _usb_virt_bus_remov_dev_from_drv
* Description:
*     将device从driver的virt_dev_list列表中删除。
* Arguments:
*     dev       : input.  即将被删除的device
*     drv       : input.  驱动
* Return value:
*     void
* note:
*     不用关心device是否存在于virt_dev_list列表中
*
*********************************************************************************
*/
static void _usb_virt_bus_remov_dev_from_drv(struct usb_host_virt_sub_dev *dev,
        struct  usb_host_func_drv *drv)
{
    /* check input */
    if (dev == NULL || drv == NULL)
    {
        __err("PANIC : [VIRR BUS] : _usb_virt_bus_remov_dev_from_drv() input == NULL");
        return ;
    }

    /* 队列为空,就不用删除了 */
    if (usb_list_empty(&(drv->virt_dev_list)))
    {
        __err("PANIC : [VIRR BUS] : _usb_virt_bus_remov_dev_from_drv() func_drv->dev_list is empty");
        return ;
    }

    /* del device from driver list */
    list_head_ext_remov_node_from_list(dev, &(drv->virt_dev_list));
}


/*
********************************************************************************
*                     usb_virt_bus_drv_reg
* Description:
*     将driver添加到总线上
* Arguments:
*     drv       : input.  待注册的驱动
* Return value:
*
* note:
*     一个驱动不能注册两次?????????
*********************************************************************************
*/
int32_t usb_virt_bus_drv_reg(struct usb_host_func_drv *drv)
{
    struct usb_list_head *list_start = NULL;
    struct usb_list_head *list_now = NULL;
    struct usb_host_virt_sub_dev *dev = NULL;
    if (drv == NULL)
    {
        __err("PANIC : [VIRR BUS] : usb_virt_bus_drv_reg() input == NULL");
        return -1;
    }

    /* 新注册的驱动是没有设备与其匹配的 */
    if (! usb_list_empty(&(drv->virt_dev_list)))
    {
        __err("PANIC : [VIRR BUS] : usb_virt_bus_drv_reg() drv`s dev_list not empty");
        return -1;
    }

    /* bus上已经存在driver, 就不要再添加了 */
    if (list_node_exist((void *)drv, &(my_usb_virt_bus.drv_list)) == 0)
    {
        __err("ERR: drv is already in the list");
        return 0;
    }

    hal_log_info("--usb_virt_bus_drv_reg---1-2--\n");
    //UsbLock(my_usb_virt_bus.BusLock);
    hal_sem_wait(my_usb_virt_bus.BusLock);

    /* 将driver添加到bus上 */
    list_head_malloc_and_add(drv, &(my_usb_virt_bus.drv_list));
    hal_log_info("--usb_virt_bus_drv_reg---1-3--\n");
    /* 先前可能已经有device连上bus了, 这里就去寻找bus上与之匹配的deivce */
    list_start = &(my_usb_virt_bus.dev_list);
    list_now = list_start->next;

    while (list_start != list_now)
    {
        dev = (struct usb_host_virt_sub_dev *)(list_now->data);

        if (dev == NULL)
        {
            __err("dev == NULL", dev);
            break;
        }

        list_now = list_now->next;
        //UsbLock(dev->usb_virt_sub_dev_semi);
        hal_sem_wait(dev->usb_virt_sub_dev_semi);

        /* 找到没有被bind的dev */
        if (dev->func_drv == NULL)
        {
            /* 事先尝试bind到一起 */
            dev->func_drv = drv;
            hal_log_info("---usb_virt_bus_drv_reg----1---\n");
            if (drv->func_drv_ext.probe_ext(dev) == 0)
            {
                /* device 和 driver 匹配成功, 就将 device 添加到 driver 的virt_dev_list中*/
                list_head_malloc_and_add(dev, &(drv->virt_dev_list));
            }
            else
            {
                /* 匹配失败, 就清空。device无人认领 */
                dev->func_drv = NULL;
            }
            hal_log_info("---usb_virt_bus_drv_reg----2---\n");
        }

        //UsbUnLock(dev->usb_virt_sub_dev_semi);
        hal_sem_post(dev->usb_virt_sub_dev_semi);
    }

    //UsbUnLock(my_usb_virt_bus.BusLock);
    hal_sem_post(my_usb_virt_bus.BusLock);
    return 0;
}

/*
********************************************************************************
*                     usb_virt_bus_drv_unreg
* Description:
*     将driver从总线上摘掉
* Arguments:
*     drv       : input.
* Return value:
*
* note:
*     注意该期间，dev不能使用，得用dev->usb_virt_dev_semi来保护
* 因为这个期间dev属于临界区域，处于混沌状态

* 遍历该func_driver所支持的scsi_device list,既scsi_func_driver->scsi_dev_list
* 如果dev->drv == drv(该dev的驱动 == 本驱动)则做如下操作:
*       1,从drv->scsi_dev_list中删除本dev
*       2,将dev->drv == NULL
*       3,将调用drv->scsi_remove
*********************************************************************************
*/
int32_t usb_virt_bus_drv_unreg(struct usb_host_func_drv *drv)
{
    struct usb_list_head *list_start = NULL;
    struct usb_list_head *list_now = NULL;
    struct usb_host_virt_sub_dev *dev = NULL;

    if (drv == NULL)
    {
        __err("PANIC : [VIRR BUS] : usb_virt_bus_drv_unreg() input == NULL");
        return -1;
    }

    //UsbLock(my_usb_virt_bus.BusLock);
    hal_sem_wait(my_usb_virt_bus.BusLock);

    /* 先unbind改drv与与之关联的dev */
    if (usb_list_empty(&(drv->virt_dev_list)))
    {
        /* 既然bus上的driver队列都空了, 也就没有必要去删除driver了 */
    }
    else
    {
        /* 遍历driver的virt_dev_list, 删除所有的device */
        list_start = &(drv->virt_dev_list);
        list_now = list_start->next;

        while (list_start != list_now)
        {
            dev = (struct usb_host_virt_sub_dev *)(list_now->data);

            if (dev == NULL)
            {
                __err("dev == NULL", dev);
                break;
            }

            list_now = list_now->next;
            //UsbLock(dev->usb_virt_sub_dev_semi);
            hal_sem_wait(dev->usb_virt_sub_dev_semi);

            if (dev)
            {
                if (drv->func_drv_ext.disconnect_ext)
                {
                    if (drv->func_drv_ext.disconnect_ext(dev) == 0)
                    {
                        //remove each other
                        dev->func_drv = NULL;
                        _usb_virt_bus_remov_dev_from_drv(dev, drv);
                    }
                    else
                    {
                        __err("PANIC : [VIRR BUS] : disconnect fail");
                    }
                }
            }

            //UsbUnLock(dev->usb_virt_sub_dev_semi);
            hal_sem_post(dev->usb_virt_sub_dev_semi);
        }
    }

    /* disconnect失败的device, 应该强行删除 */
    if (! usb_list_empty(&(drv->virt_dev_list)))
    {
        __err("PANIC : [VIRR BUS] : usb_virt_bus_drv_unreg() drv->dev_list not empty");
    }

    /* 从supper bus中删除本drv */
    list_head_ext_remov_node_from_list(drv, &(my_usb_virt_bus.drv_list));
    //UsbUnLock(my_usb_virt_bus.BusLock);
    hal_sem_post(my_usb_virt_bus.BusLock);
    return 0;
}


/*
********************************************************************************
*                     usb_virt_bus_dev_add
* Description:
*     将device添加到总线上
* Arguments:
*     dev  : input.
* Return value:
*
* note:
*     一个设备不能注册两次?????????
*********************************************************************************
*/
int32_t usb_virt_bus_dev_add(struct usb_host_virt_sub_dev *dev)
{
    uint32_t sr = 0;

    if (!dev || !(dev->father_dev))
    {
        __err("PANIC : [VIRR BUS] : usb_virt_bus_dev_add() : dev == NULL");
        return -1;
    }

    /* bus上已经存在deivce, 就不要再添加了 */
    if (list_node_exist((void *)dev, &(my_usb_virt_bus.dev_list)) == 0)
    {
        __err("ERR: device is already in the list");
        return 0;
    }

    //UsbLock(my_usb_virt_bus.BusLock);
    hal_sem_wait(my_usb_virt_bus.BusLock);

    if (dev->func_drv != NULL)
    {
        __err("PANIC : [VIRR BUS] : dev->drv != NULL,new dev has been bind to drv");
        //UsbUnLock(my_usb_virt_bus.BusLock);
        hal_sem_post(my_usb_virt_bus.BusLock);
        return -1;
    }
    else
    {
        /* 先前可能已经有driver连上bus了, 这里就去寻找bus上与之匹配的driver */
        struct usb_list_head *list_start  = NULL;
        struct usb_list_head *list_now = NULL;
        //UsbLock(dev->usb_virt_sub_dev_semi);
        hal_sem_wait(dev->usb_virt_sub_dev_semi);
        list_start = &(my_usb_virt_bus.drv_list);
        list_now = list_start->next;
        hal_log_info("--usb_virt_bus_dev_add---0\n");

        while (list_start != list_now)
        {
            struct usb_host_func_drv *func_drv = (struct usb_host_func_drv *)list_now->data;
            list_now = list_now->next;
            /* 事先尝试bind到一起 */
            dev->func_drv = func_drv;
            hal_log_info("--usb_virt_bus_dev_add---1\n");
            if (func_drv->func_drv_ext.probe_ext(dev) == 0)
            {
                /* add 到drv的 dev list中 */
                //USB_OS_ENTER_CRITICAL(sr);
                sr = hal_spin_lock_irqsave(&device_lock);
                list_head_malloc_and_add(dev, &(func_drv->virt_dev_list));
                hal_spin_unlock_irqrestore(&device_lock, sr);
                //USB_OS_EXIT_CRITICAL(sr);
                break;  /* 遇到第一个macth的drv就结束。 */
            }
            else
            {
                dev->func_drv = NULL; /* 失败则清空 */
            }
        hal_log_info("--usb_virt_bus_dev_add---2\n");
        }

        //UsbUnLock(dev->usb_virt_sub_dev_semi);
        hal_sem_post(dev->usb_virt_sub_dev_semi);

    }

    /* 将dev添加到supper bus */
    //USB_OS_ENTER_CRITICAL(sr);
    sr = hal_spin_lock_irqsave(&device_lock);
    list_head_malloc_and_add(dev, &(my_usb_virt_bus.dev_list));
    hal_spin_unlock_irqrestore(&device_lock, sr);
    hal_sem_post(my_usb_virt_bus.BusLock);
    //USB_OS_EXIT_CRITICAL(sr);
    //UsbUnLock(my_usb_virt_bus.BusLock);
    return 0;
}

/*
********************************************************************************
*                     usb_virt_bus_dev_add
* Description:
*     将device添加到总线上
* Arguments:
*     dev  : input.
* Return value:
*
* note:
*     注意该期间，dev不能使用，得用dev->scsi_dev_semi来保护
* 因为这个期间dev属于临界区域，处于混沌状态用dev->usb_virt_dev_semi保护
*    从dev->drv中删除本dev
*    调用drv->scsi_remove
*    dev->drv == NULL
*********************************************************************************
*/
int32_t usb_virt_bus_dev_del(struct usb_host_virt_sub_dev *dev)
{
    struct usb_host_func_drv *func_driver = NULL;

    if (dev == NULL)
    {
        __err("PANIC : [VIRR BUS] : usb_virt_bus_dev_del() input == NULL");
        return -1;
    }

    //UsbLock(my_usb_virt_bus.BusLock);
    hal_sem_wait(my_usb_virt_bus.BusLock);
    func_driver = dev->func_drv;
    //UsbLock(dev->usb_virt_sub_dev_semi);
    hal_sem_wait(dev->usb_virt_sub_dev_semi);

    if (func_driver)
    {
        if (func_driver->func_drv_ext.disconnect_ext)
        {
            if (func_driver->func_drv_ext.disconnect_ext(dev) == 0)
            {
                //remove each other
                dev->func_drv = NULL;
                _usb_virt_bus_remov_dev_from_drv(dev, func_driver);
            }
            else
            {
                __err("PANIC : [VIRR BUS] :  disconnect fail");
            }
        }
    }
    else
    {
        __err("PANIC : [VIRR BUS] : usb_virt_bus_dev_del() dev->drv == NULL");
    }

    //UsbUnLock(dev->usb_virt_sub_dev_semi);
    hal_sem_post(dev->usb_virt_sub_dev_semi);
    //del from supper bus
    list_head_ext_remov_node_from_list(dev, &(my_usb_virt_bus.dev_list));
    //UsbUnLock(my_usb_virt_bus.BusLock);
    hal_sem_post(my_usb_virt_bus.BusLock);

    return 0;
}

/*
********************************************************************************
*                     usb_virt_bus_init
* Description:
*     bus的初始化只是初始化device list和driver list
* Arguments:
*     void
* Return value:
*     void
* note:
*     void
*********************************************************************************
*/
int32_t usb_virt_bus_init(void)
{
    memset(&my_usb_virt_bus, 0, sizeof(struct usb_virt_bus));
    USB_INIT_LIST_HEAD(& (my_usb_virt_bus.dev_list));
    USB_INIT_LIST_HEAD(&(my_usb_virt_bus.drv_list));

//    my_usb_virt_bus.BusLock = USB_OS_SemCreate(1);
    my_usb_virt_bus.BusLock = hal_sem_create(1);

    if (my_usb_virt_bus.BusLock == NULL)
    {
        __err("ERR: usb_virt_bus_init: my_usb_virt_bus.BusLock == NULL");
        return -1;
    }

    return 0;
}

/*
********************************************************************************
*                     usb_virt_bus_exit
* Description:
*
* Arguments:
*     void
* Return value:
*     void
* note:
*     void
*********************************************************************************
*/
int32_t usb_virt_bus_exit(void)
{
    // uint8_t err = 0;

    if (my_usb_virt_bus.BusLock)
    {
        //    USB_OS_SemDel(my_usb_virt_bus.BusLock, &err);
        hal_sem_delete(my_usb_virt_bus.BusLock);
        my_usb_virt_bus.BusLock = NULL;
    }
    else
    {
        __err("ERR: usb_virt_bus_exit: my_usb_virt_bus.BusLock == NULL");
        return -1;
    }

    memset(&my_usb_virt_bus, 0, sizeof(struct usb_virt_bus));
    USB_INIT_LIST_HEAD(&(my_usb_virt_bus.dev_list));
    USB_INIT_LIST_HEAD(&(my_usb_virt_bus.drv_list));
    return 0;
}
