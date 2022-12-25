/**
  ******************************************************************************
  * @file    bl808_dsi.c
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

#include "bl808_dsi.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSI
 *  @{
 */

/** @defgroup  DSI_Private_Macros
 *  @{
 */
#define DSI_TX_TIMEOUT_COUNT (320 * 1000)

/*@} end of group DSI_Private_Macros */

/** @defgroup  DSI_Private_Types
 *  @{
 */

/*@} end of group DSI_Private_Types */

/** @defgroup  DSI_Private_Variables
 *  @{
 */

static const uint32_t dsiAddr[DSI_ID_MAX] = { DSI_BASE };

/**
 *  @brief DSI interrupt callback function address array
*/
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *DSIIntCbfArra[DSI_ID_MAX][DSI_INT_COUNT] = {
    { NULL, NULL, NULL }
};
#endif
/*@} end of group DSI_Private_Variables */

/** @defgroup  DSI_Global_Variables
 *  @{
 */

/*@} end of group DSI_Global_Variables */

/** @defgroup  DSI_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type DSI_IntHandler(DSI_ID_Type dsiId);
#endif

/*@} end of group DSI_Private_Fun_Declaration */

/** @defgroup  DSI_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  DSI interrupt handle
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type DSI_IntHandler(DSI_ID_Type dsiId)
{
    uint32_t maskVal;
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(dsiId));

    maskVal = BL_RD_REG(DSIx, DSI_INT_MASK);
    tmpVal = BL_RD_REG(DSIx, DSI_INT_STATUS);

    if (tmpVal & DSI_INT_ESCAPE_TX_END && !(maskVal & DSI_INT_ESCAPE_TX_END)) {
        DSI_IntClear(dsiId, DSI_INT_ESCAPE_TX_END);

        if (DSIIntCbfArra[dsiId][0] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][0]();
        }
    }

    if (tmpVal & DSI_INT_LPDT_RX_END && !(maskVal & DSI_INT_LPDT_RX_END)) {
        DSI_IntClear(dsiId, DSI_INT_LPDT_RX_END);

        if (DSIIntCbfArra[dsiId][1] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][1]();
        }
    }

    if (tmpVal & DSI_INT_ULPS_RX_END && !(maskVal & DSI_INT_ULPS_RX_END)) {
        DSI_IntClear(dsiId, DSI_INT_ULPS_RX_END);

        if (DSIIntCbfArra[dsiId][2] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][2]();
        }
    }

    if (tmpVal & DSI_INT_TRIGGER0_RX_END && !(maskVal & DSI_INT_TRIGGER0_RX_END)) {
        DSI_IntClear(dsiId, DSI_INT_TRIGGER0_RX_END);

        if (DSIIntCbfArra[dsiId][3] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][3]();
        }
    }

    if (tmpVal & DSI_INT_TRIGGER1_RX_END && !(maskVal & DSI_INT_TRIGGER1_RX_END)) {
        DSI_IntClear(dsiId, DSI_INT_TRIGGER1_RX_END);

        if (DSIIntCbfArra[dsiId][4] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][4]();
        }
    }

    if (tmpVal & DSI_INT_TRIGGER2_RX_END && !(maskVal & DSI_INT_TRIGGER2_RX_END)) {
        DSI_IntClear(dsiId, DSI_INT_TRIGGER2_RX_END);

        if (DSIIntCbfArra[dsiId][5] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][5]();
        }
    }

    if (tmpVal & DSI_INT_TRIGGER3_RX_END && !(maskVal & DSI_INT_TRIGGER3_RX_END)) {
        DSI_IntClear(dsiId, DSI_INT_TRIGGER3_RX_END);

        if (DSIIntCbfArra[dsiId][6] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][6]();
        }
    }

    if (tmpVal & DSI_INT_TX_FIFO_READY && !(maskVal & DSI_INT_TX_FIFO_READY)) {
        DSI_IntClear(dsiId, DSI_INT_TX_FIFO_READY);

        if (DSIIntCbfArra[dsiId][7] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][7]();
        }
    }

    if (tmpVal & DSI_INT_RX_FIFO_READY && !(maskVal & DSI_INT_RX_FIFO_READY)) {
        DSI_IntClear(dsiId, DSI_INT_RX_FIFO_READY);

        if (DSIIntCbfArra[dsiId][8] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][8]();
        }
    }

    if (tmpVal & DSI_INT_DATA_OVERRUN_ERR && !(maskVal & DSI_INT_DATA_OVERRUN_ERR)) {
        DSI_IntClear(dsiId, DSI_INT_DATA_OVERRUN_ERR);

        if (DSIIntCbfArra[dsiId][9] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][9]();
        }
    }

    if (tmpVal & DSI_INT_DATA_UNDERRUN_ERR && !(maskVal & DSI_INT_DATA_UNDERRUN_ERR)) {
        DSI_IntClear(dsiId, DSI_INT_DATA_UNDERRUN_ERR);

        if (DSIIntCbfArra[dsiId][10] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][10]();
        }
    }

    if (tmpVal & DSI_INT_PIXEL_COUNT_SMALL_ERR && !(maskVal & DSI_INT_PIXEL_COUNT_SMALL_ERR)) {
        DSI_IntClear(dsiId, DSI_INT_PIXEL_COUNT_SMALL_ERR);

        if (DSIIntCbfArra[dsiId][11] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][11]();
        }
    }

    if (tmpVal & DSI_INT_PIXEL_COUNT_LARGE_ERR && !(maskVal & DSI_INT_PIXEL_COUNT_LARGE_ERR)) {
        DSI_IntClear(dsiId, DSI_INT_PIXEL_COUNT_LARGE_ERR);

        if (DSIIntCbfArra[dsiId][12] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][12]();
        }
    }

    if (tmpVal & DSI_INT_FIFO_ERROR && !(maskVal & DSI_INT_FIFO_ERROR)) {
        DSI_IntClear(dsiId, DSI_INT_FIFO_ERROR);

        if (DSIIntCbfArra[dsiId][13] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][13]();
        }
    }

    return SUCCESS;
}
#endif

/*@} end of group DSI_Private_Functions */

