/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include "board.h"

struct apm32_spi_cs
{
    GPIO_T *GPIOx;
    uint16_t GPIO_Pin;
};

#endif /*__DRV_SPI_H__ */
