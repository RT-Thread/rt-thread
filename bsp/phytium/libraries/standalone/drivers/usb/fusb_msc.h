/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fusb_msc.h
 * Date: 2022-02-11 13:33:09
 * LastEditTime: 2022-02-17 17:50:46
 * Description:  This files is for definition of USB mass storage function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FUSB_MSC_H
#define  FUSB_MSC_H

/***************************** Include Files *********************************/

#include "fusb.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
/* Possible values for quirks field. */
enum
{
    /* Don't check for LUNs (force assumption that there's only one LUN). */
    FUSB_MSC_QUIRK_NO_LUNS  = 1 << 0,
    /* Never do a BULK_ONLY reset, just continue. This means that the device
       cannot recover from phase errors and won't detach automatically for
       unrecoverable errors. Do not use unless you have to. */
    FUSB_MSC_QUIRK_NO_RESET = 1 << 1,
};

/* Possible values for ready field. */
enum
{
    FUSB_MSC_DETACHED = -1, /* Disk detached or out to lunch. */
    FUSB_MSC_NOT_READY = 0, /* Disk not ready yet -- empty card reader */
    FUSB_MSC_READY = 1,     /* Disk ready to communicate. */
};

enum
{
    FUSB_MSC_SUBCLASS_ATAPI_8020 = 0x2,
    FUSB_MSC_SUBCLASS_ATAPI_8070 = 0x5,
    FUSB_MSC_SUBCLASS_SCSI = 0x6
};

/* Protocols of MSC */
enum
{
    FUSB_MSC_PROTOCOL_BULK_ONLY = 0x50 /* Usb bulk-only transfer protocol */
};

typedef enum
{
    FUSB_DIR_DATA_IN = 0x80, /* data from the device to the host */
    FUSB_DIR_DATA_OUT = 0 /* data from the host to the device */
} FUsbMassStorageDirection;

/**************************** Type Definitions *******************************/
typedef struct
{
    unsigned int blocksize;
    unsigned int numblocks;
    FUsbEndpoint *bulk_in;
    FUsbEndpoint *bulk_out;
    u8 quirks       : 7;
    u8 usbdisk_created  : 1;
    s8 ready;
    u8 lun;
    u8 num_luns;
    void *data; /* For use by consumers of libpayload. */
} FUsbMassStorage;

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define MSC_INST(dev) ((FUsbMassStorage*)(dev)->data)

/**
 * @name: FUsbMscGetCapcityMB
 * @msg: 获取USB大容量存储设备的容量，单位MB
 * @return {fsize_t} 容量，MB
 * @param {FUsbDev} *dev, USB大容量存储设备实例
 */
static inline u32 FUsbMscGetCapcityMB(FUsbDev *dev)
{
    FASSERT(dev);
    return (u32)(MSC_INST(dev)->numblocks > 1000000
                 ? (MSC_INST(dev)->numblocks / 1024) * MSC_INST(dev)->blocksize / 1024
                 : MSC_INST(dev)->numblocks * MSC_INST(dev)->blocksize / 1024 / 1024);
}

/**
 * @name: FUsbMscGetBlkSize
 * @msg: 获取USB大容量存储设备的块大小
 * @return {*} 块大小，字节数
 * @param {FUsbDev} *dev, USB大容量存储设备实例
 */
static inline u32 FUsbMscGetBlkSize(FUsbDev *dev)
{
    FASSERT(dev);
    return (u32)MSC_INST(dev)->blocksize;
}

/**
 * @name: FUsbMscGetBlkNum
 * @msg: 获取USB大容量存储设备块数目
 * @return {*} 块数目
 * @param {FUsbDev} *dev, USB大容量存储设备实例
 */
static inline u32 FUsbMscGetBlkNum(FUsbDev *dev)
{
    FASSERT(dev);
    return (u32)MSC_INST(dev)->numblocks;
}

/************************** Function Prototypes ******************************/
/* 读写USB大容量存储设备，以512字节为一块 */
int FUsbMscRwBlk512(FUsbDev *dev, int start, int n, FUsbMassStorageDirection dir, u8 *buf);

/* USB大容量存储设备的初始化函数，由应用程序注册到FUSB框架中 */
void FUsbMassStorageInit(FUsbDev *dev);

/**
 * To be implemented by application. It's called by the USB stack
 * when a new USB storage device is found, so the client has the chance
 * to know about it.
 *
 * @param dev descriptor for the USB storage device
 */
void __attribute__((weak)) FUsbDiskCreate(FUsbDev *dev);

/**
 * To be implemented by application. It's called by the USB stack
 * when it finds out that a USB storage device is removed.
 *
 * @param dev descriptor for the USB storage device
 */
void __attribute__((weak)) FUsbDiskRemove(FUsbDev *dev);

#ifdef __cplusplus
}
#endif


#endif
