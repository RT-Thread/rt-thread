/*
 * File      : MPU6050_sensor.cpp
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-12-20     Bernard      the first version
 * 2015-1-11      RT_learning  modify the mpu6050 initialize
 */

#include <string.h>
#include <stdio.h>
#include <rtdevice.h>

#include "mpu6050_sensor.h"


const static sensor_t _MPU6050_sensor[] = 
{
    {
    .name = "Accelerometer",
    .vendor = "Invensense",
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
    .vendor = "Invensense",
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

MPU6050::MPU6050(int sensor_type, const char* iic_bus, int addr)
	: SensorBase(sensor_type)
{
    this->i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(iic_bus);
    if (this->i2c_bus == NULL) 
    {
        printf("MPU6050: No IIC device:%s\n", iic_bus);
        return;
    }

    this->i2c_addr = addr;

    /* register to sensor manager */
    SensorManager::registerSensor(this);
}

int MPU6050::read_reg(rt_uint8_t reg, rt_uint8_t *value)
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

int MPU6050::read_buffer(rt_uint8_t reg, rt_uint8_t* value, rt_size_t size)
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

int MPU6050::write_reg(rt_uint8_t reg, rt_uint8_t value)
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


MPU6050_Accelerometer::MPU6050_Accelerometer(const char* iic_name, int addr)
    : MPU6050(SENSOR_TYPE_ACCELEROMETER, iic_name, addr)
{
	int index;
	uint8_t id;
	rt_uint8_t value[6] = {0};
	rt_int32_t x, y, z;
    SensorConfig config = {SENSOR_MODE_NORMAL, SENSOR_DATARATE_400HZ, SENSOR_ACCEL_RANGE_2G};

	/* initialize MPU6050 */
    write_reg(MPU6050_PWR_MGMT_1,   0x80);			/* reset mpu6050 device 									*/
	write_reg(MPU6050_SMPLRT_DIV,   0x00);			/* Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) 	*/
    write_reg(MPU6050_PWR_MGMT_1,   0x03);			/* Wake up device , set device clock Z axis gyroscope		*/
	write_reg(MPU6050_CONFIG,   	0x03);			/* set DLPF_CFG 42Hz										*/
    write_reg(MPU6050_GYRO_CONFIG,  0x18);			/* set gyro 2000deg/s 										*/
    write_reg(MPU6050_ACCEL_CONFIG, 0x08);			/* set acc +-4g/s 											*/
	
		
	x_offset = y_offset = z_offset = 0;
	x = y = z = 0;

	/* read MPU6050 id */
	read_buffer(MPU6050_WHOAMI, &id, 1);
	if (id != MPU6050_ID)
	{
		printf("Warning: not found MPU6050 id: %02x\n", id);
	}

	/* get offset */
	for (index = 0; index < 200; index ++)
	{
		read_buffer(MPU6050_ACCEL_XOUT_H, value, 6);
		
		x += (((rt_int16_t)value[0] << 8)   | value[1]);
		y += (((rt_int16_t)value[2] << 8)   | value[3]);
		z += (((rt_int16_t)value[4] << 8)   | value[5]);		
	}
	x_offset = x / 200;
	y_offset = y / 200;
	z_offset = z / 200;
    
	this->enable = RT_FALSE;
	this->sensitivity = SENSOR_ACCEL_SENSITIVITY_2G;
  this->config = config;
}

int 
MPU6050_Accelerometer::configure(SensorConfig *config)
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
		range = 0;
		break;
	case SENSOR_ACCEL_RANGE_4G:
		this->sensitivity = SENSOR_ACCEL_SENSITIVITY_4G;
		range = 0x01 << 2;
		break;
	case SENSOR_ACCEL_RANGE_8G:
		this->sensitivity = SENSOR_ACCEL_SENSITIVITY_8G;
		range = 0x02 << 2;
		break;
	case SENSOR_ACCEL_RANGE_16G:
		this->sensitivity = SENSOR_ACCEL_SENSITIVITY_16G;
		range = 0x03 << 2;
		break;
	default:
		return -1;
	}

	/* set range to sensor */
	read_reg(MPU6050_ACCEL_CONFIG, &value);
	value &= ~(0x3 << 2);
	value |= range;
	write_reg(MPU6050_ACCEL_CONFIG, value);

    return 0;
}

int 
MPU6050_Accelerometer::activate(int enable)
{
	uint8_t value;

    if (enable && this->enable == RT_FALSE)
    {
        /* enable accelerometer */
		read_reg(MPU6050_PWR_MGMT_2, &value); 
		value &= ~(0x07 << 2);
		write_reg(MPU6050_PWR_MGMT_2, value);
    }

	if (!enable && this->enable == RT_TRUE)
    {
        /* disable accelerometer */
		read_reg(MPU6050_PWR_MGMT_2, &value); 
		value |= (0x07 << 2);
		write_reg(MPU6050_PWR_MGMT_2, value);
    }

	if (enable) this->enable = RT_TRUE;
	else this->enable = RT_FALSE;

    return 0;
}

