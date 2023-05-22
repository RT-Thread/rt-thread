/**
  ******************************************************************************
  * @file    bl602_glb.c
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

#include "bl602_glb.h"
#include "bl602_hbn.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GLB
 *  @{
 */

/** @defgroup  GLB_Private_Macros
 *  @{
 */
#define GLB_CLK_SET_DUMMY_WAIT \
    {                          \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
    }
#define GLB_GPIO_Get_Reg(pin)       (glb_gpio_reg_t *)(GLB_BASE + GLB_GPIO_OFFSET + (pin / 2) * 4)
#define GLB_GPIO_INT0_NUM           (23)
#define GLB_REG_BCLK_DIS_TRUE       (*(volatile uint32_t *)(0x40000FFC) = (0x00000001))
#define GLB_REG_BCLK_DIS_FALSE      (*(volatile uint32_t *)(0x40000FFC) = (0x00000000))
#define GLB_GPIO_INT0_CLEAR_TIMEOUT (32)

/*@} end of group GLB_Private_Macros */

/** @defgroup  GLB_Private_Types
 *  @{
 */

/*@} end of group GLB_Private_Types */

/** @defgroup  GLB_Private_Variables
 *  @{
 */
static intCallback_Type *glbBmxErrIntCbfArra[BMX_ERR_INT_ALL] = { NULL };
static intCallback_Type *glbBmxToIntCbfArra[BMX_TO_INT_ALL] = { NULL };
static intCallback_Type *glbGpioInt0CbfArra[GLB_GPIO_INT0_NUM] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                                                   NULL, NULL, NULL, NULL, NULL, NULL, NULL };

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
 * @brief  get root clock selection
 *
 * @param  None
 *
 * @return root clock selection
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
GLB_ROOT_CLK_Type ATTR_CLOCK_SECTION GLB_Get_Root_CLK_Sel(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);

    switch (BL_GET_REG_BITS_VAL(tmpVal, GLB_HBN_ROOT_CLK_SEL)) {
        case 0:
            return GLB_ROOT_CLK_RC32M;

        case 1:
            return GLB_ROOT_CLK_XTAL;

        case 2:
            return GLB_ROOT_CLK_PLL;

        case 3:
            return GLB_ROOT_CLK_PLL;

        default:
            return GLB_ROOT_CLK_RC32M;
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Set System clock divider
 *
 * @param  hclkDiv: HCLK divider
 * @param  bclkDiv: BCLK divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_System_CLK_Div(uint8_t hclkDiv, uint8_t bclkDiv)
{
    /***********************************************************************************/
    /*                                 NOTE                                            */
    /* "GLB_REG_BCLK_DIS_TRUE + GLB_REG_BCLK_DIS_FALSE" will stop bclk a little while. */
    /* OCRAM use bclk as source clock. Pay attention to risks when using this API.     */
    /***********************************************************************************/
    uint32_t tmpVal;

    /* recommended: fclk<=160MHz, bclk<=80MHz */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV, hclkDiv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV, bclkDiv);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG0, tmpVal);
    GLB_REG_BCLK_DIS_TRUE;
    GLB_REG_BCLK_DIS_FALSE;
    SystemCoreClockSet(SystemCoreClockGet() / ((uint16_t)hclkDiv + 1));
    GLB_CLK_SET_DUMMY_WAIT;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_HCLK_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_BCLK_EN);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG0, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Get Bus clock divider
 *
 * @param  None
 *
 * @return Clock Divider
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
uint8_t ATTR_CLOCK_SECTION GLB_Get_BCLK_Div(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV);
}
#endif

