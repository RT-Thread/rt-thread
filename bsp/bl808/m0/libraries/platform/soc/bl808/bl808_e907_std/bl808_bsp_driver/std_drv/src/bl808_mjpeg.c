/**
  ******************************************************************************
  * @file    bl808_mjpeg.c
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
#include "bl808_mjpeg.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  MJPEG
 *  @{
 */

/** @defgroup  MJPEG_Private_Macros
 *  @{
 */

/*@} end of group MJPEG_Private_Macros */

/** @defgroup  MJPEG_Private_Types
 *  @{
 */

/*@} end of group MJPEG_Private_Types */

/** @defgroup  MJPEG_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *mjpegIntCbfArra[MJPEG_INT_ALL] = { NULL };
#endif

/*@} end of group MJPEG_Private_Variables */

/** @defgroup  MJPEG_Global_Variables
 *  @{
 */

/*@} end of group MJPEG_Global_Variables */

/** @defgroup  MJPEG_Private_Fun_Declaration
 *  @{
 */

/*@} end of group MJPEG_Private_Fun_Declaration */

/** @defgroup  MJPEG_Private_Functions
 *  @{
 */

/*@} end of group MJPEG_Private_Functions */

/** @defgroup  MJPEG_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Mjpeg module init
 *
 * @param  cfg: Mjpeg configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Init(MJPEG_CFG_Type *cfg)
{
    uint32_t tmpVal;

    /* Disable clock gate */
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_MJPEG);

    /* disable mjpeg */
    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_MJPEG_ENABLE);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_1, tmpVal);

    /* basic configure */
    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_MJPEG_HW_FRAME, cfg->frameCount);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_YUV_MODE, cfg->yuv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_W_XLEN, cfg->burst);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_MJPEG_BIT_ORDER, cfg->bitOrderEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_ORDER_U_EVEN, cfg->evenOrderEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_READ_FWRAP, cfg->readStartEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_REFLECT_DMY, cfg->reflectDmy);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_LAST_HF_HBLK_DMY, cfg->verticalDmy);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_LAST_HF_WBLK_DMY, cfg->horizationalDmy);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_1, tmpVal);

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_MJPEG_WAIT_CYCLE, cfg->waitCount);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_2, tmpVal);

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_FRAME_SIZE);

    switch (cfg->yuv) {
        case MJPEG_YUV422_INTERLEAVE:
        case MJPEG_YUV422_PLANAR:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_FRAME_WBLK, (cfg->resolutionX + 15) >> 4);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_FRAME_HBLK, (cfg->resolutionY + 7) >> 3);
            break;

        case MJPEG_YUV420:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_FRAME_WBLK, (cfg->resolutionX + 15) >> 4);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_FRAME_HBLK, (cfg->resolutionY + 15) >> 4);
            break;

        case MJPEG_YUV400:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_FRAME_WBLK, (cfg->resolutionX + 7) >> 3);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_FRAME_HBLK, (cfg->resolutionY + 7) >> 3);
            break;

        default:
            break;
    }

    BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_SIZE, tmpVal);

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_SWAP_MODE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_W_SWAP_MODE, cfg->swapModeEnable);
    BL_WR_REG(MJPEG_BASE, MJPEG_SWAP_MODE, tmpVal);

    /*align buffer to 16 bytes boundary, should be kept the same as CAM module*/
    BL_WR_REG(MJPEG_BASE, MJPEG_YY_FRAME_ADDR, (cfg->bufferCamYY & 0xFFFFFFF0));
    BL_WR_REG(MJPEG_BASE, MJPEG_UV_FRAME_ADDR, (cfg->bufferCamUV & 0xFFFFFFF0));
    BL_WR_REG(MJPEG_BASE, MJPEG_YUV_MEM, (cfg->sizeCamUV << 16) + cfg->sizeCamYY);

    /*align buffer to 16 bytes boundary*/
    BL_WR_REG(MJPEG_BASE, MJPEG_JPEG_FRAME_ADDR, (cfg->bufferMjpeg & 0xFFFFFFF0));

    /*Set memory brust size */
    if (cfg->burst == MJPEG_BURST_SINGLE) {
        BL_WR_REG(MJPEG_BASE, MJPEG_JPEG_STORE_MEMORY, cfg->sizeMjpeg / 8);
    } else if (cfg->burst == MJPEG_BURST_INCR4) {
        BL_WR_REG(MJPEG_BASE, MJPEG_JPEG_STORE_MEMORY, cfg->sizeMjpeg / 32);
    } else if (cfg->burst == MJPEG_BURST_INCR8) {
        BL_WR_REG(MJPEG_BASE, MJPEG_JPEG_STORE_MEMORY, cfg->sizeMjpeg / 64);
    } else if (cfg->burst == MJPEG_BURST_INCR16) {
        BL_WR_REG(MJPEG_BASE, MJPEG_JPEG_STORE_MEMORY, cfg->sizeMjpeg / 128);
    }

    /* Clear interrupt */
    BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 0x3F00);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(MJPEG_IRQn, MJPEG_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  Mjpeg set YUYV order, only work in interleave mode
 *
 * @param  y0: Y0 order
 * @param  u0: U0 order
 * @param  y1: Y1 order
 * @param  v0: V0 order
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Set_YUYV_Order_Interleave(uint8_t y0, uint8_t u0, uint8_t y1, uint8_t v0)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_HEADER_BYTE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_Y0_ORDER, y0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_U0_ORDER, u0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_Y1_ORDER, y1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_V0_ORDER, v0);
    BL_WR_REG(MJPEG_BASE, MJPEG_HEADER_BYTE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Mjpeg set Y/UV input cam id, only work in planar mode
 *
 * @param  yCamId: Cam id of Y used
 * @param  uvCamId: Cam id of UV used
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Set_Planar_Y_UV_Input(uint8_t yCamId, uint8_t uvCamId)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_YY_DVP2AXI_SEL, yCamId);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_UV_DVP2AXI_SEL, uvCamId);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Deinit mjpeg module
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Deinit(void)
{
    GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_MJPEG);
}

