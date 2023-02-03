/**
  ******************************************************************************
  * @file    bl808_romapi_patch.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 Bouffalo Lab</center></h2>
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

#include "bl808_romapi_patch.h"
#include "bl808_romdriver_e907.h"
#error "Not using romndriver now"

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
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_32M = {
    .clkpllRefdivRatio = 3,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_38P4M = {
    .clkpllRefdivRatio = 3,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_40M = {
    .clkpllRefdivRatio = 3,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_26M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION mipiPllCfg_1500M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                       /*!< XTAL is None */
    { &mipiPllBasicCfg_24M, 0x3E800 },   /*!< XTAL is 24M */
    { &mipiPllBasicCfg_32M, 0x46500 },   /*!< XTAL is 32M */
    { &mipiPllBasicCfg_38P4M, 0x3A980 }, /*!< XTAL is 38.4M */
    { &mipiPllBasicCfg_40M, 0x38400 },   /*!< XTAL is 40M */
    { &mipiPllBasicCfg_26M, 0x39B13 },   /*!< XTAL is 26M */
    { &mipiPllBasicCfg_32M, 0x46500 },   /*!< XTAL is RC32M */
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
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_32M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_38P4M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_40M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1400MCfg_26M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 4,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_1400M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll1400MCfg_24M, 0x3A555 },   /*!< XTAL is 24M */
    { &uhsPll1400MCfg_32M, 0x41A00 },   /*!< XTAL is 32M */
    { &uhsPll1400MCfg_38P4M, 0x36B00 }, /*!< XTAL is 38.4M */
    { &uhsPll1400MCfg_40M, 0x34800 },   /*!< XTAL is 40M */
    { &uhsPll1400MCfg_26M, 0x35D89 },   /*!< XTAL is 26M */
    { &uhsPll1400MCfg_32M, 0x41A00 },   /*!< XTAL is RC32M */
};

/* uhs PLL 1500 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_24M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_32M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_38P4M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_40M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1500MCfg_26M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1500/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_1500M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll1500MCfg_24M, 0x3E800 },   /*!< XTAL is 24M */
    { &uhsPll1500MCfg_32M, 0x46500 },   /*!< XTAL is 32M */
    { &uhsPll1500MCfg_38P4M, 0x3A980 }, /*!< XTAL is 38.4M */
    { &uhsPll1500MCfg_40M, 0x38400 },   /*!< XTAL is 40M */
    { &uhsPll1500MCfg_26M, 0x39B13 },   /*!< XTAL is 26M */
    { &uhsPll1500MCfg_32M, 0x46500 },   /*!< XTAL is RC32M */
};

/* uhs PLL 1600 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1600BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
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
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_32M = {
    .clkpllRefdivRatio = 4,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_38P4M = {
    .clkpllRefdivRatio = 4,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_40M = {
    .clkpllRefdivRatio = 4,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll400BasicCfg_26M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 400/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_400M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll400BasicCfg_24M, 0x19000 },    /*!< XTAL is 24M */
    { &uhsPll400BasicCfg_32M, 0x19000 },    /*!< XTAL is 32M */
    { &uhsPll400BasicCfg_38P4M, 0x14D55 },  /*!< XTAL is 38.4M */
    { &uhsPll400BasicCfg_40M, 0x14000 },    /*!< XTAL is 40M */
    { &uhsPll400BasicCfg_26M, 0x1713B },    /*!< XTAL is 26M */
    { &uhsPll400BasicCfg_32M, 0x19000 },    /*!< XTAL is RC32M */
};

/* uhs PLL 667 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_24M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_32M = {
    .clkpllRefdivRatio = 4,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_38P4M = {
    .clkpllRefdivRatio = 4,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_40M = {
    .clkpllRefdivRatio = 4,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll667BasicCfg_26M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 1,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 667/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_667M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll667BasicCfg_24M, 0x29B00 },    /*!< XTAL is 24M */
    { &uhsPll667BasicCfg_32M, 0x29B00 },    /*!< XTAL is 32M */
    { &uhsPll667BasicCfg_38P4M, 0x22BD5 },  /*!< XTAL is 38.4M */
    { &uhsPll667BasicCfg_40M, 0x21599 },    /*!< XTAL is 40M */
    { &uhsPll667BasicCfg_26M, 0x267B1 },    /*!< XTAL is 26M */
    { &uhsPll667BasicCfg_32M, 0x29B00 },    /*!< XTAL is RC32M */
};

/* uhs PLL 800 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_24M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_32M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_38P4M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_40M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll800BasicCfg_26M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 800/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_800M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll800BasicCfg_24M, 0x21555 },    /*!< XTAL is 24M */
    { &uhsPll800BasicCfg_32M, 0x25800 },    /*!< XTAL is 32M */
    { &uhsPll800BasicCfg_38P4M, 0x1F400 },  /*!< XTAL is 38.4M */
    { &uhsPll800BasicCfg_40M, 0x1E000 },    /*!< XTAL is 40M */
    { &uhsPll800BasicCfg_26M, 0x1EC4E },    /*!< XTAL is 26M */
    { &uhsPll800BasicCfg_32M, 0x25800 },    /*!< XTAL is RC32M */
};