/****************************************************************************/ /**
 * @brief  Get CPU clock divider
 *
 * @param  None
 *
 * @return Clock Divider
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
uint8_t ATTR_CLOCK_SECTION GLB_Get_HCLK_Div(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV);
}
#endif

/****************************************************************************/ /**
 * @brief  update SystemCoreClock value
 *
 * @param  xtalType: XTAL frequency type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION Update_SystemCoreClockWith_XTAL(GLB_PLL_XTAL_Type xtalType)
{
    CHECK_PARAM(IS_GLB_PLL_XTAL_TYPE(xtalType));

    switch (xtalType) {
        case GLB_PLL_XTAL_NONE:
            break;

        case GLB_PLL_XTAL_24M:
            SystemCoreClockSet(24000000);
            break;

        case GLB_PLL_XTAL_32M:
            SystemCoreClockSet(32000000);
            break;

        case GLB_PLL_XTAL_38P4M:
            SystemCoreClockSet(38400000);
            break;

        case GLB_PLL_XTAL_40M:
            SystemCoreClockSet(40000000);
            break;

        case GLB_PLL_XTAL_26M:
            SystemCoreClockSet(26000000);
            break;

        case GLB_PLL_XTAL_RC32M:
            SystemCoreClockSet(32000000);
            break;

        default:
            break;
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Set System clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  clkFreq: clock frequency selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_System_CLK(GLB_PLL_XTAL_Type xtalType, GLB_SYS_CLK_Type clkFreq)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_PLL_XTAL_TYPE(xtalType));
    CHECK_PARAM(IS_GLB_SYS_CLK_TYPE(clkFreq));

    /* reg_bclk_en = reg_hclk_en = reg_fclk_en = 1, cannot be zero */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_BCLK_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_HCLK_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_FCLK_EN);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG0, tmpVal);

    /* Before config XTAL and PLL ,make sure root clk is from RC32M */
    HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_RC32M);
    GLB_Set_System_CLK_Div(0, 0);
    SystemCoreClockSet(32 * 1000 * 1000);

    /* Select PKA clock from hclk */
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_HCLK);

    if (xtalType == GLB_PLL_XTAL_NONE) {
        if (clkFreq == GLB_SYS_CLK_RC32M) {
            return SUCCESS;
        } else {
            return ERROR;
        }
    }

    if (xtalType != GLB_PLL_XTAL_RC32M) {
        /* power on xtal first */
        AON_Power_On_XTAL();
    }

    /* always power up PLL and enable all PLL clock output */
    PDS_Power_On_PLL((PDS_PLL_XTAL_Type)xtalType);
    BL602_Delay_US(55);
    PDS_Enable_PLL_All_Clks();

    /* reg_pll_en = 1, cannot be zero */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_PLL_EN);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG0, tmpVal);

    /* select pll output clock before select root clock */
    if (clkFreq >= GLB_SYS_CLK_PLL48M) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PLL_SEL, clkFreq - GLB_SYS_CLK_PLL48M);
        BL_WR_REG(GLB_BASE, GLB_CLK_CFG0, tmpVal);
    }

    /* select root clock */
    switch (clkFreq) {
        case GLB_SYS_CLK_RC32M:
            break;

        case GLB_SYS_CLK_XTAL:
            HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_XTAL);
            Update_SystemCoreClockWith_XTAL(xtalType);
            break;

        case GLB_SYS_CLK_PLL48M:
            HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_PLL);
            SystemCoreClockSet(48 * 1000 * 1000);
            break;

        case GLB_SYS_CLK_PLL120M:
            GLB_Set_System_CLK_Div(0, 1);
            HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_PLL);
            SystemCoreClockSet(120 * 1000 * 1000);
            break;

        case GLB_SYS_CLK_PLL160M:
            L1C_IROM_2T_Access_Set(ENABLE);
            GLB_Set_System_CLK_Div(0, 1);
            HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_PLL);
            SystemCoreClockSet(160 * 1000 * 1000);
            break;

        case GLB_SYS_CLK_PLL192M:
            L1C_IROM_2T_Access_Set(ENABLE);
            GLB_Set_System_CLK_Div(0, 1);
            HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_PLL);
            SystemCoreClockSet(192 * 1000 * 1000);
            break;

        default:
            break;
    }

    GLB_CLK_SET_DUMMY_WAIT;

    /* select PKA clock from 120M since we power up PLL */
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_PLL120M);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  This is demo for user that use RC32M as default bootup clock instead of PLL,when APP is
 *         started, this function can be called to set PLL to 160M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION System_Core_Clock_Update_From_RC32M(void)
{
    SF_Ctrl_Cfg_Type sfCtrlCfg = {
        .owner = SF_CTRL_OWNER_IAHB,
        .clkDelay = 1,
        .clkInvert = 1,
        .rxClkInvert = 1,
        .doDelay = 0,
        .diDelay = 0,
        .oeDelay = 0,
    };
    /* Use RC32M as PLL ref source to set up PLL to 160M */
    GLB_Set_System_CLK(GLB_PLL_XTAL_RC32M, GLB_SYS_CLK_PLL160M);
    /* Flash controller also need changes since system (bus) clock changed */
    SF_Ctrl_Enable(&sfCtrlCfg);
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  set BLE clock
 *
 * @param  enable: Enable or disable BLE clock
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_BLE_CLK(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG1);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_BLE_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_BLE_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set wifi core clock divider
 *
 * @param  clkDiv: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_WiFi_Core_CLK(uint8_t clkDiv)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((clkDiv <= 0x3));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFI_MAC_CORE_DIV, clkDiv);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set wifi encryption clock
 *
 * @param  clkDiv: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_WiFi_Encrypt_CLK(uint8_t clkDiv)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((clkDiv <= 0x3));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFI_MAC_WT_DIV, clkDiv);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set DMA clock
 *
 * @param  enable: Enable or disable BLE clock
 * @param  clk: DMA clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DMA_CLK(uint8_t enable, GLB_DMA_CLK_ID_Type clk)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, GLB_DMA_CLK_EN);

    if (enable) {
        tmpVal2 |= (1 << clk);
    } else {
        tmpVal2 &= (~(1 << clk));
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DMA_CLK_EN, tmpVal2);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

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

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_IR_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_IR_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_IR_CLK_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

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
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_SF_CLK(uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;
    GLB_PLL_CLK_Type clk;

    CHECK_PARAM(IS_GLB_SFLASH_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x7));

    /* disable SFLASH clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SF_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

    /* Select flash clock, all Flash CLKs are divied by PLL_480M */
    clk = GLB_PLL_CLK_480M;
    PDS_Enable_PLL_Clk((PDS_PLL_CLK_Type)clk);
    /* clock divider */
    /* Select flash clock, all Flash CLKs are divied by PLL_480M */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_DIV, div);

    switch (clkSel) {
        case GLB_SFLASH_CLK_120M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x0);
            break;

        case GLB_SFLASH_CLK_XTAL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x1);
            break;

        case GLB_SFLASH_CLK_48M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x3);
            break;

        case GLB_SFLASH_CLK_80M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x1);
            break;

        case GLB_SFLASH_CLK_BCLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x2);
            break;

        case GLB_SFLASH_CLK_96M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x3);
            break;

        default:
            break;
    }

    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

    /* enable or disable flash clock */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SF_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SF_CLK_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

    return SUCCESS;
}
#endif

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
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_UART_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

    /* Set div */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UART_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

    /* Select clock source for uart */
    HBN_Set_UART_CLK_Sel(clkSel);

    /* Set enable or disable */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_UART_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_UART_CLK_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set I2C clock
 *
 * @param  enable: Enable or disable I2C clock
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_I2C_CLK(uint8_t enable, uint8_t div)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_I2C_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG3, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG3);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_CLK_CFG3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set SPI clock
 *
 * @param  enable: Enable or disable SPI clock
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_SPI_CLK(uint8_t enable, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0x1F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SPI_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG3, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG3);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_CLK_CFG3, tmpVal);

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
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_Type clkSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PKA_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PKA_CLK_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Software system reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_SW_System_Reset(void)
{
    /***********************************************************************************/
    /*                                 NOTE                                            */
    /* "GLB_REG_BCLK_DIS_TRUE + GLB_REG_BCLK_DIS_FALSE" will stop bclk a little while. */
    /* OCRAM use bclk as source clock. Pay attention to risks when using this API.     */
    /***********************************************************************************/
    uint32_t tmpVal;

    /* Swicth clock to 32M as default */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL, 0);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    /* HCLK is RC32M , so BCLK/HCLK no need divider */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV, 0);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG0, tmpVal);
    GLB_REG_BCLK_DIS_TRUE;
    GLB_REG_BCLK_DIS_FALSE;
    GLB_CLK_SET_DUMMY_WAIT;

    /* Do reset */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    //tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    /* waiting for reset */
    while (1) {
        BL602_Delay_US(10);
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Software CPU reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_SW_CPU_Reset(void)
{
    /***********************************************************************************/
    /*                                 NOTE                                            */
    /* "GLB_REG_BCLK_DIS_TRUE + GLB_REG_BCLK_DIS_FALSE" will stop bclk a little while. */
    /* OCRAM use bclk as source clock. Pay attention to risks when using this API.     */
    /***********************************************************************************/
    uint32_t tmpVal;

    /* Swicth clock to 32M as default */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL, 0);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    /* HCLK is RC32M , so BCLK/HCLK no need divider */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV, 0);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG0, tmpVal);
    GLB_REG_BCLK_DIS_TRUE;
    GLB_REG_BCLK_DIS_FALSE;
    GLB_CLK_SET_DUMMY_WAIT;

    /* Do reset */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    //tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    //tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    /* waiting for reset */
    while (1) {
        BL602_Delay_US(10);
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Software power on reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_SW_POR_Reset(void)
{
    /***********************************************************************************/
    /*                                 NOTE                                            */
    /* "GLB_REG_BCLK_DIS_TRUE + GLB_REG_BCLK_DIS_FALSE" will stop bclk a little while. */
    /* OCRAM use bclk as source clock. Pay attention to risks when using this API.     */
    /***********************************************************************************/
    uint32_t tmpVal;

    /* Swicth clock to 32M as default */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL, 0);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    /* HCLK is RC32M , so BCLK/HCLK no need divider */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV, 0);
    BL_WR_REG(GLB_BASE, GLB_CLK_CFG0, tmpVal);
    GLB_REG_BCLK_DIS_TRUE;
    GLB_REG_BCLK_DIS_FALSE;
    GLB_CLK_SET_DUMMY_WAIT;

    /* Do reset */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);

    /* waiting for reset */
    while (1) {
        BL602_Delay_US(10);
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Reset slave 1
 *
 * @param  slave1: slave num
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_AHB_Slave1_Reset(BL_AHB_Slave1_Type slave1)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG1);
    tmpVal &= (~(1 << slave1));
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG1, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG1);
    tmpVal |= (1 << slave1);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG1, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG1);
    tmpVal &= (~(1 << slave1));
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  clock gate
 *
 * @param  enable: ENABLE or DISABLE
 * @param  slave1: AHB slaveClk type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_AHB_Slave1_Clock_Gate(uint8_t enable, BL_AHB_Slave1_Type slave1)
{
    uint32_t tmpVal = 0;

    if ((BL_AHB_SLAVE1_GLB == slave1) || (BL_AHB_SLAVE1_TZ2 == slave1) ||
        (BL_AHB_SLAVE1_CCI == slave1) || (BL_AHB_SLAVE1_L1C == slave1) ||
        (BL_AHB_SLAVE1_PDS_HBN_AON_HBNRAM == slave1)) {
        /* not support */
        return ERROR;
    }

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);

    if (enable) {
        /* clear bit means clock gate */
        tmpVal &= (~(1 << slave1));
    } else {
        /* set bit means clock pass */
        tmpVal |= (1 << slave1);
    }

    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpVal);

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
BL_Err_Type GLB_BMX_Init(BMX_Cfg_Type *BmxCfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((BmxCfg->timeoutEn) <= 0xF);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_BMX_TIMEOUT_EN, BmxCfg->timeoutEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_BMX_ERR_EN, BmxCfg->errEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_BMX_ARB_MODE, BmxCfg->arbMod);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG1, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(BMX_ERR_IRQn, BMX_ERR_IRQHandler);
    Interrupt_Handler_Register(BMX_TO_IRQn, BMX_TO_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  BMX address monitor enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_BMX_Addr_Monitor_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_BMX_ERR_ADDR_DIS);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  BMX address monitor disable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_BMX_Addr_Monitor_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_BMX_ERR_ADDR_DIS);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  BMX bus error response enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_BMX_BusErrResponse_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG1);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_BMX_ERR_EN);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  BMX bus error response disable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_BMX_BusErrResponse_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_BMX_ERR_EN);
    BL_WR_REG(GLB_BASE, GLB_BMX_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get BMX error status
 *
 * @param  errType: BMX error status type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type GLB_BMX_Get_Status(BMX_BUS_ERR_Type errType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_BMX_BUS_ERR_TYPE(errType));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_BMX_CFG2);

    if (errType == BMX_BUS_ERR_TRUSTZONE_DECODE) {
        return BL_GET_REG_BITS_VAL(tmpVal, GLB_BMX_ERR_TZ) ? SET : RESET;
    } else {
        return BL_GET_REG_BITS_VAL(tmpVal, GLB_BMX_ERR_DEC) ? SET : RESET;
    }
}

