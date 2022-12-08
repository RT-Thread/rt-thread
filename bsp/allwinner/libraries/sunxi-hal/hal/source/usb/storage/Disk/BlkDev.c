/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : UsbBlkDev.c
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
#include  "usbh_buff_manager.h"
#include  "usb_msc_i.h"
#include  "Scsi2.h"
#include  "BlkDev.h"
#include  "CD.h"
#include  "error.h"

/*
*******************************************************************************
*                     DiskOpen
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static void *DiskOpen(void *open_arg, uint32_t mode)
{
    __UsbBlkDev_t *BlkDev = NULL;

    if (open_arg == NULL)
    {
        hal_log_err("ERR: DiskOpen: input error, open_arg = %x", open_arg);
        return NULL;
    }

    BlkDev = (__UsbBlkDev_t *)open_arg;

    if (BlkDev->Magic != USB_BLK_DEV_MAGIC)
    {
        hal_log_err("ERR: DiskOpen: BlkDev Magic(%x) is invalid", BlkDev->Magic);
        return NULL;
    }

    BlkDev->used++;
    return (void *)open_arg;
}

/*
*******************************************************************************
*                     DiskClose
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static int32_t DiskClose(void * hDev)
{
    __UsbBlkDev_t *BlkDev = NULL;

    if (hDev == NULL)
    {
        hal_log_err("ERR: DiskClose: input error, hDev = %x", hDev);
        return EPDK_FAIL;
    }

    BlkDev = (__UsbBlkDev_t *)hDev;

    if (BlkDev->Magic != USB_BLK_DEV_MAGIC)
    {
        hal_log_err("ERR: DiskClose: BlkDev Magic(%x) is invalid", BlkDev->Magic);
        return EPDK_FAIL;
    }

    BlkDev->used--;
    return EPDK_OK;
}

/*
*******************************************************************************
*                     __DiskRead
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static unsigned int __DiskRead(void *pBuffer, unsigned int blk, unsigned int n, void * hDev)
{
    __UsbBlkDev_t *BlkDev = NULL;
    __mscLun_t *mscLun = NULL;
    unsigned int cmd_version = 10;   /* 默认为10 */
    int ret = 0;

    if (hDev == NULL)
    {
        hal_log_err("ERR: __DiskRead: input error, hDev = %x", hDev);
        return EPDK_FAIL;
    }

    if (n == 0)
    {
        hal_log_err("ERR: __DiskRead: the read length can not be zero");
        return EPDK_FAIL;
    }

    //DMSG_MSC_TEST("__DiskRead: Blk = %d, N = %d, LastBlk = %d", blk, n, (blk + n));
    BlkDev = (__UsbBlkDev_t *)hDev;

    if (BlkDev->Magic != USB_BLK_DEV_MAGIC)
    {
        hal_log_err("ERR: __DiskRead: BlkDev Magic(%x) is invalid", BlkDev->Magic);
        return EPDK_FAIL;
    }

    /* 如果没有注册disk设备, 就不能够读数据 */
    if (!BlkDev->is_RegDisk)
    {
        hal_log_err("ERR: __DiskRead: Not reged Disk, can not read");
        return EPDK_FAIL;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: __DiskRead: mscLun == NULL");
        return EPDK_FAIL;
    }

    /* 如果介质不存在, 就不能够从设备读数据 */
    if (!mscLun->MediaPresent)
    {
        hal_log_err("ERR: __DiskRead: media is not present, __DiskRead failed");
        return EPDK_FAIL;
    }

    if ((blk + n) > mscLun->disk_info.capacity)
    {
        hal_log_err("ERR: __DiskRead: block(%x, %x) is adjacence max capacity(%x)", blk, n, mscLun->disk_info.capacity);
        return EPDK_FAIL;
    }

    //set_usbh_disk_status(USB_STORAGE_DEVICE_STATUS_READ);
    /*
        if(mscLun->mscDev->SubClass == USBMSC_SUBCLASS_SCSI){
            if(mscLun->disk_info.capacity > 0xffffffff){
                cmd_version = 16;
            }else if(mscLun->disk_info.capacity > 0x1fffff){
                cmd_version = 10;
            }else{
                cmd_version = 6;
            }
        }else{
            cmd_version = 10;
        }
    */
    /* 目前所见的USB设备里面都使用的是10字节命名，而且协议规定的是10/12字节命令 */
    cmd_version = 10;
    hal_sem_wait(mscLun->Lock);

    if (cmd_version == 16)
    {
        ret = ScsiRead(mscLun, 16, blk, n, pBuffer,
                       (n * (mscLun->disk_info.sector_size)));
    }
    else if (cmd_version == 10)
    {
        ret = ScsiRead(mscLun, 10, blk, n, pBuffer,
                       (n * (mscLun->disk_info.sector_size)));
    }
    else
    {
        ret = ScsiRead(mscLun, 6, blk, n, pBuffer,
                       (n * (mscLun->disk_info.sector_size)));
    }

    hal_sem_post(mscLun->Lock);
    //set_usbh_disk_status(USB_STORAGE_DEVICE_STATUS_IDLE);

    if (ret != 0)
    {
        hal_log_err("ERR: ScsiRead%d failed. DevNo = %d, blk = %d, n = %d", cmd_version, BlkDev->DevNo, blk, n);
        return EPDK_FAIL;
    }

    return n;
}