/* uhs PLL 1066 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_24M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_32M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_38P4M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_40M = {
    .clkpllRefdivRatio = 3,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll1066BasicCfg_26M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 1066/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_1066M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll1066BasicCfg_24M, 0x2C6AA },   /*!< XTAL is 24M */
    { &uhsPll1066BasicCfg_32M, 0x31F80 },   /*!< XTAL is 32M */
    { &uhsPll1066BasicCfg_38P4M, 0x29A40 }, /*!< XTAL is 38.4M */
    { &uhsPll1066BasicCfg_40M, 0x27F99 },   /*!< XTAL is 40M */
    { &uhsPll1066BasicCfg_26M, 0x29000 },   /*!< XTAL is 26M */
    { &uhsPll1066BasicCfg_32M, 0x31F80 },   /*!< XTAL is RC32M */
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
    .clkpllSelSampleClk = 1,    /*!< pll_sel_sample_clk */
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

static intCallback_Type *uartIntCbfArra[UART_ID_MAX][UART_INT_ALL] = {
    { NULL }
};
#ifndef BFLB_USE_HAL_DRIVER
static const uint32_t uartAddr[UART_ID_MAX] = { UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE };

typedef struct
{
    uint32_t jedecID;
    char *name;
    const SPI_Flash_Cfg_Type *cfg;
} Flash_Info_t;
#endif

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_GD_LQ64E = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xc8,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x02,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x01,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xa0,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3d,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 500,
    .timeE32k = 2000,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 3,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Winb_64JW = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xef,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x31,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 0,
    .cReadMode = 0xf0,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 400,
    .timeE32k = 1600,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 3,
    .qeData = 0,
};


