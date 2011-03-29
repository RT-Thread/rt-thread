/******************************************************************//**
 * @file 		drv_usart.c
 * @brief 	USART driver of RT-Thread RTOS for EFM32
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
 * 2010-12-22	onelife		Initial creation for EFM32
 * 2011-01-17	onelife		Merge with serial.c
 *
 * @section Change Logs of serial.c
 * 2009-02-05	Bernard		first version
 * 2009-10-25	Bernard		fix rt_serial_read bug when there is no data in the buffer.
 * 2010-03-29	Bernard		cleanup code.
 *********************************************************************/

/******************************************************************//**
 * @addtogroup efm32
 * @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include "hdl_interrupt.h"
#include "drv_usart.h"

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------*/
#ifdef RT_USING_USART0
#if (RT_USING_USART0 > 3)
	#error "The location number range of usart is 0~3"
#endif
	struct rt_device usart0_device;
#endif

#ifdef RT_USING_USART1
#if (RT_USING_USART1 > 3)
	#error "The location number range of usart is 0~3"
#endif
	struct rt_device usart1_device;
#endif

#ifdef RT_USING_USART2
#if (RT_USING_USART2 > 3)
	#error "The location number range of usart is 0~3"
#endif
	struct rt_device usart2_device;
#endif

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *   Initialize USART device
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
static rt_err_t rt_usart_init (rt_device_t dev)
{
	struct efm32_usart_device_t *usart;
	
	usart = (struct efm32_usart_device_t *)(dev->user_data);

	if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
	{
		if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
		{
			struct efm32_usart_dma_mode_t *dma_tx;

			dma_tx = (struct efm32_usart_dma_mode_t *)(usart->tx_mode);

			usart->state |= USART_STATE_RX_BUSY;
		}

		if (dev->flag & RT_DEVICE_FLAG_INT_RX)
		{
			struct efm32_usart_int_mode_t *int_rx;
			
			int_rx = (struct efm32_usart_int_mode_t *)(usart->rx_mode);
			
			int_rx->data_ptr = RT_NULL;
		}

		/* Enable USART */
		USART_Enable(usart->usart_device, usartEnable);

		dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
	}

	return RT_EOK;
}

/******************************************************************//**
 * @brief
 *   Open USART device
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
static rt_err_t rt_usart_open(rt_device_t dev, rt_uint16_t oflag)
{
	RT_ASSERT(dev != RT_NULL);

	struct efm32_usart_device_t	*usart;
	IRQn_Type 					rxIrq;
	
	usart = (struct efm32_usart_device_t *)(dev->user_data);

	//if (usart->state & USART_STATE_CONSOLE)
	{	/* Allocate new RX buffer */
		struct efm32_usart_int_mode_t	*int_mode;
		
		int_mode = (struct efm32_usart_int_mode_t *)(usart->rx_mode);

		if ((int_mode->data_ptr = rt_malloc(SERIAL_RX_BUFFER_SIZE)) == RT_NULL)
		{
#ifdef RT_USART_DEBUG
			rt_kprintf("no memory for serial RX buffer\n");
#endif
			return -RT_ENOMEM;
		}
		rt_memset(int_mode->data_ptr, 0, SERIAL_RX_BUFFER_SIZE);
		int_mode->data_size = SERIAL_RX_BUFFER_SIZE;
		int_mode->read_index = 0;
		int_mode->save_index = 0;
	}
	
	/* Enable TX/RX interrupt */	
	switch (usart->unit)
	{
	case 0:
		rxIrq 		= USART0_RX_IRQn;
		break;
	case 1:
		rxIrq		= USART1_RX_IRQn;
		break;
	case 2:
		rxIrq		= USART2_RX_IRQn;
		break;
	}

	/* Enable RX interrupts */
	usart->usart_device->IEN 	= USART_IEN_RXDATAV;
	usart->usart_device->IFC 	= _USART_IFC_MASK;

	/* Enable IRQ */
	if (oflag != RT_DEVICE_OFLAG_WRONLY)
	{
		NVIC_ClearPendingIRQ(rxIrq);
		NVIC_SetPriority(rxIrq, EFM32_IRQ_PRI_DEFAULT);
		NVIC_EnableIRQ(rxIrq);
	}
	if (oflag != RT_DEVICE_OFLAG_RDONLY)
	{
		/* DMA IRQ is enabled by DMA_Init() */
		NVIC_SetPriority(DMA_IRQn, EFM32_IRQ_PRI_DEFAULT);
	}

