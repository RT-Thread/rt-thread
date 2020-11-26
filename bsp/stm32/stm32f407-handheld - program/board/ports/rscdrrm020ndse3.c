/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-06-30     wangk        add rscdrrm020ndse3 driver
 */

#include <rtthread.h>
#include <stdbool.h>
#include "drv_spi.h"
#include "rscdrrm020ndse3.h"
#include "Pressure_Comp.h"
#include "board_config.h"

#if defined(BSP_USING_RSCDRRM020NDSE3)

#define RSCDRRM020NDSE3_DEBUG

#ifdef RSCDRRM020NDSE3_DEBUG
    #define RSCDRRM020NDSE3_TRACE	rt_kprintf
#else
    #define RSCDRRM020NDSE3_TRACE(...)
#endif /* RSCDRRM020NDSE3_DEBUG */

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

/* SPI总线名 */
#define RSCDRRM020NDSE3_SPI_BUS_NAME "spi2"
/* EEPROM SPI设备名 */
#define RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME "spi20"
/* ADC SPI设备名 */
#define RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME "spi21"
/* PIN Define in board_config.h */

/* 传感器EEPROM大小(字节数) */
#define RSCDRRM020NDSE3_EEPROM_SIZE		(452)

/* ADC采集模式 */
#define RSCDRRM020NDSE3_ADC_NORMAL 0x00
#define RSCDRRM020NDSE3_ADC_FAST 0x10

/* ADC采集频率(Normal模式下) */
#define RSCDRRM020NDSE3_ADC_20HZ 0x00
#define RSCDRRM020NDSE3_ADC_45HZ 0x20
#define RSCDRRM020NDSE3_ADC_90HZ 0x40
#define RSCDRRM020NDSE3_ADC_175HZ 0x60
#define RSCDRRM020NDSE3_ADC_330HZ 0x80
#define RSCDRRM020NDSE3_ADC_600HZ 0xA0
#define RSCDRRM020NDSE3_ADC_1000HZ 0xC0
/* ADC采集频率(FAST模式下翻倍) */

/* ADC采集类型 */
#define RSCDRRM020NDSE3_ADC_TEMPERATURE 0x06 // 温度
#define RSCDRRM020NDSE3_ADC_PRESSURE 0x04 // 压力

/* ADC默认采样率配置 */
#define RSCDRRM020NDSE3_ADC_DEFAUT_FREQ_INDEX 6 // 默认采样率索引,6=330HZ(实际温度采集会占用少量周期)
#define RSCDRRM020NDSE3_ADC_DEFAUT_FREQ 330 // 默认采样率实际值

/* ADC温度采集周期(ms) */
#define RSCDRRM020NDSE3_ADC_TEMP_INTERVAL 100

/* EVENT定义 */
#define RSCDRRM020NDSE3_EVENT_DATA_READY 0x00000001

#define rscdrrm020ndse3_lock(dev)      rt_mutex_take(&((struct rscdrrm020ndse3_device*)dev)->lock, RT_WAITING_FOREVER);
#define rscdrrm020ndse3_unlock(dev)    rt_mutex_release(&((struct rscdrrm020ndse3_device*)dev)->lock);

/* 传感器设备对象 */
static struct rscdrrm020ndse3_device rscdrrm020ndse3_dev;

/* 传感器设备线程 */
static struct rt_thread* rscdrrm020ndse3_thread = RT_NULL;

static rt_event_t rscdrrm020ndse3_event = RT_NULL;

/* 滤波器相关变量(用于自动归零) */
static uint32_t rscdrrm020ndse3_filter_min_val = 0xFFFFFFFF; // 样本中的最小值
static uint32_t rscdrrm020ndse3_filter_max_val = 0; // 样本中的最大值
static uint32_t rscdrrm020ndse3_filter_sum = 0; // 样本累加和(用于计算均值)
static uint32_t rscdrrm020ndse3_filter_sample_cnt = 0; // 当前已采集的样本数
static uint32_t rscdrrm020ndse3_filter_n = (10 * RSCDRRM020NDSE3_ADC_DEFAUT_FREQ_INDEX + 10); // 总共需要的采集次数

/* 自动归零完成回调函数 */
static ATUO_ZERO_CPL_FUNC s_pfnAutoZeroCompleted = NULL;

/* 控制连续采集压力的次数(连续采集之间会插入温度采集) */
static uint32_t pressure_continuous_cnt = 0; // 当前已连续采集次数
static uint32_t pressure_continuous_n = ((RSCDRRM020NDSE3_ADC_TEMP_INTERVAL * RSCDRRM020NDSE3_ADC_DEFAUT_FREQ) / 1000); // 连续采集压力的总次数

