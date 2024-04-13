/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_msc.h"
#include "usb_scsi.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_msc"
#include "usb_log.h"

#define DEV_FORMAT "/dev/sd%c"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_msc_buf[64];

static struct usbh_msc g_msc_class[CONFIG_USBHOST_MAX_MSC_CLASS];
static uint32_t g_devinuse = 0;
static struct usbh_msc_modeswitch_config *g_msc_modeswitch_config = NULL;

static struct usbh_msc *usbh_msc_class_alloc(void)
{
    int devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_MSC_CLASS; devno++) {
        if ((g_devinuse & (1 << devno)) == 0) {
            g_devinuse |= (1 << devno);
            memset(&g_msc_class[devno], 0, sizeof(struct usbh_msc));
            g_msc_class[devno].sdchar = 'a' + devno;
            return &g_msc_class[devno];
        }
    }
    return NULL;
}

static void usbh_msc_class_free(struct usbh_msc *msc_class)
{
    int devno = msc_class->sdchar - 'a';

    if (devno >= 0 && devno < 32) {
        g_devinuse &= ~(1 << devno);
    }
    memset(msc_class, 0, sizeof(struct usbh_msc));
}

static int usbh_msc_get_maxlun(struct usbh_msc *msc_class, uint8_t *buffer)
{
    struct usb_setup_packet *setup = msc_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = MSC_REQUEST_GET_MAX_LUN;
    setup->wValue = 0;
    setup->wIndex = msc_class->intf;
    setup->wLength = 1;

    return usbh_control_transfer(msc_class->hport, setup, buffer);
}

static void usbh_msc_cbw_dump(struct CBW *cbw)
{
    int i;

    USB_LOG_DBG("CBW:\r\n");
    USB_LOG_DBG("  signature: 0x%08x\r\n", (unsigned int)cbw->dSignature);
    USB_LOG_DBG("  tag:       0x%08x\r\n", (unsigned int)cbw->dTag);
    USB_LOG_DBG("  datlen:    0x%08x\r\n", (unsigned int)cbw->dDataLength);
    USB_LOG_DBG("  flags:     0x%02x\r\n", cbw->bmFlags);
    USB_LOG_DBG("  lun:       0x%02x\r\n", cbw->bLUN);
    USB_LOG_DBG("  cblen:    0x%02x\r\n", cbw->bCBLength);

    USB_LOG_DBG("CB:\r\n");
    for (i = 0; i < cbw->bCBLength; i += 8) {
        USB_LOG_DBG("  0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\r\n",
                    cbw->CB[i], cbw->CB[i + 1], cbw->CB[i + 2],
                    cbw->CB[i + 3], cbw->CB[i + 4], cbw->CB[i + 5],
                    cbw->CB[i + 6], cbw->CB[i + 7]);
    }
}

static void usbh_msc_csw_dump(struct CSW *csw)
{
    USB_LOG_DBG("CSW:\r\n");
    USB_LOG_DBG("  signature: 0x%08x\r\n", (unsigned int)csw->dSignature);
    USB_LOG_DBG("  tag:       0x%08x\r\n", (unsigned int)csw->dTag);
    USB_LOG_DBG("  residue:   0x%08x\r\n", (unsigned int)csw->dDataResidue);
    USB_LOG_DBG("  status:    0x%02x\r\n", csw->bStatus);
}

