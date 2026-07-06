/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_conf.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G45X_CONF_H__
#define __N32G45X_CONF_H__

/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */

#include "n32g45x_adc.h"
#include "n32g45x_bkp.h"
#include "n32g45x_can.h"
#include "n32g45x_comp.h"
#include "n32g45x_crc.h"
#include "n32g45x_dac.h"
#include "n32g45x_dbg.h"
#include "n32g45x_dma.h"
#include "n32g45x_dvp.h"
#include "n32g45x_eth.h"
#include "n32g45x_exti.h"
#include "n32g45x_flash.h"
#include "n32g45x_gpio.h"
#include "n32g45x_i2c.h"
#include "n32g45x_iwdg.h"
#include "n32g45x_opamp.h"
#include "n32g45x_pwr.h"
#include "n32g45x_qspi.h"
#include "n32g45x_rcc.h"
#include "n32g45x_rtc.h"
#include "n32g45x_sdio.h"
#include "n32g45x_spi.h"
#include "n32g45x_tim.h"
#include "n32g45x_usart.h"
#include "n32g45x_wwdg.h"
#include "n32g45x_xfmc.h"
#include "n32g45x_tsc.h"

#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Uncomment the line below to expanse the "assert_param" macro in the
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1  */

#ifdef USE_FULL_ASSERT

/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param expr If expr is false, it calls assert_failed function which reports
 *         the name of the source file and the source line number of the call
 *         that failed. If expr is true, it returns no value.
 */
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((const uint8_t*)#expr, (const uint8_t*)__FILE__, __LINE__))

void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __N32G45X_CONF_H__ */
