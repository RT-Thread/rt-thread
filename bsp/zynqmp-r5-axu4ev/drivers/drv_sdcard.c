/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-24     WangHuachen  the first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <dfs_fs.h>
#include <drivers/mmcsd_core.h>

#include <stdint.h>
#include <stdio.h>

#include "drv_sdcard.h"
#include "xsdps_core.h"

#define DBG_TAG "drv.sdcard"
#define DBG_LVL DBG_INFO
#include "rtdbg.h"

#define FILE_SYSTEM_INTERFACE_SD
#define SD_CD_DELAY 10000U

typedef rt_uint8_t BYTE;
typedef rt_uint32_t DWORD;
typedef unsigned int UINT;

/* Status of Disk Functions */
typedef rt_uint8_t DSTATUS;

/* Results of Disk Functions */
typedef enum
{
    RES_OK = 0, /* 0: Successful */
    RES_ERROR,  /* 1: R/W Error */
    RES_WRPRT,  /* 2: Write Protected */
    RES_NOTRDY, /* 3: Not Ready */
    RES_PARERR  /* 4: Invalid Parameter */
} DRESULT;

/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT 0x01  /* Drive not initialized */
#define STA_NODISK 0x02  /* No medium in the drive */
#define STA_PROTECT 0x04 /* Write protected */

static DSTATUS Stat[2] = {STA_NOINIT, STA_NOINIT}; /* Disk status */

#ifdef FILE_SYSTEM_INTERFACE_SD
static XSdPs SdInstance[2];
static u32 BaseAddress;
static u32 CardDetect;
static u32 WriteProtect;
static u32 SlotType[2];
static u8 HostCntrlrVer[2];
#endif

static BYTE sdcard_drvnum = 0;
static struct rt_device sdcard_device;
static struct dfs_partition part;
static struct rt_mutex sd_lock[2];

static DSTATUS disk_status(
    BYTE pdrv /* Drive number (0) */
)
{
    DSTATUS s = Stat[pdrv];
#ifdef FILE_SYSTEM_INTERFACE_SD
    u32 StatusReg;
    u32 DelayCount = 0;

    if (SdInstance[pdrv].Config.BaseAddress == (u32)0)
    {
#ifdef XPAR_XSDPS_1_DEVICE_ID
        if (pdrv == 1)
        {
            BaseAddress = XPAR_XSDPS_1_BASEADDR;
            CardDetect = XPAR_XSDPS_1_HAS_CD;
            WriteProtect = XPAR_XSDPS_1_HAS_WP;
        }
        else
        {
#endif
            BaseAddress = XPAR_XSDPS_0_BASEADDR;
            CardDetect = XPAR_XSDPS_0_HAS_CD;
            WriteProtect = XPAR_XSDPS_0_HAS_WP;
#ifdef XPAR_XSDPS_1_DEVICE_ID
        }
#endif
        HostCntrlrVer[pdrv] = (u8)(XSdPs_ReadReg16(BaseAddress,
                                                   XSDPS_HOST_CTRL_VER_OFFSET) &
                                   XSDPS_HC_SPEC_VER_MASK);
        if (HostCntrlrVer[pdrv] == XSDPS_HC_SPEC_V3)
        {
            SlotType[pdrv] = XSdPs_ReadReg(BaseAddress,
                                           XSDPS_CAPS_OFFSET) &
                             XSDPS_CAPS_SLOT_TYPE_MASK;
        }
        else
        {
            SlotType[pdrv] = 0;
        }
    }

    /* If SD is not powered up then mark it as not initialized */
    if ((XSdPs_ReadReg8((u32)BaseAddress, XSDPS_POWER_CTRL_OFFSET) &
         XSDPS_PC_BUS_PWR_MASK) == 0U)
    {
        s |= STA_NOINIT;
    }

    StatusReg = XSdPs_GetPresentStatusReg((u32)BaseAddress);
    if (SlotType[pdrv] != XSDPS_CAPS_EMB_SLOT)
    {
        if (CardDetect)
        {
            while ((StatusReg & XSDPS_PSR_CARD_INSRT_MASK) == 0U)
            {
                if (DelayCount == 500U)
                {
                    s = STA_NODISK | STA_NOINIT;
                    goto Label;
                }
                else
                {
                    /* Wait for 10 msec */
                    usleep(SD_CD_DELAY);
                    DelayCount++;
                    StatusReg = XSdPs_GetPresentStatusReg((u32)BaseAddress);
                }
            }
        }
        s &= ~STA_NODISK;
        if (WriteProtect)
        {
            if ((StatusReg & XSDPS_PSR_WPS_PL_MASK) == 0U)
            {
                s |= STA_PROTECT;
                goto Label;
            }
        }
        s &= ~STA_PROTECT;
    }
    else
    {
        s &= ~STA_NODISK & ~STA_PROTECT;
    }

Label:
    Stat[pdrv] = s;
#endif

    return s;
}