/** @defgroup  DSI_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  DSI module init
 *
 * @param  dsiId: DSI ID type
 * @param  cfg: DSI configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSI_Init(DSI_ID_Type dsiId, DSI_CFG_Type *cfg)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    DSI_Lane_Type lanes=0;

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_DATA_TYPE(cfg->dataType));
    CHECK_PARAM(IS_DSI_LANE_NUMBER_TYPE(cfg->laneNum));
    CHECK_PARAM(IS_DSI_LANE_ORDER_TYPE(cfg->laneOrder));
    CHECK_PARAM(IS_DSI_HS_SYNC_TYPE(cfg->syncType));

    /* Set DSI configuration */
    tmpVal = BL_RD_REG(DSIx, DSI_CONFIG);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LANE_NUM, cfg->laneNum);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_HSTX_MODE, cfg->syncType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LANE_MUX_SEL, cfg->laneOrder);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_DT, cfg->dataType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_VC, cfg->virtualChan);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_HSTX_VFP, cfg->vfp);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_HSTX_VSA, cfg->vsa);

    BL_WR_REG(DSIx, DSI_CONFIG, tmpVal);

    if(cfg->laneNum == DSI_LANE_NUMBER_1){
        lanes=DSI_LANE_CLOCK|DSI_LANE_DATA0;
    }else if(cfg->laneNum == DSI_LANE_NUMBER_2){
        lanes=DSI_LANE_CLOCK|DSI_LANE_DATA0|DSI_LANE_DATA1;
    }else if(cfg->laneNum == DSI_LANE_NUMBER_4){
        lanes=DSI_LANE_CLOCK|DSI_LANE_DATA0|DSI_LANE_DATA1|DSI_LANE_DATA2|DSI_LANE_DATA3;
    }

    DSI_PHY_Enable_Lanes(dsiId,lanes);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(MIPI_DSI_IRQn, DSI_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  Deinit DSI module
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_Deinit(DSI_ID_Type dsiId)
{
}

/****************************************************************************/ /**
 * @brief  DSI Enable Disable Interrupt
 *
 * @param  dsiId: DSI ID type
 * @param  intType: DSI Interrupt Type
 * @param  intMask: mask or unmask
 *
 * @return None
 *
*******************************************************************************/
void DSI_IntMask(DSI_ID_Type dsiId, DSI_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(DSIx, DSI_INT_MASK);

    if (intMask == UNMASK) {
        /* Unmask this interrupt */
        tmpVal &= (~intType);

    } else {
        /* Mask this interrupt */
        tmpVal |= intType;
    }

    BL_WR_REG(DSIx, DSI_INT_MASK, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI Clear Interrupt
 *
 * @param  dsiId: DSI ID type
 * @param  intType: DSI Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void DSI_IntClear(DSI_ID_Type dsiId, DSI_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_INT_TYPE(intType));

    tmpVal = BL_RD_REG(DSIx, DSI_INT_CLEAR);

    /* Clear this interrupt */
    tmpVal |= intType;

    BL_WR_REG(DSIx, DSI_INT_CLEAR, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI Enable Interrupt
 *
 * @param  dsiId: DSI ID type
 * @param  intType: DSI Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void DSI_IntEnable(DSI_ID_Type dsiId, DSI_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_INT_TYPE(intType));

    tmpVal = BL_RD_REG(DSIx, DSI_INT_ENABLE);

    /* Enable this interrupt */
    tmpVal |= intType;

    BL_WR_REG(DSIx, DSI_INT_ENABLE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI Get Interrupt status
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
DSI_INT_Type DSI_IntGet(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal = BL_RD_REG(DSIx, DSI_INT_STATUS);

    return BL_GET_REG_BITS_VAL(tmpVal, DSI_INT_STATUS);
}

/****************************************************************************/ /**
 * @brief  DSI set line buffer threshold for controller to start transmitting each line(unit:pixel)
 *
 * @param  dsiId: DSI ID type
 * @param  frameWidth: frame width
 * @param  dvpTsrcClock: display(dp_dvp_tsrc) clock rate
 * @param  dsiClock: DSI bit clock rate
 * @param  dataType: DSI data type
 * @param  laneNumber: DSI lane number
 *
 * @return None
 *
*******************************************************************************/
void DSI_Set_Line_Buffer_Threshold(DSI_ID_Type dsiId, uint32_t frameWidth, uint32_t dvpTsrcClock, uint32_t dsiClock, \
                                   DSI_Data_Type dataType, DSI_Lane_Number_Type laneNumber)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    int64_t threshold = dvpTsrcClock;
    uint32_t pixelByte;

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_DATA_TYPE(dataType));
    CHECK_PARAM(IS_DSI_LANE_NUMBER_TYPE(laneNumber));

    /* Frame Width should not exceed 1280 and should be a multiple of 4 */
    if(frameWidth > 1280 || frameWidth % 4){
        return;
    }

    if(dataType < DSI_DATA_RGB666){
        pixelByte = 2;
    }else{
        pixelByte = 3;
    }

    threshold = frameWidth - threshold*frameWidth*pixelByte/(dsiClock/8)/(1<<laneNumber);

    if(threshold < 6){
        threshold = 6;
    }
    tmpVal = BL_RD_REG(DSIx, DSI_HSTX_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_HSTX_PC, frameWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_HSTX_OUT_TH, threshold);
    BL_WR_REG(DSIx, DSI_HSTX_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI set VSA and VFP
 *
 * @param  dsiId: DSI ID type
 * @param  vsa: Vertical sync active
 * @param  vfp: Vertical front porch
 *
 * @return None
 *
*******************************************************************************/
void DSI_Set_VSA_VFP(DSI_ID_Type dsiId, uint8_t vsa, uint8_t vfp)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    
    tmpVal = BL_RD_REG(DSIx, DSI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_HSTX_VFP, vfp);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_HSTX_VSA, vsa);
    BL_WR_REG(DSIx, DSI_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI Reinit data lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Reset(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);

    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_RESET_N);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);

    tmpVal = BL_SET_REG_BIT(tmpVal, DSI_RESET_N);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI Config DPHY
 *
 * @param  dsiId: DSI ID type
 *
 * @param  phyCfg: DPHY config
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Config(DSI_ID_Type dsiId, DSI_DPhy_CFG_Type *phyCfg)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_CK_ZERO, phyCfg->time_clk_zero);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_CK_TRAIL, phyCfg->time_clk_trail);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_CK_EXIT, phyCfg->time_clk_exit);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_1, tmpVal);

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_HS_ZERO, phyCfg->time_data_zero);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_HS_TRAIL, phyCfg->time_data_trail);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_HS_EXIT, phyCfg->time_data_exit);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_HS_PREP, phyCfg->time_data_prepare);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_2, tmpVal);

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_TA_GO, phyCfg->time_ta_go);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_TA_GET, phyCfg->time_ta_get);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_REQRDY, phyCfg->time_req_ready);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_LPX, phyCfg->time_lpx);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_3, tmpVal);

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_REG_TIME_WAKEUP, phyCfg->time_wakeup);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_4, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI Reinit data lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Reinit_Data_Lanes(DSI_ID_Type dsiId, DSI_Lane_Type lanes)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_LANE_TYPE(lanes));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);

    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL0_FORCERXMODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL1_FORCERXMODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL2_FORCERXMODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL3_FORCERXMODE);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);

    if (lanes & DSI_LANE_DATA0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL0_FORCERXMODE);
    }

    if (lanes & DSI_LANE_DATA1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL1_FORCERXMODE);
    }

    if (lanes & DSI_LANE_DATA2) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL2_FORCERXMODE);
    }

    if (lanes & DSI_LANE_DATA3) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL3_FORCERXMODE);
    }

    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI enable lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Enable_Lanes(DSI_ID_Type dsiId, DSI_Lane_Type lanes)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_LANE_TYPE(lanes));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);

    if (lanes & DSI_LANE_DATA0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL0_ENABLE);
    }

    if (lanes & DSI_LANE_DATA1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL1_ENABLE);
    }

    if (lanes & DSI_LANE_DATA2) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL2_ENABLE);
    }

    if (lanes & DSI_LANE_DATA3) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL3_ENABLE);
    }

    if (lanes & DSI_LANE_CLOCK) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CL_ENABLE);
    }

    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI disable lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Disable_Lanes(DSI_ID_Type dsiId, DSI_Lane_Type lanes)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_LANE_TYPE(lanes));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);

    if (lanes & DSI_LANE_DATA0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL0_ENABLE);
    }

    if (lanes & DSI_LANE_DATA1) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL1_ENABLE);
    }

    if (lanes & DSI_LANE_DATA2) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL2_ENABLE);
    }

    if (lanes & DSI_LANE_DATA3) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL3_ENABLE);
    }

    if (lanes & DSI_LANE_CLOCK) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_CL_ENABLE);
    }

    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI stop data lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Stop_Data_Lanes(DSI_ID_Type dsiId, DSI_Lane_Type lanes)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_LANE_TYPE(lanes));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);

    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL0_FORCETXSTOPMODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL1_FORCETXSTOPMODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL2_FORCETXSTOPMODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DL3_FORCETXSTOPMODE);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);

    if (lanes & DSI_LANE_DATA0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL0_FORCETXSTOPMODE);
    }

    if (lanes & DSI_LANE_DATA1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL1_FORCETXSTOPMODE);
    }

    if (lanes & DSI_LANE_DATA2) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL2_FORCETXSTOPMODE);
    }

    if (lanes & DSI_LANE_DATA3) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL3_FORCETXSTOPMODE);
    }

    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI stop data lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Data_Lane0_TurnAround(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DL0_TURNESC);
    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DSI get lanes state
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Get_Lanes_State(DSI_ID_Type dsiId, DSI_Lane_Type lane, DSI_Lane_State_Type *state)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    uint32_t stop_state_pos = 0;
    uint32_t ulp_state_pos = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_LANE_TYPE(lanes));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);

    *state = DSI_LANE_STAT_NORMAL;

    if (lane == DSI_LANE_DATA0) {
        stop_state_pos = DSI_DL0_STOPSTATE_POS;
        ulp_state_pos = DSI_DL0_ULPSACTIVENOT_POS;
    } else if (lane == DSI_LANE_DATA1) {
        stop_state_pos = DSI_DL1_STOPSTATE_POS;
        ulp_state_pos = DSI_DL1_ULPSACTIVENOT_POS;
    } else if (lane == DSI_LANE_DATA2) {
        stop_state_pos = DSI_DL2_STOPSTATE_POS;
        ulp_state_pos = DSI_DL2_ULPSACTIVENOT_POS;
    } else if (lane == DSI_LANE_DATA3) {
        stop_state_pos = DSI_DL3_STOPSTATE_POS;
        ulp_state_pos = DSI_DL3_ULPSACTIVENOT_POS;
    } else if (lane == DSI_LANE_CLOCK) {
        stop_state_pos = DSI_CL_STOPSTATE_POS;
        ulp_state_pos = DSI_CL_ULPSACTIVENOT_POS;
    } else {
        return;
    }

    if(!(tmpVal & (1 << ulp_state_pos))) {
        *state = DSI_LANE_STAT_ULP;
    } else if(tmpVal & (1 << stop_state_pos)) {
        *state = DSI_LANE_STAT_STOP;
    } else {
        if(lane == DSI_LANE_CLOCK) {
            if(tmpVal & (1 << DSI_CL_TXREQUESTHS_POS)) {
                *state = DSI_LANE_STAT_HS;
            } else {
                *state = DSI_LANE_STAT_BRIDGE;
            }
        } else {
            if(BL_RD_REG(DSIx, DSI_CONFIG) & (1 << DSI_CR_HSTX_EN_POS)) {
                *state = DSI_LANE_STAT_HS;
            } else {
                *state = DSI_LANE_STAT_BRIDGE;
            }
        }
    }
}

