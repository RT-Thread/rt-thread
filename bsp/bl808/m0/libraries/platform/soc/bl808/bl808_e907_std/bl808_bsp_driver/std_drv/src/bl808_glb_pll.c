/**
  ******************************************************************************
  * @file    bl808_glb_pll.c
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

/*@} end of group GLB_Private_Types */

/** @defgroup  GLB_Private_Variables
 *  @{
 */



/* WiFi PLL Config*/
const GLB_WAC_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_32M_38P4M_40M = {
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
const GLB_WAC_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_24M = {
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
const GLB_WAC_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_26M = {
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
const GLB_WAC_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION wifiPllCfg_960M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                                 /*!< XTAL is None */
    { &wifiPllBasicCfg_24M, 0x1400000 },           /*!< XTAL is 24M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1E00000 }, /*!< XTAL is 32M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1900000 }, /*!< XTAL is 38.4M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1800000 }, /*!< XTAL is 40M */
    { &wifiPllBasicCfg_26M, 0x1276276 },           /*!< XTAL is 26M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1E00000 }, /*!< XTAL is RC32M */
};

/* Audio PLL Config*/
const GLB_WAC_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPllBasicCfg_24M_26M = {
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
const GLB_WAC_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPllBasicCfg_32M_38P4M_40M = {
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
const GLB_WAC_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_442P368M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                                /*!< XTAL is None */
    { &audioPllBasicCfg_24M_26M, 0x126E9 },       /*!< XTAL is 24M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1BA5E }, /*!< XTAL is 32M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x170A3 }, /*!< XTAL is 38.4M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x161E5 }, /*!< XTAL is 40M */
    { &audioPllBasicCfg_24M_26M, 0x1103A },       /*!< XTAL is 26M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1BA5E }, /*!< XTAL is RC32M */
};
const GLB_WAC_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_451P584M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                                /*!< XTAL is None */
    { &audioPllBasicCfg_24M_26M, 0x12D0E },       /*!< XTAL is 24M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1C395 }, /*!< XTAL is 32M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x17851 }, /*!< XTAL is 38.4M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x16944 }, /*!< XTAL is 40M */
    { &audioPllBasicCfg_24M_26M, 0x115E5 },       /*!< XTAL is 26M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1C395 }, /*!< XTAL is RC32M */
};

/* CPU PLL Config*/
const GLB_WAC_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION cpuPllBasicCfg_24M_26M = {
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
const GLB_WAC_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION cpuPllBasicCfg_32M_38P4M_40M = {
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
const GLB_WAC_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION cpuPllCfg_380M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                              /*!< XTAL is None */
    { &cpuPllBasicCfg_24M_26M, 0xFD55 },        /*!< XTAL is 24M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x17C00 }, /*!< XTAL is 32M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x13CAA }, /*!< XTAL is 38.4M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x13000 }, /*!< XTAL is 40M */
    { &cpuPllBasicCfg_24M_26M, 0xE9D8 },        /*!< XTAL is 26M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x17C00 }, /*!< XTAL is RC32M */
};
const GLB_WAC_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION cpuPllCfg_400M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                              /*!< XTAL is None */
    { &cpuPllBasicCfg_24M_26M, 0x10AAA },       /*!< XTAL is 24M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x19000 }, /*!< XTAL is 32M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x14D55 }, /*!< XTAL is 38.4M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x14000 }, /*!< XTAL is 40M */
    { &cpuPllBasicCfg_24M_26M, 0xF627 },        /*!< XTAL is 26M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x19000 }, /*!< XTAL is RC32M */
};
const GLB_WAC_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION cpuPllCfg_480M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                              /*!< XTAL is None */
    { &cpuPllBasicCfg_24M_26M, 0x14000 },       /*!< XTAL is 24M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x1E000 }, /*!< XTAL is 32M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x19000 }, /*!< XTAL is 38.4M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x18000 }, /*!< XTAL is 40M */
    { &cpuPllBasicCfg_24M_26M, 0x12762 },       /*!< XTAL is 26M */
    { &cpuPllBasicCfg_32M_38P4M_40M, 0x1E000 }, /*!< XTAL is RC32M */
};

/* MIPI PLL Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_24M = {
    .clkpllRefdivRatio = 1,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_32M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_40M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_26M = {
    .clkpllRefdivRatio = 1,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION mipiPllCfg_1500M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                       /*!< XTAL is None */
    { &mipiPllBasicCfg_24M, 0x1F400 },   /*!< XTAL is 24M */
    { &mipiPllBasicCfg_32M, 0x2EE00 },   /*!< XTAL is 32M */
    { &mipiPllBasicCfg_38P4M, 0x27100 }, /*!< XTAL is 38.4M */
    { &mipiPllBasicCfg_40M, 0x25800 },   /*!< XTAL is 40M */
    { &mipiPllBasicCfg_26M, 0x1CD89 },   /*!< XTAL is 26M */
    { &mipiPllBasicCfg_32M, 0x2EE00 },   /*!< XTAL is RC32M */
};

/* uhs PLL 2100 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_2100M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll2100BasicCfg_24M, 0x2BC00 },   /*!< XTAL is 24M */
    { &uhsPll2100BasicCfg_32M, 0x41A00 },   /*!< XTAL is 32M */
    { &uhsPll2100BasicCfg_38P4M, 0x36B00 }, /*!< XTAL is 38.4M */
    { &uhsPll2100BasicCfg_40M, 0x34800 },   /*!< XTAL is 40M */
    { &uhsPll2100BasicCfg_26M, 0x28627 },   /*!< XTAL is 26M */
    { &uhsPll2100BasicCfg_32M, 0x41A00 },   /*!< XTAL is RC32M */
};

/* uhs PLL 1400 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_1400M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll1400MCfg_24M, 0x1D2AA },   /*!< XTAL is 24M */
    { &uhsPll1400MCfg_32M, 0x2BC00 },   /*!< XTAL is 32M */
    { &uhsPll1400MCfg_38P4M, 0x24755 }, /*!< XTAL is 38.4M */
    { &uhsPll1400MCfg_40M, 0x23000 },   /*!< XTAL is 40M */
    { &uhsPll1400MCfg_26M, 0x1AEC4 },   /*!< XTAL is 26M */
    { &uhsPll1400MCfg_32M, 0x2BC00 },   /*!< XTAL is RC32M */
};

