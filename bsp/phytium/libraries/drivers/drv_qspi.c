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
 *
 */
#include "rtconfig.h"

#ifdef RT_USING_QSPI
#include <rtthread.h>
#include "rtdevice.h"
#include "drv_qspi.h"
#include "fqspi_flash.h"
#include "rtdbg.h"
#include "fiopad.h"

#define DAT_LENGTH 128

static phytium_qspi_bus phytium_qspi =
{
    .fqspi_id = FQSPI0_ID,
};

static struct rt_qspi_device *qspi_device;        /* phytium device bus handle */
static char qspi_bus_name[RT_NAME_MAX] = "QSPIBUS";
static char qspi_dev_name[RT_NAME_MAX] = "QSPIDEV";
extern FIOPadCtrl iopad_ctrl;

rt_err_t FQspiInit(phytium_qspi_bus *phytium_qspi_bus)
{
    FError ret = FT_SUCCESS;
    rt_uint32_t qspi_id = phytium_qspi_bus->fqspi_id;

#ifdef USING_QSPI_CHANNEL0
    FIOPadSetFunc(&iopad_ctrl, FIOPAD_AR51_REG0_OFFSET, FIOPAD_FUNC0);
    FIOPadSetFunc(&iopad_ctrl, FIOPAD_AR45_REG0_OFFSET, FIOPAD_FUNC0);
#endif

#ifdef USING_QSPI_CHANNEL1
    FIOPadSetFunc(&iopad_ctrl, FIOPAD_AR55_REG0_OFFSET, FIOPAD_FUNC0);
    FIOPadSetFunc(&iopad_ctrl, FIOPAD_AR49_REG0_OFFSET, FIOPAD_FUNC0);
#endif

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
        return RT_ERROR;
    }
    else
    {
        rt_kprintf("Qspi init successfully.\n");
    }

    /* Detect connected flash infomation */
    ret = FQspiFlashDetect(&(phytium_qspi_bus->fqspi));
    if (FT_SUCCESS != ret)
    {
        LOG_E("Qspi flash detect failed.\n");
        return RT_ERROR;
    }
    else
    {
        rt_kprintf("Qspi flash detect successfully.\n");
    }

    return RT_EOK;
}

static rt_err_t phytium_qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
    phytium_qspi_bus *qspi_bus;
    qspi_bus = (struct phytium_qspi_bus *) device->bus->parent.user_data;
    rt_err_t ret = RT_EOK;

    ret = FQspiInit(qspi_bus);
    if (RT_EOK != ret)
    {
        qspi_bus->init = RT_FALSE;
        rt_kprintf("Qspi init failed!!!\n");
        return RT_ERROR;
    }
    qspi_bus->init = RT_EOK;

    return RT_EOK;
}

static rt_uint32_t phytium_qspi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);
    phytium_qspi_bus *qspi_bus;
    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;
    rt_uint32_t cmd = qspi_message->instruction.content;
    rt_uint32_t flash_addr = qspi_message->address.content;

    rt_uint8_t *rcvb = message->recv_buf;
    rt_uint8_t *sndb = message->send_buf;
    FError ret = FT_SUCCESS;

    qspi_bus = (struct phytium_qspi_bus *) device->bus->parent.user_data;
#ifdef USING_QSPI_CHANNEL0
    qspi_bus->fqspi.config.channel = 0;
#endif

#ifdef USING_QSPI_CHANNEL1
    qspi_bus->fqspi.config.channel = 1;
#endif
    uintptr addr = qspi_bus->fqspi.config.mem_start + qspi_bus->fqspi.config.channel * qspi_bus->fqspi.flash_size + flash_addr;

#ifdef RT_USING_SMART
    addr = (uintptr)rt_ioremap((void *)addr, 0x2000);
