/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2022-04-11  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#ifndef __BOARD_SAM_GMAC_H_
#define __BOARD_SAM_GMAC_H_

#include <rtthread.h>

/**
  * @brief  GMAC duplex type
  */
typedef enum
{
  GMAC_HALF_DUPLEX                       = 0x00, /*!< half duplex */
  GMAC_FULL_DUPLEX                       = 0x01  /*!< full duplex */
} gmac_duplex_type;

/**
  * @brief  GMAC speed type
  */
typedef enum
{
  GMAC_SPEED_10MBPS                      = 0x00, /*!< 10 mbps */
  GMAC_SPEED_100MBPS                     = 0x01  /*!< 100 mbps */
} gmac_speed_type;

#define CONF_AT24MAC_ADDRESS               0x57

#endif // __BOARD_SAM_GMAC_H_
