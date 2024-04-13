/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_ASIX_H
#define USBH_ASIX_H

#include "lwip/netif.h"
#include "lwip/pbuf.h"

/* ASIX AX8817X based USB 2.0 Ethernet Devices */

#define AX_CMD_SET_SW_MII         0x06
#define AX_CMD_READ_MII_REG       0x07
#define AX_CMD_WRITE_MII_REG      0x08
#define AX_CMD_STATMNGSTS_REG     0x09
#define AX_CMD_SET_HW_MII         0x0a
#define AX_CMD_READ_EEPROM        0x0b
#define AX_CMD_WRITE_EEPROM       0x0c
#define AX_CMD_WRITE_ENABLE       0x0d
#define AX_CMD_WRITE_DISABLE      0x0e
#define AX_CMD_READ_RX_CTL        0x0f
#define AX_CMD_WRITE_RX_CTL       0x10
#define AX_CMD_READ_IPG012        0x11
#define AX_CMD_WRITE_IPG0         0x12
#define AX_CMD_WRITE_IPG1         0x13
#define AX_CMD_READ_NODE_ID       0x13
#define AX_CMD_WRITE_NODE_ID      0x14
#define AX_CMD_WRITE_IPG2         0x14
#define AX_CMD_WRITE_MULTI_FILTER 0x16
#define AX88172_CMD_READ_NODE_ID  0x17
#define AX_CMD_READ_PHY_ID        0x19
#define AX_CMD_READ_MEDIUM_STATUS 0x1a
#define AX_CMD_WRITE_MEDIUM_MODE  0x1b
#define AX_CMD_READ_MONITOR_MODE  0x1c
#define AX_CMD_WRITE_MONITOR_MODE 0x1d
#define AX_CMD_READ_GPIOS         0x1e
#define AX_CMD_WRITE_GPIOS        0x1f
#define AX_CMD_SW_RESET           0x20
#define AX_CMD_SW_PHY_STATUS      0x21
#define AX_CMD_SW_PHY_SELECT      0x22
#define AX_QCTCTRL                0x2A

#define AX_CHIPCODE_MASK          0x70
#define AX_AX88772_CHIPCODE       0x00
#define AX_AX88772A_CHIPCODE      0x10
#define AX_AX88772B_CHIPCODE      0x20
#define AX_HOST_EN                0x01

#define AX_PHYSEL_PSEL            0x01
#define AX_PHYSEL_SSMII           0
#define AX_PHYSEL_SSEN            0x10

#define AX_PHY_SELECT_MASK        (BIT(3) | BIT(2))
#define AX_PHY_SELECT_INTERNAL    0
#define AX_PHY_SELECT_EXTERNAL    BIT(2)

#define AX_MONITOR_MODE           0x01
#define AX_MONITOR_LINK           0x02
#define AX_MONITOR_MAGIC          0x04
#define AX_MONITOR_HSFS           0x10

/* AX88172 Medium Status Register values */
#define AX88172_MEDIUM_FD         0x02
#define AX88172_MEDIUM_TX         0x04
#define AX88172_MEDIUM_FC         0x10
#define AX88172_MEDIUM_DEFAULT \
    (AX88172_MEDIUM_FD | AX88172_MEDIUM_TX | AX88172_MEDIUM_FC)

#define AX_MCAST_FILTER_SIZE 8
#define AX_MAX_MCAST         64

#define AX_SWRESET_CLEAR     0x00
#define AX_SWRESET_RR        0x01
#define AX_SWRESET_RT        0x02
#define AX_SWRESET_PRTE      0x04
#define AX_SWRESET_PRL       0x08
#define AX_SWRESET_BZ        0x10
#define AX_SWRESET_IPRL      0x20
#define AX_SWRESET_IPPD      0x40

#define AX88772_IPG0_DEFAULT 0x15
#define AX88772_IPG1_DEFAULT 0x0c
#define AX88772_IPG2_DEFAULT 0x12

