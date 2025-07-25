 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv/spiflash.h
 * @brief    Header File for SPIFLASH Driver
 * @version  V1.0
 * @date     02. June 2020
 * @model    spiflash
 ******************************************************************************/
#ifndef _DRV_SPIFLASH_H_
#define _DRV_SPIFLASH_H_

#include <stdint.h>
#include <drv/gpio.h>
#include <drv/spi.h>
#include <drv/qspi.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* \brief  Build a flash ID
* \param [in] vendor_id    Vendor id(8bit)
* \param [in] device_id    Flash device id (ID15~ID0) 16bit
* \return    24bit flash id
*/
#define FLASH_ID_BUILD(VENDOR_ID,DEVICE_ID)

/**
* \struct csi_spiflash_lock_info_t
* \ flash use status register 1 to protect data in memory array
* \ different flash vendor support different  protect region (top/bottom/none)
*   also support different protect number
*   status1 register bif field show as follow
*   7          |6           |5            |4     |3     |2     |1     |0
*   ---------------------------------------------------------------------
*   vensor def | vendor def | vendor def  | BP2  | BP1  |  BP0 | WEL  | BUSY
* \ Protect type
* \ Protect block size : Vendor define ,user should check flash datasheet of vendor
*                      : Use w25q64fw as example , min protect block size is 128 KB
* \ TOP      : Protect address from flash top address
* \ BOTTOM   : Protect address from flash bottom address
* \ SEC      : Protect addres base on sector unit and protect region only must not exceed one block
* \ BPx      : Protect start addres base on TOP/BOTTOM feature,and BPx value denote protect number
* \            BP[x..0]'s value : 2^(n-1) protect block unit, ex, BP[x..0] = 5, protect block number = 2^(5-1) = 16
* \            If BP[x..0] = 0  denote protect none
* \            If BP[x..0]'s all bis is 1 ,denote protect all flash
* \
* \ NOTE:
* \        only  support SEC = 0
* \        only  support CMP = 0
* \
*
* Sample table portion for 8MB flash (Winbond w25q64fw):
*
*   SEC  |  TB   |  BP2  |  BP1  |  BP0  |  Prot Length  | Protected Portion
*  --------------------------------------------------------------------------
*    X   |   X   |   0   |   0   |   0   |  NONE         | NONE
*    0   |   0   |   0   |   0   |   1   |  128 KB       | Upper 1/64
*    0   |   0   |   0   |   1   |   0   |  256 KB       | Upper 1/32
*    0   |   0   |   0   |   1   |   1   |  512 KB       | Upper 1/16
*    0   |   0   |   1   |   0   |   0   |  1 MB         | Upper 1/8
*    0   |   0   |   1   |   0   |   1   |  2 MB         | Upper 1/4
*    0   |   0   |   1   |   1   |   0   |  4 MB         | Upper 1/2
*    X   |   X   |   1   |   1   |   1   |  8 MB         | ALL
*  ------|-------|-------|-------|-------|---------------|-------------------
*    0   |   1   |   0   |   0   |   1   |  128 KB       | Lower 1/64
*    0   |   1   |   0   |   1   |   0   |  256 KB       | Lower 1/32
*    0   |   1   |   0   |   1   |   1   |  512 KB       | Lower 1/16
*    0   |   1   |   1   |   0   |   0   |  1 MB         | Lower 1/8
*    0   |   1   |   1   |   0   |   1   |  2 MB         | Lower 1/4
*    0   |   1   |   1   |   1   |   0   |  4 MB         | Lower 1/2
*
*/
typedef enum {
    LOCK_TP_NONE,
    LOCK_TP_TOP,
    LOCK_TP_BOTTOM,
    LOCK_TP_DUAL
} csi_spiflash_lock_region_t;
typedef enum {
    SPIFLASH_DATA_1_LINE  = 1,
    SPIFLASH_DATA_2_LINES = 2,
    SPIFLASH_DATA_4_LINES = 4
} csi_spiflash_data_line_t;
typedef union {
    csi_spi_t   spi;
    csi_qspi_t  qspi;
} csi_spi_qspi_t;

/**
\brief Flash information
*/
typedef struct {
    char    *flash_name;                  ///< Name string of spiflash
    uint32_t flash_id;                    ///< JEDEC ID  = manufature ID <<16 | device ID (ID15~ID0)
    uint32_t flash_size;                  ///< Flash chip size
    uint32_t xip_addr;                    ///< If use qspi controler to access flash ,code can be ececuted on flash ,the addr is xip addr
    uint32_t sector_size;                 ///< Sector size
    uint32_t page_size;                   ///< Page size for read or program
} csi_spiflash_info_t;

typedef struct{
    struct{
        uint8_t buswidth;                  ///< cmd buswidth
    }cmd;
    struct {
        uint8_t buswidth;                  ///< addr buswidth
    }addr;
    struct {
        uint8_t nbytes;                    ///< dummy bytes
    }dummy;
    struct {
        uint8_t buswidth;                  ///<  data buswidth
    }data;
} csi_spiflash_cmd_t;

/**
\brief Flash control block
*/
typedef struct {
    csi_spi_qspi_t spi_qspi;               ///< Spi/qspi handle
    void (*spi_cs_callback)(csi_gpio_pin_state_t value);
    void           *flash_prv_info;        ///< Point to vendor private feature struct
    int32_t (*spi_send)(void *spi, uint8_t cmd, uint32_t addr, uint32_t addr_size, const void *data, uint32_t size);
    int32_t (*spi_receive)(void *spi, uint8_t cmd, uint32_t addr, uint32_t addr_size, void *data, uint32_t size);
    csi_error_t (*set_cmd)(void *spi, csi_spiflash_cmd_t *cmd);
    void           *priv;                  ///< User private param
} csi_spiflash_t;

