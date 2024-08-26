/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_video.h"
#include "usbd_audio.h"
#include "usbd_hid.h"
#include "cherryusb_mjpeg.h"

#define VIDEO_IN_EP  0x81
#define VIDEO_INT_EP 0x86

#ifdef CONFIG_USB_HS
#define MAX_PAYLOAD_SIZE  1024 // for high speed with one transcations every one micro frame
#define VIDEO_PACKET_SIZE (unsigned int)(((MAX_PAYLOAD_SIZE / 1)) | (0x00 << 11))

// #define MAX_PAYLOAD_SIZE  2048 // for high speed with two transcations every one micro frame
// #define VIDEO_PACKET_SIZE (unsigned int)(((MAX_PAYLOAD_SIZE / 2)) | (0x01 << 11))

// #define MAX_PAYLOAD_SIZE  3072 // for high speed with three transcations every one micro frame
// #define VIDEO_PACKET_SIZE (unsigned int)(((MAX_PAYLOAD_SIZE / 3)) | (0x02 << 11))

#else
#define MAX_PAYLOAD_SIZE  1020
#define VIDEO_PACKET_SIZE (unsigned int)(((MAX_PAYLOAD_SIZE / 1)) | (0x00 << 11))
#endif

#define WIDTH  (unsigned int)(640)
#define HEIGHT (unsigned int)(480)

#define CAM_FPS        (30)
#define INTERVAL       (unsigned long)(10000000 / CAM_FPS)
#define MIN_BIT_RATE   (unsigned long)(WIDTH * HEIGHT * 16 * CAM_FPS) //16 bit
#define MAX_BIT_RATE   (unsigned long)(WIDTH * HEIGHT * 16 * CAM_FPS)
#define MAX_FRAME_SIZE (unsigned long)(WIDTH * HEIGHT * 2)

#define VS_HEADER_SIZ (unsigned int)(VIDEO_SIZEOF_VS_INPUT_HEADER_DESC(1, 1) + VIDEO_SIZEOF_VS_FORMAT_MJPEG_DESC + VIDEO_SIZEOF_VS_FRAME_MJPEG_DESC(1))

#define USB_VIDEO_DESC_SIZ (unsigned long)(9 +                                       \
                                           VIDEO_VC_NOEP_DESCRIPTOR_LEN +            \
                                           9 +                                       \
                                           VS_HEADER_SIZ +                           \
                                           9 +                                       \
                                           7 +                                       \
                                           AUDIO_AC_DESCRIPTOR_INIT_LEN(2) +         \
                                           AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +     \
                                           AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(2, 1) + \
                                           AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +    \
                                           AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +     \
                                           AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(2, 1) + \
                                           AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +    \
                                           AUDIO_AS_DESCRIPTOR_INIT_LEN(1) +         \
                                           AUDIO_AS_DESCRIPTOR_INIT_LEN(1) +         \
                                           25)

#define USBD_VID           0xffff
#define USBD_PID           0xffff
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#ifdef CONFIG_USB_HS
#define EP_INTERVAL 0x04
#else
#define EP_INTERVAL 0x01
#endif

#define AUDIO_IN_EP  0x82
#define AUDIO_OUT_EP 0x03

#define AUDIO_IN_FU_ID  0x02
#define AUDIO_OUT_FU_ID 0x05

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

#define AUDIO_AC_SIZ (AUDIO_SIZEOF_AC_HEADER_DESC(2) +          \
                      AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +     \
                      AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(2, 1) + \
                      AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC +    \
                      AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC +     \
                      AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(2, 1) + \
                      AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC)

#define HID_INT_EP          0x84
#define HID_INT_EP_SIZE     8
#define HID_INT_EP_INTERVAL 10

#define HID_KEYBOARD_REPORT_DESC_SIZE 63

