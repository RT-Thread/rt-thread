/*
 * File      : bmi055_sensor.cpp
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author           Notes
 * 2015-1-11     RT_learning      the first version
 */

#include <string.h>
#include <stdio.h>
#include <rtdevice.h>
#include "bmi055_sensor.h"


const static sensor_t _BMI055_sensor[] = 
{
    {
    .name = "Accelerometer",
    .vendor = "Bosch",
    .version = sizeof(sensor_t), 
    .handle = 0, 
    .type = SENSOR_TYPE_ACCELEROMETER, 
    .maxRange = SENSOR_ACCEL_RANGE_16G,
    .resolution = 1.0f, 
    .power = 0.5f,
    .minDelay = 10000, 
    .fifoReservedEventCount = 0, 
    .fifoMaxEventCount = 64, 
    },
    {
    .name = "Gyroscope",
    .vendor = "Bosch",
    .version = sizeof(sensor_t), 
    .handle = 0, 
    .type = SENSOR_TYPE_GYROSCOPE, 
    .maxRange = SENSOR_GYRO_RANGE_2000DPS,
    .resolution = 1.0f,
    .power = 0.5f,
    .minDelay = 10000, 
    .fifoReservedEventCount = 0, 
    .fifoMaxEventCount = 64, 
    }
};

BMI055::BMI055(int sensor_type, const char* iic_bus, int addr)
	: SensorBase(sensor_type)
{
    this->i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(iic_bus);
    if (this->i2c_bus == NULL) 
    {
        printf("BMI055: No IIC device:%s\n", iic_bus);
        return;
    }

    this->i2c_addr = addr;

    /* register to sensor manager */
    SensorManager::registerSensor(this);
}

int BMI055::read_reg(rt_uint8_t reg, rt_uint8_t *value)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = this->i2c_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &reg;
    msgs[0].len   = 1;

    msgs[1].addr  = this->i2c_addr;
    msgs[1].flags = RT_I2C_RD; /* Read from slave */
    msgs[1].buf   = (rt_uint8_t *)value;
    msgs[1].len   = 1;

    if (rt_i2c_transfer(this->i2c_bus, msgs, 2) == 2)
        return RT_EOK;

    return -RT_ERROR;
}

int BMI055::read_buffer(rt_uint8_t reg, rt_uint8_t* value, rt_size_t size)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = this->i2c_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &reg;
    msgs[0].len   = 1;

    msgs[1].addr  = this->i2c_addr;
    msgs[1].flags = RT_I2C_RD; /* Read from slave */
    msgs[1].buf   = (rt_uint8_t *)value;
    msgs[1].len   = size;

    if (rt_i2c_transfer(this->i2c_bus, msgs, 2) == 2)
        return RT_EOK;

    return -RT_ERROR;
}

int BMI055::write_reg(rt_uint8_t reg, rt_uint8_t value)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = this->i2c_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &reg;
    msgs[0].len   = 1;

    msgs[1].addr  = this->i2c_addr;
    msgs[1].flags = RT_I2C_WR | RT_I2C_NO_START;
    msgs[1].buf   = (rt_uint8_t *)&value;
    msgs[1].len   = 1;

    if (rt_i2c_transfer(this->i2c_bus, msgs, 2) == 2)
        return RT_EOK;
    
    return -RT_ERROR;
}


BMI055_Accelerometer::BMI055_Accelerometer(const char* iic_name, int addr)
    : BMI055(SENSOR_TYPE_ACCELEROMETER, iic_name, addr)
{
	int index;
	uint8_t id;
	rt_uint8_t value[6] = {0};
	rt_int32_t x, y, z;
    SensorConfig config = {SENSOR_MODE_NORMAL, SENSOR_DATARATE_400HZ, SENSOR_ACCEL_RANGE_2G};
	
	write_reg(BMI055_BGW_SOFTRESET, 0xB6);			/* reset of the sensor  P57							*/
	write_reg(BMI055_PMU_LPW, 0x00);				/* PMU_LPW   NORMAL mode P55						*/
	write_reg(BMI055_PMU_BW, 0x0A);					/* 01010b  31.25 Hz P55								*/
	write_reg(BMI055_PMU_RANGE, 0x05);				/* 0101b  ±4g range PMU_RANGE set acc +-4g/s  P54	*/
	
		
	x_offset = y_offset = z_offset = 0;
	x = y = z = 0;

	/* read BMI055 id */
	read_buffer(BMI055_ACC_BGW_CHIPID, &id, 1);		/* BGW_CHIPID P47*/
	if (id != BMI055_ACC_BGW_CHIPID_VALUE)
	{
		printf("Warning: not found BMI055 id: %02x\n", id);
	}

	/* get offset */
	for (index = 0; index < 200; index ++)
	{
		read_buffer(BMI055_ACCD_X_LSB, value, 6);					/*ACCD_X_LSB P47 */
		
		x += (((rt_int16_t)value[1] << 8)   | value[0]);
		y += (((rt_int16_t)value[3] << 8)   | value[2]);
		z += (((rt_int16_t)value[5] << 8)   | value[4]);		
	}
	x_offset = x / 200;
	y_offset = y / 200;
	z_offset = z / 200;
    
	this->enable = RT_FALSE;
	this->sensitivity = SENSOR_ACCEL_SENSITIVITY_2G;
    this->config = config;
}

