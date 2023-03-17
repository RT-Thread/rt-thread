/**
  ******************************************************************************
  * @file    bl628_sflah.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL628_SFLAH_H__
#define __BL628_SFLAH_H__

#include "bflb_sf_ctrl.h"

/** @addtogroup  BL628_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SFLAH
 *  @{
 */

/** @defgroup  SFLAH_Public_Types
 *  @{
 */

/**
 *  @brief Serial flash configuration structure type definition
 */
typedef struct
{
    uint8_t  io_mode;                   /*!< Serail flash interface mode,bit0-3:IF mode,bit4:unwrap,bit5:32-bits addr mode support */
    uint8_t  c_read_support;            /*!< Support continuous read mode,bit0:continuous read mode support,bit1:read mode cfg */
    uint8_t  clk_delay;                 /*!< SPI clock delay,bit0-3:delay,bit4-6:pad delay */
    uint8_t  clk_invert;                /*!< SPI clock phase invert,bit0:clck invert,bit1:rx invert,bit2-4:pad delay,bit5-7:pad delay */
    uint8_t  reset_en_cmd;              /*!< Flash enable reset command */
    uint8_t  reset_cmd;                 /*!< Flash reset command */
    uint8_t  reset_c_read_cmd;          /*!< Flash reset continuous read command */
    uint8_t  reset_c_read_cmd_size;     /*!< Flash reset continuous read command size */
    uint8_t  jedec_id_cmd;              /*!< JEDEC ID command */
    uint8_t  jedec_id_cmd_dmy_clk;      /*!< JEDEC ID command dummy clock */
#if defined(BL702L) || defined(BL702) || defined(BL602)
    uint8_t  qpi_jedec_id_cmd;          /*!< QPI JEDEC ID comamnd */
    uint8_t  qpi_jedec_id_cmd_dmy_clk;  /*!< QPI JEDEC ID command dummy clock */
#else
    uint8_t  enter_32bits_addr_cmd;     /*!< Enter 32-bits addr command */
    uint8_t  exit_32bits_addr_cmd;      /*!< Exit 32-bits addr command */
#endif
    uint8_t  sector_size;               /*!< *1024bytes */
    uint8_t  mid;                       /*!< Manufacturer ID */
    uint16_t page_size;                 /*!< Page size */
    uint8_t  chip_erase_cmd;            /*!< Chip erase cmd */
    uint8_t  sector_erase_cmd;          /*!< Sector erase command */
    uint8_t  blk32_erase_cmd;           /*!< Block 32K erase command,some Micron not support */
    uint8_t  blk64_erase_cmd;           /*!< Block 64K erase command */
    uint8_t  write_enable_cmd;          /*!< Need before every erase or program */
    uint8_t  page_program_cmd;          /*!< Page program cmd */
    uint8_t  qpage_program_cmd;         /*!< QIO page program cmd */
    uint8_t  qpp_addr_mode;             /*!< QIO page program address mode */
    uint8_t  fast_read_cmd;             /*!< Fast read command */
    uint8_t  fr_dmy_clk;                /*!< Fast read command dummy clock */
    uint8_t  qpi_fast_read_cmd;         /*!< QPI fast read command */
    uint8_t  qpi_fr_dmy_clk;            /*!< QPI fast read command dummy clock */
    uint8_t  fast_read_do_cmd;          /*!< Fast read dual output command */
    uint8_t  fr_do_dmy_clk;             /*!< Fast read dual output command dummy clock */
    uint8_t  fast_read_dio_cmd;         /*!< Fast read dual io comamnd */
    uint8_t  fr_dio_dmy_clk;            /*!< Fast read dual io command dummy clock */
    uint8_t  fast_read_qo_cmd;          /*!< Fast read quad output comamnd */
    uint8_t  fr_qo_dmy_clk;             /*!< Fast read quad output comamnd dummy clock */
    uint8_t  fast_read_qio_cmd;         /*!< Fast read quad io comamnd */
    uint8_t  fr_qio_dmy_clk;            /*!< Fast read quad io comamnd dummy clock */
    uint8_t  qpi_fast_read_qio_cmd;     /*!< QPI fast read quad io comamnd */
    uint8_t  qpi_fr_qio_dmy_clk;        /*!< QPI fast read QIO dummy clock */
    uint8_t  qpi_page_program_cmd;      /*!< QPI program command */
    uint8_t  write_vreg_enable_cmd;     /*!< Enable write reg */
    uint8_t  wr_enable_index;           /*!< Write enable register index */
    uint8_t  qe_index;                  /*!< Quad mode enable register index */
    uint8_t  busy_index;                /*!< Busy status register index */
    uint8_t  wr_enable_bit;             /*!< Write enable bit pos */
    uint8_t  qe_bit;                    /*!< Quad enable bit pos */
    uint8_t  busy_bit;                  /*!< Busy status bit pos */
    uint8_t  wr_enable_write_reg_len;   /*!< Register length of write enable */
    uint8_t  wr_enable_read_reg_len;    /*!< Register length of write enable status */
    uint8_t  qe_write_reg_len;          /*!< Register length of contain quad enable */
    uint8_t  qe_read_reg_len;           /*!< Register length of contain quad enable status */
    uint8_t  release_powerdown;         /*!< Release power down command */
    uint8_t  busy_read_reg_len;         /*!< Register length of contain busy status */
    uint8_t  read_reg_cmd[4];           /*!< Read register command buffer */
    uint8_t  write_reg_cmd[4];          /*!< Write register command buffer */
    uint8_t  enter_qpi;                 /*!< Enter qpi command */
    uint8_t  exit_qpi;                  /*!< Exit qpi command */
    uint8_t  c_read_mode;               /*!< Config data for continuous read mode */
    uint8_t  c_rexit;                   /*!< Config data for exit continuous read mode */
    uint8_t  burst_wrap_cmd;            /*!< Enable burst wrap command */
    uint8_t  burst_wrap_cmd_dmy_clk;    /*!< Enable burst wrap command dummy clock */
    uint8_t  burst_wrap_data_mode;      /*!< Data and address mode for this command */
    uint8_t  burst_wrap_data;           /*!< Data to enable burst wrap */
    uint8_t  de_burst_wrap_cmd;         /*!< Disable burst wrap command */
    uint8_t  de_burst_wrap_cmd_dmy_clk; /*!< Disable burst wrap command dummy clock */
    uint8_t  de_burst_wrap_data_mode;   /*!< Data and address mode for this command */
    uint8_t  de_burst_wrap_data;        /*!< Data to disable burst wrap */
    uint16_t time_e_sector;             /*!< 4K erase time */
    uint16_t time_e_32k;                /*!< 32K erase time */
    uint16_t time_e_64k;                /*!< 64K erase time */
    uint16_t time_page_pgm;             /*!< Page program time */
    uint16_t time_ce;                   /*!< Chip erase time in ms */
    uint8_t  pd_delay;                  /*!< Release power down command delay time for wake up */
    uint8_t  qe_data;                   /*!< QE set data */
} __attribute__((packed)) spi_flash_cfg_type;

