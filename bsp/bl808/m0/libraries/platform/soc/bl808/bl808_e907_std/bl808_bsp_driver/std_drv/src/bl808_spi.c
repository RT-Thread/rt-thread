/**
  ******************************************************************************
  * @file    bl808_spi.c
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

#include "bl808_spi.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SPI
 *  @{
 */

/** @defgroup  SPI_Private_Macros
 *  @{
 */
#define SPI_TX_TIMEOUT_COUNT (320 * 1000)
#define SPI_RX_TIMEOUT_COUNT (320 * 1000)

/*@} end of group SPI_Private_Macros */

/** @defgroup  SPI_Private_Types
 *  @{
 */

/*@} end of group SPI_Private_Types */

/** @defgroup  SPI_Private_Variables
 *  @{
 */
const uint32_t spiAddr[SPI_ID_MAX] = { SPI0_BASE, SPI1_BASE };
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *spiIntCbfArra[SPI_ID_MAX][SPI_INT_ALL] = {
    { NULL }
};
#endif

/*@} end of group SPI_Private_Variables */

/** @defgroup  SPI_Global_Variables
 *  @{
 */

/*@} end of group SPI_Global_Variables */

/** @defgroup  SPI_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static void SPI_IntHandler(SPI_ID_Type spiNo);
#endif

/*@} end of group SPI_Private_Fun_Declaration */

/** @defgroup  SPI_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  SPI interrupt common handler function
 *
 * @param  spiNo: SPI ID type
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static void SPI_IntHandler(SPI_ID_Type spiNo)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    tmpVal = BL_RD_REG(SPIx, SPI_INT_STS);

    /* Transfer end interrupt,shared by both master and slave mode */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_END_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_END_MASK)) {
        BL_WR_REG(SPIx, SPI_INT_STS, BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_END_CLR));

        if (spiIntCbfArra[spiNo][SPI_INT_END] != NULL) {
            spiIntCbfArra[spiNo][SPI_INT_END]();
        }
    }

    /* TX fifo ready interrupt(fifo count > fifo threshold) */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_TXF_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_TXF_MASK)) {
        if (spiIntCbfArra[spiNo][SPI_INT_TX_FIFO_REQ] != NULL) {
            spiIntCbfArra[spiNo][SPI_INT_TX_FIFO_REQ]();
        }
    }

    /*  RX fifo ready interrupt(fifo count > fifo threshold) */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_RXF_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_RXF_MASK)) {
        if (spiIntCbfArra[spiNo][SPI_INT_RX_FIFO_REQ] != NULL) {
            spiIntCbfArra[spiNo][SPI_INT_RX_FIFO_REQ]();
        }
    }

    /* Slave mode transfer time-out interrupt,triggered when bus is idle for the given value */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_STO_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_STO_MASK)) {
        BL_WR_REG(SPIx, SPI_INT_STS, BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_STO_CLR));

        if (spiIntCbfArra[spiNo][SPI_INT_SLAVE_TIMEOUT] != NULL) {
            spiIntCbfArra[spiNo][SPI_INT_SLAVE_TIMEOUT]();
        }
    }

    /* Slave mode tx underrun error interrupt,trigged when tx is not ready during transfer */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_TXU_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_TXU_MASK)) {
        BL_WR_REG(SPIx, SPI_INT_STS, BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_TXU_CLR));

        if (spiIntCbfArra[spiNo][SPI_INT_SLAVE_UNDERRUN] != NULL) {
            spiIntCbfArra[spiNo][SPI_INT_SLAVE_UNDERRUN]();
        }
    }

    /* TX/RX fifo overflow/underflow interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_FER_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_FER_MASK)) {
        if (spiIntCbfArra[spiNo][SPI_INT_FIFO_ERROR] != NULL) {
            spiIntCbfArra[spiNo][SPI_INT_FIFO_ERROR]();
        }
    }
}
#endif

/*@} end of group SPI_Private_Functions */

