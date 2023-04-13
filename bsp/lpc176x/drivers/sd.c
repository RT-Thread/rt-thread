/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include <dfs_fs.h>

#include "spi.h"
#include "sd.h"

/* 512 bytes for each sector */
#define SD_SECTOR_SIZE  512

/* token for write operation */
#define TOKEN_SINGLE_BLOCK  0xFE
#define TOKEN_MULTI_BLOCK   0xFC
#define TOKEN_STOP_TRAN     0xFD

/* Local variables */
static uint8_t CardType;
static SDCFG SDCfg;
static struct rt_device sdcard_device;
static struct dfs_partition part;

/* Local Function Prototypes */
static bool     LPC17xx_SD_Init(void);
static uint8_t  LPC17xx_SD_SendCmd(uint8_t cmd, uint32_t arg);
static bool     LPC17xx_SD_ReadSector(uint32_t sector, uint8_t *buff, uint32_t count);
static bool     LPC17xx_SD_ReadDataBlock(uint8_t *buff,    uint32_t cnt);
static bool     LPC17xx_SD_WriteSector(uint32_t sector, const uint8_t *buff, uint32_t count);
static bool     LPC17xx_SD_WriteDataBlock(const uint8_t *buff, uint8_t token);
static bool     LPC17xx_SD_ReadCfg(SDCFG *cfg);
static bool     LPC17xx_SD_WaitForReady(void);

/* wait until the card is not busy */
static bool LPC17xx_SD_WaitForReady(void)
{
    uint8_t res;
    /* timeout should be large enough to make sure the write operaion can be completed. */
    uint32_t timeout = 400000;

    LPC17xx_SPI_SendByte(0xFF);
    do
    {
        res = LPC17xx_SPI_RecvByte();
    }
    while ((res != 0xFF) && timeout--);

    return (res == 0xFF ? true : false);
}

/* Initialize SD/MMC card. */
static bool LPC17xx_SD_Init(void)
{
    uint32_t i, timeout;
    uint8_t cmd, ct, ocr[4];
    bool ret = false;

    /* Initialize SPI interface and enable Flash Card SPI mode. */
    LPC17xx_SPI_Init();

    /* At least 74 clock cycles are required prior to starting bus communication */
    for (i = 0; i < 80; i++)       /* 80 dummy clocks */
    {
        LPC17xx_SPI_SendByte(0xFF);
    }

    ct = CT_NONE;
    if (LPC17xx_SD_SendCmd(GO_IDLE_STATE, 0) == 0x1)
    {
        timeout = 50000;
        if (LPC17xx_SD_SendCmd(CMD8, 0x1AA) == 1)   /* SDHC */
        {
            /* Get trailing return value of R7 resp */
            for (i = 0; i < 4; i++) ocr[i] = LPC17xx_SPI_RecvByte();
            if (ocr[2] == 0x01 && ocr[3] == 0xAA)   /* The card can work at vdd range of 2.7-3.6V */
            {
                /* Wait for leaving idle state (ACMD41 with HCS bit) */
                while (timeout-- && LPC17xx_SD_SendCmd(SD_SEND_OP_COND, 1UL << 30));
                /* Check CCS bit in the OCR */
                if (timeout && LPC17xx_SD_SendCmd(READ_OCR, 0) == 0)
                {
                    for (i = 0; i < 4; i++) ocr[i] = LPC17xx_SPI_RecvByte();
                    ct = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;
                }
            }
            else      /* SDSC or MMC */
            {
                if (LPC17xx_SD_SendCmd(SD_SEND_OP_COND, 0) <= 1)
                {
                    ct = CT_SD1;
                    cmd = SD_SEND_OP_COND; /* SDSC */
                }
                else
                {
                    ct = CT_MMC;
                    cmd = SEND_OP_COND;    /* MMC */
                }
                /* Wait for leaving idle state */
                while (timeout-- && LPC17xx_SD_SendCmd(cmd, 0));
                /* Set R/W block length to 512 */
                if (!timeout || LPC17xx_SD_SendCmd(SET_BLOCKLEN, SD_SECTOR_SIZE) != 0)
                    ct = CT_NONE;
            }
        }
        else    /* SDSC or MMC */
        {
            if (LPC17xx_SD_SendCmd(SD_SEND_OP_COND, 0) <= 1)
            {
                ct = CT_SD1;
                cmd = SD_SEND_OP_COND; /* SDSC */
            }
            else
            {
                ct = CT_MMC;
                cmd = SEND_OP_COND;    /* MMC */
            }
            /* Wait for leaving idle state */
            while (timeout-- && LPC17xx_SD_SendCmd(cmd, 0));
            /* Set R/W block length to 512 */
            if (!timeout || LPC17xx_SD_SendCmd(SET_BLOCKLEN, SD_SECTOR_SIZE) != 0)
                ct = CT_NONE;
        }
    }
    CardType = ct;
    LPC17xx_SPI_Release();

    if (ct)             /* Initialization succeeded */
    {
        ret = true;
        if (ct == CT_MMC)
        {
            LPC17xx_SPI_SetSpeed(SPI_SPEED_20MHz);
        }
        else
        {
            LPC17xx_SPI_SetSpeed(SPI_SPEED_20MHz);
        }
    }
    else                /* Initialization failed */
    {
        LPC17xx_SPI_Select();
        LPC17xx_SD_WaitForReady();
        LPC17xx_SPI_DeInit();
    }

    return ret;
}

