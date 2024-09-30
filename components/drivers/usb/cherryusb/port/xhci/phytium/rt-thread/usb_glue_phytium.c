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
#include "usbh_core.h"

#include "usb_config.h"

void usb_hc_setup_xhci_interrupt(uint32_t id);
void usb_hc_revoke_xhci_interrupt(uint32_t id);

void *xhci_mem_malloc(size_t align, size_t size)
{
    void *result = rt_malloc_align(size, align);

    if (result)
    {
        memset(result, 0U, size);
    }

    return result;
}

void xhci_mem_free(void *ptr)
{
    if (NULL != ptr)
    {
        rt_free(ptr);
    }
}

void xhci_dcache_sync(void *ptr, size_t len, uint32_t flags)
{
    if (flags & XHCI_DCACHE_FLUSH)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, ptr, len);
    }
    else if (flags & XHCI_DCACHE_INVALIDATE)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, ptr, len);
    }
}

void usb_assert(const char *filename, int linenum)
{
    rt_assert_handler("", filename, linenum);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    /* platform XHCI controller */
    usb_hc_setup_xhci_interrupt(bus->busid);
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    usb_hc_revoke_xhci_interrupt(bus->busid);
}