/* uhs PLL 1500 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_1500M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll1500MCfg_24M, 0x1F400 },   /*!< XTAL is 24M */
    { &uhsPll1500MCfg_32M, 0x2EE00 },   /*!< XTAL is 32M */
    { &uhsPll1500MCfg_38P4M, 0x27100 }, /*!< XTAL is 38.4M */
    { &uhsPll1500MCfg_40M, 0x25800 },   /*!< XTAL is 40M */
    { &uhsPll1500MCfg_26M, 0x1CD89 },   /*!< XTAL is 26M */
    { &uhsPll1500MCfg_32M, 0x2EE00 },   /*!< XTAL is RC32M */
};

/* uhs PLL 1600 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1600BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1600/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1600BasicCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1600/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1600BasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1600/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1600BasicCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1600/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1600BasicCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1600/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_1600M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll1600BasicCfg_24M, 0x21555 },   /*!< XTAL is 24M */
    { &uhsPll1600BasicCfg_32M, 0x32000 },   /*!< XTAL is 32M */
    { &uhsPll1600BasicCfg_38P4M, 0x29AAA }, /*!< XTAL is 38.4M */
    { &uhsPll1600BasicCfg_40M, 0x28000 },   /*!< XTAL is 40M */
    { &uhsPll1600BasicCfg_26M, 0x1EC4E },   /*!< XTAL is 26M */
    { &uhsPll1600BasicCfg_32M, 0x32000 },   /*!< XTAL is RC32M */
};

/* uhs PLL 400 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 0,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 0,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 0,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 0,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 0,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_400M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll400BasicCfg_24M, 0x8555  },    /*!< XTAL is 24M */
    { &uhsPll400BasicCfg_32M, 0xC800  },    /*!< XTAL is 32M */
    { &uhsPll400BasicCfg_38P4M, 0xA6AA  },  /*!< XTAL is 38.4M */
    { &uhsPll400BasicCfg_40M, 0xA000  },    /*!< XTAL is 40M */
    { &uhsPll400BasicCfg_26M, 0x7B13  },    /*!< XTAL is 26M */
    { &uhsPll400BasicCfg_32M, 0xC800  },    /*!< XTAL is RC32M */
};

/* uhs PLL 667 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 0,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 0,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_667M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll667BasicCfg_24M, 0xDE55  },    /*!< XTAL is 24M */
    { &uhsPll667BasicCfg_32M, 0x14D80 },    /*!< XTAL is 32M */
    { &uhsPll667BasicCfg_38P4M, 0x115EA },  /*!< XTAL is 38.4M */
    { &uhsPll667BasicCfg_40M, 0x10ACC },    /*!< XTAL is 40M */
    { &uhsPll667BasicCfg_26M, 0xCD3B  },    /*!< XTAL is 26M */
    { &uhsPll667BasicCfg_32M, 0x14D80 },    /*!< XTAL is RC32M */
};

/* uhs PLL 800 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 0,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_800M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll800BasicCfg_24M, 0x10AAA },    /*!< XTAL is 24M */
    { &uhsPll800BasicCfg_32M, 0x19000 },    /*!< XTAL is 32M */
    { &uhsPll800BasicCfg_38P4M, 0x14D55 },  /*!< XTAL is 38.4M */
    { &uhsPll800BasicCfg_40M, 0x14000 },    /*!< XTAL is 40M */
    { &uhsPll800BasicCfg_26M, 0xF627  },    /*!< XTAL is 26M */
    { &uhsPll800BasicCfg_32M, 0x19000 },    /*!< XTAL is RC32M */
};

/* uhs PLL 1066 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_1066M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll1066BasicCfg_24M, 0x16355 },   /*!< XTAL is 24M */
    { &uhsPll1066BasicCfg_32M, 0x21500 },   /*!< XTAL is 32M */
    { &uhsPll1066BasicCfg_38P4M, 0x1BC2A }, /*!< XTAL is 38.4M */
    { &uhsPll1066BasicCfg_40M, 0x1AA66 },   /*!< XTAL is 40M */
    { &uhsPll1066BasicCfg_26M, 0x14800 },   /*!< XTAL is 26M */
    { &uhsPll1066BasicCfg_32M, 0x21500 },   /*!< XTAL is RC32M */
};

/* uhs PLL 2000 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2000BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2000/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2000BasicCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2000/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2000BasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2000/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2000BasicCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2000/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2000BasicCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2000/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_2000M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll2000BasicCfg_24M, 0x29AAA },   /*!< XTAL is 24M */
    { &uhsPll2000BasicCfg_32M, 0x3E800 },   /*!< XTAL is 32M */
    { &uhsPll2000BasicCfg_38P4M, 0x34155 }, /*!< XTAL is 38.4M */
    { &uhsPll2000BasicCfg_40M, 0x32000 },   /*!< XTAL is 40M */
    { &uhsPll2000BasicCfg_26M, 0x26762 },   /*!< XTAL is 26M */
    { &uhsPll2000BasicCfg_32M, 0x3E800 },   /*!< XTAL is RC32M */
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
 * @brief  set dsp muxpll 320M selection
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_Muxpll_320M_Sel(GLB_DSP_MUXPLL_320M_CLK_SEL_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_DSP_MUXPLL_320M_CLK_SEL_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_MM_MUXPLL_320M_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get dsp muxpll 320M selection
 *
 * @param  None
 *
 * @return dsp 320M mux select value
 *
*******************************************************************************/
GLB_DSP_MUXPLL_320M_CLK_SEL_Type ATTR_CLOCK_SECTION GLB_Get_DSP_Muxpll_320M_Sel(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    return (GLB_DSP_MUXPLL_320M_CLK_SEL_Type)(BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_MM_MUXPLL_320M_SEL));
}

/****************************************************************************/ /**
 * @brief  set dsp muxpll 240M selection
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_Muxpll_240M_Sel(GLB_DSP_MUXPLL_240M_CLK_SEL_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_DSP_MUXPLL_240M_CLK_SEL_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_MM_MUXPLL_240M_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get dsp muxpll 240M selection
 *
 * @param  None
 *
 * @return dsp 240M mux select value
 *
*******************************************************************************/
GLB_DSP_MUXPLL_240M_CLK_SEL_Type ATTR_CLOCK_SECTION GLB_Get_DSP_Muxpll_240M_Sel(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    return (GLB_DSP_MUXPLL_240M_CLK_SEL_Type)(BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_MM_MUXPLL_240M_SEL));
}

