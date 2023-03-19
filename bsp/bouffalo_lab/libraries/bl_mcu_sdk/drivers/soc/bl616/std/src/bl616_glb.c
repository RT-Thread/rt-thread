/**
  ******************************************************************************
  * @file    bl616_glb.c
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

#include "bl616_clock.h"
#include "bl616_glb.h"
#include "bl616_aon.h"
#include "bl616_hbn.h"
#include "bl616_pds.h"

/** @addtogroup  BL616_Peripheral_Driver
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
#define GLB_CLK_SET_DUMMY_TIMEOUT (0xFF)
#define GLB_FREQ_RC32M            (32000000)

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

/* WiFi PLL Config*/
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_32M_38P4M_40M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 0,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 0,        /*!< pll_icp_1u */
    .clkpllIcp5u = 2,        /*!< pll_icp_5u */
    .clkpllRz = 3,           /*!< pll_rz */
    .clkpllCz = 1,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 1,      /*!< pll_r4_short */
    .clkpllC4En = 0,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 1,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 1,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_24M = {
    .clkpllRefdivRatio = 1,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 0,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 0,        /*!< pll_icp_1u */
    .clkpllIcp5u = 2,        /*!< pll_icp_5u */
    .clkpllRz = 3,           /*!< pll_rz */
    .clkpllCz = 1,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 1,      /*!< pll_r4_short */
    .clkpllC4En = 0,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 1,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 1,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_26M = {
    .clkpllRefdivRatio = 1,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION wifiPllCfg_960M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 0 },                                 /*!< XTAL is None */
    { &wifiPllBasicCfg_24M, 0x1400000, 0 },           /*!< XTAL is 24M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1E00000, 0 }, /*!< XTAL is 32M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1900000, 0 }, /*!< XTAL is 38.4M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1800000, 0 }, /*!< XTAL is 40M */
    { &wifiPllBasicCfg_26M, 0x1276276, 0 },           /*!< XTAL is 26M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1E00000, 0 }, /*!< XTAL is RC32M */
};
const uint32_t ATTR_CLOCK_CONST_SECTION usbPllSdmin_12M = 0x28000;
const uint32_t ATTR_CLOCK_CONST_SECTION sscDivSdmin_24M = 0x28000;

/* Audio PLL Config*/
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPllBasicCfg_24M_26M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPllBasicCfg_32M_38P4M_40M = {
    .clkpllRefdivRatio = 4,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_491P52M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 20 },                                /*!< XTAL is None */
    { &audioPllBasicCfg_24M_26M, 0x147AE, 20 },       /*!< XTAL is 24M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1EB85, 20 }, /*!< XTAL is 32M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x19999, 20 }, /*!< XTAL is 38.4M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x18937, 20 }, /*!< XTAL is 40M */
    { &audioPllBasicCfg_24M_26M, 0x12E79, 20 },       /*!< XTAL is 26M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1EB85, 20 }, /*!< XTAL is RC32M */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_451P58M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 20 },                                /*!< XTAL is None */
    { &audioPllBasicCfg_24M_26M, 0x12D0D, 20 },       /*!< XTAL is 24M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1C394, 20 }, /*!< XTAL is 32M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x17851, 20 }, /*!< XTAL is 38.4M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x16943, 20 }, /*!< XTAL is 40M */
    { &audioPllBasicCfg_24M_26M, 0x115E5, 20 },       /*!< XTAL is 26M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1C394, 20 }, /*!< XTAL is RC32M */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_400M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 8 },                                /*!< XTAL is None */
    { &audioPllBasicCfg_24M_26M, 0x10AAA, 8 },       /*!< XTAL is 24M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x19000, 8 }, /*!< XTAL is 32M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x14D55, 8 }, /*!< XTAL is 38.4M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x14000, 8 }, /*!< XTAL is 40M */
    { &audioPllBasicCfg_24M_26M, 0xF627, 8 },        /*!< XTAL is 26M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x19000, 8 }, /*!< XTAL is RC32M */
};

/* Audio PLL Config*/
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll384BasicCfg_24M_26M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll384BasicCfg_32M_38P4M_40M = {
    .clkpllRefdivRatio = 4,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_384M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 8 },                                   /*!< XTAL is None */
    { &audioPll384BasicCfg_24M_26M, 0x10000, 8 },       /*!< XTAL is 24M */
    { &audioPll384BasicCfg_32M_38P4M_40M, 0x18000, 8 }, /*!< XTAL is 32M */
    { &audioPll384BasicCfg_32M_38P4M_40M, 0x14000, 8 }, /*!< XTAL is 38.4M */
    { &audioPll384BasicCfg_32M_38P4M_40M, 0x13333, 8 }, /*!< XTAL is 40M */
    { &audioPll384BasicCfg_24M_26M, 0xEC4E, 8 },        /*!< XTAL is 26M */
    { &audioPll384BasicCfg_32M_38P4M_40M, 0x18000, 8 }, /*!< XTAL is RC32M */
};

