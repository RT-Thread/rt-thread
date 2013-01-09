/***************************************************************************//**
 * @file    dev_misc.h
 * @brief   Miscellaneous driver of RT-Thread RTOS for EFM32
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-02-22   onelife     Initial creation for EFM32
 ******************************************************************************/
#ifndef __DEV_MISC_H__
#define __DEV_MISC_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
rt_err_t rt_hw_misc_init(void);
rt_int32_t rt_hw_get_temp(void);
rt_uint32_t rt_hw_get_vdd(void);

#endif /* __DEV_MISC_H__ */
