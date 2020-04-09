/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang         the first version
 * 2019-07-19     Magicoe      The first version for LPC55S6x
 */

#include <string.h>
#include <board.h>

#include "fsl_common.h" 
#include "fsl_iocon.h"

#include "fsl_sdif.h"

#include "fsl_sd.h"

#include "drv_sd.h"

#include <finsh.h>
#include <dfs.h>
#include <dfs_fs.h>
#include "board.h"

static struct mci_device *_mci_device;
static uint8_t sdio_buffer[1024];

#ifdef RT_USING_SDIO

static rt_err_t rt_mci_init(rt_device_t dev)
{
    rt_err_t result = RT_EOK;

    return result;
}

static rt_err_t rt_mci_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_mci_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_mci_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint8_t status = kStatus_Success;
    struct mci_device *mci = (struct mci_device *)dev;

    rt_mutex_take(&mci->lock, RT_WAITING_FOREVER);

    {
        /* non-aligned. */
        uint32_t i;
        rt_size_t sector_adr;
        uint8_t* copy_buffer;

        sector_adr = pos;
        copy_buffer = (uint8_t*)buffer;

        for(i=0; i<size; i++)
        {
            status=SD_ReadBlocks(&mci->card, sdio_buffer, sector_adr, 1);

            memcpy(copy_buffer, sdio_buffer, mci->card.blockSize);
            sector_adr ++;
            copy_buffer += mci->card.blockSize;
        }
    }

    rt_mutex_release(&_mci_device->lock);

    if (status == kStatus_Success) return size;

    return 0;
}

static rt_size_t rt_mci_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_uint8_t status = kStatus_Success;
    struct mci_device *mci = (struct mci_device *)dev;

    rt_mutex_take(&mci->lock, RT_WAITING_FOREVER);

    {
        /* non-aligned. */
        uint32_t i;
        rt_size_t sector_adr;
        uint8_t* copy_buffer;

        sector_adr = pos;
        copy_buffer = (uint8_t*)buffer;

        for(i = 0; i < size; i++)
        {
            memcpy(sdio_buffer, copy_buffer, mci->card.blockSize);

            status = SD_WriteBlocks(&mci->card, sdio_buffer, sector_adr, 1);

            sector_adr ++;
            copy_buffer += mci->card.blockSize;

        }
    }

    /* release and exit */
    rt_mutex_release(&_mci_device->lock);

    if (status == kStatus_Success) return size;

    return 0;
}

static rt_err_t rt_mci_control(rt_device_t dev, int cmd, void *args)
{
    struct mci_device *mci = (struct mci_device *)dev;

    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = mci->card.blockSize;
        geometry->block_size = mci->card.csd.eraseSectorSize;
        geometry->sector_count = mci->card.blockCount;
    }

    return RT_EOK;
}

/*! @brief SDMMC host detect card configuration */
static const sdmmchost_detect_card_t s_sdCardDetect = {
    .cdType = BOARD_SD_DETECT_TYPE,
    .cdTimeOut_ms = (~0U),
};

/*! @brief Card descriptor. */
sd_card_t g_sd;
int rt_hw_mci_init(void)
{
    _mci_device = (struct mci_device *)rt_malloc(sizeof(struct mci_device));
    if (_mci_device == RT_NULL)
    {
        rt_kprintf("mci_hw_init _mci_device rt_malloc failed!\n");
        return -RT_ERROR;
    }
    rt_memset(_mci_device, 0, sizeof(struct mci_device));
    
    /* attach main clock to SDIF */
    CLOCK_AttachClk(kMAIN_CLK_to_SDIO_CLK);
    /* need call this function to clear the halt bit in clock divider register */
    CLOCK_SetClkDiv(kCLOCK_DivSdioClk, (uint32_t)(SystemCoreClock / FSL_FEATURE_SDIF_MAX_SOURCE_CLOCK + 1U), true);

    _mci_device->card = g_sd;
    
    /* Save host information. */
    _mci_device->card.host.base = SDIF;
    _mci_device->card.host.sourceClock_Hz = CLOCK_GetFreq(kCLOCK_SDio);
    _mci_device->card.usrParam.cd = &s_sdCardDetect;
#if 1
    rt_kprintf("\r\nNeed wait a few seconds to SD init, Better Set SystemTick as 1000\r\n");
    rt_kprintf("SDCard Freq %d\r\n", _mci_device->card.host.sourceClock_Hz);
#endif
    if (kStatus_Success != SD_HostInit(&_mci_device->card))
    {
        memset(&_mci_device->card, 0U, sizeof(_mci_device->card));
        rt_kprintf("SD_Init failed!\n");
        return -RT_ERROR;
    }

    /* power off card */
    SD_PowerOffCard(_mci_device->card.host.base, _mci_device->card.usrParam.pwr);
    
    /* check SD card insert */
    if(BOARD_SDIF_CD_STATUS() == true)
    {
        rt_kprintf("\r\nCard detect fail.\r\n");
        return kStatus_Fail;
    }
    
    /* wait card insert */
    if (SD_WaitCardDetectStatus(_mci_device->card.host.base, &s_sdCardDetect, true) == kStatus_Success)
    {
        /* reset host once card re-plug in */
        SD_HostReset(&(_mci_device->card.host));
        /* power on the card */
        SD_PowerOnCard(_mci_device->card.host.base, _mci_device->card.usrParam.pwr);
    }
    else
    {
        rt_kprintf("\r\nCard detect fail.\r\n");
        return kStatus_Fail;
    }
    
    /* Init card. */
    if (SD_CardInit(&_mci_device->card))
    {
        rt_kprintf("\r\nSD card init failed.\r\n");
        return kStatus_Fail;
    }

    /* initialize mutex lock */
    rt_mutex_init(&_mci_device->lock, "sdcard0", RT_IPC_FLAG_FIFO);
    /* create finish event */
    _mci_device->finish_event = rt_event_create("sdcard0", RT_IPC_FLAG_FIFO);

    /* register sdcard device */
    _mci_device->parent.type    = RT_Device_Class_Block;

    _mci_device->geometry.bytes_per_sector = 0;
    _mci_device->geometry.sector_count = 0;
    _mci_device->geometry.block_size = 0;

    _mci_device->parent.init    = rt_mci_init;
    _mci_device->parent.open    = rt_mci_open;
    _mci_device->parent.close   = rt_mci_close;
    _mci_device->parent.read    = rt_mci_read;
    _mci_device->parent.write   = rt_mci_write;
    _mci_device->parent.control = rt_mci_control;

    /* no private, no callback */
    _mci_device->parent.user_data = RT_NULL;
    _mci_device->parent.rx_indicate = RT_NULL;
    _mci_device->parent.tx_complete = RT_NULL;

    rt_device_register(&_mci_device->parent, "sdcard0",
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE );

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_mci_init);

#endif /* endif RT_USING_SDIO */