static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_XM25QH16={
    .resetCreadCmd=0xff,
    .resetCreadCmdSize=3,
    .mid=0x20,

    .deBurstWrapCmd=0x77,
    .deBurstWrapCmdDmyClk=0x3,
    .deBurstWrapDataMode=SF_CTRL_DATA_4_LINES,
    .deBurstWrapData=0xF0,

    /*reg*/
    .writeEnableCmd=0x06,
    .wrEnableIndex=0x00,
    .wrEnableBit=0x01,
    .wrEnableReadRegLen=0x01,

    .qeIndex=1,
    .qeBit=0x01,
    .qeWriteRegLen=0x01,
    .qeReadRegLen=0x1,

    .busyIndex=0,
    .busyBit=0x00,
    .busyReadRegLen=0x1,
    .releasePowerDown=0xab,

    .readRegCmd[0]=0x05,
    .readRegCmd[1]=0x35,
    .writeRegCmd[0]=0x01,
    .writeRegCmd[1]=0x31,

    .fastReadQioCmd=0xeb,
    .frQioDmyClk=16/8,
    .cReadSupport=1,
    .cReadMode=0x20,

    .burstWrapCmd=0x77,
    .burstWrapCmdDmyClk=0x3,
    .burstWrapDataMode=SF_CTRL_DATA_4_LINES,
    .burstWrapData=0x40,
        /*erase*/
    .chipEraseCmd=0xc7,
    .sectorEraseCmd=0x20,
    .blk32EraseCmd=0x52,
    .blk64EraseCmd=0xd8,
    /*write*/
    .pageProgramCmd=0x02,
    .qpageProgramCmd=0x32,
    .qppAddrMode=SF_CTRL_ADDR_1_LINE,

    .ioMode=SF_CTRL_QIO_MODE,
    .clkDelay=1,
    .clkInvert=0x01,

    .resetEnCmd=0x66,
    .resetCmd=0x99,
    .cRExit=0xff,
    .wrEnableWriteRegLen=0x00,

    /*id*/
    .jedecIdCmd=0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd=0x0b,
    .frDmyClk=8/8,
    .qpiFastReadCmd =0x0b,
    .qpiFrDmyClk=8/8,
    .fastReadDoCmd=0x3b,
    .frDoDmyClk=8/8,
    .fastReadDioCmd=0xbb,
    .frDioDmyClk=0,
    .fastReadQoCmd=0x6b,
    .frQoDmyClk=8/8,

    .qpiFastReadQioCmd=0xeb,
    .qpiFrQioDmyClk=16/8,
    .qpiPageProgramCmd=0x02,
    .writeVregEnableCmd=0x50,

    /* qpi mode */
    .enterQpi=0x38,
    .exitQpi=0xff,

        /*AC*/
    .timeEsector=400,
    .timeE32k=1600,
    .timeE64k=2000,
    .timePagePgm=5,
    .timeCe=33000,
    .pdDelay=3,
    .qeData=0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Winb_256FV = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xef,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x31,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0x20,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = 0x24,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 400,
    .timeE32k = 1600,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 3,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Winb_16JV = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xef,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x31,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0x20,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 400,
    .timeE32k = 1600,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 3,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Gd_Q32E_Q128E = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xc8,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x31,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xa0,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 300,
    .timeE32k = 1200,
    .timeE64k = 1200,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 20,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Gd_Q80E_Q16E = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xc8,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x02,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x01,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xa0,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 500,
    .timeE32k = 2000,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 20,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Mxic_25L256 = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xc2,

    .deBurstWrapCmd = 0xC0,
    .deBurstWrapCmdDmyClk = 0x00,
    .deBurstWrapDataMode = SF_CTRL_DATA_1_LINE,
    .deBurstWrapData = 0x10,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 0,
    .qeBit = 0x06,
    .qeWriteRegLen = 0x02,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x15,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x01,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xA5,

    .burstWrapCmd = 0xC0,
    .burstWrapCmdDmyClk = 0x00,
    .burstWrapDataMode = SF_CTRL_DATA_1_LINE,
    .burstWrapData = 0x02,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x38,
    .qppAddrMode = SF_CTRL_ADDR_4_LINES,

    .ioMode = (SF_CTRL_QIO_MODE | 0x20),
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 400,
    .timeE32k = 1000,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 20,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION Flash_Info_t flashInfos[] = {
    {
        .jedecID = 0x1760c8,
        //.name="GD_LQ64E_64_18",
        .cfg = &flashCfg_GD_LQ64E,
    },
    {
        .jedecID = 0x1760ef,
        //.name="WB_64JW_64_18",
        .cfg = &flashCfg_Winb_64JW,
    },
    {
        .jedecID=0x144020,
        //.name="XM_25QH80_80_33",
        .cfg=&flashCfg_XM25QH16,
    },
    {
        .jedecID=0x154020,
        //.name="XM_25QH16_16_33",
        .cfg=&flashCfg_XM25QH16,
    },
    {
        .jedecID=0x164020,
        //.name="XM_25QH32_32_33",
        .cfg=&flashCfg_XM25QH16,
    },
    {
        .jedecID=0x174020,
        //.name="XM_25QH64_64_33",
        .cfg=&flashCfg_XM25QH16,
    },
    {
        .jedecID = 0x17400B,
        //.name="XT_25F64B_32_33",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x1570ef,
        //.name="Winb_16JV_16_33",
        .cfg = &flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x1940ef,
        //.name="Winb_256FV_128_33",
        .cfg = &flashCfg_Winb_256FV,
    },
    {
        .jedecID = 0x1860c8,
        //.name="GD_LQ128E_64_18",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x15345e,
        //.name="ZB_WQ16A_16_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x15405e,
        //.name="ZB_Q16B_16_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x16405e,
        //.name="ZB_Q32B_32_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x17405e,
        //.name="ZB_Q64B_64_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x15605E,
        //.name="ZB_VQ16",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x3925C2,
        //.name="MX_25U256_256_33",
        .cfg = &flashCfg_Mxic_25L256,
    },
    {
        .jedecID = 0x1740c8,
        //.name="GD_Q64E_64_18",
        .cfg = &flashCfg_XM25QH16,
    }
};

static void UART_IntHandler(UART_ID_Type uartId)
{
    uint32_t tmpVal = 0;
    uint32_t maskVal = 0;
    uint32_t UARTx = uartAddr[uartId];

    tmpVal = BL_RD_REG(UARTx, UART_INT_STS);
    maskVal = BL_RD_REG(UARTx, UART_INT_MASK);

    /* Length of uart tx data transfer arrived interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_END_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_END_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_UTX_END_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_TX_END] != NULL) {
            uartIntCbfArra[uartId][UART_INT_TX_END]();
        }
    }

    /* Length of uart rx data transfer arrived interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_END_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_END_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_END_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_RX_END] != NULL) {
            uartIntCbfArra[uartId][UART_INT_RX_END]();
        }
    }

    /* Tx fifo ready interrupt,auto-cleared when data is pushed */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_FRDY_MASK)) {
        if (uartIntCbfArra[uartId][UART_INT_TX_FIFO_REQ] != NULL) {
            uartIntCbfArra[uartId][UART_INT_TX_FIFO_REQ]();
        }
    }

    /* Rx fifo ready interrupt,auto-cleared when data is popped */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_FRDY_MASK)) {
        if (uartIntCbfArra[uartId][UART_INT_RX_FIFO_REQ] != NULL) {
            uartIntCbfArra[uartId][UART_INT_RX_FIFO_REQ]();
        }
    }

    /* Rx time-out interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_RTO_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_RTO_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_RTO_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_RTO] != NULL) {
            uartIntCbfArra[uartId][UART_INT_RTO]();
        }
    }

    /* Rx parity check error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_PCE_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_PCE_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_PCE_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_PCE] != NULL) {
            uartIntCbfArra[uartId][UART_INT_PCE]();
        }
    }

    /* Tx fifo overflow/underflow error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_FER_MASK)) {
        if (uartIntCbfArra[uartId][UART_INT_TX_FER] != NULL) {
            uartIntCbfArra[uartId][UART_INT_TX_FER]();
        }
    }

    /* Rx fifo overflow/underflow error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_FER_MASK)) {
        if (uartIntCbfArra[uartId][UART_INT_RX_FER] != NULL) {
            uartIntCbfArra[uartId][UART_INT_RX_FER]();
        }
    }

    /* Rx lin mode sync field error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_LSE_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_LSE_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_LSE_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_LSE] != NULL) {
            uartIntCbfArra[uartId][UART_INT_LSE]();
        }
    }

    /* Rx byte count reached interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_BCR_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_BCR_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_BCR_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_BCR] != NULL) {
            uartIntCbfArra[uartId][UART_INT_BCR]();
        }
    }

    /* Rx auto baud rate detection finish interrupt using start bit */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_ADS_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_ADS_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_ADS_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_STARTBIT] != NULL) {
            uartIntCbfArra[uartId][UART_INT_STARTBIT]();
        }
    }

    /* Rx auto baud rate detection finish interrupt using codeword 0x55 */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_AD5_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_AD5_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 1 << UART_CR_URX_AD5_CLR_POS);

        if (uartIntCbfArra[uartId][UART_INT_0X55] != NULL) {
            uartIntCbfArra[uartId][UART_INT_0X55]();
        }
    }
}