#ifdef RT_USART_DEBUG
		rt_kprintf("USART%d: Open with flag %x\n", usart->unit, oflag);
#endif

	return RT_EOK;
}

/******************************************************************//**
 * @brief
 *   Close USART device
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
static rt_err_t rt_usart_close(rt_device_t dev)
{
	struct efm32_usart_int_mode_t *int_rx;

	int_rx = (struct efm32_usart_int_mode_t *)\
		(((struct efm32_usart_device_t *)(dev->user_data))->rx_mode);
	
	rt_free(int_rx->data_ptr);
	int_rx->data_ptr = RT_NULL;
	
	return RT_EOK;
}

/******************************************************************//**
 * @brief
 *   Read from USART device
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
static rt_size_t rt_usart_read (
	rt_device_t 	dev, 
	rt_off_t 		pos, 
	void* 			buffer, 
	rt_size_t 		size)
{
	rt_uint8_t* ptr;
	rt_err_t 	err_code;

	ptr = buffer;
	err_code = RT_EOK;

	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* interrupt mode Rx */
		while (size)
		{
			rt_base_t level;
			struct efm32_usart_int_mode_t *int_rx;

			int_rx = (struct efm32_usart_int_mode_t *)\
				(((struct efm32_usart_device_t *)(dev->user_data))->rx_mode);

			/* disable interrupt */
			level = rt_hw_interrupt_disable();

			if (int_rx->read_index != int_rx->save_index)
			{
				/* read a character */
				*ptr++ = int_rx->data_ptr[int_rx->read_index];
				size--;

				/* move to next position */
				int_rx->read_index ++;
				if (int_rx->read_index >= SERIAL_RX_BUFFER_SIZE)
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
	}
	else
	{
		/* polling mode */
		USART_TypeDef *usart_device;

		RT_ASSERT(buffer != RT_NULL);
		usart_device = ((struct efm32_usart_device_t *)(dev->user_data))->usart_device;
			
		while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
		{
			while (usart_device->STATUS & USART_STATUS_RXDATAV)
			{
				*ptr = usart_device->RXDATA & 0xff;
				ptr ++;
			}
		}
	}

	/* set error code */
	rt_set_errno(err_code);
	return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

/******************************************************************//**
 * @brief
 *   Write to USART device
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
static rt_size_t rt_usart_write (
	rt_device_t 	dev, 
	rt_off_t 		pos, 
	const void* 	buffer, 
	rt_size_t 		size)
{
	rt_err_t 						err_code;
	rt_size_t 						write_size;
	struct efm32_usart_device_t* 	usart;

	err_code = RT_EOK;
	write_size = 0;
	usart = (struct efm32_usart_device_t*)(dev->user_data);

	if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
	{	/* DMA mode Tx */
		struct efm32_usart_dma_mode_t *dma_tx;
	
		if (dev->flag & RT_DEVICE_FLAG_STREAM)
		{
			*((rt_uint8_t *)buffer + size++) = '\r';
			*((rt_uint8_t *)buffer + size) = 0x0;
		}

		dma_tx = (struct efm32_usart_dma_mode_t *)(usart->tx_mode);
		dma_tx->data_ptr = (rt_uint32_t *)buffer;
		dma_tx->data_size = size;

		usart->state |= USART_STATE_TX_BUSY;

		DMA_ActivateBasic(
			dma_tx->dma_channel,
			true,
			false,
			(void *)&(usart->usart_device->TXDATA),
			buffer,
			size - 1);

		/* Wait, otherwise the TX buffer is overwrite */
		if (usart->state & USART_STATE_CONSOLE)
		{
			while(usart->state & USART_STATE_TX_BUSY);
		}
		else
		{
			while(usart->state & USART_STATE_TX_BUSY)
			{
				rt_thread_sleep(USART_WAIT_TIME_TX);
			}
		}
		
		write_size = size;
	}
	else
	{	/* polling mode */	
		rt_uint8_t* ptr = (rt_uint8_t*)buffer;
	
		if (dev->flag & RT_DEVICE_FLAG_STREAM)
		{
			/* stream mode */
			while (size)
			{
				if (*ptr == '\n')
				{
					while (!(usart->usart_device->STATUS & USART_STATUS_TXBL));
					usart->usart_device->TXDATA = '\r';
				}

				while (!(usart->usart_device->STATUS & USART_STATUS_TXBL));
				usart->usart_device->TXDATA = (rt_uint32_t)*ptr;

				++ptr; --size;
			}
		}
		else
		{
			/* write data directly */
			while (size)
			{
				while (!(usart->usart_device->STATUS & USART_STATUS_TXBL));
				usart->usart_device->TXDATA = (rt_uint32_t)*ptr;

				++ptr; --size;
			}
		}

		write_size = (rt_size_t)ptr - (rt_size_t)buffer;
	}

	/* set error code */
	rt_set_errno(err_code);
	return write_size;
}