/****************************************************************************/ /**
 * @brief  Get BMX error address
 *
 * @param  None
 *
 * @return NP BMX error address
 *
*******************************************************************************/
uint32_t GLB_BMX_Get_Err_Addr(void)
{
    return BL_RD_REG(GLB_BASE, GLB_BMX_ERR_ADDR);
}

/****************************************************************************/ /**
 * @brief  BMX error interrupt callback install
 *
 * @param  intType: BMX error interrupt type
 * @param  cbFun: callback
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type BMX_ERR_INT_Callback_Install(BMX_ERR_INT_Type intType, intCallback_Type *cbFun)
{
    CHECK_PARAM(IS_BMX_ERR_INT_TYPE(intType));

    glbBmxErrIntCbfArra[intType] = cbFun;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  BMX ERR interrupt IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void BMX_ERR_IRQHandler(void)
{
    BMX_ERR_INT_Type intType;

    for (intType = BMX_ERR_INT_ERR; intType < BMX_ERR_INT_ALL; intType++) {
        if (glbBmxErrIntCbfArra[intType] != NULL) {
            glbBmxErrIntCbfArra[intType]();
        }
    }

    while (1) {
        MSG("BMX_ERR_IRQHandler\r\n");
        BL602_Delay_MS(1000);
    }
}
#endif

/****************************************************************************/ /**
 * @brief  BMX timeout interrupt callback install
 *
 * @param  intType: BMX timeout interrupt type
 * @param  cbFun: callback
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type BMX_TIMEOUT_INT_Callback_Install(BMX_TO_INT_Type intType, intCallback_Type *cbFun)
{
    CHECK_PARAM(IS_BMX_TO_INT_TYPE(intType));

    glbBmxToIntCbfArra[intType] = cbFun;

    return SUCCESS;
}

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

    for (intType = BMX_TO_INT_TIMEOUT; intType < BMX_TO_INT_ALL; intType++) {
        if (glbBmxToIntCbfArra[intType] != NULL) {
            glbBmxToIntCbfArra[intType]();
        }
    }

    while (1) {
        MSG("BMX_TO_IRQHandler\r\n");
        BL602_Delay_MS(1000);
    }
}
#endif

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
    BL_WR_REG(GLB_BASE, GLB_SRAM_RET, value);

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
    return BL_RD_REG(GLB_BASE, GLB_SRAM_RET);
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
    BL_WR_REG(GLB_BASE, GLB_SRAM_SLP, value);

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
    return BL_RD_REG(GLB_BASE, GLB_SRAM_SLP);
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
    BL_WR_REG(GLB_BASE, GLB_SRAM_PARM, value);

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
    return BL_RD_REG(GLB_BASE, GLB_SRAM_PARM);
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

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SEAM_MISC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, emType);
    BL_WR_REG(GLB_BASE, GLB_SEAM_MISC, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  swap UART gpio pins sig function
 *
 * @param  swapSel: UART swap set gpio pins selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_UART_Sig_Swap_Set(uint8_t swapSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((swapSel <= 0x7));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UART_SWAP_SET, swapSel);
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  swap JTAG gpio pins function
 *
 * @param  swapSel: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_JTAG_Sig_Swap_Set(uint8_t swapSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((swapSel <= 0x3F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_JTAG_SWAP_SET, swapSel);
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  swap SPI0 MOSI with MISO
 *
 * @param  newState: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Swap_SPI_0_MOSI_With_MISO(BL_Fun_Type newState)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_SPI_0_SWAP, newState);
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

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
BL_Err_Type GLB_Set_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_SPI_PAD_ACT_AS_TYPE(mod));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_SPI_0_MASTER_MODE, mod);
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  use internal flash
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_Select_Internal_Flash(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SEL_EMBEDDED_SFLASH);
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  use external flash
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_Select_External_Flash(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SEL_EMBEDDED_SFLASH);
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Deswap internal flash IO3 and IO0 pin
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_Deswap_Flash_Pin(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_3_IO_0);
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Swap internal flash IO3 and IO0 pin
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_Swap_Flash_Pin(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_3_IO_0);
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  set MTimer clock
 *
 * @param  enable: enable or disable MTimer clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_MTimer_CLK(uint8_t enable, GLB_MTIMER_CLK_Type clkSel, uint32_t div)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_MTIMER_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x1FFFF));

    /* disable MTimer clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CPU_CLK_CFG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CPU_RTC_EN);
    BL_WR_REG(GLB_BASE, GLB_CPU_CLK_CFG, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CPU_CLK_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CPU_RTC_SEL, clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CPU_RTC_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_CPU_CLK_CFG, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CPU_CLK_CFG);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CPU_RTC_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CPU_RTC_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_CPU_CLK_CFG, tmpVal);

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

    /* disable ADC clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPADC_32M_SRC_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    BL_WR_REG(GLB_BASE, GLB_GPADC_32M_SRC_CTRL, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPADC_32M_SRC_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPADC_32M_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPADC_32M_CLK_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_GPADC_32M_SRC_CTRL, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPADC_32M_SRC_CTRL);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_GPADC_32M_SRC_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set DAC clock
 *
 * @param  enable: enable frequency divider or not
 * @param  clkSel: ADC clock selection
 * @param  div: src divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DAC_CLK(uint8_t enable, GLB_DAC_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_DAC_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_COMP);

    if (clkSel == GLB_DAC_CLK_32M) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_CLK_SRC_SEL);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_CLK_SRC_SEL);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_512K_DIV, div);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  platform wakeup will becomes one of  pds_wakeup source
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Platform_Wakeup_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_EN_PLATFORM_WAKEUP);
    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  platform wakeup will not becomes one of  pds_wakeup source
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Platform_Wakeup_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_EN_PLATFORM_WAKEUP);
    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

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

    /* disable DIG512K and DIG32K clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);
    dig512kEn = BL_GET_REG_BITS_VAL(tmpVal, GLB_DIG_512K_EN);
    dig32kEn = BL_GET_REG_BITS_VAL(tmpVal, GLB_DIG_32K_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_32K_EN);
    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_CLK_SRC_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    /* repristinate DIG512K and DIG32K clock */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_512K_EN, dig512kEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_32K_EN, dig32kEn);
    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set DIG 512K clock
 *
 * @param  enable: enable or disable DIG 512K clock
 * @param  compensation: enable or disable DIG 512K clock compensation
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DIG_512K_CLK(uint8_t enable, uint8_t compensation, uint8_t div)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);

    if (compensation) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_512K_COMP);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_COMP);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_512K_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_512K_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set DIG 32K clock
 *
 * @param  enable: enable or disable DIG 32K clock
 * @param  compensation: enable or disable DIG 32K clock compensation
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DIG_32K_CLK(uint8_t enable, uint8_t compensation, uint16_t div)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);

    if (compensation) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_32K_COMP);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_32K_COMP);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DIG_32K_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DIG_32K_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DIG_32K_EN);
    }

    BL_WR_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set BT coex signal
 *
 * @param  enable: ENABLE or DISABLE, if enable, the AP JTAG will be replaced by BT Coex Signal
 * @param  bandWidth: BT Bandwidth
 * @param  pti: BT Packet Traffic Information
 * @param  channel: BT Channel
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_BT_Coex_Signal(uint8_t enable, GLB_BT_BANDWIDTH_Type bandWidth, uint8_t pti, uint8_t channel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_BT_BANDWIDTH_TYPE(bandWidth));
    CHECK_PARAM((pti <= 0xF));
    CHECK_PARAM((channel <= 78));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_BT_COEX_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_COEX_BT_BW, bandWidth);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_COEX_BT_PTI, pti);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_COEX_BT_CHANNEL, channel);
    BL_WR_REG(GLB_BASE, GLB_WIFI_BT_COEX_CTRL, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_BT_COEX_CTRL);

    if (enable) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EN_GPIO_BT_COEX, 1);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EN_GPIO_BT_COEX, 0);
    }

    BL_WR_REG(GLB_BASE, GLB_WIFI_BT_COEX_CTRL, tmpVal);

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

    tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_SIG_SEL_0);
    sig_pos = (sig * 4);
    /* Clear original val */
    tmpVal &= (~(0xf << sig_pos));
    /* Set new value */
    tmpVal |= (fun << sig_pos);
    BL_WR_REG(GLB_BASE, GLB_UART_SIG_SEL_0, tmpVal);

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

    /* Select gpio between gpio11 and gpio13 */
    if (gpio > 10 && gpio < 14) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_LED_DRIVER);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_IR_RX_GPIO_SEL, gpio - 10);
        BL_WR_REG(GLB_BASE, GLB_LED_DRIVER, tmpVal);
    }

    /* Close ir rx */
    if (gpio == 0) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_LED_DRIVER);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_IR_RX_GPIO_SEL, 0);
        BL_WR_REG(GLB_BASE, GLB_LED_DRIVER, tmpVal);
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
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LED_DRIVER);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_PU_LEDDRV);
    BL_WR_REG(GLB_BASE, GLB_LED_DRIVER, tmpVal);

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
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LED_DRIVER);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PU_LEDDRV);
    BL_WR_REG(GLB_BASE, GLB_LED_DRIVER, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set ir led driver ibias
 *
 * @param  ibias: Ibias value,0x0:0mA~0xf:120mA,8mA/step
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_IR_LED_Driver_Ibias(uint8_t ibias)
{
    uint32_t tmpVal = 0;

    /* Set driver ibias */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LED_DRIVER);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LEDDRV_IBIAS, ibias & 0xF);
    BL_WR_REG(GLB_BASE, GLB_LED_DRIVER, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO initialization
 *
 * @param  cfg: GPIO configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg)
{
    uint8_t gpioPin = cfg->gpioPin;
    uint32_t *pOut;
    uint32_t pos;
    uint32_t tmpOut;
    uint32_t tmpVal;

    /* drive strength(drive) = 0  <=>  8.0mA  @ 3.3V */
    /* drive strength(drive) = 1  <=>  9.6mA  @ 3.3V */
    /* drive strength(drive) = 2  <=>  11.2mA @ 3.3V */
    /* drive strength(drive) = 3  <=>  12.8mA @ 3.3V */

    pOut = (uint32_t *)(GLB_BASE + GLB_GPIO_OUTPUT_EN_OFFSET + ((gpioPin >> 5) << 2));
    pos = gpioPin % 32;
    tmpOut = *pOut;

    /* Disable output anyway*/
    tmpOut &= (~(1 << pos));
    *pOut = tmpOut;

    tmpVal = BL_RD_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4);

    if (gpioPin % 2 == 0) {
        if (cfg->gpioMode != GPIO_MODE_ANALOG) {
            /* not analog mode */

            /* Set input or output */
            if (cfg->gpioMode == GPIO_MODE_OUTPUT) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
                tmpOut |= (1 << pos);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
            }

            /* Set pull up or down */
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);

            if (cfg->pullType == GPIO_PULL_UP) {
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            } else if (cfg->pullType == GPIO_PULL_DOWN) {
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
            }
        } else {
            /* analog mode */

            /* clear ie && oe */
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
            tmpOut &= ~(1 << pos);

            /* clear pu && pd */
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
        }

        /* set drive && smt && func */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_DRV, cfg->drive);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_SMT, cfg->smtCtrl);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_FUNC_SEL, cfg->gpioFun);
    } else {
        if (cfg->gpioMode != GPIO_MODE_ANALOG) {
            /* not analog mode */

            /* Set input or output */
            if (cfg->gpioMode == GPIO_MODE_OUTPUT) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_1_IE);
                tmpOut |= (1 << pos);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_1_IE);
            }

            /* Set pull up or down */
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_1_PU);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_1_PD);

            if (cfg->pullType == GPIO_PULL_UP) {
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_1_PU);
            } else if (cfg->pullType == GPIO_PULL_DOWN) {
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_1_PD);
            }
        } else {
            /* analog mode */

            /* clear ie && oe */
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_1_IE);
            tmpOut &= ~(1 << pos);

            /* clear pu && pd */
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_1_PU);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_1_PD);
        }

        /* set drive && smt && func */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_1_DRV, cfg->drive);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_1_SMT, cfg->smtCtrl);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_1_FUNC_SEL, cfg->gpioFun);
    }

    BL_WR_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4, tmpVal);

    *pOut = tmpOut;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  init GPIO function in pin list
 *
 * @param  gpioFun: GPIO pin function
 * @param  pinList: GPIO pin list
 * @param  cnt: GPIO pin count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Func_Init(GLB_GPIO_FUNC_Type gpioFun, GLB_GPIO_Type *pinList, uint8_t cnt)
{
    GLB_GPIO_Cfg_Type gpioCfg = {
        .gpioPin = GLB_GPIO_PIN_0,
        .gpioFun = (uint8_t)gpioFun,
        .gpioMode = GPIO_MODE_AF,
        .pullType = GPIO_PULL_UP,
        .drive = 1,
        .smtCtrl = 1
    };

    if (gpioFun == GPIO_FUN_ANALOG) {
        gpioCfg.gpioMode = GPIO_MODE_ANALOG;
    }

    for (uint8_t i = 0; i < cnt; i++) {
        gpioCfg.gpioPin = pinList[i];
        GLB_GPIO_Init(&gpioCfg);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set input function enable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_INPUT_Enable(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;
    uint32_t pinOffset;

    pinOffset = (gpioPin >> 1) << 2;
    tmpVal = *(uint32_t *)(GLB_BASE + GLB_GPIO_OFFSET + pinOffset);

    if (gpioPin % 2 == 0) {
        /* [0] is ie */
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
    } else {
        /* [16] is ie */
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_1_IE);
    }

    *(uint32_t *)(GLB_BASE + GLB_GPIO_OFFSET + pinOffset) = tmpVal;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set input function disable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_INPUT_Disable(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;
    uint32_t pinOffset;

    pinOffset = (gpioPin >> 1) << 2;
    tmpVal = *(uint32_t *)(GLB_BASE + GLB_GPIO_OFFSET + pinOffset);

    if (gpioPin % 2 == 0) {
        /* [0] is ie */
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
    } else {
        /* [16] is ie */
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_1_IE);
    }

    *(uint32_t *)(GLB_BASE + GLB_GPIO_OFFSET + pinOffset) = tmpVal;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set output function enable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_OUTPUT_Enable(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFGCTL34);
    tmpVal = tmpVal | (1 << gpioPin);
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFGCTL34, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  GPIO set output function disable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_OUTPUT_Disable(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFGCTL34);
    tmpVal = tmpVal & ~(1 << gpioPin);
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFGCTL34, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  GPIO set High-Z
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Set_HZ(GLB_GPIO_Type gpioPin)
{
    uint32_t *pOut;
    uint32_t pos;
    uint32_t tmpOut;
    uint32_t tmpVal;

    pOut = (uint32_t *)(GLB_BASE + GLB_GPIO_OUTPUT_EN_OFFSET + ((gpioPin >> 5) << 2));
    pos = gpioPin % 32;
    tmpOut = *pOut;

    /* Disable output anyway*/
    tmpOut &= (~(1 << pos));
    *pOut = tmpOut;

    tmpVal = BL_RD_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4);

    /* select GPIO_FUN_GPIO as FUNC_SEL */
    if (gpioPin % 2 == 0) {
        tmpVal = (tmpVal & 0xffff0000);
        tmpVal |= 0x0B00;
    } else {
        tmpVal = (tmpVal & 0x0000ffff);
        tmpVal |= (0x0B00 << 16);
    }

    BL_WR_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4, tmpVal);

    /* Disable output anyway*/
    *pOut = tmpOut;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  GPIO set Pull up
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Set_PullUp(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4);

    /* Set Pull up */
    if (gpioPin % 2 == 0) {
        tmpVal &= (~(1 << 5));
        tmpVal |= (1 << 4);
    } else {
        tmpVal &= (~(1 << 21));
        tmpVal |= (1 << 20);
    }

    BL_WR_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set Pull down
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Set_PullDown(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4);

    /* Set Pull up */
    if (gpioPin % 2 == 0) {
        tmpVal &= (~(1 << 4));
        tmpVal |= (1 << 5);
    } else {
        tmpVal &= (~(1 << 20));
        tmpVal |= (1 << 21);
    }

    BL_WR_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get GPIO function
 *
 * @param  gpioPin: GPIO type
 *
 * @return GPIO function
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
uint8_t ATTR_TCM_SECTION GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4);

    if (gpioPin % 2 == 0) {
        return BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_FUNC_SEL);
    } else {
        return BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_1_FUNC_SEL);
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Get GPIO0-GPIO5 real function
 *
 * @param  gpioPin: GPIO type
 *
 * @return GPIO real function
 *
