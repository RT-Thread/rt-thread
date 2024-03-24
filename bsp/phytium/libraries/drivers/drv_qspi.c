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


#define DAT_LENGTH 128
#define QSPI_ALIGNED_BYTE 4
static rt_uint8_t rd_buf[DAT_LENGTH];
static rt_uint8_t wr_buf[DAT_LENGTH];

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
        rt_kprintf("Qspi init successfully.\n");
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
        rt_kprintf("Qspi flash detect successfully.\n");
    }

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
        rt_kprintf("Qspi init failed!!!\n");
        return -RT_ERROR;
    }
    qspi_bus->init = RT_EOK;

    return RT_EOK;
}

static FError QspiFlashWriteData(FQspiCtrl *pctrl, u8 command, uintptr addr, const u8 *buf, size_t len)
{
    RT_ASSERT(pctrl && buf);
    FError ret = FQSPI_SUCCESS;
    u32 loop = 0;
    const u32 mask = (u32)GENMASK(1, 0);
    u32 reg_val = 0;
    u32 val = 0;
    u32 aligned_bit = 0;

    u8 tmp[QSPI_ALIGNED_BYTE] = {0xff, 0xff, 0xff, 0xff};
    uintptr base_addr = pctrl->config.base_addr;

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        LOG_E("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    /* Flash write enable */
    FQspiFlashEnableWrite(pctrl);

    memset(&pctrl->wr_cfg, 0, sizeof(pctrl->wr_cfg));
    /* set cmd region, command */
    pctrl->wr_cfg.wr_cmd = command;
    pctrl->wr_cfg.wr_wait = FQSPI_WAIT_ENABLE;
    /* clear addr select bit */
    pctrl->wr_cfg.wr_addr_sel = 0;
    /* set wr mode, use buffer */
    pctrl->wr_cfg.wr_mode = FQSPI_USE_BUFFER_ENABLE;
    /* set sck_sel region, clk_div */
    pctrl->wr_cfg.wr_sck_sel = FQSPI_SCK_DIV_128;

    /* set addr_sel region, FQSPI_ADDR_SEL_3 or FQSPI_ADDR_SEL_4 */
    switch (command)
    {
        case FQSPI_FLASH_CMD_PP:
        case FQSPI_FLASH_CMD_QPP:
            pctrl->wr_cfg.wr_addr_sel = FQSPI_ADDR_SEL_3;
            break;
        case FQSPI_FLASH_CMD_4PP:
        case FQSPI_FLASH_CMD_4QPP:
            pctrl->wr_cfg.wr_addr_sel = FQSPI_ADDR_SEL_4;
            break;
        default:
            ret |= FQSPI_NOT_SUPPORT;
            return ret;
            break;
    }

    /*write wr_cfg to Write config register 0x08 */
    FQspiWrCfgConfig(pctrl);
    if (IS_ALIGNED(addr, QSPI_ALIGNED_BYTE)) /* if copy src is aligned by 4 bytes */
    {
        /* write alligned data into memory space */
        for (loop = 0; loop < (len >> 2); loop++)
        {
            FQSPI_DAT_WRITE(addr + QSPI_ALIGNED_BYTE * loop, *(u32 *)(buf + QSPI_ALIGNED_BYTE * loop));
        }
        /* write not alligned data into memory space */
        if (len & mask)
        {
            addr = addr + (len & ~mask);
            memcpy(tmp, buf + (len & ~mask), len & mask);
            FQSPI_DAT_WRITE(addr, *(u32 *)(tmp));
        }
    }
    else
    {
        aligned_bit = (addr & mask);
        addr = addr - aligned_bit;
        reg_val = FQSPI_READ_REG32(addr, 0);

        for (loop = 0; loop < (QSPI_ALIGNED_BYTE - aligned_bit); loop++)
        {
            val = (val << 8) | (buf[loop]);
            reg_val &= (~(0xff << (loop * 8)));
        }

        reg_val |= val;
        reg_val = __builtin_bswap32(reg_val);
        FQSPI_DAT_WRITE(addr, reg_val);

        buf = buf + loop;
        len = len - loop;
        addr = addr + QSPI_ALIGNED_BYTE;

        LOG_E("addr=%p, buf=%p, len=%d, value=%#x\r\n", addr, buf, len, *(u32 *)(buf));

        for (loop = 0; loop < (len >> 2); loop++)
        {
            FQSPI_DAT_WRITE(addr + QSPI_ALIGNED_BYTE * loop, *(u32 *)(buf + QSPI_ALIGNED_BYTE * loop));
        }

        if (!IS_ALIGNED(len, QSPI_ALIGNED_BYTE))
        {
            buf = buf + QSPI_ALIGNED_BYTE * loop;
            len = len - QSPI_ALIGNED_BYTE * loop;
            addr = addr + QSPI_ALIGNED_BYTE * loop;
            memcpy(tmp, buf, len);
            FQSPI_DAT_WRITE(addr, *(u32 *)(tmp));
        }
    }

    /* flush buffer data to Flash */
    FQspiWriteFlush(base_addr);

    ret = FQspiFlashWaitForCmd(pctrl);

    return ret;
}

size_t QspiFlashReadData(FQspiCtrl *pctrl, uintptr addr, u8 *buf, size_t len)
{
    /* addr of copy dst or src might be zero */
    RT_ASSERT(pctrl && buf);
    size_t loop = 0;
    const size_t cnt = len / QSPI_ALIGNED_BYTE;    /* cnt number of 4-bytes need copy  */
    const size_t remain = len % QSPI_ALIGNED_BYTE; /* remain number of 1-byte not aligned */
    u8 align_buf[QSPI_ALIGNED_BYTE];
    size_t copy_len = 0;

    intptr src_addr = (intptr)addr; /* conver to 32/64 bit addr */
    intptr dst_addr = (intptr)buf;

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        LOG_E("Nor flash not ready !!!");
        return 0;
    }
    if (0 == pctrl->rd_cfg.rd_cmd)
    {
        LOG_E("Nor flash read command is not ready !!!");
        return 0;
    }

    if (0 == len)
    {
        return 0;
    }

    if (IS_ALIGNED(src_addr, QSPI_ALIGNED_BYTE)) /* if copy src is aligned by 4 bytes */
    {
        /* read 4-bytes aligned buf part */
        for (loop = 0; loop < cnt; loop++)
        {
            *(u32 *)dst_addr = *(volatile u32 *)(src_addr);
            src_addr += QSPI_ALIGNED_BYTE;
            dst_addr += QSPI_ALIGNED_BYTE;
        }

        copy_len += (loop << 2);

        if (remain > 0)
        {
            *(u32 *)align_buf = *(volatile u32 *)(src_addr);
        }

        /* read remain un-aligned buf byte by byte */
        for (loop = 0; loop < remain; loop++)
        {
            *(u8 *)dst_addr = align_buf[loop];
            dst_addr += 1;
        }

        copy_len += loop;

    }
    else /* if copy src is not aligned */
    {
        /* read byte by byte */
        for (loop = 0; loop < len; loop++)
        {
            *(u8 *)dst_addr = *(volatile u8 *)(src_addr);
            dst_addr += 1;
            src_addr += 1;
        }
        copy_len += loop;

    }

    return copy_len;
}

