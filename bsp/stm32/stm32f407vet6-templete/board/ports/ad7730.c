/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-06-30     wangk        add spi adc port file
 */

#include <rtthread.h>
#include "drv_spi.h"
#include "ad7730.h"

#if defined(BSP_USING_AD7730)

#define AD7730_DEBUG

#ifdef AD7730_DEBUG
    #define AD7730_TRACE	rt_kprintf
#else
    #define AD7730_TRACE(...)
#endif /* AD7730_DEBUG */

#define AD7730_SPI_BUS_NAME "spi2"
#define AD7730_SPI_DEVICE_NAME "spi20"
/* defined the RDY pin: PC2 */
#define AD7730_RDY_PIN			GET_PIN(C, 2)
/* defined the STANDBY pin: PC3 */
#define AD7730_STANDBY_PIN		GET_PIN(C, 3)
/* defined the RESET pin: PC4 */
#define AD7730_RESET_PIN		GET_PIN(C, 4)
/* defined the REF_SLEEP pin: PA9 */
#define AD7730_REF_SLEEP_PIN	GET_PIN(A, 9)

#define ad7730_lock(dev)      rt_mutex_take(&((struct ad7730_device*)dev)->lock, RT_WAITING_FOREVER);
#define ad7730_unlock(dev)    rt_mutex_release(&((struct ad7730_device*)dev)->lock);

static struct ad7730_device ad7730_dev;

/* read the specific register */
static rt_err_t ad7730_spi_readreg(uint8_t reg, uint8_t* recv_buf, rt_size_t buf_len)
{
	struct rt_spi_device* spi_device = ad7730_dev.spi_device;
	
	uint8_t send_buf[1] = {CR_SINGLE_READ | reg};

    return rt_spi_send_then_recv(spi_device, send_buf, sizeof(send_buf), recv_buf, buf_len);
}

/* write the specific register */
static rt_err_t ad7730_spi_writereg(uint8_t reg, const uint8_t* send_data, rt_size_t data_len)
{
	struct rt_spi_device* spi_device = ad7730_dev.spi_device;
	
	uint8_t send_buf[1] = {CR_SINGLE_WRITE | reg};

    return rt_spi_send_then_send(spi_device, send_buf, sizeof(send_buf), send_data, data_len);
}

/* wait ad7730 rdy pin low */
static rt_err_t ad7730_wait_rdy(rt_device_t dev, rt_int32_t ms)
{
#if 1
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	rt_err_t ret = RT_EOK;
	while (rt_pin_read(ad7730->rdy_pin) != PIN_LOW)
	{
		if (ms <= 0)
		{ // timeout
			ret = -RT_ERROR;
			break;
		}
		rt_thread_mdelay(1);
		--ms;
	}
#else
	rt_err_t ret = RT_EOK;
	uint8_t recv_buf[1] = {0};
	while (1)
	{
		if (ms <= 0)
		{ // timeout
			ret = -RT_ERROR;
			break;
		}
		
		ret = ad7730_spi_readreg(CR_STATUS_REGISTER, recv_buf, 1);
		if (RT_EOK != ret)
		{
			rt_kprintf("read CR_STATUS_REGISTER failed!\r\n");
			return ret;
		}
		if (0x00 == (recv_buf[0] & 0x80))
		{
			break;
		}
		
		rt_thread_mdelay(1);
		--ms;
	}
#endif
	
	return ret;
}