int 
BMI055_Accelerometer::configure(SensorConfig *config)
{
	int range;
	uint8_t value;

	if (config == RT_NULL) return -1;

	/* TODO: set datarate */

	/* get range and calc the sensitivity */
	range = config->range.accel_range;
	switch (range)
	{
	case SENSOR_ACCEL_RANGE_2G:
		this->sensitivity = SENSOR_ACCEL_SENSITIVITY_2G;
		range = 0x03;		//0011b
		break;
	case SENSOR_ACCEL_RANGE_4G:
		this->sensitivity = SENSOR_ACCEL_SENSITIVITY_4G;
		range = 0x05;		//0101b
		break;
	case SENSOR_ACCEL_RANGE_8G:
		this->sensitivity = SENSOR_ACCEL_SENSITIVITY_8G;
		range = 0x01 << 3;	//1000b
		break;
	case SENSOR_ACCEL_RANGE_16G:
		this->sensitivity = SENSOR_ACCEL_SENSITIVITY_16G;
		range = 0x03 << 2;	//1100b
		break;
	default:
		return -1;
	}

	/* set range to sensor */
	read_reg(BMI055_PMU_RANGE, &value);		/* PMU_RANGE P54 */
	value &= 0xF0;
	value |= range;
	write_reg(BMI055_PMU_RANGE, value);

    return 0;
}

int 
BMI055_Accelerometer::activate(int enable)
{
	uint8_t value;

    if (enable && this->enable == RT_FALSE)
    {
        /* enable accelerometer */
		read_reg(BMI055_PMU_LPW, &value); 	/* P55 */
		value &= ~(0x07 << 7);
		write_reg(BMI055_PMU_LPW, value);
    }

	if (!enable && this->enable == RT_TRUE)
    {
        /* disable accelerometer */
		read_reg(BMI055_PMU_LPW, &value); 
		value &= ~(0x07 << 7);
		value |= (0x01 << 7);
		write_reg(BMI055_PMU_LPW, value);
    }

	if (enable) this->enable = RT_TRUE;
	else this->enable = RT_FALSE;

    return 0;
}

int 
BMI055_Accelerometer::poll(sensors_event_t *event)
{
	rt_uint8_t value[6];
	rt_int16_t x, y, z;

    /* parameters check */
    if (event == NULL) return -1;

	/* get event data */
	event->version = sizeof(sensors_event_t);
	event->sensor = (int32_t) this;
	event->timestamp = rt_tick_get();
	event->type = SENSOR_TYPE_ACCELEROMETER;

	read_buffer(0x02, value, 6);

	/* get raw data */
	x = (((rt_int16_t)value[1] << 8) | value[0]);
	y = (((rt_int16_t)value[3] << 8) | value[2]);
	z = (((rt_int16_t)value[5] << 8) | value[4]);

	if (config.mode == SENSOR_MODE_RAW)
	{
		event->raw_acceleration.x = x;
		event->raw_acceleration.y = y;
		event->raw_acceleration.z = z;
	}
	else
	{

		x -= x_offset; y -= y_offset; z -= z_offset;
		event->acceleration.x = x * this->sensitivity * SENSORS_GRAVITY_STANDARD;
		event->acceleration.y = y * this->sensitivity * SENSORS_GRAVITY_STANDARD;
		event->acceleration.z = z * this->sensitivity * SENSORS_GRAVITY_STANDARD;
	}
	
	return 0;
}

void 
BMI055_Accelerometer::getSensor(sensor_t *sensor)
{
    /* get sensor description */
    if (sensor)
    {
        memcpy(sensor, &_BMI055_sensor[0], sizeof(sensor_t));
    }
}

