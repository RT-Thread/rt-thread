/*!
 *   \file  	 cmd_parser.c
 *   \brief	     uart and usb command parser /ARM/IAR/GCC compiler
 *   \details
 *   \Change Logs
 *   \date           \author           \Notes
 *   2020-11-23      Eric -  first implementation
*/

/*
 --------------------------------------------------------------------------------
    Dependencies
 --------------------------------------------------------------------------------
 */
/* <Header file of standard Library> */
#include <rtthread.h>
#include <stdbool.h>
/*----------------------------------------------------------------------------*/
/* "Header file of nonstandard Library" */
#include "drv_spi.h"
#include "rscdrrm020dsecopy.h"
#include "Pressure_Comp.h"
#include "board_config.h"

/*
 --------------------------------------------------------------------------------
    Debugging Flag
 --------------------------------------------------------------------------------
 */
#ifndef ULOG_USING_SYSLOG
    #define LOG_TAG              "[rscdrrm020dsecopy.c]"
    #define LOG_LVL              LOG_LVL_DBG
    #include <ulog.h>
#else
    #include <syslog.h>
#endif /* ULOG_USING_SYSLOG */


/*
 --------------------------------------------------------------------------------
    Mcaro Definitions
 --------------------------------------------------------------------------------
 */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / size((a)[0]))
#endif
/* spi bus name */
#define RSCDRRM020NDSE3_SPI_BUS_NAME        "spi2"
/* eeprom spi device name */
#define RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME  "spi20"
/* adc spi device name */
#define RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME "spi21"
/* pin define in board_config.h */

/* sensor eeprom size byte */
#define RSCDRRM020NDSE3_EEPROM_SIZE         (452)
/*! adc read mode in datasheet P22 
Table 3-1. ADC Configuration Register
 */
#define RSCDRRM020NDSE3_ADC_NORMAL          0x00
#define RSCDRRM020NDSE3_ADC_FAST            0x10
/* adc frequence in normal */
#define RSCDRRM020NDSE3_ADC_20HZ            0x00
#define RSCDRRM020NDSE3_ADC_45HZ            0x20
#define RSCDRRM020NDSE3_ADC_90HZ            0x40
#define RSCDRRM020NDSE3_ADC_175HZ           0x60
#define RSCDRRM020NDSE3_ADC_330HZ           0x80
#define RSCDRRM020NDSE3_ADC_600HZ           0xA0
#define RSCDRRM020NDSE3_ADC_1000HZ          0xC0
/* adc frequence in fast mode (double) */

/* adc read mode */
#define RSCDRRM020NDSE3_ADC_TEMPERATURE     0x06 // read temperature
#define RSCDRRM020NDSE3_ADC_PRESSURE        0x04 // pressure

/*! adc default frequence index 6 330HZ
temperature read will occupy period
 */
#define RSCDRRM020NDSE3_ADC_DEFAULT_FREQ_INDEX  6
#define RSCDRRM020NDSE3_ADC_DEFAULT_FREQ    330

/* adc temperature read period (ms) */
#define RSCDRRM020NDSE3_ADC_TEMP_INTERVAL   100

/* rt data read event */
#define RSCDRRM020NDSE3_EVENT_DATA_READY    0x00000001
/* rt mutex take and release */
#define rscdrrm020ndse3_lock(dev)   rt_mutex_take(&((struct rscdrrm020ndse3_device*)dev)->lock,RT_WAITING_FOREVER);
#define rscdrrm020ndse3_unlock(dev) rt_mutex_release(&((struct rscdrrm020ndse3_device*)dev)->lock);

/*
 --------------------------------------------------------------------------------
    Data Structures
 --------------------------------------------------------------------------------
 */

 /*
 -------------------------------------------------------------------------------
    Typedefinitions
 -------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------
    Local Vars
 --------------------------------------------------------------------------------
 */
/* sensor device */
static struct rscdrrm020ndse3_device rscdrrm020ndse3_dev;

/* sensor device thread */
static struct rt_thread* rscdrrm020ndse3_thread = RT_NULL;
/* sensor device event */
static rt_event_t rscdrrm020ndse3_event = RT_NULL;

/* filter Vars (use to auto zero) */
static uint32_t rscdrrm020ndse3_filter_min_val = 0xFFFFFFFF; // sample min
static uint32_t rscdrrm020ndse3_filter_max_val = 0; // sample max
static uint32_t rscdrrm020ndse3_filter_sum = 0; // sum sample for average
static uint32_t rscdrrm020ndse3_filter_sample_cnt = 0; // already read samples
static uint32_t rscdrrm020ndse3_filter_n = (10 * RSCDRRM020NDSE3_ADC_DEFAULT_FREQ_INDEX + 10); // all read times

/* auto zero callback function */
static AUTO_ZERO_CPL_FUNC s_pfnAutoZeroCompleted = NULL;

/* pressure continuous counts (with temperature data) */
static uint32_t pressure_continuous_cnt = 0; // already read pressure data count
static uint32_t pressure_continuous_n   = ((RSCDRRM020NDSE3_ADC_TEMP_INTERVAL * RSCDRRM020NDSE3_ADC_DEFAULT_FREQ) / 1000); //continuous read pressure data count

/* work mode frequence table (index by typedef struct) */
typedef struct 
{
    uint8_t mode;       //work mode
    uint8_t freq_cfg;   //frequence(configration)
    uint16_t freq_val   //frequence(real)
}WorkModeFreq_T;

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