/**
  \brief       Initialize SPIFLASH with spi controler  and probe flash device
  \param[in]   spiflash   SPIFLASH handle
  \param[in]   spi_idx    SPI controler index
  \param[in]   spi_cs     GPIO info for chip select,if NULL, not use gpio cs
  \return      Error code
*/
csi_error_t csi_spiflash_spi_init(csi_spiflash_t *spiflash, uint32_t spi_idx, void *spi_cs_callback);

/**
  \brief       Initialize SPIFLASH with qspi controler  and probe flash device
  \param[in]   spiflash    SPIFLASH handle
  \param[in]   qspi_idx    QSPI controler index
  \return      Error code
*/
csi_error_t csi_spiflash_qspi_init(csi_spiflash_t *spiflash, uint32_t qspi_idx, void *qspi_cs_callback);

/**
  \brief       De-initialize SPIFLASH Interface based on spi controler. stops operation and releases the software resources used by the interface
  \param[in]   spiflash    SPIFLASH handle to operate
  \return      Error code
*/
void csi_spiflash_spi_uninit(csi_spiflash_t *spiflash);

/**
  \brief       De-initialize SPIFLASH Interface based on qspi controler. stops operation and releases the software resources used by the interface
  \param[in]   spiflash    SPIFLASH handle to operate
  \return      Error code
*/
void csi_spiflash_qspi_uninit(csi_spiflash_t *spiflash);


/**
  \brief       Get flash device infomation
  \param[in]   spiflash      SPIFLASH handle to operate
  \param[in]   flash_info    User storage to get flash vendor info after flash init
  \return      spiflash_info_t
*/
csi_error_t csi_spiflash_get_flash_info(csi_spiflash_t *spiflash, csi_spiflash_info_t *flash_info);


/**
  \brief       Read data from Flash
  \param[in]   spiflash   SPIFLASH handle to operate
  \param[in]   offset     Data address, offset address relative to zero
  \param[out]  data       Pointer to a buffer storing the data read from Flash
  \param[in]   size       Number of data items to read
  \return      If receive successful, this function shall return the num of data witch is received successful
               otherwise, the function shall return Error code
*/
int32_t csi_spiflash_read(csi_spiflash_t *spiflash, uint32_t offset, void *data, uint32_t size);

/**
  \brief       Program data to Flash
  \param[in]   spiflash  SPIFLASH handle to operate
  \param[in]   offset    Data address, offset address relative to zero
  \param[in]   data      Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   size      Number of data items to program
  \return      If program successful, this function shall return the num of data witch is program successful,
               otherwise, the function shall return Error code
*/
int32_t csi_spiflash_program(csi_spiflash_t *spiflash, uint32_t offset, const void *data, uint32_t size);

/**
  \brief       Erase Flash Sector
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   offset    Data address, offset address relative to zero
  \param[in]   size      Length to be erased
  \return      Error code
*/
csi_error_t csi_spiflash_erase(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size);

/**
  \brief       Read flash status register
  \param[in]   spiflash  SPIFLASH handle to operate
  \param[in]   cmd_code  Cmd code
  \param[out]  data      Data buf to save flash status register
  \param[in]   size      Register length in byte
  \return      Error code
*/
csi_error_t csi_spiflash_read_reg(csi_spiflash_t *spiflash, uint8_t cmd_code, uint8_t *data, uint32_t size);

/**
  \brief       Write status register
  \param[in]   spiflash  SPIFLASH handle to operate
  \param[in]   cmd       Cmd code
  \param[out]  data      Data buf to save flash status register
  \param[in]   size      Register length in byte
  \return      Error code
*/
csi_error_t csi_spiflash_write_reg(csi_spiflash_t *spiflash, uint8_t cmd_code, uint8_t *data, uint32_t size);


/**
  \brief       Enable spiflash write protection
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   offset      Protect flash offset,offset need protect block size aligned
  \param[in]   size        Lock size(byte)
  \return      Error code
*/
csi_error_t csi_spiflash_lock(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size);

/**
  \brief       Enable spiflash write protection
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   offset      Protect flash offset,offset need protect block size aligned
  \param[in]   size        Unlock size(byte)
  \return      Error code
*/
csi_error_t csi_spiflash_unlock(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size);

/**
  \brief       check flash is locked(write protect)
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   offset      Protect flash offset,offset need protect block size aligned
  \param[in]   size        Locked size(byte)
  \return      0:unlocked if query region overlay with locked region 1: locked if query reigon is fully in locked region
*/
int csi_spiflash_is_locked(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size);

/**
  \brief       Set QSPI data line
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   line        SPIFLASH data line mode
  \return      Error code
*/
csi_error_t csi_spiflash_config_data_line(csi_spiflash_t *spiflash, csi_spiflash_data_line_t line);

/**
  \brief       Set QSPI frequence
  \param[in]   spiflash SPIFLASH handle to operate
  \param[in]   hz       SPIFLASH frequence
  \return      The actual config frequency
*/
uint32_t csi_spiflash_frequence(csi_spiflash_t *spiflash, uint32_t hz);

/**
  \brief       Flash power down.
  \param[in]   spiflash SPIFLASH handle to operate.
  \return      error code
*/
csi_error_t csi_spiflash_release_power_down(csi_spiflash_t *spiflash);

/**
  \brief       Flash power release.
  \param[in]   spiflash SPIFLASH handle to operate.
  \return      none
*/
void csi_spiflash_power_down(csi_spiflash_t *spiflash);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_SPIFLASH_H_ */
