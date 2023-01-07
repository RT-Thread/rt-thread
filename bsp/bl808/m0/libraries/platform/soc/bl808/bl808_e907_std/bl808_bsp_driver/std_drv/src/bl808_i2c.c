/**
  ******************************************************************************
  * @file    bl808_i2c.c
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

#include "bl808_i2c.h"
#include "bl808_glb.h"
#include "bl808_clock.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  I2C
 *  @{
 */

/** @defgroup  I2C_Private_Macros
 *  @{
 */
#define I2C_FIFO_STATUS_TIMEOUT (320 * 1000 * 2)
#define PUT_UINT32_LE(n, b, i)               \
    {                                        \
        (b)[(i)] = (uint8_t)((n));           \
        (b)[(i) + 1] = (uint8_t)((n) >> 8);  \
        (b)[(i) + 2] = (uint8_t)((n) >> 16); \
        (b)[(i) + 3] = (uint8_t)((n) >> 24); \
    }

/*@} end of group I2C_Private_Macros */

/** @defgroup  I2C_Private_Types
 *  @{
 */

/*@} end of group I2C_Private_Types */

/** @defgroup  I2C_Private_Variables
 *  @{
 */
static const uint32_t i2cAddr[4] = { I2C0_BASE, I2C1_BASE, I2C2_BASE, I2C3_BASE };
#ifndef BFLB_USE_HAL_DRIVER
intCallback_Type *i2cIntCbfArra[I2C_ID_MAX][I2C_INT_ALL] = { { NULL } };
#endif

/*@} end of group I2C_Private_Variables */

/** @defgroup  I2C_Global_Variables
 *  @{
 */

/*@} end of group I2C_Global_Variables */

/** @defgroup  I2C_Private_Fun_Declaration
 *  @{
 */

/*@} end of group I2C_Private_Fun_Declaration */

/** @defgroup  I2C_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  I2C interrupt handler
 *
 * @param  i2cNo: I2C ID type
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static void I2C_IntHandler(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);

    if (BL_IS_REG_BIT_SET(tmpVal, I2C_END_INT)) {
        if (i2cIntCbfArra[i2cNo][I2C_TRANS_END_INT] != NULL) {
            /* Call the callback function */
            i2cIntCbfArra[i2cNo][I2C_TRANS_END_INT]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, I2C_TXF_INT)) {
        if (i2cIntCbfArra[i2cNo][I2C_TX_FIFO_READY_INT] != NULL) {
            /* Call the callback function */
            i2cIntCbfArra[i2cNo][I2C_TX_FIFO_READY_INT]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, I2C_RXF_INT)) {
        if (i2cIntCbfArra[i2cNo][I2C_RX_FIFO_READY_INT] != NULL) {
            /* Call the callback function */
            i2cIntCbfArra[i2cNo][I2C_RX_FIFO_READY_INT]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, I2C_NAK_INT)) {
        if (i2cIntCbfArra[i2cNo][I2C_NACK_RECV_INT] != NULL) {
            /* Call the callback function */
            i2cIntCbfArra[i2cNo][I2C_NACK_RECV_INT]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, I2C_ARB_INT)) {
        if (i2cIntCbfArra[i2cNo][I2C_ARB_LOST_INT] != NULL) {
            /* Call the callback function */
            i2cIntCbfArra[i2cNo][I2C_ARB_LOST_INT]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, I2C_FER_INT)) {
        if (i2cIntCbfArra[i2cNo][I2C_FIFO_ERR_INT] != NULL) {
            /* Call the callback function */
            i2cIntCbfArra[i2cNo][I2C_FIFO_ERR_INT]();
        }
    }
}
#endif

/*@} end of group I2C_Private_Functions */

