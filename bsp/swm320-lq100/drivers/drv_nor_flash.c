/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 */

#include <rtdevice.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SWM320.h>

#define BLOCK_SIZE (64 * 1024)
#define FLASH_SIZE (BSP_NOR_FLASH_SIZE)
#define BLOCK_COUNTER (FLASH_SIZE / BLOCK_SIZE)

static struct rt_mutex flash_lock;

/* RT-Thread MTD device interface */
static long swm320_read_id(struct rt_mtd_nor_device *device)
{
    return 0xdeadbeef;
}

static rt_size_t swm320_read(struct rt_mtd_nor_device *device,
                             rt_off_t position,
                             rt_uint8_t *data,
                             rt_size_t size)
{
    int ret = rt_mutex_take(&flash_lock, RT_WAITING_FOREVER);
    if (ret == -RT_ETIMEOUT)
    {
        rt_kprintf("Take mutex time out.\n");
        return ret;
    }
    else if (ret == -RT_ERROR)
    {
        rt_kprintf("Take mutex error.\n");
        return ret;
    }

    memcpy(data, ((const void *)(NORFLM_BASE + position)), size);
    rt_mutex_release(&flash_lock);
    return size;
}

static rt_size_t swm320_write(struct rt_mtd_nor_device *device,
                              rt_off_t position,
                              const rt_uint8_t *data,
                              rt_size_t size)
{
    rt_size_t i;
    const rt_uint16_t *hwdata = (const rt_uint16_t *)data;
    int ret = rt_mutex_take(&flash_lock, RT_WAITING_FOREVER);
    if (ret == -RT_ETIMEOUT)
    {
        rt_kprintf("Take mutex time out.\n");
        return ret;
    }
    else if (ret == -RT_ERROR)
    {
        rt_kprintf("Take mutex error.\n");
        return ret;
    }

    for (i = 0; i < size / 2; i++)
    {
        NORFL_Write(position, hwdata[i]);
        position += 2;
    }
    rt_mutex_release(&flash_lock);
    return size;
}

static rt_err_t swm320_erase_block(struct rt_mtd_nor_device *device,
                                   rt_off_t offset,
                                   rt_uint32_t length)
{
    rt_err_t ret = rt_mutex_take(&flash_lock, RT_WAITING_FOREVER);
    if (ret == -RT_ETIMEOUT)
    {
        rt_kprintf("Take mutex time out.\n");
        return ret;
    }
    else if (ret == -RT_ERROR)
    {
        rt_kprintf("Take mutex error.\n");
        return ret;
    }
    
    NORFL_SectorErase(offset);
    rt_mutex_release(&flash_lock);
    return RT_EOK;
}

const static struct rt_mtd_nor_driver_ops mtd_ops =
{
    swm320_read_id,
    swm320_read,
    swm320_write,
    swm320_erase_block
};

static rt_err_t hw_init()
{
    NORFL_InitStructure NORFL_InitStruct;
    PORT->PORTP_SEL0 = 0xAAAAAAAA; //PP0-23 => ADDR0-23
    PORT->PORTP_SEL1 = 0xAAAA;

    PORT->PORTM_SEL0 = 0xAAAAAAAA; //PM0-15 => DATA15-0
    PORT->PORTM_INEN = 0xFFFF;

    PORT->PORTM_SEL1 = 0x2AA; //PM16 => OEN, PM17 => WEN, PM18 => NORFL_CSN,PM19 => SDRAM_CSN, PM20 => SRAM_CSN, PM21 => SDRAM_CKE

    NORFL_InitStruct.DataWidth = 16;
    NORFL_InitStruct.WELowPulseTime = 5;
    NORFL_InitStruct.OEPreValidTime = 12;
    NORFL_InitStruct.OperFinishIEn = 0;
    NORFL_InitStruct.OperTimeoutIEn = 0;
    NORFL_Init(&NORFL_InitStruct);
    return RT_EOK;
}
static struct rt_mtd_nor_device mtd;
int rt_hw_norflash_init(void)
{
    hw_init();
    /* set page size and block size */
    mtd.block_size = BLOCK_SIZE; /* 64kByte */
    mtd.ops = &mtd_ops;

    /* initialize mutex */
    if (rt_mutex_init(&flash_lock, "nor", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        rt_kprintf("init sd lock mutex failed\n");
        return -RT_ERROR;
    }
    mtd.block_start = 0;
    mtd.block_end = BLOCK_COUNTER;

    /* register MTD device */
    rt_mtd_nor_register_device("nor", &mtd);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_norflash_init);

#ifdef RT_USING_FINSH
#include <finsh.h>
void nor_erase(void)
{
    NORFL_ChipErase();
}
MSH_CMD_EXPORT(nor_erase, erase all block in SPI flash);
#endif
