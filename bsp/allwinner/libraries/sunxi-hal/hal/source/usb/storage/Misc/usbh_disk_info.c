/*
********************************************************************************************************************
*                                              usb_host
*
*                              (c) Copyright 2007-2009, javen.China
*                                       All Rights Reserved
*
* File Name     : usbh_disk_info.c
*
* Author        : javen
*
* Version       : 1.0
*
* Date          : 2009.08.18
*
* Description   : host支持海量存储类时候的读写状况获取
*
* History       :
*
*
********************************************************************************************************************
*/
#include  "usb_os_platform.h"
#include  "list_head_ext.h"
#include  "usbh_disk_info.h"
#include  "error.h"
#include  "usb_msc_i.h"

static usbh_disk_info_t usbh_disk_info;  /* handle */
static unsigned int  usb_disk_status = 0;         /* disk status */

static int usbh_disk_GetDeviceInfo(usbh_disk_info_t *disk_info,
                                     char *DeviceName,
                                     usbhDeivceInfo_t *usbhDeivceInfo);

/*
*********************************************************************
*                     set_usbh_disk_status
*
* Description:
*
* Arguments:
*    void
* Returns:
*    void
* note:
*    无
*
*********************************************************************
*/
void set_usbh_disk_status(unsigned int status)
{
    unsigned int cpu_sr = 0;
    ENTER_CRITICAL(cpu_sr);
    usb_disk_status = status;
    EXIT_CRITICAL(cpu_sr);
}

/*
*********************************************************************
*                     get_usbh_disk_status
*
* Description:
*
* Arguments:
*    void
* Returns:
*    void
* note:
*    无
*
*********************************************************************
*/
unsigned int get_usbh_disk_status(void)
{
    return usb_disk_status;
}

/*
*********************************************************************
*                     usbh_disk_info_open
*
* Description:
*
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
static void *  usbh_disk_info_open(void *open_arg, uint32_t mode)
{
    usbh_disk_info_t *info = &usbh_disk_info;
    info->cnt++;
    return (void *)info;
}

/*
*********************************************************************
*                     usbh_disk_info_open
*
* Description:
*
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
static int32_t usbh_disk_info_close(void * hDev)
{
    usbh_disk_info_t *info = &usbh_disk_info;

    if (hDev != (void *)info)
    {
        hal_log_err("PANIC : usbh_disk_info_close() : handle error\n");
        return EPDK_FAIL;
    }

    info->cnt--;
    return EPDK_OK;
}


/*
*********************************************************************
*                     usbh_disk_info_open
*
* Description:
*
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
static uint32_t usbh_disk_info_read(void *pBuffer, uint32_t blk, uint32_t n, void * hDev)
{
    hal_log_err("WARN : usbh_disk_info_read() : can read nothing\n");
    return 0;
}

/*
*********************************************************************
*                     usbh_disk_info_open
*
* Description:
*
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
static uint32_t usbh_disk_info_write(const void *pBuffer, uint32_t blk, uint32_t n, void * hDev)
{
    hal_log_err("WARN : usbh_disk_info_write() : can write nothing\n");
    return 0;
}

/*
*********************************************************************
*                     usbh_disk_info_open
*
* Description:
*
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
static int32_t usbh_disk_info_ioctrl(void * hDev, uint32_t Cmd, long Aux, void *pBuffer)
{
    usbh_disk_info_t *info = &usbh_disk_info;

    if (hDev != (void *)info)
    {
        hal_log_err("ERR : handle error, (0x%x, 0x%x)\n", hDev, info);
        return EPDK_FAIL;
    }

    switch (Cmd)
    {
        case USB_DEVICE_INFO_USER_CMD_GET_DISK_STATUS:  //read读取当前所有lun的读写状态
        {
            unsigned int *p_status = (unsigned int *)pBuffer;

            if (pBuffer == NULL)
            {
                hal_log_err("PANIC : usbh_disk_info_ioctrl() : buff == NULL, error\n");
                return EPDK_FAIL;
            }

            *p_status = get_usbh_disk_status();
        }
        break;

        case USB_DEVICE_INFO_USER_CMD_GET_DEVICE_INFO:
            return usbh_disk_GetDeviceInfo(&usbh_disk_info, (char *)Aux, (usbhDeivceInfo_t *)pBuffer);

        //break;

        default:
            hal_log_err("ERR : usbh_disk_info_ioctrl(), unkown cmd(0x%x)\n", Cmd);
            return EPDK_FAIL;
    }

    return EPDK_OK;
}

static __dev_devop_t usbh_disk_info_op =
{
    usbh_disk_info_open,
    usbh_disk_info_close,
    usbh_disk_info_read,
    usbh_disk_info_write,
    usbh_disk_info_ioctrl
};

/*
*********************************************************************
*                     usbh_disk_SaveDeviceInfo
*
* Description:
*
*
* Arguments:
*
*
* Returns:
*
*
* note:
*
*
*********************************************************************
*/
void usbh_disk_SaveDeviceInfo(usbh_disk_device_info_t *device_info)
{
    usbh_disk_info_t *disk_info = &usbh_disk_info;

    if (device_info == NULL)
    {
        hal_log_err("ERR: input error\n");
        return ;
    }
    list_head_malloc_and_add((void *)device_info, &(disk_info->device_list));
}

