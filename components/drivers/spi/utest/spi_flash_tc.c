/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     CYFS         add SPI flash SFUD read/write utest
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_SPI_FLASH

#undef DBG_TAG
#undef DBG_LVL
#include "dev_spi_flash_sfud.h"

#define SPI_FLASH_SPI_DEV_NAME       RT_UTEST_SPI_FLASH_SPI_DEV_NAME
#define SPI_FLASH_DEV_NAME           RT_UTEST_SPI_FLASH_DEV_NAME
#define SPI_FLASH_BUS_NAME           RT_UTEST_SPI_FLASH_BUS_NAME
#define SPI_FLASH_CS_PIN             RT_UTEST_SPI_FLASH_CS_PIN
#define SPI_FLASH_MAX_HZ             RT_UTEST_SPI_FLASH_MAX_HZ
#define SPI_FLASH_TEST_OFFSET        RT_UTEST_SPI_FLASH_TEST_OFFSET
#define SPI_FLASH_TEST_SIZE          RT_UTEST_SPI_FLASH_TEST_SIZE

static rt_spi_flash_device_t spi_flash_probe_dev = RT_NULL;
static sfud_flash_t sfud_dev = RT_NULL;
static struct rt_spi_device spi_flash_attached_dev;
static rt_bool_t spi_flash_attached;
static rt_uint32_t test_addr;
static rt_uint32_t backup_addr;
static rt_uint32_t backup_size;
static rt_uint8_t *backup_buf = RT_NULL;
static rt_uint8_t *write_buf = RT_NULL;
static rt_uint8_t *read_buf = RT_NULL;

static rt_uint32_t spi_flash_align_down(rt_uint32_t value, rt_uint32_t align)
{
    return value - value % align;
}

static rt_uint32_t spi_flash_align_up(rt_uint32_t value, rt_uint32_t align)
{
    rt_uint64_t aligned = value;

    aligned = (aligned + align - 1) / align * align;
    return (rt_uint32_t)aligned;
}