/* 工作模式频率表(通过下标索引) */
typedef struct
{
	uint8_t mode; // 工作模式
	uint8_t freq_cfg; // 采样率(配置值)
	uint16_t freq_val; // 采样率(实际值)
} WorkModeFreq_T;
static WorkModeFreq_T s_tModeFreqTbl[] = {
	{RSCDRRM020NDSE3_ADC_NORMAL, RSCDRRM020NDSE3_ADC_20HZ, 20}, 	// 0=20HZ
	{RSCDRRM020NDSE3_ADC_FAST, RSCDRRM020NDSE3_ADC_20HZ, 40}, 		// 1=40HZ
	{RSCDRRM020NDSE3_ADC_NORMAL, RSCDRRM020NDSE3_ADC_45HZ, 45}, 	// 2=45HZ 
	{RSCDRRM020NDSE3_ADC_NORMAL, RSCDRRM020NDSE3_ADC_90HZ, 90}, 	// 3=90HZ // {RSCDRRM020NDSE3_ADC_FAST, RSCDRRM020NDSE3_ADC_45HZ},
	{RSCDRRM020NDSE3_ADC_NORMAL, RSCDRRM020NDSE3_ADC_175HZ, 175},	// 4=175HZ
	{RSCDRRM020NDSE3_ADC_FAST, RSCDRRM020NDSE3_ADC_90HZ, 180}, 		// 5=180HZ
	{RSCDRRM020NDSE3_ADC_NORMAL, RSCDRRM020NDSE3_ADC_330HZ, 330}, 	// 6=330HZ
	{RSCDRRM020NDSE3_ADC_FAST, RSCDRRM020NDSE3_ADC_175HZ, 350}, 	// 7=350HZ
	{RSCDRRM020NDSE3_ADC_NORMAL, RSCDRRM020NDSE3_ADC_600HZ, 600}, 	// 8=600HZ
	{RSCDRRM020NDSE3_ADC_FAST, RSCDRRM020NDSE3_ADC_330HZ, 660}, 	// 9=660HZ
	{RSCDRRM020NDSE3_ADC_NORMAL, RSCDRRM020NDSE3_ADC_1000HZ, 1000}, // 10=1000HZ
	{RSCDRRM020NDSE3_ADC_FAST, RSCDRRM020NDSE3_ADC_600HZ, 1200}, 	// 11=1200HZ
	{RSCDRRM020NDSE3_ADC_FAST, RSCDRRM020NDSE3_ADC_1000HZ, 2000}, 	// 12=2000HZ
};

/* 开启传感器电源 */
static void rscdrrm020ndse3_power_on(rt_device_t dev)
{
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_power_on()\r\n");
	
	/* 开启传感器电源 */
	rt_pin_write(RSCDRRM020NDSE3_PWER_EN_PIN, PIN_HIGH);
	
	/* 等待传感器启动完毕 */
	rt_thread_mdelay(1);
}

/* 关闭传感器电源 */
static void rscdrrm020ndse3_power_off(rt_device_t dev)
{
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_power_off()\r\n");
	
	/* 关闭传感器电源 */
	rt_pin_write(RSCDRRM020NDSE3_PWER_EN_PIN, PIN_LOW);
}

/* 读取EEPROM中的指定地址、指定长度的数据 */
static rt_err_t rscdrrm020ndse3_spi_read_eeprom(uint16_t address, uint8_t* recv_buf, rt_size_t buf_len)
{
	struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_ee_device;
	
	uint8_t send_buf[2] = {0};
	/* 
		To read from memory, the host sends an EAD_EEPROM instruction[0000 X011] followed by an 8-bit address. 
		The ‘X’ bit in the read instruction is the ninth (MSB) address bit.
	*/
	if (address & 0x0100)
	{ // ninth (MSB) address bit is 1
		send_buf[0] = 0x0B; // EAD_EEPROM
	}
	else
	{ // ninth (MSB) address bit is 0
		send_buf[0] = 0x03; // EAD_EEPROM
	}
	send_buf[1] = (uint8_t)(address & 0x00FF); // ADDRESS

    return rt_spi_send_then_recv(spi_device, send_buf, sizeof(send_buf), recv_buf, buf_len);
}

/* 发送ADC命令 */
static rt_err_t rscdrrm020ndse3_spi_send_adc_cmd(uint8_t cmd)
{
	struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_adc_device;
	
    rt_size_t ret = rt_spi_send(spi_device, &cmd, 1);
	if (1 != ret)
	{
		return rt_get_errno();
	}
	
	return RT_EOK;
}

/* 写入ADC寄存器 */
static rt_err_t rscdrrm020ndse3_spi_write_adc_reg(uint8_t reg, const uint8_t* send_data, rt_size_t data_len)
{
	struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_adc_device;
	
	/*
		To program a configuration register, the host sends a WREG command [0100 RRNN], 
		where ‘RR’ is the register number and ‘NN’ is the number of bytes to be written –1.
	*/
	uint8_t send_buf[1] = {0};
	send_buf[0] = 0x40 | ((reg & 0x03) << 2) | ((data_len - 1) & 0x03);

    return rt_spi_send_then_send(spi_device, send_buf, sizeof(send_buf), send_data, data_len);
}

/* 读取ADC寄存器 */
static rt_err_t rscdrrm020ndse3_spi_read_adc_reg(uint8_t reg, uint8_t* recv_buf, rt_size_t buf_len)
{
	struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_adc_device;
	
	/*
		RREG (0010 rrnn), 
		where ‘RR’ is the register number and ‘NN’ is the number of bytes to be read –1.
	*/
	uint8_t send_buf[1] = {0};
	send_buf[0] = 0x20 | ((reg & 0x03) << 2) | ((buf_len - 1) & 0x03);

    return rt_spi_send_then_recv(spi_device, send_buf, sizeof(send_buf), recv_buf, buf_len);
}

static rt_err_t rscdrrm020ndse3_spi_adc_transfer(const uint8_t* send_data, uint8_t* recv_buf, rt_size_t length)
{
	struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_adc_device;
	
	rt_size_t ret = rt_spi_transfer(spi_device, send_data, recv_buf, length);
	if (length != ret)
	{
		return rt_get_errno();
	}

	return RT_EOK;
}

/* rscdrrm020ndse3 rdy interupt service */
static void rscdrrm020ndse3_rdy_isr(void *args)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)args;
	
	/* 状态检查 */
	if(!rscdrrm020ndse3->start)
	{
		return;
	}
	
	/* 通知传感器线程处理数据读取 */
	rt_event_send(rscdrrm020ndse3_event, RSCDRRM020NDSE3_EVENT_DATA_READY);
}

