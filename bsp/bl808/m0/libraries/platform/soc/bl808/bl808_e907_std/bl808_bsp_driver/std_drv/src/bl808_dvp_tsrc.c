/**
  ******************************************************************************
  * @file    bl808_dvp_tsrc.c
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

#include "bl808_dvp_tsrc.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DVP_TSRC
 *  @{
 */

/** @defgroup  DVP_TSRC_Private_Macros
 *  @{
 */

/*@} end of group DVP_TSRC_Private_Macros */

/** @defgroup  DVP_TSRC_Private_Types
 *  @{
 */

/*@} end of group DVP_TSRC_Private_Types */

/** @defgroup  DVP_TSRC_Private_Variables
 *  @{
 */
static const uint32_t dvpTsrcAddr[DVP_TSRC_ID_MAX] = { DVP_TSRC0_BASE, DVP_TSRC1_BASE };

/*@} end of group DVP_TSRC_Private_Variables */

/** @defgroup  DVP_TSRC_Global_Variables
 *  @{
 */

/*@} end of group DVP_TSRC_Global_Variables */

/** @defgroup  DVP_TSRC_Private_Fun_Declaration
 *  @{
 */

/*@} end of group DVP_TSRC_Private_Fun_Declaration */

/** @defgroup  DVP_TSRC_Private_Functions
 *  @{
 */

/*@} end of group DVP_TSRC_Private_Functions */

