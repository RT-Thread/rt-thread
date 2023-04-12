/**
  ******************************************************************************
  * @file    bl602_sflah_ext.h
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
#ifndef __BL602_SFLAH_EXT_H__
#define __BL602_SFLAH_EXT_H__

#include "bflb_sflash.h"
#include "bl602_common.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SFLAH_EXT
 *  @{
 */

/** @defgroup  SFLAH_EXT_Public_Types
 *  @{
 */

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
int bflb_sflash_restore_from_powerdown(spi_flash_cfg_type *p_flash_cfg, uint8_t flash_cont_read, uint8_t bank);
int bflb_sflash_rcv_enable(spi_flash_cfg_type *p_flash_cfg, uint8_t r_cmd, uint8_t w_cmd, uint8_t bit_pos);
int bflb_sflash_erase_security_register(spi_flash_cfg_type *p_flash_cfg, struct sflash_sec_reg_cfg *p_sec_reg_cfg);
int bflb_sflash_program_security_register(spi_flash_cfg_type *p_flash_cfg,
                                          struct sflash_sec_reg_cfg *p_sec_reg_cfg);
int bflb_sflash_read_security_register(struct sflash_sec_reg_cfg *p_sec_reg_cfg);
int bflb_sflash_clear_status_register(spi_flash_cfg_type *p_flash_cfg);
int bflb_sflash_cache_enable_set(uint8_t way_disable);
int bflb_sflash_cache_flush(void);

/*@} end of group SFLAH_EXT_Public_Functions */

/*@} end of group SFLAH_EXT */

/*@} end of group BL602_Peripheral_Driver */

#endif /* __BL602_SFLAH_EXT_H__ */
