#ifndef __USBH_HID_KEYBD_H__
#define __USBH_HID_KEYBD_H__

#include <stdint.h>


#define KBD_LEFT_CTRL       0x01
#define KBD_LEFT_SHIFT      0x02
#define KBD_LEFT_ALT        0x04
#define KBD_LEFT_CMD        0x08
#define KBD_RIGHT_CTRL      0x10
#define KBD_RIGHT_SHIFT     0x20
#define KBD_RIGHT_ALT       0x40
#define KBD_RIGHT_CMD       0x80


extern USBH_HID_cb_t USBH_HID_KeyBD_cb;


void USBH_HID_KeyBD_Init(void);
void USBH_HID_KeyBD_Decode(uint8_t *pbuf);

__attribute__((weak))
void USBH_HID_KeyBD_Handle(uint8_t ctrl, char key);


#endif // __USBH_HID_KEYBD_H__
