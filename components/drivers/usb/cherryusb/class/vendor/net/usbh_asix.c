/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_asix.h"
#include "usb_cdc.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "asix"
#include "usb_log.h"

#define DEV_FORMAT "/dev/asix"

static struct usbh_asix g_asix_class;

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_asix_rx_buffer[CONFIG_USBHOST_ASIX_ETH_MAX_TX_SIZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_asix_tx_buffer[CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_asix_inttx_buffer[16];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_asix_buf[32];

#define ETH_ALEN 6

#define PHY_MODE_MARVELL     0x0000
#define MII_MARVELL_LED_CTRL 0x0018
#define MII_MARVELL_STATUS   0x001b
#define MII_MARVELL_CTRL     0x0014

#define MARVELL_LED_MANUAL 0x0019

#define MARVELL_STATUS_HWCFG 0x0004

#define MARVELL_CTRL_TXDELAY 0x0002
#define MARVELL_CTRL_RXDELAY 0x0080

#define PHY_MODE_RTL8211CL 0x000C

#define AX88772A_PHY14H         0x14
#define AX88772A_PHY14H_DEFAULT 0x442C

#define AX88772A_PHY15H         0x15
#define AX88772A_PHY15H_DEFAULT 0x03C8

#define AX88772A_PHY16H         0x16
#define AX88772A_PHY16H_DEFAULT 0x4044

#define SPEED_100 0
#define SPEED_10  1

static int usbh_asix_read_cmd(struct usbh_asix *asix_class,
                              uint8_t cmd,
                              uint16_t value,
                              uint16_t index,
                              void *data,
                              uint16_t size)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!asix_class || !asix_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = asix_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = cmd;
    setup->wValue = value;
    setup->wIndex = index;
    setup->wLength = size;

    ret = usbh_control_transfer(asix_class->hport, setup, g_asix_buf);
    if (ret < 0) {
        return ret;
    }
    memcpy(data, g_asix_buf, ret - 8);

    return ret;
}

static int usbh_asix_write_cmd(struct usbh_asix *asix_class,
                               uint8_t cmd,
                               uint16_t value,
                               uint16_t index,
                               void *data,
                               uint16_t size)
{
    struct usb_setup_packet *setup;

    if (!asix_class || !asix_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = asix_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = cmd;
    setup->wValue = value;
    setup->wIndex = index;
    setup->wLength = size;

    memcpy(g_asix_buf, data, size);

    return usbh_control_transfer(asix_class->hport, setup, g_asix_buf);
}

static int usbh_asix_mdio_write(struct usbh_asix *asix_class, int phy_id, int loc, int val)
{
    uint8_t smsr;
    uint16_t res = (uint16_t)val;
    int ret;

    for (uint8_t i = 0; i < 10; i++) {
        ret = usbh_asix_write_cmd(asix_class, AX_CMD_SET_SW_MII, 0, 0, NULL, 0);
        if (ret < 0) {
            return ret;
        }
        usb_osal_msleep(1);
        ret = usbh_asix_read_cmd(asix_class, AX_CMD_STATMNGSTS_REG, 0, 0, &smsr, 1);
        if (ret < 0) {
            return ret;
        }

        if (smsr & AX_HOST_EN) {
            break;
        }
    }

    ret = usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_MII_REG, phy_id, loc, &res, 2);
    if (ret < 0) {
        return ret;
    }

    ret = usbh_asix_write_cmd(asix_class, AX_CMD_SET_HW_MII, 0, 0, NULL, 0);
    if (ret < 0) {
        return ret;
    }
    return 0;
}

static int usbh_asix_mdio_read(struct usbh_asix *asix_class, int phy_id, int loc)
{
    uint8_t smsr;
    uint16_t res;
    int ret;

    for (uint8_t i = 0; i < 10; i++) {
        ret = usbh_asix_write_cmd(asix_class, AX_CMD_SET_SW_MII, 0, 0, NULL, 0);
        if (ret < 0) {
            return ret;
        }
        usb_osal_msleep(1);
        ret = usbh_asix_read_cmd(asix_class, AX_CMD_STATMNGSTS_REG, 0, 0, &smsr, 1);
        if (ret < 0) {
            return ret;
        }

        if (smsr & AX_HOST_EN) {
            break;
        }
    }

    ret = usbh_asix_read_cmd(asix_class, AX_CMD_READ_MII_REG, phy_id, loc, &res, 2);
    if (ret < 0) {
        return ret;
    }

    ret = usbh_asix_write_cmd(asix_class, AX_CMD_SET_HW_MII, 0, 0, NULL, 0);
    if (ret < 0) {
        return ret;
    }
    return res;
}

static int usbh_asix_read_phy_addr(struct usbh_asix *asix_class, bool internal)
{
    int ret, offset;
    uint8_t buf[2];

    ret = usbh_asix_read_cmd(asix_class, AX_CMD_READ_PHY_ID, 0, 0, buf, 2);
    if (ret < 0) {
        return ret;
    }

    offset = (internal ? 1 : 0);
    ret = buf[offset];

    USB_LOG_INFO("%s PHY address 0x%x\r\n", internal ? "internal" : "external", ret);

    return ret;
}

static int usbh_asix_sw_reset(struct usbh_asix *asix_class, uint8_t flags)
{
    int ret;

    ret = usbh_asix_write_cmd(asix_class, AX_CMD_SW_RESET, flags, 0, NULL, 0);
    if (ret < 0)
        USB_LOG_ERR("Failed to send software reset: %d\r\n", ret);

    return ret;
}

static uint16_t usbh_asix_read_rx_ctl(struct usbh_asix *asix_class)
{
    uint16_t v;
    int ret = usbh_asix_read_cmd(asix_class, AX_CMD_READ_RX_CTL, 0, 0, &v, 2);
    if (ret < 0) {
        return ret;
    }
    return v;
}

static int usbh_asix_write_rx_ctl(struct usbh_asix *asix_class, uint16_t mode)
{
    int ret;

    USB_LOG_DBG("asix_write_rx_ctl() - mode = 0x%04x\r\n", mode);
    ret = usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_RX_CTL, mode, 0, NULL, 0);
    if (ret < 0)
        USB_LOG_ERR("Failed to write RX_CTL mode to 0x%04x: %02x\r\n",
                    mode, ret);

    return ret;
}