/*
 --------------------------------------------------------------------------------
    Extern Function
 --------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------
    Local Function Definitions
 --------------------------------------------------------------------------------
 */
/*
 * Function: rscdrrm020ndse3_power_on()
 * Descriptions: open sensor power
 */
static void rscdrrm020ndse3_power_on(rt_device_t dev)
{
    LOG_D("rscdrrm020ndse3_power_on()");
    rt_pin_write(RSCDRRM020NDSE3_PWER_EN_PIN, PIN_HIGH);
    rt_thread_mdelay(1);
}
/*
 * Function: rscdrrm020ndse3_power_off()
 * Descriptions: sensor power off
 */
static void rscdrrm020ndse3_power_off(rt_device_t dev)
{
    LOG_D("rscdrrm020ndse3_power_off()");
    rt_pin_write(RSCDRRM020NDSE3_PWER_EN_PIN, PIN_LOW);
}
/*
 * Function: rscdrrm020ndse3_spi_read_eeprom()
 * Descriptions: read eeprom set address lenth/data
 */
static rt_err_t rscdrrm020ndse3_spi_read_eeprom(uint16_t address, uint8_t* recv_buf, rt_size_t buf_len)
{
    struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_ee_device;

    uint8_t send_buf[2] = {0};
    /*! EEPROM Communications in datasheet P20
    Each memory of EEPROM contains 8-bit data or one byte. To read from memory, 
    the host sends an EAD_EEPROM instruction[0000 X011] followed by an 8-bit address. 
    The ‘X’ bit in the read instruction is the ninth (MSB) address bit
     */
    if (address & 0x0100)
    {// ninth (MSB) address bit is 1
        send_buf[0] = 0x0B; //  EAD_EEPROM
    }
    else
    {// ninth (MSB) address bit is 0
        send_buf[0] = 0x03;        
    }
    send_buf[1] = (uint8_t)(address & 0x00ff); //ADRESS

    return rt_spi_send_then_recv(spi_device, send_buf, sizeof(send_buf), recv_buf, buf_len);    
}
/*
 * Function: rscdrrm020ndse3_spi_send_adc_cmd()
 * Descriptions: send adc command
 */
static rt_err_t rscdrrm020ndse3_spi_send_adc_cmd(uint8_t cmd)
{
    struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_adc_device;

    rt_size_t ret = rt_spi_send(spi_device, &cmd , 1);
    if(1 != ret)
    {
        return rt_get_errno();
    }

    return RT_EOK;
}
/*
 * Function: rscdrrm020ndse3_spi_write_adc_reg()
 * Descriptions: write adc register
 */
static rt_err_t rscdrrm020ndse3_spi_write_adc_reg(uint8_t reg, const uint8_t* send_data, rt_size_t data_len)
{
    struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_adc_device;

    /*!
    To program a configuration register, the host sends a WREG command [0100 RRNN],
     where ‘RR’ is the register number and ‘NN’ is the number of bytes to be written –1
     */
    uint8_t send_buf[1] = {0};
    send_buf[0] = 0x40 | ((reg & 0x30) << 2) | ((data_len -1) & 0x30);

    return rt_spi_send_then_send(spi_device, send_buf, sizeof(send_buf), send_buf, data_len);
}
/*
 * Function: rscdrrm020ndse3_spi_read_adc_reg()
 * Descriptions: read adc register
 */
static rt_err_t rscdrrm020ndse3_spi_read_adc_reg(uint8_t reg, uint8_t* recv_buf, rt_size_t buf_len)
{
    struct rt_spi_device* spi_device = rscdrrm020ndse3_dev.spi_adc_device;
    /*
		RREG (0010 RRNN), 
		where ‘RR’ is the register number and ‘NN’ is the number of bytes to be read –1.
	*/
    uint8_t send_buf[1] = {0};
    send_buf[0] = 0x20 | ((reg & 0x03) << 2) | ((buf_len - 1) & 0x03);
    
    return rt_spi_send_then_recv(spi_device, send_buf, sizeof(send_buf), recv_buf, buf_len);
}
/*
 * Function: rscdrrm020ndse3_spi_adc_transfer()
 * Descriptions: transfer data one times
 */
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
/*
 * Function: rscdrrm020ndse3_rdy_isr()
 * Descriptions: rscdrrm020ndse3 rdy interupt service
 */
static void rscdrrm020ndse3_rdy_isr(void *args)
{
    struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)args;
    
    /* check sensor status */
    if (!rscdrrm020ndse3->start)
    {
        return;
    }

    /* send event to thread */
    rt_event_send(rscdrrm020ndse3_event, RSCDRRM020NDSE3_EVENT_DATA_READY);
}
/*
 * Function: rscdrrm020ndse3_start()
 * Descriptions: rscdrrm020ndse3 rdy interupt service
 */
