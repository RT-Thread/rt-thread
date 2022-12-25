/**
  ******************************************************************************
  * @file    bl808_osd_probe.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl808_osd_probe.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  OSD_PROBE
 *  @{
 */

/** @defgroup  OSD_PROBE_Private_Macros
 *  @{
 */

/*@} end of group OSD_PROBE_Private_Macros */

/** @defgroup  OSD_PROBE_Private_Types
 *  @{
 */

/*@} end of group OSD_PROBE_Private_Types */

/** @defgroup  OSD_PROBE_Private_Variables
 *  @{
 */

/*@} end of group OSD_PROBE_Private_Variables */

/** @defgroup  OSD_PROBE_Global_Variables
 *  @{
 */

/*@} end of group OSD_PROBE_Global_Variables */

/** @defgroup  OSD_PROBE_Private_Fun_Declaration
 *  @{
 */

/*@} end of group OSD_PROBE_Private_Fun_Declaration */

/** @defgroup  OSD_PROBE_Private_Functions
 *  @{
 */

/*@} end of group OSD_PROBE_Private_Functions */

/** @defgroup  OSD_PROBE_Public_Functions
 *  @{
 */

/******************************************************************************
 * @brief  OSD probe setup one detect point
 *
 * @param  index: point index in probe.
 * @param  x: point x-axis.
 * @param  y: point y-axis.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_probe_set_addr(uintptr_t index, uintptr_t x, uintptr_t y)
{
    uint32_t addr = 0;

    addr = ((y << OSD_PB_REG_OSD_PB_Y_00_POS) & OSD_PB_REG_OSD_PB_Y_00_MSK) | (x & OSD_PB_REG_OSD_PB_X_00_MSK);

    if (index < OSD_PROBE_ADDR_MAX_INDEX) {
        BL_WR_WORD(OSD_PROBE_BASE + OSD_PB_ADDR_00_OFFSET + index * sizeof(uint32_t), addr);
        return SUCCESS;
    } else {
        return INVALID;
    }
}

/******************************************************************************
 * @brief  OSD probe get info of one detect point
 *
 * @param  index: point index in probe.
 * @param  x: return the value of point x-axis.
 * @param  y: return the value of point y-axis.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_probe_get_addr(uintptr_t index, uintptr_t *x, uintptr_t *y)
{
    uint32_t addr = 0;
    BL_Err_Type err = INVALID;

    CHECK_PARAM(NULL != x);
    CHECK_PARAM(NULL != y);

    if (index < OSD_PROBE_ADDR_MAX_INDEX) {
        addr = BL_RD_WORD(OSD_PROBE_BASE + OSD_PB_ADDR_00_OFFSET + index * sizeof(uint32_t));
        *x = addr & OSD_PB_REG_OSD_PB_X_00_MSK;
        *y = (addr & OSD_PB_REG_OSD_PB_Y_00_MSK) >> OSD_PB_REG_OSD_PB_Y_00_POS;
        err = SUCCESS;
    }

    return err;
}

/******************************************************************************
 * @brief  OSD probe get result count info
 *
 * @param  cnt: return the count info of the probe result.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_probe_get_count(uintptr_t *cnt)
{
    CHECK_PARAM(NULL != cnt);

    *cnt = BL_GET_REG_BITS_VAL(BL_RD_REG(OSD_PROBE_BASE, OSD_PB_CTRL_REG), OSD_PB_STS_OSD_PB_W_CNT_R);

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD probe get result
 *
 * @param  res: return the probe result.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_probe_get_result(uintptr_t *res)
{
    uint32_t ctrl = 0;

    CHECK_PARAM(NULL != res);

    ctrl = BL_GET_REG_BITS_VAL(BL_RD_REG(OSD_PROBE_BASE, OSD_PB_CTRL_REG), OSD_PB_STS_OSD_PB_IDX_R);

    *res = ctrl ? BL_RD_REG(OSD_PROBE_BASE, OSD_PB_RESULT0) : BL_RD_REG(OSD_PROBE_BASE, OSD_PB_RESULT1);

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD probe get ctrl reg
 *
 * @param  ctrl: return the value of the ctrl reg.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_probe_get_ctrl(uintptr_t *ctrl)
{
    CHECK_PARAM(NULL != ctrl);

    *ctrl = BL_RD_REG(OSD_PROBE_BASE, OSD_PB_CTRL_REG);

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD probe set Y channel threshold.
 *
 * @param  luma: value of the Y threshold.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_probe_set_threshold(uintptr_t luma)
{
    uint32_t ctrl = 0;

    ctrl = BL_RD_REG(OSD_PROBE_BASE, OSD_PB_CTRL_REG);
    ctrl &= ~OSD_PB_REG_OSD_PB_LUMA_TH_MSK;
    ctrl |= (luma & OSD_PB_REG_OSD_PB_LUMA_TH_MSK);
    BL_WR_REG(OSD_PROBE_BASE, OSD_PB_CTRL_REG, ctrl);

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD probe get Y channel threshold.
 *
 * @param  luma: return value of the Y threshold in reg.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_probe_get_threshold(uintptr_t *luma)
{
    uint32_t ctrl = 0;

    CHECK_PARAM(NULL != luma);

    ctrl = BL_RD_REG(OSD_PROBE_BASE, OSD_PB_CTRL_REG);
    *luma = ctrl & OSD_PB_REG_OSD_PB_LUMA_TH_MSK;

    return SUCCESS;
}

/*@} end of group OSD_PROBE_Public_Functions */

/*@} end of group OSD_PROBE */

/*@} end of group BL808_Peripheral_Driver */
