/*!
    \file  usbd_std.h
    \brief USB 2.0 standard driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-06-30, V1.0.0, firmware for GD32F4xx
*/

#ifndef USBD_STD_H
#define USBD_STD_H

#include "usb_std.h"
#include "usbd_core.h"
#include "usbd_conf.h"
#include <wchar.h>

#define USBD_LANGID_STR_IDX                            0x00U     /*!< USB language ID string index*/
#define USBD_MFC_STR_IDX                               0x01U     /*!< USB manufacturer string index*/
#define USBD_PRODUCT_STR_IDX                           0x02U     /*!< USB product string index*/
#define USBD_SERIAL_STR_IDX                            0x03U     /*!< USB serial string index*/
#define USBD_CONFIG_STR_IDX                            0x04U     /*!< USB configuration string index*/
#define USBD_INTERFACE_STR_IDX                         0x05U     /*!< USB interface string index*/

#define USB_STATUS_REMOTE_WAKEUP                       0x02U     /*!< USB remote wakeup status*/
#define USB_STATUS_SELF_POWERED                        0x01U     /*!< USB self power status*/

#define USB_FEATURE_ENDP_HALT                          0x00U     /*!< USB halt endpoint feature*/
#define USB_FEATURE_REMOTE_WAKEUP                      0x01U     /*!< USB remote wakeup feature*/
#define USB_FEATURE_TEST_MODE                          0x02U     /*!< USB test mode feature*/

#define ENG_LANGID                                     0x0409U   /*!< USB english language id*/
#define CHN_LANGID                                     0x0804U   /*!< USB chinese language id*/

#define USB_DEVICE_DESC_SIZE                           0x12U     /*!< USB device descriptor size*/

#define LOWBYTE(x)           ((uint8_t)((x) & 0x00FFU))          /*!< USB lowbyte operation marco*/
#define HIGHBYTE(x)          ((uint8_t)(((x) & 0xFF00U) >> 8U))  /*!< USB highbyte operation marco*/

#define USB_MIN(a, b)        (((a) < (b)) ? (a) : (b))           /*!< USB minimum operation marco*/

#define WIDE_STRING(string)  _WIDE_STRING(string)
#define _WIDE_STRING(string) L##string

#define USBD_STRING_DESC(string) \
    (uint8_t *)&(struct { \
        uint8_t _len; \
        uint8_t _type; \
        wchar_t _data[sizeof(string)]; \
    }) { \
        sizeof(WIDE_STRING(string)) + 2U - 2U, \
        USB_DESCTYPE_STRING, \
        WIDE_STRING(string) \
    }

#define IS_NOT_EP0(ep_addr)   (((ep_addr) != 0x00U) && ((ep_addr) != 0x80U))

/* function declarations */
/* USB device setup transaction*/
usbd_status_enum usbd_setup_transaction (usb_core_handle_struct *pudev);
/* USB device out transaction*/
usbd_status_enum usbd_out_transaction (usb_core_handle_struct *pudev, uint8_t endp_num);
/* USB device in transaction*/
usbd_status_enum usbd_in_transaction (usb_core_handle_struct *pudev, uint8_t endp_num);
/* USB device enum error handle*/
void usbd_enum_error (usb_core_handle_struct *pudev, usb_device_req_struct *req);

#endif /* USBD_STD_H */
