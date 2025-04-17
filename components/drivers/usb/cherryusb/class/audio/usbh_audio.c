/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_audio.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_audio"
#include "usb_log.h"

#define DEV_FORMAT "/dev/audio%d"

/* general descriptor field offsets */
#define DESC_bLength            0 /** Length offset */
#define DESC_bDescriptorType    1 /** Descriptor type offset */
#define DESC_bDescriptorSubType 2 /** Descriptor subtype offset */

/* interface descriptor field offsets */
#define INTF_DESC_bInterfaceNumber  2 /** Interface number offset */
#define INTF_DESC_bAlternateSetting 3 /** Alternate setting offset */

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_audio_buf[128];

static struct usbh_audio g_audio_class[CONFIG_USBHOST_MAX_AUDIO_CLASS];
static uint32_t g_devinuse = 0;

static struct usbh_audio *usbh_audio_class_alloc(void)
{
    uint8_t devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_AUDIO_CLASS; devno++) {
        if ((g_devinuse & (1U << devno)) == 0) {
            g_devinuse |= (1U << devno);
            memset(&g_audio_class[devno], 0, sizeof(struct usbh_audio));
            g_audio_class[devno].minor = devno;
            return &g_audio_class[devno];
        }
    }
    return NULL;
}

static void usbh_audio_class_free(struct usbh_audio *audio_class)
{
    uint8_t devno = audio_class->minor;

    if (devno < 32) {
        g_devinuse &= ~(1U << devno);
    }
    memset(audio_class, 0, sizeof(struct usbh_audio));
}

