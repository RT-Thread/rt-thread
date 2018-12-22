/******************************************************************************
**
** \file      gh_debug_auc.c
**
** \brief     RCT Debug Registers.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#include "gh_debug_auc.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_CORE_CTRL (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_CORE_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_CORE_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_CORE_FRAC (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_CORE_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_FRAC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_FRAC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_CORE_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_FRAC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_FRAC] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_HDMI_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_HDMI_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_HDMI_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_HDMI_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_HDMI_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_HDMI_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_HDMI_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_HDMI_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_HDMI_CTRL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_HDMI_CTRL_Hdmi_phy_test_mode(U8 data)
{
    GH_DEBUG_AUC_HDMI_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_HDMI_CTRL;
    d.bitc.hdmi_phy_test_mode = data;
    *(volatile U32 *)REG_DEBUG_AUC_HDMI_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_HDMI_CTRL_Hdmi_phy_test_mode] <-- 0x%08x\n",
                        REG_DEBUG_AUC_HDMI_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_HDMI_CTRL_Hdmi_phy_test_mode(void)
{
    GH_DEBUG_AUC_HDMI_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_HDMI_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_HDMI_CTRL_Hdmi_phy_test_mode] --> 0x%08x\n",
                        REG_DEBUG_AUC_HDMI_CTRL,value);
    #endif
    return tmp_value.bitc.hdmi_phy_test_mode;
}
void GH_DEBUG_AUC_set_HDMI_CTRL_use_hdmi_phy_clk_v(U8 data)
{
    GH_DEBUG_AUC_HDMI_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_HDMI_CTRL;
    d.bitc.use_hdmi_phy_clk_v = data;
    *(volatile U32 *)REG_DEBUG_AUC_HDMI_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_HDMI_CTRL_use_hdmi_phy_clk_v] <-- 0x%08x\n",
                        REG_DEBUG_AUC_HDMI_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_HDMI_CTRL_use_hdmi_phy_clk_v(void)
{
    GH_DEBUG_AUC_HDMI_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_HDMI_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_HDMI_CTRL_use_hdmi_phy_clk_v] --> 0x%08x\n",
                        REG_DEBUG_AUC_HDMI_CTRL,value);
    #endif
    return tmp_value.bitc.use_hdmi_phy_clk_v;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_SD48 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_SD48(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_SD48 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_SD48] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SD48,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_SD48(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_SD48);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_SD48] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SD48,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_SD48_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_SD48_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_SD48;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_SD48 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_SD48_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SD48,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_SD48_Div(void)
{
    GH_DEBUG_AUC_SCALER_SD48_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_SD48);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_SD48_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SD48,value);
    #endif
    return tmp_value.bitc.div;
}
void GH_DEBUG_AUC_set_SCALER_SD48_SDCLK_delay(U8 data)
{
    GH_DEBUG_AUC_SCALER_SD48_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_SD48;
    d.bitc.sdclk_delay = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_SD48 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_SD48_SDCLK_delay] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SD48,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SCALER_SD48_SDCLK_delay(void)
{
    GH_DEBUG_AUC_SCALER_SD48_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_SD48);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_SD48_SDCLK_delay] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SD48,value);
    #endif
    return tmp_value.bitc.sdclk_delay;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_WriteEnable(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.writeenable = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_WriteEnable] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_WriteEnable(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_WriteEnable] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.writeenable;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_BYPASS(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_BYPASS] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_BYPASS(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_BYPASS] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.bypass;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_Mode(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_Mode] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_Mode(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_Mode] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.mode;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_reset(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_reset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_reset(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_reset] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.reset;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_PowerDown(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.powerdown = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_PowerDown] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_PowerDown(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_PowerDown] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.powerdown;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_HalfVCO(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.halfvco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_HalfVCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_HalfVCO(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_HalfVCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.halfvco;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_Tristate(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.tristate = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_Tristate] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_Tristate(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_Tristate] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.tristate;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_pll_tout_async(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.pll_tout_async = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_pll_tout_async] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_pll_tout_async(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_pll_tout_async] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.pll_tout_async;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_SDIV(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.sdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_SDIV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_SDIV(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_SDIV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.sdiv;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_SOUT(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.sout = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_SOUT] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_SOUT(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_SOUT] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.sout;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_pll_lock(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.pll_lock = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_pll_lock] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_pll_lock(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_pll_lock] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.pll_lock;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_gclk_vo(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.gclk_vo = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_gclk_vo] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_gclk_vo(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_gclk_vo] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.gclk_vo;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_INTPROG(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL;
    d.bitc.intprog = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL_INTPROG] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_INTPROG(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL_INTPROG] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.intprog;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO_FRAC (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_FRAC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_FRAC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_FRAC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_FRAC] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_VIDEO (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_VIDEO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_VIDEO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_VIDEO_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_VIDEO_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_VIDEO_Div(void)
{
    GH_DEBUG_AUC_SCALER_VIDEO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_SENSOR_CTRL (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_SENSOR_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_SENSOR_FRAC (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_SENSOR_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_FRAC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_FRAC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_SENSOR_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_FRAC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_FRAC] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_LOCK (read)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_AUC_get_PLL_LOCK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return value;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_VIDEO2(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_VIDEO2] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_video2;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_VIDEO(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_VIDEO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_video;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_USB(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_USB] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_usb;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_SENSOR(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_SENSOR] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_sensor;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_IDSP(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_IDSP] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_idsp;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_DDR(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_DDR] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_ddr;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_CORE(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_CORE] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_core;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_AUDIO(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_AUDIO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_audio;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_HDMI(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_HDMI] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_hdmi;
}
U8   GH_DEBUG_AUC_get_PLL_LOCK_PLL_VIN(void)
{
    GH_DEBUG_AUC_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_LOCK_PLL_VIN] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_vin;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_SENSOR_POST (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_SENSOR_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_POST = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_SENSOR_POST] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SENSOR_POST,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_SENSOR_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_POST);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_SENSOR_POST] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SENSOR_POST,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_SENSOR_POST_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_SENSOR_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_POST = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_SENSOR_POST_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SENSOR_POST,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_SENSOR_POST_Div(void)
{
    GH_DEBUG_AUC_SCALER_SENSOR_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_POST);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_SENSOR_POST_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SENSOR_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SYS_CONFIG (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SYS_CONFIG(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SYS_CONFIG(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_BootMedia(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.bootmedia = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_BootMedia] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_BootMedia(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_BootMedia] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.bootmedia;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_clock(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.clock = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_clock] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_clock(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_clock] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.clock;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_grst(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.grst = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_grst] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_grst(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_grst] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.grst;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_page_size(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.page_size = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_page_size] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_page_size(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_page_size] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.page_size;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_read(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.read = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_read] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_read(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_read] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.read;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_enet(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.enet = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_enet] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_enet(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_enet] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.enet;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_Boot_Bypass(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.boot_bypass = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_Boot_Bypass] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_Boot_Bypass(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_Boot_Bypass] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.boot_bypass;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_fastboot(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.fastboot = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_fastboot] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_fastboot(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_fastboot] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.fastboot;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_IO_Flash_boot(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.io_flash_boot = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_IO_Flash_boot] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_IO_Flash_boot(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_IO_Flash_boot] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.io_flash_boot;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_SD_BOOT(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.sd_boot = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_SD_BOOT] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_SD_BOOT(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_SD_BOOT] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.sd_boot;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_EMA_SEL(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.ema_sel = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_EMA_SEL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_EMA_SEL(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_EMA_SEL] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.ema_sel;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_lock_mode(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.lock_mode = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_lock_mode] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_lock_mode(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_lock_mode] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.lock_mode;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_grst_l(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.grst_l = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_grst_l] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_grst_l(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_grst_l] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.grst_l;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_RMII_SEL(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.rmii_sel = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_RMII_SEL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_RMII_SEL(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_RMII_SEL] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.rmii_sel;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_spi_boot(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.spi_boot = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_spi_boot] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_spi_boot(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_spi_boot] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.spi_boot;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_hif_en(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.hif_en = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_hif_en] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_hif_en(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_hif_en] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.hif_en;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_FREE(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.free = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_FREE] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_FREE(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_FREE] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.free;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_hif_type(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.hif_type = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_hif_type] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_hif_type(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_hif_type] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.hif_type;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_rdy_pl(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.rdy_pl = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_rdy_pl] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_rdy_pl(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_rdy_pl] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.rdy_pl;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_rct_ahb_hif_secure_mode(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.rct_ahb_hif_secure_mode = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_rct_ahb_hif_secure_mode] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_rct_ahb_hif_secure_mode(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_rct_ahb_hif_secure_mode] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.rct_ahb_hif_secure_mode;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_usbp(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.usbp = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_usbp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_usbp(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_usbp] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.usbp;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_ref_clk_is_24Mhz(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.ref_clk_is_24mhz = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_ref_clk_is_24Mhz] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_ref_clk_is_24Mhz(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_ref_clk_is_24Mhz] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.ref_clk_is_24mhz;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_rct_bira_efuse_disable(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.rct_bira_efuse_disable = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_rct_bira_efuse_disable] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_rct_bira_efuse_disable(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_rct_bira_efuse_disable] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.rct_bira_efuse_disable;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_hardcoded(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.hardcoded = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_hardcoded] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_hardcoded(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_hardcoded] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.hardcoded;
}
void GH_DEBUG_AUC_set_SYS_CONFIG_source(U8 data)
{
    GH_DEBUG_AUC_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG;
    d.bitc.source = data;
    *(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SYS_CONFIG_source] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SYS_CONFIG_source(void)
{
    GH_DEBUG_AUC_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SYS_CONFIG_source] --> 0x%08x\n",
                        REG_DEBUG_AUC_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.source;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_UART (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_UART(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_UART = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_UART] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_UART,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_UART(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_UART);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_UART] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_UART,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_SSI (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_SSI(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_SSI = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_SSI] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_SSI,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_SSI(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_SSI);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_SSI] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_SSI,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_MOTOR (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_MOTOR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_MOTOR = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_MOTOR] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_MOTOR,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_MOTOR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_MOTOR);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_MOTOR] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_MOTOR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_IR (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_IR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_IR = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_IR] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_IR,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_IR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_IR);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_IR] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_IR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_HOST (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_HOST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_HOST = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_HOST] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_HOST,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_HOST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_HOST);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_HOST] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_HOST,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_SENSOR_PRE (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_SENSOR_PRE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_PRE = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_SENSOR_PRE] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SENSOR_PRE,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_SENSOR_PRE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_PRE);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_SENSOR_PRE] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SENSOR_PRE,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_SENSOR_PRE_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_SENSOR_PRE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_PRE;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_PRE = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_SENSOR_PRE_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SENSOR_PRE,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_SENSOR_PRE_Div(void)
{
    GH_DEBUG_AUC_SCALER_SENSOR_PRE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_SENSOR_PRE);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_SENSOR_PRE_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_SENSOR_PRE,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_ANA_PWR (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_ANA_PWR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ANA_PWR] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_ANA_PWR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ANA_PWR);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ANA_PWR] --> 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_ANA_PWR_USBsuspend(U8 data)
{
    GH_DEBUG_AUC_ANA_PWR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR;
    d.bitc.usbsuspend = data;
    *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ANA_PWR_USBsuspend] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_ANA_PWR_USBsuspend(void)
{
    GH_DEBUG_AUC_ANA_PWR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ANA_PWR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ANA_PWR_USBsuspend] --> 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,value);
    #endif
    return tmp_value.bitc.usbsuspend;
}
void GH_DEBUG_AUC_set_ANA_PWR_suspendUSBP(U8 data)
{
    GH_DEBUG_AUC_ANA_PWR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR;
    d.bitc.suspendusbp = data;
    *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ANA_PWR_suspendUSBP] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_ANA_PWR_suspendUSBP(void)
{
    GH_DEBUG_AUC_ANA_PWR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ANA_PWR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ANA_PWR_suspendUSBP] --> 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,value);
    #endif
    return tmp_value.bitc.suspendusbp;
}
void GH_DEBUG_AUC_set_ANA_PWR_power_controller(U8 data)
{
    GH_DEBUG_AUC_ANA_PWR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR;
    d.bitc.power_controller = data;
    *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ANA_PWR_power_controller] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_ANA_PWR_power_controller(void)
{
    GH_DEBUG_AUC_ANA_PWR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ANA_PWR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ANA_PWR_power_controller] --> 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,value);
    #endif
    return tmp_value.bitc.power_controller;
}
void GH_DEBUG_AUC_set_ANA_PWR_DLLpowerdown(U8 data)
{
    GH_DEBUG_AUC_ANA_PWR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR;
    d.bitc.dllpowerdown = data;
    *(volatile U32 *)REG_DEBUG_AUC_ANA_PWR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ANA_PWR_DLLpowerdown] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_ANA_PWR_DLLpowerdown(void)
{
    GH_DEBUG_AUC_ANA_PWR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ANA_PWR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ANA_PWR_DLLpowerdown] --> 0x%08x\n",
                        REG_DEBUG_AUC_ANA_PWR,value);
    #endif
    return tmp_value.bitc.dllpowerdown;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_AUDIO_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_AUDIO_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_AUDIO_FRAC (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_AUDIO_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_FRAC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_FRAC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_AUDIO_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_FRAC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_FRAC] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_AUDIO (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_AUDIO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_AUDIO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_AUDIO,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_AUDIO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_AUDIO] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_AUDIO,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_AUDIO_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_AUDIO_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_AUDIO_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_AUDIO,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_AUDIO_Div(void)
{
    GH_DEBUG_AUC_SCALER_AUDIO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_AUDIO_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_AUDIO,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_AUDIO_PRE (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_AUDIO_PRE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO_PRE = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_AUDIO_PRE] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_AUDIO_PRE,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_AUDIO_PRE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO_PRE);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_AUDIO_PRE] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_AUDIO_PRE,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_AUDIO_PRE_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_AUDIO_PRE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO_PRE;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO_PRE = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_AUDIO_PRE_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_AUDIO_PRE,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_AUDIO_PRE_Div(void)
{
    GH_DEBUG_AUC_SCALER_AUDIO_PRE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_AUDIO_PRE);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_AUDIO_PRE_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_AUDIO_PRE,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SOFT_OR_DLLRESET (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SOFT_OR_DLLRESET(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SOFT_OR_DLLRESET = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SOFT_OR_DLLRESET] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SOFT_OR_DLLRESET,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SOFT_OR_DLLRESET(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SOFT_OR_DLLRESET);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SOFT_OR_DLLRESET] --> 0x%08x\n",
                        REG_DEBUG_AUC_SOFT_OR_DLLRESET,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SOFT_OR_DLLRESET_Softreset(U8 data)
{
    GH_DEBUG_AUC_SOFT_OR_DLLRESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SOFT_OR_DLLRESET;
    d.bitc.softreset = data;
    *(volatile U32 *)REG_DEBUG_AUC_SOFT_OR_DLLRESET = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SOFT_OR_DLLRESET_Softreset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SOFT_OR_DLLRESET,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SOFT_OR_DLLRESET_Softreset(void)
{
    GH_DEBUG_AUC_SOFT_OR_DLLRESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SOFT_OR_DLLRESET);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SOFT_OR_DLLRESET_Softreset] --> 0x%08x\n",
                        REG_DEBUG_AUC_SOFT_OR_DLLRESET,value);
    #endif
    return tmp_value.bitc.softreset;
}
void GH_DEBUG_AUC_set_SOFT_OR_DLLRESET_dll_rst_l(U8 data)
{
    GH_DEBUG_AUC_SOFT_OR_DLLRESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SOFT_OR_DLLRESET;
    d.bitc.dll_rst_l = data;
    *(volatile U32 *)REG_DEBUG_AUC_SOFT_OR_DLLRESET = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SOFT_OR_DLLRESET_dll_rst_l] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SOFT_OR_DLLRESET,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SOFT_OR_DLLRESET_dll_rst_l(void)
{
    GH_DEBUG_AUC_SOFT_OR_DLLRESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SOFT_OR_DLLRESET);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SOFT_OR_DLLRESET_dll_rst_l] --> 0x%08x\n",
                        REG_DEBUG_AUC_SOFT_OR_DLLRESET,value);
    #endif
    return tmp_value.bitc.dll_rst_l;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_FIO_RESET (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_FIO_RESET(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_FIO_RESET] <-- 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_FIO_RESET(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_FIO_RESET);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_FIO_RESET] --> 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_FIO_RESET_flashreset(U8 data)
{
    GH_DEBUG_AUC_FIO_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET;
    d.bitc.flashreset = data;
    *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_FIO_RESET_flashreset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_FIO_RESET_flashreset(void)
{
    GH_DEBUG_AUC_FIO_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_FIO_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_FIO_RESET_flashreset] --> 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,value);
    #endif
    return tmp_value.bitc.flashreset;
}
void GH_DEBUG_AUC_set_FIO_RESET_xdreset(U8 data)
{
    GH_DEBUG_AUC_FIO_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET;
    d.bitc.xdreset = data;
    *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_FIO_RESET_xdreset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_FIO_RESET_xdreset(void)
{
    GH_DEBUG_AUC_FIO_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_FIO_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_FIO_RESET_xdreset] --> 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,value);
    #endif
    return tmp_value.bitc.xdreset;
}
void GH_DEBUG_AUC_set_FIO_RESET_cfreset(U8 data)
{
    GH_DEBUG_AUC_FIO_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET;
    d.bitc.cfreset = data;
    *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_FIO_RESET_cfreset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_FIO_RESET_cfreset(void)
{
    GH_DEBUG_AUC_FIO_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_FIO_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_FIO_RESET_cfreset] --> 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,value);
    #endif
    return tmp_value.bitc.cfreset;
}
void GH_DEBUG_AUC_set_FIO_RESET_fioreset(U8 data)
{
    GH_DEBUG_AUC_FIO_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET;
    d.bitc.fioreset = data;
    *(volatile U32 *)REG_DEBUG_AUC_FIO_RESET = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_FIO_RESET_fioreset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_FIO_RESET_fioreset(void)
{
    GH_DEBUG_AUC_FIO_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_FIO_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_FIO_RESET_fioreset] --> 0x%08x\n",
                        REG_DEBUG_AUC_FIO_RESET,value);
    #endif
    return tmp_value.bitc.fioreset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_WDT_RST_L (read)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_AUC_get_WDT_RST_L(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_WDT_RST_L);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_WDT_RST_L] --> 0x%08x\n",
                        REG_DEBUG_AUC_WDT_RST_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_USB (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_USB(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_USB = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_USB] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_USB,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_USB(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_USB);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_USB] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_USB,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_USB_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_USB_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_USB;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_USB = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_USB_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_USB,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_USB_Div(void)
{
    GH_DEBUG_AUC_SCALER_USB_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_USB);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_USB_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_USB,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CLK_DEBOUNCE (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CLK_DEBOUNCE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CLK_DEBOUNCE = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_DEBOUNCE] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_DEBOUNCE,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CLK_DEBOUNCE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_DEBOUNCE);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_DEBOUNCE] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_DEBOUNCE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_PWM (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_PWM(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_PWM = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_PWM] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_PWM,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_PWM(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_PWM);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_PWM] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_PWM,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_USBP_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_USBP_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_USBP_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_USBP_CTRL_refclkdiv(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.refclkdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_refclkdiv] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_refclkdiv(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_refclkdiv] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.refclkdiv;
}
void GH_DEBUG_AUC_set_USBP_CTRL_usbphy_reset(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.usbphy_reset = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_usbphy_reset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_usbphy_reset(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_usbphy_reset] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.usbphy_reset;
}
void GH_DEBUG_AUC_set_USBP_CTRL_refclksel(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.refclksel = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_refclksel] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_refclksel(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_refclksel] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.refclksel;
}
void GH_DEBUG_AUC_set_USBP_CTRL_commononn(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.commononn = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_commononn] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_commononn(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_commononn] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.commononn;
}
void GH_DEBUG_AUC_set_USBP_CTRL_compdistune(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.compdistune = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_compdistune] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_compdistune(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_compdistune] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.compdistune;
}
void GH_DEBUG_AUC_set_USBP_CTRL_otgtune(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.otgtune = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_otgtune] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_otgtune(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_otgtune] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.otgtune;
}
void GH_DEBUG_AUC_set_USBP_CTRL_sqrxtune(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.sqrxtune = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_sqrxtune] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_sqrxtune(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_sqrxtune] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.sqrxtune;
}
void GH_DEBUG_AUC_set_USBP_CTRL_rxfslstune(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.rxfslstune = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_rxfslstune] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_rxfslstune(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_rxfslstune] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.rxfslstune;
}
void GH_DEBUG_AUC_set_USBP_CTRL_txpreemphasistune(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.txpreemphasistune = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_txpreemphasistune] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_txpreemphasistune(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_txpreemphasistune] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.txpreemphasistune;
}
void GH_DEBUG_AUC_set_USBP_CTRL_txrisetune(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.txrisetune = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_txrisetune] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_txrisetune(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_txrisetune] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.txrisetune;
}
void GH_DEBUG_AUC_set_USBP_CTRL_txvreftune(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.txvreftune = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_txvreftune] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_txvreftune(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_txvreftune] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.txvreftune;
}
void GH_DEBUG_AUC_set_USBP_CTRL_txhsxvtune(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.txhsxvtune = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_txhsxvtune] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_txhsxvtune(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_txhsxvtune] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.txhsxvtune;
}
void GH_DEBUG_AUC_set_USBP_CTRL_ATERESET(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.atereset = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_ATERESET] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_ATERESET(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_ATERESET] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.atereset;
}
void GH_DEBUG_AUC_set_USBP_CTRL_USBDCsoftreset(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.usbdcsoftreset = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_USBDCsoftreset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_USBDCsoftreset(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_USBDCsoftreset] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.usbdcsoftreset;
}
void GH_DEBUG_AUC_set_USBP_CTRL_SLEEPM(U8 data)
{
    GH_DEBUG_AUC_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL;
    d.bitc.sleepm = data;
    *(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USBP_CTRL_SLEEPM] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USBP_CTRL_SLEEPM(void)
{
    GH_DEBUG_AUC_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USBP_CTRL_SLEEPM] --> 0x%08x\n",
                        REG_DEBUG_AUC_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.sleepm;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CKEN_VDSP (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CKEN_VDSP(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CKEN_VDSP] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_VDSP,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CKEN_VDSP(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CKEN_VDSP] --> 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_VDSP,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_CKEN_VDSP_cken_tsfm(U8 data)
{
    GH_DEBUG_AUC_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP;
    d.bitc.cken_tsfm = data;
    *(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CKEN_VDSP_cken_tsfm] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_VDSP,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CKEN_VDSP_cken_tsfm(void)
{
    GH_DEBUG_AUC_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CKEN_VDSP_cken_tsfm] --> 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.cken_tsfm;
}
void GH_DEBUG_AUC_set_CKEN_VDSP_cken_code(U8 data)
{
    GH_DEBUG_AUC_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP;
    d.bitc.cken_code = data;
    *(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CKEN_VDSP_cken_code] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_VDSP,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CKEN_VDSP_cken_code(void)
{
    GH_DEBUG_AUC_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CKEN_VDSP_cken_code] --> 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.cken_code;
}
void GH_DEBUG_AUC_set_CKEN_VDSP_cken_smem(U8 data)
{
    GH_DEBUG_AUC_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP;
    d.bitc.cken_smem = data;
    *(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CKEN_VDSP_cken_smem] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_VDSP,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CKEN_VDSP_cken_smem(void)
{
    GH_DEBUG_AUC_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CKEN_VDSP_cken_smem] --> 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.cken_smem;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_DLL0 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_DLL0(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_DLL0 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL0] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL0,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_DLL0(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL0);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL0] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL0,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_DLL0_DLL_SEL2(U8 data)
{
    GH_DEBUG_AUC_DLL0_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL0;
    d.bitc.dll_sel2 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL0 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL0_DLL_SEL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL0,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL0_DLL_SEL2(void)
{
    GH_DEBUG_AUC_DLL0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL0);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL0_DLL_SEL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL0,value);
    #endif
    return tmp_value.bitc.dll_sel2;
}
void GH_DEBUG_AUC_set_DLL0_DLL_SEL1(U8 data)
{
    GH_DEBUG_AUC_DLL0_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL0;
    d.bitc.dll_sel1 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL0 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL0_DLL_SEL1] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL0,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL0_DLL_SEL1(void)
{
    GH_DEBUG_AUC_DLL0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL0);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL0_DLL_SEL1] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL0,value);
    #endif
    return tmp_value.bitc.dll_sel1;
}
void GH_DEBUG_AUC_set_DLL0_DLL_SEL0(U8 data)
{
    GH_DEBUG_AUC_DLL0_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL0;
    d.bitc.dll_sel0 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL0 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL0_DLL_SEL0] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL0,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL0_DLL_SEL0(void)
{
    GH_DEBUG_AUC_DLL0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL0);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL0_DLL_SEL0] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL0,value);
    #endif
    return tmp_value.bitc.dll_sel0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_DLL1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_DLL1(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_DLL1 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL1] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL1,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_DLL1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL1);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL1] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL1,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_DLL1_DLL_SEL2(U8 data)
{
    GH_DEBUG_AUC_DLL1_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL1;
    d.bitc.dll_sel2 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL1 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL1_DLL_SEL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL1,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL1_DLL_SEL2(void)
{
    GH_DEBUG_AUC_DLL1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL1);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL1_DLL_SEL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL1,value);
    #endif
    return tmp_value.bitc.dll_sel2;
}
void GH_DEBUG_AUC_set_DLL1_DLL_SEL1(U8 data)
{
    GH_DEBUG_AUC_DLL1_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL1;
    d.bitc.dll_sel1 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL1 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL1_DLL_SEL1] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL1,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL1_DLL_SEL1(void)
{
    GH_DEBUG_AUC_DLL1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL1);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL1_DLL_SEL1] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL1,value);
    #endif
    return tmp_value.bitc.dll_sel1;
}
void GH_DEBUG_AUC_set_DLL1_DLL_SEL0(U8 data)
{
    GH_DEBUG_AUC_DLL1_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL1;
    d.bitc.dll_sel0 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL1 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL1_DLL_SEL0] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL1,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL1_DLL_SEL0(void)
{
    GH_DEBUG_AUC_DLL1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL1);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL1_DLL_SEL0] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL1,value);
    #endif
    return tmp_value.bitc.dll_sel0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_ADC (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_ADC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_ADC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_ADC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ADC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_ADC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_ADC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_ADC] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ADC,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_ADC_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_ADC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_ADC;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_ADC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_ADC_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ADC,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_ADC_Div(void)
{
    GH_DEBUG_AUC_SCALER_ADC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_ADC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_ADC_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ADC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_VIDEO_POST (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_VIDEO_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO_POST = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO_POST] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO_POST,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_VIDEO_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO_POST);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO_POST] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO_POST,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_VIDEO_POST_Div(U16 data)
{
    GH_DEBUG_AUC_SCALER_VIDEO_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO_POST = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO_POST_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO_POST,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_VIDEO_POST_Div(void)
{
    GH_DEBUG_AUC_SCALER_VIDEO_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO_POST);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO_POST_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CLK_REF_AU_EXTERNAL (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CLK_REF_AU_EXTERNAL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_REF_AU_EXTERNAL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CLK_REF_AU_EXTERNAL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_REF_AU_EXTERNAL] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_CLK_REF_AU_EXTERNAL_external(U8 data)
{
    GH_DEBUG_AUC_CLK_REF_AU_EXTERNAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_REF_AU_EXTERNAL_external] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CLK_REF_AU_EXTERNAL_external(void)
{
    GH_DEBUG_AUC_CLK_REF_AU_EXTERNAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_REF_AU_EXTERNAL_external] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_AU_EXTERNAL,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_USE_EXTERNAL_CLK_AU (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_USE_EXTERNAL_CLK_AU(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_EXTERNAL_CLK_AU] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_USE_EXTERNAL_CLK_AU(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_EXTERNAL_CLK_AU] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_USE_EXTERNAL_CLK_AU_external(U8 data)
{
    GH_DEBUG_AUC_USE_EXTERNAL_CLK_AU_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_EXTERNAL_CLK_AU_external] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USE_EXTERNAL_CLK_AU_external(void)
{
    GH_DEBUG_AUC_USE_EXTERNAL_CLK_AU_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_EXTERNAL_CLK_AU_external] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_CLK_AU,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL (read/write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CLK_REF_VIDEO_EXTERNAL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_REF_VIDEO_EXTERNAL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CLK_REF_VIDEO_EXTERNAL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_REF_VIDEO_EXTERNAL] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_CLK_REF_VIDEO_EXTERNAL_external(U8 data)
{
    GH_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_REF_VIDEO_EXTERNAL_external] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CLK_REF_VIDEO_EXTERNAL_external(void)
{
    GH_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_REF_VIDEO_EXTERNAL_external] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_VIDEO_EXTERNAL,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_USE_EXTERNAL_VD_CLK (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_USE_EXTERNAL_VD_CLK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_EXTERNAL_VD_CLK] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_USE_EXTERNAL_VD_CLK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_EXTERNAL_VD_CLK] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_USE_EXTERNAL_VD_CLK_external(U8 data)
{
    GH_DEBUG_AUC_USE_EXTERNAL_VD_CLK_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_EXTERNAL_VD_CLK_external] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USE_EXTERNAL_VD_CLK_external(void)
{
    GH_DEBUG_AUC_USE_EXTERNAL_VD_CLK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_EXTERNAL_VD_CLK_external] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_VD_CLK,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_USE_CLK_SI_4_CLK_AU (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_AU(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_AU] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_AU(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_AU] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_AU_PLLref(U8 data)
{
    GH_DEBUG_AUC_USE_CLK_SI_4_CLK_AU_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_AU_PLLref] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_AU_PLLref(void)
{
    GH_DEBUG_AUC_USE_CLK_SI_4_CLK_AU_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_AU_PLLref] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_AU,value);
    #endif
    return tmp_value.bitc.pllref;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_USE_CLK_SI_4_CLK_VO (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_VO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_VO] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO_PLLref(U8 data)
{
    GH_DEBUG_AUC_USE_CLK_SI_4_CLK_VO_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO_PLLref] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_VO_PLLref(void)
{
    GH_DEBUG_AUC_USE_CLK_SI_4_CLK_VO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_VO_PLLref] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO,value);
    #endif
    return tmp_value.bitc.pllref;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CLK_SI_INPUT_MODE (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CLK_SI_INPUT_MODE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CLK_SI_INPUT_MODE = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_SI_INPUT_MODE] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_SI_INPUT_MODE,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CLK_SI_INPUT_MODE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_SI_INPUT_MODE);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_SI_INPUT_MODE] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_SI_INPUT_MODE,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_CLK_SI_INPUT_MODE_clk_si(U8 data)
{
    GH_DEBUG_AUC_CLK_SI_INPUT_MODE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CLK_SI_INPUT_MODE;
    d.bitc.clk_si = data;
    *(volatile U32 *)REG_DEBUG_AUC_CLK_SI_INPUT_MODE = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_SI_INPUT_MODE_clk_si] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_SI_INPUT_MODE,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CLK_SI_INPUT_MODE_clk_si(void)
{
    GH_DEBUG_AUC_CLK_SI_INPUT_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_SI_INPUT_MODE);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_SI_INPUT_MODE_clk_si] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_SI_INPUT_MODE,value);
    #endif
    return tmp_value.bitc.clk_si;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO2_CTRL (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL_pll_lock(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO2_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL;
    d.bitc.pll_lock = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL_pll_lock] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL_pll_lock(void)
{
    GH_DEBUG_AUC_PLL_VIDEO2_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL_pll_lock] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL,value);
    #endif
    return tmp_value.bitc.pll_lock;
}
void GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL_gclk_vo(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO2_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL;
    d.bitc.gclk_vo = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL_gclk_vo] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL_gclk_vo(void)
{
    GH_DEBUG_AUC_PLL_VIDEO2_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL_gclk_vo] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL,value);
    #endif
    return tmp_value.bitc.gclk_vo;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO2_FRAC (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO2_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_FRAC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO2_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_FRAC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO2_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_FRAC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO2_FRAC] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_VIDEO2 (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_VIDEO2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_VIDEO2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO2] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_VIDEO2_IntegerDiv(U16 data)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2;
    d.bitc.integerdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO2_IntegerDiv] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_VIDEO2_IntegerDiv(void)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO2_IntegerDiv] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2,value);
    #endif
    return tmp_value.bitc.integerdiv;
}
void GH_DEBUG_AUC_set_SCALER_VIDEO2_PrimeDiv(U8 data)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2;
    d.bitc.primediv = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO2_PrimeDiv] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SCALER_VIDEO2_PrimeDiv(void)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO2_PrimeDiv] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2,value);
    #endif
    return tmp_value.bitc.primediv;
}
void GH_DEBUG_AUC_set_SCALER_VIDEO2_DutyCycle(U8 data)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2;
    d.bitc.dutycycle = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO2_DutyCycle] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SCALER_VIDEO2_DutyCycle(void)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO2_DutyCycle] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2,value);
    #endif
    return tmp_value.bitc.dutycycle;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_VIDEO2_POST (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_VIDEO2_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO2_POST] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2_POST,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_VIDEO2_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO2_POST] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2_POST,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_VIDEO2_POST_IntegerDiv(U16 data)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST;
    d.bitc.integerdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO2_POST_IntegerDiv] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2_POST,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_SCALER_VIDEO2_POST_IntegerDiv(void)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO2_POST_IntegerDiv] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2_POST,value);
    #endif
    return tmp_value.bitc.integerdiv;
}
void GH_DEBUG_AUC_set_SCALER_VIDEO2_POST_PrimeDiv(U8 data)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST;
    d.bitc.primediv = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO2_POST_PrimeDiv] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2_POST,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SCALER_VIDEO2_POST_PrimeDiv(void)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO2_POST_PrimeDiv] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2_POST,value);
    #endif
    return tmp_value.bitc.primediv;
}
void GH_DEBUG_AUC_set_SCALER_VIDEO2_POST_DutyCycle(U8 data)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST;
    d.bitc.dutycycle = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_VIDEO2_POST_DutyCycle] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2_POST,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SCALER_VIDEO2_POST_DutyCycle(void)
{
    GH_DEBUG_AUC_SCALER_VIDEO2_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_VIDEO2_POST);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_VIDEO2_POST_DutyCycle] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_VIDEO2_POST,value);
    #endif
    return tmp_value.bitc.dutycycle;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_USE_CLK_SI_4_CLK_VO2 (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_VO2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_VO2] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO2_PLLref(U8 data)
{
    GH_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO2_PLLref] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_VO2_PLLref(void)
{
    GH_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_CLK_SI_4_CLK_VO2_PLLref] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_CLK_SI_4_CLK_VO2,value);
    #endif
    return tmp_value.bitc.pllref;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_USE_EXTERNAL_VD2_CLK (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_USE_EXTERNAL_VD2_CLK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_EXTERNAL_VD2_CLK] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_USE_EXTERNAL_VD2_CLK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_EXTERNAL_VD2_CLK] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_USE_EXTERNAL_VD2_CLK_external(U8 data)
{
    GH_DEBUG_AUC_USE_EXTERNAL_VD2_CLK_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_EXTERNAL_VD2_CLK_external] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_USE_EXTERNAL_VD2_CLK_external(void)
{
    GH_DEBUG_AUC_USE_EXTERNAL_VD2_CLK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_EXTERNAL_VD2_CLK_external] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_EXTERNAL_VD2_CLK,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CLK_REF_VIDEO2_EXTERNAL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_REF_VIDEO2_EXTERNAL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CLK_REF_VIDEO2_EXTERNAL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_REF_VIDEO2_EXTERNAL] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_CLK_REF_VIDEO2_EXTERNAL_external(U8 data)
{
    GH_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_REF_VIDEO2_EXTERNAL_external] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CLK_REF_VIDEO2_EXTERNAL_external(void)
{
    GH_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_REF_VIDEO2_EXTERNAL_external] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_VIDEO2_EXTERNAL,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_DDR_CTRL (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_DDR_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_DDR_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_DDR_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_DDR_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_DDR_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_DDR_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_DDR_FRAC (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_DDR_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_FRAC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_DDR_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_DDR_FRAC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_DDR_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_FRAC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_DDR_FRAC] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_DDR_FRAC,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_DDR_FRAC_fraction(U16 data)
{
    GH_DEBUG_AUC_PLL_DDR_FRAC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_FRAC;
    d.bitc.fraction = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_FRAC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_DDR_FRAC_fraction] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_DDR_FRAC,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_DDR_FRAC_fraction(void)
{
    GH_DEBUG_AUC_PLL_DDR_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_FRAC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_DDR_FRAC_fraction] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_DDR_FRAC,value);
    #endif
    return tmp_value.bitc.fraction;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_IDSP_CTRL (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_IDSP_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_IDSP_FRAC (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_IDSP_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_FRAC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_FRAC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_IDSP_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_FRAC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_FRAC] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_FRAC,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_IDSP_FRAC_fraction(U16 data)
{
    GH_DEBUG_AUC_PLL_IDSP_FRAC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_FRAC;
    d.bitc.fraction = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_FRAC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_FRAC_fraction] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_FRAC,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_IDSP_FRAC_fraction(void)
{
    GH_DEBUG_AUC_PLL_IDSP_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_FRAC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_FRAC_fraction] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_FRAC,value);
    #endif
    return tmp_value.bitc.fraction;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_SSI2 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_SSI2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_SSI2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_SSI2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_SSI2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_SSI2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_SSI2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_SSI2] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_SSI2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_LVDS_LVCMOS (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_LVDS_LVCMOS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_LVCMOS = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_LVCMOS] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_LVCMOS,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_LVDS_LVCMOS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_LVCMOS);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_LVCMOS] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_LVCMOS,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_LVDS_LVCMOS_lvcoms_sd(U16 data)
{
    GH_DEBUG_AUC_LVDS_LVCMOS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_LVDS_LVCMOS;
    d.bitc.lvcoms_sd = data;
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_LVCMOS = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_LVCMOS_lvcoms_sd] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_LVCMOS,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_LVDS_LVCMOS_lvcoms_sd(void)
{
    GH_DEBUG_AUC_LVDS_LVCMOS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_LVCMOS);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_LVCMOS_lvcoms_sd] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_LVCMOS,value);
    #endif
    return tmp_value.bitc.lvcoms_sd;
}
void GH_DEBUG_AUC_set_LVDS_LVCMOS_lvcmos_spclk(U8 data)
{
    GH_DEBUG_AUC_LVDS_LVCMOS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_LVDS_LVCMOS;
    d.bitc.lvcmos_spclk = data;
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_LVCMOS = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_LVCMOS_lvcmos_spclk] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_LVCMOS,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_LVDS_LVCMOS_lvcmos_spclk(void)
{
    GH_DEBUG_AUC_LVDS_LVCMOS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_LVCMOS);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_LVCMOS_lvcmos_spclk] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_LVCMOS,value);
    #endif
    return tmp_value.bitc.lvcmos_spclk;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_LVDS_ASYNC (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_LVDS_ASYNC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_ASYNC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_LVDS_ASYNC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_ASYNC] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_LVDS_ASYNC_async_sd(U16 data)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC;
    d.bitc.async_sd = data;
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_ASYNC_async_sd] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_LVDS_ASYNC_async_sd(void)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_ASYNC_async_sd] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.async_sd;
}
void GH_DEBUG_AUC_set_LVDS_ASYNC_async_spclk(U8 data)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC;
    d.bitc.async_spclk = data;
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_ASYNC_async_spclk] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_LVDS_ASYNC_async_spclk(void)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_ASYNC_async_spclk] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.async_spclk;
}
void GH_DEBUG_AUC_set_LVDS_ASYNC_lvds_pd(U8 data)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC;
    d.bitc.lvds_pd = data;
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_ASYNC_lvds_pd] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_LVDS_ASYNC_lvds_pd(void)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_ASYNC_lvds_pd] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.lvds_pd;
}
void GH_DEBUG_AUC_set_LVDS_ASYNC_lvds_ib_ctrl(U8 data)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC;
    d.bitc.lvds_ib_ctrl = data;
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_ASYNC_lvds_ib_ctrl] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_LVDS_ASYNC_lvds_ib_ctrl(void)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_ASYNC_lvds_ib_ctrl] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.lvds_ib_ctrl;
}
void GH_DEBUG_AUC_set_LVDS_ASYNC_lvds_bit_mode(U8 data)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC;
    d.bitc.lvds_bit_mode = data;
    *(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_LVDS_ASYNC_lvds_bit_mode] <-- 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_LVDS_ASYNC_lvds_bit_mode(void)
{
    GH_DEBUG_AUC_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_LVDS_ASYNC_lvds_bit_mode] --> 0x%08x\n",
                        REG_DEBUG_AUC_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.lvds_bit_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_CORE_CTRL2 (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_CORE_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_CORE_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_CORE_CTRL2_Controllability(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL2_Charge(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL2_Charge(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_CORE_CTRL3 (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_CORE_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL3_VCO(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL3_Clamp(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL3_DSM_dither(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL3_Feedforward(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3_Bias(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL3_Bias(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
void GH_DEBUG_AUC_set_PLL_CORE_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_CORE_CTRL3_JDIV(void)
{
    GH_DEBUG_AUC_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_IDSP_CTRL2 (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_IDSP_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_IDSP_CTRL2_Controllability(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL2_Charge(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL2_Charge(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_IDSP_CTRL3 (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_IDSP_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_VCO(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_Clamp(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_DSM_dither(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_Feedforward(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_Bias(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_Bias(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_JDIV(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_IDSP_CTRL22 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL22(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL22 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL22] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL22,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_IDSP_CTRL22(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL22);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL22] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL22,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL22_Controllability(U16 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL22_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL22;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL22 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL22_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL22,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_IDSP_CTRL22_Controllability(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL22_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL22);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL22_Controllability] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL22,value);
    #endif
    return tmp_value.bitc.controllability;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL22_Charge(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL22_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL22;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL22 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL22_Charge] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL22,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL22_Charge(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL22_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL22);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL22_Charge] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL22,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_IDSP_CTRL32 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_IDSP_CTRL32(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_VCO(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.vco;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_PLL_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_PLL_VCO(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_Clamp(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_Clamp(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_Clamp] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.clamp;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_DSM_dither(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_DSM_dither(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_DSM_dither_gain(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_DSM_dither_gain(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_Feedforward(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_Feedforward(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.feedforward;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_Bias(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_Bias] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_Bias(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_Bias] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.bias;
}
void GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_JDIV(U8 data)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_CTRL32_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_JDIV(void)
{
    GH_DEBUG_AUC_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_CTRL32_JDIV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_CORE_POST (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_CORE_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_CORE_POST = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_CORE_POST] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_CORE_POST,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_CORE_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_CORE_POST);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_CORE_POST] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_CORE_POST,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_CORE_POST_Div(U8 data)
{
    GH_DEBUG_AUC_SCALER_CORE_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_CORE_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_CORE_POST = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_CORE_POST_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_CORE_POST,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SCALER_CORE_POST_Div(void)
{
    GH_DEBUG_AUC_SCALER_CORE_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_CORE_POST);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_CORE_POST_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_CORE_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_SENSOR_CTRL2 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_SENSOR_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_SENSOR_CTRL2_Controllability(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL2_Charge(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL2_Charge(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_SENSOR_CTRL3 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_VCO(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_Clamp(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_DSM_dither(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_Feedforward(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_Bias(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_Bias(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
void GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_JDIV(void)
{
    GH_DEBUG_AUC_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_AUDIO_CTRL2 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_AUDIO_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_AUDIO_CTRL2_Controllability(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL2_Charge(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL2_Charge(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_AUDIO_CTRL3 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_VCO(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_Clamp(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_DSM_dither(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_Feedforward(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_Bias(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_Bias(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
void GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_JDIV(void)
{
    GH_DEBUG_AUC_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO_CTRL2 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_VIDEO_CTRL2_Controllability(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL2_Charge(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL2_Charge(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO_CTRL3 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_VCO(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_Clamp(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_DSM_dither(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_Feedforward(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_Bias(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_Bias(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
void GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_JDIV(void)
{
    GH_DEBUG_AUC_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO2_CTRL2 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_AUC_PLL_VIDEO2_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL2,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL2_Controllability(void)
{
    GH_DEBUG_AUC_PLL_VIDEO2_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
void GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL2_Charge(U8 data)
{
    GH_DEBUG_AUC_PLL_VIDEO2_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL2_Charge(void)
{
    GH_DEBUG_AUC_PLL_VIDEO2_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO2_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_USB_CTRL2 (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_USB_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_USB_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_PLL_USB_CTRL2_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_USB_CTRL2_VCO(void)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.vco;
}
void GH_DEBUG_AUC_set_PLL_USB_CTRL2_PLL_VCO(U8 data)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_USB_CTRL2_PLL_VCO(void)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
void GH_DEBUG_AUC_set_PLL_USB_CTRL2_Clamp(U8 data)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_USB_CTRL2_Clamp(void)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2_Clamp] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.clamp;
}
void GH_DEBUG_AUC_set_PLL_USB_CTRL2_DSM_dither(U8 data)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_USB_CTRL2_DSM_dither(void)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
void GH_DEBUG_AUC_set_PLL_USB_CTRL2_DSM_dither_gain(U8 data)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_USB_CTRL2_DSM_dither_gain(void)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
void GH_DEBUG_AUC_set_PLL_USB_CTRL2_Feedforward(U8 data)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_USB_CTRL2_Feedforward(void)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.feedforward;
}
void GH_DEBUG_AUC_set_PLL_USB_CTRL2_Bias(U8 data)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2_Bias] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_USB_CTRL2_Bias(void)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2_Bias] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.bias;
}
void GH_DEBUG_AUC_set_PLL_USB_CTRL2_JDIV(U8 data)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_USB_CTRL2_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_PLL_USB_CTRL2_JDIV(void)
{
    GH_DEBUG_AUC_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_USB_CTRL2_JDIV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_DDR_CALIB (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_DDR_CALIB(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_DDR_CALIB = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_DDR_CALIB] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_DDR_CALIB,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_DDR_CALIB(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_DDR_CALIB);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_DDR_CALIB] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_DDR_CALIB,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_DLL_CTRL_SEL (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_DLL_CTRL_SEL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_DLL_CTRL_SEL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_dll_sbc(U16 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_dll_sbc = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_dll_sbc] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U16  GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_dll_sbc(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_dll_sbc] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_dll_sbc;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_dll_selm(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_dll_selm = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_dll_selm] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_dll_selm(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_dll_selm] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_dll_selm;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_single_end(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_single_end = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_single_end] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_single_end(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_single_end] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_single_end;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_pue_dq(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_pue_dq = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_pue_dq] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_pue_dq(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_pue_dq] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_pue_dq;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_pde_dq(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_pde_dq = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_pde_dq] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_pde_dq(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_pde_dq] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_pde_dq;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_npue_dqs = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_npue_dqs;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_npde_dqs = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_npde_dqs;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_ppde_dqs = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ppde_dqs;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_ppue_dqs = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ppue_dqs;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_cmosrcv(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_cmosrcv = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_cmosrcv] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_cmosrcv(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_cmosrcv] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_cmosrcv;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_pue_cmd(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_pue_cmd = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_pue_cmd] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_pue_cmd(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_pue_cmd] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_pue_cmd;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_pde_cmd(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_pde_cmd = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_pde_cmd] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_pde_cmd(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_pde_cmd] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_pde_cmd;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_npue_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs2] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_npue_dqs2;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_npde_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs2] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_npde_dqs2;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_ppde_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ppde_dqs2;
}
void GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(U8 data)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_ppue_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(void)
{
    GH_DEBUG_AUC_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ppue_dqs2;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_DLL_OCD_BITS (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_DLL_OCD_BITS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_OCD_BITS] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_DLL_OCD_BITS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_OCD_BITS] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_DLL_OCD_BITS_rct_ddrio_ddr2(U8 data)
{
    GH_DEBUG_AUC_DLL_OCD_BITS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS;
    d.bitc.rct_ddrio_ddr2 = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_OCD_BITS_rct_ddrio_ddr2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_OCD_BITS_rct_ddrio_ddr2(void)
{
    GH_DEBUG_AUC_DLL_OCD_BITS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_OCD_BITS_rct_ddrio_ddr2] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ddr2;
}
void GH_DEBUG_AUC_set_DLL_OCD_BITS_rct_ddrio_ocd_cmd(U8 data)
{
    GH_DEBUG_AUC_DLL_OCD_BITS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS;
    d.bitc.rct_ddrio_ocd_cmd = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_OCD_BITS_rct_ddrio_ocd_cmd] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_OCD_BITS_rct_ddrio_ocd_cmd(void)
{
    GH_DEBUG_AUC_DLL_OCD_BITS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_OCD_BITS_rct_ddrio_ocd_cmd] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ocd_cmd;
}
void GH_DEBUG_AUC_set_DLL_OCD_BITS_rct_ddrio_ocd(U8 data)
{
    GH_DEBUG_AUC_DLL_OCD_BITS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS;
    d.bitc.rct_ddrio_ocd = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_OCD_BITS_rct_ddrio_ocd] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_OCD_BITS_rct_ddrio_ocd(void)
{
    GH_DEBUG_AUC_DLL_OCD_BITS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_OCD_BITS_rct_ddrio_ocd] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ocd;
}
void GH_DEBUG_AUC_set_DLL_OCD_BITS_rct_ddrio_odt(U8 data)
{
    GH_DEBUG_AUC_DLL_OCD_BITS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS;
    d.bitc.rct_ddrio_odt = data;
    *(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DLL_OCD_BITS_rct_ddrio_odt] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DLL_OCD_BITS_rct_ddrio_odt(void)
{
    GH_DEBUG_AUC_DLL_OCD_BITS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DLL_OCD_BITS);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DLL_OCD_BITS_rct_ddrio_odt] --> 0x%08x\n",
                        REG_DEBUG_AUC_DLL_OCD_BITS,value);
    #endif
    return tmp_value.bitc.rct_ddrio_odt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_CORE_OBSV (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_CORE_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_OBSV = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_CORE_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_OBSV,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_CORE_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_CORE_OBSV);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_CORE_OBSV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_CORE_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_IDSP_OBSV (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_IDSP_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_OBSV = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_IDSP_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_OBSV,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_IDSP_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_IDSP_OBSV);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_IDSP_OBSV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_IDSP_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_DDR_OBSV (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_DDR_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_OBSV = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_DDR_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_DDR_OBSV,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_DDR_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_DDR_OBSV);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_DDR_OBSV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_DDR_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_SENSOR_OBSV (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_SENSOR_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_OBSV = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_SENSOR_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_OBSV,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_SENSOR_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_SENSOR_OBSV);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_SENSOR_OBSV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_SENSOR_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_AUDIO_OBSV (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_AUDIO_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_OBSV = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_AUDIO_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_OBSV,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_AUDIO_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_AUDIO_OBSV);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_AUDIO_OBSV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_AUDIO_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO_OBSV (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_OBSV = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_OBSV,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO_OBSV);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO_OBSV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_PLL_VIDEO2_OBSV (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_PLL_VIDEO2_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_OBSV = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_PLL_VIDEO2_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_OBSV,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_PLL_VIDEO2_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_PLL_VIDEO2_OBSV);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_PLL_VIDEO2_OBSV] --> 0x%08x\n",
                        REG_DEBUG_AUC_PLL_VIDEO2_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_ADC16_CTRL_ADDR (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_ADC16_CTRL_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_ADC16_CTRL_ADDR = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ADC16_CTRL_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ADC16_CTRL_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_ADC16_CTRL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ADC16_CTRL_ADDR);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ADC16_CTRL_ADDR] --> 0x%08x\n",
                        REG_DEBUG_AUC_ADC16_CTRL_ADDR,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_ADC16_CTRL_ADDR_adc_power_down(U8 data)
{
    GH_DEBUG_AUC_ADC16_CTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_ADC16_CTRL_ADDR;
    d.bitc.adc_power_down = data;
    *(volatile U32 *)REG_DEBUG_AUC_ADC16_CTRL_ADDR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ADC16_CTRL_ADDR_adc_power_down] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ADC16_CTRL_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_ADC16_CTRL_ADDR_adc_power_down(void)
{
    GH_DEBUG_AUC_ADC16_CTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ADC16_CTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ADC16_CTRL_ADDR_adc_power_down] --> 0x%08x\n",
                        REG_DEBUG_AUC_ADC16_CTRL_ADDR,value);
    #endif
    return tmp_value.bitc.adc_power_down;
}
void GH_DEBUG_AUC_set_ADC16_CTRL_ADDR_adc_clock_select(U8 data)
{
    GH_DEBUG_AUC_ADC16_CTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_ADC16_CTRL_ADDR;
    d.bitc.adc_clock_select = data;
    *(volatile U32 *)REG_DEBUG_AUC_ADC16_CTRL_ADDR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ADC16_CTRL_ADDR_adc_clock_select] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ADC16_CTRL_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_ADC16_CTRL_ADDR_adc_clock_select(void)
{
    GH_DEBUG_AUC_ADC16_CTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ADC16_CTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ADC16_CTRL_ADDR_adc_clock_select] --> 0x%08x\n",
                        REG_DEBUG_AUC_ADC16_CTRL_ADDR,value);
    #endif
    return tmp_value.bitc.adc_clock_select;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CLK_REF_SSI_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CLK_REF_SSI_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_SSI_ADDR = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_REF_SSI_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_SSI_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CLK_REF_SSI_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_REF_SSI_ADDR);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_REF_SSI_ADDR] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_SSI_ADDR,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_CLK_REF_SSI_ADDR_clk(U8 data)
{
    GH_DEBUG_AUC_CLK_REF_SSI_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_SSI_ADDR;
    d.bitc.clk = data;
    *(volatile U32 *)REG_DEBUG_AUC_CLK_REF_SSI_ADDR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLK_REF_SSI_ADDR_clk] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_SSI_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CLK_REF_SSI_ADDR_clk(void)
{
    GH_DEBUG_AUC_CLK_REF_SSI_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLK_REF_SSI_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLK_REF_SSI_ADDR_clk] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLK_REF_SSI_ADDR,value);
    #endif
    return tmp_value.bitc.clk;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_DVEN (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_DVEN(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_DVEN = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_DVEN] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_DVEN,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_DVEN(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_DVEN);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_DVEN] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_DVEN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_MS (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_MS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_MS = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_MS] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_MS,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_MS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_MS);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_MS] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_MS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_MS_DELAY_CTRL (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_MS_DELAY_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_MS_DELAY_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_MS_DELAY_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_MS_DELAY_CTRL] --> 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_MS_DELAY_CTRL_delay_sclk(U8 data)
{
    GH_DEBUG_AUC_MS_DELAY_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL;
    d.bitc.delay_sclk = data;
    *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_MS_DELAY_CTRL_delay_sclk] <-- 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_MS_DELAY_CTRL_delay_sclk(void)
{
    GH_DEBUG_AUC_MS_DELAY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_MS_DELAY_CTRL_delay_sclk] --> 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,value);
    #endif
    return tmp_value.bitc.delay_sclk;
}
void GH_DEBUG_AUC_set_MS_DELAY_CTRL_input_delay(U8 data)
{
    GH_DEBUG_AUC_MS_DELAY_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL;
    d.bitc.input_delay = data;
    *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_MS_DELAY_CTRL_input_delay] <-- 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_MS_DELAY_CTRL_input_delay(void)
{
    GH_DEBUG_AUC_MS_DELAY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_MS_DELAY_CTRL_input_delay] --> 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,value);
    #endif
    return tmp_value.bitc.input_delay;
}
void GH_DEBUG_AUC_set_MS_DELAY_CTRL_output_delay(U8 data)
{
    GH_DEBUG_AUC_MS_DELAY_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL;
    d.bitc.output_delay = data;
    *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_MS_DELAY_CTRL_output_delay] <-- 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_MS_DELAY_CTRL_output_delay(void)
{
    GH_DEBUG_AUC_MS_DELAY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_MS_DELAY_CTRL_output_delay] --> 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,value);
    #endif
    return tmp_value.bitc.output_delay;
}
void GH_DEBUG_AUC_set_MS_DELAY_CTRL_timing(U8 data)
{
    GH_DEBUG_AUC_MS_DELAY_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL;
    d.bitc.timing = data;
    *(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_MS_DELAY_CTRL_timing] <-- 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_MS_DELAY_CTRL_timing(void)
{
    GH_DEBUG_AUC_MS_DELAY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_MS_DELAY_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_MS_DELAY_CTRL_timing] --> 0x%08x\n",
                        REG_DEBUG_AUC_MS_DELAY_CTRL,value);
    #endif
    return tmp_value.bitc.timing;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_USE_COMMON_VO_CLOCK (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_USE_COMMON_VO_CLOCK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_USE_COMMON_VO_CLOCK = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_USE_COMMON_VO_CLOCK] <-- 0x%08x\n",
                        REG_DEBUG_AUC_USE_COMMON_VO_CLOCK,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_USE_COMMON_VO_CLOCK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_USE_COMMON_VO_CLOCK);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_USE_COMMON_VO_CLOCK] --> 0x%08x\n",
                        REG_DEBUG_AUC_USE_COMMON_VO_CLOCK,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CLOCK_OBSV_ADDR (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CLOCK_OBSV_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CLOCK_OBSV_ADDR = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLOCK_OBSV_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLOCK_OBSV_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CLOCK_OBSV_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLOCK_OBSV_ADDR);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLOCK_OBSV_ADDR] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLOCK_OBSV_ADDR,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_CLOCK_OBSV_ADDR_pll(U8 data)
{
    GH_DEBUG_AUC_CLOCK_OBSV_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CLOCK_OBSV_ADDR;
    d.bitc.pll = data;
    *(volatile U32 *)REG_DEBUG_AUC_CLOCK_OBSV_ADDR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLOCK_OBSV_ADDR_pll] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLOCK_OBSV_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CLOCK_OBSV_ADDR_pll(void)
{
    GH_DEBUG_AUC_CLOCK_OBSV_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLOCK_OBSV_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLOCK_OBSV_ADDR_pll] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLOCK_OBSV_ADDR,value);
    #endif
    return tmp_value.bitc.pll;
}
void GH_DEBUG_AUC_set_CLOCK_OBSV_ADDR_observation(U8 data)
{
    GH_DEBUG_AUC_CLOCK_OBSV_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CLOCK_OBSV_ADDR;
    d.bitc.observation = data;
    *(volatile U32 *)REG_DEBUG_AUC_CLOCK_OBSV_ADDR = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CLOCK_OBSV_ADDR_observation] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CLOCK_OBSV_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CLOCK_OBSV_ADDR_observation(void)
{
    GH_DEBUG_AUC_CLOCK_OBSV_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CLOCK_OBSV_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CLOCK_OBSV_ADDR_observation] --> 0x%08x\n",
                        REG_DEBUG_AUC_CLOCK_OBSV_ADDR,value);
    #endif
    return tmp_value.bitc.observation;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_DISABLE_EXT_BYPASS (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_DISABLE_EXT_BYPASS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_DISABLE_EXT_BYPASS = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DISABLE_EXT_BYPASS] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DISABLE_EXT_BYPASS,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_DISABLE_EXT_BYPASS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DISABLE_EXT_BYPASS);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DISABLE_EXT_BYPASS] --> 0x%08x\n",
                        REG_DEBUG_AUC_DISABLE_EXT_BYPASS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_ARM_SYNC_LOCK (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_ARM_SYNC_LOCK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_ARM_SYNC_LOCK = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ARM_SYNC_LOCK] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ARM_SYNC_LOCK,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_ARM_SYNC_LOCK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ARM_SYNC_LOCK);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ARM_SYNC_LOCK] --> 0x%08x\n",
                        REG_DEBUG_AUC_ARM_SYNC_LOCK,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_ARM_SYNC_LOCK_mode(U8 data)
{
    GH_DEBUG_AUC_ARM_SYNC_LOCK_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_ARM_SYNC_LOCK;
    d.bitc.mode = data;
    *(volatile U32 *)REG_DEBUG_AUC_ARM_SYNC_LOCK = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ARM_SYNC_LOCK_mode] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ARM_SYNC_LOCK,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_ARM_SYNC_LOCK_mode(void)
{
    GH_DEBUG_AUC_ARM_SYNC_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ARM_SYNC_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ARM_SYNC_LOCK_mode] --> 0x%08x\n",
                        REG_DEBUG_AUC_ARM_SYNC_LOCK,value);
    #endif
    return tmp_value.bitc.mode;
}
void GH_DEBUG_AUC_set_ARM_SYNC_LOCK_reset(U8 data)
{
    GH_DEBUG_AUC_ARM_SYNC_LOCK_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_ARM_SYNC_LOCK;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_AUC_ARM_SYNC_LOCK = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_ARM_SYNC_LOCK_reset] <-- 0x%08x\n",
                        REG_DEBUG_AUC_ARM_SYNC_LOCK,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_ARM_SYNC_LOCK_reset(void)
{
    GH_DEBUG_AUC_ARM_SYNC_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_ARM_SYNC_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_ARM_SYNC_LOCK_reset] --> 0x%08x\n",
                        REG_DEBUG_AUC_ARM_SYNC_LOCK,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_ARM_SYNC (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_ARM_SYNC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_ARM_SYNC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_ARM_SYNC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ARM_SYNC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_ARM_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_ARM_SYNC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_ARM_SYNC] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ARM_SYNC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_ARM_ASYNC (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_ARM_ASYNC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_ARM_ASYNC = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_ARM_ASYNC] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ARM_ASYNC,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_ARM_ASYNC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_ARM_ASYNC);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_ARM_ASYNC] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ARM_ASYNC,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_ARM_ASYNC_Div(U8 data)
{
    GH_DEBUG_AUC_SCALER_ARM_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_ARM_ASYNC;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_ARM_ASYNC = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_ARM_ASYNC_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ARM_ASYNC,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SCALER_ARM_ASYNC_Div(void)
{
    GH_DEBUG_AUC_SCALER_ARM_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_ARM_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_ARM_ASYNC_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_ARM_ASYNC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_SCALER_IDSP_POST (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_SCALER_IDSP_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_IDSP_POST = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_IDSP_POST] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_IDSP_POST,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_SCALER_IDSP_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_IDSP_POST);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_IDSP_POST] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_IDSP_POST,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_SCALER_IDSP_POST_Div(U8 data)
{
    GH_DEBUG_AUC_SCALER_IDSP_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_SCALER_IDSP_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_AUC_SCALER_IDSP_POST = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_SCALER_IDSP_POST_Div] <-- 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_IDSP_POST,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_SCALER_IDSP_POST_Div(void)
{
    GH_DEBUG_AUC_SCALER_IDSP_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_SCALER_IDSP_POST);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_SCALER_IDSP_POST_Div] --> 0x%08x\n",
                        REG_DEBUG_AUC_SCALER_IDSP_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_OCTRL_GPIO (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_OCTRL_GPIO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_OCTRL_GPIO = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_OCTRL_GPIO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_OCTRL_GPIO,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_OCTRL_GPIO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_OCTRL_GPIO);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_OCTRL_GPIO] --> 0x%08x\n",
                        REG_DEBUG_AUC_OCTRL_GPIO,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_IOCTRL_MISC1 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_IOCTRL_MISC1(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_IOCTRL_MISC1 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_IOCTRL_MISC1] <-- 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_MISC1,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_IOCTRL_MISC1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_IOCTRL_MISC1);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_IOCTRL_MISC1] --> 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_MISC1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_OCTRL_MISC2 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_OCTRL_MISC2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_OCTRL_MISC2 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_OCTRL_MISC2] <-- 0x%08x\n",
                        REG_DEBUG_AUC_OCTRL_MISC2,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_OCTRL_MISC2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_OCTRL_MISC2);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_OCTRL_MISC2] --> 0x%08x\n",
                        REG_DEBUG_AUC_OCTRL_MISC2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_IOCTRL_SD (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_IOCTRL_SD(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_IOCTRL_SD = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_IOCTRL_SD] <-- 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_SD,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_IOCTRL_SD(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_IOCTRL_SD);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_IOCTRL_SD] --> 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_SD,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_IOCTRL_SMIO (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_IOCTRL_SMIO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_IOCTRL_SMIO = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_IOCTRL_SMIO] <-- 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_SMIO,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_IOCTRL_SMIO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_IOCTRL_SMIO);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_IOCTRL_SMIO] --> 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_SMIO,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_IOCTRL_VD0 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_IOCTRL_VD0(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_IOCTRL_VD0 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_IOCTRL_VD0] <-- 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_VD0,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_IOCTRL_VD0(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_IOCTRL_VD0);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_IOCTRL_VD0] --> 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_VD0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_IOCTRL_VD1 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_IOCTRL_VD1(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_IOCTRL_VD1 = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_IOCTRL_VD1] <-- 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_VD1,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_IOCTRL_VD1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_IOCTRL_VD1);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_IOCTRL_VD1] --> 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_VD1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_IOCTRL_SENSOR (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_IOCTRL_SENSOR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_IOCTRL_SENSOR = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_IOCTRL_SENSOR] <-- 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_SENSOR,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_IOCTRL_SENSOR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_IOCTRL_SENSOR);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_IOCTRL_SENSOR] --> 0x%08x\n",
                        REG_DEBUG_AUC_IOCTRL_SENSOR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_AHB_MISC_EN (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_AHB_MISC_EN(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_AHB_MISC_EN = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_AHB_MISC_EN] <-- 0x%08x\n",
                        REG_DEBUG_AUC_AHB_MISC_EN,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_AHB_MISC_EN(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_AHB_MISC_EN);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_AHB_MISC_EN] --> 0x%08x\n",
                        REG_DEBUG_AUC_AHB_MISC_EN,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_AHB_MISC_EN_rct_ahb(U8 data)
{
    GH_DEBUG_AUC_AHB_MISC_EN_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_AHB_MISC_EN;
    d.bitc.rct_ahb = data;
    *(volatile U32 *)REG_DEBUG_AUC_AHB_MISC_EN = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_AHB_MISC_EN_rct_ahb] <-- 0x%08x\n",
                        REG_DEBUG_AUC_AHB_MISC_EN,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_AHB_MISC_EN_rct_ahb(void)
{
    GH_DEBUG_AUC_AHB_MISC_EN_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_AHB_MISC_EN);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_AHB_MISC_EN_rct_ahb] --> 0x%08x\n",
                        REG_DEBUG_AUC_AHB_MISC_EN,value);
    #endif
    return tmp_value.bitc.rct_ahb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CG_DDR_INIT (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CG_DDR_INIT(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CG_DDR_INIT = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_DDR_INIT] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_DDR_INIT,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CG_DDR_INIT(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_DDR_INIT);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_DDR_INIT] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_DDR_INIT,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_CG_DDR_INIT_Divide(U8 data)
{
    GH_DEBUG_AUC_CG_DDR_INIT_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CG_DDR_INIT;
    d.bitc.divide = data;
    *(volatile U32 *)REG_DEBUG_AUC_CG_DDR_INIT = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_DDR_INIT_Divide] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_DDR_INIT,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CG_DDR_INIT_Divide(void)
{
    GH_DEBUG_AUC_CG_DDR_INIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_DDR_INIT);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_DDR_INIT_Divide] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_DDR_INIT,value);
    #endif
    return tmp_value.bitc.divide;
}
void GH_DEBUG_AUC_set_CG_DDR_INIT_en(U8 data)
{
    GH_DEBUG_AUC_CG_DDR_INIT_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_CG_DDR_INIT;
    d.bitc.en = data;
    *(volatile U32 *)REG_DEBUG_AUC_CG_DDR_INIT = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CG_DDR_INIT_en] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CG_DDR_INIT,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_CG_DDR_INIT_en(void)
{
    GH_DEBUG_AUC_CG_DDR_INIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CG_DDR_INIT);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CG_DDR_INIT_en] --> 0x%08x\n",
                        REG_DEBUG_AUC_CG_DDR_INIT,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_DDR_DIV_RST (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_DDR_DIV_RST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_DDR_DIV_RST = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DDR_DIV_RST] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DDR_DIV_RST,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_DDR_DIV_RST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DDR_DIV_RST);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DDR_DIV_RST] --> 0x%08x\n",
                        REG_DEBUG_AUC_DDR_DIV_RST,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_DDRC_IDSP_RESET (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_DDRC_IDSP_RESET(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_DDRC_IDSP_RESET = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DDRC_IDSP_RESET] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DDRC_IDSP_RESET,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_DDRC_IDSP_RESET(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DDRC_IDSP_RESET);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DDRC_IDSP_RESET] --> 0x%08x\n",
                        REG_DEBUG_AUC_DDRC_IDSP_RESET,value);
    #endif
    return value;
}
void GH_DEBUG_AUC_set_DDRC_IDSP_RESET_ddrc(U8 data)
{
    GH_DEBUG_AUC_DDRC_IDSP_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DDRC_IDSP_RESET;
    d.bitc.ddrc = data;
    *(volatile U32 *)REG_DEBUG_AUC_DDRC_IDSP_RESET = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DDRC_IDSP_RESET_ddrc] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DDRC_IDSP_RESET,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DDRC_IDSP_RESET_ddrc(void)
{
    GH_DEBUG_AUC_DDRC_IDSP_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DDRC_IDSP_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DDRC_IDSP_RESET_ddrc] --> 0x%08x\n",
                        REG_DEBUG_AUC_DDRC_IDSP_RESET,value);
    #endif
    return tmp_value.bitc.ddrc;
}
void GH_DEBUG_AUC_set_DDRC_IDSP_RESET_idsp(U8 data)
{
    GH_DEBUG_AUC_DDRC_IDSP_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_AUC_DDRC_IDSP_RESET;
    d.bitc.idsp = data;
    *(volatile U32 *)REG_DEBUG_AUC_DDRC_IDSP_RESET = d.all;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_DDRC_IDSP_RESET_idsp] <-- 0x%08x\n",
                        REG_DEBUG_AUC_DDRC_IDSP_RESET,d.all,d.all);
    #endif
}
U8   GH_DEBUG_AUC_get_DDRC_IDSP_RESET_idsp(void)
{
    GH_DEBUG_AUC_DDRC_IDSP_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_DDRC_IDSP_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_DDRC_IDSP_RESET_idsp] --> 0x%08x\n",
                        REG_DEBUG_AUC_DDRC_IDSP_RESET,value);
    #endif
    return tmp_value.bitc.idsp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_AUC_CKEN_IDSP (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_AUC_set_CKEN_IDSP(U32 data)
{
    *(volatile U32 *)REG_DEBUG_AUC_CKEN_IDSP = data;
    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_AUC_set_CKEN_IDSP] <-- 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_IDSP,data,data);
    #endif
}
U32  GH_DEBUG_AUC_get_CKEN_IDSP(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_AUC_CKEN_IDSP);

    #if GH_DEBUG_AUC_ENABLE_DEBUG_PRINT
    GH_DEBUG_AUC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_AUC_get_CKEN_IDSP] --> 0x%08x\n",
                        REG_DEBUG_AUC_CKEN_IDSP,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_DEBUG_AUC_init(void)
{
    GH_DEBUG_AUC_set_PLL_CORE_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_CORE_FRAC((U32)0x00000000);
    GH_DEBUG_AUC_set_HDMI_CTRL((U32)0x00000002);
    GH_DEBUG_AUC_set_SCALER_SD48((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO_FRAC((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_VIDEO((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_SENSOR_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_SENSOR_FRAC((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_SENSOR_POST((U32)0x00000000);
    GH_DEBUG_AUC_set_SYS_CONFIG((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_UART((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_SSI((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_MOTOR((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_IR((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_HOST((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_SENSOR_PRE((U32)0x00000000);
    GH_DEBUG_AUC_set_ANA_PWR((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_AUDIO_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_AUDIO_FRAC((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_AUDIO((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_AUDIO_PRE((U32)0x00000000);
    GH_DEBUG_AUC_set_SOFT_OR_DLLRESET((U32)0x00000000);
    GH_DEBUG_AUC_set_FIO_RESET((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_USB((U32)0x00000000);
    GH_DEBUG_AUC_set_CLK_DEBOUNCE((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_PWM((U32)0x00000000);
    GH_DEBUG_AUC_set_USBP_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_CKEN_VDSP((U32)0x00000000);
    GH_DEBUG_AUC_set_DLL0((U32)0x00000000);
    GH_DEBUG_AUC_set_DLL1((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_ADC((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_VIDEO_POST((U32)0x00000000);
    GH_DEBUG_AUC_set_CLK_REF_AU_EXTERNAL((U32)0x00000000);
    GH_DEBUG_AUC_set_USE_EXTERNAL_CLK_AU((U32)0x00000000);
    GH_DEBUG_AUC_set_CLK_REF_VIDEO_EXTERNAL((U32)0x00000000);
    GH_DEBUG_AUC_set_USE_EXTERNAL_VD_CLK((U32)0x00000000);
    GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_AU((U32)0x00000000);
    GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO((U32)0x00000000);
    GH_DEBUG_AUC_set_CLK_SI_INPUT_MODE((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO2_FRAC((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_VIDEO2((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_VIDEO2_POST((U32)0x00000000);
    GH_DEBUG_AUC_set_USE_CLK_SI_4_CLK_VO2((U32)0x00000000);
    GH_DEBUG_AUC_set_USE_EXTERNAL_VD2_CLK((U32)0x00000000);
    GH_DEBUG_AUC_set_CLK_REF_VIDEO2_EXTERNAL((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_DDR_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_DDR_FRAC((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_IDSP_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_IDSP_FRAC((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_SSI2((U32)0x00000000);
    GH_DEBUG_AUC_set_LVDS_LVCMOS((U32)0x00000000);
    GH_DEBUG_AUC_set_LVDS_ASYNC((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_CORE_CTRL2((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_CORE_CTRL3((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_IDSP_CTRL2((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_IDSP_CTRL3((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_IDSP_CTRL22((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_IDSP_CTRL32((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_CORE_POST((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_SENSOR_CTRL2((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_SENSOR_CTRL3((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_AUDIO_CTRL2((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_AUDIO_CTRL3((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO_CTRL2((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO_CTRL3((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO2_CTRL2((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_USB_CTRL2((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_DDR_CALIB((U32)0x00000000);
    GH_DEBUG_AUC_set_DLL_CTRL_SEL((U32)0x00000000);
    GH_DEBUG_AUC_set_DLL_OCD_BITS((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_CORE_OBSV((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_IDSP_OBSV((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_DDR_OBSV((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_SENSOR_OBSV((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_AUDIO_OBSV((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO_OBSV((U32)0x00000000);
    GH_DEBUG_AUC_set_PLL_VIDEO2_OBSV((U32)0x00000000);
    GH_DEBUG_AUC_set_ADC16_CTRL_ADDR((U32)0x00000000);
    GH_DEBUG_AUC_set_CLK_REF_SSI_ADDR((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_DVEN((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_MS((U32)0x00000000);
    GH_DEBUG_AUC_set_MS_DELAY_CTRL((U32)0x00000000);
    GH_DEBUG_AUC_set_USE_COMMON_VO_CLOCK((U32)0x00000000);
    GH_DEBUG_AUC_set_CLOCK_OBSV_ADDR((U32)0x00000000);
    GH_DEBUG_AUC_set_DISABLE_EXT_BYPASS((U32)0x00000000);
    GH_DEBUG_AUC_set_ARM_SYNC_LOCK((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_ARM_SYNC((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_ARM_ASYNC((U32)0x00000000);
    GH_DEBUG_AUC_set_SCALER_IDSP_POST((U32)0x00000000);
    GH_DEBUG_AUC_set_OCTRL_GPIO((U32)0x00000000);
    GH_DEBUG_AUC_set_IOCTRL_MISC1((U32)0x00000000);
    GH_DEBUG_AUC_set_OCTRL_MISC2((U32)0x00000000);
    GH_DEBUG_AUC_set_IOCTRL_SD((U32)0x00000000);
    GH_DEBUG_AUC_set_IOCTRL_SMIO((U32)0x00000000);
    GH_DEBUG_AUC_set_IOCTRL_VD0((U32)0x00000000);
    GH_DEBUG_AUC_set_IOCTRL_VD1((U32)0x00000000);
    GH_DEBUG_AUC_set_IOCTRL_SENSOR((U32)0x00000000);
    GH_DEBUG_AUC_set_AHB_MISC_EN((U32)0x00000000);
    GH_DEBUG_AUC_set_CG_DDR_INIT((U32)0x00000000);
    GH_DEBUG_AUC_set_DDR_DIV_RST((U32)0x00000000);
    GH_DEBUG_AUC_set_DDRC_IDSP_RESET((U32)0x00000000);
    GH_DEBUG_AUC_set_CKEN_IDSP((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

