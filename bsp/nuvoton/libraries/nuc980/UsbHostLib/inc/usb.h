/**************************************************************************//**
 * @file     usb.h
 * @version  V1.00
 * @brief    USB Host library header file.
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef _USBH_H_
#define _USBH_H_

#include "config.h"
#include "usbh_lib.h"
#include "ehci.h"
#include "ohci.h"

/// @cond HIDDEN_SYMBOLS

struct utr_t;
struct udev_t;
struct hub_dev_t;
struct iface_t;
struct ep_info_t;

/*----------------------------------------------------------------------------------*/
/*   USB device request setup packet                                                */
/*----------------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__))
{
    uint8_t  bmRequestType;
    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
}
DEV_REQ_T;

/*
 *  bmRequestType[7]    - Data transfer direction
 */
#define REQ_TYPE_OUT                   0x00
#define REQ_TYPE_IN                    0x80
/*
 *  bmRequestType[6:5]  - Type
 */
#define REQ_TYPE_STD_DEV               0x00
#define REQ_TYPE_CLASS_DEV             0x20
#define REQ_TYPE_VENDOR_DEV            0x40
/*
 *  bmRequestType[4:0]  - Recipient
 */
#define REQ_TYPE_TO_DEV                0x00
#define REQ_TYPE_TO_IFACE              0x01
#define REQ_TYPE_TO_EP                 0x02
#define REQ_TYPE_TO_OTHER              0x03
/*
 *  Standard Requests
 */
#define USB_REQ_GET_STATUS             0x00
#define USB_REQ_CLEAR_FEATURE          0x01
#define USB_REQ_SET_FEATURE            0x03
#define USB_REQ_SET_ADDRESS            0x05
#define USB_REQ_GET_DESCRIPTOR         0x06
#define USB_REQ_SET_CONFIGURATION      0x09
#define USB_REQ_SET_INTERFACE          0x0B
/*
 *  Descriptor Types
 */
#define USB_DT_STANDARD                0x00
#define USB_DT_CLASS                   0x20
#define USB_DT_VENDOR                  0x40

#define USB_DT_DEVICE                  0x01
#define USB_DT_CONFIGURATION           0x02
#define USB_DT_STRING                  0x03
#define USB_DT_INTERFACE               0x04
#define USB_DT_ENDPOINT                0x05
#define USB_DT_DEVICE_QUALIFIER        0x06
#define USB_DT_OTHER_SPEED_CONF        0x07
#define USB_DT_IFACE_POWER             0x08



/*----------------------------------------------------------------------------------*/
/*  USB standard descriptors                                                        */
/*----------------------------------------------------------------------------------*/

/* Descriptor header */
typedef struct __attribute__((__packed__))
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
}
DESC_HDR_T;

/*----------------------------------------------------------------------------------*/
/*  USB device descriptor                                                           */
/*----------------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__))  /*!< device descriptor structure        */
{
    uint8_t  bLength;                   /*!< Length of device descriptor            */
    uint8_t  bDescriptorType;           /*!< Device descriptor type                 */
    uint16_t bcdUSB;                    /*!< USB version number                     */
    uint8_t  bDeviceClass;              /*!< Device class code                      */
    uint8_t  bDeviceSubClass;           /*!< Device subclass code                   */
    uint8_t  bDeviceProtocol;           /*!< Device protocol code                   */
    uint8_t  bMaxPacketSize0;           /*!< Maximum packet size of control endpoint*/
    uint16_t idVendor;                  /*!< Vendor ID                              */
    uint16_t idProduct;                 /*!< Product ID                             */
    uint16_t bcdDevice;                 /*!< Device ID                              */
    uint8_t  iManufacturer;             /*!< Manufacture description string ID      */
    uint8_t  iProduct;                  /*!< Product description string ID          */
    uint8_t  iSerialNumber;             /*!< Serial number description string ID    */
    uint8_t  bNumConfigurations;        /*!< Total number of configurations         */
}
DESC_DEV_T;                           /*!< device descriptor structure            */

/*
 *  Configuration Descriptor
 */
