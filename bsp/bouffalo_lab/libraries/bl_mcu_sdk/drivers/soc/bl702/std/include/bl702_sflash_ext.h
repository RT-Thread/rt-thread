/**
  ******************************************************************************
  * @file    bl702_sflah_ext.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 Bouffalo Lab</center></h2>
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
#ifndef __BL702_SFLAH_EXT_H__
#define __BL702_SFLAH_EXT_H__

#include "bflb_sflash.h"
#include "bl702_common.h"

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SFLAH_EXT
 *  @{
 */

/** @defgroup  SFLAH_EXT_Public_Types
 *  @{
 */

/**
 *  @brief Serail flash protect KH25V40 type definition
 */
#define SFLASH_KH25V40_PROTECT_NONE         0  /*!< SFlash no protect KH25V40 */
#define SFLASH_KH25V40_PROTECT_448KTO512K   1  /*!< SFlash protect KH25V40 448K to 512K */
#define SFLASH_KH25V40_PROTECT_384KTO512K   2  /*!< SFlash protect KH25V40 384K to 512K */
#define SFLASH_KH25V40_PROTECT_256KTO512K   3  /*!< SFlash protect KH25V40 256K to 512K */
#define SFLASH_KH25V40_PROTECT_ALL          4  /*!< SFlash protect KH25V40 0K to 512K */

/*@} end of group SFLAH_EXT_Public_Types */

/** @defgroup  SFLAH_EXT_Public_Constants
 *  @{
 */

/*@} end of group SFLAH_EXT_Public_Constants */

/** @defgroup  SFLAH_EXT_Public_Macros
 *  @{
 */

/*@} end of group SFLAH_EXT_Public_Macros */

/** @defgroup  SFLAH_EXT_Public_Functions
 *  @{
 */
int bflb_sflash_kh25v40_write_protect(spi_flash_cfg_type *flash_cfg, uint8_t protect);
int bflb_sflash_read_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t read_reg_cmd, uint8_t *reg_value,
                                  uint8_t reg_len);
int bflb_sflash_write_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t read_reg_cmd, uint8_t *reg_value,
                                   uint8_t reg_len);
int bflb_sflash_clear_status_register(spi_flash_cfg_type *p_flash_cfg);

/*@} end of group SFLAH_EXT_Public_Functions */

/*@} end of group SFLAH_EXT */

/*@} end of group BL702_Peripheral_Driver */

#endif /* __BL702_SFLAH_EXT_H__ */
