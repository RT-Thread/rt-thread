// #include <sunxi_drv_gpio.h>
#include <stddef.h>
#include <typedef.h>
#include <hal_gpio.h>

#include "usb_hw_scan.h"
#include "usb_msg_center.h"
#include "usb_manager_common.h"

#undef  x_set_bit
#define x_set_bit(value, bit)           ((value) |= (1U << (bit)))

/* clear bit */
#undef  x_clear_bit
#define x_clear_bit(value, bit)         ((value) &= ~(1U << (bit)))

static int device_insmod_delay;
static struct usb_scan_info g_usb_scan_info;
static void (*__usb_hw_scan)(struct usb_scan_info *);
extern int thread_suspend_flag;
static unsigned int PIODataIn_debounce(usb_gpio_t *usb_gpio, gpio_data_t *value)
{
    unsigned int retry  = 0;
    unsigned int time   = 10;
    unsigned int temp1  = 0;
    unsigned int cnt    = 0;
    unsigned int change = 0;    /* if have shake */

    /**
     * try 10 times, if value is the same,
     * then current read is valid; otherwise invalid.
     */
    if (usb_gpio->valid) {
        retry = time;
        while (retry--) {
            hal_gpio_get_data(usb_gpio->gpio_set.gpio, (gpio_data_t *)&temp1);
            if (temp1) {
                cnt++;
            }
        }

        /* 10 times, the value is all 0 or 1 */
        if ((cnt == time) || (cnt == 0)) {
            change = 0;
        } else {
            change = 1;
        }
    } else {
        change = 1;
    }

    if (!change) {
        *value = temp1;
    }
    Usb_Manager_Debug("usb_gpio->valid = %x, cnt = %x, change= %d, temp1 = %x\n", usb_gpio->valid, cnt, change, temp1);
    return change;
}

static u32 get_id_state(struct usb_scan_info *info)
{
    enum usb_id_state id_state = USB_DEVICE_MODE;
    gpio_data_t pin_data = 0;

    if (!PIODataIn_debounce((usb_gpio_t *)&info->cfg->port.id, &pin_data))
    {
        Usb_Manager_Debug("%s pin_data:%d\n", KEY_USB_ID_GPIO, pin_data);
        if (pin_data)
        {
            id_state = USB_DEVICE_MODE;
        }
        else
        {
            id_state = USB_HOST_MODE;
        }
        info->id_old_state = id_state;
    }
    else
    {
        id_state = info->id_old_state;
    }
    Usb_Manager_Debug("%s id_state:%d\n", KEY_USB_ID_GPIO, id_state);
    Usb_Manager_Debug("%s id_old_state:%d\n", KEY_USB_ID_GPIO, info->id_old_state);
    return id_state;
}
static u32 get_detect_vbus_state(struct usb_scan_info *info)
{
    enum usb_det_vbus_state det_vbus_state = USB_DET_VBUS_INVALID;
    gpio_data_t pin_data = 0;

    if (!PIODataIn_debounce((usb_gpio_t *)&info->cfg->port.det_vbus, &pin_data))
    {
        Usb_Manager_Debug("%s pin_data:%d\n", KEY_USB_DETVBUS_GPIO, pin_data);
        if (pin_data)
        {
            det_vbus_state = USB_DET_VBUS_VALID;
        }
        else
        {
            det_vbus_state = USB_DET_VBUS_INVALID;
        }

        info->det_vbus_old_state = det_vbus_state;
    }
    else
    {
        det_vbus_state = info->det_vbus_old_state;
    }
    Usb_Manager_Debug("%s id_state:%d\n", KEY_USB_DETVBUS_GPIO, det_vbus_state);
    Usb_Manager_Debug("%s id_old_state:%d\n", KEY_USB_DETVBUS_GPIO, info->det_vbus_old_state);
    return det_vbus_state;
}
static u32 get_dp_dm_status(struct usb_scan_info *info)
{
    u32 ret  = 0;
    //  u32 ret0 = 0;
    //  u32 ret1 = 0;
    //  u32 ret2 = 0;

    //  ret0 = get_dp_dm_status_normal();
    //  ret1 = get_dp_dm_status_normal();
    //  ret2 = get_dp_dm_status_normal();

    //  /* continuous 3 times, to avoid the voltage sudden changes */
    //  if ((ret0 == ret1) && (ret0 == ret2)) {
    //      ret = ret0;
    //  } else if (ret2 == 0x11) {
    //      if (get_usb_role() == USB_ROLE_DEVICE) {
    //          ret = 0x11;
    //          DMSG_PANIC("ERR: dp/dm status is continuous(0x11)\n");
    //      }
    //  } else {
    //      ret = ret2;
    //  }

    return ret;
}
static void do_switch_to_null(struct usb_scan_info *info)
{
    enum usb_role role = USB_ROLE_NULL;

    role = get_usb_role();
    device_insmod_delay = 0;
    info->host_insmod_delay   = 0;

    Usb_Manager_Debug("role:%d\n", role);
    switch (role)
    {
        case USB_ROLE_NULL:
            /* nothing to do */
            break;
        case USB_ROLE_HOST:
            if (thread_suspend_flag)
                break;
            hw_rmmod_usb_host();
            break;
        case USB_ROLE_DEVICE:
            if (thread_suspend_flag)
                break;
            hw_rmmod_usb_device();
            break;
        default:
            Usb_Manager_Err("unknown usb role(%d)\n", role);
    }
}