/****************************************************************************/ /**
 * @brief  Enable mjpeg module
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Enable(void)
{
    uint32_t tmpVal;

    /* Enable mjpeg module */
    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_1);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_MJPEG_ENABLE);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Disable mjpeg module
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Disable(void)
{
    uint32_t tmpVal;

    /* Disable mjpeg module */
    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_MJPEG_ENABLE);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Enable&disable mjpeg software mode and set frame count
 *
 * @param  swType: SW mode type
 * @param  count: Frame count
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_SW_Enable(MJPEG_SW_Mode_Type swType, uint8_t count)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_SW_FRAME, count);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_SW_KICK_MODE, swType);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_2, tmpVal);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_MJPEG_SW_MODE);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_2, tmpVal);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_MJPEG_SW_MODE);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  MJPEG software mode run, software mode enable first
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_SW_Run(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_2);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_MJPEG_SW_RUN);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_2, tmpVal);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_MJPEG_SW_RUN);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Set memory to store block line for frame on SW kick
 *
 * @param  count: Block line count
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_SW_Set_Kick_Block(uint16_t count)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_YUV_MEM_SW);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_SW_KICK_HBLK, count);
    BL_WR_REG(MJPEG_BASE, MJPEG_YUV_MEM_SW, tmpVal);
}

/****************************************************************************/ /**
 * @brief  MJPEG SW mode kick once
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_SW_Kick(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_2);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_SW_KICK);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get one mjpeg frame
 *
 * @param  info: Mjpeg frame infomation pointer
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Get_Frame_Info(MJPEG_Frame_Info *info)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_3);

    info->validFrames = BL_GET_REG_BITS_VAL(tmpVal, MJPEG_FRAME_VALID_CNT);
    info->curFrameId = BL_GET_REG_BITS_VAL(BL_RD_REG(MJPEG_BASE, MJPEG_FRAME_ID_10), MJPEG_FRAME_ID_0);
    info->curFrameAddr = BL_RD_REG(MJPEG_BASE, MJPEG_START_ADDR0);
    info->curFrameBytes = (BL_RD_REG(MJPEG_BASE, MJPEG_BIT_CNT0) + 7) >> 3;
    info->status = tmpVal;
}

/****************************************************************************/ /**
 * @brief  Get available count of frames
 *
 * @param  None
 *
 * @return Frames count
 *
*******************************************************************************/
uint8_t MJPEG_Get_Frame_Count(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_3), MJPEG_FRAME_VALID_CNT);
}

/****************************************************************************/ /**
 * @brief  Pop one mjpeg frame
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Pop_Frame(void)
{
    BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 1);
}

/****************************************************************************/ /**
 * @brief  Free current read memory block
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Current_Block_Clear(void)
{
    BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 0x2);
}

/****************************************************************************/ /**
 * @brief  Current read memory block index
 *
 * @param  None
 *
 * @return Block number
 *
*******************************************************************************/
MJPEG_Swap_Block_Type MJPEG_Get_Current_Block(void)
{
    return (MJPEG_Swap_Block_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(MJPEG_BASE, MJPEG_SWAP_MODE), MJPEG_STS_READ_SWAP_IDX);
}

