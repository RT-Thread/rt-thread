#ifndef __RT_DEVICE_H__
#define __RT_DEVICE_H__

#include <rtthread.h>

#define RT_DEVICE(device)	((rt_device_t)device)

/* completion flag */
struct rt_completion
{
	rt_uint32_t flag;

	/* suspended list */
	rt_list_t suspended_list;
};

/* ring buffer */
struct rt_ringbuffer
{
	rt_uint16_t read_index, write_index;
	rt_uint8_t *buffer_ptr;
	rt_uint16_t buffer_size;
};

/**
 * Completion
 */
void rt_completion_init(struct rt_completion* completion);
rt_err_t rt_completion_wait(struct rt_completion* completion, rt_int32_t timeout);
void rt_completion_done(struct rt_completion* completion);

/**
 * DataLink for DeviceDriver
 */

/**
 * RingBuffer for DeviceDriver
 */
void rt_ringbuffer_init(struct rt_ringbuffer* rb, rt_uint8_t *pool, rt_uint16_t size);
rt_size_t rt_ringbuffer_put(struct rt_ringbuffer* rb, const rt_uint8_t *ptr, rt_uint16_t length);
rt_size_t rt_ringbuffer_putchar(struct rt_ringbuffer* rb, const rt_uint8_t ch);
rt_size_t rt_ringbuffer_get(struct rt_ringbuffer* rb, rt_uint8_t *ptr, rt_uint16_t length);
rt_size_t rt_ringbuffer_available_size(struct rt_ringbuffer* rb);
rt_size_t rt_ringbuffer_emptry_size(struct rt_ringbuffer* rb);

#ifdef RT_USING_SPI
#include "drivers/spi.h"
#endif

#ifdef RT_USING_MTD
#include "drivers/mtd.h"
#endif

#ifdef RT_USING_MTD_NAND
#include "drivers/mtd_nand.h"
#endif

#ifdef RT_USING_USB_DEVICE
#include "drivers/usb_device.h"
#endif

#ifdef RT_USING_USB_HOST
#include "drivers/usb_host.h"
#endif

#endif