/* ad7730 single read data */
static uint32_t ad7730_single_read_data(rt_device_t dev)
{
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	struct rt_spi_device* spi_device = ad7730->spi_device;
	
	uint8_t send_data[3] = {0};
	uint8_t recv_buf[3] = {0};
	
	send_data[0] = (CR_SINGLE_READ | CR_DATA_REGISTER);
	rt_size_t send_len = rt_spi_send(spi_device, send_data, 1);
	if (1 != send_len)
	{
		AD7730_TRACE("ad7730 single read set communication register failed(%d)!\r\n", send_len);
		return 0;
	}

	send_data[0] = 0xFF; //transfer 0xFF (set MSB) to prevent writing to CR accidentally during reading
	send_data[1] = 0xFF;
	send_data[2] = 0xFF;
	send_len = rt_spi_transfer(spi_device, send_data, recv_buf, 3); // return the actual length of transmitted
	if (3 != send_len)
	{
		AD7730_TRACE("ad7730 single read data failed(%d)!\r\n", send_len);
		return 0;
	}
	
	uint32_t adc_val = ((uint32_t)(recv_buf[0]) << 16) | ((uint32_t)(recv_buf[1]) << 8) | ((uint32_t)(recv_buf[2])/* << 0*/);
	
    return adc_val;
}

/* ad7730 continuous read data */
static uint32_t ad7730_cont_read_data(rt_device_t dev)
{
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	struct rt_spi_device* spi_device = ad7730->spi_device;
	
	uint8_t send_data[3] = {0};
	uint8_t recv_buf[3] = {0};
	
	send_data[0] = 0x0;
	send_data[1] = 0x0;
	send_data[2] = 0x0; //need to transfer all 0 bytes to keep DIN of AD7730 low prevent device reset during cont read
	rt_size_t send_len = rt_spi_transfer(spi_device, send_data, recv_buf, 3); // return the actual length of transmitted
	if (3 != send_len)
	{
		AD7730_TRACE("ad7730 continuous read data failed(%d)!\r\n", send_len);
		return 0;
	}
	
	uint32_t adc_val = ((uint32_t)(recv_buf[0]) << 16) | ((uint32_t)(recv_buf[1]) << 8) | ((uint32_t)(recv_buf[2])/* << 0*/);
	
    return adc_val;
}

/* config ad7730 */
static rt_err_t ad7730_config(rt_device_t dev)
{
	AD7730_TRACE("ad7730_config()\r\n");
	
	//struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	uint8_t send_data[3] = {0};
	rt_err_t ret = RT_EOK;
	
#if 0
	/* 配置AC CHOP DL */
	/* -------------- Filter Config ----------------------- */
	send_data[0] = FR2_SINC_AVERAGING_256;
	send_data[1] = (FR1_SKIP_OFF | FR1_FAST_OFF);
	send_data[2] = FR0_AC_ON | FR0_CHOP_ON | FR0_DL_15;
	ret = ad7730_spi_writereg(CR_FILTER_REGISTER, send_data, 3);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 filter config failed(%d)!\r\n", ret);
		return ret;
    }
#else
	/* -------------- Filter Config ----------------------- */
	send_data[0] = FR2_SINC_AVERAGING_256;
	send_data[1] = (FR1_SKIP_OFF | FR1_FAST_OFF);
	//send_data[2] = FR0_CHOP_OFF;
	send_data[2] = FR0_CHOP_ON;
	ret = ad7730_spi_writereg(CR_FILTER_REGISTER, send_data, 3);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 filter config failed(%d)!\r\n", ret);
		return ret;
    }
#endif
	
	/* -------------- DAC Config ----------------------- */
	send_data[0] = (DACR_OFFSET_SIGN_POSITIVE | DACR_OFFSET_NONE); //set DAC to zero offset
	ret = ad7730_spi_writereg(CR_DAC_REGISTER, send_data, 1);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 dac config failed(%d)!\r\n", ret);
		return ret;
    }
	
    return RT_EOK;
}