/** @defgroup  I2C_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  I2C write word data
 *
 * @param  i2cNo: I2C ID type
 * @param  data: Data word
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type I2C_SendWord(I2C_ID_Type i2cNo, uint32_t data)
{
    uint32_t I2Cx = i2cAddr[i2cNo];
    uint32_t timeOut = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    timeOut = I2C_FIFO_STATUS_TIMEOUT;

    while (BL_GET_REG_BITS_VAL(BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_1), I2C_TX_FIFO_CNT) == 0) {
        timeOut--;
        if (timeOut == 0) {
            return TIMEOUT;
        }
    }

    BL_WR_REG(I2Cx, I2C_FIFO_WDATA, data);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  I2C read word data
 *
 * @param  i2cNo: I2C ID type
 *
 * @return word data
 *
*******************************************************************************/
BL_Err_Type I2C_RecieveWord(I2C_ID_Type i2cNo, uint32_t *recvBuff)
{
    uint32_t I2Cx = i2cAddr[i2cNo];
    uint32_t timeOut = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    timeOut = I2C_FIFO_STATUS_TIMEOUT;

    while (BL_GET_REG_BITS_VAL(BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_1), I2C_RX_FIFO_CNT) == 0) {
        timeOut--;

        if (timeOut == 0) {
            return TIMEOUT;
        }
    }

    *recvBuff = BL_RD_REG(I2Cx, I2C_FIFO_RDATA);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  I2C enable
 *
 * @param  i2cNo: I2C ID type
 *
 * @return None
 *
*******************************************************************************/
void I2C_Enable(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_M_EN);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  I2C disable
 *
 * @param  i2cNo: I2C ID type
 *
 * @return None
 *
*******************************************************************************/
void I2C_Disable(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_M_EN);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);

    /* Clear I2C fifo */
    tmpVal = BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_TX_FIFO_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_RX_FIFO_CLR);
    BL_WR_REG(I2Cx, I2C_FIFO_CONFIG_0, tmpVal);

    /* Clear I2C interrupt status */
    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_END_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_NAK_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_ARB_CLR);
    BL_WR_REG(I2Cx, I2C_INT_STS, tmpVal);
}

/****************************************************************************/ /**
 * @brief  I2C set global reset function
 *
 * @param  i2cNo: I2C ID type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type I2C_DeInit(I2C_ID_Type i2cNo)
{
    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    if (i2cNo == I2C0_ID || i2cNo == I2C1_ID) {
        GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_I2C);
    } else if (i2cNo == I2C0_MM_ID) {
        GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_I2C0);
    } else if (i2cNo == I2C1_MM_ID) {
        GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_I2C1);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  I2C init function
 *
 * @param  i2cNo: I2C ID type
 * @param  direct: I2C read or write direct
 * @param  cfg: I2C transfer config struct
 *
 * @return None
 *
*******************************************************************************/
void I2C_Init(I2C_ID_Type i2cNo, I2C_Direction_Type direct, I2C_Transfer_Cfg *cfg)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    /* set i2c clk,default is 400000,max support clk is 400000 */
    if (cfg->clk == 0 || cfg->clk > 400000){
        I2C_ClockSet(i2cNo, 400000);
    } else {
        I2C_ClockSet(i2cNo, cfg->clk);
    }

    /* Disable clock gate when use I2C0 */
    if (I2C0_ID == i2cNo) {
        GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_I2C);
    } else if (I2C1_ID == i2cNo) {
        GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_I2C1);
    } 

    /* I2C write config */
    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);

    if (direct == I2C_WRITE) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_PKT_DIR);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_PKT_DIR);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SLV_ADDR, cfg->slaveAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_10B_ADDR_EN, cfg->slaveAddr10Bit);

    if (cfg->subAddrSize > 0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_SUB_ADDR_EN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SUB_ADDR_BC, cfg->subAddrSize - 1);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_SUB_ADDR_EN);
    }

    /* align clock when 1 master*/
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SCL_SYNC_EN, DISABLE);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_LEN, cfg->dataSize - 1);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);

    /* Set sub address */
    BL_WR_REG(I2Cx, I2C_SUB_ADDR, cfg->subAddr);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(I2C0_IRQn, I2C0_IRQHandler);
    Interrupt_Handler_Register(I2C1_IRQn, I2C1_IRQHandler);
    Interrupt_Handler_Register(I2C2_IRQn, I2C2_IRQHandler);
    Interrupt_Handler_Register(I2C3_IRQn, I2C2_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  Set de-glitch function cycle count value
 *
 * @param  i2cNo: I2C ID type
 * @param  cnt: De-glitch function cycle count
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type I2C_SetDeglitchCount(I2C_ID_Type i2cNo, uint8_t cnt)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);

    if (cnt > 0) {
        /* enable de-glitch function */
        tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_DEG_EN);
    } else if (cnt == 0) {
        /* disable de-glitch function */
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_DEG_EN);
    } else {
        return ERROR;
    }

    /* Set count value */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_DEG_CNT, cnt);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set i2c prd
 *
 * @param  i2cNo: I2C ID type
 * @param  phase: I2C phase value
 *
 * @return None
 *