BMI055_Gyroscope::BMI055_Gyroscope(const char* iic_name, int addr)
    : BMI055(SENSOR_TYPE_GYROSCOPE, iic_name, addr)
{
	int index;
	uint8_t id;
	rt_uint8_t value[6];
	rt_int32_t x, y, z;

    /* initialize BMI055 */
    write_reg(BMI055_MODE_LPM1_ADDR, 0x00);			/* normal mode 						*/
	write_reg(BMI055_MODE_LPM2_ADDR, 0x80);			/* fast powerup 					*/
    write_reg(BMI055_BW_ADDR,        0x03);			/* ODR:400Hz Filter Bandwidth:47Hz	*/
	write_reg(BMI055_RANGE_ADDR,     0x00);			/* 2000dps 							*/
	

	x_offset = y_offset = z_offset = 0;
	x = y = z = 0;

	/* read BMI055 id */
	read_buffer(BMI055_CHIP_ID_ADDR, &id, 1);
	if (id != BMI055_GRRO_CHIP_ID)
	{
		printf("Warning: not found BMI055 id: %02x\n", id);
	}

	/* get offset */
	for (index = 0; index < 200; index ++)
	{
		read_buffer(BMI055_RATE_X_LSB_ADDR, value, 6);

		x += (((rt_int16_t)value[1] << 8)   | value[0]);
		y += (((rt_int16_t)value[3] << 8)   | value[2]);
		z += (((rt_int16_t)value[5] << 8)   | value[4]);		
	}
	x_offset = x / 200;
	y_offset = y / 200;
	z_offset = z / 200;

	this->enable = RT_FALSE;
	this->sensitivity = SENSOR_GYRO_SENSITIVITY_250DPS;
}

int 
BMI055_Gyroscope::configure(SensorConfig *config)
{
	int range;
	uint8_t value;

	if (config == RT_NULL) return -1;

	/* TODO: set datarate */

	/* get range and calc the sensitivity */
	range = config->range.gyro_range;
	switch (range)
	{
	//to do add more range e.g   125DPS
	//case 
	case SENSOR_GYRO_RANGE_250DPS:
		this->sensitivity = SENSOR_GYRO_SENSITIVITY_250DPS;
		range = 0x11;
		break;
	case SENSOR_GYRO_RANGE_500DPS:
		this->sensitivity = SENSOR_GYRO_SENSITIVITY_500DPS;
		range = 0x10;
		break;
	case SENSOR_GYRO_RANGE_1000DPS:
		this->sensitivity = SENSOR_GYRO_SENSITIVITY_1000DPS;
		range = 0x01;
		break;
	case SENSOR_GYRO_RANGE_2000DPS:
		this->sensitivity = SENSOR_GYRO_SENSITIVITY_2000DPS;
		range = 0x00;
		break;
	default:
		return -1;
	}

	/* set range to sensor */
	read_reg(BMI055_RANGE_ADDR, &value);
	value &= ~0x07;
	value |= range;
	write_reg(BMI055_RANGE_ADDR, value);

    return 0;
}

int 
BMI055_Gyroscope::activate(int enable)
{
	uint8_t value;
	
    if (enable && this->enable == RT_FALSE)
    {
        /* enable gyroscope */
		read_reg(BMI055_MODE_LPM1_ADDR, &value);   
		value &= ~(0x1010 << 4);					//{0; 0}  NORMAL mode
		write_reg(BMI055_MODE_LPM1_ADDR, value);	//P101 NORMAL mode
    }

	if (!enable && this->enable == RT_TRUE)
    {
        /* disable gyroscope */
		read_reg(BMI055_MODE_LPM1_ADDR, &value); 
		value &= ~(0x01 << 5);						//set bit5 deep_suspend 0
		value |= (0x01 << 7);						//set bit1 suspend 1   
		write_reg(BMI055_MODE_LPM1_ADDR, value);	//{1; 0} SUSPEND mode
    }

	if (enable) this->enable = RT_TRUE;
	else this->enable = RT_FALSE;

    return 0;
}

int 
BMI055_Gyroscope::poll(sensors_event_t *event)
{
	rt_uint8_t value[6];
	rt_int16_t x, y, z;

	/* parameters check */
	if (event == NULL) return -1;

	/* get event data */
	event->version = sizeof(sensors_event_t);
	event->sensor = (int32_t) this;
	event->timestamp = rt_tick_get();
	event->type = SENSOR_TYPE_GYROSCOPE;

	read_buffer(BMI055_RATE_X_LSB_ADDR, value, 6);

	/* get raw data */
	x = (((rt_int16_t)value[1] << 8) | value[0]);
	y = (((rt_int16_t)value[3] << 8) | value[2]);
	z = (((rt_int16_t)value[5] << 8) | value[4]);

	
	if (config.mode == SENSOR_MODE_RAW)
	{
		event->raw_gyro.x = x;
		event->raw_gyro.y = y;
		event->raw_gyro.z = z;
	}
	else
	{
		x -= x_offset; y -= y_offset; z -= z_offset;
		event->gyro.x = x * this->sensitivity * SENSORS_DPS_TO_RADS;
		event->gyro.y = y * this->sensitivity * SENSORS_DPS_TO_RADS;
		event->gyro.z = z * this->sensitivity * SENSORS_DPS_TO_RADS;
	}
	
	return 0;
}

void 
BMI055_Gyroscope::getSensor(sensor_t *sensor)
{
    /* get sensor description */
    if (sensor)
    {
        memcpy(sensor, &_BMI055_sensor[1], sizeof(sensor_t));
    }
}
