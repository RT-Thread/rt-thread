/*!
    \file    usbd_core.h
    \brief   USB device driver core

    \version 2020-07-17, V3.0.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#ifndef __USBD_CORE_H
#define __USBD_CORE_H

#include "usb_ch9_std.h"

/* endpoints definitions */
#define EP_IN(x)              ((uint8_t)(0x80U | (x)))
#define EP_OUT(x)             ((uint8_t)(x))

#define EP_DIR(x)             ((uint8_t)((x) >> 7U))
#define EP_ID(x)              ((uint8_t)((x) & 0x7FU))

/* USB device endpoint0 max packet size */
#define USBD_EP0_MAX_SIZE     64U

#define USBD_TRANSC_COUNT     3U

/* USB device operation status */
enum usbd_status {
    USBD_UNCONNECTED = 0U,        /*!< USB device unconnected status */
    USBD_DEFAULT,                 /*!< USB device default status */
    USBD_ADDRESSED,               /*!< USB device addressed status */
    USBD_CONFIGURED,              /*!< USB device configured status */
    USBD_SUSPENDED,               /*!< USB device suspended status */
    USBD_CONNECTED                /*!< USB device connected status */
};

/* USB device operation state */
enum usbd_state {
    USBD_OK = 0U,                 /*!< USB device OK state */
    USBD_BUSY,                    /*!< USB device busy state */
    USBD_FAIL                     /*!< USB device fail state */
};

/* USB device  type */
enum usbd_transc {
    TRANSC_SETUP = 0U,            /*!< SETUP transaction */
    TRANSC_OUT,                   /*!< OUT transaction */
    TRANSC_IN,                    /*!< IN transaction */
    TRANSC_UNKNOWN                /*!< unknown transaction */
};

/* USB device endpoint buffer type */
enum usbd_ep_kind {
    EP_BUF_SNG = 0U,              /*!< single buffer endpoint type value */
    EP_BUF_DBL                    /*!< double buffer endpoint type value */
};

/* USB device transaction structure */
typedef struct {
    uint8_t   max_len;            /*!< packet max length */
    uint8_t   ep_stall;           /*!< endpoint STALL */

    uint8_t  *xfer_buf;           /*!< transfer buffer */
    uint16_t  xfer_len;           /*!< transfer length */
    uint16_t  xfer_count;         /*!< transfer count */
} usb_transc;

/* USB device basic structure */
typedef struct {
    uint8_t  max_ep_count;        /*!< endpoint max count */
    uint8_t  twin_buf;            /*!< double buffer */
    uint16_t ram_size;            /*!< ram size */
} usb_basic;

/* USB descriptor */
typedef struct {
    uint8_t *dev_desc;            /*!< device descriptor */
    uint8_t *config_desc;         /*!< configure descriptor */
    uint8_t *bos_desc;            /*!< BOS descriptor */
    uint8_t **strings;            /*!< strings descriptor */
} usb_desc;

/* USB power management */
typedef struct {
    uint8_t  power_mode;          /*!< power mode */
    uint8_t  power_low;           /*!< power low */
    uint8_t  esof_count;          /*!< ESOF count */
    uint8_t  suspend_enabled;     /*!< suspend enabled flag */
    uint8_t  remote_wakeup;       /*!< remote wakeup */
    uint8_t  remote_wakeup_on;    /*!< remote wakeup enable */
    uint8_t  lpm_enable;          /*!< LPM enable */
} usb_pm;

/* USB LPM management */
typedef struct {
    uint32_t besl;                /*!< BESL */
    uint32_t L1_resume;           /*!< L1 resume */
    uint32_t L1_remote_wakeup;    /*!< L1 remote wakeup */
} usb_lpm;

/* USB control information */
typedef struct {
    usb_req    req;               /*!< USB request */
    uint8_t    ctl_zlp;           /*!< control zero length packet */
} usb_control;

typedef struct _usb_dev usb_dev;
typedef struct _usb_handler usb_handler;
typedef void (*usb_ep_transc) (usb_dev *usbd_dev, uint8_t ep_num);

/* USB class structure */
typedef struct {
    uint8_t req_cmd;
    uint8_t req_altset;

    uint8_t (*init)         (usb_dev *udev, uint8_t config_index);
    uint8_t (*deinit)       (usb_dev *udev, uint8_t config_index);

    uint8_t (*req_process)  (usb_dev *udev, usb_req *req);

    uint8_t (*ctlx_in)      (usb_dev *udev);
    uint8_t (*ctlx_out)     (usb_dev *udev);

    void (*data_in)  (usb_dev *udev, uint8_t ep_num);
    void (*data_out) (usb_dev *udev, uint8_t ep_num);
} usb_class;

