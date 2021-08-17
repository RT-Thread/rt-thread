/**************************************************************************//**
 * @file     NuMicro.h
 * @version  V1.00
 * @brief    NuMicro peripheral access layer header file.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NUMICRO_H__
#define __NUMICRO_H__

#include "N9H30.h"
#include "nu_adc.h"
#include "nu_uart.h"
#include "nu_spi.h"
#include "nu_i2c.h"
#include "nu_etimer.h"
#include "nu_emac.h"
#include "nu_sdh.h"
#include "nu_gpio.h"
#include "nu_rtc.h"
#include "nu_wdt.h"
//#include "nu_ebi.h"
#include "nu_scuart.h"
#include "nu_pwm.h"
//#include "nu_crypto.h"
#include "nu_can.h"
#include "nu_i2s.h"
#include "nu_usbd.h"
#include "nu_lcd.h"
#include "nu_jpegcodec.h"
#include "nu_2d.h"
#include "nu_crypto.h"

#include "nu_sys.h"

#ifndef __STATIC_INLINE
    #define __STATIC_INLINE  static __inline
#endif

#ifndef __CLZ
    #if defined(__CC_ARM)
        #define __CLZ  __clz
    #else
        #define __CLZ  __builtin_clz
    #endif
#endif

#endif  /* __NUMICRO_H__ */


