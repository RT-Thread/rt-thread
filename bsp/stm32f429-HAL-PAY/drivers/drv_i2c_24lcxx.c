#include "drv_i2c_24lcxx.h"
#include <rtdevice.h>

#if 1
    #define I2CDEBUG      rt_kprintf
#else
    #define I2CDEBUG(...)
#endif

#define I2C_DEV_ADDR		(0xA0>>1)	/* I2C设备器件地址,不含读写位 */
#define I2C_DEV_BUS_NAME	"i2c2"		/* I2C设备名称,必须和drv_i2c.c注册的I2C设备名称一致 */
#define EEPROM_NAME	"eeprom0"
static struct rt_device ee_dev;
static struct rt_i2c_bus_device *dev_i2c_bus;    /* I2C设备句柄 */

static rt_err_t i2c_dev_read_bytes(rt_uint8_t memAddr, rt_uint8_t *buf, rt_uint16_t len);
static rt_err_t i2c_dev_write_bytes(rt_uint8_t memAddr, rt_uint8_t *data, rt_uint16_t len);
static rt_err_t i2c_dev_write_page(rt_uint8_t memAddr, rt_uint8_t *buffer);
static rt_err_t i2c_dev_write_buffer(rt_uint8_t memAddr, const rt_uint8_t *buffer, rt_uint16_t len);
static rt_err_t i2c_dev_read_buffer(rt_uint8_t memAddr, rt_uint8_t *buffer, rt_uint16_t len);

/*
METHOD == 0：使用rt_i2c_transfer()的封装
METHOD == 1：使用rt_i2c_master_send()或者rt_i2c_master_recv()的封装
*/
#define METHOD 0

