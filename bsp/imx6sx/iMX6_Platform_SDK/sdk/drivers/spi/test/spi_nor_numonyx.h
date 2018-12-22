/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _IMX_SPI_NOR_NUMONYX_H_
#define _IMX_SPI_NOR_NUMONYX_H_

#include "sdk.h"

#define SPI_NOR_XFER_SZ 512

#define WREN        0x06
#define WRDI        0x04
#define RDID        0x9F
#define RDSR        0x05
#define WRSR        0x01
#define READ        0x03
#define FAST_READ   0x0B
#define PP	        0x02
#define SE   	    0xD8
#define BE	        0xC7
#define DP	        0xB9
#define RES	        0xAB

#define RDSR_BUSY   (1 << 0)
#define RDSR_WEL    (1 << 1)
#define RDSR_BP0    (1 << 2)
#define RDSR_BP1    (1 << 3)
#define RDSR_BP2    (1 << 4)
#define RDSR_SRWD   (1 << 7)

#define NUMONYX_CMD_SZ 4
#define NUMONYX_MAX_RX 36
#define NUMONYX_MAX_TX 36

#define SZ_64K      0x10000
#define SZ_32K      0x8000
#define SZ_4K       0x1000

#define SZ_SECTOR   SZ_64K
#define SZ_CHIP     (SZ_SECTOR * 64)

#define SZ_PAGE     256
#define SZ_MASK     0xFFFFFF00
#define SZ_OFFSET   0x000000FF

#define TRANS_FAIL  -1

extern int spi_nor_query_numonyx(uint8_t *);
extern int spi_nor_erase_numonyx(uint32_t, uint32_t);
extern int spi_nor_read_numonyx(uint32_t, uint8_t *, int);
extern int spi_nor_write_numonyx(uint32_t, uint8_t *, int);

#endif