/*
*******************************************************************************
*                     __DiskWrite
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static unsigned int __DiskWrite(const void *pBuffer, unsigned int blk, unsigned int n, void * hDev)
{
    __UsbBlkDev_t *BlkDev = NULL;
    __mscLun_t *mscLun = NULL;
    unsigned int cmd_version = 10;   /* 默认为10 */
    int ret = 0;

    if (hDev == NULL)
    {
        hal_log_err("ERR: __DiskWrite: input error, hDev = %x", hDev);
        return 0;
    }

    if (n == 0)
    {
        hal_log_err("ERR: __DiskWrite: the write length can not be zero");
        return 0;
    }

    //DMSG_MSC_TEST("__DiskWrite: Blk = %d, N = %d, LastBlk = %d", blk, n, (blk + n));
    BlkDev = (__UsbBlkDev_t *)hDev;

    if (BlkDev->Magic != USB_BLK_DEV_MAGIC)
    {
        hal_log_err("ERR: __DiskWrite: BlkDev Magic(%x) is invalid", BlkDev->Magic);
        return 0;
    }

    /* 如果没有注册disk设备, 就不能够读数据 */
    if (!BlkDev->is_RegDisk)
    {
        hal_log_err("ERR: __DiskWrite: Not reged Disk, can not read");
        return 0;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: __DiskWrite: mscLun == NULL");
        return 0;
    }

    /* 如果介质不存在, 就不能够往设备写数据 */
    if (!mscLun->MediaPresent)
    {
        hal_log_err("ERR: __DiskWrite: media is not present, __DiskWrite failed");
        return 0;
    }

    if (mscLun->WriteProtect)
    {
        hal_log_err("ERR: __DiskWrite: device is protect, can't write");
        return 0;
    }

    if ((blk + n) > mscLun->disk_info.capacity)
    {
        hal_log_err("ERR: __DiskWrite: block(%x, %x) is adjacence max capacity(%x)", blk, n, mscLun->disk_info.capacity);
        return 0;
    }

    //set_usbh_disk_status(USB_STORAGE_DEVICE_STATUS_WRITE);
    /*
        if(mscLun->mscDev->SubClass == USBMSC_SUBCLASS_SCSI){
            if(mscLun->disk_info.capacity > 0xffffffff){
                cmd_version = 16;
            }else if(mscLun->disk_info.capacity > 0x1fffff){
                cmd_version = 10;
            }else{
                cmd_version = 6;
            }
        }else{
            cmd_version = 10;
        }
    */
    /* 目前所见的USB设备里面都使用的是10字节命名，而且协议规定的是10/12字节命令 */
    cmd_version = 10;
    hal_sem_wait(mscLun->Lock);

    if (cmd_version == 16)
    {
        ret = ScsiWrite(mscLun, 16, blk, n, (void *)pBuffer,
                        (n * (mscLun->disk_info.sector_size)));
    }
    else if (cmd_version == 10)
    {
        ret = ScsiWrite(mscLun, 10, blk, n, (void *)pBuffer,
                        (n * (mscLun->disk_info.sector_size)));
    }
    else
    {
        ret = ScsiWrite(mscLun, 6, blk, n, (void *)pBuffer,
                        (n * (mscLun->disk_info.sector_size)));
    }

    hal_sem_post(mscLun->Lock);
    //set_usbh_disk_status(USB_STORAGE_DEVICE_STATUS_IDLE);

    if (ret != 0)
    {
        hal_log_err("ERR: ScsiWrite%d failed. DevNo = %d, blk = %d, n = %d", cmd_version, BlkDev->DevNo, blk, n);
        return 0;
    }

    return n;
}

#if 1
/*
*******************************************************************************
*                     DiskRead
*
* Description:
*    设备读
*
* Parameters:
*    pBuffer    :  output. 装载读回来的数据
*    blk        :  input.  起始扇区
*    n          :  input.  扇区个数
*    hDev       :  input.  设备
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static uint32_t DiskRead(void *pBuffer, uint32_t blk, uint32_t n, void * hDev)
{
    __UsbBlkDev_t *BlkDev = NULL;
    __mscLun_t *mscLun = NULL;
    unsigned int cnt = 0;

    if (hDev == NULL)
    {
        hal_log_err("ERR: DiskRead: input error, hDev = %x", hDev);
        return 0;
    }

    //DMSG_MSC_TEST("DiskRead: Blk = %d, N = %d, LastBlk = %d", blk, n, (blk + n));
    BlkDev = (__UsbBlkDev_t *)hDev;

    if (BlkDev->Magic != USB_BLK_DEV_MAGIC)
    {
        hal_log_err("ERR: DiskRead: BlkDev Magic(%x) is invalid", BlkDev->Magic);
        return 0;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: DiskRead: mscLun == NULL");
        return 0;
    }

    if ((blk + n) > mscLun->disk_info.capacity)
    {
        hal_log_err("ERR: DiskRead: block(%x, %x) is adjacence max capacity(%x)", blk, n, mscLun->disk_info.capacity);
        return 0;
    }

    /* 1、lba0 不预读
       2、本次读写长度超过了最大容量，不预读
    */
    if ((blk != 0)
        && ((blk + (USBH_TEMP_BUFFER_MAX_LEN / mscLun->disk_info.sector_size)) < mscLun->disk_info.capacity))
    {
        cnt = usbh_msc_special_read((void *)pBuffer,
                                    blk,
                                    n,
                                    hDev,
                                    BlkDev->DevNo,
                                    mscLun->disk_info.sector_size,
                                    (void *)__DiskRead);
    }
    else
    {
        hal_log_info("DiskRead: block(%x, %x) is adjacence max capacity(%x), can't use special write",
                  blk, n, mscLun->disk_info.capacity);
        cnt = __DiskRead(pBuffer, blk, n, hDev);
    }

    if (cnt != n)
    {
        hal_log_err("ERR: DiskRead failed, want(%d) != real(%d)", n, cnt);
        return 0;
    }

    //DMSG_MSC_TEST("read end");
    return n;
}

