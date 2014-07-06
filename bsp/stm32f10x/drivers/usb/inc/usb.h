//usb.h
#include "usb_lib.h"
#ifndef			__USB_H__
#define			__USB_H__
void rt_hw_usb_init(void);
void Get_SerialNum(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Cable_Config (FunctionalState NewState);
void USB_Connect (bool con);
#endif
