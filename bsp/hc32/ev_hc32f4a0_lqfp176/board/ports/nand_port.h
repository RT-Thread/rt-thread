/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-01     CDT          first version
 */

#ifndef __NAND_PORT_H__
#define __NAND_PORT_H__

/******************** NAND chip information ***********************************/
#define NAND_BYTES_PER_PAGE             2048UL
#define NAND_SPARE_AREA_SIZE            64UL
#define NAND_PAGES_PER_BLOCK            64UL
#define NAND_BYTES_PER_BLOCK            (NAND_PAGES_PER_BLOCK * NAND_BYTES_PER_PAGE)
#define NAND_BLOCKS_PER_PLANE           1024UL
#define NAND_PLANE_PER_DEVICE           2UL
#define NAND_DEVICE_BLOCKS              (NAND_BLOCKS_PER_PLANE * NAND_PLANE_PER_DEVICE)
#define NAND_DEVICE_PAGES               (NAND_DEVICE_BLOCKS * NAND_PAGES_PER_BLOCK)

/******************** EXMC_NFC configure **************************************/
/* chip: EXMC_NFC_BANK0~7 */
#define NAND_EXMC_NFC_BANK              EXMC_NFC_BANK0

/* density:2Gbit */
#define NAND_EXMC_NFC_BANK_CAPACITY     EXMC_NFC_BANK_CAPACITY_2GBIT

/* device width: 8-bit */
#define NAND_EXMC_NFC_MEMORY_WIDTH      EXMC_NFC_MEMORY_WIDTH_8BIT

/* page size: 2KByte */
#define NAND_EXMC_NFC_PAGE_SIZE         EXMC_NFC_PAGE_SIZE_2KBYTE

/* row address cycle: 3 */
#define NAND_EXMC_NFC_ROW_ADDR_CYCLE    EXMC_NFC_3_ROW_ADDR_CYCLE

/* ECC mode */
#define NAND_EXMC_NFC_ECC_MD            EXMC_NFC_1BIT_ECC

/* timing configuration(EXCLK clock frequency: 60MHz@3.3V) for MT29F2G08AB */
/* TS: ALE/CLE/CE setup time(min=10ns) */
#define NAND_TS                         1U

/* TWP: WE# pulse width (min=10ns) */
#define NAND_TWP                        1U

/* TRP: RE# pulse width (MT29F2G08AB min=10ns and EXMC t_data_s min=24ns) */
#define NAND_TRP                        2U

/* TTH: ALE/CLE/CE hold time (min=5ns) */
#define NAND_TH                         1U

/* TWH: WE# pulse width HIGH (min=10ns) */
#define NAND_TWH                        1U

/* TRH: RE# pulse width HIGH (min=7ns) */
#define NAND_TRH                        1U

/* TRR: Ready to RE# LOW (min=20ns) */
#define NAND_TRR                        2U

/* TWB: WE# HIGH to busy (max=100ns) */
#define NAND_TWB                        1U

/* TWB: WE# HIGH to busy (max=100ns) */
#define NAND_TRB                        1U

/* TCCS: Change read column and Change write column delay */
#define NAND_TCCS                       5U

/* TWTR: WE# HIGH to RE# LOW (min=60ns) */
#define NAND_TWTR                       4U

/* TRTW: RE# HIGH to WE# LOW (min=100ns) */
#define NAND_TRTW                       7U

/* TADL: ALE to data start (min=70ns) */
#define NAND_TADL                       5U

#endif