/****************************************************************************/ /**
 * @brief  Set clock lane operation
 *
 * @param  dsiId: DSI ID type
 *
 * @param  opt: operation type
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Set_Clock_Lane(DSI_ID_Type dsiId, DSI_Clock_Lane_Opt_Type opt)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_CLOCK_LANE_OPT_TYPE(opt));

    tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);

    if (opt & DSI_CLOCK_LANE_OPT_ULP_ENTER) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CL_TXULPSCLK);
    }

    if (opt & DSI_CLOCK_LANE_OPT_ULP_EXIT) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CL_TXULPSEXIT);
        BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);
        arch_delay_ms(1);
        tmpVal = BL_RD_REG(DSIx, DSI_DPHY_CONFIG_0);
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_CL_TXULPSCLK);
    }

    if (opt & DSI_CLOCK_LANE_OPT_HS_REQ) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CL_TXREQUESTHS);
    }
    
    if (opt & DSI_CLOCK_LANE_OPT_HS_EXIT) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_CL_TXREQUESTHS);
    }

    BL_WR_REG(DSIx, DSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Start HS Mode
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_HS_Mode_Start(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    DSI_Lane_State_Type state = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    /* bring clock lane to high speed */
    DSI_PHY_Get_Lanes_State(dsiId, DSI_LANE_CLOCK, &state);
    if(state == DSI_LANE_STAT_STOP){
        DSI_PHY_Set_Clock_Lane(dsiId, DSI_CLOCK_LANE_OPT_HS_REQ);
    }

    /* bring data lane to high speed */
    DSI_PHY_Get_Lanes_State(dsiId, DSI_LANE_DATA0, &state);
    if(state == DSI_LANE_STAT_STOP){
        tmpVal = BL_RD_REG(DSIx, DSI_CONFIG);
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CR_HSTX_EN);
        BL_WR_REG(DSIx, DSI_CONFIG, tmpVal);
    }

}

