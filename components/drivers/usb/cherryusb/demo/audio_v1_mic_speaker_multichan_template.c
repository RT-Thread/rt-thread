/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_audio.h"

#define USING_FEEDBACK 0

#define USBD_VID           0xffff
#define USBD_PID           0xffff
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#ifdef CONFIG_USB_HS
#define EP_INTERVAL               0x04
#define FEEDBACK_ENDP_PACKET_SIZE 0x04
#else
#define EP_INTERVAL               0x01
#define FEEDBACK_ENDP_PACKET_SIZE 0x03
#endif

#define AUDIO_IN_EP           0x81
#define AUDIO_OUT_EP          0x02
#define AUDIO_OUT_FEEDBACK_EP 0x83

#define AUDIO_IN_FU_ID  0x02
#define AUDIO_OUT_FU_ID 0x05

#define IN_CHANNEL_NUM 2

#if IN_CHANNEL_NUM == 1
#define INPUT_CTRL      0x03, 0x03
#define INPUT_CH_ENABLE 0x0001
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

#define OUT_CHANNEL_NUM 2

#if OUT_CHANNEL_NUM == 1
#define OUTPUT_CTRL      0x03, 0x03
#define OUTPUT_CH_ENABLE 0x0001
#elif OUT_CHANNEL_NUM == 2
#define OUTPUT_CTRL      0x03, 0x03, 0x03
#define OUTPUT_CH_ENABLE 0x0003
#elif OUT_CHANNEL_NUM == 3
#define OUTPUT_CTRL      0x03, 0x03, 0x03, 0x03
#define OUTPUT_CH_ENABLE 0x0007
#elif OUT_CHANNEL_NUM == 4
#define OUTPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03
#define OUTPUT_CH_ENABLE 0x000f
#elif OUT_CHANNEL_NUM == 5
#define OUTPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03, 0x03
#define OUTPUT_CH_ENABLE 0x001f
#elif OUT_CHANNEL_NUM == 6
#define OUTPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
#define OUTPUT_CH_ENABLE 0x003F
#elif OUT_CHANNEL_NUM == 7
#define OUTPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
#define OUTPUT_CH_ENABLE 0x007f
#elif OUT_CHANNEL_NUM == 8
#define OUTPUT_CTRL      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
#define OUTPUT_CH_ENABLE 0x00ff
#endif

/* AUDIO Class Config */
#define AUDIO_SPEAKER_FREQ            16000U
#define AUDIO_SPEAKER_FRAME_SIZE_BYTE 2u
#define AUDIO_SPEAKER_RESOLUTION_BIT  16u
#define AUDIO_MIC_FREQ                16000U
#define AUDIO_MIC_FRAME_SIZE_BYTE     2u
#define AUDIO_MIC_RESOLUTION_BIT      16u

#define AUDIO_SAMPLE_FREQ(frq) (uint8_t)(frq), (uint8_t)((frq >> 8)), (uint8_t)((frq >> 16))

/* AudioFreq * DataSize (2 bytes) * NumChannels (Stereo: 2) */
#define AUDIO_OUT_PACKET ((uint32_t)((AUDIO_SPEAKER_FREQ * AUDIO_SPEAKER_FRAME_SIZE_BYTE * 2) / 1000))
/* 16bit(2 Bytes) 双声道(Mono:2) */
#define AUDIO_IN_PACKET ((uint32_t)((AUDIO_MIC_FREQ * AUDIO_MIC_FRAME_SIZE_BYTE * 2) / 1000))

#if USING_FEEDBACK == 0
#define USB_CONFIG_SIZE (unsigned long)(9 +                                                     \
                                        AUDIO_AC_DESCRIPTOR_LEN(2) +                            \
                                        AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +                   \
                                        AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(IN_CHANNEL_NUM, 1) +  \
                                        AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +                  \
                                        AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +                   \
                                        AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(OUT_CHANNEL_NUM, 1) + \
                                        AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +                  \
                                        AUDIO_AS_DESCRIPTOR_LEN(1) +                            \
                                        AUDIO_AS_DESCRIPTOR_LEN(1))
#else
#define USB_CONFIG_SIZE (unsigned long)(9 +                                                     \
                                        AUDIO_AC_DESCRIPTOR_LEN(2) +                            \
                                        AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +                   \
                                        AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(IN_CHANNEL_NUM, 1) +  \
                                        AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +                  \
                                        AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +                   \
                                        AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(OUT_CHANNEL_NUM, 1) + \
                                        AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +                  \
                                        AUDIO_AS_DESCRIPTOR_LEN(1) +                            \
                                        AUDIO_AS_FEEDBACK_DESCRIPTOR_LEN(1))
