/*!
    \file  usbd_core.h
    \brief USB device driver core
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.0, firmware for GD32F30x
*/

#ifndef USBD_CORE_H
#define USBD_CORE_H

#include "usbd_conf.h"
#include "usbd_regs.h"

/* interrupt flag mask which decide what event should be handled by application */
#define IER_MASK          (CTL_STIE | CTL_WKUPIE | CTL_SPSIE \
                            | CTL_SOFIE | CTL_ESOFIE | CTL_RSTIE)

#ifdef LPM_ENABLED
#undef IER_MASK

#define IER_MASK          (CTL_STIE | CTL_WKUPIE | CTL_SPSIE \
                            | CTL_SOFIE | CTL_ESOFIE | CTL_RSTIE | CTL_L1REQIE)
#endif /* LPM_ENABLED */

/* USB device endpoint0 max packet size */
#define USBD_EP0_MAX_SIZE     64U

#define USBD_CONTRL_STATUS_TX() do \
{ \
    pbuf_reg->tx_count = 0U; \
    USBD_ENDP_TX_STATUS_SET(EP0, EPTX_VALID); \
} while(0)

#define USBD_CONTRL_STATUS_RX() do \
{ \
    USBD_STATUS_OUT_SET(EP0); \
    USBD_ENDP_RX_STATUS_SET(EP0, EPRX_VALID); \
} while(0)

#define ENDP_BUF_ADDR         (sizeof(usbd_ep_buf_struct) * EP_COUNT)

/* USB device endpoint type */
typedef enum
{
    ENDP_CONTROL = 0, /*!< control endpoint type value */
    ENDP_ISOC,        /*!< isochronous endpoint type value */
    ENDP_BULK,        /*!< bulk endpoint type value */
    ENDP_INT          /*!< interupt endpoint type value */
}usbd_eptype_enum;

/* USB device endpoint kind */
typedef enum
{
    ENDP_SNG_BUF = 0, /*!< single buffer endpoint type value */
    ENDP_DBL_BUF      /*!< double buffer endpoint type value */
}usbd_epkind_enum;

/* transfer direction */
typedef enum
{
    USBD_RX = 0,      /*!< receive direction type value */
    USBD_TX           /*!< transmit direction type value */
}usbd_dir_enum;

/* USB device status */
typedef enum
{
    USBD_UNCONNECTED = 0, /*!< USB device unconnected status */
    USBD_DEFAULT,         /*!< USB device default status */
    USBD_ADDRESSED,       /*!< USB device addressed status */
    USBD_CONFIGURED,      /*!< USB device configured status */
    USBD_SUSPENDED,       /*!< USB device suspended status */
    USBD_CONNECTED        /*!< USB device connected status */
}usbd_run_status_enum;

/* USB device operation state */
typedef enum
{
    USBD_OK = 0,          /*!< USB device ok */
    USBD_BUSY,            /*!< USB device busy */
    USBD_FAIL             /*!< USB device fail */
}usbd_status_enum;

typedef struct
{
    uint16_t tx_addr;    /*!< transmission address */
    uint16_t reserved0;
    uint16_t tx_count;   /*!< transmission count */
    uint16_t reserved1;
    uint16_t rx_addr;    /*!< reception address */
    uint16_t reserved2;
    uint16_t rx_count;   /*!< reception count */
    uint16_t reserved3;
}usbd_ep_buf_struct;

/* USB endpoint structure */
typedef struct
{
    /* basic parameters */
    uint8_t        stall;            /*!< endpoint stall status */
    uint32_t       maxpacket;        /*!< the maxpacket of the endpoint */

    /* transaction level parameters */
    uint8_t       *trs_buf;          /*!< transaction buffer address */
    uint32_t       trs_len;          /*!< transaction buffer length */
    uint32_t       trs_count;        /*!< transaction data counts */
}usb_ep_struct;

/* USB standard device request structure */
typedef struct
{
    uint8_t    bmRequestType; /*!< the property of the request */
    uint8_t    bRequest;      /*!< the code of the request */
    uint16_t   wValue;        /*!< the value of the request which used to choose the different request in the same code request */
    uint16_t   wIndex;        /*!< USB standard device request index */
    uint16_t   wLength;       /*!< the return datas length that the host wants to get */
}usb_device_req_struct;

/* USB core driver struct */
typedef struct
{
    /* basic parameters */
    uint8_t  config_num;      /*!< the number of the USB device configuration */
    uint8_t  status;          /*!< USB device status */
    uint8_t  prev_status;     /*!< the previous USB device status */
    uint8_t  remote_wakeup;   /*!< the flag that point out the device whether support the 
                                   remte wakeup function */

    /* the parameters which needs in control transfer */
    uint8_t  setup_packet[8];      /*!< the buffer used to store the setup packet */
    uint32_t ctl_count;            /*!< the datas length of control transfer request */

    /* device endpoints */
    usb_ep_struct in_ep[EP_COUNT];      /*!< the IN direction endpoints */
    usb_ep_struct out_ep[EP_COUNT];     /*!< the OUT direction endpoints */

#ifdef LPM_ENABLED
    uint8_t *bos_desc;                  /*!< BOS descriptor */
#endif /* LPM_ENABLED */

    uint8_t *dev_desc;                  /*!< device descriptor */
    uint8_t *config_desc;               /*!< configuration descriptor */
    void* const *strings;               /*!< configuration strings */

    /* device class handler */
    usbd_status_enum (*class_init)         (void *pudev, uint8_t config_index);
    usbd_status_enum (*class_deinit)       (void *pudev, uint8_t config_index);
    usbd_status_enum (*class_req_handler)  (void *pudev, usb_device_req_struct *req);
    usbd_status_enum (*class_data_handler) (void *pudev, usbd_dir_enum rx_tx, uint8_t ep_num);
}usbd_core_handle_struct;

extern uint32_t g_free_buf_addr;
extern usbd_ep_buf_struct *pbuf_reg;

/* function declarations */
/* device core register initialization */
void  usbd_core_init (usbd_core_handle_struct *pudev);
/* device core register configure when stop device */
void  usbd_core_deinit (void);

/* free buffer used from application by toggling the SW_BUF byte */
void  user_buffer_free (uint8_t ep_num, uint8_t dir);

/* endpoint initialization */
void  usbd_ep_init (usbd_core_handle_struct *pudev, void *pep_desc);
/* configure the endpoint when it is disabled */
void  usbd_ep_deinit (usbd_core_handle_struct *pudev, uint8_t ep_addr);
/* endpoint prepare to transmit data */
void  usbd_ep_tx (usbd_core_handle_struct *pudev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len);
/* endpoint prepare to receive data */
void  usbd_ep_rx (usbd_core_handle_struct *pudev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len);
/* set an endpoint to STALL status */
void  usbd_ep_stall (usbd_core_handle_struct *pudev, uint8_t ep_addr);
/* clear endpoint stalled status */
void  usbd_ep_clear_stall (usbd_core_handle_struct *pudev, uint8_t ep_addr);
/* write datas from user fifo to USBRAM */
void  usbd_ep_data_write (uint8_t *user_fifo, uint16_t usbram_addr, uint16_t bytes);
/* read datas from USBRAM to user fifo */
void  usbd_ep_data_read (uint8_t *user_fifo, uint16_t usbram_addr, uint16_t bytes);

/* get the endpoint status */
uint8_t  usbd_ep_status_get (usbd_core_handle_struct *pudev, uint8_t ep_addr);

/* get the received data length */
uint16_t  usbd_rx_count_get (usbd_core_handle_struct *pudev, uint8_t ep_num);

#endif /* USBD_CORE_H */