/*
*********************************************************************
*                     usbh_disk_FreeDeviceInfo
*
* Description:
*
*
* Arguments:
*
*
* Returns:
*
*
* note:
*
*
*********************************************************************
*/
void usbh_disk_FreeDeviceInfo(usbh_disk_device_info_t *device_info)
{
    usbh_disk_info_t *disk_info = &usbh_disk_info;

    if (device_info == NULL)
    {
        hal_log_err("ERR: input error\n");
        return ;
    }

    list_del_node_by_data((void *)device_info, &(disk_info->device_list));
}

/*
*********************************************************************
*                     usbh_disk_GetDeviceInfo
*
* Description:
*
*
* Arguments:
*
*
* Returns:
*
*
* note:
*
*
*********************************************************************
*/
static int usbh_disk_GetDeviceInfo(usbh_disk_info_t *disk_info,
                                     char *DeviceName,
                                     usbhDeivceInfo_t *usbhDeivceInfo)
{
    struct usb_list_head *head      = NULL;
    struct usb_list_head *list_now  = NULL;
    struct usb_list_head *list_next = NULL;
    usbh_disk_device_info_t *device_info = NULL;
    unsigned int is_find = 0;

    if (DeviceName == NULL || disk_info == NULL)
    {
        hal_log_err("ERR: input error\n");
        return EPDK_FAIL;
    }

    head = &(disk_info->device_list);
    list_now = head->next;

    while (head != list_now)
    {
        list_next = list_now->next;
        device_info = (usbh_disk_device_info_t *)list_now->data;

        if (device_info)
        {
            /* 找到对应的设备 */
            if (strcmp(DeviceName, device_info->DeviceName) == 0)
            {
                memcpy(usbhDeivceInfo, &device_info->DeivceInfo, sizeof(usbhDeivceInfo_t));
                is_find = 1;
            }
        }

        list_now = list_next;
    }

    if (is_find)
    {
        return EPDK_OK;
    }

    return EPDK_FAIL;
}

/*
*********************************************************************
*                     usbh_disk_info_open
*
* Description:
*     sd信息设备，目前主要用于监测sd设备的读写情况
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
int usbh_disk_info_reg(void)
{
    usbh_disk_info_t *info = &usbh_disk_info;
    usb_disk_status = 0;
    memset(info, 0, sizeof(usbh_disk_info_t));
    USB_INIT_LIST_HEAD(&info->device_list);
    info->reghandle = esDEV_DevReg(DEV_CLASS_USERDEF, USB_DEVICE_INFO_NAME, &usbh_disk_info_op, NULL);

    if (info->reghandle == NULL)
    {
        hal_log_err("ERR: register to the block layer failed.\n");
        return -1;
    }

    return 0;
}

/*
*********************************************************************
*                     usbh_disk_info_open
*
* Description:
*     sd信息设备，目前主要用于监测sd设备的读写情况
* Arguments:
*
* Returns:
*
* note:
*
*
*********************************************************************
*/
int usbh_disk_info_unreg(void)
{
    usbh_disk_info_t *info = &usbh_disk_info;
    int ret = 0;

    if (info->reghandle == NULL)
    {
        hal_log_err("ERR: usbh_disk_info_unreg: info->reghandle == NULL\n");
        return -1;
    }

    ret = esDEV_DevUnreg(info->reghandle);
    memset(info, 0, sizeof(usbh_disk_info_t));
    return ret;
}


