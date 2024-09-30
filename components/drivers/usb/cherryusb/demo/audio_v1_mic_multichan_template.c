/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_audio.h"

#define USBD_VID           0xffff
#define USBD_PID           0xffff
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#ifdef CONFIG_USB_HS
#define EP_INTERVAL 0x04
#else
#define EP_INTERVAL 0x01
#endif

#define AUDIO_IN_EP 0x81

#define AUDIO_IN_FU_ID 0x02

/* AUDIO Class Config */
#define AUDIO_FREQ 16000U

#define IN_CHANNEL_NUM 1

#if IN_CHANNEL_NUM == 1
#define INPUT_CTRL      0x03, 0x03
#define INPUT_CH_ENABLE 0x0000
#elif IN_CHANNEL_NUM == 2
#define INPUT_CTRL      0x03, 0x03, 0x03
#define INPUT_CH_ENABLE 0x0003
#elif IN_CHANNEL_NUM == 3
#define INPUT_CTRL      0x03, 0x03, 0x03, 0x03
#define INPUT_CH_ENABLE 0x0007
#elif IN_CHANNEL_NUM == 4
#define INPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03
#define INPUT_CH_ENABLE 0x000f
#elif IN_CHANNEL_NUM == 5
#define INPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03, 0x03
#define INPUT_CH_ENABLE 0x001f
#elif IN_CHANNEL_NUM == 6
#define INPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
#define INPUT_CH_ENABLE 0x003F
#elif IN_CHANNEL_NUM == 7
#define INPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
#define INPUT_CH_ENABLE 0x007f
#elif IN_CHANNEL_NUM == 8
#define INPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
#define INPUT_CH_ENABLE 0x00ff
#endif

/* AudioFreq * DataSize (2 bytes) * NumChannels (Stereo: 1) */
/* 16bit(2 Bytes) 单声道(Mono:1) */
#define AUDIO_IN_PACKET ((uint32_t)((AUDIO_FREQ * 2 * IN_CHANNEL_NUM) / 1000))

#define USB_AUDIO_CONFIG_DESC_SIZ (unsigned long)(9 +                                                    \
                                                  AUDIO_AC_DESCRIPTOR_INIT_LEN(1) +                      \
                                                  AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +                  \
                                                  AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(IN_CHANNEL_NUM, 1) + \
                                                  AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +                 \
                                                  AUDIO_AS_DESCRIPTOR_INIT_LEN(1))

#define AUDIO_AC_SIZ (AUDIO_SIZEOF_AC_HEADER_DESC(1) +                       \
                      AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +                  \
                      AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(IN_CHANNEL_NUM, 1) + \
                      AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC)

const uint8_t audio_v1_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xef, 0x02, 0x01, USBD_VID, USBD_PID, 0x0001, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_AUDIO_CONFIG_DESC_SIZ, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    AUDIO_AC_DESCRIPTOR_INIT(0x00, 0x02, AUDIO_AC_SIZ, 0x00, 0x01),
    AUDIO_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(0x01, AUDIO_INTERM_MIC, IN_CHANNEL_NUM, INPUT_CH_ENABLE),
    AUDIO_AC_FEATURE_UNIT_DESCRIPTOR_INIT(AUDIO_IN_FU_ID, 0x01, 0x01, INPUT_CTRL),
    AUDIO_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(0x03, AUDIO_TERMINAL_STREAMING, AUDIO_IN_FU_ID),
    AUDIO_AS_DESCRIPTOR_INIT(0x01, 0x03, IN_CHANNEL_NUM, 2, 16, AUDIO_IN_EP, 0x05, AUDIO_IN_PACKET, EP_INTERVAL, AUDIO_SAMPLE_FREQ_3B(AUDIO_FREQ)),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x26,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ' ', 0x00,                  /* wcChar9 */
    'U', 0x00,                  /* wcChar10 */
    'A', 0x00,                  /* wcChar11 */
    'C', 0x00,                  /* wcChar12 */
    ' ', 0x00,                  /* wcChar13 */
    'D', 0x00,                  /* wcChar14 */
    'E', 0x00,                  /* wcChar15 */
    'M', 0x00,                  /* wcChar16 */
    'O', 0x00,                  /* wcChar17 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x16,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '1', 0x00,                  /* wcChar3 */
    '0', 0x00,                  /* wcChar4 */
    '3', 0x00,                  /* wcChar5 */
    '1', 0x00,                  /* wcChar6 */
    '0', 0x00,                  /* wcChar7 */
    '0', 0x00,                  /* wcChar8 */
    '0' + IN_CHANNEL_NUM, 0x00, /* wcChar9 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
#endif
    0x00
};

volatile bool tx_flag = 0;
volatile bool ep_tx_busy_flag = false;

static void usbd_event_handler(uint8_t busid, uint8_t event)
{
    switch (event) {
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

void usbd_audio_open(uint8_t busid, uint8_t intf)
{
    tx_flag = 1;
    ep_tx_busy_flag = false;
    USB_LOG_RAW("OPEN\r\n");
}

void usbd_audio_close(uint8_t busid, uint8_t intf)
{
    USB_LOG_RAW("CLOSE\r\n");
    ep_tx_busy_flag = false;
    tx_flag = 0;
}

void usbd_audio_iso_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual in len:%d\r\n", nbytes);
    ep_tx_busy_flag = false;
}

static struct usbd_endpoint audio_in_ep = {
    .ep_cb = usbd_audio_iso_callback,
    .ep_addr = AUDIO_IN_EP
};

struct usbd_interface intf0;
struct usbd_interface intf1;

struct audio_entity_info audio_entity_table[] = {
    { .bEntityId = AUDIO_IN_FU_ID,
      .bDescriptorSubtype = AUDIO_CONTROL_FEATURE_UNIT,
      .ep = AUDIO_IN_EP },
};

void audio_v1_init(uint8_t busid, uintptr_t reg_base)
{
    usbd_desc_register(busid, audio_v1_descriptor);
    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf0, 0x0100, audio_entity_table, 1));
    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf1, 0x0100, audio_entity_table, 1));
    usbd_add_endpoint(busid, &audio_in_ep);

    usbd_initialize(busid, reg_base, usbd_event_handler);
}

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t write_buffer[AUDIO_IN_PACKET];

void audio_test(uint8_t busid)
{
    while (1) {
        if (tx_flag) {
            memset(write_buffer, 'a', AUDIO_IN_PACKET);
            ep_tx_busy_flag = true;
            usbd_ep_start_write(busid, AUDIO_IN_EP, write_buffer, AUDIO_IN_PACKET);
            while (ep_tx_busy_flag) {
                if (tx_flag == false) {
                    break;
                }
            }
        }
    }
}
