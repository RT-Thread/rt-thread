/******************************************************************//**
 * @file 		drv_iic.c
 * @brief 	Serial API of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2009, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2011-01-06	onelife		Initial creation for EFM32
 *********************************************************************/

/******************************************************************//**
 * @addtogroup efm32
 * @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include "drv_iic.h"

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------*/
#ifdef RT_USING_IIC0
#if (RT_USING_IIC0 > 3)
	#error "The location number range of IIC is 0~3"
#endif
	struct rt_device iic0_device;
#endif

#ifdef RT_USING_IIC1
#if (RT_USING_IIC1 > 3)
	#error "The location number range of IIC is 0~3"
#endif
	struct rt_device iic1_device;
#endif

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *   Initialize IIC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 *********************************************************************/
static rt_err_t rt_iic_init (rt_device_t dev)
{
	struct efm32_iic_device_t* iic;

	iic = (struct efm32_iic_device_t*)dev->user_data;

	if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
	{
		/* Enable IIC */
		I2C_Enable(iic->iic_device, true);

		dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
	}

	return RT_EOK;
}

static rt_err_t rt_iic_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_iic_close(rt_device_t dev)
{
	return RT_EOK;
}

/******************************************************************//**
 * @brief
 *   Read from IIC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] pos
 *   Offset
 *
 * @param[in] buffer
 *   Poniter to the buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *   Error code
 *********************************************************************/
static rt_size_t rt_iic_read (
	rt_device_t 	dev, 
	rt_off_t 		pos, 
	void* 			buffer, 
	rt_size_t 		size)
{
	rt_err_t 					err_code;
	rt_size_t 					read_size;
	struct efm32_iic_device_t* 	iic;
	I2C_TransferSeq_TypeDef 	seq;
	I2C_TransferReturn_TypeDef 	ret;
	rt_uint8_t 					data[1];

	if (!size)
	{
		return 0;
	}

	err_code = RT_EOK;
	read_size = 0;
	iic = (struct efm32_iic_device_t*)dev->user_data;
	data[0] = (rt_uint8_t)(pos & 0x000000FF);

	if (iic->is_master)
	{
		seq.addr = iic->slave_address;
		seq.flags = I2C_FLAG_WRITE_READ;
		/* Select register to be read */
		seq.buf[0].data = data;
		seq.buf[0].len = 1;
		/* Select location/length of data to be read */
		seq.buf[1].data = (rt_uint8_t *)buffer;
		seq.buf[1].len = size;
	}
	else
	{
		//TODO
	}

	/* Do a polled transfer */
	ret = I2C_TransferInit(iic->iic_device, &seq);
	while (ret == i2cTransferInProgress)
	{
	  ret = I2C_Transfer(iic->iic_device);
	}

	if (ret != i2cTransferDone)
	{
#ifdef RT_IIC_DEBUG
		rt_kprintf("IIC0 read error: %x\n", ret);
		rt_kprintf("IIC0 read address: %x\n", seq.addr);
		rt_kprintf("IIC0 read data0: %x -> %x\n", seq.buf[0].data, *seq.buf[0].data);
		rt_kprintf("IIC0 read len0: %x\n", seq.buf[0].len);
		rt_kprintf("IIC0 read data1: %x -> %x\n", seq.buf[1].data, *seq.buf[1].data);
		rt_kprintf("IIC0 read len1: %x\n", seq.buf[1].len);
#endif
		err_code = (rt_err_t)ret;
	}
	else
	{
#ifdef RT_IIC_DEBUG
		rt_kprintf("IIC0 read size: %d\n", size);
#endif
		read_size = size;
	}

	/* set error code */
	rt_set_errno(err_code);
	return read_size;
}

/******************************************************************//**
 * @brief
 *   Write to IIC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] pos
 *   Offset
 *
 * @param[in] buffer
 *   Poniter to the buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *   Error code
 *********************************************************************/
