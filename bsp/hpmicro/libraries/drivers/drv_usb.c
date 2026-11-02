/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "tusb.h"

/* Definition of logic unit number for each drive */
#define LUN_USB     (0U)    /* lun 0 of usb drive */

static rt_ssize_t hpm_usb_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static rt_ssize_t hpm_usb_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
rt_err_t  hpm_usb_control(rt_device_t dev, int cmd, void *args);

rt_uint8_t usb_dev_addr;

static struct rt_device hpm_usb = {
    .read = hpm_usb_read,
    .write = hpm_usb_write,
    .control = hpm_usb_control,
};

static bool usb_disk_wait_for_complete(uint8_t usb_addr)
{
    #if CFG_TUSB_OS != OPT_OS_NONE
    int32_t retry_cnt = 200;
    #else
    int32_t retry_cnt = 5000000;
    #endif

    while (!tuh_msc_idle(usb_addr) && retry_cnt--)
    {
        #if CFG_TUSB_OS != OPT_OS_NONE
        osal_task_delay(5);
        #else
        tuh_task();
        #endif
    }

    return retry_cnt > 0 ? true : false;
}

void hpm_usb_set_addr(uint8_t dev_addr)
{
    usb_dev_addr = dev_addr;
}

static rt_ssize_t hpm_usb_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_bool_t result;

    result = tuh_msc_read10(usb_dev_addr, LUN_USB, buffer, pos, size, NULL);

    if (result) {
        result =  usb_disk_wait_for_complete(usb_dev_addr);
    }

    return result ? size : 0;
}

static rt_ssize_t hpm_usb_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    bool result;

    result = tuh_msc_write10(usb_dev_addr, LUN_USB, buffer, pos, size, NULL);

    if (result) {
        result =  usb_disk_wait_for_complete(usb_dev_addr);
    }

    return result ? size : 0;
}

rt_err_t hpm_usb_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t ret = RT_EOK;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_BLK_GETGEOME:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        struct rt_device_blk_geometry *geometry = (struct rt_device_blk_geometry *)args;
        geometry->sector_count = tuh_msc_get_block_count(usb_dev_addr, LUN_USB);
        geometry->bytes_per_sector = tuh_msc_get_block_size(usb_dev_addr, LUN_USB);
       break;
    case RT_DEVICE_CTRL_BLK_SYNC:
        break;
    case RT_DEVICE_CTRL_BLK_ERASE:
        break;

    default:
        ret = -RT_EINVAL;
        break;
    }

    return ret;
}

int rt_hw_usb_init(void)
{
    rt_err_t err = RT_EOK;

    hpm_usb.type = RT_Device_Class_Block;

    err = rt_device_register(&hpm_usb, "usb0", RT_DEVICE_FLAG_RDWR);

    if (err != RT_EOK) {
        LOG_E("rt device %s failed, status=%d\n", "usb", err);
        return err;
    }
    
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
    /* Register usb device to irq table */
    extern void hpm_isr_usb0(void);
    rt_hw_interrupt_install(IRQn_USB0, (rt_isr_handler_t)hpm_isr_usb0, HPM_USB0, "usb0");
#ifdef HPM_USB1_BASE
    extern void hpm_isr_usb1(void);
    rt_hw_interrupt_install(IRQn_USB1, (rt_isr_handler_t)hpm_isr_usb1, HPM_USB1, "usb1");
#endif
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

    return err;
}

INIT_BOARD_EXPORT(rt_hw_usb_init);