static uint16_t usbh_asix_read_medium_status(struct usbh_asix *asix_class)
{
    uint16_t v;
    int ret = usbh_asix_read_cmd(asix_class, AX_CMD_READ_MEDIUM_STATUS, 0, 0, &v, 2);

    if (ret < 0) {
        USB_LOG_ERR("Error reading Medium Status register: %02x\r\n",
                    ret);
        return ret; /* TODO: callers not checking for error ret */
    }

    return v;
}

static int usbh_asix_write_medium_mode(struct usbh_asix *asix_class, uint16_t mode)
{
    int ret;

    USB_LOG_DBG("asix_write_medium_mode() - mode = 0x%04x\r\n", mode);
    ret = usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_MEDIUM_MODE, mode, 0, NULL, 0);
    if (ret < 0)
        USB_LOG_ERR("Failed to write Medium Mode mode to 0x%04x: %02x\r\n",
                    mode, ret);

    return ret;
}

static int usbh_asix_write_gpio(struct usbh_asix *asix_class, uint16_t value, int sleep)
{
    int ret;

    USB_LOG_DBG("asix_write_gpio() - value = 0x%04x\r\n", value);
    ret = usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_GPIOS, value, 0, NULL, 0);
    if (ret < 0)
        USB_LOG_ERR("Failed to write GPIO value 0x%04x: %d\r\n",
                    value, ret);

    if (sleep)
        usb_osal_msleep(sleep);

    return ret;
}

/*
 * AX88772 & AX88178 have a 16-bit RX_CTL value
 */