/****************************************************************************/ /**
 * @brief  Stop HS Mode
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_HS_Mode_Stop(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    DSI_Lane_State_Type state = 0;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    /* set data lane to stop mode */
    DSI_PHY_Get_Lanes_State(dsiId, DSI_LANE_DATA0, &state);
    if(state != DSI_LANE_STAT_STOP){
        tmpVal = BL_RD_REG(DSIx, DSI_CONFIG);
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_CR_HSTX_EN);
        BL_WR_REG(DSIx, DSI_CONFIG, tmpVal);
        do{
            DSI_PHY_Get_Lanes_State(dsiId, DSI_LANE_DATA0, &state);
        }while(state != DSI_LANE_STAT_STOP);
    }

    /* set clock lane to stop mode */
    DSI_PHY_Get_Lanes_State(dsiId, DSI_LANE_CLOCK, &state);
    if(state != DSI_LANE_STAT_STOP){
        DSI_PHY_Set_Clock_Lane(dsiId, DSI_CLOCK_LANE_OPT_HS_EXIT);
        do{
            DSI_PHY_Get_Lanes_State(dsiId, DSI_LANE_CLOCK, &state);
        }while(state != DSI_LANE_STAT_STOP);
    }

}

/****************************************************************************/ /**
 * @brief  DSI configure fifo function
 *
 * @param  dsiId: DSI ID type
 *
 * @param  fifoCfg: FIFO configuration structure pointer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_FifoConfig(DSI_ID_Type dsiId, DSI_FifoCfg_Type *fifoCfg)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    /* Deal with DSI fifo configure register */
    tmpVal = BL_RD_REG(DSIx, DSI_FIFO_CONFIG_1);
    /* Configure dma tx fifo threshold */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_TX_FIFO_TH, fifoCfg->txFifoDmaThreshold);
    /* Configure dma rx fifo threshold */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_RX_FIFO_TH, fifoCfg->rxFifoDmaThreshold);
    /* Write back */
    BL_WR_REG(DSIx, DSI_FIFO_CONFIG_1, tmpVal);

    /* Enable or disable DSI fifo dma function */
    tmpVal = BL_RD_REG(DSIx, DSI_FIFO_CONFIG_0);

    if (ENABLE == fifoCfg->txFifoDmaEnable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DMA_TX_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DMA_TX_EN);
    }

    if (ENABLE == fifoCfg->rxFifoDmaEnable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSI_DMA_RX_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_DMA_RX_EN);
    }

    BL_WR_REG(DSIx, DSI_FIFO_CONFIG_0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSI start tx for short and long packet
 *
 * @param  dsiId: DSI ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_LPDT_Start_Tx(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_CR_ESC_RX_EN);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CR_ESC_TX_EN);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  DSI wait for send done
 * 
 * @param  dsiId: DSI ID type
 * 
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_Wait_For_Esc_Tx_Done(DSI_ID_Type dsiId)
{        
    DSI_INT_Type intStatus;

    /* wait for Tx finished */
    do{
        intStatus=DSI_IntGet(dsiId);
    }while(!(intStatus&DSI_INT_ESCAPE_TX_END));
    DSI_IntClear(dsiId,DSI_INT_ESCAPE_TX_END);

    return SUCCESS;
}
/****************************************************************************/ /**
 * @brief  DSI start rx for short and long packet
 *
 * @param  dsiId: DSI ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_LPDT_Start_Rx(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSI_CR_ESC_RX_EN);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CR_ESC_RX_EN);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSI Get Rx length
 *
 * @param  dsiId: DSI ID type
 *
 * @return RX length
 *
*******************************************************************************/
uint16_t DSI_LPDT_Get_Rx_Length(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    return BL_GET_REG_BITS_VAL(tmpVal, DSI_ST_ESC_RX_LEN);
}

