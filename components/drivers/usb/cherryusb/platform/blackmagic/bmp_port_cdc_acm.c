/*
 * Copyright (c) 2025, A_Stupid_Liberal
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "usbd_core.h"
#include "usbd_cdc_acm.h"
#include "general.h"
#include "gdb_if.h"
#include "hpm_l1c_drv.h"

#define CDC_IN_EP  0x81
#define CDC_OUT_EP 0x01
#define CDC_INT_EP 0x83

#define CDC_MAX_PACKET_SIZE 512

#ifdef CONFIG_USB_HS
#if CDC_MAX_PACKET_SIZE != 512
#error "CDC_MAX_PACKET_SIZE must be 512 in hs"
#endif
#else
#if CDC_MAX_PACKET_SIZE != 64
#error "CDC_MAX_PACKET_SIZE must be 64 in fs"
#endif
#endif

/*!< config descriptor size */
#define USB_CONFIG_SIZE (9 + CDC_ACM_DESCRIPTOR_LEN)

static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01)
};

static const uint8_t config_descriptor_hs[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, USB_BULK_EP_MPS_HS, 0x02),
};

static const uint8_t config_descriptor_fs[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, USB_BULK_EP_MPS_FS, 0x02),
};

static const uint8_t device_quality_descriptor[] = {
    USB_DEVICE_QUALIFIER_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, 0x01),
};

static const uint8_t other_speed_config_descriptor_hs[] = {
    USB_OTHER_SPEED_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, USB_BULK_EP_MPS_FS, 0x02),
};

static const uint8_t other_speed_config_descriptor_fs[] = {
    USB_OTHER_SPEED_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, USB_BULK_EP_MPS_HS, 0x02),
};

static const char *string_descriptors[] = {
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "CherryUSB",                  /* Manufacturer */
    "CherryUSB BMP DEMO",         /* Product */
    "20250501",                   /* Serial Number */
};

static const uint8_t *device_descriptor_callback(uint8_t speed)
{
    (void)speed;

    return device_descriptor;
}

static const uint8_t *config_descriptor_callback(uint8_t speed)
{
    if (speed == USB_SPEED_HIGH) {
        return config_descriptor_hs;
    } else if (speed == USB_SPEED_FULL) {
        return config_descriptor_fs;
    } else {
        return NULL;
    }
}

static const uint8_t *device_quality_descriptor_callback(uint8_t speed)
{
    (void)speed;

    return device_quality_descriptor;
}

static const uint8_t *other_speed_config_descriptor_callback(uint8_t speed)
{
    if (speed == USB_SPEED_HIGH) {
        return other_speed_config_descriptor_hs;
    } else if (speed == USB_SPEED_FULL) {
        return other_speed_config_descriptor_fs;
    } else {
        return NULL;
    }
}

static const char *string_descriptor_callback(uint8_t speed, uint8_t index)
{
    (void)speed;

    if (index >= (sizeof(string_descriptors) / sizeof(char *))) {
        return NULL;
    }
    return string_descriptors[index];
}

const struct usb_descriptor cdc_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .other_speed_descriptor_callback = other_speed_config_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback,
};

#define USB_RX_BUFFER_SIZE 16384
__attribute__((aligned(64))) uint8_t g_usb_write_buffer[USB_RX_BUFFER_SIZE];
__attribute__((aligned(64))) uint8_t g_usb_read_buffer[USB_RX_BUFFER_SIZE];

volatile bool g_usb_tx_busy_flag = false;
volatile uint32_t g_usb_tx_count = 0;
volatile uint32_t g_usb_rx_count = 0;
volatile uint32_t g_usb_rx_offset = 0;

static void usbd_event_handler(uint8_t busid, uint8_t event)
{
    switch (event) {
        case USBD_EVENT_RESET:
            g_usb_tx_busy_flag = false;
            g_usb_rx_offset = 0;
            g_usb_rx_count = 0;
            g_usb_tx_count = 0;
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            g_usb_tx_busy_flag = false;
            g_usb_rx_offset = 0;
            g_usb_rx_count = 0;
            g_usb_tx_count = 0;
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:
            /* setup first out ep read transfer */
            usbd_ep_start_read(busid, CDC_OUT_EP, g_usb_read_buffer, USB_RX_BUFFER_SIZE);
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

void usbd_cdc_acm_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)busid;

    usb_dcache_invalidate((uint32_t)g_usb_read_buffer, USB_ALIGN_UP(nbytes, 64));
    g_usb_rx_count = nbytes;
    g_usb_rx_offset = 0;
}