static DSTATUS disk_initialize(
    BYTE pdrv /* Physical drive number (0) */
)
{
    DSTATUS s;
#ifdef FILE_SYSTEM_INTERFACE_SD
    s32 Status = XST_FAILURE;
    XSdPs_Config *SdConfig;
#endif

    s = disk_status(pdrv);
    if ((s & STA_NODISK) != 0U)
    {
        return s;
    }

    /* If disk is already initialized */
    if ((s & STA_NOINIT) == 0U)
    {
        return s;
    }

#ifdef FILE_SYSTEM_INTERFACE_SD
    if (CardDetect)
    {
        /*
             * Card detection check
             * If the HC detects the No Card State, power will be cleared
             */
        while (!((XSDPS_PSR_CARD_DPL_MASK |
                  XSDPS_PSR_CARD_STABLE_MASK |
                  XSDPS_PSR_CARD_INSRT_MASK) ==
                 (XSdPs_GetPresentStatusReg((u32)BaseAddress) &
                  (XSDPS_PSR_CARD_DPL_MASK |
                   XSDPS_PSR_CARD_STABLE_MASK |
                   XSDPS_PSR_CARD_INSRT_MASK))))
            ;
    }

    /*
     * Initialize the host controller
     */
    SdConfig = XSdPs_LookupConfig((u16)pdrv);
    if (NULL == SdConfig)
    {
        s |= STA_NOINIT;
        return s;
    }

    Status = XSdPs_CfgInitialize(&SdInstance[pdrv], SdConfig,
                                 SdConfig->BaseAddress);
    if (Status != XST_SUCCESS)
    {
        s |= STA_NOINIT;
        return s;
    }

    Status = XSdPs_CardInitialize(&SdInstance[pdrv]);
    if (Status != XST_SUCCESS)
    {
        s |= STA_NOINIT;
        return s;
    }

    /*
     * Disk is initialized.
     * Store the same in Stat.
     */
    s &= (~STA_NOINIT);

    Stat[pdrv] = s;
#endif

#ifdef FILE_SYSTEM_INTERFACE_RAM
    /* Assign RAMFS address value from xparameters.h */
    dataramfs = (char *)RAMFS_START_ADDR;

    /* Clearing No init Status for RAM */
    s &= (~STA_NOINIT);
    Stat[pdrv] = s;
#endif

    return s;
}

static DRESULT disk_read(
    BYTE pdrv,    /* Physical drive number (0) */
    BYTE *buff,   /* Pointer to the data buffer to store read data */
    DWORD sector, /* Start sector number (LBA) */
    UINT count    /* Sector count (1..128) */
)
{
    DSTATUS s;
#ifdef FILE_SYSTEM_INTERFACE_SD
    s32 Status = XST_FAILURE;
    DWORD LocSector = sector;
#endif

    s = disk_status(pdrv);

    if ((s & STA_NOINIT) != 0U)
    {
        return RES_NOTRDY;
    }
    if (count == 0U)
    {
        return RES_PARERR;
    }

#ifdef FILE_SYSTEM_INTERFACE_SD
    /* Convert LBA to byte address if needed */
    if ((SdInstance[pdrv].HCS) == 0U)
    {
        LocSector *= (DWORD)XSDPS_BLK_SIZE_512_MASK;
    }

    Status = XSdPs_ReadPolled(&SdInstance[pdrv], (u32)LocSector, count, buff);
    if (Status != XST_SUCCESS)
    {
        return RES_ERROR;
    }
#endif

#ifdef FILE_SYSTEM_INTERFACE_RAM
    memcpy(buff, dataramfs + (sector * SECTORSIZE), count * SECTORSIZE);
#endif

    return RES_OK;
}

