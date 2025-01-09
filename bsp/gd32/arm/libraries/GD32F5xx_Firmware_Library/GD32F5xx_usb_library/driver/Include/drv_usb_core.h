/*!
    \file    drv_usb_core.h
    \brief   USB core low level driver header file

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

#ifndef DRV_USB_CORE_H
#define DRV_USB_CORE_H

#include "drv_usb_regs.h"
#include "usb_ch9_std.h"

#define USB_FS_EP0_MAX_LEN                  64U                                 /*!< maximum packet size of endpoint 0 */
#define HC_MAX_PACKET_COUNT                 140U                                /*!< maximum packet count */

#define EP_ID(x)                            ((uint8_t)((x) & 0x7FU))            /*!< endpoint number */
#define EP_DIR(x)                           ((uint8_t)((x) >> 7))               /*!< endpoint direction */

#define EP_MAX_PACKET_SIZE_MASK             0x07FFU                             /*!< endpoint maximum packet size mask */

enum _usb_mode {
    DEVICE_MODE = 0U,                                                           /*!< device mode */
    HOST_MODE,                                                                  /*!< host mode */
    OTG_MODE                                                                    /*!< OTG mode */
};

enum _usb_eptype {
    USB_EPTYPE_CTRL = 0U,                                                       /*!< control endpoint type */
    USB_EPTYPE_ISOC = 1U,                                                       /*!< isochronous endpoint type */
    USB_EPTYPE_BULK = 2U,                                                       /*!< bulk endpoint type */
    USB_EPTYPE_INTR = 3U,                                                       /*!< interrupt endpoint type */
    USB_EPTYPE_MASK = 3U                                                        /*!< endpoint type mask */
};

typedef enum {
    USB_OTG_OK = 0U,                                                            /*!< USB OTG status succeed */
    USB_OTG_FAIL                                                                /*!< USB OTG status fail */
} usb_otg_status;

typedef enum {
    USB_OK = 0U,                                                                /*!< USB status succeed */
    USB_FAIL                                                                    /*!< USB status fail */
} usb_status;

typedef enum {
    USB_USE_FIFO = 0U,                                                          /*!< USB use FIFO transfer mode */
    USB_USE_DMA                                                                 /*!< USB use DMA transfer mode */
} usb_transfer_mode;

typedef struct {
    uint8_t        core_enum;                                                   /*!< USB core type */
    uint8_t        core_speed;                                                  /*!< USB core speed */
    uint8_t        num_pipe;                                                    /*!< USB host channel numbers */
    uint8_t        num_ep;                                                      /*!< USB device endpoint numbers */
    uint8_t        transfer_mode;                                               /*!< USB transfer mode */
    uint8_t        phy_itf;                                                     /*!< USB core PHY interface */
    uint8_t        sof_enable;                                                  /*!< USB SOF output */
    uint8_t        low_power;                                                   /*!< USB low power */
    uint8_t        lpm_enable;                                                  /*!< USB link power mode(LPM) */
    uint8_t        vbus_sensing_enable;                                         /*!< USB VBUS sensing feature */
    uint8_t        use_dedicated_ep1;                                           /*!< USB dedicated endpoint1 interrupt */
    uint8_t        use_external_vbus;                                           /*!< enable or disable the use of the external VBUS */
    uint32_t       base_reg;                                                    /*!< base register address */
} usb_core_basic;

#ifdef USE_DEVICE_MODE

/* USB descriptor */
typedef struct _usb_desc {
    uint8_t *dev_desc;                                                          /*!< device descriptor */
    uint8_t *config_desc;                                                       /*!< configure descriptor */
    uint8_t *bos_desc;                                                          /*!< BOS descriptor */

#if defined(USE_USB_HS) && defined(USE_ULPI_PHY)
    uint8_t *other_speed_config_desc;                                           /*!< other speed configuration descriptor */
    uint8_t *qualifier_desc;                                                    /*!< qualifier descriptor */
#endif

    void* const *strings;                                                       /*!< string descriptor */
} usb_desc;

/* USB power management */
typedef struct _usb_pm {
    uint8_t  power_mode;                                                        /*!< power mode */
    uint8_t  power_low;                                                         /*!< power low */
    uint8_t  dev_remote_wakeup;                                                 /*!< remote wakeup */
    uint8_t  remote_wakeup_on;                                                  /*!< remote wakeup on */
} usb_pm;

/* USB control information */
typedef struct _usb_control {
    usb_req    req;                                                             /*!< USB standard device request */

    uint8_t    ctl_state;                                                       /*!< USB control transfer state */
    uint8_t    ctl_zlp;                                                         /*!< zero length package */
} usb_control;

