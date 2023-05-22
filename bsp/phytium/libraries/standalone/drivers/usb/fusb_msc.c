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
 * FilePath: fusb_msc.c
 * Date: 2022-02-11 13:33:09
 * LastEditTime: 2022-02-17 17:49:43
 * Description:  This files is for implementation of USB mass storage function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include <string.h>
#include "fswap.h"
#include "fsleep.h"
#include "fassert.h"
#include "fgeneric_timer.h"
#include "fdebug.h"

#include "fusb.h"
#include "fusb_msc.h"


#define FUSB_DEBUG_TAG "FUSB_MSC"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

static inline tick_t FUsbMscGetTick(void)
{
    return GenericTimerRead();
}

static inline tick_t FUsbMscStartTick(void)
{
    GenericTimerStart();
    return FUsbMscGetTick();
}

static inline void FUsbMscStopTick(void)
{
    GenericTimerStop();
}

static inline boolean FUsbMscTimeout(tick_t start_tick, tick_t timeout_tick)
{
    return (FUsbMscGetTick() - start_tick) > timeout_tick;
}

static void FUsbMassStorageForceInit(FUsbDev *dev, u32 quirks);
static int FUsbMscRwBlks(FUsbDev *dev, int start, int n, FUsbMassStorageDirection dir, u8 *buf);

static const char *FUsbMscSubClassString[7] =
{
    "(none)",
    "RBC",
    "MMC-2",
    "QIC-157",
    "UFI",
    "SFF-8070i",
    "SCSI transparent"
};

static const char *FUsbMscProtocolStrings[0x51] =
{
    "Control/Bulk/Interrupt protocol (with command completion interrupt)",
    "Control/Bulk/Interrupt protocol (with no command completion interrupt)",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "Bulk-Only Transport"
};

/**
 * @name: FUsbMscCreateDisk
 * @msg: 调用应用程序实现的钩子函数，创建USB Disk
 * @return {*}
 * @param {FUsbDev} *dev, USB大容量存储设备实例
 */
static void FUsbMscCreateDisk(FUsbDev *dev)
{
    FASSERT(dev);

    if (FUsbDiskCreate)
    {
        FUsbDiskCreate(dev);
        MSC_INST(dev)->usbdisk_created = 1;
    }

    return;
}

/**
 * @name: FUsbMscRemoveDisk
 * @msg: 调用应用程序实现的钩子函数，移除USB Disk
 * @return {*}
 * @param {FUsbDev} *dev, USB大容量存储设备实例
 */
static void FUsbMscRemoveDisk(FUsbDev *dev)
{
    FASSERT(dev);

    if (MSC_INST(dev)->usbdisk_created && FUsbDiskRemove)
    {
        FUsbDiskRemove(dev);
    }

    return;
}

/**
 * @name: FUsbMscDestory
 * @msg: 移除USB大容量存储设备实例
 * @return {*}
 * @param {FUsbDev} *dev, USB大容量存储设备实例
 */
static void FUsbMscDestory(FUsbDev *dev)
{
    FASSERT(dev && dev->controller);
    FUsb *instance = dev->controller->usb;
    FASSERT(instance);

    if (NULL != dev->data)
    {
        FUsbMscRemoveDisk(dev);
        FUSB_FREE(instance, dev->data);
    }

    dev->data = NULL;
    return;
}

const int DEV_RESET = 0xff;
const int GET_MAX_LUN = 0xfe;
/* Many USB3 devices do not work with large transfer requests.
 * Limit the request size to 64KB chunks to ensure maximum compatibility. */
const int MAX_CHUNK_BYTES = 1024 * 64;

const unsigned int cbw_signature = 0x43425355; /* according to USB mass-bulk spec. helps to identify data packets */
const unsigned int csw_signature = 0x53425355;

/* following data structure following name convention in USB mass-bulk spec., which may not compiliance to other code */

/* A packet containing a command block and associated information. */
typedef struct
{
    unsigned int dCBWSignature;
    unsigned int dCBWTag;
    unsigned int dCBWDataTransferLength;
    unsigned char bmCBWFlags;
    unsigned long bCBWLUN : 4; /* device Logical Unit Number (LUN) */
    unsigned long : 4;
    unsigned long bCBWCBLength : 5;
    unsigned long : 3;
    unsigned char CBWCB[31 - 15];
} __attribute__((packed)) FUsbMscCbw; /* Command Block Wrapper (CBW) */

