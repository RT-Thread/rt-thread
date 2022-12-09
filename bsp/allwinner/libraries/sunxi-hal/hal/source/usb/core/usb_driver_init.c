#include "usb_driver_init.h"
int usb_drivers_init(void) {
#ifdef  CONFIG_USB_STORAGE
    mscInit();
#endif
#ifdef  CONFIG_USB_HID
    HidInit();
#endif
#ifdef  CONFIG_USB_CAMERA
    UVCInit();
#endif
    return 0;
}
int usb_drivers_exit(void) {
#ifdef  CONFIG_USB_STORAGE
    mscExit();
#endif
#ifdef  CONFIG_USB_HID
    HidExit();
#endif
#ifdef  CONFIG_USB_CAMERA
    UVCExit();
#endif
    return 0;
}

