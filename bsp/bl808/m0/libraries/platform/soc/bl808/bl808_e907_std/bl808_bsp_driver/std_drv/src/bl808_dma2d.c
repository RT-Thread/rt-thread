/**
  ******************************************************************************
  * @file    bl808_dma2d.c
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
#include "bl808_dma2d.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DMA2D
 *  @{
 */

/** @defgroup  DMA2D_Private_Macros
 *  @{
 */
#define DMA2D_Get_Channel(id_base, ch) ((id_base) + (ch)*0x100)

/*@} end of group DMA2D_Private_Macros */

/** @defgroup  DMA2D_Private_Types
 *  @{
 */

/*@} end of group DMA2D_Private_Types */

/** @defgroup  DMA2D_Private_Variables
 *  @{
 */
static const uint32_t dma2dAddr[DMA2D_ID_MAX] = { DMA2D_BASE };
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *dma2dIntCbfArra[DMA2D_ID_MAX][DMA2D_CH_MAX][DMA2D_INT_ALL] = {
    { { NULL } }
};
#endif
static DMA2D_LLI_Ctrl_Type PingPongListArra[DMA2D_ID_MAX][DMA2D_CH_MAX][2];

/*@} end of group DMA2D_Private_Variables */

/** @defgroup  DMA2D_Global_Variables
 *  @{
 */

/*@} end of group DMA2D_Global_Variables */

/** @defgroup  DMA2D_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static void DMA2D_IntHandler(DMA2D_ID_Type dmaId);
#endif
static void CPU_Interrupt_Enable_DMA2D(DMA2D_ID_Type dmaId);
static void CPU_Interrupt_Disable_DMA2D(DMA2D_ID_Type dmaId);

/*@} end of group DMA2D_Private_Fun_Declaration */

/** @defgroup  DMA2D_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  DMA2D interrupt handler
 *
 * @param  dmaId: DMA2D ID type
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static void DMA2D_IntHandler(DMA2D_ID_Type dmaId)
{
    uint32_t tmpVal;
    uint8_t ch;
    /* Get DMA2D register */
    uint32_t DMA2DChs = dma2dAddr[dmaId];

    for (ch = 0; ch < DMA2D_CH_MAX; ch++) {
        tmpVal = BL_RD_REG(DMA2DChs, DMA2D_DMA_INTSTATUS);

        if ((BL_GET_REG_BITS_VAL(tmpVal, DMA2D_INTSTATUS) & (1 << ch)) != 0) {
            /* Clear interrupt */
            BL_WR_REG(DMA2DChs, DMA2D_DMA_INTTCCLEAR, 1 << ch);

            if (dma2dIntCbfArra[dmaId][ch][DMA2D_INT_TCOMPLETED] != NULL) {
                /* Call the callback function */
                dma2dIntCbfArra[dmaId][ch][DMA2D_INT_TCOMPLETED]();
            }
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  CPU enable DMA2D interrupt
 *
 * @param  dmaId: DMA2D ID type
 *
 * @return None
 *
*******************************************************************************/
static void CPU_Interrupt_Enable_DMA2D(DMA2D_ID_Type dmaId)
{
    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));

    CPU_Interrupt_Enable(DMA2D_INT0_IRQn);
    CPU_Interrupt_Enable(DMA2D_INT1_IRQn);
}

/****************************************************************************/ /**
 * @brief  CPU disable DMA2D interrupt
 *
 * @param  dmaId: DMA2D ID type
 *
 * @return None
 *
*******************************************************************************/
static void CPU_Interrupt_Disable_DMA2D(DMA2D_ID_Type dmaId)
{
    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));

    CPU_Interrupt_Disable(DMA2D_INT0_IRQn);
    CPU_Interrupt_Disable(DMA2D_INT1_IRQn);
}

/*@} end of group DMA2D_Private_Functions */

/** @defgroup  DMA2D_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  DMA2D enable
 *
 * @param  dmaId: DMA2D ID type
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Enable(DMA2D_ID_Type dmaId)
{
    uint32_t tmpVal;
    /* Get DMA2D register */
    uint32_t DMA2DChs = dma2dAddr[dmaId];

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_DMA_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, DMA2D_E);
    BL_WR_REG(DMA2DChs, DMA2D_DMA_CONFIG, tmpVal);
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(DMA2D_INT0_IRQn, DMA2D_INT0_IRQHandler);
    Interrupt_Handler_Register(DMA2D_INT1_IRQn, DMA2D_INT1_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  DMA2D disable
 *
 * @param  dmaId: DMA2D ID type
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Disable(DMA2D_ID_Type dmaId)
{
    uint32_t tmpVal;
    /* Get DMA2D register */
    uint32_t DMA2DChs = dma2dAddr[dmaId];

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_DMA_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DMA2D_E);
    BL_WR_REG(DMA2DChs, DMA2D_DMA_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DMA2D configure function
 *
 * @param  dmaId: DMA2D ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
void DMA2D_Init(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_Cfg_Type *cfg)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_CFG);
    BL_WR_REG(DMA2DChs, DMA2D_C0_CFG, BL_SET_REG_BIT(tmpVal, DMA2D_REG_DMA_2D_EN));

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_SRC_CNT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_SRC_X_CNT, cfg->srcCntX);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_SRC_Y_CNT, cfg->srcCntY);
    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_CNT, tmpVal);

    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_XIC, cfg->srcIncrX);
    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_YIC, cfg->srcIncrY);

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_DST_CNT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_DST_X_CNT, cfg->dstCntX);
    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_CNT, tmpVal);

    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_XIC, cfg->dstIncrX);
    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_YIC, cfg->dstIncrY);
}