/* 启动传感器数据采集 */
static rt_err_t rscdrrm020ndse3_start(rt_device_t dev)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_start()\r\n");
	
	rscdrrm020ndse3_lock(dev);
	
	/* 状态检查 */
	if (rscdrrm020ndse3->start)
	{ // 已启动
		rscdrrm020ndse3_unlock(dev);
		return RT_EOK;
	}
	
	rscdrrm020ndse3_unlock(dev);
	
	/*
		The ADC reset command RESET [0000 0110] resets the ADC to the default values.
	*/
	rt_err_t ret = rscdrrm020ndse3_spi_send_adc_cmd(0x06);
	if (RT_EOK != ret)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_send_adc_cmd(0x06) failed, error(%d)!\r\n", ret);
		goto _EXIT;
	}
	
	/*
		Resets the device to the default values. 
		Wait at least (50 μs + 32 · t(CLK)) after the RESET command is sent before sending any other command.
	*/
	//while (PIN_LOW != rt_pin_read(RSCDRRM020NDSE3_RDY_PIN))
	{
		rt_thread_mdelay(1);
	}
	
	/*
		配置ADC参数
		Initialize all four configuration registers to the default values in the EEPROM’s Relative addresses 61, 63, 65 and 67 
		by sending a WREG command to address 0
	*/
	ret = rscdrrm020ndse3_spi_write_adc_reg(0x00, rscdrrm020ndse3->adc_cfg_param, sizeof(rscdrrm020ndse3->adc_cfg_param));
	if (RT_EOK != ret)
    {
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_write_adc_reg(0, adc_cfg_param) failed, error(%d)!\r\n", ret);
		goto _EXIT;
    }
	
	/* 读取配置寄存器进行验证 */
	{ // 消除编译警告
		uint8_t cfg_regs[4] = {0};
		ret = rscdrrm020ndse3_spi_read_adc_reg(0x00, cfg_regs, sizeof(cfg_regs));
		if (RT_EOK != ret)
		{
			RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_read_adc_reg(0x00) failed, error(%d)!\r\n", ret);
			goto _EXIT;
		}
	}
	
	/*
		先配置ADC为温度采集模式并配置采样率
		Configure the sensor to temperature mode and the desired data rate by setting configuration register 1 by sending a WREG
		command to address 1, [0100 0100] followed by the single configuration byte. Bit 1 (TS) of the configuration register should
		be set to 1.
	*/
	{ // 消除编译警告
		//const WorkModeFreq_T* pctWorkModeFreq = &(s_tModeFreqTbl[rscdrrm020ndse3->freq_index]);
		//uint8_t mode = RSCDRRM020NDSE3_ADC_TEMPERATURE | pctWorkModeFreq->freq_cfg | pctWorkModeFreq->mode;
		uint8_t mode = RSCDRRM020NDSE3_ADC_TEMPERATURE | RSCDRRM020NDSE3_ADC_1000HZ | RSCDRRM020NDSE3_ADC_FAST; // 用最快速度采集温度,避免过度干扰压力采集时序
		ret = rscdrrm020ndse3_spi_write_adc_reg(0x01, &mode, 1);
		if (RT_EOK != ret)
		{
			RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_write_adc_reg(0x01) failed, error(%d)!\r\n", ret);
			goto _EXIT;
		}
	}
	
	/*
		Send 08h command to start data conversion on ADC.
	*/
	ret = rscdrrm020ndse3_spi_send_adc_cmd(0x08);
	if (RT_EOK != ret)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_send_adc_cmd(0x08) failed, error(%d)!\r\n", ret);
		goto _EXIT;
	}
	
	/*
		the START/SYNC command must be issued one time to start converting continuously. 
		Sending the START/SYNC command while converting in continuous conversion mode resets the
		digital filter and restarts continuous conversions
	*/

	/* 使能传感器数据READY中断检测 */
	ret = rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_ENABLE);
	if (RT_EOK != ret)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() call rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN) failed, error(%d)!\r\n", ret);
		goto _EXIT;
	}
	
	rscdrrm020ndse3_lock(dev);
	
	/* 清除结果 */
	rscdrrm020ndse3->pressure_comp = 0.0;
	rscdrrm020ndse3->temperature = 0;
	
	/* 复位压力连续采集次数 */
	pressure_continuous_cnt = 0;
	
	/* 当前为温度采集模式 */
	rscdrrm020ndse3->mode = RSCDRRM020NDSE3_TEMPERATURE;
	
	/* 进入启动状态 */
	rscdrrm020ndse3->start = true;
	
	rscdrrm020ndse3_unlock(dev);
	
_EXIT:
	return ret;
}

/* 停止传感器数据采集 */
static rt_err_t rscdrrm020ndse3_stop(rt_device_t dev)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_stop()\r\n");
	
	rscdrrm020ndse3_lock(dev);
	
	/* 状态检查 */
	if (!rscdrrm020ndse3->start)
	{ // 已停止
		rscdrrm020ndse3_unlock(dev);
		return RT_EOK;
	}
	
	rscdrrm020ndse3_unlock(dev);
	
	/*
		The ADC reset command RESET [0000 0110] resets the ADC to the default values.
	*/
	rt_err_t ret = rscdrrm020ndse3_spi_send_adc_cmd(0x06);
	if (RT_EOK != ret)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_stop() call rscdrrm020ndse3_spi_send_adc_cmd(0x06) failed, error(%d)!\r\n", ret);
		goto _EXIT;
	}
	
	/* 停止传感器数据READY中断检测 */
	ret = rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE);
	if (RT_EOK != ret)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_stop() call rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE) failed, error(%d)!\r\n", ret);
		goto _EXIT;
	}
	
	rscdrrm020ndse3_lock(dev);
	
	/* 进入停止状态 */
	rscdrrm020ndse3->start = false;
	
	/* 清除结果 */
	rscdrrm020ndse3->pressure_comp = 0.0;
	rscdrrm020ndse3->temperature = 0;
	
	/* 复位压力连续采集次数 */
	pressure_continuous_cnt = 0;
	
	rscdrrm020ndse3_unlock(dev);
	
_EXIT:
	return ret;
}