/* A packet containing the status of a command block */
typedef struct
{
    unsigned int dCSWSignature;
    unsigned int dCSWTag;
    unsigned int dCSWDataResidue;
    unsigned char bCSWStatus;
} __attribute__((packed)) FUsbMscCsw;

enum
{
    /*
     * MSC commands can be
     *   successful,
     *   fail with proper response or
     *   fail totally, which results in detaching of the USB device
     *   and immediate cleanup of the FUsbDev structure.
     * In the latter case the caller has to make sure, that he won't
     * use the device any more.
     */
    MSC_COMMAND_OK = 0,
    MSC_COMMAND_FAIL,
    MSC_COMMAND_DETACHED
};

static int FUsbMscRequestSense(FUsbDev *dev);
static int FUsbMscRequestNoMedia(FUsbDev *dev);
static void FUsbMscPoll(FUsbDev *dev);

static int FUsbClearStall(FUsbEndpoint *ep)
{
    FASSERT(ep);
    int ret = FUsbClearFeature(ep->dev, ep->endpoint, FUSB_ENDPOINT_HALT,
                               FUsbGenerateReqType(FUSB_REQ_HOST_TO_DEVICE, FUSB_REQ_TYPE_STANDARD, FUSB_REQ_RECP_EP));

    ep->toggle = 0;

    return ret;
}

static int FUsbMscResetTransport(FUsbDev *dev)
{
    FUsbDevReq dr;
    memset(&dr, 0, sizeof(dr));
    dr.bmRequestType = 0;
    dr.data_dir = FUSB_REQ_HOST_TO_DEVICE;
    dr.req_type = FUSB_REQ_TYPE_CLASS;
    dr.req_recp = FUSB_REQ_RECP_IF;
    dr.bRequest = DEV_RESET;
    dr.wValue = 0;
    dr.wIndex = 0;
    dr.wLength = 0;

    if (MSC_INST(dev)->quirks & FUSB_MSC_QUIRK_NO_RESET)
    {
        return MSC_COMMAND_FAIL;
    }

    /* if any of these fails, detach device, as we are lost */
    if (dev->controller->control(dev, FUSB_OUT, sizeof(dr), &dr, 0, 0) < 0 ||
        FUsbClearStall(MSC_INST(dev)->bulk_in) ||
        FUsbClearStall(MSC_INST(dev)->bulk_out))
    {
        FUSB_INFO("Detaching unresponsive device. ");
        FUsbDetachDev(dev->controller, dev->address);
        return MSC_COMMAND_DETACHED;
    }
    /* return fail as we are only called in case of failure */
    return MSC_COMMAND_FAIL;
}

/* device may stall this command, so beware! */
static void FUsbMscInitLuns(FUsbDev *dev)
{
    FUsbMassStorage *msc = MSC_INST(dev);
    FUsbDevReq dr;
    dr.bmRequestType = 0;
    dr.data_dir = FUSB_REQ_DEVICE_TO_HOST;
    dr.req_type = FUSB_REQ_TYPE_CLASS;
    dr.req_recp = FUSB_REQ_RECP_IF;
    dr.bRequest = GET_MAX_LUN;
    dr.wValue = 0;
    dr.wIndex = 0;
    dr.wLength = 1;

    /* send class-spefic request Get Max Lun */
    if ((MSC_INST(dev)->quirks & FUSB_MSC_QUIRK_NO_LUNS) ||
        (dev->controller->control(dev, FUSB_IN, sizeof(dr), &dr,
                                  sizeof(msc->num_luns), &msc->num_luns) < FUSB_CC_ZERO_BYTES))
    {
        msc->num_luns = 0; /* assume only 1 lun if req fails */
    }

    msc->num_luns++;       /* Get Max LUN returns number of last LUN */
    msc->lun = 0;

    return;
}

unsigned int tag;
static void FUsbMscWrapCbw(FUsbMscCbw *cbw, int datalen, FUsbMassStorageDirection dir, const u8 *cmd,
                           int cmdlen, u8 lun)
{
    memset(cbw, 0, sizeof(FUsbMscCbw));

    /* commands are typically shorter, but we don't want overflows */
    if ((size_t)cmdlen > sizeof(cbw->CBWCB))
    {
        cmdlen = (int)sizeof(cbw->CBWCB);
    }

    cbw->dCBWSignature = cbw_signature;
    cbw->dCBWTag = ++tag; /* command block tag to device */
    cbw->bCBWLUN = lun; /* logic unit number to send */

    cbw->dCBWDataTransferLength = datalen; /*  number of bytes of data expect to transfer */
    cbw->bmCBWFlags = dir;

    memcpy(cbw->CBWCB, cmd, cmdlen); /* the command block to be executed by the device */

    cbw->bCBWCBLength = cmdlen; /* the valid length of the CBWCB in bytes */
    return;
}