typedef struct {
    struct {
        uint8_t num: 4U;                                                        /*!< the endpoint number.it can be from 0 to 6 */
        uint8_t pad: 3U;                                                        /*!< padding between number and direction */
        uint8_t dir: 1U;                                                        /*!< the endpoint direction */
    } ep_addr;

    uint8_t        ep_type;                                                     /*!< USB endpoint type */
    uint8_t        ep_stall;                                                    /*!< USB endpoint STALL status */

    uint8_t        frame_num;                                                   /*!< number of frame */
    uint16_t       max_len;                                                     /*!< maximum packet length */

    /* transaction level variables */
    uint8_t       *xfer_buf;                                                    /*!< transmit buffer */
    uint32_t       xfer_len;                                                    /*!< transmit buffer length */
    uint32_t       xfer_count;                                                  /*!< transmit buffer count */

    uint32_t       remain_len;                                                  /*!< remain packet length */

    uint32_t       dma_addr;                                                    /*!< DMA address */
} usb_transc;

typedef struct _usb_core_driver usb_dev;

typedef struct _usb_class_core {
    uint8_t  command;                                                           /*!< device class request command */
    uint8_t  alter_set;                                                         /*!< alternative set */

    uint8_t  (*init)(usb_dev *udev, uint8_t config_index);                      /*!< initialize handler */
    uint8_t  (*deinit)(usb_dev *udev, uint8_t config_index);                    /*!< de-initialize handler */

    uint8_t  (*req_proc)(usb_dev *udev, usb_req *req);                          /*!< device request handler */

    uint8_t  (*set_intf)(usb_dev *udev, usb_req *req);                          /*!< device set interface callback */

    uint8_t  (*ctlx_in)(usb_dev *udev);                                         /*!< device control IN callback */
    uint8_t  (*ctlx_out)(usb_dev *udev);                                        /*!< device control OUT callback */

    uint8_t  (*data_in)(usb_dev *udev, uint8_t ep_num);                         /*!< device data IN handler */
    uint8_t  (*data_out)(usb_dev *udev, uint8_t ep_num);                        /*!< device data OUT handler */

    uint8_t  (*SOF)(usb_dev *udev);                                             /*!< start of frame handler */

    uint8_t  (*incomplete_isoc_in)(usb_dev *udev);                              /*!< incomplete synchronization IN transfer handler */
    uint8_t  (*incomplete_isoc_out)(usb_dev *udev);                             /*!< incomplete synchronization OUT transfer handler */
} usb_class_core;

typedef struct _usb_perp_dev {
    uint8_t            config;                                                  /*!< configuration */
    uint8_t            dev_addr;                                                /*!< device address */

    __IO uint8_t       cur_status;                                              /*!< current status */
    __IO uint8_t       backup_status;                                           /*!< backup status */

    usb_transc         transc_in[USBFS_MAX_TX_FIFOS];                           /*!< endpoint IN transaction */
    usb_transc         transc_out[USBFS_MAX_TX_FIFOS];                          /*!< endpoint OUT transaction */

    usb_pm             pm;                                                      /*!< power management */
    usb_control        control;                                                 /*!< USB control information */
    usb_desc          *desc;                                                    /*!< USB descriptors pointer */
    usb_class_core    *class_core;                                              /*!< class driver */
    void              *class_data[6];                                           /*!< class data pointer */
    void              *user_data;                                               /*!< user data pointer */
    void              *pdata;                                                   /*!< reserved data pointer */
} usb_perp_dev;

#endif /* USE_DEVICE_MODE */

#ifdef USE_HOST_MODE

typedef enum _usb_pipe_status {
    PIPE_IDLE = 0U,                                                             /*!< host pipe IDLE status */
    PIPE_XF,                                                                    /*!< host pipe transfer completed status */
    PIPE_HALTED,                                                                /*!< host pipe halted status */
    PIPE_NAK,                                                                   /*!< host pipe NAK status */
    PIPE_NYET,                                                                  /*!< host pipe NYET status */
    PIPE_STALL,                                                                 /*!< host pipe STALL status */
    PIPE_TRACERR,                                                               /*!< host pipe transaction error status */
    PIPE_BBERR,                                                                 /*!< host pipe babble error status */
    PIPE_REQOVR,                                                                /*!< host pipe frame overrun status */
    PIPE_DTGERR                                                                 /*!< host pipe data toggle error status */
} usb_pipe_status;

typedef enum _usb_pipe_mode {
    PIPE_PERIOD     = 0U,                                                       /*!< USB host pipe PERIOD mode */
    PIPE_NON_PERIOD = 1U                                                        /*!< USB host pipe NOT PERIOD mode */
} usb_pipe_mode;

typedef enum _usb_urb_state {
    URB_IDLE = 0U,                                                              /*!< USB URB IDLE state */
    URB_DONE,                                                                   /*!< USB URB DONE state */
    URB_NOTREADY,                                                               /*!< USB URB NOT READY state */
    URB_ERROR,                                                                  /*!< USB URB ERROR state */
    URB_STALL,                                                                  /*!< USB URB STALL state */
    URB_PING                                                                    /*!< USB URB PING state */
} usb_urb_state;

