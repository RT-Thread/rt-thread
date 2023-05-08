/**
  ******************************************************************************
  * @file    bflb_xip_sflash.h
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
#ifndef __BL628_XIP_SFLASH_H__
#define __BL628_XIP_SFLASH_H__

#include "bflb_sflash.h"

/** @addtogroup  BL628_Peripheral_Driver
 *  @{
 */

/** @addtogroup  XIP_SFLASH
 *  @{
 */

/** @defgroup  XIP_SFLASH_Public_Types
 *  @{
 */

/*@} end of group XIP_SFLASH_Public_Types */

/** @defgroup  XIP_SFLASH_Public_Constants
 *  @{
 */

/*@} end of group XIP_SFLASH_Public_Constants */

/** @defgroup  XIP_SFLASH_Public_Macros
 *  @{
 */

/*@} end of group XIP_SFLASH_Public_Macros */

/** @defgroup  XIP_SFLASH_Public_Functions
 *  @{
 */
int bflb_xip_sflash_state_save(spi_flash_cfg_type *p_flash_cfg, uint32_t *offset,
                                   uint8_t group, uint8_t bank);
int bflb_xip_sflash_state_restore(spi_flash_cfg_type *p_flash_cfg, uint32_t offset,
                                      uint8_t group, uint8_t bank);
int bflb_xip_sflash_erase_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t start_addr,
                                        int len, uint8_t group, uint8_t bank);
int bflb_xip_sflash_write_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr,
                                        uint8_t *data, uint32_t len, uint8_t group, uint8_t bank);
int bflb_xip_sflash_read_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr,
                                       uint8_t *data, uint32_t len, uint8_t group, uint8_t bank);
int bflb_xip_sflash_get_jedecid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data,
                                              uint8_t group, uint8_t bank);
int bflb_xip_sflash_get_deviceid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t is_32bits_addr,
                                               uint8_t *data, uint8_t group, uint8_t bank);
int bflb_xip_sflash_get_uniqueid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data,
                                               uint8_t idlen, uint8_t group, uint8_t bank);
int bflb_xip_sflash_clear_status_register_need_lock(spi_flash_cfg_type *p_Flash_Cfg,
                                                        uint8_t group, uint8_t bank);
int bflb_xip_sflash_read_via_cache_need_lock(uint32_t addr, uint8_t *data, uint32_t len,
                                                 uint8_t group, uint8_t bank);
void bflb_xip_sflash_opt_enter(uint8_t *aes_enable);
void bflb_xip_sflash_opt_exit(uint8_t aes_enable);

/*@} end of group XIP_SFLASH_Public_Functions */

/*@} end of group XIP_SFLASH */

/*@} end of group BL628_Peripheral_Driver */

#endif /* __BL628_XIP_SFLASH_H__ */
