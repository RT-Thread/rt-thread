/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-14     zhugengyu    first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#if defined(BSP_USING_PUSB2) && defined(PKG_CHERRYUSB_HOST_PUSB2)

#include "board.h"

#include "interrupt.h"
#include "mm_aspace.h"
#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif

#include "usbh_core.h"

#include "fcpu_info.h"

struct usb_pusb2_config
{
    rt_uint32_t  id;
    rt_ubase_t   base_addr; /* virtual address */
    rt_uint32_t  irq;
    rt_uint32_t  irq_priority;
};

static struct usb_pusb2_config pusb2_config[1U] =
{
    [FUSB2_ID_VHUB_0] =
    {
        .id = FUSB2_ID_VHUB_0,
        .base_addr = FUSB2_0_VHUB_BASE_ADDR,
        .irq = FUSB2_0_VHUB_IRQ_NUM,
        .irq_priority = 0xd0,
    },
};

/* cherry usb support unique instance yet */
#define PUSB2_DEVICE_ID      FUSB2_ID_VHUB_0

extern void USBH_IRQHandler(void *);

static void usb_pusb2_interrupt_handler(rt_int32_t vector, void *args)
{
    /* args not in use */
    USBH_IRQHandler(args);
}

static void usb_pusb2_setup_interrupt(struct usb_pusb2_config *config)
{
    RT_ASSERT(config);
    rt_uint32_t irq_num = config->irq;
    rt_uint32_t irq_priority = config->irq_priority;
    rt_uint32_t cpu_id = 0;

    GetCpuId((u32 *)&cpu_id);

    rt_hw_interrupt_set_target_cpus(irq_num, cpu_id);
    rt_hw_interrupt_set_priority(irq_num, irq_priority);
    rt_hw_interrupt_install(irq_num, usb_pusb2_interrupt_handler, config, "pusb2");
    rt_hw_interrupt_umask(irq_num);
}

/* implement cherryusb weak functions */
void usb_hc_low_level_init()
{
    usb_pusb2_setup_interrupt(&pusb2_config[PUSB2_DEVICE_ID]);
}

void usb_hc_low_level_deinit(void)
{

}

unsigned long usb_hc_get_register_base(void)
{
    return pusb2_config[PUSB2_DEVICE_ID].base_addr;
}

void usb_assert(const char *filename, int linenum)
{
    RT_ASSERT(0);
}

#endif