*******************************************************************************/
GLB_GPIO_REAL_MODE_Type GLB_GPIO_Get_Real_Fun(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;

    CHECK_PARAM((gpioPin <= GLB_GPIO_PIN_5));

    tmpVal = BL_RD_WORD(GLB_BASE + GLB_GPIO_OFFSET + gpioPin / 2 * 4);

    if (gpioPin % 2 == 0) {
        return (GLB_GPIO_REAL_MODE_Type)BL_GET_REG_BITS_VAL(tmpVal, GLB_REAL_GPIO_0_FUNC_SEL);
    } else {
        return (GLB_GPIO_REAL_MODE_Type)BL_GET_REG_BITS_VAL(tmpVal, GLB_REAL_GPIO_1_FUNC_SEL);
    }
}

/****************************************************************************/ /**
 * @brief  Write GPIO
 *
 * @param  gpioPin: GPIO type
 * @param  val: GPIO value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Write(GLB_GPIO_Type gpioPin, uint32_t val)
{
    uint32_t *pOut = (uint32_t *)(GLB_BASE + GLB_GPIO_OUTPUT_OFFSET + ((gpioPin >> 5) << 2));
    uint32_t pos = gpioPin % 32;
    uint32_t tmpOut;

    tmpOut = *pOut;

    if (val > 0) {
        tmpOut |= (1 << pos);
    } else {
        tmpOut &= (~(1 << pos));
    }

    *pOut = tmpOut;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Read GPIO
 *
 * @param  gpioPin: GPIO type
 *
 * @return GPIO value
 *
*******************************************************************************/
uint32_t GLB_GPIO_Read(GLB_GPIO_Type gpioPin)
{
    uint32_t *p = (uint32_t *)(GLB_BASE + GLB_GPIO_INPUT_OFFSET + ((gpioPin >> 5) << 2));
    uint32_t pos = gpioPin % 32;

    if ((*p) & (1 << pos)) {
        return 1;
    } else {
        return 0;
    }
}

