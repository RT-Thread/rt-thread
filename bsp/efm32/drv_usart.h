/******************************************************************//**
 * @file 		drv_usart.h
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
 *********************************************************************/
#ifndef __DRV_USART_H__
#define __DRV_USART_H__

/* Includes -------------------------------------------------------------------*/
/* Exported types -------------------------------------------------------------*/
struct efm32_usart_int_mode_t
{
	rt_uint8_t  *data_ptr;
	rt_uint8_t  data_size;
	rt_uint32_t read_index, save_index;
};

struct efm32_usart_dma_mode_t
{
	/* DMA Channel */
	rt_uint32_t dma_channel;

	/* buffer info */
	rt_uint32_t *data_ptr;
	rt_uint8_t  data_size;
};

struct efm32_usart_device_t
{
	/* Unit number */
	rt_uint8_t unit;
	/* State */
	rt_uint8_t state;
	/*  Pointer to USART device structure */
	USART_TypeDef* usart_device;
	/* Pointer to RX structure */
	void *rx_mode;
	/* Pointer to TX structure */
	void *tx_mode;
};

/* Exported constants ---------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
#define USART_WAIT_TIME_TX		(RT_TICK_PER_SECOND / 100 * 3)

#define USART_STATE_CONSOLE 	(1 << 0)
#define USART_STATE_SYNC		(1 << 1)
#define USART_STATE_MASTER		(1 << 2)
#define USART_STATE_AUTOCS 		(1 << 3)
#define USART_STATE_TX_BUSY 	(1 << 4)
#define USART_STATE_RX_BUSY 	(1 << 5)


/* Exported functions --------------------------------------------------------- */
void rt_hw_usart_init(void);

#endif /* __DRV_USART_H__ */