/****************************************************************************/ /**
 * @brief  DSI Escape mode send trigger command
 *
 * @param  dsiId: DSI ID type
 *
 * @param  cmd: trigger command
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_Send_Trigger_Command(DSI_ID_Type dsiId, uint8_t cmd)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    DSI_PHY_HS_Mode_Stop(dsiId);

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_ESC_TX_MODE, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_ESC_TX_TRIG, cmd);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CR_ESC_TX_EN);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    return DSI_Wait_For_Esc_Tx_Done(dsiId);
}

/****************************************************************************/ /**
 * @brief  DSI Escape mode send ULPS command
 *
 * @param  dsiId: DSI ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_Send_ULPS_Command(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    DSI_PHY_HS_Mode_Stop(dsiId);

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_ESC_TX_MODE, 2);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CR_ESC_TX_EN);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    return DSI_Wait_For_Esc_Tx_Done(dsiId);
}

/****************************************************************************/ /**
 * @brief  DSI exit ULPS
 *
 * @param  dsiId: DSI ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_Exit_ULPS(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    //DSI_Lane_State_Type state;

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_ESC_TX_ULPS_EXIT, 1);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    arch_delay_ms(2);
#if 0
    DSI_PHY_HS_Mode_Stop(dsiId);

    do
    {
        DSI_PHY_Get_Lanes_State(dsiId, DSI_LANE_DATA0, &state);
    } while(state != DSI_LANE_STAT_STOP);

#endif
    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_ESC_TX_MODE, 3);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSI_CR_ESC_TX_EN);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    return DSI_Wait_For_Esc_Tx_Done(dsiId);
}

/****************************************************************************/ /**
 * @brief  DSI config LPDT short packet
 *
 * @param  dsiId: DSI ID type
 *
 * @param  msg: LPDT long message config
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_LPDT_Config_Short_Packet(DSI_ID_Type dsiId, DSI_LPDT_MSG_Type *msg)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    DSI_PHY_HS_Mode_Stop(dsiId);

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_ESC_TX_MODE, 0);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    /*short packet*/
    tmpVal = BL_RD_REG(DSIx, DSI_LPDT_TX_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_PDLEN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_VC, msg->virtualChan);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_DI, msg->dataType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_WORD0, msg->tx_buf[0]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_WORD1, msg->tx_buf[1]);
    BL_WR_REG(DSIx, DSI_LPDT_TX_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSI send LPDT short packet
 *
 * @param  dsiId: DSI ID type
 *
 * @param  msg: DSI message config
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_LPDT_Send_Short_Packet(DSI_ID_Type dsiId, DSI_LPDT_MSG_Type *msg)
{
    DSI_LPDT_Config_Short_Packet(dsiId, msg);

    DSI_LPDT_Start_Tx(dsiId);

    return DSI_Wait_For_Esc_Tx_Done(dsiId);
}

/****************************************************************************/ /**
 * @brief  DSI config LPDT long packet
 *
 * @param  dsiId: DSI ID type
 *
 * @param  msg: LPDT long message config
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_LPDT_Config_Long_Packet(DSI_ID_Type dsiId, DSI_LPDT_MSG_Type *msg)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    DSI_PHY_HS_Mode_Stop(dsiId);

    tmpVal = BL_RD_REG(DSIx, DSI_ESC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_ESC_TX_MODE, 0);
    BL_WR_REG(DSIx, DSI_ESC_CONFIG, tmpVal);

    /*long  packet*/
    tmpVal = BL_RD_REG(DSIx, DSI_LPDT_TX_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_VC, msg->virtualChan);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_DI, msg->dataType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_WORD0, msg->tx_len & 0xff);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_WORD1, (msg->tx_len >> 8) & 0xff);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSI_CR_LPDT_PDLEN, msg->tx_len);
    BL_WR_REG(DSIx, DSI_LPDT_TX_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSI get tx fifo unoccupied count value
 *
 * @param  dsiId: DSI ID type
 *
 * @return Tx fifo unoccupied count value
 *
*******************************************************************************/
uint8_t DSI_GetTxFifoCount(DSI_ID_Type dsiId)
{
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameter */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(DSIx, DSI_FIFO_CONFIG_1), DSI_TX_FIFO_CNT);
}

