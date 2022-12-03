/*
*******************************************************************************
*                                              usb host module                                           *
*                                                                                                                                          *
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.                       *
*                               All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.07.xx
*
* Description :
*
* History :
*******************************************************************************
*/
//#include "usb_host_config.h"
#include <string.h>

//#include <usb/usb_os_platform.h>
#include <usb_host_common.h>

//#include "usb_host_base_types.h"
#include <usb_list.h>
#include <usb_gen_dev_mod.h>
#include <usb_drv_dev_macth.h>
#include "usb_virt_bus.h"
#include "usb_gen_hcd.h"
#include "usb_msg.h"
//#include <atomic.h>
#include <hal_osal.h>


static u32 usb_host_is_run_flag = 0;

#define USB_HOST_IS_RUN_TRUE    0x11
#define USB_HOST_IS_RUN_FAIL    0x22


//usb host开启
void usb_host_enable(void)
{
    usb_host_is_run_flag = USB_HOST_IS_RUN_TRUE;
}
//usb host 禁止
void usb_host_disable(void)
{
    usb_host_is_run_flag = USB_HOST_IS_RUN_FAIL;
}
//查询usb host是否开启
//return    :   非0为enable
u8 usb_host_is_enabled(void)
{
    return (usb_host_is_run_flag == USB_HOST_IS_RUN_TRUE) ? 0x01 : 0x00;
}

/**
 * usb_host_alloc_virt_dev - usb device constructor (usbcore-internal)
 * @parent: hub to which device is connected; null to allocate a root hub
 * @bus: bus used to access the device
 * @port1: one-based index of port; ignored for root hubs
 * Context: !in_interrupt ()
 *
 * Only hub drivers (including virtual root hub drivers for host
 * controllers) should ever call this.
 *
 * This call may not be used in a non-sleeping context.
 */
/* 创建usb_host_virt_dev结构 */
struct usb_host_virt_dev *usb_host_alloc_virt_dev(struct usb_host_virt_dev *parent, struct usb_virt_bus *bus, u32 port1)
{
    struct usb_host_virt_dev *dev = NULL;
    s32 i = 0;

    if (bus == NULL)
    {
        __err("PANIC : usb_host_alloc_virt_dev()  : input == NULL");
        return NULL;
    }

    // dev =  hal_malloc(sizeof(*dev));
    dev =  hal_malloc(sizeof(struct usb_host_virt_dev));

    if (!dev)
    {
        __err("PANIC : usb_host_alloc_virt_dev()  : dev == NULL");
        return NULL;
    }

    memset(dev, 0, sizeof(struct usb_host_virt_dev));
    dev->state = USB_STATE_ATTACHED;

    INIT_LIST_HEAD(&dev->ep0.urb_list);
    dev->ep0.desc.bLength = USB_DT_ENDPOINT_SIZE;
    dev->ep0.desc.bDescriptorType = USB_DT_ENDPOINT;
    /* ep0 maxpacket comes later, from device descriptor */
    dev->ep_in[0] = dev->ep_out[0] = &dev->ep0;
    /* Save readable and stable topology id, distinguishing devices
     * by location for diagnostics, tools, driver model, etc.  The
     * string is a path along hub ports, from the root.  Each device's
     * dev->devpath will be stable until USB is re-cabled, and hubs
     * are often labeled with these port numbers.  The bus_id isn't
     * as stable:  bus->busnum changes easily from modprobe order,
     * cardbus or pci hotplugging, and so on.
     */
    /*
        if ((!parent)) {
            dev->devpath [0] = '0';

            dev->dev.parent = bus->controller;
            sprintf (&dev->dev.bus_id[0], "usb%d", bus->busnum);
        } else {
            //match any labeling on the hubs; it's one-based
            if (parent->devpath [0] == '0')
                snprintf (dev->devpath, sizeof dev->devpath,
                    "%d", port1);
            else
                snprintf (dev->devpath, sizeof dev->devpath,
                    "%s.%d", parent->devpath, port1);

            dev->dev.parent = &parent->dev;
            sprintf (&dev->dev.bus_id[0], "%d-%s",
                bus->busnum, dev->devpath);

            // hub driver sets up TT records
        }
    */
    dev->bus = bus;
    dev->parent = parent;
    //?INIT_LIST_HEAD(&dev->filelist);