/* 自动归零 */
static rt_err_t rscdrrm020ndse3_auto_zero(rt_device_t dev, ATUO_ZERO_CPL_FUNC pfnAutoZeroCompleted)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_auto_zero()\r\n");
	
	rscdrrm020ndse3_lock(dev);
	
	/* 状态检查 */
	if (!rscdrrm020ndse3->start)
	{ // 未启动
		rscdrrm020ndse3_unlock(dev);
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_auto_zero() failed, not in start state!\r\n");
		return -RT_ERROR;
	}
	if (rscdrrm020ndse3->auto_zero)
	{ // 正在执行自动归零
		rscdrrm020ndse3_unlock(dev);
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_auto_zero() failed, auto zero already in process!\r\n");
		return -RT_ERROR;
	}
	
	/* 初始化滤波器变量 */
	rscdrrm020ndse3_filter_sum = 0;
	rscdrrm020ndse3_filter_sample_cnt = 0;
	rscdrrm020ndse3_filter_min_val = 0xFFFFFFFF;
	rscdrrm020ndse3_filter_max_val = 0;
	
	/* 设置自动归零请求标志 */
	rscdrrm020ndse3->auto_zero = true;
	
	/* 安装完成回调函数 */
	s_pfnAutoZeroCompleted = pfnAutoZeroCompleted;
	
	rscdrrm020ndse3_unlock(dev);
	
	return RT_EOK;
}

/* 设置采样率 */
static rt_err_t rscdrrm020ndse3_set_freq(rt_device_t dev, uint32_t u32FreqIndex)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_set_freq() u32FreqIndex=%u\r\n", u32FreqIndex);
	
	/* 参数范围检查 */
	if (u32FreqIndex >= ARRAY_SIZE(s_tModeFreqTbl))
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_set_freq() failed, freq_index must < (%u)!\r\n", ARRAY_SIZE(s_tModeFreqTbl));
		return -RT_ERROR;
	}
	
	rscdrrm020ndse3_lock(dev);
	
	/* 更新采样率配置 */
	rscdrrm020ndse3->freq_index = u32FreqIndex;
	
	/* 由于采样率变化,需要重新计算滤波器总共需要的采集次数(用于自动归零) */
	rscdrrm020ndse3_filter_n = (10 * u32FreqIndex + 10);
	
	/* 由于采样率变化,需要重新计算压力值连续采集总次数(确保温度采集约100ms进行一次) */
	const WorkModeFreq_T* pctWorkModeFreq = &(s_tModeFreqTbl[u32FreqIndex]);
	pressure_continuous_n = ((RSCDRRM020NDSE3_ADC_TEMP_INTERVAL * pctWorkModeFreq->freq_val) / 1000); // (RSCDRRM020NDSE3_ADC_TEMP_INTERVAL / (1000 / pctWorkModeFreq->freq_val))
	
	rscdrrm020ndse3_unlock(dev);
	
	return RT_EOK;
}

/* 读取采样率 */
static rt_err_t rscdrrm020ndse3_get_freq(rt_device_t dev, uint32_t* pu32FreqIndex)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_get_freq() pu32FreqIndex=0x%x\r\n", pu32FreqIndex);
	
	//rscdrrm020ndse3_lock(dev);
	if (pu32FreqIndex)
	{
		*pu32FreqIndex = rscdrrm020ndse3->freq_index;
	}
	
	//rscdrrm020ndse3_unlock(dev);
	
	return RT_EOK;
}

/* 读取采样率 */
static rt_err_t rscdrrm020ndse3_get_temperature(rt_device_t dev, float* pfTemperature)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_get_temperature() pfTemperature=0x%x\r\n", pfTemperature);
	
	//rscdrrm020ndse3_lock(dev);
	if (pfTemperature)
	{
		/*
			To convert the digital value to a Celsius temperature, first check if the MSB is 0 or 1. 
			If the MSB = 0, simply multiply the decimal code by 0.03125°C to obtain the result. 
			If the MSB = 1, subtract 1 from the result and complement all bits, multiply the result by -0.03125°C.
		*/
		int temperature = (int)((rscdrrm020ndse3->temperature & 0x00002000) ? (rscdrrm020ndse3->temperature | 0xFFFFC000) : rscdrrm020ndse3->temperature); // 14 bits
		*pfTemperature = (float)temperature * 0.03125f;
	}
	
	//rscdrrm020ndse3_unlock(dev);
	
	return RT_EOK;
}

/* 取得即将切换到的采集模式(封装压力/温度交替采集策略) */
static enum rscdrrm020ndse3_mode rscdrrm020ndse3_next_mode(struct rscdrrm020ndse3_device* rscdrrm020ndse3)
{
	enum rscdrrm020ndse3_mode next_mode = RSCDRRM020NDSE3_PRESSURE;
	
	if (RSCDRRM020NDSE3_PRESSURE == rscdrrm020ndse3->mode) // pressure
	{ // 当前为压力采集模式
		if (pressure_continuous_cnt < pressure_continuous_n)
		{ // 还没有达到连续采集次数
			/* 连续压力采集 */
			next_mode = RSCDRRM020NDSE3_PRESSURE;
			/* 递增计数器 */
			++pressure_continuous_cnt;
		}
		else
		{ // 达到连续采集次数
			/* 切换到温度采集 */
			next_mode = RSCDRRM020NDSE3_TEMPERATURE;
		}
	}
	else //if (RSCDRRM020NDSE3_TEMPERATURE == rscdrrm020ndse3->mode) // temperature
	{ // 当前为温度采集模式
		/* 切换到压力采集模式 */
		next_mode = RSCDRRM020NDSE3_PRESSURE;
		/* 复位计数器 */
		pressure_continuous_cnt = 0;
	}
	
	return next_mode;
}