typedef struct __attribute__((__packed__)) usb_config_descriptor    /*!< Configuration descriptor structure     */
{
    uint8_t   bLength;                  /*!< Length of configuration descriptor     */
    uint8_t   bDescriptorType;          /*!< Descriptor type                        */
    uint16_t  wTotalLength;             /*!< Total length of this configuration     */
    uint8_t   bNumInterfaces;           /*!< Total number of interfaces             */
    uint8_t   bConfigurationValue;      /*!< Configuration descriptor number        */
    uint8_t   iConfiguration;           /*!< String descriptor ID                   */
    uint8_t   bmAttributes;             /*!< Configuration characteristics          */
    uint8_t   MaxPower;                 /*!< Maximum power consumption              */
} DESC_CONF_T;                          /*!< Configuration descriptor structure     */

/*
 *  Interface Descriptor
 */
typedef struct  __attribute__((__packed__))usb_interface_descriptor   /*!< Interface descriptor structure       */
{
    uint8_t  bLength;                   /*!< Length of interface descriptor         */
    uint8_t  bDescriptorType;           /*!< Descriptor type                        */
    uint8_t  bInterfaceNumber;          /*!< Interface number                       */
    uint8_t  bAlternateSetting;         /*!< Alternate setting number               */
    uint8_t  bNumEndpoints;             /*!< Number of endpoints                    */
    uint8_t  bInterfaceClass;           /*!< Interface class code                   */
    uint8_t  bInterfaceSubClass;        /*!< Interface subclass code                */
    uint8_t  bInterfaceProtocol;        /*!< Interface protocol code                */
    uint8_t  iInterface;                /*!< Interface ID                           */
} DESC_IF_T;                            /*!< Interface descriptor structure         */

/*
 *  Endpoint Descriptor
 */
typedef struct __attribute__((__packed__)) usb_endpoint_descriptor   /*!< Endpoint descriptor structure         */
{
    uint8_t  bLength;                   /*!< Length of endpoint descriptor          */
    uint8_t  bDescriptorType;           /*!< Descriptor type                        */
    uint8_t  bEndpointAddress;          /*!< Endpoint address                       */
    uint8_t  bmAttributes;              /*!< Endpoint attribute                     */
    uint16_t wMaxPacketSize;            /*!< Maximum packet size                    */
    uint8_t  bInterval;                 /*!< Synchronous transfer interval          */
    uint8_t  bRefresh;                  /*!< Refresh                                */
    uint8_t  bSynchAddress;             /*!< Sync address                           */
} DESC_EP_T;                            /*!< Endpoint descriptor structure          */

/*
 *  Endpoint descriptor bEndpointAddress[7] - direction
 */
#define EP_ADDR_DIR_MASK               0x80
#define EP_ADDR_DIR_IN                 0x80
#define EP_ADDR_DIR_OUT                0x00

/*
 *  Endpoint descriptor bmAttributes[1:0] - transfer type
 */
#define EP_ATTR_TT_MASK                0x03
#define EP_ATTR_TT_CTRL                0x00
#define EP_ATTR_TT_ISO                 0x01
#define EP_ATTR_TT_BULK                0x02
#define EP_ATTR_TT_INT                 0x03


/*----------------------------------------------------------------------------------*/
/*  USB Host controller driver                                                      */
/*----------------------------------------------------------------------------------*/
typedef struct
{
    int (*init)(void);
    void (*shutdown)(void);
    void (*suspend)(void);
    void (*resume)(void);
    int (*ctrl_xfer)(struct utr_t *utr);
    int (*bulk_xfer)(struct utr_t *utr);
    int (*int_xfer)(struct utr_t *utr);
    int (*iso_xfer)(struct utr_t *utr);
    int (*quit_xfer)(struct utr_t *utr, struct ep_info_t *ep);

    /* root hub support */
    int (*rthub_port_reset)(int port);
    int (*rthub_polling)(void);
} HC_DRV_T;


/*----------------------------------------------------------------------------------*/
/*  USB device driver                                                               */
/*----------------------------------------------------------------------------------*/
typedef struct
{
    int (*probe)(struct iface_t *iface);
    void (*disconnect)(struct iface_t *iface);
    void (*suspend)(struct iface_t *iface);
    void (*resume)(struct iface_t *iface);
} UDEV_DRV_T;


/*----------------------------------------------------------------------------------*/
/*  USB device                                                                      */
/*----------------------------------------------------------------------------------*/

typedef enum
{
    SPEED_LOW,
    SPEED_FULL,
    SPEED_HIGH
} SPEED_E;

