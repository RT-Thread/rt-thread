/******************************************************************//**
 * @file 		drv_iic.h
 * @brief 	IIC driver of RT-Thread RTOS for EFM32
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
 * 2011-01-07	onelife		Initial creation for EFM32
 *********************************************************************/
#ifndef __DRV_IIC_H__
#define __DRV_IIC_H__

/* Includes -------------------------------------------------------------------*/
/* Exported types -------------------------------------------------------------*/
struct efm32_iic_device_t
{
	I2C_TypeDef* 	iic_device;
	rt_bool_t 		is_master;
	rt_uint16_t		master_address;
	rt_uint16_t		slave_address;
};

struct efm32_iic_control_t
{
	rt_bool_t 		is_master;
	rt_uint16_t		master_address;
	rt_uint16_t		slave_address;
};

/* Exported constants ---------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------- */
void rt_hw_iic_init(void);

#endif /* __DRV_IIC_H__ */