    dev->usb_virt_dev_semi =  hal_sem_create(1);

    //=================================
    //初始化virt_sub_dev部分
    for (i = 0; i < USB_MAX_VIRT_SUB_DEV_NR; i ++)
    {
        dev->virt_sub_dev_array[i].usb_virt_sub_dev_semi = hal_sem_create(1);
    }

    return dev;
}



void usb_host_free_virt_dev(struct usb_host_virt_dev *virt_dev)
{
    s32 i = 0;
    u8 err = 0;

    if (virt_dev == NULL)
    {
        __err("PANIC : usb_host_free_virt_dev() : input == NULL");
        return ;
    }

    // --<1>--释放semi
    // 释放virt_sub_dev部分
    for (i = 0; i < USB_MAX_VIRT_SUB_DEV_NR; i ++)
    {
       if (virt_dev->virt_sub_dev_array[i].usb_virt_sub_dev_semi)
       {
           hal_sem_delete(virt_dev->virt_sub_dev_array[i].usb_virt_sub_dev_semi);
       }
       else
       {
           __err("PANIC : usb_host_free_virt_dev() : virt_sub_dev`s semi == NULL");
           return;
       }
    }

    if (virt_dev->usb_virt_dev_semi)
    {
       hal_sem_delete(virt_dev->usb_virt_dev_semi);
    }
    else
    {
       __err("PANIC : usb_host_free_virt_dev() : virt_dev`s semi == NULL");
       return;
    }

    //--<2>--释放string
    if (virt_dev->manufacturer)
    {
        free(virt_dev->manufacturer);
        virt_dev->manufacturer = NULL;
    }
    else
    {
        __err("ERR: parameter is NULL, can't free");
    }

    if (virt_dev->product)
    {
        free(virt_dev->product);
        virt_dev->product = NULL;
    }
    else
    {
        __err("ERR: parameter is NULL, can't free");
    }

    if (virt_dev->serial)
    {
        free(virt_dev->serial);
        virt_dev->serial = NULL;
    }
    else
    {
        __err("ERR: parameter is NULL, can't free");
    }

    //--<3>--释放,所有相关描述符
    if (virt_dev->config)
    {
        int j = 0;
        int k = 0;
        int l = 0;
        //int m = 0;

        for (j = 0; j < virt_dev->descriptor.bNumConfigurations ; j++)
        {
            for (k = 0; k < virt_dev->config[j].desc.bNumInterfaces ; k++)
            {
                for (l = 0; l < virt_dev->config[j].intf_cache[k]->num_altsetting; l++)
                {
                    //for(m = 0; m < virt_dev->config[j].intf_cache[k].altsetting_array[l].desc.bNumEndpoints; m++){
                    if (virt_dev->config[j].intf_cache[k]->altsetting_array[l].endpoint)
                    {
                        free(virt_dev->config[j].intf_cache[k]->altsetting_array[l].endpoint);
                        virt_dev->config[j].intf_cache[k]->altsetting_array[l].endpoint = NULL;
                    }
                    else
                    {
                        __err("ERR: parameter is NULL, can't free");
                    }

                    //}
                }

                if (virt_dev->config[j].intf_cache[k]->altsetting_array)
                {
                    free(virt_dev->config[j].intf_cache[k]->altsetting_array);
                    virt_dev->config[j].intf_cache[k]->altsetting_array = NULL;
                }
                else
                {
                    __err("ERR: parameter is NULL, can't free");
                }

                if (virt_dev->config[j].intf_cache[k])
                {
                    free(virt_dev->config[j].intf_cache[k]);
                    virt_dev->config[j].intf_cache[k] = NULL;
                }
                else
                {
                    __err("ERR: parameter is NULL, can't free");
                }

                /*--在usb_disable_device()中已经删除了
                DMSG_INFO("new_interfaces[n]--free-- = %x",virt_dev->config[j].interfac[k]);
                if(virt_dev->config[j].interfac[k]){
                    free(virt_dev->config[j].interfac[k]);
                    virt_dev->config[j].interfac[k] = NULL;
                }
                */
            }

            //free
            //free(virt_dev->config->intf_cache);
            //virt_dev->config->intf_cache = NULL;
        }

        //free
        if (virt_dev->config)
        {
            free(virt_dev->config);
            virt_dev->config = NULL;
        }
        else
        {
            __err("ERR: parameter is NULL, can't free");
        }
    }

    for (i = 0; i < virt_dev->descriptor.bNumConfigurations; i++)
    {
        if (virt_dev->rawdescriptors[i])
        {
            free(virt_dev->rawdescriptors[i]);
            virt_dev->rawdescriptors[i] = NULL;
        }
        else
        {
            __err("ERR: parameter is NULL, can't free");
        }
    }

    if (virt_dev->rawdescriptors)
    {
        free(virt_dev->rawdescriptors);
        virt_dev->rawdescriptors = NULL;
    }
    else
    {
        __err("ERR: parameter is NULL, can't free");
    }

    //--<4>--释放自己
    free(virt_dev);
    // virt_dev = NULL;
    return;
}