#endif

#define AUDIO_AC_SIZ (AUDIO_SIZEOF_AC_HEADER_DESC(2) +                        \
                      AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +                   \
                      AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(IN_CHANNEL_NUM, 1) +  \
                      AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +                  \
                      AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +                   \
                      AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(OUT_CHANNEL_NUM, 1) + \
                      AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC)

static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xef, 0x02, 0x01, USBD_VID, USBD_PID, 0x0001, 0x01)
};

static const uint8_t config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x03, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    AUDIO_AC_DESCRIPTOR_INIT(0x00, 0x03, AUDIO_AC_SIZ, 0x00, 0x01, 0x02),
    AUDIO_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(0x01, AUDIO_INTERM_MIC, IN_CHANNEL_NUM, INPUT_CH_ENABLE),
    AUDIO_AC_FEATURE_UNIT_DESCRIPTOR_INIT(AUDIO_IN_FU_ID, 0x01, 0x01, INPUT_CTRL),
    AUDIO_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(0x03, AUDIO_TERMINAL_STREAMING, AUDIO_IN_FU_ID),
    AUDIO_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(0x04, AUDIO_TERMINAL_STREAMING, OUT_CHANNEL_NUM, OUTPUT_CH_ENABLE),
    AUDIO_AC_FEATURE_UNIT_DESCRIPTOR_INIT(AUDIO_OUT_FU_ID, 0x04, 0x01, OUTPUT_CTRL),
    AUDIO_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(0x06, AUDIO_OUTTERM_SPEAKER, AUDIO_OUT_FU_ID),
    AUDIO_AS_DESCRIPTOR_INIT(0x01, 0x03, IN_CHANNEL_NUM, AUDIO_MIC_FRAME_SIZE_BYTE, AUDIO_MIC_RESOLUTION_BIT, AUDIO_IN_EP, 0x05, AUDIO_IN_PACKET,
                             EP_INTERVAL, AUDIO_SAMPLE_FREQ_3B(AUDIO_MIC_FREQ)),
#if USING_FEEDBACK == 0
    AUDIO_AS_DESCRIPTOR_INIT(0x02, 0x04, OUT_CHANNEL_NUM, AUDIO_SPEAKER_FRAME_SIZE_BYTE, AUDIO_SPEAKER_RESOLUTION_BIT, AUDIO_OUT_EP, 0x09, AUDIO_OUT_PACKET,
                             EP_INTERVAL, AUDIO_SAMPLE_FREQ_3B(AUDIO_SPEAKER_FREQ)),
#else
    AUDIO_AS_FEEDBACK_DESCRIPTOR_INIT(0x02, 0x04, OUT_CHANNEL_NUM, AUDIO_SPEAKER_FRAME_SIZE_BYTE, AUDIO_SPEAKER_RESOLUTION_BIT, AUDIO_OUT_EP, AUDIO_OUT_PACKET,
                                      EP_INTERVAL, AUDIO_OUT_FEEDBACK_EP, AUDIO_SAMPLE_FREQ_3B(AUDIO_SPEAKER_FREQ)),
#endif
};

static const uint8_t device_quality_descriptor[] = {
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
    0x00,
    0x00,
};

static const char *string_descriptors[] = {
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "CherryUSB",                  /* Manufacturer */
    "CherryUSB UAC DEMO",         /* Product */
    "2022123456",                 /* Serial Number */
};

static const uint8_t *device_descriptor_callback(uint8_t speed)
{
    return device_descriptor;
}

static const uint8_t *config_descriptor_callback(uint8_t speed)
{
    return config_descriptor;
}

static const uint8_t *device_quality_descriptor_callback(uint8_t speed)
{
    return device_quality_descriptor;
}

static const char *string_descriptor_callback(uint8_t speed, uint8_t index)
{
    if (index > 3) {
        return NULL;
    }
    return string_descriptors[index];
}

const struct usb_descriptor audio_v1_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback
};

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_buffer[AUDIO_OUT_PACKET];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t write_buffer[AUDIO_IN_PACKET];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t s_speaker_feedback_buffer[4];