static rt_err_t rscdrrm020ndse3_start(rt_device_t dev)
{
    struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
    LOG_D("rscdrrm020ndse3_start()");

    rscdrrm020ndse3_lock(dev);

    /* check sensor status */
    if (rscdrrm020ndse3->start) 
    {//start
    rscdrrm020ndse3_unlock(dev);
    return RT_EOK;        
    }

    rscdrrm020ndse3_unlock(dev);

    /*! ADC Reset Command in datasheet P23
        The ADC reset command RESET [0000 0110] resets the ADC to the default values.
     */
    rt_err_t ret = rscdrrm020ndse3_spi_send_adc_cmd(0x06);
    if (RT_EOK != ret)
    {
        LOG_D("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_send_adc_cmd(0x06) failed, error(%d)!\r\n", ret);
        goto _EXIT;
    }
	/*!
		Resets the device to the default values. 
		Wait at least (50 μs + 32 · t(CLK)) after the RESET command is sent before sending any other command.
	 */
    {
        rt_thread_mdelay(1);
    }
    /*!
		配置ADC参数
		Initialize all four configuration registers to the default values in the EEPROM’s Relative addresses 61, 63, 65 and 67 
		by sending a WREG command to address 0
	 */
    ret = rscdrrm020ndse3_spi_write_adc_reg(0x00, rscdrrm020ndse3->adc_cfg_param, sizeof(rscdrrm020ndse3->adc_cfg_param));
	if (RT_EOK != ret)
    {
		LOG_D("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_write_adc_reg(0, adc_cfg_param) failed, error(%d)!\r\n", ret);
		goto _EXIT;
    }

    /* read register check data */
    {
        uint8_t cfg_regs[4] = {0};
        ret =rscdrrm020ndse3_spi_read_adc_reg(0x00, cfg_regs,sizeof(cfg_regs));
        if (RT_EOK != ret)
        {
            LOG_D("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_read_adc_reg(0x00) failed, error(%d)!\r\n", ret);
			goto _EXIT;
        }        
    }
    /*! ADC Programming and Read Sequence datasheet P24
		config read temperature mode and set frequence
        Configure the sensor to temperature mode and the desired data rate by setting configuration register 1 by sending a WREG
		command to address 1, [0100 0100] followed by the single configuration byte. Bit 1 (TS) of the configuration register should
		be set to 1.
	 */
    {
        uint8_t mode = RSCDRRM020NDSE3_ADC_TEMPERATURE | RSCDRRM020NDSE3_ADC_1000HZ | RSCDRRM020NDSE3_ADC_FAST;
        ret = rscdrrm020ndse3_spi_write_adc_reg(0x01, &mode, 1);
        if (RT_EOK != ret)
        {
			LOG_D("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_write_adc_reg(0x01) failed, error(%d)!\r\n", ret);
			goto _EXIT;
        }
    }

    /*! datasheet P24
		Send 08h command to start data conversion on ADC.
	 */
    ret = rscdrrm020ndse3_spi_send_adc_cmd(0x08);
    if (RT_EOK != ret)
    {
		LOG_D("rscdrrm020ndse3_open() call rscdrrm020ndse3_spi_send_adc_cmd(0x08) failed, error(%d)!\r\n", ret);
		goto _EXIT;
    }
   	/*!
		the START/SYNC command must be issued one time to start converting continuously. 
		Sending the START/SYNC command while converting in continuous conversion mode resets the
		digital filter and restarts continuous conversions
	 */ 
    /* enable sensor data ready interupt */
    ret = rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_ENABLE);
 	{
		LOG_D("rscdrrm020ndse3_open() call rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN) failed, error(%d)!\r\n", ret);
		goto _EXIT;
	} 

    rscdrrm020ndse3_lock(dev);

    /* clear data */
    rscdrrm020ndse3->pressure_comp = 0.0;
    rscdrrm020ndse3->temperature   = 0;

    /* reset continuous count */
    pressure_continuous_cnt        = 0;

    /* temperature read mode */
    rscdrrm020ndse3->mode = RSCDRRM020NDSE3_TEMPERATURE;
    /* start mode */
    rscdrrm020ndse3->start = true;

    rscdrrm020ndse3_unlock(dev);

_EXIT:
    return ret;    
}

/*
 * Function: rscdrrm020ndse3_stop()
 * Descriptions: stop read sensor data
 */
static rt_err_t rscdrrm020ndse3_stop(rt_device_t dev)
{
    struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
    LOG_D("rscdrrm020ndse3_stop()");

    rscdrrm020ndse3_lock(dev);

    /* check sensor status */
    if (!rscdrrm020ndse3->start) 
    {//stop
    rscdrrm020ndse3_unlock(dev);
    return RT_EOK;        
    }

    rscdrrm020ndse3_unlock(dev);

    /*! ADC Reset Command in datasheet P23
        The ADC reset command RESET [0000 0110] resets the ADC to the default values.
     */
    rt_err_t ret = rscdrrm020ndse3_spi_send_adc_cmd(0x06);
    if (RT_EOK != ret)
    {
        LOG_D("rscdrrm020ndse3_stop() call rscdrrm020ndse3_spi_send_adc_cmd(0x06) failed, error(%d)!\r\n", ret);
        goto _EXIT;
    }
	
    /* stop sensor ready interupt */
    ret = rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE);
 	{
		LOG_D("rscdrrm020ndse3_open() call rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN) failed, error(%d)!\r\n", ret);
		goto _EXIT;
	} 

    rscdrrm020ndse3_lock(dev);

        /* start mode */
    rscdrrm020ndse3->start = false;

    /* clear data */
    rscdrrm020ndse3->pressure_comp = 0.0;
    rscdrrm020ndse3->temperature   = 0;

    /* reset continuous count */
    pressure_continuous_cnt        = 0;

    rscdrrm020ndse3_unlock(dev);

_EXIT:
    return ret;    
}

/*
 * Function: rscdrrm020ndse3_stop()
 * Descriptions: stop read sensor data
 */
