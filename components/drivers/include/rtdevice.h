#ifndef __RT_DEVICE_H__
#define __RT_DEVICE_H__

#include <rtthread.h>

#define RT_DEVICE(device)	((rt_device_t)device)

#ifdef RT_USING_SPI
#include "drivers/spi.h"
#endif

#ifdef RT_USING_MTD
#include "drivers/mtd.h"
#endif

#ifdef RT_USING_USB_DEVICE
#include "drivers/usb_device.h"
#endif

#ifdef RT_USING_USB_HOST
#include "drivers/usb_host.h"
#endif

#endif
