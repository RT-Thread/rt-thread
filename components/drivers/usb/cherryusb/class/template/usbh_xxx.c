#include "usbh_core.h"
#include "usbh_xxx.h"

#define DEV_FORMAT "/dev/xxx"

#define CONFIG_USBHOST_MAX_CUSTOM_CLASS 1
static struct usbh_xxx g_xxx_class[CONFIG_USBHOST_MAX_CUSTOM_CLASS];
static uint32_t g_devinuse = 0;

static struct usbh_xxx *usbh_xxx_class_alloc(void)
{
    uint8_t devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_CUSTOM_CLASS; devno++) {
        if ((g_devinuse & (1U << devno)) == 0) {
            g_devinuse |= (1U << devno);
            memset(&g_xxx_class[devno], 0, sizeof(struct usbh_xxx));
            g_xxx_class[devno].minor = devno;
            return &g_xxx_class[devno];
        }
    }
    return NULL;
}

static void usbh_xxx_class_free(struct usbh_xxx *xxx_class)
{
    uint8_t devno = xxx_class->minor;

    if (devno < 32) {
        g_devinuse &= ~(1U << devno);
    }
    memset(xxx_class, 0, sizeof(struct usbh_xxx));
}

static int usbh_xxx_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret;

    struct usbh_xxx *xxx_class = usbh_xxx_class_alloc();
    if (xxx_class == NULL) {
        USB_LOG_ERR("Fail to alloc xxx_class\r\n");
        return -USB_ERR_NOMEM;
    }

    return ret;
}


static int usbh_xxx_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_xxx *xxx_class = (struct usbh_xxx *)hport->config.intf[intf].priv;

    if (xxx_class) {
        if (xxx_class->xxxin) {
            usbh_kill_urb(&xxx_class->xxxin_urb);
        }

        if (xxx_class->xxxout) {
            usbh_kill_urb(&xxx_class->xxxout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister xxx Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_xxx_stop(xxx_class);
        }

        usbh_xxx_class_free(xxx_class);
    }

    return ret;
}

__WEAK void usbh_xxx_run(struct usbh_xxx *xxx_class)
{
}

__WEAK void usbh_xxx_stop(struct usbh_xxx *xxx_class)
{
}

static const struct usbh_class_driver xxx_class_driver = {
    .driver_name = "xxx",
    .connect = usbh_xxx_connect,
    .disconnect = usbh_xxx_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info xxx_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .class = 0,
    .subclass = 0,
    .protocol = 0,
    .id_table = NULL,
    .class_driver = &xxx_class_driver
};
