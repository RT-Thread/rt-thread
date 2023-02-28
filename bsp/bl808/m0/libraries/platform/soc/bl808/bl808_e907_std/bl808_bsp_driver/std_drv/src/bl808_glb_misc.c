/**
  ******************************************************************************
  * @file    bl808_glb_misc.c
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

#include "bl808_clock.h"
#include "bl808_glb.h"
#include "bl808_aon.h"
#include "bl808_hbn.h"
#include "bl808_pds.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GLB
 *  @{
 */

/** @defgroup  GLB_Private_Macros
 *  @{
 */



/*@} end of group GLB_Private_Macros */

/** @defgroup  GLB_Private_Types
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *glbBmxToIntCbfArra[BMX_TO_INT_ALL] = { NULL };
#endif

static BL_Err_Type GLB_Get_And_Clr_First_Set_From_U64(uint64_t *val, uint32_t *bit);

/*@} end of group GLB_Private_Types */

/** @defgroup  GLB_Private_Variables
 *  @{
 */

/*@} end of group GLB_Private_Variables */

/** @defgroup  GLB_Global_Variables
 *  @{
 */

/*@} end of group GLB_Global_Variables */

/** @defgroup  GLB_Private_Fun_Declaration
 *  @{
 */

/*@} end of group GLB_Private_Fun_Declaration */

/** @defgroup  GLB_Private_Functions
 *  @{
 */

/*@} end of group GLB_Private_Functions */

/** @defgroup  GLB_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  GLB set display clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  srcClk: source clock type
 * @param  evenDiv: divider in even number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Display_CLK(uint8_t enable, GLB_DISP_CLK_Type srcClk, uint8_t evenDiv)
{
    uint32_t tmpVal = 0;
    uint32_t evenNum = 0;

    CHECK_PARAM(IS_GLB_DISP_CLK_TYPE(srcClk));
    CHECK_PARAM((evenDiv <= 0x7F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG1, tmpVal);

    if ((evenDiv >= 8) && (evenDiv <= 126)) {
        evenNum = evenDiv & ~(1 << 0);
    } else {
        evenNum = evenDiv;
    }

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG1);
    if(enable){
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN);
    }else{
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_EVEN_DIV_RATIO, evenNum);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB enable or disable ethernet clock
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Ethernet_CLK_From_UHSPLL(uint8_t enable)

{
    uint32_t tmpVal = 0;

    /* uhspll_even_div_en */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_UHS_PLL_CFG1);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_UHSPLL_EVEN_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_UHSPLL_EVEN_DIV_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_UHS_PLL_CFG1, tmpVal);

    return SUCCESS;
}