static int FUsbMscGetCsw(FUsbEndpoint *ep, FUsbMscCsw *csw)
{
    FUsbHc *ctrlr = ep->dev->controller;
    int ret = ctrlr->bulk(ep, sizeof(FUsbMscCsw), (u8 *)csw, 1);

    /* Some broken sticks send a zero-length packet at the end of their data
       transfer which would show up here. Skip it to get the actual CSW. */
    if (ret == 0)
    {
        ret = ctrlr->bulk(ep, sizeof(FUsbMscCsw), (u8 *)csw, 1);
    }

    if (ret < 0)
    {
        FUsbClearStall(ep);
        ret = ctrlr->bulk(ep, sizeof(FUsbMscCsw), (u8 *)csw, 1);
        if (ret < 0)
        {
            return FUsbMscResetTransport(ep->dev);
        }
    }

    if (ret != sizeof(FUsbMscCsw) || csw->dCSWTag != tag ||
        csw->dCSWSignature != csw_signature)
    {
        FUSB_INFO("MSC: received malformed CSW ");
        return FUsbMscResetTransport(ep->dev);
    }

    return MSC_COMMAND_OK;
}

static int FUsbMscExecCmd(FUsbDev *dev, FUsbMassStorageDirection dir, const u8 *cb, int cblen,
                          u8 *buf, int buflen, int residue_ok)
{
    FUsbMscCbw cbw;
    FUsbMscCsw csw;

    int always_succeed = 0;
    if ((cb[0] == 0x1b) && (cb[4] == 1)) /* check if it is Bulk-Only Mass Storage Reset request with reques type 00100001b */
    {
        /* start command, always succeed */
        always_succeed = 1;
    }

    FUsbMscWrapCbw(&cbw, buflen, dir, cb, cblen, MSC_INST(dev)->lun);

    if (dev->controller->bulk(MSC_INST(dev)->bulk_out, sizeof(cbw), (u8 *)&cbw, 0) < 0)
    {
        return FUsbMscResetTransport(dev);
    }

    if (buflen > 0)
    {
        if (dir == FUSB_DIR_DATA_IN)
        {
            if (dev->controller->bulk(MSC_INST(dev)->bulk_in, buflen, buf, 0) < 0)
            {
                FUsbClearStall(MSC_INST(dev)->bulk_in);
            }
        }
        else
        {
            if (dev->controller->bulk(MSC_INST(dev)->bulk_out, buflen, buf, 0) < 0)
            {
                FUsbClearStall(MSC_INST(dev)->bulk_out);
            }
        }
    }

    int ret = FUsbMscGetCsw(MSC_INST(dev)->bulk_in, &csw);

    if (ret)
    {
        return ret;
    }
    else if (always_succeed == 1)
    {
        /* return success, regardless of message */
        return MSC_COMMAND_OK;
    }
    else if (csw.bCSWStatus == 2)
    {
        /* phase error, reset transport */
        return FUsbMscResetTransport(dev);
    }
    else if (csw.bCSWStatus == 0)
    {
        if ((csw.dCSWDataResidue == 0) || residue_ok)
            /* no error, exit */
        {
            return MSC_COMMAND_OK;
        }
        else
            /* missed some bytes */
        {
            return MSC_COMMAND_FAIL;
        }
    }
    else
    {
        if (cb[0] == 0x03)
            /* requesting sense failed, that's bad */
        {
            return MSC_COMMAND_FAIL;
        }
        else if (cb[0] == 0)
            /* If command was TEST UNIT READY determine if the
             * device is of removable type indicating no media
             * found. */
        {
            return FUsbMscRequestNoMedia(dev);
        }
        /* error "check condition" or reserved error */
        ret = FUsbMscRequestSense(dev);
        /* return fail or the status of FUsbMscRequestSense if it's worse */
        return ret ? ret : MSC_COMMAND_FAIL;
    }
}