static rt_err_t spi_flash_restore_backup(void)
{
    sfud_err result;

    if (sfud_dev == RT_NULL || backup_buf == RT_NULL || backup_size == 0)
    {
        return RT_EOK;
    }

    result = sfud_erase_write(sfud_dev, backup_addr, backup_size, backup_buf);
    if (result != SFUD_SUCCESS)
    {
        LOG_E("Restore SPI flash data failed, addr: 0x%08x, size: %u.", backup_addr, backup_size);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static void spi_flash_fill_pattern(rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t i;

    for (i = 0; i < size; i++)
    {
        buf[i] = (rt_uint8_t)(0xA5 ^ (i * 13 + (i >> 2)));
    }
}

static void spi_flash_free_buffers(void)
{
    if (backup_buf != RT_NULL)
    {
        rt_free(backup_buf);
        backup_buf = RT_NULL;
    }
    if (write_buf != RT_NULL)
    {
        rt_free(write_buf);
        write_buf = RT_NULL;
    }
    if (read_buf != RT_NULL)
    {
        rt_free(read_buf);
        read_buf = RT_NULL;
    }
}

static void spi_flash_delete_probe_dev(void)
{
    sfud_dev = RT_NULL;
    if (spi_flash_probe_dev != RT_NULL)
    {
        rt_sfud_flash_delete(spi_flash_probe_dev);
        spi_flash_probe_dev = RT_NULL;
    }
}

static void spi_flash_detach_device(void)
{
    if (spi_flash_attached)
    {
        rt_spi_bus_detach_device_cspin(&spi_flash_attached_dev);
        spi_flash_attached = RT_FALSE;
    }
}

static rt_bool_t spi_flash_is_all_ff(const rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t i;

    for (i = 0; i < size; i++)
    {
        if (buf[i] != 0xFF)
        {
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}

static sfud_flash_t spi_flash_find_existing(void)
{
    rt_device_t flash_dev;
    rt_device_t spi_dev;

    flash_dev = rt_device_find(SPI_FLASH_DEV_NAME);
    if (flash_dev != RT_NULL && flash_dev->type == RT_Device_Class_Block)
    {
        rt_spi_flash_device_t spi_flash_dev = (rt_spi_flash_device_t)flash_dev;

        if (spi_flash_dev->user_data != RT_NULL)
        {
            LOG_I("Use existing SFUD flash device %s.", SPI_FLASH_DEV_NAME);
            return (sfud_flash_t)spi_flash_dev->user_data;
        }
    }

    spi_dev = rt_device_find(SPI_FLASH_SPI_DEV_NAME);
    if (spi_dev != RT_NULL && spi_dev->type == RT_Device_Class_SPIDevice)
    {
        struct rt_spi_device *rt_spi_dev = (struct rt_spi_device *)spi_dev;
        rt_spi_flash_device_t spi_flash_dev = (rt_spi_flash_device_t)rt_spi_dev->user_data;

        if (spi_flash_dev != RT_NULL && spi_flash_dev->user_data != RT_NULL)
        {
            sfud_flash_t flash = (sfud_flash_t)spi_flash_dev->user_data;

            LOG_I("Use existing SFUD flash %s on SPI device %s.",
                  flash->name, SPI_FLASH_SPI_DEV_NAME);
            return flash;
        }
    }

    return RT_NULL;
}

static rt_err_t spi_flash_attach_device(void)
{
    rt_base_t cs_pin = SPI_FLASH_CS_PIN;
    rt_device_t spi_dev;
    rt_device_t bus;
    rt_err_t result;

    spi_dev = rt_device_find(SPI_FLASH_SPI_DEV_NAME);
    if (spi_dev != RT_NULL)
    {
        if (spi_dev->type != RT_Device_Class_SPIDevice)
        {
            LOG_E("%s exists but is not an SPI device.", SPI_FLASH_SPI_DEV_NAME);
            return -RT_ERROR;
        }
        return RT_EOK;
    }

    bus = rt_device_find(SPI_FLASH_BUS_NAME);
    if (bus == RT_NULL || bus->type != RT_Device_Class_SPIBUS)
    {
        LOG_E("SPI bus %s not found.", SPI_FLASH_BUS_NAME);
        return -RT_ERROR;
    }

    if (cs_pin < 0)
    {
        cs_pin = PIN_NONE;
    }

    LOG_I("Try to attach SPI flash device %s to bus %s, CS pin %d.",
          SPI_FLASH_SPI_DEV_NAME, SPI_FLASH_BUS_NAME, (int)cs_pin);

    rt_memset(&spi_flash_attached_dev, 0, sizeof(spi_flash_attached_dev));
    result = rt_spi_bus_attach_device_cspin(&spi_flash_attached_dev,
                                            SPI_FLASH_SPI_DEV_NAME,
                                            SPI_FLASH_BUS_NAME,
                                            cs_pin,
                                            RT_NULL);
    if (result == RT_EOK)
    {
        spi_flash_attached = RT_TRUE;
        LOG_I("Attach SPI flash device %s to bus %s success.",
              SPI_FLASH_SPI_DEV_NAME, SPI_FLASH_BUS_NAME);
    }
    else
    {
        LOG_E("Attach SPI flash device %s to bus %s failed, result: %d.",
              SPI_FLASH_SPI_DEV_NAME, SPI_FLASH_BUS_NAME, result);
    }

    return result;
}

static rt_err_t spi_flash_read_jedec_id(rt_uint8_t id[3])
{
    rt_device_t spi_dev;
    struct rt_spi_device *rt_spi_dev;
    struct rt_spi_configuration cfg;
    rt_uint8_t cmd = 0x9F;
    rt_err_t result;

    spi_dev = rt_device_find(SPI_FLASH_SPI_DEV_NAME);
    if (spi_dev == RT_NULL || spi_dev->type != RT_Device_Class_SPIDevice)
    {
        return -RT_ERROR;
    }

    rt_spi_dev = (struct rt_spi_device *)spi_dev;
    rt_memset(&cfg, 0, sizeof(cfg));
    cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.data_width = 8;
    cfg.max_hz = SPI_FLASH_MAX_HZ;

    result = rt_spi_configure(rt_spi_dev, &cfg);
    if (result != RT_EOK && result != -RT_EBUSY)
    {
        return result;
    }

    return rt_spi_send_then_recv(rt_spi_dev, &cmd, sizeof(cmd), id, 3);
}

static void spi_flash_probe_info(void)
{
    rt_uint8_t mf_id = sfud_dev->chip.mf_id;
    rt_uint8_t type_id = sfud_dev->chip.type_id;
    rt_uint8_t capacity_id = sfud_dev->chip.capacity_id;

    LOG_I("SPI flash %s JEDEC ID %02x %02x %02x, capacity %u bytes, erase granularity %u bytes.",
          sfud_dev->name, mf_id, type_id, capacity_id, sfud_dev->chip.capacity, sfud_dev->chip.erase_gran);

    uassert_true(sfud_dev->chip.capacity > 0);
    uassert_true(sfud_dev->chip.erase_gran > 0);
    uassert_true(sfud_dev->chip.write_mode != 0);
    uassert_true(sfud_dev->chip.erase_gran_cmd != 0);
}

static void spi_flash_erase_write_read(void)
{
    sfud_err result;

    rt_memset(read_buf, 0, SPI_FLASH_TEST_SIZE);
    result = sfud_erase(sfud_dev, backup_addr, backup_size);
    uassert_int_equal(result, SFUD_SUCCESS);

    result = sfud_read(sfud_dev, test_addr, SPI_FLASH_TEST_SIZE, read_buf);
    uassert_int_equal(result, SFUD_SUCCESS);
    uassert_true(spi_flash_is_all_ff(read_buf, SPI_FLASH_TEST_SIZE));

    spi_flash_fill_pattern(write_buf, SPI_FLASH_TEST_SIZE);
    result = sfud_write(sfud_dev, test_addr, SPI_FLASH_TEST_SIZE, write_buf);
    uassert_int_equal(result, SFUD_SUCCESS);

    rt_memset(read_buf, 0, SPI_FLASH_TEST_SIZE);
    result = sfud_read(sfud_dev, test_addr, SPI_FLASH_TEST_SIZE, read_buf);
    uassert_int_equal(result, SFUD_SUCCESS);
    uassert_buf_equal(write_buf, read_buf, SPI_FLASH_TEST_SIZE);
}

static rt_err_t utest_tc_init(void)
{
    rt_uint32_t erase_gran;

    sfud_dev = spi_flash_find_existing();
    if (sfud_dev == RT_NULL && spi_flash_attach_device() != RT_EOK)
    {
        LOG_E("Attach SPI flash device %s on bus %s failed.",
              SPI_FLASH_SPI_DEV_NAME, SPI_FLASH_BUS_NAME);
        return -RT_ERROR;
    }

    if (sfud_dev == RT_NULL)
    {
        rt_uint8_t jedec_id[3] = {0};

        if (spi_flash_read_jedec_id(jedec_id) == RT_EOK)
        {
            LOG_I("SPI flash raw JEDEC ID: %02x %02x %02x at %u Hz.",
                  jedec_id[0], jedec_id[1], jedec_id[2], (unsigned int)SPI_FLASH_MAX_HZ);
        }
        else
        {
            LOG_W("Read SPI flash raw JEDEC ID failed before SFUD probe.");
        }

        LOG_I("Try to probe SFUD flash device %s by SPI device %s.",
              SPI_FLASH_DEV_NAME, SPI_FLASH_SPI_DEV_NAME);
        {
            struct rt_spi_configuration cfg;

            rt_memset(&cfg, 0, sizeof(cfg));
            cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB;
            cfg.data_width = 8;
            cfg.max_hz = SPI_FLASH_MAX_HZ;
            spi_flash_probe_dev = rt_sfud_flash_probe_ex(SPI_FLASH_DEV_NAME,
                                                         SPI_FLASH_SPI_DEV_NAME,
                                                         &cfg,
                                                         RT_NULL);
        }
        if (spi_flash_probe_dev != RT_NULL)
        {
            sfud_dev = (sfud_flash_t)spi_flash_probe_dev->user_data;
        }
    }

    if (sfud_dev == RT_NULL)
    {
        LOG_E("SFUD flash on SPI device %s not found.", SPI_FLASH_SPI_DEV_NAME);
        spi_flash_detach_device();
        return -RT_ERROR;
    }

    if (SPI_FLASH_TEST_SIZE <= 0)
    {
        LOG_E("SPI flash test size must be greater than 0.");
        spi_flash_detach_device();
        return -RT_ERROR;
    }

    erase_gran = sfud_dev->chip.erase_gran;
    if (sfud_dev->chip.capacity == 0 || erase_gran == 0)
    {
        LOG_E("Invalid SPI flash geometry, capacity: %u, erase granularity: %u.",
              sfud_dev->chip.capacity, erase_gran);
        goto __error;
    }

    test_addr = SPI_FLASH_TEST_OFFSET;
    if (test_addr >= sfud_dev->chip.capacity ||
        SPI_FLASH_TEST_SIZE > sfud_dev->chip.capacity - test_addr)
    {
        LOG_E("SPI flash test range is out of bounds, offset: 0x%08x, size: %u, capacity: %u.",
              test_addr, SPI_FLASH_TEST_SIZE, sfud_dev->chip.capacity);
        goto __error;
    }

    backup_addr = spi_flash_align_down(test_addr, erase_gran);
    backup_size = spi_flash_align_up(test_addr + SPI_FLASH_TEST_SIZE - backup_addr, erase_gran);
    if (backup_size > sfud_dev->chip.capacity - backup_addr)
    {
        LOG_E("SPI flash backup range is out of bounds, offset: 0x%08x, size: %u, capacity: %u.",
              backup_addr, backup_size, sfud_dev->chip.capacity);
        goto __error;
    }

    backup_buf = (rt_uint8_t *)rt_malloc(backup_size);
    write_buf = (rt_uint8_t *)rt_malloc(SPI_FLASH_TEST_SIZE);
    read_buf = (rt_uint8_t *)rt_malloc(SPI_FLASH_TEST_SIZE);
    if (backup_buf == RT_NULL || write_buf == RT_NULL || read_buf == RT_NULL)
    {
        LOG_E("Allocate SPI flash test buffer failed.");
        goto __nomem;
    }

    if (sfud_read(sfud_dev, backup_addr, backup_size, backup_buf) != SFUD_SUCCESS)
    {
        LOG_E("Backup SPI flash data failed, addr: 0x%08x, size: %u.", backup_addr, backup_size);
        goto __error;
    }

    LOG_I("SPI flash test uses %s on %s at offset 0x%08x, size %u.",
          sfud_dev->name, SPI_FLASH_SPI_DEV_NAME, test_addr, SPI_FLASH_TEST_SIZE);

    return RT_EOK;

__nomem:
    spi_flash_free_buffers();
    spi_flash_delete_probe_dev();
    spi_flash_detach_device();
    return -RT_ENOMEM;

__error:
    spi_flash_free_buffers();
    spi_flash_delete_probe_dev();
    spi_flash_detach_device();
    return -RT_ERROR;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t result;

    result = spi_flash_restore_backup();

    spi_flash_free_buffers();
    spi_flash_delete_probe_dev();
    spi_flash_detach_device();

    return result;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(spi_flash_probe_info);
    UTEST_UNIT_RUN(spi_flash_erase_write_read);
}

UTEST_TC_EXPORT(testcase, "components.drivers.spi.flash", utest_tc_init, utest_tc_cleanup, 30);

#endif /* RT_UTEST_SPI_FLASH */