/****************************************************************************/ /**
 * @brief  DSP get MCU interrupt status
 *
 * @param  intType: MCU interrupt type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type GLB_DSP_Get_MCU_IntStatus(GLB_MCU_ALL_INT_Type intType)
{
    CHECK_PARAM(IS_GLB_MCU_ALL_INT_TYPE(intType));

    if (intType < 32) {
        return (BL_RD_REG(GLB_BASE, GLB_CORE_CFG16) & (1 << intType)) ? SET : RESET;
    } else {
        return (BL_RD_REG(GLB_BASE, GLB_CORE_CFG17) & (1 << (intType - 32))) ? SET : RESET;
    }
}

/****************************************************************************/ /**
 * @brief  DSP set MCU interrupt mask
 *
 * @param  intType: MCU interrupt type
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_DSP_Set_MCU_IntMask(GLB_MCU_ALL_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_MCU_ALL_INT_TYPE(intType));

    if (intType < 32) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_CORE_CFG18);
        if (UNMASK != intMask) {
            tmpVal |= (1 << intType);
        } else {
            tmpVal &= ~(1 << intType);
        }
        BL_WR_REG(GLB_BASE, GLB_CORE_CFG18, tmpVal);
    } else {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_CORE_CFG19);
        if (UNMASK != intMask) {
            tmpVal |= (1 << (intType - 32));
        } else {
            tmpVal &= ~(1 << (intType - 32));
        }
        BL_WR_REG(GLB_BASE, GLB_CORE_CFG19, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSP clear MCU interrupt status
 *
 * @param  intType: MCU interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_DSP_Clr_MCU_IntStatus(GLB_MCU_ALL_INT_Type intType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_MCU_ALL_INT_TYPE(intType));

    if (intType < 32) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_CORE_CFG20);
        tmpVal |= (1 << intType);
        BL_WR_REG(GLB_BASE, GLB_CORE_CFG20, tmpVal);
    } else {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_CORE_CFG21);
        tmpVal |= (1 << (intType - 32));
        BL_WR_REG(GLB_BASE, GLB_CORE_CFG21, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSP set LP interrupt enable
 *
 * @param  enable: ENABLE or DISABLE
 * @param  intType: LP interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_DSP_Set_LP_IntEn(uint8_t enable, GLB_LP_ALL_INT_Type intType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_LP_ALL_INT_TYPE(intType));

    if (intType < 32) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_CORE_CFG22);
        if (enable) {
            tmpVal |= (1 << intType);
        } else {
            tmpVal &= ~(1 << intType);
        }
        BL_WR_REG(GLB_BASE, GLB_CORE_CFG22, tmpVal);
    } else {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_CORE_CFG23);
        if (enable) {
            tmpVal |= (1 << (intType - 32));
        } else {
            tmpVal &= ~(1 << (intType - 32));
        }
        BL_WR_REG(GLB_BASE, GLB_CORE_CFG23, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSP get LP interrupt status
 *
 * @param  intType: LP interrupt type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type GLB_DSP_Get_LP_IntStatus(GLB_LP_ALL_INT_Type intType)
{
    CHECK_PARAM(IS_GLB_LP_ALL_INT_TYPE(intType));

    if (intType < 32) {
        return (BL_RD_REG(GLB_BASE, GLB_CORE_CFG24) & (1 << intType)) ? SET : RESET;
    } else {
        return (BL_RD_REG(GLB_BASE, GLB_CORE_CFG25) & (1 << (intType - 32))) ? SET : RESET;
    }
}

/****************************************************************************/ /**
 * @brief  MCU get DSP interrupt status
 *
 * @param  intType: DSP interrupt type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type GLB_MCU_Get_DSP_IntStatus(GLB_DSP_ALL_INT_Type intType)
{
    CHECK_PARAM(IS_GLB_DSP_ALL_INT_TYPE(intType));

    if (intType < 32) {
        return (BL_RD_REG(MM_MISC_BASE, MM_MISC_MM_INT_STA0) & (1 << intType)) ? SET : RESET;
    } else {
        return (BL_RD_REG(MM_MISC_BASE, MM_MISC_MM_INT_STA1) & (1 << (intType - 32))) ? SET : RESET;
    }
}

/****************************************************************************/ /**
 * @brief  MCU set DSP interrupt mask
 *
 * @param  intType: DSP interrupt type
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_MCU_Set_DSP_IntMask(GLB_DSP_ALL_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_ALL_INT_TYPE(intType));

    if (intType < 32) {
        tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_MM_INT_MASK0);
        if (UNMASK != intMask) {
            tmpVal |= (1 << intType);
        } else {
            tmpVal &= ~(1 << intType);
        }
        BL_WR_REG(MM_MISC_BASE, MM_MISC_MM_INT_MASK0, tmpVal);
    } else {
        tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_MM_INT_MASK1);
        if (UNMASK != intMask) {
            tmpVal |= (1 << (intType - 32));
        } else {
            tmpVal &= ~(1 << (intType - 32));
        }
        BL_WR_REG(MM_MISC_BASE, MM_MISC_MM_INT_MASK1, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  MCU clear DSP interrupt status
 *
 * @param  intType: DSP interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_MCU_Clr_DSP_IntStatus(GLB_DSP_ALL_INT_Type intType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_ALL_INT_TYPE(intType));

    if (intType < 32) {
        tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_MM_INT_CLR_0);
        tmpVal |= (1 << intType);
        BL_WR_REG(MM_MISC_BASE, MM_MISC_MM_INT_CLR_0, tmpVal);
    } else {
        tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_MM_INT_CLR_1);
        tmpVal |= (1 << (intType - 32));
        BL_WR_REG(MM_MISC_BASE, MM_MISC_MM_INT_CLR_1, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set MTimer clock
 *
 * @param  enable: enable or disable MTimer clock
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_MCU_MTimer_CLK(uint8_t enable, uint16_t div, uint8_t rst)
{
    uint32_t tmpVal;

    CHECK_PARAM((div <= 0x3FF));

    /* disable MTimer clock first */
    tmpVal = BL_RD_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_EN);
    BL_WR_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC, tmpVal);

    tmpVal = BL_RD_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_RST);
    BL_WR_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC, tmpVal);
    tmpVal = BL_RD_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC);
    tmpVal = BL_SET_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_RST);
    BL_WR_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC, tmpVal);
    tmpVal = BL_RD_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_RST);
    BL_WR_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC, tmpVal);

    tmpVal = BL_RD_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MCU_MISC_REG_MCU_RTC_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_EN);
    }
    BL_WR_REG(MCU_MISC_BASE, MCU_MISC_MCU_E907_RTC, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set MTimer clock
 *
 * @param  enable: enable or disable MTimer clock
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_MTimer_CLK(uint8_t enable, uint16_t div, uint8_t rst)
{
    uint32_t tmpVal;

    CHECK_PARAM((div <= 0x3FF));

    /* disable MTimer clock first */
    tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_CPU_RTC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_MISC_C906_RTC_EN);
    BL_WR_REG(MM_MISC_BASE, MM_MISC_CPU_RTC, tmpVal);

    tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_CPU_RTC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_MISC_C906_RTC_RST);
    BL_WR_REG(MM_MISC_BASE, MM_MISC_CPU_RTC, tmpVal);
    tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_CPU_RTC);
    tmpVal = BL_SET_REG_BIT(tmpVal, MM_MISC_C906_RTC_RST);
    BL_WR_REG(MM_MISC_BASE, MM_MISC_CPU_RTC, tmpVal);
    tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_CPU_RTC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_MISC_C906_RTC_RST);
    BL_WR_REG(MM_MISC_BASE, MM_MISC_CPU_RTC, tmpVal);

    tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_CPU_RTC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_C906_RTC_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_MISC_C906_RTC_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_MISC_C906_RTC_EN);
    }
    BL_WR_REG(MM_MISC_BASE, MM_MISC_CPU_RTC, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set ADC clock
 *
 * @param  enable: enable frequency divider or not
 * @param  clkSel: ADC clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_ADC_CLK(uint8_t enable, GLB_ADC_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_ADC_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3F));

    /* disable ADC clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_ADC_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    BL_WR_REG(GLB_BASE, GLB_ADC_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_ADC_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPADC_32M_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPADC_32M_CLK_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_ADC_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_ADC_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_ADC_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set DMA clock
 *
 * @param  enable: Enable or disable
 * @param  clk: DMA clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DMA_CLK(uint8_t enable, GLB_DMA_CLK_ID_Type clk)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_GLB_DMA_CLK_ID_TYPE(clk));

    if (clk >= GLB_DMA1_CLK_CH0) {
        /* DMA1 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_DMA_CFG1);
        tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, GLB_DMA2_CLK_EN);
        if (enable) {
            tmpVal2 |= (1 << (clk - GLB_DMA1_CLK_CH0));
        } else {
            tmpVal2 &= (~(1 << (clk - GLB_DMA1_CLK_CH0)));
        }
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DMA2_CLK_EN, tmpVal2);
        BL_WR_REG(GLB_BASE, GLB_DMA_CFG1, tmpVal);
    } else {
        /* DMA0 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_DMA_CFG0);
        tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, GLB_DMA_CLK_EN);
        if (enable) {
            tmpVal2 |= (1 << clk);
        } else {
            tmpVal2 &= (~(1 << clk));
        }
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DMA_CLK_EN, tmpVal2);
        BL_WR_REG(GLB_BASE, GLB_DMA_CFG0, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set peripheral DMA cn
 *
 * @param  peri: peripheral
 * @param  cn: cn
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Peripheral_DMA_CN(GLB_PERI_DMA_Type peri, GLB_PERI_DMA_CN_SEL_Type cn)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PERI_DMA_TYPE(peri));
    CHECK_PARAM(IS_GLB_PERI_DMA_CN_SEL_TYPE(cn));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DMA_CFG2);
    switch (cn) {
        case GLB_PERI_DMA_CN_SEL_DMA0:
            tmpVal &= ~(1 << peri);
            break;
        case GLB_PERI_DMA_CN_SEL_DMA1:
            tmpVal |= (1 << peri);
            break;
        default:
            break;
    }
    BL_WR_REG(GLB_BASE, GLB_DMA_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set IR clock divider
 *
 * @param  enable: enable or disable IR clock
 * @param  clkSel: IR clock type
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_IR_CLK(uint8_t enable, GLB_IR_CLK_SRC_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_IR_CLK_SRC_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_IR_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_IR_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_IR_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_IR_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_IR_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_IR_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_IR_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_IR_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_IR_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_IR_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select ir rx gpio (gpio11~gpio13)
 *
 * @param  gpio: IR gpio selected
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_IR_RX_GPIO_Sel(GLB_GPIO_Type gpio)
{
    uint32_t tmpVal = 0;

    /* Select gpio between gpio9 and gpio23 */
    if (gpio > 8 && gpio < 24) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_IR_CFG1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_IR_RX_GPIO_SEL, gpio - 8);
        BL_WR_REG(GLB_BASE, GLB_IR_CFG1, tmpVal);
    }

    /* Close ir rx */
    if (gpio == 0) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_IR_CFG1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_IR_RX_GPIO_SEL, 0);
        BL_WR_REG(GLB_BASE, GLB_IR_CFG1, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable ir led driver
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_IR_LED_Driver_Enable(void)
{
    uint32_t tmpVal = 0;

    /* Enable led driver */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_IR_CFG1);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_PU_LEDDRV);
    BL_WR_REG(GLB_BASE, GLB_IR_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable ir led driver
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_IR_LED_Driver_Disable(void)
{
    uint32_t tmpVal = 0;

    /* Disable led driver */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_IR_CFG1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PU_LEDDRV);
    BL_WR_REG(GLB_BASE, GLB_IR_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set UART2 IO selection
 *
 * @param  ioType: UART2 IO selection type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_UART2_IO_Sel(GLB_UART2_IO_SEL_Type ioType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_UART2_IO_SEL_TYPE(ioType));

    /* Set uart2 io selection */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UART2_IO_SEL, ioType);
    BL_WR_REG(GLB_BASE, GLB_UART_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set UART clock
 *
 * @param  enable: Enable or disable UART clock
 * @param  clkSel: UART clock type
 * @param  div: UART clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_UART_CLK(uint8_t enable, HBN_UART_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0x7));
    CHECK_PARAM(IS_HBN_UART_CLK_TYPE(clkSel));

    /* disable UART clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_UART_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_UART_CFG0, tmpVal);

    /* Set div */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UART_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_UART_CFG0, tmpVal);

    /* Select clock source for uart */
    HBN_Set_UART_CLK_Sel(clkSel);

    /* Set enable or disable */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_UART_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_UART_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_UART_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select UART signal function
 *
 * @param  sig: UART signal
 * @param  fun: UART function
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_UART_Fun_Sel(GLB_UART_SIG_Type sig, GLB_UART_SIG_FUN_Type fun)
{
    uint32_t sig_pos = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_UART_SIG_TYPE(sig));
    CHECK_PARAM(IS_GLB_UART_SIG_FUN_TYPE(fun));

    if (sig < GLB_UART_SIG_8) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_CFG1);
        sig_pos = (sig * 4);
        /* Clear original val */
        tmpVal &= (~(0xf << sig_pos));
        /* Set new value */
        tmpVal |= (fun << sig_pos);
        BL_WR_REG(GLB_BASE, GLB_UART_CFG1, tmpVal);
    } else {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_CFG2);
        sig_pos = ((sig - 8) * 4);
        /* Clear original val */
        tmpVal &= (~(0xf << sig_pos));
        /* Set new value */
        tmpVal |= (fun << sig_pos);
        BL_WR_REG(GLB_BASE, GLB_UART_CFG2, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set sflash clock
 *
 * @param  enable: enable or disable sflash clock
 * @param  clkSel: sflash clock type
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_SF_CLK(uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_SFLASH_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x7));

    /* disable SFLASH clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SF_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SF_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_SF_CFG0, tmpVal);

    if (clkSel == GLB_SFLASH_CLK_100M_CPUPLL) {
        GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_CPUPLL_100M);
    }

    /* clock divider */
    /* Select flash clock, all Flash CLKs are divied by PLL_480M */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SF_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_DIV, div);
    switch (clkSel) {
        case GLB_SFLASH_CLK_120M_WIFIPLL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x0);
            break;
        case GLB_SFLASH_CLK_XTAL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x1);
            break;
        case GLB_SFLASH_CLK_100M_CPUPLL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x3);
            break;
        case GLB_SFLASH_CLK_80M_MUXPLL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x1);
            break;
        case GLB_SFLASH_CLK_BCLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x2);
            break;
        case GLB_SFLASH_CLK_96M_WIFIPLL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x3);
            break;
        default:
            break;
    }
    BL_WR_REG(GLB_BASE, GLB_SF_CFG0, tmpVal);

    /* enable or disable flash clock */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SF_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SF_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SF_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_SF_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set I2C clock
 *
 * @param  enable: Enable or disable I2C clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_I2C_CLK(uint8_t enable, GLB_I2C_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_I2C_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_I2C_CLK_SEL, clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_I2C_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set I2S clock
 *
 * @param  refClkEn: ref clock ENABLE or DISABLE
 * @param  refClkDiv: divider
 * @param  inRef: di ref clock
 * @param  outRef: do ref clock
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_I2S_CLK(uint8_t refClkEn, uint8_t refClkDiv, GLB_I2S_DI_REF_CLK_Type inRef, GLB_I2S_DO_REF_CLK_Type outRef)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((refClkDiv <= 0x3F));
    CHECK_PARAM(IS_GLB_I2S_DI_REF_CLK_TYPE(inRef));
    CHECK_PARAM(IS_GLB_I2S_DO_REF_CLK_TYPE(outRef));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_I2S_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_I2S_DO_REF_CLK_SEL, outRef);
    if (refClkEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_I2S_REF_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_I2S_REF_CLK_EN);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_I2S_DI_REF_CLK_SEL, inRef);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_I2S_REF_CLK_DIV, refClkDiv);
    BL_WR_REG(GLB_BASE, GLB_I2S_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set SPI clock
 *
 * @param  enable: Enable or disable SPI clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_SPI_CLK(uint8_t enable, GLB_SPI_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_SPI_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x1F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SPI_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SPI_CLK_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set PWM1 clock
 *
 * @param  ioSel: io select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_PWM1_IO_Sel(GLB_PWM1_IO_SEL_Type ioSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PWM1_IO_SEL_TYPE(ioSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PWM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PWM1_IO_SEL, ioSel);
    BL_WR_REG(GLB_BASE, GLB_PWM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set PWM2 clock
 *
 * @param  ioSel: io select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_PWM2_IO_Sel(GLB_PWM2_IO_SEL_Type ioSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PWM2_IO_SEL_TYPE(ioSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PWM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PWM2_IO_SEL, ioSel);
    BL_WR_REG(GLB_BASE, GLB_PWM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set PDM clock
 *
 * @param  ioSel: io select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_PDM_IO_Sel(GLB_PDM_IO_SEL_Type ioSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PDM_IO_SEL_TYPE(ioSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PDM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PDM_IO_SEL, ioSel);
    BL_WR_REG(GLB_BASE, GLB_PDM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  select DIG clock source
 *
 * @param  clkSel: DIG clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DIG_CLK_Sel(GLB_DIG_CLK_Type clkSel)
{
    uint32_t tmpVal;
    uint32_t dig512kEn;
    uint32_t dig32kEn;

    CHECK_PARAM(IS_GLB_DIG_CLK_TYPE(clkSel));

    /* disable DIG512K and DIG32K clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG0);
    dig512kEn = BL_GET_REG_BITS_VAL(tmpVal, GLB_DIG_512K_EN);
    dig32kEn = BL_GET_REG_BITS_VAL(tmpVal, GLB_DIG_32K_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_32K_EN);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_CLK_SRC_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG0, tmpVal);

    /* repristinate DIG512K and DIG32K clock */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_512K_EN, dig512kEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_32K_EN, dig32kEn);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set DIG 512K clock
 *
 * @param  enable: enable or disable DIG 512K clock
 * @param  compensationEn: enable or disable DIG 512K clock compensation
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DIG_512K_CLK(uint8_t enable, uint8_t compensationEn, uint8_t div)
{
    uint32_t tmpVal;

    CHECK_PARAM((div <= 0x7F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG0);
    if (compensationEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_512K_COMP);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_COMP);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_512K_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set DIG 32K clock
 *
 * @param  enable: enable or disable DIG 32K clock
 * @param  compensationEn: enable or disable DIG 32K clock compensation
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DIG_32K_CLK(uint8_t enable, uint8_t compensationEn, uint16_t div)
{
    uint32_t tmpVal;

    CHECK_PARAM((div <= 0x7FF));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG0);
    if (compensationEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_32K_COMP);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_32K_COMP);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_32K_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_32K_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_32K_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  platform wakeup becomes one of  pds_wakeup source
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Platform_Wakeup_PDS_Enable(uint8_t enable)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_EN_PLATFORM_WAKEUP);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_EN_PLATFORM_WAKEUP);
    }
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  mcu gpio timer clock select
 *
 * @param  gpioPin: gpio pin number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Sel_MCU_TMR_GPIO_Clock(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    switch (gpioPin & 0x3) {
        case 0: /* inout_sig_0 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_0_EN, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPIO_TMR_CLK_SEL, 0);
            break;
        case 1: /* inout_sig_1 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_1_EN, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPIO_TMR_CLK_SEL, 1);
            break;
        case 2: /* inout_sig_2 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_2_EN, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPIO_TMR_CLK_SEL, 2);
            break;
        case 3: /* inout_sig_3 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_3_EN, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPIO_TMR_CLK_SEL, 3);
            break;
        default:
            break;
    }
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  dsp gpio timer clock select
 *
 * @param  gpioPin: gpio pin number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Sel_DSP_TMR_GPIO_Clock(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    switch (gpioPin & 0x3) {
        case 0: /* inout_sig_0 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_0_EN, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPIO_MM_TMR_CLK_SEL, 0);
            break;
        case 1: /* inout_sig_1 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_1_EN, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPIO_MM_TMR_CLK_SEL, 1);
            break;
        case 2: /* inout_sig_2 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_2_EN, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPIO_MM_TMR_CLK_SEL, 2);
            break;
        case 3: /* inout_sig_3 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_3_EN, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPIO_MM_TMR_CLK_SEL, 3);
            break;
        default:
            break;
    }
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  chip clock out0 select
 *
 * @param  clkOutType: chip clock out0 output type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Chip_Clock_Out0_Sel(GLB_CHIP_CLK_OUT_0_Type clkOutType)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    /* set clk out0 output enable */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_0_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_0_SEL, clkOutType);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  chip clock out1 select
 *
 * @param  clkOutType: chip clock out1 output type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Chip_Clock_Out1_Sel(GLB_CHIP_CLK_OUT_1_Type clkOutType)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    /* set clk out1 output enable */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_1_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_1_SEL, clkOutType);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  chip clock out2 select
 *
 * @param  clkOutType: chip clock out2 output type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Chip_Clock_Out2_Sel(GLB_CHIP_CLK_OUT_2_Type clkOutType)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    /* set clk out2 output enable */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_2_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_2_SEL, clkOutType);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  chip clock out3 select
 *
 * @param  clkOutType: chip clock out3 output type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Chip_Clock_Out3_Sel(GLB_CHIP_CLK_OUT_3_Type clkOutType)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    /* set clk out3 output enable */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_3_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_3_SEL, clkOutType);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  csi dsi clock select
 *
 * @param  csiClkSel: csi clock select
 * @param  dsiClkSel: dsi clock select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_CSI_DSI_CLK_Sel(GLB_CSI_DSI_CLK_SEL_Type csiClkSel, GLB_CSI_DSI_CLK_SEL_Type dsiClkSel)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CSI_TXCLKESC_SEL, csiClkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DSI_TXCLKESC_SEL, dsiClkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  BMX init
 *
 * @param  BmxCfg: BMX config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_BMX_TO_Init(BMX_TO_Cfg_Type *BmxCfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((BmxCfg->timeoutEn) <= 0x1F);
    CHECK_PARAM(IS_BMX_ARB_TYPE(BmxCfg->arbMod));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_BMX_TIMEOUT_EN, BmxCfg->timeoutEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_BMX_ARB_MODE, BmxCfg->arbMod);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG0, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(BMX_MCU_TO_IRQn, BMX_TO_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get BMX TO status
 *
 * @param  None
 *
 * @return BMX TO status
 *
*******************************************************************************/
uint8_t GLB_Get_BMX_TO_Status(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_BMX_CFG0), GLB_STS_BMX_TIMEOUT_STS);
}

/****************************************************************************/ /**
 * @brief  clear BMX TO status
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Clr_BMX_TO_Status(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_BMX_TIMEOUT_CLR);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_BMX_TIMEOUT_CLR);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_BMX_TIMEOUT_CLR);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  BMX timeout interrupt callback install
 *
 * @param  intType: BMX timeout interrupt type
 * @param  cbFun: callback
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type BMX_TIMEOUT_INT_Callback_Install(BMX_TO_INT_Type intType, intCallback_Type *cbFun)
{
    CHECK_PARAM(IS_BMX_TO_INT_TYPE(intType));

    glbBmxToIntCbfArra[intType] = cbFun;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  BMX Time Out interrupt IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void BMX_TO_IRQHandler(void)
{
    BMX_TO_INT_Type intType;

    for (intType = 0; intType < BMX_TO_INT_ALL; intType++) {
        if (glbBmxToIntCbfArra[intType] != NULL) {
            glbBmxToIntCbfArra[intType]();
        }
    }
    GLB_Clr_BMX_TO_Status();
}
#endif

/****************************************************************************/ /**
 * @brief  set audio auto clock
 *
 * @param  divEn: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Audio_AUTO_CLK(uint8_t divEn)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    if (divEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_AUTO_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_AUTO_DIV_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set audio ADC clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Audio_ADC_CLK(uint8_t enable, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0x3F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_ADC_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_AUDIO_ADC_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_ADC_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_ADC_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set audio DAC clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Audio_DAC_CLK(uint8_t enable, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0x3F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_DAC_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_AUDIO_DAC_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_DAC_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_DAC_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set audio PDM clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Audio_PDM_CLK(uint8_t enable, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0x3F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_PDM_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_AUDIO_PDM_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_PDM_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_PDM_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set audio PDM clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_PADC_CLK(uint8_t enable, uint16_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0x3F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_PADC_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PADC_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_PADC_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_PADC_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  invert eth rx clock
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Invert_ETH_RX_CLK(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_ETH_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CFG_INV_ETH_RX_CLK);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CFG_INV_ETH_RX_CLK);
    }
    BL_WR_REG(GLB_BASE, GLB_ETH_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  invert eth tx clock
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Invert_ETH_TX_CLK(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_ETH_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CFG_INV_ETH_TX_CLK);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CFG_INV_ETH_TX_CLK);
    }
    BL_WR_REG(GLB_BASE, GLB_ETH_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  invert eth ref clock
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Invert_ETH_REF_O_CLK(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_ETH_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CFG_INV_ETH_REF_CLK_O);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CFG_INV_ETH_REF_CLK_O);
    }
    BL_WR_REG(GLB_BASE, GLB_ETH_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set eth ref clock select
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_ETH_REF_O_CLK_Sel(GLB_ETH_REF_CLK_OUT_Type clkSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_ETH_REF_CLK_OUT_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_ETH_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CFG_SEL_ETH_REF_CLK_O, clkSel);
    BL_WR_REG(GLB_BASE, GLB_ETH_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set CAM clock
 *
 * @param  enable: Enable or disable CAM clock
 * @param  clkSel: CAM clock type
 * @param  div: clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_CAM_CLK(uint8_t enable, GLB_CAM_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_CAM_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_CAM_REF_CLK_SRC_SEL, clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_CAM_REF_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set SDH clock
 *
 * @param  enable: Enable or disable
 * @param  clkSel: SDH clock type
 * @param  div: clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_SDH_CLK(uint8_t enable, GLB_SDH_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_SDH_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x7));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SDH_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_SDH_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_SDH_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SDH_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_SDH_CLK_SEL, clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_SDH_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_SDH_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SDH_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_SDH_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_SDH_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_SDH_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  swap UART gpio pins sig function
 *
 * @param  group: UART swap set group
 * @param  swap: swap or no swap
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_Type group, uint8_t swap)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal2 = 0;

    CHECK_PARAM(IS_GLB_UART_SIG_SWAP_GRP_TYPE(group));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, GLB_UART_SWAP_SET);
    if (swap) {
        tmpVal2 |= (1 << group);
    } else {
        tmpVal2 &= ~(1 << group);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UART_SWAP_SET, tmpVal2);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  swap DSP SPI0 MOSI with MISO
 *
 * @param  newState: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Swap_DSP_SPI_0_MOSI_With_MISO(BL_Fun_Type newState)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_MM_SPI_SWAP, newState);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select DSP SPI_0 act mode
 *
 * @param  mod: SPI work mode
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_SPI_PAD_ACT_AS_TYPE(mod));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_MM_SPI_MASTER_MODE, mod);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set L2SRAM
 *
 * @param  h2pfSramRel: make pfh_64k0,pfh_64k1,pfh_64k0 writable
 * @param  vramSramRel: make l2_vram writable
 * @param  dspl2SramRel: make dspl2_32k0,dspl2_32k1 writable
 * @param  blaiSramRel: make blai_64k0,blai_64k1 writable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_L2SRAM_Available_Size(uint8_t h2pfSramRel, uint8_t vramSramRel, uint8_t dspl2SramRel, uint8_t blaiSramRel)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_MISC_VRAM_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_H2PF_SRAM_REL, h2pfSramRel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_VRAM_SRAM_REL, vramSramRel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_DSPL2_SRAM_REL, dspl2SramRel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_BLAI_SRAM_REL, blaiSramRel);
    BL_WR_REG(MM_GLB_BASE, MM_MISC_VRAM_CTRL, tmpVal);

    /* Make the above settings effective */
    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_MISC_VRAM_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_SYSRAM_SET, 1);
    BL_WR_REG(MM_GLB_BASE, MM_MISC_VRAM_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select DSP SPI_0 act mode
 *
 * @param  mod: SPI work mode
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Swap_MCU_SPI_0_MOSI_With_MISO(BL_Fun_Type newState)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_SPI_0_SWAP, newState);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select SPI_0 act mode
 *
 * @param  mod: SPI work mode
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_MCU_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_SPI_PAD_ACT_AS_TYPE(mod));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_SPI_0_MASTER_MODE, mod);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set flash io parameter
 *
 * @param  selEmbedded: Select embedded flash pin
 * @param  swap: Select embedded flash swap io0 with io3
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_Set_Flash_IO_PARM(uint8_t selEmbedded, uint8_t swap)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    if (selEmbedded) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SEL_EMBEDDED_SFLASH);
        if (swap) {
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_3_IO_0);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_3_IO_0);
        }
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SEL_EMBEDDED_SFLASH);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_3_IO_0);
    }
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    if (selEmbedded) {
        GLB_Embedded_Flash_Pad_Enable();
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  gate pll clock cgen
 *
 * @param  clk: pll clock cgen
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_PLL_CGEN_Clock_Gate(GLB_PLL_CGEN_Type clk)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PLL_CGEN_TYPE(clk));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG3);
    tmpVal &= (~(1 << clk));
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  gate pll clock cgen
 *
 * @param  clk: pll clock cgen
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_Type clk)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PLL_CGEN_TYPE(clk));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG3);
    tmpVal |= (1 << clk);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  select PKA clock source
 *
 * @param  clkSel: PKA clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_Type clkSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PKA_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PKA_CLK_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  mcu system part reset
 *
 * @param  sysPart: mcu reset part
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_MCU_SW_System_Reset(GLB_MCU_SW_SYSTEM_Type sysPart)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_MCU_SW_SYSTEM_TYPE(sysPart));

    /* reset=0 */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal &= ~(1 << sysPart);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
    BL_DRV_DUMMY;
    /* reset=1 */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal |= (1 << sysPart);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
    BL_DRV_DUMMY;
    /* reset=1 */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal &= ~(1 << sysPart);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Software system reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_SW_System_Reset(void)
{
    uint32_t tmpVal;

    /* Swicth DSP clock to RC32M, no divider */
    GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_RC32M);
    GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_XCLK);
    GLB_Set_DSP_System_CLK_Div(0, 0);

    /* Swicth MCU clock to RC32M, no divider */
    HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    GLB_Set_MCU_System_CLK_Div(0, 0, 0);

    /* reset M0/M1/LP/SYS(bus+...+D0+D1) */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_PICO_RESET);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    /* waiting for reset */
    while (1) {
        arch_delay_us(10);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Software CPU reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_SW_CPU_Reset(void)
{
    uint32_t tmpVal;

    GLB_CORE_ID_Type core = GLB_CORE_ID_INVALID;

    /* Do reset */
    core = GLB_Get_Core_Type();

    switch (core) {
        case GLB_CORE_ID_M0:
            /* Swicth MCU clock to RC32M, no divider */
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            GLB_Set_MCU_System_CLK_Div(0, 0, 0);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            break;
        case GLB_CORE_ID_D0:
            /* Swicth DSP clock to RC32M, no divider */
            GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_RC32M);
            GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_XCLK);
            GLB_Set_DSP_System_CLK_Div(0, 0);
            tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET);
            tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_CTRL_MMCPU0_RESET);
            BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET, tmpVal);
            tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET);
            tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_CTRL_MMCPU0_RESET);
            BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET, tmpVal);
            tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET);
            tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_CTRL_MMCPU0_RESET);
            BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET, tmpVal);
            break;
        case GLB_CORE_ID_LP:
            /* Swicth MCU clock to RC32M, no divider */
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            GLB_Set_MCU_System_CLK_Div(0, 0, 0);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_PICO_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_PICO_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_PICO_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            break;
        default:
            break;
    }

    /* waiting for reset */
    while (1) {
        arch_delay_us(10);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Software power on reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_SW_POR_Reset(void)
{
    uint32_t tmpVal;

    /* Swicth DSP clock to RC32M, no divider */
    GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_RC32M);
    GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_XCLK);
    GLB_Set_DSP_System_CLK_Div(0, 0);

    /* Swicth MCU clock to RC32M, no divider */
    HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    GLB_Set_MCU_System_CLK_Div(0, 0, 0);

    /* Do reset */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    /* waiting for reset */
    while (1) {
        arch_delay_us(10);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set auto calc xtal type value
 *
 * @param  calcXtalType: auto calc xtal type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Auto_Calc_Xtal_Type(GLB_XTAL_Type calcXtalType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_XTAL_TYPE(calcXtalType));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_HW_RSV0);
    tmpVal = tmpVal & 0xffff0000;
    tmpVal |= GLB_AUTO_CALC_XTAL_FLAG_VALUE;
    tmpVal |= calcXtalType;
    BL_WR_REG(GLB_BASE, GLB_HW_RSV0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set auto calc xtal type value
 *
 * @param  calcXtalType: auto calc xtal type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Get_Auto_Calc_Xtal_Type(GLB_XTAL_Type *calcXtalType)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_HW_RSV0);
    if ((tmpVal & GLB_AUTO_CALC_XTAL_FLAG_MASK) == GLB_AUTO_CALC_XTAL_FLAG_VALUE) {
        *calcXtalType = (tmpVal & 0xff);
        return SUCCESS;
    } else {
        *calcXtalType = 0;
        return ERROR;
    }
}

