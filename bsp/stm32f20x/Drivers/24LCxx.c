/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-21     JoyChen      First version, support 24LC024H eeprom device
 */

#include <rtthread.h>
#include "i2c.h"

#define EE_Address 0xA0

#define EE24LC024H

/*
	Note: If eeprom size lager then EE_MEM_SIZE byte, you must define EE_ADDR_SIZE == I2C_MEM_2Bytes
*/
#ifdef EE24LC024H
#define EE_ADDR_SIZE I2C_MEM_1Byte
#define EE_MEM_SIZE	256
#define EE_PageSize	16
#endif

static struct rt_device ee_dev;

uint32_t EE_ReadBuffer(void *pBuffer, rt_off_t ReadAddr, rt_size_t NumByteToRead)
{
	return I2C_IORW(I2C1, (uint8_t *)pBuffer, (uint16_t)NumByteToRead, (uint16_t)ReadAddr, EE_Address | 0x01, I2C_MEM_1Byte );
}

uint32_t EE_WritePage(void *pBuffer, uint16_t WriteAddr)
{ 
	I2C_IORW(I2C1, (uint8_t *)pBuffer, EE_PageSize , WriteAddr, EE_Address , EE_ADDR_SIZE );

	/*if( I2C_AcknowledgePolling(I2C1 , EE_Address) == Error )
		rt_kprintf("EE ACK failed\n");*/
	rt_thread_delay(50);

	return 0;
}

uint32_t EE_WriteByte(void *pBuffer, uint16_t WriteAddr)
{
	I2C_IORW(I2C1, (uint8_t *)pBuffer, 1 , WriteAddr, EE_Address, EE_ADDR_SIZE );

	/*if( I2C_AcknowledgePolling(I2C1 , EE_Address) == Error )
		rt_kprintf("EE ACK failed\n");*/
	rt_thread_delay(50);

	return 0;
}

Status EE_WriteBuffer(const void *pBuffer, rt_off_t WriteAddr, rt_size_t NumByteToWrite)
{
	uint8_t NumOfPage = 0, NumOfSingle = 0;
	uint16_t Addr = 0,count = 0;
	uint8_t *ptr = (uint8_t *)pBuffer;
	
	Addr = (uint16_t)(WriteAddr&0xFFFF);

	count = (uint16_t)(NumByteToWrite&0xFFFF);
	
	if ((WriteAddr + NumByteToWrite) > EE_MEM_SIZE)
		return Error;

	while (count >= EE_PageSize)
	{
		EE_WritePage(ptr, Addr);
		Addr += EE_PageSize;
		count -= EE_PageSize;
		ptr += EE_PageSize;  
	}
	
	while (count)
	{
		EE_WriteByte(ptr++, Addr++);
		count--;
	}
	
	return Success; 
}

static rt_err_t ee24LCxx_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t ee24LCxx_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size)
{
	if (EE_ReadBuffer(buf, pos, size) == Success)
		return size;
	else
		return -1;
}

static rt_size_t ee24LCxx_write(rt_device_t dev, rt_off_t pos, const void *buf, rt_size_t size)
{
	if (EE_WriteBuffer(buf, pos, size) == Success)
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

static rt_err_t ee24LCxx_control(rt_device_t dev, int cmd, void *args)
{
	return RT_EOK;
}

void ee24LCxx_hw_init(void)
{
	uint32_t delay, i;
	I2C1_INIT();

	for (i =0; i < 4; i++)
	{
		delay = 0xFFFFF;
		while (delay--);
	}

	ee_dev.init 	= ee24LCxx_init;
	ee_dev.open 	= ee24LCxx_open;
	ee_dev.close	= ee24LCxx_close;
	ee_dev.read 	= ee24LCxx_read;
	ee_dev.write	= ee24LCxx_write;
	ee_dev.control	= ee24LCxx_control;
	ee_dev.type 	= RT_Device_Class_Unknown;

	rt_device_register(&ee_dev, "eeprom", RT_DEVICE_FLAG_RDWR);
}

void dump_ee(void)
{
	rt_device_t dev;
	char buf[EE_MEM_SIZE];
	int i, j;

	dev = rt_device_find("eeprom");
	rt_device_read(dev, 0, buf, EE_MEM_SIZE );

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			rt_kprintf("0x%02X ", buf[ i*16+ j]);
		}
		rt_kprintf("\n");
	}
}

void ee_reset(void)
{
	char buf[EE_MEM_SIZE], read[EE_MEM_SIZE];
	int i;
	rt_device_t dev = rt_device_find("eeprom");

	for (i = 0; i < EE_MEM_SIZE; i++)
	{
		buf[i] = 0xFF;
		read[i] = 0;
	}
	if (rt_device_write(dev, 0, buf, EE_MEM_SIZE ) == EE_MEM_SIZE)
		rt_kprintf("Write Success\n");

	rt_device_read(dev, 0, read, EE_MEM_SIZE );

	for (i = 0; i < EE_MEM_SIZE; i++)
	{
		if (buf[i] != read[i])
			rt_kprintf("EE Failed %X != %X at %d\n", buf[i], read[i], i);
	}
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(ee_reset, test system);
FINSH_FUNCTION_EXPORT(dump_ee, test system);
#endif
