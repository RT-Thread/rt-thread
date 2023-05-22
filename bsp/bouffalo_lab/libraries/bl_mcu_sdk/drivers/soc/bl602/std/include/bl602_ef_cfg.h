/**
  ******************************************************************************
  * @file    bl602_ef_cfg.h
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
#ifndef __BL602_EF_CFG_H__
#define __BL602_EF_CFG_H__

#include "bl602_common.h"
#include "bflb_ef_ctrl.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  EF_CTRL
 *  @{
 */

/** @defgroup  EF_CTRL_Public_Types
 *  @{
 */

/**
 *  @brief Efuse Ctrl key slot type definition
 */
typedef struct {
    uint32_t rsvd_18_0  : 19; /*!< Reserved */
    uint32_t chip_ver   : 3;  /*!< chip revision */
    uint32_t rsvd_23_22 : 2;  /*!< Reserved */
    uint32_t extInfo    : 3;  /*!< Efuse device info extension: 1:BL602C, 2:BL602L, 3:BL602E, 4:POS/AT */
    uint32_t memoryInfo : 2;  /*!< Efuse memory info 0:no memory, 1:1MB flash, 2:2MB flash, 3:4MB flash */
    uint32_t rsvd_29    : 1;  /*!< Efuse reserved */
    uint32_t mcuInfo    : 1;  /*!< Efuse mcu info 0:wifi, 1:mcu */
    uint32_t pinInfo    : 1;  /*!< Efuse pin info 0:QFN32, 1:QFN40 */
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

/*@} end of group BL602_Peripheral_Driver */

#endif /* __BL602_EF_CFG_H__ */
