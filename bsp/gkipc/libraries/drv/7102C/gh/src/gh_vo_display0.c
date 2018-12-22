/******************************************************************************
**
** \file      gh_vo_display0.c
**
** \brief     VO Display A access function.
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
#include "gh_vo_display0.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_VO_DISPLAY0_BACKGROUND_S             m_vo_display0_background;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_0_S    m_vo_display0_digital_csc_param_0;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_1_S    m_vo_display0_digital_csc_param_1;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_2_S    m_vo_display0_digital_csc_param_2;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_3_S    m_vo_display0_digital_csc_param_3;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_4_S    m_vo_display0_digital_csc_param_4;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_5_S    m_vo_display0_digital_csc_param_5;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_6_S    m_vo_display0_digital_csc_param_6;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_7_S    m_vo_display0_digital_csc_param_7;
GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_8_S    m_vo_display0_digital_csc_param_8;

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_CONTROL (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_CONTROL_Fixed_Format(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.fixed_format = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Fixed_Format] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_CONTROL_Fixed_Format(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Fixed_Format] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.fixed_format;
}
void GH_VO_DISPLAY0_set_CONTROL_Interlace_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.interlace_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Interlace_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_CONTROL_Interlace_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Interlace_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.interlace_enable;
}
void GH_VO_DISPLAY0_set_CONTROL_Reverse_Mode_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.reverse_mode_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Reverse_Mode_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_CONTROL_Reverse_Mode_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Reverse_Mode_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.reverse_mode_enable;
}
void GH_VO_DISPLAY0_set_CONTROL_VOUT_VOUT_Sync_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.vout_vout_sync_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_VOUT_VOUT_Sync_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_CONTROL_VOUT_VOUT_Sync_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_VOUT_VOUT_Sync_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.vout_vout_sync_enable;
}
void GH_VO_DISPLAY0_set_CONTROL_VIN_VOUT_Sync_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.vin_vout_sync_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_VIN_VOUT_Sync_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_CONTROL_VIN_VOUT_Sync_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_VIN_VOUT_Sync_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.vin_vout_sync_enable;
}
void GH_VO_DISPLAY0_set_CONTROL_Digital_Output_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.digital_output_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Digital_Output_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_CONTROL_Digital_Output_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Digital_Output_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.digital_output_enable;
}
void GH_VO_DISPLAY0_set_CONTROL_I80_Output_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.i80_output_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_I80_Output_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_CONTROL_I80_Output_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_I80_Output_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.i80_output_enable;
}
void GH_VO_DISPLAY0_set_CONTROL_Reset(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Reset] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_CONTROL_Reset(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Reset] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_STATUS (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_STATUS(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_STATUS(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_STATUS_HDMI_Field(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.hdmi_field = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_HDMI_Field] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_STATUS_HDMI_Field(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_HDMI_Field] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.hdmi_field;
}
void GH_VO_DISPLAY0_set_STATUS_Analog_Fied(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.analog_fied = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Analog_Fied] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_STATUS_Analog_Fied(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Analog_Fied] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.analog_fied;
}
void GH_VO_DISPLAY0_set_STATUS_Digital_Field(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.digital_field = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Digital_Field] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_STATUS_Digital_Field(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Digital_Field] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.digital_field;
}
void GH_VO_DISPLAY0_set_STATUS_HDMI_Underflow(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.hdmi_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_HDMI_Underflow] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_STATUS_HDMI_Underflow(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_HDMI_Underflow] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.hdmi_underflow;
}
void GH_VO_DISPLAY0_set_STATUS_Analog_Underflow(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.analog_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Analog_Underflow] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_STATUS_Analog_Underflow(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Analog_Underflow] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.analog_underflow;
}
void GH_VO_DISPLAY0_set_STATUS_Digital_Underflow(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.digital_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Digital_Underflow] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_STATUS_Digital_Underflow(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Digital_Underflow] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.digital_underflow;
}
void GH_VO_DISPLAY0_set_STATUS_SDTV_Configuration_Ready(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.sdtv_configuration_ready = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_SDTV_Configuration_Ready] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_STATUS_SDTV_Configuration_Ready(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_SDTV_Configuration_Ready] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.sdtv_configuration_ready;
}
void GH_VO_DISPLAY0_set_STATUS_Reset(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Reset] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_STATUS_Reset(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Reset] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_FRAME_SIZE_FIELD0 (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Height(U16 data)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Height] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Height(void)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Height] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,value);
    #endif
    return tmp_value.bitc.height;
}
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Width(U16 data)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0;
    d.bitc.width = data;
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Width] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Width(void)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Width] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,value);
    #endif
    return tmp_value.bitc.width;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_FRAME_SIZE_FIELD1 (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD1,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD1,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1_Height(U16 data)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1_Height] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1_Height(void)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1_Height] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD1,value);
    #endif
    return tmp_value.bitc.height;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_row(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_row(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,value);
    #endif
    return tmp_value.bitc.row;
}
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_column(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_column(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_ACTIVE_REGION_END_0 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_row(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_row(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,value);
    #endif
    return tmp_value.bitc.row;
}
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_column(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_column(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_row(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_row(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,value);
    #endif
    return tmp_value.bitc.row;
}
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_column(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_column(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_ACTIVE_REGION_END_1 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_row(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_row(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,value);
    #endif
    return tmp_value.bitc.row;
}
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_column(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_column(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_BACKGROUND (write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_BACKGROUND(U32 data)
{
    m_vo_display0_background.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_BACKGROUND = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_BACKGROUND] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_BACKGROUND,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_BACKGROUND(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_BACKGROUND] --> 0x%08x\n",
                        m_vo_display0_background.all);
    #endif
    return m_vo_display0_background.all;
}
void GH_VO_DISPLAY0_set_BACKGROUND_v(U8 data)
{
    m_vo_display0_background.bitc.v = data;
    *(volatile U32 *)REG_VO_DISPLAY0_BACKGROUND = m_vo_display0_background.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_BACKGROUND_v] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_BACKGROUND,m_vo_display0_background.all,m_vo_display0_background.all);
    #endif
}
U8   GH_VO_DISPLAY0_getm_BACKGROUND_v(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_BACKGROUND_v] --> 0x%08x\n",
                        m_vo_display0_background.bitc.v);
    #endif
    return m_vo_display0_background.bitc.v;
}
void GH_VO_DISPLAY0_set_BACKGROUND_u(U8 data)
{
    m_vo_display0_background.bitc.u = data;
    *(volatile U32 *)REG_VO_DISPLAY0_BACKGROUND = m_vo_display0_background.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_BACKGROUND_u] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_BACKGROUND,m_vo_display0_background.all,m_vo_display0_background.all);
    #endif
}
U8   GH_VO_DISPLAY0_getm_BACKGROUND_u(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_BACKGROUND_u] --> 0x%08x\n",
                        m_vo_display0_background.bitc.u);
    #endif
    return m_vo_display0_background.bitc.u;
}
void GH_VO_DISPLAY0_set_BACKGROUND_y(U8 data)
{
    m_vo_display0_background.bitc.y = data;
    *(volatile U32 *)REG_VO_DISPLAY0_BACKGROUND = m_vo_display0_background.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_BACKGROUND_y] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_BACKGROUND,m_vo_display0_background.all,m_vo_display0_background.all);
    #endif
}
U8   GH_VO_DISPLAY0_getm_BACKGROUND_y(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_BACKGROUND_y] --> 0x%08x\n",
                        m_vo_display0_background.bitc.y);
    #endif
    return m_vo_display0_background.bitc.y;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_OUTPUT (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_OUTPUT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Hsync_Polarity(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_hsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Hsync_Polarity] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Hsync_Polarity(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Hsync_Polarity] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_hsync_polarity;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Vsync_Polarity(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_vsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Vsync_Polarity] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Vsync_Polarity(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Vsync_Polarity] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_vsync_polarity;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_output_divider = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Output_Divider] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Output_Divider] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_output_divider;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_divider_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_divider_enable;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Edge(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_edge = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Edge] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Edge(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Edge] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_edge;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Disable(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_disable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Disable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Disable(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Disable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_disable;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_divider_pattern_width = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_divider_pattern_width;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_MIPI_Configuration(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.mipi_configuration = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_MIPI_Configuration] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_MIPI_Configuration(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_MIPI_Configuration] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.mipi_configuration;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.color_sequence_even_lines = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Even_Lines] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Even_Lines] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.color_sequence_even_lines;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.color_sequence_odd_lines = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.color_sequence_odd_lines;
}
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Mode(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.mode = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Mode] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Mode(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Mode] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_HSYNC_CONTROL (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_end_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL;
    d.bitc.end_column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_end_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_end_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_end_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,value);
    #endif
    return tmp_value.bitc.end_column;
}
void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_start_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL;
    d.bitc.start_column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_start_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_start_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_start_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,value);
    #endif
    return tmp_value.bitc.start_column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_VSYNC_START_0 (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,value);
    #endif
    return tmp_value.bitc.row;
}
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_VSYNC_END_0 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,value);
    #endif
    return tmp_value.bitc.row;
}
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_VSYNC_START_1 (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,value);
    #endif
    return tmp_value.bitc.row;
}
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_VSYNC_END_1 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,value);
    #endif
    return tmp_value.bitc.row;
}
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_656_VBIT (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_VBIT] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_VBIT] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_end_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_656_VBIT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT;
    d.bitc.end_row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_end_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_end_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_656_VBIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_end_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,value);
    #endif
    return tmp_value.bitc.end_row;
}
void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_start_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_656_VBIT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT;
    d.bitc.start_row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_start_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_start_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_656_VBIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_start_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,value);
    #endif
    return tmp_value.bitc.start_row;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_656_SAV_START (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_SAV_START,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_SAV_START,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START_Code_Location(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_656_SAV_START_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START;
    d.bitc.code_location = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START_Code_Location] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_SAV_START,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START_Code_Location(void)
{
    GH_VO_DISPLAY0_DIGITAL_656_SAV_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START_Code_Location] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_SAV_START,value);
    #endif
    return tmp_value.bitc.code_location;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0 (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1 (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2 (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN2(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN2] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN2(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN2] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3 (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN3(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN3] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN3(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN3] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_0 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0(U32 data)
{
    m_vo_display0_digital_csc_param_0.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_0.all);
    #endif
    return m_vo_display0_digital_csc_param_0.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a0246(U16 data)
{
    m_vo_display0_digital_csc_param_0.bitc.coefficient_a0246 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0 = m_vo_display0_digital_csc_param_0.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a0246] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0,m_vo_display0_digital_csc_param_0.all,m_vo_display0_digital_csc_param_0.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_0.bitc.coefficient_a0246);
    #endif
    return m_vo_display0_digital_csc_param_0.bitc.coefficient_a0246;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a1357(U16 data)
{
    m_vo_display0_digital_csc_param_0.bitc.coefficient_a1357 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0 = m_vo_display0_digital_csc_param_0.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a1357] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0,m_vo_display0_digital_csc_param_0.all,m_vo_display0_digital_csc_param_0.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_0.bitc.coefficient_a1357);
    #endif
    return m_vo_display0_digital_csc_param_0.bitc.coefficient_a1357;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_1 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1(U32 data)
{
    m_vo_display0_digital_csc_param_1.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_1.all);
    #endif
    return m_vo_display0_digital_csc_param_1.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a0246(U16 data)
{
    m_vo_display0_digital_csc_param_1.bitc.coefficient_a0246 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1 = m_vo_display0_digital_csc_param_1.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a0246] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1,m_vo_display0_digital_csc_param_1.all,m_vo_display0_digital_csc_param_1.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_1.bitc.coefficient_a0246);
    #endif
    return m_vo_display0_digital_csc_param_1.bitc.coefficient_a0246;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a1357(U16 data)
{
    m_vo_display0_digital_csc_param_1.bitc.coefficient_a1357 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1 = m_vo_display0_digital_csc_param_1.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a1357] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1,m_vo_display0_digital_csc_param_1.all,m_vo_display0_digital_csc_param_1.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_1.bitc.coefficient_a1357);
    #endif
    return m_vo_display0_digital_csc_param_1.bitc.coefficient_a1357;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_2 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2(U32 data)
{
    m_vo_display0_digital_csc_param_2.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_2.all);
    #endif
    return m_vo_display0_digital_csc_param_2.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a0246(U16 data)
{
    m_vo_display0_digital_csc_param_2.bitc.coefficient_a0246 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2 = m_vo_display0_digital_csc_param_2.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a0246] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2,m_vo_display0_digital_csc_param_2.all,m_vo_display0_digital_csc_param_2.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_2.bitc.coefficient_a0246);
    #endif
    return m_vo_display0_digital_csc_param_2.bitc.coefficient_a0246;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a1357(U16 data)
{
    m_vo_display0_digital_csc_param_2.bitc.coefficient_a1357 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2 = m_vo_display0_digital_csc_param_2.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a1357] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2,m_vo_display0_digital_csc_param_2.all,m_vo_display0_digital_csc_param_2.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_2.bitc.coefficient_a1357);
    #endif
    return m_vo_display0_digital_csc_param_2.bitc.coefficient_a1357;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_3 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3(U32 data)
{
    m_vo_display0_digital_csc_param_3.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_3.all);
    #endif
    return m_vo_display0_digital_csc_param_3.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a0246(U16 data)
{
    m_vo_display0_digital_csc_param_3.bitc.coefficient_a0246 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3 = m_vo_display0_digital_csc_param_3.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a0246] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3,m_vo_display0_digital_csc_param_3.all,m_vo_display0_digital_csc_param_3.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_3.bitc.coefficient_a0246);
    #endif
    return m_vo_display0_digital_csc_param_3.bitc.coefficient_a0246;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a1357(U16 data)
{
    m_vo_display0_digital_csc_param_3.bitc.coefficient_a1357 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3 = m_vo_display0_digital_csc_param_3.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a1357] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3,m_vo_display0_digital_csc_param_3.all,m_vo_display0_digital_csc_param_3.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_3.bitc.coefficient_a1357);
    #endif
    return m_vo_display0_digital_csc_param_3.bitc.coefficient_a1357;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_4 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4(U32 data)
{
    m_vo_display0_digital_csc_param_4.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_4.all);
    #endif
    return m_vo_display0_digital_csc_param_4.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Coefficient_a8(U16 data)
{
    m_vo_display0_digital_csc_param_4.bitc.coefficient_a8 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4 = m_vo_display0_digital_csc_param_4.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Coefficient_a8] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4,m_vo_display0_digital_csc_param_4.all,m_vo_display0_digital_csc_param_4.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Coefficient_a8(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Coefficient_a8] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_4.bitc.coefficient_a8);
    #endif
    return m_vo_display0_digital_csc_param_4.bitc.coefficient_a8;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Constant_b0(U16 data)
{
    m_vo_display0_digital_csc_param_4.bitc.constant_b0 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4 = m_vo_display0_digital_csc_param_4.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Constant_b0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4,m_vo_display0_digital_csc_param_4.all,m_vo_display0_digital_csc_param_4.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Constant_b0(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Constant_b0] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_4.bitc.constant_b0);
    #endif
    return m_vo_display0_digital_csc_param_4.bitc.constant_b0;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_5 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5(U32 data)
{
    m_vo_display0_digital_csc_param_5.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_5.all);
    #endif
    return m_vo_display0_digital_csc_param_5.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b1(U16 data)
{
    m_vo_display0_digital_csc_param_5.bitc.constant_b1 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5 = m_vo_display0_digital_csc_param_5.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5,m_vo_display0_digital_csc_param_5.all,m_vo_display0_digital_csc_param_5.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b1(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b1] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_5.bitc.constant_b1);
    #endif
    return m_vo_display0_digital_csc_param_5.bitc.constant_b1;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b2(U16 data)
{
    m_vo_display0_digital_csc_param_5.bitc.constant_b2 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5 = m_vo_display0_digital_csc_param_5.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b2] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5,m_vo_display0_digital_csc_param_5.all,m_vo_display0_digital_csc_param_5.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b2(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b2] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_5.bitc.constant_b2);
    #endif
    return m_vo_display0_digital_csc_param_5.bitc.constant_b2;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_6 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6(U32 data)
{
    m_vo_display0_digital_csc_param_6.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_6.all);
    #endif
    return m_vo_display0_digital_csc_param_6.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(U16 data)
{
    m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_low = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6 = m_vo_display0_digital_csc_param_6.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6,m_vo_display0_digital_csc_param_6.all,m_vo_display0_digital_csc_param_6.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_low);
    #endif
    return m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_low;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(U16 data)
{
    m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_high = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6 = m_vo_display0_digital_csc_param_6.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6,m_vo_display0_digital_csc_param_6.all,m_vo_display0_digital_csc_param_6.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_high);
    #endif
    return m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_high;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_7 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7(U32 data)
{
    m_vo_display0_digital_csc_param_7.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_7.all);
    #endif
    return m_vo_display0_digital_csc_param_7.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(U16 data)
{
    m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_low = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7 = m_vo_display0_digital_csc_param_7.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7,m_vo_display0_digital_csc_param_7.all,m_vo_display0_digital_csc_param_7.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_low);
    #endif
    return m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_low;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(U16 data)
{
    m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_high = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7 = m_vo_display0_digital_csc_param_7.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7,m_vo_display0_digital_csc_param_7.all,m_vo_display0_digital_csc_param_7.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_high);
    #endif
    return m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_high;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_8 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8(U32 data)
{
    m_vo_display0_digital_csc_param_8.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_8.all);
    #endif
    return m_vo_display0_digital_csc_param_8.all;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(U16 data)
{
    m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_low = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8 = m_vo_display0_digital_csc_param_8.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8,m_vo_display0_digital_csc_param_8.all,m_vo_display0_digital_csc_param_8.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_low);
    #endif
    return m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_low;
}
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(U16 data)
{
    m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_high = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8 = m_vo_display0_digital_csc_param_8.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8,m_vo_display0_digital_csc_param_8.all,m_vo_display0_digital_csc_param_8.all);
    #endif
}
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_high);
    #endif
    return m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_high;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_VOUT_VOUT_SYNC (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC] --> 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,value);
    #endif
    return value;
}
void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Start_Row(U16 data)
{
    GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC;
    d.bitc.start_row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Start_Row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,d.all,d.all);
    #endif
}
U16  GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Start_Row(void)
{
    GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Start_Row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,value);
    #endif
    return tmp_value.bitc.start_row;
}
void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Field_Select(U8 data)
{
    GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC;
    d.bitc.field_select = data;
    *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Field_Select] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Field_Select(void)
{
    GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Field_Select] --> 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,value);
    #endif
    return tmp_value.bitc.field_select;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_INPUT_STREAM_ENABLES (read/write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_INPUT_STREAM_ENABLES(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_INPUT_STREAM_ENABLES = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_INPUT_STREAM_ENABLES] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_INPUT_STREAM_ENABLES,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_INPUT_STREAM_ENABLES(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_INPUT_STREAM_ENABLES);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_INPUT_STREAM_ENABLES] --> 0x%08x\n",
                        REG_VO_DISPLAY0_INPUT_STREAM_ENABLES,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_INPUT_SYNC_CONTROL (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_INPUT_SYNC_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_INPUT_SYNC_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_INPUT_SYNC_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_INPUT_SYNC_CONTROL,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_INPUT_SYNC_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_INPUT_SYNC_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_INPUT_SYNC_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_INPUT_SYNC_CONTROL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_OUTPUT_SYNC_CONTROL (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_OUTPUT_SYNC_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_OUTPUT_SYNC_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_OUTPUT_SYNC_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_OUTPUT_SYNC_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_STREAM_CONTROL (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_STREAM_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_STREAM_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STREAM_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STREAM_CONTROL,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_STREAM_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STREAM_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STREAM_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STREAM_CONTROL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_FRAME_ENABLE (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DISPLAY0_set_FRAME_ENABLE(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_ENABLE = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_ENABLE] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_ENABLE,data,data);
    #endif
}
U32  GH_VO_DISPLAY0_get_FRAME_ENABLE(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_ENABLE);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_ENABLE] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_ENABLE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VO_DISPLAY0_init(void)
{
    GH_VO_DISPLAY0_set_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY0_set_STATUS((U32)0x00000000);
    GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0((U32)0x00000000);
    GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1((U32)0x00000000);
    GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0((U32)0x00000000);
    GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0((U32)0x00000000);
    GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1((U32)0x00000000);
    GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1((U32)0x00000000);
    GH_VO_DISPLAY0_set_BACKGROUND((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_OUTPUT((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_656_VBIT((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN0((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN1((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN2((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN3((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7((U32)0x00000000);
    GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8((U32)0x00000000);
    GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC((U32)0x00000000);
    GH_VO_DISPLAY0_set_INPUT_STREAM_ENABLES((U32)0x00000000);
    GH_VO_DISPLAY0_set_INPUT_SYNC_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY0_set_OUTPUT_SYNC_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY0_set_STREAM_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY0_set_FRAME_ENABLE((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

