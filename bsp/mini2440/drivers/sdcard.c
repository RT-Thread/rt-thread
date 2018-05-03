/*
 * File      : sd.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, 2007, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author        Notes
 * 2007-12-02     Yi.Qiu        the first version
 * 2010-01-01     Bernard       Modify for mini2440
 * 2012-12-15     amr168        support SDHC
 * 2017-11-20     kuangdazzidd  add csd cmd support
 */

#include "sdcard.h"
#include "rtdef.h"

extern   rt_uint32_t   PCLK;
volatile rt_uint32_t   rd_cnt;
volatile rt_uint32_t   wt_cnt;
volatile rt_int32_t    RCA;
volatile rt_int32_t    sd_type;

struct sd_csd {
    rt_uint16_t    bsize;
    rt_uint32_t    nblks;
}g_sd_csd;

static void sd_delay(rt_uint32_t ms)
{
    ms *= 7326;
    while(--ms);
}

static int sd_cmd_end(int cmd, int be_resp)
{
    int finish0;

    if (!be_resp)
    {
        finish0 = SDICSTA;

        while ((finish0&0x800) != 0x800)
            finish0 = SDICSTA;

        SDICSTA = finish0;

        return RT_EOK;
    }
    else
    {
        finish0 = SDICSTA;

        while (!(((finish0&0x200)==0x200) | ((finish0&0x400) == 0x400)))
            finish0=SDICSTA;

        if (cmd == 1 || cmd == 41)
        {
            if ((finish0 & 0xf00) != 0xa00)
            {
                SDICSTA = finish0;
                    if ((finish0&0x400) == 0x400)
                        return RT_ERROR;
            }
            SDICSTA = finish0;
        }
        else
        {
            if ((finish0 & 0x1f00) != 0xa00)
            {
                /* rt_kprintf("CMD%d:SDICSTA=0x%x, SDIRSP0=0x%x\n", cmd, SDICSTA, SDIRSP0); */
                SDICSTA = finish0;
                if ((finish0 & 0x400) == 0x400)
                    return RT_ERROR;
            }
            SDICSTA = finish0;
        }
        return RT_EOK;
    }
}

static int sd_data_end(void)
{
    int finish;

    finish = SDIDSTA;

    while (!(((finish & 0x10) == 0x10) | ((finish & 0x20) == 0x20)))
    {
        finish = SDIDSTA;
    }

    if ((finish & 0xfc) != 0x10)
    {
        SDIDSTA = 0xec;

        return RT_ERROR;
    }

    return RT_EOK;
}

static void sd_cmd0(void)
{
    SDICARG = 0x0;
    SDICCON = (1<<8) | 0x40;

    sd_cmd_end(0, 0);
    SDICSTA = 0x800;      /* Clear cmd_end(no rsp) */
}

static int sd_cmd55(void)
{
    SDICARG = RCA << 16;
    SDICCON = (0x1 << 9) | (0x1 << 8) | 0x77;

    if (sd_cmd_end(55, 1) == RT_ERROR)
    {
        /* rt_kprintf("CMD55 error\n"); */
        return RT_ERROR;
    }

    SDICSTA = 0xa00;


    return RT_EOK;
}

static int sd_cmd9(void *p_rsp)
{
SDICARG = RCA << 16;
SDICCON = (1 << 10) | (1 << 9) | (0x1<<8) | (0x40 | 0x09);

sd_cmd_end(9, 1);

    ((rt_uint32_t *)p_rsp)[0] = SDIRSP3;
    ((rt_uint32_t *)p_rsp)[1] = SDIRSP2;
    ((rt_uint32_t *)p_rsp)[2] = SDIRSP1;
    ((rt_uint32_t *)p_rsp)[3] = SDIRSP0;

return RT_EOK;
}

static void sd_sel_desel(char sel_desel)
{
    if (sel_desel)
    {
RECMDS7:
        SDICARG = RCA << 16;
        SDICCON = (0x1 << 9) | (0x1 << 8) | 0x47;
        if (sd_cmd_end(7, 1) == RT_ERROR)
            goto RECMDS7;

        SDICSTA = 0xa00;

        if (SDIRSP0 & 0x1e00 != 0x800)
            goto RECMDS7;
    }
    else
    {
RECMDD7:
        SDICARG = 0 << 16;
        SDICCON = (0x1 << 8) | 0x47;

        if (sd_cmd_end(7, 0) == RT_ERROR)
            goto RECMDD7;
        SDICSTA = 0x800;
    }
}

