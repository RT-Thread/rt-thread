#ifndef _USBD_XXX_H_
#define _USBD_XXX_H_

#include "usb_xxx.h"

#ifdef __cplusplus
extern "C" {
#endif

struct usbd_interface *usbd_xxx_init_intf(uint8_t busid, struct usbd_interface *intf);

#ifdef __cplusplus
}
#endif

#endif /* _USBD_XXX_H_ */