/******************************************************************//**
* @brief
*	Configure USART device
*
* @details
*
* @note
*
* @param[in] dev
*	Pointer to device descriptor
*
* @param[in] cmd
*	IIC control command
*
* @param[in] args
*	Arguments
*
* @return
*	Error code
*********************************************************************/
static rt_err_t rt_usart_control (
	rt_device_t 	dev, 
	rt_uint8_t 		cmd, 
	void 			*args)
{
	RT_ASSERT(dev != RT_NULL);

	struct efm32_usart_device_t *usart;

	usart = (struct efm32_usart_device_t *)(dev->user_data);
	
	switch (cmd)
	{
	case RT_DEVICE_CTRL_SUSPEND:
		/* Suspend device */
		dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
		USART_Enable(usart->usart_device, usartDisable);
		break;

	case RT_DEVICE_CTRL_RESUME:
		/* Resume device */
		dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
		USART_Enable(usart->usart_device, usartEnable);
		break;

	case RT_DEVICE_CTRL_USART_RBUFFER:
		/* Set RX buffer */
		{
			struct efm32_usart_int_mode_t *int_rx;
			rt_uint8_t size;

			int_rx = (struct efm32_usart_int_mode_t *)(usart->rx_mode);
			size = (rt_uint8_t)((rt_uint32_t)args & 0xFFUL);

			/* Free previous RX buffer */
			if (int_rx->data_ptr != RT_NULL)
			{
				if (size == 0)
				{	/* Free RX buffer */
					rt_free(int_rx->data_ptr);
					int_rx->data_ptr = RT_NULL;
				}
				else if (size != int_rx->data_size)
				{
					/* Re-allocate RX buffer */
					if ((int_rx->data_ptr = rt_realloc(int_rx->data_ptr, size)) \
						== RT_NULL)
					{
#ifdef RT_USART_DEBUG
						rt_kprintf("no memory for usart rx buffer\n");
#endif
						return -RT_ENOMEM;
					}
					// TODO: Is the following line necessary?
					//rt_memset(int_rx->data_ptr, 0, size); 
				}
			}	
			else
			{
				/* Allocate new RX buffer */
				if ((int_rx->data_ptr = rt_malloc(size)) == RT_NULL)
				{
#ifdef RT_USART_DEBUG
					rt_kprintf("no memory for usart rx buffer\n");
#endif
					return -RT_ENOMEM;
				}
			}
			int_rx->data_size = size;
			int_rx->read_index = 0;
			int_rx->save_index = 0; 
		}
		break;

	}

	return RT_EOK;
}

/******************************************************************//**
 * @brief
 *	USART RX data valid interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *	Pointer to device descriptor
 *********************************************************************/