/****************************************************************************/ /**
 * @brief  DSI get rx fifo count value
 *
 * @param  dsiId: DSI ID type
 *
 * @return Rx fifo count value
 *
*******************************************************************************/
uint8_t DSI_GetRxFifoCount(DSI_ID_Type dsiId)
{
    uint32_t DSIx = dsiAddr[dsiId];

    /* Check the parameter */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(DSIx, DSI_FIFO_CONFIG_1), DSI_RX_FIFO_CNT);
}

/****************************************************************************/ /**
 * @brief  DSI full fill FIFO
 *
 * @param  dsiId: DSI ID type
 *
 * @param  data: Data to send buffer
 *
 * @param  len: Data length to send
 *
 * @return Data length filled
 *
*******************************************************************************/
uint8_t DSI_Full_Fill_FIFO(DSI_ID_Type dsiId, const uint8_t *data, uint16_t len)
{
    uint32_t DSIx = dsiAddr[dsiId];
    const uint8_t *pDataEnd = data + len;
    uint8_t filled = 0;

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Send data */
    while (data < pDataEnd) {
        if (DSI_GetTxFifoCount(dsiId) > 0) {
            BL_WR_WORD(DSIx + DSI_FIFO_WDATA_OFFSET, BL_RDWD_FRM_BYTEP(data));
            data += 4;
            filled += 4;
        } else {
            return filled;
        }
    }

    return filled;
}

