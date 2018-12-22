/*!
    \file  usb_defines.h
    \brief USB core defines
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef USB_DEFINES_H
#define USB_DEFINES_H

#include  "usb_conf.h"

#ifndef NULL
    #define NULL                                (void *)0   /*!< USB null marco value*/
#endif /* NULL */

#define USB_CORE_SPEED_HIGH                     0U    /* USB core speed is high-speed */
#define USB_CORE_SPEED_FULL                     1U    /* USB core speed is full-speed */

#define USBFS_MAX_PACKET_SIZE                   64U   /* USBFS max packet size */
#define USBFS_MAX_HOST_CHANNELCOUNT             8U    /* USBFS host channel count */
#define USBFS_MAX_DEV_EPCOUNT                   4U    /* USBFS device endpoint count */
#define USBFS_MAX_FIFO_WORDLEN                  320U  /* USBFS max fifo size in words */

#define USBHS_MAX_PACKET_SIZE                   512U  /* USBHS max packet size */
#define USBHS_MAX_HOST_CHANNELCOUNT             12U   /* USBHS host channel count */
#define USBHS_MAX_DEV_EPCOUNT                   6U    /* USBHS device endpoint count */
#define USBHS_MAX_FIFO_WORDLEN                  1280U /* USBHS max fifo size in words */

#define USB_CORE_ULPI_PHY                       1U    /* USB core use external ULPI PHY */
#define USB_CORE_EMBEDDED_PHY                   2U    /* USB core use embedded PHY */

#define DSTAT_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ     0U    /* USB enumerate speed use high-speed PHY clock in 30MHz or 60MHz */
#define DSTAT_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ     1U    /* USB enumerate speed use full-speed PHY clock in 30MHz or 60MHz */
#define DSTAT_ENUMSPD_LS_PHY_6MHZ               2U    /* USB enumerate speed use low-speed PHY clock in 6MHz */
#define DSTAT_ENUMSPD_FS_PHY_48MHZ              3U    /* USB enumerate speed use full-speed PHY clock in 48MHz */

#define GRSTATR_RPCKST_IN                       2U    /* IN data packet received */
#define GRSTATR_RPCKST_IN_XFER_COMP             3U    /* IN transfer completed (generates an interrupt if poped) */
#define GRSTATR_RPCKST_DATA_TOGGLE_ERR          5U    /* Data toggle error (generates an interrupt if poped) */
#define GRSTATR_RPCKST_CH_HALTED                7U    /* Channel halted (generates an interrupt if poped) */

#define DEVICE_MODE                             0U    /* USB core in device mode */
#define HOST_MODE                               1U    /* USB core in host mode */
#define OTG_MODE                                2U    /* USB core in OTG mode */

#define USB_EPTYPE_CTRL                         0U    /* USB control endpoint type */
#define USB_EPTYPE_ISOC                         1U    /* USB synchronous endpoint type */
#define USB_EPTYPE_BULK                         2U    /* USB bulk endpoint type */
#define USB_EPTYPE_INTR                         3U    /* USB interrupt endpoint type */
#define USB_EPTYPE_MASK                         3U    /* USB endpoint type mask */

#define RXSTAT_GOUT_NAK                         1U    /* global OUT NAK (triggers an interrupt) */
#define RXSTAT_DATA_UPDT                        2U    /* OUT data packet received */
#define RXSTAT_XFER_COMP                        3U    /* OUT transfer completed (triggers an interrupt) */
#define RXSTAT_SETUP_COMP                       4U    /* SETUP transaction completed (triggers an interrupt) */
#define RXSTAT_SETUP_UPDT                       6U    /* SETUP data packet received */

#define DPID_DATA0                              0U    /* device endpoint data PID is DATA0 */
#define DPID_DATA1                              2U    /* device endpoint data PID is DATA1 */
#define DPID_DATA2                              1U    /* device endpoint data PID is DATA2 */
#define DPID_MDATA                              3U    /* device endpoint data PID is MDATA */

#define HC_PID_DATA0                            0U    /* host channel data PID is DATA0 */
#define HC_PID_DATA2                            1U    /* host channel data PID is DATA2 */
#define HC_PID_DATA1                            2U    /* host channel data PID is DATA1 */
#define HC_PID_SETUP                            3U    /* host channel data PID is SETUP */

#define HPRT_PRTSPD_HIGH_SPEED                  0U    /* host port speed use high speed */
#define HPRT_PRTSPD_FULL_SPEED                  1U    /* host port speed use full speed */
#define HPRT_PRTSPD_LOW_SPEED                   2U    /* host port speed use low speed */

#define HCTLR_30_60_MHZ                         0U    /* USB PHY(ULPI) clock is 60MHz */
#define HCTLR_48_MHZ                            1U    /* USB PHY(embedded full-speed) clock is 48MHz */
#define HCTLR_6_MHZ                             2U    /* USB PHY(embedded low-speed) clock is 6MHz */

#define HCCHAR_CTRL                             0U    /* control channel type */
#define HCCHAR_ISOC                             1U    /* synchronous channel type */
#define HCCHAR_BULK                             2U    /* bulk channel type */
#define HCCHAR_INTR                             3U    /* interrupt channel type */

typedef enum
{
    USB_HS_CORE_ID = 0,
    USB_FS_CORE_ID = 1
}usb_core_id_enum;

typedef enum
{
    USB_SPEED_UNKNOWN = 0,
    USB_SPEED_LOW,
    USB_SPEED_FULL,
    USB_SPEED_HIGH
}usb_speed_enum;

#endif /* USB_DEFINES_H */
