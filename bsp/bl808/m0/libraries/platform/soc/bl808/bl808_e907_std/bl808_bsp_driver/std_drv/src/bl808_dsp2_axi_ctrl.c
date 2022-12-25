/**
  ******************************************************************************
  * @file    bl808_dsp2_axi_ctrl.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl808_dsp2_axi_ctrl.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSP2_AXI_CTRL
 *  @{
 */

/** @defgroup  DSP2_AXI_CTRL_Private_Macros
 *  @{
 */

/*@} end of group DSP2_AXI_CTRL_Private_Macros */

/** @defgroup  DSP2_AXI_CTRL_Private_Types
 *  @{
 */

/*@} end of group DSP2_AXI_CTRL_Private_Types */

/** @defgroup  DSP2_AXI_CTRL_Private_Variables
 *  @{
 */

/*@} end of group DSP2_AXI_CTRL_Private_Variables */

/** @defgroup  DSP2_AXI_CTRL_Global_Variables
 *  @{
 */

/*@} end of group DSP2_AXI_CTRL_Global_Variables */

/** @defgroup  DSP2_AXI_CTRL_Private_Fun_Declaration
 *  @{
 */

/*@} end of group DSP2_AXI_CTRL_Private_Fun_Declaration */

/** @defgroup  DSP2_AXI_CTRL_Private_Functions
 *  @{
 */

/*@} end of group DSP2_AXI_CTRL_Private_Functions */

/** @defgroup  DSP2_AXI_CTRL_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  3DNR init function
 *
 * @param  dsp23DNRCfg: 3DNR configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_3DNR_Init(DSP2_3DNR_Cfg_Type *dsp23DNRCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_3DNR_BURST_TYPE(dsp23DNRCfg->burst));

    tmpVal = BL_RD_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_AXI_CTRL_REG_XLEN, dsp23DNRCfg->burst);
    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, tmpVal);

    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_HADDR_START_ADDRESS, dsp23DNRCfg->memStart);

    /*Set memory brust size */
    switch (dsp23DNRCfg->burst) {
        case DSP2_3DNR_BURST_TYPE_SINGLE:
            tmpVal = dsp23DNRCfg->memSize / 8;
            break;

        case DSP2_3DNR_BURST_TYPE_INCR4:
            tmpVal = dsp23DNRCfg->memSize / 32;
            break;

        case DSP2_3DNR_BURST_TYPE_INCR8:
            tmpVal = dsp23DNRCfg->memSize / 64;
            break;

        case DSP2_3DNR_BURST_TYPE_INCR16:
            tmpVal = dsp23DNRCfg->memSize / 128;
            break;

        case DSP2_3DNR_BURST_TYPE_INCR32:
            tmpVal = dsp23DNRCfg->memSize / 256;
            break;

        case DSP2_3DNR_BURST_TYPE_INCR64:
            tmpVal = dsp23DNRCfg->memSize / 512;
            break;

        default:
            tmpVal = 0;
            break;
    }

    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_MEMORY_BURST_COUNT, tmpVal);

    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_HSYNC_CONTROL, dsp23DNRCfg->hsyncStart << 16 | dsp23DNRCfg->hsyncEnd);
    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_VSYNC_CONTROL, dsp23DNRCfg->vsyncStart << 16 | dsp23DNRCfg->vsyncEnd);
}

/****************************************************************************/ /**
 * @brief  3DNR enable function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_3DNR_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, BL_SET_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_ENABLE));
}

/****************************************************************************/ /**
 * @brief  3DNR disable function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_3DNR_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, BL_CLR_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_ENABLE));
}

/****************************************************************************/ /**
 * @brief  3DNR clear write fifo overflow error function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_3DNR_Clear_Write_Overflow(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, BL_SET_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_OVERFLOW_CLR));
}

/****************************************************************************/ /**
 * @brief  3DNR clear read fifo drain error function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_3DNR_Clear_Read_Drain(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL);
    BL_WR_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_CONTROL, BL_SET_REG_BIT(tmpVal, DSP2_AXI_CTRL_REG_DRAIN_CLR));
}

/****************************************************************************/ /**
 * @brief  3DNR get write and read status function
 *
 * @param  dsp23DNRStatus: 3DNR write and read status type
 *
 * @return Set or reset
 *
*******************************************************************************/
BL_Sts_Type DSP2_3DNR_Get_status(DSP2_3DNR_Status_Type dsp23DNRStatus)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AXI_CTRL_NR3D_BASE, DSP2_AXI_CTRL_NR_STATUS);

    if (tmpVal & 1 << dsp23DNRStatus) {
        return SET;
    } else {
        return RESET;
    }
}

/*@} end of group DSP2_AXI_CTRL_Public_Functions */

/*@} end of group DSP2_AXI_CTRL */

/*@} end of group BL808_Peripheral_Driver */