/**
 *  @brief Serial flash security register configuration
 */
struct sflash_sec_reg_cfg
{
    uint8_t  erase_cmd;         /*!< Erase security register command */
    uint8_t  program_cmd;       /*!< Program security register command */
    uint8_t  read_cmd;          /*!< Read security register command */
    uint8_t  enter_sec_opt_cmd; /*!< Enter security register option mode command */
    uint8_t  exit_sec_opt_cmd;  /*!< Exit security register option mode command */
    uint8_t  block_num;         /*!< Security register block number */
    uint8_t  *data;             /*!< Data pointer to be program/read */
    uint32_t addr;              /*!< Start address to be program/read */
    uint32_t len;               /*!< Data length to be program/read */
};
/*@} end of group SFLAH_Public_Types */

/** @defgroup  SFLAH_Public_Constants
 *  @{
 */

/*@} end of group SFLAH_Public_Constants */

/** @defgroup  SFLAH_Public_Macros
 *  @{
 */
#define BFLB_SPIFLASH_BLK32K_SIZE (32 * 1024)
#define BFLB_SPIFLASH_BLK64K_SIZE (64 * 1024)
#define BFLB_SPIFLASH_CMD_INVALID 0xff

/*@} end of group SFLAH_Public_Macros */

/** @defgroup  SFLAH_Public_Functions
 *  @{
 */