/****************************************************************************/ /**
 * @brief  set dsp muxpll 160M selection
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_Muxpll_160M_Sel(GLB_DSP_MUXPLL_160M_CLK_SEL_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_DSP_MUXPLL_160M_CLK_SEL_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_MM_MUXPLL_160M_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get dsp muxpll 160M selection
 *
 * @param  None
 *
 * @return dsp 160M mux select value
 *
*******************************************************************************/
GLB_DSP_MUXPLL_160M_CLK_SEL_Type ATTR_CLOCK_SECTION GLB_Get_DSP_Muxpll_160M_Sel(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG1);
    return (GLB_DSP_MUXPLL_160M_CLK_SEL_Type)(BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_MM_MUXPLL_160M_SEL));
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
    GLB_CORE_ID_Type coreType;
    HBN_MCU_XCLK_Type mcuXclkSel;
    HBN_MCU_ROOT_CLK_Type mcuRootClkSel;
    GLB_DSP_XCLK_Type dspXclkSel;
    GLB_DSP_ROOT_CLK_Type dspRootClkSel;
    volatile GLB_PLL_REF_CLK_Type refClk;

    CHECK_PARAM(IS_GLB_XTAL_TYPE(xtalType));
    CHECK_PARAM((pllType < (GLB_PLL_UHSPLL * 2)));

    if (xtalType == GLB_XTAL_NONE) {
        return ERROR;
    }

    if (xtalType != GLB_XTAL_RC32M) {
        /* power on xtal first */
        AON_Power_On_XTAL();
    }

    coreType = GLB_Get_Core_Type();
    if ((GLB_CORE_ID_D0 == coreType)) {
        /* D0 */
        /* Before config XTAL and PLL ,make sure root clk is from RC32M */
        dspXclkSel = GLB_Get_DSP_XCLK_Sel();
        dspRootClkSel = GLB_Get_DSP_ROOT_CLK_Sel();
        if ((dspXclkSel != GLB_DSP_XCLK_RC32M) || (dspRootClkSel != GLB_DSP_ROOT_CLK_XCLK)) {
            GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_RC32M);
            GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_XCLK);
        }
        GLB_Set_DSP_System_CLK_Div(0, 0);
    } else {
        /* M0 or LP or invalid(use M0 instead) */
        /* Before config XTAL and PLL ,make sure root clk is from RC32M */
        mcuXclkSel = HBN_Get_MCU_XCLK_Sel();
        mcuRootClkSel = HBN_Get_MCU_Root_CLK_Sel();
        if ((mcuXclkSel != HBN_MCU_XCLK_RC32M) || (mcuRootClkSel != HBN_MCU_ROOT_CLK_XCLK)) {
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
        }
        GLB_Set_MCU_System_CLK_Div(0, 0, 0);
    }

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
        GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_WIFIPLL);
        GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_WIFIPLL, refClk);
        GLB_Power_On_WAC_PLL(GLB_WAC_PLL_WIFIPLL, &wifiPllCfg_960M[xtalType], 0);
    }

    /* power on aupll */
    if (pllType & GLB_PLL_AUPLL) {
        GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_AUPLL);
        GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_AUPLL, refClk);
        GLB_Power_On_WAC_PLL(GLB_WAC_PLL_AUPLL, &audioPllCfg_442P368M[xtalType], 0);
    }

    /* power on cpupll */
    if (pllType & GLB_PLL_CPUPLL) {
        GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_CPUPLL);
        GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_CPUPLL, refClk);
        GLB_Power_On_WAC_PLL(GLB_WAC_PLL_CPUPLL, &cpuPllCfg_380M[xtalType], 0);
    }

    /* power on mipipll */
    if (pllType & GLB_PLL_MIPIPLL) {
        GLB_Power_Off_MU_PLL(GLB_MU_PLL_MIPIPLL);
        GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_MIPIPLL, refClk);
        GLB_Power_On_MU_PLL(GLB_MU_PLL_MIPIPLL, &mipiPllCfg_1500M[xtalType], 0);
    }

    /* power on uhspll */
    if (pllType & GLB_PLL_UHSPLL) {
        GLB_Power_Off_MU_PLL(GLB_MU_PLL_UHSPLL);
        GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_UHSPLL, refClk);
        GLB_Power_On_MU_PLL(GLB_MU_PLL_UHSPLL, &uhsPllCfg_2100M[xtalType], 0);
    }

    arch_delay_us(75);

    if (xtalType != GLB_XTAL_RC32M) {
        /* if power on xtal, always set xclk from xtal */
        HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_XTAL);
        GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_XTAL);
    }

    /* enable all PLL clock output */
    /* GLB reg_pll_en = 1, cannot be zero */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_PLL_EN);
    BL_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);
    /* MM_GLB reg_pll_en = 1, cannot be zero */
    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_PLL_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power off wifi audio cpu PLL
 *
 * @param  pllType: PLL XTAL type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_Type pllType)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));

    switch (pllType) {
        case GLB_WAC_PLL_WIFIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_AUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_CPUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_CPU_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
    }

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
 * @brief  GLB wifi audio cpu PLL ref clock select
 *
 * @param  pllType: PLL XTAL type
 * @param  refClk: PLL ref clock select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_Type pllType, GLB_PLL_REF_CLK_Type refClk)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));
    CHECK_PARAM(IS_GLB_PLL_REF_CLK_TYPE(refClk));

    switch (pllType) {
        case GLB_WAC_PLL_WIFIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_AUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_CPUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_CPU_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
    }

    /* xxxpll_refclk_sel */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    if ((GLB_WAC_PLL_WIFIPLL == pllType) && (GLB_PLL_REFCLK_XTAL == refClk)) {
        /* wifipll_refclk_sel different from other's pll, 1 means xtal */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFCLK_SEL, 1);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFCLK_SEL, refClk);
    }
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power on PLL
 *
 * @param  pllType: PLL XTAL type
 * @param  cfg: GLB PLL configuration
 * @param  waitStable: wait PLL clock stable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_On_WAC_PLL(GLB_WAC_PLL_Type pllType, const GLB_WAC_PLL_Cfg_Type *const cfg, uint8_t waitStable)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    /* unknown */
    CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));

    switch (pllType) {
        case GLB_WAC_PLL_WIFIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_AUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_CPUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_CPU_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
    }

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
    if (GLB_WAC_PLL_WIFIPLL == pllType) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_CTRL_HW, cfg->basicCfg->clkpllSdmCtrlHw);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_BYPASS, cfg->basicCfg->clkpllSdmBypass);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDMIN, cfg->clkpllSdmin);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_BYPASS, cfg->basicCfg->clkpllSdmBypass);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDMIN, cfg->clkpllSdmin);
    }
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 6, tmpVal);

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

    /* aupll : cfg1, aupll_postdiv = 0x12 or 0x14 */
    if (GLB_WAC_PLL_AUPLL == pllType) {
        tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
        if ((cfg->clkpllSdmin==0x12D0E)||(cfg->clkpllSdmin==0x1C395)||(cfg->clkpllSdmin==0x17851)||(cfg->clkpllSdmin==0x16944)||(cfg->clkpllSdmin==0x115E5)) {
            /* 451.548 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_POSTDIV, 0x14);
        } else {
            /* 442.368 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_POSTDIV, 0x12);
        }
        BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);
    }

    /* Step4:enable output clock */
    /* wifipll : cfg5, wifipll_vco_div3_en=1 */
    if (GLB_WAC_PLL_WIFIPLL == pllType) {
        tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 5);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_VCO_DIV3_EN);
        BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 5, tmpVal);
    }
    /* cfg8 : wifipll->wifipll_en_ctrl_hw=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 8);
    if (GLB_WAC_PLL_WIFIPLL == pllType) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_EN_CTRL_HW, 1);
    }
    /* cfg8 : wifipll/aupll/cpupll clock enable */
    switch (pllType) {
        case GLB_WAC_PLL_WIFIPLL:
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV4);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV5);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV6);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV8);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV10);
            break;
        case GLB_WAC_PLL_AUPLL:
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV1);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV2);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV2P5);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV5);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV6);
            break;
        case GLB_WAC_PLL_CPUPLL:
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV1);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV2);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV2P5);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV4);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV5);
            break;
        default:
            break;
    }
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
 * @brief  GLB power off mipi uhs PLL
 *
 * @param  pllType: PLL XTAL type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_Off_MU_PLL(GLB_MU_PLL_Type pllType)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_Power_Off_MU_TYPE(pllType));

    switch (pllType) {
        case GLB_MU_PLL_MIPIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
        case GLB_MU_PLL_UHSPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_UHS_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
    }

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
 * @brief  GLB mipi uhs PLL ref clock select
 *
 * @param  pllType: PLL XTAL type
 * @param  refClk: PLL ref clock select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_Type pllType, GLB_PLL_REF_CLK_Type refClk)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));
    CHECK_PARAM(IS_GLB_PLL_REF_CLK_TYPE(refClk));

    switch (pllType) {
        case GLB_MU_PLL_MIPIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
        case GLB_MU_PLL_UHSPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_UHS_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
    }

    /* xxxpll_refclk_sel */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFCLK_SEL, refClk);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power on PLL
 *
 * @param  pllType: PLL XTAL type
 * @param  cfg: GLB PLL configuration
 * @param  waitStable: wait PLL stable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_On_MU_PLL(GLB_MU_PLL_Type pllType, const GLB_MU_PLL_Cfg_Type *const cfg, uint8_t waitStable)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    /* unknown */
    CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));

    switch (pllType) {
        case GLB_MU_PLL_MIPIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
        case GLB_MU_PLL_UHSPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_UHS_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
    }

    /* Step1:config parameter */
    /* cfg1:Set aupll_refclk_sel and aupll_refdiv_ratio */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFDIV_RATIO, cfg->basicCfg->clkpllRefdivRatio);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    /* cfg4:Set aupll_sel_sample_clk */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SEL_SAMPLE_CLK, cfg->basicCfg->clkpllSelSampleClk);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 4, tmpVal);

    /* cfg5:Set aupll_vco_speed */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_VCO_SPEED, cfg->basicCfg->clkpllVcoSpeed);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 5, tmpVal);

    /* cfg1: uhspll_even_div_en and uhspll_even_div_ratio */
    if (GLB_MU_PLL_UHSPLL == pllType) {
        tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_EVEN_DIV_EN, cfg->basicCfg->clkpllEvenDivEn);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_EVEN_DIV_RATIO, cfg->basicCfg->clkpllEvenDivRatio);
        BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);
    }

    /* cfg6:Set aupll_sdm_bypass,aupll_sdmin */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDMIN, cfg->clkpllSdmin);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 6, tmpVal);

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

    if (waitStable) {
        /* Wait 1.5*30us    */
        arch_delay_us(45);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set System clock divider
 *
 * @param  mcuClkDiv: HCLK divider
 * @param  mcuPBclkDiv: BCLK divider
 * @param  lpClkDiv: LP clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_MCU_System_CLK_Div(uint8_t mcuClkDiv, uint8_t mcuPBclkDiv, uint8_t lpClkDiv)
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

    /* config lp clock div=lpClkDiv */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CPU_CORE_CFG7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_PICO_DIV, lpClkDiv);
    BL_WR_REG(PDS_BASE, PDS_CPU_CORE_CFG7, tmpVal);
    /* bclk act pulse */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SYS_CFG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_PICO_CLK_DIV_ACT_PULSE, 1);
    BL_WR_REG(GLB_BASE, GLB_SYS_CFG1, tmpVal);

    timeout = 1024;
    do {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_SYS_CFG1);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal, GLB_STS_PICO_CLK_PROT_DONE);
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
 * @param  lpClkDiv: LP clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Get_MCU_System_CLK_Div(uint8_t *mcuClkDiv, uint8_t *mcuPBclkDiv, uint8_t *lpClkDiv)
{
    *mcuClkDiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_HCLK_DIV);
    *mcuPBclkDiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_BCLK_DIV);
    *lpClkDiv = BL_GET_REG_BITS_VAL(BL_RD_REG(PDS_BASE, PDS_CPU_CORE_CFG7), PDS_REG_PICO_DIV);

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
    GLB_Set_MCU_System_CLK_Div(0, 0, 0);

    /* select pll output clock before select root clock */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CPU_CORE_CFG1);
    switch (clkFreq) {
        case GLB_MCU_SYS_CLK_CPUPLL_400M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 0);
            break;
        case GLB_MCU_SYS_CLK_WIFIPLL_240M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 2);
            break;
        case GLB_MCU_SYS_CLK_WIFIPLL_320M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 3);
            break;
        default:
            break;
    }
    BL_WR_REG(PDS_BASE, PDS_CPU_CORE_CFG1, tmpVal);

    /* select root clock */
    switch (clkFreq) {
        case GLB_MCU_SYS_CLK_RC32M:
            GLB_Set_MCU_System_CLK_Div(0, 0, 0);
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            break;
        case GLB_MCU_SYS_CLK_XTAL:
            GLB_Set_MCU_System_CLK_Div(0, 0, 0);
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_XTAL);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            break;
        case GLB_MCU_SYS_CLK_CPUPLL_400M:
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(1, 2, 1);
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            /* unuseful for mcu, useful for dsp, just for safe */
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_WIFIPLL_240M:
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0, 2, 1);
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            /* unuseful for mcu, useful for dsp, just for safe */
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_WIFIPLL_320M:
            /* overclock, not recommended */
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0, 3, 1);
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
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
 * @brief  select DSP0 DSP1 clock div
 *
 * @param  dspClkDiv: mm glb cpu div
 * @param  dspBclkDiv: mm glb bclk2x div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_System_CLK_Div(uint8_t dspClkDiv, uint8_t dspBclkDiv)
{
    uint32_t tmpVal = 0;
    uint32_t timeout = 1024;
    GLB_DSP_XCLK_Type dspXclkSel;
    GLB_DSP_ROOT_CLK_Type dspRootClkSel;

    /* get root clock */
    dspXclkSel = GLB_Get_DSP_XCLK_Sel();
    dspRootClkSel = GLB_Get_DSP_ROOT_CLK_Sel();

    /* change root clock to rc32m */
    if ((dspXclkSel != GLB_DSP_XCLK_RC32M) || (dspRootClkSel != GLB_DSP_ROOT_CLK_XCLK)) {
        GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_RC32M);
        GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_XCLK);
    }

    /* set div */
    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK2X_DIV, dspBclkDiv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_CLK_DIV, dspClkDiv);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CPU, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK2X_DIV_ACT_PULSE, 1);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    do {
        tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_STS_BCLK2X_PROT_DONE);
    } while ((--timeout) && (!tmpVal));
    if (!timeout) {
        return ERROR;
    }

    /* recover root clock */
    GLB_Set_DSP_XCLK_Sel(dspXclkSel);
    GLB_Set_DSP_ROOT_CLK_Sel(dspRootClkSel);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get DSP0 DSP1 clock div
 *
 * @param  dspClkDiv: mm glb cpu div
 * @param  dspBclkDiv: mm glb bclk2x div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Get_DSP_System_CLK_Div(uint8_t *dspClkDiv, uint8_t *dspBclkDiv)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CPU);
    *dspBclkDiv = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK2X_DIV);
    *dspClkDiv = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_CLK_DIV);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set dsp System clock
 *
 * @param  clkFreq: dsp system clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_Type clkFreq)
{
    GLB_DSP_XCLK_Type dspXclkSel;

    CHECK_PARAM(IS_GLB_DSP_SYS_CLK_TYPE(clkFreq));

    /* get root clock */
    dspXclkSel = GLB_Get_DSP_XCLK_Sel();

    /* Before config XTAL and PLL ,make sure root clk is from RC32M */
    GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_RC32M);
    GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_XCLK);
    GLB_Set_DSP_System_CLK_Div(0, 0);

    /* select pll output clock before select root clock */
    if (GLB_DSP_SYS_CLK_MM_WIFIPLL_240M == clkFreq) {
        GLB_Set_DSP_MUXPLL_CLK_Sel(GLB_DSP_PLL_CLK_MUXPLL_240M);
    } else if (GLB_DSP_SYS_CLK_MM_WIFIPLL_320M == clkFreq) {
        GLB_Set_DSP_MUXPLL_CLK_Sel(GLB_DSP_PLL_CLK_MUXPLL_320M);
    } else if (GLB_DSP_SYS_CLK_CPUPLL_400M == clkFreq) {
        GLB_Set_DSP_MUXPLL_CLK_Sel(GLB_DSP_PLL_CLK_CPUPLL_400M);
    }

    /* select root clock */
    switch (clkFreq) {
        case GLB_DSP_SYS_CLK_RC32M:
            GLB_Set_DSP_System_CLK_Div(0, 0);
            GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_RC32M);
            GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_XCLK);
            break;
        case GLB_DSP_SYS_CLK_XTAL:
            GLB_Set_DSP_System_CLK_Div(0, 0);
            GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_XTAL);
            GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_XCLK);
            break;
        case GLB_DSP_SYS_CLK_MM_WIFIPLL_240M:
            GLB_Set_DSP_System_CLK_Div(0, 1);
            GLB_Set_DSP_Muxpll_240M_Sel(GLB_DSP_MUXPLL_SEL_WIFIPLL_240M);
            GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        case GLB_DSP_SYS_CLK_MM_WIFIPLL_320M:
            GLB_Set_DSP_System_CLK_Div(0, 1);
            GLB_Set_DSP_Muxpll_320M_Sel(GLB_DSP_MUXPLL_SEL_WIFIPLL_320M);
            GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        case GLB_DSP_SYS_CLK_CPUPLL_400M:
            GLB_Set_DSP_System_CLK_Div(0, 1);
            GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        default:
            break;
    }
    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  select DSP0 pbus clock div
 *
 * @param  dspBclkDiv: mm glb bclk2x div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_PBCLK_Div(uint8_t dspPBclkDiv)
{
    uint32_t tmpVal = 0;

    /* set div */
    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK1X_DIV, dspPBclkDiv);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CPU, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get DSP0 pbus clock div
 *
 * @param  dspBclkDiv: mm glb bclk2x div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Get_DSP_PBCLK_Div(uint8_t *dspPBclkDiv)
{
    *dspPBclkDiv = BL_GET_REG_BITS_VAL(BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CPU), MM_GLB_REG_BCLK1X_DIV);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set dsp pbus clock
 *
 * @param  pbClkSel: dsp pbus clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_PBCLK(GLB_DSP_SYS_PBCLK_Type pbClkSel)
{
    CHECK_PARAM(IS_GLB_DSP_SYS_PBCLK_TYPE(pbClkSel));

    GLB_Set_DSP_PBCLK_Div(0);

    /* select pbroot clock */
    switch (pbClkSel) {
        case GLB_DSP_SYS_PBCLK_RC32M:
            GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_RC32M);
            GLB_Set_DSP_PBCLK_Div(0);
            GLB_Set_DSP_PBROOT_CLK_Sel(GLB_DSP_PBROOT_CLK_MM_XCLK);
            break;
        case GLB_DSP_SYS_PBCLK_XTAL:
            GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_XTAL);
            GLB_Set_DSP_PBCLK_Div(0);
            GLB_Set_DSP_PBROOT_CLK_Sel(GLB_DSP_PBROOT_CLK_MM_XCLK);
            break;
        case GLB_DSP_SYS_PBCLK_MM_WIFIPLL_160M:
            GLB_Set_DSP_Muxpll_160M_Sel(GLB_DSP_MUXPLL_SEL_WIFIPLL_160M);
            GLB_Set_DSP_PBCLK_Div(0);
            GLB_Set_DSP_PBROOT_CLK_Sel(GLB_DSP_PBROOT_CLK_MM_MUXPLL_160M);
            break;
        case GLB_DSP_SYS_PBCLK_CPUPLL_160M:
            GLB_Set_DSP_Muxpll_160M_Sel(GLB_DSP_MUXPLL_SEL_CPUPLL_160M);
            GLB_Set_DSP_PBCLK_Div(0);
            GLB_Set_DSP_PBROOT_CLK_Sel(GLB_DSP_PBROOT_CLK_MM_MUXPLL_160M);
            break;
        case GLB_DSP_SYS_PBCLK_MM_WIFIPLL_240M:
            GLB_Set_DSP_Muxpll_240M_Sel(GLB_DSP_MUXPLL_SEL_WIFIPLL_240M);
            GLB_Set_DSP_PBCLK_Div(1);
            GLB_Set_DSP_PBROOT_CLK_Sel(GLB_DSP_PBROOT_CLK_MM_MUXPLL_240M);
            break;
        default:
            break;
    }
    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSP0 clock enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_DSP0_Clock_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_MMCPU0_CLK_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DSP0 clock disable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_DSP0_Clock_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_MMCPU0_CLK_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get xclk clock source Select
 *
 * @param  None
 *
 * @return xclk clock type selection
 *