/* 传感器线程 */
static void rscdrrm020ndse3_thread_entry(void* param)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)param;
	/* 当前采集的压力值(未补偿) */
	uint32_t pressure = 0;
	/* 当前采集的温度值 */
	uint32_t temperature = 0;
	
	/* 进入事件循环 */
    while (1)
	{
		
		rt_uint32_t event_recved = 0;
		rt_err_t ret = rt_event_recv(rscdrrm020ndse3_event, RSCDRRM020NDSE3_EVENT_DATA_READY,
						  (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
						  RT_WAITING_FOREVER, &event_recved);
		if (RT_EOK != ret)
		{
			RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_thread_entry() rt_event_recv(rscdrrm020ndse3_event) failed, error(%d)!\r\n", ret);
			break;
		}
		
		rscdrrm020ndse3_lock(rscdrrm020ndse3);
		
		/* 状态检查 */
		if(!rscdrrm020ndse3->start)
		{
			rscdrrm020ndse3_unlock(rscdrrm020ndse3);
			continue;
		}
		
		rscdrrm020ndse3_unlock(rscdrrm020ndse3);
		
		if (event_recved & RSCDRRM020NDSE3_EVENT_DATA_READY)
		{// 数据已就绪
			rscdrrm020ndse3_lock(rscdrrm020ndse3);
			if (RSCDRRM020NDSE3_PRESSURE == rscdrrm020ndse3->mode) // pressure
			{
				rscdrrm020ndse3->mode = rscdrrm020ndse3_next_mode(rscdrrm020ndse3); // 切换模式
				rscdrrm020ndse3_unlock(rscdrrm020ndse3);
				
				/* 读取传感器压力数据并切换为温度采集模式 */
				uint8_t send_buf[4] = {0};
				uint8_t recv_buf[4] = {0};
				send_buf[0] = 0xFF;
				send_buf[1] = 0x40 | ((0x01 & 0x03) << 2) | ((1 - 1) & 0x03); // WREG command [0100 RRNN],
				const WorkModeFreq_T* pctWorkModeFreq = &(s_tModeFreqTbl[rscdrrm020ndse3->freq_index]);
				if (RSCDRRM020NDSE3_TEMPERATURE == rscdrrm020ndse3->mode)
				{ // 下次采集温度
					send_buf[2] = RSCDRRM020NDSE3_ADC_TEMPERATURE | RSCDRRM020NDSE3_ADC_1000HZ | RSCDRRM020NDSE3_ADC_FAST; // 用最快速度采集温度,避免过度干扰压力采集时序
				}
				else // if (RSCDRRM020NDSE3_PRESSURE == rscdrrm020ndse3->mode)
				{ // 下次采集压力
					send_buf[2] = RSCDRRM020NDSE3_ADC_PRESSURE | pctWorkModeFreq->freq_cfg | pctWorkModeFreq->mode;
				}
				send_buf[3] = 0xFF;
				ret = rscdrrm020ndse3_spi_adc_transfer(send_buf, recv_buf, sizeof(send_buf));
				if (RT_EOK == ret)
				{
					/* 
						处理压力数据
						Pressure data are output starting with MSB, in 24-bit 2’s complement format.
					*/
					pressure = (((uint32_t)recv_buf[0] << 16) & 0x00FF0000) 
						| (((uint32_t)recv_buf[1] << 8) & 0x0000FF00) 
						| ((uint32_t)recv_buf[2] & 0x000000FF);
					
					/* LOCK */
					rscdrrm020ndse3_lock(rscdrrm020ndse3);
					
					/* 处理自动归零请求 */
					if (rscdrrm020ndse3->auto_zero)
					{
						/* 统计样本的最小值、最大值、累加和、个数 */
						if (pressure < rscdrrm020ndse3_filter_min_val)
						{
							rscdrrm020ndse3_filter_min_val = pressure;
						}
						else if (pressure > rscdrrm020ndse3_filter_max_val)
						{
							rscdrrm020ndse3_filter_max_val = pressure;
						}
						rscdrrm020ndse3_filter_sum += pressure;
						rscdrrm020ndse3_filter_sample_cnt++;
				
						if (rscdrrm020ndse3_filter_sample_cnt >= rscdrrm020ndse3_filter_n)
						{ // 采集的样本数已达到要求
							/* 去掉最大值和最小值,计算均值 */
							uint32_t avg_pressure = (rscdrrm020ndse3_filter_sum - rscdrrm020ndse3_filter_min_val - rscdrrm020ndse3_filter_max_val) / (rscdrrm020ndse3_filter_sample_cnt - 2);
							pressure = avg_pressure;
							
							/* 清除自动归零请求标志 */
							rscdrrm020ndse3->auto_zero = false;
							/* 临时保存回调函数指针 */
							ATUO_ZERO_CPL_FUNC pfnAutoZeroCompleted = s_pfnAutoZeroCompleted;
							/* 清空回调函数指针 */
							s_pfnAutoZeroCompleted = NULL;
							/* 重新初始化滤波器变量 */
							rscdrrm020ndse3_filter_sum = 0;
							rscdrrm020ndse3_filter_sample_cnt = 0;
							rscdrrm020ndse3_filter_min_val = 0xFFFFFFFF;
							rscdrrm020ndse3_filter_max_val = 0;
							
							/* UNLOCK */
							rscdrrm020ndse3_unlock(rscdrrm020ndse3);
							
							/* 设置归零参数 */
							AutoZero_Pressure(avg_pressure, temperature);
							
							/* 如果设置了回调函数 */
							if (pfnAutoZeroCompleted)
							{
								/* 调用回调函数 */
								pfnAutoZeroCompleted();
							}
						}
						else
						{
							/* UNLOCK */
							rscdrrm020ndse3_unlock(rscdrrm020ndse3);
						}
					}
					else
					{
						/* UNLOCK */
						rscdrrm020ndse3_unlock(rscdrrm020ndse3);
					}
					
					/* 执行温度补偿并输出结果 */
					CompReturn_Struct result = Compensate_Pressure(pressure, temperature);
					if (PRESSURE_VALID == result.CompStatus)
					{ // 得到有效补偿结果
						/* 保存补偿结果压力值 */
						rscdrrm020ndse3->pressure_comp = result.f32PressureOutput;
						
						/* invoke callback */
						if (rscdrrm020ndse3->parent.rx_indicate != RT_NULL)
						{
							rscdrrm020ndse3->parent.rx_indicate(&rscdrrm020ndse3->parent, 4);
						}
					}
				}
			}
			else //if (RSCDRRM020NDSE3_TEMPERATURE == rscdrrm020ndse3->mode) // temperature
			{
				rscdrrm020ndse3->mode = rscdrrm020ndse3_next_mode(rscdrrm020ndse3); // 切换模式
				rscdrrm020ndse3_unlock(rscdrrm020ndse3);
				
				/* 读取传感器温度数据并切换为压力采集模式 */
				uint8_t send_buf[4] = {0};
				uint8_t recv_buf[4] = {0};
				send_buf[0] = 0xFF;
				send_buf[1] = 0x40 | ((0x01 & 0x03) << 2) | ((1 - 1) & 0x03); // WREG command [0100 RRNN],
				const WorkModeFreq_T* pctWorkModeFreq = &(s_tModeFreqTbl[rscdrrm020ndse3->freq_index]);
				if (RSCDRRM020NDSE3_TEMPERATURE == rscdrrm020ndse3->mode)
				{ // 下次采集温度
					send_buf[2] = RSCDRRM020NDSE3_ADC_TEMPERATURE | RSCDRRM020NDSE3_ADC_1000HZ | RSCDRRM020NDSE3_ADC_FAST; // 用最快速度采集温度,避免过度干扰压力采集时序
				}
				else // if (RSCDRRM020NDSE3_PRESSURE == rscdrrm020ndse3->mode)
				{ // 下次采集压力
					send_buf[2] = RSCDRRM020NDSE3_ADC_PRESSURE | pctWorkModeFreq->freq_cfg | pctWorkModeFreq->mode;
				}
				send_buf[3] = 0xFF;
				ret = rscdrrm020ndse3_spi_adc_transfer(send_buf, recv_buf, sizeof(send_buf));
				if (RT_EOK == ret)
				{
					/* 
						处理温度数据
						Temperature data are output starting with MSB. When reading 24 bits, the first 14 bits are used
						to indicate the temperature measurement result. The last 10 bits are random data and must be ignored. Negative temperature
						is represented in 2’s complement format. MSB = 0 indicates positive result, MSB = 1 indicates negative value.
					*/
					temperature = ((((uint32_t)recv_buf[0] << 8) & 0x0000FF00)
						| (((uint32_t)recv_buf[1]) & 0x000000FF)) >> 2;
					rscdrrm020ndse3->temperature = temperature;
				}
			}
		}
	}
}