//return    :   0       //成功
//      :   其余    //失败
int32_t _usb_core_func_drv_probe_interface(struct usb_host_virt_sub_dev *sub_dev)
{
    struct usb_interface *intf = NULL;
    struct usb_host_func_drv *func_drv = NULL;
    const struct usb_drv_dev_match_table  *id = NULL;
    s32 error = -ENODEV;
    struct usb_host_virt_dev *virt_dev = NULL;

    if (!sub_dev || !(sub_dev->sub_dev_interface))
    {
        __err("PANIC : _usb_core_func_drv_probe_interface() : input fail,sub_dev = 0x%x ,");
        return  -ENODEV;
    }

    intf = usb_mod_to_usb_interface(sub_dev);
    func_drv = sub_dev->func_drv;
    hal_log_info("----func_drv->func_drv_name = %s\n", func_drv->func_drv_name);

    if (!func_drv->probe)
    {
        __err("PANIC : _usb_core_func_drv_probe_interface() : func_drv->probe == NULL");
        return error;
    }

    /* FIXME we'd much prefer to just resume it ... */
    virt_dev = usb_mod_interface_to_usbdev(intf);

    if (virt_dev == NULL)
    {
        __err("PANIC : virt_dev == NULL");
        return error;
    }

    if (virt_dev->state == USB_STATE_SUSPENDED)
    {
        __err("PANIC : virt_dev->state == USB_STATE_SUSPENDED");
        return -EHOSTUNREACH;
    }
    hal_log_info("---usb_core_func_drv_probe----1---\n");
    id = usb_match_id(intf, func_drv->match_table);

    if (id)
    {
        intf->condition = USB_INTERFACE_BINDING;
    hal_log_info("---usb_core_func_drv_probe----2---\n");
        error = func_drv->probe(intf, id);
    hal_log_info("---usb_core_func_drv_probe----3---\n");
        intf->condition = error ? USB_INTERFACE_UNBOUND : USB_INTERFACE_BOUND;
        return error;
    }

    return -ENODEV; //失败
}

int32_t _usb_core_func_drv_disconncet_interface(struct usb_host_virt_sub_dev *dev)
{
    struct usb_interface *intf = NULL;
    struct usb_host_func_drv *driver = NULL;

    if (dev == NULL)
    {
        __err("ERR; invalid argment");
        return -1;
    }

    intf = usb_mod_to_usb_interface(dev);

    if (intf == NULL)
    {
        __err("ERR; invalid argment");
        return -1;
    }

    driver = usb_mod_interface_to_func_drv(intf);

    if (driver == NULL)
    {
        __err("ERR; invalid argment");
        return -1;
    }

    intf->condition = USB_INTERFACE_UNBINDING;
    /* release all urbs for this interface */
    usb_disable_interface(usb_mod_interface_to_usbdev(intf), intf);

    /* 调用driver的disconnect,如msc_disconnect() */
    if (driver && driver->disconnect)
    {
        driver->disconnect(intf);
    }

    /* reset other interface state */
    usb_set_interface(usb_mod_interface_to_usbdev(intf),
                      intf->altsetting[0].desc.bInterfaceNumber,
                      0);
    usb_mod_usb_set_intf_priv_data(intf, NULL);
    intf->condition = USB_INTERFACE_UNBOUND;
    return 0;
}


