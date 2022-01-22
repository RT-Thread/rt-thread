/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "am_mcu_apollo.h"
#include "flash.h"

/* RT-Thread device interface */
static rt_err_t rt_flash_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_flash_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_flash_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_flash_control(rt_device_t dev, int cmd, void *args)
{
    uint32_t ui32Critical, i;
    uint32_t ui32CurrentPage, ui32CurrentBlock;

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL)
            return -RT_ERROR;

        geometry->bytes_per_sector = 8192;
        geometry->sector_count = 8192;
        geometry->block_size = 8192;
    }

    else if(cmd == RT_DEVICE_CTRL_BLK_ERASE)
    {
        struct rom_control_erase *erase;
        erase = (struct rom_control_erase *)args;

        // Start a critical section.
        ui32Critical = am_hal_interrupt_master_disable();

        if (erase->type == 0x01)
        {
            for(i = 0; i < erase->pagenums; i++)
            {
                // Figure out what page and block we're working on.
                ui32CurrentPage =  AM_HAL_FLASH_ADDR2PAGE(erase->addrstart);
                ui32CurrentBlock = AM_HAL_FLASH_ADDR2INST(erase->addrstart);

                am_hal_flash_page_erase(AM_HAL_FLASH_PROGRAM_KEY, ui32CurrentBlock, ui32CurrentPage); //单扇区擦除命令
                erase->addrstart += 8192;
            }
        }

        // Exit the critical section.
        am_hal_interrupt_master_set(ui32Critical);
    }

    return RT_EOK;
}

static rt_size_t rt_flash_read(rt_device_t dev,
                                   rt_off_t pos,
                                   void* buffer,
                                   rt_size_t size)
{
    rt_memcpy((uint8_t *)buffer, (uint8_t *)pos, size);

    return size;
}

static rt_size_t rt_flash_write(rt_device_t dev,
                                    rt_off_t pos,
                                    const void* buffer,
                                    rt_size_t size)
{
    uint32_t ui32Critical;
    uint32_t ui32WordsInBuffer;

    ui32WordsInBuffer = (size + 3)/ 4;

    // Start a critical section.
    ui32Critical = am_hal_interrupt_master_disable();

    // Program the flash page with the data we just received.
    am_hal_flash_program_main(AM_HAL_FLASH_PROGRAM_KEY, (uint32_t *)buffer, (uint32_t *)pos, ui32WordsInBuffer);

    // Exit the critical section.
    am_hal_interrupt_master_set(ui32Critical);

    return size;
}

int rt_hw_rom_init(void)
{
    static struct rt_device device;

    /* register device */
    device.type        = RT_Device_Class_Block;
    device.init        = rt_flash_init;
    device.open        = rt_flash_open;
    device.close       = rt_flash_close;
    device.read        = rt_flash_read;
    device.write       = rt_flash_write;
    device.control     = rt_flash_control;

    /* no private */
    device.user_data = RT_NULL;

    /* register the device */
    rt_device_register(&device, "rom", RT_DEVICE_FLAG_RDWR);

    //rt_kprintf("register device rom!\r\n");

    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_DEVICE_EXPORT(rt_hw_rom_init);
#endif

/*@}*/