/****************************************************************************/ /**
 * @brief  DMA2D channel init
 *
 * @param  dmaId: DMA2D ID type
 * @param  chCfg: DMA2D configuration
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Channel_Init(DMA2D_ID_Type dmaId, DMA2D_Channel_Cfg_Type *chCfg)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], chCfg->ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(chCfg->ch));
    CHECK_PARAM(IS_DMA2D_TRANS_WIDTH_TYPE(chCfg->srcTransfWidth));
    CHECK_PARAM(IS_DMA2D_TRANS_WIDTH_TYPE(chCfg->dstTransfWidth));
    CHECK_PARAM(IS_DMA2D_BURST_SIZE_TYPE(chCfg->srcBurstSize));
    CHECK_PARAM(IS_DMA2D_BURST_SIZE_TYPE(chCfg->dstBurstSize));
    CHECK_PARAM(IS_DMA2D_TRANS_DIR_TYPE(chCfg->dir));
    CHECK_PARAM(IS_DMA2D_PERIPH_REQ_TYPE(chCfg->dstPeriph));
    CHECK_PARAM(IS_DMA2D_PERIPH_REQ_TYPE(chCfg->srcPeriph));

    /* Config channel config */
    BL_WR_REG(DMA2DChs, DMA2D_C0SRCADDR, chCfg->srcDmaAddr);
    BL_WR_REG(DMA2DChs, DMA2D_C0DSTADDR, chCfg->destDmaAddr);

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_BUS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_TRANSFERSIZE, chCfg->transfLength);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_SRC_SIZE, chCfg->srcTransfWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_DST_SIZE, chCfg->dstTransfWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_SRC_BURST, chCfg->srcBurstSize);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_DST_BURST, chCfg->dstBurstSize);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_SI, chCfg->srcAddrInc);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_DI, chCfg->destAddrInc);
    BL_WR_REG(DMA2DChs, DMA2D_C0_BUS, tmpVal);

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_FLOWCNTRL, chCfg->dir);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_DSTPERIPHERAL, chCfg->dstPeriph);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_SRCPERIPHERAL, chCfg->srcPeriph);
    BL_WR_REG(DMA2DChs, DMA2D_C0_CFG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DMA2D set default value of all registers function
 *
 * @param  dmaId: DMA2D ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
void DMA2D_DeInit(DMA2D_ID_Type dmaId)
{
    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));

    GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_DMA2D);
}

/****************************************************************************/ /**
 * @brief  DMA2D channel update source memory address and len
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel
 * @param  memAddr: source memoty address
 * @param  len: source memory data length
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Channel_Update_SrcMemcfg(DMA2D_ID_Type dmaId, uint8_t ch, uint32_t memAddr, uint32_t len)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));

    /* config channel config*/
    BL_WR_REG(DMA2DChs, DMA2D_C0SRCADDR, memAddr);
    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_BUS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_TRANSFERSIZE, len);
    BL_WR_REG(DMA2DChs, DMA2D_C0_BUS, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DMA2D channel update destination memory address and len
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel
 * @param  memAddr: destination memoty address
 * @param  len: destination memory data length
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Channel_Update_DstMemcfg(DMA2D_ID_Type dmaId, uint8_t ch, uint32_t memAddr, uint32_t len)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));

    /* config channel config*/
    BL_WR_REG(DMA2DChs, DMA2D_C0DSTADDR, memAddr);
    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_BUS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_TRANSFERSIZE, len);
    BL_WR_REG(DMA2DChs, DMA2D_C0_BUS, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get DMA2D channel tranfersize
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel
 *
 * @return tranfersize size
 *
*******************************************************************************/
uint32_t DMA2D_Channel_TranferSize(DMA2D_ID_Type dmaId, uint8_t ch)
{
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(DMA2DChs, DMA2D_C0_BUS), DMA2D_TRANSFERSIZE);
}

/****************************************************************************/ /**
 * @brief  Get DMA2D channel busy status
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type DMA2D_Channel_Is_Busy(DMA2D_ID_Type dmaId, uint8_t ch)
{
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));

    return BL_IS_REG_BIT_SET(BL_RD_REG(DMA2DChs, DMA2D_C0_CFG), DMA2D_CH_EN) == 1 ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  DMA2D enable
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel number
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Channel_Enable(DMA2D_ID_Type dmaId, uint8_t ch)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_CFG);
    tmpVal = BL_SET_REG_BIT(tmpVal, DMA2D_CH_EN);
    BL_WR_REG(DMA2DChs, DMA2D_C0_CFG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DMA2D disable
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel number
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Channel_Disable(DMA2D_ID_Type dmaId, uint8_t ch)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_CFG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DMA2D_CH_EN);
    BL_WR_REG(DMA2DChs, DMA2D_C0_CFG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DMA2D init LLI transfer
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel number
 * @param  lliCfg: LLI configuration
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_LLI_Init(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_LLI_Cfg_Type *lliCfg)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));
    CHECK_PARAM(IS_DMA2D_TRANS_DIR_TYPE(lliCfg->dir));
    CHECK_PARAM(IS_DMA2D_PERIPH_REQ_TYPE(lliCfg->dstPeriph));
    CHECK_PARAM(IS_DMA2D_PERIPH_REQ_TYPE(lliCfg->srcPeriph));

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_FLOWCNTRL, lliCfg->dir);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_DSTPERIPHERAL, lliCfg->dstPeriph);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_SRCPERIPHERAL, lliCfg->srcPeriph);
    BL_WR_REG(DMA2DChs, DMA2D_C0_CFG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DMA2D channel update LLI
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel number
 * @param  LLI: LLI addr
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_LLI_Update(DMA2D_ID_Type dmaId, uint8_t ch, uint32_t LLI)
{
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch) + 0x100;

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));

    /* Config channel config */
    //BL_WR_REG(DMA2DChs, DMA2D_LLI, LLI);
    ARCH_MemCpy4((uint32_t *)(uintptr_t)DMA2DChs, (uint32_t *)(uintptr_t)LLI, 10);
}