#if METHOD == 0
static rt_err_t i2c_dev_write_bytes(rt_uint8_t memAddr, rt_uint8_t *data, rt_uint16_t len)
{
    struct rt_i2c_msg msgs;
    rt_uint8_t buf[len+1];
	rt_uint16_t flags = 0;
	
	if((memAddr + len) > EE_MEM_SIZE || len > EE_PageSize)
	{
		return -RT_ERROR;
	}
	buf[0] = memAddr;
	rt_memcpy(&buf[1],data,len);	
	if(EE_ADDR_SIZE==I2C_ADDR_2Byte)
	{
		flags |= RT_I2C_ADDR_10BIT;
	}
	
    msgs.addr  = I2C_DEV_ADDR;    /* 从机地址 */
    msgs.flags = flags|RT_I2C_WR; /* 写标志 */
    msgs.buf   = buf;             /* 发送数据指针 */
    msgs.len   = len+1;

    if (rt_i2c_transfer(dev_i2c_bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}
static rt_err_t i2c_dev_read_bytes(rt_uint8_t memAddr, rt_uint8_t *buf, rt_uint16_t len)
{
    struct rt_i2c_msg msgs[2];
	rt_uint16_t flags = 0;
	if(EE_ADDR_SIZE==I2C_ADDR_2Byte)
	{
		flags |= RT_I2C_ADDR_10BIT;
	}

    msgs[0].addr  = I2C_DEV_ADDR;    /* 从机地址 */
    msgs[0].flags = RT_I2C_WR;       /* 写标志 */
    msgs[0].buf   = &memAddr;        /* 从机寄存器地址 */
    msgs[0].len   = 1;               /* 发送数据字节数 */

    msgs[1].addr  = I2C_DEV_ADDR;    /* 从机地址 */
    msgs[1].flags = flags|RT_I2C_RD; /* 读标志 */
    msgs[1].buf   = buf;             /* 读取数据指针 */
    msgs[1].len   = len;             /* 读取数据字节数 */

    if (rt_i2c_transfer(dev_i2c_bus, msgs, 2) == 2)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}
#elif METHOD == 1
static rt_err_t i2c_dev_write_bytes(rt_uint8_t memAddr, rt_uint8_t *data, rt_uint16_t len)
{
    rt_uint8_t buf[len+1];	
	rt_uint16_t flags = 0;

	if((memAddr + len) > EE_MEM_SIZE || len > EE_PageSize)
	{
		return -RT_ERROR;
	}
	buf[0] = memAddr;
	rt_memcpy(&buf[1],data,len);
	if(EE_ADDR_SIZE==I2C_ADDR_2Byte)
	{
		flags |= RT_I2C_ADDR_10BIT;
	}
	
    if (rt_i2c_master_send(dev_i2c_bus, I2C_DEV_ADDR, flags, buf, len+1) == len+1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}
static rt_err_t i2c_dev_read_bytes(rt_uint8_t memAddr, rt_uint8_t *buf, rt_uint16_t len)
{
	rt_uint16_t flags = 0;
	if(EE_ADDR_SIZE==I2C_ADDR_2Byte)
	{
		flags |= RT_I2C_ADDR_10BIT;
	}
	
    if (rt_i2c_master_send(dev_i2c_bus, I2C_DEV_ADDR, flags, &memAddr, 1) == 1)
    {
        if (rt_i2c_master_recv(dev_i2c_bus, I2C_DEV_ADDR, flags, buf, len) == len)
        {			
            return RT_EOK;
        }
        else
        {
            return -RT_ERROR;
        }
    }
    else
    {
        return -RT_ERROR;
    }
}
#endif

static rt_err_t i2c_dev_write_page(rt_uint8_t memAddr, rt_uint8_t *buffer)
{
	rt_err_t res = RT_EOK;
	rt_uint16_t len = EE_PageSize;	
	if((memAddr + len) > EE_MEM_SIZE)
	{
		return -RT_ERROR;
	}
	res = i2c_dev_write_bytes(memAddr, buffer, len);
	rt_thread_delay(rt_tick_from_millisecond(5));
	return res;
}

static rt_err_t i2c_dev_write_buffer(rt_uint8_t memAddr, const rt_uint8_t *buffer, rt_uint16_t len)
{
	rt_err_t res = RT_EOK;
	uint16_t Addr = 0,count = 0;
	uint8_t *ptr = (uint8_t *)buffer;	
	Addr = (uint16_t)(memAddr&0xFFFF);
	count = (uint16_t)(len&0xFFFF);
	
	if ((memAddr + len) > EE_MEM_SIZE)
		return -RT_ERROR;
	while (count >= EE_PageSize && res==RT_EOK)
	{
		res = i2c_dev_write_page(Addr, ptr);
		Addr += EE_PageSize;
		count -= EE_PageSize;
		ptr += EE_PageSize;  
	}
	res = i2c_dev_write_bytes(Addr++, ptr, count);
	rt_thread_delay(rt_tick_from_millisecond(5));
	return res;
}
static rt_err_t i2c_dev_read_buffer(rt_uint8_t memAddr, rt_uint8_t *buffer, rt_uint16_t len)
{
	rt_err_t res = RT_EOK;
	if((memAddr + len) > EE_MEM_SIZE)
	{
		return -RT_ERROR;
	}
	res = i2c_dev_read_bytes(memAddr, buffer, len);
	return res;
}
/* end of i2c_dev driver */
static rt_err_t ee24LCxx_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t ee24LCxx_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size)
{
	if (i2c_dev_read_buffer(pos, buf, size) == RT_EOK)
		return size;
	else
		return 0;
}

static rt_size_t ee24LCxx_write(rt_device_t dev, rt_off_t pos, const void *buf, rt_size_t size)
{
	if (i2c_dev_write_buffer(pos, buf, size) == RT_EOK)
		return size;
	else
		return 0;
}

static rt_err_t ee24LCxx_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t ee24LCxx_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t ee24LCxx_control(rt_device_t dev, int cmd, void *args)
{
	return RT_EOK;
}

//I2C_DEV硬件初始化
int i2c_dev_hw_init(void)
{
    dev_i2c_bus = rt_i2c_bus_device_find(I2C_DEV_BUS_NAME);  /*查找I2C设备*/
    if (dev_i2c_bus == RT_NULL)
    {
        I2CDEBUG("can't find i2c_dev %s device\r\n", I2C_DEV_BUS_NAME);
        return -RT_ERROR;
    }
    I2CDEBUG("i2c_dev set i2c bus to %s\r\n", I2C_DEV_BUS_NAME);
	
	ee_dev.init 	= ee24LCxx_init;
	ee_dev.open 	= ee24LCxx_open;
	ee_dev.close	= ee24LCxx_close;
	ee_dev.read 	= ee24LCxx_read;
	ee_dev.write	= ee24LCxx_write;
	ee_dev.control	= ee24LCxx_control;
	ee_dev.type 	= RT_Device_Class_Unknown;

	rt_device_register(&ee_dev, EEPROM_NAME, RT_DEVICE_FLAG_RDWR);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(i2c_dev_hw_init);
