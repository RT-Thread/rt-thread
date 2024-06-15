/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_qspi.h
 * @brief    This file contains all the functions prototypes for the IFlash library.
 *
 * Change Logs:
 * Date           Author             Version        Notes
 * 2021-08-14     wushengyan         V1.0.0         the first version
 */

#ifndef __YC_QSPI_H__
#define __YC_QSPI_H__
#include "yc3122.h"

#define BOOT_UART_DOWNLOAD_FLAG         0x5a5aa5a5
#define BOOT_USB_DOWNLOAD_FLAG          0xaa5555aa
#define BOOT_AUTO_SELECT_FLAG           0xffffffff

#define ENC_BULK_BUF_SIZE               0x9000

typedef enum {
  YC_QFLASH_SIZE_UNKNOW = 0,
  YC_QFLASH_SIZE_512KB = 1,
  YC_QFLASH_SIZE_1MB = 2,
  YC_QFLASH_SIZE_4MB = 3,
} yc_qspi_flash_size_enum;

typedef struct
{
    uint16_t is_end;
    uint16_t enc_index;
    uint8_t enc_buf[ENC_BULK_BUF_SIZE];
} ENC_BulkTypeDef;


/**
 * @method qspi_flash_pageerase
 * @brief  page erase (256byte)
 * @param  flash_addr
 * @retval ERROR,SUCCESS
 */
uint8_t qspi_flash_pageerase(uint32_t flash_addr);
/**
 * @method qspi_flash_sectorerase
 * @brief  sector erase (4K)
 * @param  flash_addr:flash addr (4k Bytes align)
 * @retval ERROR,SUCCESS
 */
uint8_t qspi_flash_sectorerase(uint32_t flash_addr);

/**
 * @method qspi_flash_blockerase32k
 * @brief  block erase  (32K)
 * @param  flash_addr:flash addr (32k Bytes align)
 * @retval ERROR,SUCCESS
 */
uint8_t qspi_flash_blockerase32k(uint32_t flash_addr);

/**
 * @method qspi_flash_blockerase64k
 * @brief  block erase  (64K)
 * @param  flash_addr:flash addr (64k Bytes align)
 * @retval ERROR,SUCCESS
 */
uint8_t qspi_flash_blockerase64k(uint32_t flash_addr);

/**
 * @method qspi_flash_write
 * @brief  write flash
 * @param  flash_addr:flash addr (when flash_addr%256!=0,256-(flash_addr%256)+len must less than 256)
 * @param  buf
 * @param  len
 * @retval ERROR,SUCCESS
 */
uint8_t qspi_flash_write(uint32_t flash_addr, uint8_t *buf, uint32_t len);

/**
 * @method qspi_flash_read
 * @brief  read flash
 * @param  flash_addr:flash addr
 * @param  buf
 * @param  len
 * @retval ERROR,SUCCESS
 */
uint8_t qspi_flash_read(uint32_t flash_addr, uint8_t *buf, uint32_t len);

/**
 * @method flash_blank_check
 * @brief  check logical addr data is blank
 * @param  startaddr:cpu addr
 * @param  len
 * @retval TRUE:  blank
 *         FALSE: not blank
 */
Boolean flash_blank_check(uint32_t startaddr, uint32_t len);

/**
 * @method enc_write_flash
 * @brief  write data to flash with enc
 * @param  flash_addr:cpu addr (must 32 Bytes align)
 * @param  buf
 * @param  len:(must 32 Bytes align)
 * @retval ERROR,SUCCESS
 */
uint8_t enc_write_flash(uint32_t flash_addr, uint8_t *buf, uint32_t len);

/**
 * @method enc_read_flash
 * @brief  read flash data with enc
 * @param  flash_addr:cpu addr
 * @param  buf
 * @param  len
 * @retval ERROR,SUCCESS
 */
uint8_t enc_read_flash(uint32_t flash_addr, uint8_t *buf, uint32_t len);

/**
 * @method enc_read_flash_fast
  * @brief  enc read flash fast(You must sure that the read area is written by enc)
 * @param  flash_addr:cpu addr
 * @param  buf
 * @param  len
  * @return SUCCESS or ERROR
  */
uint8_t enc_read_flash_fast(uint32_t flash_addr, uint8_t *buf, uint32_t len);

/**
 * @method enc_erase_flash_32byte
 * @brief  erase 32 Bytes
 * @param  flash_addr : cpu addr (must 32 Bytes align)
 * @retval ERROR,SUCCESS
 */
uint8_t enc_erase_flash_32byte(uint32_t flash_addr);

/**
 * @method enc_erase_flash_32k
 * @brief  enc erase 32K Bytes
 * @param  flash_addr : cpu addr (must 32K Bytes align)
 * @retval ERROR,SUCCESS
 */
uint8_t enc_erase_flash_32k(uint32_t flash_addr);

/**
  * @brief  enc erase flash app area
  * @param  addr:align at 32k for CPU addr
  * @param  len:erase len
  * @return ERROR,SUCCESS
  */
uint8_t enc_earse_flash_app_area(uint32_t addr,uint32_t len);

/**
  * @brief  enc write download flag
  * @param  addr:BOOT_UART_DOWNLOAD_FLAG,BOOT_USB_DOWNLOAD_FLAG or BOOT_AUTO_SELECT_FLAG
  * @return ERROR,SUCCESS
  */
uint8_t enc_write_download_flag(uint32_t flag);

/**
 * @method enc_write_flash_bulk
 * @brief  write bulk data to flash with enc
* @param  EncBulkStruct:enc buf struct
 * @param  flash_addr:cpu addr(start addr must 32k Bytes align)
 * @param  buf
 * @param  len: Integer multiple of 32 bytes
 * @retval ERROR,SUCCESS
 */
uint8_t enc_write_flash_bulk(ENC_BulkTypeDef *EncBulkStruct,uint32_t flash_addr, uint8_t *buf, uint32_t len);

/**
 * @method prefetch
 * @brief  fetch code to cache
 * @param  start_addr: code start addr
 * @param  end_addr  : code end addr
 * @retval NULL
 */
void prefetch(void *start_addr, void *end_addr);

/**
 * @method read_flash_size
 * @brief  read the chip flash size
 * @param  NULL
 * @retval yc_qspi_flash_size_enum
 */
yc_qspi_flash_size_enum read_flash_size(void);

/**
 * @method qspi_GetVersion
 * @brief  get qspi lib version
 * @param  NULL
 * @retval version
 */
uint32_t qspi_GetVersion(void);

#endif
