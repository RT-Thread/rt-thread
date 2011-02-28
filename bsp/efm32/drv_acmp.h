/******************************************************************//**
 * @file 		drv_acmp.h
 * @brief 	ACMP (analog comparator) driver of RT-Thread RTOS for EFM32
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
 * 2011-02-23	onelife		Initial creation for EFM32
 *********************************************************************/
#ifndef __DRV_ACMP_H__
#define __DRV_ACMP_H__

/* Includes -------------------------------------------------------------------*/
#include "hdl_interrupt.h"

/* Exported types -------------------------------------------------------------*/
struct efm32_acmp_device_t
{
	ACMP_TypeDef 		*acmp_device;
	efm32_irq_hook_t 	hook;
};

struct efm32_acmp_output_t
{
	rt_uint32_t 		location; 
	rt_bool_t 			enable; 
	rt_bool_t 			invert;
};

struct efm32_acmp_control_t
{
	ACMP_Init_TypeDef			*init;
	ACMP_Channel_TypeDef		posInput;
	ACMP_Channel_TypeDef		negInput;
	struct efm32_acmp_output_t 	*output;
	efm32_irq_hook_t 			hook;
};

/* Exported constants ---------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
/** Default config for ACMP init structure. */
#define ACMP_INIT_DEFAULT 										\
{ 																\
	false, 					/* Full bias current*/ 					\
	true, 					/* Half bias current */ 				\
	0, 						/* Biasprog current configuration */ 		\
	false, 					/* Enable interrupt for falling edge */ 	\
	false, 					/* Enable interrupt for rising edge */ 	\
	acmpWarmTime512, 		/* Warm-up time must be >10us */ 		\
	acmpHysteresisLevel0,	/* Hysteresis configuration */ 			\
	0, 						/* Inactive comparator output value */ 	\
	false, 					/* Enable low power mode */ 			\
	0 						/* Vdd reference scaling */ 			\
}

/* Exported functions --------------------------------------------------------- */
void rt_hw_acmp_init(void);

#endif /*__DRV_ACMP_H__ */
