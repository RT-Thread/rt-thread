/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026/06/10     Tim          first version 
 */
#include "usbd_core.h"
#include "usbd_cdc_acm.h"

#define RT1180_CDC_IN_EP             0x81
#define RT1180_CDC_OUT_EP            0x02
#define RT1180_CDC_INT_EP            0x83
#define RT1180_CDC_INTF_NUM          0x00
#define RT1180_CDC_MSOS_VENDOR_CODE  0x17

#define RT1180_USBD_VID              0xFFFF
#define RT1180_USBD_PID              0xFFFF
#define RT1180_USBD_MAX_POWER        100

#define RT1180_USB_CONFIG_SIZE       (9 + CDC_ACM_DESCRIPTOR_LEN)

#ifdef CONFIG_USB_HS
#define RT1180_CDC_MAX_MPS           512
#else
#define RT1180_CDC_MAX_MPS           64
#endif

static const uint8_t rt1180_cdc_device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01,
                               RT1180_USBD_VID, RT1180_USBD_PID, 0x0100, 0x01)
};

static const uint8_t rt1180_cdc_config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(RT1180_USB_CONFIG_SIZE, 0x02, 0x01,
                               USB_CONFIG_BUS_POWERED, RT1180_USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(RT1180_CDC_INTF_NUM, RT1180_CDC_INT_EP,
                            RT1180_CDC_OUT_EP, RT1180_CDC_IN_EP,
                            RT1180_CDC_MAX_MPS, 0x02)
};

static const uint8_t rt1180_cdc_device_quality_descriptor[] = {
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x00,
    0x00,
};

static const char *rt1180_cdc_string_descriptors[] = {
    (const char[]){ 0x09, 0x04 },
    "CherryUSB",
    "RT1180 CDC ACM",
    "2022123456",
};

static const uint8_t rt1180_cdc_msos_string_descriptor[] = {
    USB_MSOSV1_STRING_DESCRIPTOR_INIT(RT1180_CDC_MSOS_VENDOR_CODE)
};

static const uint8_t rt1180_cdc_msos_compat_id_descriptor[] = {
    USB_MSOSV1_COMP_ID_HEADER_DESCRIPTOR_INIT(0)
};

static const uint8_t rt1180_cdc_msos_properties_descriptor[] = {
    0x0a, 0x00, 0x00, 0x00,
    0x00, 0x01,
    0x05, 0x00,
    0x00, 0x00,
};

static const uint8_t *rt1180_cdc_msos_properties[] = {
    rt1180_cdc_msos_properties_descriptor,
    rt1180_cdc_msos_properties_descriptor,
};

static const struct usb_msosv1_descriptor rt1180_cdc_msosv1_descriptor = {
    .string = rt1180_cdc_msos_string_descriptor,
    .vendor_code = RT1180_CDC_MSOS_VENDOR_CODE,
    .compat_id = rt1180_cdc_msos_compat_id_descriptor,
    .comp_id_property = rt1180_cdc_msos_properties,
};

static const uint8_t *rt1180_cdc_device_descriptor_callback(uint8_t speed)
{
    (void)speed;
    return rt1180_cdc_device_descriptor;
}

static const uint8_t *rt1180_cdc_config_descriptor_callback(uint8_t speed)
{
    (void)speed;
    return rt1180_cdc_config_descriptor;
}

static const uint8_t *rt1180_cdc_device_quality_descriptor_callback(uint8_t speed)
{
    (void)speed;
    return rt1180_cdc_device_quality_descriptor;
}

static const char *rt1180_cdc_string_descriptor_callback(uint8_t speed, uint8_t index)
{
    (void)speed;

    if (index > 3)
    {
        return NULL;
    }

    return rt1180_cdc_string_descriptors[index];
}

static const struct usb_descriptor rt1180_cdc_descriptor = {
    .device_descriptor_callback = rt1180_cdc_device_descriptor_callback,
    .config_descriptor_callback = rt1180_cdc_config_descriptor_callback,
    .device_quality_descriptor_callback = rt1180_cdc_device_quality_descriptor_callback,
    .string_descriptor_callback = rt1180_cdc_string_descriptor_callback,
    .msosv1_descriptor = &rt1180_cdc_msosv1_descriptor,
};

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t rt1180_cdc_read_buffer[2048];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t rt1180_cdc_write_buffer[2048];

static void rt1180_cdc_start_read(uint8_t busid)
{
    usbd_ep_start_read(busid, RT1180_CDC_OUT_EP,
                       rt1180_cdc_read_buffer,
                       sizeof(rt1180_cdc_read_buffer));
}

static void rt1180_cdc_event_handler(uint8_t busid, uint8_t event)
{
    switch (event)
    {
    case USBD_EVENT_CONFIGURED:
        rt1180_cdc_start_read(busid);
        break;
    default:
        break;
    }
}

static void rt1180_cdc_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)ep;

    USB_LOG_RAW("actual out len:%d\r\n", (unsigned int)nbytes);

    if (nbytes == 0)
    {
        rt1180_cdc_start_read(busid);
        return;
    }

    if (nbytes > sizeof(rt1180_cdc_write_buffer))
    {
        nbytes = sizeof(rt1180_cdc_write_buffer);
    }

    memcpy(rt1180_cdc_write_buffer, rt1180_cdc_read_buffer, nbytes);

    if (usbd_ep_start_write(busid, RT1180_CDC_IN_EP, rt1180_cdc_write_buffer, nbytes) != 0)
    {
        rt1180_cdc_start_read(busid);
    }
}

static void rt1180_cdc_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual in len:%d\r\n", (unsigned int)nbytes);

    if ((nbytes % usbd_get_ep_mps(busid, ep)) == 0 && nbytes)
    {
        usbd_ep_start_write(busid, RT1180_CDC_IN_EP, NULL, 0);
    }
    else
    {
        rt1180_cdc_start_read(busid);
    }
}

static struct usbd_endpoint rt1180_cdc_out_ep = {
    .ep_addr = RT1180_CDC_OUT_EP,
    .ep_cb = rt1180_cdc_bulk_out,
};

static struct usbd_endpoint rt1180_cdc_in_ep = {
    .ep_addr = RT1180_CDC_IN_EP,
    .ep_cb = rt1180_cdc_bulk_in,
};

static struct usbd_interface rt1180_cdc_intf0;
static struct usbd_interface rt1180_cdc_intf1;

void rt1180_cdc_acm_init(uint8_t busid, uintptr_t reg_base)
{
    usbd_desc_register(busid, &rt1180_cdc_descriptor);
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &rt1180_cdc_intf0));
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &rt1180_cdc_intf1));
    usbd_add_endpoint(busid, &rt1180_cdc_out_ep);
    usbd_add_endpoint(busid, &rt1180_cdc_in_ep);
    usbd_initialize(busid, reg_base, rt1180_cdc_event_handler);
}
