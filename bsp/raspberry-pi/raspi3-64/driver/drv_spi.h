/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include <rthw.h>

#include "bcm283x.h"
#include <rtdevice.h>
#include <drivers/spi.h>
#include "raspi.h"

#define SPI0_BASE_ADDR     (PER_BASE + BCM283X_SPI0_BASE)

#define	SPI_CORE_CLK	250000000U
#define	SPI_CS		0x00
#define	SPI_CS_LEN_LONG		(1 << 25)
#define	SPI_CS_DMA_LEN		(1 << 24)
#define	SPI_CS_CSPOL2		(1 << 23)
#define	SPI_CS_CSPOL1		(1 << 22)
#define	SPI_CS_CSPOL0		(1 << 21)
#define	SPI_CS_RXF		(1 << 20)
#define	SPI_CS_RXR		(1 << 19)
#define	SPI_CS_TXD		(1 << 18)
#define	SPI_CS_RXD		(1 << 17)
#define	SPI_CS_DONE		(1 << 16)
#define	SPI_CS_LEN		(1 << 13)
#define	SPI_CS_REN		(1 << 12)
#define	SPI_CS_ADCS		(1 << 11)
#define	SPI_CS_INTR		(1 << 10)
#define	SPI_CS_INTD		(1 << 9)
#define	SPI_CS_DMAEN		(1 << 8)
#define	SPI_CS_TA		(1 << 7)
#define	SPI_CS_CSPOL		(1 << 6)
#define	SPI_CS_CLEAR_RXFIFO	(1 << 5)
#define	SPI_CS_CLEAR_TXFIFO	(1 << 4)
#define	SPI_CS_CPOL		(1 << 3)
#define	SPI_CS_CPHA		(1 << 2)
#define	SPI_CS_MASK		0x3
#define	SPI_FIFO	0x04
#define	SPI_CLK		0x08
#define	SPI_CLK_MASK		0xffff
#define	SPI_DLEN	0x0c
#define	SPI_DLEN_MASK		0xffff
#define	SPI_LTOH	0x10
#define	SPI_LTOH_MASK		0xf
#define	SPI_DC		0x14
#define	SPI_DC_RPANIC_SHIFT	24
#define	SPI_DC_RPANIC_MASK	(0xff << SPI_DC_RPANIC_SHIFT)
#define	SPI_DC_RDREQ_SHIFT	16
#define	SPI_DC_RDREQ_MASK	(0xff << SPI_DC_RDREQ_SHIFT)
#define	SPI_DC_TPANIC_SHIFT	8
#define	SPI_DC_TPANIC_MASK	(0xff << SPI_DC_TPANIC_SHIFT)
#define	SPI_DC_TDREQ_SHIFT	0
#define	SPI_DC_TDREQ_MASK	0xff

int rt_hw_spi_bus_init(void);

#endif
