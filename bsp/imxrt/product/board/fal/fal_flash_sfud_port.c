/*****************************************************************************
* File Name      : fal_cfg.c
* Author         : Inhand Embedded Team
* Description    :
* Copyright      : InHand Networks Co., Ltd.
* Website        : https://www.inhand.com.cn
******************************************************************************
* modification history :
* liliang created on 2019-11-06 14:49:04
* weiyf   modify  on 2020-06-01 解决ASSERT
******************************************************************************/
#include <rtthread.h>

#if 1//defined(PKG_USING_FAL)
#include <fal.h>
#endif
// #if defined(BSP_USING_SPI_FLASH) && defined(RT_USING_SFUD)
// #include <fal_cfg.h>
// #endif
#if 1//defined(RT_USING_SFUD)
    #include <sfud.h>
    #include <spi_flash_sfud.h>
#endif
//#define SPI_FLASH_DEV_NAME MX25L4006
/******************************************************************************/
#if 1//defined(BSP_USING_SPI_FLASH) && defined(RT_USING_SFUD)

static int init(void);
static int read(long offset, uint8_t *buf, size_t size);
static int write(long offset, const uint8_t *buf, size_t size);
static int erase(long offset, size_t size);

static sfud_flash_t sfud_dev = RT_NULL;
struct fal_flash_dev spi_flash = {SPI_FLASH_DEV_NAME, 0, 512 * 1024, 4096,     \
                                {init, read, write, erase},1};

static int init(void)
{
    sfud_dev = rt_sfud_flash_find_by_dev_name(SPI_FLASH_DEV_NAME);
    if(sfud_dev == RT_NULL)
    {
        log_e("Can't find spi flash \"%s\"", SPI_FLASH_DEV_NAME);
        return -RT_ERROR;
    }
    /* update the flash chip information */
    spi_flash.blk_size  = sfud_dev->chip.erase_gran;
    spi_flash.len       = sfud_dev->chip.capacity;
    //log_i("[fal info debug] spi_flash.len = %d", spi_flash.len);
	return RT_EOK;
}

static int read(long offset, uint8_t *buf, size_t size)
{
    //RT_ASSERT(buf != RT_NULL);
    if(buf == RT_NULL)
    {
        return -RT_ERROR;
    }
    //RT_ASSERT(sfud_dev != RT_NULL);
    if(sfud_dev == RT_NULL)
    {
        return -RT_ERROR;
    }
    sfud_read(sfud_dev, spi_flash.addr + offset, size, buf);
    return size;
}
static int write(long offset, const uint8_t *buf, size_t size)
{
    //RT_ASSERT(buf != RT_NULL);
    if(buf == RT_NULL)
    {
        return -RT_ERROR;
    }
    //RT_ASSERT(sfud_dev != RT_NULL);
    if(sfud_dev == RT_NULL)
    {
        return -RT_ERROR;
    }
    if (sfud_write(sfud_dev, spi_flash.addr + offset, size, buf) != SFUD_SUCCESS)
    {
        return -RT_ERROR;
    }
    return size;
}
static int erase(long offset, size_t size)
{
    //RT_ASSERT(sfud_dev != RT_NULL);
    if(sfud_dev == RT_NULL)
    {
        return -RT_ERROR;
    }
    if (sfud_erase(sfud_dev, spi_flash.addr + offset, size) != SFUD_SUCCESS)
    {
        return -RT_ERROR;
    }

    return size;
}

#endif /* defined(BSP_USING_SPI_FLASH) && defined(RT_USING_SFUD) */