static void usbh_asix_set_multicast(struct usbh_asix *asix_class)
{
    uint16_t rx_ctl = AX_DEFAULT_RX_CTL | AX_RX_CTL_AM;
#if CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE == 4096
    rx_ctl |= AX_RX_CTL_MFB_4096;
#elif CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE == 8192
    rx_ctl |= AX_RX_CTL_MFB_8192;
#elif CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE == 16384
    rx_ctl |= AX_RX_CTL_MFB_16384;
#else
    rx_ctl |= AX_RX_CTL_MFB_2048;
#endif
    const uint8_t multi_filter[] = { 0x00, 0x00, 0x20, 0x80, 0x00, 0x00, 0x00, 0x40 };

    usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_MULTI_FILTER, 0, 0, (uint8_t *)multi_filter, AX_MCAST_FILTER_SIZE);
    usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_RX_CTL, rx_ctl, 0, NULL, 0);
}

static int usbh_ax88772_hw_reset(struct usbh_asix *asix_class)
{
    uint16_t rx_ctl;
    int ret;

    ret = usbh_asix_write_gpio(asix_class, AX_GPIO_RSE | AX_GPIO_GPO_2 | AX_GPIO_GPO2EN, 5);
    if (ret < 0)
        goto out;

    ret = usbh_asix_write_cmd(asix_class, AX_CMD_SW_PHY_SELECT, asix_class->embd_phy,
                              0, NULL, 0);
    if (ret < 0) {
        USB_LOG_ERR("Select PHY #1 failed: %d\r\n", ret);
        goto out;
    }

    if (asix_class->embd_phy) {
        ret = usbh_asix_sw_reset(asix_class, AX_SWRESET_IPPD);
        if (ret < 0)
            goto out;

        usb_osal_msleep(10);

        ret = usbh_asix_sw_reset(asix_class, AX_SWRESET_CLEAR);
        if (ret < 0)
            goto out;

        usb_osal_msleep(60);

        ret = usbh_asix_sw_reset(asix_class, AX_SWRESET_IPRL | AX_SWRESET_PRL);
        if (ret < 0)
            goto out;
    } else {
        ret = usbh_asix_sw_reset(asix_class, AX_SWRESET_IPPD | AX_SWRESET_PRL);
        if (ret < 0)
            goto out;
    }

    usb_osal_msleep(150);

    ret = usbh_asix_write_rx_ctl(asix_class, AX_DEFAULT_RX_CTL);
    if (ret < 0)
        goto out;

    ret = usbh_asix_write_medium_mode(asix_class, AX88772_MEDIUM_DEFAULT);
    if (ret < 0)
        goto out;

    ret = usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_IPG0,
                              AX88772_IPG0_DEFAULT | AX88772_IPG1_DEFAULT,
                              AX88772_IPG2_DEFAULT, NULL, 0);
    if (ret < 0) {
        USB_LOG_ERR("Write IPG,IPG1,IPG2 failed: %d\r\n", ret);
        goto out;
    }

    /* Rewrite MAC address */
    ret = usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_NODE_ID, 0, 0, asix_class->mac, ETH_ALEN);
    if (ret < 0)
        goto out;

    /* Set RX_CTL to default values with 2k buffer, and enable cactus */
    ret = usbh_asix_write_rx_ctl(asix_class, AX_DEFAULT_RX_CTL);
    if (ret < 0)
        goto out;

    rx_ctl = usbh_asix_read_rx_ctl(asix_class);
    USB_LOG_INFO("RX_CTL is 0x%04x after all initializations\r\n",
                 rx_ctl);

    rx_ctl = usbh_asix_read_medium_status(asix_class);
    USB_LOG_INFO("Medium Status is 0x%04x after all initializations\r\n",
                 rx_ctl);

    return 0;

out:
    return ret;
}