/*
*******************************************************************************
*                     DiskWrite
*
* Description:
*    设备写
*
* Parameters:
*    pBuffer    :  input. 要写的数据
*    blk        :  input. 起始扇区
*    n          :  input. 扇区个数
*    hDev       :  input. 设备
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static uint32_t DiskWrite(const void *pBuffer, uint32_t blk, uint32_t n, void * hDev)
{
    __UsbBlkDev_t *BlkDev = NULL;
    __mscLun_t *mscLun = NULL;
    unsigned int cnt = 0;

    if (hDev == NULL)
    {
        hal_log_err("ERR: DiskWrite: input error, hDev = %x", hDev);
        return 0;
    }

    //DMSG_MSC_TEST("DiskWrite: Blk = %d, N = %d, LastBlk = %d", blk, n, (blk + n));
    BlkDev = (__UsbBlkDev_t *)hDev;

    if (BlkDev->Magic != USB_BLK_DEV_MAGIC)
    {
        hal_log_err("ERR: DiskWrite: BlkDev Magic(%x) is invalid", BlkDev->Magic);
        return 0;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: __DiskWrite: mscLun == NULL");
        return 0;
    }

    if ((blk + n) > mscLun->disk_info.capacity)
    {
        hal_log_err("ERR: DiskWrite: block(%x, %x) is adjacence max capacity(%x)", blk, n, mscLun->disk_info.capacity);
        return 0;
    }

    /* 1、lba0 不预读
       2、本次读写长度超过了最大容量，不预读
    */
    if ((blk != 0)
        && ((blk + (USBH_TEMP_BUFFER_MAX_LEN / mscLun->disk_info.sector_size)) < mscLun->disk_info.capacity))
    {
        cnt = usbh_msc_special_write((void *)pBuffer,
                                     blk,
                                     n,
                                     hDev,
                                     BlkDev->DevNo,
                                     mscLun->disk_info.sector_size,
                                     (void *)__DiskWrite);
    }
    else
    {
        hal_log_info("DiskWrite: block(%x, %x) is adjacence max capacity(%x), can't use special write",
                  blk, n, mscLun->disk_info.capacity);
        set_usbh_temp_buff_invalid_by_dev(BlkDev->DevNo);
        cnt = __DiskWrite(pBuffer, blk, n, hDev);
    }

    if (cnt != n)
    {
        hal_log_err("ERR: DiskWrite failed, want(%d) != real(%d)", n, cnt);
        return 0;
    }

    //DMSG_MSC_TEST("write end");
    return n;
}

#else

static unsigned int DiskRead(void *pBuffer, unsigned int blk, unsigned int n, void * hDev)
{
    return __DiskRead(pBuffer, blk, n, hDev);
}

static unsigned int DiskWrite(const void *pBuffer, unsigned int blk, unsigned int n, void * hDev)
{
    return __DiskWrite(pBuffer, blk, n, hDev);
}

#endif

