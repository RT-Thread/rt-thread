/*
 * File      : nuc97x_conf.h
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */


#ifndef _NUC970_CONF_H_
#define _NUC970_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "nuc97x.h"
#include "nuc97x_sys.h"
#include "nuc97x_mfp.h"
#include "nuc97x_gpio.h"
#include "nuc97x_interrupt.h"
#include "nuc97x_i2c.h"
#include "nuc97x_spi.h"
#include "nuc97x_etimer.h"
#include "nuc97x_timer.h"
#include "nuc97x_uart.h"
#include "nuc97x_ethernet.h"
//#include "nuc970_usbd.h"
//#include "nuc97x_sdio.h"


#define UNCACHE_MASK    0x80000000
//#define UNCACHE_MASK    0x00000000
#define UNCACHE_BUFFER(x)     ((void *)((uint32_t)(x) | UNCACHE_MASK))

#ifndef ARRAY_SIZE
# define ARRAY_SIZE(ar) (sizeof(ar) / sizeof(ar[0]))
#endif

/*
 * UART config
 */

/*
 * SPI config
 */
#define SPI0_USING_GPIOB
#define SPI1_USING_GPIOB
//#define SPI1_USING_GPIOI


#ifdef __cplusplus
}
#endif

#endif /* _NUC970_CONF_H_ */