/* AX88772 & AX88178 Medium Mode Register */
#define AX_MEDIUM_PF         0x0080
#define AX_MEDIUM_JFE        0x0040
#define AX_MEDIUM_TFC        0x0020
#define AX_MEDIUM_RFC        0x0010
#define AX_MEDIUM_ENCK       0x0008
#define AX_MEDIUM_AC         0x0004
#define AX_MEDIUM_FD         0x0002
#define AX_MEDIUM_GM         0x0001
#define AX_MEDIUM_SM         0x1000
#define AX_MEDIUM_SBP        0x0800
#define AX_MEDIUM_PS         0x0200
#define AX_MEDIUM_RE         0x0100

#define AX88178_MEDIUM_DEFAULT                       \
    (AX_MEDIUM_PS | AX_MEDIUM_FD | AX_MEDIUM_AC |    \
     AX_MEDIUM_RFC | AX_MEDIUM_TFC | AX_MEDIUM_JFE | \
     AX_MEDIUM_RE)

#define AX88772_MEDIUM_DEFAULT     \
    (AX_MEDIUM_FD | AX_MEDIUM_PS | \
     AX_MEDIUM_AC | AX_MEDIUM_RE)

/* AX88772 & AX88178 RX_CTL values */
#define AX_RX_CTL_SO        0x0080
#define AX_RX_CTL_AP        0x0020
#define AX_RX_CTL_AM        0x0010
#define AX_RX_CTL_AB        0x0008
#define AX_RX_CTL_SEP       0x0004
#define AX_RX_CTL_AMALL     0x0002
#define AX_RX_CTL_PRO       0x0001
#define AX_RX_CTL_MFB_2048  0x0000
#define AX_RX_CTL_MFB_4096  0x0100
#define AX_RX_CTL_MFB_8192  0x0200
#define AX_RX_CTL_MFB_16384 0x0300

#define AX_DEFAULT_RX_CTL   (AX_RX_CTL_SO | AX_RX_CTL_AB)

/* GPIO 0 .. 2 toggles */
#define AX_GPIO_GPO0EN      0x01 /* GPIO0 Output enable */
#define AX_GPIO_GPO_0       0x02 /* GPIO0 Output value */
#define AX_GPIO_GPO1EN      0x04 /* GPIO1 Output enable */
#define AX_GPIO_GPO_1       0x08 /* GPIO1 Output value */
#define AX_GPIO_GPO2EN      0x10 /* GPIO2 Output enable */
#define AX_GPIO_GPO_2       0x20 /* GPIO2 Output value */
#define AX_GPIO_RESERVED    0x40 /* Reserved */
#define AX_GPIO_RSE         0x80 /* Reload serial EEPROM */

#define AX_EEPROM_MAGIC     0xdeadbeef
#define AX_EEPROM_LEN       0x200

#define AX_EMBD_PHY_ADDR    0x10

struct usbh_asix {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *bulkin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *bulkout; /* Bulk OUT endpoint */
    struct usb_endpoint_descriptor *intin;   /* INTR IN endpoint  */
    struct usbh_urb bulkout_urb;
    struct usbh_urb bulkin_urb;
    struct usbh_urb intin_urb;

    uint8_t intf;
    char *name;
    uint8_t phy_addr;
    uint8_t embd_phy;
    uint8_t chipcode;
    uint16_t mac_capabilities;

    bool connect_status;
    uint8_t mac[6];

    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gateway;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_asix_get_connect_status(struct usbh_asix *asix_class);

void usbh_asix_run(struct usbh_asix *asix_class);
void usbh_asix_stop(struct usbh_asix *asix_class);

void usbh_asix_rx_thread(void *argument);
err_t usbh_asix_linkoutput(struct netif *netif, struct pbuf *p);

#ifdef __cplusplus
}
#endif

#endif /* USBH_ASIX_H */