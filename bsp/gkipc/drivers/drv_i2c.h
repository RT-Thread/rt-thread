/*
 * File      : drv_i2c.h
 * This file is part of gkipc BSP for RT-Thread distribution.
 *
 * Copyright (c) 2017 ChengDu goke Microelectronics Co., Ltd.
 * All rights reserved
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
 *  Visit http://www.goke.com to get contact with goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef _I2C_H_
#define _I2C_H_

#include <rtthread.h>


/*!
*******************************************************************************
** \brief I2C channel number.
*******************************************************************************
*/
typedef enum
{
    RT_I2C_CHANNEL_ONE = 0, /*!< I2C channel 1.*/
    RT_I2C_CHANNEL_TWO,     /*!< I2C channel 2.*/
}RT_I2C_ChannelT;


/*!
*******************************************************************************
** \brief I2C operition modes.
*******************************************************************************
*/
typedef enum
{
    RT_I2C_GENERIC_MASTER_MODE, /*!< Generic master mode.*/
    RT_I2C_GENERIC_SLAVER_MODE, /*!< Generic slave mode.*/
    RT_I2C_AUTO_MASTER_MODE,    /*!< Auto master mode.*/
    RT_I2C_AUTO_SLAVER_MODE,    /*!< Auto slave mode.*/
    RT_I2C_DMA_MASTER_MODE,     /*!< DMA master mode.*/
    RT_I2C_DMA_SLAVER_MODE,     /*!< DMA slave mode.*/
}RT_I2C_OpenModeT;


/*!
*******************************************************************************
** \brief Protocol modes.
*******************************************************************************
*/
typedef enum
{
    RT_I2C_COMMON_PROTOCOL = 0,  /*!< Common protocol.*/
    RT_I2C_RESTART_PROTOCOL,     /*!< Protocol with restart.*/
}RT_I2C_ProtocolT;


/*!
*******************************************************************************
** \brief I2C datarate speed modes.
*******************************************************************************
*/
typedef enum
{
    RT_I2C_100KBPS = 100000, /*!< 100kHz datarate.*/
    RT_I2C_400KBPS = 400000,     /*!< 400kHz datarate.*/
}RT_I2C_SpeedT;

/*!
*******************************************************************************
** \brief I2C transmit modes.
*******************************************************************************
*/
typedef enum
{
    RT_I2C_NORMAL = 0,
    RT_I2C_TURBO_MODE,  // write operation only.
    RT_I2C_INTERRUPT,
}RT_I2C_ModeT;

/*!
*******************************************************************************
** \brief Init parameters.
*******************************************************************************
*/
typedef struct
{
    RT_I2C_OpenModeT       mode;          /*!< Operation mode.*/
    rt_int8_t              priority;      /*!< IRQ priority */
    rt_int8_t              gpioSdaPinCh1; /*!< GPIO SDA pin assigmnet channel 1.*/
    rt_int8_t              gpioSclPinCh1; /*!< GPIO SCL pin assigmnet channel 1.*/
    rt_int8_t              gpioSdaPinCh2; /*!< For future use.*/
    rt_int8_t              gpioSclPinCh2; /*!< For future use.*/
}RT_I2C_InitParamsT;


/*!
*******************************************************************************
** \brief Open parameters.
*******************************************************************************
*/
typedef struct
{
    RT_I2C_ChannelT    channel;   /*!< i2c channel index*/
    RT_I2C_SpeedT      speed;     /*!< i2c speed*/
    RT_I2C_ModeT       mode;      /*!< i2c mode*/
}RT_I2C_OpenParamsT;

typedef struct gk_i2c_config
{
    RT_I2C_InitParamsT  i2cInitParams;
}gk_i2c_config_s;



typedef struct gk_i2c_obj
{
    rt_uint32_t id;
    rt_uint32_t handle;
    rt_mutex_t lock;
    gk_i2c_config_s config;
}gk_i2c_obj_s;


void rt_hw_i2c_init(void);


#endif/*_I2C_H_*/