void rt_hw_usart_rx_isr(rt_device_t dev)
{
	struct efm32_usart_device_t 	*usart;
	struct efm32_usart_int_mode_t 	*int_rx;

	/* interrupt mode receive */
	RT_ASSERT(dev->flag & RT_DEVICE_FLAG_INT_RX);
	
	usart = (struct efm32_usart_device_t *)(dev->user_data);
	int_rx = (struct efm32_usart_int_mode_t *)(usart->rx_mode);

	RT_ASSERT(int_rx->data_ptr != RT_NULL);

	/* Set status */
	usart->state |= USART_STATE_RX_BUSY;
	
	/* save on rx buffer */
	while (usart->usart_device->STATUS & USART_STATUS_RXDATAV)
	{
		rt_base_t level;

		/* disable interrupt */
		level = rt_hw_interrupt_disable();

		/* save character */
		int_rx->data_ptr[int_rx->save_index] = \
			(rt_uint8_t)(usart->usart_device->RXDATA & 0xFFUL);
		int_rx->save_index ++;
		if (int_rx->save_index >= SERIAL_RX_BUFFER_SIZE)
			int_rx->save_index = 0;

		/* if the next position is read index, discard this 'read char' */
		if (int_rx->save_index == int_rx->read_index)
		{
			int_rx->read_index ++;
			if (int_rx->read_index >= SERIAL_RX_BUFFER_SIZE)
			{
				int_rx->read_index = 0;
			}
		}

		/* enable interrupt */
		rt_hw_interrupt_enable(level);
	}

	/* invoke callback */
	if (dev->rx_indicate != RT_NULL)
	{
		rt_size_t rx_length;

		/* get rx length */
		rx_length = int_rx->read_index > int_rx->save_index ?
			SERIAL_RX_BUFFER_SIZE - int_rx->read_index + int_rx->save_index : \
			int_rx->save_index - int_rx->read_index;

		dev->rx_indicate(dev, rx_length);
	}
}

/******************************************************************//**
 * @brief
 *	DMA for USART TX interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *	Pointer to device descriptor
 *********************************************************************/
void rt_hw_usart_dma_tx_isr(rt_device_t dev)
{
	/* DMA mode receive */
	struct efm32_usart_device_t 	*usart;
	struct efm32_usart_dma_mode_t 	*dma_tx;

	RT_ASSERT(dev->flag & RT_DEVICE_FLAG_DMA_TX);

	usart = (struct efm32_usart_device_t *)(dev->user_data);
	dma_tx = (struct efm32_usart_dma_mode_t *)(usart->tx_mode);

	/* invoke call to notify tx complete */
	if (dev->tx_complete != RT_NULL)
	{
		dev->tx_complete(dev, dma_tx->data_ptr);
	}

	/* Set status */
	usart->state &= ~(rt_uint32_t)USART_STATE_TX_BUSY;
}

/******************************************************************//**
* @brief
*	Register USART device
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
* @param[in] usart
*	Pointer to USART device descriptor 
*
* @return
*	Error code
*********************************************************************/
rt_err_t rt_hw_usart_register(
	rt_device_t		device, 
	const char		*name, 
	rt_uint32_t		flag, 
	struct efm32_usart_device_t *usart)
{
	RT_ASSERT(device != RT_NULL);

	if ((flag & RT_DEVICE_FLAG_DMA_RX) ||
		(flag & RT_DEVICE_FLAG_INT_TX))
	{
		RT_ASSERT(0);
	}

	device->type 		= RT_Device_Class_Char;
	device->rx_indicate = RT_NULL;
	device->tx_complete = RT_NULL;
	device->init 		= rt_usart_init;
	device->open		= rt_usart_open;
	device->close		= rt_usart_close;
	device->read 		= rt_usart_read;
	device->write 		= rt_usart_write;
	device->control 	= rt_usart_control;
	device->user_data	= usart;