/** @defgroup  DVP_TSRC_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  DVP_TSRC init
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  dvpTsrcCfg: DVP_TSRC configuration
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DVP_TSRC_Init(DVP_TSRC_ID_Type tsrcId, DVP_TSRC_Cfg_Type *dvpTsrcCfg)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));
    CHECK_PARAM(IS_DVP_TSRC_PIXEL_FORMAT_TYPE(dvpTsrcCfg->format));
    CHECK_PARAM(IS_DVP_TSRC_DVP2AXI_TYPE(dvpTsrcCfg->dvp2axi));
    CHECK_PARAM(IS_DVP_TSRC_SWAP_CONTROL_TYPE(dvpTsrcCfg->swapControl));
    CHECK_PARAM(IS_DVP_TSRC_BURST_TYPE(dvpTsrcCfg->burst));
    CHECK_PARAM(IS_DVP_TSRC_YUV420_LINE_TYPE(dvpTsrcCfg->lineType));

    /* Enable using AXI data */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DTSRC_CR_MODE_CEA_861);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_SWAP_MODE, dvpTsrcCfg->swapMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_SWAP_IDX_SWM, dvpTsrcCfg->swapControl);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_SWAP_IDX_SEL, dvpTsrcCfg->dvp2axi);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_DVP_DATA_MODE, dvpTsrcCfg->format);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_SNSR_EN, dvpTsrcCfg->dataFromSensor);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_SNSR_HSYNC_INV, dvpTsrcCfg->sensorHsyncInverse);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_SNSR_VSYNC_INV, dvpTsrcCfg->sensorVsyncInverse);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_B0_SEL, dvpTsrcCfg->byte0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_B1_SEL, dvpTsrcCfg->byte1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_B2_SEL, dvpTsrcCfg->byte2);
    tmpVal = BL_SET_REG_BIT(tmpVal, DTSRC_CR_AXI_EN);
    BL_WR_REG(dvpTsrcX, DTSRC_CONFIG, tmpVal);

    /* Set burst length */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_AXI2DVP_SETTING);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_420_MODE, dvpTsrcCfg->yuv420Enable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_420_UD_SEL, dvpTsrcCfg->lineType);
    BL_WR_REG(dvpTsrcX, DTSRC_AXI2DVP_SETTING, BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_XLEN, dvpTsrcCfg->burst));

    /* Set horizontal pixel count */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_FRAME_SIZE_H);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_TOTAL_H, dvpTsrcCfg->hTotalCnt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_BLANK_H, dvpTsrcCfg->hBlankCnt);
    BL_WR_REG(dvpTsrcX, DTSRC_FRAME_SIZE_H, tmpVal);

    /* Set vertical pixel count */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_FRAME_SIZE_V);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_TOTAL_V, dvpTsrcCfg->vTotalCnt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_BLANK_V, dvpTsrcCfg->vBlankCnt);
    BL_WR_REG(dvpTsrcX, DTSRC_FRAME_SIZE_V, tmpVal);

    /* Set vertical prefetch start position */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_AXI2DVP_PREFETCH);
    BL_WR_REG(dvpTsrcX, DTSRC_AXI2DVP_PREFETCH, BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_PREFETCH_V, dvpTsrcCfg->prefetch));

    /* Set fifo threshold for each DVP line to start to output */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_SNSR2DVP_WAIT_POS);
    BL_WR_REG(dvpTsrcX, DTSRC_SNSR2DVP_WAIT_POS, BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_SNSR_FIFO_TH, dvpTsrcCfg->fifoThreshold));

    /* Set axi2dvp start address, Y planar in YUV420 mode, frame 0 in swap mode */
    BL_WR_REG(dvpTsrcX, DTSRC_AXI2DVP_START_ADDR_BY, dvpTsrcCfg->memStartY0);

    /* Set axi2dvp memory size in burst */
    switch (dvpTsrcCfg->burst) {
        case DVP_TSRC_BURST_TYPE_SINGLE:
            tmpVal = dvpTsrcCfg->memSizeY0 / 8;
            break;

        case DVP_TSRC_BURST_TYPE_INCR4:
            tmpVal = dvpTsrcCfg->memSizeY0 / 32;
            break;

        case DVP_TSRC_BURST_TYPE_INCR8:
            tmpVal = dvpTsrcCfg->memSizeY0 / 64;
            break;

        case DVP_TSRC_BURST_TYPE_INCR16:
            tmpVal = dvpTsrcCfg->memSizeY0 / 128;
            break;

        case DVP_TSRC_BURST_TYPE_INCR32:
            tmpVal = dvpTsrcCfg->memSizeY0 / 256;
            break;

        case DVP_TSRC_BURST_TYPE_INCR64:
            tmpVal = dvpTsrcCfg->memSizeY0 / 512;
            break;

        default:
            tmpVal = 0;
            break;
    }

    BL_WR_REG(dvpTsrcX, DTSRC_AXI2DVP_BURST_CNT, tmpVal);

    /* Set axi2dvp start address, Y planar in YUV420 mode, frame 1 in swap mode */
    BL_WR_REG(dvpTsrcX, DTSRC_AXI2DVP_SWAP_ADDR_BY, dvpTsrcCfg->memStartY1);

    /* Set axi2dvp start address, UV planar in YUV420 mode, frame 0 in swap mode */
    BL_WR_REG(dvpTsrcX, DTSRC_AXI2DVP_START_ADDR_UV, dvpTsrcCfg->memStartUV0);

    /* Set axi2dvp start address, UV planar in YUV420 mode, frame 1 in swap mode */
    BL_WR_REG(dvpTsrcX, DTSRC_AXI2DVP_SWAP_ADDR_UV, dvpTsrcCfg->memStartUV1);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Use fake gradient data function init
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  dataCfg: Fake gradient data configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Fake_Data_Init(DVP_TSRC_ID_Type tsrcId, DVP_TSRC_Fake_Data_Cfg_Type *dataCfg)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    /* Enable using fake gradient data */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX, DTSRC_CONFIG, BL_CLR_REG_BIT(tmpVal, DTSRC_CR_AXI_EN));

    /* Set min and max value of fake gradient data */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_PIX_DATA_RANGE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_DATA_MIN, dataCfg->minData);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_DATA_MAX, dataCfg->maxData);
    BL_WR_REG(dvpTsrcX, DTSRC_PIX_DATA_RANGE, tmpVal);

    /* Set step value for eack line of fake gradient data */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_PIX_DATA_STEP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_DATA_STEP, dataCfg->step);
    BL_WR_REG(dvpTsrcX, DTSRC_PIX_DATA_STEP, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CEA-861 mode init
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  ceaCfg: CEA-861 configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_CEA861_Init(DVP_TSRC_ID_Type tsrcId, DVP_TSRC_CEA861_Cfg_Type *ceaCfg)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX, DTSRC_CONFIG, BL_SET_REG_BIT(tmpVal, DTSRC_CR_MODE_CEA_861));

    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_FRAME_SIZE_CEA_861);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_H_PLACEMENT, ceaCfg->hsyncStart);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_H_DURATION, ceaCfg->hsyncEnd);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_V_PLACEMENT, ceaCfg->vsyncStart);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_V_DURATION, ceaCfg->vsyncEnd);
    BL_WR_REG(dvpTsrcX, DTSRC_FRAME_SIZE_CEA_861, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Sensor input configuration
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  threshold: FIFO threshold for each DVP line to start to output
 * @param  hsyncInv:Enable or disable inverse signal of sensor hsync
 * @param  vsyncInv:Enable or disable inverse signal of sensor vsync
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Sensor_Input_Set(DVP_TSRC_ID_Type tsrcId, uint16_t threshold, BL_Fun_Type hsyncInv, BL_Fun_Type vsyncInv)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, DTSRC_CR_SNSR_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_SNSR_HSYNC_INV, hsyncInv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_SNSR_VSYNC_INV, vsyncInv);
    BL_WR_REG(dvpTsrcX, DTSRC_CONFIG, tmpVal);

    /* Set fifo threshold for each DVP line to start to output */
    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_SNSR2DVP_WAIT_POS);
    BL_WR_REG(dvpTsrcX, DTSRC_SNSR2DVP_WAIT_POS, BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_SNSR_FIFO_TH, threshold));
}