typedef struct
{
    unsigned char command;    /* 0 */
    unsigned char res1;       /* 1 */
    unsigned int block;       /* 2-5 */
    unsigned char res2;       /* 6 */
    unsigned short numblocks; /* 7-8 */
    unsigned char control;    /* 9 - the block is 10 bytes long */
} __attribute__((packed)) FUsbMscCmdBlk;

typedef struct
{
    unsigned char command; /* 0 */
    unsigned char res1;    /* 1 */
    unsigned char res2;    /* 2 */
    unsigned char res3;    /* 3 */
    union
    {
        /* 4 */
        struct
        {
            unsigned long start : 1; /* for START STOP UNIT */
            unsigned long : 7;
        };
        unsigned char length; /* for REQUEST SENSE */
    };
    unsigned char control; /* 5 */
} __attribute__((packed)) FUsbMscCmdBlk6;

/**
 * Like FUsbMscRwBlks, but for soft-sectors of 512b size. Converts the
 * start and count from 512b units.
 * Start and count must be aligned so that they match the native
 * sector size.
 *
 */
/**
 * @name: FUsbMscRwBlk512
 * @msg: 读写USB大容量存储设备，以512字节为一块
 * @param dev device to access
 * @param start first sector to access
 * @param n number of sectors to access
 * @param dir direction of access: FUSB_DIR_DATA_IN == read, FUSB_DIR_DATA_OUT == write
 * @param buf buffer to read into or write from. Must be at least n*512 bytes
 * @return 0 on success, 1 on failure
 */
int FUsbMscRwBlk512(FUsbDev *dev, int start, int n,
                    FUsbMassStorageDirection dir, u8 *buf)
{
    int blocksize_divider = MSC_INST(dev)->blocksize / 512;
    return FUsbMscRwBlks(dev, start / blocksize_divider,
                         n / blocksize_divider, dir, buf);
}

/**
 * Reads or writes a number of sequential blocks on a USB storage device.
 * As it uses the READ(10) SCSI-2 command, it's limited to storage devices
 * of at most 2TB. It assumes sectors of 512 bytes.
 *
 * @param dev device to access
 * @param start first sector to access
 * @param n number of sectors to access
 * @param dir direction of access: FUSB_DIR_DATA_IN == read, FUSB_DIR_DATA_OUT == write
 * @param buf buffer to read into or write from. Must be at least n*sectorsize bytes
 * @return 0 on success, 1 on failure
 */
static int FUsbMscRwChunk(FUsbDev *dev, int start, int n, FUsbMassStorageDirection dir, u8 *buf)
{
    FUsbMscCmdBlk cb;
    memset(&cb, 0, sizeof(cb));
    if (dir == FUSB_DIR_DATA_IN)
    {
        /* read */
        cb.command = 0x28;
    }
    else
    {
        /* write */
        cb.command = 0x2a;
    }
    cb.block = htonl(start);
    cb.numblocks = htons(n);

    return FUsbMscExecCmd(dev, dir, (u8 *)&cb, sizeof(cb), buf,
                          n * MSC_INST(dev)->blocksize, 0) != MSC_COMMAND_OK
           ? 1
           : 0;
}

/**
 * Reads or writes a number of sequential blocks on a USB storage device
 * that is split into MAX_CHUNK_BYTES size requests.
 *
 * As it uses the READ(10) SCSI-2 command, it's limited to storage devices
 * of at most 2TB. It assumes sectors of 512 bytes.
 *
 * @param dev device to access
 * @param start first sector to access
 * @param n number of sectors to access
 * @param dir direction of access: FUSB_DIR_DATA_IN == read,
 *                                 FUSB_DIR_DATA_OUT == write
 * @param buf buffer to read into or write from.
 *            Must be at least n*sectorsize bytes
 * @return 0 on success, 1 on failure
 */
static int FUsbMscRwBlks(FUsbDev *dev, int start, int n, FUsbMassStorageDirection dir, u8 *buf)
{
    int chunk_size = MAX_CHUNK_BYTES / MSC_INST(dev)->blocksize;
    int chunk;

    /* Read as many full chunks as needed. */
    for (chunk = 0; chunk < (n / chunk_size); chunk++)
    {
        if (FUsbMscRwChunk(dev, start + (chunk * chunk_size),
                           chunk_size, dir,
                           buf + (chunk * MAX_CHUNK_BYTES)) != MSC_COMMAND_OK)
        {
            return 1;
        }
    }

    /* Read any remaining partial chunk at the end. */
    if (n % chunk_size)
    {
        if (FUsbMscRwChunk(dev, start + (chunk * chunk_size),
                           n % chunk_size, dir,
                           buf + (chunk * MAX_CHUNK_BYTES)) != MSC_COMMAND_OK)
        {
            return 1;
        }
    }

    return 0;
}

