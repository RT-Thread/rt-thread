/*
 * This file is part of the Serial Flash Universal Driver Library.
 *
 * Copyright (c) 2016-2018, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: It is the flash types and specification macro definition head file for this library.
 * Created on: 2016-06-09
 */

#ifndef _SFUD_FLASH_DEF_H_
#define _SFUD_FLASH_DEF_H_

#include <stdint.h>
#include <sfud_cfg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * flash program(write) data mode
 */
enum sfud_write_mode {
    SFUD_WM_PAGE_256B = 1 << 0,                            /**< write 1 to 256 bytes per page */
    SFUD_WM_BYTE = 1 << 1,                                 /**< byte write */
    SFUD_WM_AAI = 1 << 2,                                  /**< auto address increment */
    SFUD_WM_DUAL_BUFFER = 1 << 3,                          /**< dual-buffer write, like AT45DB series */
};

/* manufacturer information */
typedef struct {
    char *name;
    uint8_t id;
} sfud_mf;

/* flash chip information */
typedef struct {
    char *name;                                  /**< flash chip name */
    uint8_t mf_id;                               /**< manufacturer ID */
    uint8_t type_id;                             /**< memory type ID */
    uint8_t capacity_id;                         /**< capacity ID */
    uint32_t capacity;                           /**< flash capacity (bytes) */
    uint16_t write_mode;                         /**< write mode @see sfud_write_mode */
    uint32_t erase_gran;                         /**< erase granularity (bytes) */
    uint8_t erase_gran_cmd;                      /**< erase granularity size block command */
} sfud_flash_chip;

#ifdef SFUD_USING_QSPI
/* QSPI flash chip's extended information compared with SPI flash */
typedef struct {
    uint8_t mf_id;                               /**< manufacturer ID */
    uint8_t type_id;                             /**< memory type ID */
    uint8_t capacity_id;                         /**< capacity ID */
    uint8_t read_mode;                           /**< supported read mode on this qspi flash chip */
} sfud_qspi_flash_ext_info;
#endif

/* SFUD support manufacturer JEDEC ID */
#define SFUD_MF_ID_CYPRESS                             0x01
#define SFUD_MF_ID_FUJITSU                             0x04
#define SFUD_MF_ID_EON                                 0x1C
#define SFUD_MF_ID_ATMEL                               0x1F
#define SFUD_MF_ID_MICRON                              0x20
#define SFUD_MF_ID_AMIC                                0x37
#define SFUD_MF_ID_SANYO                               0x62
#define SFUD_MF_ID_INTEL                               0x89
#define SFUD_MF_ID_ESMT                                0x8C
#define SFUD_MF_ID_FUDAN                               0xA1
#define SFUD_MF_ID_HYUNDAI                             0xAD
#define SFUD_MF_ID_SST                                 0xBF
#define SFUD_MF_ID_MICRONIX                            0xC2
#define SFUD_MF_ID_GIGADEVICE                          0xC8
#define SFUD_MF_ID_ISSI                                0xD5
#define SFUD_MF_ID_WINBOND                             0xEF

/* SFUD supported manufacturer information table */
#define SFUD_MF_TABLE                                     \
{                                                         \
    {"Cypress",    SFUD_MF_ID_CYPRESS},                   \
    {"Fujitsu",    SFUD_MF_ID_FUJITSU},                   \
    {"EON",        SFUD_MF_ID_EON},                       \
    {"Atmel",      SFUD_MF_ID_ATMEL},                     \
    {"Micron",     SFUD_MF_ID_MICRON},                    \
    {"AMIC",       SFUD_MF_ID_AMIC},                      \
    {"Sanyo",      SFUD_MF_ID_SANYO},                     \
    {"Intel",      SFUD_MF_ID_INTEL},                     \
    {"ESMT",       SFUD_MF_ID_ESMT},                      \
    {"Fudan",      SFUD_MF_ID_FUDAN},                     \
    {"Hyundai",    SFUD_MF_ID_HYUNDAI},                   \
    {"SST",        SFUD_MF_ID_SST},                       \
    {"GigaDevice", SFUD_MF_ID_GIGADEVICE},                \
    {"ISSI",       SFUD_MF_ID_ISSI},                      \
    {"Winbond",    SFUD_MF_ID_WINBOND},                   \
    {"Micronix",   SFUD_MF_ID_MICRONIX},                  \
}

#ifdef SFUD_USING_FLASH_INFO_TABLE
/* SFUD supported flash chip information table. If the flash not support JEDEC JESD216 standard,
 * then the SFUD will find the flash chip information by this table. You can add other flash to here then
 *  notice me for update it. The configuration information name and index reference the sfud_flash_chip structure.
 * | name | mf_id | type_id | capacity_id | capacity | write_mode | erase_gran | erase_gran_cmd |
 */
