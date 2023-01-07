/**
  ******************************************************************************
  * @file    bl808_mjdec.c
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
#include "bl808_mjdec.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  MJDEC
 *  @{
 */

/** @defgroup  MJDEC_Private_Macros
 *  @{
 */

/*@} end of group MJDEC_Private_Macros */

/** @defgroup  MJDEC_Private_Types
 *  @{
 */

/*@} end of group MJDEC_Private_Types */

/** @defgroup  MJDEC_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type * mjdecIntCbfArra[MJDEC_INT_ALL] = {NULL};
#endif

/*@} end of group MJDEC_Private_Variables */

/** @defgroup  MJDEC_Global_Variables
 *  @{
 */

/*@} end of group MJDEC_Global_Variables */

/** @defgroup  MJDEC_Private_Fun_Declaration
 *  @{
 */

/*@} end of group MJDEC_Private_Fun_Declaration */

/** @defgroup  MJDEC_Private_Functions
 *  @{
 */

/*@} end of group MJDEC_Private_Functions */

/** @defgroup  MJDEC_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Mjdec module init
 *
 * @param  cfg: Mjdec configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_Init(MJDEC_CFG_Type *cfg)
{
    uint32_t tmpVal;
    uint32_t q;

    /* disable mjdec */
    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJDEC_REG_MJ_DEC_ENABLE);
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);

    if(cfg->picQuality < 1) {
        q = 1;
    } else if(cfg->picQuality > 75) {
        q = 100;
    } else {
        q = cfg->picQuality;
    }

    /* basic configure */
    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_YUV_MODE, cfg->yuv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_W_XLEN, cfg->burstWrite);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_R_XLEN, cfg->burstRead);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_U_EVEN, cfg->evenOrderEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_LAST_HF_BLK_DMY, cfg->dmyBlock);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_LAST_HF_HBLK_DMY, cfg->dmyVertical);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_LAST_HF_WBLK_DMY, cfg->dmyHorizational);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_SWAP_MODE, cfg->swapMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_Q_MODE, q);
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);

    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MJDEC_REG_FRAME_CNT_TRGR_INT,cfg->intCnt);
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_3,tmpVal);

    /* align buffer to 16 bytes boundary */
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_YY_FRAME_ADDR, (cfg->bufferFrameYY + 0xF) & (~0xF));
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_UV_FRAME_ADDR, (cfg->bufferFrameUV + 0xF) & (~0xF));
    
    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_FRAME_SIZE);
    switch(cfg->yuv)
    {
        case MJDEC_YUV422_PLANAR:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_WBLK, (cfg->resolutionX+15)>>4);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_HBLK, (cfg->resolutionY+7)>>3);
            break;
        case MJDEC_YUV420:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_WBLK, (cfg->resolutionX+15)>>4);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_HBLK, (cfg->resolutionY+15)>>4);
            break;
        case MJDEC_YUV400:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_WBLK, (cfg->resolutionX+7)>>3);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_FRAME_HBLK, (cfg->resolutionY+7)>>3);
            break;
        default:
            break;
    }
    BL_WR_REG(MJDEC_BASE,MJDEC_JDEC_FRAME_SIZE, tmpVal);

    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_HEADER_SKIP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_HDER_SKIP, cfg->headSkip);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_HDER_SKIP_BYTE, cfg->headByte);
    BL_WR_REG(MJDEC_BASE,MJDEC_JDEC_HEADER_SKIP, tmpVal);

    /* Clear interrupt */
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_INT_CLR, 0x1);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(MJDEC_IRQn, MJDEC_IRQHandler);
#endif
}

/****************************************************************************//**
 * @brief  Deinit mjdec module
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_Deinit(void)
{
    GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_MJPEG_DEC);
}

/****************************************************************************//**
 * @brief  Enable mjdec module
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_Enable(void)
{
    uint32_t tmpVal;

    /* Enable mjdec module */
    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_MJ_DEC_ENABLE);
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);
}

/****************************************************************************//**
 * @brief  Disable mjdec module
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_Disable(void)
{
    uint32_t tmpVal;

    /* Disable mjdec module */
    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MJDEC_REG_MJ_DEC_ENABLE);
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get one mjdec frame
 *
 * @param  info: Mjdec frame infomation pointer
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_Get_Frame_Info(MJDEC_Frame_Info *info)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_3);
    info->validFrames = BL_GET_REG_BITS_VAL(tmpVal, MJDEC_FRAME_VALID_CNT);
    info->curFrameAddr = BL_RD_REG(MJDEC_BASE, MJDEC_JP_ADDR0);
}

/****************************************************************************//**
 * @brief  Get available count of frames
 *
 * @param  None
 *
 * @return Frames count
 *
*******************************************************************************/
uint8_t MJDEC_Get_Frame_Count(void)
{
    return (uint8_t)BL_GET_REG_BITS_VAL(BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_3), MJDEC_FRAME_VALID_CNT);
}

/****************************************************************************/ /**
 * @brief  Push one jpeg picture frame
 *
 * @param  bufferMjpeg: jpeg picture frame buffer pointer
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type MJDEC_Push_Frame(uint32_t bufferJpeg)
{
    /* because of AXI 64bits, bufferJpeg address bit [0:2] must be 0 */
    if((bufferJpeg & 0x07) != 0)
    {
        return INVALID;
    }
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_FRAM_PUSH, bufferJpeg | 0x1);
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Pop one mjdec frame
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_Pop_Frame(void)
{
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_INT_CLR, 1 << 1);
}

