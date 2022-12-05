#ifndef _USB_URB_H_
#define _USB_URB_H_
#include "usb_host_common.h"

void _debug_print_urb(struct urb *urb_input);

void usb_init_urb(struct urb *urb);
struct urb *usb_alloc_urb(int iso_packets);
void usb_free_urb(struct urb *urb);
int usb_submit_urb(struct urb *urb, unsigned mem_flags);
int usb_unlink_urb(struct urb *urb);
void usb_kill_urb(struct urb *urb);

#endif
