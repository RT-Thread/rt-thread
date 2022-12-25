/**
  ******************************************************************************
  * @file    bl808_cam.c
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

#include "bl808.h"
#include "bl808_cam.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CAM
 *  @{
 */

/** @defgroup  CAM_Private_Macros
 *  @{
 */

/*@} end of group CAM_Private_Macros */

/** @defgroup  CAM_Private_Types
 *  @{
 */

/*@} end of group CAM_Private_Types */

/** @defgroup  CAM_Private_Variables
 *  @{
 */
static const uint32_t camAddr[CAM_ID_MAX] = { DVP0_BASE, DVP1_BASE, DVP2_BASE, DVP3_BASE,
                                              DVP4_BASE, DVP5_BASE, DVP6_BASE, DVP7_BASE };
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *camIntCbfArra[CAM_ID_MAX][CAM_INT_ALL] = { { NULL } };
#endif

/*@} end of group CAM_Private_Variables */

/** @defgroup  CAM_Global_Variables
 *  @{
 */

/*@} end of group CAM_Global_Variables */

/** @defgroup  CAM_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static void CAM_IntHandler(CAM_ID_Type camId);
#endif

/*@} end of group CAM_Private_Fun_Declaration */

/** @defgroup  CAM_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Camera interrupt common handler function
 *
 * @param  camId: Camera ID type
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static void CAM_IntHandler(CAM_ID_Type camId)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP_STATUS_AND_ERROR);

    if (BL_IS_REG_BIT_SET(tmpVal, CAM_STS_NORMAL_INT)) {
        CAM_IntClr(camId, CAM_INT_NORMAL);

        if (camIntCbfArra[camId][CAM_INT_NORMAL] != NULL) {
            /* call the callback function */
            camIntCbfArra[camId][CAM_INT_NORMAL]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, CAM_STS_MEM_INT)) {
        CAM_IntClr(camId, CAM_INT_MEMORY_OVERWRITE);

        if (camIntCbfArra[camId][CAM_INT_MEMORY_OVERWRITE] != NULL) {
            /* call the callback function */
            camIntCbfArra[camId][CAM_INT_MEMORY_OVERWRITE]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, CAM_STS_FRAME_INT)) {
        CAM_IntClr(camId, CAM_INT_FRAME_OVERWRITE);

        if (camIntCbfArra[camId][CAM_INT_FRAME_OVERWRITE] != NULL) {
            /* call the callback function */
            camIntCbfArra[camId][CAM_INT_FRAME_OVERWRITE]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, CAM_STS_FIFO_INT)) {
        CAM_IntClr(camId, CAM_INT_FIFO_OVERWRITE);

        if (camIntCbfArra[camId][CAM_INT_FIFO_OVERWRITE] != NULL) {
            /* call the callback function */
            camIntCbfArra[camId][CAM_INT_FIFO_OVERWRITE]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, CAM_STS_HCNT_INT)) {
        CAM_IntClr(camId, CAM_INT_HSYNC_CNT_ERROR);

        if (camIntCbfArra[camId][CAM_INT_HSYNC_CNT_ERROR] != NULL) {
            /* call the callback function */
            camIntCbfArra[camId][CAM_INT_HSYNC_CNT_ERROR]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, CAM_STS_VCNT_INT)) {
        CAM_IntClr(camId, CAM_INT_VSYNC_CNT_ERROR);

        if (camIntCbfArra[camId][CAM_INT_VSYNC_CNT_ERROR] != NULL) {
            /* call the callback function */
            camIntCbfArra[camId][CAM_INT_VSYNC_CNT_ERROR]();
        }
    }
}
#endif

/*@} end of group CAM_Private_Functions */

