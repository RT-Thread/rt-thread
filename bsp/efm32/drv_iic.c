/******************************************************************//**
 * @file 		drv_iic.c
 * @brief 	Serial API of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
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
 * 2011-06-17	onelife		Modify init function for efm32lib v2 upgrading
 *********************************************************************/

/******************************************************************//**
 * @addtogroup efm32
 * @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include "hdl_interrupt.h"
#include "drv_iic.h"

#if (defined(RT_USING_IIC0) || defined(RT_USING_IIC1))
/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
#ifdef RT_IIC_DEBUG
#define iic_debug(format,args...) 			rt_kprintf(format, ##args)
#else
#define iic_debug(format,args...)
#endif

/* Private variables ------------------------------------------------------------*/
#ifdef RT_USING_IIC0
#if (RT_USING_IIC0 > 3)
	#error "The location number range of IIC is 0~3"
#endif
	struct rt_device iic0_device;
	static struct rt_device iic0_rx_index;
#endif

#ifdef RT_USING_IIC1
#if (RT_USING_IIC1 > 3)
	#error "The location number range of IIC is 0~3"
#endif
	struct rt_device 		iic1_device;
	static struct rt_device iic1_rx_index;
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
		iic->rx_buffer = RT_NULL;
		iic->state = 0;

		dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
	}

	return RT_EOK;
}

/******************************************************************//**
 * @brief
 *   Open IIC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] oflag
 *   Device open flag
 *
 * @return
 *   Error code
 *********************************************************************/
static rt_err_t rt_iic_open(rt_device_t dev, rt_uint16_t oflag)
{
	RT_ASSERT(dev != RT_NULL);

	iic_debug("IIC: Open with flag %x\n", oflag);
	return RT_EOK;
}