static rt_ssize_t phytium_qspi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);
    phytium_qspi_bus *qspi_bus;
    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;
    rt_uint32_t cmd = qspi_message->instruction.content;
    rt_uint32_t flash_addr = qspi_message->address.content;

    const void *rcvb = message->recv_buf;
    const void *sndb = message->send_buf;
    FError ret = FT_SUCCESS;

    qspi_bus = (phytium_qspi_bus *)(struct phytium_qspi_bus *) device->bus->parent.user_data;

#ifdef USING_QSPI_CHANNEL0
    qspi_bus->fqspi.config.channel = 0;
#elif defined USING_QSPI_CHANNEL1
    qspi_bus->fqspi.config.channel = 1;
#endif

    uintptr addr = qspi_bus->fqspi.config.mem_start + qspi_bus->fqspi.config.channel * qspi_bus->fqspi.flash_size + flash_addr;

#ifdef RT_USING_SMART
    addr = (uintptr)rt_ioremap((void *)addr, 0x2000);
#endif
    /*Distinguish the write mode according to different commands*/
    if (cmd == FQSPI_FLASH_CMD_PP || cmd == FQSPI_FLASH_CMD_QPP || cmd == FQSPI_FLASH_CMD_4PP || cmd == FQSPI_FLASH_CMD_4QPP)
    {
        rt_uint8_t len = message->length;

        rt_memcpy(&wr_buf, (char *)message->send_buf, len);
        ret = FQspiFlashErase(&(qspi_bus->fqspi), FQSPI_FLASH_CMD_SE, flash_addr);
        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to erase mem, test result 0x%x.\r\n", ret);
            return -RT_ERROR;
        }
        /* write norflash data */
        ret = QspiFlashWriteData(&(qspi_bus->fqspi), cmd, addr, (u8 *)&wr_buf, len);

        if (FT_SUCCESS != ret)
        {
            LOG_E("Failed to write mem, test result 0x%x.\r\n", ret);
            return -RT_ERROR;
        }
        else
        {
            rt_kprintf("Write successfully!!!\r\n");
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
            rt_kprintf("Failed to config read, test result 0x%x.\r\n", ret);
            return -RT_ERROR;
        }
        /* read norflash data */
        size_t read_len = QspiFlashReadData(&(qspi_bus->fqspi), addr, (u8 *)&rd_buf, DAT_LENGTH);
        message->length = read_len;
        if (read_len != DAT_LENGTH)
        {
            rt_kprintf("Failed to read mem, read len = %d.\r\n", read_len);
            return -RT_ERROR;
        }
        else
        {
            rt_kprintf("Read successfully!!!\r\n");
            message->recv_buf = &rd_buf;

        }
        FtDumpHexByte(message->recv_buf, read_len);

        return RT_EOK;
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

        return RT_EOK;
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

        return RT_EOK;
    }
    rt_kprintf("cmd not found!!!\r\n");
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
    rt_kprintf("qspi_device addr == %p\n", qspi_device);
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
        rt_kprintf("Qspi bus register successfully!!!\n");
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
