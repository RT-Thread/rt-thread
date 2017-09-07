/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef ARCH_H_
#define ARCH_H_


/*****************************/
/* BSP CONTROLLER BASE       */
/*****************************/
#define		INTC_REG_BASE		(0xE0200000)
#define		SDC0_REG_BASE		(0xE2000000)
#define		SDC1_REG_BASE		(0xE2100000)
#define		TVE_REG_BASE		(0xE8000000)
#define		VOU_REG_BASE		(0xE8100000)
#define		AES_REG_BASE		(0xE8200000)
#define		JPEG_REG_BASE		(0xE8300000)
#define		ISPB_REG_BASE		(0xEA000000)
#define		ISPF_REG_BASE		(0xEA100000)
#define		VPU_REG_BASE		(0xEC000000)
#define		VCU_REG_BASE		(0xEC100000)
#define		DDRC_REG_BASE		(0xED000000)
#define 	DMAC_REG_BASE		(0xEE000000)
#define 	GMAC_REG_BASE		(0xEF000000)
#define 	PMU_REG_BASE		(0xF0000000)
#define 	I2C0_REG_BASE		(0xF0200000)
#define 	GPIO0_REG_BASE		(0xF0300000)
#define     GPIO1_REG_BASE      (0xf4000000)
#define 	PWM_REG_BASE		(0xF0400000)
#define 	SPI0_REG_BASE		(0xF0500000)
#define 	SPI1_REG_BASE		(0xF0600000)
#define		UART0_REG_BASE		(0xF0700000)
#define		UART1_REG_BASE		(0xF0800000)
#define		I2S_REG_BASE		(0xF0900000)
#define		ACODEC_REG_BASE		(0xF0A00000)
#define		I2C1_REG_BASE		(0xF0B00000)
#define		TMR_REG_BASE		(0xF0C00000)
#define		WDT_REG_BASE		(0xF0D00000)
#define		DPHY_REG_BASE		(0xF1000000)
#define		MIPIC_REG_BASE		(0xF1100000)
#define		SADC_REG_BASE		(0xF1200000)





typedef enum IRQn
{
  PAE_IRQn             =  0,
  VPU_IRQn             =  1,
  ISP_F_IRQn           =  2,
  ISP_B_IRQn           =  3,
  VOU_IRQn             =  4,
  JPEG_IRQn            =  5,
  TVE_IRQn             =  6,
  TOE_IRQn             =  7,
  DDRC_IRQn            =  8,
  DMAC_IRQn            =  9,
  AES_IRQn             = 10,
  MIPIC_IRQn           = 11,
  MIPI_WRAP_IRQn       = 12,
  PMU_IRQn             = 13,
  EMAC_IRQn            = 14,
  AXIC0_IRQn           = 16,
  AXIC1_IRQn           = 17,
  X2H0_IRQn            = 18,
  X2H1_IRQn            = 19,
  AHBC0_IRQn           = 20,
  AHBC1_IRQn           = 21,
  SADC_IRQn            = 23,
  SDC0_IRQn            = 24,
  SDC1_IRQn            = 25,
  ACW_IRQn             = 26,
  WDT_IRQn             = 27,
  SPI0_IRQn            = 28,
  SPI1_IRQn            = 29,
  UART0_IRQn           = 30,
  UART1_IRQn           = 31,
  I2S0_IRQn            = 32,
  I2S1_IRQn            = 33,
  RTC_IRQn             = 34,
  PWM_IRQn             = 35,
  TMR0_IRQn            = 36,
  TMR1_IRQn            = 37,
  USB0_IRQn            = 38,
  USB1_IRQn            = 39,
  GPIO0_IRQn           = 40,
  GPIO1_IRQn           = 41,
  I2C0_IRQn            = 42,
  I2C1_IRQn            = 43,

} IRQn_Type;

#endif /* ARCH_H_ */
