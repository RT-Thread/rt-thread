#include <rtthread.h>

#if defined(BSP_USING_OSPI_FLASH)

#include <stdint.h>
#include <string.h>

#include "fal_cfg.h"
#include <fal.h>
#include "hal_data.h"
#include "bsp_sflash_map_ra6w1.h"

static rt_bool_t s_ospi_flash_opened;

static int ra6w1_ospi_flash_open(void)
{
    fsp_err_t err;

    if (s_ospi_flash_opened)
    {
        return RT_EOK;
    }

    err = R_OSPI_W_Open((spi_flash_ctrl_t *)&g_ospi_flash_ctrl,
                        &g_ospi_flash_cfg);
    if (err != FSP_SUCCESS)
    {
        return -RT_ERROR;
    }

    s_ospi_flash_opened = RT_TRUE;
    return RT_EOK;
}

static int ra6w1_ospi_flash_init(void)
{
    return ra6w1_ospi_flash_open();
}

static int ra6w1_ospi_flash_read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    rt_memcpy((void *) buf, (void *) ((uint32_t)offset | OSPI_W_AUTOMODE_BASE_ADD), size);
    return (int)size;
}

static int ra6w1_ospi_flash_write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    uint32_t addr     = (uint32_t)offset;
    uint32_t remaining = (uint32_t)size;
    uint32_t buf_offs  = 0;
    uint32_t write_len;
    fsp_err_t err;

    if (ra6w1_ospi_flash_open() != RT_EOK)
    {
        return -RT_ERROR;
    }

    while (remaining > 0)
    {
        write_len = (remaining > FLASH_SECTOR_SIZE) ? FLASH_SECTOR_SIZE : remaining;

        /* Stash tail if writing less than a full sector */
        uint8_t *stash = RT_NULL;
        uint32_t stash_len = 0;

        if (write_len < FLASH_SECTOR_SIZE)
        {
            stash_len = FLASH_SECTOR_SIZE - write_len;
            stash = rt_malloc(stash_len);
            if (stash == RT_NULL)
                return -RT_ENOMEM;

            rt_memcpy(stash,
                      (const void *)((addr + write_len) | OSPI_W_AUTOMODE_BASE_ADD),
                      stash_len);
        }

        err = R_OSPI_W_Erase((spi_flash_ctrl_t *)&g_ospi_flash_ctrl,
                             (uint8_t *)(uintptr_t)addr,
                             FLASH_SECTOR_SIZE);
        if (err != FSP_SUCCESS)
        {
            if (stash) rt_free(stash);
            return -RT_ERROR;
        }

        err = R_OSPI_W_Write((spi_flash_ctrl_t *)&g_ospi_flash_ctrl,
                             buf + buf_offs,
                             (uint8_t *)(uintptr_t)addr,
                             write_len);
        if (err != FSP_SUCCESS)
        {
            if (stash) rt_free(stash);
            return -RT_ERROR;
        }

        addr     += write_len;
        buf_offs += write_len;

        /* Restore stashed tail */
        if (stash_len > 0)
        {
            err = R_OSPI_W_Write((spi_flash_ctrl_t *)&g_ospi_flash_ctrl,
                                 stash,
                                 (uint8_t *)(uintptr_t)addr,
                                 stash_len);
            rt_free(stash);

            if (err != FSP_SUCCESS)
                return -RT_ERROR;
        }

        remaining -= write_len;
    }

    return (int)size;
}

static int ra6w1_ospi_flash_erase(long offset, rt_size_t size)
{
    uint32_t addr     = (uint32_t)offset;
    uint32_t remaining = (uint32_t)size;
    uint32_t erase_len;
    fsp_err_t err;

    if (ra6w1_ospi_flash_open() != RT_EOK)
    {
        return -RT_ERROR;
    }

    while (remaining > 0)
    {
        erase_len = (remaining > FLASH_SECTOR_SIZE) ? FLASH_SECTOR_SIZE : remaining;

        /* Stash tail if erasing less than a full sector */
        uint8_t *stash = RT_NULL;
        uint32_t stash_len = 0;

        if (erase_len < FLASH_SECTOR_SIZE)
        {
            stash_len = FLASH_SECTOR_SIZE - erase_len;
            stash = rt_malloc(stash_len);
            if (stash == RT_NULL)
                return -RT_ENOMEM;

            rt_memcpy(stash,
                      (const void *)((addr + erase_len) | OSPI_W_AUTOMODE_BASE_ADD),
                      stash_len);
        }

        err = R_OSPI_W_Erase((spi_flash_ctrl_t *)&g_ospi_flash_ctrl,
                             (uint8_t *)(uintptr_t)addr,
                             FLASH_SECTOR_SIZE);
        if (err != FSP_SUCCESS)
        {
            if (stash) rt_free(stash);
            return -RT_ERROR;
        }

        addr += erase_len;

        /* Restore stashed tail */
        if (stash_len > 0)
        {
            err = R_OSPI_W_Write((spi_flash_ctrl_t *)&g_ospi_flash_ctrl,
                                 stash,
                                 (uint8_t *)(uintptr_t)addr,
                                 stash_len);
            rt_free(stash);

            if (err != FSP_SUCCESS)
                return -RT_ERROR;
        }

        remaining -= erase_len;
    }

    return (int)size;
}

const struct fal_flash_dev ra6w1_ospi_flash  =
{
    .name       = RA6W1_OSPI_FLASH_DEV_NAME,
    .addr       = SF_BASE_ADDR,
    .len        = MEMORY_QSPIF_SIZE,
    .blk_size   = FLASH_SECTOR_SIZE,
    .ops        =
    {
        .init  = ra6w1_ospi_flash_init,
        .read  = ra6w1_ospi_flash_read,
        .write = ra6w1_ospi_flash_write,
        .erase = ra6w1_ospi_flash_erase,
    },
    .write_gran = 1,
    .blocks     =
    {
        {
            .size  = FLASH_SECTOR_SIZE,
            .count = MEMORY_QSPIF_SIZE / FLASH_SECTOR_SIZE,
        },
    },
};

static int ra6w1_fal_auto_init(void)
{
    fal_init();

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(ra6w1_fal_auto_init);

#endif /* RT_USING_FAL && BSP_USING_OSPI_FLASH */
