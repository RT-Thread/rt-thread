/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     zhugengyu    first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#ifdef BSP_USING_XHCI

#include "board.h"

#include "interrupt.h"
#include "mm_aspace.h"
#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif

#include "usbh_core.h"

#include "fcpu_info.h"

struct usb_xhci_config
{
    rt_uint32_t  id;
    rt_ubase_t   base_addr; /* virtual address */
    rt_uint32_t  irq;
    rt_uint32_t  irq_priority;
};

static struct usb_xhci_config xhci_config[FUSB3_NUM] =
{
    [FUSB3_ID_0] = {
        .id = FUSB3_ID_0,
        .base_addr = FUSB3_0_BASE_ADDR + FUSB3_XHCI_OFFSET,
        .irq = FUSB3_0_IRQ_NUM,
        .irq_priority = 0xd0,
    },
    [FUSB3_ID_1] = {
        .id = FUSB3_ID_1,
        .base_addr = FUSB3_1_BASE_ADDR + FUSB3_XHCI_OFFSET,
        .irq = FUSB3_1_IRQ_NUM,
        .irq_priority = 0xd0,
    },
};

/* cherry usb support unique instance yet */
#define XHCI_DEVICE_ID      CONFIG_USBHOST_XHCI_ID

extern void USBH_IRQHandler(void *);

static void usb_xhci_interrupt_handler(rt_int32_t vector, void *args)
{
    /* args not in used */
    USBH_IRQHandler(args);
}

static void usb_xhci_setup_interrupt(struct usb_xhci_config *config)
{
    RT_ASSERT(config);
    rt_uint32_t irq_num = config->irq;
    rt_uint32_t irq_priority = config->irq_priority;
    rt_uint32_t cpu_id = 0;

    GetCpuId((u32 *)&cpu_id);

    rt_hw_interrupt_set_target_cpus(irq_num, cpu_id);
    rt_hw_interrupt_set_priority(irq_num, irq_priority);
    rt_hw_interrupt_install(irq_num, usb_xhci_interrupt_handler, config, "xhci");
    rt_hw_interrupt_umask(irq_num);
}

/* implement cherryusb weak functions */
void usb_hc_low_level_init(void)
{
    usb_xhci_setup_interrupt(&xhci_config[XHCI_DEVICE_ID]);
}

unsigned long usb_hc_get_register_base(void)
{
    return xhci_config[XHCI_DEVICE_ID].base_addr;
}

void usb_assert(const char *filename, int linenum)
{
    RT_ASSERT(0);
}

#endif
