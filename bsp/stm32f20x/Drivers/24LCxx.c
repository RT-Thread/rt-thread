#include <rtthread.h>
#include "i2c.h"

#define EE_Address 0xA0

#define EE24LC024H

/*
	Note: If eeprom size lager then 256 byte, you must define EE_ADDR_SIZE == I2C_MEM_2Bytes
*/
#ifdef EE24LC024H
#define EE_PageSize 8
#define EE_ADDR_SIZE I2C_MEM_1Byte
#define EE_MEM_SIZE	256
#define EE_PageSize 16
#endif

static struct rt_device ee_dev;

uint32_t EE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)
{
	return I2C_IORW(I2C1, pBuffer, NumByteToRead, ReadAddr, EE_Address | 0x01, I2C_MEM_1Byte );
}

uint32_t EE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr)
{ 
	I2C_IORW(I2C1, pBuffer, EE_PageSize , WriteAddr, EE_Address , EE_ADDR_SIZE );

	/*if( I2C_AcknowledgePolling(I2C1 , EE_Address) == Error )
		rt_kprintf("EE ACK failed\n");*/
	rt_thread_delay(50);
}
uint32_t EE_WriteByte(uint8_t* pBuffer, uint16_t WriteAddr)
{
	I2C_IORW(I2C1, pBuffer, 1 , WriteAddr, EE_Address, EE_ADDR_SIZE );

	/*if( I2C_AcknowledgePolling(I2C1 , EE_Address) == Error )
		rt_kprintf("EE ACK failed\n");*/
	rt_thread_delay(50);
}

Status EE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0, NumOfSingle = 0;
	uint16_t Addr = 0,count = 0;
	uint8_t* ptr = pBuffer;
	
	Addr = WriteAddr;

	count = NumByteToWrite;
	
	if( (WriteAddr + NumByteToWrite ) > EE_MEM_SIZE )
		return Error;

	while( count >= EE_PageSize )
	{
		EE_WritePage(ptr, Addr);
		Addr += EE_PageSize;
		count -= EE_PageSize;
		ptr += EE_PageSize;  
	}
	
	while( count )
	{
		EE_WriteByte( ptr++, Addr++ );
		count--;
	}
	
	return Success; 

}

static rt_err_t ee24LCxx_init (rt_device_t dev)
{
	return RT_EOK;
}
static rt_size_t ee24LCxx_read( rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size )
{
	if( EE_ReadBuffer(buf, pos, size) == Success )
	 	return size;
	else
		return -1;
}

static rt_size_t ee24LCxx_write( rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size )
{
	if( EE_WriteBuffer(buf, pos, size) == Success )
	 	return size;
	else
		return -1;
}

static rt_err_t ee24LCxx_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t ee24LCxx_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t ee24LCxx_control (rt_device_t dev, rt_uint8_t cmd, void *args)
{
	return RT_EOK;
}

void ee24LCxx_hw_init()
{ 
	I2C1_INIT();

    ee_dev.init 	= ee24LCxx_init;
    ee_dev.open 	= ee24LCxx_open;
    ee_dev.close	= ee24LCxx_close;
    ee_dev.read 	= ee24LCxx_read;
    ee_dev.write	= ee24LCxx_write;
    ee_dev.control  = ee24LCxx_control;
    ee_dev.type 	= RT_Device_Class_I2C;


    rt_device_register(&ee_dev, "eeprom", RT_DEVICE_FLAG_RDWR);
}

void ee_test()
{
	char buf[256], read[256];
	int i,ret;

	rt_device_t dev;
	dev = rt_device_find("eeprom");

	for(i = 0; i < 256; i++ )
	{
		buf[i] = i;
		read[i] = 0;
	}
	if( rt_device_write(dev, 0, buf, 256 ) == 256 )
		rt_kprintf("Write Success\n");

	rt_device_read(dev, 0, read, 256 );

	for(i = 0; i < 256; i++ )
	{
		if( buf[i] != read[i] )
			rt_kprintf("EE Failed %X != %X at %d\n", buf[i], read[i], i);
	}
	rt_kprintf("Finsh\n");

}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(ee_test, test system);
#endif