/*****************************************************************************
    Send a Command to Flash card and get a Response
    cmd:  cmd index
    arg: argument for the cmd
    return the received response of the command
*****************************************************************************/
static uint8_t LPC17xx_SD_SendCmd(uint8_t cmd, uint32_t arg)
{
    uint32_t r1, n;

    if (cmd & 0x80)     /* ACMD<n> is the command sequence of CMD55-CMD<n> */
    {
        cmd &= 0x7F;
        r1 = LPC17xx_SD_SendCmd(APP_CMD, 0);   /* CMD55 */
        if (r1 > 1) return r1; /* cmd send failed */
    }

    /* Select the card and wait for ready */
    LPC17xx_SPI_DeSelect();
    LPC17xx_SPI_Select();
    if (LPC17xx_SD_WaitForReady() == false) return 0xFF;

    LPC17xx_SPI_SendByte(0xFF);      /* prepare 8 clocks */
    LPC17xx_SPI_SendByte(cmd);
    LPC17xx_SPI_SendByte(arg >> 24);
    LPC17xx_SPI_SendByte(arg >> 16);
    LPC17xx_SPI_SendByte(arg >> 8);
    LPC17xx_SPI_SendByte(arg);
    /* Checksum, should only be valid for the first command.CMD0 */
    n = 0x01;                           /* Dummy CRC + Stop */
    if (cmd == GO_IDLE_STATE) n = 0x95;         /* Valid CRC for CMD0(0) */
    if (cmd == CMD8) n = 0x87;          /* Valid CRC for CMD8(0x1AA) */
    LPC17xx_SPI_SendByte(n);

    if (cmd == STOP_TRAN) LPC17xx_SPI_RecvByte();       /* Skip a stuff byte when stop reading */

    n = 10;     /* Wait for a valid response in timeout of 10 attempts */
    do
    {
        r1 = LPC17xx_SPI_RecvByte();
    }
    while ((r1 & 0x80) && --n);

    return (r1);        /* Return with the response value */
}

/*****************************************************************************
    Read "count" Sector(s) starting from sector index "sector",
    buff <- [sector, sector+1, ... sector+count-1]
    if success, return true, otherwise return false
*****************************************************************************/
static bool LPC17xx_SD_ReadSector(uint32_t sector, uint8_t *buff, uint32_t count)
{
    /* Convert to byte address if needed */
    if (!(CardType & CT_BLOCK)) sector *= SD_SECTOR_SIZE;

    if (count == 1)     /* Single block read */
    {
        if ((LPC17xx_SD_SendCmd(READ_BLOCK, sector) == 0)
                && LPC17xx_SD_ReadDataBlock(buff, SD_SECTOR_SIZE))
            count = 0;
    }
    else                    /* Multiple block read */
    {
        if (LPC17xx_SD_SendCmd(READ_MULT_BLOCK, sector) == 0)
        {
            do
            {
                if (!LPC17xx_SD_ReadDataBlock(buff, SD_SECTOR_SIZE)) break;
                buff += SD_SECTOR_SIZE;
            }
            while (--count);
            LPC17xx_SD_SendCmd(STOP_TRAN, 0);   /* STOP_TRANSMISSION */
        }
    }
    LPC17xx_SPI_Release();

    return count ? false : true;
}

/*****************************************************************************
    read specified number of data to specified buffer.
    buff:  Data buffer to store received data
    cnt:   Byte count (must be multiple of 4, normally 512)
*****************************************************************************/
static bool LPC17xx_SD_ReadDataBlock(uint8_t *buff,    uint32_t cnt)
{
    uint8_t token;
    uint32_t timeout;

    timeout = 20000;
    do                              /* Wait for data packet in timeout of 100ms */
    {
        token = LPC17xx_SPI_RecvByte();
    }
    while ((token == 0xFF) && timeout--);
    if (token != 0xFE) return false; /* If not valid data token, return with error */

#if USE_FIFO
    LPC17xx_SPI_RecvBlock_FIFO(buff, cnt);
#else
    do      /* Receive the data block into buffer */
    {
        *buff++ = LPC17xx_SPI_RecvByte();
        *buff++ = LPC17xx_SPI_RecvByte();
        *buff++ = LPC17xx_SPI_RecvByte();
        *buff++ = LPC17xx_SPI_RecvByte();
    }
    while (cnt -= 4);
#endif /* USE_FIFO */
    LPC17xx_SPI_RecvByte();                         /* Discard CRC */
    LPC17xx_SPI_RecvByte();

    return true;                    /* Return with success */
}