/** @defgroup  SPI_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  SPI initialization function
 *
 * @param  spiNo: SPI ID type
 * @param  spiCfg: SPI configuration structure pointer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_Init(SPI_ID_Type spiNo, SPI_CFG_Type *spiCfg)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_SLAVE_PIN_TYPE(slavePin));
    CHECK_PARAM(IS_SPI_WORK_MODE_TYPE(spiCfg->mod));
    CHECK_PARAM(IS_SPI_BYTE_INVERSE_TYPE(spiCfg->byteSequence));
    CHECK_PARAM(IS_SPI_BIT_INVERSE_TYPE(spiCfg->bitSequence));
    CHECK_PARAM(IS_SPI_CLK_PHASE_INVERSE_TYPE(spiCfg->clkPhaseInv));
    CHECK_PARAM(IS_SPI_CLK_POLARITY_TYPE(spiCfg->clkPolarity));

    /* Disable clock gate when use SPI0 */
    if (SPI0_ID == spiNo) {
        GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_SPI);
    }

    /* spi config */
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_DEG_EN, spiCfg->deglitchEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_S_3PIN_MODE, spiCfg->slavePin);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_M_CONT_EN, spiCfg->continuousEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_BYTE_INV, spiCfg->byteSequence);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_BIT_INV, spiCfg->bitSequence);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_SCLK_PH, (spiCfg->clkPhaseInv + 1) & 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_SCLK_POL, spiCfg->clkPolarity);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_FRAME_SIZE, spiCfg->frameSize);
    BL_WR_REG(SPIx, SPI_CONFIG, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SPI0_IRQn, SPI0_IRQHandler);
    Interrupt_Handler_Register(SPI1_IRQn, SPI1_IRQHandler);
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SPI set default value of all registers function
 *
 * @param  spiNo: SPI ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_DeInit(SPI_ID_Type spiNo)
{
    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    if (SPI0_ID == spiNo) {
        GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_SPI);
    } else if (SPI0_MM_ID == spiNo) {
        GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_SPI);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Length of data phase1/0,start/stop condition and interval between frame initialization
 *         function
 *
 * @param  spiNo: SPI ID type
 * @param  clockCfg: Clock configuration structure pointer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_ClockConfig(SPI_ID_Type spiNo, SPI_ClockCfg_Type *clockCfg)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Configure length of data phase1/0 and start/stop condition */
    tmpVal = BL_RD_REG(SPIx, SPI_PRD_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_S, clockCfg->startLen - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_P, clockCfg->stopLen - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_D_PH_0, clockCfg->dataPhase0Len - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_D_PH_1, clockCfg->dataPhase1Len - 1);
    BL_WR_REG(SPIx, SPI_PRD_0, tmpVal);

    /* Configure length of interval between frame */
    tmpVal = BL_RD_REG(SPIx, SPI_PRD_1);
    BL_WR_REG(SPIx, SPI_PRD_1, BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_I, clockCfg->intervalLen - 1));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SPI configure fifo function
 *
 * @param  spiNo: SPI ID type
 * @param  fifoCfg: FIFO configuration structure pointer
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_FifoConfig(SPI_ID_Type spiNo, SPI_FifoCfg_Type *fifoCfg)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Set fifo threshold value */
    tmpVal = BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_TX_FIFO_TH, fifoCfg->txFifoThreshold);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_RX_FIFO_TH, fifoCfg->rxFifoThreshold);
    BL_WR_REG(SPIx, SPI_FIFO_CONFIG_1, tmpVal);

    /* Enable or disable dma function */
    tmpVal = BL_RD_REG(SPIx, SPI_FIFO_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_DMA_TX_EN, fifoCfg->txFifoDmaEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_DMA_RX_EN, fifoCfg->rxFifoDmaEnable);
    BL_WR_REG(SPIx, SPI_FIFO_CONFIG_0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set SPI Frame Size
 *
 * @param  spiNo: SPI ID type
 * @param  frameSize: FrameSize Type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_SetFrameSize(SPI_ID_Type spiNo, SPI_FrameSize_Type frameSize)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_SLAVE_PIN_TYPE(frameSize));

    /* The SPI must be clear fifo first */
    SPI_ClrRxFifo(spiNo);
    SPI_ClrTxFifo(spiNo);

    /* set framsize*/
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_FRAME_SIZE, frameSize);
    BL_WR_REG(SPIx, SPI_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set SPI SCK Clcok
 *
 * @param  spiNo: SPI ID type
 * @param  clk: Clk
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_SetClock(SPI_ID_Type spiNo, uint32_t clk)
{
    uint32_t glb_div = 0, spi_div = 0;
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    if (clk > 80000000) {
        clk = 80000000;
    } else if (clk < 9766) {
        clk = 9766;
    }

    if (clk >= 312500) {
        glb_div = 0;
        spi_div = 80000000 / clk - 1;
    } else {
        glb_div = 31;
        spi_div = 2500000 / clk - 1;
    }

    if (spiNo == SPI0_ID) {
        GLB_Set_SPI_CLK(ENABLE, GLB_SPI_CLK_MCU_MUXPLL_160M, glb_div);
    } else {
        GLB_Set_DSP_SPI_CLK(ENABLE, GLB_DSP_SPI_CLK_DSP_MUXPLL_160M, glb_div);
    }

    /* Configure length of data phase1/0 and start/stop condition */
    tmpVal = BL_RD_REG(SPIx, SPI_PRD_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_S, spi_div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_P, spi_div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_D_PH_0, spi_div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_D_PH_1, spi_div);
    BL_WR_REG(SPIx, SPI_PRD_0, tmpVal);

    tmpVal = BL_RD_REG(SPIx, SPI_PRD_1);
    BL_WR_REG(SPIx, SPI_PRD_1, BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_PRD_I, spi_div));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable spi transfer
 *
 * @param  spiNo: SPI ID type
 * @param  modeType: Master or slave mode select
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_Enable(SPI_ID_Type spiNo, SPI_WORK_MODE_Type modeType)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_WORK_MODE_TYPE(modeType));

    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);

    if (modeType != SPI_WORK_MODE_SLAVE) {
        /* master mode */
        tmpVal = BL_CLR_REG_BIT(tmpVal, SPI_CR_SPI_S_EN);
        tmpVal = BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_M_EN);
    } else {
        /* slave mode */
        tmpVal = BL_CLR_REG_BIT(tmpVal, SPI_CR_SPI_M_EN);
        tmpVal = BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_S_EN);
    }

    BL_WR_REG(SPIx, SPI_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable spi transfer
 *
 * @param  spiNo: SPI ID type
 * @param  modeType: Master or slave mode select
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_Disable(SPI_ID_Type spiNo, SPI_WORK_MODE_Type modeType)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_WORK_MODE_TYPE(modeType));

    /* close master and slave */
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SPI_CR_SPI_M_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SPI_CR_SPI_S_EN);
    BL_WR_REG(SPIx, SPI_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set time-out value to trigger interrupt when spi bus is idle for the given value
 *
 * @param  spiNo: SPI ID type
 * @param  value: Time value
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_SetTimeOutValue(SPI_ID_Type spiNo, uint16_t value)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Set time-out value */
    tmpVal = BL_RD_REG(SPIx, SPI_STO_VALUE);
    BL_WR_REG(SPIx, SPI_STO_VALUE, BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_STO_VALUE, value - 1));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set de-glitch function cycle count value
 *
 * @param  spiNo: SPI ID type
 * @param  cnt: De-glitch function cycle count
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_SetDeglitchCount(SPI_ID_Type spiNo, uint8_t cnt)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Set count value */
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_DEG_CNT, cnt);
    BL_WR_REG(SPIx, SPI_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable rx data ignore function and set start/stop point
 *
 * @param  spiNo: SPI ID type
 * @param  startPoint: Start point
 * @param  stopPoint: Stop point
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_RxIgnoreEnable(SPI_ID_Type spiNo, uint8_t startPoint, uint8_t stopPoint)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Enable rx ignore function */
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    BL_WR_REG(SPIx, SPI_CONFIG, BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_RXD_IGNR_EN));

    /* Set start and stop point */
    tmpVal = startPoint << SPI_CR_SPI_RXD_IGNR_S_POS | stopPoint;
    BL_WR_REG(SPIx, SPI_RXD_IGNR, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable rx data ignore function
 *
 * @param  spiNo: SPI ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_RxIgnoreDisable(SPI_ID_Type spiNo)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Disable rx ignore function */
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    BL_WR_REG(SPIx, SPI_CONFIG, BL_CLR_REG_BIT(tmpVal, SPI_CR_SPI_RXD_IGNR_EN));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Clear tx fifo and tx fifo overflow/underflow status
 *
 * @param  spiNo: SPI ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_ClrTxFifo(SPI_ID_Type spiNo)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Clear tx fifo */
    tmpVal = BL_RD_REG(SPIx, SPI_FIFO_CONFIG_0);
    BL_WR_REG(SPIx, SPI_FIFO_CONFIG_0, BL_SET_REG_BIT(tmpVal, SPI_TX_FIFO_CLR));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Clear rx fifo and rx fifo overflow/underflow status
 *
 * @param  spiNo: SPI ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_ClrRxFifo(SPI_ID_Type spiNo)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Clear rx fifo */
    tmpVal = BL_RD_REG(SPIx, SPI_FIFO_CONFIG_0);
    BL_WR_REG(SPIx, SPI_FIFO_CONFIG_0, BL_SET_REG_BIT(tmpVal, SPI_RX_FIFO_CLR));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Clear spi interrupt status
 *
 * @param  spiNo: SPI ID type
 * @param  intType: SPI interrupt type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_ClrIntStatus(SPI_ID_Type spiNo, SPI_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Clear certain or all interrupt */
    tmpVal = BL_RD_REG(SPIx, SPI_INT_STS);

    if (SPI_INT_ALL == intType) {
        tmpVal |= 0x1f << SPI_CR_SPI_END_CLR_POS;
    } else {
        tmpVal |= 1 << (intType + SPI_CR_SPI_END_CLR_POS);
    }

    BL_WR_REG(SPIx, SPI_INT_STS, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SPI mask or unmask certain or all interrupt
 *
 * @param  spiNo: SPI ID type
 * @param  intType: SPI interrupt type
 * @param  intMask: SPI interrupt mask value( MASK:disbale interrupt,UNMASK:enable interrupt )
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_IntMask(SPI_ID_Type spiNo, SPI_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(SPIx, SPI_INT_STS);

    /* Mask or unmask certain or all interrupt */
    if (SPI_INT_ALL == intType) {
        if (MASK == intMask) {
            tmpVal |= 0x3f << SPI_CR_SPI_END_MASK_POS;
        } else {
            tmpVal &= ~(0x3f << SPI_CR_SPI_END_MASK_POS);
        }
    } else {
        if (MASK == intMask) {
            tmpVal |= 1 << (intType + SPI_CR_SPI_END_MASK_POS);
        } else {
            tmpVal &= ~(1 << (intType + SPI_CR_SPI_END_MASK_POS));
        }
    }

    /* Write back */
    BL_WR_REG(SPIx, SPI_INT_STS, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Install spi interrupt callback function
 *
 * @param  spiNo: SPI ID type
 * @param  intType: SPI interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return SUCCESS
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type SPI_Int_Callback_Install(SPI_ID_Type spiNo, SPI_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_INT_TYPE(intType));

    spiIntCbfArra[spiNo][intType] = cbFun;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  SPI send datas
 *
 * @param  spiNo: SPI ID type
 * @param  buff: Buffer of datas
 * @param  length: Length of buffer
 * @param  timeoutType: Enable or disable timeout judgment
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_SendData(SPI_ID_Type spiNo, void *buff, uint32_t length, SPI_Timeout_Type timeoutType)
{
    uint32_t tmpVal;
    uint32_t txLen = 0;
    uint32_t rData;
    uint32_t frameSize = 0;
    uint32_t SPIx = spiAddr[spiNo];
    uint32_t timeoutCnt = SPI_TX_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_TIMEOUT_TYPE(timeoutType));

    /* Get fifo valid width */
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    frameSize = BL_GET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_FRAME_SIZE);

    switch (frameSize) {
        case 0:

            tmpVal = length <= (SPI_TX_FIFO_SIZE) ? length : SPI_TX_FIFO_SIZE;

            /* Fill tx fifo */
            for (; txLen < tmpVal; txLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint8_t *)buff)[txLen]);
            }

            /* Wait receive data and send the rest of the data */
            for (; txLen < length; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                rData |= BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint8_t *)buff)[txLen]);
            }

            /* Wait receive the rest of the data */
            for (txLen = 0; txLen < tmpVal; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                rData |= BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        case 1:

            tmpVal = length <= (SPI_TX_FIFO_SIZE / 2) ? length : (SPI_TX_FIFO_SIZE / 2);

            /* Fill tx fifo */
            for (; txLen < tmpVal; txLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint16_t *)buff)[txLen]);
            }

            /* Wait receive data and send the rest of the data */
            for (; txLen < length; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                rData |= BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint16_t *)buff)[txLen]);
            }

            /* Wait receive the rest of the data */
            for (txLen = 0; txLen < tmpVal; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                rData |= BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        case 2:

        /* Same as case 3 */
        case 3:

            tmpVal = length <= (SPI_TX_FIFO_SIZE / 4) ? length : (SPI_TX_FIFO_SIZE / 4);

            /* Fill tx fifo */
            for (; txLen < tmpVal; txLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint32_t *)buff)[txLen]);
            }

            /* Wait receive data and send the rest of the data */
            for (; txLen < length; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                rData |= BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint32_t *)buff)[txLen]);
            }

            /* Wait receive the rest of the data */
            for (txLen = 0; txLen < tmpVal; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                rData |= BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        default:
            break;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SPI receive datas
 *
 * @param  spiNo: SPI ID type
 * @param  buff: Buffer of datas
 * @param  length: Length of buffer
 * @param  timeoutType: Enable or disable timeout judgment
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_ReceiveData(SPI_ID_Type spiNo, void *buff, uint32_t length, SPI_Timeout_Type timeoutType)
{
    uint32_t tmpVal;
    uint32_t rxLen = 0;
    uint32_t frameSize = 0;
    uint32_t SPIx = spiAddr[spiNo];
    uint32_t timeoutCnt = SPI_RX_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_TIMEOUT_TYPE(timeoutType));

    /* Get fifo valid width */
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    frameSize = BL_GET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_FRAME_SIZE);

    switch (frameSize) {
        case 0:

            tmpVal = length <= (SPI_TX_FIFO_SIZE) ? length : SPI_TX_FIFO_SIZE;

            /* Fill tx fifo with 0 */
            for (rxLen = 0; rxLen < tmpVal; rxLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, 0);
            }

            /* Wait receive data and send the rest of the data 0 */
            for (rxLen = 0; rxLen < length - tmpVal; rxLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint8_t *)buff)[rxLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, 0);
            }

            /* Wait receive the rest of the data */
            for (; rxLen < length; rxLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint8_t *)buff)[rxLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        case 1:

            tmpVal = length <= (SPI_TX_FIFO_SIZE / 2) ? length : (SPI_TX_FIFO_SIZE / 2);

            /* Fill tx fifo with 0 */
            for (rxLen = 0; rxLen < tmpVal; rxLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, 0);
            }

            /* Wait receive data and send the rest of the data 0 */
            for (rxLen = 0; rxLen < length - tmpVal; rxLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint16_t *)buff)[rxLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, 0);
            }

            /* Wait receive the rest of the data */
            for (; rxLen < length; rxLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint16_t *)buff)[rxLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        case 2:

        /* Same as case 3 */
        case 3:

            tmpVal = length <= (SPI_TX_FIFO_SIZE / 4) ? length : (SPI_TX_FIFO_SIZE / 4);

            /* Fill tx fifo with 0 */
            for (rxLen = 0; rxLen < tmpVal; rxLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, 0);
            }

            /* Wait receive data and send the rest of the data 0 */
            for (rxLen = 0; rxLen < length - tmpVal; rxLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint32_t *)buff)[rxLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, 0);
            }

            /* Wait receive the rest of the data */
            for (; rxLen < length; rxLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint32_t *)buff)[rxLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        default:
            break;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SPI send and receive datas at the same time
 *
 * @param  spiNo: SPI ID type
 * @param  sendBuff: Buffer of datas to send
 * @param  recvBuff: Buffer of datas received
 * @param  length: Length of buffer
 * @param  timeoutType: Enable or disable timeout judgment
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type SPI_SendRecvData(SPI_ID_Type spiNo, void *sendBuff, void *recvBuff, uint32_t length, SPI_Timeout_Type timeoutType)
{
    uint32_t tmpVal;
    uint32_t txLen = 0;
    uint32_t frameSize = 0;
    uint32_t SPIx = spiAddr[spiNo];
    uint32_t timeoutCnt = SPI_RX_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_TIMEOUT_TYPE(timeoutType));

    /* Get fifo valid width */
    tmpVal = BL_RD_REG(SPIx, SPI_CONFIG);
    frameSize = BL_GET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_FRAME_SIZE);

    switch (frameSize) {
        case 0:

            tmpVal = length <= (SPI_TX_FIFO_SIZE) ? length : SPI_TX_FIFO_SIZE;

            /* Fill tx fifo */
            for (; txLen < tmpVal; txLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint8_t *)sendBuff)[txLen]);
            }

            /* Wait receive data and send the rest of the data */
            for (; txLen < length; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint8_t *)recvBuff)[txLen - tmpVal] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint8_t *)sendBuff)[txLen]);
            }

            /* Wait receive the rest of the data */
            for (txLen = 0; txLen < tmpVal; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint8_t *)recvBuff)[length - tmpVal + txLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        case 1:

            tmpVal = length <= (SPI_TX_FIFO_SIZE / 2) ? length : (SPI_TX_FIFO_SIZE / 2);

            /* Fill tx fifo */
            for (; txLen < tmpVal; txLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint16_t *)sendBuff)[txLen]);
            }

            /* Wait receive data and send the rest of the data */
            for (; txLen < length; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint16_t *)recvBuff)[txLen - tmpVal] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint16_t *)sendBuff)[txLen]);
            }

            /* Wait receive the rest of the data */
            for (txLen = 0; txLen < tmpVal; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint16_t *)recvBuff)[length - tmpVal + txLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        case 2:

        /* Same as case 3 */
        case 3:

            tmpVal = length <= (SPI_TX_FIFO_SIZE / 4) ? length : (SPI_TX_FIFO_SIZE / 4);

            /* Fill tx fifo */
            for (; txLen < tmpVal; txLen++) {
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint32_t *)sendBuff)[txLen]);
            }

            /* Wait receive data and send the rest of the data */
            for (; txLen < length; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint32_t *)recvBuff)[txLen - tmpVal] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
                BL_WR_REG(SPIx, SPI_FIFO_WDATA, ((uint32_t *)sendBuff)[txLen]);
            }

            /* Wait receive the rest of the data */
            for (txLen = 0; txLen < tmpVal; txLen++) {
                timeoutCnt = SPI_RX_TIMEOUT_COUNT;

                while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT) == 0) {
                    if (timeoutType) {
                        timeoutCnt--;

                        if (timeoutCnt == 0) {
                            return TIMEOUT;
                        }
                    }
                }

                ((uint32_t *)recvBuff)[length - tmpVal + txLen] = BL_RD_REG(SPIx, SPI_FIFO_RDATA);
            }

            break;

        default:
            break;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get tx fifo available count value function
 *
 * @param  spiNo: SPI ID type
 *
 * @return Count value
 *