/****************************************************************************/ /**
 * @brief  set flash id value
 *
 * @param  idValue: flash id value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Flash_Id_Value(uint32_t idValue)
{
    BL_WR_REG(GLB_BASE, GLB_HW_RSV1, idValue);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get flash id value
 *
 * @param  None
 *
 * @return flash id
 *
*******************************************************************************/
uint32_t GLB_Get_Flash_Id_Value(void)
{
    return BL_RD_REG(GLB_BASE, GLB_HW_RSV1);
}

/****************************************************************************/ /**
 * @brief  set sram_ret value
 *
 * @param  value: value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_SRAM_RET(uint32_t value)
{
    BL_WR_REG(GLB_BASE, GLB_SRAM_CFG0, value);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get sram_ret value
 *
 * @param  None
 *
 * @return value
 *
*******************************************************************************/
uint32_t GLB_Get_SRAM_RET(void)
{
    return BL_RD_REG(GLB_BASE, GLB_SRAM_CFG0);
}

/****************************************************************************/ /**
 * @brief  set sram_slp value
 *
 * @param  value: value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_SRAM_SLP(uint32_t value)
{
    BL_WR_REG(GLB_BASE, GLB_SRAM_CFG1, value);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get sram_slp value
 *
 * @param  None
 *
 * @return value
 *
*******************************************************************************/
uint32_t GLB_Get_SRAM_SLP(void)
{
    return BL_RD_REG(GLB_BASE, GLB_SRAM_CFG1);
}

