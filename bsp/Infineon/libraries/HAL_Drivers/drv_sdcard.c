/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     vandoul      first
 */

#include <rtthread.h>
#include "cy_gpio.h"
#include "cyhal_gpio.h"
#include "cyhal_sdhc.h"

#ifdef BSP_USING_SDCARD

/*#define DRV_DEBUG*/
#define LOG_TAG             "drv.sdio"
#include <drv_log.h>

#define SDIO_BLOCK_SIZE                         (512)

#if BSP_USING_SDCARD_LED_CTRL_ENANBLE
#define SDCARD_LED_CTRL_ENABLE           true
#else
#define SDCARD_LED_CTRL_ENABLE           false
#endif
#if BSP_USING_SDCARD_EMMC_ENANBLE
#define SDCARD_EMMC_ENABLE           true
#else
#define SDCARD_EMMC_ENABLE           false
#endif

struct _cy_sdio_pin_and_name_config
{
    const char *name;
    cyhal_gpio_t cmd;               /**< The pin connected to the command signal. */
    cyhal_gpio_t clk;               /**< The pin connected to the clock signal. */
    cyhal_gpio_t data0;             /**< The pin connected to the data0 signal. */
    cyhal_gpio_t data1;             /**< The pin connected to the data1 signal. */
    cyhal_gpio_t data2;             /**< The pin connected to the data2 signal. */
    cyhal_gpio_t data3;             /**< The pin connected to the data3 signal. */
    cyhal_gpio_t data4;             /**< The pin connected to the data4 signal; pass NC when unused. */
    cyhal_gpio_t data5;             /**< The pin connected to the data5 signal; pass NC when unused. */
    cyhal_gpio_t data6;             /**< The pin connected to the data6 signal; pass NC when unused. */
    cyhal_gpio_t data7;             /**< The pin connected to the data7 signal; pass NC when unused. */
    cyhal_gpio_t card_detect;       /**< The pin connected to the card detect signal. */
    cyhal_gpio_t io_volt_sel;       /**< The pin connected to the voltage select signal. */
    cyhal_gpio_t card_if_pwr_en;    /**< The pin connected to the card interface power enable signal. */
    cyhal_gpio_t card_mech_write_prot; /**< The pin connected to the write protect signal. */
    cyhal_gpio_t led_ctrl;          /**< The pin connected to the LED control signal. */
    cyhal_gpio_t card_emmc_reset;   /**< The pin connected to the eMMC card reset signal. */
};

static const struct _cy_sdio_pin_and_name_config _sdcard_config =
{
    .name = "sd0",
    .cmd                  = BSP_USING_SDCARD_CMD_PIN,
    .clk                  = BSP_USING_SDCARD_CLK_PIN,
    .data0                = BSP_USING_SDCARD_DAT0_PIN,
    .data1                = BSP_USING_SDCARD_DAT1_PIN,
    .data2                = BSP_USING_SDCARD_DAT2_PIN,
    .data3                = BSP_USING_SDCARD_DAT3_PIN,
    .data4                = BSP_USING_SDCARD_DAT4_PIN,
    .data5                = BSP_USING_SDCARD_DAT5_PIN,
    .data6                = BSP_USING_SDCARD_DAT6_PIN,
    .data7                = BSP_USING_SDCARD_DAT7_PIN,
    .card_detect          = BSP_USING_SDCARD_DETECT_PIN,
    .io_volt_sel          = BSP_USING_SDCARD_IO_VOLT_SEL_PIN,
    .card_if_pwr_en       = BSP_USING_SDCARD_CARD_IF_PWR_EN_PIN,
    .card_mech_write_prot = BSP_USING_SDCARD_CARD_MECH_WRITE_PROT_PIN,
    #if BSP_USING_SDCARD_LED_CTRL_PIN
    .led_ctrl             = BSP_USING_SDCARD_LED_CTRL_PIN,
    #else
    .led_ctrl             = -1,
    #endif
    .card_emmc_reset      = BSP_USING_SDCARD_CARD_EMMC_RESET_PIN,
};

#include <dfs_fs.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_gpt.h>
struct rthw_sdio
{
    struct rt_device parent;
    cyhal_sdhc_t sdhc_obj; /**< Object for use with the SDHC HAL driver. */
    cyhal_sdhc_config_t sdhc_config; /**< Card configuration structure to be passed to the HAL driver. */
    const struct _cy_sdio_pin_config *pins_cfg;
    struct dfs_partition part;
    struct rt_device_blk_geometry geometry;
};
static rt_err_t rt_mmcsd_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_mmcsd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_mmcsd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_mmcsd_control(rt_device_t dev, int cmd, void *args)
{
    struct rthw_sdio *sdio = (struct rthw_sdio *)dev;
    struct dfs_partition *part = &sdio->part;
    struct rt_device_blk_geometry *geometry = &sdio->geometry;
    struct mmcsd_blk_device *blk_dev = (struct mmcsd_blk_device *)dev->user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_BLK_GETGEOME:
        rt_memcpy(args, geometry, sizeof(struct rt_device_blk_geometry));
        break;
    case RT_DEVICE_CTRL_BLK_PARTITION:
        rt_memcpy(args, part, sizeof(struct dfs_partition));
    default:
        break;
    }
    return RT_EOK;
}

