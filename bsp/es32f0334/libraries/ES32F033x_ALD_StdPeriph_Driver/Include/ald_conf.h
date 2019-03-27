/**
  *********************************************************************************
  *
  * @file    ald_conf.h
  * @brief   Enable/Disable the peripheral module.
  *
  * @version V1.0
  * @date    18 Apr 2017
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
#define ALD_USART
#define ALD_SMARTCARD	/* The ALD_SMARTCARD depend on ALD_USART */
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
#define ALD_TEMP
#define ALD_BKPC
#define ALD_DAC
#define ALD_IAP

#define TICK_INT_PRIORITY	3

#endif
