/*!
    \file    usbh_core.h
    \brief   USB host core state machine header file

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#ifndef USBH_CORE_H
#define USBH_CORE_H

#include "usbh_conf.h"
#include "drv_usb_host.h"

#define MSC_CLASS                                       0x08U                  /*!< USB MSC class */
#define HID_CLASS                                       0x03U                  /*!< USB HID class */
#define MSC_PROTOCOL                                    0x50U                  /*!< USB MSC protocol */
#define CBI_PROTOCOL                                    0x01U                  /*!< USB CBI protocol */

#define USBH_MAX_ERROR_COUNT                            3U                     /*!< USBH maximum error count */

#define USBH_DEV_ADDR_DEFAULT                           0U                     /*!< USBH device address default */
#define USBH_DEV_ADDR                                   1U                     /*!< USBH device address */

typedef enum {
    USBH_OK = 0U,                                      /*!< USB host OK status */
    USBH_BUSY,                                         /*!< USB host busy status */
    USBH_FAIL,                                         /*!< USB host fail status */
    USBH_NOT_SUPPORTED,                                /*!< USB host not support status */
    USBH_UNRECOVERED_ERROR,                            /*!< USB host unrecovered error status */
    USBH_SPEED_UNKNOWN_ERROR,                          /*!< USB host speed unknown error status */
    USBH_APPLY_DEINIT                                  /*!< USB host apply deinit status */
} usbh_status;

/* USB host global operation state */
typedef enum {
    HOST_DEFAULT = 0U,                                 /*!< USB host global operation default state */
    HOST_DETECT_DEV_SPEED,                             /*!< USB host global operation detect device speed state */
    HOST_DEV_CONNECT,                                  /*!< USB host global operation device connect state */
    HOST_DEV_DETACHED,                                 /*!< USB host global operation device detached state */
    HOST_DEV_ENUM,                                     /*!< USB host global operation device enumeration state */
    HOST_PWR_FEATURE_SET,                              /*!< USB host global operation setting power feature state */
    HOST_CLASS_CHECK,                                  /*!< USB host global operation class check state */
    HOST_CLASS_ENUM,                                   /*!< USB host global operation class enumeration state */
    HOST_CLASS_HANDLER,                                /*!< USB host global operation class handler state */
    HOST_USER_INPUT,                                   /*!< USB host global operation user input state */
    HOST_SUSPEND,                                      /*!< USB host global operation suspend state */
    HOST_WAKEUP,                                       /*!< USB host global operation wakeup state */
    HOST_ERROR                                         /*!< USB host global operation error state */
} usb_host_state;

/* USB host enumeration state */
typedef enum {
    ENUM_DEFAULT = 0U,                                 /*!< USB host enumeration default state */
    ENUM_GET_DEV_DESC,                                 /*!< USB host enumeration get device descriptor state */
    ENUM_SET_ADDR,                                     /*!< USB host enumeration set address state */
    ENUM_GET_CFG_DESC,                                 /*!< USB host enumeration get configuration descriptor state */
    ENUM_GET_CFG_DESC_SET,                             /*!< USB host enumeration set configuration descriptor state */
    ENUM_GET_STR_DESC,                                 /*!< USB host enumeration get string descriptor state */
#ifdef USB_MTP
    ENUM_GET_MTP_STR,                                  /*!< USB host enumeration get MTP string state */
#endif /* USB_MTP */
    ENUM_SET_CONFIGURATION,                            /*!< USB host enumeration set configuration state */
    ENUM_DEV_CONFIGURED                                /*!< USB host enumeration device configured state */
} usbh_enum_state;

/* USB host control transfer state */
typedef enum  {
    CTL_IDLE = 0U,                                     /*!< USB host control transfer idle state */
    CTL_SETUP,                                         /*!< USB host control transfer SETUP state */
    CTL_SETUP_WAIT,                                    /*!< USB host control transfer SETUP wait state */
    CTL_DATA_IN,                                       /*!< USB host control transfer data IN state */
    CTL_DATA_IN_WAIT,                                  /*!< USB host control transfer data IN wait state */
    CTL_DATA_OUT,                                      /*!< USB host control transfer data OUT state */
    CTL_DATA_OUT_WAIT,                                 /*!< USB host control transfer data OUT wait state */
    CTL_STATUS_IN,                                     /*!< USB host control transfer status IN state */
    CTL_STATUS_IN_WAIT,                                /*!< USB host control transfer status IN wait state */
    CTL_STATUS_OUT,                                    /*!< USB host control transfer status OUT state */
    CTL_STATUS_OUT_WAIT,                               /*!< USB host control transfer status OUT wait state */
    CTL_ERROR,                                         /*!< USB host control transfer error state */
    CTL_FINISH                                         /*!< USB host control transfer finish state */
} usbh_ctl_state;

/* user action state */
typedef enum {
    USR_IN_NO_RESP = 0U,                               /*!< user action IN no response state */
    USR_IN_RESP_OK = 1U                                /*!< user action IN response OK state */
} usbh_user_status;

/* USB host wakeup mode */
typedef enum {
    NORMAL_WORK = 0U,
    GENERAL_WAKEUP = 1U,
    REMOTE_WAKEUP = 2
} usbh_wakeup_mode;

/* control transfer information */
typedef struct _usbh_control {
    uint8_t               pipe_in_num;                 /*!< the number of IN pipe*/
    uint8_t               pipe_out_num;                /*!< the number of OUT pipe */
    uint8_t               max_len;                     /*!< maximum length of control transfer */
    uint8_t               error_count;                 /*!< the count of control error */

    uint8_t               *buf;                        /*!< control transfer buffer */
    uint16_t              ctl_len;                     /*!< the length of control transfer */
    __IO uint32_t         timer;                       /*!< control transfer timer */

    usb_setup             setup;                       /*!< control transfer SETUP packet */
    usbh_ctl_state        ctl_state;                   /*!< host control transfer state */
} usbh_control;