static rt_ssize_t rt_mmcsd_read(rt_device_t dev,
                               rt_off_t    pos,
                               void       *buffer,
                               rt_size_t   size)
{
    rt_err_t err = 0;
    void *rd_ptr = (void *)buffer;
    struct rthw_sdio *sdio = (struct rthw_sdio *)dev;
    cyhal_sdhc_t *hw_sdio = &sdio->sdhc_obj;
    off_t offset = sdio->part.offset;

    LOG_D("mmc read: off:%d pos:%d size:%d", offset, pos, size);
    if (dev == RT_NULL)
    {
        rt_set_errno(-RT_EINVAL);
        return 0;
    }

    rt_sem_take(sdio->part.lock, RT_WAITING_FOREVER);
    do {
        size_t block_count =  size;
        uint32_t addr = (offset + pos);
        cy_rslt_t result = cyhal_sdhc_read_async(hw_sdio, addr, buffer, &block_count);
        if(CY_RSLT_SUCCESS != result)
        {
            err = -RT_ERROR;
            break;
        }
        /* Waits on a semaphore until the transfer completes, when RTOS_AWARE component is defined. */
        result = cyhal_sdhc_wait_transfer_complete(hw_sdio);
        if(CY_RSLT_SUCCESS != result)
        {
            err = -RT_ERROR;
            break;
        }
    }while(0);
    rt_sem_release(sdio->part.lock);

    /* the length of reading must align to SECTOR SIZE */
    if (err)
    {
        rt_set_errno(-RT_EIO);
        return 0;
    }
    return size;
}