*******************************************************************************/
void I2C_SetPrd(I2C_ID_Type i2cNo, uint8_t phase)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    //phase_cycles = (32000000 / phase / 4) - 1;
    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_START);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_0, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_1, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_2, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_3, phase);
    BL_WR_REG(I2Cx, I2C_PRD_START, tmpVal);
    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_STOP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_0, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_1, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_2, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_3, phase);
    BL_WR_REG(I2Cx, I2C_PRD_STOP, tmpVal);
    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_DATA);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_0, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_1, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_2, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_3, phase);
    BL_WR_REG(I2Cx, I2C_PRD_DATA, tmpVal);
}

/****************************************************************************/ /**
 * @brief  I2C set scl output clock
 *
 * @param  i2cNo: I2C ID type
 * @param  clk: Clock set
 *
 * @return None
 *
*******************************************************************************/
void I2C_ClockSet(I2C_ID_Type i2cNo, uint32_t clk)
{
    uint32_t bclk = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    if (i2cNo == I2C0_ID || i2cNo == I2C1_ID) {
        bclk = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_PBCLK);

        if (clk >= 100000) {
            GLB_Set_I2C_CLK(1, GLB_I2C_CLK_BCLK, 0);
            I2C_SetPrd(i2cNo, bclk / (clk * 4) - 1);
        } else if (clk >= 8000) {
            GLB_Set_I2C_CLK(1, GLB_I2C_CLK_BCLK, 9);
            I2C_SetPrd(i2cNo, bclk / 10 / (clk * 4) - 1);
        } else if (clk >= 800) {
            GLB_Set_I2C_CLK(1, GLB_I2C_CLK_BCLK, 99);
            I2C_SetPrd(i2cNo, bclk / 100 / (clk * 4) - 1);
        } else {
            GLB_Set_I2C_CLK(1, GLB_I2C_CLK_BCLK, 255);
            I2C_SetPrd(i2cNo, bclk / 256 / (clk * 4) - 1);
        }
    } else if (i2cNo == I2C0_MM_ID) {
        bclk = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_PBCLK);

        if (clk >= 100000) {
            GLB_Set_DSP_I2C0_CLK(1, 1, 1, 0);
            I2C_SetPrd(i2cNo, bclk / (clk * 4) - 1);
        } else if (clk >= 8000) {
            GLB_Set_DSP_I2C0_CLK(1, 1, 1, 9);
            I2C_SetPrd(i2cNo, bclk / 10 / (clk * 4) - 1);
        } else if (clk >= 800) {
            GLB_Set_DSP_I2C0_CLK(1, 1, 1, 99);
            I2C_SetPrd(i2cNo, bclk / 100 / (clk * 4) - 1);
        } else {
            GLB_Set_DSP_I2C0_CLK(1, 1, 1, 255);
            I2C_SetPrd(i2cNo, bclk / 256 / (clk * 4) - 1);
        }
    } else if (i2cNo == I2C1_MM_ID) {
        bclk = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_PBCLK);

        if (clk >= 100000) {
            GLB_Set_DSP_I2C1_CLK(1, 1, 1, 0);
            I2C_SetPrd(i2cNo, bclk / (clk * 4) - 1);
        } else if (clk >= 8000) {
            GLB_Set_DSP_I2C1_CLK(1, 1, 1, 9);
            I2C_SetPrd(i2cNo, bclk / 10 / (clk * 4) - 1);
        } else if (clk >= 800) {
            GLB_Set_DSP_I2C1_CLK(1, 1, 1, 99);
            I2C_SetPrd(i2cNo, bclk / 100 / (clk * 4) - 1);
        } else {
            GLB_Set_DSP_I2C1_CLK(1, 1, 1, 255);
            I2C_SetPrd(i2cNo, bclk / 256 / (clk * 4) - 1);
        }
    }
}