static rt_err_t rscdrrm020nds3_auto_zero(rt_device_t dev, AUTO_ZERO_CPL_FUNC pfnAutoZeroCompleted)
{
    struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
    LOG_D("rscdrrm020ndse3_auto_zero()");

    rscdrrm020ndse3_lock(dev);

    /* check status */
    if (!rscdrrm020ndse3->start)
    {// not in start
		rscdrrm020ndse3_unlock(dev);
		LOG_D("rscdrrm020ndse3_auto_zero() failed, not in start state!\r\n");
		return -RT_ERROR;
    }
    if (rscdrrm020ndse3->auto_zero)
    {// auto zero runing
		rscdrrm020ndse3_unlock(dev);
		LOG_D("rscdrrm020ndse3_auto_zero() failed, auto zero already in process!\r\n");
		return -RT_ERROR;
    }

    /* init filter vars */
    rscdrrm020ndse3_filter_sum          = 0;
    rscdrrm020ndse3_filter_sample_cnt   = 0;
    rscdrrm020ndse3_filter_min_val      = 0xFFFFFFFF;
    rscdrrm020ndse3_filter_max_val      = 0;

    /* set auto zero flag */
    rscdrrm020ndse3->auto_zero          = true;

    /* auto zero completed */
    s_pfnAutoZeroCompleted              = pfnAutoZeroCompleted;

    rscdrrm020ndse3_unlock(dev);

    return RT_EOK;    
}
/*
 * Function: rscdrrm020ndse3_set_freq()
 * Descriptions: set frequence
 */
static rt_err_t rscdrrm020ndse3_set_freq(rt_device_t dev, uint32_t u32FreqIndex)
{
    struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
 	LOG_D("rscdrrm020ndse3_set_freq() u32FreqIndex=%u\r\n", u32FreqIndex);
    
    /* index */
    if (u32FreqIndex >= ARRAY_SIZE(s_tModeFreqTbl))
    {
		LOG_D("rscdrrm020ndse3_set_freq() failed, freq_index must < (%u)!\r\n", ARRAY_SIZE(s_tModeFreqTbl));
		return -RT_ERROR;
    }

    rscdrrm020ndse3_lock(dev);

    /* update frequence configration */
    rscdrrm020ndse3->freq_index = u32FreqIndex;

    /* recount filter index for autozero */
    rscdrrm020ndse3_filter_n = (10 * u32FreqIndex +10);

    /* recount pressure index */
    const WorkModeFreq_T* pctWorkModeFreq = &(s_tModeFreqTbl[u32FreqIndex]);
    pressure_continuous_n = ((RSCDRRM020NDSE3_ADC_TEMP_INTERVAL * pctWorkModeFreq->freq_val) / 1000);
    
    rscdrrm020ndse3_unlock(dev);

    return RT_EOK;
}

/*
 * Function: rscdrrm020ndse3_get_freq()
 * Descriptions: read frequence
 */
static rt_err_t rscdrrm020ndse3_get_freq(rt_device_t dev, uint32_t* pu32FreqIndex)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	LOG_D("rscdrrm020ndse3_get_freq() pu32FreqIndex=0x%x\r\n", pu32FreqIndex);
	
	//rscdrrm020ndse3_lock(dev);
	if (pu32FreqIndex)
	{
		*pu32FreqIndex = rscdrrm020ndse3->freq_index;
	}
	
	//rscdrrm020ndse3_unlock(dev);	
	return RT_EOK;
}
/*
 * Function: rscdrrm020ndse3_get_temperature()
 * Descriptions: read temperature
 */