const uint8_t video_audio_hid_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xef, 0x02, 0x01, USBD_VID, USBD_PID, 0x0001, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_VIDEO_DESC_SIZ, 0x06, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    //VIDEO_VC_DESCRIPTOR_INIT(0x00, VIDEO_INT_EP, 0x0100, VIDEO_VC_TERMINAL_LEN, 48000000, 0x02),
    VIDEO_VC_NOEP_DESCRIPTOR_INIT(0x00, VIDEO_INT_EP, 0x0100, VIDEO_VC_TERMINAL_LEN, 48000000, 0x02),
    VIDEO_VS_DESCRIPTOR_INIT(0x01, 0x00, 0x00),
    VIDEO_VS_INPUT_HEADER_DESCRIPTOR_INIT(0x01, VS_HEADER_SIZ, VIDEO_IN_EP, 0x00),
    VIDEO_VS_FORMAT_MJPEG_DESCRIPTOR_INIT(0x01, 0x01),
    VIDEO_VS_FRAME_MJPEG_DESCRIPTOR_INIT(0x01, WIDTH, HEIGHT, MIN_BIT_RATE, MAX_BIT_RATE, MAX_FRAME_SIZE, DBVAL(INTERVAL), 0x01, DBVAL(INTERVAL)),
    VIDEO_VS_DESCRIPTOR_INIT(0x01, 0x01, 0x01),
    /* 1.2.2.2 Standard VideoStream Isochronous Video Data Endpoint Descriptor */
    USB_ENDPOINT_DESCRIPTOR_INIT(VIDEO_IN_EP, 0x05, VIDEO_PACKET_SIZE, 0x01),
    AUDIO_AC_DESCRIPTOR_INIT(0x02, 0x03, AUDIO_AC_SIZ, 0x00, 0x03, 0x04),
    AUDIO_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(0x01, AUDIO_INTERM_MIC, 0x02, 0x0003),
    AUDIO_AC_FEATURE_UNIT_DESCRIPTOR_INIT(0x02, 0x01, 0x01, 0x03, 0x00, 0x00),
    AUDIO_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(0x03, AUDIO_TERMINAL_STREAMING, 0x02),
    AUDIO_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(0x04, AUDIO_TERMINAL_STREAMING, 0x02, 0x0003),
    AUDIO_AC_FEATURE_UNIT_DESCRIPTOR_INIT(0x05, 0x04, 0x01, 0x03, 0x00, 0x00),
    AUDIO_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(0x06, AUDIO_OUTTERM_SPEAKER, 0x05),
    AUDIO_AS_DESCRIPTOR_INIT(0x03, 0x04, 0x02, AUDIO_SPEAKER_FRAME_SIZE_BYTE, AUDIO_SPEAKER_RESOLUTION_BIT, AUDIO_OUT_EP, 0x09, AUDIO_OUT_PACKET,
                             EP_INTERVAL, AUDIO_SAMPLE_FREQ_3B(AUDIO_SPEAKER_FREQ)),
    AUDIO_AS_DESCRIPTOR_INIT(0x04, 0x03, 0x02, AUDIO_MIC_FRAME_SIZE_BYTE, AUDIO_MIC_RESOLUTION_BIT, AUDIO_IN_EP, 0x05, AUDIO_IN_PACKET,
                             EP_INTERVAL, AUDIO_SAMPLE_FREQ_3B(AUDIO_MIC_FREQ)),
    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,                          /* bLength: Interface Descriptor size */
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType: Interface descriptor type */
    0x05,                          /* bInterfaceNumber: Number of Interface */
    0x00,                          /* bAlternateSetting: Alternate setting */
    0x01,                          /* bNumEndpoints */
    0x03,                          /* bInterfaceClass: HID */
    0x01,                          /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x01,                          /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,                             /* iInterface: Index of string descriptor */
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,                    /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE_HID, /* bDescriptorType: HID */
    0x11,                    /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,                          /* bCountryCode: Hardware target country */
    0x01,                          /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,                          /* bDescriptorType */
    HID_KEYBOARD_REPORT_DESC_SIZE, /* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Mouse endpoint ********************/
    /* 27 */
    0x07,                         /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT, /* bDescriptorType: */
    HID_INT_EP,                   /* bEndpointAddress: Endpoint Address (IN) */
    0x03,                         /* bmAttributes: Interrupt endpoint */
    HID_INT_EP_SIZE,              /* wMaxPacketSize: 4 Byte max */
    0x00,
    HID_INT_EP_INTERVAL, /* bInterval: Polling Interval */
    /* 34 */
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
    '4', 0x00,                  /* wcChar3 */
    '0', 0x00,                  /* wcChar4 */
    '3', 0x00,                  /* wcChar5 */
    '1', 0x00,                  /* wcChar6 */
    '0', 0x00,                  /* wcChar7 */
    '0', 0x00,                  /* wcChar8 */
    '0', 0x00,                  /* wcChar9 */
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