static rt_size_t rt_iic_write (
	rt_device_t 	dev, 
	rt_off_t 		pos, 
	const void* 	buffer, 
	rt_size_t 		size)
{
	rt_err_t 					err_code;
	rt_size_t 					write_size;
	struct efm32_iic_device_t* 	iic;
	I2C_TransferSeq_TypeDef 	seq;
	I2C_TransferReturn_TypeDef 	ret;
	//rt_uint8_t 					data[1];

	if (!size)
	{
		return 0;
	}

	err_code = RT_EOK;
	write_size = 0;
	iic = (struct efm32_iic_device_t*)dev->user_data;
	//data[0] = (rt_uint8_t)(pos & 0x000000FF);

	if (iic->is_master)
	{
		seq.addr = iic->slave_address;
		if (pos != (rt_off_t)(-1))
		{
			seq.flags = I2C_FLAG_WRITE_WRITE;
			/* Select register to be write */
			seq.buf[0].data = (rt_uint8_t *)(pos & 0x000000FF);
			seq.buf[0].len = 1;
			/* Select location/length of data to be write */
			seq.buf[1].data = (rt_uint8_t *)buffer;
			seq.buf[1].len = size;
		}
		else
		{
			seq.flags = I2C_FLAG_WRITE;
			/* Select location/length of data to be write */
			seq.buf[0].data = (rt_uint8_t *)buffer;
			seq.buf[0].len = size;
		}
	}
	else
	{
		//TODO
	}

	/* Do a polled transfer */
	ret = I2C_TransferInit(iic->iic_device, &seq);
	while (ret == i2cTransferInProgress)
	{
	  ret = I2C_Transfer(iic->iic_device);
	}
	
	if (ret != i2cTransferDone)
	{
		err_code = (rt_err_t)ret;
	}
	else
	{
		write_size = size;
	}

	/* set error code */
	rt_set_errno(err_code);
	return write_size;
}

 /******************************************************************//**
 * @brief
 *   Configure IIC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] cmd
 *   IIC control command
 *
 * @param[in] args
 *   Arguments
 *
 * @return
 *   Error code
 *********************************************************************/
static rt_err_t rt_iic_control (
	rt_device_t 	dev, 
	rt_uint8_t 		cmd, 
	void 			*args)
{
	struct efm32_iic_device_t *iic;

	RT_ASSERT(dev != RT_NULL);
	iic = (struct efm32_iic_device_t*)dev->user_data;
	switch (cmd)
	{
	case RT_DEVICE_CTRL_SUSPEND:
		/* suspend device */
		dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
		I2C_Enable(iic->iic_device, false);
		break;

	case RT_DEVICE_CTRL_RESUME:
		/* resume device */
		dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
		I2C_Enable(iic->iic_device, true);
		break;

	case RT_DEVICE_CTRL_IIC:
		{
			/* change device setting */
			struct efm32_iic_control_t *control;

			control = (struct efm32_iic_control_t *)args;
			iic->is_master = control->is_master;
			iic->master_address = control->master_address << 1;
			iic->slave_address = control->slave_address << 1;
		}
		break;
	}

	return RT_EOK;
}

/******************************************************************//**
* @brief
*	Register IIC device
*
* @details
*
* @note
*
* @param[in] device
*	Pointer to device descriptor
*
* @param[in] name
*	Device name
*
* @param[in] flag
*	Configuration flags
*
* @param[in] iic
*	Pointer to IIC device descriptor 
*
* @return
*	Error code
*********************************************************************/
rt_err_t rt_hw_iic_register(
	rt_device_t		device, 
	const char		*name, 
	rt_uint32_t		flag, 
	struct efm32_iic_device_t *iic)
{
	RT_ASSERT(device != RT_NULL);

	if ((flag & RT_DEVICE_FLAG_DMA_TX) || (flag & RT_DEVICE_FLAG_DMA_RX) || 
		(flag & RT_DEVICE_FLAG_INT_TX) || (flag & RT_DEVICE_FLAG_INT_RX))
	{
		RT_ASSERT(0);
	}