/* initialize the device */
static rt_err_t rscdrrm020ndse3_init(rt_device_t dev)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_init()\r\n");
	
	/* 创建EVENT */
	rscdrrm020ndse3_event = rt_event_create("rscdrrm020ndse3", RT_IPC_FLAG_FIFO);
	if (RT_NULL == rscdrrm020ndse3_event)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_init() call rt_event_create(rscdrrm020ndse3) failed!\r\n");
        return -RT_ERROR;
	}
	
	/* 创建和启动传感器线程 */ 
    rscdrrm020ndse3_thread = rt_thread_create("rscdrrm020ndse3", rscdrrm020ndse3_thread_entry, (void*)rscdrrm020ndse3, 1024, 5, 10); 
    if(RT_NULL == rscdrrm020ndse3_thread)
    {
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_init() call rt_thread_create(rscdrrm020ndse3) failed!\r\n");
        return -RT_ERROR;
    }
    rt_thread_startup(rscdrrm020ndse3_thread);
	
	/* 开启传感器电源 */
	rscdrrm020ndse3_power_on(dev);
	
	/* 分配缓冲区用于存储EEPROM中的所有参数 */
	uint8_t* eeprom_buf = (uint8_t*)rt_malloc(RSCDRRM020NDSE3_EEPROM_SIZE);
	if (RT_NULL == eeprom_buf)
	{
		/* 关闭传感器电源 */
		rscdrrm020ndse3_power_off(dev);
	
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_init() call rt_malloc(RSCDRRM020NDSE3_EEPROM_SIZE) failed!\r\n");
		return -RT_ENOMEM;
	}
	
	/* 读取EEPROM到缓冲区 */
	rt_err_t ret = rscdrrm020ndse3_spi_read_eeprom(0x00, eeprom_buf, RSCDRRM020NDSE3_EEPROM_SIZE);
	if (RT_EOK != ret)
    {
		/* 释放资源 */
		rt_free(eeprom_buf);
	
		/* 关闭传感器电源 */
		rscdrrm020ndse3_power_off(dev);
		
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_init() call rscdrrm020ndse3_spi_read_eeprom(0,%d) failed, error(%d)!\r\n", 
			RSCDRRM020NDSE3_EEPROM_SIZE, ret);
		return ret;
    }
	
	/* 使用EEPROM中的参数初始化补偿函数库 */
	CompStatus_Enum comp_ret = Compensate_Pressure_Init(eeprom_buf);
	if (COMPINIT_OK != comp_ret)
	{
		/* 释放资源 */
		rt_free(eeprom_buf);
	
		/* 关闭传感器电源 */
		rscdrrm020ndse3_power_off(dev);
		
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_init() call Compensate_Pressure_Init(eeprom_buf) failed, error(%d)!\r\n", comp_ret);
		return -RT_ERROR;
	}
	
	/* 
		保存ADC参数
		Initialize all four configuration registers to the default values in the EEPROM’s Relative addresses 61, 63, 65 and 67
	*/
	rscdrrm020ndse3->adc_cfg_param[0] = eeprom_buf[61];
	rscdrrm020ndse3->adc_cfg_param[1] = eeprom_buf[63];
	rscdrrm020ndse3->adc_cfg_param[2] = eeprom_buf[65];
	rscdrrm020ndse3->adc_cfg_param[3] = eeprom_buf[67];
	
	/* 释放资源 */
	rt_free(eeprom_buf);
	
	/* 关闭传感器电源 */
	rscdrrm020ndse3_power_off(dev);
	
	/* 清除启动状态 */
	rscdrrm020ndse3->start = false;
	
	/* 清除结果 */
	rscdrrm020ndse3->pressure_comp = 0.0;
	rscdrrm020ndse3->temperature = 0;
	
	/* 复位压力连续采集次数 */
	pressure_continuous_cnt = 0;
	
    return RT_EOK;
}

