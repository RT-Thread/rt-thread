/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_audio.h"

struct audio_entity_param {
    uint32_t wCur;
    uint32_t wMin;
    uint32_t wMax;
    uint32_t wRes;
};

struct usbd_audio_priv {
    struct audio_entity_info *table;
    uint8_t num;
    uint16_t uac_version;
} g_usbd_audio[CONFIG_USBDEV_MAX_BUS];

static int audio_class_endpoint_request_handler(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len)
{
    uint8_t control_selector;
    uint32_t sampling_freq = 0;
    uint8_t ep;

    control_selector = HI_BYTE(setup->wValue);
    ep = LO_BYTE(setup->wIndex);

    switch (control_selector) {
        case AUDIO_EP_CONTROL_SAMPLING_FEQ:
            switch (setup->bRequest) {
                case AUDIO_REQUEST_SET_CUR:
                    memcpy((uint8_t *)&sampling_freq, *data, *len);
                    USB_LOG_DBG("Set ep:0x%02x %d Hz\r\n", ep, (int)sampling_freq);
                    usbd_audio_set_sampling_freq(busid, ep, sampling_freq);
                    break;
                case AUDIO_REQUEST_GET_CUR:
                case AUDIO_REQUEST_GET_MIN:
                case AUDIO_REQUEST_GET_MAX:
                case AUDIO_REQUEST_GET_RES:
                    sampling_freq = usbd_audio_get_sampling_freq(busid, ep);
                    memcpy(*data, &sampling_freq, 3);
                    USB_LOG_DBG("Get ep:0x%02x %d Hz\r\n", ep, (int)sampling_freq);
                    *len = 3;
                    break;
            }

            break;
        default:
            USB_LOG_WRN("Unhandled Audio Class control selector 0x%02x\r\n", control_selector);
            return -1;
    }
    return 0;
}