*******************************************************************************/
GLB_DSP_XCLK_Type ATTR_CLOCK_SECTION GLB_Get_DSP_XCLK_Sel(void)
{
    return (GLB_DSP_XCLK_Type)(BL_GET_REG_BITS_VAL(BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU), MM_GLB_REG_XCLK_CLK_SEL));
}

/****************************************************************************/ /**
 * @brief  Select xclk clock source
 *
 * @param  xclk: xclk clock type selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_Type xclk)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_DSP_XCLK_TYPE(xclk));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_XCLK_CLK_SEL, xclk);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get DSP root clock
 *
 * @param  None
 *
 * @return mm glb root clock type
 *
*******************************************************************************/
GLB_DSP_ROOT_CLK_Type ATTR_CLOCK_SECTION GLB_Get_DSP_ROOT_CLK_Sel(void)
{
    uint32_t tmpVal = 0;
    uint32_t rootclk = 0;

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    rootclk = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_ROOT_CLK_SEL);
    if (0 == rootclk) {
        /* xclk */
        return GLB_DSP_ROOT_CLK_XCLK;
    } else {
        /* pll */
        return GLB_DSP_ROOT_CLK_PLL;
    }
}

/****************************************************************************/ /**
 * @brief  select DSP root clock
 *
 * @param  rootClk: mm glb root clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_Type rootClk)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_DSP_ROOT_CLK_TYPE(rootClk));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    switch (rootClk) {
        case GLB_DSP_ROOT_CLK_XCLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_ROOT_CLK_SEL, 0);
            break;
        case GLB_DSP_ROOT_CLK_PLL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_ROOT_CLK_SEL, 1);
            break;
        default:
            break;
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  select DSP muxpll clock
 *
 * @param  pllClk: mm glb pll clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_MUXPLL_CLK_Sel(GLB_DSP_PLL_CLK_Type pllClk)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_PLL_CLK_TYPE(pllClk));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    switch (pllClk) {
        case GLB_DSP_PLL_CLK_MUXPLL_240M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_CLK_SEL, 0);
            break;
        case GLB_DSP_PLL_CLK_MUXPLL_320M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_CLK_SEL, 1);
            break;
        case GLB_DSP_PLL_CLK_CPUPLL_400M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_CLK_SEL, 2);
            break;
        default:
            break;
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get DSP pbroot clock
 *
 * @param  None
 *
 * @return mm DSP pbroot clock type
 *
*******************************************************************************/
GLB_DSP_PBROOT_CLK_Type ATTR_CLOCK_SECTION GLB_Get_DSP_PBROOT_CLK_Sel(void)
{
    uint32_t tmpVal = 0;
    uint32_t pbrootclk = 0;

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    pbrootclk = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK1X_SEL);
    switch (pbrootclk) {
        case 0:
            return GLB_DSP_PBROOT_CLK_MM_XCLK;
        case 1:
            return GLB_DSP_PBROOT_CLK_MM_XCLK;
        case 2:
            return GLB_DSP_PBROOT_CLK_MM_MUXPLL_160M;
        case 3:
            return GLB_DSP_PBROOT_CLK_MM_MUXPLL_240M;
        default:
            return GLB_DSP_PBROOT_CLK_MM_XCLK;
    }
}