/* control the device */
static rt_err_t rscdrrm020ndse3_control(rt_device_t dev, int cmd, void *args)
{
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_control() cmd=0x%x\r\n", cmd);
	
	rt_err_t ret = RT_EOK;
	
    switch (cmd)
    {
		case RSCDRRM020NDSE3_START:
		{
			/* 启动传感器数据采集 */
			ret = rscdrrm020ndse3_start(dev);
			break;
		}
		case RSCDRRM020NDSE3_STOP:
		{
			/* 停止传感器数据采集 */
			ret = rscdrrm020ndse3_stop(dev);
			break;
		}
		case RSCDRRM020NDSE3_AUTO_ZERO:
		{
			ATUO_ZERO_CPL_FUNC pfnAutoZeroCompleted = (ATUO_ZERO_CPL_FUNC)args;
			/* 请求自动归零 */
			ret = rscdrrm020ndse3_auto_zero(dev, pfnAutoZeroCompleted);
			break;
		}
		case RSCDRRM020NDSE3_SET_FREQ:
		{
			uint32_t u32FreqIndex = (uint32_t)args;
			/* 设置采样率 */
			ret = rscdrrm020ndse3_set_freq(dev, u32FreqIndex);
			break;
		}
		case RSCDRRM020NDSE3_GET_FREQ:
		{
			uint32_t* pu32FreqIndex = (uint32_t*)args;
			/* 读取采样率 */
			ret = rscdrrm020ndse3_get_freq(dev, pu32FreqIndex);
			break;
		}
		case RSCDRRM020NDSE3_GET_TEMP:
		{
			float* pfTemperature = (float*)args;
			/* 读取温度值(单位: 摄氏度) */
			ret = rscdrrm020ndse3_get_temperature(dev, pfTemperature);
			break;
		}
		default:
		{
			ret = -RT_ERROR;
			RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_control() failed, unsupported cmd(0x%x)!\r\n", cmd);
			break;
		}
    }

    return ret;
}

/* Open the rscdrrm020ndse3 device */
static rt_err_t rscdrrm020ndse3_open(rt_device_t dev, uint16_t oflag)
{
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() oflag=0x%x\r\n", oflag);
	
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	
	/* 开启传感器电源 */
	rscdrrm020ndse3_power_on(dev);
	
	/* 配置传感器数据READY中断检测 */
	rt_err_t ret = rt_pin_attach_irq(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_MODE_FALLING, rscdrrm020ndse3_rdy_isr, rscdrrm020ndse3);
	if (RT_EOK != ret)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() call rt_pin_attach_irq(RSCDRRM020NDSE3_RDY_PIN) failed, error(%d)!\r\n", ret);
		return ret;
	}
	
	/* 确保传感器数据READY中断检测处于DISABLE状态 */
	ret = rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE);
	if (RT_EOK != ret)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_open() call rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE) failed, error(%d)!\r\n", ret);
		return ret;
	}
	
	rscdrrm020ndse3_lock(dev);
	
	/* 初始时为停止状态 */
	rscdrrm020ndse3->start = false;
	
	/* 清除结果 */
	rscdrrm020ndse3->pressure_comp = 0.0;
	rscdrrm020ndse3->temperature = 0;
	
	/* 复位压力连续采集次数 */
	pressure_continuous_cnt = 0;
	
	/* 采样率(索引) */
	rscdrrm020ndse3->freq_index = RSCDRRM020NDSE3_ADC_DEFAUT_FREQ_INDEX;
	
	rscdrrm020ndse3_unlock(dev);
	
    return RT_EOK;
}

/* Close the device */
static rt_err_t rscdrrm020ndse3_close(rt_device_t dev)
{
	RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_close()\r\n");
	
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	
	rscdrrm020ndse3_lock(dev);
	
	/* 进入停止状态 */
	rscdrrm020ndse3->start = false;
	
	/* 清除结果 */
	rscdrrm020ndse3->pressure_comp = 0.0;
	rscdrrm020ndse3->temperature = 0;
	
	/* 复位压力连续采集次数 */
	pressure_continuous_cnt = 0;
	
	rscdrrm020ndse3_unlock(dev);
	
	/* 停止传感器数据READY中断检测 */
	rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE);
	
	/* 卸载传感器数据READY中断检测 */
	rt_pin_detach_irq(RSCDRRM020NDSE3_RDY_PIN);
	
	/* 关闭传感器电源 */
	rscdrrm020ndse3_power_off(dev);
	
    return RT_EOK;
}

/* Read */
static rt_size_t rscdrrm020ndse3_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	if (size < 4)
	{
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3 read data buffer size must >= 4!\r\n");
		return 0;
	}
	
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
		
	rt_memcpy(buffer, &(rscdrrm020ndse3->pressure_comp), 4);
	
	return 4;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rscdrrm020ndse3_ops = 
{
    rscdrrm020ndse3_init,
    rscdrrm020ndse3_open,
    rscdrrm020ndse3_close,
    rscdrrm020ndse3_read,
    RT_NULL,
    rscdrrm020ndse3_control
};
#endif

