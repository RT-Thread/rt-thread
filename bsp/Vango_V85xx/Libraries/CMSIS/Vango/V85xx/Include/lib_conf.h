/**
  ******************************************************************************
  * @file    lib_conf.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   Dirver configuration.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_CONF_H
#define __LIB_CONF_H

/* ########################## Assert Selection ############################## */

//#define ASSERT_NDEBUG    1

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file 
  */
#include "lib_ana.h"
#include "lib_adc.h"
#include "lib_adc_tiny.h"
#include "lib_clk.h"
#include "lib_comp.h"
#include "lib_crypt.h"
#include "lib_dma.h"
#include "lib_flash.h"
#include "lib_gpio.h"
#include "lib_i2c.h"
#include "lib_iso7816.h"
#include "lib_lcd.h"
#include "lib_misc.h"
#include "lib_pmu.h"
#include "lib_pwm.h"
#include "lib_rtc.h"
#include "lib_spi.h"
#include "lib_tmr.h"
#include "lib_u32k.h"
#include "lib_uart.h"
#include "lib_version.h"
#include "lib_wdt.h"
#include "lib_LoadNVR.h"
#include "lib_CodeRAM.h"
#include "lib_cortex.h"

/* Exported macro ------------------------------------------------------------*/
#ifndef  ASSERT_NDEBUG
  #define assert_parameters(expr) ((expr) ? (void)0U : assert_errhandler((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_errhandler(uint8_t* file, uint32_t line);
#else
  #define assert_parameters(expr) ((void)0U)
#endif /* ASSERT_NDEBUG */ 

#endif

/*********************************** END OF FILE ******************************/