static int usbh_ax88772a_hw_reset(struct usbh_asix *asix_class)
{
    uint16_t rx_ctl, phy14h, phy15h, phy16h;
    int ret;

    ret = usbh_asix_write_gpio(asix_class, AX_GPIO_RSE, 5);
    if (ret < 0)
        goto out;

    ret = usbh_asix_write_cmd(asix_class, AX_CMD_SW_PHY_SELECT, asix_class->embd_phy | AX_PHYSEL_SSEN, 0, NULL, 0);
    if (ret < 0) {
        USB_LOG_ERR("Select PHY #1 failed: %d\r\n", ret);
        goto out;
    }
    usb_osal_msleep(10);

    ret = usbh_asix_sw_reset(asix_class, AX_SWRESET_IPPD | AX_SWRESET_IPRL);
    if (ret < 0)
        goto out;

    usb_osal_msleep(10);

    ret = usbh_asix_sw_reset(asix_class, AX_SWRESET_IPRL);
    if (ret < 0)
        goto out;

    usb_osal_msleep(160);

    ret = usbh_asix_sw_reset(asix_class, AX_SWRESET_CLEAR);
    if (ret < 0)
        goto out;

    ret = usbh_asix_sw_reset(asix_class, AX_SWRESET_IPRL);
    if (ret < 0)
        goto out;

    usb_osal_msleep(200);

    if (asix_class->chipcode == AX_AX88772B_CHIPCODE) {
        ret = usbh_asix_write_cmd(asix_class, AX_QCTCTRL, 0x8000, 0x8001, NULL, 0);
        if (ret < 0) {
            USB_LOG_ERR("Write BQ setting failed: %d\r\n", ret);
            goto out;
        }
    } else if (asix_class->chipcode == AX_AX88772A_CHIPCODE) {
        /* Check if the PHY registers have default settings */
        phy14h = usbh_asix_mdio_read(asix_class, asix_class->phy_addr,
                                     AX88772A_PHY14H);
        phy15h = usbh_asix_mdio_read(asix_class, asix_class->phy_addr,
                                     AX88772A_PHY15H);
        phy16h = usbh_asix_mdio_read(asix_class, asix_class->phy_addr,
                                     AX88772A_PHY16H);

        USB_LOG_DBG("772a_hw_reset: MR20=0x%x MR21=0x%x MR22=0x%x\r\n",
                    phy14h, phy15h, phy16h);

        /* Restore PHY registers default setting if not */
        if (phy14h != AX88772A_PHY14H_DEFAULT)
            usbh_asix_mdio_write(asix_class, asix_class->phy_addr,
                                 AX88772A_PHY14H,
                                 AX88772A_PHY14H_DEFAULT);
        if (phy15h != AX88772A_PHY15H_DEFAULT)
            usbh_asix_mdio_write(asix_class, asix_class->phy_addr,
                                 AX88772A_PHY15H,
                                 AX88772A_PHY15H_DEFAULT);
        if (phy16h != AX88772A_PHY16H_DEFAULT)
            usbh_asix_mdio_write(asix_class, asix_class->phy_addr,
                                 AX88772A_PHY16H,
                                 AX88772A_PHY16H_DEFAULT);
    }

    ret = usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_IPG0,
                              AX88772_IPG0_DEFAULT | AX88772_IPG1_DEFAULT,
                              AX88772_IPG2_DEFAULT, NULL, 0);
    if (ret < 0) {
        USB_LOG_ERR("Write IPG,IPG1,IPG2 failed: %d\r\n", ret);
        goto out;
    }

    /* Rewrite MAC address */
    ret = usbh_asix_write_cmd(asix_class, AX_CMD_WRITE_NODE_ID, 0, 0, asix_class->mac, ETH_ALEN);
    if (ret < 0)
        goto out;

    /* Set RX_CTL to default values with 2k buffer, and enable cactus */
    ret = usbh_asix_write_rx_ctl(asix_class, AX_DEFAULT_RX_CTL);
    if (ret < 0)
        goto out;

    ret = usbh_asix_write_medium_mode(asix_class, AX88772_MEDIUM_DEFAULT);
    if (ret < 0)
        return ret;

    /* Set RX_CTL to default values with 2k buffer, and enable cactus */
    ret = usbh_asix_write_rx_ctl(asix_class, AX_DEFAULT_RX_CTL);
    if (ret < 0)
        goto out;

    rx_ctl = usbh_asix_read_rx_ctl(asix_class);
    USB_LOG_INFO("RX_CTL is 0x%04x after all initializations\r\n", rx_ctl);

    rx_ctl = usbh_asix_read_medium_status(asix_class);
    USB_LOG_INFO("Medium Status is 0x%04x after all initializations\r\n", rx_ctl);

    return 0;

out:
    return ret;
}