static const uint8_t hid_keyboard_report_desc[HID_KEYBOARD_REPORT_DESC_SIZE] = {
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x06, // USAGE (Keyboard)
    0xa1, 0x01, // COLLECTION (Application)
    0x05, 0x07, // USAGE_PAGE (Keyboard)
    0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0x01, // LOGICAL_MAXIMUM (1)
    0x75, 0x01, // REPORT_SIZE (1)
    0x95, 0x08, // REPORT_COUNT (8)
    0x81, 0x02, // INPUT (Data,Var,Abs)
    0x95, 0x01, // REPORT_COUNT (1)
    0x75, 0x08, // REPORT_SIZE (8)
    0x81, 0x03, // INPUT (Cnst,Var,Abs)
    0x95, 0x05, // REPORT_COUNT (5)
    0x75, 0x01, // REPORT_SIZE (1)
    0x05, 0x08, // USAGE_PAGE (LEDs)
    0x19, 0x01, // USAGE_MINIMUM (Num Lock)
    0x29, 0x05, // USAGE_MAXIMUM (Kana)
    0x91, 0x02, // OUTPUT (Data,Var,Abs)
    0x95, 0x01, // REPORT_COUNT (1)
    0x75, 0x03, // REPORT_SIZE (3)
    0x91, 0x03, // OUTPUT (Cnst,Var,Abs)
    0x95, 0x06, // REPORT_COUNT (6)
    0x75, 0x08, // REPORT_SIZE (8)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x05, 0x07, // USAGE_PAGE (Keyboard)
    0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65, // USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00, // INPUT (Data,Ary,Abs)
    0xc0        // END_COLLECTION
};

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t audio_read_buffer[AUDIO_OUT_PACKET];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t audio_write_buffer[AUDIO_IN_PACKET];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t video_packet_buffer[40 * 1024];

volatile bool video_tx_flag = 0;
volatile bool audio_tx_flag = 0;
volatile bool audio_rx_flag = 0;
volatile bool video_iso_tx_busy = false;
volatile bool audio_iso_tx_busy = false;

#define HID_STATE_IDLE 0
#define HID_STATE_BUSY 1

/*!< hid state ! Data can be sent only when state is idle  */
static volatile uint8_t hid_state = HID_STATE_IDLE;

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
            video_tx_flag = 0;
            audio_tx_flag = 0;
            audio_rx_flag = 0;
            video_iso_tx_busy = false;
            audio_iso_tx_busy = false;
            hid_state = HID_STATE_IDLE;
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

void usbd_video_open(uint8_t busid, uint8_t intf)
{
    if (intf == 1) {
        video_tx_flag = 1;
        USB_LOG_RAW("OPEN\r\n");
        video_iso_tx_busy = false;
    }
}
void usbd_video_close(uint8_t busid, uint8_t intf)
{
    if (intf == 1) {
        USB_LOG_RAW("CLOSE\r\n");
        video_tx_flag = 0;
        video_iso_tx_busy = false;
    }
}

void usbd_video_iso_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    //USB_LOG_RAW("actual in len:%d\r\n", nbytes);
    video_iso_tx_busy = false;
}

static struct usbd_endpoint video_in_ep = {
    .ep_cb = usbd_video_iso_callback,
    .ep_addr = VIDEO_IN_EP
};

void usbd_audio_open(uint8_t busid, uint8_t intf)
{
    if (intf == 3) {
        audio_rx_flag = 1;
        /* setup first out ep read transfer */
        usbd_ep_start_read(busid, AUDIO_OUT_EP, audio_read_buffer, AUDIO_OUT_PACKET);
        printf("OPEN1\r\n");
    } else if (intf == 4) {
        audio_tx_flag = 1;
        audio_iso_tx_busy = false;
        printf("OPEN2\r\n");
    }
}

void usbd_audio_close(uint8_t busid, uint8_t intf)
{
    if (intf == 3) {
        audio_rx_flag = 0;
        printf("CLOSE1\r\n");
    } else if (intf == 4) {
        audio_tx_flag = 0;
        audio_iso_tx_busy = false;
        printf("CLOSE2\r\n");
    }
}

void usbd_audio_out_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual out len:%d\r\n", nbytes);
    usbd_ep_start_read(busid, AUDIO_OUT_EP, audio_read_buffer, AUDIO_OUT_PACKET);
}

void usbd_audio_in_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual in len:%d\r\n", nbytes);
    audio_iso_tx_busy = false;
}

static struct usbd_endpoint audio_in_ep = {
    .ep_cb = usbd_audio_in_callback,
    .ep_addr = AUDIO_IN_EP
};

static struct usbd_endpoint audio_out_ep = {
    .ep_cb = usbd_audio_out_callback,
    .ep_addr = AUDIO_OUT_EP
};

void usbd_hid_int_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    hid_state = HID_STATE_IDLE;
}

static struct usbd_endpoint hid_in_ep = {
    .ep_cb = usbd_hid_int_callback,
    .ep_addr = HID_INT_EP
};