/****************************************************************************/ /**
 * @brief  Set GLB GPIO interrupt mask
 *
 * @param  gpioPin: GPIO type
 * @param  intMask: GPIO interrupt MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_IntMask(GLB_GPIO_Type gpioPin, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    if (gpioPin < 32) {
        /* GPIO0 ~ GPIO31 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_MASK1);

        if (intMask == MASK) {
            tmpVal = tmpVal | (1 << gpioPin);
        } else {
            tmpVal = tmpVal & ~(1 << gpioPin);
        }

        BL_WR_REG(GLB_BASE, GLB_GPIO_INT_MASK1, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set GLB GPIO interrupt mask
 *
 * @param  gpioPin: GPIO type
 * @param  intClear: GPIO interrupt clear or unclear
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_IntClear(GLB_GPIO_Type gpioPin, BL_Sts_Type intClear)
{
    uint32_t tmpVal;

    if (gpioPin < 32) {
        /* GPIO0 ~ GPIO31 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_CLR1);

        if (intClear == SET) {
            tmpVal = tmpVal | (1 << gpioPin);
        } else {
            tmpVal = tmpVal & ~(1 << gpioPin);
        }

        BL_WR_REG(GLB_BASE, GLB_GPIO_INT_CLR1, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get GLB GPIO interrrupt status
 *
 * @param  gpioPin: GPIO type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type GLB_Get_GPIO_IntStatus(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal = 0;

    if (gpioPin < 32) {
        /* GPIO0 ~ GPIO31 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_STAT1);
    }

    return (tmpVal & (1 << gpioPin)) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  Clear GLB GPIO interrrupt status
 *
 * @param  gpioPin: GPIO type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Clr_GPIO_IntStatus(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;

    if (gpioPin < 32) {
        /* GPIO0 ~ GPIO31 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_CLR1);
        tmpVal = tmpVal | (1 << gpioPin);
        BL_WR_REG(GLB_BASE, GLB_GPIO_INT_CLR1, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set GLB GPIO interrupt mode
 *
 * @param  gpioPin: GPIO type
 * @param  intCtlMod: GPIO interrupt control mode
 * @param  intTrgMod: GPIO interrupt trigger mode
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_GPIO_IntMod(GLB_GPIO_Type gpioPin, GLB_GPIO_INT_CONTROL_Type intCtlMod, GLB_GPIO_INT_TRIG_Type intTrgMod)
{
    uint32_t tmpVal;
    uint32_t tmpGpioPin;

    CHECK_PARAM(IS_GLB_GPIO_INT_CONTROL_TYPE(intCtlMod));
    CHECK_PARAM(IS_GLB_GPIO_INT_TRIG_TYPE(intTrgMod));

    if (gpioPin < GLB_GPIO_PIN_10) {
        /* GPIO0 ~ GPIO9 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET1);
        tmpGpioPin = gpioPin;
        tmpVal = (tmpVal & ~(0x7 << (3 * tmpGpioPin))) | (((intCtlMod << 2) | intTrgMod) << (3 * tmpGpioPin));
        BL_WR_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET1, tmpVal);
    } else if (gpioPin < GLB_GPIO_PIN_20) {
        /* GPIO10 ~ GPIO19 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET2);
        tmpGpioPin = gpioPin - GLB_GPIO_PIN_10;
        tmpVal = (tmpVal & ~(0x7 << (3 * tmpGpioPin))) | (((intCtlMod << 2) | intTrgMod) << (3 * tmpGpioPin));
        BL_WR_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET2, tmpVal);
    } else {
        /* GPIO20 ~ GPIO29 */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET3);
        tmpGpioPin = gpioPin - GLB_GPIO_PIN_20;
        tmpVal = (tmpVal & ~(0x7 << (3 * tmpGpioPin))) | (((intCtlMod << 2) | intTrgMod) << (3 * tmpGpioPin));
        BL_WR_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET3, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get GPIO interrupt control mode
 *
 * @param  gpioPin: GPIO pin type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