void UART1_IRQHandler(void)
{
    UART_IntHandler(UART1_ID);
}

void UART0_IRQHandler(void)
{
    UART_IntHandler(UART0_ID);
}

#endif

/****************************************************************************/ /**
 * @brief  Install uart interrupt callback function
 *
 * @param  uartId: UART ID type
 * @param  intType: UART interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type UART_Int_Callback_Install(UART_ID_Type uartId, UART_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_UART_ID_TYPE(uartId));
    CHECK_PARAM(IS_UART_INT_TYPE(intType));

    uartIntCbfArra[uartId][intType] = cbFun;

    return SUCCESS;
}
//CLOCK
//EFUSE
//PDS
/****************************************************************************/ /**
 * @brief  PDS turn on USB
 *
 * @param  waitReady : wait turn on usb finish
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_Turn_On_USB(uint8_t waitReady)
{
    uint32_t tmpVal = 0;

    /* USB_PHY_CTRL[3:2] reg_usb_phy_xtlsel=0                             */
    /* 2000e504 = 0x40; #100; USB_PHY_CTRL[6] reg_pu_usb20_psw=1 (VCC33A) */
    /* 2000e504 = 0x41; #500; USB_PHY_CTRL[0] reg_usb_phy_ponrst=1        */
    /* 2000e500 = 0x20; #100; USB_CTL[0] reg_usb_sw_rst_n=0               */
    /* 2000e500 = 0x22; #500; USB_CTL[1] reg_usb_ext_susp_n=1             */
    /* 2000e500 = 0x23; #100; USB_CTL[0] reg_usb_sw_rst_n=1               */
    /* #1.2ms; wait UCLK                                                  */
    /* wait(soc616_b0.usb_uclk);                                          */

    tmpVal = BL_RD_REG(PDS_BASE, PDS_USB_PHY_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_REG_USB_PHY_XTLSEL, 0);
    BL_WR_REG(PDS_BASE, PDS_USB_PHY_CTRL, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_USB_PHY_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_REG_PU_USB20_PSW);
    BL_WR_REG(PDS_BASE, PDS_USB_PHY_CTRL, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_USB_PHY_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_REG_USB_PHY_PONRST);
    BL_WR_REG(PDS_BASE, PDS_USB_PHY_CTRL, tmpVal);

    /* greater than 5T */
    arch_delay_us(1);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_USB_CTL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_REG_USB_SW_RST_N);
    BL_WR_REG(PDS_BASE, PDS_USB_CTL, tmpVal);

    /* greater than 5T */
    arch_delay_us(1);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_USB_CTL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_REG_USB_EXT_SUSP_N);
    BL_WR_REG(PDS_BASE, PDS_USB_CTL, tmpVal);

    /* wait UCLK 1.2ms */
    arch_delay_ms(3);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_USB_CTL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_REG_USB_SW_RST_N);
    BL_WR_REG(PDS_BASE, PDS_USB_CTL, tmpVal);

    if (waitReady) {
        arch_delay_ms(2);
    }

    return SUCCESS;
}

//HBN

/****************************************************************************/ /**
 * @brief  Power on XTAL 32K
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_On_Xtal_32K(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_XTAL32K);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_XTAL32K_HIZ_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PU_XTAL32K);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PU_XTAL32K_BUF);
    BL_WR_REG(HBN_BASE, HBN_XTAL32K, tmpVal);

    /* Delay >1s */
    arch_delay_us(1100);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power off XTAL 32K
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_Off_Xtal_32K(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_XTAL32K);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_XTAL32K_HIZ_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PU_XTAL32K);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PU_XTAL32K_BUF);
    BL_WR_REG(HBN_BASE, HBN_XTAL32K, tmpVal);

    return SUCCESS;
}