int 
MPU6050_Accelerometer::poll(sensors_event_t *event)
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

	read_buffer(MPU6050_ACCEL_XOUT_H, value, 6);

	/* get raw data */
	x = (((rt_int16_t)value[0] << 8) | value[1]);
	y = (((rt_int16_t)value[2] << 8) | value[3]);
	z = (((rt_int16_t)value[4] << 8) | value[5]);

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
MPU6050_Accelerometer::getSensor(sensor_t *sensor)
{
    /* get sensor description */
    if (sensor)
    {
        memcpy(sensor, &_MPU6050_sensor[0], sizeof(sensor_t));
    }
}

MPU6050_Gyroscope::MPU6050_Gyroscope(const char* iic_name, int addr)
    : MPU6050(SENSOR_TYPE_GYROSCOPE, iic_name, addr)
{
	int index;
	uint8_t id;
	rt_uint8_t value[6];
	rt_int32_t x, y, z;

    /* initialize MPU6050 */
    write_reg(MPU6050_PWR_MGMT_1,   0x80);			/* reset mpu6050 device 									*/
	write_reg(MPU6050_SMPLRT_DIV,   0x00);			/* Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) 	*/
    write_reg(MPU6050_PWR_MGMT_1,   0x03);			/* Wake up device , set device clock Z axis gyroscope		*/
	write_reg(MPU6050_CONFIG,   	0x03);			/* set DLPF_CFG 42Hz 										*/
    write_reg(MPU6050_GYRO_CONFIG,  0x18);			/* set gyro 2000deg/s										*/
    write_reg(MPU6050_ACCEL_CONFIG, 0x08);			/* set acc +-4g/s 											*/

	x_offset = y_offset = z_offset = 0;
	x = y = z = 0;

	/* read MPU6050 id */
	read_reg(MPU6050_WHOAMI, &id);
	if (id != MPU6050_ID)
	{
		printf("Warning: not found MPU6050 id: %02x\n", id);
	}

	/* get offset */
	for (index = 0; index < 200; index ++)
	{
		read_buffer(MPU6050_GYRO_XOUT_H, value, 6);

		x += (((rt_int16_t)value[0] << 8)   | value[1]);
		y += (((rt_int16_t)value[2] << 8)   | value[3]);
		z += (((rt_int16_t)value[4] << 8)   | value[5]);		
	}
	x_offset = x / 200;
	y_offset = y / 200;
	z_offset = z / 200;

	this->enable = RT_FALSE;
	this->sensitivity = SENSOR_GYRO_SENSITIVITY_250DPS;
}

int 
MPU6050_Gyroscope::configure(SensorConfig *config)
{
	int range;
	uint8_t value;

	if (config == RT_NULL) return -1;

	/* TODO: set datarate */

	/* get range and calc the sensitivity */
	range = config->range.gyro_range;
	switch (range)
	{
	case SENSOR_GYRO_RANGE_250DPS:
		this->sensitivity = SENSOR_GYRO_SENSITIVITY_250DPS;
		range = 0;
		break;
	case SENSOR_GYRO_RANGE_500DPS:
		this->sensitivity = SENSOR_GYRO_SENSITIVITY_500DPS;
		range = 0x01 << 2;
		break;
	case SENSOR_GYRO_RANGE_1000DPS:
		this->sensitivity = SENSOR_GYRO_SENSITIVITY_1000DPS;
		range = 0x02 << 2;
		break;
	case SENSOR_GYRO_RANGE_2000DPS:
		this->sensitivity = SENSOR_GYRO_SENSITIVITY_2000DPS;
		range = 0x03 << 2;
		break;
	default:
		return -1;
	}

	/* set range to sensor */
	read_reg(MPU6050_GYRO_CONFIG, &value);
	value &= ~(0x3 << 2);
	value |= range;
	write_reg(MPU6050_GYRO_CONFIG, value);

    return 0;
}

int 
MPU6050_Gyroscope::activate(int enable)
{
	uint8_t value;
	
    if (enable && this->enable == RT_FALSE)
    {
        /* enable gyroscope */
		read_reg(MPU6050_PWR_MGMT_1, &value);
		value &= ~(0x01 << 4);
		write_reg(MPU6050_PWR_MGMT_1, value);

		read_reg(MPU6050_PWR_MGMT_2, &value); 
		value &= ~(0x07 << 0);
		write_reg(MPU6050_PWR_MGMT_2, value);
    }

	if (!enable && this->enable == RT_TRUE)
    {
        /* disable gyroscope */
		read_reg(MPU6050_PWR_MGMT_2, &value); 
		value |= (0x07 << 0);
		write_reg(MPU6050_PWR_MGMT_2, value);
    }

	if (enable) this->enable = RT_TRUE;
	else this->enable = RT_FALSE;

    return 0;
}

int 
MPU6050_Gyroscope::poll(sensors_event_t *event)
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

	read_buffer(MPU6050_GYRO_XOUT_H, value, 6);

	/* get raw data */
	x = (((rt_int16_t)value[0] << 8) | value[1]);
	y = (((rt_int16_t)value[2] << 8) | value[3]);
	z = (((rt_int16_t)value[4] << 8) | value[5]);

	
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
MPU6050_Gyroscope::getSensor(sensor_t *sensor)
{
    /* get sensor description */
    if (sensor)
    {
        memcpy(sensor, &_MPU6050_sensor[1], sizeof(sensor_t));
    }
}