void usbd_cdc_acm_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)busid;

    if ((nbytes % usbd_get_ep_mps(busid, ep)) == 0 && nbytes) {
        /* send zlp */
        usbd_ep_start_write(busid, CDC_IN_EP, NULL, 0);
    } else {
        g_usb_tx_busy_flag = false;
    }
}

/*!< endpoint call back */
struct usbd_endpoint cdc_out_ep = {
    .ep_addr = CDC_OUT_EP,
    .ep_cb = usbd_cdc_acm_bulk_out
};

struct usbd_endpoint cdc_in_ep = {
    .ep_addr = CDC_IN_EP,
    .ep_cb = usbd_cdc_acm_bulk_in
};

static struct usbd_interface intf0;
static struct usbd_interface intf1;

/* function ------------------------------------------------------------------*/

void cdc_acm_init(uint8_t busid, uint32_t reg_base)
{
    usbd_desc_register(busid, &cdc_descriptor);
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &intf0));
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &intf1));
    usbd_add_endpoint(busid, &cdc_out_ep);
    usbd_add_endpoint(busid, &cdc_in_ep);
    usbd_initialize(busid, reg_base, usbd_event_handler);
}

volatile bool dtr_enable = false;

void usbd_cdc_acm_set_dtr(uint8_t busid, uint8_t intf, bool dtr)
{
    if (dtr) {
        //printf("remote attach \r\n");
    } else {
        //printf("remote detach \r\n");
    }

    dtr_enable = dtr;
}

void gdb_if_putchar(const char c, const bool flush)
{
    g_usb_write_buffer[g_usb_tx_count++] = c;

    if (flush) {
        g_usb_tx_busy_flag = true;
        usb_dcache_clean((uint32_t)g_usb_write_buffer, USB_ALIGN_UP(g_usb_tx_count, 64));
        usbd_ep_start_write(0, CDC_IN_EP, (uint8_t *)core_local_mem_to_sys_address(0, (uint32_t)g_usb_write_buffer), g_usb_tx_count);
        while (g_usb_tx_busy_flag) {
        }
        g_usb_tx_count = 0;
    }
}

void gdb_if_flush(const bool force)
{
    g_usb_tx_busy_flag = true;
    usb_dcache_clean((uint32_t)g_usb_write_buffer, USB_ALIGN_UP(g_usb_tx_count, 64));
    usbd_ep_start_write(0, CDC_IN_EP, (uint8_t *)core_local_mem_to_sys_address(0, (uint32_t)g_usb_write_buffer), g_usb_tx_count);
    while (g_usb_tx_busy_flag) {
    }
    g_usb_tx_count = 0;
}

static int __gdb_if_getchar(void)
{
    if (dtr_enable == false) {
        return '\04';
    }

    if (g_usb_rx_count > 0) {
        if (g_usb_rx_offset < g_usb_rx_count) {
            return g_usb_read_buffer[g_usb_rx_offset++];
        } else {
            g_usb_rx_count = 0;
            /* setup first out ep read transfer */
            usbd_ep_start_read(0, CDC_OUT_EP, g_usb_read_buffer, USB_RX_BUFFER_SIZE);
            return -1;
        }
    } else {
        return -1;
    }
}

char gdb_if_getchar(void)
{
    int c;

    while ((c = __gdb_if_getchar()) == -1) {
    }

    return (char)c;
}

char gdb_if_getchar_to(const uint32_t timeout)
{
    int c = 0;
    platform_timeout_s receive_timeout;
    platform_timeout_set(&receive_timeout, timeout);

    /* Wait while we need more data or until the timeout expires */
    while (!platform_timeout_is_expired(&receive_timeout)) {
        c = __gdb_if_getchar();
        if (c != -1) {
            return (char)c;
        }
    }
    return -1;
}