/****************************************************************************/ /**
 * @brief  DSI feed FIFO with data
 *
 * @param  dsiId: DSI ID type
 *
 * @param  data: Data to send buffer
 *
 * @param  len: Data length to send
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_Feed_FIFO(DSI_ID_Type dsiId, const uint8_t *data, uint16_t len)
{
    uint32_t timeoutCnt = DSI_TX_TIMEOUT_COUNT;
    uint32_t DSIx = dsiAddr[dsiId];
    const uint8_t *pDataEnd = data + len;

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Send data */
    while (data < pDataEnd) {
        if (DSI_GetTxFifoCount(dsiId) > 0) {
            BL_WR_WORD(DSIx + DSI_FIFO_WDATA_OFFSET, BL_RDWD_FRM_BYTEP(data));
            timeoutCnt = DSI_TX_TIMEOUT_COUNT;
            data += 4;
        } else {
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSI Read FIFO
 *
 * @param  dsiId: DSI ID type
 *
 * @param  data: Data to receive buffer
 *
 * @param  len: Data length to receive
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_Read_FIFO(DSI_ID_Type dsiId, uint8_t *data, uint16_t len)
{
    uint32_t DSIx = dsiAddr[dsiId];
    uint8_t *pDataEnd = data + len;

    /* Check the parameter */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));

    /* Receive data */
    while (data < pDataEnd && DSI_GetRxFifoCount(dsiId) > 0) {
        BL_WRWD_TO_BYTEP(data, BL_RD_WORD(DSIx + DSI_FIFO_RDATA_OFFSET));
        data += 4;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSI send LPDT long packet
 *
 * @param  dsiId: DSI ID type
 *
 * @param  msg: DSI message config
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_LPDT_Send_Long_Packet(DSI_ID_Type dsiId, DSI_LPDT_MSG_Type *msg)
{
    uint8_t filled = 0;

    DSI_LPDT_Config_Long_Packet(dsiId, msg);

    filled = DSI_Full_Fill_FIFO(dsiId, msg->tx_buf, msg->tx_len);

    DSI_LPDT_Start_Tx(dsiId);

    if (filled < msg->tx_len) {
        DSI_Feed_FIFO(dsiId, msg->tx_buf + filled, msg->tx_len - filled);
    }

    return DSI_Wait_For_Esc_Tx_Done(dsiId);
}

/****************************************************************************/ /**
 * @brief  DSI receive packet
 *
 * @param  dsiId: DSI ID type
 *
 * @param  msg: DSI message config
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DSI_LPDT_Recv_Packet(DSI_ID_Type dsiId, DSI_LPDT_MSG_Type *msg)
{
    DSI_Lane_State_Type state;
    DSI_INT_Type intStatus;

    /* wait for bus stop */
    do {
        DSI_PHY_Get_Lanes_State(dsiId, DSI_LANE_DATA0, &state);
    } while (state != DSI_LANE_STAT_STOP);

    /* turn around */
    DSI_PHY_Data_Lane0_TurnAround(dsiId);

    /* start rx */
    DSI_LPDT_Start_Rx(dsiId);

    /* wait for rx finished */
    do {
        intStatus = DSI_IntGet(dsiId);
    } while (!(intStatus & DSI_INT_LPDT_RX_END));
    DSI_IntClear(dsiId,DSI_INT_LPDT_RX_END);

    msg->rx_len = DSI_LPDT_Get_Rx_Length(dsiId);

    DSI_Read_FIFO(dsiId, msg->rx_buf, msg->rx_len);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSI interrupt function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DSI_IRQHandler(void)
{
    DSI_IntHandler(DSI0_ID);
}
#endif

/*@} end of group DSI_Public_Functions */

/*@} end of group DSI */

/*@} end of group BL808_Peripheral_Driver */