/****************************************************************************/ /**
 * @brief  DMA2D channel get LLI counter
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel number
 *
 * @return LLI counter
 *
*******************************************************************************/
uint32_t DMA2D_LLI_Get_Counter(DMA2D_ID_Type dmaId, uint8_t ch)
{
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(DMA2DChs, DMA2D_C0_CFG), DMA2D_LLICOUNTER);
}

/****************************************************************************/ /**
 * @brief  DMA2D LLI PingPong Structure Start
 *
 * @param  dmaPpStruct: dma pp struct pointer
 * @param  Ping_Transfer_len: ping len
 * @param  Pong_Transfer_len: pong len
 *
 * @return Succrss or not
 *
*******************************************************************************/
BL_Err_Type DMA2D_LLI_PpStruct_Set_Transfer_Len(DMA2D_LLI_PP_Struct *dmaPpStruct, uint16_t Ping_Transfer_len, uint16_t Pong_Transfer_len)
{
    struct DMA2D_Control_Reg dmaCtrlRegVal_temp;

    if (Ping_Transfer_len > 4096 || Pong_Transfer_len > 4096) {
        return ERROR;
    }

    dmaCtrlRegVal_temp = PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX].dmaCtrl;
    dmaCtrlRegVal_temp.TransferSize = Ping_Transfer_len;
    PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX].dmaCtrl = dmaCtrlRegVal_temp;

    dmaCtrlRegVal_temp = PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX].dmaCtrl;
    dmaCtrlRegVal_temp.TransferSize = Pong_Transfer_len;
    PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX].dmaCtrl = dmaCtrlRegVal_temp;

    DMA2D_LLI_Init(dmaPpStruct->dmaId, dmaPpStruct->dmaChan, dmaPpStruct->lliCfg);
    DMA2D_LLI_Update(dmaPpStruct->dmaId, dmaPpStruct->dmaChan, (uint32_t)(uintptr_t)&PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX]);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DMA2D LLI Start New Transmit for Ping-Pong Buf
 *
 * @param  dmaPpBuf: DMA2D LLI Ping-Pong Buf
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_LLI_PpBuf_Start_New_Transmit(DMA2D_LLI_PP_Buf *dmaPpBuf)
{
    CPU_Interrupt_Disable_DMA2D(dmaPpBuf->dmaId);

    if (dmaPpBuf->lliListHeader[dmaPpBuf->idleIndex] != NULL) {
        DMA2D_LLI_Update(dmaPpBuf->dmaId, dmaPpBuf->dmaChan, (uint32_t)(uintptr_t)dmaPpBuf->lliListHeader[dmaPpBuf->idleIndex]);
        DMA2D_Channel_Enable(dmaPpBuf->dmaId, dmaPpBuf->dmaChan);
        dmaPpBuf->idleIndex = (dmaPpBuf->idleIndex == 0) ? 1 : 0;
    }

    CPU_Interrupt_Enable_DMA2D(dmaPpBuf->dmaId);
}

/****************************************************************************/ /**
 * @brief  DMA2D LLI Remove Completed Ping-Pong Buf List
 *
 * @param  dmaPpBuf: DMA2D LLI Ping-Pong Buf
 *
 * @return Next Ping-Pong Buf List Header
 *
*******************************************************************************/
DMA2D_LLI_Ctrl_Type *DMA2D_LLI_PpBuf_Remove_Completed_List(DMA2D_LLI_PP_Buf *dmaPpBuf)
{
    CPU_Interrupt_Disable_DMA2D(dmaPpBuf->dmaId);

    dmaPpBuf->lliListHeader[!dmaPpBuf->idleIndex] = NULL;
    CPU_Interrupt_Enable_DMA2D(dmaPpBuf->dmaId);
    return dmaPpBuf->lliListHeader[!dmaPpBuf->idleIndex];
}

/****************************************************************************/ /**
 * @brief  DMA2D LLI Append Buf to List
 *
 * @param  dmaPpBuf: DMA2D LLI Ping-Pong Buf
 * @param  dmaLliList: New LLI Buf to Append
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_LLI_PpBuf_Append(DMA2D_LLI_PP_Buf *dmaPpBuf, DMA2D_LLI_Ctrl_Type *dmaLliList)
{
    DMA2D_LLI_Ctrl_Type *pLliList = NULL;
    CPU_Interrupt_Disable_DMA2D(dmaPpBuf->dmaId);

    pLliList = dmaPpBuf->lliListHeader[dmaPpBuf->idleIndex];

    if (pLliList == NULL) {
        dmaLliList->nextLLI = 0;
        dmaLliList->dmaCtrl.I = 1;
        dmaPpBuf->lliListHeader[dmaPpBuf->idleIndex] = dmaLliList;
    } else {
        /*Append to last */
        while (pLliList->nextLLI != 0) {
            pLliList = (DMA2D_LLI_Ctrl_Type *)(uintptr_t)pLliList->nextLLI;
        }

        pLliList->nextLLI = (uint32_t)(uintptr_t)dmaLliList;
        pLliList->dmaCtrl.I = 0;
        dmaLliList->nextLLI = 0;
        dmaLliList->dmaCtrl.I = 1;
    }

    if (DMA2D_Channel_Is_Busy(dmaPpBuf->dmaId, dmaPpBuf->dmaChan) == RESET) {
        /* DMA2D stopped: maybe stop just a few minutes ago(not enter INT due to CPU_Interrupt_Disable)
           or has already stopped before this function is called */
        if (dmaPpBuf->lliListHeader[!dmaPpBuf->idleIndex] == NULL) {
            /* DMA2D has already stopped before this function is called */
            DMA2D_LLI_PpBuf_Start_New_Transmit(dmaPpBuf);
        }
    }

    CPU_Interrupt_Enable_DMA2D(dmaPpBuf->dmaId);
}