/* calibration ad7730 */
static rt_err_t ad7730_calibration(rt_device_t dev, int adc_channel)
{
	AD7730_TRACE("ad7730_calibration() adc_channel=%d\r\n", adc_channel);
	
	if ((adc_channel < 0)
		|| (adc_channel >= 3))
	{
		AD7730_TRACE("ad7730_calibration() failed, invalid channel(%d)!\r\n", adc_channel);
		return -RT_ERROR;
	}
	
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	
	ad7730_lock(dev);
	
	if (AD7730_IDLE != ad7730->work_state)
	{
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730_calibration(%d) failed, busy in state(%d)!\r\n", adc_channel, ad7730->work_state);
		return -RT_ERROR;
	}
	
	ad7730_unlock(dev);

	uint8_t send_data[2] = {0};
	rt_err_t ret = RT_EOK;
	
	/* 
		It is recommended that internal full-scale calibrations are performed on the 80 mV range, regardless
		of the subsequent operating range, to optimize the postcalibration gain error. 
		This calibration should be followed by either an Internal Zero-Scale or System Zero-Scale calibration.
	*/
	/* -------------- Internal Full Scale Calibration ----------------------- */
	send_data[0] = MR1_MODE_INTERNAL_FULL_CALIBRATION | CURRENT_MODE_1_SETTINGS_CAL;
	send_data[1] = CURRENT_MODE_0_SETTINGS_CAL_FULL | adc_channel;
	ret = ad7730_spi_writereg(CR_MODE_REGISTER, send_data, 2);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 internal full scale calibration failed(%d)!\r\n", ret);
		return ret;
    }
	ret = ad7730_wait_rdy(dev, 5000); // wait for ready pin to go low after calibration
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 internal full scale calibration wait rdy failed(%d)!\r\n", ret);
		return ret;
    }

	/* This zero-scale calibration should be performed at the operating input range */
#if 0
	/* -------------- Internal Zero Calibration  ----------------------- */
	send_data[0] = MR1_MODE_INTERNAL_ZERO_CALIBRATION | CURRENT_MODE_1_SETTINGS_CAL;
	send_data[1] = CURRENT_MODE_0_SETTINGS_CAL_ZERO | adc_channel;
	ret = ad7730_spi_writereg(CR_MODE_REGISTER, send_data, 2);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 internal zero scale calibration failed(%d)!\r\n", ret);
		return ret;
    }
#else
	/* -------------- System Zero Calibration  ----------------------- */
	send_data[0] = MR1_MODE_SYSTEM_ZERO_CALIBRATION | CURRENT_MODE_1_SETTINGS_CAL;
	send_data[1] = CURRENT_MODE_0_SETTINGS_CAL_ZERO | adc_channel;
	ret = ad7730_spi_writereg(CR_MODE_REGISTER, send_data, 2);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 internal zero scale calibration failed(%d)!\r\n", ret);
		return ret;
    }
#endif
	ret = ad7730_wait_rdy(dev, 5000); // wait for ready pin to go low after calibration
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 internal zero scale calibration wait rdy failed(%d)!\r\n", ret);
		return ret;
    }
	
	if (rt_pin_read(ad7730->rdy_pin) == PIN_LOW)
	{
		/* clear the rdy state */
		ad7730_single_read_data(dev);
	}
	
#if 0
	/* -------------- DAC Config ----------------------- */
	send_data[0] = (DACR_OFFSET_SIGN_POSITIVE | DACR_OFFSET_17P5MV); //set DAC to zero offset
	ret = ad7730_spi_writereg(CR_DAC_REGISTER, send_data, 1);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 dac config failed(%d)!\r\n", ret);
		return ret;
    }
#endif
	
    return RT_EOK;
}

