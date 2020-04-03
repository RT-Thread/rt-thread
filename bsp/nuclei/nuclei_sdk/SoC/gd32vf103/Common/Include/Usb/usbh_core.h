/*!
    \file  usbh_core.h
    \brief USB host core state machine header file

    \version 2019-6-5, V1.0.0, firmware for GD32 USBFS&USBHS
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef __USBH_CORE_H
#define __USBH_CORE_H

#include "usbh_conf.h"
#include "drv_usb_host.h"

#define MSC_CLASS                                       0x08U
#define HID_CLASS                                       0x03U
#define MSC_PROTOCOL                                    0x50U
#define CBI_PROTOCOL                                    0x01U

#define USBH_MAX_ERROR_COUNT                            3U

#define USBH_DEV_ADDR_DEFAULT                           0U
#define USBH_DEV_ADDR                                   1U

typedef enum
{
    USBH_OK = 0U,
    USBH_BUSY,
    USBH_FAIL,
    USBH_NOT_SUPPORTED,
    USBH_UNRECOVERED_ERROR,
    USBH_SPEED_UNKNOWN_ERROR,
    USBH_APPLY_DEINIT
} usbh_status;

/* USB host global operation state */
typedef enum
{
    HOST_DEFAULT = 0U,
    HOST_DETECT_DEV_SPEED,
    HOST_DEV_ATTACHED,
    HOST_DEV_DETACHED,
    HOST_ENUM,
    HOST_CLASS_ENUM,
    HOST_CLASS_HANDLER,
    HOST_USER_INPUT,
    HOST_SUSPENDED,
    HOST_ERROR
} usb_host_state;

/* USB host enumeration state */
typedef enum
{
    ENUM_DEFAULT = 0U,
    ENUM_GET_DEV_DESC,
    ENUM_SET_ADDR,
    ENUM_GET_CFG_DESC,
    ENUM_GET_CFG_DESC_SET,
    ENUM_GET_STR_DESC,
    ENUM_SET_CONFIGURATION,
    ENUM_DEV_CONFIGURED
} usbh_enum_state;

/* USB host control transfer state */
typedef enum 
{
    CTL_IDLE = 0U,
    CTL_SETUP,
    CTL_DATA_IN,
    CTL_DATA_OUT,
    CTL_STATUS_IN,
    CTL_STATUS_OUT,
    CTL_ERROR,
    CTL_FINISH
} usbh_ctl_state;

/* user action state */
typedef enum
{
    USBH_USER_NO_RESP = 0U,
    USBH_USER_RESP_OK = 1U,
} usbh_user_status;

/* control transfer information */
typedef struct _usbh_control
{
    uint8_t               pipe_in_num;
    uint8_t               pipe_out_num;
    uint8_t               max_len;
    uint8_t               error_count;

    uint8_t               *buf;
    uint16_t              ctl_len;
    uint16_t              timer;

    usb_setup             setup;
    usbh_ctl_state        ctl_state;
} usbh_control;

/* USB device property */
typedef struct
{
    uint8_t                   addr;
    uint32_t                  speed;

    usb_desc_dev              dev_desc;
    usb_desc_config           cfg_desc;
    usb_desc_itf              itf_desc[USBH_MAX_INTERFACES_NUM];
    usb_desc_ep               ep_desc[USBH_MAX_INTERFACES_NUM][USBH_MAX_EP_NUM];
} usb_dev_prop;

/**
  * @brief Device class callbacks
  */
typedef struct
{
    usbh_status (*class_init)      (usb_core_driver *pudev, void *phost);
    void        (*class_deinit)    (usb_core_driver *pudev, void *phost);
    usbh_status (*class_requests)  (usb_core_driver *pudev, void *phost);
    usbh_status (*class_machine)   (usb_core_driver *pudev, void *phost);
} usbh_class_cb;

/**
  * @brief User callbacks
  */
typedef struct
{
    void (*dev_init)                    (void);
    void (*dev_deinit)                  (void);
    void (*dev_attach)                  (void);
    void (*dev_reset)                   (void);
    void (*dev_detach)                  (void);
    void (*dev_over_currented)          (void);
    void (*dev_speed_detected)          (uint32_t dev_speed);
    void (*dev_devdesc_assigned)        (void *dev_desc);
    void (*dev_address_set)             (void);

    void (*dev_cfgdesc_assigned)        (usb_desc_config *cfg_desc,
                                         usb_desc_itf *itf_desc,
                                         usb_desc_ep *ep_desc);

    void (*dev_mfc_str)                 (void *mfc_str);
    void (*dev_prod_str)                (void *prod_str);
    void (*dev_seral_str)               (void *serial_str);
    void (*dev_enumerated)              (void);
    usbh_user_status (*dev_user_input)  (void);
    int  (*dev_user_app)                (void);
    void (*dev_not_supported)           (void);
    void (*dev_error)                   (void);
} usbh_user_cb;

/**
  * @brief Host information
  */
typedef struct
{
    usb_host_state                      cur_state;              /*!< host state machine value */
    usb_host_state                      backup_state;           /*!< backup of previous state machine value */
    usbh_enum_state                     enum_state;             /*!< enumeration state machine */
    usbh_control                        control;                /*!< USB host control state machine */
    usb_dev_prop                        dev_prop;               /*!< USB device properity */

    usbh_class_cb                       *class_cb;              /*!< USB class callback */
    usbh_user_cb                        *usr_cb;                /*!< USB user callback */
} usbh_host;


/* USB host stack initializations */
void usbh_init (usb_core_driver *pudev, usb_core_enum core, usbh_host *puhost);

/* de-initialize USB host */
usbh_status usbh_deinit (usb_core_driver *pudev, usbh_host *puhost);

/* USB host core main state machine process */
void usbh_core_task (usb_core_driver *pudev, usbh_host *puhost);

/* handle the error on USB host side */
void usbh_error_handler (usbh_host *puhost, usbh_status ErrType);

/* get USB URB state */
static inline usb_urb_state usbh_urbstate_get (usb_core_driver *pudev, uint8_t pp_num)
{
    return pudev->host.pipe[pp_num].urb_state;
}

/* get USB transfer data count */
static inline uint32_t usbh_xfercount_get (usb_core_driver *pudev, uint8_t pp_num)
{
    return pudev->host.backup_xfercount[pp_num];
}

#endif /* __USBH_CORE_H */

