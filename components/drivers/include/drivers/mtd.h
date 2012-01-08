#ifndef __MTD_H__
#define __MTD_H__

struct rt_mtd_device
{
	const struct rt_mtd_driver_ops* ops;
};

struct rt_mtd_driver_ops
{
	rt_uint32_t (*read_id) (rt_mtd_device* device);
	rt_err_t (*read_page)  (rt_mtd_device* device, rt_uint32_t page, rt_uint8_t *data, rt_uint8_t *spare);
	rt_err_t (*write_page) (rt_mtd_device* device, rt_uint32_t page, rt_uint8_t *data, rt_uint8_t *spare);

	rt_err_t (*erase_block)(rt_mtd_device* device, rt_uint32_t block);
};

#endif