/****************************************************************************//**
 * @brief  Set frame threshold to issue normal interrupt
 *
 * @param  count: Frame threshold
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_Set_Frame_Threshold(uint8_t count)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MJDEC_REG_FRAME_CNT_TRGR_INT,count);
    BL_WR_REG(MJDEC_BASE,MJDEC_JDEC_CONTROL_3,tmpVal);
}

/****************************************************************************//**
 * @brief  Set Q value
 *
 * @param  q: Q value, must be in 1-75 or 100
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_Set_Q_Value(uint8_t q)
{
    uint32_t tmpVal;

    if(q < 1) {
        q = 1;
    } else if(q > 75) {
        q = 100;
    }
    tmpVal = BL_RD_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MJDEC_REG_Q_MODE, q);
    BL_WR_REG(MJDEC_BASE, MJDEC_JDEC_CONTROL_1, tmpVal);
}

/****************************************************************************//**
 * @brief  MJDEC Enable Disable Interrupt
 *
 * @param  intType: MJDEC Interrupt Type
 * @param  intMask: Enable or Disable
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_IntMask(MJDEC_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_MJDEC_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(MJDEC_BASE,MJDEC_JDEC_CONTROL_3);
    switch(intType)
    {
        case MJDEC_INT_NORMAL:
            if(intMask == UNMASK){
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal,MJDEC_REG_INT_NORMAL_EN);
            }else{
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal,MJDEC_REG_INT_NORMAL_EN);
            }
            break;

        case MJDEC_INT_BACK_IDLE:
            if(intMask == UNMASK){
                /* Enable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal,MJDEC_REG_INT_IDLE_EN);
            }else{
                /* Disable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal,MJDEC_REG_INT_IDLE_EN);
            }
            break;

        case MJDEC_INT_ALL:
            if(intMask == UNMASK){
                /* Enable all interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, MJDEC_REG_INT_NORMAL_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal,MJDEC_REG_INT_IDLE_EN);
            }else{
                /* Disable all interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, MJDEC_REG_INT_NORMAL_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal,MJDEC_REG_INT_IDLE_EN);
            }
            break;

        default:
            break;
    }
    BL_WR_REG(MJDEC_BASE,MJDEC_JDEC_CONTROL_3,tmpVal);
}

/****************************************************************************//**
 * @brief  MJDEC Interrupt Clear
 *
 * @param  intType: MJDEC Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void MJDEC_IntClr(MJDEC_INT_Type intType)
{
    uint32_t tmpVal;
    
    CHECK_PARAM(IS_MJDEC_INT_TYPE(intType));
    
    tmpVal = BL_RD_REG(MJDEC_BASE,MJDEC_JDEC_INT_CLR);
    switch(intType)
    {
        case MJDEC_INT_NORMAL:
            tmpVal = BL_SET_REG_BIT(tmpVal,MJDEC_REG_INT_CLR);
            break;
        case MJDEC_INT_BACK_IDLE:
            tmpVal = BL_SET_REG_BIT(tmpVal,MJDEC_REG_INT_CLR);
            break;
        case MJDEC_INT_ALL:
            tmpVal = 0x1;
        default:
            break;
    }
    BL_WR_REG(MJDEC_BASE,MJDEC_JDEC_INT_CLR,tmpVal);
}

/****************************************************************************//**
 * @brief  Install mjdec interrupt callback function
 *
 * @param  intType: MJDEC interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void MJDEC_Int_Callback_Install(MJDEC_INT_Type intType,intCallback_Type* cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_MJDEC_INT_TYPE(intType));

    mjdecIntCbfArra[intType] = cbFun;
}
#endif

/****************************************************************************//**
 * @brief  Mjdec interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void MJDEC_IRQHandler(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(MJDEC_BASE,MJDEC_JDEC_CONTROL_3);
    BL_WR_REG(MJDEC_BASE,MJDEC_JDEC_INT_CLR, 0x1);
    if( BL_IS_REG_BIT_SET(tmpVal, MJDEC_STS_NORMAL_INT) ){
        // BL_WR_REG(MJDEC_BASE,MJDEC_JDEC_INT_CLR, 0x1);
        if(mjdecIntCbfArra[MJDEC_INT_NORMAL] != NULL) {
            /* call the callback function */
            mjdecIntCbfArra[MJDEC_INT_NORMAL]();
        }
    }
    if( BL_IS_REG_BIT_SET(tmpVal, MJDEC_STS_IDLE_INT) ){
        // BL_WR_REG(MJDEC_BASE,MJDEC_JDEC_INT_CLR, 0x1);
        if(mjdecIntCbfArra[MJDEC_INT_BACK_IDLE] != NULL) {
            /* call the callback function */
            mjdecIntCbfArra[MJDEC_INT_BACK_IDLE]();
        }
    }
}
#endif


/*@} end of group MJDEC_Public_Functions */

/*@} end of group MJDEC */

/*@} end of group BL808_Peripheral_Driver */