static void sd_setbus(void)
{
    do
    {
        sd_cmd55();

        SDICARG = 1 << 1; /* 4bit bus */
        SDICCON = (0x1<<9) | (0x1<<8) | 0x46; /* sht_resp, wait_resp, start, CMD55 */
    }while (sd_cmd_end(6, 1) == RT_ERROR);

    SDICSTA=0xa00;      /* Clear cmd_end(with rsp) */
}


static rt_uint32_t bits_str (rt_uint32_t *str, rt_uint32_t start, rt_uint8_t len)
{
    rt_uint32_t  mask;
    rt_uint32_t  index;
    rt_uint8_t   shift;
    rt_uint32_t  value;

    mask  = (int)((len < 32) ? (1 << len) : 0) - 1;
    index = start / 32;
    shift = start & 31;
    value = str[index] >> shift;

    if ((len + shift) > 32) {
        value |= str[index + 1] << (32 - shift);
    }
    value &= mask;
    return value;
}


static int sd_decode_csd (rt_uint32_t  *p_csd)
{
    rt_uint32_t e, m, r;
    rt_uint8_t  structure;

    structure = bits_str(p_csd, 126, 2);

    switch (structure) {
        case 0:
            m = bits_str(p_csd, 99, 4);
            e = bits_str(p_csd, 96, 3);
            g_sd_csd.bsize  = 512;
            m = bits_str(p_csd, 62, 12);
            e = bits_str(p_csd, 47, 3);
            r = bits_str(p_csd, 80, 4);
            g_sd_csd.nblks = ((1 + m) << (e + r - 7));
            break;

        case 1:
            m = bits_str(p_csd, 99, 4);
            e = bits_str(p_csd, 96, 3);
            g_sd_csd.bsize  = 512;
            m = bits_str(p_csd, 48, 22);
            g_sd_csd.nblks = (1 + m) << 10;
            break;

        default:
            return RT_ERROR;
    }
    return RT_EOK;
}


static int sd_send_csd(rt_uint32_t  *p_csd)
{
    int         ret;
    rt_uint32_t rsp[4];

    ret = sd_cmd9((void*)&rsp);

    if (ret != 0) {
        return ret;
    }

    rt_memcpy((void*)p_csd, (void*)rsp, 16);
    return RT_EOK;
}

static int sd_ocr(void)
{
    int i, ver=0;

    /* Negotiate operating condition for SD, it makes card ready state */
    for (i = 0; i < 50; i ++)
    {
        sd_cmd55();

        SDICARG = 0x40ff8000; /* HCS=1, compatible v1.x and v2.0 */
        SDICCON = (0x1<<9) | (0x1<<8) | 0x69;

        /* if using real board, should replace code here. need to modify qemu in near future*/
        /* Check end of ACMD41 */
        if (sd_cmd_end(41, 1) == RT_EOK)
        {
            if (SDIRSP0 == 0x80ff8000)
            {
                ver = 1; /* SD V1.x, CCS=0 */
                break;
            }
            else if (SDIRSP0 == 0xc0ff8000)
            {
                ver = 2; /* SD V2.0, CCS=1 */
                break;
            }
        }

        sd_delay(200);
    }
    SDICSTA = 0xa00;

    return ver;
}

rt_err_t sd_cmd8(void)
{
    SDICARG = 0x000001AA; 
    SDICCON = (0x1<<9) | (0x1<<8) | 0x48; //sht_resp, wait_resp, start
    if (sd_cmd_end(8, 1) == RT_ERROR)
        return RT_ERROR;
    SDICSTA = 0xa00;
    
    if ((SDIRSP0&0x1aa) == 0x1aa)
        return RT_EOK; 
    else 
        return RT_ERROR;
}

static rt_uint8_t sd_init(void)
{
    //-- SD controller & card initialize
    int         i;
    rt_uint32_t csd[4];
    /* Important notice for MMC test condition */
    /* Cmd & Data lines must be enabled by pull up resister */
    SDIPRE    = PCLK / (INICLK) - 1;
    SDICON    = (0<<4) | 1;   // Type A, clk enable
    SDIFSTA   = SDIFSTA | (1<<16);
    SDIBSIZE  = 0x200;       /* 512byte per one block */
    SDIDTIMER = 0x7fffff;     /* timeout count */

    /* Wait 74SDCLK for MMC card */
    for (i = 0; i < 0x1000; i ++);

    sd_cmd0();
    sd_cmd8(); /* Must be use it, Host shall supports high capacity */

    /* Check SD card OCR */
    sd_type = sd_ocr();
    if (sd_type > 0)
    {
        rt_kprintf("In SD ready\n");
    }
    else
    {
        rt_kprintf("Initialize fail\nNo Card assertion\n");

        return RT_ERROR;
    }

RECMD2:
    SDICARG = 0x0;
    SDICCON = (0x1<<10)|(0x1<<9)|(0x1<<8)|0x42; /* lng_resp, wait_resp, start, CMD2 */
    if (sd_cmd_end(2, 1) == RT_ERROR)
        goto RECMD2;

    SDICSTA = 0xa00;    /* Clear cmd_end(with rsp) */

RECMD3:
    SDICARG = 0<<16;    /* CMD3(MMC:Set RCA, SD:Ask RCA-->SBZ) */
    SDICCON = (0x1<<9)|(0x1<<8)|0x43; /* sht_resp, wait_resp, start, CMD3 */
    if (sd_cmd_end(3, 1) == RT_ERROR)
        goto RECMD3;
    SDICSTA=0xa00;  /* Clear cmd_end(with rsp) */

    sd_send_csd(csd);
    sd_decode_csd(csd);

    RCA = (SDIRSP0 & 0xffff0000) >> 16;
    SDIPRE = PCLK / (SDCLK) - 1; /* Normal clock=25MHz */
    if (SDIRSP0 & 0x1e00 != 0x600)
        goto RECMD3;

    sd_sel_desel(1);
    sd_delay(200);
    sd_setbus();

    return RT_EOK;
}

