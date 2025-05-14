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
 * @file     spinand.h
 * @brief    header file for spinand driver
 * @version  V1.0
 * @date     17. Aug 2017
 * @model    spinand
 ******************************************************************************/
#ifndef _DRV_NANDFLASH_H_
#define _DRV_NANDFLASH_H_


#include <stdint.h>
#include <drv/gpio.h>
#include <drv/qspi.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define   SPINAND_DEF_SPEED             (1000000)
#define   SPIANND_DEF_MAX_WAIT_TIME     (1000)                             ///<  max wait time in ms

typedef union {
    csi_qspi_t  qspi;                                                      ///<  hold qspi object
} csi_nand_spi_qspi_t;


typedef struct {
uint32_t       target;                                                      ///< target in chip
uint32_t       lun;                                                         ///< lun in target
uint32_t       plane;                                                       ///< plane number in lun
uint32_t       block;                                                       ///< block index in lun
uint32_t       page;                                                        ///< page  index in lun
uint32_t       offset;                                                      ///< column offset within page
}csi_nand_pos_t;

typedef enum{
    SPI_MEM_NODATA,                                                         ///< no data portion
    SPI_MEM_DATA_IN,                                                        ///< read data
    SPI_MEM_DATA_OUT                                                        ///< write data
}csi_spi_mem_dir_t;

typedef struct{

  struct{
    uint8_t buswidth;                                                       ///< cmd buswidth
    uint8_t opcode;                                                         ///< cmd code
  }cmd;

  struct {
    uint8_t buswidth;                                                       ///< addr buswidth
    uint8_t nbytes;                                                         ///< bytes of addr
    uint64_t val;                                                           ///< addr value
  }addr;

  struct {
    uint8_t nbytes;                                                         ///< dummy bytes
    uint8_t buswidth;                                                       ///< bus width
  }dummy;


  struct {
    uint8_t buswidth;                                                       ///<  data buswidth
    uint32_t nbytes;                                                        ///<  data len
    csi_spi_mem_dir_t dir;                                                  ///<  data xfer dir
    union{
      void*  in;                                                            ///<  read data buf ptr
      void*  out;                                                           ///<  write datat buf ptr
    }buf;
  }data;

}spi_mem_op_t;

typedef struct  {
    const uint8_t *id;                                                        ///< point to chip id array
    const uint8_t len;                                                        ///< id length
}csi_spinand_id_t;

typedef struct {
  uint8_t   id[4];                                                          ///< id data
  uint8_t   len;                                                            ///< id length
}csi_nand_id_t;


typedef struct{
  uint16_t strength;                                                        ///< number of hw-ecc engine bits
  uint16_t step_size;                                                       ///< corect size by ecc per-step
}csi_nand_ecc_req_t;

typedef struct {
    uint32_t bits_per_cell;                                                   ///< bit per-cell
    uint32_t pagesize;                                                        ///< page size
    uint32_t oobsize;                                                         ///< spare area size
    uint32_t pages_per_eraseblock;                                            ///< pages per block
    uint32_t eraseblocks_per_lun;                                             ///< blocks per lun(logic unit number== max block index )
    uint32_t max_bad_eraseblocks_per_lun;                                     ///< max bad blocks per lun
    uint32_t planes_per_lun;                                                  ///< planes per-lun
    uint32_t luns_per_target;                                                 ///< luns per die
  uint32_t ntargets;                                                        ///< target index
}csi_nand_mem_layout_t;



typedef struct  {
    char                        *model;                                       ///<   chip name of vendor
    uint32_t                     flags;                                       ///<   chip-specific feature bits group
    csi_spinand_id_t             devid;                                       ///<   devid of chip
    csi_nand_mem_layout_t        memorg;                                      ///<   mem layout of chip
    csi_nand_ecc_req_t           eccreq;                                      ///<   ecc capabilty of chip
    csi_error_t (*select_target)(void *spinand, uint32_t target);             ///<   select target
  csi_error_t (*check_ecc_status)(void *spinand,uint8_t status);            ///<   check vendor specific ecc status
}csi_spinand_info_t;