/****************************************************************************/ /**
 * @brief  Get block status, full or not full
 *
 * @param  block: Block number
 *
 * @return Block status
 *
*******************************************************************************/
BL_Sts_Type MJPEG_Block_Is_Full(MJPEG_Swap_Block_Type block)
{
    CHECK_PARAM(IS_MJPEG_SWAP_BLOCK_TYPE(block));

    if (MJPEG_BLOCK_0 == block) {
        return (BL_Sts_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(MJPEG_BASE, MJPEG_SWAP_MODE), MJPEG_STS_SWAP0_FULL);
    } else {
        return (BL_Sts_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(MJPEG_BASE, MJPEG_SWAP_MODE), MJPEG_STS_SWAP1_FULL);
    }
}

/****************************************************************************/ /**
 * @brief  Current read memory block is frame start
 *
 * @param  None
 *
 * @return Set or reset
 *
*******************************************************************************/
BL_Sts_Type MJPEG_Current_Block_Is_Start(void)
{
    return (BL_Sts_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(MJPEG_BASE, MJPEG_SWAP_MODE), MJPEG_STS_SWAP_FSTART);
}

/****************************************************************************/ /**
 * @brief  Current read memory block is frame end
 *
 * @param  None
 *
 * @return Set or reset
 *
*******************************************************************************/
BL_Sts_Type MJPEG_Current_Block_Is_End(void)
{
    return (BL_Sts_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(MJPEG_BASE, MJPEG_SWAP_MODE), MJPEG_STS_SWAP_FEND);
}

/****************************************************************************/ /**
 * @brief  Get frame remain bit count in last block, only valid when current read memory block is
 *         frame end
 *
 * @param  None
 *
 * @return Bit count
 *
*******************************************************************************/
uint32_t MJPEG_Get_Remain_Bit(void)
{
    return BL_RD_REG(MJPEG_BASE, MJPEG_SWAP_BIT_CNT);
}

