#ifndef __SPI_H__
#define __SPI_H__

#include <rtthread.h>

#define RT_SPI_CPHA		(1<<0)                             /* bit[0]:CPHA */
#define RT_SPI_CPOL		(1<<1)                             /* bit[1]:CPOL */
#define RT_SPI_LSB		(0<<2)                             /* bit[2]: 0-LSB */
#define RT_SPI_MSB		(1<<2)                             /* bit[2]: 1-MSB */

#define RT_SPI_MODE_0		(0 | 0)					       /* CPOL = 0, CPHA = 0 */
#define RT_SPI_MODE_1		(0 | RT_SPI_CPHA)			   /* CPOL = 0, CPHA = 1 */
#define RT_SPI_MODE_2		(RT_SPI_CPOL | 0)			   /* CPOL = 1, CPHA = 0 */
#define RT_SPI_MODE_3		(RT_SPI_CPOL | RT_SPI_CPHA)	   /* CPOL = 1, CPHA = 1 */

#define RT_SPI_MODE_MASK    (RT_SPI_CPHA | RT_SPI_CPOL | RT_SPI_MSB)

/**
 * SPI message structure
 */
struct rt_spi_message
{
	const void* send_buf;
	void* recv_buf;
	rt_size_t length;

	unsigned cs_take:1;
	unsigned cs_release:1;
};

/**
 * SPI configuration structure
 */
struct rt_spi_configuration
{
	rt_uint8_t mode;
	rt_uint8_t data_width;
	rt_uint16_t reserved;

	rt_uint32_t max_hz;
};

struct rt_spi_ops;
struct rt_spi_bus
{
	struct rt_device parent;
	struct rt_spi_ops *ops;

	struct rt_mutex lock;
	struct rt_spi_device* owner;
};

/**
 * SPI operators
 */
struct rt_spi_ops
{
	rt_err_t (*configure)(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
	rt_uint32_t (*xfer)(struct rt_spi_device* device, struct rt_spi_message* message);
};

/**
 * SPI Virtual BUS, one device must connected to a virtual BUS
 */
struct rt_spi_device
{
	struct rt_device parent;
	struct rt_spi_bus *bus;

	struct rt_spi_configuration config;
};
#define SPI_DEVICE(dev)	((struct rt_spi_device*)(dev))

/* register a SPI bus */
rt_err_t rt_spi_bus_register(struct rt_spi_bus* bus, const char* name, struct rt_spi_ops* ops);
/* attach a device on SPI bus */
rt_err_t rt_spi_bus_attach_device(struct rt_spi_device* device, const char* name, const char* bus_name, void* user_data);
/* set configuration on SPI device */
rt_err_t rt_spi_configure(struct rt_spi_device* device, struct rt_spi_configuration* cfg);

/* send data then receive data from SPI devicew */
rt_err_t rt_spi_send_then_recv(struct rt_spi_device* device, const void *send_buf, rt_size_t send_length,
		void* recv_buf, rt_size_t recv_length);

rt_err_t rt_spi_send_then_send(struct rt_spi_device* device, const void *send_buf1, rt_size_t send_length1,
		const void* send_buf2, rt_size_t send_length2);

rt_size_t rt_spi_transfer(struct rt_spi_device* device, const void *send_buf,
		void* recv_buf, rt_size_t length);

rt_inline rt_size_t rt_spi_recv(struct rt_spi_device* device, void* recv_buf, rt_size_t length)
{
	return rt_spi_transfer(device, RT_NULL, recv_buf, length);
}

rt_inline rt_size_t rt_spi_send(struct rt_spi_device* device, const void* send_buf, rt_size_t length)
{
	return rt_spi_transfer(device, send_buf, RT_NULL, length);
}

rt_inline rt_uint8_t rt_spi_sendrecv8(struct rt_spi_device* device, rt_uint8_t data)
{
	rt_uint8_t value;

	rt_spi_send_then_recv(device, &data, 1, &value, 1);
	return value;
}

rt_inline rt_uint16_t rt_spi_sendrecv16(struct rt_spi_device* device, rt_uint16_t data)
{
	rt_uint16_t value;

	rt_spi_send_then_recv(device, &data, 2, &value, 2);
	return value;
}

#endif