/**
 * @brief Power Off RC32K in all state
 *
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_CLOCK_SECTION HBN_PD_RC32K_All_State(void)
{
    int32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_RST_CTRL2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_RC32K);
    BL_WR_REG(HBN_BASE, HBN_RTC_RST_CTRL2, tmpVal);
    HBN_Power_Off_RC32K();
    return SUCCESS;
}

/**
 * @brief Power Off RC32K In power off state
 *
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_CLOCK_SECTION HBN_PD_RC32K_In_Poff(void)
{
    int32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_RST_CTRL2);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_RC32K);
    BL_WR_REG(HBN_BASE, HBN_RTC_RST_CTRL2, tmpVal);
    HBN_Power_Off_RC32K();
    return SUCCESS;
}

/****************************************************************************
 * @brief  HBN set ldo11_Rtc voltage out
 *
 * @param  ldoLevel: LDO11_Rtc volatge level
 *        0:0.60V  1:0.65V  2:0.70V  3:0.75V
 *        4:0.80V  5:0.85V  6:0.9V   7:0.95V
 *        8:1.0V   9:1.05V  10:1.1V  11:1.15V,
 *        12:1.2V  13:1.25V  14:1.3V 15:1.35V
 *
 * @return SUCCESS or ERROR
 *
 *******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_Rtc_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    HBN_RTC_MISC_Type rtcMiscCfg;

    CHECK_PARAM(IS_HBN_LDO_LEVEL_TYPE(ldoLevel));

    HBN_Get_RTC_Misc_Cfg(&rtcMiscCfg);
    rtcMiscCfg.ldo11RtcVoutSelRtc = ldoLevel;
    HBN_Set_RTC_Misc_Cfg(&rtcMiscCfg);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN set ldo11 all voltage out, not include dcdc11
 *
 * @param  ldoLevel: LDO volatge level
 *
 * @return SUCCESS or ERROR
 *
 * @note not support LDO11_Rtc 0.65v & 0.6v
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_All_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    uint32_t tmpVal;
    HBN_RTC_MISC_Type rtcMiscCfg;

    CHECK_PARAM(IS_HBN_LDO_LEVEL_TYPE(ldoLevel));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_SW_LDO11_AON_VOUT_SEL, ldoLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_SW_LDO11_RT_VOUT_SEL, ldoLevel);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);

    HBN_Get_RTC_Misc_Cfg(&rtcMiscCfg);
    rtcMiscCfg.ldo11RtcVoutSelRtc = ldoLevel;
    HBN_Set_RTC_Misc_Cfg(&rtcMiscCfg);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get RTC misc config
 *
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Get_RTC_Misc_Cfg(HBN_RTC_MISC_Type *cfg)
{
    uint32_t tmpVal = 0;
    uint32_t *pCfg = (uint32_t *)cfg;

    if (!cfg) {
        return ERROR;
    }

    /* read [31:19] */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_RST_CTRL);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, HBN_RTC_RST_CTRL_MISC);

    /* use [30:19] */
    *pCfg = tmpVal;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set RTC misc config
 *
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_RTC_Misc_Cfg(HBN_RTC_MISC_Type *cfg)
{
    uint32_t tmpVal = 0;

    if (!cfg) {
        return ERROR;
    }

    /* read [31:19] */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_RST_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_RTC_RST_CTRL_MISC, ((*(uint32_t *)cfg)<<1));
    BL_WR_REG(HBN_BASE, HBN_RTC_RST_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable ACOMP0 interrupt
 *
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Enable_AComp0_IRQ(HBN_ACOMP_INT_EDGE_Type edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN);
    tmpVal2 = tmpVal2 | (1 << edge);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable ACOMP0 interrupt
 *
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Disable_AComp0_IRQ(HBN_ACOMP_INT_EDGE_Type edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN);
    tmpVal2 = tmpVal2 & (~(1 << edge));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable ACOMP1 interrupt
 *
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Enable_AComp1_IRQ(HBN_ACOMP_INT_EDGE_Type edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN);
    tmpVal2 = tmpVal2 | (1 << edge);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable ACOMP1 interrupt
 *
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Disable_AComp1_IRQ(HBN_ACOMP_INT_EDGE_Type edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN);
    tmpVal2 = tmpVal2 & (~(1 << edge));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

//AON
/****************************************************************************/ /**
 * @brief  AON set DCDC11_Top voltage out
 *
 * @param  dcdcLevel: DCDC11_Top volatge level
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Set_DCDC11_Top_Vout(AON_DCDC_LEVEL_Type dcdcLevel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_AON_DCDC_LEVEL_TYPE(dcdcLevel));

    tmpVal = BL_RD_REG(AON_BASE, AON_DCDC_TOP_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_DCDC11_VOUT_SEL_AON, dcdcLevel);
    BL_WR_REG(AON_BASE, AON_DCDC_TOP_0, tmpVal);

    return SUCCESS;
}
/****************************************************************************/ /**
 * @brief      delay us
 *
 * @param[in]  core:  systemcoreclock
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core, uint32_t cnt, uint32_t loopT)
{
    volatile uint32_t divVal = loopT;
    volatile uint32_t speed = 0;
    volatile uint32_t cycNum = 0;

    /* 1M=100K*10, so multiple is 10 */
    /* loop function take 4 instructions, so instructionNum is 4 */
    /* divVal = multiple*instructionNum */

    if (core >= 1 * 1000 * 1000) {
        /* CPU clock >= 1MHz */
        speed = core / (100 * 1000);
        cycNum = speed * cnt;
        cycNum = cycNum / 10;
        cycNum = cycNum / divVal;
        /* cycNum >= 0 */
    } else {
        /* CPU clock < 1MHz */
        speed = core / 1000;
        cycNum = speed * cnt;
        cycNum = cycNum / 1000;
        cycNum = cycNum / divVal;
        /* cycNum >= 0 */
    }

    if (!cycNum) {
        return;
    }

    __asm__ __volatile__(
        "mv       a4,%0\n\t"
        "li       a5,0x0\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        ".align 4\n\t"
        "1  :\n"
        "beq      a5,a4,2f\n\t"
        "addi     a5,a5,0x1\n\t"
        "lui      a3,0xF0000\n\t"
        "lw       a3,0(a3)\n\t"
        "j        1b\n\t"
        "nop\n\t"
        "nop\n\t"
        "2   :\n\t"
        "nop\n"
        :                  /* output */
        : "r"(cycNum)      /* input */
        : "a3", "a4", "a5" /* destruct description */
    );
}