/* ad7730 start single read */
static rt_err_t ad7730_start_single_read(rt_device_t dev, int adc_channel)
{
	AD7730_TRACE("ad7730_start_single_read() adc_channel=%d\r\n", adc_channel);
	
	if ((adc_channel < 0)
		|| (adc_channel >= 3))
	{
		AD7730_TRACE("ad7730_start_single_read() failed, invalid channel(%d)!\r\n", adc_channel);
		return -RT_ERROR;
	}
	
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	
	ad7730_lock(dev);
	
	if (AD7730_IDLE != ad7730->work_state)
	{
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730_start_single_read(%d) failed, busy in state(%d)!\r\n", adc_channel, ad7730->work_state);
		return -RT_ERROR;
	}
	
	ad7730->work_state = AD7730_SINGLE_READ;
	
	ad7730_unlock(dev);
	
	uint8_t send_data[3] = {0};
	
	// need to put AD7730 into single read mode before every read (returns to idle after every conversion)
	send_data[0] = MR1_MODE_SINGLE | CURRENT_MODE_1_SETTINGS_READ; //write to mode reg startin single readings for 0-10mV range
	send_data[1] = CURRENT_MODE_0_SETTINGS_READ | adc_channel;
	rt_err_t ret = ad7730_spi_writereg(CR_MODE_REGISTER, send_data, 2);
	if (RT_EOK != ret)
    {
		ad7730_lock(dev);
		ad7730->work_state = AD7730_IDLE;
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730 read set mode failed(%d)!\r\n", ret);
		return ret;
    }
	
    return RT_EOK;
}

/* ad7730 start continuous read */
static rt_err_t ad7730_start_cont_read(rt_device_t dev, int adc_channel)
{
	AD7730_TRACE("ad7730_start_cont_read() adc_channel=%d\r\n", adc_channel);
	
	if ((adc_channel < 0)
		|| (adc_channel >= 3))
	{
		AD7730_TRACE("ad7730_start_cont_read() failed, invalid channel(%d)!\r\n", adc_channel);
		return -RT_ERROR;
	}
	
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	struct rt_spi_device* spi_device = ad7730->spi_device;
	
	ad7730_lock(dev);
	
	if (AD7730_IDLE != ad7730->work_state)
	{
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730_start_cont_read(%d) failed, busy in state(%d)!\r\n", adc_channel, ad7730->work_state);
		return -RT_ERROR;
	}
	
	uint8_t send_data[2] = {0};
	
	send_data[0] = (MR1_MODE_CONTINUOUS | CURRENT_MODE_1_SETTINGS_READ);
	send_data[1] = CURRENT_MODE_0_SETTINGS_READ | adc_channel;
	rt_err_t ret = ad7730_spi_writereg(CR_MODE_REGISTER, send_data, 2);
	if (RT_EOK != ret)
    {
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730 set continuous read mode failed(%d)!\r\n", ret);
		return ret;
    }

	send_data[0] = (CR_CONTINUOUS_READ_START | CR_DATA_REGISTER);
	rt_size_t send_len = rt_spi_send(spi_device, send_data, 1);
	if (1 != send_len)
    {
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730 start continuous read failed(%d)!\r\n", send_len);
		return -RT_ERROR;
    }
	
	ad7730->work_state = AD7730_CONT_READ;
	
	ad7730_unlock(dev);
	
	return RT_EOK;
}

/* ad7730 stop continuous read */
static rt_err_t ad7730_stop_cont_read(rt_device_t dev)
{
	AD7730_TRACE("ad7730_stop_cont_read()\r\n");
	
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	struct rt_spi_device* spi_device = ad7730->spi_device;

	ad7730_lock(dev);
	
	if (AD7730_CONT_READ != ad7730->work_state)
	{
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730_stop_cont_read() waring, not in cont read state!\r\n");
		return RT_EOK;
	}
	
	uint8_t send_data[3] = {0};
	
	send_data[0] = (CR_SINGLE_WRITE | CR_CONTINUOUS_READ_STOP); //0x30
	rt_size_t send_len = rt_spi_send(spi_device, send_data, 1);
	if (1 != send_len)
    {
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730 stop continuous read failed(%d)!\r\n", send_len);
		return -RT_ERROR;
    }
	
	// need to put AD7730 into single read mode before every read (returns to idle after every conversion)
	send_data[0] = MR1_MODE_SINGLE | CURRENT_MODE_1_SETTINGS_READ; //write to mode reg startin single readings for 0-10mV range
	send_data[1] = CURRENT_MODE_0_SETTINGS_READ;
	rt_err_t ret = ad7730_spi_writereg(CR_MODE_REGISTER, send_data, 2);
	if (RT_EOK != ret)
    {
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730 stop continuous read set mode failed(%d)!\r\n", ret);
		return ret;
    }
	
	ad7730->work_state = AD7730_IDLE;
	
	ad7730_unlock(dev);
	
	return RT_EOK;
}

