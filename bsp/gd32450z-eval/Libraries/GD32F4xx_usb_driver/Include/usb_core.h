/*!
    \file  usb_core.h
    \brief USB core driver header file
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef USB_CORE_H
#define USB_CORE_H

#include "usb_conf.h"
#include "usb_regs.h"
#include "usb_defines.h"

#define USB_MAX_EP0_SIZE                        64U   /* endpoint 0 max packet size */
#define RX_MAX_DATA_LENGTH                      512U  /* host rx buffer max data length */
#define HC_MAX_PACKET_COUNT                     140U  /* host channel max packet count */

#ifdef USE_USBFS
    #define USB_MAX_DEV_EPCOUNT                 USBFS_MAX_DEV_EPCOUNT
    #define USB_MAX_FIFOS                       (USBFS_MAX_HOST_CHANNELCOUNT * 2U - 1U)
#elif defined(USE_USBHS)
    #define USB_MAX_DEV_EPCOUNT                 USBHS_MAX_DEV_EPCOUNT
    #define USB_MAX_FIFOS                       (USBHS_MAX_HOST_CHANNELCOUNT * 2U - 1U)
#endif /* USE_USBFS */

/* USB core status */
typedef enum
{
    USB_OK = 0,         /* USB core OK status */
    USB_FAIL            /* USB core fail status */
}usb_status_enum;

/* USB host channel status */
typedef enum
{
    HC_IDLE = 0,        /* USB host channel idle status */
    HC_XF,              /* USB host channel transfer status */
    HC_HALTED,          /* USB host channel halted status */
    HC_NAK,             /* USB host channel nak status */
    HC_NYET,            /* USB host channel nyet status */
    HC_STALL,           /* USB host channel stall status */
    HC_TRACERR,         /* USB host channel tracerr status */
    HC_BBERR,           /* USB host channel bberr status */
    HC_DTGERR,          /* USB host channel dtgerr status */
}hc_status_enum;

/* USB URB(USB request block) state */
typedef enum
{
    URB_IDLE = 0,       /* USB URB idle status */
    URB_DONE,           /* USB URB done status */
    URB_NOTREADY,       /* USB URB notready status */
    URB_ERROR,          /* USB URB error status */
    URB_STALL,          /* USB URB stall status */
    URB_PING            /* USB URB ping status */
}urb_state_enum;

/* USB core configuration */
typedef struct
{
    uint8_t        core_id;            /* USB core id */
    uint8_t        core_speed;         /* USB core speed */
    uint8_t        phy_interface;      /* USB PHY interface */
    uint8_t        host_channel_num;   /* USB host channel number */
    uint8_t        dev_endp_num;       /* USB device endpoint number */
    uint8_t        dma_enable;         /* USBHS can use DMA  */
    uint8_t        sof_output;         /* USB SOF output */
    uint8_t        low_power;          /* USB low power */
    uint16_t       max_packet_size;    /* USB max packet size */
    uint16_t       max_fifo_size;      /* USB fifo size */
}usb_core_cfgs_struct;

typedef enum
{
    USBD_OK = 0,      /* USB device ok status */
    USBD_BUSY,        /* USB device busy status */
    USBD_FAIL,        /* USB device fail stauts */
}usbd_status_enum;

/* USB control transfer state */
typedef enum
{
    USB_CTRL_IDLE = 0,     /* USB control transfer idle state */
    USB_CTRL_SETUP,        /* USB control transfer setup state */
    USB_CTRL_DATA_IN,      /* USB control transfer data in state */
    USB_CTRL_DATA_OUT,     /* USB control transfer data out state */
    USB_CTRL_STATUS_IN,    /* USB control transfer status in state*/
    USB_CTRL_STATUS_OUT,   /* USB control transfer status out state */
    USB_CTRL_STALL         /* USB control transfer stall state */
}usbd_control_state_enum;

/* USB transfer direction */
typedef enum
{
    USBD_RX = 0,         /* receive direction type value */
    USBD_TX              /* transmit direction type value */
}usbd_dir_enum;

