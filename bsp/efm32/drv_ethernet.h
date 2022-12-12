/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-06-22   onelife     Initial creation for using EFM32 USART module
 */

#ifndef __DEV_ETHERNET_H__
#define __DEV_ETHERNET_H__

/* Includes ------------------------------------------------------------------*/
#include "enc28j60.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define ETH_ADDR_LEN            (6)
#define ETH_CLK_MAX             (10000000)  /* Should be more than 8 Mz (Errata 1) */
//#define ETH_HALF_DUPLEX

#define ETH_PERIOD_WAIT_INIT    (RT_TICK_PER_SECOND/100)
#define ETH_PERIOD_WAIT_TX      (RT_TICK_PER_SECOND/100)
#define ETH_SPI_RX_SKIP         (1)

#define ETH_RESET_PORT          (gpioPortB)
#define ETH_RESET_PIN           (9)
#define ETH_INT_PORT            (gpioPortB)
#define ETH_INT_PIN             (10)

/* Exported functions ------------------------------------------------------- */
rt_err_t efm_hw_eth_init(void);

#endif /* __DEV_ETHERNET_H__ */