/*****************************************************************************
    Write "count" Sector(s) starting from sector index "sector",
    buff -> [sector, sector+1, ... sector+count-1]
    if success, return true, otherwise return false
*****************************************************************************/
static bool LPC17xx_SD_WriteSector(uint32_t sector, const uint8_t *buff, uint32_t count)
{
    if (!(CardType & CT_BLOCK)) sector *= 512;  /* Convert to byte address if needed */

    if (count == 1)     /* Single block write */
    {
        if ((LPC17xx_SD_SendCmd(WRITE_BLOCK, sector) == 0)
                && LPC17xx_SD_WriteDataBlock(buff, TOKEN_SINGLE_BLOCK))
            count = 0;
    }
    else                    /* Multiple block write */
    {
        if (CardType & CT_SDC) LPC17xx_SD_SendCmd(SET_WR_BLK_ERASE_COUNT, count);
        if (LPC17xx_SD_SendCmd(WRITE_MULT_BLOCK, sector) == 0)
        {
            do
            {
                if (!LPC17xx_SD_WriteDataBlock(buff, TOKEN_MULTI_BLOCK)) break;
                buff += 512;
            }
            while (--count);
#if 1
            if (!LPC17xx_SD_WriteDataBlock(0, TOKEN_STOP_TRAN)) /* STOP_TRAN token */
                count = 1;
#else
            LPC17xx_SPI_SendByte(TOKEN_STOP_TRAN);
#endif
        }
    }
    LPC17xx_SPI_Release();
    return count ? false : true;
}

/*****************************************************************************
    Write 512 bytes
    buffer: 512 byte data block to be transmitted
    token:  0xFE -> single block
            0xFC -> multi block
            0xFD -> Stop
*****************************************************************************/
static bool LPC17xx_SD_WriteDataBlock(const uint8_t *buff, uint8_t token)
{
    uint8_t resp, i;

    i = i; // avoid warning

    LPC17xx_SPI_SendByte(token);        /* send data token first*/

    if (token != TOKEN_STOP_TRAN)
    {
#if USE_FIFO
        LPC17xx_SPI_SendBlock_FIFO(buff);
#else
        /* Send data. */
        for (i = 512 / 4; i ; i--)
        {
            LPC17xx_SPI_SendByte(*buff++);
            LPC17xx_SPI_SendByte(*buff++);
            LPC17xx_SPI_SendByte(*buff++);
            LPC17xx_SPI_SendByte(*buff++);
        }
#endif /* USE_FIFO */
        LPC17xx_SPI_SendByte(0xFF);                 /* 16-bit CRC (Dummy) */
        LPC17xx_SPI_SendByte(0xFF);

        resp = LPC17xx_SPI_RecvByte();              /* Receive data response */
        if ((resp & 0x1F) != 0x05)      /* If not accepted, return with error */
            return false;

        if (LPC17xx_SD_WaitForReady() == false)   /* Wait while Flash Card is busy. */
            return false;
    }

    return true;
}