/****************************************************************************/ /**
 * @brief  I2C set scl sync
 *
 * @param  i2cNo: I2C ID type
 * @param  enable: Enable or disable I2C scl sync
 *
 * @return None
 *
*******************************************************************************/
void I2C_SetSclSync(I2C_ID_Type i2cNo, uint8_t enable)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_SCL_SYNC_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_SCL_SYNC_EN);
    }

    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get i2c busy state
 *
 * @param  i2cNo: I2C ID type
 *
 * @return RESET or SET
 *
*******************************************************************************/
BL_Sts_Type I2C_IsBusy(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_BUS_BUSY);
    return ((BL_IS_REG_BIT_SET(tmpVal, I2C_STS_I2C_BUS_BUSY)) ? SET : RESET);
}

/****************************************************************************/ /**
 * @brief  Get i2c transfer end state
 *
 * @param  i2cNo: I2C ID type
 *
 * @return RESET or SET
 *
*******************************************************************************/
BL_Sts_Type I2C_TransferEndStatus(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);
    return ((BL_IS_REG_BIT_SET(tmpVal, I2C_END_INT)) ? SET : RESET);
}

/****************************************************************************/ /**
 * @brief  I2C master write block data
 *
 * @param  i2cNo: I2C ID type
 * @param  cfg: I2C transfer config struct
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type I2C_MasterSendBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg)
{
    uint8_t i;
    uint32_t timeOut = 0;
    uint32_t temp = 0;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    I2C_Disable(i2cNo);
    I2C_Init(i2cNo, I2C_WRITE, cfg);

    /* Set I2C write data */
    for (i = 0; i < cfg->dataSize; i++) {
        temp += (cfg->data[i] << ((i % 4) * 8));

        if ((i + 1) % 4 == 0) {
            timeOut = I2C_FIFO_STATUS_TIMEOUT;

            while (BL_GET_REG_BITS_VAL(BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_1), I2C_TX_FIFO_CNT) == 0) {
                timeOut--;

                if (timeOut == 0) {
                    I2C_Disable(i2cNo);
                    return TIMEOUT;
                }
            }

            BL_WR_REG(I2Cx, I2C_FIFO_WDATA, temp);
            if(BL_GET_REG_BITS_VAL(BL_RD_REG(I2Cx, I2C_CONFIG), I2C_CR_I2C_M_EN) == 0) {
                I2C_Enable(i2cNo);
            }
            temp = 0;
        }
    }

    if ((cfg->dataSize % 4) != 0) {
        timeOut = I2C_FIFO_STATUS_TIMEOUT;

        while (BL_GET_REG_BITS_VAL(BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_1), I2C_TX_FIFO_CNT) == 0) {
            timeOut--;

            if (timeOut == 0) {
                I2C_Disable(i2cNo);
                return TIMEOUT;
            }
        }

        BL_WR_REG(I2Cx, I2C_FIFO_WDATA, temp);
        if(BL_GET_REG_BITS_VAL(BL_RD_REG(I2Cx, I2C_CONFIG), I2C_CR_I2C_M_EN) == 0) {
            I2C_Enable(i2cNo);
        }
    }

    timeOut = I2C_FIFO_STATUS_TIMEOUT;

    while (I2C_IsBusy(i2cNo) || !I2C_TransferEndStatus(i2cNo)) {
        timeOut--;

        if (timeOut == 0) {
            I2C_Disable(i2cNo);
            return TIMEOUT;
        }
    }

    I2C_Disable(i2cNo);
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  I2C master read block data
 *
 * @param  i2cNo: I2C ID type
 * @param  cfg: I2C transfer config struct
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type I2C_MasterReceiveBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg)
{
    uint8_t i = 0;
    uint32_t timeOut = 0;
    uint32_t temp = 0;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    I2C_Disable(i2cNo);
    I2C_Init(i2cNo, I2C_READ, cfg);
    I2C_Enable(i2cNo);

    /* Read I2C data */
    while (cfg->dataSize - i >= 4) {
        timeOut = I2C_FIFO_STATUS_TIMEOUT;

        while (BL_GET_REG_BITS_VAL(BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_1), I2C_RX_FIFO_CNT) == 0) {
            timeOut--;

            if (timeOut == 0) {
                I2C_Disable(i2cNo);
                return TIMEOUT;
            }
        }

        temp = BL_RD_REG(I2Cx, I2C_FIFO_RDATA);
        PUT_UINT32_LE(temp, cfg->data, i);
        i += 4;
    }

    if (i < cfg->dataSize) {
        timeOut = I2C_FIFO_STATUS_TIMEOUT;

        while (BL_GET_REG_BITS_VAL(BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_1), I2C_RX_FIFO_CNT) == 0) {
            timeOut--;

            if (timeOut == 0) {
                I2C_Disable(i2cNo);
                return TIMEOUT;
            }
        }

        temp = BL_RD_REG(I2Cx, I2C_FIFO_RDATA);

        while (i < cfg->dataSize) {
            cfg->data[i] = (temp & 0xff);
            temp = (temp >> 8);
            i++;
        }
    }

    timeOut = I2C_FIFO_STATUS_TIMEOUT;

    while (I2C_IsBusy(i2cNo) || !I2C_TransferEndStatus(i2cNo)) {
        timeOut--;

        if (timeOut == 0) {
            I2C_Disable(i2cNo);
            return TIMEOUT;
        }
    }

    I2C_Disable(i2cNo);
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Mask/Unmask the I2C interrupt
 *
 * @param  i2cNo: I2C ID type
 * @param  intType: Specifies the interrupt type
 * @param  intMask: Enable/Disable Specified interrupt type
 *
 * @return None
 *