/****************************************************************************/ /**
 * @brief  DMA2D LLi Destroy Ping-Pong Buf
 *
 * @param  dmaPpBuf: DMA2D LLI Ping-Pong Buf
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_LLI_PpBuf_Destroy(DMA2D_LLI_PP_Buf *dmaPpBuf)
{
    /* DMA2D LLI Disable */
    DMA2D_Channel_Disable(dmaPpBuf->dmaId, dmaPpBuf->dmaChan);

    if (dmaPpBuf->lliListHeader[0] != NULL && dmaPpBuf->onTransCompleted != NULL) {
        dmaPpBuf->onTransCompleted(dmaPpBuf->lliListHeader[0]);
    }

    dmaPpBuf->lliListHeader[0] = NULL;

    if (dmaPpBuf->lliListHeader[1] != NULL && dmaPpBuf->onTransCompleted != NULL) {
        dmaPpBuf->onTransCompleted(dmaPpBuf->lliListHeader[1]);
    }

    dmaPpBuf->lliListHeader[1] = NULL;
    dmaPpBuf->idleIndex = 0;
}

/****************************************************************************/ /**
 * @brief  Mask/Unmask the DMA2D interrupt
 *
 * @param  dmaId: DMA2D ID type
 * @param  ch: DMA2D channel number
 * @param  intType: Specifies the interrupt type
 * @param  intMask: Enable/Disable Specified interrupt type
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_IntMask(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(ch));
    CHECK_PARAM(IS_DMA2D_INT_TYPE(intType));

    switch (intType) {
        case DMA2D_INT_TCOMPLETED:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_SET_REG_BIT(BL_RD_REG(DMA2DChs, DMA2D_C0_BUS), DMA2D_I);
                BL_WR_REG(DMA2DChs, DMA2D_C0_BUS, tmpVal);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_CLR_REG_BIT(BL_RD_REG(DMA2DChs, DMA2D_C0_BUS), DMA2D_I);
                BL_WR_REG(DMA2DChs, DMA2D_C0_BUS, tmpVal);
            }

            break;

        case DMA2D_INT_ALL:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_BUS);
                tmpVal = BL_SET_REG_BIT(tmpVal, DMA2D_I);
                BL_WR_REG(DMA2DChs, DMA2D_C0_BUS, tmpVal);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_BUS);
                tmpVal = BL_CLR_REG_BIT(tmpVal, DMA2D_I);
                BL_WR_REG(DMA2DChs, DMA2D_C0_BUS, tmpVal);
            }

            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  Install DMA2D interrupt callback function
 *
 * @param  dmaId: DMA2D ID type
 * @param  dmaChan: DMA2D Channel type
 * @param  intType: DMA2D interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DMA2D_Int_Callback_Install(DMA2D_ID_Type dmaId, DMA2D_Chan_Type dmaChan, DMA2D_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_ID_TYPE(dmaId));
    CHECK_PARAM(IS_DMA2D_CHAN_TYPE(dmaChan));
    CHECK_PARAM(IS_DMA2D_INT_TYPE(intType));

    dma2dIntCbfArra[dmaId][dmaChan][intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  MMSYS DMA2D channel 0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DMA2D_INT0_IRQHandler(void)
{
    DMA2D_IntHandler(DMA2D0_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  MMSYS DMA2D channel 1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DMA2D_INT1_IRQHandler(void)
{
    DMA2D_IntHandler(DMA2D0_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  DMA2D LLI PingPong Structure Initial
 *
 * @param  dmaPpStruct: DMA2D LLI PingPong Config Parameter
 *
 * @return start success or not
 *
*******************************************************************************/
BL_Err_Type DMA2D_LLI_PpStruct_Init(DMA2D_LLI_PP_Struct *dmaPpStruct)
{
    //setup lliList
    dmaPpStruct->dmaCtrlRegVal.I = 1;
    dmaPpStruct->pingpongIndex = 0;

    if (dmaPpStruct->lliCfg->dir == DMA2D_TRNS_M2P) {
        PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX].srcDmaAddr = dmaPpStruct->pingpongBufAddr[0];
        PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX].destDmaAddr = dmaPpStruct->operatePeriphAddr;

        PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX].srcDmaAddr = dmaPpStruct->pingpongBufAddr[1];
        PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX].destDmaAddr = dmaPpStruct->operatePeriphAddr;
    } else if (dmaPpStruct->lliCfg->dir == DMA2D_TRNS_P2M) {
        PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX].srcDmaAddr = dmaPpStruct->operatePeriphAddr;
        PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX].destDmaAddr = dmaPpStruct->pingpongBufAddr[0];

        PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX].srcDmaAddr = dmaPpStruct->operatePeriphAddr;
        PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX].destDmaAddr = dmaPpStruct->pingpongBufAddr[1];
    } else {
        return ERROR;
        /*V1.0 version DMA2D LLI Ping-Pong structure not support P2P & M2M MODE*/
    }

    PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX].nextLLI = (uint32_t)(uintptr_t)&PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX];
    PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX].dmaCtrl = dmaPpStruct->dmaCtrlRegVal;

    PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX].nextLLI = (uint32_t)(uintptr_t)&PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX];
    PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PONG_INDEX].dmaCtrl = dmaPpStruct->dmaCtrlRegVal;

    DMA2D_LLI_Init(dmaPpStruct->dmaId, dmaPpStruct->dmaChan, dmaPpStruct->lliCfg);

    DMA2D_LLI_Update(dmaPpStruct->dmaId, dmaPpStruct->dmaChan, (uint32_t)(uintptr_t)&PingPongListArra[dmaPpStruct->dmaId][dmaPpStruct->dmaChan][DMA2D_PING_INDEX]);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DMA2D LLI PingPong Structure Start
 *
 * @param  dmaPpStruct: None
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_LLI_PpStruct_Start(DMA2D_LLI_PP_Struct *dmaPpStruct)
{
    DMA2D_Channel_Enable(dmaPpStruct->dmaId, dmaPpStruct->dmaChan);
}