/* Only request it, we don't interpret it.
   On certain errors, that's necessary to get devices out of
   a special state called "Contingent Allegiance Condition" */
static int FUsbMscRequestSense(FUsbDev *dev)
{
    u8 buf[19];
    FUsbMscCmdBlk6 cb;
    memset(&cb, 0, sizeof(cb));
    cb.command = 0x3;
    cb.length = sizeof(buf);

    return FUsbMscExecCmd(dev, FUSB_DIR_DATA_IN, (u8 *)&cb,
                          sizeof(cb), buf, sizeof(buf), 1);
}

static int FUsbMscRequestNoMedia(FUsbDev *dev)
{
    u8 buf[19];
    int ret;
    FUsbMscCmdBlk6 cb;
    memset(&cb, 0, sizeof(cb));
    cb.command = 0x3;
    cb.length = sizeof(buf);

    ret = FUsbMscExecCmd(dev, FUSB_DIR_DATA_IN, (u8 *)&cb,
                         sizeof(cb), buf, sizeof(buf), 1);

    if (ret)
    {
        return ret;
    }

    /* Check if sense key is set to NOT READY. */
    if ((buf[2] & 0xf) != 2)
    {
        return MSC_COMMAND_FAIL;
    }

    /* Check if additional sense code is 0x3a. */
    if (buf[12] != 0x3a)
    {
        return MSC_COMMAND_FAIL;
    }

    /* No media is present. Return MSC_COMMAND_OK while marking the disk
     * not ready. */
    FUSB_INFO("Empty media found. ");
    MSC_INST(dev)->ready = FUSB_MSC_NOT_READY;
    return MSC_COMMAND_OK;
}

static int FUsbMscCheckIfReady(FUsbDev *dev)
{
    FUsbMscCmdBlk6 cb;
    memset(&cb, 0, sizeof(cb)); /* full initialization for T-U-R */

    /* Bulk-Only Mass Storage Reset, class-specific request */
    return FUsbMscExecCmd(dev, FUSB_DIR_DATA_OUT, (u8 *)&cb,
                          sizeof(cb), 0, 0, 0);
}

static int FUsbMscSpinUp(FUsbDev *dev)
{
    FUsbMscCmdBlk6 cb;
    memset(&cb, 0, sizeof(cb));
    cb.command = 0x1b;
    cb.start = 1;
    return FUsbMscExecCmd(dev, FUSB_DIR_DATA_OUT, (u8 *)&cb,
                          sizeof(cb), 0, 0, 0);
}

static int FUsbMscReadCapcity(FUsbDev *dev)
{
    FUsbMscCmdBlk cb;
    memset(&cb, 0, sizeof(cb));
    cb.command = 0x25; /* read capacity */
    u32 buf[2];

    FUSB_INFO("Reading capacity of mass storage device. ");
    int count = 0, ret;
    while (count++ < 20)
    {
        switch (ret = FUsbMscExecCmd(dev, FUSB_DIR_DATA_IN, (u8 *)&cb,
                                     sizeof(cb), (u8 *)buf, 8, 0))
        {
            case MSC_COMMAND_OK:
                break;
            case MSC_COMMAND_FAIL:
                continue;
            default: /* if it's worse return */
                return ret;
        }
        break;
    }
    if (count >= 20)
    {
        /* still not successful, assume 2tb in 512byte sectors, which is just the same garbage as any other number, but probably more usable. */
        FUSB_WARN("Assuming 2 TB with 512-byte sectors as read capacity didn't answer. ");
        MSC_INST(dev)->numblocks = 0xffffffff;
        MSC_INST(dev)->blocksize = 512;
    }
    else
    {
        MSC_INST(dev)->numblocks = ntohl(buf[0]) + 1;
        MSC_INST(dev)->blocksize = ntohl(buf[1]);
    }

    FUSB_INFO("  %d %d-byte sectors (%d MB) ", MSC_INST(dev)->numblocks,
              MSC_INST(dev)->blocksize,
              /* round down high block counts to avoid integer overflow */
              MSC_INST(dev)->numblocks > 1000000
              ? (MSC_INST(dev)->numblocks / 1000) * MSC_INST(dev)->blocksize / 1000
              : MSC_INST(dev)->numblocks * MSC_INST(dev)->blocksize / 1000 / 1000);

    return MSC_COMMAND_OK;
}