typedef struct {
    csi_error_t (*init)  (void *spinand);                                    ///< vendor chip inition
    void       (*uninit) (void *spinand);                                    ///< vendor chip uninition
}csi_spinand_manufacturer_ops_t;

typedef struct {
    uint8_t                                  id;                              ///< vendor id
    char                                     *name;                           ///< vendor name
    const csi_spinand_info_t                 *chips;                          ///< vendor chip param
    uint32_t                                 nchips;                          ///< chips number supported
    const csi_spinand_manufacturer_ops_t     *ops;                            ///< vendor specific operations
}csi_spinand_manufacturer_t;


typedef struct {
  char                                     *model_name;                     ///< name of nand-device module
  uint16_t                                 page_size;                       ///< page-size of nand-device
  uint16_t                                 oob_size;                        ///< oob-size(spare size) of nand-device
  uint16_t                                 pages_per_block;                 ///< pages-per-block
  uint16_t                                 max_bad_blocks;                  ///< max possible bad blocks of nand-device
  uint32_t                                 total_blocks;                    ///< total blocks of nand-device
}csi_spinand_dev_params_t;

typedef struct
{
  void             *xfer_buf;                                             ///<  point to xfer data buf
  uint32_t         xfer_buf_len;                                          ///<  length of xfer buf ,count in byte
  uint16_t         rxfer_copy_offset;                                     ///<  copy offset from word-aligned buf
  uint16_t         rxfer_origin_len;                                      ///<  copy length from word-aligned buf
}csi_xfer_data_buf_t;


/**
\brief Flash control block
*/
typedef struct {
    #define SPINAND_SCRAT_BUF_LEN   4                                      ///< scratch buf len
    csi_nand_spi_qspi_t spi_qspi;                                               ///< Spi/qspi handle
    uint8_t        scractbuf[SPINAND_SCRAT_BUF_LEN];                       ///< scracthbuf for read/write id or reg
    uint8_t        cur_target;                                             ///< current target
    uint16_t       max_tx_size;                                            ///< max tx op size
    uint16_t       max_rx_size;                                            ///< max rx op size
    csi_xfer_data_buf_t  xfer;                                             ///< xfer buf
    csi_spinand_info_t *chip_info;                                         ///< Point to vendor private feature struct
    csi_spinand_manufacturer_t *maf;                                       ///< point to manufacture
    void (*spi_cs_callback)(csi_gpio_pin_state_t value);                   ///< gpio chip select for spi or qspi
    csi_error_t (*spi_mem)(void *spinand,spi_mem_op_t *op);                ///< spi-mem op function
    void           *priv;                                                  ///< User private param
} csi_spinand_t;

typedef enum {
    XFER_CPU_POLLING,                                                      ///< transfer by qspi with cpu polling mode
    XFER_DMA,                                                              ///< transfer by qspi with external dma engine
    XFER_INTR,                                                             ///< transfer by qspi with cpu-interrut
}csi_spinand_xfer_t;

/**
  \brief       Initialize NANDFLASH with qspi controler  and probe flash device
  \param[in]   spinand              NANDFLASH handle
  \param[in]   qspi_idx             QSPI controler index
  \param[in]   spi_cs_callback      GPIO info for chip select,if NULL, not use gpio cs
  \return      Error code
*/
csi_error_t csi_spinand_qspi_init(csi_spinand_t *spinand, uint32_t qspi_idx,void *gpio_cs_callback);

/**
  \brief       De-initialize NANDFLASH Interface based on spi controler. stops operation and releases the software resources used by the interface
  \param[in]   spinand    NANDFLASH handle to operate
  \return      Error code
*/
void csi_spinand_qspi_uninit(csi_spinand_t *spinand);

/**
  \brief       set xfer mode
  \param[in]   spinand    NANDFLASH handle to operate
  \param[in]   xfer_mode  please ref csi_spinand_xfer_t
  \return      Error code
*/
csi_error_t csi_spinand_set_xfer_mode(csi_spinand_t *spinand,csi_spinand_xfer_t xfer_mode);