/** @defgroup  CAM_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Camera module init
 *
 * @param  camId: CAM ID type
 * @param  cfg: Camera configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void CAM_Init(CAM_ID_Type camId, CAM_CFG_Type *cfg)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));
    CHECK_PARAM(IS_CAM_SW_MODE_TYPE(cfg->swMode));
    CHECK_PARAM(IS_CAM_INPUT_PIX_WIDTH_TYPE(cfg->pixWidth));
    CHECK_PARAM(IS_CAM_OUTPUT_DROP_MODE_TYPE(cfg->dropMode));
    CHECK_PARAM(IS_CAM_FRAME_ACTIVE_POL(cfg->framePol));
    CHECK_PARAM(IS_CAM_LINE_ACTIVE_POL(cfg->linePol));
    CHECK_PARAM(IS_CAM_BURST_TYPE(cfg->burstType));
    CHECK_PARAM(IS_CAM_SENSOR_MODE_TYPE(cfg->camSensorMode));

    /* Disable clock gate */
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_CAM);

    /* Set camera configuration */
    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_CONFIGUE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_DVP_ENABLE);
    BL_WR_REG(CAMx, CAM_DVP2AXI_CONFIGUE, tmpVal);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_SW_MODE, cfg->swMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_DVP_DATA_MODE, cfg->pixWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_FRAM_VLD_POL, cfg->framePol);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_LINE_VLD_POL, cfg->linePol);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_XLEN, cfg->burstType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_DVP_MODE, cfg->camSensorMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_DVP_WAIT_CYCLE, cfg->waitCount);

    switch (cfg->dropMode) {
        case CAM_DROP_NONE:
            tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_DROP_EN);
            tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_V_SUBSAMPLE_EN);
            break;

        case CAM_DROP_ODD_ROW_ODD_PIXEL:
            tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_DROP_EN);
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_V_SUBSAMPLE_EN);
            tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_V_SUBSAMPLE_POL);
            break;

        case CAM_DROP_ODD_ROW_EVEN_PIXEL:
            tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_DROP_EN);
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_V_SUBSAMPLE_EN);
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_V_SUBSAMPLE_POL);
            break;

        case CAM_DROP_ALL_ODD_PIXEL:
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_DROP_EN);
            tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_DROP_EVEN);
            tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_V_SUBSAMPLE_EN);
            break;

        case CAM_DROP_ALL_EVEN_PIXEL:
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_DROP_EN);
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_DROP_EVEN);
            tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_V_SUBSAMPLE_EN);
            break;

        default:
            break;
    }

    BL_WR_REG(CAMx, CAM_DVP2AXI_CONFIGUE, tmpVal);

    /* Set frame count to issue interrupt at sw mode */
    tmpVal = BL_RD_REG(CAMx, CAM_DVP_STATUS_AND_ERROR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_FRAME_CNT_TRGR_INT, cfg->swIntCnt);
    BL_WR_REG(CAMx, CAM_DVP_STATUS_AND_ERROR, tmpVal);

    /* Set camera memory start address, memory brust size and frame byte size */
    BL_WR_REG(CAMx, CAM_DVP2AXI_ADDR_START, cfg->memStart & 0xFFFFFFF0);

    switch (cfg->burstType) {
        case CAM_BURST_TYPE_SINGLE:
            tmpVal = cfg->memSize / 8;
            break;

        case CAM_BURST_TYPE_INCR4:
            tmpVal = cfg->memSize / 32;
            break;

        case CAM_BURST_TYPE_INCR8:
            tmpVal = cfg->memSize / 64;
            break;

        case CAM_BURST_TYPE_INCR16:
            tmpVal = cfg->memSize / 128;
            break;

        case CAM_BURST_TYPE_INCR32:
            tmpVal = cfg->memSize / 256;
            break;

        case CAM_BURST_TYPE_INCR64:
            tmpVal = cfg->memSize / 512;
            break;

        default:
            tmpVal = 0;
            break;
    }

    BL_WR_REG(CAMx, CAM_DVP2AXI_MEM_BCNT, tmpVal);

    BL_WR_REG(CAMx, CAM_DVP2AXI_FRAME_BCNT, cfg->frameSize);

    /* Clear interrupt */
    BL_WR_REG(CAMx, CAM_DVP_FRAME_FIFO_POP, 0xFFFF0);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(DVP2BUS_INT0_IRQn, CAM0_IRQHandler);
    Interrupt_Handler_Register(DVP2BUS_INT1_IRQn, CAM1_IRQHandler);
    Interrupt_Handler_Register(DVP2BUS_INT2_IRQn, CAM2_IRQHandler);
    Interrupt_Handler_Register(DVP2BUS_INT3_IRQn, CAM3_IRQHandler);
    Interrupt_Handler_Register(DVP2BUS_INT4_IRQn, CAM4_IRQHandler);
    Interrupt_Handler_Register(DVP2BUS_INT5_IRQn, CAM5_IRQHandler);
    Interrupt_Handler_Register(DVP2BUS_INT6_IRQn, CAM6_IRQHandler);
    Interrupt_Handler_Register(DVP2BUS_INT7_IRQn, CAM7_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  Deinit camera module
 *
 * @param  camId: CAM ID type
 *
 * @return None
 *
*******************************************************************************/
void CAM_Deinit(CAM_ID_Type camId)
{
    switch(camId){
        case CAM0_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DVP2BUSA);
            break;
        case CAM1_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DVP2BUSB);
            break;
        case CAM2_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DVP2BUSC);
            break;
        case CAM3_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DVP2BUSD);
            break;
        case CAM4_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DVP2BUSE);
            break;
        case CAM5_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DVP2BUSF);
            break;
        case CAM6_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DVP2BUSG);
            break;
        case CAM7_ID:
            GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DVP2BUSH);
            break;
        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  Enable camera module
 *
 * @param  camId: CAM ID type
 *
 * @return None
 *