/****************************************************************************/ /**
 * @brief  DVP_TSRC enable
 *
 * @param  tsrcId: DVP_TSRC ID type
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Enable(DVP_TSRC_ID_Type tsrcId)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX, DTSRC_CONFIG, BL_SET_REG_BIT(tmpVal, DTSRC_CR_ENABLE));
}

/****************************************************************************/ /**
 * @brief  DVP_TSRC disable
 *
 * @param  tsrcId: DVP_TSRC ID type
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Disable(DVP_TSRC_ID_Type tsrcId)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX, DTSRC_CONFIG, BL_CLR_REG_BIT(tmpVal, DTSRC_CR_ENABLE));
}

/****************************************************************************/ /**
 * @brief  DVP_TSRC set swap index in software mode
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  index: Swap index used
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Set_Swap_Index(DVP_TSRC_ID_Type tsrcId, uint8_t index)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX, DTSRC_CONFIG, BL_SET_REG_BITS_VAL(tmpVal, DTSRC_CR_AXI_SWAP_IDX_SWV, index));
}

/****************************************************************************/ /**
 * @brief  AXI2DVP clear drain error function
 *
 * @param  tsrcId: DVP_TSRC ID type
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Clear_Drain_Error(DVP_TSRC_ID_Type tsrcId)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX, DTSRC_AXI2DVP_SETTING);
    BL_WR_REG(dvpTsrcX, DTSRC_AXI2DVP_SETTING, BL_SET_REG_BIT(tmpVal, DTSRC_CR_AXI_DRAIN_ERR_CLR));
}

/****************************************************************************/ /**
 * @brief  Get AXI2DVP status function
 *
 * @param  tsrcId: DVP_TSRC ID type
 *
 * @return Status
 *
*******************************************************************************/
uint32_t DVP_TSRC_Get_Status(DVP_TSRC_ID_Type tsrcId)
{
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    return (BL_RD_REG(dvpTsrcX, DTSRC_AXI2DVP_STATUS));
}

/*@} end of group DVP_TSRC_Public_Functions */

/*@} end of group DVP_TSRC */

/*@} end of group BL808_Peripheral_Driver */