static void usbh_ax88772_mac_link_down(struct usbh_asix *asix_class)
{
    usbh_asix_write_medium_mode(asix_class, 0);
}

static void usbh_ax88772_mac_link_up(struct usbh_asix *asix_class, int speed, int duplex, bool tx_pause, bool rx_pause)
{
    uint16_t m = AX_MEDIUM_AC | AX_MEDIUM_RE;

    m |= duplex ? AX_MEDIUM_FD : 0;

    switch (speed) {
        case SPEED_100:
            m |= AX_MEDIUM_PS;
            break;
        case SPEED_10:
            break;
        default:
            return;
    }

    if (tx_pause)
        m |= AX_MEDIUM_TFC;

    if (rx_pause)
        m |= AX_MEDIUM_RFC;

    usbh_asix_write_medium_mode(asix_class, m);
}

static int usbh_asix_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret;

    struct usbh_asix *asix_class = &g_asix_class;

    memset(asix_class, 0, sizeof(struct usbh_asix));

    asix_class->hport = hport;
    asix_class->intf = intf;

    hport->config.intf[intf].priv = asix_class;

    if ((hport->device_desc.idVendor == 0x0b95) && (hport->device_desc.idProduct == 0x772b)) {
        asix_class->name = "ASIX AX88772B";
    } else if ((hport->device_desc.idVendor == 0x0b95) && (hport->device_desc.idProduct == 0x7720)) {
        asix_class->name = "ASIX AX88772";
    } else if ((hport->device_desc.idVendor == 0x0b95) && (hport->device_desc.idProduct == 0x1780)) {
        asix_class->name = "ASIX AX88178";
    }

    for (uint8_t i = 0; i < (ETH_ALEN >> 1); i++) {
        ret = usbh_asix_read_cmd(asix_class, AX_CMD_READ_EEPROM,
                                 0x04 + i, 0, &asix_class->mac[i * 2], 2);
        if (ret < 0) {
            return ret;
        }
    }

    USB_LOG_INFO("asix MAC address %02x:%02x:%02x:%02x:%02x:%02x\r\n",
                 asix_class->mac[0],
                 asix_class->mac[1],
                 asix_class->mac[2],
                 asix_class->mac[3],
                 asix_class->mac[4],
                 asix_class->mac[5]);

    ret = usbh_asix_read_phy_addr(asix_class, true);
    if (ret < 0) {
        USB_LOG_ERR("Failed to read phy addr: %d\r\n", ret);
        return ret;
    }
    asix_class->phy_addr = ret;
    asix_class->embd_phy = ((ret & 0x1f) == AX_EMBD_PHY_ADDR);

    ret = usbh_asix_read_cmd(asix_class, AX_CMD_STATMNGSTS_REG, 0, 0, &asix_class->chipcode, 1);
    if (ret < 0) {
        USB_LOG_ERR("Failed to read STATMNGSTS_REG: %d\r\n", ret);
        return ret;
    }

    asix_class->chipcode &= AX_CHIPCODE_MASK;
    USB_LOG_INFO("asix chipcode 0x%x\r\n", asix_class->chipcode);

    if (asix_class->chipcode == AX_AX88772_CHIPCODE) {
        usbh_ax88772_hw_reset(asix_class);
    } else {
        usbh_ax88772a_hw_reset(asix_class);
    }
    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;

        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(asix_class->intin, ep_desc);
            } else {
                return -USB_ERR_NOTSUPP;
            }
        } else {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(asix_class->bulkin, ep_desc);
            } else {
                USBH_EP_INIT(asix_class->bulkout, ep_desc);
            }
        }
    }

    if (asix_class->chipcode == AX_AX88772B_CHIPCODE) {
        usbh_asix_mdio_write(asix_class, asix_class->phy_addr, 0, 0);
        usbh_asix_mdio_read(asix_class, asix_class->phy_addr, 0);

        usbh_asix_mdio_write(asix_class, asix_class->phy_addr, 0, 0x8200);
        usbh_asix_mdio_read(asix_class, asix_class->phy_addr, 0);

        usbh_asix_mdio_write(asix_class, asix_class->phy_addr, 0, 0x3900);
        usbh_asix_mdio_read(asix_class, asix_class->phy_addr, 0);

        usbh_asix_mdio_write(asix_class, asix_class->phy_addr, 0, 0x3100);
        usbh_asix_mdio_read(asix_class, asix_class->phy_addr, 4);

        usbh_asix_mdio_write(asix_class, asix_class->phy_addr, 4, 0x01e1);
        usbh_asix_mdio_read(asix_class, asix_class->phy_addr, 1);

        usbh_asix_mdio_write(asix_class, asix_class->phy_addr, 0, 0x3300);
        usbh_asix_mdio_read(asix_class, asix_class->phy_addr, 0);
    }

    USB_LOG_INFO("Init %s done\r\n", asix_class->name);

    strncpy(hport->config.intf[intf].devname, DEV_FORMAT, CONFIG_USBHOST_DEV_NAMELEN);

    USB_LOG_INFO("Register ASIX Class:%s\r\n", hport->config.intf[intf].devname);
    usbh_asix_run(asix_class);
    return ret;
}

