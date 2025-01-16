/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _USB_OHCI_PRIV_H
#define _USB_OHCI_PRIV_H

#include "usbh_core.h"
#include "usbh_hub.h"
#include "usb_ohci_reg.h"

#define OHCI_HCOR ((struct ohci_hcor *)(uintptr_t)(bus->hcd.reg_base + CONFIG_USB_OHCI_HCOR_OFFSET))

#define OHCI_PTR2ADDR(x) ((uint32_t)(uintptr_t)(x) & ~0x0F)
#define OHCI_ADDR2ED(x)  ((struct ohci_ed_hw *)(uintptr_t)((uint32_t)(x) & ~0x0F))
#define OHCI_ADDR2TD(x) ((struct ohci_td_hw *)(uintptr_t)((uint32_t)(x) & ~0x0F))

#ifndef CONFIG_USB_OHCI_ED_NUM
#define CONFIG_USB_OHCI_ED_NUM CONFIG_USBHOST_PIPE_NUM
#endif
#ifndef CONFIG_USB_OHCI_TD_NUM
#define CONFIG_USB_OHCI_TD_NUM 3
#endif

struct ohci_ed_hw;
struct ohci_td_hw {
    struct ohci_gtd hw;
    struct usbh_urb *urb;
    uint32_t buf_start;
    uint32_t length;
} __attribute__((aligned(32))); /* min is 16bytes, we use 32 for cacheline */

struct ohci_ed_hw {
    struct ohci_ed hw;
    struct ohci_td_hw td_pool[CONFIG_USB_OHCI_TD_NUM];
    uint32_t td_count;
    uint8_t ed_type;
    usb_osal_sem_t waitsem;
} __attribute__((aligned(32))); /* min is 16bytes, we use 32 for cacheline */

struct ohci_hcd {
    bool ohci_ed_used[CONFIG_USB_OHCI_ED_NUM];
    uint8_t n_ports;
};

int ohci_init(struct usbh_bus *bus);
int ohci_deinit(struct usbh_bus *bus);
uint16_t ohci_get_frame_number(struct usbh_bus *bus);
int ohci_roothub_control(struct usbh_bus *bus, struct usb_setup_packet *setup, uint8_t *buf);
int ohci_submit_urb(struct usbh_urb *urb);
int ohci_kill_urb(struct usbh_urb *urb);

void OHCI_IRQHandler(uint8_t busid);

#endif