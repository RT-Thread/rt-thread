/**
  ******************************************************************************
  * @file    bl808_osd_probe.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 Bouffalo Lab</center></h2>
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

#ifndef __BL808_OSD_PROBE_H__
#define __BL808_OSD_PROBE_H__

#include <stdint.h>
#include "bl808_common.h"
#include "osd_probe_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  OSD_PROBE
 *  @{
 */

/** @defgroup  OSD_PROBE_Public_Macros
 *  @{
 */

/** @defgroup  OSD_PROBE max supported pointers definitions
 *  @{
 */

#define OSD_PROBE_ADDR_MAX_INDEX (32)

/*@} end of group OSD_PROBE_Public_Macros */

/** @defgroup  OSD_PROBE_Public_Constants
 *  @{
 */

/*@} end of group OSD_PROBE_Public_Constants */

/** @defgroup  OSD_PROBE_Public_Types
 *  @{
 */

/*@} end of group OSD_PROBE_Public_Types */

/** @defgroup  OSD_PROBE_Public_Functions
 *  @{
 */

BL_Err_Type osd_probe_set_addr(uintptr_t index, uintptr_t x, uintptr_t y);
BL_Err_Type osd_probe_get_addr(uintptr_t index, uintptr_t *x, uintptr_t *y);
BL_Err_Type osd_probe_get_count(uintptr_t *cnt);
BL_Err_Type osd_probe_get_result(uintptr_t *res);
BL_Err_Type osd_probe_get_ctrl(uintptr_t *ctrl);
BL_Err_Type osd_probe_set_threshold(uintptr_t luma);
BL_Err_Type osd_probe_get_threshold(uintptr_t *luma);

/*@} end of group OSD_PROBE_Public_Functions */

/*@} end of group OSD_PROBE */

/*@} end of group BL808_Peripheral_Driver */

#endif