static rt_err_t rscdrrm020ndse3_get_temperature(rt_device_t dev, float* pfTemperature)
{
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	LOG_D("rscdrrm020ndse3_get_temperature() pfTemperature=0x%x\r\n", pfTemperature);
	
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

/*
 * Function: rscdrrm020ndse3_next_mode()
 * Descriptions: next mode pressure/temperature alternate
 */
static enum rscdrrm020ndse3_mode rscdrrm020ndse3_next_mode(struct rscdrrm020ndse3_device* rscdrrm020ndse3)
{
    enum rscdrrm020ndse3_mode next_mode = RSCDRRM020NDSE3_PRESSURE;

    if (RSCDRRM020NDSE3_PRESSURE == rscdrrm020ndse3->mode) // pressure
    { // pressure read mode
        if (pressure_continuous_cnt < pressure_continuous_n)
        {// continuous ++
            /* continuous pressure read */
             next_mode = RSCDRRM020NDSE3_PRESSURE;
             /* up counter */
             ++pressure_continuous_cnt;
        }
        else
         {// turn to temperature read mode
         next_mode = RSCDRRM020NDSE3_TEMPERATURE;        
         }
    }
    else
    {//temperature read mode
        /* turn to read pressure mode */
        next_mode = RSCDRRM020NDSE3_PRESSURE;
        /* rest pressure counter */
        pressure_continuous_cnt = 0;
    }

    return next_mode;
}
/*!
 * \fn      rscdrrm020ndse3_thread_entry()
 * \brief   sensor thread
 */
static void rscdrrm020ndse3_thread_entry(void* param)
{
    struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)param;
    /* pressure not compensation */
    uint32_t pressure = 0;
    /* temperature */
    uint32_t temperature = 0;

    /* into loop */
    while (1)
    {
        rt_uint32_t event_recved = 0;
        rt_err_t ret = rt_event_recv(rscdrrm020ndse3_event, RSCDRRM020NDSE3_EVENT_DATA_READY,
                                    (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
                                    RT_WAITING_FOREVER, &event_recved);
        if (RT_EOK != ret)
        {
      		LOG_E("rscdrrm020ndse3_thread_entry() rt_event_recv(rscdrrm020ndse3_event) failed, error(%d)!\r\n", ret);
			break;      
        }

        rscdrrm020ndse3_lock(rscdrrm020ndse3);

        /* check status */
        if (!rscdrrm020ndse3->start)
        {
            rscdrrm020ndse3_unlock(rscdrrm020ndse3);
            continue;
        }

        rscdrrm020ndse3_unlock(rscdrrm020ndse3);

        if (event_recved & RSCDRRM020NDSE3_EVENT_DATA_READY)
        {/*data ready */
            rscdrrm020ndse3_lock(rscdrrm020ndse3);
            if (RSCDRRM020NDSE3_PRESSURE == rscdrrm020ndse3->mode ) //pressure
            {
                rscdrrm020ndse3->mode = rscdrrm020ndse3_next_mode(rscdrrm020ndse3);
                rscdrrm020ndse3_unlock(rscdrrm020ndse3);

                /*! read pressure sensor and turn to read temperature mode
                Configure the sensor to the pressure mode and the desired data 
                rate by setting configuration register 1 by sending a WREG command to address 1,
                 [0100 0100] followed by the single configuration byte.Bit 1 (TS) of the 
                 configuration register should be set to 0
                 */

                uint8_t send_buf[4] = {0};
                uint8_t recv_buf[4] = {0};
                send_buf[0] = 0xFF;
                send_buf[1] = 0x40 | ((0x01 & 0x03) <<2) | ((1 -1) & 0x03);//// WREG command [0100 RRNN],
                const WorkModeFreq_T* pctWorkModeFreq = &(s_tModeFreqTbl[rscdrrm020ndse3->freq_index]);
                if(RSCDRRM020NDSE3_TEMPERATURE == rscdrrm020ndse3->mode )
                {//temperature next
                    /* use fast mode read temperature */
                    send_buf[2] = RSCDRRM020NDSE3_ADC_TEMPERATURE | RSCDRRM020NDSE3_ADC_1000HZ | RSCDRRM020NDSE3_ADC_FAST; 
                }
                else
                {//pressure next
                    send_buf[2] = RSCDRRM020NDSE3_ADC_PRESSURE | pctWorkModeFreq->freq_cfg | pctWorkModeFreq->mode;
                }
                send_buf[3] = 0xFF;
                ret = rscdrrm020ndse3_spi_adc_transfer(send_buf, recv_buf, sizeof(send_buf));
                if (RT_EOK == ret)
                {
					/*! pressure data
						Pressure data are output starting with MSB, in 24-bit 2’s complement format.
					 */
                    pressure = (((uint32_t)recv_buf[0] << 16 & 0x00FF0000)
                                | (((uint32_t)recv_buf[1] << 8) & 0x0000FF00)
                                | ((uint32_t)recv_buf[2] & 0x000000FF));
                    /* lock */
                    rscdrrm020ndse3_lock(rscdrrm020ndse3);

                    /* request auto zero */
                    if (rscdrrm020ndse3->auto_zero)
                    {
                        /* samples min max sum count */
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
                        { // max samples
                            /* remove max min calculate average */
                            uint32_t avg_pressure = (rscdrrm020ndse3_filter_sum - rscdrrm020ndse3_filter_min_val - rscdrrm020ndse3_filter_max_val) / (rscdrrm020ndse3_filter_sample_cnt - 2);
                            pressure = avg_pressure;

                            /* clear auto zero flag */
                            rscdrrm020ndse3->auto_zero = false ;
                            /* temporary save callback function */
                            AUTO_ZERO_CPL_FUNC pfnAutoZeroCompleted = s_pfnAutoZeroCompleted;
                            /* clear callback function pointer */
                            s_pfnAutoZeroCompleted = NULL;
                            /* init filter vars */
                            rscdrrm020ndse3_filter_sum = 0;
                            rscdrrm020ndse3_filter_sample_cnt = 0;
							rscdrrm020ndse3_filter_min_val = 0xFFFFFFFF;
							rscdrrm020ndse3_filter_max_val = 0;

                            /* unlock */
                            rscdrrm020ndse3_unlock(rscdrrm020ndse3);

                            /* set auto zero param */
                            AutoZero_Pressure(avg_pressure, temperature);

                            /* if set callback function */
                            if (s_pfnAutoZeroCompleted)
                            {//into callback function
                                pfnAutoZeroCompleted();
                            }
                        }
                        else
                        {
                            /* unlock */
                            rscdrrm020ndse3_unlock(rscdrrm020ndse3);                            
                        }   
                    }
                    else
                    {
                        /* unlock */
                        rscdrrm020ndse3_unlock(rscdrrm020ndse3);
                    }
                    /* temperature compensation and output */
                    CompReturn_Struct result = Compensate_Pressure(pressure, temperature);
                    if (PRESSURE_VALID == result.CompStatus)
                    {// get valid compensation pressure
                        /* save compensation pressure */
                        rscdrrm020ndse3->pressure_comp = result.f32PressureOutput;

                        /* invoke callback */
                        if (rscdrrm020ndse3->parent.rx_indicate != RT_NULL)
                        {
                            rscdrrm020ndse3->parent.rx_indicate(&rscdrrm020ndse3->parent,4);
                        }                        
                    } 
                }                
            }
            else //temperature
            {
                /* turn temperature mode */
                rscdrrm020ndse3->mode = rscdrrm020ndse3_next_mode(rscdrrm020ndse3);
                rscdrrm020ndse3_unlock(rscdrrm020ndse3);

                /* read temperature and turn to read pressure mode */
                uint8_t send_buf[4] = {0};
				uint8_t recv_buf[4] = {0};
				send_buf[0] = 0xFF;
				send_buf[1] = 0x40 | ((0x01 & 0x03) << 2) | ((1 - 1) & 0x03); // WREG command [0100 RRNN],
				const WorkModeFreq_T* pctWorkModeFreq = &(s_tModeFreqTbl[rscdrrm020ndse3->freq_index]);
				if (RSCDRRM020NDSE3_TEMPERATURE == rscdrrm020ndse3->mode)
				{ // read temperature
					send_buf[2] = RSCDRRM020NDSE3_ADC_TEMPERATURE | RSCDRRM020NDSE3_ADC_1000HZ | RSCDRRM020NDSE3_ADC_FAST; // fast mode read pressure incase interference pressure data
				}
				else // if (RSCDRRM020NDSE3_PRESSURE == rscdrrm020ndse3->mode)
				{ // read pressure
					send_buf[2] = RSCDRRM020NDSE3_ADC_PRESSURE | pctWorkModeFreq->freq_cfg | pctWorkModeFreq->mode;
				}
				send_buf[3] = 0xFF;
				ret = rscdrrm020ndse3_spi_adc_transfer(send_buf, recv_buf, sizeof(send_buf));
                if (RT_EOK == ret)
                {
                    /*! process temperature data 
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

/*!
 * \fn      rscdrrm020ndse3_thread_entry()
 * \brief   sensor thread
 */
static rt_err_t rscdrrm020ndse3_init(rt_device_t dev)
{
    struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
    LOG_D("rscdrrm020ndse3_init()");

    /* create event */
    rscdrrm020ndse3_event = rt_event_create("rscdrrm020ndse3", RT_IPC_FLAG_FIFO);
    if (RT_NULL == rscdrrm020ndse3_event)
    {
		LOG_E("rscdrrm020ndse3_init() call rt_event_create(rscdrrm020ndse3) failed!\r\n");
        return -RT_ERROR;
    }

    /* create thread */
    rscdrrm020ndse3_thread = rt_thread_create("rscdrrm020dse3", rscdrrm020ndse3_thread_entry, (void*)rscdrrm020ndse3, 1024, 5, 10);
    if (RT_NULL == rscdrrm020ndse3_thread)
    {
		LOG_E("rscdrrm020ndse3_init() call rt_thread_create(rscdrrm020ndse3) failed!\r\n");
        return -RT_ERROR;
    }
    rt_thread_startup(rscdrrm020ndse3_thread);

    /* open sensor power */
    rscdrrm020ndse3_power_on(dev);

    /* malloc buffer save eeprom parameter */
    uint8_t* eeprom_buf = (uint8_t*)rt_malloc(RSCDRRM020NDSE3_EEPROM_SIZE);
    if (RT_NULL == eeprom_buf)
    {
        /* shut down sensor power */
        rscdrrm020ndse3_power_off(dev);
        LOG_E("rscdrrm020ndse3_init() call rt_malloc(RSCDRRM020NDSE3_EEPROM_SIZE) failed!");
		return -RT_ENOMEM;
    }

    /* read eeprom to buffer */
    rt_err_t ret = rscdrrm020ndse3_spi_read_eeprom(0x00, eeprom_buf, RSCDRRM020NDSE3_EEPROM_SIZE);
    if (RT_EOK != ret)
    {
        /* free malloc */
        rt_free(eeprom_buf);

        /* shut down sensor power */
        LOG_E("rscdrrm020ndse3_init() call rscdrrm020ndse3_spi_read_eeprom(0,%d) failed, error(%d)!", 
		RSCDRRM020NDSE3_EEPROM_SIZE, ret);

		return ret;
    }

    /* init compensation function */
    CompStatus_Enum comp_ret = Compensate_Pressure_Init(eeprom_buf);
    if (COMPINIT_OK != comp_ret)
    {
        /* free malloc */
        rt_free(eeprom_buf);

        /* shut down sensor buffer */
        rscdrrm020ndse3_power_off(dev);
        LOG_E("rscdrrm020ndse3_init() call Compensate_Pressure_Init(eeprom_buf) failed, error(%d)!", comp_ret);
		
        return -RT_ERROR;
    }
    /* save adc parameter */
	/*!
	Initialize all four configuration registers to the default values in the EEPROM’s
    Relative addresses 61, 63, 65 and 67
	 */
    rscdrrm020ndse3->adc_cfg_param[0] = eeprom_buf[61];
    rscdrrm020ndse3->adc_cfg_param[1] = eeprom_buf[63];
    rscdrrm020ndse3->adc_cfg_param[2] = eeprom_buf[65];
    rscdrrm020ndse3->adc_cfg_param[3] = eeprom_buf[67];
    
    /* free malloc */
    rt_free(eeprom_buf);

    /* shut down sensor power */
    rscdrrm020ndse3_power_off(dev);

    /* clear start status */
    rscdrrm020ndse3->start = false;

    /* reset result */
    rscdrrm020ndse3->pressure_comp = 0.0;
    rscdrrm020ndse3->temperature   = 0;

    /* reset pressure counts */
    pressure_continuous_cnt = 0;

    return RT_EOK;
}

/*!
 * \fn      rscdrrm020ndse3_control()
 * \brief   control sensor device start/stop/auto zero/set freqence/get freqence/get temperature
 */
static rt_err_t rscdrrm020ndse3_control(rt_device_t dev, int cmd, void *args)
{ 
    LOG_D("rscdrrm020ndse3_control() cmd=0x%x", cmd);

    rt_err_t ret = RT_EOK;

    switch (cmd)
    {
        case RSCDRRM020NDSE3_START:
        {
            /* start sensor device */
            ret = rscdrrm020ndse3_start(dev);
            break;
        }
        case RSCDRRM020NDSE3_STOP :
        {
            /* stop sensor device */
            ret = rscdrrm020ndse3_stop(dev);
        }
        case RSCDRRM020NDSE3_AUTO_ZERO :
        {
            AUTO_ZERO_CPL_FUNC pfnAutoZeroCompleted = (AUTO_ZERO_CPL_FUNC)args;
            /* request auto zero */
            ret = rscdrrm020ndse3_auto_zero(dev, pfnAutoZeroCompleted);
            break;		      
        }
        case RSCDRRM020NDSE3_SET_FREQ :
        {	
            uint32_t u32FreqIndex = (uint32_t)args;
            /* set freqence */
            ret = rscdrrm020ndse3_set_freq(dev, u32FreqIndex);
            break;
            
        }
        case RSCDRRM020NDSE3_GET_FREQ :
        {	
            uint32_t* pu32FreqIndex = (uint32_t*)args;
            /* read freqence */
            ret = rscdrrm020ndse3_get_freq(dev, pu32FreqIndex);
            break;      
        }
        case RSCDRRM020NDSE3_GET_TEMP :
        {	
            float* pfTemperature = (float*)args;
            /* read temperature ℃ */
            ret = rscdrrm020ndse3_get_temperature(dev, pfTemperature);
            break;        
        }
        default:
        {		
            ret = -RT_ERROR;
            LOG_E("rscdrrm020ndse3_control() failed, unsupported cmd(0x%x)!\r\n", cmd);
            break;
        }
    }

    return ret;
}

/*!
 * \fn      rscdrrm020ndse3_open()
 * \brief   open the rscdrrm020ndse3 device
 */
static rt_err_t rscdrrm020ndse3_open(rt_device_t dev, uint16_t oflag)
{
    LOG_D("rscdrrm020ndse3_open() oflag=0x%x\r\n", oflag);
    struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;

    /* open sensor power */
    rscdrrm020ndse3_power_on(dev);

    /* config sensor data ready interrupt */
    rt_err_t ret =rt_pin_attach_irq(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_MODE_FALLING, rscdrrm020ndse3_rdy_isr, rscdrrm020ndse3);
	if (RT_EOK != ret)
	{
		LOG_E("rscdrrm020ndse3_open() call rt_pin_attach_irq(RSCDRRM020NDSE3_RDY_PIN) failed, error(%d)!\r\n", ret);
		return ret;
	}

    /* sensor data ready disable */
    ret = rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE);
 	if (RT_EOK != ret)
	{
		LOG_E("rscdrrm020ndse3_open() call rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE) failed, error(%d)!\r\n", ret);
		return ret;
	}

    rscdrrm020ndse3_lock(dev); 

    /* init start status */
    rscdrrm020ndse3->start = false;

    /* reset result */
 	rscdrrm020ndse3->pressure_comp = 0.0;
	rscdrrm020ndse3->temperature = 0;
	
	/* reset continuous count */
	pressure_continuous_cnt = 0;
	
	/* set default frequence */
	rscdrrm020ndse3->freq_index = RSCDRRM020NDSE3_ADC_DEFAULT_FREQ_INDEX;
	
	rscdrrm020ndse3_unlock(dev);
	
    return RT_EOK;
}  

/*!
 * \fn      rscdrrm020ndse3_close()
 * \brief   close the rscdrrm020ndse3 device
 */
static rt_err_t rscdrrm020ndse3_close(rt_device_t dev)
{
	LOG_D("rscdrrm020ndse3_close()\r\n");
	
	struct rscdrrm020ndse3_device* rscdrrm020ndse3 = (struct rscdrrm020ndse3_device*)dev;
	
	rscdrrm020ndse3_lock(dev);
	
	/* set stop flag */
	rscdrrm020ndse3->start = false;
	
	/* clear result */
	rscdrrm020ndse3->pressure_comp = 0.0;
	rscdrrm020ndse3->temperature = 0;
	
	/* reset pressure count */
	pressure_continuous_cnt = 0;
	
	rscdrrm020ndse3_unlock(dev);
	
	/* disable sensor ready pin */
	rt_pin_irq_enable(RSCDRRM020NDSE3_RDY_PIN, PIN_IRQ_DISABLE);
	
	/* detach sensor data interrupt */
	rt_pin_detach_irq(RSCDRRM020NDSE3_RDY_PIN);
	
	/* shut down sensor power */
	rscdrrm020ndse3_power_off(dev);
	
    return RT_EOK;
}

/*!
 * \fn      rscdrrm020ndse3_read()
 * \brief   read the rscdrrm020ndse3 device
 */
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

/*!
 * \fn      rscdrrm020ndse3_hw_init()
 * \brief   init the rscdrrm020ndse3 hw device
 */
int rscdrrm020ndse3_hw_init(void)
{
    LOG_D("rscdrrm020ndse3_hw_init()\r\n");
    
    /* create and init spi eeprom (CS_EE pin: PE15) */
    rt_err_t ret = rt_hw_spi_device_attach(RSCDRRM020NDSE3_SPI_BUS_NAME,
        RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME, GPIOE, GPIO_PIN_15);
     if (RT_EOK != ret)
    {
		LOG_E("rscdrrm020ndse3_hw_init() call rt_hw_spi_device_attach(%s, %s) failed, error(%d)!\r\n", 
			RSCDRRM020NDSE3_SPI_BUS_NAME, RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME, ret);
		return ret;
    }
		
	struct rt_spi_device* spi_ee_device = (struct rt_spi_device*)rt_device_find(RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME);
    if (RT_NULL == spi_ee_device)
    {
		LOG_E("rscdrrm020ndse3_hw_init() call rt_device_find(%s) failed!\r\n", 
			RSCDRRM020NDSE3_SPI_EE_DEVICE_NAME);
		return -RT_ERROR;
    }

    /* config eeprom spi device */
    {
		/*! EEPROM Communications in datasheet P20
         EEPROM operates in SPI mode 0 where CPOL = 0 and CPHA = 0 
        (0,0) and mode 3 where CPOL = 1 and CPHA = 1 (1,1) 
         */
		struct rt_spi_configuration cfg = {0};
		cfg.data_width = 8;
		cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible Modes 0 (CPOL = 0, CPHA = 0) */
		cfg.max_hz = 5 * 1000 * 1000; /* SPI Interface with Clock Speeds Up to 5 MHz */
		ret = rt_spi_configure(spi_ee_device, &cfg);
		if (RT_EOK != ret)
		{
			LOG_E("rscdrrm020ndse3_hw_init() call rt_spi_configure(spi_ee_device) failed, error(%d)!\r\n", ret);
			return ret;
		}
    }

    /* save eeprom spi device */
    rscdrrm020ndse3_dev.spi_ee_device = spi_ee_device;

    /* create and init spi adc device */
  	ret = rt_hw_spi_device_attach(RSCDRRM020NDSE3_SPI_BUS_NAME, 
		RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME, GPIOB, GPIO_PIN_10);
    if (RT_EOK != ret)
    {
		LOG_E("rscdrrm020ndse3_hw_init() call rt_hw_spi_device_attach(%s, %s) failed, error(%d)!\r\n", 
			RSCDRRM020NDSE3_SPI_BUS_NAME, RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME, ret);
		return ret;
    }
		
	struct rt_spi_device* spi_adc_device = (struct rt_spi_device*)rt_device_find(RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME);
    if (RT_NULL == spi_adc_device)
    {
		LOG_E("rscdrrm020ndse3_hw_init() call rt_device_find(%s) failed!\r\n", 
			RSCDRRM020NDSE3_SPI_ADC_DEVICE_NAME);
		return -RT_ERROR;
    }  

    /* config adc spi device */
    {
        /*! ADC Communications and Initialization in datasheet P21
        The ADC interface operates in SPI mode 1 where CPOL = 0 and CPHA = 1 
         */
        struct rt_spi_configuration cfg = { 0 };
        cfg.data_width = 8;        
        cfg.mode       = RT_SPI_MODE_1 | RT_SPI_MSB;/* SPI Compatible Modes 1 (CPOL = 0, CPHA = 1) */
        cfg.max_hz     = 5 * 1000 * 1000; /* SPI Interface with Clock Speeds Up to 5 MHz */
        ret = rt_spi_configure(spi_adc_device, &cfg);
        	if (RT_EOK != ret)
            {
                LOG_E("rscdrrm020ndse3_hw_init() call rt_spi_configure(spi_adc_device) failed, error(%d)!\r\n", ret);
                return ret;
            }
       }

       /*  save adc spi device */
       rscdrrm020ndse3_dev.spi_adc_device = spi_adc_device;

       /* init er-thread device struct */
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
    rt_pin_write(RSCDRRM020NDSE3_PWER_EN_PIN, PIN_LOW); //shut down power in init
    rt_pin_mode(RSCDRRM020NDSE3_PWER_EN_PIN, PIN_MODE_OUTPUT);

    /* set RDY pin mode to input */
    rt_pin_mode(RSCDRRM020NDSE3_RDY_PIN, PIN_MODE_INPUT_PULLUP);

    /* clear adc parameter */
    rt_menset(rscdrrm020ndse3_dev.adc_cfg_param, 0, sizeof(rscdrrm020ndse3_dev.adc_cfg_param));

    /* clear start flag */
    rscdrrm020ndse3_dev.start = false;

    /* clear result */
    rscdrrm020ndse3_dev.pressure_comp = 0.0;
    rscdrrm020ndse3_dev.temperature   = 0;

    /* reset pressure count */
    pressure_continuous_cnt = 0;

    /* init device lock */
    re_mutex_init(&(rscdrrm020ndse3_dev.lock),"rscdrrm020ndse3", RT_IPC_FLAG_FIFO);

    /* register a character device */
    ret = rt_device_register(&(rscdrrm020ndse3_dev.parent), RSCDRRM020NDSE3_DEVICE_NAME,
        RT_DEVICE_FLAG_STANDALONE | RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_INT_RX);
 	
     if (RT_EOK != ret)
    {
        LOG_E("rscdrrm020ndse3_hw_init() call rt_device_register(%s) failed, error(%d)!\r\n", 
			RSCDRRM020NDSE3_DEVICE_NAME, ret);
		return ret;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rscdrrm020ndse3_hw_init);





/*
 --------------------------------------------------------------------------------
    Global Function Definitions
 --------------------------------------------------------------------------------
 */

/*
* Function: cmd_init()
* Descriptions: This function will initialize cmd parser
* Author: Eric
* Returns:
* Parameter:
* History:
*/

/*
 -------------------------------------------------------------------------------
    Exported Function Declarations
 -------------------------------------------------------------------------------
 */