static DRESULT disk_write(
    BYTE pdrv,        /* Physical drive nmuber (0..) */
    const BYTE *buff, /* Data to be written */
    DWORD sector,     /* Sector address (LBA) */
    UINT count        /* Number of sectors to write (1..128) */
)
{
    DSTATUS s;
#ifdef FILE_SYSTEM_INTERFACE_SD
    s32 Status = XST_FAILURE;
    DWORD LocSector = sector;
#endif

    s = disk_status(pdrv);
    if ((s & STA_NOINIT) != 0U)
    {
        return RES_NOTRDY;
    }
    if (count == 0U)
    {
        return RES_PARERR;
    }

#ifdef FILE_SYSTEM_INTERFACE_SD
    /* Convert LBA to byte address if needed */
    if ((SdInstance[pdrv].HCS) == 0U)
    {
        LocSector *= (DWORD)XSDPS_BLK_SIZE_512_MASK;
    }

    Status = XSdPs_WritePolled(&SdInstance[pdrv], (u32)LocSector, count, buff);
    if (Status != XST_SUCCESS)
    {
        return RES_ERROR;
    }

#endif

#ifdef FILE_SYSTEM_INTERFACE_RAM
    memcpy(dataramfs + (sector * SECTORSIZE), buff, count * SECTORSIZE);
#endif

    return RES_OK;
}

static rt_err_t rt_sdcard_init(rt_device_t dev)
{
    char sdlock_name[20];
    BYTE drvnum = *((BYTE *)dev->user_data);

    rt_snprintf(sdlock_name, sizeof(sdlock_name), "sdlock%d", drvnum);
    if (rt_mutex_init(&sd_lock[drvnum], sdlock_name, RT_IPC_FLAG_PRIO) != RT_EOK)
    {
        LOG_E("init sdlock semaphore failed\n");
    }
    else
        LOG_D("sdcard init OK\n");

    return RT_EOK;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(((rt_uint32_t)buffer % 4) == 0);
    DRESULT status;
    BYTE drvnum = *((BYTE *)dev->user_data);

    rt_mutex_take(&sd_lock[drvnum], RT_WAITING_FOREVER);
    status = disk_read(drvnum, buffer, part.offset + pos, size);
    rt_mutex_release(&sd_lock[drvnum]);

    if (status == RES_OK)
        return size;

    LOG_E("sdcard read failed\n");
    return 0;
}

static rt_ssize_t rt_sdcard_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_ASSERT(((rt_uint32_t)buffer % 4) == 0);
    DRESULT status;
    BYTE drvnum = *((BYTE *)dev->user_data);

    rt_mutex_take(&sd_lock[drvnum], RT_WAITING_FOREVER);
    status = disk_write(drvnum, buffer, part.offset + pos, size);
    rt_mutex_release(&sd_lock[drvnum]);

    if (status == RES_OK)
        return size;

    LOG_E("sdcard write failed\n");
    return 0;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    BYTE drvnum = *((BYTE *)dev->user_data);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL)
            return -RT_ERROR;

        geometry->bytes_per_sector = 512;
        geometry->block_size = 128;
        geometry->sector_count = SdInstance[drvnum].SectorCount;
    }

    return RT_EOK;
}

#ifdef BSP_USING_SD0
static int rh_hw_emmc_init(void)
{
    if (disk_initialize(sdcard_drvnum) == RES_OK)
    {
        DRESULT status;
        rt_uint8_t *sector;

        /* get the first sector to read partition table */
        sector = (rt_uint8_t *)rt_malloc(512);
        if (sector == RT_NULL)
        {
            LOG_E("allocate partition sector buffer failed\n");
            return -RT_ERROR;
        }
        status = disk_read(0, sector, 0, 1);
        if (status == RES_OK)
        {
            /* get the first partition */
            if (dfs_filesystem_get_partition(&part, sector, 0) != 0)
            {
                /* there is no partition */
                part.offset = 0;
                part.size = 0;
            }
        }
        else
        {
            /* there is no partition table */
            part.offset = 0;
            part.size = 0;
        }

        /* release sector buffer */
        rt_free(sector);

        /* register sdcard device */
        sdcard_device.type = RT_Device_Class_Block;
        sdcard_device.init = rt_sdcard_init;
        sdcard_device.open = rt_sdcard_open;
        sdcard_device.close = rt_sdcard_close;
        sdcard_device.read = rt_sdcard_read;
        sdcard_device.write = rt_sdcard_write;
        sdcard_device.control = rt_sdcard_control;

        /* no private */
        sdcard_device.user_data = &sdcard_drvnum;
        rt_device_register(&sdcard_device, "sd0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
        return RT_EOK;
    }

    return -RT_ERROR;
}
INIT_DEVICE_EXPORT(rh_hw_emmc_init);
#endif