/****************************************************************************/ /**
 * @brief  DMA2D LLI PingPong Structure Stop
 *
 * @param  dmaPpStruct: None
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_LLI_PpStruct_Stop(DMA2D_LLI_PP_Struct *dmaPpStruct)
{
    DMA2D_Channel_Disable(dmaPpStruct->dmaId, dmaPpStruct->dmaChan);
}

/****************************************************************************/ /**
 * @brief  DMA2D translate picture
 *
 * @param  cfg: Pointer of DMA2D picture configure type
 * @param  lliCfg: Pointer of DMA2D LLI ctrl type
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Picture_Translate_Calculate(DMA2D_Picture_Cfg_Type *cfg, DMA2D_LLI_Ctrl_Type *lliCfg)
{
    uint32_t tmpVal = 1 << cfg->transWidth;
    lliCfg->dmaCtrl.SRC_SIZE = cfg->transWidth;
    lliCfg->dmaCtrl.DST_SIZE = cfg->transWidth;

    DMA2D_Picture_Cfg_Type pictureCfg = {
        .transWidth = cfg->transWidth,
        .pixWidth = cfg->pixWidth,
        .srcAddr = cfg->srcAddr,
        .srcWidth = cfg->srcWidth,
        .srcX0 = cfg->srcX0,
        .srcY0 = cfg->srcY0,
        .srcX1 = cfg->srcX1,
        .srcY1 = cfg->srcY1,
        .dstAddr = cfg->dstAddr,
        .dstWidth = cfg->dstWidth,
        .dstX0 = cfg->dstX0,
        .dstY0 = cfg->dstY0,
    };

    if (cfg->srcX0 > cfg->srcX1 && cfg->srcY0 <= cfg->srcY1) {
        pictureCfg.srcX0 = cfg->srcX1;
        pictureCfg.srcX1 = cfg->srcX0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth;
    } else if (cfg->srcX0 <= cfg->srcX1 && cfg->srcY0 > cfg->srcY1) {
        pictureCfg.srcY0 = cfg->srcY1;
        pictureCfg.srcY1 = cfg->srcY0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcY1 - pictureCfg.srcY0) * pictureCfg.pixWidth * pictureCfg.srcWidth;
    } else if (cfg->srcX0 > cfg->srcX1 && cfg->srcY0 > cfg->srcY1) {
        pictureCfg.srcX0 = cfg->srcX1;
        pictureCfg.srcX1 = cfg->srcX0;
        pictureCfg.srcY0 = cfg->srcY1;
        pictureCfg.srcY1 = cfg->srcY0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcY1 - pictureCfg.srcY0) * pictureCfg.pixWidth * pictureCfg.srcWidth - (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth;
    }

    lliCfg->srcDmaAddr = pictureCfg.srcAddr + pictureCfg.srcWidth * pictureCfg.pixWidth * pictureCfg.srcY0 + pictureCfg.pixWidth * pictureCfg.srcX0;
    lliCfg->destDmaAddr = pictureCfg.dstAddr + pictureCfg.dstWidth * pictureCfg.pixWidth * pictureCfg.dstY0 + pictureCfg.pixWidth * pictureCfg.dstX0;

    lliCfg->dma2dCfg.srcCntX = (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal;
    lliCfg->dma2dCfg.srcIncrX = tmpVal;
    lliCfg->dma2dCfg.srcCntY = pictureCfg.srcY1 - pictureCfg.srcY0;
    lliCfg->dma2dCfg.srcIncrY = (pictureCfg.srcWidth - pictureCfg.srcX1 + pictureCfg.srcX0) * pictureCfg.pixWidth + tmpVal;
    lliCfg->dma2dCfg.dstCntX = (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal;
    lliCfg->dma2dCfg.dstIncrX = tmpVal;
    lliCfg->dma2dCfg.dstIncrY = (pictureCfg.dstWidth - pictureCfg.srcX1 + pictureCfg.srcX0) * pictureCfg.pixWidth + tmpVal;
}

/****************************************************************************/ /**
 * @brief  DMA2D rotate picture
 *
 * @param  cfg: Pointer of DMA2D picture configure type
 * @param  lliCfg: Pointer of DMA2D LLI ctrl type
 * @param  rotate: Rotate degree type
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Picture_Rotate_Calculate(DMA2D_Picture_Cfg_Type *cfg, DMA2D_LLI_Ctrl_Type *lliCfg, DMA2D_Rotate_Type rotate)
{
    uint32_t tmpVal = 1 << cfg->transWidth;
    lliCfg->dmaCtrl.SRC_SIZE = cfg->transWidth;
    lliCfg->dmaCtrl.DST_SIZE = cfg->transWidth;

    DMA2D_Picture_Cfg_Type pictureCfg = {
        .transWidth = cfg->transWidth,
        .pixWidth = cfg->pixWidth,
        .srcAddr = cfg->srcAddr,
        .srcWidth = cfg->srcWidth,
        .srcX0 = cfg->srcX0,
        .srcY0 = cfg->srcY0,
        .srcX1 = cfg->srcX1,
        .srcY1 = cfg->srcY1,
        .dstAddr = cfg->dstAddr,
        .dstWidth = cfg->dstWidth,
        .dstX0 = cfg->dstX0,
        .dstY0 = cfg->dstY0,
    };

    if (cfg->srcX0 > cfg->srcX1 && cfg->srcY0 <= cfg->srcY1) {
        pictureCfg.srcX0 = cfg->srcX1;
        pictureCfg.srcX1 = cfg->srcX0;
    } else if (cfg->srcX0 <= cfg->srcX1 && cfg->srcY0 > cfg->srcY1) {
        pictureCfg.srcY0 = cfg->srcY1;
        pictureCfg.srcY1 = cfg->srcY0;
    } else if (cfg->srcX0 > cfg->srcX1 && cfg->srcY0 > cfg->srcY1) {
        pictureCfg.srcX0 = cfg->srcX1;
        pictureCfg.srcX1 = cfg->srcX0;
        pictureCfg.srcY0 = cfg->srcY1;
        pictureCfg.srcY1 = cfg->srcY0;
    }

    lliCfg->srcDmaAddr = pictureCfg.srcAddr + pictureCfg.srcWidth * pictureCfg.pixWidth * pictureCfg.srcY0 + pictureCfg.pixWidth * pictureCfg.srcX0;
    lliCfg->destDmaAddr = pictureCfg.dstAddr + pictureCfg.dstWidth * pictureCfg.pixWidth * pictureCfg.dstY0 + pictureCfg.pixWidth * pictureCfg.dstX0;

    lliCfg->dma2dCfg.srcCntX = (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal;
    lliCfg->dma2dCfg.srcIncrX = tmpVal;
    lliCfg->dma2dCfg.srcCntY = pictureCfg.srcY1 - pictureCfg.srcY0;
    lliCfg->dma2dCfg.srcIncrY = (pictureCfg.srcWidth - pictureCfg.srcX1 + pictureCfg.srcX0) * pictureCfg.pixWidth + tmpVal;
    lliCfg->dma2dCfg.dstCntX = (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal;
    lliCfg->dma2dCfg.dstIncrX = pictureCfg.dstWidth * pictureCfg.pixWidth;
    lliCfg->dma2dCfg.dstIncrY = -((pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal * pictureCfg.pixWidth * pictureCfg.dstWidth) + pictureCfg.pixWidth * pictureCfg.dstWidth - tmpVal;

    if (rotate == DMA2D_ROTATE_DEGREE_90) {
        lliCfg->destDmaAddr += (pictureCfg.srcY1 - pictureCfg.srcY0 - 1) * tmpVal;
    } else if (rotate == DMA2D_ROTATE_DEGREE_180) {
        lliCfg->destDmaAddr += (pictureCfg.srcY1 - pictureCfg.srcY0) * tmpVal * pictureCfg.dstWidth + (pictureCfg.srcX1 - pictureCfg.srcX0 - 1) * tmpVal;
        lliCfg->dma2dCfg.dstIncrX = -tmpVal;
        lliCfg->dma2dCfg.dstIncrY = -pictureCfg.dstWidth * pictureCfg.pixWidth + (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth - tmpVal;
    } else if (rotate == DMA2D_ROTATE_DEGREE_270) {
        lliCfg->destDmaAddr += (pictureCfg.srcX1 - pictureCfg.srcX0 - 1) * tmpVal * pictureCfg.dstWidth;
        lliCfg->dma2dCfg.dstIncrX = -pictureCfg.dstWidth * pictureCfg.pixWidth;
        lliCfg->dma2dCfg.dstIncrY = -lliCfg->dma2dCfg.dstIncrY;
    }
}

/****************************************************************************/ /**
 * @brief  DMA2D fold picture
 *
 * @param  cfg: Pointer of DMA2D picture configure type
 * @param  lliCfg: Pointer of DMA2D LLI ctrl type
 * @param  fold: Fold direction type
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Picture_Fold_Calculate(DMA2D_Picture_Cfg_Type *cfg, DMA2D_LLI_Ctrl_Type *lliCfg, DMA2D_Fold_Type fold)
{
    uint32_t tmpVal = 1 << cfg->transWidth;
    lliCfg->dmaCtrl.SRC_SIZE = cfg->transWidth;
    lliCfg->dmaCtrl.DST_SIZE = cfg->transWidth;

    DMA2D_Picture_Cfg_Type pictureCfg = {
        .transWidth = cfg->transWidth,
        .pixWidth = cfg->pixWidth,
        .srcAddr = cfg->srcAddr,
        .srcWidth = cfg->srcWidth,
        .srcX0 = cfg->srcX0,
        .srcY0 = cfg->srcY0,
        .srcX1 = cfg->srcX1,
        .srcY1 = cfg->srcY1,
        .dstAddr = cfg->dstAddr,
        .dstWidth = cfg->dstWidth,
        .dstX0 = cfg->dstX0,
        .dstY0 = cfg->dstY0,
    };

    if (cfg->srcX0 > cfg->srcX1 && cfg->srcY0 <= cfg->srcY1) {
        pictureCfg.srcX0 = cfg->srcX1;
        pictureCfg.srcX1 = cfg->srcX0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth;
    } else if (cfg->srcX0 <= cfg->srcX1 && cfg->srcY0 > cfg->srcY1) {
        pictureCfg.srcY0 = cfg->srcY1;
        pictureCfg.srcY1 = cfg->srcY0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcY1 - pictureCfg.srcY0) * pictureCfg.pixWidth * pictureCfg.srcWidth;
    } else if (cfg->srcX0 > cfg->srcX1 && cfg->srcY0 > cfg->srcY1) {
        pictureCfg.srcX0 = cfg->srcX1;
        pictureCfg.srcX1 = cfg->srcX0;
        pictureCfg.srcY0 = cfg->srcY1;
        pictureCfg.srcY1 = cfg->srcY0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcY1 - pictureCfg.srcY0) * pictureCfg.pixWidth * pictureCfg.srcWidth - (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth;
    }

    lliCfg->srcDmaAddr = pictureCfg.srcAddr + pictureCfg.srcWidth * pictureCfg.pixWidth * pictureCfg.srcY0 + pictureCfg.pixWidth * pictureCfg.srcX0;
    lliCfg->destDmaAddr = pictureCfg.dstAddr + pictureCfg.dstWidth * pictureCfg.pixWidth * pictureCfg.dstY0 + pictureCfg.pixWidth * pictureCfg.dstX0 + (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth - tmpVal;

    lliCfg->dma2dCfg.srcCntX = (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal;
    lliCfg->dma2dCfg.srcIncrX = tmpVal;
    lliCfg->dma2dCfg.srcCntY = pictureCfg.srcY1 - pictureCfg.srcY0;
    lliCfg->dma2dCfg.srcIncrY = (pictureCfg.srcWidth - pictureCfg.srcX1 + pictureCfg.srcX0) * pictureCfg.pixWidth + tmpVal;
    lliCfg->dma2dCfg.dstCntX = (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal;
    lliCfg->dma2dCfg.dstIncrX = -tmpVal;
    lliCfg->dma2dCfg.dstIncrY = (pictureCfg.dstWidth + pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth - tmpVal;

    if (fold == DMA2D_FOLD_UP_DOWN) {
        lliCfg->destDmaAddr = pictureCfg.dstAddr + pictureCfg.dstWidth * pictureCfg.pixWidth * pictureCfg.dstY0 + pictureCfg.pixWidth * pictureCfg.dstX0 + (pictureCfg.srcY1 - pictureCfg.srcY0 - 1) * pictureCfg.pixWidth * pictureCfg.dstWidth;
        lliCfg->dma2dCfg.dstIncrX = tmpVal;
        lliCfg->dma2dCfg.dstIncrY = -lliCfg->dma2dCfg.dstIncrY;
    }
}

/****************************************************************************/ /**
 * @brief  DMA2D fill picture
 *
 * @param  cfg: Pointer of DMA2D picture configure type
 * @param  lliCfg: Pointer of DMA2D LLI ctrl type
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Picture_Fill_Calculate(DMA2D_Picture_Cfg_Type *cfg, DMA2D_LLI_Ctrl_Type *lliCfg)
{
    uint32_t tmpVal = 1 << cfg->transWidth;
    lliCfg->dmaCtrl.SRC_SIZE = cfg->transWidth;
    lliCfg->dmaCtrl.DST_SIZE = cfg->transWidth;

    DMA2D_Picture_Cfg_Type pictureCfg = {
        .transWidth = cfg->transWidth,
        .pixWidth = cfg->pixWidth,
        .srcAddr = cfg->srcAddr,
        .srcWidth = cfg->srcWidth,
        .srcX0 = cfg->srcX0,
        .srcY0 = cfg->srcY0,
        .srcX1 = cfg->srcX1,
        .srcY1 = cfg->srcY1,
        .dstAddr = cfg->dstAddr,
        .dstWidth = cfg->dstWidth,
        .dstX0 = cfg->dstX0,
        .dstY0 = cfg->dstY0,
    };

    if (cfg->srcX0 > cfg->srcX1 && cfg->srcY0 <= cfg->srcY1) {
        pictureCfg.srcX0 = cfg->srcX1;
        pictureCfg.srcX1 = cfg->srcX0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth;
    } else if (cfg->srcX0 <= cfg->srcX1 && cfg->srcY0 > cfg->srcY1) {
        pictureCfg.srcY0 = cfg->srcY1;
        pictureCfg.srcY1 = cfg->srcY0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcY1 - pictureCfg.srcY0) * pictureCfg.pixWidth * pictureCfg.srcWidth;
    } else if (cfg->srcX0 > cfg->srcX1 && cfg->srcY0 > cfg->srcY1) {
        pictureCfg.srcX0 = cfg->srcX1;
        pictureCfg.srcX1 = cfg->srcX0;
        pictureCfg.srcY0 = cfg->srcY1;
        pictureCfg.srcY1 = cfg->srcY0;
        pictureCfg.dstAddr = pictureCfg.dstAddr - (pictureCfg.srcY1 - pictureCfg.srcY0) * pictureCfg.pixWidth * pictureCfg.srcWidth - (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth;
    }

    lliCfg->srcDmaAddr = pictureCfg.srcAddr;
    lliCfg->destDmaAddr = pictureCfg.dstAddr + pictureCfg.dstWidth * pictureCfg.pixWidth * pictureCfg.dstY0 + pictureCfg.pixWidth * pictureCfg.dstX0;

    lliCfg->dma2dCfg.srcCntX = (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal;
    lliCfg->dma2dCfg.srcIncrX = 0;
    lliCfg->dma2dCfg.srcCntY = pictureCfg.srcY1 - pictureCfg.srcY0;
    lliCfg->dma2dCfg.srcIncrY = 0;
    lliCfg->dma2dCfg.dstCntX = (pictureCfg.srcX1 - pictureCfg.srcX0) * pictureCfg.pixWidth / tmpVal;
    lliCfg->dma2dCfg.dstIncrX = tmpVal;
    lliCfg->dma2dCfg.dstIncrY = (pictureCfg.dstWidth - pictureCfg.srcX1 + pictureCfg.srcX0) * pictureCfg.pixWidth + tmpVal;
}

/****************************************************************************/ /**
 * @brief  DMA2D transfer start
 *
 * @param  dmaId: DMA2D id
 * @param  ch: DMA2D channel
 * @param  lliCfg: Pointer of DMA2D LLI ctrl type
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Picture_Transfer_Start(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_LLI_Ctrl_Type *lliCfg)
{
    DMA2D_Channel_Cfg_Type chCfg = {
        .srcDmaAddr = lliCfg->srcDmaAddr,
        .destDmaAddr = lliCfg->destDmaAddr,
        .transfLength = 0,
        .dir = DMA2D_TRNS_M2M,
        .ch = ch,
        .srcTransfWidth = lliCfg->dmaCtrl.SRC_SIZE,
        .dstTransfWidth = lliCfg->dmaCtrl.DST_SIZE,
        .srcBurstSize = DMA2D_BURST_SIZE_16,
        .dstBurstSize = DMA2D_BURST_SIZE_16,
        .srcAddrInc = DMA2D_MINC_ENABLE,
        .destAddrInc = DMA2D_MINC_ENABLE,
        .srcPeriph = DMA2D_REQ_NONE,
        .dstPeriph = DMA2D_REQ_NONE,
    };

    DMA2D_Channel_Disable(dmaId, ch);
    DMA2D_Init(dmaId, ch, &lliCfg->dma2dCfg);
    DMA2D_Channel_Init(dmaId, &chCfg);
    DMA2D_Enable(dmaId);
    DMA2D_Channel_Enable(dmaId, ch);
}

/****************************************************************************/ /**
 * @brief  DMA2D color key mode configure
 *
 * @param  dmaId: DMA2D id
 * @param  ch: DMA2D channel
 * @param  keyType: Color key type
 * @param  keyValue: Color key value
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Color_Key_Set(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_Color_Key_Type keyType, uint32_t keyValue)
{
    uint32_t tmpVal;
    /* Get DMA2D register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_COLOR_KEY_TYPE(keyType));

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_KEY_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_KEY_MODE, keyType);
    switch(keyType)
    {
        case DMA2D_COLOR_KEY_8BIT:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_KEY_STRB, 0x1);
            break;
        case DMA2D_COLOR_KEY_16BIT:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_KEY_STRB, 0x3);
            break;
        case DMA2D_COLOR_KEY_24BIT:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_KEY_STRB, 0x7);
            break;
        case DMA2D_COLOR_KEY_32BIT:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA2D_KEY_STRB, 0xf);
            break;
        default:
            break;
    }
    BL_WR_REG(DMA2DChs, DMA2D_C0_KEY_EN, tmpVal);

    BL_WR_REG(DMA2DChs, DMA2D_C0_KEY, keyValue);
}

/****************************************************************************/ /**
 * @brief  DMA2D color key mode enable
 *
 * @param  dmaId: DMA2D id
 * @param  ch: DMA2D channel
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Color_Key_Enable(DMA2D_ID_Type dmaId, uint8_t ch)
{
    uint32_t tmpVal;
    /* Get DMA2D register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA2D_COLOR_KEY_TYPE(keyType));

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_KEY_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, DMA2D_KEY_EN);
    BL_WR_REG(DMA2DChs, DMA2D_C0_KEY_EN, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DMA2D color key mode disable
 *
 * @param  dmaId: DMA2D id
 * @param  ch: DMA2D channel
 *
 * @return None
 *
*******************************************************************************/
void DMA2D_Color_Key_Disable(DMA2D_ID_Type dmaId, uint8_t ch)
{
    uint32_t tmpVal;
    /* Get DMA2D register */
    uint32_t DMA2DChs = DMA2D_Get_Channel(dma2dAddr[dmaId], ch);

    tmpVal = BL_RD_REG(DMA2DChs, DMA2D_C0_KEY_EN);
    BL_WR_REG(DMA2DChs, DMA2D_C0_KEY_EN, BL_CLR_REG_BIT(tmpVal, DMA2D_KEY_EN));
}

/*@} end of group DMA2D_Public_Functions */

/*@} end of group DMA2D */

/*@} end of group BL808_Peripheral_Driver */