/* ad7730 rdy interupt service */
static void ad7730_rdy_isr(void *args)
{
	struct ad7730_device* ad7730 = (struct ad7730_device*)args;
	
	/* invoke callback */
	if (ad7730->parent.rx_indicate != RT_NULL)
	{
		ad7730->parent.rx_indicate(&ad7730->parent, 4);
	}
}

/* dump useful register contents */
static rt_err_t ad7730_dump_reg(rt_device_t dev)
{
	AD7730_TRACE("ad7730_dump_reg()\r\n");
	
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	uint8_t recv_buf[4] = {0};
	rt_err_t ret = RT_EOK;

	ad7730_lock(dev);
	
	if (AD7730_IDLE != ad7730->work_state)
	{
		ad7730_unlock(dev);
		AD7730_TRACE("ad7730_dump_reg() failed, busy in state(%d)!\r\n", ad7730->work_state);
		return -RT_ERROR;
	}
	
	//#define CR_COMMUNICATION_REGISTER 0x00 // Communications Register (Write Operation) 8Bits
	
	//#define CR_STATUS_REGISTER 0x00 // Status Register (Read Operation) 8Bits
	ret = ad7730_spi_readreg(CR_STATUS_REGISTER, recv_buf, 1);
	if (RT_EOK != ret)
    {
		rt_kprintf("read CR_STATUS_REGISTER failed!\r\n");
		return ret;
    }
	rt_kprintf("CR_STATUS_REGISTER=0x%x\r\n", recv_buf[0]);
	
	//#define CR_DATA_REGISTER 0x01 // Data Register 16/24bit(WL=1)
	ret = ad7730_spi_readreg(CR_DATA_REGISTER, recv_buf, 3);
	if (RT_EOK != ret)
    {
		rt_kprintf("read CR_DATA_REGISTER failed!\r\n");
		return ret;
    }
	rt_kprintf("CR_DATA_REGISTER=0x%x 0x%x 0x%x\r\n", recv_buf[0], recv_buf[1], recv_buf[2]);
	
	//#define CR_MODE_REGISTER 0x02 // Mode Register 16bit
	ret = ad7730_spi_readreg(CR_MODE_REGISTER, recv_buf, 2);
	if (RT_EOK != ret)
    {
		rt_kprintf("read CR_MODE_REGISTER failed!\r\n");
		return ret;
    }
	rt_kprintf("CR_MODE_REGISTER=0x%x 0x%x\r\n", recv_buf[0], recv_buf[1]);
	
	//#define CR_FILTER_REGISTER 0x03 // Filter Register 24bit
	ret = ad7730_spi_readreg(CR_FILTER_REGISTER, recv_buf, 3);
	if (RT_EOK != ret)
    {
		rt_kprintf("read CR_FILTER_REGISTER failed!\r\n");
		return ret;
    }
	rt_kprintf("CR_FILTER_REGISTER=0x%x 0x%x 0x%x\r\n", recv_buf[0], recv_buf[1], recv_buf[2]);
	
	//#define CR_DAC_REGISTER 0x04 // DAC Register 8bit
	ret = ad7730_spi_readreg(CR_DAC_REGISTER, recv_buf, 1);
	if (RT_EOK != ret)
    {
		rt_kprintf("read CR_DAC_REGISTER failed!\r\n");
		return ret;
    }
	rt_kprintf("CR_DAC_REGISTER=0x%x\r\n", recv_buf[0]);
	
	//#define CR_OFFSET_REGISTER 0x05 // Offset Register 24bit
	ret = ad7730_spi_readreg(CR_FILTER_REGISTER, recv_buf, 3);
	if (RT_EOK != ret)
    {
		rt_kprintf("read CR_OFFSET_REGISTER failed!\r\n");
		return ret;
    }
	rt_kprintf("CR_OFFSET_REGISTER=0x%x 0x%x 0x%x\r\n", recv_buf[0], recv_buf[1], recv_buf[2]);
	
	//#define CR_GAIN_REGISTER 0x06 // Gain Register 24bit
	ret = ad7730_spi_readreg(CR_GAIN_REGISTER, recv_buf, 3);
	if (RT_EOK != ret)
    {
		rt_kprintf("read CR_GAIN_REGISTER failed!\r\n");
		return ret;
    }
	rt_kprintf("CR_GAIN_REGISTER=0x%x 0x%x 0x%x\r\n", recv_buf[0], recv_buf[1], recv_buf[2]);
	
	//#define CR_TEST_REGISTER 0x07 // Test Register 24bit
	ret = ad7730_spi_readreg(CR_TEST_REGISTER, recv_buf, 3);
	if (RT_EOK != ret)
    {
		rt_kprintf("read CR_TEST_REGISTER failed!\r\n");
		return ret;
    }
	rt_kprintf("CR_TEST_REGISTER=0x%x 0x%x 0x%x\r\n", recv_buf[0], recv_buf[1], recv_buf[2]);
	
	ad7730_unlock(dev);
	
	return RT_EOK;
}

