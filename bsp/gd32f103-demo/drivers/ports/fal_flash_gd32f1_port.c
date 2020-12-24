#include <gd32f10x.h>
#include <drv_flash.h>
#include <fal.h>

const struct fal_flash_dev gd32f1_onchip_flash;

static int init(void)
{
    /* do nothing now */
	return 1;
}

static int read(long offset, uint8_t *buf, size_t size)
{
    return gd32_flash_read(gd32f1_onchip_flash.addr + offset, buf, size);
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    return gd32_flash_write(gd32f1_onchip_flash.addr + offset, buf, size);
}

static int erase(long offset, size_t size)
{
    return gd32_flash_erase(gd32f1_onchip_flash.addr + offset, size);
}

const struct fal_flash_dev gd32f1_onchip_flash =
{
    .name       = "gd32_onchip",
    .addr       = FLASH_BASE,
    .len        = 256*1024,
    .blk_size   = 8*8,
    .ops        = {init, read, write, erase},
    .write_gran = 32
};