static rt_ssize_t rt_mmcsd_write(rt_device_t dev,
                                rt_off_t    pos,
                                const void *buffer,
                                rt_size_t   size)
{
    rt_err_t err = 0;
    void *rd_ptr = (void *)buffer;
    struct rthw_sdio *sdio = (struct rthw_sdio *)dev;
    cyhal_sdhc_t *hw_sdio = &sdio->sdhc_obj;
    off_t offset = sdio->part.offset;

    LOG_D("mmc write: off:%d pos:%d size:%d", offset, pos, size);
    if (dev == RT_NULL)
    {
        rt_set_errno(-RT_EINVAL);
        return 0;
    }

    rt_sem_take(sdio->part.lock, RT_WAITING_FOREVER);
    do {
        size_t block_count =  size ;
        uint32_t addr = (offset + pos);
        cy_rslt_t result = cyhal_sdhc_write_async(hw_sdio, addr, buffer, &block_count);
        if(CY_RSLT_SUCCESS != result)
        {
            err = -RT_ERROR;
            break;
        }
        /* Waits on a semaphore until the transfer completes, when RTOS_AWARE component is defined. */
        result = cyhal_sdhc_wait_transfer_complete(hw_sdio);
        if(CY_RSLT_SUCCESS != result)
        {
            err = -RT_ERROR;
            break;
        }
    }while(0);
    rt_sem_release(sdio->part.lock);

    /* the length of reading must align to SECTOR SIZE */
    if (err)
    {
        rt_set_errno(-RT_EIO);
        return 0;
    }
    return size;
}
#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops mmcsd_blk_ops =
{
    rt_mmcsd_init,
    rt_mmcsd_open,
    rt_mmcsd_close,
    rt_mmcsd_read,
    rt_mmcsd_write,
    rt_mmcsd_control
};
#endif
int rt_hw_sdio_init(void)
{
    struct rthw_sdio *sdio = RT_NULL;
    struct _cy_sdio_pin_config *pins_cfg;
    char sname[16];

    sdio = rt_malloc(sizeof(struct rthw_sdio));
    if (sdio == RT_NULL)
    {
        LOG_E("malloc rthw_sdio fail");
        return RT_NULL;
    }
    rt_memset(sdio, 0, sizeof(struct rthw_sdio));

    LOG_D("sdio pins: cmd=%d,clk=%d,d0=%d,d1=%d,d2=%d,d3=%d,d4=%d,d5=%d,d6=%d,d7=%d",
        _sdio1_pins_and_name.cmd,   _sdio1_pins_and_name.clk,
        _sdio1_pins_and_name.data0, _sdio1_pins_and_name.data1, _sdio1_pins_and_name.data2, _sdio1_pins_and_name.data3,
        _sdio1_pins_and_name.data4, _sdio1_pins_and_name.data5, _sdio1_pins_and_name.data6, _sdio1_pins_and_name.data7
    );
    LOG_D("\tdetect=%d,volt_sel=%d,pwr_en=%d,write_prot=%d,led_ctrl=%d,emmc_reset=%d",
        _sdio1_pins_and_name.card_detect,          _sdio1_pins_and_name.io_volt_sel, _sdio1_pins_and_name.card_if_pwr_en,
        _sdio1_pins_and_name.card_mech_write_prot, _sdio1_pins_and_name.led_ctrl,    _sdio1_pins_and_name.card_emmc_reset
    );
    /* register mmcsd device */
    sdio->parent.type  = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    sdio->parent.ops  = &mmcsd_blk_ops;
#else
    sdio->parent.init = rt_mmcsd_init;
    sdio->parent.open = rt_mmcsd_open;
    sdio->parent.close = rt_mmcsd_close;
    sdio->parent.read = rt_mmcsd_read;
    sdio->parent.write = rt_mmcsd_write;
    sdio->parent.control = rt_mmcsd_control;
#endif

    do {
        sdio->sdhc_config.enableLedControl = SDCARD_LED_CTRL_ENABLE;
        sdio->sdhc_config.isEmmc = SDCARD_EMMC_ENABLE;
        sdio->sdhc_config.lowVoltageSignaling = false;
        sdio->sdhc_config.busWidth = BSP_USING_SDCARD_BUS_WIDTH;
        /* Initialize the SD Card interface. */
        int rslt = cyhal_sdhc_init_hw(&sdio->sdhc_obj, &sdio->sdhc_config, _sdcard_config.cmd,   _sdcard_config.clk,
                                 _sdcard_config.data0,  _sdcard_config.data1, _sdcard_config.data2, _sdcard_config.data3,
                                 _sdcard_config.data4,  _sdcard_config.data5, _sdcard_config.data6, _sdcard_config.data7,
                                 _sdcard_config.card_detect, _sdcard_config.io_volt_sel, _sdcard_config.card_if_pwr_en,
                                 _sdcard_config.card_mech_write_prot, _sdcard_config.led_ctrl, _sdcard_config.card_emmc_reset, RT_NULL);
        if(rslt != CY_RSLT_SUCCESS)
        {
            LOG_E("sdhc hw init fail: (0x%x)", rslt);
            break;
        }

        rslt = cyhal_sdhc_init_card(&sdio->sdhc_obj);
        if(rslt != CY_RSLT_SUCCESS)
        {
            LOG_E("sdhc init fail: (0x%x)", rslt);
            break;
        }

        rt_uint32_t block_count;
        rslt = cyhal_sdhc_get_block_count(&sdio->sdhc_obj, &block_count);
        if(rslt != CY_RSLT_SUCCESS)
        {
            LOG_E("get block count fail: (0x%x)", rslt);
            break;
        }
        LOG_D("block count:%d(0x%x)", block_count, block_count);

        sdio->geometry.bytes_per_sector = 512;
        sdio->geometry.block_size = 512;
        sdio->geometry.sector_count = block_count;

        rt_snprintf(sname, sizeof(sname) - 1, "sem_%s%d", _sdcard_config.name, 0);
        sdio->part.lock = rt_sem_create(sname, 1, RT_IPC_FLAG_FIFO);
        if(sdio->part.lock == RT_NULL)
        {
            LOG_E("create part.lock fail");
            break;
        }

        rt_uint8_t *sector = rt_malloc(512);
        if(sector == RT_NULL)
        {
            LOG_E("malloc sector fail");
            break;
        }
        if(rt_mmcsd_read(&sdio->parent, 0, sector, 1) < 0)
        {
            LOG_E("rt_mmcsd_read fail");
            rt_free(sector);
            break;
        }
        rslt = dfs_filesystem_get_partition(&sdio->part, sector, 0);
        rt_free(sector);
        if(rslt != RT_EOK)
        {
            LOG_E("partition not found!");
            break;
        }

        rslt = rt_device_register(&(sdio->parent), _sdcard_config.name,
                       RT_DEVICE_FLAG_RDWR);

        if(rslt != RT_EOK)
        {
            LOG_E("register device fail!");
            break;
        }

        return RT_EOK;

    }while(0);

    if(sdio)
    {
        cyhal_sdhc_free(&sdio->sdhc_obj);
        if(sdio->part.lock)
        {
            rt_sem_delete(sdio->part.lock);
        }
        rt_free(sdio);
    }

    return -RT_ERROR;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

#endif