static rt_uint8_t sd_readblock(rt_uint32_t address, rt_uint8_t *buf)
{
    rt_uint32_t status, tmp;

    rd_cnt = 0;
    SDIFSTA = SDIFSTA | (1<<16);

    SDIDCON = (2 << 22) | (1 << 19) | (1 << 17) | (1 << 16) | (1 << 14) | (2 << 12) | (1 << 0);
    SDICARG = address;

RERDCMD:
    SDICCON = (0x1 << 9 ) | (0x1 << 8) | 0x51;
    if (sd_cmd_end(17, 1) == RT_ERROR)
    {
        rt_kprintf("Read CMD Error\n");
        goto RERDCMD;
    }

    SDICSTA = 0xa00;

    while (rd_cnt < 128)
    {
        if ((SDIDSTA & 0x20) == 0x20)
        {
            SDIDSTA = (0x1 << 0x5);
            break;
        }
        status = SDIFSTA;
        if ((status & 0x1000) == 0x1000)
        {
            tmp = SDIDAT;
            rt_memcpy(buf, &tmp, sizeof(rt_uint32_t));
            rd_cnt ++;
            buf += 4;
        }
    }
    if (sd_data_end() == RT_ERROR)
    {
        rt_kprintf("Dat error\n");

        return RT_ERROR;
    }

    SDIDCON = SDIDCON &~ (7<<12);
    SDIFSTA = SDIFSTA & 0x200;
    SDIDSTA = 0x10;

    return RT_EOK;
}

static rt_uint8_t sd_writeblock(rt_uint32_t address, rt_uint8_t *buf)
{
    rt_uint32_t status, tmp;

    wt_cnt = 0;
    SDIFSTA = SDIFSTA | (1 << 16);

    SDIDCON = (2 << 22) | (1 << 20) | (1 << 17) | (1 << 16) | (1 << 14) | (3 << 12) | (1 << 0);
    SDICARG = address;

REWTCMD:
    SDICCON = (0x1 << 9) | (0x1 << 8) |0x58;

    if (sd_cmd_end(24, 1) == RT_ERROR)
        goto REWTCMD;

    SDICSTA = 0xa00;

    while (wt_cnt < 128)
    {
        status = SDIFSTA;
        if ((status & 0x2000) == 0x2000)
        {
            rt_memcpy(&tmp, buf, sizeof(rt_uint32_t));
            SDIDAT = tmp;
            wt_cnt ++;
            buf += 4;
        }
    }
    if (sd_data_end() == RT_ERROR)
    {
        rt_kprintf("Data Error\n");

        return RT_ERROR;
    }
    SDIDCON = SDIDCON &~ (7<<12);
    SDIDSTA = 0x10;

    return RT_EOK;
}

#ifdef RT_USING_DFS
/* RT-Thread Device Driver Interface */
#include <rtthread.h>

#include <dfs_fs.h>

struct rt_device sdcard_device[4];
struct dfs_partition part[4];

static rt_err_t rt_sdcard_init(rt_device_t dev)
{
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

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
struct rt_device_blk_geometry *p_geometry = (struct rt_device_blk_geometry *)args;
p_geometry->block_size = g_sd_csd.bsize;
p_geometry->sector_count = g_sd_csd.nblks;
p_geometry->bytes_per_sector = 512;
    return RT_EOK;
}