*******************************************************************************/
void CAM_Enable(CAM_ID_Type camId)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    /* Enable camera module */
    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_DVP_ENABLE);
    BL_WR_REG(CAMx, CAM_DVP2AXI_CONFIGUE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Disable camera module
 *
 * @param  camId: CAM ID type
 *
 * @return None
 *
*******************************************************************************/
void CAM_Disable(CAM_ID_Type camId)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    /* Disable camera module */
    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_CONFIGUE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_DVP_ENABLE);
    BL_WR_REG(CAMx, CAM_DVP2AXI_CONFIGUE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Camera clock gate function
 *
 * @param  camId: CAM ID type
 * @param  enable: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void CAM_Clock_Gate(CAM_ID_Type camId, BL_Fun_Type enable)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_DVP_PIX_CLK_CG, enable);
    BL_WR_REG(CAMx, CAM_DVP2AXI_CONFIGUE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Camera hsync crop function
 *
 * @param  camId: CAM ID type
 * @param  start: Valid hsync start count
 * @param  end: Valid hsync end count
 *
 * @return None
 *
*******************************************************************************/
void CAM_Hsync_Crop(CAM_ID_Type camId, uint16_t start, uint16_t end)
{
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    BL_WR_REG(CAMx, CAM_DVP2AXI_HSYNC_CROP, (start << 16) + end);
}

/****************************************************************************/ /**
 * @brief  Camera vsync crop function
 *
 * @param  camId: CAM ID type
 * @param  start: Valid vsync start count
 * @param  end: Valid vsync end count
 *
 * @return None
 *
*******************************************************************************/
void CAM_Vsync_Crop(CAM_ID_Type camId, uint16_t start, uint16_t end)
{
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    BL_WR_REG(CAMx, CAM_DVP2AXI_VSYNC_CROP, (start << 16) + end);
}

/****************************************************************************/ /**
 * @brief  Camera set total valid pix count in a line function
 *
 * @param  camId: CAM ID type
 * @param  count: Count value
 *
 * @return None
 *
*******************************************************************************/
void CAM_Set_Hsync_Total_Count(CAM_ID_Type camId, uint16_t count)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_FRAM_EXM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_TOTAL_HCNT, count);
    BL_WR_REG(CAMx, CAM_DVP2AXI_FRAM_EXM, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Camera set total valid line count in a frame function
 *
 * @param  camId: CAM ID type
 * @param  count: Count value
 *
 * @return None
 *
*******************************************************************************/
void CAM_Set_Vsync_Total_Count(CAM_ID_Type camId, uint16_t count)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_FRAM_EXM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_TOTAL_VCNT, count);
    BL_WR_REG(CAMx, CAM_DVP2AXI_FRAM_EXM, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get one camera frame
 *
 * @param  camId: CAM ID type
 * @param  info: Camera frame infomation pointer
 *
 * @return None
 *
*******************************************************************************/
void CAM_Get_Frame_Info(CAM_ID_Type camId, CAM_Frame_Info *info)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP_STATUS_AND_ERROR);

    info->validFrames = BL_GET_REG_BITS_VAL(tmpVal, CAM_FRAME_VALID_CNT);
    info->curFrameId = BL_GET_REG_BITS_VAL(BL_RD_REG(CAMx, CAM_FRAME_ID_STS01), CAM_FRAME_ID_0);
    info->curFrameAddr = BL_RD_REG(CAMx, CAM_FRAME_START_ADDR0);
    info->curFrameBytes = BL_RD_REG(CAMx, CAM_DVP2AXI_FRAME_BCNT);
    info->status = tmpVal;
}