/* USB interface descriptor set */
typedef struct _usb_desc_itf_set {
    usb_desc_itf itf_desc;                             /*!< USB interface descriptor */
    usb_desc_ep  ep_desc[USBH_MAX_EP_NUM];             /*!< USB endpoint descriptor */
} usb_desc_itf_set;

/* USB configure descriptor set */
typedef struct _usb_desc_cfg_set {
    usb_desc_config   cfg_desc;                                                      /*!< USB configuration descriptor */
    usb_desc_itf_set  itf_desc_set[USBH_MAX_INTERFACES_NUM][USBH_MAX_ALT_SETTING];   /*!< USB interface descriptor set*/
} usb_desc_cfg_set;

/* USB device property */
typedef struct {
    uint8_t                   data[USBH_DATA_BUF_MAX_LEN];                           /*!< if DMA is used, the data array must be located in the first position */
    uint8_t                   cur_itf;                                               /*!< USB device current interface */
    uint8_t                   addr;                                                  /*!< USB device address */

    uint32_t                  speed;                                                 /*!< USB device speed */

    usb_desc_dev              dev_desc;                                              /*!< USB device descriptor  */
    usb_desc_cfg_set          cfg_desc_set;                                          /*!< USB interface descriptor set */

#if (1U == USBH_CFG_DESC_KEEP)
    uint8_t                   cfgdesc_rawdata[USBH_CFGSET_MAX_LEN];                  /*!< USB configuration descriptor raw data*/
#endif /* (1U == USBH_CFG_DESC_KEEP) */
} usb_dev_prop;

struct _usbh_host;

/* device class callbacks */
typedef struct {
    uint8_t     class_code;                                                          /*!< USB class type */
    usbh_status (*class_init)(struct _usbh_host *phost);
    void        (*class_deinit)(struct _usbh_host *phost);
    usbh_status (*class_requests)(struct _usbh_host *phost);
    usbh_status (*class_machine)(struct _usbh_host *phost);
    usbh_status (*class_sof)(struct _usbh_host *uhost);
    void         *class_data;                                                       /*!< USB class data pointer */
} usbh_class;

/* user callbacks */
typedef struct {
    void (*dev_init)(void);
    void (*dev_deinit)(void);
    void (*dev_attach)(void);
    void (*dev_reset)(void);
    void (*dev_detach)(void);
    void (*dev_over_currented)(void);
    void (*dev_speed_detected)(uint32_t dev_speed);
    void (*dev_devdesc_assigned)(void *dev_desc);
    void (*dev_address_set)(void);

    void (*dev_cfgdesc_assigned)(usb_desc_config *cfg_desc, \
                                 usb_desc_itf *itf_desc, \
                                 usb_desc_ep *ep_desc);

    void (*dev_mfc_str)(void *mfc_str);
    void (*dev_prod_str)(void *prod_str);
    void (*dev_seral_str)(void *serial_str);
    void (*dev_enumerated)(void);
    usbh_user_status (*dev_user_input)(void);
    int  (*dev_user_app)(void);
    void (*dev_not_supported)(void);
    void (*dev_error)(void);
} usbh_user_cb;

/* host information */
typedef struct _usbh_host {
    usb_host_state                      cur_state;                          /*!< host state machine value */
    usb_host_state                      backup_state;                       /*!< backup of previous state machine value */
    usbh_enum_state                     enum_state;                         /*!< enumeration state machine */
    usbh_control                        control;                            /*!< USB host control state machine */
    usb_dev_prop                        dev_prop;                           /*!< USB device property */

    usbh_class                          *uclass[USBH_MAX_SUPPORTED_CLASS];  /*!< USB host supported class */
    usbh_class                          *active_class;                      /*!< USB active class */
    usbh_user_cb                        *usr_cb;                            /*!< USB user callback */

    uint8_t                             class_num;                          /*!< USB class number */

    void                                *data;                              /*!< used for... */

    uint8_t                             suspend_flag;                       /*!< host suspend flag */
    uint8_t                             dev_supp_remote_wkup;               /*!< record device remote wakeup function */
    usbh_wakeup_mode                    wakeup_mode;                        /*!< record wakeup mode */
} usbh_host;

/*!
    \brief      get USB URB state
    \param[in]  udev: pointer to USB core instance
    \param[in]  pp_num: pipe number
    \param[out] none
    \retval     URB state
*/
static inline usb_urb_state usbh_urbstate_get(usb_core_driver *udev, uint8_t pp_num)
{
    return udev->host.pipe[pp_num].urb_state;
}

/*!
    \brief      get USB transfer data count
    \param[in]  udev: pointer to USB core instance
    \param[in]  pp_num: pipe number
    \param[out] none
    \retval     transfer data count
*/
static inline uint32_t usbh_xfercount_get(usb_core_driver *udev, uint8_t pp_num)
{
    return udev->host.backup_xfercount[pp_num];
}

/* function declarations */
/* USB host stack initializations */
void usbh_init(usbh_host *uhost, usb_core_driver *udev, usb_core_enum usb_core, usbh_user_cb *user_cb);
/* USB host register device class */
usbh_status usbh_class_register(usbh_host *uhost, usbh_class *puclass);
/* de-initialize USB host */
usbh_status usbh_deinit(usbh_host *uhost);
/* USB host core main state machine process */
void usbh_core_task(usbh_host *uhost);
/* handle the error on USB host side */
void usbh_error_handler(usbh_host *uhost, usbh_status err_type);

#endif /* USBH_CORE_H */
