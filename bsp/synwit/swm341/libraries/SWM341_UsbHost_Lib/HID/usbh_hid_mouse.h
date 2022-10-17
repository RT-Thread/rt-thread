#ifndef __USBH_HID_MOUSE_H__
#define __USBH_HID_MOUSE_H__

#include <stdint.h>


typedef struct {
    uint8_t button; // bit0 左键  bit1 右键   bit2 中键
    uint8_t x;
    uint8_t y;
    uint8_t z;      // Not Supported
} USBH_HID_Mouse_Data_t;

extern USBH_HID_Mouse_Data_t USBH_HID_Mouse_Data;


extern USBH_HID_cb_t USBH_HID_Mouse_cb;


void USBH_HID_Mouse_Init(void);
void USBH_HID_Mouse_Decode(uint8_t *data);


#endif // __USBH_HID_MOUSE_H__