/*
*******************************************************************************
*                     DiskIoctl
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static int32_t DiskIoctl(void * hDev, uint32_t Cmd, long Aux, void *pBuffer)
{
    __UsbBlkDev_t *BlkDev = NULL;
    __mscLun_t *mscLun = NULL;
    unsigned int ret = 0;

    if (hDev == NULL)
    {
        hal_log_err("ERR: DiskIoctl: input error, hDev = %x", hDev);
        return EPDK_FAIL;
    }

    BlkDev = (__UsbBlkDev_t *)hDev;

    if (BlkDev->Magic != USB_BLK_DEV_MAGIC)
    {
        hal_log_err("ERR: DiskIoctl: BlkDev Magic(%x) is invalid", BlkDev->Magic);
        return EPDK_FAIL;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: DiskIoctl: mscLun == NULL");
        return EPDK_FAIL;
    }

    /* 由于块设备不支持光驱设备, 因此这里就只能做个临时版本 */
    if (mscLun->DeviceType == SCSI_DEVICE_CDROM)
    {
        ret = CDIOCtrl(BlkDev, Cmd, Aux, pBuffer);

        if (ret == EPDK_OK)
        {
            hal_log_err("[CD_ROM]: Cmd(%x) is USB CD_ROM command");
            return EPDK_OK;
        }
    }

    switch (Cmd)
    {
        case DEV_CMD_GET_INFO:
        {
            if (!pBuffer)
            {
                hal_log_err("ERR : usb storage disk ,pBuffer == NULL");
                return EPDK_FAIL;
            }

            ((__dev_blkinfo_t *)pBuffer)->hiddennum = 0;
            ((__dev_blkinfo_t *)pBuffer)->headnum   = 0;
            ((__dev_blkinfo_t *)pBuffer)->secnum    = 0;
            ((__dev_blkinfo_t *)pBuffer)->partsize  = mscLun->disk_info.capacity;
            ((__dev_blkinfo_t *)pBuffer)->secsize   = mscLun->disk_info.sector_size;
            hal_log_info("[usb storage]: DEV_CMD_GET_INFO, capacity = %dM, sector = %d",
                      ((mscLun->disk_info.capacity) >> 11), mscLun->disk_info.sector_size);
        }
        break;

        case DEV_CMD_GET_STATUS:
            return EPDK_OK;

        case DEV_IOC_USR_FLUSH_CACHE:
            return EPDK_OK;

        case DEV_CDROM_LAST_WRITTEN:
            return EPDK_FAIL;

        case DEV_CDROM_MULTISESSION:
            return EPDK_FAIL;

        default:
            hal_log_err("WARN : DiskIoctl ,cmd = %x ,not support now", Cmd);
            return EPDK_FAIL;
    }

    return EPDK_OK;
}

/*
*******************************************************************************
*                     UsbBlkDevAllocInit
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
#define  USB_STORAGE_DEV_NAME       "SCSI_DISK"
#define  USB_CDROM_DEV_NAME         "USB_CDROM"

__UsbBlkDev_t *UsbBlkDevAllocInit(__mscLun_t *mscLun)
{
    __UsbBlkDev_t *BlkDev = NULL;
    unsigned char temp_buff[32];
    unsigned int temp = 0;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: UsbBlkDevAllocInit: input error");
        return NULL;
    }

    //--<1>--create a block device
    BlkDev = (__UsbBlkDev_t *)hal_malloc(sizeof(__UsbBlkDev_t));

    if (BlkDev == NULL)
    {
        hal_log_err("ERR: UsbBlkDevAllocInit: USB_OS_MALLOC failed");
        return NULL;
    }

    memset(BlkDev, 0, sizeof(__UsbBlkDev_t));
    BlkDev->Lun = mscLun;
    //--<2>--create lock
    //--<3>--create DevNo
    BlkDev->DevNo = (mscLun->LunNo * 1) + (mscLun->mscDev->mscDevNo * 10);

    //--<4>--create sub device name
    if (mscLun->DeviceType == SCSI_DEVICE_CDROM)
    {
        memcpy((void *)BlkDev->DevName, USB_CDROM_DEV_NAME, strlen(USB_CDROM_DEV_NAME));
        strcat((char *)BlkDev->DevName, "_");
    }
    else
    {
        memcpy((void *)BlkDev->DevName, USB_STORAGE_DEV_NAME, strlen(USB_STORAGE_DEV_NAME));
        strcat((char *)BlkDev->DevName, "_");
    }

    /* usb controler number */
    temp = 0;
    memset(temp_buff, 0, 32);
    Usb_uint2str_dec(temp, (char *)temp_buff);
    strcat((char *)BlkDev->DevName, (const char *)temp_buff);
    /* mscDevNo */
    memset(temp_buff, 0, 32);
    Usb_uint2str_dec(mscLun->mscDev->mscDevNo, (char *)temp_buff);
    strcat((char *)BlkDev->DevName, (const char *)temp_buff);
    /* LunNo */
    memset(temp_buff, 0, 32);
    Usb_uint2str_dec(mscLun->LunNo, (char *)temp_buff);
    strcat((char *)BlkDev->DevName, (const char *)temp_buff);
    /* init device operation function */
    BlkDev->DiskOp.Open  = DiskOpen;
    BlkDev->DiskOp.Close = DiskClose;
    BlkDev->DiskOp.Read  = DiskRead;
    BlkDev->DiskOp.Write = DiskWrite;
    BlkDev->DiskOp.Ioctl = DiskIoctl;
    return BlkDev;
}