*******************************************************************************/
void I2C_IntMask(I2C_ID_Type i2cNo, I2C_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));
    CHECK_PARAM(IS_I2C_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);

    switch (intType) {
        case I2C_TRANS_END_INT:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_END_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_END_MASK);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_END_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_END_MASK);
            }

            break;

        case I2C_TX_FIFO_READY_INT:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_TXF_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_TXF_MASK);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_TXF_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_TXF_MASK);
            }

            break;

        case I2C_RX_FIFO_READY_INT:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_RXF_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_RXF_MASK);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_RXF_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_RXF_MASK);
            }

            break;

        case I2C_NACK_RECV_INT:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_NAK_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_NAK_MASK);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_NAK_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_NAK_MASK);
            }

            break;

        case I2C_ARB_LOST_INT:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_ARB_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_ARB_MASK);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_ARB_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_ARB_MASK);
            }

            break;

        case I2C_FIFO_ERR_INT:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_FER_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_FER_MASK);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_FER_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_FER_MASK);
            }

            break;

        case I2C_INT_ALL:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_END_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_TXF_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_RXF_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_NAK_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_ARB_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_FER_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_END_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_TXF_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_RXF_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_NAK_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_ARB_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_FER_MASK);
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_END_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_TXF_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_RXF_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_NAK_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_ARB_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_FER_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_END_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_TXF_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_RXF_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_NAK_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_ARB_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_FER_MASK);
            }

            break;

        default:
            break;
    }

    BL_WR_REG(I2Cx, I2C_INT_STS, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Install I2C interrupt callback function
 *
 * @param  i2cNo: I2C ID type
 * @param  intType: Specifies the interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void I2C_Int_Callback_Install(I2C_ID_Type i2cNo, I2C_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));
    CHECK_PARAM(IS_I2C_INT_TYPE(intType));

    i2cIntCbfArra[i2cNo][intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  I2C0 IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void I2C0_IRQHandler(void)
{
    I2C_IntHandler(I2C0_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  I2C1 IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void I2C1_IRQHandler(void)
{
    I2C_IntHandler(I2C1_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  I2C2 IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void I2C2_IRQHandler(void)
{
    I2C_IntHandler(I2C0_MM_ID);
}
#endif

/****************************************************************************/ /**
 * @brief  I2C3 IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void I2C3_IRQHandler(void)
{
    I2C_IntHandler(I2C1_MM_ID);
}
#endif

/*@} end of group I2C_Public_Functions */

/*@} end of group I2C */

/*@} end of group BL808_Peripheral_Driver */