typedef struct ep_info_t
{
    uint8_t     bEndpointAddress;
    uint8_t     bmAttributes;
    uint8_t     bInterval;
    uint8_t     bToggle;
    uint16_t    wMaxPacketSize;
    void        *hw_pipe;               /*!< point to the HC assocaied endpoint    \hideinitializer */
}   EP_INFO_T;

typedef struct udev_t
{
    DESC_DEV_T    descriptor;           /*!< Device descriptor.                    \hideinitializer */
    struct hub_dev_t *parent;           /*!< parent hub device                     \hideinitializer */
    uint8_t       port_num;             /*!< The hub port this device connected on \hideinitializer */
    uint8_t       dev_num;              /*!< device number                         \hideinitializer */
    int8_t        cur_conf;             /*!< Currentll selected configuration      \hideinitializer */
    SPEED_E       speed;                /*!< device speed (low/full/high)          \hideinitializer */
    /*
     *  The followings are lightweight USB stack internal used .
    */
    uint8_t       *cfd_buff;            /*!< Configuration descriptor buffer.      \hideinitializer */
    EP_INFO_T     ep0;                  /*!< Endpoint 0                            \hideinitializer */
    HC_DRV_T      *hc_driver;           /*!< host controller driver                \hideinitializer */
    struct iface_t  *iface_list;        /*!< Working interface list                \hideinitializer */
    struct udev_t *next;                /*!< link for global usb device list       \hideinitializer */
} UDEV_T;

typedef struct alt_iface_t
{
    DESC_IF_T     *ifd;                 /*!< point to the location of this alternative interface descriptor in UDEV_T->cfd_buff */
    EP_INFO_T     ep[MAX_EP_PER_IFACE]; /*!< endpoints of this alternative interface                */
} ALT_IFACE_T;

typedef struct iface_t
{
    UDEV_T        *udev;                /*!< USB device                            \hideinitializer */
    uint8_t       if_num;               /*!< Interface number                      \hideinitializer */
    uint8_t       num_alt;              /*!< Number of alternative interface       \hideinitializer */
    ALT_IFACE_T   *aif;                 /*!< Point to the active alternative interface              */
    ALT_IFACE_T   alt[MAX_ALT_PER_IFACE];  /*!< List of alternative interface      \hideinitializer */
    UDEV_DRV_T    *driver;              /*!< Interface associated driver           \hideinitializer */
    void          *context;             /*!< Reference to device context           \hideinitializer */
    struct iface_t  *next;              /*!< Point to next interface of the same device. Started from UDEV_T->iface_list   \hideinitializer */
} IFACE_T;


/*----------------------------------------------------------------------------------*/
/*  URB (USB Request Block)                                                         */
/*----------------------------------------------------------------------------------*/

#define IF_PER_UTR             8      /* number of frames per UTR isochronous transfer (DO NOT modify it!)  */

typedef void (*FUNC_UTR_T)(struct utr_t *);

typedef struct utr_t
{
    UDEV_T      *udev;                /*!< point to associated USB device        \hideinitializer */
    DEV_REQ_T   setup;                /*!< buffer for setup packet               \hideinitializer */
    EP_INFO_T   *ep;                  /*!< associated endpoint                   \hideinitializer */
    uint8_t     *buff;                /*!< transfer buffer                       \hideinitializer */
    uint8_t     bIsTransferDone;      /*!< tansfer done?                         \hideinitializer */
    uint32_t    data_len;             /*!< length of data to be transferred      \hideinitializer */
    uint32_t    xfer_len;             /*!< length of transferred data            \hideinitializer */
    uint8_t     bIsoNewSched;         /*!< New schedule isochronous transfer     \hideinitializer */
    uint16_t    iso_sf;               /*!< Isochronous start frame number        \hideinitializer */
    uint16_t    iso_xlen[IF_PER_UTR]; /*!< transfer length of isochronous frames \hideinitializer */
    uint8_t    *iso_buff[IF_PER_UTR]; /*!< transfer buffer address of isochronous frames \hideinitializer */
    int         iso_status[IF_PER_UTR]; /*!< transfer status of isochronous frames \hideinitializer */
    int         td_cnt;               /*!< number of transfer descriptors        \hideinitializer */
    int         status;               /*!< return status                         \hideinitializer */
    int         interval;             /*!< interrupt/isochronous interval        \hideinitializer */
    void        *context;             /*!< point to deivce proprietary data area \hideinitializer */
    FUNC_UTR_T  func;                 /*!< tansfer done call-back function       \hideinitializer */
    struct utr_t  *next;              /* point to the next UTR of the same endpoint. \hideinitializer */
} UTR_T;


