/**
  ******************************************************************************
  * @file    bl808_dsp2_misc.c
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

#include "bl808_dsp2_misc.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSP2_MISC
 *  @{
 */

/** @defgroup  DSP2_MISC_Private_Macros
 *  @{
 */

/*@} end of group DSP2_MISC_Private_Macros */

/** @defgroup  DSP2_MISC_Private_Types
 *  @{
 */

/*@} end of group DSP2_MISC_Private_Types */

/** @defgroup  DSP2_MISC_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *dsp2MiscIntCbfArra[DSP2_MISC_INT_ALL] = {
    NULL
};
#endif

/*@} end of group DSP2_MISC_Private_Variables */

/** @defgroup  DSP2_MISC_Global_Variables
 *  @{
 */

/*@} end of group DSP2_MISC_Global_Variables */

/** @defgroup  DSP2_MISC_Private_Fun_Declaration
 *  @{
 */

/*@} end of group DSP2_MISC_Private_Fun_Declaration */

/** @defgroup  DSP2_MISC_Private_Functions
 *  @{
 */

/*@} end of group DSP2_MISC_Private_Functions */

/** @defgroup  DSP2_MISC_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  DVP AS 2X function init
 *
 * @param  dvp2xCfg: DVP AS 2X configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_2X_Init(DSP2_MISC_2X_Cfg_Type *dvp2xCfg)
{
    uint32_t tmpVal;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_ACTIVE_LEVEL_TYPE(dvp2xCfg->hSyncLevel));
    CHECK_PARAM(IS_DSP2_MISC_ACTIVE_LEVEL_TYPE(dvp2xCfg->vSyncLevel));
    CHECK_PARAM(IS_DSP2_MISC_2X_DATA_ORDER_TYPE(dvp2xCfg->dataOrder));
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DVPAS_HS_INV, dvp2xCfg->hSyncLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DVPAS_VS_INV, dvp2xCfg->vSyncLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DVPAS_DA_ORDER, dvp2xCfg->dataOrder);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DVPAS_FIFO_TH, dvp2xCfg->fifoThreshold & 0x7ff);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, tmpVal);
}

/****************************************************************************//**
 * @brief  DVP AS 2X function enable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_2X_Enable(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_DVPAS_ENABLE));
}

/****************************************************************************//**
 * @brief  DVP AS 2X function disable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_2X_Disable(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_DVPAS_ENABLE));
}

/****************************************************************************/ /**
 * @brief  CAM input selection
 *
 * @param  camId: CAM id
 * @param  inputType: CAM input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_CAM_Input_Select(DSP2_MISC_CAM_ID_Type camId, DSP2_MISC_CAM_Input_Type inputType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CAM_ID_TYPE(camId));
    CHECK_PARAM(IS_DSP2_MISC_CAM_INPUT_TYPE(inputType));

    if (camId < DSP2_MISC_CAM_4_ID) {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1);
        tmpVal = (tmpVal & ~(0x3f << (camId * 8))) | (inputType & 0x3f) << (camId * 8);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1, tmpVal);
    } else {
        camId -= 4;
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2);
        tmpVal = (tmpVal & ~(0x3f << (camId * 8))) | (inputType & 0x3f) << (camId * 8);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  CAM frame id type selection
 *
 * @param  camId: CAM id
 * @param  idType: Frame id type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_CAM_Frame_ID_Select(DSP2_MISC_CAM_ID_Type camId, DSP2_MISC_Frame_ID_Type idType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CAM_ID_TYPE(camId));
    CHECK_PARAM(IS_DSP2_MISC_FRAME_ID_TYPE(idType));

    if (camId < DSP2_MISC_CAM_4_ID) {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1);
        tmpVal = (tmpVal & ~(0x1 << (camId * 8 + DSP2_MISC_RG_D2X_ID_SEL_A_POS))) | idType << (camId * 8 + DSP2_MISC_RG_D2X_ID_SEL_A_POS);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_1, tmpVal);
    } else {
        camId -= 4;
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2);
        tmpVal = (tmpVal & ~(0x1 << (camId * 8 + DSP2_MISC_RG_D2X_ID_SEL_E_POS))) | idType << (camId * 8 + DSP2_MISC_RG_D2X_ID_SEL_E_POS);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP2BUS_SRC_SEL_2, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  Frame id init
 *
 * @param  idType: Frame id type
 * @param  edgeType: Frame id edge type
 * @param  vsyncCnt: Vsync count to trigger id increment
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Frame_ID_Init(DSP2_MISC_Frame_ID_Type idType, DSP2_MISC_Frame_ID_Edge_Type edgeType, uint16_t vsyncCnt)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_FRAME_ID_TYPE(idType));
    CHECK_PARAM(IS_DSP2_MISC_FRAME_ID_EDGE_TYPE(edgeType));

    if (idType == DSP2_MISC_FRAME_BAYER_ID) {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DSP2_ID_BAYER);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_BAYER_IDGEN_EDGE, edgeType);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_BAYER_IDGEN_CNT_INCR, vsyncCnt);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DSP2_ID_BAYER, tmpVal);
    } else {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DSP2_ID_YUV);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_YUV_IDGEN_EDGE, edgeType);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_YUV_IDGEN_CNT_INCR, vsyncCnt);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DSP2_ID_YUV, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  Reset frame id
 *
 * @param  idType: Frame id type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Frame_ID_Reset(DSP2_MISC_Frame_ID_Type idType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_FRAME_ID_TYPE(idType));

    if (idType == DSP2_MISC_FRAME_BAYER_ID) {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DSP2_ID_BAYER);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DSP2_ID_BAYER, BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_BAYER_IDGEN_RST));
    } else {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DSP2_ID_YUV);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DSP2_ID_YUV, BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_YUV_IDGEN_RST));
    }
}

/****************************************************************************/ /**
 * @brief  OSD input selection
 *
 * @param  osdId: OSD id
 * @param  inputType: OSD input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_OSD_Input_Select(DSP2_MISC_OSD_ID_Type osdId, DSP2_MISC_OSD_Input_Type inputType)
{
    uint32_t tmpVal;
    uint32_t osdAddr = DSP2_MISC_BASE + DSP2_MISC_OSDA_I_CTRL_OFFSET + 4 * osdId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_OSD_ID_TYPE(osdId));
    CHECK_PARAM(IS_DSP2_MISC_OSD_INPUT_TYPE(inputType));

    tmpVal = BL_RD_WORD(osdAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_OSDA_SEL, inputType);
    BL_WR_WORD(osdAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  OSD probe input selection
 *
 * @param  inputType: OSD input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_OSD_Probe_Input_Select(DSP2_MISC_OSD_Input_Type inputType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_OSD_INPUT_TYPE(inputType));

    if (inputType > DSP2_MISC_OSD_DSP2_INPUT) {
        return;
    }

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_OSDA_I_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_OSD_PB_SEL, inputType);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_OSDA_I_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Crop init
 *
 * @param  cropId: Crop id
 * @param  cropCfg: Crop configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Crop_Init(DSP2_MISC_Crop_ID_Type cropId, DSP2_MISC_Crop_Cfg_Type *cropCfg)
{
    uint32_t cropAddr = DSP2_MISC_BASE + DSP2_MISC_CROPA_HSYNC_OFFSET + 8 * cropId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CROP_ID_TYPE(cropId));

    BL_WR_WORD(cropAddr, cropCfg->hsyncEnd << 16 | cropCfg->hsyncStart);
    cropAddr += 4;
    BL_WR_WORD(cropAddr, cropCfg->vsyncEnd << 16 | cropCfg->vsyncStart);
}

/****************************************************************************/ /**
 * @brief  Crop enable
 *
 * @param  cropId: Crop id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Crop_Enable(DSP2_MISC_Crop_ID_Type cropId)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CROP_ID_TYPE(cropId));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CROP_ENABLE);

    switch (cropId) {
        case DSP2_MISC_CROP_0_ID:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_CROPA_ENABLE);
            break;

        case DSP2_MISC_CROP_1_ID:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_CROPB_ENABLE);
            break;

        case DSP2_MISC_CROP_2_ID:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_CROPC_ENABLE);
            break;

        case DSP2_MISC_CROP_3_ID:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_CROPD_ENABLE);
            break;

        default:
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CROP_ENABLE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Crop disable
 *
 * @param  cropId: Crop id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Crop_Disable(DSP2_MISC_Crop_ID_Type cropId)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_CROP_ID_TYPE(cropId));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CROP_ENABLE);

    switch (cropId) {
        case DSP2_MISC_CROP_0_ID:
            tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_CROPA_ENABLE);
            break;

        case DSP2_MISC_CROP_1_ID:
            tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_CROPB_ENABLE);
            break;

        case DSP2_MISC_CROP_2_ID:
            tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_CROPC_ENABLE);
            break;

        case DSP2_MISC_CROP_3_ID:
            tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_CROPD_ENABLE);
            break;

        default:
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CROP_ENABLE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Scaler input selection
 *
 * @param  scalerId: Scaler id
 * @param  inputType: Scaler input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Input_Select(DSP2_MISC_Scaler_ID_Type scalerId, DSP2_MISC_Scaler_Input_Type inputType)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE + DSP2_MISC_SCALERA_I_SIZE_OFFSET + 8 * scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));
    CHECK_PARAM(IS_DSP2_MISC_SCALER_INPUT_TYPE(inputType));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALERA_SEL, inputType);
    BL_WR_WORD(scalerAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Scaler init
 *
 * @param  scalerId: Scaler id
 * @param  scalerCfg: Scaler configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Init(DSP2_MISC_Scaler_ID_Type scalerId, DSP2_MISC_Scaler_Cfg_Type *scalerCfg)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE + DSP2_MISC_SCALERA_I_SIZE_OFFSET + 8 * scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALERA_I_W, scalerCfg->inputWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALERA_I_H, scalerCfg->inputHeight & 0x7ff);
    BL_WR_WORD(scalerAddr, tmpVal);

    scalerAddr += 4;
    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALERA_O_W, scalerCfg->outputWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SCALERA_O_H, scalerCfg->outputHeight);
    BL_WR_WORD(scalerAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Scaler enable
 *
 * @param  scalerId: Scaler id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Enable(DSP2_MISC_Scaler_ID_Type scalerId)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE + DSP2_MISC_SCALERA_I_SIZE_OFFSET + 8 * scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_SCALERA_BYPASS);
    BL_WR_WORD(scalerAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Scaler disable
 *
 * @param  scalerId: Scaler id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Disable(DSP2_MISC_Scaler_ID_Type scalerId)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE + DSP2_MISC_SCALERA_I_SIZE_OFFSET + 8 * scalerId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));

    tmpVal = BL_RD_WORD(scalerAddr);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SCALERA_BYPASS);
    BL_WR_WORD(scalerAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Adjust input selection
 *
 * @param  adjustId: Adjust id
 * @param  inputType: Adjust input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Scaler_Shadow(DSP2_MISC_Scaler_ID_Type scalerId)
{
    uint32_t tmpVal;
    uint32_t scalerAddr = DSP2_MISC_BASE + DSP2_MISC_SCALERA_I_SIZE_OFFSET + 8 * scalerId;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_SCALER_ID_TYPE(scalerId));
    
    tmpVal = BL_RD_WORD(scalerAddr);
    BL_WR_WORD(scalerAddr, BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SCLRA_SW_SH));
}

/****************************************************************************/ /**
 * @brief  Adjust input selection
 *
 * @param  adjustId: Adjust id
 * @param  inputType: Adjust input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Adjust_Input_Select(DSP2_MISC_Adjust_ID_Type adjustId, DSP2_MISC_Adjust_Input_Type inputType)
{
    uint32_t tmpVal;
    uint32_t adjustAddr = DSP2_MISC_BASE + DSP2_MISC_ADJA_CTRL_2_OFFSET + 16 * adjustId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_ADJUST_ID_TYPE(adjustId));
    CHECK_PARAM(IS_DSP2_MISC_ADJUST_INPUT_TYPE(inputType));

    tmpVal = BL_RD_WORD(adjustAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_ADJA_SEL, inputType);
    BL_WR_WORD(adjustAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Adjust init
 *
 * @param  adjustId: Adjust id
 * @param  adjustCfg: Adjust configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Adjust_Init(DSP2_MISC_Adjust_ID_Type adjustId, DSP2_MISC_Adjust_Cfg_Type *adjustCfg)
{
    uint32_t tmpVal;
    uint32_t adjustAddr = DSP2_MISC_BASE + DSP2_MISC_ADJA_CTRL_0_OFFSET + 16 * adjustId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_ADJUST_ID_TYPE(adjustId));

    tmpVal = BL_RD_WORD(adjustAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_Y_LUMA, adjustCfg->yLuma);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_Y_MUL0, adjustCfg->yMul0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_Y_MUL1, adjustCfg->yMul1);
    BL_WR_WORD(adjustAddr, tmpVal);

    adjustAddr += 4;
    tmpVal = BL_RD_WORD(adjustAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_Y_MIN, adjustCfg->yMin);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_Y_MAX, adjustCfg->yMax);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_UV_MIN, adjustCfg->uvMin);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_UV_MAX, adjustCfg->uvMax);
    BL_WR_WORD(adjustAddr, tmpVal);

    adjustAddr += 4;
    tmpVal = BL_RD_WORD(adjustAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_UV_MUL0, adjustCfg->uvMul0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_ADJA_UV_MUL1, adjustCfg->uvMul1);
    BL_WR_WORD(adjustAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Adjust enable
 *
 * @param  adjustId: Adjust id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Adjust_Enable(DSP2_MISC_Adjust_ID_Type adjustId)
{
    uint32_t tmpVal;
    uint32_t adjustAddr = DSP2_MISC_BASE + DSP2_MISC_ADJA_CTRL_0_OFFSET + 16 * adjustId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_ADJUST_ID_TYPE(adjustId));

    tmpVal = BL_RD_WORD(adjustAddr);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_ADJA_ADJ_EB);
    BL_WR_WORD(adjustAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Adjust disable
 *
 * @param  adjustId: Adjust id
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Adjust_Disable(DSP2_MISC_Adjust_ID_Type adjustId)
{
    uint32_t tmpVal;
    uint32_t adjustAddr = DSP2_MISC_BASE + DSP2_MISC_ADJA_CTRL_0_OFFSET + 16 * adjustId;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_ADJUST_ID_TYPE(adjustId));

    tmpVal = BL_RD_WORD(adjustAddr);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_REG_ADJA_ADJ_EB);
    BL_WR_WORD(adjustAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Display init
 *
 * @param  displayCfg: Display configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Display_Init(DSP2_MISC_Display_Cfg_Type *displayCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_ADJUST_ID_TYPE(adjustId));
    CHECK_PARAM(IS_DSP2_MISC_DISPLAY_OSD_INPUT_TYPE(displayCfg->osdType));
    CHECK_PARAM(IS_DSP2_MISC_DISPLAY_INPUT_TYPE(displayCfg->inputType));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_DISP_HDMI_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_DISP_BT1120_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MISC_RG_DISP_DPI_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_MUX_SEL, displayCfg->inputType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_OSDDP_SEL, displayCfg->osdType);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_CONFIG, tmpVal);

    if (displayCfg->dpiEnable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_DISP_DPI_EN);
    } else if (displayCfg->hdmiEnable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_DISP_HDMI_EN);
    } else if (displayCfg->bt1120Enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_DISP_BT1120_EN);
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_CONFIG, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_DPI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_DPI_HS_W, displayCfg->hsyncWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_DPI_HFP_W, displayCfg->hfpWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_DPI_VS_W, displayCfg->vsyncWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_DPI_VFP_W, displayCfg->vfpWidth);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_DPI_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Display gamma init
 *
 * @param  gammaCfg: Display gamma configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Display_Gamma_Init(DSP2_MISC_Display_Gamma_Cfg_Type *gammaCfg)
{
    uint32_t tmpVal, i, j;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_GMA_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_DP_GMA_CH0_EN, gammaCfg->ch0Enable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_DP_GMA_CH1_EN, gammaCfg->ch1Enable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_DP_GMA_CH2_EN, gammaCfg->ch2Enable);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_GMA_CFG, tmpVal);

    if (gammaCfg->gammaCurve == NULL) {
        return;
    }

    for (i = 0; i < 64; i++) {
        tmpVal = 0;

        for (j = 0; j < 4; j++) {
            tmpVal |= gammaCfg->gammaCurve[j + 4 * i] << (8 * j);
        }

        BL_WR_WORD(DSP2_MISC_BASE + DSP2_MISC_DISP_GMA_CURVE_00_OFFSET + 4 * i, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  YUV2RGB input selection
 *
 * @param  inputType: YUV2RGB input type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_YUV2RGB_Input_Select(DSP2_MISC_YUV2RGB_Input_Type inputType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_YUV2RGB_INPUT_TYPE(inputType));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_SEL, inputType);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  YUV2RGB init
 *
 * @param  yuv2rgbId: YUV2RGB ID type
 * @param  yuv2rgbCfg: YUV2RGB configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_YUV2RGB_Init(DSP2_MISC_YUV2RGB_ID_Type yuv2rgbId, DSP2_MISC_YUV2RGB_Cfg_Type *yuv2rgbCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_YUV2RGB_ID_TYPE(yuv2rgbId));

    if (yuv2rgbId == DSP2_MISC_YUV2RGB_DISPLAY_ID) {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_PRE_0, yuv2rgbCfg->preOffset0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_PRE_1, yuv2rgbCfg->preOffset1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_PRE_2, yuv2rgbCfg->preOffset2);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_0, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_POS_0, yuv2rgbCfg->postOffset0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_POS_1, yuv2rgbCfg->postOffset1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_POS_2, yuv2rgbCfg->postOffset2);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_1, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_00, yuv2rgbCfg->matrix00);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_01, yuv2rgbCfg->matrix01);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_02_L, yuv2rgbCfg->matrix02);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_2, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_3);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_02_U, yuv2rgbCfg->matrix02 >> 8);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_10, yuv2rgbCfg->matrix10);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_11, yuv2rgbCfg->matrix11);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_12_L, yuv2rgbCfg->matrix12);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_3, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_4);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_12_U, yuv2rgbCfg->matrix12 >> 4);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_20, yuv2rgbCfg->matrix20);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_21, yuv2rgbCfg->matrix21);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_4, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_5);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_MTX_22, yuv2rgbCfg->matrix22);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_5, tmpVal);

        /* Enable or disable function */
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_0);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_YUV_RGB_CONFIG_0, BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_Y2R_EN, yuv2rgbCfg->enable));

    } else if (yuv2rgbId == DSP2_MISC_YUV2RGB_NORMAL_ID) {
        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_PRE_0, yuv2rgbCfg->preOffset0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_POS_0, yuv2rgbCfg->postOffset0);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_0, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_PRE_1, yuv2rgbCfg->preOffset1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_POS_1, yuv2rgbCfg->postOffset1);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_1, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_PRE_2, yuv2rgbCfg->preOffset2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_POS_2, yuv2rgbCfg->postOffset2);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_2, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_3);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_00, yuv2rgbCfg->matrix00);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_01, yuv2rgbCfg->matrix01);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_3, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_4);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_02, yuv2rgbCfg->matrix02);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_10, yuv2rgbCfg->matrix10);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_4, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_5);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_11, yuv2rgbCfg->matrix11);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_12, yuv2rgbCfg->matrix12);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_5, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_6);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_20, yuv2rgbCfg->matrix20);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_21, yuv2rgbCfg->matrix21);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_6, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_7);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_MTX_22, yuv2rgbCfg->matrix22);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_7, tmpVal);

        tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_0);
        BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_Y2RA_CONFIG_0, BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_Y2RA_EN, yuv2rgbCfg->enable));
    }
}