	/* register a character device */
	return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/******************************************************************//**
* @brief
*	Initialize the specified USART unit 
*
* @details
*
* @note
*
* @param[in] device
*	Pointer to device descriptor
*
* @param[in] unitNumber
*	Unit number
*
* @param[in] location
*	Pin location number 
*
* @param[in] flag
*	Configuration flag
*
* @param[in] dmaChannel
*	DMA channel number for TX
*
* @param[in] console
*	Indicate if using as console 
*
* @return
*	Pointer to USART device  
*********************************************************************/
static struct efm32_usart_device_t *rt_hw_usart_unit_init(
	rt_device_t device,
	rt_uint8_t 	unitNumber, 
	rt_uint8_t 	location,
	rt_uint32_t flag,
	rt_uint32_t	dmaChannel,
	rt_bool_t 	console)
{
	struct efm32_usart_device_t 	*usart;
	struct efm32_usart_dma_mode_t	*dma_mode;
	CMU_Clock_TypeDef				usartClock;
	rt_uint32_t						txDmaSelect;
	USART_InitAsync_TypeDef			init;
	efm32_irq_hook_init_t			hook;

	/* Allocate device */
	usart = rt_malloc(sizeof(struct efm32_usart_device_t));
	if (usart == RT_NULL)
	{
#ifdef RT_USART_DEBUG
		rt_kprintf("no memory for USART driver\n");
#endif
		return usart;
	}
	usart->unit 	= unitNumber;
	if (console == true)
	{
		usart->state = USART_STATE_CONSOLE;
	}
	else
	{
		usart->state = 0;
	}
	usart->tx_mode 	= RT_NULL;
	usart->rx_mode 	= RT_NULL;

	/* Allocate TX */
	dma_mode = RT_NULL;
	if (flag & RT_DEVICE_FLAG_DMA_TX)
	{
		usart->tx_mode = dma_mode = rt_malloc(sizeof(struct efm32_usart_dma_mode_t));
		if (dma_mode == RT_NULL)
		{
#ifdef RT_USART_DEBUG
			rt_kprintf("no memory for USART TX by DMA\n");
#endif
			rt_free(usart->rx_mode);
			rt_free(usart);
			usart = RT_NULL;
			return usart;
		}
		dma_mode->dma_channel = dmaChannel;
	}

	/* Allocate RX */
	if (flag & RT_DEVICE_FLAG_INT_RX)
	{
		usart->rx_mode = rt_malloc(sizeof(struct efm32_usart_int_mode_t));
		if (usart->rx_mode == RT_NULL)
		{
#ifdef RT_USART_DEBUG
			rt_kprintf("no memory for USART RX by interrupt\n");
#endif
			rt_free(usart->tx_mode);
			rt_free(usart);
			usart = RT_NULL;
			return usart;
		}
	}

	/* Initialization */
	switch (unitNumber)
	{
	case 0:
		usart->usart_device	= USART0;
		usartClock 			= (CMU_Clock_TypeDef)cmuClock_USART0;
		txDmaSelect			= DMAREQ_USART0_TXBL;
		break;
		
	case 1:
		usart->usart_device	= USART1;
		usartClock 			= (CMU_Clock_TypeDef)cmuClock_USART1;
		txDmaSelect			= DMAREQ_USART1_TXBL;
		break;
		
	case 2:
		usart->usart_device	= USART2;
		usartClock 			= (CMU_Clock_TypeDef)cmuClock_USART2;
		txDmaSelect			= DMAREQ_USART2_TXBL;
		break;
	}

	/* Enable USART clock */
	CMU_ClockEnable(usartClock, true);

	/* Reset */
	USART_Reset(usart->usart_device);

	/* Config GPIO */
	GPIO_PinModeSet(
		(GPIO_Port_TypeDef)AF_PORT(AF_USART_TX(unitNumber), location),
		AF_PIN(AF_USART_TX(unitNumber), location),
		gpioModePushPull,
		0);
	GPIO_PinModeSet(
		(GPIO_Port_TypeDef)AF_PORT(AF_USART_RX(unitNumber), location),
		AF_PIN(AF_USART_RX(unitNumber), location),
		gpioModeInputPull,
		1);

	/* Config interrupt and NVIC */
	if (flag & RT_DEVICE_FLAG_INT_RX)
	{	
		hook.type		= efm32_irq_type_usart;
		hook.unit		= unitNumber * 2 + 1;
		hook.cbFunc 	= rt_hw_usart_rx_isr;
		hook.userPtr	= device;
		efm32_irq_hook_register(&hook);
	}

	/* Config DMA */
	if (flag & RT_DEVICE_FLAG_DMA_TX)
	{
		DMA_CB_TypeDef			*callback;
		DMA_CfgChannel_TypeDef	chnlCfg;
		DMA_CfgDescr_TypeDef	descrCfg;

		hook.type 			= efm32_irq_type_dma;
		hook.unit 			= dmaChannel;
		hook.cbFunc			= rt_hw_usart_dma_tx_isr;
		hook.userPtr 		= device;
		efm32_irq_hook_register(&hook);

		callback = (DMA_CB_TypeDef *)rt_malloc(sizeof(DMA_CB_TypeDef));
		callback->cbFunc	= DMA_IRQHandler_All;
		callback->userPtr	= RT_NULL;
		callback->primary	= 0;

		/* Setting up DMA channel */
		chnlCfg.highPri		= false;	/* Can't use with peripherals */
		chnlCfg.enableInt 	= true;		/* Interrupt for callback function */
		chnlCfg.select 		= txDmaSelect;		
		chnlCfg.cb			= callback;
		DMA_CfgChannel(dmaChannel, &chnlCfg);

		/* Setting up DMA channel descriptor */
		descrCfg.dstInc 	= dmaDataIncNone;
		descrCfg.srcInc 	= dmaDataInc1;
		descrCfg.size 		= dmaDataSize1;
		descrCfg.arbRate 	= dmaArbitrate1;
		descrCfg.hprot 		= 0;
		DMA_CfgDescr(dmaChannel, true, &descrCfg);			
	}

	/* Enable RX and TX pins and set location */
	usart->usart_device->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | \
					(location << _USART_ROUTE_LOCATION_SHIFT);

	/* Init specified USART unit */
	init.enable 		= usartEnable;
	init.refFreq		= 0;
	init.baudrate		= UART_BAUDRATE;
	init.oversampling	= USART_CTRL_OVS_X4;
	init.databits		= USART_FRAME_DATABITS_EIGHT;
	init.parity 		= USART_FRAME_PARITY_NONE;
	init.stopbits		= USART_FRAME_STOPBITS_ONE;
	USART_InitAsync(usart->usart_device, &init);

	/* Clear RX/TX buffers */
	usart->usart_device->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;

	return usart;
}

/******************************************************************//**
* @brief
*	Initialize all USART module related hardware and register USART device to kernel
*
* @details
*
* @note
*********************************************************************/
void rt_hw_usart_init(void)
{
	struct efm32_usart_device_t	*usart;
	rt_uint32_t 				flag;
	rt_bool_t					console;

	/* Register usart0 */
#ifdef RT_USING_USART0
	flag = RT_DEVICE_FLAG_RDWR;

 #if (RT_CONSOLE_DEVICE == 0x0UL)
	console = true;
	flag |= RT_DEVICE_FLAG_STREAM;
 #else
	console = false;
 #endif

 #ifdef RT_USART0_USING_DMA
 	RT_ASSERT(RT_USART0_USING_DMA < DMA_CHAN_COUNT);
	flag |= RT_DEVICE_FLAG_DMA_TX;
 #else
   #define RT_USART0_USING_DMA EFM32_NO_DATA
 #endif

	flag |= RT_DEVICE_FLAG_INT_RX;

	usart = rt_hw_usart_unit_init(
		&usart0_device, 
		0, 
		RT_USING_USART0, 
		flag, 
		RT_USART0_USING_DMA, 
		console);

	rt_hw_usart_register(&usart0_device, RT_USART0_NAME, flag, usart);
#endif

	/* Register usart1 */
#ifdef RT_USING_USART1
	flag = RT_DEVICE_FLAG_RDWR;

 #if (RT_CONSOLE_DEVICE == 0x1UL)
	console = true;
	flag |= RT_DEVICE_FLAG_STREAM;
 #else
	console = false;
 #endif

 #ifdef RT_USART1_USING_DMA
 	RT_ASSERT(RT_USART1_USING_DMA < DMA_CHAN_COUNT);
	flag |= RT_DEVICE_FLAG_DMA_TX;
 #else
	
   #define RT_USART1_USING_DMA EFM32_NO_DATA
 #endif

	flag |= RT_DEVICE_FLAG_INT_RX;
  
	usart = rt_hw_usart_unit_init(
		&usart1_device, 
		1, 
		RT_USING_USART1, 
		flag, 
		RT_USART1_USING_DMA, 
		console);

	rt_hw_usart_register(&usart1_device, RT_USART1_NAME, flag, usart);
#endif

	/* Register usart2 */
#ifdef RT_USING_USART2
	flag = RT_DEVICE_FLAG_RDWR;

 #if (RT_CONSOLE_DEVICE == 0x2UL)
	console = true;
	flag |= RT_DEVICE_FLAG_STREAM;
 #else
	console = false;
 #endif

 #ifdef RT_USART2_USING_DMA
 	RT_ASSERT(RT_USART2_USING_DMA < DMA_CHAN_COUNT);
	flag |= RT_DEVICE_FLAG_DMA_TX;

 #else
	
   #define RT_USART2_USING_DMA EFM32_NO_DATA
 #endif

	flag |= RT_DEVICE_FLAG_INT_RX;
  
	usart = rt_hw_usart_unit_init(
		&usart2_device, 
		2, 
		RT_USING_USART2, 
		flag, 
		RT_USART2_USING_DMA, 
		console);

	rt_hw_usart_register(&usart2_device, RT_USART2_NAME, flag, usart);
#endif
}

/******************************************************************//**
 * @}
*********************************************************************/