/* initialize the interface */
static rt_err_t ad7730_init(rt_device_t dev)
{
	// TODO
    return RT_EOK;
}

/* control the interface */
static rt_err_t ad7730_control(rt_device_t dev, int cmd, void *args)
{
	AD7730_TRACE("ad7730_control() cmd=0x%x\r\n", cmd);
	
	rt_err_t ret = RT_EOK;
	
    switch (cmd)
    {
		case AD7730_DUMP_REG: // dump useful register contents
		{
			ret = ad7730_dump_reg(dev);
			if (RT_EOK != ret)
			{
				AD7730_TRACE("ad7730_control() failed, ad7730_dump_reg error(%d)!\r\n", ret);
			}
			break;
		}
		case AD7730_START_CONT_READ: // start continuous read
		{
			ret = ad7730_start_cont_read(dev, (int)args);
			if (RT_EOK != ret)
			{
				AD7730_TRACE("ad7730_control() failed, ad7730_start_cont_read error(%d)!\r\n", ret);
			}
			break;
		}
		case AD7730_STOP_CONT_READ: // stop continuous read
		{
			ret = ad7730_stop_cont_read(dev);
			if (RT_EOK != ret)
			{
				AD7730_TRACE("ad7730_control() failed, ad7730_stop_cont_read error(%d)!\r\n", ret);
			}
			break;
		}
		case AD7730_START_SINGLE_READ: // start single read
		{
			ret = ad7730_start_single_read(dev, (int)args);
			if (RT_EOK != ret)
			{
				AD7730_TRACE("ad7730_control() failed, ad7730_start_single_read error(%d)!\r\n", ret);
			}
			break;
		}
		case AD7730_DO_CALIBRATION:
		{
			ret = ad7730_calibration(dev, (int)args);
			if (RT_EOK != ret)
			{
				AD7730_TRACE("ad7730_control() failed, ad7730_calibration error(%d)!\r\n", ret);
			}
			break;
		}
		default:
		{
			ret = -RT_ERROR;
			AD7730_TRACE("ad7730_control() failed, unsupported cmd(0x%x)!\r\n", cmd);
			break;
		}
    }

    return ret;
}

