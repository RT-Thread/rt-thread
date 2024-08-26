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

#include "usbh_core.h"

static const uint32_t irq_nums[] = {
    FUSB2_0_VHUB_IRQ_NUM, FUSB2_1_IRQ_NUM, FUSB2_2_IRQ_NUM
};

void USBH_IRQHandler(uint8_t busid);

void usb_assert(const char *filename, int linenum)
{
    rt_assert_handler("", filename, linenum);
}

static void usb_hc_pusb2_interrupt_handler(int irqno, void *param)
{
    if (irqno == FUSB2_0_VHUB_IRQ_NUM) {
        USBH_IRQHandler(FUSB2_ID_VHUB_0);
    } else if (irqno == FUSB2_1_IRQ_NUM) {
        USBH_IRQHandler(FUSB2_ID_1);
    } else if (irqno == FUSB2_2_IRQ_NUM) {
        USBH_IRQHandler(FUSB2_ID_2);
    }
}

static void usb_hc_setup_pusb2_interrupt(uint32_t id)
{
    uint32_t irq_num = irq_nums[id];

    rt_hw_interrupt_set_priority(irq_num, 0U);
    rt_hw_interrupt_install(irq_num, usb_hc_pusb2_interrupt_handler, NULL, "pusb2-hc");
    rt_hw_interrupt_umask(irq_num);

    USB_LOG_DBG("Enable irq-%d\n", irq_num);
}

static void usb_hc_revoke_pusb2_interrupt(uint32_t id)
{
    uint32_t irq_num = irq_nums[id];

    rt_hw_interrupt_mask(irq_num);
}

unsigned long usb_hc_get_register_base(uint32_t id)
{
    if (id == FUSB2_ID_VHUB_0) {
        return FUSB2_0_VHUB_BASE_ADDR;
    } else if (id == FUSB2_ID_1) {
        return FUSB2_1_BASE_ADDR;
    } else if (id == FUSB2_ID_2) {
        return FUSB2_2_BASE_ADDR;
    } else {
        USB_ASSERT(0);
        return 0;
    }
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    usb_hc_setup_pusb2_interrupt(bus->busid);
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    usb_hc_revoke_pusb2_interrupt(bus->busid);
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