GLB_GPIO_INT_CONTROL_Type GLB_Get_GPIO_IntCtlMod(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;
    uint32_t bitVal;

    if (gpioPin < GLB_GPIO_PIN_10) {
        /* GPIO0 - GPIO9 */
        bitVal = gpioPin - 0;
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET1);
        tmpVal = (tmpVal & (0x7 << (bitVal * 3))) >> (bitVal * 3);
        return (tmpVal >> 2) ? GLB_GPIO_INT_CONTROL_ASYNC : GLB_GPIO_INT_CONTROL_SYNC;
    } else if ((gpioPin > GLB_GPIO_PIN_9) && (gpioPin < GLB_GPIO_PIN_20)) {
        /* GPIO10 - GPIO19 */
        bitVal = gpioPin - 10;
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET2);
        tmpVal = (tmpVal & (0x7 << (bitVal * 3))) >> (bitVal * 3);
        return (tmpVal >> 2) ? GLB_GPIO_INT_CONTROL_ASYNC : GLB_GPIO_INT_CONTROL_SYNC;
    } else {
        /* GPIO20 - GPIO29 */
        bitVal = gpioPin - 20;
        tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_INT_MODE_SET3);
        tmpVal = (tmpVal & (0x7 << (bitVal * 3))) >> (bitVal * 3);
        return (tmpVal >> 2) ? GLB_GPIO_INT_CONTROL_ASYNC : GLB_GPIO_INT_CONTROL_SYNC;
    }
}