typedef struct _usb_pipe {
    uint8_t              in_used;                                               /*!< pipe used */
    uint8_t              dev_addr;                                              /*!< USB device address */
    uint32_t             dev_speed;                                             /*!< USB device speed */

    struct {
        uint8_t          num;                                                   /*!< endpoint numbers */
        uint8_t          dir;                                                   /*!< endpoint direction */
        uint8_t          type;                                                  /*!< endpoint transfer type */
        uint16_t         mps;                                                   /*!< endpoint max packet size */
    } ep;

    __IO uint8_t         supp_ping;                                             /*!< host pipe support PING */
    __IO uint8_t         do_ping;                                               /*!< host pipe do PING  */
    __IO uint32_t        DPID;                                                  /*!< data PID */

    uint8_t              *xfer_buf;                                             /*!< USB transfer buffer */
    uint32_t             xfer_len;                                              /*!< USB transfer length */
    uint32_t             xfer_count;                                            /*!< USB transfer count */

    uint8_t              data_toggle_in;                                        /*!< toggle DATA IN */
    uint8_t              data_toggle_out;                                       /*!< toggle DATA OUT */

    __IO uint32_t        err_count;                                             /*!< error count */
    __IO usb_pipe_status pp_status;                                             /*!< USB pipe status */
    __IO usb_urb_state   urb_state;                                             /*!< USB urb state */
} usb_pipe;

typedef struct _usb_host_drv {
    __IO uint32_t            connect_status;                                    /*!< connect status */
    __IO uint32_t            port_enabled;                                      /*!< USB port enable */
    __IO uint32_t            backup_xfercount[USBFS_MAX_TX_FIFOS];              /*!< USB backup transfer data count */

    usb_pipe                 pipe[USBFS_MAX_TX_FIFOS];                          /*!< USB host pipe handles */
    void                     *data;                                             /*!< user data pointer */
} usb_host_drv;

#endif /* USE_HOST_MODE */

typedef struct _usb_core_driver {
    usb_core_basic     bp;                                                      /*!< USB basic parameters */
    usb_core_regs      regs;                                                    /*!< USB registers */

#ifdef USE_DEVICE_MODE
    usb_perp_dev       dev;                                                     /*!< USB peripheral device */
#endif /* USE_DEVICE_MODE */

#ifdef USE_HOST_MODE
    usb_host_drv       host;                                                    /*!< USB peripheral host */
#endif /* USE_HOST_MODE */
} usb_core_driver;

/* static inline function definitions */

/*!
    \brief      get the global interrupts
    \param[in]  usb_regs: pointer to USB core registers
    \param[out] none
    \retval     interrupt status
*/
__STATIC_INLINE uint32_t usb_coreintr_get(usb_core_regs *usb_regs)
{
    uint32_t reg_data = usb_regs->gr->GINTEN;

    reg_data &= usb_regs->gr->GINTF;

    return reg_data;
}

/*!
    \brief      set USB RX FIFO size
    \param[in]  usb_regs: pointer to USB core registers
    \param[in]  size: assigned FIFO size
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_set_rxfifo(usb_core_regs *usb_regs, uint16_t size)
{
    usb_regs->gr->GRFLEN = size;
}

/*!
    \brief      enable the global interrupts
    \param[in]  usb_regs: pointer to USB core registers
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_globalint_enable(usb_core_regs *usb_regs)
{
    /* enable USB global interrupt */
    usb_regs->gr->GAHBCS |= GAHBCS_GINTEN;
}

/*!
    \brief      disable the global interrupts
    \param[in]  usb_regs: pointer to USB core registers
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_globalint_disable(usb_core_regs *usb_regs)
{
    /* disable USB global interrupt */
    usb_regs->gr->GAHBCS &= ~GAHBCS_GINTEN;
}

/* function declarations */
/* configure core capabilities */
usb_status usb_basic_init(usb_core_basic *usb_basic, usb_core_regs *usb_regs, usb_core_enum usb_core);
/* initializes the USB controller registers and prepares the core device mode or host mode operation */
usb_status usb_core_init(usb_core_basic usb_basic, usb_core_regs *usb_regs);
/* write a packet into the TX FIFO associated with the endpoint */
usb_status usb_txfifo_write(usb_core_regs *usb_regs, uint8_t *src_buf, uint8_t  fifo_num, uint16_t byte_count);
/* read a packet from the RX FIFO associated with the endpoint */
void *usb_rxfifo_read(usb_core_regs *usb_regs, uint8_t *dest_buf, uint16_t byte_count);
/* flush a TX FIFO or all TX FIFOs */
usb_status usb_txfifo_flush(usb_core_regs *usb_regs, uint8_t fifo_num);
/* flush the entire RX FIFO */
usb_status usb_rxfifo_flush(usb_core_regs *usb_regs);
/* set endpoint or channel TX FIFO size */
void usb_set_txfifo(usb_core_regs *usb_regs, uint8_t fifo, uint16_t size);
/* set USB current mode */
void usb_curmode_set(usb_core_regs *usb_regs, uint8_t mode);

#endif /* DRV_USB_CORE_H */
