/**
  ******************************************************************************
  * @file    bl602_sf_cfg_ext.h
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
#ifndef __BL602_SF_CFG_EXT_H__
#define __BL602_SF_CFG_EXT_H__

#include "string.h"
#include "bflb_sflash.h"
#include "bflb_sf_ctrl.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SF_CFG_EXT
 *  @{
 */

/** @defgroup  SF_CFG_EXT_Public_Types
 *  @{
 */

/*@} end of group SF_CFG_EXT_Public_Types */

/** @defgroup  SF_CFG_EXT_Public_Constants
 *  @{
 */

/*@} end of group SF_CFG_EXT_Public_Constants */

/** @defgroup  SF_CFG_EXT_Public_Macros
 *  @{
 */

/*@} end of group SF_CFG_EXT_Public_Macros */

/** @defgroup  SF_CFG_EXT_Public_Functions
 *  @{
 */
int bflb_sf_cfg_get_flash_cfg_need_lock_ext(uint32_t flash_id, spi_flash_cfg_type *p_flash_cfg,
                                            uint8_t group, uint8_t bank);
uint32_t bflb_sf_cfg_flash_identify_ext(uint8_t call_from_flash, uint8_t flash_pin_cfg, uint8_t restore_default,
                                        spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank);

/*@} end of group SF_CFG_EXT_Public_Functions */

/*@} end of group SF_CFG_EXT */

/*@} end of group BL602_Peripheral_Driver */

#endif /* __BL602_SF_CFG_EXT_H__ */