/****************************************************************************/ /**
 * @brief      delay us
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
void ATTR_TCM_SECTION arch_delay_us(uint32_t cnt)
{
    GLB_CORE_ID_Type coreID;
    uint32_t coreFreq;
    uint32_t loopTick = 5;
    uint32_t m0Cyc00[] = { 46, 46, 77, 85 };
    uint32_t m0Cyc10[] = { 10, 10, 77, 85 };
    uint32_t m0Cyc11[] = { 10, 10, 77, 85 };
    uint32_t d0Cyc00[] = { 5, 5, 62, 34 };
    uint32_t d0Cyc11[] = { 5, 5, 13, 13 };
    uint32_t lpCyc00[] = { 6, 6, 55, 85 };
    uint32_t *pCyc = NULL;
    uint32_t iCacheEn = 1;
    uint32_t dCacheEn = 1;

    /* requirement: icache enable && dcache enable */
    /* otherwise the latency depends on the code address */

    coreID = GLB_Get_Core_Type();

    if (GLB_CORE_ID_M0 == coreID) {
        coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
#ifdef __RV32
        iCacheEn = (__get_MHCR() & CLIC_INTIE_IE_Msk) >> CLIC_INTIE_IE_Pos;
        dCacheEn = (__get_MHCR() & CACHE_MHCR_DE_Msk) >> CACHE_MHCR_DE_Pos;
#endif
        if (iCacheEn && dCacheEn) {
            pCyc = m0Cyc11;
        } else if (iCacheEn && !dCacheEn) {
            pCyc = m0Cyc10;
        } else if (!iCacheEn && !dCacheEn) {
            pCyc = m0Cyc00;
        } else {
            pCyc = m0Cyc11;
        }
    } else if (GLB_CORE_ID_D0 == coreID) {
        coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);
#ifdef __RV64
        iCacheEn = (__get_MHCR() & CACHE_MHCR_IE_Msk) >> CACHE_MHCR_IE_Pos;
        dCacheEn = (__get_MHCR() & CACHE_MHCR_DE_Msk) >> CACHE_MHCR_DE_Pos;
#endif
        if (iCacheEn && dCacheEn) {
            pCyc = d0Cyc11;
        } else if (!iCacheEn && !dCacheEn) {
            pCyc = d0Cyc00;
        } else {
            pCyc = d0Cyc11;
        }
    } else if (GLB_CORE_ID_LP == coreID) {
        coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_LP_CLK);
        pCyc = lpCyc00;
    } else {
        coreFreq = 32 * 1000 * 1000;
        pCyc = lpCyc00;
    }

    switch (((uint32_t)&ASM_Delay_Us) >> 24) {
        case 0x22:
            loopTick = pCyc[0];
            break;
        case 0x62:
            loopTick = pCyc[0];
            break;
        case 0x3F:
            loopTick = pCyc[2];
            break;
        case 0x3E:
            loopTick = pCyc[3];
            break;
        default:
            break;
    }

    coreFreq = coreFreq ? coreFreq : (32 * 1000 * 1000);

    ASM_Delay_Us(coreFreq, cnt, loopTick);
}

/****************************************************************************/ /**
 * @brief      delay ms
 *
 * @param[in]  cnt:  delay cnt ms
 *
 * @return none
 *
 *******************************************************************************/
