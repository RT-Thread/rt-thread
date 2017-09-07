/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file        imx_spi_nor_atmel.h
 * @brief       header file for Atmel SPI NOR flash
 *
 * @ingroup     diag_driver
 */

#ifndef _IMX_SPI_NOR_ATMEL_H_
#define _IMX_SPI_NOR_ATMEL_H_

#define SPI_NOR_XFER_SZ         512

#define READ        0x03        // tx: 1 byte cmd + 3 byte addr; rx: variable bytes
#define READ_HS     0x0B        // tx: 1 byte cmd + 3 byte addr + 1 byte dummy; rx: variable bytes
#define RDSR        0x05        // read status register 1 byte tx cmd + 1 byte rx status
#define RDSR_BUSY       (1 << 0)    // 1=write-in-progress (default 0)
#define RDSR_WEL        (1 << 1)    // 1=write enable (default 0)
#define RDSR_BP0        (1 << 2)    // block write prot level (default 1)
#define RDSR_BP1        (1 << 3)    // block write prot level (default 1)
#define RDSR_BP2        (1 << 4)    // block write prot level (default 1)
#define RDSR_BP3        (1 << 5)    // block write prot level (default 1)
#define RDSR_AAI        (1 << 6)    // 1=AAI prog mode; 0=byte prog (default 0)
#define RDSR_BPL        (1 << 7)    // 1=BP3,BP2,BP1,BP0 RO; 0=R/W (default 0)
#define WREN        0x06        // write enable. 1 byte tx cmd
#define WRDI        0x04        // write disable. 1 byte tx cmd
#define EWSR        0x50        // Enable write status. 1 byte tx cmd
#define WRSR        0x01        // Write status register. 1 byte tx cmd + 1 byte tx value
#define ERASE_4K    0x20        // sector erase. 1 byte cmd + 3 byte addr
#define ERASE_32K   0x52        // 32K block erase. 1 byte cmd + 3 byte addr
#define ERASE_64K   0xD8        // 64K block erase. 1 byte cmd + 3 byte addr
#define ERASE_CHIP  0x60        // whole chip erase
#define BYTE_PROG   0x02        // all tx: 1 cmd + 3 addr + 1 data
#define AAI_PROG    0xAD        // all tx: [1 cmd + 3 addr + 2 data] + RDSR
//   + [1cmd + 2 data] + .. + [WRDI] + [RDSR]
#define JEDEC_ID    0x9F        // read JEDEC ID. tx: 1 byte cmd; rx: 3 byte ID

/* Atmel SPI-NOR commands */
#define WR_2_MEM_DIR  0x82
#define BUF1_WR             0x84
#define BUF2_WR             0x87
#define BUF1_TO_MEM     0x83
#define BUF2_TO_MEM     0x86
#define STAT_READ          0xD7
#define STAT_PG_SZ    (1 << 0)  // 1=Page size is 512, 0=Page size is 528 (default 0)
#define STAT_PROT      (1 << 1) // 1=sector protection enabled (default 0)
#define STAT_COMP      (1 << 6)
#define STAT_BUSY      (1 << 7) // 1=Device not busy
#define CONFIG_REG1      0x3D
#define CONFIG_REG2      0x2A
#define CONFIG_REG3      0x80
#define CONFIG_REG4      0xA6

#define SZ_64K      0x10000
#define SZ_32K      0x8000
#define SZ_4K       0x1000
#define TRANS_FAIL  -1

#endif // _IMX_SPI_NOR_ATMEL_H_