	device->type 		= RT_Device_Class_Char;
	device->rx_indicate = RT_NULL;
	device->tx_complete = RT_NULL;
	device->init 		= rt_iic_init;
	device->open		= rt_iic_open;
	device->close		= rt_iic_close;
	device->read 		= rt_iic_read;
	device->write 		= rt_iic_write;
	device->control 	= rt_iic_control;
	device->user_data	= iic;

	/* register a character device */
	return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/******************************************************************//**
* @brief
*	Initialize the specified IIC unit 
*
* @details
*
* @note
*
* @param[in] unitNumber
*	Unit number
*
* @param[in] location
*	Pin location number 
*********************************************************************/
static void rt_hw_iic_unit_init(
	rt_uint8_t 	unitNumber, 
	rt_uint8_t 	location)
{
	I2C_TypeDef				*iic;
	CMU_Clock_TypeDef		iicClock;
	I2C_Init_TypeDef		init = I2C_INIT_DEFAULT;

	switch (unitNumber)
	{
	case 0:
		iic 		= I2C0;
		iicClock 	= (CMU_Clock_TypeDef)cmuClock_I2C0;	
		break;
#if (I2C_COUNT > 1)
	case 1:
		iic		  = I2C1;
		iicClock  = (CMU_Clock_TypeDef)cmuClock_I2C1; 
		break;
#endif
	default:
		return;
	}

	/* Enabling clock */
	CMU_ClockEnable(iicClock, true);  

	/* Reset */
	I2C_Reset(iic);

	/* Config GPIO */
	GPIO_PinModeSet(
		(GPIO_Port_TypeDef)AF_PORT(AF_I2C_SCL(unitNumber), location),
		AF_PIN(AF_I2C_SCL(unitNumber), location),
		gpioModeWiredAndPullUpFilter,
		1);
	GPIO_PinModeSet(
		(GPIO_Port_TypeDef)AF_PORT(AF_I2C_SDA(unitNumber), location),
		AF_PIN(AF_I2C_SDA(unitNumber), location),
		gpioModeWiredAndPullUpFilter,
		1);

	/* Enable SDZ and SCL pins and set location */
	iic->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN | \
				(location << _I2C_ROUTE_LOCATION_SHIFT);
	
	/* Initializing IIC */
	init.enable = false;
	I2C_Init(iic, &init);

	/* Abort current TX data and clear TX buffers */
	iic->CMD = I2C_CMD_ABORT | I2C_CMD_CLEARPC | I2C_CMD_CLEARTX;
	
	/* Clear previous interrupts */
	iic->IFC = _I2C_IFC_MASK;
}

/******************************************************************//**
* @brief
*	Initialize all IIC module related hardware and register IIC device to kernel
*
* @details
*
* @note
*********************************************************************/
void rt_hw_iic_init(void)
{
	struct efm32_iic_device_t *iic;
	rt_uint32_t flag;

	flag = RT_DEVICE_FLAG_RDWR;

	/* register iic0 */
#ifdef RT_USING_IIC0
	iic = rt_malloc(sizeof(struct efm32_iic_device_t));
	if (iic == RT_NULL)
	{
		rt_kprintf("no memory for IIC0 driver\n");
		return;
	}

	iic->iic_device = I2C0;
	iic->is_master = true;
	iic->master_address = 0x0000;
	iic->slave_address = 0x0000;
	rt_hw_iic_unit_init(0, RT_USING_IIC0);

	rt_hw_iic_register(&iic0_device, RT_IIC0_NAME, flag, iic);
#endif

		/* register iic1 */
#ifdef RT_USING_IIC1
	iic = rt_malloc(sizeof(struct efm32_iic_device_t));
	if (iic == RT_NULL)
	{
		rt_kprintf("no memory for IIC1 driver\n");
		return;
	}

	iic->iic_device = I2C1;
	iic->is_master = true;
	iic->master_address = 0x0000;
	iic->slave_address = 0x0000;
	rt_hw_iic_unit_init(1, RT_USING_IIC1);
	
	rt_hw_iic_register(&iic1_device, RT_IIC1_NAME, flag, iic);
#endif
}

/******************************************************************//**
 * @}
*********************************************************************/