static rt_size_t rt_sdcard_read(rt_device_t dev,
                                rt_off_t    pos,
                                void       *buffer,
                                rt_size_t   size)
{
    int i, addr;
    struct dfs_partition *part = (struct dfs_partition *)dev->user_data;

    if (dev == RT_NULL)
    {
        rt_set_errno(-EINVAL);

        return 0;
    }

    /* read all sectors */
    for (i = 0; i < size; i ++)
    {
        rt_sem_take(part->lock, RT_WAITING_FOREVER);
        if (sd_type == 1)
            addr = (part->offset + i + pos)*SECTOR_SIZE;
        else
            addr = (part->offset + i + pos);
        sd_readblock(addr, (rt_uint8_t *)((rt_uint8_t *)buffer + i * SECTOR_SIZE));
        rt_sem_release(part->lock);
    }

    /* the length of reading must align to SECTOR SIZE */
    return size;
}

static rt_size_t rt_sdcard_write(rt_device_t dev,
                                 rt_off_t    pos,
                                 const void *buffer,
                                 rt_size_t   size)
{
    int i, addr;
    struct dfs_partition *part = (struct dfs_partition *)dev->user_data;

    if (dev == RT_NULL)
    {
        rt_set_errno(-EINVAL);

        return 0;
    }

    /* read all sectors */
    for (i = 0; i < size; i++)
    {
        rt_sem_take(part->lock, RT_WAITING_FOREVER);
        if (sd_type == 1)
            addr = (part->offset + i + pos)*SECTOR_SIZE;
        else
            addr = (part->offset + i + pos);
        sd_writeblock(addr, (rt_uint8_t*)((rt_uint8_t*)buffer + i * SECTOR_SIZE));
        rt_sem_release(part->lock);
    }

    /* the length of reading must align to SECTOR SIZE */
    return size;
}

void rt_hw_sdcard_init(void)
{
    rt_uint8_t i, status;
    rt_uint8_t *sector;
    char dname[4];
    char sname[8];

    /* Enable PCLK into SDI Block */
    CLKCON |= 1 << 9;

    /* Setup GPIO as SD and SDCMD, SDDAT[3:0] Pull up En */
    GPEUP  = GPEUP  & (~(0x3f << 5))   | (0x01 << 5);
    GPECON = GPECON & (~(0xfff << 10)) | (0xaaa << 10);

    RCA = 0;

    if (sd_init() == RT_EOK)
    {
        /* get the first sector to read partition table */
        sector = (rt_uint8_t*) rt_malloc (512);
        if (sector == RT_NULL)
        {
            rt_kprintf("allocate partition sector buffer failed\n");

            return;
        }
        status = sd_readblock(0, sector);
        if (status == RT_EOK)
        {
            for (i = 0; i < 4; i ++)
            {
                /* get the first partition */
                status = dfs_filesystem_get_partition(&part[i], sector, i);
                if (status == RT_EOK)
                {
                    rt_snprintf(dname, 4, "sd%d",  i);
                    rt_snprintf(sname, 8, "sem_sd%d",  i);
                    part[i].lock = rt_sem_create(sname, 1, RT_IPC_FLAG_FIFO);

                    /* register sdcard device */
                    sdcard_device[i].type      = RT_Device_Class_Block;
                    sdcard_device[i].init      = rt_sdcard_init;
                    sdcard_device[i].open      = rt_sdcard_open;
                    sdcard_device[i].close     = rt_sdcard_close;
                    sdcard_device[i].read      = rt_sdcard_read;
                    sdcard_device[i].write     = rt_sdcard_write;
                    sdcard_device[i].control   = rt_sdcard_control;
                    sdcard_device[i].user_data = &part[i];

                    rt_device_register(&sdcard_device[i], dname,
                        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);
                }
                else
                {
                    if (i == 0)
                    {
                        /* there is no partition table */
                        part[0].offset = 0;
                        part[0].size   = 0;
                        part[0].lock   = rt_sem_create("sem_sd0", 1, RT_IPC_FLAG_FIFO);

                        /* register sdcard device */
                        sdcard_device[0].type      = RT_Device_Class_Block;
                        sdcard_device[0].init      = rt_sdcard_init;
                        sdcard_device[0].open      = rt_sdcard_open;
                        sdcard_device[0].close     = rt_sdcard_close;
                        sdcard_device[0].read      = rt_sdcard_read;
                        sdcard_device[0].write     = rt_sdcard_write;
                        sdcard_device[0].control   = rt_sdcard_control;
                        sdcard_device[0].user_data = &part[0];

                        rt_device_register(&sdcard_device[0], "sd0",
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

                        break;
                    }
                }
            }
        }
        else
        {
            rt_kprintf("read sdcard first sector failed\n");
        }

        /* release sector buffer */
        rt_free(sector);

        return;
    }
    else
    {
        rt_kprintf("sdcard init failed\n");
    }
}

#endif