/*
*******************************************************************************
*                     UsbBlkDevFree
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
int UsbBlkDevFree(__UsbBlkDev_t *BlkDev)
{
    if (BlkDev == NULL)
    {
        hal_log_err("ERR: UsbBlkDevFree: input error");
        return -1;
    }

    BlkDev->DiskOp.Open  = NULL;
    BlkDev->DiskOp.Close = NULL;
    BlkDev->DiskOp.Read  = NULL;
    BlkDev->DiskOp.Write = NULL;
    BlkDev->DiskOp.Ioctl = NULL;
    hal_free(BlkDev);
    return 0;
}

/*
*******************************************************************************
*                     PrintDevStatus
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*
*
*******************************************************************************
*/
static void PrintDevStatus(unsigned char *FunName, int status)
{
    hal_log_info("FunName: %s,", FunName);

    switch (status)
    {
        case  USB_STATUS_SUCCESS:
            hal_log_info("USB_STATUS_SUCCESS");
            break;

        case  USB_STATUS_DEVICE_DISCONNECTED:
            hal_log_info("USB_STATUS_DEVICE_DISCONNECTED");
            break;

        case USB_STATUS_IO_TIMEOUT:
            hal_log_info("USB_STATUS_IO_TIMEOUT");
            break;

        case USB_STATUS_IO_DEVICE_ERROR:
            hal_log_info("USB_STATUS_IO_DEVICE_ERROR");
            break;

        case USB_STATUS_DEVICE_BUSY:
            hal_log_info("USB_STATUS_DEVICE_BUSY");
            break;

        case USB_STATUS_BUFFER_TOO_SMALL:
            hal_log_info("USB_STATUS_BUFFER_TOO_SMALL");
            break;

        case USB_STATUS_INVALID_COMMAND:
            hal_log_info("USB_STATUS_INVALID_COMMAND");
            break;

        case USB_STATUS_INVALID_FIELD_IN_COMMAND:
            hal_log_info("USB_STATUS_INVALID_FIELD_IN_COMMAND");
            break;

        case USB_STATUS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE:
            hal_log_info("USB_STATUS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE");
            break;

        case USB_STATUS_MEDIA_NOT_PRESENT:
            hal_log_info("USB_STATUS_MEDIA_NOT_PRESENT");
            break;

        case USB_STATUS_NOT_READY_TO_READY_TRANSITION:
            hal_log_info("USB_STATUS_NOT_READY_TO_READY_TRANSITION");
            break;

        case USB_STATUS_UNRECOGNIZED_MEDIA:
            hal_log_info("USB_STATUS_UNRECOGNIZED_MEDIA");
            break;

        case USB_STATUS_UNKOWN_ERROR:
            hal_log_info("USB_STATUS_UNKOWN_ERROR");
            break;

        default:
            hal_log_info("unkonw status %d", status);
            break;
    }

    return ;
}

static void Pr__s32DiskInfo(__UsbBlkDev_t *BlkDev)
{
    __mscLun_t *mscLun = NULL;

    if (BlkDev == NULL)
    {
        hal_log_err("ERR: Pr__s32DiskInfo: input error, BlkDev = %x", BlkDev);
        return ;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: UnitReady: mscLun == NULL");
        return ;
    }

    hal_log_info("-----------------Disk Information-----------------");
    hal_log_info("WriteProtect = %d", mscLun->WriteProtect);
    hal_log_info("MediaPresent = %d", mscLun->MediaPresent);
    hal_log_info("WCE          = %d", mscLun->WCE);
    hal_log_info("RCD          = %d", mscLun->RCD);
    hal_log_info("capacity     = %dM, sector number = %d", (mscLun->disk_info.capacity * 512) / (1024 * 1024), mscLun->disk_info.capacity);
    hal_log_info("sector_size  = %d", mscLun->disk_info.sector_size);
    hal_log_info("DevNo        = %d", BlkDev->DevNo);
    hal_log_info("ClassName    = %s", BlkDev->ClassName);
    hal_log_info("DevName      = %s", BlkDev->DevName);
    hal_log_info("--------------------------------------------------");
    return ;
}


/*
*******************************************************************************
*                     WaitForDeviceReady
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*
*
*******************************************************************************
*/
static void WaitForDeviceReady(__UsbBlkDev_t *BlkDev)
{
    __mscLun_t *mscLun = NULL;
    unsigned int Repeat = 10;
    int ret = USB_STATUS_SUCCESS;

    if (BlkDev == NULL)
    {
        hal_log_err("ERR: UnitReady: input error");
        return ;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: UnitReady: mscLun == NULL");
        return ;
    }

    hal_sem_wait(mscLun->Lock);
    /* Unit Ready? */
    ret = ScsiTestUnitReady(mscLun);

    if (ret == USB_STATUS_SUCCESS)
    {
        goto end;
    }
    else if (mscLun->DeviceType == SCSI_DEVICE_CDROM)
    {
        PrintDevStatus("ScsiTestUnitReady", ret);
        ScsiStartStopUnit(mscLun, 0, 1);
    }

    /* wait for unit ready */
    do
    {
        ret = ScsiTestUnitReady(mscLun);

        if (ret == USB_STATUS_INVALID_COMMAND)
        {
            hal_log_err("ERR: Device Not Support ScsiTestUnitReady command");
            PrintDevStatus("ScsiTestUnitReady", ret);
            break;
        }

        /* 判断media的状态 */
        if (ret != USB_STATUS_SUCCESS)
        {
            mscLun->MediaPresent = 0;
        }
        else if ((ret == USB_STATUS_SUCCESS && !(mscLun->MediaPresent)))
        {
            hal_log_info("Media not Present, but ScsiTestUnitReady command is successful,"
                      " Repeat = %d", Repeat);
            mscLun->MediaPresent = 1;
        }

        --Repeat;

        if (USB_STATUS_SUCCESS != ret && Repeat != 0)
        {
            hal_msleep(1000);
        }
    } while (Repeat && !(mscLun->MediaPresent));

end:
    hal_sem_post(mscLun->Lock);
    return ;
}