/* USB core driver structure */
struct _usb_dev {
    /* basic parameters */
    uint8_t         config;
    uint8_t         dev_addr;

    __IO uint8_t    cur_status;
    __IO uint8_t    backup_status;

    usb_pm          pm;
#ifdef LPM_ENABLED
    usb_lpm         lpm;
#endif /* LPM_ENABLED */
    usb_control     control;

    usb_transc      transc_out[EP_COUNT];
    usb_transc      transc_in[EP_COUNT];

    usb_ep_transc   ep_transc[EP_COUNT][USBD_TRANSC_COUNT];

    /* device class */
    usb_desc       *desc;
    usb_class      *class_core;
    usb_handler    *drv_handler;

    void           *class_data[USBD_ITF_MAX_NUM];
    void           *user_data;
    void           *data;
};

typedef struct
{
    uint8_t (*SOF) (usb_dev *udev); /*!< SOF ISR callback */
} usbd_int_cb_struct;

/* USB handler structure */
struct _usb_handler {
    void (*init)             (void);
    void (*deinit)           (void);

    void (*dp_pullup)        (FlagStatus status);
    void (*set_addr)         (usb_dev *udev);
    void (*suspend)          (void);
    void (*suspend_leave)    (void);
    void (*resume)           (usb_dev *udev);

    void (*ep_reset)         (usb_dev *udev);
    void (*ep_setup)         (usb_dev *udev, uint8_t buf_kind, uint32_t buf_addr, const usb_desc_ep *ep_desc);
    void (*ep_disable)       (usb_dev *udev, uint8_t ep_addr);
    void (*ep_rx_enable)     (usb_dev *udev, uint8_t ep_num);
    void (*ep_write)         (uint8_t *fifo, uint8_t ep_num, uint16_t bytes);
    uint16_t (*ep_read)      (uint8_t *fifo, uint8_t ep_num, uint8_t buf_kind);
    void (*ep_stall_set)     (usb_dev *udev, uint8_t ep_addr);
    void (*ep_stall_clear)   (usb_dev *udev, uint8_t ep_addr);
    uint8_t (*ep_status_get) (usb_dev *udev, uint8_t ep_addr);
};

extern usbd_int_cb_struct *usbd_int_fops;

/* static inline function definitions */
/*!
    \brief      device connect
    \param[in]  udev: pointer to USB core instance
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_connect (usb_dev *udev)
{
    udev->drv_handler->dp_pullup(SET);

    udev->cur_status = (uint8_t)USBD_CONNECTED;
}


/*!
    \brief      device disconnect
    \param[in]  udev: pointer to USB core instance
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_disconnect (usb_dev *udev)
{
    udev->drv_handler->dp_pullup(RESET);

    udev->cur_status = (uint8_t)USBD_UNCONNECTED;
}

/*!
    \brief      device core register configure when stop device
    \param[in]  udev: pointer to USB core instance
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_core_deinit (usb_dev *udev)
{
    udev->drv_handler->deinit();
}

/*!
    \brief      initialize endpoint
    \param[in]  udev: pointer to USB core instance
    \param[in]  buf_kind: endpoint buffer kind
    \param[in]  buf_addr: buffer address
    \param[in]  ep_desc: pointer to endpoint descriptor
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_ep_init (usb_dev *udev, uint8_t buf_kind, uint32_t buf_addr, const usb_desc_ep *ep_desc)
{
    udev->drv_handler->ep_setup(udev, buf_kind, buf_addr, ep_desc);
}

/*!
    \brief      configure the endpoint when it is disabled
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_ep_deinit (usb_dev *udev, uint8_t ep_addr)
{
    udev->drv_handler->ep_disable(udev, ep_addr);
}

/*!
    \brief      set an endpoint to STALL status
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_ep_stall (usb_dev *udev, uint8_t ep_addr)
{
    udev->drv_handler->ep_stall_set(udev, ep_addr);
}

/*!
    \brief      clear endpoint stalled status
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_ep_clear_stall (usb_dev *udev, uint8_t ep_addr)
{
    udev->drv_handler->ep_stall_clear(udev, ep_addr);
}

/*!
    \brief      get endpoint status
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
__STATIC_INLINE uint8_t usbd_ep_status_get (usb_dev *udev, uint8_t ep_addr)
{
    return udev->drv_handler->ep_status_get(udev, ep_addr);
}

/* function declarations */
/* initialize USBD */
void usbd_init(usb_dev *udev, usb_desc *desc, usb_class *usbc);
/* endpoint prepare to transmit data */
void usbd_ep_send (usb_dev *udev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len);
/* endpoint prepare to receive data */
void usbd_ep_recev (usb_dev *udev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len);

#endif /* __USBD_CORE_H */