/* USB endpoint in device mode */
typedef struct
{
    uint8_t         endp_type;   /* USB endpoint type */
    uint8_t         endp_frame;  /* USB endpoint frame */
    uint32_t        endp_mps;    /* USB endpoint max packet size */

    /* Transaction level variables */
    uint8_t        *xfer_buff;   /* USB transfer buffer */
    uint32_t        xfer_len;    /* USB transfer length */
    uint32_t        xfer_count;  /* USB transfer count */

    uint32_t        dma_addr;    /* USBHS can use DMA */
}usb_ep_struct;

/* USB device standard request */
typedef struct
{
    uint8_t         bmRequestType;  /* USB device request type */
    uint8_t         bRequest;       /* USB device request */
    uint16_t        wValue;         /* USB device request value */
    uint16_t        wIndex;         /* USB device request index */
    uint16_t        wLength;        /* USB device request length */
}usb_device_req_struct;

/* USB core device driver */
typedef struct
{
    uint8_t         config_num;          /* USB configuration number */
    uint8_t         status;              /* USB status */
    uint8_t         ctl_status;          /* USB control status */
    uint8_t         prev_status;         /* USB previous status */
    uint8_t         connection_status;   /* USB connection status */
    uint32_t        remote_wakeup;       /* USB remote wakeup */

    /* transfer level variables */
    uint32_t        remain_len;          /* USB remain length */
    uint32_t        sum_len;             /* USB sum length */
    uint32_t        ctl_len;             /* USB control length */
    uint8_t         setup_packet[8 * 3]; /* USB setup packet */

    usb_ep_struct   in_ep[USB_MAX_DEV_EPCOUNT];   /* USB IN endpoint */
    usb_ep_struct   out_ep[USB_MAX_DEV_EPCOUNT];  /* USB OUT endpoint */

    uint8_t  *dev_desc;                  /* device descriptor */
    uint8_t  *config_desc;               /* configuration descriptor */
    uint8_t* *strings;                   /* configuration strings */

    /* device class handler */
    uint8_t (*class_init)         (void *pudev, uint8_t config_index);         /* device class initialize */
    uint8_t (*class_deinit)       (void *pudev, uint8_t config_index);         /* device class deinitialize */
    uint8_t (*class_req_handler)  (void *pudev, usb_device_req_struct *req);   /* device request handler */
    uint8_t (*class_data_handler) (void *pudev, usbd_dir_enum rx_tx, uint8_t ep_id);  /* device data handler */
}dcd_dev_struct;

/* USB core host mode channel */
typedef struct
{
    uint8_t         dev_addr;     /* device address */
    uint8_t         dev_speed;    /* device speed */
    uint8_t         DPID;         /* endpoint transfer data pid */
    uint8_t         endp_id;      /* endpoint id */
    uint8_t         endp_in;      /* endpoint in */
    uint8_t         endp_type;    /* endpoint type */
    uint16_t        endp_mps;     /* endpoint max pactet size */
    uint16_t        info;         /* channel information */

    uint8_t         do_ping;      /* USBHS ping */

    uint8_t        *xfer_buff;    /* transfer buffer */
    uint32_t        xfer_len;     /* transfer length */
    uint32_t        xfer_count;   /* trasnfer count */

    uint32_t        err_count;    /* USB transfer error count */
    uint32_t        dma_addr;     /* USBHS can use DMA */

    hc_status_enum  status;       /* channel status */
    urb_state_enum  urb_state;    /* URB state */

    uint8_t         data_tg_in;   /* data in toggle */
    uint8_t         data_tg_out;  /* data out toggle */
}usb_hostchannel_struct;

/* USB core host driver */
typedef struct
{
    uint8_t                 rx_buffer[RX_MAX_DATA_LENGTH]; /* rx buffer */
    uint8_t                 connect_status;                /* device connect status */
    usb_hostchannel_struct  host_channel[USB_MAX_FIFOS];   /* host channel */
    void (*vbus_drive)     (void *pudev, uint8_t state);   /* the vbus driver function */
}hcd_dev_struct;

