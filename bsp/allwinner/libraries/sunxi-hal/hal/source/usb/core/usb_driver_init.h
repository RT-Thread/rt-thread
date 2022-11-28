#ifndef __USB_DEVICE_DRIVER_H__
#define __USB_DEVICE_DRIVER_H__
#ifdef  CONFIG_USB_STORAGE
#include "usb_msc.h"
#endif
#ifdef  CONFIG_USB_HID
#include "Hid.h"
#endif
#ifdef  CONFIG_USB_CAMERA
#include "UVC.h"
#endif

int usb_drivers_init(void);
int usb_drivers_exit(void);
#endif

