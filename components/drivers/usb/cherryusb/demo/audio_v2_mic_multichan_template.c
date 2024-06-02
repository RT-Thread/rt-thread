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

#define AUDIO_IN_CLOCK_ID 0x01
#define AUDIO_IN_FU_ID    0x03

#define AUDIO_FREQ      48000
#define HALF_WORD_BYTES 2  //2 half word (one channel)
#define SAMPLE_BITS     16 //16 bit per channel

#define BMCONTROL (AUDIO_V2_FU_CONTROL_MUTE | AUDIO_V2_FU_CONTROL_VOLUME)

#define IN_CHANNEL_NUM 2

#if IN_CHANNEL_NUM == 1
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x00000000
#elif IN_CHANNEL_NUM == 2
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x00000003
#elif IN_CHANNEL_NUM == 3
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x00000007
#elif IN_CHANNEL_NUM == 4
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x0000000f
#elif IN_CHANNEL_NUM == 5
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x0000001f
#elif IN_CHANNEL_NUM == 6
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x0000003F
#elif IN_CHANNEL_NUM == 7
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x0000007f
#elif IN_CHANNEL_NUM == 8
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x000000ff
#endif

#define AUDIO_IN_PACKET ((uint32_t)((AUDIO_FREQ * HALF_WORD_BYTES * IN_CHANNEL_NUM) / 1000))

#define USB_AUDIO_CONFIG_DESC_SIZ (9 +                                                    \
                                   AUDIO_V2_AC_DESCRIPTOR_INIT_LEN +                      \
                                   AUDIO_V2_SIZEOF_AC_CLOCK_SOURCE_DESC +                 \
                                   AUDIO_V2_SIZEOF_AC_INPUT_TERMINAL_DESC +               \
                                   AUDIO_V2_SIZEOF_AC_FEATURE_UNIT_DESC(IN_CHANNEL_NUM) + \
                                   AUDIO_V2_SIZEOF_AC_OUTPUT_TERMINAL_DESC +              \
                                   AUDIO_V2_AS_DESCRIPTOR_INIT_LEN)

#define AUDIO_AC_SIZ (AUDIO_V2_SIZEOF_AC_HEADER_DESC +                       \
                      AUDIO_V2_SIZEOF_AC_CLOCK_SOURCE_DESC +                 \
                      AUDIO_V2_SIZEOF_AC_INPUT_TERMINAL_DESC +               \
                      AUDIO_V2_SIZEOF_AC_FEATURE_UNIT_DESC(IN_CHANNEL_NUM) + \
                      AUDIO_V2_SIZEOF_AC_OUTPUT_TERMINAL_DESC)

const uint8_t audio_v2_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0001, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_AUDIO_CONFIG_DESC_SIZ, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    AUDIO_V2_AC_DESCRIPTOR_INIT(0x00, 0x02, AUDIO_AC_SIZ, AUDIO_CATEGORY_MICROPHONE, 0x00, 0x00),
    AUDIO_V2_AC_CLOCK_SOURCE_DESCRIPTOR_INIT(0x01, 0x03, 0x03),
    AUDIO_V2_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(0x02, AUDIO_INTERM_MIC, 0x01, IN_CHANNEL_NUM, INPUT_CH_ENABLE, 0x0000),
    AUDIO_V2_AC_FEATURE_UNIT_DESCRIPTOR_INIT(0x03, 0x02, INPUT_CTRL),
    AUDIO_V2_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(0x04, AUDIO_TERMINAL_STREAMING, 0x03, 0x01, 0x0000),
    AUDIO_V2_AS_DESCRIPTOR_INIT(0x01, 0x04, IN_CHANNEL_NUM, INPUT_CH_ENABLE, HALF_WORD_BYTES, SAMPLE_BITS, AUDIO_IN_EP, 0x05, (AUDIO_IN_PACKET + 4), EP_INTERVAL),
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
    '4', 0x00,                  /* wcChar9 */
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

static const uint8_t mic_default_sampling_freq_table[] = {
    AUDIO_SAMPLE_FREQ_NUM(1),
    AUDIO_SAMPLE_FREQ_4B(16000),
    AUDIO_SAMPLE_FREQ_4B(16000),
    AUDIO_SAMPLE_FREQ_4B(0x00)
};

volatile bool tx_flag = 0;

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
    USB_LOG_RAW("OPEN\r\n");
}

void usbd_audio_close(uint8_t busid, uint8_t intf)
{
    USB_LOG_RAW("CLOSE\r\n");
    tx_flag = 0;
}

void usbd_audio_get_sampling_freq_table(uint8_t busid, uint8_t ep, uint8_t **sampling_freq_table)
{
    if (ep == AUDIO_IN_EP) {
        *sampling_freq_table = (uint8_t *)mic_default_sampling_freq_table;
    }
}

void usbd_audio_iso_in_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
}

static struct usbd_endpoint audio_in_ep = {
    .ep_cb = usbd_audio_iso_in_callback,
    .ep_addr = AUDIO_IN_EP
};

struct usbd_interface intf0;
struct usbd_interface intf1;

struct audio_entity_info audio_entity_table[] = {
    { .bEntityId = AUDIO_IN_CLOCK_ID,
      .bDescriptorSubtype = AUDIO_CONTROL_CLOCK_SOURCE,
      .ep = AUDIO_IN_EP },
    { .bEntityId = AUDIO_IN_FU_ID,
      .bDescriptorSubtype = AUDIO_CONTROL_FEATURE_UNIT,
      .ep = AUDIO_IN_EP },
};

void audio_v2_init(uint8_t busid, uint32_t reg_base)
{
    usbd_desc_register(busid, audio_v2_descriptor);
    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf0, 0x0200, audio_entity_table, 2));
    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf1, 0x0200, audio_entity_table, 2));
    usbd_add_endpoint(busid, &audio_in_ep);

    usbd_initialize(busid, reg_base, usbd_event_handler);
}

void audio_v2_test(uint8_t busid)
{
    if (tx_flag) {
    }
}
