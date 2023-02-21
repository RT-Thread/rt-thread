#ifndef __USBH_HID_KEYBD_H__
#define __USBH_HID_KEYBD_H__

#include <stdint.h>


extern USBH_HID_cb_t USBH_HID_KeyBD_cb;


void USBH_HID_KeyBD_Init(void);
void USBH_HID_KeyBd_Decode(uint8_t *pbuf);


#endif // __USBH_HID_KEYBD_H__