static void do_switch_to_host(struct usb_scan_info *info)
{
    enum usb_role role = USB_ROLE_NULL;

    role = get_usb_role();
    device_insmod_delay = 0;

    Usb_Manager_Debug("role:%d\n", role);
    switch (role)
    {
        case USB_ROLE_NULL:
            if (info->cfg->port.detect_mode == USB_DETECT_MODE_THREAD)
            {
                if (thread_suspend_flag)
                    break;
                /* delay for vbus is stably */
                if (info->host_insmod_delay < USB_SCAN_INSMOD_HOST_DRIVER_DELAY)
                {
                    info->host_insmod_delay++;
                    break;
                }
                info->host_insmod_delay = 0;
            }
            hw_insmod_usb_host();
            break;
        case USB_ROLE_HOST:
            /* nothing to do */
            break;
        case USB_ROLE_DEVICE:
            if (info->cfg->port.detect_mode == USB_DETECT_MODE_THREAD)
            {
                if (thread_suspend_flag)
                    break;
            }
            hw_rmmod_usb_device();
            break;
        default:
            Usb_Manager_Err("unknown usb role(%d)\n", role);
    }
}

static void do_switch_to_device(struct usb_scan_info *info)
{
    enum usb_role role = USB_ROLE_NULL;

    role = get_usb_role();
    info->host_insmod_delay = 0;

    Usb_Manager_Debug("role:%d\n", role);
    switch (role)
    {
        case USB_ROLE_NULL:
            if (info->cfg->port.detect_mode == USB_DETECT_MODE_THREAD)
            {
                if (get_dp_dm_status(info) == 0x00)
                {
                    if (thread_suspend_flag)
                        break;
                    /* delay for vbus is stably */
                    if (device_insmod_delay < USB_SCAN_INSMOD_DEVICE_DRIVER_DELAY)
                    {
                        device_insmod_delay++;
                        break;
                    }
                    device_insmod_delay = 0;
                }
            }
            hw_insmod_usb_device();
            break;
        case USB_ROLE_HOST:
            if (info->cfg->port.detect_mode == USB_DETECT_MODE_THREAD)
            {
                if (thread_suspend_flag)
                    break;
                hw_rmmod_usb_host();
            }
            hw_rmmod_usb_host();
            break;
        case USB_ROLE_DEVICE:
            /* nothing to do */
            break;
        default:
            Usb_Manager_Err("unknown usb role(%d)\n", role);
    }
}

static unsigned int get_vbus_id_state(struct usb_scan_info *info)
{
    u32 state = 0;

    if (get_id_state(info) == USB_DEVICE_MODE)
    {
        x_set_bit(state, 0);
    }

    if (get_detect_vbus_state(info) == USB_DET_VBUS_VALID)
    {
        x_set_bit(state, 1);
    }

    return state;
}

static void vbus_id_hw_scan(struct usb_scan_info *info)
{
    unsigned int vbus_id_state = 0;

    vbus_id_state = get_vbus_id_state(info);
    switch (vbus_id_state)
    {
        case  0x00:
        case  0x02:
            do_switch_to_host(info);
            break;
        case  0x01:
//          do_switch_to_null(info);
//          break;
        case  0x03:
            do_switch_to_device(info);
            break;
        default:
            Usb_Manager_Err("vbus_id_hw_scan: ");
            Usb_Manager_Err("unknown vbus_id_state(0x%x)\n", vbus_id_state);
    }
}
static void null_hw_scan(struct usb_scan_info *info)
{
    Usb_Manager_Debug("null_hw_scan\n");
}
void usb_hw_scan(struct usb_cfg *cfg)
{
    __usb_hw_scan(&g_usb_scan_info);
}

