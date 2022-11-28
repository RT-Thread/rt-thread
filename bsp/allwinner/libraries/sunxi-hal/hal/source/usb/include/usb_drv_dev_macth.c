#include "usb_os_platform.h"

#include "usb_list.h"
#include "usb_gen_dev_mod.h"
#include "usb_host_common.h"




/**
 * usb_match_id - find first usb_device_id matching device or interface
 * @interface: the interface of interest
 * @id: array of usb_device_id structures, terminated by zero entry
 *
 * usb_match_id searches an array of usb_device_id's and returns
 * the first one matching the device or interface, or null.
 * This is used when binding (or rebinding) a driver to an interface.
 * Most USB device drivers will use this indirectly, through the usb core,
 * but some layered driver frameworks use it directly.
 * These device tables are exported with MODULE_DEVICE_TABLE, through
 * modutils and "modules.usbmap", to support the driver loading
 * functionality of USB hotplugging.
 *
 * What Matches:
 *
 * The "match_flags" element in a usb_device_id controls which
 * members are used.  If the corresponding bit is set, the
 * value in the device_id must match its corresponding member
 * in the device or interface descriptor, or else the device_id
 * does not match.
 *
 * "driver_info" is normally used only by device drivers,
 * but you can create a wildcard "matches anything" usb_device_id
 * as a driver's "modules.usbmap" entry if you provide an id with
 * only a nonzero "driver_info" field.  If you do this, the USB device
 * driver's probe() routine should use additional intelligence to
 * decide whether to bind to the specified interface.
 *
 * What Makes Good usb_device_id Tables:
 *
 * The match algorithm is very simple, so that intelligence in
 * driver selection must come from smart driver id records.
 * Unless you have good reasons to use another selection policy,
 * provide match elements only in related groups, and order match
 * specifiers from specific to general.  Use the macros provided
 * for that purpose if you can.
 *
 * The most specific match specifiers use device descriptor
 * data.  These are commonly used with product-specific matches;
 * the USB_DEVICE macro lets you provide vendor and product IDs,
 * and you can also match against ranges of product revisions.
 * These are widely used for devices with application or vendor
 * specific bDeviceClass values.
 *
 * Matches based on device class/subclass/protocol specifications
 * are slightly more general; use the USB_DEVICE_INFO macro, or
 * its siblings.  These are used with single-function devices
 * where bDeviceClass doesn't specify that each interface has
 * its own class.
 *
 * Matches based on interface class/subclass/protocol are the
 * most general; they let drivers bind to any interface on a
 * multiple-function device.  Use the USB_INTERFACE_INFO
 * macro, or its siblings, to match class-per-interface style
 * devices (as recorded in bDeviceClass).
 *
 * Within those groups, remember that not all combinations are
 * meaningful.  For example, don't give a product version range
 * without vendor and product IDs; or specify a protocol without
 * its associated class and subclass.
 */
const struct usb_drv_dev_match_table *usb_match_id(struct usb_interface *intf,
        const struct usb_drv_dev_match_table *id)
{
    struct usb_host_virt_interface *virt_intf = NULL;
    struct usb_host_virt_dev  *dev = NULL;

    /* proc_connectinfo in devio.c may call us with id == NULL. */
    if (id == NULL)
    {
        hal_log_err("ERR: usb_match_id: input error");
        return NULL;
    }

    virt_intf = intf->cur_altsetting;

    if (virt_intf == NULL)
    {
        hal_log_err("ERR: usb_match_id: virt_intf == NULL");
        return NULL;
    }

    dev = usb_mod_interface_to_usbdev(intf);

    if (dev == NULL)
    {
        hal_log_err("ERR: usb_match_id: dev == NULL");
        return NULL;
    }

    /* It is important to check that id->driver_info is nonzero,
       since an entry that is all zeroes except for a nonzero
       id->driver_info is the way to create an entry that
       indicates that the driver want to examine every
       device and interface. */
    for (; id->idVendor || id->bDeviceClass || id->bInterfaceClass ||
         id->driver_info; id++)
    {
        /*
                hal_log_info("usb match id, match_flags = %x, bInterfaceClass= (%x, %x)",
                           id->match_flags, id->bInterfaceClass,
                           virt_intf->desc.bInterfaceClass);
        */
        if ((id->match_flags & USB_DEVICE_ID_MATCH_VENDOR) &&
            id->idVendor != le16_to_cpu(dev->descriptor.idVendor))
        {
            continue;
        }

        if ((id->match_flags & USB_DEVICE_ID_MATCH_PRODUCT) &&
            id->idProduct != le16_to_cpu(dev->descriptor.idProduct))
        {
            continue;
        }

        /* No need to test id->bcdDevice_lo != 0, since 0 is never
           greater than any unsigned number. */
        if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_LO) &&
            (id->bcdDevice_lo > le16_to_cpu(dev->descriptor.bcdDevice)))
        {
            continue;
        }

        if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_HI) &&
            (id->bcdDevice_hi < le16_to_cpu(dev->descriptor.bcdDevice)))
        {
            continue;
        }

        if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_CLASS) &&
            (id->bDeviceClass != dev->descriptor.bDeviceClass))
        {
            continue;
        }

        if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_SUBCLASS) &&
            (id->bDeviceSubClass != dev->descriptor.bDeviceSubClass))
        {
            continue;
        }

        if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_PROTOCOL) &&
            (id->bDeviceProtocol != dev->descriptor.bDeviceProtocol))
        {
            continue;
        }

        if ((id->match_flags & USB_DEVICE_ID_MATCH_INT_CLASS) &&
            (id->bInterfaceClass != virt_intf->desc.bInterfaceClass))
        {
            continue;
        }

        if ((id->match_flags & USB_DEVICE_ID_MATCH_INT_SUBCLASS) &&
            (id->bInterfaceSubClass != virt_intf->desc.bInterfaceSubClass))
        {
            continue;
        }

        if ((id->match_flags & USB_DEVICE_ID_MATCH_INT_PROTOCOL) &&
            (id->bInterfaceProtocol != virt_intf->desc.bInterfaceProtocol))
        {
            continue;
        }

        hal_log_info("usb match id suceessfull");
        return id;
    }

    hal_log_info("usb match id failed, bDeviceClass = %x, bInterfaceClass = %x",
              dev->descriptor.bDeviceClass, virt_intf->desc.bInterfaceClass);
    return NULL;
}


