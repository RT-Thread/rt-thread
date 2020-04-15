/*
 * File      : drv_sfc_gd25qxx_mtd.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê4ÔÂ19ÈÕ     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/mtd_nor.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_gpio.h"
#include "drv_sfc.h"

/* JEDEC Manufacturer's ID */
#define MF_ID           (0xC8)

/* JEDEC Device ID: Memory type and Capacity */
#define MTC_GD25Q128                (0x4018)
#define MTC_GD25Q256                (0x4019)


/* RT-Thread MTD device interface */
static rt_base_t mtd_gd25_read_id(struct rt_mtd_nor_device *device)
{
    struct sfc_flash *flash = (struct sfc_flash *)device;

    return (rt_uint32_t)flash->id;
}

static rt_size_t mtd_gd25_read(struct rt_mtd_nor_device *device, rt_off_t position, rt_uint8_t *data, rt_uint32_t size)
{
    struct sfc_flash *flash = (struct sfc_flash *)device;

    return sfc_norflash_read(flash,position,data,size);
}

static rt_size_t mtd_gd25_write(struct rt_mtd_nor_device *device, rt_off_t position, const rt_uint8_t *data, rt_uint32_t size)
{
    struct sfc_flash *flash = (struct sfc_flash *)device;

    return sfc_norflash_write(flash,position,data,size);
}


static rt_err_t mtd_gd25_erase_block(struct rt_mtd_nor_device *device, rt_off_t offset, rt_uint32_t length)
{
    struct sfc_flash *flash = (struct sfc_flash *)device;

    sfc_norflash_erase_sector(flash,offset);
    return RT_EOK;
}

const static struct rt_mtd_nor_driver_ops mtd_gd25_ops =
{
    mtd_gd25_read_id,
    mtd_gd25_read,
    mtd_gd25_write,
    mtd_gd25_erase_block,
};

#ifdef SFC_USE_QUAD
struct sfc_quad_mode  flash_quad_mode[] =
{
    {
        .RDSR_CMD = CMD_RDSR_1,
        .WRSR_CMD = CMD_WRSR_1,
        .RDSR_DATE = 0x2,//the data is write the spi status register for QE bit
        .RD_DATE_SIZE = 1,
        .WRSR_DATE = 0x2,//this bit should be the flash QUAD mode enable
        .WD_DATE_SIZE = 1,
        .cmd_read = CMD_QUAD_READ,//
        .sfc_mode = TRAN_SPI_QUAD,
    },
    {
        .RDSR_CMD = CMD_RDSR,
        .WRSR_CMD = CMD_WRSR,
        .RDSR_DATE = 0x40,//the data is write the spi status register for QE bit
        .RD_DATE_SIZE = 1,
        .WRSR_DATE = 0x40,//this bit should be the flash QUAD mode enable
        .WD_DATE_SIZE = 1,
        .cmd_read = CMD_QUAD_IO_FAST_READ,
        .sfc_mode = TRAN_SPI_IO_QUAD,
    },
    {
        .RDSR_CMD = CMD_RDSR_1,
        .WRSR_CMD = CMD_WRSR,
        .RDSR_DATE = 0x20,//the data is write the spi status register for QE bit
        .RD_DATE_SIZE = 1,
        .WRSR_DATE = 0x200,//this bit should be the flash QUAD mode enable
        .WD_DATE_SIZE = 2,
        .cmd_read = CMD_QUAD_READ,
        .sfc_mode = TRAN_SPI_QUAD,
    },
    {
        .RDSR_CMD = CMD_RDSR,
        .WRSR_CMD = CMD_WRSR,
        .RDSR_DATE = 0x40,//the data is write the spi status register for QE bit
        .RD_DATE_SIZE = 1,
        .WRSR_DATE = 0x40,//this bit should be the flash QUAD mode enable
        .WD_DATE_SIZE = 1,
        .cmd_read = CMD_QUAD_READ,
        .sfc_mode = TRAN_SPI_QUAD,
    },

};
#endif

static struct sfc_flash _gd25_flash_info =
{
        .name       = "GD25Q128C",
        .id         = 0xc84018,
        .pagesize   = 256,
        .sectorsize = ( 4 * 1024),
        .chipsize   = (16 * 1024 * 1024),
        .erasesize  = ( 4 * 1024),
        .writesize  = 256,
        .addrsize   = DEFAULT_ADDRSIZE,
        .quad_mode  = &flash_quad_mode[0]
};

static char flashIdStr[128];
extern int rt_hw_gd25qxx_mtd_part_init(const char *mtd_name);
int rt_hw_gd25qxx_init(void)
{
    struct sfc_flash   *flash = &_gd25_flash_info;
    int result;
    
    result = sfc_norflash_probe(flash);
    if(result != RT_EOK)
    {
        rt_kprintf("GD25 init Failed..\n");

        return result;
    }

    if((flash->id >> 16) != MF_ID)
    {
        rt_kprintf("Manufacturers ID error!\r\n");
        rt_kprintf("JEDEC Read-ID Data : %06X\r\n", flash->id);
        return -RT_ENOSYS;
    }

    switch (flash->id & 0xFFFF)
    {
        case MTC_GD25Q128:
            flash->name     = "GD25Q128C";
            flash->chipsize = (16 * 1024 * 1024);
            flash->addrsize = 3;
            flash->quad_mode = &flash_quad_mode[0];
        break;
        case MTC_GD25Q256:
            flash->name     = "GD25Q256C";
            flash->chipsize = (32 * 1024 * 1024);
            flash->addrsize = 4;
            flash->quad_mode = &flash_quad_mode[3];
            /* enable 4-byte addressing if the device exceeds 16MiB */
            sfc_norflash_set_addr_width_4byte(flash,1);
        break;
        default:
            rt_kprintf("Memory Capacity error!\r\n");
            return -RT_ENOSYS;
        break;
    }

    //format FLASH UUID...
    {
        int strSize,i;

        strSize  = rt_snprintf(flashIdStr + 0,sizeof(flashIdStr) - 0,"%06X",flash->id);
        for(i=0;i<8;i++)
            strSize += rt_snprintf(flashIdStr + strSize,sizeof(flashIdStr) - strSize,"%02X",flash->uid[i]);
        flashIdStr[strSize] = '\0';
    }

    /* Init device interface ... */
    flash->mtd.block_size   = flash->erasesize;
    flash->mtd.block_start  = 0;
    flash->mtd.block_end    = flash->chipsize / flash->erasesize;
    flash->mtd.ops          = &mtd_gd25_ops;
    rt_mtd_nor_register_device("gd25mtd",&flash->mtd);
    
    rt_hw_gd25qxx_mtd_part_init("gd25mtd");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_gd25qxx_init);