/****************************************************************************/ /**
 * @brief  set sram_param value
 *
 * @param  value: value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_SRAM_PARM(uint32_t value)
{
    BL_WR_REG(GLB_BASE, GLB_SRAM_CFG2, value);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get sram_parm value
 *
 * @param  None
 *
 * @return value
 *
*******************************************************************************/
uint32_t GLB_Get_SRAM_PARM(void)
{
    return BL_RD_REG(GLB_BASE, GLB_SRAM_CFG2);
}

/****************************************************************************/ /**
 * @brief  select EM type
 *
 * @param  emType: EM type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_EM_Sel(GLB_EM_Type emType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_EM_TYPE(emType));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SRAM_CFG3);
    switch (emType) {
        case GLB_WRAM160KB_EM0KB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x00);
            break;
        case GLB_WRAM144KB_EM16KB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x03);
            break;
        case GLB_WRAM128KB_EM32KB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x0F);
            break;
        case GLB_WRAM112KB_EM48KB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x3F);
            break;
        case GLB_WRAM96KB_EM64KB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0xFF);
            break;
        default:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x03);
            break;
    }
    BL_WR_REG(GLB_BASE, GLB_SRAM_CFG3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set psram clock
 *
 * @param  id: psram id
 * @param  enable: enable or disable psram clock
 * @param  pll: psram pll clock
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_PSram_CLK(uint8_t id, uint8_t enable, GLB_PSRAM_PLL_Type pll, uint8_t div)
{
    uint32_t tmpVal = 0;
    uint32_t en = 0;

    CHECK_PARAM(IS_GLB_PSRAM_PLL_TYPE(pll));
    CHECK_PARAM((div <= 0x3));

    en = enable ? 1 : 0;
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG3);
    switch (pll) {
        case GLB_PSRAM_EMI_CPUPLL_400M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_EMI_CPUPLL_400M, en);
            break;
        case GLB_PSRAM_EMI_WIFIPLL_320M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_EMI_WIFIPLL_320M, en);
            break;
        case GLB_PSRAM_EMI_AUPLL_DIV1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_EMI_AUPLL_DIV1, en);
            break;
        default:
            break;
    }
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG3, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PSRAM_CFG0);
    if (id == 1) {
        /* psram B */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PSRAMB_CLK_EN, en);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PSRAMB_CLK_SEL, pll);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PSRAMB_CLK_DIV, div);
    }
    BL_WR_REG(GLB_BASE, GLB_PSRAM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  trim ldo18io vout
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Trim_LDO18IO_Vout(void)
{
    Efuse_Ana_LDO18IO_VOUT_Trim_Type trim;
    uint32_t tmpVal = 0;

    EF_Ctrl_Read_LDO18IO_Vout_Trim(&trim);
    if (trim.trimLdo18ioVoutEn) {
        if (trim.trimLdo18ioVoutParity == EF_Ctrl_Get_Trim_Parity(trim.trimLdo18ioVoutVal, 4)) {
            tmpVal = BL_RD_REG(AON_BASE, AON_LDO18IO);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_LDO18IO_VOUT_TRIM_AON, trim.trimLdo18ioVoutVal);
            BL_WR_REG(AON_BASE, AON_LDO18IO, tmpVal);
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  trim ldo18flash vout
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Trim_LDO18FLASH_Vout(void)
{
    Efuse_Ana_LDO18FLASH_Trim_Type trim;
    uint32_t tmpVal = 0;

    EF_Ctrl_Read_LDO18FLASH_Trim(&trim);
    if (trim.trimLdo18flashVoutAonEn) {
        if (trim.trimLdo18flashVoutAonParity == EF_Ctrl_Get_Trim_Parity(trim.trimLdo18flashVoutAon, 4)) {
            tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO18FLASH);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO18FLASH_VOUT_TRIM, trim.trimLdo18flashVoutAon);
            BL_WR_REG(GLB_BASE, GLB_LDO18FLASH, tmpVal);
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  set cnn clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  clkSel: cnn clock type
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_CNN_CLK(uint8_t enable, GLB_DSP_CNN_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_CNN_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x7));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CNN_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CNN_CLK_SEL, clkSel);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_CNN_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_CNN_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CPU, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set display clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  clkSel: display clock type
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_DP_CLK(uint8_t enable, GLB_DSP_DP_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_DP_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0xF));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_DSP2_DP_CLK);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_DP_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_DP_CLK_SEL, clkSel);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_DP_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_DP_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_DSP2_DP_CLK, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set dsp2 clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  clkSel: dsp2 clock type
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_DSP2_CLK(uint8_t enable, GLB_DSP_DSP2_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_DSP2_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_DSP2_DP_CLK);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_DSP2_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_DSP2_CLK_SEL, clkSel);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_DSP2_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_DSP2_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_DSP2_DP_CLK, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set h264 clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  clkSel: h264 clock type
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_H264_CLK(uint8_t enable, GLB_DSP_H264_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_H264_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x7));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_CODEC_CLK);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_H264_CLK_DIV_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_CODEC_CLK, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_CODEC_CLK);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_H264_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_H264_CLK_SEL, clkSel);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_H264_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_H264_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_CODEC_CLK, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set spi clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_SPI_CLK(uint8_t enable, GLB_DSP_SPI_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_SPI_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_SPI_CLK_DIV_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_SPI_CLK_SEL, clkSel);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_SPI_CLK_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_SPI_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_SPI_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set uart0 clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  uartClk: mm glb uart clock type
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_UART0_CLK(uint8_t enable, GLB_DSP_UART_CLK_Type uartClk, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_UART_CLK_TYPE(uartClk));
    CHECK_PARAM((div <= 0x7));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_UART0_CLK_DIV_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_UART_CLK_SEL, uartClk);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_UART0_CLK_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_UART0_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_UART0_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set uart1 clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  uartClk: mm glb uart clock type
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_UART1_CLK(uint8_t enable, GLB_DSP_UART_CLK_Type uartClk, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_UART_CLK_TYPE(uartClk));
    CHECK_PARAM((div <= 0x7));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI3);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_UART1_CLK_DIV_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI3, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_UART_CLK_SEL, uartClk);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_UART1_CLK_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_UART1_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_UART1_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set i2c0 clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  divEn: div enable
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_I2C0_CLK(uint8_t enable, GLB_DSP_I2C_CLK_Type clkSel, uint8_t divEn, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_I2C_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_I2C_CLK_SEL, clkSel);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_I2C0_CLK_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_EN);
    }
    if (divEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set i2c1 clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  divEn: div enable
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_I2C1_CLK(uint8_t enable, GLB_DSP_I2C_CLK_Type clkSel, uint8_t divEn, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_I2C_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI3);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C1_CLK_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI3, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_I2C_CLK_SEL, clkSel);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_I2C1_CLK_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_I2C1_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C1_CLK_EN);
    }
    if (divEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_I2C1_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C1_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  sw sys reset
 *
 * @param  sysPart: reset type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_DSP_SW_System_Reset(GLB_DSP_SW_SYSTEM_Type sysPart)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_SW_SYSTEM_TYPE(sysPart));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET);
    tmpVal &= ~(1 << sysPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET);
    tmpVal |= (1 << sysPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET);
    tmpVal &= ~(1 << sysPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  peripheral reset
 *
 * @param  periPart: reset type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_DSP_Peripheral_Reset(GLB_DSP_PERIPHERAL_Type periPart)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_PERIPHERAL_TYPE(periPart));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_MM_PERI);
    tmpVal &= ~(1 << periPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_MM_PERI, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_MM_PERI);
    tmpVal |= (1 << periPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_MM_PERI, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_MM_PERI);
    tmpVal &= ~(1 << periPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_MM_PERI, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  dsp2 sub reset
 *
 * @param  dsp2Part: reset type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_DSP_DSP2_Sub_Reset(GLB_DSP_DSP2_SUB_Type dsp2Part)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_DSP2_SUB_TYPE(dsp2Part));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_DSP2_SUB);
    tmpVal &= ~(1 << dsp2Part);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_DSP2_SUB, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_DSP2_SUB);
    tmpVal |= (1 << dsp2Part);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_DSP2_SUB, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_DSP2_SUB);
    tmpVal &= ~(1 << dsp2Part);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_DSP2_SUB, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  codec sub reset
 *
 * @param  codecPart: reset type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_DSP_Codec_Sub_Reset(GLB_DSP_CODEC_SUB_Type codecPart)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_CODEC_SUB_TYPE(codecPart));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_CODEC_SUB);
    tmpVal &= ~(1 << codecPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_CODEC_SUB, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_CODEC_SUB);
    tmpVal |= (1 << codecPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_CODEC_SUB, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_SW_RESET_CODEC_SUB);
    tmpVal &= ~(1 << codecPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_SW_RESET_CODEC_SUB, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  image sensor reset
 *
 * @param  imageSensorPart: reset type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_DSP_Image_Sensor_Reset(GLB_DSP_IMAGE_SENSOR_Type imageSensorPart)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_IMAGE_SENSOR_TYPE(imageSensorPart));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_IMAGE_SENSOR_CTRL);
    tmpVal &= ~(1 << imageSensorPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_IMAGE_SENSOR_CTRL, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_IMAGE_SENSOR_CTRL);
    tmpVal |= (1 << imageSensorPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_IMAGE_SENSOR_CTRL, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_IMAGE_SENSOR_CTRL);
    tmpVal &= ~(1 << imageSensorPart);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_IMAGE_SENSOR_CTRL, tmpVal);

    return SUCCESS;
}

/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL808_Peripheral_Driver */
