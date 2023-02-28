/**
  ******************************************************************************
  * @file    bl808_dac.c
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

#include "bl808_dac.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DAC
 *  @{
 */

/** @defgroup  DAC_Private_Macros
 *  @{
 */
#define GPIP_CLK_SET_DUMMY_WAIT \
    {                           \
        __NOP();                \
        __NOP();                \
        __NOP();                \
        __NOP();                \
        __NOP();                \
        __NOP();                \
        __NOP();                \
        __NOP();                \
    }

/*@} end of group DAC_Private_Macros */

/** @defgroup  DAC_Private_Types
 *  @{
 */

/*@} end of group DAC_Private_Types */

/** @defgroup  DAC_Private_Variables
 *  @{
 */

/*@} end of group DAC_Private_Variables */

/** @defgroup  DAC_Global_Variables
 *  @{
 */

/*@} end of group DAC_Global_Variables */

/** @defgroup  DAC_Private_Fun_Declaration
 *  @{
 */

/*@} end of group DAC_Private_Fun_Declaration */

/** @defgroup  DAC_Private_Functions
 *  @{
 */

/*@} end of group DAC_Private_Functions */

/** @defgroup  DAC_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  DAC initialization
 *
 * @param  cfg: DAC configuration pointer
 *
 * @return None
 *
*******************************************************************************/
void GLB_DAC_Init(GLB_DAC_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_DAC_REF_SEL_TYPE(cfg->refSel));

    /* Set DAC config */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_REF_SEL, cfg->refSel);

    if (ENABLE == cfg->resetChanA) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPDACA_RSTN_ANA);
        tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }

    if (ENABLE == cfg->resetChanB) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPDACB_RSTN_ANA);
        tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }

    /* Clear reset */
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDACA_RSTN_ANA);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDACB_RSTN_ANA);
    tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DAC channel A initialization
 *
 * @param  cfg: DAC channel configuration pointer
 *
 * @return None
 *
*******************************************************************************/
void GLB_DAC_Set_ChanA_Config(GLB_DAC_Chan_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_DAC_CHAN_TYPE(cfg->outMux));

    /* Set channel A config */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_A_OUTMUX, cfg->outMux);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_IOA_EN, cfg->outputEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_A_EN, cfg->chanEn);

    tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DAC channel B initialization
 *
 * @param  cfg: DAC channel configuration pointer
 *
 * @return None
 *
*******************************************************************************/
void GLB_DAC_Set_ChanB_Config(GLB_DAC_Chan_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_DAC_CHAN_TYPE(cfg->outMux));

    /* Set channel A config */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_B_OUTMUX, cfg->outMux);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_IOB_EN, cfg->outputEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_B_EN, cfg->chanEn);

    tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Select DAC channel B source
 *
 * @param  src: DAC channel B source selection type
 *
 * @return None
 *
*******************************************************************************/
void GPIP_Set_DAC_ChanB_SRC_SEL(GPIP_DAC_ChanB_SRC_Type src)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GPIP_DAC_CHANB_SRC_TYPE(src));

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_CH_B_SEL, src);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Select DAC channel A source
 *
 * @param  src: DAC channel A source selection type
 *
 * @return None
 *
*******************************************************************************/
void GPIP_Set_DAC_ChanA_SRC_SEL(GPIP_DAC_ChanA_SRC_Type src)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GPIP_DAC_CHANA_SRC_TYPE(src));

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_CH_A_SEL, src);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Enable DAC channel B
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void GPIP_DAC_ChanB_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPDAC_EN);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Disable DAC channel B
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void GPIP_DAC_ChanB_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPDAC_EN);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Enable DAC channel A
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void GPIP_DAC_ChanA_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPDAC_EN);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Disable DAC channel A
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void GPIP_DAC_ChanA_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPDAC_EN);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Select DAC DMA TX format
 *
 * @param  fmt: DAC DMA TX format selection type
 *
 * @return None
 *