const GLB_SLAVE_GRP_0_TBL_Type ATTR_CLOCK_CONST_SECTION glb_slave_grp_0_table[GLB_SLAVE_GRP_0_MAX] = {
    { GLB_ADC_CFG0_OFFSET, GLB_GPADC_32M_DIV_EN_POS, GLB_GPADC_32M_CLK_SEL_POS, GLB_GPADC_32M_CLK_DIV_POS, GLB_GPADC_32M_DIV_EN_LEN, GLB_GPADC_32M_CLK_SEL_LEN, GLB_GPADC_32M_CLK_DIV_LEN },
    { GLB_IR_CFG0_OFFSET, GLB_IR_CLK_EN_POS, 0, GLB_IR_CLK_DIV_POS, GLB_IR_CLK_EN_LEN, 0, GLB_IR_CLK_DIV_LEN },
    { GLB_I2C_CFG0_OFFSET, GLB_I2C_CLK_EN_POS, GLB_I2C_CLK_SEL_POS, GLB_I2C_CLK_DIV_POS, GLB_I2C_CLK_EN_LEN, GLB_I2C_CLK_SEL_LEN, GLB_I2C_CLK_DIV_LEN },
    { GLB_SPI_CFG0_OFFSET, GLB_SPI_CLK_EN_POS, GLB_SPI_CLK_SEL_POS, GLB_SPI_CLK_DIV_POS, GLB_SPI_CLK_EN_LEN, GLB_SPI_CLK_SEL_LEN, GLB_SPI_CLK_DIV_LEN },
    { GLB_PEC_CFG0_OFFSET, GLB_PEC_CLK_EN_POS, GLB_PEC_CLK_SEL_POS, GLB_PEC_CLK_DIV_POS, GLB_PEC_CLK_EN_LEN, GLB_PEC_CLK_SEL_LEN, GLB_PEC_CLK_DIV_LEN },
    { GLB_DBI_CFG0_OFFSET, GLB_DBI_CLK_EN_POS, GLB_DBI_CLK_SEL_POS, GLB_DBI_CLK_DIV_POS, GLB_DBI_CLK_EN_LEN, GLB_DBI_CLK_SEL_LEN, GLB_DBI_CLK_DIV_LEN },
    { GLB_AUDIO_CFG0_OFFSET, GLB_REG_AUDIO_AUTO_DIV_EN_POS, 0, 0, GLB_REG_AUDIO_AUTO_DIV_EN_LEN, 0, 0 },
    { GLB_AUDIO_CFG0_OFFSET, GLB_REG_AUDIO_ADC_CLK_EN_POS, 0, GLB_REG_AUDIO_ADC_CLK_DIV_POS, GLB_REG_AUDIO_ADC_CLK_EN_LEN, 0, GLB_REG_AUDIO_ADC_CLK_DIV_LEN },
    { GLB_AUDIO_CFG1_OFFSET, GLB_REG_AUDIO_SOLO_CLK_EN_POS, 0, GLB_REG_AUDIO_SOLO_CLK_DIV_POS, GLB_REG_AUDIO_SOLO_CLK_EN_LEN, 0, GLB_REG_AUDIO_SOLO_CLK_DIV_LEN },
    { GLB_CAM_CFG0_OFFSET, GLB_REG_CAM_REF_CLK_EN_POS, GLB_REG_CAM_REF_CLK_SRC_SEL_POS, GLB_REG_CAM_REF_CLK_DIV_POS, GLB_REG_CAM_REF_CLK_EN_LEN, GLB_REG_CAM_REF_CLK_SRC_SEL_LEN, GLB_REG_CAM_REF_CLK_DIV_LEN },
    { GLB_SDH_CFG0_OFFSET, GLB_REG_SDH_CLK_EN_POS, GLB_REG_SDH_CLK_SEL_POS, GLB_REG_SDH_CLK_DIV_POS, GLB_REG_SDH_CLK_EN_LEN, GLB_REG_SDH_CLK_SEL_LEN, GLB_REG_SDH_CLK_DIV_LEN },
    { GLB_PSRAM_CFG0_OFFSET, GLB_REG_PSRAMB_CLK_EN_POS, GLB_REG_PSRAMB_CLK_SEL_POS, GLB_REG_PSRAMB_CLK_DIV_POS, GLB_REG_PSRAMB_CLK_EN_LEN, GLB_REG_PSRAMB_CLK_SEL_LEN, GLB_REG_PSRAMB_CLK_DIV_LEN },
};

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
 * @brief  set mcu muxpll 160M selection
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_MCU_Muxpll_160M_Sel(GLB_MCU_MUXPLL_160M_CLK_SEL_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_MCU_MUXPLL_160M_CLK_SEL_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_TOP_MUXPLL_160M_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get mcu muxpll 160M selection
 *
 * @param  None
 *
 * @return 160M mux select value
 *
*******************************************************************************/
GLB_MCU_MUXPLL_160M_CLK_SEL_Type ATTR_CLOCK_SECTION GLB_Get_MCU_Muxpll_160M_Sel(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    return (GLB_MCU_MUXPLL_160M_CLK_SEL_Type)(BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_TOP_MUXPLL_160M_SEL));
}

/****************************************************************************/ /**
 * @brief  set top muxpll 80M selection
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_MCU_Muxpll_80M_Sel(GLB_MCU_MUXPLL_80M_CLK_SEL_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_MCU_MUXPLL_80M_CLK_SEL_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_TOP_MUXPLL_80M_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get mcu muxpll 80M selection
 *
 * @param  None
 *
 * @return 80M mux select value
 *
*******************************************************************************/
GLB_MCU_MUXPLL_80M_CLK_SEL_Type ATTR_CLOCK_SECTION GLB_Get_MCU_Muxpll_80M_Sel(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    return (GLB_MCU_MUXPLL_80M_CLK_SEL_Type)(BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_TOP_MUXPLL_80M_SEL));
}

/****************************************************************************/ /**
 * @brief  set isp muxpll 80M selection
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_ISP_Muxpll_80M_Sel(GLB_ISP_MUXPLL_80M_CLK_SEL_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_ISP_MUXPLL_80M_CLK_SEL_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_ISP_MUXPLL_80M_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get isp muxpll 80M selection
 *
 * @param  None
 *
 * @return 80M mux select value
 *
*******************************************************************************/
GLB_ISP_MUXPLL_80M_CLK_SEL_Type ATTR_CLOCK_SECTION GLB_Get_ISP_Muxpll_80M_Sel(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    return (GLB_ISP_MUXPLL_80M_CLK_SEL_Type)(BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_ISP_MUXPLL_80M_SEL));
}

/****************************************************************************/ /**
 * @brief  power on all PLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllType: only power on xtal
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_On_XTAL_And_PLL_CLK(GLB_XTAL_Type xtalType, GLB_PLL_Type pllType)
{
    uint32_t tmpVal;
    HBN_MCU_XCLK_Type mcuXclkSel;
    HBN_MCU_ROOT_CLK_Type mcuRootClkSel;
    volatile GLB_PLL_REF_CLK_Type refClk;

    CHECK_PARAM(IS_GLB_XTAL_TYPE(xtalType));
    CHECK_PARAM((pllType < (GLB_PLL_AUPLL * 2)));

    if (xtalType == GLB_XTAL_NONE) {
        return ERROR;
    }

    if (xtalType != GLB_XTAL_RC32M) {
        /* power on xtal first */
        AON_Power_On_XTAL();
    }

#if defined(DUAL_CORE)
    GLB_CORE_ID_Type coreType;
    coreType = GLB_Get_Core_Type();
    if ((GLB_CORE_ID_M0 == coreType)) {
#endif
        /* M0 */
        /* Before config XTAL and PLL ,make sure root clk is from RC32M */
        mcuXclkSel = HBN_Get_MCU_XCLK_Sel();
        mcuRootClkSel = HBN_Get_MCU_Root_CLK_Sel();
        if ((mcuXclkSel != HBN_MCU_XCLK_RC32M) || (mcuRootClkSel != HBN_MCU_ROOT_CLK_XCLK)) {
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
        }
        GLB_Set_MCU_System_CLK_Div(0, 0);
#if defined(DUAL_CORE)
    }
