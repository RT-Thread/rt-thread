/******************************************************************//**
 * @file 		drv_iic.h
 * @brief 	IIC driver of RT-Thread RTOS for EFM32
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
 * 2011-01-07	onelife		Initial creation for EFM32
 *********************************************************************/
#ifndef __DRV_IIC_H__
#define __DRV_IIC_H__

/* Includes -------------------------------------------------------------------*/
/* Exported types -------------------------------------------------------------*/
struct efm32_iic_int_mode_t
{
	rt_uint8_t  *data_ptr;
	rt_uint8_t  data_size;
	rt_uint32_t read_index, save_index;
};

struct efm32_iic_device_t
{
	/* State */
	rt_uint8_t 		state;
	/*  Pointer to IIC device structure */
	I2C_TypeDef* 	iic_device;
	/*  Master address */
	rt_uint16_t		master_address;
	/*  Slave address */
	rt_uint16_t		slave_address;
	/* RX structure */
	struct efm32_iic_int_mode_t 	*rx_buffer;
};

struct efm32_iic_control_t
{
	rt_uint8_t 		config;
	rt_uint16_t		master_address;
	rt_uint16_t		slave_address;
};

/* Exported constants ---------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
#define IIC_STATE_MASTER 	(1 << 0)
#define IIC_STATE_BROADCAST (1 << 1)
//#define IIC_STATE_TX_BUSY 	(1 << 2)
#define IIC_STATE_RX_BUSY 	(1 << 3)

/* Exported functions --------------------------------------------------------- */
void rt_hw_iic_init(void);

#endif /* __DRV_IIC_H__ */
