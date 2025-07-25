/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_AOA_H
#define USB_AOA_H

//AOA 1.0
#define AOA_ACCESSORY_VENDOR_ID      0x18D1
#define AOA_ACCESSORY_PRODUCT_ID     0x2D00
#define AOA_ACCESSORY_ADB_PRODUCT_ID 0x2D01

//AOA 2.0
#define AOA_AUDIO_PRODUCT_ID               0x2D02
#define AOA_AUDIO_ADB_PRODUCT_ID           0x2D03
#define AOA_ACCESSORY_AUDIO_PRODUCT_ID     0x2D04
#define AOA_ACCESSORY_AUDIO_ADB_PRODUCT_ID 0x2D05

//AOA 1.0
#define AOA_ACCESSORY_GET_PROTOCOL 51
#define AOA_ACCESSORY_SEND_STRING  52
#define AOA_ACCESSORY_START        53

//AOA 2.0
#define AOA_ACCESSORY_REGISTER_HID        54
#define AOA_ACCESSORY_UNREGISTER_HID      55
#define AOA_ACCESSORY_SET_HID_REPORT_DESC 56
#define AOA_ACCESSORY_SEND_HID_EVENT      57
#define AOA_ACCESSORY_SET_AUDIO_MODE      58

#define AOA_ACCESSORY_STRING_MANUFACTURER 0
#define AOA_ACCESSORY_STRING_MODEL        1
#define AOA_ACCESSORY_STRING_DESCRIPTION  2
#define AOA_ACCESSORY_STRING_VERSION      3
#define AOA_ACCESSORY_STRING_URI          4
#define AOA_ACCESSORY_STRING_SERIAL       5

struct aoa_string_info {
    char acc_manufacturer[64];
    char acc_model[64];
    char acc_description[64];
    char acc_version[64];
    char acc_uri[64];
    char acc_serial[64];
};

#endif /* USB_AOA_H */