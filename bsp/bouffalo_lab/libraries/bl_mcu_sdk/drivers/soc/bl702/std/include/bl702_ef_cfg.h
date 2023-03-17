/**
  ******************************************************************************
  * @file    bl702_ef_cfg.h
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
#ifndef __BL702_EF_CFG_H__
#define __BL702_EF_CFG_H__

#include "bflb_ef_ctrl.h"
#include "bl702_common.h"

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  EF_CTRL
 *  @{
 */

/** @defgroup  EF_CTRL_Public_Types
 *  @{
 */
/**
 *  @brief Efuse analog device info type definition
 */
typedef struct
{
    uint32_t rsvd_21_0   : 22; /*!< Reserved */
    uint32_t sf_swap_cfg : 2;  /*!< 0:swap none, 1:swap SF2_CS & SF2_IO2, 2:swap SF2_IO0 & SF2_IO3, 3:swap both */
    uint32_t psram_cfg   : 2;  /*!< 0:no psram, 1:2MB psram, 2:external psram, 3:reserved */
    uint32_t flash_cfg   : 3;  /*!< 0:external flash SF2, 1:0.5MB flash, 2:1MB flash, 3:external flash SF1, 5:2MB flash */
    uint32_t rsvd_29     : 1;  /*!< Reserved */
    uint32_t pkg_info    : 2;  /*!< 0:QFN32, 1:QFN40, 2:QFN48, 3:reserved */
} bflb_efuse_device_info_type;

/*@} end of group EF_CTRL_Public_Types */

/** @defgroup  EF_CTRL_Public_Constants
 *  @{
 */

/*@} end of group EF_CTRL_Public_Constants */

/** @defgroup  EF_CTRL_Public_Macros
 *  @{
 */

/*@} end of group EF_CTRL_Public_Macros */

/** @defgroup  EF_CTRL_Public_Functions
 *  @{
 */
void bflb_efuse_switch_cpu_clock_save(void);
void bflb_efuse_switch_cpu_clock_restore(void);
void bflb_ef_ctrl_get_device_info(bflb_efuse_device_info_type *deviceInfo);
uint32_t bflb_ef_ctrl_get_common_trim_list(const bflb_ef_ctrl_com_trim_cfg_t **trim_list);

/*@} end of group EF_CTRL_Public_Functions */

/*@} end of group EF_CTRL */

/*@} end of group BL702_Peripheral_Driver */

#endif /* __BL702_EF_CFG_H__ */