/****************************************************************************/ /**
 * @brief  GPIO INT0 IRQHandler install
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_INT0_IRQHandler_Install(void)
{
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(GPIO_INT0_IRQn, GPIO_INT0_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO interrupt IRQ handler callback install
 *
 * @param  gpioPin: GPIO pin type
 * @param  cbFun: callback function
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_INT0_Callback_Install(GLB_GPIO_Type gpioPin, intCallback_Type *cbFun)
{
    if (gpioPin < 32) {
        glbGpioInt0CbfArra[gpioPin] = cbFun;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO interrupt IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void GPIO_INT0_IRQHandler(void)
{
    GLB_GPIO_Type gpioPin;
    uint32_t timeOut = 0;

    for (gpioPin = GLB_GPIO_PIN_0; gpioPin <= GLB_GPIO_PIN_22; gpioPin++) {
        if (SET == GLB_Get_GPIO_IntStatus(gpioPin)) {
            GLB_GPIO_IntClear(gpioPin, SET);

            /* timeout check */
            timeOut = GLB_GPIO_INT0_CLEAR_TIMEOUT;

            do {
                timeOut--;
            } while ((SET == GLB_Get_GPIO_IntStatus(gpioPin)) && timeOut);

            if (!timeOut) {
                MSG("WARNING: Clear GPIO interrupt status fail.\r\n");
            }

            /* if timeOut==0, GPIO interrupt status not cleared */
            GLB_GPIO_IntClear(gpioPin, RESET);

            if (glbGpioInt0CbfArra[gpioPin] != NULL) {
                /* Call the callback function */
                glbGpioInt0CbfArra[gpioPin]();
            }
        }
    }
}
#endif

/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL602_Peripheral_Driver */
