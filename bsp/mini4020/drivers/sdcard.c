/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author      Notes
 * 2007-12-02     Yi.Qiu      the first version
 * 2010-01-01     Bernard     Modify for mini2440
 * 2010-10-13     Wangmeng    Added sep4020 support
 */

#include <rtthread.h>

#include "sdcard.h"

#ifdef RT_USING_DFS
volatile rt_int32_t RCA;

/* RT-Thread Device Driver Interface */
#include <dfs_fs.h>

/*GLOBAL SD DEVICE PONITER*/
static struct sd_device *ptr_sddev;
static rt_uint8_t gsec_buf[SECTOR_SIZE];

#define USE_TIMEOUT

/*This file is to power on/off the SEP4020 SDC*/
/**
 * This function will power on/off the SEP4020 SDC
 *
 * @param sd_ctl: 0/power on; 1/power off
 * @return none
 *
 */
static void sd_pwr(int sd_ctl)
{
    if (sd_ctl)
    {
        *(RP)GPIO_PORTA_SEL  |= 0x0200;
        *(RP)GPIO_PORTA_DIR  &= (~0x0200);
        *(RP)GPIO_PORTA_DATA |= 0x0200;
    }
    else
    {

        *(RP)GPIO_PORTA_SEL |= 0x0200;
        *(RP)GPIO_PORTA_DIR &= (~0x0200);
        *(RP)GPIO_PORTA_DATA &= (~0x0200);
    }
}

/*a nop operation to delay*/
static void delay(U32 j)
{
    U32 i;

    for (i = 0; i < j; i++)
    {
        /* nothing */
    }
}

/*
* Send the command to set the data transfer mode
* @param cmd:the command to sent
* @param arg:the argument of the command
* @param mode:SDC transfer mode
* @param blk_len:the block size of each data
* @param num:number of blocks
* @param mask:sdc interrupt mask
*/
static rt_err_t cmd_data(U16 cmd, U32 arg, U16 mode, U16 blk_len, U16 num, U16 mask)
{
    U32 i;
#ifdef USE_TIMEOUT
    U32 to = 10000;
#endif

    *(RP)SDC_CLOCK_CONTROL = 0Xff00;
    *(RP)SDC_CLOCK_CONTROL = 0Xff04;
    *(RP)SDC_INTERRUPT_STATUS_MASK = mask;

    *(RP)SDC_TRANSFER_MODE = mode;

    *(RP)SDC_BLOCK_SIZE = blk_len;
    *(RP)SDC_BLOCK_COUNT = num;
    *(RP)SDC_ARGUMENT = arg;
    *(RP)SDC_COMMAND = cmd;

    delay(10);

    i = *(RP)SDC_INTERRUPT_STATUS & 0x1000;

    while (i != 0x1000)
    {
        i = *(RP)SDC_INTERRUPT_STATUS & 0x1000;
#ifdef USE_TIMEOUT
        to --;
        if (!to)
        {
            EOUT("%s TIMEOUT\n", __FUNCTION__);
            return RT_ETIMEOUT;
        }
#endif
    }
    delay(160);

    return *(RP)SDC_RESPONSE0;
}

static rt_err_t cmd_response(U16 Cmd, U32 Arg, U16 TransMode, U16 BlkLen, U16 Nob, U16 IntMask)
{
    U32 i;
#ifdef USE_TIMEOUT
    U32 to = 50000;
#endif

    *(RP)SDC_CLOCK_CONTROL = 0Xff00;

    *(RP)SDC_CLOCK_CONTROL = 0Xff04;


    *(RP)SDC_INTERRUPT_STATUS_MASK = IntMask;
    *(RP)SDC_TRANSFER_MODE = TransMode;
    *(RP)SDC_BLOCK_SIZE = BlkLen;
    *(RP)SDC_BLOCK_COUNT = Nob;
    *(RP)SDC_ARGUMENT = Arg;
    *(RP)SDC_COMMAND = Cmd;

    delay(10);

    i = *(RP)SDC_INTERRUPT_STATUS & 0x1040;

    while (i != 0x1040)
    {
        i = *(RP)SDC_INTERRUPT_STATUS & 0x1040;
#ifdef USE_TIMEOUT
        to--;
        if (!to)
        {
            EOUT("%s Timeout\n", __FUNCTION__);
            return RT_ETIMEOUT;
        }
#endif
    }

    //DBOUT("cmd_response TO is %d\n",to);
    delay(100);

    return RT_EOK;
}