#ifdef USE_OTG_MODE

/* USB core OTG-mode driver */
typedef struct
{
    uint8_t         OTG_State;      /* OTG state */
    uint8_t         OTG_PrevState;  /* OTG previous state */
    uint8_t         OTG_Mode;       /* OTG mode */
}otg_dev_struct;

#endif /* USE_OTG_MODE */

/* USB core driver */
typedef struct
{
    usb_core_cfgs_struct   cfg;

#ifdef USE_DEVICE_MODE
    dcd_dev_struct         dev;
#endif /* USE_DEVICE_MODE */

#ifdef USE_HOST_MODE
    hcd_dev_struct         host;
#endif /* USE_HOST_MODE */

#ifdef USE_OTG_MODE
    otg_dev_struct         otg;
#endif /* USE_OTG_MODE */

    void (*udelay) (const uint32_t usec);
    void (*mdelay) (const uint32_t msec);
}usb_core_handle_struct;

/* function declarations */

/* global APIs */
/* initializes the USB controller registers and prepares the core device mode or host mode operation */
usb_status_enum usb_core_init (usb_core_handle_struct *pudev);
/* initialize core parameters */
usb_status_enum usb_core_select (usb_core_handle_struct *pudev, usb_core_id_enum core_id);
/* read a packet from the Rx FIFO associated with the endpoint */
void* usb_fifo_read (uint8_t *dest, uint16_t len);
/* write a packet into the Tx FIFO associated with the endpoint */
usb_status_enum usb_fifo_write (uint8_t *src, uint8_t ep_id, uint16_t len);
/* flush a Tx FIFO or all Tx FIFOs */
usb_status_enum usb_txfifo_flush (usb_core_handle_struct *pudev, uint8_t fifo_num);
/* flush the entire Rx FIFO */
usb_status_enum usb_rxfifo_flush (usb_core_handle_struct *pudev);
/* set operation mode (host or device) */
usb_status_enum usb_mode_set (usb_core_handle_struct *pudev, uint8_t mode);

/* host APIs */
#ifdef USE_HOST_MODE

/* initializes USB core for host mode */
usb_status_enum usb_hostcore_init (usb_core_handle_struct *pudev);
/* enables the host mode interrupts */
usb_status_enum usb_hostint_enable (usb_core_handle_struct *pudev);
/* initialize host channel */
usb_status_enum usb_hostchannel_init (usb_core_handle_struct *pudev, uint8_t hc_num);
/* halt channel */
usb_status_enum usb_hostchannel_halt (usb_core_handle_struct *pudev, uint8_t hc_num);
/* prepare host channel for transferring packets */
usb_status_enum usb_hostchannel_startxfer (usb_core_handle_struct *pudev, uint8_t hc_num);
/* issue a ping token */
usb_status_enum usb_hostchannel_ping (usb_core_handle_struct *pudev, uint8_t hc_num);
/* reset host port */
uint32_t usb_port_reset (usb_core_handle_struct *pudev);
/* control the VBUS to power */
void usb_vbus_drive (usb_core_handle_struct *pudev, uint8_t state);
/* stop the USB host and clean up fifos */
void usb_host_stop (usb_core_handle_struct *pudev);

#endif /* USE_HOST_MODE */

/* device APIs */
#ifdef USE_DEVICE_MODE

/* initialize USB core registers for device mode */
usb_status_enum usb_devcore_init (usb_core_handle_struct *pudev);
/* configures endpoint 0 to receive SETUP packets */
void usb_ep0_startout (usb_core_handle_struct *pudev);
/* active remote wakeup signalling */
void usb_remotewakeup_active (usb_core_handle_struct *pudev);
/* active USB core clock */
void usb_clock_ungate (usb_core_handle_struct *pudev);
/* stop the device and clean up fifos */
void usb_device_stop (usb_core_handle_struct *pudev);

#endif /* USE_DEVICE_MODE */

#endif  /* USB_CORE_H */