struct usbd_interface intf0;
struct usbd_interface intf1;

struct usbd_interface intf2;
struct usbd_interface intf3;
struct usbd_interface intf4;

struct usbd_interface intf5;

struct audio_entity_info audio_entity_table[] = {
    { .bEntityId = AUDIO_IN_FU_ID,
      .bDescriptorSubtype = AUDIO_CONTROL_FEATURE_UNIT,
      .ep = AUDIO_IN_EP },
    { .bEntityId = AUDIO_OUT_FU_ID,
      .bDescriptorSubtype = AUDIO_CONTROL_FEATURE_UNIT,
      .ep = AUDIO_OUT_EP },
};

void composite_init(uint8_t busid, uintptr_t reg_base)
{
    usbd_desc_register(busid, video_audio_hid_descriptor);
    usbd_add_interface(busid, usbd_video_init_intf(busid, &intf0, INTERVAL, MAX_FRAME_SIZE, MAX_PAYLOAD_SIZE));
    usbd_add_interface(busid, usbd_video_init_intf(busid, &intf1, INTERVAL, MAX_FRAME_SIZE, MAX_PAYLOAD_SIZE));
    usbd_add_endpoint(busid, &video_in_ep);

    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf2, 0x0100, audio_entity_table, 2));
    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf3, 0x0100, audio_entity_table, 2));
    usbd_add_interface(busid, usbd_audio_init_intf(busid, &intf4, 0x0100, audio_entity_table, 2));
    usbd_add_endpoint(busid, &audio_in_ep);
    usbd_add_endpoint(busid, &audio_out_ep);

    usbd_add_interface(busid, usbd_hid_init_intf(busid, &intf0, hid_keyboard_report_desc, HID_KEYBOARD_REPORT_DESC_SIZE));
    usbd_add_endpoint(busid, &hid_in_ep);

    usbd_initialize(busid, reg_base, usbd_event_handler);
}

/* just for test, rewrite by yourself */
void audio_test(uint8_t busid)
{
    while (1) {
        if (audio_tx_flag) {
            memset(audio_write_buffer, 'a', AUDIO_IN_PACKET);
            audio_iso_tx_busy = true;
            usbd_ep_start_write(busid, AUDIO_IN_EP, audio_write_buffer, AUDIO_IN_PACKET);
            while (audio_iso_tx_busy) {
                if (audio_tx_flag == false) {
                    break;
                }
            }
        }
    }
}

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t hid_write_buffer[64];

void hid_keyboard_test(uint8_t busid)
{
    const uint8_t sendbuffer[8] = { 0x00, 0x00, HID_KBD_USAGE_A, 0x00, 0x00, 0x00, 0x00, 0x00 };

    memcpy(hid_write_buffer, sendbuffer, 8);
    int ret = usbd_ep_start_write(busid, HID_INT_EP, hid_write_buffer, 8);
    if (ret < 0) {
        return;
    }
    hid_state = HID_STATE_BUSY;
    while (hid_state == HID_STATE_BUSY) {
    }
}

void video_test(uint8_t busid)
{
    uint32_t out_len;
    uint32_t packets;

    (void)packets;
    memset(video_packet_buffer, 0, 40 * 1024);
    while (1) {
        if (video_tx_flag) {
            packets = usbd_video_payload_fill(busid, (uint8_t *)cherryusb_mjpeg, sizeof(cherryusb_mjpeg), video_packet_buffer, &out_len);
#if 1
            video_iso_tx_busy = true;
            usbd_ep_start_write(busid, VIDEO_IN_EP, video_packet_buffer, out_len);
            while (video_iso_tx_busy) {
                if (video_tx_flag == 0) {
                    break;
                }
            }
#else
            /* dwc2 must use this method */
            for (uint32_t i = 0; i < packets; i++) {
                if (i == (packets - 1)) {
                    video_iso_tx_busy = true;
                    usbd_ep_start_write(busid, VIDEO_IN_EP, &video_packet_buffer[i * MAX_PAYLOAD_SIZE], out_len - (packets - 1) * MAX_PAYLOAD_SIZE);
                    while (video_iso_tx_busy) {
                        if (video_tx_flag == 0) {
                            break;
                        }
                    }
                } else {
                    video_iso_tx_busy = true;
                    usbd_ep_start_write(busid, VIDEO_IN_EP, &video_packet_buffer[i * MAX_PAYLOAD_SIZE], MAX_PAYLOAD_SIZE);
                    while (video_iso_tx_busy) {
                        if (video_tx_flag == 0) {
                            break;
                        }
                    }
                }
            }
#endif
        }
    }
}