static int FUsbMscWaitReady(FUsbDev *dev)
{
    int i;
    /* SCSI/ATA specs say we have to wait up to 30s, but most devices
     * are ready much sooner. Use a 5 sec timeout to better accommodate
     * devices which fail to respond. */
    const tick_t timeout_tick = 1000000;
    FError ret = FUSB_ERR_WAIT_TIMEOUT;

    FUSB_INFO("  Waiting for device to become ready...");

    /* Initially mark the device ready. */
    MSC_INST(dev)->ready = FUSB_MSC_READY;
    tick_t start_tick = FUsbMscStartTick();

    do
    {
        switch (FUsbMscCheckIfReady(dev))
        {
            case MSC_COMMAND_OK:
                break;
            case MSC_COMMAND_FAIL:
                fsleep_millisec(100);
                FUSB_INFO(".");
                continue;
            default:
                /* Device detached, return immediately */
                return FUSB_MSC_DETACHED;
        }
        break;
    }
    while (!FUsbMscTimeout(start_tick, timeout_tick));

    if (FUsbMscTimeout(start_tick, timeout_tick))
    {
        FUSB_INFO("Timeout. Device not ready. ");
        MSC_INST(dev)->ready = FUSB_MSC_NOT_READY;
    }

    /* Don't bother spinning up the storage device if the device is not
     * ready. This can happen when empty card readers are present.
     * Polling will pick it back up if readiness changes. */
    if (!MSC_INST(dev)->ready)
    {
        return MSC_INST(dev)->ready;
    }

    for (i = 0; i < 30; i++)
    {
        FUSB_INFO(".");
        switch (FUsbMscSpinUp(dev))
        {
            case MSC_COMMAND_OK:
                FUSB_INFO(" OK.");
                break;
            case MSC_COMMAND_FAIL:
                fsleep_millisec(100);
                continue;
            default:
                /* Device detached, return immediately */
                return FUSB_MSC_DETACHED;
        }
        break;
    }

    if (FUsbMscReadCapcity(dev) == MSC_COMMAND_DETACHED)
    {
        return FUSB_MSC_DETACHED;
    }

    return MSC_INST(dev)->ready;
}

/**
 * @name: FUsbMassStorageInit
 * @msg: USB大容量存储设备的初始化函数，由应用程序注册到FUSB框架中
 * @return {*}
 * @param {FUsbDev} *dev, USB大容量存储设备实例
 */
void FUsbMassStorageInit(FUsbDev *dev)
{
    FASSERT(dev && dev->configuration);
    FUsbConfigurationDescriptor *cd =
        (FUsbConfigurationDescriptor *)dev->configuration;
    FASSERT(FUSB_DESC_TYPE_CONFIG == cd->bDescriptorType);
    FUsbInterfaceDescriptor *interface =
            (FUsbInterfaceDescriptor *)(((char *)cd) + cd->bLength);
    FASSERT(FUSB_DESC_TYPE_INTERFACE == interface->bDescriptorType);

    if (FUSB_MASS_STORAGE_DEVICE != interface->bInterfaceClass)
    {
        FUSB_ERROR("Class %d not supported. ", interface->bInterfaceClass);
        return;
    }

    FUSB_INFO("	command set: %s protocol: %s ",
              FUsbMscSubClassString[interface->bInterfaceSubClass],
              FUsbMscProtocolStrings[interface->bInterfaceProtocol]);

    if (interface->bInterfaceProtocol != FUSB_MSC_PROTOCOL_BULK_ONLY)
    {
        FUSB_ERROR("  Protocol not supported. ");
        FUsbDetachDev(dev->controller, dev->address);
        return;
    }

    if ((interface->bInterfaceSubClass != FUSB_MSC_SUBCLASS_ATAPI_8020) && /* ATAPI 8020 */
        (interface->bInterfaceSubClass != FUSB_MSC_SUBCLASS_ATAPI_8070) && /* ATAPI 8070 */
        (interface->bInterfaceSubClass != FUSB_MSC_SUBCLASS_SCSI))
    {
        /* SCSI */
        /* Other protocols, such as ATAPI don't seem to be very popular. looks like ATAPI would be really easy to add, if necessary. */
        FUSB_ERROR("  Interface SubClass not supported. ");
        FUsbDetachDev(dev->controller, dev->address);
        return;
    }

    FUsbMassStorageForceInit(dev, 0);
    return;
}