int usb_hw_scan_init(usb_cfg_t *cfg)
{
    int ret = 0;
    struct usb_port_info *port_info = NULL;
    struct usb_scan_info *scan_info = &g_usb_scan_info;

    memset(scan_info, 0, sizeof(struct usb_scan_info));
    scan_info->cfg          = cfg;
    scan_info->id_old_state     = USB_DEVICE_MODE;
    scan_info->det_vbus_old_state   = USB_DET_VBUS_INVALID;

    device_insmod_delay = 0;
    port_info = (struct usb_port_info *)&cfg->port;
    Usb_Manager_Debug("port_info->port.port_type:%d\n", port_info->port_type);
    switch (port_info->port_type)
    {
        case USB_PORT_TYPE_DEVICE:
        case USB_PORT_TYPE_HOST:
            __usb_hw_scan = null_hw_scan;
            break;
        case USB_PORT_TYPE_OTG:
        {
            if (port_info->detect_type == USB_DETECT_TYPE_VBUS_ID)
            {
                Usb_Manager_Debug("set %s mul_sel:%d\n", KEY_USB_ID_GPIO, port_info->id.gpio_set.mul_sel);
                Usb_Manager_Debug("set %s drv_level:%d\n", KEY_USB_ID_GPIO, port_info->id.gpio_set.drv_level);
                Usb_Manager_Debug("set %s pull:%d\n", KEY_USB_ID_GPIO, port_info->id.gpio_set.pull);
                Usb_Manager_Debug("set %s data:%d\n", KEY_USB_ID_GPIO, port_info->id.gpio_set.data);
                hal_gpio_pinmux_set_function(port_info->id.gpio_set.gpio, port_info->id.gpio_set.mul_sel);
                hal_gpio_set_driving_level(port_info->id.gpio_set.gpio, port_info->id.gpio_set.drv_level);
                hal_gpio_set_pull(port_info->id.gpio_set.gpio, port_info->id.gpio_set.pull);
                hal_gpio_set_data(port_info->id.gpio_set.gpio, port_info->id.gpio_set.data);

                Usb_Manager_Debug("set %s mul_sel:%d\n", KEY_USB_DETVBUS_GPIO, port_info->det_vbus.gpio_set.mul_sel);
                Usb_Manager_Debug("set %s drv_level:%d\n", KEY_USB_DETVBUS_GPIO, port_info->det_vbus.gpio_set.drv_level);
                Usb_Manager_Debug("set %s pull:%d\n", KEY_USB_DETVBUS_GPIO, port_info->det_vbus.gpio_set.pull);
                Usb_Manager_Debug("set %s data:%d\n", KEY_USB_DETVBUS_GPIO, port_info->det_vbus.gpio_set.data);
                hal_gpio_pinmux_set_function(port_info->det_vbus.gpio_set.gpio, port_info->det_vbus.gpio_set.mul_sel);
                hal_gpio_set_driving_level(port_info->det_vbus.gpio_set.gpio, port_info->det_vbus.gpio_set.drv_level);
                hal_gpio_set_pull(port_info->det_vbus.gpio_set.gpio, port_info->det_vbus.gpio_set.pull);
                hal_gpio_set_data(port_info->id.gpio_set.gpio, port_info->det_vbus.gpio_set.data);

                Usb_Manager_Debug("set %s mul_sel:%d\n", KEY_USB_DRVVBUS_GPIO, port_info->drv_vbus.gpio_set.mul_sel);
                Usb_Manager_Debug("set %s drv_level:%d\n", KEY_USB_DRVVBUS_GPIO, port_info->drv_vbus.gpio_set.drv_level);
                Usb_Manager_Debug("set %s pull:%d\n", KEY_USB_DRVVBUS_GPIO, port_info->drv_vbus.gpio_set.pull);
                Usb_Manager_Debug("set %s data:%d\n", KEY_USB_DRVVBUS_GPIO, port_info->drv_vbus.gpio_set.data);
                hal_gpio_pinmux_set_function(port_info->drv_vbus.gpio_set.gpio, port_info->drv_vbus.gpio_set.mul_sel);
                hal_gpio_set_driving_level(port_info->drv_vbus.gpio_set.gpio, port_info->drv_vbus.gpio_set.drv_level);
                hal_gpio_set_pull(port_info->drv_vbus.gpio_set.gpio, port_info->drv_vbus.gpio_set.pull);
                hal_gpio_set_data(port_info->drv_vbus.gpio_set.gpio, port_info->drv_vbus.gpio_set.data);
            }
            else
            {
                Usb_Manager_Err("detect_type(%d) can't support\n", port_info->port_type);
            }
            __usb_hw_scan = vbus_id_hw_scan;
        }
        break;
        default:
            Usb_Manager_Err("unknown port_type(%d)\n", port_info->port_type);
            ret = -1;
            goto failed;
    }

    return 0;

failed:
    __usb_hw_scan = null_hw_scan;
    return ret;
}
