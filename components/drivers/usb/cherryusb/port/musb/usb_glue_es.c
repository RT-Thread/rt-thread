/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_config.h"
#include "stdint.h"
#include "usb_musb_reg.h"

#if CONFIG_USBDEV_EP_NUM != 6
#error es32 chips only support 6 endpoints
#endif

#if CONFIG_USBHOST_PIPE_NUM != 6
#error es32 chips only support 6 pipes
#endif

// clang-format off
static struct musb_fifo_cfg musb_device_table[] = {
{ .ep_num =  0, .style = FIFO_TXRX,   .maxpacket = 64, },
{ .ep_num =  1, .style = FIFO_TXRX,   .maxpacket = 1024, },
{ .ep_num =  2, .style = FIFO_TXRX,   .maxpacket = 512, },
{ .ep_num =  3, .style = FIFO_TXRX,   .maxpacket = 512, },
{ .ep_num =  4, .style = FIFO_TXRX,   .maxpacket = 512, },
{ .ep_num =  5, .style = FIFO_TXRX,   .maxpacket = 512, },
};

static struct musb_fifo_cfg musb_host_table[] = {
{ .ep_num =  0, .style = FIFO_TXRX,   .maxpacket = 64, },
{ .ep_num =  1, .style = FIFO_TXRX,   .maxpacket = 1024, },
{ .ep_num =  2, .style = FIFO_TXRX,   .maxpacket = 512, },
{ .ep_num =  3, .style = FIFO_TXRX,   .maxpacket = 512, },
{ .ep_num =  4, .style = FIFO_TXRX,   .maxpacket = 512, },
{ .ep_num =  5, .style = FIFO_TXRX,   .maxpacket = 512, },
};
// clang-format on

uint8_t usbd_get_musb_fifo_cfg(struct musb_fifo_cfg **cfg)
{
    *cfg = musb_device_table;
    return sizeof(musb_device_table) / sizeof(musb_device_table[0]);
}

uint8_t usbh_get_musb_fifo_cfg(struct musb_fifo_cfg **cfg)
{
    *cfg = musb_host_table;
    return sizeof(musb_host_table) / sizeof(musb_host_table[0]);
}

uint32_t usb_get_musb_ram_size(void)
{
    return 4096;
}