/****************************************************************************/ /**
 * @brief  Get available count of frames
 *
 * @param  camId: CAM ID type
 *
 * @return Frames count
 *
*******************************************************************************/
uint8_t CAM_Get_Frame_Count(CAM_ID_Type camId)
{
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(CAMx, CAM_DVP_STATUS_AND_ERROR), CAM_FRAME_VALID_CNT);
}

/****************************************************************************/ /**
 * @brief  Pop one camera frame
 *
 * @param  camId: CAM ID type
 *
 * @return None
 *
*******************************************************************************/
void CAM_Pop_Frame(CAM_ID_Type camId)
{
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    /* Pop one frame */
    BL_WR_REG(CAMx, CAM_DVP_FRAME_FIFO_POP, 1);
}

/****************************************************************************/ /**
 * @brief  CAMERA Enable Disable Interrupt
 *
 * @param  camId: CAM ID type
 * @param  intType: CAMERA Interrupt Type
 * @param  intMask: Enable or Disable
 *
 * @return None
 *
*******************************************************************************/
void CAM_IntMask(CAM_ID_Type camId, CAM_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));
    CHECK_PARAM(IS_CAM_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP_STATUS_AND_ERROR);

    switch (intType) {
        case CAM_INT_NORMAL:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_NORMAL_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_INT_NORMAL_EN);
            }

            break;

        case CAM_INT_MEMORY_OVERWRITE:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_MEM_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_INT_MEM_EN);
            }

            break;

        case CAM_INT_FRAME_OVERWRITE:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_FRAME_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_INT_FRAME_EN);
            }

            break;

        case CAM_INT_FIFO_OVERWRITE:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_FIFO_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_INT_FIFO_EN);
            }

            break;

        case CAM_INT_VSYNC_CNT_ERROR:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_VCNT_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_INT_VCNT_EN);
            }

            break;

        case CAM_INT_HSYNC_CNT_ERROR:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_HCNT_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, CAM_REG_INT_HCNT_EN);
            }

            break;

        case CAM_INT_ALL:
            if (intMask == UNMASK) {
                /* Enable all interrupt */
                tmpVal |= 0xFC0;
            } else {
                /* Disable all interrupt */
                tmpVal &= 0xFFFFF03F;
            }

            break;

        default:
            break;
    }

    BL_WR_REG(CAMx, CAM_DVP_STATUS_AND_ERROR, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CAMERA Interrupt Clear
 *
 * @param  camId: CAM ID type
 * @param  intType: CAMERA Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void CAM_IntClr(CAM_ID_Type camId, CAM_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP_FRAME_FIFO_POP);

    switch (intType) {
        case CAM_INT_NORMAL:
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_NORMAL_CLR);
            break;

        case CAM_INT_MEMORY_OVERWRITE:
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_MEM_CLR);
            break;

        case CAM_INT_FRAME_OVERWRITE:
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_FRAME_CLR);
            break;

        case CAM_INT_FIFO_OVERWRITE:
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_FIFO_CLR);
            break;

        case CAM_INT_VSYNC_CNT_ERROR:
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_VCNT_CLR);
            break;

        case CAM_INT_HSYNC_CNT_ERROR:
            tmpVal = BL_SET_REG_BIT(tmpVal, CAM_REG_INT_HCNT_CLR);
            break;

        case CAM_INT_ALL:
            tmpVal = 0xFFFF0;

        default:
            break;
    }

    BL_WR_REG(CAMx, CAM_DVP_FRAME_FIFO_POP, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Install camera interrupt callback function
 *
 * @param  camId: CAM ID type
 * @param  intType: CAMERA interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM_Int_Callback_Install(CAM_ID_Type camId, CAM_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));
    CHECK_PARAM(IS_CAM_INT_TYPE(intType));

    camIntCbfArra[camId][intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  CAMERA input 8-bit mode lower/upper byte select function
 *
 * @param  camId: CAM ID type
 * @param  byteType: Byte type
 *
 * @return None
 *
*******************************************************************************/
void CAM_8_Bit_Byte_Select(CAM_ID_Type camId, CAM_8_Bit_Byte_Type byteType)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));
    CHECK_PARAM(IS_CAM_8_BIT_BYTE_TYPE(byteType));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_DVP_DATA_BSEL, byteType);
    BL_WR_REG(CAMx, CAM_DVP2AXI_CONFIGUE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CAMERA input 16-bit mode RGB order select function
 *
 * @param  camId: CAM ID type
 * @param  rgbType: RGB order type
 *
 * @return None
 *
*******************************************************************************/
void CAM_16_Bit_RGB_order(CAM_ID_Type camId, CAM_16_Bit_RGB_Type rgbType)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));
    CHECK_PARAM(IS_CAM_16_BIT_RGB_TYPE(rgbType));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_MISC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_FORMAT_565, rgbType);
    BL_WR_REG(CAMx, CAM_DVP2AXI_MISC, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CAMERA input 32-bit mode alpha value set function
 *
 * @param  camId: CAM ID type
 * @param  alpha: Alpha value
 *
 * @return None
 *
*******************************************************************************/
void CAM_32_Bit_Alpha_Set(CAM_ID_Type camId, uint8_t alpha)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_MISC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_ALPHA, alpha);
    BL_WR_REG(CAMx, CAM_DVP2AXI_MISC, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CAMERA set frame period and bitwise frame valid in period function
 *
 * @param  camId: CAM ID type
 * @param  period: Frame period count
 * @param  validBit: Bitwise frame valid in period
 *
 * @return None
 *
*******************************************************************************/
void CAM_Set_Frame_Valid_Period(CAM_ID_Type camId, uint8_t period, uint32_t validBit)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_FRAME_PERIOD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_FRAME_PERIOD, period);
    BL_WR_REG(CAMx, CAM_DVP2AXI_FRAME_PERIOD, tmpVal);

    BL_WR_REG(CAMx, CAM_DVP2AXI_FRAME_VLD, validBit);
}