/****************************************************************************/ /**
 * @brief  RGB2YUV init
 *
 * @param  rgb2yuvCfg: YUV2RGB configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_RGB2YUV_Init(DSP2_MISC_YUV2RGB_Cfg_Type *rgb2yuvCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_PRE_0, rgb2yuvCfg->preOffset0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_PRE_1, rgb2yuvCfg->preOffset1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_PRE_2, rgb2yuvCfg->preOffset2);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_POS_0, rgb2yuvCfg->postOffset0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_POS_1, rgb2yuvCfg->postOffset1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_POS_2, rgb2yuvCfg->postOffset2);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_00, rgb2yuvCfg->matrix00);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_01, rgb2yuvCfg->matrix01);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_02_L, rgb2yuvCfg->matrix02);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_2, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_02_U, rgb2yuvCfg->matrix02 >> 8);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_10, rgb2yuvCfg->matrix10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_11, rgb2yuvCfg->matrix11);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_12_L, rgb2yuvCfg->matrix12);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_3, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_12_U, rgb2yuvCfg->matrix12 >> 4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_20, rgb2yuvCfg->matrix20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_21, rgb2yuvCfg->matrix21);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_4, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_MTX_22, rgb2yuvCfg->matrix22);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_5, tmpVal);

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_0);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DISP_RGB2YUV_CONFIG_0, BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DISP_R2Y_EN, rgb2yuvCfg->enable));
}

/****************************************************************************/ /**
 * @brief  Clear certain or all of the interrupt
 *
 * @param  intType: Interrupt type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Int_Clear(DSP2_MISC_INT_Type intType)
{
    uint32_t tmpVal = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));

    switch (intType) {
        case DSP2_MISC_INT_AWB0:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB_INT_CLR);
            break;

        case DSP2_MISC_INT_AE:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AE_INT_CLR);
            break;

        case DSP2_MISC_INT_WDR:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_WDR_INT_CLR);
            break;

        case DSP2_MISC_INT_AWB1:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB2_INT_CLR);
            break;

        case DSP2_MISC_INT_OSD_PB:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_OSD_PB_INT_CLR);
            break;

        case DSP2_MISC_INT_SEOF0:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF1_INT_CLR);
            break;

        case DSP2_MISC_INT_SEOF1:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF2_INT_CLR);
            break;

        case DSP2_MISC_INT_SEOF2:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF3_INT_CLR);
            break;

        case DSP2_MISC_INT_AE_HIST:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AE_HIST_INT_CLR);
            break;

        case DSP2_MISC_INT_AWB2:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_AWB3_INT_CLR);
            break;

        case DSP2_MISC_INT_DISPLAY:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_CLR);
            break;

        case DSP2_MISC_INT_SEOF3:
            tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_RG_SEOF4_INT_CLR);
            break;

        case DSP2_MISC_INT_ALL:
            tmpVal = 0x7f1f;
            break;

        default:
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CLR, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Mask/Unmask certain or all of the interrupt
 *
 * @param  intType: Interrupt type
 * @param  intMask: Mask or unmask
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Int_Mask(DSP2_MISC_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);

    switch (intType) {
        case DSP2_MISC_INT_AWB0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AWB_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_AE:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AE_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_WDR:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_WDR_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_AWB1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AWB2_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_OSD_PB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_OSD_PB_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_SEOF0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_SEOF1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_SEOF2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_AE_HIST:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AE_HIST_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_AWB2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_AWB3_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_DISPLAY:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_SEOF3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_MASK, intMask);
            break;

        case DSP2_MISC_INT_ALL:
            if (intMask == MASK) {
                tmpVal |= 0x1131111f;
            } else {
                tmpVal &= ~0x1131111f;
            }

            break;

        default:
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Install dsp2 misc interrupt callback function
 *
 * @param  intType: DSP2 misc interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DSP2_MISC_Int_Callback_Install(DSP2_MISC_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));

    switch (intType) {
#if defined(CPU_D0)

        case DSP2_MISC_INT_AWB0:
            Interrupt_Handler_Register(DSP2_AWB0_IRQn, AWB0_IRQHandler);
            break;
#endif

        case DSP2_MISC_INT_AE:
            Interrupt_Handler_Register(DSP2_AE_IRQn, AE_IRQHandler);
            break;

        case DSP2_MISC_INT_WDR:
            Interrupt_Handler_Register(DSP2_WDR_IRQn, WDR_IRQHandler);
            break;

        case DSP2_MISC_INT_AWB1:
            Interrupt_Handler_Register(DSP2_AWB1_IRQn, AWB1_IRQHandler);
            break;

        case DSP2_MISC_INT_OSD_PB:
            Interrupt_Handler_Register(OSD_PB_IRQn, OSD_PB_IRQHandler);
            break;

        case DSP2_MISC_INT_SEOF0:
            Interrupt_Handler_Register(SEOF_INT0_IRQn, SEOF0_IRQHandler);
            break;

        case DSP2_MISC_INT_SEOF1:
            Interrupt_Handler_Register(SEOF_INT1_IRQn, SEOF1_IRQHandler);
            break;

        case DSP2_MISC_INT_SEOF2:
            Interrupt_Handler_Register(SEOF_INT2_IRQn, SEOF2_IRQHandler);
            break;

        case DSP2_MISC_INT_AE_HIST:
            Interrupt_Handler_Register(DSP2_AE_HIST_IRQn, AE_HIST_IRQHandler);
            break;

        case DSP2_MISC_INT_AWB2:
            Interrupt_Handler_Register(DSP2_AWB2_IRQn, AWB2_IRQHandler);
            break;

        case DSP2_MISC_INT_DISPLAY:
            Interrupt_Handler_Register(DISPLAY_IRQn, Display_IRQHandler);
            break;

        case DSP2_MISC_INT_SEOF3:
            Interrupt_Handler_Register(SEOF_INT3_IRQn, SEOF3_IRQHandler);
            break;

        default:
            break;
    }

    dsp2MiscIntCbfArra[intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  Select SEOF interrupt vsync source
 *
 * @param  intType: SEOF interrupt type
 * @param  source: SEOF interrupt vsync source type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_SEOF_Set_Source(DSP2_MISC_INT_Type intType, DSP2_MISC_SEOF_Source_Type source)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));
    CHECK_PARAM(IS_DSP2_MISC_SEOF_SOURCE_TYPE(source));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);

    switch (intType) {
        case DSP2_MISC_INT_SEOF0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_SRC, source);
            break;

        case DSP2_MISC_INT_SEOF1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_SRC, source);
            break;

        case DSP2_MISC_INT_SEOF2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_SRC, source);
            break;

        case DSP2_MISC_INT_DISPLAY:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_SRC, source & 0x1);
            break;

        case DSP2_MISC_INT_SEOF3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_SRC, source);
            break;

        default:
            return;
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Select SEOF interrupt vsync source
 *
 * @param  intType: SEOF interrupt type
 * @param  edge: SEOF interrupt edge type
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_SEOF_Set_Edge(DSP2_MISC_INT_Type intType, DSP2_MISC_SEOF_Edge_Type edge)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_INT_TYPE(intType));
    CHECK_PARAM(IS_DSP2_MISC_SEOF_SOURCE_TYPE(edge));

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL);

    switch (intType) {
        case DSP2_MISC_INT_SEOF0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF1_INT_EDGE, edge);
            break;

        case DSP2_MISC_INT_SEOF1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF2_INT_EDGE, edge);
            break;

        case DSP2_MISC_INT_SEOF2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF3_INT_EDGE, edge);
            break;

        case DSP2_MISC_INT_DISPLAY:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_DP_SEOF0_INT_EDGE, edge);
            break;

        case DSP2_MISC_INT_SEOF3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_RG_SEOF4_INT_EDGE, edge);
            break;

        default:
            return;
            break;
    }

    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_INT_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Reshape init
 *
 * @param  reshapeCfg: Reshape configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Reshape_Init(DSP2_MISC_Reshape_Cfg_Type *reshapeCfg)
{
    uint32_t tmpVal;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_ACTIVE_LEVEL_TYPE(reshapeCfg->hSyncLevel));
    CHECK_PARAM(IS_DSP2_MISC_ACTIVE_LEVEL_TYPE(reshapeCfg->vSyncLevel));
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_RSHP_TGL_COUNT, reshapeCfg->vsyncNumber & 0x1f);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_RSHP_HSYNC_INV, reshapeCfg->hSyncLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_RSHP_VSYNC_INV, reshapeCfg->vSyncLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_RSHP_EN, reshapeCfg->enable);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Clear vsync toggle counter
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Reshape_Counter_Clear(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_RESHAPE, BL_SET_REG_BIT(tmpVal, DSP2_MISC_REG_RSHP_CLR));
}

/****************************************************************************/ /**
 * @brief  Enable or disable use DE as hsync for DSP2
 *
 * @param  enable: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_DE_As_Hsync(BL_Fun_Type enable)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_CR_DSP2_DE_AS_HSYNC, enable);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Select DVP TSRC data source
 *
 * @param  sourceType: DVP or CSI
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_TSRC_Source_Select(DSP2_MISC_TSRC_Source_Type sourceType)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_DSP2_DTSRC_SRC, sourceType);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Configure bayer data shift function
 *
 * @param  bitEnable: Enable bits used
 * @param  shiftType: Set shift direction
 * @param  bitShift: Set Shift bits
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_Bayer_Shift(uint16_t bitEnable, DSP2_MISC_Bayer_Shift_Type shiftType, uint8_t bitShift)
{
    uint32_t tmpVal = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_MISC_BAYER_SHIFT_TYPE(shiftType));

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_CTRL, bitEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_SHT_BIT, bitShift);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_REG_PIX_DATA_SHT_DIR, shiftType);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_PIX_DATA_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Reduce m frames to n frames function enable
 *
 * @param  m: Total frame count
 * @param  n: Enabled frame count
 * @param  step: Step between enabled frames
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_M2N_Enable(uint8_t m, uint8_t n, uint8_t step)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_FRAME_M_TO_N);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MISC_CR_FRAME_M_TO_N_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_CR_FRAME_INTERVAL, step);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_CR_FRAME_CNT_N, n);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MISC_CR_FRAME_CNT_M, m);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_FRAME_M_TO_N, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Reduce m frames to n frames function disable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DSP2_MISC_M2N_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_FRAME_M_TO_N);
    BL_WR_REG(DSP2_MISC_BASE, DSP2_MISC_DVP_FRAME_M_TO_N, BL_CLR_REG_BIT(tmpVal, DSP2_MISC_CR_FRAME_M_TO_N_EN));
}

/****************************************************************************/ /**
 * @brief  SEOF0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void SEOF0_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_SEOF0);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_SEOF0] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_SEOF0]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  SEOF1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void SEOF1_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_SEOF1);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_SEOF1] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_SEOF1]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  SEOF2 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void SEOF2_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_SEOF2);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_SEOF2] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_SEOF2]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  SEOF3 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void SEOF3_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_SEOF3);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_SEOF3] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_SEOF3]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  AWB0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void AWB0_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_AWB0);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_AWB0] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_AWB0]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  AWB1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void AWB1_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_AWB1);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_AWB1] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_AWB1]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  AWB2 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void AWB2_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_AWB2);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_AWB2] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_AWB2]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  AE interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void AE_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_AE);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_AE] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_AE]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  AE HIST interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void AE_HIST_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_AE_HIST);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_AE_HIST] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_AE_HIST]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  WDR interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void WDR_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_WDR);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_WDR] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_WDR]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  OSD PB interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void OSD_PB_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_OSD_PB);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_OSD_PB] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_OSD_PB]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Display interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void Display_IRQHandler(void)
{
    DSP2_MISC_Int_Clear(DSP2_MISC_INT_DISPLAY);

    if (dsp2MiscIntCbfArra[DSP2_MISC_INT_DISPLAY] != NULL) {
        dsp2MiscIntCbfArra[DSP2_MISC_INT_DISPLAY]();
    }
}
#endif

/*@} end of group DSP2_MISC_Public_Functions */

/*@} end of group DSP2_MISC */

/*@} end of group BL808_Peripheral_Driver */
