#ifndef __USB_HW_SCAN_H__
#define __USB_HW_SCAN_H__
#include "sunxi_usb_board.h"

#define  USB_SCAN_INSMOD_DEVICE_DRIVER_DELAY    2
#define  USB_SCAN_INSMOD_HOST_DRIVER_DELAY  1
typedef enum usb_id_state
{
    USB_HOST_MODE = 0,
    USB_DEVICE_MODE = 1,
} usb_id_state_t;

/* usb detect vbus */
typedef enum usb_det_vbus_state
{
    USB_DET_VBUS_INVALID = 0,
    USB_DET_VBUS_VALID  = 1
} usb_det_vbus_state_t;

typedef struct usb_scan_info
{
    usb_id_state_t id_old_state;        /* last id state */
    usb_det_vbus_state_t det_vbus_old_state;    /* last vbus state */
    unsigned int device_insmod_delay;   /* debounce time */
    unsigned int host_insmod_delay; /* debounce time */
    usb_cfg_t *cfg;
} usb_scan_info_t;
int usb_hw_scan_init(usb_cfg_t *cfg);
void usb_hw_scan(usb_cfg_t *cfg);
#endif