*******************************************************************************/
void GPIP_Set_DAC_DMA_TX_FORMAT_SEL(GPIP_DAC_DMA_TX_FORMAT_Type fmt)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GPIP_DAC_DMA_TX_FORMAT_TYPE(fmt));

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_DMA_FORMAT, fmt);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Enable DAC DMA TX
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void GPIP_Set_DAC_DMA_TX_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPDAC_DMA_TX_EN);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Disable DAC DMA TX
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void GPIP_Set_DAC_DMA_TX_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPDAC_DMA_TX_EN);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Disable DAC DMA TX
 *
 * @param  data: The data to be send
 *
 * @return None
 *
*******************************************************************************/
void GPIP_DAC_DMA_WriteData(uint32_t data)
{
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_DMA_WDATA, data);
}

/****************************************************************************/ /**
 * @brief  AON and GPIP DAC config
 *
 * @param  cfg: AON and GPIP DAC configuration
 *
 * @return config success or not
 *
*******************************************************************************/
BL_Err_Type GLB_GPIP_DAC_Init(GLB_GPIP_DAC_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_DAC_REF_SEL_TYPE(cfg->refSel));
    CHECK_PARAM(IS_GPIP_DAC_MOD_TYPE(cfg->div));
    CHECK_PARAM(IS_GPIP_DAC_DMA_TX_FORMAT_TYPE(cfg->dmaFmt));

    /* AON Set DAC config */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_REF_SEL, cfg->refSel);

    if (ENABLE == cfg->resetChanA) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPDACA_RSTN_ANA);
        tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }

    if (ENABLE == cfg->resetChanB) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPDACB_RSTN_ANA);
        tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }

    /* AON Clear reset */
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDACA_RSTN_ANA);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDACB_RSTN_ANA);
    tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);

    /* GPIP Set DAC config */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_MODE, cfg->div);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

    /* GPIP Set DMA config */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_DMA_TX_EN, cfg->dmaEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_DMA_FORMAT, cfg->dmaFmt);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  AON and GPIP DAC channel A config
 *
 * @param  cfg: AON and GPIP DAC channel A configuration
 *
 * @return None
 *
*******************************************************************************/
void GLB_GPIP_DAC_Set_ChanA_Config(GLB_GPIP_DAC_ChanA_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GPIP_DAC_CHANA_SRC_TYPE(cfg->src));

    /* GPIP select source */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_CH_A_SEL, cfg->src);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

    /* GPIP enable or disable channel */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_EN, cfg->chanEn);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

    /* AON enable or disable channel */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_IOA_EN, cfg->outputEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_A_EN, cfg->chanCovtEn);
    tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  AON and GPIP DAC channel B config
 *
 * @param  cfg: AON and GPIP DAC channel B configuration
 *
 * @return None
 *
*******************************************************************************/
void GLB_GPIP_DAC_Set_ChanB_Config(GLB_GPIP_DAC_ChanB_Cfg_Type *cfg)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GPIP_DAC_CHANB_SRC_TYPE(cfg->src));

    /* GPIP select source */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_CH_B_SEL, cfg->src);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

    /* GPIP enable or disable channel */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_EN, cfg->chanEn);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

    /* AON enable or disable channel */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_IOB_EN, cfg->outputEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_B_EN, cfg->chanCovtEn);
    tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DAC channel A set value
 *
 * @param  val: DAC value
 *
 * @return None
 *
*******************************************************************************/
void GLB_DAC_Set_ChanA_Value(uint16_t val)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_A_DATA, val);
    tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG3, tmpVal);
}

/****************************************************************************/ /**
 * @brief  DAC channel B set value
 *
 * @param  val: DAC value
 *
 * @return None
 *
*******************************************************************************/
void GLB_DAC_Set_ChanB_Value(uint16_t val)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_B_DATA, val);
    tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG3, tmpVal);
}

/*@} end of group DAC_Public_Functions */

/*@} end of group DAC */

/*@} end of group BL808_Peripheral_Driver */
