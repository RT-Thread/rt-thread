/**
  *********************************************************************************
  *
  * @file    ald_conf.h
  * @brief   Enable/Disable the peripheral module.
  *
  * @version V1.0
  * @date    01 Jul 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */


#ifndef __ALD_CONF_H__
#define __ALD_CONF_H__


#define ALD_DMA
#define ALD_GPIO
#define ALD_UART
#define ALD_LPUART
#define ALD_I2C
#define ALD_CMU
#define ALD_RMU
#define ALD_PMU
#define ALD_WDT
#define ALD_LCD
#define ALD_RTC
#define ALD_CAN
#define ALD_FLASH
#define ALD_ADC
#define ALD_CRC
#define ALD_CRYPT
#define ALD_TIMER
#define ALD_LPTIM
#define ALD_PIS
#define ALD_SPI
#define ALD_CALC
#define ALD_ACMP
#define ALD_OPAMP
#define ALD_TRNG
#define ALD_TSENSE
#define ALD_BKPC
#define ALD_DAC
#define ALD_IAP
#define ALD_I2S
#define ALD_ECC
#define ALD_NAND
#define ALD_QSPI
#define ALD_NOR
#define ALD_SRAM
#define ALD_USB

#if defined(ALD_NAND) || defined(ALD_NOR) || defined(ALD_SRAM)
#define ALD_EBI
#endif

#define TICK_INT_PRIORITY	3

#endif