/* Read MMC/SD Card device configuration. */
static bool LPC17xx_SD_ReadCfg(SDCFG *cfg)
{
    uint8_t i;
    uint16_t csize;
    uint8_t n, csd[16];
    bool retv = false;

    /* Read the OCR - Operations Condition Register. */
    if (LPC17xx_SD_SendCmd(READ_OCR, 0) != 0x00) goto x;
    for (i = 0; i < 4; i++) cfg->ocr[i] = LPC17xx_SPI_RecvByte();

    /* Read the CID - Card Identification. */
    if ((LPC17xx_SD_SendCmd(SEND_CID, 0) != 0x00) ||
            (LPC17xx_SD_ReadDataBlock(cfg->cid, 16) == false))
        goto x;

    /* Read the CSD - Card Specific Data. */
    if ((LPC17xx_SD_SendCmd(SEND_CSD, 0) != 0x00) ||
            (LPC17xx_SD_ReadDataBlock(cfg->csd, 16) == false))
        goto x;

    cfg -> sectorsize = SD_SECTOR_SIZE;

    /* Get number of sectors on the disk (DWORD) */
    if ((cfg->csd[0] >> 6) == 1)    /* SDC ver 2.00 */
    {
        csize = cfg->csd[9] + ((uint16_t)cfg->csd[8] << 8) + 1;
        cfg -> sectorcnt = (uint32_t)csize << 10;
    }
    else                        /* SDC ver 1.XX or MMC*/
    {
        n = (cfg->csd[5] & 15) + ((cfg->csd[10] & 128) >> 7) + ((cfg->csd[9] & 3) << 1) + 2;  // 19
        csize = (cfg->csd[8] >> 6) + ((uint16_t)cfg->csd[7] << 2) + ((uint16_t)(cfg->csd[6] & 3) << 10) + 1; // 3752
        cfg -> sectorcnt = (uint32_t)csize << (n - 9); // 3842048
    }

    cfg->size = cfg -> sectorcnt * cfg -> sectorsize; // 512*3842048=1967128576Byte (1.83GB)

    /* Get erase block size in unit of sector (DWORD) */
    if (CardType & CT_SD2)              /* SDC ver 2.00 */
    {
        if (LPC17xx_SD_SendCmd(SD_STATUS /*ACMD13*/, 0) == 0)       /* Read SD status */
        {
            LPC17xx_SPI_RecvByte();
            if (LPC17xx_SD_ReadDataBlock(csd, 16))                  /* Read partial block */
            {
                for (n = 64 - 16; n; n--) LPC17xx_SPI_RecvByte();   /* Purge trailing data */
                cfg->blocksize = 16UL << (csd[10] >> 4);
                retv = true;
            }
        }
    }
    else                        /* SDC ver 1.XX or MMC */
    {
        if ((LPC17xx_SD_SendCmd(SEND_CSD, 0) == 0) && LPC17xx_SD_ReadDataBlock(csd, 16))    /* Read CSD */
        {
            if (CardType & CT_SD1)              /* SDC ver 1.XX */
            {
                cfg->blocksize = (((csd[10] & 63) << 1) + ((uint16_t)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
            }
            else                        /* MMC */
            {
                // cfg->blocksize = ((uint16_t)((buf[10] & 124) >> 2) + 1) * (((buf[11] & 3) << 3) + ((buf[11] & 224) >> 5) + 1);
                cfg->blocksize = ((uint16_t)((cfg->csd[10] & 124) >> 2) + 1) * (((cfg->csd[10] & 3) << 3) + ((cfg->csd[11] & 224) >> 5) + 1);
            }
            retv = true;
        }
    }

x:
    LPC17xx_SPI_Release();
    return (retv);
}

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

static rt_ssize_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    bool status;

    status = LPC17xx_SD_ReadSector(part.offset + pos, buffer, size);

    if (status == true) return size;

    rt_kprintf("read failed: %d, pos 0x%08x, size %d\n", status, pos, size);
    return 0;
}

static rt_ssize_t rt_sdcard_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    bool status;

    status = LPC17xx_SD_WriteSector(part.offset + pos, buffer, size);

    if (status == true) return size;

    rt_kprintf("write failed: %d, pos 0x%08x, size %d\n", status, pos, size);
    return 0;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;

        if (geometry == RT_NULL) return -RT_ERROR;
        if (dev->user_data == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = ((SDCFG *)dev->user_data)->sectorsize;
        geometry->block_size = ((SDCFG *)dev->user_data)->blocksize;
        geometry->sector_count = ((SDCFG *)dev->user_data)->sectorcnt;
    }

    return RT_EOK;
}

void rt_hw_sdcard_init()
{
    if (LPC17xx_SD_Init() && LPC17xx_SD_ReadCfg(&SDCfg))
    {
        bool status;
        rt_uint8_t *sector;

        /* get the first sector to read partition table */
        sector = (rt_uint8_t *) rt_malloc(512);
        if (sector == RT_NULL)
        {
            rt_kprintf("allocate partition sector buffer failed\n");
            return;
        }

        status = LPC17xx_SD_ReadSector(0, sector, 1);
        if (status == true)
        {
            /* get the first partition */
            if (dfs_filesystem_get_partition(&part, sector, 0) != 0)
            {
                /* there is no partition */
                part.offset = 0;
                part.size   = 0;
            }
        }
        else
        {
            /* there is no partition table */
            part.offset = 0;
            part.size   = 0;
        }

        /* release sector buffer */
        rt_free(sector);

        /* register sdcard device */
        sdcard_device.type  = RT_Device_Class_Block;
        sdcard_device.init  = rt_sdcard_init;
        sdcard_device.open  = rt_sdcard_open;
        sdcard_device.close = rt_sdcard_close;
        sdcard_device.read  = rt_sdcard_read;
        sdcard_device.write = rt_sdcard_write;
        sdcard_device.control = rt_sdcard_control;

        /* no private */
        sdcard_device.user_data = &SDCfg;

        rt_device_register(&sdcard_device, "sd0",
                           RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

        return;
    }

    rt_kprintf("sdcard init failed\n");
}