#endif

    HBN_Set_Xtal_Type(xtalType);

    if (GLB_PLL_NONE == pllType) {
        GLB_CLK_SET_DUMMY_WAIT;
        return SUCCESS;
    }

    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }

    /* power on wifipll */
    if (pllType & GLB_PLL_WIFIPLL) {
        GLB_Power_Off_WIFIPLL();
        GLB_WIFIPLL_Ref_Clk_Sel(refClk);
        GLB_Power_On_WIFIPLL(&wifiPllCfg_960M[xtalType], 0);
    }

    /* power on aupll */
    if (pllType & GLB_PLL_AUPLL) {
        GLB_Power_Off_AUPLL();
        GLB_AUPLL_Ref_Clk_Sel(refClk);
        GLB_Power_On_AUPLL(&audioPllCfg_491P52M[xtalType], 0);
    }

    arch_delay_us(75);

    if (xtalType != GLB_XTAL_RC32M) {
        /* if power on xtal, always set xclk from xtal */
        HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_XTAL);
    }

    /* enable all PLL clock output */
    /* GLB reg_pll_en = 1, cannot be zero */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_PLL_EN);
    BL_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power off wifipll
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_Off_WIFIPLL(void)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;

    /* cfg0 : pu_wifipll=0 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PU_WIFIPLL, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* cfg0 : pu_wifipll_sfreg=0 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PU_WIFIPLL_SFREG, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB wifipll ref clock select
 *
 * @param  refClk: PLL ref clock select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_WIFIPLL_Ref_Clk_Sel(GLB_PLL_REF_CLK_Type refClk)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PLL_REF_CLK_TYPE(refClk));

    REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;

    /* xxxpll_refclk_sel */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    if (GLB_PLL_REFCLK_XTAL == refClk) {
        /* wifipll_refclk_sel different from other's pll, 1 means xtal */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_REFCLK_SEL, 1);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_REFCLK_SEL, refClk);
    }
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power on wifipll
 *
 * @param  cfg: GLB PLL configuration
 * @param  waitStable: wait PLL clock stable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_On_WIFIPLL(const GLB_WA_PLL_Cfg_Type *const cfg, uint8_t waitStable)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;

    /* Step1:config parameter */
    /* cfg1:Set wifipll_refclk_sel and wifipll_refdiv_ratio */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_REFDIV_RATIO, cfg->basicCfg->clkpllRefdivRatio);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    /* cfg2:Set wifipll_int_frac_sw,wifipll_icp_1u,wifipll_icp_5u */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_INT_FRAC_SW, cfg->basicCfg->clkpllIntFracSw);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_ICP_1U, cfg->basicCfg->clkpllIcp1u);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_ICP_5U, cfg->basicCfg->clkpllIcp5u);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 2, tmpVal);

    /* cfg3:Set wifipll_rz,wifipll_cz,wifipll_c3,wifipll_r4_short,wifipll_r4_en */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_RZ, cfg->basicCfg->clkpllRz);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_CZ, cfg->basicCfg->clkpllCz);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_C3, cfg->basicCfg->clkpllC3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_R4_SHORT, cfg->basicCfg->clkpllR4Short);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_C4_EN, cfg->basicCfg->clkpllC4En);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 3, tmpVal);

    /* cfg4:Set wifipll_sel_sample_clk */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SEL_SAMPLE_CLK, cfg->basicCfg->clkpllSelSampleClk);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 4, tmpVal);

    /* cfg5:Set wifipll_vco_speed */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_VCO_SPEED, cfg->basicCfg->clkpllVcoSpeed);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 5, tmpVal);

    /* cfg6:Set wifipll_sdm_bypass,wifipll_sdmin */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_CTRL_HW, cfg->basicCfg->clkpllSdmCtrlHw);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_BYPASS, cfg->basicCfg->clkpllSdmBypass);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDMIN, cfg->clkpllSdmin);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 6, tmpVal);

    /* cfg10:always set usbpll_sdmin */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_USBPLL_SDMIN, usbPllSdmin_12M);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 10, tmpVal);

    /* cfg12:always set sscdiv_sdmin */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 12);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SSCDIV_SDMIN, sscDivSdmin_24M);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 12, tmpVal);

    /* Step2:config pu */
    /* cfg0 : pu_wifipll_sfreg=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PU_WIFIPLL_SFREG, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
    arch_delay_us(3);

    /* cfg0 : pu_wifipll=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PU_WIFIPLL, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
    arch_delay_us(3);

    /* toggle sdm_reset (pulse 0 > 1us) */
    /* cfg0 : wifipll_sdm_reset */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_RSTB, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* Step3:reset pll */
    /* cfg0 : toggle wifipll_reset_fbdv, pulse 0 > 1us */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_FBDV_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_FBDV_RSTB, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_FBDV_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* Step4:enable output clock */
    /* cfg8 : wifipll clock enable */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 8);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV3);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV4);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV5);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV6);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV8);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV10);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV12);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV20);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV30);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 8, tmpVal);

    if (waitStable) {
        /* Wait 1.5*30us    */
        arch_delay_us(45);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power off aupll
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_Off_AUPLL(void)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;

    /* cfg0 : pu_aupll=0 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* cfg0 : pu_aupll_sfreg=0 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL_SFREG, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB wifi aupll ref clock select
 *
 * @param  refClk: PLL ref clock select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_AUPLL_Ref_Clk_Sel(GLB_PLL_REF_CLK_Type refClk)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PLL_REF_CLK_TYPE(refClk));

    REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;

    /* xxxpll_refclk_sel */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFCLK_SEL, refClk);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power on PLL
 *
 * @param  cfg: GLB PLL configuration
 * @param  waitStable: wait PLL clock stable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_On_AUPLL(const GLB_WA_PLL_Cfg_Type *const cfg, uint8_t waitStable)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;

    /* Step1:config parameter */
    /* cfg1:Set aupll_refclk_sel and aupll_refdiv_ratio */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFDIV_RATIO, cfg->basicCfg->clkpllRefdivRatio);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    /* cfg2:Set aupll_int_frac_sw,aupll_icp_1u,aupll_icp_5u */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_INT_FRAC_SW, cfg->basicCfg->clkpllIntFracSw);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_ICP_1U, cfg->basicCfg->clkpllIcp1u);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_ICP_5U, cfg->basicCfg->clkpllIcp5u);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 2, tmpVal);

    /* cfg3:Set aupll_rz,aupll_cz,aupll_c3,aupll_r4_short,aupll_r4_en */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_RZ, cfg->basicCfg->clkpllRz);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_CZ, cfg->basicCfg->clkpllCz);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_C3, cfg->basicCfg->clkpllC3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_R4_SHORT, cfg->basicCfg->clkpllR4Short);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_C4_EN, cfg->basicCfg->clkpllC4En);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 3, tmpVal);

    /* cfg4:Set aupll_sel_sample_clk */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SEL_SAMPLE_CLK, cfg->basicCfg->clkpllSelSampleClk);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 4, tmpVal);

    /* cfg5:Set aupll_vco_speed */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_VCO_SPEED, cfg->basicCfg->clkpllVcoSpeed);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 5, tmpVal);

    /* cfg6:Set aupll_sdm_bypass,aupll_sdmin */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_BYPASS, cfg->basicCfg->clkpllSdmBypass);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDMIN, cfg->clkpllSdmin);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 6, tmpVal);

    /* cfg1:Set aupll_postdiv */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_POSTDIV, cfg->clkpllPostDiv);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    /* Step2:config pu */
    /* cfg0 : pu_aupll_sfreg=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL_SFREG, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
    arch_delay_us(3);

    /* cfg0 : pu_wifipll=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
    arch_delay_us(3);

    /* toggle sdm_reset (pulse 0 > 1us) */
    /* cfg0 : aupll_sdm_reset */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* Step3:reset pll */
    /* cfg0 : toggle aupll_reset_fbdv, pulse 0 > 1us */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* Step4:enable output clock */
    /* cfg8 : wifipll/aupll/cpupll clock enable */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 8);
    tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV1);
    tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV2);
    tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV2P5);
    tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV5);
    tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV6);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 8, tmpVal);

    if (waitStable) {
        /* Wait 1.5*30us    */
        arch_delay_us(45);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB enable or disable USB clock
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_USB_CLK_From_WIFIPLL(uint8_t enable)
{
    uint32_t tmpVal = 0;

    /* pu_usbpll_mmdiv */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_PLL_CFG10);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_PU_USBPLL_MMDIV);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PU_USBPLL_MMDIV);
    }
    BL_WR_REG(GLB_BASE, GLB_WIFI_PLL_CFG10, tmpVal);

    /* delay > 2us */
    arch_delay_us(3);

    /* toggle usbpll_rstb */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_PLL_CFG10);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_USBPLL_RSTB);
    BL_WR_REG(GLB_BASE, GLB_WIFI_PLL_CFG10, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_PLL_CFG10);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_USBPLL_RSTB);
    BL_WR_REG(GLB_BASE, GLB_WIFI_PLL_CFG10, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_PLL_CFG10);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_USBPLL_RSTB);
    BL_WR_REG(GLB_BASE, GLB_WIFI_PLL_CFG10, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB enable or disable SSC clock
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_SSC_CLK_From_WIFIPLL(uint8_t enable)
{
    uint32_t tmpVal = 0;

    /* pu_usbpll_mmdiv */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_PLL_CFG12);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_PU_SSCDIV_MMDIV);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PU_SSCDIV_MMDIV);
    }
    BL_WR_REG(GLB_BASE, GLB_WIFI_PLL_CFG12, tmpVal);

    /* delay > 2us */
    arch_delay_us(3);

    /* toggle sscdiv_rstb */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_PLL_CFG12);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SSCDIV_RSTB);
    BL_WR_REG(GLB_BASE, GLB_WIFI_PLL_CFG12, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_PLL_CFG12);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SSCDIV_RSTB);
    BL_WR_REG(GLB_BASE, GLB_WIFI_PLL_CFG12, tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_WIFI_PLL_CFG12);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SSCDIV_RSTB);
    BL_WR_REG(GLB_BASE, GLB_WIFI_PLL_CFG12, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set System clock divider
 *
 * @param  mcuClkDiv: HCLK divider
 * @param  mcuPBclkDiv: BCLK divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_MCU_System_CLK_Div(uint8_t mcuClkDiv, uint8_t mcuPBclkDiv)
{
    uint32_t tmpVal;
    uint32_t timeout = 1024;
    HBN_MCU_XCLK_Type xclkSel;
    HBN_MCU_ROOT_CLK_Type rootClkSel;

    /* get root clock */
    xclkSel = HBN_Get_MCU_XCLK_Sel();
    rootClkSel = HBN_Get_MCU_Root_CLK_Sel();

    if ((xclkSel != HBN_MCU_XCLK_RC32M) || (rootClkSel != HBN_MCU_ROOT_CLK_XCLK)) {
        HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
        HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    }

    /* config hclk_div=mcuClkDiv */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV, mcuClkDiv);
    BL_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);

    /* config bclk_div=mcuPBclkDiv */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV, mcuPBclkDiv);
    BL_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);
    /* bclk act pulse */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SYS_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV_ACT_PULSE, 1);
    BL_WR_REG(GLB_BASE, GLB_SYS_CFG1, tmpVal);

    timeout = 1024;
    do {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_SYS_CFG1);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal, GLB_STS_BCLK_PROT_DONE);
    } while ((--timeout) && (!tmpVal));
    if (!timeout) {
        return ERROR;
    }

    /* recover root clock */
    HBN_Set_MCU_XCLK_Sel(xclkSel);
    HBN_Set_MCU_Root_CLK_Sel(rootClkSel);

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get System clock divider
 *
 * @param  mcuClkDiv: HCLK divider
 * @param  mcuPBclkDiv: BCLK divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Get_MCU_System_CLK_Div(uint8_t *mcuClkDiv, uint8_t *mcuPBclkDiv)
{
    if ((NULL == mcuClkDiv) || (NULL == mcuPBclkDiv)) {
        return ERROR;
    }

    *mcuClkDiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_HCLK_DIV);
    *mcuPBclkDiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_BCLK_DIV);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set mcu System clock
 *
 * @param  clkFreq: mcu system clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_Type clkFreq)
{
    uint32_t tmpVal;
    HBN_MCU_XCLK_Type mcuXclkSel;

    CHECK_PARAM(IS_GLB_MCU_SYS_CLK_TYPE(clkFreq));

    /* get xclk&&rootclk clock */
    mcuXclkSel = HBN_Get_MCU_XCLK_Sel();

    /* change root clock to rc32m */
    HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    GLB_Set_MCU_System_CLK_Div(0, 0);

    /* select pll output clock before select root clock */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CPU_CORE_CFG1);
    switch (clkFreq) {
        case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 0);
            break;
        case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 1);
            break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_240M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 2);
            break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_320M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 3);
            break;
        default:
            break;
    }
    BL_WR_REG(PDS_BASE, PDS_CPU_CORE_CFG1, tmpVal);

    /* select root clock */
    switch (clkFreq) {
        case GLB_MCU_SYS_CLK_RC32M:
            GLB_Set_MCU_System_CLK_Div(0, 0);
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            break;
        case GLB_MCU_SYS_CLK_XTAL:
            GLB_Set_MCU_System_CLK_Div(0, 0);
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_XTAL);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            break;
        case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV2:
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0, 2);
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_AUPLL_DIV2);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV1:
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(1, 2);
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_AUPLL_DIV1);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_240M:
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0, 2);
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_WIFIPLL_240M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_320M:
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0, 3);
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_WIFIPLL_320M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        default:
            break;
    }

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get core type
 *
 * @param  None
 *
 * @return core type
 *