/****************************************************************************/ /**
 * @brief  Enable or disable function that covers first frame memory everytime in hardware mode
 *
 * @param  camId: CAM ID type
 * @param  enable: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void CAM_HW_Cover_First_Frame_Everytime(CAM_ID_Type camId, BL_Fun_Type enable)
{
    uint32_t tmpVal;
    uint32_t CAMx = camAddr[camId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(camId));

    tmpVal = BL_RD_REG(CAMx, CAM_DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAM_REG_HW_MODE_FWRAP, enable);
    BL_WR_REG(CAMx, CAM_DVP2AXI_CONFIGUE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Camera 0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM0_IRQHandler(void)
{
    CAM_IntHandler(CAM0_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  Camera 1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM1_IRQHandler(void)
{
    CAM_IntHandler(CAM1_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  Camera 2 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM2_IRQHandler(void)
{
    CAM_IntHandler(CAM2_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  Camera 3 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM3_IRQHandler(void)
{
    CAM_IntHandler(CAM3_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  Camera 4 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM4_IRQHandler(void)
{
    CAM_IntHandler(CAM4_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  Camera 5 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM5_IRQHandler(void)
{
    CAM_IntHandler(CAM5_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  Camera 6 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM6_IRQHandler(void)
{
    CAM_IntHandler(CAM6_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  Camera 7 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CAM7_IRQHandler(void)
{
    CAM_IntHandler(CAM7_ID);
}
#endif

/*@} end of group CAM_Public_Functions */

/*@} end of group CAM */

/*@} end of group BL808_Peripheral_Driver */