#define SFUD_FLASH_CHIP_TABLE                                                                                       \
{                                                                                                                   \
    {"AT45DB161E", SFUD_MF_ID_ATMEL, 0x26, 0x00, 2L*1024L*1024L, SFUD_WM_BYTE|SFUD_WM_DUAL_BUFFER, 512, 0x81},      \
    {"W25Q40BV", SFUD_MF_ID_WINBOND, 0x40, 0x13, 512L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                        \
    {"W25Q16BV", SFUD_MF_ID_WINBOND, 0x40, 0x15, 2L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                    \
    {"W25Q64CV", SFUD_MF_ID_WINBOND, 0x40, 0x17, 8L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                    \
    {"W25Q64DW", SFUD_MF_ID_WINBOND, 0x60, 0x17, 8L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                    \
    {"W25Q128BV", SFUD_MF_ID_WINBOND, 0x40, 0x18, 16L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                  \
    {"W25Q256FV", SFUD_MF_ID_WINBOND, 0x40, 0x19, 32L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                  \
    {"SST25VF016B", SFUD_MF_ID_SST, 0x25, 0x41, 2L*1024L*1024L, SFUD_WM_BYTE|SFUD_WM_AAI, 4096, 0x20},              \
    {"M25P32", SFUD_MF_ID_MICRON, 0x20, 0x16, 4L*1024L*1024L, SFUD_WM_PAGE_256B, 64L*1024L, 0xD8},                  \
    {"M25P80", SFUD_MF_ID_MICRON, 0x20, 0x14, 1L*1024L*1024L, SFUD_WM_PAGE_256B, 64L*1024L, 0xD8},                  \
    {"M25P40", SFUD_MF_ID_MICRON, 0x20, 0x13, 512L*1024L, SFUD_WM_PAGE_256B, 64L*1024L, 0xD8},                      \
    {"EN25Q32B", SFUD_MF_ID_EON, 0x30, 0x16, 4L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                        \
    {"GD25Q64B", SFUD_MF_ID_GIGADEVICE, 0x40, 0x17, 8L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                 \
    {"GD25Q16B", SFUD_MF_ID_GIGADEVICE, 0x40, 0x15, 2L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                 \
    {"S25FL216K", SFUD_MF_ID_CYPRESS, 0x40, 0x15, 2L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                   \
    {"S25FL032P", SFUD_MF_ID_CYPRESS, 0x02, 0x15, 4L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                   \
    {"A25L080", SFUD_MF_ID_AMIC, 0x30, 0x14, 1L*1024L*1024L, SFUD_WM_PAGE_256B, 4096, 0x20},                        \
    {"F25L004", SFUD_MF_ID_ESMT, 0x20, 0x13, 512L*1024L, SFUD_WM_BYTE|SFUD_WM_AAI, 4096, 0x20},                     \
    {"PCT25VF016B", SFUD_MF_ID_SST, 0x25, 0x41, 2L*1024L*1024L, SFUD_WM_BYTE|SFUD_WM_AAI, 4096, 0x20},              \
}
#endif /* SFUD_USING_FLASH_INFO_TABLE */

#ifdef SFUD_USING_QSPI
/* This table saves flash read-fast instructions in QSPI mode, 
 * SFUD can use this table to select the most appropriate read instruction for flash.
 * | mf_id | type_id | capacity_id | qspi_read_mode |
 */
#define SFUD_FLASH_EXT_INFO_TABLE                                                                  \
{                                                                                                  \
    /* W25Q40BV */                                                                                 \
    {SFUD_MF_ID_WINBOND, 0x40, 0x13, NORMAL_SPI_READ|DUAL_OUTPUT},                                 \
    /* W25Q80JV */                                                                                 \
    {SFUD_MF_ID_WINBOND, 0x40, 0x14, NORMAL_SPI_READ|DUAL_OUTPUT},                                 \
    /* W25Q16BV */                                                                                 \
    {SFUD_MF_ID_WINBOND, 0x40, 0x15, NORMAL_SPI_READ|DUAL_OUTPUT},                                 \
    /* W25Q32BV */                                                                                 \
    {SFUD_MF_ID_WINBOND, 0x40, 0x16, NORMAL_SPI_READ|DUAL_OUTPUT|QUAD_OUTPUT|QUAD_IO},             \
    /* W25Q64JV */                                                                                 \
    {SFUD_MF_ID_WINBOND, 0x40, 0x17, NORMAL_SPI_READ|DUAL_OUTPUT|DUAL_IO|QUAD_OUTPUT|QUAD_IO},     \
    /* W25Q128JV */                                                                                \
    {SFUD_MF_ID_WINBOND, 0x40, 0x18, NORMAL_SPI_READ|DUAL_OUTPUT|DUAL_IO|QUAD_OUTPUT|QUAD_IO},     \
    /* W25Q256FV */                                                                                \
    {SFUD_MF_ID_WINBOND, 0x40, 0x19, NORMAL_SPI_READ|DUAL_OUTPUT|DUAL_IO|QUAD_OUTPUT|QUAD_IO},     \
    /* EN25Q32B */                                                                                 \
    {SFUD_MF_ID_EON, 0x30, 0x16, NORMAL_SPI_READ|DUAL_OUTPUT|QUAD_IO},                             \
    /* S25FL216K */                                                                                \
    {SFUD_MF_ID_CYPRESS, 0x40, 0x15, NORMAL_SPI_READ|DUAL_OUTPUT},                                 \
    /* A25L080 */                                                                                  \
    {SFUD_MF_ID_AMIC, 0x30, 0x14, NORMAL_SPI_READ|DUAL_OUTPUT|DUAL_IO},                            \
    /* A25LQ64 */                                                                                  \
    {SFUD_MF_ID_AMIC, 0x40, 0x17, NORMAL_SPI_READ|DUAL_OUTPUT|DUAL_IO|QUAD_IO},                    \
    /* MX25L3206E and KH25L3206E */                                                                \
    {SFUD_MF_ID_MICRONIX, 0x20, 0x16, NORMAL_SPI_READ|DUAL_OUTPUT},                                \
    /* GD25Q64B */                                                                                 \
    {SFUD_MF_ID_GIGADEVICE, 0x40, 0x17, NORMAL_SPI_READ|DUAL_OUTPUT},                              \
}
#endif /* SFUD_USING_QSPI */

#ifdef __cplusplus
}
#endif

#endif /* _SFUD_FLASH_DEF_H_ */