/******************************************************************//**
 * @brief
 *   Close IIC device
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
static rt_err_t rt_iic_close(rt_device_t dev)
{
	struct efm32_iic_device_t	*iic;
	
	iic = (struct efm32_iic_device_t *)(dev->user_data);

	rt_free(iic->rx_buffer->data_ptr);
	rt_free(iic->rx_buffer);
	iic->rx_buffer = RT_NULL;
	
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

	if (iic->state & IIC_STATE_MASTER)
	{
		seq.addr = iic->slave_address;
		seq.flags = I2C_FLAG_WRITE_READ;
		/* Select register to be read */
		seq.buf[0].data = data;
		seq.buf[0].len = 1;
		/* Select location/length of data to be read */
		seq.buf[1].data = (rt_uint8_t *)buffer;
		seq.buf[1].len = size;

		/* Do a polled transfer */
		ret = I2C_TransferInit(iic->iic_device, &seq);
		while (ret == i2cTransferInProgress)
		{
		  ret = I2C_Transfer(iic->iic_device);
		}
	
		if (ret != i2cTransferDone)
		{
			iic_debug("IIC0 read error: %x\n", ret);
			iic_debug("IIC0 read address: %x\n", seq.addr);
			iic_debug("IIC0 read data0: %x -> %x\n", seq.buf[0].data, *seq.buf[0].data);
			iic_debug("IIC0 read len0: %x\n", seq.buf[0].len);
			iic_debug("IIC0 read data1: %x -> %x\n", seq.buf[1].data, *seq.buf[1].data);
			iic_debug("IIC0 read len1: %x\n", seq.buf[1].len);
			err_code = (rt_err_t)ret;
		}
		else
		{
			read_size = size;
			iic_debug("IIC0 read size: %d\n", read_size);
		}
	}
	else
	{
		rt_uint8_t* ptr;

		ptr = buffer;

		/* interrupt mode Rx */
		while (size)
		{
			rt_base_t level;
			struct efm32_iic_int_mode_t *int_rx;

			int_rx = iic->rx_buffer;

			/* disable interrupt */
			level = rt_hw_interrupt_disable();

			if (int_rx->read_index != int_rx->save_index)
			{
				/* read a character */
				*ptr++ = int_rx->data_ptr[int_rx->read_index];
				size--;

				/* move to next position */
				int_rx->read_index ++;
				if (int_rx->read_index >= IIC_RX_BUFFER_SIZE)
				{
					int_rx->read_index = 0;
				}
			}
			else
			{
				/* set error code */
				err_code = -RT_EEMPTY;

				/* enable interrupt */
				rt_hw_interrupt_enable(level);
				break;
			}

			/* enable interrupt */
			rt_hw_interrupt_enable(level);
		}

		read_size = (rt_uint32_t)ptr - (rt_uint32_t)buffer;
		iic_debug("IIC0 slave read size: %d\n", read_size);
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

	if (iic->state & IIC_STATE_MASTER)
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
		// TODO: Slave mode TX
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
	 RT_ASSERT(dev != RT_NULL);

	struct efm32_iic_device_t *iic;

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

	case RT_DEVICE_CTRL_IIC_SETTING:
		{
			/* change device setting */
			struct efm32_iic_control_t *control;

			control = (struct efm32_iic_control_t *)args;
			iic->state = control->config & (IIC_STATE_MASTER | IIC_STATE_BROADCAST);
			iic->master_address = control->master_address << 1;
			iic->slave_address = control->slave_address << 1;

			if (!(iic->state & IIC_STATE_MASTER))
			{
				if (iic->rx_buffer == RT_NULL)
				{
					iic->rx_buffer = rt_malloc(sizeof(struct efm32_iic_int_mode_t));
					if (iic->rx_buffer == RT_NULL)
					{
						iic_debug("no memory for IIC RX structure\n");
						return -RT_ENOMEM;
					}

					/* Allocate RX buffer */
					if ((iic->rx_buffer->data_ptr = \
						rt_malloc(IIC_RX_BUFFER_SIZE)) == RT_NULL)
					{
						iic_debug("no memory for IIC RX buffer\n");
						rt_free(iic->rx_buffer);
						return -RT_ENOMEM;
					}
					rt_memset(iic->rx_buffer->data_ptr, 0, IIC_RX_BUFFER_SIZE);
					iic->rx_buffer->data_size = IIC_RX_BUFFER_SIZE;
					iic->rx_buffer->read_index = 0;
					iic->rx_buffer->save_index = 0;
				}
			
				/* Enable slave mode */
				I2C_SlaveAddressSet(iic->iic_device, iic->slave_address);
				I2C_SlaveAddressMaskSet(iic->iic_device, 0xFF);
				iic->iic_device->CTRL |= I2C_CTRL_SLAVE | I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;

				/* Enable interrupts */
				I2C_IntEnable(iic->iic_device, I2C_IEN_ADDR | I2C_IEN_RXDATAV | I2C_IEN_SSTOP);
				I2C_IntClear(iic->iic_device, _I2C_IFC_MASK);
				
				/* Enable I2Cn interrupt vector in NVIC */
#ifdef RT_USING_IIC0
				if (dev == &iic0_device)
				{
					NVIC_ClearPendingIRQ(I2C0_IRQn);
					NVIC_SetPriority(I2C0_IRQn, EFM32_IRQ_PRI_DEFAULT);
					NVIC_EnableIRQ(I2C0_IRQn);
				}
#endif
#ifdef RT_USING_IIC1
				if (dev == &iic1_device)
				{
					NVIC_ClearPendingIRQ(I2C1_IRQn);
					NVIC_SetPriority(I2C1_IRQn, EFM32_IRQ_PRI_DEFAULT);
					NVIC_EnableIRQ(I2C1_IRQn);
				}
#endif
			}
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
		(flag & RT_DEVICE_FLAG_INT_TX))
	{
		RT_ASSERT(0);
	}

	device->type 		= RT_Device_Class_I2C;
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
 *	IIC slave mode RX data valid interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *	Pointer to device descriptor
 *********************************************************************/
static void rt_hw_iic_slave_isr(rt_device_t dev)
{
 	struct efm32_iic_device_t 	*iic;
	struct efm32_iic_int_mode_t *int_rx;
	rt_uint32_t 				status;
	volatile rt_uint32_t 		temp;

	/* interrupt mode receive */
	RT_ASSERT(dev->flag & RT_DEVICE_FLAG_INT_RX);

	iic = (struct efm32_iic_device_t*)dev->user_data;
	int_rx = iic->rx_buffer;
	status = iic->iic_device->IF;

	if (status & I2C_IF_ADDR)
	{
		/* Address Match */ 
		/* Indicating that reception is started */
		temp = iic->iic_device->RXDATA & 0xFFUL;
		if ((temp != 0x00) || (iic->state & IIC_STATE_BROADCAST))
		{
			iic->state |= IIC_STATE_RX_BUSY;
		}
	} 
	else if (status & I2C_IF_RXDATAV)
	{
		if (iic->state & IIC_STATE_RX_BUSY)
		{
			rt_base_t level;
			
			/* disable interrupt */
			level = rt_hw_interrupt_disable();

			/* save character */
			int_rx->data_ptr[int_rx->save_index] = \
				(rt_uint8_t)(iic->iic_device->RXDATA & 0xFFUL);
			int_rx->save_index ++;
			if (int_rx->save_index >= IIC_RX_BUFFER_SIZE)
				int_rx->save_index = 0;

			/* if the next position is read index, discard this 'read char' */
			if (int_rx->save_index == int_rx->read_index)
			{
				int_rx->read_index ++;
				if (int_rx->read_index >= IIC_RX_BUFFER_SIZE)
				{
					int_rx->read_index = 0;
				}
			}

			/* enable interrupt */
			rt_hw_interrupt_enable(level);
		}
		else
		{
			temp = iic->iic_device->RXDATA;
		}
	}

	if(status & I2C_IF_SSTOP)
	{
		/* Stop received, reception is ended */
		iic->state &= ~(rt_uint8_t)IIC_STATE_RX_BUSY;
	}
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
static struct efm32_iic_device_t *rt_hw_iic_unit_init(
	rt_device_t device,
	rt_uint8_t 	unitNumber, 
	rt_uint8_t 	location)
{
	struct efm32_iic_device_t 	*iic;
	CMU_Clock_TypeDef			iicClock;
	I2C_Init_TypeDef			init = I2C_INIT_DEFAULT;
	efm32_irq_hook_init_t		hook;

	do
	{
		/* Allocate device */
		iic = rt_malloc(sizeof(struct efm32_iic_device_t));
		if (iic == RT_NULL)
		{
			iic_debug("no memory for IIC%d driver\n", unitNumber);
			break;
		}
		iic->state 			|= IIC_STATE_MASTER;
		iic->master_address	= 0x0000;
		iic->slave_address 	= 0x0000;
		iic->rx_buffer 		= RT_NULL;

		/* Initialization */
		if (unitNumber >= I2C_COUNT)
		{
			break;
		}
		switch (unitNumber)
		{
		case 0:
			iic->iic_device	= I2C0;
			iicClock 		= (CMU_Clock_TypeDef)cmuClock_I2C0;	
			break;

#if (I2C_COUNT > 1)
		case 1:
			iic->iic_device	= I2C1;
			iicClock  		= (CMU_Clock_TypeDef)cmuClock_I2C1; 
			break;
#endif

		default:
			break;
		}

		/* Enabling clock */
		CMU_ClockEnable(iicClock, true);  

		/* Reset */
		I2C_Reset(iic->iic_device);

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

		hook.type		= efm32_irq_type_iic;
		hook.unit		= unitNumber;
		hook.cbFunc 	= rt_hw_iic_slave_isr;
		hook.userPtr	= device;
		efm32_irq_hook_register(&hook);

		/* Enable SDZ and SCL pins and set location */
		iic->iic_device->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN | \
					(location << _I2C_ROUTE_LOCATION_SHIFT);

		/* Initializing IIC */
		init.enable = false;
		I2C_Init(iic->iic_device, &init);

		/* Abort current TX data and clear TX buffers */
		iic->iic_device->CMD = I2C_CMD_ABORT | I2C_CMD_CLEARPC | I2C_CMD_CLEARTX;

		return iic;
	} while(0);

	if (iic)
	{
		rt_free(iic);
	}
	rt_kprintf("IIC: Init failed!\n");
	return RT_NULL;
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

	flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

	/* register iic0 */
#ifdef RT_USING_IIC0
	if ((iic = rt_hw_iic_unit_init(&iic0_device, 0, RT_USING_IIC0)) != RT_NULL)
	{
		rt_hw_iic_register(&iic0_device, RT_IIC0_NAME, flag, iic);
	}
#endif

	/* register iic1 */
#ifdef RT_USING_IIC1
	if ((iic = rt_hw_iic_unit_init(&iic1_device, 1, RT_USING_IIC1)) != RT_NULL)
	{
		rt_hw_iic_register(&iic1_device, RT_IIC1_NAME, flag, iic);
	}
#endif
}

#endif
/******************************************************************//**
 * @}
*********************************************************************/