void ATTR_TCM_SECTION arch_delay_ms(uint32_t cnt)
{
    uint32_t i = 0;
    uint32_t count = 0;

    if (cnt >= 1024) {
        /* delay (n*1024) ms */
        for (i = 0; i < (cnt / 1024); i++) {
            arch_delay_us(1024 * 1000);
        }
    }

    count = cnt & 0x3FF;

    if (count) {
        /* delay (1-1023)ms */
        arch_delay_us(count * 1000);
    }
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

//FLASH

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
        if ((cfg->clkpllSdmin == 0x12D0E) || (cfg->clkpllSdmin == 0x1C395) || (cfg->clkpllSdmin == 0x17851) || (cfg->clkpllSdmin == 0x16944) || (cfg->clkpllSdmin == 0x115E5)) {
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
    GLB_Power_On_WAC_PLL(GLB_WAC_PLL_WIFIPLL, &(pllCfgList[xtalType]), 1);

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
    GLB_Power_On_WAC_PLL(GLB_WAC_PLL_AUPLL, &(pllCfgList[xtalType]), 1);

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
    GLB_Power_On_WAC_PLL(GLB_WAC_PLL_CPUPLL, &(pllCfgList[xtalType]), 1);

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
    GLB_Power_On_MU_PLL(GLB_MU_PLL_MIPIPLL, &(pllCfgList[xtalType]), 1);

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
    GLB_Power_On_MU_PLL(GLB_MU_PLL_UHSPLL, &(pllCfgList[xtalType]), 1);

    return SUCCESS;
}

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
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_EVEN_DIV_RATIO, evenNum);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Erase flash one 32K block
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  blkNum: flash 32K block number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION SFlash_Blk32_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t blkNum)
{
    uint32_t cnt = 0;
    uint8_t is32BitsAddr = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    BL_Err_Type stat = SFlash_Write_Enable(flashCfg);

    if (stat != SUCCESS) {
        return stat;
    }

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    is32BitsAddr = (flashCfg->ioMode & 0x20);
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;

    if (is32BitsAddr > 0) {
        flashCmd.addrSize++;
        flashCmd.cmdBuf[0] = (flashCfg->blk32EraseCmd << 24) | ((BFLB_SPIFLASH_BLK32K_SIZE * blkNum) >> 8);
        flashCmd.cmdBuf[1] = ((BFLB_SPIFLASH_BLK32K_SIZE * blkNum) << 24);
    } else {
        flashCmd.cmdBuf[0] = (flashCfg->blk32EraseCmd << 24) | (BFLB_SPIFLASH_BLK32K_SIZE * blkNum);
    }

    SF_Ctrl_SendCmd(&flashCmd);

    while (SET == SFlash_Busy(flashCfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flashCfg->timeE32k * 3) {
            return ERROR;
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  startaddr: start address to erase
 * @param  endaddr: end address(include this address) to erase
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION SFlash_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t startaddr, uint32_t endaddr)
{
    uint32_t len = 0;
    uint32_t eraseLen = 0;
    BL_Err_Type ret = SUCCESS;

    if (startaddr > endaddr) {
        return ERROR;
    }

    while (startaddr <= endaddr) {
        len = endaddr - startaddr + 1;

        if (flashCfg->blk64EraseCmd != BFLB_SPIFLASH_CMD_INVALID &&
            (startaddr & (BFLB_SPIFLASH_BLK64K_SIZE - 1)) == 0 &&
            len > (BFLB_SPIFLASH_BLK64K_SIZE - flashCfg->sectorSize * 1024)) {
            /* 64K margin address,and length > 64K-sector size, erase one first */
            ret = SFlash_Blk64_Erase(flashCfg, startaddr / BFLB_SPIFLASH_BLK64K_SIZE);
            eraseLen = BFLB_SPIFLASH_BLK64K_SIZE;
        } else if (flashCfg->blk32EraseCmd != BFLB_SPIFLASH_CMD_INVALID &&
                   (startaddr & (BFLB_SPIFLASH_BLK32K_SIZE - 1)) == 0 &&
                   len > (BFLB_SPIFLASH_BLK32K_SIZE - flashCfg->sectorSize * 1024)) {
            /* 32K margin address,and length > 32K-sector size, erase one first */
            ret = SFlash_Blk32_Erase(flashCfg, startaddr / BFLB_SPIFLASH_BLK32K_SIZE);
            eraseLen = BFLB_SPIFLASH_BLK32K_SIZE;
        } else {
            /* Sector erase */
            startaddr = ((startaddr) & (~(flashCfg->sectorSize * 1024 - 1)));
            ret = SFlash_Sector_Erase(flashCfg, startaddr / flashCfg->sectorSize / 1024);
            eraseLen = flashCfg->sectorSize * 1024;
        }

        startaddr += eraseLen;

        if (ret != SUCCESS) {
            return ERROR;
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  startaddr: start address to erase
 * @param  len: data length to erase
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_Erase_Need_Lock(SPI_Flash_Cfg_Type *pFlashCfg, uint32_t startaddr, int len,
                                                        uint8_t group, SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat;
    uint32_t offset;
    uint8_t aesEnable = 0;
    SF_Ctrl_IO_Type ioMode = (SF_Ctrl_IO_Type)pFlashCfg->ioMode & 0xf;

    XIP_SFlash_Opt_Enter(&aesEnable);
    stat = XIP_SFlash_State_Save(pFlashCfg, &offset, group, bank);

    if (stat != SUCCESS) {
        SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    } else {
        stat = SFlash_Erase(pFlashCfg, startaddr, startaddr + len - 1);
        XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
    }

    XIP_SFlash_Opt_Exit(aesEnable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Get flash config according to flash ID patch
 *
 * @param  flashID: Flash ID
 * @param  pFlashCfg: Flash config pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION SF_Cfg_Get_Flash_Cfg_Need_Lock_Ext(uint32_t flashID, SPI_Flash_Cfg_Type *pFlashCfg,
                                                                uint8_t group, SF_Ctrl_Bank_Select bank)
{
    uint32_t i;
    uint8_t buf[sizeof(SPI_Flash_Cfg_Type) + 8];
    uint32_t crc, *pCrc;
    uint32_t xipOffset;
    char flashCfgMagic[] = "FCFG";

    if (flashID == 0) {
        xipOffset = SF_Ctrl_Get_Flash_Image_Offset(group, bank);
        SF_Ctrl_Set_Flash_Image_Offset(0, group, bank);
        XIP_SFlash_Read_Via_Cache_Need_Lock(8 + BL808_FLASH_XIP_BASE, buf, sizeof(SPI_Flash_Cfg_Type) + 8, group, bank);
        SF_Ctrl_Set_Flash_Image_Offset(xipOffset, group, bank);

        if (ARCH_MemCmp(buf, flashCfgMagic, 4) == 0) {
            crc = BFLB_Soft_CRC32((uint8_t *)buf + 4, sizeof(SPI_Flash_Cfg_Type));
            pCrc = (uint32_t *)(buf + 4 + sizeof(SPI_Flash_Cfg_Type));

            if (*pCrc == crc) {
                ARCH_MemCpy_Fast(pFlashCfg, (uint8_t *)buf + 4, sizeof(SPI_Flash_Cfg_Type));
                return SUCCESS;
            }
        }
    } else {
        if(RomDriver_SF_Cfg_Get_Flash_Cfg_Need_Lock(flashID, pFlashCfg, group, bank) == SUCCESS){
            return SUCCESS;
        }
        for (i = 0; i < sizeof(flashInfos) / sizeof(flashInfos[0]); i++) {
            if (flashInfos[i].jedecID == flashID) {
                ARCH_MemCpy_Fast(pFlashCfg, flashInfos[i].cfg, sizeof(SPI_Flash_Cfg_Type));
                return SUCCESS;
            }
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Identify one flash patch
 *
 * @param  callFromFlash: code run at flash or ram
 * @param  flashPinCfg: Bit 7: autoscan, Bit6-0: flash GPIO config
 * @param  restoreDefault: Wether restore default flash GPIO config
 * @param  pFlashCfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return Flash ID
 *
*******************************************************************************/
uint32_t ATTR_TCM_SECTION SF_Cfg_Flash_Identify_Ext(uint8_t callFromFlash, uint8_t flashPinCfg,
    uint8_t restoreDefault, SPI_Flash_Cfg_Type *pFlashCfg, uint8_t group, SF_Ctrl_Bank_Select bank)
{
    uint32_t jdecId = 0;
    uint32_t i = 0;
    uint32_t ret = 0;

    ret = SF_Cfg_Flash_Identify(callFromFlash, flashPinCfg, restoreDefault, pFlashCfg, group, bank);
    if(callFromFlash){
        SFlash_Set_IDbus_Cfg(pFlashCfg, pFlashCfg->ioMode&0xf , 1, 0, 32, bank);
    }
    if((ret&BFLB_FLASH_ID_VALID_FLAG) != 0){
        return ret;
    }

    jdecId = (ret&0xffffff);
    for(i=0; i<sizeof(flashInfos)/sizeof(flashInfos[0]); i++){
        if(flashInfos[i].jedecID == jdecId){
            ARCH_MemCpy_Fast(pFlashCfg, flashInfos[i].cfg,sizeof(SPI_Flash_Cfg_Type));
            break;
        }
    }
    if(i == sizeof(flashInfos)/sizeof(flashInfos[0])){
        return jdecId;
    }else{
        return (jdecId|BFLB_FLASH_ID_VALID_FLAG);
    }
}

/****************************************************************************/ /**
 * @brief  Get Xtal value
 *
 * @param  xtalVal:Xtal value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Get_Xtal_Value(uint32_t *xtalVal)
{
    uint32_t tmpVal = 0;
    uint8_t xtalType = 0;

    if (NULL == xtalVal) {
        return ERROR;
    }

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV3);
    if ((tmpVal & HBN_XTAL_FLAG_MASK) == HBN_XTAL_FLAG_VALUE) {
        xtalType = (tmpVal & 0xff);
        switch(xtalType){
            case GLB_XTAL_NONE:
                *xtalVal = 0;
                break;
            case GLB_XTAL_24M:
                *xtalVal = 24000000;
                break;
            case GLB_XTAL_32M:
                *xtalVal = 32000000;
                break;
            case GLB_XTAL_38P4M:
                *xtalVal = 38400000;
                break;
            case GLB_XTAL_40M:
                *xtalVal = 40000000;
                break;
            case GLB_XTAL_26M:
                *xtalVal = 26000000;
                break;
            case GLB_XTAL_RC32M:
                *xtalVal = 32000000;
                break;
            default :
                *xtalVal = 0;
                break;
        }
        return SUCCESS;
    }

    *xtalVal = 0;
    return ERROR;
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

    tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_VRAM_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_H2PF_SRAM_REL, h2pfSramRel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_VRAM_SRAM_REL, vramSramRel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_DSPL2_SRAM_REL, dspl2SramRel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_BLAI_SRAM_REL, blaiSramRel);
    BL_WR_REG(MM_MISC_BASE, MM_MISC_VRAM_CTRL, tmpVal);

    /* Make the above settings effective */
    tmpVal = BL_RD_REG(MM_MISC_BASE, MM_MISC_VRAM_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_MISC_REG_SYSRAM_SET, 1);
    BL_WR_REG(MM_MISC_BASE, MM_MISC_VRAM_CTRL, tmpVal);

    return SUCCESS;
}
