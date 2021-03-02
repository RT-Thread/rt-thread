/**
    *****************************************************************************
    * @file     cmem7_includes.h
    *
    * @brief    CMEM7 includes file, easy to use CMEM7 library
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_INCLUDES_H
#define __CMEM7_INCLUDES_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7_conf.h"
#include "cmem7_it.h"

#ifdef _ADC
    #include "cmem7_adc.h"
#endif

#ifdef _AES
    #include "cmem7_aes.h"
#endif

#ifdef _CAN
    #include "cmem7_can.h"
#endif

#ifdef _DDR
    #include "cmem7_ddr.h"
#endif

#ifdef _DMA
    #include "cmem7_dma.h"
#endif

#ifdef _EFUSE
    #include "cmem7_efuse.h"
#endif

#ifdef _ETH
    #include "cmem7_eth.h"
#endif

#ifdef _FLASH
    #include "cmem7_flash.h"
#endif

#ifdef _GPIO
    #include "cmem7_gpio.h"
#endif

#ifdef _I2C
    #include "cmem7_i2c.h"
#endif

#ifdef _MISC
    #include "cmem7_misc.h"
#endif

#ifdef _RTC
    #include "cmem7_rtc.h"
#endif

#ifdef _SPI
    #include "cmem7_spi.h"
#endif

#ifdef _TIM
    #include "cmem7_tim.h"
#endif

#ifdef _UART
    #include "cmem7_uart.h"
#endif

#ifdef _USB
    #include "cmem7_usb.h"
#endif

#ifdef _WDG
    #include "cmem7_wdg.h"
#endif


#ifdef _MARVELL
  #include <marvel_98dx242.h>
    #include <s24g_i2c.h>
#endif

#ifdef _IP1826D
  #include <ip1826d_v00.h>
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_INCLUDES_H */