/* Open the ethernet interface */
static rt_err_t ad7730_open(rt_device_t dev, uint16_t oflag)
{
	AD7730_TRACE("ad7730_open() oflag=0x%x\r\n", oflag);
	
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	
	rt_pin_write(ad7730->ref_sleep_pin, PIN_HIGH);
	rt_thread_mdelay(1);
	
	rt_pin_write(ad7730->standby_pin, PIN_HIGH);
	rt_thread_mdelay(1);
	
	rt_pin_write(ad7730->reset_pin, PIN_HIGH);
	rt_thread_mdelay(1);
	
	ad7730->work_state = AD7730_IDLE;
	
	rt_err_t ret = ad7730_config(dev);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 open config failed(%d)!\r\n", ret);
		return ret;
    }
	
	ret = ad7730_calibration(dev, 0);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 open calibration(0) failed(%d)!\r\n", ret);
		return ret;
    }
	
	ret = ad7730_calibration(dev, 1);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 open calibration(1) failed(%d)!\r\n", ret);
		return ret;
    }
	
	ret = ad7730_calibration(dev, 2);
	if (RT_EOK != ret)
    {
		AD7730_TRACE("ad7730 open calibration(2) failed(%d)!\r\n", ret);
		return ret;
    }
	
	ret = rt_pin_attach_irq(ad7730->rdy_pin, PIN_IRQ_MODE_FALLING, ad7730_rdy_isr, ad7730);
	if (RT_EOK != ret)
	{
		AD7730_TRACE("ad7730 attach rdy irq failed(%d)!\r\n", ret);
		return ret;
	}
	
	ret = rt_pin_irq_enable(ad7730->rdy_pin, PIN_IRQ_ENABLE);
	if (RT_EOK != ret)
	{
		AD7730_TRACE("ad7730 enable rdy irq failed(%d)!\r\n", ret);
		return ret;
	}
	
    return RT_EOK;
}

/* Close the interface */
static rt_err_t ad7730_close(rt_device_t dev)
{
	AD7730_TRACE("ad7730_close()\r\n");
	
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	
	ad7730_lock(dev);
	
	rt_pin_irq_enable(ad7730->rdy_pin, PIN_IRQ_DISABLE);
	
	rt_pin_detach_irq(ad7730->rdy_pin);
	
	if (AD7730_CONT_READ == ad7730->work_state)
	{
		ad7730_stop_cont_read(dev);
	}
	
	rt_pin_write(ad7730->standby_pin, PIN_LOW);
	
	rt_pin_write(ad7730->ref_sleep_pin, PIN_LOW);
	
	rt_pin_write(ad7730->reset_pin, PIN_LOW);
	
	ad7730->work_state = AD7730_IDLE;
	
	ad7730_unlock(dev);
	
    return RT_EOK;
}

/* Read */
static rt_size_t ad7730_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	if (size < 4)
	{
		AD7730_TRACE("ad7730 read data buffer size must >= 4!\r\n");
		return 0;
	}
	
	struct ad7730_device* ad7730 = (struct ad7730_device*)dev;
	
	uint32_t ad7730_val = 0;
	
	ad7730_lock(dev);
	
	switch (ad7730->work_state)
	{
		case AD7730_IDLE:
			ad7730_val = ad7730_single_read_data(dev);
			break;
		case AD7730_SINGLE_READ:
			ad7730->work_state = AD7730_IDLE;
			ad7730_val = ad7730_single_read_data(dev);
			break;
		case AD7730_CONT_READ:
			ad7730_val = ad7730_cont_read_data(dev);
			break;
	}
	
	ad7730_unlock(dev);
	
	rt_memcpy(buffer, &ad7730_val, 4);
	
    return 4;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops ad7730_ops = 
{
    ad7730_init,
    ad7730_open,
    ad7730_close,
    ad7730_read,
    RT_NULL,
    ad7730_control
};
#endif