/****************************************************************************/ /**
 * @brief  select DSP pbroot clock
 *
 * @param  pbrootClk: mm DSP pbroot clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_PBROOT_CLK_Sel(GLB_DSP_PBROOT_CLK_Type pbrootClk)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_DSP_PBROOT_CLK_TYPE(pbrootClk));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    switch (pbrootClk) {
        case GLB_DSP_PBROOT_CLK_MM_XCLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK1X_SEL, 0);
            break;
        case GLB_DSP_PBROOT_CLK_MM_MUXPLL_160M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK1X_SEL, 2);
            break;
        case GLB_DSP_PBROOT_CLK_MM_MUXPLL_240M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK1X_SEL, 3);
            break;
        default:
            break;
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
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
        case GLB_CORE_ID_D0:
            BL_WR_REG(MM_MISC_BASE, MM_MISC_CPU0_BOOT, addr);
            break;
        case GLB_CORE_ID_LP:
            BL_WR_REG(PDS_BASE, PDS_CPU_CORE_CFG13, addr);
            break;
        default:
            return ERROR;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  hold cpu
 *
 * @param  coreID: core type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Halt_CPU(GLB_CORE_ID_Type coreID)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_CORE_ID_TYPE(coreID));

    switch (coreID) {
        case GLB_CORE_ID_M0:
            PDS_Set_MCU0_Clock_Disable();
            arch_delay_us(1);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            break;
        case GLB_CORE_ID_D0:
            GLB_DSP0_Clock_Disable();
            arch_delay_us(1);
            tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET);
            tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_CTRL_MMCPU0_RESET);
            BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET, tmpVal);
            break;
        case GLB_CORE_ID_LP:
            PDS_Set_LP_Clock_Disable();
            arch_delay_us(1);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CTRL_PICO_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            break;
        default:
            return ERROR;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  release cpu
 *
 * @param  coreID: core type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Release_CPU(GLB_CORE_ID_Type coreID)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_CORE_ID_TYPE(coreID));

    switch (coreID) {
        case GLB_CORE_ID_M0:
            PDS_Set_MCU0_Clock_Enable();
            arch_delay_us(1);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_CPU_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            break;
        case GLB_CORE_ID_D0:
            GLB_DSP0_Clock_Enable();
            arch_delay_us(1);
            tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET);
            tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_CTRL_MMCPU0_RESET);
            BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_SW_SYS_RESET, tmpVal);
            break;
        case GLB_CORE_ID_LP:
            PDS_Set_LP_Clock_Enable();
            arch_delay_us(1);
            tmpVal = BL_RD_REG(GLB_BASE, GLB_SWRST_CFG2);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CTRL_PICO_RESET);
            BL_WR_REG(GLB_BASE, GLB_SWRST_CFG2, tmpVal);
            break;
        default:
            return ERROR;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set MTimer clock
 *
 * @param  enable: enable or disable
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_EMI_CLK(uint8_t enable, GLB_EMI_CLK_Type clkSel, uint32_t div)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_EMI_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3));

    /* disable EMI clock first */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_EMI_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_EMI_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_EMI_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_EMI_CFG0);
    switch (clkSel) {
        case GLB_EMI_CLK_MCU_PBCLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_EMI_CLK_SEL, 0);
            break;
        case GLB_EMI_CLK_CPUPLL_200M_CLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_EMI_CLK_SEL, 4);
            break;
        case GLB_EMI_CLK_WIFIPLL_320M_CLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_EMI_CLK_SEL, 2);
            break;
        case GLB_EMI_CLK_CPUPLL_400M_CLK:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_EMI_CLK_SEL, 3);
            break;
        default:
            break;
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_EMI_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_EMI_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_EMI_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_EMI_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_EMI_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_EMI_CFG0, tmpVal);

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
 * @brief  reconfigure WIFIPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_WIFI_PLL(GLB_XTAL_Type xtalType, const GLB_WAC_PLL_Cfg_Type * pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;
    
    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }
    
    GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_WIFIPLL);
    GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_WIFIPLL, refClk);
    GLB_Power_On_WAC_PLL(GLB_WAC_PLL_WIFIPLL, &(pllCfgList[xtalType]), 0);
    
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
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL(GLB_XTAL_Type xtalType, const GLB_WAC_PLL_Cfg_Type * pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;
    
    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }
    
    GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_AUPLL);
    GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_AUPLL, refClk);
    GLB_Power_On_WAC_PLL(GLB_WAC_PLL_AUPLL, &(pllCfgList[xtalType]), 0);
    
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure CPUPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_CPU_PLL(GLB_XTAL_Type xtalType, const GLB_WAC_PLL_Cfg_Type * pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;
    
    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }
    
    GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_CPUPLL);
    GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_CPUPLL, refClk);
    GLB_Power_On_WAC_PLL(GLB_WAC_PLL_CPUPLL, &(pllCfgList[xtalType]), 0);
    
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure MIPIPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_MIPI_PLL(GLB_XTAL_Type xtalType, const GLB_MU_PLL_Cfg_Type * pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;
    
    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }
    
    GLB_Power_Off_MU_PLL(GLB_MU_PLL_MIPIPLL);
    GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_MIPIPLL, refClk);
    GLB_Power_On_MU_PLL(GLB_MU_PLL_MIPIPLL, &(pllCfgList[xtalType]), 0);
    
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure MIPIPLL clock div
 *
 * @param  divEn: div enable
 * @param  divRatio: div ratio
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_MIPI_PLL_Div(uint8_t divEn, uint8_t divRatio)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;
    
    REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
    
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN, divEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_EVEN_DIV_RATIO, divRatio);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);
    
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure UHSPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_UHS_PLL(GLB_XTAL_Type xtalType, const GLB_MU_PLL_Cfg_Type * pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;
    
    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }
    
    GLB_Power_Off_MU_PLL(GLB_MU_PLL_UHSPLL);
    GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_UHSPLL, refClk);
    GLB_Power_On_MU_PLL(GLB_MU_PLL_UHSPLL, &(pllCfgList[xtalType]), 0);
    
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
        case CORE_ID_D0:
            return GLB_CORE_ID_D0;
        case CORE_ID_LP:
            return GLB_CORE_ID_LP;
        default:
            return GLB_CORE_ID_INVALID;
    }

    return GLB_CORE_ID_INVALID;
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
 * @param  ips: GLB_AHB_CLOCK_IP_xxx | GLB_AHB_CLOCK_IP_xxx | ......
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
                case GLB_AHB_CLOCK_IP_SDU:
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
                    tmpValCfg0 &= ~(1 << 3);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_2:
                    tmpValCfg0 &= ~(1 << 3);
                    tmpValCfg2 &= ~(1 << 24);
                    break;
                case GLB_AHB_CLOCK_IP_CCI:
                    tmpValCfg0 &= ~(1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_RF_TOP:
                    tmpValCfg1 &= ~(1 << 1);
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
                    tmpValCfg2 &= ~(1 << 19);
                    tmpValCfg2 &= ~(1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_UART0:
                    tmpValCfg1 &= ~(1 << 16);
                    break;
                case GLB_AHB_CLOCK_IP_UART1:
                    tmpValCfg1 &= ~(1 << 17);
                    break;
                case GLB_AHB_CLOCK_IP_UART2:
                    tmpValCfg1 &= ~(1 << 26);
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
                    tmpValCfg2 &= ~(1 << 8);
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_LP:
                    break;
                case GLB_AHB_CLOCK_IP_ZB_NORMAL:
                    tmpValCfg2 &= ~(1 << 9);
                    break;
                case GLB_AHB_CLOCK_IP_ZB_LP:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_NORMAL:
                    tmpValCfg2 &= ~(1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_LP:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL:
                    tmpValCfg2 &= ~(1 << 10);
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_EMI_MISC:
                    tmpValCfg2 &= ~(1 << 16);
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM0_CTRL:
                    tmpValCfg2 &= ~(1 << 17);
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM1_CTRL:
                    tmpValCfg2 &= ~(1 << 18);
                    break;
                case GLB_AHB_CLOCK_IP_USB20:
                    tmpValCfg1 &= ~(1 << 13);
                    break;
                case GLB_AHB_CLOCK_IP_MIX2:
                    tmpValCfg2 &= ~(1 << 20);
                    break;
                case GLB_AHB_CLOCK_IP_AUDIO:
                    tmpValCfg2 &= ~(1 << 21);
                    break;
                case GLB_AHB_CLOCK_IP_SDH:
                    tmpValCfg2 &= ~(1 << 22);
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_NORMAL:
                    tmpValCfg2 &= ~(1 << 11);
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_I2C1:
                    tmpValCfg1 &= ~(1 << 25);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PHY:
                    tmpValCfg0 &= ~(1 << 7);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_MAC_PHY:
                    tmpValCfg0 &= ~(1 << 6);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PLATFORM:
                    tmpValCfg0 &= ~(1 << 5);
                    break;
                case GLB_AHB_CLOCK_IP_LZ4:
                    tmpValCfg1 &= ~(1 << 29);
                    break;
                case GLB_AHB_CLOCK_IP_AUPDM:
                    tmpValCfg1 &= ~(1 << 28);
                    break;
                case GLB_AHB_CLOCK_IP_GAUGE:
                    tmpValCfg1 &= ~(1 << 0);
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
 * @param  ips: GLB_AHB_CLOCK_xxx | GLB_AHB_CLOCK_xxx | ...... (not GLB_AHB_CLOCK_IP_xxx)
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
                case GLB_AHB_CLOCK_IP_SDU:
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
                    tmpValCfg0 |= (1 << 3);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_2:
                    tmpValCfg0 |= (1 << 3);
                    tmpValCfg2 |= (1 << 24);
                    break;
                case GLB_AHB_CLOCK_IP_CCI:
                    tmpValCfg0 |= (1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_RF_TOP:
                    tmpValCfg1 |= (1 << 1);
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
                    tmpValCfg2 |= (1 << 19);
                    tmpValCfg2 |= (1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_UART0:
                    tmpValCfg1 |= (1 << 16);
                    break;
                case GLB_AHB_CLOCK_IP_UART1:
                    tmpValCfg1 |= (1 << 17);
                    break;
                case GLB_AHB_CLOCK_IP_UART2:
                    tmpValCfg1 |= (1 << 26);
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
                    tmpValCfg1 |= (1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_USB11:
                    break;
                case GLB_AHB_CLOCK_IP_CAM:
                    break;
                case GLB_AHB_CLOCK_IP_MJPEG:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_NORMAL:
                    tmpValCfg2 |= (1 << 8);
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_LP:
                    break;
                case GLB_AHB_CLOCK_IP_ZB_NORMAL:
                    tmpValCfg2 |= (1 << 9);
                    break;
                case GLB_AHB_CLOCK_IP_ZB_LP:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_NORMAL:
                    tmpValCfg2 |= (1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_LP:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL:
                    tmpValCfg2 |= (1 << 10);
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_EMI_MISC:
                    tmpValCfg2 |= (1 << 16);
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM0_CTRL:
                    tmpValCfg2 |= (1 << 17);
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM1_CTRL:
                    tmpValCfg2 |= (1 << 18);
                    break;
                case GLB_AHB_CLOCK_IP_USB20:
                    tmpValCfg1 |= (1 << 13);
                    break;
                case GLB_AHB_CLOCK_IP_MIX2:
                    tmpValCfg2 |= (1 << 20);
                    break;
                case GLB_AHB_CLOCK_IP_AUDIO:
                    tmpValCfg2 |= (1 << 21);
                    break;
                case GLB_AHB_CLOCK_IP_SDH:
                    tmpValCfg2 |= (1 << 22);
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_NORMAL:
                    tmpValCfg2 |= (1 << 11);
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_I2C1:
                    tmpValCfg1 |= (1 << 25);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PHY:
                    tmpValCfg0 |= (1 << 7);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_MAC_PHY:
                    tmpValCfg0 |= (1 << 6);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PLATFORM:
                    tmpValCfg0 |= (1 << 5);
                    break;
                case GLB_AHB_CLOCK_IP_LZ4:
                    tmpValCfg1 |= (1 << 29);
                    break;
                case GLB_AHB_CLOCK_IP_AUPDM:
                    tmpValCfg1 |= (1 << 28);
                    break;
                case GLB_AHB_CLOCK_IP_GAUGE:
                    tmpValCfg1 |= (1 << 0);
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
 * @brief  software reset
 *
 * @param  swrst: reset num
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_Type swrst)
{
    uint32_t tmpVal = 0;
    uint32_t bit = 0;
    uint32_t regAddr = 0;

    CHECK_PARAM(IS_GLB_AHB_DSP_SW_TYPE(swrst));

    if (swrst < 32) {
        bit = swrst;
        regAddr = MM_GLB_BASE + MM_GLB_MM_SW_SYS_RESET_OFFSET;
    } else if (swrst < 64) {
        bit = swrst - 32;
        regAddr = MM_GLB_BASE + MM_GLB_SW_RESET_MM_PERI_OFFSET;
    } else if (swrst < 96) {
        bit = swrst - 64;
        regAddr = MM_GLB_BASE + MM_GLB_SW_RESET_DSP2_SUB_OFFSET;
    } else if (swrst < 128) {
        bit = swrst - 96;
        regAddr = MM_GLB_BASE + MM_GLB_SW_RESET_CODEC_SUB_OFFSET;
    } else if (swrst < 160) {
        bit = swrst - 128;
        regAddr = MM_GLB_BASE + MM_GLB_IMAGE_SENSOR_CTRL_OFFSET;
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

/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL808_Peripheral_Driver */