static int usbh_asix_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_asix *asix_class = (struct usbh_asix *)hport->config.intf[intf].priv;

    if (asix_class) {
        if (asix_class->bulkin) {
            usbh_kill_urb(&asix_class->bulkin_urb);
        }

        if (asix_class->bulkout) {
            usbh_kill_urb(&asix_class->bulkout_urb);
        }

        if (asix_class->intin) {
            usbh_kill_urb(&asix_class->intin_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister ASIX Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_asix_stop(asix_class);
        }

        memset(asix_class, 0, sizeof(struct usbh_asix));
    }

    return ret;
}

int usbh_asix_get_connect_status(struct usbh_asix *asix_class)
{
    int ret;

    usbh_int_urb_fill(&asix_class->intin_urb, asix_class->hport, asix_class->intin, g_asix_inttx_buffer, 8, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    ret = usbh_submit_urb(&asix_class->intin_urb);
    if (ret < 0) {
        return ret;
    }

    if (g_asix_inttx_buffer[1] == 0x00) {
        if (g_asix_inttx_buffer[2] & 0x01) {
            asix_class->connect_status = true;
            usbh_ax88772_mac_link_up(asix_class, SPEED_100, 1, 1, 1);
            usbh_asix_set_multicast(asix_class);
        } else {
            asix_class->connect_status = false;
            usbh_ax88772_mac_link_down(asix_class);
        }
    }
    return 0;
}

void usbh_asix_rx_thread(void *argument)
{
    uint32_t g_asix_rx_length;
    int ret;
    uint16_t len;
    uint16_t len_crc;
    uint32_t data_offset;
#if CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE <= (16 * 1024)
    uint32_t transfer_size = CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE;
#else
    uint32_t transfer_size = (16 * 1024);
#endif

    (void)argument;
    USB_LOG_INFO("Create asix rx thread\r\n");
    // clang-format off
find_class:
    // clang-format on
    g_asix_class.connect_status = false;
    if (usbh_find_class_instance("/dev/asix") == NULL) {
        goto delete;
    }

    while (g_asix_class.connect_status == false) {
        ret = usbh_asix_get_connect_status(&g_asix_class);
        if (ret < 0) {
            usb_osal_msleep(100);
            goto find_class;
        }
        usb_osal_msleep(128);
    }

    g_asix_rx_length = 0;
    while (1) {
        usbh_bulk_urb_fill(&g_asix_class.bulkin_urb, g_asix_class.hport, g_asix_class.bulkin, &g_asix_rx_buffer[g_asix_rx_length], transfer_size, USB_OSAL_WAITING_FOREVER, NULL, NULL);
        ret = usbh_submit_urb(&g_asix_class.bulkin_urb);
        if (ret < 0) {
            goto find_class;
        }

        g_asix_rx_length += g_asix_class.bulkin_urb.actual_length;

        /* A transfer is complete because last packet is a short packet.
         * Short packet is not zero, match g_asix_rx_length % USB_GET_MAXPACKETSIZE(g_asix_class.bulkin->wMaxPacketSize).
         * Short packet is zero, check if g_asix_class.bulkin_urb.actual_length < transfer_size, for example transfer is complete with size is 1024 < 2048.
        */
        if (g_asix_rx_length % USB_GET_MAXPACKETSIZE(g_asix_class.bulkin->wMaxPacketSize) ||
            (g_asix_class.bulkin_urb.actual_length < transfer_size)) {
            USB_LOG_DBG("rxlen:%d\r\n", g_asix_rx_length);

            data_offset = 0;
            while (g_asix_rx_length > 0) {
                len = ((uint16_t)g_asix_rx_buffer[data_offset + 0] | ((uint16_t)(g_asix_rx_buffer[data_offset + 1]) << 8)) & 0x7ff;
                len_crc = g_asix_rx_buffer[data_offset + 2] | ((uint16_t)(g_asix_rx_buffer[data_offset + 3]) << 8);

                if (len != (~len_crc & 0x7ff)) {
                    USB_LOG_ERR("rx header error\r\n");
                    g_asix_rx_length = 0;
                    continue;
                }

                uint8_t *buf = (uint8_t *)&g_asix_rx_buffer[data_offset + 4];
                usbh_asix_eth_input(buf, len);
                g_asix_rx_length -= (len + 4);
                data_offset += (len + 4);

                if (g_asix_rx_length < 4) {
                    g_asix_rx_length = 0;
                }
            }
        } else {
#if CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE <= (16 * 1024)
            if (g_asix_rx_length == CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE) {
#else
            if ((g_asix_rx_length + (16 * 1024)) > CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE) {
#endif
                USB_LOG_ERR("Rx packet is overflow, please reduce tcp window size or increase CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE\r\n");
                while (1) {
                }
            }
        }
    }
    // clang-format off
delete:
    USB_LOG_INFO("Delete asix rx thread\r\n");
    usb_osal_thread_delete(NULL);
    // clang-format on
}

uint8_t *usbh_asix_get_eth_txbuf(void)
{
    return &g_asix_tx_buffer[4];
}

int usbh_asix_eth_output(uint32_t buflen)
{
    uint16_t actual_len;

    if (g_asix_class.connect_status == false) {
        return -USB_ERR_NOTCONN;
    }

    g_asix_tx_buffer[0] = buflen & 0xff;
    g_asix_tx_buffer[1] = (buflen >> 8) & 0xff;
    g_asix_tx_buffer[2] = ~g_asix_tx_buffer[0];
    g_asix_tx_buffer[3] = ~g_asix_tx_buffer[1];

    if (!(buflen + 4) % USB_GET_MAXPACKETSIZE(g_asix_class.bulkout->wMaxPacketSize)) {
        USB_LOG_DBG("txlen:%d\r\n", buflen + 8);
        g_asix_tx_buffer[buflen + 4 + 0] = 0x00;
        g_asix_tx_buffer[buflen + 4 + 1] = 0x00;
        g_asix_tx_buffer[buflen + 4 + 2] = 0xff;
        g_asix_tx_buffer[buflen + 4 + 3] = 0xff;
        actual_len = buflen + 8;
    } else {
        USB_LOG_DBG("txlen:%d\r\n", buflen + 4);
        actual_len = buflen + 4;
    }

    usbh_bulk_urb_fill(&g_asix_class.bulkout_urb, g_asix_class.hport, g_asix_class.bulkout, g_asix_tx_buffer, actual_len, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    return usbh_submit_urb(&g_asix_class.bulkout_urb);
}

__WEAK void usbh_asix_run(struct usbh_asix *asix_class)
{
    (void)asix_class;
}

__WEAK void usbh_asix_stop(struct usbh_asix *asix_class)
{
    (void)asix_class;
}

static const uint16_t asix_id_table[][2] = {
    { 0x0B95, 0x772B },
    { 0x0B95, 0x7720 },
    { 0, 0 },
};

static const struct usbh_class_driver asix_class_driver = {
    .driver_name = "asix",
    .connect = usbh_asix_connect,
    .disconnect = usbh_asix_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info asix_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .class = 0xff,
    .subclass = 0x00,
    .protocol = 0x00,
    .id_table = asix_id_table,
    .class_driver = &asix_class_driver
};