/*
*******************************************************************************
*                     ReadCapacity
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*
*
*******************************************************************************
*/
static void ReadCapacity(__UsbBlkDev_t *BlkDev)
{
    __mscLun_t *mscLun = NULL;
    int ret = 0;

    if (BlkDev == NULL)
    {
        hal_log_err("ERR: UnitReady: input error");
        return ;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: UnitReady: mscLun == NULL");
        return ;
    }

    if (mscLun->MediaPresent)
    {
        hal_sem_wait(mscLun->Lock);
        ret = ScsiReadCapacity(mscLun);

        if (ret != USB_STATUS_SUCCESS)
        {
            hal_log_err("ERR: ScsiReadCapacity failed");
            PrintDevStatus("ScsiReadCapacity", ret);
        }

        hal_sem_post(mscLun->Lock);
    }
    else
    {
        hal_log_err("ERR: media is not present, ReadCapacity failed");
    }

    return ;
}

/*
*******************************************************************************
*                     ReadProtectFlag
*
* Description:
*    获得设备写保护标志位
*
* Parameters:
*
*
* Return value:
*
*
* note:
*
*
*******************************************************************************
*/
static void ReadProtectFlag(__UsbBlkDev_t *BlkDev)
{
    __mscLun_t *mscLun = NULL;
    __BlockDevSpecPara_t *DevSpecPara = NULL;
    unsigned int cmd_version = 6;   /* 默认使用mode sense 6 */
    int ret = 0;
    unsigned int ActLen = 0;
    unsigned char  buffer[SCSI_MODE_SENSE_MAX_DATA_LEN];

    if (BlkDev == NULL)
    {
        hal_log_err("ERR: UnitReady: input error");
        return ;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: UnitReady: mscLun == NULL");
        return ;
    }

    if ((mscLun->mscDev->SubClass != USBMSC_SUBCLASS_SCSI) || (mscLun->DeviceType == SCSI_DEVICE_CDROM))
    {
        cmd_version = 10;
    }

    memset(buffer, 0, SCSI_MODE_SENSE_MAX_DATA_LEN);
    hal_sem_wait(mscLun->Lock);

    /* send mode sense command */
    if (cmd_version == 6)
    {
        ret = ScsiModeSense6(mscLun,
                             MODE_PAGE_ALL_PAGES,
                             ((mscLun->DeviceType == SCSI_DEVICE_CDROM) ? 1 : 0),
                             (void *)buffer,
                             SCSI_MODE_SENSE_MAX_DATA_LEN,
                             &ActLen);

        if (ret == USB_STATUS_INVALID_COMMAND)
        {
            cmd_version = 10;
        }
        else if (ret != USB_STATUS_SUCCESS)
        {
            hal_log_err("ERR: ScsiModeSense6 failed");
            PrintDevStatus("ScsiModeSense6", ret);
            cmd_version = 0;
        }
    }

    if (cmd_version == 10)
    {
        ret = ScsiModeSense10(mscLun,
                              MODE_PAGE_ALL_PAGES,
                              ((mscLun->DeviceType == SCSI_DEVICE_CDROM) ? 1 : 0),
                              (void *)buffer,
                              SCSI_MODE_SENSE_MAX_DATA_LEN,
                              &ActLen);

        if (ret != USB_STATUS_SUCCESS)
        {
            hal_log_err("ERR: ScsiModeSense10 failed");
            PrintDevStatus("ScsiModeSense10", ret);
            cmd_version = 0;
        }
    }

    /* parse mode sense data */
    if (ActLen)
    {
        if (cmd_version == 6)
        {
            DevSpecPara = (__BlockDevSpecPara_t *) & (buffer[2]);
            mscLun->WriteProtect = DevSpecPara->WP;
        }
        else if (cmd_version == 10)
        {
            DevSpecPara = (__BlockDevSpecPara_t *) & (buffer[3]);
            mscLun->WriteProtect = DevSpecPara->WP;
        }
        else
        {
            mscLun->WriteProtect = 0;
        }
    }
    else   /* if deivce not have 0x3f page, then no mode sense data */
    {
        hal_log_err("ReadProtectFlag: no mode sense data");
        mscLun->WriteProtect = 0;
    }

    hal_sem_post(mscLun->Lock);
    return ;
}