/**
 * usb_altnum_to_altsetting - get the altsetting structure with a given
 *  alternate setting number.
 * @intf: the interface containing the altsetting in question
 * @altnum: the desired alternate setting number
 *
 * This searches the altsetting array of the specified interface for
 * an entry with the correct bAlternateSetting value and returns a pointer
 * to that entry, or null.
 *
 * Note that altsettings need not be stored sequentially by number, so
 * it would be incorrect to assume that the first altsetting entry in
 * the array corresponds to altsetting zero.  This routine helps device
 * drivers avoid such mistakes.
 *
 * Don't call this function unless you are bound to the intf interface
 * or you have locked the device!
 */
struct usb_host_virt_interface *usb_altnum_to_altsetting(struct usb_interface *intf, s32 altnum)
{
    int i;

    for (i = 0; i < intf->num_altsetting; i++)
    {
        if (intf->altsetting[i].desc.bAlternateSetting == altnum)
        {
            return &intf->altsetting[i];
        }
    }

    return NULL;
}

/**
 * usb_lock_device - acquire the lock for a usb device structure
 * @udev: device that's being locked
 *
 * Use this routine when you don't hold any other device locks;
 * to acquire nested inner locks call down(&udev->serialize) directly.
 * This is necessary for proper interaction with usb_lock_all_devices().
 */
void usb_lock_device(struct usb_host_virt_dev *virt_dev)
{
    u8 err = 0;
    //down_read(&usb_all_devices_rwsem);
    //USB_OS_SEMI_PEND(virt_dev->usb_virt_dev_semi, 0, &err);
    hal_sem_wait(virt_dev->usb_virt_dev_semi);
}

/**
 * usb_unlock_device - release the lock for a usb device structure
 * @udev: device that's being unlocked
 *
 * Use this routine when releasing the only device lock you hold;
 * to release inner nested locks call up(&udev->serialize) directly.
 * This is necessary for proper interaction with usb_lock_all_devices().
 */
void usb_unlock_device(struct usb_host_virt_dev *virt_dev)
{
    //USB_OS_SEMI_POST(virt_dev->usb_virt_dev_semi);
    hal_sem_post(virt_dev->usb_virt_dev_semi);
    //up_read(&usb_all_devices_rwsem);
}




void *usb_buffer_alloc(struct usb_host_virt_dev *dev, u32 size, u32 mem_flags, void *dma)
{
    return hcd_ops_buffer_alloc(dev->bus, size, mem_flags, dma);
}

/**
 * usb_buffer_free - free memory allocated with usb_buffer_alloc()
 * @dev: device the buffer was used with
 * @size: requested buffer size
 * @addr: CPU address of buffer
 * @dma: DMA address of buffer
 *
 * This reclaims an I/O buffer, letting it be reused.  The memory must have
 * been allocated using usb_buffer_alloc(), and the parameters must match
 * those provided in that allocation request.
 */
void usb_buffer_free(struct usb_host_virt_dev *dev, u32 size, void *addr, void *dma)
{
    hcd_ops_buffer_free(dev->bus, size, addr, dma);
}

/**
 * usb_ifnum_to_if - get the interface object with a given interface number
 * @dev: the device whose current configuration is considered
 * @ifnum: the desired interface
 *
 * This walks the device descriptor for the currently active configuration
 * and returns a pointer to the interface with that particular interface
 * number, or null.
 *
 * Note that configuration descriptors are not required to assign interface
 * numbers sequentially, so that it would be incorrect to assume that
 * the first interface in that descriptor corresponds to interface zero.
 * This routine helps device drivers avoid such mistakes.
 * However, you should make sure that you do the right thing with any
 * alternate settings available for this interfaces.
 *
 * Don't call this function unless you are bound to one of the interfaces
 * on this device or you have locked the device!
 */
struct usb_interface *usb_ifnum_to_if(struct usb_host_virt_dev *dev, u32  ifnum)
{
    struct usb_host_virt_config *config = dev->actconfig;
    int i;

    if (!config)
    {
        __err("ERR: input = NULL");
        return NULL;
    }

    for (i = 0; i < config->desc.bNumInterfaces; i++)
    {
        if (config->interfac[i]->altsetting[0].desc.bInterfaceNumber == ifnum)
        {
            return config->interfac[i];
        }
    }

    return NULL;
}