/* Force a device to enumerate as MSC, without checking class/protocol types.
   It must still have a bulk endpoint pair and respond to MSC commands. */
static void FUsbMassStorageForceInit(FUsbDev *dev, u32 quirks)
{
    FASSERT(dev && dev->controller);
    int i;
    FUsb *instance = dev->controller->usb;
    FASSERT(instance);

    /* init .data before setting .destroy */
    dev->data = NULL;
    dev->destroy = FUsbMscDestory;
    dev->poll = FUsbMscPoll;

    FASSERT(NULL == dev->data);
    dev->data = FUSB_ALLOCATE(instance, sizeof(FUsbMassStorage), FUSB_DEFAULT_ALIGN);
    if (NULL == dev->data)
    {
        FUSB_ERROR("Not enough memory for USB MSC device. ");
        FASSERT(0);
    }

    MSC_INST(dev)->bulk_in = NULL;
    MSC_INST(dev)->bulk_out = NULL;
    MSC_INST(dev)->usbdisk_created = 0;
    MSC_INST(dev)->quirks = quirks;

    /* loop over all ep except ep0 to get bulk-in/bulk-out ep instance */
    for (i = 1; i <= dev->num_endp; i++)
    {
        if (dev->endpoints[i].endpoint == 0)
        {
            continue;
        }
        if (dev->endpoints[i].type != FUSB_BULK_EP)
        {
            continue;
        }
        if ((dev->endpoints[i].direction == FUSB_IN) && (MSC_INST(dev)->bulk_in == 0))
        {
            MSC_INST(dev)->bulk_in = &dev->endpoints[i];
        }
        if ((dev->endpoints[i].direction == FUSB_OUT) && (MSC_INST(dev)->bulk_out == 0))
        {
            MSC_INST(dev)->bulk_out = &dev->endpoints[i];
        }
    }

    /* check if non bulk-in ep */
    if (MSC_INST(dev)->bulk_in == NULL)
    {
        FUSB_ERROR("Couldn't find bulk-in endpoint.");
        FUsbDetachDev(dev->controller, dev->address);
        return;
    }

    /* check if non bulk-out ep */
    if (MSC_INST(dev)->bulk_out == NULL)
    {
        FUSB_ERROR("Couldn't find bulk-out endpoint.");
        FUsbDetachDev(dev->controller, dev->address);
        return;
    }

    FUSB_INFO("Using endpoint %x as in, %x as out.",
              MSC_INST(dev)->bulk_in->endpoint,
              MSC_INST(dev)->bulk_out->endpoint);

    /* Some sticks need a little more time to get ready after SET_CONFIG. */
    fsleep_microsec(50);

    FUsbMscInitLuns(dev);
    FUSB_INFO("Has %d luns.", MSC_INST(dev)->num_luns);

    /* Test if msc is ready (nothing to do if it isn't). */
    if (FUsbMscWaitReady(dev) != FUSB_MSC_READY)
    {
        return;
    }

    /* Create the disk. */
    FUsbMscCreateDisk(dev);

    return;
}

static void FUsbMscPoll(FUsbDev *dev)
{
    FUsbMassStorage *msc = MSC_INST(dev);
    int prev_ready = msc->ready;

    if (FUsbMscWaitReady(dev) == FUSB_MSC_DETACHED)
    {
        return;
    }

    if (!prev_ready && msc->ready)
    {
        FUSB_INFO("USB msc: not ready -> ready (lun %d) ", msc->lun);
        FUsbMscCreateDisk(dev);
    }
    else if (prev_ready && !msc->ready)
    {
        FUSB_INFO("USB msc: ready -> not ready (lun %d) ", msc->lun);
        FUsbMscRemoveDisk(dev);
    }
    else if (!prev_ready && !msc->ready)
    {
        u8 new_lun = (msc->lun + 1) % msc->num_luns;
        FUSB_INFO("USB msc: not ready (lun %d) -> lun %d ", msc->lun,
                  new_lun);
        msc->lun = new_lun;
    }

    return;
}
