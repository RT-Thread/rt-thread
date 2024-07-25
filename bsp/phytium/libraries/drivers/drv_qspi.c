/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-20     zhangyan     first version
 * 2023-05-31     zhangyan     improve functions
 *
 */
#include "rtconfig.h"
#include "rtdevice.h"
#define LOG_TAG      "qspi_drv"
#include "drv_log.h"
#include <rtthread.h>
#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif
#include "drv_qspi.h"
#include "fqspi_flash.h"
#include "fiopad.h"
#include "fqspi_hw.h"
#include "fio_mux.h"

#define QSPI_ALIGNED_BYTE 4

typedef struct
{
    rt_uint32_t fqspi_id;
    const char *name;
    rt_uint32_t init; /* 0 is init already */
    FQspiCtrl fqspi;
    struct rt_spi_bus qspi_bus;
} phytium_qspi_bus;

rt_err_t FQspiInit(phytium_qspi_bus *phytium_qspi_bus)
{
    FError ret = FT_SUCCESS;
    rt_uint32_t qspi_id = phytium_qspi_bus->fqspi_id;

    FIOPadSetQspiMux(qspi_id, FQSPI_CS_0);
    FIOPadSetQspiMux(qspi_id, FQSPI_CS_1);

    FQspiDeInitialize(&(phytium_qspi_bus->fqspi));

    FQspiConfig pconfig = *FQspiLookupConfig(qspi_id);

#ifdef RT_USING_SMART
    pconfig.base_addr = (uintptr)rt_ioremap((void *)pconfig.base_addr, 0x1000);
#endif

    /* Norflash init, include reset and read flash_size */
    ret = FQspiCfgInitialize(&(phytium_qspi_bus->fqspi), &pconfig);
    if (FT_SUCCESS != ret)
    {
        LOG_E("Qspi init failed.\n");
        return -RT_ERROR;
    }
    else
    {
        LOG_D("Qspi init successfully.\n");
    }

    /* Detect connected flash infomation */
    ret = FQspiFlashDetect(&(phytium_qspi_bus->fqspi));
    if (FT_SUCCESS != ret)
    {
        LOG_E("Qspi flash detect failed.\n");
        return -RT_ERROR;
    }
    else
    {
        LOG_D("Qspi flash detect successfully.\n");
    }

#ifdef USING_QSPI_CHANNEL0
    phytium_qspi_bus->fqspi.config.channel = 0;
#elif defined USING_QSPI_CHANNEL1
    phytium_qspi_bus->fqspi.config.channel = 1;
#endif

#ifdef RT_USING_SMART
    phytium_qspi_bus->fqspi.config.mem_start = (uintptr)rt_ioremap((void *)phytium_qspi_bus->fqspi.config.mem_start, (phytium_qspi_bus->fqspi.config.channel + 1) * (phytium_qspi_bus->fqspi.flash_size));
#endif

    return RT_EOK;
}

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
void FtDumpHexByte(const u8 *ptr, u32 buflen)
{
    u8 *buf = (u8 *)ptr;
    fsize_t i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%p: ", ptr + i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
            {
                rt_kprintf("%02X ", buf[i + j]);
            }
            else
            {
                rt_kprintf("   ");
            }
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
            {
                rt_kprintf("%c", (char)(__is_print(buf[i + j]) ? buf[i + j] : '.'));
            }
        rt_kprintf("\r\n");
    }
}

static rt_err_t phytium_qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
    phytium_qspi_bus *qspi_bus;
    qspi_bus = (phytium_qspi_bus *)(struct phytium_qspi_bus *) device->bus->parent.user_data;
    rt_err_t ret = RT_EOK;

    ret = FQspiInit(qspi_bus);
    if (RT_EOK != ret)
    {
        qspi_bus->init = RT_FALSE;
        LOG_E("Qspi init failed!!!\n");
        return -RT_ERROR;
    }
    qspi_bus->init = RT_EOK;

    return RT_EOK;
}

