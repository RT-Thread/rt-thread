//usb.h
#ifndef					__USB_H__
#define					__USB_H__
#include <rthw.h>
#include <rtthread.h>
#include "serial.h"
#define					USB_BUFFER_SIZE		64	
struct stm32_usb_buffer
{
	rt_uint8_t  usb_buffer[USB_BUFFER_SIZE];
	rt_uint32_t read_index, save_index;
};

struct stm32_usb_device
{
	void*	usbdata;
	struct 	stm32_usb_buffer* usb_rx;
};

extern rt_sem_t  usb_sem;
rt_err_t rt_hw_usbhid_register(rt_device_t device, const char* name, rt_uint32_t flag, struct stm32_serial_device *serial);
void rt_hw_usb_init(void);
#endif