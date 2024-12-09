/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-28     qiujingbao   first version
 * 2024/06/08     flyingcys    fix transmission failure
 */
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include "mmio.h"
#include "dw_spi.h"

#define DW_SPI_REG_SIZE             (0x10000UL)
#define DW_SPI0_BASE                (0x04180000UL)
#define DW_SPI1_BASE                (DW_SPI0_BASE + 1 * DW_SPI_REG_SIZE)
#define DW_SPI2_BASE                (DW_SPI0_BASE + 2 * DW_SPI_REG_SIZE)
#define DW_SPI3_BASE                (DW_SPI0_BASE + 3 * DW_SPI_REG_SIZE)

#define DW_SPI0_IRQn                54
#define DW_SPI1_IRQn                55
#define DW_SPI2_IRQn                56
#define DW_SPI3_IRQn                56

#endif /* __DRV_SPI_H__ */