/****************************************************************************/ /**
 * @brief  Set frame threshold to issue normal interrupt
 *
 * @param  count: Frame threshold
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Set_Frame_Threshold(uint8_t count)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_FRAME_CNT_TRGR_INT, count);
    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_3, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Set bytes of frame head to preserve
 *
 * @param  size: Bytes of head
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Frame_Head_Set_Size(uint16_t size)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_HEADER_BYTE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_HEAD_BYTE, size);
    BL_WR_REG(MJPEG_BASE, MJPEG_HEADER_BYTE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Enable or disable auto fill frame tail with 0xff and 0xd9
 *
 * @param  enable: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Frame_Tail_Auto_Fill(BL_Fun_Type enable)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_HEADER_BYTE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJPEG_REG_TAIL_EXP, enable);
    BL_WR_REG(MJPEG_BASE, MJPEG_HEADER_BYTE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Set parameter in Y quantize table according to index
 *
 * @param  index: Q parameter index
 * @param  qParameter: Q parameter value
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Set_Quantize_Parameter_Y(uint8_t index, uint16_t qParameter)
{
    uint32_t tmpVal;

    if (index > 63) {
        return;
    }

    index = index % 8 * 8 + index / 8;

    tmpVal = 2048 / qParameter;

    if (20480 / qParameter % 10 > 4) {
        tmpVal++;
    }

    qParameter = tmpVal & 0xffff;

    tmpVal = BL_RD_WORD(MJPEG_BASE + MJPEG_Q_PARAM_00_OFFSET + (index >> 1) * 4);
    BL_WR_WORD(MJPEG_BASE + MJPEG_Q_PARAM_00_OFFSET + (index >> 1) * 4, (tmpVal & 0xffff0000 >> 16 * (index % 2)) | qParameter << 16 * (index % 2));
}

/****************************************************************************/ /**
 * @brief  Set parameter in UV quantize table according to index
 *
 * @param  index: Q parameter index
 * @param  qParameter: Q parameter value
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Set_Quantize_Parameter_UV(uint8_t index, uint16_t qParameter)
{
    uint32_t tmpVal;

    if (index > 63) {
        return;
    }

    index = index % 8 * 8 + index / 8;

    tmpVal = 2048 / qParameter;

    if (20480 / qParameter % 10 > 4) {
        tmpVal++;
    }

    qParameter = tmpVal & 0xffff;

    tmpVal = BL_RD_WORD(MJPEG_BASE + MJPEG_Q_PARAM_40_OFFSET + (index >> 1) * 4);
    BL_WR_WORD(MJPEG_BASE + MJPEG_Q_PARAM_40_OFFSET + (index >> 1) * 4, (tmpVal & 0xffff0000 >> 16 * (index % 2)) | qParameter << 16 * (index % 2));
}

/****************************************************************************/ /**
 * @brief  Set Y quantize table
 *
 * @param  qTable: Y table
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Set_Quantize_Table_Y(uint16_t *qTable)
{
    uint8_t i, j;
    uint16_t tmpVal1;
    uint16_t tmpVal2;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            tmpVal1 = 2048 / qTable[16 * j + i];
            tmpVal2 = 2048 / qTable[16 * j + i + 8];

            if (20480 / qTable[16 * j + i] % 10 > 4) {
                tmpVal1++;
            }

            if (20480 / qTable[16 * j + i + 8] % 10 > 4) {
                tmpVal2++;
            }

            BL_WR_WORD(MJPEG_BASE + MJPEG_Q_PARAM_00_OFFSET + (i * 4 + j) * 4, tmpVal1 | tmpVal2 << 16);
        }
    }
}

/****************************************************************************/ /**
 * @brief  Set UV quantize table
 *
 * @param  qTable: UV table
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Set_Quantize_Table_UV(uint16_t *qTable)
{
    uint8_t i, j;
    uint16_t tmpVal1;
    uint16_t tmpVal2;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            tmpVal1 = 2048 / qTable[16 * j + i];
            tmpVal2 = 2048 / qTable[16 * j + i + 8];

            if (20480 / qTable[16 * j + i] % 10 > 4) {
                tmpVal1++;
            }

            if (20480 / qTable[16 * j + i + 8] % 10 > 4) {
                tmpVal2++;
            }

            BL_WR_WORD(MJPEG_BASE + MJPEG_Q_PARAM_40_OFFSET + (i * 4 + j) * 4, tmpVal1 | tmpVal2 << 16);
        }
    }
}

/****************************************************************************/ /**
 * @brief  Calculate quantize table according to input table and quality factor
 *
 * @param  inputTable: Pointer of input table
 * @param  outputTable: Pointer of output table
 * @param  quality: Quality factor
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Calculate_Quantize_Table(uint16_t *inputTable, uint16_t *outputTable, uint8_t quality)
{
    uint32_t scaleFactor, i;

    if (quality == 0) {
        quality = 1;
    } else if (quality > 100) {
        quality = 100;
    }

    if (quality < 50) {
        scaleFactor = 5000000 / quality;
    } else {
        scaleFactor = 200000 - quality * 2000;
    }

    for (i = 0; i < 64; i++) {
        outputTable[i] = (inputTable[i] * scaleFactor + 50000) / 100000;

        if (outputTable[i] == 0) {
            outputTable[i] = 1;
        } else if (outputTable[i] > 0xff) {
            outputTable[i] = 0xff;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Quantize SRAM switch
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_Quantize_SRAM_Switch(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_Q_ENC);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_Q_SRAM_SW);
    BL_WR_REG(MJPEG_BASE, MJPEG_Q_ENC, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get current quantize SRAM selection for encode
 *
 * @param  None
 *
 * @return Current quantize SRAM
 *
*******************************************************************************/
uint8_t MJPEG_Get_Current_Quantize_SRAM(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_Q_ENC);
    return BL_GET_REG_BITS_VAL(tmpVal, MJPEG_STS_Q_SRAM_ENC);
}

/****************************************************************************/ /**
 * @brief  Get frame0~3 quantize SRAM selection
 *
 * @param  frameId: Frame id
 *
 * @return Quantize SRAM
 *
*******************************************************************************/
uint8_t MJPEG_Get_Frame_Quantize_SRAM(MJPEG_Frame_ID_Type frameId)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_Q_ENC);
    return (tmpVal >> frameId & 1);
}