/**
  \brief       get flash device infomation
  \param[in]   spinand        NANDFLASH handle to operate
  \param[in]   flash_info    User storage to get flash vendor info after flash init
  \return      spinand_info_t
*/

csi_error_t csi_spinand_get_flash_info(csi_spinand_t *spinand, csi_spinand_dev_params_t *flash_info);

/**
  \brief       Read data from Flash
  \param[in]   spinand    NANDFLASH handle to operate
  \param[in]   offset    Data address, offset address relative to zero
  \param[out]  data      Pointer to a buffer storing the data read from Flash
  \param[in]   cnt       Number of data items to read
  \return      If receive successful, this function shall return the num of data witch is received successfulful
               otherwise, the function shall return Error code
*/
int32_t csi_spinand_read(csi_spinand_t *spinand, uint64_t offset, void *data, uint32_t size);


/**
  \brief       Read spare data from specific page
  \param[in]   spinand    NANDFLASH handle to operate
  \param[in]   page_addr  page addr, address relative to zero, addr need page size aligned
  \param[in]   spare_offset  offset address within the spare area of the page
  \param[out]  data      Pointer to a buffer storing the data read from Flash
  \param[in]   size       Number of data items to read
  \return      If receive successful, this function shall return the num of data witch is received successfully
               otherwise, the function shall return Error code
*/
int32_t csi_spinand_read_spare_data(csi_spinand_t *spinand,uint64_t page_addr,uint32_t spare_offset,void *data, uint32_t size);

/**
  \brief       write data to Flash
  \param[in]   spinand   NANDFLASH handle to operate
  \param[in]   offset    Data address, offset address relative to zero
  \param[in]   data      Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   size      Number of data items to program
  \return      If program successful, this function shall return the num of data witch is programed successfully
               otherwise, the function shall return Error code
*/
int32_t csi_spinand_write(csi_spinand_t *spinand, uint64_t offset, const void *data, uint64_t size);

/**
  \brief       write spare data to specific page
  \param[in]   spinand    NANDFLASH handle to operate
  \param[in]   page_addr page addr, address relative to zero, addr need page size aligned
  \param[in]   spare_offset  offset address within the spare area of the page
  \param[out]  data      Pointer to a buffer storing the data write to Flash
  \param[in]   size       Number of data items to write
  \return      If program successful, this function shall return the num of data witch is programed successfully
               otherwise, the function shall return Error code
*/
int32_t csi_spinand_write_spare_data(csi_spinand_t *spinand,uint64_t page_addr,uint32_t spare_offset,void *data, uint32_t size);


/**
  \brief       Erase Flash Sector
  \param[in]   spinand    NANDFLASH handle to operate
  \param[in]   offset    Data address, offset address relative to zero
  \param[in]   size      Length to be erased
  \param[out]  last erased block addr
  \return      Error code
*/
csi_error_t csi_spinand_erase(csi_spinand_t *spinand, uint64_t offset, uint64_t size, uint64_t *last_fail_addr);

/**
  \brief       check whether the block is bad
  \param[in]   spinand      NANDFLASH handle to operate
  \param[in]   block_addr  block addr (count in bytes)
  \return      1: bad      0: not bad    <0  err code
*/


int32_t  csi_spinand_block_is_bad(csi_spinand_t *spinand,uint64_t block_addr);

/**
  \brief       mark block as a bad block
  \param[in]   spinand      NANDFLASH handle to operate
  \param[in]   block_addr  block addr (count in bytes)
  \return      Error code
*/
csi_error_t  csi_spinand_block_mark_bad(csi_spinand_t *spinand, uint64_t block_addr);

/**
  \brief       reset spinand device
  \param[in]   spinand      NANDFLASH handle to operate
  \return      Error code
*/
int32_t  csi_spinand_reset(csi_spinand_t *spinand);

/**
  \brief       Set QSPI frequence
  \param[in]   spinand NANDFLASH handle to operate
  \param[in]   hz       NANDFLASH frequence
  \return      The actual config frequency
*/
uint32_t csi_spinand_frequence(csi_spinand_t *spinand, uint32_t hz);



#ifdef __cplusplus
}
#endif

#endif /* _DRV_NANDFLASH_H_ */