int ad7730_hw_init(void)
{
    AD7730_TRACE("ad7730_hw_init()\r\n");
	
	rt_err_t ret = rt_hw_spi_device_attach(AD7730_SPI_BUS_NAME, AD7730_SPI_DEVICE_NAME, GPIOB, GPIO_PIN_12);
    if (RT_EOK != ret)
    {
		AD7730_TRACE("spi bus %s attach failed!\r\n", AD7730_SPI_BUS_NAME);
		return ret;
    }
		
	struct rt_spi_device* spi_device = (struct rt_spi_device *)rt_device_find(AD7730_SPI_DEVICE_NAME);
    if (RT_NULL == spi_device)
    {
		AD7730_TRACE("spi device %s not found!\r\n", AD7730_SPI_DEVICE_NAME);
		return -RT_ERROR;
    }

    /* config spi */
    {
		struct rt_spi_configuration cfg = {0};
		cfg.data_width = 8;
		cfg.mode = RT_SPI_MODE_1 | RT_SPI_MSB; /* SPI Compatible Modes 1 (CPOL = 0, CPHA = 1) */
		cfg.max_hz = 5 * 1000 * 1000; /* SPI Interface with Clock Speeds Up to 5 MHz */
		ret = rt_spi_configure(spi_device, &cfg);
		if (RT_EOK != ret)
		{
			AD7730_TRACE("spi bus %s config failed!\r\n", AD7730_SPI_BUS_NAME);
			return ret;
		}
    } /* config spi */
		
	/* attach spi device */
	ad7730_dev.spi_device = spi_device;
		
		/* init rt-thread device struct */
    ad7730_dev.parent.type    = RT_Device_Class_Miscellaneous;
#ifdef RT_USING_DEVICE_OPS
    ad7730_dev.parent.ops     = &ad7730_ops;
#else
    ad7730_dev.parent.init    = ad7730_init;
    ad7730_dev.parent.open    = ad7730_open;
    ad7730_dev.parent.close   = ad7730_close;
    ad7730_dev.parent.read    = ad7730_read;
    ad7730_dev.parent.write   = RT_NULL;
    ad7730_dev.parent.control = ad7730_control;
#endif
	
	/* set RDY pin mode to input */
    rt_pin_mode(AD7730_RDY_PIN, PIN_MODE_INPUT_PULLUP);
	ad7730_dev.rdy_pin = AD7730_RDY_PIN;
	
	/* set STANDBY pin mode to output */
	rt_pin_write(AD7730_STANDBY_PIN, PIN_LOW);
    rt_pin_mode(AD7730_STANDBY_PIN, PIN_MODE_OUTPUT);
	ad7730_dev.standby_pin = AD7730_STANDBY_PIN;
	
	/* set RESET pin mode to output */
	rt_pin_write(AD7730_RESET_PIN, PIN_LOW);
    rt_pin_mode(AD7730_RESET_PIN, PIN_MODE_OUTPUT);
	ad7730_dev.reset_pin = AD7730_RESET_PIN;
	
	/* set REF_SLEEP pin mode to output */
	rt_pin_write(AD7730_REF_SLEEP_PIN, PIN_LOW);
    rt_pin_mode(AD7730_REF_SLEEP_PIN, PIN_MODE_OUTPUT);
	ad7730_dev.ref_sleep_pin = AD7730_REF_SLEEP_PIN;
	
	/* work state */
	ad7730_dev.work_state = AD7730_IDLE;
	
	/* init lock */
	rt_mutex_init(&(ad7730_dev.lock), "ad7730", RT_IPC_FLAG_FIFO);
	
	/* register a character device */
    ret = rt_device_register(&(ad7730_dev.parent), AD7730_DEVICE_NAME, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_INT_RX);
	if (RT_EOK != ret)
    {
        AD7730_TRACE("device %s register failed!\r\n", AD7730_DEVICE_NAME);
		return ret;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(ad7730_hw_init);

#endif /* BSP_USING_AD7730 */