static int audio_class_interface_request_handler(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len)
{
    USB_LOG_DBG("Audio Class request: "
                "bRequest 0x%02x\r\n",
                setup->bRequest);

    uint8_t entity_id;
    uint8_t ep = 0;
    uint8_t subtype = 0x01;
    uint8_t control_selector;
    uint8_t ch;
    uint8_t mute;
    uint16_t volume;
    int volume_db = 0;
    uint32_t sampling_freq = 0;

    const char *mute_string[2] = { "off", "on" };

    entity_id = HI_BYTE(setup->wIndex);
    control_selector = HI_BYTE(setup->wValue);
    ch = LO_BYTE(setup->wValue);

    ARG_UNUSED(mute_string);

    for (uint8_t i = 0; i < g_usbd_audio[busid].num; i++) {
        if (g_usbd_audio[busid].table[i].bEntityId == entity_id) {
            subtype = g_usbd_audio[busid].table[i].bDescriptorSubtype;
            ep = g_usbd_audio[busid].table[i].ep;
            break;
        }
    }

    if (subtype == 0x01) {
        USB_LOG_ERR("Do not find subtype for 0x%02x\r\n", entity_id);
        return -1;
    }

    USB_LOG_DBG("Audio entity_id:%02x, subtype:%02x, cs:%02x\r\n", entity_id, subtype, control_selector);

    switch (subtype) {
        case AUDIO_CONTROL_FEATURE_UNIT:
            switch (control_selector) {
                case AUDIO_FU_CONTROL_MUTE:
                    if (g_usbd_audio[busid].uac_version < 0x0200) {
                        switch (setup->bRequest) {
                            case AUDIO_REQUEST_SET_CUR:
                                mute = (*data)[0];
                                usbd_audio_set_mute(busid, ep, ch, mute);
                                break;
                            case AUDIO_REQUEST_GET_CUR:
                                (*data)[0] = usbd_audio_get_mute(busid, ep, ch);
                                *len = 1;
                                break;
                            default:
                                USB_LOG_WRN("Unhandled Audio Class bRequest 0x%02x in cs 0x%02x\r\n", setup->bRequest, control_selector);
                                return -1;
                        }
                    } else {
                        switch (setup->bRequest) {
                            case AUDIO_REQUEST_CUR:
                                if (setup->bmRequestType & USB_REQUEST_DIR_MASK) {
                                    (*data)[0] = usbd_audio_get_mute(busid, ep, ch);
                                    *len = 1;
                                } else {
                                    mute = (*data)[0];
                                    usbd_audio_set_mute(busid, ep, ch, mute);
                                }
                                break;
                            default:
                                //USB_LOG_WRN("Unhandled Audio Class bRequest 0x%02x in cs 0x%02x\r\n", setup->bRequest, control_selector);
                                return -1;
                        }
                    }
                    break;
                case AUDIO_FU_CONTROL_VOLUME:
                    if (g_usbd_audio[busid].uac_version < 0x0200) {
                        switch (setup->bRequest) {
                            case AUDIO_REQUEST_SET_CUR:
                                memcpy(&volume, *data, *len);
                                if (volume < 0x8000) {
                                    volume_db = volume / 256;
                                } else if (volume > 0x8000) {
                                    volume_db = (0xffff - volume + 1) / -256;
                                }
                                volume_db += 128; /* 0 ~ 255 */
                                USB_LOG_DBG("Set ep:0x%02x ch:%d volume:0x%04x\r\n", ep, ch, volume);
                                usbd_audio_set_volume(busid, ep, ch, volume_db);
                                break;
                            case AUDIO_REQUEST_GET_CUR:
                                volume_db = usbd_audio_get_volume(busid, ep, ch);
                                volume_db -= 128;
                                if (volume_db >= 0) {
                                    volume = volume_db * 256;
                                } else {
                                    volume = volume_db * 256 + 0xffff + 1;
                                }
                                memcpy(*data, &volume, 2);
                                *len = 2;
                                break;
                            case AUDIO_REQUEST_GET_MIN:
                                (*data)[0] = 0x00; /* -2560/256 dB */
                                (*data)[1] = 0xdb;
                                *len = 2;
                                break;
                            case AUDIO_REQUEST_GET_MAX:
                                (*data)[0] = 0x00; /* 0 dB */
                                (*data)[1] = 0x00;
                                *len = 2;
                                break;
                            case AUDIO_REQUEST_GET_RES:
                                (*data)[0] = 0x00; /* -256/256 dB */
                                (*data)[1] = 0x01;
                                *len = 2;
                                break;
                            default:
                                USB_LOG_WRN("Unhandled Audio Class bRequest 0x%02x in cs 0x%02x\r\n", setup->bRequest, control_selector);
                                return -1;
                        }
                    } else {
                        switch (setup->bRequest) {
                            case AUDIO_REQUEST_CUR:
                                if (setup->bmRequestType & USB_REQUEST_DIR_MASK) {
                                    volume_db = usbd_audio_get_volume(busid, ep, ch);
                                    volume = volume_db;
                                    memcpy(*data, &volume, 2);
                                    *len = 2;
                                } else {
                                    memcpy(&volume, *data, *len);
                                    volume_db = volume;
                                    USB_LOG_DBG("Set ep:0x%02x ch:%d volume:0x%02x\r\n", ep, ch, volume);
                                    usbd_audio_set_volume(busid, ep, ch, volume_db);
                                }
                                break;
                            case AUDIO_REQUEST_RANGE:
                                if (setup->bmRequestType & USB_REQUEST_DIR_MASK) {
                                    *((uint16_t *)(*data + 0)) = 1;
                                    *((uint16_t *)(*data + 2)) = 0;
                                    *((uint16_t *)(*data + 4)) = 100;
                                    *((uint16_t *)(*data + 6)) = 1;
                                    *len = 8;
                                } else {
                                }
                                break;
                            default:
                                //USB_LOG_WRN("Unhandled Audio Class bRequest 0x%02x in cs 0x%02x\r\n", setup->bRequest, control_selector);
                                return -1;
                        }
                    }
                    break;

                default:
                    USB_LOG_WRN("Unhandled Audio Class cs 0x%02x \r\n", control_selector);
                    return -1;
            }
            break;
        case AUDIO_CONTROL_CLOCK_SOURCE:
            switch (control_selector) {
                case AUDIO_CS_CONTROL_SAM_FREQ:
                    switch (setup->bRequest) {
                        case AUDIO_REQUEST_CUR:
                            if (setup->bmRequestType & USB_REQUEST_DIR_MASK) {
                                sampling_freq = usbd_audio_get_sampling_freq(busid, ep);
                                memcpy(*data, &sampling_freq, 4);
                                USB_LOG_DBG("Get ep:0x%02x %d Hz\r\n", ep, (int)sampling_freq);
                                *len = 4;
                            } else {
                                memcpy(&sampling_freq, *data, setup->wLength);
                                USB_LOG_DBG("Set ep:0x%02x %d Hz\r\n", ep, (int)sampling_freq);
                                usbd_audio_set_sampling_freq(busid, ep, sampling_freq);
                            }
                            break;
                        case AUDIO_REQUEST_RANGE:
                            if (setup->bmRequestType & USB_REQUEST_DIR_MASK) {
                                uint8_t *sampling_freq_table = NULL;
                                uint16_t num;

                                usbd_audio_get_sampling_freq_table(busid, ep, &sampling_freq_table);
                                num = (uint16_t)((uint16_t)(sampling_freq_table[1] << 8) | ((uint16_t)sampling_freq_table[0]));
                                memcpy(*data, sampling_freq_table, (12 * num + 2));
                                *len = (12 * num + 2);
                            } else {
                            }
                            break;
                        default:
                            //USB_LOG_WRN("Unhandled Audio Class bRequest 0x%02x in cs 0x%02x\r\n", setup->bRequest, control_selector);
                            return -1;
                    }
                    break;
                case AUDIO_CS_CONTROL_CLOCK_VALID:
                    if (setup->bmRequestType & USB_REQUEST_DIR_MASK) {
                        (*data)[0] = 1;
                        *len = 1;
                    } else {
                        return -1;
                    }
                    break;

                default:
                    //USB_LOG_WRN("Unhandled Audio Class cs 0x%02x \r\n", control_selector);
                    return -1;
            }
            break;

        default:
            break;
    }
    return 0;
}