int rscdrrm020ndse3_hw_init(void)
{
    RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_hw_init()\r\n");
	
	/* 创建和初始化SPI EEPROM设备(CS_EE pin: PE15) */
	rt_err_t ret = rt_hw_spi_device_attach(RSCDRRM020NDSE3_SPI_BUS_NAME, 
		RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME, GPIOE, GPIO_PIN_15);
    if (RT_EOK != ret)
    {
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_hw_init() call rt_hw_spi_device_attach(%s, %s) failed, error(%d)!\r\n", 
			RSCDRRM020NDSE3_SPI_BUS_NAME, RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME, ret);
		return ret;
    }
		
	struct rt_spi_device* spi_ee_device = (struct rt_spi_device*)rt_device_find(RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME);
    if (RT_NULL == spi_ee_device)
    {
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_hw_init() call rt_device_find(%s) failed!\r\n", 
			RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME);
		return -RT_ERROR;
    }

    /* config eeprom spi device */
    {
		/* EEPROM operates in SPI mode 0 where CPOL = 0 and CPHA = 0 (0,0) and mode 3 where CPOL = 1 and CPHA = 1 (1,1) */
		struct rt_spi_configuration cfg = {0};
		cfg.data_width = 8;
		cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible Modes 0 (CPOL = 0, CPHA = 0) */
		cfg.max_hz = 5 * 1000 * 1000; /* SPI Interface with Clock Speeds Up to 5 MHz */
		ret = rt_spi_configure(spi_ee_device, &cfg);
		if (RT_EOK != ret)
		{
			RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_hw_init() call rt_spi_configure(spi_ee_device) failed, error(%d)!\r\n", ret);
			return ret;
		}
    }
		
	/* save eeprom spi device */
	rscdrrm020ndse3_dev.spi_ee_device = spi_ee_device;
	
	/* 创建和初始化SPI ADC设备(CS_ADC pin: PB10) */
	ret = rt_hw_spi_device_attach(RSCDRRM020NDSE3_SPI_BUS_NAME, 
		RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME, GPIOB, GPIO_PIN_10);
    if (RT_EOK != ret)
    {
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_hw_init() call rt_hw_spi_device_attach(%s, %s) failed, error(%d)!\r\n", 
			RSCDRRM020NDSE3_SPI_BUS_NAME, RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME, ret);
		return ret;
    }
		
	struct rt_spi_device* spi_adc_device = (struct rt_spi_device*)rt_device_find(RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME);
    if (RT_NULL == spi_adc_device)
    {
		RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_hw_init() call rt_device_find(%s) failed!\r\n", 
			RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME);
		return -RT_ERROR;
    }

    /* config adc spi device */
    {
		/* The ADC interface operates in SPI mode 1 where CPOL = 0 and CPHA = 1 */
		struct rt_spi_configuration cfg = {0};
		cfg.data_width = 8;
		cfg.mode = RT_SPI_MODE_1 | RT_SPI_MSB; /* SPI Compatible Modes 1 (CPOL = 0, CPHA = 1) */
		cfg.max_hz = 5 * 1000 * 1000; /* SPI Interface with Clock Speeds Up to 5 MHz */
		ret = rt_spi_configure(spi_adc_device, &cfg);
		if (RT_EOK != ret)
		{
			RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_hw_init() call rt_spi_configure(spi_adc_device) failed, error(%d)!\r\n", ret);
			return ret;
		}
    }
		
	/* save adc spi device */
	rscdrrm020ndse3_dev.spi_adc_device = spi_adc_device;
		
	/* init rt-thread device struct */
    rscdrrm020ndse3_dev.parent.type    = RT_Device_Class_Miscellaneous;
#ifdef RT_USING_DEVICE_OPS
    rscdrrm020ndse3_dev.parent.ops     = &rscdrrm020ndse3_ops;
#else
    rscdrrm020ndse3_dev.parent.init    = rscdrrm020ndse3_init;
    rscdrrm020ndse3_dev.parent.open    = rscdrrm020ndse3_open;
    rscdrrm020ndse3_dev.parent.close   = rscdrrm020ndse3_close;
    rscdrrm020ndse3_dev.parent.read    = rscdrrm020ndse3_read;
    rscdrrm020ndse3_dev.parent.write   = RT_NULL;
    rscdrrm020ndse3_dev.parent.control = rscdrrm020ndse3_control;
#endif
	
	/* set POWER_EN pin mode to output */
	rt_pin_write(RSCDRRM020NDSE3_PWER_EN_PIN, PIN_LOW); // 初始化时关闭传感器电源
    rt_pin_mode(RSCDRRM020NDSE3_PWER_EN_PIN, PIN_MODE_OUTPUT);
	
	/* set RDY pin mode to input */
    rt_pin_mode(RSCDRRM020NDSE3_RDY_PIN, PIN_MODE_INPUT_PULLUP);
	
	/* ADC参数清零 */
	rt_memset(rscdrrm020ndse3_dev.adc_cfg_param, 0, sizeof(rscdrrm020ndse3_dev.adc_cfg_param));
	
	/* 清除启动状态 */
	rscdrrm020ndse3_dev.start = false;
	
	/* 清除结果 */
	rscdrrm020ndse3_dev.pressure_comp = 0.0;
	rscdrrm020ndse3_dev.temperature = 0;
	
	/* 复位压力连续采集次数 */
	pressure_continuous_cnt = 0;
	
	/* init lock */
	rt_mutex_init(&(rscdrrm020ndse3_dev.lock), "rscdrrm020ndse3", RT_IPC_FLAG_FIFO);
	
	/* register a character device */
    ret = rt_device_register(&(rscdrrm020ndse3_dev.parent), RSCDRRM020NDSE3_DEVICE_NAME, 
		RT_DEVICE_FLAG_STANDALONE | RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_INT_RX);
	if (RT_EOK != ret)
    {
        RSCDRRM020NDSE3_TRACE("rscdrrm020ndse3_hw_init() call rt_device_register(%s) failed, error(%d)!\r\n", 
			RSCDRRM020NDSE3_DEVICE_NAME, ret);
		return ret;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rscdrrm020ndse3_hw_init);

#endif /* BSP_USING_RSCDRRM020NDSE3 */