int usbh_audio_open(struct usbh_audio *audio_class, const char *name, uint32_t samp_freq, uint8_t bitresolution)
{
    struct usb_setup_packet *setup;
    struct usb_endpoint_descriptor *ep_desc;
    uint8_t mult;
    uint16_t mps;
    int ret;
    uint8_t intf = 0xff;
    uint8_t altsetting = 1;

    if (!audio_class || !audio_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = audio_class->hport->setup;

    if (audio_class->is_opened) {
        return 0;
    }

    for (uint8_t i = 0; i < audio_class->stream_intf_num; i++) {
        if (strcmp(name, audio_class->as_msg_table[i].stream_name) == 0) {
            intf = audio_class->as_msg_table[i].stream_intf;
            for (uint8_t j = 1; j < audio_class->as_msg_table[i].num_of_altsetting; j++) {
                if (audio_class->as_msg_table[i].as_format[j].bBitResolution == bitresolution) {
                    for (uint8_t k = 0; k < audio_class->as_msg_table[i].as_format[j].bSamFreqType; k++) {
                        uint32_t freq = 0;

                        memcpy(&freq, &audio_class->as_msg_table[i].as_format[j].tSamFreq[3 * k], 3);
                        if (freq == samp_freq) {
                            altsetting = j;
                            goto freq_found;
                        }
                    }
                }
            }
        }
    }
    return -USB_ERR_NODEV;

freq_found:

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = USB_REQUEST_SET_INTERFACE;
    setup->wValue = altsetting;
    setup->wIndex = intf;
    setup->wLength = 0;

    ret = usbh_control_transfer(audio_class->hport, setup, NULL);
    if (ret < 0) {
        return ret;
    }

    ep_desc = &audio_class->hport->config.intf[intf].altsetting[altsetting].ep[0].ep_desc;

    if (audio_class->as_msg_table[intf - audio_class->ctrl_intf - 1].ep_attr & AUDIO_EP_CONTROL_SAMPLING_FEQ) {
        setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_ENDPOINT;
        setup->bRequest = AUDIO_REQUEST_SET_CUR;
        setup->wValue = (AUDIO_EP_CONTROL_SAMPLING_FEQ << 8) | 0x00;
        setup->wIndex = ep_desc->bEndpointAddress;
        setup->wLength = 3;

        memcpy(g_audio_buf, &samp_freq, 3);
        ret = usbh_control_transfer(audio_class->hport, setup, g_audio_buf);
        if (ret < 0) {
            return ret;
        }
    }

    mult = (ep_desc->wMaxPacketSize & USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_MASK) >> USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT;
    mps = ep_desc->wMaxPacketSize & USB_MAXPACKETSIZE_MASK;
    if (ep_desc->bEndpointAddress & 0x80) {
        audio_class->isoin_mps = mps * (mult + 1);
        USBH_EP_INIT(audio_class->isoin, ep_desc);
    } else {
        audio_class->isoout_mps = mps * (mult + 1);
        USBH_EP_INIT(audio_class->isoout, ep_desc);
    }

    USB_LOG_INFO("Open audio stream :%s, altsetting: %u\r\n", name, altsetting);
    audio_class->is_opened = true;
    return ret;
}

int usbh_audio_close(struct usbh_audio *audio_class, const char *name)
{
    struct usb_setup_packet *setup;
    struct usb_endpoint_descriptor *ep_desc;
    int ret;
    uint8_t intf = 0xff;
    uint8_t altsetting = 1;

    if (!audio_class || !audio_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = audio_class->hport->setup;

    for (uint8_t i = 0; i < audio_class->stream_intf_num; i++) {
        if (strcmp(name, audio_class->as_msg_table[i].stream_name) == 0) {
            intf = audio_class->as_msg_table[i].stream_intf;
        }
    }

    if (intf == 0xff) {
        return -USB_ERR_NODEV;
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = USB_REQUEST_SET_INTERFACE;
    setup->wValue = 0;
    setup->wIndex = intf;
    setup->wLength = 0;

    ret = usbh_control_transfer(audio_class->hport, setup, NULL);
    if (ret < 0) {
        return ret;
    }
    USB_LOG_INFO("Close audio stream :%s\r\n", name);
    audio_class->is_opened = false;

    ep_desc = &audio_class->hport->config.intf[intf].altsetting[altsetting].ep[0].ep_desc;
    if (ep_desc->bEndpointAddress & 0x80) {
        if (audio_class->isoin) {
            audio_class->isoin = NULL;
        }
    } else {
        if (audio_class->isoout) {
            audio_class->isoout = NULL;
        }
    }

    return ret;
}

int usbh_audio_set_volume(struct usbh_audio *audio_class, const char *name, uint8_t ch, uint8_t volume)
{
    struct usb_setup_packet *setup;
    int ret;
    uint8_t feature_id = 0xff;
    uint16_t volume_hex;

    if (!audio_class || !audio_class->hport) {
        return -USB_ERR_INVAL;
    }

    if (volume > 100) {
        return -USB_ERR_INVAL;
    }

    setup = audio_class->hport->setup;

    for (uint8_t i = 0; i < audio_class->stream_intf_num; i++) {
        if (strcmp(name, audio_class->as_msg_table[i].stream_name) == 0) {
            feature_id = audio_class->as_msg_table[i].feature_terminal_id;
        }
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = AUDIO_REQUEST_SET_CUR;
    setup->wValue = (AUDIO_FU_CONTROL_VOLUME << 8) | ch;
    setup->wIndex = (feature_id << 8) | audio_class->ctrl_intf;
    setup->wLength = 2;

    volume_hex = -0xDB00 / 100 * volume + 0xdb00;

    memcpy(g_audio_buf, &volume_hex, 2);
    ret = usbh_control_transfer(audio_class->hport, setup, NULL);

    return ret;
}

int usbh_audio_set_mute(struct usbh_audio *audio_class, const char *name, uint8_t ch, bool mute)
{
    struct usb_setup_packet *setup;
    int ret;
    uint8_t feature_id = 0xff;

    if (!audio_class || !audio_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = audio_class->hport->setup;

    for (uint8_t i = 0; i < audio_class->stream_intf_num; i++) {
        if (strcmp(name, audio_class->as_msg_table[i].stream_name) == 0) {
            feature_id = audio_class->as_msg_table[i].feature_terminal_id;
        }
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = AUDIO_REQUEST_SET_CUR;
    setup->wValue = (AUDIO_FU_CONTROL_MUTE << 8) | ch;
    setup->wIndex = (feature_id << 8) | audio_class->ctrl_intf;
    setup->wLength = 1;

    memcpy(g_audio_buf, &mute, 1);
    ret = usbh_control_transfer(audio_class->hport, setup, g_audio_buf);

    return ret;
}

void usbh_audio_list_module(struct usbh_audio *audio_class)
{
    USB_LOG_INFO("============= Audio module information ===================\r\n");
    USB_LOG_RAW("bcdADC :%04x\r\n", audio_class->bcdADC);
    USB_LOG_RAW("Num of audio stream :%u\r\n", audio_class->stream_intf_num);

    for (uint8_t i = 0; i < audio_class->stream_intf_num; i++) {
        USB_LOG_RAW("\tstream name :%s\r\n", audio_class->as_msg_table[i].stream_name);
        USB_LOG_RAW("\tstream intf :%u\r\n", audio_class->as_msg_table[i].stream_intf);
        USB_LOG_RAW("\tNum of altsetting :%u\r\n", audio_class->as_msg_table[i].num_of_altsetting);

        for (uint8_t j = 0; j < audio_class->as_msg_table[i].num_of_altsetting; j++) {
            if (j == 0) {
                USB_LOG_RAW("\t\tIngore altsetting 0\r\n");
                continue;
            }
            USB_LOG_RAW("\t\tAltsetting :%u\r\n", j);
            USB_LOG_RAW("\t\t\tbNrChannels :%u\r\n", audio_class->as_msg_table[i].as_format[j].bNrChannels);
            USB_LOG_RAW("\t\t\tbBitResolution :%u\r\n", audio_class->as_msg_table[i].as_format[j].bBitResolution);
            USB_LOG_RAW("\t\t\tbSamFreqType :%u\r\n", audio_class->as_msg_table[i].as_format[j].bSamFreqType);

            for (uint8_t k = 0; k < audio_class->as_msg_table[i].as_format[j].bSamFreqType; k++) {
                uint32_t freq = 0;

                memcpy(&freq, &audio_class->as_msg_table[i].as_format[j].tSamFreq[3 * k], 3);
                USB_LOG_RAW("\t\t\t\tSampleFreq :%u\r\n", freq);
            }
        }
    }

    USB_LOG_INFO("============= Audio module information ===================\r\n");
}

static int usbh_audio_ctrl_connect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret;
    uint8_t cur_iface = 0xff;
    uint8_t cur_iface_count = 0xff;
    uint8_t cur_alt_setting = 0xff;
    uint8_t input_offset = 0;
    uint8_t output_offset = 0;
    uint8_t feature_unit_offset = 0;
    uint8_t *p;

    struct usbh_audio *audio_class = usbh_audio_class_alloc();
    if (audio_class == NULL) {
        USB_LOG_ERR("Fail to alloc audio_class\r\n");
        return -USB_ERR_NOMEM;
    }

    audio_class->hport = hport;
    audio_class->ctrl_intf = intf;
    hport->config.intf[intf].priv = audio_class;

    p = hport->raw_config_desc;
    while (p[DESC_bLength]) {
        switch (p[DESC_bDescriptorType]) {
            case USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION:
                cur_iface_count = p[3];
                break;
            case USB_DESCRIPTOR_TYPE_INTERFACE:
                cur_iface = p[INTF_DESC_bInterfaceNumber];
                cur_alt_setting = p[INTF_DESC_bAlternateSetting];
                break;
            case USB_DESCRIPTOR_TYPE_ENDPOINT:
                break;
            case AUDIO_INTERFACE_DESCRIPTOR_TYPE:
                if (cur_iface == audio_class->ctrl_intf) {
                    switch (p[DESC_bDescriptorSubType]) {
                        case AUDIO_CONTROL_HEADER: {
                            struct audio_cs_if_ac_header_descriptor *desc = (struct audio_cs_if_ac_header_descriptor *)p;
                            audio_class->bcdADC = desc->bcdADC;
                            audio_class->bInCollection = desc->bInCollection;
                        } break;
                        case AUDIO_CONTROL_INPUT_TERMINAL: {
                            struct audio_cs_if_ac_input_terminal_descriptor *desc = (struct audio_cs_if_ac_input_terminal_descriptor *)p;

                            memcpy(&audio_class->ac_msg_table[input_offset].ac_input, desc, sizeof(struct audio_cs_if_ac_input_terminal_descriptor));
                            input_offset++;
                        } break;
                        case AUDIO_CONTROL_OUTPUT_TERMINAL: {
                            struct audio_cs_if_ac_output_terminal_descriptor *desc = (struct audio_cs_if_ac_output_terminal_descriptor *)p;

                            memcpy(&audio_class->ac_msg_table[output_offset].ac_output, desc, sizeof(struct audio_cs_if_ac_output_terminal_descriptor));
                            output_offset++;
                        } break;
                        case AUDIO_CONTROL_FEATURE_UNIT: {
                            struct audio_cs_if_ac_feature_unit_descriptor *desc = (struct audio_cs_if_ac_feature_unit_descriptor *)p;

                            memcpy(&audio_class->ac_msg_table[feature_unit_offset].ac_feature_unit, desc, desc->bLength);
                            feature_unit_offset++;
                        } break;
                        case AUDIO_CONTROL_PROCESSING_UNIT:

                            break;
                        default:
                            break;
                    }
                } else if ((cur_iface > audio_class->ctrl_intf) && (cur_iface < (audio_class->ctrl_intf + cur_iface_count))) {
                    switch (p[DESC_bDescriptorSubType]) {
                        case AUDIO_STREAMING_GENERAL: {
                            struct audio_cs_if_as_general_descriptor *desc = (struct audio_cs_if_as_general_descriptor *)p;

                            /* all altsetting have the same general */
                            audio_class->as_msg_table[cur_iface - audio_class->ctrl_intf - 1].stream_intf = cur_iface;
                            memcpy(&audio_class->as_msg_table[cur_iface - audio_class->ctrl_intf - 1].as_general, desc, sizeof(struct audio_cs_if_as_general_descriptor));
                        } break;
                        case AUDIO_STREAMING_FORMAT_TYPE: {
                            struct audio_cs_if_as_format_type_descriptor *desc = (struct audio_cs_if_as_format_type_descriptor *)p;
                            audio_class->as_msg_table[cur_iface - audio_class->ctrl_intf - 1].num_of_altsetting = (cur_alt_setting + 1);
                            memcpy(&audio_class->as_msg_table[cur_iface - audio_class->ctrl_intf - 1].as_format[cur_alt_setting], desc, desc->bLength);
                        } break;
                        default:
                            break;
                    }
                }
                break;
            case AUDIO_ENDPOINT_DESCRIPTOR_TYPE:
                if ((cur_iface > audio_class->ctrl_intf) && (cur_iface < (audio_class->ctrl_intf + cur_iface_count))) {
                    if (p[DESC_bDescriptorSubType] == AUDIO_ENDPOINT_GENERAL) {
                        struct audio_cs_ep_ep_general_descriptor *desc = (struct audio_cs_ep_ep_general_descriptor *)p;
                        audio_class->as_msg_table[cur_iface - audio_class->ctrl_intf - 1].ep_attr = desc->bmAttributes;
                    }
                }
                break;
            default:
                break;
        }
        /* skip to next descriptor */
        p += p[DESC_bLength];
    }

    if ((input_offset != output_offset) && (input_offset != feature_unit_offset)) {
        USB_LOG_ERR("Audio descriptor is invalid\r\n");
        return -USB_ERR_INVAL;
    }

    audio_class->stream_intf_num = input_offset;

    for (uint8_t i = 0; i < audio_class->stream_intf_num; i++) {
        /* Search 0x0101 in input or output desc */
        for (uint8_t streamidx = 0; streamidx < audio_class->stream_intf_num; streamidx++) {
            if (audio_class->as_msg_table[i].as_general.bTerminalLink == audio_class->ac_msg_table[streamidx].ac_input.bTerminalID) {
                /* INPUT --> FEATURE UNIT --> OUTPUT */
                audio_class->as_msg_table[i].input_terminal_id = audio_class->ac_msg_table[streamidx].ac_input.bTerminalID;

                /* Search input terminal id in feature desc */
                for (uint8_t featureidx = 0; featureidx < audio_class->stream_intf_num; featureidx++) {
                    if (audio_class->ac_msg_table[streamidx].ac_input.bTerminalID == audio_class->ac_msg_table[featureidx].ac_feature_unit.bSourceID) {
                        audio_class->as_msg_table[i].feature_terminal_id = audio_class->ac_msg_table[featureidx].ac_feature_unit.bUnitID;

                        /* Search feature unit id in output desc */
                        for (uint8_t outputid = 0; outputid < audio_class->stream_intf_num; outputid++) {
                            if (audio_class->ac_msg_table[featureidx].ac_feature_unit.bUnitID == audio_class->ac_msg_table[outputid].ac_output.bSourceID) {
                                audio_class->as_msg_table[i].output_terminal_id = audio_class->ac_msg_table[outputid].ac_output.bTerminalID;

                                switch (audio_class->ac_msg_table[outputid].ac_output.wTerminalType) {
                                    case AUDIO_OUTTERM_SPEAKER:
                                        audio_class->as_msg_table[i].stream_name = "speaker";
                                        break;
                                    case AUDIO_OUTTERM_HEADPHONES:
                                        audio_class->as_msg_table[i].stream_name = "headphoens";
                                        break;
                                    case AUDIO_OUTTERM_HEADDISPLAY:
                                        audio_class->as_msg_table[i].stream_name = "headdisplay";
                                        break;
                                    default:
                                        audio_class->as_msg_table[i].stream_name = "unknown";
                                        break;
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            } else if (audio_class->as_msg_table[i].as_general.bTerminalLink == audio_class->ac_msg_table[streamidx].ac_output.bTerminalID) {
                /* OUTPUT --> FEATURE UNIT --> INPUT */
                audio_class->as_msg_table[i].output_terminal_id = audio_class->ac_msg_table[streamidx].ac_output.bTerminalID;

                /* Search output terminal id in feature desc */
                for (uint8_t featureidx = 0; featureidx < audio_class->stream_intf_num; featureidx++) {
                    if (audio_class->ac_msg_table[streamidx].ac_output.bSourceID == audio_class->ac_msg_table[featureidx].ac_feature_unit.bUnitID) {
                        audio_class->as_msg_table[i].feature_terminal_id = audio_class->ac_msg_table[featureidx].ac_feature_unit.bUnitID;

                        /* Search feature unit id in input desc */
                        for (uint8_t inputid = 0; inputid < audio_class->stream_intf_num; inputid++) {
                            if (audio_class->ac_msg_table[featureidx].ac_feature_unit.bSourceID == audio_class->ac_msg_table[inputid].ac_input.bTerminalID) {
                                audio_class->as_msg_table[i].input_terminal_id = audio_class->ac_msg_table[inputid].ac_input.bTerminalID;

                                switch (audio_class->ac_msg_table[inputid].ac_input.wTerminalType) {
                                    case AUDIO_INTERM_MIC:
                                        audio_class->as_msg_table[i].stream_name = "mic";
                                        break;
                                    default:
                                        audio_class->as_msg_table[i].stream_name = "unknown";
                                        break;
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    for (uint8_t i = 0; i < audio_class->stream_intf_num; i++) {
        ret = usbh_audio_close(audio_class, audio_class->as_msg_table[i].stream_name);
        if (ret < 0) {
            USB_LOG_ERR("Fail to close audio stream :%s\r\n", audio_class->as_msg_table[i].stream_name);
            return ret;
        }
    }

    usbh_audio_list_module(audio_class);

    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, audio_class->minor);
    USB_LOG_INFO("Register Audio Class:%s\r\n", hport->config.intf[intf].devname);

    usbh_audio_run(audio_class);
    return 0;
}

static int usbh_audio_ctrl_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_audio *audio_class = (struct usbh_audio *)hport->config.intf[intf].priv;

    if (audio_class) {
        if (audio_class->isoin) {
        }

        if (audio_class->isoout) {
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister Audio Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_audio_stop(audio_class);
        }

        usbh_audio_class_free(audio_class);
    }

    return ret;
}

static int usbh_audio_data_connect(struct usbh_hubport *hport, uint8_t intf)
{
    (void)hport;
    (void)intf;
    return 0;
}

static int usbh_audio_data_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    (void)hport;
    (void)intf;
    return 0;
}

__WEAK void usbh_audio_run(struct usbh_audio *audio_class)
{
    (void)audio_class;
}

__WEAK void usbh_audio_stop(struct usbh_audio *audio_class)
{
    (void)audio_class;
}

const struct usbh_class_driver audio_ctrl_class_driver = {
    .driver_name = "audio_ctrl",
    .connect = usbh_audio_ctrl_connect,
    .disconnect = usbh_audio_ctrl_disconnect
};

const struct usbh_class_driver audio_streaming_class_driver = {
    .driver_name = "audio_streaming",
    .connect = usbh_audio_data_connect,
    .disconnect = usbh_audio_data_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info audio_ctrl_intf_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS,
    .class = USB_DEVICE_CLASS_AUDIO,
    .subclass = AUDIO_SUBCLASS_AUDIOCONTROL,
    .protocol = 0x00,
    .id_table = NULL,
    .class_driver = &audio_ctrl_class_driver
};

CLASS_INFO_DEFINE const struct usbh_class_info audio_streaming_intf_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS,
    .class = USB_DEVICE_CLASS_AUDIO,
    .subclass = AUDIO_SUBCLASS_AUDIOSTREAMING,
    .protocol = 0x00,
    .id_table = NULL,
    .class_driver = &audio_streaming_class_driver
};