static void audio_notify_handler(uint8_t busid, uint8_t event, void *arg)
{
    switch (event) {
        case USBD_EVENT_RESET:

            break;

        case USBD_EVENT_SET_INTERFACE: {
            struct usb_interface_descriptor *intf = (struct usb_interface_descriptor *)arg;
            if (intf->bAlternateSetting) {
                usbd_audio_open(busid, intf->bInterfaceNumber);
            } else {
                usbd_audio_close(busid, intf->bInterfaceNumber);
            }
        }

        break;

        default:
            break;
    }
}

struct usbd_interface *usbd_audio_init_intf(uint8_t busid,
                                            struct usbd_interface *intf,
                                            uint16_t uac_version,
                                            struct audio_entity_info *table,
                                            uint8_t num)
{
    if (uac_version < 0x0200) {
        intf->class_interface_handler = audio_class_interface_request_handler;
        intf->class_endpoint_handler = audio_class_endpoint_request_handler;
        intf->vendor_handler = NULL;
        intf->notify_handler = audio_notify_handler;
    } else {
        intf->class_interface_handler = audio_class_interface_request_handler;
        intf->class_endpoint_handler = NULL;
        intf->vendor_handler = NULL;
        intf->notify_handler = audio_notify_handler;
    }

    g_usbd_audio[busid].uac_version = uac_version;
    g_usbd_audio[busid].table = table;
    g_usbd_audio[busid].num = num;

    return intf;
}

__WEAK void usbd_audio_set_volume(uint8_t busid, uint8_t ep, uint8_t ch, int volume)
{
    (void)busid;
    (void)ep;
    (void)ch;
    (void)volume;
}

__WEAK int usbd_audio_get_volume(uint8_t busid, uint8_t ep, uint8_t ch)
{
    (void)busid;
    (void)ep;
    (void)ch;

    return 0;
}

__WEAK void usbd_audio_set_mute(uint8_t busid, uint8_t ep, uint8_t ch, bool mute)
{
    (void)busid;
    (void)ep;
    (void)ch;
    (void)mute;
}

__WEAK bool usbd_audio_get_mute(uint8_t busid, uint8_t ep, uint8_t ch)
{
    (void)busid;
    (void)ep;
    (void)ch;

    return 0;
}

__WEAK void usbd_audio_set_sampling_freq(uint8_t busid, uint8_t ep, uint32_t sampling_freq)
{
    (void)busid;
    (void)ep;
    (void)sampling_freq;
}

__WEAK uint32_t usbd_audio_get_sampling_freq(uint8_t busid, uint8_t ep)
{
    (void)busid;
    (void)ep;

    return 0;
}

__WEAK void usbd_audio_get_sampling_freq_table(uint8_t busid, uint8_t ep, uint8_t **sampling_freq_table)
{
    (void)busid;
    (void)ep;
    (void)sampling_freq_table;
}