*******************************************************************************/
GLB_CORE_ID_Type ATTR_CLOCK_SECTION GLB_Get_Core_Type(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_WORD(CORE_ID_ADDRESS);

    switch (tmpVal) {
        case CORE_ID_M0:
            return GLB_CORE_ID_M0;
        default:
            return GLB_CORE_ID_INVALID;
    }

    return GLB_CORE_ID_INVALID;
}

/****************************************************************************/ /**
 * @brief  set CPU reset address
 *
 * @param  coreID: core type
 * @param  addr: reset address
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_CPU_Reset_Address(GLB_CORE_ID_Type coreID, uint32_t addr)
{
    CHECK_PARAM(IS_GLB_CORE_ID_TYPE(coreID));

    switch (coreID) {
        case GLB_CORE_ID_M0:
            BL_WR_REG(PDS_BASE, PDS_CPU_CORE_CFG14, addr);
            break;
        default:
            return ERROR;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Clr_EMI_Reset_Gate(void)
{
    uint32_t tmpVal;

    /* clear EMI swrst bit */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SWRST_S1_EXT_EMI_MISC);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG0, tmpVal);

    /* set EMI cgen bit */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CGEN_S1_EXT_EMI_MISC);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG2, tmpVal);

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
#ifndef BOOTROM
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
#endif

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
#ifndef BOOTROM
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_IR_CLK_SRC_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3F));

    (void)clkSel;

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
#endif
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
    } else {
        return ERROR;
    }

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

    if (clkSel == GLB_SFLASH_CLK_TOP_AUPLL_DIV5) {
        GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_AUPLL_DIV5);
    }

    /* clock divider */
    /* Select flash clock, all Flash CLKs are divied by PLL_480M */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SF_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_DIV, div);
    switch (clkSel) {
        case GLB_SFLASH_CLK_WIFIPLL_120M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x0);
            break;
        case GLB_SFLASH_CLK_XTAL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x1);
            break;
        case GLB_SFLASH_CLK_TOP_AUPLL_DIV5:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2, 0x3);
            break;
        case GLB_SFLASH_CLK_MUXPLL_80M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x1);
            break;
        case GLB_SFLASH_CLK_BCLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL, 0x2);
            break;
        case GLB_SFLASH_CLK_WIFIPLL_96M:
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
#ifndef BOOTROM
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
#endif
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
#ifndef BOOTROM
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
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  swap SPI gpio pins sig function
 *
 * @param  group: SPI swap set group
 * @param  swap: swap or no swap
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_SPI_Sig_Swap_Set(GLB_SPI_SIG_SWAP_GRP_Type group, uint8_t swap)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal2 = 0;

    CHECK_PARAM(IS_GLB_SPI_SIG_SWAP_GRP_TYPE(group));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, GLB_SPI_SWAP_SET);
    if (swap) {
        tmpVal2 |= (1 << group);
    } else {
        tmpVal2 &= ~(1 << group);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SPI_SWAP_SET, tmpVal2);
    BL_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set PEC clock
 *
 * @param  enable: Enable or disable PEC clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_PEC_CLK(uint8_t enable, GLB_PEC_CLK_Type clkSel, uint8_t div)
{
#ifndef BOOTROM
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PEC_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x1F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PEC_CFG0);
    tmpVal >>= 1;
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PEC_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_PEC_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PEC_CFG0);
    tmpVal >>= 1;
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PEC_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PEC_CLK_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_PEC_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PEC_CFG0);
    tmpVal >>= 1;
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_PEC_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PEC_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_PEC_CFG0, tmpVal);
#endif
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
    tmpVal >>= 1;
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PWM1_IO_SEL, ioSel);
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
 * @brief  set DBI clock
 *
 * @param  enable: Enable or disable DBI clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DBI_CLK(uint8_t enable, GLB_DBI_CLK_Type clkSel, uint8_t div)
{
#ifndef BOOTROM
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DBI_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x1F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DBI_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DBI_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_DBI_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DBI_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DBI_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_DBI_CLK_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DBI_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DBI_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_DBI_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_DBI_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_DBI_CFG0, tmpVal);
#endif
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

    CHECK_PARAM((BmxCfg->timeoutEn) <= 0xF);
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
#ifndef BOOTROM
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    if (divEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_AUTO_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_AUTO_DIV_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);
#endif
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
#ifndef BOOTROM
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
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set audio SOLO clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: divider
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Audio_SOLO_CLK(uint8_t enable, uint8_t div)
{
#ifndef BOOTROM
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0xFF));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_SOLO_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_AUDIO_SOLO_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_SOLO_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_SOLO_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);
#endif
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
#ifndef BOOTROM
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
#endif
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
#ifndef BOOTROM
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
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable or Disable Host config 0x6[3] to reset System
 *
 * @param  enable: Enable or disable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Config_SDIO_Host_Reset_System(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SDIO_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_SYS_RST_SD_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_SYS_RST_SD_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_SDIO_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable or Disable Host config 0x6[3] to reset SDU sdu_rst_ sd_rst_
 *
 * @param  enable: Enable or disable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Config_SDIO_Host_Reset_SDU(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SDIO_CFG0);
    if (enable) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_SDU_RST_SD_DIS);
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_SD_RST_SD_DIS);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_SDU_RST_SD_DIS);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_SD_RST_SD_DIS);
    }
    BL_WR_REG(GLB_BASE, GLB_SDIO_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable or Disable Host config 0x7[4] to interrupt CPU
 *
 * @param  enable: Enable or disable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Config_SDIO_Host_Interrupt_CPU(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SDIO_CFG0);
    if (enable) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_SDIO_INT_SYS_DIS);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_SDIO_INT_SYS_DIS);
    }
    BL_WR_REG(GLB_BASE, GLB_SDIO_CFG0, tmpVal);

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
 * @brief  swap SPI0 MOSI with MISO
 *
 * @param  newState: ENABLE or DISABLE
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
 * @param  swapIo3Io0: Select embedded flash swap io0 with io3
 * @param  swapIo2Cs: Select embedded flash swap cs with io2
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_Set_SFlash_IO_PARM(uint8_t selEmbedded, uint8_t swapIo3Io0, uint8_t swapIo2Cs)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    if (selEmbedded) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SEL_EMBEDDED_SFLASH);
        if (swapIo3Io0) {
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_3_IO_0);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_3_IO_0);
        }
        if (swapIo2Cs) {
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_2_CS);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_2_CS);
        }
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SEL_EMBEDDED_SFLASH);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_3_IO_0);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SWAP_SFLASH_IO_2_CS);
    }
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    if (selEmbedded) {
        GLB_Embedded_Flash_Pad_Enable(swapIo2Cs);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set sflash2 io parameter
 *
 * @param  swapIo3Io0: Select embedded flash swap io0 with io3
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_Set_SFlash2_IO_PARM(uint8_t swapIo3Io0)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    if (swapIo3Io0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SWAP_SFLASH2_IO_3_IO_0);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SWAP_SFLASH2_IO_3_IO_0);
    }
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  clear reset recorder
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Clr_Reset_Reason(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_RESET_STS0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CLR_TOP_RESET_RECORDER);
    BL_WR_REG(GLB_BASE, GLB_RESET_STS0, tmpVal);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_RESET_STS0);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CLR_TOP_RESET_RECORDER);
    BL_WR_REG(GLB_BASE, GLB_RESET_STS0, tmpVal);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_RESET_STS0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CLR_TOP_RESET_RECORDER);
    BL_WR_REG(GLB_BASE, GLB_RESET_STS0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get reset reason
 *
 * @param  reason: store reset reason
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Get_Reset_Reason(GLB_RESET_RECORD_Type *reason)
{
    uint32_t tmpVal;

    CHECK_PARAM((NULL != reason));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_RESET_STS0);
    reason->reset_recorder_ana_powb = (tmpVal >> 0) & 0x1;
    reason->reset_recorder_ext_rst_n = (tmpVal >> 1) & 0x1;
    reason->reset_recorder_pds_reset = (tmpVal >> 2) & 0x1;
    reason->reset_recorder_wdt_rst_n = (tmpVal >> 3) & 0x1;
    reason->reset_recorder_cpu_porst_n = (tmpVal >> 4) & 0x1;
    reason->reset_recorder_sys_reset_n = (tmpVal >> 5) & 0x1;
    reason->reset_recorder_cpu_sys_rstreq_n = (tmpVal >> 6) & 0x1;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  software reset
 *
 * @param  swrst: reset num
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_Type swrst)
{
    uint32_t tmpVal = 0;
    uint32_t bit = 0;
    uint32_t regAddr = 0;

    CHECK_PARAM(IS_GLB_AHB_MCU_SW_TYPE(swrst));

    if (swrst < 32) {
        bit = swrst;
        regAddr = GLB_BASE + GLB_SWRST_CFG0_OFFSET;
    } else if (swrst < 64) {
        bit = swrst - 32;
        regAddr = GLB_BASE + GLB_SWRST_CFG1_OFFSET;
    } else if (swrst < 96) {
        bit = swrst - 64;
        regAddr = GLB_BASE + GLB_SWRST_CFG2_OFFSET;
    }

    tmpVal = BL_RD_WORD(regAddr);
    tmpVal &= ~(1 << bit);
    BL_WR_WORD(regAddr, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_WORD(regAddr);
    tmpVal |= (1 << bit);
    BL_WR_WORD(regAddr, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_WORD(regAddr);
    tmpVal &= ~(1 << bit);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  dis reset
 *
 * @param  enable: ENABLE or DISABLE
 * @param  disrst: disrst macro
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Disrst_Set(uint8_t enable, GLB_DISRST_Type disrst)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DISRST_TYPE(disrst));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG3);
    if (enable) {
        tmpVal |= (1 << disrst);
    } else {
        tmpVal &= ~(1 << disrst);
    }
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get first 1 from u64, then clear it
 *
 * @param  val: target value
 * @param  bit: first 1 in bit
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
static BL_Err_Type GLB_Get_And_Clr_First_Set_From_U64(uint64_t *val, uint32_t *bit)
{
    if (!*val) {
        return ERROR;
    }

    for (uint8_t i = 0; i < 64; i++) {
        if ((*val) & ((uint64_t)1 << i)) {
            *bit = i;
            (*val) &= ~((uint64_t)1 << i);
            break;
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  hold IPs clock
 *
 * @param  ips: GLB_AHB_CLOCK_CPU | GLB_AHB_CLOCK_RSVD | ...... (not GLB_AHB_CLOCK_IP_xxx)
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_PER_Clock_Gate(uint64_t ips)
{
    /* api request from cjy */

    uint32_t tmpValCfg0 = 0;
    uint32_t tmpValCfg1 = 0;
    uint32_t tmpValCfg2 = 0;
    uint32_t bitfield = 0;

    tmpValCfg0 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG0);
    tmpValCfg1 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
    tmpValCfg2 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG2);
    while (ips) {
        if (SUCCESS == GLB_Get_And_Clr_First_Set_From_U64(&ips, &bitfield)) {
            switch (bitfield) {
                case GLB_AHB_CLOCK_IP_CPU:
                    tmpValCfg0 &= ~(1 << 0);
                    break;
                case GLB_AHB_CLOCK_IP_RSVD:
                    tmpValCfg0 &= ~(1 << 1);
                    break;
                case GLB_AHB_CLOCK_IP_SEC:
                    tmpValCfg0 &= ~(1 << 2);
                    tmpValCfg1 &= ~(1 << 3);
                    tmpValCfg1 &= ~(1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_0:
                    tmpValCfg0 &= ~(1 << 3);
                    tmpValCfg1 &= ~(1 << 12);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_1:
                    break;
                case GLB_AHB_CLOCK_IP_DMA_2:
                    break;
                case GLB_AHB_CLOCK_IP_CCI:
                    tmpValCfg0 &= ~(1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_RF_TOP:
                    break;
                case GLB_AHB_CLOCK_IP_GPIP:
                    tmpValCfg1 &= ~(1 << 2);
                    break;
                case GLB_AHB_CLOCK_IP_TZC:
                    tmpValCfg1 &= ~(1 << 5);
                    break;
                case GLB_AHB_CLOCK_IP_EF_CTRL:
                    tmpValCfg1 &= ~(1 << 7);
                    break;
                case GLB_AHB_CLOCK_IP_SF_CTRL:
                    tmpValCfg1 &= ~(1 << 11);
                    break;
                case GLB_AHB_CLOCK_IP_EMAC:
                    tmpValCfg2 &= ~(1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_UART0:
                    tmpValCfg1 &= ~(1 << 16);
                    break;
                case GLB_AHB_CLOCK_IP_UART1:
                    tmpValCfg1 &= ~(1 << 17);
                    break;
                case GLB_AHB_CLOCK_IP_UART2:
                    break;
                case GLB_AHB_CLOCK_IP_UART3:
                    break;
                case GLB_AHB_CLOCK_IP_UART4:
                    break;
                case GLB_AHB_CLOCK_IP_SPI:
                    tmpValCfg1 &= ~(1 << 18);
                    break;
                case GLB_AHB_CLOCK_IP_I2C:
                    tmpValCfg1 &= ~(1 << 19);
                    break;
                case GLB_AHB_CLOCK_IP_PWM:
                    tmpValCfg1 &= ~(1 << 20);
                    break;
                case GLB_AHB_CLOCK_IP_TIMER:
                    tmpValCfg1 &= ~(1 << 21);
                    break;
                case GLB_AHB_CLOCK_IP_IR:
                    tmpValCfg1 &= ~(1 << 22);
                    break;
                case GLB_AHB_CLOCK_IP_CHECKSUM:
                    tmpValCfg1 &= ~(1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_QDEC:
                    break;
                case GLB_AHB_CLOCK_IP_KYS:
                    break;
                case GLB_AHB_CLOCK_IP_I2S:
                    tmpValCfg1 &= ~(1 << 27);
                    break;
                case GLB_AHB_CLOCK_IP_USB11:
                    break;
                case GLB_AHB_CLOCK_IP_CAM:
                    break;
                case GLB_AHB_CLOCK_IP_MJPEG:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_NORMAL:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_LP:
                    break;
                case GLB_AHB_CLOCK_IP_ZB_NORMAL:
                    break;
                case GLB_AHB_CLOCK_IP_ZB_LP:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_NORMAL:
                    tmpValCfg2 &= ~(1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_LP:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_EMI_MISC:
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM0_CTRL:
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM1_CTRL:
                    tmpValCfg2 &= ~(1 << 18);
                    break;
                case GLB_AHB_CLOCK_IP_USB20_SDU:
                    tmpValCfg1 &= ~(1 << 13);
                    break;
                case GLB_AHB_CLOCK_IP_MIX2:
                    break;
                case GLB_AHB_CLOCK_IP_AUDIO:
                    tmpValCfg2 &= ~(1 << 21);
                    break;
                case GLB_AHB_CLOCK_IP_SDH:
                    tmpValCfg2 &= ~(1 << 22);
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_NORMAL:
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_I2C1:
                    tmpValCfg1 &= ~(1 << 25);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PHY:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_MAC_PHY:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PLATFORM:
                    break;
                case GLB_AHB_CLOCK_IP_LZ4:
                    break;
                case GLB_AHB_CLOCK_IP_AUPDM:
                    break;
                case GLB_AHB_CLOCK_IP_GAUGE:
                    break;
                case GLB_AHB_CLOCK_IP_DBI:
                    tmpValCfg1 &= ~(1 << 24);
                    break;
                case GLB_AHB_CLOCK_IP_PEC:
                    tmpValCfg2 &= ~(1 << 25);
                    break;
                case GLB_AHB_CLOCK_IP_ISO11898:
                    tmpValCfg1 &= ~(1 << 26);
                    break;
                case GLB_AHB_CLOCK_IP_AUSOLO_TOP:
                    tmpValCfg1 &= ~(1 << 28);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_GPIO:
                    tmpValCfg1 &= ~(1 << 0);
                    break;
                case GLB_AHB_CLOCK_IP_MM_MISC:
                    tmpValCfg2 &= ~(1 << 16);
                    break;
                default:
                    break;
            }
        }
    }
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG0, tmpValCfg0);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpValCfg1);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG2, tmpValCfg2);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  release IPs clock
 *
 * @param  ips: GLB_AHB_CLOCK_CPU | GLB_AHB_CLOCK_RSVD | ...... (not GLB_AHB_CLOCK_IP_xxx)
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_PER_Clock_UnGate(uint64_t ips)
{
    /* api request from cjy */

    uint32_t tmpValCfg0 = 0;
    uint32_t tmpValCfg1 = 0;
    uint32_t tmpValCfg2 = 0;
    uint32_t bitfield = 0;

    tmpValCfg0 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG0);
    tmpValCfg1 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
    tmpValCfg2 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG2);
    while (ips) {
        if (SUCCESS == GLB_Get_And_Clr_First_Set_From_U64(&ips, &bitfield)) {
            switch (bitfield) {
                case GLB_AHB_CLOCK_IP_CPU:
                    tmpValCfg0 |= (1 << 0);
                    break;
                case GLB_AHB_CLOCK_IP_RSVD:
                    tmpValCfg0 |= (1 << 1);
                    break;
                case GLB_AHB_CLOCK_IP_SEC:
                    tmpValCfg0 |= (1 << 2);
                    tmpValCfg1 |= (1 << 3);
                    tmpValCfg1 |= (1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_0:
                    tmpValCfg0 |= (1 << 3);
                    tmpValCfg1 |= (1 << 12);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_1:
                    break;
                case GLB_AHB_CLOCK_IP_DMA_2:
                    break;
                case GLB_AHB_CLOCK_IP_CCI:
                    tmpValCfg0 |= (1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_RF_TOP:
                    break;
                case GLB_AHB_CLOCK_IP_GPIP:
                    tmpValCfg1 |= (1 << 2);
                    break;
                case GLB_AHB_CLOCK_IP_TZC:
                    tmpValCfg1 |= (1 << 5);
                    break;
                case GLB_AHB_CLOCK_IP_EF_CTRL:
                    tmpValCfg1 |= (1 << 7);
                    break;
                case GLB_AHB_CLOCK_IP_SF_CTRL:
                    tmpValCfg1 |= (1 << 11);
                    break;
                case GLB_AHB_CLOCK_IP_EMAC:
                    tmpValCfg2 |= (1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_UART0:
                    tmpValCfg1 |= (1 << 16);
                    break;
                case GLB_AHB_CLOCK_IP_UART1:
                    tmpValCfg1 |= (1 << 17);
                    break;
                case GLB_AHB_CLOCK_IP_UART2:
                    break;
                case GLB_AHB_CLOCK_IP_UART3:
                    break;
                case GLB_AHB_CLOCK_IP_UART4:
                    break;
                case GLB_AHB_CLOCK_IP_SPI:
                    tmpValCfg1 |= (1 << 18);
                    break;
                case GLB_AHB_CLOCK_IP_I2C:
                    tmpValCfg1 |= (1 << 19);
                    break;
                case GLB_AHB_CLOCK_IP_PWM:
                    tmpValCfg1 |= (1 << 20);
                    break;
                case GLB_AHB_CLOCK_IP_TIMER:
                    tmpValCfg1 |= (1 << 21);
                    break;
                case GLB_AHB_CLOCK_IP_IR:
                    tmpValCfg1 |= (1 << 22);
                    break;
                case GLB_AHB_CLOCK_IP_CHECKSUM:
                    tmpValCfg1 |= (1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_QDEC:
                    break;
                case GLB_AHB_CLOCK_IP_KYS:
                    break;
                case GLB_AHB_CLOCK_IP_I2S:
                    tmpValCfg1 |= (1 << 27);
                    break;
                case GLB_AHB_CLOCK_IP_USB11:
                    break;
                case GLB_AHB_CLOCK_IP_CAM:
                    break;
                case GLB_AHB_CLOCK_IP_MJPEG:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_NORMAL:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_LP:
                    break;
                case GLB_AHB_CLOCK_IP_ZB_NORMAL:
                    break;
                case GLB_AHB_CLOCK_IP_ZB_LP:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_NORMAL:
                    tmpValCfg2 |= (1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_LP:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_EMI_MISC:
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM0_CTRL:
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM1_CTRL:
                    tmpValCfg2 |= (1 << 18);
                    break;
                case GLB_AHB_CLOCK_IP_USB20_SDU:
                    tmpValCfg1 |= (1 << 13);
                    break;
                case GLB_AHB_CLOCK_IP_MIX2:
                    break;
                case GLB_AHB_CLOCK_IP_AUDIO:
                    tmpValCfg2 |= (1 << 21);
                    break;
                case GLB_AHB_CLOCK_IP_SDH:
                    tmpValCfg2 |= (1 << 22);
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_NORMAL:
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_I2C1:
                    tmpValCfg1 |= (1 << 25);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PHY:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_MAC_PHY:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PLATFORM:
                    break;
                case GLB_AHB_CLOCK_IP_LZ4:
                    break;
                case GLB_AHB_CLOCK_IP_AUPDM:
                    break;
                case GLB_AHB_CLOCK_IP_GAUGE:
                    break;
                case GLB_AHB_CLOCK_IP_DBI:
                    tmpValCfg1 |= (1 << 24);
                    break;
                case GLB_AHB_CLOCK_IP_PEC:
                    tmpValCfg2 |= (1 << 25);
                    break;
                case GLB_AHB_CLOCK_IP_ISO11898:
                    tmpValCfg1 |= (1 << 26);
                    break;
                case GLB_AHB_CLOCK_IP_AUSOLO_TOP:
                    tmpValCfg1 |= (1 << 28);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_GPIO:
                    tmpValCfg1 |= (1 << 0);
                    break;
                case GLB_AHB_CLOCK_IP_MM_MISC:
                    tmpValCfg2 |= (1 << 16);
                    break;
                default:
                    break;
            }
        }
    }
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG0, tmpValCfg0);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpValCfg1);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG2, tmpValCfg2);

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

    /* Swicth MCU clock to RC32M, no divider */
    HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    GLB_Set_MCU_System_CLK_Div(0, 0);

    /* reset M0/SYS(bus) */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_SYS_RESET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
    BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
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

#if defined(DUAL_CORE)
    GLB_CORE_ID_Type core = GLB_CORE_ID_INVALID;
    /* Do reset */
    core = GLB_Get_Core_Type();
    switch (core) {
        case GLB_CORE_ID_M0:
#endif
            /* Swicth MCU clock to RC32M, no divider */
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            GLB_Set_MCU_System_CLK_Div(0, 0);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
#if defined(DUAL_CORE)
            break;
        default:
            break;
    }
#endif

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

    /* Swicth MCU clock to RC32M, no divider */
    HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    GLB_Set_MCU_System_CLK_Div(0, 0);

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
BL_Err_Type ATTR_TCM_SECTION GLB_Set_Flash_Id_Value(uint32_t idValue)
{
    BL_WR_REG(GLB_BASE, GLB_HW_RSV1, (idValue | BFLB_FLASH_ID_VALID_FLAG));

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
uint32_t ATTR_TCM_SECTION GLB_Get_Flash_Id_Value(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_HW_RSV1);
    if ((tmpVal & BFLB_FLASH_ID_VALID_FLAG) != 0) {
        return (tmpVal & BFLB_FLASH_ID_VALID_MASK);
    }

    return 0x00000000;
}

/****************************************************************************/ /**
 * @brief  trim LDO18IO vout sel
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_Trim_Ldo18ioVoutSel(void)
{
    Efuse_Ana_Ldo18ioVoutSel_Type trim;
    int32_t tmpVal = 0;

    EF_Ctrl_Read_Ldo18ioVoutSel_Trim(&trim);
    if (trim.ldo18ioVoutSelEn) {
        if (trim.ldo18ioVoutSelParity == EF_Ctrl_Get_Trim_Parity(trim.ldo18ioVoutSelAon, 4)) {
            tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO18IO);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO18IO_VOUT_SEL, trim.ldo18ioVoutSelAon);
            BL_WR_REG(GLB_BASE, GLB_LDO18IO, tmpVal);
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  trim LDO18IO bypass
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_Trim_Ldo18ioBypass(void)
{
    Efuse_Ana_Ldo18ioBypass_Type trim;
    int32_t tmpVal = 0;

    EF_Ctrl_Read_Ldo18ioBypass_Trim(&trim);
    if (trim.ldo18ioBypassEn) {
        if (trim.ldo18ioBypassParity == EF_Ctrl_Get_Trim_Parity(trim.ldo18ioBypassAon, 1)) {
            tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO18IO);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO18IO_BYPASS, trim.ldo18ioBypassAon);
            BL_WR_REG(GLB_BASE, GLB_LDO18IO, tmpVal);
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  trim LDO18IO vout
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_Trim_Ldo18ioVoutTrim(void)
{
    Efuse_Ana_Ldo18ioVoutTrim_Type trim;
    int32_t tmpVal = 0;

    EF_Ctrl_Read_Ldo18ioVoutTrim_Trim(&trim);
    if (trim.ldo18ioVoutTrimEn) {
        if (trim.ldo18ioVoutTrimParity == EF_Ctrl_Get_Trim_Parity(trim.ldo18ioVoutTrimAon, 4)) {
            tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO18IO);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO18IO_VOUT_TRIM, trim.ldo18ioVoutTrimAon);
            BL_WR_REG(GLB_BASE, GLB_LDO18IO, tmpVal);
            return SUCCESS;
        }
    }

    return ERROR;
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
        case GLB_WRAM128KB_EM32KB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x03);
            break;
        case GLB_WRAM96KB_EM64KB:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x0F);
            break;
        default:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x03);
            break;
    }
    BL_WR_REG(GLB_BASE, GLB_SRAM_CFG3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set PSRAMB clock
 *
 * @param  enable: Enable or disable
 * @param  clkSel: PSRAMB clock type
 * @param  div: clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_PSRAMB_CLK_Sel(uint8_t enable, GLB_PSRAMB_PLL_Type clkSel, uint8_t div)
{
#ifndef BOOTROM
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PSRAMB_PLL_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PSRAM_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_PSRAMB_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_PSRAM_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PSRAM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PSRAMB_CLK_SEL, clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PSRAMB_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_PSRAM_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PSRAM_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_PSRAMB_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_PSRAMB_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_PSRAM_CFG0, tmpVal);
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set PSRAMB clock
 *
 * @param  slave: slave IP
 * @param  enable: enable or disable clock
 * @param  clkSel: clock selection
 * @param  div: clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_Slave_Grp_0_CLK(GLB_SLAVE_GRP_0_Type slave, uint8_t enable, GLB_SLAVE_GRP_0_CLK_SEL_Type clkSel, uint32_t div)
{
    uint32_t tmpVal;
    uint32_t regAddr = GLB_BASE + glb_slave_grp_0_table[slave].clkOffSetAddr;
    uint8_t enPos = glb_slave_grp_0_table[slave].clkEnPos;
    uint8_t selPos = glb_slave_grp_0_table[slave].clkSelPos;
    uint8_t divPos = glb_slave_grp_0_table[slave].clkDivPos;
    uint8_t enLen = glb_slave_grp_0_table[slave].clkEnLen;
    uint8_t selLen = glb_slave_grp_0_table[slave].clkSelLen;
    uint8_t divLen = glb_slave_grp_0_table[slave].clkDivLen;

    CHECK_PARAM(IS_GLB_SLAVE_GRP_0_TYPE(slave));

    /* disable clock first */
    if (enLen) {
        tmpVal = BL_RD_BYTE(regAddr);
        tmpVal &= ~(((1ULL << enLen) - 1) << enPos);
        BL_WR_BYTE(regAddr, tmpVal);
    }

    /* set clock sel or div */
    tmpVal = BL_RD_BYTE(regAddr);
    if (selLen) {
        tmpVal &= ~(((1ULL << selLen) - 1) << selPos);
        tmpVal |= (((clkSel.clkSel) & ((1 << selLen) - 1)) << selPos);
    }
    if (divLen) {
        tmpVal &= ~(((1ULL << divLen) - 1) << divPos);
        tmpVal |= ((div & ((1 << divLen) - 1)) << divPos);
    }
    BL_WR_BYTE(regAddr, tmpVal);

    /* enable clock */
    if (enLen && enable) {
        tmpVal = BL_RD_BYTE(regAddr);
        tmpVal |= (((1ULL << enLen) - 1) << enPos);
        BL_WR_BYTE(regAddr, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure WIFIPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_WIFI_PLL(GLB_XTAL_Type xtalType, const GLB_WA_PLL_Cfg_Type *pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;

    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }

    GLB_Power_Off_WIFIPLL();
    GLB_WIFIPLL_Ref_Clk_Sel(refClk);
    GLB_Power_On_WIFIPLL(&(pllCfgList[xtalType]), 1);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure AUPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL(GLB_XTAL_Type xtalType, const GLB_WA_PLL_Cfg_Type *pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;

    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }

    GLB_Power_Off_AUPLL();
    GLB_AUPLL_Ref_Clk_Sel(refClk);
    GLB_Power_On_AUPLL(&(pllCfgList[xtalType]), 1);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 384M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_384M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType = GLB_XTAL_NONE;

    /* we take 384M for CPU use,so set LDO to 1.2V*/
    HBN_Set_Ldo11_All_Vout(HBN_LDO_LEVEL_1P20V);
    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((GLB_XTAL_Type)xtalType, audioPllCfg_384M);
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 400M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_400M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType = GLB_XTAL_NONE;

    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((GLB_XTAL_Type)xtalType, audioPllCfg_400M);
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 451P58M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_451P58M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType = GLB_XTAL_NONE;

    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((GLB_XTAL_Type)xtalType, audioPllCfg_451P58M);
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 491P52M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_491P52M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType = GLB_XTAL_NONE;

    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((GLB_XTAL_Type)xtalType, audioPllCfg_491P52M);
}

/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL616_Peripheral_Driver */