/*
*******************************************************************************
*                     ReadCacheType
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*
*
*******************************************************************************
*/
static void ReadCacheType(__UsbBlkDev_t *BlkDev)
{
    __mscLun_t *mscLun = NULL;
    unsigned int cmd_version = 6;   /* 默认使用mode sense 6 */
    int ret = 0;
    unsigned char  buffer[SCSI_MODE_SENSE_MAX_DATA_LEN];
    unsigned int ActLen = 0;
    unsigned int CachepageValid = 0;
    unsigned int CachepageAddr = 0;

    if (BlkDev == NULL)
    {
        hal_log_err("ERR: UnitReady: input error");
        return ;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: UnitReady: mscLun == NULL");
        return ;
    }

    if ((mscLun->mscDev->SubClass != USBMSC_SUBCLASS_SCSI) || (mscLun->DeviceType == SCSI_DEVICE_CDROM))
    {
        cmd_version = 10;
    }

    memset(buffer, 0, SCSI_MODE_SENSE_MAX_DATA_LEN);
    hal_sem_wait(mscLun->Lock);

    /* send mode sense command */
    if (cmd_version == 6)
    {
        ret = ScsiModeSense6(mscLun,
                             MODE_PAGE_WCACHING_PAGE,
                             ((mscLun->DeviceType == SCSI_DEVICE_CDROM) ? 1 : 0),
                             (void *)buffer,
                             SCSI_MODE_SENSE_MAX_DATA_LEN,
                             &ActLen);

        if (ret == USB_STATUS_INVALID_COMMAND)
        {
            cmd_version = 10;
        }
        else if (ret != USB_STATUS_SUCCESS)
        {
            hal_log_err("ERR: ScsiModeSense6 failed");
            PrintDevStatus("ScsiModeSense6", ret);
            cmd_version = 0;
        }
    }

    if (cmd_version == 10)
    {
        ret = ScsiModeSense10(mscLun,
                              MODE_PAGE_WCACHING_PAGE,
                              ((mscLun->DeviceType == SCSI_DEVICE_CDROM) ? 1 : 0),
                              (void *)buffer,
                              SCSI_MODE_SENSE_MAX_DATA_LEN,
                              &ActLen);

        if (ret != USB_STATUS_SUCCESS)
        {
            hal_log_err("ERR: ScsiModeSense10 failed");
            PrintDevStatus("ScsiModeSense10", ret);
            cmd_version = 0;
        }
    }

    /* parse mode sense data */
    if (ActLen)
    {
        if (cmd_version == 6)
        {
            CachepageAddr  = 4;
            CachepageValid = 1;
        }
        else if (cmd_version == 10)
        {
            CachepageAddr  = 8;
            CachepageValid = 1;
        }
        else
        {
            CachepageAddr  = 0;
            CachepageValid = 0;
        }

        if (CachepageValid)
        {
            mscLun->WCE = (buffer[CachepageAddr + 2] & 0x04) ? 1 : 0;   /* bit2 */
            mscLun->RCD = (buffer[CachepageAddr + 2] & 0x01) ? 1 : 0;   /* bit0 */
        }
        else
        {
            mscLun->WCE = 0;
            mscLun->RCD = 0;
        }
    }
    else   /* if deivce not have cahe page, then no mode sense data */
    {
        hal_log_err("ReadCacheType: no mode sense data");
        mscLun->WCE = 0;
        mscLun->RCD = 0;
    }

    hal_sem_post(mscLun->Lock);
    return ;
}


/*
*******************************************************************************
*                     GetDiskInfo
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
void GetDiskInfo(__UsbBlkDev_t *BlkDev)
{
    __mscLun_t *mscLun = NULL;

    if (BlkDev == NULL)
    {
        hal_log_err("ERR: GetDiskInfo: input error");
        return ;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: GetDiskInfo: mscLun == NULL");
        return ;
    }

    mscLun->MediaPresent          = 1;
    mscLun->WriteProtect          = 0;
    mscLun->WCE                   = 0;
    mscLun->RCD                   = 0;
    mscLun->disk_info.capacity    = 0;
    mscLun->disk_info.sector_size = 0;
    /* check unit is ready? */
    WaitForDeviceReady(BlkDev);

    if (!mscLun->MediaPresent)
    {
        hal_log_err("ERR: can not get disk info, for unit is not ready");
        mscLun->MediaPresent          = 0;
        mscLun->WriteProtect          = 0;
        mscLun->WCE                   = 0;
        mscLun->RCD                   = 0;
        mscLun->disk_info.capacity    = 0;
        mscLun->disk_info.sector_size = 0;
        return;
    }

    /* read capacity */
    ReadCapacity(BlkDev);
    /* Lun是否写保护? */
    ReadProtectFlag(BlkDev);
    /* Lun是否带cache? */
    ReadCacheType(BlkDev);
    Pr__s32DiskInfo(BlkDev);
//  printf("%s %d %s\n", __FILE__, __LINE__, __func__);
    return ;
}

/*
*******************************************************************************
*                     WaitForDeviceReady
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*
*
*******************************************************************************
*/
void ShutDown(__UsbBlkDev_t *BlkDev)
{
    __mscLun_t *mscLun = NULL;

    if (BlkDev == NULL)
    {
        hal_log_err("ERR: GetDiskInfo: input error");
        return ;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: GetDiskInfo: mscLun == NULL");
        return ;
    }

    /* sync cache */
    if (mscLun->WCE)
    {
        ScsiSynchronizeCache(mscLun);
    }

    return ;
}

