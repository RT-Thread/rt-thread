/***************************************************************************//**
 * @file    dev_lcd.h
 * @brief   LCD driver of RT-Thread RTOS for EFM32
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 *  LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-12-16   onelife     Initial creation of address mapped method (pixel
 *  drive) for EFM32GG_DK3750 board
 ******************************************************************************/
#ifndef __DEV_LCD_H__
#define __DEV_LCD_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void efm32_spiLcd_init(void);

#endif /* __DEV_LCD_H__ */