#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
void bflb_sflash_init(const struct sf_ctrl_cfg_type *p_sf_ctrl_cfg, const struct sf_ctrl_bank2_cfg *p_bank2_cfg);
#else
void bflb_sflash_init(const struct sf_ctrl_cfg_type *p_sf_ctrl_cfg);
#endif
int bflb_sflash_set_spi_mode(uint8_t mode);
int bflb_sflash_read_reg(spi_flash_cfg_type *flash_cfg, uint8_t reg_index, uint8_t *reg_value, uint8_t reg_len);
int bflb_sflash_write_reg(spi_flash_cfg_type *flash_cfg, uint8_t reg_index, uint8_t *reg_value, uint8_t reg_len);
int bflb_sflash_read_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t read_reg_cmd, uint8_t *reg_value,
                                      uint8_t reg_len);
int bflb_sflash_write_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t write_reg_cmd, uint8_t *reg_value,
                                       uint8_t reg_len);
int bflb_sflash_busy(spi_flash_cfg_type *flash_cfg);
int bflb_sflash_write_enable(spi_flash_cfg_type *flash_cfg);
int bflb_sflash_qspi_enable(spi_flash_cfg_type *flash_cfg);
int bflb_sflash_qspi_disable(spi_flash_cfg_type *flash_cfg);
void bflb_sflash_volatile_reg_write_enable(spi_flash_cfg_type *flash_cfg);
int bflb_sflash_chip_erase(spi_flash_cfg_type *flash_cfg);
int bflb_sflash_sector_erase(spi_flash_cfg_type *flash_cfg, uint32_t sector_num);
int bflb_sflash_blk32_erase(spi_flash_cfg_type *flash_cfg, uint32_t blk_num);
int bflb_sflash_blk64_erase(spi_flash_cfg_type *flash_cfg, uint32_t blk_num);
int bflb_sflash_erase(spi_flash_cfg_type *flash_cfg, uint32_t start_addr, uint32_t end_addr);
void bflb_sflash_get_uniqueid(uint8_t *data, uint8_t id_len);
void bflb_sflash_get_jedecid(spi_flash_cfg_type *flash_cfg, uint8_t *data);
void bflb_sflash_get_deviceid(uint8_t *data, uint8_t is_32bits_addr);
void bflb_sflash_powerdown(void);
void bflb_sflash_release_powerdown(spi_flash_cfg_type *flash_cfg);
int bflb_sflash_restore_from_powerdown(spi_flash_cfg_type *flash_cfg, uint8_t flash_cont_read, uint8_t bank);
void bflb_sflash_set_burst_wrap(spi_flash_cfg_type *flash_cfg);
void bflb_sflash_disable_burst_wrap(spi_flash_cfg_type *flash_cfg);
#ifdef BFLB_SF_CTRL_32BITS_ADDR_ENABLE
int bflb_sflash_set_32bits_addr_mode(spi_flash_cfg_type *flash_cfg, uint8_t en_32bits_addr);
#endif
int bflb_sflash_software_reset(spi_flash_cfg_type *flash_cfg);
void bflb_sflash_reset_continue_read(spi_flash_cfg_type *flash_cfg);
int bflb_sflash_set_xip_cfg(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint8_t cont_read, uint32_t addr,
                            uint32_t len, uint8_t bank);
int bflb_sflash_xip_read_enable(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint8_t cont_read, uint8_t bank);
void bflb_sflash_xip_read_disable(void);
int bflb_sflash_rcv_enable(spi_flash_cfg_type *flash_cfg, uint8_t r_cmd, uint8_t w_cmd, uint8_t bit_pos);
int bflb_sflash_erase_security_register(spi_flash_cfg_type *flash_cfg, struct sflash_sec_reg_cfg *p_sec_reg_cfg);
int bflb_sflash_program_security_register(spi_flash_cfg_type *flash_cfg, struct sflash_sec_reg_cfg *p_sec_reg_cfg);
int bflb_sflash_read_security_register(struct sflash_sec_reg_cfg *p_sec_reg_cfg);
int bflb_sflash_clear_status_register(spi_flash_cfg_type *flash_cfg);
int bflb_sflash_read(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint8_t cont_read, uint32_t addr, uint8_t *data,
                         uint32_t len);
int bflb_sflash_program(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint32_t addr, uint8_t *data, uint32_t len);

/*@} end of group SFLAH_Public_Functions */

/*@} end of group SFLAH */

/*@} end of group BL628_Peripheral_Driver */

#endif /* __BL628_SFLAH_H__ */
