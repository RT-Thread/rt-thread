/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : UsbBlkDev.h
*
* Author        : javen
*
* Version       : 2.0
*
* Date          : 2010.03.02
*
* Description   :
*
* History       :
*
********************************************************************************************************************
*/
#ifndef  __BLKDEV_H__
#define  __BLKDEV_H__

#include  "usbh_disk_info.h"

#define  USB_BLK_DEV_MAGIC              0x5a13d099
#define  USB_BULK_DISK_MAX_NAME_LEN     32

typedef struct __UsbBlkDev
{
    unsigned int   last_lun;               //如果为1，表示是最后一个分区
    unsigned int   Magic;                  /* 表示设备是否合法                 */
    __mscLun_t *Lun;                /* sd和其他scsi device共有的属性    */

    /* Disk information */
    unsigned int used;                     /* 打开设备计数                     */
    __dev_devop_t DiskOp;           /* 设备操作函数                     */

    /* Disk manager */
    void *DevParaHdle;      /* open时的句柄                     */
    void *DevRegHdle;       /* reg时的句柄                      */

    unsigned int DevNo;                                /* 此设备号, 它由host_id, target_id, lun 组成   */
    unsigned char ClassName[USB_BULK_DISK_MAX_NAME_LEN]; /* 设备类名, 如"disk"               */
    unsigned char DevName[USB_BULK_DISK_MAX_NAME_LEN];   /* 此设备名, 如"SCSI_DISK_000"      */

    unsigned int is_RegDisk;               /* 是否注册过disk设备                           */
    unsigned int ErrCmdNr;                 /* test_unit_ready期间, 未知错误的次数          */

    void *Extern;                   /* 扩展属性, 如cd                               */

    usbh_disk_device_info_t device_info;
} __UsbBlkDev_t;

//------------------------------------------
//
//------------------------------------------
__UsbBlkDev_t *UsbBlkDevAllocInit(__mscLun_t *mscLun);
int UsbBlkDevFree(__UsbBlkDev_t *BlkDev);

void GetDiskInfo(__UsbBlkDev_t *BlkDev);
void ShutDown(__UsbBlkDev_t *BlkDev);

int UsbBlkDevReg(__UsbBlkDev_t *BlkDev, unsigned char *ClassName, unsigned int RegDisk);
int UsbBlkDevUnReg(__UsbBlkDev_t *BlkDev);


#endif   //__BLKDEV_H__