static inline int usbh_msc_bulk_in_transfer(struct usbh_msc *msc_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &msc_class->bulkin_urb;

    usbh_bulk_urb_fill(urb, msc_class->hport, msc_class->bulkin, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

static inline int usbh_msc_bulk_out_transfer(struct usbh_msc *msc_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &msc_class->bulkout_urb;

    usbh_bulk_urb_fill(urb, msc_class->hport, msc_class->bulkout, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

static int usbh_bulk_cbw_csw_xfer(struct usbh_msc *msc_class, struct CBW *cbw, struct CSW *csw, uint8_t *buffer)
{
    int nbytes;

    usbh_msc_cbw_dump(cbw);

    /* Send the CBW */
    nbytes = usbh_msc_bulk_out_transfer(msc_class, (uint8_t *)cbw, USB_SIZEOF_MSC_CBW, CONFIG_USBHOST_MSC_TIMEOUT);
    if (nbytes < 0) {
        USB_LOG_ERR("cbw transfer error\r\n");
        goto __err_exit;
    }

    if (cbw->dDataLength != 0) {
        if (cbw->CB[0] == SCSI_CMD_WRITE10) {
            nbytes = usbh_msc_bulk_out_transfer(msc_class, buffer, cbw->dDataLength, CONFIG_USBHOST_MSC_TIMEOUT);
        } else if (cbw->CB[0] == SCSI_CMD_READCAPACITY10) {
            nbytes = usbh_msc_bulk_in_transfer(msc_class, buffer, cbw->dDataLength, CONFIG_USBHOST_MSC_TIMEOUT);
            if (nbytes >= 0) {
                /* Save the capacity information */
                msc_class->blocknum = GET_BE32(&buffer[0]) + 1;
                msc_class->blocksize = GET_BE32(&buffer[4]);
            }
        } else {
            nbytes = usbh_msc_bulk_in_transfer(msc_class, buffer, cbw->dDataLength, CONFIG_USBHOST_MSC_TIMEOUT);
        }

        if (nbytes < 0) {
            USB_LOG_ERR("msc data transfer error\r\n");
            goto __err_exit;
        }
    }

    /* Receive the CSW */
    memset(csw, 0, USB_SIZEOF_MSC_CSW);
    nbytes = usbh_msc_bulk_in_transfer(msc_class, (uint8_t *)csw, USB_SIZEOF_MSC_CSW, CONFIG_USBHOST_MSC_TIMEOUT);
    if (nbytes < 0) {
        USB_LOG_ERR("csw transfer error\r\n");
        goto __err_exit;
    }

    usbh_msc_csw_dump(csw);

    /* check csw status */
    if (csw->dSignature != MSC_CSW_Signature) {
        USB_LOG_ERR("csw signature error\r\n");
        return -USB_ERR_INVAL;
    }

    if (csw->bStatus != 0) {
        USB_LOG_ERR("csw bStatus %d\r\n", csw->bStatus);
        return -USB_ERR_INVAL;
    }
__err_exit:
    return nbytes < 0 ? (int)nbytes : 0;
}

static inline int usbh_msc_scsi_testunitready(struct usbh_msc *msc_class)
{
    struct CBW *cbw;

    /* Construct the CBW */
    cbw = (struct CBW *)g_msc_buf;
    memset(cbw, 0, USB_SIZEOF_MSC_CBW);
    cbw->dSignature = MSC_CBW_Signature;

    cbw->bCBLength = SCSICMD_TESTUNITREADY_SIZEOF;
    cbw->CB[0] = SCSI_CMD_TESTUNITREADY;

    return usbh_bulk_cbw_csw_xfer(msc_class, cbw, (struct CSW *)g_msc_buf, NULL);
}

static inline int usbh_msc_scsi_requestsense(struct usbh_msc *msc_class)
{
    struct CBW *cbw;

    /* Construct the CBW */
    cbw = (struct CBW *)g_msc_buf;
    memset(cbw, 0, USB_SIZEOF_MSC_CBW);
    cbw->dSignature = MSC_CBW_Signature;

    cbw->bmFlags = 0x80;
    cbw->dDataLength = SCSIRESP_FIXEDSENSEDATA_SIZEOF;
    cbw->bCBLength = SCSICMD_REQUESTSENSE_SIZEOF;
    cbw->CB[0] = SCSI_CMD_REQUESTSENSE;
    cbw->CB[4] = SCSIRESP_FIXEDSENSEDATA_SIZEOF;

    return usbh_bulk_cbw_csw_xfer(msc_class, cbw, (struct CSW *)g_msc_buf, g_msc_buf);
}

static inline int usbh_msc_scsi_inquiry(struct usbh_msc *msc_class)
{
    struct CBW *cbw;

    /* Construct the CBW */
    cbw = (struct CBW *)g_msc_buf;
    memset(cbw, 0, USB_SIZEOF_MSC_CBW);
    cbw->dSignature = MSC_CBW_Signature;

    cbw->dDataLength = SCSIRESP_INQUIRY_SIZEOF;
    cbw->bmFlags = 0x80;
    cbw->bCBLength = SCSICMD_INQUIRY_SIZEOF;
    cbw->CB[0] = SCSI_CMD_INQUIRY;
    cbw->CB[4] = SCSIRESP_INQUIRY_SIZEOF;

    return usbh_bulk_cbw_csw_xfer(msc_class, cbw, (struct CSW *)g_msc_buf, g_msc_buf);
}

static inline int usbh_msc_scsi_readcapacity10(struct usbh_msc *msc_class)
{
    struct CBW *cbw;

    /* Construct the CBW */
    cbw = (struct CBW *)g_msc_buf;
    memset(cbw, 0, USB_SIZEOF_MSC_CBW);
    cbw->dSignature = MSC_CBW_Signature;

    cbw->dDataLength = SCSIRESP_READCAPACITY10_SIZEOF;
    cbw->bmFlags = 0x80;
    cbw->bCBLength = SCSICMD_READCAPACITY10_SIZEOF;
    cbw->CB[0] = SCSI_CMD_READCAPACITY10;

    return usbh_bulk_cbw_csw_xfer(msc_class, cbw, (struct CSW *)g_msc_buf, g_msc_buf);
}

static inline void usbh_msc_modeswitch(struct usbh_msc *msc_class, const uint8_t *message)
{
    struct CBW *cbw;

    /* Construct the CBW */
    cbw = (struct CBW *)g_msc_buf;

    memcpy(g_msc_buf, message, 31);

    usbh_bulk_cbw_csw_xfer(msc_class, cbw, (struct CSW *)g_msc_buf, NULL);
}

static int usbh_msc_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret;
    struct usbh_msc_modeswitch_config *config;

    struct usbh_msc *msc_class = usbh_msc_class_alloc();
    if (msc_class == NULL) {
        USB_LOG_ERR("Fail to alloc msc_class\r\n");
        return -USB_ERR_NOMEM;
    }

    msc_class->hport = hport;
    msc_class->intf = intf;

    hport->config.intf[intf].priv = msc_class;

    ret = usbh_msc_get_maxlun(msc_class, g_msc_buf);
    if (ret < 0) {
        return ret;
    }

    USB_LOG_INFO("Get max LUN:%u\r\n", g_msc_buf[0] + 1);

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;
        if (ep_desc->bEndpointAddress & 0x80) {
            USBH_EP_INIT(msc_class->bulkin, ep_desc);
        } else {
            USBH_EP_INIT(msc_class->bulkout, ep_desc);
        }
    }

    if (g_msc_modeswitch_config) {
        uint8_t num = 0;
        while (1) {
            config = &g_msc_modeswitch_config[num];
            if (config && config->name) {
                if ((hport->device_desc.idVendor == config->vid) &&
                    (hport->device_desc.idProduct == config->pid)) {
                    USB_LOG_INFO("%s usb_modeswitch enable\r\n", config->name);
                    usbh_msc_modeswitch(msc_class, config->message_content);
                    return 0;
                }
                num++;
            } else {
                break;
            }
        }
    }

    ret = usbh_msc_scsi_testunitready(msc_class);
    if (ret < 0) {
        ret = usbh_msc_scsi_requestsense(msc_class);
        if (ret < 0) {
            USB_LOG_ERR("Fail to scsi_testunitready\r\n");
            return ret;
        }
    }

    ret = usbh_msc_scsi_inquiry(msc_class);
    if (ret < 0) {
        USB_LOG_ERR("Fail to scsi_inquiry\r\n");
        return ret;
    }
    ret = usbh_msc_scsi_readcapacity10(msc_class);
    if (ret < 0) {
        USB_LOG_ERR("Fail to scsi_readcapacity10\r\n");
        return ret;
    }

    if (msc_class->blocksize > 0) {
        USB_LOG_INFO("Capacity info:\r\n");
        USB_LOG_INFO("Block num:%d,block size:%d\r\n", (unsigned int)msc_class->blocknum, (unsigned int)msc_class->blocksize);
    } else {
        USB_LOG_ERR("Invalid block size\r\n");
        return -USB_ERR_RANGE;
    }

    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, msc_class->sdchar);

    USB_LOG_INFO("Register MSC Class:%s\r\n", hport->config.intf[intf].devname);

    usbh_msc_run(msc_class);
    return ret;
}

static int usbh_msc_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_msc *msc_class = (struct usbh_msc *)hport->config.intf[intf].priv;

    if (msc_class) {
        if (msc_class->bulkin) {
            usbh_kill_urb(&msc_class->bulkin_urb);
        }

        if (msc_class->bulkout) {
            usbh_kill_urb(&msc_class->bulkout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister MSC Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_msc_stop(msc_class);
        }

        usbh_msc_class_free(msc_class);
    }

    return ret;
}


int usbh_msc_scsi_write10(struct usbh_msc *msc_class, uint32_t start_sector, const uint8_t *buffer, uint32_t nsectors)
{
    struct CBW *cbw;

    /* Construct the CBW */
    cbw = (struct CBW *)g_msc_buf;
    memset(cbw, 0, USB_SIZEOF_MSC_CBW);
    cbw->dSignature = MSC_CBW_Signature;

    cbw->dDataLength = (msc_class->blocksize * nsectors);
    cbw->bCBLength = SCSICMD_WRITE10_SIZEOF;
    cbw->CB[0] = SCSI_CMD_WRITE10;

    SET_BE32(&cbw->CB[2], start_sector);
    SET_BE16(&cbw->CB[7], nsectors);

    return usbh_bulk_cbw_csw_xfer(msc_class, cbw, (struct CSW *)g_msc_buf, (uint8_t *)buffer);
}

int usbh_msc_scsi_read10(struct usbh_msc *msc_class, uint32_t start_sector, const uint8_t *buffer, uint32_t nsectors)
{
    struct CBW *cbw;

    /* Construct the CBW */
    cbw = (struct CBW *)g_msc_buf;
    memset(cbw, 0, USB_SIZEOF_MSC_CBW);
    cbw->dSignature = MSC_CBW_Signature;

    cbw->dDataLength = (msc_class->blocksize * nsectors);
    cbw->bmFlags = 0x80;
    cbw->bCBLength = SCSICMD_READ10_SIZEOF;
    cbw->CB[0] = SCSI_CMD_READ10;

    SET_BE32(&cbw->CB[2], start_sector);
    SET_BE16(&cbw->CB[7], nsectors);

    return usbh_bulk_cbw_csw_xfer(msc_class, cbw, (struct CSW *)g_msc_buf, (uint8_t *)buffer);
}

void usbh_msc_modeswitch_enable(struct usbh_msc_modeswitch_config *config)
{
    if (config) {
        g_msc_modeswitch_config = config;
    } else {
        g_msc_modeswitch_config = NULL;
    }
}

__WEAK void usbh_msc_run(struct usbh_msc *msc_class)
{
}

__WEAK void usbh_msc_stop(struct usbh_msc *msc_class)
{
}

const struct usbh_class_driver msc_class_driver = {
    .driver_name = "msc",
    .connect = usbh_msc_connect,
    .disconnect = usbh_msc_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info msc_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .class = USB_DEVICE_CLASS_MASS_STORAGE,
    .subclass = MSC_SUBCLASS_SCSI,
    .protocol = MSC_PROTOCOL_BULK_ONLY,
    .id_table = NULL,
    .class_driver = &msc_class_driver
};