#endif
    /*Distinguish the write mode according to different commands*/
    if (cmd == FQSPI_FLASH_CMD_PP || cmd == FQSPI_FLASH_CMD_QPP || cmd == FQSPI_FLASH_CMD_4PP || cmd == FQSPI_FLASH_CMD_4QPP)
    {
        rt_uint8_t *wr_buf = NULL;
        wr_buf = (rt_uint8_t *)rt_malloc(DAT_LENGTH * sizeof(rt_uint8_t));
        rt_uint8_t len = message->length;
        rt_memcpy(wr_buf, (char *)message->send_buf, len);
        ret = FQspiFlashErase(&(qspi_bus->fqspi), FQSPI_FLASH_CMD_SE, flash_addr);
        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to erase mem, test result 0x%x.\r\n", ret);
            return RT_ERROR;
        }
        /* write norflash data */
        ret = FQspiFlashWriteData(&(qspi_bus->fqspi), cmd, addr, wr_buf, len);

        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to write mem, test result 0x%x.\r\n", ret);
            return RT_ERROR;
        }
        else
        {
            rt_kprintf("Write successfully!!!\r\n");
        }
        rt_free(wr_buf);

        return RT_EOK;
    }

    /*Distinguish the read mode according to different commands*/
    if (cmd == FQSPI_FLASH_CMD_READ || cmd == FQSPI_FLASH_CMD_4READ || cmd == FQSPI_FLASH_CMD_FAST_READ || cmd == FQSPI_FLASH_CMD_4FAST_READ ||
            cmd == FQSPI_FLASH_CMD_DUAL_READ || cmd == FQSPI_FLASH_CMD_QIOR || cmd == FQSPI_FLASH_CMD_4QIOR)
    {
        rt_uint8_t *rd_buf = NULL;
        rd_buf = (rt_uint8_t *)rt_malloc(DAT_LENGTH * sizeof(rt_uint8_t));

        ret |= FQspiFlashReadDataConfig(&(qspi_bus->fqspi), cmd);

        if (FT_SUCCESS != ret)
        {
            rt_kprintf("Failed to config read, test result 0x%x.\r\n", ret);
            return RT_ERROR;
        }
        /* read norflash data */
        size_t read_len = FQspiFlashReadData(&(qspi_bus->fqspi), addr, rd_buf, DAT_LENGTH);
        message->length = read_len;
        if (read_len != DAT_LENGTH)
        {
            rt_kprintf("Failed to read mem, read len = %d.\r\n", read_len);
            return RT_ERROR;
        }
        else
        {
            rt_kprintf("Read successfully!!!\r\n");
            message->recv_buf = rd_buf;
            rt_free(rd_buf);
        }
        FtDumpHexByte(message->recv_buf, read_len);

        return RT_EOK;
    }

    if (rcvb)
    {
        if (cmd == FQSPI_FLASH_CMD_RDID || cmd == FQSPI_FLASH_CMD_RDSR1 || cmd == FQSPI_FLASH_CMD_RDSR2 || cmd == FQSPI_FLASH_CMD_RDSR3)
        {
            ret |= FQspiFlashSpecialInstruction(&(qspi_bus->fqspi), cmd, rcvb, sizeof(rcvb));
            if (FT_SUCCESS != ret)
            {
                LOG_E("Failed to read flash information.\n");
                return RT_ERROR;
            }
        }

        return RT_EOK;
    }

    if (sndb)
    {
        ret |= FQspiFlashEnableWrite(&(qspi_bus->fqspi));
        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to enable flash reg write.\n");
            return RT_ERROR;
        }

        ret |= FQspiFlashWriteReg(&(qspi_bus->fqspi), cmd, sndb, 1);
        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to write flash reg.\n");
            return RT_ERROR;
        }

        return RT_EOK;
    }
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

        return  result;
    }
}

int rt_hw_qspi_init(void)
{
    int result = RT_EOK;

    phytium_qspi.qspi_bus.parent.user_data = &phytium_qspi;

    if (rt_qspi_bus_register(&phytium_qspi.qspi_bus, qspi_bus_name, &phytium_qspi_ops) == RT_EOK)
    {
        rt_kprintf("Qspi bus register successfully!!!\n");
    }
    else
    {
        LOG_E("Qspi bus register Failed!!!\n");
        result = -RT_ERROR;
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_qspi_init);

/*example*/
struct rt_spi_message write_message;
struct rt_spi_message read_message;

rt_err_t qspi_init()
{
    rt_err_t res = RT_EOK;
    res = phytium_qspi_bus_attach_device(qspi_bus_name, qspi_dev_name);
    RT_ASSERT(res == RT_EOK);
    qspi_device = (struct rt_qspi_device *)rt_device_find(qspi_dev_name);

    return res;
}

/*read cmd example message improvement*/
void ReadCmd(struct rt_spi_message *spi_message)
{
    struct rt_qspi_message *message = (struct rt_qspi_message *) spi_message;
    message->address.content = 0x360000 ;/*Flash address*/
    message->instruction.content = 0x03 ;/*read cmd*/

    rt_qspi_transfer_message(qspi_device, message);
}

/*write cmd example message improvement*/
void WriteCmd(struct rt_spi_message *spi_message)
{
    struct rt_qspi_message *message = (struct rt_qspi_message *) spi_message;
    message->address.content = 0x360000 ;/*Flash address*/
    message->instruction.content = 0x02 ;/*write cmd*/
    rt_qspi_transfer_message(qspi_device, message);
}

/*write cmd example message improvement*/
void qspi_thread(void *parameter)
{
    rt_err_t res;

    qspi_init();
    /*Read and write flash chip fixed area repeatedly*/
    write_message.send_buf = "phytium";
    write_message.length = strlen((char *)write_message.send_buf) + 1;
    WriteCmd(&write_message);
    ReadCmd(&read_message);

    write_message.send_buf = "phytium hello world!";
    write_message.length = strlen((char *)write_message.send_buf) + 1;
    WriteCmd(&write_message);
    ReadCmd(&read_message);

    write_message.send_buf = "Welcome to phytium chip";
    write_message.length = strlen((char *)write_message.send_buf) + 1;
    WriteCmd(&write_message);
    ReadCmd(&read_message);

    rt_uint8_t recv;
    rt_uint8_t cmd = 0x9F;/*read the flash status reg2*/
    res = rt_qspi_send_then_recv(qspi_device, &cmd, sizeof(cmd), &recv, sizeof(recv));
    RT_ASSERT(res != RT_EOK);

    rt_kprintf("The status reg = %x \n", recv);

    return 0;
}

rt_err_t qspi_sample(int argc, char *argv[])
{
    rt_thread_t thread;
    rt_err_t res;
    thread = rt_thread_create("qspi_thread", qspi_thread, RT_NULL, 2048, 25, 10);
    res = rt_thread_startup(thread);
    RT_ASSERT(res == RT_EOK);

    return res;
}
/* Enter qspi_sample command for testing */
MSH_CMD_EXPORT(qspi_sample, qspi sample);
#endif

