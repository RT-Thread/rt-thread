/**
  ******************************************************************************
  * @file    bflb_spi_psram.h
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
#ifndef __BFLB_SPI_PSRAM_H__
#define __BFLB_SPI_PSRAM_H__

#include "sf_ctrl_reg.h"
#include "bflb_common.h"
#include "bflb_sf_ctrl.h"

/** @addtogroup  BFLB_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PSRAM
 *  @{
 */

/** @defgroup  PSRAM_Public_Types
 *  @{
 */

/**
 *  @brief Psram drive strength type definition
 */

#define PSRAM_DRIVE_STRENGTH_50_OHMS      0  /*!< Drive strength 50 ohms(default) */
#define PSRAM_DRIVE_STRENGTH_100_OHMS     1  /*!< Drive strength 100 ohms */
#define PSRAM_DRIVE_STRENGTH_200_OHMS     2  /*!< Drive strength 200 ohms */

/**
 *  @brief Psram burst length size type definition
 */
#define PSRAM_BURST_LENGTH_16_BYTES       0  /*!< Burst Length 16 bytes */
#define PSRAM_BURST_LENGTH_32_BYTES       1  /*!< Burst Length 32 bytes */
#define PSRAM_BURST_LENGTH_64_BYTES       2  /*!< Burst Length 64 bytes */
#define PSRAM_BURST_LENGTH_512_BYTES      3 /*!< Burst Length 512 bytes(default) */

/**
 *  @brief Psram ctrl mode type definition
 */
#define PSRAM_SPI_CTRL_MODE               0  /*!< Psram SPI ctrl mode */
#define PSRAM_QPI_CTRL_MODE               1  /*!< Psram QPI ctrl mode */

/**
 *  @brief Psram ctrl configuration structure type definition
 */
struct spi_psram_cfg_type {
    uint8_t read_id_cmd;                  /*!< Read ID command */
    uint8_t read_id_dmy_clk;              /*!< Read ID command dummy clock */
    uint8_t burst_toggle_cmd;             /*!< Burst toggle length command */
    uint8_t reset_enable_cmd;             /*!< Psram reset enable command */
    uint8_t reset_cmd;                    /*!< Psram reset command */
    uint8_t enter_quad_mode_cmd;          /*!< Psram enter quad mode command */
    uint8_t exit_quad_mode_cmd;           /*!< Psram exit quad mode command */
    uint8_t read_reg_cmd;                 /*!< Read register command */
    uint8_t read_reg_dmy_clk;             /*!< Read register command dummy clock */
    uint8_t write_reg_cmd;                /*!< Write register command */
    uint8_t read_cmd;                     /*!< Psram read command */
    uint8_t read_dmy_clk;                 /*!< Psram read command dummy clock */
    uint8_t f_read_cmd;                   /*!< Psram fast read command */
    uint8_t f_read_dmy_clk;               /*!< Psram fast read command dummy clock */
    uint8_t f_read_quad_cmd;              /*!< Psram fast read quad command */
    uint8_t f_read_quad_dmy_clk;          /*!< Psram fast read quad command dummy clock */
    uint8_t write_cmd;                    /*!< Psram write command */
    uint8_t quad_write_cmd;               /*!< Psram quad write command */
    uint16_t page_size;                   /*!< Psram page size */
#if defined(BL702L)
    uint8_t burst_toggle_en;              /*!< Psram burst toggle mode enable */
#endif
    uint8_t ctrl_mode;                    /*!< Psram ctrl mode */
    uint8_t drive_strength;               /*!< Psram drive strength */
    uint8_t burst_length;                 /*!< Psram burst length size */
};

/*@} end of group PSRAM_Public_Types */

/** @defgroup  PSRAM_Public_Constants
 *  @{
 */

/*@} end of group PSRAM_Public_Constants */

/** @defgroup  PSRAM_Public_Macros
 *  @{
 */

/*@} end of group PSRAM_Public_Macros */

/** @defgroup  PSRAM_Public_Functions
 *  @{
 */

/**
 *  @brief PSRAM Functions
 */
void bflb_psram_init(struct spi_psram_cfg_type *psram_cfg, struct sf_ctrl_cmds_cfg *cmds_cfg,
                     struct sf_ctrl_psram_cfg *sf_ctrl_psram_cfg);
void bflb_psram_readreg(struct spi_psram_cfg_type *psram_cfg, uint8_t *reg_value);
void bflb_psram_writereg(struct spi_psram_cfg_type *psram_cfg, uint8_t *reg_value);
int bflb_psram_setdrivestrength(struct spi_psram_cfg_type *psram_cfg);
int bflb_psram_setburstwrap(struct spi_psram_cfg_type *psram_cfg);
void bflb_psram_readid(struct spi_psram_cfg_type *psram_cfg, uint8_t *data);
int bflb_psram_enterquadmode(struct spi_psram_cfg_type *psram_cfg);
int bflb_psram_exitquadmode(struct spi_psram_cfg_type *psram_cfg);
int bflb_psram_toggleburstlength(struct spi_psram_cfg_type *psram_cfg, uint8_t ctrl_mode);
int bflb_psram_softwarereset(struct spi_psram_cfg_type *psram_cfg, uint8_t ctrl_mode);
int bflb_psram_set_idbus_cfg(struct spi_psram_cfg_type *psram_cfg, uint8_t io_mode, uint32_t addr, uint32_t len);
int bflb_psram_cache_write_set(struct spi_psram_cfg_type *psram_cfg, uint8_t io_mode, uint8_t wt_en,
                               uint8_t wb_en, uint8_t wa_en);
int bflb_psram_write(struct spi_psram_cfg_type *psram_cfg, uint8_t io_mode, uint32_t addr, uint8_t *data, uint32_t len);
int bflb_psram_read(struct spi_psram_cfg_type *psram_cfg, uint8_t io_mode, uint32_t addr, uint8_t *data, uint32_t len);

/*@} end of group PSRAM_Public_Functions */

/*@} end of group PSRAM */

/*@} end of group BFLB_Peripheral_Driver */

#endif /* __BFLB_SPI_PSRAM_H__ */
