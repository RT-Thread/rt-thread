/*
 * Copyright : (C) 2024 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2024/6/26 first commit
 */
#include "rtthread.h"
#include "interrupt.h"

#include "fparameters.h"

#include "usbd_core.h"

void USBD_IRQHandler(uint8_t busid);

void usb_assert(const char *filename, int linenum)
{
    rt_assert_handler("", filename, linenum);
}

static void usb_dc_pusb2_interrupt_handler(int irqno, void *param)
{
    USBD_IRQHandler(CONFIG_USB_PUSB2_BUS_ID);
}

static void usb_dc_setup_pusb2_interrupt(uint32_t id)
{
    uint32_t irq_num = FUSB2_0_VHUB_IRQ_NUM;

    rt_hw_interrupt_set_priority(irq_num, 0U);
    rt_hw_interrupt_install(irq_num, usb_dc_pusb2_interrupt_handler, NULL, "pusb2-dc");
    rt_hw_interrupt_umask(irq_num);
}

static void usb_dc_revoke_pusb2_interrupt(uint32_t id)
{
    uint32_t irq_num = FUSB2_0_VHUB_IRQ_NUM;

    rt_hw_interrupt_mask(irq_num);
}

unsigned long usb_dc_get_register_base(uint32_t id)
{
    USB_ASSERT(id == FUSB2_ID_VHUB_0);
    return FUSB2_0_VHUB_BASE_ADDR;
}

void usb_dc_low_level_init()
{
    usb_dc_setup_pusb2_interrupt(CONFIG_USB_PUSB2_BUS_ID);
}

void usb_dc_low_level_deinit(void)
{
    usb_dc_revoke_pusb2_interrupt(CONFIG_USB_PUSB2_BUS_ID);
}

void *usb_sys_mem_malloc(size_t size)
{
    void *buf = rt_malloc(size);

    if (buf) {
        rt_memset(buf, 0, size);
    }

    return buf;
}

void usb_sys_mem_free(void *ptr)
{
    if (ptr) {
        rt_free(ptr);
    }
}

void *usb_sys_malloc_align(size_t align, size_t size)
{
    void *buf = rt_malloc_align(size, align);

    if (buf) {
        rt_memset(buf, 0, size);
    }

    return buf;
}