/*----------------------------------------------------------------------------------*/
/*  Global variables                                                                */
/*----------------------------------------------------------------------------------*/
extern USBH_T      *_ohci;
extern HSUSBH_T    *_ehci;

extern HC_DRV_T    ohci_driver;
extern HC_DRV_T    ehci_driver;

extern UDEV_T *g_udev_list;

extern volatile int _IsInUsbInterrupt;

/*----------------------------------------------------------------------------------*/
/*  USB stack exported functions                                                    */
/*----------------------------------------------------------------------------------*/
extern void usbh_delay_ms(int msec);

extern void dump_ohci_regs(void);
extern void dump_ohci_ports(void);
extern void dump_ohci_int_table(void);
extern void dump_ehci_regs(void);
extern void dump_ehci_qtd(qTD_T *qtd);
extern void dump_ehci_asynclist(void);
extern void dump_ehci_period_frame_list_simple(void);
extern void usbh_dump_buff_bytes(uint8_t *buff, int nSize);
extern void usbh_dump_interface_descriptor(DESC_IF_T *if_desc);
extern void usbh_dump_endpoint_descriptor(DESC_EP_T *ep_desc);
extern void usbh_dump_iface(IFACE_T *iface);
extern void usbh_dump_ep_info(EP_INFO_T *ep);

/*
 *  Memory management functions
 */
extern void USB_InitializeMemoryPool(void);
extern void *USB_malloc(int wanted_size, int boundary);
extern void USB_free(void *);
extern int  USB_available_memory(void);
extern int  USB_allocated_memory(void);
extern void usbh_memory_init(void);
extern uint32_t  usbh_memory_used(void);
extern void *usbh_alloc_mem(int size);
extern void usbh_free_mem(void *p, int size);
extern int  alloc_dev_address(void);
extern void free_dev_address(int dev_addr);
extern UDEV_T *alloc_device(void);
extern void free_device(UDEV_T *udev);
extern UTR_T *alloc_utr(UDEV_T *udev);
extern void free_utr(UTR_T *utr);
extern ED_T *alloc_ohci_ED(void);
extern void free_ohci_ED(ED_T *ed);
extern TD_T *alloc_ohci_TD(UTR_T *utr);
extern void free_ohci_TD(TD_T *td);
extern QH_T *alloc_ehci_QH(void);
extern void free_ehci_QH(QH_T *qh);
extern qTD_T *alloc_ehci_qTD(UTR_T *utr);
extern void free_ehci_qTD(qTD_T *qtd);
extern iTD_T *alloc_ehci_iTD(void);
extern void free_ehci_iTD(iTD_T *itd);
extern siTD_T *alloc_ehci_siTD(void);
extern void free_ehci_siTD(siTD_T *sitd);


extern void usbh_hub_init(void);
extern int  usbh_connect_device(UDEV_T *);
extern void usbh_disconnect_device(UDEV_T *);
extern int  usbh_register_driver(UDEV_DRV_T *driver);
extern EP_INFO_T *usbh_iface_find_ep(IFACE_T *iface, uint8_t ep_addr, uint8_t dir_type);
extern int  usbh_reset_device(UDEV_T *);
extern int usbh_reset_port(UDEV_T *);

/*
 *  USB Standard Request functions
 */
extern int usbh_get_device_descriptor(UDEV_T *udev, DESC_DEV_T *desc_buff);
extern int usbh_get_config_descriptor(UDEV_T *udev, uint8_t *desc_buff, int buff_len);
extern int usbh_set_configuration(UDEV_T *udev, uint8_t conf_val);
extern int usbh_set_interface(IFACE_T *iface, uint16_t alt_setting);
extern int usbh_clear_halt(UDEV_T *udev, uint16_t ep_addr);

extern int usbh_ctrl_xfer(UDEV_T *udev, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint16_t wLength, uint8_t *buff, uint32_t *xfer_len, uint32_t timeout);
extern int usbh_bulk_xfer(UTR_T *utr);
extern int usbh_int_xfer(UTR_T *utr);
extern int usbh_iso_xfer(UTR_T *utr);
extern int usbh_quit_utr(UTR_T *utr);
extern int usbh_quit_xfer(UDEV_T *udev, EP_INFO_T *ep);


/// @endcond HIDDEN_SYMBOLS

#endif  /* _USBH_H_ */