/*
*******************************************************************************
*                     UsbBlkDevReg
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
int UsbBlkDevReg(__UsbBlkDev_t *BlkDev, unsigned char *ClassName, unsigned int RegDisk)
{
extern unsigned int hub_GetHubSeries(struct usb_host_virt_dev *udev);
extern unsigned int hub_GetHubNo(struct usb_host_virt_dev *udev);

    if (BlkDev == NULL || ClassName == NULL)
    {
        hal_log_err("ERR: UsbBlkDevInit: input error");
        return -1;
    }

    //更新标志位
    BlkDev->Magic = USB_BLK_DEV_MAGIC;

    if (RegDisk)
    {
        BlkDev->is_RegDisk = 1;
    }

    strncpy((char *)BlkDev->ClassName, (const char *)ClassName, strlen((const char *)ClassName));
    /* save deivce info */
    memset(&BlkDev->device_info, 0, sizeof(usbh_disk_device_info_t));
    strcpy((char *)BlkDev->device_info.Classname, (char *)BlkDev->ClassName);
    strcpy((char *)BlkDev->device_info.DeviceName, (char *)BlkDev->DevName);
    strcpy((char *)BlkDev->device_info.DeivceInfo.Vender, (char *)BlkDev->Lun->Vendor);
    strcpy((char *)BlkDev->device_info.DeivceInfo.Product, (char *)BlkDev->Lun->Product);
    strcpy((char *)BlkDev->device_info.DeivceInfo.Serial, (char *)BlkDev->Lun->Revision);

    BlkDev->device_info.DeivceInfo.HubPortNo = (hub_GetHubNo(BlkDev->Lun->mscDev->pusb_dev) & 0x0f)
            | ((hub_GetHubSeries(BlkDev->Lun->mscDev->pusb_dev) & 0x0f) << 8);

    if ((BlkDev->Lun->DeviceType == SCSI_DEVICE_DIRECT_ACCESS) && (BlkDev->Lun->RemoveAble == 0))
    {
        BlkDev->device_info.DeivceInfo.DeviceType = USB_STORAGE_DEVICE_TYPE_HDD;
    }
    else if ((BlkDev->Lun->DeviceType == SCSI_DEVICE_DIRECT_ACCESS) && BlkDev->Lun->RemoveAble)
    {
        BlkDev->device_info.DeivceInfo.DeviceType = USB_STORAGE_DEVICE_TYPE_UDISK;
    }
    else if (BlkDev->Lun->DeviceType == SCSI_DEVICE_CDROM)
    {
        BlkDev->device_info.DeivceInfo.DeviceType = USB_STORAGE_DEVICE_TYPE_CDROM;
    }
    else
    {
        BlkDev->device_info.DeivceInfo.DeviceType = USB_STORAGE_DEVICE_TYPE_UNKOWN;
    }

    printf("Classname  = %s\n", BlkDev->device_info.Classname);
    printf("DevName  = %s\n", BlkDev->DevName);
    printf("DeviceName = %s\n", BlkDev->device_info.DeviceName);
    printf("Vender     = %s\n", BlkDev->device_info.DeivceInfo.Vender);
    printf("Product    = %s\n", BlkDev->device_info.DeivceInfo.Product);
    printf("Serial     = %s\n", BlkDev->device_info.DeivceInfo.Serial);
    printf("HubPortNo  = %d\n", BlkDev->device_info.DeivceInfo.HubPortNo);
    printf("DeviceType = %d\n", BlkDev->device_info.DeivceInfo.DeviceType);
    usbh_disk_SaveDeviceInfo(&BlkDev->device_info);
    /* reg disk */
    BlkDev->DevRegHdle = esDEV_DevReg((const char *)ClassName, (const char *)BlkDev->DevName, &(BlkDev->DiskOp), (void *)BlkDev);

    if (BlkDev->DevRegHdle == NULL)
    {
        hal_log_err("ERR: Block device register failed.");
        BlkDev->Magic = 0;
        BlkDev->is_RegDisk = 0;
        return USB_ERR_UNKOWN_ERROR;
    }

    printf("..............................................................................\n");
    printf("[USB Disk]: Register new device, class = [%s], dev = [%s]\n", BlkDev->ClassName, BlkDev->DevName);
    printf("..............................................................................\n");
    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     UsbBlkDevUnReg
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
int UsbBlkDevUnReg(__UsbBlkDev_t *BlkDev)
{
    if (BlkDev == NULL)
    {
        hal_log_err("ERR: UsbBlkDevUnReg: input error");
        return -1;
        //return USB_ERR_BAD_ARGUMENTS;
    }

    if (BlkDev->DevRegHdle)
    {
        hal_log_info("..............................................................................");
        hal_log_info("[USB Disk]: UnRegister old device, class = [%s], dev = [%s]", BlkDev->ClassName, BlkDev->DevName);
        hal_log_info("..............................................................................");
        usbh_disk_FreeDeviceInfo(&BlkDev->device_info);
        esDEV_DevUnreg(BlkDev->DevRegHdle);
        BlkDev->DevRegHdle = NULL;
        BlkDev->is_RegDisk = 0;
        memset(BlkDev->ClassName, 0, USB_BULK_DISK_MAX_NAME_LEN);
    }
    else
    {
        hal_log_err("ERR: UsbBlkDevUnReg: DevRegHdle = NULL");
        //return USB_ERR_BAD_ARGUMENTS;
        return -1;
    }

    set_usbh_temp_buff_invalid_by_dev(BlkDev->DevNo);
    BlkDev->Magic = 0;
    return 0;
    //return USB_ERR_SUCCESS;

}