static rt_err_t cmd_wait(U16 Cmd, U32 Arg, U16 IntMask)
{
    int i;
#ifdef USE_TIMEOUT
    U32 to = 200000;
#endif

    *(RP)SDC_CLOCK_CONTROL = 0Xff00;

    *(RP)SDC_CLOCK_CONTROL = 0Xff04;

    *(RP)SDC_COMMAND = Cmd;

    *(RP)SDC_INTERRUPT_STATUS_MASK = IntMask;

    *(RP)SDC_ARGUMENT = Arg;

    i = *(RP)SDC_INTERRUPT_STATUS & 0x1000;

    while (i != 0x1000)
    {
        i = *(RP)SDC_INTERRUPT_STATUS & 0x1000;
#ifdef USE_TIMEOUT
        to--;
        if (!to)
        {
            EOUT("%s Timeout\n", __FUNCTION__);
            return RT_ETIMEOUT;
        }
#endif

    }

    //DBOUT("cmd_wait TO is %d\n",to);

    delay(10);

    return RT_EOK;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_err_t sd_init(void)
{
    rt_err_t err;
#ifdef USE_TIMEOUT
    rt_uint32_t to = 1000;
#endif
    sd_pwr(1);

    *(RP)SDC_SOFTWARE_RESET = 0x0;
    delay(200);
    *(RP)SDC_SOFTWARE_RESET = 0x1;
    delay(200);

    cmd_wait(0x08, 0x0, 0xfff);

    do
    {
        err = cmd_wait(0x6ea, 0x0, 0xfff);

#ifdef USE_TIMEOUT
        if (err != RT_EOK)
        {
            EOUT("cmd_wait err in %s\n", __FUNCTION__);
            return RT_ETIMEOUT;
        }
#endif

        delay(3);
        err = cmd_wait(0x52a, 0x80ff8000, 0xfff);
        if (err != RT_EOK)
        {
            EOUT("cmd_wait err in %s\n", __FUNCTION__);
            return RT_ETIMEOUT;
        }
#ifdef USE_TIMEOUT
        to--;
        if (!to)
        {
            EOUT("%s timeout\n", __FUNCTION__);
            return RT_ETIMEOUT;
        }
#endif

    }
    while (*(RP)SDC_RESPONSE0 < 0X80008000);

    cmd_data(0x49, 0X0, 0X0, 0x0, 0x0, 0Xfff);
    cmd_data(0x6a, 0X0, 0X0, 0x0, 0x0, 0Xfff);
    RCA = *(RP)SDC_RESPONSE0;
    cmd_data(0xea, RCA, 0X0, 0x0, 0x0, 0Xfff);

    return RT_EOK;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_err_t sd_readblock(rt_uint32_t address, rt_uint8_t *buf)
{
    U32 complete, i;
    rt_uint8_t temp;
    rt_err_t err;
    rt_uint32_t discard;
#ifdef USE_TIMEOUT
    rt_uint32_t to = 10;
#endif

    RT_UNUSED(discard);

    //rt_kprintf("in readblock:%x\n",address);
    //Clear all the errors & interrups
    *(RP)DMAC_INTINTERRCLR  |= 0x1;
    *(RP)DMAC_INTINTERRCLR  &= ~0x1;
    *(RP)DMAC_INTTCCLEAR    |= 0x1;
    *(RP)DMAC_INTTCCLEAR    &= ~0x1;

    /*Clear read fifo*/
    *(RP)(SDC_INTERRUPT_STATUS_MASK) = ~(0x1 << 9); //don't mask fifo empty
    while ((*(RP)SDC_INTERRUPT_STATUS) & 0x200 != 0x200)
        discard = *(RP)SDC_READ_BUFER_ACCESS;

    /*DMAC2,word,size=0x80*/
    *(RP)DMAC_C2SRCADDR  = SDC_READ_BUFER_ACCESS;
    *(RP)DMAC_C2DESTADDR = (rt_uint32_t)buf;
    *(RP)DMAC_C2CONTROL  = 0x20249b;
    *(RP)DMAC_C2CONFIGURATION = 0x38d;

    err = cmd_wait(0x6ea, RCA, 0xfff);
    if (err != RT_EOK)
    {
        rt_set_errno(err);
        return err;
    }

    err = cmd_wait(0xca, 0x2, 0xfff);
    if (err != RT_EOK)
    {
        rt_set_errno(err);
        return err;
    }

    err = cmd_response(0x22e, address, 0X1, 0x0200, 0x1, 0Xfff); //CMD17 4bit mode
    if (err != RT_EOK)
    {
        rt_set_errno(err);
        return err;
    }

    complete = *(RP)SDC_INTERRUPT_STATUS;

    /*CRC*/
    if ((complete | 0xfffffffd) != 0xfffffffd)
    {
        rt_kprintf("CRC ERROR!!!\n");
        complete = *(RP)SDC_INTERRUPT_STATUS;
    }
    while (((*(RP)(DMAC_INTTCSTATUS)) & 0x4) != 0x4)
    {
        delay(10);
#ifdef USE_TIMEOUT
        to--;
        if (!to)
        {
            EOUT("%s TIMEOUT\n", __FUNCTION__);
            return RT_ETIMEOUT;
        }
#endif
    }
#ifdef USE_TIMEOUT
    //DBOUT("%s timeout is %d\n",__FUNCTION__,to);
#endif
    /*for the buf is big-endian we must reverse it*/
    for (i = 0; i < 0x80; i++)
    {
        temp = buf[0];
        buf[0] = buf[3];
        buf[3] = temp;

        temp = buf[1];
        buf[1] = buf[2];
        buf[2] = temp;

        buf += 4;
    }

    return RT_EOK;
}

static rt_uint8_t sd_readmultiblock(rt_uint32_t address, rt_uint8_t *buf, rt_uint32_t size)
{
    rt_int32_t index;
    rt_uint8_t status = RT_EOK;

    for (index = 0; index < size; index++)
    {
        status = sd_readblock(address + index * SECTOR_SIZE, buf + index * SECTOR_SIZE);
        if (status != RT_EOK)
            break;
    }
    return status;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_uint8_t sd_writeblock(rt_uint32_t address, rt_uint8_t *buf)
{
    U32 complete;
    rt_uint8_t temp;
    rt_uint8_t *ptr = buf;
    rt_err_t err;
#ifdef USE_TIMEOUT
    rt_uint32_t to = 10;
#endif

    int i;

    rt_kprintf("in writeblock:%x\n", address);

    /*for the buf is big-endian we must reverse it*/
    for (i = 0; i < 0x80; i++)
    {
        temp = ptr[0];
        ptr[0] = ptr[3];
        ptr[3] = temp;

        temp = ptr[1];
        ptr[1] = ptr[2];
        ptr[2] = temp;

        ptr += 4;
    }
    //Clear all the errors & interrups
    *(RP)DMAC_INTINTERRCLR  |= 0x1;
    *(RP)DMAC_INTINTERRCLR  &= ~0x1;
    *(RP)DMAC_INTTCCLEAR    |= 0x1;
    *(RP)DMAC_INTTCCLEAR    &= ~0x1;

    *(RP)DMAC_C2SRCADDR  = (U32)buf;
    *(RP)DMAC_C2DESTADDR = SDC_WRITE_BUFER_ACCESS;
    *(RP)DMAC_C2CONTROL  = 0x20149b;
    *(RP)DMAC_C2CONFIGURATION = 0x380b;


    err = cmd_wait(0x6ea, RCA, 0xfff);
    if (err != RT_EOK)
    {
        rt_set_errno(err);
        return err;
    }

    err = cmd_wait(0xca, 0x2, 0xfff);
    if (err != RT_EOK)
    {
        rt_set_errno(err);
        return err;
    }

    err = cmd_response(0x30e, address, 0X3, 0x0200, 0x1, 0Xfff); //CMD24  1bit mode
    if (err != RT_EOK)
    {
        rt_set_errno(err);
        return err;
    }

    complete = *(RP)SDC_INTERRUPT_STATUS;

    if ((complete | 0xfffffffe) != 0xfffffffe)
    {
        //printf("CRC ERROR");
        complete = *(RP)SDC_INTERRUPT_STATUS;
    }

    while (((*(RP)(DMAC_INTTCSTATUS)) & 0x4) != 0x4)
    {
        delay(10);
#ifdef USE_TIMEOUT
        to--;
        if (!to)
        {
            EOUT("%s TIMEOUT\n", __FUNCTION__);
        }
#endif
    }
#ifdef USE_TIMEOUT
    //DBOUT("%s timeout is %d\n",__FUNCTION__,to);
#endif

    return RT_EOK;
}


/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_err_t rt_sdcard_init(rt_device_t dev)
{
    return 0;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    return 0;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_err_t rt_sdcard_close(rt_device_t dev)
{
    return 0;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    rt_kprintf("cmd = %d\n", cmd);
    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = 512;
        geometry->block_size = 0x200000;
        //if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)
        //  geometry->sector_count = (SDCardInfo.SD_csd.DeviceSize + 1)  * 1024;
        //else
        geometry->sector_count = 0x200000;//SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize;
    }

    return RT_EOK;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_ssize_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint32_t retry = 3;
    rt_uint8_t  status;
    rt_uint32_t index;

    struct dfs_partition *part;

    if (dev == RT_NULL)
    {
        rt_set_errno(-DFS_STATUS_EINVAL);
        return 0;
    }

    part = (struct dfs_partition *)dev->user_data;
    // take the semaphore
    rt_sem_take(part->lock, RT_WAITING_FOREVER);
    while (retry--)
    {
        if (((rt_uint32_t)buffer % 4 != 0) ||
                ((rt_uint32_t)buffer > 0x20080000))
        {
            for (index = 0; index < size; index++)
            {
                status = sd_readblock((part->offset + pos) * SECTOR_SIZE, ptr_sddev->sec_buf);
                if (status != RT_EOK)
                    break;

                rt_memcpy((rt_uint8_t *)buffer + (index * SECTOR_SIZE), ptr_sddev->sec_buf, SECTOR_SIZE);
            }
        }
        else
        {
            for (index = 0; index < size; index++)
            {
                status = sd_readblock((pos) * SECTOR_SIZE, (rt_uint8_t *)buffer + index * SECTOR_SIZE);
                if (status != RT_EOK)
                    break;
            }
        }

    }
    rt_sem_release(part->lock);

    if (status == RT_EOK)
        return size;

    rt_kprintf("read failed: %d, buffer 0x%08x\n", status, buffer);
    return 0;

}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
static rt_ssize_t rt_sdcard_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    int i;
    rt_uint8_t status;
    struct dfs_partition *part;

    if (dev == RT_NULL)
    {
        rt_set_errno(-DFS_STATUS_EINVAL);
        return 0;
    }

    part = (struct dfs_partition *)dev->user_data;

    rt_sem_take(part->lock, RT_WAITING_FOREVER);

    if (((rt_uint32_t)buffer % 4 != 0) ||
            ((rt_uint32_t)buffer > 0x20080000))
    {
        rt_uint32_t index;

        for (index = 0; index < size; index++)
        {
            rt_memcpy(ptr_sddev->sec_buf, ((rt_uint8_t *)buffer + index * SECTOR_SIZE), SECTOR_SIZE);
            status = sd_writeblock((part->offset + index + pos) * SECTOR_SIZE, ptr_sddev->sec_buf);
        }
    }
    else
    {

        for (i = 0; i < size; i++)
        {
            status = sd_writeblock((part->offset + i + pos) * SECTOR_SIZE,
                                   (rt_uint8_t *)((rt_uint8_t *)buffer + i * SECTOR_SIZE));
            if (status != RT_EOK) break;
        }
    }

    rt_sem_release(part->lock);

    if (status == RT_EOK)
        return size;

    rt_kprintf("read failed: %d, buffer 0x%08x\n", status, buffer);
    return 0;
}


rt_err_t rt_hw_sdcard_exit()
{
    if (ptr_sddev->device != RT_NULL)
        rt_free(ptr_sddev->device);
    if (ptr_sddev->part != RT_NULL)
        rt_free(ptr_sddev->part);
    if (ptr_sddev != RT_NULL)
        rt_free(ptr_sddev);

    return RT_EOK;
}

/**
 * This function will init sd card
 *
 * @param void
 */
rt_err_t rt_hw_sdcard_init()
{
    /*For test*/
    rt_err_t err;
    rt_int32_t i;

    char dname[4];
    char sname[8];

    /*Initialize structure*/

    ptr_sddev = (struct sd_device *)rt_malloc(sizeof(struct sd_device));
    if (ptr_sddev == RT_NULL)
    {
        EOUT("Failed to allocate sdcard device structure\n");
        return RT_ENOMEM;
    }

    /*sdcard intialize*/
    err = sd_init();
    if (err != RT_EOK)
        goto FAIL2;

    /*set sector buffer*/
    ptr_sddev->sec_buf = gsec_buf;
    ptr_sddev->buf_size = SECTOR_SIZE;
    ptr_sddev->sdc = (struct sd_c *)SD_BASE;

    //DBOUT("allocate partition sector buffer OK!");

    err = sd_readblock(0, ptr_sddev->sec_buf);
    if (err != RT_EOK)
    {
        EOUT("read first block error\n");
        goto FAIL2;
    }

    /*sdcard driver initialize*/
    ptr_sddev->part = (struct dfs_partition *)rt_malloc(4 * sizeof(struct dfs_partition));
    if (ptr_sddev->part == RT_NULL)
    {
        EOUT("allocate partition failed\n");
        err =  RT_ENOMEM;
        goto FAIL2;
    }

    /*alloc device buffer*/
    ptr_sddev->device = (struct rt_device *)rt_malloc(4 * sizeof(struct rt_device));
    if (ptr_sddev->device == RT_NULL)
    {
        EOUT("allocate device failed\n");
        err = RT_ENOMEM;
        goto FAIL1;
    }

    ptr_sddev->part_num = 0;

    err = sd_readblock(0, ptr_sddev->sec_buf);

    if (err != RT_EOK)
    {
        EOUT("Read block 0 to initialize ERROR\n");
        goto FAIL1;
    }

    for (i = 0; i < 4; i++)
    {
        /* get the first partition */
        err = dfs_filesystem_get_partition(&(ptr_sddev->part[i]), ptr_sddev->sec_buf, i);
        if (err == RT_EOK)
        {
            rt_snprintf(dname, 4, "sd%d",  i);
            rt_snprintf(sname, 8, "sem_sd%d",  i);
            ptr_sddev->part[i].lock = rt_sem_create(sname, 1, RT_IPC_FLAG_FIFO);

            /* register sdcard device */
            ptr_sddev->device[i].init = rt_sdcard_init;
            ptr_sddev->device[i].open = rt_sdcard_open;
            ptr_sddev->device[i].close = rt_sdcard_close;
            ptr_sddev->device[i].read = rt_sdcard_read;
            ptr_sddev->device[i].write = rt_sdcard_write;
            ptr_sddev->device[i].control = rt_sdcard_control;
            ptr_sddev->device[i].user_data = &ptr_sddev->part[i];

            err = rt_device_register(&ptr_sddev->device[i], dname,
                                     RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

            if (err == RT_EOK)
                ptr_sddev->part_num++;
        }
        else
        {
            if (i == 0)
            {
                /* there is no partition table */
                ptr_sddev->part[0].offset = 0;
                ptr_sddev->part[0].size   = 0;
                ptr_sddev->part[0].lock = rt_sem_create("sem_sd0", 1, RT_IPC_FLAG_FIFO);

                /* register sdcard device */
                ptr_sddev->device[0].init = rt_sdcard_init;
                ptr_sddev->device[0].open = rt_sdcard_open;
                ptr_sddev->device[0].close = rt_sdcard_close;
                ptr_sddev->device[0].read = rt_sdcard_read;
                ptr_sddev->device[0].write = rt_sdcard_write;
                ptr_sddev->device[0].control = rt_sdcard_control;
                ptr_sddev->device[0].user_data = &ptr_sddev->part[0];

                err = rt_device_register(&ptr_sddev->device[0], "sd0",
                                         RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

                if (err == RT_EOK)
                    ptr_sddev->part_num++;

                break;
            }
        }
    }

    if (ptr_sddev->part_num == 0)
        goto FAIL0;

    return err;

FAIL0:
    rt_free(ptr_sddev->device);
    ptr_sddev->device = RT_NULL;

FAIL1:
    rt_free(ptr_sddev->part);
    ptr_sddev->part = RT_NULL;

FAIL2:
    rt_free(ptr_sddev);
    ptr_sddev = RT_NULL;

    return err;
}

#endif