static rt_ssize_t phytium_qspi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);
    FError ret = FT_SUCCESS;
    phytium_qspi_bus *qspi_bus;
    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;

    rt_uint32_t cmd = qspi_message->instruction.content;
    rt_uint32_t flash_addr = qspi_message->address.content;
    rt_uint32_t len = message->length;

    const void *rcvb = message->recv_buf;
    const void *sndb = message->send_buf;

    qspi_bus = (phytium_qspi_bus *)(struct phytium_qspi_bus *) device->bus->parent.user_data;

    /*Distinguish the write mode according to different commands*/
    if (cmd == FQSPI_FLASH_CMD_PP || cmd == FQSPI_FLASH_CMD_QPP || cmd == FQSPI_FLASH_CMD_4PP || cmd == FQSPI_FLASH_CMD_4QPP)
    {
        ret = FQspiFlashErase(&(qspi_bus->fqspi), FQSPI_FLASH_CMD_SE, flash_addr);
        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to erase mem, test result 0x%x.\r\n", ret);
            return -RT_ERROR;
        }
        /* write norflash data */
        ret = FQspiFlashWriteData(&(qspi_bus->fqspi), cmd, flash_addr, (u8 *)message->send_buf, len);

        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to write mem, test result 0x%x.\r\n", ret);
            return -RT_ERROR;
        }
        else
        {
            LOG_D("Write successfully!!!\r\n");
        }

        return RT_EOK;
    }

    /*Distinguish the read mode according to different commands*/
    if (cmd == FQSPI_FLASH_CMD_READ || cmd == FQSPI_FLASH_CMD_4READ || cmd == FQSPI_FLASH_CMD_FAST_READ || cmd == FQSPI_FLASH_CMD_4FAST_READ ||
        cmd == FQSPI_FLASH_CMD_DUAL_READ || cmd == FQSPI_FLASH_CMD_QIOR || cmd == FQSPI_FLASH_CMD_4QIOR)
    {
        ret |= FQspiFlashReadDataConfig(&(qspi_bus->fqspi), cmd);
        if (FT_SUCCESS != ret)
        {
            LOG_D("Failed to config read, test result 0x%x.\r\n", ret);
            return -RT_ERROR;
        }
        /* read norflash data */
        size_t read_len = FQspiFlashReadData(&(qspi_bus->fqspi), flash_addr, (u8 *)message->recv_buf, len);
        if (read_len != len)
        {
            LOG_E("Failed to read mem, read len = %d.\r\n", read_len);
            return -RT_ERROR;
        }
        else
        {
            LOG_D("Read successfully!!!, read_len = %d\r\n", read_len);
        }
        FtDumpHexByte(message->recv_buf, read_len);

        return read_len;
    }

    if (rcvb)
    {
        if (cmd == FQSPI_FLASH_CMD_RDID || cmd == FQSPI_FLASH_CMD_RDSR1 || cmd == FQSPI_FLASH_CMD_RDSR2 || cmd == FQSPI_FLASH_CMD_RDSR3)
        {
            ret |= FQspiFlashSpecialInstruction(&(qspi_bus->fqspi), cmd, (u8 *)rcvb, sizeof(rcvb));
            if (FT_SUCCESS != ret)
            {
                LOG_E("Failed to read flash information.\n");
                return -RT_ERROR;
            }
        }

        return 1;
    }

    if (sndb)
    {
        ret |= FQspiFlashEnableWrite(&(qspi_bus->fqspi));
        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to enable flash reg write.\n");
            return -RT_ERROR;
        }

        ret |= FQspiFlashWriteReg(&(qspi_bus->fqspi), cmd, (u8 *)sndb, 1);
        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to write flash reg.\n");
            return -RT_ERROR;
        }

        return 1;
    }

    LOG_E("cmd not found!!!\r\n");
    return ret;
}

static struct rt_spi_ops phytium_qspi_ops =
{
    .configure = phytium_qspi_configure,
    .xfer = phytium_qspi_xfer,
};

rt_err_t phytium_qspi_bus_attach_device(const char *bus_name, const char *device_name)
{
    struct rt_qspi_device *qspi_device;
    rt_err_t result = RT_EOK;
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    qspi_device = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
    if (qspi_device == RT_NULL)
    {
        LOG_E("Qspi bus attach device failed.");
        result = RT_ENOMEM;
        goto __exit;
    }

    result = rt_spi_bus_attach_device(&(qspi_device->parent), device_name, bus_name, RT_NULL);
__exit:
    if (result != RT_EOK)
    {
        if (qspi_device)
        {
            rt_free(qspi_device);
        }
    }
    return  result;
}

static int rt_qspi_init(phytium_qspi_bus *phytium_qspi)
{
    int result = RT_EOK;

    phytium_qspi->qspi_bus.parent.user_data = phytium_qspi;

    if (rt_qspi_bus_register(&phytium_qspi->qspi_bus, phytium_qspi->name, &phytium_qspi_ops) == RT_EOK)
    {
        LOG_D("Qspi bus register successfully!!!\n");
    }
    else
    {
        LOG_E("Qspi bus register Failed!!!\n");
        result = -RT_ERROR;
    }

    return result;
}

#if defined(RT_USING_QSPI0)
    static phytium_qspi_bus phytium_qspi0_bus;
#endif

int rt_hw_qspi_init(void)
{
#if defined(RT_USING_QSPI0)
    phytium_qspi0_bus.name = "QSPI0";
    phytium_qspi0_bus.fqspi_id = FQSPI0_ID;
    rt_qspi_init(&phytium_qspi0_bus);
#endif
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_qspi_init);