*******************************************************************************/
uint8_t SPI_GetTxFifoCount(SPI_ID_Type spiNo)
{
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Get count value */
    return BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_TX_FIFO_CNT);
}

/****************************************************************************/ /**
 * @brief  Get rx fifo available count value function
 *
 * @param  spiNo: SPI ID type
 *
 * @return Count value
 *
*******************************************************************************/
uint8_t SPI_GetRxFifoCount(SPI_ID_Type spiNo)
{
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Get count value */
    return BL_GET_REG_BITS_VAL(BL_RD_REG(SPIx, SPI_FIFO_CONFIG_1), SPI_RX_FIFO_CNT);
}

/****************************************************************************/ /**
 * @brief  Get spi interrupt status
 *
 * @param  spiNo: SPI ID type
 * @param  intType: SPI interrupt type
 *
 * @return Status of interrupt
 *
*******************************************************************************/
BL_Sts_Type SPI_GetIntStatus(SPI_ID_Type spiNo, SPI_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_INT_TYPE(intType));

    /* Get certain or all interrupt status */
    tmpVal = BL_RD_REG(SPIx, SPI_INT_STS);

    if (SPI_INT_ALL == intType) {
        if ((tmpVal & 0x3f) != 0) {
            return SET;
        } else {
            return RESET;
        }
    } else {
        if ((tmpVal & (1U << intType)) != 0) {
            return SET;
        } else {
            return RESET;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Get indicator of spi bus busy
 *
 * @param  spiNo: SPI ID type
 *
 * @return Status of spi bus
 *
*******************************************************************************/
BL_Sts_Type SPI_GetBusyStatus(SPI_ID_Type spiNo)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));

    /* Get bus busy status */
    tmpVal = BL_RD_REG(SPIx, SPI_BUS_BUSY);

    if (BL_IS_REG_BIT_SET(tmpVal, SPI_STS_SPI_BUS_BUSY)) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  Get tx/rx fifo overflow or underflow status
 *
 * @param  spiNo: SPI ID type
 * @param  fifoSts: Select tx/rx overflow or underflow
 *
 * @return Status of tx/rx fifo
 *
*******************************************************************************/
BL_Sts_Type SPI_GetFifoStatus(SPI_ID_Type spiNo, SPI_FifoStatus_Type fifoSts)
{
    uint32_t tmpVal;
    uint32_t SPIx = spiAddr[spiNo];

    /* Check the parameters */
    CHECK_PARAM(IS_SPI_ID_TYPE(spiNo));
    CHECK_PARAM(IS_SPI_FIFOSTATUS_TYPE(fifoSts));

    /* Get tx/rx fifo overflow or underflow status */
    tmpVal = BL_RD_REG(SPIx, SPI_FIFO_CONFIG_0);

    if ((tmpVal & (1U << (fifoSts + SPI_TX_FIFO_OVERFLOW_POS))) != 0) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  SPI0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void SPI0_IRQHandler(void)
{
    SPI_IntHandler(SPI0_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  SPI1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void SPI1_IRQHandler(void)
{
    SPI_IntHandler(SPI0_MM_ID);
}
#endif

/*@} end of group SPI_Public_Functions */

/*@} end of group SPI */

/*@} end of group BL808_Peripheral_Driver */