volatile bool tx_flag = 0;
volatile bool rx_flag = 0;
volatile bool ep_tx_busy_flag = false;
volatile uint32_t s_mic_sample_rate;
volatile uint32_t s_speaker_sample_rate;

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
    if (intf == 1) {
        rx_flag = 1;
        /* setup first out ep read transfer */
        usbd_ep_start_read(busid, AUDIO_OUT_EP, read_buffer, AUDIO_OUT_PACKET);
#if USING_FEEDBACK == 1
        uint32_t feedback_value = AUDIO_FREQ_TO_FEEDBACK_FS(s_speaker_sample_rate);
        AUDIO_FEEDBACK_TO_BUF_FS(s_speaker_feedback_buffer, feedback_value); /* uac1 can only use 10.14 */
        usbd_ep_start_write(busid, AUDIO_OUT_FEEDBACK_EP, s_speaker_feedback_buffer, FEEDBACK_ENDP_PACKET_SIZE);
#endif
        USB_LOG_INFO("OPEN1\r\n");
    } else {
        tx_flag = 1;
        ep_tx_busy_flag = false;
        USB_LOG_INFO("OPEN2\r\n");
    }
}

void usbd_audio_close(uint8_t busid, uint8_t intf)
{
    if (intf == 1) {
        rx_flag = 0;
        USB_LOG_INFO("CLOSE1\r\n");
    } else {
        tx_flag = 0;
        ep_tx_busy_flag = false;
        USB_LOG_INFO("CLOSE2\r\n");
    }
}

void usbd_audio_set_sampling_freq(uint8_t busid, uint8_t ep, uint32_t sampling_freq)
{
    if (ep == AUDIO_OUT_EP) {
        s_speaker_sample_rate = sampling_freq;
    } else if (ep == AUDIO_IN_EP) {
        s_mic_sample_rate = sampling_freq;
    }
}

uint32_t usbd_audio_get_sampling_freq(uint8_t busid, uint8_t ep)
{
    (void)busid;

    uint32_t freq = 0;

    if (ep == AUDIO_OUT_EP) {
        freq = s_speaker_sample_rate;
    } else if (ep == AUDIO_IN_EP) {
        freq = s_mic_sample_rate;
    }

    return freq;
}

void usbd_audio_out_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual out len:%d\r\n", (unsigned int)nbytes);
    usbd_ep_start_read(busid, AUDIO_OUT_EP, read_buffer, AUDIO_OUT_PACKET);
}

void usbd_audio_in_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual in len:%d\r\n", (unsigned int)nbytes);
    ep_tx_busy_flag = false;
}

#if USING_FEEDBACK == 1
void usbd_audio_iso_out_feedback_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual feedback len:%d\r\n", (unsigned int)nbytes);
    uint32_t feedback_value = AUDIO_FREQ_TO_FEEDBACK_FS(s_speaker_sample_rate);
    AUDIO_FEEDBACK_TO_BUF_FS(s_speaker_feedback_buffer, feedback_value);
    usbd_ep_start_write(busid, AUDIO_OUT_FEEDBACK_EP, s_speaker_feedback_buffer, FEEDBACK_ENDP_PACKET_SIZE);
}
#endif

static struct usbd_endpoint audio_in_ep = {
    .ep_cb = usbd_audio_in_callback,
    .ep_addr = AUDIO_IN_EP
};

static struct usbd_endpoint audio_out_ep = {
    .ep_cb = usbd_audio_out_callback,
    .ep_addr = AUDIO_OUT_EP
};

#if USING_FEEDBACK == 1
static struct usbd_endpoint audio_out_feedback_ep = {
    .ep_cb = usbd_audio_iso_out_feedback_callback,
    .ep_addr = AUDIO_OUT_FEEDBACK_EP
};
#endif

struct usbd_interface intf0;
struct usbd_interface intf1;
struct usbd_interface intf2;

struct audio_entity_info audio_entity_table[] = {
    { .bEntityId = AUDIO_IN_FU_ID,
      .bDescriptorSubtype = AUDIO_CONTROL_FEATURE_UNIT,
      .ep = AUDIO_IN_EP },
    { .bEntityId = AUDIO_OUT_FU_ID,
      .bDescriptorSubtype = AUDIO_CONTROL_FEATURE_UNIT,
      .ep = AUDIO_OUT_EP },
};

// In windows, audio driver cannot remove auto, so when you modify any descriptor information, please modify string descriptors too.

void audio_v1_init(uint8_t busid, uintptr_t reg_base)
{
    usbd_desc_register(busid, &audio_v1_descriptor);

    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf0, 0x0100, audio_entity_table, 2));
    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf1, 0x0100, audio_entity_table, 2));
    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf2, 0x0100, audio_entity_table, 2));
    usbd_add_endpoint(busid, &audio_in_ep);
    usbd_add_endpoint(busid, &audio_out_ep);
#if USING_FEEDBACK == 1
    usbd_add_endpoint(busid, &audio_out_feedback_ep);
#endif
    usbd_initialize(busid, reg_base, usbd_event_handler);
}

void audio_v1_test(uint8_t busid)
{
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