/****************************************************************************/ /**
 * @brief  MJPEG Enable Disable Interrupt
 *
 * @param  intType: MJPEG Interrupt Type
 * @param  intMask: Enable or Disable
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_IntMask(MJPEG_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_MJPEG_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_3);

    switch (intType) {
        case MJPEG_INT_NORMAL:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_NORMAL_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_NORMAL_EN);
            }

            break;

        case MJPEG_INT_CAM_OVERWRITE:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_CAM_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_CAM_EN);
            }

            break;

        case MJPEG_INT_MEM_OVERWRITE:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_MEM_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_MEM_EN);
            }

            break;

        case MJPEG_INT_FRAME_OVERWRITE:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_FRAME_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_FRAME_EN);
            }

            break;

        case MJPEG_INT_BACK_IDLE:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_IDLE_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_IDLE_EN);
            }

            break;

        case MJPEG_INT_SWAP:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_SWAP_EN);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_SWAP_EN);
            }

            break;

        case MJPEG_INT_ALL:
            if (intMask == UNMASK) {
                /* Enable all interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_NORMAL_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_CAM_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_MEM_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_FRAME_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_IDLE_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_SWAP_EN);
            } else {
                /* Disable all interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_NORMAL_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_CAM_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_MEM_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_FRAME_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_IDLE_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJPEG_REG_INT_SWAP_EN);
            }

            break;

        default:
            break;
    }

    BL_WR_REG(MJPEG_BASE, MJPEG_CONTROL_3, tmpVal);
}

/****************************************************************************/ /**
 * @brief  MJPEG Interrupt Clear
 *
 * @param  intType: MJPEG Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void MJPEG_IntClr(MJPEG_INT_Type intType)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_MJPEG_INT_TYPE(intType));

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP);

    switch (intType) {
        case MJPEG_INT_NORMAL:
            tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_NORMAL_CLR);
            break;

        case MJPEG_INT_CAM_OVERWRITE:
            tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_CAM_CLR);
            break;

        case MJPEG_INT_MEM_OVERWRITE:
            tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_MEM_CLR);
            break;

        case MJPEG_INT_FRAME_OVERWRITE:
            tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_FRAME_CLR);
            break;

        case MJPEG_INT_BACK_IDLE:
            tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_IDLE_CLR);
            break;

        case MJPEG_INT_SWAP:
            tmpVal = BL_SET_REG_BIT(tmpVal, MJPEG_REG_INT_SWAP_CLR);
            break;

        case MJPEG_INT_ALL:
            tmpVal = 0x3F00;

        default:
            break;
    }

    BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Install mjpeg interrupt callback function
 *
 * @param  intType: MJPEG interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void MJPEG_Int_Callback_Install(MJPEG_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_MJPEG_INT_TYPE(intType));

    mjpegIntCbfArra[intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  Mjpeg interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void MJPEG_IRQHandler(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_3);

    if (BL_IS_REG_BIT_SET(tmpVal, MJPEG_STS_NORMAL_INT)) {
        BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 0x100);

        if (mjpegIntCbfArra[MJPEG_INT_NORMAL] != NULL) {
            /* call the callback function */
            mjpegIntCbfArra[MJPEG_INT_NORMAL]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJPEG_STS_CAM_INT)) {
        BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 0x200);

        if (mjpegIntCbfArra[MJPEG_INT_CAM_OVERWRITE] != NULL) {
            /* call the callback function */
            mjpegIntCbfArra[MJPEG_INT_CAM_OVERWRITE]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJPEG_STS_MEM_INT)) {
        BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 0x400);

        if (mjpegIntCbfArra[MJPEG_INT_MEM_OVERWRITE] != NULL) {
            /* call the callback function */
            mjpegIntCbfArra[MJPEG_INT_MEM_OVERWRITE]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJPEG_STS_FRAME_INT)) {
        BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 0x800);

        if (mjpegIntCbfArra[MJPEG_INT_FRAME_OVERWRITE] != NULL) {
            /* call the callback function */
            mjpegIntCbfArra[MJPEG_INT_FRAME_OVERWRITE]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJPEG_STS_IDLE_INT)) {
        BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 0x1000);

        if (mjpegIntCbfArra[MJPEG_INT_BACK_IDLE] != NULL) {
            /* call the callback function */
            mjpegIntCbfArra[MJPEG_INT_BACK_IDLE]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, MJPEG_STS_SWAP_INT)) {
        BL_WR_REG(MJPEG_BASE, MJPEG_FRAME_FIFO_POP, 0x2000);

        if (mjpegIntCbfArra[MJPEG_INT_SWAP] != NULL) {
            /* call the callback function */
            mjpegIntCbfArra[MJPEG_INT_SWAP]();
        }
    }
}
#endif

/*@} end of group MJPEG_Public_Functions */

/*@} end of group MJPEG */

/*@} end of group BL808_Peripheral_Driver */
